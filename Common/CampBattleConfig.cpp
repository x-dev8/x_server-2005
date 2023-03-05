#include "CampBattleConfig.h"

bool CampBattleConfig::LoadMapSetting( MeXmlElement* pElement )
{
    int nValue = 0;

    vecMapSetting.clear();
    MeXmlElement* pMapSetting = pElement->FirstChildElement( "MapSetting" );
    if ( pMapSetting == NULL )
    { return false; }
	
    MeXmlElement* pMap = pMapSetting->FirstChildElement( "Map" );
    while ( pMap != NULL )
    {
        MapSetting xSetting;
        if ( pMap->Attribute( "ID", &nValue ) == NULL )
        { return false; }
        xSetting.SetMapID( nValue );

        if ( pMap->Attribute( "Country", &nValue ) == NULL )
        { return false; }
        xSetting.SetCountryID( nValue );

        vecMapSetting.push_back( xSetting );

        pMap = pMap->NextSiblingElement();
    }

    return true;
}

bool CampBattleConfig::LoadTimeSetting( MeXmlElement* pElement )
{
    // 时间设定
    vecSignUpTimeSetting.clear();
    vecPrepareTimeSetting.clear();
    vecEnterTimeSetting.clear();
    vecFightTimeSetting.clear();
    vecEnterTimeSetting.clear();
    
    int nValue = 0;

    MeXmlElement* pTimeSettings = pElement->FirstChildElement( "TimeSettings" );
    if ( pTimeSettings == NULL )
    { return false; }

    MeXmlElement* pTime = pTimeSettings->FirstChildElement( "TimeSetting" );
    while( pTime != NULL )
    {
        TimeSetting xSetting;

        // 报名时间
        MeXmlElement* pSignUp = pTime->FirstChildElement( "SignUpTime" );
        if ( pSignUp == NULL )
        { return false; }

        if ( pSignUp->Attribute( "DayOfWeek", &nValue ) == NULL )
        { return false; }
        xSetting.SetDayOfWeek( nValue );

        if ( pSignUp->Attribute( "Hour", &nValue ) == NULL )
        { return false; }
        xSetting.SetHour( nValue );

        if ( pSignUp->Attribute( "Minute", &nValue ) == NULL )
        { return false; }
        xSetting.SetMinute( nValue );

        if ( pSignUp->Attribute( "KeepTime", &nValue ) == NULL )
        { return false; }
        xSetting.SetKeepTime( nValue );

        vecSignUpTimeSetting.push_back( xSetting );

        // 准备时间
        MeXmlElement* pPrepare = pTime->FirstChildElement( "PrepareTime" );
        if ( pPrepare == NULL )
        { return false; }

        if ( pPrepare->Attribute( "DayOfWeek", &nValue ) == NULL )
        { return false; }
        xSetting.SetDayOfWeek( nValue );

        if ( pPrepare->Attribute( "Hour", &nValue ) == NULL )
        { return false; }
        xSetting.SetHour( nValue );

        if ( pPrepare->Attribute( "Minute", &nValue ) == NULL )
        { return false; }
        xSetting.SetMinute( nValue );

        if ( pPrepare->Attribute( "KeepTime", &nValue ) == NULL )
        { return false; }
        xSetting.SetKeepTime( nValue );

        vecPrepareTimeSetting.push_back( xSetting );

        // 进入时间
        MeXmlElement* pEnter = pTime->FirstChildElement( "EnterTime" );
        if ( pEnter == NULL )
        { return false; }

        if ( pEnter->Attribute( "DayOfWeek", &nValue ) == NULL )
        { return false; }
        xSetting.SetDayOfWeek( nValue );

        if ( pEnter->Attribute( "Hour", &nValue ) == NULL )
        { return false; }
        xSetting.SetHour( nValue );

        if ( pEnter->Attribute( "Minute", &nValue ) == NULL )
        { return false; }
        xSetting.SetMinute( nValue );

        if ( pEnter->Attribute( "KeepTime", &nValue ) == NULL )
        { return false; }
        xSetting.SetKeepTime( nValue );

        vecEnterTimeSetting.push_back( xSetting );

        // 战斗时间
        MeXmlElement* pFight = pTime->FirstChildElement( "FightTime" );
        if ( pFight == NULL )
        { return false; }

        if ( pFight->Attribute( "DayOfWeek", &nValue ) == NULL )
        { return false; }
        xSetting.SetDayOfWeek( nValue );

        if ( pFight->Attribute( "Hour", &nValue ) == NULL )
        { return false; }
        xSetting.SetHour( nValue );

        if ( pFight->Attribute( "Minute", &nValue ) == NULL )
        { return false; }
        xSetting.SetMinute( nValue );

        if ( pFight->Attribute( "KeepTime", &nValue ) == NULL )
        { return false; }
        xSetting.SetKeepTime( nValue );

        vecFightTimeSetting.push_back( xSetting );

        // 结束时间
        MeXmlElement* pEnd = pTime->FirstChildElement( "EndTime" );
        if ( pEnd == NULL )
        { return false; }

        if ( pEnd->Attribute( "DayOfWeek", &nValue ) == NULL )
        { return false; }
        xSetting.SetDayOfWeek( nValue );

        if ( pEnd->Attribute( "Hour", &nValue ) == NULL )
        { return false; }
        xSetting.SetHour( nValue );

        if ( pEnd->Attribute( "Minute", &nValue ) == NULL )
        { return false; }
        xSetting.SetMinute( nValue );

        if ( pEnd->Attribute( "KeepTime", &nValue ) == NULL )
        { return false; }
        xSetting.SetKeepTime( nValue );

        vecEndTimeSetting.push_back( xSetting );

        pTime = pTime->NextSiblingElement();
    }

    return true;
}


