#include "SplitItemConfig.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

#include "ErrorCode.h"
SplitItemConfig& SplitItemConfig::Instance()
{
    static SplitItemConfig instance;
    return instance;
}

uint32 SplitItemConfig::Load( const char* szFileName )
{   
    int nValue = 0;
    if ( szFileName == NULL || szFileName[0] == 0 )
	{ return ER_Failed; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFileName, 1 ) ) 
    { return ER_Failed; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL ) 
    { return ER_Failed; } 

    MeXmlElement* pItems = pRoot->FirstChildElement( "Items" );
    if ( pItems == NULL )
    { return ER_Failed; }

    MeXmlElement* pItem = pItems->FirstChildElement( "Item" );    
    while ( pItem != NULL )
    {
        SSplitItem splitItem;
        if ( pItem->Attribute( "Id", &nValue ) == NULL )
        { return ER_Failed; }
        splitItem.id = nValue;

        MeXmlElement* pProductItem = pItem->FirstChildElement( "ProductItem" );        
        while ( pProductItem != NULL )
        {
            SProductItem productItem;
            pProductItem->Attribute( "Id", &nValue );
            productItem.id = nValue;
            
            pProductItem->Attribute( "Count", &nValue );
            productItem.count = nValue;

            pProductItem->Attribute( "Probability", &nValue );
            productItem.probability = nValue;

            splitItem.products.push_back(  productItem );
           
            pProductItem = pProductItem->NextSiblingElement();
        }

        uint32 nIndex = _splitItems.size();

        _splitItems.push_back( splitItem );

        // ½øÐÐ¼ìË÷¼ÍÂ¼
        bool bResult = _splitItemIndexs.insert( SplitItemIndexContainer::value_type(splitItem.id, nIndex)).second;
        if ( !bResult )
        { return ER_Failed; }

        pItem = pItem->NextSiblingElement();
    }
    return ER_Success;
}

uint32 SplitItemConfig::GetSplitItemAllProduct( uint16 itemId, ProductItemContainer& products )
{
    products.clear();

    ItrSplitItemIndexContainer it = _splitItemIndexs.find( itemId );
    if ( it == _splitItemIndexs.end())
    { return ER_Failed; }

    uint32 index = it->second;
    if ( index >= _splitItems.size() )
    { return ER_Failed; }

    products = _splitItems[index].products;
    return ER_Success;
}

SplitItemConfig::SProductItem* SplitItemConfig::GetSplitItemProduct( uint16 itemId )
{   
    static CIBAA_RandGen xRandGen;

    ItrSplitItemIndexContainer it = _splitItemIndexs.find( itemId );
    if ( it == _splitItemIndexs.end())
    { return NULL; }

    uint32 index = it->second;
    if ( index >= _splitItems.size() )
    { return NULL; }

    ItrProductItemContainer itPro    = _splitItems[index].products.begin();    
    ItrProductItemContainer itProEnd = _splitItems[index].products.end();

    std::map<uint32, uint32> randRange;
    uint32 probabilityNum = 0;
    for ( uint32 i=0; itPro!=itProEnd; ++itPro, ++i )
    {
        probabilityNum += itPro->probability;
        randRange.insert( std::map<uint32, uint32>::value_type( probabilityNum, i ) );
    }

    if ( probabilityNum == 0)
    { return NULL; }

    uint32 randNum = xRandGen.rand32() % probabilityNum;
    std::map<uint32, uint32>::iterator itRand = randRange.upper_bound( randNum );
    if ( itRand == randRange.end() )
    { return NULL;}

    uint32 targetIndex = itRand->second;
    if ( targetIndex >= _splitItems[index].products.size() )
    { return NULL; }
    
    return &_splitItems[index].products[targetIndex];
}

bool SplitItemConfig::IsHaveSplitItemInfo( uint16 itemId )
{
    ItrSplitItemIndexContainer it = _splitItemIndexs.find( itemId );
    if ( it == _splitItemIndexs.end())
    { return false; }

    return true;
}
