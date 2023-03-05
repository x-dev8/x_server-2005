#pragma once

#define PER_SPACE_TIME 60 * 1000
#include "AttackBot.h"


class CNormalBot : public CAttackBot
{
public:
	CNormalBot(void);
	virtual ~CNormalBot(void);

	virtual void PlayGame();

	virtual void InitPlayGame(UINT mapid = 0);

	virtual bool LoginOutGame();
	virtual bool RandFlyToMap();
	virtual void RunTeam();

	void SetFlySpaceTime(int nSpaceTime) { m_nFlySpaceTime = nSpaceTime * 1000;}

private:
	void RandLoginOutSpaceTime();

private:	
	DWORD m_dwLoginOutSpace;		//机器人登出游戏的间隔时间
	DWORD m_dwNextRunTimeSpace;			

	DWORD m_dwStartPlayTime;

	int m_nFlySpaceTime;	//飞行时间间隔
	DWORD m_dwLastFlyTime;  //上次飞行时间

};
