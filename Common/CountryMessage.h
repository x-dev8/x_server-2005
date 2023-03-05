#ifndef __GAMECOUNTRYMESSAGE_H__
#define __GAMECOUNTRYMESSAGE_H__

/************************************************************************
            国家消息定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "MessageRangeDefine.h"
#include "CountryDefine.h"
#include "GlobalDef.h"

#pragma pack( push, 1 )

enum CountryMessageDefine
{
    MSG_TELLCOUNTRYTITLEINFO = GAMEWORD_COUNTRYMSG_BEGIN,          // 广播国家称号
    MSG_QUERYCOUNTRYINFOREQ,                                       // 查看国家信息
    MSG_QUERYCOUNTRYINFOACK,                                       // 查看国家信息
	MSG_UPDATECOUNTRYINFOACK,                                      // 更新国家信息
    MSG_TELLCOUNTRYQUERYSTATUS,                                    // 通知国家任务状态
    MSG_COUNTRYNOTICECHANGEREQ,                                    // 请求更改国家公告
    MSG_COUNTRYNOTICECHANGEACK,                                    // 更改国家公告回馈
    MSG_COUNTRYQUESTSTATECHANGEREQ,                                // 请求发布国家任务
    MSG_COUNTRYQUESTSTATECHANGEACK,                                // 请求发布国家任务回馈
    MSG_COUNTRYOFFICIALAPPOINTREQ,                                 // 请求任命国家官员
    MSG_COUNTRYOFFICIALAPPOINTACK,                                 // 请求任命国家官员回馈
    MSG_COUNTRYOFFICIALRECALLREQ,                                  // 请求免除国家官员
    MSG_COUNTRYOFFICIALRECALLACK,                                  // 请求免除国家官员回馈
    MSG_COUNTRYQUESTSTATUSSTOP,                                    // 通知某个国家发布任务结束了
    MSG_TELLCOUNTRYKILLPOSITION,                                   // 全世界广播杀死了某国官员
    MSG_COUNTRYREQUESTRAISEREQ,                                    // 请求国家募集
    MSG_COUNTRYREQUESTRAISEACK,                                    // 国家募集回馈
    MSG_COUNTRYRAISETOPLAYERREQ,                                   // 向玩家请求募捐
    MSG_COUNTRYRAISETOPLAYERACK,                                   // 玩家募捐回馈
    MSG_COUNTRYRAISETELLPLAYER,                                    // 通知玩家募集结果
    MSG_COUNTRYRECEIVEMOUNTACK,                                    // 领取国家坐骑结果
    MSG_TELLCOUNTRYBORDERSFIGHT,                                   // 通知边境正在被侵犯
    MSG_TELLCOUNTRYKILLENEMY,                                      // 通知某玩家抵御了敌国入侵
    MSG_COUNTRYFLYTOBORDERSREQ,                                    // 左右捕请求飞往边塞
    MSG_COUNTRYOPERATETOPLAYERREQ,                                 // 禁言请求
    MSG_COUNTRYOPERATETOPLAYERACK,                                 // 禁言回馈
    MSG_COUNTRYTELLOPERATETOPLAYER,                                // 通知被禁言者你被禁言了
    MSG_COUNTRYCONVENERESULT,                                      // 申请国家召集反馈结果 
    MSG_COUNTRYCONVENEREQ,                                         // 请求召集
    MSG_COUNTRYCONVENEACK,                                         // 召集
    MSG_COUNTRYCOUNTRYAPPOINT,                                     // 通知被任命或者被免职
    MSG_COUNTRYTELLCOUNTRYID,                                      // 通知国家信息( 叛国使用 )
    MSG_COUNTRYCHANGEREQ,
    MSG_COUNTRYCHANGEACK,
    MSG_TELLOPERATETOCOUNTRY,
    MSG_COUNTRYTELLWEAK,
	MSG_COUNTRYTELLSTRONG,
    MSG_COUNTRYBATTLEREPLACE,
    MSG_TELLCOUNTRYNAME,
    MSG_CHANGECOUNTRYNAMEREQ,
    MSG_CHANGECOUNTRYNAMEACK,
    MSG_TELLCOUNTRYNAMECHANGE,
    MSG_TELLCOUNTRYSTATUS,
    MSG_UPDATECOUNTRYWARFIGHTKILL,
    MSG_TELLCOUNTRYPLAYERRAISE,
	MSG_DELCOUNTRYOFFICIALREQ,

    GS2CS_COUNTRYNOTICECHANGEREQ = CENTERGAME_COUNTRY_BEGIN,        
    CS2GS_COUNTRYNOTICECHANGEACK,
    GS2CS_COUNTRYQUESTSTATUSCHANGEREQ,
    CS2GS_COUNTRYQUESTSTATUSCHANGEACK,
    GS2CS_COUNTRYOFFICIALAPPOINTREQ,
    GS2CS_COUNTRYOFFICIALRECALLREQ,
	GS2CS_DELCOUNTRYOFFICIALREQ,
    CS2GS_COUNTRYDATECHANGEED,                                       // 国家日期改变了
    CS2GS_COUNTRYQUESTSTATUSSTOP,                                    // 国家发布任务时间到了
    CS2GS_COUNTRYDATALIST,
	CS2GS_COUNTRYWEAKSTRONGTH,
    GS2CS_COUNTRYBATTLERESULT,
    CS2GS_COUNTRYBATTLERESULT,
	GS2CS_ADDCOUNTRYOFFICIAL,
    GS2CS_COUNTRYREQUESTRAISEREQ,
    CS2GS_COUNTRYREQUESTRAISEACK,
    GS2CS_COUNTRYMONEYRAISEED,
	GS2CS_RAISECOUNTRYPLAYERITEM,
    GS2CS_COUNTRYBORDERSFIHGT,
    CS2GS_COUNTRYBORDERSFIHGT,
    GS2CS_COUNTRYOPERATETOPLAYERREQ,
    CS2GS_COUNTRYOPERATETOPLAYERREQ,
    GS2CS_COUNTRYOPERATETOPLAYERACK,
    CS2GS_COUNTRYOPERATETOPLAYERACK,
    GS2CS_COUNTRYCONVENEREQ,
    CS2GS_COUNTRYCONVENEREQ,

    GS2CS_COUNTRYSETOFFICIAL,
    CS2GS_COUNTRYSETOFFICIAL,
    CS2GS_COUNTRYDATAUPDATE,
    GS2CS_COUNTRYCHANGERESULT,
    CS2GS_COUNTRYOFFICIALCHANGE,
	CS2GS_COUNTRYOFFICIALREWARD,
    GS2CS_COUNTRYDATACHANGEREQ,
    CS2GS_TELLWEAKCOUNTRY,
	CS2GS_TELLSTRONGCOUNTRY,
    GS2CS_CHANGECOUNTRYNAMEREQ,
    CS2GS_COUNTRYNAMECHANGE,
    CS2GS_COUNTRYWARSTATUS,
    GS2CS_COUNTRYWARKILLPLAYER,
    CS2GS_COUNTRYWARKILLPLAYER,
    GS2CS_COUNTRYWARSTATUSCHANGE,
    GS2CS_COUNTRYPLAYERCHANGE,
	CS2GS_ADDCOUNTRYOFFICIAL,
    // DB操作
    CS2DB_REQUESTCOUNTRYDATAREQ,                                     // 请求加载国家资源
    DB2CS_REQUESTCOUNTRYDATAACK,                                     // 请求加载国家资源回馈
    CS2DB_COUNTRYDATESAVEREQ,										// 国家信息保存到数据库
	CS2CS_GS2CSCountryBattleReward,									//国战奖励
	CS2DB_COUNTRYOFFICEREQ,
	DB2CS_REQUESTCOUNTRYOFFICECK,
	//CS2CS_GS2CSDeleteCountryBattleReward,							//删除国王战奖励
	MSG_COUNTRYFLYMAP,
	MSG_COUNTRYFLYMAPREQ,
	MSG_TELLCOUNTRYPLAYERRAISEITEM,
	CS2GS_ADDCOUNTRYINFOACK,
	GS2CS_ADDCOUNTRYINFOREQ,
	MSG_ADDCOUNTRYINFOREQ,
	DB2CS_REQUESTCOUNTRYINFOACK,
	CS2DB_REQUESTCOUNTRYINFOREQ,
	CS2GS_REQUESTCOUNTRYINFOACK,
	MSG_LOADCOUNTRYINFOREQ,
	MSG_LOADCOUNTRYINFOACK,

	MSG_COUNTRYBUFFCHANGE,
	MSG_COUNTRYBUFFCHANGEACK,

	MSG_TELLCHANGECOUNTRY  = 3033,
};

struct MsgCountryModule : public Msg
{
    MsgCountryModule()
    {
        SetModuleType( EMessageModule_Country );
    }
};

// 同步国家称号给客户端
struct MsgTellCountryTitleInfo : public MsgCountryModule
{
    MsgTellCountryTitleInfo()
    {
        header.dwType = MSG_TELLCOUNTRYTITLEINFO;
        header.stLength = sizeof( MsgTellCountryTitleInfo );
    }

    GameObjectId stPlayerID;      // 玩家ID
    uint16  stCountryTitle;     // 国家称号
};

// 通知国家任务状态, 如果有, 客户端在活动列表中需要加上这个
struct MsgTellCountryQuestStatus : public MsgCountryModule
{
    MsgTellCountryQuestStatus()
    {
        header.dwType = MSG_TELLCOUNTRYQUERYSTATUS;
        header.stLength = sizeof( MsgTellCountryQuestStatus ) - sizeof( xQuest );
        nCount = 0;
    }
    
    enum EConstDefine
    {
        MaxCount = 4,
    };

    struct QuestStatus
    {
        QuestStatus() : bNeedNotice( false ), n64StartTime( 0 )
        {
        }

        uint8 uchType;          // 任务类型
        __int64 n64StartTime;   // 开始时间
        bool bNeedNotice;       // 是否需要显示通知
    };

    int nCount;
    QuestStatus xQuest[ MaxCount ];

    void AddQuestStatus( QuestStatus& xInfo )
    {
        if ( nCount >= MaxCount )
        { return; }
    
        xQuest[ nCount ] = xInfo;
        ++nCount;
        header.stLength += sizeof( QuestStatus );
    }
};

struct MsgCountryFlyMap : public MsgCountryModule
{
    MsgCountryFlyMap()
    {
        header.dwType = MSG_COUNTRYFLYMAP;
        header.stLength = sizeof( MsgCountryFlyMap );
    }
    uint8 uchType;// 任务类型
};
struct MsgCountryFlyMapReq : public MsgCountryModule
{
    MsgCountryFlyMapReq()
    {
        header.dwType = MSG_COUNTRYFLYMAPREQ;
        header.stLength = sizeof( MsgCountryFlyMapReq );
    }
    uint8 uchType;// 任务类型
};
struct MsgAddCountryInfoReq : public MsgCountryModule
{
    MsgAddCountryInfoReq()
    {
        header.dwType = MSG_ADDCOUNTRYINFOREQ;
        header.stLength = sizeof( MsgAddCountryInfoReq );
    }
    char szNotice[ CountryDefine::MaxCountryInfoLength ];
	int Value;
	__int64 Time;
};
// 请求修改国家公告
struct MsgCountryNoticeChangeReq : public MsgCountryModule
{
    MsgCountryNoticeChangeReq()
    {
        header.dwType = MSG_COUNTRYNOTICECHANGEREQ;
        header.stLength = sizeof( MsgCountryNoticeChangeReq );
    }

    char szNotice[ CountryDefine::MaxNoticeLength ];
};

// 修改国家公告回馈
struct MsgCountryNoticeChangeAck : public MsgCountryModule
{
    MsgCountryNoticeChangeAck()
    {
        header.dwType = MSG_COUNTRYNOTICECHANGEACK;
        header.stLength = sizeof( MsgCountryNoticeChangeAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,    // 修改成功
        ECD_NotRight,       // 没有权限
        ECD_TimeLimit,      // 时间限制
        ECD_NotEnoughMoney, // 国家资金不够
    };

    uint8 uchResult;
};

// 请求发布国家任务
struct MsgQueryCountryInfoReq : public MsgCountryModule
{
    MsgQueryCountryInfoReq()
    {
        header.dwType = MSG_QUERYCOUNTRYINFOREQ;
        header.stLength = sizeof( MsgQueryCountryInfoReq );
    }
};

struct MsgLoadCountryInfoReq : public MsgCountryModule
{
    MsgLoadCountryInfoReq()
    {
        header.dwType = MSG_LOADCOUNTRYINFOREQ;
        header.stLength = sizeof( MsgLoadCountryInfoReq );
    }
};
struct MsgLoadCountryInfoAck : public MsgCountryModule
{
    MsgLoadCountryInfoAck()
    {
        header.dwType = MSG_LOADCOUNTRYINFOACK;
        header.stLength = sizeof( MsgLoadCountryInfoAck );

		memset( Info, 0, sizeof( Info ) );
		memset( Time, 0, sizeof( Time ) );
		memset( values, 0, sizeof( values ) );
		Sum = 0;
		IsEnd = false;
    }
	int Sum;
	char Info[CountryDefine::MaxMsgCountryInfoSum][CountryDefine::MaxCountryInfoLength];
	__int64 Time[CountryDefine::MaxMsgCountryInfoSum];
	int values[CountryDefine::MaxMsgCountryInfoSum];
	bool IsEnd;
};

//zhuxincong 9.18 更新国家信息，比如说钱，贡品
struct MsgUpdateCountryDate : public MsgCountryModule
{
	MsgUpdateCountryDate()
	{
		header.dwType = MSG_UPDATECOUNTRYINFOACK;
		header.stLength = sizeof(MsgUpdateCountryDate);
	}

	int nValue;
	char chType;

};


// 通知国家任务发布状态
struct MsgQueryCountryInfoAck : public MsgCountryModule
{
    MsgQueryCountryInfoAck()
    {
        header.dwType = MSG_QUERYCOUNTRYINFOACK;
        header.stLength = sizeof( MsgQueryCountryInfoAck );
    }

    struct QuestStatus
    {
        QuestStatus() : uchCount( 0 ), nLeftTime( 0 ) {}

        uint8 uchCount;     // 任务开放次数 ( 0 未开放,  1 = 开放 )
        uint32 nLeftTime;   // 剩余多少时间(  单位: 秒 0 = 已开放, 已经过了 , 其他 开放中 )
    };

    char szName[ CountryDefine::MaxCountryLength ];         // 名字
    char szNotice[ CountryDefine::MaxNoticeLength ];        //  公告
    char szOfficial[ CountryDefine::Position_Max ][ CountryDefine::MaxNameLength ];   // 官员名称
    uint32 nMoney;          // 国家资金 ( 玩家点查询国家资源时候, 不再发 )
	uint32 nTribute;
    uint32 nCountryRight;   // 国家权力
	uint32 nStrongth;		//国家实力
    QuestStatus xQuestStatus[ CountryDefine::QuestType_Max ];       // 4个发布任务
	
	uint8 szsexID[CountryDefine::Position_Max];
	uint16 szfaceID[CountryDefine::Position_Max];
	uint16 szheaderID[CountryDefine::Position_Max];
	uint16 szprofession[CountryDefine::Position_Max];
};

// 请求发布国家任务
struct MsgCountryQuestStatusChangeReq : public MsgCountryModule
{
    MsgCountryQuestStatusChangeReq()
    {
        header.dwType = MSG_COUNTRYQUESTSTATECHANGEREQ;
        header.stLength = sizeof( MsgCountryQuestStatusChangeReq );
    }

    uint8 uchQuestType;
};

// 发布国家任务回馈
struct MsgCountryQuestStatusChangeAck : public MsgCountryModule
{
    MsgCountryQuestStatusChangeAck()
    {
        header.dwType = MSG_COUNTRYQUESTSTATECHANGEACK;
        header.stLength = sizeof( MsgCountryQuestStatusChangeAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,    // 成功( 收发成功, 按钮变灰 )
        ECD_NotRight,       // 没有权限
        ECD_Already,        // 已经发布过了
        ECD_NotEnoughMoney,
    };

    uint8 uchQuestType;
    uint8 uchResult;
};

// 任命国家官员职位
struct MsgCountryOfficialAppointReq : public MsgCountryModule
{
    MsgCountryOfficialAppointReq()
    {
        header.dwType = MSG_COUNTRYOFFICIALAPPOINTREQ;
        header.stLength = sizeof( MsgCountryOfficialAppointReq );
    }

    uint8 uchPosition;      // 任命什么职位
    char szName[ CountryDefine::MaxNameLength ];   // 任命者名字
};


// 任命国家官员回馈
struct MsgCountryOfficialAppointAck : public MsgCountryModule
{
    MsgCountryOfficialAppointAck()
    {
        header.dwType = MSG_COUNTRYOFFICIALAPPOINTACK;
        header.stLength = sizeof( MsgCountryOfficialAppointAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,    // 成功( 收发成功, 按钮变灰 )
        ECD_NotRight,       // 没有权限
        ECD_NotCountryMember, // 不是本国成员不能任命
        ECD_NotOnline,      // 不在线
        ECD_LevelLess,      // 等级不足45级
        ECD_Already,        // 已经有职位, 不能重复任命
		ECD_NOGuild,        //没有公会
		ECD_NoItem,			//没有物品
    };

    uint8 uchResult;
    uint8 uchPosition;      // 任命什么职位
    uint32 nPlayerID;       // 被任命的玩家ID
};

// 免除国家官员职位
struct MsgCountryOfficialRecallReq : public MsgCountryModule
{
    MsgCountryOfficialRecallReq()
    {
        header.dwType = MSG_COUNTRYOFFICIALRECALLREQ;
        header.stLength = sizeof( MsgCountryOfficialRecallReq );
    }

    uint8 uchPosition;       // 免除什么职位
};

struct MsgDelCountryOfficialReq : public MsgCountryModule //自己辞去官职
{
    MsgDelCountryOfficialReq()
    {
        header.dwType = MSG_DELCOUNTRYOFFICIALREQ;
        header.stLength = sizeof( MsgDelCountryOfficialReq );
    }
};


// 免除国家官员职位回馈
struct MsgCountryOfficialRecallAck : public MsgCountryModule
{
    MsgCountryOfficialRecallAck()
    {
        header.dwType = MSG_COUNTRYOFFICIALRECALLACK;
        header.stLength = sizeof( MsgCountryOfficialRecallAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotRight,   // 没有权限
		ECD_DelSuccess,
    };


    uint8 uchResult;
    uint8 uchPosition;       // 免除什么职位
};

// 通知国家发布任务到时间了
struct MsgCountryQuestStatusStop : public MsgCountryModule
{
    MsgCountryQuestStatusStop()
    {
        header.dwType = MSG_COUNTRYQUESTSTATUSSTOP;
        header.stLength = sizeof( MsgCountryQuestStatusStop );
    }

    uint8 uchQuestType;    
};

// 杀死国家官员
struct MsgTellCountryKillPosition : public MsgCountryModule
{
    MsgTellCountryKillPosition()
    {
        header.dwType = MSG_TELLCOUNTRYKILLPOSITION;
        header.stLength = sizeof( MsgTellCountryKillPosition );
    }

    uint8 uchKillerCountry;                  // 杀人者国家  
    char szKillerName[ CountryDefine::MaxNameLength ];   // 杀人者名字

    uint8 uchBeKilledCountry;                 // 被杀者国家
    uint8 uchBeKilledPosition;                // 被杀者国家职位
    char szBeKilledName[ CountryDefine::MaxNameLength ];  // 被杀者名字
};

// 客户端请求募集国家资金
struct MsgCountryRequestRaiseReq : public MsgCountryModule
{
    MsgCountryRequestRaiseReq()
    {
        header.dwType = MSG_COUNTRYREQUESTRAISEREQ;
        header.stLength = sizeof( MsgCountryRequestRaiseReq );
    }
};

// 回馈给申请者
struct MsgCountryRequestRaiseAck : public MsgCountryModule
{
    MsgCountryRequestRaiseAck()
    {
        header.dwType = MSG_COUNTRYREQUESTRAISEACK;
        header.stLength = sizeof( MsgCountryRequestRaiseAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotRight,       // 没有权限
        ECD_TimeLimit,      // 一天只能募集一次
    };

    uint8 uchResult;
};

// 服务器发送募捐给所有玩家, 客户端判断等级
struct MsgCountryRaiseToPlayerReq : public MsgCountryModule
{
    MsgCountryRaiseToPlayerReq()
    {
        header.dwType = MSG_COUNTRYRAISETOPLAYERREQ;
        header.stLength = sizeof( MsgCountryRaiseToPlayerReq );
    }
};

// 玩家募捐
struct MsgCountryRaiseToPlayerAck : public MsgCountryModule
{
    MsgCountryRaiseToPlayerAck()
    {
        header.dwType = MSG_COUNTRYRAISETOPLAYERACK;
        header.stLength = sizeof( MsgCountryRaiseToPlayerAck );
    }

    uint32 nMoney;      // 捐的金钱
};

// 募集
struct MsgCountryRaiseTellPlayer : public MsgCountryModule
{
    MsgCountryRaiseTellPlayer()
    {
        header.dwType = MSG_COUNTRYRAISETELLPLAYER;
        header.stLength = sizeof( MsgCountryRaiseTellPlayer );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_LevelLess,      // 等级不足
        ECD_NotEnoughMoney, // 金钱不足
        ECD_ErrorRaiseMoney,// 募集金钱超过最大值
        ECD_NotRaiseTime,   // 不在募集时段 不能募集
        ECD_CountryMoneyMax,// 国家资金已经最大了
    };

    uint8 uchResult;
};

// 募集全国广播
struct MsgTellCountryPlayerRaise : public MsgCountryModule
{
    MsgTellCountryPlayerRaise()
    {
        header.dwType = MSG_TELLCOUNTRYPLAYERRAISE;
        header.stLength = sizeof( MsgTellCountryPlayerRaise );

        memset( szName, 0, sizeof( szName ) );
    }

    char szName[ CountryDefine::MaxNameLength ];    // 玩家
    int nMoney;     // 捐献了多少钱
};

struct MsgTellCountryPlayerRaiseItem : public MsgCountryModule
{
    MsgTellCountryPlayerRaiseItem()
    {
        header.dwType = MSG_TELLCOUNTRYPLAYERRAISEITEM;
        header.stLength = sizeof( MsgTellCountryPlayerRaiseItem );

        memset( szName, 0, sizeof( szName ) );
    }
    char szName[ CountryDefine::MaxNameLength ];    // 玩家
    unsigned short CountryID;
};

// 领取国家坐骑回馈
struct MsgCountryReceiveMountAck : public MsgCountryModule
{
    MsgCountryReceiveMountAck()
    {
        header.dwType = MSG_COUNTRYRECEIVEMOUNTACK;
        header.stLength = sizeof( MsgCountryReceiveMountAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotRight,      // 没有权限不能领取
        ECD_Alreadly,      // 已经领取了
        ECD_NotHaveMount,  // 没有对应你等级的马
        ECD_MaxCount,      // 马携带数量已经最大了
    };

    uint8 uchResult;
};

// 记录国家边塞战斗的坐标( 客户也记录, 记录队列长队在CountryConfig设置 )
struct MsgTellCountryBordersFight : public MsgCountryModule
{
    MsgTellCountryBordersFight()
    {
        header.dwType = MSG_TELLCOUNTRYBORDERSFIGHT;
        header.stLength = sizeof( MsgTellCountryBordersFight );
    }

    uint16 ustMapID;
    uint16 ustPosX;
    uint16 ustPosY;
};

// 通知客户端 某某某抵御了外敌
struct MsgTellCountryKillEnemy : public MsgCountryModule
{
    MsgTellCountryKillEnemy()
    {
        header.dwType = MSG_TELLCOUNTRYKILLENEMY;
        header.stLength = sizeof( MsgTellCountryKillEnemy );
    }
    
    uint16 ustMapID;
    char szPlayerName[ CountryDefine::MaxNameLength ];
};

// 左右捕 请求飞往边塞
struct MsgCountryFlyToBordersReq : public MsgCountryModule
{
    MsgCountryFlyToBordersReq()
    {
        header.dwType = MSG_COUNTRYFLYTOBORDERSREQ;
        header.stLength = sizeof( MsgCountryFlyToBordersReq );
    }
    
    uint16 ustMapID;
    uint16 ustPosX;
    uint16 ustPosY;
};

// 客户端请求操作
struct MsgCountryOperateToPlayerReq : public MsgCountryModule
{
    MsgCountryOperateToPlayerReq()
    {
        header.dwType = MSG_COUNTRYOPERATETOPLAYERREQ;
        header.stLength = sizeof( MsgCountryOperateToPlayerReq );
        memset( szName, 0, sizeof( szName ) );
    }
    
    enum EConstDefine
    {
        Operate_BanSpeak = 0,        // 禁言
        Operate_Chain,               // 囚禁
        Operate_Remit,               // 赦免
    };

    uint8 uchOperate;
    char szName[ CountryDefine::MaxNameLength ];
};

// 客户端操作回馈
struct MsgCountryOperateToPlayerAck : public MsgCountryModule
{
    MsgCountryOperateToPlayerAck()
    {
        header.dwType = MSG_COUNTRYOPERATETOPLAYERACK;
        header.stLength = sizeof( MsgCountryOperateToPlayerAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotRight,           // 没有权限
        ECD_TimeLimit,          // 一天只能3次
        ECD_NotEnoughMoney,     // 没有足够的金钱
        ECD_NotOnLine,          // 不在线
        ECD_NotSameCountry,     // 不是本国国民
        ECD_NeedNotRemit,       // 不需要赦免
        ECD_CountryBattle,      // 国王, 青龙, 朱雀争夺战期间不能使用
    };

    uint8 uchOperate;
    uint8 uchResult;
};

// 通知被操作者 你被干嘛了
struct MsgCountryTellOperateToPlayer : public MsgCountryModule
{
    MsgCountryTellOperateToPlayer()
    {
        header.dwType = MSG_COUNTRYTELLOPERATETOPLAYER;
        header.stLength = sizeof( MsgCountryTellOperateToPlayer );
    }

    uint8 uchOperate;
};

// 通知全国某人被干嘛了( 打一个系统公告 )
struct MsgTellOperateToCountry : public MsgCountryModule
{
    MsgTellOperateToCountry()
    {
        header.dwType = MSG_TELLOPERATETOCOUNTRY;
        header.stLength = sizeof( MsgTellOperateToCountry );
    }

    char szName[ CountryDefine::MaxNameLength ];    // 
    uint8 uchOperate;
};

// 申请国家召集结果
struct MsgCountryConveneResult : public MsgCountryModule
{
    MsgCountryConveneResult()
    {
        header.dwType = MSG_COUNTRYCONVENERESULT;
        header.stLength = sizeof( MsgCountryConveneResult );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotRight,           // 没有权限
        ECD_TimeLimit,          // 一天只能3次
        ECD_NotEnoughMoney,     // 没有足够的金钱
        ECD_EctypeMap,          // 副本不能国家召集
    };

    uint8 uchResult;
};

// 服务器给客户端召集请求
struct MsgCountryConveneReq : public MsgCountryModule
{
    MsgCountryConveneReq()
    {
        header.dwType = MSG_COUNTRYCONVENEREQ;
        header.stLength = sizeof( MsgCountryConveneReq );
    }

    uint32 nOfficialID;  // 召集人, ( 如果是自己 就不要弹出框 )
};

// 是否同意召集 ( 不同意不用回消息 )
struct MsgCountryConveneAck : public MsgCountryModule
{
    MsgCountryConveneAck()
    {
        header.dwType = MSG_COUNTRYCONVENEACK;
        header.stLength = sizeof( MsgCountryConveneAck );
    }
};

struct MsgCountryTellAppoint : public MsgCountryModule
{
    MsgCountryTellAppoint()
    {
        header.dwType = MSG_COUNTRYCOUNTRYAPPOINT;
        header.stLength = sizeof( MsgCountryTellAppoint );
    }

    enum EConstDefine
    {
        ECD_Appoint = 0, // 被任命
        ECD_Recall,      // 被免职
    };

    uint8 uchType;       // 被任命 或者被免职
    uint8 uchPosition;   // 职位
};

// 通知国家ID
struct MsgCountryTellCountryID : public MsgCountryModule
{
    MsgCountryTellCountryID()
    {
        header.dwType = MSG_COUNTRYTELLCOUNTRYID;
        header.stLength = sizeof( MsgCountryTellCountryID );
    }
    /*uint8 stID;*/
    uint8 uchCountry;
};

