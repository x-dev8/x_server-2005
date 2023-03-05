#ifndef _HUNTINGQUESTCONFIG_
#define _HUNTINGQUESTCONFIG_

#include "MeRTLibs.h"

class HuntingQuestConfig
{
public:
	struct SData
	{
		SData()
		{
			nId = 0;
			nQuality = 0;
			nAdviseLevel = 0;
		}

		int nId;
		int nQuality;
		int nAdviseLevel;
	};

	typedef std::vector< SData > BaseVec;
	typedef std::vector< BaseVec > TypeVec;
	typedef std::map< int, TypeVec > LevelMap;

	typedef std::vector< SData > GoldTypeVec;
	typedef std::map< int, GoldTypeVec > GoldLevelMap;

	typedef std::vector< SData > AllQuestVec;

	HuntingQuestConfig();
	virtual ~HuntingQuestConfig();

	bool LoadHuntingQuestConfig( const char* pszConfig );

	int GetFreshGold() { return nReFreshGold; }
	int GetFreshMoney() { return nReFreshMoney; }
	int GetFreshTime() { return nReFreshTime; }
	float GetGoldProbability() { return fProbability; }

	AllQuestVec& GetAllQuest() { return vecAllQuest; }
	GoldLevelMap& GetGoldLevelMap() { return mapGoldLevel; }
	LevelMap& GetLevelMap() { return mapLevel; }

	BaseVec& GetLevelGoldQuest( int level, int Country );
	TypeVec& GetLevelTypeQuest( int level, int Country );

	SData* GetBaseDataById( int nId );

	static HuntingQuestConfig& Instance()
	{
		static HuntingQuestConfig s_xHuntingQuest;
		return s_xHuntingQuest;
	}

private:
	int nReFreshGold;
	int nReFreshMoney;
	int nReFreshTime;
	float fProbability;

	BaseVec vecBase;
	TypeVec vecType;
	LevelMap mapLevel;

	GoldTypeVec vecGoldType;
	GoldLevelMap mapGoldLevel;

	AllQuestVec vecAllQuest;

	BaseVec vecLevelGoldQuest; //当前等级能接的金色任务
	TypeVec vecLevelTypeQuest; //当前等级能接的类型任务
};

#define theHuntingQuestConfig HuntingQuestConfig::Instance()
#endif