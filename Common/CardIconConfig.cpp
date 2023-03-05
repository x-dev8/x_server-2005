#include "CardIconConfig.h"
#include "GlobalDef.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"

CardIconConfig::CardIconConfig()
{
	m_vecCard.resize( More_nCardMax );
}

CardIconConfig::~CardIconConfig()
{
	m_vecCard.clear();
}

void CardIconConfig::AddData( SCard card )
{
	if (card.shID == -1 || card.shID >= More_nCardMax)
		return;

	m_vecCard[card.shID].shID = card.shID;

	for (int i = 0; i < ECT_MaxID; i++)
	{
		m_vecCard[card.shID].unTypeID[i] = card.unTypeID[i];
	}

	m_vecCard[card.shID].nLevel = card.nLevel;
	m_vecCard[card.shID].type = card.type;

	m_vecCard[card.shID].sBrightImg.strImg = card.sBrightImg.strImg;
	m_vecCard[card.shID].sBrightImg.nWidth = card.sBrightImg.nWidth;
	m_vecCard[card.shID].sBrightImg.nHeight = card.sBrightImg.nHeight;
	m_vecCard[card.shID].sBrightImg.nRow = card.sBrightImg.nRow;
	m_vecCard[card.shID].sBrightImg.nColumn = card.sBrightImg.nColumn;

	m_vecCard[card.shID].sDarkImg.strImg = card.sDarkImg.strImg;
	m_vecCard[card.shID].sDarkImg.nWidth = card.sDarkImg.nWidth;
	m_vecCard[card.shID].sDarkImg.nHeight = card.sDarkImg.nHeight;
	m_vecCard[card.shID].sDarkImg.nRow = card.sDarkImg.nRow;
	m_vecCard[card.shID].sDarkImg.nColumn = card.sDarkImg.nColumn;

	m_vecCard[card.shID].strName = card.strName;
}

bool CardIconConfig::LoadCardIconConfig( const char* pszConfig )
{
	if (!pszConfig || *pszConfig == 0)
		return false;

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile(pszConfig))
		return false;
	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (!pRoot)
		return false;

	MeXmlElement* pCards = pRoot->FirstChildElement("Cards");
	if (!pCards)
		return false;
	MeXmlElement* pCard = pCards->FirstChildElement("Card");

	while (pCard)
	{
		SCard card;

		int nId = -1;
		if (!pCard->Attribute("ID", &nId))
			return false;
		card.shID = nId;

		int nTypeID1 = 0;
		if (!pCard->Attribute("TypeID1", &nTypeID1))
			return false;
		card.unTypeID[0] = nTypeID1;

		int nTypeID2 = 0;
		pCard->Attribute("TypeID2", &nTypeID2);
		card.unTypeID[1] = nTypeID2;

		int nTypeID3 = 0;
		pCard->Attribute("TypeID3", &nTypeID3);
		card.unTypeID[2] = nTypeID3;

		int nTypeID4 = 0;
		pCard->Attribute("TypeID4", &nTypeID4);
		card.unTypeID[3] = nTypeID4;

		int nTypeID5 = 0;
		pCard->Attribute("TypeID5", &nTypeID5);
		card.unTypeID[4] = nTypeID5;

		int nLevel = -1;
		if (!pCard->Attribute("Level", &nLevel))
			return false;
		card.nLevel = nLevel;

		int nType = 3;
		ECardType eType = ECT_TypeNull;
		if (!pCard->Attribute("Type", &nType))
			return false;

		switch (nType)
		{
		case 0:
			eType = ECT_Pet;
			break;
		case 1:
			eType = ECT_Hero;
			break;
		case 2:
			eType = ECT_Mount;
			break;
		default:
			eType = ECT_TypeNull;
			break;
		}
		card.type = eType;

		Common::_tstring strBImg;
		strBImg.fromUTF8( pCard->Attribute("BrightImage") );
		card.sBrightImg.strImg = strBImg;

		int nBWidth = 0;
		pCard->Attribute("BrightWidth", &nBWidth);
		card.sBrightImg.nWidth = nBWidth;

		int nBHeight = 0;
		pCard->Attribute("BrightHeight", &nBHeight);
		card.sBrightImg.nHeight = nBHeight;

		int nBRow = 0;
		pCard->Attribute("BrightRow", &nBRow);
		card.sBrightImg.nRow = nBRow;

		int nBColumn = 0;
		pCard->Attribute("BrightColumn", &nBColumn);
		card.sBrightImg.nColumn = nBColumn;

		Common::_tstring strDImg;
		strDImg.fromUTF8( pCard->Attribute("DarkImage") );
		card.sDarkImg.strImg = strDImg;

		int nDWidth = 0;
		pCard->Attribute("DarkWidth", &nDWidth);
		card.sDarkImg.nWidth = nDWidth;

		int nDHeight = 0;
		pCard->Attribute("DarkHeight", &nDHeight);
		card.sDarkImg.nHeight = nDHeight;

		int nDRow = 0;
		pCard->Attribute("DarkRow", &nDRow);
		card.sDarkImg.nRow = nDRow;

		int nDColumn = 0;
		pCard->Attribute("DarkColumn", &nDColumn);
		card.sDarkImg.nColumn = nDColumn;

		//std::wstring strName;
		//strName = Common::_tstring::UTF8towcs( pCard->Attribute("Name") );
		//card.strName = Common::_tstring::toNarrowString(strName.c_str());
		card.strName = pCard->Attribute("Name");

		AddData(card);

		pCard = pCard->NextSiblingElement();
	}

	return true;
}

short CardIconConfig::GetCardIdByTypeId( uint32 typeId )
{
	if ( typeId <= 0 )
		return -1;

	int nSize = m_vecCard.size();
	for (int i = 0; i < nSize; i++)
	{
		if ( m_vecCard[i].shID == -1 )
			continue;

		for (int j = 0; j < ECT_MaxID; j++)
		{
			if ( m_vecCard[i].unTypeID[j] == typeId )
				return m_vecCard[i].shID;
		}
	}

	return -1;
}