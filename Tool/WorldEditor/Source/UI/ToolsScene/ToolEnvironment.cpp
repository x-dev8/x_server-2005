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
#include "Edit/ToolEnv.h"
#include "Edit/ToolManager.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "ToolEnvironment.h"

////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CToolEnvDlg, CDialog)

CToolEnvDlg::CToolEnvDlg(CToolEnvDlg* pParent)
: CDialog(CToolEnvDlg::IDD, pParent)
{
	m_curSel		= RES_INVALID_ID;
}

CToolEnvDlg::~CToolEnvDlg()
{

}

void CToolEnvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolEnvironmentDlg)	
	DDX_Control(pDX, IDC_LIST_ENV, m_listEnv);
	DDX_Control(pDX, IDC_EDIT_ENV_NAME, m_envName);
	DDX_Control(pDX, IDC_EDT_BRUSH_RADIUS_ENV, m_brushRadius);
	DDX_Control(pDX, IDC_EDT_SELECTED_ENV, m_selectedEnv);
	DDX_Control(pDX, IDC_CMB_LIGHT, m_listLight);
	DDX_Control(pDX, IDC_CMB_FOG, m_listFog);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CToolEnvDlg, CDialog)
	//{{AFX_MSG_MAP(CToolEnvDlg)
	ON_LBN_SELCHANGE(IDC_LIST_ENV, OnClkListCtrl)
	ON_EN_KILLFOCUS(IDC_EDIT_ENV_NAME, OnKillfocusName)
	ON_EN_KILLFOCUS(IDC_EDT_BRUSH_RADIUS_ENV, OnKillfocusRadius)
	ON_LBN_SELCHANGE(IDC_CMB_LIGHT, OnLightChange)
	ON_LBN_SELCHANGE(IDC_CMB_FOG, OnFogChange)
	ON_BN_CLICKED(IDC_RADIO_SET_ENV, OnChkSetZone)
	ON_BN_CLICKED(IDC_RADIO_ENV_PICK, OnChkPickZone)
	ON_BN_CLICKED(IDC_BTN_ENV_SET, OnBtnSetZone )
	ON_BN_CLICKED(IDC_BTN_ENV_ADD, OnBtnAddZone )
	ON_BN_CLICKED(IDC_BTN_ENV_DEL, OnBtnDelZone )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CToolEnvDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CheckDlgButton( IDC_RADIO_ENV_PICK, 1 );
	m_brushRadius.SetWindowText( _T("0") );
	m_selectedEnv.SetWindowText( _T("无") );
	UpdateData( FALSE );
	
	return TRUE;
}

void CToolEnvDlg::SetActive( bool isModify )
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_ENV );
	CToolEnv* toolZone = (CToolEnv*)( toolManager->GetActiveTool() );
	Assert( NULL != toolZone );
	toolZone->Bind( this );

	UpdateZoneList();
	UpdateLightList();
	UpdateFogList();

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}
	if (resMgr->GetEnvResList().size() > 0 )
	{
		m_curSel = 0;
		toolZone->m_brushZoneId = m_curSel;
		GetToolZone()->UpdateZonePreview(m_curSel);
	}
	else
	{
		m_curSel = RES_INVALID_ID;
	}
	UpdateSelect();
}

void CToolEnvDlg::OnClkListCtrl()
{
	m_curSel = m_listEnv.GetCurSel();
	if( -1 != m_curSel ) {
		GetToolZone()->m_brushZoneId = m_curSel;

		GetToolZone()->UpdateZonePreview(m_curSel);
	}
}

