/********************************************************************
	created:	2008/05/20
	created:	20:5:2008   14:35
	filename: 	d:\work\whu\Sample\SimpleSample\PostProcess.h
	file path:	d:\work\whu\Sample\SimpleSample
	file base:	PostProcess
	file ext:	h
	author:		whu
	
	purpose:	全屏特效。
*********************************************************************/

#pragma once
#include "Me3d/Me3d.h"

//
//  static assert.
//
#ifndef BOOST_STATIC_ASSERT
namespace boost{

    // HP aCC cannot deal with missing names for template value parameters
    template <bool x> struct STATIC_ASSERTION_FAILURE;

    template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };

    // HP aCC cannot deal with missing names for template value parameters
    template<int x> struct static_assert_test{};

}

#define BOOST_STATIC_ASSERT( B ) \
    typedef ::boost::static_assert_test<\
    sizeof(::boost::STATIC_ASSERTION_FAILURE< (bool)( B ) >)\
    > boost_static_assert_typedef_

#endif

//
//  release define.
//
#ifndef Safe_Release
    #define Safe_Release( v ) if( v ) { (v)->Release(); (v) = NULL; }
#endif

#ifndef Safe_Delete
    #define Safe_Delete( v ) if( v ) { delete (v); (v) = NULL; }
#endif

//--------------------------------------------------------------------------------------
// struct PostProcessElement
// A struct that encapsulates aspects of a render target PostProcess
// technique.
//--------------------------------------------------------------------------------------
struct PostProcessElement : public MeCommonAllocObj<PostProcessElement>
{
    const static int NUM_PARAMS = 5;
    const static int MAX_CHAR_NUM = 256;
    const static int RT_COUNT = 1;

    LPD3DXEFFECT m_pEffect;              // Effect object for this technique
    D3DXHANDLE   m_hTPostProcess;        // PostProcess technique handle
    int          m_nRenderTarget;        // Render target channel this PP outputs
    D3DXHANDLE   m_hTexSource[4];        // Handle to the post-process source textures
    D3DXHANDLE   m_hTexScene[4];         // Handle to the saved scene texture
    bool         m_bWrite[4];            // Indicates whether the post-process technique
    //   outputs data for this render target.
    struct Parameter
    {
        D3DXHANDLE  hParam;
        D3DXVECTOR4 paramVectorValue;
		D3DXMATRIXA16 paramMatrixValue;
        int         paramSize;
        std::string paramName;
        std::string paramDesc;

        Parameter() : hParam( NULL ),
            paramSize(0)
        {
        }
    };

    typedef std::map< std::string, Parameter >  Parameters;

    Parameters   parametersVector;
	Parameters   parametersMatrix;

public:
    PostProcessElement();
    ~PostProcessElement() { Cleanup(); }

    HRESULT Init( LPDIRECT3DDEVICE9 pDev, DWORD dwShaderFlags, LPCSTR wszName );
    void Cleanup();
    HRESULT OnLostDevice();
    HRESULT OnResetDevice( DWORD dwWidth, DWORD dwHeight );
};

// 目前只支持1个RenderTarget。
BOOST_STATIC_ASSERT( PostProcessElement::RT_COUNT == 1 );

//--------------------------------------------------------------------------------------
// struct RenderTargetChain
//--------------------------------------------------------------------------------------
struct RenderTargetChain
{
    int m_nNext;
    bool m_bFirstRender;
    LPDIRECT3DTEXTURE9 m_pRenderTarget[2];

public:
    RenderTargetChain() : m_nNext( 0 ), m_bFirstRender( true )
    {
        memset( m_pRenderTarget, 0, sizeof(m_pRenderTarget) );
    }

    ~RenderTargetChain()
    {
        Cleanup();
    }

    void Init( LPDIRECT3DTEXTURE9 *pRT )
    {
        for( int i = 0; i < 2; ++i )
        {
            m_pRenderTarget[i] = pRT[i];
            m_pRenderTarget[i]->AddRef();
        }
    }

    void Cleanup()
    {
        for ( int i = 0; i < 2; ++i )
        {
            Safe_Release( m_pRenderTarget[i] );
        }
    }

    void Flip() { m_nNext = 1 - m_nNext; };

    LPDIRECT3DTEXTURE9 GetPrevTarget() { return m_pRenderTarget[1 - m_nNext]; }
    LPDIRECT3DTEXTURE9 GetPrevSource() { return m_pRenderTarget[m_nNext]; }
    LPDIRECT3DTEXTURE9 GetNextTarget() { return m_pRenderTarget[m_nNext]; }
    LPDIRECT3DTEXTURE9 GetNextSource() { return m_pRenderTarget[1 - m_nNext]; }
};

/** Post process effect.
*/
class PostProcessEffect : public MeCommonAllocObj<PostProcessEffect>
{
public:
    struct QuadVertex 
    {
        float x, y, z, w;
        float u, v;
        float u2, v2;     // Texcoord for the original scene

