#ifndef __CENTERGAMEMESSAGE_H__
#define __CENTERGAMEMESSAGE_H__

#pragma once

#include "MsgBase.h"
//#include "MessageDefine.h"
#include "GameDataType.h"
#include "PlatformMessageDefine.h"

#pragma pack( push, 1 ) 

enum CenterServerGameServerMessage
{
    GS2CS_REGISTERGAMESERVERINFO_REQ = CENTERGAME_MESSAGE_BEGIN, // 注册游戏服务器请求
    CS2GS_REGISTERGAMESERVERINFO_ACK,                            // 注册游戏服务器应答

    UPDATEMAPINFO,                    // 更新游戏服务器地图信息（双向）

    CS2GS_LOGININFO,                  // 登陆信息
    S2S_SWITCHGATE,                   // 切换GateServer信息
    GS2CS_SWITCHSTAGEREQ,             // 切场景请求
    CS2GS_SWITCHSTAGEACK,             // 切场景响应
	GS2CS_CREATEMULITSTAGEREQ,
	GS2CS_CREATEMULITSTAGEACK,
                                    
    GS2CS_PLAYEREXITGAMESERVER,       // 玩家离开GameServer
    GS2CS_PLAYERSYNINSERVERINFO,      // 玩家进入GameServer
                                    
    GS2CS_PLAYERCREATETEAMREQ,        // 玩家请求创建队伍
    GS2CS_PLAYERCREATETEAMACK,      
    GS2CS_PLAYERTEAMINVITEEREQ,       // 玩家邀请某某加入队伍
    GS2CS_PLAYERTEAMINVITEEACK,       // 玩家回应被邀请
    GS2CS_PLAYERADDTEAMMEMBERREQ,     // 玩家加入队伍
    GS2CS_PLAYERDELETETEAMMEMBER,
    GS2CS_PLAYERUPDATETEAMMEMBERINFO,
    GS2CS_PLAYERREMOVEFROMTEAMREQ,
    GS2CS_PLAYERREMOVEFROMTEAMACK,
    GS2CS_PLAYERTEAMINFOREQ,
    GS2CS_PLAYERTEAMINFOACK,
    GS2CS_PLAYERUPGRADETEAMREQ,
    GS2CS_PLAYERUPGRADETEAMACK,
    GS2CS_PLAYERCHATMESSAGE,          // 聊天消息
    GS2CS_QUERYPLAYERINFOREQ,
    GS2CS_QUERYPLAYERINFOACK,
    GS2CS_TRANSMIT,                   // 消息转发
    S2S_TRANSMIT_RESULT,              // 消息转发结果

    CS2GS_PLAYERJOINTEAM,               // 玩家加入队伍
    CS2GS_PLAYEREXITTEAM,               // 玩家退出队伍
    CS2GS_TEAMOUTLINE,                  // 玩家下线
    GS2CS_TEAMCHANGEASSIGNMODEREQ,      // 请求更换分配模式
    CS2GS_TEAMCHANGEASSIGNMODEACK,      // 回应更换分配模式
    GS2CS_TEAMCHANGEASSIGNITEMLEVELREQ, // 请求更换队伍物品分配等级
    CS2GS_TEAMCHANGEASSIGNITEMLEVELACK, // 回应更换队伍物品分配等级

    S2S_NOTIFYTIMEEVENT,                    // 时间激活通知
    S2S_CHANGEEXP,                          // 同步经验变更

    S2S_ANTIADDICTIONACCOUNTINFO,           // 账号在线信息
    S2S_NOTIYANTIADDICTIONTIMEINFO,         // 通知游戏服务器反沉迷的阶段时间

    GS2GS_BANSPEAK,                         // 禁言
    GS2GS_CALLPALYER,                       // 跨服拉人
    CS2GS_CREATETEAM,                       // 创建队伍

    GS2CS_DRAWFROMPLATFORM_QUERY,         // 领取东西请求
    CS2GS_DRAWFROMPLATFORM_ACK,           // 领取东西返回

    S2S_CALL_GRAPHIC,                     // 请求呼叫验证码

    CS2GS_SETCHECKCHEATOPEN,              // 设置外挂检测开关

    S2S_UPDATEDROPITEMCONTROL,            // 更新物品掉落阈值控制
    GS2CS_TEAMONLINE,

    CS2GSMSGBORNMAPOPERATE,

//    GS2CS_MONEYITEMEXCHANGE,               // 实物兑换
    MSG_CHANGEMAPCALLBACK,                 // 切换地图回调消息
    S2S_UPDATETRADESHOPCONFIG,             // 更新金锭商城配置文件

    S2S_SHUTDOWNSERVER,                    // 关闭服务器
    S2S_CHANGEMAPEXPRATE,                  // 改变地图经验比率

    GS2CS_MAILLISTREQ,                     // 请求邮件列表
    CS2GS_MAILLISTACK,                     // 回馈邮件列表
    GS2CS_SENDMAILREQ,                     // 请求发邮件
    CS2GS_SENDMAILACK,                     // 回馈发邮件
    GS2CS_OPMAILREQ,                       // 邮件操作
    CS2GS_OPMAILACK,                       // 邮件操作回馈

    GS2CS_QUERYMAILCANSENDREQ,             // 查询邮件是否可以发送
    CS2GS_QUERYMAILCANSENDACK,             // 回馈邮件是否可以发送
    S2S_REMOTEBANREQ,                      // 远程Ban请求
	S2S_DleteCountryBattleReward,			//国王站奖励删除
    CS2GSLOADFRESOURCESUCCESS,

    CS2DB_ITEMDROPCONTROLREQ,       // 保存物品掉落阈值相关
    DB2CS_ITEMDROPCONTROL,
    CS2GS_ITEMDROPCONTROL,
    CS2DB_SAVEITEMDROPCONTROL,
    CS2GS_UPDATECOUNTRYONLINECOUNT,

    //***********************************************无敌分割线**
    MSG_PARTITIONLOGFILE,

    CS2GS_OPRECORDCHATONOFF,     // 是否打开聊天纪录开关
    S2S_RECORDCHATCONTENT,       // 上传聊天内容
    CS2GS_REWARDOPERATE,         // 全服奖励

	GS2CS_CREATETEAM,			// 创建单人队伍
	GS2CS_DISBANDTEAM,			// 解散队伍
	GS2CS_DISBANDTEAMACK,		// 解散队伍回复

	GS2CS_UPDATEANTIADDICTIONINFOREQ, // 更新防沉迷信息请求
	CS2GS_UPDATEANTIADDICTIONINFOACK, // 更新防沉迷信息反馈
	CS2GS_PING,
	CS2LS_LOGIN_ERROR,               //登录失败
	CS2GS_QUEUE_OP,                  //排队开启开关
	GS2CS_REQ_EPISTARPOINT,          //请求添加晶元点
	CS2GS_CHARREMOVEITEMBYID,        //让gs的某个玩家删除特定id的物品
	CS2GS_UPDATEARELOADCONFIG,		 //让GS重新加载指定配置文件
    // 如有增加游戏逻辑协议请加上上面 下面给GM用
    CS2GS_GMBROATCAST_REQ  = CENTERGAME_MESSAGE_BEGIN + 1000,
    CS2GS_GMKICKPLAYER_REQ,
	CS2GS_PLATFORMSENDMAILREQ,        //platform请求发送邮件,要在game server生成物品信息
	CS2GS_PLATFORMSENDMAILACK,        //game server返回发送
	GS2CS_ASKFORPRESENT,              //向CENTER SERVER发起请求礼品
	GS2CS_ASKFORPLATFORMACTIVITY,     //向CENTER SERVER发起请求平台活动

	CS2GS_ASKBROADCAST,				  //向game server请求公告触发消息
	GS2CS_ASKBROADCAST_ACK,			  //向center server返回公告触发消息

	S2S_BlockAccount,				  //锁帐号
	S2S_BlockMacAddress,		      //锁mac 只给运营用

	CS2GS_TEAMSTATECHANGE,
};

