#include "CampCountryBattle.h"
#include "CampBattleMessage.h"
#include "CampBattleManager.h"
#include "CampCountryBattleConfig.h"
#include "GamePlayer.h"
#include "ShareData.h"

CampCountryBattle::CampCountryBattle() : CampBattle()
{

}

void CampCountryBattle::Release()
{
    ReleaseBattle< CampCountryBattle >( this );
}



void CampCountryBattle::SendEnterCampBattleMessage()
{
    // ��õ�ͼID
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_pBattleManager->GetMapID() );
    if ( pMapData == NULL )
    { return; }

    // ��ý����NPC�ص�
    MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
    if ( pRelive == NULL )
    { return; }



   /* MsgFlyToCampBattleReq xReq;
    xReq.uchBattleType = m_pBattleManager->GetBattleType();
    xReq.nMapID        = m_pBattleManager->GetMapID();*/

	MsgFlyToCampBattleReq xReq;
	xReq.uchBattleType = m_pBattleManager->GetBattleType();
	xReq.nMapID = m_pBattleManager->GetMapID();
	xReq.nKingdomID = m_pBattleManager->GetKingdomMapID();
	xReq.nKingdomX = m_pBattleManager->GetKingdomMapX();
	xReq.nKingdomY = m_pBattleManager->GetKingdomMapY();
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

void CampCountryBattle::ProcessCampBattleFightStatus()
{
	//zhuxincong ս����ʼ��ʱ�� ͳ���»���
    SendCampBattlePlayerCountMessage();
	//�ж�˫�������� �����һ��Ϊ0 ��ʾ�Ѿ����Խ���ս����
}

void CampCountryBattle::SendCampBattlePlayerCountMessage()
{
	//zhuxincong �����û������Ƕ��ٴ���
    // ����ս�����������ɵĳ�Ա����
    //const CampCountryBattleConfig* pBattleConfig = static_cast< const CampCountryBattleConfig* >( m_pBattleManager->GetBattleConfig() );
	 CampCountryBattleConfig* pBattleConfig =  (CampCountryBattleConfig* )( m_pBattleManager->GetBattleConfig() );

	MsgTellCountryBattlePlayerCount xTell;
	xTell.nRedCount =GetRedResource(); //pBattleConfig->GetRedScore();
	xTell.nBlueCount =GetBlueResource(); //pBattleConfig->GetBlueScore();
	xTell.nRedMasterDeathCount  = pBattleConfig->GetMaxDeathCount() + 1;
	xTell.nBlueMasterDeathCount = pBattleConfig->GetMaxDeathCount() + 1;

	GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
    //MsgTellCountryBattlePlayerCount xTell;
    //xTell.nRedMasterDeathCount  = pBattleConfig->GetMaxDeathCount() + 1;
    //xTell.nBlueMasterDeathCount = pBattleConfig->GetMaxDeathCount() + 1;

    //for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
    //{
    //    if ( iter->second.GetTotalDeathCount() > pBattleConfig->GetMaxDeathCount() )
    //    { continue; }

    //    switch ( CampDefine::GetBaseFightCamp( iter->second.GetFightCamp() ) )
    //    {
    //    case CampDefine::BaseCampRed:
    //        {
    //            ++xTell.nRedCount;  // ����+1

    //            // ����ǰ���
    //            GameGuild* pGuild = theGameGuildManager.GetGuild( m_nRedID );
    //            if ( pGuild != NULL && pGuild->IsMaster( iter->first ) )
    //            { xTell.nRedMasterDeathCount = iter->second.GetTotalDeathCount(); }
    //        }
    //        break;
    //    case CampDefine::BaseCampBlue:
    //        {
    //            ++xTell.nBlueCount;  // ����+1

    //            // ����ǰ���
    //            GameGuild* pGuild = theGameGuildManager.GetGuild( m_nBlueID );
    //            if ( pGuild != NULL && pGuild->IsMaster( iter->first ) )
    //            { xTell.nBlueMasterDeathCount = iter->second.GetTotalDeathCount(); }
    //        }
    //        break;
    //    default:
    //        break;
    //    }
    //}

    //GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
}


