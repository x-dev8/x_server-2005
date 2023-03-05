#include "GameGuildGeneralBattle.h"
#include "GamePlayer.h"
#include "ShareData.h"
#include "GameGuildGeneralBattleConfig.h"
#include "GameGuildGeneralBattleManager.h"
#include "GameWorld.h"
#include "XmlStringLanguage.h"
#include "MonsterCreater.h"
#include "GameBattleMessage.h"
#include "CampBattleMessage.h"
GameGuildGeneralBattle::GameGuildGeneralBattle() : m_nEctypeMapID( 0 ), m_bFirstKill( true ), m_nRedResource( 0 ), m_nBlueResource( 0 ), m_uchStatus( GameBattleDefine::StatusEnter ),
                           m_nRedID( 0 ), m_nBlueID( 0 ), m_nWinResource( 100 ),m_RedTotleKillSum(0),m_BlueTotleKillSum(0)
{
    m_mapBattlePlayer.clear();
    m_pManager = NULL;
	m_RedBoss = NULL;
	m_BlueBoss = NULL;

	m_xRefreshTimer.StartTimer( 1, 3000 );
	m_BlueBarracksDeadSum = 0;
	m_RedBarracksDeadSum = 0;

	m_xNormalTimer.clear();
}
void GameGuildGeneralBattle::SetGuildGameBattleTimeMap()
{
	if(!m_pManager)
		return;
	const GameGuildGeneralBattleConfig* pBattleConfig = m_pManager->GetBattleConfig();
	if(pBattleConfig)
	{
		map<int,GameGuildGeneralBattleConfig::NormalMonster> mapList;
		pBattleConfig->GetNormalMonster(mapList);
		map<int,GameGuildGeneralBattleConfig::NormalMonster>::iterator Iter = mapList.begin();
		for(;Iter !=mapList.end();++Iter)
		{
			GameTimerEx ex;
			m_xNormalTimer.insert(std::map<int,GameTimerEx>::value_type(Iter->first,ex));
		}
	}
}
void GameGuildGeneralBattle::SetStatus( unsigned char uchValue )
{
    m_uchStatus = uchValue;
	if(m_pManager->GetGameBattleOnceInfo(GetBattleIndexID()))
		m_pManager->GetGameBattleOnceInfo(GetBattleIndexID())->SetBattleStatus(uchValue);
}
unsigned char GameGuildGeneralBattle::RunUpdate( unsigned int nCurrentTime )
{
    switch ( GetStatus() )
    {
    case GameBattleDefine::StatusEnter:
        ProcessGameBattleEnterStatus();
        break;
    case GameBattleDefine::StatusFight:
        ProcessGameBattleFightStatus();
        break;
    case GameBattleDefine::StatusEnd:
        ProcessGameBattleEndStatus();
        break;
    default:
		SetStatus( GameBattleDefine::StatusRelease );
        break;
    }
    return GetStatus();
}
void GameGuildGeneralBattle::Init()
{

}
void GameGuildGeneralBattle::Destroy()
{
	Release();//����ս��
}
void GameGuildGeneralBattle::Release()
{
    ReleaseGameGuildGeneralBattle< GameGuildGeneralBattle >( this );
}
void GameGuildGeneralBattle::SendGameBattleResourceMessage()
{
	// 5��ͬ��һ����Դ��
    MsgTellGameBattleResource xTell;
	xTell.nRedGuildID = m_nRedID;
	xTell.nBlueGuildID = m_nBlueID;
    xTell.nRedResource  = m_nRedResource;
    xTell.nBlueResource = m_nBlueResource;
	xTell.nBlueTotleKillSum = m_BlueTotleKillSum;
	xTell.nRedTotleKillSum = m_RedTotleKillSum;
	//��˫����Ӫ��Ѫ��������¼����
	const GameGuildGeneralBattleConfig* pBattleConfig = m_pManager->GetBattleConfig();
	if(pBattleConfig->GetGetRefreshSettingCount() != 3)
		return;
    for ( int i = 0; i < pBattleConfig->GetGetRefreshSettingCount(); ++i )
    {
        const GameGuildGeneralBattleConfig::RefreshSetting* pSetting = pBattleConfig->GetRefreshSettingByIndex( i );
        if ( pSetting == NULL )
        { continue; }	
		if(m_RedBarracks.size() <= i || m_BlueBarracks.size() <= i)
			continue;
		MonsterBaseEx * pCreate = (MonsterBaseEx *)theRunTimeData.GetCharacterByID( m_RedBarracks[i]);
		if(pCreate == NULL || pCreate->GetHPMax() == 0/*|| pCreate->GetMonsterID() !=pSetting->GetBarracksID()*/)
		{
			 xTell.nRedAtterHp[i] = 0;
			 m_RedBarracks[i] = NULL;
		}
		else
		{
			 xTell.nRedAtterHp[i] = (pCreate->GetHP() * 1.0)/pCreate->GetHPMax();
		}
		
		pCreate = (MonsterBaseEx *)theRunTimeData.GetCharacterByID( m_BlueBarracks[i]);
		if(pCreate == NULL  || pCreate->GetHPMax() == 0/*|| pCreate->GetMonsterID() !=pSetting->GetBarracksID()*/)
		{
			 xTell.nBlueAtterHp[i] = 0;
			 m_BlueBarracks[i] = NULL;
		}
		else
		{
			 xTell.nBlueAtterHp[i] = (pCreate->GetHP() * 1.0)/pCreate->GetHPMax();
		}
	}
	if(m_RedBoss && m_RedBoss->GetHPMax() != 0)
	{
		 xTell.nRedAtterHp[3] = (m_RedBoss->GetHP() * 1.0)/m_RedBoss->GetHPMax();
	}
	else
	{
		if(m_RedBarracksDeadSum == pBattleConfig->GetGetRefreshSettingCount() || m_RedBarracksDeadSum == -1)
		{
			xTell.nRedAtterHp[3] = 0;
		}
		else
		{
			xTell.nRedAtterHp[3] = 100;
		}
	}
	if(m_BlueBoss  && m_BlueBoss->GetHPMax() != 0)
	{
		 xTell.nBlueAtterHp[3] = (m_BlueBoss->GetHP() * 1.0)/m_BlueBoss->GetHPMax();
	}
	else
	{
		if(m_BlueBarracksDeadSum == pBattleConfig->GetGetRefreshSettingCount() || m_BlueBarracksDeadSum == -1)
		{
			xTell.nBlueAtterHp[3] = 0;
		}
		else
		{
			xTell.nBlueAtterHp[3] = 100;
		}
	}
    GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
}
void GameGuildGeneralBattle::ProcessGameBattleEnterStatus()
{
	if ( !m_xRefreshTimer.DoneTimer( HQ_TimeGetTime() ) )
    { return; }

    GameStage* pStage = theGameWorld.GetStageById( GetBattleMapID() );
    if ( pStage == NULL )
    { return; }

    // ��ֹͣ��ʱ��
    m_xRefreshTimer.StopTimer();

    m_mapRefreshIndex.clear();

    MonsterCreateData xCreateData;
    xCreateData.SetMapID( pStage->GetStageID() );

	const GameGuildGeneralBattleConfig* pBattleConfig = m_pManager->GetBattleConfig();
    for ( int i = 0; i < pBattleConfig->GetGetRefreshSettingCount(); ++i )
    {
        const GameGuildGeneralBattleConfig::RefreshSetting* pSetting = pBattleConfig->GetRefreshSettingByIndex( i );
        if ( pSetting == NULL )
        { continue; }

        const GameGuildGeneralBattleConfig::RefreshSetting::BarracksSetting& xRedSetting = pSetting->GetRedBarracksSetting();

        xCreateData.SetMonsterID( xRedSetting.GetMonsterID());
        xCreateData.SetPostionX( xRedSetting.GetPosX() );
        xCreateData.SetPostionY( xRedSetting.GetPosY() );

		xCreateData.SetDirection(xRedSetting.GetAngle());

        xCreateData.SetFightCamp( GameBattleDefine::GameBattle_Red );
		xCreateData.SetMapID(m_nEctypeMapID);	
		MonsterBaseEx*  pMonst = MonsterCreater::CreateBuildMonster( xCreateData );
		if(pMonst)
			m_RedBarracks.push_back(pMonst->GetID());

        const GameGuildGeneralBattleConfig::RefreshSetting::BarracksSetting& xBlueSetting = pSetting->GetBlueBarracksSetting();

        xCreateData.SetMonsterID( xBlueSetting.GetMonsterID());
        xCreateData.SetPostionX( xBlueSetting.GetPosX() );
        xCreateData.SetPostionY( xBlueSetting.GetPosY() );
		xCreateData.SetDirection(xBlueSetting.GetAngle());
        xCreateData.SetFightCamp( GameBattleDefine::GameBattle_Blue );
		xCreateData.SetMapID(m_nEctypeMapID);
		pMonst = MonsterCreater::CreateBuildMonster( xCreateData );
		if(pMonst)
			m_BlueBarracks.push_back(pMonst->GetID());

        // ����ˢ����Ϣ
        RefreshIndex xRefreshIndex;
        xRefreshIndex.SetRedIndex( 0 );
        xRefreshIndex.SetMaxRedIndex( xRedSetting.GetMonsterCount() - 1 );
        xRefreshIndex.SetBlueIndex( 0 );
        xRefreshIndex.SetMaxBlueIndex( xBlueSetting.GetMonsterCount() - 1 );
        m_mapRefreshIndex.insert( std::make_pair( pSetting->GetBarracksID(), xRefreshIndex ) );
    }

    // ˢ��������Ӫ��
    for ( int i = 0; i < pBattleConfig->GetRedCampMonsterCount(); ++i )
    {
        const GameGuildGeneralBattleConfig::CampMonster* pMonster = pBattleConfig->GetRedCampMonster( i );
        if ( pMonster == NULL )
        { continue; }

        xCreateData.SetMonsterID( pMonster->GetID() );
        xCreateData.SetPostionX( pMonster->GetPosX() );
        xCreateData.SetPostionY( pMonster->GetPosY() );
		xCreateData.SetDirection(pMonster->GetAngle());


        xCreateData.SetFightCamp( GameBattleDefine::GameBattle_Red );
		xCreateData.SetMapID(m_nEctypeMapID);

        MonsterCreater::CreateNormalMonster( xCreateData );
    }

    for ( int i = 0; i < pBattleConfig->GetBlueCampMonsterCount(); ++i )
    {
        const GameGuildGeneralBattleConfig::CampMonster* pMonster = pBattleConfig->GetBlueCampMonster( i );
        if ( pMonster == NULL )
        { continue; }

        xCreateData.SetMonsterID( pMonster->GetID() );
        xCreateData.SetPostionX( pMonster->GetPosX() );
        xCreateData.SetPostionY( pMonster->GetPosY() );
		xCreateData.SetDirection(pMonster->GetAngle());


        xCreateData.SetFightCamp( GameBattleDefine::GameBattle_Blue );
		xCreateData.SetMapID(m_nEctypeMapID);

        MonsterCreater::CreateNormalMonster( xCreateData );
    }
}
void GameGuildGeneralBattle::SendEnterGameBattleMessage()
{
    // ��õ�ͼID
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_pManager->GetGameBattleMapID() );
    if ( pMapData == NULL )
    { return; }

    // ��ý����NPC�ص�
    MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
    if ( pRelive == NULL )
    { return; }

    MsgFlyToGameBattleReq xReq;
    xReq.uchBattleType = m_pManager->GetGameBattleType();
    xReq.nMapID        = m_pManager->GetGameBattleMapID();	
	xReq.nKingdomID = m_pManager->GetBattleConfig()->GetKingdomMap().GetMapID();
	xReq.nKingdomX = m_pManager->GetBattleConfig()->GetKingdomMap().GetMapX();
	xReq.nKingdomY = m_pManager->GetBattleConfig()->GetKingdomMap().GetMapY();
	xReq.RedID = GetRedID();
	xReq.BlueID = GetBlueID();

    // �췽����
    GameGuild* pRedGuild = theGameGuildManager.GetGuild( m_nRedID );
    if ( pRedGuild != NULL )
    {
        pRedGuild->SendMessageToGuild( &xReq, GuildDefine::InitID, pMapData->MinPlayerLevel, true );
    }

    // ��������
    GameGuild* pBlueGuild = theGameGuildManager.GetGuild( m_nBlueID );
    if ( pBlueGuild != NULL )
    { 
        pBlueGuild->SendMessageToGuild( &xReq, GuildDefine::InitID, pMapData->MinPlayerLevel, true );
    }
}
void GameGuildGeneralBattle::ProcessGameBattleFightStatus()
{
	SendGameBattleResourceMessage();
    // ��ʱˢ��
    ProcessRefreshGameBattleMonster();

    // ������( Roshan )ˢ��
    ProcessRefreshNormalMonster();
}
void GameGuildGeneralBattle::ProcessRefreshGameBattleMonster()
{
	if ( !m_xRefreshTimer.DoneTimer( HQ_TimeGetTime() ) )
    { return; }

    GameStage* pStage = theGameWorld.GetStageById( GetBattleMapID() );
    if ( pStage == NULL )
    { return; }

    MonsterCreateData xCreateData;
    xCreateData.SetMapID( pStage->GetStageID() );
    xCreateData.SetCreateType( 0 );
    xCreateData.SetCount( GameGuildGeneralBattleConfig::RefreshSetting::GetCount() );
    xCreateData.SetRadius( GameGuildGeneralBattleConfig::RefreshSetting::GetRadius() );
    xCreateData.SetFightCamp( GameGuildGeneralBattleConfig::RefreshSetting::GetType() );

    const GameGuildGeneralBattleConfig* pBattleConfig = m_pManager->GetBattleConfig();
    for ( RefreshIndexMapIter iter = m_mapRefreshIndex.begin(); iter != m_mapRefreshIndex.end(); ++iter )
    {
        const GameGuildGeneralBattleConfig::RefreshSetting* pSetting = pBattleConfig->GetRefreshSetting( iter->first );
        if ( pSetting == NULL )
        { continue; }

        // �췽��Ӫˢ��
        const GameGuildGeneralBattleConfig::RefreshSetting::BarracksSetting& xRedBarrackSetting = pSetting->GetRedBarracksSetting();
        const GameGuildGeneralBattleConfig::RefreshSetting::MonsterDataList* pRedMonsterDataList = xRedBarrackSetting.GetMonster( iter->second.GetRedIndex() );
		if(pRedMonsterDataList != NULL)
		{
			//ˢ��һ����
			vector<GameGuildGeneralBattleConfig::RefreshSetting::MonsterData> vec;
			pRedMonsterDataList->GetAllMonster(vec);
			vector<GameGuildGeneralBattleConfig::RefreshSetting::MonsterData>::iterator Iter = vec.begin();
			for(;Iter !=vec.end();++Iter)
			{
				//��������ˢ��
				MonsterCreateData xCreateDataRed;
				xCreateDataRed.SetMapID( pStage->GetStageID() );
				xCreateDataRed.SetCount( 1 );
				xCreateDataRed.SetRouteID( Iter->GetRouteID());
				xCreateDataRed.SetPostionX(Iter->GetPosX());
				xCreateDataRed.SetPostionY(Iter->GetPosY());
				xCreateDataRed.SetMonsterID(Iter->GetMonsterID());
				xCreateDataRed.SetDirection(Iter->GetAngle());
				xCreateDataRed.SetFightCamp( GameBattleDefine::GameBattle_Red );
				MonsterCreater::ProcessCreateNormalMonster( xCreateDataRed );
			}
		}	
        // ������Ӫˢ��
        const GameGuildGeneralBattleConfig::RefreshSetting::BarracksSetting& xBlueBarrackSetting = pSetting->GetBlueBarracksSetting();
		const GameGuildGeneralBattleConfig::RefreshSetting::MonsterDataList* pBlueMonsterDataList = xBlueBarrackSetting.GetMonster( iter->second.GetBlueIndex() );
		if(pBlueMonsterDataList != NULL)
		{
			//ˢ��һ����
			vector<GameGuildGeneralBattleConfig::RefreshSetting::MonsterData> vec;
			pBlueMonsterDataList->GetAllMonster(vec);
			vector<GameGuildGeneralBattleConfig::RefreshSetting::MonsterData>::iterator Iter = vec.begin();
			for(;Iter !=vec.end();++Iter)
			{
				//��������ˢ��
				MonsterCreateData xCreateDataBlue;
				xCreateDataBlue.SetMapID( pStage->GetStageID() );
				xCreateDataBlue.SetCount( 1 );
				xCreateDataBlue.SetRouteID( Iter->GetRouteID());
				xCreateDataBlue.SetPostionX(Iter->GetPosX());
				xCreateDataBlue.SetPostionY(Iter->GetPosY());
				xCreateDataBlue.SetMonsterID(Iter->GetMonsterID());
				xCreateDataBlue.SetDirection(Iter->GetAngle());
				xCreateDataBlue.SetFightCamp( GameBattleDefine::GameBattle_Blue );
				MonsterCreater::ProcessCreateNormalMonster( xCreateDataBlue );
			}
		}	
    }
}
void GameGuildGeneralBattle::ProcessRefreshNormalMonster()
{
	map<int,GameGuildGeneralBattleConfig::NormalMonster> mapList;
	const GameGuildGeneralBattleConfig* pBattleConfig = m_pManager->GetBattleConfig();
	pBattleConfig->GetNormalMonster(mapList);
	map<int,GameGuildGeneralBattleConfig::NormalMonster>::iterator Iter = mapList.begin();
	for(;Iter !=mapList.end();++Iter)
	{
		if(m_xNormalTimer.count(Iter->first) != 1)
			continue;
		if(!m_xNormalTimer[Iter->first].DoneTimer())
			continue;
		MonsterCreateData xCreateData;
		xCreateData.SetMapID( GetBattleMapID() );
		xCreateData.SetPostionX( Iter->second.GetPosX() );
		xCreateData.SetPostionY( Iter->second.GetPosY() );
		xCreateData.SetDirection(Iter->second.GetAngle());
		xCreateData.SetMonsterID( Iter->second.GetID() );
		xCreateData.SetCount( 1 );
		xCreateData.SetRadius( 2 );
		xCreateData.SetBodySize( Iter->second.GetBodySize() );
		MonsterCreater::CreateNormalMonster( xCreateData );
		// ֪ͨս�����������
		MsgTellCampGuildBattleRefreshMonster xTell;
		xTell.nMonsterID = Iter->second.GetID();
		xTell.nStringID  = Iter->second.GetString();
		GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
	}
}
void GameGuildGeneralBattle::ProcessGameBattleEndStatus()
{
    if ( !m_xReleaseTimer.DoneTimer() )
    { return; }

    SetStatus( GameBattleDefine::StatusRelease );

    m_mapBattlePlayer.clear();

    // �ҵ�����, �ͷŵ�
    GameStage* pStage = theGameWorld.GetStageById( GetBattleMapID() );
    if ( pStage != NULL && pStage->IsEctypeStage() )
    { pStage->SetStageWaitRelease( true ); }

}

