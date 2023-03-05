//-----------------------------------------------------------------------------
// File:	StaticMeshRayTracer.h
// Desc:	计算静态模型光照图
// Create: 	01/14/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef STATIC_MESH_RAYTRACER_H
#define STATIC_MESH_RAYTRACER_H
#include "MeRTLibs.h"
#include "MeTerrain/Lighting/StaticMeshInstance.h"
#include "Me3d/Model/Mex2.h"

class CWorldTile;
class SurfaceLayoutMgr;
class TObjectInfo;
class CNdlLightRes;
class Mex2GeoChunk;
class MeMatrix;
class LightAttenuationEvaluator;
class Vector;
class CNdlWorldPickerBase;
class LightRes;

struct ShadowData
{
	ShadowData()
		:fShadowValue(0.f)
		,uiNormalIndex(0)
		,uiFaceIndex(0)
	{}

	FLOAT				fShadowValue;				// 光照阴影覆盖度
	UINT				uiNormalIndex;				// 指向StaticMeshRayTracer::m_vecNormalList的索引
	UINT				uiFaceIndex;				// 三角形索引，判断邻接像素是否邻接面
};

class StaticMeshRayTracer
{
public:
	// 构造
	StaticMeshRayTracer()
		:m_pTile(NULL)
		,m_pLayoutMgr(NULL)
		,m_bChangedOnly(FALSE)
	{
		m_IlluminateObjects.clear();
		m_mapNdlLights.clear();
	}

	StaticMeshRayTracer(CWorldTile* tile, BOOL ChangedOnly)
		:m_pTile(tile)
		,m_pLayoutMgr(NULL)
		,m_bChangedOnly(ChangedOnly)
	{
		m_IlluminateObjects.clear();
		m_mapNdlLights.clear();
	}

	// 析构
	virtual ~StaticMeshRayTracer() { ReleaseData(); }

	// 创建静态模型光照图主入口
	int RetrieveIlluminateObjects();
	int IlluminateOneObject(TObjectInfo* pObjInfo, int nTerrainChunkId, int& iOutFaceCount);

	void AllocateLayoutMgr();
	void RayTraceObject(int id, CNdlWorldPickerBase* pPick);

	void BuildObjectResource(int id);

	void AllocateObjectLightMap(int id);
	void AllocateObjectLightMap(TObjectInfo* pObject);

	void ReleaseData();
	void PrepareData(int nFaceCount);

	bool GetNormalById(int id, Vector& vOut)
	{
		if( id < 0 || id >= m_vecNormalList.size() )
			return false;

		vOut = m_vecNormalList[id];
		return true;
	}

private:
	struct IlluminateData
	{
		IlluminateData(TObjectInfo* object, INT id): pObject(object)
		{ vecChunkId.clear(); vecChunkId.push_back(id); } 
		TObjectInfo*		pObject;
		std::vector<INT>	vecChunkId;					// 在几个chunk里，则受那几个chunk灯光影响
	};


	// 光线跟踪
	void RayTrace(IlluminateData& Data, CNdlWorldPickerBase* pPick);
	void RayTrace_Lightmap(TObjectInfo* pObject, StaticMeshInstance* pStaticMeshInstance, const MeMatrix& LocalToWorld, INT LightmapResolution,
							std::vector<LightRes*>& Lights, CNdlWorldPickerBase* pPick);
	void LightmapTraceLight(TObjectInfo* pObject, Mex2GeoChunk* pMesh, const MeMatrix& LocalToWorld, INT LightmapResolution, LightRes* pLight,
							std::vector<ShadowData>& Output, CNdlWorldPickerBase* pPick);
	INT CalculateLightmapResolution(TObjectInfo* pObject);
	// 面是否受光照影响
	BOOL FaceIlluminated(LightAttenuationEvaluator* Light, FLOAT MeshDeterminant, Vector* Vertices);
	// 计算半透遮光面
	void CalculateLightMask(Mex2GeoChunk* pMesh, LightRes* pLight, std::vector<FLOAT>& Output);

	// 根据LightCache数据创建每个模型灯光数据
	void BuildResources(TObjectInfo* pObject);
	int Build_LightMaps(StaticMeshInstance* pStaticMeshInstance, const MeMatrix& LocalToWorld, int nColorDataIndex);

	// 从全局Lightmap贴图分配空间保存灯光数据
	void AllocateLightMap(LayerData& LayerData, INT LightmapResolution, INT* OffsetX, INT* OffsetY);

	// 获取模型受哪些光影响
	void GetRelevantLights(IlluminateData& Data, std::vector<LightRes*>& Output);

	// 创建场景光源对应的LightRes光源
	void PrepareLights();
	void CreateNdlLightMaps();
	LightRes* CreateNdlLightMap(CNdlLightRes* pNdlLight);
	void ReleaseNdlLightMap();

	CWorldTile*								m_pTile;
	std::map<TObjectInfo*, IlluminateData>	m_IlluminateObjects;
	std::vector<ShadowData>					m_vecShadowData;		// 光照图每个像素的阴影数据
	SurfaceLayoutMgr*						m_pLayoutMgr;
	BOOL									m_bChangedOnly;			// 只更新改变的模型和灯光
	std::vector<Vector>						m_vecNormalList;		// 记录所有模型的三角形法线表
	std::map<CNdlLightRes*, LightRes*>		m_mapNdlLights;			// 保存CNdlLightRes光源对应的LightRes光源
};

#endif