// F:\Hero\Program\Tool\WorldEditor\Source\UI\Dlg\LightMapSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WorldEditor.h"
#include "Resource/resource.h"
#include "LightMapSettingDlg.h"


// LightMapSettingDlg dialog

IMPLEMENT_DYNAMIC(LightMapSettingDlg, CDialog)

LightMapSettingDlg::LightMapSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LightMapSettingDlg::IDD, pParent), m_sShadowColor(0)
{

}

LightMapSettingDlg::~LightMapSettingDlg()
{
}

void LightMapSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LIGHTMAP_VALUE, m_shadowValue);	
}


BEGIN_MESSAGE_MAP(LightMapSettingDlg, CDialog)
	ON_BN_CLICKED(IDOK, &LightMapSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()

short LightMapSettingDlg::GetShadowColor()
{
	return m_sShadowColor;
}


// LightMapSettingDlg message handlers

void LightMapSettingDlg::OnBnClickedOk()
{
	CString color;
	m_shadowValue.GetWindowText(color);
	m_sShadowColor = (short)_tstoi(color);

	OnOK();
}
