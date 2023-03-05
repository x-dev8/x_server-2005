#pragma once

#include "Me3d/Me3d.h"

class BladeRibbonEffect : public MeCommonAllocObj<BladeRibbonEffect>
{
public:
	enum
	{
		eMaxEdge = 64,
	};
	struct Edge
	{
		D3DXVECTOR3 vPoint[2];
	};
	struct RVertex
	{
		D3DXVECTOR3 p;
		DWORD		color;
		float		u, v;
	};
public:
	BladeRibbonEffect();
	void	Create( int nNumFrame );
	void	Update( int nFrame, float* pfFrameMatrices, int nNumFrame );
	void	Render( int nTextureId, DWORD dwColor, float fAlpha );
	void	Enable( BOOL bEnable ){ m_bEnable = bEnable; }
	BOOL	IsEnable(){ return m_bEnable; }
	BOOL	IsDead( DWORD );
public:
	BOOL	m_bEnable;
	DWORD	m_dwStartTime;
	DWORD	m_dwLife;
	D3DXVECTOR3 m_vPoints[2];
	Edge	m_edges[eMaxEdge];
	//D3DXMATRIX m_amatFrame[eMaxEdge];
	//RVertex	m_verts[eMaxEdge*eMaxEdge];
	int		m_nParentBoneId;
	int		m_nTextureId;
	int		m_nMaxFrame;
	int		m_nNumFrame;
};