/********************************************************************
	created:	2008/05/20
	created:	20:5:2008   14:35
	filename: 	d:\work\whu\Sample\SimpleSample\PostProcess.cpp
	file path:	d:\work\whu\Sample\SimpleSample
	file base:	PostProcess
	file ext:	cpp
	author:		whu
	
	purpose:	全屏特效。
*********************************************************************/

#include "Me3d/PostProcess/PostProcess.h"
#include "Me3d/Engine/EngineInstance.h"
#include "Me3d/Global.h"
#include <exception>
#include <sstream>
#include <cassert>
#include <tchar.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) 
//#include "Launcher/DataLauncher.h"
#include "../filepacket/packet_interface.h"
#ifndef STD_ThrowException
#define STD_ThrowException( error )                                 \
    std::stringstream __strTemp__;                                  \
    __strTemp__ << __FILE__ << "(" << __LINE__ << "): " << error;   \
    throw std::exception( __strTemp__.str().c_str() );
#endif

//-------------------------------------------------------
//                  PostProcessElement
//-------------------------------------------------------

RenderTargetChain PostProcessEffect::s_RTChain[PostProcessElement::RT_COUNT];

PostProcessElement::PostProcessElement() : m_pEffect(NULL),
    m_hTPostProcess(NULL),
    m_nRenderTarget(0)
{
    memset( m_hTexSource, 0, sizeof(m_hTexSource) );
    memset( m_hTexScene, 0, sizeof(m_hTexScene) );
    memset( m_bWrite, 0, sizeof(m_bWrite) );
}

HRESULT PostProcessElement::Init(LPDIRECT3DDEVICE9 pDev, DWORD dwShaderFlags, LPCSTR wszName)
{
    HRESULT hr = D3DXERR_INVALIDDATA;
    LPD3DXBUFFER error = NULL;

    hr = D3DXCreateEffectFromFile( pDev,
        wszName,
        NULL,
        NULL,
        dwShaderFlags,
        NULL,
        &m_pEffect,
        &error );
	if( hr != S_OK )
	{
// 		FILE	* fp = fopen(wszName,"rb");
// 		if (!fp)
		char * pData=NULL;size_t nSize;
		nSize=packet_namespace::LoadFile(wszName,pData,0);
		if(nSize<=0)
		{
			delete [] pData;
			return D3DXERR_INVALIDDATA;
		}
		hr = D3DXCreateEffect( pDev,
			pData,nSize,//fp->_ptr,fp->_bufsiz,
			NULL,
			NULL,
			dwShaderFlags,
			NULL,
			&m_pEffect,
			&error );
		if (error)
		{
			 MessageBox(NULL,(char*)(error->GetBufferPointer()),NULL,MB_OK);
		}
	 
	//	fclose(fp);
		delete [] pData;
		if( FAILED( hr ) )
			return hr;
	}

    // Get the PostProcess technique handle
    m_hTPostProcess = m_pEffect->GetTechniqueByName( "PostProcess" );

    // Obtain the handles to all texture objects in the effect
	m_hTexScene[0] = m_pEffect->GetParameterByName( NULL, "g_txSceneColor" );
	m_hTexScene[1] = m_pEffect->GetParameterByName( NULL, "g_txScenePosition" );
    m_hTexScene[2] = m_pEffect->GetParameterByName( NULL, "g_txSceneNormal" );
    m_hTexScene[3] = m_pEffect->GetParameterByName( NULL, "g_txSceneVelocity" );
	m_hTexSource[0] = m_pEffect->GetParameterByName( NULL, "g_txSrcColor" );
	m_hTexSource[1] = m_pEffect->GetParameterByName( NULL, "g_txSrcPosition" );
    m_hTexSource[2] = m_pEffect->GetParameterByName( NULL, "g_txSrcNormal" );
    m_hTexSource[3] = m_pEffect->GetParameterByName( NULL, "g_txSrcVelocity" );

    // Find out what render targets the technique writes to.
    D3DXTECHNIQUE_DESC techdesc;
    if( FAILED( m_pEffect->GetTechniqueDesc( m_hTPostProcess, &techdesc ) ) )
        return D3DERR_INVALIDCALL;

    for( DWORD i = 0; i < techdesc.Passes; ++i )
    {
        D3DXPASS_DESC passdesc;
        if( SUCCEEDED( m_pEffect->GetPassDesc( m_pEffect->GetPass( m_hTPostProcess, i ), &passdesc ) ) )
        {
            D3DXSEMANTIC aSem[MAXD3DDECLLENGTH];
            UINT uCount;
            if( SUCCEEDED( D3DXGetShaderOutputSemantics( passdesc.pPixelShaderFunction, aSem, &uCount ) ) )
            {
                // Semantics received. Now examine the content and
                // find out which render target this technique
                // writes to.
                while( uCount-- )
                {
                    if( D3DDECLUSAGE_COLOR == aSem[uCount].Usage &&
                        RT_COUNT > aSem[uCount].UsageIndex )
                        m_bWrite[uCount] = true;
                }
            }
        }
    }

    // Obtain the render target channel
    D3DXHANDLE hAnno;
    hAnno = m_pEffect->GetAnnotationByName( m_hTPostProcess, "nRenderTarget" );
    if( hAnno )
        m_pEffect->GetInt( hAnno, &m_nRenderTarget );

    // Obtain the handles to the changeable parameters, if any.
    for( int i = 0; i < NUM_PARAMS; ++i )
    {
        char szName[32];

        StringCchPrintfA( szName, 32, "Parameter%d", i );
        hAnno = m_pEffect->GetAnnotationByName( m_hTPostProcess, szName );
        LPCSTR szParamName;
        if( !hAnno ||
            FAILED( m_pEffect->GetString( hAnno, &szParamName ) ) )
            continue;	

        Parameter param;
        param.paramName = szParamName;
        param.hParam = m_pEffect->GetParameterByName( NULL, szParamName );

        // Get the parameter description
        LPCSTR szParamDesc;
        StringCchPrintfA( szName, 32, "Parameter%dDesc", i );
        hAnno = m_pEffect->GetAnnotationByName( m_hTPostProcess, szName );
        if( hAnno &&
            SUCCEEDED( m_pEffect->GetString( hAnno, &szParamDesc ) ) )
        {
            param.paramDesc = szParamDesc;
        }

        // Get the parameter size
        StringCchPrintfA( szName, 32, "Parameter%dSize", i );
        hAnno = m_pEffect->GetAnnotationByName( m_hTPostProcess, szName );
        if( hAnno )
        {
            m_pEffect->GetInt( hAnno, &param.paramSize );
        }

        // Get the parameter default
        StringCchPrintfA( szName, 32, "Parameter%dDef", i );
        hAnno = m_pEffect->GetAnnotationByName( m_hTPostProcess, szName );
        if( hAnno )
        {
            m_pEffect->GetVector( hAnno, &param.paramVectorValue );
        }
		// added, jiayi, [2009.5.7]
		if( i > 2)//matrix
			parametersMatrix[szParamName] = param;
		else
			parametersVector[szParamName] = param;
    }

    return S_OK;
}

