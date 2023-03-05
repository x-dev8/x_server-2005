#include "CharacterFindParth.h"
#include "GameParthFinder.h"
#include "GameWorld.h"
#include "Configure.h"


CharacterFindParth::CharacterFindParth()
{
	_nCharID = 0;
	ClearFindParth();
}

void CharacterFindParth::InitFindParth( GameObjectId nCharID, bool blIsFindParth, bool blIsDynamicBlock )
{
	_nCharID = nCharID;
	ClearFindParth();
	SetIsFindParth( blIsFindParth );
	SetDynamicBlockState( blIsDynamicBlock ? DBS_Open : DBS_Close );
}

void CharacterFindParth::ClearFindParth()
{
	_nCharMapID = 0;
	_charPos = D3DXVECTOR3( 0, 0, 0 );
	_findParth.clear();
	_blIsFindParth = false;
	_nFinParthState = FPS_None;
	_nDynamicBlockState = DBS_Close;
	_blIsFindParthInThread = false;
}

void CharacterFindParth::ReInitFindParth( bool blIsFindParth, bool blIsDynamicBlock )
{
    if ( !g_Cfg.bAIFindParth )
    { return; }

	if ( blIsFindParth == IsFindParth() && blIsDynamicBlock == ! IsDynamicBlockClosed() )
	{ return; }

	if ( IsDynamicBlockOpen() )
	{// 回收动态阻挡点
		SwMap* pParthFinder = GetStageParthFinder(_nCharMapID);
		SwMap* pStaticParthFinder = GetStageThreadParthFinder(_nCharMapID);
		if ( pParthFinder && pStaticParthFinder )
		{
			ClearBlockPoint( *pParthFinder, swVec2f( _charPos.x, _charPos.y ), *pStaticParthFinder );
		}
	}

	ClearFindParth();
	SetIsFindParth( blIsFindParth );
	SetDynamicBlockState( blIsDynamicBlock ? DBS_Open : DBS_Close );
}

bool CharacterFindParth::FindTheNextPosToMove( D3DXVECTOR3& vTargetPos, const D3DXVECTOR3& vSelfPos, unsigned int nMapID )
{
	// 记录信息
	_nCharMapID = nMapID;
	_charPos = vSelfPos;

	//寻路
	swVec2f nextPoint( vTargetPos.x, vTargetPos.y );
	swVec2f selfPoint( vSelfPos.x, vSelfPos.y );
	nextPoint = GetCurPointInParth( nextPoint, selfPoint, nMapID );

	// 在等待线程寻路
	if ( _blIsFindParthInThread )
		return false;

	//log
	//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "selfPos [%f,%f]\t targetPos[%f,%f]\t", GetFloatX(), GetFloatY(), pTarget->GetFloatX(), pTarget->GetFloatY() );
	//for ( int i = 0; i < _findParth.size(); ++i )
	//{
	//	LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "point [%f,%f]\t", _findParth[i].x, _findParth[i].y );
	//}
	//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "cur point index [%d]\t", _nCurPointInParthIndex );

	//设置当前目标点
	vTargetPos.x = nextPoint.x;
	vTargetPos.y = nextPoint.y;

	return true;
}

void CharacterFindParth::AfterMoveToPos( const D3DXVECTOR3& posMoveTo, unsigned int nMapID )
{
	if ( IsDynamicBlockOpen() )
	{// 动态阻挡开启
		swVec2f lastPoint( _charPos.x, _charPos.y );
		swVec2f pointMoveTo( posMoveTo.x, posMoveTo.y );

		SwMap* pParthFinder = GetStageParthFinder(nMapID);
		SwMap* pStaticParthFinder = GetStageThreadParthFinder(nMapID);
		if ( pParthFinder && pStaticParthFinder )
		{
			ClearBlockPoint( *pParthFinder, lastPoint, *pStaticParthFinder );

			if ( pParthFinder->CanReach( pointMoveTo ) == false && IsDynamicBlockOpen() )
			{// 记录移动到阻挡点
				LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_DEBUG, "bad point[%f,%f]\t targetPoint[%f,%f]\t from[%f,%f]\tMapID[%d]",
					posMoveTo.x, posMoveTo.y, _findParth.empty() ? 0.0f : _findParth.back().x, _findParth.empty() ? 0.0f : _findParth.back().y, lastPoint.x, lastPoint.y, nMapID );
			}

			_charPos = posMoveTo;
			SetBlockPoint( *pParthFinder, pointMoveTo, *pStaticParthFinder );
		}
	}
}

bool CharacterFindParth::CheckReachPos()
{
	if ( NextPointInParth() )
	{//还有后续路点则继续移动
		return false;
	}
	else
	{
		SetFindParthState( FPS_None );
		return true;
	}
}

