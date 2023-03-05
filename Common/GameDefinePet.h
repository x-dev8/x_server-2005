#ifndef __COMMON_GAMEDEFINEPET_H__
#define __COMMON_GAMEDEFINEPET_H__

#pragma once

#include "GlobalDef.h"

#define PET_LEVELUP_BASEATTR            1   // 宠物升级获得属性点
#define PET_LEVELUP_POTENTIALPOINT      4   // 宠物升级获得潜力点
#define PET_LOYALTY_LIMIT               100 // 宠物快乐度上限
#define PET_LEVEL_OVERTOP_MAX           5   // 宠物等级最多高于玩家 5级

enum EPetBreedConstDefine
{
    //////////////////////////////////////////////////////////////////////////
    // 繁殖操作状态
    EPetBreed_StatusInit = 0,
    EPetBreed_StatusStart  ,  
    EPetBreed_StatusLock   ,  
    EPetBreed_StatusConfirm,  
    /////////////////////////////////////////////////////////////
    // 繁殖操作结束
    EPetBreed_FinishSuccess = 0 ,       
    EPetBreed_FinishFailed      ,
    EPetBreed_FinishTimeOut     ,           
    EPetBreed_FinishCancel      ,            
    EPetBreed_FinishOutLine     ,
    EPetBreed_FinishHasBreed    ,
};

//宠物性格	
//胆小	cowardice
//谨慎	reticence
//忠诚	ligeance
//精明	prudence
//勇猛	valor
enum EPetCharacterize
{
    EPetChar_Cowardice   ,
    EPetChar_Reticence   ,
    EPetChar_Ligeance    ,
    EPetChar_Prudence    ,
    EPetChar_Valor       ,
    EPetChar_Count            
};

enum EPetQuality
{
    EPetQuality_None      ,
    EPetQuality_Normal    ,
    EPetQuality_Advance   ,
    EPetQuality_Flaunt    ,
    EPetQuality_Count   
};

enum EPetGrowthRateStar
{
    EPetGrowth_One       ,
    EPetGrowth_Two       ,
    EPetGrowth_Three     ,
    EPetGrowth_Four      ,
    EPetGrowth_Five      ,
    EPetGrowth_Count
};

enum EPetFood
{
    EPetFood_Meat       ,   // 肉
    EPetFood_Grass      ,   // 草
    EPetFood_Insect     ,   // 虫子
    EPetFood_Grain      ,   // 谷物
    EPetFood_Count
};

static char* (g_szPetFoodType[]) = 
{
    "Meat"      , 
    "Grass"     , 
    "Insect"    , 
    "Grain"     , 
};

enum EPetAttackType
{
    EPetAttack_Unkonw  , // 没有任何结算
    EPetAttack_Physical, // 物攻
    EPetAttack_Magic   , // 魔攻
    EPetAttack_Both    , // 对物防魔防都做伤害结算
};

enum EPetSkillCategory
{
    EPetSkillCategory_ManualAttack      =   1,  // 攻击
    EPetSkillCategory_AssistAttack      =   2,  // 攻击辅助
    EPetSkillCategory_Restore           =   3,  // 治疗
    EPetSkillCategory_AssistDefend      =   4,  // 防御辅助
    EPetSkillCategory_Relive            =   5,  // 复活
    EPetSkillCategory_AutoAttack        =   6,  // 自动攻击
    EPetSkillCategory_PetAttr           =   7,  // 增加宠物属性
    EPetSkillCategory_MasterAttr        =   8,  // 增加主人属性
    EPetSkillCategory_AssistMaster      =   9,  // 承受主人伤害
	EPetSkillCategory_Aptitude			=   10, // 资质类
    EPetSkillCategory_MaxSize           =   11,
};

enum EPetSource
{
    EPetSource_Other = 0 ,   //其他
    EPetSource_Skill     ,   //捕捉
    EPetSource_Breed     ,   //繁殖
    EPetSource_Stall     ,   //交易
};

enum EDisappearSource
{
    EDS_Discard     ,   // 放生
    EDS_SavvyUp     ,   // 提升悟性
    EDS_Breed       ,   // 繁殖
    EDS_Stall       ,   // 交易
};

//召唤宠物怪
struct SSummonPet
{
    SSummonPet()
    {
        petId       = InvalidGameObjectId;
        petAIType   = ePetCommandAI;
        skillId     = 0;
    }

    void Clear()
    {
        petId       = InvalidGameObjectId;
        petAIType   = ePetCommandAI;
        skillId     = 0;
    }

    GameObjectId  petId;   //宠物ID
    uint8   petAIType   ;   //宠物类型
    uint16  skillId     ;   //召唤技能

    bool operator == ( uint16 id ) { return skillId == id; }
};

#endif // __COMMON_GAMEDEFINEPET_H__