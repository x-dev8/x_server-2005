#ifndef __FAMILY_DEFINE_H__
#define __FAMILY_DEFINE_H__

#include <string.h>


namespace FamilyDefine
{
	// ���峣������
	enum EConstDefine
	{
		MaxNameLen = 33,			// ��Ա����������
		MaxFamilyNameLen = 17,		// ��������������
		MaxFamilyAimLen = 401,		// ������ּ��������
		MaxFamilyNoticeLen = 401,	// ���幫�泤������
		MaxRequestNoteLen = 161,	// �������Գ�������

		MaxFamilyMoney = 2000000000,// �����ʽ�����
		MaxFamilyProsperity = 2000000000,	// ���己�ٶ�����

		InitFamilyID = 0,	// ��ʼ���ļ���ID
		FirstFamilyID = 1,	// ��ʼ����ID

		InvalidFamilyDisbandTime = 0,// ��Ч�ļ����ɢʱ��
		UpdateSpace = 10000,
		LoadSpaceTime = 1000000,
		SaveSpaveTime = 300000,
		InviteKeepTime = 90000,		// ����ʱЧ
		RequestKeepTime = 90000,	// ����ʱЧ

		//////////////////////////////////////////////////////////////////////////
		UpdateNormal = 0,
		UpdateDiaband,
		//////////////////////////////////////////////////////////////////////////

		// ��Ա��Ϣ���±�־
		UpdateMemberOnLine = 1,     // ��������
		UpdateMemberLevel,          // ���µȼ�
		UpdateMemberPosition,       // ����ְλ
		UpdateMemberProfession,     // ����ְҵ
		UpdateMemberExp,            // ������Ҿ���( �ͻ��˲��ô��� )
		UpdateMemberDonateMoney,	// ������Ҿ��

		// ����Ϣ���±�� 
		UpdateFamilyLevel = 1,       // ���°��ɵȼ�
		UpdateFamilyLeader,          // ���°��ɰ���
		UpdateFamilyDonate,          // ���°��ɾ��׵Ľ�Ǯ( �ͻ��˲��ô��� )
		UpdateFamilyDisbandTime,     // ���°��ɽ�ɢʱ��

		////////////////////////////////////////////////////////////////
		OperateAdd = 1,             // +
		OperateSub,                 // -
		OperateSet,                 // =
		////////////////////////////////////////////////////////////////

		// ����Ȩ��
		Right_None		= 0,		// ��
		Right_Accept	= 1 << 0,	// ���ܼ����������
		Right_Kick		= 1 << 1,	// ����������
		Right_LevelUp	= 1 << 2,	// ��������
		Right_Transfer	= 1 << 3,	// ת��ְλ
		Right_Invite	= 1 << 4,	// ������Ҽ������
		Right_Activity	= 1 << 5,	// �����
		Right_LeaveMsg	= 1 << 6,	// ����
		Right_Leave		= 1 << 7,	// �˳�����

		// ����ְλ
		Position_None = 0,	// ��
		Position_Member,	// ��Ա
		Position_Leader,	// �峤

		// ְλȨ��
		Right_Member = Right_Leave,
		Right_Leader = Right_Accept | Right_Kick | Right_LevelUp | Right_Transfer | Right_Invite | Right_Activity | Right_LeaveMsg,

		// ����ͼ��
		Totem_Human = 0,	// ��
		Totem_Machine,		// ��
		Totem_Monster,		// ��
		Totem_Immortal,		// ��
		Totem_Ghost,		// ��
		Totem_Goblin,		// ��
		Totem_God,			// ��
		Totem_Demon,		// ħ

		//////////////////////////////////////////////////////////////////////////
		DecodeFieldBufferSize = 1024 * 10,
		UnZipTempBufferSize   = 1024 * 20,
		ZipTempBufferSize     = 1024 * 40,
		EncodeFieldBufferSize = 1024 * 10,
		//////////////////////////////////////////////////////////////////////////

		PlayerLvIsTen	= 10,		//�������10����֪ͨ�����еļ����峤

		Enum_Leave_Self	= 0,		// �Լ��˳�����
		Enum_Leave_Kicked,			// ���峤�߳�����
		Enum_Family_Disbanded,		// ���屻��ɢ����ұ��޳�

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

	// �����Ա
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
		char			_szName[ MaxNameLen ];	// ����
		unsigned short	_nLevel;				// �ȼ�
		unsigned char	_nProfession;			// ְҵ  
		unsigned int	_nFamilyID;				// ����ID
		unsigned char	_nPosition;				// ����ְλ
		bool			_bOnLine;				// �Ƿ�����
		unsigned int	_nDonateMoney;			// ���
		bool			_bFirstEnterWorld;		// �Ƿ��ǵ�һ�ν�����Ϸ	���������ݿ�
	};

	// ���������Ϣ
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
		unsigned int	_nID;						// ����ID
		unsigned char	_nLevel;					// ����ȼ�
		char			_szName[ MaxFamilyNameLen ];// ��������
		char			_szAim[ MaxFamilyAimLen ];	// ������ּ
		unsigned char	_nTotem;					// ����ͼ��
		unsigned int	_nProsperity;				// ���ٶ�
		unsigned int	_nMoney;					// �����ʽ�
		unsigned int	_nLeaderID;					// ���峤ID
		char			_szNotice[ MaxFamilyNoticeLen ]; // ���幫��
	};

	// �������ü�����Ϣ
	class ServerFamilyInfo : public FamilyInfo
	{
	public:
		ServerFamilyInfo() { _n64DisbandTime = 0; }

		__int64 GetDisbandTime() const { return _n64DisbandTime; }
		void SetDisbandTime( __int64 nValue ) { _n64DisbandTime = nValue; }

		__int64	GetLastChangeAimTime() const	{ return _nLChangeAimTime; }
		void	SetLastChangeAimTime( __int64 nTime )	{ _nLChangeAimTime = nTime; }

	private:
		__int64 _n64DisbandTime;	// �����ɢ������ʱ��( == 0 û������ʱ�� )
		__int64	_nLChangeAimTime;	// ��������ּ��ʱ��
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
		unsigned int _nInviterID;	// ������
		unsigned int _nInviteeID;	// ��������
		unsigned int _nInviteTime;	// ����ʱ��
	};

	class FamilyRequest
	{
	public:
		const FamilyMember& GetMember() const { return _xMember; }
		unsigned int GetRequestTime() const { return _nRequestTime; }

		void SetMember( FamilyMember& xMember ) { _xMember = xMember; }
		void SetRequestTime( unsigned int nValue ){ _nRequestTime = nValue; }

	private:
		FamilyMember _xMember;		// ��������
		unsigned int _nRequestTime;	// ����ʱ��
	};

	// �ͻ��˼����б���Ϣ
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
		unsigned int nProsperity;	// ���ٶ�
		unsigned int nMemberCount;
	};
}

#endif