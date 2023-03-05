#include "BigTile.h"
//#include "MeConnector.h"
#include "GamePlayer.h"
#include "GateServer.h"

BigTile::BigTile()
{
    MapId = 0;
}

BigTile::~BigTile()
{
}

void BigTile::AddId( GameObjectId stID )
{
    m_chars.insert( stID );
}
void BigTile::RemoveId( GameObjectId stID )
{
    m_chars.erase( stID );
}

void BigTile::SendMsg( GameObjectId stID, Msg* pMsg,bool bExceptMe )
{
    BaseCharacter* pChar = NULL;
    GamePlayer* pClient = NULL;
    GameObjectIDSetItr it = m_chars.begin();
    for ( ; it!=m_chars.end(); ++it )
    {
        if( bExceptMe && stID == *it )
        { continue; }

        pChar = GettheGateServer().GetChar( *it );
        if( !pChar )
        { continue; }

        if( !pChar->IsPlayer() )
        { continue; }

        pClient = (GamePlayer*)pChar;
        pClient->SendMsg( pMsg );
    }
}

void BigTile::SendCountryMsg ( Msg* pMsg,TCountryId country, uint16 ustLevel, uint16 stExceptID )
{
    BaseCharacter* pChar = NULL;
    GamePlayer* pClient  = NULL;

    GameObjectIDSetItr it = m_chars.begin();
    for ( ; it!=m_chars.end(); ++it )
    {
        pChar = GettheGateServer().GetChar( *it );
        if( NULL == pChar || !pChar->IsPlayer() )
        { continue; }

        pClient = static_cast< GamePlayer* >( pChar );
        if ( pClient->GetCountryId() != country )
        { continue; }

        if ( pClient->GetLevel()<ustLevel )
        { continue; } // 等级不足, 不发送消息

        if ( pClient->GetGameServerPlayerId() == stExceptID )
        { continue; }

        pClient->SendMsg( pMsg );
    }
}
