#include "stdafx.h"
#include "Attackbot.h"


class EctypeBot:public CAttackBot
{
public:
    static DWORD EctypeMapTimeSpace;

    EctypeBot();
    ~EctypeBot();

    virtual void PlayGame();
    virtual void InitPlayGame(UINT MapId);
    void LeaveEctypeMap();

    virtual void OnMsg_Ping(Msg* pMsg);
    virtual void SwitchMsg(Msg* pMsg);

    bool InEctypeMap(int CurMapid);
    void ReqOpenEcTypeMap4XiYuan();
public:
    virtual void OnMsgChangeMap(Msg* pMsg);

public: 
    // OnMsg
    virtual void OnMsg_Ack_Script(Msg* pMsg);
private:
    bool  ReadlyFlyToEctype;
    DWORD ReqFlyEctypeTime;
    int ReqFlyMapId;
    DWORD OnEctypeTime;
    DWORD SendPingTime;
    DWORD LastLockTargetTime;
    short Targetmap;
};