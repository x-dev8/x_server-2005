#pragma once
#include <windows.h>
#include "Dxsdk/d3dx9.h"
#include "EffectHollywood.h"

class CEffectLight
{
public:
	CEffectLight();
public:
	BOOL			m_bEnable;
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vDir;
	DWORD			m_dwStartTime;
	DWORD			m_dwLife;
	D3DXVECTOR3		m_vDiffuse;
	float			m_fIntense;
};
// 一次发射性效果，相当一部分效果通过这个产生
// 每当player启动一个技能，
// 该类读取指定配置文件，
// 根据配置文件创建若干个模型效果，
// 
//class CSkillCast
//{
//public:
//	enum
//	{
//		eIntonateEffect,
//		eFireEffect,
//		eTrackEffect,
//		eHitEffect,
//		eMaxEffect,
//	};
//public:
//	CSkillCast();
//	~CSkillCast();
//
//	BOOL	Create( const char* pszFilename );
//	BOOL	OnIntonate();
//	BOOL	OnFire();
//	BOOL	OnHit();
//	void	Clear();
//public:
//	CModelEffect* m_pEffects[eMaxEffect];
//};


class CCharEffectContainer:public IEffectQuoter, public MeCommonAllocObj<CCharEffectContainer>
{
public:
	enum
	{
		eEmpty,
		ePoison,			// 中毒效果
		eStun,				// 眩晕
		eNpcTip,			// npc头顶的符号
		eEffectMax,
	};

	enum
	{
		eLight_Hit,
		eLight_State,
		eLightMax,
	};
	enum
	{
		eSkillCastMax = 32,
	};
public:
	CCharEffectContainer(void);
public:
	~CCharEffectContainer(void);

	void			Destroy();

	IEffectHelper*	GetEffectHelper( int nPart );
	IEffect*		GetEffect( int nEffect );

	BOOL			ApplyEffect( int nEffect, int nID );
	BOOL			ClearEffect( int nEffect );
	BOOL			ClearEffectNotDestroy( int nEffect );
	
	BOOL			UnRef( int nEffectID );

	void			FlagDestroy();
	BOOL			GetDestroyFlag();

	// 灯光相关
	CEffectLight*	GetEffectLight( int nLight );
	void			OpenHitLight( DWORD dwLife, float r = 1.0f, float g = 1.0f, float b = 1.0f );
	void			OpenStateLight( DWORD dwLife, float r = 1.0f, float g = 1.0f, float b = 1.0f );
	BOOL			IsStateLightClosed();
	void			ClearStateLight();

	BOOL			HasEffectLight();
	void			UpdateLight( DWORD dwTime, D3DLIGHT9* pLight );
	//BOOL			m_bDestroyFlag;

	void			SetId(int id) { m_nId = id; }
	int				GetId() { return m_nId; }

protected:
	CEffectHelper	m_EffectHelpers[eEffectBindPartMax];
	CEffectLight	m_EffectLights[eLightMax];
	int				m_nEffects[eEffectMax];
	int				m_nCharID;
	BOOL			m_bDestroyFlag;

	int				m_nId;

	//IEffect*		m_pEffects[eEffectMax];
	//std::vector<CSkillCast		m_SkillCast;
	//CSkillCast*		m_pSkillCasts[eSkillCastMax];
};
