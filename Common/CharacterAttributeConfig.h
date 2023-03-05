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
{ // �ȼ��Ķ������Ե�����
    ESecondAttrFixType_hpMax,         // HP����ֵ
    ESecondAttrFixType_mpMax,         // MP����ֵ
    ESecondAttrFixType_phyAttack,     // ����������ֵ
    ESecondAttrFixType_exact,         // ��������ֵ
    ESecondAttrFixType_dodge,         // ��������ֵ
    ESecondAttrFixType_critical,      // ��������ֵ
    ESecondAttrFixType_tenacityl,     // ��������ֵ
    ESecondAttrFixType_hpRestore,     // �����ظ�����ֵ
    ESecondAttrFixType_mpRestore,     // MP�ظ�����ֵ
    ESecondAttrFixType_magicAttack,   // ħ����������ֵ
    ESecondAttrFixType_phyDefend,     // �������ֵ
    ESecondAttrFixType_magicDefend,   // ħ������ֵ
    ESecondAttrFixType_MaxSize,       // �������ֵ
};

//�ȼ�����
struct SLevelAttribute
{   
    int16 baseAttribute[EBaseAttr_MaxSize];               // �ȼ��Ļ�������    
    int16 secondAttributeFix[ESecondAttrFixType_MaxSize]; // �ȼ��Ķ������Ե�����
};

//������ְҵ�ȼ�����
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
    // ��������
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