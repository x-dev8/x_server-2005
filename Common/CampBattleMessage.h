#ifndef __CAMPBATTLEMESSAGEDEFINE_H__
#define __CAMPBATTLEMESSAGEDEFINE_H__

/************************************************************************
            阵营战场消息定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "MessageRangeDefine.h"
#include "CampBattleDefine.h"
#include "GuildDefine.h"
#pragma pack( push, 1 )

enum CampBattleMessageDefine
{
    MSG_TELLCAMPBATTLESTATUS = GAMEWORD_CAMPBATTLEMSG_BEGIN,   
    MSG_TELLCAMPBATTLEKILLPLAYER,
    MSG_TELLCAMPBATTLERESOURCE,
    MSG_TELLCAMPBATTLEFIGHTCAMP,
    MSG_CAMPBATTLEPLAYERREQ,
    MSG_TELLCAMPBATTLEPLAYER,
    MSG_LEAVECAMPBATTLEREQ,
    MSG_FLYTOCAMPBATTLEREQ,
    MSG_FLYTOCAMPBATTLEACK,
    MSG_CAMPBATTLESIGNUPREQ,
    MSG_CAMPBATTLESIGNUPACK,
    MSG_ENTERCAMPBATTLEREQ,
    MSG_ENTERCAMPBATTLEACK,
    MSG_KILLCAMPBATTLEMONSTER,
    MSG_TELLCAMPBATTLEMATCH,


    MSG_SHOWCAMPGUILDBATTLEENTER,
    MSG_CAMPGUILDBATTLERESULT,
    MSG_TELLCAMPGUILDBATTLEUNMATCH,
    MSG_TELLCAMPGUILDBATTLEREFRESHMONSTER,

    MSG_TELLCAMPBATTLESIGNUPREPLACE,
    MSG_TELLCOUNTERBATTLERESULT,
    MSG_TELLCAMPBATTLEDEATHCOUNT,
    MSG_TELLCOUNTRYBATTLEEGUILD,
    MSG_QUETYCOUNTRYBATTLESIGNUPACK,
    MSG_TELLCOUNTERBATTLEPLAYERCOUNT,
	MSG_CAMPWORLDBATTLEACK,
	MSG_GETGLOBALDBBATTLESUMREQ,
	MSG_GETGLOBALDBBATTLESUMACK,
	MSG_CAMPBATTLESIGNUPSECC,
	MSG_CAMPBATTLECHECKCAMPBATTLEVALUESUM,
	MSG_CAMPGUILDBATTLEREWARDINFO,
};

struct MsgCampBattleModule : public Msg
{
    MsgCampBattleModule()
    {
        SetModuleType( EMessageModule_CampBattle );
    }
};

// 通知阵营战场状态
struct MsgTellCampBattleStatus : public MsgCampBattleModule
{
    MsgTellCampBattleStatus()
    {
        header.dwType = MSG_TELLCAMPBATTLESTATUS;
        header.stLength = sizeof( MsgTellCampBattleStatus );
        nLeftTime = 0;
    }

    unsigned char uchCampBattleType;    // 阵营战场类型
    unsigned char uchCampBattleStatus;  // 阵营战场状态
    unsigned int nLeftTime;             // 剩余时间 (单位: 秒, nLeftTime == 0时, 不需要处理剩余时间 )
};

// 通知阵营战场杀人
struct MsgTellCampBattleKillPlayer : public MsgCampBattleModule
{
    MsgTellCampBattleKillPlayer()
    {
        header.dwType = MSG_TELLCAMPBATTLEKILLPLAYER;
        header.stLength = sizeof( MsgTellCampBattleKillPlayer );
    }

    enum EConstDefine
    {
        TypeFirstKill = 1,  // 一血
        TypeKeepKill,       // 连续杀人
        TypeBeKill,         // 终结杀人
        TypeTotalKill,      // 总共杀人
    };

    unsigned char uchCampBattleType;                // 阵营战场类型
    unsigned char uchKillType;                      // 杀人类型( 上面有定义 )
    char szKillerName[ CampDefine::NameLength ];    // 杀人者
    char szBeKillName[ CampDefine::NameLength ];    // 被杀者
    unsigned short ustKillCount;                    // 杀人数量( 被杀时的数量 )
    unsigned short ustStringID;                     // 广播使用的StringID;
};

// 同步战场资源分
struct MsgTellCampBattleResource : public MsgCampBattleModule
{
    MsgTellCampBattleResource()
    {
        header.dwType = MSG_TELLCAMPBATTLERESOURCE;
        header.stLength = sizeof( MsgTellCampBattleResource );
    }
	unsigned int nRedGuildID;
	unsigned int nBlueGuildID;
    unsigned int nRedResource;      // 红方资源
    unsigned int nBlueResource;     // 蓝方资源
	unsigned int nRedTotleKillSum;
	unsigned int nBlueTotleKillSum;
	float nRedAtterHp[4];
	float nBlueAtterHp[4];
};

// 通知客户端阵营消息
struct MsgTellCampBattleFightCamp : public MsgCampBattleModule
{
    MsgTellCampBattleFightCamp()
    {
        header.dwType = MSG_TELLCAMPBATTLEFIGHTCAMP;
        header.stLength = sizeof( MsgTellCampBattleFightCamp );
    }

    GameObjectId ustPlayerID; // 玩家动态ID
    unsigned char uchFightCamp; // 阵营
};

// 客户端请求杀人信息
struct MsgCampBattlePlayerReq : public MsgCampBattleModule
{
    MsgCampBattlePlayerReq()
    {
        header.dwType = MSG_CAMPBATTLEPLAYERREQ;
        header.stLength = sizeof( MsgCampBattlePlayerReq );
    }
    
    enum EConstDefine
    {
        TypeSelfCamp = 1,   // 请求自己阵营
        TypeTargetCamp,     // 请求对方阵营
        TypeAllCamp,        // 请求双方阵营
    };

    unsigned char uchReqType;   // 请求类型
};

// 阵营战场的杀人信息
struct MsgTellCampBattlePlayer : public MsgCampBattleModule
{
    MsgTellCampBattlePlayer()
    {
        header.dwType = MSG_TELLCAMPBATTLEPLAYER;
        header.stLength = sizeof( MsgTellCampBattlePlayer ) - sizeof( xPlayer );

        uchCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 200,
    };

    unsigned char uchCampBattleType;    // 阵营战场类型
    unsigned char uchCount;
    BattlePlayer xPlayer[ MaxCount ];

    void AddBattlePlayer( BattlePlayer& xData )
    {
        if ( uchCount >= MaxCount )
        { return; }

        xPlayer[ uchCount ] = xData;
        ++uchCount;
        header.stLength += sizeof ( BattlePlayer );
    }
};

// 请求离开战场
struct MsgLeaveCampBattleReq : public MsgCampBattleModule
{
    MsgLeaveCampBattleReq()
    {
        header.dwType = MSG_LEAVECAMPBATTLEREQ;
        header.stLength = sizeof( MsgLeaveCampBattleReq );
    }
};

// 服务器通知客户端是否要进入帮派阵营战场
struct MsgFlyToCampBattleReq : public MsgCampBattleModule
{
    MsgFlyToCampBattleReq()
    {
        header.dwType = MSG_FLYTOCAMPBATTLEREQ;
        header.stLength = sizeof( MsgFlyToCampBattleReq );
    }

    unsigned char uchBattleType;
    unsigned int nMapID;    // ConfigMapID
	unsigned int nKingdomID; //国家主城id
	float nKingdomX;
	float nKingdomY;
	unsigned int RedID;
	unsigned int BlueID;
};

// 客户端同意加入阵营战场, 服务器传送该玩家到NPC处
struct MsgFlyToCampBattleAck : public MsgCampBattleModule
{
    MsgFlyToCampBattleAck()
    {
        header.dwType = MSG_FLYTOCAMPBATTLEACK;
        header.stLength = sizeof( MsgFlyToCampBattleAck );
    }

    unsigned int nMapID;    // ConfigMapID
};

// 报名阵营战场
struct MsgCampBattleSignUpReq : public MsgCampBattleModule
{
    MsgCampBattleSignUpReq()
    {
        header.dwType = MSG_CAMPBATTLESIGNUPREQ;
        header.stLength = sizeof( MsgCampBattleSignUpReq );
    }

    unsigned char uchBattleType;
};

// 报名结果回馈
struct MsgCampBattleSignUpAck : public MsgCampBattleModule
{
	MsgCampBattleSignUpAck()
	{
		header.dwType = MSG_CAMPBATTLESIGNUPACK;
		header.stLength = sizeof( MsgCampBattleSignUpAck );
		uchWarxishu = 0;
		unhGuildxishu = 0;
	}

	unsigned char uchWarxishu;
	unsigned char uchResult;
	unsigned char unhGuildxishu;
};
struct MsgCampBattleSignUpSecc : public MsgCampBattleModule
{
	MsgCampBattleSignUpSecc()
	{
		header.dwType = MSG_CAMPBATTLESIGNUPSECC;
		header.stLength = sizeof( MsgCampBattleSignUpSecc );
	}
	unsigned int RedGuildID;
	unsigned int BlueGuildID;
};
struct MsgCampBattleCheckCampBattleValueSum : public MsgCampBattleModule
{
	MsgCampBattleCheckCampBattleValueSum()
	{
		header.dwType = MSG_CAMPBATTLECHECKCAMPBATTLEVALUESUM;
		header.stLength = sizeof( MsgCampBattleCheckCampBattleValueSum );
	}
	unsigned int redguildid;
	unsigned int blueguildid;
	bool redlose;
	bool bulelose;
};



// 进入阵营战场请求
struct MsgEnterCampBattleReq : public MsgCampBattleModule
{
    MsgEnterCampBattleReq()
    {
        header.dwType = MSG_ENTERCAMPBATTLEREQ;
        header.stLength = sizeof( MsgEnterCampBattleReq );
    }

    unsigned char uchBattleType;    // 阵营战场类型
};

// 进入战场结果回馈
struct MsgEnterCampBattleAck : public MsgCampBattleModule
{
    MsgEnterCampBattleAck()
    {
        header.dwType = MSG_ENTERCAMPBATTLEACK;
        header.stLength = sizeof( MsgEnterCampBattleAck );
    }

    unsigned char uchResult;
};

// 战场杀死怪物
struct MsgKillCampBattleMonster : public MsgCampBattleModule
{
    MsgKillCampBattleMonster()
    {
        header.dwType = MSG_KILLCAMPBATTLEMONSTER;
        header.stLength = sizeof( MsgKillCampBattleMonster );
    }

    unsigned char uchBattleType;
    unsigned char uchFightCamp;    
    int nMonsterID; // 怪物ID
    int nStringID;  // 广播的ID
};

// 通知阵营战场对阵列表
struct MsgTellCampBattleMatch : public MsgCampBattleModule
{
    MsgTellCampBattleMatch()
    {
        header.dwType = MSG_TELLCAMPBATTLEMATCH;
        header.stLength = sizeof( MsgTellCampBattleMatch );
    }

    unsigned char uchBattleType;
    unsigned int nRedID;
    unsigned int nBlueID;
};


// 通知帮派帮主, 你的报名中被其他帮派顶替了
struct MsgTellCampBattleSignUpReplace : public MsgCampBattleModule
{
    MsgTellCampBattleSignUpReplace()
    {
        header.dwType = MSG_TELLCAMPBATTLESIGNUPREPLACE;
        header.stLength = sizeof( MsgTellCampBattleSignUpReplace );
    }

    unsigned char uchBattleType;    // 阵营战场类型
};

struct MsgTellCampBattleDeathCount : public MsgCampBattleModule
{
    MsgTellCampBattleDeathCount()
    {
        header.dwType = MSG_TELLCAMPBATTLEDEATHCOUNT;
        header.stLength = sizeof( MsgTellCampBattleDeathCount );
    }

    uint8 nDeathCount;  // 当前死亡次数
    uint8 nMaxCount;    // 最大死亡次数
};

////////////////////////////////////////////////////////////////////////////////
// 帮派争夺战消息协议
// 显示帮派争夺战进入窗口
struct MsgShowCampGuildBattleEnter : public MsgCampBattleModule
{
    MsgShowCampGuildBattleEnter()
    {
        header.dwType = MSG_SHOWCAMPGUILDBATTLEENTER;
        header.stLength = sizeof( MsgShowCampGuildBattleEnter );
    }

    unsigned char uchBattleType;    // 阵营战场类型

    unsigned int nRedGuildID;   // 红方帮派ID
    unsigned int nBlueGuildID;  // 蓝方帮派ID
};

// 帮派争夺战结果
struct MsgCampGuildBattleResult : public MsgCampBattleModule
{
    MsgCampGuildBattleResult()
    {
        header.dwType = MSG_CAMPGUILDBATTLERESULT;
        header.stLength = sizeof( MsgCampGuildBattleResult );
    }

    unsigned int nWinGuildID;   // 胜利帮派ID
    unsigned int nLoseGuildID;  // 胜利帮派ID
};

struct MsgCampGuildBattleRewardInfo : public MsgCampBattleModule
{
	const static int MaxLength = 10;
    MsgCampGuildBattleRewardInfo()
    {
        header.dwType = MSG_CAMPGUILDBATTLEREWARDINFO;
        header.stLength = sizeof( MsgCampGuildBattleRewardInfo);
    }

	/*void calclength()
	{
		header.stLength = sizeof( MsgCampGuildBattleRewardInfo) - (MaxLength-OtherSum*2) * sizeof(unsigned int);
	}*/

    unsigned int nWinGuildID;   // 胜利帮派ID
    unsigned int nLoseGuildID; 
	unsigned int WinItemID;
	unsigned int LoseItemID;
	unsigned int OtherItemID;
	unsigned int OtherSum;
	unsigned int KissSum;
	unsigned int PlayerID[MaxLength];
	char Name[MaxLength][GuildDefine::MaxNameLength];
	unsigned int Point[MaxLength];
	//unsigned int Info[MaxLength];
};

