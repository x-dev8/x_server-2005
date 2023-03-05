#include "CampGuildBattleConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "Dxsdk\d3dx9math.h"

int CampGuildBattleConfig::RefreshSetting::nTimeSpace = 180;
int CampGuildBattleConfig::RefreshSetting::nCount = 5;
int CampGuildBattleConfig::RefreshSetting::nRadius = 2;
int CampGuildBattleConfig::RefreshSetting::nType = 0;

bool CampGuildBattleConfig::LoadConfig( const char* szFile )
{
    if ( !CampBattleConfig::LoadConfig( szFile ) )
    { return false; }

    if ( szFile == NULL || szFile[ 0 ] == 0 )
    { return false; }

    MeXmlDocument xMeXml;
    if ( !xMeXml.LoadFile( szFile, 1 ) )
    { return false; }

    MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
    if ( pRoot == NULL )
    { return false; }

    MeXmlElement* pGuildBattle = pRoot->FirstChildElement( "BattleSettings" );
    if ( pGuildBattle == NULL )
    { return false; }

    int nValue = 0;
    double dValue = 0;

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
        
        /*loat fRedDir = nValue * 3.1415926f / 180.f;
        D3DXVECTOR3 vRedDir = D3DXVECTOR3( cos(fRedDir), sin(fRedDir), 0.0f );
        D3DXVec3Normalize( &vRedDir, &vRedDir );
        xRedBarracksSetting.SetDirX( vRedDir.x );
        xRedBarracksSetting.SetDirY( vRedDir.y  );*/
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

       /* float fBlueDir = nValue * 3.1415926f / 180.f;
        D3DXVECTOR3 vBlueDir = D3DXVECTOR3( cos(fBlueDir), sin(fBlueDir), 0.0f );
        D3DXVec3Normalize( &vBlueDir, &vBlueDir );
        xRedBarracksSetting.SetDirX( vBlueDir.x );
        xRedBarracksSetting.SetDirY( vBlueDir.y  );*/
		xBlueBarracksSetting.SetAngle(nValue);

        //xBlueBarracksSetting.SetDirX( static_cast< float >( dValue ) );
       // xBlueBarracksSetting.SetDirY( static_cast< float >( dValue ) );
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

       /* pMonster = pBlueCamp->FirstChildElement( "Monster" );
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

        /*float fDir = nValue * 3.1415926f / 180.f;
        D3DXVECTOR3 vDir = D3DXVECTOR3( cos(fDir), sin(fDir), 0.0f );
        D3DXVec3Normalize( &vDir, &vDir );
        xMonster.SetDirX( vDir.x );
        xMonster.SetDirY( vDir.y );*/

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

        /*float fDir = nValue * 3.1415926f / 180.f;
        D3DXVECTOR3 vDir = D3DXVECTOR3( cos(fDir), sin(fDir), 0.0f );
        D3DXVec3Normalize( &vDir, &vDir );
        xMonster.SetDirX( vDir.x );
        xMonster.SetDirY( vDir.y );*/

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
    
    /*float fNormalDir = nValue * 3.1415926f / 180.f;
    D3DXVECTOR3 vNormalDir = D3DXVECTOR3( cos(fNormalDir), sin(fNormalDir), 0.0f );
    D3DXVec3Normalize( &vNormalDir, &vNormalDir );
    xNormalMonster.SetDirX( vNormalDir.x );
    xNormalMonster.SetDirY( vNormalDir.y );*/

	

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
    /*float fDir = nValue * 3.1415926f / 180.f;
    D3DXVECTOR3 vDir = D3DXVECTOR3( cos(fDir), sin(fDir), 0.0f );
    D3DXVec3Normalize( &vDir, &vDir );
    m_RedBoss.SetDirX( vDir.x );
    m_RedBoss.SetDirY( vDir.y );*/
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
   /* fDir = nValue * 3.1415926f / 180.f;
    vDir = D3DXVECTOR3( cos(fDir), sin(fDir), 0.0f );
    D3DXVec3Normalize( &vDir, &vDir );
    m_BlueBoss.SetDirX( vDir.x );
    m_RedBoss.SetDirY( vDir.y );*/
	m_BlueBoss.SetAngle(nValue);
    if ( pBlueBOSSMonster->Attribute( "BodySize", &nValue ) == NULL )
    { return false; }
    m_BlueBoss.SetBodySize( static_cast< float >( nValue ) );
	if ( pBlueBOSSMonster->Attribute( "RouteID", &nValue ) == NULL )
    { return false; }
	m_BlueBoss.SetRouteID(nValue);

	//额外的奖励信息
	MeXmlElement* pOtherRewardSetting = pGuildBattle->FirstChildElement( "OtherRewardSetting" );
    if ( pOtherRewardSetting == NULL )
    { return false; }
	
	if ( pOtherRewardSetting->Attribute( "WinItemID", &nValue ) == NULL )
    { return false; }
	m_OtherRweard.SetWinItemID(nValue);
    if ( pOtherRewardSetting->Attribute( "LoseItemID", &nValue ) == NULL )
    { return false; }
    m_OtherRweard.SetLoseItemID(nValue);
    if ( pOtherRewardSetting->Attribute( "OtherSum", &nValue ) == NULL )
    { return false; }
    m_OtherRweard.SetOtherSum(nValue);
    if ( pOtherRewardSetting->Attribute( "OtherItemID", &nValue ) == NULL )
    { return false; }
	m_OtherRweard.SetOtherItemID(nValue);
	if ( pOtherRewardSetting->Attribute( "WinPoint", &nValue ) == NULL )
    { return false; }
    m_OtherRweard.SetWinPoint(nValue);
    if ( pOtherRewardSetting->Attribute( "LosePoint", &nValue ) == NULL )
    { return false; }
	m_OtherRweard.SetLosePoint(nValue);
    return true;
}