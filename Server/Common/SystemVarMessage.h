#ifndef __SYSTEMVARMESSAGE_H__
#define __SYSTEMVARMESSAGE_H__

#include "MsgBase.h"
#include "SystemVarDefine.h"
#include "MessageRangeDefine.h"

#pragma pack( push, 1 )

enum SystemVarMessageDefine
{
    GS2CS_SENDCHANGEVARREQ  = SYSTEM_VAR_BEGIN,     // GS 2 CS ϵͳ�����ı���Ϣ
    GS2CS_SENDCHANGEVARACK  ,     // GS 2 CS ϵͳ�����ı����
    CS2DB_SAVESYSTEMVARREQ  ,     // ����ϵͳ������DB
    DB2CS_LOADSYSTEMVARACK  ,     // DB����ϵͳ������CS
    CS2DB_LOADSYSTEMVARREQ  ,     // CS���͵�DB����ϵͳ����
    CS2GS_SYSTEMVAR         ,     // CS ����ϵͳ������GS
    DB2CS_LOADSYSVARSUCCESS ,     // DB ���͸� CS����ϵͳ�����ɹ�
};
// ����ϵͳ����
struct GS2CSSendChangeVarReq : public Msg
{
    GS2CSSendChangeVarReq()
    {
        header.dwType = GS2CS_SENDCHANGEVARREQ;
        header.stLength = sizeof(GS2CSSendChangeVarReq);
        serverId = -1;
        memset( szName, 0, sizeof(szName) );
    }
    uint32 serverId;    // ������ID
    int  nKey;          // ������Ӧ��key
    int  nIndex;        // ������Ӧ��Index
    char szName[SystemVarDefine::NAME_LENGTH];    // ϵͳ��������
    int  nVar;          // ����ֵ
};

//struct GS2CSSendChangeVarAck : public Msg
//{
//    enum eResultDefine
//    {
//        ED_Error   = 0,     // ʧ��
//        ED_Success = 1,     // �ɹ�
//    };
//
//    GS2CSSendChangeVarAck()
//    {
//        header.dwType = GS2CS_SENDCHANGEVARACK;
//        header.stLength = sizeof(GS2CSSendChangeVarAck);
//    }
//
//    unsigned int nResult;   // ���
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