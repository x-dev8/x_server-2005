#include "KillMonsterCountConfig.h"
// #include <tinyxml/tinyxml.h>
#include "RapidXml\MeRapidXml.h"

bool KillMonsterCount::LoadKillMonsterCountConfig( const char* szFile )
{
    m_mapKillCount.clear();

    if ( szFile == NULL || *szFile == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pKillMonsterCount = pRoot->FirstChildElement( "KillMonsterCount" );
    if ( pKillMonsterCount == NULL )
    { return false; }

    MeXmlElement* pKillMonster = pKillMonsterCount->FirstChildElement( "KillMonster" );
    while ( pKillMonster != NULL )
    {
        int nCount;
        if ( pKillMonster->Attribute( "Count", &nCount ) == NULL || nCount == 0 )
        { return false; }

        double fModulus;
        if ( pKillMonster->Attribute( "Modulus", &fModulus ) == NULL )
        { return false; }

        if ( !AddModulus( nCount, static_cast< float >( fModulus ) ) )
        { return false; }

        pKillMonster = pKillMonster->NextSiblingElement();
    }

    if ( m_mapKillCount.empty() )
    { return false; }

    KillCountMapIter iter = m_mapKillCount.begin();
    m_ustMaxCount = iter->first;
    m_fMinModulus = iter->second;

    iter = m_mapKillCount.end();
    --iter;

    m_ustMinCount = iter->first;
    m_fMaxModulus = 1.0f;

    return true;
}