void GameGuildGeneralBattle::AddBattlePlayer( unsigned int nPlayerID, GameBattleDefine::BattlePlayer& xPlayer )
{
    if ( xPlayer.GetFight() == GameBattleDefine::GameBattle_None )
    { return; }

	GameBattleDefine::BattlePlayer* pBattlePlayer = GetBattlePlayer( nPlayerID );
    if ( pBattlePlayer != NULL )
    { return; } // �Ѿ������б�����

    m_mapBattlePlayer[ nPlayerID ] = xPlayer;
}

GameBattleDefine::BattlePlayer* GameGuildGeneralBattle::GetBattlePlayer( unsigned int nPlayerID )
{
    BattlePlayerMapIter iter = m_mapBattlePlayer.find( nPlayerID ); 
    if ( iter == m_mapBattlePlayer.end() )
    { return NULL; }

    return &( iter->second );
}

int GameGuildGeneralBattle::GetBattlePlayerCount( unsigned char uchFight )
{
    int nCount = 0;
    for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
    {
        if ( iter->second.GetFight() == uchFight )
		{
			GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( iter->first );
			if ( pPlayer == NULL || pPlayer->GetMapID() != GetBattleMapID() )
			{ continue; }
			++nCount;
		}
    }
    return nCount;
}

unsigned int GameGuildGeneralBattle::GetGameBattleResource( unsigned char uchFight )
{
    switch (uchFight)
    {
    case GameBattleDefine::GameBattle_Red:
        return GetRedResource();
        break;
    case GameBattleDefine::GameBattle_Blue:
        return GetBlueResource();
        break;
    default:
        break;
    }

    return 0;
}