// 请求改变国家
struct MsgCountryChangeReq : public MsgCountryModule
{
    MsgCountryChangeReq()
    {
        header.dwType = MSG_COUNTRYCHANGEREQ;
        header.stLength = sizeof( MsgCountryChangeReq );
    }

    uint8 uchCountryID;
};

// 回馈国家改变
struct MsgCountryChangeAck : public MsgCountryModule
{
    MsgCountryChangeAck()
    {
        header.dwType = MSG_COUNTRYCHANGEACK;
        header.stLength = sizeof( MsgCountryChangeAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_HaveTeam,       // 叛国不能有队伍
        ECD_HaveGuild,      // 叛国不能有帮派
        ECD_SameCountry,    // 相同国家
        ECD_ErrorCountry,   // 错误的国家ID
        ECD_NotEnoughMoney, // 没有足够的金钱
        ECD_HaveMarriage,   // 有夫妻关系不能改变国际
        ECD_HaveStudent,    // 有徒弟
        ECD_HaveTeacher,    // 有师傅
        ECD_TimeLimit,      // 一周只能改变一次国籍
		ECD_Item,			// 叛国的物品不足够
		ECD_HaveOff,		// 有官职
		ECD_MaxLevel,		//
		ECD_MinLevel,		//
		ECD_QuestStates		//
    };

    uint8 uchResult;
};

// 通知本国玩家 你的国家已经变成弱国了
struct MsgCountryTellWeak : public MsgCountryModule
{
    MsgCountryTellWeak()
    {
        header.dwType = MSG_COUNTRYTELLWEAK;
        header.stLength = sizeof( MsgCountryTellWeak );
    }

