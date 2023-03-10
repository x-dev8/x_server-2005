/********************************************************************
    Filename:    GameDefineChar.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_GAMEDEFINECHAR_H__
#define __COMMON_GAMEDEFINECHAR_H__

#pragma once
#pragma warning ( push )
#pragma warning ( disable: 4018 )
#pragma warning ( disable: 4244 )

#pragma pack ( push, 1 )

#include "GameDefineGlobal.h"

enum EConstSkillId
{    
    //普通攻击 最多5个 客户端发出普通攻击时，根据当前武器普通攻击的个数，选择一个发出
    //服务器判定时，用范围判定是否普通攻击下发时，用正确的下发
    ConstSkillId_NormalAttack_Combat   = 1300 ,// 徒手
    ConstSkillId_NormalAttack_Warrior  = 1301 ,// 战士
    ConstSkillId_NormalAttack_Mage     = 1302 ,// 法师
    ConstSkillId_NormalAttack_Taoist   = 1303 ,// 道士
    ConstSkillId_NormalAttack_Assassin = 1304 ,// 刺客
    ConstSkillId_NormalAttack_Hunter   = 1305 ,// 猎人
    ConstSkillId_NormalAttack_Sniper   = 1306 ,// 火枪
}; 

enum EBaseAttr
{ //基本属性
    EBaseAttr_Strength    , // 力量
    EBaseAttr_Agility     , // 敏捷
    EBaseAttr_Constitution, // 体质
    EBaseAttr_Intelligence, // 智力
    EBaseAttr_MaxSize     , // 种类最大值
};

enum EAttackDefineType
{
    EAttackDefineType_Short, // 近程
    EAttackDefineType_Long,  // 远程
    EAttackDefineType_Magic, // 魔法
    EAttackDefineType_Max,   // 种类最大值
};

enum EArmType
{ // 兵种
    EArmType_Warrior , // 战士
    EArmType_Mage    , // 法师
    EArmType_Taoist  , // 道士
    EArmType_Assassin, // 刺客
    EArmType_Hunter  , // 猎人
    EArmType_Sniper  , // 火枪
    EArmType_MaxSize , // 种类最大值

    EArmType_Monster = 20, // 怪
};

enum ERaceType
{ //脸
    Race_China = 0 , //中国人
    Race_MiddleEast, //中东
    Race_West      , //西方
    Race_Max
};

enum ESexType
{ //性别
    Sex_Male = 0, //男性   
    Sex_Female,   //女性
    Sex_Max
};

// 大类
enum EAttackSuperType
{
    EAttackSuperType_Physics , // 物攻   -[ 近攻, 远攻(子弹,弓箭) ]
    EAttackSuperType_Magic   , // 魔攻   -[ 魔攻 ]
    EAttackSuperType_Element , // 元素攻 -[ 冰攻 火攻 电攻 风攻]
};
// 子类
enum EAttackType
{
    EAttackType_Short  , // 近攻
    EAttackType_Long   , // 远攻
    EAttackType_Magic  , // 魔攻
    EAttackType_Max    , // 攻击的最大种类个数
};
// 子类
enum EDefendType
{
    EDefendType_Short  , // 近防
    EDefendType_Long   , // 远防
    EDefendType_Magic  , // 魔防
    EDefendType_Max    , // 防御的最大种类个数
};

enum ERAttributeType
{
    RT_None = 0             ,   //无

    RT_AddStrength          ,   //力量
    RT_AddAgility           ,   //敏捷
    RT_AddConstitution      ,   //体质
    RT_AddIntelligence      ,   //智力

    RT_AddShortAttack       ,   //近攻点数
    RT_AddLongAttack        ,   //远攻点数
    RT_AddMagicAttack       ,   //魔攻点数

    RT_AddShortDefend       ,   //近防点数
    RT_AddMagicDefend       ,   //魔防点数
    RT_AddLongDefend        ,   //远程防御

    RT_AddExact             ,   //命中
    RT_AddDodge             ,   //闪避
    RT_AddCritical          ,   //暴击
    RT_AddTenacity          ,   //韧性
    RT_AddCriticalIntensity ,   //暴击伤害

    RT_AddHPMax             ,   //生命上限
    RT_AddAPMax             ,   //弓箭上限
    RT_AddBPMax             ,   //弹药上限
    RT_AddFPMax             ,   //怒气上限
    RT_AddEPMax             ,   //能量上限
    RT_AddMPMax             ,   //魔法上限

    RT_AddBaseAttr          ,   //全基础属性
    RT_AddExpPer            ,   //经验获得 百分比
    RT_AddEnergyMax         ,   //活力上限
    RT_AddMoveSpeed         ,   //移动速度 具体的值
    RT_AddHPRestore         ,   //生命回复

    RT_AddAPRestore         ,   //弓箭回复
    RT_AddBPRestore         ,   //弹药回复
    RT_AddFPRestore         ,   //怒气回复
    RT_AddEPRestore         ,   //能量回复
    RT_AddMPRestore         ,   //魔法回复

    RT_AddAttrMAX           ,
};

// 只有状态累加会出现负值 其他的数据应该都是正
struct SAttrType0
{ // 四个基础一级属性 hp回复 energy回复
    uint16 upLimit;   // 上限

    uint16 base;      // 0-65535
    int16  item;      // -32766-32767
    int16  status;    // -32766-32767
    uint16 skill;     // 0-65535
    int16  title;     // -32766-32767
    uint16 mount;     // 0-65535
    int16  suit;      // -32766-32767
    int16  itemPer;   // -2000%-2000%
    int16  statusPer; // -2000%-2000%
    uint16 skillPer;  // 0%-2000%
    int16  titlePer;  // -2000%-2000%
    uint16 mountPer;  // 0%-2000%
    int16  suitPer;   // -2000%-2000%
    uint16 final;     // 0-65535

    SAttrType0()
    { 
        memset( this, 0, sizeof( SAttrType0 ));
        upLimit  = 65535;
    }

    void Reset()
    {
        memset( this, 0, sizeof( SAttrType0 )); 
        upLimit = 65535;
    }

    uint16 GetPartFinal( uint16 part )
    {
        int32 value = 0;
        switch ( part )
        {
        case ECustomDataPart_item:
            { value = item + base * ( itemPer * 0.01 ) ;    }
            break;
        case ECustomDataPart_status:
            { value = status + base * ( statusPer * 0.01 ); }
            break;
        case ECustomDataPart_skill:
            { value = skill + base * ( skillPer * 0.01 );   }
            break;
        case ECustomDataPart_title:
            { value = title + base * ( titlePer * 0.01 ) ;  }
            break;
        case ECustomDataPart_mount:
            { value = mount + base * ( mountPer * 0.01 );   }
            break;
        case ECustomDataPart_suit:
            { value = suit + base * ( suitPer * 0.01 );     }
            break;
        }

        if ( value < 0)
        { value = 0; }
        return (uint16)value;
    }

    void AddPartValue( uint16 part, int16 value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base += value; }
            break;
        case ECustomDataPart_item:
            { item += value; }
            break;
        case ECustomDataPart_status:
            { status += value; }
            break;
        case ECustomDataPart_skill:
            { skill += value; }
            break;
        case ECustomDataPart_title:
            { title += value;  }
            break;
        case ECustomDataPart_mount:
            { mount += value; }
            break;
        case ECustomDataPart_suit:
            { suit  += value; }
            break;
        case ECustomDataPart_final:
            { final += value; }
            break;
        }
    }

    void ClearPart( uint16 part )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base = 0; }
            break;
        case ECustomDataPart_item:
            { item = 0; itemPer = 0;    }
            break;
        case ECustomDataPart_status:
            { status = 0; statusPer = 0;}
            break;
        case ECustomDataPart_skill:
            { skill = 0; skillPer = 0;  }
            break;
        case ECustomDataPart_title:
            { title = 0; titlePer = 0;    }
            break;
        case ECustomDataPart_mount:
            { mount = 0;  mountPer = 0; }
            break;
        case ECustomDataPart_suit:
            { suit = 0; suitPer = 0;    }
            break;
        case ECustomDataPart_final:
            { final = 0; }
            break;
        }
    }


    void UpdateFinal()
    {
        int32 tFinalPer = itemPer + statusPer + skillPer + titlePer + mountPer + suitPer;
        int32 tFinal = base + item + status + skill + title + mount + suit + (int32)(base * ( tFinalPer * 0.01 )); 

        if ( tFinal > upLimit)
        { final = upLimit; }
        else if ( tFinal < 0 )
        { final = 0; }
        else
        { final = (uint16)tFinal; }
    }
};

struct SAttrType1
{ // HPMax EnergyMax
    uint32 upLimit;   // 上限

    uint32 base;      // +
    int32  item;      // +/-
    int32  status;    // +/-
    uint32 skill;     // +
    int32  title;     // +/-
    uint32 mount;     // +  
    int32  suit;      // +/-
    int16  itemPer;   // +/-
    int16  statusPer; // +/-
    uint16 skillPer;  // + 
    int16  titlePer;  // +/-
    uint16 mountPer;  // +/-
    int16  suitPer;   // +/-
    uint32 final;     // +/-

    SAttrType1()
    { 
        memset( this, 0, sizeof( SAttrType1 ));
        upLimit = 100000000;
    }

    void Reset()
    {
        memset( this, 0, sizeof( SAttrType1 )); 
        upLimit = 100000000;
    }

    void AddPartValue( uint16 part, int32 value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base += value; }
            break;
        case ECustomDataPart_item:
            { item += value; }
            break;
        case ECustomDataPart_status:
            { status += value; }
            break;
        case ECustomDataPart_skill:
            { skill += value; }
            break;
        case ECustomDataPart_title:
            { title += value;  }
            break;
        case ECustomDataPart_mount:
            { mount += value; }
            break;
        case ECustomDataPart_suit:
            { suit  += value; }
            break;
        case ECustomDataPart_final:
            { final += value; }
            break;
        }
    }

    void UpdateFinal()
    {
        int32 tFinalPer = itemPer + statusPer + skillPer + titlePer + mountPer + suitPer;
        int32 tFinal =  base + item + status + skill + title + mount + suit + (int32)(base * ( tFinalPer * 0.01) ); 
        if ( tFinal > upLimit)
        { final = upLimit; }
        else if ( tFinal < 1 )
        { final = 1; }
        else
        { final = tFinal; }
    }
};

struct SAttrType2
{ // 进攻 远攻 魔攻 移动 攻击速度 吟唱时间 近防 远防 魔防
    float  upLimit;   // 上限

    float  base     ; // +/-
    float  item     ; // +/-
    float  status   ; // +/-
    float  skill    ; // +/-
    float  title    ; // +/-
    float  mount    ; // +/-
    float  suit     ; // +/-
    int16  itemPer  ; // +/-
    int16  statusPer; // +/-
    uint16 skillPer ; // +
    int16  titlePer ; // +/-
    uint16 mountPer ; // +
    int16  suitPer  ; // +/-
    float  final    ;

    SAttrType2()
    { 
        memset( this, 0, sizeof( SAttrType2 )); 
        upLimit = 50000.0;
    }

    void Reset()
    {
        memset( this, 0, sizeof( SAttrType2 )); 
        upLimit = 50000.0;
    }

    void AddPartValue( uint16 part, float value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base += value; }
            break;
        case ECustomDataPart_item:
            { item += value; }
            break;
        case ECustomDataPart_status:
            { status += value; }
            break;
        case ECustomDataPart_skill:
            { skill += value; }
            break;
        case ECustomDataPart_title:
            { title += value;  }
            break;
        case ECustomDataPart_mount:
            { mount += value; }
            break;
        case ECustomDataPart_suit:
            { suit  += value; }
            break;
        case ECustomDataPart_final:
            { final += value; }
            break;
        }
    }

    void UpdateFinal()
    {
        int32 tFinalPer = itemPer + statusPer + skillPer + titlePer + mountPer + suitPer;
        float tFinal = base + item + status + skill + title + mount + suit + base * ( tFinalPer * 0.01 ); 
        if ( tFinal > upLimit)
        { final = upLimit; }
        else if ( tFinal < 0.0f )
        { final = 0.0f; }
        else
        { final = tFinal; }
    }
};

struct SCharAttributeUpdate
{
    uint16 strength         ;
    uint16 agility          ;
    uint16 constitution     ;
    uint16 intelligence     ;
    int32  hpMax            ;
    int32  energyMax        ;
    float  attack           ;
    float  defendShort      ;
    float  defendLong       ;
    float  defendMagic      ;
    float  moveSpeed        ;
    int16  hpRestore        ;
    int16  energyRestore    ;
    int16  derateShort      ;
    int16  derateLong       ;
    int16  derateMagic      ;
    int16  derateIgnoreShort;
    int16  derateIgnoreLong ;
    int16  derateIgnoreMagic;
    int16  dodge            ;
    int16  exact            ;
    int16  critical         ;
    int16  criticalIntensity;
    int16  tenacity         ;
    int16  resistDread      ;
    int16  resistComa       ;
    int16  resistSilence    ;
    int16  resistSlow       ;
    int16  attackSpeed      ;
    int16  intonate         ;
};

// 角色的一级属性 用于运行时结构
struct SCharBaseAttr
{
    SAttrType0 baseAttrValue[EBaseAttr_MaxSize]; // 属性值

    void UpdateFinal()
    {
        for ( uint8 i=0; i<EBaseAttr_MaxSize; ++i )
        { baseAttrValue[i].UpdateFinal(); }
    }

    void ClearPart( uint16 part )
    {
        for ( uint8 i=0; i<EBaseAttr_MaxSize; ++i )
        { baseAttrValue[i].ClearPart( part ); }
    }
};

// 角色的二级属性 用于运行时结构
struct SCharFightAttr
{   
    SAttrType1 hpMax            ; // 1-5W      HP上限 
    SAttrType1 energyMax        ; // 1-5W      MP上限 魔法：法师.道士专有 怒气：战士专有 能量：刺客专有 箭支：猎人专有 弹药：火枪专有
    SAttrType2 attack           ; // 1-5W      攻击力  战士 刺客-defendShort 法师 道士-defendMagic 猎人 火枪-defendLong
    SAttrType2 defendShort      ; // 1-5W      近程防御
    SAttrType2 defendLong       ; // 1-5W      远程防御
    SAttrType2 defendMagic      ; // 1-5W      魔法防御
    SAttrType2 moveSpeed        ; // 1.0-100.0 移动速度
    SAttrType0 hpRestore        ; // 1-1000    HP恢复
    SAttrType0 energyRestore    ; // 1-1000    MP恢复
    SInt16     derateShort      ; // 1%-100%   近程减免     /100
    SInt16     derateLong       ; // 1%-100%   远程减免     /100
    SInt16     derateMagic      ; // 1%-100%   魔法减免     /100
    SInt16     derateIgnoreShort; // 1%-100%   忽视近程减免 /100
    SInt16     derateIgnoreLong ; // 1%-100%   忽视远程减免 /100
    SInt16     derateIgnoreMagic; // 1%-100%   忽视魔法减免 /100
    SInt16     dodge            ; // 1%-100%   闪避率       /100 单位为万分之一
    SInt16     exact            ; // 1%-100%   命中率       /100 单位为万分之一
    SInt16     critical         ; // 1%-100%   暴击率       /100
    SInt16     criticalIntensity; // 1-1000    暴击伤害     /100
    SInt16     tenacity         ; // 1-1000    韧性         /100
    SInt16     resistDread      ; // 1-1000    恐惧抗性
    SInt16     resistComa       ; // 1-1000    昏迷抗性
    SInt16     resistSilence    ; // 1-1000    沉默抗性
    SInt16     resistSlow       ; // 1-1000    减速抗性
    SAttrType2 attackSpeed      ; // 1-1000    攻击速度
    SAttrType2 intonate         ; // 1-1000    吟唱时间
};

struct SBaseProperty
{
    SCharBaseAttr  baseAttr; // 一级属性
    SCharFightAttr fight;    // 二级属性
};

//////////////////////////////////////////////////////////////////////////
struct SCharAttrEx
{ // 为第三个项目做前期数据结构定义 时间关系第二个项目还是用旧的
    enum EBaseIndex
    {        
        EBaseIndex_Strength,     // 力量
        EBaseIndex_Agility,      // 敏捷
        EBaseIndex_Constitution, // 体质
        EBaseIndex_Intelligence, // 智力
        EBaseIndex_MaxSize,      // 最大个数
    };

    TValueArray<uint16, EBaseIndex_MaxSize > charAttrBase;
};

// 得到职业相应的基础攻击大类
inline uint8 GetBaseAttackType( uint16 profession )
{
    switch ( profession )
    {
    case EArmType_Warrior:
    case EArmType_Assassin:
        return EAttackType_Short;
        break;
    case EArmType_Hunter:
    case EArmType_Sniper:
        return EAttackType_Long;
        break;
    case EArmType_Mage:
    case EArmType_Taoist:
        return EAttackType_Magic;
        break;
    }
}

#pragma pack ( pop )
#pragma warning ( pop )

#endif // __COMMON_GAMEDEFINECHAR_H__