void PostProcessElement::Cleanup()
{
    Safe_Release( m_pEffect );
}

HRESULT PostProcessElement::OnResetDevice(DWORD dwWidth, DWORD dwHeight )
{
    assert( m_pEffect );
	if( !m_pEffect )
		return S_OK;

    m_pEffect->OnResetDevice();

    // If one or more kernel exists, convert kernel from
    // pixel space to texel space.

    // First check for kernels.  Kernels are identified by
    // having a string annotation of name "ConvertPixelsToTexels"
    D3DXHANDLE hParamToConvert;
    D3DXHANDLE hAnnotation;
    UINT uParamIndex = 0;
    // If a top-level parameter has the "ConvertPixelsToTexels" annotation,
    // do the conversion.
    while( NULL != ( hParamToConvert = m_pEffect->GetParameter( NULL, uParamIndex++ ) ) )
    {
        if( NULL != ( hAnnotation = m_pEffect->GetAnnotationByName( hParamToConvert, "ConvertPixelsToTexels" ) ) )
        {
            LPCSTR szSource;
            m_pEffect->GetString( hAnnotation, &szSource );
            D3DXHANDLE hConvertSource = m_pEffect->GetParameterByName( NULL, szSource );

            if( hConvertSource )
            {
                // Kernel source exists. Proceed.
                // Retrieve the kernel size
                D3DXPARAMETER_DESC desc;
                m_pEffect->GetParameterDesc( hConvertSource, &desc );
                // Each element has 2 floats
                DWORD cKernel = desc.Bytes / (2 * sizeof(float));
                D3DXVECTOR4 *pvKernel = MeDefaultNew D3DXVECTOR4[cKernel];
                if( !pvKernel )
                    return E_OUTOFMEMORY;
                m_pEffect->GetVectorArray( hConvertSource, pvKernel, cKernel );
                // Convert
                for( DWORD i = 0; i < cKernel; ++i )
                {
                    pvKernel[i].x = pvKernel[i].x / dwWidth;
                    pvKernel[i].y = pvKernel[i].y / dwHeight;
                }
                // Copy back
                m_pEffect->SetVectorArray( hParamToConvert, pvKernel, cKernel );

                delete[] pvKernel;
            }
        }
    }

    return S_OK;
}

HRESULT PostProcessElement::OnLostDevice()
{
    assert( m_pEffect );
    m_pEffect->OnLostDevice();
    return S_OK;
}


