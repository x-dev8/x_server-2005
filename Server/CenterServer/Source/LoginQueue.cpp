#include "loginqueue.h"
#include "MeRTLibsServer.h"
#include "Config.h"
#include "GlobalDef.h"
#include "GameTime.h"

TokenCenter::~TokenCenter()
{

}

TokenCenter::TokenCenter():isFirstLease(true),CheckTime(0),TickNum(Config::GetInstance().usMaxTickNum)
{
    
}

TokenCenter& TokenCenter::Instance()
{
    static TokenCenter StaticTickCenter;
    return StaticTickCenter;
}

bool    TokenCenter::Lease(ClientPeer *pClientPeer)
{
    if (!pClientPeer)
    {
        return false;
    }
    if (TickNum == 0)
    {
        return false;
    }
    if (pClientPeer->HaveToken())
    {
        return true;
    }
    --TickNum;
    pClientPeer->GetToken();
    return true;
}

bool TokenCenter::Reversion(ClientPeer* pClientPeer)
{
    if (!pClientPeer)
    {
        return false;
    }

    if (pClientPeer->HaveToken())
    {
        pClientPeer->MissToken();
    }
    else
    {
        return false;
    }

    ++TickNum;
    if (TickNum >= Config::GetInstance().usMaxTickNum)
    {
        TickNum = Config::GetInstance().usMaxTickNum;
    }
    return true;
}

unsigned short TokenCenter::GetCurTokenNum()
{
    return TickNum;
}

bool TokenCenter::HaveIdlesseToken() const
{
    return TickNum != 0;
}

void TokenCenter::AutoRestore()
{
    //初始化
    if (CheckTime == 0)
    {
        CheckTime = HQ_TimeGetTime();
        return;
    }

    if( GameTime::IsPassCurrentTime( CheckTime, 60000 ) )//每一分钟检查一次，回复一次
    {
        if (TickNum == 0)
            TickNum = Config::GetInstance().usMaxTickNum;
        CheckTime = HQ_TimeGetTime();
    }
}

// bool TokenCenter::AddClientPeerToQueue(ClientPeer* pClientPeer)
// {
//     if (!pClientPeer)
//     {
//         return false;
//     }
//     SLoginInfoBase& rLoginInfoBase = pClientPeer->GetLoginInfo();
//     TokenQueueType::iterator itr = find(TokenQueue.begin(),TokenQueue.end(),rLoginInfoBase.nAccountID);
//     if (itr != TokenQueue.end())
//     {
//         return false;
//     }
//     TokenQueue.push_back(pClientPeer);
//     return true;
// }
// 
// bool TokenCenter::RemoveFromClientPeer(ClientPeer* pClientPeer)
// {
//     if (!pClientPeer)
//     {
//         return false;
//     }
//     SLoginInfoBase& rLoginInfoBase = pClientPeer->GetLoginInfo();
//     TokenQueueType::iterator itr = find(TokenQueue.begin(),TokenQueue.end(),rLoginInfoBase.nAccountID);
//     if (itr == TokenQueue.end())
//     {
//         return false;
//     }
//     
//     TokenQueue.erase(itr);
//     return true;
// }
// 
// ClientPeer* TokenCenter::FindClientPeerById(unsigned long AccountId)
// {
//     TokenQueueType::iterator itr = find(TokenQueue.begin(),TokenQueue.end(),AccountId);
//     if (itr == TokenQueue.end())
//     {
//         return NULL;
//     }
//     return *itr;
// }
// 
// ClientPeer* TokenCenter::PopFirstClientPeer()
// {
//     if (TokenQueue.empty())
//     {
//         return NULL;
//     }
// 
//     ClientPeer* First = TokenQueue.front();
//     TokenQueue.pop_front();
//     return First;
// }
