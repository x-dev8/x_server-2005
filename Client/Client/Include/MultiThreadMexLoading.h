//#pragma once
//#include <windows.h>
//#include "Mutex.h"
//#include "Mex2LoadReq.h"
//#include "ModelLoadingThread.h"
//
//class MultiThreadMexLoadingMgr
//{
//public:
//	MultiThreadMexLoadingMgr();
//	~MultiThreadMexLoadingMgr();
// 	BOOL FindPointer( void* p );
//	BOOL RegisterPointer( void* p );
//	BOOL UnRegisterPointer( void* p );   
//
//	MeLoopThreadReq* CreateLoadReq( int nType );	
//
//	void PostMexLoadingReq( MeLoopThreadReq* req );
//
//	void StartThreads();
//	void CloseThreads();
//	void MainThreadProcess();
//	void ClearLoadingList();
//
//protected:
//	ModelLoadingThread* GetPartModelThread(){
//		return m_pkPartModelLoadingThread;
//	}
//	ModelLoadingThread* GetMounsterNPCThread(){
//		return m_pkMounstNPCLoadingThread;
//	}
//	ModelLoadingThread* GetEffectThread(){
//		return m_pkEffectLoadingThread;
//	}
//
//protected:
//	std::vector<void*> m_Pointers;
//	//CSemiAutoIntLock s_cs;
//	// added, [10/20/2010 zhangjiayi]
//	ModelLoadingThread* m_pkPartModelLoadingThread;
//	ModelLoadingThread* m_pkMounstNPCLoadingThread;
//	ModelLoadingThread* m_pkEffectLoadingThread;
//};
//
////BOOL PostMexLoadingReq( Mex2LoadReq* req );
//extern MultiThreadMexLoadingMgr* MeLoopThreadMan::Instance();