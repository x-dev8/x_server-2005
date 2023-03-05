//-----------------------------------------------------------------------------
// File:	StaticMeshRayTracer.cpp
// Desc:	计算模型光照图
// Create: 	01/14/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#include "MeTerrain/stdafx.h"
#include "MeTerrain/Lighting/StaticMeshRayTracer.h"
#include "MeTerrain/Lighting/SurfaceLayoutMgr.h"
#include "MeTerrain/Lighting/StaticMeshInstance.h"
#include "MeTerrain/Lighting/StaticLightingCache.h"
#include "MeTerrain/Lighting/LightAttenuationEvaluator.h"
#include "MeTerrain/Lighting/TriangleRasterizer.h"
#include "MeTerrain/Lighting/LightBitmapFilter.h"
#include "MeTerrain/Lighting/LightMapFunctors.h"
#include "MeTerrain/Lighting/LightMapTexture.h"
#include "MeTerrain/NdlResMgr.h"
#include "MeTerrain/NdlRes.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "MeTerrain/Lighting/MeshLightmapColorData.h"
#include "MeTerrain/Lighting/LightRes.h"
#include "Me3d/Model/Mex2.h"
#include "Me3d/D3dutil.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 计算静态模型阴影度
class StaticMeshShadowingFunctor
{
public:

	StaticMeshShadowingFunctor(CWorldTile* pTile, LightRes* pLight, std::vector<ShadowData>* OutputShadowing, INT SizeX, INT SizeY, CNdlWorldPickerBase* pInPick)
		:m_pTile(pTile)
		,m_pLight(pLight)
		,m_pShadowing(OutputShadowing)
		,m_nSizeX(SizeX)
		,m_nSizeY(SizeY)
		,m_pPick(pInPick)
		//,m_bPickTerrain(false)
	{
		assert(pTile);
		assert(pLight);
		assert(OutputShadowing);
		m_LightEvaluator.SetLightActor(pLight);
		m_vecLastCollideObjs.clear();
	}

