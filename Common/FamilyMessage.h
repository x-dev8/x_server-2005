#ifndef __FAMILY_MESSAGE_H__
#define __FAMILY_MESSAGE_H__

#include "MsgBase.h"
#include "MessageRangeDefine.h"
#include "FamilyDefine.h"
#include "GlobalDef.h"


#pragma pack( push, 1 )

enum FamilyMessageDefine
{
	MSG_CREATEFAMILYREQ = GAMEWORD_FAMILYMSG_BEGIN,
	MSG_CREATEFAMILYACK,
	MSG_TELLCREATEFAMILY,
	MSG_TELLJOINFAMILYTOFAMILY,
	MSG_TELLFAMILYINFO,
	MSG_JOINFAMILYREQ,
	MSG_JOINFAMILYACK,
	MSG_TELLJOINFAMILYTOVIEW,
	MSG_INVITEFAMILYREQ,
	MSG_INVITEFAMILYACK,
	MSG_INVITEJOINFAMILYREQ,
	MSG_INVITEJOINFAMILYACK,
	MSG_REQUESTJOINFAMILYREQ,
	MSG_REQUESTJOINFAMILYACK,
	MSG_ALLFAMILYINFOLIST,
	MSG_QUITFAMILYREQ,
	MSG_TELLLEAVEFAMILYTOFAMILY,
	MSG_TELLLEAVEFAMILYTOVIEW,
	MSG_QUITFAMILYACK,
	MSG_KICKOUTFAMILYREQ,
	MSG_FAMILYNOTICEREQ,
	MSG_FAMILYNOTICEACK,
	MSG_TELLFAMILYNOTICEUPDATE,
	MSG_FAMILYTRANSFERREQ,
	MSG_FAMILYTRANSFERACK,
	MSG_TELLFAMILYTRANSFER,
	MSG_TELLVIEW_POSITIONCHANGE,
	MSG_FAMILYDONATEREQ,
	MSG_FAMILYDONATEACK,
	MSG_TELLFAMILYDONATE,
	MSG_FAMILYUPGRADEREQ,
	MSG_FAMILYUPGRADEACK,
	MSG_TELLFAMILYUPGRADE,
	MSG_QUERYFAMILYINFOREQ,
	MSG_QUERYFAMILYINFOACK,
	MSG_TELLFAMILYDISBAND,
	MSG_FAMILYMEMBERDATAUPDATE,
	MSG_TELLCLIENTPROSPERITY,
	MSG_FAMILYAIMREQ,
	MSG_FAMILYAIMACK,

	// 服务器间消息定义
	GS2CS_CREATEFAMILYREQ = CENTERGAME_FAMILY_BEGIN,
	CS2GS_CREATEFAMILYACK,
	CS2GS_JOINFAMILYACK,
	GS2CS_FAMILYMESSAGE,
	CS2GS_FAMILYMESSAGE,
	GS2CS_INVITEFAMILYREQ,
	GS2CS_INVITEJOINFAMILYACK,
	GS2CS_JOINFAMILYREQ,
	GS2CS_REQUESTJOINFAMILYACK,
	GS2CS_QUITFAMILYREQ,
	GS2CS_KICKOUTFAMILYREQ,
	CS2GS_LEAVEFAMILYACK,
	DB2CS_FAMILYDATALIST,
	DB2CS_FAMILYMEMBERLIST,
	CS2DB_FAMILYDATAUPDATEREQ,
	CS2DB_FAMILYMEMBERUPDATEREQ,
	CS2DB_FAMILYMEMBERLEAVEREQ,
	CS2DB_FAMILYDATALOADREQ,
	CS2DB_FAMILYDISBANDREQ,
	CS2GS_ALLFAMILIESSENDEND,
	CS2GS_FAMILYDETAIL,
	GS2CS_FAMILYNOTICEREQ,
	CS2GS_FAMILYNOTICEACK,
	GS2CS_FAMILYTRANSFERREQ,
	CS2GS_FAMILYTRANSFERACK,
	GS2CS_FAMILYDONATEREQ,
	CS2GS_FAMILYDONATEACK,
	GS2CS_FAMILYUPGRADEREQ,
	CS2GS_FAMILYUPGRADEACK,
	CS2GS_TELLFAMILYDISBAND,
	GS2CS_TELLMEMBEROFFLINE,
	GS2CS_FAMILYPLAYERLVTOTEN,
	GS2CS_FAMILYMEMBERDATACHANGEREQ,
	CS2GS_FAMILYMEMBERDATAUPDATE,
	CS2GS_FAMILYPLAYERLVTOTEN,
	CS2GS_FAMILYPROSPERITYUPDATE,
	GS2CS_FAMILYPROSPERITYUPDATE,
	GS2CS_FAMILYAIMREQ,
	CS2GS_FAMILYAIMACK,
};

struct MsgFamilyModule : Msg
{
	MsgFamilyModule()
	{
		SetModuleType( EMessageModule_Family );
	}
};

// 请求创建家族
struct MsgCreateFamilyReq : MsgFamilyModule
{
	MsgCreateFamilyReq()
	{
		header.dwType = MSG_CREATEFAMILYREQ;
		header.stLength = sizeof( MsgCreateFamilyReq );

		memset( szName, 0, sizeof(szName) );
		memset( szAim, 0, sizeof(szAim) );
		nTotem = 0;
	}

