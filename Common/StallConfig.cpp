#include "StallConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"


StallConfig& GetStallConfig()
{
	static StallConfig instance;
	return instance;
}

bool StallConfig::LoadStallConfig( const char* szFile )
{
	if (szFile == NULL || *szFile == 0)
	{ return false;	}

	_OfflineStallCostMenu.clear();

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile( szFile ))
	{ return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (pRoot == NULL )
	{ return false; }

	//////////////////////////////////////////////////////////////////////////
	//  ÀëÏß°ÚÌ¯ÅäÖÃ
	MeXmlElement* pOfflineStallCosts = pRoot->FirstChildElement("OfflineStallCosts");
	if (pOfflineStallCosts == NULL) 
	{ return false; }

	int iValue;

	MeXmlElement* pOneCostType = pOfflineStallCosts->FirstChildElement("OneCostType");
	while (pOneCostType != NULL)
	{	
		CostSetmeal costSetmeal;

		pOneCostType->Attribute("ID", &iValue);
		costSetmeal.nID = iValue;

		pOneCostType->Attribute("StallRevenue", &iValue);
		costSetmeal.nStallRevenue = iValue;

		pOneCostType->Attribute("TradeRevenue", &iValue);
		costSetmeal.nTradeRevenue = iValue;

		pOneCostType->Attribute("OfflineTime", &iValue);
		costSetmeal.nTime = iValue;

		MeXmlElement* pCost = pOneCostType->FirstChildElement("Cost");
		while (pCost != NULL)
		{
			OneCost ontCost;

			pCost->Attribute("Type", &iValue);
			ontCost.nType = iValue;

			pCost->Attribute("Subtype", &iValue);
			ontCost.nSubType = iValue;

			pCost->Attribute("Value", &iValue);
			ontCost.nValue = iValue;

			costSetmeal.costList.push_back(ontCost);

			pCost = pCost->NextSiblingElement();
		}

		_OfflineStallCostMenu.push_back(costSetmeal);

		//next
		pOneCostType= pOneCostType->NextSiblingElement();
	}

	//////////////////////////////////////////////////////////////////////////
	//  ÔÚÏß°ÚÌ¯ÅäÖÃ
	MeXmlElement* pOnlineStallCosts = pRoot->FirstChildElement("OnlineStallCosts");
	if (pOnlineStallCosts == NULL) 
	{ return false; }

	pOneCostType = pOnlineStallCosts->FirstChildElement("OneCostType");
	while (pOneCostType != NULL)
	{	
		CostSetmeal costSetmeal;

		pOneCostType->Attribute("ID", &iValue);
		costSetmeal.nID = iValue;

		pOneCostType->Attribute("StallRevenue", &iValue);
		costSetmeal.nStallRevenue = iValue;

		pOneCostType->Attribute("TradeRevenue", &iValue);
		costSetmeal.nTradeRevenue = iValue;

		MeXmlElement* pCost = pOneCostType->FirstChildElement("Cost");
		while (pCost != NULL)
		{
			OneCost ontCost;

			pCost->Attribute("Type", &iValue);
			ontCost.nType = iValue;

			pCost->Attribute("Subtype", &iValue);
			ontCost.nSubType = iValue;

			pCost->Attribute("Value", &iValue);
			ontCost.nValue = iValue;

			costSetmeal.costList.push_back(ontCost);

			pCost = pCost->NextSiblingElement();
		}

		_OnlineStallCostMenu.push_back(costSetmeal);

		//next
		pOneCostType= pOneCostType->NextSiblingElement();
	}

	return true;
}

StallConfig::CostSetmeal* StallConfig::GetOfflineCostSetmeal( int nIndex )
{
	if ( nIndex >= _OfflineStallCostMenu.size() )
	{ return NULL; }

	return &_OfflineStallCostMenu[nIndex];
}

StallConfig::CostSetmeal* StallConfig::GetOnlineCostSetmeal( int nIndex )
{
	if ( nIndex >= _OnlineStallCostMenu.size() )
	{ return NULL; }

	return &_OnlineStallCostMenu[nIndex];
}

StallConfig::CostSetmeal* StallConfig::GetOnlineCostSetmealByID( uint8 nID )
{
	ItrStallCostMenu itr = _OnlineStallCostMenu.begin();
	ItrStallCostMenu endItr = _OnlineStallCostMenu.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( nID == itr->nID )
		{ return &*itr; }
	}
	return NULL;
}

StallConfig::CostSetmeal* StallConfig::GetOfflineCostSetmealByID( uint8 nID )
{
	ItrStallCostMenu itr = _OfflineStallCostMenu.begin();
	ItrStallCostMenu endItr = _OfflineStallCostMenu.end();
	for ( ; itr != endItr; ++itr )
	{
		if ( nID == itr->nID )
		{ return &*itr; }
	}
	return NULL;
}
