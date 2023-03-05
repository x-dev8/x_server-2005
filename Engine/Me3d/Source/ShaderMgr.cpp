#include "Me3d/Me3d.h"
#include "Me3d/ShaderMgr.h"
#include "Me3d/Engine/EngineInstance.h"
#include "FuncPerformanceLog.h"
#include "Me3d/DXUtil.h"
//#include "Launcher/DataLauncher.h"
//using   namespace   std;   

#define GLOWRES 2
#define SCENE_EFFECT_FILENAME "data\\shader\\scene.fxo"
#define WORLD_EFFECT_FILENAME "data\\shader\\world.fxo"
#define WATER_NORMAL_FILENAME1 "data/texture/liquid/waternormal0.tga"
#define WATER_NORMAL_FILENAME2 "data/texture/liquid/waternormal1.tga"
DWORD QUADVERT::FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;

D3DVERTEXELEMENT9 BLENDVERT::Decl[6] =
{
	{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,		0 },
	{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,		0 },
	{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,		0 },
	{ 0, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT,	0 },
	{ 0, 48, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES,	0 },
	//{ 0, 56, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,			0 },
	D3DDECL_END()
};

static CShaderMgr g_ShaderMgr;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
CShaderMgr* GetShaderMgr()
{
	return &g_ShaderMgr;
};

CShaderMgr::CShaderMgr()
{
	guardfunc;
	m_bShadowMap = false;
	m_bPixWater = false;
	m_bBlur = false;

	m_fBrightVal = 0.0f;
	m_fBlurVal = 0.0f;
	m_vTintColol = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);

	m_nBlurType = 0;
	m_nWaterType = 1;
	m_nShadowType = 0;

	m_pBlendDecl = NULL;
	//g_pQuadVB = NULL;
	m_bCanUseShader = FALSE;
	m_bIsUseingShader = FALSE;

	m_dwSceneEffect = 0;
	// water 
	m_fWaterHeight = 0;
	m_fFresnelPower = 0.5f;
	m_fFresnelScale = 1.3f;
	m_fWaterBlendWeight = 0.7f;
	m_dwWaterColor = D3DCOLOR_ARGB( 0xff, 0, 153, 178 );

    // add [5/30/2008 whu]
    memset( g_pQuadVB, 0, sizeof(g_pQuadVB) );


    m_pBlendDecl = NULL;
    m_pSceneEffect = NULL;	
    m_pWorldEffect = NULL;	

    m_pWaterRefTex = NULL;	
    m_pWaterRefSur = NULL;	

	m_pWaterNormalTex1 = NULL;
	m_pWaterNormalTex2 = NULL;

	// 水面反光暂时不用，先注掉[QL]
	//m_pWaterRefraTex = NULL;
	m_pWaterRefraSur = NULL;

    m_pWaterLightTex = NULL;
    m_pWaterLightSur = NULL;

	// 泛光渲染到贴图功能太老，删除[QL]
    //m_pSceneTexture = NULL;
    //m_pSceneTexture0 = NULL;
    //m_pSceneTexture1 = NULL;
    //m_pSceneSurface = NULL;
    //m_pSceneSurface0 = NULL;
    //m_pSceneSurface1 = NULL;

	unguard;
}
CShaderMgr::~CShaderMgr()
{
    // change [5/30/2008 whu]
    guardfunc;
    DestroyDeviceOjbects();
    unguard;
}

// add [5/30/2008 whu]
void CShaderMgr::DestroyDeviceOjbects()
{
    guardfunc;

    // add [5/30/2008 whu]
    SAFE_RELEASE( g_pQuadVB[0] );
    SAFE_RELEASE( g_pQuadVB[1] );
    SAFE_RELEASE( g_pQuadVB[2] );

    SAFE_RELEASE( m_pBlendDecl );
    SAFE_RELEASE( m_pSceneEffect );
    SAFE_RELEASE( m_pWorldEffect );

    //释放纹理
    SAFE_RELEASE( m_pWaterRefTex );
    SAFE_RELEASE( m_pWaterRefSur );
	SAFE_RELEASE( m_pWaterNormalTex1 );
	SAFE_RELEASE( m_pWaterNormalTex2 );
	// 水面反光暂时不用，先注掉[QL]
	//SAFE_RELEASE( m_pWaterRefraTex );
	SAFE_RELEASE( m_pWaterRefraSur );

    SAFE_RELEASE( m_pWaterLightTex );
    SAFE_RELEASE( m_pWaterLightSur );


	// 泛光渲染到贴图功能太老，删除[QL]
    //SAFE_RELEASE( m_pSceneTexture );
    //SAFE_RELEASE( m_pSceneTexture0 );
    //SAFE_RELEASE( m_pSceneTexture1 );
    //SAFE_RELEASE( m_pSceneSurface );
    //SAFE_RELEASE( m_pSceneSurface0 );
    //SAFE_RELEASE( m_pSceneSurface1 );

    unguard;
}

