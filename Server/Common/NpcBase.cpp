#include "NpcBase.h"
#include "ScriptCompiler.h"
#include "ScriptMgr.h"
#include "GameWorld.h"
#include "ShareData.h"
#include "FuncPerformanceLog.h"
#include "SlkReader.h"
#include "ResourcePath.h"
#include "RouteManager.h"

#define TALK_TIMEOUT ( 2 * 60000)

uint8 NpcBase::GetObjecTypeByNpcType( uint8 npcType )
{
    switch ( npcType )
    {
    case eNT_Normal       :
    case eNT_Restore      :
    case eNT_Weapon       :
    case eNT_Jewelry      :
    case eNT_Dress        :
    case eNT_Material     :
    case eNT_Transport    :
    case eNT_Cavalry      :
    case eNT_Storage      :
    case eNT_Star         :
    case eNT_MakeItemNpc  :
    case eNT_Activity     :
    case eNT_Feudal       :
    case eNT_Sale         :
    case eNT_SpecialSale  :
    case eNT_ScriptNpc    :
    case eNT_GongXun      :
    case eNT_MingWang     :
    case eNT_ShiZhuang    :
    case eNT_WenDa        :
    case eNT_JiNeng       :
    case eNT_PeiJian      :
    case eNT_ShiWu        :
    case eNT_YiZhan       :
    case eNT_ZaHuo        :
    case eNT_FenJie       :
    case eNT_QianZhuang   :
    case eNT_Pub          :
    case eNT_MoveStar     :
    case eNT_SpecialRepair:
    case eNT_KeepWord2    :
    case eNT_KeepWord3    :
    case eNT_KeepWord4    :
    case eNT_KeepWord5    :
    case eNT_KeepWord6    :
    case eNT_KeepWord7    :
    case eNT_KeepWord8    :
    case eNT_KeepWord9    :
    case eNT_Item         :
    case eNT_Battle       :
        return Object_NpcNormal;
        break;
    case eNT_Patrol:
        return Object_NpcFight;
        break;
    case eNT_Ship:
        return Object_NpcShip;
        break;
    }

    return Object_NpcNormal;
}

NpcBase::NpcBase()
{
    m_dwLastUpdateMoveStateToPlayerTime = 0;
    SetObjType( Object_Npc );
    SetCanSwitchStage( false );
    SetStatus( CS_IDLE );
    m_enNpcType = eNT_Normal;    
    m_dwWaitingStartTime = 0;
    m_nCurStep           = -1;
    m_enMoveState        = EAction_Stop;
    m_nTalkCount         = 0;
    m_bMask              = false;
    _pNpcInfo            = NULL;
    m_DisappearTime      = 0;
    m_bShow              = true;
    _bIsConfigAddress    = false;
    m_fMoveStep          = 1.0f;
    m_n9AreaPlayerCnt    = 0;
}

NpcBase::~NpcBase()
{
    GetScriptMgr()->ReleaseVMByDstId( ST_NPC, GetID() );
    if ( !_bIsConfigAddress )
    { delete _pNpcInfo; }
}

void NpcBase::StartShowTimer( unsigned int nStartTime, unsigned int nSpaceTime )
{
    m_xShowTimer.StartTimer( nStartTime, nSpaceTime );
}

void NpcBase::StartHideTimer( unsigned int nStartTime, unsigned int nSpaceTime )
{
    m_xHideTimer.StartTimer( nStartTime, nSpaceTime );
}

// 设置NPC状态
void NpcBase::SetShow( bool bValue )
{
    m_bShow = bValue;

    MsgTellHideStatus xTell;
    xTell.header.stID = GetID();
    xTell.stID        = GetID();
    xTell.bShow       = m_bShow;
    GettheServer().SendMsgToView( &xTell, GetID(), true );
}

BOOL NpcBase::AddRelateQuestInfo( RelateQuestInfo* pInfo )
{
    _relateQuestInfo.push_back( *pInfo );
    return TRUE;
}