	char	szName[ FamilyDefine::MaxFamilyNameLen ];// 家族名字
	char	szAim[ FamilyDefine::MaxFamilyAimLen ];	// 家族宗旨
	unsigned char	nTotem;			// 家族图腾
};

// 回复请求创建家族
struct MsgCreateFamilyAck : public MsgFamilyModule
{
	MsgCreateFamilyAck()
	{
		header.dwType = MSG_CREATEFAMILYACK;
		header.stLength = sizeof( MsgCreateFamilyAck );

		uchResult = ECD_Success;
	}

	enum EConstDefine
	{
		ECD_Success = 0,	// 创建成功
		ECD_ErrorName,		// 存在屏蔽字符, 非法名字, 
		ECD_SaveName,		// 存在相同名字的家族
		ECD_LevelLess,		// 等级不足，不能创建家族
		ECD_NotEnoughMoney,	// 背包金钱不足，不能创建家族
	};

	unsigned char uchResult;
};

// 通知新创建了一个家族
struct MsgTellCreateFamily : public MsgFamilyModule
{
	MsgTellCreateFamily()
	{
		header.dwType = MSG_TELLCREATEFAMILY;
		header.stLength = sizeof( MsgTellCreateFamily );

		nFamilyID = 0;
		memset( szPlayer, 0, sizeof(szPlayer) );
		memset( szName, 0, sizeof(szName) );
	}

	char szPlayer[ FamilyDefine::MaxNameLen ];    // 创建人
	unsigned int nFamilyID;
	unsigned int nProspeprity;
	unsigned int nFamilyLevel;
	unsigned int nMemberCount;
	char szName[ FamilyDefine::MaxFamilyNameLen ];    // 家族名字
};

struct MsgTellJoinFamilyToFamily : MsgFamilyModule
{
	MsgTellJoinFamilyToFamily()
	{
		header.dwType = MSG_TELLJOINFAMILYTOFAMILY;
		header.stLength = sizeof( MsgTellJoinFamilyToFamily );
	}

	FamilyDefine::FamilyMember member;
};

// 发送家族信息给客户端,
struct MsgTellFamilyInfo : public MsgFamilyModule
{
	MsgTellFamilyInfo()
	{
		header.dwType   = MSG_TELLFAMILYINFO;

		ResetMembers();
	}

	enum EConstDefine
	{
		MaxCount = 1024 * 32 / sizeof( FamilyDefine::FamilyMember ),
	};

	FamilyDefine::FamilyInfo info;

	bool bEnd;	// 是否最后一个包
	unsigned short nCount;
	FamilyDefine::FamilyMember members[ MaxCount ];

	bool AddMember( FamilyDefine::FamilyMember& member )
	{
		if ( nCount >= MaxCount )
		{ return false; }

		members[ nCount++ ] = member;
		header.stLength += sizeof( FamilyDefine::FamilyMember );
		
		return true;
	}

	void ResetMembers()
	{
		header.stLength = sizeof( MsgTellFamilyInfo ) - sizeof( members );
		nCount = 0;
		bEnd = true;
	}
};

// 回复加入家族
struct MsgJoinFamilyAck : public MsgFamilyModule
{
	MsgJoinFamilyAck()
	{
		header.dwType = MSG_JOINFAMILYACK;
		header.stLength = sizeof( MsgJoinFamilyAck );

		uchResult = ECD_JoinSuccess;
	}

	enum EConstDefine
	{
		ECD_JoinSuccess,
		ECD_CreateSuccess,
		ECD_AlreadyHaveFamily,   // 对方已经有家族了
		ECD_LevelLess,          // 等级不足
		ECD_TimeLimit,          // 退家族以后24小时内不能加入家族
		ECD_GuildNotExist,      // 申请的家族不存在
		ECD_MemberFull,         // 目标家族成员数已经满了
		ECD_NotAgree,           // 拒绝申请加入
		ECD_NotOnLine,          // 家族管理员都不在线
	};

	unsigned char uchResult;
};

// 通知附近玩家某人加入家族了
struct MsgTellJoinFamilyToView : public MsgFamilyModule
{
	MsgTellJoinFamilyToView()
	{
		header.dwType   = MSG_TELLJOINFAMILYTOVIEW;
		header.stLength = sizeof( MsgTellJoinFamilyToView );
	}

	unsigned int nFamilyID;
};

// 通知附近玩家某人离开家族了
struct MsgTellLeaveFamilyToView : public MsgFamilyModule
{
	MsgTellLeaveFamilyToView()
	{
		header.dwType   = MSG_TELLLEAVEFAMILYTOVIEW;
		header.stLength = sizeof( MsgTellLeaveFamilyToView );
	}

	unsigned int nFamilyID;
};

// 邀请某人进入家族
struct MsgInviteFamilyReq : public MsgFamilyModule
{
	MsgInviteFamilyReq()
	{
		header.dwType   = MSG_INVITEFAMILYREQ;
		header.stLength = sizeof( MsgInviteFamilyReq );
	}

	char szPlayerName[ FamilyDefine::MaxNameLen ];
};

// 回应邀请进入家族
struct MsgInviteFamilyAck : public MsgFamilyModule
{
	MsgInviteFamilyAck()
	{
		header.dwType   = MSG_INVITEFAMILYACK;
		header.stLength = sizeof( MsgInviteFamilyAck );
	}

