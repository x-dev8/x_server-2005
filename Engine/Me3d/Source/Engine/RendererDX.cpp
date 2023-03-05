#include "Me3d/Engine/rendererdx.h"
#include "Me3d/Engine/TextureDx8.h"
#include "Me3d/Engine/Engine.h"
#include "FuncPerformanceLog.h"
#include "Me3d/D3dutil.h"
#include "Me3d/Config.h"
#include "Me3d/Global.h"
#include "Me3d/D3dRes.h"
#include "Me3d/Material.h"
#include "Me3d/Shader.h"
#include "Me3d/ShaderManager.h"
#include "Me3d/ShaderMgr.h"
#include "Me3d/Camera.h"
#include "Me3d/Model/Mex2.h"
#include <sstream>
#include <windows.h>
#include <assert.h>
#include "Dxsdk/D3D9.h"
#include "Dxsdk/d3d9types.h"
// add [5/28/2008 whu]
#ifndef STD_ThrowException
#define STD_ThrowException( error )                                 \
    std::stringstream __strTemp__;                                  \
    __strTemp__ << __FILE__ << "(" << __LINE__ << "): " << error;   \
    throw std::exception( __strTemp__.str().c_str() );
#endif

//-----------------------------------------------------------------------------
// Miscellaneous helper functions
//-----------------------------------------------------------------------------
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif


//extern void PushSurface(short nMainMapID, short nAddMapID, short nShaderID,			// 贴图/Shader
//						DWORD dwFvf,UINT nStride, BYTE * pVertices, WORD nVertCount,	// 顶点信息
//						BYTE * pIndeices, WORD nTriangleCount, DWORD dwFlag,
//						DWORD dwPolyType, INT nIBOffset );
FEngineState		GEngineState;
extern VOID Lock3DMemory();
extern VOID UnLockMemory();


const char* szShaderLevelName[2] = { "_Low", "_High" };

static graphics::ShaderVertexPixel* s_diffuseShader = 0;
static graphics::ShaderVertexPixel* s_diffuseLMShader = 0;
// added, jiayi, [2010/6/18]
static graphics::ShaderVertexPixel* s_shimmerShader = 0;
static graphics::ShaderVertexPixel* s_specularShader = 0;
static graphics::ShaderVertexPixel* s_noLightingShader = 0;
static graphics::ShaderVertexPixel* s_noLightingLMShader = 0;
static graphics::ShaderVertexPixel* s_alphaTestShader = 0;
static graphics::ShaderVertexPixel* s_alphaTestLMShader = 0;
static graphics::ShaderVertexPixel* s_particleShader = 0;
static graphics::ShaderVertexPixel* s_skyBoxShader = 0;
static graphics::ShaderVertexPixel* s_collisionShader = 0;
static graphics::ShaderVertexPixel* s_shadowShader = 0;
static graphics::ShaderVertexPixel* s_diffuseShaderSkeleton = 0;
static graphics::ShaderVertexPixel* s_shimmerShaderSkeleton = 0;
static graphics::ShaderVertexPixel* s_specularShaderSkeleton = 0;
static graphics::ShaderVertexPixel* s_shadowShaderSkeleton = 0;
static graphics::ShaderVertexPixel* s_effectShaderSkeleton = 0;
static graphics::ShaderVertexPixel* s_OutlineShader = 0;


//D3DVERTEXELEMENT9 MexDecl[] =
//{
//	{ 0, 0,  D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,		0 },
//	{ 0, 12, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,			0 },
//	{ 0, 24, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,			0 },
//	{ 0, 28, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,		0 },
//	D3DDECL_END()
//};

// D3DVERTEXELEMENT9 MexDecl[] =
// {
// 	{ 0, 0,  D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,		0 },
// 	{ 0, 12, D3DDECLTYPE_FLOAT3,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,			0 },
// 	{ 0, 24, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,		0 },
// 	D3DDECL_END()
// };
// 

// D3DVERTEXELEMENT9 UIDecl[] =
// {
// 	{ 0, 0,  D3DDECLTYPE_FLOAT4,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT,		0 },
// 	{ 0, 16, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,			0 },
// 	{ 0, 20, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,		0 },
// 	D3DDECL_END()
// };

//
//	FD3DRenderInterface::FD3DSavedState::FD3DSavedState
//
RendererDx::FD3DSavedState::FD3DSavedState()
{
	guard(RendererDx::FD3DSavedState::FD3DSavedState);

	ViewportX			= 0;
	ViewportY			= 0;
	ViewportWidth		= 0;
	ViewportHeight		= 0;

	ZBias				= 0;

	StencilTest			= CF_Always;
	StencilFailOp		= SO_Keep;
	StencilZFailOp		= SO_Keep;
	StencilPassOp		= SO_Keep;
	StencilRef			= 0;
	StencilMask			= 0xffffffff;
	StencilWriteMask	= 0xffffffff;

	D3DXMATRIX Identity = 
	D3DXMATRIX( 
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
	LocalToWorld		= Identity;
	WorldToCamera		= Identity;
	CameraToScreen		= Identity;

//	VertexShader		= NULL;
	memset(Streams, 0, sizeof(Streams));
	memset(StreamStrides, 0, sizeof(StreamStrides));

	NumStreams			= 0;

	IndexBuffer			= NULL;
	IndexBufferBase		= 0;

	CullMode			= D3DCULL_NONE;

	UseDynamicLighting	= 0;
	UseStaticLighting	= 1;
	LightingModulate2X	= 0;
	LightingOnly		= 0;
	//Lightmap			= NULL;
	memset( &AmbientLightColor, 0, sizeof(D3DCOLORVALUE) );
	memset(Lights, 0, sizeof(Lights));
	memset(LightEnabled,0, sizeof(LightEnabled));

	DistanceFogEnabled	= 0;
	DistanceFogStart	= 0.0f;
	DistanceFogEnd		= 0.0f;
	memset( &DistanceFogColor, 0, sizeof(D3DCOLORVALUE) );

	NumMaterialPasses	= 1;
	CurrentMaterialPass = 0;

	unguard;
}


 bool RendererDx::m_BOpenKT = false;

RendererDx::RendererDx(void):
m_pDevice(NULL),
m_nSurfaceCount(0),
m_nSortedSurfaceCount(0)
{

	guardfunc;
	m_fGlobalTransparent = 1.0f;
	m_fGlobalDiffuse[0] = 1.0f;
	m_fGlobalDiffuse[1] = 1.0f;
	m_fGlobalDiffuse[2] = 1.0f;

	m_fGlobalUOffset[0] = 0.0f;
	m_fGlobalUOffset[1] = 0.0f;
	m_fGlobalVOffset[0] = 0.0f;
	m_fGlobalVOffset[1] = 0.0f;

	m_shGlobalTextureID = -1;
	m_dwPolyType = D3DPT_TRIANGLELIST;

	//ZeroMemory( &mtrl, sizeof(mtrl) );
	D3DUtil_InitMaterial( m_DefaultMaterial, 1.0f, 1.0f, 1.0f );

// 	m_RenderBuffers[0].Create( 1024*1024*8 );
// 	m_RenderBuffers[1].Create( 1024*1024*8 );

	SavedStateIndex	= 0;
	CurrentState	= &SavedStates[SavedStateIndex];

// 	m_pMexDecl = NULL;
// 	m_pUIDecl = NULL;
// 	m_pMexVB = NULL;
// 	m_pUIVB = NULL;
// 	m_pUIIB = NULL;

	m_shSaveShaderID = -1;
	m_dwSaveFlag = 0xffffffff;

	m_nDynamicVertexOffset = 0;
	m_nMexVertexOffset = 0;

    //
    // add [5/26/2008 whu]
    //
    m_bSupportShader = true;
    m_bUseShader = true;
    m_pSpecularVS = NULL;
    m_pSpecularPS = NULL;
    m_pSpecularAndAnimPS = NULL;
    m_pSpecularVSCT = NULL;
    m_pSpecularPSCT = NULL;
    m_pSpecularAndAnimPS = NULL;
    m_pSpecularAndAnimPSCT = NULL;
    m_pBrightPS = NULL;
    m_pBrightPSCT = NULL;
    m_pCurrentVS = NULL;
    m_pCurrentPS = NULL;
    m_pCurrentVSCT = NULL;
    m_pCurrentPSCT = NULL;

    // transform.
    D3DXMatrixIdentity( &m_world );
    D3DXMatrixIdentity( &m_view );
    D3DXMatrixIdentity( &m_proj );

    //// material.
    //m_globalAmbient[0] = 0.3f;
    //m_globalAmbient[1] = 0.3f;
    //m_globalAmbient[2] = 0.3f;
    //m_globalAmbient[3] = 0.3f;

    //m_ambient[0] = 0.3f;
    //m_ambient[1] = 0.3f;
    //m_ambient[2] = 0.3f;
    //m_ambient[3] = 0.3f;

    //m_diffuse[0] = 1.0f;
    //m_diffuse[1] = 1.0f;
    //m_diffuse[2] = 1.0f;
    //m_diffuse[3] = 1.0f;

    //m_specular[0] = 1.0f;
    //m_specular[1] = 1.0f;
    //m_specular[2] = 1.0f;
    //m_specular[3] = 1.0f;

    //// light.
    //m_bLighting = false;

    //m_lightDir[0] = 0.0f;
    //m_lightDir[1] = 0.0f;
    //m_lightDir[2] = -1.0f;

    //m_lightAmbient[0] = 0.3f;
    //m_lightAmbient[1] = 0.3f;
    //m_lightAmbient[2] = 0.3f;
    //m_lightAmbient[3] = 0.3f;

    //m_lightDiffuse[0] = 1.0f;
    //m_lightDiffuse[1] = 1.0f;
    //m_lightDiffuse[2] = 1.0f;
    //m_lightDiffuse[3] = 1.0f;

    //m_lightSpecular[0] = 1.0f;
    //m_lightSpecular[1] = 1.0f;
    //m_lightSpecular[2] = 1.0f;
    //m_lightSpecular[3] = 1.0f;

    // material.
    m_globalAmbient = D3DXCOLOR( 0.3f, 0.3f, 0.3f, 1.0f );
    m_ambient =  D3DXCOLOR( 0.3f, 0.3f, 0.3f, 1.0f );
    m_diffuse =  D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
    m_specular =  D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );

    // light.
    m_bLighting = false;
	for(int i = 0; i < LIGHT_INDEX_COUNT; ++i)
	{
		m_lightDir[i] = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_lightAmbient[i] = D3DXCOLOR( 0.3f, 0.3f, 0.3f, 1.0f );
		m_lightDiffuse[i] = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
		m_lightSpecular[i] = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	}
    
    m_pAnimationTex = NULL;
	m_RenderTLightMap = false;

    m_pCurrentMaterial = NULL;

	m_d3dTerrainEffect = NULL;
	m_pTerrainMaterial = NULL;

	m_pMexMaterial = MeNew graphics::Material("MexShader");

    m_shaderParam["RenderShadow"] = 0.0f;
	m_uiShaderLevel = 1;//high
    //------------------------------------------
	m_LastTerrainIndexBuffer			= NULL;

	m_pCurrentShader = NULL;

	unguard;
}

RendererDx::~RendererDx(void)
{
	guardfunc;
// 	if( m_pMexDecl )
// 	{
// 		m_pMexDecl->Release();
// 		m_pMexDecl = NULL;
// 	}

// 	if( m_pMexVB )
// 	{
// 		m_pMexVB->Release();
// 		m_pMexVB = NULL;
// 	}

// 	if( m_pUIDecl )
// 	{
// 		m_pUIDecl->Release();
// 		m_pUIDecl = NULL;
// 	}

// 	if( m_pUIVB )
// 	{
// 		m_pUIVB->Release();
// 		m_pUIVB = NULL;
// 	}

// 	if( m_pUIIB )
// 	{
// 		m_pUIIB->Release();
// 		m_pUIIB = NULL;
// 	}

    // add [5/26/2008 whu]
    if ( m_pSpecularVS )
    {
        m_pSpecularVS->Release();
        m_pSpecularVS = NULL;
    }

    if ( m_pSpecularPS )
    {
        m_pSpecularPS->Release();
        m_pSpecularPS = NULL;
    }

    if ( m_pSpecularAndAnimPS )
    {
        m_pSpecularAndAnimPS->Release();
        m_pSpecularAndAnimPS = NULL;
    }

    if ( m_pSpecularVSCT )
    {
        m_pSpecularVSCT->Release();
        m_pSpecularVSCT = NULL;
    }

    if ( m_pSpecularPSCT )
    {
        m_pSpecularPSCT->Release();
        m_pSpecularPSCT = NULL;
    }

    if ( m_pSpecularAndAnimPSCT )
    {
        m_pSpecularAndAnimPSCT->Release();
        m_pSpecularAndAnimPSCT = NULL;
    }

    if ( m_pBrightPS )
    {
        m_pBrightPS->Release();
        m_pBrightPS = NULL;
    }

    if ( m_pBrightPSCT )
    {
        m_pBrightPSCT->Release();
        m_pBrightPSCT = NULL;
    }

    if ( m_pAnimationTex )
    {
        m_pAnimationTex->Release();
        m_pAnimationTex = NULL;
    }

	if (m_pMexMaterial)
	{
		delete m_pMexMaterial;
	}

	/*
	 * 2012.6.5 wangshuai
	 * 修正了调用引擎Release后, 再次SetEngine空指针导致程序崩溃的问题
	 */
	{
		m_pCurrentShader = 0;

		s_diffuseShader = 0;
		s_diffuseLMShader = 0;

		s_shimmerShader = 0;
		s_specularShader = 0;
		s_noLightingShader = 0;
		s_noLightingLMShader = 0;
		s_alphaTestShader = 0;
		s_alphaTestLMShader = 0;
		s_particleShader = 0;
		s_skyBoxShader = 0;
		s_collisionShader = 0;
		s_shadowShader = 0;
		s_diffuseShaderSkeleton = 0;
		s_shimmerShaderSkeleton = 0;
		s_specularShaderSkeleton = 0;
		s_shadowShaderSkeleton = 0;
		s_effectShaderSkeleton = 0;
		s_OutlineShader = 0;
	}

	unguard;
}

void RendererDx::SetDevice( void* pDevice )
{ 
	guardfunc;
    m_device = pDevice;
	m_pDevice = (LPDIRECT3DDEVICE9)pDevice; 
#ifdef USE_MANUAL_RS_MANAGED
    DeferredState.Init( this );
#else
	//m_pDevice->Init( this );
#endif
	m_pDevice->GetDeviceCaps(&DeviceCaps8);

// #if 0
// 	HRESULT hr;
// 	while(1)
// 	{
// 		hr = m_pDevice->CreateVertexDeclaration( MexDecl, &m_pMexDecl );
// 		if( SUCCEEDED(hr) ) break;
// 	}
// 
// 	while(1)
// 	{
// 		hr = m_pDevice->CreateVertexDeclaration( UIDecl, &m_pUIDecl );
// 		if( SUCCEEDED(hr) ) break;
// 	}
// 
// 	while(1)
// 	{
// 		hr = m_pDevice->CreateVertexBuffer( 2883540, D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_SYSTEMMEM, &m_pUIVB, NULL );
// 		if( SUCCEEDED(hr) ) break;
// 	}
// 
// 	while(1)
// 	{
// 		hr = m_pDevice->CreateVertexBuffer( 2883540, D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_SYSTEMMEM, &m_pMexVB, NULL );
// 		if( SUCCEEDED(hr) ) break;
// 	}
// 
// 	while(1)
// 	{
// 		hr = m_pDevice->CreateIndexBuffer( 1024*8*6*sizeof(unsigned short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pUIIB, NULL );
// 		if( SUCCEEDED(hr) ) break;
// 	}
// 
// 	short* shIBFace = NULL;
// 	while(1)
// 	{
// 		hr = m_pUIIB->Lock( 0, 1024*8*6*sizeof(unsigned short), (void**)&shIBFace, D3DLOCK_NOSYSLOCK );
// 		if( SUCCEEDED(hr) ) break;
// 	}
// 
// 	for( int i = 0; i < 1024*8; i++ )
// 	{
// 		shIBFace[i*6+0] = i*4+0;
// 		shIBFace[i*6+1] = i*4+1;
// 		shIBFace[i*6+2] = i*4+2;
// 
// 		shIBFace[i*6+3] = i*4+3;
// 		shIBFace[i*6+4] = i*4+2;
// 		shIBFace[i*6+5] = i*4+1;
// 	}
// 
// 	while(1)
// 	{
// 		hr = m_pUIIB->Unlock();
// 		if( SUCCEEDED(hr) ) break;
// 	}
// 
//     //
//     // add [5/26/2008 whu] -----------------
//     //
//     try
//     {
//         D3DCAPS9 Caps;
//         if( FAILED( m_pDevice->GetDeviceCaps( &Caps ) ) )
//         {
//             STD_ThrowException( "Dot't get device caps.\n" );
//         }
// 
//         // Check for vertex/pixel shaders 2.0 support
//         if( Caps.VertexShaderVersion < D3DVS_VERSION( 2, 0 ) || Caps.PixelShaderVersion < D3DPS_VERSION( 2, 0 ) )
//         {
//             STD_ThrowException( "Dot't support shader 2.0.\n" );
//         }
// 
//         ID3DXBuffer* pCode = NULL;
// 
//         if( !m_pSpecularVSCT && FAILED( D3DXCompileShaderFromFile( "DATA\\SHADER\\PostProcess\\RenderObject.fx",
//             NULL, NULL,
//             "Specular_vs",
//             "vs_2_0",
//             0,
//             &pCode,
//             NULL,
//             &m_pSpecularVSCT ) ) )
//         {
//             STD_ThrowException( "Failed to call D3DXCompileShaderFromFile (Specular_vs) in the file DATA\\SHADER\\PostProcess\\RenderObject.fx.\n" );
//         }
// 
//         if( !m_pSpecularVS && FAILED( m_pDevice->CreateVertexShader( reinterpret_cast< DWORD* >( pCode->GetBufferPointer() ), &m_pSpecularVS ) ) )
//         {
//             STD_ThrowException( "Failed to call CreateVertexShader (Specular_vs) in the file DATA\\SHADER\\PostProcess\\RenderObject.fx.\n" );
//         }
// 
//         if ( pCode )
//         {
//             pCode->Release();
//             pCode = NULL;
//         }
// 
//         if( !m_pSpecularPSCT && FAILED( D3DXCompileShaderFromFile( "DATA\\SHADER\\PostProcess\\RenderObject.fx",
//             NULL, NULL,
//             "Specular_ps",
//             "ps_2_0",
//             0,
//             &pCode,
//             NULL,
//             &m_pSpecularPSCT ) ) )
//         {
//             STD_ThrowException( "Failed to call D3DXCompileShaderFromFile (Specular_vs) in the file DATA\\SHADER\\PostProcess\\RenderObject.fx.\n" );
//         }
// 
//         if( !m_pSpecularPS && FAILED( m_pDevice->CreatePixelShader( reinterpret_cast< DWORD* >( pCode->GetBufferPointer() ), &m_pSpecularPS ) ) )
//         {
//             STD_ThrowException( "Failed to call CreatePixelShader (Specular_ps) in the file DATA\\SHADER\\PostProcess\\RenderObject.fx.\n" );
//         }
// 
//         if ( pCode )
//         {
//             pCode->Release();
//             pCode = NULL;
//         }
// 
//         if( !m_pSpecularAndAnimPSCT && FAILED( D3DXCompileShaderFromFile( "DATA\\SHADER\\PostProcess\\RenderObject.fx",
//             NULL, NULL,
//             "SpecularAndAnim_ps",
//             "ps_2_0",
//             0,
//             &pCode,
//             NULL,
//             &m_pSpecularAndAnimPSCT ) ) )
//         {
//             STD_ThrowException( "Failed to call D3DXCompileShaderFromFile (SpecularAndAnim_ps) in the file DATA\\SHADER\\PostProcess\\RenderObject.fx.\n" );
//         }
// 
//         if( !m_pSpecularAndAnimPS && FAILED( m_pDevice->CreatePixelShader( reinterpret_cast< DWORD* >( pCode->GetBufferPointer() ), &m_pSpecularAndAnimPS ) ) )
//         {
//             STD_ThrowException( "Failed to call CreatePixelShader (SpecularAndAnim_ps) in the file DATA\\SHADER\\PostProcess\\RenderObject.fx.\n" );
//         }
// 
//         if ( pCode )
//         {
//             pCode->Release();
//             pCode = NULL;
//         }
// 
//         if( !m_pBrightPSCT && FAILED( D3DXCompileShaderFromFile( "DATA\\SHADER\\PostProcess\\RenderObject.fx",
//             NULL, NULL,
//             "RenderObject_ps",
//             "ps_2_0",
//             0,
//             &pCode,
//             NULL,
//             &m_pBrightPSCT ) ) )
//         {
//             STD_ThrowException( "Failed to call D3DXCompileShaderFromFile (RenderObject_ps) in the file DATA\\SHADER\\PostProcess\\RenderObject.fx.\n" );
//         }
// 
//         if( !m_pBrightPS && FAILED( m_pDevice->CreatePixelShader( reinterpret_cast< DWORD* >( pCode->GetBufferPointer() ), &m_pBrightPS ) ) )
//         {
//             STD_ThrowException( "Failed to call CreatePixelShader (RenderObject_ps) in the file DATA\\SHADER\\PostProcess\\RenderObject.fx.\n" );
//         }
// 
//         if ( pCode )
//         {
//             pCode->Release();
//             pCode = NULL;
//         }
// 
//         if ( !m_pAnimationTex )
//         {
//             m_pCurrentVS = m_pSpecularVS;
//             m_pCurrentVSCT = m_pSpecularVSCT;
//             m_pCurrentPS = m_pSpecularAndAnimPS;
//             m_pCurrentPSCT = m_pSpecularAndAnimPSCT;
// 
//             if( FAILED( D3DXCreateTextureFromFileEx( m_pDevice, "Data\\TEXTURE\\Effect\\Rune.dds", D3DX_DEFAULT, D3DX_DEFAULT, 
//                 D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 
//                 D3DX_DEFAULT, D3DX_DEFAULT, 0, 
//                 NULL, NULL, &m_pAnimationTex ) ) )
//             {
//                 m_pCurrentPS = m_pSpecularPS;
//                 m_pCurrentPSCT = m_pSpecularPSCT;
//                 //STD_ThrowException( "Failed to call D3DXCreateTextureFromFileEx -> Data\\TEXTURE\\Effect\\Rune.dds.\n" );
//             }
//         }
//     }
//     catch( const std::exception& e )
//     {
//         m_bSupportShader = false;
//         m_bUseShader = false;
// 
//         OutputDebugString( e.what() );
//     }
// #endif
    //---------------------------------------

	//m_pDevice->CreateVertexDeclaration( MexDecl, &m_pMexDecl );
	//m_pDevice->CreateVertexDeclaration( UIDecl, &m_pUIDecl );
	//m_pDevice->CreateVertexBuffer( 2883540,	D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_pUIVB, NULL );
	//m_pDevice->CreateVertexBuffer( 2883540,	D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_pMexVB, NULL );
	//m_pDevice->CreateIndexBuffer( 1024*8*6*sizeof(unsigned short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pUIIB, NULL );

	//short* shIBFace = NULL;
	//m_pUIIB->Lock( 0, 1024*8*6*sizeof(unsigned short), (void**)&shIBFace, D3DLOCK_NOSYSLOCK );
	//for( int i = 0; i < 1024*8; i++ )
	//{
	//	shIBFace[i*6+0] = i*4+0;
	//	shIBFace[i*6+1] = i*4+1;
	//	shIBFace[i*6+2] = i*4+2;

	//	shIBFace[i*6+3] = i*4+3;
	//	shIBFace[i*6+4] = i*4+2;
	//	shIBFace[i*6+5] = i*4+1;
	//}
	//m_pUIIB->Unlock();
	unguard;
}


