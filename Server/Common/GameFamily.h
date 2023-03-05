#ifndef __GAME_FAMILY_H__
#define __GAME_FAMILY_H__

#include "Family.h"
#include "memory_pool.h"


class GamePlayer;
// family on game server
class GameFamily : public Family,	INHERIT_POOL_PARAM( GameFamily, 50 )
{
public:
	static GameFamily* CreateFamily()	{ return CNewWithDebug< GameFamily >::Alloc( 1, "����GameFamilyʵ��"); }
	virtual void Release()	{ CNewWithDebug< GameFamily >::Free( this ); }

	static GamePlayer* GetPlayer( unsigned int nPlayerID );

	void ProcessMemberJoinFamily( const FamilyDefine::FamilyMember& member );

	void ProcessMemberLeaveFamily( const FamilyDefine::FamilyMember& member, uint8 nType );

	void SendMessageToFamily( Msg* pMessage, unsigned int nExceptID = FamilyDefine::InitFamilyID, unsigned short nLevel = 0, bool bSendToCenter = false );

	void SendFamilyDetailToClient( unsigned int nPlayerID );

	void SendFamilyInfoToClient( unsigned int nPlayerID );

	void ProcessEnterWorld( unsigned int nPlayerID );

	void ProcessOffline( unsigned int nPlayerID );

	void ProcessUpdateFamilyNotice();

	void ProcessUpdateFamilyAim();

	void ProcessTransferPosition( const FamilyDefine::FamilyMember& requester, const FamilyDefine::FamilyMember& target );

	void ProcessDonate( FamilyDefine::FamilyMember& member, unsigned int nMoney );

	void ProcessUpgrade( const FamilyDefine::FamilyMember& member );

	void ProcessMemberDataUpdate( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue ); 

	void ProcessMemberDataUpdate( FamilyDefine::FamilyMember* pMember, unsigned char uchType, unsigned int nValue );

	void ProcessFamilyPositionChange( FamilyDefine::FamilyMember* pMember, unsigned char uchPosition );

	// ���ͳ�Ա���ݸ�����Ϣ
	void SendMemberDataUpdateMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );

	// ���ͳ�Ա���ݸı�����CenterServer
	void SendMemberDataChangeReqMessage( unsigned int nPlayerID, unsigned char uchChangeType, unsigned char uchOperatetype, unsigned int nValue ); 

	// ��ɢ����
	void ProcessDisbandFamily();

};

#endif