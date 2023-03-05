#pragma once
#include "GameDefineBot.h"

class CLoginBot :
    public BaseRobot
{
public:
    CLoginBot(void);
public:
    virtual ~CLoginBot(void);

    inline void SetOnlineTime(int nTime) { m_nOnlineTime = nTime; } 

    virtual void PlayGame();

    virtual void OnMsgAckEnterWorld( Msg* pMsg );

    virtual void SetAreaInfo(SAreaInfo *pAreaInfo);

private:
    DWORD m_dwLoginTime;
    int m_nOnlineTime;

    SAreaInfo m_xAreaInfo;
};
