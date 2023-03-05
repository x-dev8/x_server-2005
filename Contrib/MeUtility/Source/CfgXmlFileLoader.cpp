#include "CfgXmlFileLoader.h"
#include "tstring.h"

bool CCfgXmlFileLoader::GetAttributeFloat( TiXmlElement* pElement, const char* pszName, float& fValue )
{
	if( !pElement )
		return false;
	int nResult = pElement->QueryFloatAttribute( pszName, &fValue );
	return ( nResult == TIXML_SUCCESS );

}
bool CCfgXmlFileLoader::GetAttributeInt( TiXmlElement* pElement, const char* pszName, DWORD& dwValue )
{
	if( !pElement )
		return false;
	int nResult = pElement->QueryIntAttribute( pszName, (int*)&dwValue );
	return ( nResult == TIXML_SUCCESS );

}
bool CCfgXmlFileLoader::GetAttributeInt( TiXmlElement* pElement, const char* pszName, int& nValue )
{
	if( !pElement )
		return false;
	int nResult = pElement->QueryIntAttribute( pszName, &nValue );
	return ( nResult == TIXML_SUCCESS );

}
bool CCfgXmlFileLoader::GetAttributeString( TiXmlElement* pElement, const char* pszName, std::string& strValue )
{
	strValue.clear();
	if( !pElement )
		return false;

	const char* pszTemp = pElement->Attribute( pszName );
	if( !pszTemp )
		return false;
	strValue = Common::_tstring::toNarrowString(Common::_tstring::UTF8towcs(pszTemp).c_str());
	return true;	
}