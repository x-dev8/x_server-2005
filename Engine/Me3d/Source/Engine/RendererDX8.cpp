#include "Me3d/Me3d.h"
#include "Me3d/Engine/RendererDx8.h"
#include "Me3d/Engine/TextureDx8.h"
#include "Me3d/Engine/Engine.h"
#include "FuncPerformanceLog.h"
#include "Me3d/d3dutil.h"
#include <windows.h>
#include <assert.h>


IDirect3DVertexDeclaration9 *CHRRenderSurface::ms_pVertexDeclHardware[VertexDeclaration_Total] = {0};
D3DVERTEXELEMENT9 CHRRenderSurface::ms_VertexElemHardware[VertexDeclaration_Total][EVERTEXELEMEN_NUMBER] = 
{
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION,  0 },
		{ 1, 0, D3DDECLTYPE_FLOAT3,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,    0 },
		{ 2, 0, D3DDECLTYPE_D3DCOLOR,   D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_COLOR,		0 },
		{ 3, 0, D3DDECLTYPE_FLOAT2,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD,  0 },
		// 		{ 4, 0,     D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD,     1 },
		D3DDECL_END()
	},
	{
		{ 0, 0, D3DDECLTYPE_FLOAT4,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION,  0 },
		{ 1, 0, D3DDECLTYPE_FLOAT3,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,    0 },
		{ 2, 0, D3DDECLTYPE_D3DCOLOR,   D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_COLOR,		0 },
		{ 3, 0, D3DDECLTYPE_FLOAT2,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD,  0 },
		// 		{ 4, 0,     D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD,     1 },
		D3DDECL_END()
	},
	{
		{ 0, 0,     D3DDECLTYPE_FLOAT3,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION,  0 },
		{ 1, 0,		D3DDECLTYPE_FLOAT3,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,    0 },
		{ 2, 0,		D3DDECLTYPE_D3DCOLOR,   D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_COLOR,		0 },
		{ 3, 0,		D3DDECLTYPE_FLOAT2,     D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD,  0 },
		{ 4, 0,     D3DDECLTYPE_FLOAT2,		D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD,	1 },
		D3DDECL_END()
	}

};

IDirect3DVertexDeclaration9 *CHRRenderSurface::ms_pSkeletonDeclHardware = 0;
#if 0
D3DVERTEXELEMENT9 CHRRenderSurface::ms_SkeletonElemHardware[7] = 
{
	{ 0, 0,		D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,		0 },
	{ 1, 0,		D3DDECLTYPE_FLOAT3,     D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,			0 },
	{ 2, 0,		D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,			0 },
	{ 3, 0,		D3DDECLTYPE_FLOAT2,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,		0 },
	{ 4, 0,		D3DDECLTYPE_FLOAT4,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT,	0 },
	{ 4, 16,	D3DDECLTYPE_UBYTE4,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES,	0 },
	D3DDECL_END()
};
#else
D3DVERTEXELEMENT9 CHRRenderSurface::ms_SkeletonElemHardware[7] = 
{
	{ 0, 0,		D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,		0 },
	{ 0, 12,	D3DDECLTYPE_FLOAT4,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT,	0 },
	{ 0, 28,	D3DDECLTYPE_UBYTE4,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES,	0 },
	{ 0, 32,	D3DDECLTYPE_FLOAT3,     D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,			0 },
	{ 1, 0,		D3DDECLTYPE_FLOAT2,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,		0 },
	{ 2, 0,		D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,			0 },
	D3DDECL_END()
};
#endif

void CHRRenderSurface::GlobalInitialize()
{
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	for (int i = 0; i < VertexDeclaration_Total; ++i)
	{
		pd3dDevice->CreateVertexDeclaration( ms_VertexElemHardware[i], &ms_pVertexDeclHardware[i] );
	}

	HRESULT hr = pd3dDevice->CreateVertexDeclaration( ms_SkeletonElemHardware, &ms_pSkeletonDeclHardware );
	assert( hr == S_OK );
}

void CHRRenderSurface::GlobalDestroy()
{
	for (int i = 0; i < VertexDeclaration_Total; ++i)
	{
		if(ms_pVertexDeclHardware[i])
		{
			ms_pVertexDeclHardware[i]->Release();
			ms_pVertexDeclHardware[i] = 0;
		}	

	}

	if (ms_pSkeletonDeclHardware)
	{
		ms_pSkeletonDeclHardware->Release();
		ms_pSkeletonDeclHardware = 0;
	}
}
//struct SortFace
//{
//	short nFaceId;
//	float fDepth;
//};
//union Pointer
//{
//	BYTE*	byte;
//	DWORD*	dw;
//	float*	f;
//	int*	i;
//	D3DXVECTOR3* v;
//	D3DXVECTOR2* uv;
//};

static int CompareSortFace( const void *arg1, const void *arg2 )
{
	guardfunc;
	SortFace* face1 = (SortFace*)arg1;
	SortFace* face2 = (SortFace*)arg2;
	if( face1->fDepth > face2->fDepth )return -1;
	if( face1->fDepth < face2->fDepth )return 1;
	return 0;
	unguard;
}

int	CompareSurface( const void *arg1, const void *arg2 )
{
	guardfunc;
	CHRRenderSurface* surface1 = (CHRRenderSurface*)arg1;
	CHRRenderSurface* surface2 = (CHRRenderSurface*)arg2;
	if( surface1->m_fCameraZ > surface2->m_fCameraZ )return -1;
	if( surface1->m_fCameraZ < surface2->m_fCameraZ )return 1;
	return 0;
	unguard;
}

