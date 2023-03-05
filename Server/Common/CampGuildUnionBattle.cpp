#include "CampGuildUnionBattle.h"
#include "GuildManager.h"
#include "CampBattleMessage.h"
#include "MapConfig.h"
#include "CampGuildUnionBattleConfig.h"
#include "GamePlayer.h"
#include "CampBattleManager.h"
#include "GameWorld.h"
#include "MonsterCreater.h"
#include "CampGuildUnionBattleConfig.h"
#include "LogEventService.h"
CampGuildUnionBattle::CampGuildUnionBattle() : CampBattle()
{
    m_xRefreshTimer.StartTimer( 1, 3000 );
	m_xNormalTimer.clear();
	const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
	if(pBattleConfig)
	{
		map<int,CampGuildBattleConfig::NormalMonster> mapList;
		pBattleConfig->GetNormalMonster(mapList);
		map<int,CampGuildBattleConfig::NormalMonster>::iterator Iter = mapList.begin();
		for(;Iter !=mapList.end();++Iter)
		{
			GameTimerEx ex;
			m_xNormalTimer.insert(std::map<int,GameTimerEx>::value_type(Iter->first,ex));
		}
	}
}

void CampGuildUnionBattle::Release()
{
    ReleaseBattle< CampGuildUnionBattle >( this );
}

void CampGuildUnionBattle::SendEnterCampBattleMessage()
{
    // 获得地图ID
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_pBattleManager->GetMapID() );
    if ( pMapData == NULL )
    { return; }

    // 获得进入的NPC地点
    MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
    if ( pRelive == NULL )
    { return; }

    MsgFlyToCampBattleReq xReq;
    xReq.uchBattleType = m_pBattleManager->GetBattleType();
    xReq.nMapID        = m_pBattleManager->GetMapID();
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

void CampGuildUnionBattle::ProcessCampBattleEnterStatus()
{
    if ( !m_xRefreshTimer.DoneTimer( HQ_TimeGetTime() ) )
    { return; }

    GameStage* pStage = theGameWorld.GetStageById( GetBattleMapID() );
    if ( pStage == NULL )
    { return; }

    // 先停止定时器
    m_xRefreshTimer.StopTimer();

    m_mapRefreshIndex.clear();

    MonsterCreateData xCreateData;
    xCreateData.SetMapID( pStage->GetStageID() );

    // 刷出双方兵营
    const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
    for ( int i = 0; i < pBattleConfig->GetGetRefreshSettingCount(); ++i )
    {
        const CampGuildBattleConfig::RefreshSetting* pSetting = pBattleConfig->GetRefreshSettingByIndex( i );
        if ( pSetting == NULL )
        { continue; }

        const CampGuildBattleConfig::RefreshSetting::BarracksSetting& xRedSetting = pSetting->GetRedBarracksSetting();

        xCreateData.SetMonsterID( pSetting->GetBarracksID() );
        xCreateData.SetPostionX( xRedSetting.GetPosX() );
        xCreateData.SetPostionY( xRedSetting.GetPosY() );
        xCreateData.SetDirX( xRedSetting.GetDirX() );
        xCreateData.SetDirY( xRedSetting.GetDirY() );
        xCreateData.SetFightCamp( CampDefine::GuildCampRed );

        const CampGuildBattleConfig::RefreshSetting::BarracksSetting& xBlueSetting = pSetting->GetBlueBarracksSetting();

        xCreateData.SetMonsterID( pSetting->GetBarracksID() );
        xCreateData.SetPostionX( xBlueSetting.GetPosX() );
        xCreateData.SetPostionY( xBlueSetting.GetPosY() );
        xCreateData.SetDirX( xBlueSetting.GetDirX() );
        xCreateData.SetDirY( xBlueSetting.GetDirY() );
        xCreateData.SetFightCamp( CampDefine::GuildCampBlue );

        // 加入刷怪信息
        RefreshIndex xRefreshIndex;
        xRefreshIndex.SetRedIndex( 0 );
        xRefreshIndex.SetMaxRedIndex( xRedSetting.GetMonsterCount() - 1 );
        xRefreshIndex.SetBlueIndex( 0 );
        xRefreshIndex.SetMaxBlueIndex( xBlueSetting.GetMonsterCount() - 1 );
        m_mapRefreshIndex.insert( std::make_pair( pSetting->GetBarracksID(), xRefreshIndex ) );
    }

    // 刷新其他阵营怪
    for ( int i = 0; i < pBattleConfig->GetRedCampMonsterCount(); ++i )
    {
        const CampGuildBattleConfig::CampMonster* pMonster = pBattleConfig->GetRedCampMonster( i );
        if ( pMonster == NULL )
        { continue; }

        xCreateData.SetMonsterID( pMonster->GetID() );
        xCreateData.SetPostionX( pMonster->GetPosX() );
        xCreateData.SetPostionY( pMonster->GetPosY() );
        xCreateData.SetDirX( pMonster->GetDirX() );
        xCreateData.SetDirY( pMonster->GetDirY() );
        xCreateData.SetFightCamp( CampDefine::GuildCampRed );

        MonsterCreater::CreateNormalMonster( xCreateData );
    }

    for ( int i = 0; i < pBattleConfig->GetBlueCampMonsterCount(); ++i )
    {
        const CampGuildBattleConfig::CampMonster* pMonster = pBattleConfig->GetBlueCampMonster( i );
        if ( pMonster == NULL )
        { continue; }

        xCreateData.SetMonsterID( pMonster->GetID() );
        xCreateData.SetPostionX( pMonster->GetPosX() );
        xCreateData.SetPostionY( pMonster->GetPosY() );
        xCreateData.SetDirX( pMonster->GetDirX() );
        xCreateData.SetDirY( pMonster->GetDirY() );
        xCreateData.SetFightCamp( CampDefine::GuildCampBlue );

        MonsterCreater::CreateNormalMonster( xCreateData );
    }
}

