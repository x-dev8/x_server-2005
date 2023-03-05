#include "PhyleConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"
#include "application_config.h"
#include "FamilyDefine.h"
#include "ItemDetail.h"

unsigned int PhyleChastenConfig::GetDamageByTotem( unsigned char attackerTotem, unsigned char targetTotem )
{
	if ( FamilyDefine::Totem_Human <= attackerTotem && attackerTotem <= FamilyDefine::Totem_Demon &&
		 FamilyDefine::Totem_Human <= targetTotem && targetTotem <= FamilyDefine::Totem_Demon)
	{
	
		PhyleContainerItr iter = PhyleSettingContainer.begin();
		for ( ; iter != PhyleSettingContainer.end(); ++iter )
		{
			if ( iter->nTotemType == attackerTotem )
			{
				return iter->totemChastenDamage[ targetTotem ];
			}
		}
	}

	return 0;
}

bool PhyleChastenConfig::LoadConfig(const char* szFile)
{
	if (szFile == NULL || *szFile == 0)
	{ return false;	}

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(szFile, 1))
	{ return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (pRoot == NULL )
	{ return false; }


	MeXmlElement* pIdentify = pRoot->FirstChildElement("Identify");
	if (pIdentify == NULL) 
	{ return false; }
	int iValue = 0;

	while (pIdentify != NULL)
	{
		IdentifyIntro xIdentify;

		pIdentify->Attribute("PetType", &iValue);
		xIdentify.nPetType = iValue;

		Common::_tstring phyleIntro;
		phyleIntro.fromUTF8( pIdentify->Attribute("IdentifyIntro") );
		xIdentify.szIdentifyIntro = phyleIntro;

		IdentifyIntroContainer.push_back(xIdentify);
		pIdentify = pIdentify->NextSiblingElement("Identify");

	}

	MeXmlElement* pTotemChastens = pRoot->FirstChildElement("TotemChastenConfig");
	if (pTotemChastens == NULL) 
	{ return false; }

	iValue = 0;

	MeXmlElement* pTotemChastenElement = pTotemChastens->FirstChildElement("TotemChasten");
	while (pTotemChastenElement != NULL)
	{	
		SPhyleChasten xTotemChasten;
		
		pTotemChastenElement->Attribute("TotemType", &iValue);
		xTotemChasten.nTotemType = iValue;

		MeXmlElement* pTotemDamageElement = pTotemChastenElement->FirstChildElement("DamageSetting");
		while (pTotemDamageElement != NULL)
		{
			int index = 0;

			pTotemDamageElement->Attribute("TargetTotemType", &iValue);
			index = iValue;

			pTotemDamageElement->Attribute("DamagePercent", &iValue);
			xTotemChasten.totemChastenDamage[index] = iValue;

			pTotemDamageElement = pTotemDamageElement->NextSiblingElement();

		}

		PhyleSettingContainer.push_back(xTotemChasten);
		pTotemChastenElement = pTotemChastenElement->NextSiblingElement();

	}

	return true;
}

std::string PhyleChastenConfig::GetIdentifyIntroByPetType( unsigned int nPetType )
{
	IdentifyIntroContainerItr iter = IdentifyIntroContainer.begin();
	for ( ; iter != IdentifyIntroContainer.end(); ++iter )
	{
		if ( iter->nPetType == nPetType )
		{
			return iter->szIdentifyIntro;
		}
	}
	
	return NULL;
}