	enum EConstDefine
	{
		ECD_Success = 0,        // 邀请成功
		ECD_NotHaveFamily,       // 自己没有家族, 
		ECD_NotHaveRight,       // 没有邀请权限
		ECD_NotOnLine,          // 对方不存在 或者不在线 不在线, 
		ECD_AlreadyHaveFamily,   // 对方已经有家族了
		ECD_LevelLess,          // 对方等级不足20级, 不能邀请加入家族
		ECD_MemberFull,         // 成员数已经满了
		ECD_NotAgree,           // 拒绝加入家族
	};

	unsigned char uchResult;
};

// 通知某人, 某人邀请你加入家族
struct MsgInviteJoinFamilyReq : public MsgFamilyModule
{
	MsgInviteJoinFamilyReq()
	{
		header.dwType   = MSG_INVITEJOINFAMILYREQ;
		header.stLength = sizeof( MsgInviteJoinFamilyReq );
	}

	unsigned int nFamilyID;      // 家族ID
	char szInviterName[ FamilyDefine::MaxNameLen ];   // 邀请人的名字
};

// 玩家响应家族邀请到服务器
struct MsgInviteJoinFamilyAck : public MsgFamilyModule
{
	MsgInviteJoinFamilyAck()
	{
		header.dwType   = MSG_INVITEJOINFAMILYACK;
		header.stLength = sizeof( MsgInviteJoinFamilyAck );
	}

	unsigned int nFamilyID;      // 家族ID
	bool bAgreeJoin;            // 是否同意邀请
};

// 玩家申请加入家族
struct MsgJoinFamilyReq : public MsgFamilyModule
{
	MsgJoinFamilyReq()
	{
		header.dwType   = MSG_JOINFAMILYREQ;
		header.stLength = sizeof( MsgJoinFamilyReq );
	}

	unsigned int nFamilyID;      // 家族ID
	char szNote[ FamilyDefine::MaxRequestNoteLen ];	// 留言
};

// 发送消息给家族管理员, 某人申请加入家族
struct MsgRequestJoinFamilyReq : public MsgFamilyModule
{
	MsgRequestJoinFamilyReq()
	{
		header.dwType   = MSG_REQUESTJOINFAMILYREQ;
		header.stLength = sizeof( MsgRequestJoinFamilyReq );
	}

	unsigned int nRequesterID;                      // 申请人的DBID
	char szRequesterName[ FamilyDefine::MaxNameLen ];   // 申请人的名字
	char szNote[ FamilyDefine::MaxRequestNoteLen ];	// 留言
};

// 回馈申请加入家族
struct MsgRequestJoinFamilyAck : public MsgFamilyModule
{
	MsgRequestJoinFamilyAck()
	{
		header.dwType   = MSG_REQUESTJOINFAMILYACK;
		header.stLength = sizeof( MsgRequestJoinFamilyAck );
	}

	unsigned int nPlayerID;      // 申请人的DBID
	bool bAgreeJoin;             // 是否同意加入家族   
};

// 所有家族列表
struct MsgAllFamilyInfoList : public MsgFamilyModule
{
	MsgAllFamilyInfoList()
	{
		header.dwType = MSG_ALLFAMILYINFOLIST;

		Reset();
	}

	enum EConstDefine
	{
		MaxCountPerPack = 1024 * 32 / sizeof( FamilyDefine::FamilySimpleInfo ),
	};

	bool bEnd;	// 是否最后一个包
	unsigned int nFamilyCount;
	FamilyDefine::FamilySimpleInfo infoList[ MaxCountPerPack ];

	void Reset()
	{
		header.stLength = sizeof( MsgAllFamilyInfoList ) - sizeof( infoList );
		nFamilyCount = 0;
		bEnd = true;
	}

	bool AddFamily( const FamilyDefine::FamilySimpleInfo& info )
	{
		if ( nFamilyCount >= MaxCountPerPack )
		{ return false; }

		infoList[ nFamilyCount++ ] = info;
		header.stLength += sizeof( FamilyDefine::FamilySimpleInfo );

		return true;
	}
};

// 退出家族
struct MsgQuitFamilyReq : public MsgFamilyModule
{
	MsgQuitFamilyReq()
	{
		header.dwType = MSG_QUITFAMILYREQ;
		header.stLength = sizeof( MsgQuitFamilyReq );
	}
};

struct MsgQuitFamilyAck : public MsgFamilyModule
{
	MsgQuitFamilyAck()
	{
		header.dwType = MSG_QUITFAMILYACK;
		header.stLength = sizeof( MsgQuitFamilyAck );

	}

	unsigned char uchResult;

};

// 通知某人离开家族
struct MsgTellLeaveFamilyToFamily : public MsgFamilyModule
{
	MsgTellLeaveFamilyToFamily()
	{
		header.dwType = MSG_TELLLEAVEFAMILYTOFAMILY;
		header.stLength = sizeof( MsgTellLeaveFamilyToFamily );
	}

	FamilyDefine::FamilyMember member;
};

// 开除出家族请求
struct MsgKickOutFamilyReq : public MsgFamilyModule
{
	MsgKickOutFamilyReq()
	{
		header.dwType = MSG_KICKOUTFAMILYREQ;
		header.stLength = sizeof( MsgKickOutFamilyReq );
	}