        const static D3DVERTEXELEMENT9 Decl[4];
    };

    PostProcessEffect( const std::string& name );
    virtual ~PostProcessEffect();

    /** 得到PostProcessEffect实例名。
    */
    const std::string& getName() const { return _name; }

    /** 初始化资源。
    Exception: std::exception.
    @param FxDirectory Post Process shader .fx file directory。
    */
    virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "", bool bNeedMultiRTs = false );

    /** 销毁资源。
    */
    virtual void destroy();

    /** 当显示设备丢失时调用来重新初始化资源。
    Exception: std::exception.
    */
    virtual void restoreDeviceObjects( IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight );

    /** 当显示设备丢失时调用来销毁资源。
    Exception: std::exception.
    */
    virtual void invalidateDeviceObjects();

    /** 渲染场景前调用，更新RenderTarget，用于渲染全屏特效时使用。
    Exception: std::exception.
    */
    virtual void preRenderTargetUpdate();

    /** 渲染全屏特效。
    Exception: std::exception.
    */
    virtual void render( IDirect3DTexture9* pSceneRT );

	/** 渲染全屏特效,添加position信息。
	*/
	virtual void render( IDirect3DTexture9* pSceneRT , IDirect3DTexture9* pScenePositionRT );

    /** 得到最终全屏处理好的RenderTarget。
    */
    IDirect3DTexture9* getFinalTexture() {  return s_RTChain[0].m_pRenderTarget[_nLastTargetIndex]; }

    /** 设置PostProcessElement对应的变量值。
    */
    void setParameter( const std::string& paramName, const D3DXVECTOR4& value );
	D3DXVECTOR4* getParameterVector4( const std::string& paramName ) const;

	/** 设置PostProcessElement对应的变量值。
    */
    void setParameter( const std::string& paramName, const D3DXMATRIXA16& value );
	D3DXMATRIXA16* getParameterMatrix16( const std::string& paramName ) const;

	/** 是否开启
	*/
	void enable( bool bEnable ){ _bEnable = bEnable; }
	
	/** 是否开启
	*/
	bool enable() { return _bEnable; }

	/** 是否需要multi-rendertarget
	*/
	bool needMultiRenderTarget(){ return _bNeedMultiRTs; }

	/** update render target to effect
	*/
	virtual void updateRenderTargetToEffect(){};

protected:
    /** 渲染单个全屏特效。
    Exception: std::exception.
    */
    virtual void _singlePostProcess( IDirect3DDevice9 *pd3dDevice, PostProcessElement &PP,
                    IDirect3DVertexBuffer9 *pVB, QuadVertex *aQuad, float &fExtentX, float &fExtentY );

    /** 添加一个全屏特效处理单元。
    */
    PostProcessElement* _addPostProcessElement( LPCSTR FxDirectory, LPCSTR FxFilename );


    IDirect3DDevice9*               _pd3dDevice;
    IDirect3DTexture9*              _pSceneSaveRT[PostProcessElement::RT_COUNT];  // To save original scene image before PostProcess
    IDirect3DVertexDeclaration9*    _pVertDeclPP;                                 // Vertex decl for post-processing
    static RenderTargetChain	    s_RTChain[PostProcessElement::RT_COUNT];       // Render target chain (4 used in sample)
    size_t                          _screenWidth;
    size_t                          _screenHeight;
    QuadVertex                      _quadVertex[4];
    std::vector<PostProcessElement*> _postProcessElements;
    std::string                     _name;
	bool							_bNeedMultiRTs;
	bool							_bEnable;									  // 是否开启该process
	int								_nLastTargetIndex;
};

/** LightShaft post process effect
*/
class LightShaftProcessEffect : public PostProcessEffect
{	
public:
	LightShaftProcessEffect( const std::string& name );
	virtual ~LightShaftProcessEffect();

	/** 初始化资源。
	*/
	virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "", bool bNeedMultiRTs = false );

	/** 销毁资源。
	*/
	virtual void destroy();

	/** 当显示设备丢失时调用来重新初始化资源。
	Exception: std::exception.
	*/
	virtual void restoreDeviceObjects( IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight );

	/** 当显示设备丢失时调用来销毁资源。
	Exception: std::exception.
	*/
	virtual void invalidateDeviceObjects();

	/** 渲染全屏特效。
	*/
	virtual void render( IDirect3DTexture9* pSceneRT );

	/** update render target to effect
	*/
	virtual void updateRenderTargetToEffect();

	/** get sun surface
	*/
	IDirect3DSurface9* getSunSurface(){ if(!_checkSunSurface())
											return 0; 
										return m_pSurfaceSun; }

protected:
	bool _checkSunSurface();

protected:
	IDirect3DTexture9* m_pTexSun;
	IDirect3DSurface9* m_pSurfaceSun;

};

