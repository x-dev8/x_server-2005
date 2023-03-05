// UIObjectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UIEditor.h"
#include "UIObjectDlg.h"
#include <assert.h>
#include "UIEditorDoc.h"
#include "PropertyDlg.h"
#include "MainFrm.h"
#include "UIEditorView.h"

CUIObjectDlg	theUIObjectDlg;
// CUIObjectDlg 对话框

IMPLEMENT_DYNAMIC(CUIObjectDlg, CDialog)
CUIObjectDlg::CUIObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUIObjectDlg::IDD, pParent)
{
	m_bInit = FALSE;
	m_pstDialog = NULL;
	m_pstCurControl = NULL;
	m_pCopyControl = NULL;
}

CUIObjectDlg::~CUIObjectDlg()
{
	SAFE_DELETE( m_pstDialog );
	ReleaseCopyControl();
	for( UINT n=0; n<m_vtControls.size(); n++ )
	{
		SAFE_DELETE( m_vtControls[n].pControl );
	}
}

void CUIObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_UI_OBJECT, m_treeObject);
}

BOOL CUIObjectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_bInit = TRUE;

	strcpy( m_stObjectKinds[ObjectKind_Dialog].szName, "[Dialog]" );
	strcpy( m_stObjectKinds[ObjectKind_Picture].szName, "[Pictures]" );
	for( int n=0; n<ObjectKind_Max; n++ )
	{
		m_stObjectKinds[n].hItem = m_treeObject.InsertItem(m_stObjectKinds[n].szName);
	}
	assert( m_pstDialog == NULL );
	m_pstDialog = new CFrameControl;
	m_stObjectKinds[ObjectKind_Dialog].pControl = m_pstDialog;

	return TRUE;  // return TRUE unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CUIObjectDlg, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_UI_OBJECT, OnNMDblclkTreeUiObject)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(TVN_KEYDOWN, IDC_TREE_UI_OBJECT, OnTvnKeydownTreeUiObject)
END_MESSAGE_MAP()

// CUIObjectDlg 消息处理程序

void CUIObjectDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此添加消息处理程序代码
	if ( m_bInit )
	{
		CRect sz;
		GetClientRect(sz);
		sz.DeflateRect(1,1);

		m_treeObject.MoveWindow(sz);
	}
}

void CUIObjectDlg::OnNMDblclkTreeUiObject(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hCurSel = m_treeObject.GetNextItem(TVI_ROOT, TVGN_CARET);
	// report it to the user
	if (hCurSel)
	{
		// 如果是对话框
		if ( hCurSel == m_stObjectKinds[ObjectKind_Dialog].hItem )
		{
			DBClickDialog( hCurSel );
			g_enState = State_Dialog;
		}
		else if ( m_treeObject.GetParentItem(hCurSel) == m_stObjectKinds[ObjectKind_Dialog].hItem )
		{
			DBClickControl( hCurSel );
			g_enState = State_Control;
		}
		else if ( m_treeObject.GetParentItem(hCurSel) == m_stObjectKinds[ObjectKind_Picture].hItem )
		{
			DBClickPic( hCurSel );
			g_enState = State_Pic;
		}
	}

	*pResult = 0;
}

bool CUIObjectDlg::AddControl( const E_ControlType enType, int nX, int nY )
{
	CBaseControl* pControl = NewControl( enType );
	pControl->OnSize();

	int nFrameLeft, nFrameTop, nFrameRight, nFrameBottom;
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	assert( pMainFrame );
	CUIEditorView *pView = (CUIEditorView*)pMainFrame->GetActiveView();
	assert( pView );
	pView->GetFramePos( &nFrameLeft, &nFrameTop, &nFrameRight, &nFrameBottom );
	RECT rc = {nFrameLeft, nFrameTop, nFrameRight, nFrameBottom};
	//RECT rc = {0,0,m_pstDialog->m_nWidth,m_pstDialog->m_nHeight};
	pControl->SetPos( nX, nY, &rc );
	S_ObjectKinds	stControl;
	stControl.pControl = pControl;
	strcpy( stControl.szName, pControl->m_strID );
	stControl.hItem = m_treeObject.InsertItem( stControl.szName, m_stObjectKinds[ObjectKind_Dialog].hItem );
	m_vtControls.push_back( stControl );

	m_treeObject.SelectItem( stControl.hItem );
	thePropertyDlg.Clear();
	pControl->AddToPropertyDlg();
	g_enState =	State_Control;
	m_pstCurControl = pControl;
	Invalidate();
	GetDoc()->UpdateAllViews(NULL);
	return true;
}

