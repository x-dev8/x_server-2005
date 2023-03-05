/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolEnvironment.cpp
* Date: 	06/12/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "ToolWorldFog.h"
#include "Edit/ToolManager.h"
const float g_MaxFogDistance = 1000.f;

////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CToolWorldFogDlg, CDialog)

CToolWorldFogDlg::CToolWorldFogDlg(CToolWorldFogDlg* pParent)
: CDialog(CToolWorldFogDlg::IDD, pParent)
{
	
}

CToolWorldFogDlg::~CToolWorldFogDlg()
{

}

void CToolWorldFogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolWorldFogDlg)	
	
	DDX_Control(pDX, IDC_EDT_LIGHT_NAME, m_editName);
	
	DDX_Control(pDX, IDC_LIST_FOG, mFogLB);
	DDX_Control(pDX, IDC_BTN_LIGHT_FOG, m_cpFogLight);
	
	DDX_XTColorPicker(pDX, IDC_BTN_LIGHT_FOG, m_colorFogLight);
	
	DDX_Control(pDX, IDC_EDT_LIGHT_NEAR, m_editLightNear);
	DDX_Control(pDX, IDC_EDT_LIGHT_FAR, m_editLightFar);
	
	DDX_Control(pDX, IDC_EDIT_BLOOMSCALE, m_editBloomScale);
	DDX_Control(pDX, IDC_EDIT_LUMINANCE, m_editLuminance);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CToolWorldFogDlg, CDialog)
	//{{AFX_MSG_MAP(CToolWorldFogDlg)
	ON_LBN_SELCHANGE(IDC_LIST_FOG, OnFogChange)

	ON_BN_CLICKED(IDC_BTN_FOG_SET, OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_FOG_ADD, OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_FOG_DEL, OnBnClickedBtnDel)

	ON_CPN_XT_SELENDOK(IDC_BTN_LIGHT_FOG, OnSelEndOkColorLight)

	ON_EN_KILLFOCUS(IDC_EDT_FOG_NAME, OnKillfocusName)
	ON_EN_KILLFOCUS(IDC_EDT_LIGHT_NEAR, OnKillfocusLightNear)
	ON_EN_KILLFOCUS(IDC_EDT_LIGHT_FAR, OnKillfocusLightFar)
	ON_EN_KILLFOCUS(IDC_EDIT_BLOOMSCALE, OnKillfocusBloomScale)
	ON_EN_KILLFOCUS(IDC_EDIT_LUMINANCE, OnKillfocusLuminance)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CToolWorldFogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cpFogLight.SetDefaultColor( RGB(0xaa,0xaa,0xaa) );
	m_cpFogLight.ShowText(true);

	m_editLightNear.SetWindowText( _T("50.0f") );
	m_editLightFar.SetWindowText( _T("200.0f") );

	m_editBloomScale.SetWindowText( "0.0f" );
	m_editLuminance.SetWindowText( "0.0f" );

	Reset();

	UpdateData( FALSE );

	return TRUE;
}

void CToolWorldFogDlg::SetActive( bool isModify )
{
	UpdateList();
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_CAMERA );

	m_curSel	= -1;
	m_editName.SetWindowText( _T("") );
}

void CToolWorldFogDlg::SetFog( CNdlFogRes* fogRes )
{
	m_colorFogLight		= fogRes->m_lightColor;
	
	CString strValue;
	strValue			= fogRes->GetName();
	m_editName.SetWindowText( strValue );

	strValue.Format( _T("%.3f"), fogRes->m_lightNear );
	m_editLightNear.SetWindowText( strValue );
	strValue.Format( _T("%.3f"), fogRes->m_lightFar );
	m_editLightFar.SetWindowText( strValue );
	
	NiColor color;
	ConvertRGB2NiColor( fogRes->m_lightColor, color );
	theApp.SetFogColor( color );
	theApp.SetFogDepth( fogRes->m_lightNear, fogRes->m_lightFar );

	UpdateData( FALSE );
}

