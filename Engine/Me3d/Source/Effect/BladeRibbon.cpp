#include "Me3d/effect/bladeribbon.h"
#include "Me3d/Include.h"
#include "Me3d/engine/Engine.h"
BladeRibbonEffect::BladeRibbonEffect():
m_nTextureId(-1),
m_bEnable(FALSE),
m_nNumFrame(0),
m_dwStartTime(0),
m_dwLife(0)
{}
void BladeRibbonEffect::Create( int nNumFrame )
{
	m_nMaxFrame = nNumFrame;
	if( m_nMaxFrame >= eMaxEdge )
		m_nMaxFrame = eMaxEdge;
}
BOOL BladeRibbonEffect::IsDead( DWORD dwTime )
{
	return dwTime >= m_dwStartTime+m_dwLife;
}
void BladeRibbonEffect::Update( int nFrame, float* pfFrameMatrices, int nNumFrame )
{
	m_nNumFrame = nNumFrame;
	if( m_nNumFrame > m_nMaxFrame )
		m_nNumFrame = m_nMaxFrame;
	D3DXMATRIX* pmatFrames = (D3DXMATRIX*)pfFrameMatrices;
	for( int nFrame = 0; nFrame < m_nNumFrame; nFrame++ )
	{
		D3DXVec3TransformCoord( (D3DXVECTOR3*)&m_edges[nFrame].vPoint[0], 
			(D3DXVECTOR3*)&m_vPoints[0],	
			(D3DXMATRIX*)&pmatFrames[nFrame] );

		D3DXVec3TransformCoord( (D3DXVECTOR3*)&m_edges[nFrame].vPoint[1], 
			(D3DXVECTOR3*)&m_vPoints[1],	
			(D3DXMATRIX*)&pmatFrames[nFrame] );
	}

}
void BladeRibbonEffect::Render( int nTextureId, DWORD dwColor, float fAlpha )
{
	if( m_nNumFrame < 2 )
		return;
	float k = 1.0f/(m_nNumFrame-1);
	
	DWORD dwRibbonColor = dwColor;

	for( int i = 0; i < m_nNumFrame; i++ )
	{
		GetDrawer()->DrawLine3D( 
			m_edges[i].vPoint[0], m_edges[i].vPoint[1], 0xffffffff );
	}
	//for(int i = 0; i < m_nNumFrame-1; i++ )
	//{
	//	m_verts[i*4].p = *(D3DXVECTOR3*)&m_edges[i].vPoint[0];
	//	m_verts[i*4].color = dwRibbonColor;
	//	m_verts[i*4].u = k*i;
	//	m_verts[i*4].v = 1.0f;

	//	m_verts[i*4+1].p = *(D3DXVECTOR3*)&m_edges[i].vPoint[1];
	//	m_verts[i*4+1].color = dwRibbonColor;
	//	m_verts[i*4+1].u = k*i;
	//	m_verts[i*4+1].v = 0;

	//	m_verts[i*4+2].p = *(D3DXVECTOR3*)&m_edges[i+1].vPoint[0];
	//	m_verts[i*4+2].color = dwRibbonColor;
	//	m_verts[i*4+2].u = k*i+k;
	//	m_verts[i*4+2].v = 1.0f;

	//	m_verts[i*4+3].p = *(D3DXVECTOR3*)&m_edges[i+1].vPoint[1];
	//	m_verts[i*4+3].color = dwRibbonColor;
	//	m_verts[i*4+3].u = k*i+k;
	//	m_verts[i*4+3].v = 0;
	//}

	//DWORD dwFlag = eTwoSided|eAlphaBlend|eZWriteDisable|eDstBlendOne;

	//GetEngine()->GetRenderer()->DirectPushSurface( 
	//	nTextureId,
	//	-1, 
	//	MEX2_SHADER,
	//	D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1, 
	//	sizeof( RVertex ), 
	//	(BYTE*)m_verts,
	//	(m_nNumFrame-1)*4, 
	//	(BYTE*)Emitter::GetCWIndexBuffer(), 
	//	(m_nNumFrame-1)*2,
	//	dwFlag|eLightingDisable );

	return;
}