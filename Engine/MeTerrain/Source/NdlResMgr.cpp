/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NdlResMgr.cpp
* Create: 	10/06/2006
* Desc:		全局资源管理
* Author:	Yuan Ding
*
* Modify:	TObjectInfo增加光照图数据
* Modify by:Qiu Li, 01/19/2010
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "Me3d/Model/Mex2.h"

#include "Me3d/Utility.h"
#include "tstring.h"
#include "MeTerrain/Lighting/StaticMeshInstance.h"
WORD*		CResMgr::m_liquidIndexStream = NULL;
WORD*		CResMgr::m_IndexStream[LODLEVEL] = {
	NULL
};
int			CResMgr::m_LODFaceCount[LODLEVEL] =
{
	8*8*4,
	4*4*4,
	2*2*4,
	4*4*4 + 8*4,
	CHUNK_LOD1T02_FACE_NUMBER
};
WORD		CResMgr::m_LOD2IndexConvert[CHUNK_LOD1T02_VERTEX_NUMBER];

// int			CResMgr::m_baseShadowId = RES_INVALID_ID;

LPDIRECT3DINDEXBUFFER9 CResMgr::m_pIB[LODLEVEL] = {0};
extern char g_NullModelPath[];
CSoundPointRes* CResMgr::CreateSoundPointRes()
{
	return MeNew CSoundPointRes;
}

CTransportRes* CResMgr::CreateTransportRes()
{
	return MeNew CTransportRes;
}

CTargetRes* CResMgr::CreateTargetRes()
{
	return MeNew CTargetRes;
}

bool CResMgr::IsNeedClone( CNdlStaticModelRes* pRes,sInt32 nsubIndex )
{
	return pRes->IsNeedClone(nsubIndex);
}

CResMgr::SInOutPos CResMgr::m_IndexToInOut[CHUNK_VERTEX_NUMBER];
static int  s_MASKLAYER = 4;
namespace {
	int IndexMapBuf2(int lodLevel , int y) 
	{
		return ((y+1)/2)*9 + (y/2)*8 ;
	}
	const int c_stripSize2		= CHUNK_VERTEX_NUMBER;
	const int c_stripFaceSize	= c_stripSize2 - 2;
	static WORD s_stripBuf[c_stripSize2];


	template <class T>
	void Stripify2( T *in, T* out ,int lodLevel)	
	{
		int nBase = 1 << ((lodLevel <= 2)?lodLevel: (lodLevel - 2));
// 		int nMaxIndex = 16 / nBase;
		for (int row=0; row < 16; row++) 
		{
			if (row%(nBase*2) != 0)
			{
				continue;
			}
			T *thisrow = &in[IndexMapBuf2(lodLevel,(row))];
			T *nextrow = &in[IndexMapBuf2(lodLevel,(row+1*nBase))];
			T *overrow = &in[IndexMapBuf2(lodLevel,(row+2*nBase))];

			for(int col=0; col< 8; col++) 
			{

				if (col%(nBase) != 0)
				{
					continue;
				}
				if (0 == lodLevel )
				{
					*out++ = overrow[col];
					*out++ = nextrow[col];
					*out++ = thisrow[col];

					*out++ = nextrow[col];
					*out++ = thisrow[(col + 1)];
					*out++ = thisrow[col];

					*out++ = overrow[(col + 1)];
					*out++ = nextrow[col];
					*out++ = overrow[col];

					*out++ = nextrow[col];
					*out++ = overrow[(col + 1)];
					*out++ = thisrow[(col + 1)];
				}
				else
				{
					*out++ = overrow[col];
					*out++ = nextrow[col+nBase/2 ];
					*out++ = thisrow[col];

					*out++ = nextrow[col+nBase/2];
					*out++ = thisrow[col + nBase];
					*out++ = thisrow[col];

					*out++ = overrow[col + nBase];
					*out++ = nextrow[col+nBase/2];
					*out++ = overrow[col];

					*out++ = nextrow[col+nBase/2];
					*out++ = overrow[col + nBase];
					*out++ = thisrow[col + nBase];

					if (lodLevel > 2)
					{//过度chunk加三角型防止破面
						if (0 == col )
						{
							*out++ = nextrow[col+nBase/2 ];
							*out++ = thisrow[col ];
							*out++ = nextrow[col];

							*out++ = nextrow[col+nBase/2 ];
							*out++ = nextrow[col];
							*out++ = overrow[col ];
						}
						if (0 == row)
						{
							*out++ = nextrow[col+nBase/2 ];
							*out++ = thisrow[col + nBase/2];
							*out++ = thisrow[col];
							*out++ = nextrow[col+nBase/2 ];
							*out++ = thisrow[col + nBase];
							*out++ = thisrow[col + nBase/2];
						}
						if ((16 - 2 * nBase) == row )
						{
							*out++ = overrow[col + nBase/2 ];
							*out++ = nextrow[col + nBase/2 ];
							*out++ = overrow[col];
							*out++ = overrow[col+ nBase/2 ];
							*out++ = overrow[col + nBase];
							*out++ = nextrow[col + nBase/2];
						}
						if ((8 - nBase) == col)
						{
							*out++ = nextrow[col+nBase/2 ];
							*out++ = nextrow[col + nBase];
							*out++ = thisrow[col  + nBase];

							*out++ = nextrow[col+nBase/2 ];
							*out++ = overrow[col  + nBase];
							*out++ = nextrow[col + nBase];
						}
					}
				}
			}
		}
	}

	// 水面.
	int IndexMapBuf3(int col, int row) {
		return row * 9 + col;
	}
	const int c_stripSize3		= 8*9*2 + 7*3;
	const int c_stripFaceSize3	= c_stripSize3 - 2;
	const int c_stripBuf3Size = 9*9;
	static WORD s_stripBuf3[c_stripBuf3Size];

	template <class T>
	void Stripify3( T *in, T *out )	{ 
		for ( int row = 0; row < 8; row++ ) { 
			T *thisrow = &in[IndexMapBuf3(0,row)];
			T *nextrow = &in[IndexMapBuf3(0,row+1)];

			for( int col = 0; col < 8; col++ ) {
				*out++ = thisrow[col];
				*out++ = nextrow[col];
			}
				*out++	= thisrow[8];
				*out++	= nextrow[8];
			if( row < 7 ) {
				*out++	= nextrow[8];
				*out++	= nextrow[0];
				*out++	= nextrow[0];
			}
		}
	}
	
	void TransformBox3D( TBox3D& destBox, const TBox3D& srcBox, flt32 posX, flt32 posY, flt32 posZ )
	{
		destBox.minPt[0]	= srcBox.minPt[0] + posX;
		destBox.minPt[1]	= srcBox.minPt[1] + posY;
		destBox.minPt[2]	= srcBox.minPt[2] + posZ;
		
		destBox.maxPt[0]	= srcBox.maxPt[0] + posX;
		destBox.maxPt[1]	= srcBox.maxPt[1] + posY;
		destBox.maxPt[2]	= srcBox.maxPt[2] + posZ;
	}

	// 精简LOD，边缘无缝隙
}

TObjectInfo::TObjectInfo()
:m_bLightChanged(false)
,m_bCastShadow(true)
,m_ucLightMapScale(LMS_64)
{
	id			= RES_INVALID_ID;
	model		= NULL;
	m_pModelFloor	= NULL;
	m_pCollision	= NULL;
	m_pSupperFloor = NULL;
	m_pCameraCollision	= NULL;
	m_pAlphaBox = NULL;
	m_nCountRef			= 0;
	for( sInt32 i=0; i<3; i++ ) {
		pos[i]		= 0.0f;
		offset[i]	= 0.0f;
		rotate[i]	= 0.0f;
		scale[i]	= 1.0f;
	}
	m_FadeMode = ModelFirstRender;
	m_fAlpha = 1.0f;
	m_fDestAlpha = 1.f;
	m_bToDestBlend = false;
	m_FadeParam = 0.f;
	m_bWasInCullFar = true;
	m_bIsCulled = false;
	m_bIsWujian = false;

	m_bIsOpaque = false;
	m_bIs2_5dColi = false;

	m_isLoad	  = false;
	m_vecStaticMeshInstances.clear();
	m_mapLightColorData.clear();
}

TObjectInfo::~TObjectInfo()
{
	id			= RES_INVALID_ID;
	UnLoadModel();
	DestroyStaticMeshInstances();
}


bool TObjectInfo::LoadFromFile(const char* pszFile)
{
	if( m_isLoad )
		return true;

	MexResMgr::Record* pRecord = GetMexResMgr()->CreateModel(pszFile);
	if (pRecord->res.pMex)
	{
		m_isLoad = true;
	}
	else
	{
		pRecord = GetMexResMgr()->CreateModel(g_NullModelPath);
	}

// 	// 加载IMex模型
// 	IMex* pMex = GetEngine()->CreateMex();
// 	MexCfg* pMexCfg = MeNew MexCfg;
// 
// 	DWORD dwFlag = 0;
// 	if( GetMe3dConfig()->m_bFastLoadMex )
// 		dwFlag |= eMex_LoadFlag_FastLoad;
// 	m_isLoad = pMex->LoadFromFile( pszFile, dwFlag );
// 
// 	if( !m_isLoad )
// 	{
// 		pMex->Release();
// 		delete pMex;
// 		if( pMexCfg )
// 		{
// 			delete pMexCfg;
// 		}
// 		return m_isLoad;
// 	}
 	model = MeNew MexAnimCtrl;
// 
// 	IMexGeometry* pGeomtry = pMex->GetGeometry();
// 	IMexTextures* pTextures = pMex->GetTextures();
// 
// 	MexCfgAvatarSetting* pSetting = pMexCfg->m_AvatarSettings.FindByName( DEFAULT_AVATARSETTING_NAME );
// 	if( pGeomtry )
// 	{
// 		DWORD dwFlag = eMexCfg_SubsetVisible;
// 		for( int nSubset = 0; nSubset < pGeomtry->GetChunkCount(); nSubset++  )
// 		{
// 			pSetting->m_vectorSubsetFlag.push_back( dwFlag );	
// 		}
// 	}
// 	if( pTextures )
// 	{
// 		for( int nTexture = 0; nTexture < pTextures->GetTextureCount(); nTexture++ )
// 		{
// 			MexCfgAvatarSetting::ReplaceableTexture rt;
// 			strcpy( rt.szFileName, pTextures->GetTexture(nTexture)->GetName() );
// 			pSetting->m_vectorReplaceableTexture.push_back( rt );
// 		}
// 
// 	}
// 
//     char s[MAX_PATH]  = {0};
//     Common::_tstring strAniFileName( pszFile );
//     strAniFileName = strAniFileName.MakeLower();
//     strAniFileName.Replace( Common::_tstring( ".mex" ), Common::_tstring( ".ani" ) );
//     if( !pMexCfg->LoadFromFile( strAniFileName.c_str() ) )
//     {
//         MexCfgSequence* sequence = MeNew MexCfgSequence;
//         sequence->m_spAnimName.SetString( "none" );
//         sequence->m_npStartFrameId.SetNumber( pMex->GetSequence()->GetStartFrameID() );
//         sequence->m_npEndFrameId.SetNumber( pMex->GetSequence()->GetEndFrameID() );
//         sequence->m_npHasLightTrack.SetNumber( 1 );
//         pMexCfg->m_sequences.m_vectorSequence.push_back( sequence );
//     }


//     model->PlayAnimByName("Idle",0);

	// 加载完毕
	model->ChangeModel(pRecord->nId, TRUE);
	GetMexResMgr()->DestroyModel(pRecord->nId);
	model->MirrorX( 0 );

	// TODO: 创建StaticMeshInstance

	return true;
}
TObjectInfo* TObjectInfo::Clone()
{
	if( !model )
	{
		assert( false );
		return 0;
	}
	if( !model->GetMex() )
	{
		assert( false );
		return 0;
	}
	TObjectInfo* pCloned = MeNew TObjectInfo();
	
// 	DWORD dwFlag = 0;
	pCloned->model = MeNew MexAnimCtrl;
	if( pCloned->model->Clone(model, TRUE) )
		return pCloned;
	else
		return NULL;

	//IMex* pCloneMex = model->GetMex()->Clone( dwFlag );
	//if( !pCloneMex )
	//	return 0;
	//pCloned->model->ChangeModel( pCloneMex, model->GetMexCfg(), TRUE );
	////pCloned->model->MirrorX(TRUE);

	return pCloned;
}

