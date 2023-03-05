#include "TeamManager.h"
#include "GlobalDef.h"
#include "BasePlayer.h"
#include "ShareData.h"
#include "helper.h"
#include "FuncPerformanceLog.h"
#include "GameServer.h"
#include "XmlStringLanguage.h"
//#include "LogFileObjectName.h"
#include "QuestManager.h"

//////////////////////////////////////////////////////////////////////////////
//TeamEx
TeamEx::TeamEx() : m_dwSessionId(0), m_bCorps(false) , m_nAssignModeType(AssignMode_FreeMode), m_nAssignIndex(0),
                   m_dwNextUpdateToCenterTime(0), m_dwStopUpdateTeamMemberTime(0), m_chAssignItemLevel(eIL_Choiceness)
{
    m_listTeamMember.clear();
    m_mapManipleCount.clear();

    m_dwNextUpdateSelfTime = HQ_TimeGetTime() + TeamSelfUpdate;
    m_dwNextUpdateTime = 0;
    m_dwTeamHeaderID = ErrorUnsignedLongID;
}
 
TeamEx::~TeamEx()
{

}

TeamEx::TeamMember* TeamEx::GetTeamMember(DWORD dwDataBaseId)
{
    TeamIter iter = find(m_listTeamMember.begin(), m_listTeamMember.end(), dwDataBaseId);
    if (iter == m_listTeamMember.end()) { return NULL; }

    return &(*iter);
}

TeamEx::TeamMember* TeamEx::GetTeamMemberByIndex(unsigned int nIndex)
{
    if (nIndex < 0 || nIndex >= TeamMemberCount()) { return NULL; }

    TeamIter iter = m_listTeamMember.begin();
    advance(iter, nIndex); // 计算偏移

    return &(*iter);
}

DWORD TeamEx::GetTeamMemberDataBaseIdByIndex(unsigned int nIndex)
{
    TeamMember* pMember = GetTeamMemberByIndex(nIndex);

    return ( pMember != NULL ? pMember->GetMemberID() : ErrorUnsignedLongID );
}

TeamEx::TeamMember* TeamEx::GetManipleHeader(short stManipleId)
{
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end  = m_listTeamMember.end();

    for ( ; iter != end; ++iter)
    {
        if(iter->GetManipleID() == stManipleId && iter->GetManipleHeader() )
        {
            return &(*iter);
        }
    }
    return NULL;
}
                                        
TeamEx::TeamMember* TeamEx::GetTeamHeader()
{
    return GetTeamMember( GetTeamHeaderID() );
}

bool TeamEx::UpdateTeamToCorps()
{
    if (TeamMemberCount() == TeamMaxManipleMember)    //只有人数达到5人才允许扩充到团
    {
        m_bCorps = true;
        
        MsgReqCovCorps xMsg;
        SendMessageToTeamMember(&xMsg);
        
        return true;
    }

    return false;
}


bool TeamEx::IsTeamFull()
{
    bool bIsFull = false;

    if (!m_bCorps)
    {
        if (TeamMemberCount() >= TeamMaxManipleMember)
        {
            bIsFull = true;
        }
    }
    else
    {
        if (TeamMemberCount() >= TeamMaxMember)
        {
            bIsFull = true;
        }
    }

    return bIsFull;
}

bool TeamEx::IsInTeam(DWORD dwDataBaseId)
{
    TeamIter iter = find(m_listTeamMember.begin(), m_listTeamMember.end(), dwDataBaseId);

    return (iter != m_listTeamMember.end());
}

bool TeamEx::IsManipleHeader(DWORD dwDataBaseId)
{
    TeamIter iter = find(m_listTeamMember.begin(), m_listTeamMember.end(), dwDataBaseId);
    if (iter != m_listTeamMember.end())
    {
        return iter->GetManipleHeader();
    }

    return false;
}

short TeamEx::GetManiple(DWORD dwDataBaseId)
{
    TeamMember *pMember = GetTeamMember(dwDataBaseId);

    return (pMember != NULL ? pMember->GetManipleID() : -1); 
}

bool TeamEx::IsTeamHeader(DWORD dwDataBaseId)
{
    if ( dwDataBaseId == ErrorUnsignedLongID )
    { return false; }

    return dwDataBaseId == GetTeamHeaderID();
}

