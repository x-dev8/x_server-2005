/********************************************************************
	Filename: 	FlyBot.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __BOT_FLYBOT_H__
#define __BOT_FLYBOT_H__

#pragma once

#include "Bot.h"
#include "MeRTLibsServer.h"

class CFlyBot : public BaseRobot
{
public:
    CFlyBot();
    virtual ~CFlyBot();

    virtual void PlayGame();

	void PlayFly();
	void SetFlySpaceTime(int nSpaceTime) { m_nFlySpaceTime = nSpaceTime * 1000;}

private:
	unsigned int m_dwLastFlyTime;
	int m_nFlySpaceTime;
};

#endif // __BOT_FLYBOT_H__

