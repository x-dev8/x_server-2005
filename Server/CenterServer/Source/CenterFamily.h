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

	static CenterFamily* CreateFamily()	{ return CNewWithDebug< CenterFamily >::Alloc( 1, "创建CenterFamily实例"); }
	virtual void Release()	{ CNewWithDebug< CenterFamily >::Free( this ); }

	// 更新
	unsigned short	RunUpdate( unsigned int nCurrentTime );

	// 保存基本数据到数据库
	void SaveFamilyDataToDatabase();

	// 处理玩家加入家族
	void ProcessMemberJoinFamily( const FamilyDefine::FamilyMember& member );

	// 处理玩家离开家族
	void ProcessMemberLeaveFamily( const FamilyDefine::FamilyMember& member, uint8 nType );

	// 发送家族数据到GameServer
	void SendFamilyDataToGameServer( unsigned int nServerID );

	// 保存玩家信息到数据库
	void SaveMemberDataToDatabase(); 

	// 发送邮件给离线玩家
	void SendMailToMemberNotOnLine( const FamilyDefine::FamilyMember& member, uint8 nType );

	// 发送邮件给家族里所有不在线的成员
	void SendMailToAllMemberNotOnLine( uint8 nType );

	// 处理公告更新
	void ProcessUpdateFamilyNotice();
	
	// 处理家族宗旨更新
	void ProcessUpdateFamilyAim();

	// 处理转让职位
	void ProcessTransferPosition( const FamilyDefine::FamilyMember& requester, const FamilyDefine::FamilyMember& target );

	// 处理捐金
	void ProcessDonate( FamilyDefine::FamilyMember& member, unsigned int nMoeny );

	// 处理升级
	void ProcessUpgrade(const FamilyDefine::FamilyMember& member );

	// 处理解散
	void ProcessDisbandFamily();

	// 更新邀请
	void UpdateInivte( unsigned int nCurrentTime );

	// 更新申请
	void UpdateRequest( unsigned int nCurrentTime );

	// 更新memberleave容器
	void UpdateMemberLeave( unsigned int nKeepTime );

	// 处理成员下线
	void ProcessMemberOffline( FamilyDefine::FamilyMember& member );

	// 如果所有的家族成员都不在线，设这解散时间，否则，将解散时间置为0
	void ProcessAllMemberOffline();

	void ProcessMemberDataUpdate( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue ); 

	void ProcessMemberDataUpdate( FamilyDefine::FamilyMember* pMember, unsigned char uchType, unsigned int nValue );

	void ProcessFamilyPositionChange( FamilyDefine::FamilyMember* pMember, unsigned char uchPosition );

	// 发送成员数据更新消息
	void SendMemberDataUpdateMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );

	// 发送成员数据改变请求到CenterServer
	void SendMemberDataChangeReqMessage( unsigned int nPlayerID, unsigned char uchChangeType, unsigned char uchOperatetype, unsigned int nValue ); 

	// 成员上线
	void ProcessEnterWorld( unsigned int nPlayerID );

	// 成员下线
	void ProcessExitWorld( unsigned int nPlayerID );    

	// 添加在线成员人数
	void AddOnLineCount();      

	// 减少在线成员人数
	void SubOnLineCount();

	// 设置判断玩家是否是当天第一次进入游戏的bool值
	void SetbFirstEnterWorld( bool bFirstEnterWorld );

	void OperateProsperity( uint8 uType, int nValue );

	void SendMessageToFamily( Msg* pMessage, unsigned int nExceptID = FamilyDefine::InitFamilyID, unsigned short nLevel = 0, bool bSendToCenter = false );

	// 服务器关系时, 要保存所有数据
	void SaveFamilyAndMemberData();   

private:
	typedef std::set< unsigned int >		SaveMemberContainer;
	typedef SaveMemberContainer::iterator	SaveMemberContainerItr;

	void AddNeedSaveMember( unsigned int nPlayerID );

	void StartSaveTimer();

	int m_nOnLineCount;                 // 在线玩家个数
	SaveMemberContainer _saveMembers;	// 需要保存的成员
	GameTimerEx _familyInfoSaveTimer;	// 家族数据保存Timer
	GameTimerEx _memberSaveTimer;		// 家族成员保存的Timer
	GameTimerEx _bFirstEnterTimer;		// 设置bfirstEnterWorld的Timer
	GameTimerEx _prosperityTimer;		// 定时清除繁荣度Timer
	GameTimerEx	_memberLeaveTimer;		// 定时清除服务器保存的memberleave信息
};

#endif