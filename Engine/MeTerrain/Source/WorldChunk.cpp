/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	WorldChunk.cpp
* Create: 	10/06/2006
* Desc:		地图数据Chunk
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/WorldPrecompiled.hpp"
#include "MeTerrain/SwRender.h"

#include "Me3d/Model/Mex2.h"
#include "MeTerrain/NdlResMgr.h"
#define _MinOrMaxMacro( min, max, x ) if( (x)<(min) ){ (min)=(x); }else{ if((x)>(max)){ (max)=(x); } }
////////////////////////////////////////////////////////////////////////////////
CWorldChunk::CWorldChunk( CWorldTile* tile )
:m_liquidColor(g_defaultLiquidColor)
,m_eLoadLevel(eCreate)
,m_parentTile(NULL)
{


	m_culled		= false;
	m_height[0]		=  swInfinity;
	m_height[1]		= -swInfinity;
	m_chunk[0]		= -1;
	m_chunk[1]		= -1;
	m_origin[0]		= 0.0f;
	m_origin[1]		= 0.0f;
	m_textureLOD	= 0;
	m_fTotalHeight[0] = 0;
	m_fTotalHeight[1] = 0;
	InitializeCriticalSection(&m_usingMarkCS);
	Reset( tile );
}

CWorldChunk::~CWorldChunk()
{
	Reset(NULL);
	DeleteCriticalSection(&m_usingMarkCS);
}

void CWorldChunk::Create( sInt32 chunkX, sInt32 chunkY )	
{
	Assert( NULL != m_parentTile );

	SetPos( chunkX, chunkY );


	for( sInt32 i = 0; i < (WORLD_TILE_CHUNK_UNIT_NUM+1)*(WORLD_TILE_CHUNK_UNIT_NUM+1); i++ ) {
		m_vertexOut[i].height	= -swInfinity;
	}
	for( sInt32 i = 0; i < WORLD_TILE_CHUNK_UNIT_NUM*WORLD_TILE_CHUNK_UNIT_NUM; i++ ) {
		m_vertexIn[i].height	= swInfinity;
	}

	m_staticModelList.clear();
	for (size_t i = 0; i < m_doodadList.size();++i)
	{
		delete m_doodadList[i];
	}
	m_doodadList.clear();
}	

void CWorldChunk::Reset( CWorldTile* tile )
{
	m_isLoad		= false;
	if (m_eLoadLevel >= eModelLoaded)
	{
		UnloadStaticModelList();
	}
	m_eLoadLevel = (eCreate);
	m_staticModelList.clear();
	m_liquidAlphaCoaf = 1.0f;
	m_shape			= RES_INVALID_ID;
	m_maskId		= RES_INVALID_ID;
	m_shadow		= RES_INVALID_ID;
	m_road			= RES_INVALID_ID;
	m_envId		= RES_INVALID_ID;
	m_zoneId		= RES_INVALID_ID;
	m_liquidId		= RES_INVALID_ID;
	m_layerCount	= 0;
	m_liquidHeight	= 0.0f;
	m_usingMark		= 0;

	for( sInt32 i = 0; i < TextureLayerFlight; i++ ) {
		m_texture[i] = RES_INVALID_ID;
		if( i < (TextureLayerFlight-1) ) {
			m_alpha[i]	= RES_INVALID_ID;	
		}
	}

// 	memset( m_vertexOut, 0, sizeof(TChunkVertex) );
// 	memset( m_vertexIn, 0, sizeof(TChunkVertex) );
	for (size_t i = 0; i < m_doodadList.size(); ++i)
	{
		delete m_doodadList[i];
	}
	m_doodadList.clear();
	m_parentTile	= tile;
	SetLODLevel(0);
}

void CWorldChunk::SetPos( sInt32 chunkX, sInt32 chunkY )
{
	m_chunk[0]	= chunkX;
	m_chunk[1]	= chunkY;

	m_origin[0]	= chunkX*WORLD_CHUNKSIZE+(WORLD_CHUNKSIZE*0.5f);
	m_origin[1]	= chunkY*WORLD_CHUNKSIZE+(WORLD_CHUNKSIZE*0.5f);
	//m_origin[1]	= -chunkY*WORLD_CHUNKSIZE - (WORLD_CHUNKSIZE*0.5f);
}

void CWorldChunk::CalcHeight()
{
	m_height[0] = swInfinity;
	m_height[1] = -swInfinity;
	for( uInt32 i=0; i<(WORLD_TILE_CHUNK_UNIT_NUM+1)*(WORLD_TILE_CHUNK_UNIT_NUM+1); i++ ) {
		m_height[0] = ZnMin<flt32>( m_height[0], m_vertexOut[i].height );
		m_height[1] = ZnMax<flt32>( m_height[1], m_vertexOut[i].height );
		
		if( i < (WORLD_TILE_CHUNK_UNIT_NUM)*(WORLD_TILE_CHUNK_UNIT_NUM) ) {
			m_height[0] = ZnMin<flt32>( m_height[0], m_vertexIn[i].height );
			m_height[1] = ZnMax<flt32>( m_height[1], m_vertexIn[i].height );
		}
	}
	m_parentTile->CalcHeight();
}

bool CWorldChunk::GetMinMaxHeight( sInt32 unitX, sInt32 unitY, flt32& minHeight, flt32& maxHeight )
{
	sInt32 id;
	flt32 z;

	// v0
	minHeight	= m_vertexIn[unitY*WORLD_TILE_CHUNK_UNIT_NUM+unitX].height;
	maxHeight	= minHeight;
	id			= unitY*(WORLD_TILE_CHUNK_UNIT_NUM+1)+unitX;

	// v1
	z			= m_vertexOut[id++].height;
	_MinOrMaxMacro( minHeight, maxHeight, z );

	// v2
	z			= m_vertexOut[id].height;
	_MinOrMaxMacro( minHeight, maxHeight, z );

	// v3
	id			+= WORLD_TILE_CHUNK_UNIT_NUM;
	z			= m_vertexOut[id++].height;
	_MinOrMaxMacro( minHeight, maxHeight, z );

	// v4
	z			= m_vertexOut[id].height;
	_MinOrMaxMacro( minHeight, maxHeight, z );
	
	return true;
}

