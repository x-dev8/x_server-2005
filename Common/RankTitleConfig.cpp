#include "RankTitleConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"

RankTitleConfig::RankTitleConfig()
{
	m_nShowCount = 0;
	m_vecRankTitle.clear();
}

RankTitleConfig::~RankTitleConfig()
{
	m_vecRankTitle.clear();
}

bool RankTitleConfig::LoadRankTitleConfig( const char* pszConfig )
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

	int nShowCount = 0;
	pTitles->Attribute("ShowCount", &nShowCount);
	m_nShowCount = nShowCount;

	MeXmlElement* pTitle = pTitles->FirstChildElement("Title");

	while (pTitle)
	{
		SData data;

		int nId = -1;
		if (!pTitle->Attribute("Id", &nId))
			return false;
		data.nId = nId;

		data.strName = pTitle->Attribute("Name");
		data.strDescription = pTitle->Attribute("Description");

		int nCurSalary = 0;
		pTitle->Attribute("CurrentSalary", &nCurSalary);
		data.nCurSalary = nCurSalary;

		int nNeedHonour = 0;
		pTitle->Attribute("NeedHonour", &nNeedHonour);
		data.nNeedHonour = nNeedHonour;

		int nNeedMoney = 0;
		pTitle->Attribute("NeedMoney", &nNeedMoney);
		data.nNeedMoney = nNeedMoney;

		int nBuffId = 0;
		pTitle->Attribute("BuffId", &nBuffId);
		data.nBuffId = nBuffId;

		int nBuffLevel = 0;
		pTitle->Attribute("BuffLevel", &nBuffLevel);
		data.nBuffLevel = nBuffLevel;

		data.strPic = pTitle->Attribute("PicPath");

		int nPicHeight = 0;
		pTitle->Attribute("PicHeight", &nPicHeight);
		data.nPicHeight = nPicHeight;

		int nPicWidth = 0;
		pTitle->Attribute("PicWidth", &nPicWidth);
		data.nPicWidth = nPicWidth;

		m_vecRankTitle.push_back( data );

		pTitle = pTitle->NextSiblingElement();
	}

	if ( m_nShowCount > m_vecRankTitle.size() )
		m_nShowCount = m_vecRankTitle.size();

	return true;
}