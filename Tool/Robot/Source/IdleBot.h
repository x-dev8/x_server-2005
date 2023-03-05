#include "stdafx.h"
#include "Bot.h"
#include "GameDefineBot.h"
#include <string>

class OnlineBot:public BaseRobot
{
public:
    enum EOperation
    {
        EP_FISH = 0,
        EP_CHANGENAME = 1,
        EP_TOTAL,
    };
public:
    OnlineBot();
    ~OnlineBot();

    virtual void PlayGame();
    virtual void InitPlayGame(UINT mapid = 0);
    int GetFishToolIndexInBag();
    void GetFish();
    void SetAreaInfo(SAreaInfo *pAreaInfo);
    void ReqChangeCharacterName(char* szNewName);

    void SwitchMsg(Msg* pMsg);

    void OnMsgNotifyBeKick(Msg* pMsg);
    SAreaInfo m_xAreaInfo;
private:
    DWORD m_PingTime;
    bool  m_PlayGame;
    DWORD ReqRandFlyTime;
    DWORD RunTime;
    DWORD UseFishItemTime;
    bool IsSendMoveOnce; //ÊÇ·ñÒÆ¶¯¹ý
    bool IsClear;

};