	unsigned int nTargetPlayerID;
};

// 发家族公告
struct MsgFamilyNoticeReq : public MsgFamilyModule
{
	MsgFamilyNoticeReq()
	{
		SetType( MSG_FAMILYNOTICEREQ );
		SetLength( sizeof( MsgFamilyNoticeReq ) );
	}

	char szNotice[ FamilyDefine::MaxFamilyNoticeLen ];
};

// 回复发家族公告
struct MsgFamilyNoticeAck : public MsgFamilyModule
{
	MsgFamilyNoticeAck()
	{
		SetType( MSG_FAMILYNOTICEACK );
		SetLength( sizeof( MsgFamilyNoticeAck ) );
	}

	enum EConstDefine
	{
		ECD_Success = 0,
		ECD_ErrorNotice,
	};

	unsigned char uchResult;
};

// 通知公告更新
struct MsgTellFamilyNoticeUpdate : public MsgFamilyModule
{
	MsgTellFamilyNoticeUpdate()
	{
		SetType( MSG_TELLFAMILYNOTICEUPDATE );
		SetLength( sizeof( MsgTellFamilyNoticeUpdate ) );
	}

	char szNotice[ FamilyDefine::MaxFamilyNoticeLen ];
};

// 请求转让职位
struct MsgFamilyTransferReq : public MsgFamilyModule
{
	MsgFamilyTransferReq()
	{
		SetType( MSG_FAMILYTRANSFERREQ );
		SetLength( sizeof( MsgFamilyTransferReq ) );
	}

	unsigned int nTargetPlayerID;
};

// 回复转让职位
struct MsgFamilyTransferAck : public MsgFamilyModule
{
	MsgFamilyTransferAck()
	{
		SetType( MSG_FAMILYTRANSFERACK );
		SetLength( sizeof( MsgFamilyTransferAck ) );
	}

	enum EConstDefine
	{
		ECD_Success = 0,
		ECD_NoRight,		// 没有转让职位的权限
		ECD_TargetNull,		// 目标离线或者不存在
	};

	unsigned char uchResult;
};


// 通知转让职位
struct MsgTellFamilyTransfer : public MsgFamilyModule
{
	MsgTellFamilyTransfer()
	{
		SetType( MSG_TELLFAMILYTRANSFER );
		SetLength( sizeof( MsgTellFamilyTransfer ) );
	}

	unsigned int nRequesterID;
	unsigned int nTargetPlayerID;
	unsigned char nPosition;
};

// 通知视野范围内的玩家，目标家族职位头顶显示的变化
struct MsgTellViewPositionChange : public MsgFamilyModule
{
	MsgTellViewPositionChange()
	{
		SetType( MSG_TELLVIEW_POSITIONCHANGE );
		SetLength( sizeof( MsgTellViewPositionChange ) );
	}

	unsigned int nPlayerID;
	unsigned char nPosition;
};

// 捐金
struct MsgFamilyDonateReq : public MsgFamilyModule
{
	MsgFamilyDonateReq()
	{
		SetType( MSG_FAMILYDONATEREQ );
		SetLength( sizeof( MsgFamilyDonateReq ) );
	}

	unsigned int nMoney;
};

// 回复捐金
struct MsgFamilyDonateAck : public MsgFamilyModule
{
	MsgFamilyDonateAck()
	{
		SetType( MSG_FAMILYDONATEACK );
		SetLength( sizeof( MsgFamilyDonateAck ) );
	}

	enum EConstDefine
	{
		ECD_Success = 0,
		ECD_MaxFamilyMoney,
		ECD_NoEnoughMoney,
	};

	unsigned char uchResult;
};

// 通知捐金
struct MsgTellFamilyDonate : public MsgFamilyModule
{
	MsgTellFamilyDonate()
	{
		SetType( MSG_TELLFAMILYDONATE );
		SetLength( sizeof( MsgTellFamilyDonate ) );
	}

	unsigned int nMemberID;
	unsigned int nMoney;
};

// 家族升级
struct MsgFamilyUpgradeReq : public MsgFamilyModule
{
	MsgFamilyUpgradeReq()
	{
		SetType( MSG_FAMILYUPGRADEREQ );
		SetLength( sizeof( MsgFamilyUpgradeReq ) );
	}
};

// 回复家族升级
struct MsgFamilyUpgradeAck : public MsgFamilyModule
{
	MsgFamilyUpgradeAck()
	{
		SetType( MSG_FAMILYUPGRADEACK );
		SetLength( sizeof( MsgFamilyUpgradeAck ) );
	}

	enum EConstDefine
	{
		ECD_Success = 0,
		ECD_UpgradeError,
	};

	unsigned char uchResult;
};

// 通知家族升级
struct MsgTellFamilyUpgrade : public MsgFamilyModule
{
	MsgTellFamilyUpgrade()
	{
		SetType( MSG_TELLFAMILYUPGRADE );
		SetLength( sizeof( MsgTellFamilyUpgrade ) );
	}

	unsigned int		    nMemberID;
	unsigned int	  nNewFamilyLevel;
	unsigned int	  nNewFamilyMoney;
	unsigned int nNewFamilyProsperity;
};

