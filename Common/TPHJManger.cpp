#include "TPHJManger.h"
#include "RapidXml\MeRapidXml.h"
#include "tstring.h"
#include "ItemDetail.h"

CTPHJManger::CTPHJManger()
{
	m_max_rank = 0;
	_mapTPHJ.clear();
	m_setMapNoEnter.clear();
}

CTPHJManger::~CTPHJManger()
{
	_mapTPHJ.clear();
	m_setMapNoEnter.clear();
}

bool CTPHJManger::MapCanEnterTphj(int nMapID)
{
	set<int>::iterator iter = m_setMapNoEnter.find(nMapID);
	if (iter!=m_setMapNoEnter.end())
	{
		return false;
	}
	return true;
}

bool CTPHJManger::LoadConifg(const char* szFileName,bool server_or_client)
{	
	if (szFileName == NULL)
	{ return false; }

	MeXmlDocument mMeXmlDoc;
	if (!mMeXmlDoc.LoadFile(szFileName))
	{ return false; }

	MeXmlElement *pRoot = mMeXmlDoc.FirstChildElement("Project");
	if (pRoot == NULL)
	{ return false; }

	MeXmlElement *pRandomTree = pRoot->FirstChildElement("TPHJ");
	if (pRandomTree == NULL)
	{ return false; }

	//int mapID = 0;
	//if ( pRandomTree->Attribute( "mapid", &mapID ) == NULL )
	//{ return false; }
	//m_mapid = mapID;
	//float posx = 0;
	//if ( pRandomTree->Attribute( "posx", &posx ) == NULL )
	//{ return false; }
	//m_posx = posx;
	//float posy = 0;
	//if ( pRandomTree->Attribute( "posy", &posy ) == NULL )
	//{ return false; }
	//m_posy = posy;
	//float direction = 0;
	//if ( pRandomTree->Attribute( "posz", &direction ) == NULL )
	//{ return false; }
	//m_direction = direction;
	int rankmax = 0;
	if ( pRandomTree->Attribute( "rankmax", &rankmax ) == NULL )
	{ return false; }
	m_max_rank = rankmax;
	Common::_tstring strDefaultTip;
	strDefaultTip.fromUTF8(pRandomTree->Attribute("defaultTip"));
	m_tip =strDefaultTip;

	//std::string strMapNoEnter= pRandomTree->Attribute("mapNoEnter");
	char* strMapNoEnter = const_cast<char*>(pRandomTree->Attribute("mapNoEnter"));
	if (strMapNoEnter)
	{
		char* pTemp = strtok(strMapNoEnter,",");
		while (pTemp)
		{
			int nNoEnterMapID = atoi(pTemp);
			m_setMapNoEnter.insert(nNoEnterMapID);
			pTemp = strtok(NULL,",");
		}
	}

	MeXmlElement *pRankElement = pRandomTree->FirstChildElement("TPHJRank");
	if (pRankElement == NULL)
	{ return false; }

	int iValue = 0;

	while ( pRankElement != NULL )
	{
		STPHJ pRank;// = (STPHJ *)GettheItemDetail().AllocItem( 0, sizeof(STPHJ) );
		//if( pRank == NULL )
		//{ return false; }

		if( pRankElement->Attribute("rank", &iValue) == NULL )
		{ return false; }
		pRank.rank = iValue;

		Common::_tstring strFuse;
		strFuse.fromUTF8(pRankElement->Attribute("pic"));
		pRank.rank_pic =strFuse;

		Common::_tstring strFic;
		strFic.fromUTF8(pRankElement->Attribute("graypic"));
		pRank.gray_pic =strFic;

		Common::_tstring strTip;
		strTip.fromUTF8(pRankElement->Attribute("tip"));
		pRank.tip =strTip;

		int mapID = 0;
		if ( pRankElement->Attribute( "mapid", &mapID ) == NULL )
		{ return false; }
		pRank.map_id = mapID;
		float posx = 0;
		if ( pRankElement->Attribute( "posx", &posx ) == NULL )
		{ return false; }
		pRank.posX = posx;
		float posy = 0;
		if ( pRankElement->Attribute( "posy", &posy ) == NULL )
		{ return false; }
		pRank.posY = posy;
		float direction = 0;
		if ( pRankElement->Attribute( "posz", &direction ) == NULL )
		{ return false; }
		pRank.posZ = direction;
		
		// ¼ÓÈë²éÕÒ
		_mapTPHJ.insert( make_pair(pRank.rank,pRank) ); 

		pRankElement = pRankElement->NextSiblingElement();
	}

	return true;
}

CTPHJManger::STPHJ* CTPHJManger::FindTPHJRankByRankID(const char cRankID)
{
	if (cRankID>0 && cRankID<=m_max_rank)
	{
		mapTPHJ::iterator iter = _mapTPHJ.find(cRankID);
		if (iter == _mapTPHJ.end())
		{
			return NULL;
		}
		return &(iter->second);
	}
	return NULL;
}