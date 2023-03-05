#include "Me3d/ShaderManager.h"
#include "Me3d/Shader.h"
#include "Me3d/Utility.h"
#include <cassert>
#include "Me3d/Model/MexAnimCtrl.h"
#include "Me3d/Material.h"
namespace graphics
{
#define SHADOW_MAP_SIZE 2048

    ShaderManager* ShaderManager::_pInst = NULL;

    ShaderManager::ShaderManager() : _pDevice(NULL),
        _bUseShader( true ), //_bUseOuterShader( false ),
		_pShadowMap(NULL), _pShadowSurf(NULL), _pShadowDepth(NULL), _bRenderShadow(false),
		_pRenderTarget(NULL), _pRenderTargetDepth(NULL), _bUseShadow(false), _bSupportSkeletonShader(true),_bOutline(false)
    {
    }

    ShaderManager::~ShaderManager()
    {
    }

    bool ShaderManager::supportVertexShader( unsigned int major, unsigned int minor ) const
    {
        D3DCAPS9 Caps;
        if( !_pDevice || FAILED( _pDevice->GetDeviceCaps( &Caps ) ) )
        {
            return false;
        }

        if( Caps.VertexShaderVersion >= D3DVS_VERSION( major, minor ) )
        {
            return true;
        }
        return false;
    }

    bool ShaderManager::supportPixelShader( unsigned int major, unsigned int minor ) const
    {
        D3DCAPS9 Caps;
        if( !_pDevice || FAILED( _pDevice->GetDeviceCaps( &Caps ) ) )
        {
            return false;
        }

        if( Caps.PixelShaderVersion >= D3DPS_VERSION( major, minor ) )
        {
            return true;
        }
        return false;
    }

    void ShaderManager::initialize( IDirect3DDevice9* pDevice )
    {
		_pDevice = pDevice;

		// Constant Float Register Equal to D3DCAPS9.MaxVertexShaderConst (at least 256 for vs_2_0). 
		_bSupportSkeletonShader = supportVertexShader(2, 0);
    }

    void ShaderManager::shutdown()
    {
        Shaders::iterator it, end = _shaders.end();
        for ( it = _shaders.begin(); it != end; ++it )
        {
            if ( it->second )
            {
                delete it->second;
            }
        }
		_shaders.clear();

		SafeRelease(_pShadowDepth);
		SafeRelease(_pShadowSurf);
		SafeRelease(_pShadowMap);
    }

    void ShaderManager::restoreDeviceObjects( IDirect3DDevice9* pDevice )
    {
		if( FAILED( pDevice->CreateTexture( SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, 1, D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_pShadowMap, NULL ) ) )
		{
			assert(0 && "FAILED Create ShadowMap");
			return;
		}

		_pShadowMap->GetSurfaceLevel( 0, &_pShadowSurf );

		if (FAILED(pDevice->CreateDepthStencilSurface(
			SHADOW_MAP_SIZE,
			SHADOW_MAP_SIZE,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0,
			TRUE,
			&_pShadowDepth,
			NULL)))
		{
			assert(0 && "FAILED 创建阴影stencil buffer");
		}

        Shaders::iterator it, end = _shaders.end();
        for ( it = _shaders.begin(); it != end; ++it )
        {
            it->second->restoreDeviceObjects( pDevice );
        }
    }

    void ShaderManager::invalidateDeviceObjects()
    {
        Shaders::iterator it, end = _shaders.end();
        for ( it = _shaders.begin(); it != end; ++it )
        {
            it->second->invalidateDeviceObjects();
        }

		SafeRelease(_pShadowDepth);
		SafeRelease(_pShadowSurf);
		SafeRelease(_pShadowMap);
    }

    void ShaderManager::addShader(Shader* pEffect )
    {
        assert( _shaders.find( pEffect->getName() ) == _shaders.end() );
		if( _shaders.find( pEffect->getName() ) != _shaders.end() )
			_shaders.erase( pEffect->getName() );
        _shaders.insert( Shaders::value_type( pEffect->getName(), pEffect ) );
    }

    Shader* ShaderManager::getShader(const std::string& name )
    {
        Shaders::iterator it = _shaders.find( name );
        if ( it == _shaders.end() )
        {
            return NULL;
        }
        return it->second;
    }