// 请求查询家族详细信息
struct MsgQueryFamilyInfoReq : public MsgFamilyModule
{
	MsgQueryFamilyInfoReq()
	{
		SetType( MSG_QUERYFAMILYINFOREQ );
		SetLength( sizeof( MsgQueryFamilyInfoReq ) );
	}

	unsigned int nFamilyID;
};

// 回复请求查询家族详细信息
struct MsgQueryFamilyInfoAck : public MsgFamilyModule
{
	MsgQueryFamilyInfoAck()
	{
		SetType( MSG_QUERYFAMILYINFOACK );
		SetLength( sizeof( MsgQueryFamilyInfoAck ) );

		memset( szLeaderName, 0, sizeof( szLeaderName ) );
	}

	FamilyDefine::FamilyInfo				 info;
	char szLeaderName[ FamilyDefine::MaxNameLen ];
	unsigned int						nLeaderLv;
	unsigned char						nPosition;
	bool							  bLeadOnLine;
};

// 通知家族解除
struct MsgTellFamilyDisband : public MsgFamilyModule
{
	MsgTellFamilyDisband()
	{
		SetType( MSG_TELLFAMILYDISBAND );
		SetLength( sizeof( MsgTellFamilyDisband ) );
	}

	unsigned int nFamilyID;
};

//////////////////////////////////////////////////////////////////////////

struct GS2CSCreateFamilyReq : public MsgFamilyModule
{
	GS2CSCreateFamilyReq()
	{
		header.dwType = GS2CS_CREATEFAMILYREQ;
		header.stLength = sizeof( GS2CSCreateFamilyReq );

		memset( szFamilyName, 0, sizeof(szFamilyName) );
		memset( szAim, 0, sizeof(szAim) );
		nTotem = 0;
	}

	char szFamilyName[ FamilyDefine::MaxFamilyNameLen ];
	char szAim[ FamilyDefine::MaxFamilyAimLen ];
	unsigned char nTotem;
	FamilyDefine::FamilyMember member;
};

struct CS2GSCreateFamilyAck : public MsgFamilyModule
{
	CS2GSCreateFamilyAck()
	{
		header.dwType   = CS2GS_CREATEFAMILYACK;
		header.stLength = sizeof( CS2GSCreateFamilyAck );
	}

	char szPlayer[ FamilyDefine::MaxNameLen ];
	FamilyDefine::ServerFamilyInfo familyInfo;
};

struct CS2GSJoinFamilyAck : public MsgFamilyModule
{
	CS2GSJoinFamilyAck()
	{
		header.dwType = CS2GS_JOINFAMILYACK;
		header.stLength = sizeof( CS2GSJoinFamilyAck );
	}

	FamilyDefine::FamilyMember member;
};

struct GS2CSFamilyMessage : public MsgFamilyModule
{
	GS2CSFamilyMessage()
	{
		header.dwType   = GS2CS_FAMILYMESSAGE;
		header.stLength = sizeof( GS2CSFamilyMessage ) - MaxLength;

		memset( szMessage, 0, sizeof( szMessage ) );
		nFamilyID = 0;
		nLevel = 0;
		nExceptID = FamilyDefine::InitFamilyID;
	}

	enum EConstDefine
	{
		MaxLength = 1024 * 32,
	};

	unsigned int nFamilyID;
	unsigned int nExceptID;
	unsigned short nLevel;   
	char szMessage[ MaxLength ];

	void AddMessage( void* pMessage, unsigned int nLength )
	{
		if ( pMessage == NULL || nLength > MaxLength )
		{ return; }

		memcpy_s( szMessage, MaxLength, pMessage, nLength );

		header.stLength += nLength;
	}
};

struct CS2GSFamilyMessage : public MsgFamilyModule
{
	CS2GSFamilyMessage()
	{
		header.dwType   = CS2GS_FAMILYMESSAGE;
		header.stLength = sizeof( CS2GSFamilyMessage ) - MaxLength;

		memset( szMessage, 0, sizeof( szMessage ) );
		nFamilyID = 0;
		nLevel = 0;
		nExceptID = FamilyDefine::InitFamilyID;
	}

	enum EConstDefine
	{
		MaxLength = 1024 * 32,
	};

	unsigned int nFamilyID;
	unsigned int nExceptID;
	unsigned short nLevel;   
	char szMessage[ MaxLength ];

	void AddMessage( void* pMessage, unsigned int nLength )
	{
		if ( pMessage == NULL || nLength > MaxLength )
		{ return; }

		memcpy_s( szMessage, MaxLength, pMessage, nLength );

		header.stLength += nLength;
	}
};


struct GS2CSInviteFamilyReq : public MsgFamilyModule
{
	GS2CSInviteFamilyReq()
	{
		header.dwType = GS2CS_INVITEFAMILYREQ;
		header.stLength = sizeof( GS2CSInviteFamilyReq );
	}

	unsigned int nInviterID;
	unsigned int nInviteeID;
	unsigned int nFamilyID;
};

struct GS2CSInviteJoinFamilyAck : public MsgFamilyModule
{
	GS2CSInviteJoinFamilyAck()
	{
		header.dwType = GS2CS_INVITEJOINFAMILYACK;
		header.stLength = sizeof( GS2CSInviteJoinFamilyAck );
	}

	bool bAgree;
	FamilyDefine::FamilyMember member;
};

