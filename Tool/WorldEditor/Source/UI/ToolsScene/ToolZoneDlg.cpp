/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolZoneironment.cpp
* Date: 	06/12/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include "Edit/ToolZone.h"
#include "Edit/ToolManager.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "ToolZoneDlg.h"
#include "Map/WorldWriteStream.h"
////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CToolZoneDlg, CDialog)

CToolZoneDlg::CToolZoneDlg(CToolZoneDlg* pParent)
: CDialog(CToolZoneDlg::IDD, pParent)
{
	m_curSel		= RES_INVALID_ID;
	m_saved			= true;
}

CToolZoneDlg::~CToolZoneDlg()
{

}

void CToolZoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolZoneironmentDlg)	
	DDX_Control(pDX, IDC_EDIT_ARTFONT_LEFT, m_rectLeft);
	DDX_Control(pDX, IDC_EDIT_ARTFONT_TOP, m_rectTop);
	DDX_Control(pDX, IDC_EDIT_ARTFONT_RIGHT, m_rectRight);
	DDX_Control(pDX, IDC_EDIT_ARTFONT_BOTTOM, m_rectButtom);
	DDX_Control(pDX, IDC_LIST_ZONE, m_listZone);
	DDX_Control(pDX, IDC_EDIT_ZONE_NAME, m_zoneName);
	DDX_Control(pDX, IDC_EDT_BRUSH_RADIUS, m_brushRadius);
	DDX_Control(pDX, IDC_EDT_SELECTED_ZONE, m_selectedZone);
	DDX_Control(pDX, IDC_EDT_MUSIC, m_editMusic);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BTN_ZONE_SAVE, m_ZoneSave);
}
BEGIN_MESSAGE_MAP(CToolZoneDlg, CDialog)
	//{{AFX_MSG_MAP(CToolZONEDlg)
	ON_LBN_SELCHANGE(IDC_LIST_ZONE, OnClkListCtrl)
	ON_EN_KILLFOCUS(IDC_EDIT_ZONE_NAME, OnKillfocusName)
	ON_EN_KILLFOCUS(IDC_EDT_BRUSH_RADIUS, OnKillfocusRadius)
	ON_BN_CLICKED(IDC_RADIO_SET_ZONE, OnChkSetZone)
	ON_BN_CLICKED(IDC_RADIO_ZONE_PICK, OnChkPickZone)
	ON_BN_CLICKED(IDC_BTN_ZONE_SET, OnBtnSetZone )
	ON_BN_CLICKED(IDC_BTN_ZONE_ADD, OnBtnAddZone )
	ON_BN_CLICKED(IDC_BTN_ZONE_DEL, OnBtnDelZone )
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_ZONE_SAVE, &CToolZoneDlg::OnBnClickedBtnZoneSave)
END_MESSAGE_MAP()

BOOL CToolZoneDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editMusic.Initialize(this, BES_XT_CHOOSEFILE);
	m_editMusic.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );

	CheckDlgButton( IDC_RADIO_ZONE_PICK, 1 );
	m_brushRadius.SetWindowText( _T("0") );
	m_selectedZone.SetWindowText( _T("无") );
	UpdateData( FALSE );
	
	return TRUE;
}

void CToolZoneDlg::SetActive( bool isModify )
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_ZONE );
	CToolZone* toolZone = (CToolZone*)( toolManager->GetActiveTool() );
	Assert( NULL != toolZone );
	toolZone->Bind( this );

	UpdateZoneList();

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}
	if (resMgr->GetZoneResList().size() > 0 )
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

void CToolZoneDlg::OnClkListCtrl()
{
	m_curSel = m_listZone.GetCurSel();
	if( -1 != m_curSel ) {
		GetToolZone()->m_brushZoneId = m_curSel;

		GetToolZone()->UpdateZonePreview(m_curSel);

		// 通过WorldBuffer来更新 [2012.5.17] wangshuai
		theApp.GetWorld()->GetWorldBuffer()->UpdateTileEnv(theApp.GetWorld()->GetWorldBuffer()->GetActiveTile(), m_curSel);

		// 设置Tile的Dirty标记
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify(CURRENTTILE);
	}
}

void CToolZoneDlg::OnKillfocusName()
{
}

void CToolZoneDlg::OnKillfocusRadius()
{
	UpdateData();

	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_ZONE );
	CToolZone* toolZone = (CToolZone*)( toolManager->GetActiveTool() );
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


void CToolZoneDlg::OnChkPickZone()
{

	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolZone* zone			= (CToolZone*)toolMgr->GetTool( TOOL_ZONE );
	CheckDlgButton( IDC_RADIO_SET_ZONE, 0 );

	zone->SetPaintMode( false );
}

