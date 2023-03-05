#ifndef __SYSTEMVARMESSAGE_H__
#define __SYSTEMVARMESSAGE_H__

#include "MsgBase.h"
#include "SystemVarDefine.h"
#include "MessageRangeDefine.h"

#pragma pack( push, 1 )

enum SystemVarMessageDefine
{
    GS2CS_SENDCHANGEVARREQ  = SYSTEM_VAR_BEGIN,     // GS 2 CS 系统变量改变消息
    GS2CS_SENDCHANGEVARACK  ,     // GS 2 CS 系统变量改变回馈
    CS2DB_SAVESYSTEMVARREQ  ,     // 保存系统变量给DB
    DB2CS_LOADSYSTEMVARACK  ,     // DB加载系统变量到CS
    CS2DB_LOADSYSTEMVARREQ  ,     // CS发送到DB加载系统变量
    CS2GS_SYSTEMVAR         ,     // CS 发送系统变量给GS
    DB2CS_LOADSYSVARSUCCESS ,     // DB 发送给 CS加载系统变量成功
};
// 保存系统变量
struct GS2CSSendChangeVarReq : public Msg
{
    GS2CSSendChangeVarReq()
    {
        header.dwType = GS2CS_SENDCHANGEVARREQ;
        header.stLength = sizeof(GS2CSSendChangeVarReq);
        serverId = -1;
        memset( szName, 0, sizeof(szName) );
    }
    uint32 serverId;    // 服务器ID
    int  nKey;          // 变量对应的key
    int  nIndex;        // 变量对应的Index
    char szName[SystemVarDefine::NAME_LENGTH];    // 系统变量名称
    int  nVar;          // 变量值
};

//struct GS2CSSendChangeVarAck : public Msg
//{
//    enum eResultDefine
//    {
//        ED_Error   = 0,     // 失败
//        ED_Success = 1,     // 成功
//    };
//
//    GS2CSSendChangeVarAck()
//    {
//        header.dwType = GS2CS_SENDCHANGEVARACK;
//        header.stLength = sizeof(GS2CSSendChangeVarAck);
//    }
//
//    unsigned int nResult;   // 结果
//};

struct CS2DBSaveSystemVarReq : public Msg
{
    CS2DBSaveSystemVarReq()
    {
        header.dwType = CS2DB_SAVESYSTEMVARREQ;
        header.stLength = sizeof(CS2DBSaveSystemVarReq);
        memset(xSystemVar.sysVar, 0, sizeof(xSystemVar.sysVar));
    }
    SystemVar xSystemVar;
};

struct CS2DBLoadSystemVarReq : public Msg
{
    CS2DBLoadSystemVarReq()
    {
        header.dwType = CS2DB_LOADSYSTEMVARREQ;
        header.stLength = sizeof(CS2DBLoadSystemVarReq);
    }
};

struct DB2CSLoadSystemVarAck : public Msg
{
    DB2CSLoadSystemVarAck()
    {
        header.dwType = DB2CS_LOADSYSTEMVARACK;
        header.stLength = sizeof(DB2CSLoadSystemVarAck);
    }
    SystemVar xSystemVar;
};

struct CS2GSSystemVar : public Msg
{
    CS2GSSystemVar()
    {
        header.dwType = CS2GS_SYSTEMVAR;
        header.stLength = sizeof(CS2GSSystemVar);
    }
    SystemVar xSystemVar;
};

struct DB2CSLoadSysVarSuccess : public Msg
{
    DB2CSLoadSysVarSuccess()
    {
        header.dwType = DB2CS_LOADSYSVARSUCCESS;
        header.stLength = sizeof(DB2CSLoadSysVarSuccess);
    }
};

#pragma pack( pop )

#endif