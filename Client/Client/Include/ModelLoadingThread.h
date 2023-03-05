//#pragma once
//
//#include <MeFoundation/MeFoundationPCH.h>
//#include <MeFoundation/MeThread.h>
//#include "ModelLoadingThreadProc.h"
//
//class ModelLoadingThread : public MeThread
//{
//public:
//	inline void MainThreadProcess(){
//		GetProcedure()->MainThreadProcess();
//	}
//
//	void PostMexLoadingReq( MeLoopThreadReq* req );
//	void ClearLoadingList();
//
//	void SetMainProcessSpeed( int nSpeed );
//
//public:
//	static ModelLoadingThread* CreateThread( ModelLoadingThreadProc* pkProc );
//
//};