bool TObjectInfo::UpdateRenderCounter(uInt32 curRenderCounter)
{
	if( renderCounter != curRenderCounter )
	{
		renderCounter = curRenderCounter;
		return true;
	}
	else
		return false;
}

float TObjectInfo::GetModelScale()
{
	if( model )
	{
		return model->GetScale();
	}
	return 0.f;
}

void TObjectInfo::IncreaseRef(CResMgr* pResMgr)
{
	if (NULL == pResMgr)
	{
		return;
	}
	++m_nCountRef;
	if (m_nCountRef > 0 && !m_isLoad)
	{
		assert(model == NULL);
		pResMgr->GenerateObjInfo(this);
	}
}

void TObjectInfo::DecreaseRef( CResMgr* pResMgr )
{
	if (NULL == pResMgr)
	{
		return;
	}
	--m_nCountRef;
	if (m_nCountRef == 0 && m_isLoad)
	{
		CWorldRes* p = pResMgr->GetStaticModelRefList()[id];
		p->DecRefCount();
		CNdlGlobalResMgr* pGlobal = SwGlobal::GetWorld()->GetWorldBuffer()->GetGlobalResMgr();
		CNdlStaticModelRes* pRes	= dynamic_cast<CNdlStaticModelRes*>(pGlobal->FindRefStaticModel(p->GetName()));
		if (pRes->GetModel() == model)
		{//is copy
			model = NULL;
			sInt32 childIndex = 0;
#ifdef SUPPORT_CHILD_MODEL
			childIndex = pRes->GetChildIndex(childModelName);
#endif//SUPPORT_CHILD_MODEL
			pRes->MarkClone(childIndex,false);
		}
		else
		{
			SAFE_DESTROY_AND_DELETE(model);
		}
		pGlobal->UnloadRefModel(p->GetName());

		CleanDspTree();
		m_isLoad = false;
	}

}

void TObjectInfo::UnLoadModel()
{
	SAFE_DESTROY_AND_DELETE(model);
	CleanDspTree();
	m_isLoad = false;
}
void TObjectInfo::CreateFloorAndCollision()
{
	guardfunc;
	CleanDspTree();

	// 设置最小单位，
	float fMinLeafSize = WORLD_TILESIZE*8/2;

	IMex* pMex = model->GetMex();
	if( !pMex || !pMex->GetGeometry())
		return;

	/*
	 * 2012.6.20 wangshuai
	 * 关于摄像机碰撞Bsp创建的规则
	 * 如果根节点(骨骼)的命名以opaque.xxx开始的, 不创建 摄像机碰撞Bsp(和相机碰撞时不透明)
	 */
	IMexBone *rootBone = pMex->GetSkeleton()->GetBone(0);
	char szRootBoneName[MAX_PATH] = {0};
	strcpy(szRootBoneName, rootBone->GetName());
	strlwr(szRootBoneName);

	if (strstr(szRootBoneName, "opaque.") != NULL)
		m_bIsOpaque = true;
	else
		m_bIsOpaque = false;

	/*
	 * Author: 2012-10-26 14:06:48 wangshuai
	 * Desc:   如果根节点的命名是以2.5dcoli.开始的, 在2.5d模式下参与相机碰撞
	 */
	if (strstr(szRootBoneName, "2.5dcoli.") != NULL)
		m_bIs2_5dColi = true;
	else
		m_bIs2_5dColi = false;

	MeMatrix* pMatrices = model->GetMatrices();
	int maxVertexCount = 0;
	static std::vector<Vector> vertices;
	// 统计子模型中，顶点数最大值
	for( int nChunk = 0; nChunk < pMex->GetGeometry()->GetChunkCount(); nChunk++ )
	{
		IRenderable* pChunk = pMex->GetGeometry()->GetChunk(nChunk);
		if (maxVertexCount < pChunk->GetVertexCount())
			maxVertexCount = pChunk->GetVertexCount();
	}
	vertices.resize(maxVertexCount);

	static MeMatrix group[MexAnimCtrl::g_MaxBoneNum];//多线程安全，在线程中使用自己的buffer
	for (int nChunk = 0; nChunk < pMex->GetGeometry()->GetChunkCount(); nChunk++)
	{
		Mex2GeoChunk *pChunk = (Mex2GeoChunk*)pMex->GetGeometry()->GetChunk(nChunk);

 		float *vers = (float *) &vertices[0];

		if (pChunk->IsEffect())
			continue;

		short *indices = (short *) pChunk->GetIndicesLocked();
		if (pChunk->GetType() == Mex2GeoChunkProperty::eRFloor)
		{
			pChunk->BlendVertex(vers,NULL, pChunk->GetVertexCount(), pMex, (float*)pMatrices ,group);
			CreateFloorBsp(fMinLeafSize);
			m_pModelFloor->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
			// floor也是collision
			CreateCollisionBsp(fMinLeafSize);
			m_pCollision->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
		}
		else if (pChunk->GetType() == Mex2GeoChunkProperty::eFloor)
		{
			pChunk->BlendVertex(vers,NULL, pChunk->GetVertexCount(), pMex, (float*)pMatrices ,group);

			CreateFloorBsp(fMinLeafSize);
			m_pModelFloor->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );

			// floor也是collision
			CreateCollisionBsp(fMinLeafSize);
			m_pCollision->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );

			if (!m_bIsOpaque)
			{
				CreateCameraBsp(fMinLeafSize);
				m_pCameraCollision->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
			}
		}
		else if (pChunk->GetType() == Mex2GeoChunkProperty::eRCollision)
		{
			pChunk->BlendVertex(vers,NULL, pChunk->GetVertexCount(), pMex, (float*)pMatrices ,group);
			CreateCollisionBsp(fMinLeafSize);
			m_pCollision->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
		}
		else if (pChunk->GetType() == Mex2GeoChunkProperty::eCollision)
		{
			pChunk->BlendVertex(vers,NULL, pChunk->GetVertexCount(), pMex, (float*)pMatrices ,group);
			CreateCollisionBsp(fMinLeafSize);
			m_pCollision->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );

			if (!m_bIsOpaque)
			{
				CreateCameraBsp(fMinLeafSize);
				m_pCameraCollision->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
			}
		}
		else if (pChunk->GetType() == Mex2GeoChunkProperty::eAlphaBox)
		{
			pChunk->BlendVertex(vers,NULL, pChunk->GetVertexCount(), pMex, (float*)pMatrices ,group);
			CreateAlphaBoxBsp(fMinLeafSize);
			m_pAlphaBox->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
		}
		pChunk->UnlockIndices();

// 		char lwrName[MAX_PATH] = {0};
// 		const char* pszName = pChunk->GetName();
// 		strncpy( lwrName, pszName, MAX_PATH );
// 		strlwr(lwrName);
// 		short* indices = (short*)pChunk->GetIndicesLocked();
// 		if (strstr(lwrName, "sfloor") )
// 		{
// 			pChunk->SetSupperFloor();
// 		}
//         else if( strstr(lwrName, "rfloor") )    // 只判断人站立位置，不碰相机
//         {
//         }
//         else if( strstr(lwrName, "floor") )
// 		{
// 		}
// 		else if( strstr(lwrName, "rcoli"))	// 只碰撞人，不碰相机
// 		{
// 			pChunk->BlendVertex( pMex, (float*)pMatrices );
// 			pChunk->SetCollision();
// 			CreateCollisionBsp(fMinLeafSize);
// 			m_pCollision->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
// 		}
// 		else if( strstr(lwrName, "coli") )	// 对人和相机都碰撞
// 		{
// 			pChunk->BlendVertex( pMex, (float*)pMatrices );
// 			pChunk->SetCollision();
// 			CreateCollisionBsp(fMinLeafSize);
// 			m_pCollision->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
// 			CreateCameraBsp(fMinLeafSize);
// 			m_pCameraCollision->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
// 		}
	}

    if( m_pModelFloor )
        m_pModelFloor->CreateTree2();

	if( m_pCollision )
		m_pCollision->CreateTree2();

	if( m_pCameraCollision )
		m_pCameraCollision->CreateTree2();

	if( m_pAlphaBox )
		m_pAlphaBox->CreateTree2();
	return;
	unguard;

}

void TObjectInfo::CreateFloorBsp( float fMinLeafSize )
{
	if (NULL == m_pModelFloor)
	{
		m_pModelFloor = MeNew BspTree;
		m_pModelFloor->SetMinLeafSize( fMinLeafSize );
	}
}
void TObjectInfo::CreateCollisionBsp( float fMinLeafSize )
{
	if (NULL == m_pCollision)
	{
		m_pCollision = MeNew BspTree;
		m_pCollision->SetMinLeafSize( fMinLeafSize );
	}
}

void TObjectInfo::CreateCameraBsp( float fMinLeafSize )
{
	if (NULL == m_pCameraCollision)
	{
		m_pCameraCollision = MeNew BspTree;
		m_pCameraCollision->SetMinLeafSize( fMinLeafSize );
	}
}

void TObjectInfo::CreateAlphaBoxBsp( float fMinLeafSize )
{
	if (NULL == m_pAlphaBox)
	{
		m_pAlphaBox = MeNew BspTree;
		m_pAlphaBox->SetMinLeafSize( fMinLeafSize );
	}
}

void TObjectInfo::CleanDspTree()
{
	SAFE_DESTROY_AND_DELETE(m_pModelFloor);
	SAFE_DESTROY_AND_DELETE(m_pCollision);
	SAFE_DESTROY_AND_DELETE(m_pCameraCollision);
	SAFE_DESTROY_AND_DELETE(m_pAlphaBox);
}

void TObjectInfo::Render( float fAlpha, bool bUseLightmap /*= true*/, int* pVertexCount/*=NULL*/, int* pFaceCount/*=NULL*/, int* pSubmodelCount/*=NULL*/ )
{
	if( !FLOAT_EQUAL( m_fAlpha, m_fDestAlpha ) && m_bToDestBlend )
		m_fAlpha += fabs( m_fDestAlpha - m_fAlpha  ) / ( m_fDestAlpha - m_fAlpha ) * 0.05f;

	if( m_bCastShadow && !m_LayerDatas.empty() && bUseLightmap )
		model->Render( m_fAlpha, &m_LayerDatas, pVertexCount, pFaceCount, pSubmodelCount );
	else
		model->Render( m_fAlpha, NULL, pVertexCount, pFaceCount, pSubmodelCount );
}

void TObjectInfo::RenderAABBAndRadius()
{
	GetDrawer()->DrawBox3D(model->GetWorldBBox(), 0xff0000ff);

	const Vector pos = model->GetPosition();
	if (model->GetMexCfg() != NULL)
	{
		GetDrawer()->DrawCircle3D(pos.x, pos.y, pos.z, model->GetMexCfg()->m_BodyRadius.m_npRadius.GetNumber(), 20, 0xffff0000);
	}
}

StaticMeshInstance* TObjectInfo::GetStaticMeshInstanceByChunkId( int chunk )
{
	for( int i=0; i<m_vecStaticMeshInstances.size(); ++i )
	{
		if( m_vecStaticMeshInstances[i]->GetChunkIndex() == chunk )
			return m_vecStaticMeshInstances[i];
	}
	return NULL;
}

void TObjectInfo::CreateStaticMeshInstance(Mex2GeoChunk* pChunk, int chunkid)
{
	StaticMeshInstance* pStaticMeshInstance = MeNew StaticMeshInstance(this, pChunk, (unsigned short)chunkid);
	m_vecStaticMeshInstances.push_back(pStaticMeshInstance);
	m_LayerDatas.insert( std::make_pair( pStaticMeshInstance->GetChunkIndex(), pStaticMeshInstance->GetLayer() ) );
}

