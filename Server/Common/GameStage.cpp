#include "GameStage.h"
#include "ShareData.h"
#include "GameWorld.h"
#include "ThreadBuffer.h"
#include "MapArea.h"
#include "GameStageDataCenter.h"
#include "GamePlayer.h"
#include "MonsterCreater.h"
#include "NpcCreater.h"

GameStage::GameStage() : m_pMapData( NULL ), m_iZoneCount( 0 ), m_iAreaCount( 0 ), m_iAreaLength( 0 ), m_iAreaHeight( 0 ), m_nMapWidth( 0 ), m_nMapHeight( 0 ), m_pParthFinder( NULL ), m_pThreadParthFinder( NULL )
{
    m_dwLastProcessTime = HQ_TimeGetTime();
    memset( m_cgaArea, 0, sizeof( m_cgaArea ) );
    memset( m_cgzZone, 0, sizeof( m_cgzZone ) );
    memset( m_rcAIArea, 0, sizeof( m_rcAIArea ) );
    memset( m_szStageStoreName, 0, sizeof( m_szStageStoreName ) );
}

GameStage::~GameStage()
{
    StopRunThread();
    //StopRefreshMonsterThread();

    // 释放本场景中所有的Character
	//DWORD drtime = HQ_TimeGetTime();
	ReleaseAllCharacter();
	//printf("free character: %d\n",HQ_TimeGetTime() - drtime);

    for(int i = 0; i < StageDefine::constMaxAreas; ++i )
    {
        if( m_cgaArea[i] != NULL )
        { m_cgaArea[i]->Release(); }
        m_cgaArea[i] = NULL;
    }

    for( int i = 0; i < StageDefine::constMaxZones; ++i )
    {
        if( m_cgzZone[i] != NULL )
        { m_cgzZone[i]->Release(); }
        m_cgzZone[i] = NULL;
    }

	if (m_pThreadParthFinder)
	{
		delete m_pThreadParthFinder;
	}
	
	if (m_pParthFinder)
	{
		delete m_pParthFinder;
	}
	//printf("free stage: %d\n",HQ_TimeGetTime() - drtime);
}

void GameStage::ReleaseAllCharacter()
{
	std::vector< int > vecCharID; // 非玩家
	for ( int n = 0; n < GetCharacterCount(); ++n )
	{
		int nCharID = GetCharacterID( n );
		BaseCharacter* pBaseChar = theRunTimeData.GetCharacterByID( nCharID );
		if ( pBaseChar != NULL && pBaseChar->IsPlayer() )
		{
			GamePlayer* pPlayer = static_cast< GamePlayer* >( pBaseChar );
			LogMessage::LogLogicError( "account[%u:%s:-] 地图[%s]释放, 里面还有玩家在里面",  pPlayer->GetAccountID(), pPlayer->GetCharName(), /*pPlayer->GetSessionKey(),*/ m_pMapData->MapName.c_str() );
			pPlayer->OnExit( NULL );
			continue;
		}

		vecCharID.push_back( nCharID );
	}

	for ( std::vector< int >::iterator iter = vecCharID.begin(); iter != vecCharID.end(); ++iter )
	{
		GettheWorld().OnDelCharacterOnlyID( *iter );
		theRunTimeData.ReleaseObject( *iter, __FILE__, __LINE__ );
	}
}

bool GameStage::Initialize( MapConfig::MapData* pMapData, uint32 nStageID, uint32 nMapLevel )
{
    // 设置配置引用
    SetMapData( pMapData );
    SetStoreName( pMapData->GetMapFilePath() );
    SetStageID( nStageID );

    // 先设置地图长度 和 高度 
    int nMapWidth = ChunckToTile( pMapData->Column );
    int nMapHeight = ChunckToTile( pMapData->Row );

    SetWidth( nMapWidth );
    SetHeight( nMapHeight );

    // 按只有一个文件信息读入是否成功
    bool bAsOneAreaLoadSuccess = LoadStage( STAGEROOTDIRECTORY, pMapData->Id, nMapLevel );
    if( !bAsOneAreaLoadSuccess )
    { // 不成功 按无缝地图[Stage分块]调用接口
        if( !LoadStage( STAGEROOTDIRECTORY, pMapData->Id, nMapWidth, nMapHeight, nMapLevel ) )
        { //可以立即删除掉
            LogMessage::LogLogicError( "Read %s stage failed.\n", pMapData->GetMapFilePath() );
            return false;
        }        
    }

    return true;
}

void GameStage::RunUpdate()
{
	DECLARE_TIME_TEST
	BEGIN_TIME_TEST( "GameStage[1]" );
    uint32 nCurrentTime = HQ_TimeGetTime();
    uint32 nCostTime = GameTime::GetPassTime( nCurrentTime, m_dwLastProcessTime );
    m_dwLastProcessTime = nCurrentTime;
	END_TIME_TEST_1( "GameStage[1]", 100 );
    // 刷新怪物	
	BEGIN_TIME_TEST( "GameStage[2]" );
    RefreshMonster();
	END_TIME_TEST_1( "GameStage[2]", 100 );
    // 检查zone
	BEGIN_TIME_TEST( "GameStage[3]" );
    CheckZone();
	END_TIME_TEST_1( "GameStage[3]", 100 );
    static CharacterMap mapCharacter;
    mapCharacter.clear();

    static GameObjectId nCharList[ dr_stageMaxCharacters ] = { InvalidGameObjectId };
    memset( nCharList, 0, sizeof( nCharList ) );

    if ( m_xCharacterTable.Count() > dr_stageMaxCharacters)
    { assert( false ); }

    if ( !m_xCharacterTable.CopyCharList( nCharList, dr_stageMaxCharacters ) )
    { return; }
	BEGIN_TIME_TEST( "GameStage[4]" );
    int nLoopCount = GetCharacterCount();
    for( int i = 0; i < nLoopCount; ++i )
    {
        GameObjectId cPID = nCharList[i];
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( cPID );
        if( pChar == NULL )
        {
            mapCharacter.insert( CharacterMap::value_type( i, cPID ) );            
            continue; // 暂时不将此ID删除，最后删除
        }

        pChar->Run( nCostTime );
        CheckKickOutPlayer( pChar );
    }
	END_TIME_TEST_1( "GameStage[4]", 100 );
	BEGIN_TIME_TEST( "GameStage[5]" );
    if ( !mapCharacter.empty() )              //最后将找不到的ID删除
    {
        for ( CharacterMapIter iter = mapCharacter.begin(); iter != mapCharacter.end(); ++iter )
        {
            if ( iter->second == GetCharacterID( iter->first ) )  // 判断是否真的存在列表中
            { DelCharacterID( iter->second, iter->first ); } // 根据下标删除快一些
        }
        mapCharacter.clear();
    }
	END_TIME_TEST_1( "GameStage[5]", 100 );
}

void GameStage::CalcAreaInfo()
{
    m_iAreaLength = ( m_nMapWidth + StageDefine::constAreaSize - 1 ) / StageDefine::constAreaSize;  // width
    m_iAreaHeight = ( m_nMapHeight + StageDefine::constAreaSize - 1 ) / StageDefine::constAreaSize; // height
    m_iAreaCount  = m_iAreaHeight * m_iAreaLength;                    // 个数

    for( int y = 0; y < m_iAreaHeight; ++y )
    {
        for( int x = 0; x < m_iAreaLength; ++x )
        {
            int nAreaIndex = y*m_iAreaLength+x;
            if ( nAreaIndex < 0 || nAreaIndex >= StageDefine::constMaxAreas )
            { continue; }

            GameArea* pGameArea = GameArea::CreateInstance();
            if ( pGameArea == NULL )
            { continue; }

            m_cgaArea[nAreaIndex] = pGameArea;
            m_cgaArea[nAreaIndex]->AddAroundArea( x, y, m_iAreaLength, m_iAreaHeight );
            m_cgaArea[nAreaIndex]->AddAroundArea( x-1, y, m_iAreaLength, m_iAreaHeight );
            m_cgaArea[nAreaIndex]->AddAroundArea( x+1, y, m_iAreaLength, m_iAreaHeight );

            m_cgaArea[nAreaIndex]->AddAroundArea( x, y-1, m_iAreaLength, m_iAreaHeight );
            m_cgaArea[nAreaIndex]->AddAroundArea( x-1, y-1, m_iAreaLength, m_iAreaHeight );
            m_cgaArea[nAreaIndex]->AddAroundArea( x+1, y-1, m_iAreaLength, m_iAreaHeight );

            m_cgaArea[nAreaIndex]->AddAroundArea( x, y+1, m_iAreaLength, m_iAreaHeight );
            m_cgaArea[nAreaIndex]->AddAroundArea( x-1, y+1, m_iAreaLength, m_iAreaHeight );
            m_cgaArea[nAreaIndex]->AddAroundArea( x+1, y+1, m_iAreaLength, m_iAreaHeight );
        }
    }
}

int GameStage::TestAreaNumber( int x, int y )
{
    int xArea = x;
    int yArea = y;

    if( xArea < 0 )
    { xArea = 0; }

    if( yArea < 0 )
    { yArea = 0; }

    if( yArea >= m_nMapHeight )
    { yArea = m_nMapHeight - 1; }

    if( xArea >= m_nMapWidth )
    { xArea = m_nMapWidth - 1; }

    xArea /= StageDefine::constAreaSize;
    yArea /= StageDefine::constAreaSize;

    int nArea = yArea * m_iAreaLength + xArea;
    if( nArea < 0 || nArea >= m_iAreaCount || nArea >= StageDefine::constMaxAreas )
    { nArea = -1; }

    return nArea;
}

bool GameStage::LoadStage( const char* szRootDir, uint32 mapId, int nStageWidth, int nStageHeight, int nMapLevel /* = 0 */ )
{
    if( szRootDir == NULL )
    { return false;     }

    const DWORD dwColorCanWalk = 0xffffffff;
    const DWORD dwColorCannotWalk = 0x00000000;
    const char  cColorCanWalk = 0;
    const char  cColorCannotWalk = 1;

    m_nMapWidth = nStageWidth;
    m_nMapHeight = nStageHeight;

    CalcAreaInfo();

    char szCurMapName[MAX_PATH];
    char szCurFilePath[MAX_PATH];

    if( m_nMapWidth / More_nMapSize == 1 && m_nMapHeight / More_nMapSize == 1 )
    {
        sprintf_s( szCurFilePath, MAX_PATH-1, "%s\\%s\\%s\\%s.monstercfg.xml", szRootDir, m_szStageStoreName, m_szStageStoreName, m_szStageStoreName );
        if( !LoadMonsterConfig( mapId, szCurFilePath, 0, 0, nMapLevel ) )
        {
            LogMessage::LogSystemError( "Load monster config file failed [%s]", szCurFilePath);
            return false;
        }
    }
    else
    {
        LandStageConfig xLandConfig;
        char szPath[MAX_PATH] = {0};
        sprintf_s(szPath, sizeof(szPath)-1, "%s\\%s\\%s.xml", szRootDir, m_szStageStoreName,m_szStageStoreName);
        xLandConfig.loadXMLSettings(szPath);

        for (int x = 0; x < m_nMapWidth/More_nMapSize; x++)
        {
            for (int y = 0; y < m_nMapHeight/More_nMapSize; y++)
            {
                if( !xLandConfig.IsReplaceMap( x, y, szCurFilePath, sizeof(szCurFilePath) ) ) 
                {
                    sprintf_s( szCurMapName, MAX_PATH-1, "%s_%d_%d", m_szStageStoreName,  x, y );
                    sprintf_s( szCurFilePath, MAX_PATH-1, "%s\\%s\\%s\\%s.monstercfg.xml", szRootDir, m_szStageStoreName, szCurMapName, szCurMapName );
                }

                if( !LoadMonsterConfig( mapId, szCurFilePath, x, y, nMapLevel ) )
                {
                    LogMessage::LogSystemError( "Load monster config file failed [%s]", szCurFilePath);
                    return false;
                }
            }
        }
    }

    return true;    
}

