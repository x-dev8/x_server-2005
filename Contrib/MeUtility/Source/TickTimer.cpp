#include "TickTimer.h"

CTickTimer::CTickTimer(void)
{
	uCurrTime = GetCycleCount();
}

CTickTimer::~CTickTimer(void)
{
	uCurrTime = GetCycleCount() - uCurrTime;
	char szTime[100] = {0};
	sprintf_s(szTime, "%u Cycle\n", uCurrTime);
	OutputDebugString( szTime );
}

unsigned __int64 CTickTimer::GetCurrTick()
{
	return GetCycleCount() - uCurrTime;
}