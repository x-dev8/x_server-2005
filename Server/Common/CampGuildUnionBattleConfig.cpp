#include "CampGuildUnionBattleConfig.h"
#include "Dxsdk\d3dx9math.h"
#include "CountryDefine.h"
bool CampGuildOnceBattleConfig::Init(MeXmlElement* pGuildBattle)
{
	//加载
    double dValue = 0;
	if ( pGuildBattle->Attribute( "battlesum", &BattleSum ) == NULL )
    { return false; }
	int nValue = 0;

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

	if ( !LoadRewardSetting( pGuildBattle ) )
	{ return false; }
	if ( !LoadKingdomMapSetting( pGuildBattle ) )
	{ return false; }

    // 报名设定
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

        if ( pRedCamp->Attribute( "PosX", &dValue ) == NULL )
        { return false; }
        xRedBarracksSetting.SetPosX( static_cast< float >( dValue ) );

        if ( pRedCamp->Attribute( "PosY", &dValue ) == NULL )
        { return false; }
        xRedBarracksSetting.SetPosY( static_cast< float >( dValue ) );

        if ( pRedCamp->Attribute( "Angle", &nValue ) == NULL )
        { return false; }
        
        float fRedDir = nValue * 3.1415926f / 180.f;
        D3DXVECTOR3 vRedDir = D3DXVECTOR3( cos(fRedDir), sin(fRedDir), 0.0f );
        D3DXVec3Normalize( &vRedDir, &vRedDir );
        xRedBarracksSetting.SetDirX( vRedDir.x );
        xRedBarracksSetting.SetDirY( vRedDir.y  );

       /* MeXmlElement* pMonster = pRedCamp->FirstChildElement( "Monster" );
        while ( pMonster != NULL )
        { 
            RefreshSetting::MonsterData xData;
            if ( pMonster->Attribute( "ID", &nValue ) == NULL )
            { return false; }
            xData.SetMonsterID( nValue );

            if ( pMonster->Attribute( "RouteID", &nValue ) == NULL )
            { return false; }
            xData.SetRouteID( nValue );

            xRedBarracksSetting.AddMonster( xData );

            pMonster = pMonster->NextSiblingElement();
        }*/
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
		}


        xSetting.SetRedBarracksSetting( xRedBarracksSetting );

        MeXmlElement* pBlueCamp = pBarracks->FirstChildElement( "BlueCamp" );
        if ( pBlueCamp == NULL )
        { return false; }

        RefreshSetting::BarracksSetting xBlueBarracksSetting;
        if ( pBlueCamp->Attribute( "PosX", &dValue ) == NULL )
        { return false; }
        xBlueBarracksSetting.SetPosX( static_cast< float >( dValue ) );

        if ( pBlueCamp->Attribute( "PosY", &dValue ) == NULL )
        { return false; }
        xBlueBarracksSetting.SetPosY( static_cast< float >( dValue ) );

        if ( pBlueCamp->Attribute( "Angle", &nValue ) == NULL )
        { return false; }

        float fBlueDir = nValue * 3.1415926f / 180.f;
        D3DXVECTOR3 vBlueDir = D3DXVECTOR3( cos(fBlueDir), sin(fBlueDir), 0.0f );
        D3DXVec3Normalize( &vBlueDir, &vBlueDir );
        xRedBarracksSetting.SetDirX( vBlueDir.x );
        xRedBarracksSetting.SetDirY( vBlueDir.y  );

        xBlueBarracksSetting.SetDirX( static_cast< float >( dValue ) );
        xBlueBarracksSetting.SetDirY( static_cast< float >( dValue ) );

        /*pMonster = pBlueCamp->FirstChildElement( "Monster" );
        while ( pMonster != NULL )
        { 
            RefreshSetting::MonsterData xData;
            if ( pMonster->Attribute( "ID", &nValue ) == NULL )
            { return false; }
            xData.SetMonsterID( nValue );

            if ( pMonster->Attribute( "RouteID", &nValue ) == NULL )
            { return false; }
            xData.SetRouteID( nValue );

            xBlueBarracksSetting.AddMonster( xData );

            pMonster = pMonster->NextSiblingElement();
        }*/
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

        float fDir = nValue * 3.1415926f / 180.f;
        D3DXVECTOR3 vDir = D3DXVECTOR3( cos(fDir), sin(fDir), 0.0f );
        D3DXVec3Normalize( &vDir, &vDir );
        xMonster.SetDirX( vDir.x );
        xMonster.SetDirY( vDir.y );

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

        float fDir = nValue * 3.1415926f / 180.f;
        D3DXVECTOR3 vDir = D3DXVECTOR3( cos(fDir), sin(fDir), 0.0f );
        D3DXVec3Normalize( &vDir, &vDir );
        xMonster.SetDirX( vDir.x );
        xMonster.SetDirY( vDir.y );

        if ( pBlueMonster->Attribute( "BodySize", &dValue ) == NULL )
        { return false; }
        xMonster.SetBodySize( static_cast< float >( dValue ) );

        vecBlueCampMonster.push_back( xMonster );

        pBlueMonster = pBlueMonster->NextSiblingElement();
    }

     //中立怪物
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
    /*MeXmlElement* pNormalMonster = pGuildBattle->FirstChildElement( "NormalMonster" );
    if ( pNormalMonster == NULL )
    { return false; }

    if ( pNormalMonster->Attribute( "TimeSpace", &nValue ) == NULL )
    { return false; }
    xNormalMonster.SetTimeSpace( nValue );

    if ( pNormalMonster->Attribute( "StringID", &nValue ) == NULL )
    { return false; }
    xNormalMonster.SetString( nValue );

    if ( pNormalMonster->Attribute( "ID", &nValue ) == NULL )
    { return false; }
    xNormalMonster.SetID( nValue );

    if ( pNormalMonster->Attribute( "PosX", &dValue ) == NULL )
    { return false; }
    xNormalMonster.SetPosX( static_cast< float >( dValue ) );

    if ( pNormalMonster->Attribute( "PosY", &dValue ) == NULL )
    { return false; }
    xNormalMonster.SetPosY( static_cast< float >( dValue ) );

    if ( pNormalMonster->Attribute( "Angle", &nValue ) == NULL )
    { return false; }
    float fNormalDir = nValue * 3.1415926f / 180.f;
    D3DXVECTOR3 vNormalDir = D3DXVECTOR3( cos(fNormalDir), sin(fNormalDir), 0.0f );
    D3DXVec3Normalize( &vNormalDir, &vNormalDir );
    xNormalMonster.SetDirX( vNormalDir.x );
    xNormalMonster.SetDirY( vNormalDir.y );

    if ( pNormalMonster->Attribute( "BodySize", &dValue ) == NULL )
    { return false; }
    xNormalMonster.SetBodySize( static_cast< float >( dValue ) );*/

    return true;
}

