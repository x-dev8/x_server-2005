#include "TitleManager.h"
#include "TitleConfig.h"
#include <algorithm>
#include "GlobalDef.h"

bool TitleManager::SetCurrentTitle( unsigned short ustTitltID )
{
    if ( ustTitltID != TitleConfig::Init_ID )
    {
        if ( !IsHaveTitle( ustTitltID ) )       // 判断是否有这个称号
        { return false; }
    }

    m_ustCurrentTitle = ustTitltID;
    return true;
}

bool TitleManager::AddTitle( TitleData& xData )
{
    if ( GetTitleCount() >= m_ustMaxTitleCount || xData.GetTitleID() == TitleConfig::Init_ID )
    { return false; }

    if ( IsHaveTitle( xData.GetTitleID() ) )
    { return false; }

    m_vecTitle.push_back( xData );
    return true;
}

bool TitleManager::AddTitle( unsigned short ustTitleID, __int64 n64AcquireTime, unsigned int nActiveTime )
{
    TitleData xData( ustTitleID, n64AcquireTime, nActiveTime );

    return AddTitle( xData );
}

bool TitleManager::RemoveTitle( unsigned short ustTitleID )
{
    TitleVectorIter iter = std::find( m_vecTitle.begin(), m_vecTitle.end(), ustTitleID );
    if ( iter == m_vecTitle.end() )
    { return false; }

    m_vecTitle.erase( iter );
    return true;
}

bool TitleManager::IsHaveTitle( unsigned short ustTitleID )
{
    return std::find( m_vecTitle.begin(), m_vecTitle.end(), ustTitleID ) != m_vecTitle.end();
}

// 先找在我的称号里面,是不是有顶掉
bool TitleManager::IsAlreadyDisplaceTitle( unsigned short ustTitleID )
{
    if ( ustTitleID == TitleConfig::Init_ID )
    { return false; }

    for ( TitleVectorIter iter = m_vecTitle.begin(); iter != m_vecTitle.end(); ++iter )
    {
        TitleConfig::Title* pTitleConfig = theTitleConfig.GetTitleByTitleID( iter->GetTitleID() );
        if ( pTitleConfig == NULL )
        { continue; }

        for ( int i = 0;  i < TitleConfig::Title_Max_Displace; ++i )
        {
            unsigned short ustDisplaceID = pTitleConfig->GetDisplaceId( i );
            if ( ustDisplaceID == ustTitleID )     // 有顶掉ustTitleID的, 然后判断 ustTitleID 是否也顶掉它 
            {
                TitleConfig::Title* pAddTitleConfig = theTitleConfig.GetTitleByTitleID( ustTitleID );
                if ( pAddTitleConfig == NULL )
                { return false; }

                for ( int k = 0; k < TitleConfig::Title_Max_Displace; ++k )
                {
                    if ( pAddTitleConfig->GetDisplaceId( k ) == pTitleConfig->GetID() )
                    { return false; }
                }

                return true;        // 自己不顶掉nDisplaceID, 而 nDisplaceID 顶掉自己
            }
        }
    }

    return false;
}

unsigned short TitleManager::GetDisplaceID( unsigned short ustTitleID )
{
    TitleConfig::Title* pTitleConfig = theTitleConfig.GetTitleByTitleID( ustTitleID );
    if ( pTitleConfig == NULL )
    { return TitleConfig::Init_ID; }

    for ( int i = 0; i < TitleConfig::Title_Max_Displace; ++i )
    {
        unsigned short ustDisplaceID = pTitleConfig->GetDisplaceId( i );
        if ( ustDisplaceID == TitleConfig::Init_ID )
        { continue; }

        if ( IsHaveTitle( ustDisplaceID ) )       // 如果有被这个称号要顶掉的称号,返回
        { return ustDisplaceID; }
    }

    return TitleConfig::Init_ID;
}

TitleData* TitleManager::GetTitleDataByIndex( unsigned short uchIndex )
{
    if ( uchIndex >= GetTitleCount() )
    { return NULL; }

    return &m_vecTitle.at( uchIndex );
}

