#ifndef __PLATFORMMESSAGEDEFINE_H__
#define __PLATFORMMESSAGEDEFINE_H__

#pragma once
#include "GlobalDef.h"
#include "PlatformDefine.h"
#include "DBMessageDefine.h"

enum EPlatformMessageDefineO
{
	PFMSG_BEGIN         = 1,
//	PFMSG_ITEMEXCHANGE,       // 实物兑换   

	PFMSG_SERVERSTATUS_REQ,   // 请求服务器的状态
	PFMSG_SERVERSTATUS_ACK,   // 应答服务器的状态

	PFMSG_ADDITEM_REQ,        // 送道具
	PFMSG_ADDITEM_ACK,        // 送道具回馈

	//PFMSG_GMKICKPLAYER_REQ,   // 踢角色
	//PFMSG_GMKICKPLAYER_ACK,

	PFMSG_RELOADTRADESHOP_REQ,      // 触发金锭商城重新加载
	PFMSG_SHUTDOWNSERVERS_REQ,      // 请求关服维护
	PFMSG_CHANGEMAPEXPRATE_REQ,     // 请求修改地图经验

	PFMSG_GMBROADCAST_REQ,          //ok 发公告
	PFMSG_GMOPCHATONOFF,            //ok 聊天纪录开关
	PFMSG_C2PTELLSERVERID,          //ok center server告诉platform自己的ID
	PFMSG_P2CREGERES,               //ok platform告诉center 注册结果,服务是否可以使用

	PFMSG_SENDMAIL,				//ok platform触发发送给某个角色邮件
	PFMSG_ASKFORPRESENT,           //ok 请求present
	PFMSG_ASKFORACTIVITY,		//ok 请求activity

	PFMSG_MODIFY_ERROR,        // ok 操作错误返回值,统一处理

	PFMSG_BANACCOUNT,			//锁定帐号登录
	PFMSG_BANMACADRESS,			//锁定MAC登录

	PFMSG_REQ_EPISTARPOINT,		//center server tell platform 操作 晶元点数
	PFMSG_ACK_EPISTARPOINT,		//platform tell center server 操作 晶元点数 反馈消息
	//PFMSG_GMUPDATEFILTERSTRING_REQ, // 在线更新过滤词库
	//PFMSG_GMOPENEXPMUL_REQ,         // 打开双倍经验
	//PFMSG_GMMONSTEROP_REQ,          // 杀死怪物 召唤怪物
	/*PFMSG_ADDPOINTS,
	PFMSG_ADDPOINTS_ACK,*/
	//PFMSG_INFOQUERY_REQ = 50, // 查询 各种卡 卡等级 礼包信息 请求
	//PFMSG_INFOQUERY_ACK,      // 查询 各种卡 卡等级 礼包信息 回馈
	//PFMSG_CREATECHAR_REQ,     // 创建角色
	//PFMSG_CREATECHAR_ACK,     // 创建角色回馈
	//PFMSG_GMGETPLAYERINFO_REQ,      // 查询角色信息（属性，金钱，金锭，金票，等级，装备，背包，技能，仓库，坐骑）[无论角色是否在线，如果不在线，返回数据库中的信息]
	//PFMSG_GMGETPLAYERINFO_ACK,
	//PFMSG_GMGETPLAYERMAPINFO_REQ,   // 查询角色是否在线，返回其所在地图和位置
	//PFMSG_GMGETPLAYERMAPINFO_ACK,
	//PFMSG_GMMOVEPLAYER_REQ,         // 移动角色坐标
	//PFMSG_GMMOVEPLAYER_ACK,
	//PFMSG_GMGETORGANIZEINFO_REQ,    // 查询帮会信息
	//PFMSG_GMGETORGANIZEINFO_ACK,
	//PFMSG_GMGETITEMINFO_REQ,        // 查询物品（输入物品id，返回物品属性等）
	//PFMSG_GMGETITEMINFO_ACK,
	//PFMSG_GMCHANGEPLAYERINFO_REQ,   // 改变角色属性（等级，经验，技能）
	//PFMSG_GMCHANGEPLAYERINFO_ACK,
	//PFMSG_GMBANCHAT_REQ,            // 禁言，解禁
	//PFMSG_GMBANCHAT_ACK,
	//PFMSG_GMCREATEITEMTOPLAYER_REQ, // 生成道具给某角色
	//PFMSG_GMCREATEITEMTOPLAYER_ACK,

