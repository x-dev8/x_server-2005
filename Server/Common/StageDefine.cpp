#include "StageDefine.h"

LandStageConfig::LandStageConfig() : IOXMLObjectInstance( "Land" ), m_nWidth( 0 ), m_nHeight( 0 ), m_bLoaded ( false )
{
    m_nWidth = 0;
    m_nHeight = 0;
    m_bLoaded = FALSE;

    m_vecReplaceMap.clear();
}

LandStageConfig::~LandStageConfig() 
{
}

bool LandStageConfig::loadXMLSettings( const char *szPath )
{
    m_bLoaded = TRUE;
    bool bSucess = IOXMLObjectInstance::loadXMLSettings( szPath );
    return bSucess;
}

bool LandStageConfig::loadXMLSettings( XMLElement *pParentElement )
{
    if( !isSuitable( pParentElement ) )
    { return false; }

    XMLElement* pElement = pParentElement->getChildByName( "Width" );
    if( pElement != NULL )
    { m_nWidth = pElement->getValuei(); }

    pElement = pParentElement->getChildByName( "Height" );
    if( pElement != NULL )
    { m_nHeight = pElement->getValuei(); }

    for( size_t i = 0; i < pParentElement->getChildrenCount(); ++i )
    {
        XMLElement *pChild = pParentElement->getChild( i );
        if( pChild->getName() == "Replace" )
        {
            ReadReplaceMap( pChild );
            continue;
        }
    }

    return true;    
}

bool LandStageConfig::ReadReplaceMap( XMLElement *pElement )
{
    if ( pElement == NULL )
    { return false; }

    if( pElement->getName() != "Replace" )
    { return true; }

    XMLElement *pChild = NULL;
    ReplaceMap xReplaceMap;

    if( pChild = pElement->getChildByName( "Name" ) )
    { strncpy( xReplaceMap.m_szName, pChild->getValue().c_str(), sizeof( xReplaceMap.m_szName ) - 1 ); }

    if( pChild = pElement->getChildByName( "BeginX" ) )
    { xReplaceMap.m_nBeginX = pChild->getValuei(); }

    if( pChild = pElement->getChildByName( "BeginY" ) )
    { xReplaceMap.m_nBeginY = pChild->getValuei(); }

    if( pChild = pElement->getChildByName( "EndX" ) )
    { xReplaceMap.m_nEndX = pChild->getValuei(); }

    if( pChild = pElement->getChildByName( "EndY" ) )
    { xReplaceMap.m_nEndY = pChild->getValuei(); }

    if( pChild = pElement->getChildByName( "ReplaceX" ) )
    { xReplaceMap.m_nReplaceX = pChild->getValuei(); }


    if( pChild = pElement->getChildByName( "ReplaceY" ) )
    { xReplaceMap.m_nReplaceY = pChild->getValuei(); }

    if( pChild = pElement->getChildByName("ReplaceEndX") )
    { xReplaceMap.m_nReplaceEndX = pChild->getValuei(); }

    if( pChild = pElement->getChildByName("ReplaceEndY") )
    { xReplaceMap.m_nReplaceEndY = pChild->getValuei(); }

    m_vecReplaceMap.push_back( xReplaceMap );
    return true;
}

bool LandStageConfig::exportXMLSettings( std::ofstream &xmlFile )
{
    return true;
}

bool LandStageConfig::exportXMLSettings( const char* xmlPath )
{
    return true;
}

bool LandStageConfig::IsReplaceMap( INT nX, INT nY, char *szFile, unsigned int szFileLength )
{
    for ( ReplaceMapVectorIter iter = m_vecReplaceMap.begin(); iter != m_vecReplaceMap.end(); ++iter )
    {  
        RECT xRect = { 0 };
        SetRect( &xRect, iter->m_nReplaceX, iter->m_nReplaceY, iter->m_nReplaceEndX, iter->m_nReplaceEndY );
        
        POINT xPoint;
        xPoint.x = nX;
        xPoint.y = nY;
        if( !PtInRect( &xRect, xPoint ) )
        { continue; }

        int nReplaceX = nX + iter->m_nBeginX - iter->m_nReplaceX;
        int nReplaceY = nY + iter->m_nBeginY - iter->m_nReplaceY;

        char szCurMapName[260] = { 0 };
        sprintf_s( szCurMapName, sizeof( szCurMapName )-1, "%s_%d_%d", iter->m_szName, nReplaceX, nReplaceY );
        sprintf_s( szFile, szFileLength-1, "data\\world\\%s\\%s\\%s.monstercfg.xml",  iter->m_szName, szCurMapName, szCurMapName );
        return true;
    }

    return false;
}
