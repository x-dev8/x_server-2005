// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "WorldEditor.h"
#include "Resource/Resource.h"
#include "ui/Custom/TexturePreviewWnd.h"
#include "ui/Custom/TextureNavigationWnd.h"
#include "Edit/BaseTool.h"

#include "ui/ToolsWnd/ToolDoodadDlg.h"
#include "ui/ToolsWnd/ToolLiquidDlg.h"
#include "ui/ToolsWnd/ToolTransportDlg.h"
#include "ui/ToolsWnd/ToolFlyRouteDlg.h"
#include "ui/ToolsScene/ToolClickToAddDlg.h"
#include "ui/ToolsWnd/MonsterQuadDlg.h"
#include "ui/ToolsWnd/ToolModel.h"
#include "ui/ToolsWnd/ToolLayer.h"
#include "ui/ToolsWnd/ToolTerrain.h"
#include "ui/ToolsScene/ToolWorld.h"
#include "ui/ToolsScene/ToolEnvironment.h"
#include "ui/ToolsScene/ToolWorldLight.h"
#include "ui/ToolsScene/ToolWorldFog.h"
#include "ui/ToolsScene/ToolZoneDlg.h"

#include "ui/View/ToolsScene.h"
#include "ui/View/ToolsCreate.h"
#include "ui/View/ToolsModify.h"
#include "ui/View/ToolsTabView.h"
#include "MainFrm.h"
#include "Resource/Resource.h"
#include "ui/ToolsWnd/DlgNpcEditor.h"



// CMainFrame
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_ACTIVATEAPP()
	ON_XTP_CREATECONTROL()
	//ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
    //ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_STATUS_PROMPT,           // status line indicator
	ID_STATUS_MOUSEPOS,
	ID_STATUS_WORLDPOS,
	ID_STATUS_COUNT,
};
const int NUMSTATUSPANES = 4;

enum
{
	SBI_PROMPT = 0,
	SBI_MOUSEPOS,
	SBI_WORLDPOS,
	SBI_LOOPCOUNT,
	SBI_PROCESS
};

struct
{
	int nIndex;
	UINT nID;
	UINT nStyle;
	int cxWidth;
} paneinfo[NUMSTATUSPANES] = 
{
	{ SBI_PROMPT,		ID_SEPARATOR,			SBPS_STRETCH|SBPS_NOBORDERS, 0 },
	{ SBI_MOUSEPOS,		ID_STATUS_MOUSEPOS,		SBPS_NORMAL|SBPS_NOBORDERS, 450 },
	{ SBI_WORLDPOS,		ID_STATUS_WORLDPOS,		SBPS_NORMAL|SBPS_NOBORDERS, 380 },
	{ SBI_LOOPCOUNT,	ID_STATUS_COUNT,		SBPS_NORMAL|SBPS_NOBORDERS, 140 },
};

static UINT uHideCmds[] = 
{
	ID_FILE_PRINT,
	ID_FILE_PRINT_PREVIEW,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_wndWorldExplorerView	= NULL;
}

