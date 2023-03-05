#include "AiCharacter.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "GameWorld.h"
#include "RouteManager.h"
#include "D3DFunction.h"
#include "TeamManager.h"

AiCharacter::AiCharacter()
{
    m_nUseSkillIndex     = 0;
    m_nRouteStep         = -1;
    m_pRoute             = NULL;
    m_bNeedVerifyPoint   = false;
    m_n9AreaPlayerCount  = 0;
    m_fMoveStep          = 1.0f;
    m_nDeathScriptVMID        = -1;
    m_nThinkingTime      = 0;
    m_nUseSkillTotalRate = 0;
    m_nTalkCount         = 0;
    ClearLockID();
    SetAiStatus( AiDefine::ThinkingMoveAround );
    ClearMoveTargetPoint();
    ClearLastIdlePoint();
    SetViewSight( AiDefine::MinEnmityViewSight );

    SetForce( ForceDefine::NoneForce );
    SetStatus( CS_IDLE );
    SetDead( false );

	for(int i =0;i<BodyStatusType_Max;++i)
		_buffs[i].Reset();
    _buffManager.CreateFromData( _buffs, BodyStatusType_Max );
	_buffManager.UpdateEffect();

    m_xTimer[ AiDefine::AiTimer_Thinking ].StartTimer( HQ_TimeGetTime(), 1000 );
    m_xTimer[ AiDefine::AiTimer_Move ].StartTimer( HQ_TimeGetTime(), AiDefine::VerifyPointSpaceTime );

    _blIsFindParthConfig = false;
    _blIsDynamicBlockConfig = false;
	m_bKeepAttackTimeFlag = true;

	m_mapPlayerScore.clear();
}

AiCharacter::~AiCharacter()
{
    ReleaseAiTask();
}

void AiCharacter::ReleaseAiTask()
{
    for ( AiTaskVectorIter iter = m_vecAiTask.begin(); iter != m_vecAiTask.end(); ++iter )
    {
        ( *iter )->Release();
    }

    m_vecAiTask.clear();
}


bool AiCharacter::ProcessMsg( Msg* pMessage )
{
    // 如果接到了自己被销毁，那就再也不能执行任何任务
    switch ( pMessage->GetType() )
    {
    case MSG_EXIT:
        {
            OnExit( pMessage );
            return false;
        }
        break;
    default:
        break;
    }

    return true;
}

void AiCharacter::OnExit( Msg* pMessage, uint8 nExitType )
{
	// 从巡逻组中删除
	GetMonsterGroupLogic().OnMonsterDie();

    // 确保附近有玩家才发送,以提高性能
    if ( HaveAreaPlayer() )
    { GettheServer().SendMsgToView( pMessage, GetID(), false ); }

    // 从场景中删掉
    theGameWorld.OnDelCharacter( GetID() ); 

    // 从释放回内存池
    theRunTimeData.ReleaseObject( GetID() , __FILE__, __LINE__); 
}

void AiCharacter::ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue )
{
    bContinue = true;

    m_dwProcessLogicCostTime += dwCostTime; // 累积时间 有的地方不是每个逻辑帧都调用的
    m_ExtendStatus.Process();
    switch ( GetStatus() )
    {
    case CS_IDLE:
        StatusActionIdle();
        break;
    case CS_ATTACK:// 角色处在攻击的状态
        StatusActionAttack();
        break;
    case CS_HOLDSKILL:// 持续技能
        StatusActionHoldSkill();
        break;
    case CS_INTONATE:// 吟唱
        StatusActionIntonate();
        break;
    case CS_HURT:
        break;
    case CS_DIEING:// 死亡状态，用于等待重生
        StatusActionDieing();
        break;
    default:
        break;
    }

    if( !IsDead() )
    { // 非死亡状态
        // 且距上次检查有1秒的间隔
        if( GameTime::IsPassCurrentTime( m_dwLastRefreshCharDataTime, CHAR_REFRESHTIME ) )
        {    
            m_dwLastRefreshCharDataTime = HQ_TimeGetTime();
            RefreshCharData( m_dwProcessLogicCostTime );
            m_dwProcessLogicCostTime = 0;
        }
    }
}

void AiCharacter::InitRoute( uint32 nMapID, int nRouteID )
{
    // 路点信息
    if ( nRouteID == -1 )
    { return; }

    m_pRoute = theRouteManager.GetRouteInfo( EctypeId2MapId( nMapID ), nRouteID );
    if ( m_pRoute != NULL )
    {
        SetAiStatus( AiDefine::ThinkingMoveToRoute );
        m_nRouteStep = 0;
        SetMoveRoutePoint();
    }
}

void AiCharacter::Run( uint32 nCostTime )
{
    // 如果怪物要死亡, 则不执行下面Ai
    if ( !ProcessDisappear() )
    {
        // 处理怪物AI逻辑
        ProcessAiLogic( nCostTime );

        // 处理复活
        ProcessAiRelive();
    }

    // 处理基类
    BaseCharacter::Run( nCostTime );
}

void AiCharacter::ProcessAiLogic( uint32 nCostTime )
{
    if ( IsDead() )
    { return; }

    uint32 nCurrentTime = HQ_TimeGetTime();

    // 刷新仇恨
    ProcessRefreshEnmity( nCurrentTime );

    // 处理中了状态结果
    ProcessBufferStatus();

    // 获得攻击目标
    ProcessFindAttackTarget();

    // 处理怪物AI思考
    ProcessAiThinking( nCurrentTime );

    // 处理lua脚本执行
    ProcessLuaRunThinking();

    // 处理怪物移动
    ProcessAiMoving( nCostTime );

    // 处理怪物Task任务
    ProcessAiTask();

    // 处理怪物脱离战斗后视野变化
    ProcessIdleViewSightChange();

    // 处理怪物回血, 回魔
    ProcessRestore( nCurrentTime );
}

void AiCharacter::ProcessBufferStatus()
{
    // 如果中了随即乱跑的状态
    if ( _buffManager.IsRandRun() )
    { return SetAiStatus( AiDefine::ThinkingRandRun ); }
}

void AiCharacter::ProcessAiRelive()
{
    if ( !m_xTimer[ AiDefine::AiTimer_Relive ].DoneTimer() )
    { return; }

    SetStatus( CS_IDLE );
    SetDead( false );

    SetHP( GetHPMax() );
    SetMP( GetMPMax() );

    // 清空人物身上的状态
    bool bResult = _buffManager.UpdateOnDead();
    if ( bResult )
    {
        _buffManager.ApplyBuffsToChar( GetProfession(), GetCharBaseAttr(), GetCharFightAttr() );  
        SendBuffChanged( NULL );
    }

	

	/*MsgExitMySight exitplayersight;
	exitplayersight.header.stID = GetID();
	GettheServer().SendMsgToView( &exitplayersight, GetID(), false );*/

	if (IsFightNpc() && _HAS_FLAG(m_dwFightFlag, eFighting)) //战斗npc复活的时候 清除战斗状态，不然等直接进入战斗的时候，战斗状态不发送客户端
	{
		_CLS_FLAG(m_dwFightFlag, eFighting);
	}

    MsgCharAttrChanged Change;
    Change.iChangeCount = 0;
    Change.header.stID = GetID();
    Change.AddAttrShortChange( CharAttr_Relive, false );
    Change.AddAttrIntChange( CharAttr_HP, GetHP() );
    Change.CaluLength();
    GettheServer().SendMsgToView( &Change, GetID(), false );

    // 没有路点的怪, 拉到出生点
    if ( !NeedMoveToNextRoute() )
    {
        SetFloatXF( m_xBornPoint.x );
        SetFloatYF( m_xBornPoint.y );
        SetDir( GetBornDir() );

        SendVerifyPointMessage();
    }

	SetAiStatus( AiDefine::ThinkingMoveToLastIdle );
}

bool AiCharacter::ProcessDisappear()
{
    if ( !m_xTimer[ AiDefine::AiTimer_Disappear ].DoneTimer() )
    { return false; }

    CharacterMurder();
    return true;
}

void AiCharacter::ProcessRefreshEnmity( uint32 nCurrentTime )
{
    if ( !m_xRefeshEnmityTimer.DoneTimer( nCurrentTime ) )
    { return; }
    
    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        // 上一次的仇恨值
        //int nLastEnimty = iter->second.GetEnmity();

        // 仇恨衰减
        BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( iter->first );

#ifdef _DEBUG
        // 去掉战斗NPC和怪物之间的打斗 方便战斗测试
        if ( (IsNpc() && !IsFightNpc())||( pTarget != NULL && pTarget->IsNpc() && !pTarget->IsFightNpc())  )
        { continue; }
#endif // _DEBUG

        if ( pTarget == NULL || pTarget->IsDead() || !CheckInMaxAttackRange( pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY(), 0 ) )
        { // 死亡以后, 如果有仇恨则清除之..
            iter->second.ClearEnmity();
			if (pTarget)
			{
				GetMonsterGroupLogic().OnClearTargetEnmity( pTarget->GetID() );
			}

        }
        else
        {
            // 仇恨衰减
            //iter->second.DecEnmity( iter->second.GetReduction() );

            // 处理怪物的视野仇恨
            ProcessViewEnmity( iter->second, pTarget );
        }

        // 处理仇恨衰减后, 如果没有仇恨了, 要清楚攻击角色列表
        if ( !iter->second.HaveEnmity() )
        { ProcessClearEnmityResult( iter->first ); }
    }

    // 刷新前存在仇恨, 刷新后没有仇恨, 脱离战斗状态
    if ( HaveFighteFlag( eFighting ) && !HaveEnmity() )
    { ProcessEndAttackStatus(); }
}