bool GameStage::LoadStage(const char* szRootDir, uint32 mapId, int nMapLevel /* = 0 */)
{
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( mapId );
    if ( pMapData == NULL )
    { return NULL; }

    CalcAreaInfo();

    std::string strFilePath = szRootDir;
    strFilePath += "\\";
    strFilePath += pMapData->GetMapMonsterDataFile();

    if( !LoadMonsterConfig( mapId, strFilePath.c_str(), nMapLevel ) )
    {
        LogMessage::LogSystemError( "Load [%s] file failed", strFilePath.c_str() );
        return false;
    }

    return true;   
}

void GameStage::Get9AreaList( AreaIndexTPL(Area9) &IdList, int nArea )
{
    int aX = nArea%m_iAreaLength;
    int aY = nArea/m_iAreaLength;

    int X = 0,Y = 0;

    // 自动不发送不存在的区块
#define TESTINTOB( MaX, MaY ) X = MaX; Y = MaY; \
    if( !(X < 0 || X >= m_iAreaLength || Y < 0 || Y >= m_iAreaHeight) ) \
    { IdList.New( Y*m_iAreaLength + X, false ); }

    TESTINTOB( aX   ,   aY );
    TESTINTOB( aX-1 ,   aY );
    TESTINTOB( aX+1 ,   aY ); 

    TESTINTOB( aX   ,   aY-1 );
    TESTINTOB( aX-1 ,   aY-1 );
    TESTINTOB( aX+1 ,   aY-1 );

    TESTINTOB( aX   ,   aY+1 );
    TESTINTOB( aX-1 ,   aY+1 );
    TESTINTOB( aX+1 ,   aY+1 );
}

void GameStage::GetCharIdTable( GameObjectIdTPL( dr_stageMaxCharacters) &IdList, int nArea )
{
    AreaIndexTPL(Area9) areaList;
    Get9AreaList( areaList, nArea );

    for( int i=0;i<areaList.Count();i++)
    {
        if ( areaList[i] >= StageDefine::constMaxAreas)
        { continue; }

        GameArea* pGameArea = m_cgaArea[ areaList[i] ];
        if ( pGameArea == NULL )
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        { IdList.Add( objectId, false ); }
    }
}

bool GameStage::CharacterEnter( BaseCharacter* pChar,const char* szFile, uint32 line )
{  
    if( pChar == NULL )
    { return false; }

    uint32 dwID = pChar->GetID();
    int    nX   = pChar->GetTileX();
    int    nY   = pChar->GetTileY();

    // 判断增加的位置是否在合法的地图范围内
    if ( !IsInStage( nX, nY, 0) )
    {
        LogMessage::LogLogicError( "GameObject %s pos is slop over. (X: %d>=%d, Y: %d>=%d )", pChar->GetCharName(), nX, GetWidth(), nY, GetHeight() );
        return false;
    }

    int nArea = TestAreaNumber( nX, nY );
    if ( nArea < 0 )
    {
        LogMessage::LogLogicError( "CharacterEnter 坐标信息不对[%d, %d, %d]!", EctypeId2MapId(GetStageID()), nX, nY );
        return false;
    }

    // 加入大表
    if( !m_xCharacterTable.Add( dwID, pChar->IsPlayer() ) )
    {
        LogMessage::LogLogicError( "CharacterEnter 加入角色表失败!" );
        return false;
    }

    // 加入Area表
    if ( !m_cgaArea[nArea]->CharacterEnter( dwID, pChar->IsPlayer() ) )
    {
        LogMessage::LogLogicError( "CharacterEnter[%d] Object进入地图区域错误!", dwID );
        m_xCharacterTable.Del( dwID, pChar->IsPlayer() ); // 开始加的要删除
        return false;
    }

    // 下面逻辑如果有返回 需要清掉 m_CharacterTable 和 m_cgaArea[nArea]
    if ( pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
        if ( !ProcessEnterStage( pPlayer ) )
        { goto ProcessCharListReturn; }


        // 加入玩家列表
        m_setPlayer.insert( pChar->GetID() );
    }

    pChar->SetCurArea( nArea );     // 进入场景以后, 设置当前区域区块
    pChar->SendSyncCharPosToGate(); //发送同步消息到Gate
    pChar->SetActionId( -1 );
    SendAllInfoToCharBy9AreaEnter( pChar );
    pChar->OnEnterStage();      // 进入场景以后的其他的一些处理
    return true;

ProcessCharListReturn:
    m_cgaArea[nArea]->CharacterLeave( dwID, pChar->IsPlayer() );
    m_xCharacterTable.Del( dwID, pChar->IsPlayer() );
    return false;
}

bool GameStage::CharacterLeave( BaseCharacter* pChar )
{
    if( NULL == pChar )
    { return false; }

    GameObjectId dwID  = pChar->GetID();    

    // 删除角色列表
    DelCharacterID( dwID );

    int nArea = pChar->GetCurArea();
    if( nArea >= 0 )
    {
        if ( nArea >= m_iAreaCount )
        { 
            LogMessage::LogLogicError("CharacterLeave::GetCurArea[0x%x][%d] out range[%d*%d]", GetStageID(), nArea, m_iAreaLength, m_iAreaHeight );
            return false; 
        }

        bool bExist = m_cgaArea[ nArea ]->CharacterLeave( dwID, pChar->IsPlayer() );

        if( bExist )
        { SendAllInfoToCharBy9AreaLeave( pChar ); }
        else
        { LogMessage::LogLogicError("场景[0x%x]中Object[%u]离开区块失败Area[%d]", GetStageID(), dwID, nArea ); }
    }

    if ( pChar->IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
        ProcessLeaveStage( pPlayer );
    }

    return true;
}

bool GameStage::SendAllInfoToCharBy9AreaEnter( BaseCharacter* pChar )
{
    if( NULL == pChar )
    { return false; }

    int nArea = TestAreaNumber( pChar->GetTileX(), pChar->GetTileY() ); // 得到当前所在的区块ID
    if( nArea < 0 )
    { return false; }

    int aX = nArea % m_iAreaLength;
    int aY = nArea / m_iAreaLength;
    int X = 0,Y = 0;


    // 自动不发送不存在的区块
#define AREAINFOAUTOMSGTOENTER( MaX, MaY ) X = MaX; Y = MaY; \
    if( !(X < 0 || X >= m_iAreaLength || Y < 0 || Y >= m_iAreaHeight) ) \
    { \
    m_cgaArea[Y*m_iAreaLength+X]->SendAllInfoToChar( pChar->GetID() ); \
    }

    AREAINFOAUTOMSGTOENTER( aX   ,   aY );
    AREAINFOAUTOMSGTOENTER( aX-1 ,   aY );
    AREAINFOAUTOMSGTOENTER( aX+1 ,   aY );

    AREAINFOAUTOMSGTOENTER( aX   ,   aY-1 );
    AREAINFOAUTOMSGTOENTER( aX-1 ,   aY-1 );
    AREAINFOAUTOMSGTOENTER( aX+1 ,   aY-1 );

    AREAINFOAUTOMSGTOENTER( aX   ,   aY+1 );
    AREAINFOAUTOMSGTOENTER( aX-1 ,   aY+1 );
    AREAINFOAUTOMSGTOENTER( aX+1 ,   aY+1 );

    return true;
}

bool GameStage::SendAllInfoToCharBy9AreaLeave( BaseCharacter* pChar )
{
    if( NULL == pChar)
    { return false; }

    int nArea = TestAreaNumber( pChar->GetTileX(), pChar->GetTileY() ); // 得到当前所在的区块ID
    if( nArea < 0 )
    { return false; }

    int aX = nArea % m_iAreaLength;
    int aY = nArea / m_iAreaLength;
    int X = 0,Y = 0;

    // 自动不发送不存在的区块
#define AREAINFOAUTOMSGTOLEAVE( MaX, MaY ) X = MaX; Y = MaY; \
    if( !(X < 0 || X >= m_iAreaLength || Y < 0 || Y >= m_iAreaHeight) ) \
    { \
    m_cgaArea[Y*m_iAreaLength+X]->AllLeaveFromCharSight( pChar->GetID() ); \
    }

    AREAINFOAUTOMSGTOLEAVE( aX   ,   aY );
    AREAINFOAUTOMSGTOLEAVE( aX-1 ,   aY );
    AREAINFOAUTOMSGTOLEAVE( aX+1 ,   aY );

    AREAINFOAUTOMSGTOLEAVE( aX   ,   aY-1 );
    AREAINFOAUTOMSGTOLEAVE( aX-1 ,   aY-1 );
    AREAINFOAUTOMSGTOLEAVE( aX+1 ,   aY-1 );

    AREAINFOAUTOMSGTOLEAVE( aX   ,   aY+1 );
    AREAINFOAUTOMSGTOLEAVE( aX-1 ,   aY+1 );
    AREAINFOAUTOMSGTOLEAVE( aX+1 ,   aY+1 );

    return true;
}

#define ERROR_ZONE( x ) \
    if ( _errorCallTime.DoneTimer( HQ_TimeGetTime())) \
{ \
    char szError[256] = { 0 }; \
    sprintf_s( szError, sizeof(szError)-1, "%d CheckZone MapConfig[%u] 的Zone[%s] t[%d] a[%d]",x, EctypeId2MapId(GetStageID()), pZone->GetZoneName(), t, pZone->GetCoveredArea(t) ); \
    LogMessage::LogSystemError( szError ); \
}

bool GameStage::CheckZone()
{ // 对触发区域进行检测
    _errorCallTime.StartTimer( HQ_TimeGetTime(), 3000 );

    for ( int i=0; i<m_iZoneCount; ++i)
    {
        GameZone* pZone = m_cgzZone[i];
        if ( pZone == NULL )
        { continue; }

        short stCoveredAreaCharCount = 0;

        // 得到Zone覆盖的Area内有无Player
        if ( !pZone->GetCoveredAreaHasPlayer() )
        { // 没有玩家的时候
            for ( int t=0; t<pZone->GetCoveredAreaCount(); t++ )
            {
                if ( pZone->GetCoveredArea(t) >= StageDefine::constMaxAreas)
                {
                    ERROR_ZONE( 1 );
                    continue;
                }

                GameArea* pGameArea = m_cgaArea[pZone->GetCoveredArea(t)];
                if ( pGameArea == NULL )
                {                    
                    ERROR_ZONE( 2 );
                    continue;
                }

                stCoveredAreaCharCount += pGameArea->GetObjectSize();
            }
        }

        if ( stCoveredAreaCharCount != pZone->GetCoveredAreaCharCount() || pZone->GetCoveredAreaHasPlayer() )
        { // 角色个数不一样 或者 有玩家
            pZone->ClearCharacterList();
            pZone->ClearCurPlayerList();
            stCoveredAreaCharCount = 0;
            bool bHasPlayer = false;
            for ( int j=0; j<pZone->GetCoveredAreaCount(); j++ )
            {
                if ( pZone->GetCoveredArea(j) >= StageDefine::constMaxAreas)
                { continue; }

                GameArea* pGameArea = m_cgaArea[pZone->GetCoveredArea(j)];
                if ( pGameArea == NULL)
                { continue; }

                //  遍历AreaId
                std::vector<GameObjectId> notExistObjectIds;
                GameObjectId objectId = InvalidGameObjectId;
                for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
                {
                    BaseCharacter* pChar = theRunTimeData.GetCharacterByID(objectId);
                    if( NULL == pChar)
                    { 
                        notExistObjectIds.push_back( objectId );
                        continue;
                    }

                    if ( pChar->IsPlayer() )
                    { bHasPlayer = true; }

                    if ( pChar->GetTileX() >= pZone->GetOutZone().left && pChar->GetTileX() <= pZone->GetOutZone().right && 
                        pChar->GetTileY() >= pZone->GetOutZone().top  && pChar->GetTileY() <= pZone->GetOutZone().bottom )
                    {
                        pZone->AddCharacterToList( objectId );
                        if ( pChar->IsPlayer() )
                        { pZone->AddCurPlayer2List( objectId ); }
                    }
                }

                // 删除不存在的ObjectId
                std::vector<GameObjectId>::iterator it = notExistObjectIds.begin();
                for ( ; it!=notExistObjectIds.end(); ++it )
                { pGameArea->CharacterLeave( *it, true ); }

                stCoveredAreaCharCount += pGameArea->GetObjectSize();
            }
            pZone->UpdateLastPlayerList();
            pZone->SetCoveredAreaHasPlayer( bHasPlayer             );
            pZone->SetCoveredAreaCharCount( stCoveredAreaCharCount );
        }
    }
    return true;
}

