#include "stdafx.h"
#include "GameDefineBot.h"
#include "NormalBot.h"
#define  ERRORTEAMID -1
class TeamBot:public CNormalBot
{
public: 
    enum TeamOperation
    {
        ETO_InviteTeam = 0,
        ETO_BreakTeam = 1,
        ETO_TransferTeamHead = 2,
        ETO_Moveing = 3,
        ETO_ChangeTeamAssign = 4,
        ETO_BreakGame = 5,
        ETO_Ectype = 6,
        ETO_TeamChat = 7,
        ETO_ChangeMap = 8,
        ETO_TotalOperation,
    };
    struct TeamMember
    {
        DWORD dwDataBaseId;  // 数据库Id(唯一)
        short stManipleId;   // 所在小队的Id
        bool bManipleHeader; // 是否是小队长
        bool bTeamHeader;    // 是否是大队长
        char MemberName[dr_MaxPlayerName];
        bool operator == (const DWORD &DataBaseId)
        {
            return dwDataBaseId == DataBaseId;
        }
        bool operator == (const std::string &PlayerName)
        {
            return PlayerName.compare(MemberName) == 0;
        }
        DWORD dwGroupId;
    };

    TeamBot();
    virtual ~TeamBot();

    virtual void InitPlayGame(UINT mapid = 0);
    virtual void PlayGame();
    virtual void PlayTeam(DWORD dwTime);
    
    virtual void SwitchMsg(Msg* pMsg);

    bool RandInviteTeamMember();
    bool BreakTeam();
    bool CheckTeam();    
    void TransferTeamHead();
    void LogTeam();
    bool IsTeamHead(){ if (m_TeamHeadId <= 0)return false; return GetBotDBID() == m_TeamHeadId; }
    void ChangeTeamAssign();
    void BreakGameToSelectRole();
    void GoToEctypeMap();
    void RandFlyTeamMap();
    void LoadTeamMap();

    std::string GetTeamHeadName();

    void TeamTalk();
    bool IsTeamMember(const char* PlayerName);
    bool IsInTeamMap(const int MapId);
    void SaveLastMapInfo();
    bool IsHaveTeam(){ return dwTeamId != ERRORTEAMID;}
    bool IsTeamEctypeMap(const int mapID);
protected:
    virtual void OnMsgInquireInvitee(Msg* pMsg);
    virtual void OnMsgAckInquireInvitee(Msg* pMsg);
    virtual void OnMsgAddTeamMember(Msg* pMsg);
    virtual void OnMsgAckJoinTeam(Msg* pMsg);
    virtual void OnMsgDeleteTeamMember(Msg* pMsg);
    virtual void OnMsgExitTeam(Msg* pMsg);
    virtual void OnMsgTeamPlayerInfo(Msg* pMsg);

private:
    short m_CurTeamNum;
    DWORD m_RunTime;
    DWORD m_TeamHeadId;
    bool  m_PlayGame;
    std::vector<TeamMember> VecTeam;// 小队成员列表
    bool bReqFlymap;
    DWORD m_NoHavePlayerTime;
    bool m_Breakteam;
    bool m_ReturnSelRole;       // 是否是返回选择人物界面

    int m_LastMapId;
    float m_MapX;
    float m_MapY;
    bool m_IsChangeMap;
    DWORD m_LastChangeMapTime;
    short m_ReqFlyNum;
    DWORD m_LastMoveTime;
    DWORD m_OnEctypeMapTime;
    DWORD m_EnterEctypeMapTime;
    DWORD m_ReqLeaveEctypeMapTime;
    bool m_ReqGoToEctype;

    DWORD   ReqFlyEctypeTime;
    int     ReqFlyEctypeMapId;

    std::vector<int> vecTeamMap;
    DWORD ReqFlyTeamMapTime;

    DWORD dwTeamId;
};