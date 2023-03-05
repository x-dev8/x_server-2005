/********************************************************************
	Filename: 	TimeClock.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_HRCTIMECLOCK_H__
#define __UTILITY_HRCTIMECLOCK_H__

#pragma once

#include "MeRTLibs.h"

//����˵����ǰʱ��
class TimeClock
{
    enum enumConst
    {
        const_iFullTimeCircle = 24*60*60
    };

    DWORD m_dwLastUpdate;
    DWORD m_dwTime;
    int	  m_iTimeFactor;
    int	  m_iUpdateInterval;
    DWORD m_dwCaluRest;	
public:
    TimeClock(void);
    ~TimeClock(void);

    void SetCurrentTime( DWORD dwTime );

    //��ʵÿ���Ӧ��Ϸ�೤ʱ�䣨�룩
    void SetTimeFactor( int iTimeFactor )
    {
        if( iTimeFactor <= 0 )
            return;
        m_iTimeFactor = iTimeFactor;
        m_iUpdateInterval = 1000 / iTimeFactor;
    }

    void Update( void );
    DWORD GetCurTime( void )
    {
        return m_dwTime;
    }
};

#endif //__UTILITY_HRCTIMECLOCK_H__
