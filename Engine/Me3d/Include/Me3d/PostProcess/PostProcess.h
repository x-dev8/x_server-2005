/********************************************************************
	created:	2008/05/20
	created:	20:5:2008   14:35
	filename: 	d:\work\whu\Sample\SimpleSample\PostProcess.h
	file path:	d:\work\whu\Sample\SimpleSample
	file base:	PostProcess
	file ext:	h
	author:		whu
	
	purpose:	ȫ����Ч��
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

// Ŀǰֻ֧��1��RenderTarget��
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

    /** �õ�PostProcessEffectʵ������
    */
    const std::string& getName() const { return _name; }

    /** ��ʼ����Դ��
    Exception: std::exception.
    @param FxDirectory Post Process shader .fx file directory��
    */
    virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "", bool bNeedMultiRTs = false );

    /** ������Դ��
    */
    virtual void destroy();

    /** ����ʾ�豸��ʧʱ���������³�ʼ����Դ��
    Exception: std::exception.
    */
    virtual void restoreDeviceObjects( IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight );

    /** ����ʾ�豸��ʧʱ������������Դ��
    Exception: std::exception.
    */
    virtual void invalidateDeviceObjects();

    /** ��Ⱦ����ǰ���ã�����RenderTarget��������Ⱦȫ����Чʱʹ�á�
    Exception: std::exception.
    */
    virtual void preRenderTargetUpdate();

    /** ��Ⱦȫ����Ч��
    Exception: std::exception.
    */
    virtual void render( IDirect3DTexture9* pSceneRT );

	/** ��Ⱦȫ����Ч,���position��Ϣ��
	*/
	virtual void render( IDirect3DTexture9* pSceneRT , IDirect3DTexture9* pScenePositionRT );

    /** �õ�����ȫ������õ�RenderTarget��
    */
    IDirect3DTexture9* getFinalTexture() {  return s_RTChain[0].m_pRenderTarget[_nLastTargetIndex]; }

    /** ����PostProcessElement��Ӧ�ı���ֵ��
    */
    void setParameter( const std::string& paramName, const D3DXVECTOR4& value );
	D3DXVECTOR4* getParameterVector4( const std::string& paramName ) const;

	/** ����PostProcessElement��Ӧ�ı���ֵ��
    */
    void setParameter( const std::string& paramName, const D3DXMATRIXA16& value );
	D3DXMATRIXA16* getParameterMatrix16( const std::string& paramName ) const;

	/** �Ƿ���
	*/
	void enable( bool bEnable ){ _bEnable = bEnable; }
	
	/** �Ƿ���
	*/
	bool enable() { return _bEnable; }

	/** �Ƿ���Ҫmulti-rendertarget
	*/
	bool needMultiRenderTarget(){ return _bNeedMultiRTs; }

	/** update render target to effect
	*/
	virtual void updateRenderTargetToEffect(){};

protected:
    /** ��Ⱦ����ȫ����Ч��
    Exception: std::exception.
    */
    virtual void _singlePostProcess( IDirect3DDevice9 *pd3dDevice, PostProcessElement &PP,
                    IDirect3DVertexBuffer9 *pVB, QuadVertex *aQuad, float &fExtentX, float &fExtentY );

    /** ���һ��ȫ����Ч����Ԫ��
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
	bool							_bEnable;									  // �Ƿ�����process
	int								_nLastTargetIndex;
};

/** LightShaft post process effect
*/
class LightShaftProcessEffect : public PostProcessEffect
{	
public:
	LightShaftProcessEffect( const std::string& name );
	virtual ~LightShaftProcessEffect();

