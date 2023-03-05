/********************************************************************
	created:	2008/05/20
	created:	20:5:2008   14:34
	filename: 	d:\work\whu\Sample\SimpleSample\PostProcessManager.cpp
	file path:	d:\work\whu\Sample\SimpleSample
	file base:	PostProcessManager
	file ext:	cpp
	author:		whu
	
	purpose:	全屏特效管理器。
*********************************************************************/

#include "Me3d/PostProcess/PostProcessManager.h"
#include "Me3d/PostProcess/PostProcess.h"
#include <exception>
#include <sstream>
#include <cassert>
#include "../filepacket/packet_interface.h"
//#include "Launcher/DataLauncher.h"
#include "Me3d/Engine/Engine.h"
#include "Me3d/Engine/TextureManager.h"
#include "Me3d/Engine/TextureManagerInstance.h"
// #include "Me3d/Me3d.h"
// #include "Me3d/Material.h"
// #include "Me3d/Engine/Renderer.h"
// #include "Me3d/Engine/MeRenderManager.h"

#ifndef STD_ThrowException
#define STD_ThrowException( error )                                 \
    std::stringstream __strTemp__;                                  \
    __strTemp__ << __FILE__ << "(" << __LINE__ << "): " << error;   \
    throw std::exception( __strTemp__.str().c_str() );
#endif

PostProcessManager* PostProcessManager::_instance = NULL;

PostProcessManager::PostProcessManager() : _pd3dDevice( NULL ),
    _pSceneRT( NULL ), _pSceneDS( NULL ), _pOldRT( NULL ), _pVertDecl( NULL ), _pEffect( NULL ),
    _screenWidth( 0 ), _screenHeight( 0 ),_pScenePositionRT(0), _pScenePositionRTSurface(0),
    _bInitialize( false ), _bEnabled( false ), _bEnableMultiRTs( false ),
    _pSceneRTSurface(0), _pCrossPostProcessingTexture( 0 ), _bOpenEx( false )
{
	_fOffsetBrightness = 0;
	_vOffsetContrast = D3DXVECTOR3( 1, 1, 1 );
	_pDefaultRenderTargetTempTexture = 0;
	_pDefaultRenderTargetTempSurface = 0;
	_pZPositionRenderTargetTempSurface = 0;
	_pZPositionRenderTargetTempTexture = 0;
}

PostProcessManager::~PostProcessManager()
{
}

void PostProcessManager::initialize( IDirect3DDevice9* pd3dDevice, LPCSTR szQuadEffectFilename, bool bOpenEx /*= false*/ )
{
    _pd3dDevice = pd3dDevice;
    _bInitialize = false;
	_bOpenEx = bOpenEx;

    D3DCAPS9 Caps;
    if( FAILED( _pd3dDevice->GetDeviceCaps( &Caps ) ) )
    {
        return;
    }

    // Check for vertex/pixel shaders 2.0 support
    if( Caps.VertexShaderVersion < D3DVS_VERSION( 2, 0 ) || Caps.PixelShaderVersion < D3DPS_VERSION( 2, 0 ) )
    {
        return;
    }

    // Create vertex declaration for post-process
    if( FAILED( _pd3dDevice->CreateVertexDeclaration( PostProcessEffect::QuadVertex::Decl, &_pVertDecl ) ) )
    {
        return;
    }

	// check for multi-rendertarget
	if( Caps.NumSimultaneousRTs > 1)	
		_enableMultiRenderTarget( true );	
	else
		_enableMultiRenderTarget( false );

    DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;
#ifdef DEBUG_VS
    dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
    dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	if (FAILED( D3DXCreateEffectFromFile( _pd3dDevice, szQuadEffectFilename, NULL, NULL, dwShaderFlags, 
		NULL, &_pEffect, NULL ) ) )
	{
// 		FILE	* fp = fopen(szQuadEffectFilename,"rb");
// 		if (!fp)
// 		{
// 			return;
// 		}
		char * pData=NULL;size_t nSize;
		nSize=packet_namespace::LoadFile(szQuadEffectFilename,pData,0);
		if(nSize<=0)
		{
			delete [] pData;
			return ;
		}
		if (FAILED( D3DXCreateEffect( _pd3dDevice, pData,nSize//fp->_ptr,fp->_bufsiz
			, NULL, NULL, dwShaderFlags, 
			NULL, &_pEffect, NULL ) ) )
		{
		//	fclose( fp );
			delete [] pData;
			return;
		}
		delete [] pData;
	//	fclose(fp);
	}

    _bInitialize = true;
}