// void RendererDx::PushEffectSurface( int nMainMapID, 
// 					   BYTE* pVertices, 
// 					   int nNumVert,
// 					   BYTE* pIndices,
// 					   int nNumTriangle,
// 					   DWORD dwFlag )
// {
// 	HREffectVert* pSrcVertices = (HREffectVert*)pVertices;
// 	int nFindBuffer = -1;
// 	// 查找texture相同的
// 	for( int nBuffer = 0; nBuffer < m_nNumEffectBuffer; nBuffer++ )
// 	{
// 		CHREffectBuffer& buffer = m_EffectBufferList[nBuffer];
// 		// 如果贴图不一样或者
// 		if( buffer.m_nTextureID != nMainMapID ||
// 			buffer.m_dwFlag != dwFlag )
// 			continue;
// 		// buffer满了
// 		if( buffer.m_nNumFace >= CHREffectBuffer::eMaxFace )
// 			continue;
// 		nFindBuffer = nBuffer;
// 		break;
// 	}
// }

// void RendererDx::PushSurface( short nMainMapID, 
// 								 short nAddMapID, 
// 								 short nShaderID,	// 贴图/Shader
// 								 DWORD dwFVF,
// 								 UINT nStride, 
// 								 BYTE *pVertices, 
// 								 WORD nVertCount,	// 顶点信息
// 								 BYTE * pIndeices, 
// 								 WORD nTriangleCount, 
// 								 DWORD dwFlag,
// 								 DWORD dwPolyType )
// {
// 	guardfunc;
// 	//CSALocker locker(this);
// 
// 	if( (0 >= nVertCount) ||
// 		nTriangleCount == 0 )
// 		return;
// 
//#ifdef USE_MANUAL_RS_MANAGED
 //  DeferredState.Commit();
//#endif
// 
// 	int const MAX_BUFFER = 1024*1024;
// 	static BYTE byBuffer[MAX_BUFFER];
// 
// 	Pointer p;
// 	p.byte = byBuffer;
// 
// 	float* normals = NULL;
// 	float* vertices = NULL;
// 	DWORD* diffuses = NULL;
// 	D3DXVECTOR2* uvs = NULL;
// 	m_dwPolyType = dwPolyType;
// 	// 顶点
// 	vertices = p.f;
// 	if( dwFVF & D3DFVF_XYZ )
// 		p.f += 3*nVertCount;
// 	else if( dwFVF & D3DFVF_XYZRHW )
// 		p.f += 4*nVertCount;
// 	if( dwFVF & D3DFVF_NORMAL )
// 	{
// 		normals = p.f;
// 		p.f += 3*nVertCount;
// 	}
// 	if( dwFVF & D3DFVF_DIFFUSE )
// 	{
// 		diffuses = p.dw;
// 		p.dw += nVertCount;
// 	}
// 	if( dwFVF & D3DFVF_TEX1 )
// 	{
// 		uvs = p.uv;
// 		p.uv += nVertCount;
// 	}
// 	for( int i = 0; i < nVertCount; i++ )
// 	{
// 		Pointer src;
// 		src.byte = &pVertices[i*nStride];
// 		if( dwFVF & D3DFVF_XYZ )
// 		{
// 			vertices[i*3] = *src.f++;
// 			vertices[i*3+1] = *src.f++;
// 			vertices[i*3+2] = *src.f++;
// 		}
// 		else if( dwFVF & D3DFVF_XYZRHW )
// 		{
// 			vertices[i*4] = *src.f++;
// 			vertices[i*4+1] = *src.f++;
// 			vertices[i*4+2] = *src.f++;
// 			vertices[i*4+3] = *src.f++;
// 		}
// 
// 		if( dwFVF & D3DFVF_NORMAL )
// 		{
// 			normals[i*3] = *src.f++;
// 			normals[i*3+1] = *src.f++;
// 			normals[i*3+2] = *src.f++;
// 		}
// 		if( dwFVF & D3DFVF_DIFFUSE )
// 		{
// 			diffuses[i] = *src.dw++;
// 		}
// 		if( dwFVF & D3DFVF_TEX1 )
// 		{
// 			uvs[i] = *src.uv++;
// 		}
// 	}
// 
// 	//CHRRenderSurface* pSurface = GetCurrentSurface();
// 	SetVertices( vertices );
// 	SetNormals( normals );
// 	SetDiffuse( diffuses );
// 	SetUVs( uvs, 0 );
// 	SetLayerCount( 1 );	
// 
// 	SetTextureId( nMainMapID, 0 );
// 	SetIndices( pIndeices );
// 	SetSurfaceFVF( dwFVF );
// 	SetVertexStride( nStride );
// 	SetShaderId( nShaderID );
// 	Push( nVertCount, nTriangleCount, dwFlag );
// 
// 
// 	Flush( 0 );
// 	unguard;
// }
// 

// MexVertex* RendererDx::LockMexVB( int nVertCount, int& nBaseVertexIndex )
// {
// 	guardfunc;
// 	MexVertex* pVBVertex = NULL;
// 	nBaseVertexIndex = m_nMexVertexOffset/sizeof(MexVertex);
// 	if( m_nMexVertexOffset + (sizeof(MexVertex)*nVertCount) > 2883540 )
// 	{
// 		m_nMexVertexOffset = 0;
// 		nBaseVertexIndex = 0;
// 
// 		if( FAILED( GetMexVB()->Lock( m_nMexVertexOffset, sizeof(MexVertex)*nVertCount, (void**)&pVBVertex, D3DLOCK_NOSYSLOCK|D3DLOCK_DISCARD ) ) )
// 			return NULL;
// 	}
// 	else
// 	{
// 		if( FAILED( GetMexVB()->Lock( m_nMexVertexOffset, sizeof(MexVertex)*nVertCount, (void**)&pVBVertex, D3DLOCK_NOSYSLOCK|D3DLOCK_NOOVERWRITE ) ) )
// 			return NULL;
// 	}
// 
// 	m_nMexVertexOffset += sizeof(MexVertex)*nVertCount;
// 
// 	return pVBVertex;
// 	unguard;
// }
// 
// void RendererDx::UnlockMexVB()
// {
// 	guardfunc;
// 	if( FAILED( GetMexVB()->Unlock() ) )
// 	{
// 		assert( "Can not UnlockVB !!!!!!!! A Level Bug!!!" && false );
// 	}
// 	unguard;
// }

// void RendererDx::BeginFastRenderMex()
// {
// 	guardfunc;
// 	//m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00000000 );
// 	m_pDevice->SetRenderState( D3DRS_AMBIENT, 0x00000000 );
// 
// 	//m_pDevice->SetRenderState( D3DRS_FOGENABLE, FALSE );
// 
// 	m_pDevice->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL );
// 	m_pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
// 
// 
// 	unguard;
// }
// 
// void RendererDx::EndFastRenderMex()
// {
// 	guardfunc;
// 	m_pDevice->SetFVF( D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1 );
// 	unguard;
// }



// void RendererDx::FastRenderMex(short nMainMapID,
// 								  short nAddMapID,
// 								  WORD nVertCount,
// 								  BYTE *pIndeices,
// 								  WORD nTriangleCount,
// 								  DWORD dwFlag,
// 								  D3DMATERIAL9* mtrl,
// 								  INT nVBOffset )
// {
// 	guardfunc;
// 	//TRUETIMEFUNC();
// 
// 	//m_pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
// 
// 	m_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
// 
// 	m_pDevice->SetMaterial( mtrl );
// 
// 
// 	//static float fLastAlpha = -1;
// 
// 	//if( fLastAlpha != m_fGlobalTransparent )
// 	//{
// 	//	D3DMATERIAL9 mtrl;
// 	//	D3DUtil_InitMaterial( mtrl, 1.0f, 0.0f, 0.0f );
// 	//	mtrl.Ambient.a = 1.0f;
// 	//	mtrl.Ambient.r = 1.0f;
// 	//	mtrl.Ambient.g = 1.0f;
// 	//	mtrl.Ambient.b = 1.0f;
// 	//	mtrl.Diffuse.a = m_fGlobalTransparent;
// 	//	mtrl.Diffuse.r = 1.0f;
// 	//	mtrl.Diffuse.g = 1.0f;
// 	//	mtrl.Diffuse.b = 1.0f;
// 	//	m_pDevice->SetMaterial( &mtrl );
// 
// 	//	fLastAlpha = m_fGlobalTransparent;
// 	//}
// 
// 
// 	ITexture* pTexture = GetEngine()->GetTextureManager()->GetTexture( nMainMapID );
// 	if( pTexture )
// 	{
// 		m_pDevice->SetTexture( 0, (LPDIRECT3DTEXTURE9)pTexture->GetData() );
// 	}
// 
// 	m_pDevice->SetVertexDeclaration( GetMexDecl() );
// 	m_pDevice->SetStreamSource( 0, (IDirect3DVertexBuffer9*)GetMexVB(), 0, sizeof(MexVertex) );
// 	m_pDevice->SetIndices( (IDirect3DIndexBuffer9*)pIndeices );
// 
// 	m_pDevice->DrawIndexedPrimitive(
// 		D3DPT_TRIANGLELIST,
// 		nVBOffset,
// 		0,
// 		nVertCount,
// 		0,
// 		nTriangleCount );
// 
// 	unguard;
// }


void RendererDx::DirectPushSurface( short nMainMapID,
								   short nAddMapID,
								   short nShaderID,
								   DWORD dwFvf,
								   UINT nStride,
								   BYTE *pVertices,
								   UINT nVertCount,
								   BYTE *pIndeices,
								   UINT nTriangleCount,
								   DWORD dwFlag,
								   DWORD dwPolyType,
								   INT nIBOffset, INT nVBOffset, int nType,
								   short nLuminanceMapID )
{
	MeScopeProfileCommonFun;
	guardfunc;
	//CSALocker locker(this);

	if (0 >= nVertCount)
	{
		return;
	}
	int nBaseVertexIndex = 0;

	IRenderer* r = this;

// 	LPDIRECT3DTEXTURE9 d3dBaseTex = NULL;
// 	LPDIRECT3DTEXTURE9 d3dBrightTex = NULL;
// 
// 	if( dwFlag & eNeedNotSetTexture )
// 	{
// 
// 	}
// 	else
// 	{
// 		ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nMainMapID );
// 		if( pTexture )
// 		{
// 			d3dBaseTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
// 			if ( d3dBaseTex )
// 			{
// 				r->SetTexture( 0, d3dBaseTex );
// 			}
// 			else
// 				return;
// 		}
// 		else
// 		{
// 			r->SetTexture( 0, NULL );
// 		}
// 	}
// 
// 	if( nAddMapID != -1 )
// 	{
// 		ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nAddMapID );
// 		if( pBaseTexture != NULL )
// 		{
// 			LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
// 			r->SetTexture( 1, pd3dTexture );
// 		}
// 		else
// 			r->SetTexture( 1, NULL );
// 	}
// 	// add [5/26/2008 whu]
// 	else if ( nLuminanceMapID != -1 )
// 	{
// 		ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLuminanceMapID );
// 		if( pBaseTexture != NULL )
// 		{
// 			d3dBrightTex = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
// 			r->SetTexture( 1, d3dBrightTex );
// 		}
// 		else
// 		{
// 			r->SetTexture( 1, NULL );
// 			//r->SetTexture( 2, NULL );
// 		}
// 	}
// 	else	
// 	{
// 		r->SetTexture( 1, NULL );
// 		//r->SetTexture( 2, NULL );
// 	}

	LPDIRECT3DTEXTURE9 d3dBrightTex = NULL;
	ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLuminanceMapID );
	if( pBaseTexture != NULL )
	{
		d3dBrightTex = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
	}
	if( !SetTextures( dwFlag, nMainMapID, nAddMapID, d3dBrightTex ) )
		return;

	m_shSaveShaderID = nShaderID;
	SetRenderStatesWithFlag( dwFlag, dwFvf, nMainMapID, nAddMapID );

	if (s_diffuseShader == NULL)
	{
		s_diffuseShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderDiffuse");
		s_diffuseLMShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderDiffuseLM");
		s_shimmerShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderShimmer");
		s_specularShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderSpecular");
		s_noLightingShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderNoLighting");
		s_noLightingLMShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderNoLightingLM");
		s_alphaTestShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderAlphaTest");
		s_alphaTestLMShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderAlphaTestLM");
		s_particleShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderParticle");
		s_skyBoxShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderSkyBox");
		s_collisionShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderCollision");
		s_shadowShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderShadow");
		s_OutlineShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderOutline");
	}

// 	if (graphics::ShaderManager::instance()->isUseOuterShader())
// 	{
// 		graphics::Material* material = 0;
// 		material = m_pMexMaterial;
// 		if (!material->getShader())
// 		{
// 			material->setShader("MexShader");
// 		}
// 
// 		graphics::ShaderEffect* pShaderEffect = 0;
// 		ID3DXEffect* pd3dEffect = 0;
// 		if (material && (pShaderEffect = (graphics::ShaderEffect*)material->getShader()) &&
// 			(pd3dEffect = pShaderEffect->getID3DXEffect()))
// 		{
// 			pd3dEffect->SetTexture( "baseTex", d3dBaseTex );
// 			if (d3dBrightTex)
// 			{
// 				pd3dEffect->SetTexture( "brightTex", d3dBrightTex );
// 				pd3dEffect->SetFloat( "specular", 1.0f );
// 			}
// 			else
// 				pd3dEffect->SetFloat( "specular", 0.0f );
// 
// 			D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
// 			pd3dEffect->SetMatrix( "world", &m_world );
// 			pd3dEffect->SetMatrix( "worldViewProj", &wvp );
// 			pd3dEffect->SetValue( "eye", &GetMe3dConfig()->GetCamera()->GetEyePt(), sizeof(D3DXVECTOR3) );
// 			pd3dEffect->SetValue( "lightDir", &m_lightDir[LIGHT_INDEX_TERRAIN], sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]) );
// 			pd3dEffect->SetValue( "lightAmbient", &m_lightAmbient[LIGHT_INDEX_TERRAIN], sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]) );
// 			pd3dEffect->SetValue( "lightDiffuse", &m_lightDiffuse[LIGHT_INDEX_TERRAIN], sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]) );
// 			pd3dEffect->SetValue( "lightColor", &m_lightDiffuse[LIGHT_INDEX_COLLISION], sizeof(m_lightDiffuse[LIGHT_INDEX_COLLISION]) );
// 			pd3dEffect->SetFloat( "g_FarPlane", Config::GetCamera()->GetFarPlane() );
// 			pd3dEffect->SetFloat( "alpha", m_fGlobalTransparent );
// 			pd3dEffect->CommitChanges();
// 		}
// 	}

	if( dwFlag & eUseVB )
	{
		assert( nStride );

		if( dwFlag & eNeetNotDraw )
		{
			r->Commit();

			//m_pDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
			//////m_pDevice->SetRenderState( D3DRS_ZFUNC, D3DCMP_GREATER );
			//m_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );

			//m_pDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
			//m_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
			//m_pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_INVSRCALPHA );
			//m_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_SRCALPHA );
			//m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
			////m_pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
			////m_pDevice->SetRenderState( D3DRS_STENCILENABLE, FALSE );
			////m_pDevice->SetRenderState( D3DRS_TWOSIDEDSTENCILMODE)

			//m_pDevice->SetTexture( 0, NULL );
			//m_pDevice->SetTexture( 1, NULL );
			//m_pDevice->SetTexture( 2, NULL );

		}
		else
		{
			if( dwFlag & eUseIB )
			{
				r->SetStreamSource( 0, (IDirect3DVertexBuffer9*)pVertices, nStride );
				r->SetIndices( (IDirect3DIndexBuffer9*)pIndeices, 0 );	
				r->Commit();

				if ((nShaderID == MEX2_SHADER || nShaderID == HELP_COLI_FLOOR || nShaderID == MEX2_PARTICLE) &&
					graphics::ShaderManager::instance()->isUseShader())// && !graphics::ShaderManager::instance()->isUseOuterShader())
				{
					graphics::ShaderVertexPixel* pShader = 0;
					if(graphics::ShaderManager::instance()->isUseOutline())
					{
						m_pCurrentShader = s_OutlineShader;
						if(m_pCurrentShader)
						{
							D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
							m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
						}
					}
					else if (graphics::ShaderManager::instance()->isRenderShadow())
					{
						pShader = s_shadowShader;
						if (pShader)
						{
							// vertex program parameter
							pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
						}
					}
					else if (nShaderID == HELP_COLI_FLOOR)
					{
						pShader = s_collisionShader;
						if (pShader)
						{
							// vertex program parameter
							D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
							pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
						}
					}
					else if (nShaderID == MEX2_PARTICLE)
					{
						pShader = s_particleShader;
						if (pShader)
						{
							// vertex program parameter
							D3DXMATRIXA16 wvp = m_view * m_proj;
							pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
						}
					}
					else if (dwFlag & eRenderSkyBox)
					{
						pShader = s_skyBoxShader;
						if (pShader)
						{
							// vertex program parameter
							D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
							pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
						}
					}
					else if(dwFlag & eRenderTreeLeaf)
					{
						pShader = s_alphaTestShader;
						if (pShader)
						{
							// vertex program parameter
							D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
							pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_World, &m_world);
							pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
							pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
								sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
							pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
								sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
							pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
								sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));
							pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
								sizeof(m_fGlobalTransparent));
						}
					}
					// added, jiayi, [2010/6/18]
					else if( dwFlag & eShimmer ) // shimmer
					{
						//////////////////////////////////
						/// 设置backbuff的工作在外层做 ///
						//////////////////////////////////
						pShader = s_shimmerShader;
						if( pShader )
						{
							// vertex program parameter
							D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
							pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
							pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
								sizeof(m_fGlobalTransparent));
							float fTimer = (float)HQ_TimeGetTime();
							pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_Timer, &fTimer,
								sizeof(float));

						}
					}
					else if(dwFlag & eLightingDisable)//不受光照
					{
						pShader = s_noLightingShader;
						if (pShader)
						{
							// vertex program parameter
							D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
							pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
							pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
								sizeof(m_fGlobalTransparent));

							if (graphics::ShaderManager::instance()->isUseShadow())
							{
								pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, true);
								pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ShadowMapMatrix, graphics::ShaderManager::instance()->getShadowMapMatrix());
								pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
								m_pDevice->SetTexture(1, graphics::ShaderManager::instance()->getShadowMap());
							}
							else
							{
								pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, false);
							}
						}
					}
					else if (d3dBrightTex)
					{
						pShader = s_specularShader;
						if (pShader)
						{
							// vertex program parameter
							D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
							pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_World, &m_world);
							pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
							pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
								sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
							pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
								sizeof(m_fGlobalTransparent));
							pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Eye, &GetMe3dConfig()->GetCamera()->GetEyePt(),
								sizeof(D3DXVECTOR3));

							// pixel program parameter
							pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
								sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
							pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
								sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));

							float specular = d3dBrightTex == NULL ? 0.0f : 1.0f;
							pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_Specular, &specular,
								sizeof(specular));
						}
					}
					else
					{
						pShader = s_diffuseShader;
						if (pShader)
						{
							// vertex program parameter
							D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
							pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_World, &m_world);
							pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
							pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
								sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));

							// pixel program parameter
							pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
								sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
							pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
								sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));

							if (graphics::ShaderManager::instance()->isUseShadow())
							{
								pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, true);
								pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ShadowMapMatrix, graphics::ShaderManager::instance()->getShadowMapMatrix());
								pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
								m_pDevice->SetTexture(1, graphics::ShaderManager::instance()->getShadowMap());
							}
							else
							{
								pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, false);
							}
						}
					}

					if (pShader)
					{
						pShader->begin( *m_pMexMaterial );
						pShader->beginPass();
						{
							m_pDevice->DrawIndexedPrimitive(
								(D3DPRIMITIVETYPE) dwPolyType,
								nBaseVertexIndex,
								0,
								nVertCount,
								nIBOffset,
								nTriangleCount );
						}
						pShader->endPass();
						pShader->end();
					}
				}
				else
				{
					m_pDevice->DrawIndexedPrimitive(
						(D3DPRIMITIVETYPE) dwPolyType,
						nBaseVertexIndex,
						0,
						nVertCount,
						nIBOffset,
						nTriangleCount );
				}
			}
			else
			{
				r->SetStreamSource( 0, (IDirect3DVertexBuffer9*)pVertices, nStride );
				r->Commit();

				LONG Rt = 	m_pDevice->DrawPrimitive(
					(D3DPRIMITIVETYPE) dwPolyType,
					0,
					nTriangleCount);
			}

		}

		r->SetStreamSource( 0, NULL, 0 );
		r->SetIndices( NULL, 0 );	
	}
	else
	{
		r->SetStreamSource( 0, NULL, 0 );
		r->SetIndices( NULL, 0 );	
		r->Commit();

		if ( (nShaderID == MEX2_SHADER || nShaderID == HELP_COLI_FLOOR || nShaderID == MEX2_PARTICLE) &&
			graphics::ShaderManager::instance()->isUseShader())// && !graphics::ShaderManager::instance()->isUseOuterShader())
		{
			graphics::ShaderVertexPixel* pShader = 0;
			if(graphics::ShaderManager::instance()->isUseOutline())
			{
				m_pCurrentShader = s_OutlineShader;
				if(m_pCurrentShader)
				{
					D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
					m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
				}
			}
			else if (graphics::ShaderManager::instance()->isRenderShadow())
			{
				pShader = s_shadowShader;
				if (pShader)
				{
					// vertex program parameter
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
				}
			}
			else if (nShaderID == HELP_COLI_FLOOR)
			{
				pShader = s_collisionShader;
				if (pShader)
				{
					// vertex program parameter
					D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
				}
			}
			else if (nShaderID == MEX2_PARTICLE)
			{
				pShader = s_particleShader;
				if (pShader)
				{
					// vertex program parameter
					D3DXMATRIXA16 wvp = m_view * m_proj;
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
				}
			}
			else if (dwFlag & eRenderSkyBox)
			{
				pShader = s_skyBoxShader;
				if (pShader)
				{
					// vertex program parameter
					D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
				}
			}
			else if(dwFlag & eRenderTreeLeaf)
			{
				pShader = s_alphaTestShader;
				if (pShader)
				{
					// vertex program parameter
					D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_World, &m_world);
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
					pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
					pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
					pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));
					pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
						sizeof(m_fGlobalTransparent));
				}
			}
			else if(dwFlag & eLightingDisable)//不受光照
			{
				pShader = s_noLightingShader;
				if (pShader)
				{
					// vertex program parameter
					D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
					pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
						sizeof(m_fGlobalTransparent));

					if (graphics::ShaderManager::instance()->isUseShadow())
					{
						pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, true);
						pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ShadowMapMatrix, graphics::ShaderManager::instance()->getShadowMapMatrix());
						pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
						m_pDevice->SetTexture(1, graphics::ShaderManager::instance()->getShadowMap());
					}
					else
					{
						pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, false);
					}
				}
			}
			else if (d3dBrightTex)
			{
				pShader = s_specularShader;
				if (pShader)
				{
					// vertex program parameter
					D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_World, &m_world);
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
					pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
					pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
						sizeof(m_fGlobalTransparent));
					pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Eye, &GetMe3dConfig()->GetCamera()->GetEyePt(),
						sizeof(D3DXVECTOR3));

					// pixel program parameter
					pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
					pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));

					float specular = d3dBrightTex == NULL ? 0.0f : 1.0f;
					pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_Specular, &specular,
						sizeof(specular));
				}
			}
			else
			{
				pShader = s_diffuseShader;
				if (pShader)
				{
					// vertex program parameter
					D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_World, &m_world);
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
					pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));

					// pixel program parameter
					pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
					pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));

					if (graphics::ShaderManager::instance()->isUseShadow())
					{
						pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, true);
						pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ShadowMapMatrix, graphics::ShaderManager::instance()->getShadowMapMatrix());
						pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
						m_pDevice->SetTexture(1, graphics::ShaderManager::instance()->getShadowMap());
					}
					else
					{
						pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, false);
					}
				}
			}

			if (pShader)
			{
				pShader->begin( *m_pMexMaterial );
				pShader->beginPass();
				{
					if (pIndeices)
					{
						m_pDevice->DrawIndexedPrimitiveUP(
							(D3DPRIMITIVETYPE)dwPolyType,
							0,
							nVertCount,
							nTriangleCount,
							pIndeices,
							D3DFMT_INDEX16,
							pVertices,
							nStride );
					}
					else
					{
						m_pDevice->DrawPrimitiveUP(
							(D3DPRIMITIVETYPE)dwPolyType,
							nTriangleCount,
							pVertices,
							nStride );
					}
				}
				pShader->endPass();
				pShader->end();
			}
		}
		else
		{
			if (dwFlag & eRenderSkyBox)
			{
				graphics::ShaderVertexPixel* pShader = s_skyBoxShader;
				if (pShader)
				{
					// vertex program parameter
					D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
					pShader->setVertexProgramParameter("worldViewProj", &wvp, sizeof(D3DXMATRIXA16));

					pShader->begin( *m_pMexMaterial );
					pShader->beginPass();
					{
						if (pIndeices)
						{
							m_pDevice->DrawIndexedPrimitiveUP(
								(D3DPRIMITIVETYPE)dwPolyType,
								0,
								nVertCount,
								nTriangleCount,
								pIndeices,
								D3DFMT_INDEX16,
								pVertices,
								nStride );
						}
						else
						{
							m_pDevice->DrawPrimitiveUP(
								(D3DPRIMITIVETYPE)dwPolyType,
								nTriangleCount,
								pVertices,
								nStride );
						}
					}
					pShader->endPass();
					pShader->end();
				}
			}
			else
			{
				if (pIndeices)
				{
					m_pDevice->DrawIndexedPrimitiveUP(
						(D3DPRIMITIVETYPE)dwPolyType,
						0,
						nVertCount,
						nTriangleCount,
						pIndeices,
						D3DFMT_INDEX16,
						pVertices,
						nStride );
				}
				else
				{
					m_pDevice->DrawPrimitiveUP(
						(D3DPRIMITIVETYPE)dwPolyType,
						nTriangleCount,
						pVertices,
						nStride );
				}
			}
		}

	}

	m_pDevice->SetTexture(1, 0);
	r->SetTexture( 1, NULL );
	r->SetTextureHardware( 1, NULL );

	unguard;

}

