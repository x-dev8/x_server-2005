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
    // ����ӵ����Լ������٣��Ǿ���Ҳ����ִ���κ�����
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
	// ��Ѳ������ɾ��
	GetMonsterGroupLogic().OnMonsterDie();

    // ȷ����������Ҳŷ���,���������
    if ( HaveAreaPlayer() )
    { GettheServer().SendMsgToView( pMessage, GetID(), false ); }

    // �ӳ�����ɾ��
    theGameWorld.OnDelCharacter( GetID() ); 

    // ���ͷŻ��ڴ��
    theRunTimeData.ReleaseObject( GetID() , __FILE__, __LINE__); 
}

void AiCharacter::ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue )
{
    bContinue = true;

    m_dwProcessLogicCostTime += dwCostTime; // �ۻ�ʱ�� �еĵط�����ÿ���߼�֡�����õ�
    m_ExtendStatus.Process();
    switch ( GetStatus() )
    {
    case CS_IDLE:
        StatusActionIdle();
        break;
    case CS_ATTACK:// ��ɫ���ڹ�����״̬
        StatusActionAttack();
        break;
    case CS_HOLDSKILL:// ��������
        StatusActionHoldSkill();
        break;
    case CS_INTONATE:// ����
        StatusActionIntonate();
        break;
    case CS_HURT:
        break;
    case CS_DIEING:// ����״̬�����ڵȴ�����
        StatusActionDieing();
        break;
    default:
        break;
    }

    if( !IsDead() )
    { // ������״̬
        // �Ҿ��ϴμ����1��ļ��
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
    // ·����Ϣ
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
    // �������Ҫ����, ��ִ������Ai
    if ( !ProcessDisappear() )
    {
        // �������AI�߼�
        ProcessAiLogic( nCostTime );

        // ������
        ProcessAiRelive();
    }

    // �������
    BaseCharacter::Run( nCostTime );
}

void AiCharacter::ProcessAiLogic( uint32 nCostTime )
{
    if ( IsDead() )
    { return; }

    uint32 nCurrentTime = HQ_TimeGetTime();

    // ˢ�³��
    ProcessRefreshEnmity( nCurrentTime );

    // ��������״̬���
    ProcessBufferStatus();

    // ��ù���Ŀ��
    ProcessFindAttackTarget();

    // �������AI˼��
    ProcessAiThinking( nCurrentTime );

    // ����lua�ű�ִ��
    ProcessLuaRunThinking();

    // ��������ƶ�
    ProcessAiMoving( nCostTime );

    // �������Task����
    ProcessAiTask();

    // �����������ս������Ұ�仯
    ProcessIdleViewSightChange();

    // ��������Ѫ, ��ħ
    ProcessRestore( nCurrentTime );
}

void AiCharacter::ProcessBufferStatus()
{
    // ��������漴���ܵ�״̬
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

    // ����������ϵ�״̬
    bool bResult = _buffManager.UpdateOnDead();
    if ( bResult )
    {
        _buffManager.ApplyBuffsToChar( GetProfession(), GetCharBaseAttr(), GetCharFightAttr() );  
        SendBuffChanged( NULL );
    }

	

	/*MsgExitMySight exitplayersight;
	exitplayersight.header.stID = GetID();
	GettheServer().SendMsgToView( &exitplayersight, GetID(), false );*/

	if (IsFightNpc() && _HAS_FLAG(m_dwFightFlag, eFighting)) //ս��npc�����ʱ�� ���ս��״̬����Ȼ��ֱ�ӽ���ս����ʱ��ս��״̬�����Ϳͻ���
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

    // û��·��Ĺ�, ����������
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
        // ��һ�εĳ��ֵ
        //int nLastEnimty = iter->second.GetEnmity();

        // ���˥��
        BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( iter->first );

#ifdef _DEBUG
        // ȥ��ս��NPC�͹���֮��Ĵ� ����ս������
        if ( (IsNpc() && !IsFightNpc())||( pTarget != NULL && pTarget->IsNpc() && !pTarget->IsFightNpc())  )
        { continue; }
#endif // _DEBUG

        if ( pTarget == NULL || pTarget->IsDead() || !CheckInMaxAttackRange( pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY(), 0 ) )
        { // �����Ժ�, ����г�������֮..
            iter->second.ClearEnmity();
			if (pTarget)
			{
				GetMonsterGroupLogic().OnClearTargetEnmity( pTarget->GetID() );
			}

        }
        else
        {
            // ���˥��
            //iter->second.DecEnmity( iter->second.GetReduction() );

            // ����������Ұ���
            ProcessViewEnmity( iter->second, pTarget );
        }

        // ������˥����, ���û�г����, Ҫ���������ɫ�б�
        if ( !iter->second.HaveEnmity() )
        { ProcessClearEnmityResult( iter->first ); }
    }

    // ˢ��ǰ���ڳ��, ˢ�º�û�г��, ����ս��״̬
    if ( HaveFighteFlag( eFighting ) && !HaveEnmity() )
    { ProcessEndAttackStatus(); }
}

