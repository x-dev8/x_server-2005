/********************************************************************
	created:	2008/05/20
	created:	20:5:2008   14:34
	filename: 	d:\work\whu\Sample\SimpleSample\PostProcessManager.h
	file path:	d:\work\whu\Sample\SimpleSample
	file base:	PostProcessManager
	file ext:	h
	author:		whu
	
	purpose:	全屏特效管理器。
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

    /** 初始化资源。
        Exception: std::exception.
    */
    void initialize( IDirect3DDevice9* pd3dDevice, LPCSTR szQuadEffectFilename, bool bOpenEx = false );

    /** 销毁资源。
    */
    void shutdown();

    /** 当显示设备丢失时调用来重新初始化资源。
        Exception: std::exception.
    */
    virtual void restoreDeviceObjects( IDirect3DDevice9* pd3dDevice, size_t screenWidth, size_t screenHeight );

    /** 当显示设备丢失时调用来销毁资源。
        Exception: std::exception.
    */
    virtual void invalidateDeviceObjects();

    /** 添加一个全屏特效。
    */
    void addPostProcessEffect( PostProcessEffect* pEffect );

    /** 移除名为name的全屏特效。
    */
    void removePostProcessEffect( const std::string& name );

    /** 渲染全屏特效。
        Exception: std::exception.
    */
    void render();

    /** 授权使用Post Process。
    */
    void enablePostProcess( bool enabled ) { _bEnabled = enabled; }

    /** 是否使用Post Process。
    */
    bool enablePostProcess() const { return _bEnabled; }	

	/** 是否使用multi-render target
	*/
	bool enableMultiRenderTarget() const { return _bEnableMultiRTs; }

	/** 设置PostProcessEffect对应的变量值。
	*/
	void setParameter( const std::string& paramName, const D3DXVECTOR2& value );

	/** 设置PostProcessEffect对应的变量值。
	*/
	void setParameter( const std::string& paramName, const D3DXVECTOR3& value );
    /** 设置PostProcessEffect对应的变量值。
    */
	void setParameter( const std::string& paramName, const D3DXVECTOR4& value );
	D3DXVECTOR4* getParameterVector4( const std::string& paramName ) const;

	/** 设置PostProcessEffect对应的变量值。
	*/
	void setParameter( const std::string& paramName, const D3DXMATRIXA16& value );
	D3DXMATRIXA16* getParameterMatrix16( const std::string& paramName ) const;

	/** 获得position的rt
	*/
	IDirect3DSurface9* getPositionRenderTarget(){ return _pScenePositionRTSurface; }

	/** 开启/关闭某个特效
	*/
	void enableProcess( const char* pszName, bool bEnable );

	/** update position rt
	*/
	void updateMultiRenderTarget();

	/** 更新render target 给需要的effect
	*/
	void updateRenderTargetToEffect();

	void SetBrightNContrast( float fB, const D3DXVECTOR3& vC ){ _fOffsetBrightness = fB; _vOffsetContrast = vC; }
	const D3DXVECTOR3& GetContrast() const { return _vOffsetContrast; }
	float GetBrightness() const{ return _fOffsetBrightness; }

	/** 设置cross-postprocessing曲线图
	*/
	void SetCrossPostProcessingTexture( const std::string& strFilename );
	void SetCrossPostProcessingTexture( IDirect3DTexture9* pTexture ) { _pCrossPostProcessingTexture = pTexture; }
	IDirect3DTexture9* GetCrossPostPrcessingTexture() const { return _pCrossPostProcessingTexture; }

	/** 开启额外功能
	*/
	void OpenEx( bool bOpen ){ _bOpenEx= bOpen; }

	/** 储存/恢复临时rt
	*/
	void saveTempRenderTarget();
	void restoreTempRenderTarget();

	LPDIRECT3DTEXTURE9 GetSceneRT() const { return _pSceneRT; }
	LPDIRECT3DSURFACE9 GetSceneRTSuf() {return _pSceneRTSurface;}

	void ScretchRectToTexture( bool bDelTarget = true );	

	PostProcessEffect* GetPostProcessEffect(const char* pString);
protected:
    PostProcessManager();

	/** 授权使用multi-render target
	*/
	void _enableMultiRenderTarget( bool bEnableMultiRTs );

    /** 渲染场景前调用，更新RenderTarget，用于渲染全屏特效时使用。
    Exception: std::exception.
    */
    void _preRenderTargetUpdate();

    /** 渲染Post Process好的贴图到全屏去。
    */
    void _renderQuad(IDirect3DTexture9* tex);

    static PostProcessManager* _instance;

	typedef std::map< std::string, PostProcessEffect* > PostProcessEffectMap;
	PostProcessEffectMap _postProcessEffectMap;

    IDirect3DDevice9*            _pd3dDevice;
    IDirect3DTexture9*           _pSceneRT;     /// 渲染场景的RenderTarget，用于后期处理特效。
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

    IDirect3DSurface9*           _pSceneDS;     /// 渲染场景的DepthStencilSurface，用于后期处理特效。
    IDirect3DSurface9*           _pOldRT;       /// 保存渲染场景旧的RenderTarget。
    IDirect3DVertexDeclaration9* _pVertDecl;    /// Vertex decl for post-processing
    ID3DXEffect*                 _pEffect;
    size_t                       _screenWidth;
    size_t                       _screenHeight;
    bool                         _bInitialize;
    bool                         _bEnabled;      /// 可以使用Post Process。
	bool						 _bEnableMultiRTs; // multi-rendertarget
	float						 _fOffsetBrightness;
	D3DXVECTOR3					 _vOffsetContrast;
	IDirect3DTexture9*			 _pCrossPostProcessingTexture; // for cross-postprocessing
};
