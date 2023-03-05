#ifndef __CONSIGNMENTMESSAGE_H__
#define __CONSIGNMENTMESSAGE_H__
/************************************************************************
            FileName : ConsignmentMessage.h

            寄售系统消息定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "ConsignmentDefine.h"
#include "MessageRangeDefine.h"

#pragma pack( push, 1 )

enum ConsignmentMessageDefine
{
    MSG_SHOWCONSIGNMENTMONEYLIST = GAMEWORD_CONSIGNMENTMSG_BEGIN,       // 显示金钱寄售列表
    MSG_SHOWCONSIGNMENTITEMLIST,                                        // 显示物品寄售列表( 包括物品, 坐骑, 宠物等 )
    MSG_SHOWCONSIGNMENTACCOUNT,                                         // 当前帐号资金
    MSG_SHOWCONSIGNMENTHISTROY,                                         // 显示历史记录
    MSG_OPERATEACCOUNTREQ,                                              // 存取钱请求
    MSG_OPERATEACCOUNTACK,                                              // 存取钱回馈
    MSG_CONSIGNMENTMONEYREQ,                                            // 请求寄售金钱
    MSG_CONSIGNMENTMONEYACK,                                            // 回馈寄售金钱
    MSG_CONSIGNMENTITEMREQ,                                             // 请求寄售物品
    MSG_CONSIGNMENTITEMACK,                                             // 回馈寄售物品
    MSG_CONSIGNMENTOPERATEREQ,                                          // 请求操作寄售单
    MSG_CONSIGNMENTOPERATEACK,                                          // 回馈操作寄售单
    MSG_QUERYCONSIGNMENTLIST,                                           // 请求查看寄售单
    MSG_QUERYCONSIGNMENTACK,                                            // 回馈
    MSG_CONSIGNMENTMONEYHISTROYREQ,                                     // 请求查看历史记录
    MSG_CONSIGNMENTMONEYHISTROYACK,
    MSG_TELLCONSIGNMENTMONEY,                                           // 全服广播, 默认挂单了

    CS2DB_LOADCONSIGNMENTDATAREQ = CENTERGAME_CONSIGNMENT_BEGIN,        // 请求加载数据
    DB2CS_CONSIGNMENTACCOUNTLIST,                                       // 帐号列表
    DB2CS_CONSIGNMENTMONEYLIST,                                         // 金钱寄售列表
    DB2CS_CONSIGNMENTITELISTM,                                          // 物品寄售列表
    DB2CS_CONSIGNMENTHISTROYLIST,                                       // 历史交易记录
    GS2CS_OPERNCONSIGNMENTMONEYWINDOW,                                  // 请求打开金锭寄售界面
    CS2GS_CONSIGNMENTCOUNT,                                             // 帐号信息
    CS2GS_CONSIGNMENTOPERATEEND,                                        // 超过结束
    GS2CS_QUERYCONSIGNMENTLIST,                                         // 请求查看寄售列表
    GS2CS_OPERATEMONEYREQ,                                              // 请求金钱帐号操作
    CS2GS_OPERATEMONEYACK,                                              // 回馈金钱操作
    CS2DB_OPERATEMONEYREQ,                                              // 请求数据库帐号操作
    DB2CS_OPERATEMONEYACK,                                              // 数据库回馈
    GS2CS_CONSIGNMENTMONEYREQ,
    CS2DB_CONSIGNMENTMONEYREQ,
    GS2CS_CONSIGNMENTMONEYHISTROYREQ,
    GS2CS_CONSIGNMENTOPERATEREQ,
    CS2DB_CONSIGNMENTMONEYOPERATEREQ,
    DB2CS_CONSIGNMENTMONEYOPERATEACK,

	GS2CS_CONSIGNMENTITEMREQ,
};

struct MsgConsignmentModule : public Msg
{
    MsgConsignmentModule()
    {
        SetModuleType( EMessageModule_Consignment );
    }
};

// 金锭寄售列表
struct MsgShowConsignmentMoneyList : public MsgConsignmentModule
{
    MsgShowConsignmentMoneyList()
    {
        header.dwType = MSG_SHOWCONSIGNMENTMONEYLIST;
        header.stLength = sizeof( MsgShowConsignmentMoneyList ) - sizeof( xList );
        nCount = 0;
        uchShowType = Show_All;
    }

    enum EConstDefine
    {
        Show_SellRMB = 0,       // 出售列表刷新
        Show_BuyRMB,            // 收购列表刷新
        Show_All,               // 全部刷新
    };

    unsigned char uchShowType;          // 显示刷新的列表

    int nCount;
    ConsignmentBase xList[ ConsignmentDefine::MaxConsignmentCount * 2 ];    // 寄售列表

    void AddConsignmentMoney( const ConsignmentBase* pConsignment )
    {
        if ( nCount >= ConsignmentDefine::MaxConsignmentCount * 2 )
        { return; }

        xList[ nCount ].Initialize( pConsignment );

        ++nCount;
        header.stLength += sizeof( ConsignmentBase );
    }
};

// 帐号信息
struct MsgShowConsignmentAccount : public MsgConsignmentModule
{
    MsgShowConsignmentAccount()
    {
        header.dwType = MSG_SHOWCONSIGNMENTACCOUNT;
        header.stLength = sizeof( MsgShowConsignmentAccount );
    }
    
    uint32 nRMBMoney;       // 金锭
    uint32 nGameMoney;      // 游戏币
};

// 显示历史记录
struct MsgShowConsignmentHistroy : public MsgConsignmentModule
{
    MsgShowConsignmentHistroy()
    {
        header.dwType = MSG_SHOWCONSIGNMENTHISTROY;
        header.stLength = sizeof( MsgShowConsignmentHistroy ) - sizeof( xList );
        nCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 100,
    };

    int nCount;
    ConsignmentHistroy xList[ MaxCount ];    // 寄售列表

    void AddConsignmentHistroy( const ConsignmentHistroy* pHistroy )
    {
        if ( nCount >= MaxCount )
        { return; }

        xList[ nCount ].Initialize( pHistroy );

        ++nCount;
        header.stLength += sizeof( ConsignmentHistroy );
    }
};

// 存取钱请求
struct MsgOperateMoneyReq : public MsgConsignmentModule
{
    MsgOperateMoneyReq()
    {
        header.dwType = MSG_OPERATEACCOUNTREQ;
        header.stLength = sizeof( MsgOperateMoneyReq );

        nRMBMoney = 0;
        nGameMoney = 0;
    }
    
    uint8 uchOperate;        // 类型( 在ConsignmentDefine中定义 )
    uint32 nRMBMoney;        // 金锭
    uint32 nGameMoney;       // 游戏币
};

// 存取钱回馈
struct MsgOperateMoneyAck : public MsgConsignmentModule
{
    MsgOperateMoneyAck()
    {
        header.dwType = MSG_OPERATEACCOUNTACK;
        header.stLength = sizeof( MsgOperateMoneyAck );
    }

    enum EConstDefine
    {
        ECD_NotEnoughMoney = 1, // 没有足够的钱
        ECD_NotEnoughJinDing,   // 没有足够的金锭
        ECD_TooMuchMoney,       // 金钱数量达到上限
        ECD_TooMuchJinDing,     // 账户金锭数量达到上限
        ECD_WaitProcess,        // 上一个操作正在处理中, 请稍后再试
        ECD_SystemBusy,         // 不要频繁操作
		ECD_InProtectLockTime,  // 在财产保护时间内
    };

    uint8 uchOperate;           // 类型
    uint8 uchResult;
};

// 请求寄售金锭
struct MsgConsignmentMoneyReq : public MsgConsignmentModule
{
    MsgConsignmentMoneyReq()
    {
        header.dwType = MSG_CONSIGNMENTMONEYREQ;
        header.stLength = sizeof( MsgConsignmentMoneyReq );
    }

    ConsignmentBase xConsignment;       // 寄售的内容
};

//liaojie
//请求寄售物品
//struct MsgConsignmentItemReq : public MsgConsignmentModule
//{
//	MsgConsignmentItemReq()
//	{
//		header.dwType = MSG_CONSIGNMENTITEMREQ;
//		header.stLength = sizeof(MsgConsignmentItemReq);
//	}
//	ConsignmentData xConsignment;		//寄售单内容
//};

//  回馈寄售挂单操作
struct MsgConsignmentMoneyAck : public MsgConsignmentModule
{
    MsgConsignmentMoneyAck()
    {
        header.dwType = MSG_CONSIGNMENTMONEYACK;
        header.stLength = sizeof( MsgConsignmentMoneyAck );
    }

    enum EConstDefine
    {
        ECD_NotEnoughMoney = 1,     // 账户上没有足够的游戏比
        ECD_NotEnoughjinDing,       // 没有足够的金锭 
        ECD_ConsignmentCountLimit,  // 最少交易25个金锭
        ECD_WaitProcess,            // 上一个操作正在处理中, 请稍后再试
        ECD_SystemBusy,             // 不要频繁操作
        ECD_MustFriend,             // 指定的玩家必须是你的好友
    };

    uint8 uchResult;
};

//  回馈寄售物品操作
struct MsgConsignmentItemAck : public MsgConsignmentModule
{
	MsgConsignmentItemAck()
	{
		header.dwType = MSG_CONSIGNMENTITEMACK;
		header.stLength = sizeof( MsgConsignmentItemAck );
	}

	enum EConstDefine
	{
		ECD_NotEnoughMoney = 1,     // 账户上没有足够的游戏比
		//ECD_NotEnoughjinDing,       // 没有足够的金锭 
		//ECD_ConsignmentCountLimit,  // 最少交易25个金锭
		ECD_NoEnoughItem,			// 没有足够的物品
		ECD_WaitProcess,            // 上一个操作正在处理中, 请稍后再试
		ECD_SystemBusy,             // 不要频繁操作
		ECD_MustFriend,             // 指定的玩家必须是你的好友
	};

	uint8 uchResult;
};

// 请求一个操作
struct MsgConsignmentOperateReq : public MsgConsignmentModule
{
    MsgConsignmentOperateReq()
    {
        header.dwType = MSG_CONSIGNMENTOPERATEREQ;
        header.stLength = sizeof( MsgConsignmentOperateReq );
    }

    uint8 uchOperate;           // 类型 ( 在ConsignmentDefine中定义 )
    __int64 n64ConsignmentID;   // 寄售单ID
    uint8 uchConsignmentType;   // 寄售单类型
};

// 回馈操作
struct MsgConsignmentOperateAck : public MsgConsignmentModule
{
    MsgConsignmentOperateAck()
    {
        header.dwType = MSG_CONSIGNMENTOPERATEACK;
        header.stLength = sizeof( MsgConsignmentOperateAck );
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 操作成功, ( 列表中删除此订单 )
        ECD_NotEnoughMoney,     // 账户上没有足够的钱
        ECD_NotEnoughJinDing,   // 账户上没有足够的金锭
        ECD_WaitProcess,        // 上一个操作正在处理中, 请稍后再试
        ECD_SystemBusy,         // 系统繁忙, 请稍后再试
        ECD_ConsignmentSelled,  // 已经出售完了
        ECD_ConsignmentProcess, // 单子正在处理中, 请稍后
        ECD_ErrorOperate,       // 错误的操作,( 别人出售, 你要买, 别人收购, 你要卖 )
        ECD_CanNotOperateSelf,  // 不能买卖自己的单子
        ECD_CanNotCancelOther,  // 不能撤销其他玩家的单子
        ECD_NotAppointPlayer,   // 不是指定玩家, 不能购买或者出售
    };

    uint8 uchResult;

    __int64 n64ConsignmentID;   // 寄售单ID
    uint8 uchConsignmentType;   // 寄售单类型
    __int64 n64EndTime;         // 结束时间
    uint8 uchEndStatus;         // 结束时的状态
};

// 查询寄售单
struct MsgQueryConsignmentList : public MsgConsignmentModule
{
    MsgQueryConsignmentList()
    {
        header.dwType = MSG_QUERYCONSIGNMENTLIST;
        header.stLength = sizeof( MsgQueryConsignmentList );
    }

    uint8 uchConsignmentType;   // 寄售单类型
    uint8 uchQueryType;         // 查询类型
    int nCount;                 // 如果有数量, 传入数量
};

struct MsgQueryConsignmentListAck : public MsgConsignmentModule
{
    MsgQueryConsignmentListAck()
    {
        header.dwType = MSG_QUERYCONSIGNMENTACK;
        header.stLength = sizeof( MsgQueryConsignmentListAck );
    }

    enum EConstDefine
    {
        ECD_SystemBusy = 1, // 请不要频繁操作
        ECD_WaitProcess,    // 等待处理中
    };

    uint8 uchResult;
};

// 查询历史记录
struct MsgConsignmentMoneyHistroyReq : public MsgConsignmentModule
{
    MsgConsignmentMoneyHistroyReq()
    {
        header.dwType = MSG_CONSIGNMENTMONEYHISTROYREQ;
        header.stLength = sizeof( MsgConsignmentMoneyHistroyReq );
    }
};

struct MsgConsignmentMoneyHistroyAck : public MsgConsignmentModule
{
    MsgConsignmentMoneyHistroyAck()
    {
        header.dwType = MSG_CONSIGNMENTMONEYHISTROYACK;
        header.stLength = sizeof( MsgConsignmentMoneyHistroyAck );
    }

    enum EConstDefine
    {
        ECD_SystemBusy = 1, // 请不要频繁操作
        ECD_WaitProcess,    // 等待处理中
    };

    uint8 uchResult;
};

// 通知客户端某人挂单了
struct MsgTellConsignmentMoney : public MsgConsignmentModule
{
    MsgTellConsignmentMoney()
    {
        header.dwType = MSG_TELLCONSIGNMENTMONEY;
        header.stLength = sizeof( MsgTellConsignmentMoney );
    }
    
    uint8 uchConsignmentType;  // 挂单类型
    uint32 nPrice;             // 价钱
    uint32 nCount;             // 数量
};

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
struct CS2DBLoadConsignmentDataReq : public MsgConsignmentModule
{
    CS2DBLoadConsignmentDataReq()
    {
        header.dwType = CS2DB_LOADCONSIGNMENTDATAREQ;
        header.stLength = sizeof( CS2DBLoadConsignmentDataReq );
    }
};

struct DB2CSLoadConsignmentAccount : public MsgConsignmentModule
{
    DB2CSLoadConsignmentAccount()
    {
        header.dwType = DB2CS_CONSIGNMENTACCOUNTLIST;
        Reset();
    }

    enum EConstDefine
    {
        MaxCount = 1000,
    };

    int nCount;
    ConsignmentAccount xAccount[ MaxCount ];

    void AddConsignmentAccount( unsigned long nPlayerID, unsigned long nRMBMoney, unsigned long nGameMoney )
    {
        if ( nCount >= MaxCount )
        { return; }

        xAccount[ nCount ].SetPlayerID( nPlayerID );
        xAccount[ nCount ].SetRMBMoney( nRMBMoney );
        xAccount[ nCount ].SetGameMoney( nGameMoney );

        ++nCount;
        header.stLength += sizeof( ConsignmentAccount );
    }

    bool IsFull() { return nCount >= MaxCount; }
    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof( DB2CSLoadConsignmentAccount ) - sizeof( xAccount );
    }
};

struct DB2CSLoadConsignmentMoneyList : public MsgConsignmentModule
{
    DB2CSLoadConsignmentMoneyList()
    {
        header.dwType = DB2CS_CONSIGNMENTMONEYLIST;
        Reset();
    }

    enum EConstDefine
    {
        MaxCount = 500,
    };

    int nCount;
    ConsignmentBase xList[ MaxCount ];

    void AddConsignmentMoney( const ConsignmentBase* pBase )
    {
        if ( nCount >= MaxCount )
        { return; }

        xList[ nCount ].Initialize( pBase );

        ++nCount;
        header.stLength += sizeof( ConsignmentBase );
    }

    bool IsFull() { return nCount >= MaxCount; }
    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof( DB2CSLoadConsignmentAccount ) - sizeof( xList );
    }
};

struct DB2CSLoadConsignmentHistroy : public MsgConsignmentModule
{
    DB2CSLoadConsignmentHistroy()
    {
        header.dwType = DB2CS_CONSIGNMENTHISTROYLIST;
        Reset();
    }

    enum EConstDefine
    {
        MaxCount = 500,
    };

    int nCount;
    ConsignmentHistroy xList[ MaxCount ];

    void AddConsignmentHistroy( const ConsignmentHistroy* pHistroy )
    {
        if ( nCount >= MaxCount )
        { return; }

        xList[ nCount ].Initialize( pHistroy );

        ++nCount;
        header.stLength += sizeof( ConsignmentHistroy );
    }

    bool IsFull() { return nCount >= MaxCount; }
    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof( DB2CSLoadConsignmentHistroy ) - sizeof( xList );
    }
};

struct GS2CSOpenConsignmentMoneyWindow : public MsgConsignmentModule
{
    GS2CSOpenConsignmentMoneyWindow()
    {
        header.dwType = GS2CS_OPERNCONSIGNMENTMONEYWINDOW;
        header.stLength = sizeof( GS2CSOpenConsignmentMoneyWindow );
    }

	bool bGetAll;  //是否获得全部寄售信息,0:只拿帐号信息
    uint32 nPlayerID;
};

struct CS2GSConsignmentAccount : public MsgConsignmentModule
{
    CS2GSConsignmentAccount()
    {
        header.dwType = CS2GS_CONSIGNMENTCOUNT;
        header.stLength = sizeof( CS2GSConsignmentAccount );
    }

    ConsignmentAccount xAcount;
    bool bProcess;
};

struct CS2GSConsignmentOperate : public MsgConsignmentModule
{
    CS2GSConsignmentOperate()
    {
        header.dwType = CS2GS_CONSIGNMENTOPERATEEND;
        header.stLength = sizeof( CS2GSConsignmentOperate );
    }

    bool bProcess;
};


struct GS2CSQueryConsignmentList : public MsgConsignmentModule
{
    GS2CSQueryConsignmentList()
    {
        header.dwType = GS2CS_QUERYCONSIGNMENTLIST;
        header.stLength = sizeof( GS2CSQueryConsignmentList );
    }

    uint32 nPlayerID;

    uint8 uchConsignmentType;   // 寄售单类型
    uint8 uchQueryType;         // 查询类型
    int nCount;                 // 如果有数量, 传入数量
};

struct GS2CSOperateMoneyReq : public MsgConsignmentModule
{
    GS2CSOperateMoneyReq()
    {
        header.dwType = GS2CS_OPERATEMONEYREQ;
        header.stLength = sizeof( GS2CSOperateMoneyReq );
    }

    uint32 nPlayerID;

    uint8 uchOperate;        // 类型( 在ConsignmentDefine中定义 )
    uint32 nRMBMoney;        // 金锭
    uint32 nGameMoney;       // 游戏币       
};

struct CS2GSOperateMoneyAck : public MsgConsignmentModule
{
    CS2GSOperateMoneyAck()
    {
        header.dwType = CS2GS_OPERATEMONEYACK;
        header.stLength = sizeof( CS2GSOperateMoneyAck );
    }

    ConsignmentAccount xAccount;    // 帐号信息

    uint8 uchOperate;        // 类型( 在ConsignmentDefine中定义 )
    uint32 nRMBMoney;        // 金锭
    uint32 nGameMoney;       // 游戏币
};

struct CS2DBOperateMoneyReq : public MsgConsignmentModule
{
    CS2DBOperateMoneyReq()
    {
        header.dwType = CS2DB_OPERATEMONEYREQ;
        header.stLength = sizeof( CS2DBOperateMoneyReq );
    }

    ConsignmentAccount xAccount;    // 帐号信息

    bool bNeedDBAck;                // 是否需要数据库回馈

    uint8 uchOperate;        // 类型( 在ConsignmentDefine中定义 )
    uint32 nRMBMoney;        // 金锭
    uint32 nGameMoney;       // 游戏币
};

struct DB2CSOperateMoneyAck : public MsgConsignmentModule
{
    DB2CSOperateMoneyAck()
    {
        header.dwType = DB2CS_OPERATEMONEYACK;
        header.stLength = sizeof( DB2CSOperateMoneyAck );
    }

    ConsignmentAccount xAccount;    // 帐号信息

    uint8 uchOperate;        // 类型( 在ConsignmentDefine中定义 )
    uint32 nRMBMoney;        // 金锭
    uint32 nGameMoney;       // 游戏币
};

struct GS2CSConsignmentMoneyReq : public MsgConsignmentModule
{
    GS2CSConsignmentMoneyReq()
    {
        header.dwType = GS2CS_CONSIGNMENTMONEYREQ;
        header.stLength = sizeof( GS2CSConsignmentMoneyReq );
    }

    uint32 nPlayerID;
    ConsignmentBase xConsignment;       // 寄售的内容

    uint32 nCostValue;                  // 寄售的费用( 直接发给Center, 不再算 )
};

struct GS2CSConsignmentItemReq : public MsgConsignmentModule
{
	GS2CSConsignmentItemReq()
	{
		header.dwType = GS2CS_CONSIGNMENTITEMREQ;
		header.stLength = sizeof( GS2CSConsignmentItemReq );
	}

	uint32 nPlayerID;
	ConsignmentData xConsignment;       // 寄售的内容

	uint32 nCostValue;                  // 寄售的费用( 直接发给Center, 不再算 )
};

struct CS2DBConsignmentMoneyReq : public MsgConsignmentModule
{
    CS2DBConsignmentMoneyReq()
    {
        header.dwType = CS2DB_CONSIGNMENTMONEYREQ;
        header.stLength = sizeof( CS2DBConsignmentMoneyReq );
    }

    ConsignmentAccount xAccount;    // 帐号信息
    ConsignmentHistroy xConsignment;       // 寄售的内容
};

struct GS2CSConsignmentMoneyHistroyReq : public MsgConsignmentModule
{
    GS2CSConsignmentMoneyHistroyReq()
    {
        header.dwType = GS2CS_CONSIGNMENTMONEYHISTROYREQ;
        header.stLength = sizeof( GS2CSConsignmentMoneyHistroyReq );
    }

    uint32 nPlayerID;
};

struct GS2CSConsignmentOperateReq : public MsgConsignmentModule
{
    GS2CSConsignmentOperateReq()
    {
        header.dwType = GS2CS_CONSIGNMENTOPERATEREQ;
        header.stLength = sizeof( GS2CSConsignmentOperateReq );
    }

    uint32 nPlayerID;
    uint8 uchOperate;           // 操作类型 ( 在ConsignmentDefine中定义 )
    __int64 n64ConsignmentID;   // 寄售单ID
    uint8 uchConsignmentType;   // 寄售单类型
};

struct CS2DBConsignmentmoneyOperateReq : public MsgConsignmentModule
{
    CS2DBConsignmentmoneyOperateReq()
    {
        header.dwType = CS2DB_CONSIGNMENTMONEYOPERATEREQ;
        header.stLength = sizeof( CS2DBConsignmentmoneyOperateReq );
    }

    ConsignmentAccount xSellerAccount;
    ConsignmentAccount xOperaterAccount;

    __int64 nConsignmentID; // 寄售单ID
    __int64 n64EndTime;       // 结束时间
    uint8 uchEndStatus;     // 结束的状态

    ConsignmentHistroy xNewHistroy; // 新的记录
};

struct DB2CSConsignmentmoneyOperateAck : public MsgConsignmentModule
{
    DB2CSConsignmentmoneyOperateAck()
    {
        header.dwType = DB2CS_CONSIGNMENTMONEYOPERATEACK;
        header.stLength = sizeof( DB2CSConsignmentmoneyOperateAck );
    }

    ConsignmentAccount xSellerAccount;
    ConsignmentAccount xOperaterAccount;

    __int64 nConsignmentID; // 寄售单ID
    __int64 n64EndTime;       // 结束时间
    uint8 uchEndStatus;     // 结束的状态

    ConsignmentHistroy xNewHistroy; // 新的记录
};

#pragma pack( pop )

#endif