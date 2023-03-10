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

//各个职业的普通攻击 
//客户端发出普通攻击时，根据当前武器普通攻击的个数，选择一个发出
//服务器判定时，用范围判定是否普通攻击下发时，用正确的下发
enum EConstSkillId
{    
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
    EBaseAttr_Stamina     , // 耐力
    EBaseAttr_Intelligence, // 灵气
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
    EArmType_Mage    , // 乐师
    EArmType_Taoist  , // 法师
    EArmType_Assassin, // 刺客
    EArmType_Hunter  , // 猎人
    EArmType_Sniper  , // 火枪
    EArmType_MaxSize , // 种类最大值

    EArmType_Monster = 20, // 怪
};

enum EPhyleType
{ // 种族
    EPhyle_Human    ,	// 人类
    EPhyle_Machine	,   // 机器
    EPhyle_Beast	,   // 兽类
    EPhyle_Immortal	,   // 仙
    EPhyle_Ghost	,   // 鬼
    EPhyle_Bogey	,   // 妖
    EPhyle_Deity	,   // 神
    EPhyle_Demon    ,   // 魔

    EPhyle_MaxCount
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
    EDefendType_Physical    , // 物防
    EDefendType_Magic       , // 魔防
    EDefendType_Both        , // 所有
    EDefendType_Max         , // 防御的最大种类个数
};

enum ERAttributeType
{
    RT_None = 0             ,   //无

    RT_AddStrength          ,   //力量
    RT_AddAgility           ,   //敏捷
    RT_AddConstitution      ,   //体质
    RT_AddIntelligence      ,   //智力

    RT_AddPhysicsAttack     ,   //物攻点数
    RT_AddLongAttack_UnUse  ,   //远攻点数 [未使用]
    RT_AddMagicAttack       ,   //魔攻点数

    RT_AddPhysicsDefend     ,   //物防点数
    RT_AddMagicDefend       ,   //魔防点数
    RT_AddLongDefend_UnUse  ,   //远程防御 [未使用]

    RT_AddExact             ,   //命中
    RT_AddDodge             ,   //闪避
    RT_AddCritical          ,   //暴击
    RT_AddTenacity          ,   //韧性
    RT_AddCriticalIntensity ,   //暴击伤害

    RT_AddHPMax             ,   //生命上限
    RT_AddAPMax_UnUse       ,   //弓箭上限 [未使用]
    RT_AddBPMax_UnUse       ,   //弹药上限 [未使用]
    RT_AddFPMax_UnUse       ,   //怒气上限 [未使用]
    RT_AddEPMax_UnUse       ,   //能量上限 [未使用]
    RT_AddMPMax             ,   //魔法上限

    RT_AddBaseAttr          ,   //全基础属性
    RT_AddExpPer            ,   //经验获得 百分比
    RT_AddEnergyMax         ,   //活力上限
    RT_AddMoveSpeed         ,   //移动速度 具体的值
    RT_AddHPRestore         ,   //生命回复

    RT_AddAPRestore_UnUse   ,   //弓箭回复 [未使用]
    RT_AddBPRestore_UnUse   ,   //弹药回复 [未使用]
    RT_AddFPRestore_UnUse   ,   //怒气回复 [未使用]
    RT_AddEPRestore_UnUse   ,   //能量回复 [未使用]
    RT_AddMPRestore         ,   //魔法回复

    RT_AddDaoxing           ,   //道行
    RT_AddBreakStrike       ,   //破甲伤害
    RT_AddStabStrike        ,   //贯穿伤害
    RT_AddElementStrike     ,   //元素伤害
    RT_AddToxinStrike       ,   //毒素伤害
    RT_AddSpiritStrike      ,   //精神伤害
    RT_AddBreakResist       ,   //破甲抗性
    RT_AddStabResist        ,   //贯穿抗性
    RT_AddElementResist     ,   //元素抗性
    RT_AddToxinResist       ,   //毒素抗性
    RT_AddSpiritResist      ,   //精神抗性

    RT_AddAttrMaxSize       ,
};

