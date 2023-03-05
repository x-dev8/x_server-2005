#include "MeFoundation/MeFoundationPCH.h"
#include "MeFoundation/MeThread.h"

//////////////////////////////////////////////////////////////////////////
MeThread::MeThread()
{
	m_pkThreadProc = 0;
}
//////////////////////////////////////////////////////////////////////////
MeThread::~MeThread()
{
	GetProcedure()->WaitForComplete();
	m_pkThreadProc->Destroy();
	MeDelete m_pkThreadProc;
	m_pkThreadProc = NULL;
}
//////////////////////////////////////////////////////////////////////////
MeThread* MeThread::CreateThread( MeThreadProcedure* pkProc )
{
	MeThread* pkThread = MeNew MeThread();
	pkThread->SetProcedure( pkProc );

	_beginthread( ThreadProc, 0, pkThread );
	
	return pkThread;
}
//////////////////////////////////////////////////////////////////////////
void MeThread::ThreadProc( void* p )
{
	MeThread* pkThread = ( MeThread* )p;
	pkThread->GetProcedure()->ThreadProcedure();
	_endthread();
}
//////////////////////////////////////////////////////////////////////////