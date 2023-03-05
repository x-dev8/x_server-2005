#include "Me3d/Me3d.h"
#include "Me3d/Engine/Renderer.h"
#include "Me3d/Engine/TextureManagerInstance.h"
#include "Me3d/Engine/MeShimmerCollector.h"
#include "Me3d/Model/MexGeoChunk.h"

//////////////////////////////////////////////////////////////////////////
ITexture* MeShimmerCollector::ms_pkFrameTexture = 0;
short MeShimmerCollector::ms_sFrameTexId = -1;
LPDIRECT3DSURFACE9 MeShimmerCollector::ms_offScreenSurf = 0;
//////////////////////////////////////////////////////////////////////////
MeShimmerCollector::~MeShimmerCollector()
{
	DeleteFrameTexture();
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
bool MeShimmerCollector::IsCollectible( MeSorter::RenderableBasePtr pkObj )
{
	if( !pkObj )
		return false;

	return pkObj->GetCollectibleType() == SortRenderable::eCT_Shimmer;
}
//////////////////////////////////////////////////////////////////////////
void MeShimmerCollector::CreateFrameTexture( unsigned int uiWidth,
											 unsigned int uiHeight,
											LPDIRECT3DTEXTURE9 pQuadTex )
{
	DeleteFrameTexture();
	ms_pkFrameTexture = GetEngine()->GetTextureManager()->CreateTexture();
// 	ms_pkFrameTexture->Create( "ShimmerTex", uiWidth, uiHeight,
// 		D3DFMT_A8R8G8B8, 0, 0, D3DPOOL_MANAGED );
	ms_pkFrameTexture->SetName( "ShimmerTex" );
	ms_sFrameTexId = GetEngine()->GetTextureManager()->RegisterTexture(
		ms_pkFrameTexture );
	TextureDx8* pkTex = dynamic_cast<TextureDx8*>( ms_pkFrameTexture );
	if( pkTex && pQuadTex )
	{
		pkTex->m_pd3dTexture = pQuadTex;
		pkTex->m_bLoaded = true;
	}

	//´´½¨off-screen surface
// 	LPDIRECT3DDEVICE9 pDevice = 
// 		(LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();
// 
// 	pDevice->CreateOffscreenPlainSurface(
// 		uiWidth,
// 		uiHeight,
// 		D3DFMT_A8R8G8B8,
// 		D3DPOOL_SYSTEMMEM,
// 		&ms_offScreenSurf,
// 		NULL);
	
}
//////////////////////////////////////////////////////////////////////////
void MeShimmerCollector::DeleteFrameTexture()
{
	TextureDx8* pkTex = dynamic_cast<TextureDx8*>( ms_pkFrameTexture );
	if( pkTex )
		pkTex->m_pd3dTexture = 0;

	if( GetFrameTextureId() >= 0 )
	{
		GetEngine()->GetTextureManager()->UnRegisterTexture( 
			GetFrameTextureId() );
	}	
	ms_sFrameTexId = -1;

// 	if( ms_offScreenSurf )
// 		ms_offScreenSurf->Release();
}
//////////////////////////////////////////////////////////////////////////
void MeShimmerCollector::DoRender()
{
	MeScopeProfileShimmerCollectorFun
	if( m_kItems.empty() || !m_bUseCollector )
		return;

	MeSorter::RenderableListIter it = m_kItems.begin();
	for( ; it != m_kItems.end(); ++ it )
	{
		( *it ).m_pRenderable->DoRender( true );
	}
	m_kItems.clear();
}
//////////////////////////////////////////////////////////////////////////