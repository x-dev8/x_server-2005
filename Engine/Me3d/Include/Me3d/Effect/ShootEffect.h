#pragma once
// #include <d3dx8.h>
#include "EffectHollywood.h"
/*
	������Ч�������¼������ֹ���
	����˲�䣬master������Ч����
	���е�Ч����
	����Ŀ����Ч��
*/
class CShootEffect:public CBaseEffect
{
public:
	CShootEffect(void);
public:
	~CShootEffect(void);
public:
	virtual BOOL LoadSetting( const char* pszFilename );
	virtual void Update( DWORD dwTime );
	virtual void Render();
	virtual void Release();
	
	virtual void OnHit( DWORD dwTime );
	virtual void OnFire( DWORD dwTime );
public:
	BOOL	m_bHit;
	BOOL	m_bFire;
	D3DXVECTOR3 m_vTargetPos;
	D3DXVECTOR3 m_vFirePos;
	D3DXVECTOR3 m_vHeadPos;
	D3DXVECTOR3 m_vTailPos;
	DWORD	m_dwShootTime;

	float	m_fTailLength;

	IEffect* m_pFireEffect;
	IEffect* m_pHitEffect;
	BOOL	m_bHasFireEffect;
	BOOL	m_bHasFlyEffect;
	BOOL	m_bHasHitEffect;
	char	m_szFireEffectFile[MAX_PATH];
	char	m_szFlyEffectFile[MAX_PATH];
	char	m_szHitEffectFile[MAX_PATH];
};