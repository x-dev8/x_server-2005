#include "TreasureBoxConfig.h"
#include <functional>
#include <algorithm>
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

unsigned char TreasureData::m_uchMaxIndex = ECD_Max_TreasureCount;

bool TreasureBoxConfig::Initialize()
{
    if ( m_uchMaxBoxLevel < 0 || TreasureData::GetMaxIndex() < 0 )
    { return false; }

    m_vecTreasureData.clear();
    m_vecTreasureData.resize( m_uchMaxBoxLevel + 1 );

    m_vecProbability.clear();
    m_vecProbability.resize( m_uchMaxBoxLevel + 1 );

    m_vecSpecificValue.clear();
    m_vecSpecificValue.resize( m_uchMaxBoxLevel + 1 );
    
    return true;
}

bool TreasureBoxConfig::AddTreasureData( unsigned char uchLevel, unsigned short ustItemID, TreasureData& xData )
{
    if ( uchLevel < ECD_Min_BoxLevel || uchLevel > m_uchMaxBoxLevel || ustItemID == 0 || xData.IsError() )
    { return false; }

    DataMap& xDataMap = m_vecTreasureData[uchLevel];
    DataMapIter iter = xDataMap.find( ustItemID );
    if ( iter == xDataMap.end() )
    {
        DataVector vecDataVector;
        vecDataVector.resize( TreasureData::GetMaxIndex() );

        vecDataVector[xData.GetIndex()] = xData;

        xDataMap.insert( make_pair( ustItemID, vecDataVector ) );
    }
    else
    {
        if ( iter->second.at( xData.GetIndex() ).GetItemID() != 0 )
        { return false; }

        iter->second[xData.GetIndex()] = xData;
    }

    return true;
}

bool TreasureBoxConfig::AddProbability( unsigned char uchLevel, unsigned short ustItemID, unsigned int nProbability )
{
    if ( uchLevel < ECD_Min_BoxLevel || uchLevel > m_uchMaxBoxLevel || ustItemID == 0 )
    { return false; }

    ProbabilityMap& xProbabilityMap = m_vecProbability[uchLevel];
    ProbabilityMapIter iter = xProbabilityMap.find( ustItemID );
    if ( iter == xProbabilityMap.end() )
    {
        xProbabilityMap.insert( std::make_pair( ustItemID, nProbability ) );
    }
    else
    {
        iter->second += nProbability;
    }

    return true;
}

bool TreasureBoxConfig::AddSpecificValue( unsigned char uchLevel, unsigned short ustItemID, unsigned int nSpecificValue )
{
    if ( uchLevel < ECD_Min_BoxLevel || uchLevel > m_uchMaxBoxLevel || ustItemID == 0 || nSpecificValue >= TreasureData::GetMaxIndex() )
    { return false; }

    ProbabilityMap& xProbabilityMap = m_vecSpecificValue[uchLevel];
    ProbabilityMapIter iter = xProbabilityMap.find( ustItemID );
    if ( iter != xProbabilityMap.end() )
    { return false; }

    xProbabilityMap.insert( std::make_pair( ustItemID, nSpecificValue ) );

    return true;
}

// 得到宝箱中所有的东西
const TreasureBoxConfig::DataVector* TreasureBoxConfig::GetTreasureData( unsigned char uchLevel, unsigned short ustItemID ) const
{
    if ( uchLevel < ECD_Min_BoxLevel || uchLevel > m_uchMaxBoxLevel )
    { return NULL; }

    const DataMap& xDataMap = m_vecTreasureData[uchLevel];
    DataMapConstIter iter = xDataMap.find( ustItemID );
    if ( iter == xDataMap.end() )
    { return NULL; }

    return &( iter->second );
}

// 得到宝箱中某个位置的东西
const TreasureData* TreasureBoxConfig::GetTreasureData( unsigned char uchLevel, unsigned short ustItemID, unsigned char uchIndex ) const
{
    if ( uchIndex < 0 || uchIndex > TreasureData::GetMaxIndex() )
    { return NULL; }

    const DataVector* pDataVector = GetTreasureData( uchLevel, ustItemID );
    if ( pDataVector == NULL )
    { return NULL; }

    return &( pDataVector->at( uchIndex ) );
}

struct FindTreasureData : public std::unary_function< TreasureData, bool >
{
    FindTreasureData( unsigned int nProbability ) : m_nValue( 0 ), m_nProbability( nProbability ) {}

