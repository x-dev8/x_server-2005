#include "tstring.h"
#include "RapidXml/MeRapidXml.h"
#include "ChatChannelConfig.h"

//-------------------------------------------------------------------------------
#define CHATCHANNELCONFIG_XML_DEFAULT "..\\Data\\ClientConfig\\UserSetting.config"
#define XML_ROOT_NAME "Project"
#define XML_CHATCHANNELCONFIG_ROOT_NAME "ChatChannelConfig"
#define XML_CHATCHANNELCONFIG_INFO "ChatChannelInfo"
#define XML_CHATCHANNELCONFIG_INFO_NAME "Name"
#define XML_CHATCHANNELCONFIG_INFO_TYPE "Type"
#define XML_CHATCHANNELCONFIG_INFO_COLOR "Color"
#define XML_CHATCHANNELCONFIG_INFO_CHANNEL "Channel"
#define CHAT_COMMAND_CONFIG "..\\Data\\ClientConfig\\UserSetting.config"
//-------------------------------------------------------------------------------
bool ChatChannelConfig::Load( const char* pszFilename )
{
	m_ChatChannelInfoList.clear();

	MeXmlDocument xmlDoc;
	bool bRet = false;
	if( !pszFilename )
		bRet = xmlDoc.LoadFile( 
		CHATCHANNELCONFIG_XML_DEFAULT );
	else
		bRet = xmlDoc.LoadFile( 
		pszFilename );
	//if there is no custom setting, load the default one.
	if( pszFilename && !bRet )
	{		
		bRet = xmlDoc.LoadFile( 
			CHATCHANNELCONFIG_XML_DEFAULT );
		if( !bRet )
			return false;
	}
	//load root
	MeXmlElement* pRoot = xmlDoc.FirstChildElement( 
		XML_ROOT_NAME );

	if( !pRoot )
		return false;

	pRoot = pRoot->FirstChildElement( XML_CHATCHANNELCONFIG_ROOT_NAME );	

	if( !pRoot )
		return false;

	//load settings
	MeXmlElement* pChatChannel = pRoot->FirstChildElement( XML_CHATCHANNELCONFIG_INFO );
	while ( pChatChannel != NULL )
	{	
		ChatChannelInfo cciInfo;
		// name
		Common::_tstring strName;			
		strName.fromUTF8( pChatChannel->Attribute( XML_CHATCHANNELCONFIG_INFO_NAME ) );
		if ( strName.empty() )
			return false;		
		cciInfo.m_strChannelName = strName;		

		double dTemp = 0;
		// type		
		if( !pChatChannel->Attribute( XML_CHATCHANNELCONFIG_INFO_TYPE, &dTemp ) )
			return false;
		cciInfo.m_dwChannelType = dTemp;

		// color
		if( !pChatChannel->Attribute( XML_CHATCHANNELCONFIG_INFO_COLOR, &dTemp ) )
			return false;
		cciInfo.m_dwChannelColor = dTemp;

        // Channel
        if( !pChatChannel->Attribute( XML_CHATCHANNELCONFIG_INFO_CHANNEL, &dTemp ) )
            return false;
        cciInfo.m_dwDefChannelType = dTemp;

		m_ChatChannelInfoList.push_back( cciInfo );
		
		//next
		pChatChannel = pChatChannel->NextSiblingElement();
	}

	return true;
}
//-------------------------------------------------------------------------------
bool ChatChannelConfig::Save( const char* pszFilename )
{
	MeXmlDocument xmlDoc;
	//header
	xmlDoc.InsertEndChild( MeXmlDeclaration( "1.0","utf-8","yes" ) );

	//root
	MeXmlElement* pRootNode = xmlDoc.InsertEndChild( 
		( XML_ROOT_NAME ) );
	if( !pRootNode )
		return false;

	pRootNode = pRootNode->InsertEndChild( ( XML_CHATCHANNELCONFIG_ROOT_NAME ) );
	if( !pRootNode )
		return false;
	
	ChatChannelInfoList::iterator it = m_ChatChannelInfoList.begin();
	for( ; it != m_ChatChannelInfoList.end(); ++ it )
	{
		MeXmlElement* pInfo = pRootNode->InsertEndChild( ( XML_CHATCHANNELCONFIG_INFO ) );
		if( !pInfo )
			return false;

		MeXmlElement* pElement = pInfo->ToElement();
		if( !pElement )
			return false;

		Common::_tstring strName = (*it).m_strChannelName;
		pElement->SetAttribute( XML_CHATCHANNELCONFIG_INFO_NAME, strName.toUTF8().c_str() );
		double dTemp = (*it).m_dwChannelType;
		pElement->SetAttribute( XML_CHATCHANNELCONFIG_INFO_TYPE, dTemp );
		dTemp = (*it).m_dwChannelColor;
		pElement->SetAttribute( XML_CHATCHANNELCONFIG_INFO_COLOR,dTemp );
        dTemp = (*it).m_dwDefChannelType;
        pElement->SetAttribute( XML_CHATCHANNELCONFIG_INFO_CHANNEL,dTemp );
	}
	xmlDoc.SaveFile( pszFilename );
	return true;
}
//-------------------------------------------------------------------------------
ChatChannelConfig* ChatChannelConfig::Instance()
{
	static ChatChannelConfig cccInstance;
	return &cccInstance;
}
//-------------------------------------------------------------------------------
bool ChatChannelConfig::LoadCommandConfig()
{
	m_ChatCommandInfo.clear();

	MeXmlDocument xmlDoc;
	bool bRet = false;
	bRet = xmlDoc.LoadFile( CHAT_COMMAND_CONFIG );
	if( !bRet )
		return false;

	//load root
	MeXmlElement* pRoot = xmlDoc.FirstChildElement( XML_ROOT_NAME );
	if( !pRoot )
		return false;

	pRoot = pRoot->FirstChildElement( "ChatTypeSetting" );	
	if( !pRoot )
		return false;

	const char* szValue = NULL;
	std::wstring str;
	MeXmlElement* pElem = pRoot->FirstChildElement("ChatTypeInfo");
	for( ; pElem; pElem = pElem->NextSiblingElement() )
	{
		ChatTypeInfo kTypeInfo;
		szValue = pElem->Attribute("Type");
		if( szValue )
		{
			kTypeInfo.strType = szValue;

			szValue = pElem->Attribute("CommandCN");
			if( szValue )
			{
				str = Common::_tstring::UTF8towcs(szValue);
				kTypeInfo.strCommandCn = Common::_tstring::toNarrowString(str.c_str());

				szValue = pElem->Attribute("CommandEN");
				if( szValue )
				{
					kTypeInfo.strCommandEn = szValue;
					m_ChatCommandInfo.push_back(kTypeInfo);
				}
			}
		}
	}

	return true;
}
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