bool TeamEx::SetTeamHeader(DWORD dwDataBaseId, bool bQuickUpdate /* = true */)
{
    DWORD dwLastHeaderID = GetTeamHeaderID();
    if ( dwLastHeaderID == dwDataBaseId )
    { return false; }  //已经是队长的

    if ( !IsInTeam( dwDataBaseId ) )
    { return false; }

    SetTeamHeaderID( dwDataBaseId );            // 设置新队长

    if ( bQuickUpdate )
    {
        m_dwStopUpdateTeamMemberTime = HQ_TimeGetTime() + 1000;         //1秒不更新其他服务器发送过来的队长信息
    }

    RunTeamUpdate( bQuickUpdate );

    //通知附近玩家,队长信息已经改变
    GamePlayer* pLastHeader = (GamePlayer*) RunTimeData::GetInstance().GetGamePlayerByDBID( dwLastHeaderID );
    if ( pLastHeader != NULL )        
    { // 已经不是队长
        pLastHeader->TellTeamInfoChange( ETP_Member );
    }

    GamePlayer* pNowHeader = (GamePlayer*) RunTimeData::GetInstance().GetGamePlayerByDBID( dwDataBaseId );
    if ( pNowHeader != NULL )
    {  //已经变更为队长
        pNowHeader->TellTeamInfoChange( ETP_Leader );
    }

    return true;
}

//设置某队员为小队长
bool TeamEx::SetManipleHeader(DWORD dwDataBaseId)
{
    TeamMember* pTeamMember = GetTeamMember(dwDataBaseId);
    if (pTeamMember == NULL) { return false; } //不在队伍中

    //取消掉原来的小队长
    TeamMember* pManipleHeader = GetManipleHeader(pTeamMember->GetManipleID());
    DWORD dwSrcManipleHeaderId = -1;
    if (pManipleHeader != NULL)
    {
        if (pManipleHeader->GetMemberID() == dwDataBaseId)
        { return false; }        //是同一个人

        pManipleHeader->SetManipleHeader( false );
        dwSrcManipleHeaderId = pManipleHeader->GetMemberID();
    }

    pTeamMember->SetManipleHeader( true );
    
    MsgRetFlagHeaderFromTeam xRet;
    xRet.bSrcess    = true;
    xRet.dwSrcID    = dwSrcManipleHeaderId;   //注意, 这里是db id, 需要改下协议
    xRet.dwDestID   = dwDataBaseId;

    SendMessageToTeamMember(&xRet);

    return true;
}

//切换队员的小队
bool TeamEx::ChangeTeamMemberManiple(DWORD dwDataBaseId, short stManipleId)
{
    if (dwDataBaseId == ErrorUnsignedLongID || stManipleId < 0 || stManipleId >= TeamMaxManipleCount) { return false; }

    TeamMember* pTeamMember = GetTeamMember( dwDataBaseId );
    if ( pTeamMember == NULL )
    { return false; }

    if ( IsManipleFull(stManipleId) ) 
    { return false; }

    if ( pTeamMember->GetManipleHeader() )  // 原先是小队长
    {
        //找到一个队员来继承小队长
        TeamIter iter = m_listTeamMember.begin();
        TeamIter end = m_listTeamMember.end();
        for ( ; iter != end; ++iter)
        {
            if ( iter->GetMemberID() != pTeamMember->GetMemberID() )
            {
                if ( iter->GetManipleID() == pTeamMember->GetManipleID() )
                {
                    iter->SetManipleHeader( true );
                    break;
                }
            }            
        }

        pTeamMember->SetManipleHeader( false );    
    }
    UpdateManipleCount( pTeamMember->GetManipleID(), false );    //更新原来小队数量

    //////////////////////////////////////////////////////////////////////////////////
    MsgMovePlayerFromManiple xMsg;
    xMsg.dwSrc = dwDataBaseId;
    xMsg.stSrcManiple = stManipleId;

    SendMessageToTeamMember(&xMsg);
    ////////////////////////////////////////////////////////////////////////////////////

    pTeamMember->SetManipleID( stManipleId );    
    UpdateManipleCount( stManipleId );                //更新现在小队数量

    return true;
}

//交换两个队员的小队
bool TeamEx::ExChangeTeamMeberManiple(DWORD dwSrcDataBaseId, DWORD dwDestDataBaseId)
{
    TeamMember* pSrcMember = GetTeamMember(dwSrcDataBaseId);
    if (pSrcMember == NULL) { return false; }

    TeamMember* pDestMember = GetTeamMember(dwDestDataBaseId);
    if (pDestMember == NULL) { return false; }

    //如果在同一个小队,不执行
    if ( pDestMember->GetManipleID() == pDestMember->GetManipleID() ) 
    { return false; }

    //更换小队ID
    short stTempManipleId = pDestMember->GetManipleID();
    pDestMember->SetManipleID( pSrcMember->GetManipleID() );
    pSrcMember->SetManipleID( stTempManipleId );

    //更换小队长标志
    bool bTempbManiple = pDestMember->GetManipleHeader();
    pDestMember->SetManipleHeader( pSrcMember->GetManipleHeader() );
    pSrcMember->SetManipleHeader( bTempbManiple );

    ///////////////////////////////////////////////////////////////////////////////////////
    MsgChangeManipleFromTeamRet xMsg;
    xMsg.bSrcess = true;
    xMsg.dwSrc = dwSrcDataBaseId;
    xMsg.stSrcManiple = pSrcMember->GetManipleID();
    xMsg.dwDest = dwDestDataBaseId;
    xMsg.stDestManiple = pDestMember->GetManipleID();

    SendMessageToTeamMember(&xMsg);
    /////////////////////////////////////////////////////////////////////////////////////

    return true;
}