bool CampBattleConfig::LoadEnterSetting( MeXmlElement* pElement )
{
    int nValue = 0;

    MeXmlElement* pEnterSetting = pElement->FirstChildElement( "EnterSetting" );
    if ( pEnterSetting == NULL )
    { return false; }

    if ( pEnterSetting->Attribute( "MaxCount", &nValue ) == NULL )
    { return false; }
    xEnterSetting.SetMaxCount( nValue );

    if ( pEnterSetting->Attribute( "MinLevel", &nValue ) == NULL )
    { return false; }
    xEnterSetting.SetMinLevel( nValue );

    return true;
}

bool CampBattleConfig::LoadResourceSetting( MeXmlElement* pElement )
{
    int nValue = 0;
    // 资源分设定
    MeXmlElement* pResource = pElement->FirstChildElement( "Resource" );
    if ( pResource == NULL )
    { return false; }

    if ( pResource->Attribute( "MaxResource", &nValue ) == NULL )
    { return false; }
    xResourceSetting.SetMaxResource( nValue );

    if ( pResource->Attribute( "KillResource", &nValue ) == NULL )
    { return false; }
    xResourceSetting.SetKillResource( nValue );

    return true;
}

bool CampBattleConfig::LoadKillSetting(  MeXmlElement* pElement )
{
    int nValue = 0;
    // 杀人设定
    MeXmlElement* pKillSetting = pElement->FirstChildElement( "KillSetting" );
    if ( pKillSetting == NULL )
    { return false; }

    // 首杀
    MeXmlElement* pFirstKill = pKillSetting->FirstChildElement( "FirstKill" );
    if ( pFirstKill == NULL )
    { return false; }

    if ( pFirstKill->Attribute( "StringID", &nValue ) == NULL )
    { return false; }
    xFirstKillSetting.SetString( nValue );

    // 连续杀人
    MeXmlElement* pKeepKills = pKillSetting->FirstChildElement( "KeepKills" );
    if ( pKeepKills == NULL )
    { return false; }

    MeXmlElement* pKeepKill = pKeepKills->FirstChildElement( "KeepKill" );
    while ( pKeepKill != NULL )
    {
        KillSetting xSetting;

        if ( pKeepKill->Attribute( "Count", &nValue ) == NULL )
        { return false; }
        xSetting.SetCount( nValue );

        if ( pKeepKill->Attribute( "StringID", &nValue ) == NULL )
        { return false; }
        xSetting.SetString( nValue );

        mapKillerSetting[ xSetting.GetCount() ] = xSetting;

        pKeepKill = pKeepKill->NextSiblingElement();
    }

    // 终结杀人
    MeXmlElement* pBeKilleds = pKillSetting->FirstChildElement( "BeKilleds" );
    if ( pBeKilleds == NULL )
    { return false; }

    MeXmlElement* pBeKilled = pBeKilleds->FirstChildElement( "BeKilled" );
    while ( pBeKilled != NULL )
    {
        KillSetting xSetting;

        if ( pBeKilled->Attribute( "Count", &nValue ) == NULL )
        { return false; }
        xSetting.SetCount( nValue );

        if ( pBeKilled->Attribute( "StringID", &nValue ) == NULL )
        { return false; }
        xSetting.SetString( nValue );

        vecBeKillSetting.push_back( xSetting );

        pBeKilled = pBeKilled->NextSiblingElement();
    }

    // 总共杀人
    MeXmlElement* pTotalKills = pKillSetting->FirstChildElement( "TotalKills" );
    if ( pTotalKills == NULL )
    { return false; }

    MeXmlElement* pTotalKill = pTotalKills->FirstChildElement( "TotalKill" );
    while ( pTotalKill != NULL )
    {
        KillSetting xSetting;

        if ( pTotalKill->Attribute( "Count", &nValue ) == NULL )
        { return false; }
        xSetting.SetCount( nValue );

        if ( pTotalKill->Attribute( "StringID", &nValue ) == NULL )
        { return false; }
        xSetting.SetString( nValue );

        mapTotalKillSetting[ xSetting.GetCount() ] = xSetting;

        pTotalKill = pTotalKill->NextSiblingElement();
    }

    return true;
}

