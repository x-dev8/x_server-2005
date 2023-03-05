/********************************************************************
    Filename:     GamePlayer.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_GAMEPLAYER_H__
#define __GAMESERVER_GAMEPLAYER_H__

#pragma once

#include "BaseCharacter.h"
#include "ScriptVM.h"
#include "GraphicCodeCheck.h"
#include "Dxsdk/d3dx9math.h"
#include "ItemBag.h"
#include "Bag/SkillBag.h"
#include "Bag/ActionBag.h"
#include "Bag/StoreTradeBag.h"
#include "Bag/HotkeyBag.h"
#include "Bag/MouseBag.h"
#include "Bag/ProduceItemBag.h"
#include "ItemDetail.h"
#include "ScriptKeyWord.h"
#include "ScriptFunctionDefine.h"
#include "SuitManager.h"
#include "ShopMgr.h"
#include "StorageMgr.h"
#include "Enmity.h"
#include "RestoreColdDown.h"
#include "Mutex.h"
#include "FileDB.h"
#include "NpcBaseEx.h"
#include "YuanBaoHandle.h"
#include "RestoreColdDown.h"
#include "TitleServerManager.h"
#include "TitleConfig.h"
#include "Trigger.h"
#include "RecipeConfig.h"
#include "ActionWatchManager.h"
#include "BuyBackPack.h"
#include "MailManagerPlayer.h"
#include "GuideQuestConfig.h"
#include "GameDefinePlayer.h"
#include "RelationManager.h"
#include "CountryManager.h"
#include "GuildManager.h"
#include "StarLevelUpConfig.h"
#include "RunningScriptControl.h"
#include "StallManager.h"
#include "Configure.h"
#include "AchieveServerManager.h"
#include "BargainingManager.h"
#include "PasswordDefine.h"
#include "XinFaManager.h"
#include "PetManager.h"
#include "StallConfig.h"
#include "FamilyManager.h"
#include "GameFamily.h"
#include "TPHJManger.h"
#include "SevenDayManager.h"
#ifdef NPGUARD
#include "CSAuth.h"
#endif
#pragma warning(disable:4244)
#pragma warning(disable:4018)
#pragma warning(disable:4101)

#define HINTMESSAGESENDRATE 10000 //提示消息的发送频率m

// 定义新手Tip保存的变量的高位和低位Byte
#define TIPVARHIGH 6
#define TIPVARLOW 7

class PKCopyScene;
class CodeData;
class LuckReward;
class MonsterBaseEx;
class GamePlayer : public BaseCharacter, public DPlayerChar,public BuffEvent,
                   public TPlayerEnmity<EnmitySize>, 
                   INHERIT_POOL_PARAM( GamePlayer,50 )
                   /*,public RunningScriptControl*/
{
//////////////////////////////////////////////////////////////////////////
public: // 结构体

    enum EGMPermission
    {   
        GP_FLYTOMAP       = 1<<0, // 飞地图
        GP_BECKONPLAYER   = 1<<1, // 拉人
        GP_FLYTOPLAYER    = 1<<2,
        GP_KILLTARGET     = 1<<3,
        GP_SUNMMONMONSTER = 1<<4,
        GP_BULL           = 1<<5,
        GP_SHOWPOS        = 1<<6,

        GP_SETADDEXP      = 1<<7,
        GP_NPCLIST        = 1<<8,
        GP_CREATEGUILD    = 1<<9,
        GP_LEARNSKILL     = 1<<10,
        GP_ADDITEM        = 1<<11,

        GP_IAMGOD         = 1<<12,
        GP_SETMONEY       = 1<<13,
        GP_ADDEXP         = 1<<14,
        GP_CAPTURE        = 1<<15,
        GP_ADDSKILLEXP    = 1<<16,

        GP_GETYUANBAO     = 1<<17,
        GP_UPDATEYUANBAO  = 1<<18,  
        GP_KICKCHAR       = 1<<19, // 踢人

        GP_ADDMONSTER     = 1<<20,
        GP_ONDEATH        = 1<<21,

        GP_PERPETUAL      = 1<<22,
        GP_DETROY         = 1<<23,

        GP_LOW     = GP_FLYTOMAP + GP_BECKONPLAYER + GP_FLYTOPLAYER + GP_KILLTARGET + GP_BULL + GP_SHOWPOS,
        GP_MEDIUN  = GP_LOW + GP_SETADDEXP +  GP_NPCLIST + GP_CREATEGUILD + GP_LEARNSKILL + GP_ADDITEM,
        GP_HIGH    = GP_MEDIUN + GP_IAMGOD + GP_SETMONEY + GP_ADDEXP + GP_CAPTURE + GP_ADDSKILLEXP,
        GP_HIGHEST = GP_HIGH + GP_GETYUANBAO + GP_UPDATEYUANBAO,

        GP_ROOT           = 0x7fffffff,
    };

    enum EConstDefine
    {
        // 系统公告类型
        SystemServer = 0,
        SystemWorld,
        SystemSingle,

        // 进入场景类型
        EnterStage = 1,     // 进入场景
        LeaveStage = 2,     // 离开场景, 进入到新的场景

        PlayerChangeStage = 0,  // 个人跳转
        TeamChangeStage   = 1,  // 队伍跳转
        GuildChangeStage  = 2,  // 帮派跳转

        // 分段发消息类型
        SendQuestMessage= 1    ,  //任务先发
        SendGuildMessage,		//工会
		SendRelationMessage,    //好友
        SendOtherMessage,       //其他
        SendIdentifyMessage,   //图鉴信息
        SendFamilyMessage,     //家族
        SendMessageEnd,

		//所在的战场类型
		Battle_Non = 0,  //不在战场
		Battle_Team = 1,  //小队战场
		Battle_Camp = 2,  //阵营战场里面
    };

	enum EScriptStates
	{
		EScriptStates_Init = 0,
		EScriptStates_OnDead = 1,
	};

    struct SDBInfo
    {
        SDBInfo() 
        {
            memset( this, 0, sizeof( SDBInfo ) );
			pdwCharacterID.clear();
			pdwCharacterMapId.clear();
			ustCountryID.clear();
			pdwSlot.clear();
        }

        uint32 dwAccountID;
        uint32 dwCharacterID;
		std::vector<uint32> pdwCharacterID;
		std::vector<uint32> pdwCharacterMapId;
		std::vector<short> ustCountryID;
		std::vector<uint32> pdwSlot;
        //uint32 pdwCharacterID[More_iCharPerAccount];
        //uint32 pdwCharacterMapId[More_iCharPerAccount];
        //short  ustCountryID[More_iCharPerAccount];
    };

    struct SReliveInfo
    {
        SReliveInfo()
        {
            bFreeRelive  = false;
            bSendMessage = true;
            bFlyToMap    = true;
            bDeathExit   = false;
            nReliveHP    = 10;
            nReliveMP    = 10;
			byAddition	 = 0;
        }

        bool bFreeRelive;   // 是否免费复活
        bool bSendMessage;  // 是否发送消息给客户端
        bool bFlyToMap;     // 是否要飞行地图
        bool bDeathExit;    // 是否死亡退出

        int nReliveHP;      // 回复HP( 百分比 )
        int nReliveMP;      // 回复MP( 百分比 )

		BYTE byAddition;	//附加信息（加个buf等等）
    };

    typedef std::vector<unsigned short> ItemContainer;
    typedef ItemContainer::iterator     ItrItemContainer;

//////////////////////////////////////////////////////////////////////////
    struct UseItemInfo
    {
        UseItemInfo()
        {
            Clear();
        }
        unsigned char uchItemBagType;
        ItemBag* pItemBag;
        short stIndex;
        short stItemID;
        short stCount;
        __int64 nGuid;

        void Clear()
        {
            uchItemBagType = 0;
            pItemBag = NULL;
            stIndex = -1;
            stItemID = -1;
            stCount = 0;
            nGuid = 0;
        }

        bool IsValid() { return ( pItemBag != NULL && stIndex != -1 && stItemID != -1 && nGuid != 0 ); }
    };

    struct WaitChangeStage
    {
        WaitChangeStage() : uchType( 0 ), dwMapID( 0 ), dwCurrentMapID( 0 ) {}

        uint8 uchType;              // 类型
        DWORD dwCurrentMapID;       // 当前的Map
        DWORD dwMapID;              // 要到达的地图
        float fX;
        float fY;
        float fDir;
        GameTimerEx xTimer;         
    };

    struct SkillItemRelive
    {
        uint8 uchType;
        int nItemID;
        int nValue;
        GameTimerEx xTimer;
    };

public: // 方法
    DECLARE_POOL_FUNC( GamePlayer )

    GamePlayer();
    virtual ~GamePlayer();

    // 移动模块
#include "PlayerMoveActionModule.h"

public:
    // IBaseCharProperty
    virtual SCharFightAttr* GetCharFightAttr();
    virtual void            SetHPMax( uint32 hpMax );
    virtual uint32          GetHPMax()              ;
    virtual void            SetMPMax( uint32 hpMax );
    virtual uint32          GetMPMax()              ;
    virtual int             GetHP()                 ;
    virtual int             GetMP()                 ;
    virtual void            SetHP( int nHp )        ;
    virtual void            SetMP( int nMp )        ;
    virtual void            OperateHP( uint8 uchOperateType, int nValue );
    virtual void            OperateMP( uint8 uchOperateType, int nValue );

    virtual bool            HasHPMaxChange()        ;
    virtual bool            HasMPMaxChange()        ;

    virtual float           GetMoveSpeed()              
	{ 
		if (mBiaocheState&&m_BiaoCheSpeed > 0.0f)
		{//如果镖车状态则是镖车速度
			return m_BiaoCheSpeed;
		}
		return GetCharFightAttr()->moveSpeed.final; 
	}
    virtual void            SetMoveSpeed( float fMove ) { GetCharFightAttr()->moveSpeed.base = fMove; GetCharFightAttr()->moveSpeed.UpdateFinal(); }

    void  SetXP( int xp );      // 设置XP值
    int   GetXP() { return gCharInfoServer.baseinfo.liveinfo.nXp; } // 获得XP值

    virtual bool IsPlayer() { return true; }

    // 初始化玩家数据
    virtual void  Initialize();

    virtual void  ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue ); // 在处理消息前调用
    virtual void  Run( DWORD dwCostTime );                                           // 主动执行 主运行

    virtual void  EnterMySight( BaseCharacter* pWho );    
    virtual void  ExitMySight( BaseCharacter* pWho );
    virtual Msg*  FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize);
    virtual void  RefreshCharData( DWORD dwCostTime);                // 刷新人物数据[更新频率1秒一次]
    virtual short IsSkillCanUse(BaseCharacter *pDst, int skill_no, int skill_level);      // 是否可以使用技能
    virtual bool  CheckWalkPreconditionState();                      // 判断可否移动
    virtual bool  CheckUseSkillPreconditionState();                  // 判断NPC是否处在一个可以使用一个技能的状态

    virtual bool  OnScriptSkill( ItemDefine::SItemSkill* pItemSkill );
    virtual short ApplySkillCost( ItemDefine::SItemSkill *pSkill );  // 应用技能消耗
    virtual long  ApplyBufferStatus(int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue); // 应用buff
    virtual void  OnBuffStatusChanged( bool bSendMessage );
    virtual void  OnSitDownRestore( );   // 坐下的恢复速率
    virtual void  OnStandUpRestore( );   // 站起的恢复速率
    virtual void  IncreaseSingleSkillExp( int nSkillExp );
    virtual void  IncreaseTotalSkillExp( int& nSkillExp );    
    virtual void  OnEnterFightState(); // 进战斗状态
    virtual void  OnOutFightState();   // 出战斗状态

    virtual bool  TryPassivenessTriggerAttack();    // 尝试被动触发技能
    bool  TrySelfPassivenessTriggerAttack();        // 尝试触发自身被动技能
    bool  TryMountPassivenessTriggerAttack();       // 尝试触发坐骑被动技能

    
    // 判断能够攻击对方
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    // 判断是否能被攻击
    virtual bool CheckCanBeAttack();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    // 判断是否有武器
    bool IsHaveWeapon( int16 weapontype );  

    // 更新装备数据到玩家身上
    void UpdateAllEquipData(); 

    // 更新所有套装属性
    void UpdateAllSuitData();

    // 是否能装备某物品
    bool IsCanEquip( uint8 part, SCharItem* pItem, bool bCheck = false );

    // 装备某物品
    bool Equip( uint8 part, SCharItem& item, bool bJustSetItem );

    // 装备防具
    bool EquipArmour( uint8 part, SCharItem* pitem);

    // 装备物品
    bool EquipWeapon( uint8 part, SCharItem* pItem);

    // 卸下装备
    void UnEquip( uint8 part, uint16 stPackIndex );

	//卸下并且删除装备
	void UnEquipAndRemove( uint8 part);

    // 卸下身上所有的装备
    void RemoveAllEquip();                            

    // 获得某部位装备
    SCharItem* GetVisualEquipItem( uint8 stPart );       

    // 删除指点部位的装备和套装
    void DeleteVisualEquipItem   ( uint8 stPart ); 

    // 删除装备技能
    void RemoveEquipItemSkill    ( uint8 stPart );

    // 设置指定部位装备
    void SetEquip( uint8 part, const SCharItem& rItem ); 

    // 获得物品类型
    short GetWeaponType( char cWhichHand );

    // 判断是否有某装备
    bool IsHaveEquipItem( uint16 nItemId );      

    // 检查所有道具时间, 加锁属性
    void CheckAllItemOperate();

    // 检查道具时间, 加锁属性
    bool CheckItemOperate( SCharItem* pCharItem );

    // 设置装备耐久度 
    void  SubEquipHp( short index, float fDropHp, bool& bNeedUpdateEquipHp );   

    int  GetWeaponAttack( int nType );
    int  GetArmourDefend( int nType );

    // 获得法宝
    SCharItem* GetTalismanItem();
    void SetTalismanItem( SCharItem* pCharItem );
    void DeleteTalismanItem();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    // 玩家死亡
    virtual void OnDeath();

    // 玩家复活
    void ProcessRelive( uint8 uchReliveType, SReliveInfo& xReliveInfo );
    void ProcessReliveBySkill( SReliveInfo& xReliveInfo );
    void ProcessReliveToMap( DWORD dwMapId, float fX, float fY, float fDir, SReliveInfo& xReliveInfo ); 
    void ProcessDeathExitRelive();
    
    // 开启复活定时器
    SkillItemRelive& GetSkillItemRelive() { return m_xSkillItemRelive; }

    // 得到完美复活需要的银票数
    int GetReliveOriginAllHpMp() { return m_nReliveOriginAllHpMp; } 

     // 设置完美复活需要的银票数
    void SetReliveOriginAllHpMp(int nValue) { m_nReliveOriginAllHpMp = nValue; }

    // 玩家死亡惩罚
    void PunishWhenDeath( BaseCharacter* pAttacker );

    // 检查是否死亡赦免
    bool CheckDeathRemit();

    // 玩家死亡掉落物品
    void DropItemWhenDeath( BaseCharacter* pAttacker );

	// 玩家死亡掉经验和荣誉
	void DropExpHonourWhenDeath( BaseCharacter* pAttacker );

    // 玩家死亡掉装备持久
    void CalcEquipHpWhenDeath();

    // 玩家死亡掉落压镖物品
    void DropItemWhenDeadByGuildQuest();

    // 处理死亡后宠物逻辑
    void ProcessMountAndPetWhenDeath();

    // 获得重生点
    MapConfig::RelivePosition* GetRelivePosition( MapConfig::MapData* pMapData );
	const MapConfig::SpecRelivePosition* GetSpecRelivePosition( MapConfig::MapData* pMapData );
	short IsInBattle(MapConfig::MapData* pMapData);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // 更新变化装备后 人物的基本属性(攻击，防御等)
    // 更新装备的特殊属性
    void ApplyAttrTypeToChar( uint16 attrType, uint16 part, CustomValue value );

    void ApplyEquipRandAttributesToChar     ( SCharItem* pItem, uint16 part );
    void ApplyTalismanRandAttributesToChar  ( SCharItem* pItem, uint16 part );

    void ApplyRandAttributeToChar( uint16 stRandID,   uint16 part );				// 计算随机属性
	void ApplyRandAttributeToChar( uint16 stRandID,   uint16 part, uint8 nQuality );// 计算随机属性

    void ApplyGemsToChar( SCharItem *pItem, uint16 part );
    void ApplyGemAttributeToChar( unsigned short ustItemID, uint16 part );      // 计算宝石属性

    void ApplySuitEquipAttributesToChar( unsigned short ustItemID );            // 计算套装随机属性
    void ApplyStarActivationAttribute  ( SStarActivation::SEffect* pEffect  );  // 计算星激活属性
    void ApplyStampActivationAttribute ( SStampActivation::SEffect* pEffect );

    ///////////////////////////////////////////////////////////////////////////////////////////////
    
    // 坐骑    
    short  GetRideId(){ return m_nDromeId; }
    void   SetRideId( short sMountId ){ m_nDromeId = sMountId; }
	uint16 GetRideLevel(){ return m_nMountLevel;}
	void   SetRideLevel( uint16 nMountLevel){ m_nMountLevel = nMountLevel;}
    uint8  GetRidePos() { return m_nDromePos; }
    void   SetRidePos( uint8 pos ) { m_nDromePos = pos; }
    GameObjectId GetRideDriverId() { return m_nDriverId; }
    void   SetRideDriverId( GameObjectId nCharId ) { m_nDriverId = nCharId; }

    // 获得坐骑数量
    unsigned char GetMountCount() { return gCharInfoServer.baseinfo.liveinfo.ucMountCount; }
        
    // 设置坐骑数量
    void SetMountCount( int nValue ) { gCharInfoServer.baseinfo.liveinfo.ucMountCount = nValue; }

    // 判断是否能骑马
    bool IsCanRide();

    // 骑坐骑, nid == -1时候, 下坐骑
    bool DoRide( int nId );

	bool IsCanPet(void);
	//召唤副将
	bool DoPet(int nIndex);

    // 骑第一匹坐骑
    bool DoRideFristMount();

    // 给第一匹坐骑加主动技能
    bool AddSkillToFristMount( uint16 skillId, uint8 level );
    
    // 获得当前出战的坐骑
    short GetRidingMountIdInDb() { return gCharInfoServer.otherdata.stMountId; }

    // 删除坐骑
    bool RemoveMountByGuid( __int64 nGuild );
    bool RemoveMountByIndex( uint8 uchIndex );
	bool RemoveMountByid(unsigned short usMountId,bool _All);//根据坐骑ID删除坐骑
    
    // 添加坐骑
    __int64 AddMount( unsigned short usMountId ); // 返回坐骑guid
    int AddMount( const SMountItem& xMount );
	bool IsMountFull();

    // 设置骑马状态
    void SetActiveBeRiding( bool bBeRiding ) { _mountManager.SetActiveBeRiding( bBeRiding ); }

    // 获得出战的马的索引
    int GetActiveMountIndex() { return _mountManager.GetActiveMountIndex(); }

    // 获得坐骑
    SMountItem* GetMountByIndex( uint8 uchIndex ) { return _mountManager.GetMountByIndex( uchIndex ); }
    SMountItem* GetMountByGuid( __int64 n64Guid ) { return _mountManager.GetMountByGuid( n64Guid ); }

    // 获得出战坐骑
    SMountItem* GetActiveMount() { return _mountManager.GetActiveMount(); }

    // 下多人坐骑
    bool GotOffMultiMount();

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // 上大载体
    bool OnNpcShip();

    // 下大载体
    bool OffNpcShip();

    // 得到大载体的ObjectId
    void SetNpcShipId( GameObjectId npcId ){ m_nBigShipId = npcId; }

    // 得到大载体的ObjectId
    GameObjectId GetNpcShipId() { return m_nBigShipId; }
    
    //////////////////////////////////////////////////////////////////////////

    // 添加宠物
    int   AddPet( const SPetItem& xPet , uint8 source = EPetSource_Other );
    int64 AddPet( int monsterId, int quality, int sex, int generation = 0 , uint8 source = EPetSource_Other );

    bool  AddPetIdentify ( uint16 petType );
    SPetIdentify* GetPetIdentify( uint16  petType );
    ItemDefine::SItemSkill* GetPetTalentSkillByType ( uint16 petType ) ;

    // 删除宠物
    bool RemovePetByGuid( __int64 nGuild, int source = EDS_Discard  );
    bool RemovePetByIndex( uint8 uchIndex, int source = EDS_Discard );

    // 领取繁殖宠物
    void PetBreedAcquire();

    // 产生宠物
    bool PetBreedGenerate();

    // 广播繁殖消息
    void PetBreedBroadcast( int64 nOldGuid , int64 nNewGuid );

    //////////////////////////////////////////////////////////////////////////
    
    // 等级改变
    void ChangeLevel(int nNewLevel); // 改变等级

	/*
	*	Author 2012-9-11 zhuxincong
	*	DESC: 改变国籍
	*/

	void ChangeCountry (int& nCountryID);

    // 经验改变
    void ChangeExp( __int64 exp );

    // 处理添加经验
    void IncreaseExp( int iRewardExp, int nSkillExp, BaseCharacter* pKillTarget = NULL );  

    // 处理添加队伍经验
    void IncreaseTeamExp( BaseCharacter *pKillTarget );

    // 设置玩家经验
    void SetPlayerExp(int64 dwExp) { gCharInfoServer.baseinfo.liveinfo.dwExp = dwExp; }

    // 获得玩家经验
    int64 GetPlayerExp(){ return gCharInfoServer.baseinfo.liveinfo.dwExp; }

    // 设置玩家未使用的经验
    void SetPlayerExpUnUsed( int64 dwExpNotUsed ) { gCharInfoServer.baseinfo.liveinfo.dwExpNotUsed = dwExpNotUsed; }

    // 获得玩家未使用的经验
    int64 GetPlayerExpUnUsed() { return gCharInfoServer.baseinfo.liveinfo.dwExpNotUsed; }

    // 获得玩家的总经验, 包括使用的和未使用的经验
    int64 GetPlayerCurrentExp() { return GetPlayerExp() + GetPlayerExpUnUsed(); }

    // 添加经验
    int IncreasePlayerExp( int& dwExp); //增长经验的函数

    // 获得玩家离线的经验
    void GetOfflineHookExp( uint8 nHookLevel );

    // 离线挂机每分钟经验值
    int32 GetOfflineHookMinuteExp ( uint8 hookLevel );   

    // 处理杀怪增加经验
    void ProcessKillMonsterExp( BaseCharacter* pTarget, int iRewardExp, int iRewardSkillExp );

    // 增加道行
    void IncreaseDaoxing( int nDaoxing );


    // 经验变化率
    float GetExpChangePer() { return m_fChangeExpPer; }
    void  SetExpChangePer(float fValue) { m_fChangeExpPer = fValue; }
    float GetSkillExpChangePer() { return m_fChangeSkillExpPer; }
    void  SetSkillExpChangePer(float fValue) { m_fChangeSkillExpPer = fValue; }

    bool  IsOpenDoubleExp() { return m_bIsOpenDoubleExp; }

    bool  AddSysDoubleExpTime ( int nValue ) ;
    bool  AddItemDoubleExpTime( int nValue ) ;
    void  ClearDoubleExpStatus();

    void           SetSkillExp(uint32 dwSkillExp) { gCharInfoServer.baseinfo.liveinfo.dwSkillExp = dwSkillExp; }
    uint32         GetSkillExp() { return gCharInfoServer.baseinfo.liveinfo.dwSkillExp; }

    void           SetSkillExpUnUsed(uint32 dwSkillExpNotUsed) { gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed = dwSkillExpNotUsed; }
    uint32         GetSkillExpUnUsed() { return gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed; }

    void           SetSkillExpForSkillID( unsigned short ustSkillID ) { gCharInfoServer.baseinfo.liveinfo.ustSkillExpForSkillID = ustSkillID; } // 设置需要升级的技能
    unsigned short GetSkillExpForSkillID() { return gCharInfoServer.baseinfo.liveinfo.ustSkillExpForSkillID; } // 得到当前需要修炼的技能

    unsigned short GetSkillExpForSkillLevel(unsigned short ustSkillID);             // 得到技能的等级    

    void           SetSkillExpToSkill(uint32 dwSkillExp,unsigned short ustSkillID);
    uint32         GetSkillExpToSkill(unsigned short ustSkillID);                   // 得到指定技能的技能经验

    void           OperateSkillExp( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine );
    void           OperateRecipeSkillPoint( uint8 uchOperateType, uint16 skillId, uint32 nValue, char* szFunction, int nLine );

    // 技能模块
    #include "PlayerSkillModule.h"

    //////////////////////////////////////////////////////////////////////
    // BufferStatus
    short GetMeAddStatus        ( int i );
    short GetMeAddStatusLvl     ( int i );
    short GetDstAddStatus       ( int i );
    short GetDstAddStatusLvl    ( int i );
    float GetDstStatusRate      ( int i );
    float GetMeStatusRate       ( int i );
    int8  GetDstAddStatusTrigger( int i );
    int8  GetMeAddStatusTrigger ( int i );

    virtual void  ApplyBuffStatusToCharAttr();
    virtual SCharBaseAttr* GetCharBaseAttr(){ return &gCharInfoServer.baseinfo.baseProperty.baseAttr; }

    SBaseAttrType* GetBaseAttr( uint8 nWhich );
    SBaseAttrType* GetAddSubBaseAttr( uint8 nWhich );

    void ApplyBaseAttrToFightAttr( bool total, uint16 part, bool bAdd = true);

    void SetCharAllBaseAttributeBase( int16* atttrBaseArray, int nSize);
  
    bool IsNeedDropTaskItem( short stQuestId, short stTaskState,int nItemId );

    // Update
    void RunUpdateTime( uint32 dwCostTime );   // 更新一些时间限制功能

    // PK    
    void       SetDstPlayerId( int nId ){ m_nDstPlayerId = nId; }
    int        GetDstPlayerId(){ return m_nDstPlayerId; }
    void       GetBirthday( int *pYear, int *pMonth, int *pDay );

    void       KillCapturePet();
    bool       CreateProtectMonster( int monsterId, int varId, bool isCanRide = false);   // 创建保护对象 同时绑定一个基数变量
    //void       LostProtectChar();                               // 失去保护对象
	void       ResetLostProtectCharData();						// 失去保护对象时重置变量 
    void       KillProtectChar();                               // 杀死要保护的对象
    bool       HaveProtectChar() { return m_ProtectCharID>=0; } // 是否有保护对象
    GameObjectId GetProtectCharID(){ return m_ProtectCharID; } // 获得保护对象的ID
    int        GetProtectCharMonsterId();                       // 获得保护对象的怪物索引
    void       SetCurZoneID( int id ){ m_nCurZoneID = id; }
    int        GetCurZoneID(){ return m_nCurZoneID; }
