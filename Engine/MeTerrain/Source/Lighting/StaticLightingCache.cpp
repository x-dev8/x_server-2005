//-----------------------------------------------------------------------------
// File:	StaticLightingCache.cpp
// Desc:	存储灯光预生成的阴影数据，仅在编辑器中使用。
// Create: 	01/17/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#include "MeTerrain/stdafx.h"
#include "MeTerrain/Lighting/StaticLightingCache.h"
#include "MeTerrain/NdlRes.h"
#include "Me3d/MathEx.h"

void StaticLightingCache::Clear()
{
	m_vecVisibilityData.clear();
	m_vecIgnoreLights.clear();
}

//void StaticLightingCache::ClearChangedOnly(const std::vector<void*>* vecDeleteLights)
//{
//	// 从后往前删，防止vector下标出错
//	for (INT i = m_vecVisibilityData.size()-1; i >= 0; --i)
//	{
//		VisibilityData& Data = m_vecVisibilityData[i];
//
//		if (!Data.GetLightSource() || Data.GetLightSource()->LightChanged())
//			m_vecVisibilityData.erase(m_vecVisibilityData.begin()+i);
//		else if( vecDeleteLights )
//		{
//			for(INT j=0; j<vecDeleteLights->size(); ++j)
//			{
//				if( (*vecDeleteLights)[j] == Data.GetLightSource() )
//				{
//					m_vecVisibilityData.erase(m_vecVisibilityData.begin()+i);
//					break;
//				}
//			}
//		}
//	}
//
//	for (INT i = m_vecIgnoreLights.size()-1; i >= 0; --i)
//	{
//		if (!m_vecIgnoreLights[i] || m_vecIgnoreLights[i]->LightChanged())
//			m_vecIgnoreLights.erase(m_vecIgnoreLights.begin()+i);
//		else if( vecDeleteLights )
//		{
//			for(INT j=0; j<vecDeleteLights->size(); ++j)
//			{
//				if( (*vecDeleteLights)[j] == m_vecIgnoreLights[i] )
//				{
//					m_vecIgnoreLights.erase(m_vecIgnoreLights.begin()+i);
//					break;
//				}
//			}
//		}
//	}
//}

INT StaticLightingCache::GetLightIndex( LightRes* pLightSource ) const
{
	for( INT i=0; i<m_vecVisibilityData.size(); ++i )
	{
		if( m_vecVisibilityData[i].GetLightSource() == pLightSource )
			return i;
	}

	return INVALID_LIGHT;
}

INT StaticLightingCache::GetIgnoreLightIndex( LightRes* pLightSource ) const
{
	for( INT i=0; i<m_vecIgnoreLights.size(); ++i )
	{
		if( m_vecIgnoreLights[i] == pLightSource )
			return i;
	}

	return INVALID_LIGHT;
}

void StaticLightingCache::AddIgnoreLight( LightRes* pLightSource )
{
	if( GetIgnoreLightIndex(pLightSource) == INVALID_LIGHT )
		m_vecIgnoreLights.push_back(pLightSource);
}

void StaticLightingCache::SaveVisibilityData( LightRes* pLightSource, const std::vector<ShadowData>& Visibility, UINT NumSamples, UINT BorderSize /*= 0*/ )
{
	SaveVisibilityData(pLightSource, Visibility, NumSamples, 0, 0, m_uiWidth-1, m_uiHeight-1, BorderSize);
}

void StaticLightingCache::SaveVisibilityData( LightRes* pLightSource, const std::vector<ShadowData>& Visibility, UINT NumSamples, UINT MinX, UINT MinY,
											 UINT MaxX, UINT MaxY, UINT BorderSize /*= 0*/, const BYTE* Coverage /*= 0*/ )
{
	assert(MaxX <= (m_uiWidth + BorderSize*2));
	assert(MaxY <= (m_uiHeight + BorderSize*2));

	assert(GetLightIndex(pLightSource) == INVALID_LIGHT);
	assert(GetIgnoreLightIndex(pLightSource) == INVALID_LIGHT);

	VisibilityData Data(pLightSource, MinX, MinY, MaxX, MaxY);
	Data.SaveSamples(Visibility, NumSamples);
	Data.SaveCoverage(Coverage, Coverage ? NumSamples : 0);
	m_vecVisibilityData.push_back(Data);
}

const StaticLightingCache::VisibilityData* StaticLightingCache::GetVisiblityData( LightRes* pLightSource )
{
	INT Index = GetLightIndex(pLightSource);
	return (Index != INVALID_LIGHT) ? &m_vecVisibilityData[Index] : NULL;
}

void StaticLightingCache::SetDimensions( UINT Width, UINT Height )
{
	// 如果宽度/高度改变，则清空cache
	if (Width != m_uiWidth || Height != m_uiHeight)
		Clear();

	m_uiWidth = Width;
	m_uiHeight = Height;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticLightingCache::VisibilityData::SaveSamples( const std::vector<ShadowData>& VisibilitySamples, INT NumSamples )
{
	assert(NumSamples == GetWidth() * GetHeight());
	if( NumSamples != GetWidth() * GetHeight() )
		return;

	m_vecVisibility.clear();
	m_vecVisibility.resize(NumSamples);

	m_vecNormalList.clear();
	m_vecNormalList.resize(NumSamples);

	m_vecFaceList.clear();
	m_vecFaceList.resize(NumSamples);

	for (INT i=0; i < NumSamples; ++i)
	{
		FLOAT SampleFloat = sqrtf(VisibilitySamples[i].fShadowValue);	// sqrt linear data to improve precision
		BYTE SampleByte = Clamp(INT(SampleFloat*255),0,255);

		m_vecVisibility[i] = SampleByte;
		m_vecNormalList[i] = VisibilitySamples[i].uiNormalIndex;
		m_vecFaceList[i] = VisibilitySamples[i].uiFaceIndex;
	}
}

void StaticLightingCache::VisibilityData::LoadSamples( std::vector<ShadowData>& VisibilitySamples ) const
{
	assert(m_vecVisibility.size() == GetWidth() * GetHeight());
	assert(m_vecNormalList.size() == GetWidth() * GetHeight());
	assert(m_vecFaceList.size() == GetWidth() * GetHeight());
	if( m_vecVisibility.size() != GetWidth() * GetHeight() ||
		m_vecNormalList.size() != GetWidth() * GetHeight() ||
		m_vecFaceList.size() != GetWidth() * GetHeight() )
		return;

	for( INT i=0; i < m_vecVisibility.size(); ++i )
	{
		FLOAT SampleFloat = (FLOAT)m_vecVisibility[i];
		SampleFloat *= (1.f/255.f);		// convert [0..1] range;
		SampleFloat *= SampleFloat;		// linearize

		VisibilitySamples[i].fShadowValue = SampleFloat;
		VisibilitySamples[i].uiNormalIndex = m_vecNormalList[i];
		VisibilitySamples[i].uiFaceIndex = m_vecFaceList[i];
	}
}

void StaticLightingCache::VisibilityData::SaveCoverage( const BYTE* CoverageSamples, INT NumSamples )
{
	if( !CoverageSamples )
		return;
	m_vecCoverage.clear();
	m_vecCoverage.resize(NumSamples);

	for (INT i=0; i < NumSamples; ++i)
		m_vecCoverage[i] = CoverageSamples[i];
}

void StaticLightingCache::VisibilityData::LoadCoverage( BYTE* CoverageSamples ) const
{
	if( !CoverageSamples )
		return;
	for (INT i=0; i < m_vecCoverage.size(); ++i)
		CoverageSamples[i] = m_vecCoverage[i];
}