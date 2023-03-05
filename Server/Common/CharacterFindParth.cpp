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
	{// ���ն�̬�赲��
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
	// ��¼��Ϣ
	_nCharMapID = nMapID;
	_charPos = vSelfPos;

	//Ѱ·
	swVec2f nextPoint( vTargetPos.x, vTargetPos.y );
	swVec2f selfPoint( vSelfPos.x, vSelfPos.y );
	nextPoint = GetCurPointInParth( nextPoint, selfPoint, nMapID );

	// �ڵȴ��߳�Ѱ·
	if ( _blIsFindParthInThread )
		return false;

	//log
	//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "selfPos [%f,%f]\t targetPos[%f,%f]\t", GetFloatX(), GetFloatY(), pTarget->GetFloatX(), pTarget->GetFloatY() );
	//for ( int i = 0; i < _findParth.size(); ++i )
	//{
	//	LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "point [%f,%f]\t", _findParth[i].x, _findParth[i].y );
	//}
	//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "cur point index [%d]\t", _nCurPointInParthIndex );

	//���õ�ǰĿ���
	vTargetPos.x = nextPoint.x;
	vTargetPos.y = nextPoint.y;

	return true;
}

void CharacterFindParth::AfterMoveToPos( const D3DXVECTOR3& posMoveTo, unsigned int nMapID )
{
	if ( IsDynamicBlockOpen() )
	{// ��̬�赲����
		swVec2f lastPoint( _charPos.x, _charPos.y );
		swVec2f pointMoveTo( posMoveTo.x, posMoveTo.y );

		SwMap* pParthFinder = GetStageParthFinder(nMapID);
		SwMap* pStaticParthFinder = GetStageThreadParthFinder(nMapID);
		if ( pParthFinder && pStaticParthFinder )
		{
			ClearBlockPoint( *pParthFinder, lastPoint, *pStaticParthFinder );

			if ( pParthFinder->CanReach( pointMoveTo ) == false && IsDynamicBlockOpen() )
			{// ��¼�ƶ����赲��
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
	{//���к���·��������ƶ�
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
	// �õ���ǰ��ͼ��Ѱ·��
	SwMap* pParthFinder = GetStageParthFinder( nMapID );
	if ( NULL == pParthFinder )
		return targetPos;

	bool blNeedFindParth = true;

	// ͨ���Ż�
	D3DXVECTOR3 vecSelfTargetDistance( targetPos.x - selfPos.x, targetPos.y - selfPos.y, 0 );
	float fSelfTargetDistance = D3DXVec3Length( &vecSelfTargetDistance );
	if ( fSelfTargetDistance > 100.0f )
	{// �����Զ,����Ѱ·
		blNeedFindParth = false;
	}
	swVec2f targetLastPos;
	if ( ! _findParth.empty() )
	{ targetLastPos = _findParth.back(); }
	D3DXVECTOR3 vecTargetMoveDistance( targetPos.x - targetLastPos.x, targetPos.y - targetLastPos.y, 0 );
	float fTargetMoveDistance = D3DXVec3Length( &vecTargetMoveDistance );
	if ( ! _findParth.empty() && fTargetMoveDistance < 0.5f )
	{// Ŀ���ƶ�����,������Ѱ·
		blNeedFindParth = false;
	}

	if ( ! IsDynamicBlockOpen() )
	{// ��̬�赲ʱ�ݲ����Ż�
		if ( IsAStarParth() || IsPosParth() )
		{// �ϴ�Ѱ··��ΪA*����λ��·��
			if ( pParthFinder->SameMapGrid( targetLastPos, targetPos) )
			{// Ŀ�껹��ͬһ������,������Ѱ·
				blNeedFindParth = false;
				if ( IsAStarParth() && ! _findParth.empty() )
				{// A*·���򸲸�Ŀ��λ��
					_findParth[ _findParth.size() - 1 ] = targetPos;	// ��Ŀ��λ��
				}
			}
		}
	}

	if ( blNeedFindParth )
	{// ��Ҫ����Ѱ·
		// ע��:����Ѱ·�߳�ʹ�õ�Ѱ·��,���̲߳����ô�Ѱ·��Ѱ·,����ֻ�������Ŀ��λ���Ƿ��վ��
		SwMap* pThreadParthFinder = GetStageThreadParthFinder( nMapID );
		if ( pThreadParthFinder )
		{
			if ( pThreadParthFinder->CanReach( selfPos ) == false )
			{// ���ش���: ��ɫ��վ���赲��
				_nDynamicBlockState = DBS_TempClose;
				return targetPos;
			}

			if ( fSelfTargetDistance > 30.0f || pThreadParthFinder->CanReach(targetPos) == false )
			{// �������һ������,����Ŀ��λ�ò���վ��,�򽻸�Ѱ·�߳�ȥѰ·
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
		{// �µ�λ�ÿ�ֱ��Ѱ·,�������ύ��Ѱ·�̵߳�Ѱ·
			_blIsFindParthInThread = false;
		}

		if ( IsDynamicBlockTempClosed() )
		{// ����ʱ�رյĶ�̬�赲
			_nDynamicBlockState = DBS_Open;
		}

		bool blSelfCanReach = pParthFinder->CanReach( selfPos );
		if ( false == blSelfCanReach )
		{// ��ʱ����������赲��
			ClearBlockPoint( *pParthFinder, selfPos, *pThreadParthFinder );
		}

		bool blTargetCanReach = pParthFinder->CanReach( targetPos );
		if ( false == blTargetCanReach )
		{// ��ʱ����Ŀ���Ϊ��վ��
			ClearBlockPoint( *pParthFinder, targetPos, *pThreadParthFinder );
		}

		if ( pParthFinder->CanMove( selfPos, targetPos ) )
		{//�����ֱ�ߵ���Ŀ��
			ClearParth();
			 _findParth.push_back(targetPos);
			SetFindParthState( FPS_Line );
			//LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "******************* line parth **************" );
		}
		else
		{// ����ֱ�ߵ���,����Ѱ·
			if ( ! _findParth.empty() && pParthFinder->CanMove( targetPos, targetLastPos ) )
			{// �����״�Ѱ·,�����Ż�
				_findParth.push_back( targetPos );
				SetFindParthState( FPS_Line );	// ����ֱ��,���Ǵ�ֱ����
			}
			else
			{
				swVec2f startPos = selfPos;
				std::vector< swVec2f > parthAdd;
				bool blClearParth = true;

				if ( ! _findParth.empty() )
				{// �����״�Ѱ·,�����Ż�
					// ȡ�Լ���Ŀ������Լ�Ŀ���ƶ������н�����A��Ѱ·
					if ( fTargetMoveDistance < fSelfTargetDistance )
					{
						startPos = targetLastPos;
						blClearParth = false;
					}
				}

				if ( pParthFinder->FindPath( startPos, targetPos, parthAdd ) )
				{// Ŀ����Ѱ·
					// Ѱ·�㷨ֻ��Ѱ��ͬ�����ڵĵ�,��Ҫ��Ŀ��λ�ü���·��
					parthAdd.push_back(targetPos);
					SetFindParthState( FPS_AStar );
				}
				else
				{// Ŀ��㲻��Ѱ·����Ѱ·ʧ��				
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
		{// �ָ�Ŀ��λ��Ϊ�赲��
			SetBlockPoint( *pParthFinder, targetPos, *pThreadParthFinder );
		}

		if ( false == blSelfCanReach )
		{// �ָ������赲��
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
	{// �������óɶ�̬�赲��
		parthFinder.AddBlockPoint( point.x, point.y );
	}
}

void CharacterFindParth::ClearBlockPoint( SwMap& parthFinder, const swVec2f& point, SwMap& staticParthFinder )
{
	if ( parthFinder.CanReach(point) == false && staticParthFinder.CanReach(point) == true )
	{// ��̬�赲�������赲��,�������
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