// 顶点顺序为 znVertexOrder
bool CWorldChunk::GetUnitVertex( sInt32 unitX, sInt32 unitY, TVertInfo* outVertInfo )
{
	sInt32 id;
	
	id		= unitY*WORLD_TILE_CHUNK_UNIT_NUM+unitX;
	// v0
	outVertInfo[0].vert[0]	= 1;
	outVertInfo[0].vert[1]	= 1;

	outVertInfo[0].pos[0]	= m_origin[0]-(WORLD_CHUNKSIZE*0.5f)+unitX*WORLD_UNITSIZE + (WORLD_UNITSIZE*0.5f);
	outVertInfo[0].pos[1]	= m_origin[1]-(WORLD_CHUNKSIZE*0.5f)+unitY*WORLD_UNITSIZE + (WORLD_UNITSIZE*0.5f);
	outVertInfo[0].pos[2]	= m_vertexIn[id].height;
	for (size_t i = 0; i < 3; ++i)
	{
		outVertInfo[0].normal[i]= m_vertexIn[id].normal[i]/127.f;	
	}
	// v1
	id		= unitY*(WORLD_TILE_CHUNK_UNIT_NUM+1)+unitX;
	outVertInfo[1].vert[0]	= 0;
	outVertInfo[1].vert[1]	= 0;

	outVertInfo[1].pos[0]	= outVertInfo[0].pos[0]-(WORLD_UNITSIZE*0.5f);
	outVertInfo[1].pos[1]	= outVertInfo[0].pos[1]-(WORLD_UNITSIZE*0.5f);
	outVertInfo[1].pos[2]	= m_vertexOut[id].height;
	for (size_t i = 0; i < 3; ++i)
	{
		outVertInfo[1].normal[i]= m_vertexOut[id].normal[i]/127.f;	
	}

	// v2
	id		+= (WORLD_TILE_CHUNK_UNIT_NUM+1);
	outVertInfo[2].vert[0]	= 0;
	outVertInfo[2].vert[1]	= 2;
	outVertInfo[2].pos[0]	= outVertInfo[0].pos[0]-(WORLD_UNITSIZE*0.5f);
	outVertInfo[2].pos[1]	= outVertInfo[0].pos[1]+(WORLD_UNITSIZE*0.5f);
	outVertInfo[2].pos[2]	= m_vertexOut[id].height;
	for (size_t i = 0; i < 3; ++i)
	{
		outVertInfo[2].normal[i]= m_vertexOut[id].normal[i]/127.f;	
	}

	// v3
	id += 1;
	outVertInfo[3].vert[0]	= 2;
	outVertInfo[3].vert[1]	= 2;
	outVertInfo[3].pos[0]	= outVertInfo[0].pos[0]+(WORLD_UNITSIZE*0.5f);
	outVertInfo[3].pos[1]	= outVertInfo[0].pos[1]+(WORLD_UNITSIZE*0.5f);
	outVertInfo[3].pos[2]	= m_vertexOut[id].height;
	for (size_t i = 0; i < 3; ++i)
	{
		outVertInfo[3].normal[i]= m_vertexOut[id].normal[i]/127.f;	
	}

	// v4
	id		-= (WORLD_TILE_CHUNK_UNIT_NUM+1);
	outVertInfo[4].vert[0]	= 2;
	outVertInfo[4].vert[1]	= 0;
	outVertInfo[4].pos[0]	= outVertInfo[0].pos[0]+(WORLD_UNITSIZE*0.5f);
	outVertInfo[4].pos[1]	= outVertInfo[0].pos[1]-(WORLD_UNITSIZE*0.5f);
	outVertInfo[4].pos[2]	= m_vertexOut[id].height;
	for (size_t i = 0; i < 3; ++i)
	{
		outVertInfo[4].normal[i]= m_vertexOut[id].normal[i]/127.f;	
	}

	return true;
}

// NOTE: 
// 因为即使是相同模型 modelId 也不同．所以不需要检验.
bool CWorldChunk::PushModel( sInt32 modelId )
{
	m_staticModelList.push_back( modelId );
		
	return true;
}


int CWorldChunk::AddDoodadLevel( uInt32 ulevelUnit,bool isEdit )
{
	
	m_doodadList.push_back(MeNew TDoodadLevelInfo(ulevelUnit,isEdit));
	return m_doodadList.size() - 1;
}

TDoodadLevelInfo* CWorldChunk::GetDoodadLevel( sInt32 nIndex )
{
	if(nIndex >=0 && nIndex < m_doodadList.size())
	return m_doodadList[nIndex];
	
	return NULL;
}


//only for worldEdit
TDoodadLevelInfo* CWorldChunk::GetDoodadLevel( uInt32 mdoodadId, uInt32 ulevelUnit, CResMgr*	pResMgr )
{
	for (size_t i = 0; i < m_doodadList.size();++i)
	{
		if (m_doodadList[i]->mdoodadId == mdoodadId && m_doodadList[i]->mulevelUnit == ulevelUnit )
		{
			return m_doodadList[i];
		}
	}
	int nNew = AddDoodadLevel(ulevelUnit,true);
 	pResMgr->IncDoodadRef(mdoodadId);
	m_doodadList[nNew]->mdoodadId = mdoodadId;
	return m_doodadList[nNew];

}
bool CWorldChunk::DeleteDoodadLevel( sInt32 nIndex )
{
	if(nIndex >=0 && nIndex < m_doodadList.size())
	{
		m_parentTile->GetCResMgr()->DecDoodadRef(m_doodadList[nIndex]->mdoodadId);
		SAFE_DELETE(m_doodadList[nIndex]);
		m_doodadList.erase(m_doodadList.begin()+ nIndex);
		return true;
	}
	return false;
}

sInt32 CWorldChunk::GetDoodadLevelCount()
{
	return m_doodadList.size();
}


