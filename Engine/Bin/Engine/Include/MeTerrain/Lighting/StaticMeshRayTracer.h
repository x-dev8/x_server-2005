//-----------------------------------------------------------------------------
// File:	StaticMeshRayTracer.h
// Desc:	���㾲̬ģ�͹���ͼ
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

	FLOAT				fShadowValue;				// ������Ӱ���Ƕ�
	UINT				uiNormalIndex;				// ָ��StaticMeshRayTracer::m_vecNormalList������
	UINT				uiFaceIndex;				// �������������ж��ڽ������Ƿ��ڽ���
};

class StaticMeshRayTracer
{
public:
	// ����
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

	// ����
	virtual ~StaticMeshRayTracer() { ReleaseData(); }

	// ������̬ģ�͹���ͼ�����
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
		std::vector<INT>	vecChunkId;					// �ڼ���chunk������Ǽ���chunk�ƹ�Ӱ��
	};


	// ���߸���
	void RayTrace(IlluminateData& Data, CNdlWorldPickerBase* pPick);
	void RayTrace_Lightmap(TObjectInfo* pObject, StaticMeshInstance* pStaticMeshInstance, const MeMatrix& LocalToWorld, INT LightmapResolution,
							std::vector<LightRes*>& Lights, CNdlWorldPickerBase* pPick);
	void LightmapTraceLight(TObjectInfo* pObject, Mex2GeoChunk* pMesh, const MeMatrix& LocalToWorld, INT LightmapResolution, LightRes* pLight,
							std::vector<ShadowData>& Output, CNdlWorldPickerBase* pPick);
	INT CalculateLightmapResolution(TObjectInfo* pObject);
	// ���Ƿ��ܹ���Ӱ��
	BOOL FaceIlluminated(LightAttenuationEvaluator* Light, FLOAT MeshDeterminant, Vector* Vertices);
	// �����͸�ڹ���
	void CalculateLightMask(Mex2GeoChunk* pMesh, LightRes* pLight, std::vector<FLOAT>& Output);

	// ����LightCache���ݴ���ÿ��ģ�͵ƹ�����
	void BuildResources(TObjectInfo* pObject);
	int Build_LightMaps(StaticMeshInstance* pStaticMeshInstance, const MeMatrix& LocalToWorld, int nColorDataIndex);

	// ��ȫ��Lightmap��ͼ����ռ䱣��ƹ�����
	void AllocateLightMap(LayerData& LayerData, INT LightmapResolution, INT* OffsetX, INT* OffsetY);

	// ��ȡģ������Щ��Ӱ��
	void GetRelevantLights(IlluminateData& Data, std::vector<LightRes*>& Output);

	// ����������Դ��Ӧ��LightRes��Դ
	void PrepareLights();
	void CreateNdlLightMaps();
	LightRes* CreateNdlLightMap(CNdlLightRes* pNdlLight);
	void ReleaseNdlLightMap();

	CWorldTile*								m_pTile;
	std::map<TObjectInfo*, IlluminateData>	m_IlluminateObjects;
	std::vector<ShadowData>					m_vecShadowData;		// ����ͼÿ�����ص���Ӱ����
	SurfaceLayoutMgr*						m_pLayoutMgr;
	BOOL									m_bChangedOnly;			// ֻ���¸ı��ģ�ͺ͵ƹ�
	std::vector<Vector>						m_vecNormalList;		// ��¼����ģ�͵������η��߱�
	std::map<CNdlLightRes*, LightRes*>		m_mapNdlLights;			// ����CNdlLightRes��Դ��Ӧ��LightRes��Դ
};

#endif