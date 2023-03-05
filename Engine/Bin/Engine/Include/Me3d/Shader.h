#pragma once
#include "Me3d/Me3d.h"

namespace graphics
{
    class Material;

    /** Shader���ࡣ
    ʹ�÷�����
    begin();
        while beginPass()
            Draw();
        endPass();
    end();
    */
	class Shader : public MeCommonAllocObj<Shader>
    {
    protected:

    public:
        /** ���캯����
        */
        Shader( const std::string& name, const std::string& shaderType, IDirect3DDevice9* pDevice );

        /** ����������
        */
        virtual ~Shader();

        /** �õ�Shaderʵ�����ơ�
        */
        const std::string& getName() const { return _name; }

        /** �õ���Shader���ͣ���"ShaderEffect", "ShaderVertexPixel"��
        */
        const std::string& getShaderType() const { return _shaderType; }

        /** �豸����ʱ���á�
        */
        virtual void restoreDeviceObjects( IDirect3DDevice9* pDevice ) { _pDevice = pDevice; }

        /** �豸��ʧʱ���á�
        */
        virtual void invalidateDeviceObjects() {}

        /** ����Ҫ�����Technique��
        */
        virtual void setTechnique( const std::string& ) {}

        /** �õ�Ҫ�����Technique��
        */
		virtual const std::string& getTechnique() const { static std::string s; return s; }

        /** ��ʼ����һ��Technique��������shader��������Ⱦ�����֮ǰ���á�Exception: std::exception.
        */
		virtual void begin( const Material& material );

		/** ��ʼ����һ��Technique��������shader��������Ⱦ�����֮ǰ���á�Exception: std::exception.
		*/
		virtual void begin() {}

        /** ����ǰһ�������Technique����Ⱦ�����֮����á�
        */
        virtual void end() {}

        /** ��ʼ����һ��Pass����Ⱦ�����֮ǰ���á�
        */
        virtual bool beginPass() { return true; }

        /** ��ʼ�����i��Pass����Ⱦ�����֮ǰ���á�
        */
        virtual bool beginPass( unsigned int ) { return true; }

		/** ���pass����
		*/
		virtual void resetPassIndex(){}

        /** ����ǰһ�������Pass��ÿ����һ�θú�����ǰ������һ��Pass����Ⱦ�����֮����á�
        */
		virtual void endPass() {}

    protected:
        virtual void _setParameter( const std::string& name, const void* value, unsigned int bytes ) = 0;
        virtual void _setParameter( const std::string& name, const IDirect3DTexture9* value ) {}

        //
        // member variables;
        //
        std::string          _name;
        std::string          _shaderType;
        IDirect3DDevice9*    _pDevice;
    };

    /** ID3DXEffect shader.
    ʹ�÷�����
    begin();
        while beginPass()
            Draw();
        endPass();
    end();
    */
    class ShaderEffect : public Shader
    {
    public:
        /** ���캯����Exception: std::exception.
        */
        ShaderEffect( const std::string& name, IDirect3DDevice9* pDevice, const std::string& effectFilename );

        /** ����������
        */
        virtual ~ShaderEffect();

        /** �豸����ʱ���á�
        */
        virtual void restoreDeviceObjects( IDirect3DDevice9* pDevice );

        /** �豸��ʧʱ���á�
        */
        virtual void invalidateDeviceObjects();

        /** ����Ҫ�����Technique��
        */
        virtual void setTechnique( const std::string& technique ) { _technique = technique; }

        /** �õ�Ҫ�����Technique��
        */
        virtual const std::string& getTechnique() const { return _technique; }

        /** ��ʼ����һ��Technique��������shader��������Ⱦ�����֮ǰ���á�Exception: std::exception.
        */
		virtual void begin( const Material& material );

		/** ��ʼ����һ��Technique��������shader��������Ⱦ�����֮ǰ���á�Exception: std::exception.
		*/
		virtual void begin();

        /** ����ǰһ�������Technique����Ⱦ�����֮����á�
        */
        virtual void end();

        /** ��ʼ����һ��Pass����Ⱦ�����֮ǰ���á�
        */
        virtual bool beginPass();

        /** ��ʼ�����i��Pass����Ⱦ�����֮ǰ���á�
        */
        virtual bool beginPass( unsigned int i );

        /** ����ǰһ�������Pass��ÿ����һ�θú�����ǰ������һ��Pass����Ⱦ�����֮����á�
        */
        virtual void endPass();

		/** ���pass����
		*/
		virtual void resetPassIndex(){ _currenPass = 0; }

        /** �õ�D3DXEffect*
        */
		ID3DXEffect* getID3DXEffect() { return _pEffect; }

    protected:
        virtual void _create( IDirect3DDevice9* pDevice, const std::string& effectFilename );
        virtual void _destory();

