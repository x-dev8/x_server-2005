#include "RewardProfessionItemConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "application_config.h"
#include "GlobalDef.h"


bool RewardProfessionItemConfig::LoadRewardProfessionItemConfig(const char *szFile)
{
    if (szFile == NULL || *szFile == 0)
    { return false;	}

    MeXmlDocument xMeXml;
    if (!xMeXml.LoadFile(szFile, 1))
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
    if (pRoot == NULL )
    { return false; }

    MeXmlElement* pItems = pRoot->FirstChildElement("Items");
    if (pItems == NULL) 
    { return false; }

    int nValue = 0;
    int nIndex = 0;
    MeXmlElement* pItem = NULL;

    //战士
    MeXmlElement* pWarrior = pItems->FirstChildElement("Warrior");
    if (pWarrior == NULL) 
    { return false; }

    nIndex = 0;
    pItem = pWarrior->FirstChildElement("Item");
    while(pItem != NULL)
    {
        if (nIndex >= EConstDefine_RewardItemMaxSize)
        { break; }

        pItem->Attribute("Id", &nValue);

        m_nProfessionItem[EArmType_Warrior][nIndex] = nValue;

        ++nIndex;
        pItem = pItem->NextSiblingElement();
    }

    //法师
    MeXmlElement* pMage = pItems->FirstChildElement("Mage");
    if (pMage == NULL) 
    { return false; }

    nIndex = 0;
    pItem = pMage->FirstChildElement("Item");
    while(pItem != NULL)
    {
        if (nIndex >= EConstDefine_RewardItemMaxSize)
        { break; }

        pItem->Attribute("Id", &nValue);

        m_nProfessionItem[EArmType_Mage][nIndex] = nValue;

        ++nIndex;
        pItem = pItem->NextSiblingElement();
    }

    //道士
    MeXmlElement* pTaoist = pItems->FirstChildElement("Taoist");
    if (pTaoist == NULL) 
    { return false; }

    nIndex = 0;
    pItem = pTaoist->FirstChildElement("Item");
    while(pItem != NULL)
    {
        if (nIndex >= EConstDefine_RewardItemMaxSize)
        { break; }

        pItem->Attribute("Id", &nValue);

        m_nProfessionItem[EArmType_Taoist][nIndex] = nValue;

        ++nIndex;
        pItem = pItem->NextSiblingElement();
    }

    //刺客
    MeXmlElement* pAssassin = pItems->FirstChildElement("Assassin");
    if (pAssassin == NULL) 
    { return false; }

    nIndex = 0;
    pItem = pAssassin->FirstChildElement("Item");
    while(pItem != NULL)
    {
        if (nIndex >= EConstDefine_RewardItemMaxSize)
        { break; }

        pItem->Attribute("Id", &nValue);

        m_nProfessionItem[EArmType_Assassin][nIndex] = nValue;

        ++nIndex;
        pItem = pItem->NextSiblingElement();
    }
     
    //猎人
    MeXmlElement* pHunter = pItems->FirstChildElement("Hunter");
    if (pHunter == NULL) 
    { return false; }

    nIndex = 0;
    pItem = pHunter->FirstChildElement("Item");
    while(pItem != NULL)
    {
        if (nIndex >= EConstDefine_RewardItemMaxSize)
        { break; }

        pItem->Attribute("Id", &nValue);

        m_nProfessionItem[EArmType_Hunter][nIndex] = nValue;

        ++nIndex;
        pItem = pItem->NextSiblingElement();
    }

    //火枪手
    MeXmlElement* pSniper = pItems->FirstChildElement("Sniper");
    if (pSniper == NULL) 
    { return false; }

    nIndex = 0;
    pItem = pSniper->FirstChildElement("Item");
    while(pItem != NULL)
    {
        if (nIndex >= EConstDefine_RewardItemMaxSize)
        { break; }

        pItem->Attribute("Id", &nValue);

        m_nProfessionItem[EArmType_Sniper][nIndex] = nValue;

        ++nIndex;
        pItem = pItem->NextSiblingElement();
    }
 
    return true;
}
