/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwTimer.h
* Create: 	10/06/06
* Desc:		Timer实现
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __SWTIMER_H__
#define __SWTIMER_H__

#include <WTypes.h>
#include "MeUtility/Singleton.h"
// 计时精度
#define		TIMER_PERIOD	1


class SwTimer
{
public:
	SwTimer();
	virtual ~SwTimer();


public:
	// 是否到时间显示下一帧 ( 每次游戏循环调用一次该函数，否则不锁帧时GetFrames()数据会错 )
	bool		IsTimeShowNextFrame();

	// 重现开始记时，记帧数
	void		ResetTimer();

	// 设置/取得要锁定的帧数( 0为不锁帧 )
	void		SetFrameControl( int iFps );
	int			GetFrameControl()			{ return m_keepFps; }

	// 取得流逝的总时间，上帧间的时间差
	float		GetTimeTotal()				{ return m_timeTotal; }
	float		GetTimeDelta()				{ return m_timeDelta; }

	float		GetTimeCur();

	// 取得运行过的总帧数
	DWORD		GetFrames()					{ return m_frames; }


protected:
	void		UpdateFrame();		// 更新当前帧数，并计算两帧间的时间差 m_fTimeDelta


protected:
	// 帧速控制变量
	int				m_keepFps;						// 需要锁定的帧数 ( 0为不锁帧 )
	float			m_nextFrameTime;				// 下一帧的理论开始时间
	float			m_nextFrameWaitTime;			// 两帧之间的理想等待时间

	float			m_timeTotal;					// 流逝的总共时间
	float			m_timeDelta;					// 上一帧和这一帧间的时间差
	float			m_timeLast;						// 上一帧的时间
	DWORD			m_frames;						// 游戏进行的总共帧数

	int				m_timePeriod;					// 当前TimePeriod
	DWORD			m_performanceFrequency;			// 处理器高进度计时器频率
	LARGE_INTEGER	m_performanceCounterZero;		// Timer开始时的时钟周期
	DWORD			m_tickcountZero;				// Timer开始时的时间(用于高精度计时器失败时)

};


#endif	//__SWTIMER_H__