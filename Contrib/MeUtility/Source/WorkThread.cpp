#include "WorkThread.h"
#pragma warning ( push, 0 )
#include "FuncPerformanceLog.h"
#pragma warning ( pop )
#ifndef _UINTPTR_T_DEFINED
#ifdef  _WIN64
typedef unsigned __int64    uintptr_t;
#else
typedef _W64 unsigned int   uintptr_t;
#endif
#define _UINTPTR_T_DEFINED
#endif

CWorkThread::CWorkThread()
{
	m_bDead = true;
	m_bStop = true;
	m_pThreadFunc = 0;
	m_lpData = 0;
	m_bPause = false;
    m_hThread = NULL;
    m_dwThreadID = 0;
}

CWorkThread::~CWorkThread()
{
}

static void __cdecl ThreadFunc( void *lpVoid )
{
    CoInitialize( NULL );

	CWorkThread* pThread = (CWorkThread*)lpVoid;
	if( pThread )
	{
		HANDLE hThread = GetCurrentThread();
        pThread->m_dwThreadID = GetCurrentThreadId();
		SetThreadPriority( hThread,pThread->m_iPriority );
		while(1)
		{			
			//ÍË³öÏß³Ì
			if( pThread->IsStop() )
			{	
				pThread->SetDead();
				break;
			}
			pThread->RunOneStep();
		}
	}

	CoUninitialize();

	_endthread();
}

void CWorkThread::RunOneStep()
{
	if( m_bPause )
	{
		Sleep( 1 );
		return;
	}

	if( m_pThreadFunc )
    { m_pThreadFunc( m_lpData ); }
	else
    { Run(); }
}

bool CWorkThread::CreateThread( CWorkThread::t_fnThreadFuncOneStep fn,void *lpData,int iPriority )
{
	m_bStop = false;
	m_bPause = true;
	m_pThreadFunc = fn;
	uintptr_t hThread = _beginthread( ThreadFunc,0,(void*)this );
	m_iPriority = iPriority;
	m_hThread = (HANDLE)hThread;
	if( -1 != hThread )
	{
		m_bStop = false;
		m_bDead = false;
		m_lpData = lpData;
		m_bPause = false;
		return true;
	}
	return false;
}

bool CWorkThread::CreateThread1(void *lpData)
{
	if( -1 != _beginthread( ThreadFunc,0,(void*)this ) )
	{
		m_bStop = false;
		m_bDead = false;
		m_lpData = lpData;
		return true;
	}
	return false;
}
	
void CWorkThread::StopThreadAndWaitDead()
{
	m_bStop = true;
	SetPause( false );

	DWORD dwStartTime = HQ_TimeGetTime();
	while( !m_bDead )
	{
		if(HQ_TimeGetTime() - dwStartTime > 10000)
		{
			if(TerminateThread(m_hThread,1234))
			{
				m_bDead = true;
				break;
			}
			else
			{
			}
		}
	}
}
