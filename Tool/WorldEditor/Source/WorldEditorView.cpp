// WorldEditView.cpp : implementation of the CWorldEditView class
//
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <list>
#include "MeRTLibs.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldEntry.h"
#include "EditRender/EditCamera.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "Ndl/NdlHelper.h"
#include "Ndl/NdlWorldEditor.h"
#include "Edit/ToolVertex.h"
#include "Edit/ToolCamera.h"
#include "Edit/ToolManager.h"
#include "Edit/OptStack.h"
#include "Edit/ToolLayer.h"
#include "Edit/ToolLiquid.h"
#include "Edit/ToolFreeBlock.h"
#include "UI/Custom/TexturePreviewWnd.h"
#include "ui/Dlg/LightMapSettingDlg.h"
#include "ui/ToolsScene/ToolWorldSkyboxDlg.h"
#include "ui/Custom/ReachableMapGenerate.h"
#include "ui/Dlg/ColiCheck.h"
#include "ui/Dlg/CameraFollowDlg.h"
#include "WorldEditor.h"
#include "WorldEditorDoc.h"
#include "WorldEditorView.h"
#include "EditRender/GameCamera.h"
#include "EditRender/ChaseCamera.h"
#include "swLuaScript.h"
#include "Utility.h"
#include "ui/ToolsWnd/LocateDlg.h"
#include "Me3d\Shader.h"
#include "Me3d\ShaderManager.h"
#include "Me3d\Postprocess\PostProcess.h"
#include "Me3d\Postprocess\PostProcessManager.h"
#include "DXUtil.h"
#include "Logger.h"
#include "Me3d/Engine/RendererDX.h"
#include "MeTerrain/STSkyBox.h"
#include "Me3d/Engine/RendererDX8.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "Me3d/Engine/MeBitSorter.h"

// #include "Scene\Me3d_SceneConfig.h"
////////////////////////////////////////////////////////////////////////////////


const INT eMiniMapSize = 256;
const INT eShadowsSize = SHADOW_RES*16/2;

LPDIRECT3DTEXTURE9	g_pRenderTexture = NULL;
LPDIRECT3DTEXTURE9	g_pShadowRenderTexture = NULL;
LPDIRECT3DTEXTURE9	g_pShadowRenderTexture1 = NULL;

//////////////////////////////////////////////////////////////////////////
enum znDisplayMode
{
	znDM_None	= -1,
	znDM_Wireframe,
	znDM_Normal,

	znDM_Flight
};

////////////////////////////////////////////////////////////////////////////////
// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif

namespace
{
	void SetInvertFlag( uInt32& a, uInt32 flag ) {
		if( !(a&flag) ){
			a = a|flag;
		}
		else{
			a = a^flag;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif

#define INVALIDE_ID		(-1)

////////////////////////////////////////////////////////////////////////////////
// CWorldEditView
IMPLEMENT_DYNCREATE(CWorldEditView, CView)

BEGIN_MESSAGE_MAP(CWorldEditView, CView)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_TIMER()
	ON_MESSAGE(WT_PACKET, OnWTPacket)
	ON_COMMAND(ID_EDIT_UNDO, &CWorldEditView::OnUndo)
	ON_COMMAND(ID_EDIT_REDO, &CWorldEditView::OnRedo)

	ON_COMMAND(ID_BTN_LOCK_VERT, &CWorldEditView::OnLockVertex)
	ON_UPDATE_COMMAND_UI(ID_BTN_LOCK_VERT, OnUpdateLockVertex)

	ON_COMMAND(ID_BTN_EDIT_CAMERA, &CWorldEditView::OnEditCamera)
	ON_COMMAND(ID_BTN_EDIT_GAME_CAMERA, &CWorldEditView::OnEditGameCamera)

	ON_COMMAND(ID_BTN_DISPLAY_CHUNK, &CWorldEditView::OnDisplayChunk)
	ON_COMMAND(ID_BTN_DISPLAY_NORMAL, &CWorldEditView::OnDislpayNormal)
	ON_COMMAND(ID_BTN_DISPLAY_TEXTURE, &CWorldEditView::OnDisplayTexture)
	ON_COMMAND(ID_BTN_DISPLAY_SHADOW, &CWorldEditView::OnDisplayShadow)
	ON_COMMAND(ID_BTN_DISPLAY_BOUNDBOX, &CWorldEditView::OnDisplayBoundBox)
	ON_COMMAND(ID_BTN_CHASECAMERA, &CWorldEditView::OnChaseCamera)
	ON_COMMAND(ID_BTN_DISPLAY_GRID, &CWorldEditView::OnDisplayGrid)
	ON_COMMAND(ID_BTN_DISPLAYLIQUID, &CWorldEditView::OnDisplayLiquid)
	ON_COMMAND(ID_BTN_DISPLAYMODEL, &CWorldEditView::OnDisplayModel)
	ON_COMMAND(ID_BTN_DISPLAYDOODAD, &CWorldEditView::OnDisplayDoodad)
	ON_COMMAND(ID_BUTTON_RENDER_MINIMAP, &CWorldEditView::OnRenderMinimap)
	ON_COMMAND(ID_BUTTON_SHOW_AABB, &CWorldEditView::OnShowAABB)
	ON_COMMAND(ID_BUTTON_SHOW_FOG, &CWorldEditView::OnShowFog)
	//ON_COMMAND(ID_BUTTON_SHMP, &CWorldEditView::OnRenderLightView) //lyh+++ 查看深度图
	//ON_COMMAND(ID_BUTTONSHOWSHAMP, &CWorldEditView::OnRenderShowMapScene) //lyh++ 查看深度图产生的阴影效果
	ON_COMMAND(ID_TerrainBump, &CWorldEditView::OnRenderShowTerrainBumap) //lyh++ 查看地形凹凸纹理

	

	ON_COMMAND(ID_BTN_PAINT_NORMAL, &CWorldEditView::OnPaintNormal)

	ON_COMMAND(ID_BTN_SELECT_FILTER, &CWorldEditView::OnSelectFilter)
	ON_COMMAND(ID_BTN_SELECT_NAME_GROUP, &CWorldEditView::OnSelectNameGroup)

	ON_COMMAND(ID_BTN_EDIT_MOVE, &CWorldEditView::OnEditMove)
	ON_COMMAND(ID_BTN_EDIT_ROTATE, &CWorldEditView::OnEditRotate)
	ON_COMMAND(ID_BTN_EDIT_SCALE, &CWorldEditView::OnEditScale)
	ON_COMMAND(ID_BTN_DISPLAY_ENV, & CWorldEditView::OnDisplayEnv)
	ON_COMMAND(ID_BTN_DISPLAY_ZONE, & CWorldEditView::OnDisplayZone)
	ON_COMMAND(ID_Animation, & CWorldEditView::OnDisplayAnimation)
	ON_COMMAND(ID_BUTTON_LOD, & CWorldEditView::OnChangeLod)
	ON_COMMAND(ID_BUTTON_Monster, & CWorldEditView::OnMonsterShow)
	ON_COMMAND(ID_BUTTON_LIGHTMAP, & CWorldEditView::OnGenerateLightMap)
	ON_COMMAND(ID_BUTTON_LIGHTMAP_SETTING, & CWorldEditView::OnSettingLightMap)
	ON_COMMAND(ID_BUTTON_MESH_LIGHTMAP, & CWorldEditView::OnGenerateMeshLightMap)
	ON_COMMAND(ID_BUTTON_TERRAIN_LAYER, & CWorldEditView::OnSettingTerrainLayer)
	ON_COMMAND(ID_BUTTON_LOADSKYBOX, & CWorldEditView::OnLoadSkybox )

	ON_COMMAND(ID_BUTTON_MULTISEL, & CWorldEditView::OnMultiSel )
	ON_COMMAND(ID_BUTTON_FREEBLOCK, & CWorldEditView::OnFreeBlock )
	ON_COMMAND(ID_BUTTON_SlopeCheck, & CWorldEditView::OnSlopeCheck )
	ON_COMMAND(ID_BUTTON_ColiCheck, & CWorldEditView::OnColiCheck)
	ON_COMMAND(ID_BUTTON_MULTISELTEXTURE, & CWorldEditView::OnMultiSelTexture )
	ON_COMMAND(ID_VIEW_USEDYNAMICLIGHT, & CWorldEditView::OnUseDynamicLight )
	ON_COMMAND(ID_VIEW_DEBUGMSG, & CWorldEditView::OnViewDebugMsg )
	//ON_COMMAND(ID_BTN_CLEAN_MODEL, &CWorldEditView::OnCleanModel)
	ON_XTP_EXECUTE(ID_BTN_SELECT_FILTER_EX, OnSelectFilterEx)

	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateRedo)

	ON_UPDATE_COMMAND_UI(ID_BTN_SELECT_FILTER_EX, OnUpdateSelectFilterEx)

	ON_UPDATE_COMMAND_UI(ID_BTN_EDIT_CAMERA, OnUpdateEditCamera)
	ON_UPDATE_COMMAND_UI(ID_BTN_EDIT_GAME_CAMERA, OnUpdateGameCamera)
	ON_UPDATE_COMMAND_UI(ID_BTN_DISPLAY_CHUNK, OnUpdateDisplayChunk)
	ON_UPDATE_COMMAND_UI(ID_BTN_DISPLAY_NORMAL, OnUpdateDisplayNormal)

	ON_UPDATE_COMMAND_UI(ID_BTN_DISPLAY_TEXTURE, OnUpdateDisplayTexture)
	ON_UPDATE_COMMAND_UI(ID_BTN_DISPLAY_SHADOW, OnUpdateDisplayShadow)
	ON_UPDATE_COMMAND_UI(ID_BTN_DISPLAY_BOUNDBOX, OnUpdateDisplayBoundBox)
	ON_UPDATE_COMMAND_UI(ID_BTN_CHASECAMERA, OnUpdateChaseCamera)
	ON_UPDATE_COMMAND_UI(ID_BTN_DISPLAY_GRID, OnUpdateDisplayGrid)
	ON_UPDATE_COMMAND_UI(ID_BTN_DISPLAYLIQUID, OnUpdateDisplayLiquid)
	ON_UPDATE_COMMAND_UI(ID_BTN_DISPLAYMODEL, OnUpdateDisplayModel)
	ON_UPDATE_COMMAND_UI(ID_BTN_DISPLAYDOODAD, OnUpdateDisplayDoodad)
	ON_UPDATE_COMMAND_UI(ID_BTN_DISPLAY_ENV, OnUpdateDisplayEnv)
	ON_UPDATE_COMMAND_UI(ID_BTN_DISPLAY_ZONE, OnUpdateDisplayZone)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_RENDER_MINIMAP, OnUpdateRenderMinimap)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SHOW_AABB, OnUpdateShowAABB)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SHOW_FOG, OnUpdateShowFog)
	//ON_UPDATE_COMMAND_UI(ID_BUTTON_SHMP, OnUpdateRenderLightView)//lyh+++
	//ON_UPDATE_COMMAND_UI(ID_BUTTONSHOWSHAMP, OnUpdateRenderShadowMapScene)//lyh+++
	ON_UPDATE_COMMAND_UI(ID_TerrainBump, OnUpdateRenderTerrainBump)//lyh+++  查看地形凹凸纹理
	
	
	
	ON_UPDATE_COMMAND_UI(ID_Animation, OnUpdateDisplayAnimation)

	ON_UPDATE_COMMAND_UI(ID_BTN_EDIT_MOVE, OnUpdateEditMove)
	ON_UPDATE_COMMAND_UI(ID_BTN_EDIT_ROTATE, OnUpdateEditRotate)
	ON_UPDATE_COMMAND_UI(ID_BTN_EDIT_SCALE, OnUpdateEditScale)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_MULTISEL, OnUpdateMultiSel )
	ON_UPDATE_COMMAND_UI(ID_BUTTON_MULTISELTEXTURE, OnUpdateMultiSelTexture )
	ON_UPDATE_COMMAND_UI(ID_BUTTON_FREEBLOCK, OnUpdateFreeBlock )
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SlopeCheck, OnUpdateSlopeCheck )
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ColiCheck, OnUpdateColiCheck )
	ON_UPDATE_COMMAND_UI(ID_VIEW_USEDYNAMICLIGHT, OnUpdateUseDynamicLight )
	ON_UPDATE_COMMAND_UI(ID_VIEW_DEBUGMSG, OnUpdateViewDebugMsg )

	ON_COMMAND(ID_OPERATION_Locate, &CWorldEditView::OnOperationLocate)
	ON_COMMAND(ID_SAVESHMP, &CWorldEditView::OnSaveShMp)
	
	ON_COMMAND(ID_EDIT_COPY, &CWorldEditView::OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CWorldEditView::OnUpdateEditCopy)
END_MESSAGE_MAP()

// CWorldEditView construction/destruction