bool CToolWorldFogDlg::GetFog( CNdlFogRes* fogRes )
{
	UpdateData();

	CString strValue;
	m_editName.GetWindowText( strValue );
	if( strValue.GetLength() >= (RES_NAME_LEN>>1) )
		return false;
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return false;
	}
	char strName[RES_NAME_LEN];
	if( strValue.GetLength() > 0 ) 
	{
		SwPublicFunc::TChar2MutiChar( strName, RES_NAME_LEN*sizeof(char), strValue, (strValue.GetLength()+1)*sizeof(TCHAR) );
		fogRes->SetName( strName );
	}
	else 
	{
		sprintf_s( strName, "没有名字_%d", resMgr->GetFogList().size() );
		fogRes->SetName( strName );		
	}

	for( sInt32 i=0; i<resMgr->GetFogList().size(); i++ ) {
		CNdlFogRes* p = (CNdlFogRes*)(resMgr->GetFogList()[i]);
		if( 0 == strcmp( p->GetName(), strName ) ) {
			AfxMessageBox( _T("已经有相同名字!") );
			return false;
		}
	}

	fogRes->m_lightColor	= m_colorFogLight;

	m_editLightNear.GetWindowText( strValue );
	fogRes->m_lightNear		= _tstof( strValue );
	fogRes->m_lightNear		= ZnClamp<flt32>( fogRes->m_lightNear, 0.f, g_MaxFogDistance);

	m_editLightFar.GetWindowText( strValue );
	fogRes->m_lightFar		= _tstof( strValue );
	fogRes->m_lightFar		= ZnClamp<flt32>( fogRes->m_lightFar, 0.0f, g_MaxFogDistance );
	
	return true;
}

void CToolWorldFogDlg::UpdateList()
{
	mFogLB.ResetContent();

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}

	CString strName;
	for( sInt32 i=0; i< resMgr->GetFogList().size(); i++ ) {
		CWorldRes* p = resMgr->GetFogList()[i];
		mFogLB.AddString( p->GetName() );
	}

	CString text;
	float scale;
	if(theApp.GetWorld()->GetWorldBuffer()->GetActiveTile())
	{
		scale = theApp.GetWorld()->GetWorldBuffer()->GetActiveTile()->GetBloomScale();

		text.Format("%f",scale);
		m_editBloomScale.SetWindowText(text);
	}

	float lum;
	if(theApp.GetWorld()->GetWorldBuffer()->GetActiveTile())
	{
		lum = theApp.GetWorld()->GetWorldBuffer()->GetActiveTile()->GetLuminance();

		text.Format("%f",lum);
		m_editLuminance.SetWindowText(text);
	}
}

void CToolWorldFogDlg::Reset()
{
	m_editName.SetWindowText( _T("") );

	m_colorFogLight		= RGB(0xaa,0xaa,0xaa);
	m_cpFogLight.SetColor(m_colorFogLight);
}

void CToolWorldFogDlg::OnFogChange()
{
	m_curSel = mFogLB.GetCurSel();
	if( -1 != m_curSel ) {
		CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
		if (NULL == resMgr)
		{
			return;
		}

		CNdlFogRes* fogRes = resMgr->GetFogRes( m_curSel );
		if( NULL != fogRes ) {  
			SetFog( fogRes );
			
		}
	}
}


void CToolWorldFogDlg::OnKillfocusLightNear()
{
	UpdateData();

	flt32 fltNearValue;
	CString strNearValue;
	m_editLightNear.GetWindowText( strNearValue );
	fltNearValue	= _tstof( strNearValue );
	fltNearValue	= ZnClamp<flt32>( fltNearValue, 0.f, g_MaxFogDistance );
	flt32 fltFarValue;
	CString strFarValue;
	m_editLightFar.GetWindowText( strFarValue );
	fltFarValue	= _tstof( strFarValue );

// 	if (fltNearValue > fltFarValue)
// 	{
// 		fltNearValue = fltFarValue;
// 	}

	strNearValue.Format( _T("%.3f"), fltNearValue );
	m_editLightNear.SetWindowText( strNearValue );
	

	UpdateData( FALSE );
}

void CToolWorldFogDlg::OnKillfocusLightFar()
{
	UpdateData();

	flt32 fltNearValue;
	CString strNearValue;
	m_editLightNear.GetWindowText( strNearValue );
	fltNearValue	= _tstof( strNearValue );
	flt32 fltFarValue;
	CString strFarValue;
	m_editLightFar.GetWindowText( strFarValue );
	fltFarValue	= _tstof( strFarValue );
	fltFarValue	= ZnClamp<flt32>( fltFarValue, 0.0f, g_MaxFogDistance );

	if (fltFarValue < fltNearValue)
	{
		fltFarValue = fltNearValue;
	}
	strFarValue.Format( _T("%.3f"), fltFarValue );
	m_editLightFar.SetWindowText( strFarValue );

	UpdateData( FALSE );
}


void CToolWorldFogDlg::OnSelEndOkColorLight()
{
	NiColor color;
	ConvertRGB2NiColor( m_colorFogLight, color );
	theApp.SetFogColor( color );
}

