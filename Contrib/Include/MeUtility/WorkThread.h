/********************************************************************
    Filename:    WorkThread.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_WORKTHREAD_H__
#define __UTILITY_WORKTHREAD_H__

#pragma once

#include "MeRTLibs.h"

class CWorkThread
{ //工作线程
public:
    typedef void (* t_fnThreadFuncOneStep )(void*lpVoid );

public:
    CWorkThread();
    virtual ~CWorkThread();
    virtual void Run(){}
    virtual bool CreateThread( t_fnThreadFuncOneStep fn,void *lpData = 0,int iPriority = THREAD_PRIORITY_NORMAL );

    bool  IsStop(){ return m_bStop; }	
    void  SetDead(){ m_bDead = true; }
    void  SetPause( bool bPause );
    void* GetData(){ return m_lpData;}
    void  RunOneStep();
    
    bool  CreateThread1(void *lpData = 0); // 使用下面函数创建线程的，必须继承CWorkThread,重载虚函数Run
    void  StopThreadAndWaitDead();         // 由创建线程调用，关闭线程并等待结束
    void  Stop(){ m_bStop = true;SetPause( false );}

    DWORD GetThreadID() { return m_dwThreadID; }
    void  SetThreadID( DWORD threadId ) { m_dwThreadID = threadId;}

    int   GetThreadPriority() { return m_iPriority; }
protected:
    bool volatile m_bStop;
    bool volatile m_bDead;
    bool volatile m_bPause;
    DWORD m_dwThreadID;

    t_fnThreadFuncOneStep m_pThreadFunc;
	
    friend void ThreadFunc( void *lpVoid );
    int			m_iPriority;
    void		*m_lpData;
    HANDLE		m_hThread;
};

inline 
void CWorkThread::SetPause( bool bPause )
{ 
    m_bPause = bPause; 
    if( m_bPause )
    {
        SetThreadPriority( m_hThread,THREAD_PRIORITY_IDLE );
    }
    else
    {
        SetThreadPriority( m_hThread,m_iPriority );
    }
}

#endif // __UTILITY_WORKTHREAD_H__
