//-----------------------------------------------------------------------------
// File:	StaticLightingCache.h
// Desc:	存储灯光预生成的阴影数据，仅在编辑器中使用。
// Create: 	01/17/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef STATIC_LIGHTING_CACHE_H
#define STATIC_LIGHTING_CACHE_H
#include "MeRTLibs.h"
#include <MeFoundation/MeAllocatedObject.h>
#include "Me3d/Vector.h"
#include "MeTerrain/Lighting/StaticMeshRayTracer.h"

class LightRes;
#define INVALID_LIGHT -1

class StaticLightingCache: public MeCommonAllocObj<StaticLightingCache>
{
public:

	StaticLightingCache(): m_uiWidth(0), m_uiHeight(0) {}
	virtual ~StaticLightingCache() { m_vecVisibilityData.clear(); }

	class VisibilityData: public MeCommonAllocObj<VisibilityData>
	{
	public:

		VisibilityData()
			:m_pLightSource(NULL)
			,m_uiMinX(0)
			,m_uiMinY(0)
			,m_uiMaxX(0)
			,m_uiMaxY(0)
		{
			m_vecVisibility.clear();
			m_vecNormalList.clear();
			m_vecCoverage.clear();
		}
		VisibilityData(LightRes* LightSource, UINT MinX, UINT MinY, UINT MaxX, UINT MaxY)
			:m_pLightSource(LightSource)
			,m_uiMinX(MinX)
			,m_uiMinY(MinY)
			,m_uiMaxX(MaxX)
			,m_uiMaxY(MaxY)
		{
			assert(LightSource);
			m_vecVisibility.clear();
			m_vecNormalList.clear();
			m_vecCoverage.clear();
			m_vecFaceList.clear();
		}

		// 保存一组可视采样数据
		void SaveSamples(const std::vector<ShadowData>& VisibilitySamples, INT NumSamples);
		void SaveCoverage(const BYTE* CoverageSamples, INT NumSamples);

		// 加载一组可视采样数据，VisibilitySamples必须已分配内存
		void LoadSamples(std::vector<ShadowData>& VisibilitySamples) const;
		void LoadCoverage(BYTE* CoverageSamples) const;

		inline UINT GetSampleCount() const			{ return m_vecVisibility.size(); }
		inline UINT GetCoverageCount() const		{ return m_vecCoverage.size(); }
		inline LightRes* GetLightSource() const		{ return m_pLightSource; }
		inline UINT GetWidth() const				{ return m_uiMaxX - m_uiMinX+1; }
		inline UINT GetHeight() const				{ return m_uiMaxY - m_uiMinY+1; }
		inline UINT GetMinX() const					{ return m_uiMinX; }
		inline UINT GetMinY() const					{ return m_uiMinY; }
		inline UINT GetMaxX() const					{ return m_uiMaxX; }
		inline UINT GetMaxY() const					{ return m_uiMaxY; }

	private:
		LightRes*			m_pLightSource;
		std::vector<BYTE>	m_vecVisibility;
		std::vector<UINT>	m_vecNormalList;			// 每个像素的法线索引表
		std::vector<UINT>	m_vecFaceList;				// 每个像素的面索引表
		std::vector<BYTE>	m_vecCoverage;

		UINT				m_uiMinX, m_uiMinY;
		UINT				m_uiMaxX, m_uiMaxY;
	};

	// 从cache里清除所有灯光资源
	void			Clear();

	// 清除改变的灯光资源
	//void			ClearChangedOnly(const std::vector<void*>* vecDeleteLights = NULL);

	// 保存传入可视数据，覆盖已有数据
	void			SaveVisibilityData(LightRes* pLightSource, const std::vector<ShadowData>& Visibility, UINT NumSamples, UINT BorderSize = 0);

	// 获取灯光对应可视数据
	const VisibilityData* GetVisiblityData(LightRes* pLightSource);

	void			SetDimensions(UINT Width, UINT Height);
	UINT			GetWidth() const				{ return m_uiWidth; }
	UINT			GetHeight() const				{ return m_uiHeight; }
	BOOL			IsSquare() const				{ return m_uiWidth == m_uiHeight; }

	INT				GetLightCount()	const			{ return m_vecVisibilityData.size(); }
	LightRes*		GetLight(INT Index) const		{ assert(Index < m_vecVisibilityData.size()); return m_vecVisibilityData[Index].GetLightSource(); }
	INT				GetLightIndex(LightRes* pLightSource) const;

	INT				GetIgnoreLightCount() const		{ return m_vecIgnoreLights.size(); }
	INT				GetIgnoreLightIndex(LightRes* pLightSource) const;
	void			AddIgnoreLight(LightRes* pLightSource);

	BOOL			IsCached(LightRes* pLightSource) 
	{ 
		return GetLightIndex(pLightSource) != INVALID_LIGHT || GetIgnoreLightIndex(pLightSource) != INVALID_LIGHT; 
	}

protected:
	void			SaveVisibilityData(LightRes* pLightSource, const std::vector<ShadowData>& Visibility, UINT NumSamples, UINT MinX, UINT MinY,
									   UINT MaxX, UINT MaxY, UINT BorderSize = 0, const BYTE* Coverage = 0);

	UINT						m_uiWidth;
	UINT						m_uiHeight;
	std::vector<LightRes*>	m_vecIgnoreLights;		// 对模型没影响的灯光
	std::vector<VisibilityData>	m_vecVisibilityData;	// 每个灯光对应光照数据
};

#endif /* STATIC_LIGHTING_CACHE_H */
