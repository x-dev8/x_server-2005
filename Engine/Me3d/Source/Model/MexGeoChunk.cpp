
#include "Me3d/Me3d.h"

#include "Me3d/Model/MexGeoChunk.h"
#include "Me3d/StdioEx.h"
#include "DataChunkWriter.h"
#include "Me3d/emitter.h"
#include "Me3d/camera.h"
#include "Me3d/config.h"
#include "Me3d/MathLib.h"
#include "Me3d/BaseGraphics.h"
#include "Me3d/Decal.h"
#include "Me3d/Global.h"
#include "Me3d/Spline.h"
//#include "Me3d/world.h"
//#include "Me3d/light.h"
//#include "engine.h"
#include "FuncPerformanceLog.h"
#include "datachunkwriter.h"
#include "helper.h"
//#include "CSVolumeMex2Src.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/RendererDx8.h"
#include "Me3d/Engine/EngineInstance.h"
#include "FilePath.h"
#include "Me3d/MathLib.h"

// #include "VirtualFileSystem/vfs.h"
#include "Dxsdk/d3dx9.h"
#include "Me3d/Engine\RendererDX.h"

//#include "Launcher/DataLauncher.h"
#include "Me3d/Shader.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/Model/Mex2.h"
#include "Me3d/Engine/MeShimmerCollector.h"
#include "MeTerrain/Lighting/StaticMeshInstance.h"

#define DECAL_VERTEX_COUNT 100

BOOL Mex2GeoChunkProperty::Read( Mex2Pointer inP, int nSize )
{
	guardfunc;
	CDataChunkLoader l( inP.byte, nSize );
	//Mex2Pointer p(inP.p);
	//nType = *p.i++;
	nType = l.ReadInt();
	while( !l.IsEndOfMemory() )
	{
		if( l.TryReadDwordChunk( 'flag', dwFlag ) ){}
		else l.SkipChunk();
	}

	return TRUE;
	unguard;
}

Vector	CMexChunkData::vertices[MAX_VERTEX_PER_CHUNK];
Vector	CMexChunkData::normals[MAX_VERTEX_PER_CHUNK];
DWORD	CMexChunkData::diffuses[MAX_VERTEX_PER_CHUNK];
Vector2	CMexChunkData::uvs[MAX_VERTEX_PER_CHUNK];

CMexChunkData::CMexChunkData():
m_nChunkID(0),
m_nVertexCount(0),
m_nFaceCount(0),
m_nMtlId(0),
m_pVertices(NULL),
m_pNormals(NULL),
m_pBoneGroupIndices(NULL),
m_pFaces(NULL),
m_pColors(NULL),
m_pszName(NULL),
m_shUVLayerCount(1),
m_shLightmapLayer(-1)
,m_bLighting(true)
,m_bHaveShadow( true )
,m_bTreeLeaf(false)
,IsDiffuseExist(false)
{
	for(int i = 0; i < eMaxUVLayer; ++i)
	{
		m_pUVs[i] = NULL;
	}

}

CMexChunkData::~CMexChunkData()
{
	MEX2_SAFE_DELETE_ARRAY(m_pszName);
	MEX2_SAFE_DELETE_ARRAY(m_pVertices);
	MEX2_SAFE_DELETE_ARRAY(m_pNormals);
	MEX2_SAFE_DELETE_ARRAY(m_pBoneGroupIndices);
	MEX2_SAFE_DELETE_ARRAY(m_pFaces);
	MEX2_SAFE_DELETE_ARRAY(m_pColors);
	for (int i = 0;i < m_shUVLayerCount; ++i)
	{
		MEX2_SAFE_DELETE_ARRAY(m_pUVs[i]);
	}
// 	MEX2_SAFE_DELETE_ARRAY(vertices);
// 	MEX2_SAFE_DELETE_ARRAY(normals);
// 	MEX2_SAFE_DELETE_ARRAY(diffuses);
// 	MEX2_SAFE_DELETE_ARRAY(uvs);
}

Mex2GeoChunk::Mex2GeoChunk(CMexChunkData* pChunkData):
CMexChunkBase(pChunkData),
m_bSingleBoneInfl(FALSE),
m_nSingleBoneId(-1),
m_pSrcMex(NULL)
,m_fOldU(0)
,m_fOldV(0)
,m_dwOldColor(0xfffffffe)
,m_oldAlpha(0xff)
,m_nTileFrameId(0)
,m_nUTiles(1)
,m_nVTiles(1)
{
	guardfunc;

	unguard;
}


Mex2GeoChunk::~Mex2GeoChunk()
{
	guardfunc;




	unguard;
}

void CMexChunkData::SetUVs( int nLayer, float* pfUVs )
{ 
	guardfunc;
	////	//CSALocker locker(this);
	if( nLayer < 0 || nLayer > eMaxUVLayer )
	{
		assert( false );
		return;
	}
	m_pUVs[nLayer] = (Vector2*)pfUVs;
	unguard;
}



const char* CMexChunkData::GetName()
{
	guardfunc;
	////	//CSALocker locker(this);
	if( m_pszName )
		return  m_pszName;
	return "";
	unguard;
}

// void Mex2GeoChunk::InitInstance()
// {
// 	if( GetIB() && GetVB() )
// 		return;
// 	if( GetFaceCount() > 0 )
// 	{
// 		HRESULT hr;
// 		LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
// 		short* shIBFace = NULL;
// 		if( !GetIB() )
// 		{
// 			while(1)
// 			{
// 				hr = pDev->CreateIndexBuffer( GetFaceCount()*3*sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &GetIB(), NULL );
// 				if( SUCCEEDED(hr) ) break;
// 			}
// 		}
// 
// 		while(1)
// 		{
// 			hr = GetIB()->Lock( 0, 0, (void**)&shIBFace, D3DLOCK_NOSYSLOCK );
// 			if( SUCCEEDED(hr) ) break;
// 		}
// 
// 		memcpy( shIBFace, m_pFaces, GetFaceCount()*sizeof(short)*3 );
// 
// 		while(1)
// 		{
// 			hr = GetIB()->Unlock();
// 			if( SUCCEEDED(hr) ) break;
// 		}
// 
// 
// 		MexVertex* pVBVertex = NULL;
// 		if( !m_pVB )
// 		{
// 			while(1)
// 			{
// 				hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(MexVertex), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &m_pVB, NULL );
// 				if( SUCCEEDED(hr) ) break;
// 			}
// 		}
// 
// 		while(1)
// 		{
// 			hr = m_pVB->Lock( 0, 0, (void**)&pVBVertex, D3DLOCK_NOSYSLOCK );
// 			if( SUCCEEDED(hr) ) break;
// 		}
// 
// 		Vector* pVertices = (Vector*)GetVertices();
// 		Vector* pNormals = (Vector*)GetNormals();
// 		Vector2* pUVs = (Vector2*)GetUVsLocked(0);
// 		DWORD* pColors = GetDiffuseLocked();
// 
// 		for( int i = 0; i < GetVertexCount(); i++, pVBVertex++, pVertices++, pNormals++, pUVs++ )
// 		{
// 			pVBVertex->x = pVertices->x;
// 			pVBVertex->y = pVertices->y;
// 			pVBVertex->z = pVertices->z;
// 
// 			//D3DXVec3Normalize( (D3DXVECTOR3*)pNormals, (D3DXVECTOR3*)pNormals );
// 
// 			pVBVertex->nx = pNormals->x;
// 			pVBVertex->ny = pNormals->y;
// 			pVBVertex->nz = pNormals->z;
// 
// 			if (GetDiffuseLocked())
// 				pVBVertex->diff = GetDiffuseLocked()[i];
// 			else
// 				pVBVertex->diff = 0xffffffff;
// 
// 			pVBVertex->u = pUVs->x;
// 			pVBVertex->v = pUVs->y;
// 		}
// 
// 		while(1)
// 		{
// 			hr = m_pVB->Unlock();
// 			if( SUCCEEDED(hr) ) break;
// 		}
// 	}
// }

BOOL CMexChunkData::Read( Mex2Pointer inP, int nSize, DWORD dwVersion )
{
	guardfunc;
	////	//CSALocker locker(this);
	Mex2Pointer p(inP.p);

	m_nVertexCount = *p.i++;
	m_nFaceCount = *p.i++;
	m_nMtlId = *p.i++;

	m_pVertices = MeNew Vector[m_nVertexCount];
	memcpy(m_pVertices,p.v3,sizeof(Vector)*m_nVertexCount);
	p.v3 += m_nVertexCount;
	m_pNormals = MeNew Vector[m_nVertexCount];
	memcpy(m_pNormals,p.v3,sizeof(Vector)*m_nVertexCount);
// 	m_pNormals = p.v3;
	p.v3 += m_nVertexCount;



// 	m_pUVs[0] = p.uv;
	m_pUVs[0] = MeNew Vector2[m_nVertexCount];
	memcpy(m_pUVs[0],p.uv,sizeof(Vector2)*m_nVertexCount);
	p.uv += m_nVertexCount;

	//if( m_pSrcMex->GetVersion() >= 101 )
	//{

	//}

	m_pBoneGroupIndices = new BYTE[m_nVertexCount];
	memcpy(m_pBoneGroupIndices,p.byte,sizeof(BYTE)*m_nVertexCount);
// 	m_pBoneGroupIndices = p.byte;
	p.byte += m_nVertexCount;

	m_pFaces = MeNew Mex2Face[m_nFaceCount];
	memcpy(m_pFaces,p.face,sizeof(Mex2Face)*m_nFaceCount);
// 	m_pFaces = p.face;
	p.face += m_nFaceCount;

	//   addded 2003.12.12
	while( p.c < inP.c+nSize )
	{
		switch( MEX_TAG( *p.dw ) )
		{
		case 'gcpt':
			{
				p.dw++;
				int size = *p.i++;
				m_property.Read( p, size );
				p.c += size; 
			}
			break;

		case 'name':
			{
				p.dw++;
				int size = *p.i++;
				Mex2Pointer s(p.p);
				//int nStrLen = *s.i++;
				m_pszName = new char[size];
				memcpy(m_pszName,p.c,sizeof(char)*size);
// 				m_pszName = s.c;
				p.c += size;

				m_bLighting = std::string(m_pszName).find(".nol") == std::string::npos;
				m_bTreeLeaf = std::string(m_pszName).find(".leaf") != std::string::npos;
				m_bHaveShadow = std::string(m_pszName).find("noshadow") == std::string::npos; //lyh去掉 前缀 . 
			}
			break;
		case 'vcol':
			{
				p.dw++;
				int size = (*p.i++);
				Mex2Pointer s(p.p);
				//int nStrLen = *s.i++;
				m_pColors = new DWORD[size*sizeof(char)/sizeof(DWORD)];
				memcpy(m_pColors,s.dw,sizeof(char)*size);
				IsDiffuseExist = true;
// 				m_pColors = s.dw;
// 				m_pOriginColors = s.dw;
				p.c += size;
			}
			break;
		case 'mtuv':
			{
				p.dw++;
				int size = *p.i++;
				Mex2Pointer s(p.p);
				m_shUVLayerCount = (short)*s.i++;
				for( int nLayer = 1; nLayer < m_shUVLayerCount; nLayer++ )
				{
					m_pUVs[nLayer] = MeNew Vector2[m_nVertexCount];
					memcpy(m_pUVs[nLayer],s.uv,sizeof(Vector2)*m_nVertexCount);
// 					m_pUVs[nLayer] = s.uv;
					s.uv += m_nVertexCount;
				}
				{
					// 灯光图UV索引
					if( m_shUVLayerCount > 1 )
						m_shLightmapLayer = (short)*s.i++;
				}
				p.c += size;
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
			}
		}
	}

	//if( pColors )
	//{
	//	BOOL bAllVertexColorIsWhite = TRUE;
	//	for( int i = 0; i < nVertexCount; i++ )
	//	{
	//		if( pColors[i] != 0xffffffff )
	//		{
	//			bAllVertexColorIsWhite = FALSE;
	//			break;
	//		}
	//	}
	//	if( bAllVertexColorIsWhite )
	//	{
	//		pColors = NULL;
	//	}
	//}

	return TRUE;
	unguard;
}


int	Mex2GeoChunk::CalcUseBoneGroup()
{
	guardfunc;
	////	//CSALocker locker(this);
	//   added 2004.08.03
	//int nBGCount = pSrcMex->GetBoneGroups()->vectorBoneGroup.size();
	int nBGCount = m_pSrcMex->GetBoneGroups()->GetBoneGroupCount();

	m_vectorUseBoneGroup.clear();
	m_vectorUseBoneGroup.resize( nBGCount );
	m_vectorUseBoneGroup.reserve( nBGCount );	
	size_t nSize = m_pSrcMex->GetBoneGroups()->GetBoneGroupCount();
	if( nSize > 0 )
	{
		//memset( &m_vectorUseBoneGroup[0], false, nSize );

		for( int nVertexId = 0; nVertexId < GetVertexCount(); nVertexId++ )
		{
			int nBGId = GetBoneGroupIndices()[nVertexId];
			if( nBGId <= m_vectorUseBoneGroup.size() )
				m_vectorUseBoneGroup[nBGId] = false;
			if( nBGId == 0xff )
				continue;
			m_vectorUseBoneGroup[nBGId] = true;
		}
	}


	return nBGCount;
	unguard;
}
// return false means infl bone count > 1
BOOL Mex2GeoChunk::CheckIsSingleBoneInfl()
{
	guardfunc;
	////	//CSALocker locker(this);
	m_bSingleBoneInfl = FALSE;
	if( !GetBoneGroupIndices() )
		return FALSE;
	if( !m_pSrcMex )
		return FALSE;
	if( !m_pSrcMex->GetBoneGroups() )
		return FALSE;
	IMexBoneGroups* pBoneGroups = m_pSrcMex->GetBoneGroups();
	Mex2BoneGroup* bg = (Mex2BoneGroup*)pBoneGroups->GetBoneGroup(0);
	if( !bg )
		return FALSE;
	int nVertex0BoneId = -1;

#ifdef _DEBUG
	for( int nVertexId = 0; nVertexId < GetVertexCount(); nVertexId++ )
	{
		int nBGId = 0xff;
		nBGId = GetBoneGroupIndices()[nVertexId];
		if( nBGId == 0xff ||
			nBGId == -1 )
			continue;
		Mex2BoneGroup* bonegroup = (Mex2BoneGroup*)pBoneGroups->GetBoneGroup(nBGId);
		if( !bonegroup )
			continue;
		// bone count > 0则肯定不是single bone infl
		//IMexBoneGroup* bg = pSrcMex->GetBoneGroups()->GetBoneGroup(nBGId);
// 		if( bonegroup->nBoneCount > 1 )
// 			OutputBoneGroupInfoByVertexId( nVertexId );
	}
	
#endif//_DEBUG

	for( int nVertexId = 0; nVertexId < GetVertexCount(); nVertexId++ )
	{
		int nBGId = 0xff;
		nBGId = GetBoneGroupIndices()[nVertexId];
		if( nBGId == 0xff ||
			nBGId == -1 )
			continue;
		Mex2BoneGroup* bonegroup = (Mex2BoneGroup*)pBoneGroups->GetBoneGroup(nBGId);
		if( !bonegroup )
			continue;
		// bone count > 0则肯定不是single bone infl
		//IMexBoneGroup* bg = pSrcMex->GetBoneGroups()->GetBoneGroup(nBGId);
		if( bonegroup->nBoneCount > 1 )
			//if( bg->GetBoneCount() > 1 )
			return FALSE;

		if( !bonegroup->pnBoneIds )
			continue;


		if( nVertexId == 0 )
		{
			nVertex0BoneId = bonegroup->pnBoneIds[0];
		}
		//nVertex0BoneId = bg->GetBoneID(0);
		// 如果此顶点bone与0号顶点bone不相同，
		//else if( bg[nBGId].pnBoneIds[nVertexId] != nVertex0BoneId )
		else if( bonegroup->pnBoneIds[0] != nVertex0BoneId )
		{
			return FALSE;
		}
		//else if( bg->GetBoneID(nVertexId) != nVertex0BoneId )

	}
	m_bSingleBoneInfl = TRUE;
	m_nSingleBoneId = nVertex0BoneId;
	return TRUE;
	unguard;
}
extern const int g_MaxBoneNum = 256;

void Mex2GeoChunk::BlendBoneGroup(MeMatrix* pMatrices, MeMatrix* pBoneGroupMatrices )
{
	guardfunc;
	//TRUETIMEFUNC();
	////	//CSALocker locker(this);
	if( !m_pSrcMex || !m_pSrcMex->GetBoneGroups() || !m_pSrcMex->GetSkeleton())
	{
		//assert( FALSE && "geomchunk has no bone groups" );
		return;
	}
	int nBGCount = m_pSrcMex->GetBoneGroups()->GetBoneGroupCount();
	Mex2BoneGroup* bg = (Mex2BoneGroup*)(m_pSrcMex->GetBoneGroups()->GetBoneGroup(0));
	if (1 == nBGCount && 1 == bg->nBoneCount)
	{//效率优化
		int nBoneId = bg->pnBoneIds[0];
		if (nBoneId >= 0)
		{
			memcpy(pBoneGroupMatrices[0].m,pMatrices[nBoneId].m,sizeof(float)*16);
		}
		return;
	}
	int n, k, i;
	static bool isReciprocalInitialize = false;
	static float fBoneCountReciprocal[g_MaxBoneNum] = {0};
	if (!isReciprocalInitialize)
	{
		for (int i = 1; i < g_MaxBoneNum; ++i)
		{
			fBoneCountReciprocal[i] = 1.0f/i;
		}
		isReciprocalInitialize = true;
	}
// 	float fWeight = 1.0f/nBGCount;
	// 保护 [1/5/2011 zhangjiayi]
	nBGCount = min( g_MaxBoneNum, nBGCount );
	for( i = 0; i < nBGCount; ++i )
	{
		// 如果没有使用到这个骨骼组
		//if( !m_vectorUseBoneGroup[i] )
		//bool b = m_vectorUseBoneGroup[i];
		//if( !pbUseBoneGroup[i] )
		//	continue;
		bg = (Mex2BoneGroup*)(m_pSrcMex->GetBoneGroups()->GetBoneGroup(i));
		int nBoneCount = bg->nBoneCount;

		float* f0 = (float*)pBoneGroupMatrices[i].m;

 		memset( f0, 0x00, sizeof(float)*16 );

		for( n = 0; n < nBoneCount; n++ )
		{
			int nBoneId = bg->pnBoneIds[n];

			if( nBoneId < 0 || nBoneId >= ( m_pSrcMex->GetSkeleton()->GetBoneCount() ) )
				continue;

			float* f1 = (float*)pMatrices[nBoneId].m;
			if( m_pSrcMex->GetVersion() >= 102 )
			{
				float fWeight = 1.0f;
				if( nBoneCount > 1 )
				{
					fWeight = bg->GetBoneWeight(n);
					//fWeight *= nBoneCount;
				}
				for( k = 0; k < 16; k+=4 )  //循环为每一根骨骼的世界矩阵都设置成模型的世界绝阵
				{
					f0[k+0] += f1[k+0] * fWeight;
					f0[k+1] += f1[k+1] * fWeight;
					f0[k+2] += f1[k+2] * fWeight;
					f0[k+3] += f1[k+3] * fWeight;
				}
			}
			else
				for( k = 0; k < 16; k+=4 )
				{
					f0[k+0] = f1[k+0];
					f0[k+1] = f1[k+1];
					f0[k+2] = f1[k+2];
					f0[k+3] = f1[k+3];
				}
		}

		for( k = 0; k < 16; k+=4 )
		{
			f0[k+0] *= fBoneCountReciprocal[nBGCount];
			f0[k+1] *= fBoneCountReciprocal[nBGCount];
			f0[k+2] *= fBoneCountReciprocal[nBGCount];
			f0[k+3] *= fBoneCountReciprocal[nBGCount];
		}
	}
	unguard;
}

void Mex2GeoChunk::OutputBoneGroupInfoByVertexId( int nVId )
{
	int nBGId = GetBoneGroupIndices()[nVId];
	Mex2BoneGroup* bg = (Mex2BoneGroup*)(m_pSrcMex->GetBoneGroups()->GetBoneGroup(nBGId));
	if( !bg )
		return;

	int nBoneCount = bg->nBoneCount;
	for( int i = 0 ; i < nBoneCount; ++ i )
	{
		MeOutputLog::Instance()->Print( "VertexId: %d, BgId: %d, BoneId: %d, Weight: %1.1f\n", nVId, nBGId, bg->GetBoneID(i), bg->GetBoneWeight(i) );
	}
}

bool Mex2GeoChunk::IsMtrlHasAlphaTest()
{
	// 如果有材质, 判断是否有AlphaTest
	if (m_pSrcMex->GetMtls() &&	m_pSrcMex->GetMtls()->GetMtlCount() >= 0 && GetMtlId() < m_pSrcMex->GetMtls()->GetMtlCount())
	{
		if (GetMtlId() != -1)
		{
			Mex2Material *pMtl = (Mex2Material *) m_pSrcMex->GetMtls()->GetMtl(GetMtlId());
			IMexLayer *layer0 = pMtl->GetLayer(0);
			if (layer0 != NULL && layer0->GetFlag() & MEX2_ALPHATEST)
			{
				return true;
			}
		}
	}
	return false;
}

bool Mex2GeoChunk::BlendVertex( float* pBlendedVertices, float* pBlendedNormals, int nMaxVertexCount, IMex* pMex, float* pMatrices ,MeMatrix* pTmpMatrices)
{
	if( GetVertexCount() == 0 || GetFaceCount() == 0 )
	{
		return false;
	}

	if( GetVertexCount() > nMaxVertexCount )
	{
		assert( false && "mex2 geom chunk render error, vertex count or face count is invalid" );
		return false;
	}

	if( pMex != m_pSrcMex )
	{
		//assert( 0 && "需要跟踪这个代码！");
		return false;
	}

	int nRetCount = 0;
  	Vector* pos = (Vector*)GetVerticesLocked();
	while(pos == NULL && nRetCount < 100)
	{
		pos = (Vector*)GetVerticesLocked();
		++nRetCount;
	}
	if (pos == NULL)
	{
		return false;
	}
	nRetCount = 0;
	Vector* normal = (Vector*)GetNormalsLocked();
	while(normal == NULL && nRetCount < 100)
	{
		normal = (Vector*)GetNormalsLocked();
		++nRetCount;
	}
	if (normal == NULL)
	{
		return false;
	}
	Vector p;
	if (pTmpMatrices == NULL)
	{
		static MeMatrix group[g_MaxBoneNum];//此处使用static有多线程风险，故非主线程调用自备buff通过接口pTmpMatrices传入使用
		pTmpMatrices = group;
#ifdef _DEBUG
		DWORD mainThreadId = GetCurrentThreadId();
		if (mainThreadId)
		{
			int i = mainThreadId;
		}
#endif
	}
	try
	{
		BlendBoneGroup( (MeMatrix*)pMatrices, pTmpMatrices );
		Vector* pvBlendedVertices = (Vector*)pBlendedVertices;
		Vector* pvBlendedNormals = (Vector*)pBlendedNormals;

		Vector vModelNormalPoint;
		for( int nVertexId = 0; nVertexId < GetVertexCount(); ++nVertexId, ++pos, ++normal )
		{
			int nBGId = GetBoneGroupIndices()[nVertexId]; //当前子集所在的骨骼组索引
			//assert( nBGId != -1 && "mex geo chunk render3 error, bg id is -1" );
			if( nBGId == 0xff )
			{
				memcpy(&pvBlendedVertices[nVertexId], pos, sizeof(Vector));

				if( pvBlendedNormals )
					memcpy(&pvBlendedNormals[nVertexId], normal, sizeof(Vector));
			}
			else 
			{
				D3DXVec3TransformCoord( (D3DXVECTOR3*)&pvBlendedVertices[nVertexId], 
					(D3DXVECTOR3*)pos,	
					(D3DXMATRIX*)&pTmpMatrices[nBGId] );

				if( pvBlendedNormals )
				{
					D3DXVec3TransformCoord( (D3DXVECTOR3*)&vModelNormalPoint, 
						(D3DXVECTOR3*)&GetNormalPoints(nVertexId),	
						(D3DXMATRIX*)&pTmpMatrices[nBGId] );
					D3DXVec3Subtract((D3DXVECTOR3*)&pvBlendedNormals[nVertexId], (D3DXVECTOR3*)&vModelNormalPoint, (D3DXVECTOR3*)&pvBlendedVertices[nVertexId]);
				}
			}
		}
		UnlockVertices();
		UnlockNormals();
		return true;
	}
	catch(...)
	{
		char acInfo[1024] = {0};
		Mex2* pMex2 = dynamic_cast<Mex2*>(pMex);
		Mex2* pMex3 = dynamic_cast<Mex2*>(m_pSrcMex);
		if( pMex2 && pMex3)
		{
			sprintf_s( acInfo, 1024, "BlendError！%s,%s", pMex2->GetFilename(), pMex3->GetFilename() );
		}
		MeLog::Instance()->Print( acInfo );
		return false;
	}
	
}