bool AiCharacter::CheckAddViewEnmity( EnmityData& xEnmityData, BaseCharacter* pChar )
{
    // ������Ұ���
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
    // �ı�״̬
    SetStatus( CS_IDLE );

    // �������Ŀ��
    ClearLockID();

    // ������ 
    ClearEnmity( false ); //�ȸĳɲ��������ֹ�����ֺ�ս��NPC���ٴν������ǵ���Ұ������������ lrt

    // ���ս��
    ClearAllAttackerScore();

    // �뿪ս��״̬
    TryChangeFightState ( false, eFighting );

    // 2���ָ���ͨ��Ұ
    StartIdleViewTimer  ( HQ_TimeGetTime() );

    // ��ʼ��Ѫ
    StartRestoreTimer   ( HQ_TimeGetTime() ); 

    // �ı�Ai״̬
    SetAiStatus( AiDefine::ThinkingMoveToLastIdle );

    // ���Ai����
    ClearAiVariable();

	// Ѳ��������ս���߼�
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

    // ���ܻس������ʱ��, ��������Ŀ��
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

    // ɾ���Լ��Ĺ���Ŀ���б�
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

    // ǰ��thinking�л�����һ���ƶ���Ŀ���, ����ֻ�����ƶ�
    if ( NeedMovingToTargetPoint() )
    { 
		if ( GetAiStatus() == AiDefine::ThinkingMoveToBorn )// lrt �����Ҫ�ص������㣬��λ���в��ǳ����㣬�������п���ʹ����ֹͣĳ���ط�������������Ҳ������������
		{													// �������Ŀ��λ������Ϊ�����㣨�������Խ������ȥ���⣬�����ﵼ�µ�λ�ô���û�ҵ�����������
			if ( abs( m_xMoveTargetPoint.x - m_xBornPoint.x) > 1.0 || abs( m_xMoveTargetPoint.y - m_xBornPoint.y) > 1.0 )
			{
				ProcessAttackMoveSpeed( 1.5f );
				m_xMoveTargetPoint.x = m_xBornPoint.x;
				m_xMoveTargetPoint.y = m_xBornPoint.y;
			}
		}
        // ������Ҫ�ƶ�, ���ù����������    
        D3DXVECTOR3 vecDistance( m_xMoveTargetPoint.x - GetFloatX(), m_xMoveTargetPoint.y - GetFloatY(), 0/*m_xMoveTargetPoint.z - GetFloatZ()*/ );
        float fDist = D3DXVec3Length( &vecDistance );

        D3DXVECTOR3 vDir;
        D3DXVec3Normalize( &vDir, &vecDistance );

        bool bMoveArrive = false;
        float fActualMoveDist = GetMoveSpeed() * ( 0.001f * static_cast< float >( nCostTime ) );

        if( fActualMoveDist >= fDist )
        {   // ����, ������ƶ�Ŀ���
            fActualMoveDist = fDist; 
            bMoveArrive = true;
        }
        else
        {
            // ·�����ƶ�ʱ��, ���С��1.0f�������Ѿ�����, �������Ῠһ��
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

		// ������λ�ú���Ҫ���õ�Ѱ·�ӿ� Ѱ·�ڲ�ά��״̬,�����ж��Ƿ���ս��״̬
        AfterMoveToPos();

        // ������Ŀ�ĵ�״̬�ı�( ���������, ������Ҫ�ı䳯���... )
        if ( bMoveArrive )
        {
			// ����Ŀ�����Ҫ���õ�Ѱ·�ӿ� Ѱ·�ڲ�ά��״̬,�����ж��Ƿ���ս��״̬
			CheckReachPos();
			ProcessMoveArriveResult();
		}
    }

    // ÿ2��ͬ��һ��
    if ( !m_xTimer[ AiDefine::AiTimer_Move ].DoneTimer( HQ_TimeGetTime() ) )
    { return; }

    // ˢ������
    theGameWorld.OnRefreshNewArea( GetID() );

    // ��Χû����ҾͲ�������Ϣ��
    if ( !HaveAreaPlayer() )
    { return; }

    // ����ͬ����Ϣ, 4��һ��, 
    if ( !m_bNeedVerifyPoint )
    {   // ���涨ʱ����2��ִ��һ��, ��������Ҫ4���ִ��һ��
        m_bNeedVerifyPoint = true;
        return; 
    }

    m_bNeedVerifyPoint = false;

    if ( NeedMovingToTargetPoint() )
    { 
        // �ƶ���ʱ��, ֻ�����ƶ���Ϣ 
        SendMoveToTargetPointMessage(); 
    }
    else
    {
        // �ƶ���ϢƵ�� ������ ����GateServer��������Ҫͬ������λ����Ϣ
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
            SetVerifyPointAtOnce(); // ���ϸ���һ������
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
            SetVerifyPointAtOnce(); // ���ϸ���һ������
            SetAiStatus( AiDefine::ThinkingMoveToPoint );
        }
        break;
    case AiDefine::ThinkingRandRun:
        {
            // �漴���ܵ����, ����˼����һ����
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

    // ���ù���Ŀ��ƶ���Χ
    m_xCanMoveZone.left   = FloatToTile( GetFloatX() ) - AiDefine::MonsterMoveRadius;
    m_xCanMoveZone.right  = FloatToTile( GetFloatX() ) + AiDefine::MonsterMoveRadius;
    m_xCanMoveZone.top    = FloatToTile( GetFloatY() ) - AiDefine::MonsterMoveRadius;
    m_xCanMoveZone.bottom = FloatToTile( GetFloatY() ) + AiDefine::MonsterMoveRadius;

    // ͬʱ���ù����ڸ���������
    SetBornPoint( GetFloatX(), GetFloatY(), 0 );

    // �ƶ�����һ��·��
    ++m_nRouteStep;

    SetMoveRoutePoint();
}

void AiCharacter::SetMoveRoutePoint()
{
    if ( m_nRouteStep < 0 )
    { return SetAiStatus( AiDefine::ThinkingMoveAround ); }

    if (m_xTimer[ AiDefine::AiTimer_RouteMove ].IsStart() && !m_xTimer[ AiDefine::AiTimer_RouteMove ].DoneTimer() )
    { return; }

	// Ѳ����ȴ�������Ա��λ
	if ( GetMonsterGroupLogic().CanMoveOn() == false )
	{ return; }

    // ����·���, ����·����Ϣ
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

        // ��һ��·�����
        if ( m_pRoute->allMovePos.empty() )
        {
            LogMessage::LogSystemError( "RouteError:AiChar·��Id[%d] CharId[%d] CharName[%s]", m_pRoute->routeId, GetID(), GetCharName() );
            m_nRouteStep = -1;
            return SetAiStatus( AiDefine::ThinkingMoveAround );
        }

        m_nRouteStep = 0;
    }

    // ������һ��·��Ŀ��
    SMovePos& xMovePos = m_pRoute->allMovePos.at( m_nRouteStep );

    SetMoveTargetPoint( xMovePos.fX, xMovePos.fY, 0 );

    if( xMovePos.fV != GetMoveSpeed() )
    { ChangeMoveSpeed( xMovePos.fV ); } 

    SetMoveStep( xMovePos.fStep );

	// Ѳ�����߼�
	GetMonsterGroupLogic().OnMonsterMoveToPos( D3DXVECTOR3( xMovePos.fX, xMovePos.fY, 0 ) );

    // ·�㶯��
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

    // ����
    if ( xMovePos.stSceneId > 0  )
    {
        MsgScenePlay  msgScene;
        msgScene.header.stID = GetID();
        msgScene.stSceneId   = xMovePos.stSceneId;
        GettheServer().SendMsgToView( &msgScene, GetID(), true );
    }

    // ֹͣ�ƶ�
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

    // �ȷ���Ŀ�����ͻ��˴���, ʹ����ƽ�����ƶ�
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

    xVerifyPoint.SetLevel(level_normal); // �����������е����ȼ�
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
    // ����ս��,2���ָ�����Ŀ�����Ұ��Χ��С
    if ( !m_xTimer[ AiDefine::AiTimer_IdleView ].DoneTimer() )
    { return; }

    SetViewSight( GetIdleViewSight() );
}

int AiCharacter::GetThinkingSpaceTime()
{
    // ��ͨ����˼��ʱ��1000ms
    return GetThinkingTime() + theRand.rand16() % AiDefine::MonsterThinkTime;
}

uint8 AiCharacter::ThinkingAttackTarget( uint32 nCurrentTime )
{
    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( GetLockID() );
    if ( pTarget == NULL || pTarget->IsDead() || !CheckCanAttackTarget(pTarget) || !CheckInMaxAttackRange( pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY(), 0 ) )
    { return ProcessLostLockTarget( pTarget ); }

    // �õ�Ҫʹ�õļ��� CheckUseSkillPreconditionState ���������ж�, ����׷����ʱ�����һ��, Ч������
    const AiSkill* pAiSkill = GetCanUseSkill( nCurrentTime );
    if ( pAiSkill == NULL )
    { return AiDefine::ThinkingDoNothing; }

	uint8 nState = AiDefine::ThinkingAttackTarget;
    // ���ڹ�����Χ��, ���ƶ���������Χ��
    if ( !CheckCanAttackTargetDistance( pTarget, pAiSkill->GetID(), pAiSkill->GetLevel() ) )
    {
        // ���ƶ�����, ��Ŀ���ƶ�
        if ( HaveMoveAbility() )
        { 
            SetThinkingSpaceTime( AiDefine::BaseThinkTime );

			// ׷��Ŀ��,����Ѱ·
			_charFindParth.ReInitFindParth( _blIsFindParthConfig, _blIsDynamicBlockConfig );

            nState = AiDefine::ThinkingMoveToTarget; 
        }
		else
		{ nState = AiDefine::ThinkingDoNothing; }
    }

    // �Ƿ���ʹ�ü���״̬( 
    if( !CheckUseSkillPreconditionState() )
    { nState = AiDefine::ThinkingDoNothing; }

    // �����Թ���Ŀ��( �ı�ս��״̬��... )
    ProcessTryAttackTarget( pTarget );

    // ���ƶ�������Ҫ�ı䳯��
    if ( HaveMoveAbility() )
    { ProcessChangeDirToTarget();  }

    return nState;
}

// �Ƿ��ڹ�����Χ��
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
    // �ı�ս��״̬
    TryChangeFightState( true, eFighting );

    // �л���ս����Ұ
    SetViewSight( GetFightViewSight() );

    // ���Է�����һ�����( ֻ��Ŀ������Ҳ���ô�� )
    if ( pTarget->IsPlayer() )
    {
        EnmityData* pEnmityData = pTarget->GetEnmity( GetID() );
        if ( pEnmityData == NULL || pEnmityData->GetEnmity() < GetViewEnmity() )
        { pTarget->SetEnmity( GetID(),  GetViewEnmity(), GetEnmityRate() ); }
    }

    // �������·��, ���浱ǰλ��
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
    // �Ѿ���ִ��Ai
    if ( !_SkillTaskManager.IsTaskEmpty() && !m_vecAiTask.empty() )
    { return NULL; }

    AiSkill* pAiSkill = GetAiSkillByIndex( GetUseSkillIndex() );
    if ( pAiSkill != NULL ) // �Ѿ���ʹ�õļ���
    {
        if ( CheckCanUseSkill( pAiSkill->GetID() ) )
        { return pAiSkill; }
    }

    // �����ԭ���趨�ļ���
    SetUseSkillIndex( -1 );

    // û�������Ҽ���
    std::vector< int > vecCanUseSkill( 0 );

    // �ҵ�����ʹ�õļ�������
    for ( int i = 0; i < AiDefine::MonsterMaxSkillCount; ++i )
    {
        if ( !m_xAiSkill[ i ].CanUseAiSkill( GetHP(), GetMP() ) )
        { continue; }

        if ( !CheckCanUseSkill( m_xAiSkill[ i ].GetID() ) )
        { continue; }

        vecCanUseSkill.push_back( i );
    }

    // �м������ü��ܾ��������
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
    // Ŀ�겻���ڻ��߾����Զ, ɾ������б�
    //RemoveEnmity( GetLockID() ); //lrt ��ֹ�ٴν�����Ұ���ṥ�� �ĳ�����2�䣬ֻ������ֵ�͹���Ŀ�꣬��ɾ������б�
	SetEnmity( GetLockID(), 0 );
	RemoveAttackTarget( GetLockID() );

	GetMonsterGroupLogic().OnClearTargetEnmity( GetLockID() );

    ClearLockID();
    ClearMoveTargetPoint();

    if ( NeedMoveToNextRoute() )
    { SetAiStatus( AiDefine::ThinkingMoveToLastIdle ); }
    else
    { SetAiStatus( AiDefine::ThinkingMoveToBorn ); }

	// ���Ѱ·
	_charFindParth.ReInitFindParth( false, false );

    return AiDefine::ThinkingDoNothing;
}