unsigned int GameGuildGeneralBattle::GetReliveIndex( GamePlayer* pPlayer )
{
    if ( GetStatus() == GameBattleDefine::StatusRelease )
    { return GameBattleDefine::DefaultReliveIndex; }

    // ����Ǻ췽��Ӫ
	GameBattleDefine::BattlePlayer* pBattlePlayer = GetBattlePlayer( pPlayer->GetDBCharacterID() );
	if(pBattlePlayer)
	{
		if(pBattlePlayer->GetFight() != pPlayer->GetFightCamp())
			pPlayer->SetFightGame(pBattlePlayer->GetFight());//��ҵ���Ӫ������ ���������²��������ͻ���ȥ
	}

    if (pBattlePlayer->GetFight() == GameBattleDefine::GameBattle_Red )
		return GameBattleDefine::RedReliveIndex;
	else  if (pBattlePlayer->GetFight() == GameBattleDefine::GameBattle_Blue )
		return GameBattleDefine::BlueReliveIndex;
	else
		return GameBattleDefine::DefaultReliveIndex;
}

void GameGuildGeneralBattle::SendGameBattleMessage( Msg* pMessage, unsigned char uchFight )
{
    for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
    {
        if ( iter->second.GetFight() != uchFight )
        { continue; }

        GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( iter->first );
        if ( pPlayer == NULL || pPlayer->GetMapID() != GetBattleMapID() )
        { continue; }

        pPlayer->SendMessageToClient( pMessage );
    }
}

