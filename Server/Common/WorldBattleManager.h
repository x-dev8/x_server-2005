#pragma once
#include "WorldBattleConfig.h"
//世界战场 野外战场 
//1.时间更新 用于确认各个时间段战场的PK状态
//2.不同阶段的刷怪 删怪等操作
//3.对客户端额通过 和描述
class WorldBattleManager
{
public:
	enum WorldBattleStates
	{
		WBS_StatusInit = 0,		//战场初始化状态
		WBS_StatusPrepare,		//战场准备阶段
		WBS_StatusFight,		//战场开始阶段
		WBS_StatusEnd			//战场结束阶段
	};
	WorldBattleManager():m_Init(false),m_States(WBS_StatusInit){}
	~WorldBattleManager(){}
	void Init();//初始化
	void Update(unsigned int nCurrentTime);//更新
	bool LoadFilePath(const char* FilePaht);
	static WorldBattleManager& Instance()
    {
        static WorldBattleManager s_xManager;
        return s_xManager;
    }
	void SetWorldBattleIsResult();
private:
	void ProcessBattleInitStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );
	void ProcessBattlePrepareStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );
	void ProcessBattleEndStatus( unsigned int nCurrentTime, int nDayOfWeek, int nHour, int nMinute );
private:
	bool				m_Init;//是否初始化完毕
	unsigned char		m_States;
	int					m_MapPkType;
	WorldBattleConfig	m_config;
};
#define theWorldBattleManager WorldBattleManager::Instance()