bool AiCharacter::CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar )
{
    // 大于视野仇恨
    if ( xEnmityData.GetEnmity() >= GetViewEnmity() )
    { return false; }

    if ( !CheckCanAttackTarget( pChar ) )
    { return false; }

    int nViewSightDis   = ( GetLevel() - pChar->GetLevel() ) * ENMITY_RATE;
    int nViewSight      = GetViewSight() + nViewSightDis;

    if ( nViewSight < AiDefine::MinEnmityViewSight )
    { nViewSight = AiDefine::MinEnmityViewSight; }

    return pChar->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), nViewSight );
}

void AiCharacter::ProcessViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar )
{
    if ( !CheckAddViewEnmity( xEnmityData, pChar ) )
    { return; }

    xEnmityData.SetEnmity( GetViewEnmity() );
    xEnmityData.SetReduction( xEnmityData.GetEnmity() * GetEnmityRate() / AiDefine::EnmityBaseRate );
}

void AiCharacter::ProcessEndAttackStatus()
{
    // 改变状态
    SetStatus( CS_IDLE );

    // 清除锁定目标
    ClearLockID();

    // 清除仇恨 
    ClearEnmity( false ); //先改成不清除，防止主动怪和战斗NPC你再次进入他们的视野不攻击你的情况 lrt

    // 清除战绩
    ClearAllAttackerScore();

    // 离开战斗状态
    TryChangeFightState ( false, eFighting );

    // 2秒后恢复普通视野
    StartIdleViewTimer  ( HQ_TimeGetTime() );

    // 开始回血
    StartRestoreTimer   ( HQ_TimeGetTime() ); 

    // 改变Ai状态
    SetAiStatus( AiDefine::ThinkingMoveToLastIdle );

    // 清除Ai变量
    ClearAiVariable();

	// 巡逻组脱离战斗逻辑
	GetMonsterGroupLogic().OnMemberLeaveFight();
}

void AiCharacter::ClearAiVariable()
{
    memset( m_nParamValue, 0, sizeof( m_nParamValue ) );

    for ( int i=0; i<AiDefine::LuaTimerCount; ++i )
    { m_xLuaTimer[i].StopTimer(); }
}

void AiCharacter::ProcessLockTarget( int nTargetID )
{
    if ( nTargetID == InvalidGameObjectId )
    { return; }

    // 在跑回出生点的时候, 不锁定新目标
    //if ( GetAiStatus() == MonsterDefine::ThinkingMoveToBorn )
    //{  return; }

    SetLockID( nTargetID );
    SetAiStatus( AiDefine::ThinkingAttackTarget );
}

void AiCharacter::ProcessClearEnmityResult( GameObjectId nTargetID )
{
    if ( nTargetID == InvalidGameObjectId )
    { return; }

    if ( GetLockID() == nTargetID )
    { ClearLockID(); }

    // 删除自己的攻击目标列表
    RemoveAttackTarget( nTargetID );
}

bool AiCharacter::HaveMoveAbility()
{
    if ( GetAttackMoveSpeed() <= 0.001f )
    { return false; }

    return CheckCanAiMoving();
}

bool AiCharacter::CheckCanAiMoving()
{
    if ( GetStatus() == CS_INTONATE || GetStatus() == CS_HOLDSKILL )
    { return false; }

    if ( !_buffManager.IsCanMove() || IsDead() )
    { return false; }

    switch ( GetAiStatus() )
    {
    case AiDefine::ThinkingStopToTalk:
    case AiDefine::ThinkingIdle:
        return false;
        break;
    default:
        break;
    }

    return true;
}

void AiCharacter::ProcessAiMoving( uint32 nCostTime )
{
    if ( !CheckCanAiMoving() )
    { ClearMoveTargetPoint(); }

    // 前面thinking中会设置一个移动的目标点, 这里只处理移动
    if ( NeedMovingToTargetPoint() )
    { 
		if ( GetAiStatus() == AiDefine::ThinkingMoveToBorn )// lrt 如果是要回到出生点，但位置有不是出生点，这样就有可能使怪物停止某个地方不动，主动怪也不会主动攻击
		{													// 在这里把目标位置设置为出生点（这样可以解决不回去问题，但哪里导致的位置错误没找到，先这样）
			if ( abs( m_xMoveTargetPoint.x - m_xBornPoint.x) > 1.0 || abs( m_xMoveTargetPoint.y - m_xBornPoint.y) > 1.0 )
			{
				ProcessAttackMoveSpeed( 1.5f );
				m_xMoveTargetPoint.x = m_xBornPoint.x;
				m_xMoveTargetPoint.y = m_xBornPoint.y;
			}
		}
        // 怪物需要移动, 设置怪物的新坐标    
        D3DXVECTOR3 vecDistance( m_xMoveTargetPoint.x - GetFloatX(), m_xMoveTargetPoint.y - GetFloatY(), 0/*m_xMoveTargetPoint.z - GetFloatZ()*/ );
        float fDist = D3DXVec3Length( &vecDistance );

        D3DXVECTOR3 vDir;
        D3DXVec3Normalize( &vDir, &vecDistance );

        bool bMoveArrive = false;
        float fActualMoveDist = GetMoveSpeed() * ( 0.001f * static_cast< float >( nCostTime ) );

        if( fActualMoveDist >= fDist )
        {   // 到了, 就清除移动目标点
            fActualMoveDist = fDist; 
            bMoveArrive = true;
        }
        else
        {
            // 路径怪移动时候, 如果小于1.0f就任务已经到了, 否则怪物会卡一下
            switch ( GetAiStatus() )
            {
            case AiDefine::ThinkingMoveToLastIdle:
            case AiDefine::ThinkingMoveToRoute:
                {
                    if ( fDist < 1.0f )
                    { bMoveArrive = true; }
                }
                break;
            }
        }

        SetDirX( vDir.x );
        SetDirY( vDir.y );
        SetFloatXF( GetFloatX() + fActualMoveDist * vDir.x );
        SetFloatYF( GetFloatY() + fActualMoveDist * vDir.y );

		// 设置新位置后需要调用的寻路接口 寻路内部维护状态,无需判断是否在战斗状态
        AfterMoveToPos();

        // 处理到达目的点状态改变( 放在最后处理, 可能需要改变朝向等... )
        if ( bMoveArrive )
        {
			// 到达目标点需要掉用的寻路接口 寻路内部维护状态,无需判断是否在战斗状态
			CheckReachPos();
			ProcessMoveArriveResult();
		}
    }

    // 每2秒同步一次
    if ( !m_xTimer[ AiDefine::AiTimer_Move ].DoneTimer( HQ_TimeGetTime() ) )
    { return; }

    // 刷新区块
    theGameWorld.OnRefreshNewArea( GetID() );

    // 周围没有玩家就不发送消息了
    if ( !HaveAreaPlayer() )
    { return; }

    // 发送同步消息, 4秒一次, 
    if ( !m_bNeedVerifyPoint )
    {   // 上面定时器是2秒执行一次, 所以下面要4秒才执行一次
        m_bNeedVerifyPoint = true;
        return; 
    }

    m_bNeedVerifyPoint = false;

    if ( NeedMovingToTargetPoint() )
    { 
        // 移动的时候, 只发送移动消息 
        SendMoveToTargetPointMessage(); 
    }
    else
    {
        // 移动消息频率 更新用 比如GateServer热启后需要同步怪物位置信息
        SendVerifyPointMessage();
    }
}

void AiCharacter::ProcessMoveArriveResult()
{
    ClearMoveTargetPoint();
    m_xTimer[ AiDefine::AiTimer_Move ].SetSpaceTime( AiDefine::VerifyPointSpaceTime );

    switch ( m_nAiStatus )
    {
    case AiDefine::ThinkingMoveToLastIdle:
        {
            ClearLastIdlePoint();
            SetAiStatus( AiDefine::ThinkingMoveToRoute );  

			GetMonsterGroupLogic().OnArrivePos();
        }
        break;
    case AiDefine::ThinkingMoveToTarget:
        {
            SetVerifyPointAtOnce(); // 马上更新一次坐标
            SetAiStatus( AiDefine::ThinkingAttackTarget );
        }
        break;
    case AiDefine::ThinkingMoveToRoute:
        {
            ProcessArriveRoute();
        }
        break;
    case AiDefine::ThinkingMoveToBorn:
        {
            SetAiStatus( AiDefine::ThinkingMoveAround );
            SetDirectiron( GetBornDir() );

			GetMonsterGroupLogic().OnArrivePos();
        }
        break;
    case AiDefine::ThinkingMoveToPoint:
        {
            SetVerifyPointAtOnce(); // 马上更新一次坐标
            SetAiStatus( AiDefine::ThinkingMoveToPoint );
        }
        break;
    case AiDefine::ThinkingRandRun:
        {
            // 随即乱跑到达后, 马上思考下一个点
            m_xTimer[ AiDefine::AiTimer_Thinking ].NextTimer( 1 );
        }
        break;
	case AiDefine::ThinkingDoNothing:
		{
			GetMonsterGroupLogic().OnArrivePos();
		}
		break;
    default:
        break;
    }
}

void AiCharacter::ProcessArriveRoute()
{
    if ( m_pRoute == NULL )
    { return; }

    // 设置怪物的可移动范围
    m_xCanMoveZone.left   = FloatToTile( GetFloatX() ) - AiDefine::MonsterMoveRadius;
    m_xCanMoveZone.right  = FloatToTile( GetFloatX() ) + AiDefine::MonsterMoveRadius;
    m_xCanMoveZone.top    = FloatToTile( GetFloatY() ) - AiDefine::MonsterMoveRadius;
    m_xCanMoveZone.bottom = FloatToTile( GetFloatY() ) + AiDefine::MonsterMoveRadius;

    // 同时设置怪物在该坐标点出生
    SetBornPoint( GetFloatX(), GetFloatY(), 0 );

    // 移动到下一个路点
    ++m_nRouteStep;

    SetMoveRoutePoint();
}

