// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "QuestEditor.h"

#include "MainFrm.h"
#include "QuestEditorView.h"

#include "PositionFind.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMainFrame *theMainFrame;
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_BATCH, &CMainFrame::OnFileBatch)
	ON_COMMAND(ID_FILE_OPEN, &CMainFrame::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVEQUEST, &CMainFrame::OnFileSave)
	ON_COMMAND(ID_FILE_SAVEAS, &CMainFrame::OnFileSaveAs)
	ON_COMMAND(ID_APP_EXIT, &CMainFrame::OnAppExit)
	ON_COMMAND(ID_FILE_TOP, &CMainFrame::OnFileTop)
	ON_COMMAND(ID_FILE_ADD, &CMainFrame::OnFileAdd)
	ON_COMMAND(ID_FILE_DELETE, &CMainFrame::OnFileDelete)
	ON_COMMAND(ID_FILE_DELETEQUEST, &CMainFrame::OnFileDeletequest)
	ON_COMMAND(ID_FILE_FIND, &CMainFrame::OnFileFind)
	ON_COMMAND(ID_FILE_NEXT, &CMainFrame::OnFileNext)
	ON_COMMAND(ID_FILE_STRING, &CMainFrame::OnFileString)
	ON_COMMAND(ID_FILE_NPC, &CMainFrame::OnFileNpc)
	ON_COMMAND(ID_FILE_EDIT, &CMainFrame::OnFileEdit)
	ON_COMMAND(ID_FILE_STRINGEDIT, &CMainFrame::OnFileStringEdit)
	ON_COMMAND(ID_FILE_POSITION, &CMainFrame::OnFilePosition)
	ON_COMMAND(ID_DROPDELETE, &CMainFrame::OnDropDelete)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

	m_bWindowsTop = false;

	theMainFrame = this;
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
	//	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("Failed to create toolbar\n");
	//	return -1;      // fail to create
	//}

	//if (!m_wndStatusBar.Create(this) ||
	//	!m_wndStatusBar.SetIndicators(indicators,
	//	  sizeof(indicators)/sizeof(UINT)))
	//{
	//	TRACE0("Failed to create status bar\n");
	//	return -1;      // fail to create
	//}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

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


void CMainFrame::OnFileBatch()
{
	// TODO: Add your command handler code here
	theEditor->m_checkBatch.SetCheck( (theEditor->m_checkBatch.GetCheck() == 0) );
}

void CMainFrame::OnFileOpen()
{
	// TODO: Add your command handler code here
	theEditor->OnFileLoadQuestFile();

}

void CMainFrame::OnFileSave()
{
	// TODO: Add your command handler code here
	theEditor->OnFileSaveQuestFile();
}

void CMainFrame::OnFileSaveAs()
{
	// TODO: Add your command handler code here
	theEditor->OnFileSaveAt();
}

void CMainFrame::OnAppExit()
{
	// TODO: Add your command handler code here
	this->OnClose();
}

void CMainFrame::OnFileTop()
{
	// TODO: Add your command handler code here
	if (!m_bWindowsTop)
	{
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		m_bWindowsTop = true;
	}
	else
	{
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		m_bWindowsTop = false;
	}
}

void CMainFrame::OnFileAdd()
{
	// TODO: Add your command handler code here
	theEditor->AddListItem();
}

void CMainFrame::OnFileDelete()
{
	// TODO: Add your command handler code here
	theEditor->DeleteListItem();
}

void CMainFrame::OnFileDeletequest()
{
	// TODO: Add your command handler code here
	theEditor->DeleteQuest();
}

void CMainFrame::OnFileFind()
{
	// TODO: Add your command handler code here
	theEditor->OnFileFind();
}


void CMainFrame::OnFileNext()
{
	// TODO: Add your command handler code here
	theEditor->ShowNextFindQuest();
}

void CMainFrame::OnFileString()
{
	// TODO: Add your command handler code here
	theEditor->OnStringChange();
}

void CMainFrame::OnFileNpc()
{
	// TODO: Add your command handler code here
	theEditor->OnNpcChange();
}

void CMainFrame::OnFileEdit()
{
	// TODO: Add your command handler code here
	theEditor->SetListItemCanEdit();
}

void CMainFrame::OnFileStringEdit()
{
	// TODO: Add your command handler code here
	theEditor->ShowStringEditDialog();
}

void CMainFrame::OnFilePosition()
{
	// TODO: Add your command handler code here

    if (theEditor->m_pxListCtrl == &theEditor->m_listProperty)
    {
        if (theEditor->m_nItem != 5 && theEditor->m_nItem != 7)
        {
            return;
        }
    }

	PositionFind xFind;

	xFind.DoModal();
}

void CMainFrame::OnDropDelete()
{
	// TODO: Add your command handler code here
	theEditor->OnDeletedDrop();
}