    uint8 uchWeakCountryID;     
};

struct MsgCountryTellStrong : public MsgCountryModule
{
    MsgCountryTellStrong()
    {
        header.dwType = MSG_COUNTRYTELLSTRONG;
        header.stLength = sizeof( MsgCountryTellStrong );
    }

    uint8 uchStrongCountryID;     
};

// 通知帮派帮主, 你的帮派在国家争夺战报名中被其他帮派顶替了
struct MsgCountryBattleReplace : public MsgCountryModule
{
    MsgCountryBattleReplace()
    {
        header.dwType = MSG_COUNTRYBATTLEREPLACE;
        header.stLength = sizeof( MsgCountryBattleReplace );
    }
    
    uint8 uchBattleType;
};

// 通知国家国号
struct MsgTellCountryName : public MsgCountryModule
{
    MsgTellCountryName()
    {
        header.dwType = MSG_TELLCOUNTRYNAME;
        header.stLength = sizeof( MsgTellCountryName );

        memset( szName, 0, sizeof( szName ) );
    }

    char szName[ CountryDefine::Country_Max ][ CountryDefine::MaxCountryLength ];      // 国家名字
};

// 请求修改国家名字
struct MsgChangeCountryNameReq : public MsgCountryModule
{
    MsgChangeCountryNameReq()
    {
        header.dwType = MSG_CHANGECOUNTRYNAMEREQ;
        header.stLength = sizeof( MsgChangeCountryNameReq );
    }