bool CShaderMgr::CheckShaderVersion()
{
	guardfunc;
	D3DCAPS9 d3dCaps;
	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
	if( FAILED( pDev->GetDeviceCaps( &d3dCaps ) ) )
	{
		return false;
	}

	// Check for vertex/pixel shaders 2.0 support
	if( d3dCaps.VertexShaderVersion < D3DVS_VERSION( 2, 0 ) || d3dCaps.PixelShaderVersion < D3DPS_VERSION( 2, 0 ) )
	{
		return false;
	}

	//// Check for R32F surface format support
	//if( FAILED( pDev->CheckDepthStencilMatch( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3ddm.Format,
	//	D3DFMT_R32F, D3DFMT_D16 ) ) )
	//{
	//	GetErrorLog()->logString( "R32F format not supported!" );
	//	return false;
	//}
	return true;
	unguard;
}

void CShaderMgr::InitShader()
{
	guardfunc;

    DestroyDeviceOjbects();

	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();

// 	pDev->CreateTexture( 
// 		SCREEN_WIDTH,
// 		SCREEN_HEIGHT,
// 		1,
// 		D3DUSAGE_RENDERTARGET,
// 		D3DFMT_A8R8G8B8,
// 		D3DPOOL_DEFAULT,
// 		&m_pSceneTexture,
// 		NULL );
// 
// 	pDev->CreateTexture( 
// 		SCREEN_WIDTH/2,
// 		SCREEN_HEIGHT/2,
// 		1,
// 		D3DUSAGE_RENDERTARGET,
// 		D3DFMT_A8R8G8B8,
// 		D3DPOOL_DEFAULT,
// 		&m_pSceneTexture0,
// 		NULL );
// 	pDev->CreateTexture( 
// 		SCREEN_WIDTH/4,
// 		SCREEN_HEIGHT/4,
// 		1,
// 		D3DUSAGE_RENDERTARGET,
// 		D3DFMT_A8R8G8B8,
// 		D3DPOOL_DEFAULT,
// 		&m_pSceneTexture1,
// 		NULL );

	if( FAILED( pDev->CreateTexture( 
		WATER_REFLECT_SIZE,
		WATER_REFLECT_SIZE,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pWaterRefTex,
		NULL )))
	{
		return;
	}

	char filename[MAX_PATH] = {0};
	sprintf(filename, "%s\\%s", GetRootPath(), WATER_NORMAL_FILENAME1 );
	if( FAILED( D3DXCreateTextureFromFile( pDev, filename, &m_pWaterNormalTex1 ) ) )
	{
		m_pWaterNormalTex1 = 0;
		//return;
	}
	sprintf(filename, "%s\\%s", GetRootPath(), WATER_NORMAL_FILENAME2 );

	if( FAILED( D3DXCreateTextureFromFile( pDev, filename, &m_pWaterNormalTex2 ) ) )
	{
		m_pWaterNormalTex2 = 0;
		//return;
	}

	//if( FAILED( pDev->CreateTexture( 
	//	WATER_REFRACT_SIZE,
	//	WATER_REFRACT_SIZE,
	//	1,
	//	D3DUSAGE_RENDERTARGET,
	//	D3DFMT_A8R8G8B8,
	//	D3DPOOL_DEFAULT,
	//	&m_pWaterRefraTex,
	//	NULL )))
	//{
	//	GetErrorLog()->logString( "Unable to create refract WaterTexture!" );
	//	return;
	//}

// 	if( FAILED( pDev->CreateTexture( 
// 		WATER_REFLECT_SIZE,
// 		WATER_REFLECT_SIZE,
// 		1,
// 		D3DUSAGE_RENDERTARGET,
// 		D3DFMT_A8R8G8B8,
// 		D3DPOOL_DEFAULT,
// 		&m_pWaterLightTex,
// 		NULL )))
// 	{
// 		GetErrorLog()->logString( "Unable to create WaterLightTexture!" );
// 		return;
// 	}


	// 获取贴图的渲染表面
	m_pWaterRefTex->GetSurfaceLevel(0 , &m_pWaterRefSur);
	// 水面反光暂时不用，先注掉[QL]
//	m_pWaterRefraTex->GetSurfaceLevel(0, &m_pWaterRefraSur);
// 	m_pWaterLightTex->GetSurfaceLevel(0 , &m_pWaterLightSur);
// 	m_pSceneTexture->GetSurfaceLevel(0 , &m_pSceneSurface);
// 	m_pSceneTexture0->GetSurfaceLevel(0 , &m_pSceneSurface0);
// 	m_pSceneTexture1->GetSurfaceLevel(0 , &m_pSceneSurface1);
	// Grab the texture's surface

	pDev->CreateVertexDeclaration( BLENDVERT::Decl, &m_pBlendDecl );
	/*
	if( FAILED( pDev->CreateVertexBuffer( 4 * sizeof(QUADVERT), D3DUSAGE_WRITEONLY, QUADVERT::FVF,
			D3DPOOL_DEFAULT, &g_pQuadVB[0], NULL ) ) )
		{
			GetErrorLog()->logString( "Unable to create vertex buffer!" );
			return;
		}
		if( FAILED( pDev->CreateVertexBuffer( 4 * sizeof(QUADVERT), D3DUSAGE_WRITEONLY, QUADVERT::FVF,
			D3DPOOL_DEFAULT, &g_pQuadVB[1], NULL ) ) )
		{
			GetErrorLog()->logString( "Unable to create vertex buffer!" );
			return;
		}
		if( FAILED( pDev->CreateVertexBuffer( 4 * sizeof(QUADVERT), D3DUSAGE_WRITEONLY, QUADVERT::FVF,
			D3DPOOL_DEFAULT, &g_pQuadVB[2], NULL ) ) )
		{
			GetErrorLog()->logString( "Unable to create vertex buffer!" );
			return;
		}
		// Copy the vertices
		QUADVERT* pVertices;
		g_pQuadVB[0]->Lock( 0, 0, (void**)&pVertices, 0 );
		pVertices[0].p = D3DXVECTOR4( 0.0f, SCREEN_HEIGHT-0.5, 0.0f, 1.0f );
		pVertices[1].p = D3DXVECTOR4( 0.0f, 0.0f, 0.0f, 1.0f );
		pVertices[2].p = D3DXVECTOR4( SCREEN_WIDTH-0.5, SCREEN_HEIGHT-0.5, 0.0f, 1.0f );
		pVertices[3].p = D3DXVECTOR4( SCREEN_WIDTH-0.5, 0.0f, 0.0f, 1.0f );
		pVertices[0].t = D3DXVECTOR2( 0.0f, 1.0f );
		pVertices[1].t = D3DXVECTOR2( 0.0f, 0.0f );
		pVertices[2].t = D3DXVECTOR2( 1.0f, 1.0f );
		pVertices[3].t = D3DXVECTOR2( 1.0f, 0.0f );
		g_pQuadVB[0]->Unlock();
	
		g_pQuadVB[1]->Lock( 0, 0, (void**)&pVertices, 0 );
		pVertices[0].p = D3DXVECTOR4( 0.0f, SCREEN_HEIGHT / 2 - 0.5, 0.0f, 1.0f );
		pVertices[1].p = D3DXVECTOR4( 0.0f, 0.0f, 0.0f, 1.0f );
		pVertices[2].p = D3DXVECTOR4( SCREEN_WIDTH / 2 - 0.5, SCREEN_HEIGHT / 2 - 0.5, 0.0f, 1.0f );
		pVertices[3].p = D3DXVECTOR4( SCREEN_WIDTH / 2 - 0.5, 0.0f, 0.0f, 1.0f );
		pVertices[0].t = D3DXVECTOR2( 0.0f, 1.0f );
		pVertices[1].t = D3DXVECTOR2( 0.0f, 0.0f );
		pVertices[2].t = D3DXVECTOR2( 1.0f, 1.0f );
		pVertices[3].t = D3DXVECTOR2( 1.0f, 0.0f );
		g_pQuadVB[1]->Unlock();
	
		g_pQuadVB[2]->Lock( 0, 0, (void**)&pVertices, 0 );
		pVertices[0].p = D3DXVECTOR4( 0.0f, SCREEN_HEIGHT / 4 - 0.5, 0.0f, 1.0f );
		pVertices[1].p = D3DXVECTOR4( 0.0f, 0.0f, 0.0f, 1.0f );
		pVertices[2].p = D3DXVECTOR4( SCREEN_WIDTH / 4 - 0.5, SCREEN_HEIGHT / 4 - 0.5, 0.0f, 1.0f );
		pVertices[3].p = D3DXVECTOR4( SCREEN_WIDTH / 4 - 0.5, 0.0f, 0.0f, 1.0f );
		pVertices[0].t = D3DXVECTOR2( 0.0f, 1.0f );
		pVertices[1].t = D3DXVECTOR2( 0.0f, 0.0f );
		pVertices[2].t = D3DXVECTOR2( 1.0f, 1.0f );
		pVertices[3].t = D3DXVECTOR2( 1.0f, 0.0f );
		g_pQuadVB[2]->Unlock();*/
	

	ResetEffect();
	unguard;
}

