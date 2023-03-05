#ifndef __FAMILY_DEFINE_H__
#define __FAMILY_DEFINE_H__

#include <string.h>


namespace FamilyDefine
{
	// 家族常量定义
	enum EConstDefine
	{
		MaxNameLen = 33,			// 成员名长度限制
		MaxFamilyNameLen = 17,		// 家族名长度限制
		MaxFamilyAimLen = 401,		// 家族宗旨长度限制
		MaxFamilyNoticeLen = 401,	// 家族公告长度限制
		MaxRequestNoteLen = 161,	// 申请留言长度限制

		MaxFamilyMoney = 2000000000,// 家族资金上限
		MaxFamilyProsperity = 2000000000,	// 家族繁荣度上限

		InitFamilyID = 0,	// 初始化的家族ID
		FirstFamilyID = 1,	// 起始家族ID

		InvalidFamilyDisbandTime = 0,// 无效的家族解散时间
		UpdateSpace = 10000,
		LoadSpaceTime = 1000000,
		SaveSpaveTime = 300000,
		InviteKeepTime = 90000,		// 邀请时效
		RequestKeepTime = 90000,	// 申请时效

		//////////////////////////////////////////////////////////////////////////
		UpdateNormal = 0,
		UpdateDiaband,
		//////////////////////////////////////////////////////////////////////////

		// 成员信息更新标志
		UpdateMemberOnLine = 1,     // 更新在线
		UpdateMemberLevel,          // 更新等级
		UpdateMemberPosition,       // 更新职位
		UpdateMemberProfession,     // 更新职业
		UpdateMemberExp,            // 更新玩家经验( 客户端不用处理 )
		UpdateMemberDonateMoney,	// 更新玩家捐金

		// 家族息更新标记 
		UpdateFamilyLevel = 1,       // 更新帮派等级
		UpdateFamilyLeader,          // 更新帮派帮主
		UpdateFamilyDonate,          // 更新帮派捐献的金钱( 客户端不用处理 )
		UpdateFamilyDisbandTime,     // 更新帮派解散时间

		////////////////////////////////////////////////////////////////
		OperateAdd = 1,             // +
		OperateSub,                 // -
		OperateSet,                 // =
		////////////////////////////////////////////////////////////////

		// 家族权限
		Right_None		= 0,		// 无
		Right_Accept	= 1 << 0,	// 接受加入家族申请
		Right_Kick		= 1 << 1,	// 开除出家族
		Right_LevelUp	= 1 << 2,	// 家族升级
		Right_Transfer	= 1 << 3,	// 转让职位
		Right_Invite	= 1 << 4,	// 邀请玩家加入家族
		Right_Activity	= 1 << 5,	// 开启活动
		Right_LeaveMsg	= 1 << 6,	// 留言
		Right_Leave		= 1 << 7,	// 退出家族

		// 家族职位
		Position_None = 0,	// 无
		Position_Member,	// 成员
		Position_Leader,	// 族长

		// 职位权限
		Right_Member = Right_Leave,
		Right_Leader = Right_Accept | Right_Kick | Right_LevelUp | Right_Transfer | Right_Invite | Right_Activity | Right_LeaveMsg,

		// 家族图腾
		Totem_Human = 0,	// 人
		Totem_Machine,		// 机
		Totem_Monster,		// 兽
		Totem_Immortal,		// 仙
		Totem_Ghost,		// 鬼
		Totem_Goblin,		// 妖
		Totem_God,			// 神
		Totem_Demon,		// 魔

		//////////////////////////////////////////////////////////////////////////
		DecodeFieldBufferSize = 1024 * 10,
		UnZipTempBufferSize   = 1024 * 20,
		ZipTempBufferSize     = 1024 * 40,
		EncodeFieldBufferSize = 1024 * 10,
		//////////////////////////////////////////////////////////////////////////

		PlayerLvIsTen	= 10,		//玩家升到10级，通知给所有的家族族长

		Enum_Leave_Self	= 0,		// 自己退出家族
		Enum_Leave_Kicked,			// 被族长踢出家族
		Enum_Family_Disbanded,		// 家族被解散，玩家被剔除

	};

