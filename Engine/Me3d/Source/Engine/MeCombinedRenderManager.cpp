#include "Me3d/Me3d.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/Renderer.h"
#include "Me3d/Engine/MeCombinedRenderManager.h"
#include "Me3d/Model/Mex2EffectRenderable.h"
#include "Me3d/Engine/MeRenderObject.h"
#include "Me3d/Model/MexGeoChunk.h"
//////////////////////////////////////////////////////////////////////////
bool MeCombinedRenderManager::TryCombinedRender(SortRenderable* pRenderable,bool bPost)
{
	if (NULL == pRenderable)
	{
		return false;
	}
	Initialize();
	MeScopeProfileCombineRenderManagerFun
	for (int i = 0; i < m_AdapterArr.size(); ++i)
	{
		if (m_AdapterArr[i]->IsMyCombinedType(pRenderable))
		{
			m_AdapterArr[i]->CombinedRender(pRenderable,bPost);
			return true;
		}
	}
	return false;
}

// void MeCombinedRenderManager::DoCombinedRender()
// {
// 	for (int i = 0; i < m_AdapterArr.size(); ++i)
// 	{
// 			m_AdapterArr[i]->RenderAndReset(NULL);
// 	}
// 	return true;
// }

MeCombinedRenderManager::MeCombinedRenderManager()
:m_bInitialize(false)
{

}

void MeCombinedRenderManager::Initialize()
{
	if (!m_bInitialize)
	{
		m_AdapterArr.push_back(new MeEffectAdapter);
		m_AdapterArr.push_back(new MeBillboardAdapter);
		m_bInitialize = true;
	}
}

void MeCombinedRenderManager::OnDeviceLost()
{
	for (int i = 0; i < m_AdapterArr.size(); ++i)
	{
		m_AdapterArr[i]->OnDeviceLost();
		delete m_AdapterArr[i];
		m_AdapterArr[i] = NULL;
	}
	m_AdapterArr.clear();
	m_bInitialize = false;
}

MeCombinedRenderManager::~MeCombinedRenderManager()
{
	for (int i = 0; i < m_AdapterArr.size(); ++i)
	{
		delete m_AdapterArr[i];
	}
}
MeEffectAdapter::MeEffectAdapter() 
:m_VertexCount(0)
,m_FaceCount(0)
,m_VertexMem(NULL)
,m_CurrEffectObject(NULL)
,m_bUseVB( false )
,m_aVertexMem(NULL)
{
	HRESULT hr;
	if( m_bUseVB )
	{
		LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
		while(1)
		{
			hr = pDev->CreateVertexBuffer( m_nMaxVertexCount*sizeof(SEmitterVertex), D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_VertexBuffer, NULL );
			if( SUCCEEDED(hr) ) break;
		}
	}
	else
	{
		m_aVertexMem = new SEmitterVertex[m_nMaxVertexCount];
	}
}

MeEffectAdapter::~MeEffectAdapter()
{
	if (m_VertexBuffer && m_bUseVB)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}
	if( m_aVertexMem )
		delete [] m_aVertexMem;
}

void MeEffectAdapter::OnDeviceLost()
{
	if (m_VertexBuffer && m_bUseVB)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}
	if( m_aVertexMem )
		memset( m_aVertexMem, 0, sizeof( SEmitterVertex ) * m_nMaxVertexCount );
}

void MeEffectAdapter::_DoEffectRender()
{
	MeScopeProfileCombineRenderManagerFun
	if (0 >= m_VertexCount)
	{
		return;
	}
	IRenderer* rd = (IRenderer*)GetEngine()->GetRenderer();
	if ( m_bUseVB )
	{
		rd->DirectPushSurface(
			m_CurrEffectObject->GetUseTexId(),
			m_CurrEffectObject->GetAddMapId(),
			m_CurrEffectObject->GetShaderId(),
			m_CurrEffectObject->GetFVF(),
			sizeof( SEmitterVertex ),
			(BYTE*)m_VertexBuffer,
			m_VertexCount,
			(BYTE*)Emitter::GetD9IndexBuffer(),
			m_FaceCount,
			m_CurrEffectObject->GetFlag()|eUseIB|eUseVB,
			D3DPT_TRIANGLELIST,
			0,
			0,
			0,
			m_CurrEffectObject->GetUseLuminanceTexId()
			);
	}
	else
	{
		rd->DirectPushSurface(
			m_CurrEffectObject->GetUseTexId(),
			m_CurrEffectObject->GetAddMapId(),
			m_CurrEffectObject->GetShaderId(),
			m_CurrEffectObject->GetFVF(),
			sizeof( SEmitterVertex ),
			(BYTE*)m_aVertexMem,
			m_VertexCount,
			(BYTE*)Emitter::GetCWIndexBuffer(),
			m_FaceCount,
			m_CurrEffectObject->GetFlag(),
			D3DPT_TRIANGLELIST,
			0,
			0,
			0,
			m_CurrEffectObject->GetUseLuminanceTexId()
			);
	}

}

