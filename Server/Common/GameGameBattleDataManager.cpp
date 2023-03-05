#include "GameBattleDataManager.h"
#include "Configure.h"
#include "GameBattleControl.h"
#include "GameGuildGeneralBattleManager.h"
#include "GameGuildGeneralBattle.h"
#include "ShareData.h"
template<>
void GameCampBattleDataManager::RunUpdate( unsigned int nCurrentTime )
{
	//循环变量所有时间 当时间到了的换 开始创建战场并且设置战场的状态
	if(GuildCampBattleDataMap.empty())
		return;
	std::map<unsigned int,GameBattleDefine::GuildCampBattle>::iterator Iter = GuildCampBattleDataMap.begin();
	for(;Iter != GuildCampBattleDataMap.end(); ++Iter)
	{
		if ( !g_Cfg.IsMapRun( Iter->second.MapID ) )
			continue;
		//1.判断是否到了开战的时间 到了的话 我们创建一个战场管理器 加入到战场的Control里面去 并且设置战场的状态为开始报名状态

		//2.战场开启后 我们删除数据

	}
}
template<>
void GameCampBattleDataManager::LoadAddDataByDataBase()
{

}
template<>
void GameCampBattleDataManager::SendDataToServer(unsigned int nServerID )
{
	//将指定公会的约战信息发送到客户端去
	GamePlayer * pPlayer = theRunTimeData.GetGamePlayerByDBID(nServerID);
	if(pPlayer)
	{
		unsigned int GuildID = pPlayer->GetGuildID();
		GameGuild * pGuild = theGameGuildManager.GetGuild(GuildID);
		if(!pGuild)
			return;
		MsgLoadCampBattleDataAck msg;
		msg.ClearAllData();
		if(!GuildCampBattleDataMap.empty())
		{
			int Sum = 0;
			int Index = 0;
			std::map<unsigned int,GameBattleDefine::GuildCampBattle>::iterator Iter = GuildCampBattleDataMap.begin();
			for(;Iter !=GuildCampBattleDataMap.end();++Iter)
			{
				if(Iter->second.SrcGuildID != GuildID && Iter->second.DestGuildID != GuildID)
					continue;
				if(Iter->second.IsWrite)
					continue;
				++Sum;
			}
			Iter = GuildCampBattleDataMap.begin();
			for(;Iter !=GuildCampBattleDataMap.end();++Iter)
			{
				if(Iter->second.SrcGuildID != GuildID && Iter->second.DestGuildID != GuildID)
					continue;
				if(Iter->second.IsWrite)
					continue;
				++Index;
				if(msg.PushInfo(Iter->second,(Index == Sum)))
				{
					pPlayer->SendMessageToClient(&msg);
					msg.ClearAllData();
				}
			}
		}
		else
		{
			msg.Sum = 0;
			msg.IsEnd = true;
			pPlayer->SendMessageToClient(&msg);
		}
	}
}
template<>
void GameCampBattleDataManager::DedGuildBattleData(unsigned int ID)
{
	//取消公会约战
	//1.判断数据是否存在
	if(GuildCampBattleDataMap.count(ID) != 1)
		return;
	//2.删除数据
	//发送命令到客户端去
	MsgDelCampBattleDataAck msg;
	msg.ID = ID;
	GameGuild * pSrcGuild = theGameGuildManager.GetGuild(GuildCampBattleDataMap[ID].SrcGuildID);
	GameGuild * pDestGuild = theGameGuildManager.GetGuild(GuildCampBattleDataMap[ID].DestGuildID);
	if(pSrcGuild)
		pSrcGuild->SendMessageToGuild(&msg,GuildDefine::InitID,0,false);
	if(pDestGuild)
		pDestGuild->SendMessageToGuild(&msg,GuildDefine::InitID,0,false);
	GuildCampBattleDataMap.erase(ID);
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)	
		return;
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByID(ID);
	if(pBattle)
	{
		//立即结束战场
		pManager->ProcessChangeStatus(ID,GameBattleDefine::StatusEnd);//让战场转换到结束状态
	}
}
template<>
void GameCampBattleDataManager::AddGuildBattleData(GameBattleDefine::GuildCampBattle& pData)
{
	//开启公会约战
	//1.加入到集合里面去
	if(GuildCampBattleDataMap.count(pData.ID) != 0)
		GuildCampBattleDataMap.erase(pData.ID);
	GuildCampBattleDataMap.insert(std::map<unsigned int,GameBattleDefine::GuildCampBattle>::value_type(pData.ID,pData));
	if(pData.IsWrite)
		return;//如果是等待的消息 不需要修改数据
	//发送到客户端去
	MsgAddCampBattleDataAck msg;
	msg.Result = true;
	msg.add = pData;
	GameGuild * pSrcGuild = theGameGuildManager.GetGuild(pData.SrcGuildID);
	GameGuild * pDestGuild = theGameGuildManager.GetGuild(pData.DestGuildID);
	if(pSrcGuild)
		pSrcGuild->SendMessageToGuild(&msg,GuildDefine::InitID,0,false);
	if(pDestGuild)
		pDestGuild->SendMessageToGuild(&msg,GuildDefine::InitID,0,false);
	//添加到管理器里面去
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return;
	pManager->AddGameGuildGeneralBattleOnceInfo(pData.ID,pData.MapID,pData.SrcGuildID,pData.DestGuildID,pData.BeginTime,pData.MoneySum,pData.GuildMoneySum,pData.GuildMissionSum);
}
template<>
bool GameCampBattleDataManager::IsExitesNeedWriteData(unsigned int GuildID)
{
	if(GuildCampBattleDataMap.empty())
		return false;
	std::map<unsigned int,GameBattleDefine::GuildCampBattle>::iterator Iter = GuildCampBattleDataMap.begin();
	for(;Iter !=GuildCampBattleDataMap.end();++Iter)
	{
		if(GuildID == Iter->second.DestGuildID && Iter->second.IsWrite)
			return true;//有等待消息
	}
	return false;
}
template<>
bool GameCampBattleDataManager::IsCanAddGuildBattleData(unsigned int GuildID,__int64 BeginTime,unsigned int Type)
{
	if(GuildCampBattleDataMap.empty())
		return true;
	std::map<unsigned int,GameBattleDefine::GuildCampBattle>::iterator Iter = GuildCampBattleDataMap.begin();
	for(;Iter !=GuildCampBattleDataMap.end();++Iter)
	{
		if(Iter->second.SrcGuildID == GuildID || GuildID == Iter->second.DestGuildID)
		{
			//判断时间的差距
			__int64 diff = Iter->second.BeginTime - BeginTime;
			if(diff == 0 && Iter->second.IsWrite)
				continue;
			if(diff <0)
				diff = diff*-1;
			if(diff <= theGameBattleControl.GetMapMaxTimeByType(Type)*60)
				return false;
		}
	}
	return true;
}