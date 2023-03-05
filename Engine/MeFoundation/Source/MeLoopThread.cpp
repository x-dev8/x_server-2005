#include "MeFoundation/MeLoopThread.h"

//////////////////////////////////////////////////////////////////////////
void MeLoopThread::PostMexLoadingReq( MeLoopThreadReq* req )
{
	MeThreadProcedure* pkProc = GetProcedure();
	if( !pkProc )
		return;

	MeLoopThreadProcedure* pkModelProc = 
		dynamic_cast<MeLoopThreadProcedure*>( pkProc );

	if( !pkModelProc )
		return;

	pkModelProc->PostMexLoadingReq( req );
}
//////////////////////////////////////////////////////////////////////////
MeLoopThread* MeLoopThread::CreateThread( MeLoopThreadProcedure* pkProc, 
										 int nThreadInfo )
{
	MeLoopThread* pkThread = MeNew MeLoopThread( nThreadInfo );
	pkThread->SetProcedure( pkProc );

	_beginthread( ThreadProc, 0, pkThread );

	return pkThread;
}
bool MeLoopThread::IsPause()
{
	MeLoopThreadProcedure* pkModelProc = 
		dynamic_cast<MeLoopThreadProcedure*>( GetProcedure() );

	if( !pkModelProc )
		return false;

	return pkModelProc->IsPause();
}

void MeLoopThread::Pause()
{
	MeLoopThreadProcedure* pkModelProc = 
		dynamic_cast<MeLoopThreadProcedure*>( GetProcedure() );

	if( !pkModelProc )
		return;

	pkModelProc->Pause();
}

void MeLoopThread::Resume()
{
	MeLoopThreadProcedure* pkModelProc = 
		dynamic_cast<MeLoopThreadProcedure*>( GetProcedure() );

	if( !pkModelProc )
		return;

	pkModelProc->Resume();
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThread::ClearLoadingList()
{
	MeLoopThreadProcedure* pkModelProc = 
		dynamic_cast<MeLoopThreadProcedure*>( GetProcedure() );

	if( !pkModelProc )
		return;

	pkModelProc->ClearLoopList();
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThread::SetMainProcessSpeed( int nSpeed )
{
	MeLoopThreadProcedure* pkModelProc = 
		dynamic_cast<MeLoopThreadProcedure*>( GetProcedure() );

	if( !pkModelProc )
		return;

	pkModelProc->SetMainProcessSpeed( nSpeed );
}
//////////////////////////////////////////////////////////////////////////