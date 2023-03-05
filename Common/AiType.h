#pragma once

enum EnumMoveAIType
{
	eMAIT_DirectlyPathFinder = 1 ,				//不知道拐弯的
	eMAIT_DirectlyAddAStarPathFinder,			//知道拐弯的
	eMAIT_DirectlyNoBlockPathFinder,			//无视阻挡的
	eMAIT_MAX,
};

enum EnumAttackAIType
{
	eAAIT_AttackFirstTarget = 1,				//攻击最先发现的
	eAAIT_AttackPassive,						//被动攻击
	eAAIT_AttackLowPhysicDef,					//攻击最低物防的
	eAAIT_AttackLowMagicDef,					//攻击最低魔防的
	eAAIT_AttackHighPhysicAtk,					//攻击最高物攻的
	eAAIT_AttackHighMagicAtk,					//攻击最高魔攻的
	eAAIT_MAX,
};

enum EnumIdleAIType
{
	eIAIT_IdleMoveLowRate = 1,				//在区域内偶尔闲逛
	eIAIT_IdleMoveMiddleRate,				//在区域内时常闲逛
	eIAIT_IdleMoveHighRate,					//在区域内频繁闲逛
	eIAIT_MAX,
};

enum EnumSpecialAIType
{
    eSAIT_NoSpecialAI = 1,						//无特殊AI
	eSAIT_AlarmWhenBeAttack,					//受到攻击时向周围发出警报
	eSAIT_MAX,
};