	static unsigned int GetRightByPositon( unsigned char nPositon )
	{
		unsigned int nRight = Position_None;
		switch ( nPositon )
		{
		case Position_Member:
			nRight = Right_Member;
			break;
		case Position_Leader:
			nRight = Right_Leader;
			break;
		}

		return nRight;
	}

	// 家族成员
	class FamilyMember
	{
	public:
		FamilyMember()
		{
			memset( this, 0, sizeof(*this) );
			_bFirstEnterWorld = true;
		}

		unsigned int	GetID() const	{ return _nID; }
		void	SetID( unsigned int nID )	{ _nID = nID; }

		const char*	GetName() const	{ return _szName; }
		void	SetName( const char* szName )	{ strncpy_s( _szName, sizeof(_szName), szName, sizeof(_szName) - 1 ); }

		unsigned short	GetLevel() const	{ return _nLevel; }
		void	SetLevel( unsigned short nLevel )	{ _nLevel = nLevel; }

		unsigned char	GetProfession() const	{ return _nProfession; }
		void	SetProfession( unsigned char nProfession )	{ _nProfession = nProfession; }

		unsigned int	GetFamilyID() const	{ return _nFamilyID; }
		void	SetFamilyID( unsigned int nFamilyID )	{ _nFamilyID = nFamilyID; }

		unsigned char	GetPosition() const	{ return _nPosition; }
		void	SetPosition( unsigned char nPosition )	{ _nPosition = nPosition; }

		bool	GetOnLine() const	{ return _bOnLine; }
		void	SetOnline( bool bOnline )	{ _bOnLine = bOnline; }

		unsigned int	GetDonateMoney() const	{ return _nDonateMoney; }
		void	SetDonateMoney( unsigned int nValue )	{ _nDonateMoney = nValue; }

		bool	GetbFirstEnterWorld() const { return _bFirstEnterWorld; }
		void	SetbFirstEnterWorld( bool bFirstEnterWorld ) { _bFirstEnterWorld = bFirstEnterWorld; }

	private:
		unsigned int	_nID;					// ID
		char			_szName[ MaxNameLen ];	// 名字
		unsigned short	_nLevel;				// 等级
		unsigned char	_nProfession;			// 职业  
		unsigned int	_nFamilyID;				// 家族ID
		unsigned char	_nPosition;				// 家族职位
		bool			_bOnLine;				// 是否在线
		unsigned int	_nDonateMoney;			// 捐金
		bool			_bFirstEnterWorld;		// 是否是第一次进入游戏	，不存数据库
	};

	// 家族基本信息
	class FamilyInfo
	{
	public:
		FamilyInfo()
		{
			memset( this, 0, sizeof(*this) );
			_nID = InitFamilyID;
		}

		unsigned int	GetFamilyID() const	{ return _nID; }
		void	SetFamilyID( unsigned int nID )	{ _nID = nID;}

		unsigned char	GetFamilyLevel() const	{ return _nLevel; }
		void	SetFamilyLevel( unsigned char nLevel )	{ _nLevel = nLevel; }

		const char*	GetFamilyName() const	{ return _szName; }
		void	SetFamilyName( const char* szName )	{ strncpy_s( _szName, sizeof( _szName ), szName, sizeof( _szName ) - 1 ); }

		const char*	GetFamilyAim() const	{ return _szAim; }
		void	SetFamilyAim( const char* szAim )	{ strncpy_s( _szAim, sizeof( _szAim ), szAim, sizeof( _szAim ) - 1 ); }

		unsigned char	GetFamilyTotem() const	{ return _nTotem; }
		void	SetFamilyTotem( unsigned char nTotem )	{ _nTotem = nTotem; }

		unsigned int	GetProsperity() const	{ return _nProsperity; }
		void	SetProsperity( unsigned int nProsperity )	{ _nProsperity = nProsperity; }

		unsigned int	GetMoney() const	{ return _nMoney; }
		void	SetMoney( unsigned int nMoney )	{ _nMoney = nMoney; }

		unsigned int	GetLeaderID() const	{ return _nLeaderID; }
		void	SetLeaderID( unsigned int nLeaderID )	{ _nLeaderID = nLeaderID; }