bool CUIObjectDlg::AddControl( const S_BaseData* pData )
{
	assert( pData );
	CBaseControl* pControl = NewControl(pData->m_nType );
	pControl->SetData( pData );

	S_ObjectKinds	stControl;
	stControl.pControl = pControl;
	strcpy( stControl.szName, pControl->m_strID );
	stControl.hItem = m_treeObject.InsertItem( stControl.szName, m_stObjectKinds[ObjectKind_Dialog].hItem );
	m_vtControls.push_back( stControl );

	m_treeObject.SelectItem( stControl.hItem );
	thePropertyDlg.Clear();
	pControl->AddToPropertyDlg();
	g_enState =	State_Control;
	m_pstCurControl = pControl;
	Invalidate();
	return true;
}

bool CUIObjectDlg::AddPictuer( const char* szPicName )
{
	assert( szPicName );
	if ( szPicName[0] == 0 )
	{
		return false;
	}
	for( UINT n=0; n<m_vtPictures.size(); n++ )
	{
		if ( strcmp( m_vtPictures[n].szName, szPicName ) == 0 )
		{
			return false;
		}
	}
	S_ObjectKinds stPic;
	strcpy( stPic.szName, szPicName );
	stPic.hItem = m_treeObject.InsertItem( stPic.szName, m_stObjectKinds[ObjectKind_Picture].hItem );

    m_vtPictures.push_back( stPic );

	Invalidate();
	return true;
}

void CUIObjectDlg::ClearPic()
{
	for( UINT n=0; n<m_vtPictures.size(); n++ )
	{
		m_treeObject.DeleteItem( m_vtPictures[n].hItem );
	}
	m_vtPictures.clear();
	Invalidate();
}

bool CUIObjectDlg::RemoveSelPic()
{
	HTREEITEM hCurSel = m_treeObject.GetNextItem(TVI_ROOT, TVGN_CARET);
	if (hCurSel)
	{
		if ( m_treeObject.GetParentItem(hCurSel) == m_stObjectKinds[ObjectKind_Picture].hItem )
		{
			CString strFileName = m_treeObject.GetItemText(hCurSel);
			m_treeObject.DeleteItem( hCurSel );

			Invalidate();

			for( vector<S_ObjectKinds>::iterator it = m_vtPictures.begin();
				it != m_vtPictures.end(); it++ )
			{
				if ( strFileName == it->szName )
				{
					m_vtPictures.erase(it);
					return true;
				}
			}
		}
	}
	return false;
}

bool CUIObjectDlg::RemoveSelControl()
{
	if ( m_pstCurControl && m_pstCurControl != m_pstDialog )
	{
		for( vector<S_ObjectKinds>::iterator it = m_vtControls.begin();
			it != m_vtControls.end(); it++ )
		{
			if ( m_pstCurControl == it->pControl )
			{
				m_treeObject.DeleteItem( it->hItem );
				Invalidate();

				SAFE_DELETE( m_pstCurControl );
				if ( m_pCopyControl == m_pstCurControl )
				{
					m_pCopyControl = NULL;
				}
				m_vtControls.erase(it);
				m_pstCurControl = NULL;
				GetDoc()->UpdateAllViews(NULL);
				return true;
			}
		}
		assert( false );
	}
	return false;
}

void CUIObjectDlg::ClearControl()
{
	for( vector<S_ObjectKinds>::iterator it = m_vtControls.begin();
		it != m_vtControls.end(); it++ )
	{
		m_treeObject.DeleteItem( it->hItem );
		SAFE_DELETE( it->pControl );
	}
	m_vtControls.clear();
	Invalidate();
}

void CUIObjectDlg::Clear()
{
	ClearPic();
	ClearControl();
	m_pstCurControl = NULL;
	m_pCopyControl = NULL;

	SAFE_DELETE( m_pstDialog );
	m_pstDialog = new CFrameControl;
	m_stObjectKinds[ObjectKind_Dialog].pControl = m_pstDialog;

	Invalidate();
}

