#include "GameTime.h"
#include "FuncPerformanceLog.h"

static DWORD g_dwCurrentTime = 0;
static DWORD g_dwLastTime = 0;

struct S2DWORD
{
	DWORD dw0,dw1;
};
static union unionTime 
{
	GameTime::Time64 time;
	S2DWORD dword2;
}
g_time; 

//是否时间 轮回（tick约每49天归0）
//static DWORD g_bIsTimeReset = false;

void GameTime::MyGetCurrentTime(void)
{
	if( 0 == g_dwCurrentTime )
		g_time.time = 0;

	g_dwLastTime = g_dwCurrentTime;

	//g_dwCurrentTime = ::GetTickCount();
	g_dwCurrentTime = HQ_TimeGetTime();
	g_time.dword2.dw0 = g_dwCurrentTime;
	
	//回归
	if( g_dwLastTime > g_dwCurrentTime )
	{
		g_time.dword2.dw1 ++;
	}	
}

GameTime::Time64 GameTime::GetCurrentTime64()
{
	return g_time.time;
}

bool GameTime::IsLessOrEqualCurrentTime( Time64 n64DeadTime )
{
    return IsLessOrEqualCurrentTime( HQ_TimeGetTime(), n64DeadTime );
}

bool GameTime::IsLessOrEqualCurrentTime( DWORD dwCurrentTime, Time64 n64DeadTime )
{
    Time64 n64CurrentTime = dwCurrentTime;
    if( n64CurrentTime < 60000 && n64DeadTime > 0xffff0000 )
    { 
        // 如果当前时间小于 60000, 并且 n64DeadTime > 0xffff0000 说明服务器运行时间已经开始轮回了, 这个时候要特殊处理呢
        n64CurrentTime += ULONG_MAX;        // 加上一个最大unsigned long值
    }

    return n64CurrentTime >= n64DeadTime;
}

bool GameTime::IsOverDeadLine( Time64 deadTime )
{
    return IsLessOrEqualCurrentTime( deadTime );
}

bool GameTime::IsOverDeadLine( DWORD dwCurrentTime, Time64 n64DeadTime )
{
    return IsLessOrEqualCurrentTime( dwCurrentTime, n64DeadTime );
}

bool GameTime::IsPassCurrentTime( DWORD dwBaseTime, DWORD dwKeepTime )
{
    return IsOverDeadLine( ( Time64 )dwBaseTime + ( Time64 )dwKeepTime );
}

bool GameTime::IsPassCurrentTime( DWORD dwCurrentTime, DWORD dwBaseTime, DWORD dwKeepTime )
{
    return IsOverDeadLine( dwCurrentTime, ( Time64 )dwBaseTime + ( Time64 )dwKeepTime );
}


DWORD GameTime::GetPassTime( DWORD dwCurrentTime, DWORD dwLastTime )
{
    unsigned int dwPassTime = 0;
    if ( dwCurrentTime >= dwLastTime )
    {
        dwPassTime = dwCurrentTime - dwLastTime; 
    }
    else
    {
        dwPassTime = ULONG_MAX - dwLastTime + dwCurrentTime;  
    }

    return dwPassTime;
}

DWORD GameTime::GetLeftKeepTime( DWORD dwCurrentTime, DWORD dwLastTime, DWORD dwKeepTime )
{
     // 先计算过去的时间
    unsigned int dwPassTime = GetPassTime( dwCurrentTime, dwLastTime );

    // 大于才计算
    DWORD dwLeftTime = 0;
    if ( dwKeepTime > dwPassTime )
    {
        dwLeftTime = dwKeepTime - dwPassTime;
    }

    return dwLeftTime;
}