void CToolWorldFogDlg::OnBnClickedBtnModify()
{
	if( -1 == m_curSel )
		return;
	
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}
	if( m_curSel >= resMgr->GetFogList().size() )
		return;

	CNdlFogRes* resFog = (CNdlFogRes*)(resMgr->GetFogList()[m_curSel]);

	// 更新雾的名字
	CString strValue;
	m_editName.GetWindowText(strValue);
	mFogLB.LockWindowUpdate();
	mFogLB.DeleteString(m_curSel);
	mFogLB.InsertString(m_curSel, strValue);
	mFogLB.UnlockWindowUpdate();
	mFogLB.SetCurSel(m_curSel);
	resFog->SetName(strValue);

	resFog->m_lightColor	= m_cpFogLight.GetColor();//m_colorFogLight;

	m_editLightNear.GetWindowText( strValue );
	resFog->m_lightNear		= _tstof( strValue );
	resFog->m_lightNear		= ZnClamp<flt32>( resFog->m_lightNear, 0.f, g_MaxFogDistance );

	m_editLightFar.GetWindowText( strValue );
	resFog->m_lightFar		= _tstof( strValue );
	resFog->m_lightFar		= ZnClamp<flt32>( resFog->m_lightFar, 0.0f, g_MaxFogDistance );

	NiColor color;
	ConvertRGB2NiColor( resFog->m_lightColor, color );
	theApp.SetFogColor( color );
	theApp.SetFogDepth( resFog->m_lightNear, resFog->m_lightFar );
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	UpdateList();
}

void CToolWorldFogDlg::OnBnClickedBtnAdd()
{
	UpdateData();

	CString strValue;
	m_editName.GetWindowText( strValue );
	if( strValue.GetLength() >= (RES_NAME_LEN>>1) )
		return;

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}

	char strName[RES_NAME_LEN];
	if( strValue.GetLength() > 0 ) {
		SwPublicFunc::TChar2MutiChar( strName, RES_NAME_LEN*sizeof(char), strValue, (strValue.GetLength()+1)*sizeof(TCHAR) );
	}
	else {
		sprintf_s( strName, "没有名字_%d", resMgr->GetFogList().size() );
	}

	for( sInt32 i=0; i<resMgr->GetFogList().size(); i++ ) {
		CNdlFogRes* p = (CNdlFogRes*)(resMgr->GetFogList()[i]);
		if( 0 == strcmp( p->GetName(), strName ) ) {
			AfxMessageBox( _T("已经有相同名字!") );
			return;
		}
	}

	CNdlFogRes* fogRes = MeNew CNdlFogRes();

	if( !GetFog( fogRes ) ) {
		SAFE_DELETE( fogRes );
		return;
	}

	fogRes->SetId(resMgr->GetFogList().size());

	resMgr->GetFogList().push_back( fogRes );
	m_curSel = resMgr->GetFogList().size() - 1;

	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
	UpdateList();

	UpdateData( FALSE );

}

void CToolWorldFogDlg::OnBnClickedBtnDel()
{
	if( -1 == m_curSel )
		return;

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}
	if( m_curSel >= resMgr->GetFogList().size() )
		return;

	CString strPmt;
	strPmt.Format( _T("是否删除？") );
	int sel = ::AfxMessageBox( strPmt, MB_YESNO );
	if( sel == IDYES ) 
	{
		resMgr->DeleteFogRes(m_curSel);

		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);
		UpdateList();
		UpdateData( FALSE );
		Reset();
		m_curSel	= -1;
	}

}

void CToolWorldFogDlg::OnKillfocusName()
{
}
void CToolWorldFogDlg::OnKillfocusBloomScale()
{
	UpdateData();

	float scale;
	CString strScale;
	m_editBloomScale.GetWindowText( strScale );
	scale = _tstof( strScale );

	if(theApp.GetWorld()->GetWorldBuffer()->GetActiveTile())
		theApp.GetWorld()->GetWorldBuffer()->GetActiveTile()->SetBloomScale(scale);
}

void CToolWorldFogDlg::OnKillfocusLuminance()
{
	UpdateData();

	float lum;
	CString strLum;
	m_editLuminance.GetWindowText( strLum );
	lum = _tstof( strLum );

	if(theApp.GetWorld()->GetWorldBuffer()->GetActiveTile())
		theApp.GetWorld()->GetWorldBuffer()->GetActiveTile()->SetLuminance(lum);
}