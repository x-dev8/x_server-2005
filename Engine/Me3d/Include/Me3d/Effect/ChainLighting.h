#pragma once
#include <windows.h>
#include "Dxsdk/d3dx9.h"
#include <vector>
#include "EffectHollywood.h"
class CChainLightingEffect:public CBaseEffect
{
public:
	enum
	{
		eActionNotFloat,
		eActionFlowOut,	// 往外射
		eActionFlowIn,		// 吸收
	};
	enum
	{
		eBindBody,
		eBindLeftHand,
		eBindRightHand,
		
	};
	struct Texture
	{
		char	szPath[MAX_PATH];		// 路径
		int		nTextureId;				// 系统注册的纹理id
		Texture():nTextureId(-1){ memset( szPath, 0x00, MAX_PATH ); }
	};
	struct SVertex
	{
		D3DXVECTOR3 p;
		DWORD color;
		float u, v;
	};
	struct Segment
	{
		float fPoint[2];
	};
public:
	CChainLightingEffect();

	virtual BOOL IsDead( DWORD dwTime );
	virtual void Update( DWORD dwTime, D3DXVECTOR3 vPos, float fDistance );
	virtual void Release();
	virtual void SetDead();
	//virtual void Cull( D3DXVECTOR3 vPos, float fDistance );
	BOOL		LoadSetting( const char* pszFilename );
	BOOL		Compile( const char* pszFilename, BYTE** ppbyBuffer, int* pnBufferSize );
	BOOL		LoadFromMemory( BYTE* pbyBuffer, int nBufferSize );
	void		Destroy();
	void		Start();
	void		Render();
public:
	D3DXVECTOR3 m_vPos;
	IEffectHelper* m_pMaster;
	IEffectHelper* m_pTarget;
	int			m_nAction;
	int			m_nBind;			// 发射者的绑定位置
	int			m_nTargetBind;		// 目标的绑定位置
	char		m_szSound[MAX_PATH];
protected:
	DWORD		m_dwStartTime;
	DWORD		m_dwLife;
	DWORD		m_dwLastNoiseTime;
	DWORD		m_dwNoiseInterval;	// 电流产生噪声的间隔
	float		m_fFadeOutStart;
	float		m_fThick;			// 粗细
	float		m_fThickVar;		// 粗细变化范围
	float		m_fFlowSpeed;		// 流动速度
	int			m_nNumSegment;


	float		m_fScale;
	Texture		m_texture;
	std::vector<SVertex> m_verts;
	std::vector<Segment> m_segments;
	
};
