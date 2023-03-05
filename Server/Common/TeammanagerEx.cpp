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
    advance(iter, nIndex); // ����ƫ��

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
    if (TeamMemberCount() == TeamMaxManipleMember)    //ֻ�������ﵽ5�˲��������䵽��
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
    { return false; }  //�Ѿ��Ƕӳ���

    if ( !IsInTeam( dwDataBaseId ) )
    { return false; }

    SetTeamHeaderID( dwDataBaseId );            // �����¶ӳ�

    if ( bQuickUpdate )
    {
        m_dwStopUpdateTeamMemberTime = HQ_TimeGetTime() + 1000;         //1�벻�����������������͹����Ķӳ���Ϣ
    }

    RunTeamUpdate( bQuickUpdate );

    //֪ͨ�������,�ӳ���Ϣ�Ѿ��ı�
    GamePlayer* pLastHeader = (GamePlayer*) RunTimeData::GetInstance().GetGamePlayerByDBID( dwLastHeaderID );
    if ( pLastHeader != NULL )        
    { // �Ѿ����Ƕӳ�
        pLastHeader->TellTeamInfoChange( ETP_Member );
    }

    GamePlayer* pNowHeader = (GamePlayer*) RunTimeData::GetInstance().GetGamePlayerByDBID( dwDataBaseId );
    if ( pNowHeader != NULL )
    {  //�Ѿ����Ϊ�ӳ�
        pNowHeader->TellTeamInfoChange( ETP_Leader );
    }

    return true;
}

//����ĳ��ԱΪС�ӳ�
bool TeamEx::SetManipleHeader(DWORD dwDataBaseId)
{
    TeamMember* pTeamMember = GetTeamMember(dwDataBaseId);
    if (pTeamMember == NULL) { return false; } //���ڶ�����

    //ȡ����ԭ����С�ӳ�
    TeamMember* pManipleHeader = GetManipleHeader(pTeamMember->GetManipleID());
    DWORD dwSrcManipleHeaderId = -1;
    if (pManipleHeader != NULL)
    {
        if (pManipleHeader->GetMemberID() == dwDataBaseId)
        { return false; }        //��ͬһ����

        pManipleHeader->SetManipleHeader( false );
        dwSrcManipleHeaderId = pManipleHeader->GetMemberID();
    }

    pTeamMember->SetManipleHeader( true );
    
    MsgRetFlagHeaderFromTeam xRet;
    xRet.bSrcess    = true;
    xRet.dwSrcID    = dwSrcManipleHeaderId;   //ע��, ������db id, ��Ҫ����Э��
    xRet.dwDestID   = dwDataBaseId;

    SendMessageToTeamMember(&xRet);

    return true;
}