TitleData* TitleManager::GetTitleDataByID( unsigned short ustTitleID )
{
    if ( ustTitleID == TitleConfig::Init_ID )
    { return NULL; }

    TitleVectorIter iter = std::find( m_vecTitle.begin(), m_vecTitle.end(), ustTitleID );
    if ( iter == m_vecTitle.end() )
    { return NULL; }

    return &( *iter );
}

TitleData* TitleManager::GetTimeLimitTitleByTitleType( unsigned short ustConditionType ) 
{
    if ( ustConditionType <= TitleConfig::Condition_Init || ustConditionType >= TitleConfig::Condition_End )
    { return NULL; }

    for ( TitleVectorIter iter = m_vecTitle.begin(); iter != m_vecTitle.end(); ++iter )
    {
        TitleConfig::Title* pTitleConfig = theTitleConfig.GetTitleByTitleID( iter->GetTitleID() );
        if ( pTitleConfig == NULL ) 
        { continue; }

        if ( pTitleConfig->GetTimeLimit() != 0 && pTitleConfig->GetConditionType() == ustConditionType )
        { return &( *iter ); }        
    }

    return NULL;
}

bool TitleManager::IsHaveTypeTitle( unsigned char uchType )
{
    for ( TitleVectorIter iter = m_vecTitle.begin(); iter != m_vecTitle.end(); ++iter )
    {
        TitleConfig::Title* pTitleConfig = theTitleConfig.GetTitleByTitleID( iter->GetTitleID() );
        if ( pTitleConfig == NULL )
        { continue; }

        if ( pTitleConfig->GetType() == uchType )
        { return true; }
    }

    return false;
}

bool TitleManager::RemoveTypeTitle( unsigned char uchType )
{
    bool bRemoveSuccess = false;
    for ( TitleVectorIter iter = m_vecTitle.begin(); iter != m_vecTitle.end(); )
    {
        TitleConfig::Title* pTitleConfig = theTitleConfig.GetTitleByTitleID( iter->GetTitleID() );
        if ( pTitleConfig == NULL || pTitleConfig->GetType() != uchType )
        { 
            ++iter;
            continue; 
        }

        bRemoveSuccess = true;
        iter = m_vecTitle.erase( iter );
    }

    return bRemoveSuccess;
}

void TitleManager::GetTypeTitle( unsigned char uchType, std::vector< unsigned short >& vecTitleID )
{
    vecTitleID.clear();

    for ( TitleVectorIter iter = m_vecTitle.begin(); iter != m_vecTitle.end(); ++iter )
    {
        TitleConfig::Title* pTitleConfig = theTitleConfig.GetTitleByTitleID( iter->GetTitleID() );
        if ( pTitleConfig == NULL || pTitleConfig->GetType() != uchType )
        { continue; }

        vecTitleID.push_back( iter->GetTitleID() );
    }
}

void TitleManager::InitTitle( TitleData* pTitleData, int nCount, bool bCheckTimeLimit /* = false */ )
{
    if ( pTitleData == NULL || nCount == 0 )
    { return; }

    m_vecTitle.clear();
    m_vecRemoveTitle.clear();
    m_ustMaxTitleCount = nCount;        // 设置最大值

    for( int i = 0; i < nCount; ++i )
    {
        unsigned short ustTitleID = pTitleData[i].GetTitleID();
        if( ustTitleID == TitleConfig::Init_ID )
        { break; }

        // 已经到期了
        if ( bCheckTimeLimit && pTitleData[i].IsPassLimitTime() )
        { 
            m_vecRemoveTitle.push_back( ustTitleID );
            continue;
        }           

        m_vecTitle.push_back( pTitleData[i] );
    }
}

void TitleManager::SaveTitle( TitleData* pTitleData, int nCount )
{
    if ( pTitleData == NULL || nCount == 0 )
    { return; }

    int i = 0;
    for ( TitleVectorIter iter = m_vecTitle.begin(); iter != m_vecTitle.end() && i < nCount; ++iter, ++i )
    {
        pTitleData[i] = *iter;
    }
}