bool RendererDx::BeginDirectPushSurface(short nMainMapID,
										short nAddMapID,
										short nShaderID,
										DWORD dwFvf,
										LPDIRECT3DVERTEXBUFFER9 pVertices,
										LPDIRECT3DVERTEXBUFFER9 pNormals,
										LPDIRECT3DVERTEXBUFFER9 pColors,
										LPDIRECT3DVERTEXBUFFER9 pUVs,
										LPDIRECT3DINDEXBUFFER9 pIndeices,
										DWORD dwFlag,
										INT nVBOffset,
										int nType,
										short nLuminanceMapID,
										short nLightmapTexId,
										LPDIRECT3DVERTEXBUFFER9 pUVs2,
										Vector2* pvLightmapUVScale,
										Vector2* pvLightmapUVOffset )
{
	MeScopeProfileCommonFun;
	guardfunc;
	//CSALocker locker(this);


	if ( 0 )
    {
#ifdef USE_MANUAL_RS_MANAGED
        DeferredState.ClearFrame();
#else
		//m_pDevice->ClearFrame();
#endif
    }

	IRenderer* r = this;

// 	LPDIRECT3DTEXTURE9 d3dBaseTex = NULL;
// 	LPDIRECT3DTEXTURE9 d3dBrightTex = NULL;
// 
// 	if( dwFlag & eNeedNotSetTexture )
// 	{
// 
// 	}
// 	else
// 	{
// 		ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nMainMapID );
// 		if( pTexture )
// 		{
// 			d3dBaseTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
// 			if ( d3dBaseTex )
// 			{
// 				r->SetTexture( 0, d3dBaseTex );
// 				if(0)
// 					D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, d3dBaseTex, 0);
// 			}
// 			else
// 				return;
// 		}
// 		else
// 		{
// 			r->SetTexture( 0, NULL );
// 		}
// 	}
// 
// 	if( nAddMapID != -1 )
// 	{
// 		ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nAddMapID );
// 		if( pBaseTexture != NULL )
// 		{
// 			LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
// 			r->SetTexture( 1, pd3dTexture );
// 			if(0)
// 				D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, pd3dTexture, 0);
// 		}
// 		else
// 			r->SetTexture( 1, NULL );
// 	}
// 	// add [5/26/2008 whu]
// 	else if ( nLuminanceMapID != -1 )
// 	{
// 		ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLuminanceMapID );
// 		if( pBaseTexture != NULL )
// 		{
// 			d3dBrightTex = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
// 			r->SetTexture( 1, d3dBrightTex );
// 		}
// 		else
// 		{
// 			r->SetTexture( 1, NULL );
// 			//r->SetTexture( 2, NULL );
// 		}
// 	}
// 	else	
// 	{
// 		r->SetTexture( 1, NULL );
// 		//r->SetTexture( 2, NULL );
// 	}
	// 如果不使用shader，关闭lightmap
// 	if( !graphics::ShaderManager::instance()->isUseShader() )
// 		nLightmapTexId = -1;

	LPDIRECT3DTEXTURE9 d3dBrightTex = NULL;
	ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLuminanceMapID );
	if( pBaseTexture != NULL )
	{
		d3dBrightTex = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
	}

	if (!SetTextures( dwFlag, nMainMapID, nAddMapID, d3dBrightTex, nLightmapTexId))
		return false;

	m_shSaveShaderID = nShaderID;
	SetRenderStatesWithFlag( dwFlag, dwFvf, nMainMapID, nAddMapID, nLightmapTexId );

	if (dwFvf & D3DFVF_XYZ)
	{
		if( nLightmapTexId > -1 )//有lightmap
			m_pDevice->SetVertexDeclaration( CHRRenderSurface::ms_pVertexDeclHardware[CHRRenderSurface::VertexDeclaration_XYZ_LM] );
		else
			m_pDevice->SetVertexDeclaration( CHRRenderSurface::ms_pVertexDeclHardware[CHRRenderSurface::VertexDeclaration_XYZ] );
		m_pDevice->SetStreamSource( 0, pVertices,0, 3*4 );
	}
	else
	{
		m_pDevice->SetVertexDeclaration( CHRRenderSurface::ms_pVertexDeclHardware[CHRRenderSurface::VertexDeclaration_XYZW] );
		m_pDevice->SetStreamSource( 0, pVertices, 0, 4*4 );
	}
	if( dwFvf & D3DFVF_NORMAL )
	{
		m_pDevice->SetStreamSource( 1, pNormals, 0, 3*4 );
	}
	else
	{
		m_pDevice->SetStreamSource( 1, 0,0, 0 );
	}
	if( dwFvf & D3DFVF_DIFFUSE )
	{
		m_pDevice->SetStreamSource( 2, pColors,0, 4 );
	}
	else
	{
		m_pDevice->SetStreamSource( 2, 0,0, 0 );
	}
	m_pDevice->SetStreamSource( 3, pUVs, 0, 2*4 );
	if( nLightmapTexId > -1 )
		m_pDevice->SetStreamSource( 4, pUVs2, 0, 2*4 );
// 	m_pDevice->SetStreamSource( 4, pUVs, 0, 2*4 );

	r->SetIndices( (IDirect3DIndexBuffer9*)pIndeices, 0 );	
	r->MexCommit();//绘制模型的时候真正的提交渲染状态

// 	if (graphics::ShaderManager::instance()->isUseOuterShader())
// 	{
// 		graphics::Material* material = 0;
// 		material = m_pMexMaterial;
// 		if (!material->getShader())
// 		{
// 			material->setShader("MexShader");
// 		}
// 
// 		graphics::ShaderEffect* pShaderEffect = 0;
// 		ID3DXEffect* pd3dEffect = 0;
// 		if (material && (pShaderEffect = (graphics::ShaderEffect*)material->getShader()) &&
// 			(pd3dEffect = pShaderEffect->getID3DXEffect()))
// 		{
// 			pd3dEffect->SetTexture( "baseTex", d3dBaseTex );
// 			if (d3dBrightTex)
// 			{
// 				pd3dEffect->SetTexture( "brightTex", d3dBrightTex );
// 				pd3dEffect->SetFloat( "specular", 1.0f );
// 			}
// 			else
// 				pd3dEffect->SetFloat( "specular", 0.0f );
// 
// 			pd3dEffect->SetValue( "eye", &GetMe3dConfig()->GetCamera()->GetEyePt(), sizeof(D3DXVECTOR3) );
// 			pd3dEffect->SetValue( "lightDir", &m_lightDir[LIGHT_INDEX_TERRAIN], sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]) );
// 			pd3dEffect->SetValue( "lightAmbient", &m_lightAmbient[LIGHT_INDEX_TERRAIN], sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]) );
// 			pd3dEffect->SetValue( "lightDiffuse", &m_lightDiffuse[LIGHT_INDEX_TERRAIN], sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]) );
// 			pd3dEffect->SetValue( "lightColor", &m_lightDiffuse[LIGHT_INDEX_COLLISION], sizeof(m_lightDiffuse[LIGHT_INDEX_COLLISION]) );
// 			pd3dEffect->SetFloat( "g_FarPlane", Config::GetCamera()->GetFarPlane() );
// 			pd3dEffect->CommitChanges();
// 		}
// 	}

	if ((nShaderID == MEX2_SHADER || nShaderID == HELP_COLI_FLOOR || nShaderID == MEX2_PARTICLE) &&
		graphics::ShaderManager::instance()->isUseShader() )//&& !graphics::ShaderManager::instance()->isUseOuterShader())
	{
		if (s_diffuseShader == NULL)
		{
			s_diffuseShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderDiffuse");
			s_diffuseLMShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderDiffuseLM");
			s_shimmerShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderShimmer");
			s_specularShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderSpecular");
			s_noLightingShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderNoLighting");
			s_noLightingLMShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderNoLightingLM");
			s_alphaTestShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderAlphaTest");
			s_alphaTestLMShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderAlphaTestLM");
			s_particleShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderParticle");
			s_skyBoxShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderSkyBox");
			s_collisionShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderCollision");
			s_shadowShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderShadow");
		    s_OutlineShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderOutline");
		}

		if(graphics::ShaderManager::instance()->isUseOutline())
		{
			m_pCurrentShader = s_OutlineShader;
			if(m_pCurrentShader)
			{
				D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
				m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
			}
		}
		else if (graphics::ShaderManager::instance()->isRenderShadow())
		{
			m_pCurrentShader = s_shadowShader;
			if (m_pCurrentShader)
			{
				// vertex program parameter
				m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
			}
		}
		else if (nShaderID == HELP_COLI_FLOOR)
		{
			m_pCurrentShader = s_collisionShader;
		}
		else if (nShaderID == MEX2_PARTICLE)
		{
			m_pCurrentShader = s_particleShader;
		}
		else if (dwFlag & eRenderSkyBox)
		{
			m_pCurrentShader = s_skyBoxShader;
		}
		else if(dwFlag & eRenderTreeLeaf)
		{
			m_pCurrentShader = s_alphaTestShader;
			if( nLightmapTexId > -1 )
				m_pCurrentShader = s_alphaTestLMShader;
			if (m_pCurrentShader)
			{
				m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
				if( nLightmapTexId > -1 && pvLightmapUVScale && pvLightmapUVOffset)
				{
					m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightmapScale, pvLightmapUVScale,
						sizeof(*pvLightmapUVScale));
					m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightmapOffset, pvLightmapUVOffset,
						sizeof(*pvLightmapUVOffset));
				}	
				else
				{
					m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));
					m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
				}
			}
		}
		// added, jiayi, [2010/6/18]
		else if( dwFlag & eShimmer ) // shimmer
		{
			//////////////////////////////////
			/// 设置backbuff的工作在外层做 ///
			//////////////////////////////////
			m_pCurrentShader = s_shimmerShader;
			if (m_pCurrentShader != NULL)
			{
				// vertex program parameter
				float fTimer = (float)HQ_TimeGetTime();
				m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_Timer, &fTimer, sizeof(float));
				m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_World, &m_world);

				m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN], sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
				m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN], sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
				m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN], sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));				
			}
		}
		else if(dwFlag & eLightingDisable)//不受光照
		{
			m_pCurrentShader = s_noLightingShader;
			if( nLightmapTexId > -1 )
				m_pCurrentShader = s_noLightingLMShader;
			if (m_pCurrentShader)
			{
				// vertex program parameter

				if (graphics::ShaderManager::instance()->isUseShadow())
				{
					m_pCurrentShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, true);
					m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ShadowMapMatrix, graphics::ShaderManager::instance()->getShadowMapMatrix());
					m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());			
					int nSlot = 1;
					if( nLightmapTexId > -1 )
						nSlot = 2;
					m_pDevice->SetTexture(nSlot, graphics::ShaderManager::instance()->getShadowMap());
				}
				else
				{
					m_pCurrentShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, false);
				}

				if( nLightmapTexId > -1 && pvLightmapUVScale && pvLightmapUVOffset)
				{
					m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightmapScale, pvLightmapUVScale,
						sizeof(*pvLightmapUVScale));
					m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightmapOffset, pvLightmapUVOffset,
						sizeof(*pvLightmapUVOffset));
				}	
			}
		}
		else if (d3dBrightTex)
		{
			m_pCurrentShader = s_specularShader;
			if (m_pCurrentShader)
			{
				// vertex program parameter
				m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
				m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Eye, &GetMe3dConfig()->GetCamera()->GetEyePt(),
					sizeof(D3DXVECTOR3));

				// pixel program parameter
				m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
				m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));

				float specular = d3dBrightTex == NULL ? 0.0f : 1.0f;
				m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_Specular, &specular,
					sizeof(specular));
			}
		}
		else
		{
			m_pCurrentShader = s_diffuseShader;
			if( nLightmapTexId > -1 )
				m_pCurrentShader = s_diffuseLMShader;
			if (m_pCurrentShader)
			{

				// pixel program parameter
				m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));

				if( nLightmapTexId > -1 && pvLightmapUVScale && pvLightmapUVOffset)
				{
					m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightmapScale, pvLightmapUVScale,
						sizeof(*pvLightmapUVScale));
					m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightmapOffset, pvLightmapUVOffset,
						sizeof(*pvLightmapUVOffset));
				}	
				else
				{
					m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));
					m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
						sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
				}

				if (graphics::ShaderManager::instance()->isUseShadow())
				{
					m_pCurrentShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, true);
					m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ShadowMapMatrix, graphics::ShaderManager::instance()->getShadowMapMatrix());
					m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());						
					int nSlot = 1;
					if( nLightmapTexId > -1 )
						nSlot = 2;
					m_pDevice->SetTexture(nSlot, graphics::ShaderManager::instance()->getShadowMap());
				}
				else
				{
					m_pCurrentShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, false);
				}
			}
		}

       if(m_BOpenKT)
	   {
		   m_pCurrentShader = s_diffuseLMShader;
	   }

		if (m_pCurrentShader)
		{
			m_pCurrentShader->begin( *m_pMexMaterial );
			m_pCurrentShader->beginPass();

		}
	}

	return true;
	unguard;

}

void RendererDx::DoDirectPushSurface( UINT nVertCount,
										UINT nTriangleCount,
										DWORD dwPolyType,
										INT nIBOffset)
{
	MeScopeProfileCommonFun;
	if (0 >= nVertCount)
	{
		return;
	}

	if (m_pCurrentShader)
	{
		// vertex program parameter
		if (m_pCurrentShader == s_collisionShader)
		{
			D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
			m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
			m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_COLLISION],
				sizeof(m_lightDiffuse[LIGHT_INDEX_COLLISION]));
		}
		else if (/*
				 m_pCurrentShader == s_particleShader
				 ||*/
				 m_pCurrentShader == s_skyBoxShader
				 ||m_pCurrentShader == s_shimmerShader
				 )
		{
			D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
			m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
		}
		else if (m_pCurrentShader == s_alphaTestShader
			||m_pCurrentShader == s_noLightingLMShader
			||m_pCurrentShader == s_diffuseLMShader
			||m_pCurrentShader == s_noLightingShader
			||m_pCurrentShader == s_specularShader
			||m_pCurrentShader == s_diffuseShader
			)
		{
			D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
			m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_World, &m_world);
			m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
		}
		else if( m_pCurrentShader == s_alphaTestLMShader )
		{
			D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
			m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
		}

		if (m_pCurrentShader == s_alphaTestShader
			||m_pCurrentShader == s_shimmerShader
			||m_pCurrentShader == s_noLightingShader
			||m_pCurrentShader == s_specularShader
			||m_pCurrentShader == s_diffuseShader
			||m_pCurrentShader == s_alphaTestLMShader
			||m_pCurrentShader == s_noLightingLMShader
			||m_pCurrentShader == s_diffuseLMShader
			)
		{
			m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
				sizeof(m_fGlobalTransparent));
		}

#ifdef USE_MANUAL_RS_MANAGED
		if (DeferredState.IsLightChange(LIGHT_INDEX_TERRAIN))
#endif
		{
			if (m_pCurrentShader == s_alphaTestShader
				)
			{
				m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
				m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
				m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));
			}
			else if (m_pCurrentShader == s_diffuseShader
				||m_pCurrentShader == s_specularShader
				)
			{
				m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));

				// pixel program parameter
				m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
				m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));
			}
#ifdef USE_MANUAL_RS_MANAGED
			DeferredState.ClearLightChange(LIGHT_INDEX_TERRAIN);
#endif
		}
	}


	int nBaseVertexIndex = 0;

	if( m_BOpenKT )
	{
       D3DXMATRIX _S;
	   D3DXMatrixIdentity(&_S);
       D3DXMatrixScaling(&_S,1.0001f,1.0001f,1.0001f);
	   D3DXMATRIXA16 wvp = _S * m_world * m_view * m_proj;
	   m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
	   m_pDevice->DrawIndexedPrimitive(
		   (D3DPRIMITIVETYPE) dwPolyType,
		   nBaseVertexIndex,
		   0,
		   nVertCount,
		   nIBOffset,
		   nTriangleCount );
	   return;
	}

	 
	m_pDevice->DrawIndexedPrimitive(
		(D3DPRIMITIVETYPE) dwPolyType,
		nBaseVertexIndex,
		0,
		nVertCount,
		nIBOffset,
		nTriangleCount );

	

}

void RendererDx::EndDirectPushSurface()
{
	if (m_pCurrentShader)
	{
		m_pCurrentShader->endPass();
		m_pCurrentShader->end();

		m_pCurrentShader = NULL;		
	}
	m_pDevice->SetTexture(1, 0);
	this->SetTexture( 1, NULL );
	this->SetTextureHardware( 1, NULL );

	m_pDevice->SetTexture(2, 0);
	this->SetTexture( 2, NULL );
	this->SetTextureHardware( 2, NULL );

// 	this->SetStreamSource(0, 0, 0);
// 	this->SetStreamSource(1, 0, 0);
// 	this->SetStreamSource(2, 0, 0);
// 	this->SetStreamSource(3, 0, 0);
// 	this->SetStreamSource(4, 0, 0);
	m_pDevice->SetStreamSource(0, 0, 0, 0 );
	m_pDevice->SetStreamSource(1, 0, 0, 0 );
	m_pDevice->SetStreamSource(2, 0, 0, 0 );
	m_pDevice->SetStreamSource(3, 0, 0, 0 );
	m_pDevice->SetStreamSource(4, 0, 0, 0 );
	if ( 0 )
    {
#ifdef USE_MANUAL_RS_MANAGED
		DeferredState.DumpCount();
#endif
    }
}