void GameGuildGeneralBattle::ProcessKillPlayer( BaseCharacter* pKiller, GamePlayer* pBeKill )
{
    if ( pKiller == NULL || pBeKill == NULL )
    { return; }

    if ( GetStatus() != GameBattleDefine::StatusFight )
    { return; } // ����ս��״̬, �������߼�

    const GameGuildGeneralBattleConfig::ResourceSetting& xSetting = m_pManager->GetBattleConfig()->GetResourceSetting();

	GameBattleDefine::BattlePlayer* pBeKillBattlePlayer = GetBattlePlayer( pBeKill->GetDBCharacterID() );
    if (pBeKillBattlePlayer == NULL )
    { return; }

    // ɱ��������
    char szKillerName[ GameBattleDefine::NameLength ] = { 0 };
    HelperFunc::SafeNCpy( szKillerName, pKiller->GetCharName(), sizeof( szKillerName ) );

    // ����ɱ��
    int nKeepKillCount = 1;
    
    // ���ɱ�˵������
	GameBattleDefine::BattlePlayer* pKillerBattlePlayer = NULL;
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
			if(pKillerBattlePlayer->GetFight() == GameBattleDefine::GameBattle_Red)
				m_RedTotleKillSum++;
			else if(pKillerBattlePlayer->GetFight() == GameBattleDefine::GameBattle_Blue)
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
    ProcessAddGameBattleResource( pKiller->GetFightCamp(), xSetting.GetKillResource() );
}