void AiCharacter::SetMoveRoutePoint()
{
    if ( m_nRouteStep < 0 )
    { return SetAiStatus( AiDefine::ThinkingMoveAround ); }

    if (m_xTimer[ AiDefine::AiTimer_RouteMove ].IsStart() && !m_xTimer[ AiDefine::AiTimer_RouteMove ].DoneTimer() )
    { return; }

	// 巡逻组等待其他成员到位
	if ( GetMonsterGroupLogic().CanMoveOn() == false )
	{ return; }

    // 到达路点后, 设置路点信息
    if ( m_nRouteStep >= m_pRoute->allMovePos.size() )
    {
        if ( m_pRoute->nextRouteId == -1 )
        { 
            m_nRouteStep = -1;
            return SetAiStatus( AiDefine::ThinkingMoveAround );
        }

        m_pRoute = theRouteManager.GetRouteInfo( m_pRoute->nextMapId, m_pRoute->nextRouteId );
        if ( m_pRoute == NULL )
        {
            m_nRouteStep = -1;
            return SetAiStatus( AiDefine::ThinkingMoveAround );
        }

        // 下一个路点继续
        if ( m_pRoute->allMovePos.empty() )
        {
            LogMessage::LogSystemError( "RouteError:AiChar路点Id[%d] CharId[%d] CharName[%s]", m_pRoute->routeId, GetID(), GetCharName() );
            m_nRouteStep = -1;
            return SetAiStatus( AiDefine::ThinkingMoveAround );
        }

        m_nRouteStep = 0;
    }

    // 设置下一个路点目标
    SMovePos& xMovePos = m_pRoute->allMovePos.at( m_nRouteStep );

    SetMoveTargetPoint( xMovePos.fX, xMovePos.fY, 0 );

    if( xMovePos.fV != GetMoveSpeed() )
    { ChangeMoveSpeed( xMovePos.fV ); } 

    SetMoveStep( xMovePos.fStep );

	// 巡逻组逻辑
	GetMonsterGroupLogic().OnMonsterMoveToPos( D3DXVECTOR3( xMovePos.fX, xMovePos.fY, 0 ) );

    // 路点动作
    if ( strlen( xMovePos.szActionName ) >= 1 )
    {
        MsgNpcPlayAnim msg;
        msg.header.stID = GetID();
        msg.nNpcId      = GetID();
        HelperFunc::SafeNCpy( msg.szActionName,  xMovePos.szActionName , MsgNpcPlayAnim::eActionNameLength );
        HelperFunc::SafeNCpy( msg.szEndActionName, "idle", MsgNpcPlayAnim::eActionNameLength );
        msg.nLoopTimes = 1;
        GettheServer().SendMsgToView( &msg, GetID(), true );
    }

    // 场景
    if ( xMovePos.stSceneId > 0  )
    {
        MsgScenePlay  msgScene;
        msgScene.header.stID = GetID();
        msgScene.stSceneId   = xMovePos.stSceneId;
        GettheServer().SendMsgToView( &msgScene, GetID(), true );
    }

    // 停止移动
    if ( xMovePos.dwTime > 0 )
    { 
        m_xTimer[ AiDefine::AiTimer_RouteMove ].StartTimer( HQ_TimeGetTime(), xMovePos.dwTime ); 
        return;
    }
}

void AiCharacter::SetMoveTargetPoint( float fX, float fY, float fZ )
{
    m_xMoveTargetPoint.x = fX;
    m_xMoveTargetPoint.y = fY;
    m_xMoveTargetPoint.z = WORLD_HEIGHT;

    // 先发送目标点给客户端处理, 使怪物平滑的移动
    switch ( GetAiStatus() )
    {
    case AiDefine::ThinkingMoveToTarget:
        SendClosingToTargetMessage();
        break;
    default:
        SendMoveToTargetPointMessage();
        break;
    }
}

void AiCharacter::SetMovePoint( float fX, float fY, float fZ )
{
    m_xMovePoint.x = fX;
    m_xMovePoint.y = fY;
    m_xMovePoint.z = WORLD_HEIGHT;
}

void AiCharacter::SendMoveToTargetPointMessage( GamePlayer* pTarget /* = NULL */ )
{
    MsgUnPlayerMovingToPos xMoveTo;                    
    xMoveTo.header.stID = GetID();
    xMoveTo.vStartPos.x = GetFloatX();
    xMoveTo.vStartPos.y = GetFloatY();
    xMoveTo.vStartPos.z = WORLD_HEIGHT;
    xMoveTo.vEndPos     = m_xMoveTargetPoint;
    if ( pTarget == NULL )
    { GettheServer().SendMsgToView( &xMoveTo, GetID(), true ); }
    else
    { pTarget->SendMessageToClient( &xMoveTo ); }
}

void AiCharacter::SendVerifyPointMessage()
{
    MsgUnPlayerVerifyPos xVerifyPoint;

    xVerifyPoint.SetLevel(level_normal); // 在这里设置中等优先级
    xVerifyPoint.header.stID = GetID();
    xVerifyPoint.vPos.x      = GetFloatX();
    xVerifyPoint.vPos.y      = GetFloatY();
    xVerifyPoint.vPos.z      = 0;
    xVerifyPoint.chDirX      = (char)(GetDirX()*127);
    xVerifyPoint.chDirY      = (char)(GetDirY()*127);
    xVerifyPoint.chDirZ      = 0;
    GettheServer().SendMsgToView( &xVerifyPoint, GetID(), true );
}

void AiCharacter::SendClosingToTargetMessage()
{
    D3DXVECTOR3 vCusPos( GetFloatX(), GetFloatY(), WORLD_HEIGHT );                                

    MsgUnPlayerClosingToLockTarget xMsg;
    xMsg.header.stID  = GetID();
    xMsg.LockTargetID = GetLockID();
    xMsg.vPos         = vCusPos;
    GettheServer().SendMsgToView( &xMsg, GetID(), true );
}

void AiCharacter::ChangeMoveSpeed( float fValue )
{
    SetMoveSpeed( fValue );
    SetLastMovingSpeed ( fValue );
    ChangeAttr( CharAttr_MoveSpeed, fValue );
}

void AiCharacter::ProcessIdleViewSightChange()
{
    // 脱离战斗,2秒后恢复怪物的空闲视野范围大小
    if ( !m_xTimer[ AiDefine::AiTimer_IdleView ].DoneTimer() )
    { return; }

    SetViewSight( GetIdleViewSight() );
}

int AiCharacter::GetThinkingSpaceTime()
{
    // 普通怪物思考时间1000ms
    return GetThinkingTime() + theRand.rand16() % AiDefine::MonsterThinkTime;
}

uint8 AiCharacter::ThinkingAttackTarget( uint32 nCurrentTime )
{
    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( GetLockID() );
    if ( pTarget == NULL || pTarget->IsDead() || !CheckCanAttackTarget(pTarget) || !CheckInMaxAttackRange( pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY(), 0 ) )
    { return ProcessLostLockTarget( pTarget ); }

    // 得到要使用的技能 CheckUseSkillPreconditionState 放在下面判断, 否则追击的时候会慢一拍, 效果不好
    const AiSkill* pAiSkill = GetCanUseSkill( nCurrentTime );
    if ( pAiSkill == NULL )
    { return AiDefine::ThinkingDoNothing; }

	uint8 nState = AiDefine::ThinkingAttackTarget;
    // 不在攻击范围内, 先移动到攻击范围内
    if ( !CheckCanAttackTargetDistance( pTarget, pAiSkill->GetID(), pAiSkill->GetLevel() ) )
    {
        // 有移动能力, 向目标移动
        if ( HaveMoveAbility() )
        { 
            SetThinkingSpaceTime( AiDefine::BaseThinkTime );

			// 追击目标,设置寻路
			_charFindParth.ReInitFindParth( _blIsFindParthConfig, _blIsDynamicBlockConfig );

            nState = AiDefine::ThinkingMoveToTarget; 
        }
		else
		{ nState = AiDefine::ThinkingDoNothing; }
    }

    // 是否能使用技能状态( 
    if( !CheckUseSkillPreconditionState() )
    { nState = AiDefine::ThinkingDoNothing; }

    // 处理尝试攻击目标( 改变战斗状态等... )
    ProcessTryAttackTarget( pTarget );

    // 有移动能力需要改变朝向
    if ( HaveMoveAbility() )
    { ProcessChangeDirToTarget();  }

    return nState;
}

// 是否在攻击范围内
bool AiCharacter::CheckCanAttackTargetDistance( BaseCharacter* pTarget, int nSkillID, int nSkillLevel )
{
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( nSkillID, nSkillLevel );
    if ( pSkill == NULL )
    { return false; }

    float fRangeCorrect = monsterCastCorrect;
    if ( pSkill->fRangeCanCast == 0.f )
    { fRangeCorrect = 0.1f; }

    return IsInAttackRange( pTarget, pSkill, fRangeCorrect );
}

void AiCharacter::ProcessTryAttackTarget( BaseCharacter* pTarget )
{
    // 改变战斗状态
    TryChangeFightState( true, eFighting );

    // 切换到战斗视野
    SetViewSight( GetFightViewSight() );

    // 给对方设置一个仇恨( 只有目标是玩家才这么做 )
    if ( pTarget->IsPlayer() )
    {
        EnmityData* pEnmityData = pTarget->GetEnmity( GetID() );
        if ( pEnmityData == NULL || pEnmityData->GetEnmity() < GetViewEnmity() )
        { pTarget->SetEnmity( GetID(),  GetViewEnmity(), GetEnmityRate() ); }
    }

    // 如果是有路点, 保存当前位置
    if ( NeedMoveToNextRoute() && !NeedMoveToLastIdlePoint() )
    { SetLastIdlePoint( GetFloatX(), GetFloatY(), 0.0f ); }
}

bool AiCharacter::CheckCanUseSkill( uint16 nSkillID )
{
    if ( IsNormalAttack( nSkillID ) )
    { return _buffManager.IsCanUsePhysicsSkill(); }

    return _buffManager.IsCanUseMagicSkill();
}

