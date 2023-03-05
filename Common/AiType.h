#pragma once

enum EnumMoveAIType
{
	eMAIT_DirectlyPathFinder = 1 ,				//��֪�������
	eMAIT_DirectlyAddAStarPathFinder,			//֪�������
	eMAIT_DirectlyNoBlockPathFinder,			//�����赲��
	eMAIT_MAX,
};

enum EnumAttackAIType
{
	eAAIT_AttackFirstTarget = 1,				//�������ȷ��ֵ�
	eAAIT_AttackPassive,						//��������
	eAAIT_AttackLowPhysicDef,					//������������
	eAAIT_AttackLowMagicDef,					//�������ħ����
	eAAIT_AttackHighPhysicAtk,					//��������﹥��
	eAAIT_AttackHighMagicAtk,					//�������ħ����
	eAAIT_MAX,
};

enum EnumIdleAIType
{
	eIAIT_IdleMoveLowRate = 1,				//��������ż���й�
	eIAIT_IdleMoveMiddleRate,				//��������ʱ���й�
	eIAIT_IdleMoveHighRate,					//��������Ƶ���й�
	eIAIT_MAX,
};

enum EnumSpecialAIType
{
    eSAIT_NoSpecialAI = 1,						//������AI
	eSAIT_AlarmWhenBeAttack,					//�ܵ�����ʱ����Χ��������
	eSAIT_MAX,
};