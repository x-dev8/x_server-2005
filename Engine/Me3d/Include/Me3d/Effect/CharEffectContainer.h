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
// һ�η�����Ч�����൱һ����Ч��ͨ���������
// ÿ��player����һ�����ܣ�
// �����ȡָ�������ļ���
// ���������ļ��������ɸ�ģ��Ч����
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
		ePoison,			// �ж�Ч��
		eStun,				// ѣ��
		eNpcTip,			// npcͷ���ķ���
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

	// �ƹ����
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
