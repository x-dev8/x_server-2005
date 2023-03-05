#ifndef __LEVELLIMITDEFINE_H__
#define __LEVELLIMITDEFINE_H__

enum eLimitGlobal
{
	eLimitGlobal_name = 32,
	eLimitGlobal_savetime = 600000,//自动保存时间
	eLimitGlobal_DelayAck = 5000,//请求延时
};

enum eLimitState
{
	eLimitState_noActive = 0,//未激活
	eLimitState_Active = 1,//激活
	eLimitState_Done = 2,//结束
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