void CWorldChunk::GetCameraTerrainIntersection( D3DXVECTOR3* pvFrom, 
											   D3DXVECTOR3* pvDir,
											   std::vector<ChunkIntersection>* pvectorIntersection)
{

	if (IsCulled())
	{
		return;
	}
// 	float fScale = 1.00f;

	D3DXVECTOR3 vFrom = *pvFrom;
	vFrom.x = pvFrom->x;
	vFrom.y = pvFrom->y;
	vFrom.z = pvFrom->z;

	int nFaceCount = CResMgr::m_LODFaceCount[m_lodLevel];
    if( !m_parentTile )
        return;
	CResMgr* pThisMgr = m_parentTile->GetCResMgr();
    if( !pThisMgr )
        return;
	D3DXVECTOR3 p[3];
	WORD*index = pThisMgr->GetStaticIndexStream(m_lodLevel);
	flt32 originX = ((m_chunk[0])*WORLD_CHUNKSIZE+(WORLD_CHUNKSIZE*0.5f)); 
	flt32 originY = ((m_chunk[1])*WORLD_CHUNKSIZE+(WORLD_CHUNKSIZE*0.5f)); 
	for( int i = 0; i < nFaceCount; i++ )
	{
		for(int j = 0; j < 3; ++j)
		{
			CResMgr::SInOutPos& Pos = m_parentTile->GetCResMgr()->GetIndexToInOut(index[i*3 + j]);
			p[j].x = originX + Pos.x;
			p[j].y = originY + Pos.y;
			TChunkVertex* pChunkVertex = NULL;
			if (Pos.bIn)
			{
				pChunkVertex = &m_vertexIn[Pos.inOutIndex];
			}
			else
			{
				pChunkVertex = &m_vertexOut[Pos.inOutIndex];
			}
			p[j].z = pChunkVertex->height;
		}
		D3DXVECTOR3 vNormal;
		D3DXVECTOR3 e0 = p[1]-p[0];
		D3DXVECTOR3 e1 = p[2]-p[0];
		D3DXVec3Cross( &vNormal, &e0, &e1 );
		if( D3DXVec3Dot( &vNormal, pvDir ) </*>*/ 0 )	// 右手系，所以符号取反
			continue;


		float tu, tv, t;
		if( D3DXIntersectTri( &p[0], &p[1], &p[2], &vFrom, pvDir, &tu, &tv, &t ) )
		{
			ChunkIntersection is; 
			is.pChunk = this;
			is.t = t;
			is.u = tu;
			is.v = tv;
			is.p = vFrom+*pvDir*t;
			is.normal = vNormal;
			pvectorIntersection->push_back( is );
		}

	}

// 	CNdlShapeRes* pShapeRes = pThisMgr->Shape(m_shape);	
//     if( !pShapeRes )
//         return;
// 
// 	FTerrainVertexSpecial* terrainVertex = pShapeRes->GetTerrainVertex();
//     if( !terrainVertex )
//         return;
// 
// 	for( int i = 0; i < nFaceCount; i++ )
// 	{
// 		p[0] = terrainVertex[index[i*3]].p;
// 		p[1] = terrainVertex[index[i*3+1]].p;
// 		p[2] = terrainVertex[index[i*3+2]].p;
// // 		normal[0]= terrainVertex[index[i*3]].n;
// // 		normal[1]= terrainVertex[index[i*3+1]].n;
// // 		normal[2]= terrainVertex[index[i*3+2]].n;
// 		
// 		D3DXVECTOR3 vNormal;
// 		D3DXVECTOR3 e0 = p[1]-p[0];
// 		D3DXVECTOR3 e1 = p[2]-p[0];
// 		D3DXVec3Cross( &vNormal, &e0, &e1 );
// 		if( D3DXVec3Dot( &vNormal, pvDir ) </*>*/ 0 )	// 右手系，所以符号取反
// 			continue;
// 
// 		//////////////////////////////////////
// 		//p[0] += normal[0]*abs(normal[0].z);
// 		//p[1] += normal[1]*abs(normal[1].z);
// 		//p[2] += normal[2]*abs(normal[2].z);
// 
// 		float tu, tv, t;
// 		if( D3DXIntersectTri( &p[0], &p[1], &p[2], &vFrom, pvDir, &tu, &tv, &t ) )
// 		{
// 			ChunkIntersection is; 
// 			is.pChunk = this;
// 			is.t = t;
// 			is.u = tu;
// 			is.v = tv;
// 			is.p = vFrom+*pvDir*t;
// 			is.normal = vNormal;
// 			pvectorIntersection->push_back( is );
// 		}
// 
// 	}
}

TDoodadLevelInfo::TDoodadLevelInfo( uInt32 ulevelUnit ,bool isEdit)
{
	mulevelUnit = ulevelUnit;
	m_bEdit = isEdit;
//	int nTmp = (int)(WORLD_CHUNKSIZE/mulevelUnit);
	if (isEdit)
	{
		m_pDoodadMap = MeNew TDoodadInfoForEdit[mulevelUnit*mulevelUnit];
		memset(m_pDoodadMap,0,sizeof(TDoodadInfoForEdit)*mulevelUnit*mulevelUnit);
	}
	else
	{
		m_pDoodadMap = MeNew TDoodadInfo[mulevelUnit*mulevelUnit];
		memset(m_pDoodadMap,0,sizeof(TDoodadInfo)*mulevelUnit*mulevelUnit);
	}

	mdoodadId = RES_INVALID_ID;
// 	m_pMesh = 0;
}

