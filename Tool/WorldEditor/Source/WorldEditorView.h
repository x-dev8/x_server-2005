// WorldEditView.h : interface of the CWorldEditView class
//
#pragma once
#include <vector>
#include <afxmt.h>
#include "Edit/BaseTool.h"
#include "D3DApp.h"

enum znDisplayFilter
{
	znDF_None		= 0,
	znDF_Bound		= 0x01,
	znDF_Texture	= 0x02,
	znDF_Shadow		= 0x04,
	znDF_Horizontal	= 0x08,
	znDF_Liquid		= 0x10,
	znDF_Model		= 0x20,
	znDF_Env		= 0x40,
	znDF_Animation	= 0x80,
	znDF_Doodad     = 0x100,
	znDF_Zone       = 0x200,
	znDF_MultiSel   = 0x400,
	znDF_MultiSelTexture = 0x800,
	znDF_FreeBlock	=	 0x1000,
	znDF_SlopeCheck =	 0x2000,
	znDF_RenderMinimap = 0x4000,
	znDF_ShowAABB =		 0x8000,
	znDF_ShowFog = 0x10000,

	znDF_ShowLightView = 0x20000, //这个实际用来做 地形的凹凸效果开关。
	znDF_ShowShadowMapEffect = 0x40000,
	znDF_ShowTerrainBump = 0x80000,


	znDF_Flight	= 0x40000000
};

#define znDisplayNormal		(znDF_Texture|znDF_Shadow)

struct TPickResult;
class CNdlHelper;
class SwShader;
class CToolManager;
class CNdlEditWorldPicker;
class swLuaScript;
class CWorldEditView : public CView, public CD3DApplication
{
protected: // create from serialization only
	CWorldEditView();
	DECLARE_DYNCREATE(CWorldEditView)

// Attributes
public:
	CMutex *pWTMutex;
	CPoint paintCsr;
	HCTX hCtx;
	unsigned prev_pkButtons;
	LOGCONTEXT lc;
	ID3DXFont*				m_pFont;
	bool                    m_BSaveShowmap;
	LPDIRECT3DTEXTURE9      m_TempShadowMap ;
	D3DXMATRIX              m_LightWVPMat;

	CWorldEditDoc*	GetDocument() const;
	virtual			~CWorldEditView();

	void			Update( flt32 totalTime, flt32 deltaTime );
	//void			Render(float totalTime, float deltaTime );

	void			DrawTabletCursor();
	void			Reset();
	virtual void	Activate(BOOL bActivate)		{ m_isActive = bActivate; }
	inline BOOL		IsActive(void) { return m_isActive; }

	bool			GetViewSize( flt32& width, flt32& height ) { width = m_viewSize.x; height = m_viewSize.y; return true; };
	SwCamera*		GetActiveCamera();		

	sInt32			PickWorldTerrain( const CPoint& point, sInt32 pickType = emPT_Terrain);
	bool			GetRayFromPoint( const CPoint& point, Vector& outRayPt, Vector& outRayDir);
	void			SetActivePos( flt32 posX, flt32 posY );

	const TPickResult&		GetPickResult() const	{ return m_pickResult; };
	const CNdlEditWorldPicker*	GetWorldPicker() const	{ Assert( NULL != m_worldPick ); return m_worldPick; };
	CNdlEditWorldPicker* GetWorldPicker() { Assert( NULL != m_worldPick ); return m_worldPick; };

	CToolManager*	GetToolManager() const			{ Assert( NULL != m_toolManager ); return m_toolManager; };
	//CLayerEditWnd*	GetLayerEditWnd() const			{ Assert( NULL != m_layerEditWnd ); return m_layerEditWnd; };
	//CLayerBrushWnd*	GetLayerBrushWnd() const		{ Assert( NULL != m_layerBrushWnd ); return m_layerBrushWnd; };
	
	CNdlHelper*		GetHelper()						{ Assert( NULL != m_helper ); return m_helper; };

	bool			IsUseDynamicLight() { return m_bUseDynamicLight; }

	bool			IsViewDebugMsg() { return m_bViewDebugMsg; }

public:
	virtual void	OnInitialUpdate();

	void			UpdateRoot();
	virtual void	OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL	PreCreateWindow(CREATESTRUCT& cs);
	virtual void	OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);

	void			SetActiveCameraID(uInt32 val);
	uInt32			GetActiveCameraID();
	void			ResetCamera();
	virtual BOOL	LoadFxShader();

	uInt32			GetDisplayFilter() const { return m_displayFilter; }

	swLuaScript* GetLua() const { return m_Lua; }

