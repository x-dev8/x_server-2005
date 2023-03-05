/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NdlResMgr.cpp
* Create: 	10/06/2006
* Desc:		全局资源管理
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "Me3d/Model/Mex2.h"

#include "Me3d/Utility.h"


// int			CResMgr::m_baseShadowId = RES_INVALID_ID;


CSoundPointRes* CResEditMgr::CreateSoundPointRes()
{
	return MeNew CSoundPointEditRes;
}

CTransportRes* CResEditMgr::CreateTransportRes()
{
	return MeNew CTransportEditRes;

}

CTargetRes* CResEditMgr::CreateTargetRes()
{
	return MeNew CTargetEditRes;

}


bool CResEditMgr::IsNeedClone( CNdlStaticModelRes* pRes,sInt32 nsubIndex )
{
	return true;
}

void CResEditMgr::FillShapeData( CNdlShapeRes* res , CWorldChunk* worldChunk )
{
	_FillShapData(res,worldChunk);

	PushChunkLiquid( worldChunk, res->GetId(),emLT_Ocean , worldChunk->m_liquidHeight ,worldChunk->m_liquidColor,worldChunk->m_liquidAlphaCoaf);
}

bool CResEditMgr::RefreshChunkMask( CWorldChunk* worldChunk )
{
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

void CResEditMgr::ReplaceChunkTextrueId( CWorldChunk* worldChunk, sInt32 layerId , sInt32 newId )
{
	CNdlTextureRes* pTexture = NULL;
	if (worldChunk->m_texture[layerId] != -1 && (pTexture = GetTexture(worldChunk->m_texture[layerId])))
	{
		pTexture->DecRefCount();
	}
	worldChunk->m_texture[layerId] = newId;
	if (-1 != newId)
	{
		pTexture = GetTexture(worldChunk->m_texture[layerId]);
		if (pTexture)
		{
			pTexture->IncRefCount();
		}
	}
}

TObjectEditInfo::TObjectEditInfo()
{
	m_bLockHeight = true;
	m_pSupperFloor	= NULL;
}

TObjectEditInfo::~TObjectEditInfo()
{
}

void TObjectEditInfo::ApplyTransform()
{
	//if( model == NULL )
	//	return;

	//NiMatrix3 matRot;
	//matRot.FromEulerAnglesXYZ( rotate[0]*PI/180.0f, rotate[1]*PI/180.0f, rotate[2]*PI/180.0f );
	//NiMatrix3 matScl = NiMatrix3::IDENTITY;
	////matScl.SetRow( 0, scale[0], 0.0f, 0.0f );
	////matScl.SetRow( 1, 0.0f, scale[1], 0.0f );
	////matScl.SetRow( 2, 0.0f, 0.0f, scale[2] );

	//NiMatrix3 matTrans = matRot * matScl;
	//model->SetRotate( matTrans );
	//model->SetScale( scale[0] );
	//model->SetTranslate( pos[0]+offset[0], pos[1]+offset[1], pos[2]+offset[2]);
	//model->Update(0.0f);
	//if (collidModel)
	//{
	//	collidModel->SetRotate( matTrans );
	//	collidModel->SetScale( scale[0] );
	//	collidModel->SetTranslate( pos[0]+offset[0], pos[1]+offset[1], pos[2]+offset[2]);
	//	collidModel->Update(0.0f);
	//}
	//if (viewBlockModel)
	//{
	//	viewBlockModel->SetRotate( matTrans );
	//	viewBlockModel->SetScale( scale[0] );
	//	viewBlockModel->SetTranslate( pos[0]+offset[0], pos[1]+offset[1], pos[2]+offset[2]);
	//	viewBlockModel->Update(0.0f);
	//}
	//if (obstacleModel)
	//{
	//	obstacleModel->SetRotate( matTrans );
	//	obstacleModel->SetScale( scale[0] );
	//	obstacleModel->SetTranslate( pos[0]+offset[0], pos[1]+offset[1], pos[2]+offset[2]);
	//	obstacleModel->Update(0.0f);
	//}

	model->SetRotationX( rotate[0]*PI/180.0f );
	model->SetRotationY( rotate[1]*PI/180.0f );
	model->SetRotationZ( rotate[2]*PI/180.0f );
	model->SetPosition( pos[0]+offset[0], pos[1]+offset[1], pos[2]+offset[2] );
	model->SetScaleXYZ(scale[0],scale[1],scale[2]);
	// 如果是静态模型，则直接生成世界坐标数据，用于渲染
	//if( !model->IsAni() )
		model->UpdateTransform();
	CreateFloorAndCollision();
}
void TObjectEditInfo::SyncOffset2WorldPos()
{
	pos[0] += offset[0];
	pos[1] += offset[1];
	pos[2] += offset[2];
	offset[0]	= 0;
	offset[1]	= 0;
	offset[2]	= 0;

}

bool TObjectEditInfo::LoadFromFile(const char* pszFile)
{
	if(TObjectInfo::LoadFromFile(pszFile))
	{
		ApplyTransform();
		return true;
	}
	return false;
}

TObjectInfo* TObjectEditInfo::Clone()
{
	if( !model )
	{
		return 0;
	}
	if( !model->GetMex() )
	{
		return 0;
	}
	TObjectEditInfo* pCloned = MeNew TObjectEditInfo();

	// 	DWORD dwFlag = 0;
	pCloned->model = MeNew MexAnimCtrl;
	if( pCloned->model->Clone(model, TRUE) )
		return pCloned;
	else
		return NULL;


	return pCloned;

}

TObjectInfo *TObjectEditInfo::CloneAll(void)
{
	TObjectEditInfo *pModel = (TObjectEditInfo *)Clone();

	if(pModel)
	{
		pModel->id = this->id;

		memcpy(pModel->pos, pos, sizeof(pModel->pos));
		memcpy(pModel->offset, offset, sizeof(pModel->offset));
		memcpy(pModel->rotate, rotate, sizeof(pModel->rotate));
		memcpy(pModel->scale, scale, sizeof(pModel->scale));

		pModel->ApplyTransform();
	}

	return pModel;
}


void TObjectEditInfo::CreateFloorAndCollision()
{
	guardfunc;
	CleanDspTree();
// #ifdef WORLD_EDIT
	SAFE_DESTROY_AND_DELETE(m_pSupperFloor);
// #endif


	// 设置最小单位，
	float fMinLeafSize = WORLD_TILESIZE*8/2;


	IMex* pMex = model->GetMex();
	if( !pMex || !pMex->GetGeometry())
		return;

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

	for( int nChunk = 0; nChunk < pMex->GetGeometry()->GetChunkCount(); nChunk++ )
	{
		Mex2GeoChunk* pChunk = (Mex2GeoChunk*)pMex->GetGeometry()->GetChunk(nChunk);

		float* vers = (float*)&vertices[0];

		if( pChunk->IsEffect() )
			continue;

		short* indices = (short*)pChunk->GetIndicesLocked();
		if (pChunk->GetType() == Mex2GeoChunkProperty::eSupperFloor)
		{
			pChunk->BlendVertex( vers, NULL, maxVertexCount, pMex, (float*)pMatrices, NULL);
			CreateSupperFloorBsp(fMinLeafSize);
			m_pSupperFloor->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
		}
		else if (pChunk->GetType() == Mex2GeoChunkProperty::eRFloor)
		{
			pChunk->BlendVertex( pMex, (float*)pMatrices );
			CreateFloorBsp(fMinLeafSize);
			m_pModelFloor->AddMesh( (float*)pChunk->GetWorldVertices(), pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
		}
		else	if (pChunk->GetType() == Mex2GeoChunkProperty::eFloor)
		{
			pChunk->BlendVertex( pMex, (float*)pMatrices );
			CreateFloorBsp(fMinLeafSize);
			m_pModelFloor->AddMesh( (float*)pChunk->GetWorldVertices(), pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
		}
		else	if (pChunk->GetType() == Mex2GeoChunkProperty::eRCollision)
		{
			pChunk->BlendVertex( pMex, (float*)pMatrices );
			CreateCollisionBsp(fMinLeafSize);
			m_pCollision->AddMesh( (float*)pChunk->GetWorldVertices(), pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
		}
		else	if (pChunk->GetType() == Mex2GeoChunkProperty::eCollision)
		{
			pChunk->BlendVertex( pMex, (float*)pMatrices );
			CreateCollisionBsp(fMinLeafSize);
			m_pCollision->AddMesh( (float*)pChunk->GetWorldVertices(), pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
			CreateCameraBsp(fMinLeafSize);
			m_pCameraCollision->AddMesh( (float*)pChunk->GetWorldVertices(), pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
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
// 			pChunk->BlendVertex( vers, NULL, maxVertexCount, pMex, (float*)pMatrices );
// 			CreateSupperFloorBsp(fMinLeafSize);
// 			m_pSupperFloor->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
// 		}
//         else if( strstr(lwrName, "rfloor") )    // 只判断人站立位置，不碰相机
//         {
//             pChunk->BlendVertex( vers, NULL, maxVertexCount, pMex, (float*)pMatrices );
//             pChunk->SetFloor();
//             CreateFloorBsp(fMinLeafSize);
//             m_pModelFloor->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
//         }
//         else if( strstr(lwrName, "floor") )
// 		{
// 			pChunk->BlendVertex( vers, NULL, maxVertexCount, pMex, (float*)pMatrices );
// 			pChunk->SetFloor();
// 			CreateFloorBsp(fMinLeafSize);
// 			m_pModelFloor->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
// 		}
// 		else if( strstr(lwrName, "rcoli"))	// 只碰撞人，不碰相机
// 		{
// 			pChunk->BlendVertex( vers, NULL, maxVertexCount, pMex, (float*)pMatrices );
// 			pChunk->SetCollision();
// 			CreateCollisionBsp(fMinLeafSize);
// 			m_pCollision->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
// 		}
// 		else if( strstr(lwrName, "coli") )	// 对人和相机都碰撞
// 		{
// 			pChunk->BlendVertex( vers, NULL, maxVertexCount, pMex, (float*)pMatrices );
// 			pChunk->SetCollision();
// 			CreateCollisionBsp(fMinLeafSize);
// 			m_pCollision->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
// 			CreateCameraBsp(fMinLeafSize);
// 			m_pCameraCollision->AddMesh( vers, pChunk->GetVertexCount(), indices, pChunk->GetFaceCount() );
// 		}
// 		pChunk->UnlockIndices();
	}
//#ifdef WORLD_EDIT
	if( m_pSupperFloor )
		m_pSupperFloor->CreateTree2();
//#endif

    if( m_pModelFloor )
        m_pModelFloor->CreateTree2();

	if( m_pCollision )
		m_pCollision->CreateTree2();

	if( m_pCameraCollision )
		m_pCameraCollision->CreateTree2();

	return;
	unguard;

}


void TObjectEditInfo::CreateSupperFloorBsp( float fMinLeafSize )
{
	if (NULL == m_pSupperFloor)
	{
		m_pSupperFloor = MeNew BspTree;
		m_pSupperFloor->SetMinLeafSize( fMinLeafSize );
	}

}

////////////////////////////////////////////////////////////////////////////////
CResEditMgr::CResEditMgr()
{
	m_monsterQuadList.clear();
// 	m_FlyRouteList.clear();
	m_NPCRouteList.clear();
	m_roadList.clear();
	m_shapeLineList.clear();
	m_ShadowShowType	 = eShadow;
}

CResEditMgr::~CResEditMgr()
{
	CleanMonsterQuad();
	CleanNPCRoute();
    ClearNpcLine();
}


void CResEditMgr::Unload()
{
	CResMgr::Unload();
	size_t i;
	for( i = 0; i < m_roadList.size(); i++ ) {
		SAFE_DELETE( m_roadList[i] );
	}
	m_roadList.clear();
	for( i = 0; i < m_shapeLineList.size(); i++ ) {
		SAFE_DELETE( m_shapeLineList[i] );
	}
	m_shapeLineList.clear();
}

sInt32 CResEditMgr::PushStaticModel( sInt32 refModelId, const flt32* pos, const flt32* offset, const flt32* rotate, const flt32* scale,
									TWTDObjLightmapInfo* plmInfo /*= NULL*/, TWTDObjInstance* pInss /*= NULL*/, TWTDObjLightmapColorData* pColorData /*= NULL*/ )
{
	if( refModelId <0 || refModelId >= m_staticModelRefList.size() )
		return RES_INVALID_ID;

	Assert( m_staticModelRefList[refModelId]->GetId() == refModelId );
	TObjectEditInfo* objInfo	= MeNew TObjectEditInfo;
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

 	GenerateObjInfo(objInfo, true);
	m_staticModelList.push_back( objInfo );

	return m_staticModelList.size()-1;
}




//extern float fTileMaxY;
sInt32 CResEditMgr::PushChunkShape( CWorldChunk* worldChunk )
{
	CNdlLineRes* lineRes = MeNew CNdlLineRes();
	lineRes->SetId( m_shapeLineList.size() );
	sprintf_s( lineRes->m_name, "Line_%d", lineRes->GetId() );
	lineRes->SetName( lineRes->m_name );
	bool isOk = CreateLineRes( worldChunk, lineRes );
	Assert( isOk );
	m_shapeLineList.push_back( lineRes );

	//Trace( "=================== Cache chunk shape ===================\n" );
	CNdlShapeRes* res	= MeNew CNdlShapeRes(worldChunk->IsCulled());
	Assert( NULL != res );
	res->SetId( m_shapeList.size() );
	char temp[RES_NAME_LEN];
	sprintf_s( temp, RES_NAME_LEN, "Shape_%d", res->GetId() );
	res->SetName(temp);
	worldChunk->m_shape		= res->GetId();
	m_shapeList.push_back(res);

	FillShapeData(res,worldChunk);
	FillLOD2Vertex(res,worldChunk);
	PushMask( worldChunk );
	RefreshChunkMask(worldChunk);
	// 计算BBox，用于可视剪裁
	CalcBBox(res, worldChunk);
	return m_shapeList.size()-1;
}

bool	CResEditMgr::CreateMeshRes(CWorldTile* pTile, int nMeshLength, float fHeightPercent)
{
	if (!pTile)
	{
		return false;
	}
	Assert(m_Mesh.m_nSize == 0);

	int nWidth = static_cast<int>(pTile->GetWidth());
	int nHeight = static_cast<int>(pTile->GetDepth());
	float *pt = pTile->GetTotalHeight();
	float fMinZ = pt[0];
	float fMaxZ = pt[1];
	float fHeight = fMinZ + fHeightPercent * (fMaxZ - fMinZ);

	int index = 0;
	for (int i = 0; i < nWidth; i += nMeshLength)
	{
		m_Mesh.m_pVertex[index].x =  i;		
		m_Mesh.m_pVertex[index].y =  0;		
		m_Mesh.m_pVertex[index].z =  fHeight; 
		++index;
		++m_Mesh.m_nSize;
			
		m_Mesh.m_pVertex[index].x =  i;		
		m_Mesh.m_pVertex[index].y =  nHeight;		
		m_Mesh.m_pVertex[index].z =  fHeight; 
		++index;
		++m_Mesh.m_nSize;
	}

	for (int i = 0; i < nHeight; i += nMeshLength)
	{
		m_Mesh.m_pVertex[index].x =  0;		
		m_Mesh.m_pVertex[index].y =  i;		
		m_Mesh.m_pVertex[index].z =  fHeight; 
		++index;
		++m_Mesh.m_nSize;

		m_Mesh.m_pVertex[index].x =  nWidth;		
		m_Mesh.m_pVertex[index].y =  i;		
		m_Mesh.m_pVertex[index].z =  fHeight; 
		++index;
		++m_Mesh.m_nSize;
	}

	return true;
}


void CResEditMgr::SetMeshRes(sInt32 nTileId, sInt32 nLength, float fHeight)
{
	CWorld* pWorld = SwGlobal::GetWorld();
	CWorldTile* tile = pWorld->GetWorldBuffer()->GetTile(nTileId);
	if (!tile)
	{
		return;
	}
	m_Mesh.Clean();
	bool isOk = CreateMeshRes(tile, nLength, fHeight);
	Assert(isOk);
}

void CResEditMgr::FillShadowByPathFindMap( uInt8 * alphaData,CWorldChunk* pChunk )
{
	SwMap& PathFindMap = pChunk->GetParentTile()->ReachableMap();
	float fRate = PathFindMap.GetMapRate();
	int nWidth = pChunk->GetParentTile()->GetWidth() / fRate;
	uInt8* alphaPtr		= alphaData;
	uInt8* mapPtr		= PathFindMap.GetMapData();
	if (NULL == mapPtr)
	{
		return;
	}
	for( sInt32 y = 0; y < 64; ++y) 
	{
		int Y = (pChunk->m_chunk[1] * WORLD_CHUNKSIZE + WORLD_ATOMSIZE*y) / fRate;
		for( sInt32 x = 0; x < 64; ++x) 
		{
			int X = (pChunk->m_chunk[0] * WORLD_CHUNKSIZE + WORLD_ATOMSIZE*x) / fRate;
			uInt8 c		= mapPtr[Y * nWidth + X];		
			switch(c)
			{
			case SwMap::UNREACHABLE:
				{
					*alphaPtr++	= 0x00;
					break;
				}
			case SwMap::CORNER_AREA:
				{
					*alphaPtr++	= 0x44;
					break;
				}
			case SwMap::OTHERS:
				{
					*alphaPtr++	= 0x88;
					break;
				}
			case SwMap::SUB_ROAD:
				{
					*alphaPtr++	= 0xcc;
					break;
				}
			case SwMap::MAIN_ROAD:
				{
					*alphaPtr++	= 0xFF;
					break;
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------
bool CResEditMgr::UpdateChunkMask( CWorldChunk* worldChunk )
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

	// 地形Mask(包含层纹理及阴影)
	uAlphaBit layer[3][WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM];
	for( sInt32 i=0; i<(emMSKC_Flight-1); i++ ) 
	{
		memset(layer[i],0xFF,WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM);
		if( RES_INVALID_ID != worldChunk->m_alpha[i] ) 
		{
			CNdlAlphaRes* alphaRes = GetAlpha( worldChunk->m_alpha[i] );
			if (alphaRes)
			{
				SwPublicFunc::GetAlphaData(layer[i],alphaRes->GetMaskData());
			}
// 			if (alphaRes)
// 			{
// 				layer[i] =  alphaRes->m_maskData;
// 			}
		}
	}

	// 地形阴影
	uAlphaBit shadow[WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM];
	if( RES_INVALID_ID != worldChunk->m_shadow ) 
	{
		CNdlAlphaRes* alphaRes = GetShadow( worldChunk->m_shadow );
		if (alphaRes)
		{
			SwPublicFunc::GetAlphaData(shadow,alphaRes->GetMaskData());
		}
//         if( alphaRes )
//             shadow =  alphaRes->m_maskData;
//         else
//             shadow = NULL;
	}
	else 
	{
		memset(shadow,0xFF,WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM);
// 		shadow = NULL;
	}

	// 道路
	if (IsRoadShow())
	{
		if(	 RES_INVALID_ID != worldChunk->m_road ) 
		{
			CNdlAlphaRes* alphaRes = GetRoad( worldChunk->m_road );
			if (alphaRes)
			{
				SwPublicFunc::GetAlphaData(shadow,alphaRes->GetMaskData());
			}
		}
		else
		{
			memset(shadow,0xFF,WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM);
		}
	}
	else if (m_ShadowShowType == ePathFindMap) // 寻路图
	{
		FillShadowByPathFindMap(shadow, worldChunk);
	}

	_RefillMaskTexture(texture, layer[0], layer[1], layer[2], shadow);
	return true;
}

bool CResEditMgr::CreateLineRes( CWorldChunk* worldChunk, CNdlLineRes* lineRes )
{
	sInt32 id = 0;	

	const uInt16 lineVtxNum	= 2*WORLD_TILE_CHUNK_UNIT_NUM+1;

	if( (worldChunk->m_chunk[0]==(worldChunk->m_parentTile->GetRowColumn()[0]-1)) && (worldChunk->m_chunk[1]==0) ) 
	{

		//		NiColorA* lineColors	= NiNew NiColorA[lineVtxNum];
		//		NiBool* lineFlag		= NiAlloc(NiBool, lineVtxNum);

		for( sInt32 i=0; i<WORLD_TILE_CHUNK_UNIT_NUM; i++ ) {
			lineRes->m_line->kVertex[id].p.x		= worldChunk->Origin()[0]+(i-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;		
			lineRes->m_line->kVertex[id].p.y		= worldChunk->Origin()[1]+(0-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
			lineRes->m_line->kVertex[id].p.z		= worldChunk->m_vertexOut[i].height + 0.1f+130;
			lineRes->m_line->kVertex[id].u			= 0.0f;
			lineRes->m_line->kVertex[id].v			= 0.0f;
			lineRes->m_line->kVertex[id].color		= 0x000000ff;
			//			lineFlag[id]		= TRUE;
			id++;
		}
		for( sInt32 i=0; i<WORLD_TILE_CHUNK_UNIT_NUM; i++ ) {
			lineRes->m_line->kVertex[id].p.x		= worldChunk->Origin()[0]+(WORLD_TILE_CHUNK_UNIT_NUM-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;		
			lineRes->m_line->kVertex[id].p.y		= worldChunk->Origin()[1]+(i-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
			lineRes->m_line->kVertex[id].p.z		= worldChunk->m_vertexOut[(WORLD_TILE_CHUNK_UNIT_NUM+1) *i+WORLD_TILE_CHUNK_UNIT_NUM].height + 0.1f+130;
			lineRes->m_line->kVertex[id].u			= 0.0f;
			lineRes->m_line->kVertex[id].v			= 0.0f;
			lineRes->m_line->kVertex[id].color		= 0x000000ff;//			lineFlag[id]		= TRUE;
			id++;
		}
		lineRes->m_line->kVertex[id].p.x		= worldChunk->Origin()[0]+(WORLD_TILE_CHUNK_UNIT_NUM-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;		
		lineRes->m_line->kVertex[id].p.y		= worldChunk->Origin()[1]+(WORLD_TILE_CHUNK_UNIT_NUM-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
		lineRes->m_line->kVertex[id].p.z		= worldChunk->m_vertexOut[(WORLD_TILE_CHUNK_UNIT_NUM+1)*WORLD_TILE_CHUNK_UNIT_NUM+WORLD_TILE_CHUNK_UNIT_NUM].height + 0.1f+130;
		lineRes->m_line->kVertex[id].u			= 0.0f;
		lineRes->m_line->kVertex[id].v			= 0.0f;
		lineRes->m_line->kVertex[id].color		= 0x000000ff;//		lineFlag[id]			= FALSE;


	}
	else {
		for( sInt32 i=0; i<WORLD_TILE_CHUNK_UNIT_NUM; i++ ) {
			lineRes->m_line->kVertex[id].p.x		= worldChunk->Origin()[0]+(i-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;		
			lineRes->m_line->kVertex[id].p.y		= worldChunk->Origin()[1]+(0-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
			lineRes->m_line->kVertex[id].p.z		= worldChunk->m_vertexOut[i].height + 0.1f+130;
			lineRes->m_line->kVertex[id].u			= 0.0f;
			lineRes->m_line->kVertex[id].v			= 0.0f;
			lineRes->m_line->kVertex[id].color		= 0x00ffff00;
			id++;
		}
		for( sInt32 i=0; i<WORLD_TILE_CHUNK_UNIT_NUM; i++ ) {
			lineRes->m_line->kVertex[id].p.x		= worldChunk->Origin()[0]+(WORLD_TILE_CHUNK_UNIT_NUM-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;		
			lineRes->m_line->kVertex[id].p.y		= worldChunk->Origin()[1]+(i-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
			lineRes->m_line->kVertex[id].p.z		= worldChunk->m_vertexOut[(WORLD_TILE_CHUNK_UNIT_NUM+1) *i+WORLD_TILE_CHUNK_UNIT_NUM].height + 0.1f+130;
			lineRes->m_line->kVertex[id].u			= 0.0f;
			lineRes->m_line->kVertex[id].v			= 0.0f;
			lineRes->m_line->kVertex[id].color		= 0x00ffff00;
			id++;
		}
		lineRes->m_line->kVertex[id].p.x		= worldChunk->Origin()[0]+(WORLD_TILE_CHUNK_UNIT_NUM-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;		
		lineRes->m_line->kVertex[id].p.y		= worldChunk->Origin()[1]+(WORLD_TILE_CHUNK_UNIT_NUM-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
		lineRes->m_line->kVertex[id].p.z		= worldChunk->m_vertexOut[(WORLD_TILE_CHUNK_UNIT_NUM+1)*WORLD_TILE_CHUNK_UNIT_NUM+WORLD_TILE_CHUNK_UNIT_NUM].height + 0.1f+130;
		lineRes->m_line->kVertex[id].u			= 0.0f;
		lineRes->m_line->kVertex[id].v			= 0.0f;
		lineRes->m_line->kVertex[id].color		= 0x00ffff00;
	}		
	//line->SetName( "ChunkLine" );

	
	return true;
}

bool CResEditMgr::RefreshLineRes( CWorldChunk* worldChunk, sInt32 lineId )
{
	if( NULL == worldChunk )
		return false;

	if( lineId >= m_shapeLineList.size() )
		return false;

	CNdlLineRes* lineRes = (CNdlLineRes*)m_shapeLineList[lineId];
	if( NULL == lineRes )
		return false;

	CNdlLineRes::swChunckLine* chunkLine = lineRes->m_line;
	if( NULL != chunkLine ) {

		sInt32 id = 0;
		const uInt16 lineVtxNum	= 2*WORLD_TILE_CHUNK_UNIT_NUM+1;

		//		Vector* lineVerts		= chunkLine->GetVertices();
		for( sInt32 i=0; i<WORLD_TILE_CHUNK_UNIT_NUM; i++ ) {
			chunkLine->kVertex[id].p.x		= worldChunk->Origin()[0]+(i-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;		
			chunkLine->kVertex[id].p.y		= worldChunk->Origin()[1]+(0-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
			chunkLine->kVertex[id].p.z		= worldChunk->m_vertexOut[i].height + 0.1f+130;
			id++;
		}
		for( sInt32 i=0; i<WORLD_TILE_CHUNK_UNIT_NUM; i++ ) {
			chunkLine->kVertex[id].p.x		= worldChunk->Origin()[0]+(WORLD_TILE_CHUNK_UNIT_NUM-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;		
			chunkLine->kVertex[id].p.y		= worldChunk->Origin()[1]+(i-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
			chunkLine->kVertex[id].p.z		= worldChunk->m_vertexOut[(WORLD_TILE_CHUNK_UNIT_NUM+1) *i+WORLD_TILE_CHUNK_UNIT_NUM].height + 0.1f+130;
			id++;
		}
		chunkLine->kVertex[id].p.x			= worldChunk->Origin()[0]+(WORLD_TILE_CHUNK_UNIT_NUM-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;		
		chunkLine->kVertex[id].p.y			= worldChunk->Origin()[1]+(WORLD_TILE_CHUNK_UNIT_NUM-(WORLD_TILE_CHUNK_UNIT_NUM>>1))*WORLD_UNITSIZE;
		chunkLine->kVertex[id].p.z			= worldChunk->m_vertexOut[(WORLD_TILE_CHUNK_UNIT_NUM+1)*WORLD_TILE_CHUNK_UNIT_NUM+WORLD_TILE_CHUNK_UNIT_NUM].height + 0.1f+130;

	}
	

	return true;
}

CMeshLineRes* CResEditMgr::GetMesh()
{
	return &m_Mesh;
}

CNdlLineRes* CResEditMgr::Line( sInt32 id )
{
	if( (id < 0) || (id >= m_shapeLineList.size()) ) {
		return NULL;
	}

	return ( (CNdlLineRes*)m_shapeLineList[id] );
}

bool CResEditMgr::RefreshObjHeight( CWorldChunk* worldChunk )
{
	flt32 height;
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	const CNdlEditWorldPicker* picker = view->GetWorldPicker();
	for( size_t i=0; i<worldChunk->m_staticModelList.size(); i++ ) {
		sInt32 id		= worldChunk->m_staticModelList[i];
		if( id < m_staticModelList.size() ) {
			TObjectEditInfo* p	= (TObjectEditInfo*)m_staticModelList[id];
			if (!p->m_bLockHeight)
			{
				if( picker->GetHeight( p->pos[0], p->pos[1], height ) ) {
					p->pos[2]	= height;
					p->ApplyTransform();
				}
			}
		}
	}
	
	return true;
}

bool CResEditMgr::RefreshChunkShapeHeight( sInt32 shapeId, const TChunkVertex* outHeight, const TChunkVertex* inHeight, CWorldChunk* worldChunk, uInt32 hole )
{
	CNdlShapeRes* res = Shape(shapeId);
	Assert( NULL != res );
	Assert( res->GetId() == shapeId );
	sInt32 id		= 0;
	//flt32 zBias;
	FTerrainVertexSpecial* pDatas = 0;
	if (SUCCEEDED(res->m_pVB->Lock(0, CHUNK_VERTEX_NUMBER * sizeof(FTerrainVertexSpecial), (void**)&pDatas, 0)))
	{
		for( sInt32 y=0; y<9; y++ )	
		{
			for( sInt32 x=0;x<9;x++ ) 
			{
// 				Assert( id < c_stripSize2 );
				FTerrainVertexSpecial& thisVertex = pDatas[id];
				sInt32 vId = y*9+x;
				thisVertex.p.z		= outHeight[vId].height;// + zBias;
				id++;
			}
			if( y < 8 ) {
				for( sInt32 x=0;x<8;x++ ) {
					FTerrainVertexSpecial& thisVertex = pDatas[id];
					sInt32 vId = y*8+x;
					thisVertex.p.z		= inHeight[vId].height;//+WORLD_UNITSIZE*0.5f;
					id++;
				}
			}
		}
		res->m_pVB->Unlock();

	}
	CalcBBox(res, worldChunk);

	return true;
}

bool CResEditMgr::RefreshChunkShapeNormal( sInt32 shapeId, const TChunkVertex* outHeight, const TChunkVertex* inHeight, uInt32 hole )
{
	CNdlShapeRes* res = Shape(shapeId);
	Assert( NULL != res );
	Assert( res->GetId() == shapeId );
	sInt32 id		= 0;
	FTerrainVertexSpecial* pDatas = 0;
	if (SUCCEEDED(res->m_pVB->Lock(0, CHUNK_VERTEX_NUMBER * sizeof(FTerrainVertexSpecial), (void**)&pDatas, 0)))
	{
		for( sInt32 y=0; y<9; y++ )	
		{
			for( sInt32 x=0;x<9;x++ ) 
			{
// 				Assert( id < c_stripSize2 );
				FTerrainVertexSpecial& thisVertex = pDatas[id];
				sInt32 vId = y*9+x;
				thisVertex.n.x	= outHeight[vId].normal[0]/127.0f;
				thisVertex.n.y	= outHeight[vId].normal[1]/127.0f;
				thisVertex.n.z	= outHeight[vId].normal[2]/127.0f;
				id++;
			}
			if( y < 8 ) {
				for( sInt32 x=0;x<8;x++ ) {
					FTerrainVertexSpecial& thisVertex = pDatas[id];
					sInt32 vId = y*8+x;
					thisVertex.n.x	= inHeight[vId].normal[0]/127.0f;
					thisVertex.n.y	= inHeight[vId].normal[1]/127.0f;
					thisVertex.n.z	= inHeight[vId].normal[2]/127.0f;
					id++;
				}
			}
		}
		res->m_pVB->Unlock();
	}


	return true;
}

bool CResEditMgr::PopStaticModel( sInt32 staticId )
{
	Assert( staticId >= 0 && staticId < m_staticModelList.size() );

	TObjectEditInfo* objInfo	= (TObjectEditInfo*)m_staticModelList[staticId];
	sInt32	objRefId		= objInfo->id;

	if( objRefId >= 0 && objRefId < m_staticModelRefList.size() ) {
		CWorldRes* res = (CWorldRes*)m_staticModelRefList[objRefId];
		res->DecRefCount();
		Assert( res->RefCount() >= 0 );
	}
	m_bindTile->CreateFloorAndCollision();
	return true;
}

bool CResEditMgr::ModifyStaticModel( sInt32 modelId, const flt32* offset, const flt32* rotate, const flt32* scale )
{
	if( modelId <0 || modelId >= m_staticModelList.size() )
		return false;

	TObjectEditInfo* objInfo = (TObjectEditInfo*)m_staticModelList[modelId];

	bool b_isRotateModified = false;
	for( sInt32 i=0; i<3; i++ ) {
		if (objInfo->rotate[i]	!= rotate[i])
		{
			b_isRotateModified = true;
		}
	}

	for( sInt32 i=0; i<3; i++ ) {
		objInfo->rotate[i]	= rotate[i];
		objInfo->scale[i]	= scale[i];
	}

	NiMatrix3 matRot;
	matRot.FromEulerAnglesXYZ( objInfo->rotate[0]*PI/180.0f, objInfo->rotate[1]*PI/180.0f, objInfo->rotate[2]*PI/180.0f );
	NiMatrix3 matScl = NiMatrix3::IDENTITY;
	// 测试后发现,如果这么做,NiPick 有时 pick 不到物体.
	//matScl.SetRow( 0, objInfo->scale[0], 0.0f, 0.0f );
	//matScl.SetRow( 1, 0.0f, objInfo->scale[1], 0.0f );
	//matScl.SetRow( 2, 0.0f, 0.0f, objInfo->scale[2] );
	
	NiMatrix3 matRotTrans = matRot * matScl;

	if(b_isRotateModified)
	{
		objInfo->SyncOffset2WorldPos();
	}
	else
	{
		NiMatrix3 matRevRot = matRot.Inverse();
		Vector vOffset(offset[0],offset[1],offset[2]);
		Vector vOffsetTrans = vOffset* matRevRot;
		objInfo->offset[0]	= vOffsetTrans.x;
		objInfo->offset[1]	= vOffsetTrans.y;
		objInfo->offset[2]	= vOffsetTrans.z;
	}

	objInfo->ApplyTransform();
	
	return true;
}

sInt32 CResEditMgr::PushDoodad( const char* modelName )
{
	sInt32 refModelId = PushRefDoodad(modelName);
	IncDoodadRef(refModelId);
	return refModelId;
}

bool CResEditMgr::PopDoodad( sInt32 DoodadId )
{
	if( DoodadId >= 0 && DoodadId < m_doodadRefList.size() ) {
		DecDoodadRef(DoodadId);
	}
	return true;

}
bool CResEditMgr::ReplaceDoodadId( CWorldRes* nnewRes,CWorldRes* noldRes )
{
	for( sInt32 i=0; i<(m_bindTile->GetChunkTotal()); i++ ) {
		CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
		for (sInt32 k = 0; k < worldChunk->GetDoodadLevelCount(); ++k)
		{
			if (noldRes->GetId() == worldChunk->GetDoodadList()[k]->mdoodadId)
			{
				DecDoodadRef(worldChunk->GetDoodadList()[k]->mdoodadId);
				worldChunk->GetDoodadList()[k]->mdoodadId = nnewRes->GetId();
				IncDoodadRef(worldChunk->GetDoodadList()[k]->mdoodadId);
			}
		}
	}	
	return true;
}

bool CResEditMgr::ReplaceTextureId( sInt32 newId,sInt32 oldId )
{
	for( sInt32 i=0; i<(m_bindTile->GetChunkTotal()); i++ ) {
		CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
		for (sInt32 j = 0; j < worldChunk->GetLayerCount(); ++j )
		{
			if (worldChunk->m_texture[j] == oldId)
			{
				ReplaceChunkTextrueId(worldChunk, j,newId);
			}
		}
	}	
	return true;
}


bool CResEditMgr::CleanUnusedResource(bool isGameWtd)
{
	PreClean();
	CleanUnusedTexture();
	CleanUnusedAlphaAndShadow();
	CleanUnusedModel(isGameWtd);

	CleanUnusedDoodad();
	return true;
}

bool CResEditMgr::FindStaticModelInUsed( sInt32 resId)
{
	for( int i = 0; i < m_bindTile->GetChunkTotal(); i++ ) {
		CWorldChunk* worldChunk				= m_bindTile->GetChunk(i);
		std::vector<sInt32>::iterator it	= worldChunk->m_staticModelList.begin();
		for(;it!=worldChunk->m_staticModelList.end();++it) {
			sInt32 p = *it;
			if( p == resId ) {
				return true;
			}
		}
	}
	return false;
}
void CResEditMgr::CleanUnusedAlphaAndShadow()
{
	std::vector<CBaseRes*>::iterator mIt = m_alphaList.begin();
	for(;mIt!=m_alphaList.end();) 
	{
		CNdlAlphaRes* pRes	= (CNdlAlphaRes*)(*mIt);
		sInt32 delId			= pRes->GetId();
		bool bFound = false;
		bool bCanDel = false;
		for (int i = 0; i < m_bindTile->GetChunkTotal(); ++i)
		{
			CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
			for (int j = 0; j < TextureLayerFlight - 1;++j)
			{
				if (RES_INVALID_ID == worldChunk->m_alpha[j])
				{
					continue;
				}
				if (delId == worldChunk->m_alpha[j])
				{
					bFound = true;
					if (worldChunk->IsCulled() || worldChunk->m_texture[j + 1] == RES_INVALID_ID)
					{
						bCanDel = true;
					}
					else
					{
						bool bUseful = false;
						for(int a = 0; a < WORLD_TILE_CHUNK_ATOM_NUM*32; ++a)
						{
							if (pRes->GetMaskData()[a] != 0xFF)
							{
								bUseful = true;
								break;
							}
						}
						if (!bUseful)
						{
							bCanDel = true;
						}
					}
					if (bCanDel)
					{
						worldChunk->m_alpha[j] = RES_INVALID_ID;
					}
					break;
				}
			}
			if (bFound)
			{
				break;
			}

		}
		if (!bFound || bCanDel)
		{
			mIt = m_alphaList.erase( mIt );

			SAFE_DELETE( pRes );

			for( sInt32 i=0; i< m_alphaList.size(); i++ ) {
				CBaseRes* p = (CBaseRes*)m_alphaList[i];
				if( p->GetId() == delId ) {
					Assert( false );
				}
				else if( p->GetId() > delId ){
					p->GetId()--;
				}
				Assert( p->GetId() == i );
			}
			for (int i = 0; i < m_bindTile->GetChunkTotal(); ++i)
			{
				CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
				for (int j = 0; j < worldChunk->GetLayerCount() - 1;++j)
				{
					if (RES_INVALID_ID == worldChunk->m_alpha[j])
					{
						continue;
					}
					if (delId < worldChunk->m_alpha[j])
					{
						--worldChunk->m_alpha[j];
					}
				}

			}

		}
		else
		{
			++mIt;
		}

	}
	for (int i = 0; i < m_bindTile->GetChunkTotal(); ++i)
	{
		CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
		for (int j = 0; j < worldChunk->GetLayerCount() - 1;++j)
		{
			if (RES_INVALID_ID == worldChunk->m_alpha[j])
			{
				continue;
			}
			if (m_alphaList.size() < worldChunk->m_alpha[j])
			{
				assert(0);
				worldChunk->m_alpha[j] = RES_INVALID_ID;
			}
		}

	}

	mIt = m_shadowList.begin();
	for(;mIt!=m_shadowList.end();) 
	{
		CNdlAlphaRes* pRes	= (CNdlAlphaRes*)(*mIt);
		sInt32 delId			= pRes->GetId();
		bool bFound = false;
		bool bCanDel = false;
		for (int i = 0; i < m_bindTile->GetChunkTotal(); ++i)
		{
			CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
			if (RES_INVALID_ID == worldChunk->m_shadow)
			{
				continue;
			}
			{
				if (delId == worldChunk->m_shadow)
				{
					bFound = true;
					if (worldChunk->IsCulled())
					{
						bCanDel = true;
					}
					else
					{
						bool bUseful = false;
						for(int a = 0; a < WORLD_TILE_CHUNK_ATOM_NUM*32; ++a)
						{
							if (pRes->GetMaskData()[a] != 0xFF)
							{
								bUseful = true;
								break;
							}
						}
						if (!bUseful)
						{
							bCanDel = true;
						}
					}
					if (bCanDel)
					{
						worldChunk->m_shadow = RES_INVALID_ID;
					}
					break;
				}
			}
		}
		if (!bFound || bCanDel)
		{
			mIt = m_shadowList.erase( mIt );

			SAFE_DELETE( pRes );

			for( sInt32 i=0; i< m_shadowList.size(); i++ ) {
				CNdlAlphaRes* p = (CNdlAlphaRes*)m_shadowList[i];
				if( p->GetId() == delId ) {
					Assert( false );
				}
				else if( p->GetId() > delId ){
					p->GetId()--;
				}
				Assert( p->GetId() == i );
			}
			for (int i = 0; i < m_bindTile->GetChunkTotal(); ++i)
			{
				CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
				if (RES_INVALID_ID == worldChunk->m_shadow)
				{
					continue;
				}
				if (delId < worldChunk->m_shadow)
				{
					--worldChunk->m_shadow;
				}

			}

		}
		else
		{
			++mIt;
		}

	}
	for (int i = 0; i < m_bindTile->GetChunkTotal(); ++i)
	{
		CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
		if (RES_INVALID_ID == worldChunk->m_shadow)
		{
			continue;
		}
		if (m_shadowList.size() < worldChunk->m_shadow)
		{
			assert(0);
			worldChunk->m_shadow = RES_INVALID_ID;
		}
	}
}

void CResEditMgr::PreClean()
{
	if(0)
	{//这里只是处理一个美术的路径失误
		int nSize = m_staticModelRefList.size();
		for (int i = 0; i < nSize; ++i )
		{
			CWorldRes* p	= (CWorldRes*)m_staticModelRefList[i];
			const char* name = p->GetName();
			CString strName(name);
			strName = strName.MakeLower();
			name = strName.GetString();
			
// 			if (strstr(name,"qshuihu\\glass\\glass"))
// 			{
// 				int nStart = strstr(name,"qshuihu\\glass\\glass") - name;
// 				std::string cName(name);
// 				cName.erase(nStart,strlen("qshuihu\\glass\\glass"));
// 				cName.insert(nStart,"grass\\grass");
// 
// 				nStart = cName.find("glass");
// 				if (-1 != nStart)
// 				{
// 					cName.erase(nStart,strlen("glass"));
// 					cName.insert(nStart,"grass");
// 				}
// 				int nnewId = PushRefStaticModel( cName.c_str() );
// 				ReplaceModelId(m_staticModelRefList[nnewId],p);
// 				continue;
// 			}
// 			if (strstr(name,"qshuihu\\glass"))
// 			{
// 				int nStart = strstr(name,"qshuihu\\glass") - name;
// 				std::string cName(name);
// 				cName.erase(nStart,strlen("qshuihu\\glass"));
// 				cName.insert(nStart,"GrassNormal\\grass");
// 				int nnewId = PushRefStaticModel( cName.c_str() );
// 				ReplaceModelId(m_staticModelRefList[nnewId],p);
// 				continue;
// 			}
// 			if (strstr(name,"qshuihu\\tree"))
// 			{
// 				int nStart = strstr(name,"qshuihu\\tree") - name;
// 				std::string cName(name);
// 				cName.erase(nStart,strlen("qshuihu\\tree"));
// 				cName.insert(nStart,"Tree\\tree");
// 				int nnewId = PushRefStaticModel( cName.c_str() );
// 				ReplaceModelId(m_staticModelRefList[nnewId],p);
// 				continue;
// 			}
// 			if (strstr(name,"qshuihu\\sht"))
// 			{
// 				int nStart = strstr(name,"qshuihu\\sht") - name;
// 				std::string cName(name);
// 				cName.erase(nStart,strlen("qshuihu\\sht"));
// 				cName.insert(nStart,"yanggx\\sht");
// 				int nnewId = PushRefStaticModel( cName.c_str() );
// 				ReplaceModelId(m_staticModelRefList[nnewId],p);
// 				continue;
// 			}
// 			if (strstr(name,"qshuihu\\yanggx\\sht"))
// 			{
// 				int nStart = strstr(name,"qshuihu\\yanggx\\sht") - name;
// 				std::string cName(name);
// 				cName.erase(nStart,strlen("qshuihu\\yanggx\\sht"));
// 				cName.insert(nStart,"yanggx\\sht");
// 				int nnewId = PushRefStaticModel( cName.c_str() );
// 				ReplaceModelId(m_staticModelRefList[nnewId],p);
// 				continue;
// 			}
// 			if (strstr(name,"qshuihu\\yanggx\\tree"))
// 			{
// 				int nStart = strstr(name,"qshuihu\\yanggx\\tree") - name;
// 				std::string cName(name);
// 				cName.erase(nStart,strlen("qshuihu\\yanggx\\tree"));
// 				cName.insert(nStart,"tree\\tree");
// 				int nnewId = PushRefStaticModel( cName.c_str() );
// 				ReplaceModelId(m_staticModelRefList[nnewId],p);
// 				continue;
// 			}
// 			if (strstr(name,"qshuihu\\yanggx\\glass"))
// 			{
// 				int nStart = strstr(name,"qshuihu\\yanggx\\glass") - name;
// 				std::string cName(name);
// 				cName.erase(nStart,strlen("qshuihu\\yanggx\\glass"));
// 				cName.insert(nStart,"GrassNormal\\grass");
// 				int nnewId = PushRefStaticModel( cName.c_str() );
// 				ReplaceModelId(m_staticModelRefList[nnewId],p);
// 				continue;
// 			}
			if (strstr(name,"sceneobject\\guanmu"))
			{
				int nStart = strstr(name,"sceneobject\\guanmu") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("sceneobject\\guanmu"));
				cName.insert(nStart,"sceneobject\\common\\guanmu");
				int nnewId = PushRefStaticModel( cName.c_str() );
				ReplaceModelId(m_staticModelRefList[nnewId],p);
				continue;
			}
			if (strstr(name,"sceneobject\\huo"))
			{
				int nStart = strstr(name,"sceneobject\\huo") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("sceneobject\\huo"));
				cName.insert(nStart,"sceneobject\\common\\huo");
				int nnewId = PushRefStaticModel( cName.c_str() );
				ReplaceModelId(m_staticModelRefList[nnewId],p);
				continue;
			}
			if (strstr(name,"sceneobject\\male"))
			{
				int nStart = strstr(name,"sceneobject\\male") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("sceneobject\\male"));
				cName.insert(nStart,"sceneobject\\common\\male");
				int nnewId = PushRefStaticModel( cName.c_str() );
				ReplaceModelId(m_staticModelRefList[nnewId],p);
				continue;
			}
			if (strstr(name,"sceneobject\\pubu"))
			{
				int nStart = strstr(name,"sceneobject\\pubu") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("sceneobject\\pubu"));
				cName.insert(nStart,"sceneobject\\common\\pubu");
				int nnewId = PushRefStaticModel( cName.c_str() );
				ReplaceModelId(m_staticModelRefList[nnewId],p);
				continue;
			}
			if (strstr(name,"sceneobject\\wujian"))
			{
				int nStart = strstr(name,"sceneobject\\wujian") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("sceneobject\\wujian"));
				cName.insert(nStart,"sceneobject\\common\\wujian");
				int nnewId = PushRefStaticModel( cName.c_str() );
				ReplaceModelId(m_staticModelRefList[nnewId],p);
				continue;
			}
			if (strstr(name,"sceneobject\\xuehua"))
			{
				int nStart = strstr(name,"sceneobject\\xuehua") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("sceneobject\\xuehua"));
				cName.insert(nStart,"sceneobject\\common\\xuehua");
				int nnewId = PushRefStaticModel( cName.c_str() );
				ReplaceModelId(m_staticModelRefList[nnewId],p);
				continue;
			}
			if (strstr(name,"sceneobject\\trees"))
			{
				int nStart = strstr(name,"sceneobject\\trees") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("sceneobject\\trees"));
				cName.insert(nStart,"sceneobject\\common\\trees");
				int nnewId = PushRefStaticModel( cName.c_str() );
				ReplaceModelId(m_staticModelRefList[nnewId],p);
				continue;
			}
			if (strstr(name,"sceneobject\\other"))
			{
				int nStart = strstr(name,"sceneobject\\other") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("sceneobject\\other"));
				cName.insert(nStart,"sceneobject\\common");
				int nnewId = PushRefStaticModel( cName.c_str() );
				ReplaceModelId(m_staticModelRefList[nnewId],p);
				continue;
			}
			strName.Empty();
		}

	}
	if(0)
	{//这里只是处理一个美术的路径失误
		int nSize = m_doodadRefList.size();
		for (int i = 0; i < nSize; ++i )
		{
			CWorldRes* p	= m_doodadRefList[i];
			const char* name = p->GetName();
			CString strName(name);
			strName = strName.MakeLower();
			name = strName.GetString();
			if (strstr(name,"sceneobject"))
			{
				int nStart = strstr(name,"sceneobject") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("sceneobject"));
				cName.insert(nStart,"sceneobject\\common");

				int nnewId = PushDoodad( cName.c_str() );
				ReplaceDoodadId(m_doodadRefList[nnewId],p);
				continue;
			}
			strName.Empty();
		}

	}
}

void CResEditMgr::CleanUnusedTexture()
{
	if(0)
	{
		int nSize = m_textureList.size();
		for (int i = 0; i < nSize; ++i )
		{
			CWorldRes* p	= (CWorldRes*)m_textureList[i];
			const char* name = p->GetName();
			if (strstr(name,"texture\\terrain\\cao_"))
			{
				int nStart = strstr(name,"texture\\terrain\\cao_") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("texture\\terrain\\cao_"));
				cName.insert(nStart,"terrain\\grass\\cao_");

				sInt32 newId = PushTexture(cName.c_str());
				ReplaceTextureId(newId,i);
				continue;
			} 
			else if (strstr(name,"texture\\terrain\\lu_"))
			{
				int nStart = strstr(name,"texture\\terrain\\lu_") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("texture\\terrain\\lu_"));
				cName.insert(nStart,"terrain\\road\\lu_");

				sInt32 newId = PushTexture(cName.c_str());
				ReplaceTextureId(newId,i);
				continue;
			}
			else if (strstr(name,"texture\\terrain\\sh"))
			{
				int nStart = strstr(name,"texture\\terrain\\sh") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("texture\\terrain\\sh"));
				cName.insert(nStart,"terrain\\rock\\sh");

				sInt32 newId = PushTexture(cName.c_str());
				ReplaceTextureId(newId,i);
				continue;
			}
			else if (strstr(name,"texture\\terrain\\t"))
			{
				int nStart = strstr(name,"texture\\terrain\\t") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("texture\\terrain\\t"));
				cName.insert(nStart,"terrain\\T\\t");

				sInt32 newId = PushTexture(cName.c_str());
				ReplaceTextureId(newId,i);
				continue;
			}
			else if (strstr(name,"texture\\terrain\\z"))
			{
				int nStart = strstr(name,"texture\\terrain\\z") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("texture\\terrain\\z"));
				cName.insert(nStart,"terrain\\Z\\z");

				sInt32 newId = PushTexture(cName.c_str());
				ReplaceTextureId(newId,i);
				continue;
			}
			else if (strstr(name,"texture\\terrain"))
			{
				int nStart = strstr(name,"texture\\terrain") - name;
				std::string cName(name);
				cName.erase(nStart,strlen("texture\\terrain"));
				cName.insert(nStart,"terrain\\other");

				sInt32 newId = PushTexture(cName.c_str());
				ReplaceTextureId(newId,i);
				continue;
			}
		}
		std::vector<CWorldRes*>::iterator mIt = m_textureList.begin();
		while(mIt!=m_textureList.end()) 
		{
			CWorldRes* pRes	= (CWorldRes*)(*mIt);
			sInt32 delId			= pRes->GetId();
			if (!FindTextureReference(delId))
			{
				mIt = m_textureList.erase( mIt );
				SAFE_DELETE( pRes );
				for( sInt32 i=0; i< m_textureList.size(); i++ ) {
					CWorldRes* p = (CWorldRes*)m_textureList[i];
					if( p->GetId() == delId ) {
						Assert( false );
					}
					else if( p->GetId() > delId ){
						p->GetId()--;
					}
					Assert( p->GetId() == i );
				}
				for( sInt32 i=0; i<(m_bindTile->GetChunkTotal()); i++ ) {
					CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
					for (sInt32 j = 0; j < worldChunk->GetLayerCount(); j++ )
					{
						if (worldChunk->m_texture[j] > delId)
						{
							--worldChunk->m_texture[j];
						}
					}
				}	 
			}
			else
			{
				++mIt;
			}
		}
	}
}

void CResEditMgr::CleanUnusedModel(bool isGameWtd)
{
	std::vector<CWorldRes*>::iterator mIt = m_staticModelRefList.begin();
	for(;mIt!=m_staticModelRefList.end();) 
	{
		CWorldRes* pRes	= (CWorldRes*)(*mIt);
		sInt32 delId			= pRes->GetId();

		CStringA modelRealName(m_staticModelRefList[delId]->GetName());
		CStringA childModelName;
		int speratorPos = modelRealName.Find('|');
		if (-1 != speratorPos)
		{
			childModelName = modelRealName.Mid(speratorPos + 1);
			modelRealName.Truncate(speratorPos );
		}
		CNdlStaticModelRes* pModelRes	= dynamic_cast<CNdlStaticModelRes*>(m_worldBuffer->GetGlobalResMgr()->FindRefStaticModel(modelRealName));

		if( pRes->RefCount() == 0 ||  (isGameWtd )) 
		{
			mIt = m_staticModelRefList.erase( mIt );
			m_worldBuffer->GetGlobalResMgr()->UnloadRefModel(pRes->GetName());

			SAFE_DELETE( pRes );

			for( sInt32 i=0; i< m_staticModelRefList.size(); i++ ) {
				CWorldRes* p = (CWorldRes*)m_staticModelRefList[i];
				if( p->GetId() == delId ) {
					Assert( false );
				}
				else if( p->GetId() > delId ){
					p->GetId()--;
				}
				Assert( p->GetId() == i );
			}
			DeleteStaticModel(delId);
		}
		else {
			++mIt;
		}
	}

	std::vector<TObjectInfo*>::iterator it = m_staticModelList.begin();
	int index = 0;
	for(;it!=m_staticModelList.end();) 
	{
		if( !FindStaticModelInUsed( index ) ) 
		{
			it = m_staticModelList.erase(it);
			CleanTileModelId(index);
			continue;
		}
		else{
			((TObjectEditInfo*)(*it))->SyncOffset2WorldPos();
			++it;
			++index;
		}
	}
}

void CResEditMgr::CleanUnusedDoodad()
{
	std::vector<CWorldRes*>::iterator mIt = m_doodadRefList.begin();
	for(;mIt!=m_doodadRefList.end();) {
		CWorldRes* pRes	= (CWorldRes*)(*mIt);
		sInt32 delId			= pRes->GetId();
		if( pRes->RefCount() == 0 ) {
			mIt = m_doodadRefList.erase( mIt );
			SAFE_DELETE( pRes );

			for( sInt32 i=0; i< m_doodadRefList.size(); i++ ) {
				CWorldRes* p = (CWorldRes*)m_doodadRefList[i];
				if( p->GetId() == delId ) {
					Assert( false );
				}
				else if( p->GetId() > delId ){
					p->GetId()--;
				}
				Assert( p->GetId() == i );
			}
			CleanTileDoodadId(delId);
		}
		else {
			++mIt;
		}
	}
}
bool CResEditMgr::CleanTileModelId( sInt32 delId )
{
	for( int i = 0; i < m_bindTile->GetChunkTotal(); i++ ) {
		CWorldChunk* worldChunk				= m_bindTile->GetChunk(i);
		std::vector<sInt32>::iterator cIt	= worldChunk->m_staticModelList.begin();
		for(;cIt!=worldChunk->m_staticModelList.end();) {
			sInt32 p = *cIt;
			if( p == delId ) {
				cIt = worldChunk->m_staticModelList.erase( cIt );
			}
			else if( p > delId ){
				*cIt = p-1;
				cIt++;
			}
			else {
				cIt++;
			}
		}
	}
	return true;
}

void CResEditMgr::_DeleteIdFromList( std::vector< CWorldRes* >& list, sInt32 delId )
{
	std::vector<CWorldRes*>::iterator it = list.begin();
	for(;it!=list.end();) {
		CWorldRes* p = (*it);
		if( p->GetId() < 0 ) {
			Trace( "INVALID resource name (%s), id(%d) ! \n" ,p->GetName(),p->GetId());
		}
		if( p->GetId() == delId ) {
			SAFE_DELETE( p );
			it = list.erase(it);
			continue;
		}
		else if( p->GetId() > delId ){
			--p->GetId();
			Assert( p->GetId() >= 0 );
		}
		++it;
	}

}

void CResEditMgr::DeleteEnvRes( sInt32 delId )
{
	_DeleteIdFromList(GetEnvResList(),delId);

	for( int i = 0; i < m_bindTile->GetChunkTotal(); i++ )
	{
		CWorldChunk* worldChunk				= m_bindTile->GetChunk(i);
		if (worldChunk->m_envId == delId)
		{
			worldChunk->m_envId = RES_INVALID_ID;
		}
		else if(worldChunk->m_envId > delId)
		{
			--worldChunk->m_envId;
		}
	}
}

void CResEditMgr::DeleteZoneRes( sInt32 delId )
{
	_DeleteIdFromList(GetZoneResList(),delId);

	for( int i = 0; i < m_bindTile->GetChunkTotal(); i++ )
	{
		CWorldChunk* worldChunk				= m_bindTile->GetChunk(i);
		if (worldChunk->m_zoneId == delId)
		{
			worldChunk->m_zoneId = RES_INVALID_ID;
		}
		else if(worldChunk->m_zoneId > delId)
		{
			--worldChunk->m_zoneId;
		}
	}
}

void CResEditMgr::DeleteLightRes( sInt32 delId )
{
	_DeleteIdFromList(GetLightList(),delId);
	std::vector<CWorldRes*>::iterator it = GetEnvResList().begin();
	for(;it!=GetEnvResList().end();++it) 
	{
		CNdlEnvRes* pRes = (CNdlEnvRes*) (*it);
		if (pRes->GetLightId() == delId)
		{
			pRes->SetLightId(RES_INVALID_ID);
		}
		if (pRes->GetLightId() > delId)
		{
			pRes->SetLightId(pRes->GetLightId() - 1);
		}
	}
}

void CResEditMgr::DeleteFogRes( sInt32 delId )
{
	_DeleteIdFromList(GetFogList(),delId);
	std::vector<CWorldRes*>::iterator it = GetEnvResList().begin();
	for(;it!=GetEnvResList().end();++it) 
	{
		CNdlEnvRes* pRes = (CNdlEnvRes*) (*it);
		if (pRes->GetFogId() == delId)
		{
			pRes->SetFogId(RES_INVALID_ID);
		}
		if (pRes->GetFogId() > delId)
		{
			pRes->SetFogId(pRes->GetFogId() - 1);
		}
	}

}
void CResEditMgr::DeleteStaticModel( sInt32 delId )
{
	std::vector<TObjectInfo*>::iterator it = m_staticModelList.begin();
	int index = 0;
	for(;it!=m_staticModelList.end();) {
		TObjectInfo* p = (*it);
		if( p->id < 0 ) {
			Trace( "INVALID Model id! \n" );
		}
		if( p->id == delId ) {
			SafeDeleteObjInfo( p );
			it = m_staticModelList.erase(it);
			CleanTileModelId(index);
			continue;
		}
		else if( p->id > delId ){
			p->id--;
			Assert( p->id >= 0 );
		}
		++it;
		++index;
	}
}

bool CResEditMgr::CleanTileDoodadId( sInt32 delId )
{
	for( int i = 0; i < m_bindTile->GetChunkTotal(); i++ ) {
		CWorldChunk* worldChunk				= m_bindTile->GetChunk(i);
		std::vector<TDoodadLevelInfo*>::iterator cIt	= worldChunk->m_doodadList.begin();
		for(;cIt!=worldChunk->m_doodadList.end();) {
			TDoodadLevelInfo* p = *cIt;
			if( p->mdoodadId == delId ) {
				Assert(0);//理论上来讲，不应该有相等的了。
				cIt = worldChunk->m_doodadList.erase( cIt );
			}
			else if( p->mdoodadId > delId ){
				--p->mdoodadId;
				++cIt;
			}
			else {
				++cIt;
			}
		}
	}
	return true;

}

bool CResEditMgr::ReplaceModelId( CWorldRes* nnewRes,CWorldRes* noldRes )
{
	std::vector<TObjectInfo*>::iterator it = m_staticModelList.begin();
	for(;it!=m_staticModelList.end();) {
		TObjectInfo* p = (*it);
		if( p->id < 0 ) {
			Trace( "INVALID Model id! \n" );
		}
		if( p->id == noldRes->GetId() ) {
			p->id = nnewRes->GetId();
			GenerateObjInfo(p);
			nnewRes->IncRefCount();
			noldRes->DecRefCount();
		}
		++it;
	}
	return true;
}

bool CResEditMgr::RefreshChunkShapeVertexColor( sInt32 shapeId, sInt32 VertId,COLORREF niColor,bool isInVertex )
{
	CNdlShapeRes* res = Shape(shapeId);
	Assert( NULL != res );
	Assert( res->GetId() == shapeId );

	sInt32 nMul = isInVertex?(VertId/9):(VertId/8);
	sInt32 id = nMul*(8+9);
	if (isInVertex)
	{
		id += VertId%9;
	}
	else
	{
		id += 9 + VertId%8;
	}
	Assert( id < 9*9 + 8*8 );
	FTerrainVertexSpecial* pDatas = 0;
	if (SUCCEEDED(res->m_pVB->Lock(0, CHUNK_VERTEX_NUMBER * sizeof(FTerrainVertexSpecial), (void**)&pDatas, 0)))
	{
		FTerrainVertexSpecial& thisVertex = pDatas[id];

		NiColor color;
		DWORD alpha = niColor >> 24;
		ConvertRGB2NiColor(niColor,color);
		thisVertex.color		= D3DXCOLOR(color.r, color.g, color.b, ((float)alpha)/255);
		res->m_pVB->Unlock();
	}
	return true;
}





void CResEditMgr::DeleteTransport( sInt32 id )
{
	//先判断要删除的点是那种类型点, 用来后面做判断
	CTransportResBase* pDel = Transport(id);
	if (pDel == NULL) { return; }

	int nType = 0;  //初始传送点
	if (!pDel->IsTransport())
	{
		CTargetRes* pDelTarget = (CTargetRes*) pDel;
		if (!pDelTarget->IsRelive())
		{
			nType = 1;  //目标点
		}
		else
		{
			nType = 2;	//重生点
		}
	}

	for (sInt32 i = id + 1; i < m_transportList.size(); ++i)
	{
		CTransportResBase* pRes = Transport(i);
		if (pRes == NULL) { continue; }
		pRes->SetId(pRes->GetId() - 1);
		
		if (pRes->IsTransport())
		{
			if (nType == 0)
			{
				CTransportRes* pTranport  = (CTransportRes*) pRes;
				pTranport->SetEntranceId(pTranport->GetEntranceId() - 1);
			}
		}
		else 
		{
			CTargetRes* pTarget = (CTargetRes*) pRes;
			if (nType == 1 && !pTarget->IsRelive())
			{
				pTarget->SetNtargetID(pTarget->GetNtargetID() - 1);
			}
			else if (nType == 2 && pTarget->IsRelive())
			{
				pTarget->SetReliveId(pTarget->GetReliveId() - 1);
			}
		}
	}
	SAFE_DELETE( m_transportList[id] );
	m_transportList.erase(m_transportList.begin() + id);
}




void CResEditMgr::CloneModelInfo( CResMgr* pSrcMgr,sInt32* chunk )
{
	//model begin
	{
		for (size_t i = 0; i < pSrcMgr->GetStaticModelList().size(); ++i )
		{
			TObjectInfo* pInfo = pSrcMgr->GetStaticModel(i);
			CWorldRes* pRes = pSrcMgr->GetStaticModelRefList()[pInfo->id];
			sInt32 refId = PushRefStaticModel(pRes->GetName());
			flt32 pos[3];
			pos[0] = pInfo->pos[0] + chunk[0]*WORLD_CHUNKSIZE;
			pos[1] = pInfo->pos[1] + chunk[1]*WORLD_CHUNKSIZE;
			pos[2] = pInfo->pos[2];
			if((pos[0] > -0.001f) 
				&& (pos[0] < (m_bindTile->GetWidth() + 0.001f))
				&& (pos[1] > -0.001f) 
				&& (pos[1] < m_bindTile->GetDepth() + 0.001f))
			{
				int newId = PushStaticModel(refId,pos,pInfo->offset,pInfo->rotate,pInfo->scale);
// 				TObjectInfo* pNewInfo = GetStaticModel(newId);
// 				GenerateObjInfo(pNewInfo);
			}
		}
// 		m_bindTile->CreateFloorAndCollision();
	}
	//model end


}


void CResEditMgr::AttachAllSoundPoint()
{
	for (int i = 0; i < GetSoundPointCount(); ++i)
	{
		CSoundPointEditRes* pRes = (CSoundPointEditRes*)SoundPoint(i);
		pRes->ShowSoundPointPoint(true);
	}
}

void CResEditMgr::DetachAllSoundPoint()
{
	for (int i = 0; i < GetSoundPointCount(); ++i)
	{
		CSoundPointEditRes* pRes = (CSoundPointEditRes*)SoundPoint(i);
		pRes->DetachModel();
	}

}

void CResEditMgr::DeleteMonsterQuad( sInt32 id )
{
	for (sInt32 i = id + 1; i < m_monsterQuadList.size(); ++i)
	{
		CMonsterQuadRes* pRes = MonsterQuad(i);
		pRes->SetId(pRes->GetId() - 1);
	}
	SAFE_DELETE( m_monsterQuadList[id] );
	m_monsterQuadList.erase(m_monsterQuadList.begin() + id);

}
CMonsterQuadRes* CResEditMgr::MonsterQuad( sInt32 id )
{
	if( (id < 0) || (id >= m_monsterQuadList.size()) ) {
		return NULL;
	}
	return (CMonsterQuadRes*)m_monsterQuadList[id];
}

void CResEditMgr::CleanMonsterQuad()
{
	for(size_t i = 0; i < m_monsterQuadList.size(); i++ ) {
		SAFE_DELETE( m_monsterQuadList[i] );
	}
	m_monsterQuadList.clear();

}
sInt32 CResEditMgr::GetMonsterQuadCount() const
{
	return m_monsterQuadList.size();
}


CMonsterQuadRes* CResEditMgr::PushMonsterQuad( float top,float left,float right,float bottom)
{
	CMonsterQuadRes* pRes = MeNew CMonsterQuadRes;
	pRes->m_fLeft = left;
	pRes->m_fRight = right;
	pRes->m_fBottom = bottom;
	pRes->m_fTop = top;
	pRes->SetId(m_monsterQuadList.size());

	m_monsterQuadList.push_back(pRes);
	return pRes;
}

CMonsterQuadRes *CResEditMgr::CreateMonsterQuadRes(float top,float left,float right,float bottom)
{
	CMonsterQuadRes* pRes = MeNew CMonsterQuadRes;
	pRes->m_fLeft = left;
	pRes->m_fRight = right;
	pRes->m_fBottom = bottom;
	pRes->m_fTop = top;
	//pRes->SetId(m_monsterQuadList.size());
	return pRes;
}

bool CResEditMgr::PushMonsterQuad(CMonsterQuadRes *pRes)
{
	assert(pRes != NULL);
	if(NULL == pRes)
		return false;

	pRes->SetId(m_monsterQuadList.size());
	m_monsterQuadList.push_back(pRes);

	return true;
}

bool CResEditMgr::PopMonsterQuad(CMonsterQuadRes *pRes)
{
	for(std::vector<CMonsterQuadRes *>::iterator it= m_monsterQuadList.begin(); it != m_monsterQuadList.end(); ++it)
	{
		if(*it == pRes)
		{
			m_monsterQuadList.erase(it);
			return true;
		}
	}

	return false;
}

void CResEditMgr::AttachAllMonsterQuad()
{
	for (int i = 0; i < GetMonsterQuadCount(); ++i)
	{
		CMonsterQuadRes* pRes = MonsterQuad(i);
		pRes->AttachModelToNdlHelper();
	}
}

void CResEditMgr::DetachAllMonsterQuad()
{
	for (int i = 0; i < GetMonsterQuadCount(); ++i)
	{
		CMonsterQuadRes *pRes = MonsterQuad(i);
		pRes->DetachModelFromNdlHelper();
	}
}

//飞行路线开始


void CResEditMgr::AttachAllFlyRoute()
{
	for (int i = 0; i < GetNPCRouteCount(); ++i)
	{
		CNPCRouteRes* pRes = NPCRoute(i);
		if (!pRes->IsFlyRoute())
		{
			continue;
		}	
		pRes->ShowRoutePoint(true);
	}
}

void CResEditMgr::DetachAllFlyRoute()
{
	for (int i = 0; i < GetNPCRouteCount(); ++i)
	{
		CNPCRouteRes* pRes = NPCRoute(i);
		if (!pRes->IsFlyRoute())
		{
			continue;
		}	
		pRes->ClearModel();
	}

}

CNPCRouteRes* CResEditMgr::CreateRoute(const char *pName_, bool bFlyRoute_)
{
	CNPCRouteRes* pRes = MeNew CNPCRouteRes;
	if (pName_)
	{
		pRes->SetName(pName_);
	}

	pRes->SetFlyRoute(bFlyRoute_);

	return pRes;
}

bool CResEditMgr::PushRoute(CNPCRouteRes *_pRoute_)
{
	assert(_pRoute_ != NULL);
	if(NULL == _pRoute_)
		return false;

	_pRoute_->SetId(m_NPCRouteList.size());
	m_NPCRouteList.push_back(_pRoute_);

	return true;
}

bool CResEditMgr::PopRoute(CNPCRouteRes *pRoute_)
{
	for(std::vector<CNPCRouteRes *>::iterator it= m_NPCRouteList.begin(); it != m_NPCRouteList.end(); ++it)
	{
		if(*it == pRoute_)
		{
			m_NPCRouteList.erase(it);
			return true;
		}
	}

	return false;
}

CNPCRouteRes* CResEditMgr::PushFlyRoute(const char* pName)
{
	CNPCRouteRes* pRes = MeNew CNPCRouteRes;
	if (pName)
	{
		pRes->SetName(pName);
	}
	pRes->SetFlyRoute(true);
	pRes->SetId(m_NPCRouteList.size());
	m_NPCRouteList.push_back(pRes);
	return pRes;
}

void CResEditMgr::AttachAllNPCRoute()
{
	for (int i = 0; i < GetNPCRouteCount(); ++i)
	{
		CNPCRouteRes* pRes = NPCRoute(i);
		pRes->ShowRoutePoint(true);
	}
}

void CResEditMgr::DetachAllNPCRoute()
{
	for (int i = 0; i < GetNPCRouteCount(); ++i)
	{
		CNPCRouteRes* pRes = NPCRoute(i);
		pRes->ClearModel();
	}

}

void CResEditMgr::DeleteNPCRoute( sInt32 id )
{
	for (sInt32 i = id + 1; i < m_NPCRouteList.size(); ++i)
	{
		CNPCRouteRes* pRes = NPCRoute(i);
		pRes->SetId(pRes->GetId() - 1);
	}
	SAFE_DELETE( m_NPCRouteList[id] );
	m_NPCRouteList.erase(m_NPCRouteList.begin() + id);

}
CNPCRouteRes* CResEditMgr::NPCRoute( sInt32 id )
{
	if( (id < 0) || (id >= m_NPCRouteList.size()) ) {
		return NULL;
	}
	return (CNPCRouteRes*)m_NPCRouteList[id];
}

void CResEditMgr::CleanNPCRoute()
{
	for(size_t i = 0; i < m_NPCRouteList.size(); i++ ) {
		SAFE_DELETE( m_NPCRouteList[i] );
	}
	m_NPCRouteList.clear();

}
sInt32 CResEditMgr::GetNPCRouteCount() const
{
	return m_NPCRouteList.size();
}


CNPCRouteRes* CResEditMgr::PushNPCRoute(const char* pName)
{
	CNPCRouteRes* pRes = MeNew CNPCRouteRes;
	if (pName)
	{
		pRes->SetName(pName);
	}
	pRes->SetFlyRoute(false);
	pRes->SetId(m_NPCRouteList.size());
	m_NPCRouteList.push_back(pRes);
	return pRes;
}


void CResEditMgr::RefreshSpecialChunkLayer( CWorldChunk* worldChunk ,sInt32 nLevel)
{
	Assert( 0 < worldChunk->m_layerCount );

	Assert( RES_INVALID_ID != worldChunk->m_shape );
	CNdlShapeRes * shape = Shape(worldChunk->m_shape);
	FTerrainVertexSpecial* pDatas = 0;
	if (SUCCEEDED(shape->m_pVB->Lock(0, CHUNK_VERTEX_NUMBER * sizeof(FTerrainVertexSpecial), (void**)&pDatas, 0)))
	{
		CalChunkSpecialUV(worldChunk, pDatas,nLevel);
		shape->m_pVB->Unlock();
	}
	RefreshChunkMask(worldChunk);
	{
		{
			CWorldChunk* pRight = m_bindTile->GetChunk(worldChunk->m_chunk[0] + 1,worldChunk->m_chunk[1]);
			if (pRight)
			{
				int nMatchTexture = pRight->IsExistSpecialTexture(worldChunk->m_texture[nLevel]);
				if (-1 != nMatchTexture && pRight->GetTexInfo(nMatchTexture).IsLeftAlign())
				{
					RefreshSpecialChunkLayer(pRight,nMatchTexture);
				}
			}
		}
		{
			CWorldChunk* pUp = m_bindTile->GetChunk(worldChunk->m_chunk[0] ,worldChunk->m_chunk[1]+ 1);
			if (pUp)
			{
				int nMatchTexture = pUp->IsExistSpecialTexture(worldChunk->m_texture[nLevel]);
				if (-1 != nMatchTexture && pUp->GetTexInfo(nMatchTexture).IsLeftAlign())
				{
					RefreshSpecialChunkLayer(pUp,nMatchTexture);
				}
			}
		}
	}
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
}

bool CResEditMgr::SetSpecialLayerAlign( CWorldChunk* worldChunk,bool flag ,sInt32 nLevel)
{
	
	if (flag)
	{
		CWorldChunk* pAlign = NULL;
		{//向左
			pAlign = m_bindTile->GetChunk(worldChunk->m_chunk[0] - 1,worldChunk->m_chunk[1]);
			if (pAlign)
			{
				int nMatchTexture = pAlign->IsExistSpecialTexture(worldChunk->m_texture[nLevel]);
				if (-1 != nMatchTexture)
				{
					worldChunk->GetTexInfo(nLevel).m_nX = TTextureInfo::LeftAlign;
				}
				else
					pAlign = NULL;
			}
			else
			{
				pAlign = NULL;
			}
		}
		if (NULL == pAlign)
		{//向下
			pAlign = m_bindTile->GetChunk(worldChunk->m_chunk[0],worldChunk->m_chunk[1] - 1);
			if (pAlign)
			{
				int nMatchTexture = pAlign->IsExistSpecialTexture(worldChunk->m_texture[nLevel]);
				if (-1 != nMatchTexture)
				{
					worldChunk->GetTexInfo(nLevel).m_nX = TTextureInfo::DownAlign;
				}
				else
					pAlign = NULL;
			}
			else
			{
				pAlign = NULL;
			}
		}
		if (NULL == pAlign)
		{
			return false;
		}
	}
	else
	{
		TTextureInfo& ptexInfo = worldChunk->GetTexInfo(nLevel);
		sInt32 chunkX = 0;
		sInt32 chunkY = 0;
		TTextureInfo* alignTexInfo = GetAlignChunk(worldChunk,chunkX,chunkY,nLevel);
		if (!alignTexInfo)
		{
			ptexInfo.Reset();
			return false;
		}
		ptexInfo.m_ScaleX = alignTexInfo->m_ScaleX;
		ptexInfo.m_ScaleY = alignTexInfo->m_ScaleY;
		ptexInfo.m_angle  = alignTexInfo->m_angle;

		flt32 deltaX = 0.f;
		flt32 deltaY = 0.f;
		Vector2 tex(3*chunkX ,3*chunkY);
		flt32 Atan = GetAtan(tex);
		flt32 angle = Atan + ptexInfo.m_angle*PI/180.f;
		deltaX = alignTexInfo->m_nX/(float)TTextureInfo::MAXOFFSET + tex.length()*cos(angle)*TTextureInfo::SCALECOAF/((float)alignTexInfo->m_ScaleX);
		deltaY = alignTexInfo->m_nY/(float)TTextureInfo::MAXOFFSET + tex.length()*sin(angle)*TTextureInfo::SCALECOAF/((float)alignTexInfo->m_ScaleY);

		ptexInfo.m_nX		= (ZnFloat2Int(deltaX*TTextureInfo::MAXOFFSET))%TTextureInfo::MAXOFFSET;
		ptexInfo.m_nY		= (ZnFloat2Int(deltaY*TTextureInfo::MAXOFFSET))%TTextureInfo::MAXOFFSET;
	}

	RefreshSpecialChunkLayer(worldChunk,nLevel);

	return true;
}
bool CResEditMgr::ReplaceChunkTexture( CWorldChunk* worldChunk, sInt32 layerId, const char* textureName)
{
	sInt32 textureId = PushTexture( textureName );

	return ReplaceChunkTexture(worldChunk,layerId,textureId);

}
bool CResEditMgr::ReplaceTexture( sInt32 texId, const char* textureName ,CWorldChunk** ppchunk )
{
	sInt32 textureId = PushTexture( textureName );
	if (textureId == texId)
	{
		return true;
	}
	for( sInt32 i=0; i<(m_bindTile->GetChunkTotal()); i++ ) 
	{
		CWorldChunk* worldChunk = m_bindTile->GetChunk(i);
		bool bExist = false;
		for(size_t j = 0; j < worldChunk->GetLayerCount(); ++j)
		{
			if ((worldChunk->GetTexture(j)) == textureId)
			{
				bExist = true;
				break;
			}
		}
		for(size_t j = 0; j < worldChunk->GetLayerCount(); ++j)
		{
			if ((worldChunk->GetTexture(j)) == texId)
			{
				if (bExist)
				{
					*ppchunk = worldChunk;
					return false;					
				}
				else
				{
					ReplaceChunkTextrueId(worldChunk,j,textureId);
				}
				break;
			}
		}
	}
	return true;
}
bool CResEditMgr::ReplaceChunkTexture( CWorldChunk* worldChunk, sInt32 layerId, sInt32 textureId )
{
	if (worldChunk->m_texture[layerId] == textureId)
	{
		return false;
	}
	if (worldChunk->GetTexInfo(layerId).IsAlign() )
	{
		SetSpecialLayerAlign(worldChunk,false,layerId);
	}
//	sInt32 lastTexture = worldChunk->m_texture[layerId];
	{
		CWorldChunk* pRight = m_bindTile->GetChunk(worldChunk->m_chunk[0] + 1,worldChunk->m_chunk[1]);
		if (pRight)
		{
			int nMatchTexture = pRight->IsExistSpecialTexture(worldChunk->m_texture[layerId]);
			if (-1 != nMatchTexture && pRight->GetTexInfo(nMatchTexture).IsLeftAlign())
			{
				SetSpecialLayerAlign(pRight,false,nMatchTexture);
// 				RefreshSpecialChunkLayer(pRight,nMatchTexture);
			}
		}
	}
	{
		CWorldChunk* pUp = m_bindTile->GetChunk(worldChunk->m_chunk[0] ,worldChunk->m_chunk[1]+ 1);
		if (pUp)
		{
			int nMatchTexture = pUp->IsExistSpecialTexture(worldChunk->m_texture[layerId]);
			if (-1 != nMatchTexture && pUp->GetTexInfo(nMatchTexture).IsDownAlign())
			{
				SetSpecialLayerAlign(pUp,false,nMatchTexture);
// 				RefreshSpecialChunkLayer(pUp,nMatchTexture);
			}
		}
	}
	ReplaceChunkTextrueId(worldChunk,layerId,textureId);


	UpdateChunkMask( worldChunk);

	return true;
}
bool CResEditMgr::RefreshNormal()
{

	for (int i = 0; i < m_bindTile->GetChunkTotal(); ++i)
	{
		CWorldChunk* pChunk = m_bindTile->GetChunk(i);
		RefreshChunkShapeNormal(i,pChunk->m_vertexOut,pChunk->m_vertexIn);
	}
	return true;
}



sInt32 CResEditMgr::PushRoad( const uInt8* shadowMap )
{
	CNdlAlphaRes* res	= MeNew CNdlAlphaRes();
	res->SetId(m_roadList.size());
// 	sprintf_s( res->m_name, "Shadow_%d", res->GetId() );
	if( NULL != shadowMap ) 
	{
		memcpy(res->GetMaskData(),shadowMap,WORLD_TILE_CHUNK_ATOM_NUM*32*sizeof(uAlphaBit));
	}
	else
	{
		memset( res->GetMaskData(), 0xFF, WORLD_TILE_CHUNK_ATOM_NUM*32*sizeof(uAlphaBit) );
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
// 	else 
// 	{
// 		memset( res->m_maskData, 0xFF, WORLD_TILE_CHUNK_ATOM_NUM*WORLD_TILE_CHUNK_ATOM_NUM*sizeof(uAlphaBit) );
// 	}
	m_roadList.push_back( res );

	return res->GetId();

}

sInt32 CResEditMgr::GetRoadCount() const
{
	return m_roadList.size();
}
CNdlAlphaRes* CResEditMgr::GetRoad( sInt32 id )
{
	if( id >= 0 && id < m_roadList.size() )
	{
		CNdlAlphaRes* res = (CNdlAlphaRes*)m_roadList[id];
		Assert( res->GetId() == id );
		return res;
	}
	return (CNdlAlphaRes*)m_roadList[0];
}

void CResEditMgr::SetShadowShowType( int val )
{
	if (m_ShadowShowType == val)
	{
		return;
	}
	m_ShadowShowType = val;
	if(m_ShadowShowType == ePathFindMap)
	{
		m_bindTile->ReachableMap();
		if (!m_bindTile->IsLoadReachableMap())
		{
			m_ShadowShowType = eShadow;
			AfxMessageBox("寻路图(*.map)文件不存在, 请右击地图并选择生成寻路图", MB_OK);
		}

	}
	RefreshAllChunkTexture();
}

bool CResEditMgr::RefreshAllChunkTexture()
{
	for( int chunkX = 0; chunkX<m_bindTile->GetRowColumn()[0]; chunkX++ )
	{
		for( int chunkY = 0; chunkY<m_bindTile->GetRowColumn()[1]; chunkY++ )
		{
			CWorldChunk* pChunk = m_bindTile->GetChunk(chunkX,chunkY);
			UpdateChunkMask(pChunk);
		}
	}
	return true;
}






sInt32		CResEditMgr::GetNpcCount() const
{
    return m_vecSet.size();
}



void	CResEditMgr::AttachAllNpc()
{
    int nSize = m_vecSet.size();
    for (int i = 0;i < nSize;++i)
    {
        CNpcRes* pRes = m_vecSet[i];
        if(pRes != NULL)
            pRes->AttachModel();
    }
}

void CResEditMgr::DetachAllNpc()
{
    int nSize = m_vecSet.size();
    for (int i = 0;i < nSize;++i)
    {
        CNpcRes* pRes = m_vecSet[i];
        if(pRes != NULL)
            pRes->DetachModel();
    }
}

CNpcRes* CResEditMgr::GetNpcRes(int nValue)
{
//     assert(nValue >= 0&&nValue < m_vecSet.size());
//     return m_vecSet[nValue];

	if(nValue >= 0&&nValue < m_vecSet.size())
		return m_vecSet[nValue];

	return NULL;
}

CNpcRes* CResEditMgr::GetNpcResByNpcId(int id_)
{
	std::vector<CNpcRes*>::iterator it  = m_vecSet.begin();
	std::vector<CNpcRes*>::iterator end = m_vecSet.end();
	for (;it != end;++it)
	{
		assert(*it != NULL);
		if((*it)->GetNpcId() == id_)
		{
			return *it;
		}
	}

	return NULL;
}

CNpcRes* CResEditMgr::AddNpc(float x,float y,float z)
{
    CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
    if(pTile == NULL)
        return NULL;

    NpcInfo::Npc npc;
    npc.x = x;
    npc.y = y;
    npc.z = z;
    npc.modelId = 3001;
    npc.name = "掉落高等宝箱";
    npc.id   = 0;
    npc.mapId = pTile->GetMapId();
    npc.movePath = -1;
    npc.direction = 0;
    npc.canChangeDirection = 1;
    npc.triggerScript = "";
    npc.actionScript = "";
    npc.level = 1;
    npc.type = 1;
    npc.isMiniShow = 1;
	npc.isWorldShow = 1;
    npc.isCollision = 0;
    npc.title = "";
    npc.tip   = "";
    npc.strHeadPicture = "";
    npc.bodyScale = 1.0f;

    if(theNpcInfo.GetNpcCount() > 0)
    {
        NpcInfo::Npcs::reverse_iterator it = theNpcInfo.npcs_.rbegin();
        npc.id = it->second.id + 1;
    }
    else
        npc.id = 1;

    theNpcInfo.AddNpc(npc);  //增加NPC

    NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(npc.id);
    assert(pNpc != NULL);

    CNpcRes *pRes = MeNew CNpcRes;
    pRes->SetNpc(pNpc);
    pRes->SetResId(m_vecSet.size());
    m_vecSet.push_back(pRes);

    return pRes;
}

//added by zilong. 2011-03-25. ----------------------------------------------
//增加接口注释。
//要注意这个接口中的pNpc，指的是从theNpcInfo中取出的地址，否则会出错。
//感觉这个接口非常容易引起误导。
//added by zilong. end.------------------------------------------------------
CNpcRes* CResEditMgr::AddNpc(NpcInfo::Npc *pNpc)
{
    CNpcRes *pRes = MeNew CNpcRes;
    pRes->SetNpc(pNpc);
    pRes->SetResId(m_vecSet.size());
    m_vecSet.push_back(pRes);

	return pRes;
}

bool CResEditMgr::InitNpc(float x,float y,float z, NpcInfo::Npc &_npc)
{
	CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
	if(pTile == NULL)
		return false;

	_npc.x = x;
	_npc.y = y;
	_npc.z = z;
	_npc.modelId = 3001;
	_npc.name = "掉落高等宝箱";
	_npc.id   = 0;
	_npc.mapId = pTile->GetMapId();
	_npc.movePath = -1;
	_npc.direction = 0;
	_npc.canChangeDirection = 1;
	_npc.triggerScript = "";
	_npc.actionScript = "";
	_npc.level = 1;
	_npc.type = 1;
	_npc.isMiniShow = 1;
	_npc.isWorldShow = 1;
	_npc.isCollision = 0;
	_npc.title = "";
	_npc.tip   = "";
	_npc.strHeadPicture = "";
	_npc.bodyScale = 1.0f;

	if(theNpcInfo.GetNpcCount() > 0)
	{
		NpcInfo::Npcs::reverse_iterator it = theNpcInfo.npcs_.rbegin();
		_npc.id = it->second.id + 1;
	}
	else
		_npc.id = 1;

	return true;
}

void  CResEditMgr::DelNpc(int nValue,int mapId)
{
    if(mapId == -1)
        return;

    int npcId = 9999999;
    std::vector<CNpcRes*>::iterator it  = m_vecSet.begin();
    std::vector<CNpcRes*>::iterator end = m_vecSet.end();
    for (;it != end;++it)
    {
		assert(*it != NULL);
        if((*it)->GetNpcResId() == nValue)
        {
            npcId = (*it)->GetNpcId();
			//added by zilong. 2011-03-25. ----------------
			MeDelete *it;
			//added by zilong. end. -----------------------
            m_vecSet.erase(it);
            break;
        }
    }
    if(npcId == 9999999)
        return;

    NpcInfo::Npcs::iterator npcIt = theNpcInfo.npcs_.begin();
    NpcInfo::Npcs::iterator npcEnd = theNpcInfo.npcs_.end();
    for (;npcIt != npcEnd;++npcIt)
    {
        if(npcIt->second.id == npcId && npcIt->second.mapId == mapId)
        {
            theNpcInfo.npcs_.erase(npcIt);
            return;
        }
    }
}

void CResEditMgr::CreateNpcLine()
{
    ClearNpcLine();
    CNdlNpcLineRes* pLine = MeNew CNdlNpcLineRes;
    pLine->CreateLine(m_bindTile);
    m_vecLineSet.push_back(pLine);
}



void CResEditMgr::ClearNpcLine()
{
    int nSize = m_vecLineSet.size();
    for (int i = 0;i < nSize;++i)
    {
       /*CNdlNpcLineRes* pRes = m_vecLineSet[i];*/
       SAFE_DELETE(m_vecLineSet[i]);
    }
}

