#include "GameGuildGeneralBattleManager.h"
#include "GameGuildGeneralBattleConfig.h"
#include "GuildManager.h"
#include "GameGuildGeneralBattle.h"
#include <algorithm>
#include <functional>
#include "GameWorld.h"
#include "GamePlayer.h"
#include "GameBattleMessage.h"
#include "ShareData.h"
#include "Configure.h"
#include "GameBattleDefine.h"
#include "GuildDefine.h"
#include "GameBattleMessage.h"
GameGuildGeneralBattleManager::GameGuildGeneralBattleManager():m_BattleValue(0),m_BattleValueIsOpen(false)
{
    SetGameBattleType( GameBattleDefine::GameBattle_Type_GuildGeneral );
	m_BattleValue = GuildDefine::GameBattleGuildGeneral;//这个值和以前的战场必须统一起来
	m_BattleValueIsOpen = theGameGuildManager.GetCampBattleConfig()->m_GuildSetting.IsOpen;
}
GameGuildGeneralBattleManager::~GameGuildGeneralBattleManager()
{
    Destroy();
}
void GameGuildGeneralBattleManager::Init()
{

}
void GameGuildGeneralBattleManager::Destroy()
{
	for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); ++iter )
    {
        iter->second->Destroy();
    }
	m_mapGameBattle.clear();
}
void GameGuildGeneralBattleManager::AddGameGuildGeneralBattleOnceInfo(unsigned int ID,unsigned int MapID,unsigned int SrcGuildID,unsigned int DestGuildID,__int64 BeginTime,unsigned int MoneySum,unsigned int GuildMoney,unsigned int GuildMission)
{
	//给管理器里添加新的战场数据
	if(MapID != GetGameBattleMapID())
		return;
	if(m_pInfoList.count(ID) !=0)
		return;
	GameGuildGeneralBattleOnceInfo info;
	info.SetData(ID,SrcGuildID,DestGuildID,BeginTime,MapID,MoneySum,GuildMoney,GuildMission);
	m_pInfoList.insert(std::map<unsigned int,GameGuildGeneralBattleOnceInfo>::value_type(ID,info));

	//新的数据添加完毕后 我们需要立即处理下战场的当前状态
	HandleGameGuildGeneralBattleStates(ID);
}
void GameGuildGeneralBattleManager::HandleGameGuildGeneralBattleStates(unsigned int ID)
{
	if(m_pInfoList.count(ID) != 1)
		return;
	//立即成立当前战场的状态
	time_t nowtime;
	time(&nowtime);
	__int64 NowTime = nowtime;
	switch ( m_pInfoList[ID].GetBattleStatus())
	{
	case GameBattleDefine::StatusInit:        
		// 战场初始状态
		ProcessBattleInitStatus( ID,NowTime);
	case GameBattleDefine::StatusEnter:
		// 战场进入状态
		ProcessBattleEnterStatus( ID,NowTime);
	case GameBattleDefine::StatusFight:
		// 战场战斗状态
		ProcessBattleFightStatus(ID,NowTime);
	case GameBattleDefine::StatusEnd:
		// 战场结束状态
		ProcessBattleEndStatus(ID,NowTime);
	}
	if(m_pInfoList[ID].GetBattleStatus() == GameBattleDefine::StatusEnd)
	{
		GS2CSDelCampBattleData msg;
		msg.ID = ID;
		GettheServer().SendMsgToCenterServer( &msg );
		m_pInfoList.erase(ID);
	}
}
void GameGuildGeneralBattleManager::RunUpdate( unsigned int nCurrentTime )
{
	//更新函数 我们需要更新
	time_t nowtime;
	time(&nowtime);
	__int64 NowTime = nowtime;
	std::map<unsigned int,GameGuildGeneralBattleOnceInfo>::iterator Iter = m_pInfoList.begin();
	for(;Iter != m_pInfoList.end();++Iter)
	{
		switch ( Iter->second.GetBattleStatus())
		{
		 case GameBattleDefine::StatusInit:        
			// 战场初始状态
			ProcessBattleInitStatus( Iter->first,NowTime);
			break;
		case GameBattleDefine::StatusEnter:
			// 战场进入状态
			ProcessBattleEnterStatus( Iter->first,NowTime);
			break;
		case GameBattleDefine::StatusFight:
			// 战场战斗状态
			ProcessBattleFightStatus( Iter->first,NowTime);
			break;
		case GameBattleDefine::StatusEnd:
			// 战场结束状态
			ProcessBattleEndStatus(Iter->first,NowTime);
			break;
		default:
			Iter->second.SetBattleStatus( GameBattleDefine::StatusInit );
			break;
		}
		// 处理状态剩余时间
		ProcessBattleLeftTime(Iter->first, nCurrentTime );
	}
	Iter = m_pInfoList.begin();
	for(;Iter != m_pInfoList.end();)
	{
		switch ( Iter->second.GetBattleStatus())
		{
		case GameBattleDefine::StatusEnd:
		case GameBattleDefine::StatusRelease:
			{
				//当前战场已经结束了 我们需要删除数据库里的数据
				GS2CSDelCampBattleData msg;
				msg.ID = Iter->first;
				GettheServer().SendMsgToCenterServer( &msg );
				Iter = m_pInfoList.erase(Iter);
			}
			break;
		default:
			++Iter;
			break;
		}
	}
    // 战场更新
    for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); )
    {
        switch ( iter->second->RunUpdate( nCurrentTime ) )
        {
        case GameBattleDefine::StatusRelease:
            {
                iter->second->Destroy();
                iter = m_mapGameBattle.erase( iter );
            }
            break;
        default:
            ++iter;
            break;
        }
    }
}