void CShaderMgr::ResetEffect()
{
	guardfunc;
	if (!m_bCanUseShader) return;
	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
	//effect
	DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;
#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif
	char filename[MAX_PATH];
	sprintf(filename, "%s\\%s", GetRootPath(), SCENE_EFFECT_FILENAME );
	if(FAILED(D3DXCreateEffectFromFile( pDev, filename, NULL, NULL, dwShaderFlags, 
								NULL, &m_pSceneEffect, NULL )))
	{
		FILE	* fp = fopen(filename,"rb");
		if (!fp)
		{
			return ;
		}
		D3DXCreateEffect( pDev, fp->_ptr,
			fp->_cnt, NULL, NULL, dwShaderFlags, 
			NULL, &m_pSceneEffect, NULL );
		fclose(fp);
	}
 	sprintf(filename, "%s\\%s", GetRootPath(), WORLD_EFFECT_FILENAME );
	if(FAILED(D3DXCreateEffectFromFile( pDev, filename, NULL, NULL, dwShaderFlags, 
		NULL, &m_pWorldEffect, NULL )))
	{
		FILE	*fp = fopen(filename,"rb");
		if (!fp)
		{
			return ;
		}
		D3DXCreateEffect( pDev, fp->_ptr,
			fp->_cnt, NULL, NULL, dwShaderFlags, 
			NULL, &m_pWorldEffect, NULL );
		fclose(fp);
	}

	m_pWorldEffect->SetTexture( "g_txReflect", m_pWaterRefTex) ;

	// 水面反光暂时不用，先注掉[QL]
	//m_pWorldEffect->SetTexture( "g_txRefract", m_pWaterRefraTex);

	// 泛光渲染到贴图功能太老，删除[QL]
	//m_pSceneEffect->SetTexture( "g_txScene", m_pSceneTexture) ;
	//m_pSceneEffect->SetTexture( "g_txScene0", m_pSceneTexture0);
	//m_pSceneEffect->SetTexture( "g_txScene1", m_pSceneTexture1);


	m_bShadowMap	 = true;
	// scene
	m_hRenderSToD	 = m_pSceneEffect->GetTechniqueByName( "RenderSToD" );
	m_hRenderDToS	 = m_pSceneEffect->GetTechniqueByName( "RenderDToS" );
	m_hRenderFinalScene = m_pSceneEffect->GetTechniqueByName( "RenderBlendScene" );
	m_hBlend		 = m_pSceneEffect->GetParameterByName(NULL, "g_fBlend" );
	m_hBright		 = m_pSceneEffect->GetParameterByName(NULL, "g_fBright" );
	m_hTintColol	 = m_pSceneEffect->GetParameterByName(NULL, "g_vTintColol" );


	// world
	m_hRenderWater = m_pWorldEffect->GetTechniqueByName( "RenderWater" );		// 句柄

	m_hTime = m_pWorldEffect->GetParameterByName(NULL, "g_fTime" );
	m_hWaterHeight = m_pWorldEffect->GetParameterByName(NULL, "g_fWaterHeight" );
	m_hWaterColor = m_pWorldEffect->GetParameterByName(NULL, "g_vWaterColor" );
	m_hFresnelPower = m_pWorldEffect->GetParameterByName(NULL, "g_fFresnelPower" );
	m_hFresnelScale = m_pWorldEffect->GetParameterByName(NULL, "g_fFresnelScale" );
	m_hWaterBlendWeight = m_pWorldEffect->GetParameterByName(NULL, "g_fWaterBlendWeight" );
	m_hTxReflect = m_pWorldEffect->GetParameterByName(NULL, "g_txReflect" );
	m_hTxRefract = m_pWorldEffect->GetParameterByName(NULL, "g_txRefract");
	m_hTxWaterLight = m_pWorldEffect->GetParameterByName(NULL, "g_txWaterLight" );


	m_hWorldViewPro = m_pWorldEffect->GetParameterByName(NULL, "g_mWorldViewProjection" );
	m_hMaterialDiffuse = m_pWorldEffect->GetParameterByName(NULL, "MaterialDiffuse" );
	m_hMaterialAmbient = m_pWorldEffect->GetParameterByName(NULL, "MaterialAmbient" );
	m_hLightDir = m_pWorldEffect->GetParameterByName(NULL, "lightDir" );	
	m_hMatBlendArray = m_pWorldEffect->GetParameterByName(NULL, "g_matBlendArray" );



	m_hRenderBlend = m_pWorldEffect->GetTechniqueByName( "RenderBlend" );		// 句柄
	m_hMaterialAlpha = m_pWorldEffect->GetParameterByName(NULL, "MaterialAlpha" );

	// 初始化参数
	m_pSceneEffect->SetFloat( m_hBlend, m_fBlurVal );
	m_pSceneEffect->SetFloat( m_hBright, m_fBrightVal );
	m_pSceneEffect->SetVector( m_hTintColol, &m_vTintColol );

	m_pWorldEffect->SetTexture( m_hTxReflect, m_pWaterRefTex);
	// 水面反光暂时不用，先注掉[QL]
	//m_pWorldEffect->SetTexture( m_hTxRefract, m_pWaterRefraTex);
	m_pWorldEffect->SetTexture( m_hTxWaterLight, m_pWaterLightTex);

	m_pWorldEffect->SetVector( m_hWaterColor, &D3DXVECTOR4((float)((m_dwWaterColor>>16)&0xFF)/255.0f,(float)((m_dwWaterColor>>8)&0xFF)/255.0f,(float)(m_dwWaterColor&0xFF)/255.0f,1));
	m_pWorldEffect->SetFloat( m_hWaterHeight, m_fWaterHeight);

	UpdataSceneEffect();

	m_bIsUseingShader = TRUE;
	unguard;
}