    char szName[ CountryDefine::MaxCountryLength ];      // 国家名字
};

// 服务器回应修改国家名字
struct MsgChangeCountryNameAck : public MsgCountryModule
{
    MsgChangeCountryNameAck()
    {
        header.dwType = MSG_CHANGECOUNTRYNAMEACK;
        header.stLength = sizeof( MsgChangeCountryNameAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotHaveRight,  // 没有权限
        ECD_ChangeOnce,    // 只能修改一次名字
        ECD_ErrorName,     // 错误的国家名字
    };

    unsigned char uchResult;
};

// 通知全世界某国的国家名字改变了
struct MsgTellCountryNameChange : public MsgCountryModule
{
    MsgTellCountryNameChange()
    {
        header.dwType = MSG_TELLCOUNTRYNAMECHANGE;
        header.stLength = sizeof( MsgTellCountryNameChange );
    }

    unsigned char uchCountryID; // 国家ID
    char szPlayer[ CountryDefine::MaxNameLength ];       // 国王名字
    char szName[ CountryDefine::MaxCountryLength ];     // 国家名字
};

// 通知全世界国战状态
struct MsgTellCountryWarStatus : public MsgCountryModule
{
    MsgTellCountryWarStatus()
    {
        header.dwType = MSG_TELLCOUNTRYSTATUS;
        header.stLength = sizeof( MsgTellCountryWarStatus );
    }

