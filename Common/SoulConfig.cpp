#include "SoulConfig.h"
#include "RapidXml/MeRapidXml.h"

SoulConfig::SoulConfig()
{
	m_vecSoul.clear();
}

SoulConfig::~SoulConfig()
{
	m_vecSoul.clear();
}

bool SoulConfig::LoadSoulConfig( const char* pszConfig )
{
	if (!pszConfig || *pszConfig == 0)
		return false;

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(pszConfig))
		return false;
	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
		return false;

	MeXmlElement* pSouls = pRoot->FirstChildElement("Souls");
	if ( !pSouls )
		return false;

	MeXmlElement* pSoul = pSouls->FirstChildElement("Soul");

	while ( pSoul )
	{
		SData data;

		int nLevel = 0;
		pSoul->Attribute("Level", &nLevel);
		data.nLevel = nLevel;

		int nCount = 0;
		if ( nCount < ED_Max_Material )
		{
			pSoul->Attribute("Material1", &data.material[nCount].nId);
			pSoul->Attribute("Count1", &data.material[nCount].nNum);

			nCount++;
		}

		if ( nCount < ED_Max_Material )
		{
			pSoul->Attribute("Material2", &data.material[nCount].nId);
			pSoul->Attribute("Count2", &data.material[nCount].nNum);

			nCount++;
		}

		int nMoney = 0;
		pSoul->Attribute("NeedMoney", &nMoney);
		data.nMoney = nMoney;

		m_vecSoul.push_back( data );

		pSoul = pSoul->NextSiblingElement();
	}

	return true;
}

SoulConfig::SData* SoulConfig::GetLevelData( int nlevel )
{
	if ( nlevel <= 0 )
		return NULL;

	for ( int i = 0 ; i < m_vecSoul.size(); i++ )
	{
		if ( m_vecSoul[i].nLevel == nlevel )
			return &m_vecSoul[i];
	}

	return NULL;
}