void MeEffectAdapter::RenderAndReset( MeRenderObjectPtr pRenderObject )
{
	MeScopeProfileCombineRenderManagerFun
	if (m_CurrEffectObject != NULL)
	{
		if( m_bUseVB )
			m_VertexBuffer->Unlock();
		_DoEffectRender();
	}
	//new Effect Render begin
	m_CurrEffectObject = pRenderObject;
	m_VertexCount = 0;
	m_FaceCount = 0;
	m_VertexMem = NULL;
	if ( m_CurrEffectObject != NULL && m_bUseVB )
	{
		HRESULT hr;
		while(1)
		{
			hr = m_VertexBuffer->Lock( 0, 0, (void**)&m_VertexMem, 0 );
			if( SUCCEEDED(hr) ) break;
		}
	}
}

void MeEffectAdapter::CombinedRender( SortRenderable* pRenderable ,bool bPost)
{
	MeScopeProfileCombineRenderManagerFun
	CEffectRenderable* pEffectRenderable = (CEffectRenderable*)pRenderable;
	int nThisVertexCount = pEffectRenderable->GetTotalVerticesCount(bPost);
	if (nThisVertexCount > m_nMaxVertexCount)
	{
		assert(0);
		return;
	}
	if (m_CurrEffectObject && (pEffectRenderable->GetRenderObject()->GetUseTexId() == m_CurrEffectObject->GetUseTexId()))
	{
		if (nThisVertexCount + m_VertexCount > m_nMaxVertexCount)
		{
			RenderAndReset(pEffectRenderable->GetRenderObject());
		}
	}
	else
	{
		RenderAndReset(pEffectRenderable->GetRenderObject());
	}
	if(( m_bUseVB && pEffectRenderable->DoRender(&m_VertexMem[m_VertexCount]) ) ||
		pEffectRenderable->DoRender( &m_aVertexMem[m_VertexCount] ) )
	{
		m_VertexCount += nThisVertexCount;
		m_FaceCount += pEffectRenderable->GetTotalFacesCount(bPost);
	}

}

bool MeEffectAdapter::IsMyCombinedType( SortRenderable* pRenderable )
{
// 	return false;
	return pRenderable && pRenderable->IsEffect();
}

bool MeBillboardAdapter::IsMyCombinedType( SortRenderable* pRenderable )
{
// 	if (pRenderable && pRenderable->IsBillborad())
// 	{
// 		return ((CBillboardGeoChunk*)pRenderable)->CanCombinedRender();
// 	}
	return false;
}

void MeBillboardAdapter::RenderAndReset( MeRenderObjectPtr pRenderObject )
{
	MeScopeProfileCombineRenderManagerFun
	if (m_CurrEffectObject != NULL)
	{
		m_VertexBuffer->Unlock();
		m_NormalsBuffer->Unlock();
		m_DiffusesBuffer->Unlock();
		m_UvsBuffer->Unlock();
// 		m_pIB->Unlock();
		_DoEffectRender();
	}
	//new Effect Render begin
	m_CurrEffectObject = pRenderObject;
	m_VertexCount = 0;
	m_FaceCount = 0;
	m_VertexMem = NULL;
	m_NormalMem = NULL;
	m_UvsMem = NULL;
	m_DiffuseMem = NULL;
// 	m_shIBMem = NULL;
	if (m_CurrEffectObject != NULL)
	{
		HRESULT hr;
		while(1)
		{
			hr = m_VertexBuffer->Lock( 0, 0, (void**)&m_VertexMem, 0 );
			if( SUCCEEDED(hr) ) break;
		}
		while(1)
		{
			hr = m_NormalsBuffer->Lock( 0, 0, (void**)&m_NormalMem, 0 );
			if( SUCCEEDED(hr) ) break;
		}
		while(1)
		{
			hr = m_DiffusesBuffer->Lock( 0, 0, (void**)&m_DiffuseMem, 0 );
			if( SUCCEEDED(hr) ) break;
		}
		while(1)
		{
			hr = m_UvsBuffer->Lock( 0, 0, (void**)&m_UvsMem, 0 );
			if( SUCCEEDED(hr) ) break;
		}
// 		while(1)
// 		{
// 			hr = m_pIB->Lock( 0, 0, (void**)&m_shIBMem, 0 );
// 			if( SUCCEEDED(hr) ) break;
// 		}
	}
}

