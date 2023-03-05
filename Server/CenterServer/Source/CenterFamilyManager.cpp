#include "FamilyManager.h"
#include "CenterFamily.h"
#include "FamilyMessage.h"
#include "MySqlCommunication.h"
#include "GameServerManager.h"

template<>
void FamilyManager< CenterFamily >::RunUpdate( unsigned int nCurrentTime )
{
	if ( ! _updateTimer.DoneTimer( nCurrentTime ) )
	{ return; }

	// 处理加载数据
	ProcessLoadFamilyData( nCurrentTime );

	// 处理每个家族的更新
	FamilyContainerItr itr = _familyContainer.begin();
	FamilyContainerItr endItr = _familyContainer.end();
	for ( ; itr != endItr; )
	{
		if ( itr->second->RunUpdate( nCurrentTime ) == FamilyDefine::UpdateDiaband )
		{
			itr->second->Release();
			itr = _familyContainer.erase( itr );
		}
		else
		{
			++itr;
		}
	}
}

template<>
void FamilyManager< CenterFamily >::ProcessLoadFamilyData( unsigned int nCurrentTime )
{
	StartLoadTimer();
	if ( !_loadTimer.DoneTimer( nCurrentTime ) )
	{ return;  }

	CS2DBFamilyDataLoadReq xReq;
	theMysqlCommunication.PushReqMessage( &xReq, 0 );
}

template<>
void FamilyManager< CenterFamily >::SendAllFamiliesToClient( unsigned int nID )
{
	if ( ! GetLoadSuccess() )
	{ return; }

	FamilyContainerItr itr = _familyContainer.begin();
	FamilyContainerItr endItr = _familyContainer.end();
	for ( ; itr != endItr; ++itr )
	{
		itr->second->SendFamilyDataToGameServer( nID );
	}

	SendAllFamiliesEnd( nID );
}

template<>
void FamilyManager< CenterFamily >::SendAllFamiliesEnd( unsigned int nID )
{
	CS2GSAllFamiliesSendEnd end;

	GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( nID );
	if ( pGameServer != NULL )
	{
		pGameServer->Send( &end );
	}
	else
	{
		theGameServerManager.SendMessageToGameServers( &end );
	}
}

// 将玩家升到10级的消息发给所有家族的族长
template<>
void FamilyManager< CenterFamily >::SendPlayerLvUpToMaster( unsigned int nID, unsigned int nLv, char * szSpeakName )
{

	for ( FamilyContainerItr iter = _familyContainer.begin(); iter != _familyContainer.end(); ++iter )
	{

		GS2CSFamilyPlayerLvUpToTenMessage msgLvUp;
		msgLvUp.header.dwType	=  CS2GS_FAMILYPLAYERLVTOTEN;
		msgLvUp.nPlayerID		=  nID;
		msgLvUp.nTargetID		=  iter->second->GetLeaderID();
		msgLvUp.nPlayerLv		=  nLv;
		HelperFunc::SafeNCpy( msgLvUp.szSpeakName, szSpeakName, sizeof( msgLvUp.szSpeakName ) );

		ClientPeer* pClientPeer = theClientPeerManager.GetClientPeerByDBId( msgLvUp.nTargetID );
		if (pClientPeer)
		{  
			GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( pClientPeer->GetServerInfo().nServerId );
			if ( pGameServer )
			{ 
				pGameServer->Send( &msgLvUp ); 
			}
		}
	}

}