void GameGuildGeneralBattleManager::ProcessBattleInitStatus(unsigned int ID,__int64 NowTime)
{
    // 判断是否到了战场准备时间
    if(m_pInfoList.count(ID) != 1)
		return;
	if(m_pInfoList[ID].GetBattleStatus() != GameBattleDefine::StatusInit)
		return;
	//判断 分钟数是否相同
	__int64 BeginTime = m_pInfoList[ID].BeginTime;
	//int MaxKeepTime = m_pConfig.GetEnterTimeKeepTime()*60+m_pConfig.GetFightTimeKeepTime()*60;
	if(NowTime >= BeginTime /*&& NowTime< BeginTime + MaxKeepTime*/)
	{
		m_pInfoList[ID].SetLeftTime( m_pConfig.GetEnterTimeKeepTime() * OneMinuteMicroSecond );
		m_pInfoList[ID].m_nLastUpdateTime = HQ_TimeGetTime();
		ProcessChangeStatus(ID, GameBattleDefine::StatusEnter );
	} 
}
void GameGuildGeneralBattleManager::ProcessBattleEnterStatus(unsigned int ID,__int64 NowTime)
{
   if(m_pInfoList.count(ID) != 1)
		return;
   if(m_pInfoList[ID].GetBattleStatus() != GameBattleDefine::StatusEnter)
		return;
    __int64 BeginTime = m_pInfoList[ID].BeginTime + m_pConfig.GetEnterTimeKeepTime()*60;
	/*int MaxKeepTime = m_pConfig.GetSignUpKeepTime()*60 + m_pConfig.GetPrepareTimeKeepTime()*60 + m_pConfig.GetEnterTimeKeepTime()*60
		+m_pConfig.GetFightTimeKeepTime()*60;*/
	if(NowTime >= BeginTime /*&& NowTime< BeginTime + MaxKeepTime*/)
	{
		/*if(m_pInfoList[ID].GetBattleStatus() == GameBattleDefine::StatusInit)
			ProcessChangeStatus(ID, GameBattleDefine::StatusEnter );*/
		// 处理战场改变到战斗状态
		m_pInfoList[ID].SetLeftTime( m_pConfig.GetFightTimeKeepTime() * OneMinuteMicroSecond );
		m_pInfoList[ID].m_nLastUpdateTime = HQ_TimeGetTime();
		ProcessChangeStatus(ID, GameBattleDefine::StatusFight );	
	}
}

