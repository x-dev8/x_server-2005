#pragma once

#include "tinyxml/tinyxml.h"
#include "MeRTLibs.h"

class CCfgXmlFileLoader
{
public:
	CCfgXmlFileLoader(){}
	~CCfgXmlFileLoader(){}

	bool GetAttributeFloat( TiXmlElement* pElement, const char* pszName, float& fValue );
	bool GetAttributeInt( TiXmlElement* pElement, const char* pszName, int& nValue );
	bool GetAttributeInt( TiXmlElement* pElement, const char* pszName, DWORD& dwValue );
	bool GetAttributeString( TiXmlElement* pElement, const char* pszName, std::string& strValue );	

protected:
	TiXmlDocument m_doc;
};
