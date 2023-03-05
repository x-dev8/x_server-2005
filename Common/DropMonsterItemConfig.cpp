#include "DropMonsterItemConfig.h"
#include "DropItem.h"
#include "DropCommonItemConfig.h"
#include "SlkReader.h"
#include "ErrorLog.h"
#include "ResourcePath.h"
#include "LogFileObjectNameEx.h"
#include "RapidXml/MeRapidXml.h"

bool DropMonsterItemConfig::LoadData(const char* szFileName)
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
        LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Load %s File Error!",MONSTERDROPITEM_FILEPATH);
		return false;
    }
    else
    {
        LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_INFO,"Load %s File Ok!",MONSTERDROPITEM_FILEPATH);
    }

	int nMonsterId = 0;
	int nItemId = -1;
	int nProbability = 0;
	int nPackProbabilityRate = 100;
	int nRandCount = 1;
	int nPackId = -1;
	int nPackProbability = 0;
	SMonsterDrop xMonsterDropItem;

	iRow = 3;
	while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iRow++ ) ) ) 
	{
		if( CSlkReader::ret_nothisline == iRet )
			continue;

		bool bNewMonster = true;
		if( !reader.GetIntFieldByName( "MonsterId", nMonsterId ) )
		{
			bNewMonster = false;
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
		if( !reader.GetIntFieldByName( "RandCount", nRandCount ) )
		{
			LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s %d  [RandCount]  read failed", szFileName, iRow-1 );
			continue;
		}

		SCommonPack xCommonPack;
		if( !reader.GetIntFieldByName( "PackProbability", nPackProbability ) )
		{
			LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s %d  [PackProbability]  read failed", szFileName, iRow-1 );
			continue;
		}
		else
		{
			xCommonPack.nProbability = nPackProbability;
		}
		if( !reader.GetIntFieldByName( "PackProbabilityRate", nPackProbabilityRate ) )
		{
			LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s %d  [PackProbabilityRate]  read failed", szFileName, iRow-1 );
			continue;
		}
		else
		{
			xCommonPack.nPackProbabilityRate = nPackProbabilityRate;
		}

        for ( int n=0; n<MAX_COMMONPACK_COUNT; n++ )
        {
            char szPackKey[32];
            _snprintf( szPackKey, sizeof(szPackKey)-1, "CPID%d", n );
            if( !reader.GetIntFieldByName( szPackKey, nPackId ) )
            {
                LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s %d  [%s]  read failed", szFileName, iRow-1, szPackKey );
                break;
            }
            else
            {
                if ( nPackId != -1 )
                {
                    SCommonPackID stPackId;
                    stPackId.nID = nPackId;
                    stPackId.nIndex = theDropCommonItemConfig.GetIndexByPackId( nPackId );
                    xCommonPack.vtCommonPackID.push_back( stPackId );
                }
            }
        }

		//
		if ( bNewMonster == true )
		{
			if ( xMonsterDropItem.vtMonsterPack.size() > 0 ||
				xMonsterDropItem.vtPackId.size() > 0 )
			{
				m_vtDropItem.push_back( xMonsterDropItem );
				xMonsterDropItem.vtMonsterPack.clear();
				xMonsterDropItem.vtPackId.clear();
			}
			xMonsterDropItem.nMonsterId = nMonsterId;
		}

		if ( nItemId != -1 && nProbability > 0 )
		{
			SMonsterPack stMonsterPack;
			stMonsterPack.stItem.nItemId = nItemId;
			stMonsterPack.stItem.nProbability = nProbability;
			stMonsterPack.nRandCount = nRandCount;
			xMonsterDropItem.vtMonsterPack.push_back( stMonsterPack );
		}

		xMonsterDropItem.vtPackId.push_back( xCommonPack );
	}

	if ( xMonsterDropItem.vtMonsterPack.size() > 0 ||
		xMonsterDropItem.vtPackId.size() > 0 )
	{
		m_vtDropItem.push_back( xMonsterDropItem );
	}
	return true;
}


