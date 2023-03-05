//-----------------------------------------------------------------------------
// File:	LightMapFunctors.h
// Desc:	处理光照图的算式
// Create: 	01/14/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef LIGHTMAP_FUNCTORS_H
#define LIGHTMAP_FUNCTORS_H
#include "MeTerrain\Lighting\LightAttenuationEvaluator.h"
#include "MeTerrain\NiColor.h"
#include "MeTerrain\MapUtil.h"
#include "MeTerrain\Lighting\LightRes.h"

#define MAX_LIGHT_AFFECT 20

// 标准基类
class LightmapFunctor
{
public:
	void SetLightActor(LightRes* LightActor)
	{
		assert(LightActor);
		Light.SetLightActor(LightActor);
	}

protected:
	LightAttenuationEvaluator	Light;
};

// 处理多个光源亮度叠加
class LuminanceMapFunctor : public LightmapFunctor
{
public:
	LuminanceMapFunctor(NiColorB* ColorData, INT ColorCount, const std::vector<LightRes*>& LightActors, INT LightActorCount, BOOL sRGB = 0)
		:m_pColorData(ColorData)
		,m_nColorCount(ColorCount)
		,m_bRGB(sRGB)
		,m_fLightColorR(0.f)
		,m_fLightColorG(0.f)
		,m_fLightColorB(0.f)
	{
		for (INT i=0; i<MAX_LIGHT_AFFECT; ++i)
			m_LightChannels[i] = i < LightActorCount ? LightActors[i] : NULL;
	}

	void SetupSample(const Vector& Vertex_Pos, INT SampleOffset)
	{
		assert(SampleOffset < m_nColorCount);
		m_pColorData[SampleOffset] = NiColorB(DWORD(0));
	}

	void ProcessSample(const Vector& Vertex_Pos, const Vector& Vertex_Normal, FLOAT Shadow, INT SampleOffset)
	{
		assert(SampleOffset < m_nColorCount);

		// 衰减度只考虑受距离和阴影影响
		FLOAT Attenuation = Shadow * Light.AngleDistance_Attenuation(Vertex_Pos, Vertex_Normal); //Shadow影子 * lyh 光照方向和法线夹角
		NiColorB& Sample = m_pColorData[SampleOffset]; //lyh 最终的颜色数据在这里赋值

		FLOAT R = Sample.r*1.f/255 + Attenuation * m_fLightColorR;
		FLOAT G = Sample.g*1.f/255 + Attenuation * m_fLightColorG;
		FLOAT B = Sample.b*1.f/255 + Attenuation * m_fLightColorB;
		// 防止颜色饱和失真
		FLOAT fMax = max(R,G);
		fMax = max(fMax,B);
		if( fMax > 1.f )
		{
			FLOAT fMaxInv = 1.f/fMax;
			R *= fMaxInv;
			G *= fMaxInv;
			B *= fMaxInv;
		}

		Sample.r =  Clamp<BYTE>(INT(R*255),0,255);
		Sample.g =  Clamp<BYTE>(INT(G*255),0,255);
		Sample.b =  Clamp<BYTE>(INT(B*255),0,255);
	}

	void SampleNotCoverage(INT SampleOffset)
	{
		assert(SampleOffset < m_nColorCount);
		m_pColorData[SampleOffset].r = 0;
		m_pColorData[SampleOffset].g = 0;
		m_pColorData[SampleOffset].b = 0;
	}

	void SetLightActor(LightRes* LightActor)
	{
		assert(LightActor);
		Light.SetLightActor(LightActor);

		NiColorB color = LightActor->GetColor();
		m_fLightColorR = color.r * 1.f/255;
		m_fLightColorG = color.g * 1.f/255;
		m_fLightColorB = color.b * 1.f/255;
	}

private:
	NiColorB*		m_pColorData;
	INT				m_nColorCount;
	BOOL			m_bRGB;

	LightRes*		m_LightChannels[MAX_LIGHT_AFFECT];

	// 临时数据
	FLOAT			m_fLightColorR;
	FLOAT			m_fLightColorG;
	FLOAT			m_fLightColorB;
};

#endif /* LIGHTMAP_FUNCTORS_H */