void TObjectInfo::CreateStaticMeshInstance( unsigned short ChunkIndex, INT vertexCount, BYTE lightmapIndex, float* UVOffset, float* UVScale )
{
	StaticMeshInstance* pStaticMeshInstance = MeNew StaticMeshInstance(this, ChunkIndex, vertexCount, lightmapIndex, UVOffset, UVScale);
	m_vecStaticMeshInstances.push_back(pStaticMeshInstance);
	m_LayerDatas.insert( std::make_pair( pStaticMeshInstance->GetChunkIndex(), pStaticMeshInstance->GetLayer() ) );
}

void TObjectInfo::DestroyStaticMeshInstances()
{
	for( int i=0; i<m_vecStaticMeshInstances.size(); ++i )
		SAFE_DELETE(m_vecStaticMeshInstances[i]);
	m_vecStaticMeshInstances.clear();
	m_LayerDatas.clear();
}

void TObjectInfo::DestroyStaticMeshInstance(int index)
{
	if( index >= 0 && index < m_vecStaticMeshInstances.size() )
	{
		m_LayerDatas.erase( m_vecStaticMeshInstances[index]->GetChunkIndex() );
		SAFE_DELETE(m_vecStaticMeshInstances[index]);
		m_vecStaticMeshInstances.erase(m_vecStaticMeshInstances.begin() + index);		
	}
}
////////////////////////////////////////////////////////////////////////////////
CResMgr::CResMgr()
{
	m_bindTile			= NULL;
	m_deltaTime			= 0.0f;
	m_worldBuffer		= NULL;

	m_maskList.clear();
	m_shapeList.clear();
	m_transportList.clear();
	m_alphaList.clear();
	m_shadowList.clear();
	m_textureList.clear();
	m_lightList.clear();
	m_fogList.clear();
	m_envResList.clear();
	m_SoundPointList.clear();
	m_staticModelList.clear();
	m_staticModelRefList.clear();
}

CResMgr::~CResMgr()
{
	Unload();
	CleanTransport();
	CleanSoundPoint();
}

bool CResMgr::Create( CWorldBuffer* worldBuffer, CWorldTile* worldTile )
{
	m_worldBuffer	= worldBuffer;

	Assert( NULL != worldTile );
	m_bindTile		= worldTile;

	m_deltaTime		= 0.0f;


	return true;
}

void CResMgr::Unload()
{
	size_t i;
	for( i = 0; i < m_staticModelList.size(); i++ )	
	{
		TObjectInfo* objInfo = m_staticModelList[i];
		SafeDeleteObjInfo(objInfo);
	}
	m_staticModelList.clear();
	for( i = 0; i < m_staticModelRefList.size(); i++ )	{
		CWorldRes* p = m_staticModelRefList[i];
		SAFE_DELETE( p );
	}
	m_staticModelRefList.clear();

	for( i = 0; i < m_doodadRefList.size(); i++ )	{
		CWorldRes* p = m_doodadRefList[i];
// 		m_worldBuffer->m_globalResMgr->UnloadRefDoodad(p->GetName());
		SAFE_DELETE( p );
	}
	m_doodadRefList.clear();
	for( i = 0; i < m_textureList.size(); i++ )	{
		SAFE_DELETE( m_textureList[i] );
	}
	m_textureList.clear();
	FreeAlphaAndShadow();
	for( i = 0; i < m_maskList.size(); i++ ) {
		SAFE_DELETE( m_maskList[i] );
	}
	m_maskList.clear();

	for(int i = 0; i < m_shapeList.size(); ++i) {
		SAFE_DELETE(m_shapeList[i]);
	}
	m_shapeList.clear();

	for( i = 0; i < m_lightList.size(); i++ ) {
		SAFE_DELETE( m_lightList[i] );
	}  
	m_lightList.clear();
	for( i = 0; i < m_fogList.size(); i++ ) {
		SAFE_DELETE( m_fogList[i] );
	}  
	m_fogList.clear();
	for( i=0; i<m_envResList.size(); i++ ) {
		SAFE_DELETE( m_envResList[i] );
	}
	m_envResList.clear();
	for( i=0; i<m_zoneResList.size(); i++ ) {
		SAFE_DELETE( m_zoneResList[i] );
	}
	m_zoneResList.clear();
}

bool CResMgr::ReCreate()
{
	//sInt32 id = 0;
	//const uInt16 vertCount	= 9*9 + 8*8;
	//Vector2* texCoord1	= NiNew Vector2[vertCount];
	//for( sInt32 y=0; y<9; y++ )	{
	//	for( sInt32 x=0;x<9;x++ ) {
	//		Assert( id < vertCount );
	//		texCoord1[id].x	= x/8.0f;
	//		texCoord1[id].y	= y/8.0f;
	//		id++;
	//	}
	//	if( y < 8 ) {
	//		for( sInt32 x=0;x<8;x++ ) {
	//			texCoord1[id].x	= x/8.0f+0.0625f;
	//			texCoord1[id].y	= y/8.0f+0.0625f;
	//			id++;
	//		}
	//	}
	//}
	//NDL_SAFE_DELETE_ARRAY( texCoord1 );
	//if( !m_bindTile->m_isLoad )
	//	return false;
	if(m_bindTile)
	{
		for( sInt32 i=0; i<(m_bindTile->GetChunkTotal()); i++ ) {
			CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
			UpdateChunkMask( worldChunk );
		}	 
	}
	
	//for( size_t i = 0; i < m_maskList.size(); i++ ) {
		// UpdateMaskTexture( i );
	//}
	
	return true;
}

//-----------------------------------------------------------------------------------------
void CResMgr::OnDeviceLost()
{
// 	DestoryAllVertexBuffer();
	ReleaseStaticIndexBuffer();
/*for( size_t i = 0; i < m_maskList.size(); ++i )
	{
	CNdlMaskRes* pkRes = dynamic_cast<CNdlMaskRes*>( m_maskList[i]);
	if( pkRes != NULL)
	pkRes->m_texture = NULL;

	}*/
}

//-----------------------------------------------------------------------------------------
void CResMgr::OnDeviceReset(bool bBeforeReset)
{
	if( bBeforeReset )
		return;

	FillStaticIndexBuffer();
// 	FillAllVertexBuffer();
// 	for( sInt32 i=0; i<(m_bindTile->GetChunkTotal()); i++ ) {
// 		CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
// 
// 		if( worldChunk->m_layerCount != 0 &&  RES_INVALID_ID != worldChunk->m_shape)
// 			RefreshAllLayer( worldChunk);
// 	}	 


}


void CResMgr::Update( flt32 totalTime, flt32 deltaTime )
{
	m_deltaTime += deltaTime;
	if( m_deltaTime > 0.05f ) {
		
		m_deltaTime = 0.0f;
	}
}

TObjectInfo* CResMgr::GetStaticModel( sInt32 id )
{
	if( (id < 0) || (id >= m_staticModelList.size()) ) {
		return NULL;
	}
	return ((TObjectInfo*)m_staticModelList[id]);
}

sInt32 CResMgr::Texture( sInt32 id )
{
	if( (id < 0) || (id >= m_textureList.size()) ) {
		return -1;
	}
	return ((CNdlTextureRes*)m_textureList[id])->m_texture;
}
CNdlTextureRes* CResMgr::GetTexture( sInt32 id )
{
	Assert( id >= 0 && id < m_textureList.size() );

	CNdlTextureRes* res = (CNdlTextureRes*)m_textureList[id];
	Assert( res->GetId() == id );
	return res;
}

ITexture* CResMgr::Mask( sInt32 id )
{
	if( (id < 0) || (id >= m_maskList.size()) ) {
		return NULL;
	}
	return ((CNdlMaskRes*)m_maskList[id])->m_texture;
}

CNdlShapeRes* CResMgr::Shape( sInt32 id )
{
	if (id >= 0 && id < m_shapeList.size())
		return (CNdlShapeRes *) m_shapeList[id];
	else
		return NULL;
}

bool CResMgr::ReFillShape( CWorldChunk* chunk )
{
	return true;
}

sInt32 CResMgr::PushStaticModel( sInt32 refModelId, const flt32* pos, const flt32* offset, const flt32* rotate, const flt32* scale,
								TWTDObjLightmapInfo* plmInfo /*= NULL*/, TWTDObjInstance* pInss /*= NULL*/, TWTDObjLightmapColorData* pColorData /*= NULL*/ )
{
	if( refModelId <0 || refModelId >= m_staticModelRefList.size() )
		return RES_INVALID_ID;

	Assert( m_staticModelRefList[refModelId]->GetId() == refModelId );
	TObjectInfo* objInfo	= MeNew TObjectInfo;
	Assert( NULL != objInfo );
	objInfo->id				= refModelId;
	memcpy( objInfo->pos, pos, sizeof(flt32)*3 );
	memcpy( objInfo->offset, offset, sizeof(flt32)*3 );
	memcpy( objInfo->rotate, rotate, sizeof(flt32)*3 );
	memcpy( objInfo->scale, scale, sizeof(flt32)*3 );

	if( plmInfo )
	{
		objInfo->SetCastShadow(plmInfo->bCastShadow);
		objInfo->SetLightMapScale((TObjectInfo::ELightMapScale)plmInfo->ucLightMapScale);
		objInfo->DestroyStaticMeshInstances();
		if( pInss && plmInfo->ucInstanceNum > 0 )
		{
			for( int i=0; i<plmInfo->ucInstanceNum; ++i )
			{
				objInfo->CreateStaticMeshInstance(pInss[i].ucChunkIndex,
												  pInss[i].nStaticMeshVertexCount,
												  pInss[i].ucLightMapIndex,
												  pInss[i].LightMapUVOffset,
												  pInss[i].LightMapUVScale);
			}
		}
	}
	if( pColorData )
	{
		objInfo->ClearColorData();
		for( int i=0; i<pColorData->usColorDataCount; ++i )
		{
			objInfo->PushColorData(pColorData->pColorData[i].nGeoChunkIndex, pColorData->pColorData[i].nColorDataIndex);
		}
	}

	m_staticModelList.push_back( objInfo );

	return m_staticModelList.size()-1;
}

sInt32 CResMgr::PushRefStaticModel( const char* modelName ,bool onlyPhysics )
{
	sInt32 id = FindRefStaticModel( modelName );
	if( RES_INVALID_ID != id ) 
	{
		CWorldRes* pkWorldRes	= (m_staticModelRefList[id]);
		Assert( id == pkWorldRes->GetId() );
		//res->RefCount()	= 0;
		return id;
	}

	CWorldRes* pkWorldRes = MeNew CWorldRes();
	Assert( NULL != pkWorldRes );
	pkWorldRes->SetId( m_staticModelRefList.size() );
	Assert( strlen( modelName ) < RES_NAME_LEN );
	pkWorldRes->SetName( modelName );
	pkWorldRes->SetLoad(true);
	m_staticModelRefList.push_back( pkWorldRes );

	char modelRealName[MAX_PATH];
	strcpy(modelRealName, modelName);
#ifdef SUPPORT_CHILD_MODEL
	char *p = strchr(modelRealName, '|');
	if( p )
		*p = 0;
#endif //SUPPORT_CHILD_MODEL

	m_worldBuffer->m_globalResMgr->LoadRefModel(modelRealName);

	return m_staticModelRefList.size()-1;
}

sInt32 CResMgr::FindRefStaticModel( const char* modelName )
{
	for( size_t i = 0; i < m_staticModelRefList.size(); i++ ) {
		CWorldRes* p = (CWorldRes*)m_staticModelRefList[i];
		if( strcmp( p->GetName(), modelName ) == 0 ) {
			Assert( p->GetId() == i );
			return p->GetId();
		}
	}
	return RES_INVALID_ID;
}


