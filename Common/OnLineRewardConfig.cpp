#include "OnLineRewardConfig.h"
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"


bool OnLineRewardConfig::LoadOnLineRewardConfig( const char* szFile )
{
    if ( szFile == NULL || *szFile == 0 )
    { return false; }

    m_vecOnLineReward.clear();
    m_nMaxRewardCount = 0;

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pRewards = pRoot->FirstChildElement( "Rewards" );
    if ( pRewards == NULL )
    { return false; }

    int nMaxCount;
    if ( pRewards->Attribute( "MaxCount", &nMaxCount ) == NULL || nMaxCount <= 0 )
    { return false; }
    m_nMaxRewardCount = nMaxCount;

    int nRewardType;
    if ( pRewards->Attribute( "RewardType", &nRewardType ) == NULL )
    { return false; }
    m_nRewardType = nRewardType;

    int nLevelLowLimit;
    if ( pRewards->Attribute( "LevelLowLimit", &nLevelLowLimit ) == NULL )
    { return false; }
    m_nLevelLowLimit = nLevelLowLimit;

    int nLevelUpLimit;
    if ( pRewards->Attribute( "LevelUpLimit", &nLevelUpLimit ) == NULL )
    { return false; }
    m_nLevelUpLimit = nLevelUpLimit;

    m_vecOnLineReward.resize( nMaxCount );
    
    nMaxCount = 0;
    MeXmlElement* pReward = pRewards->FirstChildElement( "Reward" );
    while ( pReward != NULL )
    {
        OnLineReward xReward;

        int nIndex;
        if ( pReward->Attribute( "Index", &nIndex ) == NULL || nIndex < 0 || nIndex >= m_nMaxRewardCount )
        { return false; }

        int nOnLineTime;
        if ( pReward->Attribute( "OnlineTime", &nOnLineTime ) == NULL )
        { return false; }
        xReward.dwOnLineTime = nOnLineTime;

		int nCountDown;
		if( pReward->Attribute( "Countdown", &nCountDown ) == NULL )
		{ return false;	}
		xReward.dwCountDown = nCountDown;

		memset( xReward.nItemID,        0, sizeof( xReward.nItemID      ) );
		memset( xReward.nCount,         0, sizeof( xReward.nCount       ) );
        memset( xReward.bIsBound,       1, sizeof( xReward.bIsBound     ) );
        memset( xReward.bIsStarRandom,  0, sizeof( xReward.bIsStarRandom) );
        memset( xReward.nStarLevel,     0, sizeof( xReward.nStarLevel   ) );

        int nItemIndex = 0;
        MeXmlElement* pItem = pReward->FirstChildElement( "Item" );
        while ( pItem != NULL )
        {
            if ( nItemIndex >= EConstDefine_RewardItemMaxSize)
            { break; }

            int nItemID;
            if ( pItem->Attribute( "ID", &nItemID ) == NULL )
            { break; }
            xReward.nItemID[nItemIndex] = nItemID;

            int nItemCount;
            if ( pItem->Attribute( "Count", &nItemCount ) == NULL )
            { break; }
            xReward.nCount[nItemIndex] = nItemCount;

            int nIsBound = 1;
            if ( pItem->Attribute( "IsBound", &nIsBound ) == NULL )
            { }
            xReward.bIsBound[nItemIndex] = !!nIsBound;

            int nIsStarRandom = 0;
            if ( pItem->Attribute( "IsStarRandom", &nIsStarRandom ) == NULL )
            { }
            xReward.bIsStarRandom[nItemIndex] = !!nIsStarRandom;

            int nStarLevel = 0;
            if ( pItem->Attribute( "StarLevel", &nStarLevel ) == NULL )
            { }
            xReward.nStarLevel[nItemIndex] = nStarLevel;

            ++nItemIndex;
            pItem = pItem->NextSiblingElement();
        }

        if ( !AddOnLineReward( nIndex, xReward ) )
        { return false; }

        ++nMaxCount;    
        pReward = pReward->NextSiblingElement();
    }

    m_nMaxRewardCount = nMaxCount;  // 重新计算最大奖励个数( 客户端需要正确的最大值, 可能策划填的不对 )
    
    return true;
}