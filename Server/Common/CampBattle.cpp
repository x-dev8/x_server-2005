#include "CampBattle.h"
#include "GamePlayer.h"
#include "ShareData.h"
#include "CampBattleConfig.h"
#include "CampBattleMessage.h"
#include "GameWorld.h"
#include "CampBattleManager.h"

CampBattle::CampBattle() : m_nEctypeMapID( 0 ), m_bFirstKill( true ), m_nRedResource( 0 ), m_nBlueResource( 0 ), m_uchStatus( CampDefine::StatusEnter ),
                           m_nRedID( 0 ), m_nBlueID( 0 ), m_nWinResource( 100 ),m_RedTotleKillSum(0),m_BlueTotleKillSum(0)
{
    m_mapBattlePlayer.clear();
    m_pBattleManager = NULL;
}

unsigned char CampBattle::RunUpdate( unsigned int nCurrentTime )
{
    switch ( GetStatus() )
    {
    case CampDefine::StatusEnter:
        ProcessCampBattleEnterStatus();
        break;
    case CampDefine::StatusFight:
        ProcessCampBattleFightStatus();
        break;
    case CampDefine::StatusEnd:
        ProcessCampBattleEndStatus();
        break;
    default:
        SetStatus( CampDefine::StatusRelease );
        break;
    }

    return GetStatus();
}

void CampBattle::ProcessCampBattleFightStatus()
{
}

void CampBattle::ProcessCampBattleEndStatus()
{
    if ( !m_xReleaseTimer.DoneTimer() )
    { return; }

    SetStatus( CampDefine::StatusRelease );

    m_mapBattlePlayer.clear();

    // �ҵ�����, �ͷŵ�
    GameStage* pStage = theGameWorld.GetStageById( GetBattleMapID() );
    if ( pStage != NULL && pStage->IsEctypeStage() )
    { pStage->SetStageWaitRelease( true ); }
}

void CampBattle::AddBattlePlayer( unsigned int nPlayerID, BattlePlayer& xPlayer )
{
    if ( xPlayer.GetFightCamp() == CampDefine::NoneCamp )
    { return; }

    BattlePlayer* pBattlePlayer = GetBattlePlayer( nPlayerID );
    if ( pBattlePlayer != NULL )
    { return; } // �Ѿ������б�����

    m_mapBattlePlayer[ nPlayerID ] = xPlayer;
}

BattlePlayer* CampBattle::GetBattlePlayer( unsigned int nPlayerID )
{
    BattlePlayerMapIter iter = m_mapBattlePlayer.find( nPlayerID ); 
    if ( iter == m_mapBattlePlayer.end() )
    { return NULL; }

    return &( iter->second );
}

int CampBattle::GetBattlePlayerCount( unsigned char uchFightCamp )
{
    int nCount = 0;
    for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
    {
        if ( iter->second.GetFightCamp() == uchFightCamp )
		{
			GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( iter->first );
			if ( pPlayer == NULL || pPlayer->GetMapID() != GetBattleMapID() )
			{ continue; }
			++nCount;
		}
    }

    return nCount;
}

unsigned int CampBattle::GetCampBattleResource( unsigned char uchFightCamp )
{
    switch ( CampDefine::GetBaseFightCamp( uchFightCamp ) )
    {
    case CampDefine::BaseCampRed:
        return GetRedResource();
        break;
    case CampDefine::BaseCampBlue:
        return GetBlueResource();
        break;
    default:
        break;
    }

    return 0;
}

