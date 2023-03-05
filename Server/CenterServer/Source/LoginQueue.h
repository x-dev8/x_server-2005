#pragma once
#ifndef __LOGIN_QUEUE__
#define __LOGIN_QUEUE__
#include "ClientPeer.h"
/*
* ·ÏÆúµÄ cloud
**/
class TokenCenter
{
public:
    typedef std::list<ClientPeer*> TokenQueueType;
    ~TokenCenter();
    static TokenCenter& Instance();
    bool    Lease(ClientPeer* pClientPeer);
    bool    Reversion(ClientPeer* pClientPeer);
    unsigned short GetCurTokenNum();
    bool HaveIdlesseToken() const;
    void AutoRestore();

//     bool AddClientPeerToQueue(ClientPeer* pClientPeer);
//     bool RemoveFromClientPeer(ClientPeer* pClientPeer);
//     ClientPeer* FindClientPeerById(unsigned long AccountId);
//     ClientPeer* PopFirstClientPeer();
    
private:
    TokenCenter();
    TokenCenter(const TokenCenter &TokenCenter);
    TokenCenter& operator =(const TokenCenter &TokenCenter);

    unsigned short TickNum;
    
    bool isFirstLease;
    unsigned long CheckTime;

    TokenQueueType TokenQueue;
};

#endif