struct GS2CSRegiseterGameServerInfoReq : public Msg
{   
    GS2CSRegiseterGameServerInfoReq()
    {
        header.dwType = GS2CS_REGISTERGAMESERVERINFO_REQ;
        header.stLength = sizeof( GS2CSRegiseterGameServerInfoReq );
        Reset();
    }
    
    enum RegisterOpType
    {
        ROT_NOT_REPLACE,
        ROT_REPLACE,
		ROT_LOOP,//循环注册 一直到注册上为止
    };

    void Reset()
    {
        memset( szGameServerName, 0, sizeof(szGameServerName));
        btReset = ROT_NOT_REPLACE;
        nServerId = 0;
    }

    char szGameServerName[32];
    unsigned long nServerId;
    char btReset;
};

struct CS2GSRegiseterGameserverInfoAck : public Msg
{
    CS2GSRegiseterGameserverInfoAck()
    {
        header.dwType = CS2GS_REGISTERGAMESERVERINFO_ACK;
        header.stLength = sizeof( CS2GSRegiseterGameserverInfoAck );
    }   
    
    unsigned short nResult;
};

struct MessageUpdateMapInfo : public Msg
{
    enum EConstDefine
    {
        PerMessageGameStageMaxCount = 20,
    };

    MessageUpdateMapInfo()
    {
        header.dwType   = UPDATEMAPINFO;
        header.stLength = 0;
        Reset();
    }

    void Reset()
    {
        memset( szGameStageOp, 0, sizeof(szGameStageOp));
        szGameStageCount = 0;
    }

    bool AddStageOp( const SGameStageOp& gs )
    {
        if ( szGameStageCount >= PerMessageGameStageMaxCount)
            return false;

        szGameStageOp[szGameStageCount] = gs;
        ++szGameStageCount;

        header.stLength = sizeof(*this) - sizeof(SGameStageOp) * ( PerMessageGameStageMaxCount - szGameStageCount);
        return true;
    }
    
    SGameStageOp* GetStageOp( int nIndex )
    {
        if ( nIndex >= szGameStageCount || nIndex >= PerMessageGameStageMaxCount )
            return NULL;
        
        return &(szGameStageOp[nIndex]);
    }
    
    char szGameStageCount;
    SGameStageOp szGameStageOp[PerMessageGameStageMaxCount];
};

struct CS2GSLoginInfo : public MsgLoginInfo
{
    CS2GSLoginInfo ()
    {
        header.dwType = CS2GS_LOGININFO;
        header.stLength = sizeof(CS2GSLoginInfo);
    }
    char          clientPeerInServerType;
    unsigned long nServerId; 
};

struct S2SSwitchGate : public MsgSwitchGate
{
    S2SSwitchGate()
    {
        header.dwType = S2S_SWITCHGATE;
        header.stLength = sizeof(S2SSwitchGate );
    }
    char          nSourcePeerInServerType; // ClientPeer所在服务器类型
    char          nTargetServerType;       // 新目标服务器类型
    unsigned long nTargetServerId;         // 新目标目标服务器Id
    unsigned long nAccountId;              // 账号Id
    unsigned long dwMapID;
    float fX;
    float fY;
    float fDir;
};

struct GS2CSSwitchStageReq : public Msg
{
    GS2CSSwitchStageReq()
    {
        header.dwType = GS2CS_SWITCHSTAGEREQ;
        header.stLength = sizeof(GS2CSSwitchStageReq);
        ustCountryID = 0;
    }
    
    char          nSwitchStageType;
    unsigned long nAccountId;
    unsigned long nCharacterDbId;
    short         stWhichSlot;
    unsigned long nMapId;
    unsigned long nSessionId;
    float         fX;
    float         fY;
    float         fDir;
    unsigned long dwTime;
    unsigned long nServerId;
    short         ustCountryID;
	unsigned long nTargetServerId;
};


struct GS2CSCreateMulitStageReq : public Msg
{
    GS2CSCreateMulitStageReq()
    {
        header.dwType = GS2CS_CREATEMULITSTAGEREQ;
        header.stLength = sizeof(GS2CSCreateMulitStageReq);
    }
	//跨GameServer创建副本 并且返回值
	uint32		PlayerDBID;
	uint32		MapID;
	uint32		EctypeMapID;
	float		x;
	float		y;
	float		dir;
	unsigned short Level;
	uint32		ReserveValue;
	long		GameServerID;
};

struct GS2CSCreateMulitStageAck : public Msg
{
    GS2CSCreateMulitStageAck()
    {
        header.dwType = GS2CS_CREATEMULITSTAGEACK;
        header.stLength = sizeof(GS2CSCreateMulitStageAck);
		ErrorID = 0;
    }
	//跨GameServer创建副本 并且返回值
	uint32		PlayerDBID;
	bool		Result;
	uint32		ErrorID;
	long		GameServerID;
	uint32		MapID;
	float		x;
	float		y;
	float		dir;
};



struct CS2GSSwitchStageAck : public Msg
{
    CS2GSSwitchStageAck ()
    {
        header.dwType = CS2GS_SWITCHSTAGEACK;
        header.stLength = sizeof(CS2GSSwitchStageAck);
        ucNeedTellClientCharInfo = BV_NotNeedTellClientCharInfo;
        ucNeedUseMessageMapInfo  = BV_NotNeedUseMessageMapInfo;
        ucIsLocalFlyMap          = BV_NotLocalFlyMap;
        dwTeamSessionId          = 0;
    }

    short         nResult;    
    unsigned long nAccountId;
    unsigned long nCharDBId;
    short         stWhichSlot;
    DWORD         dwTime;
    unsigned long nMapId;
    float         fX;
    float         fY;
    float         fDir;
    unsigned char ucNeedTellClientCharInfo; // 是否要告诉客户端角色数据      【只有第一次时候发】
    unsigned char ucNeedUseMessageMapInfo;  // 是否要使用此消息中带的地图信息【切服或者地图被纠正】
    unsigned char ucIsLocalFlyMap;          // 是否是当前服务器切地图
    unsigned long dwTeamSessionId;            // 世界唯一的队伍id
};

struct GS2CSPlayerExit : public Msg
{
    GS2CSPlayerExit()
    {
        header.dwType   = GS2CS_PLAYEREXITGAMESERVER;
        header.stLength = sizeof(GS2CSPlayerExit);
        cExitType       = ET_ExitGame;
		blockTime		= 0;
        //memset( szSessionKey, 0, sizeof(szSessionKey) );
		SessionKey = 0;
    }

    uint32 nAccountId;         // 帐号Id
    uint32 dwDBID;             // 角色dbId
    uint8  cExitType;          // 退出类型
    uint32 blockTime;          // 需要block的时间
    //int8   szSessionKey[32+1]; // 登陆码
	__int64 SessionKey;
};

struct GS2CSPlayerSynInServerInfo : public Msg
{ // 同步玩家在所在服务器的信息 (在哪个服务器哪张地图哪个位置干什么)
    enum EStatus
    {
        ES_None,
        ES_InServerLoginStage, // 在GameServer或者Character的LoginStage中
        ES_FirstInMapStagePlaying,  // 第一次在GameServer的MapStage中游戏
        ES_InMapStagePlaying,  // 在GameServer的MapStage中游戏
		ES_OfflineStall,	// 离线摆摊中
    };

    GS2CSPlayerSynInServerInfo()
    {
        header.dwType   = GS2CS_PLAYERSYNINSERVERINFO;
        header.stLength = sizeof(GS2CSPlayerSynInServerInfo);
    
        nAccountId     = 0;
        nCharacterDbId = 0;
        memset( &serverInfo, 0, sizeof(SServerInfo) );
        memset( szCharacterName, 0, sizeof(szCharacterName));
        ucStatus       = ES_None;
    }
    unsigned long nAccountId;
    unsigned long nCharacterDbId;
    unsigned char uchCountry;
    char          szCharacterName[dr_MaxPlayerName];
    SServerInfo   serverInfo; // 服务器信息
    unsigned char ucStatus;   // 状态
};


