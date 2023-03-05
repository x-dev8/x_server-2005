#include "Me3d/Me3d.h"
#include "Me3d/Engine/EngineInstance.h"
#include "Me3d/Engine/RendererDX.h"
#include "Me3d/Engine/MeRenderObject.h"
#include "Me3d/ShaderManager.h"

//////////////////////////////////////////////////////////////////////////
MeDynamicAllocBuffer< DWORD, 1024 * 20 > MeRenderObject::ms_kDyBuffer;
//////////////////////////////////////////////////////////////////////////
void MeRenderObject::GenerateKey()
{
	unsigned __int64 uiAlpha = ( unsigned __int64 )( m_dwFlag & eAlphaBlend );
	unsigned __int64 n64Flag = m_dwFlag;
	unsigned __int64 n64UseTexId = (unsigned short)m_stUseTexId;
	m_ui64Key = ( n64UseTexId ) | ( n64Flag << 16 ) | ( uiAlpha << 48 );
}




//////////////////////////////////////////////////////////////////////////
bool MeModelRenderObject::BeginRender()
{
	MeScopeProfileRenderObjectFun
	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();

	Vector2* pUVScale = NULL;
	Vector2* pUVOffset = NULL;
	if( GetLightmapTexId() > -1 )
	{
		pUVScale = &(const_cast<Vector2&>(GetLightmapUVScale()));
		pUVOffset = &(const_cast<Vector2&>(GetLightmapUVOffset()));
	}
	return rd->BeginDirectPushSurface(
		GetUseTexId(),
		GetAddMapId(),
		GetShaderId(),
		GetFVF(),
		(LPDIRECT3DVERTEXBUFFER9)GetVB(),
		(LPDIRECT3DVERTEXBUFFER9)GetNB(),
		(LPDIRECT3DVERTEXBUFFER9)GetDB(),
		(LPDIRECT3DVERTEXBUFFER9)GetUVB(),
		(LPDIRECT3DINDEXBUFFER9)GetIB(),
		GetFlag(),
		0, 
		0, 
		GetUseLuminanceTexId(),
		GetLightmapTexId(),
		(LPDIRECT3DVERTEXBUFFER9)GetUVB2(),
		pUVScale,
		pUVOffset
		);
}

//-------------------------------------------------------------------------------
void MeModelRenderObject::StoreAlphaToMemory(float fAlpha)
{
	MeScopeProfileRenderObjectFun
	if (abs(float(fAlpha - 1.0)) < 0.01 || 
		(graphics::ShaderManager::instance()->isUseShader()))
	{
		return;
	}
	if (!(m_dwFvf & D3DFVF_DIFFUSE))
	{
		return;
	}
	void* ptVertex = NULL;
	LPDIRECT3DVERTEXBUFFER9 pBuffTemp = (LPDIRECT3DVERTEXBUFFER9)m_pkDB;
	if (FAILED(pBuffTemp->Lock(0, 0, (void**)&ptVertex, 0)))
	{
		//pBuffTemp->Release();
		pBuffTemp = NULL;
		return;
	}
	//memcpy(m_stBuffer.m_pt, ptVertex, m_nVertexCount * sizeof(DWORD));
	ms_kDyBuffer.MemCpyToBuff( ptVertex, m_nVertexCount * sizeof( DWORD ) );
	pBuffTemp->Unlock();
}

//----------------------------------------------------------------
void MeModelRenderObject::InsertAlphaToVertex(float fAlpha)
{
	MeScopeProfileRenderObjectFun
	if (abs(float(fAlpha - 1.0)) < 0.01 || 
		(graphics::ShaderManager::instance()->isUseShader()))
	{
		return;
	}
	if (!(m_dwFvf & D3DFVF_DIFFUSE))
	{
		return;
	}
	void* ptVertex = NULL;

	LPDIRECT3DVERTEXBUFFER9 pBuffTemp = (LPDIRECT3DVERTEXBUFFER9)m_pkDB;
	if (FAILED(pBuffTemp->Lock(0, 0, (void**)&ptVertex, 0)))
	{
		//pBuffTemp->Release();
		pBuffTemp = NULL;
		return;
	}

	DWORD* ptColor = (DWORD*)ptVertex; 
	DWORD* ptTemp = (DWORD*)ptVertex; 
	for (UINT i = 0; i < m_nVertexCount; ++i)
	{
		DWORD color = 0xffffffff;
		if(ptTemp)
		{
			color = *ptTemp++;
		}

		DWORD a = (color & 0xff000000) >> 24;
		a = (DWORD)(a * fAlpha);
		color = a<<24 | (color & 0x00ffffff);
		*ptColor++ = color;
	}

	pBuffTemp->Unlock();
}

