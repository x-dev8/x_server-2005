#include "LevelLimitConfig.h"
#include "Tinyxml/tinyxml.h"
#include "ResourcePath.h"

CLevelLimitConfig::CLevelLimitConfig()
{
	ClearData();
}

CLevelLimitConfig::~CLevelLimitConfig()
{
	ClearData();
}

void CLevelLimitConfig::ClearData()
{
	mapLevelLimitConfig::iterator itr = _mapLevelLimitConfig.begin();
	while(itr != _mapLevelLimitConfig.end())
	{
		if (itr->second)
		{
			delete itr->second;			
		}
		itr++;
	}

	_mapLevelLimitConfig.clear();
}

bool CLevelLimitConfig::LoadLevelLimitConfig()
{
	TiXmlDocument doc;
	if ( !doc.LoadFile( CENTERSERVER_LEVELLIMIT_CONFIG ) )
	{ return false; }
	TiXmlElement* pProject = doc.FirstChildElement("Project");
	if ( !pProject )
	{ return false; }

	TiXmlElement* pLimits = pProject->FirstChildElement("Limits");
	if ( !pLimits )
	{ return false; }

	int nValue = 0;
	TiXmlElement* pLevel = pLimits->FirstChildElement("Level");
	while(pLevel)
	{
		pLevel->Attribute("value",&nValue);
		if (nValue <= 0)
		{
			pLevel = pLevel->NextSiblingElement();
			continue;
		}
		SLevelLimitConfig* sllc = new SLevelLimitConfig;
		sllc->level = nValue;
		pLevel->Attribute("lastmax",&nValue);
		sllc->time_max = nValue;
		pLevel->Attribute("lastmin",&nValue);
		sllc->time_min = nValue;
		pLevel->Attribute("setupcount",&nValue);
		sllc->setup_min_count = nValue;
		pLevel->Attribute("percount",&nValue);
		sllc->per_count = nValue;
		pLevel->Attribute("nextlevel",&nValue);
		sllc->next_level = nValue;

		_mapLevelLimitConfig.insert(mapLevelLimitConfig::value_type(sllc->level,sllc));

		pLevel = pLevel->NextSiblingElement();
	}

	return true;
}

SLevelLimitConfig* CLevelLimitConfig::GetLevelLimitConfig(int lv)
{
	if (lv <= 0)
	{
		return NULL;
	}

	mapLevelLimitConfig::iterator itr = _mapLevelLimitConfig.find(lv);
	if (itr != _mapLevelLimitConfig.end())
	{
		return itr->second;
	}

	return NULL;
}

SLevelLimitConfig* CLevelLimitConfig::GetFirstLimitConfig()
{
	if (_mapLevelLimitConfig.size() <= 0)
	{
		return NULL;
	}
	mapLevelLimitConfig::iterator itr = _mapLevelLimitConfig.begin();
	return itr->second;
}