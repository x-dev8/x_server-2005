#ifndef __LEVELLIMITCENTERMANAGER_H__
#define __LEVELLIMITCENTERMANAGER_H__

#include "LevelLimitDefine.h"
#include "LevelLimitConfig.h"
#include "LevelLimitMessage.h"
#include "GameTimer.h"

class CLevelLimitCenterManager
{
public:
	CLevelLimitCenterManager();
	~CLevelLimitCenterManager();

	static CLevelLimitCenterManager& Instance()
	{
		static CLevelLimitCenterManager cllcm;
		return cllcm;
	}

	void ProceeMySqlData(MsgAckMySQLData* pData);
	bool InitLevelLimit(SLevelLimitInfo* pLLInfo,int last_done_level = 0);

	void ProcessActiveLimit();                                //处理激活的封印
	void AddPlayer(int add_count);                            //增加到达等级数量
	void ActiveLimit(const char* player_name);                //请求激活封印
	bool IsInit(){return isInit;}
	void RunUpdate(unsigned int nCurrentTime);
	void UpdateToMySql();
	void SendLevelLimitInfoToAllGame();
	// 开启保存数据入库定时器
	void StartSaveTimer( unsigned int nCurrentTime );
	void UpdatePlayerCount2GS();
	Msg2AllGameInfo* GetLimitInfoToGame(Msg2AllGameInfo& allgame);
private:
	short           limit_state;   //封印状态
	short			player_count;  //到达等级要求的player数量
	short			trigger_lv;    //触发封印的等级
	short           trigger_count; //触发封印的player数量
	short           per_count;     //每增加多少个player,状态改变:比如时间	
	unsigned long   active_time;   //激活时间
	unsigned long   done_time;     //解除时间
	unsigned long   time_max;      //最大持续时间
	unsigned long   time_min;      //最小持续时间
	char            active_name[eLimitGlobal_name];   //激活封印的角色名字
	bool            isInit;        //是否初始化
	GameTimerEx     m_saveLevelLimitTime;       // 保存封印Timer
};

#define  theLevelLimitCenterManager CLevelLimitCenterManager::Instance()

#endif