BOOL g_bLock = FALSE;

Mex2Material* Mex2GeoChunk::GetMtl()
{
	guardfunc;
	////	//CSALocker locker(this);
	//if( GetMtlId() < 0 || GetMtlId() >= m_pSrcMex->GetMtls()->vectorMtl.size() )
	if( GetMtlId() < 0 || !m_pSrcMex->GetMtls() || GetMtlId() >= m_pSrcMex->GetMtls()->GetMtlCount() )
		return NULL;
	//return &m_pSrcMex->GetMtls()->vectorMtl[GetMtlId()];
	return (Mex2Material*)m_pSrcMex->GetMtls()->GetMtl( GetMtlId() );
	unguard;
}



static CRITICAL_SECTION gs_BufferCS;
class CInitBufferCS
{
public:
	CInitBufferCS();
	~CInitBufferCS();
};

CInitBufferCS::CInitBufferCS()
{
	InitializeCriticalSection( &gs_BufferCS );
}

CInitBufferCS::~CInitBufferCS()
{
	DeleteCriticalSection( &gs_BufferCS );
}

static CInitBufferCS gs_InitBuffer;

void Mex2GeoChunk::_WriteDiffuseBuffer(DWORD dwColor, DWORD lockFlag)
{
	void* cb = 0;
	if (SUCCEEDED(GetDiffusesBuffer()->Lock(0, 0, &cb, lockFlag)))
	{
		DWORD* diffuse = (DWORD*)cb;
		for( int i = 0; i < GetVertexCount(); i++ )
		{
			// 						GetWorldDiffuses()[i] = dwColor;
			diffuse[i] = dwColor;
		}
		GetDiffusesBuffer()->Unlock();
	}
}

void Mex2GeoChunk::_ChangeVertexColorAlpha(BYTE alpha, DWORD lockFlag)
{
	void *cb = 0;
	if (SUCCEEDED(GetDiffusesBuffer()->Lock(0, 0, &cb, lockFlag)))
	{
		DWORD* diffuse = (DWORD*)cb;
		for( int i = 0; i < GetVertexCount(); i++ )
		{
			DWORD tempClr = diffuse[i];

			// 改变Alpha
			__asm
			{
				mov eax, tempClr;
				mov edx, eax;
				and edx, 0xffff;

				shr eax, 16;
				mov ah, alpha;

				shl eax, 16;
				or eax, edx;

				mov tempClr, eax;
			}
			diffuse[i] = tempClr;
		}
		GetDiffusesBuffer()->Unlock();
	}
}

void Mex2GeoChunk::_WriteUVBuffer(DWORD lockFlag)
{
	void* uvbuf = 0;
	if (SUCCEEDED(GetUvsBuffer()->Lock(0, 0, &uvbuf, lockFlag)))
	{
		memcpy(uvbuf, GetWorldUvs(), GetVertexCount()*sizeof(Vector2));
		GetUvsBuffer()->Unlock();
	}
}


void Mex2GeoChunk::_DoRender( const RenderParams* params )
{
	MeScopeProfileMexGeoChunkFun
	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
	static D3DLIGHT9 oldLight;
	if (params->m_bIsRenderModelSelected)
	{
		rd->GetLight(LIGHT_INDEX_TERRAIN,&oldLight);
		// 选中模型用红色显示
		D3DLIGHT9 light;
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Position = D3DXVECTOR3( 6, -6, 6 );
		light.Direction.x = 0.5f;
		light.Direction.y = 0.5f;
		light.Direction.z = 0.f;
		light.Ambient.a = 1.f;
		light.Ambient.r = 0.5f;
		light.Ambient.g = 0.2f;
		light.Ambient.b = 0.2f;
		light.Diffuse.a = 1.f;
		light.Diffuse.r = 0.5f;
		light.Diffuse.g = 0.2f;
		light.Diffuse.b = 0.2f;
		light.Specular.a = 0.0f;
		light.Specular.r = 0.3f;
		light.Specular.g = 0.3f;
		light.Specular.b = 0.3f;
		((RendererDx*)rd)->SetLight(LIGHT_INDEX_TERRAIN, &light);
	}

	if( params->pMatrices != NULL )
	{
		if( IsDynamicUSAGE() )
			if(!BlendVertex( (float*)GetWorldVertices(), (float*)GetWorldNormals(), MAX_VERTEX_PER_CHUNK, params->pMex, (float*)params->pMatrices ,NULL))
				return;
	}

	// 设置灯光 [11/11/2010 zhangjiayi]
	D3DXCOLOR kOldAmbient, kOldDiffuse;
	if( params->m_bDiffAmbChanged )
	{
		kOldAmbient = ((RendererDx*)GetEngine()->GetRenderer())->GetLightAmbient(LIGHT_INDEX_TERRAIN );
		kOldDiffuse = ((RendererDx*)GetEngine()->GetRenderer())->GetLightDiffuse(LIGHT_INDEX_TERRAIN );
		((RendererDx*)GetEngine()->GetRenderer())->SetLightAmbient(LIGHT_INDEX_TERRAIN, params->m_kAmbient );
		((RendererDx*)GetEngine()->GetRenderer())->SetLightDiffuse(LIGHT_INDEX_TERRAIN, params->m_kDiffuse );
		if( kOldAmbient != params->m_kAmbient ||
			kOldDiffuse != params->m_kDiffuse )
			GetEngine()->GetRenderer()->LightEnable(LIGHT_INDEX_TERRAIN,TRUE);
	}	

// 	if (GetVerticesBuffer() && g_usebuffer)
	{
		if (!IsDynamicUSAGE())
		{
			rd->SetTransform( D3DTS_WORLD, &params->pMatrices[m_nSingleBoneId] );
		}
		else
		{
			void* vb = 0;
			if (SUCCEEDED(GetVerticesBuffer()->Lock(0, 0, &vb, D3DLOCK_DISCARD)))
			{
				memcpy(vb, GetWorldVertices(), GetVertexCount()*sizeof(Vector));
				GetVerticesBuffer()->Unlock();
			}
			void* nb = 0;
			if (SUCCEEDED(GetNormalsBuffer()->Lock(0, 0, &nb, D3DLOCK_DISCARD)))
			{
				memcpy(nb, GetWorldNormals(), GetVertexCount()*sizeof(Vector));
				GetNormalsBuffer()->Unlock();
			}
			D3DXMATRIXA16 world;
			D3DXMatrixIdentity(&world);
			rd->SetTransform( D3DTS_WORLD, (float*)&world );
		}

		m_spRenderObject->DoRender();

		if (params->m_bIsRenderModelSelected)
		{
			((RendererDx*)rd)->SetLight(LIGHT_INDEX_TERRAIN, &oldLight);
		}

		D3DXMATRIXA16 world;
		D3DXMatrixIdentity(&world);
		rd->SetTransform( D3DTS_WORLD, (float*)&world );
	}
	if( params->m_bDiffAmbChanged )
	{
		((RendererDx*)GetEngine()->GetRenderer())->SetLightAmbient(LIGHT_INDEX_TERRAIN, kOldAmbient );
		((RendererDx*)GetEngine()->GetRenderer())->SetLightDiffuse(LIGHT_INDEX_TERRAIN, kOldDiffuse );
		if( kOldAmbient != params->m_kAmbient ||
			kOldDiffuse != params->m_kDiffuse )
			GetEngine()->GetRenderer()->LightEnable(LIGHT_INDEX_TERRAIN,TRUE);
	}	

}

void Mex2GeoChunk::DoRender( bool bPost /*= false*/ )
{
	MeScopeProfileMexGeoChunkFun
	//EnterCriticalSection( &gs_BufferCS );

	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();

	short stTexture = m_spRenderObject->GetUseTexId();
	if (bPost)
	{
		int nPostIndex = 0;
		for( RenderParams::OtherInfosConstIter otherit = GetOtherInfos( bPost ).begin(); 
			otherit != GetOtherInfos( bPost ).end() ; ++ otherit )
		{	
			const RenderParams* params = (*otherit );
			if (nPostIndex < m_nCurrPostIndex && GetCollectibleType() != SortRenderable::eCT_Shimmer )
			{
				++nPostIndex;
				continue;
			}
			else
			{
				m_spRenderObject->SetFlag(params->dwFlag);
				m_spRenderObject->SetUseTexId(params->stUseTexId);
				m_spRenderObject->SetLightmapTexId(params->m_nLightmapTexId);
				m_spRenderObject->SetLightmapUVScale( params->m_vLightmapUVScale );
				m_spRenderObject->SetLightmapUVOffset( params->m_vLightmapUVOffset );
				if( m_spRenderObject->BeginRender() )
				{
					rd->SetGlobalTransparent( params->fAlpha );
					_DoRender(params);
					m_spRenderObject->EndRender();
				}
				++m_nCurrPostIndex;
				
				if( ClearOtherInfo( bPost ) || GetCollectibleType() != SortRenderable::eCT_Shimmer )
					break;
			}
		}
	}
	else
	{
		if( m_spRenderObject->BeginRender() )//LYH设置渲染状态，设置shader参数
		{
			for( RenderParams::OtherInfosConstIter otherit = GetOtherInfos( bPost ).begin(); 
				otherit != GetOtherInfos( bPost ).end() ; ++ otherit )
			{	
				const RenderParams* params = (*otherit );
				rd->SetGlobalTransparent(1.f);
				if( params->fGlobalAlpha < 1.0f )
				{
					continue;
				}	
				if( params->dwFlag & eShimmer )
					continue;

				bool bReStart = false;
				if (params->stUseTexId != stTexture)
				{//支持同一个模型，利用不同贴图换装					
					bReStart = true;
				}
				//有lightmap时重新设置
				if( params->m_nLightmapTexId != m_spRenderObject->GetLightmapTexId() ||
					params->m_vLightmapUVScale != m_spRenderObject->GetLightmapUVScale() ||
					params->m_vLightmapUVOffset != m_spRenderObject->GetLightmapUVOffset() )
				{
					bReStart = true;
				}
				if( bReStart )
				{
					m_spRenderObject->EndRender();
					m_spRenderObject->SetUseTexId(params->stUseTexId);
					m_spRenderObject->SetLightmapTexId(params->m_nLightmapTexId);
					m_spRenderObject->SetLightmapUVScale( params->m_vLightmapUVScale );
					m_spRenderObject->SetLightmapUVOffset( params->m_vLightmapUVOffset );
					if( !m_spRenderObject->BeginRender() )
						continue;
				}

				_DoRender(params);
			}
			m_spRenderObject->EndRender();
		}
		ClearOtherInfo( bPost );
	}


	//LeaveCriticalSection( &gs_BufferCS );

}

void Mex2GeoChunk::_Render( RenderParams* params )
						   
{
	MeScopeProfileMexGeoChunkFun
	//EnterCriticalSection( &gs_BufferCS );

// 	if (GetVerticesBuffer() && g_usebuffer)
	{
		MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;
		MeModelRenderObject* pkFinal = dynamic_cast< MeModelRenderObject* >( pkObject );
		if( !pkFinal )
			return;

		short nShaderID = MEX2_SHADER;

		bool bPost = false;
		RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();

		pkFinal->SetUseTexId( params->stUseTexId );
		pkFinal->SetUseLuminanceTexId( params->stUseLuminanceTexId );
		if ( GetCollectibleType() == SortRenderable::eCT_Shimmer )
		{
			//pkFinal->SetAddMapId( MeShimmerCollector::GetFrameTextureId() );
			pkFinal->SetAddMapId( params->stUseHeatShimmerTexId );
			if (pkFinal->GetUseLuminanceTexId() == -1)
				pkFinal->SetUseLuminanceTexId( params->stUseShimmerGrayTexId );
			params->dwFlag |= ( eShimmer | eTwoSided );
			params->dwFlag &= ~eAlphaBlend;
			bPost = true;
		}			
		else
		{
            // added by zhuomeng.hu		[1/25/2011]
            params->fGlobalAlpha = params->fAlpha;
			if ( IsAlphaChunk(params) )
			{
				params->dwFlag |= eAlphaBlend;	
				SetCollectibleType( SortRenderable::eCT_AlphaBlend );
				bPost = true;
			}
			else
			{
				params->fGlobalAlpha = 1.0;
			}
		}
		
		if ( MeRenderManager::Instance()->IsFreshObject( this ) )			
		{
			pkFinal->SetShaderId( nShaderID );
			pkFinal->SetFVF( rd->GetCurrentSurface()->m_dwFVF );
			pkFinal->SetVertexCount( GetVertexCount() );
			pkFinal->SetVB( GetVerticesBuffer() );
			pkFinal->SetNB( GetNormalsBuffer() );
			pkFinal->SetDB( GetDiffusesBuffer() );
			pkFinal->SetUVB( GetUvsBuffer() );
			pkFinal->SetUVB2( GetUvsBuffer2() );
			pkFinal->SetIB( GetIB() );
			pkFinal->SetFaceCount( GetFaceCount() );
			if( params->m_nLightmapTexId > -1 )//有lightmap
			{
				pkFinal->SetLightmapTexId( params->m_nLightmapTexId );
				pkFinal->SetLightmapUVScale( params->m_vLightmapUVScale );
				pkFinal->SetLightmapUVOffset( params->m_vLightmapUVOffset );
			}			
			if (!bPost)
			{
				pkFinal->SetFlag( params->dwFlag );
			}
			pkObject->GenerateKey();
			MeRenderManager::Instance()->AddObject( this );
		}		
		PushOtherInfo( params, bPost );
		SetCollectibleType( SortRenderable::eCT_Count );

// 		short nShaderID = MEX2_SHADER;
// 
// 		RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
// 		params->fGlobalAlpha = rd->GetGlobalTransparent();
// 		if( IsAlphaChunk(params) )
// 		{
// 			params->dwFlag |= eAlphaBlend;	
// 		}
// 		else
// 		{
// 			params->fGlobalAlpha = 1.0;
// 		}
// 
// 		MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;
// 		MeModelRenderObject* pkFinal = dynamic_cast< MeModelRenderObject* >( pkObject );		
// 		if( pkFinal )
// 		{
// 			bool bPost = false;
// 			if( ( IsAlphaChunk(params) ) && ( GetCollectibleType() != SortRenderable::eCT_Shimmer ) )
// 			{
// 				SetCollectibleType( SortRenderable::eCT_AlphaBlend );
// 				bPost = true;
// 			}
// 			if( MeRenderManager::Instance()->IsFreshObject( this ) )				
// 			{
// 				pkFinal->SetUseTexId( params->stUseTexId );
// 				if( GetCollectibleType() == SortRenderable::eCT_Shimmer )
// 				{
// 					pkFinal->SetAddMapId( MeShimmerCollector::GetFrameTextureId() );
// 					params->dwFlag |= ( eShimmer | eTwoSided );
// 					params->dwFlag &= ~eAlphaBlend;
// 					bPost = true;
// 				}
// 				pkFinal->SetShaderId( nShaderID );
// 				pkFinal->SetFVF( rd->GetCurrentSurface()->m_dwFVF );
// 				pkFinal->SetVertexCount( GetVertexCount() );
// 				pkFinal->SetVB( GetVerticesBuffer() );
// 				pkFinal->SetNB( GetNormalsBuffer() );
// 				pkFinal->SetDB( GetDiffusesBuffer() );
// 				pkFinal->SetUVB( GetUvsBuffer() );
// 				pkFinal->SetIB( GetIB() );
// 				pkFinal->SetFaceCount( GetFaceCount() );
// 				if (!bPost)
// 				{
// 					pkFinal->SetFlag( params->dwFlag );
// 				}
// 				pkFinal->SetUseLuminanceTexId( params->stUseLuminanceTexId );
// 				pkObject->GenerateKey();
// 				MeRenderManager::Instance()->AddObject( this );
// 			}			
// 			PushOtherInfo( params, bPost );
// 			SetCollectibleType( SortRenderable::eCT_Count );
// 			
// 		}
// 
// // 		D3DXMATRIXA16 world;
// // 		D3DXMatrixIdentity(&world);
// // 		rd->SetTransform( D3DTS_WORLD, (float*)&world );
	}
	//LeaveCriticalSection( &gs_BufferCS );
}