	PFMSG_END
};

#pragma pack( push, 1 )

//struct MsgPFAddPoints : public Msg
//{ // 平台冲值
//    MsgPFAddPoints()
//    {
//        header.dwType   = PFMSG_ADDPOINTS;
//        header.stLength = sizeof(*this);
//
//        memset( &info, 0, sizeof(info));
//    }
//
//    SAddPoints info;
//};

//struct MsgPFAddPointsAck : public Msg
//{ // 平台冲值
//    MsgPFAddPointsAck()
//    {
//        header.dwType   = PFMSG_ADDPOINTS_ACK;
//        header.stLength = sizeof(*this);
//
//        result = ER_Success;
//        guid   = 0;
//        points = 0;
//        memset( &typesn, 0, sizeof(typesn));
//    }
//
//    uint32 result;     // 结果
//    uint32 guid;       // 用户id
//    uint32 points;     // 点数
//    int8   typesn[32]; // 订单号
//};

//struct MsgPFInfoQueryReq : public Msg
//{ // 向平台查询信息
//
//    MsgPFInfoQueryReq()
//    {
//        header.dwType   = PFMSG_INFOQUERY_REQ;
//        header.stLength = sizeof( MsgPFInfoQueryReq );
//    }
//    uint32 guid;      // 用户id
//    uint8  queryType;
//};

//struct MsgPFInfoQueryAck : public Msg
//{ // 向平台查询信息回馈
//    MsgPFInfoQueryAck()
//    {
//        header.dwType   = PFMSG_INFOQUERY_ACK;
//        header.stLength = sizeof( MsgPFInfoQueryAck );
//    }
//
//    uint32 result;   // 结果
//    uint32 guid;     // 用户id
//    uint8  querType; // 查询类型
//};

//struct MsgPFItemExchange : public Msg
//{ // 向平台提交实物信息
//	MsgPFItemExchange()
//	{
//		header.dwType   = PFMSG_ITEMEXCHANGE;
//		header.stLength = sizeof(*this);
//	}
//	uint32  guid;             // 帐号
//	int8    charName[33];     // 角色名
//	uint16  itemId;           // 道具id
//	int64   itemguid;         // 道具guid
//	int8    itemName[17];     // 道具名字
//	int8    linkman[17];      // 联系人
//	int8    telephone[13];    // 电话
//	int8    email[50];        // email
//	int8    identityCard[19]; // 身份证
//	int8    passport[33];     // 帐号名字
//};

//struct MsgPFCreateCharReq : public Msg
//{ // 请求创建角色
//    MsgPFCreateCharReq()
//    {
//        header.dwType   = PFMSG_CREATECHAR_REQ;
//        header.stLength = sizeof( MsgPFCreateCharReq );
//        
//        level   = 0;
//        byMonth = 0;
//        byDay   = 0;
//        bagid   = 0;
//    }
//    uint32  guid;         // 帐号
//    uint8   sex;          // 性别
//    uint8   profession;   // 角色职业
//    uint8   country;      // 国家
//    int8    charName[33]; // 角色名
//    uint16  level  ;      // 等级
//    uint8   byMonth;      // 出生月
//    uint8   byDay  ;      // 出生日
//    uint16  bagid  ;      // 礼包Id
//};
//
//struct MsgPFCreateCharAck : public Msg
//{ // 请求创建角色
//    MsgPFCreateCharAck()
//    {
//        header.dwType   = PFMSG_CREATECHAR_ACK;
//        header.stLength = sizeof( MsgPFCreateCharAck );
//    }
//    uint32  result;       // 
//    uint32  guid;         // 帐号
//    int8    charName[33]; // 角色名
//};

