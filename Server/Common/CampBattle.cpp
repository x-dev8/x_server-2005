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

    // 找到场景, 释放掉
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
    { return; } // 已经存在列表中了

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

    // 如果是红方阵营
	BattlePlayer* pBattlePlayer = GetBattlePlayer( pPlayer->GetDBCharacterID() );
	if(pBattlePlayer)
	{
		if(pBattlePlayer->GetFightCamp() != pPlayer->GetFightCamp())
			pPlayer->SetFightCamp(pBattlePlayer->GetFightCamp());//玩家的阵营错误了 重新设置下不发生到客户端去
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
    { return; } // 不在战斗状态, 不处理逻辑

    const CampBattleConfig::ResourceSetting& xSetting = m_pBattleManager->GetBattleConfig()->GetResourceSetting();

    BattlePlayer* pBeKillBattlePlayer = GetBattlePlayer( pBeKill->GetDBCharacterID() );
    if (pBeKillBattlePlayer == NULL )
    { return; }

    // 杀人者名字
    char szKillerName[ CampDefine::NameLength ] = { 0 };
    HelperFunc::SafeNCpy( szKillerName, pKiller->GetCharName(), sizeof( szKillerName ) );

    // 连续杀人
    int nKeepKillCount = 1;
    
    // 如果杀人的是玩家
    BattlePlayer* pKillerBattlePlayer = NULL;
    if ( pKiller->IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* >( pKiller );
        pKillerBattlePlayer = GetBattlePlayer( pPlayer->GetDBCharacterID() );
        if ( pKillerBattlePlayer != NULL )
        {
            // 杀人者加记数, 加积分
            pKillerBattlePlayer->AddKeepKillCount( 1 );
            pKillerBattlePlayer->AddTotalKillCount( 1 );
            pKillerBattlePlayer->AddResource( xSetting.GetKillResource() );
			//设置总杀人数
			if(CampDefine::GetBaseFightCamp(pKillerBattlePlayer->GetFightCamp()) == CampDefine::BaseCampRed)
				m_RedTotleKillSum++;
			else if(CampDefine::GetBaseFightCamp(pKillerBattlePlayer->GetFightCamp()) == CampDefine::BaseCampBlue)
				m_BlueTotleKillSum++;
            nKeepKillCount = pKillerBattlePlayer->GetKeepKillCount();
        }
    }

    // 处理传说中的一血
    PorcessFirstKillPlayer( szKillerName, pBeKill->GetCharName() );

    // 处理被杀
    ProcessBeKillByPlayer( szKillerName, pBeKillBattlePlayer );

    // 处理连续杀人
    ProcessKeepKillPlayer( szKillerName, nKeepKillCount, pBeKill->GetCharName() );

    // 处理总共杀人, 全世界广播
    if ( pKillerBattlePlayer != NULL )
    { ProcessTotalKillPlayer( pKillerBattlePlayer, pBeKillBattlePlayer ); }

    // 处理积分达到 是否胜利
    ProcessAddCampResource( pKiller->GetFightCamp(), xSetting.GetKillResource() );
}

void CampBattle::PorcessFirstKillPlayer( const char* szKillerName, const char* szBeKillName )
{
    if ( !GetFirstKill() )
    { return; }
    SetFirstKill( false );

    const CampBattleConfig::KillSetting& xSetting = m_pBattleManager->GetBattleConfig()->GetFirstKillSetting();

    // 通知场景所有玩家
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
    { return; } // 不在战斗状态, 不处理逻辑

	//zhuxincong 2013.1.14 注释
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

    // 如果有一边达到了最大值, 让战场结束
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

    // 通知场景里所有玩家
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
        // 双方都没人进入, 直接销毁战场
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
	if(BuffID != 0 && Level != 0) //玩家刚进入的时候添加一个BUFF
	{
		GameStage* pGameStage = theGameWorld.GetStageById(m_nEctypeMapID);
		if(pGameStage)
		{
			//获取地图块后 我们获取全部的玩家
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
    // 启动战场销毁定时器
    m_xReleaseTimer.StartTimer( HQ_TimeGetTime(), CampDefine::ReleaseSapceTime );

    // 计算战场结果
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
                // 指定阵营需要判断阵营信息
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

    // 添加个人积分
    BattlePlayer* pBattlePlayer = GetBattlePlayer( nPlayerID );
    if ( pBattlePlayer != NULL )
    { 
        // 添加个人积分
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

    // 添加战场积分
    ProcessAddCampResource( uchFightCamp, pSetting->GetResource() );
}

unsigned char CampBattle::GetBattleFightCamp( unsigned int nUnitID )
{
    // 红方阵营
    unsigned char uchFightCamp = m_pBattleManager->GetBattleType() * 2 + 1;
    if ( GetBlueID() == nUnitID )
    { uchFightCamp += 1; }

    return uchFightCamp;
}