    unsigned char uchStatus;
};

// 更新国家杀人信息
struct MsgUpdateCountryWarFightKill : public MsgCountryModule
{
    MsgUpdateCountryWarFightKill()
    {
        header.dwType = MSG_UPDATECOUNTRYWARFIGHTKILL;
        header.stLength = sizeof( MsgUpdateCountryWarFightKill );
    }

    uint32 nKillCount[ CountryDefine::Country_Max ];    // 3个国家的杀人情况
};

/////////////////////////////////////////////////////////////////////////////////
// 服务器间通信
////////////////////////////////////////////////////////////////////////////////
struct GS2CSCountryNoticeChangeReq : public MsgCountryModule
{
    GS2CSCountryNoticeChangeReq()
    {
        header.dwType = GS2CS_COUNTRYNOTICECHANGEREQ;
        header.stLength = sizeof( GS2CSCountryNoticeChangeReq );
    }

    uint8 uchCountryID;
    uint32 nPlayerID;
    char szNotice[ CountryDefine::MaxNoticeLength ];
};

struct CS2GSCountryNoticeChangeAck : public MsgCountryModule
{
    CS2GSCountryNoticeChangeAck()
    {
        header.dwType = CS2GS_COUNTRYNOTICECHANGEACK;
        header.stLength = sizeof( CS2GSCountryNoticeChangeAck );
    }

    uint8 uchCountryID;
    uint32 nPlayerID;
    char szNotice[ CountryDefine::MaxNoticeLength ];
};

struct CS2GSAddCountryInfoAck : public MsgCountryModule
{
    CS2GSAddCountryInfoAck()
    {
        header.dwType = CS2GS_ADDCOUNTRYINFOACK;
        header.stLength = sizeof( CS2GSAddCountryInfoAck );
    }
	uint8 uchCountryID;
    char szNotice[ CountryDefine::MaxCountryInfoLength ];
	__int64 Time;
	int Value;
};

struct CS2GSRequestCountryInfoAck : public MsgCountryModule
{
	CS2GSRequestCountryInfoAck()
    {
        header.dwType = CS2GS_REQUESTCOUNTRYINFOACK;
        header.stLength = sizeof( CS2GSRequestCountryInfoAck );
		memset( Info, 0, sizeof( Info ) );
		memset( Time, 0, sizeof( Time ) );
		memset( CountryID, 0, sizeof( CountryID ) );
		memset( values, 0, sizeof( values ) );
		Sum = 0;
		IsEnd = false;
    }
	int Sum;
	char Info[CountryDefine::MaxMsgCountryInfoSum][CountryDefine::MaxCountryInfoLength];
	uint8 CountryID[CountryDefine::MaxMsgCountryInfoSum];
	__int64 Time[CountryDefine::MaxMsgCountryInfoSum];
	int values[CountryDefine::MaxMsgCountryInfoSum];
	bool IsEnd;
};


struct GS2CSAddCountryInfoReq : public MsgCountryModule
{
    GS2CSAddCountryInfoReq()
    {
        header.dwType = GS2CS_ADDCOUNTRYINFOREQ;
        header.stLength = sizeof( GS2CSAddCountryInfoReq );
    }
	uint8 uchCountryID;
    char szNotice[ CountryDefine::MaxCountryInfoLength ];
	int Value;
	__int64 Time;
};

struct GS2CSCountryQuestStatusChangeReq : public MsgCountryModule
{
    GS2CSCountryQuestStatusChangeReq()
    {
        header.dwType = GS2CS_COUNTRYQUESTSTATUSCHANGEREQ;
        header.stLength = sizeof( GS2CSCountryQuestStatusChangeReq );
    }