unsigned int CampBattle::GetReliveIndex( GamePlayer* pPlayer )
{
    if ( GetStatus() == CampDefine::StatusRelease )
    { return CampDefine::DefaultReliveIndex; }

    // ����Ǻ췽��Ӫ
	BattlePlayer* pBattlePlayer = GetBattlePlayer( pPlayer->GetDBCharacterID() );
	if(pBattlePlayer)
	{
		if(pBattlePlayer->GetFightCamp() != pPlayer->GetFightCamp())
			pPlayer->SetFightCamp(pBattlePlayer->GetFightCamp());//��ҵ���Ӫ������ ���������²��������ͻ���ȥ
	}

    if ( CampDefine::GetBaseFightCamp( pPlayer->GetFightCamp() ) == CampDefine::BaseCampRed )
    { return CampDefine::RedReliveIndex; }

    return CampDefine::BlueReliveIndex;
}

void CampBattle::SendCampMessage( Msg* pMessage, unsigned char uchFightCamp )
{
    for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
    {
        if ( iter->second.GetFightCamp() != uchFightCamp )
        { continue; }

        GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( iter->first );
        if ( pPlayer == NULL || pPlayer->GetMapID() != GetBattleMapID() )
        { continue; }

        pPlayer->SendMessageToClient( pMessage );
    }
}

void CampBattle::ProcessKillPlayer( BaseCharacter* pKiller, GamePlayer* pBeKill )
{
    if ( pKiller == NULL || pBeKill == NULL )
    { return; }

    if ( GetStatus() != CampDefine::StatusFight )
    { return; } // ����ս��״̬, �������߼�

    const CampBattleConfig::ResourceSetting& xSetting = m_pBattleManager->GetBattleConfig()->GetResourceSetting();

    BattlePlayer* pBeKillBattlePlayer = GetBattlePlayer( pBeKill->GetDBCharacterID() );
    if (pBeKillBattlePlayer == NULL )
    { return; }

    // ɱ��������
    char szKillerName[ CampDefine::NameLength ] = { 0 };
    HelperFunc::SafeNCpy( szKillerName, pKiller->GetCharName(), sizeof( szKillerName ) );

    // ����ɱ��
    int nKeepKillCount = 1;
    
    // ���ɱ�˵������
    BattlePlayer* pKillerBattlePlayer = NULL;
    if ( pKiller->IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* >( pKiller );
        pKillerBattlePlayer = GetBattlePlayer( pPlayer->GetDBCharacterID() );
        if ( pKillerBattlePlayer != NULL )
        {
            // ɱ���߼Ӽ���, �ӻ���
            pKillerBattlePlayer->AddKeepKillCount( 1 );
            pKillerBattlePlayer->AddTotalKillCount( 1 );
            pKillerBattlePlayer->AddResource( xSetting.GetKillResource() );
			//������ɱ����
			if(CampDefine::GetBaseFightCamp(pKillerBattlePlayer->GetFightCamp()) == CampDefine::BaseCampRed)
				m_RedTotleKillSum++;
			else if(CampDefine::GetBaseFightCamp(pKillerBattlePlayer->GetFightCamp()) == CampDefine::BaseCampBlue)
				m_BlueTotleKillSum++;
            nKeepKillCount = pKillerBattlePlayer->GetKeepKillCount();
        }
    }

    // ����˵�е�һѪ
    PorcessFirstKillPlayer( szKillerName, pBeKill->GetCharName() );

    // ����ɱ
    ProcessBeKillByPlayer( szKillerName, pBeKillBattlePlayer );

    // ��������ɱ��
    ProcessKeepKillPlayer( szKillerName, nKeepKillCount, pBeKill->GetCharName() );

    // �����ܹ�ɱ��, ȫ����㲥
    if ( pKillerBattlePlayer != NULL )
    { ProcessTotalKillPlayer( pKillerBattlePlayer, pBeKillBattlePlayer ); }

    // ������ִﵽ �Ƿ�ʤ��
    ProcessAddCampResource( pKiller->GetFightCamp(), xSetting.GetKillResource() );
}

