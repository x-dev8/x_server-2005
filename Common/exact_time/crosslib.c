#include "crosslib.h"

#ifdef WIN32
#include <windows.h>

struct _tp_integer
{
	int isinit;
	LARGE_INTEGER liCounter;
};
static struct _tp_integer s_larget_int = {0};
static __inline signed __int64 __GetSecondCount__()
{
	if (0 == s_larget_int.isinit)
	{
		QueryPerformanceFrequency(&s_larget_int.liCounter);
		s_larget_int.isinit = 1;
	}
	return s_larget_int.liCounter.QuadPart;
}
/*
 * get current millisecond time
 */
signed __int64 high_millisecond_()
{
	LARGE_INTEGER liCurrent;
	QueryPerformanceCounter(&liCurrent);
	return ((signed __int64)(liCurrent.QuadPart * (signed __int64)1000) / __GetSecondCount__());
}

/* get current microsecond time */
signed __int64 high_microsecond_()
{
	LARGE_INTEGER liCurrent;
	QueryPerformanceCounter(&liCurrent);
	return ((signed __int64)(liCurrent.QuadPart * (signed __int64)1000000) / __GetSecondCount__());
}

void delay_delay(unsigned long millisecond)
{
	Sleep(millisecond);
}

#else

#include <string.h>
#include <sys/time.h>
#include <unistd.h>

/* get current millisecond time */
int64_t high_millisecond_()
{
	struct timeval tv;
	int64 res;
	gettimeofday(&tv, NULL);
	res = (int64_t)(tv.tv_sec * (int64_t)1000) + (int64_t)(tv.tv_usec/(int64_t)1000);
	return res;
}

/* get current microsecond time */
int64_t high_microsecond_()
{
	struct timeval tv;
	int64_t res;
	gettimeofday(&tv, NULL);
	res = (int64_t)(tv.tv_sec * (int64)1000000) + (int64_t)tv.tv_usec;
	return res;
}

void delay_delay (unsigned long millisecond)
{
	usleep(millisecond*1000);
}

#endif



