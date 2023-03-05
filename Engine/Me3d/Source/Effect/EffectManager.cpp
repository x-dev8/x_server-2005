#include "Me3d/Me3d.h"
#include "MeRTLibs.h"
#include <windows.h>
#include <assert.h>
#include <helper.h>
#include "Me3d/effect/effectmanager.h"
#include "Me3d/effect/CharEffectContainer.h"
#include "FuncPerformanceLog.h"
#include "MeUtility/FilePath.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/TextureManager.h"
#include "Me3d/Engine/TextureManagerInstance.h"
#include "Me3d/Model/MexRes.h"
static CEffectManager gs_EffectManager;
BOOL g_bOpenTheEffect = TRUE;

extern bool CanRenderPlayerEffect( int nPlayerID );
/////////////////////////
D3DXVECTOR3		g_vCurSelectNpcPos = D3DXVECTOR3( 0, 0, 0 );			//当前选中的Npc位置
BOOL			g_bHaveSelectNpc = FALSE;								//是否有选中的Npc

CEffectManager* GetEffectMgr()
{
	guardfunc;
	//OutputDebugStr("CEffectManager");
	return &gs_EffectManager;
	unguard;
}

CEffectManager::CEffectManager(void)
{
	guardfunc;
	for( int nEffect = 0; nEffect < eMaxEffect; nEffect++ )
	{
		m_pEffects[nEffect] = NULL;
	}

	m_nEffectCount = 0;
	m_nCharEffectContainerCount = 0;

	m_vTheLookerPos.x = 0;
	m_vTheLookerPos.y = 0;
	m_vTheLookerPos.z = 0;
	m_fTheLookerViewDistance = 40;
	m_EffectCachePreLoadOK = false;
	unguard;
}

CEffectManager::~CEffectManager(void)
{
	guardfunc;
	Destroy();
	unguard;
}

void CEffectManager::AddEffectSetting( const char* pszFilename, BYTE* pEffectSetting, int nBufferSize )
{
	guardfunc;
	CFilePath path;
	path.Split(pszFilename);

	Cache* pFound = (Cache*)m_EffectSettingFinder.GetDstByName( path.GetFileName() );
	if( pFound )
	{
		if( pFound->pbyBuffer )
		{
			delete[] pFound->pbyBuffer;
			pFound->pbyBuffer = pEffectSetting;
			pFound->nSize = nBufferSize;
			return;
		}
		else
		{
			pFound->pbyBuffer = pEffectSetting;
			pFound->nSize = nBufferSize;
			return;
		}
	}

	Cache* pCache = MeNew Cache;
	pCache->pbyBuffer = pEffectSetting;
	pCache->nSize = nBufferSize;
	m_EffectCacheList.push_back( pCache );
	m_EffectSettingFinder.Register( path.GetFileName(), pCache );
	unguard;
}

CEffectManager::Cache* CEffectManager::GetEffectSetting( const char* pszFilename )
{
	guardfunc;
	CFilePath path;
	path.Split(pszFilename);
	return (Cache*)m_EffectSettingFinder.GetDstByName( path.GetFileName() );
	unguard;
}

void CEffectManager::DestroyCache()
{
	guardfunc;
	for( int nCache = 0; nCache < m_EffectCacheList.size(); nCache++ )
	{
		Cache* pCache = m_EffectCacheList[nCache];
		if( pCache->pbyBuffer )
		{
			delete[] pCache->pbyBuffer;
		}
		delete pCache;
		pCache = NULL;
	}
	m_EffectCacheList.clear();
	m_EffectSettingFinder.Destroy();
	unguard;
}

void CEffectManager::Destroy()
{
	guardfunc;
	for( int nEffect = 0; nEffect < eMaxEffect; nEffect++ )
	{
		if( m_pEffects[nEffect] )
		{
			m_pEffects[nEffect]->Release();
			m_pEffects[nEffect] = NULL;
		}
	}

	for( int i = 0; i < eMaxCharEffectContainer; i ++ )
	{
		if( m_pCharEffectContainer[i] )
		{
			m_pCharEffectContainer[i]->Destroy();
			delete m_pCharEffectContainer[i];
			m_pCharEffectContainer[i] = NULL;
		}
	}

	DestroyCache();
	unguard;
}

void CEffectManager::Update( DWORD dwTime )
{
	guardfunc;
	guard(test1);
	for( int nEffect = 0; nEffect < eMaxEffect; nEffect++ )
	{
		IEffect* pEffect = m_pEffects[nEffect];

		guard(test1.1);
		if( !pEffect )
			continue;
		unguard;

		guard(test1.2);
		if( pEffect->IsDead( dwTime ) )
		{
			if( !GetMexResMgr()->TryLock() )
				continue;
			// 这个try贴图锁，否则容易被锁 [10/29/2010 zhangjiayi]
			if( !GetEngine()->GetTextureManager()->TryLockTextureManager() )
			{
				GetMexResMgr()->UnLock();
				continue;
			}
			BeginGuard

			guard(test1.2.1);
			ReleaseEffect( pEffect );
			m_pEffects[nEffect] = NULL;
			unguard;

			EndGuard

			GetEngine()->GetTextureManager()->UnLockTextureManager();

			GetMexResMgr()->UnLock();
		}
		else
		{
			guard(test1.2.2);
			pEffect->Update( dwTime, m_vTheLookerPos, m_fTheLookerViewDistance );
			unguard;
		}
		unguard;
	}
	unguard;

	guard(test2)
	for( int i = 0; i < eMaxCharEffectContainer; i ++ )
	{
		guard(test2.1);
		if( m_pCharEffectContainer[i] )
		{
			guard(test2.1.1);
			if( m_pCharEffectContainer[i]->GetDestroyFlag() )
			{
				guard(test2.1.1.1);
				m_pCharEffectContainer[i]->Destroy();
				delete m_pCharEffectContainer[i];
				m_pCharEffectContainer[i] = NULL;
				m_nCharEffectContainerCount--;
				unguard;
			}
			unguard;
		}
		unguard;
	}
	unguard;
	unguard;
}