	/** ��ʼ����Դ��
	*/
	virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "", bool bNeedMultiRTs = false );

	/** ������Դ��
	*/
	virtual void destroy();

	/** ����ʾ�豸��ʧʱ���������³�ʼ����Դ��
	Exception: std::exception.
	*/
	virtual void restoreDeviceObjects( IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight );

	/** ����ʾ�豸��ʧʱ������������Դ��
	Exception: std::exception.
	*/
	virtual void invalidateDeviceObjects();

	/** ��Ⱦȫ����Ч��
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

    /** ��ʼ����Դ��
    Exception: std::exception.
    @param FxDirectory Post Process shader .fx file directory��
    */
    virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "", bool bNeedMultiRTs = false );

    /** ������Դ��
    */
    virtual void destroy();

    /** ����ʾ�豸��ʧʱ���������³�ʼ����Դ��
    Exception: std::exception.
    */
    virtual void restoreDeviceObjects( IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight );

    /** ����ʾ�豸��ʧʱ������������Դ��
    Exception: std::exception.
    */
    virtual void invalidateDeviceObjects();

    /** ��Ⱦȫ����Ч��
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

    /** ��ʼ����Դ��
    Exception: std::exception.
    @param FxDirectory Post Process shader .fx file directory��
    */
    virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "", bool bNeedMultiRTs = false );

    /** ������Դ��
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

    /** ��ʼ����Դ��
    Exception: std::exception.
    @param FxDirectory Post Process shader .fx file directory��
    */
    virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "", bool bNeedMultiRTs = false );

    /** ������Դ��
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

    /** ��ʼ����Դ��
    Exception: std::exception.
    @param FxDirectory Post Process shader .fx file directory��
    */
    virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "");

    /** ������Դ��
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

	LPDIRECT3DTEXTURE9 m_SBaseTexture; //��С���ͼƬ
	LPDIRECT3DSURFACE9 m_SBaseSuf;

	LPDIRECT3DTEXTURE9 m_SluminanceTexture; //��С�������ͼ
	LPDIRECT3DSURFACE9 m_SluminanceSuf; 


	LPDIRECT3DTEXTURE9 m_SBloomTexture; //��С���ģ��ͼ
	LPDIRECT3DSURFACE9 m_SBloomSuf;    


	LPDIRECT3DTEXTURE9 m_STempTex; //��С���ģ��ͼ
	LPDIRECT3DSURFACE9 m_STempSuf;   


	//===========================================================
	//����������ͼ��д�� �����õ�ʱ���ɾ��

	LPDIRECT3DTEXTURE9 m_BloomTexture; //ԭ��С��ģ��ͼ ��Ҫ��
	LPDIRECT3DSURFACE9 m_BloomSuf;    


	LPDIRECT3DTEXTURE9 m_BaseTexture; //��Ի���ģ����ͼ ���ڲ�����
	LPDIRECT3DSURFACE9 m_BaseSuf;    

	LPDIRECT3DTEXTURE9 m_BaseTexture1; //��Ի���ģ����ͼ ���ڲ�����
	LPDIRECT3DSURFACE9 m_BaseSuf1;    


	LPDIRECT3DTEXTURE9 m_BaseTexture2; //��Ի���ģ����ͼ ���ڲ�����
	LPDIRECT3DSURFACE9 m_BaseSuf2;    


	LPDIRECT3DTEXTURE9 m_BloomBaseTexture; //��Ի���ģ����ͼ ���ڲ�����
	LPDIRECT3DSURFACE9 m_BloomBaseSuf; 


	//===============================================================
	LPDIRECT3DTEXTURE9 m_TempSceneTexture; //��Ի���ģ����ͼ ���ڲ�����
	LPDIRECT3DSURFACE9 m_TempSceneSuf; 


	
	
	 virtual void restoreDeviceObjects( IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight );

	 /** ����ʾ�豸��ʧʱ������������Դ��
	 Exception: std::exception.
	 */
	 virtual void invalidateDeviceObjects();
	/** ��ʼ����Դ��
	Exception: std::exception.
	@param FxDirectory Post Process shader .fx file directory��
	*/
	virtual void create( IDirect3DDevice9* pd3dDevice, LPCSTR FxDirectory = "");

	/** ������Դ��
	*/
	virtual void destroy();

	virtual void _singlePostProcess( IDirect3DDevice9 *pd3dDevice, PostProcessElement &PP,
		IDirect3DVertexBuffer9 *pVB, QuadVertex *aQuad, float &fExtentX, float &fExtentY );
};
