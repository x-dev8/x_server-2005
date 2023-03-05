/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolTerrain.cpp
* Date: 	05/30/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include "Edit/ToolVertex.h"
#include "Edit/ToolManager.h"
#include "ToolTerrain.h"

////////////////////////////////////////////////////////////////////////////////
const TCHAR* cHeightType[] = { _T("隆起"), _T("柔化"), _T("斜面"), _T("推平") };

////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CToolTerrain, CDialog)

CToolTerrain::CToolTerrain(CToolTerrain* pParent)
						: CDialog(CToolTerrain::IDD, pParent)
{
	m_isActive = false;
}

CToolTerrain::~CToolTerrain()
{
	
}

void CToolTerrain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolTerrain)
	DDX_Control(pDX, IDC_CHECK_APPLYHEIGHT, m_chkApplyHeight);
	DDX_Control(pDX, IDC_HEIGHT_UPDOWN, m_btnHeight[0]);
	DDX_Control(pDX, IDC_HEIGHT_SMOOTH, m_btnHeight[1]);
	DDX_Control(pDX, IDC_HEIGHT_PLANE, m_btnHeight[2]);
	DDX_Control(pDX, IDC_HEIGHT_EQUAL, m_btnHeight[3]);
	DDX_Check(pDX, IDC_CHECK_APPLYHEIGHT, m_isApplyHeight);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CToolTerrain, CDialog)
	//{{AFX_MSG_MAP(CToolTerrain)
	ON_BN_CLICKED(IDC_CHECK_APPLYHEIGHT, OnChkApplyHeight)
	ON_EN_KILLFOCUS( IDC_EDIT_SIZE, OnKillFocusEditSize )
	ON_EN_KILLFOCUS( IDC_EDIT_HEIGHTSTRENGTH, OnKillFocusEditStrength )
	ON_EN_KILLFOCUS( IDC_EDIT_HEIGHTSPEED, OnKillFocusEditSpeed )
	ON_CONTROL_RANGE( BN_CLICKED, IDC_HEIGHT_UPDOWN, IDC_HEIGHT_EQUAL, OnBtnHeightClicked )
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CToolTerrain::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_sizeBitmap.LoadBitmap(IDB_BITMAP_TERRAIN);
	m_sizeImageList.Create(32, 32, ILC_COLOR16, 20, 1);
	m_sizeImageList.Add(&m_sizeBitmap, RGB(0,255,0));

	for( sInt32 i=0; i<4; i++ )	{
		m_btnHeight[i].SetIcon(CSize(32,32), m_sizeImageList.ExtractIcon(14+i));
	}
	GetDlgItem( IDC_EDIT_SIZE )->SetWindowText( _T("8") );
	GetDlgItem( IDC_EDIT_HEIGHTSTRENGTH )->SetWindowText( _T("50") );
	GetDlgItem( IDC_EDIT_HEIGHTSPEED )->SetWindowText( _T("100") );

	return TRUE;
}

void CToolTerrain::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{

	CDialog::OnVScroll( nSBCode, nPos, pScrollBar );
}

void CToolTerrain::SetActive( bool isModify )
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_VERTEX );
	GetToolVertex()->Bind(this);//jiayi,continue


	m_isActive = true;
}

void CToolTerrain::OnKillFocusEditSize()
{
	if( !m_isActive )
		return;

	UpdateData();
	
	CString strSize;	
	GetDlgItem( IDC_EDIT_SIZE )->GetWindowText( strSize );
	flt32 brushSize = _tstof( strSize );
	if( brushSize < 1.0f ) {
		brushSize = 1.0f;
		EditSizeChanged(brushSize);
	}
	else if( brushSize > 120.0f ){
		brushSize = 120.0f;
		GetDlgItem( IDC_EDIT_SIZE )->SetWindowText( _T("120") );
		UpdateData( FALSE );
	}
	GetToolVertex()->SetEditSize( brushSize );
}

