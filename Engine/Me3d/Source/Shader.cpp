#include "Me3d/Shader.h"
#include "Me3d/Material.h"
//#include "Launcher/DataLauncher.h"
namespace graphics
{
    //------------------------------------------------
    //          Shader class
    //------------------------------------------------
    Shader::Shader(const std::string& name, const std::string& shaderType, IDirect3DDevice9* pDevice ) : _name( name ),
        _shaderType( shaderType ), _pDevice( pDevice )
    {
    }

    Shader::~Shader()
    {
    }

    void Shader::begin( const Material& material )
    {
        const ShaderParametersList& paramsList = material.getShaderParametersList();
        ShaderParametersList::const_iterator it, end = paramsList.end();
        for ( it = paramsList.begin(); it != end; ++it )
        {
            IShaderParameters& params = *(*it);
            params.begin();
            while ( params.hasValue() )
            {
                if ( params.type() == typeid(IDirect3DTexture9*) )
                {
                    void* ppTex = const_cast<void*>( params.value() );
                    _setParameter( params.key(), *static_cast<IDirect3DTexture9**>(ppTex) );
                }
                else
                {
                    _setParameter( params.key(), params.value(), params.valueBytes() );
                }
                params.next();
            }
        }
    }


    //------------------------------------------------
    //          ShaderEffect class
    //------------------------------------------------
    ShaderEffect::ShaderEffect( const std::string& name, IDirect3DDevice9* pDevice, const std::string& effectFilename ) : Shader( name, "ShaderEffect", pDevice ),
        _currenPass(0), _passNum(0), _pEffect( NULL )
    {
        _create( pDevice, effectFilename );
    }

    ShaderEffect::~ShaderEffect()
    {
        _destory();
    }