    uint8 uchCountryID;
    uint8 uchQuestType;
    uint32 nPlayerID;
};

struct CS2GSCountryQuestStatusChangeAck : public MsgCountryModule
{
    CS2GSCountryQuestStatusChangeAck()
    {
        header.dwType = CS2GS_COUNTRYQUESTSTATUSCHANGEACK;
        header.stLength = sizeof( CS2GSCountryQuestStatusChangeAck );
    }

    uint8 uchCountryID;
    uint8 uchQuestType;
    uint32 nPlayerID;
};

struct GS2CSCountryOfficialAppointReq : public MsgCountryModule
{
    GS2CSCountryOfficialAppointReq()
    {
        header.dwType = GS2CS_COUNTRYOFFICIALAPPOINTREQ;
        header.stLength = sizeof( GS2CSCountryOfficialAppointReq );

		sexID = -1;
		faceID = -1;
		headerID = -1;
		professionID = -1;
    }

    uint8 uchCountryID;
    uint32 nOfficialID;     // 任命者ID

    uint8 uchPosition;      // 任命的职位
    uint32 nPlayerID;       // 被任命的ID

	uint8	sexID;
	uint16  faceID;
	uint16  headerID;
	uint16  professionID;
};

struct GS2CSCountryOfficialRecallReq : public MsgCountryModule
{
    GS2CSCountryOfficialRecallReq()
    {
        header.dwType = GS2CS_COUNTRYOFFICIALRECALLREQ;
        header.stLength = sizeof( GS2CSCountryOfficialRecallReq );
    }

    uint8 uchCountryID;
    uint32 nOfficialID;     
    uint8 uchPosition;      // 免除的职位
};

struct GS2CSDelCountryOfficialReq : public MsgCountryModule
{
    GS2CSDelCountryOfficialReq()
    {
        header.dwType = GS2CS_DELCOUNTRYOFFICIALREQ;
        header.stLength = sizeof( GS2CSDelCountryOfficialReq );
    }
    uint8 uchCountryID; 
    uint8 uchPosition;      // 免除的职位
};

struct CS2GSCountryDateChangeed : public MsgCountryModule
{
    CS2GSCountryDateChangeed()
    {
        header.dwType = CS2GS_COUNTRYDATECHANGEED;
        header.stLength = sizeof( CS2GSCountryDateChangeed );
    }
    uint8 uchCountryID;
};

struct CS2GSCountryQuestStatusStop : public MsgCountryModule
{
    CS2GSCountryQuestStatusStop()
    {
        header.dwType = CS2GS_COUNTRYQUESTSTATUSSTOP;
        header.stLength = sizeof( CS2GSCountryQuestStatusStop );
    }
    
    uint8 uchCountryID;
    uint8 uchQuestType;
};


//ZHUXINCONG
struct GS2CSCountryBattleReward:public MsgCountryModule
{
	GS2CSCountryBattleReward()
	{
		header.dwType = CS2CS_GS2CSCountryBattleReward;
		header.stLength = sizeof(GS2CSCountryBattleReward);
		oldID = 0;
		newID = 0;
		nCampBattle = 0;
	}
	int nLevel;
	int nPlayerID;
	SCharItem CItem;
	int nPosition;
    int nGuidID;
	int oldID;
	int newID;
	int nCampBattle;
	char szName[ CountryDefine::MaxNameLength ];
};

struct GS2CSCountryBattleResult : public MsgCountryModule
{
    GS2CSCountryBattleResult()
    {
        header.dwType = GS2CS_COUNTRYBATTLERESULT;
        header.stLength = sizeof( GS2CSCountryBattleResult );
    }

    uint8 uchCountryID;

    uint8 uchBattleType;
    uint8 uchWinType;
    uint32 nGuildID;
	uint32 nLoseGuildID;
	uint32 nCampBattle;
};

struct GS2CSAddCountryOfficial : public MsgCountryModule
{
    GS2CSAddCountryOfficial()
    {
        header.dwType = GS2CS_ADDCOUNTRYOFFICIAL;
        header.stLength = sizeof( GS2CSAddCountryOfficial );

		sexID = -1;
		faceID = -1;
		headerID = -1;
		professionID = -1;
    }

    uint8 uchCountryID;
	uint8 sexID;
	uint16 faceID;
	uint16 headerID;
	uint32 nPlayerID;
	uint8  position;
	uint16 professionID;
	char szName[ CountryDefine::MaxNameLength ];
};

struct CS2GSCountryBattleResult : public MsgCountryModule
{
    CS2GSCountryBattleResult()
    {
        header.dwType = CS2GS_COUNTRYBATTLERESULT;
        header.stLength = sizeof( CS2GSCountryBattleResult );
    }

    uint8 uchCountryID;

    uint8 uchBattleType;
    uint8 uchWinType;
    uint32 nGuildID;
	uint32 nLoseGuildID;
	uint32 nCampBattle;
};

struct GS2CSCountryRequestRaiseReq : public MsgCountryModule
{
    GS2CSCountryRequestRaiseReq()
    {
        header.dwType = GS2CS_COUNTRYREQUESTRAISEREQ;
        header.stLength = sizeof( GS2CSCountryRequestRaiseReq );
    }
    
    uint8 uchCountryID;
    uint32 nPlayerID;
};

struct CS2GSCountryRequestRaiseAck : public MsgCountryModule
{
    CS2GSCountryRequestRaiseAck()
    {
        header.dwType = CS2GS_COUNTRYREQUESTRAISEACK;
        header.stLength = sizeof( CS2GSCountryRequestRaiseAck );
    }

    uint8 uchCountryID;
    uint32 nPlayerID;
};

struct GS2CSCountryMoneyRaiseed : public MsgCountryModule
{
    GS2CSCountryMoneyRaiseed()
    {
        header.dwType = GS2CS_COUNTRYMONEYRAISEED;
        header.stLength = sizeof( GS2CSCountryMoneyRaiseed );

		OperateType = 1;
    }
	int nType;// 默认为0 为金钱 1为贡品
    uint8 uchCountryID;
    int nMoney;
	int OperateType; // 1+,2-,3set,只有ntype=1才启动set，其他的操作全部为加
};

struct GS2CSRaiseCountryPlayerItem : public MsgCountryModule
{
    GS2CSRaiseCountryPlayerItem()
    {
        header.dwType = GS2CS_RAISECOUNTRYPLAYERITEM;
        header.stLength = sizeof( GS2CSRaiseCountryPlayerItem );

		
    }
	uint32 ItemID;
	uint32 PlayerID;
	SCharItem CItem;
	char szName[dr_MaxPlayerName];
};

struct GS2CSCountryBordersFight : public MsgCountryModule
{
    GS2CSCountryBordersFight()
    {
        header.dwType = GS2CS_COUNTRYBORDERSFIHGT;
        header.stLength = sizeof( GS2CSCountryBordersFight );
    }

    unsigned uchCountryID;

    uint16 ustMapID;
    int nPosX;
    int nPosY;
};

struct CS2GSCountryBordersFight : public MsgCountryModule
{
    CS2GSCountryBordersFight()
    {
        header.dwType = CS2GS_COUNTRYBORDERSFIHGT;
        header.stLength = sizeof( CS2GSCountryBordersFight );
    }

    unsigned uchCountryID;

