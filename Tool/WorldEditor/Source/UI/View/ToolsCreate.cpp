/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolsCreate.cpp
* Date: 	05/29/2007
* Desc:
*
*******************************************************************************/
#include "stdAfx.h"
#include "Resource/Resource.h"

#include "ui/Custom/TexturePreviewWnd.h"
#include "Edit/BaseTool.h"
#include "ui/ToolsWnd/ToolDoodadDlg.h"
#include "ui/ToolsWnd/ToolLiquidDlg.h"
#include "ui/ToolsWnd/ToolTransportDlg.h"
#include "ui/ToolsWnd/ToolFlyRouteDlg.h"
#include "ui/ToolsWnd/MonsterQuadDlg.h"
#include "ui/ToolsWnd/ToolTerrain.h"
#include "ui/ToolsWnd/ToolLayer.h"
#include "ui/ToolsWnd/ToolModel.h"
#include "ToolsCreate.h"

////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CToolsCreate, CScrollView)
CToolsCreate::CToolsCreate()
{
	m_nCurrentTool = emTT_Terrain;

}

CToolsCreate::~CToolsCreate()
{
}

BEGIN_MESSAGE_MAP(CToolsCreate, CWnd)
	//{{AFX_MSG_MAP(CToolsCreate)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_TOOLS_TERRAIN, ID_TOOLS_LIQUID, OnToolsCommand )
	ON_COMMAND(ID_TOOLS_TRANSPORT, OnToolsTransport )
	ON_COMMAND(ID_TOOLS_FLYROUTE, OnToolsFlyRoute )
	ON_COMMAND(ID_TOOLS_NPC,OnToolsNpc)
	ON_COMMAND(ID_TOOLS_MONSTER, OnToolsMonster )
	ON_COMMAND(ID_TOOLS_STATICLIGHT, OnToolsStaticLight )
	ON_UPDATE_COMMAND_UI_RANGE(ID_TOOLS_TERRAIN, ID_TOOLS_LIQUID, OnUpdateToolsCommand )
	ON_UPDATE_COMMAND_UI(ID_TOOLS_TRANSPORT, OnUpdateToolsCommand )
	ON_UPDATE_COMMAND_UI(ID_TOOLS_MONSTER, OnUpdateToolsCommand )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CToolsCreate::OnInitialUpdate()
{
	VERIFY( m_wndToolBar.CreateToolBar(WS_VISIBLE|WS_CHILD|CBRS_TOOLTIPS|CBRS_SIZE_FIXED, this) );
	VERIFY( m_wndToolBar.LoadToolBar( IDR_TOOLBAR_ATOM ) );

	m_wndToolBar.SetButtonSize(CSize(23, 23));

	m_wndTerrain.Create( IDD_DLG_TERRAIN,this );
	m_wndTerrain.ShowWindow( SW_HIDE );

	m_wndLayer.Create( IDD_DLG_LAYER, this );
	m_wndLayer.ShowWindow( SW_HIDE );

	m_wndDoodad.Create( IDD_DLG_DOODADS, this );
	m_wndDoodad.ShowWindow( SW_HIDE );

	m_wndModel.Create( IDD_DLG_MODEL, this );
	m_wndModel.ShowWindow( SW_HIDE );

	m_wndLiquid.Create( IDD_DLG_LIQUID, this );
	m_wndLiquid.ShowWindow( SW_HIDE );

	m_wndTransport.Create( IDD_DLG_TRANSPORT, this );
	m_wndTransport.ShowWindow( SW_HIDE );

	m_wndFlyRoute.Create( IDD_DLG_FLYROUTE, this );
	m_wndFlyRoute.ShowWindow( SW_HIDE );

	m_wndMonsterQuad.Create( IDD_DLG_MONSTERQUAD, this );
	m_wndMonsterQuad.ShowWindow( SW_HIDE );

	m_wndNpcEditor.Create(IDD_DIALOG_NPC,this);
	m_wndNpcEditor.ShowWindow(SW_HIDE);

	m_wndStaticLight.Create(IDD_DIALOG_STATIC_LIGHT, this);
	m_wndStaticLight.ShowWindow(SW_HIDE);
}