AiSkill* AiCharacter::GetCanUseSkill( uint32 nCurrentTime )
{
    // 已经在执行Ai
    if ( !_SkillTaskManager.IsTaskEmpty() && !m_vecAiTask.empty() )
    { return NULL; }

    AiSkill* pAiSkill = GetAiSkillByIndex( GetUseSkillIndex() );
    if ( pAiSkill != NULL ) // 已经有使用的技能
    {
        if ( CheckCanUseSkill( pAiSkill->GetID() ) )
        { return pAiSkill; }
    }

    // 清除掉原来设定的技能
    SetUseSkillIndex( -1 );

    // 没有重新找技能
    std::vector< int > vecCanUseSkill( 0 );

    // 找到可以使用的技能索引
    for ( int i = 0; i < AiDefine::MonsterMaxSkillCount; ++i )
    {
        if ( !m_xAiSkill[ i ].CanUseAiSkill( GetHP(), GetMP() ) )
        { continue; }

        if ( !CheckCanUseSkill( m_xAiSkill[ i ].GetID() ) )
        { continue; }

        vecCanUseSkill.push_back( i );
    }

    // 有几个可用技能就随机几次
    for ( int i = 0; i < vecCanUseSkill.size(); ++i )
    {
		int nRandNumber = 0;
		if (m_nUseSkillTotalRate != 0)
		{
			nRandNumber = theRand.rand16() % m_nUseSkillTotalRate;
		}
        for ( std::vector< int >::iterator iter = vecCanUseSkill.begin(); iter != vecCanUseSkill.end(); ++iter )
        {
            pAiSkill = GetAiSkillByIndex( *iter );
            if ( pAiSkill->GetUseRate() < nRandNumber )
            { 
                SetUseSkillIndex( *iter );
                return pAiSkill;
            }
        }
    }

    return NULL;
}

uint8 AiCharacter::ProcessLostLockTarget( BaseCharacter* pTarget )
{
    // 目标不存在或者距离过远, 删除仇恨列表
    //RemoveEnmity( GetLockID() ); //lrt 防止再次进入视野不会攻击 改成下面2句，只清掉仇恨值和攻击目标，不删除仇恨列表
	SetEnmity( GetLockID(), 0 );
	RemoveAttackTarget( GetLockID() );

	GetMonsterGroupLogic().OnClearTargetEnmity( GetLockID() );

    ClearLockID();
    ClearMoveTargetPoint();

    if ( NeedMoveToNextRoute() )
    { SetAiStatus( AiDefine::ThinkingMoveToLastIdle ); }
    else
    { SetAiStatus( AiDefine::ThinkingMoveToBorn ); }

	// 清除寻路
	_charFindParth.ReInitFindParth( false, false );

    return AiDefine::ThinkingDoNothing;
}

uint8 AiCharacter::ThinkingMoveToTarget()
{
    // 自己不在范围内
    if ( !CheckInMaxAttackRange( GetMapID(), GetFloatX(), GetFloatY(), 0 ) )
    { return ProcessLostLockTarget( NULL ); }

    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( GetLockID() );
    if ( pTarget == NULL || !CheckInMaxAttackRange( pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY(), 0 ) )
    { return ProcessLostLockTarget( pTarget ); }

    // 已经在移动
    if ( NeedMovingToTargetPoint() )
    { return AiDefine::ThinkingDoNothing; }

    return AiDefine::ThinkingMoveToTarget;
}

int AiCharacter::GetMinDistanceAttackTarget()
{
    int nMinDistanceCharID = InvalidGameObjectId;
    float fMinDistance = 100000.f;
	BaseCharacter* pChar =  NULL;
    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        if ( !iter->second.HaveEnmity() )
        { continue; }

        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( iter->first );
        if ( pChar == NULL || pChar->IsDead() )
        { continue; }

        D3DXVECTOR3 vecDistance( pChar->GetFloatX() - GetFloatX(), pChar->GetFloatY() - GetFloatY(), 0 );
        float fDistance = D3DXVec3Length( &vecDistance );
        if ( fDistance < fMinDistance )
        {
			pChar = theRunTimeData.GetCharacterByID(iter->first);
			if (pChar&&!pChar->IsDead())
			{
				fMinDistance     = fDistance;
				nMinDistanceCharID = iter->first;
			}
        }
		pChar = NULL;
    }

    return nMinDistanceCharID;
}

int AiCharacter::GetMaxEnmityAttackTarget()
{
    int nMaxEnmityCharID = InvalidGameObjectId;
    int nMaxEnmityValue = 0;
	BaseCharacter* pChar =  NULL;
    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        if ( !iter->second.HaveEnmity() || iter->second.GetDamage() == 0 )
        { continue; }
		
        // 获得仇恨最大的角色,已经有锁定目标时, 并且有伤害过我, 否则不轻易换攻击目标
        if ( iter->second.GetEnmity() > nMaxEnmityValue )
        {
			pChar = theRunTimeData.GetCharacterByID(iter->first);
			if (pChar&&!pChar->IsDead())
			{//要能找到目标角色指针，and目标没死才设置为目标
				nMaxEnmityValue  = iter->second.GetEnmity();
				nMaxEnmityCharID = iter->first;
			}
        }
		pChar = NULL;
    }
	
    return nMaxEnmityCharID;
}

void AiCharacter::ProcessFindAttackTarget()
{
    switch ( GetAiStatus() )
    {
    case AiDefine::ThinkingMoveToBorn:
    case AiDefine::ThinkingWaitRelive:
    case AiDefine::ThinkingMoveToPoint:
    case AiDefine::ThinkingRandRun:
        { return; }
        break;
    }

    // 没有仇恨直接返回
    int nLockID = InvalidGameObjectId;
    if ( !HaveLockTarget() )
    {
        // 没有锁定目标时, 找最近的目标
        nLockID = GetMinDistanceAttackTarget();
    }
    else
    {
        // 有锁定目标时, 找攻击我的, 并且仇恨最大的
        nLockID = GetMaxEnmityAttackTarget();
    }

    // 锁定目标
    ProcessLockTarget( nLockID );
}

uint8 AiCharacter::ThinkingMoveToBorn()
{
    // 已经在移动了
    if ( NeedMovingToTargetPoint() )
    { return AiDefine::ThinkingDoNothing; }

    return AiDefine::ThinkingMoveToBorn;
}

uint8 AiCharacter::ThinkingMoveToLastIdle()
{
    if ( !NeedMoveToLastIdlePoint() )
    { 
        SetAiStatus( AiDefine::ThinkingMoveToRoute );
        return AiDefine::ThinkingDoNothing; 
    }

    if ( NeedMovingToTargetPoint() )
    { return AiDefine::ThinkingDoNothing; }

    return AiDefine::ThinkingMoveToLastIdle;
}

uint8 AiCharacter::ThinkingMoveToRoute()
{
    if ( !NeedMoveToNextRoute() )
    { 
        SetAiStatus( AiDefine::ThinkingMoveToBorn );
        return AiDefine::ThinkingDoNothing; 
    }

    if ( NeedMovingToTargetPoint() )
    { return AiDefine::ThinkingDoNothing; }

    return AiDefine::ThinkingMoveToRoute;
}

uint8 AiCharacter::ThinkingMoveToPoint()
{
    if ( m_xMovePoint.x == 0.0f )
    {
        SetAiStatus( AiDefine::ThinkingMoveAround );
        return AiDefine::ThinkingDoNothing; 
    }

    if ( NeedMovingToTargetPoint() )
    { return AiDefine::ThinkingDoNothing; }
    
    D3DXVECTOR3 vTargetPos( m_xMovePoint.x , m_xMovePoint.y,0 );
    D3DXVECTOR3 vCurPos    = GetPos();

    // 只判断平面位置
    D3DXVECTOR3 vecDistance( vTargetPos.x - vCurPos.x, vTargetPos.y - vCurPos.y, 0 );

    // 到达目标点
    if ( D3DXVec3Length( &vecDistance ) <= 1 )
    {
        SetMovePoint( 0.0f, 0.0f, 0.0f );
        return AiDefine::ThinkingDoNothing;
    }

    return AiDefine::ThinkingMoveToPoint;
}

uint8 AiCharacter::ThinkingMoveAround()
{
    // 周围没有玩家..不走动, 省消息
    if ( !HaveAreaPlayer() )
    { return AiDefine::ThinkingDoNothing; }

    // 在自己活动范围内, 随即移动
    if ( !HaveMoveAbility() )
    { return AiDefine::ThinkingDoNothing; }

    // 判断移动概率
    int nRandIdleMoveRate = theRand.rand16() % AiDefine::MonsterIdleMoveRand;
    if ( nRandIdleMoveRate >= GetIdleMoveRate() )
    { return AiDefine::ThinkingDoNothing; }

    return AiDefine::ThinkingMoveAround;
}

uint8 AiCharacter::ThinkingStopToTalk()
{
    if ( !m_xTimer[ AiDefine::AiTimer_Talk ].DoneTimer() )
    { return AiDefine::ThinkingStopToTalk; }

    m_nTalkCount = 0;
    SendMoveToTargetPointMessage();
    return AiDefine::ThinkingMoveToRoute;
}

uint8 AiCharacter::ThinkRandRun()
{
    if ( _buffManager.IsRandRun() )
    { return AiDefine::ThinkingRandRun; }

    ClearMoveTargetPoint();
    return AiDefine::ThinkingAttackTarget;
}