swVec2f CharacterFindParth::GetCurPointInParth( const swVec2f &targetPos, const swVec2f& selfPos, unsigned int nMapID )
{
	// 得到当前地图的寻路器
	SwMap* pParthFinder = GetStageParthFinder( nMapID );
	if ( NULL == pParthFinder )
		return targetPos;

	bool blNeedFindParth = true;

	// 通用优化
	D3DXVECTOR3 vecSelfTargetDistance( targetPos.x - selfPos.x, targetPos.y - selfPos.y, 0 );
	float fSelfTargetDistance = D3DXVec3Length( &vecSelfTargetDistance );
	if ( fSelfTargetDistance > 100.0f )
	{// 距离过远,不再寻路
		blNeedFindParth = false;
	}
	swVec2f targetLastPos;
	if ( ! _findParth.empty() )
	{ targetLastPos = _findParth.back(); }
	D3DXVECTOR3 vecTargetMoveDistance( targetPos.x - targetLastPos.x, targetPos.y - targetLastPos.y, 0 );
	float fTargetMoveDistance = D3DXVec3Length( &vecTargetMoveDistance );
	if ( ! _findParth.empty() && fTargetMoveDistance < 0.5f )
	{// 目标移动很少,不重新寻路
		blNeedFindParth = false;
	}

	if ( ! IsDynamicBlockOpen() )
	{// 动态阻挡时暂不做优化
		if ( IsAStarParth() || IsPosParth() )
		{// 上次寻路路径为A*或者位置路径
			if ( pParthFinder->SameMapGrid( targetLastPos, targetPos) )
			{// 目标还在同一格子内,不重新寻路
				blNeedFindParth = false;
				if ( IsAStarParth() && ! _findParth.empty() )
				{// A*路径则覆盖目标位置
					_findParth[ _findParth.size() - 1 ] = targetPos;	// 新目标位置
				}
			}
		}
	}

	if ( blNeedFindParth )
	{// 需要做次寻路
		// 注意:这是寻路线程使用的寻路器,主线程不可用此寻路器寻路,这里只用来检查目标位置是否可站立
		SwMap* pThreadParthFinder = GetStageThreadParthFinder( nMapID );
		if ( pThreadParthFinder )
		{
			if ( pThreadParthFinder->CanReach( selfPos ) == false )
			{// 严重错误: 角色已站在阻挡点
				_nDynamicBlockState = DBS_TempClose;
				return targetPos;
			}

			if ( fSelfTargetDistance > 30.0f || pThreadParthFinder->CanReach(targetPos) == false )
			{// 如果超过一定距离,或者目标位置不可站立,则交给寻路线程去寻路
				if ( false == _blIsFindParthInThread )
				{
					GameParthFinder::FindParthReq req;
					req.nChaID = _nCharID;
					req.nStageID = nMapID;
					req.startPos = selfPos;
					req.targetPos = targetPos;
					GetGameParthFinder().AddFindParthReq(req);

					_blIsFindParthInThread = true;
				}

				return selfPos;
			}
		}

		if ( _blIsFindParthInThread )
		{// 新的位置可直接寻路,放弃已提交给寻路线程的寻路
			_blIsFindParthInThread = false;
		}

		if ( IsDynamicBlockTempClosed() )
		{// 打开暂时关闭的动态阻挡
			_nDynamicBlockState = DBS_Open;
		}

		bool blSelfCanReach = pParthFinder->CanReach( selfPos );
		if ( false == blSelfCanReach )
		{// 暂时屏蔽自身的阻挡点
			ClearBlockPoint( *pParthFinder, selfPos, *pThreadParthFinder );
		}

		bool blTargetCanReach = pParthFinder->CanReach( targetPos );
		if ( false == blTargetCanReach )
		{// 暂时设置目标点为可站立
			ClearBlockPoint( *pParthFinder, targetPos, *pThreadParthFinder );
		}

		if ( pParthFinder->CanMove( selfPos, targetPos ) )
		{//如果能直线到达目标
			ClearParth();
			 _findParth.push_back(targetPos);
			SetFindParthState( FPS_Line );
			//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "******************* line parth **************" );
		}
		else
		{// 不能直线到达,尝试寻路
			if ( ! _findParth.empty() && pParthFinder->CanMove( targetPos, targetLastPos ) )
			{// 不是首次寻路,尝试优化
				_findParth.push_back( targetPos );
				SetFindParthState( FPS_Line );	// 不是直线,但是带直线型
			}
			else
			{
				swVec2f startPos = selfPos;
				std::vector< swVec2f > parthAdd;
				bool blClearParth = true;

				if ( ! _findParth.empty() )
				{// 不是首次寻路,尝试优化
					// 取自己和目标距离以及目标移动距离中近的做A星寻路
					if ( fTargetMoveDistance < fSelfTargetDistance )
					{
						startPos = targetLastPos;
						blClearParth = false;
					}
				}

				if ( pParthFinder->FindPath( startPos, targetPos, parthAdd ) )
				{// 目标点可寻路
					// 寻路算法只能寻到同格子内的点,需要将目标位置加入路径
					parthAdd.push_back(targetPos);
					SetFindParthState( FPS_AStar );
				}
				else
				{// 目标点不可寻路或者寻路失败				
					parthAdd.push_back(selfPos);
					SetFindParthState( FPS_None );
				}

				if ( blClearParth )
				{ ClearParth();	}
				std::vector< swVec2f >::iterator itr = parthAdd.begin();
				for ( ; itr != parthAdd.end(); ++itr )
				{ _findParth.push_back( *itr ); }
			}
		}

		if ( false == blTargetCanReach )
		{// 恢复目标位置为阻挡点
			SetBlockPoint( *pParthFinder, targetPos, *pThreadParthFinder );
		}

		if ( false == blSelfCanReach )
		{// 恢复自身阻挡点
			SetBlockPoint( *pParthFinder, selfPos, *pThreadParthFinder );
		}
	}

	if ( _findParth.empty() )
		return selfPos;
	return _findParth.front();
}