struct GS2CSJoinFamilyReq : public MsgFamilyModule
{
	GS2CSJoinFamilyReq()
	{
		header.dwType = GS2CS_JOINFAMILYREQ;
		header.stLength = sizeof( GS2CSJoinFamilyReq );
	}

	FamilyDefine::FamilyMember member;
	char szNote[ FamilyDefine::MaxRequestNoteLen ];	// 留言
};

struct GS2CSRequestJoinFamilyAck : public MsgFamilyModule
{
	GS2CSRequestJoinFamilyAck()
	{
		header.dwType = GS2CS_REQUESTJOINFAMILYACK;
		header.stLength = sizeof( GS2CSRequestJoinFamilyAck );
	}

	unsigned int nRequesterID;
	unsigned int nRequesteeID;
	unsigned int nFamilyID;
	bool bAgreeJoin;
};

struct GS2CSQuitFamilyReq : MsgFamilyModule
{
	GS2CSQuitFamilyReq()
	{
		header.dwType = GS2CS_QUITFAMILYREQ;
		header.stLength = sizeof( GS2CSQuitFamilyReq );
	}

	unsigned int nRequesterID;
	unsigned int nFamilyID;
};

struct GS2CSKickOutFamilyReq : MsgFamilyModule
{
	GS2CSKickOutFamilyReq()
	{
		header.dwType = GS2CS_KICKOUTFAMILYREQ;
		header.stLength = sizeof( GS2CSKickOutFamilyReq );
	}

	unsigned int nRequesterID;
	unsigned int nTargetPlayerID;
	unsigned int nFamilyID;
};

struct GS2CSFamilyNoticeReq : public MsgFamilyModule
{
	GS2CSFamilyNoticeReq()
	{
		SetType( GS2CS_FAMILYNOTICEREQ );
		SetLength( sizeof( GS2CSFamilyNoticeReq ) );
	}

	unsigned int nRequesterID;
	unsigned int nFamilyID;
	char szNotice[ FamilyDefine::MaxFamilyNoticeLen ];
};

struct CS2GSFamilyNoticeAck : public MsgFamilyModule
{
	CS2GSFamilyNoticeAck()
	{
		SetType( CS2GS_FAMILYNOTICEACK );
		SetLength( sizeof( CS2GSFamilyNoticeAck ) );
	}

	unsigned int nFamilyID;
	char szNotice[ FamilyDefine::MaxFamilyNoticeLen ];
};

struct GS2CSFamilyTransferReq : public MsgFamilyModule
{
	GS2CSFamilyTransferReq()
	{
		SetType( GS2CS_FAMILYTRANSFERREQ );
		SetLength( sizeof( GS2CSFamilyTransferReq ) );
	}

	unsigned int nFamilyID;
	unsigned int nRequesterID;
	unsigned int nTargetPlayerID;
};

struct CS2GSFamilyTransferAck : public MsgFamilyModule
{
	CS2GSFamilyTransferAck()
	{
		SetType( CS2GS_FAMILYTRANSFERACK );
		SetLength( sizeof( CS2GSFamilyTransferAck ) );
	}

	unsigned int nFamilyID;
	unsigned int nRequesterID;
	unsigned int nTargetPlayerID;
};

struct GS2CSFamilyDonateReq : public MsgFamilyModule
{
	GS2CSFamilyDonateReq()
	{
		SetType( GS2CS_FAMILYDONATEREQ );
		SetLength( sizeof( GS2CSFamilyDonateReq ) );
	}

	unsigned int nFamilyID;
	unsigned int nRequesterID;
	unsigned int nMoney;
};

struct CS2GSFamilyDonateAck : public MsgFamilyModule
{
	CS2GSFamilyDonateAck()
	{
		SetType( CS2GS_FAMILYDONATEACK );
		SetLength( sizeof( CS2GSFamilyDonateAck ) );
	}

	unsigned int nFamilyID;
	unsigned int nRequesterID;
	unsigned int nMoney;
};

struct GS2CSFamilyUpgradeReq : public MsgFamilyModule
{
	GS2CSFamilyUpgradeReq()
	{
		SetType( GS2CS_FAMILYUPGRADEREQ );
		SetLength( sizeof( GS2CSFamilyUpgradeReq ) );
	}

	unsigned int nFamilyID;
	unsigned int nRequesterID;
};

struct CS2GSFamilyUpgradeAck : public MsgFamilyModule
{
	CS2GSFamilyUpgradeAck()
	{
		SetType( CS2GS_FAMILYUPGRADEACK );
		SetLength( sizeof( CS2GSFamilyUpgradeAck ) );
	}

	unsigned int nRequesterID;
	unsigned int nFamilyID;
	unsigned int nNewLevel;
	unsigned int nNewMoney;
	unsigned int nNewProsperity;
};

struct CS2GSLeaveFamilyAck : public MsgFamilyModule
{
	CS2GSLeaveFamilyAck()
	{
		header.dwType = CS2GS_LEAVEFAMILYACK;
		header.stLength = sizeof( CS2GSLeaveFamilyAck );
	}

	FamilyDefine::FamilyMember member;
	uint8 uType;
};

struct DB2CSFamilyDataList : public MsgFamilyModule
{
	DB2CSFamilyDataList()
	{
		SetType( DB2CS_FAMILYDATALIST );

		Reset();
	}