CWorldEditView::CWorldEditView()
{
	m_needRecreateRender	= false;
	m_isCorrect3D			= false;
	m_activeCameraID		= INVALIDE_ID;
	m_TempShadowMap         = NULL;

	m_displayFilter			= 0;
	// 默认开启雾效
	m_displayFilter |= znDF_ShowFog;
m_BSaveShowmap = false;
#ifdef ST_EDITOR_Helper
	m_rootNode				= NULL;
#endif
	m_hTopLevelHwnd			= NULL;
	m_toolManager			= NULL;

	m_viewSize.x			= 0.0f;
	m_viewSize.y			= 0.0f;
	m_helper				= NULL;
	m_worldPick				= NULL;
	m_brushMode				= 0;
	m_brushSize				= 1;

	m_cameraList.clear();
	m_lastTool				= TOOL_NONE;
	paintCsr.x = -1;
	prev_pkButtons = 0;
	pWTMutex = new CMutex( TRUE, NULL, NULL );
	hCtx					= 0; 

	// Override some CD3DApplication defaults:
	HDC hSrcdc = CreateDC( "DISPLAY", NULL, NULL, NULL );
	m_dwCreationWidth           = ::GetDeviceCaps( hSrcdc, HORZRES )/* - 220*/; //220 是让给工具条的
	m_dwCreationHeight          = ::GetDeviceCaps( hSrcdc, VERTRES )/* - 90*/;
	m_bUseDepthBuffer			= TRUE;
	m_dwMinDepthBits			= 16;
	m_dwMinDepthBits			= 24;
	m_strWindowTitle            = TEXT( "WorldBuilder" );
	m_bUseDepthBuffer           = TRUE;
	m_bViewDebugMsg				= TRUE;

#ifdef MAP_EDITOR
	m_bLoadingApp               = TRUE;
	m_pD3DXMesh                 = NULL;

	ZeroMemory( &m_UserInput, sizeof(m_UserInput) );
	m_fWorldRotX                = 0.0f;
	m_fWorldRotY                = 0.0f;

	// Read settings from registry
	//ReadSettings();
	//m_pTerrainMap				= NULL;	
	//临时，以后读配置文件
	FlySetPathRoot( gCfg.m_szTerrainPath );
	gEditorCamera.ResetCamera();
	g_nScrWidth = m_dwCreationWidth;
	g_nScrHeight = m_dwCreationHeight;
	gEditorCamera.SetWindowSize( g_nScrWidth,g_nScrHeight );
#endif
}

CWorldEditView::~CWorldEditView()
{
	MexInstanceMan::GlobalDestroy();
	CHRRenderSurface::GlobalDestroy();
	m_hTopLevelHwnd		= NULL;
	m_activeCameraID	= INVALIDE_ID;

	// 因为所有摄像机都没有Attach 到别的节点上,所以要手动销毁摄像机
	for( size_t i = 0; i < m_cameraList.size(); i++ )
	{
		SwCamera* p = m_cameraList[i];
		NDL_SAFE_DELETE( p );
	}
	m_cameraList.clear();
	SAFE_DELETE( m_toolManager );
#ifdef ST_EDITOR_Helper
	m_rootNode		= NULL;
#endif
	SAFE_DELETE( m_worldPick );
	NDL_SAFE_DELETE( m_helper );
	swLuaScript::Release();
	if( hCtx )
		WTClose( hCtx );
	if (pWTMutex)
	{
		delete pWTMutex;
	}
	graphics::ShaderManager::instance()->shutdown();
	MeDelete graphics::ShaderManager::instance();
	Cleanup3DEnvironment();
}

BOOL CWorldEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);

}
extern char g_NullModelPath[];
void CWorldEditView::OnInitialUpdate()
{
	m_hTopLevelHwnd = GetTopLevelParent()->GetSafeHwnd();

	m_Lua = swLuaScript::Instance();

	m_Lua->ExecFile("config.lua");

	char cNullMexPath[MAX_PATH];
	if (m_Lua->GetGlobalString("NULLMODELPATH",cNullMexPath,MAX_PATH))
	{
		strcpy_s(g_NullModelPath,MAX_PATH,cNullMexPath);
	}
	CWorldEditDoc *pDoc = GetDocument();
	pDoc->SetMainView( this );

	if( !CreateNdlRender() ) {
		Trace( "Failed to create ndl render! \n" );
	}	

	CD3DApplication::m_hMainWnd = GetSafeHwnd();
	CD3DApplication::m_hWndFocus = GetSafeHwnd();
	CD3DApplication::Create( AfxGetInstanceHandle() );

#ifdef ST_EDITOR_Helper
	m_rootNode	= NiTCreate<NiNode>();
#endif

	if( !CreateHelper() ) {
		Trace( "Failed to load helper" );
	}

	theApp.GetWorld()->GetWorldBuffer()->GetGlobalResMgr()->Create();


	m_isCorrect3D	= true;

	m_toolManager = new CToolManager();
	m_toolManager->Create( this );
	m_toolManager->SetActiveTool( TOOL_CAMERA );
	m_lastTool = m_toolManager->GetActiveTool()->GetToolId();

	m_worldPick	= new CNdlEditWorldPicker( theApp.GetWorld() );

	SwGlobal::SetWorldPicker(m_worldPick);

	// skybox
	GetSTSkyBox()->Create(8,						// resolution
		45,										// sweep in degrees
		500,									// size at horizon
		1.0f,									// height scale factor
		D3DXVECTOR3 (0, 0, 0));					// offset

}

bool CWorldEditView::CreateNdlRender()
{
	//NiRenderer* render = NiDX9Renderer::Create( 0, 0, 
	//						0, 
	//						m_hWnd, m_hTopLevelHwnd );

	//modified by zilong. 2011-01-14
	//g_render	= new CEditRender;
	g_render = new CEditRender_M;

	SwGlobal::SetRender(g_render) ;
	//	g_render->Create( render );

	CreateDefaultCamera( 0, 0 );

	m_displayMode = znDM_Normal;

	return true;										
}	

void CWorldEditView::ReCreateNdlRender()
{
	CRect rect;
	GetClientRect(rect);

	if (rect.right > 0 && rect.bottom > 0)
	{
	}

	m_needRecreateRender = false;
}

// CWorldEditView drawing
void CWorldEditView::OnDraw(CDC* /*pDC*/)
{
	//if( theApp.IsActiveApp() && m_isCorrect3D )
	//{
	//	if( m_needRecreateRender )
	//		ReCreateNdlRender();
	//	
	//	Render();
	//}
}

void CWorldEditView::Update( flt32 totalTime, flt32 deltaTime )
{
	if( theApp.IsActiveApp() && m_isCorrect3D )
	{
		if ( m_activeCameraID == 2 )
		{
			D3DXVECTOR3 cameraPos;
			D3DXVECTOR3 lookatPt;
			g_render->UpdateChaseCamera( cameraPos, lookatPt );
			ChaseCamera* camera = (ChaseCamera*)GetActiveCamera();
			camera->SetEyePos( cameraPos );
			camera->SetLookAt( lookatPt );
		}
		GetActiveCamera()->Update( totalTime, deltaTime );


		if( m_needRecreateRender )
			ReCreateNdlRender();

		theApp.GetWorld()->Update( totalTime, deltaTime );
#ifdef ST_EDITOR_Helper
		m_rootNode->UpdateSelected(totalTime);
#endif
		m_helper->Update( totalTime );

		// 老的Render用Render3DEnvironment()替代
		//Render(totalTime, deltaTime );
		Render3DEnvironment(totalTime, deltaTime);
		DrawTabletCursor();
	}
}



void CWorldEditView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	if (bActivate) {
		UpdateStatusBar();
		// tell doc to update title
		// pDoc->UpdateTitle( this );
	}
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CWorldEditView::OnIdle()
{


}

void CWorldEditView::UpdateStatusBar()
{

}

void CWorldEditView::UpdateHorizontal( const Vector& pos )
{
	if( m_displayFilter&znDF_Bound  ) {
	}
}

void CWorldEditView::SetActivePos( flt32 posX, flt32 posY )
{
	theApp.GetWorld()->SetActivePos( posX, posY );

	Vector pos;
	pos.x			= posX;
	pos.y			= posY;

	const CNdlWorldPickerBase* pWorldPick = SwGlobal::GetWorldPicker();
	pWorldPick->GetHeight( pos.x, pos.y, pos.z );

	//Vector cameraPos(pos.x,pos.y - 10.f,pos.z + 10.f);
	Vector cameraPos(pos.x,pos.y + 10.f,pos.z + 10.f);

	SwCamera* camera = GetActiveCamera();
	// 	NiMatrix3 rot;
	// 	rot.FromEulerAnglesXYZ( camera->GetRot().x, camera->GetRot().y, camera->GetRot().z );
	camera->SetPos( cameraPos);
	camera->Update(0.f,0.f);
	UpdateHorizontal( pos );
}

sInt32 CWorldEditView::PickWorldTerrain( const CPoint& point, sInt32 pickType  )
{
	sInt32 pickId = -1;

	SwCamera* pCamera = GetActiveCamera();
	CEditCamera* pEditCamera = dynamic_cast<CEditCamera*>(pCamera);
	if(!pEditCamera)
		return -1;

	Vector pos		= GetActiveCamera()->GetPos();
	UpdateHorizontal( pos );

	//setup ray
	Vector rayPt, rayDir;
	pEditCamera->ScreenToWorldRay( Vector2(point.x, point.y), rayPt, rayDir );

	m_worldPick->Pick( rayPt, rayDir, m_pickResult, pickType,false );

	HelperObject* shapeVert		= m_helper->GetHelper( HT_VertLable );
	if( m_pickResult.pickResultCount > 0 ) {
		if( NULL != shapeVert )	{
			for( sInt32 i =0; i< MAX_PICK_OBJ_COUNT; i++ ) {
				if (m_pickResult.pickResultInfo[i].resultType == emPT_Terrain
					|| m_pickResult.pickResultInfo[i].resultType == emPT_ObjBBox)
				{
					shapeVert->SetPosition( m_pickResult.pickResultInfo[i].point.x,
						m_pickResult.pickResultInfo[i].point.y, 
						m_pickResult.pickResultInfo[i].point.z);

					shapeVert->SetNormal(m_pickResult.pickResultInfo[i].normal);

					theApp.SetWorldPosText(   m_pickResult.pickResultInfo[i].point.x
						, m_pickResult.pickResultInfo[i].point.y
						, m_pickResult.pickResultInfo[i].point.z 
						, 90.f - asin(m_pickResult.pickResultInfo[i].normal.z)*180/PI);
					shapeVert->Update( 0.0f );
					pickId	= i;
					break;
				}
			}
		}
	}

	//NiCamera* camera	= GetActiveCamera()->GetNiCamera();
	//Vector pos		= GetActiveCamera()->GetPos();
	//UpdateHorizontal( pos );
	//Vector rayPt, rayDir;
	//camera->Update( 0.0f );
	//camera->WindowPointToRay( point.x, point.y, rayPt, rayDir );
	//theApp.SetMousePosText( point.x, point.y, rayPt, rayDir );
	//
	//m_worldPick->Pick( rayPt, rayDir, m_pickResult, pickType );
	//NiNode* shapeVert		= m_helper->GetHelper( HT_VertLable );
	//if( m_pickResult.pickResultCount > 0 ) {
	//	if( NULL != shapeVert )	{
	//		for( sInt32 i =0; i< MAX_PICK_OBJ_COUNT; i++ ) {
	//			if( emPT_Terrain == m_pickResult.pickResultInfo[i].resultType ) {
	//				shapeVert->SetTranslate( m_pickResult.pickResultInfo[i].point );
	//				NiMatrix3 matRot;
	//				matRot.FromEulerAnglesXYZ(m_pickResult.pickResultInfo[i].normal.y,-m_pickResult.pickResultInfo[i].normal.x,m_pickResult.pickResultInfo[i].normal.z);
	//				shapeVert->SetRotate(matRot);
	//				shapeVert->SetAppCulled( false );
	//				theApp.SetWorldPosText(   m_pickResult.pickResultInfo[i].point.x
	//										, m_pickResult.pickResultInfo[i].point.y
	//										, m_pickResult.pickResultInfo[i].point.z 
	//										, 90.f - asin(m_pickResult.pickResultInfo[i].normal.z)*180/PI);
	//				shapeVert->Update( 0.0f );
	//				pickId	= i;
	//				break;
	//			}
	//		}
	//	}
	//}
	//else {
	//	if( NULL != shapeVert )
	//		shapeVert->SetAppCulled( true );
	//}

	return pickId;
}

// CWorldEditView diagnostics

#ifdef _DEBUG
void CWorldEditView::AssertValid() const
{
	CView::AssertValid();
}

void CWorldEditView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWorldEditDoc* CWorldEditView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorldEditDoc)));
	return (CWorldEditDoc*)m_pDocument;
}
#endif //_DEBUG

void CWorldEditView::OnSize( UINT nType, int cx, int cy )
{
	CView::OnSize(nType, cx, cy);

	if( NULL != g_render )
	{
		// Get screen metrics for scaling.
		CClientDC dc( this );
		m_viewSize.x			= (float) dc.GetDeviceCaps(HORZRES);
		m_viewSize.y			= (float ) dc.GetDeviceCaps(VERTRES);

		m_needRecreateRender	= true;

		// 重新设定摄像机　
		ResizeActiveCamera();
	}
}

BOOL CWorldEditView::OnEraseBkgnd( CDC* pDC )
{
	return TRUE;
}

void CWorldEditView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!IsAvailable())
		return;

	::SetCapture( m_hWnd );

	CBaseTool* tool = m_toolManager->GetActiveTool();
	tool->OnLMouseDown( nFlags, point );
}

void CWorldEditView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!IsAvailable())
		return;

	::ReleaseCapture();

	CBaseTool* tool = m_toolManager->GetActiveTool();
	tool->OnLMouseUp( nFlags, point );
}

void CWorldEditView::OnRButtonDown( UINT nFlags, CPoint point )
{
	if (!IsAvailable())
		return;


	::SetCapture( m_hWnd );

	CBaseTool* tool = m_toolManager->GetActiveTool();
	tool->OnRMouseDown( nFlags, point );
}

void CWorldEditView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (!IsAvailable())
		return;

	::ReleaseCapture();

	CBaseTool* tool = m_toolManager->GetActiveTool();
	tool->OnRMouseUp( nFlags, point );
}

void CWorldEditView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!IsAvailable())
		return;
	if ( theApp.IsActiveApp() ) {
		if( GetFocus() != this ) {
			SetFocus();
		}
	}
	//m_pickResult.isCollided = false;
	if( NULL != m_toolManager ) {
		if( NULL != m_helper ) {	
			CBaseTool* tool = m_toolManager->GetActiveTool();
			if( NULL != tool ) {
				tool->OnMouseMove( nFlags, point );
			}
		}
	}	
	return CView::OnMouseMove( nFlags, point );
}

