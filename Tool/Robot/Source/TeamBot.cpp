#include "TeamBot.h"
#include "GameBot.h"
#include "LogFileObjectName.h"

#pragma warning(disable:4245)
#pragma warning(disable:4201)
// tarage: 每个人都要组队
//10秒的执行间隔
#define  OneSec    1000
#define  SpaceMin  10
#define  SpaceTime (OneSec * SpaceMin)

#define  OneMinute (60 * OneSec)
#define  NoHavePlayerTime (10 * OneMinute)

TeamBot::TeamBot():
m_RunTime(HQ_TimeGetTime()),
m_CurTeamNum(0),
m_TeamHeadId(0),
m_PlayGame(false),
m_NoHavePlayerTime(0),
bReqFlymap(false),
m_Breakteam(false),
m_ReturnSelRole(false),
m_LastChangeMapTime(HQ_TimeGetTime()),
m_ReqFlyNum(1),
m_LastMapId(-1),
m_LastMoveTime(HQ_TimeGetTime()),
m_ReqGoToEctype(false),
ReqFlyEctypeTime(HQ_TimeGetTime()),
ReqFlyEctypeMapId(-1),
ReqFlyTeamMapTime(HQ_TimeGetTime()),
m_ReqLeaveEctypeMapTime(HQ_TimeGetTime()),
dwTeamId(ERRORTEAMID)
{
    m_nMoveStep = OneSec*30; // 30 秒移动一次
    m_OnEctypeMapTime = OneMinute * 5; // 3控制在副本中的时间3分钟以后就返回原点
    if (m_BotType == Bot_End)
    {
        m_BotType = Bot_Team;
    }
}

TeamBot::~TeamBot()
{

}

void TeamBot::InitPlayGame(UINT mapid)
{
    m_bFlyMap = false;
    //CBot::InitPlayGame();
}

void TeamBot::PlayGame()
{
    if (!m_PlayGame)
    {
        m_ReturnSelRole = false;
        m_PlayGame = true;
        SetTipsInfo("游戏中..");
    }
    
    if ( m_Breakteam )
    {

        BreakTeam();
        m_Breakteam = false;

        return;
    }

    if (!CheckTeam())
    {
        LogTeam();
        BreakTeam();
        m_Breakteam = true;

        if (VecTeam.size() == 1)
        {
            LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR ,"队伍 [%d] 只有一个人，没有收到AddTeamMember",VecTeam[0].dwGroupId);
            VecTeam.clear();
        }
        return;
    }

    MapConfig::MapData* theMap = theMapConfig.GetMapDataById(GetMapID());
    if (theMap->IsEctypeMap())
    {
        SetTipsInfo("副本中");
        // 如果在副本的时间超过限制就飞回去
        if (HQ_TimeGetTime() - m_EnterEctypeMapTime >= m_OnEctypeMapTime)
        {
            if (HQ_TimeGetTime() - m_ReqLeaveEctypeMapTime >= OneMinute * 2 )
            {
                LoadTeamMap();
                FlyToMap(m_LastMapId,m_MapX,m_MapY);
                m_ReqLeaveEctypeMapTime = HQ_TimeGetTime();
            }
            return;
        }
        //没有超过限制就移动
        if (HQ_TimeGetTime() - m_LastMoveTime >= m_nMoveStep)
        {
            Move();
            m_LastMoveTime = HQ_TimeGetTime();
        }
    }
    PlayTeam(HQ_TimeGetTime());

    //CBot::PlayGame();
    if (HQ_TimeGetTime() - ReqFlyTeamMapTime >= OneMinute )// 2分钟内飞到队伍地图
    {
        LoadTeamMap();

        if ( !IsInTeamMap(EctypeId2MapId( GetMapID()) ) &&
             !IsTeamEctypeMap( EctypeId2MapId(GetMapID()) ) ) 
            RandFlyTeamMap();

        ReqFlyTeamMapTime = HQ_TimeGetTime();
    }
}

bool TeamBot::IsInTeamMap(const int MapId)
{
    if (MapId < 0)
        return false;

    for(std::vector<int>::iterator itr = vecTeamMap.begin();itr!= vecTeamMap.end();++itr)
    {
        if (MapId == *itr)
        {
            return true;
        }
    }

    return false;
}

