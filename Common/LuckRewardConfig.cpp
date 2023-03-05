#include "LuckRewardConfig.h"

template<>
bool LuckRewardConfig< RewardData >::LoadLuckRewardConfig( const char *szFile )
{
    if ( szFile == NULL || szFile[0] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) ) 
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL ) 
    { return false; }

    MeXmlElement* pLevels = pRoot->FirstChildElement( "Levels" );
    if ( pLevels == NULL )
    { return false; }

    int nMaxLevel;
    pLevels->Attribute( "MaxLevel", &nMaxLevel );
    if ( nMaxLevel == 0 )
        nMaxLevel = ECD_Reward_MaxLevel;

    m_uchMaxLevel = nMaxLevel;
    Initialize();           // 初始化一下

    MeXmlElement* pLevel = pLevels->FirstChildElement( "Level" );
    while ( pLevel != NULL )
    {
        int nLevel;
        if ( pLevel->Attribute( "Value", &nLevel ) == NULL || nLevel < ECD_Reward_MinLevel || nLevel > m_uchMaxLevel )
        { return false; }

        int nRewardCount;
        pLevel->Attribute( "RewardCount", &nRewardCount );
        if ( nRewardCount == 0 )
            nRewardCount = ECD_Reward_Count;
        m_vecLuckCount[nLevel] = nRewardCount;          // 设置这关奖励的个数

        MeXmlElement* pRewards = pLevel->FirstChildElement( "Rewards" );
        if ( pRewards == NULL )
        { return false; }

        char chIndex = 0;       // 索引
        MeXmlElement* pReward = pRewards->FirstChildElement( "Reward" );
        while ( pReward != NULL )
        {
            RewardData xRewardData;

            int nType;
            pReward->Attribute( "Type", &nType );
            xRewardData.SetType( nType );

            int nItemID;
            pReward->Attribute( "ItemID", &nItemID );
            xRewardData.SetItemID( nItemID );

            int nValue;
            pReward->Attribute( "Value", &nValue );
            xRewardData.SetValue( nValue );

            int nFixed;
            pReward->Attribute( "IsFixed", &nFixed );
            xRewardData.SetFixed( ( nFixed == 0 ? false : true ) );

            int nRealLife;
            pReward->Attribute( "IsRealLife", &nRealLife );
            xRewardData.SetRealLife( ( nRealLife == 0 ? false : true ) );

            int nProbability;
            pReward->Attribute( "Probability", &nProbability );
            xRewardData.SetProbability( nProbability );

            if ( !AddReward( nLevel, xRewardData ) )
            { return false; }

            if ( xRewardData.GetFixed() )             // 添加必出的奖励
            {
                m_vecFixedLuckRewardIndex[nLevel].push_back( chIndex );
            }
            else
            {   // 随机的奖励
                m_vecRandLuckReward[nLevel].push_back( xRewardData );               // 保存随机的奖励
                m_vecRandLuckRewardIndex[nLevel].push_back( chIndex );              // 保存该索引
                m_vecRandLuckNumber[nLevel] += xRewardData.GetProbability();  // 累加概率总和
            }

            ++chIndex;
            pReward = pReward->NextSiblingElement();
        }

        pLevel = pLevel->NextSiblingElement();
    }

    return true;
}

template<>
bool LuckRewardConfig< RandData >::LoadLuckRandConfig( const char *szFile )
{
    if ( szFile == NULL || szFile[0] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) ) 
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL ) 
    { return false; }

    MeXmlElement* pLevels = pRoot->FirstChildElement( "Levels" );
    if ( pLevels == NULL )
    { return false; }

    int nMaxLevel;
    pLevels->Attribute( "MaxLevel", &nMaxLevel );
    if ( nMaxLevel == 0 )
        nMaxLevel = ECD_Reward_MaxLevel;

    m_uchMaxLevel = nMaxLevel;
    Initialize();           // 初始化一下

    MeXmlElement* pLevel = pLevels->FirstChildElement( "Level" );
    while ( pLevel != NULL )
    {
        int nLevel;
        if ( pLevel->Attribute( "Value", &nLevel ) == NULL || nLevel < ECD_Reward_MinLevel || nLevel > m_uchMaxLevel )
        { return false; }

        MeXmlElement* pRands = pLevel->FirstChildElement( "Rands" );
        if ( pRands == NULL )
        { return false; }

        MeXmlElement* pRand = pRands->FirstChildElement( "Rand" );
        while ( pRand != NULL )
        {
            RandData xRandData;

            int nType;
            pRand->Attribute( "Type", &nType );
            xRandData.SetType( nType );

            int nProbability;
            pRand->Attribute( "Probability", &nProbability );
            xRandData.SetProbability( nProbability );

            //TODO:
            if ( !AddReward( nLevel, xRandData ) )
            { 
                pRand = pRand->NextSiblingElement();
                continue; 
            }

            m_vecRandLuckNumber[nLevel] += xRandData.GetProbability();  // 累加概率总和

            pRand = pRand->NextSiblingElement();
        }

        pLevel = pLevel->NextSiblingElement();
    }

    return true;
}
