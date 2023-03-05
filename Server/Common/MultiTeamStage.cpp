#include "MultiTeamStage.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "core/Name.h"

MultiTeamStage::MultiTeamStage() : EctypeStage()
{
    m_setTeam.clear();
}

GameStage::eEctypeKickType MultiTeamStage::WhyKickOutPlayer( GamePlayer* pPlayer )
{
    eEctypeKickType nStringID = EctypeStage::WhyKickOutPlayer( pPlayer );
    if ( nStringID != eEctypeKickType_no )
    { return nStringID; }

    // 没有队伍了
    if ( !pPlayer->HaveTeam() )
    { return eEctypeKickType_noTeam; }

    return eEctypeKickType_no;
}

bool MultiTeamStage::ProcessEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::ProcessEnterStage( pPlayer ) )
    { return false; }

    // 删除预约信息
    RemoveReserve( pPlayer->GetTeamID() );
    return true;
}

void MultiTeamStage::UpdateStageTeam()
{
    m_setTeam.clear();

    for ( PlayerListIter iter = m_setPlayer.begin(); iter != m_setPlayer.end(); ++iter )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *iter );
        if ( pChar == NULL || !pChar->IsPlayer() )
        { continue; }

        GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
        m_setTeam.insert( pPlayer->GetTeamID() );
    }
}

bool MultiTeamStage::HaveTeam( uint32 nTeamID )
{
    UpdateStageTeam();

    TeamListIter iter = m_setTeam.find( nTeamID );
    return iter != m_setTeam.end();
}

bool MultiTeamStage::CheckCanEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::CheckCanEnterStage( pPlayer ) )
    { return false; }

    // 已经有预约
    if ( HaveReserve( pPlayer->GetTeamID() ) )
    { return true; }

    // 队伍已经在副本中
    if ( HaveTeam( pPlayer->GetTeamID() ) )
    { return true; }

    // 当前队伍 和预约的玩家 小于限制数量
    if ( ( m_setTeam.size() + m_mapReserve.size() ) < m_pMapData->UnitCount )
    { return true; }

    return false;
}