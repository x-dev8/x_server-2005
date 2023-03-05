#pragma once
#include "stdafx.h"

#include "NormalBot.h"
#include <string>

class CFactionBot:
public CNormalBot
{
public:
    CFactionBot();
    virtual ~CFactionBot();

    virtual void PlayGame();
    virtual void InitPlayGame();

    virtual void SwitchMsg(Msg* pMsg);

    void InitSwronState();
    void CreateSwronSucc();
    void DisSwron();


private:
    std::string         SwronName;
    volatile bool       bCreateSwornSuccess;
    volatile bool       bHaveGuild;

    unsigned long       LastCreateTime;
};