struct CS2GSCreateTeam : public Msg
{
    CS2GSCreateTeam()
    {
        header.dwType = CS2GS_CREATETEAM;
        header.stLength = sizeof(CS2GSCreateTeam);
    }

    uint32 dwTeamSessionID;       // 队伍SessionID
    uint8 AssignMode;			  // 队伍分配模式
    uint8 AssignItemLevel;        // 队伍物品的分配等级
};

struct CS2GSAckJoinTeam : public Msg
{
    CS2GSAckJoinTeam()
    {
        header.dwType = CS2GS_PLAYERJOINTEAM;
        header.stLength = sizeof(CS2GSAckJoinTeam);
        bIsTeamHeader = false;
    }

    uint32 dwTeamSessionID;               // 队伍sessionid
    uint32 dwDataBaseID;                  // 加入的队员ID
    char szName[dr_MaxPlayerName];        // 加入队员的名字
    int nHp;                              // 加入队伍时的HP
    int nMp;                              // 加入队伍时的MP 
    int nHpMax;                           // 加入队伍时的最大HP
    int nMpMax;                           // 加入队伍时的最大MP
    short stLevel;                        // 加入队伍时的等级
    uint8 chProfession;                   // 职业 
    uint8 chSex;                          // 性别
    int nFaceId;                          // 预留脸部的Id
    int nHairId;                          // 头发ID
    int nHeadPicId;                       // 头像ID

    bool bIsTeamHeader;                   // 是否是队长
    short stManipleID;                    // 小队ID
    bool bIsManipleHeader;                // 是否是小队长

    uint8 chAssignModeType;
    uint8 chAssignItemLevel;      
};

struct CS2GSExitTeam : public Msg
{
    CS2GSExitTeam()
    {
        header.dwType = CS2GS_PLAYEREXITTEAM;
        header.stLength = sizeof(CS2GSExitTeam);
    }

    uint32 dwDataBaseID;
    uint32 dwTeamSessionID;
};

// 创建单人队伍
struct GS2CSCreateTeam : public Msg
{
	GS2CSCreateTeam()
	{
		header.dwType = GS2CS_CREATETEAM;
		header.stLength = sizeof(GS2CSCreateTeam);

		dwReqID = 0;
		memset(szReqName, 0, sizeof(szReqName));
		AssignMode = 0;
		AssignItemLevel = 0;
	}

	uint8 uchCountry;                     // 请求者国家
	unsigned long dwReqID;                // 请求者的id
	char szReqName[dr_MaxPlayerName];     // 请求者名字
	int nHp;                              // 加入队伍时的HP
	int nMp;                              // 加入队伍时的MP 
	int nHpMax;                           // 加入队伍时的最大HP
	int nMpMax;                           // 加入队伍时的最大MP
	short stLevel;                        // 加入队伍时的等级
	uint8 chProfession;                   // 职业 
	uint8 chSex;                          // 性别
	int nFaceId;                          // 预留脸部的Id
	int nHairId;                          // 头发ID
	int nHeadPicId;                       // 头像ID

	uint8 AssignMode;
	uint8 AssignItemLevel;           // 队伍分配等级
};

struct GS2CSPlayerTeamInviteeReq : public Msg
{
    GS2CSPlayerTeamInviteeReq()
    {
        header.dwType = GS2CS_PLAYERTEAMINVITEEREQ;
        header.stLength = sizeof(GS2CSPlayerTeamInviteeReq);
        memset(szReqName, 0, sizeof(szReqName));
        memset(szAckName, 0, sizeof(szAckName));

        AssignMode = 0;
        nFaceId = 0;
    }

    char szAckName[dr_MaxPlayerName];     // 被请求者名字
    
    uint8 uchCountry;                     // 请求者国家
    unsigned long dwReqID;                // 请求者的id
    char szReqName[dr_MaxPlayerName];     // 请求者名字
    int nHp;                              // 加入队伍时的HP
    int nMp;                              // 加入队伍时的MP 
    int nHpMax;                           // 加入队伍时的最大HP
    int nMpMax;                           // 加入队伍时的最大MP
    short stLevel;                        // 加入队伍时的等级
    uint8 chProfession;                   // 职业 
    uint8 chSex;                          // 性别
    int nFaceId;                          // 预留脸部的Id
    int nHairId;                          // 头发ID
    int nHeadPicId;                       // 头像ID

	bool countryTeam;					  // 是否可以忽略国家的判断
    
	uint8 AssignMode;			  // 队伍分配模式
    uint8 AssignItemLevel;        // 队伍物品的分配等级
};

struct CS2GSTeamStateChange : public Msg
{
	CS2GSTeamStateChange()
    {
        header.dwType = CS2GS_TEAMSTATECHANGE;
        header.stLength = sizeof(CS2GSTeamStateChange);
    }

	unsigned int TeamID;
	bool Result;
};

struct GS2CSPlayerTeamInviteeAck : public Msg
{
    GS2CSPlayerTeamInviteeAck()
    {
        header.dwType = GS2CS_PLAYERTEAMINVITEEACK;
        header.stLength = sizeof(GS2CSPlayerTeamInviteeAck);
        memset(szAckName,0, sizeof(szAckName));
    }
    
    unsigned long dwReqID;
    unsigned long dwAckID;
    char szAckName[dr_MaxPlayerName];        //被邀请者的名字
    int nHp;                              // 加入队伍时的HP
    int nMp;                              // 加入队伍时的MP 
    int nHpMax;                           // 加入队伍时的最大HP
    int nMpMax;                           // 加入队伍时的最大MP
    short stLevel;                        // 加入队伍时的等级
    uint8 chProfession;                   // 职业 
    uint8 chSex;                          // 性别
    int nFaceId;                          // 预留脸部的Id
    int nHairId;                          // 头发ID
    int nHeadPicId;                       // 头像ID
    unsigned char AssignMode;             //队伍分配模式
    unsigned char AssignItemLevel;
	uint8 bAgree;						  // 是否同意
};

struct GS2CSTeamOnLine : public Msg
{
    GS2CSTeamOnLine()
    {
        header.dwType = GS2CS_TEAMONLINE;
        header.stLength = sizeof( GS2CSTeamOnLine );
    }
    uint32 dwID;
};

struct CS2GSMsgTeamOutLine : public Msg
{
    CS2GSMsgTeamOutLine()
    {
        header.dwType = CS2GS_TEAMOUTLINE;
        header.stLength = sizeof(CS2GSMsgTeamOutLine);
    }

    DWORD dwID;
    DWORD dwTeamSessionID;
};

struct GS2CSPlayerUpdateTeamMemberInfo : public Msg
{
    GS2CSPlayerUpdateTeamMemberInfo()
    {
        header.dwType = GS2CS_PLAYERUPDATETEAMMEMBERINFO;
        header.stLength = sizeof(GS2CSPlayerUpdateTeamMemberInfo);
        memset( szName, 0, sizeof( szName ) );
    }

    unsigned long dwSessionId;
    unsigned long dwDataBaseId;
    int nHp; 
    int nHpMax;
    int nMp;
    int nMpMax;    
    unsigned char Profession;
    short stLevel;
    DWORD dwMapID;
    short x;                //格子坐标
    short y;
    float fx;
    float fy;
    short stManiple;
    bool bManipleHeader;            //小队队长
    bool bTeamHeader;
    short stSex;
    int nFaceID;
    int nHairID;
    int nHeadPicId;
    char szName[dr_MaxPlayerName];
};

struct GS2CSPlayerRemoveFromTeamReq : public Msg
{
    GS2CSPlayerRemoveFromTeamReq()
    {
        header.dwType = GS2CS_PLAYERREMOVEFROMTEAMREQ;
        header.stLength = sizeof(GS2CSPlayerRemoveFromTeamReq);
    }
    unsigned long dwSessionId;
    unsigned long dwDataBaseId;         // -1 就是请求解散队伍来着
    bool bKick;                    //是否要踢掉的
};