NpcBase::RelateQuestInfo* NpcBase::GetRelateQuestInfo( int n )
{
    if (n <0 || n >= _relateQuestInfo.size())
    {return NULL; }

    return &_relateQuestInfo[n];
}

void NpcBase::Run( DWORD dwCostTime )
{
    BaseCharacter::Run(dwCostTime);

    if ( m_DisappearTime != 0 && m_enNpcType == eNT_ScriptNpc && _disappearTime.DoneTimer() )
    {
        MsgExit msgexit;
        OnExit(&msgexit);
        return;
    }

    // 判断时间 如果要隐身, 就通知客户端隐身
    if ( m_xHideTimer.DoneTimer() )
    { SetShow( false ); }

    if ( m_xShowTimer.DoneTimer() )
    { SetShow( true ); }

    ProcessMoveAbout( dwCostTime );
}

Msg* NpcBase::FirstSightOnMe( char* szMsgBuffer, unsigned int nBuffSize)
{
    BaseCharacter::FirstSightOnMe( szMsgBuffer, nBuffSize );

    MsgNPCEnterMySight* pMsg = (MsgNPCEnterMySight*)szMsgBuffer;
    strncpy_s( pMsg->szDisplayName, GetCharName(), sizeof( pMsg->szDisplayName ) - 1);
    pMsg->stId       = GetModelId();
    pMsg->bShow      = GetShow();
    pMsg->stCharType = Object_Npc;
    pMsg->fMoveStep  = GetMoveStep();
    return pMsg;
}

void NpcBase::EnterMySight( BaseCharacter* pWho )
{ // 进入我的视野
    if (pWho->IsPlayer())
    { ++m_n9AreaPlayerCnt; }
}

void NpcBase::ExitMySight( BaseCharacter* pWho )
{ // 离开我的视野
    if (pWho->IsPlayer() && m_n9AreaPlayerCnt > 0)
    { --m_n9AreaPlayerCnt; }
}

void NpcBase::MoveStopToTalk()
{
    if ( GameTime::IsPassCurrentTime( m_dwTalkTimeOut, TALK_TIMEOUT ) )
    {
        SetMoveState( EAction_Moving );
        m_nTalkCount = 0;
    }
}

void NpcBase::ProcessMoveAbout( DWORD dwCostTime )
{
    switch( m_enMoveState ) 
    {
    case EAction_Prepare:
        Prepare();
        break;
    case EAction_Moving:
        Moving( dwCostTime );
        break;
    case EAction_WillMoveNext:
        MoveWillMoveNext();
        break;
    case EAction_MoveNext:
        MoveMoveNext();
        break;
    case EAction_Waiting:
        Waiting();
        break;
    case EAction_StopToTalk:
        MoveStopToTalk();
        break;
    case EAction_Stop:
        Stop();
        break;
    default:
        break;
    }
}

void NpcBase::ProcessSubAction( DWORD dwCostTime )
{
    
}

SMovePos* NpcBase::GetCurrentStepMovePos()
{
    if ( _Route.allMovePos.empty() )
    { return NULL; }

    if ( m_nCurStep < 0 || m_nCurStep >= _Route.allMovePos.size() )
    { m_nCurStep = 0; }

    SMovePos* pPath = &_Route.allMovePos[m_nCurStep];
    return pPath;
}

void NpcBase::UpdateMoveStateToPlayer( BaseCharacter* pPlayer )
{
    if ( GetMoveState() != EAction_Moving )
    { return; }

    SMovePos* pPath = GetCurrentStepMovePos();
    if ( NULL == pPath)
    { return; }

    MsgUnPlayerMovingToPos msg;
    msg.header.stID = GetID();
    msg.vStartPos.x = GetFloatX();
    msg.vStartPos.y = GetFloatY();
    msg.vStartPos.z = 0;
    msg.vEndPos.x = pPath->fX;
    msg.vEndPos.y = pPath->fY;
    msg.vEndPos.z = 0;
    if ( pPlayer )
    {
        GettheServer().SendMsgToSingle( &msg, pPlayer );
    }
    else
    {
        GettheServer().SendMsgToView( &msg, GetID(), false );
    }
}

