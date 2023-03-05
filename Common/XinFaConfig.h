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
        EXCD_XinFaMaxNum       = 301,   // 最多300个心法
        EXCD_XinFaMaxLevel     = 201,   // 心法最高200级
        EXCD_EffectCharAttrMax = 2 ,    // 最多影响2个人物属性
        EXCD_SkillMaxCount     = 6 ,    // 心法最多有6个技能
        EXCD_EffectSkillAttr   = 2 ,    // 最多影响技能的2个属性
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
        string  strDesc         ;   // 心法说明
        uint16  nPrevXinFa      ;   // 前置心法
        uint8   nNeedLevel      ;   // 学习等级
        uint32  nNeedMoney      ;   // 学习金钱
        uint32  nNeedExp        ;   // 学习经验
        Array< bool, EArmType_MaxSize> arrayProfessionReq; // 心法学习职业

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

#define theXinFaConfig XinFaConfig::Instance()   //实例接口

#endif