struct MsgPFAddItemReq : public Msg
{ // 请求添加物品
	MsgPFAddItemReq()
	{
		header.dwType   = PFMSG_ADDITEM_REQ;
		header.stLength = sizeof( MsgPFAddItemReq );
	}

	uint32            accountId; // 帐号
	SJiFengItemRecordPlatform item;      // 物品纪录
};

struct MsgPFAddItemAck : public Msg
{ // 请求添加物品
	enum EResult
	{
		ER_Success,
		ER_SnHaveExist,
	};

	MsgPFAddItemAck()
	{
		header.dwType   = PFMSG_ADDITEM_ACK;
		header.stLength = sizeof( MsgPFAddItemAck );
		result = ER_Success;
		memset( sn, 0, sizeof(sn) );
	}

	uint32 result;    // 结果
	uint32 accountId; // 帐号Id
	int8   sn[32];    // 序列号
	uint8  itemType;  // 物品类型
	uint16 itemid;    // 物品Id
	uint16 itemCount; // 物品个数
};

// GM
//struct MsgPFGmKickPlayerReq : public Msg
//{ // GM 踢人
//	MsgPFGmKickPlayerReq()
//	{
//		header.dwType   = PFMSG_GMKICKPLAYER_REQ;
//		header.stLength = sizeof( MsgPFGmKickPlayerReq );
//	}
//	uint32  accountGuid;  // 帐号
//	uint32  chardbId;     // 角色Id
//	int8    charName[33]; // 角色名
//	uint32  time;         // s 秒
//};

//struct MsgPFGmKickPlayerAck : public Msg
//{ // GM 踢人
//	MsgPFGmKickPlayerAck()
//	{
//		header.dwType   = PFMSG_GMKICKPLAYER_ACK;
//		header.stLength = sizeof( MsgPFGmKickPlayerAck );
//		result = ER_Success;
//	}
//
//	uint32 result;
//	uint32 accountGuid;  // 帐号
//	uint32 chardbId;     // 角色Id
//	int8   charName[33]; // 角色名
//	uint32 time;         // s 秒
//};

struct MsgPFGMBroadcastReq : public Msg
{ // GM 公告
	enum EConstDefine
	{
		CD_ContentMaxSize = 256,
	};

	MsgPFGMBroadcastReq()
	{
		header.dwType   = PFMSG_GMBROADCAST_REQ;
		header.stLength = sizeof( MsgPFGMBroadcastReq );
		memset( content, 0, CD_ContentMaxSize );
	}
	int8 content[CD_ContentMaxSize];
};

struct MsgPFServerStatusReq : public Msg
{
	MsgPFServerStatusReq()
	{
		header.dwType   = PFMSG_SERVERSTATUS_REQ;
		header.stLength = sizeof( MsgPFServerStatusReq );
	}
};

struct MsgPFServerStatusAck : public Msg
{
	MsgPFServerStatusAck()
	{
		nCount = 0;
		header.dwType   = PFMSG_SERVERSTATUS_ACK;
		header.stLength = sizeof( MsgPFServerStatusAck ) - sizeof(ServerStatus) * ( ECD_MaxCount - nCount );
	}

	enum EConstDefine
	{
		ECD_MaxCount = 10,
	};

	struct ServerStatus
	{
		ServerStatus()
		{
			memset( szName, 0, sizeof( szName ) );
		}

		int8 szName[37]; // 服务器名字
		uint8 uchStatus; // 1 = 有点卡 2 = 无响应( may be 当机 )
	};

	uint8        nCount; // nCount = 0 说明所有服务器良好
	ServerStatus xStatus[ECD_MaxCount];

	void AddServerStatus( const char* pszName, uint8 uchValue )
	{
		if ( nCount >= ECD_MaxCount )
		{ return; }

		strncpy_s( xStatus[nCount].szName, sizeof( xStatus[nCount].szName ), pszName, sizeof( xStatus[nCount].szName ) - 1 );
		xStatus[nCount].uchStatus = uchValue;
		++nCount;
		header.stLength = sizeof( MsgPFServerStatusAck ) - sizeof(ServerStatus) * ( ECD_MaxCount - nCount );
	}
};