void CToolZoneDlg::OnChkSetZone()
{

	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolZone* zone			= (CToolZone*)toolMgr->GetTool( TOOL_ZONE );
	CheckDlgButton( IDC_RADIO_ZONE_PICK, 0 );

	zone->SetPaintMode( true );
}

void CToolZoneDlg::OnBtnSetZone()
{
	if( RES_INVALID_ID == m_curSel )
		return;

	UpdateData();

	char zoneName[RES_NAME_LEN];
	CString strValue;
	m_zoneName.GetWindowText( strValue );
	if( (strValue.GetLength()<=(RES_NAME_LEN>>1)) && (strValue.GetLength()>0) )	{
		SwPublicFunc::TChar2MutiChar( zoneName, RES_NAME_LEN*sizeof(char), strValue, (strValue.GetLength()+1)*sizeof(TCHAR) );
	}
	else {
		strcpy_s( zoneName, "没有名字" );
	}
	m_editMusic.GetWindowText(strValue);
	char musicPath[MAX_PATH*2];
	if ((strValue.GetLength()>0))
	{
		/*
		 * Author:	2012-8-11 wangshuai
		 * Desc: 	从全路径中分解出相对路径
		 */
		int pos = strValue.Find("Data");
		if (pos != -1)
			strValue = strValue.Right(strValue.GetLength() - pos);

		strcpy(musicPath, strValue);
		//GetToolZone()->GetRelativePath(strValue.GetString(),musicPath);
	}
	else {
		memset(musicPath,0,sizeof(char)*MAX_PATH*2);
	}

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}
	CNdlZoneRes* zoneRes	= resMgr->GetZoneRes(m_curSel);
	zoneRes->SetMuiscPath(musicPath);
	zoneRes->SetName( zoneName );
	m_saved = false;
	GetToolZone()->UpdateZonePreview(m_curSel);
}

void CToolZoneDlg::OnBtnAddZone()
{
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	UpdateData();

	char zoneName[RES_NAME_LEN];
	CString strValue;
	m_zoneName.GetWindowText( strValue );
	if( (strValue.GetLength()<=(RES_NAME_LEN>>1)) && (strValue.GetLength()>0) )	{
		SwPublicFunc::TChar2MutiChar( zoneName, RES_NAME_LEN*sizeof(char), strValue, (strValue.GetLength()+1)*sizeof(TCHAR) );
	}
	else {
		strcpy_s( zoneName, "没有名字" );
	}

	m_editMusic.GetWindowText(strValue);
	char musicPath[MAX_PATH*2];
	if( (strValue.GetLength()>0) )	{
		GetToolZone()->GetRelativePath(strValue.GetString(),musicPath);
	}
	else {
		memset(musicPath,0,sizeof(char)*MAX_PATH*2);
	}

	RECT rect = {0,0,0,0};
	CString strRect;
	m_rectLeft.GetWindowText(strRect);
	if(strRect.GetLength() > 0)
		rect.left = atoi(strRect.GetBuffer(0));

	m_rectTop.GetWindowText(strRect);
	if(strRect.GetLength() > 0)
		rect.top = atoi(strRect.GetBuffer(0));

	m_rectRight.GetWindowText(strRect);
	if(strRect.GetLength() > 0)
		rect.right = atoi(strRect.GetBuffer(0));

	m_rectButtom.GetWindowText(strRect);
	if(strRect.GetLength() > 0)
		rect.bottom = atoi(strRect.GetBuffer(0));

// 	m_rectTop.GetWindowText(rect.top);
// 	m_rectRight.GetWindowText(rect.right);
// 	m_rectButtom.GetWindowText(rect.bottom);
	CreateZone( zoneName, musicPath, &rect);

	UpdateData( FALSE );
}

void CToolZoneDlg::OnBtnDelZone()
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

	Assert( m_curSel>=0 && m_curSel<resMgr->GetZoneResList().size() );

	resMgr->DeleteZoneRes(m_curSel);
	m_saved = false;

	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	CToolZone* toolZone = (CToolZone*)( toolManager->GetActiveTool() );
	Assert( NULL != toolZone );

	m_curSel				= RES_INVALID_ID;
	toolZone->m_brushZoneId = RES_INVALID_ID;

	UpdateZoneList();

	UpdateData( FALSE );
}

bool CToolZoneDlg::CreateZone( const char* zoneName, const char* musicPath, const RECT* pRect)
{
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return false;
	}

	resMgr->CreateZone( zoneName, musicPath, pRect );
	m_saved = false;

	UpdateZoneList();
	
	return true;
}