uint8 AiCharacter::ThinkingMoveToTarget()
{
    // �Լ����ڷ�Χ��
    if ( !CheckInMaxAttackRange( GetMapID(), GetFloatX(), GetFloatY(), 0 ) )
    { return ProcessLostLockTarget( NULL ); }

    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( GetLockID() );
    if ( pTarget == NULL || !CheckInMaxAttackRange( pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY(), 0 ) )
    { return ProcessLostLockTarget( pTarget ); }

    // �Ѿ����ƶ�
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
		
        // ��ó�����Ľ�ɫ,�Ѿ�������Ŀ��ʱ, �������˺�����, �������׻�����Ŀ��
        if ( iter->second.GetEnmity() > nMaxEnmityValue )
        {
			pChar = theRunTimeData.GetCharacterByID(iter->first);
			if (pChar&&!pChar->IsDead())
			{//Ҫ���ҵ�Ŀ���ɫָ�룬andĿ��û��������ΪĿ��
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

    // û�г��ֱ�ӷ���
    int nLockID = InvalidGameObjectId;
    if ( !HaveLockTarget() )
    {
        // û������Ŀ��ʱ, �������Ŀ��
        nLockID = GetMinDistanceAttackTarget();
    }
    else
    {
        // ������Ŀ��ʱ, �ҹ����ҵ�, ���ҳ������
        nLockID = GetMaxEnmityAttackTarget();
    }

    // ����Ŀ��
    ProcessLockTarget( nLockID );
}

uint8 AiCharacter::ThinkingMoveToBorn()
{
    // �Ѿ����ƶ���
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

    // ֻ�ж�ƽ��λ��
    D3DXVECTOR3 vecDistance( vTargetPos.x - vCurPos.x, vTargetPos.y - vCurPos.y, 0 );

    // ����Ŀ���
    if ( D3DXVec3Length( &vecDistance ) <= 1 )
    {
        SetMovePoint( 0.0f, 0.0f, 0.0f );
        return AiDefine::ThinkingDoNothing;
    }

    return AiDefine::ThinkingMoveToPoint;
}

uint8 AiCharacter::ThinkingMoveAround()
{
    // ��Χû�����..���߶�, ʡ��Ϣ
    if ( !HaveAreaPlayer() )
    { return AiDefine::ThinkingDoNothing; }

    // ���Լ����Χ��, �漴�ƶ�
    if ( !HaveMoveAbility() )
    { return AiDefine::ThinkingDoNothing; }

    // �ж��ƶ�����
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

    // �������˼��, ����Ҫ��ÿ���߼�֡��˼��, �������
    if ( !m_xTimer[ AiDefine::AiTimer_Thinking ].DoneTimer( nCurrentTime ) )
    { return; }

    // ������һ��˼��ʱ��
    SetThinkingSpaceTime( GetThinkingSpaceTime() );

    // ����˼��
    uint8 nThinkingResult = AiThinking( nCurrentTime );
    switch ( nThinkingResult )
    {
    case AiDefine::ThinkingMoveToBorn:     // �ƶ���������
        ProcessMoveToBornPoint();
        break;
    case AiDefine::ThinkingMoveAround:     // �����㸽���漴�ƶ�
        ProcessMoveAround();
        break;
    case AiDefine::ThinkingMoveToTarget:   // �ƶ�������Ŀ���
        ProcessMoveToAttackTarget();
        break;
    case AiDefine::ThinkingAttackTarget:   // ��������Ŀ��
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
    // ����ʱ, ������ʱ���ƶ��ٶ�
    float fSpeed = GetAttackMoveSpeed() * fModulus;
    if ( abs( GetCharFightAttr()->moveSpeed.base - fSpeed ) < 0.0001 )
    { return; }

    ChangeMoveSpeed( fSpeed ); 
}

void AiCharacter::ProcessIdleMoveSpeed()
{
    // ����ʱ�ƶ��ٶ�
    float fSpeed = GetIdleMoveSpeed();
    if ( abs( GetCharFightAttr()->moveSpeed.base - fSpeed ) < 0.0001 )
    { return; }

    ChangeMoveSpeed( fSpeed ); 
}

void AiCharacter::ProcessMoveToRoute()
{
    // �Ѿ����ƶ���
    if ( NeedMovingToTargetPoint() )
    { return; }

    SetMoveRoutePoint();
}

void AiCharacter::ProcessMoveToBornPoint()
{
    ProcessAttackMoveSpeed( 1.5f );

    if ( NeedMovingToTargetPoint() )
    { return; }

    // ��Ŀ������óɳ�����
    SetMoveTargetPoint( m_xBornPoint.x, m_xBornPoint.y, m_xBornPoint.z );
}

void AiCharacter::ProcessMoveToPoint()
{
    ProcessAttackMoveSpeed();

    if ( NeedMovingToTargetPoint() )
    { return; }

    // ��Ŀ������ó�ĳ��
    SetMoveTargetPoint( m_xMovePoint.x, m_xMovePoint.y, m_xMovePoint.z );
}

void AiCharacter::ProcessChangeDirToTarget()
{
    // �ҵ�����Ŀ��
    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( GetLockID() );
    if ( pTarget == NULL )
    { return; }

    D3DXVECTOR3 vecDistance( pTarget->GetFloatX() - GetFloatX(), pTarget->GetFloatY() - GetFloatY(), 0 );
    float fDistance = D3DXVec3Length( &vecDistance );

    // ����
    D3DXVECTOR3 vecDir;
    D3DXVec3Normalize( &vecDir, &vecDistance );

    // ����ı�
    SetDirX( vecDir.x );
    SetDirY( vecDir.y );

    // ����ͬ��һ��λ��
    SetVerifyPointAtOnce();
}

void AiCharacter::ProcessMoveToAttackTarget()
{
	DECLARE_TIME_TEST

    ProcessAttackMoveSpeed();

    // �ҵ�����Ŀ��
    BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( GetLockID() );
    if ( pTarget == NULL )
    { return; }

	// �ҵ�����, ��ù�������
	AiSkill* pAiSkill = GetAiSkillByIndex( GetUseSkillIndex() );
	if ( pAiSkill == NULL )
	{ 
        pAiSkill = GetCanUseSkill( HQ_TimeGetTime() );
        if ( pAiSkill == NULL )
        { return; }
    }

	// Ѱ· �˴� pAiSkill->GetAttackDistance() ����ܴ��������ܼ���
	D3DXVECTOR3 vecTargetPos( pTarget->GetPos() );
	float fFreeRange = pTarget->GetBodySize() + pAiSkill->GetAttackDistance();	// ���ܵĹ�����¼��Ŀ�������

	BEGIN_TIME_TEST( "LogicThread FindParth" );
	bool blHasFindParth = FindTheNextPosToMove( vecTargetPos, fFreeRange );
	END_TIME_TEST_1( "LogicThread FindParth", 1 );
	if ( ! blHasFindParth )
	{ return; }

    // ��Ŀ��֮��ľ���
    D3DXVECTOR3 vecDistance( vecTargetPos.x - GetFloatX(), vecTargetPos.y - GetFloatY(), 0 );
    float fDistance = D3DXVec3Length( &vecDistance );

    // ����
    D3DXVECTOR3 vecDir;
    D3DXVec3Normalize( &vecDir, &vecDistance );

    // ��ȥ���ܵĹ�����¼��Ŀ�������
    float fRange = fDistance - fFreeRange;

    // ����Ŀ���
    float fTargetX = GetFloatX() + fRange * vecDir.x;
    float fTargetY = GetFloatY() + fRange * vecDir.y;
    if ( fTargetX != m_xMoveTargetPoint.x || fTargetY != m_xMoveTargetPoint.y )
    { SetMoveTargetPoint( GetFloatX() + fRange * vecDir.x, GetFloatY() + fRange * vecDir.y, 0 ); }

    // ����׷��ʱ��, ����λ��1��ͬ��һ��
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
    // 200����һ��λ��, �Ϳͻ����㷨ͬ��
    ProcessMoveToMaster();
}

void AiCharacter::ProcessMoveToMaster()
{
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster == NULL || pMaster->IsDead() )
    { return CharacterMurder(); }

    ProcessAttackMoveSpeed();

    // ����ͬһ����ͼ, �Ͳ�����
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

    // ֻ�ж�ƽ��λ��
    D3DXVECTOR3 vecDistance( vMasterPos.x - vCurPos.x, vMasterPos.y - vCurPos.y, 0 );
    float fDistance = D3DXVec3Length( &vecDistance );

    float distanceBeginFollow = m_fBodySize + pMaster->GetBodySize() + 1.0f;

    //// ��ʼ����
    //D3DXVECTOR3 vecDir;
    //D3DXVec3Normalize( &vecDir, &vecDistance );

    // �Ѿ��ڸ���, ����Ҫ������
    if( m_fBodySize < 0 || fDistance <= distanceBeginFollow )
    { 
        return ClearMoveTargetPoint();
    }

    // �ڳ���������̫Զ, ֹͣ���� ( ֻ�л��͹�֮��Ų������� )
    if ( !IsPet() && fDistance > AiDefine::ProtectCharStopDistance )
    { 
        return ClearMoveTargetPoint(); 
    }

    // �����ɢ��������120����������
    const float fAngle = D3DX_PI / 1.5f;
    // ���˳���
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

    // �����ƶ�Ŀ���
    if ( m_xMoveTargetPoint.x != vCurPos.x || m_xMoveTargetPoint.y != vCurPos.y )
    { 
        SetMoveTargetPoint( vCurPos.x, vCurPos.y, 0 );
        // ���³�����
        SetBornPoint( vCurPos.x, vCurPos.y, 0 );
    }
}

void AiCharacter::ProcessAttackTarget()
{
    AiSkill* pAiSkill = GetAiSkillByIndex( GetUseSkillIndex() );
    if ( pAiSkill == NULL )
    { return; }

    AddAiTask( GetLockID(), pAiSkill->GetID(), pAiSkill->GetLevel() );

    // ������ȴ
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
    // ��Ѫ��ħ���ûظ�
    if ( GetHP() == GetHPMax() && GetMP() == GetMPMax() )
    { return; }

    // ���ﲻ�趨��Ѫ
    if ( GetRestoreHP() == 0 && GetRestoreMP() == 0 )
    { return; }

    m_xTimer[ AiDefine::AiTimer_Restore ].StartTimer( nCurrentTime, GetRestoreSpaceTime() );
    m_xTimer[ AiDefine::AiTimer_Restore ].NextTimer( 1 ); // ���ϻ�Ѫһ��
}

void AiCharacter::ProcessRestore( uint32 nCurrentTime )
{
    // ��ʱ��û����,����û��ʱ���򷵻�
    if ( !m_xTimer[ AiDefine::AiTimer_Restore ].DoneTimer( nCurrentTime ) || 
		GetAiStatus() == AiDefine::ThinkingAttackTarget || GetAiStatus() == AiDefine::ThinkingMoveToTarget ) //ս���в���Ѫ
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
        // �������Ըı���Ϣ. ����ֻ��ʾѪ��
        ChangeAttr( CharAttr_HP, GetHP() );
    }

    // �ָ�����, �رն�ʱ��
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

    // �Ȱ����ȼ�����
    //std::sort( m_vecAiTask.begin(), m_vecAiTask.end(), SortAITaskPriority );

    // ����ִ��Ai����
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
    case ItemDefine::casttype_AOETargetcirclearea: // ��ѡ��Ŀ��Ϊ���ĵ�Բ�η�Χ����
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
    case ItemDefine::casttype_AOEPointCircleArea       : // Ŀ��ص��Բ�η�Χ
        {
            BaseCharacter *pTargetChar = GetLockChar();
            if ( pTargetChar == NULL )
            { return; }

            bIsCharTarget = false;
            xTargetPos    = pTargetChar->GetPos();
        }
        break;
    case ItemDefine::casttype_AOEcircleself            : // ���Լ�Ϊ���ĵ�Բ�η�Χ���� *
    case ItemDefine::casttype_AOEquartercirlcefrontage : // ����90�ȵ����ͷ�Χ����     *
    case ItemDefine::casttype_AOEhalfcirclefrontage    : // ����180�ȵİ�Բ��Χ����
    case ItemDefine::casttype_AOEquartercirlcebackage  : // ����90�ȵ����ͷ�Χ����
    case ItemDefine::casttype_AOEhalfcirclebackage     : // ����180�ȵİ�Բ��Χ����
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

    // ɾ�����
    RemoveEnmity( pTarget->GetID() );

    // û�г����, ���￪ʼ�ظ�HP MP
    ProcessClearEnmityResult( pTarget->GetID() );
}

// ��¼�����ߵ�ս����Ϣ
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
		// ׷����Χ�������
		// ...
		++itrBegin;
	}
}