//-------------------------------------------------------
//                  PostProcess
//-------------------------------------------------------
// Vertex declaration for post-processing
const D3DVERTEXELEMENT9 PostProcessEffect::QuadVertex::Decl[4] =
{
    { 0, 0,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
    { 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0 },
    { 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  1 },
    D3DDECL_END()
};

PostProcessEffect::PostProcessEffect( const std::string& name ) : _pd3dDevice( NULL ),
    _pVertDeclPP( NULL ),
    _screenWidth( 0 ), _screenHeight( 0 ),
    _name( name ), _bNeedMultiRTs( false ),_bEnable( true ),
	_nLastTargetIndex( 0 )
{
    memset( _pSceneSaveRT, 0, sizeof(_pSceneSaveRT) );
}

PostProcessEffect::~PostProcessEffect()
{
}

void PostProcessEffect::create(IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory /* = TEXT */, bool bNeedMultiRTs /*= false*/)
{
    _pd3dDevice = pd3dDevice;
	_bNeedMultiRTs = bNeedMultiRTs;

    // Create vertex declaration for post-process
    if( FAILED( pd3dDevice->CreateVertexDeclaration( QuadVertex::Decl, &_pVertDeclPP ) ) )
    {
        assert( 0 && "Failed to call CreateVertexDeclaration in PostProcessEffect::Create" );
        STD_ThrowException( "Failed to call CreateVertexDeclaration in PostProcessEffect::Create" );
    }
}

void PostProcessEffect::destroy()
{
    Safe_Release( _pVertDeclPP );
	for( int i = 0 ; i < PostProcessElement::RT_COUNT ; ++ i )
	{
		Safe_Release( _pSceneSaveRT[i] );
	}

    for ( size_t i = 0; i < _postProcessElements.size(); ++i )
    {
		_postProcessElements[i]->Cleanup();
        Safe_Delete( _postProcessElements[i] );
    }

    _pd3dDevice = NULL;
}

void PostProcessEffect::restoreDeviceObjects(IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight )
{
    _pd3dDevice = pd3dDevice;
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;

    //D3DCAPS9 Caps;
    //pd3dDevice->GetDeviceCaps( &Caps );

    //// Determine which of D3DFMT_A16B16G16R16F or D3DFMT_A8R8G8B8
    //// to use for scene-rendering RTs.
    //D3DFORMAT texFormat;
    //IDirect3D9* pD3D;
    //_pd3dDevice->GetDirect3D( &pD3D );
    //D3DDISPLAYMODE DisplayMode;
    //_pd3dDevice->GetDisplayMode( 0, &DisplayMode );

    //if( FAILED( pD3D->CheckDeviceFormat( Caps.AdapterOrdinal, Caps.DeviceType,
    //    DisplayMode.Format, D3DUSAGE_RENDERTARGET, 
    //    D3DRTYPE_TEXTURE, D3DFMT_A16B16G16R16F ) ) )
    //    texFormat = D3DFMT_A8R8G8B8;
    //else
    //    texFormat = D3DFMT_A16B16G16R16F;

    // Create scene save texture
    for( int i = 0; i < PostProcessElement::RT_COUNT; ++i )
    {
        //pd3dDevice->CreateTexture( (unsigned int)_screenWidth,
        //    (unsigned int)_screenHeight,
        //    1,
        //    D3DUSAGE_RENDERTARGET,
        //    texFormat,
        //    D3DPOOL_DEFAULT,
        //    &_pSceneSaveRT[i],
        //    NULL );

        // Create the textures for this render target chains
		if( s_RTChain[0].m_pRenderTarget[0] != NULL )
			continue;

        IDirect3DTexture9 *pRT[2];
        memset( pRT, 0, sizeof(pRT) );

		HRESULT hr;
        for( int t = 0; t < 2; ++t )
        {
            hr = pd3dDevice->CreateTexture( (unsigned int)_screenWidth,
                (unsigned int)_screenHeight,
                1,
                D3DUSAGE_RENDERTARGET,
                D3DFMT_A8R8G8B8,
                D3DPOOL_DEFAULT,
                &pRT[t],
                NULL );
			if( hr == D3DERR_OUTOFVIDEOMEMORY)
			{
				assert( 0 && "D3DERR_OUTOFVIDEOMEMORY ");
				char acErrorInfo[256] = {0};		
				_stprintf_s( acErrorInfo, 256, "%s", "显存不足" );
				::MessageBoxA( 0, acErrorInfo, acErrorInfo, MB_OK );
				::TerminateProcess( ::GetCurrentProcess(), 0 );
				
			}
			else if( hr == D3DERR_INVALIDCALL )
			{
				assert( 0 && " D3DERR_INVALIDCALL " );
			}
			else if( hr == E_OUTOFMEMORY )
			{
				assert( 0 && "E_OUTOFMEMORY" );
				char acErrorInfo[256] = {0};		
				_stprintf_s( acErrorInfo, 256, "%s", "内存不足" );
				::MessageBoxA( 0, acErrorInfo, acErrorInfo, MB_OK );
				::TerminateProcess( ::GetCurrentProcess(), 0 );				
			}
        }
        s_RTChain[i].Init( pRT );

        for( int t = 0; t < 2; ++t )
        {
            Safe_Release( pRT[t] );
        }
    }

    //
    for ( size_t i = 0; i < _postProcessElements.size(); ++i )
    {
        _postProcessElements[i]->OnResetDevice( static_cast<unsigned long>(_screenWidth), 
            static_cast<unsigned long>(_screenHeight) );
    }

    //
    // Set up our quad
    //
    QuadVertex Quad[4] =
    {
        { -0.5f,             -0.5f,              1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
        { _screenWidth-0.5f, -0.5,               1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },
        { -0.5,              _screenHeight-0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f },
        { _screenWidth-0.5f, _screenHeight-0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }
    };
    memcpy( _quadVertex, Quad, sizeof(Quad) );
}

void PostProcessEffect::invalidateDeviceObjects()
{
    _pd3dDevice = NULL;

    for ( int i = 0; i < PostProcessElement::RT_COUNT; ++i )
    {
        Safe_Release( _pSceneSaveRT[i] );

        s_RTChain[i].Cleanup();
    }

    for ( size_t i = 0; i < _postProcessElements.size(); ++i )
    {
        _postProcessElements[i]->OnLostDevice();
    }
}

void PostProcessEffect::setParameter(const std::string& paramName, const D3DXVECTOR4& value )
{
    for ( size_t i = 0; i < _postProcessElements.size(); ++i )
    {
        PostProcessElement::Parameters::iterator it = _postProcessElements[i]->parametersVector.find( paramName );
        if ( it != _postProcessElements[i]->parametersVector.end() )
        {
            it->second.paramVectorValue = value;
        }
    }
}

void PostProcessEffect::setParameter( const std::string& paramName, const D3DXMATRIXA16& value )
{
	// added, jiayi, [2009.5.7]
	for ( size_t i = 0; i < _postProcessElements.size(); ++i )
	{
		PostProcessElement::Parameters::iterator it = _postProcessElements[i]->parametersMatrix.find( paramName );
		if ( it != _postProcessElements[i]->parametersMatrix.end() )
		{
			it->second.paramMatrixValue = value;
		}
	}
}

D3DXVECTOR4* PostProcessEffect::getParameterVector4( const std::string& paramName ) const
{
	for ( size_t i = 0; i < _postProcessElements.size(); ++i )
	{
		PostProcessElement::Parameters::iterator it = _postProcessElements[i]->parametersVector.find( paramName );
		if ( it != _postProcessElements[i]->parametersVector.end() )
		{
			return &it->second.paramVectorValue;
		}
	}
	return NULL;
}

D3DXMATRIXA16* PostProcessEffect::getParameterMatrix16( const std::string& paramName ) const
{
	for ( size_t i = 0; i < _postProcessElements.size(); ++i )
	{
		PostProcessElement::Parameters::iterator it = _postProcessElements[i]->parametersMatrix.find( paramName );
		if ( it != _postProcessElements[i]->parametersMatrix.end() )
		{
			return &it->second.paramMatrixValue;
		}
	}
	return NULL;
}

void PostProcessEffect::_singlePostProcess( IDirect3DDevice9 *pd3dDevice, PostProcessElement &PP,
                                           IDirect3DVertexBuffer9 *pVB, QuadVertex *aQuad, float &fExtentX, float &fExtentY )
{
    HRESULT hr;

    //
    // The post-process effect may require that a copy of the
    // originally rendered scene be available for use, so
    // we initialize them here.
    //

    for( int i = 0; i < PP.RT_COUNT; ++i )
        PP.m_pEffect->SetTexture( PP.m_hTexScene[i], _pSceneSaveRT[i] );

    //
    // If there are any parameters, initialize them here.
    //

    //for( int i = 0; i < PP.NUM_PARAMS; ++i )
    //    if( PP.m_ahParam[i] )
    //        PP.m_pEffect->SetVector( PP.m_ahParam[i], &PP.m_avParamDef[i] );

    PostProcessElement::Parameters::iterator it, end = PP.parametersVector.end();
    for ( it = PP.parametersVector.begin(); it != end; ++it )
    {
        if( it->second.hParam )
            PP.m_pEffect->SetVector( it->second.hParam, &it->second.paramVectorValue );
    }

	end = PP.parametersMatrix.end();
	for ( it = PP.parametersMatrix.begin(); it != end; ++it )
	{
		if( it->second.hParam )
			PP.m_pEffect->SetValue( it->second.hParam, &it->second.paramMatrixValue, sizeof( D3DXMATRIXA16 ) );
	}

    // Render the quad
    //if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        PP.m_pEffect->SetTechnique( "PostProcess" );

        // Set the vertex declaration
        pd3dDevice->SetVertexDeclaration( _pVertDeclPP );

        // Draw the quad
        UINT cPasses, p;
        PP.m_pEffect->Begin( &cPasses, 0 );
        for( p = 0; p < cPasses; ++p )
        {
            bool bUpdateVB = false;  // Inidicates whether the vertex buffer
            // needs update for this pass.

            //
            // If the extents has been modified, the texture coordinates
            // in the quad need to be updated.
            //

            if( aQuad[1].u != fExtentX )
            {
                aQuad[1].u = aQuad[3].u = fExtentX;
                bUpdateVB = true;
            }
            if( aQuad[2].v != fExtentY )
            {
                aQuad[2].v = aQuad[3].v = fExtentY;
                bUpdateVB = true;
            }

            //
            // Check if the pass has annotation for extent info.  Update
            // fScaleX and fScaleY if it does.  Otherwise, default to 1.0f.
            //

            float fScaleX = 1.0f, fScaleY = 1.0f;
            D3DXHANDLE hPass = PP.m_pEffect->GetPass( PP.m_hTPostProcess, p );
            D3DXHANDLE hExtentScaleX = PP.m_pEffect->GetAnnotationByName( hPass, "fScaleX" );
            if( hExtentScaleX )
                PP.m_pEffect->GetFloat( hExtentScaleX, &fScaleX );
            D3DXHANDLE hExtentScaleY = PP.m_pEffect->GetAnnotationByName( hPass, "fScaleY" );
            if( hExtentScaleY )
                PP.m_pEffect->GetFloat( hExtentScaleY, &fScaleY );

            //
            // Now modify the quad according to the scaling values specified for
            // this pass
            //
            if( fScaleX != 1.0f )
            {
                aQuad[1].x = (aQuad[1].x + 0.5f) * fScaleX - 0.5f;
                aQuad[3].x = (aQuad[3].x + 0.5f) * fScaleX - 0.5f;
                bUpdateVB = true;
            }
            if( fScaleY != 1.0f )
            {
                aQuad[2].y = (aQuad[2].y + 0.5f) * fScaleY - 0.5f;
                aQuad[3].y = (aQuad[3].y + 0.5f) * fScaleY - 0.5f;
                bUpdateVB = true;
            }

            if( bUpdateVB )
            {
                LPVOID pVBData;
                // Scaling requires updating the vertex buffer.
                if( SUCCEEDED( pVB->Lock( 0, 0, &pVBData, D3DLOCK_DISCARD ) ) )
                {
                    CopyMemory( pVBData, aQuad, 4 * sizeof(QuadVertex) );
                    pVB->Unlock();
                }
            }
            fExtentX *= fScaleX;
            fExtentY *= fScaleY;

            // Set up the textures and the render target
            //
			IDirect3DTexture9* pTemp = 0;
            for( int i = 0; i < PP.RT_COUNT; ++i )
            {
                // If this is the very first post-process rendering,
                // obtain the source textures from the scene.
                // Otherwise, initialize the post-process source texture to
                // the previous render target.
                //
                if( s_RTChain[i].m_bFirstRender )
                    PP.m_pEffect->SetTexture( PP.m_hTexSource[i], _pSceneSaveRT[i] );
                else
                    PP.m_pEffect->SetTexture( PP.m_hTexSource[i], s_RTChain[i].GetNextSource() );
				
            }
			if(0)
				D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, pTemp, 0);

            //
            // Set up the MeNew render target
            //
            IDirect3DTexture9 *pTarget = s_RTChain[PP.m_nRenderTarget].GetNextTarget();
            IDirect3DSurface9 *pTexSurf;
            if( pTarget )
                hr = pTarget->GetSurfaceLevel( 0, &pTexSurf );
            if( !pTarget || FAILED( hr ) )
            {
                assert( 0 && "Failed to call pTarget->GetSurfaceLevel in PostProcessEffect::_singlePostProcess" );
                STD_ThrowException( "Failed to call pTarget->GetSurfaceLevel in PostProcessEffect::_singlePostProcess" );
            }

            pd3dDevice->SetRenderTarget( 0, pTexSurf );
            pTexSurf->Release();
            // We have output to this render target. Flag it.
            s_RTChain[PP.m_nRenderTarget].m_bFirstRender = false;

            //
            // Clear the render target
            //
            if (FAILED(pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET,
                0x00000000, 1.0f, 0L )))
                continue;

            //
            // Render
            //
            if (SUCCEEDED(PP.m_pEffect->BeginPass( p )))
            {
                if( FAILED( pd3dDevice->SetStreamSource( 0, pVB, 0, sizeof(QuadVertex) ) ) )
					assert( "postprocess, setstreamsource" && 0 );
                if( FAILED( pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 ) ) )
					assert( "postprocess dp" && 0 );

                if( FAILED( PP.m_pEffect->EndPass() ) )
					assert( 0 && "postprocess, endpass");
            }

			_nLastTargetIndex = s_RTChain[PP.m_nRenderTarget].m_nNext;

            // Update next rendertarget index
            s_RTChain[PP.m_nRenderTarget].Flip();
			
        }
        PP.m_pEffect->End();

        //// End scene
        //pd3dDevice->EndScene();
    }
}