TDoodadLevelInfo::~TDoodadLevelInfo()
{
	ReleaseDoodadInstance();
	delete [] m_pDoodadMap;
}
#include "MeTerrain/NdlRes.h"
void TDoodadLevelInfo::RefreshDoodadInstance( CResMgr* presMgr, CWorldChunk* worldChunk ,CWorldTile* tile)
{
	if(0 == mulevelUnit)
		return;
	flt32 fAtomSize = (WORLD_CHUNKSIZE/mulevelUnit);
	MexAnimCtrl* pMesh = NULL;
	CDoodadRes* pDoodadRes = presMgr->GetDoodadRes(mdoodadId);
	if (pDoodadRes->GetModel())
	{
		pMesh = pDoodadRes->GetModel()->model;
	}
	if (NULL == pMesh)
	{//load fail
		return;
	}
	
	flt32 trans[3];
	trans[0] = worldChunk->Origin()[0];
	trans[1] = worldChunk->Origin()[1];
	if (SwGlobal::GetRender()->IsHardwareInstancing())
	{
		GetInstanceMan()->DisableInstance();
		//caculate doodad count
		int iDoodadCount = 0;
		for (size_t i = 0; i < mulevelUnit*mulevelUnit; ++i)
		{
			if (GetDoodad(i).m_nScale != 0)
			{
				++iDoodadCount;
			}
		}
		if( !iDoodadCount )
			return;
		if( FAILED( GetInstanceMan()->EnableInstance( pMesh, iDoodadCount) ) )
			return;
		//add instance
		GetInstanceMan()->Lock();
		for (size_t i = 0; i < mulevelUnit*mulevelUnit; ++i)
		{
			if (GetDoodad(i).m_nScale != 0)
			{
				CMexInstanceObject object;			
				//pObject->SetScale(((float)m_pDoodadMap[i].m_nScale)/100);
				//NiMatrix3 matRot;
				//matRot.FromEulerAnglesXYZ( 0.0f, 0.0f, (rand()%360)*PI/180.0f );
				object.SetRotate( (rand()%360)*PI/180.0f );
				object.SetScale(((float)GetDoodad(i).m_nScale)/100);
				object.SetShadow( 1.f );
				Vector trans;
				trans.x = worldChunk->Origin()[0]-(WORLD_CHUNKSIZE*0.5f)+fAtomSize*(i%mulevelUnit);
				trans.y = worldChunk->Origin()[1]-(WORLD_CHUNKSIZE*0.5f)+fAtomSize*(i/mulevelUnit);
				SwGlobal::GetWorldPicker()->GetHeight( tile, trans.x, trans.y, trans.z );
				object.SetTranslate( trans.x, trans.y, trans.z );				
				//set shadow for grass
				if(SwGlobal::GetWorldPicker()->IsShadow( trans.x, trans.y, tile ))
					object.SetShadow( 0.7f );
				//add to the manager				
				GetInstanceMan()->AddInstance( object );
			}
		}
		GetInstanceMan()->Unlock();
	}	
}

void TDoodadLevelInfo::ReleaseDoodadInstance()
{
	GetInstanceMan()->DisableInstance();
}

TDoodadInfo& TDoodadLevelInfo::GetDoodad( int index )
{
	if (m_bEdit)
	{
		TDoodadInfoForEdit* pDoodadInfoForEdit =  (TDoodadInfoForEdit*)m_pDoodadMap;
		return pDoodadInfoForEdit[index];
	}
	else
	{
		return m_pDoodadMap[index];
	}
}
int CWorldChunk::IsExistSpecialLayer()
{
	for (int i = GetLayerCount()- 1; i >= 0; --i )
	{
		if (m_texInfo[i].m_nX != 0
			|| m_texInfo[i].m_nY != 0
			|| m_texInfo[i].m_ScaleX != 10
			|| m_texInfo[i].m_ScaleY != 10
			|| abs(m_texInfo[i].m_angle) > 0.0001)
		{
			return i;
		}
	}
	return -1;
}


void CWorldChunk::SetLoadLevel( int val )
{
	assert(val >= eCreate && eTotalChunkLoadLevel > val);
	CResMgr* pResMgr = m_parentTile->GetCResMgr();
	int nCurrLevel = m_eLoadLevel;
	if (m_eLoadLevel < val)
	{
		for(;nCurrLevel < val; ++nCurrLevel)
		{
			switch(nCurrLevel)
			{
			case eCreate:
				{
					_SetLoadLevel(eInitialize);
				}
				break;
			case eInitialize:
				{
					while(IsDataInUsing(eTerrainLOD))
					{
						Sleep(1);
					}
					CNdlShapeRes* pShape = pResMgr->Shape(m_shape);
					pResMgr->FillLOD2Vertex(pShape,this);
					_SetLoadLevel(eTerrainLODLoaded);
				}
				break;
			case eTerrainLODLoaded:
				{
					while(IsDataInUsing(eTerrain))
					{
						Sleep(1);
					}
					CNdlShapeRes* pShape = pResMgr->Shape(m_shape);
					if (pShape)
					{
						LoadTexture();
						//if (!pShape->m_culled)
						{
							pResMgr->FillShapeData(pShape,this);
							pResMgr->RefreshChunkMask(this);
						}
						_SetLoadLevel(eTerrainLoaded);
					}
				}
				break;
			case eTerrainLoaded:
				{
					while(IsDataInUsing(eModel))
					{
						Sleep(1);
					}
					LoadStaticModelList();
					flt32 fHeight[2];
					CalculateChunkTotalHeight(pResMgr, fHeight);
					m_parentTile->m_tileQuadTree.UpdateQuadTree( this );
					_SetLoadLevel(eModelLoaded);
				}
				break;
			case eModelLoaded:
				{
					while(IsDataInUsing(eDoodad))
					{
						Sleep(1);
					}
					LoadDoodadList();
					_SetLoadLevel(eDoodadLoaded);
				}
				break;
			}
		}
	}
	else
	{
		for(;nCurrLevel > val; --nCurrLevel)
		{
			switch(nCurrLevel)
			{
			case eInitialize:
				{
					assert(0);
					_SetLoadLevel(eCreate);
				}
				break;
			case eTerrainLODLoaded:
				{
					_SetLoadLevel(eInitialize);
					while(IsDataInUsing(eTerrainLOD))
					{
						Sleep(1);
					}
					CNdlShapeRes* pShape = pResMgr->Shape(m_shape);
					if( pShape )
						pShape->ReleaseTerrainLODData();
				}
				break;
			case eTerrainLoaded:
				{
					_SetLoadLevel(eTerrainLODLoaded);
					while(IsDataInUsing(eTerrain))
					{
						Sleep(1);
					}
					CNdlShapeRes* pShape = pResMgr->Shape(m_shape);
					if (pShape)
					{
						pShape->ReleaseTerrainData();
						UnloadTexture();
						pResMgr->ReleaseChunkMask(this);
					}
				}
				break;
			case eModelLoaded:
				{
					_SetLoadLevel(eTerrainLoaded);
					while(IsDataInUsing(eModel))
					{
						Sleep(1);
					}
					UnloadStaticModelList();
				}
				break;
			case eDoodadLoaded:
				{
					_SetLoadLevel(eModelLoaded);
					while(IsDataInUsing(eDoodad))
					{
						Sleep(1);
					}
					UnloadDoodadList();
				}
				break;
			}
		}
	}
}