BOOL CWorldEditView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	if (!IsAvailable())
		return false;
	CBaseTool* tool = m_toolManager->GetActiveTool();
	if( NULL == tool )
		return TRUE;

	tool->OnMouseWheel( nFlags, zDelta, point );

	return TRUE;
}

void CWorldEditView::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (!IsAvailable())
		return;

	CBaseTool *tool = m_toolManager->GetActiveTool();
	if (tool == NULL)
		return;

	tool->OnKeyDown(nChar, nRepCnt, nFlags);

	return CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CWorldEditView::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (!IsAvailable())
		return;
	CBaseTool* tool = m_toolManager->GetActiveTool();
	if( NULL == tool )
		return;

	tool->OnKeyUp( nChar, nRepCnt, nFlags );

	return CView::OnKeyUp( nChar, nRepCnt, nFlags );
}

void CWorldEditView::OnTimer( UINT nIDEvent )
{
	CBaseTool* tool = m_toolManager->GetActiveTool();
	if( NULL == tool )
		return;

	tool->OnTimer();

	return CView::OnTimer( nIDEvent );
}

void CWorldEditView::OnUndo()
{
	// 	COptStack* stack = theApp.GetOptStack();
	// 	stack->Undo();
	if(NULL == m_toolManager)
		return;

	CBaseTool *tool = m_toolManager->GetActiveTool();
	if(tool)
	{
		tool->Undo();
	}
}

void CWorldEditView::OnUpdateUndo(CCmdUI* pCmdUI)
{
	// 	COptStack* stack = theApp.GetOptStack();
	// 	if( stack->GetCanUndoCount() > 0 )
	// 		pCmdUI->Enable( TRUE );
	// 	else
	// 		pCmdUI->Enable( FALSE );

	if(m_toolManager)
	{
		CBaseTool *tool = m_toolManager->GetActiveTool();
		if(tool && tool->CanUndo())
		{
			pCmdUI->Enable(TRUE);
			return;
		}
	}

	pCmdUI->Enable(FALSE);
}

void CWorldEditView::OnRedo()
{
	// 	COptStack* stack = theApp.GetOptStack();
	// 	stack->Redo();

	if(NULL == m_toolManager)
		return;

	CBaseTool *tool = m_toolManager->GetActiveTool();
	if(tool)
	{
		tool->Redo();
	}
}

void CWorldEditView::OnUpdateRedo(CCmdUI* pCmdUI)
{
	// 	COptStack* stack = theApp.GetOptStack();
	// 	if( stack->GetCanRedoCount() > 0 )
	// 		pCmdUI->Enable( TRUE );
	// 	else
	// 		pCmdUI->Enable( FALSE );

	if(m_toolManager)
	{
		CBaseTool *tool = m_toolManager->GetActiveTool();
		if(tool && tool->CanRedo())
		{
			pCmdUI->Enable(TRUE);
			return;
		}
	}

	pCmdUI->Enable(FALSE);
}

void CWorldEditView::OnLockVertex()
{
	uInt32 lParam, wParam;
	m_toolManager->GetActiveTool()->GetParam( lParam, wParam );
	if( lParam == 1 ) {
		m_toolManager->SetActiveToolParam( 0 );
	}
	else {
		m_toolManager->SetActiveToolParam( 1 );
	}
}

void CWorldEditView::OnUpdateLockVertex(CCmdUI* pCmdUI)
{
	uInt32 lParam, wParam;
	m_toolManager->GetActiveTool()->GetParam( lParam, wParam );
	if( lParam == 1 ) {
		pCmdUI->SetCheck( 1 );
	}
	else {
		pCmdUI->SetCheck( 0 );
	}
}



void CWorldEditView::OnEditCamera()
{
	if (TOOL_CAMERA == m_toolManager->GetActiveTool()->GetToolId())
	{
		m_toolManager->SetActiveTool( m_lastTool );
	}
	else
	{
		if (TOOL_GAMECAMERA != m_toolManager->GetActiveTool()->GetToolId())
		{
			m_lastTool = m_toolManager->GetActiveTool()->GetToolId();
		}
		m_toolManager->SetActiveTool( TOOL_CAMERA );
	}
	//m_toolManager->SetActiveTool( TOOL_LAYER );
}

void CWorldEditView::OnUpdateEditCamera(CCmdUI* pCmdUI)
{
	CBaseTool* tool = m_toolManager->GetActiveTool();
	if( (NULL != tool) && (tool->GetToolId() == TOOL_CAMERA) ) {
		pCmdUI->SetCheck( 1 );
	}
	else { 
		pCmdUI->SetCheck( 0 );
	}
}

void CWorldEditView::OnDisplayChunk()
{
	m_displayMode = znDM_Wireframe;

	g_render->SetWireFrame( true );
}

void CWorldEditView::OnUpdateDisplayChunk(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( m_displayMode == znDM_Wireframe);
}

void CWorldEditView::OnDislpayNormal()
{
	m_displayMode = znDM_Normal;

	g_render->SetWireFrame( false );
}

void CWorldEditView::OnUpdateDisplayNormal(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (znDM_Normal==m_displayMode)?1:0 );	
}

void CWorldEditView::OnDisplayTexture()
{
	SetInvertFlag( m_displayFilter, znDF_Texture );
}

void CWorldEditView::OnUpdateDisplayTexture(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_Texture)?1:0 );
}

void CWorldEditView::OnDisplayShadow()
{
	// 	SetInvertFlag( m_displayFilter, znDF_Shadow );
	// 	bool isPaintShadow = m_displayFilter&znDF_Shadow;
	CWorldTile* tile = CURRENTTILE;
	if (NULL != tile)
	{
		CResEditMgr* pResMgr = (CResEditMgr*)tile->GetCResMgr();		
		switch(pResMgr->GetShadowShowType())
		{
		case CResEditMgr::eShadow:
			pResMgr->SetShadowShowType(CResEditMgr::eRoad);
			m_strCurRoadShadow = "道路";
			break;
		case CResEditMgr::eRoad:
			pResMgr->SetShadowShowType(CResEditMgr::ePathFindMap);
			m_strCurRoadShadow = "寻路图";
			break;
		case CResEditMgr::ePathFindMap:
			pResMgr->SetShadowShowType(CResEditMgr::eShadow);
			m_strCurRoadShadow = "阴影";
			break;

		}

		CToolLayer* pLayer = (CToolLayer*)m_toolManager->GetTool(TOOL_LAYER);
		pLayer->SetPaintShadow(!pResMgr->IsRoadShow());

		((CMainFrame *) AfxGetMainWnd())->SetPromptText(m_strCurRoadShadow);
	}
}

void CWorldEditView::OnUpdateDisplayShadow(CCmdUI* pCmdUI)
{
	// 	pCmdUI->SetCheck( (m_displayFilter&znDF_Shadow)?1:0 );
	if (GetToolManager()->GetActiveTool()->GetToolId() == TOOL_LAYER)
		((CMainFrame *) AfxGetMainWnd())->SetPromptText(m_strCurRoadShadow);
}

void CWorldEditView::OnDisplayBoundBox()
{
	SetInvertFlag( m_displayFilter, znDF_Bound );

	// 显示碰撞模型
	GetMe3dConfig()->ChangeRenderHelper();
}

void CWorldEditView::OnUpdateDisplayBoundBox(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_Bound)?1:0 );
}

void CWorldEditView::OnChaseCamera()
{
	if ( GetActiveCameraID() == 0 )
	{
		D3DXVECTOR3 cameraPos;
		D3DXVECTOR3 lookatPos;
		if ( g_render->UpdateChaseCamera( cameraPos, lookatPos ) )
		{
			CCameraFollowDialog dlg;
			if (dlg.DoModal() != IDOK)
				return;

			SetActiveCameraID(2);
		}
		else
		{
			SetActiveCameraID(0);
		}
	}
	else
	{
		SetActiveCameraID(0);
	}

}

void CWorldEditView::OnUpdateChaseCamera(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( ( GetActiveCameraID() == 2 )?1:0 );
}

void CWorldEditView::OnDisplayGrid()
{
	SetInvertFlag( m_displayFilter, znDF_Horizontal );
	if( m_displayFilter&znDF_Horizontal ) {
		g_render->SetBoundWireframe( true );
	}
	else {
		g_render->SetBoundWireframe( false );
	}
}

void CWorldEditView::OnUpdateDisplayGrid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_Horizontal)?1:0 );

}

void CWorldEditView::OnFreeBlock()
{
	// 阻挡
	SetInvertFlag( m_displayFilter, znDF_FreeBlock );

	//CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	//CToolManager* toolManager = ((CWorldEditDoc *) GetDocument())->GetWorldView()->GetToolManager();
	CToolManager* toolManager = this->GetToolManager();

	toolManager->SetActiveTool( TOOL_FREEBLOCK );

	ToolFreeBlock* toolFreeBlock = (ToolFreeBlock*)( toolManager->GetActiveTool() );

	if( m_displayFilter&znDF_FreeBlock ) 
	{
		toolFreeBlock->EnableFreeBlock( true );
	}
	else 
	{
		toolFreeBlock->EnableFreeBlock( false );
	}
}

void CWorldEditView::OnSlopeCheck()
{
	// 斜坡检查
	SetInvertFlag( m_displayFilter, znDF_SlopeCheck );
	CEditRender* pEditRender = (CEditRender*)g_render;

	if ( m_displayFilter & znDF_SlopeCheck)
	{
		pEditRender->SetDisplaySlopeCheck( true );
		CReachableMapGenerate::Instance()->SlopeCheck();
	}
	else
	{
		pEditRender->SetDisplaySlopeCheck( false);
	}
}

void CWorldEditView::OnColiCheck( )
{
	static CColiCheck* pColiCheck = NULL;
	if (pColiCheck == NULL)
	{
		pColiCheck = new CColiCheck;
		pColiCheck->Create(IDD_DIALOG_ColiCheckResult);
	}
	pColiCheck->ShowWindow(SW_SHOW);
	pColiCheck->DoColiCheck();
}

void CWorldEditView::OnMultiSel()
{
	SetInvertFlag( m_displayFilter, znDF_MultiSel );

	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_LIQUID );

	CToolLiquid* toolLiquid = (CToolLiquid*)( toolManager->GetActiveTool() );

	if( m_displayFilter&znDF_MultiSel ) {
		toolLiquid->setMultiSel(true);
	}
	else {
		toolLiquid->setMultiSel(false);
	}
}

void CWorldEditView::OnMultiSelTexture()
{
	SetInvertFlag( m_displayFilter, znDF_MultiSelTexture );

	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_LAYER );

	CToolLayer* toolLayer = (CToolLayer*)( toolManager->GetActiveTool() );

	if( m_displayFilter&znDF_MultiSelTexture ) {
		toolLayer->setMultiSel(true);
	}
	else {
		toolLayer->setMultiSel(false);
	}
}

void CWorldEditView::OnUpdateFreeBlock(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_FreeBlock)?1:0 );
}

void CWorldEditView::OnUpdateSlopeCheck(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_SlopeCheck)?1:0 );

}

void CWorldEditView::OnUpdateColiCheck(CCmdUI* pCmdUI)
{
}

void CWorldEditView::OnUpdateMultiSel(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_MultiSel)?1:0 );
}
void CWorldEditView::OnUpdateMultiSelTexture(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_MultiSelTexture)?1:0 );
}
void CWorldEditView::OnDisplayLiquid()
{
	SetInvertFlag( m_displayFilter, znDF_Liquid );
	if( m_displayFilter&znDF_Liquid ) {
		g_render->SetRenderLiquid( true );
	}
	else {
		g_render->SetRenderLiquid( false );
	}
}

void CWorldEditView::OnUpdateDisplayLiquid(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_Liquid)?0:1 );
}

void CWorldEditView::OnDisplayModel()
{
	SetInvertFlag( m_displayFilter, znDF_Model );
	if( m_displayFilter&znDF_Model ) {
		g_render->SetRenderModel( true );
	}
	else {
		g_render->SetRenderModel( false );
	}
}

void CWorldEditView::OnDisplayDoodad()
{
	SetInvertFlag( m_displayFilter, znDF_Doodad );
	if( m_displayFilter&znDF_Doodad ) {
		g_render->SetRenderDoodad( true );
	}
	else {
		g_render->SetRenderDoodad( false );
	}
}

void CWorldEditView::OnRenderMinimap()
{
	SetInvertFlag( m_displayFilter, znDF_RenderMinimap );
}

void CWorldEditView::OnRenderLightView()
{
	SetInvertFlag( m_displayFilter, znDF_ShowLightView );
}

void CWorldEditView::OnRenderShowTerrainBumap()
{
SetInvertFlag( m_displayFilter, znDF_ShowTerrainBump );
}

void CWorldEditView::OnRenderShowMapScene()
{
	//lyh 当点击显示阴影的时候 ，加载深度图。
	//if(!(m_displayFilter & znDF_ShowShadowMapEffect))
	//{
 //       if (m_TempShadowMap)
 //       {
	//		m_TempShadowMap->Release();
	//		m_TempShadowMap = NULL;
 //       }

	//	LPDIRECT3DDEVICE9 _dev = (LPDIRECT3DDEVICE9)(GetEngine()->GetRenderer()->GetRealDevice());
	//	
	//	char szSubFolder[MAX_PATH] = {0};
	//	sprintf_s(szSubFolder, sizeof(szSubFolder)-1, "%s\\%s", SwGlobal::GetWorld()->GetWorldPath(), "ShowMap.dds");//lyh改路径光照图

	//	D3DXCreateTextureFromFile(_dev,szSubFolder,&m_TempShadowMap);
	//	if (!m_TempShadowMap)
	//	{
	//		MessageBox("深度图加载失败 ，确保文件存在","!",MB_OK);

	//	}
 //      
	//}
	SetInvertFlag( m_displayFilter, znDF_ShowShadowMapEffect );
}


void CWorldEditView::OnShowAABB()
{
	SetInvertFlag( m_displayFilter, znDF_ShowAABB );
}

