#include "GamePlayer.h"
#include "ShareData.h"

PlayerBargaining* BargainingInfo::GetPlayerBargaining( unsigned int nPlayerID )
{
    if ( nPlayerID == m_xPlayerBargainingA.GetID() )
    { return &m_xPlayerBargainingA; }

    if ( nPlayerID == m_xPlayerBargainingB.GetID() )
    { return &m_xPlayerBargainingB; }

    return NULL;
}

// 获得对方交易信息
PlayerBargaining* BargainingInfo::GetTargetPlayerBargaining( unsigned int nPlayerID )
{
    if ( nPlayerID == m_xPlayerBargainingA.GetID() )
    { return &m_xPlayerBargainingB; }

    if ( nPlayerID == m_xPlayerBargainingB.GetID() )
    { return &m_xPlayerBargainingA; }

    return NULL;
}

void BargainingInfo::StartTimer( unsigned int nStartTime, unsigned int nKeepTime )
{
    m_xBargainingTimer.StartTimer( nStartTime, nKeepTime );
}

void BargainingInfo::ClearBargainingData( unsigned char uchType )
{
    GamePlayer* pPlayerA = theRunTimeData.GetGamePlayerByDBID( m_xPlayerBargainingA.GetID() );
    if ( pPlayerA != NULL )
    {
        pPlayerA->SendBargainingFinishMessage( uchType );
    }

    GamePlayer* pPlayerB = theRunTimeData.GetGamePlayerByDBID( m_xPlayerBargainingB.GetID() );
    if ( pPlayerB != NULL )
    {
        pPlayerB->SendBargainingFinishMessage( uchType );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

BargainingManager::BargainingManager() : m_nBargainingID( BargainingDefine::NoneID )
{   
    m_mapInvite.clear();
    m_mapBargaining.clear();
    m_xUpdateTimer.StartTimer( 1, 5000 );
}

BargainingManager::~BargainingManager()
{
    for ( BargainingMapIter iter = m_mapBargaining.begin(); iter != m_mapBargaining.end(); ++iter )
    {
        iter->second->Release();
    }
    m_mapBargaining.clear();
}

BargainingInfo* BargainingManager::CreateBargaining()
{
    BargainingInfo* pBargaining = BargainingInfo::Instace();
    if ( pBargaining == NULL )
    { return NULL; }

    // 加入交易列表中
    unsigned int nBargainingID = GetBarganingID();

    pBargaining->SetID( nBargainingID );
    m_mapBargaining[ nBargainingID ] = pBargaining;

    return pBargaining;
}

BargainingInfo* BargainingManager::GetBargaining( unsigned int nBargainingID )
{
    BargainingMapIter iter = m_mapBargaining.find( nBargainingID );
    if ( iter == m_mapBargaining.end() )
    { return NULL; }

    return iter->second;
}

void BargainingManager::RemoveBargaining( unsigned int nBargainingID, unsigned char uchRemoveType )
{
    BargainingMapIter iter = m_mapBargaining.find( nBargainingID );
    if ( iter == m_mapBargaining.end() )
    { return; }

    iter->second->ClearBargainingData( uchRemoveType );
    iter->second->Release();

    m_mapBargaining.erase( iter );
}

void BargainingManager::AddBargainingInvite( unsigned int nReqID, unsigned int nAckID )
{
    BargainingInvite xInvite;
    xInvite.SetInviteID( nReqID );
    xInvite.StartTimer( HQ_TimeGetTime(), BargainingDefine::InviteKeepTime );

    m_mapInvite[ nAckID ] = xInvite;
}

void BargainingManager::RemoveBargainingInvite( unsigned int nAckID )
{
    BargainingInviteMapIter iter = m_mapInvite.find( nAckID );
    if ( iter == m_mapInvite.end() )
    { return; }

    m_mapInvite.erase( iter );
}

unsigned int BargainingManager::GetBargainingInvite( unsigned int nAckID )
{
    BargainingInviteMapIter iter = m_mapInvite.find( nAckID );
    if ( iter == m_mapInvite.end() )
    { return BargainingDefine::NoneID; }

    return iter->second.GetInviteID();
}

unsigned int BargainingManager::GetBarganingID()
{
    ++m_nBargainingID;
    if ( m_nBargainingID > BargainingDefine::MaxBargainingID )
    { m_nBargainingID = 1; }

    return m_nBargainingID;
}

void BargainingManager::UpdateBargainingInvite( unsigned int nCurrentTime )
{
    for ( BargainingInviteMapIter iter = m_mapInvite.begin(); iter != m_mapInvite.end(); )
    {
        if ( !iter->second.CheckTimer() )
        {
            ++iter;
            continue;
        }
    
        // 超时认为对方已经拒绝
        GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( iter->second.GetInviteID() );
        if ( pPlayer != NULL )
        { pPlayer->SendBargainingAckMessage( BargainingDefine::FailedRefuse ); }

        iter = m_mapInvite.erase( iter );
    }
}

void BargainingManager::UpdateBargaining( unsigned int nCurrentTime )
{
    for ( BargainingMapIter iter = m_mapBargaining.begin(); iter != m_mapBargaining.end(); )
    {
        if ( iter->second->CheckTimer() )
        {
            iter->second->ClearBargainingData( BargainingDefine::FinishTimeOut );
            iter->second->Release();
            iter = m_mapBargaining.erase( iter );
        }
        else
        {
            ++iter;
        }
    }
}

void BargainingManager::RunUpdate( unsigned int nCurrentTime )
{
    if ( !m_xUpdateTimer.DoneTimer( nCurrentTime ) )
    { return; }

    UpdateBargainingInvite( nCurrentTime );

    UpdateBargaining( nCurrentTime );
}