void RendererDx::DirectPushSurface( short nMainMapID,
								   short nAddMapID,
								   short nShaderID,
								   DWORD dwFvf,
								   UINT nVertCount,
								   LPDIRECT3DVERTEXBUFFER9 pVertices,
								   LPDIRECT3DVERTEXBUFFER9 pNormals,
								   LPDIRECT3DVERTEXBUFFER9 pColors,
								   LPDIRECT3DVERTEXBUFFER9 pUVs,
								   LPDIRECT3DINDEXBUFFER9 pIndeices,
								   UINT nTriangleCount,
								   DWORD dwFlag,
								   DWORD dwPolyType,
								   INT nIBOffset, INT nVBOffset, int nType,
								   short nLuminanceMapID )
{
	MeScopeProfileCommonFun;
	guardfunc;
	//CSALocker locker(this);
	if (0 >= nVertCount)
	{
		return;
	}

	int nBaseVertexIndex = 0;

	IRenderer* r = this;

// 	LPDIRECT3DTEXTURE9 d3dBaseTex = NULL;
// 	LPDIRECT3DTEXTURE9 d3dBrightTex = NULL;
// 
// 	if( dwFlag & eNeedNotSetTexture )
// 	{
// 
// 	}
// 	else
// 	{
// 		ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nMainMapID );
// 		if( pTexture )
// 		{
// 			d3dBaseTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
// 			if ( d3dBaseTex )
// 			{
// 				r->SetTexture( 0, d3dBaseTex );
// 				if(0)
// 					D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, d3dBaseTex, 0);
// 			}
// 			else
// 				return;
// 		}
// 		else
// 		{
// 			r->SetTexture( 0, NULL );
// 		}
// 	}
// 
// 	if( nAddMapID != -1 )
// 	{
// 		ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nAddMapID );
// 		if( pBaseTexture != NULL )
// 		{
// 			LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
// 			r->SetTexture( 1, pd3dTexture );
// 			if(0)
// 				D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, pd3dTexture, 0);
// 		}
// 		else
// 			r->SetTexture( 1, NULL );
// 	}
// 	// add [5/26/2008 whu]
// 	else if ( nLuminanceMapID != -1 )
// 	{
// 		ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLuminanceMapID );
// 		if( pBaseTexture != NULL )
// 		{
// 			d3dBrightTex = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
// 			r->SetTexture( 1, d3dBrightTex );
// 		}
// 		else
// 		{
// 			r->SetTexture( 1, NULL );
// 			//r->SetTexture( 2, NULL );
// 		}
// 	}
// 	else	
// 	{
// 		r->SetTexture( 1, NULL );
// 		//r->SetTexture( 2, NULL );
// 	}
	LPDIRECT3DTEXTURE9 d3dBrightTex = NULL;
	ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLuminanceMapID );
	if( pBaseTexture != NULL )
	{
		d3dBrightTex = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
	}
	if( !SetTextures( dwFlag, nMainMapID, nAddMapID, d3dBrightTex ) )
		return;

	m_shSaveShaderID = nShaderID;
	SetRenderStatesWithFlag( dwFlag, dwFvf, nMainMapID, nAddMapID );

	if (dwFvf & D3DFVF_XYZ)
	{
		m_pDevice->SetVertexDeclaration( CHRRenderSurface::ms_pVertexDeclHardware[CHRRenderSurface::VertexDeclaration_XYZ] );
		m_pDevice->SetStreamSource( 0, pVertices,0, 3*4 );
	}
	else
	{
		m_pDevice->SetVertexDeclaration( CHRRenderSurface::ms_pVertexDeclHardware[CHRRenderSurface::VertexDeclaration_XYZW] );
		m_pDevice->SetStreamSource( 0, pVertices, 0, 4*4 );
	}
	if( dwFvf & D3DFVF_NORMAL )
	{
		m_pDevice->SetStreamSource( 1, pNormals, 0, 3*4 );
	}
	else
	{
		m_pDevice->SetStreamSource( 1, 0,0, 0 );
	}
	if( dwFvf & D3DFVF_DIFFUSE )
	{
		m_pDevice->SetStreamSource( 2, pColors,0, 4 );
	}
	else
	{
		m_pDevice->SetStreamSource( 2, 0,0, 0 );
	}
	m_pDevice->SetStreamSource( 3, pUVs, 0, 2*4 );
// 	m_pDevice->SetStreamSource( 4, pUVs, 0, 2*4 );

	r->SetIndices( (IDirect3DIndexBuffer9*)pIndeices, 0 );	
	r->MexCommit();

// 	if (graphics::ShaderManager::instance()->isUseOuterShader())
// 	{
// 		graphics::Material* material = 0;
// 		material = m_pMexMaterial;
// 		if (!material->getShader())
// 		{
// 			material->setShader("MexShader");
// 		}
// 
// 		graphics::ShaderEffect* pShaderEffect = 0;
// 		ID3DXEffect* pd3dEffect = 0;
// 		if (material && (pShaderEffect = (graphics::ShaderEffect*)material->getShader()) &&
// 			(pd3dEffect = pShaderEffect->getID3DXEffect()))
// 		{
// 			pd3dEffect->SetTexture( "baseTex", d3dBaseTex );
// 			if (d3dBrightTex)
// 			{
// 				pd3dEffect->SetTexture( "brightTex", d3dBrightTex );
// 				pd3dEffect->SetFloat( "specular", 1.0f );
// 			}
// 			else
// 				pd3dEffect->SetFloat( "specular", 0.0f );
// 
// 			D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
// 			pd3dEffect->SetMatrix( "world", &m_world );
// 			pd3dEffect->SetMatrix( "worldViewProj", &wvp );
// 			pd3dEffect->SetValue( "eye", &GetMe3dConfig()->GetCamera()->GetEyePt(), sizeof(D3DXVECTOR3) );
// 			pd3dEffect->SetValue( "lightDir", &m_lightDir[LIGHT_INDEX_TERRAIN], sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]) );
// 			pd3dEffect->SetValue( "lightAmbient", &m_lightAmbient[LIGHT_INDEX_TERRAIN], sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]) );
// 			pd3dEffect->SetValue( "lightDiffuse", &m_lightDiffuse[LIGHT_INDEX_TERRAIN], sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]) );
// 			pd3dEffect->SetValue( "lightColor", &m_lightDiffuse[LIGHT_INDEX_COLLISION], sizeof(m_lightDiffuse[LIGHT_INDEX_COLLISION]) );
// 			pd3dEffect->SetFloat( "g_FarPlane", Config::GetCamera()->GetFarPlane() );
// 			pd3dEffect->SetFloat( "alpha", m_fGlobalTransparent );
// 			pd3dEffect->CommitChanges();
// 		}
// 	}

	if ((nShaderID == MEX2_SHADER || nShaderID == HELP_COLI_FLOOR || nShaderID == MEX2_PARTICLE) &&
		graphics::ShaderManager::instance()->isUseShader())// && !graphics::ShaderManager::instance()->isUseOuterShader())
	{
		if (s_diffuseShader == NULL)
		{
			s_diffuseShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderDiffuse");
			s_shimmerShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderShimmer");
			s_specularShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderSpecular");
			s_noLightingShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderNoLighting");
			s_alphaTestShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderAlphaTest");
			s_particleShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderParticle");
			s_skyBoxShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderSkyBox");
			s_collisionShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderCollision");
			s_shadowShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderShadow");
		    s_OutlineShader = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderOutline");
		}

		graphics::ShaderVertexPixel* pShader = 0;
		if(graphics::ShaderManager::instance()->isUseOutline())
		{
			m_pCurrentShader = s_OutlineShader;
			if(m_pCurrentShader)
			{
				D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
				m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
			}
		}
		else if (graphics::ShaderManager::instance()->isRenderShadow())
		{
			pShader = s_shadowShader;
			if (pShader)
			{
				// vertex program parameter
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
			}
		}
		else if (nShaderID == HELP_COLI_FLOOR)
		{
			pShader = s_collisionShader;
			if (pShader)
			{
				// vertex program parameter
				D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
				pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_COLLISION],
					sizeof(m_lightDiffuse[LIGHT_INDEX_COLLISION]));
			}
		}
		else if (nShaderID == MEX2_PARTICLE)
		{
			pShader = s_particleShader;
			if (pShader)
			{
				// vertex program parameter
				D3DXMATRIXA16 wvp = m_view * m_proj;
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
			}
		}
		else if (dwFlag & eRenderSkyBox)
		{
			pShader = s_skyBoxShader;
			if (pShader)
			{
				// vertex program parameter
				D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
			}
		}
		else if(dwFlag & eRenderTreeLeaf)
		{
			pShader = s_alphaTestShader;
			if (pShader)
			{
				// vertex program parameter
				D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_World, &m_world);
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
				pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
				pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
				pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));
				pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
					sizeof(m_fGlobalTransparent));
			}
		}
		// added, jiayi, [2010/6/18]
		else if( dwFlag & eShimmer ) // shimmer
		{
			//////////////////////////////////
			/// 设置backbuff的工作在外层做 ///
			//////////////////////////////////
			pShader = s_shimmerShader;
			if( pShader )
			{
				// vertex program parameter
				D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
				pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
					sizeof(m_fGlobalTransparent));
				float fTimer = (float)HQ_TimeGetTime();
				pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_Timer, &fTimer,
					sizeof(float));

				m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN], sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
				m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN], sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
				m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN], sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));
			}
		}
		else if(dwFlag & eLightingDisable)//不受光照
		{
			pShader = s_noLightingShader;
			if (pShader)
			{
				// vertex program parameter
				D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_World, &m_world);
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
				pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
					sizeof(m_fGlobalTransparent));

				if (graphics::ShaderManager::instance()->isUseShadow())
				{
					pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, true);
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ShadowMapMatrix, graphics::ShaderManager::instance()->getShadowMapMatrix());
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
					m_pDevice->SetTexture(1, graphics::ShaderManager::instance()->getShadowMap());
				}
				else
				{
					pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, false);
				}
			}
		}
		else if (d3dBrightTex)
		{
			pShader = s_specularShader;
			if (pShader)
			{
				// vertex program parameter
				D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_World, &m_world);
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
				pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
				pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
					sizeof(m_fGlobalTransparent));
				pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Eye, &GetMe3dConfig()->GetCamera()->GetEyePt(),
					sizeof(D3DXVECTOR3));

				// pixel program parameter
				pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
				pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));

				float specular = d3dBrightTex == NULL ? 0.0f : 1.0f;
				pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_Specular, &specular,
					sizeof(specular));
			}
		}
		else
		{
			pShader = s_diffuseShader;
			if (pShader)
			{
				// vertex program parameter
				D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_World, &m_world);
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_WorldViewProjection, &wvp);
				pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
				pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
					sizeof(m_fGlobalTransparent));

				// pixel program parameter
				pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
				pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
					sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));

				if (graphics::ShaderManager::instance()->isUseShadow())
				{
					pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, true);
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ShadowMapMatrix, graphics::ShaderManager::instance()->getShadowMapMatrix());
					pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
					m_pDevice->SetTexture(1, graphics::ShaderManager::instance()->getShadowMap());
				}
				else
				{
					pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, false);
				}
			}
		}

		if (pShader)
		{
			pShader->begin( *m_pMexMaterial );
			pShader->beginPass();
			{
				m_pDevice->DrawIndexedPrimitive(
					(D3DPRIMITIVETYPE) dwPolyType,
					nBaseVertexIndex,
					0,
					nVertCount,
					nIBOffset,
					nTriangleCount );
			}
			pShader->endPass();
			pShader->end();
		}
	}
	else
	{
		m_pDevice->DrawIndexedPrimitive(
			(D3DPRIMITIVETYPE) dwPolyType,
			nBaseVertexIndex,
			0,
			nVertCount,
			nIBOffset,
			nTriangleCount );
	}

	m_pDevice->SetTexture(1, 0);
	r->SetTexture( 1, NULL );
	r->SetTextureHardware( 1, NULL );

	r->SetStreamSource(0, 0, 0);
	r->SetStreamSource(1, 0, 0);
	r->SetStreamSource(2, 0, 0);
	r->SetStreamSource(3, 0, 0);
	unguard;

}


bool RendererDx::BeginDirectPushSurfaceSkeleton( short nMainMapID,
										   short nAddMapID,
										   LPDIRECT3DVERTEXBUFFER9 pVertices,
										   LPDIRECT3DVERTEXBUFFER9 pNormals,
										   LPDIRECT3DVERTEXBUFFER9 pColors,
										   LPDIRECT3DVERTEXBUFFER9 pUVs,
										   LPDIRECT3DVERTEXBUFFER9 pBoneWeightAndIndices,
										   LPDIRECT3DINDEXBUFFER9 pIndeices,
										   DWORD dwFlag,
										   short nLuminanceMapID,
										   bool isEffect,
										   D3DCOLOR dwColor
										   )
{
	MeScopeProfileCommonFun;
	guardfunc;
	//CSALocker locker(this);


	IRenderer* r = this;

// 	LPDIRECT3DTEXTURE9 d3dBaseTex = NULL;
// 	LPDIRECT3DTEXTURE9 d3dBrightTex = NULL;
// 
// 	if( dwFlag & eNeedNotSetTexture )
// 	{
// 
// 	}
// 	else
// 	{
// 		ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nMainMapID );
// 		if( pTexture )
// 		{
// 			d3dBaseTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
// 			if ( d3dBaseTex )
// 			{
// 				r->SetTexture( 0, d3dBaseTex );
// 			}
// 			else
// 				return;
// 		}
// 		else
// 		{
// 			r->SetTexture( 0, NULL );
// 		}
// 	}
// 
// 	if( nAddMapID != -1 )
// 	{
// 		ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nAddMapID );
// 		if( pBaseTexture != NULL )
// 		{
// 			LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
// 			r->SetTexture( 1, pd3dTexture );
// 			if(0)
// 				D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, pd3dTexture, 0);
// 		}
// 		else
// 			r->SetTexture( 1, NULL );
// 	}
// 	// add [5/26/2008 whu]
// 	else if ( nLuminanceMapID != -1 )
// 	{
// 		ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLuminanceMapID );
// 		if( pBaseTexture != NULL )
// 		{
// 			d3dBrightTex = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
// 			r->SetTexture( 1, d3dBrightTex );
// 		}
// 		else
// 		{
// 			r->SetTexture( 1, NULL );
// 			//r->SetTexture( 2, NULL );
// 		}
// 	}
// 	else	
// 	{
// 		r->SetTexture( 1, NULL );
// 		//r->SetTexture( 2, NULL );
// 	}
	LPDIRECT3DTEXTURE9 d3dBrightTex = NULL;
	ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLuminanceMapID );
	if( pBaseTexture != NULL )
	{
		d3dBrightTex = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
	}
	if( !SetTextures( dwFlag, nMainMapID, nAddMapID, d3dBrightTex ) )
		return false;

	m_shSaveShaderID = MEX2_SHADER;
	SetRenderStatesWithFlag( dwFlag, 0xffffffff, nMainMapID, nAddMapID );


	//m_pDevice->SetFVF(D3DFVF_XYZB5|D3DFVF_LASTBETA_UBYTE4|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	m_pDevice->SetVertexDeclaration( CHRRenderSurface::ms_pSkeletonDeclHardware );
	m_pDevice->SetStreamSource( 0, pVertices, 0, sizeof(SkeletonVertex) );
	m_pDevice->SetStreamSource( 1, pUVs, 0, sizeof(float) * 2 );
	m_pDevice->SetStreamSource( 2, pColors, 0, sizeof(DWORD) );

	r->SetIndices( (IDirect3DIndexBuffer9*)pIndeices, 0 );	
	r->MexCommit();

	if (s_diffuseShaderSkeleton == NULL)
	{
		s_diffuseShaderSkeleton = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderDiffuseSkeleton");
		s_shimmerShaderSkeleton = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderShimmerSkeleton");
		s_specularShaderSkeleton = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderSpecularSkeleton");
		s_shadowShaderSkeleton = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderShadowSkeleton");
		s_effectShaderSkeleton = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderEffectSkeleton");
	}

	if (graphics::ShaderManager::instance()->isRenderShadow())
	{
		m_pCurrentShader = s_shadowShaderSkeleton;
		if (m_pCurrentShader)
		{
			// vertex program parameter
			m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
		}
	}
	else if( dwFlag & eShimmer )
	{
		m_pCurrentShader = s_shimmerShaderSkeleton;
		if (m_pCurrentShader)
		{
			// vertex program parameter
			float fTimer = (float)HQ_TimeGetTime();
			m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_Timer, &fTimer,
				sizeof(float));
		}
	}
	else if (isEffect)
	{
		m_pCurrentShader = s_effectShaderSkeleton;
		if (m_pCurrentShader)
		{
			D3DXCOLOR color(dwColor);
			// vertex program parameter
			m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &color,
				sizeof(color));
		}
	}
	else if (d3dBrightTex)
	{
		m_pCurrentShader = s_specularShaderSkeleton;
		if (m_pCurrentShader)
		{
			// vertex program parameter
			m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
				sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
			m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Eye, &GetMe3dConfig()->GetCamera()->GetEyePt(),
				sizeof(D3DXVECTOR3));

			// pixel program parameter
			m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
				sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
			m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
				sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));

			float specular = d3dBrightTex == NULL ? 0.0f : 1.0f;
			m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_Specular, &specular,
				sizeof(specular));
		}
	}
	else
	{
		m_pCurrentShader = s_diffuseShaderSkeleton;
		if (m_pCurrentShader)
		{
			m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
				sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
			// pixel program parameter
			m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
				sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
			m_pCurrentShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
				sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));

			if (graphics::ShaderManager::instance()->isUseShadow())
			{
				m_pCurrentShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, true);
				m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ShadowMapMatrix, graphics::ShaderManager::instance()->getShadowMapMatrix());
				m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
				m_pDevice->SetTexture(1, graphics::ShaderManager::instance()->getShadowMap());
			}
			else
			{
				m_pCurrentShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, false);
			}
		}
	}

	if (m_pCurrentShader)
	{
		m_pCurrentShader->begin( *m_pMexMaterial );
		m_pCurrentShader->beginPass();
	}

	return true;

	unguard;

}

void RendererDx::DoDirectPushSurfaceSkeleton( 	UINT nVertCount,
												UINT nTriangleCount,
												D3DXMATRIXA16* pBoneWorldMatrix,
												unsigned int nBoneMatrixCount  )

{
	MeScopeProfileCommonFun;
	if (0 >= nVertCount)
	{
		return;
	}

	if (m_pCurrentShader)
	{
		if (m_pCurrentShader == s_shadowShaderSkeleton)
		{
			m_pCurrentShader->setVertexProgramParameterMatrixArray(
				graphics::ShaderVertexPixel::SCT_BoneWorldMatrix,
				pBoneWorldMatrix, 
				nBoneMatrixCount
				);
		}
		else if (m_pCurrentShader == s_shimmerShaderSkeleton
			|| m_pCurrentShader == s_effectShaderSkeleton
			|| m_pCurrentShader == s_specularShaderSkeleton
			|| m_pCurrentShader == s_diffuseShaderSkeleton
			)
		{
			D3DXMATRIXA16 vp = m_view * m_proj;
			m_pCurrentShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ViewProjection, &vp);			
			m_pCurrentShader->setVertexProgramParameterMatrixArray(
				graphics::ShaderVertexPixel::SCT_BoneWorldMatrix,
				pBoneWorldMatrix, 
				nBoneMatrixCount
				);			
		}
		if (m_pCurrentShader == s_shimmerShaderSkeleton
			||m_pCurrentShader == s_effectShaderSkeleton
			||m_pCurrentShader == s_specularShaderSkeleton
			||m_pCurrentShader == s_diffuseShaderSkeleton
			)
		{
			m_pCurrentShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
				sizeof(m_fGlobalTransparent));
		}
	}

	int nBaseVertexIndex = 0;
	m_pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		nBaseVertexIndex,
		0,
		nVertCount,
		0,
		nTriangleCount );

}

void RendererDx::EndDirectPushSurfaceSkeleton()
{
	if (m_pCurrentShader)
	{
		m_pCurrentShader->endPass();
		m_pCurrentShader->end();

		m_pCurrentShader = NULL;
	}
	m_pDevice->SetTexture(1, 0);
	this->SetTexture( 1, NULL );
	this->SetTextureHardware( 1, NULL );

	m_pDevice->SetTexture(2, 0);
	this->SetTexture( 2, NULL );
	this->SetTextureHardware( 2, NULL );

	this->SetStreamSource(0, 0, 0);
	this->SetStreamSource(1, 0, 0);
	this->SetStreamSource(2, 0, 0);
	this->SetStreamSource(3, 0, 0);
	this->SetStreamSource(4, 0, 0);

}

void RendererDx::DirectPushSurfaceSkeleton( short nMainMapID,
								   short nAddMapID,
								   UINT nVertCount,
								   LPDIRECT3DVERTEXBUFFER9 pVertices,
								   LPDIRECT3DVERTEXBUFFER9 pNormals,
								   LPDIRECT3DVERTEXBUFFER9 pColors,
								   LPDIRECT3DVERTEXBUFFER9 pUVs,
								   LPDIRECT3DVERTEXBUFFER9 pBoneWeightAndIndices,
								   LPDIRECT3DINDEXBUFFER9 pIndeices,
								   UINT nTriangleCount,
								   DWORD dwFlag,
								   short nLuminanceMapID,
								   bool isEffect,
								   D3DCOLOR dwColor,
								   D3DXMATRIXA16* pBoneWorldMatrix,
								   unsigned int nBoneMatrixCount  )
{
	MeScopeProfileCommonFun;
	guardfunc;
	//CSALocker locker(this);

	int nBaseVertexIndex = 0;

	IRenderer* r = this;

// 	LPDIRECT3DTEXTURE9 d3dBaseTex = NULL;
// 	LPDIRECT3DTEXTURE9 d3dBrightTex = NULL;
// 
// 	if( dwFlag & eNeedNotSetTexture )
// 	{
// 
// 	}
// 	else
// 	{
// 		ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nMainMapID );
// 		if( pTexture )
// 		{
// 			d3dBaseTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
// 			if ( d3dBaseTex )
// 			{
// 				r->SetTexture( 0, d3dBaseTex );
// 			}
// 			else
// 				return;
// 		}
// 		else
// 		{
// 			r->SetTexture( 0, NULL );
// 		}
// 	}
// 
// 	if( nAddMapID != -1 )
// 	{
// 		ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nAddMapID );
// 		if( pBaseTexture != NULL )
// 		{
// 			LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
// 			r->SetTexture( 1, pd3dTexture );
// 			if(0)
// 				D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, pd3dTexture, 0);
// 		}
// 		else
// 			r->SetTexture( 1, NULL );
// 	}
// 	// add [5/26/2008 whu]
// 	else if ( nLuminanceMapID != -1 )
// 	{
// 		ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLuminanceMapID );
// 		if( pBaseTexture != NULL )
// 		{
// 			d3dBrightTex = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
// 			r->SetTexture( 1, d3dBrightTex );
// 		}
// 		else
// 		{
// 			r->SetTexture( 1, NULL );
// 			//r->SetTexture( 2, NULL );
// 		}
// 	}
// 	else	
// 	{
// 		r->SetTexture( 1, NULL );
// 		//r->SetTexture( 2, NULL );
// 	}

	LPDIRECT3DTEXTURE9 d3dBrightTex = NULL;
	ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLuminanceMapID );
	if( pBaseTexture != NULL )
	{
		d3dBrightTex = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
	}
	if( !SetTextures( dwFlag, nMainMapID, nAddMapID, d3dBrightTex ) )
		return;

	m_shSaveShaderID = MEX2_SHADER;
	SetRenderStatesWithFlag( dwFlag, 0xffffffff, nMainMapID, nAddMapID );

	//m_pDevice->SetFVF(D3DFVF_XYZB5|D3DFVF_LASTBETA_UBYTE4|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1);
	m_pDevice->SetVertexDeclaration( CHRRenderSurface::ms_pSkeletonDeclHardware );
#if 1
	m_pDevice->SetStreamSource( 0, pVertices, 0, sizeof(SkeletonVertex) );
	m_pDevice->SetStreamSource( 1, pUVs, 0, sizeof(float) * 2 );
	m_pDevice->SetStreamSource( 2, pColors, 0, sizeof(DWORD) );
#else
	m_pDevice->SetStreamSource( 0, pVertices, 0, sizeof(float) * 3 );
	m_pDevice->SetStreamSource( 1, pNormals, 0, sizeof(float) * 3 );
	m_pDevice->SetStreamSource( 2, pColors, 0, sizeof(DWORD) );
	m_pDevice->SetStreamSource( 3, pUVs, 0, sizeof(float) * 2 );
	m_pDevice->SetStreamSource( 4, pBoneWeightAndIndices, 0, sizeof(BoneWeightAndIndex) );
