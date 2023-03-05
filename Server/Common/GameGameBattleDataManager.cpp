#include "GameBattleDataManager.h"
#include "Configure.h"
#include "GameBattleControl.h"
#include "GameGuildGeneralBattleManager.h"
#include "GameGuildGeneralBattle.h"
#include "ShareData.h"
template<>
void GameCampBattleDataManager::RunUpdate( unsigned int nCurrentTime )
{
	//ѭ����������ʱ�� ��ʱ�䵽�˵Ļ� ��ʼ����ս����������ս����״̬
	if(GuildCampBattleDataMap.empty())
		return;
	std::map<unsigned int,GameBattleDefine::GuildCampBattle>::iterator Iter = GuildCampBattleDataMap.begin();
	for(;Iter != GuildCampBattleDataMap.end(); ++Iter)
	{
		if ( !g_Cfg.IsMapRun( Iter->second.MapID ) )
			continue;
		//1.�ж��Ƿ��˿�ս��ʱ�� ���˵Ļ� ���Ǵ���һ��ս�������� ���뵽ս����Control����ȥ ��������ս����״̬Ϊ��ʼ����״̬

		//2.ս�������� ����ɾ������

	}
}
template<>
void GameCampBattleDataManager::LoadAddDataByDataBase()
{

}
template<>
void GameCampBattleDataManager::SendDataToServer(unsigned int nServerID )
{
	//��ָ�������Լս��Ϣ���͵��ͻ���ȥ
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
	//ȡ������Լս
	//1.�ж������Ƿ����
	if(GuildCampBattleDataMap.count(ID) != 1)
		return;
	//2.ɾ������
	//��������ͻ���ȥ
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
		//��������ս��
		pManager->ProcessChangeStatus(ID,GameBattleDefine::StatusEnd);//��ս��ת��������״̬
	}
}
template<>
void GameCampBattleDataManager::AddGuildBattleData(GameBattleDefine::GuildCampBattle& pData)
{
	//��������Լս
	//1.���뵽��������ȥ
	if(GuildCampBattleDataMap.count(pData.ID) != 0)
		GuildCampBattleDataMap.erase(pData.ID);
	GuildCampBattleDataMap.insert(std::map<unsigned int,GameBattleDefine::GuildCampBattle>::value_type(pData.ID,pData));
	if(pData.IsWrite)
		return;//����ǵȴ�����Ϣ ����Ҫ�޸�����
	//���͵��ͻ���ȥ
	MsgAddCampBattleDataAck msg;
	msg.Result = true;
	msg.add = pData;
	GameGuild * pSrcGuild = theGameGuildManager.GetGuild(pData.SrcGuildID);
	GameGuild * pDestGuild = theGameGuildManager.GetGuild(pData.DestGuildID);
	if(pSrcGuild)
		pSrcGuild->SendMessageToGuild(&msg,GuildDefine::InitID,0,false);
	if(pDestGuild)
		pDestGuild->SendMessageToGuild(&msg,GuildDefine::InitID,0,false);
	//��ӵ�����������ȥ
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
			return true;//�еȴ���Ϣ
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
			//�ж�ʱ��Ĳ��
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