static char* (g_szCharAttributeType[]) =
{
    "CharAttr_None"                 ,   //无

    "CharAttr_AddStrength"          ,   //力量
    "CharAttr_AddAgility"           ,   //敏捷
    "CharAttr_AddConstitution"      ,   //体质
    "CharAttr_AddIntelligence"      ,   //智力

    "CharAttr_AddPhysicsAttack"     ,   //物攻点数
    "CharAttr_AddLongAttack_UnUse"  ,   //远攻点数 [未使用]
    "CharAttr_AddMagicAttack"       ,   //魔攻点数

    "CharAttr_AddPhysicsDefend"     ,   //物防点数
    "CharAttr_AddMagicDefend"       ,   //魔防点数
    "CharAttr_AddLongDefend_UnUse"  ,   //远程防御 [未使用]

    "CharAttr_AddExact"             ,   //命中
    "CharAttr_AddDodge"             ,   //闪避
    "CharAttr_AddCritical"          ,   //暴击
    "CharAttr_AddTenacity"          ,   //韧性
    "CharAttr_AddCriticalIntensity" ,   //暴击伤害

    "CharAttr_AddHPMax"             ,   //生命上限
    "CharAttr_AddAPMax_UnUse"       ,   //弓箭上限 [未使用]
    "CharAttr_AddBPMax_UnUse"       ,   //弹药上限 [未使用]
    "CharAttr_AddFPMax_UnUse"       ,   //怒气上限 [未使用]
    "CharAttr_AddEPMax_UnUse"       ,   //能量上限 [未使用]
    "CharAttr_AddMPMax"             ,   //魔法上限

    "CharAttr_AddBaseAttr"         ,    //全基础属性
    "CharAttr_AddExpPer"            ,   //经验获得 百分比
    "CharAttr_AddEnergyMax"         ,   //活力上限
    "CharAttr_AddMoveSpeed"         ,   //移动速度 具体的值
    "CharAttr_AddHPRestore"         ,   //生命回复

    "CharAttr_AddAPRestore_UnUse"   ,   //弓箭回复 [未使用]
    "CharAttr_AddBPRestore_UnUse"   ,   //弹药回复 [未使用]
    "CharAttr_AddFPRestore_UnUse"   ,   //怒气回复 [未使用]
    "CharAttr_AddEPRestore_UnUse"   ,   //能量回复 [未使用]
    "CharAttr_AddMPRestore"         ,   //魔法回复

    "CharAttr_AddDaoxing"           ,   //道行
    "CharAttr_AddBreakStrike"       ,   //破甲伤害
    "CharAttr_AddStabStrike"        ,   //贯穿伤害
    "CharAttr_AddElementStrike"     ,   //元素伤害
    "CharAttr_AddToxinStrike"       ,   //毒素伤害
    "CharAttr_AddSpiritStrike"      ,   //精神伤害
    "CharAttr_AddBreakResist"       ,   //破甲抗性
    "CharAttr_AddStabResist"        ,   //贯穿抗性
    "CharAttr_AddElementResist"     ,   //元素抗性
    "CharAttr_AddToxinResist"       ,   //毒素抗性
    "CharAttr_AddSpiritResist"      ,   //精神抗性
};

// 基础属性数据类型
struct SBaseAttrType
{
    uint16 base         ;   // 基础 0-65535  
    uint16 assign       ;   // 分配 0-65535
    uint16 item         ;   // 道具 0-65535
    uint16 itemPer      ;   // 0%-2000%
    uint16 skill        ;   // 技能 0-65535
    uint16 skillPer     ;   // 0%-2000%
    int16  status       ;   // 状态 -32766-32767
    int16  statusPer    ;   // -2000%-2000%
    int16  title        ;   // 称号 -32766-32767
    int16  titlePer     ;   // -2000%-2000%
    uint16 pet          ;   // 宠物 0-65535
    uint16 petPer       ;   // 0%-2000%
    uint16 suit         ;   // 套装 0-65535
    uint16 suitPer      ;   // 0%-2000%
	uint16 hero			;	// 主将
	uint16 heroPer		;	// 
	uint16 lieutenant	;   // 副将
	uint16 lieutenantPer;   // 副将 百分比
	uint16 nohero_final ;   //没有主将时候的final值
    uint16 final        ;   // 0-65535

    SBaseAttrType()
    { 
        memset( this, 0, sizeof( SBaseAttrType ));
    }

    void Reset()
    {
        memset( this, 0, sizeof( SBaseAttrType )); 
    }