// 通知帮主, 你的帮派最后一个报名没有匹配上, 不能参加帮派争夺战
struct MsgTellCampGuildBattleUnMatch : public MsgCampBattleModule
{
    MsgTellCampGuildBattleUnMatch()
    {
        header.dwType = MSG_TELLCAMPGUILDBATTLEUNMATCH;
        header.stLength = sizeof( MsgTellCampGuildBattleUnMatch );
    }
};

// 通知战场内玩家, 某某怪刷出来了
struct MsgTellCampGuildBattleRefreshMonster : public MsgCampBattleModule
{
    MsgTellCampGuildBattleRefreshMonster()
    {
        header.dwType = MSG_TELLCAMPGUILDBATTLEREFRESHMONSTER;
        header.stLength = sizeof( MsgTellCampGuildBattleRefreshMonster );
    }

    int nMonsterID;
    int nStringID;
};


///////////////////////////////////////////////////////////////////////////////////
// 国王争夺战, 青龙争夺战, 朱雀争夺战 消息
// 全国广播某个帮派获得了战场资格
struct MsgTellCountryBattleGuild : public MsgCampBattleModule
{
    MsgTellCountryBattleGuild()
    {
        header.dwType = MSG_TELLCOUNTRYBATTLEEGUILD;
        header.stLength = sizeof( MsgTellCountryBattleGuild );
    }

