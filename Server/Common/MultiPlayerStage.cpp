#include "MultiPlayerStage.h"
#include "GamePlayer.h"

MultiPlayerStage::MultiPlayerStage() : EctypeStage()
{
}

bool MultiPlayerStage::ProcessEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::ProcessEnterStage( pPlayer ) )
    { return false; }

    // ɾ��ԤԼ��Ϣ
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

    // �Ѿ���ԤԼ
    if ( HaveReserve( pPlayer->GetDBCharacterID() ) )
    { return true; }

    if ( HavePlayer( pPlayer->GetID() ) )
    { return true; }

    // ��ǰ��� ��ԤԼ����� С����������
    if ( ( m_setPlayer.size() + m_mapReserve.size() ) < m_pMapData->UnitCount )
    { return true; }

    return false;
}