void CToolEnvDlg::OnKillfocusName()
{
	//UpdateData();

	//CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	//toolManager->SetActiveTool( TOOL_ENV );
	//CToolEnv* toolZone = (CToolEnv*)( toolManager->GetActiveTool() );
	//Assert( NULL != toolZone );

	//CString strValue;
	//m_zoneName.GetWindowText( strValue );
	//if( (strValue.GetLength()<=(RES_NAME_LEN>>1)) && (strValue.GetLength()>0) )	{
	//	SwPublicFunc::TChar2MutiChar( toolZone->m_zoneName, RES_NAME_LEN*sizeof(char), strValue, (strValue.GetLength()+1)*sizeof(TCHAR) );
	//}
	//else {
	//	strcpy_s( toolZone->m_zoneName, "" );
	//}
	//toolZone->m_brushZoneId	= RES_INVALID_ID;
}

void CToolEnvDlg::OnKillfocusRadius()
{
	UpdateData();

	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_ENV );
	CToolEnv* toolZone = (CToolEnv*)( toolManager->GetActiveTool() );
	Assert( NULL != toolZone );

	CString strValue;
	m_brushRadius.GetWindowText( strValue );
	toolZone->m_brushRadius		= _tstoi( strValue );
	if( toolZone->m_brushRadius < 0 ) {
		toolZone->m_brushRadius	= 0;
		m_brushRadius.SetWindowText( _T("0") );
		UpdateData( FALSE );
	}
	else if( toolZone->m_brushRadius > 8 ) {
		toolZone->m_brushRadius = 8;
		m_brushRadius.SetWindowText( _T("8") );
		UpdateData( FALSE );
	}
}

void CToolEnvDlg::OnLightChange()
{
	SaveEnv();
}

void CToolEnvDlg::OnFogChange()
{
	SaveEnv();
}

void CToolEnvDlg::OnChkPickZone()
{

	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolEnv* zone			= (CToolEnv*)toolMgr->GetTool( TOOL_ENV );
	CheckDlgButton( IDC_RADIO_SET_ENV, 0 );

	zone->SetPaintMode( false );
}

void CToolEnvDlg::OnChkSetZone()
{

	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolEnv* zone			= (CToolEnv*)toolMgr->GetTool( TOOL_ENV );
	CheckDlgButton( IDC_RADIO_ENV_PICK, 0 );

	zone->SetPaintMode( true );
}

void CToolEnvDlg::OnBtnSetZone()
{
	if( RES_INVALID_ID == m_curSel )
		return;

	UpdateData();

	char zoneName[RES_NAME_LEN];
	CString strValue;
	m_envName.GetWindowText( strValue );
	if( (strValue.GetLength()<=(RES_NAME_LEN>>1)) && (strValue.GetLength()>0) )	{
		SwPublicFunc::TChar2MutiChar( zoneName, RES_NAME_LEN*sizeof(char), strValue, (strValue.GetLength()+1)*sizeof(TCHAR) );
	}
	else {
		strcpy_s( zoneName, "没有名字" );
	}

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}

	Assert( m_curSel>=0 && m_curSel<resMgr->GetEnvResList().size() );

	CNdlEnvRes* zoneRes	= (CNdlEnvRes*)resMgr->GetEnvResList()[m_curSel];
	zoneRes->SetName(zoneName);

	// 刷新Zone List
	UpdateZoneList();

	// 设置Tile的Dirty标记
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify(CURRENTTILE);

	GetToolZone()->UpdateZonePreview(m_curSel);
}

void CToolEnvDlg::OnBtnAddZone()
{
	sInt32 lightId	= m_listLight.GetCurSel();
	sInt32 fogId	= m_listFog.GetCurSel();
	if (-1 == lightId || -1 == fogId)
	{
		return;
	}
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	UpdateData();

	char zoneName[RES_NAME_LEN];
	CString strValue;
	m_envName.GetWindowText( strValue );
	if( (strValue.GetLength()<=(RES_NAME_LEN>>1)) && (strValue.GetLength()>0) )	{
		SwPublicFunc::TChar2MutiChar( zoneName, RES_NAME_LEN*sizeof(char), strValue, (strValue.GetLength()+1)*sizeof(TCHAR) );
	}
	else {
		strcpy_s( zoneName, "没有名字" );
	}

	CreateZone( zoneName, lightId, fogId );

	UpdateData( FALSE );
}

