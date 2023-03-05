//#include "ModelLoadingThread.h"
//
////////////////////////////////////////////////////////////////////////////
//void ModelLoadingThread::PostMexLoadingReq( MeLoopThreadReq* req )
//{
//	MeThreadProcedure* pkProc = GetProcedure();
//	if( !pkProc )
//		return;
//
//	ModelLoadingThreadProc* pkModelProc = 
//		dynamic_cast<ModelLoadingThreadProc*>( pkProc );
//
//	if( !pkModelProc )
//		return;
//
//	pkModelProc->PostMexLoadingReq( req );
//}
////////////////////////////////////////////////////////////////////////////
//ModelLoadingThread* ModelLoadingThread::CreateThread( ModelLoadingThreadProc* pkProc )
//{
//	ModelLoadingThread* pkThread = MeNew ModelLoadingThread();
//	pkThread->SetProcedure( pkProc );
//
//	_beginthread( ThreadProc, 0, pkThread );
//
//	return pkThread;
//}
////////////////////////////////////////////////////////////////////////////
//void ModelLoadingThread::ClearLoadingList()
//{
//	ModelLoadingThreadProc* pkModelProc = 
//		dynamic_cast<ModelLoadingThreadProc*>( GetProcedure() );
//
//	if( !pkModelProc )
//		return;
//
//	pkModelProc->ClearMexLoadingList();
//}
////////////////////////////////////////////////////////////////////////////
//void ModelLoadingThread::SetMainProcessSpeed( int nSpeed )
//{
//	ModelLoadingThreadProc* pkModelProc = 
//		dynamic_cast<ModelLoadingThreadProc*>( GetProcedure() );
//
//	if( !pkModelProc )
//		return;
//
//	pkModelProc->SetMainProcessSpeed( nSpeed );
//}
////////////////////////////////////////////////////////////////////////////