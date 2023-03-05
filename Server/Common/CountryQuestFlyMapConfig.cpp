#include "CountryQuestFlyMapConfig.h"
#include "RapidXml/MeRapidXml.h"
CountryQuestFlyMapConfig::CountryQuestFlyMapConfig()
{

}
CountryQuestFlyMapConfig::~CountryQuestFlyMapConfig()
{
	
}
bool CountryQuestFlyMapConfig::LoadConfigFile(const char* FilePath)
{
	//加载指定的配置文件
	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(FilePath)) return false;
	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("Project");
	if(pRoot != NULL)
	{
		MeXmlElement* pCountry = pRoot->FirstChildElement("country");
		while (pCountry != NULL)
		{
			CountryFlyInfo CountryInfo;
			int CountryID = 0;
			if (pCountry->Attribute("id",&CountryID) == NULL) 
				return false;
			CountryInfo.CountryID = CountryID;
			if(CountryInfo.CountryID <= CountryDefine::Country_Init || CountryInfo.CountryID>= CountryDefine::Country_Max)
				return false;
			MeXmlElement* pQuest = pCountry->FirstChildElement("Quest");		
			while (pQuest != NULL)
			{
				QuestFlyInfo QuestInfo;
				
				int type = 0;
				if (pQuest->Attribute("type",&type) == NULL) 
					return false;

				if(type>=CountryDefine::QuestType_Max || type<=CountryDefine::QuestType_None)
					return false;
				
				int MapID = 0;
				if (pQuest->Attribute("mapid",&MapID) == NULL) 
					return false;

				QuestInfo.MapID = MapID;

				if (pQuest->Attribute("x",&QuestInfo.x) == NULL) 
					return false;

				if (pQuest->Attribute("y",&QuestInfo.y) == NULL) 
					return false;

				if (pQuest->Attribute("z",&QuestInfo.z) == NULL) 
					return false;

				CountryInfo.Quests[type] = QuestInfo;

				pQuest = pQuest->NextSiblingElement("Quest");
			}
			m_Configs[CountryInfo.CountryID] = CountryInfo;
			pCountry = pCountry->NextSiblingElement("country");
		}	
	}
	return true;
}
void CountryQuestFlyMapConfig::GetQuetMapInfo(unsigned int CountryID,unsigned int QuestType,unsigned int & MapID,float & x,float & y,float & z)
{
	if(CountryID <= CountryDefine::Country_Init || CountryID>= CountryDefine::Country_Max)
		return;
	if(QuestType>=CountryDefine::QuestType_Max || QuestType<=CountryDefine::QuestType_None)
		return;
	QuestFlyInfo info = m_Configs[CountryID].Quests[QuestType];
	MapID = info.MapID;
	x=info.x;
	y=info.y;
	z=info.z;
}