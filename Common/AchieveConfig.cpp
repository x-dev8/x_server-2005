#include "AchieveConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"
#include "application_config.h"
#ifndef _CLIENT_
#include "ScriptMgr.h"
#endif //_CLIENT_
#include "GlobalDef.h"

AchieveConfig::AchieveConfig()
{
    m_vecAchieve.clear();
    m_vecObserver.clear();
}

AchieveConfig::~AchieveConfig()
{

}


bool AchieveConfig::LoadAchieveConfig(const char* szFile)
{
    if (szFile == NULL || *szFile == 0)
    { return false;	}

    m_vecAchieve.clear();
    m_vecObserver.clear();

    m_vecAchieve.resize ( MAX_ACHIVEVMENT_COUNT );
    m_vecObserver.resize( More_iMaxAchieveVars  );

    MeXmlDocument xMeXml;
    if (!xMeXml.LoadFile(szFile, 1))
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
    if (pRoot == NULL )
    { return false; }

    //////////////////////////////////////////////////////////////////////////
    //  加载成就
    MeXmlElement* pAchievements = pRoot->FirstChildElement("Achievements");
    if (pAchievements == NULL) 
    { return false; }

    int iValue;

    MeXmlElement* pAchieveElement = pAchievements->FirstChildElement("Achieve");
    while (pAchieveElement != NULL)
    {	
        Achieve xAchieve;

        pAchieveElement->Attribute("Id", &iValue);
        xAchieve.nId = iValue;

        pAchieveElement->Attribute("Type", &iValue);
        xAchieve.nType = iValue;

        pAchieveElement->Attribute("SubType", &iValue);
        xAchieve.nSubType = iValue;

        Common::_tstring strSubName;
        strSubName.fromUTF8( pAchieveElement->Attribute("SubName") );
        xAchieve.strSubName = strSubName;

        Common::_tstring strName;
        strName.fromUTF8( pAchieveElement->Attribute("Name") );
        xAchieve.strName = strName;

        Common::_tstring strDesc;
        strDesc.fromUTF8( pAchieveElement->Attribute("Desc") );
        xAchieve.strDesc = strDesc;

        pAchieveElement->Attribute("ValueType", &iValue);
        xAchieve.nValueType = iValue;

        pAchieveElement->Attribute("FinishValue", &iValue);
        xAchieve.nFinishValue = iValue;

        pAchieveElement->Attribute("RewardPoint", &iValue);
        xAchieve.nRewardPoint = iValue;

        pAchieveElement->Attribute("RewardItem", &iValue);
        xAchieve.nRewardItem  = iValue;

        pAchieveElement->Attribute("IconID", &iValue);
        xAchieve.nIconID  = iValue;

        pAchieveElement->Attribute("Compare", &iValue);
        xAchieve.nCompare  = iValue;

        pAchieveElement->Attribute("ShowProcess", &iValue);
        xAchieve.nShowProcess  = iValue;

		Common::_tstring strScriptAddr;
		strScriptAddr.fromUTF8( pAchieveElement->Attribute("ScriptAddr") );
		xAchieve.strScriptAddr = strScriptAddr;

#ifndef _CLIENT_
		if ( xAchieve.strScriptAddr.length() > 0 )
			GetScriptMgr()->CreateVM( ST_ACHIEVE, xAchieve.strScriptAddr.c_str(), xAchieve.nId );
#endif //_CLIENT_

        m_vecAchieve[xAchieve.nId] = xAchieve;

        // 创建观察者
        Observer* pObserver = &m_vecObserver[xAchieve.nValueType];
        pObserver->nValueType = xAchieve.nValueType;
        pObserver->vecAchieveIds.push_back(xAchieve.nId);

        //next
        pAchieveElement = pAchieveElement->NextSiblingElement();
    }

    return true;
}
