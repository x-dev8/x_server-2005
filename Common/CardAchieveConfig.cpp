#include "CardAchieveConfig.h"
#include "GlobalDef.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"
#ifndef _CLIENT_
#include "ScriptMgr.h"
#endif //_CLIENT_

CardAchieveConfig::CardAchieveConfig()
{
	m_vecAchieve.resize( More_nCardAchieve );
}

CardAchieveConfig::~CardAchieveConfig()
{
	m_vecAchieve.clear();
}

void CardAchieveConfig::AddData( SData data )
{
	if (data.shID == -1 || data.shID >= More_nCardAchieve)
		return;

	m_vecAchieve[data.shID].shID = data.shID;

	for (int i = 0; i < MAX_CARDIDS; i++)
	{
		m_vecAchieve[data.shID].shCardIDs[i] = data.shCardIDs[i];
	}

	m_vecAchieve[data.shID].unItemID = data.unItemID;
	m_vecAchieve[data.shID].shCardCount = data.shCardCount;

	m_vecAchieve[data.shID].sBrightImg.strImg = data.sBrightImg.strImg;
	m_vecAchieve[data.shID].sBrightImg.nWidth = data.sBrightImg.nWidth;
	m_vecAchieve[data.shID].sBrightImg.nHeight = data.sBrightImg.nHeight;
	m_vecAchieve[data.shID].sBrightImg.nRow = data.sBrightImg.nRow;
	m_vecAchieve[data.shID].sBrightImg.nColumn = data.sBrightImg.nColumn;

	m_vecAchieve[data.shID].sDarkImg.strImg = data.sDarkImg.strImg;
	m_vecAchieve[data.shID].sDarkImg.nWidth = data.sDarkImg.nWidth;
	m_vecAchieve[data.shID].sDarkImg.nHeight = data.sDarkImg.nHeight;
	m_vecAchieve[data.shID].sDarkImg.nRow = data.sDarkImg.nRow;
	m_vecAchieve[data.shID].sDarkImg.nColumn = data.sDarkImg.nColumn;

	m_vecAchieve[data.shID].strName = data.strName;
}

bool CardAchieveConfig::LoadCardAchieveConfig( const char* pszConfig )
{
	if (!pszConfig || *pszConfig == 0)
		return false;

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(pszConfig))
		return false;
	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
		return false;

	MeXmlElement* pAchieves = pRoot->FirstChildElement("Achieves");
	if (!pAchieves)
		return false;

	MeXmlElement* pAchieve = pAchieves->FirstChildElement("Achieve");

	while (pAchieve)
	{
		SData data;

		int nId = -1;
		if (!pAchieve->Attribute("ID", &nId))
			return false;
		data.shID = nId;

		Common::_tstring strCardIds;
		strCardIds.fromUTF8(pAchieve->Attribute("CardIDs"));
		if ( !strCardIds.empty() )
		{
			char *szSpn = ",";
			char *szStr;
			int i = 0;

			szStr = strtok( const_cast<char*>(strCardIds.c_str()),szSpn );
			while( szStr )
			{
				data.shCardIDs[i] = atoi(szStr);
				
				szStr = strtok( NULL,szSpn );
				++i;
			}
			data.shCardCount = i;
		}

		int nItemID = 0;
		pAchieve->Attribute("ItemID", &nItemID);
		data.unItemID = nItemID;

		Common::_tstring strBImg;
		strBImg.fromUTF8( pAchieve->Attribute("BrightImage") );
		data.sBrightImg.strImg = strBImg;

		int nBWidth = 0;
		pAchieve->Attribute("BrightWidth", &nBWidth);
		data.sBrightImg.nWidth = nBWidth;

		int nBHeight = 0;
		pAchieve->Attribute("BrightHeight", &nBHeight);
		data.sBrightImg.nHeight = nBHeight;

		int nBRow = 0;
		pAchieve->Attribute("BrightRow", &nBRow);
		data.sBrightImg.nRow = nBRow;

		int nBColumn = 0;
		pAchieve->Attribute("BrightColumn", &nBColumn);
		data.sBrightImg.nColumn = nBColumn;

		Common::_tstring strDImg;
		strDImg.fromUTF8( pAchieve->Attribute("DarkImage") );
		data.sDarkImg.strImg = strDImg;

		int nDWidth = 0;
		pAchieve->Attribute("DarkWidth", &nDWidth);
		data.sDarkImg.nWidth = nDWidth;

		int nDHeight = 0;
		pAchieve->Attribute("DarkHeight", &nDHeight);
		data.sDarkImg.nHeight = nDHeight;

		int nDRow = 0;
		pAchieve->Attribute("DarkRow", &nDRow);
		data.sDarkImg.nRow = nDRow;

		int nDColumn = 0;
		pAchieve->Attribute("DarkColumn", &nDColumn);
		data.sDarkImg.nColumn = nDColumn;

		data.strName = pAchieve->Attribute("Name");

		Common::_tstring strScriptAddr;
		strScriptAddr.fromUTF8( pAchieve->Attribute("ScriptAddr") );
		data.strScriptAddr = strScriptAddr;

#ifndef _CLIENT_
		if ( data.strScriptAddr.length() > 0 )
			GetScriptMgr()->CreateVM( ST_CARD_ACHIEVE, data.strScriptAddr.c_str(), data.shID );
#endif //_CLIENT_

		AddData(data);

		pAchieve = pAchieve->NextSiblingElement();
	}

	return true;
}