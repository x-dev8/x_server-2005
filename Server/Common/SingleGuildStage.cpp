#include "SingleGuildStage.h"
#include "GamePlayer.h"
#include "core/Name.h"

SingleGuildStage::SingleGuildStage() : EctypeStage()
{

}

GameStage::eEctypeKickType SingleGuildStage::WhyKickOutPlayer( GamePlayer* pPlayer )
{
    eEctypeKickType nStringID = EctypeStage::WhyKickOutPlayer( pPlayer );
    if ( nStringID != eEctypeKickType_no )
    { return nStringID; }

    // û�й�����
    if ( pPlayer->GetGuild() == NULL )
    { return eEctypeKickType_noguild; }

    return eEctypeKickType_no;
}

bool SingleGuildStage::ProcessEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::ProcessEnterStage( pPlayer ) )
    { return false; }

    // ɾ��ԤԼ��Ϣ
    RemoveReserve( pPlayer->GetGuildID() );
    return true;
}