void GameGuildGeneralBattle::PorcessFirstKillPlayer( const char* szKillerName, const char* szBeKillName )
{
    if ( !GetFirstKill() )
    { return; }
    SetFirstKill( false );

    const GameGuildGeneralBattleConfig::KillSetting& xSetting = m_pManager->GetBattleConfig()->GetFirstKillSetting();

    // ֪ͨ�����������
    MsgTellGameBattleKillPlayer xTell;
    xTell.uchCampBattleType = m_pManager->GetGameBattleType();
    xTell.uchKillType       = MsgTellGameBattleKillPlayer::TypeFirstKill;
    xTell.ustKillCount      = 1;
    xTell.ustStringID       = xSetting.GetString();
    HelperFunc::SafeNCpy( xTell.szKillerName, szKillerName, sizeof( xTell.szKillerName ) );
    HelperFunc::SafeNCpy( xTell.szBeKillName, szBeKillName, sizeof( xTell.szBeKillName ) );
    GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
}

void GameGuildGeneralBattle::ProcessKeepKillPlayer( const char* szKillerName, int nKillCount, const char* szBeKillName )
{
    const GameGuildGeneralBattleConfig::KillSetting* pSetting = m_pManager->GetBattleConfig()->GetKillerSetting( nKillCount );
    if ( pSetting == NULL )
    { return; }

    MsgTellGameBattleKillPlayer xTell;
    xTell.uchCampBattleType = m_pManager->GetGameBattleType();
    xTell.uchKillType       = MsgTellGameBattleKillPlayer::TypeKeepKill;
    xTell.ustKillCount      = nKillCount;
    xTell.ustStringID       = pSetting->GetString();
    HelperFunc::SafeNCpy( xTell.szKillerName, szKillerName, sizeof( xTell.szKillerName ) );
    HelperFunc::SafeNCpy( xTell.szBeKillName, szBeKillName, sizeof( xTell.szBeKillName ) );
    GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
}

void GameGuildGeneralBattle::ProcessBeKillByPlayer( const char* szKillerName, GameBattleDefine::BattlePlayer* pBeKillBattlePlayer )
{
    unsigned int nKeepKillCount = pBeKillBattlePlayer->GetKeepKillCount();
    pBeKillBattlePlayer->SetKeepKillCount( 0 );
    pBeKillBattlePlayer->AddTotalDeathCount( 1 );

    const GameGuildGeneralBattleConfig::KillSetting* pSetting = m_pManager->GetBattleConfig()->GetBeKillSetting( nKeepKillCount );
    if ( pSetting == NULL )
    { return; }

    MsgTellGameBattleKillPlayer xTell;
    xTell.uchCampBattleType = m_pManager->GetGameBattleType();
    xTell.uchKillType       = MsgTellGameBattleKillPlayer::TypeBeKill;
    xTell.ustKillCount      = nKeepKillCount;
    xTell.ustStringID       = pSetting->GetString();
    HelperFunc::SafeNCpy( xTell.szKillerName, szKillerName, sizeof( xTell.szKillerName ) );
    HelperFunc::SafeNCpy( xTell.szBeKillName, pBeKillBattlePlayer->GetName(), sizeof( xTell.szBeKillName ) );
    GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
}

