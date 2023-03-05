#include "MultiPlayerStage.h"
#include "GamePlayer.h"

MultiPlayerStage::MultiPlayerStage() : EctypeStage()
{
}

bool MultiPlayerStage::ProcessEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::ProcessEnterStage( pPlayer ) )
    { return false; }

    // 删除预约信息
    RemoveReserve( pPlayer->GetDBCharacterID() );
    return true;
}

bool MultiPlayerStage::HavePlayer( GameObjectId nPlayerID )
{
    PlayerListIter iter = m_setPlayer.find( nPlayerID );

    return iter != m_setPlayer.end();
}

bool MultiPlayerStage::CheckCanEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::CheckCanEnterStage( pPlayer ) )
    { return false; }

    // 已经有预约
    if ( HaveReserve( pPlayer->GetDBCharacterID() ) )
    { return true; }

    if ( HavePlayer( pPlayer->GetID() ) )
    { return true; }

    // 当前玩家 和预约的玩家 小于限制数量
    if ( ( m_setPlayer.size() + m_mapReserve.size() ) < m_pMapData->UnitCount )
    { return true; }

    return false;
}