#ifndef __CENTER_FAMILY_H__
#define __CENTER_FAMILY_H__

#include "Family.h"
#include "memory_pool.h"
#include "GameTimer.h"

struct Msg;
class CenterFamily : public Family,	INHERIT_POOL_PARAM( CenterFamily, 50 )
{
public:
	CenterFamily();

	static CenterFamily* CreateFamily()	{ return CNewWithDebug< CenterFamily >::Alloc( 1, "����CenterFamilyʵ��"); }
	virtual void Release()	{ CNewWithDebug< CenterFamily >::Free( this ); }

	// ����
	unsigned short	RunUpdate( unsigned int nCurrentTime );

	// ����������ݵ����ݿ�
	void SaveFamilyDataToDatabase();

	// ������Ҽ������
	void ProcessMemberJoinFamily( const FamilyDefine::FamilyMember& member );

	// ��������뿪����
	void ProcessMemberLeaveFamily( const FamilyDefine::FamilyMember& member, uint8 nType );

	// ���ͼ������ݵ�GameServer
	void SendFamilyDataToGameServer( unsigned int nServerID );

	// ���������Ϣ�����ݿ�
	void SaveMemberDataToDatabase(); 

	// �����ʼ����������
	void SendMailToMemberNotOnLine( const FamilyDefine::FamilyMember& member, uint8 nType );

	// �����ʼ������������в����ߵĳ�Ա
	void SendMailToAllMemberNotOnLine( uint8 nType );

	// ���������
	void ProcessUpdateFamilyNotice();
	
	// ���������ּ����
	void ProcessUpdateFamilyAim();

	// ����ת��ְλ
	void ProcessTransferPosition( const FamilyDefine::FamilyMember& requester, const FamilyDefine::FamilyMember& target );

	// ������
	void ProcessDonate( FamilyDefine::FamilyMember& member, unsigned int nMoeny );

	// ��������
	void ProcessUpgrade(const FamilyDefine::FamilyMember& member );

	// �����ɢ
	void ProcessDisbandFamily();

	// ��������
	void UpdateInivte( unsigned int nCurrentTime );

	// ��������
	void UpdateRequest( unsigned int nCurrentTime );

	// ����memberleave����
	void UpdateMemberLeave( unsigned int nKeepTime );

	// �����Ա����
	void ProcessMemberOffline( FamilyDefine::FamilyMember& member );

	// ������еļ����Ա�������ߣ������ɢʱ�䣬���򣬽���ɢʱ����Ϊ0
	void ProcessAllMemberOffline();

	void ProcessMemberDataUpdate( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue ); 

	void ProcessMemberDataUpdate( FamilyDefine::FamilyMember* pMember, unsigned char uchType, unsigned int nValue );

	void ProcessFamilyPositionChange( FamilyDefine::FamilyMember* pMember, unsigned char uchPosition );

	// ���ͳ�Ա���ݸ�����Ϣ
	void SendMemberDataUpdateMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );

	// ���ͳ�Ա���ݸı�����CenterServer
	void SendMemberDataChangeReqMessage( unsigned int nPlayerID, unsigned char uchChangeType, unsigned char uchOperatetype, unsigned int nValue ); 

	// ��Ա����
	void ProcessEnterWorld( unsigned int nPlayerID );

	// ��Ա����
	void ProcessExitWorld( unsigned int nPlayerID );    

	// ������߳�Ա����
	void AddOnLineCount();      

	// �������߳�Ա����
	void SubOnLineCount();

	// �����ж�����Ƿ��ǵ����һ�ν�����Ϸ��boolֵ
	void SetbFirstEnterWorld( bool bFirstEnterWorld );

	void OperateProsperity( uint8 uType, int nValue );

	void SendMessageToFamily( Msg* pMessage, unsigned int nExceptID = FamilyDefine::InitFamilyID, unsigned short nLevel = 0, bool bSendToCenter = false );

	// ��������ϵʱ, Ҫ������������
	void SaveFamilyAndMemberData();   

private:
	typedef std::set< unsigned int >		SaveMemberContainer;
	typedef SaveMemberContainer::iterator	SaveMemberContainerItr;

	void AddNeedSaveMember( unsigned int nPlayerID );

	void StartSaveTimer();

	int m_nOnLineCount;                 // ������Ҹ���
	SaveMemberContainer _saveMembers;	// ��Ҫ����ĳ�Ա
	GameTimerEx _familyInfoSaveTimer;	// �������ݱ���Timer
	GameTimerEx _memberSaveTimer;		// �����Ա�����Timer
	GameTimerEx _bFirstEnterTimer;		// ����bfirstEnterWorld��Timer
	GameTimerEx _prosperityTimer;		// ��ʱ������ٶ�Timer
	GameTimerEx	_memberLeaveTimer;		// ��ʱ��������������memberleave��Ϣ
};

#endif