#pragma once

#include "MeRTLibs.h"
#include "Renderer.h"
#include "MapContainer.h"
#include "Dxsdk/d3dx9.h"
#include <map>

// add [6/4/2008 whu]
namespace graphics
{
    class Material;
}
 
class CHRRenderSurface
{
public:
	enum
	{
		eMaxLayer = 3,
	};
public:
	CHRRenderSurface(){ Reset(); }
	void	Reset();
	//void	SortToView( float* pmatView );
	//void	SortToView( float* pEyePt );
	void	SortToView( D3DXVECTOR3 vEyePt, D3DXVECTOR3 vLookatPt );
	static void GlobalInitialize();
	static void GlobalDestroy();

public:
	enum EVertexDeclarationType {
		VertexDeclaration_XYZ = 0,
		VertexDeclaration_XYZW,
		VertexDeclaration_XYZ_LM,// with lightmap uv
		VertexDeclaration_Total,
	};
	enum {
		EVERTEXELEMEN_NUMBER = 5 + 1
	};
	static IDirect3DVertexDeclaration9 *ms_pVertexDeclHardware[VertexDeclaration_Total];
	static D3DVERTEXELEMENT9 ms_VertexElemHardware[VertexDeclaration_Total][EVERTEXELEMEN_NUMBER];
	static IDirect3DVertexDeclaration9 *ms_pSkeletonDeclHardware;
	static D3DVERTEXELEMENT9 ms_SkeletonElemHardware[7];
	BYTE*	m_pbyVertices;
	BYTE*	m_pbyNormals;
	BYTE*	m_pbyDiffuse;
	BYTE*	m_pbyIndices;
	BYTE*	m_pbyUVs[eMaxLayer];
	int		m_nVertexCount;
	int		m_nFaceCount;
	int		m_nShaderId;
	int		m_nTextureIds[eMaxLayer];
	DWORD	m_dwFVF;
	int		m_nVertexStride;
	int		m_nLayerCount;
	DWORD	m_dwFlag;
	BOOL	m_bSortToView;

	BOOL	m_bHasSelfMtl;
	D3DMATERIAL9 m_mtrl;
	

	BOOL	m_bHasSpecular;
	/*float	m_fMtlSpecular[5];*/
	//////////////////////////////////////////////////////////////////////////
	BYTE*	m_pbyVertexBuffer;
	BYTE*	m_pbyIndicesBuffer;
	float	m_fCameraZ;
	LPDIRECT3DINDEXBUFFER9 m_pIB;

    // add [6/4/2008 whu]
    graphics::Material* material;
};

class CHRRenderBuffer
{
public:
	CHRRenderBuffer();
	~CHRRenderBuffer();
	BYTE*	AllocBuffer( int nNeedBufferSize );
	void	Clear();
	BOOL	Create( size_t size );
protected:
	BYTE*	m_pbyBuffer;
	DWORD	m_dwBufferSize;
	DWORD	m_dwBufferUsed;
};



struct SortFace
{
	short nFaceId;
	float fDepth;
};

union Pointer
{
	BYTE*	byte;
	DWORD*	dw;
	float*	f;
	int*	i;
	D3DXVECTOR3* v;
	D3DXVECTOR2* uv;
};

struct SkeletonVertex
{
	float x, y, z;
	float blendWeights[4];
	unsigned char blendIndices[4];
	float nx, ny, nz;
};

struct BoneWeightAndIndex
{
	float blendWeights[4];
	unsigned char blendIndices[4];
};

extern int CompareSortFace( const void *arg1, const void *arg2 );
extern int	CompareSurface( const void *arg1, const void *arg2 );