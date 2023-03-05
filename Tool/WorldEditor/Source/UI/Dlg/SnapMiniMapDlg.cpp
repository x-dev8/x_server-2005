/*******************************************************************************
*  Copyright ZWS (C) 2007 - All Rights Reserved
*
* File: 	SnapMiniMapDlg.cpp
* Date: 	12/04/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include "SnapMiniMapDlg.h"

////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CSnapMinimapDlg, CDialog)

CSnapMinimapDlg::CSnapMinimapDlg(CWnd* pParent)
	: CDialog(CSnapMinimapDlg::IDD, pParent)
{
}

CSnapMinimapDlg::~CSnapMinimapDlg()
{

}

void CSnapMinimapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CReplaceTileTextureDlg)
	DDX_Control(pDX, IDC_EDIT_SNAPPATH, m_editFileName);
	//}}AFX_DATA_MAP

}

BEGIN_MESSAGE_MAP(CSnapMinimapDlg, CDialog)
END_MESSAGE_MAP()

BOOL CSnapMinimapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editFileName.Initialize(this, BES_XT_CHOOSEFILE);
	m_editFileName.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );

	char fileName[MAX_PATH*2];
	sprintf_s( fileName, "%s\\%s", SwGlobal::GetWorld()->GetWorldPath(), m_tile->GetPathName() );
	_strlwr(fileName);
	char* pFind = strstr(fileName,".mew");
	strcpy(&pFind[1],"bmp");

// 	CString defaultTexture;
// 	defaultTexture.Format( _T("%s\\%s\\%s.bmp"), CWorld::GetAppDataCharDir(), _T("Data\\World\\minimap"), m_tileName);
	m_editFileName.SetWindowText( fileName );

	UpdateData( FALSE );

	return TRUE;
}

void CSnapMinimapDlg::OnOK()
{
	UpdateData();

	CString texturePath;

	m_editFileName.GetWindowText( texturePath );
	if( texturePath.GetLength() < 1 ) {
		::AfxMessageBox( _T("必须设定名称！") );
		return;
	}
	if( texturePath.GetLength() > (MAX_PATH>>1) ) {
		::AfxMessageBox( _T("路径长度不对，请检察层次是否太深！") );
		return;
	}
	texturePath.MakeLower();

	SwPublicFunc::TChar2MutiChar( m_fileName, MAX_PATH*2*sizeof(char), texturePath, (texturePath.GetLength()+1)*sizeof(TCHAR) );

	CDialog::OnOK();
}