void CToolTerrain::OnKillFocusEditStrength()
{
	if( !m_isActive )
		return;
	UpdateData();
	
	CString strValue;	
	GetDlgItem( IDC_EDIT_HEIGHTSTRENGTH )->GetWindowText( strValue );
	flt32 brushStrength = _tstof( strValue );
	if( brushStrength < 10.0f ) {
		brushStrength = 10.0f;
		GetDlgItem( IDC_EDIT_HEIGHTSTRENGTH )->SetWindowText( _T("10") );
		UpdateData( FALSE );
	}
	else if( brushStrength > 1000.0f ){
		brushStrength = 1000.0f;
		GetDlgItem( IDC_EDIT_HEIGHTSTRENGTH )->SetWindowText( _T("1000") );
		UpdateData( FALSE );
	}
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolVertex* toolVertex	= (CToolVertex*)toolMgr->GetTool( TOOL_VERTEX );
	Assert( NULL != toolVertex );
	toolVertex->SetEditStrength( brushStrength );
}

void CToolTerrain::OnKillFocusEditSpeed()
{
	if( !m_isActive )
		return;

	UpdateData();

	CString strValue;	
	GetDlgItem( IDC_EDIT_HEIGHTSPEED )->GetWindowText( strValue );
	flt32 brushSpeed = _tstof( strValue );
	if( brushSpeed < 10.0f ) {
		brushSpeed = 10.0f;
		GetDlgItem( IDC_EDIT_HEIGHTSPEED )->SetWindowText( _T("10") );
		UpdateData( FALSE );
	}
	else if( brushSpeed > 1000.0f ){
		brushSpeed = 1000.0f;
		GetDlgItem( IDC_EDIT_HEIGHTSPEED )->SetWindowText( _T("1000") );
		UpdateData( FALSE );
	}
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolVertex* toolVertex	= (CToolVertex*)toolMgr->GetTool( TOOL_VERTEX );
	Assert( NULL != toolVertex );
	toolVertex->SetEditSpeed( brushSpeed );
}

void CToolTerrain::OnChkApplyHeight()
{
	if( !m_isActive )
		return;

	UpdateData();
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolVertex* toolVertex	= (CToolVertex*)toolMgr->GetTool( TOOL_VERTEX );
	Assert( NULL != toolVertex );

	if( FALSE == m_isApplyHeight ) {
		for( sInt32 i=0; i<4; i++ ) {
			m_btnHeight[i].SetChecked( FALSE );
		}
		toolVertex->m_editType = znTVT_Unknow;
	}
}

void CToolTerrain::OnBtnHeightClicked(UINT nID)
{
	if( !m_isActive )
		return;

	UpdateData();

	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolVertex* toolVertex	= (CToolVertex*)toolMgr->GetTool( TOOL_VERTEX );
	Assert( NULL != toolVertex );
	
	sInt32 editType = nID - IDC_HEIGHT_UPDOWN;
	if( (editType<=znTVT_Unknow)  || (editType >= znTVT_Flight) )
		return;

	toolVertex->m_editType = (znVertexEditType)editType;

	for( sInt32 i=0; i<4; i++ )	{
		m_btnHeight[i].SetChecked( FALSE );
	}
	m_btnHeight[toolVertex->m_editType].SetChecked( TRUE );
	GetDlgItem(IDC_STATIC_HEIGHT)->SetWindowText( cHeightType[toolVertex->m_editType] );

	m_chkApplyHeight.SetCheck( BST_CHECKED );	
}

void CToolTerrain::EditSizeChanged(float editSize)
{
	CString strValue;
	strValue.Format(_T("%6.2f"),editSize);
	GetDlgItem( IDC_EDIT_SIZE )->SetWindowText( strValue );
	UpdateData( FALSE );
}

CToolVertex* CToolTerrain::GetToolVertex()
{
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	return	(CToolVertex*)toolMgr->GetTool( TOOL_VERTEX );
}
