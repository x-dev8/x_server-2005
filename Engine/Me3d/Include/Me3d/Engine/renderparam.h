#pragma once
#include "Dxsdk/d3dx9.h"
#include "Me3d/Material.h"
// #include "Me3d/Vector.h"
// #include "MeFoundation/MeAllocatedObject.h"
// #include "Me3d/Engine/MeRenderObject.h"
#include "Singleton.h"
class IMex;
class IReplaceableTextureProj;
class Mex2GeoChunk;
class MexReplaceableTextureProj;

struct RenderParams
{
	IMex* pMex;
	float* pMatrices;
// 	IRenderer* pRenderer;
	IReplaceableTextureProj* pReplaceableTextureProj;
	IReplaceableTextureProj* pShimmerGrayTextureProj;
	float fAlpha;
	bool bMustUseAlphaBlend;
	bool useAnim;	
	INT nSpecularTexID;
// 	std::map<int, std::vector<CombineModelData>>* mapCombineSubmodel;
	graphics::Material* material;
	int nFrameId;
	// added, jiayi, [2010/6/10]
	DWORD dwFlag;
	short stUseTexId;
	short stUseHeatShimmerTexId;
	short stUseShimmerGrayTexId;
	short stUseLuminanceTexId;
	float fGlobalAlpha;
	float fDistanceToEye;
	bool m_bIsRenderModelSelected;//added yd
	bool m_bNoSort;//added yd
	// 颜色 [11/11/2010 zhangjiayi]
	bool m_bDiffAmbChanged;
	D3DXCOLOR m_kDiffuse;
	D3DXCOLOR m_kAmbient;
	// lightmap信息
	int m_nLightmapTexId;
	Vector2 m_vLightmapUVScale;
	Vector2 m_vLightmapUVOffset;
	RenderParams() : pMex(0), pMatrices(0),
		pReplaceableTextureProj(0), fAlpha(1),
		bMustUseAlphaBlend(0),useAnim(0),nSpecularTexID(-1),
		material(0), nFrameId(-1),
		dwFlag(0), stUseTexId(-1), stUseLuminanceTexId(-1), stUseHeatShimmerTexId(-1), stUseShimmerGrayTexId(-1),
	fGlobalAlpha(1),m_bIsRenderModelSelected(false),fDistanceToEye(0.f),m_bNoSort(false)
	,m_bDiffAmbChanged( false ), m_nLightmapTexId(-1)
	{
	}

	// 保存_Render信息
	typedef std::vector<RenderParams*> OtherInfos;
	typedef OtherInfos::iterator OtherInfosIter;
	typedef OtherInfos::const_iterator OtherInfosConstIter;
};


class CRenderParamsMgr : public Singleton<CRenderParamsMgr>
{
public:
	RenderParams*			RetriveRenderParams()
	{
		RenderParams* params = NULL;
		if (m_nCurrUsingIndex < m_nPoolSize)
		{
			params = &pParamPool[m_nCurrUsingIndex++];
		}
		else
		{
			if(!pParamPoolBak)
			{
				pParamPoolBak = new RenderParams[m_nPoolSize*2];
			}
			if (m_nCurrUsingIndexBak < m_nPoolSize*2)
			{
				params = &pParamPoolBak[m_nCurrUsingIndexBak++];
			}
		}
		if (params)
		{
			memset(params,0,sizeof(RenderParams));
			params->nSpecularTexID = -1;
			params->nFrameId = -1;
			params->stUseTexId = -1;
			params->stUseHeatShimmerTexId = -1;
			params->stUseShimmerGrayTexId = -1;
			params->stUseLuminanceTexId = -1;			
			params->m_nLightmapTexId = -1;
		}
		return params;
	}
	void					ResetRenderParamsMgr()
	{
		if (pParamPoolBak)
		{//enlarge
			m_nPoolSize *= 2;
			delete [] pParamPool;
			pParamPool = pParamPoolBak;
			pParamPoolBak = NULL;
		}
		if (m_nCurrUsingIndex + m_nCurrUsingIndexBak > m_nMaxUse)
		{
			m_nMaxUse = m_nCurrUsingIndex + m_nCurrUsingIndexBak;
		}
		m_nCurrUsingIndex = 0;
		m_nCurrUsingIndexBak = 0;
	}
	CRenderParamsMgr():
	pParamPoolBak(NULL)
		,m_nCurrUsingIndex(0)
		,m_nCurrUsingIndexBak(0)
		,m_nPoolSize(1024)
		,m_nMaxUse(0)
	{
		pParamPool = new RenderParams[m_nPoolSize];
	}
	~CRenderParamsMgr()
	{
		if (pParamPool)
		{
			delete [] pParamPool;
			pParamPool = NULL;
		}
		if (pParamPoolBak)
		{
			delete [] pParamPoolBak;
			pParamPoolBak = NULL;
		}
	}
private:
	RenderParams*			pParamPool;
	RenderParams*			pParamPoolBak;
	int						m_nCurrUsingIndex;
	int						m_nCurrUsingIndexBak;
	int						m_nPoolSize;
	int						m_nMaxUse;
};