/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwTimer.cpp
* Create: 	10/06/06
* Desc:		Timer实现
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include <MMSystem.h>
#include "SwTimer.h"

#pragma comment( lib, "Winmm.lib" )

////////////////////////////////////////////////////////////////////////////////
//成员函数定义
////////////////////////////////////////////////////////////////////////////////
SwTimer::SwTimer()
{
	// 设置计时精度
	TIMECAPS tcap;
	if( timeGetDevCaps(&tcap,sizeof(tcap)) == TIMERR_NOERROR 
		&& tcap.wPeriodMin > TIMER_PERIOD )
	{
		m_timePeriod = tcap.wPeriodMin;
	}
	else
	{
		m_timePeriod = TIMER_PERIOD;
	}

	timeBeginPeriod(m_timePeriod);

	// 初始化精确计时间
	LARGE_INTEGER li;
	if( QueryPerformanceFrequency(&li) )
		m_performanceFrequency = (DWORD)( li.QuadPart );
	else
		m_performanceFrequency = 0;

	// 设置锁帧数据
	m_keepFps				= 0;
	m_nextFrameWaitTime	= 0.0f;

	// 置 0 记时数据
	ResetTimer();
}

SwTimer::~SwTimer()
{
	// 回复时间精度
	timeEndPeriod(m_timePeriod);
}

void SwTimer::ResetTimer()
{
	QueryPerformanceCounter(&m_performanceCounterZero);
	m_tickcountZero		= GetTickCount();

	m_timeTotal			= 0.0f;
	m_timeDelta			= 0.0f;
	m_timeLast				= 0.0f;

	m_nextFrameTime		= m_nextFrameWaitTime;
}

void SwTimer::SetFrameControl( int iFps )
{
	m_keepFps = iFps;

	if ( m_keepFps > 0 )
	{
		m_nextFrameWaitTime = 1.0f/m_keepFps;
	}
}

float SwTimer::GetTimeCur()
{
	float timeCur;

	LARGE_INTEGER li;
	if( m_performanceFrequency && QueryPerformanceCounter(&li) )
	{
		timeCur = 1.0f*(li.QuadPart-m_performanceCounterZero.QuadPart)/m_performanceFrequency;
	}
	else
	{
		timeCur = 1.0f*(GetTickCount() - m_tickcountZero);
	}

	return timeCur;
}

bool SwTimer::IsTimeShowNextFrame()
{
	// 得到精确的当前时间，转换为毫秒
	LARGE_INTEGER li;
	if( m_performanceFrequency && QueryPerformanceCounter(&li) )
	{
		m_timeTotal = 1.0f*(li.QuadPart-m_performanceCounterZero.QuadPart)/m_performanceFrequency;
	}
	else
	{
		m_timeTotal = 1.0f*(GetTickCount() - m_tickcountZero);
	}
	if( m_keepFps < 1 )
	{
		UpdateFrame();
		return true;	// 不使用帧速控制
	}


	if( m_timeTotal < m_nextFrameTime )
	{
		// 时间没到
		// 等待时间超过2ms，则睡眠1ms，降低CPU占用时间
		if( m_nextFrameTime - m_timeTotal > 0.002f )
		{
			Sleep(1);
		}

		return false;
	}

	// 计算下一帧的理论时间
	while ( m_nextFrameTime <= m_timeTotal )
	{
		m_nextFrameTime += m_nextFrameWaitTime;
	}

	// 计算fps
	UpdateFrame();
	return true;
}

void SwTimer::UpdateFrame()
{
	++m_frames;

	// 计算两帧间的时间差
	m_timeDelta = m_timeTotal-m_timeLast;
	m_timeLast  = m_timeTotal;
}

////////////////////////////////////////////////////////////////////////////////
// end of file
////////////////////////////////////////////////////////////////////////////////