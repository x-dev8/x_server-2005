/********************************************************************
    Filename:    GameStage.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/
#ifndef __GAMESTAGE_H__
#define __GAMESTAGE_H__

#include "MeRTLibsServer.h"
#include "GameArea.h"
#include "GameZone.h"
#include "MonsterProducer.h"
#include "Mutex.h"
#include "WorkThread.h"
#include "MapConfig.h"
#include "StageDefine.h"
#include "GameTimer.h"
#include "GameDataType.h"
#include "SwMap.h"

class BaseCharacter;
class GamePlayer;

class GameStage
{ 
public:
	enum eEctypeKickType
	{
		eEctypeKickType_no = 0, //不踢
		eEctypeKickType_noTeam = 1,//组队副本中无队伍
		eEctypeKickType_release = 2,//副本销毁
		eEctypeKickType_noguild = 3,//工会副本中没有工会了
	};
public:
    static void RunThread( void* p );

    // 创建场景
    template< class T > 
    static GameStage* CreateStage() { return CNewWithDebug< T >::Alloc( 1, "创建GameStage实例" ); }

    // 释放场景
    template< class T > 
    void ReleaseStage( T* pStage ) { CNewWithDebug< T >::Free( pStage ); }
    virtual void Release() = 0;

    GameStage();
    virtual ~GameStage();

    // 执行更新
    virtual void RunUpdate();    // 1刷怪 2区域 3pChar->Run 4踢玩家

    // 初始化场景
    virtual bool Initialize( MapConfig::MapData* pMapData, uint32 nStageID, uint32 nMapLevel );

    // 判断是否将要销毁
    virtual void CheckStageValid() = 0;

    // 设置场景销毁
    virtual void SetStageWaitRelease( bool bRelease ,bool bNow = false) = 0;

    // 是否等待销毁
    virtual bool IsStageWaitingRelease() = 0;

    // 是否要销毁
    virtual bool IsStageRelease() = 0;

    // 检查是否要剔除玩家
    virtual void CheckKickOutPlayer( BaseCharacter* pChar ) = 0;

    virtual int GetStageLevel() { return 0; }

    // 地图配置属性
    void SetMapData( MapConfig::MapData* pMapData) { m_pMapData = pMapData; }
    MapConfig::MapData* GetMapData() { return m_pMapData; }

    // 场景ID
    uint32 GetStageID(){ return m_nStageID; }
    void SetStageID( uint32 nValue ) { m_nStageID = nValue; }

    // 场景类型
    int GetStageType() { return m_pMapData->GetMapType(); }

    // 是否是副本场景
    bool IsEctypeStage() { return m_pMapData->IsEctypeMap(); }

    // 地图宽度
    int GetWidth() { return m_nMapWidth;}
    void SetWidth( int nValue ) { m_nMapWidth = nValue; }

    // 地图长度
    int GetHeight() { return m_nMapHeight; }
    void SetHeight( int nValue ) { m_nMapHeight = nValue; }

    // 设置存放名
    void SetStoreName( const char *szValue ) { strncpy_s( m_szStageStoreName, sizeof( m_szStageStoreName ), szValue, sizeof( m_szStageStoreName ) - 1 ); }     
    const char* GetStoreName() const { return m_szStageStoreName; }

    // 特定地合成相应的文件名
    void MakeFileName( char *dst, char *szRootDir, char *TailString, size_t dstsize );

    // 获得某个区块指针
    GameArea* GetArea( uint32 nArea );
    
    // 获得某个Zone指针
    GameZone* GetZone( uint32 nID ); 

    // 计算区块信息
    void CalcAreaInfo();                  

    // 计算所属区块
    int TestAreaNumber( int x, int y );  

    // 读取地图数据 分块地图加载读取
    bool LoadStage( const char* szRootDir, uint32 mapId, int nStageWidth, int nStageHeight, int nMapLevel = 0 );    

    // 读取地图数据 一块地图加载读取
    bool LoadStage( const char* szRootDir, uint32 mapId, int nMapLevel = 0 ); 
   
    // 获得角色列表
    GameObjectIdTPL(dr_stageMaxCharacters)& GetCharacterTable() { return m_xCharacterTable; }

    // 获得当前角色个数
    int GetCharacterCount() { return m_xCharacterTable.Count(); } 

    // 获得角色ID
    GameObjectId GetCharacterID( uint32 nIndex ); 

    // 删除角色
    bool DelCharacterID( GameObjectId nID, int index = -1 );

    // 获得9格内的角色ID表
    void Get9AreaList( AreaIndexTPL(Area9)& IdList, int nArea );
    void GetCharIdTable( GameObjectIdTPL( dr_stageMaxCharacters ) &IdList, int nArea );

    // 角色进入
    bool CharacterEnter( BaseCharacter* pChar, const char* szFile, uint32 line ); 

    // 角色离开
    bool CharacterLeave( BaseCharacter* pChar );        

    // 发送视野范围内所有人的信息到该人当他进入
    bool SendAllInfoToCharBy9AreaEnter( BaseCharacter* pChar ); 

    // 发送视野范围内所有人的信息到该人当他离开
    bool SendAllInfoToCharBy9AreaLeave( BaseCharacter* pChar ); 

    // 对触发区域进行检测
    bool CheckZone(); 

    // 刷新当前所在区块  
    bool RefreshNewArea( BaseCharacter* pChar );            

    // 刷新玩家当前能看到的玩家数(即：在9宫格内的玩家)
    int RefreshPlayerCharNumberInView( BaseCharacter* pChar );        

    // 复合计算新视区块表
    void ComplexComputeArea( AreaIndexTPL(Area9) &pOld, AreaIndexTPL(Area9) &pNew, AreaIndexTPL(Area9) &ppNewRes, AreaIndexTPL(Area9) &ppDelRes );    

    // 开启多线程
    bool StartRunThread();

    // 关闭多线程
    bool StopRunThread();

    // 读取怪物配置文件 分块地图加载读取
    bool LoadMonsterConfig( uint32 mapId , const char* szFilePath, int nLandX, int nLandY, int nMapLevel = 0 ); 

    // 读取怪物配置文件 一块地图加载读取 
    bool LoadMonsterConfig( uint32 mapId , const char* szFilePath, int nMapLevel = 0 );   

    // 开启多线程刷怪
    //bool StartRefreshMonsterThread();

    // 关闭多线程刷怪
    //bool StopRefreshMonsterThread();
    //static void RefreshMonsterThread( void* pStage );

    CMonsterProducer& GetMonsterProducer() { return m_xMonsterProducer; }

    // 刷怪
    void RefreshMonster( unsigned int nRefreshCount = 30 );           
    
    // 刷隐藏怪
    void RefreshHideMonster( int x, int y, const char* pZoneName ); 

    // 设置怪物死亡
    void SetMonsterDead( uint32 nIndex );

    // GameStage也能够创建怪物(为了让多线程刷怪尽量不涉及其他)
    //BaseCharacter* CreateMonsterBuild( uint32 monsterId, float fx, float fy, float fdirx, float fdiry, uint8 campId );

    // 创建怪物
    //BaseCharacter* CreateMonster( CMonsterProducer::TagMonsterData* pMonsterInfo, float nX, float nY, float fDirX, float fDirY, int iProductIndex, BOOL bStartUpAI = FALSE, DWORD dwSpecialID = 0, int nInfluence = 0 );

    // lua刷怪
    //void LuaSummonMonster( float x, float y, float dx, float dy, int32 monsterId, uint16 monsterNum, float fRadius, uint8 nSummonType, int nInfluence, uint16 routeId, bool bBornInRouteBegin );
    
    // 创建国家怪
    //void GameStage::CreateCountryMonster(uint32 countryId, uint32 monsterId, uint32 monsterNum, uint32 mapId, float fx, float fy, float fdirx, float fdiry, float fRadius, float fBodySize, GameObjectId summonId );
   
    // 是否人数已经满
    bool IsCaracterFull(); 

    // 坐标是否在场景中
    bool IsInStage( float x, float y, float z );

    // tile是否在场景中
    bool IsInStageTile( int tileX, int tileY, int tileZ );

    // 判断是否可以行走到该点
    static bool MapMoveable( short x,short y ); // 回调函数
    bool Moveable( BaseCharacter *pChar,short x,short y );
    bool StagePosHasNoOne( short stX, short stY );

    //+1,-1占位
    bool IncPosMask( short x,short y );
    void DecPosMask( short x,short y );

    // 查找在一个矩形中的角色列表
    int GetCharacterInRect( RECT&rc, short* pstIDBuf, int iMaxShortNum );  

    // 查找圆形区域内所有角色列表
    int GetAllCharInCircle( BaseCharacter* pSrcChar, D3DXVECTOR3 vPos, std::vector<int32>& vecCharID, int nCharType );
    int GetAllCharInCircle( float fRadius, D3DXVECTOR3 vPos, std::vector<int32>& vecCharID, int nCharType );

    // 查找在一个圆形区域内的角色列表
    int GetCharacterInCircle( D3DXVECTOR3 vPos, float fRadius, GameObjectId* pnIDBuf, int nMaxNum ); 

    // 查找在一个圆形区域内的怪物列表
    int GetMonsterInCircle( D3DXVECTOR3 vPos, float fRadius, GameObjectIdContainer& objects, int nMaxNum, bool bNeedCheckCanAttack = false, BaseCharacter* pSrcChar = NULL ); 

    // 查找某区域内某个技能能攻击的目标
    int GetTargetInCircle( BaseCharacter* pSrcChar, D3DXVECTOR3 vPos, const ItemDefine::SItemSkill* pSkill, GameObjectId* pnIDBuf, int nMaxNum );  
    int GetTargetInCircle( BaseCharacter* pSrcChar, const ItemDefine::SItemSkill* pSkill, GameObjectId *pnIDBuf, int nMaxNum, float fAngle, BOOL bFront );

    // 查找在角色面前一个90度的扇形区域内的角色列表
    int GetCharacterInQuarterCirlce( BaseCharacter* pSrcChar, float fRadius, GameObjectId *pnIDBuf, int nMaxNum );

    // 查找角色半径内所有角色列表
    int GetCharacterInCircle( BaseCharacter* pSrcChar, float fRadius, GameObjectId *pnIDBuf, int nMaxNum, float fAngle, BOOL bFront );

    // 设置任务区域的计数变量
    void SetVarInTaskArea( BaseCharacter* pSrcChar, int nVarId, int nValue, int nRadius, int nType );  

    // 玩家副本信息
    virtual void RecordPlayerDeath ( GamePlayer* pPlayer ) {};
    virtual uint16 GetPlayerDeathCount( GamePlayer* pPlayer ){ return 0; }

    // 检查是否能进入
    virtual bool CheckCanEnterStage( GamePlayer* pPlayer ) = 0;

    //寻路器相关 主线程中使用 关于阻挡的
    void	SetParthFinder( SwMap* pParthFinder );
    SwMap*	GetParthFinder()	{ return m_pParthFinder; }

	//寻路器相关 寻路线程中使用
    void	SetThreadParthFinder( SwMap* pParthFinder );
    SwMap*	GetThreadParthFinder()	{ return m_pThreadParthFinder; }

	//释放本场景中所有的Character
	void ReleaseAllCharacter();

protected:
    typedef std::map< int, GameObjectId > CharacterMap;
    typedef CharacterMap::iterator        CharacterMapIter;

    typedef std::set< GameObjectId > PlayerList;
    typedef PlayerList::iterator     PlayerListIter; 

    virtual bool ProcessEnterStage( GamePlayer* pPlayer ) = 0;
    virtual void ProcessLeaveStage( GamePlayer* pPlayer ) = 0;

protected:
    // 地图配置属性
    MapConfig::MapData* m_pMapData;

    //寻路器,寻路线程中使用
    SwMap* m_pParthFinder;
    //主线程中使用的寻路器
    SwMap* m_pThreadParthFinder;

    // 场景ID
    uint32 m_nStageID;

    // 实际地图宽 单位是2.56 Tile
    int m_nMapWidth;

    // 实际地图高
    int m_nMapHeight; 

    // 触发区块表
    GameZone* m_cgzZone[ StageDefine::constMaxZones ]; 

    // 自动分配的区块表
    GameArea* m_cgaArea[ StageDefine::constMaxAreas ]; 

    // 实际的zones个数 = m_nZoneNumber - 读取失败的Zone数
    int m_iZoneCount; 

    // 区块个数
    int m_iAreaCount;

    // 区块行的长度,即地图横排多少个区块 12 * Tile 单位
    int m_iAreaLength; 

    // 区块行的长度,即地图竖排多少个区块
    int m_iAreaHeight; 

    // 触发AI区块
    RECT m_rcAIArea[ StageDefine::constMaxZones ];   

    // 场所存放名
    char m_szStageStoreName[ StageDefine::constStoreNameMaxSize ]; 
    
    // 刷怪配置
    CMonsterProducer m_xMonsterProducer;

    // 刷怪线程 一条线程够了
    // CWorkThread m_RefreshMonsterThread;

    // 更新线程
    CWorkThread m_RunThread;

    // 所有游戏角色ID表[player character, monster, pet 等]
    GameObjectIdTPL( dr_stageMaxCharacters ) m_xCharacterTable; 

    // 上次更新时间
    uint32 m_dwLastProcessTime;

    // CheckZone定时打印时间
    GameTimerEx _errorCallTime; 

    // 副本中玩家列表
    PlayerList m_setPlayer;
};

////////////////////////////////////////////////////////////////////////////////////////////
//inline
inline GameArea* GameStage::GetArea( uint32 nArea )
{
    if( nArea >= StageDefine::constMaxAreas )
    { return NULL; }

    return m_cgaArea[ nArea ]; 
}

inline GameZone* GameStage::GetZone( uint32 nID )  
{ 
    if( nID >= StageDefine::constMaxZones )
    { return NULL; }

    return m_cgzZone[nID]; 
}

inline bool GameStage::IsInStage( float fx, float fy, float fz )
{
    if ( fx < 0 || fy < 0 || fx >= TileToFloat( GetWidth() ) || fy >= TileToFloat( GetHeight() ) )
    { return false; }

    return true;
}

inline bool GameStage::IsInStageTile( int tileX, int tileY, int tileZ )
{
    if ( tileX < 0 || tileX >= GetWidth() || tileY < 0 || tileY >= GetHeight() )
    { return false; }

    return true;
}

inline GameObjectId GameStage::GetCharacterID( uint32 nIndex )
{
    if ( GetCharacterCount() == 0 )
    { return InvalidGameObjectId; }

    if ( nIndex >= dr_stageMaxCharacters )
    { return InvalidGameObjectId; }

    return m_xCharacterTable[nIndex];
}

inline bool GameStage::DelCharacterID( GameObjectId nID, int index /*= -1*/ )
{
    m_setPlayer.erase( nID );

    if ( index == -1 )
    { return m_xCharacterTable.Del( nID ); }
    else
    { // 根据Index删 
        bool bResult = m_xCharacterTable.Del( index, false ); // 没有删除还是要删除一次
        if ( bResult )
        { return bResult; }
        
        return m_xCharacterTable.Del( nID );
    }
}

#endif