void TeamBot::LoadTeamMap()
{
    if (vecTeamMap.empty())
    {
        // 只载入长安，淮南，太原，扬州,因为这有这几张图有副本
        vecTeamMap.push_back(2);
        vecTeamMap.push_back(3);
        vecTeamMap.push_back(10);
        vecTeamMap.push_back(11);
//         int nCount = theMapConfig.MapDataCount();
//         for (int i = 0; i < nCount; ++i)
//         {
//             MapConfig::MapData *pMapData = theMapConfig.GetMapDataByIndex(i);
//             if (pMapData == NULL) { continue; }
//             if (!pMapData->IsEctypeMap() && !pMapData->MapName.empty() &&
//                 (pMapData->Id == 2 || pMapData->Id == 3 || pMapData->Id == 10 || pMapData->Id == 11) ) // 只载入长安，淮南，太原，扬州
//             {
//                 vecTeamMap.push_back(pMapData->Id);
//             }
//         }
        //nMapCount = vecTeamMap.size();
    }
}

void TeamBot::RandFlyTeamMap()
{
    static int TeamMapId = 0;

    if( HQ_TimeGetTime() - ReqFlyEctypeTime >= 60*1000)
    {
        //int RandValue = rand()%vecTeamMap.size();
        if (TeamMapId >= vecTeamMap.size())
        {
            TeamMapId = 0;
        }
        FlyToMap(vecTeamMap[TeamMapId++],Safe_Map_PosX,Safe_Map_PosY);
        ReqFlyEctypeTime = HQ_TimeGetTime();
       
        m_LastMapId = TeamMapId;
    }
}

void TeamBot::PlayTeam(DWORD dwTime)
{
    if (dwTime >= m_RunTime)
    {
        // 如果已经飞过地图且超过1分钟，则请求飞回去
        m_ReqFlyNum = 1;
        if ( ( (GetMapID() != m_LastMapId && m_LastMapId != -1) || m_IsChangeMap) && ( HQ_TimeGetTime() - m_LastChangeMapTime >= OneMinute * 2 ) )
        {
            if (m_ReqFlyNum <= 10)
            {
                FlyToMap(m_LastMapId, m_MapX, m_MapY);
                m_IsChangeMap = false;
                m_ReqFlyNum++;
                m_LastChangeMapTime = HQ_TimeGetTime();
                return;
            }                
        }
        if (m_ReturnSelRole)
        {
            return;
        }

        if (!IsHaveTeam())
        {
            // 邀请
            RandInviteTeamMember();
        }
        else
        {
            int RanNum = rand()%ETO_TotalOperation;
            switch (RanNum)
            {
            case ETO_InviteTeam: // 邀请
                RandInviteTeamMember();
                break;
            case ETO_BreakTeam:// 退队
                BreakTeam();
                break;
            case ETO_TransferTeamHead:
                TransferTeamHead();
                break;
            case ETO_Moveing:
                if (HQ_TimeGetTime() - m_LastMoveTime >= m_LastMoveTime)
                {
                    Move();
                    m_LastMoveTime = HQ_TimeGetTime();
                }
                break;
            case ETO_ChangeTeamAssign:
                ChangeTeamAssign();
                break;
            case ETO_BreakGame:
                BreakGameToSelectRole();
                break;
            case ETO_Ectype:
                GoToEctypeMap();
                break;
            case ETO_TeamChat:
                TeamTalk();
                break;
            case ETO_ChangeMap:
                // 记录自己当前坐在地图和坐标
                if (m_IsChangeMap)  // 已经飞过就不要飞了
                    break;

                SaveLastMapInfo();
                m_IsChangeMap = true;
                m_LastChangeMapTime = HQ_TimeGetTime();
                LoadTeamMap();
                RandFlyTeamMap();
                break;
            default:
                break;
            }
        }

        // 所有的机器人都同一在一个地图组队
//      if (GetMapID() != Safe_Map_Id)
//      {
//          FlyToMap(Safe_Map_Id,Safe_Map_PosX,Safe_Map_PosY);
//      }

        m_RunTime += SpaceTime;
    }
}

