#include "GuideQuestConfig.h"
#include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#include "tstring.h"

bool GuideQuestConfig::LoadGuideQuestConfig( const char* szFile )
{
    if ( szFile == NULL || szFile[ 0 ] == 0 )
    { return false; }

    m_vecGuildQuest.clear();

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, TIXML_ENCODING_UTF8 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pGuildQuests = pRoot->FirstChildElement( "GuildQuests" );
    if ( pGuildQuests == NULL )
    { return false; }

    MeXmlElement* pQuest = pGuildQuests->FirstChildElement( "Quest" );
    while ( pQuest != NULL )
    {
        GuideQuest xQuest;

        int nType;
        if ( pQuest->Attribute( "Type", &nType ) == NULL )
        { return false; }
        xQuest.SetType( nType );

        Common::_tstring strScript = "";			
        strScript.fromUTF8( pQuest->Attribute( "ScriptFile" ) );
        xQuest.SetScript( strScript.c_str() );

        int nEnter;
        if ( pQuest->Attribute( "Enter", &nEnter ) == NULL )
        { return false; }
        xQuest.SetEnter( nEnter );

        m_vecGuildQuest.push_back( xQuest );

        pQuest = pQuest->NextSiblingElement();
    }

    return true;
}