void CampCountryBattle::SendCampBattlePlayerCountMessagezxc()
{
	CampCountryBattleConfig* pBattleConfig =  (CampCountryBattleConfig* )( m_pBattleManager->GetBattleConfig() );

	MsgTellCountryBattlePlayerCount xTell;
	/*xTell.nRedCount = pBattleConfig->GetRedScore();
	xTell.nBlueCount = pBattleConfig->GetBlueScore();*/
	xTell.nRedCount =GetRedResource(); //pBattleConfig->GetRedScore();
	xTell.nBlueCount =GetBlueResource(); //pBattleConfig->GetBlueScore();
	xTell.nRedMasterDeathCount  = pBattleConfig->GetMaxDeathCount() + 1;
	xTell.nBlueMasterDeathCount = pBattleConfig->GetMaxDeathCount() + 1;

	GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
}

void CampCountryBattle::ProcessCampBattleResult( unsigned char uchFightCamp )
{
    // ����ս������
    unsigned int nWinGuildID  = GuildDefine::InitID;
	unsigned int nLoseGuildID = GuildDefine::InitID;
    unsigned char uchWinType  = CountryDefine::BattleWin_Guard;
	//zhuxincong SendCountryBattleResultMessage()������һ���������Ǻ췽��������
	unsigned int nCampBattle = GuildDefine::InitID;
    switch ( uchFightCamp )
    {
    case CampDefine::BaseCampRed:
        nWinGuildID = m_nRedID;
		nLoseGuildID = m_nBlueID;
        uchWinType  = CountryDefine::BattleWin_Guard;
		nCampBattle = CampDefine::BaseCampRed;
        break;
    case CampDefine::BaseCampBlue:
        nWinGuildID  = m_nBlueID;
		nLoseGuildID = m_nRedID;
        uchWinType  = CountryDefine::BattleWin_Challenge;
		nCampBattle = CampDefine::BaseCampBlue;
        break;
    default:
        return;
        break;
    }
    
    m_pBattleManager->SendCountryBattleResultMessage( nWinGuildID, uchWinType ,nLoseGuildID,nCampBattle);
}

unsigned int CampCountryBattle::GetReliveIndex( GamePlayer* pPlayer )
{
    const CampCountryBattleConfig* pBattleConfig = static_cast< const CampCountryBattleConfig* >( m_pBattleManager->GetBattleConfig() );

    // ����5��, ֱ�������渴��
    BattlePlayer* pBattlePlayer = GetBattlePlayer( pPlayer->GetDBCharacterID() );
    if ( pBattlePlayer == NULL /*zhuxincong ע��|| pBattlePlayer->GetTotalDeathCount() > pBattleConfig->GetMaxDeathCount()*/ )
    { return CampDefine::DefaultReliveIndex; } //zhuxincong �߻�Ҫ��5������֮���ó�FB

    return CampBattle::GetReliveIndex( pPlayer );
}

void CampCountryBattle::ProcessKillPlayer( BaseCharacter* pKiller, GamePlayer* pBeKill )
{
    CampBattle::ProcessKillPlayer( pKiller, pBeKill );
    
    // ���������������������5��, ������ʾ
    //TellBattleDeathCount( pBeKill );
	
    // ����Ƿ�ɱ����
    CheckKillAllCampBattlePlayer( pBeKill );
	//zhuxincong ������ˢ��
	//SendCampBattlePlayerCountMessagezxc();



}

void CampCountryBattle::ProcessChangeToEndStatus()
{
    // ͬ��һ��ս���������
	//zhuxincong ս������ʱͳ���»���
    SendCampBattlePlayerCountMessage();

    // ��û�зֳ�ʤ��, ����˫�����, �ó�ʤ������
    if ( ( m_nBlueResource < m_nWinResource ) && ( m_nRedResource < m_nWinResource ) )
    { ProcessCalcBattleWinGuild(); }
    
    CampBattle::ProcessChangeToEndStatus();
}

