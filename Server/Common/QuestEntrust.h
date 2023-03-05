#pragma once
//任务委托
#include "Singleton.h"
#include "GameTimer.h"
#include "RunStatus.h"
#include "QuestEntrustDefine.h"
#include "QuestEntrustConfig.h"
template< class T >
class QuestEntrust: public ISingletion<QuestEntrust< T >>
{
public:
	QuestEntrust();
	~QuestEntrust(){}

	void RunUpdate( unsigned int nCurrentTime );
	void StartLoadTimer();
	void StopLoadTimer();
	bool GetLoadSuccess() const;
	void SetLoadSuccess(bool bValue);
	void SetNewQuestEntrustID();
	void SendQuestEntrustData( unsigned int nServerID );
	void AddQuestEntrust(QuestEntrustStates& info);
	void DelQuestEntrust(unsigned int ID);
	void JoinQuestEntrust(QuestEntrustStates& info);
	void CanelQuestEntrust(QuestEntrustStates& info);

	void LoadQuestEntrust(QuestEntrustStates& info);
	void EraseQuestEntrust(unsigned int ID);
	void ChangeQuestEntrust(QuestEntrustStates& info);

	QuestEntrustConfig& GetConfig() {return m_Config;}
	QuestEntrustStates* GetQuestEntrust(unsigned int ID);
	unsigned int IsExitesJoinQuestEntrust(unsigned int PlayerID);
	bool IsExitesQuestEntrust(unsigned int PlayerID,unsigned int QuestID,vector<unsigned int>& vec);

	void StartSaveTimer( unsigned int nCurrentTime ); 
    bool IsSaveTimerStart();

	void AddIDInList(unsigned int ID){m_DBAdd.insert(std::set<unsigned int>::value_type(ID));}
	void DelIDInList(unsigned int ID){m_DBDel.insert(std::set<unsigned int>::value_type(ID));}
	void UpdateIDInList(unsigned int ID){m_DBUpdate.insert(std::set<unsigned int>::value_type(ID));}

	void SaveToDatabase();
private:
	void ProcessLoadQuestEntrustData( unsigned int nCurrentTime );//CenterServer 专用
	unsigned int GetNewQuestEntrustID();
	
private:
	std::map<unsigned int,QuestEntrustStates> QuestEntrustMap;//当前全部委托的集合
	GameTimerEx m_xUpdateTimer;    // 更新定时器
    bool m_bLoadSuccess;            // 是否加载成功
	bool m_bBeginLoad;
	unsigned int	m_NewQuestEntrustID;
	unsigned int	nRecordTime;
	QuestEntrustConfig m_Config;

	GameTimerEx m_xSaveTimer;
	std::set<unsigned int> m_DBAdd;
	std::set<unsigned int> m_DBDel;
	std::set<unsigned int> m_DBUpdate;
}; 
template< class T >
inline void QuestEntrust< T >::StartSaveTimer( unsigned int nCurrentTime)
{
    m_xSaveTimer.StartTimer( nCurrentTime,QuestEntrustSaveTime);//10分钟保存一次
}

template< class T >
inline bool QuestEntrust< T >::IsSaveTimerStart()
{
    return m_xSaveTimer.IsStart();
}
template< class T >
inline QuestEntrust< T >::QuestEntrust()
{
	m_xUpdateTimer.StartTimer( 1,QuestEntrustUpdateTime);//设置更新时间 一分钟更新一次
	m_NewQuestEntrustID = 1;
	nRecordTime = 0;
	m_bLoadSuccess= false;
	m_bBeginLoad = false;
}
template< class T >
inline void QuestEntrust< T >::SetNewQuestEntrustID()
{
	if(QuestEntrustMap.empty())
		m_NewQuestEntrustID = 1;
	else
	{
		std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustMap.begin();
		for(;Iter != QuestEntrustMap.end();++Iter)
		{
			if(Iter->first >= m_NewQuestEntrustID)
				m_NewQuestEntrustID = Iter->first;
		}
		++m_NewQuestEntrustID;
	}
}

template< class T >
unsigned int QuestEntrust< T >::GetNewQuestEntrustID()
{
	return m_NewQuestEntrustID++;
}
template< class T >
inline bool QuestEntrust< T >::GetLoadSuccess() const
{
    return m_bLoadSuccess;
}
template< class T >
inline void QuestEntrust< T >::SetLoadSuccess( bool bValue )
{
    m_bLoadSuccess = bValue;
	if (bValue)
	{
		theRunStatus.SetLoadSuccess(RunStatusDefine::LoadQuestEntrustSuccess);
	}
}
template< class T >
inline void QuestEntrust< T >::LoadQuestEntrust(QuestEntrustStates& info)
{
	if(QuestEntrustMap.count(info.ID) == 1)
		return;
	QuestEntrustMap.insert(std::map<unsigned int,QuestEntrustStates>::value_type(info.ID,info));
}
template< class T >
inline void QuestEntrust< T >::EraseQuestEntrust(unsigned int ID)
{
	if(QuestEntrustMap.count(ID) == 0)
		return;
	QuestEntrustMap.erase(ID);
}
template< class T >
inline void QuestEntrust< T >::ChangeQuestEntrust(QuestEntrustStates& info)
{
	EraseQuestEntrust(info.ID);
	LoadQuestEntrust(info);
}
template< class T >
inline QuestEntrustStates* QuestEntrust< T >::GetQuestEntrust(unsigned int ID)
{
	if(QuestEntrustMap.count(ID) == 1)
		return &QuestEntrustMap[ID];
	else
		return NULL;
}
template< class T >
inline unsigned int QuestEntrust< T >::IsExitesJoinQuestEntrust(unsigned int PlayerID)
{
	std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustMap.begin();
	for(;Iter !=QuestEntrustMap.end();++Iter)
	{
		if(Iter->second.DestPlayerID == PlayerID && !Iter->second.IsSecc)
			return Iter->first;
	}
	return 0;
}
template< class T >
inline bool QuestEntrust< T >::IsExitesQuestEntrust(unsigned int PlayerID,unsigned int QuestID,vector<unsigned int>& vec)
{
	vec.clear();
	std::map<unsigned int,QuestEntrustStates>::iterator Iter = QuestEntrustMap.begin();
	for(;Iter !=QuestEntrustMap.end();++Iter)
	{
		if(Iter->second.SrcPlayerID == PlayerID && Iter->second.SrcQuestID == QuestID)
		{
			vec.push_back(Iter->first);
		}
	}
	return !vec.empty();
}
class ClientPeer;
typedef QuestEntrust<ClientPeer> CenterQuestEntrustManager;
#define theCenterQuestEntrustManager CenterQuestEntrustManager::Instance()
class GamePlayer;
typedef QuestEntrust<GamePlayer> GameQuestEntrustManager;
#define theGameQuestEntrustManager GameQuestEntrustManager::Instance()