	void ShaderManager::beginRenderShadow(const D3DXVECTOR3& vEyeAt, const D3DXVECTOR3& vLookat,
		const D3DXVECTOR3& vViewDir, const D3DXVECTOR3& vLightDir)
	{
		if (_pShadowMap == NULL || _pDevice == NULL)
			return;

		// 保存渲染表面
		_pDevice->GetRenderTarget(0 , &_pRenderTarget);
		// 保存stencil buffer
		_pDevice->GetDepthStencilSurface(&_pRenderTargetDepth);					

		// 设置我们的贴图表面
		_pDevice->SetRenderTarget(0 , _pShadowSurf);
		// 设置stencil buffer
		_pDevice->SetDepthStencilSurface( _pShadowDepth );


		// 清空场景，渲染到贴图的背景是黑色的

		_pDevice->Clear( 0L, 0 ,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
			D3DCOLOR_ARGB(255,255,255,255), 1.0f, 0L );

		// Computee the world matrix
		D3DXMATRIX matWorld;
		D3DXMatrixIdentity( &matWorld );

		// Compute the view matrix
		D3DXMATRIX matView;

		// Compute the projection matrix
		D3DXMATRIX matProj;

		//D3DXVec3Normalize( &vViewDir, &(vLookat - vEyeAt) );
		D3DXVECTOR3 vAimDir = D3DXVECTOR3(  vViewDir.x, vViewDir.y, 0.0f );
		//D3DXVec3Normalize( &vAimDir, &vAimDir );

		float fSize = D3DXVec3Length(&(vLookat-vEyeAt));

		// View matrix
		// 						D3DXVECTOR3 vLight = g_World.m_lgtSun.Direction;
		D3DXVECTOR3 vLightPos	= vLookat - vLightDir * 40.f;
		D3DXVECTOR3 vLightAim	= vLookat;

		D3DXVec3Normalize( &vAimDir, &vAimDir );
		D3DXVECTOR3 vUp	= vAimDir;

		D3DXMatrixLookAtRH( &matView, &vLightPos, &vLightAim, &vUp );

		//   vEyeAt.z-vLookat.z+4;//(1-abs(vViewDir.z))*10+2;abs(vLookat.z-vEyeAt.z)+
		float fHeight = 120.f;
		// Compute the projection matrix
		static float fScale = 3;
		D3DXMatrixOrthoRH( &matProj, fSize*fScale, fSize*fScale, 0.f, fHeight );
		// 						FLOAT fAspect = ((FLOAT)SCREEN_WIDTH) / SCREEN_HEIGHT;//g_fCamerFOV
		//D3DXMatrixPerspectiveFovRH( &matProj, D3DXToRadian(45.0f), 1, 1.0f, 1024.0f );

		// Compute the light-view-projection matrix 
		D3DXMATRIX& mLightViewProj = _LightViewProjMatrix;// =matWorld * matView * matProj;
		D3DXMatrixMultiply( &mLightViewProj, &matView, &matProj );

		// Compute the texture matrix
		float fTexOffs = 0.5 + (0.5 / (float)SHADOW_MAP_SIZE);
		D3DXMATRIX matTexAdj( 0.5f,		0.0f,	0.0f,	0.0f,
			0.0f,    -0.5f,	0.0f,	0.0f,
			0.0f,		0.0f,	1.0f,	0.0f,
			fTexOffs, fTexOffs,  0.0f, 1.0f );

		_ShadowMapMatrix = mLightViewProj * matTexAdj;
		D3DXMATRIX& matTexture = _ShadowMapMatrix;		

		//////////////////////////////////////////////////////////////////////////
		// get object shader and set value
		graphics::ShaderEffect* pShaderEffect = (graphics::ShaderEffect*)getShader( "MexShader" );
		ID3DXEffect* pd3dEffect = 0;
		if( pShaderEffect )
		{
			pd3dEffect = pShaderEffect->getID3DXEffect();
			pd3dEffect->SetMatrix( "g_mLightViewProj", &mLightViewProj );
			pd3dEffect->SetMatrix( "g_matShadowTex", &matTexture );
		}					

		pShaderEffect = (graphics::ShaderEffect*)getShader( "TerrainBlender" );
		if( pShaderEffect )
		{
			pd3dEffect = pShaderEffect->getID3DXEffect();
			pd3dEffect->SetMatrix( "g_mLightViewProj", &mLightViewProj );
			pd3dEffect->SetMatrix( "g_matShadowTex", &matTexture );					
		}

		setRenderShadow(true);
	}

	void ShaderManager::endRenderShadow()
	{
		if (_pShadowMap == NULL || _pDevice == NULL)
			return;

		setRenderShadow(false);

		// 恢复渲染表面为显示器
		_pDevice->SetRenderTarget(0 , _pRenderTarget);
		_pDevice->SetDepthStencilSurface( _pRenderTargetDepth );
		SafeRelease(_pRenderTarget);
		SafeRelease(_pRenderTargetDepth);
	}

