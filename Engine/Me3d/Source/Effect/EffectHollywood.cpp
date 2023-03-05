#include "Me3d/Me3d.h"
#include "MeRTLibs.h"
#include <assert.h>
#include "Me3d/effect/EffectHollywood.h"
#include "FuncPerformanceLog.h"

CEffectHelper::CEffectHelper():
m_x(0.0f),
m_y(0.0f),
m_z(0.0f),
m_fTerrainZ(0.0f),
m_fRotZ(0.0f),
m_fScale(1.0f),
m_fFinalRenderAlpha(1.0f),
m_bDestroyFlag(FALSE)
{
	guardfunc;
	unguard;

}
CEffectHelper::~CEffectHelper()
{
	guardfunc;
	unguard;
}
void CEffectHelper::SetPos( float x, float y, float z )
{
	guardfunc;
	m_x = x;
	m_y = y;
	m_z = z;
	unguard;
}
void CEffectHelper::GetPos( float pos[3] )
{
	guardfunc;
	pos[0] = m_x;
	pos[1] = m_y;
	pos[2] = m_z;
	unguard;
}
void CEffectHelper::SetFinalRenderAlpha( float fAlpha )
{
	guardfunc;
	m_fFinalRenderAlpha = fAlpha;
	unguard;
}
float CEffectHelper::GetFinalRenderAlpha()
{
	guardfunc;
	return m_fFinalRenderAlpha;
	unguard;
}
void CEffectHelper::SetRot( float fRot )
{
	guardfunc;
	m_fRotZ = fRot;
	unguard;
}
float CEffectHelper::GetRot()
{
	guardfunc;
	return m_fRotZ;
	unguard;
}
void CEffectHelper::SetScale( float fScale )
{
	guardfunc;
	m_fScale = fScale;
	unguard;
}

float CEffectHelper::GetScale()
{
	guardfunc;
	return m_fScale;
	unguard;
}

void CEffectHelper::SetTerrainZ( float fTerrainZ )
{
	guardfunc;
	m_fTerrainZ = fTerrainZ;
	unguard;
}

float CEffectHelper::GetTerrainZ()
{
	guardfunc;
	return m_fTerrainZ;
	unguard;
}

void CEffectHelper::SetDestroyFlag()
{
	guardfunc;
	m_bDestroyFlag = TRUE;
	unguard;
}

BOOL CEffectHelper::IsDestroy()
{
	guardfunc;
	return m_bDestroyFlag;
	unguard;
}
//////////////////////////////////////////////////////////////////////////
CBaseEffect::CBaseEffect():
m_nID(-1),
m_pEffectQuoter(NULL),
m_nPlayerID(-1)
{
	guardfunc;
	unguard;
}

CBaseEffect::~CBaseEffect()
{
	guardfunc;
	unguard;

}

void CBaseEffect::SetID( int nID )
{
	guardfunc;
	m_nID = nID;
	unguard;

}

int CBaseEffect::GetID()
{
	guardfunc;
	return m_nID;
	unguard;

}

void CBaseEffect::Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance )
{
	guardfunc;
	unguard;
}

void CBaseEffect::Render()
{
	guardfunc;
	unguard;
}

BOOL CBaseEffect::IsDead( DWORD dwTime )
{
	guardfunc;
	return TRUE;
	unguard;
}

void CBaseEffect::SetDead()
{
	guardfunc;
	unguard;
}

void CBaseEffect::Release()
{
	guardfunc;
	delete this;
	unguard;
}