/************************************************************************/
/* 加载 config 文件             										*/
/************************************************************************/
bool DropMonsterItemConfig::LoadConfig(const char* szFileName)
{
	if (szFileName == NULL || *szFileName == 0)
	{
		return false;
	}

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(szFileName))
	{	
		LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"Load %s File Error!",MONSTERDROPITEM_FILEPATH);
		return false;
	}
	else
	{
		LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_INFO,"Load %s File Ok!",MONSTERDROPITEM_FILEPATH);
	}


	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if ( NULL == pRoot ) return false;


	MeXmlElement* pItems = pRoot->FirstChildElement("DropMonsterItems");
	if ( NULL == pItems ) return false;

	MeXmlElement* pMonster = pItems->FirstChildElement("Monster");

	m_vtDropItem.clear();

	while (pMonster != NULL)
	{
		int nMonsterId = 0;
        int nPackDropType = 0;
		int nItemId = -1;
		int nProbability = 0;
		int nPackProbabilityRate = 100;
		int nRandCount = 1;
		int nPackId = -1;
		int nPackProbability = 0;
		SMonsterDrop xMonsterDropItem;

		if (pMonster->Attribute("MonsterId", &nMonsterId) == NULL)
		{
			LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s  %s element [%s] attribute  read failed", szFileName, "Monster" , "MonsterId" );
			return false;
		}
		xMonsterDropItem.nMonsterId = nMonsterId;

        pMonster->Attribute("PackDropType", &nPackDropType);
        xMonsterDropItem.nPackDropType = nPackDropType;

        // 怪物掉落包 基本没有使用到
		MeXmlElement* pMonsterPack = pMonster->FirstChildElement("MonsterPack");
		while (pMonsterPack != NULL)
		{
			SMonsterPack stMonsterPack;
			SDropItem stDropItem;

			if (pMonsterPack->Attribute("ItemId", &nItemId) == NULL)
			{
				LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s  %s element [%s] attribute  read failed", szFileName, "MonsterPack" , "ItemId" );
				return false;
			}
			stDropItem.nItemId = nItemId;

			if (pMonsterPack->Attribute("Probability", &nProbability) == NULL)
			{
				LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s  %s element [%s] attribute  read failed", szFileName, "MonsterPack" , "Probability" );
				return false;
			}
			stDropItem.nProbability = nProbability;

			if (pMonsterPack->Attribute("RandCount", &nRandCount) == NULL)
			{
				LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s  %s element [%s] attribute  read failed", szFileName, "MonsterPack" , "RandCount" );
				return false;
			}
			stMonsterPack.nRandCount = nRandCount;

			stMonsterPack.stItem = stDropItem;

			xMonsterDropItem.vtMonsterPack.push_back(stMonsterPack);

			pMonsterPack = pMonsterPack->NextSiblingElement();
		}

        // 公共掉落包
		MeXmlElement* pCommonPack = pMonster->FirstChildElement("CommonPack");
		while (pCommonPack != NULL)
		{
			SCommonPack stCommonPack;

			if (pCommonPack->Attribute("PackProbability", &nPackProbability) == NULL)
			{
				LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s  %s element [%s] attribute  read failed", szFileName, "CommonPack" , "PackProbability" );
				return false;
			}
			stCommonPack.nProbability = nPackProbability;

			if (pCommonPack->Attribute("PackProbabilityRate", &nPackProbabilityRate) == NULL)
			{
				LOG_MESSAGE(SYSTEMOBJECT,LOG_PRIORITY_ERROR,"%s  %s element [%s] attribute  read failed", szFileName, "CommonPack" , "PackProbabilityRate" );
				return false;
			}
			stCommonPack.nPackProbabilityRate = nPackProbabilityRate;

            for ( int n=0; n<MAX_COMMONPACK_COUNT; n++ )
            {
                char szPackKey[32];
                _snprintf( szPackKey, sizeof(szPackKey)-1, "CPID%d", n );
                if (pCommonPack->Attribute(szPackKey, &nPackId) == NULL || nPackId == 0)
                { continue; }

                SCommonPackID stPackId;
                stPackId.nID = nPackId;
                stPackId.nIndex = theDropCommonItemConfig.GetIndexByPackId( nPackId );
                stCommonPack.vtCommonPackID.push_back(stPackId);

            }

            //放入怪物掉落包裹中
			xMonsterDropItem.vtPackId.push_back(stCommonPack);

			pCommonPack = pCommonPack->NextSiblingElement();
		}

		m_vtDropItem.push_back( xMonsterDropItem );

		pMonster = pMonster->NextSiblingElement();
	}

	return true;
}