DWORD TeamEx::GetCurrentAssignIndex()
{
    if (m_nAssignIndex < 0 || m_nAssignIndex >= TeamMemberCount())
    {
        m_nAssignIndex = 0;
    }

    return GetTeamMemberDataBaseIdByIndex(m_nAssignIndex++);
}


//添加一个队员到队伍中
bool TeamEx::AddTeamMember( TeamMember& xMember, bool bIsTeamHeader )
{
    if ( xMember.IsError() )            //参数错误  
    { 
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "AddTeamMember TeamMember [%u][%s] Error", xMember.GetMemberID(), xMember.GetName() );
        return false; 
    }              
    
    if ( IsInTeam( xMember.GetMemberID() ) )         //已经在队伍中 
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "AddTeamMember IsInTeam [%u][%s] Error", xMember.GetMemberID(), xMember.GetName() );
        return false; 
    }             

    if ( IsTeamFull() )
    { 
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "AddTeamMember IsTeamFull [%u][%s] Error", xMember.GetMemberID(), xMember.GetName() );
        return false; 
    }

    if ( bIsTeamHeader )
    {
        SetTeamHeaderID( xMember.GetMemberID() );
    }

    m_listTeamMember.push_back( xMember );
    UpdateManipleCount( xMember.GetManipleID() );            //更新小队数量
    ///////////////////////////////////////////////////////////////////////////////
    return true;
}

//返回队伍是否需要解散  bSendCenterServerReq=请求 bSendCenterServerAck=确认
bool TeamEx::RemoveTeamMember(DWORD dwDataBaseId)
{
    bool bReleaseTeam = false;

    TeamMember* pTeamMember = GetTeamMember(dwDataBaseId);
    if (pTeamMember == NULL) { return false; }
    
    if ( TeamMemberCount() <= 2 )  //只有两个人的队伍, 踢掉一个 队伍解散
    {
        MsgExitTeam xExitTeamMsg;
        xExitTeamMsg.bIsDisband = true;
        TeamIter iter = m_listTeamMember.begin();
        TeamIter end = m_listTeamMember.end();
        for ( ; iter != end; ++iter)
        {
            //发送消息
            GamePlayer* pPlayerChar = (GamePlayer*) RunTimeData::GetInstance().GetGamePlayerByDBID(iter->GetMemberID());
            if( pPlayerChar != NULL )
            {
                pPlayerChar->SetTeamSessionID( 0 );
                GettheServer().SendMsgToSingle(&xExitTeamMsg, pPlayerChar);

                pPlayerChar->TellTeamInfoChange( ETP_None );
            }
        }

        m_listTeamMember.clear();    
        m_mapManipleCount.clear();
        bReleaseTeam = true;    
    }
    else 
    {
        GamePlayer* pPlayerChar = (GamePlayer*)RunTimeData::GetInstance().GetGamePlayerByDBID( dwDataBaseId );
        if ( pPlayerChar != NULL )
        {
            pPlayerChar->SetTeamSessionID( 0 );
            //通知该队员离开队伍
            MsgExitTeam xExitTeamMsg;
            GettheServer().SendMsgToSingle(&xExitTeamMsg, pPlayerChar);

            pPlayerChar->TellTeamInfoChange( ETP_None );
        }

        UpdateManipleCount(pTeamMember->GetManipleID(), false);  //更新小队数量

        TeamIter iter = find( m_listTeamMember.begin(), m_listTeamMember.end(), dwDataBaseId );
        if ( iter != m_listTeamMember.end() )
        {
            m_listTeamMember.erase(iter);
        }
        
        //通知其他玩家
        MsgDeleteTeamMember xMsg;
        xMsg.dwMemberID = dwDataBaseId;
        SendMessageToTeamMember(&xMsg, dwDataBaseId, false);
    }
   
    return bReleaseTeam;
}

//解散队伍
bool TeamEx::DisbandTeam()
{
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();

    MsgExitTeam xExitTeamMsg;
    xExitTeamMsg.bIsDisband = true;
    for ( ; iter != end; ++iter )
    {
        //发送队伍解散消息
        GamePlayer* pPlayerChar = (GamePlayer*)RunTimeData::GetInstance().GetGamePlayerByDBID(iter->GetMemberID());
        if ( pPlayerChar != NULL )
        {
            pPlayerChar->SetTeamSessionID( 0 );
            GettheServer().SendMsgToSingle( &xExitTeamMsg, pPlayerChar );
            
            pPlayerChar->TellTeamInfoChange( ETP_None );
        }
    }

    m_listTeamMember.clear();
    m_mapManipleCount.clear();

    return true;
}

