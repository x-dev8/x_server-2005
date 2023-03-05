#include "Me3d/Me3d.h"
#include "MeRTLibs.h"
#include <assert.h>
#include "Me3d/effect/CharEffectContainer.h"
#include "FuncPerformanceLog.h"
#include "Me3d/effect/effectmanager.h"

CEffectLight::CEffectLight():
m_bEnable(FALSE),
m_dwStartTime(0),
m_dwLife(0),
m_fIntense(0.0f)
{
	guardfunc;
	unguard;
}

CCharEffectContainer::CCharEffectContainer(void)
{
	guardfunc;
	for( int nEffect = 0; nEffect < eEffectMax; nEffect++ )
	{
		m_nEffects[nEffect] = -1;
	}
	//for( int nCast = 0; nCast < eSkillCastMax; nCast++ )
	//{
	//	m_pSkillCasts[nCast] = NULL;
	//}

	m_nCharID = -1;
	m_bDestroyFlag = FALSE;
	memset(m_EffectLights, 0, sizeof(CEffectLight)*eLightMax);

	m_nId = 0;
	unguard;
}

CCharEffectContainer::~CCharEffectContainer(void)
{
	guardfunc;
	unguard;
}


void CCharEffectContainer::Destroy()
{
	guardfunc;

	for (int i = 0; i < eEffectMax; ++i)
	{
		if( m_nEffects[i] != -1 )
		{
			IEffect* pEffect = GetEffectMgr()->GetEffect(m_nEffects[i]);
			if (pEffect)
				pEffect->SetDead();
			m_nEffects[i] = -1;
		}
	}
	unguard;
}

IEffect* CCharEffectContainer::GetEffect( int nEffect )
{
	guardfunc;
	//if( nEffect < 0 || nEffect >= eEffectMax )
	//{
	//	assert( false );
	//	return NULL;
	//}
	//int nEffectID = m_nEffects[nEffect];
	//if( nEffectID == -1 )
	//	return NULL;
	////return m_pEffects[nEffect];
	//return GetEffectMgr()->GetEffect( nEffectID );

	return NULL;

	unguard;
}
IEffectHelper* CCharEffectContainer::GetEffectHelper( int nPart )
{
	guardfunc;
	if( nPart < 0 || nPart >= eEffectBindPartMax )
	{
		assert( false );
		return NULL;
	}
	return &m_EffectHelpers[nPart];
	unguard;
}

BOOL CCharEffectContainer::ApplyEffect( int nEffect, int nID )
{
	guardfunc;
	if( nEffect < 0 || nEffect >= eEffectMax )
	{
		assert( false );
		return FALSE;
	}
	if( m_nEffects[nEffect] == -1 )
	{
		m_nEffects[nEffect] = nID;
		return TRUE;
	}
	else
	{
//		ClearEffect( nEffect );
	}
	return FALSE;
	unguard;
}
BOOL CCharEffectContainer::UnRef( int nEffectID )
{
	guardfunc;
	//// 消除effect的引用
	//for( int nEffect = 0; nEffect < eEffectMax; nEffect++ )
	//{
	//	if( m_nEffects[nEffect] == nEffectID )
	//		m_nEffects[nEffect] = -1;
	//}
	return TRUE;
	unguard;
}

BOOL CCharEffectContainer::ClearEffect( int nEffect )
{
	guardfunc;
	guard(test1);
	if( nEffect < 0 || nEffect >= eEffectMax )
	{
		assert( false );
		return FALSE;
	}
	unguard;
	// 主动删除effect，effect被销毁
	guard(test2)
	if( m_nEffects[nEffect] != -1 )
	{
		guard(test2.1);
		GetEffectMgr()->ReleaseEffect( m_nEffects[nEffect] );
		m_nEffects[nEffect] = -1;
		return TRUE;
		unguard;
	}
	return FALSE;
	unguard;
	unguard;
}

BOOL CCharEffectContainer::ClearEffectNotDestroy( int nEffectId )
{
	for (int i = 0; i < eEffectMax; ++i)
	{
		if (m_nEffects[i] == nEffectId)
		{
			m_nEffects[i] = -1;
			return TRUE;
		}
	}
	return FALSE;
}
CEffectLight* CCharEffectContainer::GetEffectLight( int nLight )
{
	guardfunc;
	if( nLight < 0 || nLight >= eLightMax )
	{
		assert( false );
		return NULL;
	}
	return &m_EffectLights[nLight];

	unguard;
}

