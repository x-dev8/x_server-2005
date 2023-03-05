/********************************************************************************************************************************
                FileName:CharAttrModulues.h
                Author  :eliteYang
                Mail    :elite_yang@163.com
                Desc    :һ�����ԶԶ������Ե�Ӱ��ϵ���������﹥���˺�����ϵ�������˺��Ŀ���ϵ���������˺��Ŀ���ϵ��
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
        EC_HpMode            = 0,	// HPϵ��
        EC_MpMode               ,	// MPϵ��
        EC_MoveSpeedMode        ,	// �ƶ��ٶ�ϵ��
        EC_HpRestoreMode        ,	// HP�ָ�ϵ��
        EC_MpRestoreMode        ,	// MP�ָ�ϵ��
        EC_ExactMode            ,	// ����ϵ��
        EC_DodgeMode            ,	// ����ϵ��
        EC_CriticalMode         ,	// ������ϵ��
        EC_TenacityMode         ,	// ����ϵ��
        EC_CriticalIntensityMode,	// �����˺�ϵ��
        EC_DerateCriIntenMode   ,   // ���Ⱪ���˺�ϵ��
        EC_AtkSpeedMode         ,	// �����ٶ�ϵ��
        EC_IntonateMode         ,   // ����ʱ��ϵ��
        EC_BackMode             ,   // ����ϵ��
        EC_PhyAtkMode           ,   // �﹥ϵ��
        EC_MagicAtkMode         ,	// ����ϵ��
        EC_PhyDefendMode        ,   // ���ϵ��
        EC_MagicDefendMode      ,   // ����ϵ��

        EC_MAX                  ,   // ϵ���������ֵ
    };
    struct AttrModulus 
    {
        AttrModulus()
        { memset( this, 0, sizeof( AttrModulus ) ); }

        unsigned short nBaseAttrId; // һ������ID
        float Modulus[ EC_MAX ];
    };

    typedef std::map< unsigned short, AttrModulus > AttrModulusContainer;
    typedef AttrModulusContainer::iterator ItrAttrModulusContainer;

    struct AttrAttackModulus 
    {
        AttrAttackModulus()
        { memset( this, 0, sizeof( AttrAttackModulus ) ); }

        unsigned short nType;       // ��������
        float fAttackModulus;
        int nAttackFixPer;
    };

    typedef std::map< unsigned short, AttrAttackModulus > AttrAttackModlusContainer;
    typedef AttrAttackModlusContainer::iterator ItrAttrAttackModulusContainer;

    struct ProfessionModulus 
    {
        unsigned short nProfessionId;           // ְҵID
        AttrModulusContainer mapAttrModulus;    // һ�����ԶԶ������Ե�Ӱ��ϵ��
        float phyDamageModulus;                 // �����˺�����ϵ��
        float magicDamageModulus;               // �����˺�����ϵ��
        AttrAttackModlusContainer mapAttrAttackModulus; // �����˺�ϵ�����˺������ٷֱ�

        AttrModulus* GetAttrModulusById( unsigned short nId );      // ͨ��һ���������ͻ��һ������Ӱ��������Ե�ϵ��
        AttrAttackModulus* GetAttrAttackModulusByType( unsigned short nType );  // ������Թ���ϵ���������˺������ٷֱ�
    };

    typedef std::map< unsigned short, ProfessionModulus > ProfessionModulusContainer;
    typedef ProfessionModulusContainer::iterator ItrProfessionModulusContainer;

    ~CharAttrModulusConfig();
    static CharAttrModulusConfig& Instance();
    bool LoadCharAttrModulusConfig(char* szFileName);

    ProfessionModulus* GetProfessionModulusById( unsigned short nId );  // ͨ��ְҵ�������ϵ��


    float GetTotalDamageModulus()   { return fTotalDamageModulus;   }
    float GetMonsterDamageModulus() { return fMonsterDamageModulus; }
    float GetPlayerDamageModulus()  { return fPlayerDamageModulus;  }

    // �˺����㸡��ϵ��
    struct AttackFloatModulus
    {
        unsigned short nType;   // ���ͣ����磺���������� �μ�enum EDamageType
        short stMin;            // ������Сֵ
        short stMax;            // �������ֵ
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
    ProfessionModulusContainer  mapProfessionModulus;   // ְҵ����ϵ������
    AttackFloatModulusContainer mapAttackFloatModulus;  // �˺�����ϵ������
    float fTotalDamageModulus;                          // ���˺�ϵ��
    float fMonsterDamageModulus;                        // �����˺�����ϵ��
    float fPlayerDamageModulus;                         // ����˺�����ϵ��
    float fOtherPhyAtkModulus;                          // ����Char�������˺�����ϵ��
    float fOtherMagicAtkModulus;                        // ����Char��ħ���˺�����ϵ��
    PetAtkModulusContainer mapPetAtkModulus;            // ����Ĺ�������ϵ������

};

inline CharAttrModulusConfig& CharAttrModulusConfig::Instance()
{
    static CharAttrModulusConfig gCharAttrModulusConfig;
    return gCharAttrModulusConfig;
}

#endif