PostProcessElement* PostProcessEffect::_addPostProcessElement(LPCSTR FxDirectory, LPCSTR FxFilename )
{
    // Define DEBUG_VS and/or DEBUG_PS to debug vertex and/or pixel shaders with the 
    // shader debugger. Debugging vertex shaders requires either REF or software vertex 
    // processing, and debugging pixel shaders requires REF.  The 
    // D3DXSHADER_FORCE_*_SOFTWARE_NOOPT flag improves the debug experience in the 
    // shader debugger.  It enables source level debugging, prevents instruction 
    // reordering, prevents dead code elimination, and forces the compiler to compile 
    // against the next higher available software target, which ensures that the 
    // unoptimized shaders do not exceed the shader model limitations.  Setting these 
    // flags will cause slower rendering since the shaders will be unoptimized and 
    // forced into software.  See the DirectX documentation for more information about 
    // using the shader debugger.
    DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
    dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
    dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

    PostProcessElement* ppe = MeNew PostProcessElement();
    if ( _tcscmp( FxDirectory, TEXT("") ) != 0 )
    {
        TCHAR szPath[MAX_PATH] = {0};
        StringCchPrintf( szPath, MAX_PATH, TEXT("%s\\%s"), FxDirectory, FxFilename );
        if( FAILED( ppe->Init( _pd3dDevice, dwShaderFlags, szPath ) ) )
		{
			// read .fxo file
			sprintf_s( szPath, MAX_PATH, "%so", szPath );
			ppe->Init( _pd3dDevice, dwShaderFlags, szPath );
		}
    }
    else
    {
        ppe->Init( _pd3dDevice, dwShaderFlags, FxFilename );
    }
    _postProcessElements.push_back( ppe );
    return ppe;
}

void PostProcessEffect::preRenderTargetUpdate()
{
}

void PostProcessEffect::render( IDirect3DTexture9* pSceneRT )
{
	render( pSceneRT, NULL );
}

void PostProcessEffect::render( IDirect3DTexture9* pSceneRT , IDirect3DTexture9* pScenePositionRT )
{
	if( !pScenePositionRT )
	{
		if( _bNeedMultiRTs )
			return;
	}
	else
	{
		_pSceneSaveRT[1] = pScenePositionRT;
		_pSceneSaveRT[1]->AddRef();
	}

	_pSceneSaveRT[0] = pSceneRT;
	_pSceneSaveRT[0]->AddRef();
	

    //
    // Swap the chains
    //
//    int i;
//     for(i = 0; i < PostProcessElement::RT_COUNT; ++i )
//         s_RTChain[i].Flip();

    // Reset all render targets used besides RT 0
//     for( i = 1; i < PostProcessElement::RT_COUNT; ++i )
//         _pd3dDevice->SetRenderTarget( i, NULL );

    // Clear first-time render flags
    for( int i = 0; i < PostProcessElement::RT_COUNT; ++i )
        s_RTChain[i].m_bFirstRender = true;   

    //
    // Set up our quad
    //
    QuadVertex Quad[4];
    memcpy( Quad, _quadVertex, sizeof(_quadVertex) );

    //
    // Create a vertex buffer out of the quad
    //
    IDirect3DVertexBuffer9* pVB;
    HRESULT hr = _pd3dDevice->CreateVertexBuffer( sizeof(QuadVertex) * 4,
        D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,
        0,
        D3DPOOL_DEFAULT,
        &pVB,
        NULL );
    if( FAILED( hr ) )
    {
        assert( 0 && "Failed to call CreateVertexBuffer in PostProcessEffect::RestoreDeviceObjects" );
        STD_ThrowException( "Failed to call CreateVertexBuffer in PostProcessEffect::RestoreDeviceObjects" );
    }

    // Fill in the vertex buffer
    void* pVBData;
    if( SUCCEEDED( pVB->Lock( 0, 0, &pVBData, D3DLOCK_DISCARD ) ) )
    {
        CopyMemory( pVBData, Quad, sizeof(Quad) );
        pVB->Unlock();
    }

    // Perform post processing
    float fExtentX = 1.0f, fExtentY = 1.0f;
    for ( size_t i = 0; i < _postProcessElements.size(); ++i )
    {
        _singlePostProcess( _pd3dDevice, *_postProcessElements[i], pVB,
            Quad, fExtentX, fExtentY );
    }

    Safe_Release( pVB );
    Safe_Release( _pSceneSaveRT[0] );
	if( pScenePositionRT )
		Safe_Release( _pSceneSaveRT[1] );
}


