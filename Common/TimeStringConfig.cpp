#include "TimeStringConfig.h"
#include "RapidXml/MeRapidXml.h"

TimeStringConfig::TimeStringConfig()
{
	m_mapString.clear();
}

TimeStringConfig::~TimeStringConfig()
{
	m_mapString.clear();
}

bool TimeStringConfig::LoadTimeStringConfig( const char* pszConfig )
{
	if (!pszConfig || *pszConfig == 0)
		return false;

	m_mapString.clear();

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(pszConfig))
		return false;
	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
		return false;

	MeXmlElement* pElement = pRoot->FirstChildElement("Strings");
	if (!pElement)
		return false;
	MeXmlElement* pString = pElement->FirstChildElement("String");

	while (pString)
	{
		int nId = -1;
		if (!pString->Attribute("Id", &nId))
			return false;

		std::string strValue(pString->Attribute("Value"));

		m_mapString.insert(make_pair(nId, strValue));

		pString = pString->NextSiblingElement();
	}

	return true;
}

const char* TimeStringConfig::GetString(const int nId)
{
	if (nId < 0)
		return "";

	mapiter iter = m_mapString.find(nId);

	if (iter != m_mapString.end())
	{
		return (*iter).second.c_str();
	}

	return "";
}

//TimeStringManager
TimeStringManager::TimeStringManager()
{
	m_TimeData.clear();
}

TimeStringManager::~TimeStringManager()
{
	m_TimeData.clear();
}

void TimeStringManager::AddTimeData(uint32 time, uint32 id, uint32 starttime)
{
	if (time == 0)
		return;

	TimeData data;
	data.nTime = time;
	data.nStringId = id;
	data.nStartTime = starttime;

	m_TimeData.push_back(data);
}