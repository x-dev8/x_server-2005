#pragma once
#include <map>
class QuestEntrustConfig
{
public:
	QuestEntrustConfig();
	~QuestEntrustConfig();
	bool LoadQuestEntrustConfig(const char* FilePath);
	unsigned int GetChangeQuestID(unsigned int QuestID);
	unsigned int GetOldQuestID(unsigned int QuestID);
	unsigned int GetQuestMoneySum(unsigned int QuestID);
	unsigned int GetBuffID(){return m_BuffID;}
	unsigned int GetBuffLevel(){return m_BuffLevel;}
	unsigned int GetLastTime(){return m_LastTime;}
private:
	std::map<unsigned int,unsigned int> QuestChangeMap;
	std::map<unsigned int,unsigned int> NewQuestToOldMap;
	std::map<unsigned int,unsigned int> QuestMoneySumMap;
	unsigned int m_BuffID;
	unsigned int m_BuffLevel;
	unsigned int m_LastTime;//接取委托最长的持续时间 到了时间就要结束
};