void CShaderMgr::RenderScene()
{
	guardfunc;
	RenderScene(m_dwSceneEffect);
	unguard;
}
void CShaderMgr::RenderScene(DWORD dwEffect)
{
	guardfunc;
	if (!dwEffect) return;
	if (dwEffect&eNone) return;

	if (m_bCanUseShader)
	{
		if (dwEffect&eTemporalBlur)
		{	
			RenderTemporalBlurScene();
		}
		else if (dwEffect&eBlur)
		{
			RenderBlurScene();
		}
		else
		{
			RenderFinalScene();
		}
	}
	else
	{
		if (dwEffect&eTemporalBlur)
		{	
			RenderTemporalBlurSceneNoShader();
		}
		else if (dwEffect&eBlur)
		{
			RenderBlurSceneNoShader();
		}
		else
		{
			RenderFinalSceneNoShader();
		}
	}
	unguard;
}
void CShaderMgr::RenderBlurScene()
{
	guardfunc;
	if( m_fBlurVal != 0 )
	{
		IRenderer* RI = GetEngine()->GetRenderer();
		LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
		// 保存渲染表面
		LPDIRECT3DSURFACE9	pRenderTarget;
		pDev->GetRenderTarget(0 , &pRenderTarget);
		// copy 到贴图
		// 泛光渲染到贴图功能太老，删除[QL]
		//pDev->StretchRect(pRenderTarget,NULL,m_pSceneSurface,NULL, D3DTEXF_LINEAR);
		//pDev->StretchRect(pRenderTarget,NULL,m_pSceneSurface0,NULL, D3DTEXF_LINEAR);
		RI->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		RI->SetRenderState(D3DRS_LIGHTING,  FALSE);
		RI->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		RI->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);


		//RI->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		//RI->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		//RI->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
		RI->SetRenderState(D3DRS_ZENABLE, FALSE);
		RI->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);


		//    _pd3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
		//    _pd3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
		RI->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
		RI->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		RI->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
		RI->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE);
		RI->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);

		//RI->SetTextureStageState(1, D3DTSS_COLOROP,   D3DTOP_DISABLE);
		//RI->SetTextureStageState(1, D3DTSS_ALPHAOP,   D3DTOP_DISABLE);
		//RI->SetTextureStageState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		//RI->SetTextureStageState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		//RI->SetTextureStageState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		RI->Commit();

		for (int i=0;i<3;i++)
		{
			switch(i) 
			{
				case 0:
					m_hRenderScene=m_hRenderSToD;
					// 泛光渲染到贴图功能太老，删除[QL]
					//pDev->SetRenderTarget(0 , m_pSceneSurface1);
					pDev->Clear(0 , 0 , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_ARGB(0 , 0 , 0, 0) , 1 , 0);
					break;
				case 1:
					m_hRenderScene=m_hRenderDToS;
					// 泛光渲染到贴图功能太老，删除[QL]
					//pDev->SetRenderTarget(0 , m_pSceneSurface0);
					pDev->Clear(0 , 0 , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_ARGB(0 , 0 , 0, 0) , 1 , 0);
					break;
				case 2:
					m_hRenderScene=m_hRenderFinalScene;
					// 恢复渲染表面为显示器
					pDev->SetRenderTarget(0 , pRenderTarget);
					pDev->Clear(0 , 0 , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_ARGB(0 , 0 , 0, 0) , 1 , 0);
					break;
				//default:
			}
			if( SUCCEEDED( pDev->BeginScene() ) )
			{
				pDev->SetStreamSource( 0, g_pQuadVB[i], 0, sizeof(QUADVERT) );
				pDev->SetFVF(QUADVERT::FVF);
				m_pSceneEffect->SetTechnique( m_hRenderScene );
				UINT cPasses;
				m_pSceneEffect->Begin( &cPasses, 0 );
				for( UINT p = 0; p < cPasses; ++p )
				{
					m_pSceneEffect->BeginPass( p );
					pDev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
					m_pSceneEffect->EndPass();
				}
				m_pSceneEffect->End();

				pDev->EndScene();
			}

		}
	}
	unguard;
}