//以前只有发送队伍的MsgChat::CHAT_TYPE_GAMEPROMPT 消息, 如果是CHAT_TYPE_TERM 聊天呢.
void TeamEx::SendChatMessageToTeamMember(const char* chat, DWORD dwExcept /* = -1 */, bool bSendToCenter /* = true */)
{
    bool bSomeOneOnAnotherServer = false;

    MsgChat xMsgChat(MsgChat::CHAT_TYPE_GAMEPROMPT);
    xMsgChat.SetString(chat);

    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();
    for( ; iter != end; ++iter)
    {
        if(iter->GetMemberID() == dwExcept)
        { continue; }        //不给自己发消息

        GamePlayer* pChar = (GamePlayer*)RunTimeData::GetInstance().GetGamePlayerByDBID(iter->GetMemberID());
        if( pChar != NULL )
        {
            GettheServer().SendMsgToSingle(&xMsgChat, pChar);
        }
        else
        {
            bSomeOneOnAnotherServer = true;            
        }
    }

    //不在本服务器
    if (bSomeOneOnAnotherServer && bSendToCenter)
    {
        S2STransmit::STeam xTeam;
        xTeam.dwSessionID = m_dwSessionId;

        GettheServer().SendMsgToTeamRemote(&xMsgChat, xTeam);
    }
}

void TeamEx::SendMessageToTeamMember(Msg *pMsg, DWORD dwExcept/* = -1*/, bool bCenterServerAck/* = true*/)
{
    char szTemp[1024] = {0};
    GamePlayer* pCharAddPeople = NULL;

    bool bSomeOneOnAnotherServer = false;
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end  = m_listTeamMember.end();
    for( ; iter != end; ++iter )
    {
        if (iter->GetMemberID() != dwExcept)
        {
            BaseCharacter *pChar = RunTimeData::GetInstance().GetGamePlayerByDBID(iter->GetMemberID());
            if (pChar != NULL)
            {
                GettheServer().SendMsgToSingle( pMsg, pChar );

                if ( pMsg->GetType() == MSG_ADDTEAMMEMBER && pChar->GetStatus() == CS_LOADINGMAP )
                {
                    // 有时客户端在加载地图的时候, 有人进入队伍, 刚加入的队员不在列表里, 说明没有收到这个消息
                    pChar->Log( "玩家[%s][%d]正在加载地图时有人加入队伍.", iter->GetName(), iter->GetMemberID() );  
                }
            }
            else
            {
                //在其他服务器                
                bSomeOneOnAnotherServer = true;                                
            }
        }
    }

    //新加入队员,有在别的服务器上的,就发消息给CenterServer
    if ( bSomeOneOnAnotherServer && bCenterServerAck )  
    {
        if( pMsg->GetType() == MSG_CHAT )
        {
            S2STransmit::STeam xTeam;
            xTeam.dwSessionID = m_dwSessionId;
            GettheServer().SendMsgToTeamRemote( pMsg, xTeam );
        }
        //其他消息
    }
}

void TeamEx::SendMemberInfoToTeamMember(Msg *pMsg, DWORD dwExcept, bool bSendToCenter/* = true*/)
{
    bool bSomeOneOnAnotherServer =  false;

    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();
    for ( ; iter != end; ++iter)
    {
        if ( iter->GetMemberID() == dwExcept )
        { continue; }
        GamePlayer* pMemberChar = (GamePlayer*)RunTimeData::GetInstance().GetGamePlayerByDBID(iter->GetMemberID());
        if( pMemberChar != NULL )  //队员在本服
        {
            GettheServer().SendMsgToSingle( pMsg, pMemberChar );    
        }
        else //不在本服务器
        {
            bSomeOneOnAnotherServer = true;
        }
    }

    //发送给CenterServer中转
    if (bSomeOneOnAnotherServer && bSendToCenter && HQ_TimeGetTime() > m_dwNextUpdateToCenterTime)       
    {
        GS2CSPlayerUpdateTeamMemberInfo xMemberInfo;
        Msg_Team_PlayerInfo* pTeamPlayInfo = (Msg_Team_PlayerInfo*) pMsg;    

        xMemberInfo.dwSessionId     = m_dwSessionId;
        xMemberInfo.dwDataBaseId    = pTeamPlayInfo->dwDataBaseId;
        xMemberInfo.nHp             = pTeamPlayInfo->nHp;
        xMemberInfo.nHpMax          = pTeamPlayInfo->nHpMax;
        xMemberInfo.nMp             = pTeamPlayInfo->nMp;
        xMemberInfo.nMpMax          = pTeamPlayInfo->nMpMax;
        xMemberInfo.Profession      = pTeamPlayInfo->Profession;
        xMemberInfo.stLevel         = pTeamPlayInfo->stLvl;
        xMemberInfo.dwMapID         = pTeamPlayInfo->dwMapID;
        xMemberInfo.x               = pTeamPlayInfo->x;
        xMemberInfo.y               = pTeamPlayInfo->y;
        xMemberInfo.fx              = pTeamPlayInfo->fx;
        xMemberInfo.fy              = pTeamPlayInfo->fy;
        xMemberInfo.stManiple       = pTeamPlayInfo->stManiple;
        xMemberInfo.bManipleHeader  = pTeamPlayInfo->bHeader2;
        xMemberInfo.bTeamHeader     = pTeamPlayInfo->bHeader;

        GettheServer().SendMsgToCenterServer(&xMemberInfo);
    }
}