//     bool       IsInPrivateShopZone();
//     void       SetInPrivateShopZone( bool bInPrivateShopZone );
    void       GuardExpError();                // 纠正经验异常         
    void       SendCharAttibuteToClient();    // 更新角色属性数值到客户端
    void       SendVisualEquipDataToClient(); // 更新角色的装备给客户端	

    int  GetNormalAttackSkillId(int nAttackHand);
    void UpdateNormalAttackSkillId();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // 添加普通背包数量
    void AddNormalBagNowSize( unsigned short ustNum );

    // 添加材料背包数量
    void AddMaterialBagNowSize( unsigned short usNum );

    // 获得普通背包数量
    unsigned char GetNormalBagSize() { return gCharInfoServer.baseinfo.liveinfo.ucNormalBagSize;  }

    // 获得材料背包数量
    unsigned char GetMaterialBagSize() { return gCharInfoServer.baseinfo.liveinfo.ucMaterialBagSize;}

    // 获得任务被告数量
    unsigned char GetTaskBagSize() { return ITEM_BAGTASK_MAX; }
    
    // 获得仓库开启格子数量
    unsigned char GetStorageItemGrid() { return gCharInfoServer.baseinfo.liveinfo.nStorageItemGrid; }
    unsigned char GetStorageMountGrid() { return gCharInfoServer.baseinfo.liveinfo.nStorageMountGrid; }

    // 添加仓库格子数量
    bool AddStorageItemGrid (unsigned char nValue);

    bool AddStorageMountGrid( unsigned char nValue );

    // 获得普通背包物品数据
    SCharItem* GetNormalBagPointerByIndex( int nIndex );

    // 获得材料背包物品数据
    SCharItem* GetMaterialBagPointerByIndex( int nIndex );

    // 获得任务背包物品数据
    SCharItem* GetTaskBagPointerByIndex( int nIndex );

    // 获得背包物品数据
    SCharItem* GetBagItemByGuid( int64 guid );

	//lyh++ 根据物品id获得该物品的GUID
    int64 GetItemGUIDByItemID(unsigned short ustItemId);

    // 删除背包物品数据
    bool  RemoveBagItemByGuid( int64 guid, int count );

    // 是否有某种道具
    int GetItemCount( unsigned short ustItemId );
    
    // 获得背包空格子数
    int GetNullItemCount( unsigned char ucItemBagType );
    
    // 添加一个物品
    short AddItem(int nItemId, short nCount, uint8 nItemSource = 0, bool bIsBound = true, int64* pGuid = NULL,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0, int sysType = 0, int typeID = -1 );
    short AddEquipItem(int nItemId, short nCount, uint8 nItemSource = 0, bool bIsBound = true, int64* pGuid = NULL, bool bStarRandom = false, int16 nStarLevel = 0 ,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0, int sysType = 0, int typeID = -1 );
    short AddItemToBag(SCharItem &item, unsigned short &nCount, uint8 nItemSource = 0, int sysType = 0, int typeID = -1);
	short AddItemToBagByIndex(SCharItem &item,int Index, unsigned short &nCount, uint8 nItemSource = 0);
	short AddEquipRandAttrItem(int nItemId, short nCount, uint8 nItemSource = 0, bool bIsBound = true, int64* pGuid = NULL, int nRandId1 = 0, int nRandId2 = 0, int nRandId3 = 0, int nRandId4 = 0, int nRandId5 = 0, int nRandId6 = 0, int nRandId7 = 0, int sysType = 0, int typeID = -1 );
	void  AddItemSystemChat(int sysType, int typeID, SCharItem &item);
	const char* GetDefaultCountryNameById( int Id );

    // 删除一个物品
    bool RemoveItem( unsigned short ustItemId, unsigned short ustCount );
    bool RemoveItem( uint8 uchBagType, uint8 uchIndex, int nCount, int64 n64Guid );

	void RemoveAllItem( uint8 uchBagType );															//移除指定背包中所有物品luo.qin 3.21
	int	 ReturnItemID( uint8 uchBagType ,unsigned short ustItemId );								//返回指定ID号的装备在相应背包中的位置luo.qin 3.22

	

    // 获得背包指针
    ItemBag* GetItemBagByItemType( uint16 ustItemType );
    ItemBag* GetItemBagByBagType( uint8 uchBagType );

    // 获得背包类型
    uint8 GetItemBagType( uint16 ustItemType );

    // 捡取包裹
    bool  PickPackageItem( int nItemPackageID );
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool RecalcHpMp        ( uint8 ucFullHpMp, uint8 ucSendMsg );
    bool RecalcBaseProperty( bool bInitBase, uint8 ucFullHpMp, uint8 ucSendMsg, uint8 ucWherefore ); // 计算人数基础属性 包括一级属性和二级属性

    bool IsInLoginStage() { return _bInLoginStage; }
	unsigned long GetLastEnterWorldTime(){ return m_dwLastEnterWorldReqTime;}

    void  SetGateID( short stGateID ){ m_stGateID = stGateID; }
    short GetGateID(){ return m_stGateID; }

    bool IsWantSwitchGameWaitSaveInfoOk(){ return _bWantSwitchGameWaitSaveInfoOk; }
    void SendClientSwitchGateInfo();

    // 数据库
    bool IsCanAutoSaveToDB();   // 判断能否自动保存

    void SaveCharacterToDB();	// 废弃了
    SCharDBInfo& GetCharInfo() { return gCharInfoServer; }

    // 运行时候数据
    void BuildRuntimeInfo( SRuntimeInfo& runtimeInfo );

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // 获得活力值
    unsigned short GetActivity() { return gCharInfoServer.baseinfo.liveinfo.activity; }
    unsigned short GetActivityMax() { return gCharInfoServer.baseinfo.liveinfo.activityMax; }
    void OperateActivity( uint8 uchOperateType, int value, bool bSendMessage = true  );

    // 获得精力值
    unsigned short GetVigor() { return gCharInfoServer.baseinfo.liveinfo.vigor;  }
    unsigned short GetVigorMax() { return gCharInfoServer.baseinfo.liveinfo.vigorMax;  }

    // 设置精力值
    void SetVigor( unsigned short ustValue ) { gCharInfoServer.baseinfo.liveinfo.vigor = ustValue; }

    // 获得生产技能点
    unsigned short GetRecipeSkillPoint( unsigned char recipeType );
    
    // 设置成产技能点
    unsigned short SetRecipeSkillPoint( unsigned char recipeType, unsigned short pointValue );
    
    // 获得职业
    short GetProfession() { return gCharInfoServer.baseinfo.aptotic.usProfession; }

    // 设置职业
    void SetProfession(unsigned short usPro) {  gCharInfoServer.baseinfo.aptotic.usProfession = usPro ; }

    // 获得性别
    unsigned char GetSex() { return gCharInfoServer.baseinfo.aptotic.ucSex; }

    // 获得头像
    unsigned char GetHeadPic() { return gCharInfoServer.baseinfo.aptotic.ucHeadPic; }

    // 获得脸型
    int GetFaceID() { return gCharInfoServer.visual.faceId; }

    // 获得发型
    int GetHairID() { return gCharInfoServer.visual.hairId; }

    // 获得玩家DBID
    DWORD GetDBCharacterID() { return m_dbinfo.dwCharacterID; }

    // 获得帐号ID
    DWORD GetAccountID(){ return m_dbinfo.dwAccountID; }

    // 设置帐号ID
    void SetAccountID( DWORD nAccountId ) { m_dbinfo.dwAccountID = nAccountId; }

    // 获得帐号
    const char* GetAccount() { return m_szLoginName; }

    // 设置帐号
    void SetAccount(const char *AccountName){ strncpy_s( m_szLoginName,sizeof( m_szLoginName ),AccountName,sizeof( m_szLoginName ) - 1); }

    // 获得登录IP
    const char* GetLoginIP() { return m_szLoginIP; }

    // 设置IP地址
    void SetIp( const std::string& ip){ _strIp = ip; }

    // 获得IP地址
    const char* GetIp(){ return _strIp.c_str();}

    // Session
    /*char**/__int64        GetSessionKey(){ return _SessionKey; }
    bool         SetSessionKey ( __int64 SessionKey/*const char* szSessionKey*/ );

    // Log
    void         CheckCheatLog( const char* szFormat, ... ); // 外挂LOG
    void         Log          ( const char* szFormat, ... ); // Log
	void         DebugLog     ( const char* szFormat, ... ); // Log
    void         ShoppingLog  ( const char* szFormat, ... ); // 商城购物日志


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    short GetPlayerAttrDataBaseTop10(int nType); //查询数据库排名表,返回排行第几, 没有查到 返回 -1

    void AddCharToFirstList(GameObjectId shCharID);
    void RemoveCharToFirstList(GameObjectId shCharID);    

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    int64   GetTimeVar( uint8 nVarId);
    void    SetTimeVar( uint8 nVarId, int64 n64Time );

    uint32  Get32TimeVar( uint8 nVarId);
    void    Set32TimeVar( uint8 nVarId, uint32 n32Time );
    
    // 设置上线时间
    void SetEnterTime() { gTransferRuntimeInfo.OnLineTime = HQ_TimeGetTime(); }

    // 获得上线时间
    uint32 GetEnterTime() { return gTransferRuntimeInfo.OnLineTime; }

    // 获得玩家在线时间
    uint32 GetOnLineTime();

	void    SetEnterRealTime() 
	{ _nEnterRealTime = TimeEx::GetCurrentTime().GetTime(); }

	__int64 GetEnterRealTime()
	{ return _nEnterRealTime; }

	// 返回在线的秒数
	uint32 GetOnlineRealTime();

    // 设置下线时间
    void SetOffline() { m_nOfflineTime = HQ_TimeGetTime(); }

    // 获得下线时间
    uint32 GetOfflineTime() { return m_nOfflineTime; }

    //距离上次登录过了一天
    bool IsLastLoginPassOneDay();
    void ProcessLoginHandle ();
    void ProcessLastLoginPassOneDay();

    //距离上次记录时间是否过了周日
    bool IsPassSunday( int64 nRecordTime );

    // 设置下线类型
    void SetOfflineType( unsigned char exitType ){ _exitType = exitType; }

    // 获得下线类型
    uint32 GetOfflineType(){ return _exitType; }

    // 记录当前脚本时间变量
    void RecordNowTimeVar( int nVarID );

    // 判断时间变量是否过了一天
    bool IsTimeVarPassOneDay( int nVarID );

    // 判断记数变量清0时间
    void ProcessCheckVarClearTime();

    // 处理时间变量清0
    void ProcessClearTimeVar();
	void FirstEnterWorldClearTimeVar();

	//判断军阶俸禄领取时间是否过了一天
	void ProessClearSalary();
    ////////////////////////////////////////////////////////////////////////////////////////////////////


    void        SetNewPlayerName( const int8* newName ){ strncpy_s( _newPlayerName, sizeof(_newPlayerName), newName, sizeof(_newPlayerName)-1); }
    const int8* GetNewPlayerName() { return _newPlayerName; } // 取得新的名字    

    // 数据库
    bool IsCanSaveToDB(); // 判断可否被保存
    bool IsSaveTime();

    // 聊天
    void ResetHignShoutCount( void ) { gCharInfoServer.baseinfo.liveinfo.nHighShoutCount = 0;}
    void AddCurrentHighShoutCount( int nValue ) { gCharInfoServer.baseinfo.liveinfo.nHighShoutCount += nValue; }
    int  GetCurrentHighShoutCount( void ) const { return gCharInfoServer.baseinfo.liveinfo.nHighShoutCount; }
    bool IsCanChat() { return m_bCanChat; }
    void SetCanChat(bool bCan) { m_bCanChat = bCan; }
    bool IsBanSpeak() { return m_nBanSpeakTime > 0; }
    unsigned int GetBanSpeakTime() { return m_nBanSpeakTime; }
    void SetBanSpeakTime( unsigned int dwTime, bool bSendToClient = false );

    bool IsCanHighShout();      // 是否能高喊


    ////////////////////////////////////////////////////////////////////////////////////////////////////////
   
    // 获得当前称号
    short GetCurrentTitle() { return m_xTitleEx.GetCurrentTitle(); }

    // 设置当前称号
    bool SetCurrentTitle(short stTitleID) { return m_xTitleEx.SetCurrentTitle(stTitleID); }

    // 是否拥有称号
    bool IsHaveTitle(short stTitleID) { return m_xTitleEx.IsHaveTitle(stTitleID); }

    // 初始化称号列表
    void InitPlayerTitleList();                 

    // 保存称号列表
    void SavePlayerTitleList();                
     // 添加称号
    bool AddTitle( short nTitleID );    

    // 删除称号
    bool RemoveTitle(short nTitleID, bool bSendMessage = true );    

    // 更新排行榜称号列表
    void UpdateTitleListByDataBaseTop10(bool bSendToClient = false);                        

    // 更新类型称号
    void UpdateTitleListByConditionType(short nConditionType, bool bSendToClient = false);  

    // 更新服务器记数
    void UpdatePlayerCounterByCount(short nConditionType, int nID);        

    // 是否拥有某类型称号
    bool IsHaveTypeTitle( unsigned char uchType ){ return m_xTitleEx.IsHaveTypeTitle( uchType ); }

    // 删除某类型所有称号
    void RemoveTypeTitle( unsigned char uchType );

    // 处理记数获得称号
    void UpdateTitleCounter();

    // 更新称号附加的属性
    bool UpdateBaseAttrByTitle(bool bSendToClient, unsigned short nCurrentTitleID, unsigned short nLastTitleID = TitleConfig::Init_ID, bool bRemoveLastAttr = true);

    // 更新所有称号附加的属性
    bool UpdateBaseAttrByAllTitle(bool bSendToClient = false);

    // 更新称号附加的战斗属性
    bool UpdateFightAttrByTitle(bool bSendToClient,ItemDefine::SItemStatus* pStatus, bool bIsAdd = true);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    // 清除所有运行时数据
    void ClearCharRunTimeData();
    
    void SetShop( CShopMgr::SShop* pShop ){ m_pstShop = pShop; }
    
    void CheckMissionAndInform(); // 检测任务状态，并通知客户端
    void AddMission(char *pVarName);
    void DelMission(char *pVarName);

    // 队伍
    DWORD GetTeamID() { return m_dwTeamSessionId; }
    void  SetTeamID(DWORD dwSessionId) { m_dwTeamSessionId = dwSessionId; }
    bool  HaveTeam() ;

    uint32 GetPetBreedID() { return  m_dwPetBreedId; }
    void   SetPetBreedID( uint32 ID ) { m_dwPetBreedId = ID; }

    void   SetBreedPetPrompt( bool bValue ) { m_bBreedPetPrompt = bValue; }

    unsigned long GetRecordSystemTime();
    bool IsExpired( int nVarId, int keyHour, int keyMinute, int minDuration );
    bool RecordTimeVar( int nVarId );

    virtual bool IsTeamMember(BaseCharacter *pChar);
    void TellTeamInfoChange( char positon );

    // 设置宠物(保护怪)同步信息
    void SetRunTimePetInfo( RunTimePetInfo& xPetInfo,MonsterBaseEx* pAiPet, int nSummonSkillID = -1, int nPetIndex = -1 );

    long ProcessSkillAboutPetModule( const ItemDefine::SItemSkill* pSkill, SAttackTarget* pTarget ); // 处理技能中宠物模块
    long ProcessAfterIllusionModule( const ItemDefine::SItemSkill* pSkill, SAttackTarget* pTarget ); // 处理技能中镜像模块

    bool IsInProtectLockTime() { return m_nProtectLockLeaveTime != 0; }

    // 使用的物品相关
    UseItemInfo& GetUseItemInfo() { return m_xUseItemInfo; }
    void SetUseItemInfo( UseItemInfo& xInfo ){ m_xUseItemInfo = xInfo; }
    bool CheckUseItemValid();
    void ShowTreasureBox();
    bool IsTreasureBoxItem( unsigned short ustItemID );

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // 进入幸运15关
    void EnterLuckReward();

    // 更新幸运15关信息
    void UpdateLuckReward( int nType );

    // 获得当前幸运15关第几关
    int GetLuckRewardLevel( bool bCheckType = false );

    // 获得幸运15关属性指针
    LuckReward* GetLuckReward( bool bIsTeam );

    // 显示幸运15关奖励
    void ShowReceiveLuckReward( LuckReward* pLuckReward, bool bIsTeam );

    // 通知客户端弹出界面开始
    void ShowRandLuckReward( LuckReward* pLuckReward, bool bIsTeam );  

    // 处理领奖逻辑
    void ProcessReceiveLuckReward( LuckReward* pLuckReward, bool bIsTeam, bool bReceive );

    // 处理幸运15关摇奖逻辑
    void RunLuckReward( LuckReward* pLuckReward, bool bIsTeam );

    // 是否在幸运15关活动中
    bool IsInLuckReward();         

    // 通知客户端开始摇奖
    void StartLuckReward( LuckReward* pLuckReward, bool bIsTeam ); 

    // 判断能否摇奖 
    bool IsCanLuckReward();         

    // 判断能否到下一关
    bool IsCanNextLuckLevel();     

    // 判断能否接任务
    bool IsCanAcceptQuest( unsigned char uchLevel );   

    // 判断是否能领取奖品
    bool IsCanReceiveReward(); 

    // 设置可以摇奖
    void SetCanLuckReward();

    // 设置幸运15关刷怪数量
    void SetLuckSummonCount( unsigned short ustCount );

    // 获得幸运15关刷怪数量
    unsigned short GetLuckSummonCount();
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    
    // 获得当天杀怪数量
    unsigned long GetRecordKillMonsterCount() { return gCharInfoServer.otherdata.dwRecordKillMonsterCount; }

    // 清除当天杀怪数量
    void ClearRecordKillMonsterCount() { gCharInfoServer.otherdata.dwRecordKillMonsterCount = 0; }

    // 累加当天杀怪数量
    void AddRecordKillMonsterCount( int nCount = 1 ) { gCharInfoServer.otherdata.dwRecordKillMonsterCount += nCount; }

    // 判断记录杀怪时间是否已经改变
    bool CheckRecordKillMonsterTime( unsigned short ustYear, unsigned char uchMonth, unsigned char uchDay );

    // 获得杀怪经验系数
    float GetKillMonsterModulus();       
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // 处理玩家被T下线
    void ProcessBeBlock( uint8 type, uint32 time );

    // 发送检测代码给客户端
    bool ProcessSendCheckCheatData( CodeData* pCodeData, unsigned char uchCodeType );

    // 检测到外挂,处理玩家外挂数据
    bool ProcessKickByCheckCheat( unsigned int dwErrorResult );        

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // 格式化聊天物品链接
    int FormatChatItemData( const MsgChat* pChatMsg, char* szData, int nLength );
    
    // 由物品品质获得物品名字
    static void ReplaceSpecifiedName( unsigned short ustLevel, Common::_tstring& tstrName );

    // 发送系统消息
    void ProcessSystem( const char* szCommand, uint8 uchType, const MsgChat* pMsgChat = NULL );
    void ProcessSystem( uint8 uchType, const char* szCommand, const char* szItemHyberMem, int nItemCount = 1 );
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    // 显示酒馆任务
    void ShowPubQuestDlg( int nNpcID, int nType, const char* szInfo );

    void ShowBattleSignUpDlg( int nNpcID, int nType, const char* szInfo );

    void TellGameStage( short stTotalStage, short stStage, uint32 dwTime );
    
    uint32 GetPreSaveTime() { return m_PreSaveTime; }
    void   SetPreSaveTimeNow() { m_PreSaveTime = HQ_TimeGetTime(); }

    void CheckRemoveSecondPassword();

    uint32 GetLastUpdateTime() { return m_dwLastUpdateTime; }
    void SetLastUpdateTime( uint32 dwValue ) { m_dwLastUpdateTime = dwValue; }

    void AddTeamBattleIntegral( int nIntegral, int nKillCount, int nDeathCount, bool bSendMessage = true );

    void ProcessGuideQuest( int nType );    // 处理引导任务逻辑

    // 获得人物当前地图
    MapConfig::MapData* GetMapData() const { return m_pMapData; }

    // 设置任务当前地图
    void SetMapData( MapConfig::MapData* pMapData ) { m_pMapData = pMapData; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // 获得当前金钱
    uint32 GetMoney() const { return gCharInfoServer.baseinfo.liveinfo.dwMoney; }

    // 获得角色能携带的最大金钱
    uint32 GetMaxMoney();     

    // 检查是否能给角色添加金钱
    bool CheckCanAddMoney( DWORD dwAddMoney );

    // 金钱操作
    void OperateMoney( uint8 uchOperateType, uint32 nValue, bool bSendMessage, char* szFunction, int nLine,int16 sourcetype );

    // 获得当前交子数量
    uint32 GetJiaoZi() const { return gCharInfoServer.baseinfo.liveinfo.jiaoZi; }

    // 获得交子 和 金钱总数
    uint32 GetJiaoZiMoney() const { return GetMoney() + GetJiaoZi(); }

    // 操作交子 绑银
    void OperateJiaoZi( uint8 uchOperateType, uint32 nValue, bool bSendMessage, char* szFunction, int nLine ,int16 sourcetype);

    // 获得角色能携带的最大交子
    uint32 GetMaxJiaoZi();    

    // 检查是否能给角色添加交子
    bool CheckCanAddJiaoZi( DWORD dwAddJiaoZi );

    // 获得金锭
    uint32 GetJinDing() const { return gCharInfoServer.baseinfo.liveinfo.jinDing; }

    // 金锭操作 元宝
    void OperateJinDing( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype,bool bSyncToDB = true); 

	//获得商城积分
	uint32 GetConsumeScore() const {return gCharInfoServer.baseinfo.liveinfo.ConsumeScore ;}

	//商城积分操作 商城积分
	 void OperateConsumeScore( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype,bool bSyncToDB = true); 

    // 获得金票数量
    uint32 GetJinPiao() const { return gCharInfoServer.baseinfo.liveinfo.jinPiao; }

    // 金票操作 绑金
    void OperateJinPiao( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine ,int16 sourcetype); 
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    // 复活次数
    uint32 GetRecordReliveTime(){ return gCharInfoServer.baseinfo.liveinfo.nRecordReliveTime; }
    uint8  GetReliveCount() { return gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount;  }
    bool   IsCanFreeRelive();
    
    // 成就
    uint32 GetAchievePoint() { return gCharInfoServer.achieveData.achievePoint; }
    void   AddAchievePoint( uint32 nPoint ) { gCharInfoServer.achieveData.achievePoint += nPoint; }

    // 道行
    uint32 GetDaoxing()  { return gCharInfoServer.baseinfo.liveinfo.daoxing;  }
    void   OperateDaoxing( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine );

    // 荣誉 
    uint32 GetHonour() const    { return gCharInfoServer.baseinfo.liveinfo.honour;  }
    uint32 GetHonourRecord()    { return gCharInfoServer.otherdata.nRecordHonourCount; }
    uint32 GetHonourRecordTime(){ return gCharInfoServer.otherdata.nRecordHonourTime;  }
    void   ClearHonourRecord()  { gCharInfoServer.otherdata.nRecordHonourCount = 0; }
    void OperateHonour( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype );

    // 功勋
    uint32 GetExploit() const { return gCharInfoServer.baseinfo.liveinfo.exploit; }
    void OperateExploit( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype );

    // 声望
    uint32 GetReputation() const { return gCharInfoServer.baseinfo.liveinfo.reputation; }
    void OperateReputation( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine ,int16 sourcetype );

    // 副本积分
    uint32 GetEctypeScore(){ return gCharInfoServer.baseinfo.liveinfo.battleScore; }
    void OperateEctypeScore( uint8 uchOperateType, uint32 nValue );

    // 国战积分
    uint32 GetCountryScore() { return gCharInfoServer.baseinfo.liveinfo.dwCountryScore; }
    void OperateCountryScore( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine );
    void OperateTeamCountryScore( uint8 uchOperateType, uint32 nValue );

    // 比武决斗保护时间
    void  SetProtectTime( DWORD dwValue ) { dwProtectTime = dwValue;}        
    DWORD GetProtectTime() const { return dwProtectTime; }

    void SetClearDuelFight (bool bValue) { m_bIsClearDuelFight = bValue; }
    bool GetClearDuelFight () { return m_bIsClearDuelFight; }

    void SetDuelFightLoser( GameObjectId nID) { m_nDuelFightLoser = nID; }
    GameObjectId GetDuelFightLoser() { return m_nDuelFightLoser; }

	//获得国家ID
	int GetCountryId()
	{
		return gCharInfoServer.baseinfo.aptotic.ucCountry;
	}
	void SetCountryId( int uchCountry )
	{
		gCharInfoServer.baseinfo.aptotic.ucCountry = uchCountry;
		if ( gCharInfoServer.baseinfo.aptotic.ucCountry < 0 || gCharInfoServer.baseinfo.aptotic.ucCountry > 3)
		{
			gCharInfoServer.baseinfo.aptotic.ucCountry = 0;
		}
		TellClientCountryID();
		HandlePlayerCountryBuff();//当国籍发送变化的时候 处理国家BUFF
	}
	
	void TellClientCountryID();

	//太平幻境等级
	char GetTPHJRank()
	{
		return gCharInfoServer.baseinfo.liveinfo.TPHJRank;
	}
	void SetTPHJRank(char value,int operType=EOT_Set)
	{
		switch (operType)
		{
		case EOT_Set:			//直接赋值
			gCharInfoServer.baseinfo.liveinfo.TPHJRank = value;
			break;
		case EOT_Add:			//+
			gCharInfoServer.baseinfo.liveinfo.TPHJRank = gCharInfoServer.baseinfo.liveinfo.TPHJRank+value;
			break;
		case EOT_Sub:			//-
			gCharInfoServer.baseinfo.liveinfo.TPHJRank = gCharInfoServer.baseinfo.liveinfo.TPHJRank-value;
			break;
		case EOT_Mul:			//*
			gCharInfoServer.baseinfo.liveinfo.TPHJRank = gCharInfoServer.baseinfo.liveinfo.TPHJRank*value;
			break;
		case EOT_Div:			// /
			if (value!=0)
			{
				gCharInfoServer.baseinfo.liveinfo.TPHJRank = gCharInfoServer.baseinfo.liveinfo.TPHJRank/value;
			}
			break;
		}
		if (gCharInfoServer.baseinfo.liveinfo.TPHJRank<0)
		{
			gCharInfoServer.baseinfo.liveinfo.TPHJRank = 0;
		}
		TellClientTPHJRank();
	}
	void TellClientTPHJRank();
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // 请求切换到某个地图
    bool FlyToMapReq(DWORD iMapID, float x, float y, float dir, bool bCheckCanFly = true );   
	void ReviceByFlyToMap();

	void CheckIsNeedLeaveTeam();
private:
    // 切换到某个地图的实际逻辑
    bool FlyToMapAction( DWORD iMapID, int nTileX, int nTileY, float dir );

	// 切换到地图的实际逻辑
    bool ChangeToMap( GameStage* pGameStage, int nTileX, int nTileY, float dir, const char* szFile, uint32 line );

	// 切换到副本地图的实际逻辑
    bool FlyToEctypeMapAction( DWORD iMapID, int nTileX, int nTileY, float dir );

	bool IsCanFlyToMapAction(DWORD iMapID, int nTileX, int nTileY, float dir,DWORD& dwMapDataId,unsigned short& ustLevel,uint32& dwEctypeMapID,DWORD& dwReserveValue);

	void SetClientShowMapTimeStep(bool IsOpen,uint32 TimeStep);

	void StartChangeServerTimer(uint32 TimeStep);
public:
    // 处理切换到地图前的清理资源逻辑
    void ProcessChangeToMap();

    // 设置队伍切换场景
    void SetChangeStageType( uint8 nValue ) { m_nChangeStageType = nValue; }

    // 设置等待切换地图
    void SetWaitChangeStage( uint8 uchType, uint32 nMapID, float fX, float fY, float fDir, uint32 nSpaceTime, bool bSendMessage );
    
    // 处理等待切换地图逻辑
    void ProcessWaitChangeStage();

    // 处理切换地图后, 资源准备逻辑
    void ProcessChangeMap( bool lastEnterState );

    // 处理切换地图后 通知客户端消息
    void ProcessChangeMapMsg( bool bFirstEnterGameServer );

    // 处理切换地图阵营信息变化
    void ProcessChangeMapFightCamp(bool bFirstEnterGameServer);
	void ProcessChangeMapFightGame(bool bFirstEnterGameServer);

    // 第一次进入游戏世界
    void FirstEnterGameWorld( char* szMacAddress );

    // 第一次进入游戏服务器
    void FirstEnterGameServer( char* szMacAddress );

    // 离开游戏服务器
    void PlayerExitGameServer( unsigned char exitType );

    // 玩家进入地图
    void ProcessMapLoaded( bool bFirstEnterGameServer );

    void ProcessSummonObjectEnterGameServer();

    // 宠物切换地图
    void ProcessSummonObjectChangeMap( GameObjectId objectId );

    // 进入游戏检查并纠正玩家地图信息
    void CheckEnterWorldMapID( DBMsgAckEnterWorld* pEnterWord, DWORD& dwMapID, int& nMapX, int& nMapY );

    // 飞到某玩家身边
    bool FlyToPlayer( int nType );

    // 进入场景
    void OnEnterStage();

    // 离开场景
    void OnLeaveStage();

    // 是否队伍切换地图
    uint8 GetChangeStageType() const { return m_nChangeStageType; }

    // 判断人物等级是否小于地图等级
    bool IsLessThenMapLevel( uint32 nMapID );

    // 判断是否能从地狱里出来
    bool CheckPunishHell( uint32 nMapID );

	bool CheckFlyToJianYu(uint32 nMapID);

    // 判断是否在出生点地图
    bool IsInBornMap();
    
    // 下线纠正地图ID
    void CorrectMapID(); 

    // 计算副本地图等级
    unsigned short GetPlayerEctypeMapLevel( uint32 nMapID, float fX, float fY, uint8 nMapType );
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
    friend class CFileDB;

    virtual void _OnHPChanged( float underPercent ); // HP改变时触发调用
    virtual void _OnMPChanged( float underPercent ); // MP改变时触发调用

    void InitCharacter( const SCharDBInfo& dbSaveInfo, const SRuntimeInfo& dbRunInfo  ); // 初始化人物数据
    void UpdateCommonData( unsigned char bForSaveDb ); // 更新数值 bDeriveToCommon true数据派生类到基类变量 false基类变量到派生类

    void SendTipVar();   // 提示泡泡
    void SendRealTime(); // 服务器时间
  
    void SetAttackLockCharState( bool bAttack ) { m_bAttackLockChar = bAttack ; } // 是否开始攻击锁定的目标

    void OnMsgReqSkillIdToClient(unsigned short ustSkillID);

    //void TryAttackLockChar();                   // 攻击锁定目标
    long TryNormalAttack();                     // 打斗
    void _ProcessSwitchGameServerRuntimeInfo(); // 处理切服务器时候所有运行时数据

    void _RefreshEnergyAbout( DWORD dwCostTime ); // 刷新活力值
    void _RefreshVigorAbout ( DWORD dwCostTime ); // 刷新精力值

    // 道具
    bool ResetItemTime( SCharItem *pItem );
    int CalcGuildQuestReleaseRewardModulus( int nQuestID );

    long DistanceNowTime( unsigned char year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute );

    //动作
    void    SetCurActionId( uint16 nActionId ) { m_nCurActionId = nActionId ; }
    uint16  GetCurActionId() { return m_nCurActionId; }

    void    SetCurActionPlayTime( uint32 nPlayTime ) { m_nCurActionPlayTime = nPlayTime + HQ_TimeGetTime() ; }
    uint32  GetCurActionPlayTime() 
    { 
        if ( m_nCurActionPlayTime > HQ_TimeGetTime() )
        { 
            return  m_nCurActionPlayTime - HQ_TimeGetTime(); 
        }

        return 0; 
    }

    void    SetFlyMoving( bool bFly ) { m_bIsFlyMoving = bFly; }
    bool    IsFlyMoving() { return m_bIsFlyMoving; }

    // 是否在精力挂机
    bool IsBeginVigorOfflineFight();

    // 是否可以精力挂机
    bool IsCanVigorOfflineFight();

    // 当前事件
    uint16	GetCurEventID() { return m_nCurEventID; }
    void	SetCurEventID( uint16 nValue ) { m_nCurEventID = nValue; }

	// 获得家族指针
	GameFamily* GetFamily();

protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // 使用药品
    bool UseRestoreItem( ItemDefine::SItemRestore* pRestore, int bagIndex, BaseCharacter* target );

    // 更新背包药品数值
    void UpdateRestoreItemValue( ItemDefine::SItemRestore* pRestore, int bagIndex );
    
    // 获得指定目标是否能使用物品
    BaseCharacter* GetTargetCanUseGood(GameObjectId ustCharId,unsigned short ustTargetType,unsigned short ustItemID);

    // 对坐骑使用物品
    void _ProcessUseItemToMount( MsgUseGoodsToMount* pUseGoodsToMount, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );
    void _ProcessUseRestoreItemToMount( MsgUseGoodsToMount* pUseGoodsToMount, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );
    void _ProcessUseReelItemToMount   ( MsgUseGoodsToMount* pUseGoodsToMount, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );

    // 对宠物使用物品
    void _ProcessUseItemToPet( MsgUseGoodsToPet* pUseGoodsToPet, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );
    void _ProcessUseRestoreItemToPet( MsgUseGoodsToPet* pUseGoodsToPet, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );
    void _ProcessUseReelItemToPet( MsgUseGoodsToPet* pUseGoodsToPet, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemCommonConfig );

    // 对角色使用物品
    void _ProcessUseItemToChar( MsgUseGoods* pUseGoods, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig ); 
    void _ProcessUseRestoreItemToChar( MsgUseGoods* pUseGoods, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig ); 
    bool _ProcessUsePetIdentifyItemToChar( MsgUseGoods* pUseGoods, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );

    // 对好友使用物品
    void _ProcessUseItemToFriend( MsgUseGoods* pUseGoods, ItemBag* pItemBag, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig );
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void _ProcessRefreshProtectTime ( uint32 dwCurTime );

    void _ProcessRefreshProtectChar ( uint32 dwCurTime );

    void _ProcessRefreshRestore     ( uint32 dwCurTime );

    void _ProcessCurrentAction      ( uint32 dwCurTime );

    void _ProcessDoubleExpTime      ( uint32 dwCurTime );

    void _ProcessLongIntervalTimer  ( uint32 dwCurTime );
    
    //////////////////////////////////////////////////////////////////////////

    // 进入游戏服务器LOG
    void EnterGameServerLog( char* szMacAddress );

    // 离开游戏服务器LOG
    void ExitGameServerLog();

    // 玩家属性LOG
    void LogCharData( bool bExit = true );

    // 玩家进入背包物品LOG
    void LogForBagItem(int nBagType, SCharItem *pPackItem, int iBagSize,bool bIsDbCome = true);

    // 玩家退出游戏背包物品LOG
    void LogBagItemByExit(int nBagType, SCharItem *pPackItem, int iBagSize);

    // 玩家进入游戏身上装备LOG
    void LogForPlayerVisual(SCharItem* pVisualItem);

    // 玩家退出游戏身上装备LOG
    void LogForPlayerVisualByExit(SCharItem* pVisualItem);

    // 玩家其他数据LOG
    void LogOtherBagItem(SCharOtherData *pOtherData,bool bIsInWorld);

    // 具体物品LOG
    void LogItem(SCharItem* pCharItem,int nStringIndex);

    // 仓库LOG
    void LogStorage();

    // 坐骑LOG
    void LogMountData();

    // 清空特殊道具数量
    void ClearEspecialItemCounter() { _itemCounter.clear(); }

    // 添加指定道具数量
    void AddEspecialItemCounter( uint16 itemId, uint32 itemCount);

    // 指定道具LOG
    void LogEspecialItemCounter();

    // 设置开始分阶段发送消息
    void StartSendOnLineMessaage();

    // 处理上线分段发送消息
    void ProcessSendOnLineMessage( uint32 nCurrentTime );

    //////////////////////////////////////////////////////////////////////////////////
    // 登陆开始
    void StatusLoginStart();     

    // 会默认改变到这个数值等待客户端发送过来验证消息
    void StatusLoginCheck();   
    // 收到登录
    void StatusLoginLogin();    

    // 等待返回
    void StatusLoginWaitDBRet();

    // 将消息转发到数据库
    void StatusLoginLoginToDB(); 

    // 将消息转发到数据库
    void StatusLoginDBLoginED(); 

//////////////////////////////////////////////////////////////////////////
#include "PlayerMessageHandle.h"
#include "PlayerCommandModule.h"
#include "PlayerScriptModule.h"
#include "PlayerEnmityModule.h"
#include "CountryPlayerHandle.h"
#include "RelationPlayerHandle.h"
#include "GuildPlayerHandle.h"
#include "StallPlayerHandle.h"
#include "ConsignmentPlayerHandle.h"
#include "PlayerSpecialQuestModule.h"
#include "GamePlayerEquipEvolve.h"
#include "BargainingPlayerHandle.h"
#include "PasswordPlayerHandle.h"
#include "CampBattlePlayerHandle.h"
#include "PlayerBuffEvent.h"
#include "PlayerPKModule.h"
#include "PlayerSummonPetModule.h"
#include "PlayerQuestModule.h"
#include "FamilyPlayerHandle.h"
//xuda #include "WantedPlayerHandle.h"
#include "QuestEntrustPlayerHandle.h"
#include "GameBattlePlayerHandle.h"
#include "CSAuthPlayerMessageHandle.h"
//////////////////////////////////////////////////////////////////////////
// 防沉迷
#include "PlayerAntiAddictionModule.h"

public: // 变量
    SDBInfo                   m_dbinfo;
    SCharDBInfo               gCharInfoServer; 
    SRuntimeInfo              gTransferRuntimeInfo; // 中转过来的运行时数据
    ItemBag                   _NormalItemBag;       // 道具背包
    ItemBag                   _MaterialItemBag;     // 材料背包
    ItemBag                   _TaskItemBag;         // 任务背包
    SkillBag                  _SkillBag;            // 人物技能背包
	SkillBag				  _HeroSkillBag;		// 主将技能背包
    SCharStorageData          _StorageBag;          // 仓库背包
    XinFaManager              _XinFaManager;        // 心法管理
    SuitManager< GamePlayer > _suitManager;         // 套装管理
    MountManager              _mountManager;        // 坐骑管理
    PetManager                _petManager;          // 宠物管理
    AchieveServerManager      _achieveManager;      // 成就管理
    RecipeManager             _recipeManager;       // 处方管理
    GraphicCodeManager        _graphicCodeManager;  // 验证码
    ActionWatchManager        _actionManager;       // 行为监控管理
    MailPlayerManager         _mailManager;         // 玩家邮件管理
	SevenDayManager			  _sevenDayManager;		// 开服7天乐管理
	#ifdef NPGUARD
	CSAuthManager			  _authManager;
	#endif
    bool                      m_bStorageDBFlag;         // 仓库查询标志 仓库是否被打开过
    bool                      m_bInDuelReq;             // 是否在等待切磋回复
    clock_t                   m_tmChatCoolDownTime;     // 记录9宫格喊话的时间
    unsigned long             m_dwLastEnterWorldReqTime;// 最新的请求进入游戏世界的时间
    int                       m_nProtectLockLeaveTime;  // 保护锁保护剩余时间
    unsigned int              m_nBanSpeakTime;          // 禁言时间

    SCharBaseAttr             addSubBaseAttr;                                   // 记录基础属性增减
    SCharAttributeUpdate      lastFightAttr;                                    // 纪录上一次的战斗属性
    bool                      fightAttrChangeRecord[CharAttr_AttributMaxCount]; // 纪录上一次的战斗属!性变化情况

    float                     m_fChangeExpPer;      // 经验的变化率
    float                     m_fChangeSkillExpPer; // 技能经验的变化率
    bool                      m_bIsOpenDoubleExp;   // 是否打开了双倍经验

    // for debug
    bool bAlwayCritical; // 是否总是暴击
    bool bShowFightInfo; // 是否显示战斗信息

protected: // 变量
    __int64                _SessionKey;
    char                m_szLoginName[ dr_MaxNameString ];
    char                m_szLoginIP[ dr_MaxNameString ];
    GameObjectId       m_ProtectCharID;         // 要保护对象的ID
    int                 m_nProtectCharMonsterId; // 要保护对象的怪物表中的Id
    short               m_stMeAddStatus         [ EEquipPartType_MaxEquitPart ]; // 装备bufferStatus
    short               m_stMeAddStatusLvl      [ EEquipPartType_MaxEquitPart ];
    short               m_stDstAddStatus        [ EEquipPartType_MaxEquitPart ];
    short               m_stDstAddStatusLvl     [ EEquipPartType_MaxEquitPart ];
    float               m_fDstStatusRate        [ EEquipPartType_MaxEquitPart ];
    float               m_fMeStatusRate         [ EEquipPartType_MaxEquitPart ];  
    int8                m_nMeAddStatusTrigger   [ EEquipPartType_MaxEquitPart ];
    int8                m_nDstAddStatusTrigger  [ EEquipPartType_MaxEquitPart ];
    uint32              m_PreSaveTime;                  // 上次保存的时间,用在自动保存上面
    int                 m_nReliveOriginAllHpMp;         // 完美复活RMB
    bool                m_bIsStatusChangeHpMpMax;       // 是否为状态引发改变HP MP 最大值
    bool                m_bIsClearDuelFight;            // 是否清除决斗信息
    GameObjectId       m_nDuelFightLoser;             // 决斗获胜玩家ID

protected:
    // 地图场景变量
    bool                _bWantSwitchGameWaitSaveInfoOk; // 是否是在等待切服数据入库流程
    MsgSwitchGate       _GateInfo;                      // 切服保留的GateServer的信息
    short               m_stGateID;                     // 角色位于的GateID
    bool                _bFirstEnterGameServer;         // 是否是第一次进入这台GameServer
    bool                _bFirstEnterWorld;              // 是否第一次进入游戏世界
    std::string         _strIp;                         // 玩家ip
    bool                _bInLoginStage;                 // 是否在LoginStage中, 刚构建出来,默认都在

    int                 m_nCurZoneID;
    //bool                m_bInPrivateShopZone;   

protected:
    // 脚本相关
    VMScriptContainer   m_lsScript;
    unsigned long       m_dwScriptSleep;
    unsigned long       m_dwScriptSleepStartTime;
    int                 m_nTempVars[More_iMaxTempVars]; // 临时脚本数据
    int                 m_nScriptNpcId;                 // 请求的NpcObjectId

protected:
    // 时间相关
    unsigned int        m_nOfflineTime;
    unsigned char       _exitType;                      // 退出类型
    //unsigned int        m_nEnterTime;                   // 进入游戏时间
	__int64             _nEnterRealTime;                // 进入游戏的现实时间
    
    BOOL                m_bAttackLockChar;
    RestoreColdDown     m_RestoreColdDown;
    int                 m_nDstPlayerId;
    DWORD               m_dwLastDoRideTime;
    DWORD               m_dwLastHintMessageSendTime;    // 提示消息发送的最后时间
    DWORD               m_dwReqShopTime;
    unsigned long       _accumulateEneryTime;           // 活力更新的累计时间
    unsigned long       _accumulateVigorTime;           // 精力更新的累计时间
    CShopMgr::SShop*    m_pstShop;
    TitleEx             m_xTitleEx;                     // 称号
    DWORD               m_dwLastChatTime;
    MsgEnterWorld       _msgEnterWorldCache;
    UseItemInfo         m_xUseItemInfo;
    uint32              _blockTime;                     // 被踢block时间
    uint32              dwCharSaveDelay;
    DWORD               m_dwTeamSessionId;              // 组队的seesionid   0 表示没有
    uint32              m_dwLastUpdateTime;
    uint32              m_dwExpressionTime;             // 上一次发送表情的时间
    uint32              m_dwPetBreedId;                 // 宠物繁殖ID
    bool                m_bBreedPetPrompt;              // 宠物繁殖提示

    BuyBackPack< SCharItem >   m_xBuyBackItem;              // 需要回购的物品
    int8                       _newPlayerName[dr_MaxPlayerName];

    typedef std::map<uint16, uint32>       ItemCounterContainer;
    typedef ItemCounterContainer::iterator ItrItemCounterContainer;
    ItemCounterContainer                   _itemCounter;    //特殊道具集合,用于收集角色身上的某些物品的数量信息

    MapConfig::MapData* m_pMapData;
    //////////////////////////////////////////////////////////////////////////////
    DWORD           dwProtectTime;          // 保护不能被攻击时间
    uint32          m_dwCheckProtectTimePer;

    uint8           m_nChangeStageType;     // 是否队伍一起切换地图
    WaitChangeStage m_xWaitChangeStage;     // 等待切换地图
    GameTimerEx     m_xChangeServerTimer;   // 切换服务器Timer;

    ///////////////////////////////////////////////////////////////////////////////
    unsigned char m_uchSendOnLineMessageStatus;  // 第一次上线 消息分段发送阶段   
    GameTimerEx m_xSendOnLineMessageTimer;       // 第一次上线 消息分段发送定时器

    unsigned int m_nVarClearTime;                // 记录时间是否过了12点    
    GameTimerEx m_xVarClearTimer;                // 变量定时器

    SkillItemRelive m_xSkillItemRelive;          // 技能物品复活
    
    //  人物目前动作状态情况
    int     m_nDromeId          ;   // 坐骑ID
	uint16	m_nMountLevel		;	// 坐骑等级
    uint8   m_nDromePos         ;   // 座位
    GameObjectId  m_nDriverId   ;   // 驾驶员ID
    uint16  m_nCurActionId      ;   // 当前动作
    uint32  m_nCurActionPlayTime;   // 当前动作播放时间
    GameObjectId m_nBigShipId   ;   // 大载体的Id
    uint8   m_nNpcShipPos       ;   // 大载体的位置
    bool    m_bMoving           ;   // 在移动中
    bool    m_bIsFlyMoving      ;   // 是否飞行
    uint16	m_nCurEventID		;	// 需要广播的事件ID

    GameTimerEx _offlineFightTime;  //
	bool        _bGetWallowInfo; // 是否得到了防沉迷所需要的数据 从DB

	// 是否是变身镖车状态
	bool      mBiaocheState;
	float     m_BiaoCheSpeed;//镖车速度
	//总共可以获得的经验
	__int64		ulCanTakeExp;

public:
	///////////////////san guo add:///////////////////////////////
	void SetHeroId( uint16 hero_id)
	{
		gCharInfoServer.baseinfo.liveinfo.hero_id = hero_id;
	}
	void ClearHeroId()
	{
		gCharInfoServer.baseinfo.liveinfo.hero_id = INVALID_HERO_ID;
	}
	uint16 GetHeroId(){return gCharInfoServer.baseinfo.liveinfo.hero_id;}

	//太平幻境
	void SetMapID_TPHJ(DWORD map_id)
	{
		gCharInfoServer.otherdata.sBornPos.dwMapID = map_id;
	}
	void SetPrePosition_TPHJ(D3DXVECTOR3 pos)
	{
		gCharInfoServer.otherdata.sBornPos.vPos = pos;
	}

	bool IsBiaocheState() const { return mBiaocheState; }

	void RefreshHeroAttr();
	void RefreshHeroSkill();
	void RefreshMountAttr(bool IsInit = false);
	void RefreshLieutenantAttr(bool IsDoPet);//刷新副将对玩家的属性
	void GetHeroAddAttr(SCharHeroInfo* pHeroAddAttr);
	//bool ApplyHeroPassiveSkillEffect();

	void ApplyPetAttrToChar(ItemDefine::SItemSkill* pPetSkill,bool bCancelApply);

	//如果在太平幻境退出游戏
	void ProcessExitGameInTPHJ(DBMsgSaveCharacter& msg);

	__int64 GetCanTakeExp(){return ulCanTakeExp;}
	void CalcCanTakeExp();        //计算可以获得的最高经验
	void SendLevelLimitInfo();    //更新全部的封印数据给客户端
	void CheckToSendAddLimitPlayerCount();

	bool UnBindBagEquip(__int64 bagEquipGuid);
	//处理玩家的国家方面的处理
	void HandlePlayerCountryInfo();
	void HandleGuildSQ();
	void SetPlayerCountryPosition(uint8 Position);
	void SendProcessTimeToClient(int StringID,int TimeStep);
	void UpdateMountWrongData(SMountItem* mount);
	void SetPetDuration(int Value);
	int	 GetPetDuration();
	void OnUpdatePetExp();
	void SetPetMode(__int64 PetGuID,uint32 ModeID,int LastTime = -1);
	void AddCard(short stCardID, short stLevel);
	bool SetCardAchieve(int nachID);

	void TriggerSevenDays();
	int  AddFriendPoint(int Distance , int FriendlyPoint);
	void OnHandleScriptStates();
	void SetScriptStatesID(unsigned short Type =  EScriptStates_Init){m_ScriptStatesID = Type;}

	void ClearGetSalary();

	int GetTodayHuntingCount() { return gCharInfoServer.otherdata.sHunting.nCount; }
	void OperateHuntingCount( int nType, int nValue );
	void DoneHuntingQuest( int nQuestId );
private:
	int64		m_DeadPetID;
	DWORD		m_PetExpUpdateLog;
	unsigned char	m_ScriptStatesID;//当前脚本执行状态 无表示为0 当脚本结束的时候 自动还原为0 具体状态由脚本自动设置
	bool		m_IsCanDead;
	DWORD		m_LogTime;
	uint32		m_LogTeamID;

	bool		m_IsGameBattle;
public:
	void		OnRoleOnLineQuestEntrustHandle();
private:
	void		SendChangeEquipErrorInfo();
private:
	void		UpdataThreeDayInfo();

private:
	unsigned int m_YuanBaoTotle;
	unsigned int m_YuanBaoStates;
public:
	unsigned int GetYuanBaoStates(){return m_YuanBaoStates;}
	void SetYuanBaoStates(unsigned int Value){m_YuanBaoStates = Value;}

	unsigned int GetYuanBaoTotle(){return m_YuanBaoTotle;}
	void SetYuanBaoTotle(unsigned int Value){m_YuanBaoTotle = Value;}

	bool IsInBattleMap();

	bool ChangeMountStarLevel(__int64 MountOnlyID,unsigned int StarLevel,bool IsMoveLevel= false);

	void HandlePlayerCountryBuff();

	void SendLeaveExpInfo();
	void GetLeaveExp();
};