void AiCharacter::ProcessAiThinking( uint32 nCurrentTime )
{   
    if ( !CheckAiThinkingMonsterStatus() )
    { return; }

    // 处理怪物思考, 不需要在每个逻辑帧都思考, 提高性能
    if ( !m_xTimer[ AiDefine::AiTimer_Thinking ].DoneTimer( nCurrentTime ) )
    { return; }

    // 设置下一次思考时间
    SetThinkingSpaceTime( GetThinkingSpaceTime() );

    // 怪物思考
    uint8 nThinkingResult = AiThinking( nCurrentTime );
    switch ( nThinkingResult )
    {
    case AiDefine::ThinkingMoveToBorn:     // 移动到出生点
        ProcessMoveToBornPoint();
        break;
    case AiDefine::ThinkingMoveAround:     // 出生点附近随即移动
        ProcessMoveAround();
        break;
    case AiDefine::ThinkingMoveToTarget:   // 移动到攻击目标点
        ProcessMoveToAttackTarget();
        break;
    case AiDefine::ThinkingAttackTarget:   // 攻击锁定目标
        ProcessAttackTarget();
        break;
    case AiDefine::ThinkingMoveToRoute:
        ProcessMoveToRoute();
        break;
    case AiDefine::ThinkingMoveToLastIdle:
        ProcessMoveToLastIdlePoint();
        break;
    case AiDefine::ThinkingMoveToMaster:
        ProcessMoveToMaster();
        break;
    case AiDefine::ThinkingFollowMaster:
        ProcessFollowMaster();
        break;
    case AiDefine::ThinkingMoveToPoint:
        ProcessMoveToPoint();
        break;
    case AiDefine::ThinkingIdle:
        ProcessIdle();
        break;
    case AiDefine::ThinkingRandRun:
        ProcessRandRun();
        break;
    case AiDefine::ThinkingDoNothing:
        return;
        break;
    }

    SetAiStatus( nThinkingResult );
}

uint8 AiCharacter::AiThinking( uint32 nCurrentTime )
{
    switch ( GetAiStatus() )
    {
    case AiDefine::ThinkingAttackTarget:
        return ThinkingAttackTarget( nCurrentTime );
        break;
    case AiDefine::ThinkingMoveToTarget:
        return ThinkingMoveToTarget();
        break;
    case AiDefine::ThinkingMoveToBorn:
        return ThinkingMoveToBorn();
        break;
    case AiDefine::ThinkingMoveToLastIdle:
        return ThinkingMoveToLastIdle();
        break;
    case AiDefine::ThinkingMoveToRoute:
        return ThinkingMoveToRoute();
        break;
    case AiDefine::ThinkingMoveAround:
        return ThinkingMoveAround();
        break;
    case AiDefine::ThinkingStopToTalk:
        return ThinkingStopToTalk();
        break;
    case AiDefine::ThinkingMoveToPoint:
        return ThinkingMoveToPoint();
        break;
    case AiDefine::ThinkingRandRun:
        return ThinkRandRun();
        break;
    default:
        break;
    }

    return GetAiStatus();
}

void AiCharacter::ProcessAttackMoveSpeed( float fModulus )
{
    // 攻击时, 往回跑时的移动速度
    float fSpeed = GetAttackMoveSpeed() * fModulus;
    if ( abs( GetCharFightAttr()->moveSpeed.base - fSpeed ) < 0.0001 )
    { return; }

    ChangeMoveSpeed( fSpeed ); 
}

void AiCharacter::ProcessIdleMoveSpeed()
{
    // 空闲时移动速度
    float fSpeed = GetIdleMoveSpeed();
    if ( abs( GetCharFightAttr()->moveSpeed.base - fSpeed ) < 0.0001 )
    { return; }

    ChangeMoveSpeed( fSpeed ); 
}

void AiCharacter::ProcessMoveToRoute()
{
    // 已经在移动了
    if ( NeedMovingToTargetPoint() )
    { return; }

    SetMoveRoutePoint();
}

void AiCharacter::ProcessMoveToBornPoint()
{
    ProcessAttackMoveSpeed( 1.5f );

    if ( NeedMovingToTargetPoint() )
    { return; }

    // 将目标点设置成出生点
    SetMoveTargetPoint( m_xBornPoint.x, m_xBornPoint.y, m_xBornPoint.z );
}

void AiCharacter::ProcessMoveToPoint()
{
    ProcessAttackMoveSpeed();

    if ( NeedMovingToTargetPoint() )
    { return; }

    // 将目标点设置成某点
    SetMoveTargetPoint( m_xMovePoint.x, m_xMovePoint.y, m_xMovePoint.z );
}

void AiCharacter::ProcessChangeDirToTarget()
{
    // 找到攻击目标
    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( GetLockID() );
    if ( pTarget == NULL )
    { return; }

    D3DXVECTOR3 vecDistance( pTarget->GetFloatX() - GetFloatX(), pTarget->GetFloatY() - GetFloatY(), 0 );
    float fDistance = D3DXVec3Length( &vecDistance );

    // 方向
    D3DXVECTOR3 vecDir;
    D3DXVec3Normalize( &vecDir, &vecDistance );

    // 朝向改变
    SetDirX( vecDir.x );
    SetDirY( vecDir.y );

    // 立即同步一次位置
    SetVerifyPointAtOnce();
}

void AiCharacter::ProcessMoveToAttackTarget()
{
	DECLARE_TIME_TEST

    ProcessAttackMoveSpeed();

    // 找到攻击目标
    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( GetLockID() );
    if ( pTarget == NULL )
    { return; }

	// 找到技能, 获得攻击距离
	AiSkill* pAiSkill = GetAiSkillByIndex( GetUseSkillIndex() );
	if ( pAiSkill == NULL )
	{ 
        pAiSkill = GetCanUseSkill( HQ_TimeGetTime() );
        if ( pAiSkill == NULL )
        { return; }
    }

	// 寻路 此处 pAiSkill->GetAttackDistance() 如果很大会造成逃跑假象
	D3DXVECTOR3 vecTargetPos( pTarget->GetPos() );
	float fFreeRange = pTarget->GetBodySize() + pAiSkill->GetAttackDistance();	// 技能的攻击记录和目标的体型

	BEGIN_TIME_TEST( "LogicThread FindParth" );
	bool blHasFindParth = FindTheNextPosToMove( vecTargetPos, fFreeRange );
	END_TIME_TEST_1( "LogicThread FindParth", 1 );
	if ( ! blHasFindParth )
	{ return; }

    // 和目标之间的距离
    D3DXVECTOR3 vecDistance( vecTargetPos.x - GetFloatX(), vecTargetPos.y - GetFloatY(), 0 );
    float fDistance = D3DXVec3Length( &vecDistance );

    // 方向
    D3DXVECTOR3 vecDir;
    D3DXVec3Normalize( &vecDir, &vecDistance );

    // 减去技能的攻击记录和目标的体型
    float fRange = fDistance - fFreeRange;

    // 设置目标点
    float fTargetX = GetFloatX() + fRange * vecDir.x;
    float fTargetY = GetFloatY() + fRange * vecDir.y;
    if ( fTargetX != m_xMoveTargetPoint.x || fTargetY != m_xMoveTargetPoint.y )
    { SetMoveTargetPoint( GetFloatX() + fRange * vecDir.x, GetFloatY() + fRange * vecDir.y, 0 ); }

    // 怪物追击时候, 坐标位置1秒同步一次
    m_xTimer[ AiDefine::AiTimer_Move ].SetSpaceTime( AiDefine::VerifyPointSpaceTime / 2 );
}

void AiCharacter::ProcessMoveAround()
{
    ProcessIdleMoveSpeed();

    if ( NeedMovingToTargetPoint() )
    { return; }

    static const int nRoundRange = AiDefine::MonsterMoveRadius * 2;
    // -nRoundRange ~ +nRoundRange
    int nTileX = GetTileX() + theRand.rand16() % ( nRoundRange * 2 ) - nRoundRange;
    int nTileY = GetTileY() + theRand.rand16() % ( nRoundRange * 2 ) - nRoundRange;

    if ( nTileX < m_xCanMoveZone.left )
    { nTileX = m_xCanMoveZone.left; }
    if ( nTileX > m_xCanMoveZone.right )
    { nTileX = m_xCanMoveZone.right; }
    if ( nTileY < m_xCanMoveZone.top )
    { nTileY = m_xCanMoveZone.top; }
    if ( nTileY > m_xCanMoveZone.bottom )
    { nTileY = m_xCanMoveZone.bottom; }

    SetMoveTargetPoint( TileToFloat( nTileX ), TileToFloat( nTileY ), 0 );
}

void AiCharacter::ProcessMoveToLastIdlePoint()
{
    ProcessAttackMoveSpeed( 1.5f );

    if ( NeedMovingToTargetPoint() )
    { return; }

    SetMoveTargetPoint( m_xLastIdlePoint.x, m_xLastIdlePoint.y, m_xLastIdlePoint.z );    
}

void AiCharacter::ProcessIdle ()
{

}

void AiCharacter::ProcessFollowMaster()
{
    // 200设置一次位置, 和客户端算法同步
    ProcessMoveToMaster();
}