bool Mex2GeoChunk::Render( RenderParams* params,
						  DWORD dwFlagEx,
						  IReplaceableTextureProj* pLuminanceTextureProj,
						  int* pVertexCount/*=NULL*/,
						  int* pFaceCount/*=NULL*/ )
{
	MeScopeProfileMexGeoChunkFun
	guardfunc;
	if( GetVertexCount() == 0 || GetFaceCount() == 0 )
		return false;


	if( GetVertexCount() >= MAX_VERTEX_PER_CHUNK )
	{
		assert( false );
		return false;
	}

	IMex* pMex = params->pMex;
	float* pMatrices = params->pMatrices;
	IRenderer* pRenderer = GetEngine()->GetRenderer();
	IReplaceableTextureProj* pReplaceableTextureProj = params->pReplaceableTextureProj; 
// 	float fAlpha = params->fAlpha;
// 	std::map<int, std::vector<CombineModelData>>* pMapCombineSubmodel = params->mapCombineSubmodel;

	// 是否能合并渲染，要求非半透，非选中状态，是否受光情况相同，有材质，先尝试合并静态模型，QL，2009/05/07
// 	BOOL bCanCombine = pMapCombineSubmodel ? TRUE: FALSE;
// 	BOOL bUseNullMtl = FALSE;

	// 渲染地板辅助模型，并且选中当前渲染模型，则隐藏显示模型
	if( GetMe3dConfig()->GetRenderHelper() && GetMe3dConfig()->m_bIsRenderModelSelected )
		return false;

	if( GetMe3dConfig()->m_bIsRenderModelSelected )
	{
		params->m_bIsRenderModelSelected = true;
	}

	if( pMex == NULL )
		pMex = m_pSrcMex;    
	if( !pMex )
		return false;

	/*
	 * 2012.6.7 wangshuai 直接使用VisibleFloat, 废弃VisibleBool, 因为这2份数据重复了
	 */
	// 如果是仅受一根骨骼影响,而且此骨骼当前不可见
	if( m_bSingleBoneInfl && m_nSingleBoneId != -1 && !m_pSrcMex->IsBoneVisible( params->nFrameId, m_nSingleBoneId ) )
	{
		return false;
	}

	BOOL bUseNullMtl = FALSE;
	if( IsFloor() || IsCollision() ||IsSupperFloor())
		bUseNullMtl = TRUE;

	BOOL bAlphaBlend = FALSE;

	if( m_pSrcMex->GetBoneVisibleFloat( params->nFrameId, m_nSingleBoneId ) > 0 )
	{
		float fBoneAlpha = m_pSrcMex->GetBoneVisibleFloat( params->nFrameId, m_nSingleBoneId );
		params->fAlpha *= fBoneAlpha;
// 		pRenderer->SetGlobalTransparent( params->fAlpha );

        // added by ZhuoMeng.Hu		[12/13/2010]
        bAlphaBlend = TRUE;
	}

	float fAlpha = params->fAlpha;
	bool bMustUseAlphaBlend = params->bMustUseAlphaBlend;

	DWORD dwFlag = dwFlagEx;
	short stUseTexId = -1, stUseTexId2 = -1, stUserShimmerGrayTexId = -1, stUseLuminanceTexId = -1;

	BOOL bAlphaTest = dwFlagEx & eAlphaTest ? TRUE : FALSE;
	DWORD dwColor = 0xffffffff;
	DWORD dwBlendMode = MEX2_MODULATE2X;//modifyed, jiayi,[09.03.14]调低亮度
	//dwBlendMode = MEX2_MODULATE;
	float fu = 0.0f, fv = 0.0f;
	BOOL bTiling = FALSE;
	int nTileFrameId = 0;
	int nUTiles = 1, nVTiles = 1;

	Mex2Material* pMtl = NULL;
	BOOL bHasMtlAnim = FALSE;
	BOOL bCanCombine = FALSE;
	BOOL bMtrlHasAlphaChange = FALSE;

	// 如果有材质
	if ( m_pSrcMex->GetMtls() &&	m_pSrcMex->GetMtls()->GetMtlCount() >= 0 && GetMtlId() < m_pSrcMex->GetMtls()->GetMtlCount())
	{
		if ( GetMtlId() != -1  )
			pMtl = (Mex2Material*)m_pSrcMex->GetMtls()->GetMtl( GetMtlId() );

		if ( !pMtl )
		{
			bCanCombine = FALSE;	// 无材质暂定无法合并模型
		}
		else if ( pMtl->GetLayer(0) )
		{
			assert( pMtl->GetLayerCount() > 0 && "mex geomchunk render error, mtl layer count must > 0" );
			if ( pMtl->GetLayer(0)->GetFlag() & MEX2_TWOSIDED )
				dwFlag |= eTwoSided;

			assert( GetMtlId() != -1 && "mex chunk render 3 failed, mtl id = -1" );

			int nLocalTextureId = pMtl->GetLayer(0)->GetTextureID();// pMtl->pLayers[0].nTextureId;
			if (pReplaceableTextureProj != NULL)
			{
				stUseTexId = pReplaceableTextureProj->GetRenderTextureID( nLocalTextureId );
			}

			if (params->pShimmerGrayTextureProj != NULL)
				stUserShimmerGrayTexId = params->pShimmerGrayTextureProj->GetRenderTextureID( nLocalTextureId );

			// add [5/26/2008 whu]
			if (pLuminanceTextureProj != NULL)
			{
				stUseLuminanceTexId = pLuminanceTextureProj->GetRenderTextureID( nLocalTextureId );
			}

			IMexLayer* pLayer0 = pMtl->GetLayer(0);
			DWORD dwLayerFlag = pLayer0->GetFlag();

			if( bMustUseAlphaBlend )
			{
				bAlphaBlend = TRUE;
				bAlphaTest = FALSE;
				dwFlag &= (~eTwoSided);
				dwFlag |= eZWriteDisable;
			}
			else
			{
				if( dwLayerFlag & MEX2_ALPHABLEND )
				{
					bAlphaBlend = TRUE;
					if( !( dwLayerFlag & MEX2_ZWRITEENABLE )  )
						dwFlag |= eZWriteDisable;
				}

				if( dwLayerFlag & MEX2_ALPHATEST )
				{
					bAlphaTest = TRUE;
				}
			}

			if( dwLayerFlag & MEX2_SPECULARENABLE )
			{
				dwFlag |= eSpecularEnable;
				//pRenderer->SetMtlSpecular( pKey->shinstr, 1.0f, pKey->sr, pKey->sg, pKey->sb );
				pRenderer->EnableSpecular( TRUE );
			}

			int nFrameId = params->nFrameId;
			if( nFrameId >= 0 )
			{
				Mex2MtlAnim* pAnim = pMtl->colorTracks.vectorColorTrack[0];
				bMtrlHasAlphaChange = pAnim->bHasAlphaChange;
				if( IsAvatarComponent() )
				{
					DWORD dwElapseTime = HQ_TimeGetTime() - pAnim->nLastTime;
					if( pAnim->nLastTime == 0 )
					{
						nFrameId = 0;
						pAnim->nLastTime = HQ_TimeGetTime();
					}
					else if( dwElapseTime > FRAMEPERSEC )
					{
						nFrameId = pAnim->nLastFrameId + (HQ_TimeGetTime() - pAnim->nLastTime) / FRAMEPERSEC;
						pAnim->nLastTime = HQ_TimeGetTime();
					}
					else
						nFrameId = pAnim->nLastFrameId;
				}

				if( nFrameId >= pAnim->nKeyCount && pAnim->nKeyCount > 0 )
					nFrameId %= pAnim->nKeyCount;
				pAnim->nLastFrameId = nFrameId;
				if (nFrameId < pAnim->nKeyCount)
				{
					Mex2ColorKey* pKey = &pAnim->pKeys[nFrameId];

					if( !bAlphaTest && bAlphaBlend /*&&
												   pMtl->HasColorKey()*/ ||
												   !IsLighting() )
					{
						bHasMtlAnim = TRUE;

						//if( !bAlphaTest )
						dwFlag |= eLightingDisable;

						// 需要根据动画帧数来计算出当前自己的帧编号
						nTileFrameId = int((nFrameId*ONEFRAMEINTERVAL+pAnim->nStartFrame)/ max( 0.1f, pAnim->fPlaybackRate ));
						nTileFrameId %= max( 1, pAnim->nUTile*pAnim->nVTile );

						if( pKey )
						{
							dwBlendMode = pKey->dwBlendMode;
							if( pKey && pKey->selfillum == 1.0f )
								dwFlag |= eDstBlendOne;

							DWORD a = (DWORD)(pKey->alpha*255);
							DWORD r = (DWORD)(pKey->dr*255);
							DWORD g = (DWORD)(pKey->dg*255);
							DWORD b = (DWORD)(pKey->db*255);

							dwColor = a<<24|r<<16|g<<8|b;
						}
					}
					bTiling = pAnim->bTiling;
					if(!bTiling)
					{
						dwFlag |= eUClamp;
						dwFlag |= eVClamp;
						dwFlag |= eNoMipmap;
					}

					nUTiles = pAnim->nUTile;
					nVTiles = pAnim->nVTile;

					if( pKey )
					{
						fu = pKey->uoffset;
						fv = pKey->voffset;
					}
				}
			}			
		}
	}
	else
		bCanCombine = FALSE;	// 无材质暂定无法合并模型

	////dwFlag &= (~eZWriteDisable);
	//dwFlag &= (~eLightingDisable);
	//dwBlendMode = MEX2_MODULATE2X;

	switch( dwBlendMode )
	{
	case MEX2_MODULATE:
		dwFlag |= eOpModulate1X;
		break;
	case MEX2_MODULATE2X:
		dwFlag |= eOpModulate2X;//modified,jiayi
		break;
	case MEX2_ADD:
		dwFlag |= eOpAdd;
		break;
	default:
		dwFlag |= eOpModulate1X;
		break;
	}

	long const MAX_VERTEX = 32768;//8*1024*1024;//32768;// //32768;
	if( GetVertexCount() >= MAX_VERTEX )
	{
		assert( false );
		return false;
	}

	// 物体上的特效不受影响
	BOOL bEffect = FALSE;
	switch( m_ChunkData->GetPropertyP()->nType ) 
	{
	case Mex2GeoChunkProperty::eBillboard:
		bEffect = TRUE;
		break;
	}
	//DWORD dwFVF = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1;

	dwFlag |= eMipmapLinear;

	if( bAlphaTest )
	{
		bAlphaBlend = FALSE;
		dwFlag |= eAlphaTest;
	}

	if( bAlphaBlend )
	{
		//dwFlag |= eTwoSided;
		dwFlag |= eAlphaBlend;
		dwFlag |= eSortByFarZ;
		//dwFlag &= (~eLightingDisable);commented out ,jiayi,[09.03.14]
	}

	if (IsTreeLeaf())
	{
		dwFlag |= eRenderTreeLeaf;
	}

	// 不要贴图
	if( bUseNullMtl )
	{
		stUseTexId = -1;
		bCanCombine = FALSE;	// 无材质暂定无法合并模型
	}

	BOOL bHasSelfDiffuse = FALSE;
	if( IsExistDiffuse() )
		bHasSelfDiffuse = TRUE;

	if ( bHasSelfDiffuse )
	{
		// added, jiayi, [2009/12/21]
		if( !( dwFlagEx & eOpModulate1X ) )
			dwFlag |= eOpModulate2X;//modified,jiayi,[09.04.08],提高亮度，当有顶点色的时候
	}

	if ( dwFlag & eSortByFarZ  )
		bCanCombine = FALSE;	// 半透模型暂定不进行合并

	if ( IsExistDiffuse() )
	{
		//dwFlag |= eLightingDisable;//jiayi commented out [09.03.11]
		//有顶点色 不需要Modulate2
		dwBlendMode = MEX2_MODULATE;
	}

	//if( (dwColor != m_dwOldColor) && (!IsExistDiffuse()))
	// 2012.5.9 wangshuai, 修正了UV动画渐变无效的问题
	// 上面的代码是原来的, 由于多了一个感叹号, 导致UV动画的渐变颜色没有写入顶点BUFFER
	DWORD lockFlag = IsDynamicUSAGE() ? D3DLOCK_DISCARD : 0;

	/*
	 * 2012.5.23 wangshuai
	 * 材质动画目前不支持同时存在顶点色 + UV动画 + 材质透明变化
	 * 支持以下2种模式
	 * 1. 顶点色 + UV动画, 并设置材质Alpha值
	 * 2. UV动画 + 材质透明度变化(此时不支持刷顶点色透明)
	 */
	if (bMtrlHasAlphaChange)
	{
		if (dwColor != m_dwOldColor)
		{
			m_dwOldColor = dwColor;
			_WriteDiffuseBuffer(dwColor, lockFlag);
		}
	}
	else
	{
		// 如果材质没有透明度变化, 只需将材质的Alpha作为顶点颜色的Alpha值
		if (m_ChunkData->IsEffect())
		{
			if (dwColor != m_dwOldColor)
			{
				m_dwOldColor = dwColor;
				_WriteDiffuseBuffer(dwColor, lockFlag);
			}
		}
		else
		{
			BYTE mtrlAlpha = dwColor >> 24;
			if (mtrlAlpha != m_oldAlpha)
			{
				m_oldAlpha = mtrlAlpha;
				_ChangeVertexColorAlpha(mtrlAlpha, lockFlag);
			}
		}
	}

	bool changeUV = false;
	Vector2* uvs = GetUVs();
	if( fu != m_fOldU || fv != m_fOldV )
	{
		for( int i = 0; i < GetVertexCount(); i++ )
		{
			GetWorldUvs()[i].x = uvs[i].x+fu;
			GetWorldUvs()[i].y = uvs[i].y+fv;
		}
		m_fOldU = fu;
		m_fOldV = fv;
		changeUV = true;
	}

	if( m_nTileFrameId != nTileFrameId || m_nUTiles != nUTiles || m_nVTiles != nVTiles )
	{
		int row = nTileFrameId/nUTiles;
		int col = nTileFrameId%nUTiles;

		float du = 1.0f/nUTiles;
		float dv = 1.0f/nVTiles;
		if( nUTiles > 1 || nVTiles > 1 )
		{
			//assert( GetVertexCount()%4 == 0 && "geom use mtl tiling, but vertex count %4 != 0" );
			int nBoardCount = GetVertexCount()/4;
			for( int i = 0; i < nBoardCount; i++ )
			{
				GetWorldUvs()[4*i+0].x = du*col;
				GetWorldUvs()[4*i+0].y = dv*row+dv;

				GetWorldUvs()[4*i+1].x = du*col;
				GetWorldUvs()[4*i+1].y = dv*row;

				GetWorldUvs()[4*i+2].x = du*col+du;
				GetWorldUvs()[4*i+2].y = dv*row+dv;

				GetWorldUvs()[4*i+3].x = du*col+du;
				GetWorldUvs()[4*i+3].y = dv*row;

			}

			changeUV = true;
		}
		m_nTileFrameId = nTileFrameId;
		m_nUTiles = nUTiles;
		m_nVTiles = nVTiles;
	}

	if (changeUV)
	{
		_WriteUVBuffer(lockFlag);
	}

	// 统计
	if( pVertexCount )
		*pVertexCount = GetVertexCount();
	if( pFaceCount )
		*pFaceCount = GetFaceCount();

	// added, jiayi, [2010/6/10]
	// 补充填充renderparam
	params->dwFlag = dwFlag;
	params->stUseTexId = stUseTexId;
	params->stUseShimmerGrayTexId = stUserShimmerGrayTexId;
	params->stUseLuminanceTexId = stUseLuminanceTexId;
	params->m_bNoSort = IsNoSortChunk();
	// 填充diffuse,ambient [11/11/2010 zhangjiayi]
	params->m_kAmbient = ((RendererDx*)GetEngine()->GetRenderer())->GetLightAmbient(LIGHT_INDEX_TERRAIN);
	params->m_kDiffuse = ((RendererDx*)GetEngine()->GetRenderer())->GetLightDiffuse(LIGHT_INDEX_TERRAIN);
	params->m_bDiffAmbChanged = true;
	_Render( params );
	return true;

// 	{
// 
// 
// 		// 可合并模型添加到合并列表里，QL，2009/05/07
// 		if( bCanCombine && pMapCombineSubmodel && stUseTexId != -1)
// 		{
// 			if( pMapCombineSubmodel->empty() )
// 			{
// 				std::vector<CombineModelData> vctCombineModel;
// 				vctCombineModel.clear();
// 
// 				CombineModelData kData;
// 				kData.pSubmodel = this;
// 				kData.dwFlag = dwFlag;
// 				kData.fu = fu;
// 				kData.fv = fv;
// 				kData.stUseLuminanceTexId = stUseLuminanceTexId;
// 				kData.dwColor = dwColor;
// 				kData.nTileFrameId = nTileFrameId;
// 				kData.nUTiles = nUTiles;
// 				kData.nVTiles = nVTiles;
// 				kData.nSpecularTexID = params->nSpecularTexID;
// 				kData.material = params->material;
// 				kData.pMatrix = pMatrices;
// 				kData.pMex = pMex;
// 				vctCombineModel.push_back(kData);
// 				pMapCombineSubmodel->insert( std::map<int, std::vector<CombineModelData>>::value_type( stUseTexId, vctCombineModel ) );
// 			}
// 			else
// 			{
// 				std::map<int, std::vector<CombineModelData>>::iterator iter = pMapCombineSubmodel->find(stUseTexId);
// 				if( iter != pMapCombineSubmodel->end() )
// 				{
// 					CombineModelData kData;
// 					kData.pSubmodel = this;
// 					kData.dwFlag = dwFlag;
// 					kData.fu = fu;
// 					kData.fv = fv;
// 					kData.stUseLuminanceTexId = stUseLuminanceTexId;
// 					kData.dwColor = dwColor;
// 					kData.nTileFrameId = nTileFrameId;
// 					kData.nUTiles = nUTiles;
// 					kData.nVTiles = nVTiles;
// 					kData.nSpecularTexID = params->nSpecularTexID;
// 					kData.material = params->material;
// 					kData.pMatrix = pMatrices;
// 					kData.pMex = pMex;
// 					iter->second.push_back(kData);
// 				}
// 				else
// 				{
// 					std::vector<CombineModelData> vctCombineModel;
// 					vctCombineModel.clear();
// 
// 					CombineModelData kData;
// 					kData.pSubmodel = this;
// 					kData.dwFlag = dwFlag;
// 					kData.fu = fu;
// 					kData.fv = fv;
// 					kData.stUseLuminanceTexId = stUseLuminanceTexId;
// 					kData.dwColor = dwColor;
// 					kData.nTileFrameId = nTileFrameId;
// 					kData.nUTiles = nUTiles;
// 					kData.nVTiles = nVTiles;
// 					kData.nSpecularTexID = params->nSpecularTexID;
// 					kData.material = params->material;
// 					kData.pMatrix = pMatrices;
// 					kData.pMex = pMex;
// 					vctCombineModel.push_back(kData);
// 					pMapCombineSubmodel->insert( std::map<int, std::vector<CombineModelData>>::value_type( stUseTexId, vctCombineModel ) );
// 				}
// 			}
// 			return false;
// 		}
// 
// 
// 		if( dwColor != m_dwOldColor )
// 		{
// 			DWORD* diffuse = GetDiffuseLocked();
// 			for( int i = 0; i < GetVertexCount(); i++ )
// 			{
// 				if( diffuse )
// 					GetWorldDiffuses()[i] = diffuse[i];
// 				else
// 					GetWorldDiffuses()[i] = dwColor;
// 				//GetWorldDiffuses()[i] = 0x3fff0000;
// 			}
// 			UnlockDiffuse();
// 			m_dwOldColor = dwColor;
// 		}
// 
// 		Vector2* uvs = m_ChunkData->m_pUVs[0];
// 		if( fu != m_fOldU || fv != m_fOldV )
// 		{
// 			for( int i = 0; i < GetVertexCount(); i++ )
// 			{
// 				GetWorldUvs()[i].x = uvs[i].x+fu;
// 				GetWorldUvs()[i].y = uvs[i].y+fv;
// 			}
// 			m_fOldU = fu;
// 			m_fOldV = fv;
// 		}
// 
// 		if( m_nTileFrameId != nTileFrameId || m_nUTiles != nUTiles || m_nVTiles != nVTiles )
// 		{
// 			int row = nTileFrameId/nUTiles;
// 			int col = nTileFrameId%nUTiles;
// 
// 			float du = 1.0f/nUTiles;
// 			float dv = 1.0f/nVTiles;
// 			if( nUTiles > 1 || nVTiles > 1 )
// 			{
// 				//assert( GetVertexCount()%4 == 0 && "geom use mtl tiling, but vertex count %4 != 0" );
// 				int nBoardCount = GetVertexCount()/4;
// 				for( int i = 0; i < nBoardCount; i++ )
// 				{
// 					GetWorldUvs()[4*i+0].x = du*col;
// 					GetWorldUvs()[4*i+0].y = dv*row+dv;
// 
// 					GetWorldUvs()[4*i+1].x = du*col;
// 					GetWorldUvs()[4*i+1].y = dv*row;
// 
// 					GetWorldUvs()[4*i+2].x = du*col+du;
// 					GetWorldUvs()[4*i+2].y = dv*row+dv;
// 
// 					GetWorldUvs()[4*i+3].x = du*col+du;
// 					GetWorldUvs()[4*i+3].y = dv*row;
// 
// 				}
// 			}
// 			m_nTileFrameId = nTileFrameId;
// 			m_nUTiles = nUTiles;
// 			m_nVTiles = nVTiles;
// 		}
// 
// 		//if( m_pBlendedVertexBuffer || 
// 		//	m_pBlendedNormalBuffer ||
// 		//	m_pBlendedDiffuseBuffer)
// 		//{
// 		//	pRenderer->SetVertices( m_pBlendedVertexBuffer );
// 		//	pRenderer->SetNormals( m_pBlendedNormalBuffer );
// 		//	pRenderer->SetDiffuse( m_pBlendedDiffuseBuffer );
// 		//	//dwFlag |= eLightingDisable;
// 		//}
// 		//else
// 		{
// 			if( IsBillboard() )
// 				pRenderer->SetVertices( billboard_vertices );
// 			else
// 				pRenderer->SetVertices( GetWorldVertices() );
// 			pRenderer->SetNormals( GetWorldNormals() );
// 			pRenderer->SetDiffuse( GetWorldDiffuses() );
// 			pRenderer->SetUVs( GetWorldUvs(), 0 );
// 			pRenderer->SetUVs( GetWorldUvs(), 1 );
// 			pRenderer->SetIndices( m_ChunkData->m_pFaces );
// 
// 
// 		}
// 
// 		pRenderer->SetTextureId( stUseTexId, 0 );
// 		if( IsFloor() || IsCollision() ||IsSupperFloor())
// 			pRenderer->SetShaderId( HELP_COLI_FLOOR );
// 		else
// 			pRenderer->SetShaderId( MEX2_SHADER );
// 
// 		// add [5/26/2008 whu]
// 		pRenderer->SetTextureId( stUseLuminanceTexId, 2 );
// 
// 		//if( m_pIB )
// 		//{
// 		//	pRenderer->SetIB( m_pIB );
// 		//}
// 
// 
// 		//DWORD dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1;
// 		//pRenderer->SetFVF( dwFvf );
// 
// 		pRenderer->Push( GetVertexCount(), GetFaceCount(), dwFlag );
// 		//pRenderer->SetRenderState( D3DRS_COLORVERTEX, FALSE );
// 	}
// 
// 	//LeaveCriticalSection( &gs_BufferCS );
// 
// 	// 渲染辅助模型状态下，渲染结束恢复灯光，确保只在编辑器里会渲染辅助模型
// 	if( GetMe3dConfig()->m_RenderHelper )
// 	{
// 		if( IsFloor() || IsCollision() ||IsSupperFloor())
// 		{
// 			pRenderer->Flush(0);
// 		}
// 	}
// 	return true;
	unguard;
}

