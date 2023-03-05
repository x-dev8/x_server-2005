//-----------------------------------------------------------------------------
// File:	LightBitmapFilter.cpp
// Desc:	�Թ���ͼ���й���
// Create: 	01/14/2011
// Author:	Qiu Li
//
// Copyright ShenWang 2011 - All Rights Reserved.
//-----------------------------------------------------------------------------
#include "MeTerrain/stdafx.h"
#include "MeTerrain/Lighting/LightBitmapFilter.h"
#include "MeTerrain/Lighting/StaticMeshRayTracer.h"
#include "Me3d/MathEx.h"

class FloatSampler
{
public:
	FloatSampler(std::vector<FLOAT>* InSamples, std::vector<ShadowData>* InMask, INT InStride, INT InMaxX, INT InMaxY, StaticMeshRayTracer* pInTracer, const std::vector<BYTE>* InCoverage)
		:Samples(InSamples)
		,Mask(InMask)
		,Stride(InStride)
		,MaxX(InMaxX)
		,MaxY(InMaxY)
		,pTracer(pInTracer)
		,Coverage(InCoverage)
	{
		assert(InSamples);
		assert(InMask);
		assert(pInTracer);
		assert(InCoverage);
	}

	inline FLOAT GetKernelSample(Mex2GeoChunk* pStaticMesh, INT InX, INT InY, const FLOAT* Kernel, INT KernelWidth)
	{
		if( NULL == pStaticMesh )
			return 0.f;
		assert((KernelWidth % 2) == 1);	// ֻ֧���������

		Vector vCenterNormal;
		UINT uiCenterNormalId = (*Mask)[InX+InY*Stride].uiNormalIndex;
		bool bGetNormal = pTracer->GetNormalById(uiCenterNormalId, vCenterNormal);

		const Mex2Face* pFaces = pStaticMesh->GetFaces();
		const Vector* pVertices = pStaticMesh->GetVertices();

		// ���ĵ����ض�Ӧ��Ķ���
		UINT uiCenterFaceIndex = (*Mask)[InX+InY*Stride].uiFaceIndex;
		const Mex2Face& CFace = pFaces[uiCenterFaceIndex];
		Vector CVertex[3];
		for(UINT VertexIndex = 0;VertexIndex < 3;++VertexIndex)
		{
			CVertex[VertexIndex] = pVertices[CFace.nId[VertexIndex]];
		}

		const INT KernelWidth_d2 = KernelWidth/2;
		const INT StartX = InX - KernelWidth_d2;
		const INT EndX = InX + KernelWidth_d2;
		const INT StartY = InY - KernelWidth_d2;
		const INT EndY = InY + KernelWidth_d2;

		FLOAT TotalWeight = 0.f;
		FLOAT TotalSum = 0.f;

		for (INT Y = StartY, kY = 0; Y <= EndY; ++Y, ++kY)
		{
			if (Y >= 0 && Y < MaxY)
			{
				for (INT X = StartX, kX = 0; X <= EndX; ++X, ++kX)
				{
					if (X >= 0 && X < MaxX)
					{						
						INT Offset = X + Y * Stride;
						if (!Coverage || (*Coverage)[Offset])
						{
							// ���ӷ����ж�
							bool bCanSum = false;
							if( bGetNormal )
							{
								if( uiCenterNormalId == (*Mask)[Offset].uiNormalIndex )
								{
									bCanSum = true;
								}
								else
								{
									Vector vNearNormal;
									bool bNearNormal = pTracer->GetNormalById((*Mask)[Offset].uiNormalIndex, vNearNormal);
									if( bNearNormal )
									{
										float fDot = vCenterNormal.dot(vNearNormal);
										static float fCos = 0.34f;
										if( fDot > fCos )	// ���߼н�70������
										{
											bCanSum = true;
										}
									}
								}
								if( bCanSum )
								{
									bCanSum = false;
									// �Ƿ�����ڽ���
									UINT uiFaceIndex = (*Mask)[Offset].uiFaceIndex;
									if( uiCenterFaceIndex == uiFaceIndex )
										bCanSum = true;
									else
									{
										const Mex2Face& NFace = pFaces[uiFaceIndex];
										int iVertexMatchCount = 0;
										for(UINT VertexIndex = 0;VertexIndex < 3;++VertexIndex)
										{
											Vector Vertex = pVertices[NFace.nId[VertexIndex]];
											for(UINT MatchIndex = 0;MatchIndex < 3;++MatchIndex)
											{
												if( Vertex.positionEquals(CVertex[MatchIndex], 0.001f) )
												{
													++iVertexMatchCount;
													break;
												}
											}
											if( iVertexMatchCount >= 2 )
												break;
										}
										if( iVertexMatchCount >= 2 )
											bCanSum = true;
									}
								}
							}
							// ����Χ���ز���
							if( bCanSum )
							{
								const FLOAT KernelVal = Kernel[kX + kY * KernelWidth];
								TotalSum += KernelVal * (*Samples)[Offset];
								TotalWeight += KernelVal;							
							}
						}
					}
				}
			}
		}

		return TotalWeight > 0 ? TotalSum/TotalWeight : 0.f;
	}

private:
	INT Stride, MaxX, MaxY;
	const std::vector<FLOAT>*		Samples;
	const std::vector<ShadowData>*	Mask;
	const std::vector<BYTE>*		Coverage;	
	StaticMeshRayTracer*			pTracer;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LightBitmapFilter::SmoothVisibilityFloatMask( Mex2GeoChunk* pStaticMesh, std::vector<ShadowData>& Mask, INT SizeX, INT SizeY, StaticMeshRayTracer* pTracer, const std::vector<BYTE>* Coverage /*= 0*/ )
{
	if( NULL == pStaticMesh )
		return;

	// ��ʱ����洢Դ����
	INT TargetSize = SizeX * SizeY;
	std::vector<FLOAT> FloatBuffer;
	FloatBuffer.clear();
	FloatBuffer.resize(TargetSize);
	for( int i=0; i<TargetSize; ++i )
	{
		FloatBuffer[i] = Mask[i].fShadowValue;
	}

	const FLOAT FilterKernel[5][5] =
	{
		{ 29,  42,  52,  42, 29 },
		{ 42,  82, 107,  82, 42 },
		{ 52, 107, 255, 107, 52 },
		{ 42,  82, 107,  82, 42 },
		{ 29,  42,  52,  42, 29 }
	};
	const FLOAT FilterKernel_s3[3][3] =
	{
		{ 29, 42,  29 },
		{ 42, 255, 42 },
		{ 29, 42,  29 },
	};
	const FLOAT FilterKernel_s1[1][1] =
	{
		{ 255 }
	};

	static bool bSample = true;
	if( !bSample )
		return;
	FloatSampler FS(&FloatBuffer, &Mask, SizeX, SizeX, SizeY, pTracer, Coverage);
	for (INT Y=0; Y < SizeY; ++Y)
	{
		for (INT X=0; X < SizeX; ++X)
		{
			INT Offset = Y * SizeX + X;
			//if( SizeX <= 64 )
			//{
			//	// ������Χ����
			//	//Mask[Offset].fShadowValue = FS.GetKernelSample(X, Y, &FilterKernel_s1[0][0], 1);
			//}
			//else if( SizeX <= 128 )
			//	Mask[Offset].fShadowValue = FS.GetKernelSample(pStaticMesh, X, Y, &FilterKernel_s3[0][0], 3);
			//else
				Mask[Offset].fShadowValue = FS.GetKernelSample(pStaticMesh, X, Y, &FilterKernel[0][0], 5);
		}
	}
}

void LightBitmapFilter::CoverageEdgeBleed( NiColorB* Colors, const std::vector<BYTE>* Coverage, INT SizeX, INT SizeY )
{
	assert(Coverage);

	std::vector<BYTE> CoverageBleed1; CoverageBleed1.clear(); CoverageBleed1.resize(SizeX * SizeY);
	std::vector<BYTE> CoverageBleed2; CoverageBleed2.clear(); CoverageBleed2.resize(SizeX * SizeY);
	for( int i=0; i<SizeX * SizeY; ++i )
	{
		CoverageBleed1[i] = (*Coverage)[i];
		CoverageBleed2[i] = (*Coverage)[i];
	}

	std::vector<BYTE>& SrcCoverage = CoverageBleed1;
	std::vector<BYTE>& DestCoverage = CoverageBleed2;

	INT Iterations = 3;
	for (INT i=0; i < Iterations; ++i)
	{
		for(INT Y = 0;Y < SizeY; ++Y)
		{
			for(INT X = 0;X < SizeX; ++X)
			{
				INT Offset = Y * SizeX + X;

				// ֻ��䵽û���ǵĵط�
				if (!SrcCoverage[Offset])
				{
					FLOAT		ColorSum = 0.f;
					FLOAT		fColorA = 0.f, fColorR = 0.f, fColorG = 0.f, fColorB = 0.f;

					for(INT FilterY = -1;FilterY <= 1;FilterY++)
					{
						if(Y + FilterY < 0 || Y + FilterY >= SizeY)
							continue;

						for(INT FilterX = -1;FilterX <= 1;FilterX++)
						{
							if(X + FilterX < 0 || X + FilterX >= SizeX)
								continue;

							INT FilterOffset = (Y + FilterY) * SizeX + X + FilterX;
							if (!SrcCoverage[FilterOffset])
								continue;

							fColorA += Colors[FilterOffset].a;
							fColorR += Colors[FilterOffset].r;
							fColorG += Colors[FilterOffset].g;
							fColorB += Colors[FilterOffset].b;
							ColorSum += 1.f;
						}
					}

					if (ColorSum > 0)
					{
						Colors[Offset].a = Clamp<BYTE>( fColorA/ColorSum, 0, 255 );
						Colors[Offset].r = Clamp<BYTE>( fColorR/ColorSum, 0, 255 );
						Colors[Offset].g = Clamp<BYTE>( fColorG/ColorSum, 0, 255 );
						Colors[Offset].b = Clamp<BYTE>( fColorB/ColorSum, 0, 255 );
						DestCoverage[Offset] = 1;
					}
				}
			}
		}

		// �������
		for( int a = 0; a < SizeX * SizeY; ++a )
		{
			SrcCoverage[a] = DestCoverage[a];
		}
	}
}