#endif

	r->SetIndices( (IDirect3DIndexBuffer9*)pIndeices, 0 );	
	r->MexCommit();

	if (s_diffuseShaderSkeleton == NULL)
	{
		s_diffuseShaderSkeleton = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderDiffuseSkeleton");
		s_shimmerShaderSkeleton = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderShimmerSkeleton");
		s_specularShaderSkeleton = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderSpecularSkeleton");
		s_shadowShaderSkeleton = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderShadowSkeleton");
		s_effectShaderSkeleton = (graphics::ShaderVertexPixel*)graphics::ShaderManager::instance()->getShader("MexShaderEffectSkeleton");
	}

	graphics::ShaderVertexPixel* pShader = 0;
	if (graphics::ShaderManager::instance()->isRenderShadow())
	{
		pShader = s_shadowShaderSkeleton;
		if (pShader)
		{
			// vertex program parameter
			pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
			pShader->setVertexProgramParameterMatrixArray(
				graphics::ShaderVertexPixel::SCT_BoneWorldMatrix,
				pBoneWorldMatrix, 
				nBoneMatrixCount
				);
		}
	}
	else if( dwFlag & eShimmer )
	{
		pShader = s_shimmerShaderSkeleton;
		if (pShader)
		{
			// vertex program parameter
			D3DXMATRIXA16 vp = m_view * m_proj;
			pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ViewProjection, &vp);			
			pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
				sizeof(m_fGlobalTransparent));
			pShader->setVertexProgramParameterMatrixArray(
				graphics::ShaderVertexPixel::SCT_BoneWorldMatrix,
				pBoneWorldMatrix, 
				nBoneMatrixCount
				);			
			float fTimer = (float)HQ_TimeGetTime();
			pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_Timer, &fTimer,
				sizeof(float));
		}
	}
	else if (isEffect)
	{
		pShader = s_effectShaderSkeleton;
		if (pShader)
		{
			D3DXCOLOR color(dwColor);
			// vertex program parameter
			D3DXMATRIXA16 vp = m_view * m_proj;
			pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ViewProjection, &vp);
			pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &color,
				sizeof(color));
			pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
				sizeof(m_fGlobalTransparent));
			pShader->setVertexProgramParameterMatrixArray(
				graphics::ShaderVertexPixel::SCT_BoneWorldMatrix,
				pBoneWorldMatrix, 
				nBoneMatrixCount
				);
		}
	}
	else if (d3dBrightTex)
	{
		pShader = s_specularShaderSkeleton;
		if (pShader)
		{
			// vertex program parameter
			D3DXMATRIXA16 vp = m_view * m_proj;
			pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ViewProjection, &vp);
			pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
				sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
			pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
				sizeof(m_fGlobalTransparent));
			pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Eye, &GetMe3dConfig()->GetCamera()->GetEyePt(),
				sizeof(D3DXVECTOR3));
			pShader->setVertexProgramParameterMatrixArray(
				graphics::ShaderVertexPixel::SCT_BoneWorldMatrix,
				pBoneWorldMatrix, 
				nBoneMatrixCount
				);

			// pixel program parameter
			pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
				sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
			pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
				sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));

			float specular = d3dBrightTex == NULL ? 0.0f : 1.0f;
			pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_Specular, &specular,
				sizeof(specular));
		}
	}
	else
	{
		pShader = s_diffuseShaderSkeleton;
		if (pShader)
		{
			// vertex program parameter
			D3DXMATRIXA16 vp = m_view * m_proj;
			pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ViewProjection, &vp);
			pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_LightDirection, &m_lightDir[LIGHT_INDEX_TERRAIN],
				sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]));
			pShader->setVertexProgramParameter(graphics::ShaderVertexPixel::SCT_Alpha, &m_fGlobalTransparent,
				sizeof(m_fGlobalTransparent));
			pShader->setVertexProgramParameterMatrixArray(
				graphics::ShaderVertexPixel::SCT_BoneWorldMatrix,
				pBoneWorldMatrix, 
				nBoneMatrixCount
				);

			// pixel program parameter
			pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightAmbient, &m_lightAmbient[LIGHT_INDEX_TERRAIN],
				sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]));
			pShader->setPixelProgramParameter(graphics::ShaderVertexPixel::SCT_LightDiffuse, &m_lightDiffuse[LIGHT_INDEX_TERRAIN],
				sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]));

			if (graphics::ShaderManager::instance()->isUseShadow())
			{
				pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, true);
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_ShadowMapMatrix, graphics::ShaderManager::instance()->getShadowMapMatrix());
				pShader->setVertexProgramParameterMatrix(graphics::ShaderVertexPixel::SCT_LightViewProjection, graphics::ShaderManager::instance()->getLightViewProjMatrix());
				m_pDevice->SetTexture(1, graphics::ShaderManager::instance()->getShadowMap());
			}
			else
			{
				pShader->setPixelProgramParameterBool(graphics::ShaderVertexPixel::SCT_UseShadow, false);
			}
		}
	}

	if (pShader)
	{
		pShader->begin( *m_pMexMaterial );
		pShader->beginPass();
		{
			m_pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLELIST,
				nBaseVertexIndex,
				0,
				nVertCount,
				0,
				nTriangleCount );
		}
		pShader->endPass();
		pShader->end();
	}

	m_pDevice->SetTexture(1, 0);
	m_pDevice->SetTexture(2, 0);
	r->SetTexture( 1, NULL );
	r->SetTexture( 2, NULL );
	r->SetTextureHardware( 1, NULL );
	r->SetTextureHardware( 2, NULL );

	r->SetStreamSource(0, 0, 0);
	r->SetStreamSource(1, 0, 0);
	r->SetStreamSource(2, 0, 0);
// 	r->SetStreamSource(3, 0, 0);
// 	r->SetStreamSource(4, 0, 0);
	unguard;

}

bool RendererDx::SetTextures( DWORD dwFlag, int nMainMapID, int nAddMapID, LPDIRECT3DTEXTURE9 d3dBrightTex, int nLightmapID /*= -1*/ )
{
	IRenderer* r = this;

	LPDIRECT3DTEXTURE9 d3dBaseTex = NULL;

	if( dwFlag & eNeedNotSetTexture )
	{

	}
	else
	{
		ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nMainMapID );
		if( pTexture )
		{
			d3dBaseTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
			if ( d3dBaseTex )
			{
				r->SetTexture( 0, d3dBaseTex );
				if(0)
					D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, d3dBaseTex, 0);
			}
			else
				return false;
		}
		else
		{
			r->SetTexture( 0, NULL );
		}
	}

	if ( nAddMapID != -1 )
	{
		ITexture* pBaseTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nAddMapID );
		if( pBaseTexture != NULL )
		{
			LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pBaseTexture->GetData();
			r->SetTexture( 1, pd3dTexture );
			if(0)
				D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, pd3dTexture, 0);
		}
		else
			r->SetTexture( 1, NULL );
	}

	if ( d3dBrightTex )
	{
		if (dwFlag & eShimmer)
			r->SetTexture( 2, d3dBrightTex );
		else
			r->SetTexture( 1, d3dBrightTex );
	}
	else if( nLightmapID != -1 )// lightmap
	{
		ITexture* pLMTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLightmapID );
		if( pLMTexture != NULL )
		{
			LPDIRECT3DTEXTURE9 pd3dTexture = (LPDIRECT3DTEXTURE9)pLMTexture->GetData();
			r->SetTexture( 1, pd3dTexture );
			if(0)
				D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, pd3dTexture, 0);
		}
		else
			r->SetTexture( 1, NULL );
	}
	else	
	{
		r->SetTexture( 1, NULL );
		//r->SetTexture( 2, NULL );
	}
	return true;
}

void RendererDx::SetRenderStatesWithFlag( DWORD dwFlag, DWORD dwFVF, int nMainMapID, int nAddMapID, int nLightmapID /*= -1*/ )
{
	m_dwSaveFlag = dwFlag;

	IRenderer* r = this;

	DWORD dwColorOp = D3DTOP_SELECTARG1;
	DWORD dwColorArg1 = D3DTA_TEXTURE;
	DWORD dwColorArg2 = D3DTA_DIFFUSE;
	DWORD dwAlphaOp = D3DTOP_DISABLE;
	DWORD dwAlphaArg1 = D3DTA_TEXTURE;
	DWORD dwAlphaArg2 = D3DTA_DIFFUSE;
	DWORD dwZEnable = TRUE;
	DWORD dwZWriteEnable = TRUE;
	DWORD dwCullMode = D3DCULL_NONE;

	DWORD dwAlphaBlendEnable = FALSE;
	//DWORD dwAlphaBlendEnable = TRUE;

	DWORD dwSrcBlend = D3DBLEND_SRCALPHA;
	DWORD dwDestBlend = D3DBLEND_INVSRCALPHA;
	DWORD dwFillMode = D3DFILL_SOLID;
	DWORD dwShadeMode = D3DSHADE_GOURAUD;
	DWORD dwZFun = D3DCMP_LESSEQUAL;
	DWORD dwAlphaTestEnable = FALSE;

	//DWORD dwAlphaRef = 0x00000080;
	DWORD dwAlphaRef = 0x00000080;

	DWORD dwAlphaFunc = D3DCMP_GREATER;
	DWORD dwMinFilter = D3DTEXF_LINEAR;
	DWORD dwMagFilter = D3DTEXF_LINEAR;

	// 	r->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	// 	r->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

	r->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	r->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	r->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );


	r->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	r->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	r->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	r->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	float fBias = -1.0f;

	switch( m_shSaveShaderID )
	{
	case OBJECT2D_SHADER:
		if( dwFlag & eAlphaBlend )
		{
			dwAlphaBlendEnable = TRUE;
			dwSrcBlend = D3DBLEND_SRCALPHA;
			dwDestBlend = D3DBLEND_INVSRCALPHA;
			dwCullMode = D3DCULL_NONE;
			dwColorOp = D3DTOP_MODULATE;
			dwColorArg1 = D3DTA_TEXTURE;
			dwColorArg2 = D3DTA_DIFFUSE;

			dwAlphaOp = D3DTOP_MODULATE;
			dwAlphaArg1 = D3DTA_TEXTURE;
			dwAlphaArg2 = D3DTA_DIFFUSE;
		}
		else
		{
			dwAlphaBlendEnable = FALSE;
		}
		if( dwFlag & eAlphaTest )
		{
			dwAlphaTestEnable = TRUE;
		}

		if( dwFlag & eZFunLess )
			dwZFun = D3DCMP_LESS;
		if( dwFlag & eLinearFilter )
		{
			dwMinFilter = D3DTEXF_LINEAR;
			dwMagFilter = D3DTEXF_LINEAR;
		}
		else
		{
			dwMinFilter = D3DTEXF_POINT;
			dwMagFilter = D3DTEXF_POINT;
		}

		dwColorOp = D3DTOP_MODULATE; 
		dwColorArg1 = D3DTA_TEXTURE;
		dwColorArg2 = D3DTA_DIFFUSE;

		if( dwFlag & eDstBlendOne )
			dwDestBlend =  D3DBLEND_ONE;
		dwFlag |= eNoMipmap;

		break;
	case TERRAIN_BLEND:
		dwZWriteEnable = false;
		dwAlphaBlendEnable = TRUE;
		// 		dwColorOp = D3DTOP_MODULATE2X;
		// 		dwColorArg1 = D3DTA_TEXTURE;
		// 		dwColorArg2 = D3DTA_DIFFUSE;
		dwAlphaOp = D3DTOP_MODULATE;
		dwAlphaArg1 = D3DTA_TEXTURE;
		dwAlphaArg2 = D3DTA_DIFFUSE;
		if ( dwFlag & eUClamp )
		{
			r->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
			r->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		}
		if ( dwFlag & eVClamp )
		{
			r->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
			r->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		}
		break;
	case MEX2_SHADER:
	case HELP_COLI_FLOOR:
	case MEX2_PARTICLE:

		if( dwFlag & eAlphaBlend || dwFlag & eAlphaTest )
		{
			dwSrcBlend = D3DBLEND_SRCALPHA;
			dwDestBlend = D3DBLEND_INVSRCALPHA;
			dwAlphaTestEnable = FALSE;
			dwAlphaBlendEnable = FALSE;
			dwAlphaOp = D3DTOP_MODULATE;
			if( dwFlag & eGlobalTransparent )
			{
				dwAlphaArg1 = D3DTA_TFACTOR;
				dwAlphaArg2 = D3DTA_TEXTURE;
			}
			else
			{
				dwAlphaArg1 = D3DTA_DIFFUSE;
				dwAlphaArg2 = D3DTA_TEXTURE;
			}
			if( dwFlag & eUseTextureColor )
			{
				dwColorOp = D3DTOP_MODULATE;
				dwColorArg1 = D3DTA_DIFFUSE;
				dwColorArg2 = D3DTA_TEXTURE;

				dwAlphaOp = D3DTOP_ADD;
				dwAlphaArg1 = D3DTA_TEXTURE;
				dwAlphaArg2 = D3DTA_DIFFUSE;
			}
			if ( dwFlag & eUClamp )
			{
				r->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
				r->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
			}
			if ( dwFlag & eVClamp )
			{
				r->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
				r->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
			}
		}
		else
		{
			dwAlphaBlendEnable = FALSE;
		}

		if( dwFlag & eAlphaTest )
		{
			dwAlphaTestEnable = TRUE;
			// commented out, jiayi, [2009.5.6]
			//dwAlphaBlendEnable = FALSE;
		}
		if( dwFlag & eAlphaBlend )
		{
			dwAlphaBlendEnable = TRUE;
			dwAlphaTestEnable = FALSE;//dwAlphaTestEnable也同时打开的话，物体会消失
		}

		dwColorOp = D3DTOP_MODULATE2X;
		if( dwFlag & eOpModulate1X )
			dwColorOp = D3DTOP_MODULATE;
		if( dwFlag & eOpModulate2X )
			dwColorOp = D3DTOP_MODULATE2X;
		if( dwFlag & eOpModulate4X )
			dwColorOp = D3DTOP_MODULATE4X;
		if( dwFlag & eOpAdd )
			dwColorOp = D3DTOP_ADD;

		if( dwFlag & eLightingDisable )
			dwColorOp = D3DTOP_MODULATE;

		dwColorArg1 = D3DTA_TEXTURE;
		dwColorArg2 = D3DTA_DIFFUSE;

		//if( dwFlag & eZWriteDisable )
		dwZWriteEnable = FALSE;

		dwCullMode = D3DCULL_CW;
		if( dwFlag & eCullCCW )
			dwCullMode = D3DCULL_CCW;
		else
			dwCullMode = D3DCULL_CW;

		if( dwFlag & eDstBlendOne )
			dwDestBlend =  D3DBLEND_ONE;

		break;
	case TERRAIN_SKYBOX:
		dwColorOp = D3DTOP_SELECTARG1; 
		dwColorArg1 =  D3DTA_TFACTOR;
		if( dwFlag & eUseTextureColor )
		{
			//dwColorOp = D3DTOP_ADD; 
			//dwColorArg1 = D3DTA_TEXTURE;
			//dwColorArg2 = D3DTA_DIFFUSE;

			dwAlphaBlendEnable = TRUE;
			dwSrcBlend = D3DBLEND_SRCALPHA;
			dwDestBlend = D3DBLEND_INVSRCALPHA;

			dwAlphaOp = D3DTOP_SELECTARG1;
			dwAlphaArg1 = D3DTA_DIFFUSE;

			if (nMainMapID != -1)
			{
				dwColorOp = D3DTOP_MODULATEALPHA_ADDCOLOR; 
				dwColorArg1 =  D3DTA_TFACTOR;
				dwColorArg2 =  D3DTA_TEXTURE;

				if( dwFlag & eAlphaBlend )
				{
					dwAlphaBlendEnable = TRUE;
					dwSrcBlend = D3DBLEND_SRCALPHA;
					dwDestBlend = D3DBLEND_INVSRCALPHA;

					dwColorOp = D3DTOP_SELECTARG2; 
					dwColorArg1 =  D3DTA_TFACTOR;
					dwColorArg2 =  D3DTA_TEXTURE;

					dwAlphaOp = D3DTOP_SELECTARG1;
					dwAlphaArg1 = D3DTA_TEXTURE;
				}
				if ( dwFlag & eOpAdd )
				{
					dwAlphaBlendEnable = TRUE;
					dwSrcBlend = D3DBLEND_ONE;
					dwDestBlend = D3DBLEND_ONE;
				}
			}
			else
			{
				dwColorOp = D3DTOP_MODULATE; 
				dwColorArg1 = D3DTA_TFACTOR;
				dwColorArg2 = D3DTA_DIFFUSE;
			}
		}
		else if( dwFlag & eAlphaBlend )
		{
			dwAlphaBlendEnable = TRUE;
			dwSrcBlend = D3DBLEND_SRCALPHA;
			dwDestBlend = D3DBLEND_INVSRCALPHA;

			dwAlphaOp = D3DTOP_SELECTARG1;
			dwAlphaArg1 = D3DTA_DIFFUSE;
		}
		else if( dwFlag & eOpAdd )
		{
			dwAlphaBlendEnable = TRUE;
			dwSrcBlend = D3DBLEND_SRCALPHA;
			dwDestBlend = D3DBLEND_ONE;


			//r->SetRenderState( D3DRS_STENCILMASK, 0xFFFFFF00 );
			//r->SetRenderState( D3DRS_STENCILWRITEMASK, 0xFFFF00FF );

			//dwAlphaOp = D3DTOP_BLENDFACTORALPHA;
			dwAlphaOp = D3DTOP_SELECTARG1;
			dwAlphaArg1 = D3DTA_DIFFUSE;
			//dwAlphaArg2 = D3DTA_SELECTMASK;
		}

		dwAlphaTestEnable = FALSE;
		break;
	}
	//render_direct:
	if( dwFlag & eZDisable )
		dwZEnable = FALSE;
	else
		dwZEnable = TRUE;

	if( dwFlag & eZWriteDisable ||
		dwAlphaBlendEnable == TRUE )
		dwZWriteEnable = FALSE;
	else
		dwZWriteEnable = TRUE;


	DWORD dwLighting = TRUE;

	if (graphics::ShaderManager::instance()->isRenderShadow())
	{
		dwZEnable = FALSE;
		dwZWriteEnable = FALSE;
		dwAlphaBlendEnable = FALSE;
		dwAlphaTestEnable = FALSE;
		dwLighting = FALSE;
		r->SetRenderState( D3DRS_FOGENABLE, FALSE );
	}
	else if (dwFlag & eRenderSkyBox)
	{
		dwZEnable = FALSE;
		dwZWriteEnable = FALSE;
		dwCullMode = D3DCULL_CW;
		r->SetRenderState( D3DRS_FOGENABLE, FALSE );
		// 		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	}
	if( dwFlag & eLightingDisable )
		dwLighting = FALSE;

	r->SetRenderState( D3DRS_LIGHTING, dwLighting );

	if( dwFlag & eSpecularEnable )
	{
		r->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL );
		r->SetRenderState( D3DRS_SPECULARENABLE,TRUE );
	}
	else
	{
		r->SetRenderState( D3DRS_SPECULARENABLE,FALSE );
		//	r->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR2 );
	}

	//
	r->SetRenderState( D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR2 );
	r->SetRenderState( D3DRS_ZENABLE, dwZEnable );
	r->SetRenderState( D3DRS_ZWRITEENABLE, dwZWriteEnable );
	r->SetRenderState( D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable );
	r->SetRenderState( D3DRS_SRCBLEND, dwSrcBlend );
	r->SetRenderState( D3DRS_DESTBLEND, dwDestBlend );

	r->SetTextureStageState( 0, D3DTSS_COLORARG1, dwColorArg1 );
	r->SetTextureStageState( 0, D3DTSS_COLORARG2, dwColorArg2 );
	r->SetTextureStageState( 0, D3DTSS_COLOROP, dwColorOp );

	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, dwAlphaArg1 );
	r->SetTextureStageState( 0, D3DTSS_ALPHAARG2, dwAlphaArg2 );
	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, dwAlphaOp );
	if( nAddMapID != -1 || nLightmapID != -1)
	{
		r->SetTextureStageState( 1, D3DTSS_COLORARG1, dwColorArg1 );
		r->SetTextureStageState( 1, D3DTSS_COLORARG2, dwColorArg2 );
		r->SetTextureStageState( 1, D3DTSS_COLOROP, dwColorOp );

		r->SetTextureStageState( 1, D3DTSS_ALPHAARG1, dwAlphaArg1 );
		r->SetTextureStageState( 1, D3DTSS_ALPHAARG2, dwAlphaArg2 );
		r->SetTextureStageState( 1, D3DTSS_ALPHAOP, dwAlphaOp );
	}	

	if( dwFVF != 0xffffffff )
		r->SetFVF( dwFVF );
	else 
		r->SetFVF( NULL );

	if( dwFlag & eTwoSided )
		r->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	else
		r->SetRenderState( D3DRS_CULLMODE, dwCullMode );

	if(graphics::ShaderManager::instance()->isUseOutline())
	{
		if(dwCullMode == D3DCULL_NONE)
		{

		}
		else if(dwCullMode == D3DCULL_CCW)
			r->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
		else 
			r->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	}


	r->SetRenderState( D3DRS_SHADEMODE, dwShadeMode );
	r->SetRenderState( D3DRS_FILLMODE, dwFillMode );
	r->SetRenderState( D3DRS_ZFUNC, dwZFun );

	r->SetRenderState( D3DRS_ALPHATESTENABLE, dwAlphaTestEnable );
	r->SetRenderState( D3DRS_ALPHAREF, dwAlphaRef );
	r->SetRenderState( D3DRS_ALPHAFUNC, dwAlphaFunc );

	r->SetSamplerState( 0, D3DSAMP_MINFILTER, dwMinFilter );
	r->SetSamplerState( 0, D3DSAMP_MAGFILTER, dwMagFilter );

	if( dwFlag & eNoMipmap )
		r->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );
	else
	{		
		fBias = GetMe3dConfig()->GetMipLodBais(); 

		//	FLOAT LodBias = -0.5f;
		r->SetSamplerState( 0, D3DSAMP_MIPMAPLODBIAS, *((DWORD*)&fBias) );
		r->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		if( nAddMapID != -1 || nLightmapID != -1 )
		{
			r->SetSamplerState( 1, D3DSAMP_MIPMAPLODBIAS, *((DWORD*)&fBias) );
			r->SetSamplerState( 1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		}
	}
	UINT uiMaxMipmap = GetEngine()->GetTextureManager()->GetGlobalMipmap();
	if( ( uiMaxMipmap == D3DX_FROM_FILE ) ||  ( dwFlag & eAlphaBlend ) )
		uiMaxMipmap = 0;
	r->SetSamplerState( 0, D3DSAMP_MAXMIPLEVEL, uiMaxMipmap );

	r->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL );

	r->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, GetMe3dConfig()->GetFullSceneAntialiasing() );

	if( ( dwFlag & eWireFrame ) || GetMe3dConfig()->m_bAlwayseWireFrameRendering )
		r->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
}


