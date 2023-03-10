#ifndef __LEVELLIMITGAMEMANAGER_H__
#define __LEVELLIMITGAMEMANAGER_H__
#pragma once

#include "LevelLimitDefine.h"
#include "LevelLimitMessage.h"
#include "GameTimer.h"

#define special_level 30

class CLevelLimitGameManager
{
public:
	enum eLimitAward
	{		
		eLimitAward_no = 100,//30级以下玩家属于新手阶段，没有加成
		eLimitAward_lv1 = 150,//低于封印等级10级的玩家50%经验加成
		eLimitAward_lv2 = 200,//低于封印等级20级的玩家100%的经验加成
		eLimitAward_lv3 = 300,//低于封印等级30级的玩家200%的经验加成 
		eLimitAward_maxlv = 50,//大于等于封印等级的,只获得50%的经验
	};

	enum eLimitLevel_diff
	{//与封印等级的等级差
		eLimitLevel_diff_lv1 = 10,
		eLimitLevel_diff_lv2 = 20,
		eLimitLevel_diff_lv3 = 30,		
	};
public:
	CLevelLimitGameManager(void);
	~CLevelLimitGameManager(void);

	static CLevelLimitGameManager& Instance()
	{
		static CLevelLimitGameManager cllgm;
		return cllgm;
	}

	void OnMsgLevelLimitInfo(Msg2AllGameInfo* pMsg);
	void UpdatePlayerCount(int count);
	void AddPlayerCount(int count);
	void ActiveLimitToCS(const char* player_name);
	void ReqActiveLimit(const char* player_name);

	void RunOnStep(unsigned long cur_time);

	SLevelLimitInfo* GetLevelLimitInfo(){return &sllinfo;}
	bool IsInit(){return isInit;}

	short GetLimitExpAward(short stLevel);  //封印激活期间的奖励
	short GetLimitLevel(){return sllinfo.level;}

	void CheckActiveLimit(const char* player_name);
	void StartSaveTimer( unsigned int nCurrentTime );
	void UpdateLimitState(short _state);
private:
	//bool have_send;                     //是否发送过了请求
	bool isInit;						//是否初始化
	SLevelLimitInfo sllinfo;            //等级封印信息
	GameTimerEx		m_AckTimer;         //初始化延迟请求
};
#define theLevelLimitGameManager CLevelLimitGameManager::Instance()
#endif
