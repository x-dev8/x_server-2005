#include "Timestamp.h"
#include <time.h>
#include <assert.h>

CTimestamp::CTimestamp(void)
{
}

CTimestamp::~CTimestamp(void)
{
}

unsigned long CTimestamp::GetTimestamp()
{
	time_t tt;
	time(&tt);
	if (tt < 0)
	{
		assert(false);
	}
	return tt;
}

char* CTimestamp::GetTimeByTimestamp(unsigned long tt)
{
	if (tt <= 0)
	{
		return NULL;
	}
	time_t tt_temp;
	char now[64];
	struct tm *ttime;
	tt_temp = tt;
	ttime = localtime(&tt_temp);
	strftime(now,64,"%Y-%m-%d %H:%M:%S",ttime);
	return now;
}