CampGuildUnionBattleConfig::CampGuildUnionBattleConfig():m_BattleSum(0)
{

}
CampGuildUnionBattleConfig::~CampGuildUnionBattleConfig()
{

}
bool CampGuildUnionBattleConfig::LoadConfig( const char* szFile )
{
	//加载指定的配置文件 并且填充起来
    if ( szFile == NULL || szFile[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

	MeXmlElement* pGuildUnionBattle = pRoot->FirstChildElement( "GuildUnionBattle" );
    if ( pGuildUnionBattle == NULL )
    { return false; }

	if ( pGuildUnionBattle->Attribute( "battlesum", &m_BattleSum ) == NULL )
    { return false; }

	MeXmlElement* pBattleSettings = pGuildUnionBattle->FirstChildElement( "BattleSettings" );
    while ( pBattleSettings != NULL )
    {
		CampGuildOnceBattleConfig info;
		if(info.Init(pBattleSettings))
		{
			m_Config.insert(std::map<unsigned int,CampGuildOnceBattleConfig>::value_type(info.GetBattleSum(),info));
		}
		pBattleSettings = pBattleSettings->NextSiblingElement();
	}
	return true;
}
CampGuildOnceBattleConfig& CampGuildUnionBattleConfig::GetGuildBattleSumConfig(int BattleSum)
{
	if(BattleSum >= m_BattleSum)
		BattleSum = BattleSum%m_BattleSum;
	if(BattleSum >=0 && BattleSum < m_BattleSum &&  m_Config.count(BattleSum) ==1)
	{
		return m_Config[BattleSum];
	}	
}