#include "RankAwardConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"
#include "application_config.h"

RankAwardConfig::RankAwardConfig()
{
    m_vecRankAward.clear();
}

RankAwardConfig::~RankAwardConfig()
{

}


bool RankAwardConfig::LoadRankAwardConfig(const char* szFile)
{
    if (szFile == NULL || *szFile == 0)
    { return false;	}

    m_vecRankAward.clear();

    MeXmlDocument xMeXml;
    if (!xMeXml.LoadFile(szFile, 1))
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
    if (pRoot == NULL )
    { return false; }

    MeXmlElement* pRankAwards = pRoot->FirstChildElement("RankAwards");
    if (pRankAwards == NULL) 
    { return false; }
    
    int iValue;

    MeXmlElement* pRankAwardElement = pRankAwards->FirstChildElement("RankAward");
    while (pRankAwardElement != NULL)
    {	
        RankAward award;

        pRankAwardElement->Attribute("Id", &iValue);
        award.nId = iValue;

        pRankAwardElement->Attribute("RankType", &iValue);
        award.nRankType = iValue;

        pRankAwardElement->Attribute("BeginPos", &iValue);
        award.nBeginPos = iValue;

        pRankAwardElement->Attribute("EndPos", &iValue);
        award.nEndPos = iValue;

        pRankAwardElement->Attribute("TitleId", &iValue);
        award.nTitleId = iValue;

        m_vecRankAward.push_back(award);

        //next
        pRankAwardElement = pRankAwardElement->NextSiblingElement();
    }

    return true;
}