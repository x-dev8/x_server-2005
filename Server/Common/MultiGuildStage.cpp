#include "MultiGuildStage.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "core/Name.h"

MultiGuildStage::MultiGuildStage() : EctypeStage()
{
    m_setGuild.clear();
}

GameStage::eEctypeKickType MultiGuildStage::WhyKickOutPlayer( GamePlayer* pPlayer )
{
    eEctypeKickType nStringID = EctypeStage::WhyKickOutPlayer( pPlayer );
    if ( nStringID != eEctypeKickType_no )
    { return nStringID; }

    // 没有工会了
    if ( pPlayer->GetGuild() == NULL )
    { return eEctypeKickType_noguild; }

    return eEctypeKickType_no;
}

bool MultiGuildStage::ProcessEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::ProcessEnterStage( pPlayer ) )
    { return false; }

    // 删除预约信息
    RemoveReserve( pPlayer->GetGuildID() );
    return true;
}

void MultiGuildStage::UpdateStageGuild()
{
    m_setGuild.clear();

    for ( PlayerListIter iter = m_setPlayer.begin(); iter != m_setPlayer.end(); ++iter )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( *iter );
        if ( pChar == NULL || !pChar->IsPlayer() )
        { continue; }

        GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
        m_setGuild.insert( pPlayer->GetGuildID() );
    }
}

bool MultiGuildStage::HaveGuild( uint32 nGuildID )
{
    UpdateStageGuild();

    GuildListIter iter = m_setGuild.find( nGuildID );
    return iter != m_setGuild.end();
}

bool MultiGuildStage::CheckCanEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::CheckCanEnterStage( pPlayer ) )
    { return false; }

    // 已经有预约
    if ( HaveReserve( pPlayer->GetGuildID() ) )
    { return true; }

    // 更新副本队伍
    UpdateStageGuild();

    // 队伍已经在副本中
    if ( HaveGuild( pPlayer->GetGuildID() ) )
    { return true; }

    // 当前队伍 和预约的玩家 小于限制数量
    if ( ( m_setGuild.size() + m_mapReserve.size() ) < m_pMapData->UnitCount )
    { return true; }

    return false;
}