void GameGuildGeneralBattleManager::ProcessBattleFightStatus(unsigned int ID,__int64 NowTime)
{
     if(m_pInfoList.count(ID) != 1)
		return;
	 if(m_pInfoList[ID].GetBattleStatus() != GameBattleDefine::StatusFight)
		return;
    __int64 BeginTime = m_pInfoList[ID].BeginTime + m_pConfig.GetEnterTimeKeepTime()*60 +m_pConfig.GetFightTimeKeepTime()*60;
	/*int MaxKeepTime = m_pConfig.GetSignUpKeepTime()*60 + m_pConfig.GetPrepareTimeKeepTime()*60 + m_pConfig.GetEnterTimeKeepTime()*60
		+m_pConfig.GetFightTimeKeepTime()*60;*/
	if(NowTime >= BeginTime /*&& NowTime< BeginTime + MaxKeepTime*/)
	{
		/*if(m_pInfoList[ID].GetBattleStatus() == GameBattleDefine::StatusInit)
			ProcessChangeStatus(ID, GameBattleDefine::StatusEnter );
		if(m_pInfoList[ID].GetBattleStatus() == GameBattleDefine::StatusEnter)
			ProcessChangeStatus(ID, GameBattleDefine::StatusFight );*/
		m_pInfoList[ID].SetLeftTime( m_pConfig.GetEndTimeKeepTime() * OneMinuteMicroSecond );
		m_pInfoList[ID].m_nLastUpdateTime = HQ_TimeGetTime();
		ProcessChangeStatus(ID, GameBattleDefine::StatusEnd );
	}
}

void GameGuildGeneralBattleManager::ProcessBattleEndStatus(unsigned int ID,__int64 NowTime)
{

}

void GameGuildGeneralBattleManager::ProcessChangeStatus(unsigned int ID, unsigned char uchStatus )
{
    // 设置状态
	if(m_pInfoList.count(ID) != 1)
		return;
    m_pInfoList[ID].SetBattleStatus( uchStatus );

    switch(  m_pInfoList[ID].GetBattleStatus() )
    {
		//报名状态
    case GameBattleDefine::StatusSignUp:
        ProcessChangeToSignUpStatus(ID);
        break;
		//准备状态
    case GameBattleDefine::StatusPrepare:
        ProcessChangeToPrepareStatus(ID);
        break;
    case GameBattleDefine::StatusEnter:
        ProcessChangeToEnterStatus(ID);
        break;
    case GameBattleDefine::StatusFight:
        ProcessChangeToFightStatus(ID);
        break;
	case GameBattleDefine::StatusEnd:
		ProcessChangeToEndStatus(ID);
		break;
    default:
        break;
    }
	if (0xffffffff != m_pInfoList[ID].GetMapID())
	{
		SendBattleStatusMessage(ID,  m_pInfoList[ID].GetBattleStatus() );
	}
}
void GameGuildGeneralBattleManager::SendBattleStatusMessage(unsigned int ID, unsigned char uchStatus )
{
	if(m_pInfoList.count(ID) != 1)
		return;
	GameGuild* pSrcGuild = theGameGuildManager.GetGuild(m_pInfoList[ID].RedGuildID);
	GameGuild* pDestGuild = theGameGuildManager.GetGuild(m_pInfoList[ID].BlueGuildID);
    switch ( uchStatus )
    {
    case GameBattleDefine::StatusSignUp:
    case GameBattleDefine::StatusPrepare:
    case GameBattleDefine::StatusEnter:
        {
			MsgTellGameBattleStatus xTell;
			xTell.uchCampBattleType   = GetGameBattleType();
			xTell.uchCampBattleStatus = uchStatus;
			xTell.nLeftTime           = m_pInfoList[ID].GetLeftTime() / 1000;
			if(pSrcGuild)
				pSrcGuild->SendMessageToGuild(&xTell,GuildDefine::InitID,0,true);
			if(pDestGuild)
				pDestGuild->SendMessageToGuild(&xTell,GuildDefine::InitID,0,true);
        }
        break;
    case GameBattleDefine::StatusFight:
    case GameBattleDefine::StatusEnd:
        {
            // 这2个状态发功给战场地图
            for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); ++iter )
            {
                // 设置状态
                iter->second->ProcessStatusChange( uchStatus );
            }
        }
        break;
    default:
        break;
    }
}
void GameGuildGeneralBattleManager::ProcessBattleLeftTime(unsigned int ID, unsigned int nCurrentTime )
{
    // 获得过了多少时间
	if(m_pInfoList.count(ID) != 1)
		return;
    unsigned int nPassTime = GameTime::GetPassTime( nCurrentTime, m_pInfoList[ID].m_nLastUpdateTime );
    m_pInfoList[ID].SubLeftTime( nPassTime );   // 设置剩余时间
    m_pInfoList[ID].m_nLastUpdateTime = nCurrentTime;
}

