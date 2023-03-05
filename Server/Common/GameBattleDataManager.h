#pragma once
#include "Singleton.h"
#include "GameBattleDefine.h"
#include "GameTimer.h"
#include "RunStatus.h"
#include <map>
template< class T >
class CampBattleDataManager: public ISingletion<CampBattleDataManager< T >>
{
public:
	CampBattleDataManager();
	~CampBattleDataManager(){}

	void RunUpdate( unsigned int nCurrentTime );
	void LoadAddDataByDataBase();
	void SendDataToServer(unsigned int nServerID );

	void DedGuildBattleData(unsigned int ID);
	void AddGuildBattleData(GameBattleDefine::GuildCampBattle& pData);

	bool IsExitesNeedWriteData(unsigned int GuildID);
	bool IsCanAddGuildBattleData(unsigned int GuildID,__int64 BeginTime,unsigned int Type);
	bool IsExitesGuildCampBattleData(unsigned int ID);
	bool IsExitesGuildCampBattle(unsigned int GuildID);

	void InsertGuildBattleData(GameBattleDefine::GuildCampBattle& pData);
	void SetNewID();

	void SetLoadSecc();

	GameBattleDefine::GuildCampBattle* GetWriteInfoByDestID(unsigned int DestGuildID);
private:
	void EraseGuildBattleData(unsigned int ID);
	
	unsigned int GetNewID();
private:
	std::map<unsigned int,GameBattleDefine::GuildCampBattle> GuildCampBattleDataMap;
	GameTimerEx m_xUpdateTimer;
	bool IsLoadSecc;
	unsigned int	m_NewID;
	std::map<unsigned int,__int64> WriteTimeInfoMap;
};
template< class T >
inline CampBattleDataManager< T >::CampBattleDataManager()
{
	m_xUpdateTimer.StartTimer( 1,60000);
	m_NewID = 1;
	IsLoadSecc = false;
}
//template< class T >
//inline bool CampBattleDataManager< T >::IsCanAddGuildBattleData(unsigned int GuildID,__int64 BeginTime)
//{
//	if(GuildCampBattleDataMap.empty())
//		return true;
//	std::map<unsigned int,GameBattleDefine::GuildCampBattle>::iterator Iter = GuildCampBattleDataMap.begin();
//	for(;Iter !=GuildCampBattleDataMap.end();++Iter)
//	{
//		if(Iter->second.SrcGuildID == GuildID || GuildID == Iter->second.DestGuildID)
//		{
//			//ÅÐ¶ÏÊ±¼äµÄ²î¾à
//			__int64 diff = Iter->second.BeginTime - BeginTime;
//			if(diff <0)
//				diff = diff*-1;
//			if(diff <= GameBattleDefine::CampBattleMaxLastTime)
//				return false;
//		}
//	}
//	return true;
//}
template< class T >
bool CampBattleDataManager< T >::IsExitesGuildCampBattle(unsigned int GuildID)
{
	if(GuildCampBattleDataMap.empty())
		return false;
	else
	{
		std::map<unsigned int,GameBattleDefine::GuildCampBattle>::iterator Iter = GuildCampBattleDataMap.begin();
		for(;Iter != GuildCampBattleDataMap.end();++Iter)
		{
			if(Iter->second.DestGuildID == GuildID || Iter->second.SrcGuildID == GuildID)
				return true;
		}
		return false;
	}
}
template< class T >
inline GameBattleDefine::GuildCampBattle* CampBattleDataManager< T >::GetWriteInfoByDestID(unsigned int DestGuildID)
{
	if(GuildCampBattleDataMap.empty())
		return NULL;
	else
	{
		std::map<unsigned int,GameBattleDefine::GuildCampBattle>::iterator Iter = GuildCampBattleDataMap.begin();
		for(;Iter != GuildCampBattleDataMap.end();++Iter)
		{
			if(Iter->second.DestGuildID == DestGuildID && Iter->second.IsWrite)
				return &Iter->second;
		}
		return NULL;
	}
} 
template< class T>
inline void CampBattleDataManager< T >::SetLoadSecc()
{
	IsLoadSecc = true;
	if (IsLoadSecc)
	{
		theRunStatus.SetLoadSuccess(RunStatusDefine::LoadCampBattleSuccess);
	}
}
template< class T >
inline void CampBattleDataManager< T >::SetNewID()
{
	if(GuildCampBattleDataMap.empty())
		m_NewID = 1;
	else
	{
		std::map<unsigned int,GameBattleDefine::GuildCampBattle>::iterator Iter = GuildCampBattleDataMap.begin();
		for(;Iter != GuildCampBattleDataMap.end();++Iter)
		{
			if(Iter->first >= m_NewID)
				m_NewID = Iter->first;
		}
		++m_NewID;
	}
}
template< class T >
unsigned int CampBattleDataManager< T >::GetNewID()
{
	return m_NewID++;
}
template< class T >
void CampBattleDataManager< T >::EraseGuildBattleData(unsigned int ID)
{
	GuildCampBattleDataMap.erase(ID);
}
template< class T >
void CampBattleDataManager< T >::InsertGuildBattleData(GameBattleDefine::GuildCampBattle& pData)
{
	GuildCampBattleDataMap.insert(std::map<unsigned int,GameBattleDefine::GuildCampBattle>::value_type(pData.ID,pData));
}
template< class T >
bool CampBattleDataManager< T >::IsExitesGuildCampBattleData(unsigned int ID)
{
	return GuildCampBattleDataMap.count(ID) == 1;
}
class ClientPeer;
typedef CampBattleDataManager<ClientPeer> CenterCampBattleDataManager;
#define theCenterCampBattleDataManager CenterCampBattleDataManager::Instance()
class GamePlayer;
typedef CampBattleDataManager<GamePlayer> GameCampBattleDataManager;
#define theGameCampBattleDataManager GameCampBattleDataManager::Instance()