void AiCharacter::ProcessMoveToMaster()
{
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster == NULL || pMaster->IsDead() )
    { return CharacterMurder(); }

    ProcessAttackMoveSpeed();

    // 不在同一个地图, 就不跟随
    if ( pMaster->GetMapID() != GetMapID() )
    { return ClearMoveTargetPoint(); }

    if ( IsPet() && GetMoveSpeed() != pMaster->GetMoveSpeed() )
    {
        MonsterPetEx* pMonsterPet = static_cast< MonsterPetEx* > ( this ) ;
        
        ItemDefine::SMonster* pMonsterConfig = pMonsterPet->GetMonsterConfig();
        if ( pMonsterConfig == NULL || IsFloatZero( pMonsterConfig->fMoveSpeed )  )
        { return; }

        pMonsterPet->SetLastMovingSpeed  ( GetMoveSpeed() );

        GetCharFightAttr()->moveSpeed.base = pMaster->GetMoveSpeed();
        GetCharFightAttr()->moveSpeed.UpdateFinal();

        pMonsterPet->SettAttackMoveSpeed ( pMaster->GetMoveSpeed() );
        pMonsterPet->SetIdleMoveSpeed    ( pMaster->GetMoveSpeed() );
    }

    D3DXVECTOR3 vMasterPos = pMaster->GetPos();
    D3DXVECTOR3 vCurPos    = GetPos();

    // 只判断平面位置
    D3DXVECTOR3 vecDistance( vMasterPos.x - vCurPos.x, vMasterPos.y - vCurPos.y, 0 );
    float fDistance = D3DXVec3Length( &vecDistance );

    float distanceBeginFollow = m_fBodySize + pMaster->GetBodySize() + 1.0f;

    //// 开始跟随
    //D3DXVECTOR3 vecDir;
    //D3DXVec3Normalize( &vecDir, &vecDistance );

    // 已经在附近, 不需要跟随了
    if( m_fBodySize < 0 || fDistance <= distanceBeginFollow )
    { 
        return ClearMoveTargetPoint();
    }

    // 镖车超出距离太远, 停止跟随 ( 只有护送怪之类才不跟随了 )
    if ( !IsPet() && fDistance > AiDefine::ProtectCharStopDistance )
    { 
        return ClearMoveTargetPoint(); 
    }

    // 宠物分散在玩家身后120°左右两侧
    const float fAngle = D3DX_PI / 1.5f;
    // 主人朝向
    D3DXVECTOR3 vSummonerDir = D3DXVECTOR3( pMaster->GetDirX(), pMaster->GetDirY(), 0 );
    float fCorrect = pMaster->GetBodySize() + m_fBodySize + 0.5;

    switch ( GetObjType() )
    {
    case Object_MonsterPet:
        vCurPos = GetTargetPos( pMaster->GetPos(), vSummonerDir,  -fAngle, fCorrect);
        break;
    case Object_MonsterNurturePet:
        vCurPos = GetTargetPos( pMaster->GetPos(), vSummonerDir,   fAngle, fCorrect);
        break;
    default:
        vCurPos = GetTargetPos( pMaster->GetPos(), vSummonerDir,  -fAngle, fCorrect);
        break;
    }

    //float fActualDistance = fDistance - distanceBeginFollow;
    //vCurPos.x += fActualDistance * vecDir.x;
    //vCurPos.y += fActualDistance * vecDir.y;

    // 设置移动目标点
    if ( m_xMoveTargetPoint.x != vCurPos.x || m_xMoveTargetPoint.y != vCurPos.y )
    { 
        SetMoveTargetPoint( vCurPos.x, vCurPos.y, 0 );
        // 更新出生点
        SetBornPoint( vCurPos.x, vCurPos.y, 0 );
    }
}

void AiCharacter::ProcessAttackTarget()
{
    AiSkill* pAiSkill = GetAiSkillByIndex( GetUseSkillIndex() );
    if ( pAiSkill == NULL )
    { return; }

    AddAiTask( GetLockID(), pAiSkill->GetID(), pAiSkill->GetLevel() );

    // 技能冷却
    pAiSkill->SetStartColdDownTime( HQ_TimeGetTime() );
    ClearMoveTargetPoint();
}

void AiCharacter::ProcessRandRun()
{
    ProcessAttackMoveSpeed();

    if ( NeedMovingToTargetPoint() )
    { return; }

    static const int nRoundRange = AiDefine::MonsterMoveRadius;
    // -nRoundRange ~ +nRoundRange
    int nTileX = GetTileX() + theRand.rand16() % ( nRoundRange * 2 ) - nRoundRange;
    int nTileY = GetTileY() + theRand.rand16() % ( nRoundRange * 2 ) - nRoundRange;

    if ( nTileX < m_xCanMoveZone.left )
    { nTileX = m_xCanMoveZone.left; }
    if ( nTileX > m_xCanMoveZone.right )
    { nTileX = m_xCanMoveZone.right; }
    if ( nTileY < m_xCanMoveZone.top )
    { nTileY = m_xCanMoveZone.top; }
    if ( nTileY > m_xCanMoveZone.bottom )
    { nTileY = m_xCanMoveZone.bottom; }

    SetMoveTargetPoint( TileToFloat( nTileX ), TileToFloat( nTileY ), 0 );
}

void AiCharacter::StartIdleViewTimer( uint32 nCurrentTime )
{
    m_xTimer[ AiDefine::AiTimer_IdleView ].StartTimer( HQ_TimeGetTime(), 2000 );
}

void AiCharacter::StartRestoreTimer( uint32 nCurrentTime )
{
    // 满血满魔不用回复
    if ( GetHP() == GetHPMax() && GetMP() == GetMPMax() )
    { return; }

    // 怪物不设定回血
    if ( GetRestoreHP() == 0 && GetRestoreMP() == 0 )
    { return; }

    m_xTimer[ AiDefine::AiTimer_Restore ].StartTimer( nCurrentTime, GetRestoreSpaceTime() );
    m_xTimer[ AiDefine::AiTimer_Restore ].NextTimer( 1 ); // 马上回血一次
}

void AiCharacter::ProcessRestore( uint32 nCurrentTime )
{
    // 定时器没开启,或者没到时间则返回
    if ( !m_xTimer[ AiDefine::AiTimer_Restore ].DoneTimer( nCurrentTime ) || 
		GetAiStatus() == AiDefine::ThinkingAttackTarget || GetAiStatus() == AiDefine::ThinkingMoveToTarget ) //战斗中不回血
    { return; }

    uint32 nHP = GetHP() + GetRestoreHP();
    if ( nHP > GetHPMax() )
    { nHP = GetHPMax(); }

    uint32 nMP = GetMP() + GetRestoreMP();
    if ( nMP > GetMPMax() )
    { nMP = GetMPMax(); }

    SetHP( nHP );
    SetMP( nMP );

    if ( HaveAreaPlayer() )
    {
        // 发送属性改变消息. 怪物只显示血条
        ChangeAttr( CharAttr_HP, GetHP() );
    }

    // 恢复满后, 关闭定时器
    if ( GetHP() == GetHPMax() && GetMP() == GetMPMax() )
    { m_xTimer[ AiDefine::AiTimer_Restore ].StopTimer(); }
}

bool AiCharacter::CheckCanAiTask()
{
    if ( GetStatus() == CS_INTONATE || GetStatus() == CS_HOLDSKILL )
    { return false; }

    if ( !_SkillTaskManager.IsCurTaskDone() )
    { return false; }

    return true;
}

void AiCharacter::AddAiTask( GameObjectId nAttackID, uint16 nSkillID, uint8 nSkillLevel, uint8 nTaskPriority )
{
    if ( !CheckCanAiTask() )
    { return; }

    AiTask *pAiTask = AiTask::CreateInstance();
    if ( pAiTask == NULL )
    { return; }

    pAiTask->SetAttackID( nAttackID );
    pAiTask->SetSkillID( nSkillID );
    pAiTask->SetSkillLevel( nSkillLevel );
    pAiTask->SetPriority( nTaskPriority );
    m_vecAiTask.push_back( pAiTask );

    SetUseSkillIndex( -1 );
}

void AiCharacter::ProcessAiTask()
{
    if ( !CheckCanAiTask() || m_vecAiTask.empty() )
    { return; }

    // 先按优先级排序
    //std::sort( m_vecAiTask.begin(), m_vecAiTask.end(), SortAITaskPriority );

    // 依次执行Ai任务
    for ( AiTaskVectorIter iter = m_vecAiTask.begin(); iter != m_vecAiTask.end(); ++iter )
    {
        ProcessAiTask( *iter );
        ( *iter )->Release();
    }

    m_vecAiTask.clear();
}

void AiCharacter::ProcessAiTask( AiTask* pAiTask )
{
    if ( pAiTask == NULL )
    { return; }

    ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID( pAiTask->GetSkillID(), pAiTask->GetSkillLevel() );
    if( pSkillConfig == NULL )
    { return; }

    bool            bIsCharTarget = false;
    GameObjectId    nTargetCharId = pAiTask->GetAttackID();
    D3DXVECTOR3     xTargetPos    = D3DXVECTOR3( 0, 0, 0 );

    switch ( pSkillConfig->shCastType )
    {
    case ItemDefine::casttype_singletarget:
    case ItemDefine::casttype_AOETargetcirclearea: // 以选定目标为中心的圆形范围技能
        {
            switch( pSkillConfig->ustCastTarget )
            {
            case ItemDefine::casttarget_me:
                { nTargetCharId = GetID(); }
                break;
            default:
                if ( m_nLockID != InvalidGameObjectId )
                { nTargetCharId = m_nLockID; }
                break;
            }

            bIsCharTarget = true;
        }
        break;
    case ItemDefine::casttype_AOEPointCircleArea       : // 目标地点的圆形范围
        {
            BaseCharacter *pTargetChar = GetLockChar();
            if ( pTargetChar == NULL )
            { return; }

            bIsCharTarget = false;
            xTargetPos    = pTargetChar->GetPos();
        }
        break;
    case ItemDefine::casttype_AOEcircleself            : // 以自己为中心的圆形范围技能 *
    case ItemDefine::casttype_AOEquartercirlcefrontage : // 正面90度的扇型范围技能     *
    case ItemDefine::casttype_AOEhalfcirclefrontage    : // 正面180度的半圆范围技能
    case ItemDefine::casttype_AOEquartercirlcebackage  : // 背面90度的扇型范围技能
    case ItemDefine::casttype_AOEhalfcirclebackage     : // 背面180度的半圆范围技能
        {
            bIsCharTarget = false;
            xTargetPos    = GetPos();
        }
        break;
    default:
        { return; }
        break;
    }

    _SkillTaskManager.SetTasks( SSkillTask::STT_SingleSkill, bIsCharTarget, nTargetCharId, xTargetPos, pAiTask->GetSkillID(), pAiTask->GetSkillLevel() );
}

