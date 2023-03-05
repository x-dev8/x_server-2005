#include "GameGuildGeneralBattleConfig.h"
bool GameGuildGeneralBattleConfig::LoadMapSetting( MeXmlElement* pElement )
{
    int nValue = 0;

    MeXmlElement* pMapSetting = pElement->FirstChildElement( "MapSetting" );
    if ( pMapSetting == NULL )
    { return false; }
	
    MeXmlElement* pMap = pMapSetting->FirstChildElement( "Map" );
    if( pMap != NULL )
    {
        if ( pMap->Attribute( "ID", &nValue ) == NULL )
        { return false; }
        vecMapSetting.SetMapID( nValue );

        if ( pMap->Attribute( "Country", &nValue ) == NULL )
        { return false; }
        vecMapSetting.SetCountryID( nValue );
		return true;
    }
    return false;
}

bool GameGuildGeneralBattleConfig::LoadTimeSetting( MeXmlElement* pElement )
{
    int nValue = 0;

    MeXmlElement* pTime = pElement->FirstChildElement( "TimeSetting" );
    if( pTime != NULL )
    {
        // 报名时间
       /* MeXmlElement* pSignUp = pTime->FirstChildElement( "SignUpTime" );
        if ( pSignUp == NULL )
        { return false; }

        if ( pSignUp->Attribute( "KeepTime", &nValue ) == NULL )
        { return false; }
        vecSignUpTimeSetting.SetKeepTime( nValue );*/

        // 准备时间
        /*MeXmlElement* pPrepare = pTime->FirstChildElement( "PrepareTime" );
        if ( pPrepare == NULL )
        { return false; }
        if ( pPrepare->Attribute( "KeepTime", &nValue ) == NULL )
        { return false; }
        vecPrepareTimeSetting.SetKeepTime( nValue );*/


        // 进入时间
        MeXmlElement* pEnter = pTime->FirstChildElement( "EnterTime" );
        if ( pEnter == NULL )
        { return false; }

        

        if ( pEnter->Attribute( "KeepTime", &nValue ) == NULL )
        { return false; }
        vecEnterTimeSetting.SetKeepTime( nValue );


        // 战斗时间
        MeXmlElement* pFight = pTime->FirstChildElement( "FightTime" );
        if ( pFight == NULL )
        { return false; }

        if ( pFight->Attribute( "KeepTime", &nValue ) == NULL )
        { return false; }
        vecFightTimeSetting.SetKeepTime( nValue );

        // 结束时间
        MeXmlElement* pEnd = pTime->FirstChildElement( "EndTime" );
        if ( pEnd == NULL )
        { return false; }

        if ( pEnd->Attribute( "KeepTime", &nValue ) == NULL )
        { return false; }
        vecEndTimeSetting.SetKeepTime( nValue );

		return true;
    }

    return false;
}


bool GameGuildGeneralBattleConfig::LoadEnterSetting( MeXmlElement* pElement )
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

bool GameGuildGeneralBattleConfig::LoadResourceSetting( MeXmlElement* pElement )
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

bool GameGuildGeneralBattleConfig::LoadKillSetting(  MeXmlElement* pElement )
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