void RendererDx::SetTextureStageState( DWORD dwStage, DWORD dwType, DWORD dwValue )
{
	guardfunc;
	//CSALocker locker(this);

#ifdef USE_MANUAL_RS_MANAGED
	DeferredState.SetTextureStageState( dwStage, dwType, dwValue );
#else
	m_pDevice->SetTextureStageState( dwStage, (D3DTEXTURESTAGESTATETYPE) dwType, dwValue );
#endif
	unguard;
}
// void RendererDx::SetLOD2Color( float * color )
// {
// 	if (m_d3dTerrainEffect)
// 	{
// 		m_d3dTerrainEffect->SetValue( "LOD2Color", color, sizeof(D3DXCOLOR) );
// 	}
// }

void RendererDx::GetLight( int nLightID, D3DLIGHT9* pLight )
{
#ifdef USE_MANUAL_RS_MANAGED
	DeferredState.GetLight(nLightID, pLight);
#else
	m_pDevice->GetLight(nLightID, pLight);
#endif
}	
void RendererDx::SetLight( int nLightID, void* pLight )
{
	guardfunc;
    //CSALocker locker(this);

    // add [5/27/2008 whu]
    D3DLIGHT9 l = *(D3DLIGHT9*)pLight;
    //l.Ambient = D3DXCOLOR( l.Ambient ) * 0.8f;
    //l.Diffuse = D3DXCOLOR( l.Diffuse ) * 0.95f;

    m_lightDir[nLightID] = l.Direction;
    m_lightAmbient[nLightID] = l.Ambient;
	m_lightAmbient[nLightID] *= LIGHT_AMB_DIFF_SCALE;
    m_lightDiffuse[nLightID] = l.Diffuse;
	m_lightDiffuse[nLightID] *= LIGHT_AMB_DIFF_SCALE;
    m_lightSpecular[nLightID] = l.Specular;
	if (LIGHT_INDEX_TERRAIN == nLightID && m_d3dTerrainEffect)
	{
		m_d3dTerrainEffect->SetValue( "LightDirection", &m_lightDir[LIGHT_INDEX_TERRAIN], sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]) );
		m_d3dTerrainEffect->SetValue( "LightAmbientColor", &m_lightAmbient[LIGHT_INDEX_TERRAIN], sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]) );
		m_d3dTerrainEffect->SetValue( "LightDiffuseColor", &m_lightDiffuse[LIGHT_INDEX_TERRAIN], sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]) );
		m_d3dTerrainEffect->SetValue( "LightSpecularColor", &m_lightSpecular[LIGHT_INDEX_TERRAIN], sizeof(m_lightSpecular[LIGHT_INDEX_TERRAIN]) );
	}

#ifdef USE_MANUAL_RS_MANAGED
    DeferredState.SetLight( nLightID, &l );
#else
	m_pDevice->SetLight( nLightID, &l );
#endif

	unguard;
}

void RendererDx::LightEnable( int nLightID, BOOL bEnable )
{
	guardfunc;
	//CSALocker locker(this);

    m_bLighting = bEnable;

#ifdef USE_MANUAL_RS_MANAGED
    DeferredState.LightEnable( nLightID, bEnable );
#else
	m_pDevice->LightEnable( nLightID, bEnable );
#endif
	unguard;
}

// void RendererDx::Push( int nVertexCount, int nFaceCount, DWORD dwFlag )
// {
// 	guardfunc;
// 	//CSALocker locker(this);
// 	if( m_nSortedSurfaceCount >= eMaxSurface )
// 	{
// 		// 不能return，否则某些面就画不出来了
// 		//return;
// 		Flush( eSortByFarZ );
// 	}
// 
// 	CHRRenderSurface* pSurface = GetCurrentSurface();
// 	if( !pSurface )
// 	{
// 		assert( false );
// 		return;
// 	}
// 	pSurface->m_nVertexCount = nVertexCount;
// 	pSurface->m_nFaceCount = nFaceCount;
// 	assert( pSurface->m_nVertexStride > 0 );
// 	assert( pSurface->m_nVertexCount > 0 );
// 	pSurface->m_dwFlag = dwFlag;
// 	{
// 
// 
// 		// bring up, jiayi, [2009.4.28]
// 		BOOL bHasGlobalTransparent = FALSE;
// 		BOOL bHasGlobalDiffuse = FALSE;	
// 		float fTransparent = m_fGlobalTransparent;
// 		if( m_fGlobalTransparent < 1.0f )
// 		{
// 			bHasGlobalTransparent = TRUE;
// 			pSurface->m_dwFlag |= eAlphaBlend;
// 			pSurface->m_dwFlag |= eSortByFarZ;		
// 			if( (dwFlag & eRenderTreeLeaf) && m_fGlobalTransparent < 0.5f )
// 				fTransparent = 0.65f;		
// 
// 			//pSurface->m_dwFlag &= (~eAlphaTest);jiayi [09.04.01]
// 		}
// 
// 		if( pSurface->m_dwFlag & eSortByFarZ )
// 		{
// 			pSurface->m_pbyVertexBuffer = 
// 				m_RenderBuffers[1].AllocBuffer( pSurface->m_nVertexCount*pSurface->m_nVertexStride );
// 		}
// 		else 
// 		{
// 			pSurface->m_pbyVertexBuffer = 
// 				m_RenderBuffers[0].AllocBuffer( pSurface->m_nVertexCount*pSurface->m_nVertexStride );
// 		}
// 
// 		if( !pSurface->m_pbyVertexBuffer )
// 			return;
// 
// 		if( pSurface->m_dwFlag & eSortByFarZ )
// 		{
// 			pSurface->m_pbyIndicesBuffer = 
// 				m_RenderBuffers[1].AllocBuffer( pSurface->m_nFaceCount*sizeof(short)*3 );
// 		}
// 		else
// 		{
// 			pSurface->m_pbyIndicesBuffer = 
// 				m_RenderBuffers[0].AllocBuffer( pSurface->m_nFaceCount*sizeof(short)*3 );
// 		}
// 		if( !pSurface->m_pbyIndicesBuffer )
// 			return;
// 
// 		memcpy( pSurface->m_pbyIndicesBuffer, pSurface->m_pbyIndices, pSurface->m_nFaceCount*sizeof( short )*3 );
// 
// 		DWORD dwFVF = pSurface->m_dwFVF;
// 
// 		//bHasGlobalTransparent = FALSE;
// 		//pSurface->m_dwFlag |= eAlphaTest;
// 		//pSurface->m_dwFlag &= (~eAlphaBlend);
// 
// 
// 		if( m_fGlobalDiffuse[0] < 1.0f ||
// 			m_fGlobalDiffuse[1] < 1.0f ||
// 			m_fGlobalDiffuse[2] < 1.0f )
// 			bHasGlobalDiffuse = TRUE;
// 
// 		Pointer p;
// 		Pointer helper;
// 		p.byte = pSurface->m_pbyVertexBuffer;
// 		helper.byte = p.byte;
// 
// 		Pointer srcVertices;
// 		srcVertices.f = (float*)pSurface->m_pbyVertices;
// 		Pointer srcNormals;
// 		srcNormals.f = (float*)pSurface->m_pbyNormals;
// 
// 		Pointer srcDiffuse;
// 		srcDiffuse.dw = (DWORD*)pSurface->m_pbyDiffuse;
// 		Pointer srcUVs[CHRRenderSurface::eMaxLayer];
// 		srcUVs[0].f = (float*)pSurface->m_pbyUVs[0];
// 		srcUVs[1].f = (float*)pSurface->m_pbyUVs[1];
// 
// 		for( int i = 0; i < nVertexCount; i++ )
// 		{
// 			p.byte = helper.byte;
// 			if( dwFVF & D3DFVF_XYZ )
// 			{
// 				*p.f++ = *srcVertices.f++;
// 				*p.f++ = *srcVertices.f++;
// 				*p.f++ = *srcVertices.f++;
// 			}
// 			else if( dwFVF & D3DFVF_XYZRHW )
// 			{
// 				*p.f++ = *srcVertices.f++;
// 				*p.f++ = *srcVertices.f++;
// 				*p.f++ = *srcVertices.f++;
// 				*p.f++ = *srcVertices.f++;
// 			}
// 			if( dwFVF & D3DFVF_NORMAL )
// 			{
// 				*p.f++ = *srcNormals.f++;
// 				*p.f++ = *srcNormals.f++;
// 				*p.f++ = *srcNormals.f++;
// 			}
// 			if( dwFVF & D3DFVF_DIFFUSE )
// 			{
// 				DWORD color = 0xffffffff;
// 				if( srcDiffuse.dw )
// 				{
// 					color = *srcDiffuse.dw++;
// 				}
// 
// 				if( bHasGlobalTransparent )
// 				{
// 					DWORD a = (color&0xff000000)>>24;
// 					a = (DWORD)(a*fTransparent);
// 					color = a<<24|(color&0x00ffffff);
// 				}
// 
// 				if( bHasGlobalDiffuse )
// 				{
// 					DWORD r = (color&0x00ff0000)>>16;
// 					DWORD g = (color&0x0000ff00)>>8;
// 					DWORD b = (color&0x000000ff);
// 					r = (DWORD)(r*m_fGlobalDiffuse[0]);
// 					g = (DWORD)(g*m_fGlobalDiffuse[1]);
// 					b = (DWORD)(b*m_fGlobalDiffuse[2]);
// 					color = (color&0xff000000)|r<<16|g<<8|b;
// 				}
// 
// 				*p.dw++ = color;
// 			}
// 			if( dwFVF & D3DFVF_TEX1 )
// 			{
// 				*p.f++ = m_fGlobalUOffset[0]+(*srcUVs[0].f++);
// 				*p.f++ = m_fGlobalVOffset[0]+(*srcUVs[0].f++);
// 			}
// 			else if( dwFVF & D3DFVF_TEX2 )
// 			{
// 				*p.f++ = m_fGlobalUOffset[0]+(*srcUVs[0].f++);
// 				*p.f++ = m_fGlobalVOffset[0]+(*srcUVs[0].f++);
// 				if( srcUVs[1].f )
// 				{
// 					*p.f++ = m_fGlobalUOffset[1]+(*srcUVs[1].f++);
// 					*p.f++ = m_fGlobalVOffset[1]+(*srcUVs[1].f++);
// 				}
// 				else
// 				{
// 					*p.f++ = 0.0f;
// 					*p.f++ = 0.0f;
// 				}
// 
// 			}
// 			helper.byte +=pSurface->m_nVertexStride;
// 		}
// 	}
// 		
// 
// 	if( pSurface->m_dwFlag & eSortByFarZ )
// 	{
// 		m_SortedSurfaces[m_nSortedSurfaceCount++] = m_Surfaces[m_nSurfaceCount];
// 	}
// 	else
// 		m_nSurfaceCount++;
// 
// 	unguard;
// }


void RendererDx::Flush( DWORD dwFlag )
{
	guardfunc;
	//CSALocker locker(this);
	int nSurfaceCount = 0;
	CHRRenderSurface* pSurfaces = NULL;

    guard( flush.1 )
	if( dwFlag & eSortByFarZ )
	{
		nSurfaceCount = m_nSortedSurfaceCount;

		for( int i = 0; i < nSurfaceCount; i++ )
		{
			CHRRenderSurface* pSurface = &m_SortedSurfaces[i];

			//if( pSurface->m_bSortToView  )
			//	pSurface->SortToView( (float*)m_matView  );

			//if( pSurface->m_bSortToView  )
				pSurface->SortToView( m_vEyePt, m_vLookatPt );
		}

// 		qsort( m_SortedSurfaces, m_nSortedSurfaceCount, sizeof( CHRRenderSurface ) , CompareSurface );

		pSurfaces = m_SortedSurfaces;
	}
	else
	{
		nSurfaceCount = m_nSurfaceCount;
		pSurfaces = m_Surfaces;
	}
    unguard


    guard( flush.2 )
	for( int i = 0; i < nSurfaceCount; i++ )
	{
		if( i >= eMaxSurface )
            continue;

        CHRRenderSurface* pSurface = NULL;
        int nAddMapID = -1;

        pSurface = &pSurfaces[i];
		//assert( pSurface->m_nVertexCount > 0 );
		//assert( pSurface->m_nFaceCount > 0 );
		//assert( pSurface->m_nVertexStride > 0 );
		//assert( pSurface->m_dwFVF > 0 );
#ifdef USE_MANUAL_RS_MANAGED
        DeferredState.SetFVF( pSurface->m_dwFVF );
#else
		m_pDevice->SetFVF( pSurface->m_dwFVF );
#endif

        // add [5/27/2008 whu]
        D3DMATERIAL9* mtrl = &m_DefaultMaterial;

		if( pSurface->m_bHasSelfMtl )
		{
#ifdef USE_MANUAL_RS_MANAGED
            DeferredState.SetMaterial( &pSurface->m_mtrl );
#else
			m_pDevice->SetMaterial( &pSurface->m_mtrl );
#endif
			if( pSurface->m_bHasSpecular )
                dwFlag |= eSpecularEnable;

            // add [5/27/2008 whu]
            mtrl = &pSurface->m_mtrl;
		}
		else
		{
#ifdef USE_MANUAL_RS_MANAGED
            DeferredState.SetMaterial( &m_DefaultMaterial );
#else
            m_pDevice->SetMaterial( &m_DefaultMaterial );
#endif
        }

        m_ambient = mtrl->Ambient;
        m_diffuse = mtrl->Diffuse;

		if( pSurface->m_nLayerCount == 2 )
		{
			nAddMapID = pSurface->m_nTextureIds[1];
			if( pSurface->m_bHasSpecular )
				dwFlag |= eSpecularEnable;
		}

		if( pSurface->m_nShaderId == TERRAIN_SPLATTING )
			nAddMapID = pSurface->m_nTextureIds[1];

		if( pSurface->m_nVertexCount == 0 || pSurface->m_nFaceCount == 0 )
		{
			pSurface->Reset();
			continue;
		}



		//if( pSurface->m_nVertexStride == 28 )
		//{
		//	DirectPushSurface( 
		//		pSurface->m_nTextureIds[0],
		//		nAddMapID,
		//		pSurface->m_nShaderId,
		//		pSurface->m_dwFVF,
		//		pSurface->m_nVertexStride,
		//		pSurface->m_pbyVertexBuffer,
		//		pSurface->m_nVertexCount,
		//		pSurface->m_pbyIndicesBuffer,
		//		pSurface->m_nFaceCount,
		//		pSurface->m_dwFlag|dwFlag,
		//		m_dwPolyType, 0, 0, eDPST_UIVertex );
		//}
		//else
		//{
		//	DirectPushSurface( 
		//		pSurface->m_nTextureIds[0],
		//		nAddMapID,
		//		pSurface->m_nShaderId,
		//		pSurface->m_dwFVF,
		//		pSurface->m_nVertexStride,
		//		pSurface->m_pbyVertexBuffer,
		//		pSurface->m_nVertexCount,
		//		pSurface->m_pbyIndicesBuffer,
		//		pSurface->m_nFaceCount,
		//		pSurface->m_dwFlag|dwFlag,
		//		m_dwPolyType, 0 );
		//}


		//pSurface->Reset();


		//if( pSurface->m_nVertexStride == 36 )
		//{
		//	if( pSurface->m_pIB )
		//	{
		//		DirectPushSurface( 
		//			pSurface->m_nTextureIds[0],
		//			nAddMapID,
		//			pSurface->m_nShaderId,
		//			pSurface->m_dwFVF,
		//			pSurface->m_nVertexStride,
		//			pSurface->m_pbyVertexBuffer,
		//			pSurface->m_nVertexCount,
		//			(BYTE*)pSurface->m_pIB,
		//			pSurface->m_nFaceCount,
		//			pSurface->m_dwFlag|dwFlag,
		//			m_dwPolyType, 0, 0, eDPST_MexVertex );
		//	}

		//	//DirectPushSurface( 
		//	//	pSurface->m_nTextureIds[0],
		//	//	nAddMapID,
		//	//	pSurface->m_nShaderId,
		//	//	pSurface->m_dwFVF,
		//	//	pSurface->m_nVertexStride,
		//	//	pSurface->m_pbyVertexBuffer,
		//	//	pSurface->m_nVertexCount,
		//	//	pSurface->m_pbyIndicesBuffer,
		//	//	pSurface->m_nFaceCount,
		//	//	pSurface->m_dwFlag|dwFlag,
		//	//	m_dwPolyType, 0 );
		//}
		//else
		//{
		//	DirectPushSurface( 
		//		pSurface->m_nTextureIds[0],
		//		nAddMapID,
		//		pSurface->m_nShaderId,
		//		pSurface->m_dwFVF,
		//		pSurface->m_nVertexStride,
		//		pSurface->m_pbyVertexBuffer,
		//		pSurface->m_nVertexCount,
		//		pSurface->m_pbyIndicesBuffer,
		//		pSurface->m_nFaceCount,
		//		pSurface->m_dwFlag|dwFlag,
		//		m_dwPolyType, 0, 0, eDPST_UIVertex );
		//}


        // add [6/4/2008 whu]
        SetCurrentMaterial( pSurface->material );

		{
			DirectPushSurface( 
				pSurface->m_nTextureIds[0],
				nAddMapID,
				pSurface->m_nShaderId,
				pSurface->m_dwFVF,
				pSurface->m_nVertexStride,
				pSurface->m_pbyVertexBuffer,
				pSurface->m_nVertexCount,
				pSurface->m_pbyIndices,
				pSurface->m_nFaceCount,
				pSurface->m_dwFlag|dwFlag,
				m_dwPolyType, 0, 0, 0,
				pSurface->m_nTextureIds[2] );
		}

        SetCurrentMaterial( NULL );

        pSurface->Reset();
	}
    unguard

	if( dwFlag & eSortByFarZ )
	{
		m_nSortedSurfaceCount = 0;
// 		m_RenderBuffers[1].Clear();
	}
	else
	{
		m_nSurfaceCount = 0;
// 		m_RenderBuffers[0].Clear();
	}
	unguard;


	//guardfunc;
	////CSALocker locker(this);
	//int nSurfaceCount = 0;
	//CHRRenderSurface* pSurfaces = NULL;
	//if( dwFlag & eSortByFarZ )
	//{
	//	nSurfaceCount = m_nSortedSurfaceCount;

	//	for( int i = 0; i < nSurfaceCount; i++ )
	//	{
	//		CHRRenderSurface* pSurface = &m_SortedSurfaces[i];
	//		pSurface->SortToView( m_vEyePt, m_vLookatPt );
	//	}

	//	qsort( m_SortedSurfaces, m_nSortedSurfaceCount, sizeof( CHRRenderSurface ) , CompareSurface );

	//	pSurfaces = m_SortedSurfaces;
	//}
	//else
	//{
	//	nSurfaceCount = m_nSurfaceCount;
	//	pSurfaces = m_Surfaces;
	//}

	//for( int i = 0; i < nSurfaceCount; i++ )
	//{
	//	if( i >= eMaxSurface )
	//		continue;

	//	CHRRenderSurface* pSurface = &pSurfaces[i];
	//	assert( pSurface->m_nVertexCount > 0 );
	//	assert( pSurface->m_nFaceCount > 0 );
	//	assert( pSurface->m_nVertexStride > 0 );
	//	assert( pSurface->m_dwFVF > 0 );
	//	m_pDevice->SetFVF( pSurface->m_dwFVF );

	//	if( pSurface->m_bHasSelfMtl )
	//	{
	//		m_pDevice->SetMaterial( &pSurface->m_mtrl );
	//		if( pSurface->m_bHasSpecular )
	//			dwFlag |= eSpecularEnable;
	//	}
	//	else
	//	{
	//		m_pDevice->SetMaterial( &m_DefaultMaterial );
	//	}

	//	int nAddMapID = -1;
	//	if( pSurface->m_nLayerCount == 2 )
	//	{
	//		nAddMapID = pSurface->m_nTextureIds[1];
	//		if( pSurface->m_bHasSpecular )
	//			dwFlag |= eSpecularEnable;
	//	}
	//	if( pSurface->m_nShaderId == TERRAIN_SPLATTING )
	//		nAddMapID = pSurface->m_nTextureIds[1];

	//	if( pSurface->m_nVertexCount == 0 || pSurface->m_nFaceCount == 0 )
	//	{
	//		pSurface->Reset();
	//		continue;
	//	}


	//	if( pSurface->m_nVertexStride == 36 && pSurface->m_pIB )
	//	{
	//		if( pSurface->m_pIB )
	//		{
	//			DirectPushSurface( 
	//				pSurface->m_nTextureIds[0],
	//				nAddMapID,
	//				pSurface->m_nShaderId,
	//				pSurface->m_dwFVF,
	//				pSurface->m_nVertexStride,
	//				pSurface->m_pbyVertexBuffer,
	//				pSurface->m_nVertexCount,
	//				(BYTE*)pSurface->m_pIB,
	//				pSurface->m_nFaceCount,
	//				pSurface->m_dwFlag|dwFlag,
	//				m_dwPolyType, 0, 0, eDPST_MexVertex );
	//		}
	//	}
	//	else
	//	{
	//		DirectPushSurface( 
	//			pSurface->m_nTextureIds[0],
	//			nAddMapID,
	//			pSurface->m_nShaderId,
	//			pSurface->m_dwFVF,
	//			pSurface->m_nVertexStride,
	//			pSurface->m_pbyVertexBuffer,
	//			pSurface->m_nVertexCount,
	//			pSurface->m_pbyIndicesBuffer,
	//			pSurface->m_nFaceCount,
	//			pSurface->m_dwFlag|dwFlag,
	//			m_dwPolyType, 0, 0, eDPST_UIVertex );
	//	}

	//	pSurface->Reset();
	//}


	//if( dwFlag & eSortByFarZ )
	//{
	//	m_nSortedSurfaceCount = 0;
	//	m_RenderBuffers[1].Clear();
	//}
	//else
	//{
	//	m_nSurfaceCount = 0;
	//	m_RenderBuffers[0].Clear();
	//}
	//unguard;
}

