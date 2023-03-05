/*******************************************************************************
*  Copyright ZWS (C) 2007 - All Rights Reserved
*
* File: 	ServerMapDlg.cpp
* Date: 	12/05/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include "ServerMapDlg.h"

////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CServerMapDlg, CDialog)

CServerMapDlg::CServerMapDlg(CWnd* pParent)
: CDialog(CServerMapDlg::IDD, pParent)
{

}

CServerMapDlg::~CServerMapDlg()
{

}

void CServerMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CReplaceTileTextureDlg)
	DDX_Control(pDX, IDC_EDIT_CLIENTFILE, m_editClientFileName);
	DDX_Control(pDX, IDC_EDIT_SERVERFILE, m_editServerFileName);
	//}}AFX_DATA_MAP

}

BEGIN_MESSAGE_MAP(CServerMapDlg, CDialog)
END_MESSAGE_MAP()

BOOL CServerMapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editClientFileName.Initialize(this, BES_XT_CHOOSEFILE);
	m_editClientFileName.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );
	m_editServerFileName.Initialize(this, BES_XT_CHOOSEFILE);
	m_editServerFileName.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );
	

	CString defaultFileName;
	defaultFileName.Format( _T("%s\\Data\\EditWorld\\"), CWorld::GetAppDataCharDir() );
	m_editClientFileName.SetWindowText( defaultFileName );
		
	defaultFileName.Format( _T("%s\\Server\\Servermap.smf"), CWorld::GetAppDataCharDir() );
	m_editServerFileName.SetWindowText( defaultFileName );

	UpdateData( FALSE );

	return TRUE;
}

void CServerMapDlg::OnOK()
{
	UpdateData();

	CString filePath;

	m_editClientFileName.GetWindowText( filePath );
	if( filePath.GetLength() < 1 ) {
		::AfxMessageBox( _T("必须设定名称！") );
		return;
	}
	if( filePath.GetLength() > (MAX_PATH>>1) ) {
		::AfxMessageBox( _T("路径长度不对，请检察层次是否太深！") );
		return;
	}
	filePath.MakeLower();
	_tcscpy_s( m_clientFileName, filePath );
	//SwPublicFunc::TChar2MutiChar( m_clientFileName, MAX_PATH*sizeof(TCHAR), filePath, (filePath.GetLength()+1)*sizeof(TCHAR) );

	m_editServerFileName.GetWindowText( filePath );
	if( filePath.GetLength() < 1 ) {
		::AfxMessageBox( _T("必须设定名称！") );
		return;
	}
	if( filePath.GetLength() > (MAX_PATH>>1) ) {
		::AfxMessageBox( _T("路径长度不对，请检察层次是否太深！") );
		return;
	}
	filePath.MakeLower();
	SwPublicFunc::TChar2MutiChar( m_serverFileName, MAX_PATH*2*sizeof(char), filePath, (filePath.GetLength()+1)*sizeof(TCHAR) );
	
	CDialog::OnOK();
}

