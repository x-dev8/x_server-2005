#include "GuildConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "tstring.h"

bool GuildConfig::LoadConfig( const char* szFile )
{
    if ( szFile == NULL || szFile[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pGuildSettings = pRoot->FirstChildElement( "GuildSettings" );
    if ( pGuildSettings == NULL )
    { return false; }

    int nValue = 0;

    // 创建帮派设定
    MeXmlElement* pCreateGuild = pGuildSettings->FirstChildElement( "CreateGuild" );
    if ( pCreateGuild == NULL )
    { return false; }

    if ( pCreateGuild->Attribute( "Level", &nValue ) == NULL )
    { return false; }
    m_xCreateSetting.SetLevel( nValue );

    if ( pCreateGuild->Attribute( "CostMoney", &nValue ) == NULL )
    { return false; }
    m_xCreateSetting.SetCostMoney( nValue );

    // 加入帮派设定
    MeXmlElement* pJoinGuild = pGuildSettings->FirstChildElement( "JoinGuild" );
    if ( pJoinGuild == NULL )
    { return false; }

    if ( pJoinGuild->Attribute( "Level", &nValue ) == NULL )
    { return false; }
    m_xJoinSetting.SetLevel( nValue );

    if ( pJoinGuild->Attribute( "TimeLimit", &nValue ) == NULL )
    { return false; }
    m_xJoinSetting.SetTimeLimit( nValue );

    // 帮派等级设定
    MeXmlElement* pGuildLevels = pGuildSettings->FirstChildElement( "GuildLevels" );
    if ( pGuildLevels == NULL )
    { return false; }

    m_vecLevelSetting.clear();
    m_vecLevelSetting.push_back( LevelSetting() );
    MeXmlElement* pGuildLevel = pGuildLevels->FirstChildElement( "Guild" );
    while ( pGuildLevel != NULL )
    {
        LevelSetting xSetting;

        if ( pGuildLevel->Attribute( "MaxCount", &nValue ) == NULL )
        { return false; }
        xSetting.SetMaxCount( nValue );

        if ( pGuildLevel->Attribute( "MaxMisision", &nValue ) == NULL )
        { return false; }
        xSetting.SetMaxMission( nValue );

        if ( pGuildLevel->Attribute( "MaxExp", &nValue ) == NULL )
        { return false; }
        xSetting.SetMaxExp( nValue );

        if ( pGuildLevel->Attribute( "MaxMoney", &nValue ) == NULL )
        { return false; }
        xSetting.SetMaxMoney( nValue );

        if ( pGuildLevel->Attribute( "NeedExp", &nValue ) == NULL )
        { return false; }
        xSetting.SetNeedExp( nValue );

        if ( pGuildLevel->Attribute( "NeedMoney", &nValue ) == NULL )
        { return false; }
        xSetting.SetNeedMoney( nValue );

		if ( pGuildLevel->Attribute( "NeedMission", &nValue ) == NULL )
        { return false; }
        xSetting.SetNeedMission( nValue );

        m_vecLevelSetting.push_back( xSetting );

        pGuildLevel = pGuildLevel->NextSiblingElement();
    }

    // 捐献设定
    MeXmlElement* pDonate = pGuildSettings->FirstChildElement( "Donate" );
    if ( pDonate == NULL )
    { return false; }

    if ( pDonate->Attribute( "Money", &nValue ) == NULL )
    { return false; }
    m_xDonateSetting.SetMoney( nValue );

    if ( pDonate->Attribute( "Activity", &nValue ) == NULL )
    { return false; }
    m_xDonateSetting.SetActivity( nValue );

    if ( pDonate->Attribute( "Offer", &nValue ) == NULL )
    { return false; }
    m_xDonateSetting.SetOffer( nValue );

    if ( pDonate->Attribute( "MaxDonate", &nValue ) == NULL )
    { return false; }
    m_xDonateSetting.SetMaxMoney( nValue );
	
	m_xDonateSetting.ClearDonateMoneyVct();
	MeXmlElement* pDonateMoney = pDonate->FirstChildElement( "Money" );
	while ( pDonateMoney != NULL )
	{
		int nValue = 0;
		DonateMoneySetting donateMoneySetting;

		if (pDonateMoney->Attribute("Level", &nValue) == NULL)
		{
			return false;
		}
		donateMoneySetting.SetLevel(nValue);

		if (pDonateMoney->Attribute("MaxMoney", &nValue) == NULL)
		{
			return false;
		}
		donateMoneySetting.SetMoney(nValue);
		
		m_xDonateSetting.SetDonateMoney(donateMoneySetting);
		pDonateMoney = pDonateMoney->NextSiblingElement();
	}

    // 募集设定
    MeXmlElement* pCollect = pGuildSettings->FirstChildElement( "Collect" );
    if ( pCollect == NULL )
    { return false; }

    if ( pCollect->Attribute( "GuildExp", &nValue ) == NULL )
    { return false; }
    m_xCollectSetting.SetGuildExp( nValue );

    if ( pCollect->Attribute( "GuildMoney", &nValue ) == NULL )
    { return false; }
    m_xCollectSetting.SetGuildMoney( nValue );

    if ( pCollect->Attribute( "PlayerExp", &nValue ) == NULL )
    { return false; }
    m_xCollectSetting.SetPlayerExp( nValue );

    if ( pCollect->Attribute( "PlayerOffer", &nValue ) == NULL )
    { return false; }
    m_xCollectSetting.SetPlayerOffer( nValue );

    // 帮贡建设设定
    MeXmlElement* pBuild = pGuildSettings->FirstChildElement( "Build" );
    if ( pBuild == NULL )
    { return false; }

    if ( pBuild->Attribute( "CostOffer", &nValue ) == NULL )
    { return false; }
    m_xBuildSetting.SetOffer( nValue );

    if ( pBuild->Attribute( "GuildExp", &nValue ) == NULL )
    { return false; }
    m_xBuildSetting.SetGuildExp( nValue );

    if ( pBuild->Attribute( "PlayerExp", &nValue ) == NULL )
    { return false; }
    m_xBuildSetting.SetPlayerExp( nValue );

    // 弹劾设定
    MeXmlElement* pDelate = pGuildSettings->FirstChildElement( "Delate" );
    if ( pDelate == NULL )
    { return false; }

    if ( pDelate->Attribute( "DayOfWeek", &nValue ) == NULL )
    { return false; }
    m_xDelateSetting.SetDayOfWeek( nValue );

    if ( pDelate->Attribute( "StartHour", &nValue ) == NULL )
    { return false; }
    m_xDelateSetting.SetStartHour( nValue );

    if ( pDelate->Attribute( "EndHour", &nValue ) == NULL )
    { return false; }
    m_xDelateSetting.SetEndHour( nValue );

    if ( pDelate->Attribute( "Level", &nValue ) == NULL )
    { return false; }
    m_xDelateSetting.SetLevel( nValue );

    if ( pDelate->Attribute( "CostMoney", &nValue ) == NULL )
    { return false; }
    m_xDelateSetting.SetCostMoney( nValue );

    if ( pDelate->Attribute( "MinCount", &nValue ) == NULL )
    { return false; }
    m_xDelateSetting.SetMinCount( nValue );

    if ( pDelate->Attribute( "Ratio", &nValue ) == NULL )
    { return false; }
    m_xDelateSetting.SetRatio( nValue );

    // 自动解散设定
    MeXmlElement* pDisband = pGuildSettings->FirstChildElement( "Disband" );
    if ( pDisband == NULL )
    { return false; }

    if ( pDisband->Attribute( "MemberCount", &nValue ) == NULL )
    { return false; }
    m_xDisbandSetting.SetMinCount( nValue );

    if ( pDisband->Attribute( "KeepTime", &nValue ) == NULL )
    { return false; }
    m_xDisbandSetting.SetKeepTime( nValue );

    // 帮派实力计算公式系数
    double dValue = 0.0f;
    MeXmlElement* pStrength = pGuildSettings->FirstChildElement( "Strength" );
    if ( pStrength == NULL )
    { return false; }

    if ( pStrength->Attribute( "BaseModulus", &dValue ) == NULL )
    { return false; }
    m_xStrengthSetting.SetBaseModulus( static_cast< float >( dValue ) );

    if ( pStrength->Attribute( "ExtendModulus", &dValue ) == NULL )
    { return false; }
    m_xStrengthSetting.SetExtendModulus( static_cast< float >( dValue ) );

    // 使命点设定
    MeXmlElement* pMission = pGuildSettings->FirstChildElement( "Mission" );
    if ( pMission == NULL )
    { return false; }

    if ( pMission->Attribute( "GuildExp", &nValue ) == NULL )
    { return false; }
    m_xMissionSetting.SetGuildExp( nValue );

    MeXmlElement* pDateTime = pMission->FirstChildElement( "Time" );
    while ( pDateTime != NULL )
    {
        MissionSetting::DateSetting xSetting;

        if ( pDateTime->Attribute( "Date", &nValue ) == NULL )
        { return false; }
        xSetting.SetDate( nValue );

        if ( pDateTime->Attribute( "Hour", &nValue ) == NULL )
        { return false; }
        xSetting.SetHour( nValue );

        if ( pDateTime->Attribute( "Minute", &nValue ) == NULL )
        { return false; }
        xSetting.SetMinute( nValue );

        m_xMissionSetting.AddDateStting( xSetting );

        pDateTime = pDateTime->NextSiblingElement();
    }

    // 任务发布设置
    MeXmlElement* pQuestRelease = pGuildSettings->FirstChildElement( "QuestRelease" );
    if ( pQuestRelease == NULL )
    { return false; }

    if ( pQuestRelease->Attribute( "Level", &nValue ) == NULL )
    { return false; }
    m_xReleaseSetting.SetMinLevel( nValue );

    if ( pQuestRelease->Attribute( "ReleaseTime", &nValue ) == NULL )
    { return false; }
    m_xReleaseSetting.SetReleaseTime( nValue );
    
    MeXmlElement* pRelease = pQuestRelease->FirstChildElement( "Release" );
    while ( pRelease != NULL )
    {
        ReleaseSetting::QuestSetting xSetting;

        if ( pRelease->Attribute( "Type", &nValue ) == NULL )
        { return false; }
        xSetting.SetType( nValue );

        if ( pRelease->Attribute( "CostMoney", &nValue ) == NULL )
        { return false; }
        xSetting.SetCostMoney( nValue );

		if ( pRelease->Attribute( "KeepTime", &nValue ) == NULL )
		{ return false; }
		xSetting.SetKeepTime( nValue);

		Common::_tstring strName = "";			
		strName.fromUTF8( pRelease->Attribute( "Name" ) );
		xSetting.SetName( strName.c_str() );

        if ( pRelease->Attribute( "MemberReward", &nValue ) == NULL )
        { return false; }
        xSetting.SetMemberReward( nValue );

        if ( pRelease->Attribute( "ViceReward", &nValue ) == NULL )
        { return false; }
        xSetting.SetViceReward( nValue );

        if ( pRelease->Attribute( "MasterReward", &nValue ) == NULL )
        { return false; }
        xSetting.SetMasterReward( nValue );

        MeXmlElement* pQuest = pRelease->FirstChildElement( "Quest" );
        while ( pQuest != NULL )
        {
            if ( pQuest->Attribute( "ID", &nValue ) == NULL )
            { return false; }
            xSetting.AddQuest( nValue );

            pQuest = pQuest->NextSiblingElement();
        }

        m_xReleaseSetting.AddQuestSetting( xSetting );

        pRelease = pRelease->NextSiblingElement();
    }

    // 帮派商店
    MeXmlElement* pShopLevels = pGuildSettings->FirstChildElement( "ShopLevels" );
    if ( pShopLevels == NULL )
    { return false; }

    m_vecShopSetting.clear();
    m_vecShopSetting.push_back( ShopSetting() );
    MeXmlElement* pShop = pShopLevels->FirstChildElement( "Shop" );
    while ( pShop != NULL )
    {
        ShopSetting xSetting;

        int nLevel;
        if ( pShop->Attribute( "Level", &nLevel ) == NULL )
        { return false; }

        if ( pShop->Attribute( "CostExp", &nValue ) == NULL )
        { return false; }
        xSetting.SetCostExp( nValue );

        MeXmlElement* pItem = pShop->FirstChildElement( "Item" );
        while ( pItem != NULL )
        {
            int nItemID;
            if ( pItem->Attribute( "ID", &nItemID ) == NULL )
            { return false; }

            int nOffer;
            if ( pItem->Attribute( "Offer", &nOffer ) == NULL )
            { return false; }

            xSetting.AddShopItem( nItemID, nOffer );

            pItem = pItem->NextSiblingElement();
        }

        m_vecShopSetting.push_back( xSetting );

        pShop = pShop->NextSiblingElement();
    }

	// 帮派宗旨改名CD,花费设定
	MeXmlElement* pChangeAim = pGuildSettings->FirstChildElement( "ChangeAim" );
	if ( NULL == pChangeAim )
	{ return false;	}

	int nCD;
	if ( pChangeAim->Attribute( "CD", &nCD ) == NULL )
	{ return false; }
	m_changeAimSetting.SetChangeAimCD( nCD );

	int nCost;
	if ( pChangeAim->Attribute( "Cost", &nCost ) == NULL )
	{ return false; }
	m_changeAimSetting.SetChangeAimCost( nCost );

    return true;
}

unsigned int GuildConfig::DonateSetting::GetMaxDonateMoneyByLevel(int nLevel) const
{
	for (std::vector<DonateMoneySetting>::const_iterator iter = m_vctDonateMoney.begin(); iter != m_vctDonateMoney.end(); ++iter)
	{
		if (nLevel <= iter->GetLevel())
		{
			return iter->GetMoney();
		}
	}

	return 0;
}