struct GS2CSPlayerRemoveFromTeamAck : public Msg
{
    GS2CSPlayerRemoveFromTeamAck()
    {
        header.dwType = GS2CS_PLAYERREMOVEFROMTEAMACK;
        header.stLength = sizeof(GS2CSPlayerRemoveFromTeamAck);

        bDisband = false;
    }
    unsigned long dwSessionId;
    unsigned long dwDataBaseId;
    bool bDisband;              // 是否解散
};

// 解散队伍
struct GS2CSPlayerDisbandTeam : public Msg
{
	GS2CSPlayerDisbandTeam()
	{
		header.dwType = GS2CS_DISBANDTEAM;
		header.stLength = sizeof( GS2CSPlayerDisbandTeam );

		dwDataBaseID = 0;
		dwTeamSessionID = 0;
	}

	uint32 dwDataBaseID;
	uint32 dwTeamSessionID;
};

struct GS2CSPlayerDisbandTeamAck : public Msg
{
	GS2CSPlayerDisbandTeamAck()
	{
		header.dwType = GS2CS_DISBANDTEAMACK;
		header.stLength = sizeof( GS2CSPlayerDisbandTeamAck );

		dwDataBaseID = 0;
		dwTeamSessionID = 0;
	}

	uint32 dwDataBaseID;
	uint32 dwTeamSessionID;
};

struct GS2CSPlayerUpgradeTeamReq : public Msg
{
    GS2CSPlayerUpgradeTeamReq()
    {
        header.dwType = GS2CS_PLAYERUPGRADETEAMREQ;
        header.stLength = sizeof(GS2CSPlayerUpgradeTeamReq);
    }

    DWORD dwSessionId;              
    DWORD dwDataBaseId;             //把某人提升为队长
};

struct GS2CSPlayerUpgradeTeamAck : public Msg
{
    GS2CSPlayerUpgradeTeamAck()
    {
        header.dwType = GS2CS_PLAYERUPGRADETEAMACK;
        header.stLength = sizeof(GS2CSPlayerUpgradeTeamAck);
        memset(szName, 0, sizeof(szName));
    }

    DWORD dwSessionId;              
    DWORD dwDataBaseId;             //把某人提升为队长
    char szName[dr_MaxPlayerName];
};


//GS2CS_TEAMCHANGEASSIGNMODEREQ,                                  // 请求更换分配模式
//CS2GS_TEAMCHANGEASSIGNMODEACK,                                  // 回应更换分配模式
//GS2CS_TEAMCHANGEASSIGNITEMLEVELREQ,                             // 请求更换队伍物品分配等级
//CS2GS_TEAMCHANGEASSIGNITEMLEVELACK,                             // 回应更换队伍物品分配等级

struct GS2CSTeamChangeAssignModeReq : public Msg
{
    GS2CSTeamChangeAssignModeReq()
    {
        header.dwType = GS2CS_TEAMCHANGEASSIGNMODEREQ;
        header.stLength = sizeof(*this);
    }

    uint32 dwTeamSessionID;                 // 队伍sessionid
    uint32 dwTeamHeaderID;                  // 队长id            
    uint8 chAssignMode;                     // 要改变的分配模式
};

struct CS2GSTeamChangeAssignModeAck : public Msg
{
    CS2GSTeamChangeAssignModeAck()
    {
        header.dwType = CS2GS_TEAMCHANGEASSIGNMODEACK;
        header.stLength = sizeof(*this);
    }

    uint32 dwTeamSessionID;                 // 队伍sessionid
    uint8 chAssignMode;                     // 分配模式
};

struct GS2CSTeamChangeAssignItemLevelReq : public Msg
{
    GS2CSTeamChangeAssignItemLevelReq()
    {
        header.dwType = GS2CS_TEAMCHANGEASSIGNITEMLEVELREQ;
        header.stLength = sizeof(*this);
    }

    uint32 dwTeamSessionID;                 // 队伍sessionid
    uint32 dwTeamHeaderID;                  // 队长id            
    uint8 chAssignItemLevlel;               // 要改变的物品分配等级
};

struct CS2GSTeamChangeAssignItemLevelAck : public Msg
{
    CS2GSTeamChangeAssignItemLevelAck()
    {
        header.dwType = CS2GS_TEAMCHANGEASSIGNITEMLEVELACK;
        header.stLength = sizeof(*this);
    }

    uint32 dwTeamSessionID;                 // 队伍sessionid
    uint8 chAssignItemLevel;               // 物品分配等级
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
struct GS2GSBanSpeak : public Msg
{
    GS2GSBanSpeak()
    {
        header.dwType = GS2GS_BANSPEAK;
        header.stLength = sizeof(GS2GSBanSpeak);
        memset(szName, 0, sizeof(szName));
        dwDBID = InvalidLogicNumber;
    }

    uint32 dwBanTime;                   // 禁言时间
    char  szName[dr_MaxPlayerName];     // 禁言的对象
    uint32 dwDBID;                      // 经验对象
};

struct GS2GSCallPlayer : public Msg
{
    GS2GSCallPlayer()
    {
        header.dwType = GS2GS_CALLPALYER;
        header.stLength = sizeof(GS2GSCallPlayer);
        memset(szName, 0, sizeof(szName));
    }

    char  szName[dr_MaxPlayerName];     // 禁言的对象
    uint32 dwMapID;
    float fX;
    float fY;
    float fDir;
};

struct GS2CSPlayerChatMessage : public Msg
{
    //enum EConstDefine
    //{
    //    BUFFER_SIZE = 1536,
    //};

    GS2CSPlayerChatMessage()
    {
        header.dwType = GS2CS_PLAYERCHATMESSAGE;
        header.stLength = sizeof(GS2CSPlayerChatMessage);
        memset(szBuf, 0, sizeof(szBuf));
    }

    uint32 dwRecvID;                // 接收人ID
    char szBuf[ dr_MaxChatString ];      // 消息内容
};

/////////////////////////////////////////////////////////////////////////////////
struct GS2CSQueryPlayerInfoReq : public Msg
{
    GS2CSQueryPlayerInfoReq()
    {
        header.dwType = GS2CS_QUERYPLAYERINFOREQ;
        header.stLength = sizeof(GS2CSQueryPlayerInfoReq);

        memset(szAckName, 0, sizeof(szAckName));
    }

    enum ActionType
    {
        Action_FlyToPlayer = 0,
        Action_ItemFlyToPlayer,
    };

    DWORD dwReqID;                  //请求者
    DWORD dwAckID;                  //被请求
    char szAckName[dr_MaxPlayerName];       //被请求者名字

    int nAction;                    //请求玩家信息以后的动作
};


struct GS2CSQueryPlayerInfoAck : public Msg
{
    GS2CSQueryPlayerInfoAck()
    {
        header.dwType = GS2CS_QUERYPLAYERINFOACK;
        header.stLength = sizeof(GS2CSQueryPlayerInfoAck);

        memset(szAckName, 0, sizeof(szAckName));
    }

    DWORD dwReqID;                          //请求者
    DWORD dwAckID;                          //被请求
    char szAckName[dr_MaxPlayerName];       //被请求者名字
    int nAction;                            //请求玩家信息以后的动作

    unsigned int nMapID;           //当前地图ID
    float fX;
    float fY;                     //格子坐标
    float fDir;
};

//////////////////////////////////////////////////////////////////////////
// 原来在GameServer广播的消息 加个附加数据 同步到 CenterServer
// 保证全世界的广播
struct S2STransmit : public S2SMsg
{
    enum ESessionType   // 发送的目标范围
    { 
        SESSIONT_None,
        SESSIONT_World,   // 全世界
        SESSTONT_Single,  // 单体
        SESSIONT_Team,    // 队伍
        SESSIONT_Guild,   // 公会
        SESSIONT_Server,  // 服务器
        SESSIONT_Country, // 国家
        SESSIONT_Max,
    };

    enum EConstDefine
    {
        BUFFER_SIZE = 1024 * 32,
    };

    struct SCharacter
    {
        unsigned long uDbId;
        char          szName[dr_MaxPlayerName]; 
    };

