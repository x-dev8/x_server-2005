#pragma once
#include "me3d/effect/chainlighting.h"

class CChainEffect :public CChainLightingEffect
{
public:
	CChainEffect(void);
	~CChainEffect(void);
public:
	virtual void Update( DWORD dwTime, D3DXVECTOR3 vTargetPos, float fDistance );
	virtual BOOL LoadSetting( const char* pszFilename, BOOL bMilti  = false );
};