void CBillboardGeoChunk::UpdateBillboard( Vector* pVertices , float* pMatrices)
{
	SetBillboardLocaled(false);

	if( GetProperty().dwFlag & Mex2BbrdFlag_AlwayseStand )
	{
		int nBillboardCount = GetVertexCount()/4;
		for( int i = 0; i < nBillboardCount; i++ )
		{
			Vector c = GetWorldVertices()[i*4];
			c += GetWorldVertices()[i*4+1];
			c += GetWorldVertices()[i*4+2];
			c += GetWorldVertices()[i*4+3];
			c /= 4;

			Vector l = c-GetWorldVertices()[i*4];


			float fSize = l.length();//*HR3D_Config::m_fMdlSpaceScale;

			Vector up( 0, fSize, 0 );
			Vector right( fSize, 0, 0 );
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&up, (D3DXVECTOR3*)&up, (D3DXMATRIX*)&GetMe3dConfig()->GetCamera()->GetBillboardMatrix() );
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&right, (D3DXVECTOR3*)&right, (D3DXMATRIX*)&GetMe3dConfig()->GetCamera()->GetBillboardMatrix() );

			pVertices[4*i+0] = c-up-right;
			pVertices[4*i+1] = c-up+right;
			pVertices[4*i+2] = c+up+right;
			pVertices[4*i+3] = c+up-right;
		}
	}
	else if( GetProperty().dwFlag & Mex2BbrdFlag_AlwayseStand_ForEffect )
	{
		int nBillboardCount = GetVertexCount()/4;
		for( int i = 0; i < nBillboardCount; i++ )
		{
			Vector c = GetWorldVertices()[i*4];
			c += GetWorldVertices()[i*4+1];
			c += GetWorldVertices()[i*4+2];
			c += GetWorldVertices()[i*4+3];
			c /= 4;

			Vector l = c-GetWorldVertices()[i*4];


			float fSize = l.length();//*HR3D_Config::m_fMdlSpaceScale;

			Vector up( 0, fSize, 0 );
			Vector right( fSize, 0, 0 );
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&up, (D3DXVECTOR3*)&up, (D3DXMATRIX*)&GetMe3dConfig()->GetCamera()->GetBillboardMatrix() );
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&right, (D3DXVECTOR3*)&right, (D3DXMATRIX*)&GetMe3dConfig()->GetCamera()->GetBillboardMatrix() );

			pVertices[4*i+0] = c+up-right;
			pVertices[4*i+1] = c-up-right;
			pVertices[4*i+2] = c+up+right;
			pVertices[4*i+3] = c-up+right;
		}
	}
	else if( GetProperty().dwFlag & Mex2BbrdFlag_VerticalGround )
	{
		// 得到与摄像机方向相反的方向
		D3DXVECTOR3 vAntiCamera = -GetMe3dConfig()->GetCamera()->GetViewDir();

		int nBillboardCount = GetVertexCount()/4;
		Vector bbverts[4];
		for( int i = 0; i < nBillboardCount; i++ )
		{
			Vector up(0,0,1);
			bbverts[0] = GetWorldVertices()[i*4];
			bbverts[1] = GetWorldVertices()[i*4+1];
			bbverts[2] = GetWorldVertices()[i*4+2];
			bbverts[3] = GetWorldVertices()[i*4+3];

			Vector c = (bbverts[0]+bbverts[1]+bbverts[2]+bbverts[3])/4;

			Vector e0 = bbverts[1]-bbverts[0];
			Vector e1 = bbverts[2]-bbverts[0];

			Vector normal;
			// 得到billboard的法线
			D3DXVec3Cross( (D3DXVECTOR3*)&normal, (D3DXVECTOR3*)&e1, (D3DXVECTOR3*)&e0 );
			D3DXVec3Normalize( (D3DXVECTOR3*)&normal, (D3DXVECTOR3*)&normal );


			Vector right;
			D3DXVec3Cross( (D3DXVECTOR3*)&right, (D3DXVECTOR3*)&up, (D3DXVECTOR3*)&vAntiCamera );
			D3DXVec3Normalize( (D3DXVECTOR3*)&right, (D3DXVECTOR3*)&right );
			right *= e1.length()/2;
			up *= e0.length()/2;
			// 计算从billboard的法线变换到摄像机反向法线的变换
			//BuildMatrixFromVectorToVector( (float*)&normal, (float*)&vAntiCamera, (float*)&m );
			//BuildMatrixFromVectorToVector( (float*)&vAntiCamera, (float*)&normal, (float*)&m );

			//bbverts[0] = bbverts[0]-c;
			//bbverts[1] = bbverts[1]-c;
			//bbverts[2] = bbverts[2]-c;
			//bbverts[3] = bbverts[3]-c;

			//D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[0], (D3DXVECTOR3*)&bbverts[0], (D3DXMATRIX*)&m );
			//D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[1], (D3DXVECTOR3*)&bbverts[1], (D3DXMATRIX*)&m );
			//D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[2], (D3DXVECTOR3*)&bbverts[2], (D3DXMATRIX*)&m );
			//D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[3], (D3DXVECTOR3*)&bbverts[3], (D3DXMATRIX*)&m );

			pVertices[4*i+0] = c+up-right;
			pVertices[4*i+1] = c-up-right;
			pVertices[4*i+2] = c+up+right;
			pVertices[4*i+3] = c-up+right;
		}

	}
	else if( (GetProperty().dwFlag & Mex2BbrdFlag_OriginalPointCircling) && (pMatrices != NULL))
	{
		// 得到与摄像机方向相反的方向
		D3DXVECTOR3 vAntiCamera = -GetMe3dConfig()->GetCamera()->GetViewDir();
		int nBillboardCount = GetVertexCount()/4;
		Vector  bbverts[4];
		for( int i = 0; i < nBillboardCount; i++ )
		{
			bbverts[0] = GetWorldVertices()[i*4];
			bbverts[1] = GetWorldVertices()[i*4+1];
			bbverts[2] = GetWorldVertices()[i*4+2];
			bbverts[3] = GetWorldVertices()[i*4+3];

			Vector c = (bbverts[0]+bbverts[1]+bbverts[2]+bbverts[3])/4;

			Vector e0 = bbverts[1]-bbverts[0];
			Vector e1 = bbverts[2]-bbverts[0];
			Vector normal;
			// 得到billboard的法线
			D3DXVec3Cross( (D3DXVECTOR3*)&normal, (D3DXVECTOR3*)&e0, (D3DXVECTOR3*)&e1 );
			D3DXVec3Normalize( (D3DXVECTOR3*)&normal, (D3DXVECTOR3*)&normal );
			MeMatrix m;
			// 计算从billboard的法线变换到摄像机反向法线的变换
			//BuildMatrixFromVectorToVector( (float*)&normal, (float*)&vAntiCamera, (float*)&m );
			BuildMatrixFromVectorToVector( (float*)&vAntiCamera, (float*)&normal, (float*)&m );

			bbverts[0] = bbverts[0]-c;
			bbverts[1] = bbverts[1]-c;
			bbverts[2] = bbverts[2]-c;
			bbverts[3] = bbverts[3]-c;

			D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[0], (D3DXVECTOR3*)&bbverts[0], (D3DXMATRIX*)&m );
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[1], (D3DXVECTOR3*)&bbverts[1], (D3DXMATRIX*)&m );
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[2], (D3DXVECTOR3*)&bbverts[2], (D3DXMATRIX*)&m );
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[3], (D3DXVECTOR3*)&bbverts[3], (D3DXMATRIX*)&m );


			Vector NowOriginalPoint;
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&NowOriginalPoint, &D3DXVECTOR3(0,0,0), (D3DXMATRIX*)pMatrices );

			D3DXVECTOR3 viewDir;
			D3DXVec3Normalize( &viewDir, &(GetMe3dConfig()->GetCamera()->GetEyePt() - (*(D3DXVECTOR3*)&NowOriginalPoint)) );
			Vector NowC = c.length()* (*(Vector*)&viewDir);

			pVertices[4*i+0] = NowOriginalPoint+ NowC+bbverts[0];
			pVertices[4*i+1] = NowOriginalPoint+NowC+bbverts[1];
			pVertices[4*i+2] = NowOriginalPoint+NowC+bbverts[2];
			pVertices[4*i+3] = NowOriginalPoint+NowC+bbverts[3];
		}
	}
    // added by zhuomeng.hu		[1/28/2011]
    else if( GetProperty().dwFlag & Mex2BbrdFlag_SmoothRotating )
    {
        // 得到与摄像机方向相反的方向
        D3DXVECTOR3 vAntiCamera = -GetMe3dConfig()->GetCamera()->GetViewDir();
        int nBillboardCount = GetVertexCount() / 4;
        Vector  bbverts[4];
        for( int i = 0; i < nBillboardCount; i++ )
        {
            // 第一次旋转
            bbverts[0] = GetWorldVertices()[i*4];
            bbverts[1] = GetWorldVertices()[i*4+1];
            bbverts[2] = GetWorldVertices()[i*4+2];
            bbverts[3] = GetWorldVertices()[i*4+3];

            Vector c = ( bbverts[0] + bbverts[1] + bbverts[2] + bbverts[3] ) / 4;
            D3DXMATRIX* pM = (D3DXMATRIX*)&GetMe3dConfig()->GetCamera()->GetBillboardMatrix();

            bbverts[0] = bbverts[0] - c;
			bbverts[1] = bbverts[1] - c;
            bbverts[2] = bbverts[2] - c;
            bbverts[3] = bbverts[3] - c;

			D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[0], (D3DXVECTOR3*)&bbverts[0], pM );
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[1], (D3DXVECTOR3*)&bbverts[1], pM );
            D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[2], (D3DXVECTOR3*)&bbverts[2], pM );
            D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[3], (D3DXVECTOR3*)&bbverts[3], pM );

			pVertices[4*i+0] = c + bbverts[0];
			pVertices[4*i+1] = c + bbverts[1];
			pVertices[4*i+2] = c + bbverts[2];
			pVertices[4*i+3] = c + bbverts[3];

            // 第二次旋转
            Vector e0 = pVertices[4*i+0] - c;
            Vector e1 = pVertices[4*i+1] - c;
            Vector normal;
            D3DXVec3Cross( (D3DXVECTOR3*)&normal, (D3DXVECTOR3*)&e0, (D3DXVECTOR3*)&e1 );
            D3DXVec3Normalize( (D3DXVECTOR3*)&normal, (D3DXVECTOR3*)&normal );
            MeMatrix m;
            BuildMatrixFromVectorToVector( (float*)&vAntiCamera, (float*)&normal, (float*)&m );

            bbverts[0] = pVertices[4*i+0] - c;
            bbverts[1] = pVertices[4*i+1] - c;
            bbverts[2] = pVertices[4*i+2] - c;
            bbverts[3] = pVertices[4*i+3] - c;

            D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[0], (D3DXVECTOR3*)&bbverts[0], (D3DXMATRIX*)&m );
            D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[1], (D3DXVECTOR3*)&bbverts[1], (D3DXMATRIX*)&m );
            D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[2], (D3DXVECTOR3*)&bbverts[2], (D3DXMATRIX*)&m );
            D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[3], (D3DXVECTOR3*)&bbverts[3], (D3DXMATRIX*)&m );

            pVertices[4*i+0] = c + bbverts[0];
            pVertices[4*i+1] = c + bbverts[1];
            pVertices[4*i+2] = c + bbverts[2];
            pVertices[4*i+3] = c + bbverts[3];
        }
    }
	else
	{
		// 得到与摄像机方向相反的方向
		D3DXVECTOR3 vAntiCamera = -GetMe3dConfig()->GetCamera()->GetViewDir();
		int nBillboardCount = GetVertexCount()/4;
		Vector  bbverts[4];
		for( int i = 0; i < nBillboardCount; i++ )
		{
			bbverts[0] = GetWorldVertices()[i*4];
			bbverts[1] = GetWorldVertices()[i*4+1];
			bbverts[2] = GetWorldVertices()[i*4+2];
			bbverts[3] = GetWorldVertices()[i*4+3];

			Vector c = (bbverts[0]+bbverts[1]+bbverts[2]+bbverts[3])/4;

			Vector e0 = bbverts[1]-bbverts[0];
			Vector e1 = bbverts[2]-bbverts[0];
			Vector normal;
			// 得到billboard的法线
			D3DXVec3Cross( (D3DXVECTOR3*)&normal, (D3DXVECTOR3*)&e0, (D3DXVECTOR3*)&e1 );
			D3DXVec3Normalize( (D3DXVECTOR3*)&normal, (D3DXVECTOR3*)&normal );
			MeMatrix m;
			// 计算从billboard的法线变换到摄像机反向法线的变换
			//BuildMatrixFromVectorToVector( (float*)&normal, (float*)&vAntiCamera, (float*)&m );
			BuildMatrixFromVectorToVector( (float*)&vAntiCamera, (float*)&normal, (float*)&m );

			bbverts[0] = bbverts[0]-c;
			bbverts[1] = bbverts[1]-c;
			bbverts[2] = bbverts[2]-c;
			bbverts[3] = bbverts[3]-c;

			D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[0], (D3DXVECTOR3*)&bbverts[0], (D3DXMATRIX*)&m );
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[1], (D3DXVECTOR3*)&bbverts[1], (D3DXMATRIX*)&m );
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[2], (D3DXVECTOR3*)&bbverts[2], (D3DXMATRIX*)&m );
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&bbverts[3], (D3DXVECTOR3*)&bbverts[3], (D3DXMATRIX*)&m );

			pVertices[4*i+0] = c+bbverts[0];
			pVertices[4*i+1] = c+bbverts[1];
			pVertices[4*i+2] = c+bbverts[2];
			pVertices[4*i+3] = c+bbverts[3];
		}
	}

    // 公告板增加向前偏移       added by zhuomeng.hu		[1/27/2011]
    if( GetProperty().dwFlag &  Mex2BbrdFlag_FrontOffset )
    {
        int nBillboardCount = GetVertexCount() / 4;
        for( int i = 0; i < nBillboardCount; ++i )
        {
            Vector e0 = pVertices[4*i+1] - pVertices[4*i+0];
            Vector e1 = pVertices[4*i+2] - pVertices[4*i+0];
            Vector offset;
            // 得到billboard的法线方向
            D3DXVec3Cross( (D3DXVECTOR3*)&offset, (D3DXVECTOR3*)&e0, (D3DXVECTOR3*)&e1 );
            D3DXVec3Normalize( (D3DXVECTOR3*)&offset, (D3DXVECTOR3*)&offset );

            offset *= m_fFrontOffset;

            pVertices[4*i+0] += offset;
            pVertices[4*i+1] += offset;
            pVertices[4*i+2] += offset;
            pVertices[4*i+3] += offset;
        }
    }

	UpdateBillboardBox();

}

void CBillboardGeoChunk::UpdateBillboard( float* pMatrices)
{

	if( !billboard_vertices )
		billboard_vertices = MeNew Vector[GetVertexCount()];

	UpdateBillboard(billboard_vertices,pMatrices);
}

void CBillboardGeoChunk::UpdateBillboardBox()
{
	Vector* vertices= GetWorldVertices();
	if (vertices)
	{
		for( int j = 0; j < GetVertexCount(); j++ )
		{
			Vector& v = (vertices[j]);

			if( v.x < m_vMin.x )
				m_vMin.x = v.x;
			if( v.y < m_vMin.y )
				m_vMin.y = v.y;
			if( v.z < m_vMin.z )
				m_vMin.z = v.z;

			if( v.x > m_vMax.x )
				m_vMax.x = v.x;
			if( v.y > m_vMax.y )
				m_vMax.y = v.y;
			if( v.z > m_vMax.z )
				m_vMax.z = v.z;
		}
	}
}


// void Mex2GeoChunk::FastRender( IMex* pMex,
// 							  float* pMatrices,
// 							  IRenderer* pRenderer,
// 							  IReplaceableTextureProj* pReplaceableTextureProj,
// 							  float fAlpha, bool bMustUseAlphaBlend,int nFrameId,
// 							  DWORD dwFlagEx /* = 0  */)
// {
// 	guardfunc;
// 	if( GetVertexCount() == 0 || GetFaceCount() == 0 )
// 		return;
// 
// 	// 地板辅助模型，不渲染
// 	BOOL bUseNullMtl = FALSE;
// 	if( GetProperty().nType == Mex2GeoChunkProperty::eFloor ||
// 		GetProperty().nType == Mex2GeoChunkProperty::eSupperFloor ||
// 		GetProperty().nType == Mex2GeoChunkProperty::eCollision )
// 	{
// 		if( GetMe3dConfig()->m_RenderHelper == Config::None_Helper)
// 			return;
// 
// 		bUseNullMtl = TRUE;
// 	}
// 
// 	if( pMex == NULL )
// 		pMex = m_pSrcMex;       
// 
// 	// 如果是仅受一根骨骼影响,而且此骨骼当前不可见
// 	if( m_bSingleBoneInfl && m_nSingleBoneId != -1 && !m_pSrcMex->IsBoneVisible( nFrameId, m_nSingleBoneId ) )
// 	{
// 		return;
// 	}
// 
// 	DWORD dwFlag = dwFlagEx;
// 	short stUseTexId = -1,
// 		stUseTexId2 = -1;
// 
// 	BOOL bTiling = FALSE;
// 	BOOL bAlphaTest = FALSE;
// 	BOOL bAlphaBlend = FALSE;
// 	DWORD dwColor = 0xffffffff;
// 	DWORD dwBlendMode = MEX2_MODULATE2X;
// 	//dwBlendMode = MEX2_MODULATE;
// 
// 	int nTileFrameId = 0;
// 	int nUTiles = 1, nVTiles = 1;
// 	float fu = 0.0f, fv = 0.0f;
// 
// 	BOOL bHasMtlAnim = FALSE;
// 	Mex2Material* pMtl = NULL;
// 
// 	// 如果有材质
// 	if(	m_pSrcMex->GetMtls() &&	m_pSrcMex->GetMtls()->GetMtlCount() >= 0 )
// 	{
// 		if( GetMtlId() != -1  )
// 			pMtl = (Mex2Material*)m_pSrcMex->GetMtls()->GetMtl( GetMtlId() );
// 
// 		if( !pMtl )
// 		{
// 
// 		}
// 		else
// 		{
// 			assert( pMtl->GetLayerCount() > 0 && "mex geomchunk render error, mtl layer count must > 0" );
// 			if( pMtl->GetLayer(0)->GetFlag() & MEX2_TWOSIDED )
// 				dwFlag |= eTwoSided;
// 
// 			assert( GetMtlId() != -1 && "mex chunk render 3 failed, mtl id = -1" );
// 
// 			int nLocalTextureId = pMtl->GetLayer(0)->GetTextureID();
// 			if( pReplaceableTextureProj )
// 			{
// 				stUseTexId = pReplaceableTextureProj->GetRenderTextureID( nLocalTextureId );
// 			}
// 
// 			IMexLayer* pLayer0 = pMtl->GetLayer(0);
// 			DWORD dwLayerFlag = pLayer0->GetFlag();
// 
// 			if( bMustUseAlphaBlend )
// 			{
// 				bAlphaBlend = TRUE;
// 				bAlphaTest = FALSE;
// 				dwFlag &= (~eTwoSided);
// 				dwFlag |= eZWriteDisable;
// 			}
// 			else
// 			{
// 				if( dwLayerFlag & MEX2_ALPHABLEND )
// 				{
// 					bAlphaBlend = TRUE;
// 					if( !( dwLayerFlag & MEX2_ZWRITEENABLE )  )
// 						dwFlag |= eZWriteDisable;
// 				}
// 
// 				if( dwLayerFlag & MEX2_ALPHATEST )
// 				{
// 					bAlphaTest = TRUE;
// 				}
// 			}
// 
// 			if( dwLayerFlag & MEX2_SPECULARENABLE )
// 			{
// 				dwFlag |= eSpecularEnable;
// 				//pRenderer->SetMtlSpecular( pKey->shinstr, 1.0f, pKey->sr, pKey->sg, pKey->sb );
// 				pRenderer->EnableSpecular( TRUE );
// 			}
// 
// 			if( !bAlphaTest && bAlphaBlend /*&& pMtl->HasColorKey()*/ )
// 			{
// 				bHasMtlAnim = TRUE;
// 
// 				//if( !bAlphaTest )
// 				dwFlag |= eLightingDisable;
// 
// 				Mex2MtlAnim* pAnim = pMtl->GetColorTracks().vectorColorTrack[0];
// 				if (nFrameId >= 0 && nFrameId < pAnim->nKeyCount)
// 				{
// 					Mex2ColorKey* pKey = &pAnim->pKeys[nFrameId];
// 
// 					// 需要根据动画帧数来计算出当前自己的帧编号
// 					nTileFrameId = int((nFrameId*ONEFRAMEINTERVAL+pAnim->nStartFrame)/pAnim->fPlaybackRate);
// 					nTileFrameId %= pAnim->nUTile*pAnim->nVTile;
// 
// 					dwBlendMode = pKey->dwBlendMode;
// 
// 					if( pKey->selfillum == 1.0f )
// 						dwFlag |= eDstBlendOne;
// 
// 					DWORD a = (DWORD)(pKey->alpha*255);
// 					DWORD r = (DWORD)(pKey->dr*255);
// 					DWORD g = (DWORD)(pKey->dg*255);
// 					DWORD b = (DWORD)(pKey->db*255);
// 					dwColor = a<<24|r<<16|g<<8|b;
// 
// 					bTiling = pAnim->bTiling;
// 
// 					nUTiles = pAnim->nUTile;
// 					nVTiles = pAnim->nVTile;
// 
// 					fu = pKey->uoffset;
// 					fv = pKey->voffset;
// 				}
// 			}
// 		}
// 	}
// 
// 	if( IsExistDiffuse() )
// 	{
// 		//有顶点色 不需要Modulate2
// 		dwFlag |= eLightingDisable;
// 		dwBlendMode = MEX2_MODULATE;
// 	}
// 
// 
// 	switch( dwBlendMode )
// 	{
// 	case MEX2_MODULATE:
// 		dwFlag |= eOpModulate1X;
// 		break;
// 	case MEX2_MODULATE2X:
// 		dwFlag |= eOpModulate2X;
// 		break;
// 	case MEX2_ADD:
// 		dwFlag |= eOpAdd;
// 		break;
// 	default:
// 		dwFlag |= eOpModulate1X;
// 		break;
// 	}
// 
// 	if( GetVertexCount() >= MAX_VERTEX_PER_CHUNK )
// 	{
// 		assert( false );
// 		return;
// 	}
// 
// 	// 物体上的特效不受影响
// 	BOOL bEffect = FALSE;
// 	if (IsBillboard())
// 	{
// 		bEffect = TRUE;
// 	}
// 	//DWORD dwFVF = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1;
// 
// 	dwFlag |= eMipmapLinear;
// 
// 	if( bAlphaTest )
// 	{
// 		bAlphaBlend = FALSE;
// 		dwFlag |= eAlphaTest;
// 	}
// 
// 	if( bAlphaBlend )
// 	{
// 		dwFlag |= eAlphaBlend;
// 		dwFlag |= eSortByFarZ;
// 		dwFlag &= (~eLightingDisable);
// 	}
// 
// 	// 	MexSkinMesh* pSkinMesh = m_pSrcMex->GetSkinMesh();
// 	// 	BOOL bRenderWithVS = FALSE;
// 	// 	if( !bEffect &&	!bHasMtlAnim &&	GetMe3dConfig()->m_bUseSkinMesh && pSkinMesh )
// 	// 	{
// 	// 		bRenderWithVS = TRUE;
// 	// 		if( dwFlagEx & eNotUseSkinMesh )
// 	// 		{
// 	// 			bRenderWithVS = FALSE;
// 	// 		}		
// 	// 	}
// 
// 
// 	// 不要贴图
// 	if( bUseNullMtl )
// 		stUseTexId = -1;
// 
// 	//if( m_pVB )
// 	//{
// 	//	if( !bAlphaBlend )
// 	//	{
// 	//		pRenderer->DirectPushSurface( 
// 	//			stUseTexId,
// 	//			-1,
// 	//			MEX2_SHADER,
// 	//			D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1,
// 	//			sizeof( SK_VERTEX ),
// 	//			(BYTE*)m_pVB,
// 	//			GetVertexCount(),
// 	//			(BYTE*)m_pIB,
// 	//			GetFaceCount(),
// 	//			dwFlag|eUseVB|eLightingDisable );
// 	//		return;
// 	//	}
// 	//}
// 
// 	// 	if( bRenderWithVS )
// 	// 	{
// 	// 		if( !bAlphaBlend  && !bAlphaTest )
// 	// 		{
// 	// 			//	pRenderer->LightEnable( 0, FALSE );
// 	// 			MexSkinMesh::Subset* pSubset = pSkinMesh->GetSubset( m_nChunkID );
// 	// 			pSubset->nTextureID = stUseTexId;
// 	// 			pSkinMesh->RenderSubset( (LPDIRECT3DDEVICE9)pRenderer->GetRealDevice(), pSubset, pMatrices, dwFlag|eLightingDisable, fAlpha );
// 	// 			return;
// 	// 		}
// 	// 	}
// 
// 	//EnterCriticalSection( &gs_BufferCS );
// 
// 
// 	if( fAlpha < 1 )
// 	{
// 		DWORD a = (dwColor&0xff000000)>>24;
// 		a = (DWORD)(a*fAlpha);
// 		dwColor = a<<24|(dwColor&0x00ffffff);
// 	}
// 
// 	//dwColor = D3DCOLOR_ARGB( 255,255,255,255);
// 
// 
// 	{
// 		BEGINFUNCPERLOG( "VertexBlend" );
// 
// 		int nBaseVertexIndex;
// 		MexVertex* pMexVertex = pRenderer->LockMexVB( GetVertexCount(), nBaseVertexIndex );
// 
// 		if( !pMexVertex )
// 			return;
// 
// 		if( pMatrices != NULL && GetVertexCount() != 0 && GetFaceCount() != 0 && GetVertexCount() < MAX_VERTEX_PER_CHUNK )
// 		{
// 			//BlendVertex( pMexVertex, pMex, (float*)pMatrices );
// 
// 			Vector* pos = m_ChunkData->m_pVertices;
// 			Vector* normal = m_ChunkData->m_pNormals;
// 			Vector2* uvs = m_ChunkData->m_pUVs[0];
// 			Vector p;
// 			long const MAX_BONE_GROUP = 255;
// 			MeMatrix group[MAX_BONE_GROUP];
// 
// 			BlendBoneGroup( MAX_BONE_GROUP, (MeMatrix*)pMatrices, group );
// 
// 			Vector vModelNormalPoint;
// 			for( int nVertexId = 0; nVertexId < GetVertexCount(); nVertexId++, pos++, normal++, pMexVertex++ )
// 			{
// 				Vector* normalpoints = &GetNormalPoints(nVertexId);
// 				float x = 0, y = 0, z = 0;
// 				float nx = 0, ny = 0, nz = 0;
// 				int nBGId = GetBoneGroupIndices()[nVertexId];
// 
// 				if( nBGId == 0xff )
// 				{
// 					pMexVertex->x = pos->x;
// 					pMexVertex->y = pos->y;
// 					pMexVertex->z = pos->z;
// 
// 					pMexVertex->nx = normal->x;
// 					pMexVertex->ny = normal->y;
// 					pMexVertex->nz = normal->z;
// 				}
// 				else 
// 				{
// 					p.x = ( pos->x*group[nBGId].m[0][0] + pos->y*group[nBGId].m[1][0] + pos->z*group[nBGId].m[2][0] + group[nBGId].m[3][0] ) / group[nBGId].m[3][3];
// 					p.y = ( pos->x*group[nBGId].m[0][1] + pos->y*group[nBGId].m[1][1] + pos->z*group[nBGId].m[2][1] + group[nBGId].m[3][1] ) / group[nBGId].m[3][3];
// 					p.z = ( pos->x*group[nBGId].m[0][2] + pos->y*group[nBGId].m[1][2] + pos->z*group[nBGId].m[2][2] + group[nBGId].m[3][2] ) / group[nBGId].m[3][3];
// 
// 					vModelNormalPoint.x = ( normalpoints->x*group[nBGId].m[0][0] + normalpoints->y*group[nBGId].m[1][0] + normalpoints->z*group[nBGId].m[2][0] + group[nBGId].m[3][0] ) / group[nBGId].m[3][3];
// 					vModelNormalPoint.y = ( normalpoints->x*group[nBGId].m[0][1] + normalpoints->y*group[nBGId].m[1][1] + normalpoints->z*group[nBGId].m[2][1] + group[nBGId].m[3][1] ) / group[nBGId].m[3][3];
// 					vModelNormalPoint.z = ( normalpoints->x*group[nBGId].m[0][2] + normalpoints->y*group[nBGId].m[1][2] + normalpoints->z*group[nBGId].m[2][2] + group[nBGId].m[3][2] ) / group[nBGId].m[3][3];
// 
// 					pMexVertex->x = p.x;
// 					pMexVertex->y = p.y;
// 					pMexVertex->z = p.z;
// 
// 					//D3DXVECTOR3 vNormaltemp;
// 
// 					//vNormaltemp.x = (vModelNormalPoint.x - p.x);
// 					//vNormaltemp.y = (vModelNormalPoint.y - p.y);
// 					//vNormaltemp.z = (vModelNormalPoint.z - p.z);
// 
// 					//D3DXVec3Normalize( &vNormaltemp, &vNormaltemp );
// 
// 					//pMexVertex->nx = vNormaltemp.x;
// 					//pMexVertex->ny = vNormaltemp.y;
// 					//pMexVertex->nz = vNormaltemp.z;
// 
// 
// 					pMexVertex->nx = vModelNormalPoint.x - p.x;
// 					pMexVertex->ny = vModelNormalPoint.y - p.y;
// 					pMexVertex->nz = vModelNormalPoint.z - p.z;
// 
// 
// 					//pMexVertex->nx = normal->x;
// 					//pMexVertex->ny = normal->y;
// 					//pMexVertex->nz = normal->z;
// 
// 
// 
// 					//D3DXVECTOR3 vNormal = D3DXVECTOR3( vModelNormalPoint.x - p.x, vModelNormalPoint.y - p.y, vModelNormalPoint.z - p.z );
// 					//D3DXVec3Normalize( &vNormal, &vNormal );
// 
// 					//pMexVertex->nx = vNormal.x;
// 					//pMexVertex->ny = vNormal.y;
// 					//pMexVertex->nz = vNormal.z;
// 				}
// 
// 				pMexVertex->u = uvs[nVertexId].x + fu;
// 				pMexVertex->v = uvs[nVertexId].y + fv;
// 
// 				//if( GetDiffuseLocked() )
// 				//{
// 				//	pMexVertex->diff = *((float*)(&GetDiffuseLocked()[nVertexId]));
// 				//}
// 				//else
// 				//{
// 				//	pMexVertex->diff = *((float*)(&dwColor));
// 				//}
// 			}			
// 		}
// 
// 
// 		pRenderer->UnlockMexVB();
// 
// 		ENDFUNCPERLOG( "VertexBlend" );
// 		D3DMATERIAL9 m_Material;
// 		D3DUtil_InitMaterial( m_Material, 1.0f, 1.0f, 1.0f );
// 		m_Material.Diffuse.a = fAlpha;
// 
// 		pRenderer->FastRenderMex( stUseTexId, 0, GetVertexCount(), (BYTE*)GetIB(), GetFaceCount(), 0, &m_Material, nBaseVertexIndex );
// 	}
// 
// 	//LeaveCriticalSection( &gs_BufferCS );
// 	unguard;	
// }