void TeamBot::SaveLastMapInfo()
{
    m_LastMapId = GetMapID();
    m_MapX = GetPosX();
    m_MapY = GetPosY();
}

void TeamBot::ChangeTeamAssign()
{
    if (!IsTeamHead())
    {
        return;
    }
    MsgCovCorps CovCorp;
    CovCorp.AssignMode = rand()%AssignMode_Assign+1;
    SendMsg(&CovCorp);
}

void TeamBot::SwitchMsg(Msg* pMsg)
{
    if (NULL == pMsg)
        return;

    switch (pMsg->GetType())
    {
    case MSG_INQUIREINVITEE:
        OnMsgInquireInvitee(pMsg);
        return;
    case MSG_ACKINQUIREINVITEE:
        OnMsgAckInquireInvitee(pMsg);
        return;
    case MSG_ACKJOINTEAM:
        OnMsgAckJoinTeam(pMsg);
        return;
    case MSG_DELETETEAMMEMBER:
        OnMsgDeleteTeamMember(pMsg);
        return;
    case MSG_EXITTEAM:
        OnMsgExitTeam(pMsg);
        return;
    case MSG_ADDTEAMMEMBER:
        OnMsgAddTeamMember(pMsg);
        return;
    case MSG_TEAM_PLAYERINFO:
        OnMsgTeamPlayerInfo(pMsg);
        return;
    case MSG_SWITCHGATE:
        OnMsg_SwitchGate(pMsg);
        return;
    default:
        break;
    }

}

void TeamBot::OnMsgTeamPlayerInfo(Msg* pMsg)
{
    Msg_Team_PlayerInfo* MsgTeamPlayer = (Msg_Team_PlayerInfo*) pMsg;
    std::vector<TeamMember>::iterator itr = find(VecTeam.begin(),VecTeam.end(),MsgTeamPlayer->dwDataBaseId);
    if (itr != VecTeam.end())
    {
        itr->bManipleHeader = MsgTeamPlayer->bHeader;
        itr->bTeamHeader = MsgTeamPlayer->bHeader;
        if (itr->bTeamHeader && m_TeamHeadId != MsgTeamPlayer->dwDataBaseId)
        {
            m_TeamHeadId = MsgTeamPlayer->dwDataBaseId;
        }
    }
}

void TeamBot::OnMsgAckJoinTeam(Msg* pMsg)
{
    MsgAckJoinTeam* pAckMsg = (MsgAckJoinTeam*)pMsg;
    if (pAckMsg->stError == MsgAckJoinTeam::error_succeed)
    {
        //m_bHaveTeam = true;
    }
}

//void TeamBot::OnMsg_PlayerEnterSight(Msg* pMsg)
//{
//    CBot::OnMsg_PlayerEnterSight(pMsg);
//    int ranNum = rand()%m_listPlayerList.size();// szName NPCName
//    list<PlayerInfo>::iterator itr = m_listPlayerList.begin();
//    if (itr != m_listPlayerList.)
//    {
//    }
//    m_listPlayerList. .szName;
//}


void TeamBot::OnMsgInquireInvitee(Msg* pMsg)
{
    MsgInquireInvitee* InquireMsg = (MsgInquireInvitee*)pMsg;


    SetTipsInfo("应答邀请组队");
    MsgAckInquireInvitee AckMsg;
    AckMsg.header.stID = GetBotShortId();
    AckMsg.bAgree = rand()%2 == 1?MsgAckInquireInvitee::result_agree:MsgAckInquireInvitee::result_nonAgree;
    AckMsg.AssignItemLevel = InquireMsg->AssignItemLevel;
    AckMsg.AssignMode = InquireMsg->AssignMode;
//    if (!m_bHaveTeam)
    {
        AckMsg.dwReqID = InquireMsg->dwReqID;
        strncpy_s(AckMsg.name,sizeof(AckMsg.name),InquireMsg->szReqName,sizeof(AckMsg.name)-1);
    }
//     else
//     {
//         AckMsg.dwReqID = GetBotDBID();
//         strncpy_s(AckMsg.name,sizeof(AckMsg.name),GetBotRoleName(),sizeof(AckMsg.name)-1);
//     }

    SendMsg(&AckMsg);
}

