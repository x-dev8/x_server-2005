#include "PocketShop.h"
#include "RapidXml\MeRapidXml.h"
#include "tstring.h"
#include "ItemDetail.h"

CPocketShopManger::CPocketShopManger()
{
	mapPocketShop.clear();
	m_bIsLoad = false;
}

CPocketShopManger::~CPocketShopManger()
{
	for(PocketShopMap::iterator iter=mapPocketShop.begin();iter!=mapPocketShop.end();iter++)
	{
		delete iter->second;
	}
	mapPocketShop.clear();
	m_bIsLoad = false;
}

bool CPocketShopManger::LoadConifg(const char* szFileName)
{	
	if (szFileName == NULL)
	{ return false; }

	MeXmlDocument mMeXmlDoc;
	if (!mMeXmlDoc.LoadFile(szFileName))
	{ return false; }

	MeXmlElement *pRoot = mMeXmlDoc.FirstChildElement("Project");
	if (pRoot == NULL)
	{ return false; }

	MeXmlElement *pShopTree = pRoot->FirstChildElement("Shop");
	if (pShopTree == NULL)
	{ return false; }


	MeXmlElement *pShopElement = pShopTree->FirstChildElement("Item");
	if (pShopElement == NULL)
	{ return false; }

	int iValue = 0;

	while ( pShopElement != NULL )
	{
		SPocketShop* pShopItem = new SPocketShop;

		if( pShopElement->Attribute("ID", &iValue) == NULL )
		{ iValue=0; }
		pShopItem->nItemID = iValue;

		if( pShopElement->Attribute("PerCount", &iValue) == NULL )
		{ iValue=0; }
		pShopItem->nPerCount = iValue;

		if( pShopElement->Attribute("BuyPrice", &iValue) == NULL )
		{ return false;}
		pShopItem->nBuyPrice = iValue;

		if ( pShopElement->Attribute("costtype", &iValue) == NULL )
		{
			iValue = 0;
		}
		pShopItem->byCostType = iValue;

		if ( pShopElement->Attribute("IsBound", &iValue) == NULL )
		{
			iValue = 0;
		}
		pShopItem->bIsBound = iValue;
		
		// ¼ÓÈë²éÕÒ
		mapPocketShop.insert( make_pair(pShopItem->nItemID,pShopItem) ); 
		m_vecID.push_back(pShopItem->nItemID);
		pShopElement = pShopElement->NextSiblingElement();
	}
	m_bIsLoad = true;
	return true;
}

CPocketShopManger::SPocketShop* CPocketShopManger::GetPocketShopItemByID(int nItemID)
{
	PocketShopMap::iterator iter = mapPocketShop.find(nItemID);
	if (iter==mapPocketShop.end())
	{
		return NULL;
	}
	return iter->second;
}

SShopItem CPocketShopManger::SPocketShopToSShopItem(SPocketShop* item)
{
	SShopItem sItem;
	sItem.bIsBound = false;
	sItem.costItemID = 0;
	sItem.costType = item->byCostType;
	sItem.dwBuyPrice = item->nBuyPrice;
	sItem.dwSellPrice = item->nBuyPrice/2;
	sItem.nBasePrice = item->nBuyPrice;
	sItem.nCurCount = 1<<30;
	sItem.nId = item->nItemID;
	sItem.nMaxCount = 1<<30;
	sItem.nPerCount = item->nPerCount;
	return sItem;
}