    struct STeam
    {
        unsigned long dwSessionID; // session id
        short nTeamIndex;          // 队员在队伍中的索引

        STeam& operator == (const STeam& xTeam)
        {
            if(this != &xTeam)
            {
                dwSessionID = xTeam.dwSessionID;
                nTeamIndex  = xTeam.nTeamIndex;
            }

            return *this;
        }
    };

    struct SGuild
    {
        unsigned long id;
    };

    struct SServer
    {
        unsigned long id;
        char          exceptMe;
    };

    struct SCountry
    {
        TCountryId countryId;
    };

    union uDataType
    {
        SCharacter character;
        STeam      team;
        SGuild     guild;
        SServer    server;
        SCountry   country;
    };

    S2STransmit()
    {
        header.dwType   = GS2CS_TRANSMIT;
        header.stLength = sizeof(S2STransmit) - sizeof( buffer );
        directToClient = 1;
    }

    bool StorageMessage( Msg* pMessage )
    {
        if ( pMessage->GetLength() >= BUFFER_SIZE )
        { return false; }

        memcpy_s( buffer, sizeof( buffer), pMessage, pMessage->GetLength());
        header.stLength = sizeof(S2STransmit) - sizeof( buffer ) + pMessage->GetLength();
        return true;
    }
    unsigned char ucSessionType;
    uDataType     targetData;
    unsigned char directToClient;
    char          buffer[ BUFFER_SIZE ];
};

struct S2STransmitResult : public S2SMsg
{
    enum ETResult
    {
        ETR_Success,
        ETR_ClientPeerNotExist,
        ETR_GamePeerNotExist,
    };

    struct SCharacter
    {
        unsigned long uDbId;
        char          szName[dr_MaxPlayerName]; 
    };

    struct STeam
    {   
        unsigned long id;
    };

    struct SGuild
    {
        unsigned long id;
    };

    struct SServer
    {
        unsigned long id;
    };

    union uDataType
    {
        SCharacter character;
        STeam      team;
        SGuild     guild;
        SServer    server;
    };

    S2STransmitResult()
    {
        header.dwType   = S2S_TRANSMIT_RESULT;
        header.stLength = sizeof(S2STransmitResult);
    }

    unsigned long  nResult;
    unsigned char  ucSessionType;
    uDataType      targetData;
    unsigned long  msgType;
};

struct S2SNotifyTimeEvent : public Msg
{ 
    S2SNotifyTimeEvent()
    {
        header.stLength = sizeof(S2SNotifyTimeEvent);
        header.dwType   = S2S_NOTIFYTIMEEVENT;
    }

    unsigned long timeEventValue;
};

struct S2SChangeExp : public Msg
{ 
    S2SChangeExp()
    {
        header.stLength = sizeof(S2SChangeExp);
        header.dwType   = S2S_CHANGEEXP;
        expPer = 100;
    }
    int expPer;
};

struct S2SAntiAddictionAccountInfo : public Msg
{ 
    S2SAntiAddictionAccountInfo()
    {
        header.stLength = sizeof(S2SAntiAddictionAccountInfo);
        header.dwType   = S2S_ANTIADDICTIONACCOUNTINFO;
    }
    unsigned long accountId;        // 账号
    unsigned long onlineMinuteTime; // 在线时间
    unsigned long offMinuteTime;    // 线下时间
};

struct S2SNotiyAntiAddictionTimeInfo : public Msg
{
    S2SNotiyAntiAddictionTimeInfo()
    {
        header.stLength = sizeof(S2SNotiyAntiAddictionTimeInfo);
        header.dwType   = S2S_NOTIYANTIADDICTIONTIMEINFO;
		bOpenantiAddiction = false;
		nAntiAddictionSaveTime = 0;
	}

	bool              bOpenantiAddiction;
	AntiAddictionTime antiAddictionTime ;
	uint32            nAntiAddictionSaveTime;
};

struct GS2CSDrawFromPlatformQuery : public Msg
{
    GS2CSDrawFromPlatformQuery()
    {
        header.stLength = sizeof(GS2CSDrawFromPlatformQuery);
        header.dwType   = GS2CS_DRAWFROMPLATFORM_QUERY;
    }

    uint8  drawType;
    uint32 guid;
};

struct CS2GSDrawFromPlatformAck : public Msg
{
    CS2GSDrawFromPlatformAck()
    {
        header.stLength = sizeof( CS2GSDrawFromPlatformAck );
        header.dwType   = CS2GS_DRAWFROMPLATFORM_ACK;
    }

    uint16 drawType;
    uint32 result; // 结果
    uint32 guid;   // 用户id
    uint32 value;  // 人民币
};

struct S2SCallGraphic : public Msg
{
    S2SCallGraphic()
    {
        header.stLength = sizeof( S2SCallGraphic );
        header.dwType   = S2S_CALL_GRAPHIC;
    }
};

struct CS2GSMsgSetCheckCheatOpen : public Msg
{
    CS2GSMsgSetCheckCheatOpen()
    {
        header.dwType = CS2GS_SETCHECKCHEATOPEN;
        header.stLength = sizeof( CS2GSMsgSetCheckCheatOpen );
    }

    bool bOpen;
};


struct S2SMsgUpdateItemDropControl : public Msg
{
    S2SMsgUpdateItemDropControl()
    {
        header.dwType = S2S_UPDATEDROPITEMCONTROL;
        header.stLength = sizeof( S2SMsgUpdateItemDropControl );

        dwDropCount = 0;
    }

    uint16 nItemID;
    uint32 dwControlCount;
    uint32 dwDropCount;
};

struct CS2GSMsgBornMapOperate : public Msg
{
    CS2GSMsgBornMapOperate()
    {
        header.dwType = CS2GSMSGBORNMAPOPERATE;
        header.stLength = sizeof( CS2GSMsgBornMapOperate );
    }
 
    bool chOperate;
};

//struct GS2CSMoneyItemExchange : public Msg
//{
//    GS2CSMoneyItemExchange()
//    {
//        header.dwType = GS2CS_MONEYITEMEXCHANGE;
//        header.stLength = sizeof( GS2CSMoneyItemExchange );
//    }
//
//    uint32  guid;
//    int8    charName[33];
//    uint16  itemId;
//    int64   itemguid;
//    int8    itemName[17];
//    int8    linkman[17];
//    int8    telephone[13];
//    int8    email[50];
//    int8    identityCard[19];
//    int8    passport[33];
//};

struct CS2GSGMBroatcastReq : public Msg
{
    enum EConstDefine
    {
        CD_ContentMaxSize = 512,
    };

    CS2GSGMBroatcastReq()
    {
        header.dwType = CS2GS_GMBROATCAST_REQ;
        header.stLength = sizeof( CS2GSGMBroatcastReq );
    }

    int8 content[CD_ContentMaxSize];
};

struct CS2GSGmKickPlayerReq : public Msg
{ // GM 踢人
    CS2GSGmKickPlayerReq()
    {
        header.dwType   = CS2GS_GMKICKPLAYER_REQ;
        header.stLength = sizeof( CS2GSGmKickPlayerReq );
        accountGuid = 0;
        chardbId    = InvalidLogicNumber;
        memset( charName, 0, sizeof( charName ));
        time        = 0;
    }
    uint32  accountGuid;  // 帐号
    uint32  chardbId;     // 角色Id
    int8    charName[33]; // 角色名
    uint32  time;         // s 秒
};

struct MsgChangeMapCallBack : public Msg
{
    MsgChangeMapCallBack()
    {
        header.dwType   = MSG_CHANGEMAPCALLBACK;
        header.stLength = sizeof( *this );
    }

    uint32 dwTeamSessionID;
};

struct S2SUpdateTradeShopConfig : public Msg
{ // 积分商城道具领取
    enum EConstDefine
    {
        ECD_ConfigBufferMaxSize = 50 * 1024,
    };

    S2SUpdateTradeShopConfig()
    {
        Reset();
        header.dwType   = S2S_UPDATETRADESHOPCONFIG;
        header.stLength = sizeof( S2SUpdateTradeShopConfig ) - sizeof( buffer );
    }

