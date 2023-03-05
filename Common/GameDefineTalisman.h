#ifndef __COMMON_GAMEDEFINETALISMAN_H__
#define __COMMON_GAMEDEFINETALISMAN_H__

#pragma once

enum ETalismanQuality
{
    ETalismanQuality_None       ,
    ETalismanQuality_Normal     ,   // 凡品
    ETalismanQuality_Fine       ,   // 良品
    ETalismanQuality_Refine     ,   // 精品
    ETalismanQuality_Fairy      ,   // 仙物
    ETalismanQuality_Deity      ,   // 神器
    ETalismanQuality_Count   
};

// 法宝修炼属性枚举
enum ETalismanAttributeType
{
    TalismanAttr_None = 0        ,
    TalismanAttr_NimbusLimit     ,   //灵气值上限
    TalismanAttr_NimbusRestore   ,   //灵气值回复
    TalismanAttr_NimbusCost      ,   //灵气值消耗
    TalismanAttr_SkillRange      ,   //施法范围
    TalismanAttr_SkillDamage     ,   //技能伤害
    TalismanAttr_SkillRestore    ,   //技能治疗
    TalismanAttr_SkillCD         ,   //技能CD
    TalismanAttr_StatusRate      ,   //附加状态成功率
    TalismanAttr_StatusKeepTime  ,   //状态持续时间
    
    TalismanAttr_MaxSize         ,   
};

static char* (g_szTalismanAttributeType[]) =
{
    "TalismanAttr_None"            ,
    "TalismanAttr_NimbusLimit"     ,   //灵气值上限
    "TalismanAttr_NimbusRestore"   ,   //灵气值回复
    "TalismanAttr_NimbusCost"      ,   //灵气值消耗
    "TalismanAttr_SkillRange"      ,   //施法范围
    "TalismanAttr_SkillDamage"     ,   //技能伤害
    "TalismanAttr_SkillRestore"    ,   //技能治疗
    "TalismanAttr_SkillCD"         ,   //技能CD
    "TalismanAttr_StatusRate"      ,   //附加状态成功率
    "TalismanAttr_StatusKeepTime"  ,   //状态持续时间
};


#endif // __COMMON_GAMEDEFINETALISMAN_H__