        virtual void _setParameter( const std::string& name, const void* value, unsigned int bytes );
        virtual void _setParameter( const std::string& name, const IDirect3DTexture9* value );

        //
        // member variables.
        //
        unsigned int _currenPass;
        unsigned int _passNum;
        std::string  _technique;

        // shader variables.
        ID3DXEffect* _pEffect;
    };

    /** Vertex, pixel shader.
    ʹ�÷�����
    begin();
        while beginPass()
            Draw();
        endPass();
    end();
    */
    class ShaderVertexPixel : public Shader
    {
        typedef std::map<std::string, unsigned int> TextureStageIndies;

    public:
        /** ���캯����Exception: std::exception.
        */
        ShaderVertexPixel( const std::string& name, IDirect3DDevice9* pDevice,
            const std::string& vertexShaderFilename, const std::string& vertexShaderFuncName,
            const std::string& pixelShaderFilename, const std::string& pixelShaderFuncName,
            const std::string& vsVersion = "vs_2_0", const std::string& psVersion = "ps_2_0" );

        /** ����������
        */
		virtual ~ShaderVertexPixel();

		/** �豸����ʱ���á�
		*/
		virtual void restoreDeviceObjects( IDirect3DDevice9* pDevice );

		/** �豸��ʧʱ���á�
		*/
		virtual void invalidateDeviceObjects();

        /** ��ʼ����һ��Technique��������shader��������Ⱦ�����֮ǰ���á�Exception: std::exception.
        */
        virtual void begin( const Material& material );

        /** ����ǰһ�������Technique����Ⱦ�����֮����á�
        */
        virtual void end();

        /** ��ʼ����һ��Pass����Ⱦ�����֮ǰ���á�
        */
        virtual bool beginPass();

        /** ��ʼ�����i��Pass����Ⱦ�����֮ǰ���á�
        */
        virtual bool beginPass( unsigned int );

        /** ����ǰһ�������Pass��ÿ����һ�θú�����ǰ������һ��Pass����Ⱦ�����֮����á�
        */
        virtual void endPass();

        /** ������ͼ��Ӧ��������
        */
        void setTextureStageIndex( const std::string& texName, unsigned int index ) { _texStageIndies[texName] = index; }

        /** �õ�IDirect3DVertexShader9*
        */
        IDirect3DVertexShader9* getVertexShader() { return _pVertexShader; }

        /** �õ�Vertex ID3DXConstantTable*
        */
        ID3DXConstantTable* getVertexShaderConstantTable() { return _pVSConstanTable; }

        /** �õ�IDirect3DPixelShader9*
        */
        IDirect3DPixelShader9* getPixelShader() { return _pPixelShader; }

        /** �õ�Pixel ID3DXConstantTable*
        */
		ID3DXConstantTable* getPixelShaderConstantTable() { return _pPSConstanTable; }

		enum ShaderConstantType
		{
			SCT_World,
			SCT_WorldViewProjection,
			SCT_ViewProjection,
			SCT_LightDirection,
			SCT_LightAmbient,
			SCT_LightDiffuse,
			SCT_Alpha,
			SCT_Eye,
			SCT_Specular,
			SCT_ShadowMapMatrix,
			SCT_LightViewProjection,
			SCT_UseShadow,
			SCT_BoneWorldMatrix,
			SCT_Timer,
			SCT_LightmapScale,
			SCT_LightmapOffset,

			SCT_Count
		};

		void setVertexProgramParameter( const std::string& name, const void* value, unsigned int bytes );
		void setPixelProgramParameter( const std::string& name, const void* value, unsigned int bytes );

