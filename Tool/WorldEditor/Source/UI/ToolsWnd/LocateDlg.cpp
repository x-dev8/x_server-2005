// LocateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WorldEditor.h"
#include "LocateDlg.h"


// CLocateDlg dialog

IMPLEMENT_DYNAMIC(CLocateDlg, CDialog)

CLocateDlg::CLocateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLocateDlg::IDD, pParent)
	, m_pointX(0)
	, m_pointY(0)
{

}

CLocateDlg::~CLocateDlg()
{
}

void CLocateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_x, m_pointX);
	DDX_Text(pDX, IDC_EDIT_y, m_pointY);
}


BEGIN_MESSAGE_MAP(CLocateDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CLocateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLocateDlg message handlers

void CLocateDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	OnOK();
}

BOOL CLocateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	::SetFocus(GetDlgItem(IDC_EDIT_x)->m_hWnd);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