//bRunUpdate = true时候需要立即执行,
bool TeamEx::RunTeamUpdate(bool bQuickUpdate /* = false */)
{
    DWORD dwNowTime = HQ_TimeGetTime();

    if ( bQuickUpdate )     //立即执行
    {
        m_dwNextUpdateToCenterTime = 0;
        m_dwNextUpdateTime = 0;    
    }

    //把队员信息下发给客户端
    if( m_dwNextUpdateTime > dwNowTime ) 
    { return true; }
    m_dwNextUpdateTime = dwNowTime + TeamUpdateInterval;

    std::vector< uint32 > vecDeleteMember;
    vecDeleteMember.clear();

    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();
    for ( ; iter != end; ++iter )
    {
        GamePlayer* pMemberChar = (GamePlayer*)RunTimeData::GetInstance().GetGamePlayerByDBID( iter->GetMemberID() );
        if( pMemberChar == NULL ) 
        { continue; } //不在本服的不发送

        if ( pMemberChar->GetTeamSessionID() != GetTeamSessionID() )        // 如果该玩家身上的sessionid 和 队伍的不一样, 踢除这个队员
        {
            vecDeleteMember.push_back( iter->GetMemberID() );
            LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_ERROR, "玩家[%s]身上的sessionid[%u] 和 队伍[%u]的不一样!", pMemberChar->GetPlayerName(), pMemberChar->GetTeamSessionID(), GetTeamSessionID() );
            continue;
        }

        Msg_Team_PlayerInfo xInfo;
        xInfo.header.stID   = pMemberChar->GetID();
        xInfo.dwDataBaseId  = iter->GetMemberID();
        xInfo.bHeader       = IsTeamHeader( iter->GetMemberID() );
        xInfo.nHp           = pMemberChar->GetHP();
        xInfo.nMp           = pMemberChar->GetMP();
        xInfo.nHpMax        = pMemberChar->GET_VALUE( iHpMax, final );
        xInfo.nMpMax        = pMemberChar->GET_VALUE( iMpMax, final );
        xInfo.Profession    = pMemberChar->GetProfession();
        xInfo.stLvl         = pMemberChar->GetLevel();
        xInfo.dwMapID       = pMemberChar->GetMapID();          //客户端使用的是mapconfig中的地图id
        xInfo.x             = pMemberChar->GetX();
        xInfo.y             = pMemberChar->GetY();
        xInfo.fx            = pMemberChar->GetFloatX();
        xInfo.fy            = pMemberChar->GetFloatY();
        xInfo.stManiple     = iter->GetManipleID();
        xInfo.bHeader2      = IsManipleHeader( iter->GetMemberID() );
        
        SendMemberInfoToTeamMember( &xInfo, ErrorUnsignedLongID, true );    // 自己也要更新
    }

    if ( !vecDeleteMember.empty() )
    {
        for ( std::vector< uint32 >::iterator iter = vecDeleteMember.begin(); iter != vecDeleteMember.end(); ++iter )
        {
            theTeamManager.RemoveFromTeam( GetTeamSessionID(), (*iter), true );
        }
    }
    
    return true;
}

//更新小队数量信息
void TeamEx::UpdateManipleCount(short stManipleId, bool bAdd /* = true */)
{
    if (stManipleId < 0 || stManipleId >= TeamMaxManipleCount) { return; }

    ManipleCountIter iter = m_mapManipleCount.find(stManipleId);
    if (iter == m_mapManipleCount.end())
    {
        if (bAdd) //增加队员
        {
            m_mapManipleCount.insert(make_pair(stManipleId, 1));
        }
    }
    else
    {
        if (bAdd)
        {
            ++iter->second;
            if (iter->second > TeamMaxManipleMember)
            {
                iter->second = TeamMaxManipleMember;
            }
        }
        else
        {
            --iter->second;
            if (iter->second < 0)
            {
                iter->second = 0;
            }
        }
    }
}

unsigned int TeamEx::GetManipleCount(short stManipleId)
{

    ManipleCountIter iter = m_mapManipleCount.find(stManipleId);
    if (iter != m_mapManipleCount.end())
    {
        return iter->second;
    }

    return 0;
}

bool TeamEx::IsManipleFull(short stManipleId)
{
    return GetManipleCount(stManipleId) == TeamMaxManipleMember;
}