void CampCountryBattle::TellBattleDeathCount( GamePlayer* pPlayer )
{
    BattlePlayer* pBattlePlayer = GetBattlePlayer( pPlayer->GetDBCharacterID() );
    if ( pBattlePlayer == NULL )
    { return; }

    const CampCountryBattleConfig* pBattleConfig = static_cast< const CampCountryBattleConfig* >( m_pBattleManager->GetBattleConfig() );
    MsgTellCampBattleDeathCount xTell;
    xTell.nDeathCount = pBattlePlayer->GetTotalDeathCount();
    xTell.nMaxCount   = pBattleConfig->GetMaxDeathCount();
    pPlayer->SendMessageToClient( &xTell );
}

void CampCountryBattle::ProcessCalcBattleWinGuild()
{
	//zhuxincong �ж�ʤ��
    // ����˫������ ʤ������
    // ��δ�峡��, �а���һ��ʤ��
    GameGuild* pRedGuild  = theGameGuildManager.GetGuild( m_nRedID );
    GameGuild* pBlueGuild = theGameGuildManager.GetGuild( m_nBlueID );
    if ( pBlueGuild == NULL && pRedGuild == NULL )
    { return; }

    if ( pBlueGuild == NULL )
    { 
        m_nRedResource += m_nWinResource;
        return;
    }

    if ( pRedGuild == NULL )
    {
        m_nBlueResource += m_nWinResource;
        return;
    }

	/*if(m_nBlueResource == m_nRedResource)
	{
		const CampCountryBattleConfig* pBattleConfig = static_cast< const CampCountryBattleConfig* >( m_pBattleManager->GetBattleConfig() );

		��Աδ���⣬�а�������ʤ
		BattlePlayer* pRedBattlePlayer = GetBattlePlayer( pRedGuild->GetMasterID() );
		BattlePlayer* pBlueBattlePlayer = GetBattlePlayer( pBlueGuild->GetMasterID() );

		 ����������, û�н����, ����ս����ͼ, �����Ѿ����������ܴ�����
		if ( pBlueBattlePlayer == NULL || pBlueBattlePlayer->GetTotalDeathCount() > pBattleConfig->GetMaxDeathCount() )
		{
			 ������������, ��������С���ܴ���, �ڱ���ͼ
			if ( pRedBattlePlayer != NULL && pRedBattlePlayer->GetTotalDeathCount() <= pBattleConfig->GetMaxDeathCount() )
			{
				m_nRedResource += m_nWinResource;
				return;
			}
		}

		 �췽������, û�н����, ����ս����ͼ, �����Ѿ����������ܴ�����
		if ( pRedBattlePlayer == NULL || pRedBattlePlayer->GetTotalDeathCount() > pBattleConfig->GetMaxDeathCount() )
		{
			 ������������, ��������С���ܴ���, �ڱ���ͼ
			if ( pBlueBattlePlayer != NULL && pBlueBattlePlayer->GetTotalDeathCount() <= pBattleConfig->GetMaxDeathCount() )
			{
				m_nBlueResource += m_nWinResource;
				return;
			}
		}

		 �ж�˫������, �������һ��ʤ��
		int nRedBattlePlayerCount = 0;
		int nBlueBattlePlayerCount = 0;
		for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
		{
			GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( iter->first );
			if ( pPlayer == NULL || pPlayer->GetMapID() != GetBattleMapID() )
			{ continue; }

			if ( iter->second.GetTotalDeathCount() > pBattleConfig->GetMaxDeathCount() )
			{ continue; }

			if ( CampDefine::GetBaseFightCamp( iter->second.GetFightCamp() ) == CampDefine::BaseCampRed )
			{ ++nRedBattlePlayerCount; }
			else
			{ ++nBlueBattlePlayerCount; }
		}

		 �췽������
		if ( nRedBattlePlayerCount > nBlueBattlePlayerCount )
		{
			m_nRedResource += m_nWinResource;
			return;
		}

		 ����������
		if ( nBlueBattlePlayerCount > nRedBattlePlayerCount )
		{
			m_nBlueResource += m_nWinResource;
			return;
		}

		 ����һ����, 
		 ��������û�μ�, �췽ʤ��
		if ( pBlueBattlePlayer == NULL )
		{
			m_nRedResource += m_nWinResource;
			return;
		}

		 �췽����û�μ�, ����ʤ��
		if ( pRedBattlePlayer == NULL )
		{
			m_nBlueResource += m_nWinResource;
			return;
		}

		 �������, �������������ٵ�ʤ��( �췽�е����� )
		if ( pRedBattlePlayer->GetTotalDeathCount() <= pBlueBattlePlayer->GetTotalDeathCount() )
		{ m_nRedResource += m_nWinResource; }
		else
		{ m_nBlueResource += m_nWinResource; }
	}*/
}