GameObjectId AiCharacter::GetBestAttacker()
{ // ˭���������Ĺ����� ��������

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
	// �ҵ���һ��������
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
	// �����ĳɼ�ȫ�����
	m_mapPlayerScore.clear();
	OnSetMonsterBelong();//���õ�ǰ����Ĺ���Ϊ0
}
void AiCharacter::OnDeath()
{
    // ���ս����Ϣ
    ClearLockID();
    ClearEnmity( false );   // ��Ҫ����б�, ��Ϊ���ܻḴ��

    // ��������LUA
    if ( m_pBelongKiller != NULL )
    { LuaDeathCallBack( m_pBelongKiller->GetID() ) ; }
    
    // �������ýű�
    ProcessDeathCallScript();

    // �������״̬�ĸı�����
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
    // ��������
    SetStatus( CS_DIEING );

    if ( HaveAreaPlayer() )
    { 
        MsgSawSomeoneDead xSaw;
        xSaw.header.stID = GetID();    
        GettheServer().SendMsgToView( &xSaw, GetID(), true ); 
    }

    // ����ֱ�ӵ���exit���� ��������������ܲ�����������
    ProcessDeathExitWorld();
}


void AiCharacter::ProcessDeathExitWorld()
{
    ExitWorldByPushMsg();
}