void CHRRenderSurface::Reset()
{ 
	guardfunc;
    memset( this, 0x00, sizeof( *this ) ); 

    // add [5/26/2008 whu]
    m_nTextureIds[2] = -1;
	unguard;
}

void CHRRenderSurface::SortToView( D3DXVECTOR3 vEyePt, D3DXVECTOR3 vLookatPt )
{
	guardfunc;
	return;
	int const MAX_FACE = 4096;
	static SortFace sf[MAX_FACE*3];
	static short faces[MAX_FACE*3];

	//D3DXVec3Normalize( &vLookatPt, &vLookatPt );
	
	D3DXVECTOR3 pos;
	D3DXVECTOR3 l;

	m_fCameraZ = 0;
	BYTE* pVB = (BYTE*)m_pbyVertexBuffer;
	short* pIndices = (short*)m_pbyIndicesBuffer;
	float fNearest = 0.f;
	float fFarest = 0.f;
	for( int i = 0; i < m_nFaceCount; i++ )
	{
		sf[i].nFaceId = i;
		int nPosStride = m_nVertexStride;

		pos = *(D3DXVECTOR3*)&pVB[pIndices[i*3]*nPosStride];
		pos += *(D3DXVECTOR3*)&pVB[pIndices[i*3+1]*nPosStride];
		pos += *(D3DXVECTOR3*)&pVB[pIndices[i*3+2]*nPosStride];

		pos /= 3;

		l.x = vEyePt.x - pos.x;
		l.y = vEyePt.y - pos.y;
		l.z = vEyePt.z - pos.z;

		//sf[i].fDepth = D3DXVec3LengthSq( &l );
		//m_fCameraZ += sf[i].fDepth;

		sf[i].fDepth = D3DXVec3LengthSq( &l );
		fFarest = max( sf[i].fDepth, fFarest );
		fNearest = min( sf[i].fDepth, fNearest );

	}
	m_fCameraZ = ( fNearest + fFarest ) / 2.f ;
	
	//for( int i = 0; i < m_nFaceCount; i++ )
	//{
	//	if( i % 2 == 1)
	//	{
	//		int tmp = sf[i].nFaceId;
	//		sf[i].nFaceId = sf[i-1].nFaceId;
	//		sf[i-1].nFaceId = tmp;
	//	}
	//}

	{
		//TRUETIMEBLOCK( "sortface" );
		qsort( sf, m_nFaceCount, sizeof( SortFace ) , CompareSortFace );
	}
	//int flag[177];
	//ZeroMemory( flag, sizeof(flag) );
	//for( int i = 0; i < m_nFaceCount; i++ )
	//{
	//	int nFlag = sf[i].nFaceId;
	//	if( flag[nFlag] > 0 )
	//	{
	//		int k = 0;
	//	}
	//	flag[nFlag]++;
	//}
	//for( int i = 0; i < m_nFaceCount; i++ )
	//{
	//	sf[i].nFaceId = i;
	//}
	
	//int nNumSortedFace = 0;
	//for( int i = 0; i < m_nFaceCount; i++ )
	//{
	//	SortFace* f0 = &sf[i];
	//	int nSlot = -1;
	//	SortFace* f1 = &
	//	for( int s = 0; s < nNumSortedFace; s++ )
	//	{
	//		
	//	}
	//}
	
	for( int i = 0; i < m_nFaceCount; i++ )
	{
		int nOffset = sf[i].nFaceId*3;
		faces[i*3] = pIndices[nOffset];
		faces[i*3+1] = pIndices[nOffset+1];
		faces[i*3+2] = pIndices[nOffset+2];
	}

	memcpy( pIndices, faces, sizeof( short )*3*m_nFaceCount );
	unguard;
}

CHRRenderBuffer::CHRRenderBuffer():
m_dwBufferUsed(0),
m_dwBufferSize(0),
m_pbyBuffer(NULL)
{
	guardfunc;
	m_dwBufferSize = 1024*1024*8;
	m_pbyBuffer = MeDefaultNew BYTE[m_dwBufferSize];
	unguard;
}

BOOL CHRRenderBuffer::Create( size_t size )
{
	m_dwBufferSize = size*sizeof(BYTE);
    m_pbyBuffer = MeDefaultNew BYTE[m_dwBufferSize];
    m_dwBufferUsed = 0;
    memset( m_pbyBuffer, 0, sizeof(BYTE) * m_dwBufferSize );
	return TRUE;
}

CHRRenderBuffer::~CHRRenderBuffer()
{
	guardfunc;
	if( m_pbyBuffer )
	{
		delete[] m_pbyBuffer;
		m_pbyBuffer = NULL;
	}
	unguard;
}
BYTE* CHRRenderBuffer::AllocBuffer( int nNeedBufferSize )
{
	guardfunc;
	if( m_dwBufferUsed+nNeedBufferSize >= m_dwBufferSize )
	{
		assert( false );
		return NULL;
	}
	if( !m_pbyBuffer )
	{
		assert( false );
		return NULL;
	}
	BYTE* pbyAllocBuffer = &m_pbyBuffer[m_dwBufferUsed];
	m_dwBufferUsed += nNeedBufferSize;
	return pbyAllocBuffer;
	unguard;
}
void CHRRenderBuffer::Clear()
{
	guardfunc;
	m_dwBufferUsed = 0;
	unguard;
}