unsigned int TeamEx::GetTeamMemberCountInMap(unsigned int nMapId, float fX, float fY)
{
    unsigned int nCount = 0;

    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();

    for ( ; iter != end; ++iter)
    {
        BaseCharacter* pMember = RunTimeData::GetInstance().GetGamePlayerByDBID(iter->GetMemberID());
        if (pMember == NULL)
        { continue; }

        float x = fX - pMember->GetFloatX();
        float y = fY - pMember->GetFloatY();
        float dist = sqrtf( x*x + y*y );

        if (pMember->GetMapID() == nMapId && dist <= TEAM_EXP_DIS)
        {
            ++nCount;
        }            
    }

    return nCount;
}

bool TeamEx::IsAllTeamMemberGreaterMapLevel(unsigned int nLevel)
{
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();
    for ( ; iter != end; ++iter)
    {
        BaseCharacter* pMember = RunTimeData::GetInstance().GetGamePlayerByDBID(iter->GetMemberID());
        if ( pMember == NULL || pMember->GetLevel() < nLevel )
        {
            return false;
        }
    }

    return true;
}

bool TeamEx::IsAllTeamMemberHaveQuest( int nQuestID,  unsigned long &dwID )
{
    dwID = ErrorUnsignedLongID;
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();
    for ( ; iter != end; ++iter)
    {
        GamePlayer* pMember = (GamePlayer*) RunTimeData::GetInstance().GetGamePlayerByDBID(iter->GetMemberID());
        if ( pMember == NULL || pMember->GetQuestState( nQuestID ) != QuestManager::eQuestCasterState )
        {
            dwID = iter->GetMemberID();
            return false;
        }
    }

    return true;
}

void TeamEx::GetTeamMemberInMapArea(unsigned int nMapID, float fX, float fY, std::vector<uint32>& vecTeamMemberID)
{
    vecTeamMemberID.clear();
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();

    for ( ; iter != end; ++iter)
    {
        BaseCharacter* pMember = RunTimeData::GetInstance().GetGamePlayerByDBID(iter->GetMemberID());
        if (pMember == NULL) { continue; }

        float x = fX - pMember->GetFloatX();
        float y = fY - pMember->GetFloatY();
        float dist = sqrtf( x*x + y*y );

        if (pMember->GetMapID() == nMapID && dist <= TEAM_EXP_DIS)
        {
            vecTeamMemberID.push_back(iter->GetMemberID());
        }            
    }
}

//返回有效范围内队员的总等级
unsigned int TeamEx::GetTeamMemberLevelDistance(unsigned int nMapID, float fX, float fY, int& nMinLevel, int& nMaxLevel)
{
    nMinLevel = 10000;
    nMaxLevel = 0;

    unsigned int nTotalLevel = 0;
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();
    for ( ; iter != end; ++iter)
    {
        BaseCharacter* pMember = RunTimeData::GetInstance().GetGamePlayerByDBID(iter->GetMemberID());
        if (pMember == NULL) { continue; }

        float x = fX - pMember->GetFloatX();
        float y = fY - pMember->GetFloatY();
        float dist = sqrtf( x*x + y*y );

        if (pMember->GetMapID() == nMapID && dist <= TEAM_EXP_DIS)
        {
            if (pMember->GetLevel() > nMaxLevel)
            {
                nMaxLevel = pMember->GetLevel();
            }
            
            if (pMember->GetLevel() < nMinLevel)
            {
                nMinLevel = pMember->GetLevel();
            }

            nTotalLevel += pMember->GetLevel();
        }            
    }

    return nTotalLevel;
}

//队伍人数对应的经验比率表
float TeamEx::GetTeamExpPercent(unsigned int nTeamCount, bool bIsEcType)
{
    const static float fExpPercent[][TeamMaxManipleMember] = 
    {
        { 1.0f, 0.9f, 0.8f, 0.8f, 0.8f, 0.8f, },        // 普通地图经验比率
        { 1.0f, 1.2f, 1.4f, 1.6f, 1.8f, 2.0f, },        // 副本地图经验比率
    };

    if (nTeamCount == 0)
        nTeamCount = 1;
    if (nTeamCount > TeamMaxManipleMember)
        nTeamCount = TeamMaxManipleMember;

    return fExpPercent[bIsEcType][nTeamCount - 1];
}

bool TeamEx::CallAllTeamPlayerFlyToMapReq(unsigned int nMapID, float fX, float fY, float fDir /* = 0.0f */)
{
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();
    for ( ; iter != end; ++iter)
    {
        GamePlayer* pTeamPlayer = (GamePlayer*) RunTimeData::GetInstance().GetGamePlayerByDBID( iter->GetMemberID() );
        if ( pTeamPlayer != NULL )
        {
            pTeamPlayer->FlyToMapReq( nMapID, fX, fY, fDir );
        }
    }

    return true;
}

bool TeamEx::CallAllTeamPlayerChangeToMap( GameStage* pGameStage, int nTileX, int nTileY, float dir )
{
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();
    for ( ; iter != end; ++iter)
    {
        GamePlayer* pTeamPlayer = (GamePlayer*) RunTimeData::GetInstance().GetGamePlayerByDBID( iter->GetMemberID() );
        if ( pTeamPlayer != NULL )
        {
            pTeamPlayer->ChangeToMap( pGameStage, nTileX, nTileY, dir );
        }
    }

    return true;
}