    void ShaderEffect::_create(IDirect3DDevice9* pDevice, const std::string& effectFilename )
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
        DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;

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
		LPD3DXBUFFER _error;
		if(FAILED(D3DXCreateEffectFromFile( pDevice, effectFilename.c_str(), NULL, NULL, dwShaderFlags, 
			NULL, &_pEffect, &_error )))
		{

			MessageBox(NULL,(char*)(_error->GetBufferPointer()),"",MB_OK);

			FILE	* fp = fopen(effectFilename.c_str(),"rb");
			if (!fp)
			{
				std::string error = "打开(";
				error =  error + effectFilename +") 失败！";
				assert( 0 && "无法打开shader文件。" );				
				STD_ThrowException( error.c_str() );				
			}
			
			if (FAILED( D3DXCreateEffect( pDevice, fp->_ptr,
				fp->_cnt, NULL, NULL, dwShaderFlags, NULL, &_pEffect, &_error ) ) )
			{
				if(_error)
				MessageBox(NULL,(char*)(_error->GetBufferPointer()),"",MB_OK);

				assert( 0 && "创建ID3DXEffect失败！" );
				std::string error = "创建(";
				error =  error + effectFilename + ") ID3DXEffect失败！";
				
				STD_ThrowException( error.c_str() );
			}
			fclose(fp);
		}

    }

    void ShaderEffect::_destory()
    {
        if ( _pEffect )
        {
            _pEffect->Release();
            _pEffect = NULL;
        }
    }

    void ShaderEffect::restoreDeviceObjects( IDirect3DDevice9* pDevice)
    {
		Shader::restoreDeviceObjects(pDevice);

        HRESULT hr = _pEffect->OnResetDevice();
        assert( hr == S_OK );
    }

    void ShaderEffect::invalidateDeviceObjects()
	{
		Shader::invalidateDeviceObjects();

        HRESULT hr = _pEffect->OnLostDevice();
        assert( hr == S_OK );
    }

	void ShaderEffect::begin( const Material& material )
	{
		Shader::begin( material );

		HRESULT hr;
		hr = _pEffect->SetTechnique( _technique.c_str() );
		assert( hr == S_OK );
		hr = _pEffect->Begin( &_passNum, 0 );
		assert( hr == S_OK );
		_currenPass = 0;
	}

	void ShaderEffect::begin()
	{
		HRESULT hr;
		hr = _pEffect->SetTechnique( _technique.c_str() );
		assert( hr == S_OK );
		hr = _pEffect->Begin( &_passNum, 0 );
		assert( hr == S_OK );
		_currenPass = 0;
	}

	void ShaderEffect::end()
	{
		HRESULT hr = _pEffect->End();
		assert( hr == S_OK );
	}

	bool ShaderEffect::beginPass()
	{
		return beginPass( _currenPass );
	}

	bool ShaderEffect::beginPass(unsigned int i )
	{
		if ( i >= _passNum )
		{
			return false;
		}
		HRESULT hr = _pEffect->BeginPass( i );
		assert( hr == S_OK );
		return hr == S_OK;
	}

	void ShaderEffect::endPass()
	{
		HRESULT hr = _pEffect->EndPass();
		assert( hr == S_OK );

		++_currenPass;
	}

	void ShaderEffect::_setParameter(const std::string& name, const void* value, unsigned int bytes )
	{
		_pEffect->SetValue( name.c_str(), value, bytes );
	}

	void ShaderEffect::_setParameter(const std::string& name, const IDirect3DTexture9* value )
	{
		_pEffect->SetTexture( name.c_str(), const_cast<IDirect3DTexture9*>(value) );
	}


    //------------------------------------------------
    //          ShaderVertexPixel class
    //------------------------------------------------
    ShaderVertexPixel::ShaderVertexPixel( const std::string& name, IDirect3DDevice9* pDevice,
        const std::string& vertexShaderFilename, const std::string& vertexShaderFuncName,
        const std::string& pixelShaderFilename, const std::string& pixelShaderFuncName,
        const std::string& vsVersion, const std::string& psVersion  ) : Shader( name, "ShaderVertexPixel", pDevice ),
        _pVertexShader( NULL ), _pVSConstanTable( NULL ),
        _pPixelShader( NULL ), _pPSConstanTable( NULL ),
        _pOldVertexShader( NULL ), _pOldPixelShader( NULL ),
        _bBegining( false ),
		_vertexShaderFilename(vertexShaderFilename), _vertexShaderFuncName(vertexShaderFuncName),
		_pixelShaderFilename(pixelShaderFilename), _pixelShaderFuncName(pixelShaderFuncName),
		_vsVersion(vsVersion), _psVersion(psVersion)
    {
        _create( pDevice, vertexShaderFilename, vertexShaderFuncName,
            pixelShaderFilename, pixelShaderFuncName,
            vsVersion, psVersion );
    }

    ShaderVertexPixel::~ShaderVertexPixel()
    {
        _destory();
    }

    void ShaderVertexPixel::_create(IDirect3DDevice9* pDevice,
        const std::string& vertexShaderFilename, const std::string& vertexShaderFuncName,
        const std::string& pixelShaderFilename, const std::string& pixelShaderFuncName,
        const std::string& vsVersion, const std::string& psVersion )
    {
        ID3DXBuffer* pCode = NULL;
		LPD3DXBUFFER pError = NULL;

		DWORD flag = 0;
		if (psVersion.find("ps_1") != std::string::npos)
			flag = D3DXSHADER_USE_LEGACY_D3DX9_31_DLL;

        if ( vertexShaderFilename != "" )
        {
			FILE	* fp = fopen(vertexShaderFilename.c_str(),"rb");
			if (!fp)
			{
				std::string error = "打开(";
				error =  error + vertexShaderFilename +") 失败！";
				assert( 0 && "无法打开shader文件。" );
				STD_ThrowException( error.c_str() );				
			}

			fseek ( fp, 0, SEEK_END );
			long nSize = ftell( fp ) + 1;
			rewind( fp );

			char* code = new char[nSize+1];
			memset(code, 0, sizeof(char)*(nSize+1));
			fread(code, sizeof(char), nSize, fp);
			fclose( fp );

			if ( FAILED( D3DXCompileShader(code, nSize, NULL, NULL,
				vertexShaderFuncName.c_str(), vsVersion.c_str(),
				flag, &pCode, &pError, &_pVSConstanTable) ) )
			{
				delete[] code;

				std::string error;
				error = error + "Failed to call D3DXCompileShader (" +
					vertexShaderFuncName.c_str() + ") in the file " + vertexShaderFilename.c_str() + "\n";
				error  = error + " - " + static_cast<const char*>(pError->GetBufferPointer());
				STD_ThrowException( error.c_str() );
			}

			delete[] code;

            if( FAILED( pDevice->CreateVertexShader( reinterpret_cast< DWORD* >( pCode->GetBufferPointer() ), &_pVertexShader ) ) )
            {
                std::string error;
                error = error + "Failed to call CreateVertexShader (" +
                    vertexShaderFuncName.c_str() + ") in the file " + vertexShaderFilename.c_str() + "\n";
                STD_ThrowException( error.c_str() );
            }

            if ( pCode )
            {
                pCode->Release();
                pCode = NULL;
            }
        }

        if ( pixelShaderFilename != "" )
		{
			FILE	* fp = fopen(pixelShaderFilename.c_str(),"rb");
			if (!fp)
			{
				std::string error = "打开(";
				error =  error + pixelShaderFilename +") 失败！";
				assert( 0 && "无法打开shader文件。" );
				STD_ThrowException( error.c_str() );				
			}

			fseek ( fp, 0, SEEK_END );
			long nSize = ftell( fp ) + 1;
			rewind( fp );

			char* code = new char[nSize+1];
			memset(code, 0, sizeof(char)*(nSize+1));
			fread(code, sizeof(char), nSize, fp);
			fclose( fp );

			if ( FAILED( D3DXCompileShader(code, nSize, NULL, NULL,
				pixelShaderFuncName.c_str(), psVersion.c_str(),
				flag, &pCode, &pError, &_pPSConstanTable) ) )
			{
				delete[] code;

				std::string error;
				error = error + "Failed to call D3DXCompileShader (" +
					pixelShaderFuncName.c_str() + ") in the file " + pixelShaderFilename.c_str() + "\n";
				error  = error + " - " + static_cast<const char*>(pError->GetBufferPointer());
				STD_ThrowException( error.c_str() );
			}

			delete[] code;

            if( FAILED( pDevice->CreatePixelShader( reinterpret_cast< DWORD* >( pCode->GetBufferPointer() ), &_pPixelShader ) ) )
            {
                std::string error;
                error = error + "Failed to call CreateVertexShader (" +
                    pixelShaderFuncName.c_str() + ") in the file " + pixelShaderFilename.c_str() + "\n";
                STD_ThrowException( error.c_str() );
			}

            if ( pCode )
            {
                pCode->Release();
                pCode = NULL;
            }
        }

		initContant();
    }

    void ShaderVertexPixel::_destory()
    {
        if ( _pVertexShader )
        {
            _pVertexShader->Release();
            _pVertexShader = NULL;
        }
        if ( _pVSConstanTable )
        {
            _pVSConstanTable->Release();
            _pVSConstanTable = NULL;
        }
        if ( _pPixelShader )
        {
            _pPixelShader->Release();
            _pPixelShader = NULL;
        }
        if ( _pPSConstanTable )
        {
            _pPSConstanTable->Release();
            _pPSConstanTable = NULL;
        }
        if ( _pOldVertexShader )
        {
            _pOldPixelShader->Release();
            _pOldPixelShader = NULL;
        }
        if ( _pOldPixelShader )
        {
            _pOldPixelShader->Release();
            _pOldPixelShader = NULL;
        }
	}

	void ShaderVertexPixel::restoreDeviceObjects( IDirect3DDevice9* pDevice)
	{
		Shader::restoreDeviceObjects(pDevice);
		_create(pDevice, _vertexShaderFilename, _vertexShaderFuncName, _pixelShaderFilename, _pixelShaderFuncName,
			_vsVersion, _psVersion);
	}

	void ShaderVertexPixel::invalidateDeviceObjects()
	{
		_destory();
	}

	void  ShaderVertexPixel::initContant()
	{
		if (_pVSConstanTable)
		{
			_VSConstants[SCT_World]					= _pVSConstanTable->GetConstantByName( NULL, "world" );
			_VSConstants[SCT_WorldViewProjection]	= _pVSConstanTable->GetConstantByName( NULL, "worldViewProj" );
			_VSConstants[SCT_ViewProjection]		= _pVSConstanTable->GetConstantByName( NULL, "viewProj" );
			_VSConstants[SCT_LightDirection]		= _pVSConstanTable->GetConstantByName( NULL, "lightDir" );
			_VSConstants[SCT_LightAmbient]			= _pVSConstanTable->GetConstantByName( NULL, "lightAmbient" );
			_VSConstants[SCT_LightDiffuse]			= _pVSConstanTable->GetConstantByName( NULL, "lightDiffuse" );
			_VSConstants[SCT_Alpha]					= _pVSConstanTable->GetConstantByName( NULL, "alpha" );
			_VSConstants[SCT_Timer]					= _pVSConstanTable->GetConstantByName( NULL, "timer" );
			_VSConstants[SCT_Eye]					= _pVSConstanTable->GetConstantByName( NULL, "eye" );
			_VSConstants[SCT_Specular]				= _pVSConstanTable->GetConstantByName( NULL, "specular" );
			_VSConstants[SCT_ShadowMapMatrix]		= _pVSConstanTable->GetConstantByName( NULL, "shadowTexMatrix" );
			_VSConstants[SCT_LightViewProjection]	= _pVSConstanTable->GetConstantByName( NULL, "lightViewProj" );
			_VSConstants[SCT_UseShadow]				= _pVSConstanTable->GetConstantByName( NULL, "bRenderShadow" );
			_VSConstants[SCT_BoneWorldMatrix]		= _pVSConstanTable->GetConstantByName( NULL, "boneWorldMatrix" );
			_VSConstants[SCT_LightmapScale]			= _pVSConstanTable->GetConstantByName( NULL, "vLightmapScale" );
			_VSConstants[SCT_LightmapOffset]		= _pVSConstanTable->GetConstantByName( NULL, "vLightmapOffset" );
			
		}

		if (_pPSConstanTable)
		{
			_PSConstants[SCT_World]					= _pPSConstanTable->GetConstantByName( NULL, "world" );
			_PSConstants[SCT_WorldViewProjection]	= _pPSConstanTable->GetConstantByName( NULL, "worldViewProj" );
			_PSConstants[SCT_ViewProjection]		= _pPSConstanTable->GetConstantByName( NULL, "viewProj" );
			_PSConstants[SCT_LightDirection]		= _pPSConstanTable->GetConstantByName( NULL, "lightDir" );
			_PSConstants[SCT_LightAmbient]			= _pPSConstanTable->GetConstantByName( NULL, "lightAmbient" );
			_PSConstants[SCT_LightDiffuse]			= _pPSConstanTable->GetConstantByName( NULL, "lightDiffuse" );
			_PSConstants[SCT_Alpha]					= _pPSConstanTable->GetConstantByName( NULL, "alpha" );
			_PSConstants[SCT_Timer]					= _pPSConstanTable->GetConstantByName( NULL, "timer" );
			_PSConstants[SCT_Eye]					= _pPSConstanTable->GetConstantByName( NULL, "eye" );
			_PSConstants[SCT_Specular]				= _pPSConstanTable->GetConstantByName( NULL, "specular" );
			_PSConstants[SCT_ShadowMapMatrix]		= _pPSConstanTable->GetConstantByName( NULL, "shadowTexMatrix" );
			_PSConstants[SCT_LightViewProjection]	= _pPSConstanTable->GetConstantByName( NULL, "lightViewProj" );
			_PSConstants[SCT_UseShadow]				= _pPSConstanTable->GetConstantByName( NULL, "bRenderShadow" );
			_PSConstants[SCT_BoneWorldMatrix]		= _pPSConstanTable->GetConstantByName( NULL, "boneWorldMatrix" );
			_PSConstants[SCT_LightmapScale]			= _pPSConstanTable->GetConstantByName( NULL, "vLightmapScale" );
			_PSConstants[SCT_LightmapOffset]		= _pPSConstanTable->GetConstantByName( NULL, "vLightmapOffset" );
		}
	}

    void ShaderVertexPixel::begin( const Material& material )
    {
        Shader::begin( material );
        _bBegining = true;
    }

    void ShaderVertexPixel::end()
    {
        _bBegining = false;
    }

    bool ShaderVertexPixel::beginPass()
    {
        return beginPass( 0 );
    }

	bool ShaderVertexPixel::beginPass(unsigned int )
    {
        if ( !_bBegining )
        {
            return false;
        }

        HRESULT hr;
        if ( _pVertexShader )
        {
            hr = _pDevice->SetVertexShader( _pVertexShader );
            assert( hr == S_OK );
        }

        if ( _pPixelShader )
        {
            hr = _pDevice->SetPixelShader( _pPixelShader);
            assert( hr == S_OK );
        }
        return true;
    }

    void ShaderVertexPixel::endPass()
    {
        _pDevice->SetVertexShader( NULL );
        _pDevice->SetPixelShader( NULL );
        _bBegining = false;
	}

	void ShaderVertexPixel::setVertexProgramParameter(const std::string& name, const void* value, unsigned int bytes )
	{
		if ( _pVSConstanTable )
		{
			HRESULT hr;
			hr = _pVSConstanTable->SetValue( _pDevice, name.c_str(), value, bytes );
			assert(hr == S_OK);
		}
	}

	void ShaderVertexPixel::setPixelProgramParameter(const std::string& name, const void* value, unsigned int bytes )
	{
		if ( _pPSConstanTable )
		{
			HRESULT hr;
			hr = _pPSConstanTable->SetValue( _pDevice, name.c_str(), value, bytes );
			assert(hr == S_OK);
		}
	}

    void ShaderVertexPixel::_setParameter(const std::string& name, const void* value, unsigned int bytes )
    {
        if ( _pVSConstanTable )
        {
            _pVSConstanTable->SetValue( _pDevice, name.c_str(), value, bytes );
        }
        if ( _pPSConstanTable )
        {
            _pPSConstanTable->SetValue( _pDevice, name.c_str(), value, bytes );
        }
    }

    void ShaderVertexPixel::_setParameter(const std::string& name, const IDirect3DTexture9* value )
    {
        TextureStageIndies::iterator it = _texStageIndies.find( name );
        if ( it != _texStageIndies.end() )
        {
            _pDevice->SetTexture( it->second, const_cast<IDirect3DTexture9*>(value) );
        }
    }
}
