#include "DaoxingConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"
#include "application_config.h"

DaoxingConfig::SDaoxingEffect* DaoxingConfig::GetDaoxingEffect( unsigned short nQuotient )
{
    if ( nQuotient >= DAOXING_QUOTIENT_LIMIT )
    { nQuotient = DAOXING_QUOTIENT_LIMIT; }

    DaoxingIter iter = vecDaoxingEffect.begin();
    for ( ; iter != vecDaoxingEffect.end(); ++iter )
    {
        if ( ( iter->nBeginQuotient <= nQuotient && iter->nEndQuotient >= nQuotient ) )
        { return &(*iter); }
    }

    return NULL;
}

bool DaoxingConfig::LoadDaoxingConfig(const char* szFile)
{
    if (szFile == NULL || *szFile == 0)
    { return false;	}

    MeXmlDocument xMeXml;
    if (!xMeXml.LoadFile(szFile, 1))
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
    if (pRoot == NULL )
    { return false; }

    MeXmlElement* pDaoxings = pRoot->FirstChildElement("Daoxings");
    if (pDaoxings == NULL) 
    { return false; }

    int iValue = 0;

    MeXmlElement* pDaoxingElement = pDaoxings->FirstChildElement("DaoxingEffect");
    while (pDaoxingElement != NULL)
    {	
        SDaoxingEffect xEffect;

        pDaoxingElement->Attribute("ID", &iValue);
        xEffect.nId = iValue;

        pDaoxingElement->Attribute("BeginQuotient", &iValue);
        xEffect.nBeginQuotient = iValue;

        pDaoxingElement->Attribute("EndQuotient", &iValue);
        xEffect.nEndQuotient = iValue;

        pDaoxingElement->Attribute("GiddyResist", &iValue);
        xEffect.resist[SNT_GIDDY] = iValue;

        pDaoxingElement->Attribute("AddGiddyTimePer", &iValue);
        xEffect.addTimePer[SNT_GIDDY] = iValue;

		pDaoxingElement->Attribute("StandResist", &iValue);
		xEffect.resist[SNT_STAND] = iValue;

		pDaoxingElement->Attribute("AddStandTimePer", &iValue);
		xEffect.addTimePer[SNT_STAND] = iValue;

		pDaoxingElement->Attribute("SlowdownResist", &iValue);
		xEffect.resist[SNT_SLOWDOWN] = iValue;

		pDaoxingElement->Attribute("AddSlowdownTimePer", &iValue);
		xEffect.addTimePer[SNT_SLOWDOWN] = iValue;

		pDaoxingElement->Attribute("TorpidResist", &iValue);
		xEffect.resist[SNT_TORPID] = iValue;

		pDaoxingElement->Attribute("AddTorpidTimePer", &iValue);
		xEffect.addTimePer[SNT_TORPID] = iValue;

		pDaoxingElement->Attribute("HurtResist", &iValue);
		xEffect.resist[SNT_HURT] = iValue;

		pDaoxingElement->Attribute("AddHurtTimePer", &iValue);
		xEffect.addTimePer[SNT_HURT] = iValue;

		pDaoxingElement->Attribute("AttrResist", &iValue);
		xEffect.resist[SNT_ATTR] = iValue;

		pDaoxingElement->Attribute("AddAttrTimePer", &iValue);
		xEffect.addTimePer[SNT_ATTR] = iValue;

		pDaoxingElement->Attribute("AfraidResist", &iValue);
		xEffect.resist[SNT_AFRAID] = iValue;

		pDaoxingElement->Attribute("AddAfraidTimePer", &iValue);
		xEffect.addTimePer[SNT_AFRAID] = iValue;

		pDaoxingElement->Attribute("SleepResist", &iValue);
		xEffect.resist[SNT_SLEEP] = iValue;

		pDaoxingElement->Attribute("AddSleepTimePer", &iValue);
		xEffect.addTimePer[SNT_SLEEP] = iValue;

		pDaoxingElement->Attribute("DistortionResist", &iValue);
		xEffect.resist[SNT_DISTORTION] = iValue;

		pDaoxingElement->Attribute("AddDistortionTimePer", &iValue);
		xEffect.addTimePer[SNT_DISTORTION] = iValue;

		pDaoxingElement->Attribute("FrostResist", &iValue);
		xEffect.resist[SNT_FROST] = iValue;

		pDaoxingElement->Attribute("AddFrostTimePer", &iValue);
		xEffect.addTimePer[SNT_FROST] = iValue;

		pDaoxingElement->Attribute("SneeratResist", &iValue);
		xEffect.resist[SNT_SNEERAT] = iValue;

		pDaoxingElement->Attribute("AddSneeratTimePer", &iValue);
		xEffect.addTimePer[SNT_SNEERAT] = iValue;

		pDaoxingElement->Attribute("ForgetResist", &iValue);
		xEffect.resist[SNT_FORGET] = iValue;

		pDaoxingElement->Attribute("AddForgetTimePer", &iValue);
		xEffect.addTimePer[SNT_FORGET] = iValue;

		pDaoxingElement->Attribute("IlliberalityResist", &iValue);
		xEffect.resist[SNT_ILLIBERALITY] = iValue;

		pDaoxingElement->Attribute("AddIlliberalityTimePer", &iValue);
		xEffect.addTimePer[SNT_ILLIBERALITY] = iValue;

		pDaoxingElement->Attribute("AtonyResist", &iValue);
		xEffect.resist[SNT_ATONY] = iValue;

		pDaoxingElement->Attribute("AddAtonyTimePer", &iValue);
		xEffect.addTimePer[SNT_ATONY] = iValue;

		pDaoxingElement->Attribute("AllureResist", &iValue);
		xEffect.resist[SNT_ALLURE] = iValue;

		pDaoxingElement->Attribute("AddAllureTimePer", &iValue);
		xEffect.addTimePer[SNT_ALLURE] = iValue;

        vecDaoxingEffect.push_back(xEffect);
        pDaoxingElement = pDaoxingElement->NextSiblingElement();
    }

    return true;
}
