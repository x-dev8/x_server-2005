//-----------------------------------------------------------------------------
// File:	StaticMeshInstance.h
// Desc:	静态模型实例，用于创建和渲染静态模型灯光图。
// Create: 	01/17/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef STATIC_MESH_INSTANCE_H
#define STATIC_MESH_INSTANCE_H
#include "MeRTLibs.h"
#include <MeFoundation/MeAllocatedObject.h>
#include <Me3d/Vector.h>
#include <Me3d/Model/Mex2.h>

class TObjectInfo;
class Vector2;
class StaticLightingCache;
class Mex2GeoChunk;
class LightRes;

class StaticMeshInstance: public MeCommonAllocObj<StaticMeshInstance>
{
public:
	// 构造
	// Editor生成LightMap用
	StaticMeshInstance(TObjectInfo* pObjectInfo, Mex2GeoChunk* StaticMesh, unsigned short ChunkIndex);
	// 从mew读取后创建用
	StaticMeshInstance(TObjectInfo* pObjectInfo, unsigned short ChunkIndex, INT vertexCount, BYTE lightmapIndex, float* UVOffset, float* UVScale);
	
	virtual ~StaticMeshInstance();

	TObjectInfo*			GetObjectInfo()		{ return m_pObjectInfo; }
	INT						GetVertexCount()	{ return m_nStaticMeshVertexCount; }
	unsigned short			GetChunkIndex()		{ return m_ucChunkIndex; }
	Mex2GeoChunk*			GetStaticMesh();

	void					CreateLightingCache();
	StaticLightingCache*	GetLightingCache();

	LayerData*				GetLayer() { return m_pLayer; }

	void					AddUniqueLight( LightRes* pLight );

	const std::vector<LightRes*> GetLights() const{ return m_Lights; }

protected:
	TObjectInfo*			m_pObjectInfo;
	BYTE					m_ucChunkIndex;				// 模型在Mex2Geometry的chunk下标，加载地图数据后根据Index获取CStaticGeoChunk指针
	INT						m_nStaticMeshVertexCount;	// 验证模型是否改变
	LayerData*				m_pLayer;					// 灯光图信息
	
	// Editor用
	StaticLightingCache*	m_pLightingCache;			
	Mex2GeoChunk*			m_pStaticMesh;				// 通过m_pStaticMesh获取Mex2版本号
	// Editor用
	std::vector<LightRes*>	m_Lights;
};

typedef std::vector<StaticMeshInstance*> StaticMeshInstanceContainer;
typedef StaticMeshInstanceContainer::iterator StaticMeshInstanceContainerIter;
typedef StaticMeshInstanceContainer::const_iterator StaticMeshInstanceContainerConstIter;
#endif