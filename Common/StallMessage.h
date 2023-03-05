#ifndef __STALLMESSAGE_H__
#define __STALLMESSAGE_H__

/************************************************************************
            摆摊消息定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "StallDefine.h"
#include "MessageRangeDefine.h"

#pragma pack( push, 1 )

enum StallMessageDefine
{
    MSG_ADDSELLDATAREQ = GAMEWORD_STALLMSG_BEGIN,
    MSG_ADDSELLDATAACK,
    MSG_ADDBUYDATAREQ,
    MSG_ADDBUYDATAACK,
    MSG_UPDATESTALLDATA,
    MSG_MOVESELLDATAREQ,
    MSG_REMOVESELLDATAREQ,
    MSG_STARTSTALLREQ,
    MSG_STARTSTALLACK,
    MSG_TELLSTARTSTALL,
    MSG_CLOSESTALLREQ,
    MSG_TELLCLOSESTALL,
    MSG_OPENSTALLREQ,
    MSG_SHOWSTALLDATA,
    MSG_BUYSTALLREQ,
    MSG_SELLSTALLREQ,
    MSG_BUYORSELLSTALLACK,
    MSG_TELLBUYORSELLSTALLDATA,
    MSG_TELLSTALLDATACOUNT,
    MSG_CHANGESTALLTITLEREQ,
    MSG_TELLSTALLTITLETOVIEW,
    MSG_CHANGESTALLPRICEREQ,
    MSG_TELLSTALLPRICE,
    MSG_TELLTOTALSTALLDATA,
	MSG_STALLQUERY,
	MSG_ACKSTALLQUERY,
};

struct MsgStallModule : public Msg
{
    MsgStallModule()
    {
        SetModuleType( EMessageModule_Stall );
    }
};

// 添加一个出售的物品
struct MsgAddSellDataReq : public MsgStallModule
{
    MsgAddSellDataReq()
    {
        header.dwType   = MSG_ADDSELLDATAREQ;
        header.stLength = sizeof( MsgAddSellDataReq );

        nGameMoneyPrice = 0;
        nRMBMoneyPrice = 0;
    }

    unsigned char uchBagType;       // 物品背包
    unsigned char uchBagIndex;      // 背包索引
    __int64 n64Guid;                // guid
    unsigned int nGameMoneyPrice;   // 游戏币单价
    unsigned int nRMBMoneyPrice;    // 金锭单价
    unsigned char uchCount;         // 数量

    unsigned char uchStallIndex;    // 移动到摊位的位置( 必须是空位置 )
};

// 添加一个收购的物品
struct MsgAddSellDataAck : public MsgStallModule
{
    MsgAddSellDataAck()
    {
        header.dwType   = MSG_ADDSELLDATAACK;
        header.stLength = sizeof( MsgAddSellDataAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_ErrorStallIndex,    // 错误的摊位索引
        ECD_ErrorBagType,       // 错误的背包类型
        ECD_ErrorItem,          // 错误的道具
        ECD_ErrorCount,         // 错误的数量
        ECD_BoundItem,          // 过期, 绑定, 锁定的物品不能摆摊出售
        ECD_AlreadyHaveData,    // 摊位此位置有道具出售, 不能添加
        ECD_AlreadySellItem,    // 该道具已经在摊位中了
    };

    unsigned char uchResult;
};

// 添加一个收购的物品
struct MsgAddBuyDataReq : public MsgStallModule
{
    MsgAddBuyDataReq()
    {
        header.dwType   = MSG_ADDBUYDATAREQ;
        header.stLength = sizeof( MsgAddBuyDataReq );

        nGameMoneyPrice = 0;
        nRMBMoneyPrice = 0;
    }

    unsigned char uchBagType;       // 物品背包
    unsigned short ustItemID;       // 收购的物品ID
    unsigned int nGameMoneyPrice;   // 游戏币单价
    unsigned int nRMBMoneyPrice;    // 金锭单价
    unsigned char uchCount;         // 数量
    unsigned char uchStallIndex;    // 移动到摊位的位置( 必须是空位置 )
};

// 回馈添加收购物品的错误信息
struct MsgAddBuyDataAck : public MsgStallModule
{
    MsgAddBuyDataAck()
    {
        header.dwType   = MSG_ADDBUYDATAACK;
        header.stLength = sizeof( MsgAddBuyDataAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_ErrorStallIndex,    // 错误的摊位索引
        ECD_ErrorBagType,       // 错误的背包类型
        ECD_ErrorItem,          // 错误的道具ID
        ECD_AlreadyHaveData,    // 摊位此位置有道具出售, 不能添加
    };

    unsigned char uchResult;
};


// 更新摊位的信息到客户端 ( 添加摊位物品, 移除摊位物品, 都会使用这个消息 )
struct MsgUpdateStallData : public MsgStallModule
{
    MsgUpdateStallData()
    {
        header.dwType   = MSG_UPDATESTALLDATA;
        header.stLength = sizeof( MsgUpdateStallData );
    }

    unsigned char uchIndex;           // 摊位的索引
    StallData xData;                
};

// 移动摊位上的物品
struct MsgMoveStallDataReq : public MsgStallModule
{
    MsgMoveStallDataReq()
    {
        header.dwType   = MSG_MOVESELLDATAREQ;
        header.stLength = sizeof( MsgMoveStallDataReq );
    }

    unsigned char uchSrcIndex;      // 源
    unsigned char uchDestIndex;     // 目标
};

// 移除摊位上的物品
struct MsgRemoveStallDataReq : public MsgStallModule
{
    MsgRemoveStallDataReq()
    {
        header.dwType   = MSG_REMOVESELLDATAREQ;
        header.stLength = sizeof( MsgRemoveStallDataReq );
    }

    unsigned char uchIndex;      
};

//开始摆摊请求
struct MsgStartStallReq : public MsgStallModule
{
    MsgStartStallReq()
    {
        header.dwType   = MSG_STARTSTALLREQ;
        header.stLength = sizeof( MsgStartStallReq );
    }

    enum EConstDefine
    {
        TypeOpenWindow = 1,     // 打开摆摊界面
        TypeStartStall,         // 请求开始摆摊
		TypeStartOfflineStall,  // 请求开始离线摆摊
    };

    unsigned char uchOpenType;  // 上面定义
    char szTitle[ StallDefine::MaxStallTitle ];     // 摊位标题    
};

// 回馈摆摊请求
struct MsgStartStallAck : public MsgStallModule
{
    MsgStartStallAck()
    {
        header.dwType   = MSG_STARTSTALLACK;
        header.stLength = sizeof( MsgStartStallAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_PKModeCritical,         // 狂暴模式不能摆摊
        ECD_ChangeMosterBuffer,     // 拥有变身状态不能摆摊
        ECD_InProtectLockTime,      // 财产保护时间内不能摆摊
        ECD_IsBargainingNow,        // 正在交易不能摆摊
        ECD_LessPrivateShopLevel,   // 小于摆摊等级
        ECD_SelfMaxMoneyLimit,      // 携带金钱上限限制
        ECD_EmptyStall,             // 不能开启一个空摊位
        ECD_OnRide,                 // 骑马状态下不能摆摊
        ECD_ErrorStallTitle,        // 错误的商店标题
        ECD_InFighting,             // 战斗状态不能摆摊
        ECD_NotEnoughMoneyBuy,      // 没有足够的金钱收购摊位上的物品
        ECD_NotEnoughEmptyBagCount, // 没有足够的包裹空间收购所有的物品
		ECD_NotInStallZone,         // 没有处于可摆摊区域
		ECD_LackOfStallFee,			// 缺少摆摊需要的金钱或道具
		ECD_StallDistance,		    // 摆摊距离限制
        ECD_Death,                  // 死亡不能摆摊
    };

    unsigned char uchResult;
};

// 通知附近玩家, 某人摆摊了
struct MsgTellStartStall : public MsgStallModule
{
    MsgTellStartStall()
    {
        header.dwType   = MSG_TELLSTARTSTALL;
        header.stLength = sizeof( MsgTellStartStall );
    }

    GameObjectId  nPlayerID;								// 摆摊玩家ID
    unsigned	  int nModelID;                             // 模型ID
    char		  szTitle[ StallDefine::MaxStallTitle ];    // 摊位标题    
	bool		  blIsOffline;								// 是否离线摆摊
};

// 请求关闭摊位
struct MsgCloseStallReq : public MsgStallModule
{
    MsgCloseStallReq()
    {
        header.dwType   = MSG_CLOSESTALLREQ;
        header.stLength = sizeof( MsgCloseStallReq );
    }
};

// 通知附近玩家关闭摊位
struct MsgTellCloseStall : public MsgStallModule
{
    MsgTellCloseStall()
    {
        header.dwType   = MSG_TELLCLOSESTALL;
        header.stLength = sizeof( MsgTellCloseStall );
    }

    GameObjectId nPlayerID;    // 摆摊玩家动态ID
};

// 请求打开一个摊位
struct MsgOpenStallReq : public MsgStallModule
{
    MsgOpenStallReq()
    {
        header.dwType   = MSG_OPENSTALLREQ;
        header.stLength = sizeof( MsgOpenStallReq );
    }
    
    GameObjectId nPlayerID;   // 摆摊玩家动态ID
};

// 发送摊位数据到客户端
struct MsgShowStallData : public MsgStallModule
{
    MsgShowStallData()
    {
        header.dwType   = MSG_SHOWSTALLDATA;
        header.stLength = sizeof( MsgShowStallData ) - sizeof( xSellData );

        uchBuyDataCount  = 0;
        uchSellDataCount = 0;
		IsOffLineStall = false;
    }

	bool	IsOffLineStall; //是否离线摆摊
    unsigned char uchBuyDataCount;
    BuyDataToClient xBuyData[ StallDefine::MaxBuyCount ]; 

    unsigned char uchSellDataCount;
    SellDataToClient xSellData[ StallDefine::MaxSellCount ]; 

    void AddBuyData( BuyDataToClient& xData )
    {
        if ( uchBuyDataCount >= StallDefine::MaxBuyCount )
        { return; }

        xBuyData[ uchBuyDataCount ] = xData;
        ++uchBuyDataCount;
    }

    void AddSellData( SellDataToClient& xData )
    {
        if ( uchSellDataCount >= StallDefine::MaxSellCount )
        { return; }

        xSellData[ uchSellDataCount ] = xData;
        ++uchSellDataCount;

        header.stLength += sizeof( SellDataToClient );
    }
};

// 客户端请求购买一个物品
struct MsgBuyStallReq : public MsgStallModule
{
    MsgBuyStallReq()
    {
        header.dwType   = MSG_BUYSTALLREQ;
        header.stLength = sizeof( MsgBuyStallReq );
    }

    GameObjectId  nPlayerID;       // 摊主的ID
    unsigned char uchIndex;        // 摊位的索引
    unsigned int nGameMoneyPrice;  // 游戏币单价( 打开摊位时发送给客户端的 )
    unsigned int nRMBMoneyPrice;   // 金锭单价( 打开摊位时发送给客户端的 )
    unsigned char uchCount;        // 购买的数量
    __int64 n64Guid;               // 摊位物品的guid, 发送回来做校验用
};

// 客户端请求出售一个物品到摊位
struct MsgSellStallReq : public MsgStallModule
{
    MsgSellStallReq()
    {
        header.dwType   = MSG_SELLSTALLREQ;
        header.stLength = sizeof( MsgSellStallReq );
    }

    GameObjectId  nPlayerID;        // 摊主的ID
    unsigned char uchStallIndex;    // 摊位的索引
    unsigned int nGameMoneyPrice;   // 游戏币单价( 打开摊位时发送给客户端的 )
    unsigned int nRMBMoneyPrice;    // 金锭单价( 打开摊位时发送给客户端的 )
    unsigned char uchBagType;       // 背包类型
    unsigned char uchBagIndex;      // 背包物品的索引
    unsigned char uchCount;         // 出售的数量
    __int64 n64Guid;                // 背包中出售物品的guid
};

// 回馈购买或者出售的错误
struct MsgBuyOrSellStallAck : public MsgStallModule
{
    MsgBuyOrSellStallAck()
    {
        header.dwType   = MSG_BUYORSELLSTALLACK;
        header.stLength = sizeof( MsgBuyOrSellStallAck );
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 成功
        ECD_PlayerOutLine,      // 摊主已经不在线了
        ECD_StallNotStart,      // 已经不在摆摊了
        ECD_StallDataError,     // 摊位数据不正确, 请刷新摊位
        ECD_StallItemError,     // 此物品过期,或者已经被锁定, 不能购买
        ECD_NotEnoughMoney,     // 没有足够的游戏币
        ECD_NotEnoughRMB,       // 没有足够的金锭
        ECD_StallPriceError,    // 摊位价钱已经不对了
        ECD_ItemPackFull,       // 包裹买了, 不能购买
        ECD_MountPackFull,      // 坐骑背包满了, 不能购买
        ECD_PetPackFull,        // 宠物背包满了, 不能购买
        ECD_StallCountError,    // 摊位数量不正确
        ECD_StallerNotMoney,    // 摊主没有足够的游戏币金钱收购了
        ECD_StallerNotRMB,      // 摊主没有足够的金锭收购了
        ECD_SellErrorItem,      // 出售给摊位的物品数据不正确
        ECD_StallerPackFull,    // 摊主包裹满了
        ECD_SellItemBound,      // 过期 or 绑定 or 锁定的物品不能出售
        ECD_SellMountActive,    // 出战的马不能出售
        ECD_StallerMountFull,   // 摊主坐骑数量满了, 不能收购
        ECD_SellPetActive,      // 出战的马不能出售
        ECD_StallerPetFull,     // 摊主坐骑数量满了, 不能收购
        ECD_SystemBusy,         // 服务器忙, 请稍后.( 主要是因为防止双方都在等待数据库入库时, 造成刷东西的bug )
    };

    unsigned char uchResult;
};

// 通知摊主 玩家 购买 或者 出售给自己东西
struct MsgTellBuyOrSellStallData : public MsgStallModule
{
    MsgTellBuyOrSellStallData()
    {
        header.dwType   = MSG_TELLBUYORSELLSTALLDATA;
        header.stLength = sizeof( MsgTellBuyOrSellStallData );

        memset( szPlayer, 0, sizeof( szPlayer ) );
        memset( szItemName, 0, sizeof( szItemName ) );
    }

    char szPlayer[ StallDefine::MaxNameLength ];    // 玩家的名字
    unsigned char uchStallType;                     // 出售 or 购买
    char szItemName[StallDefine::MaxNameLength ];   // 物品名字
    unsigned char uchCount;                         // 数量
    unsigned int nGameMoney;                        // 此次交易获得 or 失去多少钱
    unsigned int nRmbMoney;                         // 此次交易获得 or 失去多少金锭
};

// 通知打开摆摊界面买卖操作的玩家, 当前某个位置的数量 0 = 就是没有了
struct MsgTellStallDataCount : public MsgStallModule
{
    MsgTellStallDataCount()
    {
        header.dwType   = MSG_TELLSTALLDATACOUNT;
        header.stLength = sizeof( MsgTellStallDataCount );
    }

    unsigned char uchIndex;
    unsigned char uchCount;
};

// 客户端请求改变摊位标题
struct MsgChangeStallTitleReq : public MsgStallModule
{
    MsgChangeStallTitleReq()
    {
        header.dwType   = MSG_CHANGESTALLTITLEREQ;
        header.stLength = sizeof( MsgChangeStallTitleReq );
    }
    
    char szTitle[ StallDefine::MaxStallTitle ]; // 摊位标题
};

// 通知周围玩家某玩家的摊位标题改变了
struct MsgTellStallTitleToView : public MsgStallModule
{
    MsgTellStallTitleToView()
    {
        header.dwType   = MSG_TELLSTALLTITLETOVIEW;
        header.stLength = sizeof( MsgTellStallTitleToView );
    }

    GameObjectId ustPlayerID;     // 玩家的动态id
    char szTitle[ StallDefine::MaxStallTitle ]; // 摊位标题
};

// 修改摊位的价钱 ( 不能在摆摊进行中修改 )
struct MsgChangeStallPriceReq : public MsgStallModule
{
    MsgChangeStallPriceReq()
    {
        header.dwType   = MSG_CHANGESTALLPRICEREQ;
        header.stLength = sizeof( MsgChangeStallPriceReq );

        nGameMoneyPrice = 0;
        nRMBMoneyPrice = 0;
    }

    unsigned char uchStallIndex;    // 摊位的位置( 可以是出售 和 收购 , 但必须有物品 )
    unsigned int nGameMoneyPrice;   // 游戏币单价
    unsigned int nRMBMoneyPrice;    // 金锭单价
};

// 通知摊位上某个物品价钱
struct MsgTellStallPrice : public MsgStallModule
{
    MsgTellStallPrice()
    {
        header.dwType   = MSG_TELLSTALLPRICE;
        header.stLength = sizeof( MsgTellStallPrice );

        nGameMoneyPrice = 0;
        nRMBMoneyPrice = 0;
    }

    unsigned char uchStallIndex;    // 摊位的位置
    unsigned int nGameMoneyPrice;   // 游戏币单价
    unsigned int nRMBMoneyPrice;    // 金锭单价
};

// 通知摊主, 自己摊位上的所有信息
struct MsgTellTotalStallData : public MsgStallModule
{
    MsgTellTotalStallData()
    {
        header.dwType   = MSG_TELLTOTALSTALLDATA;
        header.stLength = sizeof( MsgTellTotalStallData ) - sizeof( xStallData );

        uchCount = 0;
        memset( szStallTitle, 0, sizeof( szStallTitle ) );
    }

    struct StallDataToClient
    {
        unsigned char uchStallIndex;    // 摊位索引
        StallData xData;
    };

    char szStallTitle[ StallDefine::MaxStallTitle ];    // 摊位标题
    unsigned char uchCount; // 摊位物品个数
    StallDataToClient xStallData[ StallDefine::MaxStallCount ]; // 摊位物品数据

    void AddData( unsigned char uchIndex, StallData& xData )
    {
        if ( uchCount >= StallDefine::MaxStallCount )
        { return; }

        xStallData[ uchCount ].uchStallIndex = uchIndex;
        xStallData[ uchCount ].xData = xData;
        ++uchCount;

        header.stLength += sizeof( StallDataToClient );
    }

};


//摆摊查询当前地图上经过关键字筛选的摊位信息
struct MsgStallQuery : public MsgStallModule
{
	//关键字搜索字段
	enum ESearchField
	{
		ESF_NONE,			//不做搜索
		ESF_StallName,		//在摊位名中搜索
		ESF_ChaName,		//在角色名中搜索
//		ESF_StallOrChaName,	//在摊位名和角色名中搜索
	};

	MsgStallQuery()
	{
		header.dwType = MSG_STALLQUERY;
		header.stLength = sizeof( MsgStallQuery );

		nSearchField = ESF_NONE;
		memset( szKeyWord, 0, sizeof(szKeyWord) );
	}

	uint8	nSearchField;	//搜索字段类型
	char	szKeyWord[ StallDefine::MaxStallTitle ];	//搜索关键字
};

//摆摊查询的结果
struct MsgAckStallQuery : public MsgStallModule
{
	enum EConstDefine
	{
		ECD_PageSize = 10,	//摆摊查询结果一页的大小
	};

	MsgAckStallQuery()
	{
		Clear();
	}

	bool AddData( StallDefine::SStallInfo& data )
	{
		if ( nStallCount >= ECD_PageSize )
		{ return false; }

		xData[ nStallCount ] = data;
		++nStallCount;

		header.stLength += sizeof( StallDefine::SStallInfo );
		return true;
	}

	void Clear()
	{
		header.dwType   = MSG_ACKSTALLQUERY;
		header.stLength = sizeof( MsgAckStallQuery ) - sizeof( xData );

		blTheLast = false;
		nStallCount = 0;
	}

	bool IsTheLast() { return blTheLast; }
	void SetTheLast() { blTheLast = true; }

	bool blTheLast;		//是否列表结束
	int nStallCount;	//摊位数
	StallDefine::SStallInfo xData[ ECD_PageSize ];	//摊位信息列表
};

#pragma pack( pop )

#endif