	void ShaderManager::enableShadow(bool enable)
	{
		if (_pShadowMap == NULL || _pDevice == NULL)
			return;

		_bUseShadow = enable;

		graphics::ShaderEffect* pShaderEffect = (graphics::ShaderEffect*)getShader( "MexShader" );
		ID3DXEffect* pd3dEffectObject = 0;
		ID3DXEffect* pd3dEffectTerrain = 0;

		if( pShaderEffect )
		{
			pd3dEffectObject = pShaderEffect->getID3DXEffect();						
			pd3dEffectObject->SetBool( "g_bRenderShadow", enable );
		}					

		pShaderEffect = (graphics::ShaderEffect*)getShader( "TerrainBlender" );
		if( pShaderEffect )
		{
			pd3dEffectTerrain = pShaderEffect->getID3DXEffect();						
			pd3dEffectTerrain->SetBool( "g_bRenderShadow", enable );
		}

		if( enable )//渲染阴影
		{
			//get object effect		
			pd3dEffectObject->SetTexture( "g_txShadowMap", _pShadowMap);
			pd3dEffectTerrain->SetTexture( "g_txShadowMap", _pShadowMap);				
		}
	}

	bool ShaderManager::LoadFxShader( const char* pRootPath )
	{
		try
		{
			if ( supportPixelShader(1, 0) )
			{
				char  filename[MAX_PATH] = {0};
				sprintf( filename, "%s\\DATA\\SHADER\\Particle.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pParticleVP = MeNew graphics::ShaderVertexPixel( "MexShaderParticle",
					_pDevice, filename, "Particle_vp", filename, "Particle_fp", "vs_1_1", "ps_1_0" );
				addShader( pParticleVP );
			}

			if ( supportPixelShader( 2, 0 ) )
			{
				char shaderfile[200];
				sprintf_s( shaderfile, "%s\\%s", pRootPath, "DATA\\SHADER\\Instancing.fxo" );
				MexInstanceMan::GlobalInitialize( shaderfile );

				char path[MAX_PATH*2];
				sprintf_s( path, "%s\\%s", pRootPath, "DATA\\SHADER\\TerrainBlender.fxo" );
				graphics::ShaderEffect* pLOD2_TerrainShader = MeNew graphics::ShaderEffect( "TerrainBlender",
					_pDevice, path );
				addShader( pLOD2_TerrainShader );
				IRenderer* r = GetEngine()->GetRenderer();
				r->EnableUseShader(true);
				static graphics::Material terrainMeterial;
				terrainMeterial.setShader("TerrainBlender");
				r->SetTerrainMaterial(&terrainMeterial);

				// diffuse shader.
				char  filename[MAX_PATH] = {0};
				sprintf( filename, "%s\\DATA\\SHADER\\RenderObject.fxo", pRootPath );
				graphics::ShaderEffect* pDiffuseShader = MeNew graphics::ShaderEffect( "MexShader",
					_pDevice, filename );
				pDiffuseShader->setTechnique( "Diffuse" );
				addShader( pDiffuseShader );

				sprintf( filename, "%s\\DATA\\SHADER\\Diffuse.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pDiffuseVP = MeNew graphics::ShaderVertexPixel( "MexShaderDiffuse",
					_pDevice, filename, "Diffuse_vp", filename, "Diffuse_fp" );
				addShader( pDiffuseVP );

				// with lightmap
				sprintf( filename, "%s\\DATA\\SHADER\\Diffuse.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pDiffuseLMVP = MeNew graphics::ShaderVertexPixel( "MexShaderDiffuseLM",
					_pDevice, filename, "DiffuseLM_vp", filename, "DiffuseLM_fp" );
				addShader( pDiffuseLMVP );

				sprintf( filename, "%s\\DATA\\SHADER\\Shimmer.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pShimmerVP = MeNew graphics::ShaderVertexPixel( "MexShaderShimmer",
					_pDevice, filename, "Shimmer_vp", filename, "Shimmer_fp" );
				addShader( pShimmerVP );

				sprintf( filename, "%s\\DATA\\SHADER\\Specular.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pSpecularVP = MeNew graphics::ShaderVertexPixel( "MexShaderSpecular",
					_pDevice, filename, "Specular_vp", filename, "Specular_fp" );
				addShader( pSpecularVP );

				sprintf( filename, "%s\\DATA\\SHADER\\NoLighting.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pNotLightingVP = MeNew graphics::ShaderVertexPixel( "MexShaderNoLighting",
					_pDevice, filename, "NoLighting_vp", filename, "NoLighting_fp" );
				addShader( pNotLightingVP );

				// with light map
				sprintf( filename, "%s\\DATA\\SHADER\\NoLighting.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pNotLightingLMVP = MeNew graphics::ShaderVertexPixel( "MexShaderNoLightingLM",
					_pDevice, filename, "NoLightingLM_vp", filename, "NoLightingLM_fp" );
				addShader( pNotLightingLMVP );

				sprintf( filename, "%s\\DATA\\SHADER\\AlphaTest.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pAlphaTestVP = MeNew graphics::ShaderVertexPixel( "MexShaderAlphaTest",
					_pDevice, filename, "AlphaTest_vp", filename, "AlphaTest_fp" );
				addShader( pAlphaTestVP );

				// with lightmap
				sprintf( filename, "%s\\DATA\\SHADER\\AlphaTest.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pAlphaTestLMVP = MeNew graphics::ShaderVertexPixel( "MexShaderAlphaTestLM",
					_pDevice, filename, "AlphaTestLM_vp", filename, "AlphaTestLM_fp" );
				addShader( pAlphaTestLMVP );

				sprintf( filename, "%s\\DATA\\SHADER\\SkyBox.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pSkyBoxVP = MeNew graphics::ShaderVertexPixel( "MexShaderSkyBox",
					_pDevice, filename, "SkyBox_vp", filename, "SkyBox_fp" );
				addShader( pSkyBoxVP );

				sprintf( filename, "%s\\DATA\\SHADER\\Collision.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pCollisionVP = MeNew graphics::ShaderVertexPixel( "MexShaderCollision",
					_pDevice, filename, "Collision_vp", filename, "Collision_fp" );
				addShader( pCollisionVP );

				sprintf( filename, "%s\\DATA\\SHADER\\Shadow.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pShadowVP = MeNew graphics::ShaderVertexPixel( "MexShaderShadow",
					_pDevice, filename, "Shadow_vp", filename, "Shadow_fp" );
				addShader( pShadowVP );

				sprintf( filename, "%s\\DATA\\SHADER\\SkeletonDiffuse.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pSkeletonDiffuseVP = MeNew graphics::ShaderVertexPixel( "MexShaderDiffuseSkeleton",
					_pDevice, filename, "SkeletonDiffuse_vp", filename, "SkeletonDiffuse_fp" );
				addShader( pSkeletonDiffuseVP );

				sprintf( filename, "%s\\DATA\\SHADER\\SkeletonShimmer.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pSkeletonShimmerVP = MeNew graphics::ShaderVertexPixel( "MexShaderShimmerSkeleton",
					_pDevice, filename, "SkeletonShimmer_vp", filename, "SkeletonShimmer_fp" );
				addShader( pSkeletonShimmerVP );

				sprintf( filename, "%s\\DATA\\SHADER\\SkeletonSpecular.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pSkeletonSpecularVP = MeNew graphics::ShaderVertexPixel( "MexShaderSpecularSkeleton",
					_pDevice, filename, "SkeletonSpecular_vp", filename, "SkeletonSpecular_fp" );
				addShader( pSkeletonSpecularVP );

				sprintf( filename, "%s\\DATA\\SHADER\\SkeletonEffect.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pSkeletonEffectVP = MeNew graphics::ShaderVertexPixel( "MexShaderEffectSkeleton",
					_pDevice, filename, "SkeletonEffect_vp", filename, "SkeletonEffect_fp" );
				addShader( pSkeletonEffectVP );

				sprintf( filename, "%s\\DATA\\SHADER\\SkeletonShadow.hlsl", pRootPath );
				graphics::ShaderVertexPixel* pSkeletonShadowVP = MeNew graphics::ShaderVertexPixel( "MexShaderShadowSkeleton",
					_pDevice, filename, "SkeletonShadow_vp", filename, "SkeletonShadow_fp" );
				addShader( pSkeletonShadowVP );

			}
			else
			{
				useShader( false );
			}
		}
		catch ( const std::exception& e )
		{
			/*
			 * Author:	2012-7-19 wangshuai
			 * Desc: 	加载Shader失败, 弹出MessageBox
			 */
			MessageBox(NULL, e.what(), "异常", MB_OK);
		}
		return true;
	}

	void ShaderManager::beginOutline()
	{
		if(!_pDevice)
			return;

		enableOutline(true);
	}

	void ShaderManager::endOutline()
	{
		enableOutline(false);
	}
}