unsigned short TeamEx::GetTeamTotalLevel()
{

    unsigned short ustLevel = 0;
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();
    for ( ; iter != end; ++iter)
    {
        GamePlayer* pTeamPlayer = (GamePlayer*) RunTimeData::GetInstance().GetGamePlayerByDBID( iter->GetMemberID() );
        if ( pTeamPlayer != NULL )
        {
            ustLevel += pTeamPlayer->GetLevel();
        }
    }

    return ustLevel;
}


unsigned long TeamEx::IsTeamExpired( int nVarId, int keyHour, int keyMinute, int minDuration )
{
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();
    for ( ; iter != end; ++iter)
    {
        GamePlayer* pTeamPlayer = (GamePlayer*) RunTimeData::GetInstance().GetGamePlayerByDBID( iter->GetMemberID() );
        if ( pTeamPlayer == NULL )
        { return iter->GetMemberID(); }

        if ( !pTeamPlayer->IsExpired( nVarId, keyHour, keyMinute, minDuration ) )
        {
            return iter->GetMemberID();
        }
    }

    return ErrorUnsignedLongID;
}

bool TeamEx::RecordTeamTime( int nVarId )
{
    bool bSuccess = true;
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();
    for ( ; iter != end; ++iter)
    {
        GamePlayer* pTeamPlayer = (GamePlayer*) RunTimeData::GetInstance().GetGamePlayerByDBID( iter->GetMemberID() );
        if ( pTeamPlayer == NULL ) { return false; }

        if ( !pTeamPlayer->RecordTimeVar( nVarId ) )
        {
            bSuccess = false;
        }
    }

    return bSuccess;
}

