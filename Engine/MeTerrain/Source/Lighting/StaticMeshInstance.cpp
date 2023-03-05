//-----------------------------------------------------------------------------
// File:	StaticMeshInstance.cpp
// Desc:	静态模型实例，用于创建和渲染静态模型灯光图。
// Create: 	01/17/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#include "MeTerrain/stdafx.h"
#include "MeTerrain/Lighting/StaticMeshInstance.h"
#include "MeTerrain/Lighting/StaticLightingCache.h"
#include "Me3d/Model/MexGeoChunk.h"
#include "MeTerrain/Lighting/LightRes.h"

StaticMeshInstance::StaticMeshInstance( TObjectInfo* pObjectInfo, Mex2GeoChunk* StaticMesh, unsigned short ChunkIndex )
:m_pLightingCache(NULL)
,m_pObjectInfo(pObjectInfo)
,m_pStaticMesh(StaticMesh)
,m_ucChunkIndex(ChunkIndex)
{
	assert(pObjectInfo);
	assert(StaticMesh);
	m_nStaticMeshVertexCount = m_pStaticMesh->GetVertexCount();
	CreateLightingCache();
	m_pLayer = new LayerData;
}

StaticMeshInstance::StaticMeshInstance( TObjectInfo* pObjectInfo, unsigned short ChunkIndex, INT vertexCount, BYTE lightmapIndex, float* UVOffset, float* UVScale )
:m_pLightingCache(NULL)
,m_pObjectInfo(pObjectInfo)
,m_pStaticMesh(NULL)
,m_ucChunkIndex(ChunkIndex)
,m_nStaticMeshVertexCount(vertexCount)
{
	m_pLayer = new LayerData(lightmapIndex, UVOffset[0], UVOffset[1], UVScale[0], UVScale[1]);
}

void StaticMeshInstance::CreateLightingCache()
{
	SAFE_DELETE(m_pLightingCache);

	m_pLightingCache = MeNew StaticLightingCache;
	assert(m_pLightingCache);
}

StaticMeshInstance::~StaticMeshInstance()
{
	m_pStaticMesh = NULL;
	delete m_pLayer;
	m_pLayer = 0;
	SAFE_DELETE(m_pLightingCache);
}

Mex2GeoChunk* StaticMeshInstance::GetStaticMesh()
{
	if( m_pStaticMesh )
		return m_pStaticMesh;

	// TObjectInfo里获取
	if( !m_pObjectInfo ||
		!m_pObjectInfo->model ||
		!m_pObjectInfo->model->GetMex() ||
		!((Mex2*)(m_pObjectInfo->model->GetMex()))->GetGeometry() )
		return NULL;


	// 查找静态模型，并检查静态实例一致性
	Mex2Geometry* pGeometry = (Mex2Geometry*)((Mex2*)(m_pObjectInfo->model->GetMex()))->GetGeometry();
	if( m_ucChunkIndex < pGeometry->GetChunkCount() )
	{
		m_pStaticMesh = (Mex2GeoChunk*)pGeometry->GetChunk(m_ucChunkIndex);
	}
	return m_pStaticMesh;
}

StaticLightingCache* StaticMeshInstance::GetLightingCache()
{
	if( !m_pLightingCache )
		CreateLightingCache();

	return m_pLightingCache;
}

void StaticMeshInstance::AddUniqueLight( LightRes* pLight )
{
	bool bFind = false;
	for( int i=0; i<m_Lights.size(); ++i )
	{
		if( m_Lights[i] == pLight )
		{
			bFind = true;
			break;
		}
	}
	if( !bFind )
		m_Lights.push_back(pLight);
}