void NpcBase::MoveWillMoveNext()
{
    SMovePos* pPath = GetCurrentStepMovePos();
    if ( pPath == NULL )
    { 
        SetMoveState( EAction_Stop );
        return;
    }

    if ( strlen( pPath->szActionName ) != 0 )
    {
        // 发送给客户端做动作的消息
        MsgNpcPlayAnim msg;
        msg.header.stID = GetID();
        msg.nNpcId = GetID();
        char szName[64];
        sprintf_s( szName, sizeof(szName)-1, pPath->szActionName );
        HelperFunc::SafeNCpy( msg.szActionName, szName, MsgNpcPlayAnim::eActionNameLength );
        msg.nLoopTimes = 1;
        GettheServer().SendMsgToView( &msg, GetID(), false );
    }

    if ( pPath->dwTime != 0xffffffff )
    {
        m_dwWaitingStartTime = HQ_TimeGetTime();
        SetMoveState( EAction_Waiting );
    }
    else
    {
        SetMoveState( EAction_Stop );
    }
}

void NpcBase::Waiting()
{
    SMovePos* pMovePos = GetCurrentStepMovePos();
    if ( pMovePos == NULL )
    {
        SetMoveState( EAction_Stop ); 
        return;
    }

    if ( GameTime::IsPassCurrentTime( m_dwWaitingStartTime, pMovePos->dwTime ) )
    {
        SetMoveState( EAction_MoveNext );
    }
}

void NpcBase::Stop()
{

}

void NpcBase::Prepare()
{
    SetMoveState( EAction_Stop );
    return;
}

void NpcBase::Moving( DWORD dwCostTime )
{
    float fMovestep = GetMoveSpeed()*((float)dwCostTime/1000);

    SMovePos* pMovePos = GetCurrentStepMovePos();
    if ( pMovePos == NULL )
    {
        SetMoveState( EAction_Stop ); 
        return;
    }

    float fx = pMovePos->fX - GetFloatX();
    float fy = pMovePos->fY - GetFloatY();
    D3DXVECTOR3 vecDistance( fx, fy, 0 );
    float fDistance = D3DXVec3Length( &vecDistance );
    if ( fDistance <= fMovestep )
    {
        SetMoveState( EAction_WillMoveNext );
        fMovestep = fDistance;
    }

    D3DXVECTOR3 vDir = D3DXVECTOR3( fx, fy, 0 );
    D3DXVec3Normalize( &vDir, &vDir );
    SetDirX( vDir.x );
    SetDirY( vDir.y );

    float fMoveX = fMovestep*vDir.x;
    float fMoveY = fMovestep*vDir.y;

    SetFloatXF( GetFloatX() + fMoveX );
    SetFloatYF( GetFloatY() + fMoveY );
    theGameWorld.OnRefreshNewArea( GetID() );   

    if ( GameTime::IsPassCurrentTime( m_dwLastUpdateMoveStateToPlayerTime, 1000 ) )
    {
        UpdateMoveStateToPlayer();
        m_dwLastUpdateMoveStateToPlayerTime = HQ_TimeGetTime();
    }
}

void NpcBase::MoveMoveNext()
{
    ++m_nCurStep;

    SMovePos* pPath = GetCurrentStepMovePos();

    if ( pPath == NULL )
    {
        SetMoveState( EAction_Stop ); 
        return;
    }

    SetMoveSpeed( pPath->fV );
    SetMoveStep( pPath->fStep );
    SetMoveState( EAction_Moving );

    UpdateMoveStateToPlayer();
}