    uint8 uchBattleType;      // 国家战场类型 ( 1 2 3 分别是  国家 青龙  朱雀战场,  在CountryDefine.h中有定义 )
    uint32 nGuildID;          // 获得资格的帮派ID
};

// 通知国家战场结果
struct MsgTellCountryBattleResult : public MsgCampBattleModule
{
    MsgTellCountryBattleResult()
    {
        header.dwType = MSG_TELLCOUNTERBATTLERESULT;
        header.stLength = sizeof( MsgTellCountryBattleResult );
    }

    uint8 uchBattleType;      // 国家战场类型 ( 1 2 3  分别是  国家 青龙  朱雀战场,  在CountryDefine.h中有定义 )
    uint8 uchWinType;         // 胜利方式
    uint32 nGuildID;          // 胜利帮会ID
};

// 查询国家战场报名
struct MsgQueryCountryBattleSignUpAck : public MsgCampBattleModule
{
    MsgQueryCountryBattleSignUpAck()
    {
        header.dwType = MSG_QUETYCOUNTRYBATTLESIGNUPACK;
        header.stLength = sizeof( MsgQueryCountryBattleSignUpAck );

        uchResult = ECD_Success;
        nGuildID = 0;
    }

    enum EConstDefine
    {
        ECD_Success = 0,
        ECD_NotOpen,            // 不在报名状态, 不能查询
    };