void CWorldChunk::LoadStaticModelList()
{
	CResMgr* resMgr = m_parentTile->GetCResMgr();
	for( size_t i=0; i<m_staticModelList.size(); i++ )
	{
		sInt32 id		= m_staticModelList[i];
		if( id < resMgr->GetStaticModelList().size() )
		{
			TObjectInfo* objInfo	= resMgr->GetStaticModelList()[id];
			objInfo->IncreaseRef(resMgr);
		}
	}
}

void CWorldChunk::UnloadStaticModelList()
{
	if (NULL == m_parentTile)
	{
		return;
	}
	CResMgr* resMgr = m_parentTile->GetCResMgr();
	for( size_t i=0; i<m_staticModelList.size(); i++ )
	{
		sInt32 id		= m_staticModelList[i];
		if( id < resMgr->GetStaticModelList().size() )
		{
			TObjectInfo* objInfo	= resMgr->GetStaticModelList()[id];
			objInfo->DecreaseRef(resMgr);
		}
	}
}

void CWorldChunk::LoadDoodadList()
{
	CResMgr* resMgr = m_parentTile->GetCResMgr();
	for( size_t i=0; i<m_doodadList.size(); i++ )
	{
		TDoodadLevelInfo* pInfo		= m_doodadList[i];
		resMgr->IncDoodadRef(pInfo->mdoodadId);
		pInfo->RefreshDoodadInstance(resMgr,this,m_parentTile);
	}

}

void CWorldChunk::UnloadDoodadList()
{
	CResMgr* resMgr = m_parentTile->GetCResMgr();
	for( size_t i=0; i<m_doodadList.size(); i++ )
	{
		TDoodadLevelInfo* pInfo		= m_doodadList[i];
		resMgr->DecDoodadRef(pInfo->mdoodadId);
		pInfo->ReleaseDoodadInstance();
	}

}

void CWorldChunk::MarkDataUsing( int val,bool bInUsing )
{
	if (bInUsing)
	{
		m_usingMark |= val;
	}
	else
	{
		m_usingMark &= (~val);
	}

}

void CWorldChunk::LockFlag( bool bLock )
{
	if (bLock)
	{
		EnterCriticalSection(&m_usingMarkCS);
	}
	else
	{
		LeaveCriticalSection(&m_usingMarkCS);
	}
}

bool CWorldChunk::IsLockFlag()  
{
	if(TryEnterCriticalSection(&m_usingMarkCS))
	{
		LockFlag(false);
		return false;
	}
	else
		return true;
}

bool CWorldChunk::IsDataInUsing( int val ) 
{
	if (IsLockFlag())
	{
		return true;
	}
	return m_usingMark & val;
}

void CWorldChunk::_SetLoadLevel( int val )
{
	LockFlag(true);
	m_eLoadLevel = (eChunkLoadLevel)val;
	LockFlag(false);
}

#include "Me3d\Shader.h"
#include "Me3d\ShaderManager.h"

void CWorldChunk::RenderLod2( int* pVertexCount/*=NULL*/, int* pFaceCount/*=NULL */ )
{
	guardfunc;
	if ( CResMgr::LOD2 != m_lodLevel && CResMgr::LOD1to2 != m_lodLevel)
		return;

	CResMgr* pThisMgr = m_parentTile->GetCResMgr();
	CNdlShapeRes* pShapeRes = pThisMgr->Shape(m_shape);
	IRenderer* r = GetEngine()->GetRenderer();
	if (r->EnableUseShader() )
	{
		r->RenderTerrainLOD2WithShader(
 			sizeof( TChunkLOD2Vertex ),
 			pShapeRes->m_pVBLOD2,
 			CHUNK_LOD1T02_VERTEX_NUMBER,
			pThisMgr->GetIndexBuffer(m_lodLevel),
			CResMgr::m_LODFaceCount[m_lodLevel]);
		// 统计渲染顶点数和三角形数
		if( pVertexCount )
			*pVertexCount = CHUNK_LOD1T02_VERTEX_NUMBER;
		if( pFaceCount )
			*pFaceCount = CResMgr::m_LODFaceCount[m_lodLevel];
	}

	unguard;

}

void CWorldChunk::RenderShadow( int* pVertexCount/* =NULL */, int* pFaceCount/* =NULL */ )
{
	/*
	这个函数现在用world.fxo这个fx，今后会整合
	*/
	guardfunc;
	CResMgr* pThisMgr = m_parentTile->GetCResMgr();
	CNdlShapeRes* pShapeRes = pThisMgr->Shape(m_shape);
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();

	if (GetEngine()->GetRenderer()->EnableUseShader()  && pShapeRes->m_pVB)
	{
		pDev->SetStreamSource(0, pShapeRes->m_pVB, 0, sizeof( FTerrainVertexSpecial ));
		pDev->SetIndices(pThisMgr->GetIndexBuffer(m_lodLevel));
		pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, CHUNK_VERTEX_NUMBER, 0, CResMgr::m_LODFaceCount[m_lodLevel]);
		

		// 统计渲染顶点数和三角形数
		if( pVertexCount )
			*pVertexCount = CHUNK_VERTEX_NUMBER;
		if( pFaceCount )
			*pFaceCount = CResMgr::m_LODFaceCount[m_lodLevel];
	}
	unguard;
}

