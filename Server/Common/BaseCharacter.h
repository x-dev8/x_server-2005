/********************************************************************
    Filename:     BaseCharacter.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_CHARACTER_H__
#define __GAMESERVER_CHARACTER_H__

#pragma once

#include "GlobalDef.h"
#include "MessageDefine.h"
#include "DataBuffer.h"
#include "ScriptVM.h"
#include "ScriptMgr.h"
#include "CharacterTimeStatus.h"
#include "Helper.h"
#include "Formula.h"
#include "ItemDetail.h"
#include "BuffStatusManager.h"
#include "ContinuousTime.h"
#include "GameServer.h"
#include "GameArea.h"
#include "GameStage.h"
#include "Enmity.h"
#include "NewWithDebug.h"
#include "SkillTaskManager.h"
#include "IBaseCharControl.h"
#include "IBaseControl.h"
#include "NetControl.h"
#include "ItemSkillSpecialAttr.h"
#include "MountManager.h"
#include "RecipeManager.h"
#include "AttackFunction.h"
#include "IBaseCharProperty.h"
#include "GameDefinePet.h"
#include "AiDefine.h"
#include "GameBattleMessage.h"

// 是否根据荣誉值强制玩家下线
//const bool KICK_CREDIT = false;

class GamePlayer;
class CEffectChar;
class GameStage;

enum EGameLogicResult
{
    GLR_Success = ER_Success,
    GLR_StatusNotExist,
    GLR_InDeadNotUseStatus,
    GLR_StatusSourceNotExist,
    GLR_StatusApplyFail,
};

enum EPlayerStatus
{ //游戏世界主逻辑中的状态
    CS_START,                  // 在Character::里面默认是这值
    CS_CHECK,                  // PlayerChar会默认改变到这个数值等待客户端发送过来验证消息..(说我是天的客户端)
    CS_LOGIN,                  // 收到登录
    CS_LOGINTODB,              // 将消息转发到数据库
    CS_WAITDBRET,              // 等待从数据库读取Player角色数据
    CS_DBLOGINED,              // 将消息转发到数据库    

    //游戏世界
    CS_LOADINGMAP            , // 用户正在载入地图，不能移动，不能被攻击
    CS_IDLE                  , // 待机
    CS_WALK                  , // 行走
    CS_ATTACK                , // 攻击
    CS_INTONATE              , // 吟唱
    CS_HURT                  , // 受伤
    CS_DIEING                , // 死亡状态，用于等待重生
    CS_DOACTION              , // 做动作状态
    CS_HOLDSKILL             , // 维持技能状态
    CS_READYTOUSESPEICALSKILL, // 准备使用特殊技能
    CS_USESPEICALSKILL       , // 发动特殊技能
    CS_ONSHIP                , // 在转载物上
    CS_WAITRETURNTOCHARACTER , // 等待回到选人界面
};

const float monsterCastCorrect = 0.2f;

//////////////////////////////////////////////////////////////////////////
class BaseCharacter : public IBaseCharControl, 
                      public IBaseCharProperty,
                      public AiEnmity
{ // 基础角色类
public:   
    struct SContinuousSkillData
    { //持续性判定
        //是否是创建了效果角色的技能        
        //效果角色技能的结算由效果角色处理
        //bool bEffectSkill;
        //unsigned short ustSkillEffectID;

        bool  bMoveInterrupt;        // 移动是否打断
        
        DWORD dwTimeNextDoAttack;    // 下次结算时间
        DWORD dwAttackInterval;      // 攻击间隔
        DWORD dwTimeSkillHoldingEnd; // 维持技能结束的时间

        ItemDefine::SItemSkill* pSkill;

        //维持技能创建的EffectChar
        //在维持技能结束前，EffectChar一直都存在
        CEffectChar* pEffectChar;

        bool bCharTarget;

        //当前的攻击目标和LifeCode
        GameObjectId  ustTargetChar;
        unsigned short ustTargetLifeCode;

        D3DXVECTOR3    vTargetPos;
    };
    
    struct SEmission
    { // 角色发出的魔法剑
        BOOL  bDead;        // 是否死亡
        DWORD dwStartTime;
        DWORD dwLifeTime;
		GameObjectId  ustTargetID;
        unsigned short ustSkillID;
        unsigned short ustSkillLevel;

        SEmission()
        {
            bDead = TRUE;
        }
    };

    struct SRestoreTime
    {
        DWORD dwLastHPRestoreTime;     // 下次HP恢复检查时间
        DWORD dwLastMPRestoreTime;     // 下次MP恢复检查时间
        DWORD dwLastXPRestoreTime;     // 下次XP恢复检查时间
        DWORD dwLastPassOnlineTime;    // 下次检查在线时间
        DWORD dwLastDoubleExpTime;     // 下次检查双倍经验
    };

    struct SPlayerScore
    { // 记录攻击者的信息
        SPlayerScore()
        {
            stID    = -1;
            iDamage = 0;
			dwLastDamageTime = 0;
        }
        GameObjectId stID;
        int			 iDamage;
		DWORD dwLastDamageTime;
    };

    struct PlayerExtraDamage
    { // 记录剩余攻击力(因为攻击力太少,不能取得经验)
        PlayerExtraDamage()
        {
            stID = -1;
            iDamage = 0;
        }
        GameObjectId stID;
        int			  iDamage;
    };

    struct SDaoxingEffect
    {
        SDaoxingEffect()
        {
            nStatusID = 0;
            nDurationTime = 0;
        }
        
        void Reset()
        {
            nStatusID = 0;
            nDurationTime = 0;
        }

        uint16 nStatusID;
        uint32 nDurationTime;
    };
	
//////////////////////////////////////////////////////////////////////////
// 方法
public:
    BaseCharacter();
    virtual ~BaseCharacter() {};

    virtual void  OnExit( Msg* pMsg, unsigned char exitType = ET_ExitGame ) = 0;
    virtual void  OnDeath()                                                 = 0;     // 死亡

    virtual void  ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue ); // 在处理消息前调用
    virtual bool  ProcessMsg( Msg* pMsg );                                           // 处理消息
    virtual void  ProcessLogicAfterProcessMsg( DWORD dwCostTime, bool& bContinue );  // 在处理消息后调用
    virtual void  Run( DWORD dwCostTime );                                           // 整个逻辑帧Run

    virtual void  RefreshEnmity(){}
    virtual Msg*  FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize); // 第一眼印象
    virtual void  EnterMySight( BaseCharacter* pWho ){}
    virtual void  ExitMySight( BaseCharacter* pWho ){}
    virtual void  SendVerifyPos(){}    
    virtual short GetProfession() { return EArmType_Monster; }
    virtual short IsSkillCanUse(int skill_no, int skill_level);    // 判断是否可用此技能
    virtual void  RefreshCharData( DWORD dwCostTime );             // 刷新人物数据[更新频率1秒一次]
    virtual bool  IsCanSwitchStage() { return m_bCanSwitchStage; } // 检测是否可以切换场所
    virtual bool  CheckWalkPreconditionState();                    // 判断可否移动
    virtual bool  CheckUseSkillPreconditionState();                // 判断NPC是否处在一个可以使用一个技能的状态

    virtual DWORD SkillDischarge( SAttackTarget *pTarget, unsigned short ustSkillID, unsigned short ustSkillLevel, BaseCharacter *pMaster, int nTargetCount = 0 );
    virtual void  OnBeAttacked( BaseCharacter* pAttacker, const ItemDefine::SItemSkill* pSkillConfig );
    virtual void  OnHaveStatusDisplacement();
    virtual void  OnBeBackAttack();
    virtual void  OnBuffStatusChanged( bool bSendMessage );

    virtual long  ApplyBufferStatus(int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue){ return GLR_Success; }// 应用buffer

    virtual bool  OnScriptSkill( ItemDefine::SItemSkill* pItemSkill ){ return true; }
    virtual short ApplySkillCost( ItemDefine::SItemSkill *pSkill ); // 应用技能消耗
    virtual void  OnEnterFightState(){};                             // 进战斗状态
    virtual void  OnOutFightState(){};                               // 出战斗状态
    virtual void  OnIncreaseExp( int exp ){}                         // 添加经验
    
    virtual CScriptVM* GetVM(){ return NULL; } // 设置对应脚本

    virtual void TellClient( const char* string, ... ){} // 给客户端发送一句话
    virtual void TellClient( unsigned short ustStringID, UnionParam *pParam = NULL, int nCount = 0 ){}
    virtual void ShowInfo( bool bTile, DWORD type, const char* string, ... ){}
    virtual void ShowInfo( bool bTile, DWORD type, unsigned short ustStringID, UnionParam *pParam = NULL, int nCount = 0 ){}

    virtual void Log( const char* szFormat, ... ){}

    virtual DWORD GetTeamID() { return 0; }
    virtual void  SetTeamID(DWORD dwSessionId) {}
    virtual bool  HaveTeam() { return false; }
    virtual bool  IsTeamMember( BaseCharacter* pChar ) { return false; }

    virtual DWORD GetGuildID() const { return 0; }
    virtual bool  HaveGuild() const { return false; } 
    virtual bool  IsGuildMember( BaseCharacter* pChar ) { return false; }

    virtual void PunishWhenDeath( BaseCharacter* pAttacker ) {};

    //物品的和技能的
    //pChangeECS 每个人都能看到的改变
    //如：攻击速度，移动速变化度的
    //bApplyEquip是否是装备的附加属性
    virtual void ApplySpecialAttr( int iWhichAttr,USpecialAttrValue *pValue , bool bAdd,MsgCharAttrChanged *pChangeECS = 0,bool bApplyEquip = false );

    virtual bool TryPassivenessTriggerAttack() { return true; } // 尝试被动触发技能

    virtual void OnEnterStage(){}
    virtual void OnLeaveStage(){}

    virtual unsigned int GetEnmityRate()  { return 100; }

    //TODO: 需要移除的方法
    //virtual unsigned int AddAttackCharacter( GameObjectId charId ){ return 0; }
    //virtual unsigned int DecAttackCharacter( GameObjectId charId ){ return 0; }
    //virtual void         ClearTryToAttackCharId(){}
    //virtual void         ClearTryToAttackCharEnmity(){}
    //virtual unsigned int GetViewEnmity()  { return 10;  }
    //virtual bool         IsPassiveAttack(){ return true; }  // 是否是被动攻击
    //virtual int          GetViewSight()   { return 1;  }    // 获得视野
    //virtual bool         IsInBaseEnmityRange(){ return false; }
    //virtual GameObjectId       GetTryToAttackCharId()  { return InvalidGameObjectId; }
    //virtual void         SetTryToAttackCharId( GameObjectId nID )   { }
    //virtual void         SetAttackCharEnmity( uint32 nEnmity) { }
    //virtual uint32       GetTryAttackCharEnmity()             { return 0; }
    //virtual uint32       GetGuildID()                         { return 0; }


    //////////////////////////////////////////////////////////////////////////
    // 角色类型判断
    virtual bool IsNpc() { return false; }
    virtual bool IsItem() { return false; }
    virtual bool IsPlayer() { return false; }
    virtual bool IsMonster() { return false; }
    virtual bool IsFightNpc() { return false; }
	virtual bool IsEffectChar() { return false; }
    virtual bool IsPet() { return false; }
    virtual bool IsResourceMonster();

    // 获得怪物类型
    virtual uint8 GetMonsterType() const { return eMT_MaxCount; }

    virtual void SetMasterID( GameObjectId nValue ) {}
    virtual GameObjectId GetMasterID() { return InvalidGameObjectId; }
    bool HaveMaster() { return GetMasterID() != InvalidGameObjectId; }
    virtual GamePlayer* GetMasterPlayer() { return NULL; }

    // 获得怪物ID
    virtual int GetMonsterID() { return 0; }

    // 获得怪物专属类型
    virtual int GetSpecialType() const { return MonsterDefine::SpecialNone; }
    virtual uint32 GetSpecialValue() const { return 0; }
    virtual bool CheckSpecialTarget( int nSpecialType, GamePlayer* pTarget ) { return false; }
    
    void CriticalError(char* szFun, char* szFile, int nLine, unsigned char exitType = ET_ExitGame); // 严重错误，角色从世界销毁 必须处理MSG_EXIT消息
    
    void ExitWorld(char* szFun, char* szFile, int nLine,unsigned char exitType = ET_ExitGame);     // 对象退出世界
    void ExitWorld();
    void ExitWorldByPushMsg();

    unsigned short GetPlayerEctypeMapLevel( uint32 nMapID, float fX, float fY, bool bConsultTeam = true );
    
    void   CalcEquipHp( BaseCharacter* pTarget );    // 计算装备耐久度
    
    // 计算仇恨
    virtual void CalcEnmity( BaseCharacter* pCharTarget, const ItemDefine::SItemSkill* pSkillConfig, int nDamage );
    
    void  SetFightCamp( uint8 uchValue, bool bSendMessge = false );
	void  SetFightGame( uint8 uchValue, bool bSendMessge = false );
	uint8 GetFightCamp() const { return m_uchFightCamp; }
    bool  HaveFightCamp(){ return m_uchFightCamp != 0; }

    void SetCanSwitchStage( bool bCan = true ) { m_bCanSwitchStage = bCan; }    // 设置是否可以切换场所，默认为可切换。
    bool CheckPos( DWORD *pdwMapId, int *pnX, int *pnY, bool bCorrect );        // 检查并纠正玩家坐标

    // iGate==-1表示向所有Gate发送
    // 否则，就是新Gate连入，单独处理
    void SendSyncCharPosToGate( int iGate = -1 );
    void SendNPCExit();

    float GetLevelDistanceExpModulus(short stSrcLevel,short stTargetLevel);    

	
    
    void  SetDirectiron (float fDir);
    void  CaluStepCost  (BYTE byDir);				//判断走当前一步需要的时间..计算移动需要的时间
    bool  MoveToNextStep(BYTE byDir);
    bool  IsNextStepMoveable( int iDir );

    bool  UseRestoreItem( ItemDefine::SItemRestore *pRestore);
    
    void  SendSkillStatusTo( BaseCharacter* pTarget );
    //void  UpdateTeamScore( GamePlayer *pCharMember, int iScore );   //更新团体成绩  废弃了...

    // 技能打斗相关
    bool CheckContinuousSkillCost();    // 检查持续技能是否可以继续
    void CancelSkill();                 // 取消当前技能状态
    virtual void DoAssaultMoving( float fDistance, int nInstantMovingType ){};  // 冲锋技能

    // 锁定目标
    void SetLockID( GameObjectId nValue ) { m_nLockID = nValue; }
    GameObjectId GetLockID() const { return m_nLockID; }
    void ClearLockID() { m_nLockID = InvalidGameObjectId; }
    bool HaveLockTarget() { return m_nLockID != InvalidGameObjectId; }
    BaseCharacter* GetLockChar();

    bool FindAttackTarget ( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkill, OUT CFormula& formula );   
    bool FindAttackTarget ( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkill, OUT std::vector< BaseCharacter* >& vecTargetList );

    // 吟唱
    bool  IsCurrentTaskCanBeInterrupt( uint8 interruptType );
    void  IntonatingInterrupt( int nInterruptValue );                   //吟唱时间打断
    //float GetActualIntonateTime( unsigned short ustSkillIntonateTime )  //得到实际的吟唱时间(与技能有关)
    //{ return ustSkillIntonateTime - ustSkillIntonateTime*GetCharFightAttr()->intonate.final/250;} 

    DWORD TryAttack( SAttackTarget* pTarget,ItemDefine::SItemSkill *pSkill,unsigned short ustSkillID, unsigned short  ustSkillLevel, int nTargetCount = 0 ); // 尝试攻击    
    BOOL  IsPosInRange( float x, float y, float fDist );                 //是否在范围内    
    
    BOOL  IsInAttackRange( BaseCharacter *pDst, ItemDefine::SItemSkill* pSkill, float fRangeCorrect = monsterCastCorrect); // 是否在攻击范围之内
    bool  IsInValidCastRange( float x, float y, ItemDefine::SItemSkill* pSkill );

    DWORD MagicObjectAttack(SAttackTarget *pTarget, DWORD ustSkillID, DWORD ustSkillLevel); // 释放出一个出现在地图上的法术效果

    BYTE  GetSubAction() { return m_bySubAction; } 
    void  ChangeSubAction( BYTE bySubAction, GameObjectId sTargetCharId );

    float GetWeaponAttackRange(){ return m_fWeaponAttackRange; }
    void  SetWeaponAttackRange( float fRange ){ m_fWeaponAttackRange = fRange; }
    
    virtual SCharBaseAttr* GetCharBaseAttr() { return NULL; }
    
    void ClearAllBaseAttrByPart  ( ECustomDataPart part );
    void ClearAllFightAttrByPart ( ECustomDataPart part );

    void UpdateCharAllAttibute();       // 重新计算人物属性

    BuffStatusManager* GetBuffManager() { return &_buffManager; }    
    bool IsCanDoAction();               // 判断能否做某种行为动作

    void           SetKiller( BaseCharacter* pBelongKiller ){ m_pBelongKiller = pBelongKiller; }
    BaseCharacter* GetKiller( void ){ return m_pBelongKiller; }

    bool TryChangeFightState( bool bAdd, EActionFlag flag, bool bSendMessage = true );         // 改变行为状态
    bool HaveFighteFlag( EActionFlag flag ){ return _HAS_FLAG(m_dwFightFlag, flag); }   // 是否在某种行为状态   
    
    void AddDeBufferAttack(GameObjectId nTargetCharID); // 攻击增加状态      作用目标自己 打人的时候
    
    void SetIsBeCriticaled(bool bIsCsed) { m_bBeCSed = bIsCsed;}
    bool GetIsBeCriticaled()             { return m_bBeCSed;} // 是否被暴击

    // 人物状态
    uint8 GetStatus() { return _bodyStatus;}        // 取得当前的状态
    void  SetStatus( uint8 bodyStatus );            // 设置状态
    uint8 GetMoveStatus() { return _moveStatus; }   // 取得移动状态
    void  SetMoveStatus( uint8 moveStatus );

    int  GetNextStatus() { return _bodystatusOld;; }// 获得下一个状态
    void ApplyNextStatus();                         // 应用下一个状态

    //人物状态作用数值到人物一级二级属性
    virtual void ApplyBuffStatusToCharAttr() { _buffManager.ApplyBuffsToChar( GetProfession(), GetCharBaseAttr(), GetCharFightAttr() ); }
    
    // BuffManager
    void SendBuffs      ( GamePlayer* pPlayer, bool bNeedKnowLast );    // 同步Buff list -1 true
    void SendBuffChanged( GamePlayer* pPlayer );                        // 发有改变的Buff
        
    void UpdateBuff();             // 更新目标状态 时间清除 伤害清除
    void UpdateBuffDamage();       // 更新状态的伤害Update
    bool UpdateBuffOnAttack();     // 更新在攻击的时候是否需要清掉状态
    bool UpdateBuffOnBeAttacked(){ return false; }

    // 其实状态
    void  SetCauseStatusID( short ustStatusID )      { m_ustCauseStatusID = ustStatusID;}
    void  SetCauseStatusLevel( short ustStatusLevel ){ m_stCauseStatusLevel = ustStatusLevel;}
    void  SetCauseStatusRate( short ustStatusRate )  { m_ustCauseStatusRate = ustStatusRate;}
    short GetCauseStatusID()    { return m_ustCauseStatusID; }
    short GetCauseStatusLevel() { return m_stCauseStatusLevel;}
    short GetCauseStatusRate()  { return m_ustCauseStatusRate;}
    
    // 判断可否被攻击 判断可否PK 判定技能释放对象是否合理
    //bool IsCastTargetRight( const ItemDefine::SItemSkill*pSkill, BaseCharacter* pTagChar); // 攻击结算对象是否合理            
    bool IsCastTargetRight( const ItemDefine::SItemSkill* pSkill, BaseCharacter* pTagChar);
    bool IsCastTargetRight( const ItemDefine::SItemSkill* pSkill, int x, int y );    
    //bool IsCanBeAttacked();
    bool IsCanBeAttackedObject(); // 是否是可被攻击的对象类型
    bool IsHaveHpObject();        // 是否是有HP对象 

    bool CheckCanAttackTarget( BaseCharacter* pTarget );
    virtual bool CheckCanBeAttack();// 判断是否能被攻击

    BOOL IsInTargetBack ( BaseCharacter* pChar, float fMaxAngle );
    BOOL IsTargetInFront( BaseCharacter* pChar, float fMaxAngle );
    BOOL IsTargetInBack ( BaseCharacter* pChar, float fMaxAngle );
    
    virtual void IncreaseSingleSkillExp( int nSkillExp ){}
    virtual void IncreaseTotalSkillExp( int nSkillExp ){}

    void  SetIllusionChar( BOOL bIllusionChar ){ m_bIllusionChar = bIllusionChar;}
    BOOL  IsIllusionChar(){ return m_bIllusionChar; }

    uint32 GetLastMapID()              { return m_dwLastMapID; }
    void   SetLastMapID( uint32 dwID ) { m_dwLastMapID = dwID; }

    uint32 GetLastEctypeMapID()             { return m_dwLastEctypeMapID; }
    void   SetLastEctypeMapID( uint32 dwID) { m_dwLastEctypeMapID = dwID; }
    
    bool ChangeAttr( unsigned short ustWhichAttr, float fValue,   bool OnlyMe = false );
    bool ChangeAttr( unsigned short ustWhichAttr, DWORD dwValue,  bool OnlyMe = false );
    bool ChangeAttr( unsigned short ustWhichAttr, short stValue,  bool OnlyMe = false );
    bool ChangeAttr( unsigned short ustWhichAttr, int nValue,     bool OnlyMe = false );
    bool ChangeAttr( unsigned short ustWhichAttr, __int64 nValue, bool OnlyMe = false );

    virtual void Say( int nType, const char* szValue );
    virtual bool HaveAreaPlayer() { return false; }

    // 被杀死了，添加一些处理，清除当前的一些任务，处理
    // 如：正在吟唱被打死，应该先清除吟唱状态
    virtual void WasKilled( BaseCharacter* pKiller );// 单位被杀死了 注意重载

    // 死亡
    void SetDead( bool bDead = true ) { m_bDeadFlag = bDead; } // 设置死亡标志
    bool IsDead() { return m_bDeadFlag; }                      // 是否为无血死亡状态

    float GetBodySize(){ return m_fBodySize; }
    void  SetBodySize( float fBodySize ){ m_fBodySize = fBodySize; }
    
    void  SetMask( bool bMask ){ m_bMask = bMask; }
    BOOL  IsMask()             { return m_bMask; }

    bool  IsInMapArea(uint32 nMapID, float fX, float fY, float fDistance);

    void  SetCountry( int iCountry ){ m_iCountry = iCountry; }
    int   GetCountry( void ){ return m_iCountry; }

    void  SetForce( uint8 nValue ) { m_nForce = nValue; }
    uint8 GetForce() const { return m_nForce; }
    bool  HaveForce() const { return m_nForce != 0; }

    DWORD GetShowFlag(){ return m_dwShowFlag; }
    void  AddShowFlag( ENpcShowType flag ){ _SET_FLAG(m_dwShowFlag, flag); }

    void  SetLastMovingSpeed( float fMovingRate ){ m_fLastMovingSpeed = fMovingRate; }
    
    virtual long ProcessReliveModule( const ItemDefine::SItemSkill* pSkill, SAttackTarget* pTarget );        // 处理复活技能模块

    void  ResetDaoxingEffect();
    void  SetDaoxingEffect( uint16 nStatusID, uint32 nDurationTime );

	uint32 GetLastMapID_BeforeTPHJ()              { return m_dwLastMapID_BeforeTPHJ; }
	void   SetLastMapID_BeforeTPHJ( uint32 dwID ) { m_dwLastMapID_BeforeTPHJ = dwID; }
	float GetLastX_BeforeTPHJ()              { return m_fLastX_BeforeTPHJ; }
	void   SetLastX_BeforeTPHJ( float fx ) { m_fLastX_BeforeTPHJ = fx; }
	float GetLastY_BeforeTPHJ()              { return m_fLastY_BeforeTPHJ; }
	void   SetLastY_BeforeTPHJ( float fy ) { m_fLastY_BeforeTPHJ = fy; }
	BYTE GetReliveBuff(){return m_byReliveBuff;}
	void SetReliveBuff(BYTE buff){m_byReliveBuff = buff;}

	////////////////////////////////////////////////////////////////////////////////////////
	// 归属相关 by cloud
	virtual bool OnSetMonsterBelong(BaseCharacter * pTarget = NULL);	// 设置或者清除怪物的归属
	virtual void UpdateMonsterBeLong(BaseCharacter * pKiller = NULL){}	// 更新怪物的归属 最顶层去实现

	virtual void UpdatePlayerScore( GameObjectId stID, int iDamage ){}	// 记录攻击者的战绩信息 在结算接口中调用
	virtual void CheckClearAttackerScore(){}							// 检查无效的伤害得分
	virtual void ClearAttackerScoreById( GameObjectId nId ){}			// 清理指定的玩家
	virtual void ClearAllAttackerScore(){}								// 清理所有的玩家

	virtual GameObjectId GetBestAttacker(){return -1;}					// 谁是最厉害的攻击者
	virtual GameObjectId GetFirstValidAttacker(){return -1;}			// 得到第一个有效的攻击者

protected:
    virtual void ProcessRefreshEnmity( uint32 nCurrentTime ){}
    virtual uint8 CheckCanAttackResult( BaseCharacter* pTarget );

    // 发射技能处理
    void ProcessEmission();    

    // 行为状态
    void  AddFightFlag( EActionFlag flag );    
    void  ClearFightFlag( EActionFlag flag, bool bSendMessage = true );

    // 技能
    virtual uint32 ProcessNormalSkill ( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster, int nConformedTargetCount = 0 );
    virtual uint32 ProcessCaptureSkill( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster ){ return eFIGHT_NOFLAG; }
    virtual uint32 ProcessSuckFetchSkill( SAttackTarget* pTarget, const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster ){ return eFIGHT_NOFLAG; }
    virtual uint32 ProcessBreakOutSkill( const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster ){ return eFIGHT_NOFLAG; }
    virtual uint32 ProcessCallGraphicSkill( const ItemDefine::SItemSkill* pSkillConfig ){ return eFIGHT_NOFLAG; }
    virtual uint32 ProcessXPSkill       ( const ItemDefine::SItemSkill* pSkillConfig, BaseCharacter* pMaster ){ return eFIGHT_NOFLAG; }
    virtual uint32 ProcessPetActive     ( const ItemDefine::SItemSkill* pSkillConfig ){ return eFIGHT_NOFLAG; }

    virtual long ProcessAssaultModule      ( const ItemDefine::SItemSkill* pSkill ); // 处理冲锋技能模块
    virtual long ProcessAttackSpeed        ( const ItemDefine::SItemSkill* pSkill ); // 处理技能攻击速度

    virtual uint32 ProcessTeamRelive( const ItemDefine::SItemSkill* pSkill ) { return eFIGHT_NOFLAG; }
    virtual uint32 ProcessTeamFlyToHeader( const ItemDefine::SItemSkill* pSkill ) { return eFIGHT_NOFLAG; }

    // 状态行为
    void StatusActionIdle();                        // 空闲可控状态
    void StatusActionAttack();
    void StatusActionReadyToUseSpecialSkill();
    void StatusActionUseSpecialSkill();
    void StatusActionIntonate();
    void BeginHoldSkill();
    void StatusActionHoldSkill();    
    void StatusActionDieing();                      // 死亡状态时的处理
    void StatusActionDoAction();
    
    DWORD GetEmissionFlyTime( GameObjectId shTargetID ); // 得到飞行技能打到目标的时间
	bool IsGameBattleFigh(){return m_IsGameBattle;}
//////////////////////////////////////////////////////////////////////////
// 变量
public:
    friend class SkillTaskManager;
    friend class BuffStatusManager;

    BuffStatusManager    _buffManager;                  // 人物战斗状态。
    SkillTaskManager     _SkillTaskManager;             // 技能任务管理器
    CharacterTimeStatus  m_ExtendStatus;                // 扩展状态信息(主要用到战斗中的影响状态控制)
    
    SContinuousSkillData m_ContinuousSkill;

protected:    
    BaseCharacter*  m_pBelongKiller;                    // 这个单位的归属是谁 
    GameObjectId    m_nLockID;                          // 锁定的目标
	uint8			m_uchFightCamp;		                // 阵营
    int             m_iCountry;                         // 所属的国家
    uint8           m_nForce;                           // 所属的势力
    float           m_fBodySize;                        // 体型
    float           m_fWeaponAttackRange;               // 武器普通攻击范围
    int             m_iAttackHand;
    int             m_nNormalAttSkillId0;               // 右手
    int             m_nNormalAttSkillId1;               // 左手
    bool            m_bBeCSed;                          // 是否被暴击
    SEmission       m_Emission[MAXEMISSIONNUM];
    unsigned char   m_ucHaveEmission;                   // 是否有发射技能
    DWORD           m_dwShowFlag;                       // 显示标记,如是否会转向,是否有阴影等
    DWORD           m_dwFightFlag;                      // 战斗状态
    SRestoreTime    m_restoretime;
    bool            m_bDeadFlag;                        // 死亡标志
    uint8           _bodyStatus;                        // 当前所处的主状态 [上半身状态 大脑状态]
    uint8           _moveStatus;                        // 移动状态 [下半身状态 小脑状态]
    int             _bodystatusOld;;                    // 上一个状态
    BYTE            m_bySubAction;                      // 现在的动作
	 
    DWORD           m_dwLastMapID;                      // 玩家的上次场景ID
    DWORD           m_dwLastEctypeMapID;                // 玩家的被纠正前的地图ID
    bool            m_bMask;                            // 是否阻挡
    DWORD           m_dwLastRefreshCharDataTime;        // 记录上次调用RefreshCharData,的时间
    DWORD           m_dwLastRefreshStatusTime;          // 刷新时间
    BOOL            m_bIllusionChar;                    // 是否镜像角色
    int             m_nCompoundRateAddTemp;
    int             m_nIntensifyRateAddTemp;
    DWORD           m_dwStatusStartTime;                // 切换到该状态的开始时间
    int             m_nNextStatus;                      // 下一个状态，动作
    bool            m_bCanSwitchStage;                  // 判断可否切换,地图
    short           m_ustCauseStatusID;                 // 导致的状态ID
    short           m_stCauseStatusLevel;               // 导致的状态Level
    short           m_ustCauseStatusRate;               // 导致的状态机率    
    uint32          m_dwProcessLogicCostTime;           // 逻辑调用花费的时间
    float           m_fLastMovingSpeed;                 // 最后的移动速度

    SDaoxingEffect  m_DaoxingEffect;                    // 道行影响
    GameTimerEx     m_xRefeshEnmityTimer;               // 仇恨刷新定时器
	DWORD           m_dwLastMapID_BeforeTPHJ;                      // 玩家的进入太平幻境之前的地图ID
	float           m_fLastX_BeforeTPHJ;                      // 玩家的进入太平幻境之前的地图X
	float           m_fLastY_BeforeTPHJ;                      // 玩家的进入太平幻境之前的地图Y

	BYTE			m_byReliveBuff;								//玩家复活后随机奖励的buff

	bool			m_IsGameBattle;
};

//////////////////////////////////////////////////////////////////////////
// inline
inline void BaseCharacter::SetStatus( uint8 bodyStatus )
{
    _bodystatusOld = bodyStatus;
    _bodyStatus   = bodyStatus;
}

inline void BaseCharacter::SetMoveStatus( uint8 moveStatus )
{   
    _moveStatus = moveStatus;
}

inline void BaseCharacter::ApplyNextStatus()
{
    _bodyStatus = _bodystatusOld;;
    m_dwStatusStartTime = HQ_TimeGetTime();
}

inline bool BaseCharacter::IsCanBeAttackedObject()
{
    if ( IsPlayer() || IsMonster() || IsFightNpc())
    { return true; }

	//lyhtexiaoguai++
	if(IsEffectChar())
		return true;

    return false;
}

inline bool BaseCharacter::IsHaveHpObject()
{
    if ( IsPlayer() || IsFightNpc() )
    { return true; }

    if ( IsMonster() && !IsResourceMonster() )
    { return true; }

    return false;
}

inline bool BaseCharacter::IsResourceMonster()
{
    switch ( GetMonsterType() )
    {
    case eMT_Treasure:
    case eMT_Herb:
    case eMT_Mount:
    case eMT_Insect:
    case eMT_Mine:
    case eMT_Wood:
        return true;
        break;
    default:
        break;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////
// 函数
inline void GetOffsetByDir( int iDir,short &stXOff, short &stYOff )
{
    stXOff = 0;
    stYOff = 0;
    switch( iDir )
    {
    case DIR_0:
        stXOff = 1;
        break;
    case DIR_45:            
        stXOff = 1,stYOff = 1;
        break;
    case DIR_90:
        stYOff = 1;
        break;
    case DIR_135:
        stXOff = - 1,stYOff = 1;
        break;
    case DIR_180:            
        stXOff = - 1;
        break;
    case DIR_225:            
        stXOff = - 1,stYOff = - 1 ;
        break;
    case DIR_270:            
        stYOff = - 1;
        break;
    case DIR_315:
        stXOff = 1,stYOff = - 1;
        break;
    }
}

inline int GetDirByOffset( int dx, int dy )
{
    int nDir = DIR_0;
    if( dx > 0 && dy == 0 )
        nDir = DIR_0;
    else if( dx > 0 && dy < 0 )
        nDir = DIR_45;
    else if( dx == 0 && dy < 0 )
        nDir = DIR_90;
    else if( dx < 0 && dy < 0 )
        nDir = DIR_135;
    else if( dx < 0 && dy == 0 )
        nDir = DIR_180;
    else if( dx < 0 && dy > 0 )
        nDir = DIR_225;
    else if( dx == 0 && dy > 0 )
        nDir = DIR_270;
    else if( dx > 0 && dy > 0 )
        nDir = DIR_315;
    return nDir;
}

inline bool IsDistanceLess( int x1, int y1, int x2, int y2, int d )
{
    return ( abs( (x1)-(x2) ) < (d) && abs( (y1)-(y2) ) < (d) );
}

inline int CalcDistance( int x1, int y1, int x2, int y2 )
{
    return ( abs( (x1)-(x2) ) + abs( (y1)-(y2) ) );
}

#endif