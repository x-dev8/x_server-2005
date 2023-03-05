/********************************************************************
    Filename:    TickTimer.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#pragma once

#include <iostream>
#include <Windows.h>

class CTickTimer
{
public:
	CTickTimer(void);
	virtual ~CTickTimer(void);

public:
	__inline unsigned __int64 GetCycleCount() 
	{ 
		__asm _emit 0x0F 
		__asm _emit 0x31 
	}

	unsigned __int64 GetCurrTick();

private:
	unsigned __int64 uCurrTime;
};