void TeamEx::ClearTeamExpiredVar( int nVarId, int keyHour, int keyMinute, int minDuration, int nClearVarId )
{
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();
    for ( ; iter != end; ++iter)
    {
        GamePlayer* pTeamPlayer = (GamePlayer*) RunTimeData::GetInstance().GetGamePlayerByDBID( iter->GetMemberID() );
        if ( pTeamPlayer == NULL )
        { continue; }

        if ( pTeamPlayer->IsExpired( nVarId, keyHour, keyMinute, minDuration ) )
        {
            pTeamPlayer->SetVar( nClearVarId, 0 );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*TeamManagerEx*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TeamManagerEx::TeamManagerEx()
{
    m_mapRunTeam.clear();
}

TeamManagerEx::~TeamManagerEx()
{
    for ( TeamMapIter iter = m_mapRunTeam.begin(); iter != m_mapRunTeam.end(); ++iter )
    {
        if ( iter->second != NULL )
        {
            CNewWithDebug< TeamEx >::Free( iter->second );
        }
    }
}

bool TeamManagerEx::AddTeam( uint32 dwSessionID, TeamEx* pTeam )
{
    if ( dwSessionID == 0 || pTeam == NULL )
    { return false; }

    TeamMapIter iter = m_mapRunTeam.find( dwSessionID );
    if ( iter != m_mapRunTeam.end() )
    {
        iter->second = pTeam;
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "Session ID[%u] Is exist !", dwSessionID );
        return false;
    }

    return m_mapRunTeam.insert( make_pair( dwSessionID, pTeam ) ).second;
}

bool TeamManagerEx::ReleaseTeam( uint32 dwSessionID )
{
    TeamMapIter iter = m_mapRunTeam.find( dwSessionID );
    if ( iter == m_mapRunTeam.end() )
    { return false; }

    CNewWithDebug< TeamEx >::Free( iter->second );
    m_mapRunTeam.erase( iter );

    return true;
}

void TeamManagerEx::RunTeamManagerUpdate()
{
    for ( TeamMapIter iter = m_mapRunTeam.begin(); iter != m_mapRunTeam.end(); )
    {
        if ( iter->second == NULL )
        {
            iter = m_mapRunTeam.erase( iter );
            continue;
        }

        if ( !iter->second->RunTeamUpdate() )
        {
            CNewWithDebug< TeamEx >::Free( iter->second );
            iter = m_mapRunTeam.erase( iter );
        }
        else
        {
            ++iter;
        }
    }
}

TeamEx* TeamManagerEx::GetTeam( uint32 dwTeamSessionID )
{
   TeamMapIter iter = m_mapRunTeam.find( dwTeamSessionID );
   if ( iter == m_mapRunTeam.end() )
   { return NULL; }

    return iter->second;
}

TeamEx* TeamManagerEx::CreateTeam( uint32 dwTeamSessionID, uint8 chAssignMode, uint8 chAssignItemLevel )
{
    if (dwTeamSessionID == 0)
    { return NULL; }

    TeamEx* pTeam = CNewWithDebug<TeamEx>::Alloc(1, "TeamManagerEx::CreateTeam中创建pTeam");
    if( pTeam == NULL )
    {    
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CreateTeam Error!" );
        return NULL;
    }

    pTeam->SetTeamSessionID( dwTeamSessionID );
    pTeam->SetAssignModeType( chAssignMode );
    pTeam->SetTeamAssiginItemLevel( chAssignItemLevel );

    AddTeam( dwTeamSessionID, pTeam );

    return pTeam;
}

//队长踢掉一个队员
bool TeamManagerEx::KickMemberFromTeam( uint32 dwSessionID, uint32 dwTeamHeaderId, uint32 dwTeamMemeberId )
{
    if ( dwTeamMemeberId == ErrorUnsignedLongID )
    { return false; }

    TeamEx *pTeam = GetTeam( dwSessionID );
    if( pTeam == NULL || !pTeam->IsTeamHeader(dwTeamHeaderId) ) 
    { return false; }

    GS2CSPlayerRemoveFromTeamReq xRemove;
    xRemove.dwSessionId  = pTeam->GetTeamSessionID();
    xRemove.dwDataBaseId = dwTeamMemeberId;
    xRemove.bKick = true;
    GettheServer().SendMsgToCenterServer(&xRemove);

    return true;
}

//移除一个队员,可能是掉线(包括队长)
bool TeamManagerEx::RemoveFromTeam( uint32 dwSessionID, uint32 dwDataBaseID, bool bKick /* = false */ )
{
    GS2CSPlayerRemoveFromTeamReq xRemove;

    xRemove.dwSessionId  = dwSessionID;
    xRemove.dwDataBaseId = dwDataBaseID;
    xRemove.bKick        = bKick;
    GettheServer().SendMsgToCenterServer( &xRemove );

    return true;
}

//如果还没有队员加入队伍的时候,这个函数调用将失败
bool TeamManagerEx::DisbandTeam( uint32 dwSessionID , uint32 dwTeamHeaderId )
{
    TeamEx *pTeam = GetTeam( dwSessionID );
    if( pTeam == NULL )
    { return false; }

    if ( !pTeam->IsTeamHeader(dwTeamHeaderId) ) 
    { return false; }        //不是队长

    if ( pTeam->DisbandTeam() )
    {
        ReleaseTeam( pTeam->GetTeamSessionID() );
    }

    return true;
}

bool TeamManagerEx::ExChangeTeamMeberManiple( uint32 dwSessionID, uint32 dwTeamHeaderId, uint32 dwSrcId, uint32 dwDestId )
{
    TeamEx *pTeam = GetTeam( dwSessionID );
    if( pTeam == NULL ) 
    { return false; }

    if (!pTeam->IsTeamHeader(dwTeamHeaderId)) 
    { return false; }        //不是队长

    return pTeam->ExChangeTeamMeberManiple(dwSrcId, dwDestId);
}

bool TeamManagerEx::ChangeTeamMemberManiple( uint32 dwSessionID, uint32 dwTeamHeaderId, uint32 dwTeamMemberId, short stManipleId )
{
    TeamEx *pTeam = GetTeam( dwSessionID );
    if(pTeam == NULL) 
    { return false; }

    if (!pTeam->IsTeamHeader(dwTeamHeaderId)) 
    { return false; }        //不是队长

    return pTeam->ChangeTeamMemberManiple(dwTeamMemberId, stManipleId);
}    

bool TeamManagerEx::IsTeamHeader( uint32 dwSessionID, uint32 dwTeamMemberId )
{
    TeamEx *pTeam = GetTeam( dwSessionID );
    if(pTeam == NULL) 
    { return false; }

    return pTeam->IsTeamHeader(dwTeamMemberId);
}

bool TeamManagerEx::IsManipleHeader( uint32 dwSessionID, uint32 dwTeamMemberId )
{
    TeamEx *pTeam = GetTeam( dwSessionID );
    if( pTeam == NULL ) 
    { return false; }

    return pTeam->IsManipleHeader(dwTeamMemberId);
}    

bool TeamManagerEx::SetManipleHeader( uint32 dwSessionID, uint32 dwTeamHeaderId, uint32 dwManipleId )
{
    TeamEx *pTeam = GetTeam( dwSessionID );
    if(pTeam == NULL) { return false; }
    
    if (!pTeam->IsTeamHeader(dwTeamHeaderId)) 
    { return false; }        //不是队长

    return pTeam->SetManipleHeader(dwManipleId);
}

bool TeamManagerEx::SetCorpsTeam( uint32 dwSessionID, uint32 dwTeamHeaderId )
{
    TeamEx *pTeam = GetTeam( dwSessionID );
    if(pTeam == NULL)
    { return false; }

    if (!pTeam->IsTeamHeader(dwTeamHeaderId))
    { return false; }        //不是队长

    return pTeam->UpdateTeamToCorps();
}