void CShaderMgr::RenderBlurSceneNoShader()
{
	guardfunc;
	if( m_fBlurVal != 0 )
	{
		IRenderer* RI = GetEngine()->GetRenderer();
		LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
		// 保存渲染表面
		LPDIRECT3DSURFACE9	pRenderTarget;
		pDev->GetRenderTarget(0 , &pRenderTarget);
		// copy 到贴图
		// 泛光渲染到贴图功能太老，删除[QL]
		//pDev->StretchRect(pRenderTarget,NULL,m_pSceneSurface0,NULL, D3DTEXF_LINEAR);
		//pDev->StretchRect(pRenderTarget,NULL,m_pSceneSurface1,NULL, D3DTEXF_LINEAR);
		RI->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		RI->SetRenderState(D3DRS_LIGHTING,  FALSE);
		RI->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

		RI->SetRenderState(D3DRS_ZENABLE, FALSE);
		RI->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

		int nAlpha;
		int nVBId;
		for (int i=0;i<3;i++)
		{
			switch(i) 
			{
			case 0:
				nVBId = 1;
				nAlpha = min(m_fBlurVal*255,255);
				RI->SetRenderState( D3DRS_TEXTUREFACTOR, nAlpha<<24 );

				RI->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
				RI->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
				RI->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

				RI->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
				RI->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
				RI->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
				RI->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR );

				// 泛光渲染到贴图功能太老，删除[QL]
				//pDev->SetRenderTarget(0 , m_pSceneSurface0);
				//pDev->SetTexture(0,m_pSceneTexture1);
				break;
			case 1:
				nVBId = 0;
				nAlpha = min(m_fBlurVal*255,255);
				RI->SetRenderState( D3DRS_TEXTUREFACTOR, nAlpha<<24 );

				RI->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
				RI->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
				RI->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

				RI->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
				RI->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
				RI->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
				RI->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR );
				// 恢复渲染表面为显示器
				pDev->SetRenderTarget(0 , pRenderTarget);
				// 泛光渲染到贴图功能太老，删除[QL]
				//pDev->SetTexture(0,m_pSceneTexture0);
				break;
			case 2:
				nVBId = 0;
				nAlpha = min(m_fBrightVal*255,255);
				RI->SetRenderState( D3DRS_TEXTUREFACTOR, nAlpha<<24 );

				RI->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
				RI->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
				RI->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

				RI->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
				RI->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
				RI->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
				RI->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR );
				// 恢复渲染表面为显示器
				// 泛光渲染到贴图功能太老，删除[QL]
				//pDev->SetTexture(0,m_pSceneTexture0);
				break;
			}
			RI->Commit();

			if( SUCCEEDED( pDev->BeginScene() ) )
			{
				pDev->SetStreamSource( 0, g_pQuadVB[nVBId], 0, sizeof(QUADVERT) );
				pDev->SetFVF(QUADVERT::FVF);
				pDev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
				pDev->EndScene();
			}
		}
	}
	unguard;
}

