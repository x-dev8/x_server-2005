#pragma once
#include <Windows.h>
#include "EffectHollywood.h"
#include "ModelEffect.h"
#include "FlashEffect.h"
#include "ChainLighting.h"
#include "MissileEffect.h"
//#include "ShootEffect.h"
#include "CharEffectContainer.h"
#include "MapStrToID.h"

/*
	effect系统设计
	effect的视觉效果，都是基于时间计算，与fps无关，
*/

class CEffectManager
{
public:
	enum
	{
		eMaxEffect = 1024,
		eMaxCharEffectContainer = 1024,
	};
	struct Cache : public MeCommonAllocObj<CEffectManager::Cache>
	{
		BYTE*	pbyBuffer;
		int		nSize;
		Cache():pbyBuffer(NULL),nSize(0){}
	};
public:
	CEffectManager(void);
public:
	~CEffectManager(void);
public:
	IEffect*	GetEffect( int nID );
	int			RegisterEffect( IEffect* pEffect );
//	int			RegisterCharEffectContainer( int nCharID );
	int			RegisterCharEffectContainer();

	CCharEffectContainer*		GetCharEffectContainer( int nIndex );
	Cache*		GetEffectSetting( const char* pszFilename );

	void		FlagCharEffectContainerDestroy( int nIndex );
	void		AddEffectSetting( const char* pszFilename, BYTE* pEffectSetting, int nBufferSize );
	void		ReleaseEffect( IEffect* pEffect );
	void		ReleaseEffect( int nEffectID );
	void		Update( DWORD dwTime );
	void		Render();
	void		Destroy();
	void		DestroyCache();

	void		ReleaseEffectNotDestroy( int nEffectID )
	{ 
		if (nEffectID >= 0 && nEffectID < eMaxEffect)
			m_pEffects[nEffectID] = NULL;
	}

	int GetEffectByPlayerID(int PlayerId);

public:
	void		SetTheLookerPos( D3DXVECTOR3 vPos );
	void		SetTheLookerViewDistance( float fDistance );
	bool		IsFull() const;

	bool		IsEffectCachePreLoadOK() const { return m_EffectCachePreLoadOK; }
	void		SetEffectCachePreLoadOK(bool val) { m_EffectCachePreLoadOK = val; }
protected:
	IEffect*	m_pEffects[eMaxEffect];
	CCharEffectContainer*	m_pCharEffectContainer[eMaxCharEffectContainer];

	//观看者的位置和视野的距离
	D3DXVECTOR3				m_vTheLookerPos;
	float					m_fTheLookerViewDistance;

	//特效记数器
	int			m_nEffectCount;
	int			m_nCharEffectContainerCount;

	CMapStrToIDMgr			m_EffectSettingFinder;
	std::vector<Cache*>		m_EffectCacheList;
	bool					m_EffectCachePreLoadOK;
};
extern CEffectManager* GetEffectMgr();