void CampGuildUnionBattle::SendCampBattleResourceMessage()
{
    // 5秒同步一次资源分
    /*MsgTellCampBattleResource xTell;
    xTell.nRedResource  = m_nRedResource;
    xTell.nBlueResource = m_nBlueResource;
    GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );*/
}

void CampGuildUnionBattle::ProcessCampBattleFightStatus()
{
    SendCampBattleResourceMessage();

    // 定时刷怪
    ProcessRefreshCampMonster();

    // 中立怪( Roshan )刷新
    ProcessRefreshNormalMonster();
}

void CampGuildUnionBattle::ProcessChangeToEndStatus()
{
    // 同步一次战场积分
    SendCampBattleResourceMessage();

    CampBattle::ProcessChangeToEndStatus();
}

void CampGuildUnionBattle::ProcessCampBattleResult( unsigned char uchFightCamp )
{
    // 处理战场奖励
	//当前战场结束 我们判断当前战场的轮数 1 2 3 4
	unsigned int nWinGuildID  = GuildDefine::InitID;
	unsigned int nLoseGuildID = GuildDefine::InitID;
	switch ( uchFightCamp )
	{
	case CampDefine::BaseCampRed:
		nWinGuildID  = m_nRedID;
		nLoseGuildID = m_nBlueID;
		break;
	case CampDefine::BaseCampBlue:
		nWinGuildID  = m_nBlueID;
		nLoseGuildID = m_nRedID;
		break;
	default:
		return;
		break;
	}

	// 处理战场奖励
	GameGuild* pWinGuild = theGameGuildManager.GetGuild( nWinGuildID );
	GameGuild* pLoseGuild = theGameGuildManager.GetGuild( nLoseGuildID );
	if ( pWinGuild == NULL || pLoseGuild == NULL )
	{ return; }

	MsgCampGuildBattleResult xResult;
	xResult.nWinGuildID  = nWinGuildID;
	xResult.nLoseGuildID = nLoseGuildID;
	pWinGuild->SendMessageToGuild(&xResult);
	pLoseGuild->SendMessageToGuild(&xResult);
	//GettheServer().SendMsgToCountry( &xResult, m_pBattleManager->GetCountryID(), true );
	//我们需要设置胜利公会的轮数
	uint32 Num = pWinGuild->GetBattleSum();
	uint32 Sum = theCampGuildUnionBattleConfig.GetBattleSum();
	++Num;
	if(Num>=Sum)
		Num = 0;
	pWinGuild->SetBattleSum(Num);//设置轮数

	CS2GSGuildBattleSum msg;
	msg.nGuildID = nWinGuildID;
	msg.battleSum = Num;
	GettheServer().SendMsgToCenterServer( &msg );

	const CampBattleConfig* pCampBattleConfig = m_pBattleManager->GetBattleConfig();
	for ( int i = 0; i < pCampBattleConfig->GetRewardSettingCount(); ++i )
	{
		const CampBattleConfig::RewardSetting* pSetting = pCampBattleConfig->GetRewardSetting( i );
		if ( pSetting == NULL )
		{ continue; }

		switch ( pSetting->GetType() )
		{
		case CampBattleConfig::RewardSetting::RewardGuildExp:   // 奖励帮派经验
			{
				pWinGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildExp, GuildDefine::OperateAdd, pSetting->GetWinValue() );

				//LYH日志添加
				theLogEventService.LogGuildDetail(0,0,pWinGuild->GetID(),0,pSetting->GetWinValue(),0,"NULL");

					
				pLoseGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildExp, GuildDefine::OperateAdd, pSetting->GetLoseValue() );

				//LYH日志添加
				theLogEventService.LogGuildDetail(0,0,pLoseGuild->GetID(),0,pSetting->GetLoseValue(),0,"NULL");
			}
			break;
		case CampBattleConfig::RewardSetting::RewardGuildMission:   // 奖励帮派使命点
			{
				pWinGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildMission, GuildDefine::OperateAdd, pSetting->GetWinValue() );
				pLoseGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildMission, GuildDefine::OperateAdd, pSetting->GetLoseValue() );
			}
			break;
		case CampBattleConfig::RewardSetting::RewardGuildSalary:    // 奖励帮派津贴
			{
				pWinGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildSalary, GuildDefine::OperateAdd, pSetting->GetWinValue() );
				pLoseGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildSalary, GuildDefine::OperateAdd, pSetting->GetLoseValue() );
			}
			break;
		case CampBattleConfig::RewardSetting::RewardPlayerExp:  // 奖励个人经验
			{   // 只对参加的玩家
				for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
				{
					GamePlayer* pPlayer = GameGuild::GetPlayer( iter->first );
					if ( pPlayer == NULL )
					{ continue; }

					unsigned int nRewardValue = ( iter->second.GetFightCamp() == uchFightCamp ? pSetting->GetWinValue() : pSetting->GetLoseValue() );
					unsigned int nRewardExp = nRewardValue * pPlayer->GetLevel();
					pPlayer->IncreaseExp( nRewardExp, 0, NULL );

				}
			}
			break;
		case CampBattleConfig::RewardSetting::RewardPlayerGuildOffer:   // 奖励帮贡
			{
				for ( BattlePlayerMapIter iter = m_mapBattlePlayer.begin(); iter != m_mapBattlePlayer.end(); ++iter )
				{
					GamePlayer* pPlayer = GameGuild::GetPlayer( iter->first );
					if ( pPlayer == NULL )
					{ continue; }

					unsigned int nRewardValue = ( iter->second.GetFightCamp() == uchFightCamp ? pSetting->GetWinValue() : pSetting->GetLoseValue() );
					pPlayer->OperateGuildOffer( GuildDefine::OperateAdd, nRewardValue );
				}
			}
			break;
		default:
			break;
		}
	}
}