void CShaderMgr::RenderFinalScene()// 加亮 黑白 反色 偏色 噪点 dengdengdengdeng
{
	guardfunc;

	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
	// copy 到贴图
	LPDIRECT3DSURFACE9	pRenderTarget;
	pDev->GetRenderTarget(0 , &pRenderTarget);
	// 泛光渲染到贴图功能太老，删除[QL]
	//pDev->StretchRect(pRenderTarget,NULL,m_pSceneSurface,NULL, D3DTEXF_LINEAR);

	RI->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	RI->SetRenderState(D3DRS_LIGHTING,  FALSE);
	RI->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	RI->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	RI->SetRenderState(D3DRS_ZENABLE, FALSE);
	RI->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	RI->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	RI->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	RI->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	RI->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE);
	RI->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	RI->Commit();

	pDev->Clear(0 , 0 , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_ARGB(0 , 0 , 0, 0) , 1 , 0);

	if( SUCCEEDED( pDev->BeginScene() ) )
	{
		pDev->SetStreamSource( 0, g_pQuadVB[2], 0, sizeof(QUADVERT) );
		pDev->SetFVF(QUADVERT::FVF);
		m_pSceneEffect->SetTechnique( m_hRenderFinalScene );
		UINT cPasses;
		m_pSceneEffect->Begin( &cPasses, 0 );
		for( UINT p = 0; p < cPasses; ++p )
		{
			m_pSceneEffect->BeginPass( p );
			pDev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
			m_pSceneEffect->EndPass();
		}
		m_pSceneEffect->End();

		pDev->EndScene();
	}

	unguard;
}

void CShaderMgr::RenderFinalSceneNoShader()// 加亮 黑白 反色 偏色 噪点 dengdengdengdeng
{
	guardfunc;

	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
	// copy 到贴图
	LPDIRECT3DSURFACE9	pRenderTarget;
	pDev->GetRenderTarget(0 , &pRenderTarget);
	// 泛光渲染到贴图功能太老，删除[QL]
	//pDev->StretchRect(pRenderTarget,NULL,m_pSceneSurface,NULL, D3DTEXF_LINEAR);

	RI->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	RI->SetRenderState(D3DRS_LIGHTING,  FALSE);
	RI->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	RI->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	RI->SetRenderState(D3DRS_ZENABLE, FALSE);
	RI->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	RI->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	RI->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	RI->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	RI->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE);
	RI->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	RI->Commit();

	pDev->Clear(0 , 0 , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_ARGB(0 , 0 , 0, 0) , 1 , 0);

	if( SUCCEEDED( pDev->BeginScene() ) )
	{
		pDev->SetStreamSource( 0, g_pQuadVB[2], 0, sizeof(QUADVERT) );
		pDev->SetFVF(QUADVERT::FVF);
		m_pSceneEffect->SetTechnique( m_hRenderFinalScene );
		UINT cPasses;
		m_pSceneEffect->Begin( &cPasses, 0 );
		for( UINT p = 0; p < cPasses; ++p )
		{
			m_pSceneEffect->BeginPass( p );
			pDev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
			m_pSceneEffect->EndPass();
		}
		m_pSceneEffect->End();

		pDev->EndScene();
	}

	unguard;
}

