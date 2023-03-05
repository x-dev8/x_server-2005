/********************************************************************************************************************************
                FileName:CharAttrModulues.h
                Author  :eliteYang
                Mail    :elite_yang@163.com
                Desc    :一级属性对二级属性的影响系数，法攻物攻的伤害控制系数，总伤害的控制系数，最终伤害的控制系数
*********************************************************************************************************************************/
#ifndef __CHARATTRMODULUS_CONFIG_H__
#define __CHARATTRMODULUS_CONFIG_H__

#pragma once

#include <map>
#include "MeRTLibs.h"

#define theCharAttrModulusConfig CharAttrModulusConfig::Instance()

class CharAttrModulusConfig
{
public:
    enum ECharAttrModulus
    {
        EC_HpMode            = 0,	// HP系数
        EC_MpMode               ,	// MP系数
        EC_MoveSpeedMode        ,	// 移动速度系数
        EC_HpRestoreMode        ,	// HP恢复系数
        EC_MpRestoreMode        ,	// MP恢复系数
        EC_ExactMode            ,	// 命中系数
        EC_DodgeMode            ,	// 闪避系数
        EC_CriticalMode         ,	// 暴击率系数
        EC_TenacityMode         ,	// 韧性系数
        EC_CriticalIntensityMode,	// 暴击伤害系数
        EC_DerateCriIntenMode   ,   // 减免暴击伤害系数
        EC_AtkSpeedMode         ,	// 攻击速度系数
        EC_IntonateMode         ,   // 吟唱时间系数
        EC_BackMode             ,   // 背击系数
        EC_PhyAtkMode           ,   // 物攻系数
        EC_MagicAtkMode         ,	// 法攻系数
        EC_PhyDefendMode        ,   // 物防系数
        EC_MagicDefendMode      ,   // 法防系数

        EC_MAX                  ,   // 系数个数最大值
    };
    struct AttrModulus 
    {
        AttrModulus()
        { memset( this, 0, sizeof( AttrModulus ) ); }

        unsigned short nBaseAttrId; // 一级属性ID
        float Modulus[ EC_MAX ];
    };

    typedef std::map< unsigned short, AttrModulus > AttrModulusContainer;
    typedef AttrModulusContainer::iterator ItrAttrModulusContainer;

    struct AttrAttackModulus 
    {
        AttrAttackModulus()
        { memset( this, 0, sizeof( AttrAttackModulus ) ); }

        unsigned short nType;       // 属性类型
        float fAttackModulus;
        int nAttackFixPer;
    };

    typedef std::map< unsigned short, AttrAttackModulus > AttrAttackModlusContainer;
    typedef AttrAttackModlusContainer::iterator ItrAttrAttackModulusContainer;

    struct ProfessionModulus 
    {
        unsigned short nProfessionId;           // 职业ID
        AttrModulusContainer mapAttrModulus;    // 一级属性对二级属性的影响系数
        float phyDamageModulus;                 // 物理伤害控制系数
        float magicDamageModulus;               // 法术伤害控制系数
        AttrAttackModlusContainer mapAttrAttackModulus; // 属性伤害系数和伤害修正百分比

        AttrModulus* GetAttrModulusById( unsigned short nId );      // 通过一级属性类型获得一级属性影响二级属性的系数
        AttrAttackModulus* GetAttrAttackModulusByType( unsigned short nType );  // 获得属性攻击系数和属性伤害修正百分比
    };

    typedef std::map< unsigned short, ProfessionModulus > ProfessionModulusContainer;
    typedef ProfessionModulusContainer::iterator ItrProfessionModulusContainer;

    ~CharAttrModulusConfig();
    static CharAttrModulusConfig& Instance();
    bool LoadCharAttrModulusConfig(char* szFileName);

    ProfessionModulus* GetProfessionModulusById( unsigned short nId );  // 通过职业获得属性系数


    float GetTotalDamageModulus()   { return fTotalDamageModulus;   }
    float GetMonsterDamageModulus() { return fMonsterDamageModulus; }
    float GetPlayerDamageModulus()  { return fPlayerDamageModulus;  }

    // 伤害结算浮动系数
    struct AttackFloatModulus
    {
        unsigned short nType;   // 类型，比如：物理，法术等 参见enum EDamageType
        short stMin;            // 浮动最小值
        short stMax;            // 浮动最大值
    };

    typedef std::map< unsigned short, AttackFloatModulus > AttackFloatModulusContainer;
    typedef AttackFloatModulusContainer::iterator ItrAttackFloatModulusContainer;

    float GetAttackModulusMinByType( unsigned short nType );
    float GetAttackModulusMaxByType( unsigned short nType );
    //////////////////////////////////////////////////////////////////////////
    float GetOtherPhyAtkModulus(){ return fOtherPhyAtkModulus; }
    float GetOtherMagicAtkModulus(){ return fOtherMagicAtkModulus; }
    //////////////////////////////////////////////////////////////////////////
    struct PetAtkModulus 
    {
        uint8 nPetAtkType;
        float fPhyAtkModulus;
        float fMagicAtkModulus;
    };

    PetAtkModulus* GetPetModulusByType( uint8 nType );

    typedef std::map< uint8, PetAtkModulus > PetAtkModulusContainer;
    typedef PetAtkModulusContainer::iterator ItrPetAtkModulusContainer;
protected:
    CharAttrModulusConfig();

private:
    ProfessionModulusContainer  mapProfessionModulus;   // 职业各种系数容器
    AttackFloatModulusContainer mapAttackFloatModulus;  // 伤害浮动系数容器
    float fTotalDamageModulus;                          // 总伤害系数
    float fMonsterDamageModulus;                        // 怪物伤害结算系数
    float fPlayerDamageModulus;                         // 玩家伤害结算系数
    float fOtherPhyAtkModulus;                          // 其他Char的物理伤害控制系数
    float fOtherMagicAtkModulus;                        // 其他Char的魔法伤害控制系数
    PetAtkModulusContainer mapPetAtkModulus;            // 宠物的攻击控制系数容器

};

inline CharAttrModulusConfig& CharAttrModulusConfig::Instance()
{
    static CharAttrModulusConfig gCharAttrModulusConfig;
    return gCharAttrModulusConfig;
}

#endif