// 处理转换到报名状态逻辑
void GameGuildGeneralBattleManager::ProcessChangeToSignUpStatus(unsigned int ID)
{
	if(m_pInfoList.count(ID) != 1)
		return;
    const GameGuildGeneralBattleConfig::MapSetting* pSetting = m_pConfig.GetMapSetting();
    if ( pSetting == NULL )
		return;
    if ( !g_Cfg.IsMapRun( pSetting->GetMapID() ) )
		return;
	m_pInfoList[ID].SetMapID( pSetting->GetMapID() );

	const GameGuildGeneralBattleConfig::CKingdomMap &xKingdomMap = m_pConfig.GetKingdomMap();
	SetkingdomMapInfo(xKingdomMap.GetMapID(),
					  xKingdomMap.GetMapX(),
					  xKingdomMap.GetMapY());

}
void GameGuildGeneralBattleManager::ProcessChangeToFightStatus(unsigned int ID)
{
	//战场正式开始战斗 去除地图内全部玩家的BUFF
	
}
void GameGuildGeneralBattleManager::AddGameBattle( GameGuildGeneralBattle* pGameBattle )
{
    if ( pGameBattle == NULL )
    { return; }

    m_mapGameBattle[ pGameBattle->GetBattleMapID() ] = pGameBattle;
}

GameGuildGeneralBattle* GameGuildGeneralBattleManager::GetGameBattleByPlayerID( unsigned int nPlayerID )
{
    for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); ++iter )
    {
		GameBattleDefine::BattlePlayer* pBattlePlayer = iter->second->GetBattlePlayer( nPlayerID );
        if ( pBattlePlayer != NULL )
        { return iter->second; }
    }

    return NULL;
}

GameGuildGeneralBattle* GameGuildGeneralBattleManager::GetGameBattleByUnitID( unsigned int nUnitID )
{
    for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); ++iter )
    {
        if ( iter->second->GetRedID() == nUnitID || iter->second->GetBlueID() == nUnitID )
        { return iter->second; }
    }

    return NULL;
}
GameGuildGeneralBattle* GameGuildGeneralBattleManager::GetGameBattleByID(unsigned int ID)
{
	for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); ++iter )
    {
        if(iter->second->GetBattleIndexID() == ID)
			return iter->second;
    }
	return NULL;
}
GameGuildGeneralBattle* GameGuildGeneralBattleManager::GetGameBattleByOnlyMapID(unsigned int MapID)
{
	for ( GameBattleMapIter iter = m_mapGameBattle.begin(); iter != m_mapGameBattle.end(); ++iter )
    {
        if(iter->second->GetBattleMapID() == MapID)
			return iter->second;
    }
	return NULL;
}
void GameGuildGeneralBattleManager::SetkingdomMapInfo(int map_id,float map_x,float map_y)
{
	m_KingdomMapID = map_id;
	m_X = map_x;
	m_Y = map_y;
}