void PostProcessManager::shutdown()
{
    Safe_Release( _pVertDecl );
    Safe_Release( _pEffect );
	Safe_Release( _pScenePositionRT );
	Safe_Release( _pScenePositionRTSurface );
	Safe_Release( _pSceneDS );

	Safe_Release( _pDefaultRenderTargetTempSurface );
	Safe_Release( _pDefaultRenderTargetTempTexture );
	Safe_Release( _pZPositionRenderTargetTempSurface);
	Safe_Release( _pZPositionRenderTargetTempTexture);

    PostProcessEffectMap::iterator it = _postProcessEffectMap.begin(),
        end = _postProcessEffectMap.end();
    for ( ; it != end; ++it )
    {
        it->second->destroy();
        delete it->second;
    }

	_postProcessEffectMap.clear();

    _bInitialize = false;
    _bEnabled = false;
	_enableMultiRenderTarget( false );
	_pd3dDevice = NULL;
}

void PostProcessManager::restoreDeviceObjects(IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight )
{
    if ( !_bInitialize )
    {
        return;
    }

    assert( _pEffect && "don't call initialize." );

    _pd3dDevice = pd3dDevice;
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

    try
    {
        // Create scene save texture
        if( FAILED( pd3dDevice->CreateTexture( (unsigned int)screenWidth,
            (unsigned int)screenHeight,
            1,
            D3DUSAGE_RENDERTARGET,
            D3DFMT_A8R8G8B8,
            D3DPOOL_DEFAULT,
            &_pSceneRT,
            NULL ) ) )
        {
            STD_ThrowException( "Failed to CreateTexture." );
        }
		_pSceneRT->GetSurfaceLevel( 0 , &_pSceneRTSurface );

		if( _bOpenEx )
		{
			if( FAILED( pd3dDevice->CreateTexture( (unsigned int)screenWidth,
				(unsigned int)screenHeight,
				1,
				D3DUSAGE_RENDERTARGET,
				D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT,
				&_pDefaultRenderTargetTempTexture,
				NULL ) ) )
			{
				STD_ThrowException( "Failed to Create default rt tex." );
			}
			_pDefaultRenderTargetTempTexture->GetSurfaceLevel( 0, &_pDefaultRenderTargetTempSurface );		
		}		

#ifdef RENDER_MRT
		// 是否支持multi-rt
		if( _bEnableMultiRTs )
		{
			// create scene position info texture

			if( FAILED( pd3dDevice->CreateTexture( (unsigned int)screenWidth,
				(unsigned int)screenHeight,
				1,
				D3DUSAGE_RENDERTARGET,
				D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT,
				&_pScenePositionRT,
				NULL ) ) )
			{
				STD_ThrowException( "Failed to CreateTexture." );
			}
			_pScenePositionRT->GetSurfaceLevel( 0, &_pScenePositionRTSurface );

			if( FAILED( pd3dDevice->CreateTexture( (unsigned int)screenWidth,
				(unsigned int)screenHeight,
				1,
				D3DUSAGE_RENDERTARGET,
				D3DFMT_A8R8G8B8,
				D3DPOOL_DEFAULT,
				&_pZPositionRenderTargetTempTexture,
				NULL ) ) )
			{
				STD_ThrowException( "Failed to Create default rt tex." );
			}
			_pZPositionRenderTargetTempTexture->GetSurfaceLevel( 0, &_pZPositionRenderTargetTempSurface );

		}
#endif // RENDER_MRT

        if (FAILED( pd3dDevice->CreateDepthStencilSurface( (unsigned int)screenWidth,
            (unsigned int)screenHeight,
            D3DFMT_D16,
            D3DMULTISAMPLE_NONE,
            0,
            TRUE,
            &_pSceneDS,
            NULL
            ) ) )
        {
            STD_ThrowException( "Failed to CreateDepthStencilSurface." );
        }

        PostProcessEffectMap::iterator it = _postProcessEffectMap.begin(),
            end = _postProcessEffectMap.end();

        for ( ; it != end; ++it )
        {
#ifdef RENDER_MRT
			if( !_bEnableMultiRTs && it->second->needMultiRenderTarget() )
				continue;
#endif //RENDER_MRT

            it->second->restoreDeviceObjects( pd3dDevice, screenWidth, screenHeight );
        }

        if ( _pEffect )
        {
            _pEffect->OnResetDevice();
        }
    }
    catch( const std::exception& e )
    {
        OutputDebugString( e.what() );
    }
}