void CCharEffectContainer::OpenHitLight( DWORD dwLife, float r /* = 1.0f */, float g /* = 1.0f */, float b /* = 1.0f  */)
{
	guardfunc;
	CEffectLight* pLight = GetEffectLight( eLight_Hit );
	if( pLight )
	{
		pLight->m_bEnable = TRUE;
		pLight->m_dwStartTime = HQ_TimeGetTime();
		pLight->m_dwLife = dwLife;
		pLight->m_vDiffuse.x = r;
		pLight->m_vDiffuse.y = g;
		pLight->m_vDiffuse.z = b;
		pLight->m_fIntense = 0.5f;
	}
	unguard;
}

void CCharEffectContainer::OpenStateLight( DWORD dwLife, float r /* = 1.0f */, float g /* = 1.0f */, float b /* = 1.0f  */)
{
	guardfunc;
	CEffectLight* pLight = GetEffectLight( eLight_State );
	if( pLight )
	{
		pLight->m_bEnable = TRUE;
		pLight->m_dwStartTime = HQ_TimeGetTime();
		pLight->m_dwLife = dwLife;
		pLight->m_vDiffuse.x = r;
		pLight->m_vDiffuse.y = g;
		pLight->m_vDiffuse.z = b;
		pLight->m_fIntense = 0.5f;
	}
	unguard;
}

BOOL CCharEffectContainer::IsStateLightClosed()
{
	guardfunc;
	CEffectLight* pLight = GetEffectLight( eLight_State );
	if( pLight && !pLight->m_bEnable )
		return TRUE;
	else
		return FALSE;
	unguard;
}

void CCharEffectContainer::ClearStateLight()
{
	guardfunc;
	CEffectLight* pLight = GetEffectLight( eLight_State );
	if( pLight )
	{
		pLight->m_bEnable = FALSE;
		pLight->m_dwStartTime = 0;
		pLight->m_dwLife = 0;
		pLight->m_vDiffuse.x = 0;
		pLight->m_vDiffuse.y = 0;
		pLight->m_vDiffuse.z = 0;
		pLight->m_fIntense = 0;
	}
	unguard;
}

BOOL CCharEffectContainer::HasEffectLight()
{
	guardfunc;
	if( m_EffectLights[eLight_Hit].m_bEnable ||
		m_EffectLights[eLight_State].m_bEnable )
		return TRUE;
	return FALSE;
	unguard;
}
void CCharEffectContainer::UpdateLight( DWORD dwTime, D3DLIGHT9* pLight )
{
	guardfunc;
	if( !HasEffectLight() )
		return;
	CEffectLight* pHitLight = &m_EffectLights[eLight_Hit];
	if( pHitLight->m_bEnable )
	{
		if( pHitLight->m_dwStartTime+pHitLight->m_dwLife > dwTime )
		{
			pLight->Ambient.a = 0.0f;
			pLight->Ambient.r = 0.0f;
			pLight->Ambient.g = 0.0f;
			pLight->Ambient.b = 0.0f;

			DWORD dwPassed = dwTime-pHitLight->m_dwStartTime;
			const float PI = 3.1415926;
			const float fSpeed = PI/200.0f;
			float I = pHitLight->m_fIntense*abs(sinf( fSpeed*dwPassed ) );

			pLight->Ambient.a = 1.0f;
			pLight->Ambient.r = pHitLight->m_vDiffuse.x*I;
			pLight->Ambient.g = pHitLight->m_vDiffuse.y*I;
			pLight->Ambient.b = pHitLight->m_vDiffuse.z*I;
		}
		else
		{
			pHitLight->m_bEnable = FALSE;
		}
	}

	pHitLight = &m_EffectLights[eLight_State];
	if( pHitLight->m_bEnable )
	{
		if( pHitLight->m_dwStartTime+pHitLight->m_dwLife > dwTime )
		{
			pLight->Ambient.a = 1.0f;
			pLight->Ambient.r = pHitLight->m_vDiffuse.x;
			pLight->Ambient.g = pHitLight->m_vDiffuse.y;
			pLight->Ambient.b = pHitLight->m_vDiffuse.z;
		}
		else
		{
			pHitLight->m_bEnable = FALSE;
		}
	}
	unguard;
}

void CCharEffectContainer::FlagDestroy()
{
	guardfunc;
	m_bDestroyFlag = TRUE;

	for (int i = 0; i < eEffectMax; ++i)
	{
		if( m_nEffects[i] != -1 )
		{
			IEffect* pEffect = GetEffectMgr()->GetEffect(m_nEffects[i]);
			if (pEffect)
				pEffect->SetDead();
			m_nEffects[i] = -1;
		}
	}

	for( int i = 0; i < eEffectBindPartMax; i++ )
	{
		m_EffectHelpers[i].SetDestroyFlag();
	}
	unguard;
}

BOOL CCharEffectContainer::GetDestroyFlag()
{
	guardfunc;
	return m_bDestroyFlag;
	//return TRUE;
	unguard;
}