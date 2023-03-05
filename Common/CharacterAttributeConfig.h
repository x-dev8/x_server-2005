/********************************************************************
    Filename:    CharacterAttributeConfig.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_CHARACTER_ATTRIBUTE_CONFIG_H__
#define __COMMON_CHARACTER_ATTRIBUTE_CONFIG_H__

#pragma once

#include "GlobalDef.h"

#pragma pack( push, 1)

enum ESecondAttrFixType
{ // 等级的二级属性的修正
    ESecondAttrFixType_hpMax,         // HP修正值
    ESecondAttrFixType_mpMax,         // MP修正值
    ESecondAttrFixType_phyAttack,     // 物理攻击修正值
    ESecondAttrFixType_exact,         // 命中修正值
    ESecondAttrFixType_dodge,         // 躲闪修正值
    ESecondAttrFixType_critical,      // 暴击修正值
    ESecondAttrFixType_tenacityl,     // 韧性修正值
    ESecondAttrFixType_hpRestore,     // 生命回复修正值
    ESecondAttrFixType_mpRestore,     // MP回复修正值
    ESecondAttrFixType_magicAttack,   // 魔法攻击修正值
    ESecondAttrFixType_phyDefend,     // 物防修正值
    ESecondAttrFixType_magicDefend,   // 魔防修正值
    ESecondAttrFixType_MaxSize,       // 种类最大值
};

//等级属性
struct SLevelAttribute
{   
    int16 baseAttribute[EBaseAttr_MaxSize];               // 等级的基本属性    
    int16 secondAttributeFix[ESecondAttrFixType_MaxSize]; // 等级的二级属性的修正
};

//各兵种职业等级属性
struct SArmCharacterAttribute
{ 
    char szArmName[ARMS_NAME_LENGTH + 1];
    SLevelAttribute LevelAttribute[MAX_LEVEL_LIMIT];
};

#define theCharacterAttributeConfig CharacterAttributeConfig::GetInstance()

class CharacterAttributeConfig
{
public:    
    static CharacterAttributeConfig& GetInstance();

    uint32 LoadLevelBaseSecondAttribute( const char* szFileName );
    uint32 SaveLevelBaseSecondAttribute( const char* szFileName );

    SArmCharacterAttribute* GetArmCharacterAttribute( uint8 armsType);
    SLevelAttribute*        GetCharacterAttribute( uint8 armsType, uint16 nLevel );

protected:    
    CharacterAttributeConfig();
    CharacterAttributeConfig( const CharacterAttributeConfig& ){}
    CharacterAttributeConfig& operator=( const CharacterAttributeConfig& ){}

private:
    // 基本属性
    SArmCharacterAttribute  m_ArmCharacterAttributes[EArmType_MaxSize];
};

//////////////////////////////////////////////////////////////////////////
// inline
inline SArmCharacterAttribute* CharacterAttributeConfig::GetArmCharacterAttribute( uint8 armsType)
{
    if ( armsType>=EArmType_MaxSize )
    { return NULL; }

    return &(m_ArmCharacterAttributes[ armsType ]);
}

inline SLevelAttribute* CharacterAttributeConfig::GetCharacterAttribute( uint8 armsType, uint16 nLevel )
{
    if ( armsType>=EArmType_MaxSize || nLevel <= 0 || nLevel>MAX_LEVEL_LIMIT )
    { return NULL; }

    return &(m_ArmCharacterAttributes[ armsType ].LevelAttribute[ nLevel - 1]);
}

#pragma pack( pop)


#endif // __COMMON_CHARACTER_ATTRIBUTE_CONFIG_H__