void CShaderMgr::RenderTemporalBlurScene()// 1:copy正常画面 2:与上一帧按混合比混合并输出 3:保存此帧用于下次混合
{
	guardfunc;
	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
	LPDIRECT3DSURFACE9	pRenderTarget;
	pDev->GetRenderTarget(0 , &pRenderTarget);
	//使用shader渲染
	RenderFinalScene();

	//保存当前的画面 以备下一帧调用
	// 泛光渲染到贴图功能太老，删除[QL]
	//pDev->StretchRect(pRenderTarget,NULL,m_pSceneSurface0,NULL, D3DTEXF_LINEAR);
	unguard;
}

void CShaderMgr::RenderTemporalBlurSceneNoShader()// 1:copy正常画面 2:与上一帧按混合比混合并输出 3:保存此帧用于下次混合
{
	guardfunc;
	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
	LPDIRECT3DSURFACE9	pRenderTarget;
	pDev->GetRenderTarget(0 , &pRenderTarget);
	//使用普通渲染
	int nAlpha = min(m_fBlurVal*255,255);
	DWORD dwFactor = nAlpha<<24;
	RI->SetRenderState( D3DRS_TEXTUREFACTOR, dwFactor );

	RI->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	RI->SetRenderState( D3DRS_LIGHTING,  FALSE );
	RI->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	RI->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	RI->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	RI->SetRenderState( D3DRS_ZENABLE, FALSE );
	RI->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	RI->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1 );
	RI->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	RI->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
	RI->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR );
	RI->Commit();

	if( SUCCEEDED( pDev->BeginScene() ) )
	{
		// 泛光渲染到贴图功能太老，删除[QL]
		//pDev->SetTexture(0,m_pSceneTexture0);
		pDev->SetStreamSource( 0, g_pQuadVB[0], 0, sizeof(QUADVERT) );
		pDev->SetFVF(QUADVERT::FVF);
		pDev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
		pDev->EndScene();
	}

	//保存当前的画面 以备下一帧调用
	// 泛光渲染到贴图功能太老，删除[QL]
	//pDev->StretchRect(pRenderTarget,NULL,m_pSceneSurface0,NULL, D3DTEXF_LINEAR);

	RI->SetRenderState(D3DRS_LIGHTING,  TRUE);
	unguard;
}

void CShaderMgr::SetBlurVal(float fVal)
{
	guardfunc;
	m_fBlurVal = fVal;
	if ( m_bIsUseingShader ){
		m_pSceneEffect->SetFloat( m_hBlend, m_fBlurVal );
		m_pSceneEffect->CommitChanges();
	}
	unguard;
}
void CShaderMgr::SetBrightVal(float fVal)
{
	guardfunc;
	m_fBrightVal = fVal;
	if ( m_bIsUseingShader ){
		m_pSceneEffect->SetFloat( m_hBright,  m_fBrightVal );
		//m_pSceneEffect->SetFloat( m_hBlend0, ( 1-m_fBlurVal ) * m_fBrightVal );
		//m_pSceneEffect->SetFloat( m_hBlend1, m_fBlurVal * m_fBrightVal );
		m_pSceneEffect->CommitChanges();
	}
	unguard;
}

void CShaderMgr::SetTintColol(float fR,float fG,float fB)
{
	guardfunc;
	m_vTintColol = D3DXVECTOR4(fR,fG,fB,1.0f);
	if ( m_bIsUseingShader ){
		m_pSceneEffect->SetVector(m_hTintColol, &m_vTintColol);
		m_pSceneEffect->CommitChanges();
	}
	unguard;
}

void CShaderMgr::SetWaterColor(DWORD dwColor)
{
	guardfunc;
	if ( m_dwWaterColor !=  dwColor )
	{
		m_dwWaterColor = dwColor;
		m_pWorldEffect->SetVector(m_hWaterColor, &D3DXVECTOR4((float)((dwColor>>16)&0xFF)/255.0f,(float)((dwColor>>8)&0xFF)/255.0f,(float)(dwColor&0xFF)/255.0f,1));
		m_pWorldEffect->CommitChanges();
	}
	unguard;
}
void CShaderMgr::SetWaterHeight(float fHeight)
{
	guardfunc;
	if ( m_fWaterHeight != fHeight )
	{
		m_fWaterHeight = fHeight;
		if( m_pWorldEffect )
		{
			m_pWorldEffect->SetFloat(m_hWaterHeight, m_fWaterHeight);
			m_pWorldEffect->CommitChanges();
		}
	}
	unguard;
}

