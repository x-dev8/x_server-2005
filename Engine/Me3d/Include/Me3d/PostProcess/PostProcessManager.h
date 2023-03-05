/********************************************************************
	created:	2008/05/20
	created:	20:5:2008   14:34
	filename: 	d:\work\whu\Sample\SimpleSample\PostProcessManager.h
	file path:	d:\work\whu\Sample\SimpleSample
	file base:	PostProcessManager
	file ext:	h
	author:		whu
	
	purpose:	ȫ����Ч��������
*********************************************************************/

#pragma once
#include "Me3d/Me3d.h"

class PostProcessEffect;

class PostProcessManager : public MeCommonAllocObj<PostProcessManager>
{
public:
    ~PostProcessManager();

    static PostProcessManager& instance()
    {
        if ( !_instance )
        {
            _instance = MeNew PostProcessManager();
        }
        return *_instance;
    }

    static PostProcessManager* instancePtr()
    {
        if ( !_instance )
        {
            _instance = MeNew PostProcessManager();
        }
        return _instance;
    }

    /** ��ʼ����Դ��
        Exception: std::exception.
    */
    void initialize( IDirect3DDevice9* pd3dDevice, LPCSTR szQuadEffectFilename, bool bOpenEx = false );

    /** ������Դ��
    */
    void shutdown();

    /** ����ʾ�豸��ʧʱ���������³�ʼ����Դ��
        Exception: std::exception.
    */
    virtual void restoreDeviceObjects( IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight );

    /** ����ʾ�豸��ʧʱ������������Դ��
        Exception: std::exception.
    */
    virtual void invalidateDeviceObjects();

    /** ���һ��ȫ����Ч��
    */
    void addPostProcessEffect( PostProcessEffect* pEffect );

    /** �Ƴ���Ϊname��ȫ����Ч��
    */
    void removePostProcessEffect( const std::string& name );

    /** ��Ⱦȫ����Ч��
        Exception: std::exception.
    */
    void render();

    /** ��Ȩʹ��Post Process��
    */
    void enablePostProcess( bool enabled ) { _bEnabled = enabled; }

    /** �Ƿ�ʹ��Post Process��
    */
    bool enablePostProcess() const { return _bEnabled; }	

	/** �Ƿ�ʹ��multi-render target
	*/
	bool enableMultiRenderTarget() const { return _bEnableMultiRTs; }

	/** ����PostProcessEffect��Ӧ�ı���ֵ��
	*/
	void setParameter( const std::string& paramName, const D3DXVECTOR2& value );

	/** ����PostProcessEffect��Ӧ�ı���ֵ��
	*/
	void setParameter( const std::string& paramName, const D3DXVECTOR3& value );
    /** ����PostProcessEffect��Ӧ�ı���ֵ��
    */
	void setParameter( const std::string& paramName, const D3DXVECTOR4& value );
	D3DXVECTOR4* getParameterVector4( const std::string& paramName ) const;

	/** ����PostProcessEffect��Ӧ�ı���ֵ��
	*/
	void setParameter( const std::string& paramName, const D3DXMATRIXA16& value );
	D3DXMATRIXA16* getParameterMatrix16( const std::string& paramName ) const;

	/** ���position��rt
	*/
	IDirect3DSurface9* getPositionRenderTarget(){ return _pScenePositionRTSurface; }

	/** ����/�ر�ĳ����Ч
	*/
	void enableProcess( const char* pszName, bool bEnable );

	/** update position rt
	*/
	void updateMultiRenderTarget();

	/** ����render target ����Ҫ��effect
	*/
	void updateRenderTargetToEffect();

	void SetBrightNContrast( float fB, const D3DXVECTOR3& vC ){ _fOffsetBrightness = fB; _vOffsetContrast = vC; }
	const D3DXVECTOR3& GetContrast() const { return _vOffsetContrast; }
	float GetBrightness() const{ return _fOffsetBrightness; }

	/** ����cross-postprocessing����ͼ
	*/
	void SetCrossPostProcessingTexture( const std::string& strFilename );
	void SetCrossPostProcessingTexture( IDirect3DTexture9* pTexture ) { _pCrossPostProcessingTexture = pTexture; }
	IDirect3DTexture9* GetCrossPostPrcessingTexture() const { return _pCrossPostProcessingTexture; }

	/** �������⹦��
	*/
	void OpenEx( bool bOpen ){ _bOpenEx= bOpen; }

	/** ����/�ָ���ʱrt
	*/
	void saveTempRenderTarget();
	void restoreTempRenderTarget();

	LPDIRECT3DTEXTURE9 GetSceneRT() const { return _pSceneRT; }
	LPDIRECT3DSURFACE9 GetSceneRTSuf() {return _pSceneRTSurface;}

	void ScretchRectToTexture( bool bDelTarget = true );	

	PostProcessEffect* GetPostProcessEffect(const char* pString);
protected:
    PostProcessManager();

	/** ��Ȩʹ��multi-render target
	*/
	void _enableMultiRenderTarget( bool bEnableMultiRTs );

    /** ��Ⱦ����ǰ���ã�����RenderTarget��������Ⱦȫ����Чʱʹ�á�
    Exception: std::exception.
    */
    void _preRenderTargetUpdate();

    /** ��ȾPost Process�õ���ͼ��ȫ��ȥ��
    */
    void _renderQuad(IDirect3DTexture9* tex);

    static PostProcessManager* _instance;

	typedef std::map< std::string, PostProcessEffect* > PostProcessEffectMap;
	PostProcessEffectMap _postProcessEffectMap;

    IDirect3DDevice9*            _pd3dDevice;
    IDirect3DTexture9*           _pSceneRT;     /// ��Ⱦ������RenderTarget�����ں��ڴ�����Ч��
	IDirect3DSurface9*			 _pSceneRTSurface;
	// added, jiayi, [2009.5.5]
	IDirect3DTexture9*			 _pScenePositionRT; //position info
	IDirect3DSurface9*			 _pScenePositionRTSurface;//position surface

	// ex
	bool						 _bOpenEx;

	// added, jiayi, [2009.5.10], for save
	IDirect3DTexture9*			 _pDefaultRenderTargetTempTexture;
	IDirect3DSurface9*			 _pDefaultRenderTargetTempSurface;
	IDirect3DTexture9*			 _pZPositionRenderTargetTempTexture;
	IDirect3DSurface9*			 _pZPositionRenderTargetTempSurface;

    IDirect3DSurface9*           _pSceneDS;     /// ��Ⱦ������DepthStencilSurface�����ں��ڴ�����Ч��
    IDirect3DSurface9*           _pOldRT;       /// ������Ⱦ�����ɵ�RenderTarget��
    IDirect3DVertexDeclaration9* _pVertDecl;    /// Vertex decl for post-processing
    ID3DXEffect*                 _pEffect;
    size_t                       _screenWidth;
    size_t                       _screenHeight;
    bool                         _bInitialize;
    bool                         _bEnabled;      /// ����ʹ��Post Process��
	bool						 _bEnableMultiRTs; // multi-rendertarget
	float						 _fOffsetBrightness;
	D3DXVECTOR3					 _vOffsetContrast;
	IDirect3DTexture9*			 _pCrossPostProcessingTexture; // for cross-postprocessing
};