// 刷新当前所在区块
bool GameStage::RefreshNewArea( BaseCharacter* pChar )
{
    if( NULL == pChar )
    { return false; }

    usetime[20].szFunctionName = "GameStage::RefreshNewArea";
    __int64 lasttime = HelperFunc::GetCPUTime();

    GameObjectId dwID = pChar->GetID();
    int nOldArea = pChar->GetCurArea();
    if( nOldArea < 0 || nOldArea >= m_iAreaCount )
    { return false; }

    GameArea* pOldArea = m_cgaArea[nOldArea];
    if ( NULL == pOldArea )
    {
        LogMessage::LogSystemError( "RefreshNewArea(%d) Error::RefreshNewArea !pOldArea", dwID );
        return false;
    }

    int stX = pChar->GetTileX();
    int stY = pChar->GetTileY();
    if( !IsInStageTile( stX, stY, 0 ))
    {
        pChar->Log( " Exit By stX( %d ) >= GetWidth()( %d ) || stY( %d ) >= GetHeight()( %d ) ", stX, GetWidth(), stY, GetHeight() );
        theGameWorld.MoveRoleToSafePosAndExit( pChar );
        return false;
    } 

    int nNewArea = TestAreaNumber( stX, stY );    
    if( nNewArea == nOldArea )
    { // 同一区块
        usetime[20].nTime += (HelperFunc::GetCPUTime() - lasttime);
        return true;
    }

    if( nNewArea < 0 )
    { return false; }

    GameArea* pNewArea = m_cgaArea[nNewArea];
    if ( NULL == pNewArea )
    { return false; }

    if( !pOldArea->CharacterLeave( dwID, pChar->IsPlayer() ) )
    {    
        pChar->Log( "Exit By pOldArea->CharacterLeave" );
        pChar->CriticalError(__FUNCTION__, __FILE__, __LINE__);
        return false;
    }

    if( !pNewArea->CharacterEnter( dwID, pChar->IsPlayer() ) )
    {
        pChar->Log( "Exit By pNewArea->CharacterEnter" );
        pChar->CriticalError(__FUNCTION__, __FILE__, __LINE__);
        return false;
    }

    pChar->SetCurArea( nNewArea );  // 设置新的AreaId
    pChar->SendSyncCharPosToGate(); // 发送同步消息到Gate

    // 计算新进视野区块和移出视野区块
    AreaIndexTPL(Area9) old_area;
    AreaIndexTPL(Area9) new_area;
    AreaIndexTPL(Area9) NewAreaResult;
    AreaIndexTPL(Area9) DelAreaResult;

    Get9AreaList( old_area, nOldArea );
    Get9AreaList( new_area, nNewArea );
    ComplexComputeArea( old_area, new_area, NewAreaResult, DelAreaResult );

    for(int i=0;i<NewAreaResult.Count();i++)
    {
        int nIndex = NewAreaResult[i];
        if ( nIndex >= 0 && nIndex < m_iAreaCount )
        {
            GameArea* pArea = m_cgaArea[ nIndex ];
            if ( NULL == pArea)
            { continue; }

            pArea->SendAllInfoToChar( dwID );
        }
    }

    for( int j=0;j<DelAreaResult.Count(); ++j)
    {
        int nIndex = DelAreaResult[j];
        if ( nIndex >= 0 && nIndex < m_iAreaCount )
        {
            GameArea* pArea = m_cgaArea[ nIndex ];
            if ( NULL == pArea)
            { continue; }

            pArea->AllLeaveFromCharSight( dwID );
        }
    }

    usetime[20].nTime += (HelperFunc::GetCPUTime() - lasttime);
    return true;
}

// 刷新玩家当前能看到的玩家数(即：在9宫格内的玩家)
int GameStage::RefreshPlayerCharNumberInView( BaseCharacter* pChar )
{
    if( pChar == NULL )
    { return 0; }

    int nCurArea = pChar->GetCurArea();
    if( nCurArea < 0 || nCurArea >= StageDefine::constMaxAreas )
    {   
        if( pChar->IsPlayer() )
        {
            pChar->Log( "Exit By nCurArea < 0 || nCurArea( %d ) >= constMaxAreas( %d )", nCurArea, StageDefine::constMaxAreas );
            theGameWorld.MoveRoleToSafePosAndExit( pChar );
        }
        return 0;
    }

    GameArea* pCurArea = m_cgaArea[nCurArea];
    if ( pCurArea == NULL )
    { return 0; }

    int nPlayerCharNumberInView = 0;
    for( int i = 0; i < pCurArea->m_nAroundAreaCount && i < GAME_MAXAROUNDAREANUMBER; i++ )
    {
        int n = pCurArea->m_nAroundAreaId[i];
        if ( n < 0 || n >= StageDefine::constMaxAreas )
        { continue; }

        GameArea* pArea = m_cgaArea[n];
        if ( !pArea )
        { continue; }

        nPlayerCharNumberInView += pArea->GetPlayerObjectSize();
    }
    return nPlayerCharNumberInView;
}

void GameStage::ComplexComputeArea( AreaIndexTPL(Area9) &pOld, AreaIndexTPL(Area9) &pNew, AreaIndexTPL(Area9) &ppNewRes, AreaIndexTPL(Area9) &ppDelRes )
{
    for( int i=0; i<pNew.Count(); i++ )
    {
        int k = 0;
        for( k = 0; k<pOld.Count(); k++)
        {
            if( pNew[i] == pOld[k] )
            { break; }
        }

        if( k == pOld.Count() )
        {
            ppNewRes.New( pNew[i], FALSE );
        }
    }

    for( int j=0; j<pOld.Count(); j++ )
    {
        int k = 0;
        for( k = 0; k<pNew.Count(); k++)
        {
            if( pOld[j] == pNew[k] )
                break;
        }
        if( k == pNew.Count() )
        {
            ppDelRes.New( pOld[j], FALSE );
        }
    }
}
// 逻辑线程  刷怪线程 start
bool GameStage::StartRunThread()
{
    return m_RunThread.CreateThread(RunThread, this);
}

void GameStage::RunThread(void* p)
{
    if (p != NULL)
    {
        static_cast<GameStage*>(p)->RunUpdate();
    }

    Sleep(g_Cfg.dwMapThreadSleep);
}

bool GameStage::StopRunThread()
{
    DWORD dwThreadID = m_RunThread.GetThreadID();
    m_RunThread.StopThreadAndWaitDead();
    if (dwThreadID != 0)
    {
        GettheThreadBuffer().ReleaseBuffer(dwThreadID);
    }
    return true;
}
// 
// bool GameStage::StartRefreshMonsterThread()
// {
//     return m_RefreshMonsterThread.CreateThread(RefreshMonsterThread, this);
// }
// 
// bool GameStage::StopRefreshMonsterThread()
// {
//     DWORD dwThreadID = m_RefreshMonsterThread.GetThreadID();
//     m_RefreshMonsterThread.StopThreadAndWaitDead();
//     if (dwThreadID != 0)
//     {
//         GettheThreadBuffer().ReleaseBuffer(dwThreadID);
//     }
//     return true;
// }

// void GameStage::RefreshMonsterThread(void* pStage)
// {
//     if ( pStage != NULL )
//     {
//         static_cast<GameStage*>(pStage)->RefreshMonster(1000);
//     }
//     Sleep( g_Cfg.dwMapThreadSleep );
// }
// 逻辑线程  刷怪线程 end

void GameStage::SetMonsterDead( uint32 nIndex )
{
    m_xMonsterProducer.KillMonster( nIndex );
}

void GameStage::RefreshMonster( unsigned int nRefreshCount /*= 30 */ )
{
    if( IsCaracterFull() )
    { return; }

    for ( int i = 0; i < nRefreshCount; ++i )
    {
        int nMonsterIndex = m_xMonsterProducer.PeekReliveDeadMonster();
        if ( nMonsterIndex < 0 )
        { break; }

        CMonsterProducer::TagMonsterData* pMonsterData = m_xMonsterProducer.GetMonsterData( nMonsterIndex );
        if( pMonsterData == NULL )
        {   
            LogMessage::LogSystemError( "RefreshMonster->GetMonsterData[%d]mapid[%d] Fail", nMonsterIndex,m_pMapData->Id);
            LogMessage::LogLogicError( "RefreshMonster->GetMonsterData[%d]mapid[%d] Fail", nMonsterIndex,m_pMapData->Id);
            continue;
        }

        ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonster( pMonsterData->nMonsterIndex );
        if ( pMonsterConfig == NULL )
        { continue; }

        MonsterCreateData xCreateData;
        xCreateData.SetMonsterIndex( nMonsterIndex );
        xCreateData.SetMapID( GetStageID() );
        xCreateData.SetMonsterID( pMonsterConfig->stMonsterId );
        xCreateData.SetCount( 1 );
        MonsterCreater::FillMonsterCreateData( xCreateData, pMonsterData );
        MonsterBaseEx* pMonster = MonsterCreater::CreateNormalMonster( xCreateData );
        if ( pMonster == NULL )
        { continue; }

        m_xMonsterProducer.ReliveMonster();

		pMonster->GetMonsterGroupLogic().OnCreateMonster( pMonsterConfig->nGroupID, pMonster );
    }
}

