#ifndef _BASEINFO_H
#define _BASEINFO_H
#include "Bot.h"
#include "GameBot.h"

class BaseInfo
{
public:
	BaseInfo(){};
	virtual ~BaseInfo(){};

public:
	virtual void InitInformation(){};
	virtual void UpdateInformation(BaseRobot *pBot) = 0;
};
#endif