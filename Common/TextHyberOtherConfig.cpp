#include "TextHyberOtherConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "Mertlibs.h"
#include "tstring.h"
TextHyberOtherConfig::TextHyberOtherConfig()
{

}
TextHyberOtherConfig::~TextHyberOtherConfig()
{

}
bool TextHyberOtherConfig::LoadTextHyberOtherConfig(const char* FilePath)
{
	if ( FilePath == NULL || FilePath[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( FilePath, 1 ) )
    { return false; }

    MeXmlElement* pTo = xMeXml.FirstChildElement( "TextHyberOther" );
    if ( pTo == NULL )
    { return false; }

	MeXmlElement* pUI = pTo->FirstChildElement( "UI" );
    while ( pUI != NULL )
    {
		Common::_tstring strScriptAddr;
		strScriptAddr.fromUTF8( pUI->Attribute("Name") );
		std::string Name =strScriptAddr.c_str();

		int ID;
		if ( pUI->Attribute( "UiID", &ID ) == NULL )
			return false;

		m_Info.insert(std::map<std::string,int>::value_type(Name,ID));

		pUI = pUI->NextSiblingElement();
	}
	return true;
}
int TextHyberOtherConfig::GetUIID(std::string Name)
{
	if(m_Info.empty())
		return 0;
	if(m_Info.count(Name) != 1)
		return 0;
	return m_Info[Name];
}