bool GameStage::LoadMonsterConfig( uint32 mapId , const char* szFilePath, int nLandX, int nLandY, int nMapLevel/* = 0 */)
{
    RECT rcArea[ StageDefine::constMaxZones ];

    CStageDataLoader theStageDataLoader;    
    theStageDataLoader.Clear();
    bool bResult = theStageDataLoader.loadXMLSettings( szFilePath );
    if ( !bResult )
    { return false; }

    CMapAreaManager* ptheMapAreaManager = theStageDataLoader.GetMapAreaManager();
    int nZoneCount = 0;
    if ( ptheMapAreaManager )
        nZoneCount = ptheMapAreaManager->GetMaxArea();

    int nStartZoneCount = m_iZoneCount;

    for( int i = 0; i < nZoneCount; i++ )
    {
        // ToLog( ptheMapAreaManager ); 

        SArea* p_SArea = ptheMapAreaManager->GetAreaByID( i );

        rcArea[i].top = p_SArea->m_rcArea.top - 1 + More_nMapSize*nLandY;
        rcArea[i].left = p_SArea->m_rcArea.left - 1 + More_nMapSize*nLandX;
        rcArea[i].right = p_SArea->m_rcArea.right - 1 + More_nMapSize*nLandX;
        rcArea[i].bottom = p_SArea->m_rcArea.bottom - 1 + More_nMapSize*nLandY;

        int nStep = p_SArea->m_istep;

        m_rcAIArea[m_iZoneCount].top = rcArea[i].top - nStep;
        m_rcAIArea[m_iZoneCount].left = rcArea[i].left - nStep;
        m_rcAIArea[m_iZoneCount].bottom = rcArea[i].bottom + nStep;
        m_rcAIArea[m_iZoneCount].right = rcArea[i].right +nStep;

        if( nLandX == 0 && nLandY == 0 )
        {
            if( m_rcAIArea[i].bottom > 127 || m_rcAIArea[i].right > 127 )
            {
                continue;
            }
        }

        GameZone* pGameZone = GameZone::CreateInstance();
        if ( pGameZone == NULL )
        {
            LogMessage::LogSystemError( "CNewWithDebug<GameZone>::Alloc Fail 1" );
            return false;
        }

        m_cgzZone[m_iZoneCount] = pGameZone;
        m_cgzZone[m_iZoneCount]->SetZoneID( m_iZoneCount );
        m_cgzZone[m_iZoneCount]->SetOutZone( m_rcAIArea[i] );
        m_cgzZone[m_iZoneCount]->SetInZone( rcArea[i] );
        m_cgzZone[m_iZoneCount]->SetIntoAreaScript( p_SArea->m_strEnterScript.c_str() );
        m_cgzZone[m_iZoneCount]->SetLeaveAreaScript( p_SArea->m_strLeaveScript.c_str() );
        m_cgzZone[m_iZoneCount]->SetZonePKMode( p_SArea->m_nPKMode );
		m_cgzZone[m_iZoneCount]->SetZoneCanDuel( p_SArea->m_bCanDuel );
        m_cgzZone[m_iZoneCount]->SetPrivateShopEnable( p_SArea->m_bPrivateShop );
        //m_cgzZone[m_iZoneCount]->SetCanFreePk( p_SArea->m_bMapGuildPK );

        int iWAreas = (( m_rcAIArea[i].left - 1 ) % StageDefine::constAreaSize + (m_rcAIArea[i].right - m_rcAIArea[i].left)) / StageDefine::constAreaSize;
        int iHAreas = (( m_rcAIArea[i].top - 1 ) % StageDefine::constAreaSize + (m_rcAIArea[i].bottom - m_rcAIArea[i].top)) / StageDefine::constAreaSize;

        ++iWAreas;
        ++iHAreas;

        int iStartAreaNumber = (( m_rcAIArea[i].top - 1 ) / StageDefine::constAreaSize * m_iAreaLength) + ( ( m_rcAIArea[i].left - 1 ) / StageDefine::constAreaSize);

        for ( int y = 0; y < iHAreas; y++ )
        {
            for ( int x = 0; x < iWAreas; x++ )
            {
                int nAreaId = iStartAreaNumber + y * m_iAreaLength + x;

                m_cgzZone[m_iZoneCount]->SetCoveredArea( y * iWAreas + x, nAreaId );


                //m_cgaArea[nAreaId]->CharacterEnter();
            }
        }

        m_cgzZone[m_iZoneCount]->SetCoveredAreaCount( iWAreas * iHAreas);
        m_cgzZone[m_iZoneCount]->SetZoneName( p_SArea->m_strName.c_str() );
        m_cgzZone[m_iZoneCount]->SetMapXY( nLandX, nLandY );

        ++m_iZoneCount;
    }

    //////////////////////////////////////////////////////////////////////////
    CMonsterConfig* ptheMonCfgFile = theStageDataLoader.GetMonsterConfig();
    // ToLog( ptheMonCfgFile );
    int nMonsterCount = 0;
    if( ptheMonCfgFile )
        nMonsterCount = ptheMonCfgFile->GetMonsterCount();

    for ( int i = 0; i < nMonsterCount; i ++ )
    {
        SMapMonsterInfo* pMonsterStruct = &ptheMonCfgFile->m_vecMonster[i];

        if( !pMonsterStruct->m_bEnable )
            continue;

        if( pMonsterStruct->m_nId < 0 )
        {
            GetErrorLog()->logString( "[Error]->The [%s] monster config is wrong.\n", szFilePath );
            continue;
        }

        if( pMonsterStruct->m_iZone < 0 || pMonsterStruct->m_iZone > nZoneCount )
        {
            GetErrorLog()->logString( "[Error]->Stage [%s] Zone[%d][%s] is over . \n", m_szStageStoreName,pMonsterStruct->m_iZone,pMonsterStruct->m_strName.c_str());
            continue;
        }

        int nZone = nStartZoneCount + pMonsterStruct->m_iZone;
        pMonsterStruct->m_iZone = nZone;

        if( !m_cgzZone[nZone] )
        {
            GetErrorLog()->logString( "[Error]->Stage [%s] Zone[%d][%s] is over .. \n", m_szStageStoreName, nZone, pMonsterStruct->m_strName.c_str());
            continue;
        }

        int iW = m_cgzZone[nZone]->GetInZone().right - m_cgzZone[nZone]->GetInZone().left + 1;
        int iH = m_cgzZone[nZone]->GetInZone().bottom - m_cgzZone[nZone]->GetInZone().top + 1;

        for( int j = 0; j < pMonsterStruct->m_iNumber; ++j )
        {
            int rx = -1;
            int ry = -1;
            int nCount = 0;

            while( !Moveable(NULL,rx,ry) && nCount < 100 )
            {
                rx = rand()%iW + m_cgzZone[nZone]->GetInZone().left;        // 多线程中不能用 theRand 随机类
                ry = rand()%iH + m_cgzZone[nZone]->GetInZone().top;
                ++nCount;
            }

            if( nCount >= 100 )
                break;

            if ( m_cgzZone[nZone]->GetInZone().right - m_cgzZone[nZone]->GetInZone().left <= 0 ||
                m_cgzZone[nZone]->GetInZone().bottom - m_cgzZone[nZone]->GetInZone().top <= 0 )
            {
                // ToLog( false && "Monster Zone false" );
            }

            /*pMonsterStruct->m_nX = pMonsterStruct->m_nX*MAPTILESIZE + nLandX*MAPTILESIZE*128 + MAPTILESIZE/2;
            pMonsterStruct->m_nY = pMonsterStruct->m_nY*MAPTILESIZE + nLandY*MAPTILESIZE*128 + MAPTILESIZE/2;*/

            int nMonsterIndex = m_xMonsterProducer.AddMonster( pMonsterStruct, rx, ry, m_cgzZone[nZone]->GetInZone(), szFilePath, nMapLevel );

            if( nMonsterIndex >= 0 && pMonsterStruct->m_bHide )
            {
                m_cgzZone[nZone]->AddHideMonsterToList( nMonsterIndex );
            }
        }
    }
    return true;
}

bool GameStage::LoadMonsterConfig( uint32 mapId , const char* szFilePath, int nMapLevel/* = 0 */)
{
    CStageDataLoader* pStageDataLoader = GetGameStageDataCenter().GetStageDataLoader( mapId );
    if ( pStageDataLoader == NULL )
    { return false; }

    CMapAreaManager* ptheMapAreaManager = pStageDataLoader->GetMapAreaManager();

    int nZoneCount = 0;
    if ( ptheMapAreaManager )
    { nZoneCount = ptheMapAreaManager->GetMaxArea(); }

    for( int i = 0; i < nZoneCount; ++i )
    {
        SArea* p_SArea = ptheMapAreaManager->GetAreaByID( i );
        if ( NULL == p_SArea )
        { continue; }

        // Ai 区域
        int nStep = p_SArea->m_istep;
        m_rcAIArea[m_iZoneCount].top    = p_SArea->m_rcArea.top - nStep;
        m_rcAIArea[m_iZoneCount].left   = p_SArea->m_rcArea.left - nStep;
        m_rcAIArea[m_iZoneCount].bottom = p_SArea->m_rcArea.bottom + nStep;
        m_rcAIArea[m_iZoneCount].right  = p_SArea->m_rcArea.right + nStep;        

        // zone 信息
        GameZone* pGameZone = NEW_POOL( GameZone );
        if ( pGameZone == NULL )
        {
            LogMessage::LogSystemError( "CNewWithDebug<GameZone>::Alloc Fail 1" );
            return false;
        }

        m_cgzZone[m_iZoneCount] = pGameZone;
        m_cgzZone[m_iZoneCount]->SetZoneID           ( m_iZoneCount             );
        m_cgzZone[m_iZoneCount]->SetOutZone          ( m_rcAIArea[m_iZoneCount] );
        m_cgzZone[m_iZoneCount]->SetInZone           ( p_SArea->m_rcArea        );
        m_cgzZone[m_iZoneCount]->SetIntoAreaScript   ( p_SArea->m_strEnterScript.c_str() );
        m_cgzZone[m_iZoneCount]->SetLeaveAreaScript  ( p_SArea->m_strLeaveScript.c_str() );
        m_cgzZone[m_iZoneCount]->SetZonePKMode       ( p_SArea->m_nPKMode       );
		m_cgzZone[m_iZoneCount]->SetZoneCanDuel( p_SArea->m_bCanDuel );
        m_cgzZone[m_iZoneCount]->SetPrivateShopEnable( p_SArea->m_bPrivateShop  );
        //m_cgzZone[m_iZoneCount]->SetCanFreePk( p_SArea->m_bMapGuildPK );

        int nWidth  = m_rcAIArea[m_iZoneCount].left % StageDefine::constAreaSize + m_rcAIArea[m_iZoneCount].right - m_rcAIArea[m_iZoneCount].left + 1;
        int nHeight = m_rcAIArea[m_iZoneCount].top % StageDefine::constAreaSize + m_rcAIArea[m_iZoneCount].bottom - m_rcAIArea[m_iZoneCount].top  + 1;

        int iWAreas = nWidth  / StageDefine::constAreaSize;
        int iHAreas = nHeight / StageDefine::constAreaSize;

        if ( nWidth % StageDefine::constAreaSize != 0)
        { iWAreas += 1; }

        if ( nHeight % StageDefine::constAreaSize != 0)
        { iHAreas += 1; }

        int iStartAreaNumber =  m_rcAIArea[m_iZoneCount].top / StageDefine::constAreaSize * m_iAreaLength + m_rcAIArea[m_iZoneCount].left / StageDefine::constAreaSize;

        for ( int y=0; y<iHAreas; ++y )
        {
            for ( int x=0; x<iWAreas; ++x )
            {
                int nAreaId = iStartAreaNumber + y * m_iAreaLength + x;
                m_cgzZone[m_iZoneCount]->SetCoveredArea( y * iWAreas + x, nAreaId );
            }
        }

        m_cgzZone[m_iZoneCount]->SetCoveredAreaCount( iWAreas * iHAreas );
        m_cgzZone[m_iZoneCount]->SetZoneName( p_SArea->m_strName.c_str() );        
        int iLandX = p_SArea->m_rcArea.left / More_nMapSize;
        int iLandY = p_SArea->m_rcArea.top / More_nMapSize;
        m_cgzZone[m_iZoneCount]->SetMapXY( iLandX, iLandY );

        ++m_iZoneCount; // 相当与Index
    }

    //////////////////////////////////////////////////////////////////////////
    CMonsterConfig* ptheMonCfgFile = pStageDataLoader->GetMonsterConfig();
    int nMonsterCount = 0;
    if( ptheMonCfgFile )
    { nMonsterCount = ptheMonCfgFile->GetMonsterCount();}

    for ( int i = 0; i < nMonsterCount; ++i )
    {
        SMapMonsterInfo* pMonsterStruct = ptheMonCfgFile->GetMapMonsterInfo(i);
        if ( pMonsterStruct == NULL )
        { continue; }

        if( !pMonsterStruct->m_bEnable )
        { continue; }

        if( pMonsterStruct->m_nId < 0 )
        {
            LogMessage::LogSystemError( "[%s] the monster Id[%d] config is wrong.", szFilePath, pMonsterStruct->m_nId );
            continue;
        }

        int nZone = pMonsterStruct->m_iZone;

        if( nZone < 0 || nZone > nZoneCount || nZone > m_iZoneCount )
        {

            LogMessage::LogSystemError( "Stage[%s] Zone[%d][%s] is over.", m_szStageStoreName, nZone, pMonsterStruct->m_strName.c_str());
            continue;
        }

        if( !m_cgzZone[nZone] )
        {

            LogMessage::LogSystemError( "Stage[%s] Zone[%d][%s] pointer is null.", m_szStageStoreName, nZone, pMonsterStruct->m_strName.c_str());
            continue;
        }

        int iW = m_cgzZone[nZone]->GetInZone().right - m_cgzZone[nZone]->GetInZone().left + 1;
        int iH = m_cgzZone[nZone]->GetInZone().bottom - m_cgzZone[nZone]->GetInZone().top + 1;

        for( int j = 0; j < pMonsterStruct->m_iNumber; ++j )
        {
            int rx = -1;
            int ry = -1;
            int nCount = 0;

            while( !Moveable(NULL,rx,ry) && nCount<100 )
            {
                rx = rand()%iW + m_cgzZone[nZone]->GetInZone().left;
                ry = rand()%iH + m_cgzZone[nZone]->GetInZone().top;
                ++nCount;
            }

            if( nCount >= 100 )
                break;

            if ( m_cgzZone[nZone]->GetInZone().right - m_cgzZone[nZone]->GetInZone().left <= 0 ||
                m_cgzZone[nZone]->GetInZone().bottom - m_cgzZone[nZone]->GetInZone().top <= 0 )
            {

                LogMessage::LogSystemError( "Monster Zone false");
            }

            //pMonsterStruct->m_nX = TileToFloat(pMonsterStruct->m_nX);
            //pMonsterStruct->m_nY = TileToFloat(pMonsterStruct->m_nY);

            int nMonsterIndex = m_xMonsterProducer.AddMonster( pMonsterStruct, rx, ry, m_cgzZone[nZone]->GetInZone(), szFilePath, nMapLevel );

            if( nMonsterIndex >= 0 && pMonsterStruct->m_bHide )
            { m_cgzZone[nZone]->AddHideMonsterToList( nMonsterIndex ); }
        }
    }

    return TRUE;
}