    uint16 ustMapID;
    int nPosX;
    int nPosY;
};

struct GS2CSCountryOperateToPlayerReq : public MsgCountryModule
{
    GS2CSCountryOperateToPlayerReq()
    {
        header.dwType = GS2CS_COUNTRYOPERATETOPLAYERREQ;
        header.stLength = sizeof( GS2CSCountryOperateToPlayerReq );
    }

    uint8 uchCountryID;
    uint8 uchOperate;
    uint32 nPlayerID;
    char szName[ CountryDefine::MaxNameLength ];
};

struct CS2GSCountryOperateToPlayerReq : public MsgCountryModule
{
    CS2GSCountryOperateToPlayerReq()
    {
        header.dwType = CS2GS_COUNTRYOPERATETOPLAYERREQ;
        header.stLength = sizeof( CS2GSCountryOperateToPlayerReq );
    }

    uint8 uchCountryID;
    uint8 uchOperate;
    uint32 nOfficialID;
    uint32 nPlayerID;
};

struct GS2CSCountryOperateToPlayerAck : public MsgCountryModule
{
    GS2CSCountryOperateToPlayerAck()
    {
        header.dwType = GS2CS_COUNTRYOPERATETOPLAYERACK;
        header.stLength = sizeof( GS2CSCountryOperateToPlayerAck );
    }

    uint8 uchCountryID;
    uint8 uchOperate;
    uint32 nOfficialID;
};

struct CS2GSCountryOperateToPlayerAck : public MsgCountryModule
{
    CS2GSCountryOperateToPlayerAck()
    {
        header.dwType = CS2GS_COUNTRYOPERATETOPLAYERACK;
        header.stLength = sizeof( CS2GSCountryOperateToPlayerAck );
    }

    uint8 uchCountryID;
    uint8 uchOperate;
    uint32 nOfficialID;
};

struct GS2CSCountryConveneReq : public MsgCountryModule
{
    GS2CSCountryConveneReq()
    {
        header.dwType = GS2CS_COUNTRYCONVENEREQ;
        header.stLength = sizeof( GS2CSCountryConveneReq );
    }

    uint8 uchCountryID;
    uint32 nOfficialID;
    uint16 ustLevel;     // 地图的等级

    uint32 nMapID;
    float fX;
    float fY;
};

struct CS2GSCountryConveneReq : public MsgCountryModule
{
    CS2GSCountryConveneReq()
    {
        header.dwType = CS2GS_COUNTRYCONVENEREQ;
        header.stLength = sizeof( CS2GSCountryConveneReq );
    }

    uint8 uchCountryID;
    uint32 nOfficialID;
    uint16 ustLevel;     // 地图的等级

    uint32 nMapID;
    float fX;
    float fY;
};

struct GS2CSCountrySetOfficial : public MsgCountryModule
{
    GS2CSCountrySetOfficial()
    {
        header.dwType = GS2CS_COUNTRYSETOFFICIAL;
        header.stLength = sizeof( GS2CSCountrySetOfficial );

		sexID = -1;
		faceID = -1;
		headerID = -1;
		professionID = -1;
    }

    uint8 uchCountryID;
    uint8 uchPosition;

    uint32 nGuildID;
    uint32 nPlayerID;
	
	uint16 faceID;
	uint16 headerID;
	uint8  sexID;
	uint16 professionID;

    char szName[ CountryDefine::MaxNameLength ];
};

struct CS2GSCountrySetOfficial : public MsgCountryModule
{
    CS2GSCountrySetOfficial()
    {
        header.dwType = CS2GS_COUNTRYSETOFFICIAL;
        header.stLength = sizeof( CS2GSCountrySetOfficial );

		sexID = -1;
		faceID = -1;
		headerID = -1;
		professionID = -1;
    }

    uint8 uchCountryID;
    uint8 uchPosition;
    uint32 nGuildID;
    uint32 nPlayerID;

	uint16 faceID;
	uint16 headerID;
	uint8  sexID;
	uint16 professionID;

    char szName[ CountryDefine::MaxNameLength ];
};


struct CS2GSCountryDataUpdate : public MsgCountryModule
{
    CS2GSCountryDataUpdate()
    {
        header.dwType = CS2GS_COUNTRYDATAUPDATE;
        header.stLength = sizeof( CS2GSCountryDataUpdate );
    }

    uint8 uchCountryID;

    uint8 uchUpdateType;
    __int64 n64Value;
};

struct GS2CSCountryChangeResult : public MsgCountryModule
{
    GS2CSCountryChangeResult()
    {
        header.dwType = GS2CS_COUNTRYCHANGERESULT;
        header.stLength = sizeof( GS2CSCountryChangeResult );
    }

    unsigned int nPlayerID;
    uint8 uchCountryID;
};

struct CS2GSCountryOfficialChange : public MsgCountryModule
{
    CS2GSCountryOfficialChange()
    {
        header.dwType = CS2GS_COUNTRYOFFICIALCHANGE;
        header.stLength = sizeof( CS2GSCountryOfficialChange );

        nPlayerID = 0;
        memset( szName, 0, sizeof( szName ) );

		sexID = -1;
		faceID = -1;
		headerID = -1;
		professionID = -1;
    }

    uint8 uchCountryID;
    uint8 uchPosition;      // 职位

	uint8 sexID;
	uint16 faceID;
	uint16 headerID;
	uint16 professionID;

    unsigned int nPlayerID;
    char szName[ CountryDefine::MaxNameLength ];
};

struct CS2GSCountryOfficialReward : public MsgCountryModule
{
	CS2GSCountryOfficialReward()
    {
        header.dwType = CS2GS_COUNTRYOFFICIALREWARD;
        header.stLength = sizeof( CS2GSCountryOfficialReward );

        nPlayerID = 0;
        uchPosition = 0;
    }
    uint8 uchPosition;      // 职位
    unsigned int nPlayerID;
	char szName[ CountryDefine::MaxNameLength ];
};	

struct CS2GSAddCountryOfficial : public MsgCountryModule
{
    CS2GSAddCountryOfficial()
    {
        header.dwType = CS2GS_ADDCOUNTRYOFFICIAL;
        header.stLength = sizeof( CS2GSAddCountryOfficial );

        nPlayerID = 0;
    }

