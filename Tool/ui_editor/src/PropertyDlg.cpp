// PropertyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UIEditor.h"
#include "PropertyDlg.h"


CPropertyDlg	thePropertyDlg;
// CPropertyDlg 对话框

IMPLEMENT_DYNAMIC(CPropertyDlg, CDialog)
CPropertyDlg::CPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertyDlg::IDD, pParent)
{
	m_bInit = FALSE;
	m_pstControl = NULL;
}

CPropertyDlg::~CPropertyDlg()
{
}

void CPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROPERTY, m_ProList);
}

#include "PicEditorDlg.h"

BOOL CPropertyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bInit = TRUE;
	return TRUE;  // return TRUE  unless you set the focus to a control
}


BEGIN_MESSAGE_MAP(CPropertyDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CPropertyDlg 消息处理程序



void CPropertyDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此添加消息处理程序代码
	if ( m_bInit )
	{
		CRect sz;
		GetClientRect(sz);
		sz.DeflateRect(1,1);
		m_ProList.MoveWindow(sz);
	}
}

void CPropertyDlg::OnBnClickedCancel()
{
//	OnCancel();
}
void CPropertyDlg::OnBnClickedOk()
{
//	OnOk();
}

void CPropertyDlg::Clear()
{
	if ( m_ProList.m_hWnd )
	{
		m_ProList.ResetContent();
	}
}

void CPropertyDlg::AddItem( S_PropertyItem* pItem )
{
	m_ProList.AddItem( pItem );
}