		void setVertexProgramParameterMatrixArray( ShaderConstantType type, const D3DXMATRIX* value, unsigned int count ) {
			HRESULT hr = _pVSConstanTable->SetMatrixArray(_pDevice, _VSConstants[type], value, count);
			assert(hr == S_OK);
		}
		void setPixelProgramParameterMatrixArray( ShaderConstantType type, const D3DXMATRIX* value, unsigned int count ) {
			HRESULT hr = _pPSConstanTable->SetMatrixArray(_pDevice, _PSConstants[type], value, count);
			assert(hr == S_OK);
		}
		void setVertexProgramParameterMatrix( ShaderConstantType type, const D3DXMATRIX* value ) {
			HRESULT hr = _pVSConstanTable->SetMatrix(_pDevice, _VSConstants[type], value);
			assert(hr == S_OK);
		}
		void setPixelProgramParameterMatrix( ShaderConstantType type, const D3DXMATRIX* value ) {
			HRESULT hr = _pPSConstanTable->SetMatrix(_pDevice, _PSConstants[type], value);
			assert(hr == S_OK);
		}
		void setVertexProgramParameterFloatArray( ShaderConstantType type, const float* value, unsigned int count ) {
			HRESULT hr = _pVSConstanTable->SetFloatArray(_pDevice, _VSConstants[type], value, count);
			assert(hr == S_OK);
		}
		void setPixelProgramParameterFloatArray( ShaderConstantType type, const float* value, unsigned int count ) {
			HRESULT hr = _pPSConstanTable->SetFloatArray(_pDevice, _PSConstants[type], value, count);
			assert(hr == S_OK);
		}
		void setVertexProgramParameterFloat( ShaderConstantType type, float value ) {
			HRESULT hr = _pVSConstanTable->SetFloat(_pDevice, _VSConstants[type], value);
			assert(hr == S_OK);
		}
		void setPixelProgramParameterFloat( ShaderConstantType type, float value ) {
			HRESULT hr = _pPSConstanTable->SetFloat(_pDevice, _PSConstants[type], value);
			assert(hr == S_OK);
		}
		void setVertexProgramParameterIntArray( ShaderConstantType type, const int* value, unsigned int count ) {
			HRESULT hr = _pVSConstanTable->SetIntArray(_pDevice, _VSConstants[type], value, count);
			assert(hr == S_OK);
		}
		void setPixelProgramParameterIntArray( ShaderConstantType type, const int* value, unsigned int count ) {
			HRESULT hr = _pPSConstanTable->SetIntArray(_pDevice, _PSConstants[type], value, count);
			assert(hr == S_OK);
		}
		void setVertexProgramParameterInt( ShaderConstantType type, int value ) {
			HRESULT hr = _pVSConstanTable->SetInt(_pDevice, _VSConstants[type], value);
			assert(hr == S_OK);
		}
		void setPixelProgramParameterInt( ShaderConstantType type, int value ) {
			HRESULT hr = _pPSConstanTable->SetInt(_pDevice, _PSConstants[type], value);
			assert(hr == S_OK);
		}
		void setVertexProgramParameterBoolArray( ShaderConstantType type, const BOOL* value, unsigned int count ) {
			HRESULT hr = _pVSConstanTable->SetBoolArray(_pDevice, _VSConstants[type], value, count);
			assert(hr == S_OK);
		}
		void setPixelProgramParameterBoolArray( ShaderConstantType type, const BOOL* value, unsigned int count ) {
			HRESULT hr = _pPSConstanTable->SetBoolArray(_pDevice, _PSConstants[type], value, count);
			assert(hr == S_OK);
		}
		void setVertexProgramParameterBool( ShaderConstantType type, BOOL value ) {
			HRESULT hr = _pVSConstanTable->SetBool(_pDevice, _VSConstants[type], value);
			assert(hr == S_OK);
		}
		void setPixelProgramParameterBool( ShaderConstantType type, BOOL value ) {
			HRESULT hr = _pPSConstanTable->SetBool(_pDevice, _PSConstants[type], value);
			assert(hr == S_OK);
		}
		void setVertexProgramParameter( ShaderConstantType type, const void* value, unsigned int bytes ) {
			HRESULT hr = _pVSConstanTable->SetValue(_pDevice, _VSConstants[type], value, bytes);
			assert(hr == S_OK);
		}
		void setPixelProgramParameter( ShaderConstantType type, const void* value, unsigned int bytes ) {
			HRESULT hr = _pPSConstanTable->SetValue(_pDevice, _PSConstants[type], value, bytes);
			assert(hr == S_OK);
		}

    protected:
        virtual void _create( IDirect3DDevice9* pDevice,
            const std::string& vertexShaderFilename, const std::string& vertexShaderFuncName,
            const std::string& pixelShaderFilename, const std::string& pixelShaderFuncName,
            const std::string& vsVersion = "vs_2_0", const std::string& psVersion = "ps_2_0" );
        virtual void _destory();

        virtual void _setParameter( const std::string& name, const void* value, unsigned int bytes );
        virtual void _setParameter( const std::string& name, const IDirect3DTexture9* value );

		void initContant();

        //
        // member variables.
        //
        IDirect3DVertexShader9* _pVertexShader;
        ID3DXConstantTable*     _pVSConstanTable;
        IDirect3DPixelShader9*  _pPixelShader;
        ID3DXConstantTable*     _pPSConstanTable;
        IDirect3DVertexShader9* _pOldVertexShader;
        IDirect3DPixelShader9*  _pOldPixelShader;
        bool                    _bBegining;
        TextureStageIndies      _texStageIndies;

		std::string _vertexShaderFilename;
		std::string _vertexShaderFuncName;
		std::string _pixelShaderFilename;
		std::string _pixelShaderFuncName;
		std::string _vsVersion;
		std::string _psVersion;

		D3DXHANDLE				_VSConstants[SCT_Count];
		D3DXHANDLE				_PSConstants[SCT_Count];
    };
}