void CWorldChunk::Render( int* pVertexCount/*=NULL*/, int* pFaceCount/*=NULL*/ )
{
	guardfunc;
	if ( CResMgr::LOD2 == m_lodLevel || CResMgr::LOD1to2 == m_lodLevel)
		return;

	CResMgr* pThisMgr = m_parentTile->GetCResMgr();
	CNdlShapeRes* pShapeRes = pThisMgr->Shape(m_shape);
	IRenderer* r = GetEngine()->GetRenderer();
	if (r->EnableUseShader() && pShapeRes->m_pVB )
	{
// 		ITextureManager* ptextureMgr = GetEngine()->GetTextureManager();
		short texture[TextureLayerFlight] = {-1};
		for (int i = 0; i < GetMe3dConfig()->GetTerrainRenderLayer(); ++i)
		{
			texture[i] = pThisMgr->Texture(m_texture[i]);
// 			if (RES_INVALID_ID != texture[i])
// 			{
// 				ITexture* pTexture = ptextureMgr->GetTexture(texture[i]);
// 				if (pTexture)
// 				{
// 					pTexture->SetLOD(GetTextureLODLevel());
// 				}
// 			}
			
		}
			ITexture* pMaskTexture = pThisMgr->Mask(m_maskId);
// 			if (pMaskTexture)
// 			{
// 				pMaskTexture->SetLOD(GetTextureLODLevel() + 1);
// 			}
		r->RenderTerrainWithShader(texture[0],
			texture[1],
			texture[2]/*pThisMgr->Texture(m_texture[2])*/,
			texture[3]/*pThisMgr->Texture(m_texture[3])*/,
			pMaskTexture,
			sizeof( FTerrainVertexSpecial ),
			pShapeRes->m_pVB,
			CHUNK_VERTEX_NUMBER,
			pThisMgr->GetIndexBuffer(m_lodLevel),
			CResMgr::m_LODFaceCount[m_lodLevel]);
			// 统计渲染顶点数和三角形数
			if( pVertexCount )
				*pVertexCount = CHUNK_VERTEX_NUMBER;
			if( pFaceCount )
				*pFaceCount = CResMgr::m_LODFaceCount[m_lodLevel];
		
	}
// 	else
// 	{
// 		for (int nLayer = 0; nLayer < TextureLayerFlight; ++nLayer)
// 		{
// 			if( m_texture[nLayer] == RES_INVALID_ID )
// 				continue;
// 			int alphaid = -1;
// 			short nShaderID = TERRAIN_BASEGROUND;
// 			if (nLayer > 0)
// 			{
// 				CNdlAlphaRes* pkNdlAlphaRes = pThisMgr->GetAlpha(m_alpha[nLayer - 1]);
// 				alphaid = pkNdlAlphaRes->GetMaskTetureId();
// 				nShaderID = TERRAIN_SPLATTING;
// 			}
// 			r->DirectPushSurface(
// 				pThisMgr->Texture(m_texture[nLayer]),				
// 				alphaid,				
// 				nShaderID,
// 				D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX5,
// 				sizeof( FTerrainVertexSpecial ),
// 				(BYTE*)pShapeRes->m_terrainVertex,
// 				CHUNK_VERTEX_NUMBER,
// 				(BYTE*)pThisMgr->GetStaticIndexStream(m_lodLevel),
// 				CResMgr::m_LODFaceCount[m_lodLevel], 
// 				0
// 				// 			eZDisable|
// 				//			eWireFrame 
// 				);
// 		}
// 		if (m_shadow != RES_INVALID_ID)
// 		{
// 			CNdlAlphaRes* pkNdlAlphaRes = pThisMgr->GetShadow(m_shadow);
// 			int alphaid = pkNdlAlphaRes->GetMaskTetureId();
// 			r->DirectPushSurface( 
// 				CResMgr::m_baseShadowId,
// 				alphaid,				
// 				TERRAIN_SPLATTING,
// 				D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX5,
// 				sizeof( FTerrainVertexSpecial ),
// 				(BYTE*)pShapeRes->m_terrainVertex,
// 				CHUNK_VERTEX_NUMBER,
// 				(BYTE*)pThisMgr->GetStaticIndexStream(m_lodLevel),
// 				CResMgr::m_LODFaceCount[m_lodLevel],
// 				0 );
// 		}
// 	}

	unguard;

}

void CWorldChunk::RenderWireFrame(bool isLiquid)
{
	CResMgr* pThisMgr = m_parentTile->GetCResMgr();
	CNdlShapeRes* pShapeRes = pThisMgr->Shape(m_shape);
	IRenderer* r = GetEngine()->GetRenderer();
	if (!isLiquid)
	{
		if (CResMgr::LOD2 == m_lodLevel || CResMgr::LOD1to2 == m_lodLevel)
		{
			if (pShapeRes->m_pVBLOD2)
			{
				r->DirectPushSurface(
					-1,				
					-1,				
					TERRAIN_BASEGROUND,
					D3DFVF_XYZ,
					sizeof( TChunkLOD2Vertex ),
					(BYTE*)pShapeRes->m_pVBLOD2,
					CHUNK_LOD1T02_VERTEX_NUMBER,
					(BYTE*)pThisMgr->GetIndexBuffer(m_lodLevel),
					CResMgr::m_LODFaceCount[m_lodLevel], 
					eWireFrame|eUseVB|eUseIB
					);
			}
		}
		else
		{
			if (pShapeRes->m_pVB)
			{
				r->DirectPushSurface(
					-1,				
					-1,				
					TERRAIN_BASEGROUND,
					D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX5,
					sizeof( FTerrainVertexSpecial ),
					(BYTE*)pShapeRes->m_pVB,
					CHUNK_VERTEX_NUMBER,
					(BYTE*)pThisMgr->GetIndexBuffer(m_lodLevel),
					CResMgr::m_LODFaceCount[m_lodLevel], 
					eWireFrame|eUseVB|eUseIB
					);
			}
		}
	}
	if (isLiquid && m_liquidId != RES_INVALID_ID)
	{
// 		CNdlGlobalResMgr* pGlobal = SwGlobal::GetWorld()->GetWorldBuffer()->GetGlobalResMgr();
// 		CNdlTextureRes* pTextureRes = pGlobal->GetCurrFrameLiquidRes(m_liquidId);
		if (pShapeRes->m_liquidVertex)
		{
			int nFaceNumber = 8*9*2 + 7*3 - 2;
			r->DirectPushSurface(
				-1,				
				-1,				
				TERRAIN_BASEGROUND,
				D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,
				sizeof( CNdlShapeRes::WaterVertex ),
				(BYTE*)pShapeRes->m_liquidVertex,
				CHUNK_LIQUID_VERTEX_NUMBER,
				(BYTE*)pThisMgr->GetLiquidIndexStream(),
				nFaceNumber,
				eWireFrame
				);
		}
	}
}