void MeBillboardAdapter::CombinedRender( SortRenderable* pRenderable ,bool bPost)
{
	MeScopeProfileCombineRenderManagerFun
	MeRenderObjectPtr pRenderObject = pRenderable->GetRenderObject();
	CBillboardGeoChunk*		pBillboard = (CBillboardGeoChunk*)pRenderable;
	int nThisVertexCount = pRenderable->GetTotalVerticesCount(bPost);
	if (nThisVertexCount > m_nMaxVertexCount)
	{
		assert(0);
		return;
	}
	if (m_CurrEffectObject && (pRenderObject->GetUseTexId() == m_CurrEffectObject->GetUseTexId()))
	{
		if (nThisVertexCount + m_VertexCount > m_nMaxVertexCount)
		{
			RenderAndReset(pRenderObject);
		}
	}
	else
	{
		RenderAndReset(pRenderObject);
	}
	pBillboard->CombinedRender(bPost,m_VertexCount,&m_VertexMem[m_VertexCount],&m_NormalMem[m_VertexCount],&m_DiffuseMem[m_VertexCount],&m_UvsMem[m_VertexCount]/*,&m_shIBMem[m_FaceCount*3]*/);
	m_VertexCount += nThisVertexCount;
	m_FaceCount += nThisVertexCount/2;
}

MeBillboardAdapter::MeBillboardAdapter()
{
	HRESULT hr;
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
// 	while(1)
// 	{
// 		hr = pDev->CreateIndexBuffer( m_nMaxFaceCount*sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL );
// 		if( SUCCEEDED(hr) ) break;
// 	}

	while(1)
	{
		hr = pDev->CreateVertexBuffer( m_nMaxVertexCount*sizeof(Vector), D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_VertexBuffer, NULL );
		if( SUCCEEDED(hr) ) break;
	}
	while(1)
	{
		hr = pDev->CreateVertexBuffer( m_nMaxVertexCount*sizeof(Vector), D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_NormalsBuffer, NULL );
		if( SUCCEEDED(hr) ) break;
	}
	while(1)
	{
		hr = pDev->CreateVertexBuffer( m_nMaxVertexCount*sizeof(Vector2), D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_UvsBuffer, NULL );
		if( SUCCEEDED(hr) ) break;
	}
	while(1)
	{
		hr = pDev->CreateVertexBuffer( m_nMaxVertexCount*sizeof(DWORD), D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_DiffusesBuffer, NULL );
		if( SUCCEEDED(hr) ) break;
	}

}

MeBillboardAdapter::~MeBillboardAdapter()
{
// 	if (m_pIB)
// 	{
// 		m_pIB->Release();
// 		m_pIB = NULL;
// 	}
	if (m_VertexBuffer)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}
	if (m_NormalsBuffer)
	{
		m_NormalsBuffer->Release();
		m_NormalsBuffer = NULL;
	}
	if (m_UvsBuffer)
	{
		m_UvsBuffer->Release();
		m_UvsBuffer = NULL;
	}
	if (m_DiffusesBuffer)
	{
		m_DiffusesBuffer->Release();
		m_DiffusesBuffer = NULL;
	}

}

void MeBillboardAdapter::OnDeviceLost()
{
	if (m_VertexBuffer)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}
	if (m_NormalsBuffer)
	{
		m_NormalsBuffer->Release();
		m_NormalsBuffer = NULL;
	}
	if (m_UvsBuffer)
	{
		m_UvsBuffer->Release();
		m_UvsBuffer = NULL;
	}
	if (m_DiffusesBuffer)
	{
		m_DiffusesBuffer->Release();
		m_DiffusesBuffer = NULL;
	}
}

void MeBillboardAdapter::_DoEffectRender()
{
	MeScopeProfileCombineRenderManagerFun
	if (0 >= m_VertexCount)
	{
		return;
	}
	IRenderer* rd = (IRenderer*)GetEngine()->GetRenderer();
	D3DXMATRIXA16 world;
	D3DXMatrixIdentity(&world);
	rd->SetTransform( D3DTS_WORLD, (float*)&world );
	if( !rd->BeginDirectPushSurface(
		m_CurrEffectObject->GetUseTexId(),
		m_CurrEffectObject->GetAddMapId(),
		m_CurrEffectObject->GetShaderId(),
		m_CurrEffectObject->GetFVF(),
		m_VertexBuffer,
		m_NormalsBuffer,
		m_DiffusesBuffer,
		m_UvsBuffer,
		Emitter::GetD9IndexBuffer(),
		m_CurrEffectObject->GetFlag(),
		0, 
		0,
		m_CurrEffectObject->GetUseLuminanceTexId()
		) )
		return;

	rd->DoDirectPushSurface(
		m_VertexCount,
		m_FaceCount,
		D3DPT_TRIANGLELIST, 
		0 
		);
	rd->EndDirectPushSurface();
}