/////////////////////////////////////////////////////////////////////////////
// CExplorerView message handlers
void CToolsCreate::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CSize sz(0);
	if (m_wndToolBar.GetSafeHwnd())
	{
		sz = m_wndToolBar.CalcDockingLayout(cx, /*LM_HIDEWRAP|*/ LM_HORZDOCK|LM_HORZ | LM_COMMIT);

		m_wndToolBar.MoveWindow( 0, 0, cx, sz.cy );
		m_wndToolBar.Invalidate(FALSE);
	}
	if( m_wndTerrain.GetSafeHwnd() )
		m_wndTerrain.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	if( m_wndLayer.GetSafeHwnd() )
		m_wndLayer.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	if( m_wndDoodad.GetSafeHwnd() )
		m_wndDoodad.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	if( m_wndModel.GetSafeHwnd() )
		m_wndModel.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	if( m_wndLiquid.GetSafeHwnd() )
		m_wndLiquid.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	if( m_wndTransport.GetSafeHwnd() )
		m_wndTransport.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	if( m_wndFlyRoute.GetSafeHwnd() )
		m_wndFlyRoute.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	if(m_wndNpcEditor.GetSafeHwnd())
		m_wndNpcEditor.MoveWindow(0,sz.cy, cx, cy - sz.cy);
	if(m_wndStaticLight.GetSafeHwnd())
		m_wndStaticLight.MoveWindow(0,sz.cy, cx, cy - sz.cy);
}

BOOL CToolsCreate::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CToolsCreate::OnSetFocus(CWnd* pOldWnd)
{
	
}

void CToolsCreate::OnToolsCommand(UINT nID)
{
	UINT newTool = (nID-ID_TOOLS_TERRAIN);
	if( m_nCurrentTool == newTool )
		return;
	
	m_nCurrentTool = newTool;

	SetTool( (emToolType)m_nCurrentTool );
}

void CToolsCreate::OnUpdateToolsCommand(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck( m_nCurrentTool == (pCmdUI->m_nID-ID_TOOLS_TERRAIN)? TRUE: FALSE );
}

void CToolsCreate::SetActive()
{
	if( m_nCurrentTool < (ID_TOOLS_TRANSPORT-ID_TOOLS_TERRAIN) )
		SetTool( (emToolType)m_nCurrentTool );
}

void CToolsCreate::SetTool( emToolType toolType )
{
	m_wndTerrain.ShowWindow( SW_HIDE );
	m_wndModel.ShowWindow( SW_HIDE );
	m_wndDoodad.ShowWindow( SW_HIDE );
	m_wndLiquid.ShowWindow( SW_HIDE );
	m_wndLayer.ShowWindow( SW_HIDE );
	m_wndTransport.ShowWindow( SW_HIDE );	
	m_wndFlyRoute.ShowWindow( SW_HIDE );	
	m_wndMonsterQuad.ShowWindow(SW_HIDE);
	m_wndNpcEditor.ShowWindow(SW_HIDE);
	m_wndStaticLight.ShowWindow(SW_HIDE);

    CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
    pView->SetActiveCameraID(TOOL_CAMERA);

	switch(	toolType )
	{
	case emTT_Terrain:
		m_wndTerrain.SetActive();
		m_wndTerrain.ShowWindow( SW_SHOW );
		break;
	case emTT_Layer:
		m_wndLayer.SetActive();
		m_wndLayer.ShowWindow( SW_SHOW );
		break;
	case emTT_Doodad:
		m_wndDoodad.SetActive();
		m_wndDoodad.ShowWindow( SW_SHOW );
		break;
	case emTT_Model:
		m_wndModel.SetActive();
		m_wndModel.ShowWindow( SW_SHOW );
		break;
	case emTT_Liquid:
		m_wndLiquid.SetActive();
		m_wndLiquid.ShowWindow( SW_SHOW );
		break;
	case emTT_Transport:
		m_wndTransport.SetActive();
		m_wndTransport.ShowWindow( SW_SHOW );
		break;
	case emTT_FlyRoute:
		m_wndFlyRoute.SetActive();
		m_wndFlyRoute.ShowWindow( SW_SHOW );
		break;
	case emTT_Monster:
		m_wndMonsterQuad.SetActive();
		m_wndMonsterQuad.ShowWindow( SW_SHOW );
		break;
	case emIT_NPC:
		m_wndNpcEditor.SetActive();
		m_wndNpcEditor.ShowWindow(SW_SHOW);
		break;
	case emTT_StaticLight:
		m_wndStaticLight.SetActive();
		m_wndStaticLight.ShowWindow(SW_SHOW);
		break;
	default:
		Trace( "Unknown tools type[%d]! \n", toolType );
		break;
	}
}

void CToolsCreate::OnToolsTransport()
{
	OnToolsCommand(ID_TOOLS_TRANSPORT);
}

void CToolsCreate::OnToolsFlyRoute()
{
	OnToolsCommand(ID_TOOLS_FLYROUTE);
}

void CToolsCreate::OnToolsMonster()
{
	OnToolsCommand(ID_TOOLS_MONSTER);
}

void CToolsCreate::Reset()
{
	m_nCurrentTool = emTT_Terrain;
	SetTool( (emToolType)m_nCurrentTool );
}

void CToolsCreate::OnToolsNpc()
{
	OnToolsCommand(ID_TOOLS_NPC);
}

void CToolsCreate::OnToolsStaticLight()
{
	OnToolsCommand(ID_TOOLS_STATICLIGHT);
}