struct MsgPFGMReloadTradeShop : public Msg
{ // GM 触发重载金锭商城配置
	MsgPFGMReloadTradeShop()
	{
		header.dwType   = PFMSG_RELOADTRADESHOP_REQ;
		header.stLength = sizeof( MsgPFGMReloadTradeShop );
	}
};

struct MsgPFGMShutdownServersReq : public Msg
{ // GM 触发关闭游戏服务器组
	MsgPFGMShutdownServersReq()
	{
		header.dwType      = PFMSG_SHUTDOWNSERVERS_REQ;
		header.stLength    = sizeof( MsgPFGMShutdownServersReq );
		delayTime = 0;
	}

	uint32 delayTime; // 单位秒
};

struct MsgPFGMChangeMapExpRateReq : public Msg
{ // GM 触发游戏服务器组地图经验比例
	MsgPFGMChangeMapExpRateReq()
	{
		header.dwType        = PFMSG_CHANGEMAPEXPRATE_REQ;
		header.stLength      = sizeof( MsgPFGMChangeMapExpRateReq );
		mapConfigId = InvalidLogicNumber;
		fExpRate    = 1.0f;
	}

	uint32 mapConfigId; // 
	float  fExpRate;    // 单位 1.0 == 100% 
};

struct MsgPFGMOPChatOnOff : public Msg
{ // GM 打开聊天纪录开关
	MsgPFGMOPChatOnOff()
	{
		header.dwType        = PFMSG_GMOPCHATONOFF;
		header.stLength      = sizeof( MsgPFGMOPChatOnOff );
		isOpen      = 0;
	}    
	uint8  isOpen;
};

struct MsgC2PTellServerid:public Msg
{
	MsgC2PTellServerid()
	{
		header.dwType        = PFMSG_C2PTELLSERVERID;
		header.stLength      = sizeof( MsgC2PTellServerid );
		server_id = -1;
	}
	int server_id;
};

enum eRegeResult
{
	eRegeResult_fail = 0,//失败
	eRegeResult_succ,    //成功
	eRegeResult_Refrain, //重复注册
	eRegeResult_max
};

struct MsgP2CRegeResult:public Msg
{
	MsgP2CRegeResult()
	{
		header.dwType        = PFMSG_P2CREGERES;
		header.stLength      = sizeof( MsgC2PTellServerid );
	}
	char _result;
};

struct MsgPFSendMail:public Msg
{
	MsgPFSendMail()
	{
		header.dwType        = PFMSG_SENDMAIL;
		header.stLength      = sizeof( MsgPFSendMail );
	}
	uint32 characterid		;//角色DB ID
	char   charactername[ETaskInfo_NameMaxLength]	;
	char   title[ETaskInfo_TileMaxCount]			;//邮件标题
	char   content[ETaskInfo_MailContentMax]			;//邮件正文
	uint32 money			;//银币
	uint16 itemid			;//物品ID
	uint16 itemcount		;//物品数量
};

struct MsgPFAskForPresent:public Msg
{
	MsgPFAskForPresent()
	{
		header.dwType = PFMSG_ASKFORPRESENT;
		header.stLength = sizeof(MsgPFAskForPresent);
	}
	uint32 characterid;
	uint32 accountid;
	char   sn[33];
	char   charactername[33];
};

struct MsgPFAskForActivity:public Msg
{
	MsgPFAskForActivity()
	{
		header.dwType = PFMSG_ASKFORACTIVITY;
		header.stLength = sizeof(MsgPFAskForActivity);
	}
	uint32 characterid;
	uint32 accountid;
	int32  _type;
	char   charactername[33];
};

struct MsgPFModifyError:public Msg
{
	MsgPFModifyError()
	{
		header.dwType = PFMSG_MODIFY_ERROR;
		header.stLength = sizeof(MsgPFModifyError);
	}
	uint32 characterid;
	uint32 accountid;
	int16  result;//结果
};