//////////////////////////////////////////////////////////////////////////
// inline
inline SBaseAttrType* GamePlayer::GetBaseAttr( uint8 nWhich)
{
    if (nWhich < 0||nWhich >EBaseAttr_MaxSize)
    { return NULL; }
    return &gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[nWhich];
}

inline SBaseAttrType* GamePlayer::GetAddSubBaseAttr( uint8 nWhich )
{
    if (nWhich < 0||nWhich >EBaseAttr_MaxSize)
    { return NULL; }
    return &addSubBaseAttr.baseAttrValue[nWhich];
}

inline void GamePlayer::SetCharAllBaseAttributeBase(int16* atttrBaseArray, int nSize)
{
    for( int i=0; i<nSize; ++i)
    { GetBaseAttr(i)->base = *(atttrBaseArray + i); }
}

inline SCharItem* GamePlayer::GetVisualEquipItem( uint8 stPart )
{
    if (stPart < 0 || stPart >= EEquipPartType_MaxEquitPart)
    { return NULL; }
    
    SCharItem* pCharItem = gCharInfoServer.visual.GetVisual(stPart);
    if ( NULL == pCharItem)
    { return NULL; }

    if ( pCharItem->itembaseinfo.ustItemID == InvalidLogicNumber || pCharItem->itembaseinfo.nOnlyInt == InvalidLogicNumber )
    { return NULL; }
    return pCharItem;
}