// ������, �͵�����������������������
void CampCountryBattle::ProcessBattlePlayerOutLine( GamePlayer* pPlayer )
{
    if ( m_pBattleManager->GetBattleStatus() != CampDefine::StatusFight )
    { return; }

    BattlePlayer* pBattlePlayer = GetBattlePlayer( pPlayer->GetDBCharacterID() );
    if ( pBattlePlayer == NULL )
    { return; }

    const CampCountryBattleConfig* pBattleConfig = static_cast< const CampCountryBattleConfig* >( m_pBattleManager->GetBattleConfig() );
    pBattlePlayer->SetTotalDeathCount( pBattleConfig->GetMaxDeathCount() + 1 );

    CheckKillAllCampBattlePlayer( pPlayer );
}

void CampCountryBattle::CheckKillAllCampBattlePlayer( GamePlayer* pPlayer )
{
    // ����ɱ����Ϣ, �Ƿ���������еж���Ӫ�����
    //const CampCountryBattleConfig* pBattleConfig = static_cast< const CampCountryBattleConfig* >( m_pBattleManager->GetBattleConfig() );
	return;
	 CampCountryBattleConfig* pBattleConfig = ( CampCountryBattleConfig*) ( m_pBattleManager->GetBattleConfig() );
	int Red = GetRedResource();//pBattleConfig->GetRedScore();
	int Blue = GetBlueResource();//pBattleConfig->GetBlueScore();
    //unsigned char uchKillerFightCamp = CampDefine::NoneCamp;
    //for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
    //{
    //    if ( iter->second.GetFightCamp() != pPlayer->GetFightCamp() )
    //    { 
    //        // ��ֹ������ɱ��, ��Ϊ����Ŀǰû����Ӫ
    //        uchKillerFightCamp = iter->second.GetFightCamp();   
    //        continue;
    //    }
		///*BattlePlayerMapIter iter = m_mapBattlePlayer.begin();*/
		//if(iter == m_mapBattlePlayer.end())
		//{
		//	return;
		//}
		switch (pPlayer->GetFightCamp())
		{
		case CampDefine::KingCampRed:
			//Red = pBattleConfig->GetRedScore();
			--Red;
			SetRedResource(Red);
			//pBattleConfig->SetFRedScore(Red);
			break;
		case CampDefine::KingCampBlue:
			//Blue = pBattleConfig->GetBlueScore();
			--Blue;
			SetBlueResource(Blue);
			//pBattleConfig->SetFBlueScore(Blue);
			break;
		}
       /* if ( iter->second.GetTotalDeathCount() <= pBattleConfig->GetMaxDeathCount() )
        {
            ++nBattlePlayerCount;
            break;      
        }*/
    /*}*/

	
	
	/*if (Red == 0)
	{
		ProcessAddCampResource( CampDefine::KingCampBlue, Blue) ;
		pBattleConfig->SetRedScore();
		pBattleConfig->SetBlueScore();
	}
	else if (Blue == 0)
	{
		ProcessAddCampResource( CampDefine::KingCampRed, Red );
		pBattleConfig->SetRedScore();
		pBattleConfig->SetBlueScore();
	}*/

    //if ( nBattlePlayerCount == 0 )  // zhuxincong ������˶Է�, ֱ��ʤ��
    //{ ProcessAddCampResource( uchKillerFightCamp, GetWinResource() ); }
}
