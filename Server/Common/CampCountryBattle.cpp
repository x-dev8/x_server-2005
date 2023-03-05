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
    // 获得地图ID
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_pBattleManager->GetMapID() );
    if ( pMapData == NULL )
    { return; }

    // 获得进入的NPC地点
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

    // 红方帮派
    GameGuild* pRedGuild = theGameGuildManager.GetGuild( m_nRedID );
    if ( pRedGuild != NULL )
    {
        pRedGuild->SendMessageToGuild( &xReq, GuildDefine::InitID, pMapData->MinPlayerLevel, true );
    }

    // 蓝方帮派
    GameGuild* pBlueGuild = theGameGuildManager.GetGuild( m_nBlueID );
    if ( pBlueGuild != NULL )
    {
        pBlueGuild->SendMessageToGuild( &xReq, GuildDefine::InitID, pMapData->MinPlayerLevel, true );
    }
}

void CampCountryBattle::ProcessCampBattleFightStatus()
{
	//zhuxincong 战斗开始的时候 统计下积分
    SendCampBattlePlayerCountMessage();
	//判断双方的人数 如果有一方为0 表示已经可以结束战场了
}

void CampCountryBattle::SendCampBattlePlayerCountMessage()
{
	//zhuxincong 这里获得基数，是多少次数
    // 发送战场中两个帮派的成员数量
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
    //            ++xTell.nRedCount;  // 人数+1

    //            // 如果是帮主
    //            GameGuild* pGuild = theGameGuildManager.GetGuild( m_nRedID );
    //            if ( pGuild != NULL && pGuild->IsMaster( iter->first ) )
    //            { xTell.nRedMasterDeathCount = iter->second.GetTotalDeathCount(); }
    //        }
    //        break;
    //    case CampDefine::BaseCampBlue:
    //        {
    //            ++xTell.nBlueCount;  // 人数+1

    //            // 如果是帮主
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
    // 处理战场奖励
    unsigned int nWinGuildID  = GuildDefine::InitID;
	unsigned int nLoseGuildID = GuildDefine::InitID;
    unsigned char uchWinType  = CountryDefine::BattleWin_Guard;
	//zhuxincong SendCountryBattleResultMessage()多增加一个参数，是红方还是蓝方
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

    // 超过5次, 直接在外面复活
    BattlePlayer* pBattlePlayer = GetBattlePlayer( pPlayer->GetDBCharacterID() );
    if ( pBattlePlayer == NULL /*zhuxincong 注释|| pBattlePlayer->GetTotalDeathCount() > pBattleConfig->GetMaxDeathCount()*/ )
    { return CampDefine::DefaultReliveIndex; } //zhuxincong 策划要求，5次死亡之后不用出FB

    return CampBattle::GetReliveIndex( pPlayer );
}

void CampCountryBattle::ProcessKillPlayer( BaseCharacter* pKiller, GamePlayer* pBeKill )
{
    CampBattle::ProcessKillPlayer( pKiller, pBeKill );
    
    // 如果死人者死亡次数超过5次, 给出提示
    //TellBattleDeathCount( pBeKill );
	
    // 检测是否杀光了
    CheckKillAllCampBattlePlayer( pBeKill );
	//zhuxincong 公告板的刷新
	//SendCampBattlePlayerCountMessagezxc();



}

void CampCountryBattle::ProcessChangeToEndStatus()
{
    // 同步一次战场人数情况
	//zhuxincong 战场结束时统计下积分
    SendCampBattlePlayerCountMessage();

    // 还没有分出胜负, 计算双方玩家, 得出胜利帮派
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
	//zhuxincong 判断胜利
    // 计算双方人数 胜利条件
    // 还未清场完, 有帮主一方胜利
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

		人员未死光，有帮主方获胜
		BattlePlayer* pRedBattlePlayer = GetBattlePlayer( pRedGuild->GetMasterID() );
		BattlePlayer* pBlueBattlePlayer = GetBattlePlayer( pBlueGuild->GetMasterID() );

		 蓝方不在线, 没有进入过, 不在战场地图, 或者已经死亡超过总次数了
		if ( pBlueBattlePlayer == NULL || pBlueBattlePlayer->GetTotalDeathCount() > pBattleConfig->GetMaxDeathCount() )
		{
			 蓝方帮主在线, 死亡次数小于总次数, 在本地图
			if ( pRedBattlePlayer != NULL && pRedBattlePlayer->GetTotalDeathCount() <= pBattleConfig->GetMaxDeathCount() )
			{
				m_nRedResource += m_nWinResource;
				return;
			}
		}

		 红方不在线, 没有进入过, 不在战场地图, 或者已经死亡超过总次数了
		if ( pRedBattlePlayer == NULL || pRedBattlePlayer->GetTotalDeathCount() > pBattleConfig->GetMaxDeathCount() )
		{
			 蓝方帮主在线, 死亡次数小于总次数, 在本地图
			if ( pBlueBattlePlayer != NULL && pBlueBattlePlayer->GetTotalDeathCount() <= pBattleConfig->GetMaxDeathCount() )
			{
				m_nBlueResource += m_nWinResource;
				return;
			}
		}

		 判断双方人数, 人数多的一方胜利
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

		 红方人数多
		if ( nRedBattlePlayerCount > nBlueBattlePlayerCount )
		{
			m_nRedResource += m_nWinResource;
			return;
		}

		 蓝方人数多
		if ( nBlueBattlePlayerCount > nRedBattlePlayerCount )
		{
			m_nBlueResource += m_nWinResource;
			return;
		}

		 人数一样多, 
		 蓝方帮主没参加, 红方胜利
		if ( pBlueBattlePlayer == NULL )
		{
			m_nRedResource += m_nWinResource;
			return;
		}

		 红方帮主没参加, 蓝方胜利
		if ( pRedBattlePlayer == NULL )
		{
			m_nBlueResource += m_nWinResource;
			return;
		}

		 人数相等, 帮主死亡次数少的胜利( 红方有点优势 )
		if ( pRedBattlePlayer->GetTotalDeathCount() <= pBlueBattlePlayer->GetTotalDeathCount() )
		{ m_nRedResource += m_nWinResource; }
		else
		{ m_nBlueResource += m_nWinResource; }
	}*/
}

// 离线了, 就当该玩家死亡次数超过最大了
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
    // 处理杀人信息, 是否清除了所有敌对阵营的玩家
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
    //        // 防止被宠物杀死, 因为宠物目前没有阵营
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

    //if ( nBattlePlayerCount == 0 )  // zhuxincong 如果清了对方, 直接胜利
    //{ ProcessAddCampResource( uchKillerFightCamp, GetWinResource() ); }
}
