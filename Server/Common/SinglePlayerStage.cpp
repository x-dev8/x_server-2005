#include "SinglePlayerStage.h"
#include "GamePlayer.h"

SinglePlayerStage::SinglePlayerStage() : EctypeStage()
{

}

bool SinglePlayerStage::ProcessEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::ProcessEnterStage( pPlayer ) )
    { return false; }

    // É¾³ýÔ¤Ô¼ÐÅÏ¢
    RemoveReserve( pPlayer->GetDBCharacterID() );
    return true;
}