    void Reset()
    {
        zip = 0;
        bufferSize = 0;
        memset( buffer, 0, sizeof(buffer));
    }

    bool Clone( const uint8* inBuffer, uint32 size, bool bZip = true )
    {
        if ( size >= ECD_ConfigBufferMaxSize)
        { return false; }

        zip = bZip;
        bufferSize = size;
        memcpy_s( buffer, ECD_ConfigBufferMaxSize, inBuffer, size );
        header.stLength = sizeof( S2SUpdateTradeShopConfig ) - sizeof( buffer ) + size;
        return true;
    }
   
    uint8  zip;
    uint32 bufferSize;
    uint8  buffer[ECD_ConfigBufferMaxSize];
};

struct S2SShutdownServer : public Msg
{
    S2SShutdownServer()
    {
        header.dwType   = S2S_SHUTDOWNSERVER;
        header.stLength = sizeof( S2SShutdownServer );
        serverType      = ST_CenterServer;
        delayTime       = 0;
    }

    uint8  serverType;
    uint32 delayTime;  // 秒
};

struct S2SChangeMapExpRate : public Msg
{
    S2SChangeMapExpRate()
    {
        header.dwType   = S2S_CHANGEMAPEXPRATE;
        header.stLength = sizeof( S2SChangeMapExpRate );
        mapConfigId = InvalidLogicNumber;
        fExpRate    = 1.0f;
    }

    uint32 mapConfigId; // 单位秒
    float  fExpRate;    // 1.0 == 100% 
};

struct GS2CSMailListReq : public Msg
{
    GS2CSMailListReq()
    {
        header.dwType   = GS2CS_MAILLISTREQ;
        header.stLength = sizeof( GS2CSMailListReq );
        accountId = 0;
        charDbId  = 0;
    }
    uint32 accountId;
    uint32 charDbId;
};

struct CS2GSMailListAck : public Msg
{
    CS2GSMailListAck()
    {
        header.dwType = CS2GS_MAILLISTACK;
        header.stLength = sizeof(CS2GSMailListAck) - sizeof(mails);
        accountId = 0;
        charDbId  = 0;
        count     = 0;
        isnew     = 1;
        memset( mails, 0, sizeof(mails));
    }

    void Reset()
    {
        count = 0;        
        memset( mails, 0, sizeof(mails));
    }

    bool AddMail( const SMail& mail )
    {
        if ( count >= EM_MailMaxCount )
        { return false; }

        mails[count++] = mail;
        header.stLength = sizeof(CS2GSMailListAck) - sizeof(SMail) * ( EM_MailMaxCount - count );
        return true;
    }

    bool IsFull()
    {
        if ( count >= EM_MailMaxCount )
        { return true; }
        return false;
    }

    void RecalLength()
    { header.stLength = sizeof(CS2GSMailListAck) - sizeof(SMail) * ( EM_MailMaxCount - count ); }

    uint32 accountId;
    uint32 charDbId;
    uint8  isnew;
    uint8  count;
    SMail  mails[EM_MailMaxCount];
};

struct GS2CSSendMailReq : public Msg
{ // 请求发邮件
    GS2CSSendMailReq()
    {
        header.dwType   = GS2CS_SENDMAILREQ;
        header.stLength = sizeof( GS2CSSendMailReq );
        accountId = InvalidLogicNumber;
        
    }
    uint32 accountId;
    uint32 charDbId;
    SMail  mail;
};

struct CS2GSSendMailAck : public Msg
{ // 请求发邮件回馈
    CS2GSSendMailAck()
    {
        header.dwType   = CS2GS_SENDMAILACK;
        header.stLength = sizeof( CS2GSSendMailAck ) - sizeof(SMail);
        result = ER_Success;
    }

    void RecalLength()
    {
        header.stLength = sizeof( CS2GSSendMailAck );
    }

    uint32 result;
    uint32 accountId;
    uint32 charDbId;
    SMail  mail;
};

struct GS2CSOpMailReq : public Msg
{ // 邮件操作
    GS2CSOpMailReq()
    {
        header.dwType   = GS2CS_OPMAILREQ;
        header.stLength = sizeof( GS2CSOpMailReq );
        op = 0;
        mailId = 0;
        accountId = 0;
        charDbId = 0;
    }
    uint8  op;
    uint32 mailId;
    uint32 accountId;
    uint32 charDbId;
};

struct CS2GSOpMailAck : public Msg
{ // 邮件操作回馈
    CS2GSOpMailAck()
    {
        header.dwType   = CS2GS_OPMAILACK;
        header.stLength = sizeof( CS2GSOpMailAck ) - sizeof(accessory.content);
        result = ER_Success;
        op = 0;
        mailId = 0;
        accountId = 0;
        charDbId = 0;
        money = 0;
    }

    void RecalLength()
    { header.stLength = sizeof( CS2GSOpMailAck ); }

    uint32     result;
    uint8      op;
    uint32     mailId;
    uint32     accountId;
    uint32     charDbId;
    uint32     money;
    SMail::SAccessory accessory; // 附件类型
};
struct GS2CSQueryMailCanSendReq : public Msg
{
    GS2CSQueryMailCanSendReq()
    {
        header.dwType   = GS2CS_QUERYMAILCANSENDREQ;
        header.stLength = sizeof( GS2CSQueryMailCanSendReq );
        memset( targets, 0, sizeof(targets) );
        isHaveItem = 0;
    }

    uint32          charDbId;                     // 发起人
    uint8           isHaveItem;                 // 包括钱和物品
    SMail::SAddress targets[EM_TargetMaxCount]; // 所有人的地址
};

struct CS2GSQueryMailCanSendAck : public Msg
{
    CS2GSQueryMailCanSendAck()
    {
        header.dwType   = CS2GS_QUERYMAILCANSENDACK;
        header.stLength = sizeof( CS2GSQueryMailCanSendAck );
    }
    uint32                result;                     // 结构
    uint32                charDbId;                     // 发起人
    SMail::SAddressResult targets[EM_TargetMaxCount]; // 错误的目标地址
};

struct S2SRemoteBanReq : public Msg
{
    S2SRemoteBanReq()
    {
        header.dwType   = S2S_REMOTEBANREQ;
        header.stLength = sizeof( S2SRemoteBanReq );
    }
    char   chOrAcc;                   // 角色名为0/帐号为1,注意使用帐号时要用帐号ID
    int8   _Name[dr_MaxPlayerName]; // 目标名字
    uint32 banTime;                    // ban的时间
	uint32 accountid;				//帐号ID
};

//zhuxincong
struct S2SDleteCountryBattleReward: public Msg
{
	S2SDleteCountryBattleReward()
	{
		header.dwType = S2S_DleteCountryBattleReward;
		header.stLength = sizeof( S2SDleteCountryBattleReward );
		nPosition = 0;
		nPlayerID = 0;
	}

	int nPosition;
	int nPlayerID;
};


struct MsgPartitionLogFile : public Msg
{
    MsgPartitionLogFile()
    {
        header.dwType   = MSG_PARTITIONLOGFILE;
        header.stLength = sizeof( MsgPartitionLogFile );
    }
};

struct CS2GSOpRecordChatOnOff : public Msg
{
    CS2GSOpRecordChatOnOff()
    {
        header.dwType   = CS2GS_OPRECORDCHATONOFF;
        header.stLength = sizeof( CS2GSOpRecordChatOnOff);
        isOpen = 0;
    }
    int8 isOpen;
};

struct S2SRecordChatContent : public Msg
{
    enum EConstDefine
    {
        ECD_ContentMaxSize = 1024,
    };

    S2SRecordChatContent()
    {
        header.dwType   = S2S_RECORDCHATCONTENT;
        header.stLength = sizeof( S2SRecordChatContent) - sizeof(content);
        length = 0;
        memset( content, 0, sizeof(content));
    }

    void BuildString(const char* szFormat, ...)
    {
        va_list vl;
        va_start(vl, szFormat);
        int cnt = vsnprintf_s( content, sizeof(content), sizeof(content)-1, szFormat, vl);
        va_end(vl);

        length = (uint16)strlen( content );
        header.stLength += length;
    }

