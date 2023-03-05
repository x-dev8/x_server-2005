#pragma once
#include "Me3d/Me3d.h"

namespace graphics
{
    class Shader;

	class ShaderManager : public MeCommonAllocObj<ShaderManager>
    {
        typedef std::map< std::string, Shader* > Shaders;

    public:
        ~ShaderManager();

        static ShaderManager* instance()
        {
            if ( !_pInst )
            {
                _pInst = MeNew ShaderManager();
            }
            return _pInst;
        }

        void initialize( IDirect3DDevice9* pDevice );
        void shutdown();
		bool	LoadFxShader(const char* pRootPath)								;

        void restoreDeviceObjects( IDirect3DDevice9* pDevice );
        void invalidateDeviceObjects();

        void addShader( Shader* pEffect );
        Shader* getShader( const std::string& name );

        bool isUseShader() const { return _bUseShader; }
		void useShader( bool b )
		{ 
			// ǿ��ʹ��Shader
			//_bUseShader = b;
			_bUseShader = true;
		}

// 		bool isUseOuterShader() const { return _bUseOuterShader; }
// 		void useOuterShader( bool b ) { _bUseOuterShader = b; }

        /** Example: support D3DVS_VERSION( 2, 0 ).
        */
        bool supportVertexShader( unsigned int major, unsigned int minor ) const;

        /** Example: support D3DPS_VERSION( 2, 0 ).
        */
        bool supportPixelShader( unsigned int major, unsigned int minor ) const;

		bool supportSkeletonShader() const { return _bSupportSkeletonShader; }

		// added, [8/17/2010 zhangjiayi]
		// ����/�رչ�������
		void enableSkeletonShader( bool bEnable ){ _bSupportSkeletonShader = bEnable; }

		bool isRenderShadow() { return _bRenderShadow; }

		void beginRenderShadow(const D3DXVECTOR3& vEyeAt, const D3DXVECTOR3& vLookat,
			const D3DXVECTOR3& vViewDir, const D3DXVECTOR3& vLightDir);
		void endRenderShadow();

		void enableShadow(bool enable);
		bool isUseShadow() { return _bUseShadow; }

		LPDIRECT3DTEXTURE9 getShadowMap() { return _pShadowMap; }

		const D3DXMATRIXA16* getShadowMapMatrix() { return &_ShadowMapMatrix; }
		const D3DXMATRIXA16* getLightViewProjMatrix() { return &_LightViewProjMatrix; }

		void beginOutline();
		void endOutline();
		void enableOutline(bool enable){_bOutline = enable;}
		bool isUseOutline(){return _bOutline;}
    protected:
		ShaderManager();

		void setRenderShadow(bool v) { _bRenderShadow = v; }

        static ShaderManager* _pInst;

        IDirect3DDevice9* _pDevice;
        Shaders           _shaders;
        bool              _bUseShader;
		bool			  _bSupportSkeletonShader;
		D3DXMATRIXA16	  _ShadowMapMatrix;
		D3DXMATRIXA16	  _LightViewProjMatrix;

		//
		// ��Ӱ
		//
		LPDIRECT3DTEXTURE9 _pShadowMap;	
		LPDIRECT3DSURFACE9 _pShadowSurf;		// ��Ӱ��Ⱦ����ͼ�ı���
		LPDIRECT3DSURFACE9 _pShadowDepth;		// ��Ӱ��Ⱦ��� *****����û�ô�
		bool			   _bRenderShadow;

		LPDIRECT3DSURFACE9 _pRenderTarget;
		LPDIRECT3DSURFACE9 _pRenderTargetDepth;

		bool			   _bUseShadow;

		bool               _bOutline;   //����������
    };
}
