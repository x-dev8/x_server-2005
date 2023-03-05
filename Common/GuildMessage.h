#ifndef __GUILDMESSAGEDEFINE_H__
#define __GUILDMESSAGEDEFINE_H__

/************************************************************************
            帮派消息定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "MsgBase.h"
#include "GlobalDef.h"
#include "MessageRangeDefine.h"
#include "GuildDefine.h"

#pragma pack( push, 1 )

enum GuildMessageDefine
{
    MSG_CREATEGUILDREQ = GAMEWORD_GUILDMSG_BEGIN,       // 请求创建帮派
    MSG_CREATEGUILDACK,
    MSG_TELLCREATEGUILD,
    MSG_TELLJOINGUILDTOVIEW,
    MSG_TELLJOINGUILDTOGUILD,
    MSG_TELLLEAVEGUILDTOVIEW,
    MSG_TELLLEAVEGUILDTOGUILD,
    MSG_TELLGUILDDATA,
    MSG_TELLGUILDLIST,
    MSG_LEAVEGUILDREQ,
    MSG_LEAVEGUILDACK,
    MSG_KICKGUILDREQ,
    MSG_KICKGUILDACK,
    MSG_INVITEUILDREQ,
    MSG_INVITEGUILDACK,
    MSG_INVITEJOINGUILDREQ,
    MSG_INVITEJOINGUILDACK,
    MSG_JOINGUILDREQ,
    MSG_JOINGUILDACK,
    MSG_REQUESTJOINGUILDREQ,
	MSG_GUILDADDSQREQ,
	MSG_GUILDDELSQREQ,
    MSG_REQUESTJOINGUILDACK,
    MSG_QUERYGUILDATAREQ,
    MSG_QUERYGUILDATAACK,
    MSG_TELLDISBANDGUILD,
    MSG_MEMBERDATAUPDATE,
    MSG_GUILDDATAUPDATE,
	MSG_GUILDCLIENUPDATE,
    MSG_GUILDNOTICECHANGEREQ,
    MSG_TELLGUILDNOTICE,
    MSG_GUILDRESIGNPOSITIONREQ,
    MSG_GUILDASSIGNPOSITIONREQ,
    MSG_GUILDASSIGNPOSITIONACK,
    MSG_GUILDTRANSFERPOSITIONREQ,
    MSG_GUILDCREATEFAMILYREQ,
    MSG_GUILDCREATEFAMILYACK,
    MSG_TELLGUILDFAMILYCHANGE,
    MSG_GUILDFAMILYCHANGEREQ,
    MSG_GUILDFAMILYCHANGEACK,
    MSG_GUILDMEMBERFAMILYCHANGEREQ,
    MSG_GUILDMEMBERFAMILYCHANGEACK,
    MSG_GUILDLEVELUPACK,
    MSG_GUILDOFFERBUILDACK,
    MSG_GUILDDELATEREQUESTACK,
    MSG_GUILDDELATEAGREEREQ,
    MSG_GUILDDELATEAGREEACK,
    MSG_GUILDDELATERESULT,
    MSG_GUILDDONATEREQ,
    MSG_GUILDDONATEACK,
    MSG_GUILDRELEASEACK,
    MSG_GUILDQUESTRELEASESTATUS,
    MSG_GUILDCLEARMEMBERACTIVITY,
    MSG_TELLGUILDDISBANDTIME,
    MSG_GUILDSHOPLEVELUPREQ,
    MSG_GUILDSHOPLEVELUPACK,
    MSG_GUILDBUYITEMREQ,
    MSG_GUILDBUYITEMACK,
    MSG_GUILDCONVENTREQ,
    MSG_GUILDCONVENTACK,
	MSG_CHANGEGUILDAIM,
	MSG_CHANGEGUILDAIMACK,
	MSG_TELLGUILDAIM,
	MSG_GUILDNOTICEACK,
	MSG_GUILDTRANSFERACK,

    // 服务器间消息定义
    CS2DB_GUILDDATALOADREQ = CENTERGAME_GUILD_BEGIN,
    DB2CS_GUILDDATALIST,
    DB2CS_GUILDMEMBERLIST,
    CS2GS_GUILDDATALIST,
    CS2GS_GUILDDATASENDSUCCESS,
    CS2DB_GUILDDATAUPDATEREQ,
    CS2DB_GUILDMEMBERUPDATEREQ,
    CS2DB_GUILDDISBANDREQ,
    CS2DB_GUILDMEMBERLEAVEREQ,


    GS2CS_CREATEGUILDREQ,
    CS2GS_CREATEGUILDACK,
    GS2CS_LEAVEGUILDREQ,
    CS2GS_LEAVEGUILDACK,
    GS2CS_KICKGUILDREQ,
    GS2CS_INVITEGUILDREQ,
    GS2CS_INVITEJOINGUILDACK,
    CS2GS_JOINGUILDACK,
    GS2CS_JOINGUILDREQ,
    GS2CS_REQUESTJOINGUILDACK,
    GS2CS_DISBANDGUILDACK,
    CS2GS_MEMBERDATAUPDATE,
    CS2GS_GUILDDATAUPDATE,
    GS2CS_GUILDNOTICECHANGEREQ,
    CS2GS_GUILDNOTICECHANGEACK,
    GS2CS_GUILDRESIGNPOSITIONREQ,
    GS2CS_GUILDTRANSFERPOSITIONREQ,
    GS2CS_GUILDCREATEFAMILYREQ,
    GS2CS_GUILDFAMILYCHANGEREQ,
    CS2GS_GUILDFAMILYCHANGE,
    GS2CS_GUILDMEMBERFAMILYCHANGEREQ,
    GS2CS_GUILDASSIGNPOSTIONREQ,
    GS2CS_GUILDDATACHANGEREQ,
    GS2CS_MEMBERDATACHANGEREQ,
    GS2CS_GUILDLEVELUPREQ,
    GS2CS_GUILDOFFEGUILDRREQ,
    GS2CS_GUILDCOLLECTREQ,
    GS2CS_GUILDDELATEREQUESTREQ,
    CS2GS_GUILDDELATEREQUESTREQ,
    GS2CS_GUILDDELATEAGREEACK,
    CS2GS_GUILDDELATERESULT,
    GS2CS_GUILDDONATEREQUESTREQ,
    CS2GS_GUILDDONATEREQUESTREQ,
    GS2CS_GUILDDONATEACK,
	GS2CS_RAISEGUILDPLAYERITEM,
    CS2GS_GUILDDONATESTOP,
    GS2CS_GUILDQUESTRELEASEREQ,
    CS2GS_GUILDQUESTRELEASESTATUS,
    CS2GS_GUILDCLEARMEMBERACTIVITY,
    GS2CS_GUILDMESSAGE,
    CS2GS_GUILDMESSAGE,
    GS2CS_GUILDCONVENEREQ,
    CS2GS_GUILDCONVENEREQ,
    CS2GS_GUILDCONVENESTOP,
	GS2CS_GUILDAIMCHANGE,
	CS2GS_GUILDAIMCHANGEACK,
	GS2CS_PLAYERLVUPTOTHIRTY,			// luo.qin 4.20
	CS2GS_PLAYERLVUPTOTHIRTY,			// luo.qin 4.22
	CS2GS_MISSIONNOTENOUGH,
	GS2CS_GUILDSQREQ,
	CS2GS_GUILDBATTLESUM,
	MSG_GUILDSQACK,
	MSG_SETGUILDCAMPBATTLEVALUE,
	MSG_SETGUILDCAMPBATTLEVALUEACK,
	GS2CS_SETGUILDCAMPBATTLEVALUE,
	MSG_CHANGEGUILDNAMEREQ,
	GS2CS_CHANGEGUILDNAMEREQ,
	CS2GS_CHANGEGUILDNAMEACK,
	MSG_CHANGEGUILDNAMEACK,
	MSG_TELLGUILDPLAYERAISEITEM,

	GS2CS_GUILDMEMBERCHANGENAME,
	CS2GS_GUILDMEMBERCHANGENAME,
	MSG_GUILDCHANGENAMEACK,
	GS2CS_UPDATEGUILDCAMPBATTLEPOINT,
	GS2CS_UPDATEGUILDMEMBERONLINETIME,
	CS2GS_UPDATEGUILDMEMBERONLINETIME,
	MSG_UPDATEGUILDMEMBERONLINETIME,
};

struct MsgGuildModule : public Msg
{
    MsgGuildModule()
    {
        SetModuleType( EMessageModule_Guild );
    }
};

// 请求创建帮派
struct MsgCreateGuildReq : public MsgGuildModule
{
    MsgCreateGuildReq()
    {
        header.dwType   = MSG_CREATEGUILDREQ;
        header.stLength = sizeof( MsgCreateGuildReq );
    }

    char szName[ GuildDefine::MaxCreateLength ];    // 公会名字
	char szAim[ GuildDefine::MaxAimLength ];		// 帮派宗旨
};

// 回应请求创建帮派
struct MsgCreateGuildAck : public MsgGuildModule
{
    MsgCreateGuildAck()
    {
        header.dwType   = MSG_CREATEGUILDACK;
        header.stLength = sizeof( MsgCreateGuildAck );

        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 创建成功
        ECD_ErrorName,          // 存在屏蔽字符, 非法名字, 
        ECD_SaveName,           // 存在相同名字的帮派
        ECD_HaveGuild,          // 已经有帮派了, 不能创建
        ECD_LevelLess,          // 等级不足30级
        ECD_NotEnoughMoney,     // 没有足够的现银
		ECD_NotCountry,
    };

    unsigned char uchResult;
};

// 通知玩家, 新创建了一个帮派, 加入客户端帮派列表( 如果是自己国家的, 打出一个系统公告 )
struct MsgTellCreateGuild : public MsgGuildModule
{
    MsgTellCreateGuild()
    {
        header.dwType   = MSG_TELLCREATEGUILD;
        header.stLength = sizeof( MsgTellCreateGuild );
    }

    unsigned char uchCountry;
    char szPlayer[ GuildDefine::MaxNameLength ];    // 创建人
    unsigned int nGuildID;
    char szName[ GuildDefine::MaxCreateLength ];    // 公会名字
};

// 通知附近玩家某人加入帮派了
struct MsgTellJoinGuildToView : public MsgGuildModule
{
    MsgTellJoinGuildToView()
    {
        header.dwType   = MSG_TELLJOINGUILDTOVIEW;
        header.stLength = sizeof( MsgTellJoinGuildToView );
		nGuildPosition = 0;
    }

    unsigned int nGuildID;          // 帮派ID
	unsigned char nGuildPosition;
};

// 通知附近玩家某人离开帮派了
struct MsgTellLeaveGuildToView : public MsgGuildModule
{
    MsgTellLeaveGuildToView()
    {
        header.dwType   = MSG_TELLLEAVEGUILDTOVIEW;
        header.stLength = sizeof( MsgTellLeaveGuildToView );
    }
};

// 通知帮派成员, 有成员加入了
struct MsgTellJoinGuildToGuild : public MsgGuildModule
{
    MsgTellJoinGuildToGuild()
    {
        header.dwType   = MSG_TELLJOINGUILDTOGUILD;
        header.stLength = sizeof( MsgTellJoinGuildToGuild );
    }

    GuildMember xMember;
};

// 通知帮派成员, 有成员离开了
struct MsgTellLeaveGuildToGuild : public MsgGuildModule
{
    MsgTellLeaveGuildToGuild()
    {
        header.dwType   = MSG_TELLLEAVEGUILDTOGUILD;
        header.stLength = sizeof( MsgTellLeaveGuildToGuild );
    }

    unsigned int nPlayerID;
};

// 发送帮派信息给客户端,
struct MsgTellGuildData : public MsgGuildModule
{
    MsgTellGuildData()
    {
        header.dwType   = MSG_TELLGUILDDATA;
        header.stLength = sizeof( MsgTellGuildData ) - sizeof( xMember );

        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 200,
    };

    GuildData xData;

    unsigned short ustCount;
    GuildMember xMember[ MaxCount ];

    void AddMember( GuildMember& xInfo )
    {
        if ( ustCount >= MaxCount )
        { return; }

        xMember[ ustCount ] = xInfo;
        ++ustCount;
        header.stLength += sizeof( GuildMember );
    }
};

// 发送所有帮派列表给客户端
struct MsgTellGuildList : public MsgGuildModule
{
    MsgTellGuildList()
    {
        header.dwType   = MSG_TELLGUILDLIST;
        header.stLength = sizeof( MsgTellGuildList ) - sizeof( xList );

        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 500,
    };

    unsigned short ustCount;
    GuildListInfo xList[ MaxCount ]; 

    void AddGuild( GuildListInfo& xData )
    {
        if ( IsFull() )
        { return; }

        xList[ ustCount ] = xData;
        ++ustCount;

        header.stLength += sizeof( GuildListInfo );
    }

    bool IsFull() { return ustCount >= MaxCount; }

    void Reset()
    {
        header.stLength = sizeof( MsgTellGuildList ) - sizeof( xList );
        ustCount = 0;
    }
};

// 请求离开帮派
struct MsgLeaveGuildReq : public MsgGuildModule
{
    MsgLeaveGuildReq()
    {
        header.dwType   = MSG_LEAVEGUILDREQ;
        header.stLength = sizeof( MsgLeaveGuildReq );
    }
};

// 回馈离开帮会
struct MsgLeaveGuildAck : public MsgGuildModule
{
    MsgLeaveGuildAck()
    {
        header.dwType   = MSG_LEAVEGUILDACK;
        header.stLength = sizeof( MsgLeaveGuildAck );

        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 离开成功
        ECD_NotHaveGuild,       // 没有公会, 
        ECD_NotHaveRight,       // 没有权限( 担任了职位, 无法直接退出帮派 )
    };

    unsigned char uchResult;
};

// 请求将某人T出帮派
struct MsgKickGuildReq : public MsgGuildModule
{
    MsgKickGuildReq()
    {
        header.dwType   = MSG_KICKGUILDREQ;
        header.stLength = sizeof( MsgKickGuildReq );
    }

    unsigned int nPlayerID;
};

// 回应T人出帮派
struct MsgKickGuildAck : public MsgGuildModule
{
    MsgKickGuildAck()
    {
        header.dwType   = MSG_KICKGUILDACK;
        header.stLength = sizeof( MsgKickGuildAck );

        uchResult = ECD_Success;

    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 踢除成功
        ECD_NotHaveGuild,       // 没有帮派, 
        ECD_NotHaveRight,       // 没有T人权限, 或者别人和你职位一样高 或者一样高
    };

    unsigned char uchResult;
};

// 邀请某人进入帮派
struct MsgInviteGuildReq : public MsgGuildModule
{
    MsgInviteGuildReq()
    {
        header.dwType   = MSG_INVITEUILDREQ;
        header.stLength = sizeof( MsgInviteGuildReq );
    }

    char szPlayerName[ GuildDefine::MaxNameLength ];
};

// 回应邀请进入帮派
struct MsgInviteGuildAck : public MsgGuildModule
{
    MsgInviteGuildAck()
    {
        header.dwType   = MSG_INVITEGUILDACK;
        header.stLength = sizeof( MsgInviteGuildAck );
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 邀请成功
        ECD_NotHaveGuild,       // 自己没有帮派, 
        ECD_NotHaveRight,       // 没有邀请权限
        ECD_NotSaveCountry,     // 不是本国的不能邀请
        ECD_NotOnLine,          // 对方不存在 或者不在线 不在线, 
        ECD_AlreadyHaveGuild,   // 对方已经有帮派了
        ECD_LevelLess,          // 对方等级不足20级, 不能邀请加入帮派
        ECD_MemberFull,         // 成员数已经满了
        ECD_NotAgree,           // 拒绝加入帮派
		ECD_Agree,				// 同意加入帮派
        ECD_LeaveTimeLimit,     // 离开帮派后24小时内,对方不能加入帮派
    };

    unsigned char uchResult;
};

// 通知某人, 某公会邀请你加入帮派
struct MsgInviteJoinGuildReq : public MsgGuildModule
{
    MsgInviteJoinGuildReq()
    {
        header.dwType   = MSG_INVITEJOINGUILDREQ;
        header.stLength = sizeof( MsgInviteJoinGuildReq );
    }

    unsigned int nGuildID;      // 帮派ID
    char szInviterName[ GuildDefine::MaxNameLength ];   // 邀请人的名字
};

// 玩家响应帮派邀请到服务器
struct MsgInviteJoinGuildAck : public MsgGuildModule
{
    MsgInviteJoinGuildAck()
    {
        header.dwType   = MSG_INVITEJOINGUILDACK;
        header.stLength = sizeof( MsgInviteJoinGuildAck );
    }

    unsigned int nGuildID;      // 帮派ID
    bool bAgreeJoin;            // 是否同意邀请
};


// 玩家申请加入帮派
struct MsgJoinGuildReq : public MsgGuildModule
{
    MsgJoinGuildReq()
    {
        header.dwType   = MSG_JOINGUILDREQ;
        header.stLength = sizeof( MsgJoinGuildReq );
    }

    unsigned int nGuildID;      // 帮派ID
};

// 回应申请进入帮派
struct MsgJoinGuildAck : public MsgGuildModule
{
    MsgJoinGuildAck()
    {
        header.dwType   = MSG_JOINGUILDACK;
        header.stLength = sizeof( MsgJoinGuildAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 加入帮派成功
        ECD_CreateSuccess,      // 创建帮派成功
        ECD_AlreadyHaveGuild,   // 对方已经有帮派了
        ECD_LevelLess,          // 等级不足
        ECD_NotSaveCountry,     // 不是本国的不能申请
        ECD_TimeLimit,          // 退帮以后24小时内不能加入帮派
        ECD_GuildNotExist,      // 申请的帮派不存在
        ECD_MemberFull,         // 目标帮派成员数已经满了
        ECD_NotAgree,           // 拒绝申请加入
        ECD_NotOnLine,          // 帮派管理员都不在线
		ECD_IsCreSQ,			// 申请重复了
    };

    unsigned char uchResult;
};

// 发送消息给帮派管理员, 某人申请加入帮派
struct MsgRequestJoinGuildReq : public MsgGuildModule
{
    MsgRequestJoinGuildReq()
    {
        header.dwType   = MSG_REQUESTJOINGUILDREQ;
        header.stLength = sizeof( MsgRequestJoinGuildReq );
    }

    unsigned int nPlayerID;                      // 申请人的DBID
    char szName[ GuildDefine::MaxNameLength ];   // 申请人的名字
};

struct MsgGuildAddSQReq : public MsgGuildModule
{
    MsgGuildAddSQReq()
    {
        header.dwType   = MSG_GUILDADDSQREQ;
        header.stLength = sizeof( MsgGuildAddSQReq );
    }
    char szName[dr_MaxPlayerName];
	uint32 ID;
	uint32 Level;
	uint16 Profession;
};

struct MsgGuildDelSQReq : public MsgGuildModule
{
    MsgGuildDelSQReq()
    {
        header.dwType   = MSG_GUILDDELSQREQ;
        header.stLength = sizeof( MsgGuildDelSQReq );
    }
	uint32 ID;
};
// 回馈申请加入帮派
struct MsgRequestJoinGuildAck : public MsgGuildModule
{
    MsgRequestJoinGuildAck()
    {
        header.dwType   = MSG_REQUESTJOINGUILDACK;
        header.stLength = sizeof( MsgRequestJoinGuildAck );
    }

    unsigned int nPlayerID;      // 申请人的DBID
    bool bAgreeJoin;             // 是否同意加入帮派   
};

// 客户端请求查询帮派信息
struct MsgQueryGuildDataReq : public MsgGuildModule
{
    MsgQueryGuildDataReq()
    {
        header.dwType   = MSG_QUERYGUILDATAREQ;
        header.stLength = sizeof( MsgQueryGuildDataReq );
    }

    unsigned int nGuildID;
};

// 回应查询帮派信息
struct MsgQueryGuildDataAck : public MsgGuildModule
{
    MsgQueryGuildDataAck()
    {
        header.dwType   = MSG_QUERYGUILDATAACK;
        header.stLength = sizeof( MsgQueryGuildDataAck );

        memset( szGuildName, 0, sizeof( szGuildName ) );
        memset( szMasterName, 0, sizeof( szMasterName ) );
        memset( szGuildAim, 0, sizeof( szGuildAim ) );
    }

    unsigned int nGuildID;                              // 帮派ID
    char szGuildName[ GuildDefine::MaxNameLength ];     // 帮派名字
    unsigned char uchLevel;                             // 帮派等级
    char szMasterName[ GuildDefine::MaxNameLength ];    // 帮主名字
    unsigned short ustMemberCount;                      // 成员个数
    __int64 n64CreateTime;                                // 创建时间
    //char szGuildNotice[ GuildDefine::MaxNoticeLength ]; // 帮派公告
	char szGuildAim[ GuildDefine::MaxAimLength ];		// 帮派宗旨
};

// 通知客户端帮派解散了
struct MsgTellDisbandGuild : public MsgGuildModule
{
    MsgTellDisbandGuild()
    {
        header.dwType   = MSG_TELLDISBANDGUILD;
        header.stLength = sizeof( MsgTellDisbandGuild );
    }

    unsigned int nGuildID;      // 如果是自己帮派解散了, 要给出提示, 否则不需要
};

// 更新帮派成员信息到客户端
struct MsgMemberDataUpdate : public MsgGuildModule
{
    MsgMemberDataUpdate()
    {
        header.dwType   = MSG_MEMBERDATAUPDATE;
        header.stLength = sizeof( MsgMemberDataUpdate );
    }

    unsigned int nPlayerID;         // 成员ID

    unsigned char uchUpdateType;            // 定义在GuildDefine.h中    UpdateMemberOnLine....
    unsigned int nUpdateValue;
};

struct MsgGuildClientUpdate : public MsgGuildModule
{
    MsgGuildClientUpdate()
    {
        header.dwType   = MSG_GUILDCLIENUPDATE;
        header.stLength = sizeof( MsgGuildClientUpdate );
    }
	GuildListInfo ClientInfo;
};


// 更新帮派信息到客户端
struct MsgGuildDataUpdate : public MsgGuildModule
{
    MsgGuildDataUpdate()
    {
        header.dwType   = MSG_GUILDDATAUPDATE;
        header.stLength = sizeof( MsgGuildDataUpdate );
    }

    unsigned char uchUpdateType;            // 定义在GuildDefine.h中    UpdateGuildLevel....
    unsigned int nUpdateValue;
};

// 请求修改帮派公告
struct MsgGuildNoticeChangeReq : public MsgGuildModule
{
    MsgGuildNoticeChangeReq()
    {
        header.dwType   = MSG_GUILDNOTICECHANGEREQ;
        header.stLength = sizeof( MsgGuildNoticeChangeReq );
    }

    char szNotice[ GuildDefine::MaxNoticeLength ];
};

// 发送帮派公告到客户端
struct MsgTellGuildNotice : public MsgGuildModule
{
    MsgTellGuildNotice()
    {
        header.dwType   = MSG_TELLGUILDNOTICE;
        header.stLength = sizeof( MsgTellGuildNotice );
    }
    
    char szNotice[ GuildDefine::MaxNoticeLength ];
};

// 请求修改帮派宗旨
struct MsgChangeGuildAimReq : public MsgGuildModule
{
	MsgChangeGuildAimReq()
	{
		header.dwType = MSG_CHANGEGUILDAIM;
		header.stLength = sizeof( MsgChangeGuildAimReq );
	}

	char szAim[ GuildDefine::MaxAimLength ];
};

// 回复请求修改帮派宗旨
struct MsgChangeGuildAimAck : public MsgGuildModule
{
	MsgChangeGuildAimAck()
	{
		header.dwType = MSG_CHANGEGUILDAIMACK;
		header.stLength = sizeof( MsgChangeGuildAimAck );

		uchResult = ECD_Success;
	}

	enum EConstDefine
	{
		ECD_Success = 0,
		ECD_InCD,	// 修改宗旨CD中
	};

	unsigned char uchResult;
};

// 通知客户端帮派宗旨变化
struct MsgTellGuildAim : public MsgGuildModule
{
	MsgTellGuildAim()
	{
		header.dwType = MSG_TELLGUILDAIM;
		header.stLength = sizeof( MsgTellGuildAim );
	}

	char szAim[ GuildDefine::MaxAimLength ];
};

// 请求辞去帮派职务
struct MsgGuildResignPositionReq : public MsgGuildModule
{
    MsgGuildResignPositionReq()
    {
        header.dwType   = MSG_GUILDRESIGNPOSITIONREQ;
        header.stLength = sizeof( MsgGuildResignPositionReq );
    }
};

// 任命某个人的职位
struct MsgGuildAssignPositionReq : public MsgGuildModule
{
    MsgGuildAssignPositionReq()
    {
        header.dwType   = MSG_GUILDASSIGNPOSITIONREQ;
        header.stLength = sizeof( MsgGuildAssignPositionReq );
    }

    unsigned int nPlayerID;         // 成员ID
    unsigned char uchPosition;      // 任命的职位 ( 传入GuildDefine::Position_Member 相当于罢免他的官职 )
};

// 服务器回应任命职位
struct MsgGuildAssignPositionAck : public MsgGuildModule
{
    MsgGuildAssignPositionAck()
    {
        header.dwType   = MSG_GUILDASSIGNPOSITIONACK;
        header.stLength = sizeof( MsgGuildAssignPositionAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 创建成功
        ECD_NotHaveRight,       // 没有权限
        ECD_SamePosition,       // 已经是该职位
        ECD_NotHaveFamily,      // 没有家族, 不能任命为家族长
    };

    unsigned char uchResult;
};

// 禅让职位给某人
struct MsgGuildTransferPositionReq : public MsgGuildModule
{
    MsgGuildTransferPositionReq()
    {
        header.dwType   = MSG_GUILDTRANSFERPOSITIONREQ;
        header.stLength = sizeof( MsgGuildTransferPositionReq );
    }

    unsigned int nPlayerID;     // 帮主只能禅让给副帮主...其他只能禅让给无职位的人
};

// 创建家族
struct MsgGuildCreateFamilyReq : public MsgGuildModule
{
    MsgGuildCreateFamilyReq()
    {
        header.dwType   = MSG_GUILDCREATEFAMILYREQ;
        header.stLength = sizeof( MsgGuildCreateFamilyReq );

        memset( szName, 0, sizeof( szName ) );
    }

    char szName[ GuildDefine::MaxFamilyLength ];
};

// 服务器回应创建家族
struct MsgGuildCreateFamilyAck : public MsgGuildModule
{
    MsgGuildCreateFamilyAck()
    {
        header.dwType   = MSG_GUILDCREATEFAMILYACK;
        header.stLength = sizeof( MsgGuildCreateFamilyAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 创建成功
        ECD_NotHaveRight,       // 没有权限
        ECD_FamilyFull,         // 家族满了
        ECD_SaveFamily,         // 存在相同名字的家族
    };

    unsigned char uchResult;
};

// 客户端请求修改家族名字
struct MsgGuildFamilyChangeReq : public MsgGuildModule
{
    MsgGuildFamilyChangeReq()
    {
        header.dwType   = MSG_GUILDFAMILYCHANGEREQ;
        header.stLength = sizeof( MsgGuildFamilyChangeReq );

        memset( szName, 0, sizeof( szName ) );
    }

    unsigned char uchFamilyID;
    char szName[ GuildDefine::MaxFamilyLength ];        // 传入空名字, 相当于删除家族
};

// 服务器回应修改家族
struct MsgGuildFamilyChangeAck : public MsgGuildModule
{
    MsgGuildFamilyChangeAck()
    {
        header.dwType   = MSG_GUILDFAMILYCHANGEACK;
        header.stLength = sizeof( MsgGuildFamilyChangeAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 修改成功
        ECD_NotHaveRight,       // 没有权限
        ECD_SaveFamily,         // 存在相同名字的家族
        ECD_EmptyFamily,        // 空家族不能改名 或者 删除
		ECD_AlreadyHaveFamily,	// 对方是家族长
        ECD_IsFamilyMaster,     // 家族长无法转出
    };

    unsigned char uchResult;
};

// 服务器通知客户端家族信息改变
struct MsgTellGuildFamilyChange : public MsgGuildModule
{
    MsgTellGuildFamilyChange()
    {
        header.dwType   = MSG_TELLGUILDFAMILYCHANGE;
        header.stLength = sizeof( MsgTellGuildFamilyChange );

        memset( szName, 0, sizeof( szName ) );
    }

    unsigned char uchFamilyID;                      // 家族ID
    char szName[ GuildDefine::MaxFamilyLength ];    // 家族名字( 为空 相当于删除家族 )
};

// 客户端请求改变成员家族信息
struct MsgGuildMemberFamilyChangeReq : public MsgGuildModule
{
    MsgGuildMemberFamilyChangeReq()
    {
        header.dwType   = MSG_GUILDMEMBERFAMILYCHANGEREQ;
        header.stLength = sizeof( MsgGuildMemberFamilyChangeReq );
    }

    unsigned int nPlayerID;
    unsigned char uchFamilyID;
};

// 服务器回应改变成员家族信息
struct MsgGuildMemberFamilyChangeAck : public MsgGuildModule
{
    MsgGuildMemberFamilyChangeAck()
    {
        header.dwType   = MSG_GUILDMEMBERFAMILYCHANGEACK;
        header.stLength = sizeof( MsgGuildMemberFamilyChangeAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 改变成功
        ECD_NotHaveRight,       // 没有权限
        ECD_SaveFamily,         // 相同的家族, 不需要移动
        ECD_EmptyFamily,        // 不能移动到空家族
		ECD_AlreadyHaveFamily,	// 对方是家族长
    };

    unsigned char uchResult;
};

// 回馈升级帮会消息
struct MsgGuildLevelUpAck : public MsgGuildModule
{
    MsgGuildLevelUpAck()
    {
        header.dwType   = MSG_GUILDLEVELUPACK;
        header.stLength = sizeof( MsgGuildLevelUpAck );
        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 升级成功
        ECD_NotHaveRight,       // 没有权限
        ECD_NotEnoughMoney,     // 没有足够的帮会资金
        ECD_NotEnoughExp,       // 没有足够的帮会经验
        ECD_MaxLevel,           // 已经是最大帮派等级了
		ECD_NotEnoughMisson,	// 没有足够的使命点
    };

    unsigned char uchResult;
};

// 回应帮贡建设
struct MsgGuildOfferBuildAck : public MsgGuildModule
{
    MsgGuildOfferBuildAck()
    {
        header.dwType   = MSG_GUILDOFFERBUILDACK;
        header.stLength = sizeof( MsgGuildOfferBuildAck );
    }

    enum EConstDefine
    {
        ECD_NotEnoughOffer = 0,     // 没有足够的帮贡
        ECD_MaxGuildExp,        // 帮派经验已经到最大值了
    };

    unsigned char uchResult;
};

// 申请弹劾回馈
struct MsgGuildDelateRequestAck : public MsgGuildModule
{
    MsgGuildDelateRequestAck()
    {
        header.dwType   = MSG_GUILDDELATEREQUESTACK;
        header.stLength = sizeof( MsgGuildDelateRequestAck );
    }

    enum EConstDefine
    {
        ECD_ErrorTime = 0,          // 错误的时间段
        ECD_AlreadyDelate,      // 已经有人弹劾了
        ECD_LevelLess,          // 等级不足
        ECD_MaxGuildExp,        // 帮派经验已经到最大值了
        ECD_NotEnoughMoney,     // 没有足够的金钱
        ECD_OnLineLess,         // 帮派在线成员少于20个, 不能发起弹劾
    };

    unsigned char uchResult;
};

// 向所有帮派成员发送是否同意弹劾的消息
struct MsgGuildDelateAgreeReq : public MsgGuildModule
{
    MsgGuildDelateAgreeReq()
    {
        header.dwType   = MSG_GUILDDELATEAGREEREQ;
        header.stLength = sizeof( MsgGuildDelateAgreeReq );
    }

    unsigned int nPlayerID;     // 发起弹劾的玩家
};

// 恢复是否同意弹劾
struct MsgGuildDelateAgreeAck : public MsgGuildModule
{
    MsgGuildDelateAgreeAck()
    {
        header.dwType   = MSG_GUILDDELATEAGREEACK;
        header.stLength = sizeof( MsgGuildDelateAgreeAck );
    }

    bool bAgreeDelate;  // 是否同意弹劾
};

// 弹劾结果
struct MsgGuildDelateResult : public MsgGuildModule
{
    MsgGuildDelateResult()
    {
        header.dwType   = MSG_GUILDDELATERESULT;
        header.stLength = sizeof( MsgGuildDelateResult );
    }

    unsigned int nPlayerID;     // 发起弹劾的玩家
    bool bDelateSuccess;        // 是否弹劾成功
};

// 发送募捐请求给客户端
struct MsgGuildDonateReq : public MsgGuildModule
{
    MsgGuildDonateReq()
    {
        header.dwType   = MSG_GUILDDONATEREQ;
        header.stLength = sizeof( MsgGuildDonateReq );
    }
};

// 客户端给服务器发送捐献多少金钱
struct MsgGuildDonateAck : public MsgGuildModule
{
    MsgGuildDonateAck()
    {
        header.dwType   = MSG_GUILDDONATEACK;
        header.stLength = sizeof( MsgGuildDonateAck );
    }

    unsigned int nMoney;        // 捐献多少钱( 不能少于10两 )
};

// 回馈客户端发布任务
struct MsgGuildReleaseAck : public MsgGuildModule
{
    MsgGuildReleaseAck()
    {
        header.dwType   = MSG_GUILDRELEASEACK;
        header.stLength = sizeof( MsgGuildReleaseAck );

        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 改变成功
        ECD_NotHaveRight,       // 没有权限
        ECD_GuildLevelLess,     // 帮派等级不够
        ECD_ErrorTime,          // 必须在22点以前发布
        ECD_AlreadyRelease,     // 已经发布了
        ECD_NotEnoughMoney,     // 没有足够的金钱
        ECD_QuestError,         // 不能发布此任务
    };

    unsigned char uchResult;
};

// 通知客户端帮派任务发布状态
struct MsgGuildQuestReleaseStatus : public MsgGuildModule
{
    MsgGuildQuestReleaseStatus()
    {
        header.dwType   = MSG_GUILDQUESTRELEASESTATUS;
        header.stLength = sizeof( MsgGuildQuestReleaseStatus );
    }

    unsigned int nQuestType;      // == 0 表示发布的已经结束了
    __int64 n64RelasetTime;    
};

// 通知将所有成员本周活跃度设置到上周, 并清除本周的活跃度,
struct MsgGuildClearMemberActivity : public MsgGuildModule
{
    MsgGuildClearMemberActivity()
    {
        header.dwType   = MSG_GUILDCLEARMEMBERACTIVITY;
        header.stLength = sizeof( MsgGuildClearMemberActivity );
    }
};

// 提示帮主帮会将在某日期解散
struct MsgTellGuildDisbanTime : public MsgGuildModule
{
    MsgTellGuildDisbanTime()
    {
        header.dwType   = MSG_TELLGUILDDISBANDTIME;
        header.stLength = sizeof( MsgTellGuildDisbanTime );
    }

    __int64 n64DisbandTime;
};

struct MsgGuildShopLevelUpReq : public MsgGuildModule
{
    MsgGuildShopLevelUpReq()
    {
        header.dwType   = MSG_GUILDSHOPLEVELUPREQ;
        header.stLength = sizeof( MsgGuildShopLevelUpReq );
    }

    unsigned char uchLevel;
};

// 回馈帮派商店激活消息
struct MsgGuildShopLevelUpAck : public MsgGuildModule 
{
    MsgGuildShopLevelUpAck()
    {
        header.dwType   = MSG_GUILDSHOPLEVELUPACK;
        header.stLength = sizeof( MsgGuildShopLevelUpAck );

        uchResult = ECD_Success;
    }

    enum EConstDefine
    {
        ECD_Success = 0,        // 改变成功
        ECD_NotHaveRight,       // 没有权限
        ECD_GuildLevelLess,     // 帮派等级不够
        ECD_NotEnoughExp,      // 没有足够的帮派经验
        ECD_AlreadActive,      // 已经被激活了
        ECD_ErrorLevel,        // 错误的等级
    };

    unsigned char uchResult;
};

// 购买帮派商店物品
struct MsgGuildBuyItemReq : public MsgGuildModule
{
    MsgGuildBuyItemReq()
    {
        header.dwType   = MSG_GUILDBUYITEMREQ;
        header.stLength = sizeof( MsgGuildBuyItemReq );
    }

    unsigned char uchLevel;     // 帮派商店等级
    unsigned int nItemID;       // 购买的物品
    unsigned int nCount;        // 购买的数量
};

struct MsgGuildBuyItemAck : public MsgGuildModule
{
    MsgGuildBuyItemAck()
    {
        header.dwType   = MSG_GUILDBUYITEMACK;
        header.stLength = sizeof( MsgGuildBuyItemAck );
    }

    enum EConstDefine
    {
        ECD_NotHaveRight,       // 没有权限
        ECD_LevelNotActive,     // 帮派商店没有激活
        ECD_ErrorItem,          // 没有此物品出售
        ECD_NotEnoughOffer,     // 没有足够的帮贡
        ECD_ErrorLevel,         // 错误的商店等级
        ECD_PackFull,           // 包裹满了
    };

    unsigned char uchResult;
};

// 帮主召集帮众 到某个地图
struct MsgGuildConveneReq : public MsgGuildModule
{
    MsgGuildConveneReq()
    {
        header.dwType   = MSG_GUILDCONVENTREQ;
        header.stLength = sizeof( MsgGuildConveneReq );
    }

    unsigned int nMapID;
};

// 帮众答应召集, 不同意则不用回消息
struct MsgGuildConveneAck : public MsgGuildModule
{
    MsgGuildConveneAck()
    {
        header.dwType   = MSG_GUILDCONVENTACK;
        header.stLength = sizeof( MsgGuildConveneAck );
    }
};

// 回复发帮派公告
struct MsgGuildNoticeAck : public MsgGuildModule
{
	MsgGuildNoticeAck()
	{
		SetType( MSG_GUILDNOTICEACK );
		SetLength( sizeof( MsgGuildNoticeAck ) );
	}

	enum EConstDefine
	{
		ECD_Success = 0,
		ECD_NotHaveRight,
	};

	unsigned char uchResult;
};

// 回复转让职位
struct MsgGuildTransferAck : public MsgGuildModule
{
	MsgGuildTransferAck()
	{
		SetType( MSG_GUILDTRANSFERACK );
		SetLength( sizeof( MsgGuildTransferAck ) );
	}

	enum EConstDefine
	{
		ECD_Success = 0,
		ECD_NotHaveRight,			// 你没有权限转让职位
		ECD_NotViceMaster,			// 帮主只能转让给副帮主，对方不是副帮主	
		ECD_LevelLess,				// 对方等级不足，无法转让
		ECD_NotGuildMember,		    // 对方不是本帮成员
		ECD_NotSameFamily,			// 转让族长时，对方必须是同一家族成员
		ECD_IsKing,					// 自己是国王， 不能转让帮主
		ECD_GameBattleCD,			// 公会约战CD期间不可以转让公会约战
		ECD_GameBattleExites,		// 公会约战存在
	};

	unsigned char uchResult;
};

///////////////////////////////////////////////////////////////////////////////
// 服务器间通讯
////////////////////////////////////////////////////////////////////////////////
struct CS2DBGuildDataLoadReq : public MsgGuildModule
{
    CS2DBGuildDataLoadReq()
    {
        header.dwType   = CS2DB_GUILDDATALOADREQ;
        header.stLength = sizeof( CS2DBGuildDataLoadReq );
    }
};

struct DB2CSGuildDataList : public MsgGuildModule
{
    DB2CSGuildDataList()
    {
        header.dwType   = DB2CS_GUILDDATALIST;
        header.stLength = sizeof( DB2CSGuildDataList ) - sizeof( xList );
        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 500,
    };

    unsigned short ustCount;
    GuildDataToServer xList[ MaxCount ];

    void AddGuildData( GuildDataToServer& xData )
    {
        if ( IsFull() )
        { return; }

        xList[ ustCount ] = xData;
        ++ustCount;
        header.stLength += sizeof( GuildDataToServer );
    }

    bool IsFull() { return ustCount >= MaxCount; }
    void Reset()
    {
        header.stLength = sizeof( DB2CSGuildDataList ) - sizeof( xList );
        ustCount = 0;
    }
};

struct DB2CSGuildMemberList : public MsgGuildModule
{
    DB2CSGuildMemberList()
    {
        header.dwType   = DB2CS_GUILDMEMBERLIST;
        header.stLength = sizeof( DB2CSGuildMemberList ) - sizeof( xList );
        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 300,
    };

    unsigned short ustCount;
    GuildMember xList[ MaxCount ];

    void AddGuildMember( GuildMember& xMember )
    {
        if ( IsFull() )
        { return; }

        xList[ ustCount ] = xMember;
        ++ustCount;
        header.stLength += sizeof( GuildMember );
    }

    bool IsFull() { return ustCount >= MaxCount; }
    void Reset()
    {
        header.stLength = sizeof( DB2CSGuildMemberList ) - sizeof( xList );
        ustCount = 0;
    }
};

struct CS2DBGuildDataUpdateReq : public MsgGuildModule
{
    CS2DBGuildDataUpdateReq()
    {
        header.dwType   = CS2DB_GUILDDATAUPDATEREQ;
        header.stLength = sizeof( CS2DBGuildDataUpdateReq );
    }

    GuildDataToServer xData;
};

struct CS2DBGuildMemberUpdateReq : public MsgGuildModule
{
    CS2DBGuildMemberUpdateReq()
    {
        header.dwType   = CS2DB_GUILDMEMBERUPDATEREQ;
        header.stLength = sizeof( CS2DBGuildMemberUpdateReq ) - sizeof( xList );
        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 300,
    };

    unsigned short ustCount;
    GuildMember xList[ MaxCount ];

    void AddGuildMember( GuildMember& xMember )
    {
        if ( IsFull() )
        { return; }

        xList[ ustCount ] = xMember;
        ++ustCount;
        header.stLength += sizeof( GuildMember );
    }

    bool IsFull() { return ustCount >= MaxCount; }
};

struct CS2DBGuildDisbandReq : public MsgGuildModule
{
    CS2DBGuildDisbandReq()
    {
        header.dwType   = CS2DB_GUILDDISBANDREQ;
        header.stLength = sizeof( CS2DBGuildDisbandReq );
    }

    unsigned int nGuildID;
};

struct CS2DBGuildMemberLeaveReq : public MsgGuildModule
{
    CS2DBGuildMemberLeaveReq()
    {
        header.dwType   = CS2DB_GUILDMEMBERLEAVEREQ;
        header.stLength = sizeof( CS2DBGuildMemberLeaveReq );
    }

    unsigned int nPlayerID;
};

///////////////////////////////////////////////////////////////////////////////
struct CS2GSGuildDataList : public MsgGuildModule
{
    CS2GSGuildDataList()
    {
        header.dwType   = CS2GS_GUILDDATALIST;
        header.stLength = sizeof( CS2GSGuildDataList ) - sizeof( xMemberList );
        ustCount = 0;
    }

    enum EConstDefine
    {
        MaxCount = 300,
    };

    GuildDataToServer xData;

    unsigned short ustCount;
    GuildMember xMemberList[ MaxCount ];

    void AddGuildMember( GuildMember& xMember )
    {
        if ( IsFull() )
        { return; }

        xMemberList[ ustCount ] = xMember;

        ++ustCount;
        header.stLength += sizeof( GuildMember );
    }

    bool IsFull() { return ustCount >= MaxCount; }
};

struct CS2GSGuildDataSendSuccess : public MsgGuildModule
{
    CS2GSGuildDataSendSuccess()
    {
        header.dwType   = CS2GS_GUILDDATASENDSUCCESS;
        header.stLength = sizeof( CS2GSGuildDataSendSuccess );
    }
};

struct GS2CSCreateGuildReq : public MsgGuildModule
{
    GS2CSCreateGuildReq()
    {
        header.dwType   = GS2CS_CREATEGUILDREQ;
        header.stLength = sizeof( GS2CSCreateGuildReq );
    }

    unsigned char uchCountry;       // 国家
    char szName[ GuildDefine::MaxCreateLength ];    // 公会名字
	char szAim[ GuildDefine::MaxAimLength ];		// 帮派宗旨
    GuildMember xMember;
};

struct CS2GSCreateGuildAck : public MsgGuildModule
{
    CS2GSCreateGuildAck()
    {
        header.dwType   = CS2GS_CREATEGUILDACK;
        header.stLength = sizeof( CS2GSCreateGuildAck );
    }

    char szPlayer[ GuildDefine::MaxNameLength ];
    GuildDataToServer xGuild;
};


struct GS2CSLeaveGuildReq : public MsgGuildModule
{
    GS2CSLeaveGuildReq()
    {
        header.dwType   = GS2CS_LEAVEGUILDREQ;
        header.stLength = sizeof( GS2CSLeaveGuildReq );
    }

    unsigned int nPlayerID;
    unsigned int nGuildID;
};

struct CS2GSLeaveGuildAck : public MsgGuildModule
{
    CS2GSLeaveGuildAck()
    {
        header.dwType   = CS2GS_LEAVEGUILDACK;
        header.stLength = sizeof( CS2GSLeaveGuildAck );
    }

    unsigned int nPlayerID;
    unsigned int nGuildID;
};

struct GS2CSKickGuildReq : public MsgGuildModule
{
    GS2CSKickGuildReq()
    {
        header.dwType   = GS2CS_KICKGUILDREQ;
        header.stLength = sizeof( GS2CSKickGuildReq );
    }

    unsigned int nPlayerID;
    unsigned int nTargetID;
    unsigned int nGuildID;
};

struct GS2CSInviteGuildReq : public MsgGuildModule
{
    GS2CSInviteGuildReq()
    {
        header.dwType   = GS2CS_INVITEGUILDREQ;
        header.stLength = sizeof( GS2CSInviteGuildReq );
    }

    unsigned int nPlayerID;
    unsigned int nTargetID;
    unsigned int nGuildID;
};

struct GS2CSGuildSQReq : public MsgGuildModule
{
    GS2CSGuildSQReq()
    {
        header.dwType   = GS2CS_GUILDSQREQ;
        header.stLength = sizeof( GS2CSGuildSQReq );
    }
    unsigned int nPlayerID;
    unsigned int nGuildID;
};


struct MsgGuildSQAck : public MsgGuildModule
{
	enum EConstDefine
    {
        const_iMaxNum = 500
    };
	struct SQAtt
	{
		uint32	Level;
		uint32	ID;
		uint16  Profession;
		char	szName[dr_MaxPlayerName];	
	};
    MsgGuildSQAck()
    {
        header.dwType   = MSG_GUILDSQACK;
		Num =0;
    }
	void CaluLength()
    {
        header.stLength = (int)(sizeof( MsgGuildSQAck ) - (const_iMaxNum - Num)*sizeof(SQAtt));
    }
	void pushItem(uint32 ID,uint32 Level,uint16 Profession,const char* Name)
	{
		SQAtt sq;
		sq.ID =ID;
		sq.Level = Level;
		sq.Profession = Profession;
		strcpy_s(sq.szName,dr_MaxPlayerName-1,Name);
		Info[Num] = sq;
		++Num;
	}
    uint32		Num;
	//名称 职业 ID 等级	
	SQAtt		Info[const_iMaxNum];
};

struct GS2CSInviteJoinGuildAck : public MsgGuildModule
{
    GS2CSInviteJoinGuildAck()
    {
        header.dwType   = GS2CS_INVITEJOINGUILDACK;
        header.stLength = sizeof( GS2CSInviteJoinGuildAck );
    }

    bool bAgreeJoin;
    GuildMember xMember;
};

struct CS2GSJoinGuildAck : public MsgGuildModule
{
    CS2GSJoinGuildAck()
    {
        header.dwType   = CS2GS_JOINGUILDACK;
        header.stLength = sizeof( CS2GSJoinGuildAck );
    }

    GuildMember xMember;
};

struct GS2CSJoinGuildReq : public MsgGuildModule
{
    GS2CSJoinGuildReq()
    {
        header.dwType   = GS2CS_JOINGUILDREQ;
        header.stLength = sizeof( GS2CSJoinGuildReq );
    }

    GuildMember xMember;
};

struct GS2CSRequestJoinGuildAck : public MsgGuildModule
{
    GS2CSRequestJoinGuildAck()
    {
        header.dwType   = GS2CS_REQUESTJOINGUILDACK;
        header.stLength = sizeof( GS2CSRequestJoinGuildAck );
    }

    unsigned int nPlayerID;     // 管理人ID
    unsigned int nGuildID;      // 公会ID
    unsigned int nTargetID;     // 申请人ID
    bool bAgreeJoin;
};

struct CS2GSDisbandGuildAck : public MsgGuildModule
{
    CS2GSDisbandGuildAck()
    {
        header.dwType   = GS2CS_DISBANDGUILDACK;
        header.stLength = sizeof( CS2GSDisbandGuildAck );
    }

    unsigned int nGuildID;
};

struct CS2GSMemberDataUpdate : public MsgGuildModule
{
    CS2GSMemberDataUpdate()
    {
        header.dwType   = CS2GS_MEMBERDATAUPDATE;
        header.stLength = sizeof( CS2GSMemberDataUpdate );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned char uchUpdateType;
    unsigned int nUpdateValue;
};

struct CS2GSGuildDataUpdate : public MsgGuildModule
{
    CS2GSGuildDataUpdate()
    {
        header.dwType   = CS2GS_GUILDDATAUPDATE;
        header.stLength = sizeof( CS2GSGuildDataUpdate );
    }

    unsigned int nGuildID;

    unsigned char uchUpdateType;
    __int64 n64UpdateValue;
};

struct GS2CSGuildNoticeChangeReq : public MsgGuildModule
{
    GS2CSGuildNoticeChangeReq()
    {
        header.dwType   = GS2CS_GUILDNOTICECHANGEREQ;
        header.stLength = sizeof( GS2CSGuildNoticeChangeReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    char szNotice[ GuildDefine::MaxNoticeLength ];
};

struct GS2CSGuildAimChangeReq : public MsgGuildModule
{
	GS2CSGuildAimChangeReq()
	{
		header.dwType = GS2CS_GUILDAIMCHANGE;
		header.stLength = sizeof( GS2CSGuildAimChangeReq );
	}

	unsigned int nGuildID;
	unsigned int nPlayerID;

	char szAim[ GuildDefine::MaxAimLength ];
};

struct CS2GSGuildAimChangeAck : public MsgGuildModule
{
	CS2GSGuildAimChangeAck()
	{
		header.dwType   = CS2GS_GUILDAIMCHANGEACK;
		header.stLength = sizeof( CS2GSGuildAimChangeAck );
	}

	unsigned int nGuildID;
	__int64 nChangeAimTime;
	char szAim[ GuildDefine::MaxAimLength ];
};

struct CS2GSGuildNoticeChangeAck : public MsgGuildModule
{
    CS2GSGuildNoticeChangeAck()
    {
        header.dwType   = CS2GS_GUILDNOTICECHANGEACK;
        header.stLength = sizeof( CS2GSGuildNoticeChangeAck );
    }

    unsigned int nGuildID;
    char szNotice[ GuildDefine::MaxNoticeLength ];
};

struct GS2CSGuildResignPositionReq : public MsgGuildModule
{
    GS2CSGuildResignPositionReq()
    {
        header.dwType   = GS2CS_GUILDRESIGNPOSITIONREQ;
        header.stLength = sizeof( GS2CSGuildResignPositionReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct GS2CSGuildTransferPositionReq : public MsgGuildModule
{
    GS2CSGuildTransferPositionReq()
    {
        header.dwType   = GS2CS_GUILDTRANSFERPOSITIONREQ;
        header.stLength = sizeof( GS2CSGuildTransferPositionReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned int nTargetID;
};

struct GS2CSGuildCreateFamilyReq : public MsgGuildModule
{
    GS2CSGuildCreateFamilyReq()
    {
        header.dwType   = GS2CS_GUILDCREATEFAMILYREQ;
        header.stLength = sizeof( GS2CSGuildCreateFamilyReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    char szName[ GuildDefine::MaxFamilyLength ];
};

struct GS2CSGuildFamilyChangeReq : public MsgGuildModule
{
    GS2CSGuildFamilyChangeReq()
    {
        header.dwType   = GS2CS_GUILDFAMILYCHANGEREQ;
        header.stLength = sizeof( GS2CSGuildFamilyChangeReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned char uchFamilyID;
    char szName[ GuildDefine::MaxFamilyLength ];
};

struct CS2GSGuildFamilyChange : public MsgGuildModule
{
    CS2GSGuildFamilyChange()
    {
        header.dwType   = CS2GS_GUILDFAMILYCHANGE;
        header.stLength = sizeof( CS2GSGuildFamilyChange );

        memset( szName, 0, sizeof( szName ) );
    }

    unsigned int nGuildID;
	unsigned int nRequesterID;
    unsigned char uchFamilyID;
    char szName[ GuildDefine::MaxFamilyLength ];
};

struct GS2CSGuildMemberFamilyChangeReq : public MsgGuildModule
{
    GS2CSGuildMemberFamilyChangeReq()
    {
        header.dwType   = GS2CS_GUILDMEMBERFAMILYCHANGEREQ;
        header.stLength = sizeof( GS2CSGuildMemberFamilyChangeReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned int nTargetID;
    unsigned char uchFamilyID;
};

struct GS2CSGuildAssignPositionReq : public MsgGuildModule
{
    GS2CSGuildAssignPositionReq()
    {
        header.dwType   = GS2CS_GUILDASSIGNPOSTIONREQ;
        header.stLength = sizeof( GS2CSGuildAssignPositionReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned int nTargetID;
    unsigned char uchPosition;
};

// 帮派数据请求改变
struct GS2CSGuildDataChangeReq : public MsgGuildModule
{
    GS2CSGuildDataChangeReq()
    {
        header.dwType   = GS2CS_GUILDDATACHANGEREQ;
        header.stLength = sizeof( GS2CSGuildDataChangeReq );
    }

    unsigned int nGuildID;
    unsigned char uchChangeType;

    unsigned char uchOperateType;
    unsigned int nValue;
};

struct GS2CSMemberDataChangeReq : public MsgGuildModule
{
    GS2CSMemberDataChangeReq()
    {
        header.dwType   = GS2CS_MEMBERDATACHANGEREQ;
        header.stLength = sizeof( GS2CSMemberDataChangeReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned char uchChangeType;
    unsigned char uchOperateType;
    unsigned int nValue;
};

// 请求帮派升级
struct GS2CSGuildLevelUpReq : public MsgGuildModule
{
    GS2CSGuildLevelUpReq()
    {
        header.dwType   = GS2CS_GUILDLEVELUPREQ;
        header.stLength = sizeof( GS2CSGuildLevelUpReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

// 请求捐献帮贡
struct GS2CSGuildOfferBuildReq : public MsgGuildModule
{
    GS2CSGuildOfferBuildReq()
    {
        header.dwType   = GS2CS_GUILDOFFEGUILDRREQ;
        header.stLength = sizeof( GS2CSGuildOfferBuildReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct GS2CSGuildCollectReq : public MsgGuildModule
{
    GS2CSGuildCollectReq()
    {
        header.dwType   = GS2CS_GUILDCOLLECTREQ;
        header.stLength = sizeof( GS2CSGuildCollectReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct GS2CSGuildDelateRequestReq : public MsgGuildModule
{
    GS2CSGuildDelateRequestReq()
    {
        header.dwType   = GS2CS_GUILDDELATEREQUESTREQ;
        header.stLength = sizeof( GS2CSGuildDelateRequestReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct CS2GSGuildDelateRequestReq : public MsgGuildModule
{
    CS2GSGuildDelateRequestReq()
    {
        header.dwType   = CS2GS_GUILDDELATEREQUESTREQ;
        header.stLength = sizeof( CS2GSGuildDelateRequestReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct GS2CSGuildDelateAgreeAck : public MsgGuildModule
{
    GS2CSGuildDelateAgreeAck()
    {
        header.dwType   = GS2CS_GUILDDELATEAGREEACK;
        header.stLength = sizeof( GS2CSGuildDelateAgreeAck );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct CS2GSGuildDelateResult : public MsgGuildModule
{
    CS2GSGuildDelateResult()
    {
        header.dwType   = CS2GS_GUILDDELATERESULT;
        header.stLength = sizeof( CS2GSGuildDelateResult );
        bDelateSuccess = false;
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    bool bDelateSuccess;      // 成功 或者 失败
};

struct GS2CSGuildDonateRequestReq : public MsgGuildModule
{
    GS2CSGuildDonateRequestReq()
    {
        header.dwType   = GS2CS_GUILDDONATEREQUESTREQ;
        header.stLength = sizeof( GS2CSGuildDonateRequestReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
};

struct CS2GSGuildDonateRequestReq : public MsgGuildModule
{
    CS2GSGuildDonateRequestReq()
    {
        header.dwType   = CS2GS_GUILDDONATEREQUESTREQ;
        header.stLength = sizeof( CS2GSGuildDonateRequestReq );
    }

    unsigned int nGuildID;
};

struct GS2CSGuildDonateAck : public MsgGuildModule
{
    GS2CSGuildDonateAck()
    {
        header.dwType   = GS2CS_GUILDDONATEACK;
        header.stLength = sizeof( GS2CSGuildDonateAck );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
    unsigned int nMoney;
};

struct GS2CSRaiseGuildPlayerItem : public MsgGuildModule
{
    GS2CSRaiseGuildPlayerItem()
    {
        header.dwType = GS2CS_RAISEGUILDPLAYERITEM;
        header.stLength = sizeof( GS2CSRaiseGuildPlayerItem );

		
    }
	uint32 ItemID;
	uint32 PlayerID;
	SCharItem CItem;
	char szName[dr_MaxPlayerName];
};

struct CS2GSGuildDonateStop : public MsgGuildModule
{
    CS2GSGuildDonateStop()
    {
        header.dwType   = CS2GS_GUILDDONATESTOP;
        header.stLength = sizeof( CS2GSGuildDonateStop );
    }

    unsigned int nGuildID;
};

struct GS2CSGuildQuestReleaseReq : public MsgGuildModule
{
    GS2CSGuildQuestReleaseReq()
    {
        header.dwType   = GS2CS_GUILDQUESTRELEASEREQ;
        header.stLength = sizeof( GS2CSGuildQuestReleaseReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;

    unsigned int nQuestType;
};

struct CS2GSGuildQuestReleaseStatus : public MsgGuildModule
{
    CS2GSGuildQuestReleaseStatus()
    {
        header.dwType   = CS2GS_GUILDQUESTRELEASESTATUS;
        header.stLength = sizeof( CS2GSGuildQuestReleaseStatus );
    }

    unsigned int nGuildID;
    unsigned int nQuestID;  // == 0 表示发布的已经结束了
    __int64 n64RelasetTime;    
};

struct CS2GSGuildClearMemberActivity : public MsgGuildModule
{
    CS2GSGuildClearMemberActivity()
    {
        header.dwType   = CS2GS_GUILDCLEARMEMBERACTIVITY;
        header.stLength = sizeof( CS2GSGuildClearMemberActivity );
    }

    unsigned int nGuildID;
};

struct GS2CSGuildConveneReq : public MsgGuildModule
{
    GS2CSGuildConveneReq()
    {
        header.dwType   = GS2CS_GUILDCONVENEREQ;
        header.stLength = sizeof( GS2CSGuildConveneReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;     // 召集人
    unsigned char uchLevel;     // 帮众的限制等级
    unsigned int nMapID;
    float fPosX;
    float fPosY;
    float fDir;
};

struct CS2GSGuildConveneReq : public MsgGuildModule
{
    CS2GSGuildConveneReq()
    {
        header.dwType   = CS2GS_GUILDCONVENEREQ;
        header.stLength = sizeof( CS2GSGuildConveneReq );
    }

    unsigned int nGuildID;
    unsigned int nPlayerID;
    unsigned char uchLevel;
    unsigned int nMapID;
    float fPosX;
    float fPosY;
    float fDir;
};

struct CS2GSGuildConveneStop : public MsgGuildModule
{
    CS2GSGuildConveneStop()
    {
        header.dwType   = CS2GS_GUILDCONVENESTOP;
        header.stLength = sizeof( CS2GSGuildConveneStop );
    }

    unsigned int nGuildID;
};

struct GS2CSGuildMessage : public MsgGuildModule
{
    GS2CSGuildMessage()
    {
        header.dwType   = GS2CS_GUILDMESSAGE;
        header.stLength = sizeof( GS2CSGuildMessage ) - MaxLength;
        
        memset( szMessage, 0, sizeof( szMessage ) );
    }

    enum EConstDefine
    {
        MaxLength = 1024 * 32,
    };

    unsigned int nGuildID;
    unsigned int nExceptID;
    unsigned short ustLevel;   
    
    char szMessage[ MaxLength ];
    void AddMessage( void* pMessage, unsigned int nLength )
    {
        if ( pMessage == NULL || nLength > MaxLength )
        { return; }

        memcpy_s( szMessage, MaxLength, pMessage, nLength );

        header.stLength += nLength;
    }
};

struct CS2GSGuildMessage : public MsgGuildModule
{
    CS2GSGuildMessage()
    {
        header.dwType   = CS2GS_GUILDMESSAGE;
        header.stLength = sizeof( CS2GSGuildMessage ) - MaxLength;

        memset( szMessage, 0, sizeof( szMessage ) );
    }

    enum EConstDefine
    {
        MaxLength = 1024 * 32,
    };

    unsigned int nGuildID;
    unsigned int nExceptID;
    unsigned short ustLevel;   

    char szMessage[ MaxLength ];
    void AddMessage( void* pMessage, unsigned int nLength )
    {
        if ( pMessage == NULL || nLength > MaxLength )
        { return; }

        memcpy_s( szMessage, MaxLength, pMessage, nLength );

        header.stLength += nLength;
    }
};

//luo.qin 4.20
struct GS2CSPlayerLvUpToThirtyMessage : public MsgGuildModule
{
	GS2CSPlayerLvUpToThirtyMessage()
	{
		header.dwType   = GS2CS_PLAYERLVUPTOTHIRTY;
		header.stLength = sizeof( GS2CSPlayerLvUpToThirtyMessage );
	}

	unsigned int nPlayerID;
	unsigned int nTargetID;
	unsigned int nPlayerLv;
	char szSpeakName[dr_MaxPlayerName]; 
};
struct CS2GSMissionNotEnuoughMessage : public MsgGuildModule
{
	CS2GSMissionNotEnuoughMessage()
	{
		header.dwType   = CS2GS_MISSIONNOTENOUGH;
		header.stLength = sizeof( CS2GSMissionNotEnuoughMessage );
	}
	unsigned int nMissionCount;
	unsigned int nMasterID;

};


struct CS2GSGuildBattleSum : public MsgGuildModule
{
    CS2GSGuildBattleSum()
    {
        header.dwType   = CS2GS_GUILDBATTLESUM;
        header.stLength = sizeof( CS2GSGuildBattleSum );
    }

    unsigned int nGuildID;
	unsigned int battleSum;
};


struct MsgSetGuildCampBattleValue : public MsgGuildModule
{
    MsgSetGuildCampBattleValue()
    {
        header.dwType   = MSG_SETGUILDCAMPBATTLEVALUE;
        header.stLength = sizeof( MsgSetGuildCampBattleValue );
    }
	
	unsigned int TargetID;//目标ID
	unsigned int CampBattleValue;//需要设置的值
	bool		 IsAdd;
};

struct MsgSetGuildCampBattleValueAck : public MsgGuildModule
{
    MsgSetGuildCampBattleValueAck()
    {
        header.dwType   = MSG_SETGUILDCAMPBATTLEVALUEACK;
        header.stLength = sizeof( MsgSetGuildCampBattleValueAck );
    }
	
	unsigned int PlayerID;
	unsigned int ErrorID;//错误信息
};

struct GS2CSSetGuildCampBattleValue : public MsgGuildModule
{
    GS2CSSetGuildCampBattleValue()
    {
        header.dwType   = GS2CS_SETGUILDCAMPBATTLEVALUE;
        header.stLength = sizeof( GS2CSSetGuildCampBattleValue );
    }
	unsigned int GuildID;
	unsigned int PlayerID;
	unsigned int TargetID;//目标ID
	unsigned int CampBattleValue;//需要设置的值
	bool		 IsAdd;
};

struct MsgChangeGuldNameReq : public MsgGuildModule
{
	MsgChangeGuldNameReq()
    {
        header.dwType   = MSG_CHANGEGUILDNAMEREQ;
        header.stLength = sizeof( MsgChangeGuldNameReq );
    }
	unsigned int GuildID;
	char	Name[ GuildDefine::MaxNameLength ];
};

struct GS2CSChangeGuildNameReq : public MsgGuildModule
{
	GS2CSChangeGuildNameReq()
    {
        header.dwType   =  GS2CS_CHANGEGUILDNAMEREQ;
        header.stLength = sizeof( GS2CSChangeGuildNameReq );
    }
	unsigned int GuildID;
	unsigned int PlayerID;
	char	Name[ GuildDefine::MaxNameLength ];
};
struct CS2GSChangeGuildNameAck : public MsgGuildModule
{
	CS2GSChangeGuildNameAck()
    {
        header.dwType   =  CS2GS_CHANGEGUILDNAMEACK;
        header.stLength = sizeof( CS2GSChangeGuildNameAck );
    }
	unsigned int GuildID;
	char	Name[ GuildDefine::MaxNameLength ];
};
struct MsgChangeGuldNameAck : public MsgGuildModule
{
	MsgChangeGuldNameAck()
    {
        header.dwType   = MSG_CHANGEGUILDNAMEACK;
        header.stLength = sizeof( MsgChangeGuldNameAck );
    }
	unsigned int GuildID;
	bool	IsCanChange;
	char	Name[ GuildDefine::MaxNameLength ];
};
struct MsgTellGuildPlayerRaiseItem : public MsgGuildModule
{
	MsgTellGuildPlayerRaiseItem()
    {
        header.dwType   = MSG_TELLGUILDPLAYERAISEITEM;
        header.stLength = sizeof( MsgTellGuildPlayerRaiseItem );
    }
	char	szName[ GuildDefine::MaxNameLength ];
	unsigned short CountryID;
};

struct GS2CSGuildMemberChangeName : public MsgGuildModule
{
    GS2CSGuildMemberChangeName()
    {
        header.dwType = GS2CS_GUILDMEMBERCHANGENAME;
        header.stLength = sizeof( GS2CSGuildMemberChangeName );
    }
    int   PlayerID;
	char  szName[dr_MaxUserName];
	int	  GuildID;
};
struct CS2GSGuildMemberChangeName : public MsgGuildModule
{
    CS2GSGuildMemberChangeName()
    {
        header.dwType = CS2GS_GUILDMEMBERCHANGENAME;
        header.stLength = sizeof( CS2GSGuildMemberChangeName );
    }
    int   PlayerID;
	char  szName[dr_MaxUserName];
	int	  GuildID;
};
struct MsgGuildChangeNameAck : public MsgGuildModule
{
    MsgGuildChangeNameAck()
    {
        header.dwType = MSG_GUILDCHANGENAMEACK;
        header.stLength = sizeof( MsgGuildChangeNameAck );
    }
    int   PlayerID;
	char  szName[dr_MaxUserName];
	int	  GuildID;
};
struct GS2CSUpdateGuildCampBattlePoint : public MsgGuildModule
{
    GS2CSUpdateGuildCampBattlePoint()
    {
        header.dwType = GS2CS_UPDATEGUILDCAMPBATTLEPOINT;
        header.stLength = sizeof( GS2CSUpdateGuildCampBattlePoint );
    }
    unsigned int GuildID;
	unsigned int Point;
};

struct GS2CSUpdateGuildMemberOnLineTime : public MsgGuildModule
{
    GS2CSUpdateGuildMemberOnLineTime()
    {
        header.dwType = GS2CS_UPDATEGUILDMEMBERONLINETIME;
        header.stLength = sizeof( GS2CSUpdateGuildMemberOnLineTime );
    }
    unsigned int GuildID;
	unsigned int PlayerID;
	__int64 OnLineTime;
};
struct CS2GSUpdateGuildMemberOnLineTime : public MsgGuildModule
{
    CS2GSUpdateGuildMemberOnLineTime()
    {
        header.dwType = CS2GS_UPDATEGUILDMEMBERONLINETIME;
        header.stLength = sizeof( CS2GSUpdateGuildMemberOnLineTime );
    }
    unsigned int GuildID;
	unsigned int PlayerID;
	__int64 OnLineTime;
};
struct MsgUpdateGuildMemberOnLineTime : public MsgGuildModule
{
    MsgUpdateGuildMemberOnLineTime()
    {
        header.dwType = MSG_UPDATEGUILDMEMBERONLINETIME;
        header.stLength = sizeof( MsgUpdateGuildMemberOnLineTime );
    }
    unsigned int GuildID;
	unsigned int PlayerID;
	__int64 OnLineTime;
};

#pragma pack( pop )

#endif