    uint16 length;
    int8   content[ECD_ContentMaxSize];
};

struct CS2GSMsgRewardOperate : public Msg
{
    CS2GSMsgRewardOperate()
    {
        header.dwType   = CS2GS_REWARDOPERATE;
        header.stLength = sizeof( CS2GSMsgRewardOperate );
    }

    enum EConstDefine
    {
        ECD_Exp = 0,
    };

    uint8 uchType;
    uint32 dwValue;
};

struct CS2GSLoadResourceSuccess : public Msg
{
    CS2GSLoadResourceSuccess()
    {
        header.dwType   = CS2GSLOADFRESOURCESUCCESS;
        header.stLength = sizeof( CS2GSLoadResourceSuccess );
    }

    uint8 uchLoadType;
};

struct CS2DBItemDropControlReq : public Msg
{
    CS2DBItemDropControlReq()
    {
        header.dwType = CS2DB_ITEMDROPCONTROLREQ;
        header.stLength = sizeof( CS2DBItemDropControlReq );
    }
};

struct ItemDropInfo
{
    uint16 nItemID;
    ItemDropControl xControl;
};

struct DB2CSItemDropControl : public Msg
{
    DB2CSItemDropControl()
    {
        header.dwType = DB2CS_ITEMDROPCONTROL;
        header.stLength = sizeof( DB2CSItemDropControl ) - sizeof( xDropInfo );
        nCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 500,
    };

    int nCount;
    ItemDropInfo xDropInfo[ECD_MaxCount];

    void AddItemDropControl( uint16 nItemID, uint32 dwControlCount, uint32 dwDropCount )
    {
        if ( nCount >= ECD_MaxCount )
        { return; }

        xDropInfo[nCount].nItemID = nItemID;
        xDropInfo[nCount].xControl.dwControlCount = dwControlCount;
        xDropInfo[nCount].xControl.dwDropCount    = dwDropCount;

        ++nCount;
        header.stLength += sizeof( ItemDropInfo );
    }

    bool IsFull() { return nCount >= ECD_MaxCount; }

    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof ( DB2CSItemDropControl ) - sizeof( xDropInfo );
    }

};

struct CS2GSItemDropControl : public Msg
{
    CS2GSItemDropControl()
    {
        header.dwType = CS2GS_ITEMDROPCONTROL;
        header.stLength = sizeof( CS2GSItemDropControl ) - sizeof( xDropInfo );
        nCount = 0;
    }

    enum EConstDefine
    {
        ECD_MaxCount = 500,
    };

    int nCount;
    ItemDropInfo xDropInfo[ECD_MaxCount];

    void AddItemDropControl( uint16 nItemID, uint32 dwControlCount, uint32 dwDropCount )
    {
        if ( nCount >= ECD_MaxCount )
        { return; }

        xDropInfo[nCount].nItemID = nItemID;
        xDropInfo[nCount].xControl.dwControlCount = dwControlCount;
        xDropInfo[nCount].xControl.dwDropCount    = dwDropCount;

        ++nCount;
        header.stLength += sizeof( ItemDropInfo );
    }

    bool IsFull() { return nCount >= ECD_MaxCount; }

    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof ( CS2GSItemDropControl ) - sizeof( xDropInfo );
    }

};

struct CS2DBSaveItemDropControl : public Msg
{
    CS2DBSaveItemDropControl()
    {
        header.dwType = CS2DB_SAVEITEMDROPCONTROL;
        header.stLength = sizeof( CS2DBSaveItemDropControl ) - sizeof( xDropInfo );
        nCount = 0;
    }

    struct ItemDropInfo
    {
        uint16 nItemID;
        ItemDropControl xControl;
    };

    enum EConstDefine
    {
        ECD_MaxCount = 500,
    };

    int nCount;
    ItemDropInfo xDropInfo[ECD_MaxCount];

    void AddItemDropControl( uint16 nItemID, uint32 dwControlCount, uint32 dwDropCount )
    {
        if ( nCount >= ECD_MaxCount )
        { return; }

        xDropInfo[nCount].nItemID = nItemID;
        xDropInfo[nCount].xControl.dwControlCount = dwControlCount;
        xDropInfo[nCount].xControl.dwDropCount    = dwDropCount;

        ++nCount;
        header.stLength += sizeof( ItemDropInfo );
    }

    bool IsFull() { return nCount >= ECD_MaxCount; }

    void Reset()
    {
        nCount = 0;
        header.stLength = sizeof ( CS2DBSaveItemDropControl ) - sizeof( xDropInfo );
    }
};

struct CS2GSUpdateCountryOnLineCount : public Msg
{
    CS2GSUpdateCountryOnLineCount()
    {
        header.dwType = CS2GS_UPDATECOUNTRYONLINECOUNT;
        header.stLength = sizeof( CS2GSUpdateCountryOnLineCount );
    }

    uint8 uchCountryID;
    int nCount;
};

struct GS2CSUpdateAntiaddictionInfoReq : public Msg
{ // 更新防沉迷信息
	enum EUpdateReqType
	{
		EUpdateReqType_Init  , // 第一次登录拿
		EUpdateReqType_Update, // 游戏中Update
		EUpdateReqType_Exit  , // 退出保存
	};

	GS2CSUpdateAntiaddictionInfoReq()
	{
		header.dwType   = GS2CS_UPDATEANTIADDICTIONINFOREQ;
		header.stLength = sizeof( GS2CSUpdateAntiaddictionInfoReq );
		nType = EUpdateReqType_Init;
		memset( passport, 0, sizeof(passport));
		nAccountId = 0;
		nDuration = 0;
	}

	uint8  nType       ; // 操作类型
	int8   passport[33]; // 账号
	uint32 nAccountId  ; // 账号Id
	uint32 nDuration   ; // 经过的时间 单位分钟
};

struct CS2GSUpdateAntiaddictionInfoAck : public Msg
{ // 更新防沉迷信息
	CS2GSUpdateAntiaddictionInfoAck()
	{
		header.dwType   = CS2GS_UPDATEANTIADDICTIONINFOACK;
		header.stLength = sizeof( CS2GSUpdateAntiaddictionInfoAck );
		nResult = ER_Success;
		nAccountId = 0;
		nOnlineTime = 0;
		nDuration = 0;
	}

	uint16 nResult     ; // 结果
	uint8  nType       ; // 操作类型
	uint32 nAccountId  ; // 账号Id
	uint32 nOnlineTime ; // 累计在线时间
	uint32 nDuration   ; // 经过的时间 单位分钟
};

struct CS2GSPing : public Msg
{
	CS2GSPing()
	{
		header.dwType = CS2GS_PING;
		header.stLength = sizeof(CS2GSPing);
	}
};

#pragma pack( pop ) 

#pragma pack( push, 1)
struct SqlMessage 
{ // 请求查询的的消息cache到结构的buff中
	enum ESqlMessageId
	{
		ESM_CanLogin        = 1000,
		ESM_PlayerInGame    ,
		ESM_PlayerExitGame  ,
		ESM_ClientConnectGateOverTime , // 客户端连接Gate超时
		ESM_GameWorldNotReady,
		ESM_KickSuccess,
		ESM_ProcessLoginAllowTimeOver, // 处理登录时间太长了
		ESM_NotGameServerService,      // 服务器繁忙
		ESM_KickInValid,               // 无效的Kick
		ESM_OfflineStall,				// 设置账号状态为离线摆摊
	};

