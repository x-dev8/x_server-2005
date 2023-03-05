
#include "softKeyboard_configure.h"
#include "FuncPerformanceLog.h"
#include "RapidXml/MeRapidXml.h"

#define SOFTKEYBOARD_CONFIGURE_PATH "CONFIG\\softKeyboard.xml"

CSoftKeyboard_configure g_SoftKeyboard_configure;

CSoftKeyboard_configure::CSoftKeyboard_configure()
{
	_keyInfoMap.clear();
}

CSoftKeyboard_configure::~CSoftKeyboard_configure()
{

}

void CSoftKeyboard_configure::load()
{
	guardfunc;
	
	MeXmlDocument	doc;
	if( !doc.LoadFile(SOFTKEYBOARD_CONFIGURE_PATH) )
	{
		assert(false && "softKeyboard.cpp::load 读取文件不错");
		return;
	}

// 	MeXmlHandle hDoc(&doc);

	int id = 0;
	const char* szValue = NULL;
	const char* szID = NULL;
	const char* szValueCaps = NULL;
	uiBtns_Info	btnInfo;

	MeXmlElement* pElem = doc.FirstChildElement("root")->FirstChildElement("ui_buttons")->FirstChildElement("btn");
	for( ; pElem; pElem = pElem->NextSiblingElement() )
	{
		szID = pElem->Attribute("id");
		szValue = pElem->Attribute("vaule");
		szValueCaps = pElem->Attribute("vauleCaps");

		if( szValue && szValueCaps ) 
		{
			btnInfo._value = szValue;
			btnInfo._valueCaps = szValueCaps;
			_uiBtnsIndexMap[szID] = btnInfo;
		}
	}

	pElem = doc.FirstChildElement("root")->FirstChildElement("softKeyboard")->FirstChildElement("key");
	for( ; pElem; pElem = pElem->NextSiblingElement() )
	{
		pElem->QueryIntAttribute("id", &id);
		szValue = pElem->Attribute("value");
		if( szValue )
		{
			_keyInfoMap[id] = szValue;
		}
	}

	unguard;
}