void CWorldChunk::RenderLiquid( int* pVertexCount/*=NULL*/, int* pFaceCount/*=NULL*/ )
{
	CResMgr* pThisMgr = m_parentTile->GetCResMgr();
	CNdlGlobalResMgr* pGlobal = SwGlobal::GetWorld()->GetWorldBuffer()->GetGlobalResMgr();
	CNdlTextureRes* pTextureRes = pGlobal->GetCurrFrameLiquidRes(m_liquidId);
// 	CNdlTextureRes* pNormalTextureRes = pGlobal->GetCurrFrameLiquidNormalRes( m_liquidId );
	CNdlShapeRes* pShapeRes = pThisMgr->Shape(m_shape);
	IRenderer* r = GetEngine()->GetRenderer();
	int nFaceNumber = 8*9*2 + 7*3 - 2;
	if (r->EnableUseShader() && pShapeRes->m_liquidVertex)
	{		
		r->RenderLiquidWithShader(pTextureRes->GetTexture(),
			sizeof( CNdlShapeRes::WaterVertex ),
			(BYTE*)pShapeRes->m_liquidVertex,
			CHUNK_LIQUID_VERTEX_NUMBER,
			(BYTE*)pThisMgr->GetLiquidIndexStream(),
			nFaceNumber
			);

		// 统计
		if( pVertexCount )
			*pVertexCount = CHUNK_LIQUID_VERTEX_NUMBER;
		if( pFaceCount )
			*pFaceCount = nFaceNumber;
	}

}
void CWorldChunk::RenderLiquid_High(int* pVertexCount /* = 0 */, int* pFaceCount /* = 0 */)
{
	CResMgr* pThisMgr = m_parentTile->GetCResMgr();
	CNdlGlobalResMgr* pGlobal = SwGlobal::GetWorld()->GetWorldBuffer()->GetGlobalResMgr();
	CNdlTextureRes* pTextureRes = pGlobal->GetCurrFrameLiquidRes(m_liquidId);
// 	CNdlTextureRes* pNormalTextureRes = pGlobal->GetCurrFrameLiquidNormalRes( m_liquidId );
	CNdlShapeRes* pShapeRes = pThisMgr->Shape(m_shape);
	IRenderer* r = GetEngine()->GetRenderer();
	int nFaceNumber = 8*9*2 + 7*3 - 2;
	if (r->EnableUseShader() && pShapeRes->m_liquidVertex)
	{
		r->RenderLiquidWithShader_High(pTextureRes->GetTexture(),
			sizeof( CNdlShapeRes::WaterVertex ),
			(BYTE*)pShapeRes->m_liquidVertex,
			CHUNK_LIQUID_VERTEX_NUMBER,
			(BYTE*)pThisMgr->GetLiquidIndexStream(),
			nFaceNumber
			);

		// 统计
		if( pVertexCount )
			*pVertexCount = CHUNK_LIQUID_VERTEX_NUMBER;
		if( pFaceCount )
			*pFaceCount = nFaceNumber;
	}
}
int CWorldChunk::IsExistSpecialTexture( sInt32 textureId )
{
// 	int nSpecialLevel = IsExistSpecialLayer();
// 	if (-1 == nSpecialLevel)
// 	{
// 		return -1;
// 	}
	for (int i = 0; i < GetLayerCount(); ++i)
	{
		if (m_texture[i] == textureId)
		{
			return i;
		}
	}
	return -1;
}

void CWorldChunk::CalculateChunkTotalHeight( CResMgr *resMgr, flt32* fHeight )
{
	// 地表高度
	fHeight[0] = m_height[0];
	fHeight[1] = m_height[1];

	// 水面高度
	fHeight[0] = min(fHeight[0], m_liquidHeight);
	fHeight[1] = max(fHeight[1], m_liquidHeight);

	{
		// 所有模型高度取最大最小
		for( size_t i=0; i<m_staticModelList.size(); i++ )
		{
			sInt32 id		= m_staticModelList[i];
			if( id < resMgr->GetStaticModelList().size() )
			{
				TObjectInfo* p	= resMgr->GetStaticModelList()[id];
				if(!p->model || p->model->HasEmitter())
					continue;
				Box* pWBox = p->model->GetWorldBBox();
				for(int b=0; b<8; b++)
				{
					fHeight[0] = min(fHeight[0], pWBox->v[b].z);
					fHeight[1] = max(fHeight[1], pWBox->v[b].z);
				}
			}
		}
	}
	m_fTotalHeight[0] = fHeight[0];
	m_fTotalHeight[1] = fHeight[1];
	m_parentTile->UpdateHeightByChunk(this);

}

bool CWorldChunk::IsInShadow( sInt32 nX, sInt32 nY )
{
	if(m_shadow < 0)
		return false;

	CResMgr* resMgr = m_parentTile->GetCResMgr();
	CNdlAlphaRes* pShadow =  resMgr->GetShadow(m_shadow);
	if(pShadow)
	{
		int nIndex = nX/2 + nY * WORLD_TILE_CHUNK_ATOM_NUM/2;
		int nMod = (nX + 1)%2;
		uAlphaBit* destPtr		= pShadow->GetMaskData();
		if (nMod == 0 && ((destPtr[nIndex] & 0xF0) != 0xf0))
		{
			return true;
		}
		if (nMod == 1 && ((destPtr[nIndex] & 0x0F) != 0x0F))
		{
			return true;
		}
	}
	else
	{
		if (RES_INVALID_ID == m_maskId)
		{
			return false;
		}
		int nIndex = nX + nY * WORLD_TILE_CHUNK_ATOM_NUM;
		TextureDx8* pMask = (TextureDx8*)resMgr->Mask( m_maskId );
		if( !pMask )
			return false;
		LPDIRECT3DTEXTURE9 pd3dTexture = pMask->GetTexture();
        if( !pd3dTexture )
        {
            return false;
        }
		D3DLOCKED_RECT rect;
		if( FAILED( pd3dTexture->LockRect( 0, &rect, 0, 0 ) ) )
		{
			return false;
		}
		bool bRet = false;
		int* p = (int*)rect.pBits;
		if( p != 0 )
		{
			if( ((p[nIndex] >> 24  ) & 0xff) != 0xff )//在阴影内
			{
				bRet = true;
			}
		}

		pd3dTexture->UnlockRect(0);
		return bRet;
// 		D3DSURFACE_DESC desc;
// 		pTexture->GetLevelDesc(0,&desc);

	}

	return false;
}

