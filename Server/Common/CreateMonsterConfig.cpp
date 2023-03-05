#include "CreateMonsterConfig.h"
#include "CreateMonsterManager.h"

CreateMonsterConfig::CreateMonsterConfig()
{
	m_vecMonster.clear();
}

CreateMonsterConfig::~CreateMonsterConfig()
{
	m_vecMonster.clear();
}

bool CreateMonsterConfig::LoadCreateMonsterConfig( const char* pszConfig )
{
	if ( !pszConfig || *pszConfig == 0 )
		return false;
	m_vecMonster.clear();

	MeXmlDocument xMeXml;
	if ( !xMeXml.LoadFile( pszConfig ) )
		return false;
	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if ( !pRoot )
		return false;

	MeXmlElement* pMonsters = pRoot->FirstChildElement("Monsters");
	if ( !pMonsters )
		return false;

	MeXmlElement* pMonster = pMonsters->FirstChildElement("Monster");
	while ( pMonster )
	{
		SData data;

		int nYear = -1;
		pMonster->Attribute("Year", &nYear);
		data.nYear = nYear;

		int nMonth = -1;
		pMonster->Attribute("Month", &nMonth);
		data.nMonth = nMonth;

		int nDay = -1;
		pMonster->Attribute("Day", &nDay);
		data.nDay = nDay;

		int nHour = -1;
		pMonster->Attribute("Hour", &nHour);
		data.nHour = nHour;

		int nMinute = -1;
		pMonster->Attribute("Minute", &nMinute);
		data.nMinute = nMinute;

		int nWeek = -1;
		pMonster->Attribute("Week", &nWeek);
		data.nWeek = nWeek + 1;

		int nMonsterId = -1;
		pMonster->Attribute("MonsterId", &nMonsterId);
		data.nMonsterId = nMonsterId;

		int nMapId = -1;
		pMonster->Attribute("MapId", &nMapId);
		data.nMapId = nMapId;

		int nX = -1;
		pMonster->Attribute("X", &nX);
		data.nX = nX;

		int nY = -1;
		pMonster->Attribute("Y", &nY);
		data.nY = nY;

		int nCount = 0;
		pMonster->Attribute("Count", &nCount);
		data.nCount = nCount;

		int nIsOnly = 1;
		pMonster->Attribute("IsOnly", &nIsOnly);
		if ( nIsOnly == 1 )
			data.bIsOnly = true;
		else
			data.bIsOnly = false;

		data.strSay = pMonster->Attribute("BroadCast");

		m_vecMonster.push_back( data );

		pMonster = pMonster->NextSiblingElement();
	}

	theCreateMonsterManager.UpdataData( m_vecMonster );

	return true;
}