void TeamBot::OnMsgAckInquireInvitee(Msg* pMsg)
{
    MsgAckInquireInvitee* pAckMsg = (MsgAckInquireInvitee*)pMsg;
}

void TeamBot::OnMsgAddTeamMember(Msg* pMsg)
{
    MsgAddTeamMember* AddTeamMsg = (MsgAddTeamMember*) pMsg;

    if (AddTeamMsg->bIsNewAdd)
    {
        TeamMember team;
        team.bManipleHeader = AddTeamMsg->bHeader;
        team.bTeamHeader    = AddTeamMsg->bHeader;
        if ( AddTeamMsg->bHeader )
        {
            m_TeamHeadId = AddTeamMsg->dwMemberID;
        }
        team.dwDataBaseId = AddTeamMsg->dwMemberID;
        team.stManipleId = AddTeamMsg->stManiple;
        strncpy_s(team.MemberName,sizeof(team.MemberName),AddTeamMsg->szName,sizeof(team.MemberName)-1);
        team.dwGroupId = AddTeamMsg->dwGroupId;
        dwTeamId = AddTeamMsg->dwGroupId;
        vector<TeamMember>::iterator itr = find(VecTeam.begin(),VecTeam.end(),AddTeamMsg->dwMemberID);
        if (itr == VecTeam.end())
        {
            VecTeam.push_back(team);
        }
//         else
//         {
//             itr->bManipleHeader = AddTeamMsg->bHeader2;
//             itr->bTeamHeader    = AddTeamMsg->bHeader;
//             itr->stManipleId    = AddTeamMsg->stManiple;
// 
//         }
    }
    else
    {
        vector<TeamMember>::iterator itr = find(VecTeam.begin(),VecTeam.end(),AddTeamMsg->dwMemberID);
        if (itr != VecTeam.end())
        {
            itr->bManipleHeader = AddTeamMsg->bHeader;
            itr->bTeamHeader    = AddTeamMsg->bHeader;
            if ( AddTeamMsg->bHeader )
//             {
//                 //找到以前的队长ID，更换属性为非队长
//                 vector<TeamMember>::iterator oldItr = find(VecTeam.begin(),VecTeam.end(),m_TeamHeadId);
//                 if ( oldItr!= VecTeam.end())
//                 {
//                     oldItr->bTeamHeader = false;
//                 }
// 
//                 m_TeamHeadId = AddTeamMsg->dwMemberID;
//             }
            itr->dwGroupId = AddTeamMsg->dwGroupId;
            itr->stManipleId = AddTeamMsg->stManiple;
        }
        else
        {
            TeamMember team;
            team.bManipleHeader = AddTeamMsg->bHeader;
            team.bTeamHeader    = AddTeamMsg->bHeader;
            if ( AddTeamMsg->bHeader )
            {
                m_TeamHeadId = AddTeamMsg->dwMemberID;
            }
            team.dwDataBaseId = AddTeamMsg->dwMemberID;
            team.stManipleId = AddTeamMsg->stManiple;
            strncpy_s(team.MemberName,sizeof(team.MemberName),AddTeamMsg->szName,sizeof(team.MemberName)-1);
            team.dwGroupId = AddTeamMsg->dwGroupId;

            VecTeam.push_back(team);
        }
    }
    
}

bool TeamBot::RandInviteTeamMember()
{
    MsgRequestTeam InviteMsg;
    InviteMsg.header.stID = GetBotShortId();
    InviteMsg.AssignMode = rand()%AssignMode_Assign;
    InviteMsg.AssignItemLevel = rand()%eIL_Holiness;

    PlayerInfo* player = RandPlayer();
    if (NULL != player)
    {
        SetTipsInfo("随机邀请组队");
        InviteMsg.dwNewbieID = player->dwCharacterID; // 邀请人的DBID
        strncpy_s(InviteMsg.szNewbieName,sizeof(InviteMsg.szNewbieName),player->szName,sizeof(player->szName)-1);
        SendMsg(&InviteMsg);
        return true;
    }

    // 没有人就随机移动
    if (m_listPlayerList.empty())
    {
        Move();
//         if (0 == m_NoHavePlayerTime )
//         {
//             m_NoHavePlayerTime = HQ_TimeGetTime();
//         }

//         if ( HQ_TimeGetTime() - m_NoHavePlayerTime > NoHavePlayerTime )
//         {
//             LoadRandFlyMap();
//             RandFly();
//             bReqFlymap = true;
//         }
    }

    return false;
}

