#include "GuildManager.h"
#include "GameServerManager.h"
#include "MySqlCommunication.h"

template<>
void GuildManager< CenterGuild >::SendGuildListToClient( unsigned int nID )
{
    if ( !GetLoadSuccess() )
    { return; }

    for ( GuildMapIter iter = m_mapGuild.begin(); iter != m_mapGuild.end(); ++iter )
    {
        iter->second->SendGuildDataToClient( nID );
    }

    SendGuildListSuccess( nID );
}   

template<>
void GuildManager< CenterGuild >::SendGuildListSuccess( unsigned int nID )
{
    CS2GSGuildDataSendSuccess xSuccess;

    GameServerPeer* pGameServer = theGameServerManager.GetGameServerPeer( nID );
    if ( pGameServer != NULL )
    {
        pGameServer->Send( &xSuccess );
    }
    else
    {
        theGameServerManager.SendMessageToGameServers( &xSuccess );
    }
}

template<>
void GuildManager< CenterGuild >::ProcessLoadGuildData( unsigned int nCurrentTime )
{
    StartLoadTimer();
    if ( !m_xLoadTimer.DoneTimer( nCurrentTime ) )
    { return;  }

    CS2DBGuildDataLoadReq xReq;
    theMysqlCommunication.PushReqMessage( &xReq, 0 );
}

template<>
void GuildManager< CenterGuild >::RunUpdate( unsigned int nCurrentTime )
{
    if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
    { return; }

    // 处理加载数据
    ProcessLoadGuildData( nCurrentTime );

    // 处理每个帮派的更新
    for ( GuildMapIter iter = m_mapGuild.begin(); iter != m_mapGuild.end(); )
    {
        if ( iter->second->RunUpdate( nCurrentTime ) == GuildDefine::UpdateDiaband )
        {
            iter->second->Release();
            iter = m_mapGuild.erase( iter );
        }
        else
        {
            ++iter;
        }
    }
}

// 将玩家升到30级的消息发给所有帮派的帮主 luo.qin 4.20
template<>
void GuildManager< CenterGuild >::SendPlayerLvUpToMaster( unsigned int nID, unsigned int nLv, char * szSpeakName )
{

	for ( GuildMapIter iter = m_mapGuild.begin(); iter != m_mapGuild.end(); ++iter )
	{

		if ( iter->second->MemberCount() <= 0 )
			continue;

		GS2CSPlayerLvUpToThirtyMessage msgLvUp;
		msgLvUp.header.dwType	=  CS2GS_PLAYERLVUPTOTHIRTY;
		msgLvUp.nPlayerID		=  nID;
		msgLvUp.nTargetID		=  iter->second->GetMasterID();
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