//�л���Ա��С��
bool TeamEx::ChangeTeamMemberManiple(DWORD dwDataBaseId, short stManipleId)
{
    if (dwDataBaseId == ErrorUnsignedLongID || stManipleId < 0 || stManipleId >= TeamMaxManipleCount) { return false; }

    TeamMember* pTeamMember = GetTeamMember( dwDataBaseId );
    if ( pTeamMember == NULL )
    { return false; }

    if ( IsManipleFull(stManipleId) ) 
    { return false; }

    if ( pTeamMember->GetManipleHeader() )  // ԭ����С�ӳ�
    {
        //�ҵ�һ����Ա���̳�С�ӳ�
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
    UpdateManipleCount( pTeamMember->GetManipleID(), false );    //����ԭ��С������

    //////////////////////////////////////////////////////////////////////////////////
    MsgMovePlayerFromManiple xMsg;
    xMsg.dwSrc = dwDataBaseId;
    xMsg.stSrcManiple = stManipleId;

    SendMessageToTeamMember(&xMsg);
    ////////////////////////////////////////////////////////////////////////////////////

    pTeamMember->SetManipleID( stManipleId );    
    UpdateManipleCount( stManipleId );                //��������С������

    return true;
}

//����������Ա��С��
bool TeamEx::ExChangeTeamMeberManiple(DWORD dwSrcDataBaseId, DWORD dwDestDataBaseId)
{
    TeamMember* pSrcMember = GetTeamMember(dwSrcDataBaseId);
    if (pSrcMember == NULL) { return false; }

    TeamMember* pDestMember = GetTeamMember(dwDestDataBaseId);
    if (pDestMember == NULL) { return false; }

    //�����ͬһ��С��,��ִ��
    if ( pDestMember->GetManipleID() == pDestMember->GetManipleID() ) 
    { return false; }

    //����С��ID
    short stTempManipleId = pDestMember->GetManipleID();
    pDestMember->SetManipleID( pSrcMember->GetManipleID() );
    pSrcMember->SetManipleID( stTempManipleId );

    //����С�ӳ���־
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


//���һ����Ա��������
bool TeamEx::AddTeamMember( TeamMember& xMember, bool bIsTeamHeader )
{
    if ( xMember.IsError() )            //��������  
    { 
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "AddTeamMember TeamMember [%u][%s] Error", xMember.GetMemberID(), xMember.GetName() );
        return false; 
    }              
    
    if ( IsInTeam( xMember.GetMemberID() ) )         //�Ѿ��ڶ����� 
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
    UpdateManipleCount( xMember.GetManipleID() );            //����С������
    ///////////////////////////////////////////////////////////////////////////////
    return true;
}

//���ض����Ƿ���Ҫ��ɢ  bSendCenterServerReq=���� bSendCenterServerAck=ȷ��
bool TeamEx::RemoveTeamMember(DWORD dwDataBaseId)
{
    bool bReleaseTeam = false;

    TeamMember* pTeamMember = GetTeamMember(dwDataBaseId);
    if (pTeamMember == NULL) { return false; }
    
    if ( TeamMemberCount() <= 2 )  //ֻ�������˵Ķ���, �ߵ�һ�� �����ɢ
    {
        MsgExitTeam xExitTeamMsg;
        xExitTeamMsg.bIsDisband = true;
        TeamIter iter = m_listTeamMember.begin();
        TeamIter end = m_listTeamMember.end();
        for ( ; iter != end; ++iter)
        {
            //������Ϣ
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
            //֪ͨ�ö�Ա�뿪����
            MsgExitTeam xExitTeamMsg;
            GettheServer().SendMsgToSingle(&xExitTeamMsg, pPlayerChar);

            pPlayerChar->TellTeamInfoChange( ETP_None );
        }

        UpdateManipleCount(pTeamMember->GetManipleID(), false);  //����С������

        TeamIter iter = find( m_listTeamMember.begin(), m_listTeamMember.end(), dwDataBaseId );
        if ( iter != m_listTeamMember.end() )
        {
            m_listTeamMember.erase(iter);
        }
        
        //֪ͨ�������
        MsgDeleteTeamMember xMsg;
        xMsg.dwMemberID = dwDataBaseId;
        SendMessageToTeamMember(&xMsg, dwDataBaseId, false);
    }
   
    return bReleaseTeam;
}

//��ɢ����
bool TeamEx::DisbandTeam()
{
    TeamIter iter = m_listTeamMember.begin();
    TeamIter end = m_listTeamMember.end();

    MsgExitTeam xExitTeamMsg;
    xExitTeamMsg.bIsDisband = true;
    for ( ; iter != end; ++iter )
    {
        //���Ͷ����ɢ��Ϣ
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

//��ǰֻ�з��Ͷ����MsgChat::CHAT_TYPE_GAMEPROMPT ��Ϣ, �����CHAT_TYPE_TERM ������.
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
        { continue; }        //�����Լ�����Ϣ

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

    //���ڱ�������
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
                    // ��ʱ�ͻ����ڼ��ص�ͼ��ʱ��, ���˽������, �ռ���Ķ�Ա�����б���, ˵��û���յ������Ϣ
                    pChar->Log( "���[%s][%d]���ڼ��ص�ͼʱ���˼������.", iter->GetName(), iter->GetMemberID() );  
                }
            }
            else
            {
                //������������                
                bSomeOneOnAnotherServer = true;                                
            }
        }
    }

    //�¼����Ա,���ڱ�ķ������ϵ�,�ͷ���Ϣ��CenterServer
    if ( bSomeOneOnAnotherServer && bCenterServerAck )  
    {
        if( pMsg->GetType() == MSG_CHAT )
        {
            S2STransmit::STeam xTeam;
            xTeam.dwSessionID = m_dwSessionId;
            GettheServer().SendMsgToTeamRemote( pMsg, xTeam );
        }
        //������Ϣ
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
        if( pMemberChar != NULL )  //��Ա�ڱ���
        {
            GettheServer().SendMsgToSingle( pMsg, pMemberChar );    
        }
        else //���ڱ�������
        {
            bSomeOneOnAnotherServer = true;
        }
    }

    //���͸�CenterServer��ת
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