//-------------------------------------------------------
//                  GlowPostProcess
//-------------------------------------------------------
GlowPostProcessEffect::GlowPostProcessEffect( const std::string& name ) : PostProcessEffect( name )
{
}

GlowPostProcessEffect::~GlowPostProcessEffect()
{
}

void GlowPostProcessEffect::create(IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory, bool bNeedMultiRTs )
{
    PostProcessEffect::create( pd3dDevice, FxDirectory, bNeedMultiRTs );

    //
    // 初始化Blur效果用到的Post Process 单元。
    //
    PostProcessElement* element = _addPostProcessElement( FxDirectory, TEXT("PP_ColorDownFilter4.fxo") );
#if 0
    element = _addPostProcessElement( FxDirectory, TEXT("PP_ColorGBlurH.fx") );
    element = _addPostProcessElement( FxDirectory, TEXT("PP_ColorGBlurH.fx") );
#else
    element = _addPostProcessElement( FxDirectory, TEXT("PP_ColorBloomH.fxo") );
    element->parametersVector["BloomScale"].paramVectorValue = D3DXVECTOR4( 0.40f, 0, 0, 0 );
    element = _addPostProcessElement( FxDirectory, TEXT("PP_ColorBloomV.fxo") );
    element->parametersVector["BloomScale"].paramVectorValue = D3DXVECTOR4( 0.40f, 0, 0, 0 );
#endif
    element = _addPostProcessElement( FxDirectory, TEXT("PP_ColorCombine4.fxo") );
}

void GlowPostProcessEffect::destroy()
{
    PostProcessEffect::destroy();
}

void GlowPostProcessEffect::restoreDeviceObjects(IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight )
{
    PostProcessEffect::restoreDeviceObjects( pd3dDevice, screenWidth, screenHeight );
}

void GlowPostProcessEffect::invalidateDeviceObjects()
{
    PostProcessEffect::invalidateDeviceObjects();
}

void GlowPostProcessEffect::render( IDirect3DTexture9* pSceneRT )
{
    PostProcessEffect::render( pSceneRT );
}

//-------------------------------------------------------
//                  BloomPostProcessEffect
//-------------------------------------------------------
BloomPostProcessEffect::BloomPostProcessEffect( const std::string& name ) : PostProcessEffect( name )
{
}

BloomPostProcessEffect::~BloomPostProcessEffect()
{
}

void BloomPostProcessEffect::create(IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory, bool bNeedMultiRTs )
{
    PostProcessEffect::create( pd3dDevice, FxDirectory, bNeedMultiRTs );

    //
    // 初始化Bloom效果用到的Post Process 单元。
    //
    _addPostProcessElement( FxDirectory, TEXT("PP_ColorDownFilter4.fxo") );
    _addPostProcessElement( FxDirectory, TEXT("PP_ColorDownFilter4.fxo") );
	PostProcessElement* element =_addPostProcessElement( FxDirectory, TEXT("PP_ColorBrightPass.fxo") );
	element->parametersVector["Luminance"].paramVectorValue = D3DXVECTOR4( 0, 0, 0, 0 );
    element =_addPostProcessElement( FxDirectory, TEXT("PP_ColorBloomH.fxo") );
	element->parametersVector["BloomScale"].paramVectorValue = D3DXVECTOR4( 0, 0, 0, 0 );
    element =_addPostProcessElement( FxDirectory, TEXT("PP_ColorBloomV.fxo") );
	element->parametersVector["BloomScale"].paramVectorValue = D3DXVECTOR4( 0, 0, 0, 0 );
    element =_addPostProcessElement( FxDirectory, TEXT("PP_ColorBloomH.fxo") );
	element->parametersVector["BloomScale"].paramVectorValue = D3DXVECTOR4( 0, 0, 0, 0 );
    element =_addPostProcessElement( FxDirectory, TEXT("PP_ColorBloomV.fxo") );
	element->parametersVector["BloomScale"].paramVectorValue = D3DXVECTOR4( 0, 0, 0, 0 );	
    _addPostProcessElement( FxDirectory, TEXT("PP_ColorUpFilter4.fxo") );
    _addPostProcessElement( FxDirectory, TEXT("PP_ColorCombine4.fxo") );
}

void BloomPostProcessEffect::destroy()
{
    PostProcessEffect::destroy();
}

//-------------------------------------------------------
//                  BlurPostProcessEffect
//-------------------------------------------------------
BlurPostProcessEffect::BlurPostProcessEffect( const std::string& name ) : PostProcessEffect( name )
{
}

BlurPostProcessEffect::~BlurPostProcessEffect()
{
}

void BlurPostProcessEffect::create(IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory, bool bNeedMultiRTs )
{
    PostProcessEffect::create( pd3dDevice, FxDirectory, bNeedMultiRTs );

    //
    // 初始化Blur效果用到的Post Process 单元。
    //
    _addPostProcessElement( FxDirectory, TEXT("PP_ColorDownFilter4.fxo") );
    _addPostProcessElement( FxDirectory, TEXT("PP_ColorGBlurH.fxo") );
    _addPostProcessElement( FxDirectory, TEXT("PP_ColorGBlurV.fxo") );
	_addPostProcessElement( FxDirectory, TEXT("PP_ColorCombine4Dark.fxo") );
//     _addPostProcessElement( FxDirectory, TEXT("PP_ColorGBlurH.fx") );
//     _addPostProcessElement( FxDirectory, TEXT("PP_ColorGBlurV.fx") );
    //_addPostProcessElement( FxDirectory, TEXT("PP_ColorUpFilter4.fx") );
	//_addPostProcessElement( FxDirectory, TEXT("PP_DofCombine.fx") );

	_bEnable = false;
}

void BlurPostProcessEffect::destroy()
{
    PostProcessEffect::destroy();
}

//-------------------------------------------------------
//                  BlurPostProcessEffect
//-------------------------------------------------------
ShadowBlurPostProcessEffect::ShadowBlurPostProcessEffect( const std::string& name ) : PostProcessEffect( name )
{
}

ShadowBlurPostProcessEffect::~ShadowBlurPostProcessEffect()
{
}

