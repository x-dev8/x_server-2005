/********************************************************************
    Filename:     DBMsg.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

#include "GlobalDef.h"
#include "MessageDefine.h"
#include "CampBattleDefine.h"
//定义数据库和游戏世界交互的消息结构
enum EDBMessageDefine
{
    //数据库相关
    DB_FIRST_MSG = DB_MSG_BEGIN
    ,DBMSG_LOGIN                // 登录帐号
    ,DBMSG_ACKLOGIN             // ACK up
    ,DBMSG_ACKCHAR              // ACK 角色信息
    ,DBMSG_ENDACKCHAR           // 结束ACK查询
    ,DBMSG_SAVECHAR             // 存角色信息
    ,DBMSG_CREATECHAR           // 创建角色
    ,DBMSG_ACKCREATECHAR        // ACK up
    ,DBMSG_DELETECHAR           // 删除角色
    ,DBMSG_ACKDELETECHAR        // ACK up
    ,DBMSG_REGACCOUNTS          // 注册帐号
    ,DBMSG_ACKREGACC            // ACK up
    ,DBMSG_DELACCOUNTS          // 删除帐号
    ,DBMSG_ACKDELACC            // ACK up
    ,DBMSG_OFFLINE              // 帐号离线
    ,DBMSG_GSERVEREXIT
    ,DBMSG_CHANGEPASSWORD       // Change password
    ,DBMSG_ACKCHANGEPASSWORD
    ,DBMSG_CHANGECASHPOINT      // add or deduct cashpoint
    ,DBMSG_ACKCHANGECASHPOINT
    ,DBMSG_QUERYACCOUNTCHAR
    ,DBMSG_ENTERWORD            // 进入游戏世界
    ,DBMSG_ACKENTERWORD         // ACK UP
    ,DBMSG_ACKCHARDATA          // 接收数据库传来的角色数据
    ,DBMSG_ACKCHARITEMBAG       // 接收数据库传来的角色背包数据
    ,DBMSG_SAVEITEM             // 存角色物品包
    ,DBMSG_SAVECHARACTER        // 通知数据库保存角色数据
    ,DBMSG_ACKOPERSUCC          // 通知GameServer存储操作成功 返回消息操作成功
    ,DBMSG_QUERY_SELCHARS       // 登录成功后，请求角色信息
    ,DBMSG_CHARSAVEVARS         // 存角色系统变量
    ,DBMSG_CHARLOADVARS         // 取角色系统变量
    ,DBMSG_ITEMTRACELOG         // 道具跟踪
    ,DBMSG_REQ_STORAGE          // 查询仓库相关数据库
    ,DBMSG_ACK_STORAGE
    ,DBMSG_KICKCHAR             // 通知游戏服务器踢掉某个帐号的角色
    ,DBMSG_ACCOUNTSTATE         // 检测帐号的游戏状态并设置当前状态
    ,DBMSG_ACK_ACCOUNTSTATE     // 返回检测帐号的游戏状态结果

    ,DBMSG_REQ_CREATE_CHECKNAME // 创建 检测 玩家名字是否重复
    ,DBMSG_ACK_CREATE_CHECKNAME // 返回 创建 检测 玩家名字是否重复

	,DBMSG_CHANGENAMEREQ
	,DBMSG_CHANGENAMEACK
    
    ,DBMSG_SAVELEVEL            // 保存等级
    ,DBMSG_SAVEEXP              // 保存经验
    ,DBMSG_SAVESKILLEXP         // 保存技能经验
    ,DBMSG_ADDITEM              // 添加物品
    ,DBMSG_REMOVEITEM           // 移除物品
    ,DBMSG_EXCHANGEITEM         // 交换物品
    ,DBMSG_ITEMATTRIBCHANGE     // 物品属性变化
    ,DBMSG_ITEMAMOUNTCHANGE     // 物品数量变化
    ,DBMSG_ITEMLOCKSTATUSCHANGE // 物品锁定状态变化
    ,DBMSG_CANCELDELCHAR        // 取消删除角色
    ,DBMSG_ACKCANCELDELCHAR     // 回应取消删除角色
    ,DBMSG_REQ_ACCOUNT_BILLING      // 获取帐号点数
    ,DBMSG_ACK_ACCOUNT_BILLING      // 回馈获取帐号点数
    ,DBMSG_REQ_ACCOUNT_BILLING_OP   // 帐号点数操作
    ,DBMSG_LOG                      // 日志消息

    ,DBMSG_ACCOUNTWALLOWINFO_REQ    // 帐号沉迷信息
    ,DBMSG_ACCOUNTWALLOWINFO_ACK    // 帐号沉迷信息
    ,DBMSG_ACCOUNTWALLOWINFO_SAVE   // 帐号沉迷信息存储
    ,DBMSG_KICKCHARACK              // 踢出某帐号的回馈
    ,DBMSG_JIFENGSHOPITEMSLISTREQ   // 积分商城道具查询
    ,DBMSG_JIFENGSHOPITEMSLISTACK   // 积分商城道具列表
    ,DBMSG_JIFENGSHOPITEMSGAINREQ   // 积分商城道具领取
    ,DBMSG_JIFENGSHOPITEMSGAINACK   // 积分商城道具回馈
    ,DBMSG_CHANGENAME               // 改变名字
    ,GS2DB_REQ_INIT_DATA
    ,DB2GS_ACK_INIT_DATA
    ,DB2DB_NOTIFYFILEDBSAVECHAR     // 告诉文件db角色存好了

    ,DBMSG_PETBREEDQUERYREQ         // 宠物繁殖查询
    ,DBMSG_PETBREEDQUERYACK         // 宠物繁殖查询反馈

	,DBMSG_SHOPPING                 //商城购买物品
	,DBMSG_OPERATEACCOUNTMONEY      //操作点数
	,DBMSG_SETBILLINGMONEY          //通知GS设置点数

	,DB2DB_Cash                     //DB SERVER告诉数据库进程充值
	,DB2DB_CashResult               //返回充值结果
	,DBMSG_OPCONSUMESCORE           //操作积分
	,DBMSG_SETCONSUMESCORE
	,DB2DB_ConsumeScore				//DB SERVER告诉数据库进程充值积分
	,DB2DB_ConsumeScoreResult

	,DBMSG_LOADCAMPBATTLEDATA
	,DB2DB_LOADCAMPBATTLEDATA
	,DBMSG_ADDCAMPBATTLEDATA
	,DBMSG_DELCAMPBATTLEDATA

	,GS2DB_UPDATEYUANBAODATA
	,DB2GS_UPDATEYUANBAODATA

	,GS2DB_UPDATEPLAYERPOINT
	,DB2GS_UPDATEPLAYERPOINT
};

#pragma pack(push,1) 

struct DBMsg : public Msg
{
    DBMsg()
    {
        SetLevel(level_high);
        ustLifeCode = 0;
        shServerId  = -1;
        subMarker   = 0;
    }

    // 和ID组合在一起判断唯一的对象 CDBInterface得DispatchMsg转发消息时判断
    unsigned short ustLifeCode; // 生命代码
    short          shServerId;
    unsigned long  subMarker;   // DB消息都带上一条ID，用于标识返回成功
};

//////////////////////////////////////////////////////////////////////////
struct DBMsg_GServerExit : public DBMsg
{
	DBMsg_GServerExit()
	{
		header.dwType = DBMSG_GSERVEREXIT;
		header.stLength = sizeof(*this);
        header.uMsgLevel = level_high;
	}
};
//登录
//typedef DBMsgLogin DBMsgLogin2;
struct DBMsgLogin2:public DBMsg
{
	DBMsgLogin2()
	{
        memset(this, 0, sizeof(DBMsgLogin2));
		header.dwType = DBMSG_LOGIN;
		header.stLength = sizeof( DBMsgLogin2 );
        IsForceLogin = false;
	}
	char szUserName[ dr_MaxUserName ];
    char szPassword[ dr_MaxPassword ];
    char szIP[20];              //IP地址
	//消息发到loginServer时，由loginServer填写
	DWORD dwGWorldServerID;
	//消息发到AccountServer时，由AccountServer填写
	DWORD dwLoginServerID;
    bool IsForceLogin;
};
//消息定义
struct DBMsgAckLogin2:public DBMsg
{

	DBMsgAckLogin2()
	{
		header.dwType = DBMSG_ACKLOGIN;
		header.stLength = sizeof( DBMsgAckLogin2 );
        IsForceLogin = false;
	}
	//是否登录成功
	short		stRet;
	DWORD		dwAccountID;		
    short       stflag;
	//LoginServer根据ID发送到不同的LoginServer
	DWORD dwGWorldServerID;
	//AccountServer根据ID发送到不同的LoginServer
	DWORD dwLoginServerID;
	char szUserName[ dr_MaxUserName ];

	short stCharaterAmount;
    bool IsForceLogin;
};
struct DBMsgQuerySelChars:public DBMsg
{
	DBMsgQuerySelChars()
	{
		header.dwType = DBMSG_QUERY_SELCHARS;
		header.stLength = sizeof( *this );
		dwAccountID = 0;
		memset(szCharname,0,dr_MaxUserName);
	}
	DWORD dwAccountID;
	char  szCharname[dr_MaxUserName];
};

struct DBMsgQueryAccountChar:public DBMsg
{
	DBMsgQueryAccountChar()
	{
		header.dwType = DBMSG_QUERYACCOUNTCHAR;
		header.stLength = sizeof( *this );
		dwAccountId    = 0;
		dwCharacterId  = 0;
		bQueryAllChars = 0;
        needEnd        = 0;
	}
	uint32 dwAccountId;
	uint32 dwCharacterId;
	uint8  bQueryAllChars;
	short  stWitchSlot;
	uint16 ustLifeCode;
    uint8  needEnd;      // 是否需要结束消息
};

struct DBMsgAckCharInfo : public DBMsg
{ // 账号角色的基本信息,选择人物界面使用
	DBMsgAckCharInfo()
	{
		header.dwType   = DBMSG_ACKCHAR;
		header.stLength = sizeof( DBMsgAckCharInfo );
        dwDelTimes      = 0;
	}

	int16         stWhichSlot;
	uint32        dwCharacterID;
    uint8         bIsDel;
	SCharBaseInfo baseinfo;
	SCharVisual   visual;
    uint32        nMapId;
    uint32        dwAccountID;
    uint32        dwDelTimes;       // 剩余时间(单位秒)
};

struct DBMsgEndAckChar:public DBMsg
{ // 结束角色查询
	DBMsgEndAckChar()
	{
		header.dwType = DBMSG_ENDACKCHAR;
		header.stLength = sizeof(DBMsgEndAckChar);
	}
	DWORD dwAccountID;
};

//创建角色数据
struct DBMsgCreateHeroChar : public DBMsg
{
    enum EFlag
    {
        EF_WithEmpty     = 0,
        EF_WithNormalBag = 1 << 1,
    };

	DBMsgCreateHeroChar()
	{
		header.dwType   = DBMSG_CREATECHAR;
		header.stLength = sizeof( DBMsgCreateHeroChar );
        stWhichSlot     = -1;
        withFlag        = EF_WithEmpty;
	}

	uint32        accoundId;		
	int16         stWhichSlot;
	SCharDBInfo   charinfo;
    uint32        withFlag;
};

//创建人物时 检测是否同名
struct DBMsgReqCreateCheckName : public DBMsg
{
    enum ECheckType
    {
        ECT_CreateChar, // 创建角色
        ECT_ChangeName, // 改名字
    };

	DBMsgReqCreateCheckName()
	{
		header.dwType   = DBMSG_REQ_CREATE_CHECKNAME;
		header.stLength = sizeof( DBMsgReqCreateCheckName );
		checkType       = ECT_CreateChar;
	}
	char  szName[dr_MaxUserName];
    int8  checkType; // 是否是改名检查
};

struct DBMsgChangeNameReq : public DBMsg
{
	DBMsgChangeNameReq()
	{
		header.dwType   = DBMSG_CHANGENAMEREQ;
		header.stLength = sizeof( DBMsgChangeNameReq );
	}
	int   PlayerID;
	char  szName[dr_MaxUserName];
};

struct DBMsgChangeNameAck : public DBMsg
{
	DBMsgChangeNameAck()
	{
		header.dwType   = DBMSG_CHANGENAMEACK;
		header.stLength = sizeof( DBMsgChangeNameAck );
	}
	bool Result;
	int   PlayerID;
	char  szName[dr_MaxUserName];
	int GuildID;
};


struct DBMsgAckCreateCheckName : public DBMsg
{
	DBMsgAckCreateCheckName()
	{
		header.dwType = DBMSG_ACK_CREATE_CHECKNAME;
		header.stLength = sizeof( DBMsgAckCreateCheckName );
        memset( szName, 0, sizeof(szName));
	}
    bool bResult;
    int8 checkType; // 是否是改名检查
    char szName[dr_MaxUserName];
};

struct DBMsgCreateCharAck : public DBMsg
{ // ACK创建角色	
	DBMsgCreateCharAck()
	{
		header.dwType = DBMSG_ACKCREATECHAR;
		header.stLength = sizeof( DBMsgCreateCharAck );
        result = ER_Success;
	}

	uint32 result;				
	int16  stWhichSlot;
	uint32 dwCharacterId;
    uint32 accountId;
    int8   charName[dr_MaxPlayerName];
};

//删除角色数据
struct DBMsgDeleteChar2:public DBMsg
{
	DBMsgDeleteChar2()
	{
		header.dwType = DBMSG_DELETECHAR;
		header.stLength = sizeof( DBMsgDeleteChar2 );
	}
	DWORD dwAccountID;		
	short stWhichSlot;
	DWORD dwCharId;
};

//ACK 删除角色
struct DBMsgAckDeleteChar2:public DBMsg
{
	DBMsgAckDeleteChar2()
	{
		header.dwType   = DBMSG_ACKDELETECHAR;
		header.stLength = sizeof( DBMsgAckDeleteChar2 );
	}
	bool bSuccessed;
	short stWhichSlot;		
};

//删除角色数据
struct DBMsgCancelDelChar:public DBMsg
{
    DBMsgCancelDelChar()
    {
        header.dwType = DBMSG_CANCELDELCHAR;
        header.stLength = sizeof( DBMsgCancelDelChar );
    }
    DWORD dwAccountID;		
    short stWhichSlot;
    DWORD dwCharId;
};

//ACK 删除角色
struct DBMsgAckCancelDelChar:public DBMsg
{
    DBMsgAckCancelDelChar()
    {
        header.dwType   = DBMSG_ACKCANCELDELCHAR;
        header.stLength = sizeof( DBMsgAckCancelDelChar );
    }
    bool bSuccessed;
    short stWhichSlot;		
};

struct DBMsgEnterWorld : public DBMsg
{ // 进入游戏世界
	DBMsgEnterWorld()
	{
		header.dwType            = DBMSG_ENTERWORD;
		header.stLength          = sizeof( DBMsgEnterWorld );
        memset(szIP, 0, sizeof(szIP));
        ucNeedTellClientCharInfo = BV_NotNeedTellClientCharInfo;
        ucNeedUseMessageMapInfo  = BV_NotNeedUseMessageMapInfo;
        dwTeamSessionID          = 0;
	}

	short         stSlot;
	DWORD         dwAccountID;
    DWORD         dwCharacterID;
    char          szIP[20]; // 登陆玩家IP
    unsigned long nMapId;
    int16         nTileX;
    int16         nTileY;
    float         fDir;
    uint32        dwTeamSessionID;
    unsigned char ucNeedTellClientCharInfo;
    unsigned char ucNeedUseMessageMapInfo;
};

struct DBMsgAckEnterWorld : public DBMsg
{ // ACK 数据库进入游戏世界
	DBMsgAckEnterWorld()
	{
		header.dwType            = DBMSG_ACKENTERWORD;
		header.stLength          = sizeof( DBMsgAckEnterWorld );		
        nPKValue                 = 0;
        stPKProtectFlag          = 0;
        nStayInHellTime          = 0;
        fDir                     = 0.0f;
        ucNeedTellClientCharInfo = BV_NotNeedTellClientCharInfo;
        ucNeedUseMessageMapInfo  = BV_NotNeedUseMessageMapInfo;
        dwTeamSessionID          = 0;
        nGMLevel                 = 0;
        memset( &runtimeInfo, 0, sizeof(runtimeInfo) );
	}

    unsigned long    bRet;
	DWORD            dwCharacterID;
    unsigned int     nGMLevel;
    int              nPKValue;
    short            stPKProtectFlag;
    unsigned int     nStayInHellTime;           // 已经在地狱坐牢的时间
    unsigned long    nMapId;
    int16            nTileX;
    int16            nTileY;
    float            fDir;
    unsigned char    ucNeedTellClientCharInfo;
    unsigned char    ucNeedUseMessageMapInfo;
    SCharStorageData stStorage;
    SCharDBInfo      charinfo;
    SRuntimeInfo     runtimeInfo;
    uint32           dwTeamSessionID;
	uint32			 dwAccountYuanBaoTotle;
	uint32			 dwAccountYuanBaoStates;//元宝状态
};

struct DBMsgSaveCharacter : public DBMsg
{ // 保存角色信息
	DBMsgSaveCharacter()
	{
		header.dwType     = DBMSG_SAVECHARACTER;
		header.stLength   = sizeof( DBMsgSaveCharacter );
        nPKValue          = 0;
        stPKProtectFlag   = 0;
        accountId         = 0;
        savetype          = EST_None;
	}

	uint32           dwCharacterID;
	uint32           dwSaveTime;       // 距上一次保存的时间差
	SCharDBInfo      dbInfo;
	SCharStorageData storageInfo;
	bool             bOpenDB;
    int32            nPKValue;         // PK值得 
    int16            stPKProtectFlag;  // PK保护模式 
    uint32           nGMLevel;         // GM权限等级 0为无权限
    SRuntimeInfo     runtimeInfo;      // 运行时候的数据
    uint32           accountId;        // 账号Id
    uint8            savetype;         // 保持的类型
};

struct DBAckOperSucc : public DBMsg
{
    DBAckOperSucc()
    {
		header.dwType = DBMSG_ACKOPERSUCC;
		header.stLength = sizeof( *this );
    }
    DWORD dwMsgType;     // 消息类型
    DWORD dwCharacterID; // 角色ID
    DWORD dwMsgID;       // 发送的操作消息ID
};

//玩家离线
struct DBMsgOffline2:public DBMsg
{
	DBMsgOffline2()
	{	
		header.dwType   = DBMSG_OFFLINE;
		header.stLength = sizeof( DBMsgOffline2 );
        nIsJustSwitchGame = 0;
	}
	DWORD dwAccountID;
    char nIsJustSwitchGame;
};

//register account
struct DBMsgRegisterAccounts2:public DBMsg
{
	DBMsgRegisterAccounts2()
	{
		header.dwType   = DBMSG_REGACCOUNTS;
		header.stLength = sizeof(DBMsgRegisterAccounts2);
		memset(szUserName,0,dr_MaxUserName);
		memset(szPassword,0,dr_MaxPassword);
	}
	char szUserName[ dr_MaxUserName ];
	char szPassword[ dr_MaxPassword ];
};

//ack register account
struct DBMsgAckRegisterAccounts2:public DBMsg
{
	enum enum_result_regacc
	{
		regacc_success =0
		,regacc_alreadyhasaccount
		,regacc_failed
	};
	DBMsgAckRegisterAccounts2()
	{
		header.dwType   = DBMSG_ACKREGACC;
		header.stLength = sizeof(DBMsgAckRegisterAccounts2);
	}
	short		stRet;//result
	DWORD		dwAccountID;
};

//delete account
struct DBMsgDeleteAccounts2:public DBMsg
{
	DBMsgDeleteAccounts2()
	{
		header.dwType   = DBMSG_DELACCOUNTS;
		header.stLength = sizeof(DBMsgDeleteAccounts2);
		memset(szUserName,0,dr_MaxUserName);
	}
	char szUserName[ dr_MaxUserName ];
};

//ack delete account
struct DBMsgAckDeleteAccounts2:public DBMsg
{
	DBMsgAckDeleteAccounts2()
	{
		header.dwType   = DBMSG_ACKDELACC;
		header.stLength = sizeof(DBMsgAckDeleteAccounts2);
	}
	bool		bSuccessed;//result
};

//change password
struct DBMsgChangePassword2:public DBMsg
{
	DBMsgChangePassword2()
	{
		header.dwType      = DBMSG_CHANGEPASSWORD;
		header.stLength    = sizeof(DBMsgChangePassword2);
		memset(szUserName,0,dr_MaxUserName);
		memset(szOldPassword,0,dr_MaxPassword);
		memset(szNewPassword,0,dr_MaxPassword);
		bForceChange = false;
	}
	bool bForceChange;                 //force change password when OldPassword is incorrect 
	char szUserName[ dr_MaxUserName ];
	char szOldPassword[ dr_MaxPassword];
	char szNewPassword[ dr_MaxPassword];
};

//ack change password
struct DBMsgAckChangePassword2:public DBMsg
{
	DBMsgAckChangePassword2()
	{
		header.dwType      = DBMSG_ACKCHANGEPASSWORD;
		header.stLength    = sizeof(DBMsgAckChangePassword2);
	}
	bool		bSuccessed;//result
};

//change cashpoint
struct DBMsgChangeCashPoint2:public DBMsg
{
	DBMsgChangeCashPoint2()
	{
		header.dwType      = DBMSG_CHANGECASHPOINT;
		header.stLength    = sizeof(DBMsgChangeCashPoint2);
		memset(szUserName,0,dr_MaxUserName);
		memset(szPassword,0,dr_MaxPassword);
	}
	char szUserName[ dr_MaxUserName ];
	char szPassword[ dr_MaxPassword ];
};

//ack change cashpoint
struct DBMsgAckChangeCashPoint2:public DBMsg
{
	DBMsgAckChangeCashPoint2()
	{
		header.dwType      = DBMSG_ACKCHANGECASHPOINT;
		header.stLength    = sizeof(DBMsgAckChangeCashPoint2);
	}
	short		stRet;//result
};

//
struct DBMsgItemTraceLog : public DBMsg
{
	DBMsgItemTraceLog()
	{
		header.dwType      = DBMSG_ITEMTRACELOG;
		header.stLength    = sizeof(*this);
	}
//		DWORD	dwItemGlobalID;
	//GUID	guid;
	__int64 nBigInt;
	DWORD	dwSrcCharID;
	DWORD	dwDstCharID;
};
//查询仓库定义的结构  server to dbgate
struct DBMsgReqStorage:public DBMsg
{
	DBMsgReqStorage()
	{
		header.dwType = DBMSG_REQ_STORAGE;
		header.stLength = sizeof(DBMsgReqStorage);
	}
	DWORD dwCharacterId;
};
//
struct DBMsgAckStorage:public DBMsg
{
	DBMsgAckStorage()
	{
		header.dwType = DBMSG_ACK_STORAGE;
		header.stLength = sizeof(DBMsgAckStorage);
	}
	DWORD dwCharacterId;
	SCharStorageData stStorage;
};

struct S2SMsgKickChar : public DBMsg
{ // 通知服务器踢人
    enum EKickReason
    {
        KR_AccountRepeat, // 在游戏服务器上游戏的帐号
        KR_Ban,           // Ban角色
        KR_KickToConnect, // 在切服流程中，还没有进游戏场景的踢
    };

    enum EConstDefine
    {
        ECD_AckCount = 2,
    };

	S2SMsgKickChar()
	{
		header.dwType   = DBMSG_KICKCHAR;
		header.stLength = sizeof(S2SMsgKickChar);
        dwAccountID     = InvalidLogicNumber;
        usReason        = KR_AccountRepeat;
        time            = 0;
        uchFailAck      = 0;
        //memset( szSessionKey, 0, sizeof(szSessionKey));
		SessionKey = 0;
	}

	uint32 dwAccountID;
    uint8  usReason;
    uint32 time;
    uint8  uchFailAck;         // 失败回应次数
    //char   szSessionKey[32+1]; // SessionKey
	__int64 SessionKey;
};

struct S2SMsgKickCharAck : public DBMsg
{
    S2SMsgKickCharAck()
    {
        header.dwType   = DBMSG_KICKCHARACK;
        header.stLength = sizeof( S2SMsgKickCharAck );
        dwAccountID     = InvalidLogicNumber;
        time            = 0;
        uchFailAck      = 0;
        //memset( szSessionKey, 0, sizeof(szSessionKey));
		SessionKey = 0;
    }

    uint32 dwAccountID;
    uint8  usReason;
    uint32 time;
    uint8  uchFailAck;          // 失败回应次数
    //char   szSessionKey[32+1];  // 验证码
	__int64 SessionKey;
};

struct DBMsgAccountState:public DBMsg
{
	enum
	{
		state_offline, // 离线
		state_login,   // 登陆
		state_select,  // 选人
		state_play,    // 游戏
        state_change_gameserver // 切服务器
	};
	DBMsgAccountState()
	{
		header.dwType = DBMSG_ACCOUNTSTATE;
		header.stLength = sizeof(DBMsgAccountState);
	}
	DWORD dwAccountID;
	short shState;
};

struct DBMsgAckAccountState:public DBMsg
{
	DBMsgAckAccountState()
	{
		header.dwType = DBMSG_ACK_ACCOUNTSTATE;
		header.stLength = sizeof(DBMsgAckAccountState);
	}
	DWORD dwAccountID;
	short shRet;
    short shState;
};

struct DBMsgSaveLevel : public DBMsg
{
    DBMsgSaveLevel()
    {
        header.dwType = DBMSG_SAVELEVEL;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    unsigned int nLevel;
};

struct DBMsgSaveExp : public DBMsg
{
    DBMsgSaveExp()
    {
        header.dwType = DBMSG_SAVEEXP;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    DWORD nExp;
};

struct DBMsgSkillExp : public DBMsg
{
    DBMsgSkillExp()
    {
        header.dwType = DBMSG_SAVESKILLEXP;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    DWORD nSkillExp;
};

struct DBMsgAddItem : public DBMsg
{
    DBMsgAddItem()
    {
        header.dwType = DBMSG_ADDITEM;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    short type;         //物品容器编号
    unsigned int nPos;              //所处容器中的位置
    SCharItem item;
};

struct DBMsgRemoveItem : public DBMsg
{
    DBMsgRemoveItem()
    {
        header.dwType = DBMSG_REMOVEITEM;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    short type;         //物品容器编号
    unsigned int nPos;              //所处容器中的位置
    __int64 itemid;
};

struct DBMsgItemAttribChange : public DBMsg
{
    DBMsgItemAttribChange()
    {
        header.dwType = DBMSG_ITEMATTRIBCHANGE;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    short type;         //物品容器编号
    unsigned int nPos;              //所处容器中的位置
    SCharItem item;
};

struct DBMsgItemAmountChange : public DBMsg
{
    DBMsgItemAmountChange()
    {
        header.dwType = DBMSG_ITEMAMOUNTCHANGE;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    short type;         //物品容器编号
    unsigned int nPos;              //所处容器中的位置
    __int64 itemid;                 //物品ID
    unsigned int nAmount;           //物品数量
};

struct DBMsgItemLockStatusChange : public DBMsg
{
    DBMsgItemLockStatusChange()
    {
        header.dwType = DBMSG_ITEMLOCKSTATUSCHANGE;
        header.stLength = sizeof(*this);
    }
    DWORD dwCharacterID;
    short type;         //物品容器编号
    unsigned int nPos;              //所处容器中的位置
    __int64 itemid;                 //物品ID
    bool IsLock;                    //是否锁住
};

struct DBMsgReqAccountBilling : public S2SMsg
{
    enum EOpType
    {
        ET_ExchangeJinDing, // 兑换金锭
        ET_QueryPoint,      // 查询点数
    };

    DBMsgReqAccountBilling()
    {
        header.dwType = DBMSG_REQ_ACCOUNT_BILLING;
        header.stLength = sizeof(*this);
        guid  = 0;
        op    = ET_QueryPoint;
        value = 0;
    }
    uint32 guid;   // 帐号guid
    uint8  op;
    uint32 value;  // 使用的点数
};

struct DBMsgAckAccountBilling : public S2SMsg
{
    DBMsgAckAccountBilling()
    {
        header.dwType   = DBMSG_ACK_ACCOUNT_BILLING;
        header.stLength = sizeof(*this);
        guid  = 0;
        point = 0;
        op    = DBMsgReqAccountBilling::ET_QueryPoint;
    }
    uint8  op;
    uint32 result; // result
    uint32 guid;   // 帐号guid
    uint32 point;  // 点数
    uint32 value;  // 使用的点数
};

struct DBMsgReqAccountBillingOp : public S2SMsg
{   
    enum EBillingOpType
    {
        EBOT_Sub,
    };

    DBMsgReqAccountBillingOp()
    {
        header.dwType   = DBMSG_REQ_ACCOUNT_BILLING_OP;
        header.stLength = sizeof(*this);
    }

    uint8  op;     // 操作
    uint32 guid;   // 帐号guid
    uint32 point;  // 点数
};

struct DBMsgLog : public DBMsg
{
    DBMsgLog()
    {
        header.dwType = DBMSG_LOG;
        header.stLength = sizeof(*this);
    }
    char szCharName[dr_MaxPlayerName];
    WORD wCharID;
    char szDate[dr_LengthDate];
    char szTime[dr_LengthDate];
    char szLog[dr_MaxChatString];
};

struct DBAccountWallowInfoReq: public DBMsg
{
    // add by ZhangQi for 防沉迷系统 2010/07/07
   enum {
        ACCOUNT_TYPE_CHILD,
        ACCOUNT_TYPE_ADULT,
    };

    DBAccountWallowInfoReq()
    {
        header.dwType = DBMSG_ACCOUNTWALLOWINFO_REQ;
        header.stLength = sizeof( DBAccountWallowInfoReq );
        accountType = ACCOUNT_TYPE_ADULT;     // add by ZhangQi for 防沉迷系统 2010/07/07
    }

    bool IsChild(){ return ACCOUNT_TYPE_CHILD == accountType ;}

    uint32 accountId;   
    uint32 accountType;    //add by ZhangQi for 防沉迷系统 2010/07/07
};

struct DBAccountWallowInfoAck: public DBMsg
{
    DBAccountWallowInfoAck()
    {
        header.dwType = DBMSG_ACCOUNTWALLOWINFO_ACK;
        header.stLength = sizeof( DBAccountWallowInfoAck );
        accountId                 = 0;
        onlineMinuteTimeForWallow = 0;
        offMinuteTimeForWallow    = 0;
    }
    uint32  accountId;
    uint32  onlineMinuteTimeForWallow; // 在线累计 单位分钟
    uint32  offMinuteTimeForWallow;    // 下线累计 单位分钟
    __int64 lastOfflineTime;           // 现实的释放时间

    //start add by ZhangQi for 防沉迷系统 2010/07/07
    uint32  bOpenAntiAddiction;          //是否打开防沉迷系统
    AntiAddictionTime antiAddictionTime;   //防沉迷系统时间设置
   // end add

};

struct DBAccountWallowInfoSave : public DBMsg
{
    DBAccountWallowInfoSave()
    {
        header.dwType = DBMSG_ACCOUNTWALLOWINFO_SAVE;
        header.stLength = sizeof( DBAccountWallowInfoSave );
        accountId                 = 0;
        onlineMinuteTimeForWallow = 0;
        offMinuteTimeForWallow    = 0;
    }
    uint32  accountId;
    uint32  onlineMinuteTimeForWallow; // 在线累计 单位分钟
    uint32  offMinuteTimeForWallow;    // 下线累计 单位分钟
    __int64 lastOfflineTime;           // 现实的释放时间
};


struct DBMsgJiFengShopItemsListReq : public DBMsg
{ // 积分商城道具查询
    DBMsgJiFengShopItemsListReq()
    {
        header.dwType   = DBMSG_JIFENGSHOPITEMSLISTREQ;
        header.stLength = sizeof( DBMsgJiFengShopItemsListReq );
        accountId = 0;
    }
    uint32 accountId;
};

struct DBMsgJiFengShopItemsListAck : public DBMsg
{ // 积分商城道具列表
    enum EConstDefine
    {
        ECD_MaxJiFengItemCount = 200,
    };

    DBMsgJiFengShopItemsListAck()
    {
        isNew = 1;
        Reset();
        header.dwType   = DBMSG_JIFENGSHOPITEMSLISTACK;
        header.stLength = sizeof( DBMsgJiFengShopItemsListAck ) - sizeof(SJiFengItemRecordServer) * ( ECD_MaxJiFengItemCount - count );        
    }

    void Reset()
    {
        count = 0;
        memset( items, 0, sizeof(items));
    }

    bool AddItem( const SJiFengItemRecordServer& itemRecord )
    {
        if ( count >= ECD_MaxJiFengItemCount )
        { return false; }

        items[count++] = itemRecord;
        header.stLength = sizeof( DBMsgJiFengShopItemsListAck ) - sizeof(SJiFengItemRecordServer) * ( ECD_MaxJiFengItemCount - count );
        return true;
    }

    bool IsFull()
    { return count >= ECD_MaxJiFengItemCount; }

    uint8                   isNew; // 是否是新的
    uint16                  count;
    SJiFengItemRecordServer items[ ECD_MaxJiFengItemCount ];
};

struct DBMsgJiFengShopItemsGainReq : public DBMsg
{ // 积分商城道具领取
    DBMsgJiFengShopItemsGainReq()
    {   
        accountId       = 0;
        count           = 0;

        header.dwType   = DBMSG_JIFENGSHOPITEMSGAINREQ;        
        header.stLength = sizeof( DBMsgJiFengShopItemsGainReq ) - sizeof(uint32) * ( gJiFengGainMaxCount - count );
    }

    bool AddId( const uint32& id )
    {
        if ( count >= gJiFengGainMaxCount )
        { return false; }

        ids[count++] = id;
        header.stLength = sizeof( DBMsgJiFengShopItemsGainReq ) - sizeof(uint32) * ( gJiFengGainMaxCount - count );
        return true;
    }

    bool IsFull()
    { return count >= gJiFengGainMaxCount; }

    bool IsInIds( uint32 id )
    {
        for ( size_t i=0; i<count; ++i)
        {
            if ( id == ids[i] )
            { return true;}
        }
        return false;
    }

    void RecalLength()
    { header.stLength = sizeof( DBMsgJiFengShopItemsGainReq ) - sizeof(uint32) * ( gJiFengGainMaxCount - count );}

    uint32 accountId;
    uint16 count;
    uint32 ids[gJiFengGainMaxCount];
};

struct DBMsgJiFengShopItemsGainAck : public DBMsg
{
    enum EConstDefine
    {
        ECD_MaxJiFengItemCount = 100,
    };

    DBMsgJiFengShopItemsGainAck()
    {
        Reset();
        header.dwType   = DBMSG_JIFENGSHOPITEMSGAINACK;
        header.stLength = sizeof( DBMsgJiFengShopItemsGainAck ) - sizeof(SJiFengItemRecordServer) * ( ECD_MaxJiFengItemCount - count );        
    }

    void Reset()
    {
        count = 0;
        memset( items, 0, sizeof(items));
    }

    bool AddItem( const SJiFengItemRecordServer& itemRecord )
    {
        if ( count >= ECD_MaxJiFengItemCount )
        { return false; }

        items[count++] = itemRecord;
        header.stLength = sizeof( DBMsgJiFengShopItemsGainAck ) - sizeof(SJiFengItemRecordServer) * ( ECD_MaxJiFengItemCount - count );
        return true;
    }

    bool IsFull()
    { return count >= ECD_MaxJiFengItemCount; }

    uint16                  count;
    SJiFengItemRecordServer items[ ECD_MaxJiFengItemCount ];
};

struct MsgReqInitData : public Msg
{
    MsgReqInitData()
    {
        header.dwType   = GS2DB_REQ_INIT_DATA;
        header.stLength = sizeof( MsgReqInitData );
    }
};

struct MsgAckInitData : public Msg
{
    MsgAckInitData()
    {
        header.dwType   = DB2GS_ACK_INIT_DATA;
        header.stLength = sizeof( MsgAckInitData );
    }

    //防沉迷配置数据
    uint32  bOpenAntiAddiction;          //是否打开防沉迷系统
    AntiAddictionTime antiAddictionTime; //防沉迷系统时间设置
};

struct DB2DBNotifyFileDBSaveChar : public DBMsg
{
    DB2DBNotifyFileDBSaveChar()
    {
        header.dwType   = DB2DB_NOTIFYFILEDBSAVECHAR;
        header.stLength = sizeof( DB2DBNotifyFileDBSaveChar );
        charId = 0;
        lifeId = 0;
    }

    uint32 charId;
    uint32 lifeId;
};

struct DBMsgPetBreedQueryReq : public DBMsg
{
    DBMsgPetBreedQueryReq()
    {
        header.dwType   = DBMSG_PETBREEDQUERYREQ;
        header.stLength = sizeof( DBMsgPetBreedQueryReq );
    }

    uint32  dwDBCharacterID;    //目标的DB ID
    int64   nPetGuid       ;    
};

struct DBMsgPetBreedQueryAck : public DBMsg
{
    DBMsgPetBreedQueryAck()
    {
        header.dwType   = DBMSG_PETBREEDQUERYACK;
        header.stLength = sizeof( DBMsgPetBreedQueryAck );
    }
    
    uint32  dwDBCharacterID;    //目标的DB ID
    int64   nPetGuid       ;    
    bool    bIsAcquired    ;    //是否已领取
};

struct DBMsgShopping : public DBMsg
{
	DBMsgShopping()
	{
		header.dwType = DBMSG_SHOPPING;
		header.stLength = sizeof(DBMsgShopping);
	}
	uint32 account_id;
	uint32 character_id;
	uint16 item_id;
	uint16 item_count;
	uint32 cost_money;
	uint32 Unit_price;//单价
	uint8  flag; //lyh++ 类型 0 元宝 1绑金 2 积分 下面2个值是给积分或者绑金用
	uint32 oldValue;
	uint32 newValue;
};



struct DBMsgOperateAccountMoney:public DBMsg
{
	DBMsgOperateAccountMoney()
	{
		header.stLength = sizeof(DBMsgOperateAccountMoney);
		header.dwType = DBMSG_OPERATEACCOUNTMONEY;
	}
	uint32 account_id;
	uint32 character_id;
	uint16 operate_flag;//0:是减,1:是加,2:是设置
	uint32 modify_money;
};

//lyh操作账号积分
struct DBMsgOperateAccountConsumeScore:public DBMsg
{
	DBMsgOperateAccountConsumeScore()
	{
		header.stLength = sizeof(DBMsgOperateAccountConsumeScore);
		header.dwType = DBMSG_OPCONSUMESCORE;
	}
	uint32 account_id;
	uint32 character_id;
	uint16 operate_flag;//0:是减,1:是加,2:是设置
	uint32 modify_money;
};


struct DBMsgSetBillingMoney:public DBMsg
{
	DBMsgSetBillingMoney()
	{
		header.stLength = sizeof(DBMsgSetBillingMoney);
		header.dwType = DBMSG_SETBILLINGMONEY;
	}
	uint32 account_id;
	uint32 character_id;
	uint32 money;
};

struct DBMsgSetConsumeScore:public DBMsg
{
	DBMsgSetConsumeScore()
	{
		header.stLength = sizeof(DBMsgSetConsumeScore);
		header.dwType = DBMSG_SETCONSUMESCORE;
	}
	uint32 account_id;
	uint32 character_id;
	uint32 money;
};


struct DB2DBCash:public DBMsg
{
	DB2DBCash()
	{
		header.stLength = sizeof(DB2DBCash);
		header.dwType = DB2DB_Cash;

		memset(sn,0,17);
	}

	char	sn[17];
	uint32	account_id;
	int		money;
};

//与BillingServerDefine.h中的result定义一定要一致
enum eDB2DBCashResult
{
	eDB2DBCashResult_succ = 0,        //充值成功
	eDB2DBCashResult_cashed = 1,      //已经充值成功
	eDB2DBCashResult_checkerror = 2,  //单号确认失败
	eDB2DBCashResult_max               //未知错误
};

struct DB2DBCashResult:public DBMsg
{
	DB2DBCashResult()
	{
		header.stLength = sizeof(DB2DBCashResult);
		header.dwType = DB2DB_CashResult;
	}

	char sn[17];
	char result;
	int  money;
	uint32 account_id;
	uint32 all_money;
	uint32 account_yuanbao_totle;
	uint32 account_yuanbao_states;
};

struct DB2DBConsumeScore:public DBMsg
{
	DB2DBConsumeScore()
	{
		header.stLength = sizeof(DB2DBConsumeScore);
		header.dwType = DB2DB_ConsumeScore;

		memset(sn,0,17);
	}

	char	sn[17];
	uint32	account_id;
	int		money;
};

struct DB2DBConsumeScoreResult:public DBMsg
{
	DB2DBConsumeScoreResult()
	{
		header.stLength = sizeof(DB2DBConsumeScoreResult);
		header.dwType = DB2DB_ConsumeScoreResult;
	}

	char sn[17];
	char result;
	int  money;
	uint32 account_id;
	uint32 all_money;
};

struct GS2DBUpdateYuanBaoData : public DBMsg
{
	GS2DBUpdateYuanBaoData()
    {
        header.dwType   = GS2DB_UPDATEYUANBAODATA;
        header.stLength = sizeof( GS2DBUpdateYuanBaoData );
		AccountID = 0;
		States = 0;
    }
	unsigned int AccountID;
	unsigned int States;
};
struct DB2GSUpdateYuanBaoData : public DBMsg
{
	DB2GSUpdateYuanBaoData()
    {
        header.dwType   = DB2GS_UPDATEYUANBAODATA;
        header.stLength = sizeof( DB2GSUpdateYuanBaoData );
    }
	unsigned int AccountID;
	unsigned int States;
	bool result;
};

struct GS2DBUpdatePlayerPoint : public DBMsg
{
	GS2DBUpdatePlayerPoint()
    {
        header.dwType   = GS2DB_UPDATEPLAYERPOINT;
        header.stLength = sizeof( GS2DBUpdatePlayerPoint );
		ID = 0;
		States = 0;
		Op = 0;
		Value = 0;
		PlayerID = 0;
    }
	unsigned int PlayerID;
	unsigned int ID;
	unsigned int Op;
	unsigned int States;
	unsigned int Value;
};
struct DB2GSUpdatePlayerPoint : public DBMsg
{
	DB2GSUpdatePlayerPoint()
    {
        header.dwType   = DB2GS_UPDATEPLAYERPOINT;
        header.stLength = sizeof( DB2GSUpdatePlayerPoint );
		ID = 0;
		States = 0;
		Op = 0;
		Value = 0;
		PlayerID = 0;
		ChangeValue = 0;
    }
	unsigned int PlayerID;
	unsigned int ID;
	unsigned int States;
	unsigned int Op;
	unsigned int Value;
	unsigned int ChangeValue;
};
#pragma pack(pop) 
