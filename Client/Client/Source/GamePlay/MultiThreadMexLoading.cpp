//#include <vector>
//#include "Me3d/Engine/Engine.h"
//#include "WSModelEffect.h"
//#include "MultithreadMexLoading.h"
//#include "FuncPerformanceLog.h"
//#include <process.h>
//#include "player.h"
//#include "MapContainer.h"
//#include "Me3d/Model/mexconfig.h"
//#include "GameMain.h"
//#include "PlayerMgr.h"
//#include "Font3DManager.h"
//#include "wsCamera.h"
//
//#define MODIFY_THREAD_LOADING
//
////////////////////////////////////////////////////////////////////////////
////static CRITICAL_SECTION gs_MexLoadingCS;
////static BOOL gs_bMexLoadingThreadWillDestroy = FALSE;
////static BOOL gs_bMexLoadingThreadTerminated = FALSE;
////static std::list<Mex2LoadReq*> gs_MexLoadingReqsCache;
////static std::list<Mex2LoadReq*> gs_MexLoadingReqs;
////static std::list<Mex2LoadReq*> gs_MexLoadingAcks;
////static std::map< std::string, bool > gs_MexBackListString;
////static std::map< int, bool > gs_MexBackListInt;
//
//static MultiThreadMexLoadingMgr gs_MTMexLoadingMgr;
////extern BOOL g_bIsShowSceneAndPlayer;
////extern CHeroGame theHeroGame;
////
////HANDLE g_hMexLoadingThread = NULL;
////static HANDLE s_hMexLoadingEvent = NULL;
//
////void ProcessMexLoadingThread();
////BOOL RetriveAndEraseReqs( int nLoadingReqsCount, Mex2LoadReq*& req,int nLoadReqType);
//
//MultiThreadMexLoadingMgr* MeLoopThreadMan::Instance()
//{
//	return &gs_MTMexLoadingMgr;
//}
////////////////////////////////////////////////////////////////////////////
//MultiThreadMexLoadingMgr::MultiThreadMexLoadingMgr()
//{
//
//}
////////////////////////////////////////////////////////////////////////////
//MultiThreadMexLoadingMgr::~MultiThreadMexLoadingMgr()
//{
//	MeDelete m_pkPartModelLoadingThread;
//	m_pkPartModelLoadingThread = 0;
//	MeDelete m_pkMounstNPCLoadingThread;
//	m_pkMounstNPCLoadingThread = 0;
//	MeDelete m_pkEffectLoadingThread;
//	m_pkEffectLoadingThread = 0;
//}
//////////////////////////////////////////////////////////////////////////
//BOOL MultiThreadMexLoadingMgr::FindPointer( void* p )
//{
//	guardfunc;
//	// commented out, [10/12/2010 zhangjiayi]
//	// ֻ�����̵߳��ã�������������ͬ��
//	//CSALocker l(s_cs);
//	for( int i = 0; i < m_Pointers.size(); i++ )
//	{
//		if( m_Pointers[i] == p )
//			return TRUE;
//	}
//	return FALSE;
//	unguard;
//	
//}
//BOOL MultiThreadMexLoadingMgr::RegisterPointer( void* p )
//{
//	guardfunc;
//	//CSALocker l(s_cs);
//	for( int i = 0; i < m_Pointers.size(); i++ )
//	{
//		if( m_Pointers[i] == p )
//			return TRUE;
//	}
//	m_Pointers.push_back( p );
//	return TRUE;
//	unguard;
//}
//BOOL MultiThreadMexLoadingMgr::UnRegisterPointer( void* p )
//{
//	guardfunc;
//	//CSALocker l(s_cs);
//	for( int i = 0; i < m_Pointers.size(); i++ )
//	{
//		if( m_Pointers[i] == p )
//		{
//			m_Pointers.erase( m_Pointers.begin()+i );
//			return TRUE;
//		}
//	}
//	return FALSE;
//	unguard;
//}
////////////////////////////////////////////////////////////////////////////
//MeLoopThreadReq* MultiThreadMexLoadingMgr::CreateLoadReq( int nType )
//{
//	switch( nType )
//	{
//	case LoopLoadType::ePlayerEquip:
//		return MeNew PlayerEquipReq;
//		break;
//	case LoopLoadType::eModelEffect:
//		return MeNew ModelEffectReq;
//		break;
//	case LoopLoadType::eMonsterModel:
//		return MeNew MonsterModelReq;
//		break;
//	case LoopLoadType::eMount:
//		return MeNew MountReq;
//		break;
//	case LoopLoadType::ePlayerName:
//		return MeNew PlayerNameReq;
//		break;
//	}
//	return NULL;
//}
////////////////////////////////////////////////////////////////////////////
//void MultiThreadMexLoadingMgr::PostMexLoadingReq( MeLoopThreadReq* req )
//{
//	if( !req )
//		return;
//
//	switch( req->m_nObjectType )
//	{
//	case LoopLoadType::ePlayerEquip:
//		GetPartModelThread()->PostMexLoadingReq( req );
//		break;
//	case LoopLoadType::eModelEffect:
//		GetEffectThread()->PostMexLoadingReq( req );
//		break;
//	case LoopLoadType::eMonsterModel:
//		GetMounsterNPCThread()->PostMexLoadingReq( req );
//		break;
//	case LoopLoadType::eMount:
//		GetMounsterNPCThread()->PostMexLoadingReq( req );
//		break;
//	}
//}
////////////////////////////////////////////////////////////////////////////
//void MultiThreadMexLoadingMgr::StartThreads()
//{
//	m_pkPartModelLoadingThread = ModelLoadingThread::CreateThread(
//		MeNew ModelLoadingThreadProc() );	
//	m_pkMounstNPCLoadingThread = ModelLoadingThread::CreateThread(
//		MeNew ModelLoadingThreadProc() );
//	m_pkMounstNPCLoadingThread->SetMainProcessSpeed( 8 );
//	m_pkEffectLoadingThread = ModelLoadingThread::CreateThread(
//		MeNew ModelLoadingThreadProc() );
//}
////////////////////////////////////////////////////////////////////////////
//void MultiThreadMexLoadingMgr::CloseThreads()
//{
//	MeDelete m_pkPartModelLoadingThread;
//	m_pkPartModelLoadingThread = 0;
//	MeDelete m_pkMounstNPCLoadingThread;
//	m_pkMounstNPCLoadingThread = 0;
//	MeDelete m_pkEffectLoadingThread;
//	m_pkEffectLoadingThread = 0;
//}
////////////////////////////////////////////////////////////////////////////
//void MultiThreadMexLoadingMgr::MainThreadProcess()
//{
//  	m_pkPartModelLoadingThread->MainThreadProcess();
//	m_pkMounstNPCLoadingThread->MainThreadProcess();
//  	m_pkEffectLoadingThread->MainThreadProcess();
//}
////////////////////////////////////////////////////////////////////////////
//void MultiThreadMexLoadingMgr::ClearLoadingList()
//{
//	m_pkPartModelLoadingThread->ClearLoadingList();
//	m_pkMounstNPCLoadingThread->ClearLoadingList();
//	m_pkEffectLoadingThread->ClearLoadingList();
//}
////////////////////////////////////////////////////////////////////////////
//// mex2���߳�
////BOOL PostMexLoadingReq( Mex2LoadReq* req )
////{
////	guardfunc;
////	gs_MexLoadingReqsCache.push_back(req);
////// 	EnterCriticalSection( &gs_MexLoadingCS );
////// 	// added, jiayi, [2009/11/24]
////// 	if( gs_MexBackList.find( req.m_nModelId ) != gs_MexBackList.end() )
////// 	{
////// 		if( req.m_PlayerEquipParam.m_nType == CStdCharSkeleton::eMaxPart - 1 )
////// 		{
////// 			if( req.m_PlayerEquipParam.m_pAnim )
////// 				req.m_PlayerEquipParam.m_pAnim->SetChangeAllEquipComplete( TRUE );
////// 		}
////// 		LeaveCriticalSection( &gs_MexLoadingCS );
////// 		return false;
////// 	}
////// 	gs_MexLoadingReqs.push_back( req );
////// 	LeaveCriticalSection( &gs_MexLoadingCS );
////	return TRUE;
////	unguard;
////}
////BOOL PostMexLoadingAck( Mex2LoadReq* req )
////{
////	guardfunc;
////	EnterCriticalSection( &gs_MexLoadingCS );
////	gs_MexLoadingAcks.push_back( req );
////	LeaveCriticalSection( &gs_MexLoadingCS );
////	return TRUE;
////	unguard;
////}
////BOOL LoadMexFromReq2( Mex2LoadReq* req )
////{
////	guardfunc;
////	if( !req->ProcessInThread() )
////	{
////		MeDelete req;
////		return false;
////	}
////	return true;
////
////	// ����id���Ҽ�¼
////// 	MexResMgr::Record* pRecord = NULL;
////// 	if (req->m_nModelId != -1)
////// 	{
////// 		pRecord = GetMexResMgr()->CreateModel(req->m_nModelId);
////// 	}
////// 	else
////// 	{
////// 		pRecord = GetMexResMgr()->CreateModel(req->m_szFileName);
////// 	}
////// 	if ( pRecord && pRecord->res.pMex)
////// 	{
////// 		req->m_pMex = pRecord->res.pMex;
////// 		req->m_pMexCfg = pRecord->res.pMexCfg;
//////  		req->m_nModelId = pRecord->nId;
////// 	}
////// 	else
////// 	{
////// 		if(req->m_nObjectType == Mex2LoadReq::ePlayerEquip )
////// 		{
////// 			PlayerEquipReq* pPlayerReq = dynamic_cast< PlayerEquipReq* >( req );			
////// 			if( !pPlayerReq )
////// 				return FALSE;
////// 
////// 			if( pPlayerReq->m_nType == /*CStdCharSkeleton::eMaxPart*/eKeyAll_Max - 1 )
////// 			{//���ۼ��سɹ�����������Ƿ�������װ��������ɵı��
////// 				req->m_pMex = NULL;
////// 				req->m_pMexCfg = NULL;
////// 				req->m_nModelId = -1;
////// 				return TRUE;
////// 			}
////// 			else
////// 			{
////// 				// added, jiayi, [2010/1/29]��������Ҫ����
////// 				if( req->m_szFileName && strcmp( req->m_szFileName, "" ) != 0 )
////// 				{
////// 					::EnterCriticalSection( &gs_MexLoadingCS );
////// 					gs_MexBackListString[req->m_szFileName] = false;
////// 					::LeaveCriticalSection( &gs_MexLoadingCS );
////// 				}
////// 				else if( req->m_nModelId != -1 )
////// 				{
////// 					::EnterCriticalSection( &gs_MexLoadingCS );
////// 					gs_MexBackListInt[req->m_nModelId] = false;
////// 					::LeaveCriticalSection( &gs_MexLoadingCS );
////// 				}
////// 				
////// 			}
//////             
////// 		}
////// 		MeDelete req;
////// 		req = 0;
////// 		return FALSE;
////// 	}
////
////	//return TRUE;
////	unguard;
////
////}
////
////void MexLoadingThread(void* p)
////{
////	guardfunc;
////	// �����߳�Ҫ������
////	while( !gs_bMexLoadingThreadWillDestroy )
////	{
////		Mex2LoadReq* req = 0;
////		BOOL bHasReq = FALSE;
////		static bool bGo = true;
////		if( !bGo )
////			continue;
////		EnterCriticalSection( &gs_MexLoadingCS );
////
////
////		int nLoadingReqsCount = gs_MexLoadingReqs.size();
////		if( nLoadingReqsCount > 0 )
////		{
////
////			////////New Project
////			bHasReq = FALSE;
////			for( int i = 0 ; i < Mex2LoadReq::eReqCount ; ++ i )
////			{
////				if( bHasReq = RetriveAndEraseReqs(nLoadingReqsCount, req, i ) )
////					break;
////			}
////		}
////
////		LeaveCriticalSection( &gs_MexLoadingCS );
////		if( bHasReq )
////		{
//// 			if( LoadMexFromReq2( req ) )
////			{
////				PostMexLoadingAck( req );
////			}
////		}
////		else
////		{
////			WaitForSingleObject( s_hMexLoadingEvent, INFINITE );
////		}
////		//Sleep( 1 );
////	}
////	// ����߳̽�����
////	gs_bMexLoadingThreadTerminated = TRUE;
////	unguard;
////}
////void StartMexLoadingThread()
////{
////	guardfunc;
////	gs_bMexLoadingThreadWillDestroy = FALSE;
////	gs_bMexLoadingThreadTerminated = FALSE;
////	InitializeCriticalSection( &gs_MexLoadingCS );
////	HANDLE hThread = (HANDLE)_beginthread( MexLoadingThread, NULL, NULL );
////	g_hMexLoadingThread = hThread;
////	::SetThreadPriority( hThread, THREAD_PRIORITY_NORMAL );
////	s_hMexLoadingEvent = ::CreateEvent( 
////		NULL,         // default security attributes
////		FALSE,         // auto-reset event
////		FALSE,         // initial state is signaled
////		NULL  // object name
////		); 
////
////	unguard;
////}
////
////void ProcessMexLoadingThread()
////{
////	guardfunc;
////    if( !g_hMexLoadingThread )
////        return;
////	if (!TryEnterCriticalSection( &gs_MexLoadingCS ))
////	{
////		return;
////	}
////	for( std::list<Mex2LoadReq*>::iterator iter = gs_MexLoadingReqsCache.begin(); iter != gs_MexLoadingReqsCache.end(); ++iter )
////	{
////		Mex2LoadReq* req = *iter;
////		PlayerEquipReq* pPlayerReq = dynamic_cast< PlayerEquipReq* >( req );
////		if( pPlayerReq && ( pPlayerReq->m_nType == eKeyAll_Max - 1 ) )
////		{						
////			if( pPlayerReq->m_pAnim )
////				pPlayerReq->m_pAnim->SetChangeAllEquipComplete( TRUE );
////		}
////		bool bInBack = false;
////		if( req->m_nModelId != -1 )
////		{
////			if( gs_MexBackListInt.find( req->m_nModelId ) != gs_MexBackListInt.end() )
////				bInBack = true;
////		}
////		else if(( req->m_szFileName && strcmp( req->m_szFileName, "" ) != 0 )  &&  gs_MexBackListString.find( req->m_szFileName ) != gs_MexBackListString.end() )
////		{
////			bInBack = true;
////		}
////		if( bInBack )
////		{
////			MeDelete (*iter);			
////			continue;
////		}
////		gs_MexLoadingReqs.push_back( req );
////	}
////	if( !gs_MexLoadingReqs.empty() )
////		SetEvent( s_hMexLoadingEvent );
////	gs_MexLoadingReqsCache.clear();
////	MultiThreadMexLoadingMgr* pMgr = MeLoopThreadMan::Instance();
////
////// 	static DWORD s_dwProcessPriority = NORMAL_PRIORITY_CLASS;
////// 	if( gs_MexLoadingReqs.size() > 64 )
////// 	{
////// 		if( s_dwProcessPriority == NORMAL_PRIORITY_CLASS )
////// 		{
////// 			s_dwProcessPriority = BELOW_NORMAL_PRIORITY_CLASS;
////// 			if( g_hMexLoadingThread )
////// 				::SetThreadPriority( g_hMexLoadingThread, THREAD_PRIORITY_ABOVE_NORMAL );
////// 
////// 			if( ::SetPriorityClass( GetCurrentProcess(), s_dwProcessPriority ) == FALSE )
////// 			{
////// 				s_dwProcessPriority = NORMAL_PRIORITY_CLASS;
////// 			}
////// 		}
////// 	}
////// 	else
////// 	{
////// 		if( s_dwProcessPriority == BELOW_NORMAL_PRIORITY_CLASS )
////// 		{
////// 			s_dwProcessPriority = NORMAL_PRIORITY_CLASS;
////// 			if( g_hMexLoadingThread )
////// 				::SetThreadPriority( g_hMexLoadingThread, THREAD_PRIORITY_NORMAL );
////// 
////// 			if( ::SetPriorityClass( GetCurrentProcess(), s_dwProcessPriority ) == FALSE )
////// 			{
////// 				s_dwProcessPriority = BELOW_NORMAL_PRIORITY_CLASS;
////// 			}
////// 		}
////// 	}
////
////	if (gs_MexLoadingAcks.empty())
////	{
////		LeaveCriticalSection( &gs_MexLoadingCS );
////		return;
////	}
////
////	// �����л���ͼ�������ϸ���ͼ����ģ������������
////	if( theHeroGame.GetPlayerMgr() && !theHeroGame.GetPlayerMgr()->CanReceivePlayerMsg() )
////	{
////		int count = gs_MexLoadingAcks.size();
////		for(int i=0; i<count; ++i)
////		{
////			Mex2LoadReq* pReq = gs_MexLoadingAcks.front();
////			if( pReq )
////			{
////				pReq->DestroyMex();
////				MeDelete pReq;
////				pReq = 0;
////
////				gs_MexLoadingAcks.pop_front();
////			}
////		}
////		LeaveCriticalSection( &gs_MexLoadingCS );
////		return;
////	}
////	if (!GetMexResMgr()->TryLock())
////	{
////		LeaveCriticalSection( &gs_MexLoadingCS );
////		return;
////	}
////	if (!GetEngine()->GetTextureManager()->TryLockTextureManager())
////	{
////		GetMexResMgr()->UnLock();
////		LeaveCriticalSection( &gs_MexLoadingCS );
////		return;
////	}
////	// add, [10/15/2010 zhangjiayi]
////	// ÿx֡����һ��ģ��
////	static short stFrameCount = 0;
////	static short stStartCount = 10;
////    // ÿ�ζ�1��������л�װ����
////    int count = 0;
////    if( !g_bIsShowSceneAndPlayer )	// ���볡�������׶Σ�����ȫ�����첽�������ģ��
////        count = gs_MexLoadingAcks.size();
////    else if( !gs_MexLoadingAcks.empty() && ++stFrameCount >= stStartCount )
////	{
////        count = 1;//min(1, gs_MexLoadingAcks.size());
////		stFrameCount = 0;
////	}
////
////	for(int i=0; i<count; i++ )
////	{
////		if( gs_MexLoadingAcks.empty() )
////			break;
////		Mex2LoadReq* pReq = gs_MexLoadingAcks.front();
////		if( pReq  )
////		{
////			pReq->Process();
////		}
////		pReq->DestroyMex();		
////		gs_MexLoadingAcks.pop_front();
////		MeDelete pReq;
////		pReq = 0;
////	}
////	GetEngine()->GetTextureManager()->UnLockTextureManager();
////	GetMexResMgr()->UnLock();
////	LeaveCriticalSection( &gs_MexLoadingCS );
////	unguard;
////}
////
////void ClearMexLoadingList()
////{
////	EnterCriticalSection( &gs_MexLoadingCS );
////	gs_MexLoadingReqsCache.clear();
////	// ����������
////	gs_MexLoadingReqs.clear();
////	// ����Ѿ���ɵĶ���,��ʱ��δ��������ȡ��,���Կ���ֱ���ͷ�
////	std::list<Mex2LoadReq*>::iterator it = gs_MexLoadingAcks.begin();
////	std::list<Mex2LoadReq*>::iterator end = gs_MexLoadingAcks.end();
////	for ( ; it != end; ++it)
////	{
////		Mex2LoadReq* pReq = (*it);
////		pReq->DestroyMex();
////		MeDelete pReq;
////		pReq = 0;
////	}
////	gs_MexLoadingAcks.clear();
////	LeaveCriticalSection( &gs_MexLoadingCS );
////}
////
////void CloseMexLoadingThread()
////{
////	guardfunc;
////	// ��֪��������̣߳�������Ҫ�ر���
////	gs_bMexLoadingThreadWillDestroy = TRUE;
////	// ���ĵĵȴ�����߳̽���
////	SetEvent( s_hMexLoadingEvent);
////	while( !gs_bMexLoadingThreadTerminated )
////		Sleep( 1 );
////
////	ClearMexLoadingList();
////
////	DeleteCriticalSection( &gs_MexLoadingCS );
////	CloseHandle( s_hMexLoadingEvent );
////	unguard;
////}
////
////BOOL RetriveAndEraseReqs( int nLoadingReqsCount, Mex2LoadReq *&req ,int nLoadReqType )
////{
////	for(std::list<Mex2LoadReq*>::iterator iter = gs_MexLoadingReqs.begin(); iter != gs_MexLoadingReqs.end(); ++iter)
////	{
////		if ((*iter)->m_nObjectType == nLoadReqType)
////		{
////			req = *iter;
////			gs_MexLoadingReqs.erase(iter);
////			return TRUE;
////		}
////	}
////	return FALSE;
////}
////