	int     nMessageId;                       // 消息Id
	int     Guid;                             //帐号ID    
	//char    GLSId[MAX_NAME_STRING+1];       // 数据库中是32字节
	char    Passport[MAX_NAME_STRING+1];      //帐号名
	//char    sPassword[MAX_PASSWORD_STRING+1]; //密码,应该是加密后的
	int     AccountLevel;                     //帐号等级
	//char    SessionKey[40+1];          //认证session,唯一,永永远远是唯一
	__int64   SessionKey;
	//char    Token[32+1];
	//char    Seed[40+1];
	char    IpPort[128+1];					  //帐号验证的IP地址
	short   Status;							  // 登录状态 1 --- 登陆进来，dbcenter可以处理 2 --- dbcenter拿到这个用户 3 --- dbcenter处理完毕，client端可以登录游戏服务器 4 --- 用户已在game server中 
	int     State_Time;						  // 超时时间
	uint32  MessageCreateTime;				  // 此消息产生时间
	int8    isWallow;						  // 是否是成年人

	SqlMessage()
	{ memset(this,0,sizeof(SqlMessage)); }

	SqlMessage(const SqlMessage& table)
	{
		if (&table == this)
		{ return ; }
		memcpy_s( this, sizeof(SqlMessage), &table, sizeof(SqlMessage));
	}

	void Clear()
	{  memset(this,0,sizeof(SqlMessage));}

	bool operator ==(const SqlMessage &other)
	{
		return Guid == other.Guid;
	}

	bool operator ==(const int GuildId)
	{
		return Guid == GuildId;
	}

	bool operator ==(const char* Passport)
	{
		return strcmp(this->Passport , Passport) == 0;
	}

	SqlMessage& operator =(const SqlMessage& Passport)
	{
		if (&Passport == this)
		{
			return *this;
		}
		memcpy_s(this, sizeof(SqlMessage), &Passport, sizeof(SqlMessage));
		return *this;
	}
};

struct KickMessage
{
	KickMessage()
	{
		nGuid = 0;
		memset( szPassport, 0, sizeof(szPassport) );
		bProcess = 0;
		bAcceptTime = 0;
	}

	unsigned int  nGuid;
	char          szPassport[32+1];
	char          bProcess; // 是否被处理过
	unsigned long bAcceptTime;
};

struct MsgCenterKick:public Msg
{
	MsgCenterKick()
	{
		SetType( TO_CENTER_LOGIN_KICK );
		SetLength( sizeof( MsgCenterKick ) );
	}
	uint32           _loginserverId;
	KickMessage sql;
};

struct MsgCenterLoginOn:public Msg
{
	MsgCenterLoginOn()
	{
		SetType( TO_CENTER_LOGIN_ON );
		SetLength( sizeof( MsgCenterLoginOn ) );
	}
	uint32           _loginserverId;
	SqlMessage sql;
};

struct MsgCenterLoginOff:public Msg
{
	MsgCenterLoginOff()
	{
		SetType( TO_LOGIN_LOGIN_OFF );
		SetLength( sizeof( MsgCenterLoginOff ) );
	}
	uint32           _loginserverId;
	SqlMessage sql;
};


enum eLoginError
{
	eLE_AccountInGame = 0,//帐号已经在线
	eLE_AccountServerFullLoad ,//服务器人数已满
	eLE_AccountOverOneMac,//服务器单mac超过上限
};
struct MsgLoginError:public Msg 
{
	MsgLoginError()
	{
		SetType(CS2LS_LOGIN_ERROR);
		SetLength(sizeof(MsgLoginError));
	}
	uint32 uAccountId;
	uint8  chErrorType;
};

struct MsgPFSendmailReq:public Msg
{
	MsgPFSendmailReq()
	{
		header.stLength = sizeof(MsgPFSendmailReq);
		header.dwType  = CS2GS_PLATFORMSENDMAILREQ;
	}
	uint32 characterid		;//角色DB ID
	char   charactername[ETaskInfo_NameMaxLength]	;
	char   title[ETaskInfo_TileMaxCount]			;//邮件标题
	char   content[ETaskInfo_MailContentMax]			;//邮件正文
	uint32 money			;//银币
	uint16 itemid			;//物品ID
	uint16 itemcount		;//物品数量
};

struct MsgPFSendmailAck:public Msg
{
	MsgPFSendmailAck()
	{
		header.stLength = sizeof(MsgPFSendmailAck);
		header.dwType  = CS2GS_PLATFORMSENDMAILACK;
	}
	uint32 characterid		;//角色DB ID
	char   charactername[ETaskInfo_NameMaxLength]	;
	char   title[ETaskInfo_TileMaxCount]			;//邮件标题
	char   content[ETaskInfo_MailContentMax]			;//邮件正文
	uint32 money			;//银币
	SCharItem item			;
};

struct MsgGS2CSAskForPresent:public Msg
{
	MsgGS2CSAskForPresent()
	{
		header.stLength = sizeof(MsgGS2CSAskForPresent);
		header.dwType = GS2CS_ASKFORPRESENT;
	}
	uint32 characterid;
	uint32 accountid;
	char   sn[33];
	char   charactername[33];
};

struct MsgGS2CsAskForPlatformActivity:public Msg 
{
	MsgGS2CsAskForPlatformActivity()
	{
		header.stLength = sizeof(MsgGS2CsAskForPlatformActivity);
		header.dwType = GS2CS_ASKFORPLATFORMACTIVITY;
	}
	uint32 characterid;
	uint32 accountid;
	int32  _type;
	char   charactername[33];
};

struct MsgCS2GSQueueOp:public Msg
{
	MsgCS2GSQueueOp()
	{
		header.stLength = sizeof(MsgCS2GSQueueOp);
		header.dwType = CS2GS_QUEUE_OP;
		_open = false;
	}
	bool _open;
};

struct MsgGS2CSEpistarPoint:public Msg
{
	MsgGS2CSEpistarPoint()
	{
		header.stLength = sizeof(MsgGS2CSEpistarPoint);
		header.dwType = GS2CS_REQ_EPISTARPOINT;
	}
	uint32 accountid;
	uint32 characterid;
	uint8  _type;			//将来用
	uint16 nItemId;
	uint16 nPoint;
	char   charactername[ETaskInfo_NameMaxLength];
};
struct MsgCS2GSCharRemoveItembyId:public Msg
{
	MsgCS2GSCharRemoveItembyId()
	{
		header.stLength = sizeof(MsgCS2GSCharRemoveItembyId);
		header.dwType = CS2GS_CHARREMOVEITEMBYID;
	}
	uint32 characterid;
	uint16 nItemId;
};

struct MsgCS2GSUpdateReloadCfg:public Msg
{
	MsgCS2GSUpdateReloadCfg()
	{
		header.stLength = sizeof(MsgCS2GSUpdateReloadCfg);
		header.dwType = CS2GS_UPDATEARELOADCONFIG;
		nReloadType = -1;
	}
	uint16 nReloadType;
};
struct MsgS2SBlockAccount:public Msg
{
	MsgS2SBlockAccount()
	{
		header.stLength = sizeof(MsgS2SBlockAccount);
		header.dwType = S2S_BlockAccount;
	}
	uint32 guid;
	char   name[MAX_NAME_STRING];
	uint32 blocktime;
};

struct MsgS2SBlockMac:public Msg
{
	MsgS2SBlockMac()
	{
		header.stLength = sizeof(MsgS2SBlockMac);
		header.dwType = S2S_BlockMacAddress;
	}
	char   scMac[MAC_LENGTH];
	uint32 blocktime;
};

struct MsgCS2GSBroadCast : public Msg
{
	enum Type
	{
		Type_Monster,

		Type_Max,
	};

	MsgCS2GSBroadCast()
	{
		header.stLength = sizeof( MsgCS2GSBroadCast );
		header.dwType = CS2GS_ASKBROADCAST;

		type = Type_Max;
		nMonsterID = -1;
		nMapID = -1;
	}

	Type type;
	int nMonsterID;
	int nMapID;
};

struct MsgGS2CSBroadCastAck : public Msg
{
	MsgGS2CSBroadCastAck()
	{
		header.dwType = GS2CS_ASKBROADCAST_ACK;
		header.stLength = sizeof( MsgGS2CSBroadCastAck );

		type = MsgCS2GSBroadCast::Type_Max;
		nResult = -1;
	}

	MsgCS2GSBroadCast::Type type;
	int nResult;
};

#pragma pack( pop )

#endif // __CENTERGAMEMESSAGE_H__