void PostProcessManager::invalidateDeviceObjects()
{
    if ( !_bInitialize )
    {
        return;
    }

    assert( _pEffect && "don't call initialize." );

    _pd3dDevice = NULL;

    PostProcessEffectMap::iterator it = _postProcessEffectMap.begin(),
        end = _postProcessEffectMap.end();
    for ( ; it != end; ++it )
    {
        it->second->invalidateDeviceObjects();
    }

    if ( _pEffect )
    {
        _pEffect->OnLostDevice();
    }

    Safe_Release( _pSceneDS );
    Safe_Release( _pSceneRT );
	Safe_Release( _pSceneRTSurface );
	Safe_Release( _pScenePositionRT );
	Safe_Release( _pScenePositionRTSurface );

	Safe_Release( _pDefaultRenderTargetTempSurface );
	Safe_Release( _pDefaultRenderTargetTempTexture );
	Safe_Release( _pZPositionRenderTargetTempSurface);
	Safe_Release( _pZPositionRenderTargetTempTexture);
}

void PostProcessManager::addPostProcessEffect(PostProcessEffect* pEffect )
{
    assert( pEffect && _postProcessEffectMap.find( pEffect->getName() ) == _postProcessEffectMap.end() );
    if ( _postProcessEffectMap.find( pEffect->getName() ) != _postProcessEffectMap.end() )
    {
        throw std::exception( "pEffect already exist in PostProcessManager." );
    }
    _postProcessEffectMap.insert( PostProcessEffectMap::value_type( pEffect->getName(), pEffect ) );
}

void PostProcessManager::removePostProcessEffect(const std::string& name )
{
    PostProcessEffectMap::iterator it = _postProcessEffectMap.find( name );
    if ( it != _postProcessEffectMap.end() )
    {
        it->second->destroy();
        delete it->second;
        _postProcessEffectMap.erase( it );
    }
}

void PostProcessManager::setParameter(const std::string &paramName, const D3DXVECTOR2 &value)
{
	if( !_bEnabled )
		return;

	D3DXVECTOR4 value4( value.x, value.y, 1.f, 1.f );
	setParameter( paramName, value4 );
}

void PostProcessManager::setParameter(const std::string &paramName, const D3DXVECTOR3 &value)
{
	if( !_bEnabled )
		return;

	D3DXVECTOR4 value4( value.x, value.y, value.z, 1.f );
	setParameter( paramName, value4 );
}
void PostProcessManager::setParameter(const std::string &paramName, const D3DXVECTOR4 &value)
{
	if( !_bEnabled )
		return;

    PostProcessEffectMap::iterator it = _postProcessEffectMap.begin(),
        end = _postProcessEffectMap.end();
    for ( ; it != end; ++it )
    {
        it->second->setParameter( paramName, value );
    }
}

void PostProcessManager::setParameter(const std::string &paramName, const D3DXMATRIXA16 &value)
{
	if( !_bEnabled )
		return;

	PostProcessEffectMap::iterator it = _postProcessEffectMap.begin(),
		end = _postProcessEffectMap.end();
	for ( ; it != end; ++it )
	{
		it->second->setParameter( paramName, value );
	}
}

D3DXVECTOR4* PostProcessManager::getParameterVector4( const std::string& paramName ) const
{
	if( !_bEnabled )
		return NULL;

	PostProcessEffectMap::const_iterator it = _postProcessEffectMap.begin(),
		end = _postProcessEffectMap.end();
	D3DXVECTOR4* pRetValue = NULL;
	for ( ; it != end; ++it )
	{
		pRetValue = it->second->getParameterVector4( paramName );
		if( pRetValue )
			return pRetValue;
	}
	return NULL;
}
D3DXMATRIXA16* PostProcessManager::getParameterMatrix16( const std::string& paramName ) const
{
	if( !_bEnabled )
		return NULL;

	PostProcessEffectMap::const_iterator it = _postProcessEffectMap.begin(),
		end = _postProcessEffectMap.end();
	D3DXMATRIXA16* pRetValue = NULL;
	for ( ; it != end; ++it )
	{
		pRetValue = it->second->getParameterMatrix16( paramName );
		if( pRetValue )
			return pRetValue;
	}
	return NULL;
}

void PostProcessManager::updateRenderTargetToEffect()
{
	if( !_bEnabled )
		return;

	PostProcessEffectMap::iterator it = _postProcessEffectMap.begin(),
		end = _postProcessEffectMap.end();
	for ( ; it != end; ++it )
	{
		it->second->updateRenderTargetToEffect();
	}
}

