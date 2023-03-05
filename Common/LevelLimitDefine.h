#ifndef __LEVELLIMITDEFINE_H__
#define __LEVELLIMITDEFINE_H__

enum eLimitGlobal
{
	eLimitGlobal_name = 32,
	eLimitGlobal_savetime = 600000,//�Զ�����ʱ��
	eLimitGlobal_DelayAck = 5000,//������ʱ
};

enum eLimitState
{
	eLimitState_noActive = 0,//δ����
	eLimitState_Active = 1,//����
	eLimitState_Done = 2,//����
	eLimitState_max
};

struct SLevelLimitConfig
{
	short level;
	unsigned long time_max;
	unsigned long time_min;
	short setup_min_count;
	short per_count;
	short next_level;
};

struct SLevelLimitInfo
{
	short level;
	unsigned long active_time;
	unsigned long done_time;
	short player_count;
	short next_level;
	short state;
	char active_name[eLimitGlobal_name];
};
#endif