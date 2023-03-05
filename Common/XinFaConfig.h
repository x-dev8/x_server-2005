#ifndef __COMMON_XINFACONFIG_H__
#define __COMMON_XINFACONFIG_H__

#pragma once

#include <string>
#include <vector>
#include <map>

#include "GlobalDef.h"
#include "Array.h"

class XinFaConfig
{
public:
    enum EXinFaConstDefine
    {
        EXCD_XinFaMaxNum       = 301,   // ���300���ķ�
        EXCD_XinFaMaxLevel     = 201,   // �ķ����200��
        EXCD_EffectCharAttrMax = 2 ,    // ���Ӱ��2����������
        EXCD_SkillMaxCount     = 6 ,    // �ķ������6������
        EXCD_EffectSkillAttr   = 2 ,    // ���Ӱ�켼�ܵ�2������
    };
public:
    struct SXinFaSkill
    {
        uint16  nId         ;
        uint8   nLevel      ;
        uint8   attrType [EXCD_EffectSkillAttr];
        int16   attrValue[EXCD_EffectSkillAttr];

        SXinFaSkill()
        { memset(this,0,sizeof(SXinFaSkill)); }

    };

    struct STalentXinFa
    {
        uint16  nId             ;
        uint8   nLevel          ;
        uint16  nIconId         ;   // ICONID
        string  strName         ;
        string  strDesc         ;   // �ķ�˵��
        uint16  nPrevXinFa      ;   // ǰ���ķ�
        uint8   nNeedLevel      ;   // ѧϰ�ȼ�
        uint32  nNeedMoney      ;   // ѧϰ��Ǯ
        uint32  nNeedExp        ;   // ѧϰ����
        Array< bool, EArmType_MaxSize> arrayProfessionReq; // �ķ�ѧϰְҵ

        uint8       charAttrType [EXCD_EffectCharAttrMax];
        CustomValue charAttrValue[EXCD_EffectCharAttrMax];
        SXinFaSkill skills       [EXCD_SkillMaxCount]    ;

        STalentXinFa()  
        { memset(this,0,sizeof(STalentXinFa)); }

        SXinFaSkill* GetXinFaSkillByID( uint16 nSkillID )
        {
            for (int i=0; i < EXCD_SkillMaxCount; ++i )
            {
                if (skills[i].nId == nSkillID)
                { return &skills[i]; }
            }

            return NULL;
        }

        SXinFaSkill* GetXinFaSkill( uint16 nSkillID, uint8 nSkillLevel )
        {
            for (int i=0; i < EXCD_SkillMaxCount; ++i )
            {
                if (skills[i].nId == nSkillID && skills[i].nLevel == nSkillLevel)
                { return &skills[i]; }
            }

            return NULL;
        }

        SXinFaSkill *GetXinFaSkill( uint8 index )
        {
            if (index >= EXCD_SkillMaxCount)
            { return  NULL; }

            return &skills[index]; 
        }

        bool IsActiveSkillByIndex(uint8 index)
        {
            if (index >= EXCD_SkillMaxCount)
            { return  false; }

            return (skills[index].nLevel != 0);
        }

        bool IsActiveSkill( uint16 nSkillID )
        {
            for (int i=0; i < EXCD_SkillMaxCount; ++i )
            {
                if (skills[i].nId == nSkillID && skills[i].nLevel != 0)
                { return true; }
            }

            return false;
        }
    };

protected:
    XinFaConfig();

public:
    ~XinFaConfig();

    inline static XinFaConfig& Instance()
    {
        static XinFaConfig s_xConfig;
        return s_xConfig;
    }

    STalentXinFa* GetXinFaByID(unsigned short nID,  unsigned short nLevel);
    bool LoadXinFaConfig(const char* szFile);
 
	int	GetSkillNeedXinFaLevel(unsigned short nXinFaID, unsigned short nSkillID);
	STalentXinFa* GetXinFaByProfession(unsigned short nProfessionID,  unsigned short index);
private:
    Array< Array<STalentXinFa, EXCD_XinFaMaxLevel>, EXCD_XinFaMaxNum>  m_XinFaArray;

};

#define theXinFaConfig XinFaConfig::Instance()   //ʵ���ӿ�

#endif