BspTree::SIntersect* CWorldChunk::GetNearestIntersectCmpZ( Vector& vPos, Vector& vDir, BOOL bNormal, float fCurrZ )
{
// 	static std::vector<BspTree::SIntersect> m_vtIntersect;
//  	m_vtIntersect.clear();
	static BspTree::SIntersect nearestIntersect;
	nearestIntersect.t = WORLD_HEIGHT*200;
	CResMgr* resMgr = m_parentTile->GetCResMgr();
	BspTree::SIntersect* pIntersect = NULL;
	for( size_t i=0; i<m_staticModelList.size(); i++ )
	{
		sInt32 id		= m_staticModelList[i];
		if( id < resMgr->GetStaticModelList().size() )
		{
			TObjectInfo* p	= resMgr->GetStaticModelList()[id];
			if ( p && p->m_pModelFloor)
			{
				pIntersect = p->m_pModelFloor->GetNearestIntersectCmpZ( vPos, vDir, bNormal,fCurrZ );
				if( pIntersect )
				{
					if(nearestIntersect.t > pIntersect->t)
					{
						nearestIntersect = * pIntersect;
					}
// 					m_vtIntersect.push_back( *pIntersect );
				}
			}
		}
	}

	if (abs(nearestIntersect.t - WORLD_HEIGHT*200) > 0.0001)
	{
		return &nearestIntersect;
	}

// 	guard(test2);
// 	if( m_vtIntersect.size() > 0 )
// 	{
// 		int id = 0;
// 		for( int i = 1; i < m_vtIntersect.size(); i++ )
// 		{
// 			if( m_vtIntersect[i].t < m_vtIntersect[id].t )
// 				id = i;
// 		}
// 		return &m_vtIntersect[id];
// 	}
// 	unguard;

	return NULL;

}

BspTree::SIntersect* CWorldChunk::GetSimpleCollision( Vector& vPos ,bool bNearest,bool bDown  )
{
	Vector vDir(0,0,-1);
	if (!bDown)
	{
		vDir = Vector(0,0,1);
	}
	static BspTree::SIntersect nearestIntersect;
	nearestIntersect.t = WORLD_HEIGHT*200;
	CResMgr* resMgr = m_parentTile->GetCResMgr();
	BspTree::SIntersect* pIntersect = NULL;
	for( size_t i=0; i<m_staticModelList.size(); i++ )
	{
		sInt32 id		= m_staticModelList[i];
		if( id < resMgr->GetStaticModelList().size() )
		{
			TObjectInfo* p	= resMgr->GetStaticModelList()[id];
			if (p->m_pCollision)
			{
				pIntersect = p->m_pCollision->GetNearestIntersect( vPos, vDir,false,true);
				if (pIntersect )
				{
					if (bNearest)
					{
						if(nearestIntersect.t > pIntersect->t)
						{
							nearestIntersect = * pIntersect;
						}
					}
					else
					{
						return pIntersect;
					}
				}
			}
		}
	}
	if (abs(nearestIntersect.t - WORLD_HEIGHT*200) > 0.0001)
	{
		return &nearestIntersect;
	}
	return false;

}

BspTree::SIntersect* CWorldChunk::GetSimpleFloor( Vector& vPos,bool bNearest,bool bDown ,bool bSupper , BOOL bNormal  )
{
	Vector vDir(0,0,-1);
	if (!bDown)
	{
		vDir = Vector(0,0,1);
	}
	CResMgr* resMgr = m_parentTile->GetCResMgr();
	static BspTree::SIntersect nearestIntersect;
	nearestIntersect.t = WORLD_HEIGHT*200;
	BspTree::SIntersect* pIntersect = NULL;
	for( size_t i=0; i<m_staticModelList.size(); i++ )
	{
		sInt32 id		= m_staticModelList[i];
		if( id < resMgr->GetStaticModelList().size() )
		{
			TObjectInfo* p	= resMgr->GetStaticModelList()[id];
			BspTree* pBsp = p->m_pModelFloor;
			if (bSupper)
			{
				pBsp = p->m_pSupperFloor;
			}
			if (pBsp)
			{
				pIntersect = pBsp->GetNearestIntersect( vPos, vDir,bNormal,false);
				if (pIntersect )
				{
					if (bNearest)
					{
						if(nearestIntersect.t > pIntersect->t)
						{
							nearestIntersect = * pIntersect;
						}
					}
					else
					{
						return pIntersect;
					}
				}
			}
		}
	}
	if (abs(nearestIntersect.t - WORLD_HEIGHT*200) > 0.0001)
	{
		return &nearestIntersect;
	}
	return false;

}

void CWorldChunk::SetLODLevel( int val )
{
	m_lodLevel = val;
	if (m_parentTile && m_parentTile->GetForcedMaxLOD()!= CResMgr::LOD0)
	{
		switch (m_lodLevel)
		{
		case CResMgr::LOD0:
			{
				m_lodLevel = CResMgr::LOD1;
				break;
			}
		case CResMgr::LOD0to1:
			{
				m_lodLevel = CResMgr::LOD1;
				break;
			}
		}
	}
}

void CWorldChunk::LoadTexture()
{
//先注掉，有可能有问题2010416袁
// #ifndef WORLD_EDIT 
	if (!m_culled)
// #endif
	{
		if( !m_parentTile )
			return;
		CResMgr* pSrcMgr = m_parentTile->GetCResMgr();
		for( int l = 0; l < RES_LAYER_NUM; ++l ) 
		{
			if (m_texture[l] != RES_INVALID_ID)
			{
				CNdlTextureRes* pTexture = pSrcMgr->GetTexture(m_texture[l]);
				pTexture->IncRefCount();
			}
		}
	}
}

void CWorldChunk::UnloadTexture()
{
	if (!m_culled)
	{
		CResMgr* pSrcMgr = m_parentTile->GetCResMgr();
		for( int l = 0; l < RES_LAYER_NUM; ++l ) 
		{
			if (m_texture[l] != RES_INVALID_ID)
			{
				CNdlTextureRes* pTexture = pSrcMgr->GetTexture(m_texture[l]);
				pTexture->DecRefCount();
			}
		}
	}
}