CMainFrame::~CMainFrame()
{
	SAFE_DELETE( m_wndWorldExplorerView );
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||!m_wndStatusBar.SetIndicators(NULL,NUMSTATUSPANES) )
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	for(int i = 0; i < NUMSTATUSPANES; i++)
	{
		m_wndStatusBar.SetPaneInfo(paneinfo[i].nIndex, paneinfo[i].nID,	paneinfo[i].nStyle, paneinfo[i].cxWidth );
	}
	// Create the edit control and add it to the status bar
	if (!m_wndProgCtrl.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH,CRect(0,0,0,0), &m_wndStatusBar, 0))
	{
		TRACE0("Failed to create process control.\n");
		return -1;
	}
	int iIndex = m_wndStatusBar.GetPaneCount();
	
    // Initialize the command bars
    if (!InitCommandBars())
        return -1;

     // Set Office 2003 Theme
    CXTPPaintManager::SetTheme(xtpThemeOfficeXP);

   // Get a pointer to the command bars object.
    CXTPCommandBars* pCommandBars = GetCommandBars();
    if(pCommandBars == NULL)
    {
        TRACE0("Failed to create command bars object.\n");
        return -1;      // fail to create
    }

    // Add the menu bar
    CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(
        _T("Menu Bar"), IDR_MAINFRAME);       
    if(pMenuBar == NULL)
    {
        TRACE0("Failed to create menu bar.\n");
        return -1;      // fail to create
    }

    // Create ToolBar
    CXTPToolBar* pToolBar = (CXTPToolBar*)
        pCommandBars->Add(_T("Standard"), xtpBarTop);
    if (!pToolBar || !pToolBar->LoadToolBar(IDR_MAINFRAME)){
        TRACE0("Failed to create toolbar\n");
        return -1;
    }
	CXTPToolBar* pEditBar = (CXTPToolBar*)pCommandBars->Add(_T("Edit"), xtpBarTop);
	if (!pEditBar ||!pEditBar->LoadToolBar(IDR_TB_EDIT)){
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	
	// Hide array of commands
	pCommandBars->HideCommands(uHideCmds, _countof(uHideCmds));

	// Set "Always Show Full Menus" option to the FALSE
	pCommandBars->GetCommandBarsOptions()->bAlwaysShowFullMenus = FALSE;

    // Load the previous state for toolbars and menus.
    LoadCommandBars(_T("CommandBars"));

	//// Initialize the docking pane manager and set the
	//// initial them for the docking panes.  Do this only after all
	//// control bars objects have been created and docked.
	//m_paneManager.InstallDockingPanes(this);
    //// Set Office 2003 Theme
	//m_paneManager.SetTheme(xtpPaneThemeNativeWinXP);

	// Create docking panes.
	//CXTPDockingPane* worldPane	= m_paneManager.CreatePane(
	//	IDR_PANE_WORLD_EXPLORER, CRect(0, 0, 300, 120), xtpPaneDockLeft);
	//
	//CXTPDockingPane* toolsPane = m_paneManager.CreatePane(
	//	IDR_PANE_WORLD_TOOLS, CRect(0, 0,300, 120), xtpPaneDockBottom, worldPane );
	
	// Set the icons for the docking pane tabs.
	//int nIDIcons[] = { IDR_PANE_WORLD_EXPLORER };
	//m_paneManager.SetIcons(IDB_BITMAP_ICONS, nIDIcons, _countof(nIDIcons), RGB(0, 255, 0));
	
    // Load the previous state for docking panes.
    //CXTPDockingPaneLayout layoutNormal(&m_paneManager);
    //if (layoutNormal.Load(_T("NormalLayout"))) 
    //{
    //    m_paneManager.SetLayout(&layoutNormal); 
    //}
	theApp.SetMainFrame( this );

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	m_wndSpliter.CreateStatic(this, 1, 2);
	m_wndSpliter.CreateView(0, 0, RUNTIME_CLASS(CToolsTabView), CSize(240, 0), pContext);
	m_wndSpliter.CreateView(0, 1, pContext->m_pNewViewClass, CSize(0, 0), pContext);
	
	DWORD dw	= m_wndSpliter.GetSplitterStyle();
	dw			= dw | XT_SPLIT_NOSIZE | XT_SPLIT_NOBORDER;
	m_wndSpliter.SetSplitterStyle(dw);
	m_wndSpliter.SetActivePane( 0, 1);
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	cs.style |= WS_CLIPCHILDREN|WS_CLIPSIBLINGS;


	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers


void CMainFrame::OnClose() 
{

	// Save the current state for toolbars and menus.
    //SaveCommandBars(_T("CommandBars"));

    // Save the current state for docking panes.
    //CXTPDockingPaneLayout layoutNormal(&m_paneManager);
    //m_paneManager.GetLayout(&layoutNormal); 
    //layoutNormal.Save(_T("NormalLayout"));

	CFrameWnd::OnClose();
}


void CMainFrame::OnCustomize()
{
    //// Get a pointer to the command bars object.
    //CXTPCommandBars* pCommandBars = GetCommandBars();
    //if(pCommandBars != NULL)
    //{
    //    // Instanciate the customize dialog object.
    //    CXTPCustomizeSheet dlg(pCommandBars);

    //    // Add the options page to the customize dialog.
    //    CXTPCustomizeOptionsPage pageOptions(&dlg);
    //    dlg.AddPage(&pageOptions);

    //    // Add the commands page to the customize dialog.
    //    CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
    //    pCommands->AddCategories(IDR_MAINFRAME);

    //    // Use the command bar manager to initialize the 
    //    // customize dialog.
    //    pCommands->InsertAllCommandsCategory();
    //    pCommands->InsertBuiltInMenus(IDR_MAINFRAME);
    //    pCommands->InsertNewMenuCategory();

    //    // Dispaly the dialog.
    //    dlg.DoModal();
    //}
}

int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->bToolBar)
	{
		CXTPToolBar* pToolBar = DYNAMIC_DOWNCAST(CXTPToolBar, lpCreateControl->pCommandBar);
		if (!pToolBar)
			return FALSE;

		if (lpCreateControl->nID == ID_BTN_SELECT_FILTER_EX && pToolBar->GetBarID() == IDR_TB_EDIT)
		{
			CXTPControlComboBox* pComboSelect = (CXTPControlComboBox*)CXTPControlComboBox::CreateObject();
			pComboSelect->SetDropDownListStyle();

			pComboSelect->AddString(_T("地表装饰物"));
			pComboSelect->AddString(_T("建筑"));
			pComboSelect->SetDropDownWidth(150);

			lpCreateControl->pControl = pComboSelect;
			return TRUE;
		}
	}
	return FALSE;
}

