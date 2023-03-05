#include "CountryManager.h"
#include "GameServer.h"

template<>
void GameCountryManager::SendCountryDataToGameServer( unsigned int nServerID )
{
}

template<>
void GameCountryManager::CalcWeakCountry()
{
}
template<>
void GameCountryManager::CalcStrongCountry()
{
}
template<>
void GameCountryManager::RunUpdate( unsigned int nCurrentTime )
{
    if ( !m_xWarFightTimer.DoneTimer( nCurrentTime ) )
    { return; }

    MsgUpdateCountryWarFightKill xUpdate;
    for ( int i = 0; i < CountryDefine::Country_Max; ++i )
    {
        xUpdate.nKillCount[ i ] = m_xCountry[ i ].GetKillCount();
    }

    GettheServer().SendMsgToWorld( &xUpdate, false );
}

template<>
void GameCountryManager::SendWarStatusChangeMessage()
{
    if ( m_uchWarStatus == CountryDefine::WarStatusInit )
    { return; }     // 初始状态不发消息

    switch( m_uchWarStatus )
    {
    case CountryDefine::WarStatusFight:
        m_xWarFightTimer.StartTimer( HQ_TimeGetTime(), CountryDefine::UpdateWarKillTime );  // 开启定时器
        break;
    case CountryDefine::WarStatusEnd:
        m_xWarFightTimer.StopTimer();
        break;
    }

    MsgTellCountryWarStatus xStatus;
    xStatus.uchStatus = m_uchWarStatus;
    GettheServer().SendMsgToWorld( &xStatus, false );
}

template<>
void GameCountryManager::SendWarFightKillPlayerMessage( unsigned char uchKillCountryID, unsigned char uchDeathCountryID )
{
    GS2CSCountryWarKillPlayer xKill;
    xKill.uchKillCountryID  = uchKillCountryID;
    xKill.uchDeathCountryID = uchDeathCountryID;
    GettheServer().SendMsgToCenterServer( &xKill );
}

template<>
void GameCountryManager::ProcessWarKillPlayer( unsigned char uchKillCountryID, unsigned int nKillCount, unsigned char uchDeathCountryID, unsigned int nDeathCount )
{
    GameCountry* pKillCountry = GetCountry( uchKillCountryID );
    GameCountry* pDeathCountry = GetCountry( uchDeathCountryID );
    if ( pKillCountry == NULL || pDeathCountry == NULL )
    { return; }

    pKillCountry->SetKillCount( nKillCount );
    pDeathCountry->SetDeathCount( nDeathCount );
}
template<>
void GameCountryManager::HandleAllCountryStrength(bool IsSendMsg)
{
	
}
template<>
void GameCountryManager::CalcCountryStrengthAtOnce()
{

}