#include "SinglePlayerStage.h"
#include "GamePlayer.h"

SinglePlayerStage::SinglePlayerStage() : EctypeStage()
{

}

bool SinglePlayerStage::ProcessEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::ProcessEnterStage( pPlayer ) )
    { return false; }

    // ɾ��ԤԼ��Ϣ
    RemoveReserve( pPlayer->GetDBCharacterID() );
    return true;
}
