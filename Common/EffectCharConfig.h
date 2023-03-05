#ifndef __EFFECTCHARCONFIG_H__
#define __EFFECTCHARCONFIG_H__

#pragma once

#include <string>
#include <vector>
#include <map>
#include "GlobalDef.h"

#define theEffectCharConfig EffectCharConfig::Instance()   //实例接口

enum EFFECTCHAR_AI_TYPE
{
	AI_NO = 0, //没有ai 原地不动
	AI_FlowMaster , //跟随主人
	AI_FlowAttackTarget, //跟随攻击目标
	AI_FindNearTarget,  //随机寻找周围最近的可攻击目标 后伤害死亡
	AI_CanBeAttack,      //可以被攻击
	AI_MAX,
};


struct EFFECTCHARCONFIG
{
	EFFECTCHARCONFIG()
	{
         SkillID = -1;
		 OnDeadUseSkill = -1;
		 OnDeadUseSkillLevel = 0;
		 moveSpeed = 0;
		 SummonCnt = 1;
		 SummonDistince = 2;
		 bCanBeAttack = false;
		 bOnceAttack = false;
		 AiType = AI_NO;
		 ModelID = -1;
		 WaitTime = 0;
		 bOnceFindeNearTarget = false;
		 BeAttackDeadCnt = 1;

		 
	}
	int  SkillID;        //技能id
	int  OnDeadUseSkill; //死亡的时候使用的技能
	int  OnDeadUseSkillLevel; //死亡的时候使用的技能id
	int  moveSpeed;      //移动速度
	int  SummonCnt;      //召唤数量
	int  ModelID;        //模型id
	int  WaitTime;       //原地停留时间，只针对跟随可攻击目标 和 寻找最近目标有效
	int  BeAttackDeadCnt; //被攻击需要死亡的次数
	int  SummonDistince; //召唤怪于自身的距离 --只针对aitype为0
	bool bCanBeAttack;   //是否能攻击
	bool bOnceAttack;    //一次攻击 ,自后自动死亡
	bool bOnceFindeNearTarget; //是否一次寻找最近目标

	
	EFFECTCHAR_AI_TYPE AiType; //ai类型 
};

typedef std::map<int,EFFECTCHARCONFIG> MAP_EFFECTCHRCONFIG;

//装备加工配置文件集
class EffectCharConfig
{

public:
	static EffectCharConfig& Instance()
	{
		static EffectCharConfig s_xConfig;
		return s_xConfig;
	}

	bool LoadEffectCharConfig(const char *szFile);

	bool FindEffectCharConfigBySkillID(EFFECTCHARCONFIG &des ,int skillID);
	

private:
	MAP_EFFECTCHRCONFIG m_EffectCharConfigVec;

};

#endif