inline SCharItem*  GamePlayer::GetTalismanItem()
{
    SCharItem* pCharItem = &gCharInfoServer.visual.talisman;
    if ( NULL == pCharItem)
    { return NULL; }

    if ( pCharItem->itembaseinfo.ustItemID == InvalidLogicNumber || pCharItem->itembaseinfo.nOnlyInt == InvalidLogicNumber )
    { return NULL; }

    return pCharItem;
}

inline void GamePlayer::SetTalismanItem( SCharItem* pCharItem )
{
    if (pCharItem == NULL)
    { return ; }

    gCharInfoServer.visual.talisman = *pCharItem;
}

inline void GamePlayer::DeleteVisualEquipItem( uint8 stPart )
{
    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UnpackEquip, PasswordDefine::OP_InitAction ) )
    { return;}  // 财产保护下无法卸下装备，删除装备

	if(CS_INTONATE == GetStatus())
	{
		//吟唱状态无法切换装备
		SendChangeEquipErrorInfo();
		return;
	}

    if ( stPart >= EEquipPartType_MaxEquitPart)
    { return; }

    SCharItem* pCharItem = gCharInfoServer.visual.GetVisual(stPart);
    if ( NULL == pCharItem)
    { return; }

    pCharItem->itembaseinfo.ustItemID  = InvalidLogicNumber;
    pCharItem->itembaseinfo.nOnlyInt   = InvalidLogicNumber;
}