void RendererDx::FlushShadow( DWORD dwFlag )
{
	guardfunc;
	//CSALocker locker(this);

	int nSurfaceCount = 0;
	CHRRenderSurface* pSurfaces = NULL;
	if( dwFlag & eSortByFarZ )
	{
		nSurfaceCount = m_nSortedSurfaceCount;

		for( int i = 0; i < nSurfaceCount; i++ )
		{
			CHRRenderSurface* pSurface = &m_SortedSurfaces[i];

			//if( pSurface->m_bSortToView  )
			//	pSurface->SortToView( (float*)m_matView  );

			//if( pSurface->m_bSortToView  )
			pSurface->SortToView( m_vEyePt, m_vLookatPt );
		}

// 		qsort( m_SortedSurfaces, m_nSortedSurfaceCount, sizeof( CHRRenderSurface ) , CompareSurface );

		pSurfaces = m_SortedSurfaces;
	}
	else
	{
		nSurfaceCount = m_nSurfaceCount;
		pSurfaces = m_Surfaces;
	}

	for( int i = 0; i < nSurfaceCount; i++ )
	{
		if( i >= eMaxSurface )
			continue;
		CHRRenderSurface* pSurface = &pSurfaces[i];
		assert( pSurface->m_nVertexCount > 0 );
		assert( pSurface->m_nFaceCount > 0 );
		assert( pSurface->m_nVertexStride > 0 );
		assert( pSurface->m_dwFVF > 0 );
#ifdef USE_MANUAL_RS_MANAGED
        DeferredState.SetFVF( pSurface->m_dwFVF );
#else
		m_pDevice->SetFVF( pSurface->m_dwFVF );
#endif

		//if( pSurface->m_bHasSelfMtl )
		//{
		//	m_pDevice->SetMaterial( &pSurface->m_mtrl );
		//	if( pSurface->m_bHasSpecular )
		//		dwFlag |= eSpecularEnable;
		//}
		//else
		//{
		//	m_pDevice->SetMaterial( &m_DefaultMaterial );
		//}

		dwFlag |= eNeedNotSetTexture;
		{
			DirectPushSurface( 
				-1,
				-1,
				pSurface->m_nShaderId,
				pSurface->m_dwFVF,
				pSurface->m_nVertexStride,
				pSurface->m_pbyVertexBuffer,
				pSurface->m_nVertexCount,
				pSurface->m_pbyIndices,
				pSurface->m_nFaceCount,
				pSurface->m_dwFlag|dwFlag,
				m_dwPolyType, 0 );
		}

		pSurface->Reset();
	}
	if( dwFlag & eSortByFarZ )
	{
		m_nSortedSurfaceCount = 0;
// 		m_RenderBuffers[1].Clear();
	}
	else
	{
		m_nSurfaceCount = 0;
// 		m_RenderBuffers[0].Clear();
	}
	unguard;
}

// namespace ModelRenderHelper
// {
// 	std::vector<IRenderer*>	m_HRRenderer;
// 
// 	VOID		Push( IRenderer*HRRenderer )
// 	{
// 		m_HRRenderer.push_back( HRRenderer );
// 	}
// 	
// 	VOID		ProcessRender()
// 	{
// 	}
// 
// 	VOID		Pop( )
// 	{
// 		m_HRRenderer.clear();
// 	}
// };

void RendererDx::DrawIndexedPrimitive( D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount )
{
	guardfunc;
	//CSALocker locker(this);
	m_shSaveShaderID = -1;
	m_dwSaveFlag = 0xffffffff;
	Commit();
	m_pDevice->DrawIndexedPrimitive( PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount );
	unguard;
}


void RendererDx::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
	guardfunc;
	//CSALocker locker(this);
	m_shSaveShaderID = -1;
	m_dwSaveFlag = 0xffffffff;
	Commit();
	m_pDevice->DrawPrimitiveUP( PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride );
	unguard;
}

void RendererDx::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,
							   UINT PrimitiveCount)
{
	guardfunc;
	//CSALocker locker(this);
	m_shSaveShaderID = -1;
	m_dwSaveFlag = 0xffffffff;
	m_pDevice->DrawPrimitive( PrimitiveType, StartVertex, PrimitiveCount);
	unguard;
}

extern VOID Lock3DMemory ();
extern VOID UnLockMemory ();
LONG RendererDx::CreateVertexBuffer( UINT Length,DWORD Usage,DWORD FVF,	DWORD Pool,VOID** ppVertexBuffer)
{
	guardfunc;
	//CSALocker locker(this);
	if(!m_pDevice)
		return S_FALSE;
	//();
	LONG rt = S_OK;
	rt = m_pDevice->CreateVertexBuffer( 
		Length, 
		Usage, FVF, (D3DPOOL)Pool, (IDirect3DVertexBuffer9**)ppVertexBuffer, NULL );

	return rt;
	unguard;
}

LONG RendererDx::CreateIndexBuffer( UINT Length,DWORD Usage, DWORD Format,DWORD Pool,VOID** ppIndexBuffer)
{
	guardfunc;
	//CSALocker locker(this);
	if( !m_pDevice )
		return S_FALSE;
	//();
	LONG rt = S_OK;
	
	rt =  m_pDevice->CreateIndexBuffer( 
					Length, 
					Usage, (D3DFORMAT)Format, 
					(D3DPOOL)Pool,
					(LPDIRECT3DINDEXBUFFER9*)ppIndexBuffer, NULL );

	return rt;
	unguard;
}


DWORD RendererDx::BeginScene()
{
	guardfunc;
	//CSALocker locker(this);
#ifdef USE_MANUAL_RS_MANAGED
    DeferredState.ClearFrame();
#endif
	return m_pDevice->BeginScene();
	unguard;
}

VOID  RendererDx::EndScene()
{
	guardfunc;
	//CSALocker locker(this);

	if (0)
	{
#ifdef USE_MANUAL_RS_MANAGED
		DeferredState.DumpCount();
#endif
	}
	m_pDevice->EndScene();
	//
	//RECT ViewportRect; 
	//SetRect( &ViewportRect, m_CurViewport.X, m_CurViewport.Y, 
	//	 m_CurViewport.X + m_CurViewport.Width,
	//	 m_CurViewport.Y + m_CurViewport.Height );
	//m_pDevice->Present( &ViewportRect, &ViewportRect, NULL, NULL );
	//m_pDevice->Present(  )
	unguard;
}

INT RendererDx::SetDynamicStream(DWORD Shader,FVertexStream* Stream)
{
	guard(FD3DRenderInterface::SetIndexBuffer);

	// If there isn't a dynamic vertex stream already, allocate one.
	if(!DynamicVertexStream)
		DynamicVertexStream = MeNew FD3DDynamicVertexStream(this);

	// Add the vertices in Stream to the dynamic vertex stream.
	INT	BaseVertexIndex = DynamicVertexStream->AddVertices(Stream),
		Stride = Stream->GetStride();

	// Set the dynamic vertex stream.
#ifdef USE_MANUAL_RS_MANAGED
    DeferredState.SetStreamSource(0, DynamicVertexStream->Direct3DVertexBuffer8, Stride);
#else
	m_pDevice->SetStreamSource(0, DynamicVertexStream->Direct3DVertexBuffer8, 0, Stride);
#endif

	CurrentState->Streams[0] = DynamicVertexStream;
	CurrentState->StreamStrides[0] = Stride;

	// Unset any additional old streams.
	for(INT StreamIndex = 1;StreamIndex < CurrentState->NumStreams;StreamIndex++)
	{
		CurrentState->Streams[StreamIndex] = NULL;
#ifdef USE_MANUAL_RS_MANAGED
        DeferredState.SetStreamSource(StreamIndex, NULL, 0);
#else
		m_pDevice->SetStreamSource(StreamIndex, NULL, 0, 0);
#endif
	}

	CurrentState->NumStreams = 1;

	CurrentState->dwFvF = Shader;

#ifdef USE_MANUAL_RS_MANAGED
    DeferredState.SetFVF( Shader );
#else
	m_pDevice->SetFVF( Shader );
#endif

	return BaseVertexIndex;

	unguard;
}

INT RendererDx::SetDynamicIndexBuffer(FIndexBuffer* IndexBuffer,INT BaseVertexIndex)
{
	guard(FD3DRenderInterface::SetDynamicIndexBuffer);

	// If there isn't a dynamic index buffer already, allocate one.
	FD3DDynamicIndexBuffer* DynamicIndexBuffer;
	if( IndexBuffer->GetIndexSize() == sizeof(DWORD) )
	{
		if(!DynamicIndexBuffer32)
			DynamicIndexBuffer32 = MeNew FD3DDynamicIndexBuffer(this,sizeof(DWORD));
		DynamicIndexBuffer = DynamicIndexBuffer32;
	}
	else
	{
		if(!DynamicIndexBuffer16)
			DynamicIndexBuffer16 = MeNew FD3DDynamicIndexBuffer(this,sizeof(WORD));
		DynamicIndexBuffer = DynamicIndexBuffer16;
	}

	// Add the indices in the index buffer to the dynamic index buffer.
	INT	BaseIndex = DynamicIndexBuffer->AddIndices(IndexBuffer);

	// Set the dynamic index buffer.
	CurrentState->IndexBuffer = DynamicIndexBuffer;
	CurrentState->IndexBufferBase = BaseVertexIndex;

#ifdef USE_MANUAL_RS_MANAGED
    DeferredState.SetIndices( DynamicIndexBuffer->Direct3DIndexBuffer8, BaseVertexIndex);
#else
	m_pDevice->SetIndices( DynamicIndexBuffer->Direct3DIndexBuffer8 );
#endif

	return BaseIndex;

	unguard;
}

DWORD RendererDx::Clear ( DWORD Count, DWORD Flags,DWORD Color,float Z,DWORD Stencil)
{
	guardfunc;
	//CSALocker locker(this);

	return m_pDevice->Clear( Count, NULL, Flags, Color, Z, Stencil );
	unguard;
}

DWORD RendererDx::SetViewport ( VOID* pViewport)
{
	guardfunc;
	//CSALocker locker(this);

	m_CurViewport = *(D3DVIEWPORT9*)pViewport;

	return m_pDevice->SetViewport( (D3DVIEWPORT9*)pViewport );
	unguard;
}

// add [5/28/2008 whu]
void RendererDx::SetShader(const std::string& name )
{
    m_shaderName = name;
    if ( m_shaderName == "Specular" )
    {
        m_pCurrentVS = m_pSpecularVS;
        m_pCurrentVSCT = m_pSpecularVSCT;
        m_pCurrentPS = m_pSpecularPS;
        m_pCurrentPSCT = m_pSpecularPSCT;
    }
    else if ( m_shaderName == "SpecularAndAnim" )
    {
        m_pCurrentVS = m_pSpecularVS;
        m_pCurrentVSCT = m_pSpecularVSCT;
        m_pCurrentPS = m_pSpecularAndAnimPS;
        m_pCurrentPSCT = m_pSpecularAndAnimPSCT;
    }
    else
    {
        m_pCurrentVS = NULL;
        m_pCurrentVSCT = NULL;
        m_pCurrentPS = NULL;
        m_pCurrentPSCT = NULL;
        m_bUseShader = false;
    }
}

void RendererDx::SetShaderParameter(const ShaderParameter& param, bool append )
{
    if ( append )
    {
#ifdef _DEBUG
        ShaderParameter::const_iterator it, end = param.end();
        for ( it = param.begin(); it != end; ++it )
        {
            assert( m_shaderParam.find( it->first ) == m_shaderParam.end() && 
                "The parameter already exist!" );
        }
#endif
        m_shaderParam.insert( param.begin(), param.end() );
    }
    else
    {
        m_shaderParam = param;
    }
}

// add [6/4/2008 whu]
void RendererDx::RestoreDeviceObjects(void* pDevice )
{
    guardfunc;
    m_pDevice = (LPDIRECT3DDEVICE9)pDevice; 
#ifdef USE_MANUAL_RS_MANAGED
    DeferredState.Init( this );
#endif
    m_pDevice->GetDeviceCaps(&DeviceCaps8);


// 	GetUIDecl();

    //
    // shader
    //
    graphics::ShaderManager::instance()->restoreDeviceObjects( m_pDevice );

    unguard;
}

void RendererDx::InvalidateDeviceObjects()
{
//     SAFE_RELEASE( m_pMexDecl );
//     SAFE_RELEASE( m_pUIDecl );
//     SAFE_RELEASE( m_pUIVB );
//     SAFE_RELEASE( m_pMexVB );
// 	SAFE_RELEASE( m_pUIIB );


// 	Mex2ParticleEmitter::destroyBuffers();
// 	Mex2RibbonEmitter::destroyBuffers();

    //
    // shader
    //
    graphics::ShaderManager::instance()->invalidateDeviceObjects();
}

void RendererDx::SetMaterial(graphics::Material* pMaterial )
{
    //CSALocker locker(this);
    GetCurrentSurface()->material = pMaterial;
}

void RendererDx::SetCurrentMaterial(graphics::Material* pMtrl )
{
    //CSALocker locker(this);
    m_pCurrentMaterial = pMtrl;
}


void RendererDx::RenderTerrainLOD2WithShader(UINT nStride, LPDIRECT3DVERTEXBUFFER9 pVertices, WORD nVertCount, LPDIRECT3DINDEXBUFFER9 pIndeices, WORD nTriangleCount)
{
	guardfunc;
	MeScopeProfileCommonFun;
	//TRUETIMEFUNC();
	//CSALocker locker(this);
	assert(m_pTerrainMaterial);
// 	graphics::Shader* pShader = m_pTerrainMaterial->getShader();
// 	graphics::ShaderEffect* effect = (graphics::ShaderEffect*)(pShader);
// 	IRenderer* r = this;
// 	//	PrepareTerrainShader();
// 	ID3DXEffect* d3dEffect = NULL;
// 	if ( effect && ( d3dEffect = effect->getID3DXEffect() ) )
	{
		LPDIRECT3DTEXTURE9 d3dTex = NULL;
		assert (pIndeices);

		m_pDevice->SetStreamSource(0, pVertices, 0, nStride);
 		if (m_LastTerrainIndexBuffer != pIndeices)
		{
			m_pDevice->SetIndices(pIndeices);
			m_LastTerrainIndexBuffer = pIndeices;
		}
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, nVertCount, 0, nTriangleCount);
	}
	unguard;
}

static short ssLastTexture0 = -1;
static short ssLastTexture1 = -1;
static short ssLastTexture2 = -1;
static short ssLastTexture3 = -1;

void RendererDx::RenderTerrainWithShader( short nBaseTextureID, short nTexture1, short nTexture2, short nTexture3, ITexture* maskTexture,
										 UINT nStride, LPDIRECT3DVERTEXBUFFER9 pVertices, WORD nVertCount, LPDIRECT3DINDEXBUFFER9 pIndeices, WORD nTriangleCount )
{
	guardfunc;
	MeScopeProfileCommonFun;
	//TRUETIMEFUNC();
	//CSALocker locker(this);
	assert(m_pTerrainMaterial);
	graphics::Shader* pShader = m_pTerrainMaterial->getShader();
	graphics::ShaderEffect* effect = (graphics::ShaderEffect*)(pShader);
	IRenderer* r = this;
	//	PrepareTerrainShader();
	ID3DXEffect* d3dEffect = NULL;
	if ( effect && ( d3dEffect = effect->getID3DXEffect() ) )
	{
		//set camera far plane
		LPDIRECT3DTEXTURE9 d3dTex = NULL;
		ITexture* pTexture = NULL;
		if (ssLastTexture0 != nBaseTextureID)
		{
			pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nBaseTextureID );
			if( pTexture )
			{
				d3dTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
			}
// 			m_pDevice->SetTexture(1,d3dTex);
			d3dEffect->SetTexture( "texture0Tex", d3dTex );
			ssLastTexture0 = nBaseTextureID;
		}
		if (ssLastTexture1 != nTexture1)
		{
			d3dTex = NULL;
			pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nTexture1 );
			if( pTexture )
			{
				d3dTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
			}
// 			m_pDevice->SetTexture(2,d3dTex);
			d3dEffect->SetTexture( "texture1Tex", d3dTex );
			ssLastTexture1 = nTexture1;
		}

		if (ssLastTexture2 != nTexture2)
		{
			d3dTex = NULL;
			pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nTexture2 );
			if( pTexture )
			{
				d3dTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
			}
// 			m_pDevice->SetTexture(3,d3dTex);
			d3dEffect->SetTexture( "texture2Tex", d3dTex );
			ssLastTexture2 = nTexture2;
		}

		if (ssLastTexture3 != nTexture3)
		{
			d3dTex = NULL;
			pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nTexture3 );
			if( pTexture )
			{
				d3dTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
			}
// 			m_pDevice->SetTexture(4,d3dTex);
			d3dEffect->SetTexture( "texture3Tex", d3dTex );
			ssLastTexture3 = nTexture3;
		}

		LPDIRECT3DTEXTURE9 d3dMaskTex = NULL;
		if( maskTexture )
		{
			d3dMaskTex = (LPDIRECT3DTEXTURE9)maskTexture->GetData();
		}
// 		m_pDevice->SetTexture(5,d3dTex);
		d3dEffect->SetTexture( "maskTex", d3dMaskTex );		


		m_pDevice->SetStreamSource(0, pVertices, 0, nStride);

 		if (m_LastTerrainIndexBuffer != pIndeices)
		{
			m_pDevice->SetIndices(pIndeices);
			m_LastTerrainIndexBuffer = pIndeices;
		}
		d3dEffect->CommitChanges() ;

// 		while ( pShader->beginPass() )
		{
			assert (pIndeices);
			{
				m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, nVertCount, 0, nTriangleCount);
			}

// 			pShader->endPass();
		}
	}
	unguard;

}

void RendererDx::RenderLiquidWithShader( short nLiquidTextureID, UINT nStride, BYTE *pVertices, WORD nVertCount, BYTE *pIndeices, WORD nTriangleCount)
{
	guardfunc;
	MeScopeProfileCommonFun;
	//TRUETIMEFUNC();
	//CSALocker locker(this);
// 	PrepareLiquidShader();
	assert(m_pTerrainMaterial);
	graphics::Shader* pShader = m_pTerrainMaterial->getShader();
	graphics::ShaderEffect* effect = (graphics::ShaderEffect*)(pShader);
	ID3DXEffect* d3dEffect = NULL;
	if ( effect && ( d3dEffect = effect->getID3DXEffect() ) )
	{
		LPDIRECT3DTEXTURE9 d3dTex = NULL;
		LPDIRECT3DTEXTURE9 d3dNormalTex = NULL;
		ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLiquidTextureID );
// 		ITexture* pNormalTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLiquidNormalID );
		if( pTexture )
		{
			d3dTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
		}
// 		if( pNormalTexture )
// 		{
// 			d3dNormalTex = (LPDIRECT3DTEXTURE9)pNormalTexture->GetData( );
// 		}
		d3dEffect->SetTexture( "texture0Tex", d3dTex );	
// 		d3dEffect->SetTexture( "g_waterNormalTex", d3dNormalTex );

		d3dEffect->CommitChanges() ;
// 		while ( pShader->beginPass() )
		{
			assert (pIndeices);
			{
				m_pDevice->DrawIndexedPrimitiveUP(
					D3DPT_TRIANGLESTRIP,
					0,
					nVertCount,
					nTriangleCount,
					pIndeices,
					D3DFMT_INDEX16,
					pVertices,
					nStride );
			}

// 			pShader->endPass();
		}

	}
	unguard;

}

void RendererDx::RenderLiquidWithShader_High(short nLiquidTextureID,
											 UINT nStride, BYTE *pVertices, WORD nVertCount, BYTE *pIndeices, WORD nTriangleCount)
{
	guardfunc;
	MeScopeProfileCommonFun;
	//TRUETIMEFUNC();
	//CSALocker locker(this);
	// 	PrepareLiquidShader();
	assert(m_pTerrainMaterial);
	graphics::Shader* pShader = m_pTerrainMaterial->getShader();
	graphics::ShaderEffect* effect = (graphics::ShaderEffect*)(pShader);
	ID3DXEffect* d3dEffect = NULL;
	if ( effect && ( d3dEffect = effect->getID3DXEffect() ) )
	{
 		LPDIRECT3DTEXTURE9 d3dTex = NULL;
 		//LPDIRECT3DTEXTURE9 d3dNormalTex = NULL;
		ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLiquidTextureID );
 		//ITexture* pNormalTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( nLiquidNormalID );
 		if( pTexture )
 		{
 			d3dTex = (LPDIRECT3DTEXTURE9)pTexture->GetData();
 		}
//  		if( pNormalTexture )
//  		{
//  			d3dNormalTex = (LPDIRECT3DTEXTURE9)pNormalTexture->GetData();
//  		}
		d3dEffect->SetTexture( "texture0Tex", d3dTex );
 		//d3dEffect->SetTexture( "g_waterNormalTex", d3dNormalTex );

		d3dEffect->CommitChanges() ;

// 		pShader->resetPassIndex();
// 		while ( pShader->beginPass() )
		{
			assert (pIndeices);
			{
				m_pDevice->DrawIndexedPrimitiveUP(
					D3DPT_TRIANGLESTRIP,
					0,
					nVertCount,
					nTriangleCount,
					pIndeices,
					D3DFMT_INDEX16,
					pVertices,
					nStride );
			}

// 			pShader->endPass();
		}

	}
	unguard;
}

struct WaveDef {
	float	fDirX;
	float	fDirY;
	float	fAmplitude;
	float	fFrequency;
	float	fPhase;
};

void RendererDx::SetTerrainMaterial( graphics::Material* val )
{
	m_pTerrainMaterial = val;
	assert(m_pTerrainMaterial);
	graphics::ShaderEffect* effect = (graphics::ShaderEffect*)m_pTerrainMaterial->getShader();
	m_d3dTerrainEffect = effect->getID3DXEffect();
	//set default value
// 	m_d3dTerrainEffect->SetMatrix( "world", &m_world );
// 	D3DXMATRIXA16 wvp = m_world * m_view * m_proj;
// 	D3DXMATRIXA16 wv = m_world * m_view;
// 	m_d3dTerrainEffect->SetMatrix( "worldViewProj", &wvp );
	m_d3dTerrainEffect->SetValue( "LightDirection", &m_lightDir[LIGHT_INDEX_TERRAIN], sizeof(m_lightDir[LIGHT_INDEX_TERRAIN]) );
	m_d3dTerrainEffect->SetValue( "LightAmbientColor", &m_lightAmbient[LIGHT_INDEX_TERRAIN], sizeof(m_lightAmbient[LIGHT_INDEX_TERRAIN]) );
	m_d3dTerrainEffect->SetValue( "LightDiffuseColor", &m_lightDiffuse[LIGHT_INDEX_TERRAIN], sizeof(m_lightDiffuse[LIGHT_INDEX_TERRAIN]) );
	m_d3dTerrainEffect->SetValue( "LightSpecularColor", &m_lightSpecular[LIGHT_INDEX_TERRAIN], sizeof(m_lightSpecular[LIGHT_INDEX_TERRAIN]) );

	// wave parameters
	WaveDef wave[3];
	wave[0].fDirX = 1.f;
	wave[0].fDirY = 0.f;
	wave[0].fAmplitude = 0.05f;
	wave[0].fFrequency = 1.f;
	wave[0].fPhase = 0.001f;

	wave[1].fDirX = -0.371391f;
	wave[1].fDirY = 0.928477f;
	wave[1].fAmplitude = 0.04f;
	wave[1].fFrequency = 0.8f;
	wave[1].fPhase = 0.0015f;

	wave[2].fDirX = 0.919145f;
	wave[2].fDirY = -0.393919f;
	wave[2].fAmplitude = 0.03f;
	wave[2].fFrequency = 0.7f;
	wave[2].fPhase = 0.0015f;
	m_d3dTerrainEffect->SetValue( "Wave", wave, 3 * sizeof( WaveDef ) );
	//m_d3dTerrainEffect->SetValue( "WaterColor_Deep", D3DXVECTOR3( 0.2f, 0.5f, 0.3f ), sizeof( D3DXVECTOR3 ) );
	//m_d3dTerrainEffect->SetValue( "WaterColor_Shallow", D3DXVECTOR3( 0.2f, 0.6f, 0.3f ), sizeof( D3DXVECTOR3 ) );
	//m_d3dTerrainEffect->SetVector( "WaterColor_Deep", &D3DXVECTOR4( 0.3f, 0.6f, 0.4f, 0.8f ) );
	//m_d3dTerrainEffect->SetVector( "WaterColor_Shallow", &D3DXVECTOR4( 0.2f, 0.3f, 0.3f, 0.2f ) );
}

