/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolsScene.cpp
* Date: 	06/07/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include "ui/Custom/TexturePreviewWnd.h"
#include "ui/Custom/TextureNavigationWnd.h"
#include "Ui/ToolsScene/ToolWorld.h"
#include "ui/ToolsScene/ToolEnvironment.h"
#include "ui/ToolsScene/ToolWorldLight.h"
#include "ui/ToolsScene/ToolWorldFog.h"
#include "ui/ToolsScene/ToolZoneDlg.h"
#include "ui/ToolsScene/ToolClickToAddDlg.h"
#include "ToolsScene.h"

IMPLEMENT_DYNCREATE(CToolsScene, CWnd)
////////////////////////////////////////////////////////////////////////////////
CToolsScene::CToolsScene()
{
}

CToolsScene::~CToolsScene()
{

}

BEGIN_MESSAGE_MAP(CToolsScene, CWnd)
	//{{AFX_MSG_MAP(CToolsScene)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_TOOLBAR_SECNE_WORLD, ID_TOOLBAR_SCENE_ZONE, OnToolsCommand )
	ON_COMMAND(ID_TOOLS_CLICK2ADD, OnToolsClick2Add )
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_SECNE_WORLD, OnUpdateToolsCommandWorld )
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_SECNE_ENV, OnUpdateToolsCommandEnvironment )
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_SCENE_LIGHT, OnUpdateToolsCommandWorldLight )
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_SCENE_FOG, OnUpdateToolsCommandWorldFog )
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_SCENE_ZONE, OnUpdateToolsCommandZone )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CToolsScene::OnInitialUpdate()
{
	VERIFY( m_wndToolBar.CreateToolBar(WS_VISIBLE|WS_CHILD|CBRS_TOOLTIPS|CBRS_SIZE_FIXED, this) );
	VERIFY( m_wndToolBar.LoadToolBar( IDR_WORLD_EXPLORER ) );
	m_wndToolBar.SetButtonSize(CSize(23, 23));
	
	m_curSceneWndType =	emSWT_World;
	
	m_wndWorld.Create( IDD_DLG_WORLD,this );
	m_wndWorld.ShowWindow( SW_SHOW );

	m_wndEnvironment.Create( IDD_DLG_ENV,this );
	m_wndEnvironment.ShowWindow( SW_HIDE );

	m_wndWorldLight.Create( IDD_DLG_LIGHT, this );
	m_wndWorldLight.ShowWindow( SW_HIDE );

	m_wndWorldFog.Create( IDD_DLG_FOG, this );
	m_wndWorldFog.ShowWindow( SW_HIDE );

	m_wndZone.Create( IDD_DLG_ZONE, this );
	m_wndZone.ShowWindow( SW_HIDE );
	m_wndClick2Add.Create( IDD_DLG_Click2Add, this );
	m_wndClick2Add.ShowWindow( SW_HIDE );
}

void CToolsScene::SetActive()
{
	if ( emSWT_World != m_curSceneWndType )
	{
		SwitchWnd( m_curSceneWndType );
	}
}

void CToolsScene::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	
	CSize sz(0);
	if (m_wndToolBar.GetSafeHwnd())	{
		sz = m_wndToolBar.CalcDockingLayout(cx, /*LM_HIDEWRAP|*/ LM_HORZDOCK|LM_HORZ | LM_COMMIT);
		
		m_wndToolBar.MoveWindow( 0, 0, cx, sz.cy );
		m_wndToolBar.Invalidate(FALSE);
	}
	if( m_wndWorld.GetSafeHwnd() )
		m_wndWorld.MoveWindow(0, sz.cy, cx, cy - sz.cy);

	if( m_wndEnvironment.GetSafeHwnd() )
		m_wndEnvironment.MoveWindow(0, sz.cy, cx, cy - sz.cy);

	if( m_wndWorldLight.GetSafeHwnd() )
		m_wndWorldLight.MoveWindow(0, sz.cy, cx, cy - sz.cy);

	if( m_wndWorldFog.GetSafeHwnd() ) 
		m_wndWorldFog.MoveWindow(0, sz.cy, cx, cy - sz.cy);

	if( m_wndZone.GetSafeHwnd() )
		m_wndZone.MoveWindow(0, sz.cy, cx, cy - sz.cy);
	if( m_wndClick2Add.GetSafeHwnd() )
		m_wndClick2Add.MoveWindow(0, sz.cy, cx, cy - sz.cy);
}

