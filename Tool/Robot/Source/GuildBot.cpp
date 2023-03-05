#include "GuildBot.h"
#include "windows.h"
#include "LogFileObjectName.h"

// ִ��ʱ����
#define SpaceTime ( 20 * 1000 * 1 )

CGuildBot::CGuildBot():m_dwRunTimeSpace(HQ_TimeGetTime())
,m_dwType(EGT_Init)
,m_InviteNumber(1)
{

    m_BotType = Bot_Guild;

    InitGuildData();
}

CGuildBot::~CGuildBot()
{

}

void CGuildBot::InitPlayGame(UINT mapid)
{
	if (m_dwType == EGT_Init)
	{
		InitBotGuildType();
	}
    CNormalBot::InitPlayGame(mapid);
}

void CGuildBot::PlayGame()
{
	Say("�������ɣ������벻���ľ�ϲŶ��");

	DWORD dwNowTime = HQ_TimeGetTime();
	if (dwNowTime >= m_dwRunTimeSpace)
	{
		PlayGuild(dwNowTime);
	}
    CNormalBot::PlayGame();
}

void CGuildBot::PlayGuild(DWORD dwTime)
{
    SetTipsInfo("��Ϸ��");
	m_dwRunTimeSpace = dwTime + SpaceTime ;
	switch (m_dwType)
	{
	case EGT_Comment:		//��ͨ��Ա
		RunGuildComment();
		m_dwRunTimeSpace += SpaceTime; //��ͨ��Ա���ʱ��һ��
		break;
	case EGT_TongMaster:		//���峤
		RunGuildTong();
		break;
	case EGT_CorpMaster:		//���ɳ�
		RunGuildCorps();
		break;
	default:
		break;
	}
}

void CGuildBot::SwitchMsg(Msg *pMsg)
{
	if (pMsg == NULL)
    { return; }

	switch (pMsg->GetType())
	{
    case MSG_ACKGUILDINFO:
        OnMsgAckGuildInfo(pMsg);
        break;
    case MSG_GUILD_TELL_DISMISS:
        OnMsgGuildTellDismiss(pMsg);
        break;
    case MSG_ACK_GUILD_MANIFESTO_INFO:
        OnMsgAckGuildManifestoInfo(pMsg);
        break;
    case MSG_GUILD_TELL_LEAVE:
        OnMsgGuildTellLeave(pMsg);
        break;
    case MSG_GUILD_TELL_LEVEL:
        OnMsgGuildTellLevel(pMsg);
        break;
    case MSG_GUILD_REQ_INVITE:
        OnMsgGuildReqInvite(pMsg);
        break;
	default:
		BaseRobot::SwitchMsg(pMsg);
	}
}

char* CGuildBot::GetBotNameNum()
{
    char BotName[dr_MaxPlayerName];
    memset(BotName,0,sizeof(BotName));
    strncpy_s(BotName,sizeof(BotName),GetBotRoleName(),sizeof(BotName)-1);
    int i = 0;
    while(BotName[i] != 0)
    {
        if(BotName[i] >= '0' && BotName[i] <= '9') { break; }
        ++i;
    }

    return BotName + i;
}

void CGuildBot::InitBotGuildType()
{
	m_dwType = EGT_Comment;

    int nTemp = 0;
    std::string strNum = GetBotNameNum();
    if (!strNum.empty())
    {
        nTemp = atoi(strNum.c_str());
    }
	if (nTemp == 0) 
    {
        m_dwType = EGT_Comment;
        return;
    }

    if (nTemp%30 == 0)
    {
        m_dwType = EGT_CorpMaster;
    }
// 	if (nTemp % 60 == 0)
// 	{
// 		m_dwType = EGT_CorpMaster;
// 	}
// 	else if (nTemp % 20 == 0)
// 	{
// 		m_dwType = EGT_TongMaster;
// 	}
    m_dwType = EGT_Comment;
}

void CGuildBot::InitGuildData()
{
    memset(&m_GuildInfo,0,sizeof(m_GuildInfo));
    if (!m_GuildMembers.empty())
        m_GuildMembers.clear();
}

