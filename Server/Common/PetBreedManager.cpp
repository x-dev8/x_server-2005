#include "PetBreedManager.h"
#include "ShareData.h"
#include "GameServer.h"
#include "GamePlayer.h"

void PetBreedInfo::StartTimer( unsigned int nStartTime, unsigned int nKeepTime )
{
    _timer.StartTimer( nStartTime, nKeepTime );
}

void PetBreedInfo::ClearPetBreedData( unsigned char uchType )
{
    GamePlayer* pPlayerA = theRunTimeData.GetGamePlayerByDBID( _playerA );
    if ( pPlayerA != NULL )
    {
        pPlayerA->SetPetBreedID( InvalidLogicNumber );
        MsgPetBreedFinish msg;
        msg.nType = uchType;
        GettheServer().SendMsgToSingle( &msg, pPlayerA );
    }

    GamePlayer* pPlayerB = theRunTimeData.GetGamePlayerByDBID( _playerB );
    if ( pPlayerB != NULL )
    {
        pPlayerB->SetPetBreedID( InvalidLogicNumber );
        MsgPetBreedFinish msg;
        msg.nType = uchType;
        GettheServer().SendMsgToSingle( &msg, pPlayerB );
    }
}

PetBreedManager::PetBreedManager() 
{
    m_xUpdateTimer.StartTimer( 1, 5000 );
}

PetBreedManager::~PetBreedManager()
{
    for ( PetBreedMapIter iter = m_mapPetBreed.begin(); iter != m_mapPetBreed.end(); ++iter )
    {
        iter->second->Release();
    }
    m_mapPetBreed.clear();
}

PetBreedInfo* PetBreedManager::CreatePetBreed( unsigned long nBreedID )
{
    PetBreedInfo* pPetBreed = PetBreedInfo::Instace();
    if ( pPetBreed == NULL )
    { return NULL; }

    // 加入列表中
    pPetBreed->SetID( nBreedID );
    m_mapPetBreed[ nBreedID ] = pPetBreed;

    return pPetBreed;
}

PetBreedInfo* PetBreedManager::GetPetBreed( unsigned long nBreedID )
{
    PetBreedMapIter iter = m_mapPetBreed.find( nBreedID );
    if ( iter == m_mapPetBreed.end() )
    { return NULL; }

    return iter->second;
}

void PetBreedManager::RemovePetBreed( unsigned long nBreedID, unsigned char nType )
{
    PetBreedMapIter iter = m_mapPetBreed.find( nBreedID );
    if ( iter == m_mapPetBreed.end() )
    { return; }

    iter->second->ClearPetBreedData( nType );
    iter->second->Release();
    m_mapPetBreed.erase( iter );
}

void PetBreedManager::RunUpdate( unsigned int nCurrentTime )
{
    for ( PetBreedMapIter iter = m_mapPetBreed.begin(); iter != m_mapPetBreed.end(); )
    {
        if ( iter->second->CheckTimer() )
        {
            iter->second->ClearPetBreedData( EPetBreed_FinishTimeOut );
            iter->second->Release();
            iter = m_mapPetBreed.erase( iter );
        }
        else
        {
            ++iter;
        }
    }
}