	enum EConstDefine
	{
		MaxLoadCount = 500,
	};

	unsigned int nCount;
	FamilyDefine::ServerFamilyInfo infoList[ MaxLoadCount ];

	bool AddFamilyInfo( const FamilyDefine::ServerFamilyInfo& info )
	{
		if ( nCount >= MaxLoadCount )
		{ return false; }

		infoList[ nCount++ ] = info;
		SetLength( GetLength() + sizeof( info ) );

		return true;
	}

	void Reset()
	{
		SetLength( sizeof( DB2CSFamilyDataList ) - sizeof( infoList ) );
		nCount = 0;
	}
};

struct DB2CSFamilyMemberList : public MsgFamilyModule
{
	DB2CSFamilyMemberList()
	{
		SetType( DB2CS_FAMILYMEMBERLIST );

		Reset();
	}

	enum EConstDefine
	{
		MaxLoadCount = 500,
	};

	bool bTheLastPack;
	unsigned int nCount;
	FamilyDefine::FamilyMember memberList[ MaxLoadCount ];

	bool AddMember( const FamilyDefine::FamilyMember& member )
	{
		if ( nCount >= MaxLoadCount )
		{ return false; }

		memberList[ nCount++ ] = member;
		SetLength( GetLength() + sizeof( FamilyDefine::FamilyMember ) );

		return true;
	}

	void Reset()
	{
		SetLength( sizeof( DB2CSFamilyMemberList ) - sizeof( memberList ) );
		nCount = 0;
		bTheLastPack = true;
	}
};

struct CS2DBFamilyDataUpdateReq : public MsgFamilyModule
{
	CS2DBFamilyDataUpdateReq()
	{
		SetType( CS2DB_FAMILYDATAUPDATEREQ );
		SetLength( sizeof( CS2DBFamilyDataUpdateReq ) );
	}

	FamilyDefine::ServerFamilyInfo info;
};

struct CS2DBFamilyMemberUpdateReq : public MsgFamilyModule
{
	CS2DBFamilyMemberUpdateReq()
	{
		SetType( CS2DB_FAMILYMEMBERUPDATEREQ );
		Reset();
	}

	enum EConstDefine
	{
		MaxLoadCount = 500,
	};

	unsigned int nCount;
	FamilyDefine::FamilyMember memberList[ MaxLoadCount ];

	bool AddMember( const FamilyDefine::FamilyMember& member )
	{
		if ( nCount >= MaxLoadCount )
		{ return false; }

		memberList[ nCount++ ] = member;
		SetLength( GetLength() + sizeof( FamilyDefine::FamilyMember ) );

		return true;
	}

	void Reset()
	{
		SetLength( sizeof( CS2DBFamilyMemberUpdateReq ) - sizeof( memberList ) );
		nCount = 0;
	}
};

struct CS2DBFamilyMemberLeaveReq : public MsgFamilyModule
{
	CS2DBFamilyMemberLeaveReq()
	{
		SetType( CS2DB_FAMILYMEMBERLEAVEREQ );
		SetLength( sizeof( CS2DBFamilyMemberLeaveReq ) );
	}

	unsigned int nPlayerID;
};

struct CS2DBFamilyDataLoadReq : public MsgFamilyModule
{
	CS2DBFamilyDataLoadReq()
	{
		SetType( CS2DB_FAMILYDATALOADREQ );
		SetLength( sizeof( CS2DBFamilyDataLoadReq ) );
	}

	unsigned int nFamilyID;
};

struct CS2DBFamilyDisbandReq : public MsgFamilyModule
{
	CS2DBFamilyDisbandReq()
	{
		SetType( CS2DB_FAMILYDISBANDREQ );
		SetLength( sizeof( CS2DBFamilyDisbandReq ) );
	}

	unsigned int nFamilyID;
};

struct CS2GSAllFamiliesSendEnd : public MsgFamilyModule
{
	CS2GSAllFamiliesSendEnd()
	{
		SetType( CS2GS_ALLFAMILIESSENDEND );
		SetLength( sizeof( CS2GSAllFamiliesSendEnd ) );
	}
};

struct CS2GSFamilyDetail : public MsgFamilyModule
{
	CS2GSFamilyDetail()
	{
		SetType( CS2GS_FAMILYDETAIL );

		ResetMembers();
	}

	enum EConstDefine
	{
		MaxCount = 1024 * 32 / sizeof( FamilyDefine::FamilyMember ),
	};

	FamilyDefine::ServerFamilyInfo info;

	bool bEnd;	// 是否最后一个包
	unsigned short nCount;
	FamilyDefine::FamilyMember members[ MaxCount ];

	bool AddMember( FamilyDefine::FamilyMember& member )
	{
		if ( nCount >= MaxCount )
		{ return false; }

		members[ nCount++ ] = member;
		header.stLength += sizeof( FamilyDefine::FamilyMember );

		return true;
	}

	void ResetMembers()
	{
		header.stLength = sizeof( CS2GSFamilyDetail ) - sizeof( members );
		nCount = 0;
		bEnd = true;
	}
};

struct CS2GSTellFamilyDisband : public MsgFamilyModule
{
	CS2GSTellFamilyDisband()
	{
		SetType( CS2GS_TELLFAMILYDISBAND );
		SetLength( sizeof( CS2GSTellFamilyDisband ) );
	}