bool GameGuildGeneralBattleConfig::LoadMonsterSetting( MeXmlElement* pElement )
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
bool GameGuildGeneralBattleConfig::LoadKingdomMapSetting( MeXmlElement* pElement )
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
bool GameGuildGeneralBattleConfig::LoadEnterBuff( MeXmlElement* pElement )
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
int GameGuildGeneralBattleConfig::RefreshSetting::nTimeSpace = 180;
int GameGuildGeneralBattleConfig::RefreshSetting::nCount = 5;
int GameGuildGeneralBattleConfig::RefreshSetting::nRadius = 2;
int GameGuildGeneralBattleConfig::RefreshSetting::nType = 0;
bool GameGuildGeneralBattleConfig::LoadGameBattleConfig(const char* FilePath)
{
	//加载公会约战的数据
	if ( FilePath == NULL || FilePath[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( FilePath, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pGuildBattle = pRoot->FirstChildElement( "BattleSettings" );
	if (pGuildBattle)
	{
		if ( pGuildBattle->Attribute("BattleDiffTime", &BattleDiffTime) == NULL)
			return false;
		
		if ( !LoadMapSetting( pGuildBattle ) )
		{ return false; }

		if ( !LoadTimeSetting( pGuildBattle ) )
		{ return false; }

		if ( !LoadEnterSetting( pGuildBattle ) )
		{ return false; }

		if ( !LoadResourceSetting( pGuildBattle ) )
		{ return false; }

		if ( !LoadKillSetting( pGuildBattle ) )
		{ return false; }

		if ( !LoadMonsterSetting( pGuildBattle ) )
		{ return false; }

		if ( !LoadKingdomMapSetting( pGuildBattle ) )
		{ return false; }

		if ( !LoadEnterBuff( pGuildBattle ) )
		{ return false; }

		//加载其他的数据
		int nValue = 0;
		double dValue = 0;
		
		MeXmlElement* pSignUpSetting = pGuildBattle->FirstChildElement( "SignUpSetting" );
		if ( pSignUpSetting == NULL )
		{ return false; }
	    
		if ( pSignUpSetting->Attribute( "MemberCount", &nValue ) == NULL )
		{ return false; }
		xSignUpSetting.SetMinMemberCount( nValue );

		// 刷怪设定
		mapRefreshSetting.clear();
		MeXmlElement* pRefreshSetting = pGuildBattle->FirstChildElement( "RefreshSetting" );
		if ( pRefreshSetting == NULL )
		{ return false; }

		if ( pRefreshSetting->Attribute( "TimeSpace", &nValue ) == NULL )
		{ return false; }
		RefreshSetting::SetTimeSpace( nValue );

		if ( pRefreshSetting->Attribute( "Count", &nValue ) == NULL )
		{ return false; }
		RefreshSetting::SetCount( nValue );

		if ( pRefreshSetting->Attribute( "Radius", &nValue ) == NULL )
		{ return false; }
		RefreshSetting::SetRadius( nValue );

		if ( pRefreshSetting->Attribute( "SummonType", &nValue ) == NULL )
		{ return false; }
		RefreshSetting::SetType( nValue );

		RefreshSetting xSetting;
		MeXmlElement* pBarracks = pRefreshSetting->FirstChildElement( "Barracks" );
		while ( pBarracks != NULL )
		{
			if ( pBarracks->Attribute( "ID", &nValue ) == NULL )
			{ return false; }
			xSetting.SetBarracksID( nValue );

			RefreshSetting::BarracksSetting xRedBarracksSetting;
			MeXmlElement* pRedCamp = pBarracks->FirstChildElement( "RedCamp" );
			if ( pRedCamp == NULL )
			{ return false; }

			if ( pRedCamp->Attribute( "ID", &nValue ) == NULL )
			{ return false; }
			xRedBarracksSetting.SetMonsterID( nValue );

			if ( pRedCamp->Attribute( "PosX", &dValue ) == NULL )
			{ return false; }
			xRedBarracksSetting.SetPosX( static_cast< float >( dValue ) );

			if ( pRedCamp->Attribute( "PosY", &dValue ) == NULL )
			{ return false; }
			xRedBarracksSetting.SetPosY( static_cast< float >( dValue ) );

			if ( pRedCamp->Attribute( "Angle", &nValue ) == NULL )
			{ return false; }

			xRedBarracksSetting.SetAngle(nValue);

			MeXmlElement* pMonsters = pRedCamp->FirstChildElement( "Monsters" );
			while(pMonsters != NULL)
			{
				RefreshSetting::MonsterDataList ML;
				if ( pMonsters->Attribute( "ID", &nValue ) == NULL )
				{ return false; }
				ML.SetIndex( nValue );
		
				MeXmlElement* pMonster = pMonsters->FirstChildElement( "Monster" );
				while ( pMonster != NULL )
				{ 
					RefreshSetting::MonsterData xData;
					if ( pMonster->Attribute( "ID", &nValue ) == NULL )
					{ return false; }
					xData.SetMonsterID( nValue );

					if ( pMonster->Attribute( "RouteID", &nValue ) == NULL )
					{ return false; }
					xData.SetRouteID( nValue );

					 if ( pMonster->Attribute( "PosX", &dValue ) == NULL )
					{ return false; }
					xData.SetPosX( static_cast< float >( dValue ) );

					if ( pMonster->Attribute( "PosY", &dValue ) == NULL )
					{ return false; }
					xData.SetPosY( static_cast< float >( dValue ) );

					if ( pMonster->Attribute( "Angle", &nValue ) == NULL )
					{ return false; }
					xData.SetAngle(nValue);

					ML.AddMonsterData(xData);
					pMonster = pMonster->NextSiblingElement();
				}
				xRedBarracksSetting.AddMonster( ML );
				pMonsters = pMonsters->NextSiblingElement();
			}

			xSetting.SetRedBarracksSetting( xRedBarracksSetting );

			MeXmlElement* pBlueCamp = pBarracks->FirstChildElement( "BlueCamp" );
			if ( pBlueCamp == NULL )
			{ return false; }

			RefreshSetting::BarracksSetting xBlueBarracksSetting;

			if ( pBlueCamp->Attribute( "ID", &nValue ) == NULL )
			{ return false; }
			xBlueBarracksSetting.SetMonsterID( nValue );

			if ( pBlueCamp->Attribute( "PosX", &dValue ) == NULL )
			{ return false; }
			xBlueBarracksSetting.SetPosX( static_cast< float >( dValue ) );

			if ( pBlueCamp->Attribute( "PosY", &dValue ) == NULL )
			{ return false; }
			xBlueBarracksSetting.SetPosY( static_cast< float >( dValue ) );

			if ( pBlueCamp->Attribute( "Angle", &nValue ) == NULL )
			{ return false; }

			xBlueBarracksSetting.SetAngle(nValue);

			pMonsters = pBlueCamp->FirstChildElement( "Monsters" );
			while(pMonsters != NULL)
			{
				RefreshSetting::MonsterDataList ML;
				if ( pMonsters->Attribute( "ID", &nValue ) == NULL )
				{ return false; }
				ML.SetIndex( nValue );
		
				MeXmlElement* pMonster = pMonsters->FirstChildElement( "Monster" );
				while ( pMonster != NULL )
				{ 
					RefreshSetting::MonsterData xData;
					if ( pMonster->Attribute( "ID", &nValue ) == NULL )
					{ return false; }
					xData.SetMonsterID( nValue );

					if ( pMonster->Attribute( "RouteID", &nValue ) == NULL )
					{ return false; }
					xData.SetRouteID( nValue );

					 if ( pMonster->Attribute( "PosX", &dValue ) == NULL )
					{ return false; }
					xData.SetPosX( static_cast< float >( dValue ) );

					if ( pMonster->Attribute( "PosY", &dValue ) == NULL )
					{ return false; }
					xData.SetPosY( static_cast< float >( dValue ) );

					if ( pMonster->Attribute( "Angle", &nValue ) == NULL )
					{ return false; }
					xData.SetAngle(nValue);

					ML.AddMonsterData(xData);
					pMonster = pMonster->NextSiblingElement();
				}
				xBlueBarracksSetting.AddMonster( ML );
				pMonsters = pMonsters->NextSiblingElement();
			}

			xSetting.SetBlueBarracksSetting( xBlueBarracksSetting );

			mapRefreshSetting[ xSetting.GetBarracksID() ] = xSetting;

			pBarracks = pBarracks->NextSiblingElement();
		}

		// 其他阵营怪
		MeXmlElement* pCampMonsters = pGuildBattle->FirstChildElement( "CampMonsters" );
		if ( pCampMonsters == NULL )
		{ return false; }

		vecRedCampMonster.clear();
		MeXmlElement* pRedMonsters = pCampMonsters->FirstChildElement( "RedMonsters" );
		if ( pRedMonsters == NULL )
		{ return false; }

		MeXmlElement* pRedMonster = pRedMonsters->FirstChildElement( "Monster" );
		while ( pRedMonster != NULL )
		{ 
			CampMonster xMonster;
			if ( pRedMonster->Attribute( "ID", &nValue ) == NULL )
			{ return false; }
			xMonster.SetID( nValue );

			if ( pRedMonster->Attribute( "PosX", &dValue ) == NULL )
			{ return false; }
			xMonster.SetPosX( static_cast< float >( dValue ) );

			if ( pRedMonster->Attribute( "PosY", &dValue ) == NULL )
			{ return false; }
			xMonster.SetPosY( static_cast< float >( dValue ) );

			if ( pRedMonster->Attribute( "Angle", &nValue ) == NULL )
			{ return false; }

			xMonster.SetAngle(nValue);

			if ( pRedMonster->Attribute( "BodySize", &dValue ) == NULL )
			{ return false; }
			xMonster.SetBodySize( static_cast< float >( dValue ) );

			vecRedCampMonster.push_back( xMonster );

			pRedMonster = pRedMonster->NextSiblingElement();
		}

		vecBlueCampMonster.clear();
		MeXmlElement* pBlueMonsters = pCampMonsters->FirstChildElement( "BlueMonsters" );
		if ( pBlueMonsters == NULL )
		{ return false; }

		MeXmlElement* pBlueMonster = pBlueMonsters->FirstChildElement( "Monster" );
		while ( pBlueMonster != NULL )
		{ 
			CampMonster xMonster;
			if ( pBlueMonster->Attribute( "ID", &nValue ) == NULL )
			{ return false; }
			xMonster.SetID( nValue );

			if ( pBlueMonster->Attribute( "PosX", &dValue ) == NULL )
			{ return false; }
			xMonster.SetPosX( static_cast< float >( dValue ) );

			if ( pBlueMonster->Attribute( "PosY", &dValue ) == NULL )
			{ return false; }
			xMonster.SetPosY( static_cast< float >( dValue ) );

			if ( pBlueMonster->Attribute( "Angle", &nValue ) == NULL )
			{ return false; }

			xMonster.SetAngle(nValue);

			if ( pBlueMonster->Attribute( "BodySize", &dValue ) == NULL )
			{ return false; }
			xMonster.SetBodySize( static_cast< float >( dValue ) );

			vecBlueCampMonster.push_back( xMonster );

			pBlueMonster = pBlueMonster->NextSiblingElement();
		}

		// 中立怪物
		MeXmlElement* pNormalMonster = pGuildBattle->FirstChildElement( "NormalMonster" );
		while ( pNormalMonster != NULL )
		{
			NormalMonster pMonster;
			if ( pNormalMonster->Attribute( "TimeSpace", &nValue ) == NULL )
			{ return false; }
			pMonster.SetTimeSpace( nValue );

			if ( pNormalMonster->Attribute( "StringID", &nValue ) == NULL )
			{ return false; }
			pMonster.SetString( nValue );

			if ( pNormalMonster->Attribute( "ID", &nValue ) == NULL )
			{ return false; }
			pMonster.SetID( nValue );

			if ( pNormalMonster->Attribute( "PosX", &dValue ) == NULL )
			{ return false; }
			pMonster.SetPosX( static_cast< float >( dValue ) );

			if ( pNormalMonster->Attribute( "PosY", &dValue ) == NULL )
			{ return false; }
			pMonster.SetPosY( static_cast< float >( dValue ) );

			if ( pNormalMonster->Attribute( "Angle", &nValue ) == NULL )
			{ return false; }
			pMonster.SetAngle(nValue);

			if ( pNormalMonster->Attribute( "BodySize", &dValue ) == NULL )
			{ return false; }
			pMonster.SetBodySize( static_cast< float >( dValue ) );

			xNormalMonster.insert(std::map<int,NormalMonster>::value_type(pMonster.GetID(),pMonster));

			pNormalMonster = pNormalMonster->NextSiblingElement();
		}  	

		//战场最终BOSS信息
		MeXmlElement* pBossMonster = pGuildBattle->FirstChildElement( "Boss" );
		if ( pBossMonster == NULL )
		{ return false; }

		MeXmlElement* pRedBOSSMonster = pBossMonster->FirstChildElement( "Red" );
		if ( pRedBOSSMonster == NULL )
		{ return false; }
		if ( pRedBOSSMonster->Attribute( "ID", &nValue ) == NULL )
		{ return false; }
		m_RedBoss.SetID( nValue );
		if ( pRedBOSSMonster->Attribute( "PosX", &nValue ) == NULL )
		{ return false; }
		m_RedBoss.SetPosX( static_cast< float >( nValue ) );
		if ( pRedBOSSMonster->Attribute( "PosY", &nValue ) == NULL )
		{ return false; }
		m_RedBoss.SetPosY( static_cast< float >( nValue ) );
		if ( pRedBOSSMonster->Attribute( "Angle", &nValue ) == NULL )
		{ return false; }

		m_RedBoss.SetAngle(nValue);
		if ( pRedBOSSMonster->Attribute( "BodySize", &nValue ) == NULL )
		{ return false; }
		m_RedBoss.SetBodySize( static_cast< float >( nValue ) );
		if ( pRedBOSSMonster->Attribute( "RouteID", &nValue ) == NULL )
		{ return false; }
		m_RedBoss.SetRouteID(nValue);

		MeXmlElement* pBlueBOSSMonster = pBossMonster->FirstChildElement( "Blue" );
		if ( pBlueBOSSMonster == NULL )
		{ return false; }
		if ( pBlueBOSSMonster->Attribute( "ID", &nValue ) == NULL )
		{ return false; }
		m_BlueBoss.SetID( nValue );
		if ( pBlueBOSSMonster->Attribute( "PosX", &nValue ) == NULL )
		{ return false; }
		m_BlueBoss.SetPosX( static_cast< float >( nValue ) );
		if ( pBlueBOSSMonster->Attribute( "PosY", &nValue ) == NULL )
		{ return false; }
		m_BlueBoss.SetPosY( static_cast< float >( nValue ) );
		if ( pBlueBOSSMonster->Attribute( "Angle", &nValue ) == NULL )
		{ return false; }

		m_BlueBoss.SetAngle(nValue);
		if ( pBlueBOSSMonster->Attribute( "BodySize", &nValue ) == NULL )
		{ return false; }
		m_BlueBoss.SetBodySize( static_cast< float >( nValue ) );
		if ( pBlueBOSSMonster->Attribute( "RouteID", &nValue ) == NULL )
		{ return false; }
		m_BlueBoss.SetRouteID(nValue);
		return true;
	}    
    return false;
}