void ShadowBlurPostProcessEffect::create(IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory )
{
    PostProcessEffect::create( pd3dDevice, FxDirectory );

    //
    // 初始化Blur效果用到的Post Process 单元。
    //
    _addPostProcessElement( FxDirectory, TEXT("PP_ColorGBlurH.fxo") );
    _addPostProcessElement( FxDirectory, TEXT("PP_ColorGBlurV.fxo") );
}

void ShadowBlurPostProcessEffect::destroy()
{
    PostProcessEffect::destroy();
}

//----------------------------------------------------------
LightShaftProcessEffect::LightShaftProcessEffect(const std::string &name) : 
PostProcessEffect( name ), m_pTexSun(0), m_pSurfaceSun(0)
{}
//----------------------------------------------------------
LightShaftProcessEffect::~LightShaftProcessEffect()
{
	Safe_Release(m_pTexSun);
}
//----------------------------------------------------------
void LightShaftProcessEffect::create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory /*= TEXT("")*/, bool bNeedMultiRTs /*= false*/ )
{
	PostProcessEffect::create( pd3dDevice, FxDirectory, bNeedMultiRTs );

	_addPostProcessElement( FxDirectory, TEXT("PP_LightShaft_Pre.fxo") );		
	_addPostProcessElement( FxDirectory, TEXT("PP_ColorDownFilter4.fxo") );	
	_addPostProcessElement( FxDirectory, TEXT("PP_LightShaft.fxo") );			
	_addPostProcessElement( FxDirectory, TEXT("PP_ColorCombine4.fxo") );
}
//----------------------------------------------------------
void LightShaftProcessEffect::destroy()
{
	Safe_Release( m_pSurfaceSun );
	Safe_Release( m_pTexSun );
	PostProcessEffect::destroy();
}
//----------------------------------------------------------
void LightShaftProcessEffect::restoreDeviceObjects( IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight )
{
	PostProcessEffect::restoreDeviceObjects( pd3dDevice, screenWidth, screenHeight );

	if( FAILED( _pd3dDevice->CreateTexture( 
		_screenWidth,
		_screenHeight,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_pTexSun,
		NULL )))
	{
		OutputDebugString( "Unable to create sun texture in postprocess!" );
		return;
	}
	m_pTexSun->GetSurfaceLevel( 0, &m_pSurfaceSun );

}
//----------------------------------------------------------
void LightShaftProcessEffect::invalidateDeviceObjects()
{
	Safe_Release( m_pSurfaceSun );
	Safe_Release( m_pTexSun );
	PostProcessEffect::invalidateDeviceObjects();	
}
//----------------------------------------------------------
void LightShaftProcessEffect::render( IDirect3DTexture9* pSceneRT )
{	
	PostProcessEffect::render( pSceneRT );
}
//----------------------------------------------------------
void LightShaftProcessEffect::updateRenderTargetToEffect()
{
	if(!_checkSunSurface())
		return;
	
 	LPDIRECT3DSURFACE9 rt;
 	_pd3dDevice->GetRenderTarget(0, &rt );
  	HRESULT hr = _pd3dDevice->StretchRect( rt, NULL, m_pSurfaceSun, NULL, D3DTEXF_LINEAR );
  	assert( hr == S_OK );	
	_postProcessElements[0]->m_pEffect->SetTexture( "sunTex", m_pTexSun );
	if(0)
	{
		D3DXSaveSurfaceToFile( "d:\\test_rt.jpg", D3DXIFF_JPG, rt, 0 , 0 );
		D3DXSaveSurfaceToFile( "d:\\test.jpg", D3DXIFF_JPG, m_pSurfaceSun, 0 , 0 );
	}
	rt->Release();
}
//----------------------------------------------------------

bool LightShaftProcessEffect::_checkSunSurface()
{
	if(!m_pTexSun)
	{
		if( FAILED( _pd3dDevice->CreateTexture( 
			_screenWidth,
			_screenHeight,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&m_pTexSun,
			NULL )))
		{
			OutputDebugString( "Unable to create sun texture in postprocess!" );
			return false;
		}
		m_pTexSun->GetSurfaceLevel( 0, &m_pSurfaceSun );
	}	

	return true;

}
//----------------------------------------------------------
//----------------------------------------------------------
//----------------------------------------------------------
//hdr effect
HdrPostProcessEffect::HdrPostProcessEffect( const std::string& name ) : PostProcessEffect( name )
,m_SBaseTexture(NULL)
,m_SBaseSuf(NULL)
,m_SluminanceTexture(NULL)
,m_SluminanceSuf(NULL)
,m_SBloomTexture(NULL)
,m_SBloomSuf(NULL)
{

	 m_BloomTexture = NULL; 
	 m_BloomSuf = NULL ;    


	 m_BaseTexture = NULL ; 
	 m_BaseSuf = NULL ;    
	 m_BloomBaseTexture = NULL;
	m_BloomBaseSuf = NULL;

	m_BaseTexture2 =NULL;
	m_BaseTexture1 = NULL;

	m_BaseSuf2 =NULL;
	m_BaseSuf1 =NULL;


	 m_TempSceneTexture = NULL; //想对画面模糊的图 现在不用了
	 m_TempSceneSuf = NULL; 


}

HdrPostProcessEffect::~HdrPostProcessEffect()
{

	Safe_Release(m_SBaseTexture);
	Safe_Release(m_SBaseSuf);
	Safe_Release(m_SluminanceTexture);
	Safe_Release(m_SluminanceSuf);
	Safe_Release(m_SBloomTexture);
	Safe_Release(m_SBloomSuf);
	Safe_Release(m_BloomTexture);
	Safe_Release(m_BloomSuf);
	Safe_Release(m_BaseTexture);
	Safe_Release(m_BaseSuf);
	Safe_Release(m_BloomBaseTexture);
	Safe_Release(m_BloomBaseSuf);

	Safe_Release(m_BaseTexture1);
	Safe_Release(m_BaseSuf1);

	Safe_Release(m_BaseTexture2);
	Safe_Release(m_BaseSuf2);


	Safe_Release(m_STempTex);
	Safe_Release(m_STempSuf);

	Safe_Release(m_TempSceneTexture);
	Safe_Release(m_TempSceneSuf ); 


}

void HdrPostProcessEffect::destroy()
{
	Safe_Release(m_SBaseTexture);
	Safe_Release(m_SBaseSuf);
	Safe_Release(m_SluminanceTexture);
	Safe_Release(m_SluminanceSuf);
	Safe_Release(m_SBloomTexture);
	Safe_Release(m_SBloomSuf);
	Safe_Release(m_BloomTexture);
	Safe_Release(m_BloomSuf);
	Safe_Release(m_BaseTexture);
	Safe_Release(m_BaseSuf);
	Safe_Release(m_BloomBaseTexture);
	Safe_Release(m_BloomBaseSuf);
	Safe_Release(m_BaseTexture1);
	Safe_Release(m_BaseSuf1);

	Safe_Release(m_BaseTexture2);
	Safe_Release(m_BaseSuf2);


	Safe_Release(m_STempTex);
	Safe_Release(m_STempSuf);	
	Safe_Release(m_TempSceneTexture);
	Safe_Release(m_TempSceneSuf ); 


	PostProcessEffect::destroy();
}