void GameGuildGeneralBattle::ProcessTotalKillPlayer( GameBattleDefine::BattlePlayer* pKillerBattlePlayer, GameBattleDefine::BattlePlayer* pBeKillBattlePlayer )
{
    const GameGuildGeneralBattleConfig::KillSetting* pSetting = m_pManager->GetBattleConfig()->GetTotalKillSetting( pKillerBattlePlayer->GetTotalKillCount() );
    if ( pSetting == NULL )
    { return; }

    MsgTellGameBattleKillPlayer xTell;
    xTell.uchCampBattleType = m_pManager->GetGameBattleType();
    xTell.uchKillType       = MsgTellGameBattleKillPlayer::TypeTotalKill;
    xTell.ustKillCount      = pKillerBattlePlayer->GetTotalKillCount();
    xTell.ustStringID       = pSetting->GetString();
    HelperFunc::SafeNCpy( xTell.szKillerName, pKillerBattlePlayer->GetName(), sizeof( xTell.szKillerName ) );
    HelperFunc::SafeNCpy( xTell.szBeKillName, pBeKillBattlePlayer->GetName(), sizeof( xTell.szBeKillName ) );
	GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
    //GettheServer().SendMsgToCountry( &xTell, m_pManager->GetCountryID(), true );
}

void GameGuildGeneralBattle::ProcessAddGameBattleResource( unsigned char uchFight, unsigned int nAddResource )
{
    if ( nAddResource == 0 || GetStatus() != GameBattleDefine::StatusFight )
    { return; } // ����ս��״̬, �������߼�

	//zhuxincong 2013.1.14 ע��
    switch (uchFight )
    {
    case GameBattleDefine::GameBattle_Red:
        {   
            AddRedResource( nAddResource );
            if ( GetRedResource() < GetWinResource() )
            { return; }
        }
        break;
    case GameBattleDefine::GameBattle_Blue:
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
    ProcessStatusChange( GameBattleDefine::StatusEnd );
}

void GameGuildGeneralBattle::ProcessStatusChange( unsigned char uchStatus )
{
    if ( GetStatus() == GameBattleDefine::StatusEnd )
    { return; }

    SetStatus( uchStatus );

    switch ( GetStatus() )
    {
    case GameBattleDefine::StatusFight:
        ProcessChangeToFightStatus();
        break;
    case GameBattleDefine::StatusEnd:
        ProcessChangeToEndStatus();
        break;
    default:
        break;
    }

    // ֪ͨ�������������
    SendBattleStatusMessage();
}

void GameGuildGeneralBattle::SendBattleStatusMessage( GamePlayer* pPlayer /* = NULL*/ )
{
    MsgTellGameBattleStatus xTell;
    xTell.uchCampBattleType   = m_pManager->GetGameBattleType();
    xTell.uchCampBattleStatus = GetStatus();
	if(m_pManager->GetGameBattleOnceInfo(m_ID) != NULL)
		 xTell.nLeftTime= m_pManager->GetGameBattleOnceInfo(m_ID)->GetLeftTime() / 1000;
    if ( pPlayer == NULL )
    { GettheServer().SendMsgToStage( &xTell, GetBattleMapID() ); }
    else
    { pPlayer->SendMessageToClient( &xTell ); }
}

void GameGuildGeneralBattle::SendGameBattleMatchMessage( GamePlayer* pPlayer )
{
    MsgTellGameBattleMatch xTell;
    xTell.uchBattleType = m_pManager->GetGameBattleType();
    xTell.nRedID        = m_nRedID;
    xTell.nBlueID       = m_nBlueID;
    pPlayer->SendMessageToClient( &xTell );
}

void GameGuildGeneralBattle::ProcessChangeToFightStatus()
{
	#ifdef _DEBUG
    #else
	if ( m_mapBattlePlayer.empty() )
    {
        // ˫����û�˽���, ֱ������ս��
		ProcessStatusChange( GameBattleDefine::StatusEnd );
        //SetStatus( GameBattleDefine::StatusRelease );
        return;
    }
	#endif
    
    int nRedPlayerCount = 0;
    int nBluePlayerCount = 0;
    for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
    {
        switch( iter->second.GetFight())
        {
        case GameBattleDefine::GameBattle_Red:
            ++nRedPlayerCount;
            break;
        case GameBattleDefine::GameBattle_Blue:
            ++nBluePlayerCount;
            break;
        default:
            break;
        }
    }

	int BuffID = m_pManager->GetBattleConfig()->GetEnterBuff().GetBuffID();
	int Level = m_pManager->GetBattleConfig()->GetEnterBuff().GetLevel();
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
        ProcessAddGameBattleResource( GameBattleDefine::GameBattle_Blue, m_nWinResource );
    }
    else if ( nBluePlayerCount == 0 )
    {
        ProcessAddGameBattleResource( GameBattleDefine::GameBattle_Red, m_nWinResource );
    }

	if ( GetStatus() == GameBattleDefine::StatusEnd )
    { return; } // �����˾Ͳ�ˢ����

    // ����ˢ�ֶ�ʱ��
    m_xRefreshTimer.StartTimer( 1, GameGuildGeneralBattleConfig::RefreshSetting::GetTimeSpace() * 1000 );

    const GameGuildGeneralBattleConfig* pBattleConfig = m_pManager->GetBattleConfig();

	map<int,GameGuildGeneralBattleConfig::NormalMonster> mapList;
	pBattleConfig->GetNormalMonster(mapList);
	map<int,GameGuildGeneralBattleConfig::NormalMonster>::iterator Iter = mapList.begin();
	for(;Iter !=mapList.end();++Iter)
	{
		if(m_xNormalTimer.count(Iter->first) != 1)
			continue;
		m_xNormalTimer[Iter->first].StartTimer( HQ_TimeGetTime(), Iter->second.GetTimeSpace() * OneMinuteMicroSecond );
	}
}

