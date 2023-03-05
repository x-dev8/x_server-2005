#include "EquipEvolveConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"
//#include "application_config.h"


bool EquipEvolveConfig::LoadStilettoConfig(const char* szFile)
{
	if (szFile == NULL || *szFile == 0)
	{ return false;	}

	m_vecStiletto.clear();

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile( szFile ))
	{ return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (pRoot == NULL )
	{ return false; }

	//////////////////////////////////////////////////////////////////////////
	//  ¼ÓÔØ´ò¿×ÅäÖÃ
	MeXmlElement* pStilettos = pRoot->FirstChildElement("Stilettos");
	if (pStilettos == NULL) 
	{ return false; }

	int iValue;

	MeXmlElement* pStilettoElement = pStilettos->FirstChildElement("Stiletto");
	while (pStilettoElement != NULL)
	{	
		SEquipStiletto xStiletto;

		pStilettoElement->Attribute("HoleIndex", &iValue);
		xStiletto.nHoleIndex = iValue;

		pStilettoElement->Attribute("SuccessRate", &iValue);
		xStiletto.nSuccessRate = iValue;

		pStilettoElement->Attribute("CostType", &iValue);
		xStiletto.nCostType = iValue;

		pStilettoElement->Attribute("CostValue", &iValue);
		xStiletto.nCostValue = iValue;

		m_vecStiletto.push_back(xStiletto);

		//next
		pStilettoElement= pStilettoElement->NextSiblingElement();
	}

	return true;
}

bool EquipEvolveConfig::LoadInlayRateConfig( const char *szFile )
{
	if (szFile == NULL || *szFile == 0)
	{ return false;	}

	m_vecInlayRate.clear();

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile( szFile ))
	{ return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (pRoot == NULL )
	{ return false; }

	//////////////////////////////////////////////////////////////////////////
	//  ¼ÓÔØÅäÖÃ
	MeXmlElement* pInlayRates = pRoot->FirstChildElement("InlayRates");
	if (pInlayRates == NULL) 
	{ return false; }

	int iValue;

	MeXmlElement* pInlayRateElement = pInlayRates->FirstChildElement("InlayRate");
	while (pInlayRateElement != NULL)
	{	
		SEquipInlayRate inlayRate;

		pInlayRateElement->Attribute("MaterialType", &iValue);
		inlayRate.nMaterialType = iValue;

		pInlayRateElement->Attribute("SuccessRate", &iValue);
		inlayRate.nSuccessRate = iValue;

		m_vecInlayRate.push_back(inlayRate);

		//next
		pInlayRateElement= pInlayRateElement->NextSiblingElement();
	}

	return true;
}

EquipEvolveConfig::SEquipStiletto* EquipEvolveConfig::GetStiletto( uint8 holeIndex )
{
	for ( IterEquipStilettoContainer it = m_vecStiletto.begin(); it != m_vecStiletto.end(); ++it )
	{
		if ( it->nHoleIndex == holeIndex )
		{
			return &*it;
		}
	}
	return NULL;
}

EquipEvolveConfig::SEquipInlayRate* EquipEvolveConfig::GetInlayRate( uint8 materialType )
{
	for ( IterEquipInlayRateContainer it = m_vecInlayRate.begin(); it != m_vecInlayRate.end(); ++it )
	{
		if ( it->nMaterialType == materialType )
		{
			return &*it;
		}
	}
	return NULL;
}

bool EquipEvolveConfig::LoadUnknowIdentifyConfig( const char *szFile )
{
	if (szFile == NULL || *szFile == 0)
	{ return false;	}

	m_vecInlayRate.clear();

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile( szFile ))
	{ return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (pRoot == NULL )
	{ return false; }

	//////////////////////////////////////////////////////////////////////////
	//  ¼ÓÔØÅäÖÃ
	MeXmlElement* pUnknowIdentifies = pRoot->FirstChildElement("UnknowIdentifies");
	if (pUnknowIdentifies == NULL) 
	{ return false; }

	int iValue;

	MeXmlElement* pUnknowIdentifyElement = pUnknowIdentifies->FirstChildElement("UnknowIdentify");
	while (pUnknowIdentifyElement != NULL)
	{
		SEquipUnknowIdentify unknowIdentify;

		pUnknowIdentifyElement->Attribute("ItemID", &iValue);
		unknowIdentify.nItemID = iValue;

		Common::_tstring strGetItemID;
		strGetItemID.fromUTF8( pUnknowIdentifyElement->Attribute("GetItemID") );
		if ( !strGetItemID.empty() )
		{   
			char *szSpn = ",";
			char *szStr;

			szStr = strtok( const_cast<char*>(strGetItemID.c_str()), szSpn );
			while( szStr )
			{
				if ( atoi(szStr) > 0 )
				{
					SEquipUnknowIdentify::SGetItem getItem;
					getItem.nGetItemID = atoi(szStr);
					getItem.nGetItemRate = 0;
					unknowIdentify.getItemList.push_back(getItem);
				}
				szStr = strtok( NULL, szSpn );
			}
		}

		Common::_tstring strGetItemIDRate;
		strGetItemIDRate.fromUTF8( pUnknowIdentifyElement->Attribute("GetItemIDRate") );
		if ( !strGetItemIDRate.empty() )
		{   
			char *szSpn = ",";
			char *szStr;
			int i = 0;

			szStr = strtok( const_cast<char*>(strGetItemIDRate.c_str()), szSpn );
			while( szStr )
			{
				if ( atoi(szStr) > 0  && i < unknowIdentify.getItemList.size() )
				{
					unknowIdentify.getItemList[i].nGetItemRate = atoi(szStr);
				}
				szStr = strtok( NULL, szSpn );
				++i;
			}
		}

		pUnknowIdentifyElement->Attribute("CostType", &iValue);
		unknowIdentify.nCostType = iValue;

		pUnknowIdentifyElement->Attribute("CostValue", &iValue);
		unknowIdentify.nCostValue = iValue;

		pUnknowIdentifyElement->Attribute("IsStarRandom", &iValue);
		unknowIdentify.blIsStarRandom = iValue == 1 ? true : false;

		pUnknowIdentifyElement->Attribute("StarLevel", &iValue);
		unknowIdentify.nStarLevel = iValue;

		pUnknowIdentifyElement->Attribute("IsBound ", &iValue);
		unknowIdentify.blIsBound = iValue == 1 ? true : false;

		m_vecUnknowIdentify.push_back(unknowIdentify);

		//next
		pUnknowIdentifyElement= pUnknowIdentifyElement->NextSiblingElement();
	}

	return true;
}

EquipEvolveConfig::SEquipUnknowIdentify* EquipEvolveConfig::GetUnknowIdentify( uint16 nItemID )
{
	for ( IterEquipUnknowIdentifyContainer it = m_vecUnknowIdentify.begin(); it != m_vecUnknowIdentify.end(); ++it )
	{
		if ( it->nItemID == nItemID )
		{
			return &*it;
		}
	}
	return NULL;
}