void HdrPostProcessEffect::invalidateDeviceObjects()
{
	Safe_Release(m_SBaseTexture);
	Safe_Release(m_SBaseSuf);
	Safe_Release(m_SluminanceTexture);
	Safe_Release(m_SluminanceSuf);
	Safe_Release(m_SBloomTexture);
	Safe_Release(m_SBloomSuf);
	Safe_Release(m_BloomTexture);
	Safe_Release(m_BloomSuf);
	Safe_Release(m_BaseTexture);
	Safe_Release(m_BaseSuf);

	Safe_Release(m_BaseTexture1);
	Safe_Release(m_BaseSuf1);

	Safe_Release(m_BaseTexture2);
	Safe_Release(m_BaseSuf2);


	Safe_Release(m_BloomBaseTexture);
		Safe_Release(m_BloomBaseSuf);

		Safe_Release(m_STempTex);
		Safe_Release(m_STempSuf);	
		Safe_Release(m_TempSceneTexture);
		Safe_Release(m_TempSceneSuf ); 

	PostProcessEffect::invalidateDeviceObjects();	
}

void HdrPostProcessEffect::restoreDeviceObjects( IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight )
{
	PostProcessEffect::restoreDeviceObjects( pd3dDevice, screenWidth, screenHeight );


	if( FAILED( _pd3dDevice->CreateTexture( _screenWidth,	_screenHeight,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&m_TempSceneTexture,NULL )))
	{
		OutputDebugString( "Unable to create m_TempSceneTexture in postprocess!" );
		return;
	}
	m_TempSceneTexture->GetSurfaceLevel( 0, &m_TempSceneSuf );

	//11
	if( FAILED( _pd3dDevice->CreateTexture( _screenWidth/2,	_screenHeight/2,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&m_SBaseTexture,NULL )))
		{
			OutputDebugString( "Unable to create SbaseTexture in postprocess!" );
			return;
		}
		m_SBaseTexture->GetSurfaceLevel( 0, &m_SBaseSuf );

    //22
	if( FAILED( _pd3dDevice->CreateTexture( _screenWidth/2,	_screenHeight/2,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&m_SluminanceTexture,NULL )))
	{
		OutputDebugString( "Unable to create SbaseTexture in postprocess!" );
		return;
	}
	m_SluminanceTexture->GetSurfaceLevel( 0, &m_SluminanceSuf );

	//33
	if( FAILED( _pd3dDevice->CreateTexture( _screenWidth/4,	_screenHeight/4,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&m_SBloomTexture,NULL )))
	{
		OutputDebugString( "Unable to create SbaseTexture in postprocess!" );
		return;
	}
	m_SBloomTexture->GetSurfaceLevel( 0, &m_SBloomSuf );


	if( FAILED( _pd3dDevice->CreateTexture( _screenWidth/2,	_screenHeight/2,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&m_STempTex,NULL )))
	{
		OutputDebugString( "Unable to create SbaseTexture in postprocess!" );
		return;
	}
	m_STempTex->GetSurfaceLevel( 0, &m_STempSuf );



	//=============================================================================================================
	//下面几张我用来缩小图片了 最终把图片缩小到一个1x1的图片上 直接取亮度
	//44 11111
	if( FAILED( _pd3dDevice->CreateTexture( 512,	512 ,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&m_BloomTexture,NULL )))
	{
		OutputDebugString( "Unable to create SbaseTexture in postprocess!" );
		return;
	}
	m_BloomTexture->GetSurfaceLevel( 0, &m_BloomSuf );



	//44 2222
	if( FAILED( _pd3dDevice->CreateTexture( 256,	256,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&m_BaseTexture,NULL )))
	{
		OutputDebugString( "Unable to create SbaseTexture in postprocess!" );
		return;
	}
	m_BaseTexture->GetSurfaceLevel( 0, &m_BaseSuf );



	if( FAILED( _pd3dDevice->CreateTexture( 64,	64,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&m_BaseTexture1,NULL )))
	{
		OutputDebugString( "Unable to create SbaseTexture in postprocess!" );
		return;
	}
	m_BaseTexture1->GetSurfaceLevel( 0, &m_BaseSuf1 );



	if( FAILED( _pd3dDevice->CreateTexture( 8,	8,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&m_BaseTexture2,NULL )))
	{
		OutputDebugString( "Unable to create SbaseTexture in postprocess!" );
		return;
	}
	m_BaseTexture2->GetSurfaceLevel( 0, &m_BaseSuf2 );



	//55
	if( FAILED( _pd3dDevice->CreateTexture( 1,	1 , 1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&m_BloomBaseTexture,NULL )))
	{
		OutputDebugString( "Unable to create SbaseTexture in postprocess!" );
		return;
	}
	m_BloomBaseTexture->GetSurfaceLevel( 0, &m_BloomBaseSuf );


}



void HdrPostProcessEffect::create(IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory )
{
	PostProcessEffect::create( pd3dDevice, FxDirectory );

	// 不用他的 我里面的图片数量和引擎不能通用， 单独拿来处理好了
	// 初始化Blur效果用到的Post Process 单元。
	//

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	PostProcessElement* ppe = MeNew PostProcessElement();

	TCHAR szPath[MAX_PATH] = {0};
	StringCchPrintf( szPath, MAX_PATH, TEXT("%s\\%s"), FxDirectory, "hdr.fxo" );

	HRESULT hr = D3DXERR_INVALIDDATA;
	LPD3DXBUFFER error = NULL;

	hr = D3DXCreateEffectFromFile( _pd3dDevice,
		szPath,
		NULL,
		NULL,
		dwShaderFlags,
		NULL,
		&ppe->m_pEffect,
		&error );
	if( hr != S_OK )
	{
		char * pData=NULL;size_t nSize;
		nSize=packet_namespace::LoadFile(szPath,pData,0);
		if(nSize<=0)
		{
			delete [] pData;
			return ;
		}
		hr = D3DXCreateEffect( _pd3dDevice,
			pData,nSize,
			NULL,
			NULL,
			dwShaderFlags,
			NULL,
			&ppe->m_pEffect,
			&error );
		if (error)
		{
			MessageBox(NULL,(char*)(error->GetBufferPointer()),NULL,MB_OK);
		}
	}

	 _postProcessElements.push_back( ppe );


	 //创建图片


}

