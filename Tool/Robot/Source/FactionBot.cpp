#pragma once

#include "FactionBot.h"

#define BUFFERSIZE 512
#define ONE_MINUTE 60*1000

CFactionBot::CFactionBot():
bCreateSwornSuccess(false),
bHaveGuild(false),
LastCreateTime(HQ_TimeGetTime())
{

}

CFactionBot::~CFactionBot()
{

}

void CFactionBot::PlayGame()
{
    // 创建结义
    // 没有公会或者没有创建成功
    if (HQ_TimeGetTime() - LastCreateTime <= ONE_MINUTE) //1分钟 
    {
        CNormalBot::PlayGame();
        return;
    }

    LastCreateTime = HQ_TimeGetTime();
    if (!bCreateSwornSuccess || !bHaveGuild)
    {
        MsgGuildQueryCreate CreateGuildMsg;
        CreateGuildMsg.bCancelCreate = false;
        strncpy_s(CreateGuildMsg.szGuildName,sizeof(CreateGuildMsg.szGuildName),m_vectorCharInfo[0].aptotic.szCharacterName,sizeof(CreateGuildMsg.szGuildName)-1);

        SwronName = CreateGuildMsg.szGuildName;
        SendMsg(&CreateGuildMsg);
    }
    // 结义频道说话 创建了 xx公会
    if (bCreateSwornSuccess || bHaveGuild)
    {
//         char ChatBuffer[BUFFERSIZE];
//         sprintf_s(ChatBuffer,sizeof(ChatBuffer)-1,"[%s] 帮派,帮派中的战斗机",SwronName.c_str());
//         Say(ChatBuffer);
    }
    // 解散公会 
    if (bHaveGuild)
    {
        MsgGuildQueryDismiss DismissMsg;
        SendMsg(&DismissMsg);
        DisSwron();
    }
    
}

void CFactionBot::InitSwronState()
{
    bCreateSwornSuccess = false;
    bHaveGuild = false;
}

void CFactionBot::CreateSwronSucc()
{
    bCreateSwornSuccess = true;
    bHaveGuild = true;
}

void CFactionBot::DisSwron()
{
    bCreateSwornSuccess = false;
    bHaveGuild = false;
}

void CFactionBot::InitPlayGame()
{
    CNormalBot::InitPlayGame();
}

void CFactionBot::SwitchMsg(Msg* pMsg)
{
    if (pMsg == NULL)
    {
        return;
    }

    switch(pMsg->GetType())
    {
    case MSG_ACK_GUILDCREATE:
        {
            MsgAckGuildCreate* AckMsg  =(MsgAckGuildCreate*)pMsg;
            if (AckMsg->shResult == MsgAckGuildCreate::RESULT_SUCCESS)
            {
                // 应答创建帮派
                CreateSwronSucc();
            }
        }
        break;
    case MSG_GUILD_TELL_JOIN:
        {
            //加入帮派
            MsgGuildTellJoin* JoinMsg = (MsgGuildTellJoin*)pMsg;

            if(SwronName.compare(JoinMsg->member.szName)==0)
            {
                CreateSwronSucc();
            }
        }
        break;
    case MSG_ACKGUILDINFO:
        {
            //登录的时候，初始化自己的公会
            MsgAckGuildInfo* AckMsg = (MsgAckGuildInfo*)pMsg;
            SwronName = AckMsg->stGuildInfo.m_szName;
            CreateSwronSucc();
        }
        break; 
    case MSG_GUILD_TELL_DISMISS:
        {
            DisSwron();
        }
        break;
    }
    CNormalBot::SwitchMsg(pMsg);
}
