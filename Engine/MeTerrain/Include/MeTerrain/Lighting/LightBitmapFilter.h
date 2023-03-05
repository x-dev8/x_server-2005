//-----------------------------------------------------------------------------
// File:	LightBitmapFilter.h
// Desc:	�Թ���ͼ���й���
// Create: 	01/14/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#ifndef LIGHT_BITMAP_FILTER_H
#define LIGHT_BITMAP_FILTER_H
#include "MeRTLibs.h"
#include "Dxsdk/d3dx9math.h"
#include "Me3d/Vector.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/Lighting/StaticMeshRayTracer.h"

class LightBitmapFilter
{
public:
	LightBitmapFilter() {}

	void SmoothVisibilityFloatMask(Mex2GeoChunk* pStaticMesh, std::vector<ShadowData>& Mask, INT SizeX, INT SizeY, StaticMeshRayTracer* pTracer, const std::vector<BYTE>* Coverage = 0);

	// ���ܱ�3*3�������������䵽δ������������ȥ������ͼ��դ�߽�
	void CoverageEdgeBleed(NiColorB* Colors, const std::vector<BYTE>* Coverage, INT SizeX, INT SizeY);


private:
	//std::vector<FLOAT> FloatBuffer;
	//Vector2 LightPos;
};

#endif /* LIGHT_BITMAP_FILTER_H */