// 处理转换到准备状态逻辑
void GameGuildGeneralBattleManager::ProcessChangeToPrepareStatus(unsigned int ID)
{	
}
// 处理转换到进入状态逻辑
void GameGuildGeneralBattleManager::ProcessChangeToEnterStatus(unsigned int ID)
{
    // 创建副本场景
	if(m_pInfoList.count(ID) != 1)
		return;
	#ifdef _DEBUG
    #else
	GameGuild * pRedGuild = theGameGuildManager.GetGuild(m_pInfoList[ID].RedGuildID);
	GameGuild * pBlueGuild = theGameGuildManager.GetGuild(m_pInfoList[ID].BlueGuildID);
	if(!pRedGuild || !pBlueGuild)
		return;
	#endif
    // 创建副本
    unsigned int nBattleMapID = theGameWorld.GetEctypeMapID(m_pInfoList[ID].GetMapID(), true );
    theGameWorld.MultiCreateStage( m_pInfoList[ID].GetMapID(), nBattleMapID );

    // 创建战场
    GameGuildGeneralBattle* pGameBattle = GameGuildGeneralBattle::CreateGameGuildGeneralBattle< GameGuildGeneralBattle >();
	pGameBattle->SetGameBattleManager( this );
	pGameBattle->SetBattleMapID( nBattleMapID );
	pGameBattle->SetRedID( m_pInfoList[ID].RedGuildID );
	pGameBattle->SetBlueID( m_pInfoList[ID].BlueGuildID );
	pGameBattle->SetWinResource( m_pConfig.GetResourceSetting().GetMaxResource() );
	pGameBattle->SetData(ID,m_pInfoList[ID].MoneySum,m_pInfoList[ID].GuildMoneySum,m_pInfoList[ID].GuildMissionSum);

	// 发送是否进入战场消息
	pGameBattle->SendEnterGameBattleMessage();

	// 添加到战场列表中
	AddGameBattle( pGameBattle );
	pGameBattle->SetGuildGameBattleTimeMap();
}
bool GameGuildGeneralBattleManager::ShowGameBattleEnter( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return false; }

    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL )
    { return false; }

	//判断玩家的权限
	if(m_BattleValue !=0 && m_BattleValueIsOpen)
	{
		GameGuild * pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
		if(!pGuild)
			return false;
		GuildMember * pMember = pGuild->GetMember(pPlayer->GetDBCharacterID()) ;
		if(!pMember)
			return false;
		if(!(pMember->GetCampBattleValue() & m_BattleValue))
			return false;
	}

	GameGuildGeneralBattle* pGameBattle = GetGameBattleByUnitID( pGuild->GetID() );
    if ( pGameBattle == NULL )
    { return false; }

	if(m_pInfoList.count(pGameBattle->GetBattleIndexID()) != 1)
		return false;

	if ( m_pInfoList[pGameBattle->GetBattleIndexID()].GetBattleStatus() != GameBattleDefine::StatusEnter )
    { return false; }

    MsgShowGameGuildBattleEnter xShow;
    xShow.uchBattleType = GetGameBattleType();
    xShow.nRedGuildID   = pGameBattle->GetRedID();
    xShow.nBlueGuildID  = pGameBattle->GetBlueID();
    pPlayer->SendMessageToClient( &xShow );

    return true;
}