void CWorldEditView::OnShowFog()
{
	SetInvertFlag( m_displayFilter, znDF_ShowFog );
}

void CWorldEditView::OnUpdateDisplayModel(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_Model)?0:1 );
}

void CWorldEditView::OnUpdateDisplayDoodad(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_Doodad)?0:1 );
}

void CWorldEditView::OnDisplayEnv()
{
	SetInvertFlag( m_displayFilter, znDF_Env );
	if( m_displayFilter&znDF_Env ) {
		g_render->SetShowEnv( true );
	}
	else {
		g_render->SetShowEnv( false );
	}
}

void CWorldEditView::OnDisplayAnimation()
{
	SetInvertFlag( m_displayFilter, znDF_Animation );
	if( m_displayFilter&znDF_Animation ) {
		g_render->SetShowAnimation( true );
	}
	else {
		g_render->SetShowAnimation( false );
	}
}

void CWorldEditView::OnChangeLod()
{
	CWorldTile* tile = CURRENTTILE;
	if (NULL == tile)
		return;

	CResEditMgr* pResMgr = (CResEditMgr*)tile->GetCResMgr();
	for (int i = 0; i < tile->GetChunkTotal(); ++i)
	{
		CWorldChunk* pChunk = tile->GetChunk(i);
		int newLevel = pChunk->GetLODLevel();
		switch (newLevel)
		{
		case 0:
			newLevel = 3;
			break;
		case 1:
			newLevel = 4;
			break;
		case 2:
			newLevel = 0;
			break;
		case 3:
			newLevel = 1;
			break;
		case 4:
			newLevel = 2;
			break;
		default:
			break;
		}
		pResMgr->SetLODLevelPrivate(pChunk,newLevel);
	}
}

void CWorldEditView::OnUpdateDisplayEnv(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_Env)?1:0 );
}

void CWorldEditView::OnUpdateDisplayAnimation(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_Animation)?1:0 );
}

void CWorldEditView::OnPaintNormal()
{
	theApp.GetWorldEditor()->UpdateTileNormal();
}


void CWorldEditView::OnSelectFilter()
{

}

void CWorldEditView::OnSelectFilterEx(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	if (pControl->GetType() == xtpControlComboBox) {

		*pResult = TRUE; // Handled
	}
}

void CWorldEditView::OnUpdateSelectFilterEx(CCmdUI* pCmdUI)
{
	CXTPControlComboBox* pStateCombo = DYNAMIC_DOWNCAST(CXTPControlComboBox, CXTPControl::FromUI(pCmdUI));

	if (pStateCombo && !XTPMouseManager()->IsTrackedLock())	{

	}
	pCmdUI->Enable( TRUE );
}

void CWorldEditView::OnSelectNameGroup()
{

}

void CWorldEditView::OnEditMove()
{

}

void CWorldEditView::OnUpdateEditMove(CCmdUI* pCmdUI)
{

}

void CWorldEditView::OnEditRotate()
{

}

void CWorldEditView::OnUpdateEditRotate(CCmdUI* pCmdUI)
{

}

void CWorldEditView::OnEditScale()
{

}

void CWorldEditView::OnUpdateEditScale(CCmdUI* pCmdUI)
{

}

bool CWorldEditView::CreateDefaultCamera( int gridX, int gridY )
{
	Assert( INVALIDE_ID == m_activeCameraID );

	//SwCamera* camera	= NiTCreate<CEditCamera>();
	CEditCamera* camera	= new CEditCamera;
	camera->Create();
	camera->SetProjectionMatrix(this);
	m_cameraList.push_back( camera );

	//SwCamera* Gamecamera	= NiTCreate<GameCamera>();
	GameCamera* Gamecamera	= new GameCamera;
	Gamecamera->Create();
	Gamecamera->SetProjectionMatrix(this);
	m_cameraList.push_back( Gamecamera );

	ChaseCamera* Chasecamera	= new ChaseCamera;
	Chasecamera->Create();
	Chasecamera->SetProjectionMatrix(this);
	m_cameraList.push_back( Chasecamera );

	SetActiveCameraID(0);

	D3DXMATRIX mat = GetActiveCamera()->GetViewMatrix();

	return true;
}


SwCamera* CWorldEditView::GetActiveCamera()
{
	Assert( m_activeCameraID < m_cameraList.size() );

	ASSERT_NOTNULL( m_cameraList[m_activeCameraID] );

	return m_cameraList[m_activeCameraID];
}

void CWorldEditView::ResizeActiveCamera()
{
	RECT rect;
	this->GetClientRect( &rect );
	if( rect.right < 0.1f )
		return;

	float aspectRatio	= ( (float)rect.bottom / (float)rect.right );

}

bool CWorldEditView::CreateHelper()
{
	Assert( NULL == m_helper );

	//m_helper = NiTCreate<CNdlHelper>();
	m_helper = new CNdlHelper;
	Assert( NULL != m_helper );
	m_helper->Create();

#ifdef ST_EDITOR_Helper
	AttachNode(m_helper->GetNode() );
#endif
	UpdateRoot();

	return true;
}

#ifdef ST_EDITOR_Helper
void CWorldEditView::AttachNode( NiAVObject* pkChild, bool bFirstAvail /*= false*/ )
{
	m_rootNode->AttachChild( pkChild);
}
#endif

void CWorldEditView::OnEditGameCamera()
{
	if (TOOL_GAMECAMERA == m_toolManager->GetActiveTool()->GetToolId())
	{
		SetActiveCameraID(0);
		m_toolManager->SetActiveTool( m_lastTool );
	}
	else
	{
		if (TOOL_CAMERA != m_toolManager->GetActiveTool()->GetToolId())
		{
			m_lastTool = m_toolManager->GetActiveTool()->GetToolId();
		}
		m_toolManager->SetActiveTool( TOOL_GAMECAMERA );
	}
}

void CWorldEditView::OnUpdateGameCamera( CCmdUI* pCmdUI )
{
	CBaseTool* tool = m_toolManager->GetActiveTool();
	if( (NULL != tool) && (tool->GetToolId() == TOOL_GAMECAMERA) ) {
		pCmdUI->SetCheck( 1 );
	}
	else { 
		pCmdUI->SetCheck( 0 );
	}

}

void CWorldEditView::SetActiveCameraID( uInt32 val )
{
	if (m_activeCameraID != val)
	{
		// 		SwCamera* pOldCam = GetActiveCamera();
		m_activeCameraID = val;
		// 		SwCamera* pNewCam = GetActiveCamera();
		// 		pNewCam->SetFrustum(pNewCam->GetFrustum());
		// 		pNewCam->SetPos(pNewCam->GetPos());
		// 		pNewCam->SetRot(pNewCam->GetRot());
	}
	// 	if (-1 != m_activeCameraID)
	// 	{
	// 		SwGlobal::SetCamera(m_cameraList[m_activeCameraID]);
	// 	}
}

uInt32 CWorldEditView::GetActiveCameraID()
{
	return m_activeCameraID;
}

void CWorldEditView::ResetCamera()
{
	m_activeCameraID = 0;
	g_render->ResetCameraModel();
}

void CWorldEditView::Reset()
{
	m_toolManager->Reset();
}

bool CWorldEditView::IsAvailable()
{
	if( NULL == m_toolManager )
		return false;
	if (NULL == CURRENTTILE)
	{
		return false;
	}
	return true;
}

void CWorldEditView::UpdateRoot()
{
#ifdef ST_EDITOR_Helper
	m_rootNode->Update( 0.0f );
	m_rootNode->UpdateProperties();
	m_rootNode->UpdateEffects();
	m_rootNode->UpdateNodeBound();
#endif
}

void CWorldEditView::OnMonsterShow()
{
	g_render->ToggleDisplayMonster();
}

void CWorldEditView::OnGenerateLightMap()
{
	theApp.GetWorldEditor()->GenerateLightMap();
}

void CWorldEditView::OnSettingLightMap()
{
	LightMapSettingDlg dlg;
	if(dlg.DoModal() ==IDOK)
	{
		short color = dlg.GetShadowColor();
		theApp.GetWorldEditor()->ChangeAllShadowColor(color);
	}
}
void CWorldEditView::OnGenerateMeshLightMap()
{
	theApp.GetWorldEditor()->GenerateMeshLightMap();
}
// CWorldEditView message handlers

LRESULT CWorldEditView::OnWTPacket(WPARAM wSerial, LPARAM hCtx)
{
	// Read the packet
	PACKET pkt;
	if (!WTPacket( (HCTX)hCtx, wSerial, &pkt ))
	{
		return false;
	}

	// Process packets in order, one at a time
	CSingleLock lock( pWTMutex, TRUE );


	prev_pkButtons = pkt.pkButtons;

	// Get window size
	RECT window_rect;
	GetWindowRect( &window_rect );
	POINT size;
	size.x = window_rect.right;// - window_rect.left;
	size.y = window_rect.bottom;// - window_rect.top;
	CPoint csr;
	csr.x = (size.x * pkt.pkX) / lc.lcInExtX;	
	csr.y = size.y - (size.y * pkt.pkY) / lc.lcInExtY;

	if (csr.x > window_rect.left && csr.y > window_rect.top)
	{
		paintCsr.x = csr.x * (window_rect.right- window_rect.left)/window_rect.right;	
		paintCsr.y = csr.y * (window_rect.bottom- window_rect.top)/window_rect.top;	
		CBaseTool* tool = m_toolManager->GetActiveTool();
		tool->OnWTPacket(pkt,paintCsr );
	}


	return TRUE;
}


int CWorldEditView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 关闭内存泄露检测
	// _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	// Get default context information
	WTInfo( WTI_DEFCONTEXT, 0, &lc );

	// Open the context
	lc.lcPktData = PACKETDATA;
	lc.lcPktMode = PACKETMODE;
	lc.lcOptions = CXO_MESSAGES | CXO_SYSTEM;
	//hCtx = WTOpen( m_hWnd, &lc, TRUE );
	hCtx = WTOpen( m_hWnd, &lc, TRUE );
	return 0;
}

void CWorldEditView::OnPaint()
{
	CView::OnPaint();


}

void CWorldEditView::DrawTabletCursor()
{
	CDC *pDC = GetDC();
	// 	CDC*             pDC;             /* handle for Device Context */
	// 	PAINTSTRUCT     psPaint;         /* the paint structure */
	// 	if (pDC = BeginPaint(&psPaint)) 
	{
		pDC->MoveTo(paintCsr.x - 20,paintCsr.y     );
		pDC->LineTo(paintCsr.x + 20,paintCsr.y     );
		pDC->MoveTo(paintCsr.x     ,paintCsr.y - 20);
		pDC->LineTo(paintCsr.x     ,paintCsr.y + 20);
		// 		EndPaint( &psPaint);
	}
	ReleaseDC( pDC );
}

//-----------------------------------------------------------------------------
// Name: ConfirmDevice()
// Desc: Called during device initialization, this code checks the display device
//       for some minimum set of capabilities
//-----------------------------------------------------------------------------
HRESULT CWorldEditView::ConfirmDevice( D3DCAPS9* pCaps, DWORD dwBehavior,
									  D3DFORMAT Format )
{
	///    BOOL bCapsAcceptable;

	BOOL bHasHardWareVertexProcessing = FALSE;
	if( ( dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING ) ||
		( dwBehavior & D3DCREATE_MIXED_VERTEXPROCESSING ) )
	{
		if( pCaps->VertexShaderVersion < D3DVS_VERSION(1,0) )
			return E_FAIL;
		if( dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING )
			bHasHardWareVertexProcessing = TRUE;
	}

	// TODO: Perform checks to see if these display caps are acceptable.
	//bCapsAcceptable = TRUE;

	//if( bCapsAcceptable )         
	//    return S_OK;
	//else
	//    return E_FAIL;
	return S_OK;
}



//-----------------------------------------------------------------------------
// Name: CWorldEditView::InitDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CWorldEditView::InitDeviceObjects()
{
	// TODO: create device objects

	D3DXCreateFont( m_pd3dDevice, 
		16,
		0, 
		FW_BOLD,
		1,
		false,
		DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_DONTCARE,
		"Arial", &m_pFont );
	//    HRESULT hr;
	Logger::initialize("wb.config");
#if MAP_EDITOR
	g_World.ChangeFarPlane( 7 );
#endif
	GetMe3dConfig()->SetRenderMapBox( TRUE );
	GetMe3dConfig()->SetShowFog( FALSE );
#if MAP_EDITOR
	// 	Me3d_SceneConfig::SetBorderSize( gCfg.m_iBorderSize );

	GetShaderMgr()->SetWaterType( 3 );
#endif

	char strName[MAX_PATH];
	sprintf(strName, "%s\\DATA\\SHADER\\PostProcess\\Quad.fxo", SwGlobal::GetWorld()->GetAppDataCharDir());
	PostProcessManager::instance().initialize( m_pd3dDevice, strName );	

	BloomPostProcessEffect* bloomPost = MeNew BloomPostProcessEffect( "Bloom" );
	sprintf(strName, "%s\\DATA\\SHADER\\PostProcess", SwGlobal::GetWorld()->GetAppDataCharDir());
	bloomPost->create( m_pd3dDevice, strName );
	PostProcessManager::instance().addPostProcessEffect( bloomPost );
	//enable post process
	PostProcessManager::instance().enablePostProcess( true );

	return S_OK;
}