void AiCharacter::AddAiSkill( uint8 nIndex, AiSkill& xSkill )
{
    if ( nIndex >= AiDefine::MonsterMaxSkillCount )
    { return; }

    m_xAiSkill[ nIndex ] = xSkill;
}

AiSkill* AiCharacter::GetAiSkillByIndex( uint8 nIndex )
{
    if ( nIndex >= AiDefine::MonsterMaxSkillCount )
    { return NULL; }

    return &( m_xAiSkill[ nIndex ] );
}

void AiCharacter::SetUseSkill( uint16 nSkillID, uint16 nSkillLevel )
{
    for ( int i = 0; i < AiDefine::MonsterMaxSkillCount; ++i )
    {
        if ( m_xAiSkill[ i ].GetID() == nSkillID && m_xAiSkill[ i ].GetID() == m_xAiSkill[ i ].GetLevel() == nSkillLevel )
        { 
            SetUseSkillIndex( i );
            break;
        }
    }
}

AiSkill* AiCharacter::GetAiSkillByID( uint16 nSkillID, uint8 nSkillLevel )
{
    for ( int i = 0; i < AiDefine::MonsterMaxSkillCount; ++i )
    {
        if ( m_xAiSkill[ i ].GetID() == nSkillID && m_xAiSkill[ i ].GetID() == m_xAiSkill[ i ].GetLevel() == nSkillLevel )
        { return &( m_xAiSkill[ i ] ); }
    }

    return NULL;
}

void AiCharacter::EnterMySight( BaseCharacter* pTarget )
{
    if ( pTarget == NULL || IsDead() )
    { return; }

    if ( pTarget->IsPlayer() )
    { AddAreaPlayerCount(); }

    ProcessEnterSightEnmity( pTarget );
}

void AiCharacter::ExitMySight( BaseCharacter* pTarget )
{
    if ( pTarget->IsPlayer() )
    { SubAreaPlayerCount(); }

    // 删除仇恨
    RemoveEnmity( pTarget->GetID() );

    // 没有仇恨了, 怪物开始回复HP MP
    ProcessClearEnmityResult( pTarget->GetID() );
}

// 记录攻击者的战绩信息
void AiCharacter::UpdatePlayerScore( GameObjectId stID, int iDamage )
{
	if (stID == InvalidGameObjectId)	return;

	if ( m_mapPlayerScore.size() >= AttackMonster_MaxPlayer )
	{
		return;
	}

	ItrMapIdScoreContainer itr = m_mapPlayerScore.find(stID);
	if (itr != m_mapPlayerScore.end())
	{
		itr->second.iDamage += iDamage;
		itr->second.dwLastDamageTime = HQ_TimeGetTime();
	}
	else
	{
		SPlayerScore sScore;
		sScore.stID = stID;
		sScore.iDamage = iDamage;
		sScore.dwLastDamageTime = HQ_TimeGetTime();
		m_mapPlayerScore[stID] = sScore;
	}

	UpdateMonsterBeLong();
}

void AiCharacter::CheckClearAttackerScore()
{
	DWORD curTime = HQ_TimeGetTime();
	ItrMapIdScoreContainer itrBegin = m_mapPlayerScore.begin();
	ItrMapIdScoreContainer itrEnd   = m_mapPlayerScore.end();
	for( ; itrBegin != itrEnd;  )
	{
		BaseCharacter* pFirstChar = theRunTimeData.GetCharacterByID(itrBegin->second.stID);
		if (!pFirstChar || !pFirstChar->IsPlayer())
		{
			itrBegin = m_mapPlayerScore.erase(itrBegin);
			continue;
		}
		if ( curTime - itrBegin->second.dwLastDamageTime >= CheckDamageScoreTime )
		{
			itrBegin = m_mapPlayerScore.erase(itrBegin);
			continue;
		}
		if (GetMapID() != pFirstChar->GetMapID())
		{
			itrBegin = m_mapPlayerScore.erase(itrBegin);
			continue;
		}
		// 追击范围不检测了
		// ...
		++itrBegin;
	}
}

GameObjectId AiCharacter::GetBestAttacker()
{ // 谁是最厉害的攻击者 包括队伍

	ItrMapIdScoreContainer itrBegin = m_mapPlayerScore.begin();
	ItrMapIdScoreContainer itrEnd   = m_mapPlayerScore.end();

	GameObjectId stBestAttackerID = -1;
	int   iMaxDamage = 0;
	MapIdScoreContainer mapTeamOrSingeScore;
	for( ; itrBegin != itrEnd; ++itrBegin )
	{
		BaseCharacter* pFirstChar = theRunTimeData.GetCharacterByID(itrBegin->second.stID);
		if (!pFirstChar || !pFirstChar->IsPlayer())
		{
			continue;
		}
		if ( pFirstChar->GetTeamID() > 0 )
		{
			mapTeamOrSingeScore[pFirstChar->GetTeamID()].stID = itrBegin->second.stID;
			mapTeamOrSingeScore[pFirstChar->GetTeamID()].iDamage += itrBegin->second.iDamage;
		}
		else
		{
			mapTeamOrSingeScore[ pFirstChar->GetID()+TeamDefine::EndSessionID ].stID = itrBegin->second.stID;
			mapTeamOrSingeScore[ pFirstChar->GetID()+TeamDefine::EndSessionID ].iDamage = itrBegin->second.iDamage;
		}
	}
	itrBegin = mapTeamOrSingeScore.begin();
	itrEnd   = mapTeamOrSingeScore.end();
	for( ; itrBegin != itrEnd; ++itrBegin )
	{
		if ( itrBegin->second.iDamage > iMaxDamage )
		{
			stBestAttackerID = itrBegin->second.stID;
			iMaxDamage       = itrBegin->second.iDamage;
		}
	}

	return stBestAttackerID;
}

GameObjectId AiCharacter::GetFirstValidAttacker()
{ 
	// 找到第一个攻击的
	ItrMapIdScoreContainer itrBegin = m_mapPlayerScore.begin();
	ItrMapIdScoreContainer itrEnd   = m_mapPlayerScore.end();
	for ( ; itrBegin != itrEnd; ++itrBegin )
	{
		BaseCharacter* pFirstChar = theRunTimeData.GetCharacterByID(itrBegin->second.stID);
		if ( pFirstChar && pFirstChar->IsPlayer() && !pFirstChar->IsDead() )
			return itrBegin->second.stID; 
	}
	return -1;
}
void AiCharacter::ClearAttackerScoreById(GameObjectId nId)
{
	if (nId == InvalidGameObjectId)
	{ return; }

	ItrMapIdScoreContainer itr = m_mapPlayerScore.find(nId);
	if (itr == m_mapPlayerScore.end())
	{
		return;
	}
	m_mapPlayerScore.erase(itr);
}

void AiCharacter::ClearAllAttackerScore()
{
	// 以往的成绩全部清空
	m_mapPlayerScore.clear();
	OnSetMonsterBelong();//设置当前怪物的归属为0
}
void AiCharacter::OnDeath()
{
    // 清除战斗信息
    ClearLockID();
    ClearEnmity( false );   // 不要清除列表, 因为可能会复活

    // 死亡调用LUA
    if ( m_pBelongKiller != NULL )
    { LuaDeathCallBack( m_pBelongKiller->GetID() ) ; }
    
    // 死亡调用脚本
    ProcessDeathCallScript();

    // 处理怪物状态的改变死亡
    ProcessDeathChangeStatus();
}

bool AiCharacter::CheckDeathCallScript()
{
    if ( m_pBelongKiller == NULL || !m_pBelongKiller->IsPlayer() )
    { return false; }

    if( m_nDeathScriptVMID == -1 )
    { return false; }

    return true;
}

void AiCharacter::ProcessDeathCallScript()
{
    if ( !CheckDeathCallScript() )
    { return; }

    GamePlayer* pKillerPlayer = static_cast< GamePlayer* >( m_pBelongKiller );
    GetScriptMgr()->StartupVM( ST_MONSTER, GetMonsterID(), pKillerPlayer, false, AiDefine::MonsterDeathScriptEnter, GetID() );
}

void AiCharacter::ProcessDeathChangeStatus()
{
    // 设置死亡
    SetStatus( CS_DIEING );

    if ( HaveAreaPlayer() )
    { 
        MsgSawSomeoneDead xSaw;
        xSaw.header.stID = GetID();    
        GettheServer().SendMsgToView( &xSaw, GetID(), true ); 
    }

    // 不能直接调用exit函数 否则怪物死亡不能播放死亡动作
    ProcessDeathExitWorld();
}


void AiCharacter::ProcessDeathExitWorld()
{
    ExitWorldByPushMsg();
}

void AiCharacter::OnBeAttacked( BaseCharacter* pAttacker,const ItemDefine::SItemSkill* pSkillConfig )
{
    BaseCharacter::OnBeAttacked( pAttacker, pSkillConfig );

    // 周围的怪物警觉, 给他们都加上仇恨, 让他们来攻击攻击者
    // MAlarmWhenBeAttack();

    // 如果是路点怪, 记录开始被攻击的坐标, 战斗结束后跑回这个坐标
    if ( NeedMoveToNextRoute() && !NeedMoveToLastIdlePoint() )
    {
        SetLastIdlePoint( GetFloatX(), GetFloatY(), 0 );
    }
}

uint8 AiCharacter::CheckCanAttackResult( BaseCharacter* pTarget )
{
    uint8 nAttackResult = BaseCharacter::CheckCanAttackResult( pTarget );
    if ( nAttackResult != CheckAttack::AttackUnknow )
    { return nAttackResult; }

    return CheckAttack::AttackUnknow;
}

bool AiCharacter::CheckCanBeAttack()
{
    switch ( GetAiStatus() )
    {
    case AiDefine::ThinkingWaitRelive:
        return false;
        break;
    }

    return BaseCharacter::CheckCanBeAttack();
}