void HdrPostProcessEffect::_singlePostProcess( IDirect3DDevice9 *pd3dDevice, PostProcessElement &PP,
						IDirect3DVertexBuffer9 *pVB, QuadVertex *aQuad, float &fExtentX, float &fExtentY )
{



    aQuad[1].x /= 2.f; 
	aQuad[2].y /= 2.f;
	aQuad[3].x /=2.f;
	aQuad[3].y /= 2.f;



	
   PP.m_pEffect->SetFloat("ScreenW",aQuad[3].x);
   PP.m_pEffect->SetFloat("ScreenH",aQuad[3].y);

	//0 common
	pd3dDevice->SetVertexDeclaration( _pVertDeclPP );//设置顶点格式
	LPVOID pVBData;
	if( SUCCEEDED( pVB->Lock( 0, 0, &pVBData, D3DLOCK_DISCARD ) ) )
	{
		CopyMemory( pVBData, aQuad, 4 * sizeof(QuadVertex) );
		pVB->Unlock();
	}

	pd3dDevice->SetStreamSource( 0, pVB, 0, sizeof(QuadVertex) ) ;

    UINT cPasses, p;
	//1:to m_SBaseTexture
	LPDIRECT3DSURFACE9 rt;
	_pd3dDevice->GetRenderTarget(0, &rt );
	HRESULT hr = _pd3dDevice->StretchRect( rt, NULL, m_SBaseSuf, NULL, D3DTEXF_POINT );  //把原图缩小了 放在m_SBaseTexture上
	assert( hr == S_OK );	
	rt->Release();

	
	 _postProcessElements[0]->m_pEffect->SetTexture( "baseTexture", m_SBaseTexture );



	 //2:求平均亮度
	 _pd3dDevice->StretchRect( m_SBaseSuf, NULL, m_BloomSuf, NULL, D3DTEXF_LINEAR ); //缩小1
   

      
	 _pd3dDevice->StretchRect( m_BloomSuf, NULL, m_BaseSuf, NULL, D3DTEXF_LINEAR ); //缩小2


	
	  _pd3dDevice->StretchRect( m_BaseSuf, NULL, m_BaseSuf1, NULL, D3DTEXF_LINEAR ); //缩小3


	  
	  _pd3dDevice->StretchRect( m_BaseSuf1, NULL, m_BaseSuf2, NULL, D3DTEXF_LINEAR ); //缩小4


	 
	 _pd3dDevice->StretchRect( m_BaseSuf2, NULL, m_BloomBaseSuf, NULL, D3DTEXF_LINEAR ); //缩小5




	_pd3dDevice->SetRenderTarget(0,m_SluminanceSuf);   //设置渲染目标 为亮度图 

	 _postProcessElements[0]->m_pEffect->SetTexture( "bloom1", m_BloomBaseTexture ); //1x1的图片
	

	_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET,0x00000000, 1.0f, 0L );	
	PP.m_pEffect->SetTechnique( "TLuminance" ); //设置技术 
	
	PP.m_pEffect->Begin( &cPasses, 0 );
	for( p = 0; p < cPasses; ++p )
	{
		if (SUCCEEDED(PP.m_pEffect->BeginPass( p )))
		{		
			//draw
			pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 ) ;
			PP.m_pEffect->EndPass() ;
				
		}
	}
	PP.m_pEffect->End();










	






	//4:横向模糊 把原图
	_pd3dDevice->SetRenderTarget(0,m_STempSuf);
	_postProcessElements[0]->m_pEffect->SetTexture( "luminance", m_SBaseTexture );
	_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET,0x00000000, 1.0f, 0L );
	PP.m_pEffect->SetTechnique( "BrightPassFilterBlurH" ); //设置技术 

	PP.m_pEffect->Begin( &cPasses, 0 );
	for( p = 0; p < cPasses; ++p )
	{
		if (SUCCEEDED(PP.m_pEffect->BeginPass( p )))
		{		
			//draw
			pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 ) ;
			PP.m_pEffect->EndPass() ;

		}
	}
	PP.m_pEffect->End();

	if(0) //横向模糊图
		D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, m_SluminanceTexture, 0);

	//5:纵向模糊 不清

	aQuad[1].x /= 2.f; 
	aQuad[2].y /= 2.f; 
	aQuad[3].x /= 2.f; 
	aQuad[3].y /= 2.f; 

	if( SUCCEEDED( pVB->Lock( 0, 0, &pVBData, D3DLOCK_DISCARD ) ) )
	{
		CopyMemory( pVBData, aQuad, 4 * sizeof(QuadVertex) );
		pVB->Unlock();
	}

	pd3dDevice->SetStreamSource( 0, pVB, 0, sizeof(QuadVertex) ) ;


	_pd3dDevice->SetRenderTarget(0,m_SBloomSuf);
	_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET,0xffffffff, 1.0f, 0L );
	_postProcessElements[0]->m_pEffect->SetTexture( "bloom1", m_STempTex );
	PP.m_pEffect->SetTechnique( "BrightPassFilterBlurV" ); //设置技术 

	PP.m_pEffect->Begin( &cPasses, 0 );
	for( p = 0; p < cPasses; ++p )
	{
		if (SUCCEEDED(PP.m_pEffect->BeginPass( p )))
		{		
			//draw
			pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 ) ;
			PP.m_pEffect->EndPass() ;

		}
	}

	PP.m_pEffect->End();

	if(0) //纵向模糊图
		D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, m_SBloomTexture, 0);

	




	aQuad[1].x *= 4.f; 
	aQuad[2].y *= 4.f; 
	aQuad[3].x *= 4.f; 
	aQuad[3].y *= 4.f; 

	if( SUCCEEDED( pVB->Lock( 0, 0, &pVBData, D3DLOCK_DISCARD ) ) )
	{
		CopyMemory( pVBData, aQuad, 4 * sizeof(QuadVertex) );
		pVB->Unlock();
	}

	pd3dDevice->SetStreamSource( 0, pVB, 0, sizeof(QuadVertex) ) ;



	//7合成
	LPDIRECT3DSURFACE9 _temp;
	s_RTChain[0].m_pRenderTarget[0]->GetSurfaceLevel(0,&_temp);
	_pd3dDevice->SetRenderTarget( 0, _temp );
	_temp->Release();
	_temp = NULL;


	_pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET,0x00000000, 1.0f, 0L );

	_postProcessElements[0]->m_pEffect->SetTexture( "bloom2", m_SBloomTexture );//模糊图 屏幕大小 高光通过模糊图
	_postProcessElements[0]->m_pEffect->SetTexture( "ScrSceneTexture", _pSceneSaveRT[0] );//模糊图 屏幕大小
	_postProcessElements[0]->m_pEffect->SetTexture( "luminance", m_SluminanceTexture );//设置亮度图
   
    PP.m_pEffect->SetTechnique( "TRenderQuad" ); //设置技术 

	PP.m_pEffect->Begin( &cPasses, 0 );
	for( p = 0; p < cPasses; ++p )
	{
		if (SUCCEEDED(PP.m_pEffect->BeginPass( p )))
		{		
			//draw
			pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 ) ;
			PP.m_pEffect->EndPass() ;

		}
	}
	PP.m_pEffect->End();

	if(0) //原图
	{
		D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, m_SBloomTexture, 0);
		D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, _pSceneSaveRT[0], 0);
		D3DXSaveTextureToFile( "D:\\test.jpg", D3DXIFF_JPG, m_SluminanceTexture, 0);
	}


	_nLastTargetIndex = 0;
	
	
	


  
	
}