    uint8 uchCountryID;
    uint8 uchPosition;      // 职位
    unsigned int nPlayerID;
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//数据库存取操作
struct CS2DBRequestCountryDataReq : public MsgCountryModule
{
    CS2DBRequestCountryDataReq()
    {
        header.dwType = CS2DB_REQUESTCOUNTRYDATAREQ;
        header.stLength = sizeof( CS2DBRequestCountryDataReq );
    }
};

struct CS2DBRequestCountryInfoReq : public MsgCountryModule
{
    CS2DBRequestCountryInfoReq()
    {
        header.dwType = CS2DB_REQUESTCOUNTRYINFOREQ;
        header.stLength = sizeof( CS2DBRequestCountryInfoReq );
    }
	char Info[CountryDefine::MaxCountryInfoLength];
	uint8 CountryID;
	int Value;
	__int64 Time;
};

struct DB2CSRequestCountryDataAck : public MsgCountryModule
{
    DB2CSRequestCountryDataAck()
    {
        header.dwType = DB2CS_REQUESTCOUNTRYDATAACK;
        header.stLength = sizeof( DB2CSRequestCountryDataAck );
		memset( PlayerSum, 0, sizeof( PlayerSum ) );
    }
	unsigned int PlayerSum[CountryDefine::Country_Max];//所有国家的人数
    CountryData xData[ CountryDefine::Country_Max ];
};

struct DB2CSRequestCountryInfoAck : public MsgCountryModule
{
	DB2CSRequestCountryInfoAck()
    {
        header.dwType = DB2CS_REQUESTCOUNTRYINFOACK;
        header.stLength = sizeof( DB2CSRequestCountryInfoAck );
		memset( Info, 0, sizeof( Info ) );
		memset( Time, 0, sizeof( Time ) );
		memset( CountryID, 0, sizeof( CountryID ) );
		memset( values, 0, sizeof( values ) );
		Sum = 0;
		IsEnd = false;
    }
	int Sum;
	char Info[CountryDefine::MaxMsgCountryInfoSum][CountryDefine::MaxCountryInfoLength];
	uint8 CountryID[CountryDefine::MaxMsgCountryInfoSum];
	int values[CountryDefine::MaxMsgCountryInfoSum];
	__int64 Time[CountryDefine::MaxMsgCountryInfoSum];
	bool IsEnd;
};

struct DB2CSRequestCountryOfficeAck : public MsgCountryModule
{
    DB2CSRequestCountryOfficeAck()
    {
        header.dwType = DB2CS_REQUESTCOUNTRYOFFICECK;
        header.stLength = sizeof( DB2CSRequestCountryOfficeAck );

		sexID = -1;
		faceID = -1;
		headerID = -1;
		professionID = -1;
    }
	uint32 nPlayerID;
	uint8 countryID;
	uint8 uchPosition;
	uint8 sexID;
	uint16 faceID;
	uint16 headerID;
	uint16 professionID;
	char szName[ CountryDefine::MaxNameLength ];
};

struct CS2DBCountryDataSaveReq : public MsgCountryModule
{
    CS2DBCountryDataSaveReq()
    {
        header.dwType = CS2DB_COUNTRYDATESAVEREQ;
        header.stLength = sizeof( CS2DBCountryDataSaveReq );
    }

    CountryData xData;
};

struct CS2DBCountryOfficeReq : public MsgCountryModule
{
    CS2DBCountryOfficeReq()
    {
        header.dwType = CS2DB_COUNTRYOFFICEREQ;
        header.stLength = sizeof( CS2DBCountryOfficeReq );
    }
	uint32	nPlayerID;
	uint8 countryID;
	uint8 uchPosition;
	char szName[ CountryDefine::MaxNameLength ];
};

struct CS2GSCountryDataList : public MsgCountryModule
{
    CS2GSCountryDataList()
    {
        header.dwType = CS2GS_COUNTRYDATALIST;
        header.stLength = sizeof( CS2GSCountryDataList );
    }

    unsigned char uchWeakCountryID;
	unsigned char uchStrongCountryID;
    CountryData xData[ CountryDefine::Country_Max ];
};

struct CS2GSCountryWeakStrongthChange : public MsgCountryModule
{
    CS2GSCountryWeakStrongthChange()
    {
        header.dwType = CS2GS_COUNTRYWEAKSTRONGTH;
        header.stLength = sizeof( CS2GSCountryWeakStrongthChange );
    }

    unsigned char uchWeakCountryID;
	unsigned char uchStrongCountryID;
};

struct GS2CSCountryDateChangeReq : public MsgCountryModule
{
    GS2CSCountryDateChangeReq()
    {
        header.dwType = GS2CS_COUNTRYDATACHANGEREQ;
        header.stLength = sizeof( GS2CSCountryDateChangeReq );
    }

    unsigned char uchCountryID;
    unsigned char uchChangeType;
    unsigned char uchOperateType;
    unsigned int nValue;
};

struct CS2GSTellWeakCountry : public MsgCountryModule
{
    CS2GSTellWeakCountry()
    {
        header.dwType = CS2GS_TELLWEAKCOUNTRY;
        header.stLength = sizeof( CS2GSTellWeakCountry );
    }

    unsigned char uchCountryID;
};

struct CS2GSTellStrongCountry : public MsgCountryModule
{
    CS2GSTellStrongCountry()
    {
        header.dwType = CS2GS_TELLSTRONGCOUNTRY;
        header.stLength = sizeof( CS2GSTellStrongCountry );
    }

    unsigned char uchCountryID;
};


struct GS2CSChangeCountryNameReq : public MsgCountryModule
{
    GS2CSChangeCountryNameReq()
    {
        header.dwType = GS2CS_CHANGECOUNTRYNAMEREQ;
        header.stLength = sizeof( GS2CSChangeCountryNameReq );
    }

    unsigned char uchCountryID;
    unsigned int nPlayerID;
    char szPlayer[ CountryDefine::MaxNameLength ];
    char szName[ CountryDefine::MaxCountryLength ];
};

struct CS2GSCountryNameChange : public MsgCountryModule
{
    CS2GSCountryNameChange()
    {
        header.dwType = CS2GS_COUNTRYNAMECHANGE;
        header.stLength = sizeof( CS2GSCountryNameChange );
    }

    unsigned char uchCountryID;
    unsigned int nPlayerID;
    char szPlayer[ CountryDefine::MaxNameLength ];
    char szName[ CountryDefine::MaxCountryLength ];
};

struct CS2GSCountryWarStatus : public MsgCountryModule
{
    CS2GSCountryWarStatus()
    {
        header.dwType = CS2GS_COUNTRYWARSTATUS;
        header.stLength = sizeof( CS2GSCountryWarStatus );
    }
    
    unsigned char uchStatus;
};

struct GS2CSCountryWarKillPlayer : public MsgCountryModule
{
    GS2CSCountryWarKillPlayer()
    {
        header.dwType = GS2CS_COUNTRYWARKILLPLAYER;
        header.stLength = sizeof( GS2CSCountryWarKillPlayer );
    }

    unsigned char uchKillCountryID;
    unsigned char uchDeathCountryID;
};

struct CS2GSCountryWarKillPlayer : public MsgCountryModule
{
    CS2GSCountryWarKillPlayer()
    {
        header.dwType = CS2GS_COUNTRYWARKILLPLAYER;
        header.stLength = sizeof( CS2GSCountryWarKillPlayer );
    }

    unsigned char uchKillCountryID;
    unsigned int nKillCount;
    unsigned char uchDeathCountryID;
    unsigned int nDeathCount;
};

struct GS2CSCountryWarStatusChange : public MsgCountryModule
{
    GS2CSCountryWarStatusChange()
    {
        header.dwType = GS2CS_COUNTRYWARSTATUSCHANGE;
        header.stLength = sizeof( GS2CSCountryWarStatusChange );
    }
    
    unsigned char uchStatus;
};


struct GS2CSCountryPlayerChange : public MsgCountryModule
{
    GS2CSCountryPlayerChange()
    {
        header.dwType = GS2CS_COUNTRYPLAYERCHANGE;
        header.stLength = sizeof( GS2CSCountryPlayerChange );
    }

    unsigned int nPlayerID;
    uint8 nowCountryID;
	uint8 oldCountryID;
};	

struct MsgCountryBuffChange : public MsgCountryModule
{
    MsgCountryBuffChange()
    {
        header.dwType = MSG_COUNTRYBUFFCHANGE;
        header.stLength = sizeof( MsgCountryBuffChange );
    }
};

struct MsgCountryBuffChangeAck : public MsgCountryModule
{
    MsgCountryBuffChangeAck()
    {
        header.dwType = MSG_COUNTRYBUFFCHANGEACK;
        header.stLength = sizeof( MsgCountryBuffChangeAck );
    }
};

#pragma pack( pop )

#endif