// x:1 y:2 v:1 s:1 a:0 t:1000
// x:3 y:4 v:1 s:1 a:1 t:2000
bool NpcBase::InitRoute()
{
    if ( !_pNpcInfo)
    { return false; }

    bool bResult = GetRouteManager().GetRouteInfo( _pNpcInfo->mapId, _pNpcInfo->movePath, _Route );
    if ( !bResult )
    { return false; }

    return true;
}

void NpcBase::BeginTalk()
{
    m_nTalkCount++;
    if ( GetMoveState() != EAction_Stop )
    {
        SetMoveState( EAction_StopToTalk );
        MsgUnPlayerVerifyPos msg;
        msg.header.stID = GetID();
        msg.vPos.x      = GetFloatX();
        msg.vPos.y      = GetFloatY();
        msg.vPos.z      = 0;
        GettheServer().SendMsgToView( &msg, GetID(), false );
    }

    //MsgUnPlayerVerifyPos msg;
    //msg.header.stID = GetID();
    //msg.vPos.x      = GetFloatX();
    //msg.vPos.y      = GetFloatY();
    //msg.vPos.z      = 0;
    //GettheServer().SendMsgToView( &msg, GetID(), true );

    m_dwTalkTimeOut = HQ_TimeGetTime();
}

void NpcBase::EndTalk()
{
    m_nTalkCount--;
    if ( m_nTalkCount < 0 )
    { m_nTalkCount = 0; }

    if ( m_nTalkCount == 0 )
    {
        if ( GetMoveState() == EAction_StopToTalk )
        {
            SetMoveState( EAction_Moving );
            if ( _Route.allMovePos.size() <= 0 )
            {
                SetMoveState( EAction_Stop );
                return;
            }

            UpdateMoveStateToPlayer();
        }
    }
}

void NpcBase::MoveNext()
{
    if ( GetMoveState() == EAction_Stop )
    { SetMoveState( EAction_MoveNext ); }
}

void NpcBase::SetLastAnimName( const char* szName )
{
    if ( !szName )
    { return; }
    m_strLastAnimName = szName;
}

const char* NpcBase::GetLastAnimName()
{
    return m_strLastAnimName.c_str();
}

bool NpcBase::SetDisappearTime( DWORD DisappearTime )
{
   if ( _pNpcInfo->type != eNT_ScriptNpc || DisappearTime == 0)
   { return false; }

   m_DisappearTime = DisappearTime;
   _disappearTime.StartTimer( HQ_TimeGetTime(), m_DisappearTime );
   return true;
}

void NpcBase::OnExit( Msg* pMsg, unsigned char exitType/* = ET_ExitGame*/)
{
    GameObjectId stID = GetID();

    //确保附近有玩家才发送，以提高性能
    if (m_n9AreaPlayerCnt != 0)
    { GettheServer().SendMsgToView( pMsg, GetID(), false ); }

    // 从场景中删掉
    theGameWorld.OnDelCharacter( stID );

    // 从释放回内存池
    theRunTimeData.ReleaseObject(stID);
}

void NpcBase::CallQuestScript( NpcBase::RelateQuestInfo* pInfo, GamePlayer* pPlayer, int nNpcID )
{
    if ( pInfo == NULL )
    { return; }

    char pszFilename[MAX_PATH] = {0};
    sprintf_s( pszFilename, sizeof(pszFilename)-1, QUESTS_SCRIPT_FILEPATH_FORMAT, pInfo->stQuestId );
    if ( pInfo->m_nVMId == -1 )
    { pInfo->m_nVMId = GetScriptMgr()->CreateVM( ST_QUEST, pszFilename, -1 ); }

    if ( pInfo->m_nVMId == -1 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "调用[%s]任务脚本失败", pszFilename );
        return;
    }

    GetScriptMgr()->StartupVM( ST_QUEST, pInfo->m_nVMId, pPlayer, false, pInfo->stEnter, nNpcID );
}