void CShaderMgr::UpdataSceneEffect()
{
	guardfunc;
	if (!m_bCanUseShader) return;
	if (m_dwSceneEffect&eNone) return;

	if (m_dwSceneEffect&eTemporalBlur)
	{
		m_hRenderFinalScene = m_pSceneEffect->GetTechniqueByName( "RS_TBlur" );
	}
	else if (m_dwSceneEffect&eBlur)
	{
		m_hRenderFinalScene = m_pSceneEffect->GetTechniqueByName( "RS_Blur" );
	}
	else
	{
		m_hRenderFinalScene = m_pSceneEffect->GetTechniqueByName( "RS_Others" );
	}

	if (m_dwSceneEffect&eBright)
		m_pSceneEffect->SetBool( "g_bBright", true );
	else
		m_pSceneEffect->SetBool( "g_bBright", false );

	if (m_dwSceneEffect&eMonochrome)
		m_pSceneEffect->SetBool( "g_bMono", true );
	else
		m_pSceneEffect->SetBool( "g_bMono", false );

	if (m_dwSceneEffect&eInverse)
		m_pSceneEffect->SetBool( "g_bInv", true );
	else
		m_pSceneEffect->SetBool( "g_bInv", false );

	if (m_dwSceneEffect&eNoise)
		m_pSceneEffect->SetBool( "g_bNoise", true );
	else
		m_pSceneEffect->SetBool( "g_bNoise", false );

	if (m_dwSceneEffect&eTint)
		m_pSceneEffect->SetBool( "g_bTint", true );
	else
		m_pSceneEffect->SetBool( "g_bTint", false );
	unguard;
}

void CShaderMgr::SetSceneEffectOn(DWORD dwEffect)
{
	guardfunc;
	if (dwEffect&eTemporalBlur)		//保存当前的画面 以备下一帧调用
	{
		IRenderer* RI = GetEngine()->GetRenderer();
		LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
		LPDIRECT3DSURFACE9	pRenderTarget;
		pDev->GetRenderTarget(0 , &pRenderTarget);
		// 泛光渲染到贴图功能太老，删除[QL]
		//pDev->StretchRect(pRenderTarget,NULL,m_pSceneSurface0,NULL, D3DTEXF_LINEAR);
	}

	m_dwSceneEffect|=dwEffect;

	if (!m_bCanUseShader) return;
	switch(dwEffect) {
	case eNone:
		break;
	case eTemporalBlur:
		m_hRenderFinalScene = m_pSceneEffect->GetTechniqueByName( "RS_TBlur" );
		break;
	case eBlur:
		if (!(m_dwSceneEffect&eTemporalBlur))
		{
			m_hRenderFinalScene = m_pSceneEffect->GetTechniqueByName( "RS_Blur" );
		}
		break;
	case eBright:
		m_pSceneEffect->SetBool( "g_bBright", true );
		break;
	case eMonochrome:
		m_pSceneEffect->SetBool( "g_bMono", true );
		break;
	case eInverse:
		m_pSceneEffect->SetBool( "g_bInv", true );
		break;
	case eNoise:
		m_pSceneEffect->SetBool( "g_bNoise", true );
		break;
	case eTint:
		m_pSceneEffect->SetBool( "g_bTint", true );
		break;
		//default:
	}
	unguard;
}
void CShaderMgr::SetSceneEffectOff(DWORD dwEffect)
{
	guardfunc;
	m_dwSceneEffect&=0xFFFFFFFF^dwEffect;
	if (!m_bCanUseShader) return;
	switch(dwEffect) {
	case eNone:
		break;
	case eTemporalBlur:
		if (m_dwSceneEffect&eBlur)
		{
			m_hRenderFinalScene = m_pSceneEffect->GetTechniqueByName( "RS_Blur" );
		}
		else
		{
			m_hRenderFinalScene = m_pSceneEffect->GetTechniqueByName( "RS_Others" );
		}
		break;
	case eBlur:
		if (!(m_dwSceneEffect&eTemporalBlur))
		{
			m_hRenderFinalScene = m_pSceneEffect->GetTechniqueByName( "RS_Others" );
		}
		break;
	case eBright:
		m_pSceneEffect->SetBool( "g_bBright", false );
		break;
	case eMonochrome:
		m_pSceneEffect->SetBool( "g_bMono", false );
		break;
	case eInverse:
		m_pSceneEffect->SetBool( "g_bInv", false );
		break;
	case eNoise:
		m_pSceneEffect->SetBool( "g_bNoise", false );
		break;
	case eTint:
		m_pSceneEffect->SetBool( "g_bTint", false );
		break;
		//default:
	}
	unguard;
}