void Mex2GeoChunk::RenderShadow( IMex* pMex, 
								float* pMatrices, 
								IRenderer* pRenderer,
								IReplaceableTextureProj* pReplaceableTextureProj,
								float fAlpha,
								bool bMustUseAlphaBlend,int nFrameId, DWORD dwFlagEx )
{
	MeScopeProfileMexGeoChunkFun
	guardfunc;
	if( !HaveShadow() )
		return;
	//TRUETIMEFUNC();
	////	//CSALocker locker(this);
	if( GetVertexCount() == 0 ||
		GetFaceCount() == 0 )
		return;
	// 地板辅助模型，不渲染
	BOOL bUseNullMtl = FALSE;
	//if( IsFloor() ||
	//	IsCollision() )
	//{
	//	if( !GetMe3dConfig()->m_bRenderHelper )
	//		return;
	//	bUseNullMtl = TRUE;
	//}

	if( pMex == NULL )
		pMex = m_pSrcMex;       

	// 如果是仅受一根骨骼影响,而且此骨骼当前不可见
	if( m_bSingleBoneInfl &&
		m_nSingleBoneId != -1 &&
		!m_pSrcMex->IsBoneVisible( nFrameId, m_nSingleBoneId ) )
	{
		return;
	}

	DWORD dwFlag = dwFlagEx;
	short stUseTexId = -1;
	BOOL bAlphaBlend = TRUE;
	BOOL bAlphaTest = FALSE;
	DWORD dwColor = 0xffffffff;
	DWORD dwBlendMode = MEX2_MODULATE2X;
	//dwBlendMode = MEX2_MODULATE;
	float fu = 0.0f, fv = 0.0f;
	BOOL bTiling = FALSE;
	int nTileFrameId = 0;
	int nUTiles = 1, nVTiles = 1;

	Mex2Material *pMtl = NULL;
	BOOL bHasMtlAnim = FALSE;
	
	if (GetVertexCount() >= MAX_VERTEX_PER_CHUNK)
	{
		assert( false );
		return;
	}

	// 物体上的特效不受影响
	BOOL bEffect = FALSE;
	
	if ( bAlphaTest || IsBillboard() )
		return;

	// 不要贴图
	if( bUseNullMtl )
		stUseTexId = -1;

	//EnterCriticalSection( &gs_BufferCS );

	{

		if( IsDecal() )
		{
			return;
		}
		//   added 2003.01.15
		// 未注册
		else if( IsBillboard() )
		{
			return;
		}
		short nShaderID = MEX2_SHADER;
		if( IsFloor() || IsCollision() ||IsSupperFloor())
			nShaderID = HELP_COLI_FLOOR;		

		RenderParams* params = CRenderParamsMgr::Instance()->RetriveRenderParams();
		if (!params)
		{
			return;
		}
		params->pMex = pMex;
		params->pMatrices = pMatrices;
// 		params->pRenderer = pRenderer;
		params->pReplaceableTextureProj = pReplaceableTextureProj;
		params->fAlpha = fAlpha;
		params->fGlobalAlpha = 1.f;
		params->nFrameId = nFrameId;
		params->dwFlag = dwFlag;

		RendererDx *pRenderer = (RendererDx *) GetEngine()->GetRenderer();
		MeRenderObject *pkObject = ( MeRenderObject *) m_spRenderObject;
		MeModelRenderObject *pkFinal = dynamic_cast<MeModelRenderObject *> (pkObject);
		if ( pkFinal != NULL )
		{
			if ( MeRenderManager::Instance()->IsFreshObject( this ) )
			{
				pkFinal->SetShaderId( nShaderID );
				pkFinal->SetFVF( pRenderer->GetCurrentSurface()->m_dwFVF );
				pkFinal->SetVertexCount( GetVertexCount() );
				pkFinal->SetVB( GetVerticesBuffer() );
				pkFinal->SetNB( GetNormalsBuffer() );
				pkFinal->SetDB( GetDiffusesBuffer() );
				pkFinal->SetUVB( GetUvsBuffer() );
				pkFinal->SetIB( GetIB() );
				pkFinal->SetFaceCount( GetFaceCount() );
				pkFinal->SetFlag( dwFlag );
				pkObject->GenerateKey();
				MeRenderManager::Instance()->AddObject( this );			
			}			
			PushOtherInfo( params );
		}


	}
	//LeaveCriticalSection( &gs_BufferCS );
	//g_bLock = FALSE;
	unguard;	
}

bool Mex2GeoChunk::BlendVertex( IMex* pMex, float* pMatrices )
{
	if( pMatrices && pMex )
	{
		return BlendVertex( (float*)GetWorldVertices(), (float*)GetWorldNormals(), MAX_VERTEX_PER_CHUNK, pMex, (float*)pMatrices ,NULL);
	}
	return false;
}

void CDecalGeoChunk::SetWorldMatrix( const MeMatrix& kMatrix )
{
	float* fW = (float*)m_WorldMatrix.m;
	float* fM = (float*)kMatrix.m;
	for( int i=0; i<16; i++ )
	{
		fW[i] = fM[i];
	}
}

bool CDecalGeoChunk::IsEqualToWorldMatrix( const MeMatrix& kMatrix )
{
	float* fW = (float*)m_WorldMatrix.m;
	float* fM = (float*)kMatrix.m;
	for( int i=0; i<16; i++ )
	{
		if( fW[i] != fM[i] )
			return false;
	}
	return true;
}

bool CDecalGeoChunk::IsWorldMatrixEqualToZero()
{
	float* fW = (float*)m_WorldMatrix.m;
	for( int i=0; i<16; i++ )
	{
		if( fW[i] != 0.f )
			return false;
	}
	return true;
}


// void Mex2GeoChunk::CombineTo( CombineModelData* pRenderParams, Vector* pDstVertices, Vector* pDstNormals, DWORD* pDstDiffuses, Vector2* pDstUVs, Mex2Face* pDstFaces, int nVertexOffset )
// {
// 	float fu = pRenderParams->fu;
// 	float fv = pRenderParams->fv;
// 	DWORD dwColor = pRenderParams->dwColor;
// 	int nTileFrameId = pRenderParams->nTileFrameId;
// 	int nUTiles = pRenderParams->nUTiles;
// 	int nVTiles = pRenderParams->nVTiles;
// 
// 	if( pRenderParams->pMatrix )
// 	{
// 		BlendVertex( pRenderParams->pMex, (float*)pRenderParams->pMatrix );
// 		if( IsBillboard() )
// 			((CBillboardGeoChunk*)this)->UpdateBillboard(pRenderParams->pMatrix);
// 	}
// 
// 	if( dwColor != m_dwOldColor )
// 	{
// 		DWORD* diffuse = GetDiffuseLocked();
// 		for( int i = 0; i < GetVertexCount(); i++ )
// 		{
// 			if( diffuse )
// 				GetWorldDiffuses()[i] = diffuse[i];
// 			else
// 				GetWorldDiffuses()[i] = dwColor;
// 		}
// 		UnlockDiffuse();
// 		m_dwOldColor = dwColor;
// 	}
// 	Vector2* uvs = m_ChunkData->m_pUVs[0];
// 
// 	if( fu != m_fOldU || fv != m_fOldV )
// 	{
// 		for( int i = 0; i < GetVertexCount(); i++ )
// 		{
// 			GetWorldUvs()[i].x = uvs[i].x+fu;
// 			GetWorldUvs()[i].y = uvs[i].y+fv;
// 		}
// 		m_fOldU = fu;
// 		m_fOldV = fv;
// 	}
// 
// 	if( m_nTileFrameId != nTileFrameId || m_nUTiles != nUTiles || m_nVTiles != nVTiles )
// 	{
// 		int row = nTileFrameId/nUTiles;
// 		int col = nTileFrameId%nUTiles;
// 
// 		float du = 1.0f/nUTiles;
// 		float dv = 1.0f/nVTiles;
// 		if( nUTiles > 1 || nVTiles > 1 )
// 		{
// 			//assert( GetVertexCount()%4 == 0 && "geom use mtl tiling, but vertex count %4 != 0" );
// 			int nBoardCount = GetVertexCount()/4;
// 			for( int i = 0; i < nBoardCount; i++ )
// 			{
// 				GetWorldUvs()[4*i+0].x = du*col;
// 				GetWorldUvs()[4*i+0].y = dv*row+dv;
// 
// 				GetWorldUvs()[4*i+1].x = du*col;
// 				GetWorldUvs()[4*i+1].y = dv*row;
// 
// 				GetWorldUvs()[4*i+2].x = du*col+du;
// 				GetWorldUvs()[4*i+2].y = dv*row+dv;
// 
// 				GetWorldUvs()[4*i+3].x = du*col+du;
// 				GetWorldUvs()[4*i+3].y = dv*row;
// 			}
// 		}
// 		m_nTileFrameId = nTileFrameId;
// 		m_nUTiles = nUTiles;
// 		m_nVTiles = nVTiles;
// 	}
// 
// 	if( IsBillboard() )
// 		memcpy(pDstVertices, ((CBillboardGeoChunk*)this)->GetWorldBillboardVertices(), GetVertexCount()*sizeof(Vector));
// 	else
// 		memcpy(pDstVertices, GetWorldVertices(), GetVertexCount()*sizeof(Vector));
// 	memcpy(pDstNormals, GetWorldNormals(), GetVertexCount()*sizeof(Vector));
// 	memcpy(pDstDiffuses, GetWorldDiffuses(), GetVertexCount()*sizeof(DWORD));
// 	memcpy(pDstUVs, GetWorldUvs(), GetVertexCount()*sizeof(D3DXVECTOR2));
// 
// 	// 合并顶点索引
// 	Mex2Face* indices = GetIndicesLocked();
// 	if( nVertexOffset == 0 )
// 	{
// 		memcpy(pDstFaces, indices, GetFaceCount()*sizeof(Mex2Face));
// 	}
// 	else
// 	{
// 		for( int i = 0; i < GetFaceCount(); i++ )
// 		{
// 			pDstFaces[i].nId[0] = indices[i].nId[0] + nVertexOffset;
// 			pDstFaces[i].nId[1] = indices[i].nId[1] + nVertexOffset;
// 			pDstFaces[i].nId[2] = indices[i].nId[2] + nVertexOffset;
// 		}
// 	}
// 	UnlockIndices();
// }
// 
// void Mex2GeoChunk::CombineTo( CombineModelData* pRenderParams, MexVertex* pVBVertex, short* shIBFace, int nVertexOffset )
// {
// 	float fu = pRenderParams->fu;
// 	float fv = pRenderParams->fv;
// 	DWORD dwColor = pRenderParams->dwColor;
// 	int nTileFrameId = pRenderParams->nTileFrameId;
// 	int nUTiles = pRenderParams->nUTiles;
// 	int nVTiles = pRenderParams->nVTiles;
// 	MexVertex* pVBVertexTemp = pVBVertex;
// 
// 	if( pRenderParams->pMatrix )
// 	{
// 		BlendVertex( pRenderParams->pMex, (float*)pRenderParams->pMatrix );
// 		if( IsBillboard() )
// 			((CBillboardGeoChunk*)this)->UpdateBillboard(pRenderParams->pMatrix);
// 	}
// 
// 	Vector2* uvs = GetUVsLocked(0);
// 	DWORD* diffuse = GetDiffuseLocked();
// 	for( int i = 0; i < GetVertexCount(); i++, pVBVertexTemp++ )
// 	{
// 		if( IsBillboard() )
// 		{
// 			CBillboardGeoChunk* pBillboardChunk = ((CBillboardGeoChunk*)this);
// 			pVBVertexTemp->x = pBillboardChunk->GetWorldBillboardVertices()[i].x;
// 			pVBVertexTemp->y = pBillboardChunk->GetWorldBillboardVertices()[i].y;
// 			pVBVertexTemp->z = pBillboardChunk->GetWorldBillboardVertices()[i].z;
// 		}
// 		else
// 		{
// 			pVBVertexTemp->x = GetWorldVertices()[i].x;
// 			pVBVertexTemp->y = GetWorldVertices()[i].y;
// 			pVBVertexTemp->z = GetWorldVertices()[i].z;
// 		}
// 		pVBVertexTemp->nx = GetWorldNormals()[i].x;
// 		pVBVertexTemp->ny = GetWorldNormals()[i].y;
// 		pVBVertexTemp->nz = GetWorldNormals()[i].z;
// 
// 		if( diffuse )
// 			pVBVertexTemp->diff = diffuse[i];
// 		else
// 			pVBVertexTemp->diff = dwColor;
// 
// 
// 		pVBVertexTemp->u = uvs[i].x+fu;
// 		pVBVertexTemp->v = uvs[i].y+fv;
// 	}
// 	UnlockDiffuse();
// 	UnlockUVs(0);
// 
// 	int row = nTileFrameId/nUTiles;
// 	int col = nTileFrameId%nUTiles;
// 
// 	float du = 1.0f/nUTiles;
// 	float dv = 1.0f/nVTiles;
// 	if( nUTiles > 1 || nVTiles > 1 )
// 	{
// 		//assert( GetVertexCount()%4 == 0 && "geom use mtl tiling, but vertex count %4 != 0" );
// 		int nBoardCount = GetVertexCount()/4;
// 		pVBVertexTemp = pVBVertex;
// 		for( int i = 0; i < nBoardCount; i++ )
// 		{
// 			pVBVertexTemp->u = du*col;
// 			pVBVertexTemp->v = dv*row+dv;
// 			++pVBVertexTemp;
// 
// 			pVBVertexTemp->u = du*col;
// 			pVBVertexTemp->v = dv*row;
// 			++pVBVertexTemp;
// 
// 			pVBVertexTemp->u = du*col+du;
// 			pVBVertexTemp->v = dv*row+dv;
// 			++pVBVertexTemp;
// 
// 			pVBVertexTemp->u = du*col+du;
// 			pVBVertexTemp->v = dv*row;
// 			++pVBVertexTemp;
// 		}
// 	}
// 
// 	Mex2Face* indices = GetIndicesLocked();
// 	// 合并顶点索引
// 	if( nVertexOffset == 0 )
// 	{
// 		memcpy((void*)shIBFace, (void*)indices, GetFaceCount()*3*sizeof(short));
// 	}
// 	else
// 	{
// 		short* shIBFaceTemp = shIBFace;
// 		for( int i = 0; i < GetFaceCount(); i++ )
// 		{
// 			*shIBFaceTemp = indices[i].nId[0] + nVertexOffset;
// 			++shIBFaceTemp;
// 			*shIBFaceTemp = indices[i].nId[1] + nVertexOffset;
// 			++shIBFaceTemp;
// 			*shIBFaceTemp = indices[i].nId[2] + nVertexOffset;
// 			++shIBFaceTemp;
// 		}
// 	}
// 	UnlockIndices();
// }

//extern int GetVertexStride( DWORD dwFvf );
// void Mex2GeoChunk::RenderWithFlag( IRenderer* pRenderer, CombineModelData* pRenderParams, short stUseTexId )
// {
// 	float fu = pRenderParams->fu;
// 	float fv = pRenderParams->fv;
// 	DWORD dwFlag = pRenderParams->dwFlag;
// 	short stUseLuminanceTexId = pRenderParams->stUseLuminanceTexId;
// 	DWORD dwColor = pRenderParams->dwColor;
// 	int nTileFrameId = pRenderParams->nTileFrameId;
// 	int nUTiles = pRenderParams->nUTiles;
// 	int nVTiles = pRenderParams->nVTiles;
// 
// 	{
// 		if( pRenderParams->pMatrix )
// 		{
// 			BlendVertex( pRenderParams->pMex, (float*)pRenderParams->pMatrix );
// 			if( IsBillboard() )
// 				((CBillboardGeoChunk*)this)->UpdateBillboard(pRenderParams->pMatrix);
// 		}
// 
// 		pRenderer->SetGlobalTransparent( 1.f );	// 非半透
// 		pRenderer->SetGlobalDiffuse( 1, 1, 1 );
// 		pRenderer->SetGlobalUOffset( 0, 0.0f );
// 		pRenderer->SetGlobalVOffset( 0, 0.0f );
// 		pRenderer->SetGlobalUOffset( 1, 0.0f );
// 		pRenderer->SetGlobalVOffset( 1, 0.0f );
// 
// 		static DWORD dwFvf = D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1;
// 		pRenderer->SetSurfaceFVF( dwFvf );
// 		pRenderer->SetVertexStride( GetVertexStride( dwFvf ) );
// 
// 		if( dwFlag & eSpecularEnable && pRenderParams->nSpecularTexID != -1 )
// 		{
// 			pRenderer->SetLayerCount( 2 );
// 			pRenderer->SetTextureId( pRenderParams->nSpecularTexID, 1 );
// 			pRenderer->EnableSpecular( TRUE );
// 		}
// 
// 		if( dwColor != m_dwOldColor )
// 		{
// 			DWORD* diffuse = GetDiffuseLocked();
// 			for( int i = 0; i < GetVertexCount(); i++ )
// 			{
// 				if( diffuse )
// 					GetWorldDiffuses()[i] = diffuse[i];
// 				else
// 					GetWorldDiffuses()[i] = dwColor;
// 			}
// 			UnlockDiffuse();
// 			m_dwOldColor = dwColor;
// 		}
// 
// 		Vector2* uvs = m_ChunkData->m_pUVs[0];
// 		if( fu != m_fOldU || fv != m_fOldV )
// 		{
// 			for( int i = 0; i < GetVertexCount(); i++ )
// 			{
// 				GetWorldUvs()[i].x = uvs[i].x+fu;
// 				GetWorldUvs()[i].y = uvs[i].y+fv;
// 			}
// 			m_fOldU = fu;
// 			m_fOldV = fv;
// 		}
// 
// 		if( m_nTileFrameId != nTileFrameId || m_nUTiles != nUTiles || m_nVTiles != nVTiles )
// 		{
// 			int row = nTileFrameId/nUTiles;
// 			int col = nTileFrameId%nUTiles;
// 
// 			float du = 1.0f/nUTiles;
// 			float dv = 1.0f/nVTiles;
// 			if( nUTiles > 1 || nVTiles > 1 )
// 			{
// 				//assert( GetVertexCount()%4 == 0 && "geom use mtl tiling, but vertex count %4 != 0" );
// 				int nBoardCount = GetVertexCount()/4;
// 				for( int i = 0; i < nBoardCount; i++ )
// 				{
// 					GetWorldUvs()[4*i+0].x = du*col;
// 					GetWorldUvs()[4*i+0].y = dv*row+dv;
// 
// 					GetWorldUvs()[4*i+1].x = du*col;
// 					GetWorldUvs()[4*i+1].y = dv*row;
// 
// 					GetWorldUvs()[4*i+2].x = du*col+du;
// 					GetWorldUvs()[4*i+2].y = dv*row+dv;
// 
// 					GetWorldUvs()[4*i+3].x = du*col+du;
// 					GetWorldUvs()[4*i+3].y = dv*row;
// 				}
// 			}
// 			m_nTileFrameId = nTileFrameId;
// 			m_nUTiles = nUTiles;
// 			m_nVTiles = nVTiles;
// 		}
// 
// 		{
// 			if( IsBillboard() )
// 				pRenderer->SetVertices( ((CBillboardGeoChunk*)this)->GetWorldBillboardVertices() );
// 			else
// 				pRenderer->SetVertices( GetWorldVertices() );
// 			pRenderer->SetNormals( GetWorldNormals() );
// 			pRenderer->SetDiffuse( GetWorldDiffuses() );
// 			pRenderer->SetUVs( GetWorldUvs(), 0 );
// 			pRenderer->SetUVs( GetWorldUvs(), 1 );
// 			pRenderer->SetIndices( m_ChunkData->m_pFaces );
// 
// 
// 		}
// 
// 		pRenderer->SetTextureId( stUseTexId, 0 );
// 		pRenderer->SetShaderId( MEX2_SHADER );
// 
// 		// add [5/26/2008 whu]
// 		pRenderer->SetTextureId( stUseLuminanceTexId, 2 );
// 
// 
// 		pRenderer->Push( GetVertexCount(), GetFaceCount(), dwFlag );
// 		pRenderer->Flush( 0 );
// 	}
// }