struct MsgPFBlockAccount:public Msg
{
	MsgPFBlockAccount()
	{
		header.dwType = PFMSG_BANACCOUNT;
		header.stLength = sizeof(MsgPFBlockAccount);
	}
	uint32 accountid;
	char   name[MAX_NAME_STRING];
	uint32 blocktime;
};

struct MsgPFBlockMac:public Msg
{
	MsgPFBlockMac()
	{
		header.dwType = PFMSG_BANMACADRESS;
		header.stLength = sizeof(MsgPFBlockMac);
	}
	char   cMac[MAC_LENGTH];
	uint32 blocktime;
};

struct MsgPFEpistarPoint:public Msg
{
	MsgPFEpistarPoint()
	{
		header.stLength = sizeof(MsgPFEpistarPoint);
		header.dwType = PFMSG_REQ_EPISTARPOINT;
	}
	uint32 accountid;
	uint32 characterid;
	uint8  _type;			//将来用
	uint16 nItemId;
	uint16 nPoint;
	char   charactername[ETaskInfo_NameMaxLength];
};

struct MsgPFEpistarPointACK:public Msg
{
	MsgPFEpistarPointACK()
	{
		header.stLength = sizeof(MsgPFEpistarPointACK);
		header.dwType = PFMSG_ACK_EPISTARPOINT;
	}
	uint32 accountid;
	uint32 characterid;
	uint16 nItemId;
};

//////////////////////////////////////////////////////////////////////////
//enum EPlatformMessageDefine
//{
//    P2CS_ADDPAYREQ = PLATFORM_MESSAGE_BEGIN, // 充值请求
//    CS2P_ADDPAYACK                         , // 充值回馈
//    CS2P_NEWCARDREQ                        , // 查询卡片请求
//    P2CS_NEWCARDACK                        , // 查询卡片回馈
//};
//
//struct MsgPlatformModule : public DBMsg
//{
//    MsgPlatformModule()
//    { SetModuleType( EMessageModule_Platform ); }
//};
//
//struct P2CSAddPayReq : public MsgPlatformModule
//{
//    P2CSAddPayReq()
//    {
//        header.dwType = P2CS_ADDPAYREQ;
//        header.stLength = sizeof( P2CSAddPayReq );
//    }
//    
//    SPayInfo payInfo;
//};
// 
//struct CS2PAddPayAck : public MsgPlatformModule
//{
//    CS2PAddPayAck()
//    {
//        header.dwType = CS2P_ADDPAYACK;
//        header.stLength = sizeof( CS2PAddPayAck );
//    }
//
//    uint16 result; // 结果
//    uint32 guid  ; // 账号Id
//    uint16 typeId; // 充值账单Id
//};
//
//struct CS2PNewCardReq : public MsgPlatformModule
//{ // 向平台查询卡信息
//    CS2PNewCardReq()
//    {
//        header.dwType = CS2P_NEWCARDREQ;
//        header.stLength = sizeof( CS2PNewCardReq );
//        gssid = 0;
//        memset( passport, 0, sizeof(passport) );
//        types = 0;
//    }
//
//    uint16 gssid       ; // 服务器编号
//    int8   passport[33]; // 用户通行证
//    uint8  types       ; // 新手卡类型
//};
//
//struct P2CSNewCardAck : public MsgPlatformModule
//{ // 向平台查询卡信息
//    P2CSNewCardAck()
//    {
//        header.dwType = P2CS_NEWCARDACK;
//        header.stLength = sizeof( P2CSNewCardAck );
//        result = 0;
//        memset( passport, 0, sizeof(passport) );
//        types = 0;
//    }
//
//    uint16 result      ; // 结果
//    int8   passport[33]; // 用户通行证
//    uint8  types       ; // 新手卡类型
//};


#pragma pack( pop ) 

#endif // __PLATFORMMESSAGEDEFINE_H__