void AiCharacter::OnBeAttacked( BaseCharacter* pAttacker,const ItemDefine::SItemSkill* pSkillConfig )
{
    BaseCharacter::OnBeAttacked( pAttacker, pSkillConfig );

    // ��Χ�Ĺ��ﾯ��, �����Ƕ����ϳ��, ������������������
    // MAlarmWhenBeAttack();

    // �����·���, ��¼��ʼ������������, ս���������ܻ��������
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

// �����Է�, �ڶԷ����ϼ����ҵĳ��
void AiCharacter::CalcEnmity( BaseCharacter* pTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage )
{
    BaseCharacter::CalcEnmity( pTarget, pSkillConfig, nDamage );

    // ���ܲ������ֵ
    if ( pSkillConfig->stEnmity == 0 )
    {  return; }

	//�ص�����������в��ӳ��
	if ( GetAiStatus() == AiDefine::ThinkingMoveToBorn )
		return;

    // ����ҹ����˶Է�
    AddAttackTarget( pTarget->GetID() );

    // ���ֵ
    int nEnmity = nDamage + pSkillConfig->stEnmity;
    if ( nEnmity >= 0 )
    { 
        pTarget->AddEnmity( GetID(), nEnmity, nDamage, GetEnmityRate() );
    }
    else
    { 
        // ���ٳ�޲��ܼ��ٵ�0
        pTarget->DecEnmity( GetID(), abs( nEnmity ) );
        pTarget->AddEnmity( GetID(), 1, nDamage, GetEnmityRate() );
    }
}


long AiCharacter::ApplyBufferStatus( int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue )
{
    // ���˲��ܸ���״̬
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

    // �ͷ�����������, �����ҵ�DBID
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

    // ����Ϣ֪ͨ�ͻ���
    //״̬�Ƿ��д��ʩ�����ԣ�����еĻ�
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

    // -1Ϊ������׷����Χ
    if ( GetMaxAttackRange() == -1 )
    { return true; }

    if ( abs( m_xBornPoint.x - fX ) > GetMaxAttackRange() || abs( m_xBornPoint.y - fY ) > GetMaxAttackRange() || 
        abs( m_xBornPoint.z - fZ ) > GetMaxAttackRange() )
    {
		if (GetKeepAttakTime() != 0 && m_bKeepAttackTimeFlag)
		{//��׷��ʱ��&&��������ʱ��m_bKeepAttackTimeFlag == true����
			if (!m_xTimer[ AiDefine::AiTimer_KeepAttack ].IsStart())
			{//������ʱ��
				m_xTimer[ AiDefine::AiTimer_KeepAttack ].StartTimer( HQ_TimeGetTime(), GetKeepAttakTime() );
			}

			//���ʱ��û����˵�����ڼ�ʱʱ���ڣ�return true��Ҫ���´β���������ʱ��m_bKeepAttackTimeFlag = false
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
        { fDist -= 2.5f; } // ��Ŀ����ǰ3�׵�λ�� 

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
	{// ��Ҫ����Ŀ�겢�ҿ���Ѱ·
		if ( _charFindParth.FindTheNextPosToMove( vTargetPos, GetPos(), GetMapID() ) == false )
		{ return false; }

		if ( ! _charFindParth.IsTheLastPointInParth() )
		{
			//Ŀ��λ�õ�ſ���ģ�ʹ�С
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
	{//�ѵ��ﵱǰ·��,ȡ��һ��·��
		return _charFindParth.CheckReachPos();
	}
	return true;
}

void AiCharacter::InitFindParth( GameObjectId nID, bool blIsFindParth, bool blIsDynamicBlock )
{
    if ( !g_Cfg.bAIFindParth )
    { return; }

	// �����ʼ��ʱ������Ѱ·���赲
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