    uint16 GetPartFinal( uint16 part )
    {
        int32 value = 0;
        switch ( part )
        {
        case ECustomDataPart_item:
            { value = item   + ( base + assign ) * ( itemPer * DEF_PERCENT ) ;   }
            break;
        case ECustomDataPart_status:
            { value = status + ( base + assign ) * ( statusPer * DEF_PERCENT );  }
            break;
        case ECustomDataPart_skill:
            { value = skill  + ( base + assign ) * ( skillPer  * DEF_PERCENT );  }
            break;
        case ECustomDataPart_title:
            { value = title  + ( base + assign ) * ( titlePer  * DEF_PERCENT );  }
            break;
        case ECustomDataPart_pet:
            { value = pet    + ( base + assign ) * ( petPer    * DEF_PERCENT );  }
            break;
        case ECustomDataPart_suit:
            { value = suit   + ( base + assign ) * ( suitPer   * DEF_PERCENT );  }
            break;
		case ECustomDataPart_hero:
			{ value = hero   + nohero_final*( heroPer   * DEF_PERCENT );  }
			break;
		case ECustomDataPart_lieutenant:
			{ value = lieutenant   + ( base + assign ) * ( lieutenantPer   * DEF_PERCENT );  }
			break;
        default:
            { assert( !"SBaseAttrType no this part " ); }
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
        case ECustomDataPart_assign:
            { assign += value; }
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
            { title += value; }
            break;
        case ECustomDataPart_pet:
            { pet   += value; }
            break;
        case ECustomDataPart_suit:
            { suit  += value; }
            break;
		case ECustomDataPart_hero:
			{ hero  += value; }
			break;
		case ECustomDataPart_lieutenant:
			{ lieutenant  += value; }
			break;
        case ECustomDataPart_final:
            { final += value; }
            break;
        default:
            { assert( !"SBaseAttrType no this part " ); }
            break;
        }
    }

    void SubPartValue( uint16 part, int16 value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base -= value; }
            break;
        case ECustomDataPart_assign:
            { assign -= value; }
            break;
        case ECustomDataPart_item:
            { item -= value; }
            break;
        case ECustomDataPart_status:
            { status -= value; }
            break;
        case ECustomDataPart_skill:
            { skill -= value; }
            break;
        case ECustomDataPart_title:
            { title -= value; }
            break;
        case ECustomDataPart_pet:
            { pet   -= value; }
            break;
        case ECustomDataPart_suit:
            { suit  -= value; }
            break;
		case ECustomDataPart_hero:
			{ hero  -= value; }
			break;
		case ECustomDataPart_lieutenant:
			{ lieutenant  -= value; }
			break;
        case ECustomDataPart_final:
            { final -= value; }
            break;
        default:
            { assert( !"SBaseAttrType no this part " ); }
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
        case ECustomDataPart_assign:
            { assign = 0; }
            break;
        case ECustomDataPart_item:
            { item = 0; itemPer = 0; }
            break;
        case ECustomDataPart_status:
            { status = 0; statusPer = 0;}
            break;
        case ECustomDataPart_skill:
            { skill = 0; skillPer = 0; }
            break;
        case ECustomDataPart_title:
            { title = 0; titlePer = 0; }
            break;
        case ECustomDataPart_pet:
            { pet = 0;  petPer = 0; }
            break;
        case ECustomDataPart_suit:
            { suit = 0; suitPer = 0; }
            break;
		case ECustomDataPart_hero:
			{ hero = 0; heroPer = 0; }
			break;
		case ECustomDataPart_lieutenant:
			{ lieutenant =0; lieutenantPer = 0; }
			break;
        case ECustomDataPart_final:
            { final = 0; }
            break;
        default:
            { assert( !"SBaseAttrType no this part " ); }
            break;
        }
    }


    void UpdateFinal()
    {
        int32 tFinalPer = itemPer + statusPer + skillPer + titlePer + petPer + suitPer + lieutenantPer;
        int32 tFinal = base + assign + item + status + skill + title + pet + suit + lieutenant + (int32)( (base + assign) * ( tFinalPer * DEF_PERCENT ));
		nohero_final = tFinal;
		tFinal = tFinal+tFinal*heroPer*DEF_PERCENT+hero;

        if ( tFinal > Int16AttrTypeLimit )
        { final = Int16AttrTypeLimit; }
        else if ( tFinal < 0 )
        { final = 0; }
        else
        { final = tFinal; }
    }
};