inline void GamePlayer::DeleteTalismanItem()
{
    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UnpackEquip, PasswordDefine::OP_InitAction ) )
    { return;}  // 财产保护下无法卸下装备

	if(CS_INTONATE == GetStatus())
	{
		//吟唱状态无法切换装备
		SendChangeEquipErrorInfo();
		return;
	}

    SCharItem* pCharItem = GetTalismanItem();
    if ( NULL == pCharItem)
    { return; }

    pCharItem->itembaseinfo.ustItemID  = InvalidLogicNumber;
    pCharItem->itembaseinfo.nOnlyInt   = InvalidLogicNumber;
}

inline short GamePlayer::GetMeAddStatus( int i )
{
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_stMeAddStatus[i];
    return -1;
}

inline short GamePlayer::GetMeAddStatusLvl( int i )
{
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_stMeAddStatusLvl[i];
    return -1;
}

inline short GamePlayer::GetDstAddStatus( int i )
{
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_stDstAddStatus[i];
    return -1;
}

inline short GamePlayer::GetDstAddStatusLvl( int i )
{
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_stDstAddStatusLvl[i];
    return -1;
}

inline float GamePlayer::GetDstStatusRate( int i )
{
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_fDstStatusRate[i];
    return 0.0f;
}

inline float GamePlayer::GetMeStatusRate( int i )
{    
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_fMeStatusRate[i];
    return 0.0f;
}

