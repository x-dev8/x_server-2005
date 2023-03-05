// DoodadNewLevelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resource/Resource.h"
#include "DoodadNewLevelDlg.h"


// CDoodadNewLevelDlg dialog

IMPLEMENT_DYNAMIC(CDoodadNewLevelDlg, CDialog)

CDoodadNewLevelDlg::CDoodadNewLevelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDoodadNewLevelDlg::IDD, pParent)
	,m_nunitSize(WORLD_TILE_CHUNK_ATOM_NUM/2)
{
}

CDoodadNewLevelDlg::~CDoodadNewLevelDlg()
{
}

void CDoodadNewLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UnitSize, m_UnitSize);
}


BEGIN_MESSAGE_MAP(CDoodadNewLevelDlg, CDialog)
END_MESSAGE_MAP()

int CDoodadNewLevelDlg::GetUnitSize() const
{
	return m_nunitSize;
}

BOOL CDoodadNewLevelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString cTmp;
	for (int i = 0; i < WORLD_TILE_CHUNK_ATOM_NUM*4; ++i)
	{
		cTmp.Format("%d",i + 1);
		m_UnitSize.InsertString(i,cTmp.GetString());
	}
	m_UnitSize.SetCurSel(WORLD_TILE_CHUNK_ATOM_NUM/2 - 1);
	return true;
}

void CDoodadNewLevelDlg::OnOK()
{
	UpdateData();
	CString unitSize;
	m_UnitSize.GetWindowText(unitSize);
	m_nunitSize = _tstoi(unitSize);

	if (m_nunitSize < 1 || m_nunitSize > WORLD_TILE_CHUNK_ATOM_NUM*4)
	{
		::AfxMessageBox( _T("请输入1-256之间的整数！") );
		return;
	}
	CDialog::OnOK();

}
// CDoodadNewLevelDlg message handlers