	typedef Vector InterpolantType;
	inline void ProcessPixel(INT X, INT Y, const Vector& Position, UINT uiNormalId, UINT uiFaceIndex)
	{
		if ( X < 0 || Y < 0 || X >= m_nSizeX || Y >= m_nSizeY || !m_pShadowing )
			return;

		INT Offset = Y * m_nSizeX + X;

		// 光照按距离衰减到0
		if (m_LightEvaluator.Distance_Attenuation(Position) <= 0)
		{
			(*m_pShadowing)[Offset].fShadowValue = 0.f;
			(*m_pShadowing)[Offset].uiNormalIndex = uiNormalId;
			return;
		}

		const float TracePushout = 100.f;//0.2f;//1.5f;
		Vector	LightVector = m_LightEvaluator.Raytrace_End(Position) - Position;
		CResMgr* resMgr = m_pTile->GetCResMgr();
		if( !resMgr )
			return;

		Vector rayDir = LightVector; //方向光的话 是指向 顶点的方向。
		rayDir.normalize();
		Vector rayStart = Position + rayDir * TracePushout;

		BOOL bOccluded = FALSE;
		//if( m_bPickTerrain )
		//{
		//	TPickResult result;
		//	if( m_pPick->Pick(rayStart, rayDir, result) )
		//	{
		//		bOccluded = true;
		//	}
		//}

		if( !bOccluded && m_vecLastCollideObjs.size() )
		{
			for( int j=0; j<m_vecLastCollideObjs.size(); ++j )
			{
				if( !m_vecLastCollideObjs[j] )
					continue;

				bOccluded = MexAnimCtrl::IntersectQuick(m_vecLastCollideObjs[j]->model, (D3DXVECTOR3*)&rayStart, (D3DXVECTOR3*)&rayDir );
				if( bOccluded )
					break;
			}
		}
		if( !bOccluded )
		{
			// 保存已判断过模型，防止重复判断
			std::map<TObjectInfo*,TObjectInfo*> vecProcessedObjests;

			CWorldChunk* pMyChunk = m_pTile->GetChunkFromPos(Position.x, Position.y); //得到地形块
			if( !pMyChunk )
				return;

			float fDirX = m_LightEvaluator.GetLightXAxisLength() / WORLD_CHUNKSIZE;
			int nSignX = (fDirX == abs(fDirX)) ? 1 : -1;
			int nDirX = ceil(abs(fDirX));
			float fDirY = m_LightEvaluator.GetLightYAxisLength() / WORLD_CHUNKSIZE;
			int nSignY = (fDirY == abs(fDirY)) ? 1 : -1;
			int nDirY = ceil(abs(fDirY));

			for(int dirx = 0 ; dirx <= nDirX; ++dirx)
			{
				for(int diry = 0 ; diry <=nDirY; ++diry)
				{	
					CWorldChunk* pWorldChunk = m_pTile->GetChunk(pMyChunk->GetChunkX() + dirx * nSignX, pMyChunk->GetChunkY() + diry * nSignY);
					if( !pWorldChunk )
						continue;

					// 判断地表
// 					TPickResult result;
// 					if( m_pPick->Pick(rayStart, rayDir, result) )
// 					{
// 						m_bPickTerrain = true;
// 						bOccluded = true;
// 						break;
// 					}

					// 判断模型

					if( pWorldChunk->GetStaticModelList().size() == 0 )
						continue;

					int nModelNum = pWorldChunk->GetStaticModelList().size();
					for( INT ModelIndex = 0; ModelIndex < nModelNum; ++ModelIndex )
					{
						sInt32 nModelId = pWorldChunk->GetStaticModelList()[ModelIndex];

						if( nModelId >= resMgr->GetStaticModelList().size() )
							continue;

						TObjectInfo* pObjInfo = resMgr->GetStaticModelList()[nModelId];
						if( !pObjInfo ||
							!pObjInfo->model ||
							!pObjInfo->model->GetMex() ||
							!((Mex2*)(pObjInfo->model->GetMex()))->GetGeometry() )
							continue;

						// 是否判断过
						std::map<TObjectInfo*,TObjectInfo*>::iterator iter = vecProcessedObjests.find(pObjInfo);
						if( iter == vecProcessedObjests.end() )
						{
							vecProcessedObjests.insert(std::map<TObjectInfo*,TObjectInfo*>::value_type(pObjInfo,pObjInfo));
							// 是否投影
							if( pObjInfo->CastShadow() )
							{
								bOccluded = MexAnimCtrl::IntersectQuick(pObjInfo->model, (D3DXVECTOR3*)&rayStart, (D3DXVECTOR3*)&rayDir );
								if( bOccluded )
								{
									m_vecLastCollideObjs.push_back(pObjInfo);
									break;
								}
							}
						}
					}
				}
			}
		}

		(*m_pShadowing)[Offset].fShadowValue += bOccluded ? 0.f : 1.f; //lyh
		(*m_pShadowing)[Offset].uiNormalIndex = uiNormalId;
		(*m_pShadowing)[Offset].uiFaceIndex = uiFaceIndex;
	}

private:
	CWorldTile*					m_pTile;
	std::vector<ShadowData>*	m_pShadowing;
	INT							m_nSizeX;
	INT							m_nSizeY;
	LightRes*					m_pLight;
	LightAttenuationEvaluator	m_LightEvaluator;
	std::vector<TObjectInfo*>	m_vecLastCollideObjs;
	CNdlWorldPickerBase*		m_pPick;
	//bool						m_bPickTerrain;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StaticMeshCoverageFunctor
{
public:

	StaticMeshCoverageFunctor(std::vector<Vector>* OutputPosition, std::vector<BYTE>* OutputCoverage, INT SizeX, INT SizeY)
		:Position(OutputPosition)
		,Coverage(OutputCoverage)
		,m_nSizeX(SizeX)
		,m_nSizeY(SizeY)
	{}

	typedef Vector InterpolantType;
	inline void ProcessPixel(INT X,INT Y, const Vector& Pos, UINT uiNormalId, UINT uiFaceIndex)	//为了统一接口，增加uiNormalId和uiFaceIndex参数，此处没用到
	{
		if (X < 0 || Y < 0 || X >= m_nSizeX || Y >= m_nSizeY)
			return;
		INT Offset = Y * m_nSizeX + X;

		assert((*Coverage)[Offset] <= 255);  //lyh++  < 改为 <=
		(*Coverage)[Offset]++;
		(*Position)[Offset] = Pos;
	}

private:
	std::vector<Vector>*	Position;
	std::vector<BYTE>*		Coverage;
	INT						m_nSizeX;
	INT						m_nSizeY;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int StaticMeshRayTracer::RetrieveIlluminateObjects()
{
	assert(m_pTile);
	CResMgr* resMgr = m_pTile->GetCResMgr();
	if( !resMgr )
		return -1;

	ReleaseData();

	UINT uiTotalFaceCount = 0;
	// 搜集需要创建灯光图的模型列表
	for( INT ChunkIndex = 0; ChunkIndex < m_pTile->GetChunkTotal(); ++ChunkIndex )
	{
		CWorldChunk* pWorldChunk = m_pTile->GetChunk(ChunkIndex);
		if( pWorldChunk->GetStaticModelList().size() == 0 )
			continue;

		int nModelNum = pWorldChunk->GetStaticModelList().size();

		// 查找chunk里模型
		for( INT ModelIndex = 0; ModelIndex < nModelNum; ++ModelIndex )
		{
			sInt32 nModelId = pWorldChunk->GetStaticModelList()[ModelIndex];

			if( nModelId >= resMgr->GetStaticModelList().size() )
				continue;

			TObjectInfo* pObjInfo = resMgr->GetStaticModelList()[nModelId];
			if( !pObjInfo )
				continue;

			// 清除旧ColorData索引
			pObjInfo->ClearColorData();
			int iFaceCount = 0;
			IlluminateOneObject(pObjInfo, ChunkIndex, iFaceCount);
			uiTotalFaceCount += iFaceCount;
		}// end for
	}// end for

	if( uiTotalFaceCount )
	{
		PrepareData(uiTotalFaceCount);
	}

	if( m_IlluminateObjects.size() )
	{
		// 清楚已有模型灯光数据
		MeshLightmapColorData::GetInstance()->Clear();
	}
	return m_IlluminateObjects.size();
}

int StaticMeshRayTracer::IlluminateOneObject(TObjectInfo* pObjInfo, int nTerrainChunkId, int& iOutFaceCount)
{
	iOutFaceCount = 0;

	if( !pObjInfo ||
		!pObjInfo->model ||
		!pObjInfo->model->GetMex() ||
		!((Mex2*)(pObjInfo->model->GetMex()))->GetGeometry() )
		return m_IlluminateObjects.size();

	// 去掉草模型
	char name[MAX_PATH] = {0};
	strncpy(name, pObjInfo->model->GetMex()->GetFilename(), sizeof(name)-1 );
	strlwr(name);
	if( strstr(name, "grass") )
		return m_IlluminateObjects.size();

	// 是否投影
	if( pObjInfo->CastShadow() )
	{
		MeMatrix mat;
		pObjInfo->model->CalcTransformMatrix( &mat );

		// 查找静态模型，并检查静态实例一致性
		bool bHaveStaticMesh = false;
		bool bRecreateInstance = false;
		Mex2Geometry* pGeometry = (Mex2Geometry*)((Mex2*)(pObjInfo->model->GetMex()))->GetGeometry();
		UINT uiGeoFaceCount = 0;

		for( int nGeoChunk = 0; nGeoChunk < pGeometry->GetChunkCount(); ++nGeoChunk ) //查找子集
		{
			if( !pGeometry->GetChunk(nGeoChunk) )
				continue;

			Mex2GeoChunk* pGeoChunk = (Mex2GeoChunk*)pGeometry->GetChunk(nGeoChunk);

			if( pGeometry->GetChunk(nGeoChunk)->GetType() == Mex2GeoChunkProperty::eStatic/* &&*/
				/*pGeoChunk->IsLighting() &&*/
				//!pGeoChunk->IsTreeLeaf() &&
				//pGeoChunk->HaveShadow()
				)
			{
				bHaveStaticMesh = true;

				// 判断光照图UV层
				if( pGeoChunk->GetLightmapLayer() < 0 )
				{
					bHaveStaticMesh = false;
					uiGeoFaceCount = 0;
					// 提示
					char msg[256] = {0};
					sprintf_s(msg, sizeof(msg)-1, "-> WARNING: Model %s doesn't have lightmap layer, check model version.\n", 
						pGeoChunk->GetMex()->GetFilename());
					OutputDebugString(msg);
					break;
				}

				uiGeoFaceCount += pGeoChunk->GetFaceCount();
				if( !bRecreateInstance )
				{
					// 检查静态实例是否一致
					CStaticGeoChunk* pStaticGeoChunk = (CStaticGeoChunk*)pGeoChunk;
					StaticMeshInstance* pStaticMeshInstance = pObjInfo->GetStaticMeshInstanceByChunkId(nGeoChunk);
					if( pStaticMeshInstance )
					{
						if( pStaticMeshInstance->GetStaticMesh() != pStaticGeoChunk ||
							pStaticMeshInstance->GetVertexCount() != pStaticGeoChunk->GetVertexCount() )
						{
							bRecreateInstance = true;
							break;
						}
					}
					else
					{
						bRecreateInstance = true;
						break;
					}
				}// end if
			}// end if
		}// end for

		// 重建包围盒
		pObjInfo->model->BuildWorldBBox();

		if( bHaveStaticMesh )
		{
			// 是否已放入IlluminateObjects
			bool bFind = false;
			std::map<TObjectInfo*, IlluminateData>::iterator iter = m_IlluminateObjects.find(pObjInfo);
			if( iter != m_IlluminateObjects.end() )
			{
				bFind = true;
				// 保存模型所在地表Chunk，获取灯光用
				iter->second.vecChunkId.push_back(nTerrainChunkId);
			}
			if( !bFind )
			{
				IlluminateData Data(pObjInfo, nTerrainChunkId);
				m_IlluminateObjects.insert(std::map<TObjectInfo*, IlluminateData>::value_type(pObjInfo, Data));
				iOutFaceCount += uiGeoFaceCount;
			}

			// 重新创建静态实例
			if( bRecreateInstance )
			{
				pObjInfo->DestroyStaticMeshInstances();
				for( int nGeoChunk = 0; nGeoChunk < pGeometry->GetChunkCount(); ++nGeoChunk )
				{
					Mex2GeoChunk* pGeoChunk = (Mex2GeoChunk*)pGeometry->GetChunk(nGeoChunk);
					if( pGeoChunk->GetType() == Mex2GeoChunkProperty::eStatic )
					{
						pObjInfo->CreateStaticMeshInstance(pGeoChunk, nGeoChunk);
					}
				}
			}
		}
	}
	else
	{
		pObjInfo->DestroyStaticMeshInstances();
	}//end else

	return m_IlluminateObjects.size();
}

void StaticMeshRayTracer::RayTraceObject(int id, CNdlWorldPickerBase* pPick)
{
	if( id < 0 || id >= m_IlluminateObjects.size() )
		return;

	// Ray trace
	std::map<TObjectInfo*, IlluminateData>::iterator iter = m_IlluminateObjects.begin();
	int count = 0;
	while(count < id)
	{
		++count;
		++iter;
	}
	RayTrace(iter->second, pPick);
}

void StaticMeshRayTracer::BuildObjectResource(int id)
{
	if( id < 0 || id >= m_IlluminateObjects.size() )
		return;

	// 生成物件光照数据
	std::map<TObjectInfo*, IlluminateData>::iterator iter = m_IlluminateObjects.begin();
	int count = 0;
	while(count < id)
	{
		++count;
		++iter;
	}
	TObjectInfo* pObject = iter->first;
	if( pObject )
	{
		BuildResources(pObject);	

		// 清除LightChanged
		pObject->SetLightChanged(false);
	}
}

void StaticMeshRayTracer::ReleaseData()
{
	m_IlluminateObjects.clear();
	m_vecNormalList.clear();
	SAFE_DELETE(m_pLayoutMgr);
	ReleaseNdlLightMap();
}

void StaticMeshRayTracer::PrepareData( int nFaceCount )
{
	m_vecNormalList.reserve(nFaceCount);
	PrepareLights();
}

void StaticMeshRayTracer::RayTrace( IlluminateData& Data, CNdlWorldPickerBase* pPick )
{
	if( !Data.pObject || Data.pObject->GetStaticMeshIntanceCount() == 0 )
		return;

	if( !m_pLayoutMgr )
		AllocateLayoutMgr();

	TObjectInfo* pObject = Data.pObject;
	int submodel = 0;
	// 逆序遍历StaticMeshIntance，防止删除后下标不对
	for( int obj = pObject->GetStaticMeshIntanceCount()-1; obj >= 0; --obj )
	{
		StaticMeshInstance* pStaticMeshInstance = pObject->GetStaticMeshInstance(obj);
		if( !pStaticMeshInstance )
		{
			continue;
		}

		// 检查
		if( !pStaticMeshInstance->GetObjectInfo() || !pStaticMeshInstance->GetStaticMesh() || !pStaticMeshInstance->GetStaticMesh()->GetMex() )
		{
			pObject->DestroyStaticMeshInstance(obj);
			continue;
		}

		assert(pStaticMeshInstance->GetObjectInfo() == pObject);

		char szTemp[MAX_PATH] = {0};
		char szMexName[MAX_PATH] = {0};
		strncpy(szTemp, pStaticMeshInstance->GetStaticMesh()->GetMex()->GetFilename(), sizeof(szTemp)-1);
		strlwr(szTemp);
		char *p = strstr(szTemp, "data\\");
		if( p )
			strncpy(szMexName, p, sizeof(szMexName)-1);
		else
			strncpy(szMexName, szTemp, sizeof(szMexName)-1);

		// 区分改动部分还是全部
		//if (m_bChangedOnly && !pObject->LightChanged())
		//	pStaticMeshInstance->GetLightingCache()->ClearChangedOnly();
		//else
			pStaticMeshInstance->GetLightingCache()->Clear();

		if( pStaticMeshInstance->GetStaticMesh()->GetLightmapLayer() < 0 )
		{
			// 无光照图UV层
			char msg[256] = {0};
			sprintf_s(msg, sizeof(msg)-1, "-> WARNING: Model %s doesn't have lightmap layer, check model version.\n", szMexName);
			OutputDebugString(msg);
			return;
		}

		// 如果CalculateLightmapResolution返回0则不创建灯光图
		INT LightmapResolution = CalculateLightmapResolution(pObject);

		const BOOL ShouldGenerateSMLightMaps = LightmapResolution > 0 &&
									pStaticMeshInstance->GetStaticMesh()->GetLightmapLayer() < pStaticMeshInstance->GetStaticMesh()->GetUVLayerCount();

		if (ShouldGenerateSMLightMaps)
		{
			++submodel;

			std::vector<LightRes*> Lights;
			GetRelevantLights(Data, Lights);

			{
				char msg[256] = {0};
				sprintf_s(msg, sizeof(msg)-1, " -> Illumination %s sub model %d", szMexName, submodel);
				OutputDebugString(msg);
			}

			DWORD dwStartTime = HQ_TimeGetTime();
			DWORD dwEndTime;

			pStaticMeshInstance->GetLightingCache()->SetDimensions(LightmapResolution, LightmapResolution);

			MeMatrix mat;
			pObject->model->CalcTransformMatrix( &mat );

			// 用射线计算灯光图
			RayTrace_Lightmap(pObject, pStaticMeshInstance, mat, LightmapResolution, Lights, pPick);
			
			dwEndTime = HQ_TimeGetTime();
			{
				char msg[256] = {0};
				sprintf_s(msg, sizeof(msg)-1, " finished in %.2f seconds\n",
					(dwEndTime-dwStartTime)*0.001f);
				OutputDebugString(msg);
			}
		}
	}
}

INT StaticMeshRayTracer::CalculateLightmapResolution( TObjectInfo* pObject )
{
	BYTE LightMapScale = pObject->GetLightMapScale();

	INT LightMapResolution = 0;
	switch ( LightMapScale )
	{
	case TObjectInfo::LMS_No_Lightmap :
		return 0;

	case TObjectInfo::LMS_4 : LightMapResolution = 4; break;
	case TObjectInfo::LMS_8 : LightMapResolution = 8; break;
	case TObjectInfo::LMS_16 : LightMapResolution = 16; break;
	case TObjectInfo::LMS_32 : LightMapResolution = 32; break;
	case TObjectInfo::LMS_64 : LightMapResolution = 64; break;
	case TObjectInfo::LMS_128 : LightMapResolution = 128; break;
	case TObjectInfo::LMS_256 : LightMapResolution = 256; break;
	case TObjectInfo::LMS_512 : LightMapResolution = 512; break;
	//case TObjectInfo::LMS_1024 : LightMapResolution = 1024; break;

	default:
		// 非法枚举
		assert( FALSE );
		break;
	}

	//if ( ( GRebuildTools.GetCurrent()->LightmapQuality != LQ_HIGH ) && ( LightMapResolution > 256 ) )
	//	LightMapResolution = 256;

	if ( ( LightMapResolution != LIGHTMAP_TEXTURE_WIDTH ) && ( LightMapResolution != 4 ) && ( m_pLayoutMgr != NULL ) )
		// if not the maximum then we should subtract the padding for the lightmaps from the resolution
		// so that we can pack more into one texture
		LightMapResolution -= m_pLayoutMgr->GetBorderPadding() * 2;

	return LightMapResolution;
}

void StaticMeshRayTracer::GetRelevantLights( IlluminateData& Data, std::vector<LightRes*>& Output )
{
	// 场景光
	CResMgr* pResMgr = m_pTile->GetCResMgr();
	for( int i=0; i<Data.vecChunkId.size(); ++i )
	{
		CWorldChunk* worldChunk = m_pTile->GetChunk( Data.vecChunkId[i] );
		if( NULL != worldChunk )
		{
			if( RES_INVALID_ID != worldChunk->GetEnvId() )
			{
				if( worldChunk->GetEnvId() >=0 && worldChunk->GetEnvId() < pResMgr->GetEnvResList().size() )
				{
					CNdlEnvRes* envRes = (CNdlEnvRes*)pResMgr->GetEnvRes( worldChunk->GetEnvId() );
					CNdlLightRes* pNdlLight = (CNdlLightRes*)pResMgr->GetLightRes( envRes->GetLightId() );
					// 目前一个chunk只有一个灯光
					if( pNdlLight )
					{
						LightRes* pLightRes = NULL;
						std::map<CNdlLightRes*, LightRes*>::iterator iter = m_mapNdlLights.find(pNdlLight);
						if( iter == m_mapNdlLights.end() )
							pLightRes = CreateNdlLightMap(pNdlLight);
						else
							pLightRes = iter->second;
						Assert(pLightRes);

						bool bFind = false;
						for( int k=0; k<Output.size(); ++k )
						{
							if( pLightRes == Output[k] )
							{
								bFind = true;
								break;
							}
						}
						if( !bFind )
							Output.push_back(pLightRes);
					}
				}
				else
				{
					char text[MAX_PATH] = {0};
					sprintf_s(text, sizeof(text)-1, "第%d，%d地表chunk无灯光，该chunk上物件无投影！", worldChunk->GetChunkX(), worldChunk->GetChunkY());
					OutputDebugString(text);
					OutputDebugString("\n");
					MessageBox( NULL, text, "错误", MB_OK );
				}
			}
		}
	}

	// 静态光源
	std::vector<LightRes*> vecLights;
	vecLights.clear();
	if( StaticLightsContainer::GetInstance()->GetAffectLights(Data.pObject, m_pTile, vecLights, FALSE) )
	{
		for( int i=0; i<vecLights.size(); ++i )
		{
			if( vecLights[i] )
				Output.push_back(vecLights[i]);
		}
	}
}

void StaticMeshRayTracer::RayTrace_Lightmap( TObjectInfo* pObject, StaticMeshInstance* pStaticMeshInstance,
											const MeMatrix& LocalToWorld, INT LightmapResolution, std::vector<LightRes*>& Lights,
											CNdlWorldPickerBase* pPick )
{
	assert(pObject && pStaticMeshInstance);
	if( !pObject || !pStaticMeshInstance )
		return;

	Mex2GeoChunk* pMesh = pStaticMeshInstance->GetStaticMesh();
	if( !pMesh )
		return;

	assert(pMesh->GetLightmapLayer() < pMesh->GetUVLayerCount());

	for( INT iLight=0; iLight < Lights.size(); ++iLight )
	{
		if( !Lights[iLight] )
			continue;

		if( !pStaticMeshInstance->GetLightingCache()->IsCached(Lights[iLight]) )
		{
			LightmapTraceLight(pObject, pStaticMeshInstance->GetStaticMesh(), LocalToWorld, LightmapResolution, Lights[iLight], m_vecShadowData, pPick);

			// 判断光照亮度
			BOOL Illuminated = FALSE;
			for( INT i=0; i < m_vecShadowData.size(); ++i )
			{
				if( m_vecShadowData[i].fShadowValue > 0.f )
				{
					Illuminated = TRUE;
					break;
				}
			}

			if( Illuminated )
				pStaticMeshInstance->GetLightingCache()->SaveVisibilityData(Lights[iLight], m_vecShadowData, m_vecShadowData.size());
			else
				pStaticMeshInstance->GetLightingCache()->AddIgnoreLight(Lights[iLight]);
		}
	}
}

void StaticMeshRayTracer::LightmapTraceLight( TObjectInfo* pObject, Mex2GeoChunk* pMesh, const MeMatrix& LocalToWorld,
											  INT LightmapResolution, LightRes* pLight, std::vector<ShadowData>& Output,
											  CNdlWorldPickerBase* pPick )
{
	if( !pObject || !pMesh || !pLight )
		return;

	INT UVIndex = pMesh->GetLightmapLayer();
	if( UVIndex < 0 )
		return;

	Output.clear();
	Output.resize(LightmapResolution*LightmapResolution, ShadowData());

	// 矩阵行列式值
	FLOAT Determinant = D3DXMatrixDeterminant((D3DXMATRIX*)&LocalToWorld);

	// 光衰减计算
	LightAttenuationEvaluator LightEval(pLight);

	StaticMeshShadowingFunctor Functor(m_pTile, pLight, &Output, LightmapResolution, LightmapResolution, pPick);
	TriangleRasterizer<StaticMeshShadowingFunctor> Rasterizer(Functor);

	// 计算半透遮光面
	std::vector<FLOAT> LightMask;
	CalculateLightMask(pMesh, pLight, LightMask);

	// 光栅处理三角形
	BOOL IsTwoSided = FALSE;
	if( pMesh->GetMtlId() != -1 )
	{
		Mex2Material* pMtl = (Mex2Material*)pMesh->GetMex()->GetMtls()->GetMtl( pMesh->GetMtlId() );
		if( !pMtl && pMtl->GetLayer(0) )
		{
			if( pMtl->GetLayer(0)->GetFlag() & MEX2_TWOSIDED )
				IsTwoSided = TRUE;
		}
	}

	const Vector* pVertices = pMesh->GetVertices();
	const Mex2Face* pFaces = pMesh->GetFaces();
	const Vector* pNormals = pMesh->GetNormals();
	Vector2* pUVs = pMesh->GetUVs(UVIndex);

	for(UINT TriangleIndex = 0; TriangleIndex < pMesh->GetFaceCount(); ++TriangleIndex)
	{
		Vector	Vertices[3];
		Vector2	TexCoords[3];
		const Mex2Face& Face = pFaces[TriangleIndex];

		for(UINT VertexIndex = 0;VertexIndex < 3;VertexIndex++)
		{
			Vector Vertex = pVertices[Face.nId[VertexIndex]];
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&Vertices[VertexIndex], 
				(D3DXVECTOR3*)&Vertex,	
				(D3DXMATRIX*)&LocalToWorld );
			
			float fGutter = 2.f * LightmapResolution / 256.f;	// 是D3DUtil_GenerateUVs里Gutter / resolution的一半大小
			TexCoords[VertexIndex] = pUVs[Face.nId[VertexIndex]] * LightmapResolution - Vector2(fGutter,fGutter);
		}

		// 检测三角形是否受到光照影响
		BOOL Illuminated = IsTwoSided || FaceIlluminated(&LightEval, Determinant, Vertices);
		if (Illuminated && fabs(LightMask[Face.nId[0]]) < 0.0001f)
		{
			// 计算三角形法线
			Vector L1 = Vertices[1] - Vertices[0];
			Vector L2 = Vertices[2] - Vertices[0];
			Vector vNormal = L1.cross(L2);
			vNormal.normalize();
			m_vecNormalList.push_back(vNormal);
			Rasterizer.DrawTriangle(Vertices[0],Vertices[1],Vertices[2],TexCoords[0],TexCoords[1],TexCoords[2],m_vecNormalList.size()-1, TriangleIndex);
		}
	}
}

void StaticMeshRayTracer::CalculateLightMask( Mex2GeoChunk* pMesh, LightRes* pLight, std::vector<FLOAT>& Output )
{
	Output.clear();
	Output.resize(pMesh->GetVertexCount(), 0.f);

	// TODO: 处理点光源，材质是半透的，顶点对应Output[index] = 1.0f;

}

BOOL StaticMeshRayTracer::FaceIlluminated( LightAttenuationEvaluator* pLight, FLOAT MeshDeterminant, Vector* Vertices )
{
	if( !pLight )
		return FALSE;

	// 判断是否背光
	D3DXPLANE FacePlane;

	D3DXPlaneFromPoints(&FacePlane, (D3DXVECTOR3*)&Vertices[0], (D3DXVECTOR3*)&Vertices[1], (D3DXVECTOR3*)&Vertices[2] );
	D3DXPlaneNormalize(&FacePlane, &FacePlane);
	if (MeshDeterminant < 0)
	{
		FacePlane.a = -FacePlane.a;
		FacePlane.b = -FacePlane.b;
		FacePlane.c = -FacePlane.c;
		FacePlane.d = -FacePlane.d;
	}
	BOOL FullyAttenuated = pLight->Surface_Attenuated(FacePlane);

	return !FullyAttenuated;
}

void StaticMeshRayTracer::BuildResources( TObjectInfo* pObject )
{
	std::vector<sInt32> vecOldColorData;
	vecOldColorData.clear();
	if( pObject->GetColorData().size() )
	{
		const std::map<sInt16, sInt32>& mapColorData = pObject->GetColorData();
		std::map<sInt16, sInt32>::const_iterator iter = mapColorData.begin();
		for( ; iter != mapColorData.end(); ++iter )
		{
			sInt32 nColorIndex = iter->second;
			vecOldColorData.push_back(nColorIndex);
		}
	}
	// 清除旧ColorData索引
	pObject->ClearColorData();

	int nInsCount = 0;
	for( int index = pObject->GetStaticMeshIntanceCount()-1; index >= 0; --index )
	{
		StaticMeshInstance* pStaticMeshInstance = pObject->GetStaticMeshInstance(index);
		if( !pStaticMeshInstance ||
			!pStaticMeshInstance->GetStaticMesh() ||
			pStaticMeshInstance->GetStaticMesh()->GetLightmapLayer() < 0 )
			continue;

		// 如果没有灯光，则删除
		if( pStaticMeshInstance->GetLightingCache()->GetLightCount() == 0 )
		{
			pObject->DestroyStaticMeshInstance(index);
			continue;
		}

		// 添加灯光
 		for(int i=0; i < pStaticMeshInstance->GetLightingCache()->GetLightCount(); ++i)
 		{
 			pStaticMeshInstance->AddUniqueLight(pStaticMeshInstance->GetLightingCache()->GetLight(i));
 		}


		// 基于每层创建灯光数据
		MeMatrix mat;
		pObject->model->CalcTransformMatrix( &mat );
		
		// 复用旧ColorData索引
		int nColorDataIndex = -1;
		++nInsCount;
		if( nInsCount <= vecOldColorData.size() )
			nColorDataIndex = vecOldColorData[nInsCount-1];

		int nNewColorDataIndex = Build_LightMaps(pStaticMeshInstance, mat, nColorDataIndex);
		if( nNewColorDataIndex >= 0 )
		{
			pObject->PushColorData(pStaticMeshInstance->GetChunkIndex(), nNewColorDataIndex);
		}
	}
}

int StaticMeshRayTracer::Build_LightMaps( StaticMeshInstance* pStaticMeshInstance, const MeMatrix& LocalToWorld, int nColorDataIndex )
{
	Mex2GeoChunk* StaticMesh = pStaticMeshInstance->GetStaticMesh();
	if( NULL == StaticMesh )
		return -1;

	INT UVIndex = StaticMesh->GetLightmapLayer();
	assert(pStaticMeshInstance->GetLightingCache()->IsSquare());
	INT LightmapResolution = pStaticMeshInstance->GetLightingCache()->GetWidth();

	// 模型覆盖率记录到贴图
	std::vector<BYTE> Coverage; Coverage.clear(); Coverage.resize(LightmapResolution*LightmapResolution, 0);
	std::vector<Vector> Position; Position.clear(); Position.resize(LightmapResolution*LightmapResolution, Vector::ZERO);	
	StaticMeshCoverageFunctor CoverFunctor(&Position, &Coverage, LightmapResolution, LightmapResolution);
	TriangleRasterizer<StaticMeshCoverageFunctor> CoverageRasterizer(CoverFunctor);

	const Mex2Face* pFaces = StaticMesh->GetFaces();
	const Vector* pVertices = StaticMesh->GetVertices();
	Vector2* pUVs = StaticMesh->GetUVs(UVIndex);
	for(UINT TriangleIndex = 0;TriangleIndex < (UINT)StaticMesh->GetFaceCount();++TriangleIndex)
	{
		Vector	Vertices[3];
		Vector2	TexCoords[3];
		const Mex2Face& Face = pFaces[TriangleIndex];

		for(UINT VertexIndex = 0;VertexIndex < 3;VertexIndex++)
		{
			Vector Vertex = pVertices[Face.nId[VertexIndex]];
			D3DXVec3TransformCoord( (D3DXVECTOR3*)&Vertices[VertexIndex], 
				(D3DXVECTOR3*)&Vertex,	
				(D3DXMATRIX*)&LocalToWorld );
			float fGutter = 2.f * LightmapResolution / 256.f;
			TexCoords[VertexIndex] = pUVs[Face.nId[VertexIndex]] * LightmapResolution - Vector2(fGutter,fGutter);
		}
		CoverageRasterizer.DrawTriangle(Vertices[0],Vertices[1],Vertices[2],TexCoords[0],TexCoords[1],TexCoords[2]);
	}

	// 需要平滑/过滤每个灯阴影图
	LightBitmapFilter Filter;

	LayerData* pLayerData = pStaticMeshInstance->GetLayer();
	if( !pLayerData )
		return -1;

	// 创建灯光图，保存到临时buffer里
	NiColorB* ColorData = new NiColorB[LightmapResolution*LightmapResolution];

	memset(ColorData, 0, LightmapResolution*LightmapResolution*sizeof(NiColorB));

	// 用LuminanceMapFunctor处理每层
	LuminanceMapFunctor Functor(ColorData, LightmapResolution*LightmapResolution, 
		pStaticMeshInstance->GetLights(), pStaticMeshInstance->GetLights().size(), 1);

	// 处理每个灯光
	for (INT l=0; l < pStaticMeshInstance->GetLights().size(); ++l)
	{
		LightRes* pLight = pStaticMeshInstance->GetLights()[l];
		const StaticLightingCache::VisibilityData* LightData = pStaticMeshInstance->GetLightingCache()->GetVisiblityData(pLight);
		if( !LightData )
			continue;
		assert(LightData->GetSampleCount() == Coverage.size());

		m_vecShadowData.clear();
		m_vecShadowData.resize(LightData->GetSampleCount(), ShadowData());
		LightData->LoadSamples(m_vecShadowData);
		Filter.SmoothVisibilityFloatMask(StaticMesh, m_vecShadowData, LightmapResolution, LightmapResolution, this, &Coverage);

		Functor.SetLightActor(pLight);
		for (INT v = 0; v < Coverage.size(); ++v)
		{
			BYTE PixelCoverage = Coverage[v];
			if (PixelCoverage)
			{
				FLOAT Shadow = m_vecShadowData[v].fShadowValue / (FLOAT)PixelCoverage;
				Functor.ProcessSample(Position[v], m_vecNormalList[m_vecShadowData[v].uiNormalIndex],Shadow, v);
			}
		}
	}

	// 颜色溢出隐藏边界
	Filter.CoverageEdgeBleed(ColorData, &Coverage, LightmapResolution, LightmapResolution);

	// 保存ColorData到MeshLightmapColorData::GetInstance()
	MeshLightmapColorData::LMColorData* pData = new MeshLightmapColorData::LMColorData;
	if( pData )
	{
		pData->m_nColorDataResolution = LightmapResolution;
		pData->m_pColorData = ColorData;
		nColorDataIndex = MeshLightmapColorData::GetInstance()->PushColorData(nColorDataIndex, pData, true);
	}

	if( pStaticMeshInstance->GetLayer()->LightMapIndex >= 0 )
	{
		// 测试新UV
		//const StaticMeshInstance::LayerData& LayerData = pStaticMeshInstance->GetLayer();
		//pStaticMeshInstance->GetStaticMesh()->TestCreateUVsBuffer(
		//	pStaticMeshInstance->GetStaticMesh()->GetLightmapLayer(),
		//	LayerData.LightMapUVOffset.x,
		//	LayerData.LightMapUVOffset.y,
		//	LayerData.LightMapUVScale.x,
		//	LayerData.LightMapUVScale.y);
	}
	else
	{
		OutputDebugString("灯光图没创建成功！\n");
	}
	return nColorDataIndex;
}

void StaticMeshRayTracer::AllocateLightMap( LayerData& xLayerData, INT LightmapResolution, INT* OffsetX, INT* OffsetY )
{
	assert(m_pLayoutMgr);
	if( !m_pLayoutMgr )
		return;

	// 从整张贴图分配模型需要的灯光图
	INT LightMapIndex = m_pLayoutMgr->AddSurface(OffsetX, OffsetY, LightmapResolution, LightmapResolution);

	LightMapTexture* pLightMapTexture = m_pLayoutMgr->GetSurface(LightMapIndex);//lyh总这里面拿刚刚new出来的的光照图
	assert(pLightMapTexture);

	if( NULL == pLightMapTexture->GetBitmap() )
	{
		// 创建位图数据
		pLightMapTexture->AllocateBitmap();
	}

	// 赋值灯光图信息
	xLayerData.LightMapIndex = LightMapIndex;
	xLayerData.LightMapUVOffset = Vector2((FLOAT)*OffsetX/LIGHTMAP_TEXTURE_WIDTH,(FLOAT)*OffsetY/LIGHTMAP_TEXTURE_HEIGHT);
	xLayerData.LightMapUVScale = Vector2((FLOAT)LightmapResolution/LIGHTMAP_TEXTURE_WIDTH,(FLOAT)LightmapResolution/LIGHTMAP_TEXTURE_HEIGHT);
}

void StaticMeshRayTracer::AllocateObjectLightMap( int id )
{
	if( id < 0 || id >= m_IlluminateObjects.size() )
		return;

	// 生成物件光照数据 //lyh光照图生成入口
	std::map<TObjectInfo*, IlluminateData>::iterator iter = m_IlluminateObjects.begin();
	int count = 0;
	while(count < id)
	{
		++count;
		++iter;
	}
	TObjectInfo* pObject = iter->first;
	if( pObject )
		AllocateObjectLightMap(pObject);
}

void StaticMeshRayTracer::AllocateObjectLightMap( TObjectInfo* pObject )
{
	if( !pObject )
		return;

	if( MeshLightmapColorData::GetInstance()->GetColorDataMap().size() == 0 )
	{
		return;
	}
	const std::map<sInt32, MeshLightmapColorData::LMColorData*>& ColorDataMap = MeshLightmapColorData::GetInstance()->GetColorDataMap();

	for( int index = pObject->GetStaticMeshIntanceCount()-1; index >= 0; --index )
	{
		StaticMeshInstance* pStaticMeshInstance = pObject->GetStaticMeshInstance(index);
		if( !pStaticMeshInstance )
			continue;

		LayerData* pLayerData = pStaticMeshInstance->GetLayer();
		if( !pLayerData )
			continue;

		std::map<sInt16, sInt32>::const_iterator iter = pObject->GetColorData().find(pStaticMeshInstance->GetChunkIndex());
		if( iter == pObject->GetColorData().end() )
		{
			Assert(0&&"TObjectInfo保存灯光数据出错！");
			continue;
		}
		int nColorDataIndex = iter->second;
		std::map<sInt32, MeshLightmapColorData::LMColorData*>::const_iterator cd_iter = ColorDataMap.find(nColorDataIndex);
		if( cd_iter == ColorDataMap.end() || !cd_iter->second )
		{
			Assert(0&&"全局灯光数据查询出错！");
			continue;
		}

		MeshLightmapColorData::LMColorData* pColorData = cd_iter->second;

		// 分辨率
		INT LightmapResolution = pColorData->m_nColorDataResolution;

		// 从全局灯光贴图里分配需要的区域
		INT OffsetX = 0, OffsetY = 0;
		AllocateLightMap(*pLayerData, LightmapResolution, &OffsetX, &OffsetY);
		LightMapTexture* LuminanceMap = m_pTile->GetLightMap(pLayerData->LightMapIndex);
		assert(OffsetX + LightmapResolution <= LuminanceMap->GetWidth());
		assert(OffsetY + LightmapResolution <= LuminanceMap->GetHeight());

		// 数据拷贝到贴图里
		NiColorB* DestBuffer = LuminanceMap->GetBitmap();
		for (INT Y=0; Y < LightmapResolution; ++Y)
		{
			NiColorB* Src = &pColorData->m_pColorData[Y * LightmapResolution]; //把原图颜色数据 拷贝到 光照图的数据里面
			NiColorB* Dest = &DestBuffer[(OffsetY + Y)*LuminanceMap->GetWidth() + OffsetX];	
			memcpy(Dest, Src, LightmapResolution * sizeof(NiColorB));
		}
	}
}

void StaticMeshRayTracer::AllocateLayoutMgr()
{
	SAFE_DELETE(m_pLayoutMgr);
	m_pLayoutMgr = MeNew SurfaceLayoutMgr(m_pTile->GetLightMaps());
}

void StaticMeshRayTracer::CreateNdlLightMaps()
{
	ReleaseNdlLightMap();

	CResMgr* pResMgr = m_pTile->GetCResMgr();
	if( pResMgr && pResMgr->GetEnvResList().size() )
	{
		int count = pResMgr->GetEnvResList().size();
		for( int i=0; i<count; ++i )
		{
			CNdlEnvRes* envRes = (CNdlEnvRes*)pResMgr->GetEnvRes( i );
			if( !envRes )
				continue;
			
			CNdlLightRes* pNdlLight = (CNdlLightRes*)pResMgr->GetLightRes( envRes->GetLightId() );
			if( !pNdlLight )
				continue;
		
			CreateNdlLightMap(pNdlLight);
		}
	}
}

LightRes* StaticMeshRayTracer::CreateNdlLightMap( CNdlLightRes* pNdlLight )
{
	if( !pNdlLight )
		return NULL;

	std::map<CNdlLightRes*, LightRes*>::iterator iter = m_mapNdlLights.find(pNdlLight);
	if( iter == m_mapNdlLights.end() )
	{
		// 方向光
		DirectionLight* pDirLight = MeNew DirectionLight;
		Assert(pDirLight);
		pDirLight->SetChunkLight(true);
		pDirLight->SetDir(pNdlLight->GetLightDir());
		NiColor color;
		NiColorB colorB;
		ConvertRGB2NiColor( pNdlLight->GetLightDiffuse(), color );
		colorB.r = Clamp<BYTE>(color.r*255, 0, 255);
		colorB.g = Clamp<BYTE>(color.g*255, 0, 255);
		colorB.b = Clamp<BYTE>(color.b*255, 0, 255);
		pDirLight->SetColor(colorB);

		m_mapNdlLights.insert(std::map<CNdlLightRes*, LightRes*>::value_type(pNdlLight, pDirLight));
		return pDirLight;
	}
	return iter->second;
}

void StaticMeshRayTracer::ReleaseNdlLightMap()
{
	if( m_mapNdlLights.size() )
	{
		std::map<CNdlLightRes*, LightRes*>::iterator iter = m_mapNdlLights.begin();
		for( ; iter != m_mapNdlLights.end(); ++iter )
		{
			if( !iter->second )
				continue;

			LightRes* pLightRes = iter->second;
			SAFE_DELETE(pLightRes);
		}
		m_mapNdlLights.clear();
	}
}

void StaticMeshRayTracer::PrepareLights()
{
	// 创建场景光源对应的LightRes光源
	CreateNdlLightMaps();
	// 重新计算物件受哪些静态光影响
	StaticLightsContainer::GetInstance()->RetrieveAllObjectsAffectLights(m_pTile);
}