/** Glow post process effect.
*/
class GlowPostProcessEffect : public PostProcessEffect
{
public:
    GlowPostProcessEffect( const std::string& name );
    virtual ~GlowPostProcessEffect();

    /** 初始化资源。
    Exception: std::exception.
    @param FxDirectory Post Process shader .fx file directory。
    */
    virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "", bool bNeedMultiRTs = false );

    /** 销毁资源。
    */
    virtual void destroy();

    /** 当显示设备丢失时调用来重新初始化资源。
    Exception: std::exception.
    */
    virtual void restoreDeviceObjects( IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight );

    /** 当显示设备丢失时调用来销毁资源。
    Exception: std::exception.
    */
    virtual void invalidateDeviceObjects();

    /** 渲染全屏特效。
    Exception: std::exception.
    */
    virtual void render( IDirect3DTexture9* pSceneRT );
};

/** Bloom post process effect.
*/
class BloomPostProcessEffect : public PostProcessEffect
{
public:
    BloomPostProcessEffect( const std::string& name );
    virtual ~BloomPostProcessEffect();

    /** 初始化资源。
    Exception: std::exception.
    @param FxDirectory Post Process shader .fx file directory。
    */
    virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "", bool bNeedMultiRTs = false );

    /** 销毁资源。
    */
    virtual void destroy();
};

/** Blur post process effect.
*/
class BlurPostProcessEffect : public PostProcessEffect
{
public:
    BlurPostProcessEffect( const std::string& name );
    virtual ~BlurPostProcessEffect();

    /** 初始化资源。
    Exception: std::exception.
    @param FxDirectory Post Process shader .fx file directory。
    */
    virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "", bool bNeedMultiRTs = false );

    /** 销毁资源。
    */
    virtual void destroy();
};

/** Shadow blur post process effect.
*/
class ShadowBlurPostProcessEffect : public PostProcessEffect
{
public:
    ShadowBlurPostProcessEffect( const std::string& name );
    virtual ~ShadowBlurPostProcessEffect();

    /** 初始化资源。
    Exception: std::exception.
    @param FxDirectory Post Process shader .fx file directory。
    */
    virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "");

    /** 销毁资源。
    */
    virtual void destroy();
};

//lyh++ hdr effect shader : hdr.fxo
class HdrPostProcessEffect : public PostProcessEffect
{
public:
	HdrPostProcessEffect( const std::string& name );
	virtual ~HdrPostProcessEffect();

public:

	LPDIRECT3DTEXTURE9 m_SBaseTexture; //缩小版的图片
	LPDIRECT3DSURFACE9 m_SBaseSuf;

	LPDIRECT3DTEXTURE9 m_SluminanceTexture; //缩小版的亮度图
	LPDIRECT3DSURFACE9 m_SluminanceSuf; 


	LPDIRECT3DTEXTURE9 m_SBloomTexture; //缩小版的模糊图
	LPDIRECT3DSURFACE9 m_SBloomSuf;    


	LPDIRECT3DTEXTURE9 m_STempTex; //缩小版的模糊图
	LPDIRECT3DSURFACE9 m_STempSuf;   


	//===========================================================
	//下面这两张图先写上 ，不用的时候给删除

	LPDIRECT3DTEXTURE9 m_BloomTexture; //原大小的模糊图 不要了
	LPDIRECT3DSURFACE9 m_BloomSuf;    


	LPDIRECT3DTEXTURE9 m_BaseTexture; //想对画面模糊的图 现在不用了
	LPDIRECT3DSURFACE9 m_BaseSuf;    

	LPDIRECT3DTEXTURE9 m_BaseTexture1; //想对画面模糊的图 现在不用了
	LPDIRECT3DSURFACE9 m_BaseSuf1;    


	LPDIRECT3DTEXTURE9 m_BaseTexture2; //想对画面模糊的图 现在不用了
	LPDIRECT3DSURFACE9 m_BaseSuf2;    


	LPDIRECT3DTEXTURE9 m_BloomBaseTexture; //想对画面模糊的图 现在不用了
	LPDIRECT3DSURFACE9 m_BloomBaseSuf; 


	//===============================================================
	LPDIRECT3DTEXTURE9 m_TempSceneTexture; //想对画面模糊的图 现在不用了
	LPDIRECT3DSURFACE9 m_TempSceneSuf; 


	
	
	 virtual void restoreDeviceObjects( IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight );

	 /** 当显示设备丢失时调用来销毁资源。
	 Exception: std::exception.
	 */
	 virtual void invalidateDeviceObjects();
	/** 初始化资源。
	Exception: std::exception.
	@param FxDirectory Post Process shader .fx file directory。
	*/
	virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "");

	/** 销毁资源。
	*/
	virtual void destroy();

	virtual void _singlePostProcess( IDirect3DDevice9 *pd3dDevice, PostProcessElement &PP,
		IDirect3DVertexBuffer9 *pVB, QuadVertex *aQuad, float &fExtentX, float &fExtentY );
};