void CMexChunkBase::InitialBBox()
{

	Vector* vertices= GetVertices();
	if (vertices)
	{
		for( int j = 0; j < GetVertexCount(); j++ )
		{
			Vector& v = (vertices[j]);

			if( v.x < m_vMin.x )
				m_vMin.x = v.x;
			if( v.y < m_vMin.y )
				m_vMin.y = v.y;
			if( v.z < m_vMin.z )
				m_vMin.z = v.z;

			if( v.x > m_vMax.x )
				m_vMax.x = v.x;
			if( v.y > m_vMax.y )
				m_vMax.y = v.y;
			if( v.z > m_vMax.z )
				m_vMax.z = v.z;
		}
	}
	m_vCenter = (m_vMax + m_vMin)/2;
}

void CMexChunkBase::createBuffers()
{
	if( GetFaceCount() > 0 && IsNeedNormalPoints())
	{
		m_pNormalPoints = MeNew Vector[GetVertexCount()];

		for( int nVert = 0; nVert < GetVertexCount(); nVert++ )
		{
			m_pNormalPoints[nVert] = GetVertices()[nVert]+GetNormals()[nVert];
		}

	}

	if(GetFaceCount() > 0 )
	{
		CreateIndexBuffer();
		CreateVertexBuffers(GetD3DUSAGE(), GetD3DPOOL());
	}
}

void CMexChunkBase::restoreBuffers()
{
	if (GetD3DPOOL() == D3DPOOL_MANAGED)
	{
		return;
	}

	if(GetFaceCount() > 0 )
	{
		CreateVertexBuffers(GetD3DUSAGE(), GetD3DPOOL());
	}
}

void CMexChunkBase::invalidateBuffers()
{
	SafeRelease(verticesBuffer);
	SafeRelease(normalsBuffer);
	SafeRelease(diffusesBuffer);
	SafeRelease(uvsBuffer);
	SafeRelease(uvsBuffer2);
}

void CMexChunkBase::OnDeviceLost()
{
	if (D3DPOOL_MANAGED != GetD3DPOOL())
	{
		SafeRelease(verticesBuffer);
		SafeRelease(normalsBuffer);
		SafeRelease(diffusesBuffer);
		SafeRelease(uvsBuffer);
		SafeRelease(uvsBuffer2);
		// m_pIB 是系统拖管的资源, 无需手动释放
	}
}

void CMexChunkBase::AfterCreateBuffers()
{

}

void CMexChunkBase::destroyBuffers()
{
	SafeRelease(verticesBuffer);
	SafeRelease(normalsBuffer);
	SafeRelease(diffusesBuffer);
	SafeRelease(uvsBuffer);
	SafeRelease(uvsBuffer2);
	SafeRelease(m_pIB);
}

void CMexChunkBase::RebuildBuffer()
{
	SafeRelease(verticesBuffer);
	SafeRelease(normalsBuffer);
	SafeRelease(diffusesBuffer);
	SafeRelease(uvsBuffer);
	SafeRelease(uvsBuffer2);

	if(GetFaceCount() > 0 )
	{
		CreateVertexBuffers(GetD3DUSAGE(), GetD3DPOOL());
		LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
		short* shIBFace = NULL;
		HRESULT hr;
		if( !m_pIB )
		{
			while(1)
			{
				hr = pDev->CreateIndexBuffer( GetFaceCount()*3*sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL );
				if( SUCCEEDED(hr) ) break;
			}
		}

		while(1)
		{
			hr = m_pIB->Lock( 0, 0, (void**)&shIBFace, 0 );
			if( SUCCEEDED(hr) ) break;
		}

		memcpy( shIBFace, GetFaces(), GetFaceCount()*sizeof(short)*3 );

		while(1)
		{
			hr = m_pIB->Unlock();
			if( SUCCEEDED(hr) ) break;
		}
	}
}

CMexChunkBase::CMexChunkBase(CMexChunkData* pChunkData)
:m_pNormalPoints(NULL)
{ 
	m_ChunkData = pChunkData;
	verticesBuffer = NULL;
	normalsBuffer = NULL;
	diffusesBuffer = NULL;
	uvsBuffer = NULL;
	uvsBuffer2 = NULL;
	m_pIB = NULL;
	m_spRenderObject = 0;
	m_vMax = Vector( -10000.0f, -10000.0f, -10000.0f );			//added by zhuomeng.hu		[8/17/2010]
	m_vMin = Vector( 10000.0f, 10000.0f, 10000.0f );			//added by zhuomeng.hu		[8/17/2010]
	m_bSolidChunk = false;
	m_bNoSortChunk = false;
	m_bIsAvatarComponent = false;
	InitialBBox();
}

CMexChunkBase::~CMexChunkBase()
{
	destroyBuffers();
	MEX2_SAFE_DELETE_ARRAY(m_pNormalPoints);

	m_spRenderObject = NULL;
	MEX2_SAFE_DELETE( m_ChunkData );
}

CMexChunkBase* CMexChunkData::CreateMexChunk( CMexChunkData* pChunkData )
{
	
	CMexChunkBase* pRet = NULL;
	char lwrName[MAX_PATH] = {0};
	const char* pszName = pChunkData->GetName();
	strncpy( lwrName, pszName, MAX_PATH );
	strlwr(lwrName);
	if (strstr(lwrName, "sfloor") )
	{
		pRet = MeNew CSupperFloorGeoChunk(pChunkData);
	}
	else if ( strstr(lwrName, "rfloor") )    // 只判断人站立位置，不碰相机
	{
		pRet = MeNew CRfloorGeoChunk(pChunkData);
	}
	else if ( strstr(lwrName, "floor") )
	{
		pRet = MeNew CFloorGeoChunk(pChunkData);
	}
	else if ( strstr(lwrName, "rcoli"))	// 只碰撞人，不碰相机
	{
		pRet = MeNew CRCollisionGeoChunk(pChunkData);
	}
	else if ( strstr(lwrName, "abox") )	// 半透判断的碰撞盒
	{
		pRet = MeNew CAlphaBoxGeoChunk(pChunkData);
	}	
	else if ( strstr(lwrName, "coli") )	// 对人和相机都碰撞
	{
		pRet = MeNew CCollisionGeoChunk(pChunkData);
	}
	else if (strstr(lwrName, "noshadow"))
	{
		//pRet = MeNew CNoShadowGeoChunk(pChunkData); //lyh--  取消掉不正确的做法。 唯一一个 标记m_bHaveShadow 为false的时候 ，不绘制shadow map 即可实现建不绘制阴影 
		
	}

	if (pRet == NULL)
	{
		switch (pChunkData->GetProperty().nType)
		{
		case Mex2GeoChunkProperty::eBillboard:
			{
				pRet = MeNew CBillboardGeoChunk(pChunkData);
			}
			break;
		case Mex2GeoChunkProperty::eDecal:
			{
				pRet = MeNew CDecalGeoChunk(pChunkData);
			}
			break;
		case Mex2GeoChunkProperty::eDynamic:
			{
				pRet = MeNew CDynamicGeoChunk(pChunkData);
			}
			break;
		case Mex2GeoChunkProperty::eSkeleton:
			{
				pRet = MeNew CSkeletonGeoChunk(pChunkData);
			}
			break;
		default:
			{
			}
		}
	}

	if (pRet == NULL)
		pRet = MeNew CStaticGeoChunk(pChunkData);
	/*
	// added, jiayi, [2010/6/18]
	if( strstr( lwrName, "shimmer" ) ) // shimmer效果标识
	{
		pRet->SetCollectibleType( SortRenderable::eCT_Shimmer );		
	}
	*/

	if (strstr(lwrName, ".solid") )
	{
		pRet->SetSolidChunk(true);
	}
	if (strstr(lwrName, ".nosort") )
	{
		pRet->SetNoSortChunk(true);
	}
	return pRet;
}

float CMexChunkBase::GetDisToCameraEye( float* pMatrices )
{
	D3DXVECTOR3 vCenterInWorld;
	D3DXVec3TransformCoord( &vCenterInWorld, (D3DXVECTOR3*)&m_vCenter, (D3DXMATRIX*)pMatrices );

	D3DXVECTOR3 vDis = vCenterInWorld - GetMe3dConfig()->GetCamera()->GetEyePt();

	// modified [8/27/2010 zhangjiayi]
	// D3DXVec3LengthSq取代D3DXVec3Length
	return D3DXVec3LengthSq(&vDis);
}

// BOOL Mex2GeoChunk::Intersect( Vector* pvStart, Vector* pvDir,float* hits,  int nMax_INTERSECTION, int& nHit, DWORD dwFlag )
// {
// 	nHit = 0;
// 	if( dwFlag == eMex_HitFloor &&
// 		!IsFloor() )
// 		return false;
// 	float* pVertices = (float*)GetVerticesLocked();
// 	WORD* pFaces = (WORD*)GetIndicesLocked();
// 	int nFaceCount = GetFaceCount();
// 	for( int nFaceId = 0; nFaceId < nFaceCount; nFaceId++ )
// 	{
// 		WORD* pFace = &(pFaces[nFaceId*3]);
// 
// 		Vector* p0 = (Vector*)&pVertices[pFace[0]];
// 		Vector* p1 = (Vector*)&pVertices[pFace[1]];
// 		Vector* p2 = (Vector*)&pVertices[pFace[2]];
// 
// 		float tu, tv, t;
// 
// 		if( IntersectTri( 
// 			p0, 
// 			p1, 
// 			p2, 
// 			pvStart, 
// 			pvDir,
// 			&tu, 
// 			&tv,
// 			&t ) )
// 		{
// 			if( FloatCmp( t, 0 ) <= 0 )
// 				continue;
// 			if( nHit < nMax_INTERSECTION )
// 				hits[nHit++] = t;
// 			assert( nHit <= nMax_INTERSECTION );
// 		}
// 	}
// 	UnlockVertices();
// 	UnlockIndices();
// 
// 	return nHit != 0;
// }

bool	Mex2GeoChunk::IntersectQuick( Vector* pvStart, Vector* pvDir, MexReplaceableTextureProj* replaceableTexture, D3DXMATRIX* pModelInverseMatrix )
{
	Mex2Material* mtl = GetMtl();
	if(!mtl)
	{
		return false;//可能是包围盒之类的，没有贴图，所以不计算在内，继续查找				
	}
	int nMtl = GetMtlId();
	DWORD flag = mtl->GetLayer(0)->GetFlag();
	bool bAlphaEnable = (flag & MEX2_ALPHATEST) || (flag & MEX2_ALPHABLEND);

	bool bRet = false;
	Vector* pVertices = 0;
	if(IsBillboard())//处理billboard
	{
		CBillboardGeoChunk* pBillboardChunk = dynamic_cast<CBillboardGeoChunk*>(this);
		if( !pBillboardChunk )
			return false;

		pVertices = pBillboardChunk->GetWorldBillboardVertices();
		if( !pVertices )
			return false;

		if(!pBillboardChunk->IsBillboardLocaled())
		{
			D3DXVECTOR3* pBillboardVtxs = (D3DXVECTOR3*)pVertices;
			for(int j = 0 ; j < GetVertexCount(); ++ j)
			{
				D3DXVECTOR3* vBillboard = &pBillboardVtxs[j];
				D3DXVec3TransformCoord( vBillboard, vBillboard, pModelInverseMatrix );				
			}
			pBillboardChunk->SetBillboardLocaled( true );
		}
	}
	else
		pVertices = GetVerticesLocked();

	// 加保护
	if( !pVertices )
		return false;

	Vector* pHrVertices = (Vector*)pVertices;

	Mex2Face* indices = GetIndicesLocked();
	if (!indices )
	{
		return false;
	}
	for( int nFaceId = 0; nFaceId < GetFaceCount(); nFaceId++ )
	{
		Vector* p0 = (Vector*)&pHrVertices[indices[nFaceId].nId[0]];
		Vector* p1 = (Vector*)&pHrVertices[indices[nFaceId].nId[1]];
		Vector* p2 = (Vector*)&pHrVertices[indices[nFaceId].nId[2]];
		float tu, tv, t;

		if( IntersectTri( 
			p0, 
			p1, 
			p2, 
			pvStart, 
			pvDir,
			&tu, 
			&tv,
			&t ) )
		{
			if( FloatCmp( t, 0 ) <= 0 )
				continue;
			if(!bAlphaEnable)
			{
				bRet = true;
				break;
			}

			bool bHasAlpha = false;

			ITexture* pTexture = GetEngine()->GetTextureManager()->
				GetTextureNoLock( replaceableTexture->GetRenderTextureID(nMtl) );

			if(pTexture)
			{
				IDirect3DTexture9* pTex = (IDirect3DTexture9*)pTexture->GetData();
				// Put the colorkey in the texture's native format
				D3DSURFACE_DESC d3dsd;
				pTex->GetLevelDesc( 0, &d3dsd );

				UncompressedTexture UncompressedTexture;
				if (d3dsd.Format != D3DFMT_A8R8G8B8)
				{
					if (d3dsd.Format == D3DFMT_DXT1 || d3dsd.Format == D3DFMT_DXT2
						|| d3dsd.Format == D3DFMT_DXT3 || d3dsd.Format == D3DFMT_DXT4 || d3dsd.Format == D3DFMT_DXT5)
					{
						UncompressedTexture.Create(d3dsd.Width, d3dsd.Height, 1, 0, D3DFMT_A8R8G8B8);
						if (FAILED(UncompressedTexture.DecompressCompressedTextureSurface(pTex, 0, D3DX_DEFAULT, 0)))
						{
							return true;
						}
					}
					else
					{
						return true;
					}
				}

				if (UncompressedTexture.GetTexturePtr() != NULL)
					pTex = UncompressedTexture.GetTexturePtr();

				// Lock the texture
				D3DLOCKED_RECT  d3dlr;
				if ( FAILED( pTex->LockRect( 0, &d3dlr, 0, 0 ) ) )
					continue;

				DWORD x = tu * d3dsd.Width;
				DWORD y = tv * d3dsd.Height;

				DWORD color = ((DWORD *) d3dlr.pBits) [ y * d3dsd.Width + x ];					

				DWORD a = ( (color & 0xff000000) >> 24 );
				if ( a == 0 )
				{						
					bHasAlpha = 1;							
				}				

				pTex->UnlockRect(0);
			}
			if (!bHasAlpha)
			{
				bRet = true;
				break;
			}
		}
	}
	UnlockIndices();
	if (IsBillboard())
	{
	}
	else
		UnlockVertices();

	return bRet;
}



Vector* CMexChunkBase::GetVerticesLocked()
{
// 	return GetVertices();
	void* vb = 0;
	GetVerticesBuffer()->Lock(0, 0, &vb, 0 );
// 	if (IsDynamic())
// 	{
// 		GetVerticesBuffer()->Lock(0, 0, &vb, D3DLOCK_DISCARD );
// 	}
// 	else
// 	{
// 		GetVerticesBuffer()->Lock(0, 0, &vb, D3DLOCK_READONLY );
// 	}
	return (Vector*)vb;
}

Vector* CMexChunkBase::GetNormalsLocked()
{
//  	return GetNormals();
	void* vb = 0;
	GetNormalsBuffer()->Lock(0, 0, &vb, 0 );
	return (Vector*)vb;
}

Vector2* CMexChunkBase::GetUVsLocked( int nLayer )
{ 
	guardfunc;
//  	if( nLayer < 0 || nLayer > 4 )
//  	{
//  		assert( false );
//  		return NULL;
//  	}
//  	return GetUVs(); 
	void* vb = 0;
	GetUvsBuffer()->Lock(0, 0, &vb, 0 );
	return (Vector2*)vb;
	unguard;
}

DWORD* CMexChunkBase::GetDiffuseLocked()
{
//  	return GetDiffuses();
	void* vb = 0;
	if (GetDiffusesBuffer())
	{
		GetDiffusesBuffer()->Lock(0, 0, &vb, 0 );
	}
	return (DWORD*)vb;
}

Mex2Face* CMexChunkBase::GetIndicesLocked()
{
//  	return m_pFaces;
	void* vb = 0;
	if (GetIB())
	{
		GetIB()->Lock(0, 0, &vb, 0 );
	}
	return (Mex2Face*)vb;
}



void CMexChunkBase::UnlockVertices()
{
 	GetVerticesBuffer()->Unlock();
}

void CMexChunkBase::UnlockNormals()
{
	GetNormalsBuffer()->Unlock();

}

void CMexChunkBase::UnlockUVs(int nLayer)
{
	GetUvsBuffer()->Unlock();

}

void CMexChunkBase::UnlockDiffuse()
{
	if (GetDiffusesBuffer())
	{
		GetDiffusesBuffer()->Unlock();
	}
}

void CMexChunkBase::UnlockIndices()
{
 	GetIB()->Unlock();

}

bool CHelperGeoChunk::Render( RenderParams* params, DWORD dwFlagEx /*= 0*/, IReplaceableTextureProj* pLuminanceTextureProj /*= NULL*/, int* pVertexCount/*=NULL*/, int* pFaceCount/*=NULL*/ )
{
	MeScopeProfileMexGeoChunkFun
	guardfunc;
// 	if (!IsHelper())
// 	{
// 		return false;
// 	}
	if( GetMe3dConfig()->GetRenderHelper() == Config::None_Helper)
		return false;
	if (GetMe3dConfig()->GetRenderHelper() == Config::Floor_Helper && (!IsFloor() ))
	{
		return false;
	}
	if (GetMe3dConfig()->GetRenderHelper() == Config::Supper_Floor_Helper && (!IsSupperFloor() ))
	{
		return false;
	}
	if (GetMe3dConfig()->GetRenderHelper() == Config::Collision_Helper && (!IsCollision()))
	{
		return false;
	}
	if (GetMe3dConfig()->GetRenderHelper() == Config::Alpha_Box_Helper && (GetType() != Mex2GeoChunkProperty::eAlphaBox) )
	{
		return false;
	}

	if( GetVertexCount() == 0 || GetFaceCount() == 0 )
		return false;

	float* pMatrices = params->pMatrices;
	IRenderer* pRenderer = GetEngine()->GetRenderer();

	((RendererDx*)pRenderer)->SetLightDiffuse(LIGHT_INDEX_COLLISION, *GetHelperColor());
	DWORD dwFlag = dwFlagEx | eOpModulate1X;
	short stUseTexId = -1;
	// add [5/26/2008 whu]
	short stUseLuminanceTexId = -1;

	if( GetVertexCount() >= MAX_VERTEX_PER_CHUNK )
	{
		assert( false );
		return false;
	}

	// 统计
	if( pVertexCount )
		*pVertexCount = GetVertexCount();
	if( pFaceCount )
		*pFaceCount = GetFaceCount();

	//EnterCriticalSection( &gs_BufferCS );
	short nShaderID = HELP_COLI_FLOOR;

	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();

	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;
	MeModelRenderObject* pkFinal = dynamic_cast< MeModelRenderObject* >( pkObject );
	if( pkFinal )
	{
		if( MeRenderManager::Instance()->IsFreshObject( this ) )
		{
			pkFinal->SetUseTexId( stUseTexId );
			pkFinal->SetShaderId( nShaderID );
			pkFinal->SetFVF( rd->GetCurrentSurface()->m_dwFVF );
			pkFinal->SetVertexCount( GetVertexCount() );
			pkFinal->SetVB( GetVerticesBuffer() );
			pkFinal->SetNB( GetNormalsBuffer() );
			pkFinal->SetDB( GetDiffusesBuffer() );
			pkFinal->SetUVB( GetUvsBuffer() );
			pkFinal->SetIB( GetIB() );
			pkFinal->SetFaceCount( GetFaceCount() );
			pkFinal->SetFlag( dwFlag );
			pkFinal->SetUseLuminanceTexId( stUseLuminanceTexId );
			pkObject->GenerateKey();
			MeRenderManager::Instance()->AddObject( this );
		}		
	}
	PushOtherInfo( params, false );
	SetCollectibleType( SortRenderable::eCT_Count );

	//LeaveCriticalSection( &gs_BufferCS );
	unguard;
	return true;
}

void CDecalGeoChunk::_DoRender( const RenderParams* params )
{
	MeScopeProfileMexGeoChunkFun
	if( params->pMatrices != NULL )
	{
		if(false == BlendVertex( (float*)GetWorldVertices(), (float*)GetWorldNormals(), MAX_VERTEX_PER_CHUNK, params->pMex, (float*)params->pMatrices ,NULL))
			return;
		SetWorldMatrix(*(MeMatrix*)params->pMatrices);
	}
	float fHeight = 0.f;
	float fOffset = 0.08f;
	BOOL bInFloor = false;
	DWORD dwDecalRet = 0;
	BOOL bHasPos = false;

	DWORD dwTime = timeGetTime();

	if(!IsEqualToWorldMatrix(m_decalMatrix))
	{
		m_decalVectorList.clear();
		m_decalVectorCount = 0;

		float* fW = (float*)m_WorldMatrix.m;
		float* fD = (float*)m_decalMatrix.m;
		for( int i=0; i<16; i++ )
		{
			fD[i] = fW[i];
		}
	}

	//顶点高度拣选效率提高
	for( int nDecalVert = 0 ; nDecalVert < GetVertexCount(); ++ nDecalVert)
	{
		Vector tVector1;
		Vector tVector2;
		for(int i=0;i<m_decalVectorList.size();++i)
		{
			tVector1 = m_decalVectorList[i];
			tVector2 = GetWorldVertices()[nDecalVert];

			tVector1.z=0;
			tVector2.z=0;

			tVector1 = tVector1-tVector2;

			// modified, [8/6/2010 zhangjiayi]				
			if(tVector1.lengthsq()<0.01f)
			{
				GetWorldVertices()[nDecalVert].z = m_decalVectorList[i].z;
				bHasPos = true;
				break;
			}
		}

		if(!bHasPos && ms_pfGetZByXY )
		{
			// 第一个参数20是个测试数字，可能不会适应所有场景，主要用于地表为模型的时候
			fHeight = ms_pfGetZByXY( GetWorldVertices()[nDecalVert].z + 4.f,   GetWorldVertices()[nDecalVert].x, GetWorldVertices()[nDecalVert].y, 0, &bInFloor, &dwDecalRet, 0, 0 );
			GetWorldVertices()[nDecalVert].z = fHeight + fOffset;

			if(m_decalVectorList.size()<DECAL_VERTEX_COUNT)
			{
				m_decalVectorList.push_back(GetWorldVertices()[nDecalVert]);

				m_decalVectorCount = 0;
			}
			else
			{
				m_decalVectorList[m_decalVectorCount] = GetWorldVertices()[nDecalVert];

				if(m_decalVectorCount<DECAL_VERTEX_COUNT-1)
					++m_decalVectorCount;
				else
					m_decalVectorCount = 0;
			}

		}
	}		
	dwTime = timeGetTime()-dwTime;

	void* vb = 0;
	if (SUCCEEDED(GetVerticesBuffer()->Lock(0, 0, &vb, D3DLOCK_DISCARD)))
	{
		memcpy(vb, GetWorldVertices(), GetVertexCount()*sizeof(Vector));
		GetVerticesBuffer()->Unlock();
	}
	void* nb = 0;
	if (SUCCEEDED(GetNormalsBuffer()->Lock(0, 0, &nb, D3DLOCK_DISCARD)))
	{
		memcpy(nb, GetWorldNormals(), GetVertexCount()*sizeof(Vector));
		GetNormalsBuffer()->Unlock();
	}
	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	GetEngine()->GetRenderer()->SetTransform( D3DTS_WORLD, (float*)&world );


	m_spRenderObject->DoRender();

}




