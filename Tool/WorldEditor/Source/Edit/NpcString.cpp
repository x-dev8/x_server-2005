#include "NpcString.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"

CNpcString::CNpcString(void)
{
	Clear();
}

CNpcString::~CNpcString(void)
{
	Clear();
}

bool CNpcString::LoadConfig(const char* pszPath)
{
	assert(pszPath != NULL);
	if(NULL == pszPath)
		return false;

	MeXmlDocument tiXDoc;
	
	if(!tiXDoc.LoadFile(pszPath))
	{
		return false;
	}

	MeXmlElement *pMeXmlElement = NULL;
	pMeXmlElement = tiXDoc.FirstChildElement("Project");
	if(pMeXmlElement == NULL)
		return false;


	pMeXmlElement = pMeXmlElement->FirstChildElement("Strings");
	if(pMeXmlElement == NULL)
		return false;

	pMeXmlElement = pMeXmlElement->FirstChildElement("String");

	for (;pMeXmlElement != NULL;pMeXmlElement = pMeXmlElement->NextSiblingElement())
	{
		npcTalk cNpcTalk;

		pMeXmlElement->Attribute("Id",&cNpcTalk.m_Id);

		Common::_tstring str;
		str.fromUTF8(pMeXmlElement->Attribute("Value"));
		cNpcTalk.m_strTalk = str;

		m_TalkSet.insert(make_pair(cNpcTalk.m_Id,cNpcTalk));
	}
	return true;
}

bool CNpcString::LoadConfigForMenu(const char* pszPath)
{
    assert(pszPath != NULL);
    if(NULL == pszPath)
        return false;

    MeXmlDocument tiXDoc;

    if(!tiXDoc.LoadFile(pszPath))
    {
        return false;
    }

    MeXmlElement *pMeXmlElement = NULL;
    pMeXmlElement = tiXDoc.FirstChildElement("Project");
    if(pMeXmlElement == NULL)
        return false;


    pMeXmlElement = pMeXmlElement->FirstChildElement("Strings");
    if(pMeXmlElement == NULL)
        return false;

    pMeXmlElement = pMeXmlElement->FirstChildElement("String");

    for (;pMeXmlElement != NULL;pMeXmlElement = pMeXmlElement->NextSiblingElement())
    {
        npcTalk cNpcTalk;

        pMeXmlElement->Attribute("Id",&cNpcTalk.m_Id);

        Common::_tstring str;
        str.fromUTF8(pMeXmlElement->Attribute("Value"));
        cNpcTalk.m_strTalk = str;

        m_TalkSetForNpcMenu.insert(make_pair(cNpcTalk.m_Id, cNpcTalk));
    }
    return true;
}

void CNpcString::Clear()
{
	m_TalkSet.clear();
}

CNpcString::npcTalk* CNpcString::GetDataByID(const int Id)
{
	NPCTALKSET::iterator it = m_TalkSet.find(Id);
	if( it != m_TalkSet.end())
	{
		return &(it->second);
	}
	return 0;
}

CNpcString::npcTalk* CNpcString::GetDataByIDForMenu(const int Id)
{
    NPCTALKSET::iterator it = m_TalkSetForNpcMenu.find(Id);
    if ( it != m_TalkSetForNpcMenu.end() )
    {
        return &(it->second);
    }
    return 0;
}


void CNpcString::InsertData(npcTalk cNpcTalk)
{
	m_TalkSet.insert(make_pair(cNpcTalk.m_Id,cNpcTalk));
}

void CNpcString::DelData(int nID)
{
	NPCTALKSET::iterator it = m_TalkSet.find(nID);
	if(it != m_TalkSet.end())
		m_TalkSet.erase(it);
}

bool CNpcString::SaveConfig(const char* pszPath)
{
	assert(pszPath != NULL);
	if(NULL == pszPath)
		return false;

	MeXmlDocument xMeXmlDoc;
	xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));
	MeXmlElement *pRoot = xMeXmlDoc.InsertEndChild(("Project"))->ToElement();
	if(NULL == pRoot)
		return false;

	Common::_tstring strName = "HeroOnline";

	pRoot->SetAttribute("Name",strName.toUTF8().c_str());
	pRoot->SetAttribute("Version","");

	MeXmlElement *pItem = pRoot->InsertEndChild(("Strings"))->ToElement();
	if(NULL == pItem)
		return false;

	NPCTALKSET::iterator iter = m_TalkSet.begin();
	NPCTALKSET::iterator end = m_TalkSet.end();

	for (;iter != end; ++iter)
	{
		MeXmlElement *pString = pItem->InsertEndChild(("String"))->ToElement();

		if(NULL == pString)
			continue;

		pString->SetAttribute("Id",iter->second.m_Id);

		Common::_tstring name = iter->second.m_strTalk;
		pString->SetAttribute("Value",name.toUTF8().c_str());
	}

	return xMeXmlDoc.SaveFile(pszPath);
}

bool CNpcString::SaveConfigForMenu(const char* pszPath)
{
    assert(pszPath != NULL);
    if(NULL == pszPath)
        return false;

    MeXmlDocument xMeXmlDoc;
    xMeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));
    MeXmlElement *pRoot = xMeXmlDoc.InsertEndChild(("Project"))->ToElement();
    if(NULL == pRoot)
        return false;

    Common::_tstring strName = "HeroOnline";

    pRoot->SetAttribute("Name",strName.toUTF8().c_str());
    pRoot->SetAttribute("Version","");

    MeXmlElement *pItem = pRoot->InsertEndChild(("Strings"))->ToElement();
    if(NULL == pItem)
        return false;

    NPCTALKSET::iterator iter = m_TalkSetForNpcMenu.begin();
    NPCTALKSET::iterator end  = m_TalkSetForNpcMenu.end();

    for (;iter != end; ++iter)
    {
        MeXmlElement *pString = pItem->InsertEndChild(("String"))->ToElement();

        if(NULL == pString)
            continue;

        pString->SetAttribute("Id",iter->second.m_Id);

        Common::_tstring name = iter->second.m_strTalk;
        pString->SetAttribute("Value",name.toUTF8().c_str());
    }

    return xMeXmlDoc.SaveFile(pszPath);
}