// void RendererDx::PrepareModelShader()
// {
// 	graphics::Shader* pShader = graphics::ShaderManager::instance()->getShader("MexShader");
// 	assert( pShader && "mex shader missing" );
// 	graphics::ShaderEffect* pEffectShader = (graphics::ShaderEffect*)pShader;
// 	LPD3DXEFFECT d3dEffect = pEffectShader->getID3DXEffect();	
// 	d3dEffect->SetValue( "lightSpecular", &m_lightSpecular[LIGHT_INDEX_TERRAIN], sizeof(m_lightSpecular[LIGHT_INDEX_TERRAIN]) );
// }

void RendererDx::PrepareTerrainShader(bool bDepth)
{
	IRenderer* r = this;
	r->SetRenderState( D3DRS_ZENABLE, TRUE );
	r->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
	r->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	r->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
	r->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	r->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );

	r->SetTextureStageState( 1, D3DTSS_TEXCOORDINDEX, 1 );

	int nLayers = GetMe3dConfig()->GetTerrainRenderLayer();
	if (nLayers == 2)
	{
		float fBias = -0.5f;
		for (int i = 0; i < 2; ++i)
		{
			r->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
			r->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
			r->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			r->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			r->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
			r->SetSamplerState(i, D3DSAMP_MIPMAPLODBIAS, *((DWORD*)&fBias) );
		}
		r->SetSamplerState(2, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		r->SetSamplerState(2, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		r->SetSamplerState(2, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(2, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(2, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
	}
	else
	{
		r->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		r->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		float fBias = -0.5f;
		for (int i = 1; i < 5; ++i)
		{
			r->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
			r->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
			r->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			r->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			r->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
			r->SetSamplerState(i, D3DSAMP_MIPMAPLODBIAS, *((DWORD*)&fBias) );
		}
		r->SetSamplerState(5, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		r->SetSamplerState(5, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		r->SetSamplerState(5, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(5, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		r->SetSamplerState(5, D3DSAMP_MIPFILTER, D3DTEXF_NONE );
	}


	r->SetFVF( D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX5 );
	r->Commit();
	char pszTechName[50];
	sprintf_s( pszTechName, 50, "%s%d%s%s", "Terrain_", nLayers, "Layers", szShaderLevelName[1/*m_uiShaderLevel*/] );// modified,美术要求，永远计算diffuse [10/11/2010 zhangjiayi]
	
	if(bDepth) //游戏模式下使用 地形auto纹理映射 需要 shader mode 3.0 支持。
	sprintf_s( pszTechName, 50, "%s%d%s%s%s", "Terrain_", nLayers, "Layers", szShaderLevelName[1],"_30"  );

	if (m_RenderTLightMap)
	{
	sprintf_s( pszTechName, 50, "PosTexture"  );
	}

	
	m_LastTerrainIndexBuffer = NULL;
	ssLastTexture0 = -1;
	ssLastTexture1 = -1;
	ssLastTexture2 = -1;
	ssLastTexture3 = -1;
	//set technique
	InitTerrainTransform();
	graphics::Shader* pShader = m_pTerrainMaterial->getShader();
	pShader->setTechnique( pszTechName );
	pShader->begin( *m_pTerrainMaterial );
	graphics::ShaderEffect* effect = (graphics::ShaderEffect*)(pShader);
	MeCamera* pCamera = Config::GetCamera();
	ID3DXEffect* d3dEffect = effect->getID3DXEffect();
	if ( d3dEffect)
		d3dEffect->SetFloat( "g_FarPlane", pCamera->GetFarPlane() );

	pShader->resetPassIndex();
	pShader->beginPass();
}

void RendererDx::EndShader()
{
	graphics::Shader* pShader = m_pTerrainMaterial->getShader();
	pShader->endPass();
	pShader->end();
}

void RendererDx::EndLOD2Shader()
{
	graphics::Shader* pShader = m_pTerrainMaterial->getShader();
	pShader->endPass();
	pShader->end();
}

void RendererDx::PrepareTerrainLOD2Shader()
{
	IRenderer* r = this;
	// 	r->SetRenderState( D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR2 );
	// 	r->SetRenderState( D3DRS_ZENABLE, TRUE );
	// 	r->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	// 	r->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	// 	r->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	// 	r->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	// 
	// 	r->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	// 	r->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	// 	r->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE2X );
	// 
	// 	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	// 	r->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	// 	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE2X );

	// 	r->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );
	//	r->SetRenderState( D3DRS_SPECULARENABLE, TRUE);
	r->SetTextureStageState( 1, D3DTSS_TEXCOORDINDEX, 1 );
	r->SetFVF( D3DFVF_XYZ );
	r->Commit();
	m_LastTerrainIndexBuffer = NULL;
	//set technique
	InitTerrainTransform();
	graphics::Shader* pShader = m_pTerrainMaterial->getShader();
	pShader->setTechnique("LOD2_Terrain");
	pShader->begin( *m_pTerrainMaterial );
	pShader->beginPass( 0 );//只有一个pass
}

void RendererDx::PrepareLiquidShader()
{
	MeScopeProfileCommonFun;
	IRenderer* r = this;
	// 	r->SetRenderState( D3DRS_SPECULARMATERIALSOURCE, D3DMCS_COLOR2 );
	// 	r->SetRenderState( D3DRS_ZENABLE, TRUE );
	// 	r->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	// 	r->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	// 	r->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	// 	r->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	// 
	// 	r->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	// 	r->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	// 	r->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE2X );
	// 
	// 	r->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	// 	r->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	// 	r->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE2X );

	// 	r->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );
	//	r->SetRenderState( D3DRS_SPECULARENABLE, TRUE);
	r->SetTextureStageState( 1, D3DTSS_TEXCOORDINDEX, 1 );
	r->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1 );
	r->SetStreamSource( 0, NULL, 0 );
	r->SetIndices( NULL, 0 );	
	r->Commit();
	//set technique
	InitTerrainTransform();
	graphics::Shader* pShader = m_pTerrainMaterial->getShader();
	pShader->setTechnique("LiquidRender");
	//set parameters
	graphics::ShaderEffect* effect = (graphics::ShaderEffect*)(pShader);
	ID3DXEffect* d3dEffect = effect->getID3DXEffect();
	d3dEffect->SetFloat( "g_time", HQ_TimeGetTime() );
	d3dEffect->SetValue( "eye", &m_vEyePt, sizeof(D3DXVECTOR3) );

	pShader->begin( *m_pTerrainMaterial );
	pShader->resetPassIndex();
	pShader->beginPass();

}

void RendererDx::PrepareLiquidShader_High()
{
	MeScopeProfileCommonFun;
	IRenderer* r = this;
	r->SetTextureStageState( 1, D3DTSS_TEXCOORDINDEX, 1 );
	r->SetFVF( D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1 );
	r->SetStreamSource( 0, NULL, 0 );
	r->SetIndices( NULL, 0 );	
	r->Commit();
	InitTerrainTransform();
	//set technique
	graphics::Shader* pShader = m_pTerrainMaterial->getShader();
	pShader->setTechnique("LiquidRender_High");
	//set parameters
	CShaderMgr* ShaderMgr=GetShaderMgr();
	graphics::ShaderEffect* effect = (graphics::ShaderEffect*)(pShader);
	ID3DXEffect* d3dEffect = effect->getID3DXEffect();
	d3dEffect->SetTexture( "g_txReflect", ShaderMgr->m_pWaterRefTex);	
// 	d3dEffect->SetFloat( ShaderMgr->m_hFresnelPower, ShaderMgr->GetFresnelPower() );
// 	d3dEffect->SetFloat( ShaderMgr->m_hFresnelScale, ShaderMgr->GetFresnelScale() );
// 	d3dEffect->SetFloat( ShaderMgr->m_hWaterBlendWeight, ShaderMgr->GetWaterBlendWeight() );
// 	DWORD dwWaterColor = ShaderMgr->GetWaterColor();
// 	d3dEffect->SetVector( ShaderMgr->m_hWaterColor, &D3DXVECTOR4((float)((dwWaterColor>>16)&0xFF)/255.0f,(float)((dwWaterColor>>8)&0xFF)/255.0f,(float)(dwWaterColor&0xFF)/255.0f,1));

	if( ShaderMgr->m_pWaterNormalTex1 )
	{
		// get inverse world matrix
		D3DXMATRIX invWorld;
		D3DXMatrixIdentity(&invWorld);
		D3DXMatrixInverse( &invWorld, 0, &invWorld );
		d3dEffect->SetTexture( "g_waterNormalTex", ShaderMgr->m_pWaterNormalTex1 );
		d3dEffect->SetTexture( "g_waterNormalTex2", ShaderMgr->m_pWaterNormalTex2 );
		d3dEffect->SetMatrix( "g_invWorld", &invWorld );
	}
	
	d3dEffect->SetFloat( "g_time", HQ_TimeGetTime() );
	// 水面反光暂时不用，先注掉[QL]
	//d3dEffect->SetTexture( "g_txRefract", ShaderMgr->m_pWaterRefraTex);
	d3dEffect->SetValue( "eye", &m_vEyePt, sizeof(D3DXVECTOR3) );
	pShader->begin( *m_pTerrainMaterial );
	pShader->resetPassIndex();
	pShader->beginPass();
}

void RendererDx::SetGlobalTransparent( float t )
{
	guardfunc;
	//CSALocker locker(this);

	m_fGlobalTransparent = t;
	unguard;
}

void RendererDx::SetRenderState( DWORD dwState, DWORD dwValue )
{
	guardfunc;
	//CSALocker locker(this);
	
	/*
	DWORD oldVal;
	if (FAILED(m_pDevice->GetRenderState((D3DRENDERSTATETYPE) dwState, &oldVal)))
		return;

	if (oldVal == dwValue)
		return;
	*/

#ifdef USE_MANUAL_RS_MANAGED
    DeferredState.SetRenderState( (D3DRENDERSTATETYPE) dwState, dwValue );
#else
	m_pDevice->SetRenderState( (D3DRENDERSTATETYPE) dwState, dwValue );
#endif
	switch ( dwState )
	{
	case D3DRS_AMBIENT:
		{
			int i=0;

			// add [5/27/2008 whu]
			//D3DXCOLOR color( dwValue );
			//m_globalAmbient[0] = color.r;
			//m_globalAmbient[1] = color.g;
			//m_globalAmbient[2] = color.b;
			m_globalAmbient = dwValue;
			//m_globalAmbient *= 0.8f;
			//dwValue = m_globalAmbient;
		}
		break;
	case D3DRS_FOGCOLOR:
		{
#ifdef USE_MANUAL_RS_MANAGED
			DeferredState.SetFogColor( dwValue );		
#else
			m_pDevice->SetRenderState( D3DRS_FOGCOLOR, dwValue);
#endif
			if( m_pTerrainMaterial )
			{
				graphics::ShaderEffect* pEffectShader = (graphics::ShaderEffect*)m_pTerrainMaterial->getShader();
				LPD3DXEFFECT d3dEffect = pEffectShader->getID3DXEffect();	
				if ( d3dEffect )
				{
					D3DXCOLOR c(dwValue);
					d3dEffect->SetValue( "fogColor", &c, sizeof(D3DXCOLOR) );
				}
			}
		}
		break;
	case D3DRS_FOGSTART:
		{
#ifdef USE_MANUAL_RS_MANAGED
			DeferredState.SetFogNear( dwValue );
#else
			m_pDevice->SetRenderState( D3DRS_FOGSTART, dwValue);
#endif
			if( m_pTerrainMaterial )
			{
				graphics::ShaderEffect* pEffectShader = (graphics::ShaderEffect*)m_pTerrainMaterial->getShader();
				LPD3DXEFFECT d3dEffect = pEffectShader->getID3DXEffect();
				if ( d3dEffect )
				{
					float fValue = *(float*)&dwValue;
					d3dEffect->SetFloat( "fogStart", fValue );
				}
			}
			
		}
		break;
	case D3DRS_FOGEND:
		{
#ifdef USE_MANUAL_RS_MANAGED
			DeferredState.SetFogFar( dwValue );			
#else
			m_pDevice->SetRenderState( D3DRS_FOGEND, dwValue);
#endif
			if( m_pTerrainMaterial )
			{
				graphics::ShaderEffect* pEffectShader = (graphics::ShaderEffect*)m_pTerrainMaterial->getShader();
				LPD3DXEFFECT d3dEffect = pEffectShader->getID3DXEffect();	
				if ( d3dEffect )
				{
					float fValue = *(float*)&dwValue;
					d3dEffect->SetFloat( "fogEnd", fValue );
				}
			}
		}
		break;
	default:
		break;
	}
	unguard;
}

FEngineState::FEngineState()
{
	guardfunc;
	
	MaxActiveLights = 8;
	MaxPrimitiveCount = 655350;
	MaxVertexIndex = 65535;
	MaxStreams = 8;
	MaxStreamStride = 8;
	MaxVertexShaderConst = 4;
	VertexProcessingCaps = 8;
	VertexShaderVersion = 11;
	PixelShaderVersion = 11;

	MaxUserClipPlanes = 8;

	SupportsCubemaps = FALSE;
	UseDXT1 = TRUE;
	UseDXT3 = TRUE;
	UseDXT5 = TRUE;
	DetailTextures = TRUE;
	//MaxTextureAspectRatio = TRUE; s;	//Max aspect
	UseMippedCubemaps = FALSE;

	SupportsLodBiasing = TRUE;
	SupportsZBiasing = TRUE;
	SupportsAddsigned2x = FALSE;// D3DTOP_ADDSIGNED2X;
	SupportsDumpEnvmap = FALSE;
	SupportsBumpenvmapLuminance = FALSE; //UMPENVMAPLUMINANCE;

	MaxTextureWidth = 1024;
	MaxTextureHeight = 1024;


	UseTrilinear = FALSE;
	UseCubemaps = FALSE;

	SupportsDotProduct3 = FALSE;

	unguard;
}
#define Min(a, b) (((a) < (b)) ? (a): (b))
#define Max(a, b) (((a) > (b)) ? (a): (b))
VOID FEngineState::Init( VOID *pState )
{
	guardfunc;
	D3DCAPS9 DeviceCaps9 = *(D3DCAPS9*)pState;
	
	//DeviceCaps8
	
	MaxTextureBlendStages = DeviceCaps9.MaxTextureBlendStages;
	MaxSimultaneousTextures = DeviceCaps9.MaxSimultaneousTextures;

	MaxStreams = DeviceCaps9.MaxStreams;
	// Use software pipeline if less than 8 streams are exposed.
	if( DeviceCaps9.MaxStreams < 8 )
		UseHardwareTL = 0;

	// Software pipeline lies about caps.
	if( !(DeviceCaps9.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) )
	{
		DeviceCaps9.MaxStreams		= 16;
		DeviceCaps9.MaxActiveLights	= 8;
	}

	MaxActiveLights = DeviceCaps9.MaxActiveLights;
	MaxPrimitiveCount = DeviceCaps9.MaxPrimitiveCount;
	MaxVertexIndex = DeviceCaps9.MaxVertexIndex;
	MaxStreams = DeviceCaps9.MaxStreams;
	MaxStreamStride = DeviceCaps9.MaxStreamStride;

	MaxVertexShaderConst = DeviceCaps9.MaxVertexShaderConst;
	VertexProcessingCaps = DeviceCaps9.VertexProcessingCaps;
	VertexShaderVersion = ( (DeviceCaps9.VertexShaderVersion & 0xFF00) >> 8 ) *10 +
		DeviceCaps9.VertexShaderVersion & 0xFF;

	FLOAT fVer = (DeviceCaps9.VertexShaderVersion & 0xFF00) >> 8;
	fVer += (float)(DeviceCaps9.VertexShaderVersion & 0xFF)/10;

	PixelShaderVersion = DeviceCaps9.PixelShaderVersion;
	MaxUserClipPlanes = DeviceCaps9.MaxUserClipPlanes;

	// Calculate pixel shader version.
	PixelShaderVersion = ((DeviceCaps9.PixelShaderVersion & 0xFF00) >> 8) * 10 + DeviceCaps9.PixelShaderVersion & 0xFF;
	//PixelShaderVersion = Min(PixelShaderVersion,MaxPixelShaderVersion);

	// Check for cubemap support.
	if( DeviceCaps9.TextureCaps & D3DPTEXTURECAPS_CUBEMAP )
		SupportsCubemaps = UseCubemaps;
	else
		SupportsCubemaps = 0;

	// Check for mipped cubemap support.
	if( DeviceCaps9.TextureCaps & D3DPTEXTURECAPS_MIPCUBEMAP ) 
		UseMippedCubemaps = 1;
	else
		UseMippedCubemaps = 0;

	// Only used for debugging.
	FirstColoredMip = 0xFFFF;

	// Verify mipmapping supported.
	if
		(	!(DeviceCaps9.TextureFilterCaps & D3DPTFILTERCAPS_MIPFPOINT)
		&&	!(DeviceCaps9.TextureFilterCaps & D3DPTFILTERCAPS_MIPFLINEAR)
		)
	{
		UseMipmapping = 0;
	//	debugf(NAME_Init, TEXT("D3D Driver: Mipmapping not available with this driver"));
	}
	else
	{
		UseMipmapping = 1;
		if( DeviceCaps9.TextureFilterCaps & D3DPTFILTERCAPS_MIPFLINEAR )
		{
			UseTrilinear = TRUE;
		}
		else
			UseTrilinear = 0;
	}

	if( DeviceCaps9.TextureOpCaps & D3DTEXOPCAPS_BLENDDIFFUSEALPHA )
	{
		DetailTextures = TRUE;
	}
	else
		DetailTextures = 0;

	if( DeviceCaps9.TextureCaps & D3DPTEXTURECAPS_SQUAREONLY )
	{
		DeviceCaps9.MaxTextureAspectRatio = 1;
	}
	else if( !DeviceCaps9.MaxTextureAspectRatio )
	{
		DeviceCaps9.MaxTextureAspectRatio = Max(1,Max(DeviceCaps9.MaxTextureWidth,DeviceCaps9.MaxTextureHeight));
	}

	if( DeviceCaps9.RasterCaps & D3DPRASTERCAPS_MIPMAPLODBIAS )
	{
		SupportsLodBiasing = TRUE;
	}
	else
	{
		SupportsLodBiasing = FALSE;
	}

	//if( DeviceCaps9.RasterCaps & D3DPRASTERCAPS_ZBIAS )
	//{
	//	SupportsZBiasing = TRUE;
	//}
	//else
	//{
	//	SupportsZBiasing = FALSE;
	//}

	if( DeviceCaps9.TextureOpCaps & D3DTEXOPCAPS_ADDSIGNED2X )
	{
		SupportsAddsigned2x = TRUE;
	}
	else
	{
		SupportsAddsigned2x = FALSE;
	}

	if( DeviceCaps9.TextureOpCaps & D3DTEXOPCAPS_BUMPENVMAP )
	{
		SupportsDumpEnvmap = TRUE;
	}
	else
	{
		SupportsDumpEnvmap = FALSE;
	}

	if( DeviceCaps9.TextureOpCaps & D3DTEXOPCAPS_DOTPRODUCT3 )
	{
		//debugf( NAME_Init, TEXT("D3D Driver: Supports D3DTOP_DOTPRODUCT3") );
		SupportsDotProduct3 = TRUE;
	}
	else
	{
		SupportsDotProduct3 = FALSE;
	}



	unguard;
}

const char* RendererDx::GetCurrentShaderLevelName()
{
	return szShaderLevelName[m_uiShaderLevel];
}

// LPDIRECT3DINDEXBUFFER9 RendererDx::GetUiIB()
// {
// 	if (m_pUIIB == NULL)
// 	{
// 		HRESULT hr;
// 		while(1)
// 		{
// 			hr = m_pDevice->CreateIndexBuffer( 1024*8*6*sizeof(unsigned short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pUIIB, NULL );
// 			if( SUCCEEDED(hr) ) break;
// 		}
// 
// 		short* shIBFace = NULL;
// 		while(1)
// 		{
// 			hr = m_pUIIB->Lock( 0, 1024*8*6*sizeof(unsigned short), (void**)&shIBFace, D3DLOCK_NOSYSLOCK );
// 			if( SUCCEEDED(hr) ) break;
// 		}
// 
// 		for( int i = 0; i < 1024*8; i++ )
// 		{
// 			shIBFace[i*6+0] = i*4+0;
// 			shIBFace[i*6+1] = i*4+1;
// 			shIBFace[i*6+2] = i*4+2;
// 
// 			shIBFace[i*6+3] = i*4+3;
// 			shIBFace[i*6+4] = i*4+2;
// 			shIBFace[i*6+5] = i*4+1;
// 		}
// 
// 		while(1)
// 		{
// 			hr = m_pUIIB->Unlock();
// 			if( SUCCEEDED(hr) ) break;
// 		}
// 	}
// 	return m_pUIIB;
// }

// LPDIRECT3DVERTEXBUFFER9 RendererDx::GetUIVB()
// {
// 	if (m_pUIVB == NULL)
// 	{
// 		HRESULT hr;
// 		while(1)
// 		{
// 			hr = m_pDevice->CreateVertexBuffer( 2883540, D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_SYSTEMMEM, &m_pUIVB, NULL );
// 			if( SUCCEEDED(hr) ) break;
// 		}
// 	}
// 	return m_pUIVB;
// }

// LPDIRECT3DVERTEXBUFFER9 RendererDx::GetMexVB()
// {
// 	if (m_pMexVB == NULL)
// 	{
// 		HRESULT hr;
// 		while(1)
// 		{
// 			hr = m_pDevice->CreateVertexBuffer( 2883540, D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, 0, D3DPOOL_SYSTEMMEM, &m_pMexVB, NULL );
// 			if( SUCCEEDED(hr) ) break;
// 		}
// 	}
// 	return m_pMexVB;
// }

// LPDIRECT3DVERTEXDECLARATION9 RendererDx::GetMexDecl()
// {
// 	if (m_pMexDecl == NULL)
// 	{
// 		HRESULT hr;
// 		while(1)
// 		{
// 			hr = m_pDevice->CreateVertexDeclaration( MexDecl, &m_pMexDecl );
// 			if( SUCCEEDED(hr) ) break;
// 		}
// 	}
// 	return m_pMexDecl;
// }

// LPDIRECT3DVERTEXDECLARATION9 RendererDx::GetUIDecl()
// {
// 	if (m_pUIDecl == NULL)
// 	{
// 		HRESULT hr;
// 		while(1)
// 		{
// 			hr = m_pDevice->CreateVertexDeclaration( UIDecl, &m_pUIDecl );
// 			if( SUCCEEDED(hr) ) break;
// 		}
// 	}
// 	return m_pUIDecl;
// }