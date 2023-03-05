#include "MeFoundation/MeLoopThreadProcedure.h"

MeLoopThreadProcedure::MeLoopThreadProcedure()
{
	InitializeCriticalSection( &m_MexLoadingCS );
	m_bMexLoadingThreadWillDestroy = false;
	m_bMexLoadingThreadTerminated = false;
	m_bMexLaodingThreadWillPause = false;
	m_bMexLoadingThreadPaused = false;
	m_hMexLoadingEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	m_nSpeed = 1;
}
//////////////////////////////////////////////////////////////////////////
MeLoopThreadProcedure::~MeLoopThreadProcedure()
{
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThreadProcedure::Destroy()
{
	CloseHandle( m_hMexLoadingEvent );
	ClearLoopList();
	DeleteCriticalSection( &m_MexLoadingCS );
}
//////////////////////////////////////////////////////////////////////////
// thread procedure function
void MeLoopThreadProcedure::ThreadProcedure()
{
	// 当主线程要结束了
	while( !m_bMexLoadingThreadWillDestroy )
	{
		if (m_bMexLoadingThreadPaused)
		{
			Sleep(1);
			continue;
		}
		if (m_bMexLaodingThreadWillPause)
		{
			m_bMexLaodingThreadWillPause = false;
			m_bMexLoadingThreadPaused = true;
		}
		else
		{
			MeLoopThreadReq* req = 0;
			EnterCriticalSection( &m_MexLoadingCS );
			bool bHasReq = !m_MexLoadingReqs.empty();
			if( bHasReq )
			{
				req = m_MexLoadingReqs.back();
				m_MexLoadingReqs.pop_back();
			}		
			LeaveCriticalSection( &m_MexLoadingCS );


			if( bHasReq )
			{
				LoadMexFromReq2( req );		
				PostMexLoadingAck( req );			
			}
			else
			{
				WaitForSingleObject( m_hMexLoadingEvent, INFINITE );
			}
		}

		//Sleep( 1 );
	}
	// 这个线程结束了
	m_bMexLoadingThreadTerminated = true;
}
//////////////////////////////////////////////////////////////////////////
// tell the procedure to complete
void MeLoopThreadProcedure::WaitForComplete()
{
	m_bMexLoadingThreadWillDestroy = true;
	Signal();
	while( !m_bMexLoadingThreadTerminated )
		Sleep( 1 );
}
//////////////////////////////////////////////////////////////////////////
// awake the procedure
void MeLoopThreadProcedure::Signal()
{
	SetEvent( m_hMexLoadingEvent );
}
void MeLoopThreadProcedure::Pause()
{
	m_bMexLaodingThreadWillPause = true;
	Signal();
	while( !m_bMexLoadingThreadPaused )
		Sleep( 1 );
}

void MeLoopThreadProcedure::Resume()
{
	m_bMexLoadingThreadPaused = false;
}

bool MeLoopThreadProcedure::IsPause()
{
	return m_bMexLoadingThreadPaused;
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThreadProcedure::PostMexLoadingReq( MeLoopThreadReq* pReq )
{
	m_MexLoadingReqsCache.push_back( pReq );
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThreadProcedure::PostMexLoadingAck( MeLoopThreadReq* pReq )
{
	EnterCriticalSection( &m_MexLoadingCS );
	m_MexLoadingAcks.push_back( pReq );
	LeaveCriticalSection( &m_MexLoadingCS );
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThreadProcedure::ClearLoopList()
{
	EnterCriticalSection( &m_MexLoadingCS );

	ClearReqCacheList();

	ClearReqList();

	ClearAckList();

	LeaveCriticalSection( &m_MexLoadingCS );
}

void MeLoopThreadProcedure::ClearReqCacheList()
{
	for( Mex2LoadReqsIter it = m_MexLoadingReqsCache.begin(); 
		it != m_MexLoadingReqsCache.end(); ++ it )
	{
		(*it)->Destroy();
		MeDelete (*it);
	}
	m_MexLoadingReqsCache.clear();
}

void MeLoopThreadProcedure::ClearReqList()
{
	for( Mex2LoadReqsIter it = m_MexLoadingReqs.begin(); 
		it != m_MexLoadingReqs.end(); ++ it )
	{
		(*it)->Destroy();
		MeDelete (*it);
	}
	m_MexLoadingReqs.clear();
}