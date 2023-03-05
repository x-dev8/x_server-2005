#include "Bot.h"
#include "MessageDefine.h"
#include "LoginBot.h"

#define InitOnlineTime (0)
CLoginBot::CLoginBot()
{
    m_nOnlineTime = 20;
    m_dwLoginTime = InitOnlineTime;
    m_BotType = Bot_Login;
}

CLoginBot::~CLoginBot(void)
{
}

void CLoginBot::PlayGame()
{
    if (m_dwLoginTime == InitOnlineTime)
    {
        BaseRobot::PlayGame();
        return;
    }

    if(HQ_TimeGetTime() - m_dwLoginTime >= m_nOnlineTime * 1000)
    {
        MsgExit exit;
        SendMsg(&exit);
        m_bIsLoginGLS  = false;        
        DWORD curtime = HQ_TimeGetTime();
        while(true)
        {
            if (HQ_TimeGetTime() - curtime >= 10*1000)
            {
                break;
            }
        }
        //SetSleep(10*1000,HQ_TimeGetTime());
        //Close();
    }
}

void CLoginBot::OnMsgAckEnterWorld( Msg* pMsg )
{
    BaseRobot::OnMsgAckEnterWorld(pMsg);
    m_dwLoginTime = HQ_TimeGetTime();
}

void CLoginBot::SetAreaInfo(SAreaInfo *pAreaInfo)
{
    if (pAreaInfo  != NULL)
    {
        m_xAreaInfo.nMap = pAreaInfo->nMap;
        m_xAreaInfo.xPoint.x = pAreaInfo->xPoint.x;
        m_xAreaInfo.xPoint.y = pAreaInfo->xPoint.y;
        m_xAreaInfo.nRadius = pAreaInfo->nRadius;
    }		
}