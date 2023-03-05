#include "DropItem.h"
#include "SlkReader.h"
#include "ErrorLog.h"
#include "ResourcePath.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"
#include "ErrorCode.h"
#include "LogFileObjectNameEx.h"
#include "DropCommonItemConfig.h"


/************************************************************************/
/* 加载 DropItemCommon.slk 文件					                        */
/************************************************************************/
bool DropCommonItemConfig::LoadData(const char* szFileName)
{
	if (szFileName == NULL || *szFileName == 0)
	{
		return false;
	}

    m_vtDropItem.clear();

    CSlkReader reader;
    int iRet = 0;
    int iRow = 0;

    if( !reader.ReadFromFile( szFileName ) )
    {
        LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Load %s File Error!",COMMONDROPITEM_FILEPATH);
        return false;
    }
    else
    {
        LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_INFO,"Load %s File Ok!",COMMONDROPITEM_FILEPATH);
    }
    int nPackId = -1;
    int nItemId = -1;
    int nProbability = 0;
    int nMinDrapCount = 0;
    int nMaxDrapCount = 0;
    int nRepeat = 0;
    SCommonDrop stItem;
    //
    iRow = 3;
    while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iRow++ ) ) ) 
    {
        if( CSlkReader::ret_nothisline == iRet )
            continue;
        bool bNewPack = true;
        if( !reader.GetIntFieldByName( "PackId", nPackId ) )
        {
            bNewPack = false;
        }
        if( !reader.GetIntFieldByName( "ItemId", nItemId ) )
        {
            LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s %d  [ItemId]  read failed", szFileName, iRow-1 );
            continue;
        }
        if( !reader.GetIntFieldByName( "Probability", nProbability ) )
        {
            LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s %d  [Probability]  read failed", szFileName, iRow-1 );
            continue;
        }
        if( !reader.GetIntFieldByName( "MinDropCount", nMinDrapCount ) )
        {
            if ( bNewPack == true )
            {
                LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s %d  [MinDropCount]  read failed", szFileName, iRow-1 );
                continue;
            }
        }
        else
        {
            if ( bNewPack == false )
            {
                LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s %d  [MinDropCount]  read failed", szFileName, iRow-1 );
            }
        }
        if( !reader.GetIntFieldByName( "MaxDropCount", nMaxDrapCount ) )
        {
            if ( bNewPack == true )
            {
                LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s %d  [MaxDropCount]  read failed", szFileName, iRow-1 );
            }
        }
        else
        {
            if ( bNewPack == false )
            {
                LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s %d  [MaxDropCount]  read failed", szFileName, iRow-1 );
            }
        }
        if( !reader.GetIntFieldByName( "Repeat", nRepeat ) )
        {
            if ( bNewPack == true )
            {
                LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s %d  [Repeat]  read failed", szFileName, iRow-1 );
            }
        }
        else
        {
            if ( bNewPack == false )
            {
                LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s %d  [Repeat]  read failed", szFileName, iRow-1 );
            }
        }
        //
        if ( bNewPack == true )
        {
            if ( stItem.vtItem.size() > 0 )
            {
                m_vtDropItem.push_back( stItem );
                stItem.vtItem.clear();
            }
            stItem.nPackId = nPackId;
            stItem.nMinDropCount = nMinDrapCount;
            stItem.nMaxDropCount = nMaxDrapCount;
            stItem.bRepeat = (nRepeat != 0);
        }
        if ( nItemId != -1 && nProbability > 0 )
        {
            SDropItem stDropItem;
            stDropItem.nItemId = nItemId;
            stDropItem.nProbability = nProbability;
            stItem.vtItem.push_back( stDropItem );
        }
    }
    if ( stItem.vtItem.size() > 0 )
    {
        m_vtDropItem.push_back( stItem );
    }
    return true;
}