bool CampBattleConfig::LoadMonsterSetting( MeXmlElement* pElement )
{
    int nValue = 0;
    // 怪物设定
    mapMonsterSetting.clear();
    MeXmlElement* pMonsterSetting = pElement->FirstChildElement( "MonsterSetting" );
    if ( pMonsterSetting == NULL )
    { return false; }

    MeXmlElement* pMonster = pMonsterSetting->FirstChildElement( "Monster" );
    while ( pMonster != NULL )
    {
        MonsterSetting xSetting;
        if ( pMonster->Attribute( "ID", &nValue ) == NULL )
        { return false; }
        xSetting.SetID( nValue );

        if ( pMonster->Attribute( "Resource", &nValue ) == NULL )
        { return false; }
        xSetting.SetResource( nValue );

        if ( pMonster->Attribute( "StringID", &nValue ) == NULL )
        { return false; }
        xSetting.SetString( nValue );

        mapMonsterSetting[ xSetting.GetID() ] = xSetting;

        pMonster = pMonster->NextSiblingElement();
    }

    return true;
}

bool CampBattleConfig::LoadRewardSetting(  MeXmlElement* pElement )
{ 
    int nValue = 0;
    // 奖励设定
    vecRewardSetting.clear();
    MeXmlElement* pRewardSetting = pElement->FirstChildElement( "RewardSetting" );
    if ( pRewardSetting == NULL )
    { return false; }

    MeXmlElement* pReward = pRewardSetting->FirstChildElement( "Reward" );
    while ( pReward != NULL )
    {
        RewardSetting xSetting;
        if ( pReward->Attribute( "Type", &nValue ) == NULL )
        { return false; }
        xSetting.SetType( nValue );

        if ( pReward->Attribute( "WinValue", &nValue ) == NULL )
        { return false; }
        xSetting.SetWinValue( nValue );

        if ( pReward->Attribute( "LoseValue", &nValue ) == NULL )
        { return false; }
        xSetting.SetLoseValue( nValue );

        vecRewardSetting.push_back( xSetting );

        pReward = pReward->NextSiblingElement();
    }

    return true;
}

bool CampBattleConfig::LoadConfig( const char* szFile,unsigned char countryid)
{
    if ( szFile == NULL || szFile[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pBattleSetting = pRoot->FirstChildElement( "BattleSettings" );
	while (pBattleSetting)
	{
		int nValue = CountryDefine::Country_Init;
		if ( pBattleSetting->Attribute( "CountryId", &nValue ) == NULL )
		{ return false; }

		if (nValue !=  CountryDefine::Country_Init&&nValue != countryid)
		{
			pBattleSetting = pBattleSetting->NextSiblingElement("BattleSettings");
			continue;
		}

		if ( !LoadMapSetting( pBattleSetting ) )
		{ return false; }

		if ( !LoadTimeSetting( pBattleSetting ) )
		{ return false; }

		if ( !LoadEnterSetting( pBattleSetting ) )
		{ return false; }

		if ( !LoadResourceSetting( pBattleSetting ) )
		{ return false; }

		if ( !LoadKillSetting( pBattleSetting ) )
		{ return false; }

		if ( !LoadMonsterSetting( pBattleSetting ) )
		{ return false; }

		if ( !LoadRewardSetting( pBattleSetting ) )
		{ return false; }
		if ( !LoadKingdomMapSetting( pBattleSetting ) )
		{ return false; }
		if ( !LoadEnterBuff( pBattleSetting ) )
		{ return false; }
		return true;
	}    
    return false;
}

bool CampBattleConfig::LoadKingdomMapSetting( MeXmlElement* pElement )
{
	float fValue = 0.0f;
	int nValue = 0;

	MeXmlElement* pMapSetting = pElement->FirstChildElement( "KingdomMaps" );
	if ( pMapSetting == NULL )
	{ return false; }

	MeXmlElement* pKingdomMap = pMapSetting->FirstChildElement( "KingdomMap" );
	if (pKingdomMap)
	{
		if ( pKingdomMap->Attribute( "id", &nValue ) == NULL )
		{ return false; }
		xKongdomMap.SetMapID(nValue);

		if ( pKingdomMap->Attribute( "x", &fValue ) == NULL )
		{ return false; }
		xKongdomMap.SetMapX(fValue);

		if ( pKingdomMap->Attribute( "y", &fValue ) == NULL )
		{ return false; }
		xKongdomMap.SetMapY(fValue);

		return true;
	}
	return false;
}
bool CampBattleConfig::LoadEnterBuff( MeXmlElement* pElement )
{
	int nValue = 0;
	MeXmlElement* pMapSetting = pElement->FirstChildElement( "EnterBuff" );
	if ( pMapSetting == NULL )
	{ return false; }

	if ( pMapSetting->Attribute( "BuffID", &nValue ) == NULL )
	{ return false; }
	xEnterBuff.SetBuffID(nValue);

	if ( pMapSetting->Attribute( "Level", &nValue ) == NULL )
	{ return false; }
	xEnterBuff.SetLevel(nValue);
	return true;
}