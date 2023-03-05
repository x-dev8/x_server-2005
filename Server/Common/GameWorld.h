/********************************************************************
    Filename:    GameWorld.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_GAMEWORLD_H__
#define __GAMESERVER_GAMEWORLD_H__

#include "MapConfig.h"
#include "NormalStage.h"
#include "EctypeStage.h"
#include "Mutex.h"
#include "DropItem.h"
#include "NpcInfo.h"
#include "CountryConfig.h"
#include "MonsterProtectedEx.h"
#include "MonsterPetTrap.h"
#include "MonsterBuildEx.h"
#include "MonsterNurturePet.h"

extern SProcessTime gwusetime[200];

class CEffectChar;
class ItemCharacter;

#define theGameWorld GettheWorld()

class GameWorld
{ // 游戏世界类
public:
    enum EConstDefine
    {
        constMaxCharacters     = dr_worldMaxCharacters,   // 最大角色数
        //constMaxStages       = dr_worldMaxStages,       // 活动场所个数
        constRefreshStagesRate = dr_refreshstagezonerate, // 刷新触发区域的频率
    };

    enum EExternMessage
    { // 消息定义
        ExtMsg_AddCharacter  , // 加入角色
        ExtMsg_DelCharacter  , // 删除角色
        ExtMsg_RefreshCurArea, // 刷新当前所在区块
        ExtMsg_ChangeMapTest , // 场景切换检测
        ExtMsg_FlashMoveTo   , // 角色瞬间移动到
        ExtMsg_EnterStage    , // 角色进入场景
        ExtMsg_LeaveStage    , // 角色离开场景
    };

    struct SFlashMoveTo
    {
        DWORD dwMapID;
        short x,y;
        float fDir;
    };
   
    struct SSafePos
    { // 游戏中的安全位置，位置出错时，将角色送到这个位置
        DWORD dwMapID;
        short x,y;
    };

    struct SLoadMapInfo
    {
        GameWorld* pGameWorld;
        DWORD dwMapId;
        DWORD dwEctypeId;
        unsigned short ustLevel;
        DWORD dwStartTime;
        DWORD dwReserveValue;
		GS2CSCreateMulitStageAck	mca;
		bool sendtocenter;
    };

	//多线程创建地图需要同步的信息
	typedef std::vector< GameObjectId > vecSSynStageInfoNpc;
	typedef vecSSynStageInfoNpc::iterator SynStageNpcIter;
	struct SSynStageInfo
	{
		SSynStageInfo()
		{
			pStage = NULL;
			_vecSynStageNpc.clear();
			memset(&mca,0,sizeof(mca));
			sendtocenter = false;
		}

		GameStage*					pStage;
		vecSSynStageInfoNpc			_vecSynStageNpc;
		GS2CSCreateMulitStageAck	mca;
		bool						sendtocenter;
		DWORD						dwStartTime;
		DWORD						dwReserveValue;
	};

public:
    GameWorld();
    virtual ~GameWorld();
    
    bool           Process();         // 处理函数
    bool           GlobalMessage( EExternMessage msg, WPARAM wParam = NULL, LPARAM lParam = NULL ); // 消息接口函数
    bool           InitStages();      // 初始化地图
	
	// 创建场景 单线程/多线程 
    GameStage*     SingleCreateStage( uint32 dwMapId, uint32 dwEctypeId );	
    GameStage*     MultiCreateStage( uint32 dwMapId, uint32 dwEctypeId, uint16 ustLevel = 0, uint32 dwReserveValue = 0,GS2CSCreateMulitStageAck* pMsg = NULL);
    
	bool           ReleaseTheStage( uint32 dwEctypeId );// 单个 释放  地图
    void           TermStages();      // 全部 释放  地图

    static void    AutoSave(void* p); // 自动保存系统角色数据 全局时间算法
    static void    AutoSaveUpdate();  // 自动保存系统角色数据 单个角色时间算法

	//计算 个人/队伍 计算副本id
    DWORD          MakeEctypeStageID( MapConfig::MapData* pMapData, BaseCharacter* pChar, int nMapLevel = 0 );
	DWORD		   MakeEctypeStageIDByTeamID(MapConfig::MapData* pMapData,unsigned int TeamID);

    GameStage*     FindMultiTeamStage( MapConfig::MapData* pMapData, DWORD dwTeamSessionID );//查找队伍副本
    GameStage*     FindMultiGuildStage( MapConfig::MapData* pMapData, DWORD dwGuildID );	 //查找公会副本

    GameStage*     GetStageById( DWORD dwMapID ); // 获得指定的场所
    
    GameStage*     GetActiveStageInWorld();	//尼玛为什么会有这个接口...获得第一个副本.

	int            GetStageCount(){ return (int)m_mapGameStage.size(); }//获得运行副本的数量
	DWORD          GetMapCount( DWORD dwMapId );			//获得某个id地图的数量

	// 获得某个地图的所有运行时id和数据
	void           GetCurMapStage( DWORD ustMapID, std::vector< GameStage* >& vecStage );
	bool           GetCurMapStage( DWORD dwMapId,  std::vector<DWORD>& vtEctypeId );

	unsigned long  GetEctypeMapLastId( unsigned long uEctypeMapDataId , bool bIncreaseAfterGet = false );
	unsigned long  GetEctypeMapID( unsigned long uEctypeMapDataId , bool bIncreaseAfterGet = false );

	int            GetCreateLoadMapCount( DWORD dwMapID );		//返回m_vecCreateMapInfo的数量
	//std::string    GetMonsterDataFilePath( const std::string& stageName );
	
	size_t		   GetObjectSize()		 { return _objectIds.size(); }// 得到Object的Size
	size_t		   GetPlayerObjectSize() { return _playerIds.size(); }// 得到Player的Size

    // // 在世界中产生怪物.
    //BaseCharacter* SummonMonster( int nMapID, float fPosX, float fPosY, float fDirX, float fDirY, float fBodySize, int nMonsterId, int nMonsterNumber, float fRadius, int nSummonType, DWORD dwSpecialID = 0, int nInfluence = 0); // 召唤怪物   
    //BaseCharacter* CreateMonster( CMonsterProducer::TagMonsterData *pMonsterInfo, int nMapID, float nX, float nY, float fDirX, float fDirY, int iProductIndex, DWORD dwSpecialID = 0, int nInfluence = 0, BOOL bStartUpAI = FALSE );

    //// 召唤建筑怪
    //MonsterBuildEx*  CreateMonsterBuild( uint32 monsterId, uint32 mapId, float fx, float fy, float fdirx, float fdiry, uint8 campId );

    //// 召唤路径怪
    //MonsterRoute*  CreateMonsterRoute( uint32 monsterId, uint32 mapId, float fx, float fy, float fdirx, float fdiry, uint16 routeId, uint8 campId, bool bBornInRouteBegin, float xoff, float yoff );
    //
    //// 召唤保护怪
    //MonsterProtected* CreateMonsterProtected( uint32 monsterId, uint32 mapId, float fx, float fy, float fdirx, float fdiry, GameObjectId summonId );

    //// 召唤陷阱
    //MonsterTrap*   CreateMonsterTrap( uint32 monsterId, uint32 mapId, float fx, float fy, float fdirx, float fdiry, GameObjectId summonId );

    //// 在世界中产生召唤宠物 (即：临时存在的怪物，这种怪物的特点是： // 1、有生命周期 2、有父体 )
    //BaseCharacter* CreateSummonPet( CMonsterProducer::TagMonsterData *pMonsterInfo, int nMapID, float fx, float fy, float fdirx, float fdiry, int iProductIndex, GameObjectId shID = -1, int nInfluence  = 0, int nSummonSkillID = -1 );

    // 培育宠物
    //MonsterNurturePet* CreateNurturePet( CMonsterProducer::TagMonsterData *pMonsterInfo, int nMapID, float fx, float fy, float fdirx, float fdiry, int iProductIndex, GameObjectId iMasterID, SPetItem* pPetData );

    // 召唤分身
    //bool           CreateIllusion( CMonsterProducer::TagMonsterData pIllusionInfo, float fPosX, float fPosY, float fDirX, float fDirY, GameObjectId RealityID, GameObjectId& IllusionID ); //GameStage创建幻影分身    

    ItemCharacter* CreateItemNpc( const char *szItem, int nMapID, float fX, float fY, int nDir,  SCharItem &item, short stMasterNpc, unsigned char ucBornDelay, bool bTilePos = true );

    ItemCharacter* CreateItemPackageNpc( uint16 stItemID, unsigned long nMapID, float fX, float fY, int nDir, DropItemVector& vecDropItem, DropCharItemVector& vecCharItem, unsigned long dwTeamSeesionID, unsigned long dwPlayerID, SCharItem &item, unsigned char ucBornDelay);

    CEffectChar*   CreateEffectChar( BaseCharacter *pCharCaster,const char *szName ,int nMapID ,int iSkillID, int iSkillLevel, float nX, float nY);

    //bool           CreateNpcsHero( GameStage* pStage );
    //bool           CreateNpcHero( GameStage* pStage, NpcInfo::Npc* pNpcInfo, bool bConfigNpcInfoPointer, DWORD OnlineTime = -1);

    GameStage*     GetCharPosInWorld( BaseCharacter* pChar, DWORD& dwMapId, int& nX, int& nY, bool bCreate = false );

	bool           OnAddCharacter( GameObjectId dwID, const char* szFile, uint32 line );       // 加入角色
    bool           OnAddCharacterOnlyID(GameObjectId dwID);   // 专为刷怪而准备的加入角色，只把ID添加至Character列表，其他什么都不做
    bool           OnDelCharacter( GameObjectId dwID );       // 删除角色
    bool           OnDelCharacterOnlyID(GameObjectId dwID);   // 专为刷怪而准备的加入角色，只把ID从Character列表，其他什么都不做
    //bool         OnDelNpc( DWORD dwID );					 // 专为删除脚本NPC 

    bool           OnRefreshNewArea( GameObjectId dwID );    // 刷新当前所在区块
    bool           OnLeaveStage    ( GameObjectId dwID );    // 角色离开场景
    bool           OnEnterStage    ( GameObjectId dwID );    // 角色进入场景
    int            OnRefreshPlayerCharNumberInView( GameObjectId dwID ); // 刷新玩家当前能看到的玩家数(即：在9宫格内的玩家)

	//void           DebugShowCharListInfo(bool bRefreshNow); // 显示玩家信息
    
    bool           KickCharByAccount( DWORD dwAccount );	        // 根据账号id遍历所有角色踢下线,效率有点低
    void           MoveRoleToSafePosAndExit( BaseCharacter *pChar );// 让玩家移到安全点然后踢下线 
    void           ProcessGameStageOp();							// _gameStageOp这个容器有用么？数据都没有更新,就给center发送了一次
    //void           ProcGMCommand(const char* szCommand);			// GM工具相关的.不用，全交给center
    

    // 遍历得到Id
    GameObjectId GetNextObjectBId( bool bFirst );

    void DeleteGameStage( int nMapID );

    // 角色服务器专用
    void SetExtendrnMapOpen( bool bValue );
    const CountryConfig::BornMapSetting* GetPlayerBornMap( int nCountry );

protected:
    //static void RefreshMonster(void* p = NULL);     // 创建新得怪物
    static void LoadMapThread( void *pLoadMapInfo );  // 动态创建场景的线程

	GameStage*  CreateStage( uint32 dwMapId, uint32 dwEctypeId, uint16 ustLevel = 0, uint32 dwReserveValue = 0 );
	GameStage* 	CreateNormalStage( MapConfig::MapData* pMapData, uint32 dwEctypeId );
	GameStage* 	CreateEctypeStage( MapConfig::MapData* pMapData, uint32 dwEctypeId, uint16 ustLevel = 0, uint32 dwReserveValue = 0 );
	GameStage*  AsynCreateStage( uint32 dwMapId, uint32 dwEctypeId, uint16 ustLevel = 0, uint32 dwReserveValue = 0 ,GS2CSCreateMulitStageAck* pMsg = NULL);
	GameStage* 	AsynCreateEctypeStage( MapConfig::MapData* pMapData, uint32 dwEctypeId, uint16 ustLevel = 0, uint32 dwReserveValue = 0 /*,GS2CSCreateMulitStageAck* pMsg = NULL*/);

    void        MapMonitorRender();
    bool        OnFlashMoveTo( GameObjectId dwID, DWORD dwMapID, short nTileX, short nTileY, float fDir );
    bool        AddGameStage( GameStage* pStage );
    
    bool        CheckStageLoad();
    void        InitEctypeMapId( unsigned long uEctypeMapDataId );
    void        TryLoadAllScript();

    
	bool       CheckAsynStageInfo();
	void       CleanAsynStageInfo(SSynStageInfo* pSyn);
