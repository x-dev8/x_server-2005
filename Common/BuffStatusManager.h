/********************************************************************
    Filename:     BuffStatusManager.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_BUFFSTATUSMANAGER_H__
#define __COMMON_BUFFSTATUSMANAGER_H__

#pragma once

#include "ItemDetail.h"

class MountManager;

class BuffEvent
{
public:
    BuffEvent() : bHide(false), bXinFa(false) {}

public:
    virtual void OnEnterHide() {};
    virtual void OnXinFaUpdate() {};

public:
    bool bHide  ;     // 最后隐身状态
    bool bXinFa ;     // 心法影响状态
};

class BuffStatusManager
{
public:
    enum EStatusAnim
    {
        eStatusAnim_None = 0, // 没有状态动画
        eStatusAnim_Stun,     // 眩晕动画
        eStatusAnim_FallOver, // 摔倒动画
        eStatusAnim_Freeze,   // 冰冻动画
        eStatusAnim_Max,
    };

    //////////////////////////////////////////////////////////////////////////
    // 事件回调函数
    BuffEvent* pBuffEvent;
    void CallBuffEvent() ;
    //////////////////////////////////////////////////////////////////////////

public:
    // 初始化系列
    BuffStatusManager();
    virtual ~BuffStatusManager();    
    void CreateFromData(SCharBuff* pData, int num);
    void CreateFromData(BuffEvent* pBuffEvent, SCharBuff* pData, int num);
    void AddStatusFromData( DWORD stageId, SCharBuff* pData, int num,DWORD dwCurTime, bool bFirstEnterWorld = false);

    // 清除系列
    bool  ClearBuff( int16 index, bool needUpdate = true);                      // 清除单个作用的buff
    bool  ClearAllBuff();                                                       // 清除所有的buff
    void  ClearBuffChangedRecords();                                            // 清除所有的buff变动记录
    bool  ClearBuffByBuffIdLevel( int nStatusId,int nStatusLevel);              // 清除buff根据buffId和等级 
    bool  ClearBuffByBuffId     ( int StatusID );                               // 清除buff根据buffId
    bool  ClearBuffByMasterCharID( GameObjectId shCharID, bool IsClearDebuff = true); // 清除buff根据释放主人Id
    bool  ClearAllBuffByHaveAttack( bool bNeedUpdate = true );                  // 清除所有的有害状态
    bool  ClearBuffByType( bool bIsAvail, int nType );
    void  ClearBuffClearIdRecords();                                            // 清除 存清除bufferId的队列    
    void  ClearBuffWhenChangeMap();                                             // 清除当切换地图是需要去掉的Buff

    // 作用系列
    bool ApplyBuff( bool bStop, uint16 iStatusID, uint16 iStatusLevel, GameObjectId masterId, uint32 dwNowTime, bool bLastOne, uint32 dwDurationTime, uint32 dwMasterDbId, int eventType, int eventValue );       // 应用buff    
    bool AddBuff( int16 nPos, bool bStop, uint16 iStatusId, int iStatusLevel, GameObjectId masterId, uint32 dwNowTime, bool bLastOne, uint32 dwDurationTime, uint32 dwMasterDBID, int eventType, int eventValue); // 加入buff
    bool ApplyBuffsToChar( uint16 profession, SCharBaseAttr* pBase, SCharFightAttr* pFight ); // Buff数值作用到角色一、二级属性上

    void AddBuffIdToClearIdRecords( uint16 nID );                          // 添加一个ID到ClearStatusId队列
    void AddBuffToClearRecords( const SCharBuff& rBufferStatus );          // 添加一个Buff到Clear Record队列

    // 获取系列
    SCharBuff* GetBuff            ( int16 index );      // 得到在作用中的buff
    SCharBuff* GetBuffByStatusID  ( int16 nStatusID );  // 得到在作用中的buff
	bool IsBuffExist(int16 nStatusID);                  // StatusID对应的buff是否在作用
    SCharBuff* GetBuffAddress     ( int16 index );      // 得到buff队列地址指针
    SCharBuff* GetBuffClearRecord ( int16 index );      // 得到清除掉的buff
    bool       GetBuffChangeRecord( int16 index );      // 得到buff改变标识位

    int  GetClearIdArrayId(int nIndex);                 // 得到nIndex下标的StatusId
    int  GetBufferStatusCount() { return buffMaxCount;} // 得到Buff个数    
    int  GetEnableStatusNum()   { return iEnableStatusNum;}
    int  HaveChangeChangeMonsterIDBuff();               // 得到变身状态的个数
    int  GetBufferStatusIndexById( int statusId );      // 得到在作用中的buff下标

    // 更新系列
    bool UpdateDurationTime();                          // 更新要清除的buffer 调用他的时间频率是一秒
    bool UpdateBufferOnEnterStage ( uint32 stageId  );  // 更新buffer进入场景的时候
    bool UpdateOnBeAttack( const ItemDefine::SItemSkill* pSkillConfig ); // // 受击回调Update 清除（被攻击时要清除的状态）
    bool UpdateOnBackAttack();  // 背击回调Update 会引起清除(被背击时候要清楚的状态)
    bool UpdateOnMove();        // 移动回调Update 会引起移动清除(移动时候要)
    bool UpdateOnDead();        // 死亡回调Update 会引起Buff的减少清除
    bool UpdateCounterValue();  // 回调Update 会引起Buff的减少清除
    bool UpdateOnAttack();      // 攻击回调Update 清除buff
    void UpdateEffect();        // Update Buffer 所影响的变量

    // Log系列
    void  LogAndClearBufferClearIdArray();
    void  LogStatus( SCharBuff* pData = NULL);
    void  Log( int nFailLocation, int buffId, int buffLevel );
    
    // 获取属性系列
    bool  IsHaveStatus(int iStatus);                                 // 判定目标是否有状态   
    bool  IsHaveNegativeStatus( uint8 nNegativeType );               // 判定目标是否有负面状态 
    bool  IsRandRun()              { return bIsRandRun; }            // 随机乱跑..(不攻击)    
    //int   GetChangeSight()         { return iChangeSight;}         // 改变视线 如果返回 < 0 表示不改变视野
    int   GetCurStatusAnim()       { return nCurStatusAnim; }        // 获取当前的状态动画    
    //bool  IsCanBeFindByMonster()   { return bCanBeFindByMonster;}    // 不能发现，玩家    
    //bool  IsAttackByMonsterFirst() { return bAttackByMonsterFirst; } // 判断最优先级别被怪物攻击
    bool  IsCanMove()              { return bMoveFlag; }             // 判断可否移动
    bool  IsCanUsePhysicsSkill()   { return bUsePhysicsSkillFlag;}   // 可否使用武力技能    
    bool  IsCanUseMagicSkill()     { return bUseMagicSkillFlag; }    // 可否使用法术技能
    bool  IsCanBePhyAttack()       { return bIsBePhyAttack; }
    bool  IsCanBeMagAttack()       { return bIsBeMagAttack; }
    bool  IsCanUseItem()           { return bUseItemFlag; }          // 可否使用道具
    bool  IsHide()                 { return bHide; }                 // 是否隐身  
    bool  IsInvincible()           { return bInvincible; }           // 是否无敌
	bool  IsBuoy()                 { return bBuoy; }                 // 是否浮空
	bool  IsCanRide()			   { return bCanRide;}				 // 可否骑马

    uint8 GetDamageToHp() { return damagetohp; } // 伤害转为血 同时不够伤害
    void  SetCanMove( bool bCanMove ){ bMoveFlag = bCanMove; }
    
    //bool  IsIgnoreHedge()  { return bHedgeNull; } // 是否忽视回避    
    //bool  IsWeaponFormula(){ return bIsWeaponFormula; }        // 是否算上武器伤害    
    bool  IsCanUseSkill( ItemDefine::SItemSkill* pSkill );     // 战斗状态中判断可否使用某个技能
    bool  IsCanUseSkill( uint16 iSkillID, uint16 iSkillLevel);  // 战斗状态中判断可否使用某个技能
    bool  IsClearStatusInAttack()     { return bClearStatusInAttack; }  // 判断受到伤害的时候是否需要清除状态
    float GetDamageChange2MpRatioPer(){ return fDamage2MpRatioPer;}     // 取得伤害的转换为mp的百分率
    int   GetDamageChange2MpRatio();

    float GetDamageReflectedRatio()   { return fDamageReflectRatio; }     // 伤害反弹比例
    uint8 GetDamageReflectProability(){ return nDamageReflectProability;} // 伤害反弹几率

    int   GetDamageChengedRate();                                  // 伤害减轻
    float GetDamageChengedRatePer();                               // 伤害减轻        
    
    //int   GetToPositonRate();  // 中毒的机率    
    //int   GetToPositonLevel(); // 让目标中毒的等级
    
    float GetSuckHpRate()       { return fSuckHpRate;        } // 吸血的比例
    int   GetSuckHpValue()      { return nSuckHpValue;       } // 吸血的值
    uint8 GetSuckHpProbability(){ return nSuckHpProbability; } // 吸血的几率

    //float GetMPStoneRate(){ return fMPStolenRate;}
    //int   GetMPStoneVal(){ return iMPStolenVal; } // 偷MP的
    int   GetDamageMp();     // MP伤害    
    
    bool  IsAttackClearStatus(){ return bAttackClearStatus; } //判断攻击时候是否需要清除状态
    //short GetMagicShieldKid();
    //short GetPerDamageNeedMp();

    int   GetAddBaseAttr    ( int i ) { return nAddBaseAttr[i];     }
    int   GetAddBaseAttrPer ( int i ) { return nAddBaseAttrPer[i];  }

    //伤害吸收
    float GetSuckDamgePer();
    short GetSuckDamgeMax() { return stSuckMax;} // 吸收伤害最大值
    void  SetSuckDamgeMax(int nValue) { stSuckMax = nValue; }
    void  ClearSuckDamage();

    //float GetIncreaseMp(); //药水效力增加
    //float GetIncreaseHp();

    float GetActionTimeMod();

    //伤害免疫
    short GetHurtImmunity()  { return hurtImmunity; }
    void  SetHurtImmunity(int nValue) { hurtImmunity = nValue; }

    //short GetChangedSkill_Hurt( int i )
    //{
    //    if( i < eElement_Max && i > 0)
    //    { return stChangedSkill_Hurt[i]; }
    //    return 0;
    //}

    //short GetChangedSkill_HurtPer( int i )
    //{
    //    if( i < eElement_Max && i > 0)
    //    { return stChangedSkill_HurtPer[i]; }
    //    return 0;
    //}

    //short GetChangedPhy_Hurt()    { return stChangedPhy_Hurt; }
    //short GetChangedPhy_HurtPer() { return stChangedPhy_HurtPer;}

    void  SetBeCriticaledBufferId(short stBufferID)       { stAddBufferID = stBufferID;}
    void  SetBeCriticaledBufferLevel(short stBufferLevel) { stAddBufferLevel = stBufferLevel;}
    short GetBeCriticaledBufferId()                       { return stAddBufferID;}
    short GetBeCriticaledBuffedLevel()                    { return stAddBufferLevel;}

    bool  UpdateStatusIsInCriticaled( bool bIsBeCSed = false);
    bool  IsBeCriticaledNeedAddBuffer() { return bCsedAddBuffer; } // 是否被暴击的时候可以加buffer

    bool  CheckTargetIsHaveAddBufferFlag(float fAttackerHpPer);
    bool  CheckIsAddDeBuffer(){ return bAddDeBuffer;}

    void  SetDeBufferID(short stDeBufferID){stAddDeBufferID = stDeBufferID;}
    void  SetDeBufferLevel(short stDeBufferLevel){stAddDeBufferLevel = stDeBufferLevel;}
    short GetDeBufferID(){return stAddDeBufferID;}
    short GetDeBufferLevel(){return stAddDeBufferLevel;}

    float GetExpAddMul()   {  return fExpMulAdd + fExpMulAddByEquip; }
    
    void SetExpMulAddByEquip(uint16 expPer) 
    {
        fExpMulAddByEquip = 0.0f;
        fExpMulAddByEquip += static_cast<float>( expPer * DEF_PERCENT );
    }

    float GetSkillExpAddMul() { return fSkillExpMulAdd;  }
    //float GetAddIntonateRate(){ return fAddIntonateRate; }    
    //short GetCompoundRate()   { return stComposeOdds;    }
    //short GetIntensifyRate()  { return stIntensifyOdds;  }
    //float GetPkValueMulAdd()  { return fPkvalueMulAdd;        }
    //bool  IsCalcDailyPkValue(){ return bNeedCalcDailyPkValue; }
    //bool  IsUnControlRandRun(){ return bIsRandRun;            }
    bool  IsPetSupport(){return bIsPetSupport;}

    bool  IsHaveBackAttackDispelBuff() { return _nBackAttackDispelBuffCount > 0;}
    bool  IsHaveMoveDispelBuff()       { return _nMoveDispelBuffCount > 0; }
          
    void  SetCharName( const char* szName ){  _strCharacterName = szName; }
    float GetStatusLimitRatio( unsigned char ucType);

    void SetNextNotIntonate( bool bNextNotIntonate) { _bNextNotIntonate = bNextNotIntonate; }
    bool GetNextNotIntonate() { return _bNextNotIntonate; }

    void SetNextNotIntonateNum( int8 Num) { nNextNotIntonateNum = Num; }
    int8 GetNextNotIntonateNum() { return nNextNotIntonateNum; }

    float GetTimeExpMul()        { return _timeExpMul; }
    bool  IsDisableCallGraphic() { return _bDisableCallGraphic; }

    bool  IfConsumeEnergy() { return ifConsumeEnergy; }

    uint16 GetChangeSkillId(int index) { return changeSkillIds[index]; }
    uint32 GetChangeSkillTime(int index) { return changeSkillTimes[index]; }

    //int32  GetChangeActivityMax() { return changeActivityMax; }
    //float  GetActivityMul() { return activityMul; }

    //uint16 GetReduceTax() { return reduceTax; }
    uint16 GetDeathDurabilityPer() { return deathDurabilityPer; }
    uint16 GetDeathMountHPDropPer() { return deathMountHPDropPer; }

    int    GetAddCatchPetRate()  { return addCatchPetRate; }

    int32  GetAddMoney () { return addMoney; } 
    int32  GetAddReputation () { return addReputation; }
    int32  GetAddExploit () { return addExploit; }     
    int32  GetAddHonour  () { return addHonour;  }     
    int32  GetAddMasterValue () { return addMasterValue; } 
    int32  GetAddBattleScore () { return addBattleScore; } 
    float  GetReputationMul  () { return reputationMul ; } 
    float  GetExploitMul     () { return exploitMul; } 
    float  GetHonourMul      () { return honourMul;  } 
    float  GetMasterValueMul () { return masterValueMul; } 
    float  GetBattleScoreMul () { return battleScoreMul; } 

	uint16 GetBeDamagePerHPMax  () { return BeDamagePerHpMax; }
    //int16  GetAddMountBaseAttr(int nWitch)    {  return nAddMountBaseAttr[nWitch]; }
    //int16  GetAddMountBaseAttrPer(int nWitch) {  return nAddMountBaseAttrPer[nWitch]; }

    //int32  GetAddHonourLimit  () { return addHonourLimit;  } 
	bool   GetIsCanGetHonour(){return IsCanGetHonour;}
	bool   GetIsCanBeGetHonour(){return IsCanBeGetHonour;}
protected:
    void OnBuffHaveChanged( uint16 index );

private:
    SCharBuff* m_pstBodyStatus;                       // 人物身上能有的状态,记录数据
    SCharBuff  m_ClearBodyStatus[BodyStatusType_Max]; // 人物身上清除掉的状态,记录数据 用于清除仇恨逻辑使用
    uint16     m_nStatusClear   [BodyStatusType_Max]; // 被清除的状态Id
    bool       _buffChangeRecord[BodyStatusType_Max]; // 状态被修正的位置标志

    int   iEnableStatusNum;       // 实际的buffer状态的数量
    uint8 buffMaxCount;           // buff的最大数量

    bool  bHide;                  // 是否隐身
	bool  bCanRide;				  // 可否骑马
    bool  bMoveFlag;              // 可否移动
    bool  bUsePhysicsSkillFlag;   // 可否使用技能
    bool  bUseMagicSkillFlag;     // 可否使用技能
    bool  bIsBePhyAttack    ;     // 可否被物理攻击
    bool  bIsBeMagAttack    ;     // 可否被魔法攻击
    bool  bUseItemFlag;           // 可否使用道具
    bool  bCanBeFindByMonster;    // 判断可否被怪物发现
    bool  bAttackByMonsterFirst;  // 判断最优先级别被怪物攻击
    bool  bClearStatusInAttack;   // 判断在受到伤害的时候是否解除状态
    bool  bAttackClearStatus;     // 判断在攻击的时候是否解除状态
	bool  bBuoy;                  // 是否浮空
                                   
    int   iDamage2MpRatio;        // 物理伤害到mp
    float fDamage2MpRatioPer;     // 伤害到mp的转换比例
                                   
    int   iDamageChengedRate;     // 伤害减轻

    float fDamageReflectRatio;    // 伤害反弹比例
    uint8 nDamageReflectProability; // 伤害反弹几率
                                   
    float fDamageChengedRatePer;  // 伤害减轻 按%

    float fSuckHpRate;            // 吸血比例
    int   nSuckHpValue;           // 吸血值
    uint8 nSuckHpProbability;     // 吸血几率

    float fMPStolenRate;
    int   iMPStolenVal;

    int   iPhysicItemAttMinTemp;  // 武器攻击BUFF
    int   iPhysicItemAttMaxTemp;  //

    bool  bIsWeaponFormula;       //是否算上武器的伤害
    bool  bHedgeNull;             //是否忽视回避
    short stStatusFree;                         //状态免疫
    short stChangedSkill_Hurt[eElement_Max];    // 技能伤害    
    short stChangedSkill_HurtPer[eElement_Max]; // 技能伤害%

    // Phy Huge
    short stChangedPhy_Hurt;
    short stChangedPhy_HurtPer;
    int   iDamageMp;            // 伤害为直接扣除MP
    short stMagicShieldKid;     // 魔法盾吸收伤害类型
    float fSuckPer;             // 吸收伤害

	short stSuckBuffMax;		// 当前BUFF的伤害值吸收最大值
    short stSuckMax;            // 吸收伤害值
    //short stPerDamageNeedMp;    // 每点伤害消耗的MP
    short hurtImmunity;         // 伤害免疫次数

    //活力上限
    //int32   changeActivityMax;    //改变活力上限
    //float   activityMul      ;    //活力恢复倍率

    //药水效力增加
    //float fMpIncreasePer;
    //float fHpIncreasePer;

    float fActionTimeChangMod; //动画播放时间改变系数

    //被暴击增加的状态
    short stAddBufferID;
    short stAddBufferLevel;

    //攻击者增加的状态
    short stAddDeBufferID;
    short stAddDeBufferLevel;

    bool bAddDeBuffer;
    bool bCsedAddBuffer;

    float fExpMulAdd;        // 增加经验时候的经验加成 状态引起的
    float fExpMulAddByEquip; // 增加经验时候的经验加成 装备引起的

    float fSkillExpMulAdd; // 增加技能经验时候的技能经验加成
    
    int   nCurStatusAnim;    // 当前状态动画(有优先级)
    //float fAddIntonateRate;
    int   nAddBaseAttr[EBaseAttr_MaxSize];      // 一级属性加成
    int   nAddBaseAttrPer[EBaseAttr_MaxSize];   // 一级属性加成百分比

    //int   nAddMountBaseAttr[EBaseAttr_MaxSize];      // 坐骑一级属性加成
    //int   nAddMountBaseAttrPer[EBaseAttr_MaxSize];   // 坐骑一级属性加成百分比

    //short stComposeOdds;
    //short stIntensifyOdds;

    //float fPkvalueMulAdd;

    //bool bNeedCalcDailyPkValue;

    bool bIsRandRun;                  // 是否随机乱跑
    bool bIsPetSupport;               // 是都宠物承受伤害
    int  _nBackAttackDispelBuffCount; // 受到背击时候解除的buff个数
    int  _nMoveDispelBuffCount;       // 移动时候解除的buff个数

    int nChangeMonsterID;             // 变身怪物ID

    float _fStatusLimitResistRatio[SNT_MaxCount];

    bool  _bNextNotIntonate;        // 下一次技能是否瞬发
    int8  nNextNotIntonateNum;      // 瞬发次数
    
    std::string _strCharacterName;  // 角色名字
    float _timeExpMul;              // 时间经验加成
    bool  bInvincible;              // 无敌状态
    uint8 damagetohp;               // 伤害转换成Hp同时不掉血
    
    bool  _bDisableCallGraphic;     // 是否调用验证码
    bool ifConsumeEnergy;           // 是否不消耗能量MP

    uint16 changeSkillIds[ItemDefine::SItemStatus::ECD_ChangeSkillMaxSize]      ;   //改变冷却时间的技能
    uint32 changeSkillTimes[ItemDefine::SItemStatus::ECD_ChangeSkillMaxSize]    ;   //改变技能冷却时间

    //uint16 reduceTax;               //降低税率 
    uint16 deathDurabilityPer;      //死亡装备耐久度降低 
    uint16 deathMountHPDropPer;     //死亡坐骑生命减少  

    int16  addCatchPetRate;         //增加宠物捕捉几率

    int32     addMoney                ;   // 增加金钱
    int32     addReputation           ;   // 增加声望
    int32     addExploit              ;   // 增加功勋
    int32     addHonour               ;   // 增加荣誉
    int32     addMasterValue          ;   // 增加威望
    int32     addBattleScore          ;   // 增加战场积分
    float     reputationMul           ;   // 声望倍数
    float     exploitMul              ;   // 功勋倍数
    float     honourMul               ;   // 荣誉倍数
    float     masterValueMul          ;   // 威望倍数
    float     battleScoreMul          ;   // 战场积分倍数

    int32     addHonourLimit          ;   // 增加荣誉上限

	uint16    BeDamagePerHpMax			  ;   // 被伤害后不管多少值,每次都只掉百分比生命

	bool	  IsCanGetHonour;
	bool	  IsCanBeGetHonour;
};

//////////////////////////////////////////////////////////////////////////
// inline
inline void BuffStatusManager::AddBuffIdToClearIdRecords( uint16  nID)
{
    for (int nLoop = 0; nLoop <BodyStatusType_Max; ++nLoop)
    {
        if (m_nStatusClear[nLoop] <= 0)
        {
            m_nStatusClear[nLoop] = nID;
            return;
        }
    }
}

inline void BuffStatusManager::AddBuffToClearRecords( const SCharBuff& rBufferStatus )
{
    for (int nLoop = 0; nLoop <BodyStatusType_Max; ++nLoop)
    {
        if (m_ClearBodyStatus[nLoop].StatusID <= 0 && m_ClearBodyStatus[nLoop].iLevel<= 0)
        {
            m_ClearBodyStatus[nLoop] = rBufferStatus;
            return;
        }
    }
}

inline int BuffStatusManager::GetClearIdArrayId(int nIndex)
{
    if (nIndex < 0||nIndex >= BodyStatusType_Max)
        return 0;
    return m_nStatusClear[nIndex];
}

inline void BuffStatusManager::ClearBuffWhenChangeMap()
{
    for ( int nLoop = 0; nLoop < buffMaxCount; ++nLoop )
    {// 状态ID > 0 && 存储类型是 ESRT_OnlyInMap，则需要清除
        if ( m_pstBodyStatus[nLoop].StatusID > InvalidLogicNumber && m_pstBodyStatus[nLoop].restoreType == ItemDefine::ESRT_OnlyInMap )
        {
            ClearBuff( nLoop, true );
        }
    }
}

inline void BuffStatusManager::ClearBuffClearIdRecords()
{
    for (int np = 0 ; np < BodyStatusType_Max; ++np)
    {
        m_nStatusClear[np] = 0;
    }
}

inline bool BuffStatusManager::IsBuffExist(int16 nStatusID)
{
	for (int i = 0; i < buffMaxCount; ++i)
	{
		if (m_pstBodyStatus[i].StatusID == nStatusID && m_pstBodyStatus[i].StatusID > 0 && m_pstBodyStatus[i].iLevel > 0)
		{
			return true;
		}
	}
	return false;
}

inline SCharBuff* BuffStatusManager::GetBuff( int16 index)
{
    if (index <0 || index >=buffMaxCount)
    { return NULL; }

    if ( m_pstBodyStatus[index].StatusID<=0 || m_pstBodyStatus[index].iLevel<=0)
    { return NULL; }
    
    return &m_pstBodyStatus[index];
}

inline SCharBuff* BuffStatusManager::GetBuffByStatusID( int16 nStatusID )
{
    for (int i = 0; i < buffMaxCount; ++i)
    {
        if (m_pstBodyStatus[i].StatusID == nStatusID && m_pstBodyStatus[i].StatusID > 0 && m_pstBodyStatus[i].iLevel > 0)
        {
            return &m_pstBodyStatus[i];
        }
    }

    return NULL;
}


inline SCharBuff* BuffStatusManager::GetBuffAddress( int16 index)
{
    if (index <0 || index >=buffMaxCount)
    { return NULL; }
    
    return &m_pstBodyStatus[index];
}

inline SCharBuff* BuffStatusManager::GetBuffClearRecord( int16 index )
{
    if ( index<0 || index >=BodyStatusType_Max)
    { return NULL; }

    if ( m_ClearBodyStatus[index].StatusID <= 0 || m_ClearBodyStatus[index].iLevel <= 0)
    { return NULL; }

    return &m_ClearBodyStatus[index];
}

inline bool BuffStatusManager::GetBuffChangeRecord( int16 index )
{
    if ( index<0 || index >=BodyStatusType_Max)
    { return NULL; }

    return _buffChangeRecord[index];
}

inline float BuffStatusManager::GetStatusLimitRatio( unsigned char ucType)
{
    if ( ucType > SNT_TORPID )
        return 0.0f;

    return _fStatusLimitResistRatio[ ucType ];
}

#endif // __COMMON_BUFFSTATUSMANAGER_H__
