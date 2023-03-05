#include "ModelLoadingThreadProc.h"
#include "Me3d/Model/MexRes.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include <MeFoundation/MeLoopThreadMan.h>
#include "MeUtility/FilePath.h"
#include "Mex2LoadReq.h"
//////////////////////////////////////////////////////////////////////////
extern BOOL g_bIsShowSceneAndPlayer;
extern CRITICAL_SECTION gs_MexResMgrIDCS;
extern CRITICAL_SECTION gs_MexResMgrFileCS;
//////////////////////////////////////////////////////////////////////////
ModelLoadingThreadProc::ModelLoadingThreadProc()
{
}
//////////////////////////////////////////////////////////////////////////
ModelLoadingThreadProc::~ModelLoadingThreadProc()
{	
}
//////////////////////////////////////////////////////////////////////////
bool ModelLoadingThreadProc::LoadMexFromReq2( MeLoopThreadReq* pReq )
{
	EnterCriticalSection( &gs_MexResMgrIDCS );
	EnterCriticalSection( &gs_MexResMgrFileCS );
	MexResMgr::Record* pRecord = NULL;
	BeginGuard
	if (pReq->m_nModelId != -1)
	{
		pRecord = GetMexResMgr()->CreateModel(pReq->m_nModelId);
	}
	else
	{
		pRecord = GetMexResMgr()->CreateModel(pReq->m_szFileName);
	}
	EndGuard
	if ( pRecord && pRecord->res.pMex)
	{
		pReq->m_pMex = pRecord->res.pMex;
		pReq->m_pMexCfg = pRecord->res.pMexCfg;
		pReq->m_nModelId = pRecord->nId;
		pReq->ProcessInThread();

	}
	else
	{
		if(pReq->m_nObjectType == LoopLoadType::ePlayerEquip )
		{
			PlayerEquipReq* pPlayerReq = dynamic_cast< PlayerEquipReq* >( pReq );	

			if( pPlayerReq->m_nType == /*CStdCharSkeleton::eMaxPart*/eKeyAll_Max - 1 )
			{//无论加载成功与否，这里总是返回人物装备加载完成的标记
				pReq->m_pMex = NULL;
				pReq->m_pMexCfg = NULL;
				pReq->m_nModelId = -1;
				LeaveCriticalSection( &gs_MexResMgrFileCS );
				LeaveCriticalSection( &gs_MexResMgrIDCS );
				return true;
			}
			else
			{
				// added, jiayi, [2010/1/29]，这里需要加锁
				if( pReq->m_szFileName && strcmp( pReq->m_szFileName, "" ) != 0 )
				{
					::EnterCriticalSection( &m_MexLoadingCS );
					m_MexBackListString[pReq->m_szFileName] = false;
					::LeaveCriticalSection( &m_MexLoadingCS );
				}
				else if( pReq->m_nModelId != -1 )
				{
					::EnterCriticalSection( &m_MexLoadingCS );
					m_MexBackListInt[pReq->m_nModelId] = false;
					::LeaveCriticalSection( &m_MexLoadingCS );
				}

			}

		}
		pReq->ProcessInThread( true );
		pReq->SetValid( false );
		LeaveCriticalSection( &gs_MexResMgrFileCS );
		LeaveCriticalSection( &gs_MexResMgrIDCS );
		return false;
	}
	LeaveCriticalSection( &gs_MexResMgrFileCS );
	LeaveCriticalSection( &gs_MexResMgrIDCS );
	return true;
}
#ifdef _DEBUG
#define LOAD_COST_TIME_DEBUG 1
#else
#define LOAD_COST_TIME_DEBUG 0
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////
void ModelLoadingThreadProc::MainThreadProcess()
{
#if LOAD_COST_TIME_DEBUG
	DWORD time_cost = HQ_TimeGetTime() ;
#endif
	if (!TryEnterCriticalSection( &m_MexLoadingCS ))
	{
		return;
	}
	for( std::list<MeLoopThreadReq*>::iterator iter = m_MexLoadingReqsCache.begin(); iter != m_MexLoadingReqsCache.end(); ++iter )
	{
		MeLoopThreadReq* req = *iter;
		PlayerEquipReq* pPlayerReq = dynamic_cast< PlayerEquipReq* >( req );
		if( pPlayerReq && ( pPlayerReq->m_nType == eKeyAll_Max - 1 ) )
		{						
			if( pPlayerReq->m_pAnim )
				pPlayerReq->m_pAnim->SetChangeAllEquipComplete( TRUE );
		}
		bool bInBack = false;
		if( req->m_nModelId != -1 )
		{
			if( m_MexBackListInt.find( req->m_nModelId ) != m_MexBackListInt.end() )
				bInBack = true;
		}
		else if(( req->m_szFileName && strcmp( req->m_szFileName, "" ) != 0 )  &&  m_MexBackListString.find( req->m_szFileName ) != m_MexBackListString.end() )
		{
			bInBack = true;
		}
		if( bInBack )
		{
			MeDelete (*iter);			
			continue;
		}
		m_MexLoadingReqs.push_back( req );
	}
	if( !m_MexLoadingReqs.empty() )
		SetEvent( m_hMexLoadingEvent );

	m_MexLoadingReqsCache.clear();


	if( !TryEnterCriticalSection( &gs_MexResMgrIDCS ) )
	{
		LeaveCriticalSection( &m_MexLoadingCS );
		return;
	}
	if( !TryEnterCriticalSection( &gs_MexResMgrFileCS ) )
	{
		LeaveCriticalSection( &gs_MexResMgrIDCS );
		LeaveCriticalSection( &m_MexLoadingCS );
		return;
	}

	if (m_MexLoadingAcks.empty())
	{
		LeaveCriticalSection( &gs_MexResMgrFileCS );
		LeaveCriticalSection( &gs_MexResMgrIDCS );
		LeaveCriticalSection( &m_MexLoadingCS );
		return;
	}

	// 正在切换地图，所以上个地图加载模型数据已无用
	if( theHeroGame.GetPlayerMgr() && !theHeroGame.GetPlayerMgr()->CanReceivePlayerMsg() )
	{
		int count = m_MexLoadingAcks.size();
		for(int i=0; i<count; ++i)
		{
			MeLoopThreadReq* pReq = m_MexLoadingAcks.front();
			if( pReq )
			{
				pReq->Destroy();
				MeDelete pReq;
				pReq = 0;

				m_MexLoadingAcks.pop_front();
			}
		}
		LeaveCriticalSection( &gs_MexResMgrFileCS );
		LeaveCriticalSection( &gs_MexResMgrIDCS );
		LeaveCriticalSection( &m_MexLoadingCS );
		return;
	}
	if (!GetEngine()->GetTextureManager()->TryLockTextureManager())
	{
		LeaveCriticalSection( &gs_MexResMgrFileCS );
		LeaveCriticalSection( &gs_MexResMgrIDCS );
		LeaveCriticalSection( &m_MexLoadingCS );
		return;
	}
	BeginGuard
	// 每x帧处理一个模型
	static short stFrameCount = 0;
	// 每次对1个人物进行换装处理
	int count = 0;
//   	if( !g_bIsShowSceneAndPlayer )	// 进入场景黑屏阶段，处理全部已异步加载完的模型
//  		count = m_MexLoadingAcks.size();
//   	else if( !m_MexLoadingAcks.empty() /*&& ++stFrameCount >= m_nSpeed*/ )
//   	{
//   		count = 1;//min(1, m_MexLoadingAcks.size());
//   		stFrameCount = 0;
//   	}
	count = m_MexLoadingAcks.size();

	for(int i=0; i<count; i++ )
	{
		if( m_MexLoadingAcks.empty() )
			break;
		MeLoopThreadReq* pReq = m_MexLoadingAcks.front();
		if( pReq && pReq->IsValid() )
		{
			pReq->Process();
			pReq->Destroy();		
		}	
		m_MexLoadingAcks.pop_front();
		MeDelete pReq;
		pReq = 0;
	}
	EndGuard
	GetEngine()->GetTextureManager()->UnLockTextureManager();
// 	GetMexResMgr()->UnLock();
	LeaveCriticalSection( &gs_MexResMgrFileCS );
	LeaveCriticalSection( &gs_MexResMgrIDCS );
	LeaveCriticalSection( &m_MexLoadingCS );
#if LOAD_COST_TIME_DEBUG
	time_cost = HQ_TimeGetTime() - time_cost;
	if(time_cost != 0)
	{
		char cOutputString[2048];
		sprintf_s( cOutputString, 2048, "\nProcessCostEnd:%d\n", time_cost );
		OutputDebugStr(cOutputString);
	}
#endif
}
//////////////////////////////////////////////////////////////////////////
void ModelLoadingThreadProc::ClearAckList()
{
	// 清除已经完成的队列,此时还未被管理器取走,所以可以直接释放
	Mex2LoadReqsIter it = m_MexLoadingAcks.begin();
	Mex2LoadReqsIter end = m_MexLoadingAcks.end();
	for ( ; it != end; ++it)
	{
		MeLoopThreadReq* pReq = (*it);
		pReq->Destroy();
		MeDelete pReq;
		pReq = 0;
	}
	m_MexLoadingAcks.clear();
}
//////////////////////////////////////////////////////////////////////////