#include "GuildMissionConfig.h"
#include "RapidXml/MeRapidXml.h"
GuildMissionConfig::GuildMissionConfig()
{
	m_Mission.clear();
}
GuildMissionConfig::~GuildMissionConfig()
{
	
}
bool GuildMissionConfig::LoadConfigFile(const char* FilePath)
{
	//¶ÁÈ¡ÅäÖÃÎÄ¼þ
	MeXmlDocument mKwameXmlDoc;
	if (!mKwameXmlDoc.LoadFile(FilePath)) return false;
	MeXmlElement* pRoot = mKwameXmlDoc.FirstChildElement("guild");
	if (pRoot->Attribute("InitValue",&m_InitMission) == NULL)
		return false;
	if(pRoot != NULL)
	{
		MeXmlElement* pInfo = pRoot->FirstChildElement("info");
		while (pInfo != NULL)
		{
			int Level =0;
			if (pInfo->Attribute("Level",&Level) == NULL)
				return false;
			
			int Value = 0;
			if (pInfo->Attribute("Value",&Value) == NULL)
				return false;

			m_Mission.insert(std::map<int,int>::value_type(Level,Value));

			pInfo = pInfo->NextSiblingElement("info");
		}
	}
	return true;
}
int	GuildMissionConfig::GetMissionValue(int GuildLevel)
{
	std::map<int,int>::iterator Iter = m_Mission.find(GuildLevel);
	if(Iter == m_Mission.end())
		return -1;
	else
		return Iter->second;
}