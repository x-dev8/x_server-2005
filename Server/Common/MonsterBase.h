/********************************************************************
    Filename:     MonsterBase.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_AICHARACTER_H__
#define __GAMESERVER_AICHARACTER_H__

#include "BaseCharacter.h"
#include "FuncPerformanceLog.h"
#include "LuaPlus/LuaPlus.h"
#include "Dxsdk/d3dx9math.h"
#include "AiTaskManager.h"
#include "NetControl.h"
#include "SwMap.h"
#include "CharacterFindParth.h"

#define ENMITY_RATE           0.2f // 等级仇恨差比率
#define ENMITY_MIN_VIEWSIGHT  3    // 最小视野

#define AI_ARRAY_SIZE         10
#define AI_BOOLARRAY_SIZE     10
#define AI_MONSTERMAXSKILLNUM 3
#define AI_MAXTIMER           10

#define ProjectCharDis           10    // 10 提示
#define ProtectCharStopDistance  20   // 20 停止
#define TellClientDisPerTime     5000 // 5s 提示时间跟护送的角色距离

extern SProcessTime aiusetime[200];

enum EAISelectTaskType
{ // 当前Ai的处理策略
    EAISelectTaskType_None           ,
    EAISelectTaskType_IdleMove       , // 待机移动
    EAISelectTaskType_TryAttackTarget, // 尝试攻击目标
    EAISelectTaskType_TryUseSkill    , // 使用技能
};

struct SAiInfo
{ // 人工智能角色类数据结构
    enum EConstDefine
    {
        constDefaultTaskListSize = 10, // 默认任务缓冲大小
    };

    SAiInfo()
    {
        m_iProduceIndex         = -1;
        m_dwLastThinkingTime    = 0;
        m_sizeTaskList          = constDefaultTaskListSize;
        m_iViewSight            = 10;

        canAttackCharId         = InvalidGameObjectId;
        lastIdleX            = 0.0;
        lastIdleY            = 0.0;
        m_strDeadScriptName.clear();
        m_bPassive              = false;
        m_strItemDropTemplate   = "<void>";
        m_fItemDropMultipleRate = 0.0f;

        memset( &m_CanMoveZone , NULL, sizeof( m_CanMoveZone  ));
        memset( m_bMustUseSkill, 0,    sizeof( m_bMustUseSkill));
        memset( m_iSkillId     , 0,    sizeof( m_iSkillId     ));
        memset( m_stSkillLevel , 0,    sizeof( m_stSkillLevel ));

        m_stSkillRateTotal = 0;
    }

    int   GetCurrentSelectSkillIndex();
    int32 GetCurrentSelectSkillId();
    int32 GetCurrentSelectSkillLevel();

    int         m_iProduceIndex                                  ; // 产生序列号(每次刷怪是给出，怪物死亡时销毁)
    SFPos2      m_ptBornPoint                                    ; // 出生点
    float       lastIdleX                                        ; // 上一次未被攻击时位置X
    float       lastIdleY                                        ; // 上一次未被攻击时位置Y
    uint32      m_dwLastThinkingTime                             ; // 上一次思考时间
    uint8       m_sizeTaskList                                   ; // 任务队列长度
    uint16      m_iSkillId[AI_MONSTERMAXSKILLNUM]                ; // 技能Id
    int8        m_stSkillLevel[AI_MONSTERMAXSKILLNUM]            ; // 技能等级
    uint8       m_stSkillRate[AI_MONSTERMAXSKILLNUM]             ; // 每个技能的概率
    short       m_stSkillRateTotal                               ; // 总概率
    uint32      m_dwSkillStartColdDownTime[AI_MONSTERMAXSKILLNUM]; // 技能组的开始ColdDown时间
    uint32      m_dwSkillColdDownTime[AI_MONSTERMAXSKILLNUM]     ; // 技能组的ColdDown时间    
    bool        m_bMustUseSkill[AI_MONSTERMAXSKILLNUM]           ; // run的时候是否必须使用次技能
    int         m_iViewSight                                     ; // 视野(可攻击范围)
    GameObjectId      canAttackCharId                                  ; // 攻击目标
    RECT        m_CanMoveZone                                    ; // 可以移动范围
    bool        m_bPassive                                       ; // 当前的是否被动的状态
    std::string m_strDeadScriptName                              ; // 死亡脚本(当怪物死亡时调用一个脚本)
    std::string m_strItemDropTemplate                            ; // 物品掉落模板
    float       m_fItemDropMultipleRate                          ; // 物品掉落倍率
};

// ProcessThinking->
// ProcessAiTimer->
// ProcessSelectTask->
// ProcessAIMove->
// ProcessAITask->
class MonsterBase : public BaseCharacter, 
                    public DMonsterAIChar
{ // 人工智能角色类
private:
    struct SAITimer
    {
        DWORD dwStartTime; // 计时器触发起始时间
        DWORD dwDelay;     // 计时器触发间隔
        WORD wCount;       // 计时器触发次数 0xFFFF为无限次
    };

public:
	//寻路状态
	enum FindParthState
	{
		FPS_None,		// 不在寻路
		FPS_Line,		// 直线寻路
		FPS_AStar,		// A*寻路
		FPS_Pos,		// 寻路到的位置不是目标位置,可能是因为目标位置不可达
	};

	// 动态阻挡状态
	enum DynamicBlockState
	{
		DBS_Close,		// 关闭动态阻挡
		DBS_Open,		// 开启动态阻挡
		DBS_TempClose,	// 暂时关闭动态阻挡
	};

    MonsterBase();
    virtual ~MonsterBase();
    
    //////////////////////////////////////////////////////////////////////////
    // IBaseCharProperty
    virtual SCharFightAttr* GetCharFightAttr(){ return &_baseProperty.fightAttr; }
    virtual void            SetHPMax( uint32 hpMax );
    virtual uint32          GetHPMax();
    virtual void            SetMPMax( uint32 mpMax );
    virtual uint32          GetMPMax();
    virtual void            SetMP( int nMp );
    virtual int             GetMP();
    virtual float           GetMoveSpeed()              { return GetCharFightAttr()->moveSpeed.final; }
    virtual void            SetMoveSpeed( float fMove ) { GetCharFightAttr()->moveSpeed.base = fMove; GetCharFightAttr()->moveSpeed.UpdateFinal(); }

    // 声望奖励
    virtual void  SetRewardReputation( int32 value) { _rewardReputation = value; }
    virtual int32 GetRewardReputation() { return _rewardReputation; }

    //  荣誉奖励
    virtual void  SetRewardExpolit( int32 value) { _rewardExpolit = value; }
    virtual int32 GetRewardExpolit() { return _rewardExpolit; }

    // 好友度奖励
    virtual void   SetRewardFriendly( uint32 value ) { _rewardFriendly = value; }
    virtual uint32 GetRewardFriendly() { return _rewardFriendly; }

    // 奖励的道行
    void  SetRewardDaoxing( int32 daoxing ) { _rewardDaoxing = daoxing; }
    int32 GetRewardDaoxing() { return _rewardDaoxing ; }

    virtual void  SetResistBeMove( int16 value ){ _resistBeMove = value; }
    virtual int16 GetResistBeMove(){ return _resistBeMove;}

    virtual void  SetResistBeAtt( int16 value ){ _resistBeAtt = value; }
    virtual int16 GetResistBeAtt(){ return _resistBeAtt; }

    virtual void  SetResistBeMagic( int16 value ){ _resistBeMagic = value; }
    virtual int16 GetResistBeMagic(){ return _resistBeMagic;}

    virtual void  SetResistBeTools( int16 value ){ _resistBeTools = value; }
    virtual int16 GetResistBeTools(){ return _resistBeTools;}

    //virtual void Initialize( const CItemDetail::SMonster* pConfig );

    //////////////////////////////////////////////////////////////////////////

    virtual void  ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue ); // 在处理消息前调用
    virtual bool  ProcessMsg( Msg* pMsg );                                           // 被动消息执行
    virtual void  Run( DWORD dwCostTime );                                           // 主动执行,主运行

    virtual void  OnExit( Msg*pMsg, unsigned char exitType = ET_ExitGame );                                      // 退出
    virtual Msg*  FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize);                                     // 第一眼印象
    virtual void  EnterMySight( BaseCharacter* pWho );                                                           // 进入我的视野
    virtual void  ExitMySight( BaseCharacter* pWho );                                                            // 离开我的视野
    virtual void  OnExitMySightNoPlayer();

    virtual void  RefreshEnmity() = 0;                                                                           // 刷新仇恨
    virtual void  OnDeath();                                                                                     // 死亡
    virtual void  OnBeAttacked( BaseCharacter* pAttacker,const CItemDetail::SItemSkill* pSkillConfig ){}         // 被人打了
    virtual void  BeattackedCallBack(GameObjectId nAttackerID, int nSkillID, int nSkillLevel, int nDamage);     // 被攻击的LUA回调函数支持 告诉LUA脚本攻击者的ID，施放的技能ID，造成的伤害
    virtual void  CallDeadScript();                                                                              // 执行死亡脚本
    virtual bool  MustOpenAI() { return false;}                                                                  // 默认AI不是必须打开的
    virtual short GetProfession() { return m_shProfession; }                                                     // 怪物的职业
    virtual long  ApplyBufferStatus(int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue); // 应用buff
    virtual bool  IsCanAttack( BaseCharacter* pTarget );
    virtual unsigned int AddAttackCharacter( GameObjectId charId );
    virtual unsigned int DecAttackCharacter( GameObjectId charId );
    virtual unsigned int GetEnmityRate() { return m_nEnmityRate; }
    virtual unsigned int GetViewEnmity()  { return _nViewEnmity;  }
    virtual bool         IsPassiveAttack(){ return GetAiData()->m_bPassive; } // 是否是被动攻击
    virtual int          GetViewSight()   { return GetAiData()->m_iViewSight;  } // 获得视野
    virtual GameObjectId       GetTryToAttackCharId()               { return _tryToAttackCharId;        }
    virtual void         SetTryToAttackCharId( GameObjectId nID )   { _tryToAttackCharId = nID;         }
    virtual void         SetAttackCharEnmity( uint32 nEnmity) { _tryToAttackCharEnmity = nEnmity; }
    virtual uint32       GetTryAttackCharEnmity()             { return _tryToAttackCharEnmity;    }


    //////////////////////////////////////////////////////////////////////////
    size_t   GetAttackCharCount() { return attackCharIds.size(); }
    bool     AreaHavePlayer() { return m_n9AreaPlayerCnt > 0; }
    SAiInfo* GetAiData(){ return &_coreAiData; }

    bool  IsAIStartUp(){ return m_bAIStartUp; }
    void  StartUpAI()  { m_bAIStartUp = true; } // 开启怪物AI

    void  SetThinkTime( uint32 iValue ){ m_nThinkingTime = iValue; }

    void  SetFightModulus( float fAttackPhysicsMod, float fDefendPhysicsMod, float fAttackMagicMod, float fDefendMagicMod ); // 设置战斗系数
    float GetAttackPhysicsMod() { return _fAttackPhysicsMod; }
    float GetDefendPhysicsMod() { return _fDefendPhysicsMod; }
    float GetAttackMagicMod()   { return _fAttackMagicMod;   }
    float GetDefendMagicMod()   { return _fDefendMagicMod;   }

    void  SetAttackFloatMin( short sAttackFloating  ) { m_nAttackFloatMin = sAttackFloating; }
    void  SetAttackFloatMax( short sAttackFloating  ) { m_nAttackFloatMax = sAttackFloating; }
    short GetAttackFloat();
    
    void  SetCityMonster(bool bRet){ m_bCityMonster = bRet ;}      // 设置是否城市怪物
    bool  IsCityMonster(){ return m_bCityMonster; }
    void  SetCityDefMonster(bool bRet){ m_bCityDefMonster = bRet;} // 城市防守怪只攻击攻城的
    BOOL  IsCityDefMonster(){ return m_bCityDefMonster; }

    bool  IsPet()            { return _bPet;}
    void  SetIsPet(bool bRet){ _bPet = bRet;}

    void  SetPetType( uint8 petType ) { _petType = petType;}
    uint8 GetPetType(){ return _petType; }

    void  SetNormalMoveSpeed( float fNormalMoveSpeed ){ m_fNormalMoveSpeed = fNormalMoveSpeed; }
    void  SetIdleMoveSpeed(float fIdleMoveSpeed) {m_fIdleMoveSpeed = fIdleMoveSpeed;}
    
    void  SetProfession( short shProfession ){ m_shProfession = shProfession; } // 设置怪物的职业
    
    void  SetMonsterType( short stType );            // 设置怪物类型
    short GetMonsterType(){ return m_stMonsterType;} // 获得怪物类型
    bool  IsNeedFightMonster();                      // 是否是长时间打斗的怪 不是秒杀型的 植物资源    

    void SetProduceIndex(int index) { _coreAiData.m_iProduceIndex = index; } // 设置产生序列号
    int  GetProduceIndex() { return _coreAiData.m_iProduceIndex; }           // 获得产生序列号
    
    void SetBornPoint( SFPos2 ptBorn ); // 设置出生点
    
    void SetSkill(int index,int skill_id);              // 设置技能
    void SetSkillLevel( int index, short skilllevel );  // 设置技能等级
    void SetSkillRate( int index, short skillrate );    // 设置技能使用概率
    
    void  SetSkillRateTotal();              // 设置随机会要用的总技能概率

    int   GetCurSkill()      { return m_iCurSkillId;     } // 获得当前技能
    short GetCurSkillLevel() { return m_stCurSkillLevel; } // 获得当前技能的等级

    void  SetCurSkillIndex( int i );       // 设置当前使用技能栏
    int   GetCurSkillIndex();              // 获取当前使用技能的索引
    void  SetCurSkillLevel( uint8 index ); // 设置当前使用的技能等级

    // 获得/设置怪物slk中的ID
    int   GetMonsterId(){ return m_nMonsterId; }
    void  SetMonsterId( int n ){ m_nMonsterId = n; }
    
    void  SetViewSight( int sight ){ GetAiData()->m_iViewSight = sight; } // 设置视野
    
    
    void  SetIdleMoveViewSight( short sight ){ m_stIdleMoveViewSight = sight; } // 设置空闲移动时的视野
    short GetIdleMoveViewSight()             { return m_stIdleMoveViewSight;  } // 获得空闲移动时的视野

    void  SetFightViewSight(short sight) { m_stFightViewSight = sight; }
    short GetFightViewSight()            { return m_stFightViewSight; }
    
    void SetCanMoveZone( RECT zone ); // 可移动范围
    
    void SetSkill2LowLimit(); // 设置技能2的HP,MP下限
    void SetSkill3LowLimit(); // 设置技能3的HP,MP下限

    // 设置技能的ColdDown
    void SetSkillColdDown();    
    bool IsSkill2CanUse();
    bool IsSkill3CanUse();

    // 获取可移动范围
    RECT GetCanMoveZone();
    bool HaveTask();                            // 当前是否有任务
    int  GetAttackTargetPro();                  // 获取攻击目标的职业信息 返回-1则表示不存在当前攻击目标    
    bool IsSkillAttack( BaseCharacter* pChar ); // 是否可用当前技能攻击
    bool IsAICanAttack( BaseCharacter* pChar ); // 目标是否可攻击

    // 怪物类型状态
    void SetTypeStatus( int nValue ) { m_nTypeStatus = nValue; }
    int GetTypeStatus() { return m_nTypeStatus; }

    // 设置物品掉落模板
    void SetItemDropTemplate( const char *szDropTemplate );

    // 获得物品掉落模板
    const char *GetItemDropTemplate();

    // 设置物品掉落倍率
    void SetItemDropMultiple( float fm );
    
    // 获得物品掉落倍率
    float GetItemDropMultiple();

    float GetPercentHP();

    void SetCurSkillByIDAndLev(unsigned short skillid,unsigned short skilllevel);

    void SetMustUsingSkill(int index,bool ismust);

    // 加载Lua脚本
    void LoadLuaScript( const char* LuaFileName );

    // 掉物品
    void DropItem( int ItemID, float x, float y );

    // 掉落物品
    void DropItemRand( int ItemID, float fRate );    
    
    void AIAttack( int iTarget, int iSkill, int iLevel ); // 发出攻击指令
    
    void TryUseSkill( int nSkillID, int nSkillLevel );       // 使用脚本技能
    void TryUseSkillByID(int nID, int nSkillID, int nLevel); // 指定ID使用特定技能

    // 改变移动速度
    void        ChangeMoveSpeed( float speed );
    
    void        SetDeadScript( const char *szScriptName ); // 设置死亡脚本名
    const char* GetDeadScript();                           // 获得死亡脚本名

    float DropRnd();
    float Rnd();
    
    void AddTask( AiBaseTask * pTask ); // 增加任务
    void ClearTask();                   // 清除任务

    bool IsInRange();    // 最否在追击范围
    bool IsInMoveZone(); // 是否在移动Zone内
    bool IsInBaseEnmityRange();

    void SetFightViewEndTime( DWORD dwTime ){ m_dwFightViewEndTime = dwTime;}    
    void RestoreHPInstant( int nRestoreHP ); // 瞬间回血
    void RestoreMPInstant( int nRestoreMP ); // 瞬间回魔

    void LoseHPInstant( int nLoseHP ); // 瞬间去血
    void LoseMPInstant( int nLoseMP ); // 瞬间去魔
    
    //////////////////////////////////////////////////////////////////////////
    // ForLua
    LuaFunction<int> GetGlobalFun( LPSTR cFuncName ){ return m_LuaScript->GetGlobal(cFuncName); }
    uint16 LuaGetLevel(){ return GetLevel();  }
    int    LuaGetHP()    { return IBaseCharProperty::GetHP(); }   
    void   Say( const char* pBuf );                              // 说一句话
    void   SayAdvance( const char* pBuf, int nCount, int nPos ); // 说带系统信息的话
    int    GetRand( int n ); // 得到一个0到n的随机数
    int    GetTargetHP();    // 获得目标的HP
    int    GetTargetMP();    // 获得目标的MP
    int    GetTargetHPMax(); // 获得目标的最大HP
    int    GetTargetMPMax(); // 获得目标的最大MP
    int    GetTargetLevel(); // 获得目标的等级

    //以下四个函数是设置其他角色对自身的仇恨，
    //和基类CEnmity中的不同，基类CEnmity只设置自身对其他角色的仇恨
    int GetTargetEnmity();                     // 获得对目标对自身的仇恨
    int SetTargetEnmity(unsigned int nEnmity); // 设置当前目标对自身的仇恨

    // 获取其他目标对自身的仇恨 不存在则返回-1
    int GetEnmityByID(GameObjectId nID);

    // 设置其他目标对自身的仇恨 失败返回-1
    int SetEnmityByID(GameObjectId nID, unsigned int nEnmity);

    int GetDamageEnmityByID(GameObjectId nID);

    // 设置视野中其他目标对自身的仇恨随机(对没有造成仇恨的目标无效)
    void RandEnmity(unsigned int nMin, unsigned int nMax);

    // 随机从九宫格内获取一个有仇恨的ID
    int GetRandTarget();

    // 获取当前目标的距离
    int GetTargetDistance();

    // 行为
    void Murder(); // 自杀
    void Exit();   // 退出

    // 提升最大物理攻击力(无叠加效果)
    void UpgradePhysicsAttDamMax( int nValue );

    // 提升物理防御(无叠加效果)
    void UpgradePhysicsDef( int nValue );
    
    void         SetEnmityRate(unsigned int nEnmity) { m_nEnmityRate = nEnmity; }
    void         SetEnmity( unsigned int nEnmity) { _nViewEnmity = nEnmity; }

    //守卫
    GameObjectId  FindPersonKillerToAttack(int nSightRate);
    GameObjectId  FindPersonNormalToAttack(int nSightRate);
    GameObjectId  FindPersonPoliceToAttack(int nSightRate);
    GameObjectId  FindPersonAttackerToAttack(int nSightRate);

    void          SetSummonMasterID( GameObjectId stID ){ _summonMasterId = stID;} // 设置召唤主的ID
    BOOL		  IsSummonMonster()  { return _summonMasterId >= 0; } // 是否召唤怪物
    GameObjectId  GetSummonMasterID(){ return _summonMasterId; }      // 获取召唤主的ID

    void       SetProtectChar( GameObjectId ProtectCharID ); // 设置保护他的人
    bool       HaveProtectChar(){ return _protectCharId != -1; }

    BOOL       IsAttackTargetIsProtectChar(); // 是否攻击的目标是保护他的人

    void       SetBindProtectCharVarId( int varId ){ _protectCharVarId = varId; }
    int        GetBindProtectCharVarId() { return _protectCharVarId; }

    void       SetDisappearTime( DWORD dwTime );   // 设置消失时间
    void       AskToAttackTarget();                // 命令怪物攻击目标
    void       AskToFollowMaster();                // 命令怪物跟随主人

    void       SetSpecialTarget( DWORD dwValue );
    DWORD      GetSpecialTarget() const { return m_dwSpecialID; }
    bool       IsHaveSpecialTarget() const { return m_dwSpecialID != 0; }
    bool       IsSpecialTarget( DWORD dwValue ) const { return m_dwSpecialID == dwValue; } 

    bool       MasterOutOfTarget(BaseCharacter* Master,BaseCharacter *Target, float distance);
                
    bool       IsHaveMoveAbility(); // 是否有移动的能力
    bool       GetNeedFollowSummonMaster() { return _bNeedFollowSummonMaster; }

	//////////////////////////////////////////////////////////////////////////
	//寻路
	typedef std::vector< swVec2f >	FindParth;
	typedef FindParth::iterator		ItrFindParth;

	void		InitFindParth();												// 初始化寻路信息
	void		CheckFindParthConfigChange();									// 检测寻路配置变化
	bool		FindTheNextPosToMove( D3DXVECTOR3& vTargetPos, float& fRange );	// 寻找下一个目标位置,等待线程寻路时返回false
	void		AfterMoveToPos();												// 移动后
	void		CheckReachPos();												// 检查是否寻路结束
	bool		IsFindParth()		{ return _charFindParth.IsFindParth(); }	// 是否开启寻路
	CharacterFindParth& GetCharFindParth() { return _charFindParth; }

    //////////////////////////////////////////////////////////////////////////
    // 对属性操作
    void           SetPassiveAttack( bool bPassive ) { GetAiData()->m_bPassive = bPassive; } // 设置为被动攻击
              
    void           SetIdleMoveRate(int16 nValue)     { m_stIdleMoveRate = nValue;  }
              
    void           SetCashMoney(int nValue)          { m_nCashMoney = nValue;      }
    int            GetCashMoney()                    { return m_nCashMoney;        }
              
    void           SetRewardStatusID( uint16 nValue) { m_nRewardStatusID = nValue; }
    uint16         GetRewardStatusID()               { return m_nRewardStatusID;   }
              
    void           SetRewardMulType ( uint16 nValue) { m_nRewardMulType  = nValue; }
    uint16         GetRewardMulType()                { return m_nRewardMulType;    }
              
    void           SetRewardMulValue( uint16 nValue) { m_nRewardMulValue = nValue; }    
    uint16         GetRewardMulValue()               { return m_nRewardMulValue;   }

    //////////////////////////////////////////////////////////////////////////
    // 对目标的操作
    bool           HaveAskToAttackTargetId()            { return m_AskToAttackTargetID >= 0;}
    void           ClearAskToAttackTargetId()           { m_AskToAttackTargetID = -1; }

    bool           HaveTryToAttackCharId()              { return _tryToAttackCharId != InvalidGameObjectId;}
    
    void           ClearTryToAttackCharId();
    void           ClearTryToAttackCharEnmity();

    void           LockTarget( GameObjectId nMaxEnmityCharId );  // 锁定目标
    void           LostAttackTarget();                  // 丢失攻击目标

    void           SetCanAttackCharId( GameObjectId charId ) { _coreAiData.canAttackCharId = charId;                       } // 设置攻击目标
    void           ClearCanAttackCharId()              { _coreAiData.canAttackCharId = InvalidGameObjectId;         }
    GameObjectId         GetCanAttackCharId()                { return _coreAiData.canAttackCharId;                         } // 获取攻击目标
    bool           HaveCanAttackCharId()               { return _coreAiData.canAttackCharId != InvalidGameObjectId; } // 是否有攻击目标
    BaseCharacter* GetCanAttackChar(); // 获得攻击目标  

protected:
    // 一轮的AI
    void ProcessAIThink()                 ; // 思考
    void ProcessAITimer()                 ; // 时间触发检测
    void ProcessAISelectTask()            ; // 选择AITask
    void ProcessAIMove( DWORD dwCostTime ); // 处理AI移动    
    void ProcessAIDoTask()                ; // 处理AItask

protected:
    virtual bool OnThink()                  = 0;       // 在思考时候
    virtual bool OnMove( uint32 lapseTime ) = 0;       // 在移动时候
    virtual bool OnSuccessLockTarget(){ return true; } // 在成功锁定目标时候

    //////////////////////////////////////////////////////////////////////////
    // 召唤宠物
    void FollowTheSummonMaster( BaseCharacter* pSummoner ); // 跟随召唤主移动
    void FlyToTheSummonMaster();                            // 瞬间移动到召唤主的身边

    // 攻击目标    
    void AITryAttack();   // 尝试普通攻击
    void AITryUseSkill(); // 用技能攻击

    // 定时器
    void AddTimer( DWORD dwTime ); // 加一个时间给时钟
    bool GetTimer();               // 看时钟是否到点

    void SetTimer(unsigned int nIndex, DWORD dwDelay, WORD wCount);
    void DelTimer(unsigned int nIndex);
    
    void SetArray( int nIndex, int nValue );      // 设置脚本中要存储的变量
    int  GetArray( int nIndex );                  // 提取存储的变量
    
    void SetBoolArray( int nIndex, bool bValue ); // 设置脚本中布尔值的存储
    bool GetBoolArray( int nIndex );              // 提取脚本中的布尔值
    
    bool SummonMonster         ( int nMonsterIndex, int nMonsterAmount, int nRadius, int nSummonType );
    bool SummonInfluenceMonster( int nMonsterIndex, int nMonsterAmount, int nRadius, int nSummonType, int nInfluence );

    void SendVerifyPos( float x, float y );
    void SendClosingToTarget( GameObjectId nTargetID, D3DXVECTOR3 vNextPos );

    // 处理阵营怪死亡
    void ProcessCampMonsterDeath();
    virtual void MAlarmWhenBeAttack();

public:
    friend class GamePlayer;
    int   nSuperfluitySkillExp; // 额外的技能经验
    int   nMaxRange           ; // 活动范围
    int   m_nBaseEnmityRange  ; // 基础仇恨持续范围 
    uint8 changePassiveConfig ; // 战斗时是否成为被动怪被动怪
    int   endPassiveTimeConfig; // 战斗结束被动持续时间
    bool  bPassiveConfig      ; // 是否被动怪数据

protected:
    // 任务自动表
    AITaskContainer m_vecHighTask;
    AITaskContainer m_vecNormalTask;
    AITaskContainer m_vecLowTask;

    SAiInfo     _coreAiData                         ; // AI数据
    int         m_nVMId                             ; // 死亡脚本脚本器
    bool        m_bAIStartUp                        ; // AI是否开启
    uint32      m_n9AreaPlayerCnt                   ; // 9宫格内玩家数量    
    DWORD       m_dwFightViewEndTime                ; // FightView结束时间
    uint32      m_nThinkingTime                     ; // 怪物的思考时间
    int         m_nAiValueWave                      ; // 怪物的思考波动
    short       m_nAttackFloatMin                   ; // 攻击最小系数
    short       m_nAttackFloatMax                   ; // 攻击最大系数 
    DWORD       m_dwTimeStep                        ; // Timer的总运行时间
    DWORD       m_dwStartTime                       ; // Timer的开始时间
    bool        m_bTimerActive                      ; // Timer是否开着
    bool        _bPet                               ; // 是否pet
    uint8       _petType                            ; // 宠物类型
    GameObjectId      _tryToAttackCharId           ; // 尝试去攻击目标的Id
    uint32      _tryToAttackCharEnmity              ; // 尝试去攻击目标的Id对应的仇恨

    typedef std::set<uint16>              AttackCharContainer;
    typedef AttackCharContainer::iterator ItrAttackCharContainer;
    AttackCharContainer attackCharIds               ; // 当前怪物具有仇恨的角色列表

    uint8       m_nTypeStatus;                      ; // 怪物类型状态( npc对话状态, 怪物可攻击状态等... )

    bool        m_bMoving                           ; // 在移动中
    uint32      m_nEnmityRate                       ;            
    uint32      _nViewEnmity                        ; // 进入怪物视野触发的仇恨初值
    bool        m_bIsFighting                       ; // 在战斗状态
    short       m_shProfession                      ; // 怪物的职业
    bool        m_bLuaScriptLoaded                  ; // Lua脚本是否已载入
    short       m_stMonsterType                     ; // 怪物类型
    short       m_stIdleMoveViewSight               ; // 空闲移动中的视野
    short       m_stFightViewSight                  ; // 战斗时的视野
    short       m_stIdleMoveRate                    ; // 控制空闲移动的频率值
    uint16      m_ustSkill2HPLowerLimit             ; // 技能2的HP最小下限
    uint16      m_ustSkill2MPLowerLimit             ; // 技能2的MP最小下限
    uint16      m_ustSkill3HPLowerLimit             ; // 技能3的HP最小下限
    uint16      m_ustSkill3MPLowerLimit             ; // 技能3的MP最小下限
    bool        m_bSkill2Restore                    ; // 技能2是否恢复性技能
    bool        m_bSkill3Restore                    ; // 技能3是否恢复性技能    
    bool        _disableControlThinkTime            ; // 不要控制思考时间 
    short       m_stCurAttackRange                  ; // 记录当前的攻击距离
    uint8       m_stCurAiTactic                     ; // 当前的AI策略
    bool        _isNeedMove                         ; // 是否需要移动
    float       m_fNormalMoveSpeed                  ; // 平时的移动速度
    float       m_fIdleMoveSpeed                    ; // 空闲移动速度
    uint16      m_iCurSkillId                       ; // 当前技能
    uint8       m_nCurSkillIndex                    ; // 当前技能的索引
    short       m_stCurSkillLevel                   ; // 当前技能等级
    int         m_nMonsterId                        ; // 怪物monster.slk中的ID    
    D3DXVECTOR3 m_vLastSendTargetPos                ; // 最后一次发送的移动目标点
    uint32      m_dwSendMoveMessageTime             ; // 最近一次发移动中消息的时间
    uint32      m_noMoveSendVerifyPosTime           ; // 最近一次在不移动的情况下发纠正位置的时间
    uint16      m_ushDirUnChangedCount              ; // 怪物方向未改变的记数器
    bool        m_bClosingToTarget                  ; // 靠近目标
    bool        m_bCityMonster                      ; // 城战特殊怪FLAG，只能被不是守城的攻击
    bool        m_bCityDefMonster                   ; // 城市防守怪只攻击攻城的
    D3DXVECTOR3 _moveTargetPos                      ; // 制定的目标位置
    DWORD       m_dwSpecialID                       ; // 属于某个玩家
    GameObjectId  _summonMasterId                  ; // 召唤主的ID
    GameObjectId  _protectCharId                   ; // 保护者的ID
    int         _protectCharVarId                   ; // 绑定的保护人的基数变量
    GameObjectId  m_AskToAttackTargetID            ; // 要求攻击的目标ID
    float       _fAttackPhysicsMod                  ; // 物理攻击系数
    float       _fDefendPhysicsMod                  ; // 物理防御系数
    float       _fAttackMagicMod                    ; // 法术攻击系数
    float       _fDefendMagicMod                    ; // 法术防御系数
    int         m_nCashMoney                        ; // 掉落金钱
    uint16      m_nRewardStatusID                   ; // 奖励状态
    uint16      m_nRewardMulType                    ; // 奖励倍数类型
    uint16      m_nRewardMulValue                   ; // 奖励倍数值    
    bool        _bNeedFollowSummonMaster            ; // 是否需要跟随主人
    CItemDetail::SItemSkill* m_pCurSkill            ; // 当前选择使用的技能
    LuaStateOwner m_LuaScript                       ; // 创建Lua解释器
    SAITimer      m_Timer[AI_MAXTIMER]              ;
    AiTaskManager _AiTaskManager                    ;
    int           m_nArray[AI_ARRAY_SIZE]           ;
    bool          m_bArray[AI_BOOLARRAY_SIZE]       ;
    uint32        _endPassiveTimeRecord             ; // 战斗结束被动持续时间纪录
    GameTimerEx   m_xDisappearTimer                 ; // 消失定时器

	CharacterFindParth	_charFindParth;
};

inline void MonsterBase::SetFightModulus( float fAttackPhysicsMod, float fDefendPhysicsMod, float fAttackMagicMod, float fDefendMagicMod )
{ 
    _fAttackPhysicsMod = fAttackPhysicsMod; 
    _fDefendPhysicsMod = fDefendPhysicsMod;
    _fAttackMagicMod   = fAttackMagicMod;
    _fDefendMagicMod   = fDefendMagicMod; 
}

inline short MonsterBase::GetAttackFloat()  // 得到攻击浮动值
{ 
    return 0;
}

inline void MonsterBase::SetMonsterType( short stType)
{
    if( stType < 0 )
    {
        m_stMonsterType = eMT_NormalMonster;
    }
    else
    {
        m_stMonsterType = stType;
    }
}

// 需要长时间战斗的怪物
inline bool MonsterBase::IsNeedFightMonster()
{
    switch( m_stMonsterType )
    {
    case eMT_NormalMonster:
    case eMT_LeaderMonster:
    case eMT_BossMonster:
    case eMT_GodMonster:
    case eMT_Trap:
    case eMT_Pet:
    case eMT_IllusionMonster:
    case eMT_Protect:
        return true;
        break;
    default:
        break;
    }
    
    return false;
}

inline void MonsterBase::SetBornPoint( SFPos2 ptBorn )
{
	_coreAiData.m_ptBornPoint = ptBorn;
	_coreAiData.lastIdleX = ptBorn.x;
	_coreAiData.lastIdleY = ptBorn.y;
}

#endif // __GAMESERVER_AICHARACTER_H__