void CampBattle::PorcessFirstKillPlayer( const char* szKillerName, const char* szBeKillName )
{
    if ( !GetFirstKill() )
    { return; }
    SetFirstKill( false );

    const CampBattleConfig::KillSetting& xSetting = m_pBattleManager->GetBattleConfig()->GetFirstKillSetting();

    // ֪ͨ�����������
    MsgTellCampBattleKillPlayer xTell;
    xTell.uchCampBattleType = m_pBattleManager->GetBattleType();
    xTell.uchKillType       = MsgTellCampBattleKillPlayer::TypeFirstKill;
    xTell.ustKillCount      = 1;
    xTell.ustStringID       = xSetting.GetString();
    HelperFunc::SafeNCpy( xTell.szKillerName, szKillerName, sizeof( xTell.szKillerName ) );
    HelperFunc::SafeNCpy( xTell.szBeKillName, szBeKillName, sizeof( xTell.szBeKillName ) );
    GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
}

void CampBattle::ProcessKeepKillPlayer( const char* szKillerName, int nKillCount, const char* szBeKillName )
{
    const CampBattleConfig::KillSetting* pSetting = m_pBattleManager->GetBattleConfig()->GetKillerSetting( nKillCount );
    if ( pSetting == NULL )
    { return; }

    MsgTellCampBattleKillPlayer xTell;
    xTell.uchCampBattleType = m_pBattleManager->GetBattleType();
    xTell.uchKillType       = MsgTellCampBattleKillPlayer::TypeKeepKill;
    xTell.ustKillCount      = nKillCount;
    xTell.ustStringID       = pSetting->GetString();
    HelperFunc::SafeNCpy( xTell.szKillerName, szKillerName, sizeof( xTell.szKillerName ) );
    HelperFunc::SafeNCpy( xTell.szBeKillName, szBeKillName, sizeof( xTell.szBeKillName ) );
    GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
}

void CampBattle::ProcessBeKillByPlayer( const char* szKillerName, BattlePlayer* pBeKillBattlePlayer )
{
    unsigned int nKeepKillCount = pBeKillBattlePlayer->GetKeepKillCount();
    pBeKillBattlePlayer->SetKeepKillCount( 0 );
    pBeKillBattlePlayer->AddTotalDeathCount( 1 );

    const CampBattleConfig::KillSetting* pSetting = m_pBattleManager->GetBattleConfig()->GetBeKillSetting( nKeepKillCount );
    if ( pSetting == NULL )
    { return; }

    MsgTellCampBattleKillPlayer xTell;
    xTell.uchCampBattleType = m_pBattleManager->GetBattleType();
    xTell.uchKillType       = MsgTellCampBattleKillPlayer::TypeBeKill;
    xTell.ustKillCount      = nKeepKillCount;
    xTell.ustStringID       = pSetting->GetString();
    HelperFunc::SafeNCpy( xTell.szKillerName, szKillerName, sizeof( xTell.szKillerName ) );
    HelperFunc::SafeNCpy( xTell.szBeKillName, pBeKillBattlePlayer->GetName(), sizeof( xTell.szBeKillName ) );
    GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
}

void CampBattle::ProcessTotalKillPlayer( BattlePlayer* pKillerBattlePlayer, BattlePlayer* pBeKillBattlePlayer )
{
    const CampBattleConfig::KillSetting* pSetting = m_pBattleManager->GetBattleConfig()->GetTotalKillSetting( pKillerBattlePlayer->GetTotalKillCount() );
    if ( pSetting == NULL )
    { return; }

    MsgTellCampBattleKillPlayer xTell;
    xTell.uchCampBattleType = m_pBattleManager->GetBattleType();
    xTell.uchKillType       = MsgTellCampBattleKillPlayer::TypeTotalKill;
    xTell.ustKillCount      = pKillerBattlePlayer->GetTotalKillCount();
    xTell.ustStringID       = pSetting->GetString();
    HelperFunc::SafeNCpy( xTell.szKillerName, pKillerBattlePlayer->GetName(), sizeof( xTell.szKillerName ) );
    HelperFunc::SafeNCpy( xTell.szBeKillName, pBeKillBattlePlayer->GetName(), sizeof( xTell.szBeKillName ) );
	GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
    //GettheServer().SendMsgToCountry( &xTell, m_pBattleManager->GetCountryID(), true );
}

