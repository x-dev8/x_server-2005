#include "GuildBot.h"
#include "windows.h"
#include "LogFileObjectName.h"

// 执行时间间隔
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
	Say("都来入会吧，有意想不到的惊喜哦！");

	DWORD dwNowTime = HQ_TimeGetTime();
	if (dwNowTime >= m_dwRunTimeSpace)
	{
		PlayGuild(dwNowTime);
	}
    CNormalBot::PlayGame();
}

void CGuildBot::PlayGuild(DWORD dwTime)
{
    SetTipsInfo("游戏中");
	m_dwRunTimeSpace = dwTime + SpaceTime ;
	switch (m_dwType)
	{
	case EGT_Comment:		//普通会员
		RunGuildComment();
		m_dwRunTimeSpace += SpaceTime; //普通会员间隔时间一点
		break;
	case EGT_TongMaster:		//结义长
		RunGuildTong();
		break;
	case EGT_CorpMaster:		//帮派长
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
	//判断结义数超过 100个 就解散,否则 邀请
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
    // 有公会的操作，招募会员，踢出会员，结盟，
    int operation = rand()%EMO_SetTongMaster;
    switch(operation)
    {
    case EMO_Disband:
        DisbandGuild();
        break;
    case EMO_ModifiyManifesto:
        {
            char szManifestoinfo[1024] = {0};
            sprintf_s(szManifestoinfo,sizeof(szManifestoinfo),"这是 %s 的公会,欢迎参观!",GetBotRoleName());
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
	//判断人数是否满了(15个),没满就邀请,否则解散或者踢出
}

void CGuildBot::RunGuildComment()
{
	//判断自己有无公会, 有则退出,否则(申请加入)(目前没有, 改为等待被邀请)
    
}

void CGuildBot::OnMsgAckGuildInfo(Msg* pMsg)// 应答公会信息
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

    // 拿到公会信息以后校正机器人逻辑类型
    if (IsCorpMaster() && m_dwType != EGT_CorpMaster) // 如果是会长,但是逻辑类型不是会长则,更正机器人逻辑为会长逻辑
        m_dwType = EGT_CorpMaster;
    else if(!IsCorpMaster() && m_dwType == EGT_CorpMaster)// 如果不是会长,但是逻辑类型是会长则,更正机器人逻辑为非会长逻辑
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
    // 构造邀请机器人的名字
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

// 转让会长
void CGuildBot::CessionGuildMaster()
{
    //MsgReqGuildChangeLevel MSG_REQ_GUILD_CHANGELEVEL
    if (m_GuildMembers.size() == 1)
        return;
    
    MsgReqChangeGuildMemberGangPosition CessionMsg;
    CessionMsg.header.stID = GetBotShortId();
    CessionMsg.opType = EGCPOT_AttornMaster;
    CessionMsg.gruntedRightTarget = EOR_GangMaster;    // 0是Master
    
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

void CGuildBot::OnMsgGuildTellLevel(Msg* pMsg) // 修改权限以后
{
    MsgGuildTellLevel* pMsgGuildTellLevel = (MsgGuildTellLevel*)pMsg;

    if (IsCorpMaster())
    {// 如果以前是帮会长的更新帮会长ID，修改逻辑为普通成员
        m_GuildInfo.m_nMasterID = pMsgGuildTellLevel->nDBID;
        m_dwType = EGT_Comment;
        return;
    }

    // 不是帮会长的更新帮会长ID后判断自己是不是帮会长,如果是就更新自己的逻辑为帮会长逻辑
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