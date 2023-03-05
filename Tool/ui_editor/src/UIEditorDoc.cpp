// UIEditorDoc.cpp :  CUIEditorDoc 类的实现
//

#include "stdafx.h"
#include "UIEditor.h"
#include <assert.h>

#include "MainFrm.h"
#include "UIEditorDoc.h"
#include "PicMgr.h"
#include "CreateCode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CUIEditorDoc	*pUIEditorDoc = NULL;
// CUIEditorDoc

IMPLEMENT_DYNCREATE(CUIEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CUIEditorDoc, CDocument)
END_MESSAGE_MAP()


// CUIEditorDoc 构造/销毁

CUIEditorDoc::CUIEditorDoc()
{
}

CUIEditorDoc::~CUIEditorDoc()
{
}

// CUIEditorDoc 序列化

void CUIEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO：在此添加存储代码
	}
	else
	{
		// TODO：在此添加加载代码
	}
}


// CUIEditorDoc 诊断

#ifdef _DEBUG
void CUIEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUIEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CUIEditorDoc 命令

CUIEditorDoc* GetDoc()
{
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	assert( pMainFrame );
	CUIEditorDoc *pDoc = (CUIEditorDoc*)pMainFrame->GetActiveDocument();
	assert( pDoc );
	return pDoc;
}


BOOL CUIEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	thePropertyDlg.Clear();
	theUIObjectDlg.Clear();
	thePicMgr.Clear();

	return TRUE;
}

BOOL CUIEditorDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	if ( MessageBox( AfxGetMainWnd()->m_hWnd, "确定保存?", "确定", MB_YESNO ) != IDYES )
	{
		return FALSE;
	}

	strcpy( g_stPath, lpszPathName );
	for( int n=(int)strlen(g_stPath); n>0; n-- )
	{
		if ( g_stPath[n] == '\\' )
		{
			strcpy( g_stFileName, &g_stPath[n+1] );
			for( int m=(int)strlen(g_stFileName); m>=0; m-- )
			{
				if ( g_stFileName[m] == '.' )
				{
					g_stFileName[m] = 0;
				}
			}
			g_stPath[n] = 0;
			break;
		}
	}

	theUIObjectDlg.m_pstDialog->GetData( &stUIData.m_stHead.m_stFrameData );
	stUIData.m_stHead.m_nControlsCount = (int)theUIObjectDlg.m_vtControls.size();
	if ( stUIData.m_stHead.m_nControlsCount >= CONTROLS_COUNT_MAX2 )
	{
		MessageBox( AfxGetMainWnd()->m_hWnd, "控件数过多!超过 200 个", "失败", MB_OK );
		return FALSE;
	}
	for( UINT n=0; n<theUIObjectDlg.m_vtControls.size(); n++ )
	{
		CBaseControl *pControl = theUIObjectDlg.m_vtControls[n].pControl;
		assert( pControl );
		stUIData.m_stHead.m_nControlsType[n] = pControl->m_nType;

		S_BaseData* baseData = NULL;

		switch( pControl->m_nType )
		{
		case Type_Button:
			baseData = stUIData.NewData( Type_Button );
			break;
		case Type_CheckBox:
			baseData = stUIData.NewData( Type_CheckBox );
			break;
		case Type_Edit:
			baseData = stUIData.NewData( Type_Edit );
			break;
		case Type_Text:
			baseData = stUIData.NewData( Type_Text );
			break;
		case Type_List:
			baseData = stUIData.NewData( Type_List );
			break;
		case Type_ListImg:
			baseData = stUIData.NewData( Type_ListImg );
			break;
		case Type_ScrollBar:
			baseData = stUIData.NewData( Type_ScrollBar );
			break;
		case Type_ScrollBarEx:
			baseData = stUIData.NewData( Type_ScrollBarEx );
			break;
		case Type_ComboBox:
			baseData = stUIData.NewData( Type_ComboBox );
			break;
		case Type_Picture:
			baseData = stUIData.NewData( Type_Picture );
			break;
		case Type_Progress:
			baseData = stUIData.NewData( Type_Progress );
			break;
		case Type_Tab:
			baseData = stUIData.NewData( Type_Tab );
			break;
		case Type_ListEx:
			baseData = stUIData.NewData( Type_ListEx );
			break;
		//case Type_Tree:
		//	baseData = new S_TreeData;
		//	break;
		default:
			assert( false );
			return FALSE;
			break;
		}
		stUIData.m_pstControlData.push_back( baseData );
		pControl->GetData( stUIData.m_pstControlData[n] );
		pControl->GetData_Event( n );
	}
	DWORD dwCreatedDate = stUIData.SaveFile(lpszPathName);
	CreateCode( &stUIData, lpszPathName, dwCreatedDate );
	stUIData.Release();
	return TRUE;
}

BOOL CUIEditorDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	OnNewDocument();

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	strcpy( g_stPath, lpszPathName );
	for( int n=(int)strlen(g_stPath); n>0; n-- )
	{
		if ( g_stPath[n] == '\\' )
		{
			strcpy( g_stFileName, &g_stPath[n+1] );
			for( int m=(int)strlen(g_stFileName); m>=0; m-- )
			{
				if ( g_stFileName[m] == '.' )
				{
					g_stFileName[m] = 0;
				}
			}
			g_stPath[n] = 0;
			break;
		}
	}

	if ( stUIData.LoadFile(lpszPathName) == false )
	{
		return FALSE;
	}
	theUIObjectDlg.SetDiglogData( &stUIData.m_stHead.m_stFrameData );
	for( int n=0; n<stUIData.m_pstControlData.size(); n++ )
	{
		theUIObjectDlg.AddControl( stUIData.m_pstControlData[n] );
	}

	theUIObjectDlg.m_pstCurControl = theUIObjectDlg.m_pstDialog;
	thePropertyDlg.Clear();
	theUIObjectDlg.m_pstCurControl->AddToPropertyDlg();
	theUIObjectDlg.m_pstCurControl->AddToUIObjectDlg();
	for( UINT n=0; n<theUIObjectDlg.m_vtControls.size(); n++ )
	{
		CBaseControl* pControl = theUIObjectDlg.m_vtControls[n].pControl;
		assert( pControl );
		pControl->AddToUIObjectDlg();
	}
	stUIData.Release();
	return TRUE;
}