//----------------------------------------------------------------------
void MeModelRenderObject::RestoreAlphaToVertex(float fAlpha)
{
	MeScopeProfileRenderObjectFun
	if (abs(float(fAlpha - 1.0)) < 0.01 || 
		(graphics::ShaderManager::instance()->isUseShader()))
	{
		return;
	}

	if (!(m_dwFvf & D3DFVF_DIFFUSE))
	{
		return;
	}

	void* ptVertex = NULL;
	LPDIRECT3DVERTEXBUFFER9 pBuffTemp = (LPDIRECT3DVERTEXBUFFER9)m_pkDB;
	if (FAILED(pBuffTemp->Lock(0, 0, (void**)&ptVertex, 0)))
	{
		//pBuffTemp->Release();
		pBuffTemp = NULL;
		return;
	}
	//memcpy(ptVertex, m_stBuffer.m_pt, m_nVertexCount * sizeof(DWORD));
	ms_kDyBuffer.MemCpyFromBuff( ptVertex, m_nVertexCount * sizeof( DWORD ), m_nVertexCount * sizeof( DWORD ) );
	pBuffTemp->Unlock();
}

//-----------------------------------------------------------------
void MeModelRenderObject::DoRender()
{
	MeScopeProfileRenderObjectFun
	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();

 	float fAlpha = rd->GetGlobalTransparent();
 	StoreAlphaToMemory( fAlpha );	
 	InsertAlphaToVertex( fAlpha );	//add by yanli  2010-8-20

	rd->DoDirectPushSurface(
		GetVertexCount(),
		GetFaceCount(),
		D3DPT_TRIANGLELIST, 
		0 
		);

	RestoreAlphaToVertex( fAlpha );
}

void MeModelRenderObject::EndRender()
{
	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
	rd->EndDirectPushSurface();
}

//////////////////////////////////////////////////////////////////////////
bool MeParticleRibbonRenderObject::BeginRender()
{
	return true;
}
void MeParticleRibbonRenderObject::DoRender()
{
	MeScopeProfileRenderObjectFun
	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
	rd->DirectPushSurface(
		GetUseTexId(),
		GetAddMapId(),
		GetShaderId(),
		GetFVF(),
		GetStride(),
		(BYTE*)GetVB(),
		GetVertexCount(),
		(BYTE*)GetIB(),
		GetFaceCount(),
		GetFlag(),
		D3DPT_TRIANGLELIST,
		0,
		0,
		0,
		GetUseLuminanceTexId()
		);
}

void MeParticleRibbonRenderObject::EndRender()
{
}

//////////////////////////////////////////////////////////////////////////

bool MeSkeletonRenderObject::BeginRender()
{
	MeScopeProfileRenderObjectFun
	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
	return rd->BeginDirectPushSurfaceSkeleton(
		GetUseTexId(),
		GetAddMapId(),
		(LPDIRECT3DVERTEXBUFFER9)GetVB(),
		(LPDIRECT3DVERTEXBUFFER9)GetNB(),
		(LPDIRECT3DVERTEXBUFFER9)GetDB(),
		(LPDIRECT3DVERTEXBUFFER9)GetUVB(),
		GetBoneWeightIdxBuff(),
		(LPDIRECT3DINDEXBUFFER9)GetIB(),
		GetFlag(),
		GetUseLuminanceTexId(),
		GetChangeColor(),
		GetOldColor()
		);
}

void MeSkeletonRenderObject::DoRender()
{
	MeScopeProfileRenderObjectFun
	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
	rd->DoDirectPushSurfaceSkeleton(
		GetVertexCount(),
		GetFaceCount(),
		GetBoneWorldMatrix(),
		GetBoneMatrixCount()
		);
}

void MeSkeletonRenderObject::EndRender()
{
	RendererDx* rd = (RendererDx*)GetEngine()->GetRenderer();
	rd->EndDirectPushSurfaceSkeleton();

}

void SortRenderable::PushOtherInfo(  RenderParams* cInfo, bool bPost /*= false */ )
{
	MeScopeProfileRenderObjectFun
	if( bPost )
	{
		cInfo->fDistanceToEye = GetDisToCameraEye(cInfo->pMatrices);
		bool bInsert = false;
		for( RenderParams::OtherInfosIter otherit = m_kPostInfos.begin(); 
			otherit != m_kPostInfos.end() ; ++ otherit )
		{
			if (cInfo->fDistanceToEye > (*otherit)->fDistanceToEye)
			{
				m_kPostInfos.insert(otherit,cInfo);
				bInsert = true;
				break;
			}
		}
		if (!bInsert)
		{
			m_kPostInfos.push_back( cInfo );
		}
	}
	else
		m_kOtherInfos.push_back( cInfo );
}