// 攻击对方, 在对方身上加上我的仇恨
void AiCharacter::CalcEnmity( BaseCharacter* pTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage )
{
    BaseCharacter::CalcEnmity( pTarget, pSkillConfig, nDamage );

    // 技能不带仇恨值
    if ( pSkillConfig->stEnmity == 0 )
    {  return; }

	//回到出生点过程中不加仇恨
	if ( GetAiStatus() == AiDefine::ThinkingMoveToBorn )
		return;

    // 添加我攻击了对方
    AddAttackTarget( pTarget->GetID() );

    // 仇恨值
    int nEnmity = nDamage + pSkillConfig->stEnmity;
    if ( nEnmity >= 0 )
    { 
        pTarget->AddEnmity( GetID(), nEnmity, nDamage, GetEnmityRate() );
    }
    else
    { 
        // 减少仇恨不能减少到0
        pTarget->DecEnmity( GetID(), abs( nEnmity ) );
        pTarget->AddEnmity( GetID(), 1, nDamage, GetEnmityRate() );
    }
}


long AiCharacter::ApplyBufferStatus( int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue )
{
    // 死了不能附加状态
    if ( IsDead() ) 
    { return GLR_InDeadNotUseStatus; }

    ItemDefine::SItemStatus* pStatusItem = GettheItemDetail().GetStatus( iStatusID, iStatusLevel );
    if( pStatusItem == NULL )
    { return GLR_StatusNotExist; }

    bool bIsCanAddStatus = false;

    int nRand = theRand.rand16() % 100;
    if ( pStatusItem->bIsMove )
    {
        if ( nRand > GetResistBeMove() )
        { bIsCanAddStatus = true; }
    }
    else if ( pStatusItem->bIsAtt )
    {
        if ( nRand > GetResistBeAtt() )
        { bIsCanAddStatus = true; }
    }
    else if ( pStatusItem->bIsUsingMagic )
    {
        if ( nRand > GetResistBeMagic() )
        { bIsCanAddStatus = true; }
    }
    else if ( pStatusItem->bIsUsingTools )
    {
        if ( nRand > GetResistBeTools() )
        { bIsCanAddStatus = true; }
    }
    else
    {
        bIsCanAddStatus = true;
    }

    if ( !bIsCanAddStatus )
    { return GLR_StatusApplyFail; }

    // 释放者如果是玩家, 获得玩家的DBID
    uint32 nPlayerDBID = 0;
    BaseCharacter* pMaster = theRunTimeData.GetCharacterByID( iMaster );
    if ( pMaster != NULL && pMaster->IsPlayer())
    { 
        GamePlayer* pPlayer = static_cast< GamePlayer* > ( pMaster );
        nPlayerDBID = pPlayer->GetDBCharacterID(); 
    }

    bool bStop = false;
    if ( pStatusItem->actionMapConfigId != InvalidLogicNumber && pStatusItem->actionMapConfigId != EctypeId2MapId( GetMapID() ) )
    { bStop = true; }

    if ( !_buffManager.ApplyBuff( bStop, iStatusID, iStatusLevel, iMaster, HQ_TimeGetTime(), false, 0, nPlayerDBID, eventType, eventValue ) )
    {  return GLR_StatusApplyFail; }

    // 发消息通知客户端
    //状态是否有打断施法属性，如果有的话
    if( pStatusItem->bIsUsingMagic )
    { CancelSkill(); }

    if ( pStatusItem->bIsClearDamgeStatus )
    { _buffManager.ClearBuffByBuffIdLevel( pStatusItem->ustItemID,pStatusItem->ustLevel ); }

    return GLR_Success;
}

void AiCharacter::CharacterMurder()
{
    ExitWorldByPushMsg();
}

bool AiCharacter::IsMustMiss()
{
    switch ( GetAiStatus() )
    {
    case AiDefine::ThinkingMoveToBorn:
        return true;
        break;
    default:
        break;
    }

    return false;
}

GamePlayer* AiCharacter::GetMasterPlayer()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetMasterID() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return NULL; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer;
}

bool AiCharacter::CheckInMaxAttackRange( uint32 nMapID, float fX, float fY, float fZ )
{
    if ( nMapID != GetMapID() )
    { return false; }

    // -1为不限制追击范围
    if ( GetMaxAttackRange() == -1 )
    { return true; }

    if ( abs( m_xBornPoint.x - fX ) > GetMaxAttackRange() || abs( m_xBornPoint.y - fY ) > GetMaxAttackRange() || 
        abs( m_xBornPoint.z - fZ ) > GetMaxAttackRange() )
    {
		if (GetKeepAttakTime() != 0 && m_bKeepAttackTimeFlag)
		{//有追击时间&&允许开启计时器m_bKeepAttackTimeFlag == true进来
			if (!m_xTimer[ AiDefine::AiTimer_KeepAttack ].IsStart())
			{//开启计时器
				m_xTimer[ AiDefine::AiTimer_KeepAttack ].StartTimer( HQ_TimeGetTime(), GetKeepAttakTime() );
			}

			//如果时间没到，说明还在计时时间内，return true，要不下次不允许开启计时器m_bKeepAttackTimeFlag = false
			if ( !m_xTimer[ AiDefine::AiTimer_KeepAttack ].DoneTimer())
			{
				return true; 
			}
			else
			{
				m_bKeepAttackTimeFlag = false;
			}
		}

        return false;
    }
	else
	{
		m_bKeepAttackTimeFlag = true;
	}

    return true;
}

void AiCharacter::StartTalk()
{
    ++m_nTalkCount;
    m_xTimer[ AiDefine::AiTimer_Talk ].StopTimer();
    m_xTimer[ AiDefine::AiTimer_Talk ].StartTimer( HQ_TimeGetTime(), AiDefine::AiTalkTimeOut );

    if ( GetAiStatus() == AiDefine::ThinkingStopToTalk )
    { return; }

    SetAiStatus( AiDefine::ThinkingStopToTalk );
    SendVerifyPointMessage();
}

void AiCharacter::EndTalk()
{
    --m_nTalkCount;
    if ( m_nTalkCount < 0 )
    { m_nTalkCount = 0; }

    if ( m_nTalkCount > 0 )
    { return; }

    m_xTimer[ AiDefine::AiTimer_Talk ].NextTimer( 1 );
}

void AiCharacter::DoAssaultMoving( float fDistance, int nInstantMovingType  )
{
    if ( nInstantMovingType == IMT_None || nInstantMovingType == IMT_TargetBack )
    {
        BaseCharacter* pTarget = GetLockChar();
        if ( pTarget == NULL )
        { return; }

        D3DXVECTOR3 vecDistance( pTarget->GetFloatX() - GetFloatX(), pTarget->GetFloatY() - GetFloatY(), 0 );
        float fDist = D3DXVec3Length( &vecDistance );

        D3DXVECTOR3 vDir;
        D3DXVec3Normalize( &vDir, &vecDistance );

        if ( fDistance < fDist )
        { fDist = fDistance; }
        else
        { fDist -= 2.5f; } // 在目标面前3米的位置 

        SetFloatXF( GetFloatX() + fDist * vDir.x );
        SetFloatYF( GetFloatY() + fDist * vDir.y );
    }
    else if ( nInstantMovingType == IMT_Forward )
    {
        D3DXVECTOR3 vecDistance(  fDistance, fDistance, 0 );
        float fFianlDist = D3DXVec3Length( &vecDistance );

        D3DXVECTOR3 vDir;
        D3DXVec3Normalize( &vDir, &vecDistance );

        SetFloatXF( GetFloatX() + fFianlDist * vDir.x );
        SetFloatYF( GetFloatY() + fFianlDist * vDir.y );
    }
    else if ( nInstantMovingType == IMT_Backwards )
    {
        D3DXVECTOR3 vecDistance( -fDistance,  -fDistance, 0 );
        float fFianlDist = D3DXVec3Length( &vecDistance );

        D3DXVECTOR3 vDir;
        D3DXVec3Normalize( &vDir, &vecDistance );

        SetFloatXF( GetFloatX() + fFianlDist * vDir.x );
        SetFloatYF( GetFloatY() + fFianlDist * vDir.y );
    }

    SetVerifyPointAtOnce();
}

bool AiCharacter::FindTheNextPosToMove( D3DXVECTOR3& vTargetPos, float& fRange )
{
	if ( _charFindParth.IsFindParth() )
	{// 需要靠近目标并且开启寻路
		if ( _charFindParth.FindTheNextPosToMove( vTargetPos, GetPos(), GetMapID() ) == false )
		{ return false; }

		if ( ! _charFindParth.IsTheLastPointInParth() )
		{
			//目标位置点才考虑模型大小
			fRange = 0.0f;
		}
	}
	return true;
}

void AiCharacter::AfterMoveToPos()
{
	_charFindParth.AfterMoveToPos( GetPos(), GetMapID() );
}

bool AiCharacter::CheckReachPos()
{
	if ( _charFindParth.IsFindParth() )
	{//已到达当前路点,取下一个路点
		return _charFindParth.CheckReachPos();
	}
	return true;
}

void AiCharacter::InitFindParth( GameObjectId nID, bool blIsFindParth, bool blIsDynamicBlock )
{
    if ( !g_Cfg.bAIFindParth )
    { return; }

	// 怪物初始化时不开启寻路和阻挡
	_charFindParth.InitFindParth( nID, blIsFindParth, blIsDynamicBlock );
	//_blIsFindParthConfig = blIsFindParth;
	//_blIsDynamicBlockConfig = blIsDynamicBlock;
}

void AiCharacter::OnFindParthConfigChanged( bool blNewIsFindParth, bool blNewIsDynamicBlock )
{
    if ( !g_Cfg.bAIFindParth )
    { return; }

	_blIsFindParthConfig = blNewIsFindParth;
	_blIsDynamicBlockConfig = blNewIsDynamicBlock;
}
