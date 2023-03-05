//ƒºæËΩ±¿¯≈‰÷√–≈œ¢
#pragma once
#include "Singleton.h"
#define CHANGECOUNTRYFILEPATH  "..\\Data\\Config\\changecountry.config"
class ChangeCountryConfig
{
public:
	ChangeCountryConfig();
	~ChangeCountryConfig();
	bool LoadConfigFile();
	int  GetCD(){return CDTime;}
	int  GetMaxLevel(){return MaxLevel;}
	int  GetMinLevel(){return MinLevel;}
	int	 GetQuestIndex(){return QuestIndex;}
	int  GetQuestValue(){return QuestValue;}
	int  GetItemID(int CountryID,int TargetCountryID,int WeakCountryID,int StrongthCountryID);
	int  GetItemSum(int CountryID,int TargetCountryID,int WeakCountryID,int StrongthCountryID);

	static ChangeCountryConfig& Instance()
    {
        static ChangeCountryConfig s_xConfig;
        return s_xConfig;
    }
private:
	int 		MinLevel;
	int 		MaxLevel;
	int 		QuestIndex;
	int 		QuestValue;
	int 		CDTime;
	enum CountryChange
	{
		CC_Strongth  = 0,
		CC_Weak      = 1,
		CC_Normal    = 2,
		CC_MAX		  = 3,
	};
	struct CountryChangeItem
	{
		int 	ItemID;
		int 	ItemNum;
	};
	CountryChangeItem	CountryItem[CC_MAX][CC_MAX];
};
#define theChangeCountryConfig ChangeCountryConfig::Instance()