		const char*	GetFamilyNotice() const	{ return _szNotice; }
		void	SetFamilyNotice( const char* szNotice )	{ strncpy_s( _szNotice, sizeof( _szNotice ), szNotice, sizeof( _szNotice ) - 1 ); }

	private:
		unsigned int	_nID;						// 家族ID
		unsigned char	_nLevel;					// 家族等级
		char			_szName[ MaxFamilyNameLen ];// 家族名字
		char			_szAim[ MaxFamilyAimLen ];	// 家族宗旨
		unsigned char	_nTotem;					// 家族图腾
		unsigned int	_nProsperity;				// 繁荣度
		unsigned int	_nMoney;					// 家族资金
		unsigned int	_nLeaderID;					// 家族长ID
		char			_szNotice[ MaxFamilyNoticeLen ]; // 家族公告
	};

	// 服务器用家族信息
	class ServerFamilyInfo : public FamilyInfo
	{
	public:
		ServerFamilyInfo() { _n64DisbandTime = 0; }

		__int64 GetDisbandTime() const { return _n64DisbandTime; }
		void SetDisbandTime( __int64 nValue ) { _n64DisbandTime = nValue; }

		__int64	GetLastChangeAimTime() const	{ return _nLChangeAimTime; }
		void	SetLastChangeAimTime( __int64 nTime )	{ _nLChangeAimTime = nTime; }

	private:
		__int64 _n64DisbandTime;	// 满足解散条件的时间( == 0 没有设置时间 )
		__int64	_nLChangeAimTime;	// 最后更改宗旨的时间
	};


	class FamilyInvite
	{
	public:
		FamilyInvite() : _nInviterID( 0 ), _nInviteeID( 0 ), _nInviteTime( 0 ) {}

		unsigned int GetInviterID() const { return _nInviterID; }
		unsigned int GetInviteeID() const { return _nInviteeID; }
		unsigned int GetInviteTime() const { return _nInviteTime; }

		void SetInviterID( unsigned int nValue ) { _nInviterID = nValue; }
		void SetInviteeID( unsigned int nValue ) { _nInviteeID = nValue; }
		void SetInviteTime( unsigned int nValue ) { _nInviteTime = nValue; }

	private:
		unsigned int _nInviterID;	// 邀请人
		unsigned int _nInviteeID;	// 被邀请人
		unsigned int _nInviteTime;	// 邀请时间
	};

	class FamilyRequest
	{
	public:
		const FamilyMember& GetMember() const { return _xMember; }
		unsigned int GetRequestTime() const { return _nRequestTime; }

		void SetMember( FamilyMember& xMember ) { _xMember = xMember; }
		void SetRequestTime( unsigned int nValue ){ _nRequestTime = nValue; }

	private:
		FamilyMember _xMember;		// 申请的玩家
		unsigned int _nRequestTime;	// 申请时间
	};

	// 客户端家族列表信息
	class FamilySimpleInfo
	{
	public:
		FamilySimpleInfo() { memset( this, 0, sizeof(*this) ); }

		unsigned int GetFamilyID() const { return nFamilyID; }
		unsigned char GetLevel() const { return nLevel; }
		const char* GetFamilyName() const { return szFamilyName; }
		unsigned int GetProsperity() const { return nProsperity; }
		unsigned int GetMemberCount() const { return nMemberCount; }

		void SetFamilyID( unsigned int nValue ) { nFamilyID = nValue; }
		void SetLevel( unsigned char uchValue ) { nLevel = uchValue; }
		void SetFamilyName( const char* szValue ) { strncpy_s( szFamilyName, sizeof( szFamilyName ), szValue, sizeof( szFamilyName ) - 1 ); }
		void SetProsperity( unsigned int nValue ) { nProsperity = nValue; }
		void SetMemberCount( unsigned int nValue ) { nMemberCount = nValue; }

	private:
		unsigned int nFamilyID;
		char szFamilyName[ FamilyDefine::MaxFamilyNameLen ];
		unsigned char nLevel;
		unsigned int nProsperity;	// 繁荣度
		unsigned int nMemberCount;
	};
}

#endif