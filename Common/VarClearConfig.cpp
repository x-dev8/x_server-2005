#include "VarClearConfig.h"
#include "RapidXml/MeRapidXml.h"

VarClearConfig::VarClearConfig()
{
    m_mapPlayerVar.clear();
    m_mapGuildVar.clear();
}

bool VarClearConfig::LoadConfig( const char* szFile )
{
    if ( szFile == NULL || szFile[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pPlayerVars = pRoot->FirstChildElement( "PlayerVars" );
    if ( pPlayerVars == NULL )
    { return false; }

    m_mapPlayerVar.clear();
    MeXmlElement* pPlayerVar = pPlayerVars->FirstChildElement( "Var" );
    while ( pPlayerVar != NULL )
    {
        int nTimeVar;
        if ( pPlayerVar->Attribute( "TimeVar", &nTimeVar ) == NULL )
        { return false; }

        int nClearVar;
        if ( pPlayerVar->Attribute( "ClearVar", &nClearVar ) == NULL )
        { return false; }

        AddPlayerVar( nTimeVar, nClearVar );

        pPlayerVar = pPlayerVar->NextSiblingElement();
    }

    MeXmlElement* pGuildVars = pRoot->FirstChildElement( "GuildVars" );
    if ( pGuildVars == NULL )
    { return false; }

    m_mapGuildVar.clear();
    MeXmlElement* pGuildVar = pGuildVars->FirstChildElement( "Var" );
    while ( pGuildVar != NULL )
    {
        int nTimeVar;
        if ( pGuildVar->Attribute( "TimeVar", &nTimeVar ) == NULL )
        { return false; }

        int nClearVar;
        if ( pGuildVar->Attribute( "ClearVar", &nClearVar ) == NULL )
        { return false; }

        AddGuildVar( nTimeVar, nClearVar );

        pGuildVar = pGuildVar->NextSiblingElement();
    }

    return true;
}