void PostProcessManager::updateMultiRenderTarget()
{
	if( _bEnabled && _bEnableMultiRTs )
	{
		_pd3dDevice->SetRenderTarget( 1, _pScenePositionRTSurface );
	}
}

void PostProcessManager::_enableMultiRenderTarget( bool bEnableMultiRTs )
{
	_bEnableMultiRTs = bEnableMultiRTs;
}

void PostProcessManager::_preRenderTargetUpdate()
{
//    HRESULT hr;

//     _pd3dDevice->GetRenderTarget( 0, &_pOldRT );
// 
//     IDirect3DSurface9* pRT;
//     _pSceneRT->GetSurfaceLevel( 0, &pRT );
//     hr = _pd3dDevice->StretchRect( _pOldRT, NULL, pRT, NULL, D3DTEXF_LINEAR );
//     assert( hr == S_OK );
//     //_pd3dDevice->SetRenderTarget( 0, pRT );
//     Safe_Release( pRT );
// 	Safe_Release( _pOldRT )

    PostProcessEffectMap::iterator it = _postProcessEffectMap.begin(),
        end = _postProcessEffectMap.end();
    for ( ; it != end; ++it )
    {
#ifdef RENDER_MRT
		if( it->second->needMultiRenderTarget() && !_bEnableMultiRTs )
			it->second->enable( false );
#endif // RENDER_MRT

        it->second->preRenderTargetUpdate();
    }
}

void PostProcessManager::_renderQuad(IDirect3DTexture9* tex)
{
    // Restore old render target 0 (back buffer)
    _pd3dDevice->SetRenderTarget( 0, _pOldRT );
    Safe_Release( _pOldRT );

    //
    // Get the final result image onto the back buffer
    //
    if( SUCCEEDED( _pd3dDevice->BeginScene() ) )
    {
        //
        // Set up our quad
        //
        PostProcessEffect::QuadVertex Quad[4] =
        {
            { -0.5f,             -0.5f,              1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
            { _screenWidth-0.5f, -0.5,               1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },
            { -0.5,              _screenHeight-0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f },
            { _screenWidth-0.5f, _screenHeight-0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }
        };

        IDirect3DTexture9 *pFinalTarget = _pSceneRT;
        if ( !_postProcessEffectMap.empty() )
        {
            pFinalTarget = tex;
        }

        _pd3dDevice->SetVertexDeclaration( _pVertDecl );

		if( GetCrossPostPrcessingTexture() )
		{
			_pEffect->SetTechnique( "RenderQuad_Cross" );
			_pEffect->SetTexture( "crossTexture", _pCrossPostProcessingTexture );
		}
		else
		{ _pEffect->SetTechnique( "RenderQuad" ); }
        _pEffect->SetTexture( "baseTexture", pFinalTarget );
		_pEffect->SetFloat( "offsetContrastR", _vOffsetContrast.x );
		_pEffect->SetFloat( "offsetContrastG", _vOffsetContrast.y );
		_pEffect->SetFloat( "offsetContrastB", _vOffsetContrast.z );
		_pEffect->SetFloat( "offsetBrightness", _fOffsetBrightness );
		

        // Apply the technique contained in the effect 
        unsigned int cPasses;
        _pEffect->Begin( &cPasses, 0 );

        for ( unsigned int iPass = 0; iPass < cPasses; iPass++ )
        {
            _pEffect->BeginPass( iPass );

            _pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, Quad, sizeof(PostProcessEffect::QuadVertex) );

            _pEffect->EndPass();
        }
        _pEffect->End();

		_pd3dDevice->EndScene();

		//_pd3dDevice->SetVertexDeclaration( NULL );
    }
}

void PostProcessManager::ScretchRectToTexture( bool bDelTarget /* = true */ )
{
	_pd3dDevice->GetRenderTarget( 0, &_pOldRT );
	IDirect3DSurface9* pRT;
	_pSceneRT->GetSurfaceLevel( 0, &pRT );
	HRESULT hr = _pd3dDevice->StretchRect( _pOldRT, NULL, pRT, NULL, D3DTEXF_LINEAR );
	assert( hr == S_OK );
	Safe_Release( pRT );
	if( bDelTarget )
		Safe_Release( _pOldRT );
}

PostProcessEffect* PostProcessManager::GetPostProcessEffect(const char* pString)
{
	if (!pString)
	{
		return NULL;
	}
	PostProcessEffectMap::iterator itr = _postProcessEffectMap.find(pString);
	if (itr == _postProcessEffectMap.end())
	{
		return NULL;
	}
	return itr->second;
}