bool GameGuildGeneralBattleManager::EnterGameBattle(GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return false; }

    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL )
    { 
        pPlayer->SendOperateAckToClient< MsgEnterGameBattleAck >( CampDefine::Enter_MustSignUpGuild );
        return false;
    }

	if(m_BattleValue !=0 && m_BattleValueIsOpen)
	{
		GuildMember * pMember = pGuild->GetMember(pPlayer->GetDBCharacterID()) ;
		if(!pMember)
			return false;
		if(!(pMember->GetCampBattleValue() & m_BattleValue))
			return false;
	}

	// 查找战场
	GameGuildGeneralBattle* pGameBattle = GetGameBattleByUnitID( pGuild->GetID() );
    if ( pGameBattle == NULL )
    { 
        pPlayer->SendOperateAckToClient< MsgEnterGameBattleAck >( CampDefine::Enter_MustSignUpGuild );
        return false;
    }
	if(m_pInfoList.count(pGameBattle->GetBattleIndexID()) != 1)
		return false;
	if ( m_pInfoList[pGameBattle->GetBattleIndexID()].GetBattleStatus() != GameBattleDefine::StatusEnter  &&  m_pInfoList[pGameBattle->GetBattleIndexID()].GetBattleStatus() != GameBattleDefine::StatusFight)
	{ 
		pPlayer->SendOperateAckToClient< MsgEnterGameBattleAck >( CampDefine::Enter_NotEnterStatus );
		return false; 
	}

    const GameGuildGeneralBattleConfig::EnterSetting &xSetting = m_pConfig.GetEnterSetting();
    if ( pPlayer->GetLevel() < xSetting.GetMinLevel() )
    {
        pPlayer->SendOperateAckToClient< MsgEnterGameBattleAck >( CampDefine::Enter_NotEnterStatus );
        return false; 
    }

	GameBattleDefine::BattlePlayer* pBattlePlayer = pGameBattle->GetBattlePlayer( pPlayer->GetDBCharacterID() );
    if ( pBattlePlayer == NULL )
    {
        // 判断阵营
        unsigned char uchFightGame = pGameBattle->GetGameBattleFight( pGuild->GetID() );
     
        // 判断进入数量, 满了就不能在进入了
        if ( pGameBattle->GetBattlePlayerCount( uchFightGame ) >= xSetting.GetMaxCount() )
        {
            pPlayer->SendOperateAckToClient< MsgEnterGameBattleAck >( CampDefine::Enter_MaxCount );
            return false;
        }

        // 设置阵营, 只设置, 不发消息, 在MsgMapLoad函数中处理消息发送给客户端
        pPlayer->SetFightGame( uchFightGame );

        // 加入战场玩家
		GameBattleDefine::BattlePlayer xBattlePlayer;
        xBattlePlayer.SetName( pPlayer->GetCharName() );
        xBattlePlayer.SetLevel( pPlayer->GetLevel() );
        xBattlePlayer.SetProfession( pPlayer->GetProfession() );
        xBattlePlayer.SetFight( pPlayer->GetFightCamp() );
        pGameBattle->AddBattlePlayer( pPlayer->GetDBCharacterID(), xBattlePlayer );
    }

    // 进入战场
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_pInfoList[pGameBattle->GetBattleIndexID()].GetMapID() );
    if ( pMapData == NULL )
    { return false; }

    MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByIndex( pGameBattle->GetReliveIndex( pPlayer ) );
    if ( pRelive == NULL )
    { return false; }


	int BuffID = m_pConfig.GetEnterBuff().GetBuffID();
	int Level = m_pConfig.GetEnterBuff().GetLevel();
	if(BuffID != 0 && Level != 0 && m_pInfoList[pGameBattle->GetBattleIndexID()].GetBattleStatus() == GameBattleDefine::StatusEnter)  //玩家刚进入的时候添加一个BUFF
	{
		long nResult = GLR_Success;
		nResult = pPlayer->ApplyBufferStatus(BuffID,Level, pPlayer->GetID(), SCharBuff::StatusEventType_Other, 0);
		if ( nResult == GLR_Success  )
		{
			pPlayer->OnBuffStatusChanged( true );
		}
	}

	pGameBattle->SendBattleStatusMessage(pPlayer);
	return pPlayer->FlyToMapReq(pGameBattle->GetBattleMapID(),pRelive->PositionX, pRelive->PositionY,pRelive->Direction );
}
void GameGuildGeneralBattleManager::KillGameBattleMonster( unsigned char uchFight, unsigned int nPlayerID, int nMonsterID ,unsigned int MapID)
{
	//nPlayerID 有可能为 0  我们需要做其他的处理 
	GameGuildGeneralBattle* pBattle = GetGameBattleByOnlyMapID(MapID);
	if(!pBattle)
		return;
	pBattle->KillGameBattleMonster(uchFight,nPlayerID,nMonsterID);
}