//bRunUpdate = trueʱ����Ҫ����ִ��,
bool TeamEx::RunTeamUpdate(bool bQuickUpdate /* = false */)
{
    DWORD dwNowTime = HQ_TimeGetTime();

    if ( bQuickUpdate )     //����ִ��
    {
        m_dwNextUpdateToCenterTime = 0;
        m_dwNextUpdateTime = 0;    
    }

    //�Ѷ�Ա��Ϣ�·����ͻ���
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
        { continue; } //���ڱ����Ĳ�����

        if ( pMemberChar->GetTeamSessionID() != GetTeamSessionID() )        // �����������ϵ�sessionid �� ����Ĳ�һ��, �߳������Ա
        {
            vecDeleteMember.push_back( iter->GetMemberID() );
            LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_ERROR, "���[%s]���ϵ�sessionid[%u] �� ����[%u]�Ĳ�һ��!", pMemberChar->GetPlayerName(), pMemberChar->GetTeamSessionID(), GetTeamSessionID() );
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
        xInfo.dwMapID       = pMemberChar->GetMapID();          //�ͻ���ʹ�õ���mapconfig�еĵ�ͼid
        xInfo.x             = pMemberChar->GetX();
        xInfo.y             = pMemberChar->GetY();
        xInfo.fx            = pMemberChar->GetFloatX();
        xInfo.fy            = pMemberChar->GetFloatY();
        xInfo.stManiple     = iter->GetManipleID();
        xInfo.bHeader2      = IsManipleHeader( iter->GetMemberID() );
        
        SendMemberInfoToTeamMember( &xInfo, ErrorUnsignedLongID, true );    // �Լ�ҲҪ����
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

//����С��������Ϣ
void TeamEx::UpdateManipleCount(short stManipleId, bool bAdd /* = true */)
{
    if (stManipleId < 0 || stManipleId >= TeamMaxManipleCount) { return; }

    ManipleCountIter iter = m_mapManipleCount.find(stManipleId);
    if (iter == m_mapManipleCount.end())
    {
        if (bAdd) //���Ӷ�Ա
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

//������Ч��Χ�ڶ�Ա���ܵȼ�
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

//����������Ӧ�ľ�����ʱ�
float TeamEx::GetTeamExpPercent(unsigned int nTeamCount, bool bIsEcType)
{
    const static float fExpPercent[][TeamMaxManipleMember] = 
    {
        { 1.0f, 0.9f, 0.8f, 0.8f, 0.8f, 0.8f, },        // ��ͨ��ͼ�������
        { 1.0f, 1.2f, 1.4f, 1.6f, 1.8f, 2.0f, },        // ������ͼ�������
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

    TeamEx* pTeam = CNewWithDebug<TeamEx>::Alloc(1, "TeamManagerEx::CreateTeam�д���pTeam");
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

//�ӳ��ߵ�һ����Ա
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

//�Ƴ�һ����Ա,�����ǵ���(�����ӳ�)
bool TeamManagerEx::RemoveFromTeam( uint32 dwSessionID, uint32 dwDataBaseID, bool bKick /* = false */ )
{
    GS2CSPlayerRemoveFromTeamReq xRemove;

    xRemove.dwSessionId  = dwSessionID;
    xRemove.dwDataBaseId = dwDataBaseID;
    xRemove.bKick        = bKick;
    GettheServer().SendMsgToCenterServer( &xRemove );

    return true;
}

//�����û�ж�Ա��������ʱ��,����������ý�ʧ��
bool TeamManagerEx::DisbandTeam( uint32 dwSessionID , uint32 dwTeamHeaderId )
{
    TeamEx *pTeam = GetTeam( dwSessionID );
    if( pTeam == NULL )
    { return false; }

    if ( !pTeam->IsTeamHeader(dwTeamHeaderId) ) 
    { return false; }        //���Ƕӳ�

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
    { return false; }        //���Ƕӳ�

    return pTeam->ExChangeTeamMeberManiple(dwSrcId, dwDestId);
}

bool TeamManagerEx::ChangeTeamMemberManiple( uint32 dwSessionID, uint32 dwTeamHeaderId, uint32 dwTeamMemberId, short stManipleId )
{
    TeamEx *pTeam = GetTeam( dwSessionID );
    if(pTeam == NULL) 
    { return false; }

    if (!pTeam->IsTeamHeader(dwTeamHeaderId)) 
    { return false; }        //���Ƕӳ�

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
    { return false; }        //���Ƕӳ�

    return pTeam->SetManipleHeader(dwManipleId);
}

bool TeamManagerEx::SetCorpsTeam( uint32 dwSessionID, uint32 dwTeamHeaderId )
{
    TeamEx *pTeam = GetTeam( dwSessionID );
    if(pTeam == NULL)
    { return false; }

    if (!pTeam->IsTeamHeader(dwTeamHeaderId))
    { return false; }        //���Ƕӳ�

    return pTeam->UpdateTeamToCorps();
}