void CampGuildUnionBattle::KillCampBattleMonster( unsigned char uchFightCamp, unsigned int nPlayerID, int nMonsterID )
{
    CampBattle::KillCampBattleMonster( uchFightCamp, nPlayerID, nMonsterID );

    // 如果是中立怪, 设置它10分钟后再刷一个出来
	const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
	map<int,CampGuildBattleConfig::NormalMonster> mapList;
	pBattleConfig->GetNormalMonster(mapList);
	if(mapList.count(nMonsterID) == 1 && m_xNormalTimer.count(nMonsterID) == 1)
	{
		m_xNormalTimer[nMonsterID].StartTimer( HQ_TimeGetTime(), mapList[nMonsterID].GetTimeSpace() * OneMinuteMicroSecond );
	}
   /* const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
    const CampGuildBattleConfig::NormalMonster& xNormalMonster = pBattleConfig->GetNormalMonster();
    if ( nMonsterID == xNormalMonster.GetID() )
    {
        m_xNormalTimer.StartTimer( HQ_TimeGetTime(), xNormalMonster.GetTimeSpace() * OneMinuteMicroSecond );
        return;
    }*/

    // 判断是否是兵营
    RefreshIndexMapIter iter = m_mapRefreshIndex.find( nMonsterID );
    if ( iter == m_mapRefreshIndex.end() )
    { return; }

    // 被杀一方不能刷兵了, 自己方刷一路大兵
    switch ( CampDefine::GetBaseFightCamp( uchFightCamp ) )
    {
    case CampDefine::BaseCampRed:
        iter->second.SetRedIndex( iter->second.GetMaxRedIndex() );
        iter->second.SetBlueIndex( -1 );
        break;
    case CampDefine::BaseCampBlue:
        iter->second.SetBlueIndex( iter->second.GetMaxBlueIndex() );
        iter->second.SetRedIndex( -1 );
        break;
    default:
        return;
        break;
    }
}
void CampGuildUnionBattle::ProcessChangeToFightStatus()
{
    CampBattle::ProcessChangeToFightStatus();

    if ( GetStatus() == CampDefine::StatusEnd )
    { return; } // 结束了就不刷怪了

    // 开启刷怪定时器
    m_xRefreshTimer.StartTimer( 1, CampGuildBattleConfig::RefreshSetting::GetTimeSpace() * 1000 );

	const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
    //const CampGuildBattleConfig::NormalMonster& xNormalMonster = pBattleConfig->GetNormalMonster();

	map<int,CampGuildBattleConfig::NormalMonster> mapList;
	pBattleConfig->GetNormalMonster(mapList);
	map<int,CampGuildBattleConfig::NormalMonster>::iterator Iter = mapList.begin();
	for(;Iter !=mapList.end();++Iter)
	{
		if(m_xNormalTimer.count(Iter->first) != 1)
			continue;
		m_xNormalTimer[Iter->first].StartTimer( HQ_TimeGetTime(), Iter->second.GetTimeSpace() * OneMinuteMicroSecond );
	}

    /*const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
    const CampGuildBattleConfig::NormalMonster& xNormalMonster = pBattleConfig->GetNormalMonster();
    m_xNormalTimer.StartTimer( HQ_TimeGetTime(), xNormalMonster.GetTimeSpace() * OneMinuteMicroSecond );*/
}