    uint8 uchBattleType;      // 国家战场类型 ( 1 2 3  分别是  国家 青龙  朱雀战场,  在CountryDefine.h中有定义 )
    uint8 uchResult;          // 进入结果( 只有失败才有消息返回 )
    uint32 nGuildID;          // 报名成功的帮会ID
};

// 发送战场队员个数, 以及帮主死亡次数 ( 红方就是守擂方, 蓝方就是抢擂方 )
struct MsgTellCountryBattlePlayerCount : public MsgCampBattleModule
{
    MsgTellCountryBattlePlayerCount()
    {
        header.dwType = MSG_TELLCOUNTERBATTLEPLAYERCOUNT;
        header.stLength = sizeof( MsgTellCountryBattlePlayerCount );
        nRedCount = 0;
        nBlueCount = 0;
    }

    uint16 nRedCount;   
    uint16 nBlueCount;

    uint16 nRedMasterDeathCount;    // 红方帮主死亡次数
    uint16 nBlueMasterDeathCount;   // 蓝方帮主死亡次数
};


struct MsgCampWorldBattleAck : public MsgCampBattleModule
{
	enum WorldBattleDefine
	{
		WBD_Prepare = 1, //准备
		WBD_Fight = 2, // 开始
		WBD_End = 3, // 结束
	};
	MsgCampWorldBattleAck()
	{
		header.dwType = MSG_CAMPWORLDBATTLEACK;
		header.stLength = sizeof( MsgCampWorldBattleAck );
	}
	unsigned char uchResult;
	unsigned int  GlobalDBCOuntryID;
};

struct MsgGetGlobalDBBattleSumReq : public MsgCampBattleModule
{
    MsgGetGlobalDBBattleSumReq()
    {
        header.dwType = MSG_GETGLOBALDBBATTLESUMREQ;
        header.stLength = sizeof( MsgGetGlobalDBBattleSumReq );
    }
};

struct MsgGetGlobalDBBattleSumAck : public MsgCampBattleModule
{
    MsgGetGlobalDBBattleSumAck()
    {
        header.dwType = MSG_GETGLOBALDBBATTLESUMACK;
        header.stLength = sizeof( MsgGetGlobalDBBattleSumAck );
    }
	int Sum;
};
////////////////////////////////////////////////////////////////////////////////////

#pragma pack( pop )

#endif