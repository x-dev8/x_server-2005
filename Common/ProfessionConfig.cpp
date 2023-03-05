#include "ProfessionConfig.h"
#include "tstring.h"
#include "RapidXml/MeRapidXml.h"
#include "application_config.h"

ProfessionConfig::ProfessionConfig()
{
	m_vecProfession.clear();
}

ProfessionConfig::~ProfessionConfig()
{

}


bool ProfessionConfig::LoadProfessionConfig(const char* szFile)
{
	if (szFile == NULL || *szFile == 0)
	{ return false;	}

	m_vecProfession.clear();

	m_vecProfession.resize ( EProfession_MaxNumLimit );

	MeXmlDocument xMeXml;
	if (!xMeXml.LoadFile( szFile ))
	{ return false; }

	MeXmlElement* pRoot = xMeXml.FirstChildElement("Project");
	if (pRoot == NULL )
	{ return false; }

	//////////////////////////////////////////////////////////////////////////
	//  ¼ÓÔØÖ°Òµ
	MeXmlElement* pProfessions = pRoot->FirstChildElement("Professions");
	if (pProfessions == NULL) 
	{ return false; }

	int iValue;

	MeXmlElement* pProfessionElement = pProfessions->FirstChildElement("Profession");
	while (pProfessionElement != NULL)
	{	
		Profession xProfession;

		pProfessionElement->Attribute("ID", &iValue);
		xProfession.nID = iValue;

		pProfessionElement->Attribute("Level", &iValue);
		xProfession.nLevel= iValue;

		Common::_tstring strName;
		strName.fromUTF8( pProfessionElement->Attribute("Name") );
		xProfession.strName = strName;

		pProfessionElement->Attribute("PrevID", &iValue);
		xProfession.nPrevID = iValue;

        m_vecProfession[xProfession.nID] = xProfession;

		//next
		pProfessionElement = pProfessions->NextSiblingElement();
	}

	return true;
}