//extern LPDIRECT3DDEVICE9 g_pd3dDevice;
#define FtoDW(x) *((DWORD*)(&x))
//-----------------------------------------------------------------------------
// Name: CWorldEditView::RestoreDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CWorldEditView::RestoreDeviceObjects(bool bInitEngineInstance)
{
	// Set the world matrix	

	// Set up lighting states
	if(bInitEngineInstance)
		SetEngine( new CEngineInstance );
	GetEngine()->GetRenderer()->SetDevice( m_pd3dDevice );	

	IRenderer* RI = GetEngine()->GetRenderer();
	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity( &matIdentity );
	RI->SetTransform( D3DTS_WORLD,  (FLOAT*)&matIdentity );

	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the
	// origin, and define "up" to be in the y-direction.
	D3DXMATRIX matView;
	matView = GetActiveCamera()->GetViewMatrix();
	RI->SetTransform( D3DTS_VIEW, (FLOAT*)&matView );

#if MAP_EDITOR
	// Set the projection matrix
	float fFarPlane = MAX_RAYCAST_DISTANCE;
	Me3d_Config::GetCamera()->SetProjParams( D3DX_PI/4, 0.5, 1.0f, fFarPlane );
#endif
	D3DXMATRIX matProj;
	matProj = GetActiveCamera()->GetProjMatrix();
	RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&matProj );

	GetEngine()->UseTextureMultiThreadLoading(false);
	GetEngine()->UseAbstractPath( FALSE );

	//extern char g_szRootPath[256];
	// 	char szRootPath[MAX_PATH];
	// 	GetCurrentDirectory( MAX_PATH, szRootPath );
	// 	SetRootPath( szRootPath );

#ifdef MAP_EDITOR
	HRESULT hr = LoadSkinMeshVertexShader( 
		m_pd3dDevice, 
		"data\\shader\\paletteskin.vso",
		&GetMe3dConfig()->m_dwSkinMeshVertexShaderID );
#endif
	CRect rect;
	GetClientRect(rect);
	PostProcessManager::instance().restoreDeviceObjects( m_pd3dDevice, 
		rect.Width(), rect.Height() );

	return S_OK;
}

//void CameraLoop();
//-----------------------------------------------------------------------------
// Name: CWorldEditView::FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT CWorldEditView::FrameMove()
{
	//TRUETIMEFUNC();
	guardfunc;
	// TODO: update world
	//如果发现需要更新camera
	//
	IRenderer* RI = GetEngine()->GetRenderer();
	// 	GetEngine()->GetTextureManager()->ProcessTextureLoadingThread();
	BEGINFUNCPERLOG( "framemove" );
	//CameraLoop();

	if( GetActiveCamera()->IsNeedUpdateViewMatrix() )
	{
		D3DXMATRIX matView;
		matView = GetActiveCamera()->GetViewMatrix();
		RI->SetTransform( D3DTS_VIEW, (FLOAT*)&matView );
		RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&GetActiveCamera()->GetProjMatrix() );

		// 貌似没用
		//if( g_pCurScene->GetTerrain() )
		//{
		//	D3DXVECTOR3 vecEye = GetActiveCamera()->GetEye();
		//	D3DXVECTOR3 vecDir = GetActiveCamera()->GetDir();
		//	int xTile = 0,yTile = 0;
		//	g_pCurScene->GetTerrain()->GetPointXY( &vecEye,&vecDir,xTile,yTile );
		//	//			GetAutoMinimap()->SetCameraPos( xTile,yTile );
		//}
	}
#ifdef MAP_EDITOR
	if( g_World.GetFootupLevel() )
	{
		POINT pt;
		pt.x = g_nScrWidth/2;
		pt.y = g_nScrHeight/2;
		//	GetCursorPos( &pt );
		ScreenToClient( &pt );
		D3DXVECTOR3 vPos(0,0,0),vDir(0,0,0);
		GetActiveCamera()->Pick( &vPos,&vDir,pt.x,pt.y );
		D3DXVECTOR3 vCross;
		gpMapObjectBack = g_World.GetFootupLevel()->GetTerrain();
		if( g_World.GetRayCrossPoint( &vPos,&vDir,vCross ) )
		{
			g_vPlayer = vCross;
		}
	}

	D3DXVECTOR3 vCameraOrg;
	vCameraOrg = GetActiveCamera()->GetLookAt();
	vCameraOrg -= GetActiveCamera()->GetEye();
	D3DXVec3Normalize( &vCameraOrg,&vCameraOrg );

	{
		g_World.UpData( HQ_TimeGetTime(), &g_vPlayer, &g_vPlayer,
			(D3DXVECTOR3*)&GetActiveCamera()->GetEye(), &vCameraOrg, (FrustumEx*)&GetActiveCamera()->GetFrustum()
			);

	}


	Me3d_Config::GetCamera()->SetViewParams( (D3DXVECTOR3&)GetActiveCamera()->GetEye(),
		(D3DXVECTOR3&)GetActiveCamera()->GetLookAt(),D3DXVECTOR3(0,0,1) );
#endif

	ENDFUNCPERLOG( "framemove" );

	unguard;
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: CWorldEditView::OneTimeSceneInit()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//----------------------------------------------------------------------------
extern RECT QuadTreePath( int* pnPath, int nDepth, int nMapSize );
HRESULT CWorldEditView::OneTimeSceneInit()
{
	// TODO: perform one time initialization
#ifdef MAP_EDITOR
	InitDefScene();
	CloseOldTerrain();
	m_bLoadingApp = FALSE;
	//...
	GetMe3dConfig()->m_bUseSkinMesh = FALSE;
#endif
	return S_OK;
}
LPDIRECT3DTEXTURE9 _TempShadowMap = NULL;
void   ShadowMapset( bool IsTerrain)
{
IRenderer* RI = GetEngine()->GetRenderer();
	//lyh场景编辑器的正常渲染逻辑
	
	{

		graphics::ShaderEffect* effect = (graphics::ShaderEffect*)(RI->TerrainMaterial()->getShader());
		ID3DXEffect* d3dEffect = NULL;
		if ( effect) 
		{
			d3dEffect = effect->getID3DXEffect() ;
			d3dEffect->SetBool("bUseEditLightShadowMap",false); //设置shadowm为关闭
			if (!_TempShadowMap)
			{
				LPDIRECT3DDEVICE9 _dev = (LPDIRECT3DDEVICE9)(GetEngine()->GetRenderer()->GetRealDevice());

				char szSubFolder[MAX_PATH] = {0};
				sprintf_s(szSubFolder, sizeof(szSubFolder)-1, "%s\\%s", SwGlobal::GetWorld()->GetWorldPath(), "ShowMap.dds");//lyh改路径光照图

				D3DXCreateTextureFromFile(_dev,szSubFolder,&_TempShadowMap);
			}

			if(_TempShadowMap)
				d3dEffect->SetTexture("StaticSceneShadowMap",_TempShadowMap);
			else
				d3dEffect->SetBool("bUseEditLightShadowMap",false); //设置shadowm为关闭

		}

		//if (m_displayFilter & znDF_ShowShadowMapEffect ) //打开shadowmap 阴影绘制
		{


			if(d3dEffect && CURRENTTILE && g_render->m_BRenderDepth )
			{

               D3DXMATRIX _LightWVPMat;
			   D3DXMATRIX _LightWVPMatTex;
				g_render->GenerateLightView( CURRENTTILE, 1024, _LightWVPMat, false , true);	


				float fTexOffs = 0.5 + (0.5 / (float)1024);
				D3DXMATRIX matTexAdj( 0.5f,		0.0f,	0.0f,	0.0f,
					0.0f,    -0.5f,	0.0f,	0.0f,
					0.0f,		0.0f,	1.0f,	0.0f,
					fTexOffs, fTexOffs,  0.0f, 1.0f );

				D3DXMatrixMultiply(&_LightWVPMatTex,&_LightWVPMat,&matTexAdj);

				d3dEffect->SetMatrix("TerrainEditLightWVP",&_LightWVPMat);
				d3dEffect->SetMatrix("TerrainEditLightTexMat",&_LightWVPMatTex);
				d3dEffect->SetBool("bUseEditLightShadowMap",true);
				

				BOOL _bool_ ;
				LPDIRECT3DBASETEXTURE9 _tex;
				D3DXMATRIX mat;
				d3dEffect->GetBool("bUseEditLightShadowMap" ,&_bool_);
				d3dEffect->GetTexture("StaticSceneShadowMap",&_tex);
				d3dEffect->GetMatrix("TerrainEditLightWVP",&mat);

				if(0)
				D3DXSaveTextureToFile("d:\\lyh.tga",D3DXIFF_TGA,_tex,NULL);

				int i =1;




			
			
			
			
			}


		}

	}
   
}


HRESULT CWorldEditView::Render(float totalTime, float deltaTime )
{
	guardfunc;
IRenderer* RI = GetEngine()->GetRenderer();
	if (m_displayFilter & znDF_RenderMinimap)
	{
		if (CURRENTTILE != NULL)
			g_render->GenerateMinimap( CURRENTTILE, 1024, "", false);
		return S_OK;
	}

	//if (m_displayFilter & znDF_ShowLightView) //lyh绘制lightView 视角绘制 效果。
	//{
	//	if (CURRENTTILE != NULL)
	//	{
	//		RI->SetLightMapTEnble(true); //客户端这个值用来做 阴影开关。
	//		g_render->GenerateLightView( CURRENTTILE, 1024, m_LightWVPMat, m_BSaveShowmap);	
	//		RI->SetLightMapTEnble(false);
	//		m_BSaveShowmap = false; 
	//	}
	//	return S_OK;
	//}

	


	g_render->m_BRenderDepth = false;  //实际效果 地形的 凹凸纹理效果开关。
	if (m_displayFilter & znDF_ShowTerrainBump) 
	{
	   g_render->m_BRenderDepth = true;
	}

	//g_render->m_ShadowMapShaderSetCallBack = (ShadowMapShaderSetCallBack)(ShadowMapset);

	RECT rcDst = 
	{
		0, 0, eMiniMapSize, eMiniMapSize
	};
	RECT rcSrc = 
	{
		0, 0, eMiniMapSize, eMiniMapSize
	};

	RECT rcDstShadows = 
	{
		0, 0, eShadowsSize, eShadowsSize
	};
	RECT rcSrcShadows = 
	{
		0, 0, eShadowsSize, eShadowsSize
	};
	// 	if( !GetMe3dConfig()->IsMiniMap() )
	// 		RenderToTexture();

#ifdef MAP_EDITOR
	// 	Me3d_SceneConfig::SetVisualParams( (D3DXMATRIX*)&GetActiveCamera()->GetViewMatrix()
	// 		,(D3DXMATRIX*)&GetActiveCamera()->GetProjMatrix(),g_nScrWidth,g_nScrHeight );

	Me3d_Config::SetBillboard(  *(Me3d_Matrix*)&GetActiveCamera()->GetBillboardMatrix() );
	Me3d_Config::FrameUpdated( true );
#endif

	GetEngine()->GetRenderer()->SetEyePt( (float*)&GetActiveCamera()->GetEye() );
	GetEngine()->GetRenderer()->SetLookatPt( (float*)&GetActiveCamera()->GetLookAt() );

	DWORD dwTick = HQ_TimeGetTime();
	char szBuf[ 100 ];

	// 显示雾效
	FogProperty* pFogProp = theApp.GetFogProperty();
	bool bFogEnable = false;
	if( pFogProp && pFogProp->bShowFog )
	{
		bFogEnable = true;
		RI->Clear( 0L, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
			D3DCOLOR_ARGB(255,
			(int)(pFogProp->kFogColor.r*255.f),
			(int)(pFogProp->kFogColor.g*255.f),
			(int)(pFogProp->kFogColor.b*255.f)), 1.0f, 0L );
	}
	else
	{
		bFogEnable = false;
		RI->Clear( 0L, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
			D3DCOLOR_ARGB(255,
			(int)(SwGlobal::s_globalDefaultFogColor.r*255.f),
			(int)(SwGlobal::s_globalDefaultFogColor.g*255.f),
			(int)(SwGlobal::s_globalDefaultFogColor.b*255.f)),
			1.0f, 0L );		
	}

	// 	if( !GetMe3dConfig()->IsMiniMap() )
	// 	{
	// 		DrawRenderToTexture( g_pRenderTexture,
	// 			&rcDst,
	// 			&rcSrc,
	// 			eMiniMapSize,
	// 			eMiniMapSize,
	// 			0.0f,
	// 			0xffffffff, 0 );
	// 	}


	HRESULT hr = RI->BeginScene();

	if( SUCCEEDED( hr ) )
	{        
		DWORD dwStartRender = HQ_TimeGetTime();		
		BOOL bRender = false;
#ifdef MAP_EDITOR
		g_World.Push();
		{
			g_World.Render();

			if( g_bShowMonster )
			{
				MapCharRender();
			}
		}
#endif
		// 渲染天空盒
		D3DXVECTOR3 ptEye = GetActiveCamera()->GetEye();
		RendererDx* RIDx = (RendererDx*)GetEngine()->GetRenderer();
		LPDIRECT3DDEVICE9 r = (LPDIRECT3DDEVICE9)RIDx->GetRealDevice();
		D3DXMATRIX matOldProj = RIDx->GetProjectMatrix();

		float fAspect = (float)m_dwCreationWidth / m_dwCreationHeight;
		MeCamera tempCamera;
		tempCamera.SetProjParams( D3DX_PI/4, fAspect, 0.1f, 1000000.0f );
		RIDx->SetTransform( D3DTS_PROJECTION, (float*)&tempCamera.GetProjMatrix() );
		GetSTSkyBox()->m_bCanRender = true;// temp
		g_render->RenderSkyBox( theApp.GetWorld(), ptEye );	
		//回复projectmatrix
		RIDx->SetTransform( D3DTS_PROJECTION, (float*)&matOldProj );
		RIDx->SetRenderState( D3DRS_FOGENABLE,  bFogEnable );
		// 渲染世界
		g_render->RenderWorld( theApp.GetWorld(), GetActiveCamera()->GetFrustum(), GetActiveCamera()->GetEye(), totalTime, deltaTime);
		MeRenderManager::Instance()->DoRender(false);

		g_render->RenderLiquid();
		//{
		//	TerrainRender::Flush();
		//}

		sprintf( szBuf,"Editor View" );
		//switch( g_iView )
		//{
		//case view_normal:
		//	sprintf( szBuf,"Editor View" );
		//	break;
		//case view_top:
		//	sprintf( szBuf,"Top View" );
		//	break;
		//case view_game:
		//	sprintf( szBuf,"Game View" );
		//	break;
		//case PrtScr_game:
		//	sprintf( szBuf,"Game View" );
		//	break;
		//}

		if( IsViewDebugMsg() )
		{
			static const DWORD INFO_TEXT_COLOR = D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff);

			RECT RT;
			SetRect(&RT, 0, 0, 0, 0 );
			m_pFont->DrawText( NULL, szBuf, -1, &RT, DT_NOCLIP, INFO_TEXT_COLOR);
			SetRect(&RT, 0, 20, 20, 0 );
			m_pFont->DrawText( NULL, m_strFrameStats, -1, &RT, DT_NOCLIP, INFO_TEXT_COLOR );

			char sBuf[200] = {0};
			sprintf( sBuf,"Chunk number:%d, faces:%d, vertex:%d", g_render->GetChunkCount(), g_render->GetChunkFaceCount(),
				g_render->GetChunkVertexCount());
			SetRect(&RT, 0, 40, 0, 0 );
			m_pFont->DrawText( NULL, sBuf, -1, &RT, DT_NOCLIP, INFO_TEXT_COLOR );

			sprintf( sBuf,"object number:%d(sub-object number:%d), faces:%d, vertex:%d", g_render->GetModelCount(), g_render->GetSubmodelCount(), g_render->GetModelFaceCount(),
				g_render->GetModelVertexCount());
			SetRect(&RT, 0, 60, 0, 0 );
			m_pFont->DrawText( NULL, sBuf, -1, &RT, DT_NOCLIP, INFO_TEXT_COLOR );

			sprintf( sBuf,"Faces total:%d, Vertex total:%d",g_render->GetChunkFaceCount() + g_render->GetModelFaceCount(),
				g_render->GetChunkVertexCount() + g_render->GetModelVertexCount());
			SetRect(&RT, 0, 80, 0, 0 );
			m_pFont->DrawText( NULL, sBuf, -1, &RT, DT_NOCLIP, INFO_TEXT_COLOR );

			sprintf( sBuf,"Chunk render time:%dms\nModel render time:%dms\nDoodad render time:%dms",
				g_render->GetChunkRenderTime(), g_render->GetModelRenderTime(), g_render->GetDoodadRenderTime() );
			SetRect(&RT, 0, 100, 0, 0 );
			m_pFont->DrawText( NULL, sBuf, -1, &RT, DT_NOCLIP, INFO_TEXT_COLOR );

			sprintf( sBuf,"Terrain Layer: %d",
				GetMe3dConfig()->GetTerrainRenderLayer() );
			SetRect(&RT, 0, 150, 0, 0 );
			m_pFont->DrawText( NULL, sBuf, -1, &RT, DT_NOCLIP, INFO_TEXT_COLOR );
		}

		//{
		//	//TRUETIMEBLOCK("theSigleUI.Render()");
		//	theSigleUI.Render();
		//}
		//{
		//	//TRUETIMEBLOCK("g_EditArea.Render()");
		//	g_EditArea.Render();
		//}
		////RenderWater
		//g_World.RenderWater();
		//g_World.RenderGrass();

		//g_World.Pop();

		////Light
		//if( CMapEditor::op_addlight == gEditorInfo.uiOp )
		//{
		//	extern void RenderMouseObject();
		//	RenderMouseObject();
		//}

		m_helper->Render();
		{
			D3DXMATRIX matView;
			matView = GetActiveCamera()->GetViewMatrix();
			RI->SetTransform( D3DTS_VIEW, (FLOAT*)&matView );
			RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&matOldProj/*&GetActiveCamera()->GetProjMatrix()*/ );
		}
		m_toolManager->Render();

		//added by zilong. 2011-01-15
		if(IsSetLocation())
		{
			CToolVertex *pTool = (CToolVertex *)m_toolManager->GetTool(TOOL_VERTEX);
			if(pTool)
			{
				pTool->Render();
			}
		}

		// 		MeRenderManager::Instance()->DoRender(false);
		g_render->RenderEffect();
		RIDx->Flush( eSortByFarZ );


		MeRenderManager::Instance()->DoRender(true);
		RI->EndScene();

		RI->SetRenderState( D3DRS_FOGENABLE, FALSE );
		try
		{
			PostProcessManager::instance().render();
		}
		catch ( const std::exception& e )
		{
			OutputDebugString( e.what() );
		}
		RI->SetRenderState( D3DRS_FOGENABLE, TRUE );
	}	