void CampBattle::ProcessAddCampResource( unsigned char uchFightCamp, unsigned int nAddResource )
{
    if ( nAddResource == 0 || GetStatus() != CampDefine::StatusFight )
    { return; } // ����ս��״̬, �������߼�

	//zhuxincong 2013.1.14 ע��
    switch ( CampDefine::GetBaseFightCamp( uchFightCamp ) )
    {
    case CampDefine::BaseCampRed:
        {   
            AddRedResource( nAddResource );
            if ( GetRedResource() < GetWinResource() )
            { return; }
        }
        break;
    case CampDefine::BaseCampBlue:
        {
            AddBlueResource( nAddResource );

            if ( GetBlueResource() < GetWinResource() )
            { return; }
        }
        break;
    default:
        return;
        break;
    }

    // �����һ�ߴﵽ�����ֵ, ��ս������
    ProcessStatusChange( CampDefine::StatusEnd );
}

void CampBattle::ProcessStatusChange( unsigned char uchStatus )
{
    if ( GetStatus() == CampDefine::StatusEnd )
    { return; }

    SetStatus( uchStatus );

    switch ( GetStatus() )
    {
    case CampDefine::StatusFight:
        ProcessChangeToFightStatus();
        break;
    case CampDefine::StatusEnd:
        ProcessChangeToEndStatus();
        break;
    default:
        break;
    }

    // ֪ͨ�������������
    SendBattleStatusMessage();
}

void CampBattle::SendBattleStatusMessage( GamePlayer* pPlayer /* = NULL*/ )
{
    MsgTellCampBattleStatus xTell;
    xTell.uchCampBattleType   = m_pBattleManager->GetBattleType();
    xTell.uchCampBattleStatus = GetStatus();
    xTell.nLeftTime           = m_pBattleManager->GetLeftTime() / 1000;

    if ( pPlayer == NULL )
    { GettheServer().SendMsgToStage( &xTell, GetBattleMapID() ); }
    else
    { pPlayer->SendMessageToClient( &xTell ); }
}

void CampBattle::SendCampBattleMatchMessage( GamePlayer* pPlayer )
{
    MsgTellCampBattleMatch xTell;
    xTell.uchBattleType = m_pBattleManager->GetBattleType();
    xTell.nRedID        = m_nRedID;
    xTell.nBlueID       = m_nBlueID;
    pPlayer->SendMessageToClient( &xTell );
}

void CampBattle::ProcessChangeToFightStatus()
{
    if ( m_mapBattlePlayer.empty() )
    {
        // ˫����û�˽���, ֱ������ս��
        SetStatus( CampDefine::StatusRelease );
        return;
    }

    int nRedPlayerCount = 0;
    int nBluePlayerCount = 0;
    for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
    {
        switch( CampDefine::GetBaseFightCamp( iter->second.GetFightCamp() ) )
        {
        case CampDefine::BaseCampRed:
            ++nRedPlayerCount;
            break;
        case CampDefine::BaseCampBlue:
            ++nBluePlayerCount;
            break;
        default:
            break;
        }
    }

	int BuffID = m_pBattleManager->GetBattleConfig()->GetEnterBuff().GetBuffID();
	int Level = m_pBattleManager->GetBattleConfig()->GetEnterBuff().GetLevel();
	if(BuffID != 0 && Level != 0) //��Ҹս����ʱ�����һ��BUFF
	{
		GameStage* pGameStage = theGameWorld.GetStageById(m_nEctypeMapID);
		if(pGameStage)
		{
			//��ȡ��ͼ��� ���ǻ�ȡȫ�������
			for(int i =0;i<pGameStage->GetCharacterCount();++i)
			{
				BaseCharacter * pBase = theRunTimeData.GetCharacterByID(pGameStage->GetCharacterID(i));
				if(pBase && pBase->IsPlayer())
				{
					GamePlayer * pPlayer = static_cast<GamePlayer*>(pBase);
					if(pPlayer && pPlayer->GetBuffManager()->ClearBuffByBuffIdLevel(BuffID,Level))
						pPlayer->OnBuffStatusChanged( true );
				}
			}
		}
	}

    if ( nRedPlayerCount == 0 )
    {
        ProcessAddCampResource( CampDefine::BaseCampBlue, m_nWinResource );
        return;
    }

    if ( nBluePlayerCount == 0 )
    {
        ProcessAddCampResource( CampDefine::BaseCampRed, m_nWinResource );
        return;
    }
}