void CToolEnvDlg::OnBtnDelZone()
{
	if( RES_INVALID_ID == m_curSel )
		return;
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	int sel = ::AfxMessageBox( _T("是否确认删除?"), MB_YESNO );
	if( IDYES != sel ) 
		return;

	UpdateData();

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}

	Assert( m_curSel>=0 && m_curSel<resMgr->GetEnvResList().size() );

	resMgr->DeleteEnvRes(m_curSel);
	
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	CToolEnv* toolZone = (CToolEnv*)( toolManager->GetActiveTool() );
	Assert( NULL != toolZone );

	m_curSel				= RES_INVALID_ID;
	toolZone->m_brushZoneId = RES_INVALID_ID;

	UpdateZoneList();

	// 设置Tile的Dirty标记
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify(CURRENTTILE);
	UpdateData( FALSE );
}

bool CToolEnvDlg::CreateZone( const char* zoneName, sInt32 lightId, sInt32 fogId )
{
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return false;
	}
	Assert( lightId>=0 && lightId<resMgr->GetLightList().size() );
	Assert( fogId>=0 && fogId<resMgr->GetFogList().size() );

	resMgr->CreateEnv( zoneName, lightId, fogId );
	
	UpdateZoneList();

	// 设置Tile的Dirty标记
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify(CURRENTTILE);
	
	return true;
}

void CToolEnvDlg::UpdateZoneInfo( sInt32 zoneId )
{
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;
	
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}
	Assert( zoneId>=0 && zoneId<resMgr->GetEnvResList().size() );
	

	CNdlEnvRes* zoneRes	= (CNdlEnvRes*)resMgr->GetEnvResList()[zoneId];
	m_listLight.SetCurSel( zoneRes->GetLightId() );
	m_listFog.SetCurSel( zoneRes->GetFogId() );
	
	CString strName;
	strName					= zoneRes->GetName();
	m_envName.SetWindowText( strName );
	SetSelectedZoneName(strName);

	UpdateData( FALSE );
}

void CToolEnvDlg::UpdateWorldZone()
{
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	if( RES_INVALID_ID == m_curSel )
		return;

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}
	Assert( m_curSel>=0 && m_curSel<resMgr->GetEnvResList().size() );

	CNdlEnvRes* zoneRes	= (CNdlEnvRes*)resMgr->GetEnvResList()[m_curSel];
	Assert( NULL != zoneRes );
	CNdlLightRes* lightRes	= (CNdlLightRes*)resMgr->GetLightList()[zoneRes->GetLightId()];
	Assert( NULL != lightRes );
	CNdlFogRes* fogRes		= (CNdlFogRes*)resMgr->GetFogList()[zoneRes->GetFogId()];
	Assert( NULL != fogRes );
	
	theApp.SetLightDir( lightRes->m_lightDir );

	NiColor color;
	ConvertRGB2NiColor( lightRes->m_lightAmbient, color );
	theApp.SetLightAmbientColor( color );
	ConvertRGB2NiColor( lightRes->m_lightDiffuse, color );
	theApp.SetLightDiffuseColor( color );
	ConvertRGB2NiColor( lightRes->m_lightSpecular, color );
	theApp.SetLightSpecularColor( color );
	ConvertRGB2NiColor( lightRes->m_colorSunless, color );
	theApp.SetSunLessColor( color );

	ConvertRGB2NiColor( fogRes->m_lightColor, color );
	theApp.SetFogColor( color );
	theApp.SetFogDepth( fogRes->m_lightNear, fogRes->m_lightFar );
}

void CToolEnvDlg::UpdateZoneList()
{
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	m_listEnv.ResetContent();
	
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}

	CString strName;
	for( sInt32 i=0; i<resMgr->GetEnvResList().size(); i++ ) {
		CNdlEnvRes* p	= (CNdlEnvRes*)(resMgr->GetEnvResList()[i]);
		Assert( NULL != p );
		strName			= p->GetName();
		m_listEnv.AddString( strName );
	}
}