#ifdef MAP_EDITOR
	if( GIsCovMap )
	{
		//RECT& rect, DWORD dwColor
		RECT rect;
		SetRect( &rect, 56, 396, 56+104, 418 );
		//DrawRect2D(  );
		GetMe3dDrawer()->DrawRect2D( rect, 0xffff0000 );
		DrawProcess( 60, 400, GCovMapPer , 100 );
	}
#endif
	//Sleep( 1 );
	unguard;
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: CWorldEditView::InvalidateDeviceObjects()
// Desc: Called when the device-dependent objects are about to be lost.
//-----------------------------------------------------------------------------
HRESULT CWorldEditView::InvalidateDeviceObjects()
{
	// TODO: Cleanup any objects created in RestoreDeviceObjects()
	//    m_pFont->InvalidateDeviceObjects();
	PostProcessManager::instance().invalidateDeviceObjects();

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: CWorldEditView::DeleteDeviceObjects()
// Desc: Called when the app is exiting, or the device is being changed,
//       this function deletes any device dependent objects.
//-----------------------------------------------------------------------------
HRESULT CWorldEditView::DeleteDeviceObjects()
{
	// TODO: Cleanup any objects created in InitDeviceObjects()
	m_pFont->Release();
#ifdef MAP_EDITOR
	SAFE_RELEASE( m_pD3DXMesh );

	CloseOldTerrain();
#endif
	// 	GetEngine()->GetTextureManager()->CloseTextureLoadingThread();

	PostProcessManager::instance().shutdown();
	delete PostProcessManager::instancePtr();

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: CWorldEditView::FinalCleanup()
// Desc: Called before the app exits, this function gives the app the chance
//       to cleanup after itself.
//-----------------------------------------------------------------------------
HRESULT CWorldEditView::FinalCleanup()
{
	// TODO: Perform any final cleanup needed
#ifdef MAP_EDITOR
	CloseOldTerrain();	
	if( g_LightSetting )
		g_LightSetting->ReleaseRes();

	g_pCurScene->ReleaseScene();
	theMouseObject = NULL;
#endif
	GetMexResMgr()->Destroy();

	if( GetEngine() )
	{
		GetEngine()->Release();
		SetEngine(NULL);
	}

#ifdef MAP_EDITOR
	// Write the settings to the registry
	WriteSettings();
#endif
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: AdjustWindowForChange()
// Desc: Adjusts the window properties for windowed or fullscreen mode
//-----------------------------------------------------------------------------
HRESULT CWorldEditView::AdjustWindowForChange()
{
	// m_hwndRenderFullScreen未初始化，貌似编辑器里不支持
#ifdef MAP_EDITOR
	if( m_bWindowed )
	{
		::ShowWindow( m_hwndRenderFullScreen, SW_HIDE );
		CD3DApplication::m_hMainWnd = m_hwndRenderWindow;
	}
	else
	{
		if( ::IsIconic( m_hwndRenderFullScreen ) )
			::ShowWindow( m_hwndRenderFullScreen, SW_RESTORE );
		::ShowWindow( m_hwndRenderFullScreen, SW_SHOW );
		CD3DApplication::m_hMainWnd = m_hwndRenderFullScreen;
	}
#endif
	return S_OK;
}

// HRESULT CWorldEditView::RenderToTexture()
// {
// 	LPDIRECT3DDEVICE9 pd3dDevice = m_pd3dDevice;
// 
// 	IRenderer* RI = GetEngine()->GetRenderer();
// 
// 	D3DXMATRIX matWorld;
// 	D3DXMatrixIdentity( &matWorld );
// 	RI->SetTransform( D3DTS_WORLD, (FLOAT*)&matWorld );
// 
// 	LPDIRECT3DSURFACE9 pRenderSurface = NULL,
// 		pBackBuffer = NULL;
// 	//LPDIRECT3DSURFACE9 pZStencil = NULL;
// 	//pd3dDevice->GetDepthStencilSurface( &pZStencil );
// 	g_pRenderTexture->GetSurfaceLevel(0,&pRenderSurface);
// 	pd3dDevice->GetRenderTarget( 0, &pBackBuffer );
// 
// 	//pd3dDevice->StretchRect(pBackBuffer,NULL,pRenderSurface,NULL, D3DTEXF_LINEAR);
// 
// 	if( pd3dDevice->SetRenderTarget(0,pRenderSurface) == D3D_OK )
// 	{
// 		int k = 0;
// 	}
// 	//CD3DCamera camera;
// 	MeCamera camera;
// 	int l = 10000.0f*GetMe3dConfig()->m_fMdlSpaceScale;
// 
// 	D3DXVECTOR3 vMin(0, 0, -l );
// 	D3DXVECTOR3 vMax(128*MAPTILESIZE, 128*MAPTILESIZE, l );
// 	D3DXVECTOR3 vEyePt( vMax.x/2, vMax.y/2, l );
// 	D3DXVECTOR3 vLookAt( vMax.x/2, vMax.y/2, -l );
// 
// #ifdef MAP_EDITOR
// 	if(g_World.GetFootupLevel())
// 	{
// 		Me3d_CTerrain *pTerrain = g_World.GetFootupLevel()->GetTerrain();
// 		if( pTerrain )
// 		{
// 			INT x = 0, y = 0; 
// 			pTerrain->GetWorldMapXY( x, y );
// 
// 			vMin	=	D3DXVECTOR3( x*128*MAPTILESIZE, y*128*MAPTILESIZE, -l );
// 			vMax	=	D3DXVECTOR3( (x+1)*128*MAPTILESIZE, (y+1)*128*MAPTILESIZE, l );
// 
// 			vEyePt.x = ( (vMax.x+vMin.x)/2 );
// 			vEyePt.y = ( (vMax.y+vMin.y)/2 );
// 
// 			vLookAt.x = vEyePt.x;
// 			vLookAt.y = vEyePt.y;
// 		}
// 	}
// #endif
// 	D3DXMATRIX matProj;
// 	D3DXMatrixOrthoLH(&matProj,vMax.x-vMin.x, vMax.y-vMin.y, vMin.z, vMax.z );
// 	camera.SetViewParams( vEyePt, vLookAt, D3DXVECTOR3( 0, -1, 0 ) );
// 	camera.SetProjMatrix( matProj );
// // 	Me3d_SceneConfig::SetVisualParams( (D3DXMATRIX*)&camera.GetViewMatrix()
// // 		,(D3DXMATRIX*)&matProj,eMiniMapSize,eMiniMapSize );
// 
// 	RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&matProj );
// 	RI->SetTransform( D3DTS_VIEW, (FLOAT*)&camera.GetViewMatrix() );
// 
// 	RI->Clear( 0L, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
// 		D3DCOLOR_ARGB(255,
// 		255,
// 		255,
// 		255), 1.0f, 0 );
// 	RI->BeginScene();
// 
// // 	Me3d_CTerrain *pTerrain = NULL;
// // 	Me3d_CScene*	pScene = NULL;
// #ifdef MAP_EDITOR
// 	if(g_World.GetFootupLevel())
// 	{
// 		pTerrain = g_World.GetFootupLevel()->GetTerrain();
// 		pScene = g_World.GetFootupLevel()->GetScene();
// 
// 		GetMe3dConfig()->SetRenderAllObjs( TRUE );
// 		if( pTerrain )
// 		{
// 			pTerrain->Render();
// 		}
// 
// 		if( pScene )
// 			pScene->RenderAllObject();
// 
// 		//g_World.Render();
// 		RI->Flush( eSortByFarZ );
// 		g_World.RenderWater();
// 
// 		GetMe3dConfig()->SetRenderAllObjs( FALSE );
// 	}
// #endif
// 	RI->EndScene();
// 	if( pRenderSurface )
// 		pRenderSurface->Release();
// 	if( pBackBuffer )
// 		pBackBuffer->Release();
// 	m_pd3dDevice->SetRenderTarget( /*pBackBuffer*/0, pBackBuffer );
// 
// 	RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&GetActiveCamera()->GetProjMatrix() );
// 	RI->SetTransform( D3DTS_VIEW, (FLOAT*)&GetActiveCamera()->GetViewMatrix() );
// 
// 	//m_pd3dDevice->Present(NULL,NULL,NULL,NULL);
// 	return S_OK;
// }

D3DXVECTOR2 uv[4];

extern BOOL g_ClearTexture;
// BOOL CWorldEditView::RenderShadows()
// {
// 	LPDIRECT3DDEVICE9 pd3dDevice = m_pd3dDevice;
// 
// 	IRenderer* RI = GetEngine()->GetRenderer();
// 
// 	D3DXMATRIX matWorld;
// 	D3DXMatrixIdentity( &matWorld );
// 	RI->SetTransform( D3DTS_WORLD, (FLOAT*)&matWorld );
// 
// 
// 	LPDIRECT3DSURFACE9 pRenderSurface = NULL,pBackBuffer = NULL;
// 	LPDIRECT3DSURFACE9 pZStencil = NULL;
// 	pd3dDevice->GetDepthStencilSurface( &pZStencil );
// 	g_pShadowRenderTexture->GetSurfaceLevel(0,&pRenderSurface);
// 	pd3dDevice->GetRenderTarget( 0, &pBackBuffer);
// 	if( pd3dDevice->SetRenderTarget(/*pRenderSurface*/0,pRenderSurface) == D3D_OK )
// 	{
// 	}
// 
// 
// 	D3DXMATRIX matProjection;
// 	float fPlaneWidth = 128*MAPTILESIZE;
// 	float fPlaneHeight = 128*MAPTILESIZE;
// 
// 	MeCamera camera;	
// 	D3DXVECTOR3 vViewDir = SwGlobal::GetRender()->GetD9Light().Direction;
// #ifdef MAP_EDITOR
// 	if(g_World.GetFootupLevel())
// 	{
// 		Me3d_CScene* pScene = g_World.GetFootupLevel()->GetScene();
// 		if( pScene )	
// 		{
// 			vViewDir = D3DXVECTOR3(0, 0, -1);// pScene->m_lgtSun.Direction;
// 		}
// 	}
// #endif
// 
// 	D3DXVec3Normalize( &vViewDir, &vViewDir );
// 	D3DXVECTOR3 vLookat = D3DXVECTOR3( fPlaneWidth/2, fPlaneHeight/2, 0 );
// 
// 	D3DXPLANE plane;
// 	D3DXVECTOR3 vPlaneCenter = vLookat-vViewDir*10000.0f;
// 	// 得到摄像机的平面
// 	D3DXPlaneFromPointNormal( &plane, &vPlaneCenter, &vViewDir );
// 
// 	D3DXVECTOR3 vRect[4] = 
// 	{
// 		D3DXVECTOR3( 0, 0, 0 ),
// 		D3DXVECTOR3( fPlaneWidth, 0, 0 ),
// 		D3DXVECTOR3( fPlaneWidth, fPlaneHeight, 0 ),
// 		D3DXVECTOR3( 0, fPlaneHeight, 0 ),
// 	};
// 
// 	D3DXVECTOR3 vHit[4];
// 	for( int nHit = 0; nHit < 4; nHit++ )
// 	{
// 		D3DXPlaneIntersectLine( &vHit[nHit], &plane, &vRect[nHit], &(vRect[nHit]-vViewDir*10000.0f) );
// 	}
// 
// 	D3DXVECTOR3 vTopEdge = vHit[1]-vHit[0];
// 	float fTopEdgeLength = D3DXVec3Length( &vTopEdge );
// 	// 计算顶边的单位向量
// 	D3DXVec3Normalize( &vTopEdge, &vTopEdge );
// 	// 得到右上角斜边的长度
// 	D3DXVECTOR3 vTopRightCornerEdge = vHit[1]-vPlaneCenter;
// 	// 得到左上角斜边的长度
// 	D3DXVECTOR3 vTopLeftCornerEdge = vHit[0]-vPlaneCenter;
// 
// 	float fPlaneRightLength = abs( D3DXVec3Dot( &vTopRightCornerEdge, &vTopEdge ) );
// 	float fPlaneLegthLength = abs( D3DXVec3Dot( &vTopLeftCornerEdge, &vTopEdge ) );
// 
// 	D3DXVECTOR3 vUp;
// 	D3DXVECTOR3 vRight;
// 	if( fPlaneRightLength > fPlaneLegthLength )
// 	{
// 		vRight = vTopEdge*fPlaneRightLength;
// 		vUp = vTopRightCornerEdge-vRight;
// 		uv[0].x = (fPlaneRightLength*2-fTopEdgeLength)/(fPlaneRightLength*2);
// 		uv[1].x = 1;
// 		uv[2].x = (fTopEdgeLength)/(fPlaneRightLength*2);
// 		uv[3].x = 0;
// 	}
// 	else
// 	{
// 		fPlaneRightLength = fPlaneLegthLength;
// 		vRight = vTopEdge*fPlaneRightLength;
// 		vUp = vTopLeftCornerEdge-(-vRight);
// 		uv[0].x = 0;//;
// 		uv[1].x = ((INT)fTopEdgeLength)/((INT)fPlaneRightLength*2);
// 		uv[2].x = 1;
// 		uv[3].x = ((INT)fPlaneRightLength*2-(INT)fTopEdgeLength)/((INT)fPlaneRightLength*2);
// 	}
// 
// 	float fPlaneUpLength = D3DXVec3Length( &vUp );
// 
// 
// 	D3DXVECTOR3 vCameraUp = vUp;
// 	D3DXVECTOR3 vCameraRight = vRight;
// 
// 	D3DXVec3Normalize( &vCameraUp, &vCameraUp );
// 	D3DXVec3Normalize( &vCameraRight, &vCameraRight );
// 
// 	float asp = 1.0f;
// 	D3DXVECTOR3 vMin( -(fPlaneRightLength), -(fPlaneUpLength)/asp, 1 );
// 	D3DXVECTOR3 vMax( fPlaneRightLength, (fPlaneUpLength)/asp, 20000.0f*2 );
// 	D3DXMATRIX matProj;
// 	D3DXMatrixOrthoLH(&matProj,vMax.x-vMin.x, vMax.y-vMin.y, vMin.z, vMax.z );
// 
// 	//	camera.SetOrthoLH( vMin, vMax );
// 	camera.SetProjMatrix( matProj );
// 	camera.SetViewParams( vLookat-vViewDir*20000.0f, vLookat, vCameraUp/*D3DXVECTOR3(0,0,1)*/ );
// // 	Me3d_SceneConfig::SetVisualParams( (D3DXMATRIX*)&camera.GetViewMatrix()
// // 		,(D3DXMATRIX*)&matProj/*camera.GetProjMatrix()*/,eShadowsSize,eShadowsSize );
// 
// 	RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&matProj/*camera.GetProjMatrix()*/ );
// 	RI->SetTransform( D3DTS_VIEW, (FLOAT*)&camera.GetViewMatrix() );
// 
// 	RI->Clear( 0L, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
// 		D3DCOLOR_ARGB(255,
// 		0,
// 		0,
// 		0), 1.0f, 0.0L );
// 	RI->BeginScene();
// 
// #ifdef MAP_EDITOR
// 	CTerrainEditor *pTerrain = NULL;
// 	Me3d_CScene*	pScene = NULL;
// 	if(g_World.GetFootupLevel())
// 	{
// 		pTerrain = (CTerrainEditor*)g_World.GetFootupLevel()->GetTerrain();
// 		pScene = g_World.GetFootupLevel()->GetScene();
// 
// 		Camera* pCamera = GetMe3dConfig()->GetCamera();
// 		GetMe3dConfig()->SetRenderAllObjs( TRUE );
// 
// 		//if( pTerrain )
// 		//{
// 		//	pTerrain->RenderAll();
// 		//}
// 		if( pScene )
// 			pScene->RenderAllObject();
// 
// 		GetMe3dConfig()->SetRenderAllObjs( FALSE );
// 	}
// #endif
// 	struct Vertex
// 	{
// 		D3DXVECTOR3 p;
// 		DWORD color;
// 		float u, v;
// 	};
// 
// 	Vertex vertex[4];
// 	DWORD dwColor = 0xffffffff;
// 	vertex[0].p = vRect[3];
// 	vertex[0].u = uv[3].x;
// 	vertex[0].v = 1;
// 	vertex[0].color = dwColor;
// 
// 	vertex[1].p = vRect[0];
// 	vertex[1].u = uv[0].x;
// 	vertex[1].v = 0;
// 	vertex[1].color = dwColor;
// 
// 	vertex[2].p = vRect[2];
// 	vertex[2].u = uv[2].x;
// 	vertex[2].v = 1;
// 	vertex[2].color = dwColor;
// 
// 	vertex[3].p = vRect[1];
// 	vertex[3].u = uv[1].x;
// 	vertex[3].v = 0;
// 	vertex[3].color = dwColor;
// 	short index[6] = { 0, 1, 2, 2, 1, 3 };
// 
// 	RI->SetTexture( 0, g_pShadowRenderTexture );
// 	g_ClearTexture = FALSE;
// 	RI->DirectPushSurface(
// 		-1, 
// 		-1, 
// 		MEX2_SHADER,
// 		D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,
// 		sizeof( Vertex ), 
// 		(BYTE*)vertex,
// 		4,
// 		(BYTE*)index,
// 		2,
// 		eNeedNotSetTexture|eTwoSided|eLinearFilter );
// 	g_ClearTexture = TRUE;
// 
// 	//GetMe3dDrawer()->DrawLine3D(
// 	//	vRect[0], vRect[1], 0xffffff00 );
// 	//GetMe3dDrawer()->DrawLine3D(
// 	//	vRect[1], vRect[2], 0xffffff00 );
// 	//GetMe3dDrawer()->DrawLine3D(
// 	//	vRect[2], vRect[3], 0xffffff00 );
// 	//GetMe3dDrawer()->DrawLine3D(
// 	//	vRect[3], vRect[0], 0xffffff00 );
// 
// 	RI->EndScene();
// 	if( pRenderSurface )
// 		pRenderSurface->Release();
// 	if( pBackBuffer )
// 		pBackBuffer->Release();
// 	m_pd3dDevice->SetRenderTarget( 0, pBackBuffer );
// 
// 	RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&GetActiveCamera()->GetProjMatrix() );
// 	RI->SetTransform( D3DTS_VIEW, (FLOAT*)&GetActiveCamera()->GetViewMatrix() );
// 
// 	m_pd3dDevice->Present(NULL,NULL,NULL,NULL);
// 
// 	//Tex 2
// 	{
// 
// 		MeCamera camera;
// 		int l = 20000.0f*GetMe3dConfig()->m_fMdlSpaceScale;
// 
// 		D3DXVECTOR3 vMin(0, 0, -l );
// 		D3DXVECTOR3 vMax(128*MAPTILESIZE, 128*MAPTILESIZE, l );
// 		D3DXVECTOR3 vEyePt( vMax.x/2, vMax.y/2, l );
// 		D3DXVECTOR3 vLookAt( vMax.x/2, vMax.y/2, 0 );
// 
// 		LPDIRECT3DSURFACE9 pRenderSurface = NULL,pBackBuffer = NULL;
// 		LPDIRECT3DSURFACE9 pZStencil = NULL;
// 		pd3dDevice->GetDepthStencilSurface( &pZStencil );
// 		g_pShadowRenderTexture1->GetSurfaceLevel(0,&pRenderSurface);
// 		pd3dDevice->GetRenderTarget( 0, &pBackBuffer);
// 		if( pd3dDevice->SetRenderTarget( 0, pRenderSurface ) == D3D_OK )
// 		{
// 		}
// 
// 		D3DXMATRIX matProj;
// 		D3DXMatrixOrthoLH(&matProj,vMax.x-vMin.x, vMax.y-vMin.y, vMin.z, vMax.z );
// 		camera.SetViewParams( vEyePt, vLookAt, D3DXVECTOR3( 0, -1, 0 ) );
// 		camera.SetProjMatrix( matProj );
// // 		Me3d_SceneConfig::SetVisualParams( (D3DXMATRIX*)&camera.GetViewMatrix()
// // 			,(D3DXMATRIX*)&matProj,eMiniMapSize,eMiniMapSize );
// 
// 		RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&matProj );
// 		RI->SetTransform( D3DTS_VIEW, (FLOAT*)&camera.GetViewMatrix() );
// 
// 		RI->Clear( 0L, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
// 			D3DCOLOR_ARGB(255,
// 			0,
// 			0,
// 			0), 1.0f, 0.0L );
// 		RI->BeginScene();
// 
// 
// 
// 
// 		D3DXVECTOR3 vRect[4] = 
// 		{
// 			D3DXVECTOR3( 0, 0, 0 ),
// 			D3DXVECTOR3( 128*MAPTILESIZE, 0, 0 ),
// 			D3DXVECTOR3( 128*MAPTILESIZE, 128*MAPTILESIZE, 0 ),
// 			D3DXVECTOR3( 0, 128*MAPTILESIZE, 0 ),
// 		};
// 
// 		struct Vertex
// 		{
// 			D3DXVECTOR3 p;
// 			DWORD color;
// 			float u, v;
// 		};
// 
// 		Vertex vertex[4];
// 		DWORD dwColor = 0xffffffff;
// 		vertex[0].p = vRect[3];
// 		vertex[0].u = uv[3].x;
// 		vertex[0].v = 1;
// 		vertex[0].color = dwColor;
// 
// 		vertex[1].p = vRect[0];
// 		vertex[1].u = uv[0].x;
// 		vertex[1].v = 0;
// 		vertex[1].color = dwColor;
// 
// 		vertex[2].p = vRect[2];
// 		vertex[2].u = uv[2].x;
// 		vertex[2].v = 1;
// 		vertex[2].color = dwColor;
// 
// 		vertex[3].p = vRect[1];
// 		vertex[3].u = uv[1].x;
// 		vertex[3].v = 0;
// 		vertex[3].color = dwColor;
// 		short index[6] = { 0, 1, 2, 2, 1, 3 };
// 
// 		RI->SetTexture( 0, g_pShadowRenderTexture );
// 		g_ClearTexture = FALSE;
// 		RI->DirectPushSurface(
// 			-1, 
// 			-1, 
// 			MEX2_SHADER,
// 			D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1,
// 			sizeof( Vertex ), 
// 			(BYTE*)vertex,
// 			4,
// 			(BYTE*)index,
// 			2,
// 			eNeedNotSetTexture|eTwoSided|eLinearFilter );
// 		g_ClearTexture = TRUE;
// 		//////////////////////////////////////////////////////////////////////////
// 		RI->EndScene();
// 		if( pRenderSurface )
// 			pRenderSurface->Release();
// 		if( pBackBuffer )
// 			pBackBuffer->Release();
// 		m_pd3dDevice->SetRenderTarget( 0, pBackBuffer/*, pZStencil*/ );
// 
// 		RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&GetActiveCamera()->GetProjMatrix() );
// 		RI->SetTransform( D3DTS_VIEW, (FLOAT*)&GetActiveCamera()->GetViewMatrix() );
// 
// 		m_pd3dDevice->Present(NULL,NULL,NULL,NULL);
// 	}
// 
// 	return TRUE;
// }


BOOL CWorldEditView::LoadFxShader()
{
	// 	try
	// 	{
	graphics::ShaderManager::instance()->initialize( m_pd3dDevice );

	return graphics::ShaderManager::instance()->LoadFxShader(CWorld::GetAppDataCharDir());

	// 	if ( graphics::ShaderManager::instance()->supportPixelShader( 2, 0 ) )
	// 	{
	// 		try
	// 		{
	// 
	// #if _MSC_VER >= 1400
	// 			sprintf_s( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\RenderObject.fxo" );
	// #else
	// 			sprintf( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\RenderObject.fxo");
	// #endif
	// 			graphics::ShaderEffect* pDiffuseShader = MeNew graphics::ShaderEffect( "MexShader",
	// 				m_pd3dDevice, path );
	// 			pDiffuseShader->setTechnique( "Diffuse" );
	// 			graphics::ShaderManager::instance()->addShader( pDiffuseShader );
	// 
	// #if _MSC_VER >= 1400
	// 			sprintf_s( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\Diffuse.hlsl" );
	// #else
	// 			sprintf( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\Diffuse.hlsl");
	// #endif
	// 			graphics::ShaderVertexPixel* pDiffuseVP = MeNew graphics::ShaderVertexPixel( "MexShaderDiffuse",
	// 				m_pd3dDevice, path, "Diffuse_vp", path, "Diffuse_fp" );
	// 			graphics::ShaderManager::instance()->addShader( pDiffuseVP );
	// 
	// #if _MSC_VER >= 1400
	// 			sprintf_s( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\Specular.hlsl" );
	// #else
	// 			sprintf( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\Specular.hlsl");
	// #endif
	// 			graphics::ShaderVertexPixel* pSpecularVP = MeNew graphics::ShaderVertexPixel( "MexShaderSpecular",
	// 				m_pd3dDevice, path, "Specular_vp", path, "Specular_fp" );
	// 			graphics::ShaderManager::instance()->addShader( pSpecularVP );
	// 
	// #if _MSC_VER >= 1400
	// 			sprintf_s( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\NoLighting.hlsl" );
	// #else
	// 			sprintf( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\NotLighting.hlsl");
	// #endif
	// 			graphics::ShaderVertexPixel* pNotLightingVP = MeNew graphics::ShaderVertexPixel( "MexShaderNoLighting",
	// 				m_pd3dDevice, path, "NoLighting_vp", path, "NoLighting_fp" );
	// 			graphics::ShaderManager::instance()->addShader( pNotLightingVP );
	// 
	// #if _MSC_VER >= 1400
	// 			sprintf_s( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\AlphaTest.hlsl" );
	// #else
	// 			sprintf( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\AlphaTest.hlsl");
	// #endif
	// 			graphics::ShaderVertexPixel* pAlphaTestVP = MeNew graphics::ShaderVertexPixel( "MexShaderAlphaTest",
	// 				m_pd3dDevice, path, "AlphaTest_vp", path, "AlphaTest_fp" );
	// 			graphics::ShaderManager::instance()->addShader( pAlphaTestVP );
	// 
	// #if _MSC_VER >= 1400
	// 			sprintf_s( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\SkyBox.hlsl" );
	// #else
	// 			sprintf( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\SkyBox.hlsl");
	// #endif
	// 			graphics::ShaderVertexPixel* pSkyBoxVP = MeNew graphics::ShaderVertexPixel( "MexShaderSkyBox",
	// 				m_pd3dDevice, path, "SkyBox_vp", path, "SkyBox_fp" );
	// 			graphics::ShaderManager::instance()->addShader( pSkyBoxVP );
	// 
	// #if _MSC_VER >= 1400
	// 			sprintf_s( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\Collision.hlsl" );
	// #else
	// 			sprintf( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\Collision.hlsl");
	// #endif
	// 			graphics::ShaderVertexPixel* pCollisionVP = MeNew graphics::ShaderVertexPixel( "MexShaderCollision",
	// 				m_pd3dDevice, path, "Collision_vp", path, "Collision_fp" );
	// 			graphics::ShaderManager::instance()->addShader( pCollisionVP );
	// 
	// #if _MSC_VER >= 1400
	// 			sprintf_s( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\Particle.hlsl" );
	// #else
	// 			sprintf( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\Particle.hlsl");
	// #endif
	// 			graphics::ShaderVertexPixel* pParticleVP = MeNew graphics::ShaderVertexPixel( "MexShaderParticle",
	// 				m_pd3dDevice, path, "Particle_vp", path, "Particle_fp" );
	// 			graphics::ShaderManager::instance()->addShader( pParticleVP );
	// 
	// #if _MSC_VER >= 1400
	// 			sprintf_s( path, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\Shadow.hlsl" );
	// #else
	// 			sprintf( filename, "%s\\%s", CWorld::GetAppDataCharDir(), "DATA\\SHADER\\Shadow.hlsl");
	// #endif
	// 			graphics::ShaderVertexPixel* pShadowVP = MeNew graphics::ShaderVertexPixel( "MexShaderShadow",
	// 				m_pd3dDevice, path, "Shadow_vp", path, "Shadow_fp" );
	// 			graphics::ShaderManager::instance()->addShader( pShadowVP );
	// 		}
	// 		catch ( const std::exception& e )
	// 		{
	// 			OutputDebugString( e.what() );
	// 		}
	// 
	// 	}
	// 	else
	// 	{
	// 		graphics::ShaderManager::instance()->useShader( false );
	// 	}

	// 	return true;
}

void CWorldEditView::OnDisplayZone()
{
	SetInvertFlag( m_displayFilter, znDF_Zone );
	if( m_displayFilter&znDF_Zone ) {
		g_render->SetShowZone( true );
	}
	else {
		g_render->SetShowZone( false );
	}
}

void CWorldEditView::OnUpdateDisplayZone( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck( (m_displayFilter&znDF_Zone)?1:0 );
}

void CWorldEditView::OnUpdateRenderMinimap( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck( (m_displayFilter & znDF_RenderMinimap) ? 1 : 0 );
}

void CWorldEditView::OnUpdateRenderShadowMapScene( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck( (m_displayFilter & znDF_ShowShadowMapEffect) ? 1 : 0 );
}

void CWorldEditView::OnUpdateRenderTerrainBump( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck( (m_displayFilter & znDF_ShowTerrainBump) ? 1 : 0 );
}

void CWorldEditView::OnUpdateRenderLightView( CCmdUI* pCmdUI )
{
	pCmdUI->SetCheck( (m_displayFilter & znDF_ShowLightView) ? 1 : 0 );
}

void CWorldEditView::OnUpdateShowAABB(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter & znDF_ShowAABB) ? 1 : 0 );
	g_render->SetRenderAABBAndRadius(m_displayFilter & znDF_ShowAABB);
}

void CWorldEditView::OnUpdateShowFog(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( (m_displayFilter & znDF_ShowFog) ? 1 : 0 );

	FogProperty *pFogProp = theApp.GetFogProperty();
	pFogProp->bShowFog = m_displayFilter & znDF_ShowFog;
}

void CWorldEditView::OnSettingTerrainLayer()
{
	short layer = GetMe3dConfig()->GetTerrainRenderLayer();
	layer--;
	if( layer < 2 )
		layer = 4;
	GetMe3dConfig()->SetTerrainRenderLayer(layer);
}

void CWorldEditView::OnLoadSkybox()
{
	CToolWorldSkyboxDlg dlg;
	if( dlg.DoModal() == IDOK )
	{		
		CWorldTile* worldTile = theApp.GetWorld()->GetWorldBuffer()->GetActiveTile();
		if(!worldTile)
			return;
		if( !dlg.m_strFilename.IsEmpty() )
		{
			dlg.m_strFilename = dlg.m_strFilename.MakeLower();
			int nPos = dlg.m_strFilename.Find( CWorld::GetAppDataCharDir() );
			dlg.m_strFilename = dlg.m_strFilename.Mid( strlen( CWorld::GetAppDataCharDir() ) + nPos );
			worldTile->SetSkyBoxPath( dlg.m_strFilename.GetString() );
		}

		// 由于保存Mex文件会崩溃, 更改天空盒的贴图暂时不实现, 2012.5.13 wangshuai
		/*
		if( !dlg.m_strTextureFilename.IsEmpty() )
		{
			if (dlg.m_strFilename.IsEmpty())
			{
				AfxMessageBox("要修改贴图，模型文件不能为空！");
				return;
			}

			dlg.m_strTextureFilename = dlg.m_strTextureFilename.MakeLower();
			int nPos = dlg.m_strTextureFilename.Find( CWorld::GetAppDataCharDir() );
			dlg.m_strTextureFilename = dlg.m_strTextureFilename.Mid( strlen( CWorld::GetAppDataCharDir() ) + nPos );
			MexAnimCtrl* pModel = GetSTSkyBox()->GetSkybox();
			if( pModel && pModel->GetMex())
			{
				MexReplaceableTextureProj* pReplaceableTextures = (MexReplaceableTextureProj*)pModel->GetReplaceableTextureProj();
				if( pReplaceableTextures )
				{
					pReplaceableTextures->ReplaceTexture( 0, pModel->GetMex()->GetFilename(), dlg.m_strTextureFilename.GetString(), FALSE);
				}
				// 保存Mex文件
				pModel->GetMex()->SaveToFile(dlg.m_strFilename.GetString(), 0);
			}
		}
		*/

		// 设置Dirty标记
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify(CURRENTTILE);
	}
}

void CWorldEditView::OnSaveShMp()
{
	m_BSaveShowmap = true;
}
void CWorldEditView::OnOperationLocate()
{
	CLocateDlg dlg;
	if(IDOK == dlg.DoModal())
	{
		CBaseTool* tool = m_toolManager->GetActiveTool();
		ASSERT(tool != NULL);

		SwCamera* pCamera	= GetActiveCamera();
		ASSERT(pCamera != NULL);

		CWorldTile* pTile = theApp.GetWorld()->GetWorldBuffer()->GetActiveTile();
		if(NULL == pTile)
			return;

		D3DXVECTOR3 worldPos((float)dlg.m_pointX, (float)dlg.m_pointY, 0.0f);	//目标点的世界坐标
		if(worldPos.x < 0 || worldPos.x >= pTile->GetWidth() ||
			worldPos.y < 0 || worldPos.y >= pTile->GetDepth())
		{
			AfxMessageBox(_T("Command locate: 所输入的坐标超出范围。"));
			return;
		}

		//转换到camera 坐标系中。关键的地方，避免camera的eye对于坐标计算累计的影响
		//old solution
		/*		{
		//重置camera的eye，
		camera->SetPos(Vector(0.0f, 0.0f, 0.0f));
		camera->Update(0.0f, 0.0f);

		//const D3DXMATRIX &m = camera->GetViewMatrix();
		D3DXMATRIX m;
		D3DXMatrixInverse( &m, NULL, &camera->GetViewMatrix() );

		D3DXVec3TransformCoord(&worldPos, &worldPos, &m);
		}
		*/

		//new solution
		/*		{
		//const D3DXMATRIX &m = camera->GetViewMatrix();
		D3DXMATRIX m;
		D3DXMatrixInverse( &m, NULL, &camera->GetViewMatrix() );

		//D3DXVec3TransformNormal(&worldPos, &worldPos, &m);
		}
		*/


		CWorldChunk *pChunk = pTile->GetChunkFromPos(worldPos.x, worldPos.y);
		if(NULL == pChunk)
		{
			AfxMessageBox(_T("Command locate: 没有找到chunk。"));
			return;
		}

		//worldPos.z = pChunk->GetHeight()[1];

		CNdlEditWorldPicker* pWorldPicker = GetWorldPicker();
		if( NULL == pWorldPicker )
			return;

		pWorldPicker->GetHeight(worldPos.x, worldPos.y, worldPos.z);


		//应该让worldPos为视野中心
		const D3DXVECTOR3 &dir = pCamera->GetDir();
		const D3DXVECTOR3 &lookAt = worldPos;
		Vector eye(lookAt.x - dir.x, lookAt.y - dir.y, lookAt.z - dir.z);
		eye += Vector(dir.x, dir.y, dir.z) * (-7.5 * 6);

		CToolVertex *pTool = (CToolVertex *)(m_toolManager->GetTool(TOOL_VERTEX));
		if(pTool)
		{
			flt32 origin[2] = {worldPos.x, worldPos.y};
			pTool->UpdateBrushShape(origin);
			SetLocationFlag();
		}

		pCamera->SetPos(eye);
		pCamera->Update(0.f,0.f);
		theApp.GetWorld()->SetActivePos(worldPos.x, worldPos.y );
	}
}
void CWorldEditView::OnUseDynamicLight()
{
	m_bUseDynamicLight = !m_bUseDynamicLight;
}
void CWorldEditView::OnUpdateUseDynamicLight(CCmdUI* pCmdUI)
{
	if( m_bUseDynamicLight )
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}

void CWorldEditView::OnEditCopy()
{
	CBaseTool* tool = m_toolManager->GetActiveTool();
	if(tool != NULL && TOOL_OBJECT == tool->GetToolId())
		return;
}

void CWorldEditView::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	CBaseTool* tool = m_toolManager->GetActiveTool();
	if(NULL == tool || tool->GetToolId() != TOOL_OBJECT)
		pCmdUI->Enable(FALSE);

	pCmdUI->Enable(TRUE);
}

bool CWorldEditView::GetRayFromPoint( const CPoint& point, Vector& outRayPt, Vector& outRayDir )
{
	SwCamera* pCamera = GetActiveCamera();
	if( !pCamera )
		return false;
	CEditCamera* pEditCamera = dynamic_cast<CEditCamera*>(pCamera);
	if(!pEditCamera)
		return false;

	Vector pos = GetActiveCamera()->GetPos();
	UpdateHorizontal( pos );

	//setup ray
	return pEditCamera->ScreenToWorldRay( Vector2(point.x, point.y), outRayPt, outRayDir );
}

void CWorldEditView::OnViewDebugMsg()
{
	m_bViewDebugMsg = !m_bViewDebugMsg;
}
void CWorldEditView::OnUpdateViewDebugMsg(CCmdUI* pCmdUI)
{
	if( m_bViewDebugMsg )
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}
