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

    // û�ж�����
    if ( !pPlayer->HaveTeam() )
    { return eEctypeKickType_noTeam; }

    return eEctypeKickType_no;
}

bool MultiTeamStage::ProcessEnterStage( GamePlayer* pPlayer )
{
    if ( !EctypeStage::ProcessEnterStage( pPlayer ) )
    { return false; }

    // ɾ��ԤԼ��Ϣ
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

    // �Ѿ���ԤԼ
    if ( HaveReserve( pPlayer->GetTeamID() ) )
    { return true; }

    // �����Ѿ��ڸ�����
    if ( HaveTeam( pPlayer->GetTeamID() ) )
    { return true; }

    // ��ǰ���� ��ԤԼ����� С����������
    if ( ( m_setTeam.size() + m_mapReserve.size() ) < m_pMapData->UnitCount )
    { return true; }

    return false;
}