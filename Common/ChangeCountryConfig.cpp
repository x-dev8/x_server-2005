#include "ChangeCountryConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "CountryDefine.h"
ChangeCountryConfig::ChangeCountryConfig()
{
	for(int i =0;i<CC_MAX;++i)
	{
		for(int j =0;j<CC_MAX;++j)
		{
			CountryItem[i][j].ItemID = 0;
			CountryItem[i][j].ItemNum = 0;
		}
	}
}
ChangeCountryConfig::~ChangeCountryConfig()
{

}
bool ChangeCountryConfig::LoadConfigFile()
{
	//加载指定配置文件
	MeXmlDocument mKwameXmlDoc;
	if(!mKwameXmlDoc.LoadFile(CHANGECOUNTRYFILEPATH)) return false;
	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("country");
	if(pRoot == NULL)
		return false;
	MeXmlElement* pInfo = pRoot->FirstChildElement("Requirement");
	if(pInfo != NULL)
	{
		if (pInfo->Attribute("MinLevle",&MinLevel) == NULL)
			return false;
		
		if (pInfo->Attribute("MaxLevel",&MaxLevel) == NULL)
			return false;

		if (pInfo->Attribute("QuestIndex",&QuestIndex) == NULL)
			return false;

		if (pInfo->Attribute("QuestValue",&QuestValue) == NULL)
			return false;

		if (pInfo->Attribute("CDTime",&CDTime) == NULL)
			return false;

		//设置数组值为0
		if (pInfo->Attribute("WeakToNormal",&CountryItem[CC_Weak][CC_Normal].ItemID) == NULL)
			return false;
		if (pInfo->Attribute("WeakToNormalItemNum",&CountryItem[CC_Weak][CC_Normal].ItemNum) == NULL)
			return false;

		if (pInfo->Attribute("WeakToStrongth",&CountryItem[CC_Weak][CC_Strongth].ItemID) == NULL)
			return false;
		if (pInfo->Attribute("WeakToStrongthItemNum",&CountryItem[CC_Weak][CC_Strongth].ItemNum) == NULL)
			return false;

		if (pInfo->Attribute("WeakToWeak",&CountryItem[CC_Weak][CC_Weak].ItemID) == NULL)
			return false;
		if (pInfo->Attribute("WeakToWeakItemNum",&CountryItem[CC_Weak][CC_Weak].ItemNum) == NULL)
			return false;

		if (pInfo->Attribute("NormalToStrongth",&CountryItem[CC_Normal][CC_Strongth].ItemID) == NULL)
			return false;
		if (pInfo->Attribute("NormalToStrongthItemNum",&CountryItem[CC_Normal][CC_Strongth].ItemNum) == NULL)
			return false;

		if (pInfo->Attribute("NormalToWeak",&CountryItem[CC_Normal][CC_Weak].ItemID) == NULL)
			return false;
		if (pInfo->Attribute("NormalToWeakItemNum",&CountryItem[CC_Normal][CC_Weak].ItemNum) == NULL)
			return false;

		if (pInfo->Attribute("NormalToNormal",&CountryItem[CC_Normal][CC_Normal].ItemID) == NULL)
			return false;
		if (pInfo->Attribute("NormalToNormalItemNum",&CountryItem[CC_Normal][CC_Normal].ItemNum) == NULL)
			return false;

		if (pInfo->Attribute("StrongthToNormal",&CountryItem[CC_Strongth][CC_Normal].ItemID) == NULL)
			return false;
		if (pInfo->Attribute("StrongthToNormalItemNum",&CountryItem[CC_Strongth][CC_Normal].ItemNum) == NULL)
			return false;

		if (pInfo->Attribute("StrongthToWeak",&CountryItem[CC_Strongth][CC_Weak].ItemID) == NULL)
			return false;
		if (pInfo->Attribute("StrongthToWeakItemNum",&CountryItem[CC_Strongth][CC_Weak].ItemNum) == NULL)
			return false;

		if (pInfo->Attribute("StrongthToStrongth",&CountryItem[CC_Strongth][CC_Strongth].ItemID) == NULL)
			return false;
		if (pInfo->Attribute("StrongthToStrongthItemNum",&CountryItem[CC_Strongth][CC_Strongth].ItemNum) == NULL)
			return false;

		return true;
	}
	return false;
}
int ChangeCountryConfig::GetItemID(int CountryID,int TargetCountryID,int WeakCountryID,int StrongthCountryID)
{
	if(CountryID == CountryDefine::Country_Init || TargetCountryID == CountryDefine::Country_Init)
	{	
		return 0;
	}
	int NowStates = (CountryID == WeakCountryID) ? CC_Weak : (CountryID == StrongthCountryID ? CC_Strongth : CC_Normal);
	int TStates = (TargetCountryID == WeakCountryID) ? CC_Weak : (TargetCountryID == StrongthCountryID ? CC_Strongth : CC_Normal);
	if(NowStates >=CC_MAX || TStates>=CC_MAX)
		return 0;
	return CountryItem[NowStates][TStates].ItemID;
}
int ChangeCountryConfig::GetItemSum(int CountryID,int TargetCountryID,int WeakCountryID,int StrongthCountryID)
{	
	if(CountryID == CountryDefine::Country_Init || TargetCountryID == CountryDefine::Country_Init)
	{	
		return 0;
	}
	int NowStates = (CountryID == WeakCountryID) ? CC_Weak : (CountryID == StrongthCountryID ? CC_Strongth : CC_Normal);
	int TStates = (TargetCountryID == WeakCountryID) ? CC_Weak : (TargetCountryID == StrongthCountryID ? CC_Strongth : CC_Normal);
	if(NowStates >=CC_MAX || TStates>=CC_MAX)
		return 0;
	return CountryItem[NowStates][TStates].ItemNum;
}