void GameStage::RefreshHideMonster( int x, int y, const char* pZoneName )
{
    for( int i = 0; i < m_iZoneCount; ++i )
    {
        if ( x != m_cgzZone[i]->GetMapX() || y != m_cgzZone[i]->GetMapY() || strcmp( pZoneName, m_cgzZone[i]->GetZoneName() ) != 0 )
        { continue; }

        GameObjectIdTPL(GameZone::constMaxHideMonsters)* pHideMonsterTable = m_cgzZone[i]->GetHideMonsterIndexTable();
        for ( int i = 0; i < pHideMonsterTable->Count(); ++i )
        {
            int nMonsterIndex = (*pHideMonsterTable)[i];
            CMonsterProducer::TagMonsterData* pMonsterData = m_xMonsterProducer.GetMonsterData( nMonsterIndex );
            if( pMonsterData == NULL )
            {
                LogMessage::LogSystemError( "RefreshHideMonster->GetMonsterData[%d] Fail", nMonsterIndex);
                continue;
            }

            ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonster( pMonsterData->nMonsterIndex );
            if ( pMonsterConfig == NULL )
            { continue; }

            MonsterCreateData xCreateData;
            xCreateData.SetMapID( GetStageID() );
            xCreateData.SetMonsterID( pMonsterConfig->stMonsterId );
            xCreateData.SetCount( 1 );
            MonsterCreater::FillMonsterCreateData( xCreateData, pMonsterData );

            MonsterCreater::CreateNormalMonster( xCreateData );
        }
        break;
    }
}

bool GameStage::IsCaracterFull()
{   
    int nCount = m_xCharacterTable.Count();
    if( nCount >= dr_stageMaxCharacters )
    { return true;}

    return false;
}

//BaseCharacter* GameStage::CreateMonsterBuild( uint32 monsterId, float fx, float fy, float fdirx, float fdiry, uint8 campId )
//{
//    if ( IsCaracterFull() )
//    {
//        LogMessage::LogLogicError( "CreateMonsterBuild Stage %d,%d refresh monster failed!,pStage->IsCaracterFull", EctypeId2MapId(GetStageID()), GetStageID() );
//        return NULL;        
//    }
//
//    int nIndex = GettheItemDetail().FindMonsterIndexById( monsterId );
//    if ( nIndex < 0)
//    { return NULL;}
//
//    ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonster( nIndex );
//    if ( pMonsterConfig == NULL )
//    {
//        LogMessage::LogLogicError( "CreateMonsterRoute GettheItemDetail().GetMonster the ID:%d is null", monsterId );
//        return NULL;
//    }
//
//    if ( !IsInStage( fx, fy, 0 ))
//    {
//        LogMessage::LogLogicError( "CreateMonsterRoute Map[%s] Monster[%s][%d] pos or area size is wrong, monster x:%f y:%f StageWidth:%d StageHeight:%d",  GetStoreName(), pMonsterConfig->GetName(), pMonsterConfig->stMonsterId, fx, fy, GetWidth(), GetHeight() );
//        return NULL;
//    }
//
//    uint8 nType = Object_MonsterBuilding;
//    GameObjectId nID = theRunTimeData.CreateObject( (EObjectType)nType );
//    if( InvalidGameObjectId == nID )
//    {
//        LogMessage::LogLogicError( "ShareData::CreateObject Monster Fail" );
//        return NULL;
//    }
//
//    MonsterBuildEx* pChar = (MonsterBuildEx*)theRunTimeData.GetCharacterByID( nID );
//    if( pChar == NULL )
//    {
//        LogMessage::LogLogicError( "ShareData::GetCharacterByID Monster Fail" );
//        return NULL;
//    }
//
//    pChar->SetFightCamp( campId );
//    pChar->SetFloatXF( fx );
//    pChar->SetFloatYF( fy );
//    // 怪物默认值设置
//    pChar->SetMonsterID ( pMonsterConfig->stMonsterId  ); // 设置怪物Id
//    pChar->SetObjType   ( nType                        ); // 设置类型为怪物
//    pChar->SetCanSwitchStage( false                    ); // 设置为不可切换场所
//    pChar->SetStatus    ( CS_IDLE                      ); // 设置初始化状态为空闲
//    pChar->SetDir       ( 0                            );
//    pChar->SetDirX      ( fdirx                        );
//    pChar->SetDirY      ( fdiry                        );
//    pChar->SetCharName  ( pMonsterConfig->GetName()    );
//    pChar->SetMapID     ( GetStageID()                   );
//    pChar->SetProfession( pMonsterConfig->stProfession );
//    pChar->SetModelId   ( pMonsterConfig->iModelID     );
//    //if( pMonsterConfig->bIsDisappear )
//    //{ pChar->SetDisappearTime( pMonsterConfig->dwDisappearTime ); }
//    pChar->SetBodySize        ( pMonsterConfig->fBodyLengthSize      ); // 设置身体大小
//    //pChar->SetDeadScript      ( pMonsterConfig->GetDeadScript()      );
//    //pChar->LoadLuaScript      ( pMonsterConfig->GetAILuaScript()     );    
//    pChar->SetLevel           ( pMonsterConfig->stLevel              ); // 设置等级
//    //pChar->SetRewardExp       ( pMonsterConfig->nRewardExp           ); // 设置可获得的经验
//    //pChar->SetKillSkillExp    ( pMonsterConfig->nSuperfluitySkillExp );
//    //pChar->SetRewardReputation( pMonsterConfig->nRewardReputation    );
//    //pChar->SetRewardExpolit   ( pMonsterConfig->nRewardExploit       );
//    //pChar->SetRewardFriendly  ( pMonsterConfig->nRewardFriendly      );
//    //pChar->SetRewardDaoxing   ( pMonsterConfig->nRewardDaoxing       );
//    //pChar->SetDaoxing         ( pMonsterConfig->nDaoxing             );
//    pChar->m_nBaseEnmityRange   = pMonsterConfig->nBaseEnmityRange;
//    pChar->SetHPMax( pMonsterConfig->nHPMax  ); // HPMax
//    pChar->SetMPMax( pMonsterConfig->stMPMax ); // MPMax
//    pChar->GetCharFightAttr()->hpRestore    .base = pMonsterConfig->stHPRestore ;
//    pChar->GetCharFightAttr()->mpRestore    .base = pMonsterConfig->stMPRestore ;
//    pChar->GetCharFightAttr()->exact        .base = pMonsterConfig->stExact     ;
//    pChar->GetCharFightAttr()->dodge        .base = pMonsterConfig->stDodge     ;
//    pChar->GetCharFightAttr()->attackPhysics.base = pMonsterConfig->fPhysicAtt  ;
//    pChar->GetCharFightAttr()->attackMagic  .base = pMonsterConfig->fMagicAtt   ;
//    pChar->GetCharFightAttr()->defendPhysics.base = pMonsterConfig->fPhysicDef  ;
//    pChar->GetCharFightAttr()->defendMagic  .base = pMonsterConfig->fMagicDef   ;
//    pChar->GetCharFightAttr()->critical     .base = pMonsterConfig->critical    ;
//    pChar->GetCharFightAttr()->tenacity     .base = pMonsterConfig->tenacity    ;
//    pChar->GetCharFightAttr()->criticalIntensity  .base = pMonsterConfig->criticalIntensity ;
//
//    pChar->SetEnmityRate    ( pMonsterConfig->nEnmityRate       );
//    (( MonsterBaseEx* )pChar)->SetEnmity( pMonsterConfig->nEnmity     );
//    pChar->SetSkillColdDown();
//    pChar->SetMonsterType( pMonsterConfig->stMonsterType );// 怪物类型
//    pChar->SetCountry( country_monster );
//
//    // 实际加入到世界中
//    if( !theGameWorld.OnAddCharacterOnlyID(nID))
//    {
//        LogMessage::LogLogicError( "CreateMonsterBuild OnAddCharacterOnlyID 加入怪物[%s]出错", pMonsterConfig->GetName() );
//        theGameWorld.OnDelCharacter( nID );
//        theRunTimeData.ReleaseObject( nID );
//        return NULL;
//    }
//
//    if (!CharacterEnter( pChar, __FILE__, __LINE__ ) )
//    {
//        LogMessage::LogLogicError( "CreateMonsterBuild GameStage->CharacterEnter[%s]出错", pMonsterConfig->GetName() );
//        theGameWorld.OnDelCharacter( nID );
//        theRunTimeData.ReleaseObject( nID );
//        return NULL;
//    }
//
//    return pChar;
//}