// void CDecalGeoChunk::_Render( RenderParams* params )
// 							 
// {
// 	//EnterCriticalSection( &gs_BufferCS );
// 
// 
// 
// 	short nShaderID = MEX2_SHADER;
// 
// 	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
// 	params->fGlobalAlpha = rd->GetGlobalTransparent();
// 	if( IsAlphaChunk(params) )
// 	{
// 		params->dwFlag |= eAlphaBlend;	
// 	}
// 	else
// 	{
// 		params->fGlobalAlpha = 1.0;
// 	}
// 
// 	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;
// 	MeModelRenderObject* pkFinal = dynamic_cast< MeModelRenderObject* >( pkObject );
// 	if( pkFinal )
// 	{
// 		bool bPost = false;
// 		if( IsAlphaChunk(params) )
// 		{
// 			SetCollectibleType( SortRenderable::eCT_AlphaBlend );
// 			bPost = true;
// 		}
// 
// 		if( MeRenderManager::Instance()->IsFreshObject( this ) )		
// 		{
// 			pkFinal->SetUseTexId( params->stUseTexId );
// 			pkFinal->SetShaderId( nShaderID );
// 			pkFinal->SetFVF( rd->GetCurrentSurface()->m_dwFVF );
// 			pkFinal->SetVertexCount( GetVertexCount() );
// 			pkFinal->SetVB( GetVerticesBuffer() );
// 			pkFinal->SetNB( GetNormalsBuffer() );
// 			pkFinal->SetDB( GetDiffusesBuffer() );
// 			pkFinal->SetUVB( GetUvsBuffer() );
// 			pkFinal->SetIB( GetIB() );
// 			pkFinal->SetFaceCount( GetFaceCount() );
// 			if (!bPost)
// 			{
// 				pkFinal->SetFlag( params->dwFlag );
// 			}
// 			pkFinal->SetUseLuminanceTexId( params->stUseLuminanceTexId );
// 			pkObject->GenerateKey();
// 			MeRenderManager::Instance()->AddObject( this );
// 		}		
// 		PushOtherInfo( params,bPost );
// 		SetCollectibleType( SortRenderable::eCT_Count );
// 		
// 	}
// 	//LeaveCriticalSection( &gs_BufferCS );
// }

CDecalGeoChunk::funcGetZByXY CDecalGeoChunk::ms_pfGetZByXY = 0;

CDecalGeoChunk::CDecalGeoChunk( CMexChunkData* pChunkData ) :Mex2GeoChunk(pChunkData)
,m_decalVectorCount(0)

{
	m_decalVectorList.clear();
	// 世界矩阵初始化为零矩阵
	float* fM = (float*)m_WorldMatrix.m;
	for( int i=0; i<16; i++ )
		fM[i] = 0.f;

	fM = (float*)m_decalMatrix.m;
	for( int i=0; i<16; i++ )
		fM[i] = 0.f;

	m_spRenderObject = MeNew MeModelRenderObject;

}

void CBillboardGeoChunk::createBuffers()
{
	if (!CanCombinedRender())
	{
		CMexChunkBase::createBuffers();
	}
}

void CBillboardGeoChunk::_WriteUVBuffer( DWORD lockFlag )
{
	if (!CanCombinedRender())
	{
		Mex2GeoChunk::_WriteUVBuffer(lockFlag);
	}
	else
	{
		memcpy(GetUVs(), GetWorldUvs(), GetVertexCount()*sizeof(Vector2));
	}
}

void CBillboardGeoChunk::_WriteDiffuseBuffer( DWORD dwColor, DWORD lockFlag )
{
	if (!CanCombinedRender())
	{
		Mex2GeoChunk::_WriteDiffuseBuffer(dwColor,lockFlag);
	}
	else 		if (IsExistDiffuse())
	{
		for (int i = 0; i < GetVertexCount(); ++i)
		{
			GetDiffuses()[i] = dwColor;
		}
	}

}

bool CBillboardGeoChunk::CanCombinedRender()
{
	return false;
	//return (GetVertexCount() <= 4);
}

void CBillboardGeoChunk::CombinedRender(bool bPost,int nBaseVertex, Vector* m_VertexMem, Vector* m_NormalMem, DWORD* m_DiffuseMem, Vector2* m_UvsMem/*, unsigned short* m_shIBMem */)
{
	int nCount = 0;
	int nPostIndex = 0;
	const int nBreakIndex = 100000;
	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
	for( RenderParams::OtherInfosConstIter otherit = GetOtherInfos( bPost ).begin(); 
		otherit != GetOtherInfos( bPost ).end() ; ++ otherit )
	{	
		const RenderParams* params = (*otherit );
		if (bPost)
		{
			if (nBreakIndex == nPostIndex)
			{
				break;
			}
			if (nPostIndex < m_nCurrPostIndex)
			{
				++nPostIndex;
				continue;
			}
			else
			{
				nPostIndex = nBreakIndex;
				m_spRenderObject->SetFlag(params->dwFlag);
				m_spRenderObject->SetUseTexId(params->stUseTexId);
				++m_nCurrPostIndex;
			}
		}
		int nCurrVertexBase = GetVertexCount()*nCount;

		if( params->pMatrices != NULL )
		{
			if(!BlendVertex( (float*)GetWorldVertices(), NULL, MAX_VERTEX_PER_CHUNK, params->pMex, (float*)params->pMatrices ,NULL))
				continue;
		}
		UpdateBillboard(&m_VertexMem[nCurrVertexBase],params->pMatrices);

		memcpy(&m_NormalMem[nCurrVertexBase],GetNormals(),GetVertexCount()*sizeof(Vector));


		float fAlpha = params->fGlobalAlpha;
		rd->SetGlobalTransparent( params->fGlobalAlpha );
		if (IsExistDiffuse())
		{
// 			if (fAlpha < 1.0f)
// 			{
// 				if( (params->dwFlag & eRenderTreeLeaf) && fAlpha < 0.5f )
// 				{
// 					fAlpha = 0.65;
// 				}
// 				for(int i = 0; i <  GetVertexCount();++i)
// 				{
// 					DWORD alpha = ((DWORD)((GetDiffuses()[i] & 0xFF000000) * fAlpha) )& 0xFF000000;
// 					m_DiffuseMem[i + nCurrVertexBase] = (GetDiffuses()[i] & 0x00FFFFFF) | alpha;
// 				}
// 			}
// 			else
			{
				memcpy(&m_DiffuseMem[nCurrVertexBase],GetDiffuses(),GetVertexCount()*sizeof(DWORD));
			}
		}
		else
		{
			DWORD dwDefaultColor = m_dwOldColor;
// 			if (fAlpha < 1.0f)
// 			{
// 				if( (params->dwFlag & eRenderTreeLeaf) && fAlpha < 0.5f )
// 				{
// 					fAlpha = 0.65;
// 				}
// 				DWORD alpha = ((DWORD)(0xFF000000 * fAlpha) )& 0xFF000000;
// 				dwDefaultColor = (0x00FFFFFF) | alpha;
// 			}
			for(int i = 0; i <  GetVertexCount();++i)
			{
				m_DiffuseMem[i + nCurrVertexBase] = dwDefaultColor;
			}
		}

		memcpy(&m_UvsMem[nCurrVertexBase],GetUVs(),GetVertexCount()*sizeof(Vector2));

		++nCount;
	}
	ClearOtherInfo( bPost );
}


void CBillboardGeoChunk::_DoRender( const RenderParams* params )
{
	MeScopeProfileMexGeoChunkFun
	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	rd->SetTransform( D3DTS_WORLD, (float*)&world );
	if( params->pMatrices != NULL )
	{
		if(!BlendVertex( (float*)GetWorldVertices(), NULL, MAX_VERTEX_PER_CHUNK, params->pMex, (float*)params->pMatrices ,NULL))
			return;
	}

	//   added 2003.01.15
	// 未注册
	UpdateBillboard(params->pMatrices);

	void* vb = 0;
	if (SUCCEEDED(GetVerticesBuffer()->Lock(0, 0, &vb, D3DLOCK_DISCARD)))
	{
		memcpy(vb, billboard_vertices, GetVertexCount()*sizeof(Vector));
		GetVerticesBuffer()->Unlock();
	}


	m_spRenderObject->DoRender();			

}



// void CBillboardGeoChunk::_Render( RenderParams* params )
// 								 
// {
// 	//EnterCriticalSection( &gs_BufferCS );
// 
// 	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;
// 	MeModelRenderObject* pkFinal = dynamic_cast< MeModelRenderObject* >( pkObject );
// 	if( !pkFinal )
// 		return;
// 
// 	short nShaderID = MEX2_SHADER;
// 
// 	bool bPost = false;
// 
// 
// 	if( GetCollectibleType() == SortRenderable::eCT_Shimmer )
// 	{
// 		pkFinal->SetAddMapId( MeShimmerCollector::GetFrameTextureId() );
// 		params->dwFlag |= ( eShimmer | eTwoSided );
// 		params->dwFlag &= ~eAlphaBlend;
// 		bPost = true;
// 	}			
// 	else
// 	{
// 		RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
// 		params->fGlobalAlpha = rd->GetGlobalTransparent();
// 		if( IsAlphaChunk(params) )
// 		{
// 			params->dwFlag |= eAlphaBlend;	
// 			if (GetCollectibleType() != SortRenderable::eCT_Shimmer)
// 			{
// 				SetCollectibleType( SortRenderable::eCT_AlphaBlend );
// 			}
// 			bPost = true;
// 		}
// 		else
// 		{
// 			params->fGlobalAlpha = 1.0;
// 		}
// 	}
// 
// 	{
// 		if( MeRenderManager::Instance()->IsFreshObject( this ) )			
// 		{
// 			pkFinal->SetUseTexId( params->stUseTexId );
// 
// 			pkFinal->SetShaderId( nShaderID );
// 			pkFinal->SetFVF( rd->GetCurrentSurface()->m_dwFVF );
// 			pkFinal->SetVertexCount( GetVertexCount() );
// 			pkFinal->SetVB( GetVerticesBuffer() );
// 			pkFinal->SetNB( GetNormalsBuffer() );
// 			pkFinal->SetDB( GetDiffusesBuffer() );
// 			pkFinal->SetUVB( GetUvsBuffer() );
// 			pkFinal->SetIB( GetIB() );
// 			pkFinal->SetFaceCount( GetFaceCount() );
// 			if (!bPost)
// 			{
// 				pkFinal->SetFlag( params->dwFlag );
// 			}
// 			pkFinal->SetUseLuminanceTexId( params->stUseLuminanceTexId );
// 			pkObject->GenerateKey();
// 			MeRenderManager::Instance()->AddObject( this );
// 		}		
// 		PushOtherInfo( params, bPost );
// 		SetCollectibleType( SortRenderable::eCT_Count );
// 		
// 	}
// 
// 	//LeaveCriticalSection( &gs_BufferCS );
// }
// 

CBillboardGeoChunk::CBillboardGeoChunk( CMexChunkData* pChunkData ) : Mex2GeoChunk( pChunkData ), billboard_vertices( NULL ), m_fFrontOffset( 0.0f )
{
    m_spRenderObject = MeNew MeBillboardRenderObject;

    if( GetProperty().dwFlag &  Mex2BbrdFlag_FrontOffset )
    {
        // 增加向前偏移     added by zhuomeng.hu		[1/27/2011]
        std::string strPlaneName( pChunkData->GetName() );
        std::string::size_type offBegin = strPlaneName.find( "_off" );
        std::string::size_type offEnd = std::string::npos;
        if( offBegin != std::string::npos )
        {
            if( strPlaneName.size() > offBegin + 4 )
            {
                offBegin += 4;
                offEnd = strPlaneName.find( "_", offBegin );
                if( offEnd != std::string::npos && offEnd > offBegin )
                {
                    std::string strNum = strPlaneName.substr( offBegin, offEnd - offBegin );
                    float fNum( 0.0f );
                    fNum = atof( strNum.c_str() );
                    if( fNum > 0.0f )
                    {
                        m_fFrontOffset = fNum;
                    }
                }
            }
        }
    }
}

CBillboardGeoChunk::~CBillboardGeoChunk()
{
	MEX2_SAFE_DELETE_ARRAY(billboard_vertices);
}

void CStaticGeoChunk::_DoRender( const RenderParams* params )
{
	MeScopeProfileMexGeoChunkFun
	GetEngine()->GetRenderer()->SetTransform( D3DTS_WORLD, &params->pMatrices[m_nSingleBoneId] );

	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
	static D3DLIGHT9 oldLight;
	if (params->m_bIsRenderModelSelected)
	{
		rd->GetLight(LIGHT_INDEX_TERRAIN,&oldLight);
		// 选中模型用红色显示
		D3DLIGHT9 light;
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Position = D3DXVECTOR3( 6, -6, 6 );
		light.Direction.x = 0.5f;
		light.Direction.y = 0.5f;
		light.Direction.z = 0.f;
		light.Ambient.a = 1.f;
		light.Ambient.r = 0.5f;
		light.Ambient.g = 0.2f;
		light.Ambient.b = 0.2f;
		light.Diffuse.a = 1.f;
		light.Diffuse.r = 0.5f;
		light.Diffuse.g = 0.2f;
		light.Diffuse.b = 0.2f;
		light.Specular.a = 0.0f;
		light.Specular.r = 0.3f;
		light.Specular.g = 0.3f;
		light.Specular.b = 0.3f;
		((RendererDx*)rd)->SetLight(LIGHT_INDEX_TERRAIN, &light);
	}
	m_spRenderObject->DoRender();		
	if (params->m_bIsRenderModelSelected)
	{
		((RendererDx*)rd)->SetLight(LIGHT_INDEX_TERRAIN, &oldLight);
	}

}



// void CStaticGeoChunk::_Render( RenderParams* params )
// 							  
// {
// 	//EnterCriticalSection( &gs_BufferCS );
// 
// 
// 	/*GetEngine()->GetRenderer()>SetTransform( D3DTS_WORLD, &params->pMatrices[m_nSingleBoneId] );*/
// 
// 	short nShaderID = MEX2_SHADER;
// 
// 	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
// 	params->fGlobalAlpha = rd->GetGlobalTransparent();
// 	if( IsAlphaChunk(params) )
// 	{
// 		params->dwFlag |= eAlphaBlend;	
// 	}
// 	else
// 	{
// 		params->fGlobalAlpha = 1.0;
// 	}
// 
// 
// 	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;
// 	MeModelRenderObject* pkFinal = dynamic_cast< MeModelRenderObject* >( pkObject );
// 	if( pkFinal )
// 	{
// 		bool bPost = false;
// 		if( ( IsAlphaChunk(params) ) && ( GetCollectibleType() != SortRenderable::eCT_Shimmer ) )
// 		{
// 			SetCollectibleType( SortRenderable::eCT_AlphaBlend );
// 			bPost = true;
// 		}
// 		if( MeRenderManager::Instance()->IsFreshObject( this ) )			
// 		{
// 			pkFinal->SetUseTexId( params->stUseTexId );
// 			if( GetCollectibleType() == SortRenderable::eCT_Shimmer )
// 			{
// 				pkFinal->SetAddMapId( MeShimmerCollector::GetFrameTextureId() );
// 				params->dwFlag |= ( eShimmer | eTwoSided );
// 				params->dwFlag &= ~eAlphaBlend;
// 				bPost = true;
// 			}
// 			pkFinal->SetShaderId( nShaderID );
// 			pkFinal->SetFVF( rd->GetCurrentSurface()->m_dwFVF );
// 			pkFinal->SetVertexCount( GetVertexCount() );
// 			pkFinal->SetVB( GetVerticesBuffer() );
// 			pkFinal->SetNB( GetNormalsBuffer() );
// 			pkFinal->SetDB( GetDiffusesBuffer() );
// 			pkFinal->SetUVB( GetUvsBuffer() );
// 			pkFinal->SetIB( GetIB() );
// 			pkFinal->SetFaceCount( GetFaceCount() );
// 			if (!bPost)
// 			{
// 				pkFinal->SetFlag( params->dwFlag );
// 			}
// 			pkFinal->SetUseLuminanceTexId( params->stUseLuminanceTexId );
// 			pkObject->GenerateKey();
// 			MeRenderManager::Instance()->AddObject( this );
// 		}		
// 		PushOtherInfo( params, bPost );
// 		SetCollectibleType( SortRenderable::eCT_Count );
// 		
// 	}
// 
// 
// 	//LeaveCriticalSection( &gs_BufferCS );
// }


CSkeletonGeoChunk::CSkeletonGeoChunk(CMexChunkData* pChunkData)
: Mex2GeoChunk(pChunkData),
boneWgtIdxBuffer(NULL),
m_bChangeColor(false)
{
	m_spRenderObject = MeNew MeSkeletonRenderObject;	
}

CSkeletonGeoChunk::~CSkeletonGeoChunk()
{
}

Vector2* CSkeletonGeoChunk::GetUVsLocked( int nLayer )
{ 
	guardfunc;
	if( nLayer < 0 || nLayer > 4 )
	{
		assert( false );
		return NULL;
	}
	return GetUVs(); 
	void* vb = 0;
	GetUvsBuffer()->Lock(0, 0, &vb, D3DLOCK_DISCARD );
	return (Vector2*)vb;
	unguard;
}

