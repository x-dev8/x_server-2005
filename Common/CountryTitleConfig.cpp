#include "CountryTitleConfig.h"
#include "RapidXml/MeRapidXml.h"

CountryTitleConfig::CountryTitleConfig()
{
	m_mapCountryTitle.clear();
}

CountryTitleConfig::~CountryTitleConfig()
{
	m_mapCountryTitle.clear();
}

void CountryTitleConfig::AddMapData( int nCountry, CountryTitleVector& data )
{
	CountryTitleMapIter iter = m_mapCountryTitle.find( nCountry );
	if ( iter != m_mapCountryTitle.end() )
		return;
	m_mapCountryTitle.insert( std::make_pair( nCountry, data ) );
}

CountryTitleConfig::CountryTitleVector* CountryTitleConfig::GetCountryTitleVec( int nCountryId )
{
	CountryTitleMapIter iter = m_mapCountryTitle.find( nCountryId );
	if ( iter == m_mapCountryTitle.end() )
		return NULL;

	return &(iter->second);
}

bool CountryTitleConfig::LoadCountryTitleConfig( const char* pszConfig )
{
	if (!pszConfig || *pszConfig == 0)
		return false;

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(pszConfig))
		return false;
	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
		return false;
	MeXmlElement* pTitles = pRoot->FirstChildElement("Titles");
	if (!pTitles)
		return false;

	MeXmlElement* pTitle = pTitles->FirstChildElement("Title");
	while ( pTitle )
	{
		int nCountryId = 0;
		if (!pTitle->Attribute("CountryId", &nCountryId))
			return false;

		CountryTitleVector vecTitle;

		MeXmlElement* pTitlePic = pTitle->FirstChildElement("TitlePic");
		while ( pTitlePic )
		{
			SData data;

			int nTitleId = -1;
			if (!pTitlePic->Attribute("TitleId", &nTitleId))
				return false;
			data.nTitleId = nTitleId;

			data.strPic = pTitlePic->Attribute("PicPath");

			int nPicHeight = 0;
			pTitlePic->Attribute("PicHeight", &nPicHeight);
			data.nPicHeight = nPicHeight;

			int nPicWidth = 0;
			pTitlePic->Attribute("PicWidth", &nPicWidth);
			data.nPicWidth = nPicWidth;

			vecTitle.push_back( data );

			pTitlePic = pTitlePic->NextSiblingElement();
		}

		AddMapData( nCountryId, vecTitle );

		pTitle = pTitle->NextSiblingElement();
	}
	return true;
}