void CGuildBot::RunGuildCorps()
{
	//�жϽ��������� 100�� �ͽ�ɢ,���� ����
    if ( !IsHaveGuild() && IsGuildMaster() )
    {
        //Create Guild
        CreateGuild(GetBotRoleName());
        Move();
        RandFly();
        InviteGuildMember();
        return;
    }
    RandFly();
    Move();
    /*
    // �й���Ĳ�������ļ��Ա���߳���Ա�����ˣ�
    int operation = rand()%EMO_SetTongMaster;
    switch(operation)
    {
    case EMO_Disband:
        DisbandGuild();
        break;
    case EMO_ModifiyManifesto:
        {
            char szManifestoinfo[1024] = {0};
            sprintf_s(szManifestoinfo,sizeof(szManifestoinfo),"���� %s �Ĺ���,��ӭ�ι�!",GetBotRoleName());
            ModifiyGuildManifesto(szManifestoinfo);
        }
        break;
    case EMO_Exit:
        ExitGuild();
        break;
//     case EMO_Invite:
//         InviteGuildMember();
//         break;
//     case EMO_Ban:
//         BanGuildMember();
//         break;
//     case EMO_Cession:
//         CessionGuildMaster();
//         break;
//     case Procuratory_TongMaster:
//         break;
    }
    */
}

void CGuildBot::DisbandGuild()
{
    MsgGuildQueryDismiss DisbandMsg;
    DisbandMsg.header.stID = GetBotShortId();
    SendMsg(&DisbandMsg);
}

void CGuildBot::ModifiyGuildManifesto(char* szManifesto)
{
    if (NULL == szManifesto)
        return;

    MsgReqGuildManifestoInfo ManifestoinfoMsg;
    ManifestoinfoMsg.header.stID = GetBotShortId();
    ManifestoinfoMsg.shType = MsgReqGuildManifestoInfo::eReqType_Modifiy;
    ManifestoinfoMsg.SetGuildManifestoInfo(szManifesto);
    SendMsg(&ManifestoinfoMsg);
}

void CGuildBot::ExitGuild()
{
    MsgGuildQueryLeave LeaveMsg;
    LeaveMsg.header.stID = GetBotShortId();
    SendMsg(&LeaveMsg);
}

void CGuildBot::RunGuildTong()
{
	//�ж������Ƿ�����(15��),û��������,�����ɢ�����߳�
}

void CGuildBot::RunGuildComment()
{
	//�ж��Լ����޹���, �����˳�,����(�������)(Ŀǰû��, ��Ϊ�ȴ�������)
    
}

void CGuildBot::OnMsgAckGuildInfo(Msg* pMsg)// Ӧ�𹫻���Ϣ
{
    if (NULL == pMsg)
        return;
    MsgAckGuildInfo* pMsgGuildInfo = (MsgAckGuildInfo*)pMsg;
    m_GuildInfo = pMsgGuildInfo->stGuildInfo;

    for (int n = 0;n != pMsgGuildInfo->stGuildInfo.m_shMemberNum;++n)
    {
        m_GuildMembers.insert( GuildMemberContainer::value_type(pMsgGuildInfo->stMemberList[n].nDBId,pMsgGuildInfo->stMemberList[n]) );
        ItrGuildMemberContainer Itr = m_GuildMembers.find(pMsgGuildInfo->stMemberList[n].nDBId);
        if (Itr != m_GuildMembers.end())
        {
            m_GuildMemberByName.insert(GuildMemberByNameContainer::value_type(pMsgGuildInfo->stMemberList[n].szName,&Itr->second));
        }
    }

    // �õ�������Ϣ�Ժ�У���������߼�����
    if (IsCorpMaster() && m_dwType != EGT_CorpMaster) // ����ǻ᳤,�����߼����Ͳ��ǻ᳤��,�����������߼�Ϊ�᳤�߼�
        m_dwType = EGT_CorpMaster;
    else if(!IsCorpMaster() && m_dwType == EGT_CorpMaster)// ������ǻ᳤,�����߼������ǻ᳤��,�����������߼�Ϊ�ǻ᳤�߼�
        m_dwType = EGT_Comment;
}