void CEffectManager::Render()
{
	guardfunc;
	for( int nEffect = 0; nEffect < eMaxEffect; nEffect++ )
	{
		IEffect* pEffect = m_pEffects[nEffect];

		if( !pEffect )
			continue;

//#ifdef GAME_CLIENT
        // 判断玩家特效隐藏
        if( !CanRenderPlayerEffect(((CBaseEffect*)pEffect)->GetPlayerID()) )
            continue;
//#endif //GAME_CLIENT

		pEffect->Render();
	}
	unguard;
}

IEffect* CEffectManager::GetEffect( int nID )
{
	guardfunc;
	if( nID < 0 || nID >= eMaxEffect )
	{
		//assert( false );
		return NULL;
	}
	return m_pEffects[nID];
	unguard;
}

void CEffectManager::ReleaseEffect( int nID )
{
	guardfunc;
	//int nID = nEffectID;
	if( nID == -1 ||
		nID < 0 ||
		nID >= eMaxEffect )
	{
		assert( false );
		return;
	}
	IEffect* pEffect = m_pEffects[nID];
	if( !pEffect )
	{
		assert( false );
		return;
	}

	pEffect->Release();

	pEffect = NULL;
	m_pEffects[nID] = NULL;
	unguard;
}

void CEffectManager::ReleaseEffect( IEffect* pEffect )
{
	guardfunc;
	if( !pEffect )
	{
		assert( false );
		return;
	}
	int nID = pEffect->GetID();
	if( nID == -1 ||
		nID < 0 ||
		nID >= eMaxEffect )
	{
		assert( false );
		pEffect->Release();
		pEffect = NULL;
		return;
	}
	ReleaseEffect( nID );
	unguard;
}

int CEffectManager::RegisterEffect( IEffect* pEffect )
{
	guardfunc;
	if( !g_bOpenTheEffect )
	{
		return -1;
	}

	int nID = -1;
	for( int nEffect = 0; nEffect < eMaxEffect; nEffect++ )
	{
		if( m_pEffects[nEffect] == NULL )
		{
			nID = nEffect;
			break;
		}
	}
	if( nID == -1 )
	{
		//assert( false );
		return -1;
	}
	pEffect->SetID( nID );
	m_pEffects[nID] = pEffect;
	return nID;
	unguard;
}

BOOL CEffectManager::RegisterCharEffectContainer()
{
	guardfunc;
	for( int i = 0; i < eMaxCharEffectContainer; i++ )
	{
		if( !m_pCharEffectContainer[i] )
		{
			m_pCharEffectContainer[i] = MeNew CCharEffectContainer;
			m_pCharEffectContainer[i]->SetId(i);
			m_nCharEffectContainerCount++;
			return i;
		}
	}

	return -1;
	unguard;
}

CCharEffectContainer* CEffectManager::GetCharEffectContainer( int nIndex )
{
	guardfunc;
	if( nIndex >= 0 && nIndex < eMaxCharEffectContainer )
	{
		if( m_pCharEffectContainer[nIndex] )
		{
			return m_pCharEffectContainer[nIndex];
		}
	}
	return NULL;
	unguard;
}

void CEffectManager::FlagCharEffectContainerDestroy( int nIndex )
{
	guardfunc;
	if( m_pCharEffectContainer[nIndex] )
	{
		m_pCharEffectContainer[nIndex]->FlagDestroy();
	}
	unguard;
}

void CEffectManager::SetTheLookerPos( D3DXVECTOR3 vPos )
{
	guardfunc;
	m_vTheLookerPos = vPos;
	unguard;
}

void CEffectManager::SetTheLookerViewDistance( float fDistance )
{
	guardfunc;
	m_fTheLookerViewDistance = fDistance;
	unguard;
}

bool CEffectManager::IsFull() const
{
	for( int nEffect = 0; nEffect < eMaxEffect; nEffect++ )
	{
		if( m_pEffects[nEffect] == NULL )
		{
			return false;			
		}
	}
	return true;	
}


int CEffectManager::GetEffectByPlayerID(int PlayerId)
{
	if (PlayerId < 0)
	{
		return -2; 
	}

	for( int nEffect = 0; nEffect < eMaxEffect; nEffect++ )
	{
		if( m_pEffects[nEffect] )
		{
			int playerid = ((CBaseEffect*)m_pEffects[nEffect])->GetPlayerID() ;
			if (playerid != -1)
			{
				if(playerid == PlayerId)
					return nEffect;
			}
		}
	}

	return -1;
}