BOOL CToolsScene::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CToolsScene::OnSetFocus(CWnd* pOldWnd)
{

}

void CToolsScene::SwitchWnd( emSceneWndType wndType )
{
	m_wndWorld.ShowWindow( SW_HIDE );
	m_wndEnvironment.ShowWindow( SW_HIDE );
	m_wndWorldLight.ShowWindow( SW_HIDE );
	m_wndWorldFog.ShowWindow( SW_HIDE );
	m_wndZone.ShowWindow( SW_HIDE );
	m_wndClick2Add.ShowWindow( SW_HIDE );	
	switch( m_curSceneWndType ) {
	case emSWT_World:
		m_wndWorld.SetActive();
		m_wndWorld.ShowWindow( SW_SHOW );
		break;
	case emSWT_Environment:
		m_wndEnvironment.SetActive();
		m_wndEnvironment.ShowWindow( SW_SHOW );
		break;
	case emSWT_WorldLight:
		m_wndWorldLight.SetActive();
		m_wndWorldLight.ShowWindow( SW_SHOW );
		break;
	case emSWT_WorldFog:
		m_wndWorldFog.SetActive();
		m_wndWorldFog.ShowWindow( SW_SHOW );
		break;
	case emSWT_Zone:
		m_wndZone.SetActive();
		m_wndZone.ShowWindow( SW_SHOW );
		break;
	case emTT_Click2Add:
		m_wndClick2Add.SetActive();
		m_wndClick2Add.ShowWindow( SW_SHOW );
		break;
	default:
		break;
	}
}

void CToolsScene::OnToolsCommand(UINT nID)
{
	sInt32 id = nID - ID_TOOLBAR_SECNE_WORLD;
	if( id != m_curSceneWndType ) {
		m_curSceneWndType = (emSceneWndType)id;
		
		SwitchWnd( m_curSceneWndType );
	}
}

void CToolsScene::OnUpdateToolsCommandWorld(CCmdUI* pCmdUI)
{
	if ( emSWT_World == m_curSceneWndType ) {
		pCmdUI->SetCheck( 1 );
	}
	else {
		pCmdUI->SetCheck( 0 );
	}
}

void CToolsScene::OnUpdateToolsCommandEnvironment(CCmdUI* pCmdUI)
{
	if ( emSWT_Environment == m_curSceneWndType ) {
		pCmdUI->SetCheck( 1 );
	}
	else {
		pCmdUI->SetCheck( 0 );
	}
}

void CToolsScene::OnUpdateToolsCommandWorldLight(CCmdUI* pCmdUI)
{
	if ( emSWT_WorldLight == m_curSceneWndType ) {
		pCmdUI->SetCheck( 1 );
	}
	else {
		pCmdUI->SetCheck( 0 );
	}

}

void CToolsScene::OnUpdateToolsCommandWorldFog(CCmdUI* pCmdUI)
{
	if ( emSWT_WorldFog == m_curSceneWndType ) {
		pCmdUI->SetCheck( 1 );
	}
	else {
		pCmdUI->SetCheck( 0 );
	}
}

void CToolsScene::OnUpdateToolsCommandZone( CCmdUI* pCmdUI )
{
	if ( emSWT_Zone == m_curSceneWndType ) {
		pCmdUI->SetCheck( 1 );
	}
	else {
		pCmdUI->SetCheck( 0 );
	}

}

void CToolsScene::OnToolsClick2Add()
{
	OnToolsCommand(ID_TOOLS_CLICK2ADD);
}