void CSkeletonGeoChunk::createBuffers()
{
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();

	short* shIBFace = NULL;
	if( !m_pIB )
	{
		while(1)
		{
			hr = pDev->CreateIndexBuffer( GetFaceCount()*3*sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}

	while(1)
	{
		hr = m_pIB->Lock( 0, 0, (void**)&shIBFace, 0 );
		if( SUCCEEDED(hr) ) break;
	}

	memcpy( shIBFace, GetFaces(), GetFaceCount()*sizeof(short)*3 );

	while(1)
	{
		hr = m_pIB->Unlock();
		if( SUCCEEDED(hr) ) break;
	}

	if( !verticesBuffer )
	{
		while(1)
		{
			hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(SkeletonVertex), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &verticesBuffer, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	SkeletonVertex* pVBPos = 0;
	while(1)
	{
		hr = verticesBuffer->Lock( 0, 0, (void**)&pVBPos, 0 );
		if( SUCCEEDED(hr) ) break;
	}

	if(!diffusesBuffer )
	{
		while(1)
		{
			hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(DWORD), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &diffusesBuffer, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	DWORD* pVBDiffuse = NULL;
	while(1)
	{
		hr = diffusesBuffer->Lock( 0, 0, (void**)&pVBDiffuse, 0 );
		if( SUCCEEDED(hr) ) break;
	}

	if( !uvsBuffer )
	{
		while(1)
		{
			hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(Vector2), D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &uvsBuffer, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	short stUVLayerCnt = GetUVLayerCount();
	if( stUVLayerCnt == 2 && !uvsBuffer2 )
	{
		while( 1 )
		{
			hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(Vector2), D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &uvsBuffer2, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	float* pVBUV = NULL;
	float* pVBUV2 = NULL;
	while(1)
	{
		hr = uvsBuffer->Lock( 0, 0, (void**)&pVBUV, 0 );
		if( SUCCEEDED(hr) ) break;
	}
	while(uvsBuffer2)
	{
		hr = uvsBuffer2->Lock( 0, 0, (void**)&pVBUV2, 0 );
		if( SUCCEEDED(hr) ) break;
	}

	//////////////////////////////////////////////////////////////////////////
	struct BoneInfo 
	{
		int boneIdx;
		float boneWgt;

		bool operator>(const BoneInfo& v)  const
		{
			return boneWgt > v.boneWgt;
		}
	};


	Vector* pVertices = GetVertices();
	Vector* pNormals = GetNormals();
	Vector2* pUVs = GetUVs();
	Vector2* pUVs2 = GetUVs(1);
	DWORD* pColors = GetDiffuses();
	std::vector<int> boneIdx;
	std::vector<float> boneWgt;
	std::vector<BoneInfo> boneInfos;

	int matrixIndex = 0;
	m_matrixIdxByBoneIdx.clear();
	for( int i = 0; i < GetVertexCount(); i++,  pVertices++, pNormals++, pUVs++ )
	{
		memset(pVBPos, 0, sizeof(SkeletonVertex));

		// 顶点
		pVBPos->x = pVertices->x;
		pVBPos->y = pVertices->y;
		pVBPos->z = pVertices->z;

		// 权重，骨骼索引

		int nBGId = GetBoneGroupIndices()[i];
		//add by yanli 2010-7-30 容错处理-------------------
		if (nBGId == 0xff)
		{
			nBGId = 0;
		}
		//---------------------------------------------------
		Mex2BoneGroup* bg = (Mex2BoneGroup*)(m_pSrcMex->GetBoneGroups()->GetBoneGroup(nBGId));
		if (bg)
		{
			boneIdx.clear();
			boneWgt.clear();
			boneInfos.clear();

			int nBoneCount = bg->GetBoneCount();
			for(int n = 0; n < nBoneCount; n++ )
			{
				int nBoneId = bg->GetBoneID(n);
				float fWeight = bg->GetBoneWeight(n);
				if (fWeight >= 0.1f)
				{
					boneIdx.push_back(nBoneId);
					boneWgt.push_back(fWeight);
				}
			}

			if (boneWgt.size() > 4)
			{
				float fLastWeight = 0.0f;
				for (int w = 0; w < 4; ++w)
				{
					fLastWeight += boneWgt[w];
				}

				if (fLastWeight < 1.0f)
				{
					float avgWgt = (1 - fLastWeight) / 3;
					for (int ib = 0; ib < 4; ++ib)
					{
						boneWgt[ib] += avgWgt;
					}
				}
			}
			else
			{
				float fLastWeight = 0.0f;
				// modified, [8/13/2010 zhangjiayi]
				if( !boneWgt.empty() )
				{
					for (int w = 0; w < boneWgt.size() - 1; ++w)
					{
						fLastWeight += boneWgt[w];
					}
					if ( fLastWeight < 1.0f)
						boneWgt[boneWgt.size() - 1] = 1 - fLastWeight;
				}				
			}

			for (int ibone = 0; ibone < boneIdx.size() && ibone < 4; ++ibone)
			{
				int nBoneId = boneIdx[ibone];
				pVBPos->blendWeights[ibone] = boneWgt[ibone];

				int index = 0;
				std::map<int, int>::iterator it = m_matrixIdxByBoneIdx.find(nBoneId);
				if (it != m_matrixIdxByBoneIdx.end())
				{
					index = it->second;
				}
				else
				{
					index = matrixIndex++;
					assert( index >= 0 && index < BoneMatrixCount );
					m_matrixIdxByBoneIdx[nBoneId] = min( BoneMatrixCount - 1, max(0,index) );
				}
				pVBPos->blendIndices[ibone] = static_cast<unsigned char>(index);
			}
		}

		// 法线
		pVBPos->nx = pNormals->x;
		pVBPos->ny = pNormals->y;
		pVBPos->nz = pNormals->z;
		++pVBPos;

		// 颜色
		if (pColors)
			*pVBDiffuse = pColors[i];
		else
			*pVBDiffuse = 0xffffffff;
		++pVBDiffuse;

		// UV
		*pVBUV++ = pUVs->x;
		*pVBUV++ = pUVs->y;
		if( pUVs2)
		{
			*pVBUV2++ = pUVs2->x;
			*pVBUV2++ = pUVs2->y;
			pUVs2++;
		}
	}

	while(1)
	{
		hr = verticesBuffer->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
	while(1)
	{
		hr = diffusesBuffer->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
	while(1)
	{
		hr = uvsBuffer->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
	while(uvsBuffer2)
	{
		hr = uvsBuffer2->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
}

void CSkeletonGeoChunk::restoreBuffers()
{
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	if( !uvsBuffer )
	{
		while(1)
		{
			hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(Vector2), D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &uvsBuffer, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	short stUVLayerCnt = GetUVLayerCount();
	if( stUVLayerCnt == 2 && !uvsBuffer2 )
	{
		while( 1 )
		{
			hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(Vector2), D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &uvsBuffer2, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	float* pVBUV = NULL;
	float* pVBUV2 = NULL;
	while(1)
	{
		hr = uvsBuffer->Lock( 0, 0, (void**)&pVBUV, 0 );
		if( SUCCEEDED(hr) ) break;
	}
	while(uvsBuffer2)
	{
		hr = uvsBuffer2->Lock( 0, 0, (void**)&pVBUV2, 0 );
		if( SUCCEEDED(hr) ) break;
	}

	Vector2* pUVs = GetUVs();
	Vector2* pUVs2 = GetUVs(1);
	for( int i = 0; i < GetVertexCount(); i++,  pUVs++ )
	{
		// UV
		*pVBUV++ = pUVs->x;
		*pVBUV++ = pUVs->y;
		if( pUVs2)
		{
			*pVBUV2++ = pUVs2->x;
			*pVBUV2++ = pUVs2->y;
			pUVs2++;
		}
	}

	while(1)
	{
		hr = uvsBuffer->Unlock();
		if( SUCCEEDED(hr) ) break;
	}

	while(uvsBuffer2)
	{
		hr = uvsBuffer2->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
}

void CSkeletonGeoChunk::invalidateBuffers()
{
	SafeRelease(uvsBuffer);
	SafeRelease(uvsBuffer2);
}

void CSkeletonGeoChunk::destroyBuffers()
{
	Mex2GeoChunk::destroyBuffers();
	SafeRelease(boneWgtIdxBuffer);
}

void CSkeletonGeoChunk::OnDeviceLost()
{
	CMexChunkBase::OnDeviceLost();
	SafeRelease(boneWgtIdxBuffer);
}

void CSkeletonGeoChunk::_WriteDiffuseBuffer(DWORD dwColor, DWORD lockFlag)
{
	m_bChangeColor = true;
}

void CSkeletonGeoChunk::_WriteUVBuffer(DWORD lockFlag)
{
	void* uvbuf = 0;
	if (SUCCEEDED(GetUvsBuffer()->Lock(0, 0, &uvbuf, D3DLOCK_DISCARD)))
	{
		memcpy(uvbuf, GetWorldUvs(), GetVertexCount()*sizeof(Vector2));
		GetUvsBuffer()->Unlock();
	}
}

void CSkeletonGeoChunk::_DoRender( const RenderParams* params )
{
	MeScopeProfileMexGeoChunkFun
	// 设置灯光 [11/11/2010 zhangjiayi]
	D3DXCOLOR kOldAmbient, kOldDiffuse;
	if( params->m_bDiffAmbChanged )
	{
		kOldAmbient = ((RendererDx*)GetEngine()->GetRenderer())->GetLightAmbient(LIGHT_INDEX_TERRAIN );
		kOldDiffuse = ((RendererDx*)GetEngine()->GetRenderer())->GetLightDiffuse(LIGHT_INDEX_TERRAIN );
		((RendererDx*)GetEngine()->GetRenderer())->SetLightAmbient(LIGHT_INDEX_TERRAIN, params->m_kAmbient );
		((RendererDx*)GetEngine()->GetRenderer())->SetLightDiffuse(LIGHT_INDEX_TERRAIN, params->m_kDiffuse );
		if( kOldAmbient != params->m_kAmbient ||
			kOldDiffuse != params->m_kDiffuse )
			GetEngine()->GetRenderer()->LightEnable(LIGHT_INDEX_TERRAIN,TRUE);
	}	

	MeMatrix* matWorld = (MeMatrix*)params->pMatrices;
	std::map<int, int>::iterator it = m_matrixIdxByBoneIdx.begin();
	std::map<int, int>::iterator end = m_matrixIdxByBoneIdx.end();
	for ( ; it != end; ++it)
	{
		memcpy((D3DXMATRIXA16*)&m_boneWorldMatrix[it->second], &matWorld[it->first].m,sizeof(D3DXMATRIXA16));
	}

	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;
	MeSkeletonRenderObject* pkFinal = dynamic_cast< MeSkeletonRenderObject* >( pkObject );

	pkFinal->SetBoneWorldMatrix( m_boneWorldMatrix );
	m_spRenderObject->DoRender();

	if( params->m_bDiffAmbChanged )
	{
		((RendererDx*)GetEngine()->GetRenderer())->SetLightAmbient(LIGHT_INDEX_TERRAIN, kOldAmbient );
		((RendererDx*)GetEngine()->GetRenderer())->SetLightDiffuse(LIGHT_INDEX_TERRAIN, kOldDiffuse );
		if( kOldAmbient != params->m_kAmbient ||
			kOldDiffuse != params->m_kDiffuse )
			GetEngine()->GetRenderer()->LightEnable(LIGHT_INDEX_TERRAIN,TRUE);
	}

}


void CSkeletonGeoChunk::_Render( RenderParams* params )
								
{
	MeScopeProfileMexGeoChunkFun
	//EnterCriticalSection( &gs_BufferCS );
// 	int nPostLast = GetOtherInfos(false).size();
	Mex2GeoChunk::_Render(params);
// 	if (nPostLast == 0 && GetOtherInfos(false).size() == 1)
	{//队列里增加第一个成员
		MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;
		MeSkeletonRenderObject* pkFinal = dynamic_cast< MeSkeletonRenderObject* >( pkObject );
		if( !pkFinal )
			return;
		pkFinal->SetBoneWeightIdxBuff( boneWgtIdxBuffer );
		pkFinal->SetChangeColor( params->dwFlag & eLightingDisable && m_bChangeColor );
		pkFinal->SetOldColor( m_dwOldColor == 0xfffffffe ? 0xffffffff : m_dwOldColor );
		pkFinal->SetBoneWorldMatrix( m_boneWorldMatrix );//bs
		pkFinal->SetBoneMatrixCount( BoneMatrixCount );			
	}

// 	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;
// 	MeSkeletonRenderObject* pkFinal = dynamic_cast< MeSkeletonRenderObject* >( pkObject );
// 	if( !pkFinal )
// 		return;
// 
// 	bool bPost = false;
// 
// 	if( GetCollectibleType() == SortRenderable::eCT_Shimmer )
// 	{
// 		pkFinal->SetAddMapId( MeShimmerCollector::GetFrameTextureId() );
// 		params->dwFlag |= ( eShimmer | eTwoSided );
// 		params->dwFlag &= ~eAlphaBlend;
// 		bPost = true;
// 	}			
// 	else
// 	{
// 		RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
// 		params->fGlobalAlpha = rd->GetGlobalTransparent();
// 		if( IsAlphaChunk(params) /*|| (params->dwFlag & eAlphaBlend)*/)
// 		{
// 			params->dwFlag |= eAlphaBlend;	
// 			SetCollectibleType( SortRenderable::eCT_AlphaBlend );
// 			bPost = true;
// 		}
// 		else
// 		{
// 			params->fGlobalAlpha = 1.0;
// 		}
// 	}
// 
// 	{
// 
// 		if( MeRenderManager::Instance()->IsFreshObject( this ) )			
// 		{
// 			pkFinal->SetUseTexId( params->stUseTexId );		
// 			pkFinal->SetVertexCount( GetVertexCount() );
// 			pkFinal->SetVB( GetVerticesBuffer() );
// 			pkFinal->SetNB( GetNormalsBuffer() );
// 			pkFinal->SetDB( GetDiffusesBuffer() );
// 			pkFinal->SetUVB( GetUvsBuffer() );
// 			pkFinal->SetBoneWeightIdxBuff( boneWgtIdxBuffer );
// 			pkFinal->SetIB( GetIB() );
// 			pkFinal->SetFaceCount( GetFaceCount() );
// 			if (!bPost)
// 			{
// 				pkFinal->SetFlag( params->dwFlag );
// 			}
// 			pkFinal->SetUseLuminanceTexId( params->stUseLuminanceTexId );
// 			pkFinal->SetChangeColor( params->dwFlag & eLightingDisable && m_bChangeColor );
// 			pkFinal->SetOldColor( m_dwOldColor == 0xfffffffe ? 0xffffffff : m_dwOldColor );
// 			pkFinal->SetBoneWorldMatrix( m_boneWorldMatrix );//bs
// 			pkFinal->SetBoneMatrixCount( BoneMatrixCount );			
// 			pkObject->GenerateKey();
// 			MeRenderManager::Instance()->AddObject( this );
// 		}
// 		PushOtherInfo( params, bPost );	
// 		SetCollectibleType( SortRenderable::eCT_Count );	
// 	}

	//LeaveCriticalSection( &gs_BufferCS );
}

void CSkeletonGeoChunk::RenderShadow( IMex* pMex, float* pMatrices, IRenderer* pRenderer, IReplaceableTextureProj* pReplaceableTextureProj, float fAlpha, bool bMustUseAlphaBlend,int nFrameId, DWORD dwFlagEx)
{
	MeScopeProfileMexGeoChunkFun;

	if( !HaveShadow() )
		return;

	if( GetVertexCount() == 0 ||
		GetFaceCount() == 0 )
		return;
	// 地板辅助模型，不渲染
	BOOL bUseNullMtl = FALSE;

	if( pMex == NULL )
		pMex = m_pSrcMex;       

	// 如果是仅受一根骨骼影响,而且此骨骼当前不可见
	if( m_bSingleBoneInfl &&
		m_nSingleBoneId != -1 &&
		!m_pSrcMex->IsBoneVisible( nFrameId, m_nSingleBoneId ) )
	{
		return;
	}

	DWORD dwFlag = dwFlagEx;
	short stUseTexId = -1;
	BOOL bAlphaBlend = TRUE;
	BOOL bAlphaTest = FALSE;
	DWORD dwColor = 0xffffffff;
	DWORD dwBlendMode = MEX2_MODULATE2X;
	//dwBlendMode = MEX2_MODULATE;
	float fu = 0.0f, fv = 0.0f;
	BOOL bTiling = FALSE;
	int nTileFrameId = 0;
	int nUTiles = 1, nVTiles = 1;

	Mex2Material* pMtl = NULL;
	BOOL bHasMtlAnim = FALSE;
	//// 如果有材质
	//////////////////

	if ( GetVertexCount() >= MAX_VERTEX_PER_CHUNK )
	{
		assert( false );
		return;
	}

	// 物体上的特效不受影响
	BOOL bEffect = FALSE;
	if ( bAlphaTest || IsBillboard() )
		return;

// 	if( bAlphaTest )
// 	{
// 		bAlphaBlend = FALSE;
// 		dwFlag |= eAlphaTest;
// 	}
// 
// 	if( bAlphaBlend )
// 	{
// 		//dwFlag |= eTwoSided;
// 		dwFlag |= eAlphaBlend;
// 		dwFlag |= eSortByFarZ;
// 		dwFlag &= (~eLightingDisable);
// 	}

	// 不要贴图
	if( bUseNullMtl )
		stUseTexId = -1;

	if( IsDecal() )
	{
		return;
	}
	//   added 2003.01.15
	// 未注册
	else if( IsBillboard() )
	{
		return;
	}

	//EnterCriticalSection( &gs_BufferCS );

	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
	if( rd->GetGlobalTransparent() < 1.0f )
	{
		dwFlag |= eAlphaBlend;	
// 		if( (dwFlag & eRenderTreeLeaf) && rd->GetGlobalTransparent() < 0.5f )
// 			rd->SetGlobalTransparent(0.65f);
	}
// 	MeMatrix* matWorld = (MeMatrix*)pMatrices;
// 
// 	std::map<int, int>::iterator it = m_matrixIdxByBoneIdx.begin();
// 	std::map<int, int>::iterator end = m_matrixIdxByBoneIdx.end();
// 	for ( ; it != end; ++it)
// 	{
// 		memcpy((D3DXMATRIXA16*)&m_boneWorldMatrix[it->second], &matWorld[it->first].m,sizeof(D3DXMATRIXA16));
// 	}

// 	rd->DirectPushSurfaceSkeleton(
// 		-1,
// 		-1,
// 		GetVertexCount(),
// 		verticesBuffer,
// 		normalsBuffer,
// 		diffusesBuffer,
// 		uvsBuffer,
// 		boneWgtIdxBuffer,
// 		m_pIB,
// 		GetFaceCount(),
// 		dwFlag,
// 		-1,
// 		false,
// 		m_dwOldColor,
// 		m_boneWorldMatrix,
// 		BoneMatrixCount);
	RenderParams* params = CRenderParamsMgr::Instance()->RetriveRenderParams();
	if (!params)
	{
		return;
	}
	params->pMex = pMex;
	params->pMatrices = pMatrices;
// 	params->pRenderer = pRenderer;
	params->pReplaceableTextureProj = pReplaceableTextureProj;
	params->fAlpha = fAlpha;
	params->fGlobalAlpha = 1.f;
	params->nFrameId = nFrameId;
	params->dwFlag = dwFlag;

	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;
	MeSkeletonRenderObject* pkFinal = dynamic_cast< MeSkeletonRenderObject* >( pkObject );
	if( pkFinal )
	{
		if( MeRenderManager::Instance()->IsFreshObject( this ) )			
		{
			pkFinal->SetVertexCount( GetVertexCount() );
			pkFinal->SetVB( GetVerticesBuffer() );
			pkFinal->SetNB( GetNormalsBuffer() );
			pkFinal->SetDB( GetDiffusesBuffer() );
			pkFinal->SetUVB( GetUvsBuffer() );
			pkFinal->SetBoneWeightIdxBuff( boneWgtIdxBuffer );
			pkFinal->SetIB( GetIB() );
			pkFinal->SetFaceCount( GetFaceCount() );
			pkFinal->SetFlag( params->dwFlag );
			pkFinal->SetUseLuminanceTexId( -1 );
			pkFinal->SetChangeColor( false );
			pkFinal->SetOldColor( m_dwOldColor );
			pkFinal->SetBoneMatrixCount( BoneMatrixCount );
			pkObject->GenerateKey();
			MeRenderManager::Instance()->AddObject( this );
		}
		PushOtherInfo( params );
		
	}

	//LeaveCriticalSection( &gs_BufferCS );
}
void CMexChunkBase::CreateVertexBuffers( DWORD usage, D3DPOOL pool )
{
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	if( !verticesBuffer )
	{
		while(1)
		{
			hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(Vector), usage, 0, pool, &verticesBuffer, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	Vector* pVBPos = NULL;
	while(1)
	{
		hr = verticesBuffer->Lock( 0, 0, (void**)&pVBPos, 0 );
		if( SUCCEEDED(hr) ) break;
	}

	if( !normalsBuffer )
	{
		while(1)
		{
			hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(Vector), usage, 0, pool, &normalsBuffer, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	Vector* pVBNormal = NULL;
	while(1)
	{
		hr = normalsBuffer->Lock( 0, 0, (void**)&pVBNormal, 0 );
		if( SUCCEEDED(hr) ) break;
	}

	if( !diffusesBuffer )
	{
		while(1)
		{
			hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(DWORD), usage, 0, pool, &diffusesBuffer, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	DWORD* pVBDiffuse = NULL;
	while(1)
	{
		hr = diffusesBuffer->Lock( 0, 0, (void**)&pVBDiffuse, 0 );
		if( SUCCEEDED(hr) ) break;
	}

	if( !uvsBuffer )
	{
		while(1)
		{
			hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(Vector2), usage, 0, pool, &uvsBuffer, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	short stUVLayerCnt = GetUVLayerCount();
	if( stUVLayerCnt == 2 && !uvsBuffer2 )
	{
		while( 1 )
		{
			hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(Vector2), usage, 0, pool, &uvsBuffer2, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	float* pVBUV = NULL;
	float* pVBUV2 = NULL;
	while(1)
	{
		hr = uvsBuffer->Lock( 0, 0, (void**)&pVBUV, 0 );
		if( SUCCEEDED(hr) ) break;
	}
	while(uvsBuffer2)
	{
		hr = uvsBuffer2->Lock( 0, 0, (void**)&pVBUV2, 0 );
		if( SUCCEEDED(hr) ) break;
	}

	Vector* pVertices = GetVertices();
	Vector* pNormals = GetNormals();
	Vector2* pUVs = GetUVs();
	Vector2* pUVs2 = GetUVs(1);

	DWORD* pColors = GetDiffuses();

	for( int i = 0; i < GetVertexCount(); i++,  pVertices++, pNormals++, pUVs++ )
	{
		pVBPos->x = pVertices->x;
		pVBPos->y = pVertices->y;
		pVBPos->z = pVertices->z;
		++pVBPos;
		//D3DXVec3Normalize( (D3DXVECTOR3*)pNormals, (D3DXVECTOR3*)pNormals );

		pVBNormal->x = pNormals->x;
		pVBNormal->y = pNormals->y;
		pVBNormal->z = pNormals->z;
		++pVBNormal;
		if (pColors)
			*pVBDiffuse = pColors[i];
		else
			*pVBDiffuse = 0xffffffff;
		++pVBDiffuse;
		*pVBUV++ = pUVs->x;
		*pVBUV++ = pUVs->y;
		if( pUVs2 )
		{
			*pVBUV2++ = pUVs2->x;
			*pVBUV2++ = pUVs2->y;
			pUVs2++;
		}
	}

	while(1)
	{
		hr = verticesBuffer->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
	while(1)
	{
		hr = normalsBuffer->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
	while(1)
	{
		hr = diffusesBuffer->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
	while(1)
	{
		hr = uvsBuffer->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
	while(uvsBuffer2)
	{
		hr = uvsBuffer2->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
}

void CMexChunkBase::TestCreateUVsBuffer( int layer, float offsetu, float offsetv, float uscale, float vscale )
{
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	if( !uvsBuffer )
	{
		while(1)
		{
			hr = pDev->CreateVertexBuffer( GetVertexCount()*sizeof(Vector2), GetD3DUSAGE(), 0, GetD3DPOOL(), &uvsBuffer, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	Vector2* pVBUV = NULL;
	while(1)
	{
		hr = uvsBuffer->Lock( 0, 0, (void**)&pVBUV, 0 );
		if( SUCCEEDED(hr) ) break;
	}

	Vector2* pUVs = GetUVs(layer);
	for( int i = 0; i < GetVertexCount(); i++, pUVs++ )
	{
		pVBUV->x = pUVs->x * uscale + offsetu;
		pVBUV->y = pUVs->y * vscale + offsetv;
		++pVBUV;
	}
	while(1)
	{
		hr = uvsBuffer->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
}

void CMexChunkBase::CreateIndexBuffer()
{
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	short* shIBFace = NULL;
	if( !m_pIB )
	{
		while(1)
		{
			hr = pDev->CreateIndexBuffer( GetFaceCount()*3*sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}

	while(1)
	{
		hr = m_pIB->Lock( 0, 0, (void**)&shIBFace, 0 );
		if( SUCCEEDED(hr) ) break;
	}

	memcpy( shIBFace, GetFaces(), GetFaceCount()*sizeof(short)*3 );

	while(1)
	{
		hr = m_pIB->Unlock();
		if( SUCCEEDED(hr) ) break;
	}
}



Vector& CMexChunkBase::GetNormalPoints( int index ) 
{
	if (m_pNormalPoints)
	{
		return m_pNormalPoints[index];
	}
	else
	{
		static Vector localVector;
		Vector* pVertices = GetVerticesLocked();
		Vector* pNormals = GetNormalsLocked();
		localVector = pVertices[index]+pNormals[index];
		UnlockVertices();
		UnlockNormals();
		return localVector;
	}
}

void CStaticGeoChunk::AfterCreateBuffers()
{
	/*
	 * 2012.6.26 wangshuai
	 * 工具模式下, 不删除Buffer
	 */
	if (!GetMe3dConfig()->m_bToolMode)
	{
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pVertices);
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pNormals);
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pFaces);
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pColors);
		for (int i = 0;i < m_ChunkData->m_shUVLayerCount; ++i)
		{
			MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pUVs[i]);
		}
	}
}

void CCollisionGeoChunk::AfterCreateBuffers()
{
	/*
	 * 2012.6.14 wangshuai
	 * 工具模式下, 不删除Buffer
	 */
	if (!GetMe3dConfig()->m_bToolMode)
	{
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pVertices);
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pNormals);
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pFaces);
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pColors);
	}
}

void CHelperGeoChunk::AfterCreateBuffers()
{
	/*
	* 2012.6.28 wangshuai
	* 工具模式下, 不删除Buffer
	*/
	if (!GetMe3dConfig()->m_bToolMode)
	{
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pVertices);
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pNormals);
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pFaces);
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pColors);
		for (int i = 0;i < m_ChunkData->m_shUVLayerCount; ++i)
		{
			MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pUVs[i]);
		}
	}
}

void CHelperGeoChunk::DoRender( bool bPost /*= false */ )
{
	MeScopeProfileMexGeoChunkFun
	//EnterCriticalSection( &gs_BufferCS );

	MeRenderObject* pkObject = ( MeRenderObject* )m_spRenderObject;
	MeModelRenderObject* pkFinal = dynamic_cast< MeModelRenderObject* >( pkObject );
	if( !pkFinal )
		return;

	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
	if( m_spRenderObject->BeginRender() )
	{
		for( RenderParams::OtherInfosConstIter otherit = GetOtherInfos( bPost ).begin(); 
			otherit != GetOtherInfos( bPost ).end() ; ++ otherit )
		{	
			const RenderParams* params = (*otherit );

			rd->SetLightDiffuse(LIGHT_INDEX_COLLISION, diffuse);

			{
				rd->SetTransform( D3DTS_WORLD, &params->pMatrices[m_nSingleBoneId] );

				m_spRenderObject->DoRender();

			}		
		}
		m_spRenderObject->EndRender();
	}
	ClearOtherInfo( bPost );

	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	rd->SetTransform( D3DTS_WORLD, (float*)&world );


	//LeaveCriticalSection( &gs_BufferCS );
}

void CNoShadowGeoChunk::AfterCreateBuffers()
{
	/*
	* 2012.6.26 wangshuai
	* 工具模式下, 不删除Buffer
	*/
	if (!GetMe3dConfig()->m_bToolMode)  //lyh修改透明不产生阴影
	{
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pVertices);
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pNormals);
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pFaces);
		MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pColors);
		for (int i = 0;i < m_ChunkData->m_shUVLayerCount; ++i)
		{
			MEX2_SAFE_DELETE_ARRAY(m_ChunkData->m_pUVs[i]);
		}
	}
}

void CNoShadowGeoChunk::_DoRender( const RenderParams* params )
{
	MeScopeProfileMexGeoChunkFun
	GetEngine()->GetRenderer()->SetTransform( D3DTS_WORLD, &params->pMatrices[m_nSingleBoneId] );

	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
	static D3DLIGHT9 oldLight;
	rd->GetLight(LIGHT_INDEX_TERRAIN,&oldLight);
	m_spRenderObject->DoRender();		
	if (params->m_bIsRenderModelSelected)
	{
		((RendererDx*)rd)->SetLight(LIGHT_INDEX_TERRAIN, &oldLight);
	}

	
}