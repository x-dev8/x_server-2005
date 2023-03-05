#ifndef __BARGAININTMESSAGE_H__
#define __BARGAININTMESSAGE_H__

/************************************************************************
            摆摊消息定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "BargainingDefine.h"
#include "MessageRangeDefine.h"

#pragma pack( push, 1 )

enum BargainingMessageDefine
{
    MSG_BARGAININGREQ = GAMEWORD_BARGAININGMSG_BEGIN,
    MSG_BARGAININGACK,
    MSG_BARGAININGREQUESTREQ,
    MSG_BARGAININGREQUESTACK,
    MSG_BARGAININGSTART,
    MSG_BARGAININGFINISH,
    MSG_BARGAININGSTATUS,
    MSG_BARGAININGDATAREQ,
    MSG_BARGAININGDATAACK,
    MSG_BARGAININGDATAERROR,
    MSG_SHOWBARGAININGDATA,
    MSG_BARGAININGLOCKREQ,
    MSG_BARGAININGFIXREQ,
    MSG_BARGAININGCANCELREQ,
    MSG_REMOVEBARGAININGDATAREQ,
    MSG_REMOVEBARGAININGDATAACK,
};

struct MsgBargainingModule : public Msg
{
    MsgBargainingModule()
    {
        SetModuleType( EMessageModule_Bargaining );
    }
};

// 申请与某玩家交易
struct MsgBargainingReq : public MsgBargainingModule
{   
    MsgBargainingReq()
    {
        header.dwType   = MSG_BARGAININGREQ;
        header.stLength = sizeof( MsgBargainingReq );
    }

    GameObjectId ustPlayerID;     // 玩家动态ID
};

// 交易申请回馈
struct MsgBargainingAck : public MsgBargainingModule
{   
    MsgBargainingAck()
    {
        header.dwType   = MSG_BARGAININGACK;
        header.stLength = sizeof( MsgBargainingAck );
    }

    unsigned char uchResult;
};

// 通知客户端, 某人申请与你交易
struct MsgBargainingRequestReq : public MsgBargainingModule
{   
    MsgBargainingRequestReq()
    {
        header.dwType   = MSG_BARGAININGREQUESTREQ;
        header.stLength = sizeof( MsgBargainingRequestReq );
    }

    GameObjectId ustPlayerID;     // 玩家动态ID
};

// 对方回应是否同意交易
struct MsgBargainingRequestAck : public MsgBargainingModule
{   
    MsgBargainingRequestAck()
    {
        header.dwType   = MSG_BARGAININGREQUESTACK;
        header.stLength = sizeof( MsgBargainingRequestAck );
    }

    bool bBargainintAgree;
};

// 通知客户端  与某人的交易开始
struct MsgBargainingStart : public MsgBargainingModule
{   
    MsgBargainingStart()
    {
        header.dwType   = MSG_BARGAININGSTART;
        header.stLength = sizeof( MsgBargainingStart );
    }

    GameObjectId ustPlayerID;     // 玩家动态ID
};

// 通知客户端  交易结束
struct MsgBargainingFinish : public MsgBargainingModule
{   
    MsgBargainingFinish()
    {
        header.dwType   = MSG_BARGAININGFINISH;
        header.stLength = sizeof( MsgBargainingFinish );
    }

    unsigned char uchFinishType;
};

// 通知客户端 某玩家的交易状态
struct MsgBargainingStatus : public MsgBargainingModule
{   
    MsgBargainingStatus()
    {
        header.dwType   = MSG_BARGAININGSTATUS;
        header.stLength = sizeof( MsgBargainingStatus );
    }

    GameObjectId ustPlayerID;     // 玩家动态ID
    unsigned char uchStatus;
};

// 玩家申请往交易栏中放钱 或者放物品
struct MsgBargainingDataReq : public MsgBargainingModule
{
    MsgBargainingDataReq()
    {
        header.dwType   = MSG_BARGAININGDATAREQ;
        header.stLength = sizeof( MsgBargainingDataReq );
    }

    unsigned char uchBargainintType;    // 交易类型 ...BargainingMoney...

    // 游戏币, 金锭使用这个变量
    unsigned int nBargainingValue;      // 交易的数值
    
    // 道具类 使用这4个变量
    unsigned char uchBargainingIndex;  // 交易栏索引
    unsigned char uchBagType;          // 背包类型
    unsigned char uchIndex;            // 背包索引
    __int64 n64Guid;                   // 物品guid
};

// 通知玩家加入了物品到交易栏中
struct MsgBargainingDataAck : public MsgBargainingModule
{
    MsgBargainingDataAck()
    {
        header.dwType   = MSG_BARGAININGDATAACK;
        header.stLength = sizeof( MsgBargainingDataAck );
    }

    unsigned char uchBargainintType;    // 交易类型 ...BargainingMoney.等..

    // 游戏币, 金锭使用这个变量
    unsigned int nBargainingValue;      // 交易的数值

    // 道具类 使用这3个变量
    unsigned char uchBargainingIndex;  // 交易栏索引
    unsigned char uchBagType;          // 背包类型
    unsigned char uchIndex;            // 背包索引
    __int64 n64Guid;                   // 物品guid
};

// 通知客户端交易物品的各类错误
struct MsgBargainingDataError : public MsgBargainingModule
{
    MsgBargainingDataError()
    {
        header.dwType   = MSG_BARGAININGDATAERROR;
        header.stLength = sizeof( MsgBargainingDataError );
    }

    GameObjectId ustPlayerID;     // 玩家动态ID
    unsigned char uchResult;        // 错误类型
};

// 通知对方玩家交易的数据
struct MsgShowBargainingData : public MsgBargainingModule
{
    MsgShowBargainingData()
    {
        header.dwType   = MSG_SHOWBARGAININGDATA;
        header.stLength = sizeof( MsgShowBargainingData ) - sizeof( szBargainingData );

        memset( szBargainingData, 0, sizeof( szBargainingData ) );
    }

    unsigned char uchBargainintType;    // 交易类型 ...BargainingMoney...
    unsigned int nBargainingValue;      // 交易的数值( 金钱, 金锭使用这个数据 )
    unsigned char uchBargainingIndex;   // 交易栏索引
    char szBargainingData[ BargainingDefine::DataLength ];  // 交易的数据

    void AddBargainingData( void* pData, int nSize )
    {
        if ( pData == NULL || nSize > sizeof( szBargainingData ) )
        { return; }

        memcpy_s( szBargainingData, sizeof( szBargainingData ), pData, nSize );
        header.stLength += nSize;
    }
};

// 请求锁定
struct MsgBargainingLockReq : public MsgBargainingModule
{
    MsgBargainingLockReq()
    {
        header.dwType   = MSG_BARGAININGLOCKREQ;
        header.stLength = sizeof( MsgBargainingLockReq );
    }
};

// 请求交易确定
struct MsgBargainingFixReq : public MsgBargainingModule
{
    MsgBargainingFixReq()
    {
        header.dwType   = MSG_BARGAININGFIXREQ;
        header.stLength = sizeof( MsgBargainingFixReq );
    }
};

// 请求结束交易
struct MsgBargainingCancelReq : public MsgBargainingModule
{
    MsgBargainingCancelReq()
    {
        header.dwType   = MSG_BARGAININGCANCELREQ;
        header.stLength = sizeof( MsgBargainingCancelReq );
    }
};


// 请求移除交易物品, ( 在锁定, 确定状态下, 不能移除, 客户端不能发消息 )
struct MsgRemoveBargainingDataReq : public MsgBargainingModule
{
    MsgRemoveBargainingDataReq()
    {
        header.dwType   = MSG_REMOVEBARGAININGDATAREQ;
        header.stLength = sizeof( MsgRemoveBargainingDataReq );
    }

    unsigned char uchBargainingIndex;
};

// 回应移除交易物品, 客户端删除该位置的物品
struct MsgRemoveBargainingDataAck : public MsgBargainingModule
{
    MsgRemoveBargainingDataAck()
    {
        header.dwType   = MSG_REMOVEBARGAININGDATAACK;
        header.stLength = sizeof( MsgRemoveBargainingDataAck );
    }

    GameObjectId ustPlayerID;
    unsigned char uchBargainingIndex;
};

#pragma pack( pop )

#endif