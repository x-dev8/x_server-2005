/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwTimer.cpp
* Create: 	10/06/06
* Desc:		Timerʵ��
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
//��Ա��������
////////////////////////////////////////////////////////////////////////////////
SwTimer::SwTimer()
{
	// ���ü�ʱ����
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

	// ��ʼ����ȷ��ʱ��
	LARGE_INTEGER li;
	if( QueryPerformanceFrequency(&li) )
		m_performanceFrequency = (DWORD)( li.QuadPart );
	else
		m_performanceFrequency = 0;

	// ������֡����
	m_keepFps				= 0;
	m_nextFrameWaitTime	= 0.0f;

	// �� 0 ��ʱ����
	ResetTimer();
}

SwTimer::~SwTimer()
{
	// �ظ�ʱ�侫��
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
	// �õ���ȷ�ĵ�ǰʱ�䣬ת��Ϊ����
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
		return true;	// ��ʹ��֡�ٿ���
	}


	if( m_timeTotal < m_nextFrameTime )
	{
		// ʱ��û��
		// �ȴ�ʱ�䳬��2ms����˯��1ms������CPUռ��ʱ��
		if( m_nextFrameTime - m_timeTotal > 0.002f )
		{
			Sleep(1);
		}

		return false;
	}

	// ������һ֡������ʱ��
	while ( m_nextFrameTime <= m_timeTotal )
	{
		m_nextFrameTime += m_nextFrameWaitTime;
	}

	// ����fps
	UpdateFrame();
	return true;
}

void SwTimer::UpdateFrame()
{
	++m_frames;

	// ������֡���ʱ���
	m_timeDelta = m_timeTotal-m_timeLast;
	m_timeLast  = m_timeTotal;
}

////////////////////////////////////////////////////////////////////////////////
// end of file
////////////////////////////////////////////////////////////////////////////////