void CUIObjectDlg::DBClickDialog( HTREEITEM /*hItem*/ )
{
	thePropertyDlg.Clear();
	m_pstDialog->AddToPropertyDlg();

	if ( !m_pstDialog->m_strPicName.IsEmpty() )
	{
		GetDoc()->UpdateAllViews(NULL);
	}
}

void CUIObjectDlg::DBClickControl( HTREEITEM hItem )
{
	CBaseControl* pControl = NULL;
	for( UINT n=0; n<m_vtControls.size(); n++ )
	{
		if ( m_vtControls[n].hItem == hItem )
		{
			pControl = m_vtControls[n].pControl;
			break;
		}
	}
	if ( pControl )
	{
		m_pstCurControl = pControl;
		thePropertyDlg.Clear();
		pControl->AddToPropertyDlg();
		GetDoc()->UpdateAllViews(NULL);
	}
}

void CUIObjectDlg::DBClickPic( HTREEITEM hItem )
{
	thePropertyDlg.Clear();
	CString strFileName = m_treeObject.GetItemText(hItem);
	GetDoc()->m_GraphicsData.LoadTGAFile( strFileName );
	GetDoc()->UpdateAllViews(NULL);
}

void CUIObjectDlg::OnBnClickedCancel()
{
	//	OnCancel();
}
void CUIObjectDlg::OnBnClickedOk()
{
	//	OnOk();
}

CBaseControl* CUIObjectDlg::NewControl( const int enType )
{
	CBaseControl* pControl = NULL;
	switch( enType )
	{
	case Type_Button:
		pControl = new CButtonControl;
		break;
	case Type_CheckBox:
		pControl = new CCheckBoxControl;
		break;
	case Type_Edit:
		pControl = new CEditControl;
		break;
	case Type_Text:
		pControl = new CTextControl;
		break;
	case Type_List:
		pControl = new CListControl;
		break;
	case Type_ListImg:
		pControl = new CListImgControl;
		break;
	case Type_ScrollBar:
		pControl = new CScrollBarControl;
		break;
	case Type_ScrollBarEx:
		pControl = new CScrollBarExControl;
		break;
	case Type_ComboBox:
		pControl = new CComboBoxControl;
		break;
	case Type_Picture:
		pControl = new CPictureControl;
		break;
	case Type_Progress:
		pControl = new CProgressControl;
		break;
	case Type_Tab:
		pControl = new CTabControl;
		break;
	case Type_ListEx:
		pControl = new CListExControl;
		break;
	//case Type_Tree:
	//	pControl = new CTreeControl;
	//	break;
	default:
		assert(false);
	}
	return pControl;
}

void CUIObjectDlg::UpdateDialogName()
{
	CBaseControl *pControl = m_stObjectKinds[ObjectKind_Dialog].pControl;
	assert( pControl );
	strcpy( m_stObjectKinds[ObjectKind_Dialog].szName, pControl->m_strID );
	m_treeObject.SetItemText( m_stObjectKinds[ObjectKind_Dialog].hItem, pControl->m_strID );
}

bool CUIObjectDlg::UpdateControlName()
{
	for( vector<S_ObjectKinds>::iterator it = m_vtControls.begin();
		it != m_vtControls.end(); it++ )
	{
		CBaseControl	*pControl = it->pControl;
		assert( pControl );
		if ( pControl )
		{
			if ( strcmp(it->szName, pControl->m_strID) != 0 )
			{
				strcpy( it->szName, pControl->m_strID );
				m_treeObject.SetItemText( it->hItem, pControl->m_strID );
			}
		}
	}
	return true;
}

bool CUIObjectDlg::ShowSelItem( void* pData )
{
	assert( pData );
	if ( pData == m_stObjectKinds[ObjectKind_Dialog].pControl )
	{
		m_treeObject.SelectItem( m_stObjectKinds[ObjectKind_Dialog].hItem );
		return true;
	}
	for( UINT n=0; n<m_vtControls.size(); n++ )
	{
		if ( m_vtControls[n].pControl == pData )
		{
			m_treeObject.SelectItem( m_vtControls[n].hItem );
			return true;
		}
	}
	return false;
}