//BaseCharacter* GameStage::CreateMonster( CMonsterProducer::TagMonsterData* pMonsterData, float fX, float fY, float fDirX, float fDirY, int iProductIndex, BOOL bStartUpAI, DWORD dwSpecialID, int nInfluence )
//{
//    if ( pMonsterData == NULL )
//    { 
//        LogMessage::LogLogicError( "GameStage::CreateMonster pMonsterInfo == NULL" );
//        return NULL; 
//    }
//
//    if ( IsCaracterFull() )
//    {
//        LogMessage::LogLogicError( "Stage %d refresh monster failed!,pStage->IsCaracterFull", GetStageID() );
//        return NULL;
//    }
//
//    int nIndex = pMonsterData->nMonsterIndex;
//    ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonster( nIndex );
//    if ( pMonsterConfig == NULL )
//    {
//        LogMessage::LogLogicError( "GettheItemDetail().GetMonster the ID:%d is null", pMonsterData->nMonsterIndex );
//        return NULL;
//    }
//
//    if ( fX >= TileToFloat(GetWidth()) || fY >= TileToFloat(GetHeight())|| fX < 0 || fY < 0 )
//    {
//        LogMessage::LogLogicError( "Map[%s] Monster[%s][%d] pos or area size is wrong, monster x:%f y:%f StageWidth:%d StageHeight:%d", 
//            m_pMapData->MapName.c_str(), pMonsterConfig->GetName(), pMonsterConfig->stMonsterId, fX, fY, GetWidth(), GetHeight() );
//        return NULL;
//    }
//
//    int nType = Object_MonsterNormal;
//    GameObjectId nID = InvalidGameObjectId;
//
//    // 确认怪物的类型
//    if ( pMonsterConfig->nMonsterSide > 0)
//    {
//        nType = Object_MonsterPet;
//        nID = theRunTimeData.CreateObject( Object_MonsterPet );
//    }
//    else
//    {
//        nType = Object_MonsterNormal;
//        nID = theRunTimeData.CreateObject( Object_MonsterNormal );
//    }
//
//    if( nID == InvalidGameObjectId )
//    {
//        LogMessage::LogLogicError( "ShareData::CreateObject Monster Fail" );
//        return NULL;
//    }
//
//#ifdef _DEBUG
//    static int id = 0;
//    if ( nID == id )
//    { system("pause"); }
//#endif
//
//    MonsterBaseEx* pChar = (MonsterBaseEx*)theRunTimeData.GetCharacterByID(nID);
//    if( pChar == NULL )
//    {
//        LogMessage::LogLogicError( "ShareData::GetCharacterByID Monster Fail" );
//        return NULL;
//    }
//
//    //怪物默认值设置
//    //pChar->SetCurArea( 0 );                               // 当前所在区块初始化为0
//    pChar->SetMonsterId( pMonsterConfig->stMonsterId );     // 设置怪物Id
//    pChar->SetObjType( nType );                             // 设置类型为怪物
//    pChar->SetCanSwitchStage( false );                      // 设置为不可切换场所
//    pChar->SetStatus( CS_IDLE );                            // 设置初始化状态为空闲
//    pChar->SetSpecialTarget( dwSpecialID );                 // 初始化特殊Id    
//
//    //pChar->SetDirX( ((float)(theRand.rand32()%201)/100) - 1 );
//    //pChar->SetDirY( ((float)(theRand.rand32()%201)/100) - 1 );
//
//    pChar->SetFloatXF( fX );
//    pChar->SetFloatYF( fY );
//    pChar->SetDir ( 0     );
//    pChar->SetDirX( fDirX );
//    pChar->SetDirY( fDirY );
//    pChar->SetCharName( pMonsterConfig->GetName() );
//    pChar->SetMapID(GetStageID());
//    pChar->SetProfession( pMonsterConfig->stProfession );
//    pChar->SetModelId   ( pMonsterConfig->iModelID     );
//    if( pMonsterConfig->bIsDisappear )
//    { pChar->SetDisappearTime( pMonsterConfig->dwDisappearTime ); }
//
//    pChar->SetBodySize        ( pMonsterConfig->fBodyLengthSize      ); // 设置身体大小
//    pChar->SetDeadScript      ( pMonsterConfig->GetDeadScript()      );
//    pChar->LoadLuaScript      ( pMonsterConfig->GetAILuaScript()     );    
//    pChar->SetLevel           ( pMonsterConfig->stLevel              ); // 设置等级
//    pChar->SetRewardExp       ( pMonsterConfig->nRewardExp           ); // 设置可获得的经验
//    pChar->SetKillSkillExp  ( pMonsterConfig->nSuperfluitySkillExp );
//    pChar->SetRewardReputation( pMonsterConfig->nRewardReputation    );
//    pChar->SetRewardExpolit   ( pMonsterConfig->nRewardExploit       );
//    pChar->SetRewardFriendly  ( pMonsterConfig->nRewardFriendly      );  
//    pChar->SetRewardDaoxing   ( pMonsterConfig->nRewardDaoxing       );
//    pChar->SetDaoxing         ( pMonsterConfig->nDaoxing             );
//
//    pChar->nMaxRange            = pMonsterConfig->nMaxRange;
//    pChar->changePassiveConfig  = pMonsterConfig->nChangePassive;
//    pChar->endPassiveTimeConfig = pMonsterConfig->nPassiveTime;
//    pChar->m_nBaseEnmityRange   = pMonsterConfig->nBaseEnmityRange;
//
//    pChar->SetFightModulus( pMonsterConfig->fAttackPhysicsMod, pMonsterConfig->fDefendPhysicsMod, pMonsterConfig->fAttackMagicMod, pMonsterConfig->fDefendMagicMod );
//    //pChar->SetAttackFloat ( pMonsterConfig->sAttackFloating );
//
//    pChar->SetHPMax( pMonsterConfig->nHPMax  ); // HPMax
//    pChar->SetMPMax( pMonsterConfig->stMPMax ); // MPMax
//
//    pChar->GetCharFightAttr()->hpRestore    .base = pMonsterConfig->stHPRestore ;
//    pChar->GetCharFightAttr()->mpRestore    .base = pMonsterConfig->stMPRestore ;
//    pChar->GetCharFightAttr()->exact        .base = pMonsterConfig->stExact     ;
//    pChar->GetCharFightAttr()->dodge        .base = pMonsterConfig->stDodge     ;
//    pChar->GetCharFightAttr()->attackPhysics.base = pMonsterConfig->fPhysicAtt  ;
//    pChar->GetCharFightAttr()->attackMagic  .base = pMonsterConfig->fMagicAtt   ;
//    pChar->GetCharFightAttr()->defendPhysics.base = pMonsterConfig->fPhysicDef  ;
//    pChar->GetCharFightAttr()->defendMagic  .base = pMonsterConfig->fMagicDef   ;
//    pChar->GetCharFightAttr()->critical     .base = pMonsterConfig->critical    ;
//    pChar->GetCharFightAttr()->tenacity     .base = pMonsterConfig->tenacity    ;
//    pChar->GetCharFightAttr()->criticalIntensity  .base = pMonsterConfig->criticalIntensity ;
//    pChar->GetCharFightAttr()->attackSpeed  .base = pMonsterConfig->stAttackRate;
//    //pChar->SetAnkylosisTimeBase(p_MonsterData->stAnkylosis); // 僵硬时间
//    if ( pMonsterData->stViewSightCorrect + pMonsterConfig->stView < 0 )
//    { // 视野
//        pChar->SetViewSight        ( pMonsterConfig->stView      );
//        pChar->SetIdleMoveViewSight( pMonsterConfig->stView      );
//        pChar->SetFightViewSight   ( pMonsterConfig->stFightView );
//    }
//    else
//    {
//        pChar->SetViewSight        ( pMonsterData->stViewSightCorrect + pMonsterConfig->stView );
//        pChar->SetIdleMoveViewSight( pMonsterData->stViewSightCorrect + pMonsterConfig->stView );
//        pChar->SetFightViewSight   ( pMonsterConfig->stFightView                               );
//    }
//
//    // 移动速度
//    if( pMonsterConfig->fIdleMoveSpeed > 1.5f )
//    { pChar->GetCharFightAttr()->moveSpeed.base = 1.5f; }
//    else
//    { pChar->GetCharFightAttr()->moveSpeed.base = pMonsterConfig->fIdleMoveSpeed; }
//
//    pChar->SetNormalMoveSpeed   ( pMonsterConfig->fMoveSpeed      );
//    pChar->SetIdleMoveSpeed     ( pMonsterConfig->fIdleMoveSpeed  );
//    pChar->SetLastMovingSpeed   ( pChar->GetMoveSpeed()           );
//
//    pChar->UpdateCharAllAttibute();
//
//    pChar->SetHP                ( pMonsterConfig->nHPMax          );
//    pChar->SetMP                ( pMonsterConfig->stMPMax         );
//    pChar->SetIdleMoveRate      ( pMonsterConfig->nIdleMoveRate   );
//    pChar->SetCashMoney         ( pMonsterConfig->nCashMoney      );
//    pChar->SetRewardStatusID    ( pMonsterConfig->nRewardStatusID );
//    pChar->SetRewardMulType     ( pMonsterConfig->nRewardMulType  );
//    pChar->SetRewardMulValue    ( pMonsterConfig->nRewardMulValue );
//
//    for ( int i=0; i<ItemDefine::SMonster::MONSTER_SKILL_COUNT; ++i )
//    {
//        pChar->SetSkill     ( i, pMonsterConfig->iSkillID[i]     );
//        pChar->SetSkillLevel( i, pMonsterConfig->stSkillLevel[i] );
//        pChar->SetSkillRate ( i, pMonsterConfig->stSkillRate[i]  );
//    }
//
//    pChar->SetSkillRateTotal();
//    pChar->SetProduceIndex( iProductIndex );
//    pChar->SetThinkTime   ( pMonsterData->stAiValue );
//
//    // 如果怪物不为主动怪
//    if (pMonsterConfig->nIsInitiative == 0)
//    { pChar->bPassiveConfig = true;  } // 设置为被动攻击
//    else
//    { pChar->bPassiveConfig = false; }
//
//    pChar->SetPassiveAttack( pChar->bPassiveConfig ); 
//    pChar->SetEnmityRate    ( pMonsterConfig->nEnmityRate       );
//    pChar->SetEnmity        ( pMonsterConfig->nEnmity           );
//    pChar->SetResistBeMove  ( pMonsterConfig->nResistMove       );
//    pChar->SetResistBeAtt   ( pMonsterConfig->nResistAtt        );
//    pChar->SetResistBeMagic ( pMonsterConfig->nResistMagic      );
//    pChar->SetResistBeTools ( pMonsterConfig->nResistTools      );
//    pChar->SetCanMoveZone   ( pMonsterData->rcBron              );
//    pChar->SetCityMonster   ( pMonsterConfig->bIsCityMonster    );
//    pChar->SetCityDefMonster( pMonsterConfig->bIsCityDefMonster );
//    pChar->SetFightCamp     ( nInfluence );
//
//    // 设置怪物出生位置
//    SFPos2 ptBornPoint;
//    ptBornPoint.x = fX;
//    ptBornPoint.y = fY;
//    pChar->SetBornPoint( ptBornPoint );
//
//    pChar->SetSkill2LowLimit();
//    pChar->SetSkill3LowLimit();
//    pChar->SetSkillColdDown();
//    pChar->SetMonsterType( pMonsterConfig->stMonsterType );// 怪物类型
//
//    //设置怪物掉落的金钱
//    short stMoneyMin = 0;    
//    if ( pMonsterData->stDropMinMoneyCorrect + pMonsterConfig->stDropMinMoney < 0 )
//    { stMoneyMin = pMonsterConfig->stDropMinMoney; }
//    else
//    { stMoneyMin = pMonsterData->stDropMinMoneyCorrect + pMonsterConfig->stDropMinMoney; }
//
//    short stMoneyMax = 0;
//    if ( pMonsterData->stDropMaxMoneyCorrect + pMonsterConfig->stDropMaxMoney < 0 )
//    { stMoneyMax = pMonsterConfig->stDropMaxMoney; }
//    else
//    { stMoneyMax = pMonsterData->stDropMaxMoneyCorrect + pMonsterConfig->stDropMaxMoney; }
//
//    int TempMoney = 0;
//    if( stMoneyMax == 0 )
//    { TempMoney = 0; }
//    else
//    { TempMoney =  stMoneyMin + theRand.rand32() % ( abs( stMoneyMax - stMoneyMin ) + 1 ); }
//
//    //设置掉落倍率
//    if ( pMonsterData->fItemDropMultipleRateCorrect + pMonsterConfig->fItemDropMultipleRate )
//    { pChar->SetItemDropMultiple( pMonsterConfig->fItemDropMultipleRate ); }
//    else
//    { pChar->SetItemDropMultiple( pMonsterData->fItemDropMultipleRateCorrect + pMonsterConfig->fItemDropMultipleRate ); }
//    pChar->SetDead( false );
//
//    if ( bStartUpAI )
//    { pChar->StartUpAI(); }
//
//    // 实际加入到世界中
//    if( !theGameWorld.OnAddCharacterOnlyID(nID))
//    {
//        LogMessage::LogLogicError( "CreateMonster OnAddCharacterOnlyID 加入怪物[%s]出错", pMonsterConfig->GetName() );
//        theGameWorld.OnDelCharacter( nID );
//        theRunTimeData.ReleaseObject( nID );
//        return NULL;
//    }
//
//    if (!CharacterEnter( pChar, __FILE__, __LINE__ ) )
//    {
//        LogMessage::LogLogicError( "GameStage->CharacterEnter[%s]出错", pMonsterConfig->GetName() );
//        theGameWorld.OnDelCharacter( nID );
//        theRunTimeData.ReleaseObject( nID );
//        return NULL;
//    }
//
//    return pChar;
//}