public:
    bool  m_guildsorted;
    DWORD g_dwLastWorldProcessTime;

    static bool bShowRunProcessInfo;
    static bool bShowMemoryInfo;
	static bool bCloseGate;

private:
    typedef std::map<uint32,GameStage*>  GameStageContainer;
    typedef GameStageContainer::iterator ItrGameStageContainer;

    typedef std::vector< SLoadMapInfo > CreateMapVector;
    typedef CreateMapVector::iterator CreateMapVectorIter;

	typedef std::vector< SSynStageInfo* > SSynStageInfoVector;
	typedef SSynStageInfoVector::iterator SSynStageInfoVectorIter;

    GameStageContainer  m_mapGameStage;          // 活动场景表
    CreateMapVector     m_vecCreateMapInfo;		 // 最近10分钟内创建的动态场景
	SSynStageInfoVector m_vecSSynStageInfo;		 // 多线程创建需要同步的信息

    GameObjectIDSet     _objectIds  ; // player Npc Monster Item 等
    GameObjectIDSet     _playerIds  ; // player 
    GameObjectIDSetItr  _objectIdItr; // 光标

    int                 m_NowSaveCharaStage;     // 现在需要保存的，地图
    int                 m_NowSaveCharStageIndex; // 现在需要保存，的npc编号
    DWORD               m_PreSaveTime;           // 上次保存的时间
    DWORD               m_dwCpuHz;               // 记录CPU频率
    SSafePos            m_safepos;

    // 缓存 CenterServer 挂掉或者还没有连上CenterServer时候 GameServer有新副本的操作
    typedef std::vector<SGameStageOp> GameStageOpContainer;
    typedef GameStageOpContainer::iterator ItrGameStageOpContainer;
    GameStageOpContainer _gameStageOp;

    typedef std::map< unsigned short, unsigned long > MapIdMakeContainer;
    typedef MapIdMakeContainer::iterator              ItrMapIdMakeContainer;
    MapIdMakeContainer _MapIdMake;
    GameTimerEx _reloadScriptTimeRecord;  // 重载脚本时间记录

    // 是否打开额外的新手出生点
    bool m_bExtendBornMapOpen;

    // 记录各重生点的出生的人数信息
    typedef std::map< unsigned int, unsigned int > CountryBornMap;
    typedef CountryBornMap::iterator CountryBornMapIter;

    CountryBornMap m_mapCountryBorn;
};

GameWorld& GettheWorld();

#endif // __GAMESERVER_GAMEWORLD_H__
