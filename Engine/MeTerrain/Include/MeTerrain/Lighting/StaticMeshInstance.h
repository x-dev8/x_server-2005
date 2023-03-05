//-----------------------------------------------------------------------------
// File:	StaticMeshInstance.h
// Desc:	��̬ģ��ʵ�������ڴ�������Ⱦ��̬ģ�͵ƹ�ͼ��
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
	// ����
	// Editor����LightMap��
	StaticMeshInstance(TObjectInfo* pObjectInfo, Mex2GeoChunk* StaticMesh, unsigned short ChunkIndex);
	// ��mew��ȡ�󴴽���
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
	BYTE					m_ucChunkIndex;				// ģ����Mex2Geometry��chunk�±꣬���ص�ͼ���ݺ����Index��ȡCStaticGeoChunkָ��
	INT						m_nStaticMeshVertexCount;	// ��֤ģ���Ƿ�ı�
	LayerData*				m_pLayer;					// �ƹ�ͼ��Ϣ
	
	// Editor��
	StaticLightingCache*	m_pLightingCache;			
	Mex2GeoChunk*			m_pStaticMesh;				// ͨ��m_pStaticMesh��ȡMex2�汾��
	// Editor��
	std::vector<LightRes*>	m_Lights;
};

typedef std::vector<StaticMeshInstance*> StaticMeshInstanceContainer;
typedef StaticMeshInstanceContainer::iterator StaticMeshInstanceContainerIter;
typedef StaticMeshInstanceContainer::const_iterator StaticMeshInstanceContainerConstIter;
#endif