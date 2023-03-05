#ifndef __COMMON_CENTERLOGINMESSAGE_H__
#define __COMMON_CENTERLOGINMESSAGE_H__

#pragma once

#include "MsgBase.h"

#pragma pack( push, 1 ) 

enum CenterServerLoginServerMessage
{
    LS2CS_REGISTERLOGINSERVERINFO_REQ = CENTERLOGIN_MESSAGE_BEGIN, // 注册LoginServer请求
    CS2LS_REGISTERLOGINSERVERINFO_ACK,                             // 注册LoginServer应答
};

//////////////////////////////////////////////////////////////////////////

struct LS2CSRegiseterLoginServerInfoReq : public Msg
{
    enum RegisterOpType
    {
        ROT_NOT_REPLACE,
        ROT_REPLACE,
		ROT_LOOP,//循环注册 一直到注册上为止
    };

    LS2CSRegiseterLoginServerInfoReq()
    {
        header.dwType = LS2CS_REGISTERLOGINSERVERINFO_REQ;
        header.stLength = sizeof( LS2CSRegiseterLoginServerInfoReq );

        nLoginServerId = -1;
        btReset = ROT_NOT_REPLACE;
    }

    long nLoginServerId;
    char btReset;
};

struct CS2LSRegiseterLoginServerInfoAck : public Msg
{
    CS2LSRegiseterLoginServerInfoAck()
    {
        header.dwType = CS2LS_REGISTERLOGINSERVERINFO_ACK;
        header.stLength = sizeof( CS2LSRegiseterLoginServerInfoAck );

        nResult = ER_Success;
    }   

    unsigned short nResult;
};

#pragma pack( pop ) 

//////////////////////////////////////////////////////////////////////////
#endif // __COMMON_CENTERLOGINMESSAGE_H__