void CampGuildUnionBattle::ProcessRefreshCampMonster()
{
    if ( !m_xRefreshTimer.DoneTimer( HQ_TimeGetTime() ) )
    { return; }

    GameStage* pStage = theGameWorld.GetStageById( GetBattleMapID() );
    if ( pStage == NULL )
    { return; }

    MonsterCreateData xCreateData;
    xCreateData.SetMapID( pStage->GetStageID() );
    xCreateData.SetCreateType( 0 );
    xCreateData.SetCount( CampGuildBattleConfig::RefreshSetting::GetCount() );
    xCreateData.SetRadius( CampGuildBattleConfig::RefreshSetting::GetRadius() );
    xCreateData.SetFightCamp( CampGuildBattleConfig::RefreshSetting::GetType() );

    const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
    for ( RefreshIndexMapIter iter = m_mapRefreshIndex.begin(); iter != m_mapRefreshIndex.end(); ++iter )
    {
        const CampGuildBattleConfig::RefreshSetting* pSetting = pBattleConfig->GetRefreshSetting( iter->first );
        if ( pSetting == NULL )
        { continue; }

        // 红方阵营刷兵
        const CampGuildBattleConfig::RefreshSetting::BarracksSetting& xRedBarrackSetting = pSetting->GetRedBarracksSetting();
        const CampGuildBattleConfig::RefreshSetting::MonsterDataList* pRedMonsterDataList = xRedBarrackSetting.GetMonster( iter->second.GetRedIndex() );
		if(pRedMonsterDataList != NULL)
		{
			//刷出一波怪
			vector<CampGuildBattleConfig::RefreshSetting::MonsterData> vec;
			pRedMonsterDataList->GetAllMonster(vec);
			vector<CampGuildBattleConfig::RefreshSetting::MonsterData>::iterator Iter = vec.begin();
			for(;Iter !=vec.end();++Iter)
			{
				//根据数据刷怪
				MonsterCreateData xCreateDataRed;
				xCreateDataRed.SetMapID( pStage->GetStageID() );
				xCreateDataRed.SetCount( 1 );
				xCreateDataRed.SetRadius( Iter->GetRouteID());
				xCreateDataRed.SetPostionX(Iter->GetPosX());
				xCreateDataRed.SetPostionY(Iter->GetPosY());
				xCreateDataRed.SetMonsterID(Iter->GetMonsterID());
				xCreateDataRed.SetDirection(Iter->GetAngle());
				xCreateData.SetFightCamp( CampDefine::GuildCampRed );
				MonsterCreater::ProcessCreateNormalMonster( xCreateDataRed );
			}
		}	

        // 蓝方阵营刷兵
        const CampGuildBattleConfig::RefreshSetting::BarracksSetting& xBlueBarrackSetting = pSetting->GetBlueBarracksSetting();
        const CampGuildBattleConfig::RefreshSetting::MonsterDataList* pBlueMonsterDataList = xBlueBarrackSetting.GetMonster( iter->second.GetBlueIndex() );
		if(pBlueMonsterDataList != NULL)
		{
			//刷出一波怪
			vector<CampGuildBattleConfig::RefreshSetting::MonsterData> vec;
			pBlueMonsterDataList->GetAllMonster(vec);
			vector<CampGuildBattleConfig::RefreshSetting::MonsterData>::iterator Iter = vec.begin();
			for(;Iter !=vec.end();++Iter)
			{
				//根据数据刷怪
				MonsterCreateData xCreateDataBlue;
				xCreateDataBlue.SetMapID( pStage->GetStageID() );
				xCreateDataBlue.SetCount( 1 );
				xCreateDataBlue.SetRadius( Iter->GetRouteID());
				xCreateDataBlue.SetPostionX(Iter->GetPosX());
				xCreateDataBlue.SetPostionY(Iter->GetPosY());
				xCreateDataBlue.SetMonsterID(Iter->GetMonsterID());
				xCreateDataBlue.SetDirection(Iter->GetAngle());
				xCreateData.SetFightCamp( CampDefine::GuildCampBlue );
				MonsterCreater::ProcessCreateNormalMonster( xCreateDataBlue );
			}
		}	
    }
}

void CampGuildUnionBattle::ProcessRefreshNormalMonster()
{
	map<int,CampGuildBattleConfig::NormalMonster> mapList;
	const CampGuildBattleConfig* pBattleConfig = static_cast< const CampGuildBattleConfig* >( m_pBattleManager->GetBattleConfig() );
	pBattleConfig->GetNormalMonster(mapList);
	map<int,CampGuildBattleConfig::NormalMonster>::iterator Iter = mapList.begin();
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
		// 通知战场内所有玩家
		MsgTellCampGuildBattleRefreshMonster xTell;
		xTell.nMonsterID = Iter->second.GetID();
		xTell.nStringID  = Iter->second.GetString();
		GettheServer().SendMsgToStage( &xTell, GetBattleMapID() );
	}
}