bool CharacterFindParth::NextPointInParth()
{
	if ( _findParth.empty() )
	{ return true; }
	_findParth.pop_front();
	return ! _findParth.empty();
}

void CharacterFindParth::CloseDynamicBlock( unsigned int nMapID, const swVec2f& point )
{
	SwMap* pParthFinder = GetStageParthFinder(nMapID);
	SwMap* pStaticParthFinder = GetStageThreadParthFinder(nMapID);
	if ( pParthFinder && pStaticParthFinder )
	{
		ClearBlockPoint( *pParthFinder, point, *pStaticParthFinder );
		_nDynamicBlockState = DBS_Close;
	}
}

void CharacterFindParth::TempCloseDynamicBlock( unsigned int nMapID, const swVec2f& point )
{
	SwMap* pParthFinder = GetStageParthFinder(nMapID);
	SwMap* pStaticParthFinder = GetStageThreadParthFinder(nMapID);
	if ( pParthFinder && pStaticParthFinder )
	{
		ClearBlockPoint( *pParthFinder, point, *pStaticParthFinder );
		_nDynamicBlockState = DBS_TempClose;
	}
}

void CharacterFindParth::SetBlockPoint( SwMap& parthFinder, const swVec2f& point, SwMap& staticParthFinder )
{
	if ( staticParthFinder.CanReach(point) && parthFinder.CanReach(point) )
	{// 允许设置成动态阻挡点
		parthFinder.AddBlockPoint( point.x, point.y );
	}
}

void CharacterFindParth::ClearBlockPoint( SwMap& parthFinder, const swVec2f& point, SwMap& staticParthFinder )
{
	if ( parthFinder.CanReach(point) == false && staticParthFinder.CanReach(point) == true )
	{// 动态阻挡产生的阻挡点,可以清除
		parthFinder.DelBlockPoint( point.x, point.y );
	}
}

SwMap* CharacterFindParth::GetStageParthFinder( unsigned int nMapID )
{
	GameStage* pStage = theGameWorld.GetStageById( nMapID );
	if ( NULL == pStage )
		return NULL;

	SwMap* pParthFinder = pStage->GetParthFinder();
	return pParthFinder;
}

SwMap* CharacterFindParth::GetStageThreadParthFinder( unsigned int nMapID )
{
	GameStage* pStage = theGameWorld.GetStageById( nMapID );
	if ( NULL == pStage )
		return NULL;

	SwMap* pParthFinder = pStage->GetThreadParthFinder();
	return pParthFinder;
}

void CharacterFindParth::SetFindParth( const std::vector< swVec2f >& parth, unsigned char nFindParthState, unsigned int nMapID, const D3DXVECTOR3& selfPos )
{
	if ( ! _blIsFindParthInThread )
		return;
	_blIsFindParthInThread = false;

	ClearParth();
	std::vector< swVec2f >::const_iterator itr = parth.begin();
	for ( ; itr != parth.end(); ++itr )
	{ _findParth.push_back( *itr );	}
	SetFindParthState(nFindParthState);
	if ( IsDynamicBlockOpen() )
	{
		TempCloseDynamicBlock( nMapID, swVec2f( selfPos.x, selfPos.y ) );
	}
}