CWorldRes* CResMgr::FindTexture( const char* fileName )
{
	for( size_t i = 0; i < m_textureList.size(); ++i ) 
	{
		CWorldRes* pkNdlTextureRes = (m_textureList[i]);
		if( strcmp( pkNdlTextureRes->GetName(), fileName ) == 0 ) 
		{
			return pkNdlTextureRes;
		}
	}
	return NULL;
}

bool CResMgr::_RefillMaskTexture( ITexture* texture, uAlphaBit* data0, uAlphaBit* data1, uAlphaBit* data2, uAlphaBit* shadowData )
{
	const uInt32 uiSize = WORLD_TILE_CHUNK_ATOM_NUM;
	uInt8 r=0xFF,g=0xFF,b=0xFF,a=0xFF;

	static uInt32 temp[WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM];
	sInt32 index = 0;
	for (int j=0; j<uiSize; j++) {
		for (int x=0; x<uiSize; x++) {
			if( NULL != data0 ) {
				r = UINT32HIGHTOUINT8(*data0);
				data0++;
			}
			if( NULL != data1 ) {
				g = UINT32HIGHTOUINT8(*data1 );
				data1++;
			}
			if( NULL != data2 ) {
				b = UINT32HIGHTOUINT8(*data2) ;
				data2++;
			}
			if( NULL != shadowData ) {
				a = UINT32HIGHTOUINT8(*shadowData );
				shadowData++;
			}
			temp[index] = (a<<24) | (r<<16) | (g<<8) | b;
			++index;
		}
	}
	texture->UpdateTexture((BYTE*)temp,uiSize,uiSize,D3DFMT_A8R8G8B8);
	return true;
}

sInt32 CResMgr::PushMask( CWorldChunk* worldChunk )
{
	CNdlMaskRes* res	= NULL;
	{
		res	= MeNew CNdlMaskRes();
		res->SetId( m_maskList.size() );
	}
	m_maskList.push_back( res );
	
	worldChunk->m_maskId = m_maskList.size()-1;
	
	return worldChunk->m_maskId;
}

sInt32 CResMgr::PushAlpha( const uInt8* alpha )
// 应该有两个版本,一个使用 shader 1.4 另外一个使用固定管线.
{
	CNdlAlphaRes* pkNdlAlphaRes	= MeNew CNdlAlphaRes();
	pkNdlAlphaRes->SetId( m_alphaList.size() );
// #if _MSC_VER >= 1400
// 	sprintf_s( pkNdlAlphaRes->m_name, RES_NAME_LEN, "Alpha_%d", pkNdlAlphaRes->GetId() );
// #else
// 	sprintf( pkNdlAlphaRes->m_name, "Alpha_%d", pkNdlAlphaRes->GetId() );
// #endif
	if( NULL != alpha ) 
	{
		memcpy(pkNdlAlphaRes->m_maskData,alpha,WORLD_TILE_CHUNK_ATOM_NUM*32*sizeof(uAlphaBit));
	}
	else
	{
		memset( pkNdlAlphaRes->m_maskData, 0xFF, WORLD_TILE_CHUNK_ATOM_NUM*32*sizeof(uAlphaBit) );
	}

// 	const uInt32 uiSize = WORLD_TILE_CHUNK_ATOM_NUM;
// 
// 	Assert( NULL != pkNdlAlphaRes->m_maskData );
// 	uAlphaBit* maskData = pkNdlAlphaRes->m_maskData;
// 
// 	if( NULL != alpha ) 
// 	{
// 		for (int j = 0; j < uiSize; ++j)
// 		{
// 			for (int x = 0; x < uiSize; ++x)
// 			{
// 				*maskData = UINT8TOUINT32HIGH(*alpha);
// 				maskData++;
// 				alpha++;
// 			}
// 		}
// 	}
// 	else 
// 	{
// 		memset( pkNdlAlphaRes->m_maskData, 0xFF, uiSize*uiSize*sizeof(uAlphaBit) );
// 	}

	m_alphaList.push_back( pkNdlAlphaRes );
	
	return m_alphaList.size()-1;
}

sInt32 CResMgr::PushShadow( const uInt8* shadowMap )
{
	CNdlAlphaRes* res	= MeNew CNdlAlphaRes();
	res->m_id			= m_shadowList.size();
// #if _MSC_VER >= 1400
// 	sprintf_s( res->m_name, RES_NAME_LEN, "Shadow_%d", res->GetId() );
// #else
// 	sprintf( res->m_name, "Shadow_%d", res->GetId() );
// #endif
	if( NULL != shadowMap ) 
	{
		memcpy(res->m_maskData,shadowMap,WORLD_TILE_CHUNK_ATOM_NUM*32*sizeof(uAlphaBit));
	}
	else
	{
		memset( res->m_maskData, 0xFF, WORLD_TILE_CHUNK_ATOM_NUM*32*sizeof(uAlphaBit) );
	}


// 	Assert( NULL != res->m_maskData );
// 	uAlphaBit* maskData = res->m_maskData;
// 	if( NULL != shadowMap ) 
// 	{
// 		for (int j=0; j<WORLD_TILE_CHUNK_ATOM_NUM; j++) 
// 		{
// 			for (int i=0; i<WORLD_TILE_CHUNK_ATOM_NUM; i++) 
// 			{
// 				*maskData = UINT8TOUINT32HIGH(*shadowMap);
// 				maskData++;
// 				shadowMap++;
// 			}
// 		}
// 	}
// 	else {
// 		memset( res->m_maskData, 0xFF, WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM*sizeof(uAlphaBit) );
// 	}
	m_shadowList.push_back( res );
	
	return m_shadowList.size()-1;
}

void CResMgr::_FillShapData( CNdlShapeRes* res , CWorldChunk* worldChunk )
{
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
	if (
		// 			SUCCEEDED(pd3dDevice->CreateVertexBuffer(CHUNK_VERTEX_NUMBER * sizeof(FTerrainVertexSpecial),
		// 			D3DUSAGE_WRITEONLY, FTerrainVertexSpecial::eFVF, D3DPOOL_DEFAULT,
		// 			&m_pVB, 0))		
		// 			|| 
		SUCCEEDED(pd3dDevice->CreateVertexBuffer(CHUNK_VERTEX_NUMBER * sizeof(FTerrainVertexSpecial),
		D3DUSAGE_WRITEONLY, FTerrainVertexSpecial::eFVF, D3DPOOL_MANAGED,
		&res->m_pVB, 0))
		)
	{
		FTerrainVertexSpecial* pDatas = 0;
		if (SUCCEEDED(res->m_pVB->Lock(0, CHUNK_VERTEX_NUMBER * sizeof(FTerrainVertexSpecial), (void**)&pDatas, 0)))
		{
			FillShapeData(pDatas,worldChunk);
			res->m_pVB->Unlock();
		}
	}
}

void CResMgr::FillShapeData( CNdlShapeRes* res , CWorldChunk* worldChunk )
{
	if (!res->m_culled)	
	{
		_FillShapData(res,worldChunk);

	}
// #endif
	PushChunkLiquid( worldChunk, res->GetId(),emLT_Ocean , worldChunk->m_liquidHeight ,worldChunk->m_liquidColor,worldChunk->m_liquidAlphaCoaf);

}
int g_ChunkTextureDefaultOverlap = 3;
void CResMgr::FillShapeData( FTerrainVertexSpecial* terrainVertex,CWorldChunk* worldChunk )
{

	flt32 originX = ((worldChunk->m_chunk[0])*WORLD_CHUNKSIZE+(WORLD_CHUNKSIZE*0.5f)); 
	flt32 originY = ((worldChunk->m_chunk[1])*WORLD_CHUNKSIZE+(WORLD_CHUNKSIZE*0.5f)); 
	const TChunkVertex* outHeight = worldChunk->m_vertexOut;
	const TChunkVertex* inHeight = worldChunk->m_vertexIn;
	sInt32 id		= 0;
	for( sInt32 y=0; y<9; y++ )	
	{
		for( sInt32 x=0;x<9;x++ ) 
		{
			Assert( id < c_stripSize2 );
			FTerrainVertexSpecial& thisVertex = terrainVertex[id];
			sInt32 vId = y*9+x;
			thisVertex.p.x		= originX+m_IndexToInOut[id].x;
			thisVertex.p.y		= originY+m_IndexToInOut[id].y;
			// 左手系
			//thisVertex.p.y		= fTileMaxY - thisVertex.p.y;
			thisVertex.p.z		= outHeight[vId].height;// + zBias;
			thisVertex.n.x	= outHeight[vId].normal[0]/127.0f;
			thisVertex.n.y	= outHeight[vId].normal[1]/127.0f;
			thisVertex.n.z	= outHeight[vId].normal[2]/127.0f;
			NiColor color;
			DWORD alpha = outHeight[vId].niColor >> 24;
			ConvertRGB2NiColor(outHeight[vId].niColor,color);
			thisVertex.color		= D3DXCOLOR(color.r, color.g, color.b, ((float)alpha)/255);
			thisVertex.uv[0].u	= thisVertex.uv[1].u	= thisVertex.uv[2].u	= thisVertex.uv[3].u	= x*g_ChunkTextureDefaultOverlap/8.f;
			thisVertex.uv[0].v	= thisVertex.uv[1].v	= thisVertex.uv[2].v	= thisVertex.uv[3].v	= y*g_ChunkTextureDefaultOverlap/8.f;
			thisVertex.uvShadow.u	= x/8.0f;
			thisVertex.uvShadow.v	= y/8.0f;
			id++;
		}
		if( y < 8 ) {
			for( sInt32 x=0;x<8;x++ ) {
				FTerrainVertexSpecial& thisVertex = terrainVertex[id];
				sInt32 vId = y*8+x;
				thisVertex.p.x		= originX+m_IndexToInOut[id].x;
				thisVertex.p.y		= originY+m_IndexToInOut[id].y;
				// 左手系
				//thisVertex.p.y		= fTileMaxY - thisVertex.p.y;
				thisVertex.p.z		= inHeight[vId].height;//+WORLD_UNITSIZE*0.5f;
				thisVertex.n.x	= inHeight[vId].normal[0]/127.0f;
				thisVertex.n.y	= inHeight[vId].normal[1]/127.0f;
				thisVertex.n.z	= inHeight[vId].normal[2]/127.0f;
				NiColor color;
				DWORD alpha = inHeight[vId].niColor >> 24;
				ConvertRGB2NiColor(inHeight[vId].niColor,color);
				thisVertex.color		= D3DXCOLOR(color.r, color.g, color.b, ((float)alpha)/255);
				thisVertex.uv[0].u	= thisVertex.uv[1].u	= thisVertex.uv[2].u	= thisVertex.uv[3].u	= (x+0.5f)*g_ChunkTextureDefaultOverlap/8.f;
				thisVertex.uv[0].v	= thisVertex.uv[1].v	= thisVertex.uv[2].v	= thisVertex.uv[3].v	= (y+0.5f)*g_ChunkTextureDefaultOverlap/8.f;
				thisVertex.uvShadow.u	= x/8.0f+0.0625f;
				thisVertex.uvShadow.v	= y/8.0f+0.0625f;
				id++;
			}
		}
	}
	CalChunkSpecialUV(worldChunk, terrainVertex);

}

//extern float fTileMaxY;
sInt32 CResMgr::PushChunkShape( CWorldChunk* worldChunk )
{

	//Trace( "=================== Cache chunk shape ===================\n" );
	CNdlShapeRes* res	= MeNew CNdlShapeRes(worldChunk->IsCulled());
	Assert( NULL != res );
	res->SetId( m_shapeList.size() );
#if _MSC_VER >= 1400
	sprintf_s( res->m_name, RES_NAME_LEN, "Shape_%d", res->GetId() );
#else
	sprintf( res->m_name, "Shape_%d", res->GetId() );
#endif
	worldChunk->m_shape		= res->GetId();
	m_shapeList.push_back(res);

	PushMask( worldChunk );
	// 计算BBox，用于可视剪裁
	CalcBBox(res, worldChunk);
	return m_shapeList.size()-1;
}


