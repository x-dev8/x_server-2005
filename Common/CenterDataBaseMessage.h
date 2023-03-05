#ifndef __CENTERDATABASEMESSAGE_H__
#define __CENTERDATABASEMESSAGE_H__

#pragma once

#include "MsgBase.h"
//#include "MessageDefine.h"
#include "DBMessageDefine.h"
#include "PlatformMessageDefine.h"
#include "GlobalDef.h"

#pragma pack( push, 1 ) 

//CenterServer2DBServer
enum CenterServerDBServerMessage
{
    CS2DB_REGISTERDBSERVERINFO_REQ = CENTERDBSERVER_MESSAGE_BEGIN,
    CS2DB_REGISTERDBSERVERINFO_ACK,
    CS2DB_ACCOUNTPOINTER_REQ, // 请求帐号冲值
    DB2CS_ACCOUNTPOINTER_ACK, // 回馈冲值冲值
};

struct CS2DBRegiseterDBServerInfoReq : public Msg
{   
    CS2DBRegiseterDBServerInfoReq()
    {
        header.dwType = CS2DB_REGISTERDBSERVERINFO_REQ;
        header.stLength = sizeof( CS2DBRegiseterDBServerInfoReq );
        Reset();
    }

    enum RegisterOpType
    {
        ROT_NOT_REPLACE,
        ROT_REPLACE,
    };

    void Reset()
    {
        memset( szDBServerName, 0, sizeof(szDBServerName));
        btReset = ROT_NOT_REPLACE;
        nServerId = 0;
    }

    char szDBServerName[60];
    unsigned long nServerId;
    char btReset;
};

struct DB2CSGameServerInfoAck : public Msg
{
    DB2CSGameServerInfoAck()
    {
        header.dwType   = CS2DB_REGISTERDBSERVERINFO_ACK;
        header.stLength = sizeof( DB2CSGameServerInfoAck );
    }   

    unsigned short nResult;
};

struct CS2DBAccountPoints : public S2SMsg
{
    CS2DBAccountPoints()
    {
        header.dwType   = CS2DB_ACCOUNTPOINTER_REQ;
        header.stLength = sizeof( CS2DBAccountPoints );
        guid = 0;
        memset( &info, 0, sizeof(info));
    }

    uint32     guid;
    SAddPoints info;
};

struct DB2CSAccountPoints : public S2SMsg
{
    DB2CSAccountPoints()
    {
        header.dwType   = DB2CS_ACCOUNTPOINTER_ACK;
        header.stLength = sizeof( DB2CSAccountPoints );
        result = ER_Success;
        guid   = 0;
        points = 0;
        memset( &typesn, 0, sizeof(typesn));
    }

    uint32 result;
    uint32 guid;
    uint32 points;
    int8   typesn[32]; // 订单号
};

#pragma pack( pop ) 

#endif //__CENTERDATABASEMESSAGE_H__
