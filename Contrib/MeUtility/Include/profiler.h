/********************************************************************
    Filename:    profiler.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_TIME_COUNTER_H__
#define __UTILITY_TIME_COUNTER_H__

#include <Wtypes.h>
#include <mmsystem.h>

class CDebugTimeCounter
{
public:
    CDebugTimeCounter()
    {
        m_dwCountTime = 0;
    }

    void Reset() {
        m_dwCountTime = 0;
    }

    void Start() {
        QueryPerformanceCounter( (LARGE_INTEGER *)&m_dwStartTime );
    }
    void Stop(){
        QueryPerformanceCounter( (LARGE_INTEGER *)&m_dwStopTime );
        m_dwCountTime = m_dwCountTime + (m_dwStopTime - m_dwStartTime);
    }

    __int64 GetTime() {
        return m_dwCountTime;
    }

private:

    __int64 m_dwCountTime;
    __int64 m_dwStartTime;
    __int64 m_dwStopTime;
};

class CDebugTimeMgr
{
public:
    CDebugTimeCounter m_All_TC;
    CDebugTimeCounter m_WinMain_TC;
    CDebugTimeCounter m_MainThread_TC;
    CDebugTimeCounter m_UpdateInterval_TC;
    CDebugTimeCounter m_MainRunAll_TC;
    CDebugTimeCounter m_Connect_TC;
    CDebugTimeCounter m_RecvAll_TC;
    CDebugTimeCounter m_SendAll_TC;
    CDebugTimeCounter m_DBProcess_TC;
    CDebugTimeCounter m_WorldProcess_TC;
    CDebugTimeCounter m_LoginProcess_TC;
    CDebugTimeCounter m_AiProcess_TC;
    CDebugTimeCounter m_RefreshMonster_TC;
};

#endif // __UTILITY_TIME_COUNTER_H__