bool CResMgr::RefreshLiquidHeight(CWorldChunk* worldChunk, flt32 height , COLORREF niColor,float alphaCoaf)
{
// 	CNdlShapeRes* res = (CNdlShapeRes*)m_shapeList[worldChunk->m_shape];
	worldChunk->m_liquidHeight = height;
	worldChunk->m_liquidColor = niColor;
	worldChunk->m_liquidAlphaCoaf = alphaCoaf;
	return PushChunkLiquid(worldChunk,worldChunk->m_shape,emLT_Ocean,height,niColor,alphaCoaf);
}
// TBD:需要更改为 strip 模式,并且删除高于地表的面
bool CResMgr::PushChunkLiquid( CWorldChunk* worldChunk, sInt32 shapeId, sInt32 liquidId, flt32 height, COLORREF niColor,float alphaCoaf)
{
	if (height -	worldChunk->m_height[0]< 0.0001)
	{
		worldChunk->m_liquidId = RES_INVALID_ID;
		return false;
	}
	worldChunk->m_liquidId = liquidId;
	
	CNdlShapeRes* res = Shape(shapeId);
	if (res == NULL)
		return false;
	
	flt32 refHeight = alphaCoaf;   //&& pyj modify 以前是4.0f*alphaCoaf
// 	flt32 minAlpha	= 0.25f;
// 	flt32 maxAlpha	= 0.9f;

	for( sInt32 y=0; y<9; y++ )	
	{
		for( sInt32 x=0;x<9;x++ ) 
		{
			sInt32 vId			= y*9 + x;

			if (res->GetLiquidVertex() == NULL)
				res->CreateLiquidVertex();
			CNdlShapeRes::WaterVertex& thisVertex = res->GetLiquidVertex()[vId];

			thisVertex.p.x		= worldChunk->Origin()[0]+(x-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
			thisVertex.p.y		= worldChunk->Origin()[1]+(y-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
			thisVertex.p.z		= height;
//			normals[vId]		= Vector::UNIT_Z;
			thisVertex.uv.x		= x/8.0f;
			thisVertex.uv.y		= y/8.0f;

			flt32 deltaHeight	= height - worldChunk->m_vertexOut[vId].height;
			if(deltaHeight <= 0.0f) //&& 以前是0.2f pyj
				deltaHeight = 0.f;
			flt32 alpha = abs(deltaHeight / refHeight);
			if(alpha != 0.f)
			{
				alpha = min( alpha, 0.9f );  //&& pyj, 以前是0.1~0.8
				//alpha = max( 0.1f, alpha );  //&& pyj 注释
			}
			//int32 nAlpha = alpha* 255;  //&& pyj 注释, 后面没有用到这个值 
			NiColor color;
			ConvertRGB2NiColor(niColor,color);

			thisVertex.dwColor	= D3DXCOLOR(color.r, color.g, color.b, alpha);//D3DXCOLOR((nAlpha<<24) | (niColor&0x00FFFFFF));
		}
	}

	CalcBBox(res,worldChunk);
	return false;
}

bool CResMgr::IsChunkLiquidExist(CWorldChunk* worldChunk)
{
	CNdlShapeRes *res = Shape(worldChunk->m_shape);
	if (res != NULL && res->GetLiquidVertex() != NULL)
		return true;
	else
		return false;
}

bool CResMgr::RemoveChunkLiquid(CWorldChunk* worldChunk)
{	
	if (!IsChunkLiquidExist(worldChunk))
		return false;

	CNdlShapeRes *res = Shape(worldChunk->m_shape);
	if (res != NULL)
	{
		res->DeleteLiquidVertex();

		worldChunk->m_liquidId = RES_INVALID_ID;
		worldChunk->m_liquidHeight = 0;
		worldChunk->m_liquidColor = RGB(0, 0, 0);
		worldChunk->m_liquidAlphaCoaf = 0.1;

		return true;
	}
	else
	{
		return false;
	}
}

bool CResMgr::CreateBoundBoxShape()
{
	
	return true;
}

bool CResMgr::TextureName( char* name, sInt32 id )
{
	Assert( id >= 0 && id < m_textureList.size() );

	CWorldRes* res = m_textureList[id];
	Assert( res->GetId() == id );

#if _MSC_VER >= 1400
	strcpy_s( name, RES_NAME_LEN, res->GetName() );
#else
	strcpy( name, res->GetName() );
#endif
	return true;
}

sInt32 CResMgr::GetTextureCount() const
{
	return m_textureList.size();
}

sInt32 CResMgr::GetAlphaCount() const
{
	return m_alphaList.size();
}

sInt32 CResMgr::GetShadowCount() const
{
	return m_shadowList.size();
}

sInt32 CResMgr::GetShapeCount() const
{
	return m_shapeList.size();
}
bool CResMgr::UpdateChunkMask( CWorldChunk* worldChunk )
{
	Assert( NULL != worldChunk );
	if (worldChunk->m_maskId == RES_INVALID_ID)
	{
		return false;
	}

	CNdlMaskRes* res	= (CNdlMaskRes*)m_maskList[worldChunk->m_maskId];

	ITexture* texture = res->m_texture;
	Assert( NULL != texture );

	uInt32 *ptr = (uInt32*)texture->GetData();
	if( !ptr )
	{
		//Assert(ptr != NULL);
		return false;
	}

	uAlphaBit layer[3][WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM];
	for( sInt32 i=0; i<(emMSKC_Flight-1); i++ ) 
	{
		memset(layer[i],0xFF,WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM);
		if( RES_INVALID_ID != worldChunk->m_alpha[i] ) 
		{
			CNdlAlphaRes* alphaRes = GetAlpha( worldChunk->m_alpha[i] );
			if (alphaRes)
			{
				SwPublicFunc::GetAlphaData(layer[i],alphaRes->m_maskData);
			}
// 			if (alphaRes)
// 			{
// 				layer[i] =  alphaRes->m_maskData;
// 			}
		}
	}	
	uAlphaBit shadow[WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM];
	memset(shadow,0xFF,WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM);
	if( RES_INVALID_ID != worldChunk->m_shadow ) 
	{
		CNdlAlphaRes* alphaRes = GetShadow( worldChunk->m_shadow );
		if (alphaRes)
		{
			SwPublicFunc::GetAlphaData(shadow,alphaRes->m_maskData);
		}
//         if( alphaRes )
//             shadow =  alphaRes->m_maskData;
//         else
//             shadow = NULL;
	}
	else 
	{
// 		shadow = NULL;
	}
	_RefillMaskTexture( texture, layer[0], layer[1], layer[2], shadow );


	return true;
}

bool CResMgr::ReloadTexture( sInt32 nTexture )
{
	Assert(nTexture < m_textureList.size() && nTexture >= 0);
	CNdlTextureRes* pRes = (CNdlTextureRes*)m_textureList[nTexture];
	ITextureManager* pMgr = GetEngine()->GetTextureManager();
	pMgr->UnRegisterTexture(pRes->m_texture);
	char path[MAX_PATH*2];
#if _MSC_VER >= 1400
	sprintf_s( path, MAX_PATH*2, "%s\\%s", CWorld::GetAppDataCharDir(), pRes->GetName() );
#else
	sprintf( path, "%s\\%s", CWorld::GetAppDataCharDir(), pRes->GetName() );
#endif

	pRes->m_texture = pMgr->RegisterTexture(path,FALSE,FALSE);
	return true;
}

sInt32 CResMgr::PushTexture( const char* fileName )
{
	char lwsPath[ MAX_PATH * 2];
#if _MSC_VER >= 1400
	strcpy_s( lwsPath, fileName );
	_strlwr_s( lwsPath );
#else
	strcpy( lwsPath, fileName );
	_strlwr( lwsPath );
#endif
	CWorldRes* res = FindTexture( lwsPath );
	if( NULL != res )
	{
		return res->GetId();
	}

	CNdlTextureRes* TextureRes = MeNew CNdlTextureRes();
	TextureRes->SetId( m_textureList.size() );
	Assert( strlen( lwsPath ) < RES_NAME_LEN );
	TextureRes->SetName( lwsPath );
// 	TextureRes->IncRefCount();
	m_textureList.push_back( TextureRes );

	return m_textureList.size() - 1;
}

bool CResMgr::ReleaseChunkMask( CWorldChunk* worldChunk )
{
	if( RES_INVALID_ID != worldChunk->m_maskId ) 
	{
		CNdlMaskRes* pMask = (CNdlMaskRes*)m_maskList[worldChunk->m_maskId];
		pMask->ReleaseMask();
	}
	return true;
}

bool CResMgr::RefreshChunkMask( CWorldChunk* worldChunk )
// 层数改变时调用.
{
	if (worldChunk->IsCulled())
	{
		return false;
	}

	Assert( 0 < worldChunk->m_layerCount );

	// Mask
	if( RES_INVALID_ID != worldChunk->m_maskId ) 
	{
		CNdlMaskRes* pMask = (CNdlMaskRes*)m_maskList[worldChunk->m_maskId];
		if (pMask->GetTexture() ==  NULL)
		{
			char cName[256];
			sprintf_s( cName, RES_NAME_LEN, "Mask_%d%d", pMask->GetId(),m_bindTile->GetMapId() );
			const uInt32 uiSize = WORLD_TILE_CHUNK_ATOM_NUM;

			ITextureManager* pMgr = GetEngine()->GetTextureManager();
			pMask->m_texture = pMgr->CreateTexture();
			Assert( NULL != pMask->m_texture );	
			pMask->m_texture->Create(cName,uiSize,uiSize,D3DFMT_A8R8G8B8,NULL,0,D3DPOOL_MANAGED);
		}

		UpdateChunkMask( worldChunk );
	}

	return true;
}

CNdlAlphaRes* CResMgr::GetShadow( sInt32 id )
{
	if( id >= 0 && id < m_shadowList.size() )
	{
		CNdlAlphaRes* res = (CNdlAlphaRes*)m_shadowList[id];
		Assert( res->GetId() == id );
		return res;
	}
	return NULL;

}

CNdlAlphaRes* CResMgr::GetAlpha( sInt32 id )
{
	if( id >= 0 && id < m_alphaList.size() )
	{
		CNdlAlphaRes* res = (CNdlAlphaRes*)m_alphaList[id];
		Assert( res->GetId() == id );
		return res;

	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////

sInt32 CResMgr::FindRefDoodad( const char* fileName )
{
	for( size_t i = 0; i < m_doodadRefList.size(); i++ ) {
		CWorldRes* p = (CWorldRes*)m_doodadRefList[i];
		if( strcmp( p->GetName(), fileName ) == 0 ) {
			Assert( p->GetId() == i );
			return p->GetId();
		}
	}
	return RES_INVALID_ID;
}

sInt32 CResMgr::PushRefDoodad( const char* fileName )
{
	char path[MAX_PATH*2];
#if _MSC_VER >= 1400
	strcpy_s( path, fileName );
	_strlwr_s( path );
#else
	strcpy( path, fileName );
	_strlwr( path );
#endif
	sInt32 id = FindRefDoodad( path );
	if( RES_INVALID_ID != id ) 
	{
		CWorldRes* pkWorldRes	= (m_doodadRefList[id]);
		Assert( id == pkWorldRes->GetId() );
		//res->RefCount()	= 0;
		return id;
	}
	CWorldRes* pkWorldRes = MeNew CWorldRes();
	Assert( NULL != pkWorldRes );
	pkWorldRes->SetId( m_doodadRefList.size() );
	Assert( strlen( path ) < RES_NAME_LEN );
	pkWorldRes->SetName( path );

// 	m_worldBuffer->m_globalResMgr->RetriveRefDoodad(pkWorldRes->GetName());

// 	pkWorldRes->SetLoad(true);
	m_doodadRefList.push_back( pkWorldRes );

	return m_doodadRefList.size()-1;

}

int CResMgr::GetDoodadCount()
{
	return m_doodadRefList.size();
}

CDoodadRes* CResMgr::GetDoodadRes( sInt32 id )
{
	if( (id < 0) || (id >= m_doodadRefList.size()) ) {
		return NULL;
	}
	return m_worldBuffer->m_globalResMgr->RetriveRefDoodad(m_doodadRefList[id]->GetName());

}

CWorldRes* CResMgr::GetDoodad( sInt32 id )
{
	if( (id < 0) || (id >= m_doodadRefList.size()) ) {
		return NULL;
	}
	return m_doodadRefList[id];
}

void CResMgr::IncDoodadRef( sInt32 id )
{
	Assert( refModelId >= 0 && id < m_doodadRefList.size() ) ;
	Assert( m_doodadRefList[id]->GetId() == id );
	if (m_doodadRefList[id]->RefCount() == 0)
	{
		CDoodadRes* pDoodad = GetDoodadRes(id);
		if (pDoodad)
		{
			pDoodad->IncRefCount();
		}
	}
	m_doodadRefList[id]->IncRefCount();
}

void CResMgr::DecDoodadRef( sInt32 id )
{
	Assert( refModelId >= 0 && id < m_doodadRefList.size() ) ;
	Assert( m_doodadRefList[id]->GetId() == id );
	m_doodadRefList[id]->DecRefCount();
	if (m_doodadRefList[id]->RefCount() == 0)
	{
		CDoodadRes* pDoodad = GetDoodadRes(id);
		if (pDoodad)
		{
			pDoodad->DecRefCount();
		}
	}

}

void CResMgr::ApplyTransform( MexAnimCtrl* pObj, const flt32* pos, const flt32* offset, const flt32* rotate, const flt32* scale )
{
	if( !pObj )
		return;

	pObj->SetRotationX( rotate[0]*PI/180.0f );
	pObj->SetRotationY( rotate[1]*PI/180.0f );
	pObj->SetRotationZ( rotate[2]*PI/180.0f );
	pObj->SetPosition( pos[0]+offset[0], pos[1]+offset[1], pos[2]+offset[2] );
	pObj->SetScaleXYZ(scale[0],scale[1],scale[2]);
	// 如果是静态模型，则直接生成世界坐标数据，用于渲染
	/*if( !pObj->IsAni() )*/
	pObj->UpdateTransform();
}

//void CResMgr::ApplyTransform( NiAVObject* pObj, const flt32* pos, const flt32* offset, const flt32* rotate, const flt32* scale )
//{
//	NiMatrix3 matRot;
//	matRot.FromEulerAnglesXYZ( rotate[0]*PI/180.0f, rotate[1]*PI/180.0f, rotate[2]*PI/180.0f );
//	NiMatrix3 matScl = NiMatrix3::IDENTITY;
//
//	NiMatrix3 matTrans = matRot * matScl;
//	flt32 trans[3];
//	trans[0] = pos[0] + offset[0];
//	trans[1] = pos[1] + offset[1];
//	trans[2] = pos[2] + offset[2];
//	pObj->SetRotate( matTrans );
//	pObj->SetScale( scale[0] );
//	pObj->SetTranslate( trans[0], trans[1], trans[2] );
//	pObj->Update(0.0f);
//	pObj->UpdateProperties();
//	pObj->UpdateEffects();
//	pObj->UpdateNodeBound();
//}


bool CResMgr::FindTextureReference( sInt32 textureId )
{
	for( sInt32 i=0; i<(m_bindTile->GetChunkTotal()); i++ ) {
		CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
		for (sInt32 j = 0; j < worldChunk->GetLayerCount(); ++j )
		{
			if (worldChunk->m_texture[j] == textureId)
			{
				return true;
			}
		}
	}	 
	return false;
}

CTransportResBase* CResMgr::Transport( sInt32 id )
{
	if( (id < 0) || (id >= m_transportList.size()) ) {
		return NULL;
	}
	return (CTransportResBase*)m_transportList[id];
}

sInt32 CResMgr::GetTransportCount() const
{
	return m_transportList.size();
}


CTransportResBase* CResMgr::PushTransport( float top,float left,float right,float bottom,sInt32 nIndex)
{
	sInt32 index = 0;
	std::vector< CTransportResBase* >::reverse_iterator ite = m_transportList.rbegin();
	while(ite != m_transportList.rend())
	{
		if ((*ite)->IsTransport())
		{
			CTransportRes* pRes = (CTransportRes*)(*ite);
			index = pRes->GetEntranceId() + 1;
			break;
		}
		++ite;
	}

	CTransportRes* pRes = CreateTransportRes();
	pRes->SetLeft(left);
	pRes->SetRight(right);
	pRes->SetBottom(bottom);
	pRes->SetTop(top);
	pRes->SetNtargetID(nIndex);
	pRes->SetEntranceId(index);
	pRes->SetId(m_transportList.size());
	m_transportList.push_back(pRes);
	return pRes;
}

CTargetRes* CResMgr::GetTarget( sInt32 TargetId )
{
	std::vector< CTransportResBase* >::reverse_iterator ite = m_transportList.rbegin();
	while(ite != m_transportList.rend() )
	{
		if (!(*ite)->IsTransport()&& 
			TargetId == (*ite)->GetNtargetID() && !((CTargetRes*)(*ite))->IsRelive())
		{
			return (CTargetRes*)(*ite);
		}
		++ite;
	}
	return NULL;
}

CTargetRes* CResMgr::GetRelive( sInt32 TargetId )
{
	if (TargetId == -1) { return NULL; }

	std::vector< CTransportResBase* >::reverse_iterator ite = m_transportList.rbegin();
	while(ite != m_transportList.rend() )
	{
		if (!(*ite)->IsTransport())
		{
			CTargetRes* pRes = (CTargetRes*)(*ite);
			if (pRes->GetReliveId() == TargetId)
			{
				return pRes;
			}
		}
		++ite;
	}
	return NULL;
}

//判断是目标点 还是重生点
CTransportResBase* CResMgr::PushTarget( float posX,float posY,float dir, bool bRelive)
{
	sInt32 index = 0;
	std::vector< CTransportResBase* >::reverse_iterator ite = m_transportList.rbegin();
	
	while(ite != m_transportList.rend())
	{
		if (!(*ite)->IsTransport())
		{
			CTargetRes* pTarget = (CTargetRes*)(*ite);
			if(!bRelive && !pTarget->IsRelive())
			{
				index = (*ite)->GetNtargetID() + 1;
				break;
			}
			else if (bRelive && pTarget->IsRelive())
			{
				index = pTarget->GetReliveId() + 1;
				break;
			}			
		}
		++ite;
	}

	CTargetRes* pRes = CreateTargetRes();
	pRes->SetRelive(bRelive);
	pRes->SetPosX(posX);
	pRes->SetPosY(posY);
	pRes->SetTargetDir(dir);
	if (!bRelive)
	{
		pRes->SetNtargetID(index);
	}
	else 
	{ 
		pRes->SetReliveId(index); 
	}
	
	pRes->SetId(m_transportList.size());
	m_transportList.push_back(pRes);
	return pRes;
}




void CResMgr::CleanTransport()
{
	for(size_t i = 0; i < m_transportList.size(); i++ ) {
		SAFE_DELETE( m_transportList[i] );
	}
	m_transportList.clear();
}


sInt32 CResMgr::CreateEnv( const char* name, sInt32 lightId, sInt32 fogId )
{
//	Assert( RES_INVALID_ID != lightId );
//	Assert( RES_INVALID_ID != fogId );

	sInt32 EnvId = FindEnv( name, lightId, fogId );
	if( RES_INVALID_ID != EnvId ) {
		return EnvId;
	}

	CNdlEnvRes* newEnv	= MeNew CNdlEnvRes;
	newEnv->SetName( name );
	newEnv->SetLightId(lightId);
	newEnv->SetFogId(fogId);
	newEnv->SetId(m_envResList.size());
	m_envResList.push_back( newEnv );

	return m_envResList.size() - 1;
}

sInt32 CResMgr::CreateZone( const char* name, const char* musicPath, const RECT* pRect )
{

	sInt32 ZoneId = FindZone( name, musicPath);
	if( RES_INVALID_ID != ZoneId ) {
		return ZoneId;
	}

	CNdlZoneRes* newZone	= MeNew CNdlZoneRes;
	newZone->SetName( name );
	newZone->SetMuiscPath(musicPath);
	newZone->SetId(m_zoneResList.size());
	newZone->SetFontRect(pRect);
	m_zoneResList.push_back( newZone );

	return m_zoneResList.size() - 1;
}

sInt32 CResMgr::FindZone( const char* name, const char* musicPath)
{
	for( size_t i=0; i<m_zoneResList.size(); i++ ) {
		CNdlZoneRes* p = (CNdlZoneRes*)m_zoneResList[i];
		Assert( NULL != p );

		if( 0 == strcmp( name, p->GetName() ) )
		{
			if (musicPath == NULL && p->GetMuiscPath() == NULL)
			{
				return i;
			}
			if(musicPath && p->GetMuiscPath() && 0 == strcmp( musicPath, p->GetMuiscPath() ))
			{
				return i;
			}
		}
	}
	return RES_INVALID_ID;
}

sInt32 CResMgr::FindEnv( const char* name, sInt32 lightId, sInt32 fogId )
{
	for( size_t i=0; i<m_envResList.size(); i++ ) {
		CNdlEnvRes* p = (CNdlEnvRes*)m_envResList[i];
		Assert( NULL != p );

		if( 0 == strcmp( name, p->GetName() ) && lightId == p->GetLightId() && fogId == p->GetFogId() ) {
			return i;
		}
	}
	return RES_INVALID_ID;
}

CNdlEnvRes* CResMgr::GetEnvRes( sInt32 envId )
{
	if( envId < 0 || envId >= m_envResList.size() )
		return NULL;

	return (CNdlEnvRes*)m_envResList[envId];
}
CNdlZoneRes* CResMgr::GetZoneRes( sInt32 zoneId )
{
	if( zoneId < 0 || zoneId >= m_zoneResList.size() )
		return NULL;

	return (CNdlZoneRes*)m_zoneResList[zoneId];
}

CNdlLightRes* CResMgr::GetLightRes( sInt32 lightId )
{
	if( lightId < 0 || lightId >= m_lightList.size() )
		return NULL;

	return (CNdlLightRes*)m_lightList[lightId];

}

CNdlFogRes* CResMgr::GetFogRes( sInt32 fogId )
{
	if( fogId < 0 || fogId >= m_fogList.size() )
		return NULL;

	return (CNdlFogRes*)m_fogList[fogId];
}


void CResMgr::GenerateObjInfo(  TObjectInfo* objInfo, bool bKeepOldData /*= false*/ )
{
	sInt32 refModelId = objInfo->id;
	assert( m_staticModelRefList[refModelId] && "CResMgr::GenerateObjInfo, 引用模型列表指针为空" );
	m_staticModelRefList[refModelId]->IncRefCount();

	const flt32* pos= objInfo->pos;
	const flt32* offset= objInfo->offset;
	const flt32* rotate= objInfo->rotate;
	const flt32* scale= objInfo->scale;

	char modelRealName[MAX_PATH];
	sprintf(modelRealName, m_staticModelRefList[refModelId]->GetName());
#ifdef SUPPORT_CHILD_MODEL
	char *p = strchr(modelRealName, '|');
	char childModelName[MAX_PATH];
	if( p )
	{
		strcpy( childModelName, p+1 );
		*p = 0;
	}
#endif//SUPPORT_CHILD_MODEL
	CNdlStaticModelRes* pRes	= dynamic_cast<CNdlStaticModelRes*>(m_worldBuffer->m_globalResMgr->FindRefStaticModel(modelRealName));
	pRes->IncRefCount(bKeepOldData);
	sInt32 childIndex = 0;
#ifdef SUPPORT_CHILD_MODEL
	if( p )
	{
		childIndex = pRes->GetChildIndex(childModelName);
	}
#endif//SUPPORT_CHILD_MODEL
	bool isNeedClone = IsNeedClone(pRes,childIndex);
	if (!isNeedClone)
	{
		pRes->MarkClone(childIndex,true);
	}
	Assert( NULL != pRes );

	MexAnimCtrl* pModel = NULL;
	if( pRes->GetModel() )
	{
		// Clone资源
		if (isNeedClone)
		{
			pModel = MeNew MexAnimCtrl;
			pModel->Clone( pRes->GetModel(), TRUE );		// 设置标记为保存在chunk里的模型
		}
		else
		{
			pModel = pRes->GetModel();
		}

        if (!pModel->GetMex())
        {
            std::string err("Load Failed : ");
            err += modelRealName;
            err += "\n";
            OutputDebugString(err.c_str());
        }

 		ApplyTransform(pModel, pos, offset, rotate, scale);
		// 判断是否小物件模型
		if( pModel->GetMex() )
		{
			char filename[MAX_PATH];
			strcpy( filename, pModel->GetMex()->GetFilename() );
			strlwr(filename);
			if( strstr(filename, "wujian") || strstr(filename, "ob_wj") )
			{
				objInfo->m_bIsWujian = true;
			}
		}
		objInfo->model = pModel;
		objInfo->CreateFloorAndCollision();
	}
	objInfo->m_isLoad = true;
	if (isNeedClone)
	{
		Trace( "Clone model[%s] \n", m_staticModelRefList[refModelId]->GetName() );
	}
	else
	{
		Trace( "Use global model directly [%s] \n", m_staticModelRefList[refModelId]->GetName() );
	}
}

void CResMgr::CreateStaticStream()
{
	if (m_IndexStream[0] != NULL)
	{
		return;
	}
// 	ITextureManager* pMgr = GetEngine()->GetTextureManager();
// 	m_baseShadowId = 9;
// 	char szName[MAX_PATH] = {0};
// 	sprintf( szName, "shadow_%d_%d_5_%d_%d", 0, 0, 0, 0 );
// 
// 	m_baseShadowId = pMgr->RegisterTerrainAlpha( szName,
// 		WORLD_TILE_CHUNK_UNIT_NUM, WORLD_TILE_CHUNK_UNIT_NUM,
// 		D3DFMT_A8R8G8B8, NULL, 0, D3DPOOL_MANAGED );
// 
// 	uInt32 buffer[WORLD_TILE_CHUNK_UNIT_NUM* WORLD_TILE_CHUNK_UNIT_NUM];
// 	for (int i = 0; i < WORLD_TILE_CHUNK_UNIT_NUM* WORLD_TILE_CHUNK_UNIT_NUM;++i)
// 	{
// 		buffer[i] = 0xff000000;
// 	}
// 	TextureDx8* pTexture = (TextureDx8*)(pMgr->GetTexture( m_baseShadowId ));
// 	pTexture->UpdateTexture((BYTE*)buffer,WORLD_TILE_CHUNK_UNIT_NUM,WORLD_TILE_CHUNK_UNIT_NUM,D3DFMT_A8R8G8B8);

	for (sInt32 j=0; j<c_stripSize2; j++) {
		s_stripBuf[j] = j;
	}

	for (int i = 0; i < LODLEVEL; ++i)
	{
		m_IndexStream[i] = MeDefaultNew WORD[m_LODFaceCount[i]*3];		
		Stripify2<WORD>( s_stripBuf, m_IndexStream[i],i );
	}
	{
		bool   isCheck[CHUNK_VERTEX_NUMBER] = {false};
		for (int i = 0; i < m_LODFaceCount[LOD1to2]*3; ++i)
		{
			WORD index = m_IndexStream[LOD1to2][i]; 
			if (isCheck[index])
			{
				continue;
			}
			int nMinCount = 0;
			bool   isMinCheck[CHUNK_VERTEX_NUMBER] = {false};
			for (int j = 0; j < m_LODFaceCount[LOD1to2]* 3; ++j)
			{
				int cmpValue = m_IndexStream[LOD1to2][j];
				if(isMinCheck[cmpValue])
				{
					continue;
				}
				if (cmpValue < index)
				{
					++nMinCount;
				}
				isMinCheck[cmpValue] = true;
			}
			m_LOD2IndexConvert[nMinCount] = index;
			isCheck[index] = true;
		}
		for (int i = 0; i < CHUNK_LOD1T02_FACE_NUMBER*3; ++i)
		{
			for (int j = 0; j < CHUNK_LOD1T02_VERTEX_NUMBER;++j)
			{
				if (m_IndexStream[LOD1to2][i] == m_LOD2IndexConvert[j])
				{
					m_IndexStream[LOD1to2][i] = j;
					break;
				}
			}
		}
		for (int i = 0; i < m_LODFaceCount[LOD2]*3; ++i)
		{
			for (int j = 0; j < CHUNK_LOD1T02_VERTEX_NUMBER;++j)
			{
				if (m_IndexStream[LOD2][i] == m_LOD2IndexConvert[j])
				{
					m_IndexStream[LOD2][i] = j;
					break;
				}
			}
		}

	}

	FillStaticIndexBuffer();

	m_liquidIndexStream = MeDefaultNew WORD[c_stripSize3];

	for( sInt32 i = 0; i < c_stripBuf3Size; i++) 
	{
		s_stripBuf3[i] = i;
	}
	Stripify3<WORD>( s_stripBuf3, m_liquidIndexStream );
	
	
	//m_IndexToInOut
	sInt32 id		= 0;
	for( sInt32 y=0; y<9; y++ )	
	{
		for( sInt32 x=0;x<9;x++ ) 
		{
			sInt32 vId = y*9+x;
			m_IndexToInOut[id].x = (x-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
			m_IndexToInOut[id].y = (y-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
			m_IndexToInOut[id].inOutIndex = vId;
			m_IndexToInOut[id].bIn = false;
			id++;
		}
		if( y < 8 ) 
		{
			for( sInt32 x=0;x<8;x++ ) 
			{
				sInt32 vId = y*8+x;
				m_IndexToInOut[id].x = (x-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE+WORLD_UNITSIZE*0.5f;
				m_IndexToInOut[id].y = (y-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE+WORLD_UNITSIZE*0.5f;
				m_IndexToInOut[id].inOutIndex = vId;
				m_IndexToInOut[id].bIn = true;
				id++;
			}
		}
	}
}

void CResMgr::DestoryStaticStream()
{

	for (int i = 0; i  < LODLEVEL; ++i)
	{
		delete []		m_IndexStream[i] ;

		SafeRelease(m_pIB[i]);
	}
	delete []		m_liquidIndexStream ;

}

bool CResMgr::SetLODLevelPrivate(CWorldChunk* worldChunk, sInt32 nlevel )
{
	if (nlevel >= LODLEVEL || NULL == worldChunk)
	{
		return false;
	}
	if (worldChunk->GetLODLevel() == nlevel)
	{
		return true;
	}
	worldChunk->SetLODLevel(nlevel);
	return true;
}



void CResMgr::DeleteSoundPoint( sInt32 id )
{
	for (sInt32 i = id + 1; i < m_SoundPointList.size(); ++i)
	{
		CSoundPointRes* pRes = SoundPoint(i);
		pRes->SetId(pRes->GetId() - 1);
	}
	SAFE_DELETE( m_SoundPointList[id] );
	m_SoundPointList.erase(m_SoundPointList.begin() + id);

}
CSoundPointRes* CResMgr::SoundPoint( sInt32 id )
{
	if( (id < 0) || (id >= m_SoundPointList.size()) ) {
		return NULL;
	}
	return (CSoundPointRes*)m_SoundPointList[id];
}

void CResMgr::CleanSoundPoint()
{
	for(size_t i = 0; i < m_SoundPointList.size(); i++ ) {
		SAFE_DELETE( m_SoundPointList[i] );
	}
	m_SoundPointList.clear();

}
sInt32 CResMgr::GetSoundPointCount() const
{
	return m_SoundPointList.size();
}


CSoundPointRes* CResMgr::PushSoundPoint(const char* pName)
{
	CSoundPointRes* pRes = CreateSoundPointRes();
	if (pName)
	{
		pRes->SetName(pName);
	}
	pRes->SetId(m_SoundPointList.size());
	m_SoundPointList.push_back(pRes);
	return pRes;
}




bool CResMgr::RefreshNeighborLODLevel( CWorldChunk* worldChunk,int oldLevel,int newLevel )
{
	Assert(worldChunk);
	CWorldChunk* pNeighbor = m_bindTile->GetChunk(worldChunk->m_chunk[0] - 1,worldChunk->m_chunk[1]);
	if (pNeighbor && pNeighbor->GetLODLevel() == oldLevel)
	{
		SetLODLevelPrivate(pNeighbor,newLevel);
	}
	pNeighbor = m_bindTile->GetChunk(worldChunk->m_chunk[0] + 1,worldChunk->m_chunk[1]);
	if (pNeighbor && pNeighbor->GetLODLevel() == oldLevel)
	{
		SetLODLevelPrivate(pNeighbor,newLevel);
	}
	pNeighbor = m_bindTile->GetChunk(worldChunk->m_chunk[0] ,worldChunk->m_chunk[1]+ 1);
	if (pNeighbor && pNeighbor->GetLODLevel() == oldLevel)
	{
		SetLODLevelPrivate(pNeighbor,newLevel);
	}
	pNeighbor = m_bindTile->GetChunk(worldChunk->m_chunk[0] ,worldChunk->m_chunk[1] - 1);
	if (pNeighbor && pNeighbor->GetLODLevel() == oldLevel)
	{
		SetLODLevelPrivate(pNeighbor,newLevel);
	}
	return true;

}
bool CResMgr::SetLODLevel( CWorldChunk* worldChunk,sInt32 nlevel )
{
	int nCurrLod = worldChunk->GetLODLevel();
	switch (nlevel)
	{
	case 0:
// 		if (3 == nCurrLod)
// 		{
// 			SetLODLevelPrivate(worldChunk,0);
// 		}
// 		if (IsHigherLODNeighbor(worldChunk,1))
// 		{
// 			SetLODLevelPrivate(worldChunk,3);
// 		}
// 		else
		{
			SetLODLevelPrivate(worldChunk,0);
			RefreshNeighborLODLevel(worldChunk,1,3);
		}
		break;
	case 1:
		if (0 == nCurrLod )
		{
			SetLODLevelPrivate(worldChunk,3);
		}
		else 
		{
			if (3 == nCurrLod)
			{
				if (!IsHigherLODNeighbor(worldChunk,0))
				{
					SetLODLevelPrivate(worldChunk,1);
				}
			}
			else
			{
				SetLODLevelPrivate(worldChunk,1);
				RefreshNeighborLODLevel(worldChunk,2,4);
			}
		}
// 		else if (IsHigherLODNeighbor(worldChunk,0))
// 		{
// 			SetLODLevelPrivate(worldChunk,3);
// 		}
// 		else
// 		{
// 			SetLODLevelPrivate(worldChunk,1);
// 		}
		break;
	case 2:
		if (1 == nCurrLod )
		{
			SetLODLevelPrivate(worldChunk,4);
		}
		else 
		{
			if (4 == nCurrLod)
			{
				if (!IsHigherLODNeighbor(worldChunk,1))
				{
					SetLODLevelPrivate(worldChunk,2);
				}
			}
			else if (2 == nCurrLod)
				{
					if (IsHigherLODNeighbor(worldChunk,1) || IsHigherLODNeighbor(worldChunk,3))
					{
						SetLODLevelPrivate(worldChunk,4);
					}

				}
			else
			{
				SetLODLevelPrivate(worldChunk,2);

			}
		}
// 		if (IsHigherLODNeighbor(worldChunk,1) )//|| IsHigherLODNeighbor(worldChunk,3))
// 		{
// 			SetLODLevelPrivate(worldChunk,4);
// 		}
// 		else
// 		{
// 			SetLODLevelPrivate(worldChunk,2);
// 		}
		break;
	}
	return true;
}

bool CResMgr::IsHigherLODNeighbor(CWorldChunk* worldChunk,sInt32 nlevel)
{
	Assert(worldChunk);
	CWorldChunk* pNeighbor = m_bindTile->GetChunk(worldChunk->m_chunk[0] - 1,worldChunk->m_chunk[1]);
	if (pNeighbor && pNeighbor->GetLODLevel() == nlevel)
	{
		return true;
	}
	pNeighbor = m_bindTile->GetChunk(worldChunk->m_chunk[0] + 1,worldChunk->m_chunk[1]);
	if (pNeighbor && pNeighbor->GetLODLevel() == nlevel)
	{
		return true;
	}
	pNeighbor = m_bindTile->GetChunk(worldChunk->m_chunk[0] ,worldChunk->m_chunk[1]+ 1);
	if (pNeighbor && pNeighbor->GetLODLevel() == nlevel)
	{
		return true;
	}
	pNeighbor = m_bindTile->GetChunk(worldChunk->m_chunk[0] ,worldChunk->m_chunk[1] - 1);
	if (pNeighbor && pNeighbor->GetLODLevel() == nlevel)
	{
		return true;
	}
	return false;
}



void CResMgr::CalSpecialTEXCOORD( CWorldChunk* worldChunk,int index, FTerrainVertexSpecial terrainVertex[] )
{
// 	CNdlShapeRes * shape = Shape(worldChunk->m_shape);
	FTerrainVertexSpecial *kTexCoord = terrainVertex;
	TTextureInfo* info = &worldChunk->m_texInfo[index];
	sInt32 chunkX = 0;
	sInt32 chunkY = 0;
	if(info->IsAlign() )
	{
		info = GetAlignChunk(worldChunk,chunkX,chunkY,index);
	}
	if (!info)
	{
		return;
	}
	flt32 deltaX = info->m_nX/(float)TTextureInfo::MAXOFFSET;
	flt32 deltaY = info->m_nY/(float)TTextureInfo::MAXOFFSET;
	Vector2 scale(TTextureInfo::SCALECOAF/((float)info->m_ScaleX),TTextureInfo::SCALECOAF/((float)info->m_ScaleY));
	sInt32 id		= 0;
	for( sInt32 y=0; y<9; y++ )	
	{
		for( sInt32 x=0;x<9;x++ ) 
		{
			Assert( id < c_stripSize2 );
			Vector2 tex(8*chunkX + x,8*chunkY + y);
			flt32 Atan = GetAtan(tex);
			flt32 angle = Atan + info->m_angle*PI/180.f;
			kTexCoord[id].uv[index].u	= deltaX + (tex.length()*cos(angle)*scale.x)*g_ChunkTextureDefaultOverlap/8.0f;
			kTexCoord[id].uv[index].v	= deltaY + (tex.length()*sin(angle)*scale.y)*g_ChunkTextureDefaultOverlap/8.0f;
			id++;
		}
		if( y < 8 ) {
			for( sInt32 x=0;x<8;x++ ) {
				Vector2 tex(8*chunkX + x + 0.5f,8*chunkY + y + 0.5f);
				flt32 Atan = GetAtan(tex);
				flt32 angle = Atan + info->m_angle*PI/180.f;
				kTexCoord[id].uv[index].u	= deltaX + (tex.length()*cos(angle)*scale.x)*g_ChunkTextureDefaultOverlap/8.0f;
				kTexCoord[id].uv[index].v	= deltaY + (tex.length()*sin(angle)*scale.y)*g_ChunkTextureDefaultOverlap/8.0f;
				id++;
			}
		}
	}
}
TTextureInfo* CResMgr::GetAlignChunk( CWorldChunk* worldChunk ,sInt32& chunkX,sInt32& chunkY,int index)
{
	CWorldChunk* pAlign = NULL;
	TTextureInfo& ptexInfo = worldChunk->GetTexInfo(index);
	if (ptexInfo.m_nX == TTextureInfo::LeftAlign  )
	{
		if (worldChunk->m_chunk[0] > 0)
		{
			pAlign = m_bindTile->GetChunk(worldChunk->m_chunk[0] - 1,worldChunk->m_chunk[1]);
			++chunkX;
		}
	}
	else if( worldChunk->m_chunk[1] > 0)
	{
		pAlign = m_bindTile->GetChunk(worldChunk->m_chunk[0],worldChunk->m_chunk[1] - 1);
		++chunkY;
	}
	if (NULL == pAlign)
	{
		return NULL;
	}
	int nSpecialLevel = pAlign->IsExistSpecialTexture(worldChunk->m_texture[index]);
	if(-1 == nSpecialLevel)
		return NULL;
	if ( pAlign->GetTexInfo(nSpecialLevel).IsAlign())
	{
		return GetAlignChunk(pAlign,chunkX,chunkY,nSpecialLevel);
	}
	else
	{
		return &pAlign->GetTexInfo(nSpecialLevel);
	}

}

void CResMgr::CalcBBox(CNdlShapeRes* res, CWorldChunk* worldChunk)
{
	guardfunc;
	//CSALocker locker(this);
	D3DXVECTOR3 vMax, vMin;

	float fcenter_x = worldChunk->Origin()[0];
	float fcenter_y = worldChunk->Origin()[1];
	vMin.x = fcenter_x - WORLD_CHUNKSIZE * 0.5f;
	vMin.y = fcenter_y - WORLD_CHUNKSIZE * 0.5f;
	vMin.z = worldChunk->GetHeight()[0];
	vMax.x = vMin.x + WORLD_CHUNKSIZE;
	vMax.y = vMin.y + WORLD_CHUNKSIZE;
	vMax.z = worldChunk->GetHeight()[1];

	res->m_BBox.BuildAABB( *(Vector*)&(vMax), *(Vector*)&( vMin ) );
	res->m_MMBox.vecMin = vMin;
	res->m_MMBox.vecMax = vMax;

	// 水面
	if( RES_INVALID_ID != worldChunk->m_liquidId )
	{
		res->m_LiquidMMBox.vecMax = vMax;//vMin;
		res->m_LiquidMMBox.vecMax.z = worldChunk->GetLiquidHeight();
		res->m_LiquidMMBox.vecMin = vMin;
		res->m_LiquidMMBox.vecMin.z = worldChunk->GetLiquidHeight();
	}
	unguard;
}

void CResMgr::CalChunkSpecialUV( CWorldChunk* worldChunk, FTerrainVertexSpecial terrainVertex[],int special )
{
	if (special == -1)
	{
		special = worldChunk->IsExistSpecialLayer();
		if(special != -1)
		{
			for (int i = 0; i <= special; ++i )
			{
				CalSpecialTEXCOORD(worldChunk,i, terrainVertex);
			}
		}
	}
	else
	{
		CalSpecialTEXCOORD(worldChunk,special, terrainVertex);
	}
}
void CResMgr::FillLOD2Vertex( TChunkLOD2Vertex* LOD2Vertex,CWorldChunk* worldChunk )
{
	sInt32 id		= 0;
	sInt32 Lod2Id	= 0;
	flt32 originX = ((worldChunk->m_chunk[0])*WORLD_CHUNKSIZE+(WORLD_CHUNKSIZE*0.5f)); 
	flt32 originY = ((worldChunk->m_chunk[1])*WORLD_CHUNKSIZE+(WORLD_CHUNKSIZE*0.5f)); 
	const TChunkVertex* outHeight = worldChunk->m_vertexOut;
	const TChunkVertex* inHeight = worldChunk->m_vertexIn;
	for( sInt32 y=0; y<9; y++ )	
	{
		for( sInt32 x=0;x<9;x++ ) 
		{
			if (id == m_LOD2IndexConvert[Lod2Id])
			{
				sInt32 vId = y*9+x;
				TChunkLOD2Vertex& thisVertex = LOD2Vertex[Lod2Id];
				thisVertex.p.x		= originX+m_IndexToInOut[id].x;
				thisVertex.p.y		= originY+m_IndexToInOut[id].y;
				thisVertex.p.z		= outHeight[vId].height;
				++Lod2Id;
			}
			id++;
		}
		if( y < 8 ) {
			for( sInt32 x=0;x<8;x++ ) {
				if (id == m_LOD2IndexConvert[Lod2Id])
				{
					sInt32 vId = y*8+x;
					TChunkLOD2Vertex& thisVertex = LOD2Vertex[Lod2Id];
					thisVertex.p.x		= originX+m_IndexToInOut[id].x;
					thisVertex.p.y		= originY+m_IndexToInOut[id].y;
					thisVertex.p.z		= inHeight[vId].height;
					++Lod2Id;
				}
				id++;
			}
		}
	}

}

void CResMgr::FillLOD2Vertex(CNdlShapeRes* res,CWorldChunk* worldChunk)
{
	if ((!SwGlobal::s_SimpleMapLoadMode )&& res && (!res->m_culled))
	{
		LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
		if (
			// 			SUCCEEDED(pd3dDevice->CreateVertexBuffer(CHUNK_LOD1T02_VERTEX_NUMBER * sizeof(TChunkLOD2Vertex),
			// 			D3DUSAGE_WRITEONLY, FTerrainVertexSpecial::eFVF, D3DPOOL_DEFAULT,
			// 			&m_pVBLOD2, 0))
			// 			||
			SUCCEEDED(pd3dDevice->CreateVertexBuffer(CHUNK_LOD1T02_VERTEX_NUMBER * sizeof(TChunkLOD2Vertex),
			D3DUSAGE_WRITEONLY, D3DFVF_XYZ, D3DPOOL_MANAGED,// modified, jiayi, [2010/4/8], fvf is wrong
			&res->m_pVBLOD2, 0))
			)
		{
			TChunkLOD2Vertex* pDatas = 0;
			if (SUCCEEDED(res->m_pVBLOD2->Lock(0, CHUNK_LOD1T02_VERTEX_NUMBER * sizeof(TChunkLOD2Vertex), (void**)&pDatas, 0)))
			{
				FillLOD2Vertex(pDatas,worldChunk);
				res->m_pVBLOD2->Unlock();
			}
		}
	}
// #endif
}

void CResMgr::SafeDeleteObjInfo( TObjectInfo* objInfo )
{
	if (objInfo->model)
	{
		if( objInfo->id >= 0 && objInfo->id < (int)m_staticModelRefList.size() )
		{
			CWorldRes* p = m_staticModelRefList[objInfo->id];
			CNdlStaticModelRes* pRes	= dynamic_cast<CNdlStaticModelRes*>(m_worldBuffer->m_globalResMgr->FindRefStaticModel(p->GetName()));
			if (pRes->GetModel() == objInfo->model)
			{//is clone
				objInfo->model = NULL;
				sInt32 childIndex = 0;
#ifdef SUPPORT_CHILD_MODEL
				childIndex = pRes->GetChildIndex(childModelName);
#endif//SUPPORT_CHILD_MODEL
				pRes->MarkClone(childIndex,false);
			}
		}		
	}
	SAFE_DELETE( objInfo );
// 	m_worldBuffer->m_globalResMgr->UnloadRefModel(p->GetName());
}

void CResMgr::FreeAlphaAndShadow()
{
	int i = 0;
	for( i = 0; i < m_alphaList.size(); i++ ) {
		SAFE_DELETE( m_alphaList[i] );
	}
	m_alphaList.clear();
	for( i = 0; i < m_shadowList.size(); i++ ) {
		SAFE_DELETE( m_shadowList[i] );
	}
	m_shadowList.clear();

}

void CResMgr::FillStaticIndexBuffer()
{
	if (m_pIB[0] != NULL)
	{
		return;
	}
	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();

	for (int i = 0; i < LODLEVEL; ++i)
	{
		size_t s = m_LODFaceCount[i]*3 * sizeof(WORD);
		if (SUCCEEDED(pd3dDevice->CreateIndexBuffer(
			s, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,
			D3DPOOL_DEFAULT, &m_pIB[i], 0)))
		{
			WORD* pDatas = 0;
			if (SUCCEEDED(m_pIB[i]->Lock(0, s, (void**)&pDatas, 0)))
			{
				memcpy(pDatas, m_IndexStream[i], s);
				m_pIB[i]->Unlock();
			}
		}
	}
}

void CResMgr::ReleaseStaticIndexBuffer()
{
	for (int i = 0; i  < LODLEVEL; ++i)
	{
		SafeRelease(m_pIB[i]);
	}

}