    bool operator()( const TreasureData& xData )
    {
        m_nValue += xData.GetProbability();           // 每种类型都有一个概率,所以这里用区间来找概率
        return ( m_nProbability < m_nValue );
    }
private:
    unsigned int m_nValue;
    unsigned int m_nProbability;
};

const unsigned char TreasureBoxConfig::GetRandTreasureData( unsigned char uchLevel, unsigned short ustItemID, unsigned int nRandNumber ) const
{
    const DataVector* pDataVector = GetTreasureData( uchLevel, ustItemID );
    if ( pDataVector == NULL )
    { return -1; }

    const ProbabilityMap& xProbabilityMap = m_vecProbability[uchLevel];
    ProbabilityMapConstIter miter = xProbabilityMap.find( ustItemID );
    if ( miter == xProbabilityMap.end() || miter->second == 0 )
    { return -1; }

    int nRand = nRandNumber % miter->second;
    DataVectorIter iter = std::find_if( pDataVector->begin(), pDataVector->end(), FindTreasureData( nRand ) );
    if ( iter == pDataVector->end() )
    { return -1; }

    return static_cast< unsigned char >( distance( pDataVector->begin(), iter ) );
}

const unsigned int TreasureBoxConfig::GetSpecificValue( unsigned char uchLevel, unsigned short ustItemID )
{
    const ProbabilityMap& xProbabilityMap = m_vecSpecificValue[uchLevel];
    ProbabilityMapConstIter miter = xProbabilityMap.find( ustItemID );
    if ( miter == xProbabilityMap.end() )
    { return -1; }

    return miter->second;
}

bool TreasureBoxConfig::LoadConfig( const char* pszConfig )
{
    if ( pszConfig == NULL || pszConfig[0] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( pszConfig, 1 ) ) 
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL ) 
    { return false; }

    MeXmlElement* pInfo = pRoot->FirstChildElement( "TreasureInfo" );
    if ( pInfo == NULL )
    { return false; }

    int nMaxLevel;
    pInfo->Attribute( "MaxLevel", &nMaxLevel );
    if ( nMaxLevel == 0 )
    { return false; }
    SetMaxBoxLevel( nMaxLevel );

    int nMaxCount;
    pInfo->Attribute( "MaxCount", &nMaxCount );
    if ( nMaxCount == 0 )
    { return false; }
    TreasureData::SetMaxLevel( nMaxCount );

    Initialize();           // 初始化一下

    MeXmlElement* pTreasures = pInfo->FirstChildElement( "Treasures" );
    while ( pTreasures != NULL )
    {
        int nLevel;
        if ( pTreasures->Attribute( "Level", &nLevel ) == NULL || nLevel < ECD_Min_BoxLevel || nLevel >= TreasureData::GetMaxIndex() )
        { return false; }

        MeXmlElement* pTreasureItem = pTreasures->FirstChildElement( "TreasureItem" );
        while ( pTreasureItem != NULL )
        {
            int nBoxItemID;
            if ( pTreasureItem->Attribute( "ItemID", &nBoxItemID ) == NULL || nBoxItemID == 0 )
            { return false; }

            int nSpecificValue;
            if ( pTreasureItem->Attribute( "Specific", &nSpecificValue ) != NULL )
            {
                AddSpecificValue( nLevel, nBoxItemID, nSpecificValue );
            }
            
            MeXmlElement* pTreasure = pTreasureItem->FirstChildElement( "Treasure" );
            while ( pTreasure != NULL )
            {
                TreasureData xData;

                int nIndex;
                pTreasure->Attribute( "Index", &nIndex );
                xData.SetIndex( nIndex );

                int nItemID;
                pTreasure->Attribute( "ItemID", &nItemID );
                xData.SetItemID( nItemID );

                int nCount;
                pTreasure->Attribute( "Count", &nCount );
                xData.SetItemCount( nCount );

                int nProbability;
                pTreasure->Attribute( "Probability", &nProbability );
                xData.SetProbability( nProbability );

                int nNoticeWorld;
                pTreasure->Attribute( "NoticeWorld", &nNoticeWorld );
                xData.SetNoticeWorld( nNoticeWorld == 0 ? false : true );

                if ( !AddTreasureData( nLevel, nBoxItemID, xData ) )
                { return false; }

                if ( !AddProbability( nLevel, nBoxItemID, xData.GetProbability() ) )  // 累加概率总和
                { return false; }

                pTreasure = pTreasure->NextSiblingElement();
            }

            pTreasureItem = pTreasureItem->NextSiblingElement();
        }

        pTreasures = pTreasures->NextSiblingElement();
    }

    return true;
}