void CGuildBot::OnMsgAckGuildCreate(Msg* pMsg)
{
    MsgAckGuildCreate* pGuildCreate = (MsgAckGuildCreate*) pMsg;
    if (pGuildCreate->shResult != MsgAckGuildCreate::RESULT_FAIL)
    {
        m_GuildInfo.m_nMasterID = GetBotDBID();
        strncpy_s (m_GuildInfo.m_szName ,sizeof(m_GuildInfo.m_szName)
            ,m_ApplicationGuildName.c_str(),sizeof(m_GuildInfo.m_szName)-1);

    }
}

bool CGuildBot::CreateGuild(char* szGuildName)
{
    if (NULL == szGuildName)
        return false;
    if (!HaveEnoughMoney())
    {
        ReqBotMoney(CreateGuildGold);
        SetSleep(3000);
        return true;
    }

    MsgGuildQueryCreate CreateGuildMsg;
    CreateGuildMsg.header.stID = GetBotShortId();
    CreateGuildMsg.bCancelCreate = false;
    strncpy_s(CreateGuildMsg.szGuildName,sizeof(CreateGuildMsg.szGuildName),szGuildName,sizeof(CreateGuildMsg.szGuildName)-1);

    SendMsg(&CreateGuildMsg);

    m_ApplicationGuildName = szGuildName;
    return true;
}

void CGuildBot::OnMsgGuildTellDismiss(Msg* pMsg)
{
    InitGuildData();
}

void CGuildBot::OnMsgAckGuildManifestoInfo(Msg* pMsg)
{
    MsgAckGuildManifestoInfo* pGuildManifestoInfo = (MsgAckGuildManifestoInfo*)pMsg;
    if (IsCorpMaster()&&(pGuildManifestoInfo->shResult != MsgAckGuildManifestoInfo::EResult_Error))
    {
        LOG_MESSAGE(LogObject,LOG_PRIORITY_INFO,"Bobot %s SetManifestoInfo Ok!",GetBotRoleName());
    }
}

void CGuildBot::OnMsgGuildTellLeave(Msg* pMsg)
{
    MsgGuildTellLeave* pLeave = (MsgGuildTellLeave*)pMsg;
    if (m_GuildMembers.size() == 1)
    {
        InitGuildData();
        return;
    }
    if (!IsCorpMaster())
    {
        ItrGuildMemberContainer FindItr = m_GuildMembers.find(pLeave->nDBID);
        if (FindItr != m_GuildMembers.end())
        {
            m_GuildMembers.erase(FindItr);
        }
        
    }
    LOG_MESSAGE(LogObject,LOG_PRIORITY_INFO,"Bobot %s Leave %s Guild Ok!",GetBotRoleName(),GetGuildName());
    
}

void CGuildBot::InviteGuildMember()
{
    // ������������˵�����
    char InviteName[dr_MaxPlayerName];
    std::string strNum = GetBotNameNum();
    if (strNum.empty())
    { return;}
    int nTemp = atoi(strNum.c_str());
    if (nTemp == 0) 
    { return; }

    //nTemp = nTemp + rand()%30;
    for (int i = 0;i<30;++i)
    {
        int nSelect = s_nNameCount%2;
        sprintf_s( InviteName,sizeof(InviteName) ,"%s.%d", s_pszName[nSelect], nTemp+i);
        bool isHave = false;
        for(GuildMemberContainer::iterator itr = m_GuildMembers.begin();itr != m_GuildMembers.end();++itr)
        {
            if (_stricmp(itr->second.szName,InviteName)==0)
            {
                isHave = true;
                break;
            }
        }
        if (!isHave)
        {
            MsgGuildQueryInvite InviteMsg;
            sprintf_s(InviteMsg.szInviteeName,sizeof(InviteMsg.szInviteeName),"%s",InviteName);
            SendMsg(&InviteMsg);
        }
    }
}

void CGuildBot::BanGuildMember(int MemberDBId)
{
    if (m_GuildMembers.size() == 1)
        return;

    int Member = rand()%m_GuildMembers.size();
    if (Member < m_GuildMembers.size())
    {
        MsgGuildQueryBan BanMsg;
        strncpy_s(BanMsg.szBanName , sizeof(BanMsg.szBanName),m_GuildMembers[Member].szName,sizeof(BanMsg.szBanName));
        BanMsg.header.stID = GetBotShortId();
        SendMsg(&BanMsg);
    }
}