bool TeamBot::IsTeamMember(const char* PlayerName)
{
    if (NULL == PlayerName)
        return false;

    std::vector<TeamMember>::iterator itr = find(VecTeam.begin(),VecTeam.end(),PlayerName);
    if (itr != VecTeam.end())
        return true;

    return false;
}

bool TeamBot::BreakTeam()
{
    if (VecTeam.empty())
        return false;

    if (VecTeam.size() == 1)
        return false;

//     if (!IsHaveTeam())
//         return false;


    SetTipsInfo("删除队员");
    if (IsTeamHead())
    {
        int randNum = rand()%VecTeam.size();

        MsgKickFromTeam KickTeamMsg;
        KickTeamMsg.dwWho = VecTeam[randNum].dwDataBaseId;
        KickTeamMsg.header.stID = GetBotShortId();
        SendMsg(&KickTeamMsg);
        return true;
    }

    MsgExitTeam ExitMsg;
    ExitMsg.header.stID = GetBotShortId();
    ExitMsg.bIsDisband = false;
    SendMsg(&ExitMsg);
    return true;
}

void TeamBot::OnMsgExitTeam(Msg* pMsg)
{
    MsgExitTeam* ExitMsg = (MsgExitTeam*)pMsg;

    dwTeamId = ERRORTEAMID;
    m_TeamHeadId = 0;
    VecTeam.clear();
}

void TeamBot::OnMsgDeleteTeamMember(Msg* pMsg)
{
    MsgDeleteTeamMember* pDelete = (MsgDeleteTeamMember*)pMsg;
    vector<TeamMember>::iterator itr = find(VecTeam.begin(),VecTeam.end(),pDelete->dwMemberID);
    if (itr != VecTeam.end())
    {
        SetTipsInfo("删除队员");
        if (VecTeam.size() == 2)
        {
            dwTeamId = ERRORTEAMID;
            VecTeam.clear();
            return;
        }

        if (itr->dwDataBaseId == GetBotDBID())
        {
            dwTeamId = ERRORTEAMID;
            VecTeam.clear();
            return;
        }
        
        VecTeam.erase(itr);
    }
}

void TeamBot::TransferTeamHead()
{
    MsgReqUpgradeTeam MsgUpdateTeam;
    int randNum = rand()%VecTeam.size();

    if (VecTeam[randNum].dwDataBaseId == m_TeamHeadId)
    {
        return;
    }

    MsgUpdateTeam.dwID = VecTeam[randNum].dwDataBaseId;
    SendMsg(&MsgUpdateTeam);
}

bool TeamBot::CheckTeam()
{
    if (!IsHaveTeam())
    { return true; }
    
    if (VecTeam.size() > 6)
    {
        return false;
    }

//     if (VecTeam.size() == 1)
//     {
//         VecTeam.clear();
//         m_bHaveTeam = false;
//         return true;
//     }

    int TeamHeadNum = 0;
    for (std::vector<TeamMember>::iterator itr = VecTeam.begin(); itr != VecTeam.end();++itr)
    {
        if (itr->bTeamHeader)
        {
            ++TeamHeadNum;
        }
    }
    if (TeamHeadNum > 1|| TeamHeadNum <= 0)
    {
        return false;
    }

    return true;
}

void TeamBot::LogTeam()
{
    for (std::vector<TeamMember>::iterator itr = VecTeam.begin(); itr != VecTeam.end();++itr)
    {
        LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR,"TeamId [%d],RoleName [%s],TeamHead [%d]",itr->dwGroupId,itr->MemberName,itr->bTeamHeader?1:0);
    }
}

void TeamBot::BreakGameToSelectRole()
{
    return; // 暂时关闭
    // 回到选人界面
    SetTipsInfo("回到选人界面");
    MsgReturnToCharacterServer ReturnMsg;
    SendMsg(&ReturnMsg);
    m_ReturnSelRole = true;
}

