#include "GameStageConfig.h"
#include "tstring.h"
#include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"


bool GameStageConfig::LoadGameStageConfig( const char* pszFile )
{
    if ( pszFile == NULL || *pszFile == 0 )
    { return false; }

    m_mapStageData.clear();

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( pszFile, TIXML_ENCODING_UTF8 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pGameStages = pRoot->FirstChildElement( "GameStages" );
    if ( pGameStages == NULL ) 
    { return false; }

    MeXmlElement* pGameStage = pGameStages->FirstChildElement( "GameStage" );
    while ( pGameStage != NULL ) 
    {
        StageData xData;

        int nMapID;
        if ( pGameStage->Attribute( "MapId", &nMapID ) == NULL || nMapID < 0 )
        { return false; }
        xData.SetMapID( nMapID );

        Common::_tstring strScriptFile = "";
        strScriptFile.fromUTF8( pGameStage->Attribute( "ScriptFile" ) );
        xData.SetScriptFile( strScriptFile.c_str() );

        MeXmlElement* pStage = pGameStage->FirstChildElement( "Stage" );
        while ( pStage != NULL )
        {
            StageData::StageInfo xInfo;

            int nStage;
            if ( pStage->Attribute( "Value", &nStage ) == NULL || nStage < 0 )
            { return false; }
            xInfo.SetStage( nStage );

            int nSecond;
            if ( pStage->Attribute( "Second", &nSecond ) == NULL || nSecond == 0 )
            { return false; }
            xInfo.SetSecond( nSecond );

            Common::_tstring strString = "";
            strString.fromUTF8( pStage->Attribute( "String" ) );
            xInfo.SetString( strString.c_str() );

            if ( !xData.AddStageInfo( xInfo ) )
            { return false; }

            pStage = pStage->NextSiblingElement();
        }

        if ( !AddStageData( xData ) )
        { return false; }

        pGameStage = pGameStage->NextSiblingElement();
    }

    return true;
}