void CToolEnvDlg::UpdateLightList()
{
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;
	
	m_listLight.ResetContent();
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}

	CString strName;
	for( sInt32 i=0; i<resMgr->GetLightList().size(); i++ ) {
		CNdlLightRes* p = (CNdlLightRes*)(resMgr->GetLightList()[i]);
		Assert( NULL != p );
		strName			= p->GetName();
		m_listLight.AddString( strName );
	}
}

void CToolEnvDlg::UpdateFogList()
{
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;
	
	m_listFog.ResetContent();
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}

	CString strName;
	for( sInt32 i=0; i<resMgr->GetFogList().size(); i++ ) {
		CNdlLightRes* p = (CNdlLightRes*)( resMgr->GetFogList()[i] );
		Assert( NULL != p );
		strName	= p->GetName();
		m_listFog.AddString( strName );
	}
}

void CToolEnvDlg::UpdateSelect()
{
	m_envName.SetWindowText( _T("") );
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;
	
	if( RES_INVALID_ID == m_curSel )
		return;

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}
	Assert( m_curSel>=0 && m_curSel<resMgr->GetEnvResList().size() );

	CNdlEnvRes* zoneRes	= (CNdlEnvRes*)resMgr->GetEnvResList()[m_curSel];
	
		
	m_listEnv.SetCurSel( m_curSel );
	m_listLight.SetCurSel( zoneRes->GetLightId() );
	m_listFog.SetCurSel( zoneRes->GetFogId() );
	CString strName;
	strName.Format(_T("%hs"),zoneRes->GetName());
	m_envName.SetWindowText( strName );
	
	UpdateData( FALSE );
}

void CToolEnvDlg::SaveEnv()
{
	int nCurEvnId = m_listEnv.GetCurSel();
	if (nCurEvnId != LB_ERR)
	{
		CResEditMgr *resMgr = (CResEditMgr *) theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
		if (resMgr == NULL)
			return;

		Assert(nCurEvnId >= 0 && nCurEvnId < resMgr->GetEnvResList().size());
		CNdlEnvRes *envRes = (CNdlEnvRes *) resMgr->GetEnvResList()[nCurEvnId];
		
		char envName[RES_NAME_LEN];
		CString strValue;
		m_envName.GetWindowText(strValue);
		if ((strValue.GetLength() <= (RES_NAME_LEN >> 1)) && (strValue.GetLength() > 0))
			SwPublicFunc::TChar2MutiChar(envName, RES_NAME_LEN*sizeof(char), strValue, (strValue.GetLength()+1) * sizeof(TCHAR));
		else
			strcpy_s(envName, "没有名字");

		if (strlen(envName) > 0)
			envRes->SetName(envName);

		int nCurLightId	= m_listLight.GetCurSel();		
		if (nCurEvnId != -1)
			envRes->SetLightId(nCurLightId);
		
		int nCurFogId = m_listFog.GetCurSel();
		if (nCurFogId != -1)
			envRes->SetFogId(nCurFogId);

		// 通过WorldBuffer来更新 [2012.4.14] wangshuai
		theApp.GetWorld()->GetWorldBuffer()->UpdateTileEnv(theApp.GetWorld()->GetWorldBuffer()->GetActiveTile(), nCurEvnId);

		// 设置Tile的Dirty标记
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify(CURRENTTILE);
	}
}


void CToolEnvDlg::SetSelectedZoneName(const char* pName )
{
	m_selectedEnv.SetWindowText( pName );
}

CToolEnv* CToolEnvDlg::GetToolZone()
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_ENV);
	CToolEnv* toolZone = (CToolEnv*)( toolManager->GetActiveTool() );
	Assert( NULL != toolZone );
	return toolZone;
}