#ifdef _DEBUG
	virtual void	AssertValid() const;
	virtual void	Dump(CDumpContext& dc) const;
#endif
	afx_msg LRESULT OnWTPacket(WPARAM, LPARAM);

protected:
	bool			CreateNdlRender();
	void			ReCreateNdlRender();

	void			OnIdle();

	void			UpdateStatusBar();
	void			UpdateHorizontal( const Vector& pos );

	bool			CreateDefaultCamera( int gridX, int gridY );
	
	// 在窗口尺寸更改时，或更换摄像机后调用
	void			ResizeActiveCamera();	

	bool			CreateHelper();


	bool			IsAvailable();

// Generated message map functions
protected:
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnPaint();
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL	OnEraseBkgnd( CDC* pDC );
	afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void	OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void	OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void	OnRButtonDown(UINT nFlags, CPoint point);

	afx_msg void	OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL	OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
	afx_msg void	OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void	OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );
	afx_msg void	OnTimer( UINT nIDEvent );

	afx_msg void	OnUndo();
	afx_msg void	OnUpdateUndo(CCmdUI* pCmdUI);
	afx_msg void	OnRedo();
	afx_msg void	OnUpdateRedo(CCmdUI* pCmdUI);

	afx_msg void	OnLockVertex();
	afx_msg void	OnUpdateLockVertex(CCmdUI* pCmdUI);
	afx_msg void	OnEditObject();
	afx_msg void	OnUpdateEditObject(CCmdUI* pCmdUI);
	afx_msg void	OnEditCamera();
	afx_msg void	OnEditGameCamera();
	afx_msg void	OnUpdateEditCamera(CCmdUI* pCmdUI);
	afx_msg void	OnUpdateGameCamera(CCmdUI* pCmdUI);
	afx_msg void	OnDisplayChunk();
	afx_msg void	OnUpdateDisplayChunk(CCmdUI* pCmdUI);
	afx_msg void	OnDislpayNormal();
	afx_msg void	OnUpdateDisplayNormal(CCmdUI* pCmdUI);
	afx_msg void	OnDisplayTexture();
	afx_msg void	OnUpdateDisplayTexture(CCmdUI* pCmdUI);
	afx_msg void	OnDisplayShadow();
	afx_msg void	OnUpdateDisplayShadow(CCmdUI* pCmdUI);
	afx_msg void	OnDisplayBoundBox();
	afx_msg void	OnUpdateDisplayBoundBox(CCmdUI* pCmdUI);
	afx_msg void	OnChaseCamera();
	afx_msg void	OnUpdateChaseCamera(CCmdUI* pCmdUI);
	afx_msg void	OnDisplayGrid();
	afx_msg void	OnUpdateDisplayGrid(CCmdUI* pCmdUI);
	afx_msg void	OnDisplayLiquid();
	afx_msg void	OnUpdateDisplayLiquid(CCmdUI* pCmdUI);
	afx_msg void	OnDisplayModel();
	afx_msg void	OnDisplayDoodad();
	afx_msg void    OnRenderMinimap();
	afx_msg void    OnRenderLightView();
	afx_msg void    OnRenderShowMapScene();
	afx_msg void    OnRenderShowTerrainBumap();

	
	afx_msg void    OnShowAABB();
	afx_msg void    OnShowFog();
	afx_msg void	OnUpdateDisplayModel(CCmdUI* pCmdUI);
	afx_msg void	OnUpdateDisplayDoodad(CCmdUI* pCmdUI);
	afx_msg void	OnDisplayEnv();	
	afx_msg void	OnDisplayZone();	
	afx_msg void	OnDisplayAnimation();	
	afx_msg void	OnChangeLod();	
	afx_msg void	OnMonsterShow();	
	afx_msg void	OnUpdateDisplayEnv(CCmdUI* pCmdUI);
	afx_msg void	OnUpdateDisplayZone(CCmdUI* pCmdUI);
	afx_msg void	OnUpdateRenderMinimap(CCmdUI* pCmdUI);
	afx_msg void    OnUpdateRenderLightView(CCmdUI* pCmdUI);

	afx_msg void    OnUpdateRenderShadowMapScene(CCmdUI* pCmdUI);
	afx_msg void    OnUpdateRenderTerrainBump(CCmdUI* pCmdUI);

	afx_msg void	OnUpdateShowAABB(CCmdUI* pCmdUI);
	afx_msg void	OnUpdateShowFog(CCmdUI* pCmdUI);
	afx_msg void	OnUpdateDisplayAnimation(CCmdUI* pCmdUI);
	afx_msg void	OnGenerateLightMap();
	afx_msg void	OnSettingLightMap();
	afx_msg void	OnGenerateMeshLightMap();
	afx_msg void	OnSettingTerrainLayer();
	afx_msg void	OnLoadSkybox();

	afx_msg void	OnPaintNormal();

	//afx_msg void	OnCleanModel();
	afx_msg void	OnSelectFilter();
	afx_msg void	OnSelectFilterEx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void	OnUpdateSelectFilterEx(CCmdUI* pCmdUI);
	afx_msg void	OnSelectNameGroup();

	afx_msg void	OnEditMove();
	afx_msg void	OnUpdateEditMove(CCmdUI* pCmdUI);
	afx_msg void	OnEditRotate();
	afx_msg void	OnUpdateEditRotate(CCmdUI* pCmdUI);
	afx_msg void	OnEditScale();
	afx_msg void	OnUpdateEditScale(CCmdUI* pCmdUI);
	afx_msg void    OnMultiSel();
	afx_msg void    OnUpdateMultiSel(CCmdUI* pCmdUI);
	afx_msg void    OnMultiSelTexture();
	afx_msg void    OnUpdateMultiSelTexture(CCmdUI* pCmdUI);
	afx_msg void	OnFreeBlock();
	afx_msg void	OnUpdateFreeBlock(CCmdUI* pCmdUI);
	afx_msg void	OnSlopeCheck();
	afx_msg void	OnUpdateSlopeCheck(CCmdUI* pCmdUI);
	afx_msg void	OnColiCheck();
	afx_msg void	OnUpdateColiCheck(CCmdUI* pCmdUI);
	afx_msg void	OnUseDynamicLight();
	afx_msg void	OnUpdateUseDynamicLight(CCmdUI* pCmdUI);
	afx_msg void	OnViewDebugMsg();
	afx_msg void	OnUpdateViewDebugMsg(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

protected:
	HWND			m_hTopLevelHwnd;

	BOOL			m_isActive;		
	bool			m_isCorrect3D;
	bool			m_needRecreateRender;
	Vector2		m_viewSize;

	uInt32			m_activeCameraID;
	// 可以生成很多摄像机,用来调试显示地图．
	std::vector<SwCamera*>	m_cameraList;
	
	CNdlHelper*		m_helper;

	CToolManager*	m_toolManager;
	ToolID			m_lastTool;

	CNdlEditWorldPicker*	m_worldPick;
	TPickResult		m_pickResult;

	sInt32			m_displayMode;
	uInt32			m_displayFilter;
	sInt32			m_brushType;
	sInt32			m_brushMode;
	sInt32			m_brushSize;
	swLuaScript*		m_Lua;
	bool			m_bUseDynamicLight; // 是否使用动态光源，否则使用lightmap
	bool			m_bViewDebugMsg;
	//added by zilong.2011-01-15
	bool m_bSetLocation;

	CString			m_strCurRoadShadow;
public:
	void SetLocationFlag(){m_bSetLocation = true;}
	void ResetLocationFlag(){m_bSetLocation = false;}
	bool IsSetLocation(){return m_bSetLocation;}
private:
	HRESULT ConfirmDevice( D3DCAPS9*,DWORD,D3DFORMAT );
	HRESULT OneTimeSceneInit();
	HRESULT InitDeviceObjects();
	HRESULT RestoreDeviceObjects(bool bInitEngineInstance=true);
	HRESULT FrameMove();
	HRESULT Render(float totalTime, float deltaTime );
	HRESULT InvalidateDeviceObjects();
	HRESULT DeleteDeviceObjects();
	HRESULT FinalCleanup();
	virtual HRESULT AdjustWindowForChange();


// 	HRESULT		RenderToTexture();
// 	BOOL		RenderShadows();

public:
	afx_msg void OnOperationLocate();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
	afx_msg void OnSaveShMp();
};


#ifndef _DEBUG  // debug version in WorldEditView.cpp
inline CWorldEditDoc* CWorldEditView::GetDocument() const
   { return reinterpret_cast<CWorldEditDoc*>(m_pDocument); }
#endif