/************************************************************************/
/* 加载 config 文件             										*/
/************************************************************************/
bool DropCommonItemConfig::LoadConfig(const char* szFileName)
{
	if (szFileName == NULL || *szFileName == 0)
	{
		return false;
	}

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(szFileName))
	{	
		LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Load %s File Error!",COMMONDROPITEM_FILEPATH);
		return false;
	}
	else
	{
		LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_INFO,"Load %s File Ok!",COMMONDROPITEM_FILEPATH);
	}


	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if ( NULL == pRoot ) return false;


	MeXmlElement* pItems = pRoot->FirstChildElement("DropCommonItems");
	if ( NULL == pItems ) return false;

	MeXmlElement* pPack = pItems->FirstChildElement("Pack");

	m_vtDropItem.clear();

	while (pPack != NULL)
	{
		SCommonDrop stItem;
		int nPackId = -1;
		int nMinDrapCount = 0;
		int nMaxDrapCount = 0;
		int nRepeat = 0;

		if (pPack->Attribute("PackId", &nPackId) == NULL)
		{
			LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s  %s element [%s] attribute  read failed", szFileName, "Pack" , "PackId" );
			return false;
		}
		stItem.nPackId = nPackId;

		if (pPack->Attribute("MinDropCount", &nMinDrapCount) == NULL)
		{
			LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s  %s element [%s] attribute  read failed", szFileName, "Pack" , "MinDropCount" );
			return false;
		}
		stItem.nMinDropCount = nMinDrapCount;

		if (pPack->Attribute("MaxDropCount", &nMaxDrapCount) == NULL)
		{
			LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s  %s element [%s] attribute  read failed", szFileName, "Pack" , "MaxDropCount" );
			return false;
		}
		stItem.nMaxDropCount = nMaxDrapCount;

		if (pPack->Attribute("Repeat", &nRepeat) == NULL)
		{
			LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s  %s element [%s] attribute  read failed", szFileName, "Pack" , "Repeat" );
			return false;
		}
		stItem.bRepeat = nRepeat;

		MeXmlElement* pItem = pPack->FirstChildElement("Item");

		while (pItem != NULL)
		{
			SDropItem stDropItem;
			int nItemId         = -1;
            int nItemNum        = 1;
			int nProbability    = 0;
            int nIsBound        = 0;
            int nIsStarRandom   = 0;
            int nStarLevel      = 0;
            int nBroadcastStrID = 0;

			if (pItem->Attribute("ItemId", &nItemId) == NULL)
			{
				LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s  %s element [%s] attribute  read failed", szFileName, "Item" , "ItemId" );
				return false;
			}
			stDropItem.nItemId = nItemId;

			if (pItem->Attribute("Probability", &nProbability) == NULL)
			{
				LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s  %s element [%s] attribute  read failed", szFileName, "Item" , "Probability" );
				return false;
			}
			stDropItem.nProbability = nProbability;

            pItem->Attribute("ItemNum", &nItemNum);
            pItem->Attribute("IsBound", &nIsBound);
            pItem->Attribute("IsStarRandom", &nIsStarRandom);
            pItem->Attribute("StarLevel", &nStarLevel);
            pItem->Attribute("Broadcast", &nBroadcastStrID);

			stDropItem.nItemId          = nItemId;
            stDropItem.nItemNum         = nItemNum;
			stDropItem.nProbability     = nProbability;
            stDropItem.bIsBound         = nIsBound;
            stDropItem.bStarRandom      = nIsStarRandom;
            stDropItem.nStarLevel       = nStarLevel;
            stDropItem.nBroadcastStrID  = nBroadcastStrID;
			stItem.vtItem.push_back( stDropItem );

			//next node 
			pItem = pItem->NextSiblingElement();

		}/* 加载公共掉落包Pack中的 Item  */

		m_vtDropItem.push_back( stItem );

		//next node
		pPack = pPack->NextSiblingElement();
		
	}/* 加载公共掉落包Pack */

	return true;

}


/************************************************************************/
/* 将配置保存为 config 文件												*/
/************************************************************************/
bool DropCommonItemConfig::SaveConfig(const char* szFileName)
{
	if (szFileName == NULL || *szFileName == 0)
	{
		return false;
	}

	MeXmlDocument xMeXmlDoc;
	xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));

	MeXmlElement* pRoot = xMeXmlDoc.InsertEndChild(("Project"))->ToElement();
	if (pRoot == NULL) { return false; }

	//Common::_tstring strName = "HeroOnline";
	pRoot->SetAttribute("Name", "");

	//Common::_tstring strVersion = ApplicationConfig::Instance().GetFullVersion();		
	pRoot->SetAttribute("Version", ""/*strVersion.toUTF8().c_str()*/);

	MeXmlElement* pItems = pRoot->InsertEndChild(("DropCommonItems"))->ToElement();
	if(pItems == NULL) { return false; }

	std::vector<SCommonDrop>::iterator iter = m_vtDropItem.begin();
	std::vector<SCommonDrop>::iterator end  = m_vtDropItem.end();

	for (; iter != end; ++iter)
	{
		MeXmlElement* pPack = pItems->InsertEndChild(("Pack"))->ToElement();
		if (pPack == NULL) { return false; }

		pPack->SetAttribute("PackId", iter->nPackId);
		pPack->SetAttribute("MinDropCount", iter->nMinDropCount);
		pPack->SetAttribute("MaxDropCount", iter->nMaxDropCount);
		pPack->SetAttribute("Repeat", iter->bRepeat);

		
		std::vector<SDropItem>::iterator m_vtItemIter =  iter->vtItem.begin();
		std::vector<SDropItem>::iterator m_vtItemEnd =  iter->vtItem.end();

		for (; m_vtItemIter != m_vtItemEnd; ++m_vtItemIter)
		{
			MeXmlElement* pItem = pPack->InsertEndChild(("Item"))->ToElement();
			if (pItem == NULL) { return false; }

			pItem->SetAttribute("ItemId", m_vtItemIter->nItemId);
			pItem->SetAttribute("Probability", m_vtItemIter->nProbability);
		}

	}

	return xMeXmlDoc.SaveFile(szFileName);

}

int DropCommonItemConfig::GetIndexByPackId( int nPackId )
{
    for ( unsigned int n=0; n<m_vtDropItem.size(); n++ )
    {
        SCommonDrop* pDropItem = &m_vtDropItem[n];
        if ( pDropItem->nPackId == nPackId )
        {
            return n;
        }
    }
    return -1;
}

SCommonDrop* DropCommonItemConfig::GetSCommonDropByIndex(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_vtDropItem.size()) 
	{ return NULL; }

	return &m_vtDropItem[nIndex];
}

SCommonDrop* DropCommonItemConfig::GetSCommonDropByPackId(int nPackId)
{
	if (nPackId <= 0) 
	{ return NULL; }

	std::vector<SCommonDrop>::iterator iter = find(m_vtDropItem.begin(), m_vtDropItem.end(), nPackId);

	if (iter != m_vtDropItem.end())
	{
		return &(*iter);
	}

	return NULL;
}