struct SUInt32AttrType
{ // HPMax MPMax
    uint32 base     ;   // 基础 +
    uint32 assign   ;   // 分配 +
    uint32 item     ;   // 道具 +
    uint16 itemPer  ;   // +
    uint32 xinfa    ;   // 心法 +
    uint16 xinfaPer ;   // +
    uint32 skill    ;   // 技能 +
    uint16 skillPer ;   // + 
    int32  status   ;   // 状态 +/-
    int16  statusPer;   // +/-
    int32  title    ;   // 称号 +/-
    int16  titlePer ;   // +/-
    uint32 pet      ;   // 宠物 +
    uint16 petPer   ;   // +
    uint32 suit;        // 套装 +
    uint16 suitPer  ;   // +
	uint32 hero;        // 主将 +
	uint16 heroPer  ;   // +

	uint32 lieutenant	;   // 副将
	uint16 lieutenantPer;   // 副将 百分比

    uint32 final    ;   // +

    SUInt32AttrType()
    { 
        memset( this, 0, sizeof( SUInt32AttrType ));
    }

    void Reset()
    {
        memset( this, 0, sizeof( SUInt32AttrType )); 
    }

    void AddPartValue( uint16 part, int32 value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base += value; }
            break;
        case ECustomDataPart_assign:
            { assign += value; }
            break;
        case ECustomDataPart_item:
            { item += value; }
            break;
        case ECustomDataPart_xinfa:
            { xinfa += value; }
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
        case ECustomDataPart_pet:
            { pet += value; }
            break;
        case ECustomDataPart_suit:
            { suit  += value; }
            break;
		case ECustomDataPart_hero:
			{ hero  += value; }
			break;
		case ECustomDataPart_lieutenant:
			{
				lieutenant += value;
			}
			break;
        case ECustomDataPart_final:
            { final += value; }
            break;
        default:
            { assert( !"SUInt32AttrType no this part " ); }
            break;
        }
    }

    void SubPartValue( uint16 part, int32 value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base -= value; }
            break;
        case ECustomDataPart_assign:
            { assign -= value; }
            break;
        case ECustomDataPart_item:
            { item -= value; }
            break;
        case ECustomDataPart_xinfa:
            { xinfa -= value; }
            break;
        case ECustomDataPart_status:
            { status -= value; }
            break;
        case ECustomDataPart_skill:
            { skill -= value; }
            break;
        case ECustomDataPart_title:
            { title -= value;  }
            break;
        case ECustomDataPart_pet:
            { pet -= value; }
            break;
        case ECustomDataPart_suit:
            { suit  -= value; }
            break;
		case ECustomDataPart_hero:
			{ hero  -= value; }
			break;
		case ECustomDataPart_lieutenant:
			{
				lieutenant -= value;
			}
			break;
        case ECustomDataPart_final:
            { final -= value; }
            break;
        default:
            { assert( !"SUInt32AttrType no this part " ); }
            break;
        }
    }

    void UpdateFinal()
    {
        int32 tFinalPer = itemPer + xinfaPer + statusPer + skillPer + titlePer + petPer + suitPer + heroPer + lieutenantPer;
        int32 tFinal =  base + assign + xinfa + item + status + skill + title + pet + suit + hero + lieutenant + (int32)((base + assign) * ( tFinalPer * DEF_PERCENT) ); 
        if ( tFinal > Int32AttrTypeLimit )
        { final = Int32AttrTypeLimit; }
        else if ( tFinal < 1 )
        { final = 1; }
        else
        { final = tFinal; }
    }
};

struct SFloatAttrType
{ // 物攻 魔攻 攻击速度 物防 魔防
    float  base     ; // +
    float  assign   ; // +
    float  item     ; // +
    int16  itemPer  ; // +
    float  xinfa    ; // +
    int16  xinfaPer ; // +
    float  skill    ; // +
    int16  skillPer ; // +
    float  status   ; // +/-
    int16  statusPer; // +/-
    float  title    ; // +/-
    int16  titlePer ; // +/-
    float  pet      ; // +
    int16  petPer   ; // +
    float  suit     ; // +
    int16  suitPer  ; // +
	float  hero     ; // +
	int16  heroPer  ; // +
	
	float lieutenant	;   // 副将
	uint16 lieutenantPer;   // 副将 百分比

    float  final    ;

    SFloatAttrType()
    { 
        memset( this, 0, sizeof( SFloatAttrType )); 
    }

    void Reset()
    {
        memset( this, 0, sizeof( SFloatAttrType )); 
    }