/************************************************************************/
/* 将配置保存为 config 文件												*/
/************************************************************************/
bool DropMonsterItemConfig::SaveConfig(const char* szFileName)
{
	if (szFileName == NULL || *szFileName == 0)
	{
		return false;
	}

	MeXmlDocument xMeXmlDoc;
	xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));

	MeXmlElement* pRoot = xMeXmlDoc.InsertEndChild(("Project"))->ToElement();
	if (pRoot == NULL) 
	{ return false; }

	//Common::_tstring strName = "HeroOnline";
	pRoot->SetAttribute("Name", "");

	//Common::_tstring strVersion = ApplicationConfig::Instance().GetFullVersion();		
	pRoot->SetAttribute("Version", ""/*strVersion.toUTF8().c_str()*/);

	MeXmlElement* pItems = pRoot->InsertEndChild(("DropMonsterItems"))->ToElement();
	if(pItems == NULL) 
	{ return false; }

	std::vector< SMonsterDrop >::iterator iter = m_vtDropItem.begin();
	std::vector< SMonsterDrop >::iterator end  = m_vtDropItem.end();

	for (; iter != end; ++iter)
	{
		MeXmlElement* pMonster = pItems->InsertEndChild(("Monster"))->ToElement();
		if (pMonster == NULL) 
		{ return false; }

		pMonster->SetAttribute("MonsterId", iter->nMonsterId);

		std::vector< SMonsterPack >::iterator m_vtItemMonIter =  iter->vtMonsterPack.begin();
		std::vector< SMonsterPack >::iterator m_vtItemMonEnd  =  iter->vtMonsterPack.end();

		for (; m_vtItemMonIter != m_vtItemMonEnd; ++m_vtItemMonIter)
		{
			MeXmlElement* pPack = pMonster->InsertEndChild(("MonsterPack"))->ToElement();
			if (pPack == NULL) { return false; }

			pPack->SetAttribute("ItemId", m_vtItemMonIter->stItem.nItemId);
			pPack->SetAttribute("Probability", m_vtItemMonIter->stItem.nProbability);
			pPack->SetAttribute("RandCount", m_vtItemMonIter->nRandCount);
		}

		std::vector< SCommonPack >::iterator m_vtItemCommIter = iter->vtPackId.begin();
		std::vector< SCommonPack >::iterator m_vtItemCommEnd = iter->vtPackId.end();

		for (; m_vtItemCommIter != m_vtItemCommEnd; ++m_vtItemCommIter)
		{
			MeXmlElement* pPack = pMonster->InsertEndChild(("CommonPack"))->ToElement();
			if (pPack == NULL) { return false; }
			
			pPack->SetAttribute("PackProbability", m_vtItemCommIter->nProbability);
			pPack->SetAttribute("PackProbabilityRate", m_vtItemCommIter->nPackProbabilityRate);
            
            std::vector< SCommonPackID >::iterator m_vtItemCommPackIter = m_vtItemCommIter->vtCommonPackID.begin();
            std::vector< SCommonPackID >::iterator m_vtItemCommPackEnd = m_vtItemCommIter->vtCommonPackID.end();

            for ( int n=0; n<MAX_COMMONPACK_COUNT; n++ )
            {
                char szPackKey[32];
                _snprintf( szPackKey, sizeof(szPackKey)-1, "CPID%d", n );
                pPack->SetAttribute(szPackKey, 0);
            }

            int nCPID = 0;
            for (; m_vtItemCommPackIter != m_vtItemCommPackEnd; ++m_vtItemCommPackIter)
            {
                char szPackKey[32];
                _snprintf( szPackKey, sizeof(szPackKey)-1, "CPID%d", nCPID );
                pPack->SetAttribute(szPackKey, m_vtItemCommPackIter->nID);

                ++nCPID;
            }
		}
	}

	return xMeXmlDoc.SaveFile(szFileName);
}

SMonsterDrop* DropMonsterItemConfig::GetSMonsterDropByIndex(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_vtDropItem.size()) 
	{ return NULL; }

	return &m_vtDropItem[nIndex];
}

SMonsterDrop* DropMonsterItemConfig::GetSMonsterDropByMonsterId(int nMonsterId)
{
	if (nMonsterId <= 0) 
	{ return NULL; }

	std::vector<SMonsterDrop>::iterator iter = find(m_vtDropItem.begin(), m_vtDropItem.end(), nMonsterId);

	if (iter != m_vtDropItem.end())
	{
		return &(*iter);
	}

	return NULL;
}
