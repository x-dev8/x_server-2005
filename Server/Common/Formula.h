/********************************************************************
    Filename:     Formula.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_FORMULA_H__
#define __GAMESERVER_FORMULA_H__

#pragma once

#include "MeRTLibsServer.h"
#include "ItemDetail.h"

class BaseCharacter;

class CFormula
{
public:
    enum eAttackHand
    {
        e_Rhand = HT_RightHand,
        e_Lhand = HT_LeftHand,
        e_Max
    };
    
    enum
    { //聚气
        e_Exact = 0,
        e_Attack,
        e_BeAttack,
        e_PowerMax
    };

    enum eDaoxingEffect
    {
        e_None   = 0,
        e_Resist = 1,    // 道法抵抗
        e_Stifle = 2,    // 道法压制
    };
    
    struct SResult
    { // 最后的结算结果表示结构
        SResult()
        { 
            memset( this, 0, sizeof(SResult) );
            memset( m_nDispelNegativeType, -1, sizeof(m_nDispelNegativeType));
        }
        void Reset(); // 重置数据

        short m_stBalanceType;                                  // 结算类型

        short m_ustMeAddStatusID[ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize];    // 附加状态编号(给我的)
        short m_ustMeAddStatusLevel[ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize]; // 附加状态等级(给我的)

        short m_ustDstAddStatusID[ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize];   // 附加状态编号(给对方的)
        short m_ustDstAddStatusLevel[ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize];// 附加状态等级(给对方的)

        short m_ustMeAddStatusIDFromEquip    [ EEquipPartType_MaxEquitPart ]; // 附加装备状态编号(给我的) 
        short m_ustMeAddStatusLevelFromEquip [ EEquipPartType_MaxEquitPart ]; // 附加装备状态等级(给我的)
        short m_ustDstAddStatusIDFromEquip   [ EEquipPartType_MaxEquitPart ]; // 附加装备状态编号(给对方的)
        short m_ustDstAddStatusLevelFromEquip[ EEquipPartType_MaxEquitPart ]; // 附加装备状态等级(给对方的)

        DWORD m_dwSubComboStatus;                               // 解除状态位置
        DWORD m_dwClearStatus[ItemDefine::CLEAR_MAX_STATUS];   // 解除状态ID

        bool  m_bMiss;                                          // 攻击成功失败标志
        int   m_iDamage;                                        // HP伤害值
        int   m_nDamageMp;                                      // MP伤害
        int   m_iHPRestore;                                     // HP的恢复值        
        int   m_iMPRestore;                                     // MP的恢复
        int   m_iXPRestore;                                     // XP的恢复值
        int   m_nExtraHp  ;                                     // 瞬间吸收HP
        int   m_nShieldHp ;                                     // 盾牌吸收HP
        
        bool  m_bBackHit    ;                                   // 是否背击
        bool  m_bCriticalHit;                                   // 是否暴击
        bool  m_bRelive     ;                                   // 是否复活
        int8  m_nDaoxingEffect;                                 // 道行影响 抵抗 或者 压制
        bool  m_bHurtImmunity;                                  // 伤害免疫 折光
        
        int   m_nBackAttackDamage;                              // 背击伤害
        short m_stBackStrikeAddMeStatus;                        // 背击给我的状态
        short m_stBackStrikeAddMeStatusLevel;
        short m_stBackStrikeAddDstStatus;                       // 背击给对方的状态
        short m_stBackStrikeAddDstStatusLevel;

        int8  m_nDispelNegativeType[ItemDefine::SItemSkill::EItemSkillConst_DispelStatusMaxSize];  // 解除负面状态类型
    };

public:
    CFormula();

    // 设置操作对象接口
    void  Reset();                                 // 重置结算器
    void  ResetAttacker();                         // 重置攻击者
    void  ResetTarget();                           // 重置受攻击者组
    void  SetAttacker( BaseCharacter* pAttacker ); // 设置攻击者
    bool  AddTarget  ( BaseCharacter* pTarget );     // 加入一个受攻击者
    void  SetSkill   ( ItemDefine::SItemSkill* pSkill) { m_pSkill = pSkill; }
    bool  IsAttackable();                          // 是否处于可攻击的设置状态    
    void  BalanceAttackHero( int iAttackHand );
    
    int  CalcReliveRestoreHP( int nWhich );  // 计算复活后恢复HP的数值

    // 有关状态
    void SetStatusTarget( BaseCharacter *pTarget ){ m_pStatusTarget = pTarget; }
    void SetStatusSrc( BaseCharacter *pSrc)       { m_pStatusSrc = pSrc;       }
    void SetStatusBuff( SCharBuff* pBuff)       { m_pBuff = pBuff;       }
    void SetStatusInfo( unsigned short ustStatusID, unsigned short ustStatusLevel );

    void BalanceStatusHero();               // 状态伤害结算
    void CalcStatusBalanceTypeNone();       // 状态伤害类型公式
    void CalcStatusBalanceTypeRestore();    // 状态回复类型公式
    
    // 获得状态的结算结果
    SResult* GetTargetStatusResult(){ return &m_TargetStatusResult; }
    SResult* GetSrcStatusResult()   { return &m_SrcStatusResult;    }

    // 获得结算结果
    SResult* GetTargetLastResult(int nWhich);
    SResult* GetSrcLastResult(int nWhich);

    // 获得攻击目标指针
    BaseCharacter* GetTarget( int nWhich );
    int  GetTargetNum(){ return m_iTotalTarget; }
    void InitPlayerAttackerAttr( int iStrength,int iMagic,short stMinBonusDamageRange,short stMaxBonusDamageRange );

protected:
    bool InitBalanceDamageData( SResult*& pResult, SResult*& pSrcResult, int nWhich ); // 初始化结算数据
    bool CheckingStatus ( int nTargetIndex );
    void BalanceMissHero( int nTargetIndex );                                          // 攻击失败结算
    void BalanceDamageHero( int nWhich,int iAttackHand );                              // 伤害结算
    void BalanceRestoreHero( int nWhich );                                             // 回复结算
    void BalanceAddStatusHero( SResult* pResult, BaseCharacter* pTarget );             // 附加状态结算
    void BalanceAddDstStatusHero( SResult* pResult, BaseCharacter* pTarget, uint8 index );
    
    void CallCustomBanalanceHero    ( SResult*& pResult, SResult*& pSrcResult, int nWhich ,int iAttackHand);    // 调用自定义公式
    void CallByBalanceTypeNoneHero  ( SResult* pResult, SResult* pSrcResult, int nWhich );                      // 被结算公式调用 没有伤害任何结算
    void CallByBalanceTypePhyDamageHero ( SResult* pResult, SResult* pSrcResult, int nWhich,int iAttackHand);   // 被结算公式调用 物理伤害结算
    void CallByBalanceTypeMagDamageHero ( SResult* pResult, SResult* pSrcResult, int nWhich );                  // 被结算公式调用 魔法伤害结算
    void CallByBalanceTypeBothDamageHero( SResult* pResult, SResult* pSrcResult, int nWhich,int iAttackHand);   // 被结算公式调用 物理魔法伤害结算
    void CallByBalanceTypeRestoreHpMp   ( SResult* pResult, int nWhich  );                                      // 被结算公式调用 回HP MP结算
    void CallByBalanceTypeRelive        ( SResult* pResult, int nWhich );                                       // 被结算公式调用 复活结算

    //void BalanceAddStatus( SResult* pResult, BaseCharacter* pTarget, BaseCharacter* pSrc = NULL );           // 附加状态结算

    int  CalcNormalDamage( uint8 damageType, int nWhich, SResult* pResult, SResult* pSrcResult );   // 计算普通伤害
    int  CalcAdditionalDamage (int nWhich, SResult* pResult, SResult* pSrcResult );                 // 计算附加伤害
    bool TryBackStrikeDamage  (int nWhich, SResult* pResult, SResult* pSrcResult );                 // 计算背击
    bool TryCriticalDamageHero(int nWhich, SResult* pResult, SResult* pSrcResult );                 // 计算暴击

    void CalcTargetSuckDamage ( BaseCharacter* pDst, SResult* pResult );   
    int  CalcSuckHp( int iDamage );
    int  CalcDamageReflect( BaseCharacter* pTarget, int iDamage );
    bool IsHaveDamageToHp( BaseCharacter* pTarget );
    int  CalcDamageToHp( BaseCharacter* pTarget, int iDamage );                                     // 计算伤害转移

	void CalcBeDamagePerHP(BaseCharacter* pDst, SResult* pResult );									//受到伤害扣住百分比计算
public:
    //状态的作用对象,和状态的相关信息
    BaseCharacter* m_pStatusTarget;
    BaseCharacter* m_pStatusSrc;
    
    SCharBuff* m_pBuff;
    ItemDefine::SItemStatus* m_pStatus;
    unsigned short            m_ustTargetStatusID;
    unsigned short            m_ustTargetStatusLevel;    
    SResult m_TargetStatusResult;                     // 状态的计算结果..被释法者的数据，就是攻击目标
    SResult m_SrcStatusResult;                        //对释法者的影响数据,就是技能的释放者，攻击者
    
private:
    BaseCharacter* m_pAttacker;                            // 攻击者
    int            m_iAttackerStrength;                    // 攻击者的力量
    int            m_iAttackerMagic;                       // 攻击者的魔力
    short          m_stMinBonusDamageRange;
    short          m_stMaxBonusDamageRange;
    BaseCharacter* m_pTarget[dr_MaxAttackTarget];          // 攻击目标组    
    int            m_iTotalTarget;                         // 攻击目标数    
    SResult        m_TargetLastResult[dr_MaxAttackTarget]; // 攻击结算结果
    SResult        m_SrcLastResult[dr_MaxAttackTarget];    // 
    ItemDefine::SItemSkill* m_pSkill;                     // 当前攻击技能
};

//////////////////////////////////////////////////////////////////////////
// inline
inline CFormula::SResult* CFormula::GetTargetLastResult( int nWhich )
{
    if( nWhich < 0 || nWhich >= dr_MaxAttackTarget )
        return NULL;
    return &m_TargetLastResult[nWhich];
}

inline CFormula::SResult* CFormula::GetSrcLastResult(int nWhich)
{
    if( nWhich < 0 || nWhich >= dr_MaxAttackTarget )
        return NULL;
    return &m_SrcLastResult[nWhich];
}

inline BaseCharacter* CFormula::GetTarget( int nWhich ) 
{
    if(nWhich < 0 || nWhich>=m_iTotalTarget)
    { return NULL; }
    return m_pTarget[nWhich];
}

#endif // __GAMESERVER_FORMULA_H__
