/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ReachableMapDlg.cpp
* Create: 	11/01/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "Resource/Resource.h"
#include "ReachableMapDlg.h"

////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CReachableMapDlg, CDialog)

CReachableMapDlg::CReachableMapDlg(CWnd* pParent)
	: CDialog(CReachableMapDlg::IDD, pParent)
{
	m_mapScale = 32;
}

CReachableMapDlg::~CReachableMapDlg()
{

}

void CReachableMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CReplaceTileTextureDlg)
	DDX_Control(pDX, IDC_EDIT_MAPPATH, m_editFileName);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_EDIT_MAPSCALE, m_editMapScale);
}

BEGIN_MESSAGE_MAP(CReachableMapDlg, CDialog)
END_MESSAGE_MAP()

BOOL CReachableMapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editFileName.Initialize(this, BES_XT_CHOOSEFILE);
	m_editFileName.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );

	CString defaultTexture;
	defaultTexture.Format( _T("%s\\Data\\World\\%s.map"), CWorld::GetAppDataCharDir(), m_tileName);
	m_editFileName.SetWindowText( defaultTexture );

	CString mapScale;
	mapScale.Format(_T("%d"),m_mapScale);
	m_editMapScale.SetWindowText(mapScale);
	UpdateData( FALSE );

	return TRUE;
}

void CReachableMapDlg::OnOK()
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

	CString mapScale;
	m_editMapScale.GetWindowText(mapScale);
	m_mapScale = _tstoi(mapScale);
	CDialog::OnOK();
}