    void AddPartValue( uint16 part, float value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base += value; }
            break;
        case ECustomDataPart_assign:
            { assign += value; }
            break;
        case ECustomDataPart_item:
            { item += value; }
            break;
        case ECustomDataPart_xinfa:
            { xinfa += value; }
            break;
        case ECustomDataPart_skill:
            { skill += value; }
            break;
        case ECustomDataPart_status:
            { status += value; }
            break;
        case ECustomDataPart_title:
            { title += value;  }
            break;
        case ECustomDataPart_pet:
            { pet += value; }
            break;
        case ECustomDataPart_suit:
            { suit  += value; }
            break;
		case ECustomDataPart_hero:
			{ hero  += value; }
			break;
		case ECustomDataPart_lieutenant:
			{
				lieutenant += value;
			}
			break;
        case ECustomDataPart_final:
            { final += value; }
            break;
        default:
            { assert( !"SFloatAttrType no this part " ); }
            break;
        }
    }

    void SubPartValue( uint16 part, float value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base -= value; }
            break;
        case ECustomDataPart_assign:
            { assign -= value; }
            break;
        case ECustomDataPart_item:
            { item -= value; }
            break;
        case ECustomDataPart_xinfa:
            { xinfa -= value; }
            break;
        case ECustomDataPart_skill:
            { skill -= value; }
            break;
        case ECustomDataPart_status:
            { status -= value; }
            break;
        case ECustomDataPart_title:
            { title -= value;  }
            break;
        case ECustomDataPart_pet:
            { pet   -= value; }
            break;
        case ECustomDataPart_suit:
            { suit  -= value; }
            break;
		case ECustomDataPart_hero:
			{ hero  -= value; }
			break;
		case ECustomDataPart_lieutenant:
			{
				lieutenant -= value;
			}
			break;
        case ECustomDataPart_final:
            { final -= value; }
            break;
        default:
            { assert( !"SFloatAttrType no this part " ); }
            break;
        }
    }

    void UpdateFinal()
    {
        int32 tFinalPer = xinfaPer + itemPer + statusPer + skillPer + titlePer + petPer + suitPer + heroPer + lieutenantPer;
        float tFinal = base + assign + item  + xinfa + skill + status + title + pet + suit + hero + lieutenant +( base + assign ) * ( tFinalPer * DEF_PERCENT ); 
        if ( tFinal > FloatAttrTypeLimit )
        { final = FloatAttrTypeLimit; }
        else if ( tFinal < 0.0f )
        { final = 0.0f; }
        else
        { final = tFinal; }
    }
};

struct SUInt16AttrType
{
    uint16 base  ;
    uint16 assign;
    uint16 item  ;
    uint16 xinfa ;
    int16  status;
    int16  title ;
    uint16 skill ;
    uint16 pet   ;
    uint16 suit  ;
	uint16 hero  ;
	uint16 lieutenant;

    uint16 final ;

    SUInt16AttrType()
    { memset( this, 0, sizeof( SUInt16AttrType ));}

    void AddPartValue( uint16 part, int16 value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base += value; }
            break;
        case ECustomDataPart_assign:
            { assign += value; }
            break;
        case ECustomDataPart_item:
            { item += value; }
            break;
        case ECustomDataPart_xinfa:
            { xinfa += value; }
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
        case ECustomDataPart_pet:
            { pet   += value; }
            break;
        case ECustomDataPart_suit:
            { suit  += value; }
            break;
		case ECustomDataPart_hero:
			{ hero  += value; }
			break;
		case ECustomDataPart_lieutenant:
			{
				lieutenant += value;
			}
			break;
        case ECustomDataPart_final:
            { final += value; }
            break;
        default:
            { assert( !"SUInt16AttrType no this part " ); }
            break;
        }
    }

    void SubPartValue( uint16 part, int16 value )
    {
        switch ( part )
        {
        case ECustomDataPart_base:
            { base -= value; }
            break;
        case ECustomDataPart_assign:
            { assign -= value; }
            break;
        case ECustomDataPart_item:
            { item -= value; }
            break;
        case ECustomDataPart_xinfa:
            { xinfa -= value; }
            break;
        case ECustomDataPart_status:
            { status -= value; }
            break;
        case ECustomDataPart_skill:
            { skill -= value; }
            break;
        case ECustomDataPart_title:
            { title -= value;  }
            break;
        case ECustomDataPart_pet:
            { pet   -= value; }
            break;
        case ECustomDataPart_suit:
            { suit  -= value; }
            break;
		case ECustomDataPart_hero:
			{ hero  -= value; }
			break;
		case ECustomDataPart_lieutenant:
			{
				lieutenant -= value;
			}
			break;
        case ECustomDataPart_final:
            { final -= value; }
            break;
        default:
            { assert( !"SUInt16AttrType no this part " ); }
            break;
        }
    }

    void UpdateFinal()
    {
        int32 nFinal = base + assign + item + xinfa + status + skill + title + pet + suit + hero + lieutenant;
        if ( nFinal > Int16AttrTypeLimit )
        { final = Int16AttrTypeLimit; }
        else if ( nFinal < 0 )
        { final = 0; }
        else
        { final = nFinal; }
    }
};

