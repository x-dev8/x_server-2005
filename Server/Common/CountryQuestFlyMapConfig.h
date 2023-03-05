#pragma once
#include "CountryDefine.h"
struct QuestFlyInfo
{
	unsigned int MapID;
	float x;
	float y;
	float z;
};
struct CountryFlyInfo
{
	unsigned int CountryID;
	QuestFlyInfo Quests[CountryDefine::QuestType_Max];
};
class CountryQuestFlyMapConfig
{
public:
	CountryQuestFlyMapConfig();
	~CountryQuestFlyMapConfig();

	static CountryQuestFlyMapConfig& Instance()
    {
        static CountryQuestFlyMapConfig s_xConfig;
        return s_xConfig;
    }

	bool LoadConfigFile(const char* FilePath);
	void GetQuetMapInfo(unsigned int CountryID,unsigned int QuestType,unsigned int & MapID,float & x,float & y,float & z);
private:
	CountryFlyInfo	m_Configs[CountryDefine::Country_Max];
};
#define theCountryQuestFlyMapConfig CountryQuestFlyMapConfig::Instance()