//0 以(x,y)为中心在半径为fRadius的圆内随机刷怪,怪物朝向(dx, dy)
//void GameStage::LuaSummonMonster( float x, float y, float dx, float dy, int32 monsterId, uint16 monsterNum, float fRadius, uint8 nSummonType, int nInfluence, uint16 routeId, bool bBornInRouteBegin )
//{
//    int nMonsterIndex = GettheItemDetail().FindMonsterIndexById( monsterId );
//    if ( nMonsterIndex == -1)
//    {
//        LogMessage::LogLogicError( "LuaSummonMonster 刷怪ID设置不正确 MapID = [0x%x] 怪物ID = [%d]", GetStageID(), monsterId );
//        return;
//    }
//
//    switch( nSummonType )
//    {
//    case 0:
//        {
//            const int nMoveRadius = 2;    
//            for( int i = 0; i < monsterNum; ++i )
//            {
//                CMonsterProducer::TagMonsterData monsterData;
//                monsterData.nMonsterIndex = nMonsterIndex;
//                D3DXVECTOR3 vDir( dx, dy, 0 );
//                vDir.x = ( rand()%1001 - 500 );
//                vDir.y = ( rand()%1001 - 500 );
//                vDir.z = 0;
//                D3DXVec3Normalize( &vDir, &vDir );
//                float fDistance = (float)(rand()%1001)*fRadius*0.001f + 1.0;
//
//                monsterData.x = x + vDir.x * fDistance;
//                monsterData.y = y + vDir.y * fDistance;
//
//                monsterData.rcBron.left    = FloatToTile( monsterData.x ) - nMoveRadius;
//                monsterData.rcBron.right   = FloatToTile( monsterData.x ) + nMoveRadius;
//                monsterData.rcBron.top     = FloatToTile( monsterData.y ) - nMoveRadius;
//                monsterData.rcBron.bottom  = FloatToTile( monsterData.y ) + nMoveRadius;
//                FIX_NORMAL_ZERO( monsterData.rcBron.left );
//                FIX_NORMAL_ZERO( monsterData.rcBron.top  );
//                theGameWorld.CreateMonsterRoute( monsterId, GetStageID(), monsterData.x, monsterData.y, dx, dy, routeId, nInfluence, bBornInRouteBegin, vDir.x * fDistance, vDir.y * fDistance );
//            }
//        }
//        break;
//    default:
//        LogMessage::LogLogicError( "LuaSummonMonster 目前只支持一种刷怪方式", GetStageID(), monsterId );
//        break;
//    }
//}

//void GameStage::CreateCountryMonster(uint32 countryId, uint32 monsterId, uint32 monsterNum, uint32 mapId, 
//                                     float fx, float fy, float fdirx, float fdiry, float fRadius, float fBodySize, 
//                                     GameObjectId summonId )
//{
//    int nMonsterIndex = GettheItemDetail().FindMonsterIndexById( monsterId );
//    if ( nMonsterIndex == -1 )
//    {
//        LogMessage::LogLogicError( "CreateCountryMonster 刷怪ID不正确 MapID = [0x%x] 怪物ID = [%d]", GetStageID(), monsterId );
//        return;
//    }
//    //for ( int i = 0; i < monsterNum; ++i )
//    //{
//    //    theGameWorld.CreateMonsterCountry( countryId, monsterId, mapId, fx, fy, fdirx, fdiry, fRadius, fBodySize, summonId );
//    //}
//}

int GameStage::GetCharacterInRect( RECT& rc, short* pstIDBuf, int iMaxShortNum )
{
    RECT rcSearch;
    if( rc.left >= m_nMapWidth || rc.top >= m_nMapHeight || rc.right < 0 || rc.bottom < 0 )
    { return 0; }

    if( rc.left > rc.right || rc.top > rc.bottom )
    { return 0; }

    if( rc.left < 0 )
    { rcSearch.left = 0; }
    else
    { rcSearch.left = rc.left; }

    if( rc.right >= m_nMapWidth )
    { rcSearch.right = m_nMapWidth - 1; }
    else 
    { rcSearch.right = rc.right; }

    if( rc.top < 0 )
    { rcSearch.top = 0; }
    else
    { rcSearch.top = rc.top; }

    if( rc.bottom >= m_nMapHeight )
    { rcSearch.bottom = m_nMapHeight - 1; }
    else
    { rcSearch.bottom = rc.bottom; }

    //查找涉及的区块
    int iMinXArea,iMaxXArea, iMinYArea,iMaxYArea;
    iMinXArea = TestAreaNumber( rcSearch.left,rcSearch.top );
    iMinYArea = iMinXArea / m_iAreaLength;
    iMinXArea %= m_iAreaLength;

    iMaxXArea = TestAreaNumber( rcSearch.right,rcSearch.bottom );
    iMaxYArea = iMaxXArea / m_iAreaLength;
    iMaxXArea %= m_iAreaLength;

    int iRow,iCol;
    int iArea;
    int iCurID = 0;
    POINT pt;

    //查找在范围内的
    for( iRow = iMinYArea ; iRow <= iMaxYArea ; iRow ++ )
    {
        iArea = iRow * m_iAreaLength;
        iArea += iMinXArea;
        for( iCol = iMinXArea ; iCol <= iMaxXArea ; iCol ++,iArea ++ )
        {
            GameArea* pGameArea = GetArea( iArea );
            if ( pGameArea == NULL )
            { continue; }

            GameObjectId objectId = InvalidGameObjectId;
            for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
            {
                if ( iCurID >= iMaxShortNum )
                { break; }
                BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
                if( !pChar )
                { continue; }

                pt.x = pChar->GetTileX();
                pt.y = pChar->GetTileY();

                if( PtInRect( &rcSearch,pt ) )
                { pstIDBuf[ iCurID ++ ] = objectId; }
            }

            if( iCurID >= iMaxShortNum )
            { break; }
        }

        if( iCurID >= iMaxShortNum )
        { break; }
    }
    return iCurID;
}

int GameStage::GetCharacterInCircle( D3DXVECTOR3 vPos, float fRadius, GameObjectId *pnIDBuf, int nMaxNum )
{ // 查找在一个圆形区域内的角色列表
    int nX = FloatToTile( vPos.x);
    int nY = FloatToTile( vPos.y);

    int nCurArea = TestAreaNumber( nX, nY );
    if( nCurArea < 0 )
    { return 0; }

    int nCharNum = 0;
    GameArea* pTargetPosArea = GetArea( nCurArea );
    if ( pTargetPosArea == NULL)
    { return 0; }

    for( int i=0; i<pTargetPosArea->m_nAroundAreaCount; i++ )
    {
        int nAroundAreaId = pTargetPosArea->m_nAroundAreaId[i];
        GameArea* pGameArea = GetArea( nAroundAreaId );
        if ( pGameArea == NULL )
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            if ( nCharNum >= nMaxNum )
            { break; }

            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
            if( pChar == NULL || pChar->IsItem() )
            { continue; }

            D3DXVECTOR3 vCharPos = pChar->GetPos();
            vCharPos.z = 0;
            vPos.z = 0;

            float fDistance = D3DXVec3Length( &(vCharPos - vPos) );
            if( fDistance < fRadius )
            { pnIDBuf[ nCharNum ++ ] = objectId; }
        }

        if( nCharNum >= nMaxNum )
        { break; }
    }

    return nCharNum;
}

int GameStage::GetMonsterInCircle( D3DXVECTOR3 vPos, float fRadius, GameObjectIdContainer& objects, 
                                  int nMaxNum, bool bNeedCheckCanAttack /*= true */, BaseCharacter* pSrcChar /*= NULL */)
{
    int nX = FloatToTile( vPos.x);
    int nY = FloatToTile( vPos.y);

    int nCurArea = TestAreaNumber( nX, nY );
    if( nCurArea < 0 )
    { return 0; }

    int nCharNum = 0;

    GameArea* pTargetPosArea = GetArea( nCurArea );
    if ( pTargetPosArea == NULL)
    { return 0; }

    for( int i=0; i < pTargetPosArea->m_nAroundAreaCount; ++i )
    {
        int nAroundAreaId = pTargetPosArea->m_nAroundAreaId[i];
        GameArea* pGameArea = GetArea( nAroundAreaId );

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            if ( nCharNum >= nMaxNum )
            { break; }

            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );

            if( NULL == pChar || !pChar->IsMonster() || pChar->IsDead() )
            { continue; }

            MonsterBaseEx* pMonster = (MonsterBaseEx*)pChar;
            short shMonsterType = pMonster->GetMonsterType();
            if ( shMonsterType != eMT_NormalMonster )
            { continue;}

            D3DXVECTOR3 vCharPos = pChar->GetPos();
            vCharPos.z = 0;
            vPos.z     = 0;

            float fDistance = D3DXVec3Length( &(vCharPos - vPos) );
            if( fDistance > fRadius )
            { continue; }

            if ( bNeedCheckCanAttack && NULL != pSrcChar && !pSrcChar->CheckCanAttackTarget( pChar ))
            { continue; }

            objects.push_back( objectId );
            ++nCharNum;

            if ( nMaxNum > 0 && nCharNum >= nMaxNum)
            { break; }
        }
    }

    return nCharNum;
}

int GameStage::GetCharacterInCircle( BaseCharacter* pSrcChar, float fRadius, GameObjectId *pnIDBuf, int nMaxNum, float fAngle, BOOL bFront )
{
    if( !pSrcChar )
    { return 0; }

    D3DXVECTOR3 vPos = pSrcChar->GetPos();
    int nX = FloatToTile( vPos.x );
    int nY = FloatToTile( vPos.y );
    int nCurArea = TestAreaNumber( nX, nY );
    if( nCurArea < 0 )
    { return 0; }

    int nCharNum = 0;
    GameArea* pTargetPosArea = GetArea( nCurArea );
    if ( pTargetPosArea == NULL)
    { return 0; }

    for( int i=0; i<pTargetPosArea->m_nAroundAreaCount; ++i )
    {
        int nAroundAreaId = pTargetPosArea->m_nAroundAreaId[i];
        GameArea* pGameArea = GetArea( nAroundAreaId );
        if ( pGameArea == NULL)
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            if( nCharNum >= nMaxNum )
            { break; }

            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
            if( !pChar || pChar->IsItem())
            { continue; }

            D3DXVECTOR3 vCharPos = pChar->GetPos();
            vCharPos.z = 0;
            vPos.z = 0;
            float fDistance = D3DXVec3Length( &(vCharPos - vPos) );

            if( fDistance < fRadius )
            {
                if( bFront )
                {
                    if( pSrcChar->IsTargetInFront( pChar, fAngle ) )
                    {
                        pnIDBuf[ nCharNum ++ ] = objectId;
                    }
                }
                else
                {
                    if( pSrcChar->IsTargetInBack( pChar, fAngle ) )
                    {
                        pnIDBuf[ nCharNum ++ ] = objectId;
                    }
                }
            }
        }

        if( nCharNum >= nMaxNum )
        { break; }
    }
    return nCharNum;
}

