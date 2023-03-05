/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwTimer.h
* Create: 	10/06/06
* Desc:		Timerʵ��
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __SWTIMER_H__
#define __SWTIMER_H__

#include <WTypes.h>
#include "MeUtility/Singleton.h"
// ��ʱ����
#define		TIMER_PERIOD	1


class SwTimer
{
public:
	SwTimer();
	virtual ~SwTimer();


public:
	// �Ƿ�ʱ����ʾ��һ֡ ( ÿ����Ϸѭ������һ�θú�����������֡ʱGetFrames()���ݻ�� )
	bool		IsTimeShowNextFrame();

	// ���ֿ�ʼ��ʱ����֡��
	void		ResetTimer();

	// ����/ȡ��Ҫ������֡��( 0Ϊ����֡ )
	void		SetFrameControl( int iFps );
	int			GetFrameControl()			{ return m_keepFps; }

	// ȡ�����ŵ���ʱ�䣬��֡���ʱ���
	float		GetTimeTotal()				{ return m_timeTotal; }
	float		GetTimeDelta()				{ return m_timeDelta; }

	float		GetTimeCur();

	// ȡ�����й�����֡��
	DWORD		GetFrames()					{ return m_frames; }


protected:
	void		UpdateFrame();		// ���µ�ǰ֡������������֡���ʱ��� m_fTimeDelta


protected:
	// ֡�ٿ��Ʊ���
	int				m_keepFps;						// ��Ҫ������֡�� ( 0Ϊ����֡ )
	float			m_nextFrameTime;				// ��һ֡�����ۿ�ʼʱ��
	float			m_nextFrameWaitTime;			// ��֮֡�������ȴ�ʱ��

	float			m_timeTotal;					// ���ŵ��ܹ�ʱ��
	float			m_timeDelta;					// ��һ֡����һ֡���ʱ���
	float			m_timeLast;						// ��һ֡��ʱ��
	DWORD			m_frames;						// ��Ϸ���е��ܹ�֡��

	int				m_timePeriod;					// ��ǰTimePeriod
	DWORD			m_performanceFrequency;			// �������߽��ȼ�ʱ��Ƶ��
	LARGE_INTEGER	m_performanceCounterZero;		// Timer��ʼʱ��ʱ������
	DWORD			m_tickcountZero;				// Timer��ʼʱ��ʱ��(���ڸ߾��ȼ�ʱ��ʧ��ʱ)

};


#endif	//__SWTIMER_H__