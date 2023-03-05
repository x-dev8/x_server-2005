#include "SingleTeamStage.h"
#include "GamePlayer.h"
#include "core/Name.h"
#include "GameWorld.h"
SingleTeamStage::SingleTeamStage() : EctypeStage()
{

}

GameStage::eEctypeKickType SingleTeamStage::WhyKickOutPlayer( GamePlayer* pPlayer )
{
    eEctypeKickType nStringID = EctypeStage::WhyKickOutPlayer( pPlayer );
    if ( nStringID != eEctypeKickType_no )
    { return nStringID; }

    // 没有队伍了
    if ( !pPlayer->HaveTeam() )
    { return eEctypeKickType_noTeam; }

	//有队伍 但是队伍不是地图所设定的队伍ID
	if(theGameWorld.GetStageById(theGameWorld.MakeEctypeStageID(GetMapData(), pPlayer, m_nStageLevel )) != this)
	{ return eEctypeKickType_noTeam; }

    return eEctypeKickType_no;
}

bool SingleTeamStage::ProcessEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::ProcessEnterStage( pPlayer ) )
    { return false; }

    // 删除预约信息
    RemoveReserve( pPlayer->GetTeamID() );
    return true;
}
