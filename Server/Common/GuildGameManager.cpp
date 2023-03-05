#include "GuildManager.h"
#include "GamePlayer.h"

template<>
void GuildManager< GameGuild >::SendGuildListToClient( unsigned int nPlayerID )
{
    GamePlayer* pPlayer = GameGuild::GetPlayer( nPlayerID );
    if ( pPlayer == NULL )
    { return; }

    MsgTellGuildList xList;

    for ( GuildMapIter iter = m_mapGuild.begin(); iter != m_mapGuild.end(); ++iter )
    {
		GameGuild* pGuild = theGameGuildManager.GetGuild(iter->second->GetID());
		if ( !pGuild)
		{
			continue;
		}

        GuildListInfo xInfo;
        xInfo.SetCountry( iter->second->GetCountry() );
        xInfo.SetLevel( iter->second->GetLevel() );
        xInfo.SetID( iter->second->GetID() );
		xInfo.SetMemberNum( pGuild->MemberCount() );
        xInfo.SetName( iter->second->GetName() );

		GuildMember* pMaster = pGuild->GetMember( iter->second->GetMasterID() );
		if ( !pMaster )
		{
			continue;
		}
		xInfo.SetMasterName( pMaster->GetName() );

        xList.AddGuild( xInfo );
        if ( xList.IsFull() )
        {
            pPlayer->SendMessageToClient( &xList );
            xList.Reset();
        }
    }

    pPlayer->SendMessageToClient( &xList );
}
template<>
map< unsigned int, GameGuild* >& GuildManager< GameGuild >::GetAllGuild()
{
	return m_mapGuild;
}