void CUIObjectDlg::SetDiglogData( const S_FrameData* pFrameData )
{
	m_pstDialog->SetData( pFrameData );
}

void CUIObjectDlg::OnTvnKeydownTreeUiObject(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVKEYDOWN pTVKeyDown = reinterpret_cast<LPNMTVKEYDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if ( pTVKeyDown->wVKey == VK_DELETE )
	{
		HTREEITEM hCurSel = m_treeObject.GetNextItem(TVI_ROOT, TVGN_CARET);
		if (hCurSel)
		{
			// 如果是对话框
			if ( m_treeObject.GetParentItem(hCurSel) == m_stObjectKinds[ObjectKind_Dialog].hItem )
			{
				if ( MessageBox( "确定要移除所选定的控件?", "确认", MB_YESNO ) == IDYES )
				{
					if ( RemoveSelControl() == false )
					{
						MessageBox( "请先选定要移除的控件", "失败", MB_OK );
					}
				}
			}
			else if ( m_treeObject.GetParentItem(hCurSel) == m_stObjectKinds[ObjectKind_Picture].hItem )
			{
				if ( MessageBox( "确定要移除所选定的图片?", "确认", MB_YESNO ) == IDYES )
				{
					if ( RemoveSelPic() == false )
					{
						MessageBox( "请先选定要移除的图片", "失败", MB_OK );
					}
				}
			}
		}
	}

	*pResult = 0;
}

void CUIObjectDlg::Copy()
{
	if ( m_pstCurControl && m_pstCurControl != m_pstDialog )
	{
		ReleaseCopyControl();
		m_pCopyControl = m_pstCurControl;
	}
}

void CUIObjectDlg::Paste()
{
	if ( m_pCopyControl )
	{
		S_BaseData *pData = S_UIData::NewData( m_pCopyControl->m_nType );
		m_pCopyControl->GetData( pData );
		pData->m_rcRealSize.left += 10;
		pData->m_rcRealSize.top += 10;
		pData->m_rcRealSize.right += 10;
		pData->m_rcRealSize.bottom += 10;
		AddControl( pData );
		delete pData;
	}
}

void CUIObjectDlg::Cut()
{
	if ( m_pstCurControl && m_pstCurControl != m_pstDialog )
	{
		ReleaseCopyControl();
		m_pCopyControl = m_pstCurControl;

		for( vector<S_ObjectKinds>::iterator it = m_vtControls.begin();
			it != m_vtControls.end(); it++ )
		{
			if ( m_pstCurControl == it->pControl )
			{
				m_treeObject.DeleteItem( it->hItem );
				Invalidate();

				m_vtControls.erase(it);
				m_pstCurControl = NULL;
				return;
			}
		}
		assert(false);
	}
}

void CUIObjectDlg::ReleaseCopyControl()
{
	if ( m_pCopyControl )
	{
		bool bFindControl = false;
		for( UINT n=0; n<m_vtControls.size(); n++ )
		{
			if( m_vtControls[n].pControl == m_pCopyControl )
			{
				bFindControl = true;
				break;
			}
		}
		if ( !bFindControl )
		{
			SAFE_DELETE( m_pCopyControl );
		}
	}
}

bool CUIObjectDlg::TestDialog( char* szResultString )
{
	assert(szResultString);
	if ( m_pstDialog->m_strID.IsEmpty() )
	{
		strcpy( szResultString, "对话框ID为空" );
		return false;
	}
	for ( UINT n=0; n<m_vtControls.size(); n++ )
	{
		if ( m_vtControls[n].pControl->m_strID.IsEmpty() )
		{
			strcpy( szResultString, "控制有一ID为空" );
			return false;
		}
	}
	for ( UINT n=0; n<m_vtControls.size(); n++ )
	{
		for ( UINT m=n+1; m<m_vtControls.size(); m++ )
		{
			if ( m_vtControls[n].pControl->m_strID == m_vtControls[m].pControl->m_strID )
			{
				sprintf( szResultString, "控制有ID重复:%s", m_vtControls[n].pControl->m_strID );
				return false;
			}
		}
	}
	strcpy( szResultString, "没有问题的啦!" );
	return true;
}