void GameGuildGeneralBattle::ProcessChangeToEndStatus()
{
	SendGameBattleResourceMessage();
    // ����ս�����ٶ�ʱ��
    m_xReleaseTimer.StartTimer( HQ_TimeGetTime(), GameBattleDefine::ReleaseSapceTime );

    // ����ս�����
    ProcessCalcGameBattleWinner();
}

void GameGuildGeneralBattle::ProcessCalcGameBattleWinner()
{
    unsigned char uchFight =GameBattleDefine::GameBattle_None;
    if ( GetRedResource() >= GetBlueResource() )
    { uchFight = GameBattleDefine::GameBattle_Red; }
    else
    { uchFight = GameBattleDefine::GameBattle_Blue; }

    ProcessGameBattleResult( uchFight );
}
void GameGuildGeneralBattle::SendBattlePlayerMessage( GamePlayer* pPlayer, unsigned char uchFight )
{
    MsgTellGameBattlePlayer xTell;
    xTell.uchCampBattleType = m_pManager->GetGameBattleType();

    for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
    { 
        switch( uchFight )
        {
        case GameBattleDefine::GameBattle_Red:   
		case GameBattleDefine::GameBattle_Blue:
            {
                // ָ����Ӫ��Ҫ�ж���Ӫ��Ϣ
                if ( iter->second.GetFight() != uchFight )
                { continue; }
            }
        default:
            xTell.AddBattlePlayer( iter->second ); 
            break;
        }
    }
    
    pPlayer->SendMessageToClient( &xTell );
}

void GameGuildGeneralBattle::KillGameBattleMonster( unsigned char uchFight, unsigned int nPlayerID, int nMonsterID )
{
    const GameGuildGeneralBattleConfig* pBattleConfig = m_pManager->GetBattleConfig();
    const GameGuildGeneralBattleConfig::MonsterSetting* pSetting = pBattleConfig->GetMonsterSetting( nMonsterID );
    if ( pSetting == NULL )
    { return; }

    // ��Ӹ��˻���
	GameBattleDefine::BattlePlayer* pBattlePlayer = GetBattlePlayer( nPlayerID );
    if ( pBattlePlayer != NULL )
    { 
        // ��Ӹ��˻���
        pBattlePlayer->AddResource( pSetting->GetResource() ); 
    }

    if ( pSetting->GetString() != 0 )
    {
        MsgKillGameBattleMonster xKill;
        xKill.uchBattleType = m_pManager->GetGameBattleType();
        xKill.uchFightCamp  = uchFight;
        xKill.nMonsterID    = nMonsterID;
        xKill.nStringID     = pSetting->GetString();
        GettheServer().SendMsgToStage( &xKill, GetBattleMapID() );
    }

    // ���ս������
    ProcessAddGameBattleResource( uchFight, pSetting->GetResource() );

	// �����������, ������10���Ӻ���ˢһ������
	map<int,GameGuildGeneralBattleConfig::NormalMonster> mapList;
	pBattleConfig->GetNormalMonster(mapList);
	if(mapList.count(nMonsterID) == 1 && m_xNormalTimer.count(nMonsterID) == 1)
	{
		m_xNormalTimer[nMonsterID].StartTimer( HQ_TimeGetTime(), mapList[nMonsterID].GetTimeSpace() * OneMinuteMicroSecond );
	}
	for ( int i = 0; i < pBattleConfig->GetGetRefreshSettingCount(); ++i )
    {
        const GameGuildGeneralBattleConfig::RefreshSetting* pSetting = pBattleConfig->GetRefreshSettingByIndex( i );
        if ( pSetting == NULL )
        { continue; }

        const GameGuildGeneralBattleConfig::RefreshSetting::BarracksSetting& xRedSetting = pSetting->GetRedBarracksSetting();
		const GameGuildGeneralBattleConfig::RefreshSetting::BarracksSetting& xBlueSetting = pSetting->GetBlueBarracksSetting();
		RefreshIndexMapIter iter = m_mapRefreshIndex.find( pSetting->GetBarracksID() );
		if ( iter == m_mapRefreshIndex.end() )
			continue;
		if(xRedSetting.GetMonsterID() == nMonsterID)
		{
			if(iter->second.GetBlueIndex() != -1)
				iter->second.SetBlueIndex( iter->second.GetMaxBlueIndex() );
			iter->second.SetRedIndex( -1 );
			m_RedBarracksDeadSum++;	
			ProcessBoss();
		}
		else if(xBlueSetting.GetMonsterID() == nMonsterID)
		{
			if(iter->second.GetRedIndex() != -1)
				iter->second.SetRedIndex( iter->second.GetMaxRedIndex() );
			iter->second.SetBlueIndex( -1 );
			m_BlueBarracksDeadSum++;
			ProcessBoss();
		}
		else
			continue;
	}
	//�ж��Ƿ�Ϊ����BOSS �ǵĻ�����ս�� �ֳ�ʤ��
	if(pBattleConfig->GetRedBoss().GetID() == nMonsterID)
	{
		m_RedBoss = NULL;
		ProcessStatusChange( CampDefine::StatusEnd );
	}
	else if(pBattleConfig->GetBlueBoss().GetID() == nMonsterID)
	{
		m_BlueBoss = NULL;
		ProcessStatusChange( CampDefine::StatusEnd );
	}
}

