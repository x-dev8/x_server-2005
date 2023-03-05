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

    // 没有工会了
    if ( pPlayer->GetGuild() == NULL )
    { return eEctypeKickType_noguild; }

    return eEctypeKickType_no;
}

bool SingleGuildStage::ProcessEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::ProcessEnterStage( pPlayer ) )
    { return false; }

    // 删除预约信息
    RemoveReserve( pPlayer->GetGuildID() );
    return true;
}