void PostProcessManager::render()
{
    if ( !_bInitialize || !_bEnabled )
    {
        return;
    }

    // 更新RenderTarget用于Post Process。
    _preRenderTargetUpdate();

    IDirect3DSurface9* pOldDS = 0;
    _pd3dDevice->GetDepthStencilSurface(&pOldDS);    

    //
    // post process.
    //
	IDirect3DTexture9 *pPrevTarget = 0;
	IDirect3DSurface9 *pPrevTargetSurface = 0 ;
	IDirect3DTexture9 *pTemp = 0 ;

    if( SUCCEEDED( _pd3dDevice->BeginScene() ) )
    {
		// added, jiayi, [2010/6/18]
	//	MeRenderManager::Instance()->DoRenderCollector();

		ScretchRectToTexture( false );	

		_pd3dDevice->SetDepthStencilSurface(_pSceneDS);

        pPrevTarget = _pSceneRT;
        PostProcessEffectMap::iterator it = _postProcessEffectMap.begin(),
            end = _postProcessEffectMap.end();
        for ( ; it != end; ++it )
        {
			// 默认开启
			if( !it->second->enable() )
				continue;

			//if (strstr(it->first.c_str(),"Hdr") != NULL)
			//	continue;
     

            it->second->render( _pSceneRT, _pScenePositionRT ); 			
            pPrevTarget = it->second->getFinalTexture();
			pPrevTarget->GetSurfaceLevel( 0 , &pPrevTargetSurface );
			_pd3dDevice->StretchRect( pPrevTargetSurface, NULL, _pSceneRTSurface, NULL, D3DTEXF_LINEAR );
			if(0)
				D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, pPrevTarget, 0);
			Safe_Release( pPrevTargetSurface )
        }

        _pd3dDevice->EndScene();
    }

    _pd3dDevice->SetDepthStencilSurface(pOldDS);
    pOldDS->Release();

    // 渲染Post Process好的贴图到全屏去。
    _renderQuad( pPrevTarget );
}

void PostProcessManager::enableProcess( const char* pszName, bool bEnable )
{
	if( !_bEnabled )
		return;

	PostProcessEffectMap::iterator it = _postProcessEffectMap.find( pszName );
	if( it != _postProcessEffectMap.end() )
		it->second->enable( bEnable );
}
void PostProcessManager::SetCrossPostProcessingTexture( const std::string& strFilename )
{
	short stTextureId = GetEngine()->GetTextureManager()->RegisterTexture( strFilename.c_str(), FALSE, TRUE );
	ITexture* pTexture = GetEngine()->GetTextureManager()->GetTextureNoLock( stTextureId );
	if( pTexture && pTexture->GetData() )
	{
		SetCrossPostProcessingTexture( ( IDirect3DTexture9* )pTexture->GetData() );
	}
}
void PostProcessManager::saveTempRenderTarget()
{
	if( !_bEnabled )
		return;

	LPDIRECT3DSURFACE9 defaultRT = 0;
	LPDIRECT3DSURFACE9 positionRT = 0;
	
	_pd3dDevice->GetRenderTarget(0, &defaultRT);
	_pd3dDevice->StretchRect( defaultRT, NULL, _pDefaultRenderTargetTempSurface, NULL, D3DTEXF_LINEAR );

#ifdef RENDER_MRT
	if( _bEnableMultiRTs )
	{
		_pd3dDevice->GetRenderTarget(1, &positionRT);
		_pd3dDevice->StretchRect( positionRT, NULL, _pZPositionRenderTargetTempSurface, NULL, D3DTEXF_LINEAR );
	}	
#endif // RENDER_MRT

	if( defaultRT )
		defaultRT->Release();

	if( positionRT )
		positionRT->Release();
}

void PostProcessManager::restoreTempRenderTarget()
{
	if( !_bEnabled )
		return;

	LPDIRECT3DSURFACE9 defaultRT = 0;
	LPDIRECT3DSURFACE9 positionRT = 0;

	_pd3dDevice->GetRenderTarget(0, &defaultRT);
	_pd3dDevice->StretchRect( _pDefaultRenderTargetTempSurface, NULL, defaultRT, NULL, D3DTEXF_LINEAR );

#ifdef RENDER_MRT
	if( _bEnableMultiRTs )
	{
		_pd3dDevice->GetRenderTarget(1, &positionRT);
		_pd3dDevice->StretchRect( _pZPositionRenderTargetTempSurface, NULL, positionRT, NULL, D3DTEXF_LINEAR );
	}	
#endif // RENDER_MRT

	if( defaultRT )
		defaultRT->Release();

	if( positionRT )
		positionRT->Release();
}