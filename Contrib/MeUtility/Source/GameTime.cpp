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

//�Ƿ�ʱ�� �ֻأ�tickԼÿ49���0��
//static DWORD g_bIsTimeReset = false;

void GameTime::MyGetCurrentTime(void)
{
	if( 0 == g_dwCurrentTime )
		g_time.time = 0;

	g_dwLastTime = g_dwCurrentTime;

	//g_dwCurrentTime = ::GetTickCount();
	g_dwCurrentTime = HQ_TimeGetTime();
	g_time.dword2.dw0 = g_dwCurrentTime;
	
	//�ع�
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
        // �����ǰʱ��С�� 60000, ���� n64DeadTime > 0xffff0000 ˵������������ʱ���Ѿ���ʼ�ֻ���, ���ʱ��Ҫ���⴦����
        n64CurrentTime += ULONG_MAX;        // ����һ�����unsigned longֵ
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
     // �ȼ����ȥ��ʱ��
    unsigned int dwPassTime = GetPassTime( dwCurrentTime, dwLastTime );

    // ���ڲż���
    DWORD dwLeftTime = 0;
    if ( dwKeepTime > dwPassTime )
    {
        dwLeftTime = dwKeepTime - dwPassTime;
    }

    return dwLeftTime;
}