inline int8 GamePlayer::GetDstAddStatusTrigger( int i )
{    
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_nDstAddStatusTrigger[i];
    return 0;
}

inline int8 GamePlayer::GetMeAddStatusTrigger( int i )
{    
    if( i>= 0 && i < EEquipPartType_MaxEquitPart )
        return m_nMeAddStatusTrigger[i];
    return 0;
}

inline void GamePlayer::SetXP( int xp )
{ 
    gCharInfoServer.baseinfo.liveinfo.nXp = xp;
    if ( gCharInfoServer.baseinfo.liveinfo.nXp < 0 )
    { gCharInfoServer.baseinfo.liveinfo.nXp = 0; }

    if ( gCharInfoServer.baseinfo.liveinfo.nXp > DEF_CHAR_XP_LIMIT )
    { gCharInfoServer.baseinfo.liveinfo.nXp = DEF_CHAR_XP_LIMIT; }
}

inline SCharItem* GamePlayer::GetNormalBagPointerByIndex( int nIndex )
{
    if ( nIndex < 0 || nIndex >= ITEM_BAGMAX || nIndex >= GetNormalBagSize() )
        return NULL;

    return &gCharInfoServer.itemData.stPackItems[nIndex];
}

inline SCharItem* GamePlayer::GetMaterialBagPointerByIndex( int nIndex )
{
    if ( nIndex < 0 || nIndex >= ITEM_BAGMATERIAL_MAX || nIndex >= GetMaterialBagSize() )
        return NULL;

    return &gCharInfoServer.itemData.ciMaterialItems[nIndex];
}

