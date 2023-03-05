// F:\Hero\Program\Tool\WorldEditor\Source\UI\ToolsScene\ToolWorldSkyboxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WorldEditor.h"
#include "ToolWorldSkyboxDlg.h"


// CToolWorldSkyboxDlg dialog

IMPLEMENT_DYNAMIC(CToolWorldSkyboxDlg, CDialog)

CToolWorldSkyboxDlg::CToolWorldSkyboxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolWorldSkyboxDlg::IDD, pParent)
{

}

CToolWorldSkyboxDlg::~CToolWorldSkyboxDlg()
{
}

BOOL CToolWorldSkyboxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CHAR szPath[MAX_PATH] = {0};
	sprintf( szPath, "%s%s", CWorld::GetAppDataCharDir(), "\\data\\SceneObject\\Common\\skybox\\common.mex");

	m_editSkyboxPath.Initialize(this, BES_XT_CHOOSEFILE);
	m_editSkyboxPath.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );
	m_editSkyboxPath.SetDlgFilter(_T("*.mex|*.mex"));
	m_editSkyboxPath.SetDlgFileName(szPath);
	
	m_editSkyboxTexturePath.Initialize(this, BES_XT_CHOOSEFILE);
	m_editSkyboxTexturePath.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );
	m_editSkyboxTexturePath.SetDlgFilter(_T("*.dds|*.dds"));
	UpdateData( FALSE );

	return TRUE;
}

void CToolWorldSkyboxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SKYBOXPATH, m_editSkyboxPath);
	DDX_Control(pDX, IDC_EDIT_SKYBOXTEXTUREPATH, m_editSkyboxTexturePath);
}


BEGIN_MESSAGE_MAP(CToolWorldSkyboxDlg, CDialog)
	
END_MESSAGE_MAP()


// CToolWorldSkyboxDlg message handlers

void CToolWorldSkyboxDlg::OnOK()
{
	//m_editSkyboxPath.SetWindowText( dlgFile.GetOFN().lpstrFile );
	UpdateData();
	m_editSkyboxPath.GetWindowText( m_strFilename );
	m_editSkyboxTexturePath.GetWindowText( m_strTextureFilename );
	CDialog::OnOK();
}