void TeamBot::GoToEctypeMap()
{
    if (!IsTeamHead())
        return;
    
    // 下副本
    if (m_LastMapId == -1)
    { SaveLastMapInfo(); }

    if (m_ReqGoToEctype)
    { return; }

    if (HQ_TimeGetTime() - ReqFlyEctypeTime >=  60*1000)
    {
        CGameBotApp::EctypeMaps result = theApp.FlyEctypeMapTableByPlayerNum[ GetMapID() ];
        if (result.size() != 0)
        {
            if (result.size() == 1)
            {
                FlyToMap(result[0].EctyprMapID,result[0].EnterMapX,result[0].EnterMapY);
                ReqFlyEctypeTime = HQ_TimeGetTime();
                ReqFlyEctypeMapId = result[0].EctyprMapID;
                return;
            }
            else
            {
                DWORD RandNum = rand()%result.size();
                FlyToMap(result[RandNum].EctyprMapID,result[RandNum].EnterMapX,result[RandNum].EnterMapY);
                ReqFlyEctypeTime = HQ_TimeGetTime();
                ReqFlyEctypeMapId = result[0].EctyprMapID;
                return;
            }
        }
        else
        {
            LoadRandFlyMap();
            RandFly();
        }
        ReqFlyEctypeTime = HQ_TimeGetTime();
    }


    
    m_EnterEctypeMapTime = HQ_TimeGetTime();
}

std::string TeamBot::GetTeamHeadName()
{
    if (!IsHaveTeam())
    {
        return "";
    }
    for (std::vector<TeamMember>::iterator itr = VecTeam.begin();itr!=VecTeam.end();++itr)
    {
        if (itr->dwDataBaseId == m_TeamHeadId)
        {
            return itr->MemberName;
        }
    }
    return "";
}

void TeamBot::TeamTalk()
{
    MsgChat Msg(MsgChat::CHAT_TYPE_TERM);
    Msg.header.stID = GetBotShortId();
    //strncpy_s(Msg.chatHeader.szToName,sizeof(Msg.chatHeader.szToName),itr->MemberName,sizeof(Msg.chatHeader.szToName)-1);
    char chatBuff[512];
    sprintf_s(chatBuff,sizeof(chatBuff),"这是%s的队伍,TeamId = %d,我是%s",GetTeamHeadName().c_str(),VecTeam.begin()->dwGroupId,m_CharInfo.baseinfo.aptotic.szCharacterName);
    Msg.SetString(chatBuff);
    SendMsg(&Msg);

//     for (std::vector<TeamMember>::iterator itr = VecTeam.begin();itr!=VecTeam.end();++itr)
//     {
//         if (itr->dwDataBaseId == GetBotDBID())
//             continue;
// 
//         MsgChat Msg(MsgChat::CHAT_TYPE_TERM);
//         Msg.header.stID = GetBotShortId();
//         strncpy_s(Msg.chatHeader.szToName,sizeof(Msg.chatHeader.szToName),itr->MemberName,sizeof(Msg.chatHeader.szToName)-1);
//         char chatBuff[512];
//         sprintf_s(chatBuff,sizeof(chatBuff),"这是%s的队伍,TeamId = %d,我是%s",GetTeamHeadName().c_str(),itr->dwGroupId,m_CharInfo.baseinfo.aptotic.szCharacterName);
//         Msg.SetString(chatBuff);
//         SendMsg(&Msg);
//     }
}

bool TeamBot::IsTeamEctypeMap(const int mapID)
{
    if (mapID < 0)
        return false;

    for (CGameBotApp::EctypeMapContainer::iterator itr = theApp.FlyEctypeMapTableByPlayerNum.begin();itr!= theApp.FlyEctypeMapTableByPlayerNum.end();++itr)
    {
        for (CGameBotApp::EctypeMaps::iterator itrEctypeMap = itr->second.begin();itrEctypeMap != itr->second.end();++itrEctypeMap)
        {
            if (mapID == itrEctypeMap->EctyprMapID)
            {
                return true;
            }
        }
    }
    return false;
}
