#include "Me3d/shooteffect.h"
#include "Me3d/EffectManager.h"
#include "CfgFileLoader.h"
#include "HR3D/hr3d_include.h"
#include "Engine/Include/HREngine.h"
//#include "../SortLuaScript.h"
//#include "../LuaFuns.h"

CShootEffect::CShootEffect():
m_fTailLength(0.0f),
m_dwShootTime(0),
m_pFireEffect(NULL),
m_pHitEffect(NULL),
m_bFire(FALSE),
m_bHit(FALSE),
m_bHasFireEffect(FALSE),
m_bHasHitEffect(FALSE),
m_bHasFlyEffect(FALSE)
{}
CShootEffect::~CShootEffect()
{
	assert( m_pFireEffect == NULL );
	assert( m_pHitEffect == NULL );
}

BOOL CShootEffect::LoadSetting( const char* pszFilename )
{
	CCfgFileLoader l;
	if( !l.LoadFromFile( pszFilename ) )
		return FALSE;
	if( l.HasKey( "Fire" ) )
	{
		m_bHasFireEffect = TRUE;
		strcpy( m_szFireEffectFile, l.GetStringValue( "Fire" ) );
	}
	if( l.HasKey( "Hit" ) )
	{
		m_bHasHitEffect = TRUE;
		strcpy( m_szHitEffectFile, l.GetStringValue( "Hit" ) );
	}
	if( l.HasKey( "Fly" ) )
	{
		m_bHasFlyEffect = TRUE;
		strcpy( m_szFlyEffectFile, l.GetStringValue( "Fly" ) );
	}
	if( l.HasKey( "Period" ) )
	{
		m_dwShootTime = l.GetIntValue( "Period" );
	}
	
	
	return TRUE;
}

void CShootEffect::Release()
{
	if( m_pFireEffect )
	{
		GetEffectMgr()->ReleaseEffect( m_pFireEffect );
	}
	if( m_pHitEffect )
	{
		GetEffectMgr()->ReleaseEffect( m_pHitEffect );
	}
	delete this;
}

void CShootEffect::OnHit( DWORD dwTime )
{

	CModelEffect* pHitEffect = new CModelEffect;
	if( !pHitEffect->LoadSetting( m_szHitEffectFile ) )
	{
		pHitEffect->Release();
		return;
	}
	CModelEffect::Instance* pInstance = pHitEffect->AllocInstance();
	pInstance->vPos = m_vTargetPos;
	pInstance->dwBornTime = dwTime;
	//pHitEffect->GetEmitter()->SetStartTime( dwTime );
	GetEffectMgr()->RegisterEffect( pHitEffect );

}
void CShootEffect::OnFire( DWORD dwTime )
{
	CModelEffect* pFireEffect = new CModelEffect;
	if( !pFireEffect->LoadSetting( m_szFireEffectFile ) )
	{
		pFireEffect->Release();
		return;
	}
	CModelEffect::Instance* pInstance = pFireEffect->AllocInstance();
	pInstance->vPos = m_vFirePos;
	//pFireEffect->GetEmitter()->SetStartTime( dwTime );
	pInstance->dwBornTime = dwTime;
	GetEffectMgr()->RegisterEffect( pFireEffect );
}
void CShootEffect::Update( DWORD dwTime )
{
	if( !m_bFire )
	{
		m_bFire = TRUE;
		OnFire( dwTime );
	}


	DWORD dwPassedTime = 0;;//dwTime-GetEmitter()->GetStartTime();
	float t = (float)dwPassedTime/m_dwShootTime;

	
	D3DXVECTOR3 vDist = m_vTargetPos-m_vFirePos;
	D3DXVECTOR3 vShootDir;
	D3DXVec3Normalize( &vShootDir, &vDist );
	float fDist = D3DXVec3Length( &vDist );

	float fTailT = m_fTailLength/fDist;

	if( t < fTailT )
		fTailT = 0.0f;
	else
		fTailT = t-fTailT;
	if( t > 1.0f )
	{
		if( !m_bHit )
		{
			m_bHit = TRUE;
			OnHit( dwTime );
		}
		t = 1.0f;
	}
	if( fTailT > t )
		fTailT = t;

	m_vHeadPos = m_vFirePos+t*vDist;
	m_vTailPos = m_vFirePos+fTailT*vDist;
}

void CShootEffect::Render()
{
	GetHR3DDrawer()->DrawLine3D( m_vHeadPos, m_vTailPos, 0xffffffff );
}