unsigned char GameGuildGeneralBattle::GetGameBattleFight( unsigned int nUnitID )
{
    // �췽��Ӫ
    if ( GetBlueID() == nUnitID )
		return GameBattleDefine::GameBattle_Blue;
	else if(GetRedID() == nUnitID)
		return GameBattleDefine::GameBattle_Red;
	else
		return GameBattleDefine::GameBattle_None;
}
void GameGuildGeneralBattle::ProcessGameBattleResult( unsigned char uchFight )
{
	//��ս���Ѿ������˺� ������Ҫ������ 
	//1.֪ͨ˫�� ս���Ѿ�����
	unsigned int nWinGuildID  = GuildDefine::InitID;
	unsigned int nLoseGuildID = GuildDefine::InitID;
	switch ( uchFight )
	{
	case GameBattleDefine::GameBattle_Red:
		nWinGuildID  = m_nRedID;
		nLoseGuildID = m_nBlueID;
		break;
	case GameBattleDefine::GameBattle_Blue:
		nWinGuildID  = m_nBlueID;
		nLoseGuildID = m_nRedID;
		break;
	default:
		return;
		break;
	}

	// ����ս������
	GameGuild* pWinGuild = theGameGuildManager.GetGuild( nWinGuildID );
	GameGuild* pLoseGuild = theGameGuildManager.GetGuild( nLoseGuildID );
	if ( pWinGuild == NULL || pLoseGuild == NULL )
	{ return; }

	MsgGameGuildBattleResult xResult;
	xResult.nWinGuildID  = nWinGuildID;
	xResult.nLoseGuildID = nLoseGuildID;
	GettheServer().SendMsgToWorld( &xResult,true);
	//pWinGuild->SendMessageToGuild(&xResult);
	//pLoseGuild->SendMessageToGuild(&xResult);
	//��ʤ���Ĺ������ ����ʹ���� �͹����ʽ�
	pWinGuild->OperateGuildMission(GuildDefine::OperateAdd,GuildMession*2);
	pWinGuild->OperateGuildMoney(GuildDefine::OperateAdd,GuildMoneySum*2);
	//2.��ʤ�������ͽ���
	int Money = MoneySum * 2;
	//3.�����ʼ�
	GS2CSSendMailReq xReq;
	xReq.charDbId = RelationDefine::InitID;
	xReq.mail.type  = SMail::EMT_System;
	xReq.mail.state = SMail::EMS_NotOpen;
	xReq.mail.sendTime = TimeEx::GetNowTime();        
	// ������
	xReq.mail.owners[EM_FromIndex].charDbId = 0;
	sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
	// �ռ���	
	xReq.mail.owners[EM_ToIndex].charDbId = pWinGuild->GetMasterID();
	if(!pWinGuild->GetMember(pWinGuild->GetMasterID()))
		return;
	HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName,pWinGuild->GetMember(pWinGuild->GetMasterID())->GetName(), sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
	sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_GuildGeneral_Secc_Content ) );
	sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_GuildGeneral_Secc_Title ) );
	xReq.mail.money = Money;
	GettheServer().SendMsgToCenterServer( &xReq );
}
void GameGuildGeneralBattle::ProcessBoss()
{
	const GameGuildGeneralBattleConfig* pBattleConfig = m_pManager->GetBattleConfig();
    int Sum = pBattleConfig->GetGetRefreshSettingCount();
	 MonsterCreateData xCreateData;
	if(m_RedBarracksDeadSum == Sum)
	{
		//ˢ��BOSS
		const GameGuildGeneralBattleConfig::BossMonster& pMonster = pBattleConfig->GetRedBoss();
        xCreateData.SetMonsterID( pMonster.GetID() );
        xCreateData.SetPostionX( pMonster.GetPosX() );
        xCreateData.SetPostionY( pMonster.GetPosY() );

		xCreateData.SetDirection(pMonster.GetAngle());

        xCreateData.SetFightCamp( GameBattleDefine::GameBattle_Red );
		xCreateData.SetRouteID( pMonster.GetRouteID() );
		xCreateData.SetMapID(m_nEctypeMapID);
        m_RedBoss = MonsterCreater::CreateNormalMonster( xCreateData );

		m_RedBarracksDeadSum = -1;
	}
	else if(Sum == m_BlueBarracksDeadSum)
	{
		//ˢ��BOSS
		const GameGuildGeneralBattleConfig::BossMonster& pMonster = pBattleConfig->GetBlueBoss();
        xCreateData.SetMonsterID( pMonster.GetID() );
        xCreateData.SetPostionX( pMonster.GetPosX() );
        xCreateData.SetPostionY( pMonster.GetPosY() );

		xCreateData.SetDirection(pMonster.GetAngle());

		xCreateData.SetFightCamp( GameBattleDefine::GameBattle_Blue );
		xCreateData.SetRouteID( pMonster.GetRouteID() );
		xCreateData.SetMapID(m_nEctypeMapID);
        m_BlueBoss = MonsterCreater::CreateNormalMonster( xCreateData );

		m_BlueBarracksDeadSum = -1;
	}
}