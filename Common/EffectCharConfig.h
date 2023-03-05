#ifndef __EFFECTCHARCONFIG_H__
#define __EFFECTCHARCONFIG_H__

#pragma once

#include <string>
#include <vector>
#include <map>
#include "GlobalDef.h"

#define theEffectCharConfig EffectCharConfig::Instance()   //ʵ���ӿ�

enum EFFECTCHAR_AI_TYPE
{
	AI_NO = 0, //û��ai ԭ�ز���
	AI_FlowMaster , //��������
	AI_FlowAttackTarget, //���湥��Ŀ��
	AI_FindNearTarget,  //���Ѱ����Χ����Ŀɹ���Ŀ�� ���˺�����
	AI_CanBeAttack,      //���Ա�����
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
	int  SkillID;        //����id
	int  OnDeadUseSkill; //������ʱ��ʹ�õļ���
	int  OnDeadUseSkillLevel; //������ʱ��ʹ�õļ���id
	int  moveSpeed;      //�ƶ��ٶ�
	int  SummonCnt;      //�ٻ�����
	int  ModelID;        //ģ��id
	int  WaitTime;       //ԭ��ͣ��ʱ�䣬ֻ��Ը���ɹ���Ŀ�� �� Ѱ�����Ŀ����Ч
	int  BeAttackDeadCnt; //��������Ҫ�����Ĵ���
	int  SummonDistince; //�ٻ���������ľ��� --ֻ���aitypeΪ0
	bool bCanBeAttack;   //�Ƿ��ܹ���
	bool bOnceAttack;    //һ�ι��� ,�Ժ��Զ�����
	bool bOnceFindeNearTarget; //�Ƿ�һ��Ѱ�����Ŀ��

	
	EFFECTCHAR_AI_TYPE AiType; //ai���� 
};

typedef std::map<int,EFFECTCHARCONFIG> MAP_EFFECTCHRCONFIG;

//װ���ӹ������ļ���
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