void CampBattle::ProcessChangeToEndStatus()
{
    // ����ս�����ٶ�ʱ��
    m_xReleaseTimer.StartTimer( HQ_TimeGetTime(), CampDefine::ReleaseSapceTime );

    // ����ս�����
    ProcessCalcCampBattleWinner();
}

void CampBattle::ProcessCalcCampBattleWinner()
{
    unsigned char uchFightCamp = CampDefine::NoneCamp;
    if ( GetRedResource() >= GetBlueResource() )
    { uchFightCamp = CampDefine::BaseCampRed; }
    else
    { uchFightCamp = CampDefine::BaseCampBlue; }

    ProcessCampBattleResult( uchFightCamp );
}

void CampBattle::SendBattlePlayerMessage( GamePlayer* pPlayer, unsigned char uchFightCamp )
{
    MsgTellCampBattlePlayer xTell;
    xTell.uchCampBattleType = m_pBattleManager->GetBattleType();

    for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
    { 
        switch( uchFightCamp )
        {
        case CampDefine::BaseCampRed:   
        case CampDefine::BaseCampBlue:   
            {
                // ָ����Ӫ��Ҫ�ж���Ӫ��Ϣ
                if ( iter->second.GetFightCamp() != uchFightCamp )
                { continue; }
            }
        default:
            xTell.AddBattlePlayer( iter->second ); 
            break;
        }
    }
    
    pPlayer->SendMessageToClient( &xTell );
}

void CampBattle::KillCampBattleMonster( unsigned char uchFightCamp, unsigned int nPlayerID, int nMonsterID )
{
    const CampBattleConfig* pBattleConfig = m_pBattleManager->GetBattleConfig();
    const CampBattleConfig::MonsterSetting* pSetting = pBattleConfig->GetMonsterSetting( nMonsterID );
    if ( pSetting == NULL )
    { return; }

    // ��Ӹ��˻���
    BattlePlayer* pBattlePlayer = GetBattlePlayer( nPlayerID );
    if ( pBattlePlayer != NULL )
    { 
        // ��Ӹ��˻���
        pBattlePlayer->AddResource( pSetting->GetResource() ); 
    }

    if ( pSetting->GetString() != 0 )
    {
        MsgKillCampBattleMonster xKill;
        xKill.uchBattleType = m_pBattleManager->GetBattleType();
        xKill.uchFightCamp  = uchFightCamp;
        xKill.nMonsterID    = nMonsterID;
        xKill.nStringID     = pSetting->GetString();
        GettheServer().SendMsgToStage( &xKill, GetBattleMapID() );
    }

    // ���ս������
    ProcessAddCampResource( uchFightCamp, pSetting->GetResource() );
}

unsigned char CampBattle::GetBattleFightCamp( unsigned int nUnitID )
{
    // �췽��Ӫ
    unsigned char uchFightCamp = m_pBattleManager->GetBattleType() * 2 + 1;
    if ( GetBlueID() == nUnitID )
    { uchFightCamp += 1; }

    return uchFightCamp;
}