void CToolZoneDlg::UpdateZoneInfo( sInt32 zoneId )
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
	Assert( zoneId>=0 && zoneId<resMgr->GetZoneResList().size() );
	

	CNdlZoneRes* zoneRes	= (CNdlZoneRes*)resMgr->GetZoneResList()[zoneId];
	
	CString strName;
	strName					= zoneRes->GetName();
	m_zoneName.SetWindowText( strName );
	SetSelectedZoneName(strName);


	if (zoneRes->GetMuiscPath())
	{
		strName.Format("%s\\%s",CWorld::GetAppDataCharDir(),zoneRes->GetMuiscPath());
	}
	else
	{
		strName = '\0';
	}
	m_editMusic.SetWindowText( strName );
	if (zoneRes->GetFontRect())
	{
		CString strRect;
		strRect.Format("%d", zoneRes->GetFontRect()->left);
		m_rectLeft.SetWindowText(strRect);

		strRect.Format("%d", zoneRes->GetFontRect()->top);
			m_rectTop.SetWindowText(strRect);

		strRect.Format("%d", zoneRes->GetFontRect()->right);
			m_rectRight.SetWindowText(strRect);

		strRect.Format("%d", zoneRes->GetFontRect()->bottom);
			m_rectButtom.SetWindowText(strRect);
	}

	UpdateData( FALSE );
}

void CToolZoneDlg::UpdateWorldZone()
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
	Assert( m_curSel>=0 && m_curSel<resMgr->GetZoneResList().size() );

}

void CToolZoneDlg::UpdateZoneList()
{
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	m_listZone.ResetContent();
	
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}

	CString strName;
	for( sInt32 i=0; i<resMgr->GetZoneResList().size(); i++ ) {
		CNdlZoneRes* p	= (CNdlZoneRes*)(resMgr->GetZoneResList()[i]);
		Assert( NULL != p );
		strName			= p->GetName();
		m_listZone.AddString( strName );
	}
}


void CToolZoneDlg::UpdateSelect()
{
	m_zoneName.SetWindowText( _T("") );
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
	Assert( m_curSel>=0 && m_curSel<resMgr->GetZoneResList().size() );

	CNdlZoneRes* zoneRes	= (CNdlZoneRes*)resMgr->GetZoneResList()[m_curSel];
	
		
	m_listZone.SetCurSel( m_curSel );
	CString strName;
	strName.Format(_T("%hs"),zoneRes->GetName());
	m_zoneName.SetWindowText( strName );
	if (zoneRes->GetMuiscPath())
	{
		strName.Format("%s\\%s",CWorld::GetAppDataCharDir(),zoneRes->GetMuiscPath());
	}
	else
	{
		strName = '\0';
	}
	m_editMusic.SetWindowText( strName );
	
	if (zoneRes->GetFontRect())
	{
		CString strRect;
		strRect.Format("%d", zoneRes->GetFontRect()->left);
			m_rectLeft.SetWindowText(strRect);

		strRect.Format("%d", zoneRes->GetFontRect()->top);
			m_rectTop.SetWindowText(strRect);

		strRect.Format("%d", zoneRes->GetFontRect()->right);
			m_rectRight.SetWindowText(strRect);

		strRect.Format("%d", zoneRes->GetFontRect()->bottom);
			m_rectButtom.SetWindowText(strRect);
	}
	
	UpdateData( FALSE );
}


void CToolZoneDlg::SetSelectedZoneName(const char* pName )
{
	m_selectedZone.SetWindowText( pName );
}

CToolZone* CToolZoneDlg::GetToolZone()
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_ZONE );
	CToolZone* toolZone = (CToolZone*)( toolManager->GetActiveTool() );
	Assert( NULL != toolZone );
	return toolZone;
}
void CToolZoneDlg::OnBnClickedBtnZoneSave()
{
	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;
	if (m_saved)
	{
		return;
	}
	CWorldTile* tile = CURRENTTILE;
	if (!tile)
	{
		return;
	}

	CWorldWriteStream	writeStream(SwGlobal::GetWorld());
	char gameMapPath[MAX_PATH];
	sprintf_s(gameMapPath, MAX_PATH - 1, "%s\\%s",SwGlobal::GetWorld()->GetWorldPath(),tile->GetPathName());

	char* pFind = strstr(gameMapPath,".mew");
	strcpy(&pFind[1],"Zone");
	writeStream.WriteZoneRes(gameMapPath);
	m_saved = true;
}