// 角色的一级属性 用于运行时结构
struct SCharBaseAttr
{
    SBaseAttrType baseAttrValue[EBaseAttr_MaxSize]; // 属性值

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
    SUInt32AttrType     hpMax            ; // HP上限
    SUInt32AttrType     mpMax            ; // MP上限
    SFloatAttrType      attackPhysics    ; // 物理攻击力
    SFloatAttrType      attackMagic      ; // 魔法攻击力 
    SFloatAttrType      defendPhysics    ; // 物理防御
    SFloatAttrType      defendMagic      ; // 魔法防御
    SFloatAttrType      attackSpeed      ; // 攻击速度
    SFloatAttrType      moveSpeed        ; // 移动速度
    SFloatAttrType      hpRestore        ; // HP恢复
    SFloatAttrType      mpRestore        ; // MP恢复
    SUInt32AttrType     exact            ; // 命中率
    SUInt32AttrType     dodge            ; // 闪避率
    SFloatAttrType      critical         ; // 暴击率 
    SFloatAttrType      tenacity         ; // 韧性  
    SUInt16AttrType     criticalIntensity; // 暴击伤害
    SUInt16AttrType     backStrike       ; // 背击伤害
    SUInt16AttrType     backStrikeResist ; // 背击抗性
    SUInt16AttrType     breakStrike      ; // 破甲伤害
    SUInt16AttrType     stabStrike       ; // 贯穿伤害
    SUInt16AttrType     elementStrike    ; // 元素伤害
    SUInt16AttrType     toxinStrike      ; // 毒素伤害
    SUInt16AttrType     spiritStrike     ; // 精神伤害
    SUInt16AttrType     breakResist      ; // 破甲抗性
    SUInt16AttrType     stabResist       ; // 贯穿抗性
    SUInt16AttrType     elementResist    ; // 元素抗性
    SUInt16AttrType     toxinResist      ; // 毒素抗性
    SUInt16AttrType     spiritResist     ; // 精神抗性
};

struct SBaseProperty
{
    SCharBaseAttr  baseAttr ;  // 一级属性
    SCharFightAttr fightAttr;  // 二级属性
};

struct SCharAttributeUpdate
{
    uint16     strength         ; // 力量
    uint16     agility          ; // 敏捷
    uint16     stamina          ; // 耐力
    uint16     intelligence     ; // 灵力
    uint32     hpMax            ; // HP上限
    uint32     mpMax            ; // MP上限
    float      attackPhysics    ; // 物理攻击力
    float      attackMagic      ; // 魔法攻击力 
    float      defendPhysics    ; // 物理防御
    float      defendMagic      ; // 魔法防御
    float      attackSpeed      ; // 攻击速度
    float      moveSpeed        ; // 移动速度
    float      hpRestore        ; // HP恢复
    float      mpRestore        ; // MP恢复
    uint32     exact            ; // 命中率
    uint32     dodge            ; // 闪避率
    float      critical         ; // 暴击率
    float      tenacity         ; // 韧性
    uint16     criticalIntensity; // 暴击伤害
    uint16     backStrike       ; // 背击伤害
    uint16     backStrikeResist ; // 背击抗性
    uint16     breakStrike      ; // 破甲伤害
    uint16     stabStrike       ; // 贯穿伤害
    uint16     elementStrike    ; // 元素伤害
    uint16     toxinStrike      ; // 毒素伤害
    uint16     spiritStrike     ; // 精神伤害
    uint16     breakResist      ; // 破甲抗性
    uint16     stabResist       ; // 贯穿抗性
    uint16     elementResist    ; // 元素抗性
    uint16     toxinResist      ; // 毒素抗性
    uint16     spiritResist     ; // 精神抗性
};

#pragma pack ( pop )
#pragma warning ( pop )

#endif // __COMMON_GAMEDEFINECHAR_H__