void CMainFrame::OnActivateApp(  BOOL bActive, DWORD dwThreadID )
{
	theApp.OnActivateApp( bActive == TRUE );
}

CWnd* CMainFrame::CreateTerrainWnd()
{

	return NULL;
}

CWnd* CMainFrame::CreateLayerWnd()
{

	return NULL;
}

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	//if (wParam == XTP_DPN_SHOWWINDOW)
 //   {
 //       CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
 //       
 //       if (!pPane->IsValid())
 //       {
 //           switch (pPane->GetID())
 //           {
 //           case IDR_PANE_WORLD_TOOLS:
 //               {                           
 //                   break;
 //               }
	//		case IDR_PANE_WORLD_EXPLORER:
	//			{
	//				m_wndWorldExplorerView	= new CWorldExplorerView();
	//				m_wndWorldExplorerView->Create( _T("STATIC"), NULL, WS_CHILD, CRect(0, 0, 0, 0), this, 0 );
	//				((CWorldExplorerView*)m_wndWorldExplorerView)->OnInitialUpdate();
	//				pPane->Attach( m_wndWorldExplorerView );
	//				break;
	//			}
 //           }
 //       }
        return TRUE;
    //}
    //return FALSE;
}

void CMainFrame::UpdateProgress( int pos )
{
	//m_wndProgCtrl.SetPos( pos );
}

CString NextPromptText;
CXTPStatusBar *StatusBar = 0;
VOID CALLBACK AfterFistPromptTextProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	// 显示下一条提示
	StatusBar->SetPaneText( SBI_PROMPT, NextPromptText );
	::KillTimer(NULL, idEvent);
}

void CMainFrame::SetPromptText( LPCTSTR szText, DWORD dwTimeAfter, LPCTSTR szNextText)
{
	m_wndStatusBar.SetPaneText( SBI_PROMPT, szText );
	if (dwTimeAfter > 0 && szNextText != NULL)
	{
		NextPromptText = szNextText;
		StatusBar = &m_wndStatusBar;
		::SetTimer(NULL, 0, dwTimeAfter, AfterFistPromptTextProc);
	}
}

void CMainFrame::SetMousePosText( sInt32 posX, sInt32 posY, const Vector& rayPt, const Vector& rayDir )
{
	CString prompt;
	prompt.Format( _T("Mouse:(%d,%d) Ray: [(%4.4f,%4.4f,%4.4f)(%1.4f,%1.4f,%1.4f)]")
		, posX, posY, rayPt.x, rayPt.y, rayPt.z, rayDir.x, rayDir.y, rayDir.z );
	m_wndStatusBar.SetPaneText( SBI_MOUSEPOS, prompt );
}

void CMainFrame::SetWorldPosText( flt32 posX, flt32 posY, flt32 posZ ,flt32 angle)
{
	CString prompt;
	prompt.Format( _T("xyz:(%6.2f,%6.2f,%6.2f), angle: %6.2f, chunk: %d/%d"), posX, posY, posZ, 
		angle, g_render->GetCurTileVisibleChunkCount(), g_render->GetCurTileChunkCount());
	m_wndStatusBar.SetPaneText( SBI_WORLDPOS, prompt );
}

void CMainFrame::SetLoopCountText( sInt32 countA, sInt32 countB )
{
	CString prompt;
	prompt.Format( _T("Loop:(%d,%d)"), countA, countB );
	m_wndStatusBar.SetPaneText( SBI_LOOPCOUNT, prompt );
}

