#ifndef _SEVENDAYMANAGER_
#define _SEVENDAYMANAGER_

#include "MeRTLibs.h"

class GamePlayer;
class SevenDayManager
{
public:
	enum TaskState
	{
		TS_UnStart,		//未开启
		TS_CanGain,		//可接取
		TS_UnderWay,	//进行中
		TS_DoneUnGet,	//已完成，但未领取奖励
		TS_DoneGet,		//已完成
	};

	SevenDayManager();
	virtual ~SevenDayManager();

	void SetOwner( GamePlayer* pGamePlayer ) { pOwner = pGamePlayer;}

	bool IsInTask(int taskID); //是否任务进行中

	bool IsCanGainTask(int index); //能否接取

	bool GainTask(int index); //领取任务

	short GetTaskState(int index);
	void SetTaskState(int index, short state); //设置任务状态

	short GetTaskVar(int index);
	void SetTaskVar(int index, short var);

	bool GainReward(int index); //领取奖励

	void TriggerSevenDaysVar(int index, int nvalue = 0);

	void TriggerFirstDayVar(int index);
	void TriggerSecondDayVar(int index, int questID);
	void TriggerThirdDayVar(int index, int nvar);
	void TriggerFourthDayVar(int index);
	void TriggerFifthDayVar(int index);
	void TriggerSixthDayVar(int index);
	void TriggerSeventhDayVar(int index);

	int GetDayTime( __time64_t startTime, __time64_t nowTime ); //获取过了几天

private:
	GamePlayer* pOwner;
};

#endif //_SEVENDAYMANAGER_