inline SCharItem* GamePlayer::GetTaskBagPointerByIndex( int nIndex )
{
    if ( nIndex < 0 || nIndex >= ITEM_BAGTASK_MAX || nIndex >= GetTaskBagSize() )
        return NULL;

    return &gCharInfoServer.itemData.ciTaskItems[nIndex];
}

inline void GamePlayer::SetEquip( uint8 part, const SCharItem& rItem )
{        
    if( part >= EEquipPartType_MaxEquitPart )
    { return; }

	if(CS_INTONATE == GetStatus())
	{
		//吟唱状态无法切换装备
		SendChangeEquipErrorInfo();
		return;
	}
 
    SCharItem* pCharItem = gCharInfoServer.visual.GetVisual( part );
    if ( pCharItem == NULL )
    { return; }

    *pCharItem = rItem;
}

inline unsigned short GamePlayer::GetRecipeSkillPoint( unsigned char recipeType )
{   
    if ( recipeType >= ERT_MaxType )
    { return 0; }

    return gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ recipeType ];
}

inline unsigned short GamePlayer::SetRecipeSkillPoint( unsigned char recipeType, unsigned short pointValue)
{
    if ( recipeType >= ERT_MaxType )
    { return 0; }

    return gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ recipeType ] = pointValue;
}

inline bool GamePlayer::CheckUseItemValid()
{
    if ( !m_xUseItemInfo.IsValid() )
    { return false; }

    return true;
}

inline bool GamePlayer::SetSessionKey ( __int64 SessionKey )
{
    if ( 0 == SessionKey)
    { return false; }
	_SessionKey = SessionKey;
    //strncpy_s( _szSessionKey,sizeof(_szSessionKey),szSessionKey,sizeof(_szSessionKey)-1);
    return true;
}

#endif // __GAMESERVER_GAMEPLAYER_H__