int GameStage::GetTargetInCircle( BaseCharacter* pSrcChar, D3DXVECTOR3 vPos, const ItemDefine::SItemSkill* pSkill, GameObjectId* pnIDBuf, int nMaxNum )
{
    if ( pSkill == NULL || pnIDBuf == NULL || nMaxNum == 0 || pSrcChar == NULL )
    { return 0; }

    int nX = FloatToTile( vPos.x );
    int nY = FloatToTile( vPos.y );

    int nCurArea = TestAreaNumber( nX, nY );
    if( nCurArea < 0 )
    { return 0; }

    int nCharNum = 0;
    GameArea* pTargetPosArea = GetArea( nCurArea );
    if ( pTargetPosArea == NULL)
    { return 0; }

    for( int i = 0; i<pTargetPosArea->m_nAroundAreaCount; ++i )
    {
        int nAroundAreaId = pTargetPosArea->m_nAroundAreaId[i];
        GameArea* pGameArea = GetArea( nAroundAreaId );
        if ( pGameArea == NULL)
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            if( nCharNum >= nMaxNum )
            { break; }

            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );

            if( pChar == NULL || pChar->IsItem() ) 
            { continue; }

            // 是否使用的技能可以对目标造成影响
            if ( !pSrcChar->IsCastTargetRight( pSkill, pChar ) )
            { continue; }

            D3DXVECTOR3 vCharPos = pChar->GetPos();
            vCharPos.z = 0;
            vPos.z = 0;

            float castCorrect = 0.0f;
            if ( pSrcChar->IsPlayer() )
            { castCorrect = 0.5f; }
            else
            { castCorrect = monsterCastCorrect; }

            if( AttackFunction::InAoeRange( pSkill, vPos, vCharPos, pChar->GetBodySize(), castCorrect) )
            {
                pnIDBuf[ nCharNum++ ] = objectId;
            }
        }

        if( nCharNum >= nMaxNum )
        { break; }
    }
    return nCharNum;
}

int GameStage::GetTargetInCircle( BaseCharacter* pSrcChar, const ItemDefine::SItemSkill* pSkill, GameObjectId *pnIDBuf, int nMaxNum, float fAngle, BOOL bFront )
{
    if( pSrcChar == NULL || pSkill == NULL || pnIDBuf == NULL || nMaxNum == 0 )
    { return 0; }

    D3DXVECTOR3 vPos = pSrcChar->GetPos();
    int nX = FloatToTile( vPos.x );
    int nY = FloatToTile( vPos.y );
    int nCurArea = TestAreaNumber( nX, nY );

    if( nCurArea < 0 )
    { return 0; }

    int nCharNum = 0;
    GameArea* pTargetPosArea = GetArea( nCurArea );
    if ( pTargetPosArea == NULL)
    { return 0; }

    for( int i=0; i<pTargetPosArea->m_nAroundAreaCount; i++ )
    {
        int nAroundAreaId = pTargetPosArea->m_nAroundAreaId[i];
        GameArea* pGameArea = GetArea( nAroundAreaId );
        if ( pGameArea == NULL)
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            if( nCharNum >= nMaxNum )
            { break; }

            BaseCharacter* pTargetChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( objectId );

            if( pTargetChar == NULL || pTargetChar->IsItem() )
            { continue; }

            if ( !pSrcChar->IsCastTargetRight( pSkill, pTargetChar ) )
            { continue; }

            D3DXVECTOR3 vCharPos = pTargetChar->GetPos();
            vCharPos.z = 0;
            vPos.z = 0;

            float castCorrect = 0.0f;
            if ( pSrcChar->IsPlayer() )
            { castCorrect = 0.5f; }
            else
            { castCorrect = monsterCastCorrect; }

            if( AttackFunction::InAoeRange( pSkill, vPos, vCharPos, pTargetChar->GetBodySize(), castCorrect) )
            {
                if( bFront )
                {
                    if( pSrcChar->IsTargetInFront( pTargetChar, fAngle ) )
                    { pnIDBuf[ nCharNum++ ] = objectId; }
                }
                else
                {
                    if( pSrcChar->IsTargetInBack( pTargetChar, fAngle ) )
                    { pnIDBuf[ nCharNum++ ] = objectId; }
                }
            }
        }

        if( nCharNum >= nMaxNum )
        { break; }
    }

    return nCharNum;
}

int GameStage::GetAllCharInCircle( BaseCharacter* pSrcChar, D3DXVECTOR3 vPos, std::vector<int32>& vecCharID, int nCharType )
{
    if ( pSrcChar == NULL )
    { return 0; }

    int nX = FloatToTile( vPos.x );
    int nY = FloatToTile( vPos.y );

    int nCurArea = TestAreaNumber( nX, nY );
    if( nCurArea < 0 )
    { return 0; }

    vecCharID.clear();

    GameArea* pTargetPosArea = GetArea( nCurArea );
    if ( pTargetPosArea == NULL)
    { return 0; }

    for( int i = 0; i < pTargetPosArea->m_nAroundAreaCount; ++i )
    {
        int nAroundAreaId = pTargetPosArea->m_nAroundAreaId[i];
        GameArea* pGameArea = GetArea( nAroundAreaId );
        if ( pGameArea == NULL)
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( objectId );

            if( pTargetChar == NULL )
            { continue; }

            switch( nCharType )
            {
            case 0:
                {
                    if ( !pTargetChar->IsMonster() )
                    { continue; }
                }
                break;
            case 1:
                {
                    if ( !pTargetChar->IsPlayer() )
                    { continue; }
                }
                break;
            case 2:
                {
                    if ( !pTargetChar->IsPlayer() && !pTargetChar->IsMonster() )
                    { continue; }
                }
                break;
            }

            vecCharID.push_back( objectId );
        }
    }
    return vecCharID.size();
}

int GameStage::GetAllCharInCircle( float fRadius, D3DXVECTOR3 vPos, std::vector<int32>& vecCharID, int nCharType )
{
    int nX = FloatToTile( vPos.x );
    int nY = FloatToTile( vPos.y );

    int nCurArea = TestAreaNumber( nX, nY );
    if( nCurArea < 0 )
    { return 0; }

    vecCharID.clear();

    GameArea* pTargetPosArea = GetArea( nCurArea );
    if ( pTargetPosArea == NULL)
    { return 0; }

    for( int i = 0; i < pTargetPosArea->m_nAroundAreaCount; ++i )
    {
        int nAroundAreaId = pTargetPosArea->m_nAroundAreaId[i];
        GameArea* pGameArea = GetArea( nAroundAreaId );
        if ( pGameArea == NULL)
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( objectId );

            if( pTargetChar == NULL )
            { continue; }

            D3DXVECTOR3 vCharPos = pTargetChar->GetPos();
            vCharPos.z = 0;
            vPos.z = 0;
            float fDistance = D3DXVec3Length( &(vCharPos - vPos) );
            if ( fDistance > fRadius )
            { continue;	}

            switch( nCharType )
            {
            case 0:
                {
                    if ( !pTargetChar->IsMonster() )
                    { continue; }
                }
                break;
            case 1:
                {
                    if ( !pTargetChar->IsPlayer() )
                    { continue; }
                }
                break;
            case 2:
                {
                    if ( !pTargetChar->IsPlayer() && !pTargetChar->IsMonster() )
                    { continue; }
                }
                break;
            }

            vecCharID.push_back(objectId);
        }
    }
    return vecCharID.size();
}

int GameStage::GetCharacterInQuarterCirlce( BaseCharacter* pSrcChar, float fRadius, GameObjectId *pnIDBuf, int nMaxNum )
{
    if( !pSrcChar )
    { return 0; }

    D3DXVECTOR3 vPos = pSrcChar->GetPos();
    int nX = FloatToTile( vPos.x );
    int nY = FloatToTile( vPos.y );
    int nCurArea = TestAreaNumber( nX, nY );

    if( nCurArea < 0 )
    { return 0; }

    int nCharNum = 0;

    GameArea* pTargetPosArea = GetArea( nCurArea );
    if ( pTargetPosArea == NULL)
    { return 0; }
    for( int i=0; i<pTargetPosArea->m_nAroundAreaCount; i++ )
    {
        int nAroundAreaId = pTargetPosArea->m_nAroundAreaId[i];
        GameArea* pGameArea = GetArea( nAroundAreaId );
        if ( pGameArea == NULL)
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            if( nCharNum >= nMaxNum )
            { break; }
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );

            if( !pChar || pChar->IsItem() )
            { continue; }

            D3DXVECTOR3 vCharPos = pChar->GetPos();
            vCharPos.z = 0;
            vPos.z = 0;

            float fDistance = D3DXVec3Length( &(vCharPos - vPos) );

            if( fDistance < fRadius )
            {
                if( pSrcChar->IsTargetInFront( pChar, D3DX_PI*0.5f ) )
                {
                    pnIDBuf[ nCharNum ++ ] = objectId;
                }
            }
        }

        if( nCharNum >= nMaxNum )
        { break; }
    }
    return nCharNum;
}

void GameStage::SetVarInTaskArea( BaseCharacter* pSrcChar, int nVarId, int nValue, int nRadius, int nType )
{// 设置任务区域的计数变量
    D3DXVECTOR3 vPos = pSrcChar->GetPos();
    int nX = FloatToTile( vPos.x );
    int nY = FloatToTile( vPos.y );

    int nCurArea = TestAreaNumber( nX, nY );
    if (nCurArea < 0)
    { return;}

    GameArea* pTargetPosArea = GetArea( nCurArea );
    if ( pTargetPosArea == NULL)
    { return; }

    for ( int i = 0; i < GAME_MAXAROUNDAREANUMBER; ++i )
    {
        int nAroundAreaId = pTargetPosArea->m_nAroundAreaId[i];
        GameArea* pGameArea = GetArea( nAroundAreaId );
        if ( pGameArea == NULL)
        { continue; }

        GameObjectId objectId = InvalidGameObjectId;
        for ( uint32 currentIndex = 0; (objectId = pGameArea->GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
            if ( pChar == NULL || !pChar->IsPlayer() )
            { continue;}

            D3DXVECTOR3 vCharPos = pChar->GetPos();
            vCharPos.z = 0;
            vPos.z = 0;
            float fDistance = D3DXVec3Length( &(vCharPos - vPos) ); //得到距离
            if ( (int)fDistance > nRadius )
            { continue;}

            GamePlayer* pPlayer = (GamePlayer*)pChar;

            switch (nType)
            {
            case StageDefine::ECountryType:
                {
                    if ( pPlayer->GetCountry() != pSrcChar->GetCountry() )
                    { continue;}

                    pPlayer->SetVar(nVarId, nValue);
                }
                break;
            case StageDefine::EGuildType:
                {
                    if ( pPlayer->GetGuildID() != 0 && pSrcChar->GetGuildID() != 0 && pPlayer->GetGuildID() == pSrcChar->GetGuildID() )
                    {
                        pPlayer->SetVar(nVarId, nValue);
                    }
                }
                break;
            default:
                break;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//寻路
static GameStage *gCallBackPoint = 0;
static BaseCharacter* gCallChar = 0;

//回调函数
bool GameStage::MapMoveable( short x,short y )
{
    return gCallBackPoint->Moveable( gCallChar,x,y );
}

bool GameStage::Moveable( BaseCharacter *pChar,short x,short y )
{
    if( x < 0 || y < 0  || x >= m_nMapWidth || y >= m_nMapHeight )
        return false;        
    return true;
}

bool GameStage::StagePosHasNoOne( short stX, short stY )
{
    if( stX < 0 || stY < 0 
        || stX >= m_nMapWidth
        || stY >= m_nMapHeight )
    {
        return false;        
    }
    return true;
}

//地图占位
//0:可以行走
//1:不可以行走(静态占位)
//[2,255]:动态占位
bool GameStage::IncPosMask( short x,short y )
{
    if( x < 0 || x >= m_nMapWidth
        || y < 0 || y >= m_nMapHeight )
    {        
        return false;
    }
    return true;
}

void GameStage::DecPosMask( short x,short y )
{
    //return;
    if( x < 0 || x >= m_nMapWidth
        || y < 0 || y >= m_nMapHeight )
    {
        return;
    }
}

void GameStage::SetParthFinder( SwMap* pParthFinder )
{
    if ( m_pParthFinder )
        delete m_pParthFinder;
    m_pParthFinder = pParthFinder;
}

void GameStage::SetThreadParthFinder( SwMap* pParthFinder )
{
    if ( m_pThreadParthFinder )
        delete m_pThreadParthFinder;
    m_pThreadParthFinder = pParthFinder;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