	unsigned int nFamilyID;
};

struct GS2CSTellMemberOffline : public MsgFamilyModule
{
	GS2CSTellMemberOffline()
	{
		SetType( GS2CS_TELLMEMBEROFFLINE );
		SetLength( sizeof( GS2CSTellMemberOffline ) );
	}

	unsigned int nFamilyID;
	unsigned int nPlayerID;
};

struct GS2CSFamilyPlayerLvUpToTenMessage : public MsgFamilyModule
{
	GS2CSFamilyPlayerLvUpToTenMessage()
	{
		SetType( GS2CS_FAMILYPLAYERLVTOTEN );
		SetLength( sizeof( GS2CSFamilyPlayerLvUpToTenMessage ) );
	}

	unsigned int nPlayerID;
	unsigned int nTargetID;
	unsigned int nPlayerLv;
	char szSpeakName[dr_MaxPlayerName]; 
};

struct GS2CSFamilyMemberDataChangeReq : public MsgFamilyModule
{
	GS2CSFamilyMemberDataChangeReq()
	{
		header.dwType   = GS2CS_FAMILYMEMBERDATACHANGEREQ;
		header.stLength = sizeof( GS2CSFamilyMemberDataChangeReq );
	}

	unsigned int nFamilyID;
	unsigned int nPlayerID;

	unsigned char uchChangeType;
	unsigned char uchOperateType;
	unsigned int nValue;
};
// 更新帮派成员信息到客户端
struct MsgFamilyMemberDataUpdate : public MsgFamilyModule
{
	MsgFamilyMemberDataUpdate()
	{
		header.dwType   = MSG_FAMILYMEMBERDATAUPDATE;
		header.stLength = sizeof( MsgFamilyMemberDataUpdate );
	}

	unsigned int nPlayerID;				// 成员ID

	unsigned char uchUpdateType;        // 定义在FamilyDefine.h中    UpdateMemberOnLine....
	unsigned int nUpdateValue;
};
struct CS2GSFamilyMemberDataUpdate : public MsgFamilyModule
{
	CS2GSFamilyMemberDataUpdate()
	{
		header.dwType   = CS2GS_FAMILYMEMBERDATAUPDATE;
		header.stLength = sizeof( CS2GSFamilyMemberDataUpdate );
	}

	unsigned int nFamilyID;
	unsigned int nPlayerID;

	unsigned char uchUpdateType;
	unsigned int nUpdateValue;
};

struct CS2GSFamilyProsperityUpdate : public MsgFamilyModule
{
	CS2GSFamilyProsperityUpdate()
	{
		header.dwType   = CS2GS_FAMILYPROSPERITYUPDATE;
		header.stLength = sizeof( CS2GSFamilyProsperityUpdate );
	}

	unsigned int nFamilyID;				// 成员ID
	unsigned int nProsperity;
};

struct GS2CSFamilyProsperityUpdate : public MsgFamilyModule
{
	GS2CSFamilyProsperityUpdate()
	{
		header.dwType   = GS2CS_FAMILYPROSPERITYUPDATE;
		header.stLength = sizeof( GS2CSFamilyProsperityUpdate );
	}

	unsigned int nFamilyID;				// 成员ID
	unsigned int nProsperity;
};

struct MsgTellClientProsperity : public MsgFamilyModule
{
	MsgTellClientProsperity()
	{
		header.dwType   = MSG_TELLCLIENTPROSPERITY;
		header.stLength = sizeof( MsgTellClientProsperity );
	}
	unsigned int nProsperity;
};

// 发家族宗旨
struct MsgFamilyAimReq : public MsgFamilyModule
{
	MsgFamilyAimReq()
	{
		SetType( MSG_FAMILYAIMREQ );
		SetLength( sizeof( MsgFamilyAimReq ) );
	}

	char szAim[ FamilyDefine::MaxFamilyAimLen ];
};

// 回复发家族宗旨
struct MsgFamilyAimAck : public MsgFamilyModule
{
	MsgFamilyAimAck()
	{
		SetType( MSG_FAMILYAIMACK );
		SetLength( sizeof( MsgFamilyAimAck ) );
	}

	enum EConstDefine
	{
		ECD_Success = 0,
		ECD_ErrorAim,
		ECD_TimeLimit,				// 一周之内只能更新一次
		ECD_NotEnoughMoney,			// 没有足够的金钱更改宗旨
	};

	unsigned char uchResult;
};

struct GS2CSFamilyAimReq : public MsgFamilyModule
{
	GS2CSFamilyAimReq()
	{
		SetType( GS2CS_FAMILYAIMREQ );
		SetLength( sizeof( GS2CSFamilyAimReq ) );
	}

	unsigned int nRequesterID;
	unsigned int nFamilyID;
	char szAim[ FamilyDefine::MaxFamilyAimLen ];
};

struct CS2GSFamilyAimAck : public MsgFamilyModule
{
	CS2GSFamilyAimAck()
	{
		SetType( CS2GS_FAMILYAIMACK );
		SetLength( sizeof( CS2GSFamilyAimAck ) );
	}

	unsigned int nFamilyID;
	__int64 nChangeAimTime;
	char szAim[ FamilyDefine::MaxFamilyAimLen ];
};

#pragma pack( pop )

#endif