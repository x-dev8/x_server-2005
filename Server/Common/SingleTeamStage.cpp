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

    // û�ж�����
    if ( !pPlayer->HaveTeam() )
    { return eEctypeKickType_noTeam; }

	//�ж��� ���Ƕ��鲻�ǵ�ͼ���趨�Ķ���ID
	if(theGameWorld.GetStageById(theGameWorld.MakeEctypeStageID(GetMapData(), pPlayer, m_nStageLevel )) != this)
	{ return eEctypeKickType_noTeam; }

    return eEctypeKickType_no;
}

bool SingleTeamStage::ProcessEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::ProcessEnterStage( pPlayer ) )
    { return false; }

    // ɾ��ԤԼ��Ϣ
    RemoveReserve( pPlayer->GetTeamID() );
    return true;
}