// ת�û᳤
void CGuildBot::CessionGuildMaster()
{
    //MsgReqGuildChangeLevel MSG_REQ_GUILD_CHANGELEVEL
    if (m_GuildMembers.size() == 1)
        return;
    
    MsgReqChangeGuildMemberGangPosition CessionMsg;
    CessionMsg.header.stID = GetBotShortId();
    CessionMsg.opType = EGCPOT_AttornMaster;
    CessionMsg.gruntedRightTarget = EOR_GangMaster;    // 0��Master
    
    DWORD Num = rand()%m_GuildMembers.size();
    int CurNum = 0;
    bool IsFind = false;
    for (ItrGuildMemberContainer Itr = m_GuildMembers.begin();Itr != m_GuildMembers.end();++Itr)
    {
        if (CurNum == Num && !IsCorpMaster(Itr->first))
        {
            IsFind = true;
//             strncpy_s(CessionMsg.szTargetName,sizeof(CessionMsg.szTargetName)
//                 ,Itr->second.szName,sizeof(CessionMsg.szTargetName)-1);
            CessionMsg.charDbIdTarget = Itr->second.nDBId;
            break;
        }
        CurNum++;
    }

    if (IsFind)
    {
        SendMsg(&CessionMsg);
    }
}

void CGuildBot::OnMsgGuildReqInvite(Msg* pMsg)
{
    if (IsHaveGuild())
    {
        return;
    }
    MsgGuildReqInvite* pMsgInvite = (MsgGuildReqInvite*)pMsg;
    BOOL IsAgree = rand()%2;
    MsgGuildAckInvite AckInviteMsg;
    AckInviteMsg.bAgree      = MsgGuildAckInvite::eAgreeInvite;//IsAgree==TRUE?MsgGuildAckInvite::eAgreeInvite:MsgGuildAckInvite::eRefuseInvite;
    AckInviteMsg.nGuildID    = pMsgInvite->nGuildID;
    AckInviteMsg.nInviteDBID = pMsgInvite->nInviteDBID;
    AckInviteMsg.header.stID = GetBotShortId();

    SendMsg(&AckInviteMsg);
}

void CGuildBot::OnMsgGuildTellLevel(Msg* pMsg) // �޸�Ȩ���Ժ�
{
    MsgGuildTellLevel* pMsgGuildTellLevel = (MsgGuildTellLevel*)pMsg;

    if (IsCorpMaster())
    {// �����ǰ�ǰ�᳤�ĸ��°�᳤ID���޸��߼�Ϊ��ͨ��Ա
        m_GuildInfo.m_nMasterID = pMsgGuildTellLevel->nDBID;
        m_dwType = EGT_Comment;
        return;
    }

    // ���ǰ�᳤�ĸ��°�᳤ID���ж��Լ��ǲ��ǰ�᳤,����Ǿ͸����Լ����߼�Ϊ��᳤�߼�
    m_GuildInfo.m_nMasterID = pMsgGuildTellLevel->nDBID;
    if (IsCorpMaster())
        m_dwType = EGT_CorpMaster;

}

void CGuildBot::OnMsgGuildTellJoin(Msg* pMsg)
{
    MsgGuildTellJoin* pJoinMsg = (MsgGuildTellJoin*)pMsg;
    m_GuildMembers.insert(GuildMemberContainer::value_type(pJoinMsg->member.nDBId,pJoinMsg->member));
}

bool CGuildBot::IsMember(const char* name)
{
    ItrGuildMemberByNameContainer Itr = m_GuildMemberByName.find(name);
    return Itr != m_GuildMemberByName.end();
}

bool CGuildBot::IsGuildMaster()
{
    std::string strNum = GetBotNameNum();
    if (strNum.empty())
    {
        return false;
    }
    int num = atoi(strNum.c_str());
    if (num%30 == 0)
    {
        return true;
    }
    return false;
}