/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolModel.cpp
* Date: 	05/30/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include "Edit/ToolObject.h"
#include "Edit/ToolManager.h"
#include "ToolModel.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "MeTerrain/Lighting/StaticMeshRayTracer.h"
#include "ui/Dlg/LightMapMeshProcessDlg.h"
#include "ndl/NdlWorldEditor.h"
#include "MeTerrain/Lighting/LightMapTexture.h"
#include "ui/Custom/PathDialog.h"

const sInt32 s_DIRECTORY = -1;

////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CToolModel, CDialog)

CToolModel::CToolModel(CToolModel* pParent)
: ScrollableDialog(CToolModel::IDD, pParent, SB_VERT)
{
}

CToolModel::~CToolModel()
{

}

void CToolModel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolTerrain)
	DDX_Control(pDX, IDC_CHECK_RECURSION, m_chkRecursion);
	DDX_Control(pDX, IDC_TREE_MODEL, m_treeModel);
	//DDX_Control(pDX, IDC_CHK_PICKOBJ, m_chkPickObj);
	DDX_Control(pDX, IDC_CHK_LOCK_PARAM, m_chkLockParam);
	// 	DDX_Control(pDX, IDC_CHK_LOCK_PARAM_OFF, m_chkLockParamOff);
	// 	DDX_Control(pDX, IDC_CHK_LOCK_PARAM_ROT, m_chkLockParamRot);
	// 	DDX_Control(pDX, IDC_CHK_LOCK_PARAM_SCL, m_chkLockParamScl);
	DDX_Control(pDX, IDC_EDT_WORLD_X, m_editPosX);
	DDX_Control(pDX, IDC_EDT_WORLD_Y, m_editPosY);
	DDX_Control(pDX, IDC_EDT_WORLD_Z, m_editPosZ);
	DDX_Control(pDX, IDC_EDT_OFFSET_POS_X, m_editOffX);
	DDX_Control(pDX, IDC_EDT_OFFSET_POS_Y, m_editOffY);
	DDX_Control(pDX, IDC_EDT_OFFSET_POS_Z, m_editOffZ);
	DDX_Control(pDX, IDC_EDT_OFFSET_ROT_X, m_editRotX);
	DDX_Control(pDX, IDC_EDT_OFFSET_ROT_Y, m_editRotY);
	DDX_Control(pDX, IDC_EDT_OFFSET_ROT_Z, m_editRotZ);
	DDX_Control(pDX, IDC_EDT_OFFSET_SCL_XYZ, m_editSclXYZ);

	DDX_Control(pDX, IDC_EDT_WORLD_X_SPIN, m_spinPosX);
	DDX_Control(pDX, IDC_EDT_WORLD_Y_SPIN, m_spinPosY);
	DDX_Control(pDX, IDC_EDT_WORLD_Z_SPIN, m_spinPosZ);
	DDX_Control(pDX, IDC_EDT_OFFSET_POS_X_SPIN, m_spinOffX);
	DDX_Control(pDX, IDC_EDT_OFFSET_POS_Y_SPIN, m_spinOffY);
	DDX_Control(pDX, IDC_EDT_OFFSET_POS_Z_SPIN, m_spinOffZ);
	DDX_Control(pDX, IDC_EDT_OFFSET_ROT_X_SPIN, m_spinRotX);
	DDX_Control(pDX, IDC_EDT_OFFSET_ROT_Y_SPIN, m_spinRotY);
	DDX_Control(pDX, IDC_EDT_OFFSET_ROT_Z_SPIN, m_spinRotZ);
	DDX_Control(pDX, IDC_EDT_OFFSET_SCL_XYZ_SPIN, m_spinSclXYZ);
	DDX_Control(pDX, IDC_LIST_PICKED_MODEL, m_listPickedModel);
	DDX_Control(pDX, IDC_EDT_CHANGE_MODEL_PATH, m_editChangeModelPath);

	DDX_Control(pDX, IDC_CHECK_LIGHTMAP_CASTSHADOW, m_checkCastShadow);
	DDX_Control(pDX, IDC_COMBO_LIGHTMAP_RESOLUTION, m_comboLightmapResolution);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CToolModel, CDialog)
	//{{AFX_MSG_MAP(CToolModel)
	ON_BN_CLICKED(IDC_CHECK_RECURSION, OnChkRecursion)
	ON_BN_CLICKED( IDC_BTN_MODEL_ADD, OnBtnAddModel )
	//ON_BN_CLICKED(IDC_CHK_PICKOBJ, OnChkPickobj)
	ON_BN_CLICKED(IDC_CHK_LOCK_PARAM, OnChkLockParam)
	ON_BN_CLICKED(IDC_BTN_SET, OnBnClickedBtnSync)
	ON_BN_CLICKED(IDC_BTN_RESET, OnBnClickedBtnReset)
	//	ON_NOTIFY(NM_DBLCLK, IDC_TREE_MODEL, OnModelChange)
	ON_EN_KILLFOCUS(IDC_EDT_WORLD_X, OnKillfocusEdtWorld)
	ON_EN_KILLFOCUS(IDC_EDT_WORLD_Y, OnKillfocusEdtWorld)
	ON_EN_KILLFOCUS(IDC_EDT_WORLD_Z, OnKillfocusEdtWorld)
	ON_EN_KILLFOCUS(IDC_EDT_OFFSET_POS_X, OnKillfocusEdtOff)
	ON_EN_KILLFOCUS(IDC_EDT_OFFSET_POS_Y, OnKillfocusEdtOff)
	ON_EN_KILLFOCUS(IDC_EDT_OFFSET_POS_Z, OnKillfocusEdtOff)
	ON_EN_KILLFOCUS(IDC_EDT_OFFSET_ROT_X, OnKillfocusEdtRot)
	ON_EN_KILLFOCUS(IDC_EDT_OFFSET_ROT_Y, OnKillfocusEdtRot)
	ON_EN_KILLFOCUS(IDC_EDT_OFFSET_ROT_Z, OnKillfocusEdtRot)
	ON_EN_KILLFOCUS(IDC_EDT_OFFSET_SCL_XYZ, OnKillfocusEdtScl)
	//}}AFX_MSG_MAP
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_MODEL, &CToolModel::OnModelChange)
	ON_LBN_SELCHANGE(IDC_LIST_PICKED_MODEL, &CToolModel::OnLbnSelchangeListPickedModel)
	ON_BN_CLICKED(IDC_BTN_MODEL_CHANGE, &CToolModel::OnBnClickedBtnModelChange)
	ON_COMMAND(ID_POP_model_move, &CToolModel::OnPopmodelmove)
	ON_COMMAND(ID_POP_model_rotate, &CToolModel::OnPopmodelrotate)
	ON_COMMAND(ID_POP_model_scale, &CToolModel::OnPopmodelscale)
	ON_BN_CLICKED(IDC_CHECK_LIGHTMAP_CASTSHADOW, OnChkLightmapCastShadow)
	ON_CBN_SELCHANGE(IDC_COMBO_LIGHTMAP_RESOLUTION, OnCbnSelchangeLightmapResolution)
	ON_BN_CLICKED(IDC_BTN_LIGHTMAP_ONEMODEL, OnBnClickedBuildLightmapOneModel)

	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CToolModel::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_spinPosX.SetBuddy( &m_editPosX );
	m_spinPosX.SetRange32( -0xfffffff, 0xfffffff);  
	m_spinPosX.SetPos( 0 );
	m_spinPosY.SetBuddy( &m_editPosY );
	m_spinPosY.SetRange32( -0xfffffff, 0xfffffff);  
	m_spinPosY.SetPos( 0 );
	m_spinPosZ.SetBuddy( &m_editPosZ );
	m_spinPosZ.SetRange32( -0xfffffff, 0xfffffff);  
	m_spinPosZ.SetPos( 0 );

	m_spinOffX.SetBuddy( &m_editOffX );
	m_spinOffX.SetRange( -100, 100 );  
	m_spinOffX.SetPos( 0 );
	m_spinOffY.SetBuddy( &m_editOffY );
	m_spinOffY.SetRange( -100, 100 );  
	m_spinOffY.SetPos( 0 );
	m_spinOffZ.SetBuddy( &m_editOffZ );
	m_spinOffZ.SetRange( -100, 100 );  
	m_spinOffZ.SetPos( 0 );

	m_spinRotX.SetBuddy( &m_editRotX );
	m_spinRotX.SetRange( -359, 359 );  
	m_spinRotX.SetPos( 0 );
	m_spinRotY.SetBuddy( &m_editRotY );
	m_spinRotY.SetRange( -359, 359 );  
	m_spinRotY.SetPos( 0 );
	m_spinRotZ.SetBuddy( &m_editRotZ );
	m_spinRotZ.SetRange( -359, 359 );  
	m_spinRotZ.SetPos( 0 );

	m_spinSclXYZ.SetBuddy( &m_editSclXYZ );
	m_spinSclXYZ.SetRange( 0, 1000 );  
	m_spinSclXYZ.SetPos( 100 );

	m_chkRecursion.SetCheck( 1 );


	m_sizeBitmap.LoadBitmap(IDB_BITMAP_WORLDTREEICON);
	m_sizeImageList.Create(16, 15, ILC_COLOR16, 2, 1);
	m_sizeImageList.Add(&m_sizeBitmap, RGB(0,255,0));
	m_treeModel.SetImageList(&m_sizeImageList,LVSIL_NORMAL);

	HTREEITEM rootItem = m_treeModel.InsertItem( _T("模型树"));
	m_treeModel.SetItemData( rootItem, s_DIRECTORY );
	m_treeModel.SetItemImage(rootItem,0,0);

	m_editChangeModelPath.Initialize(this, BES_XT_CHOOSEFILE);
	m_editChangeModelPath.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );

	m_comboLightmapResolution.ResetContent();
	//m_comboLightmapResolution.AddString("1024*1024");
	m_comboLightmapResolution.AddString("512*512");
	m_comboLightmapResolution.AddString("256*256");
	m_comboLightmapResolution.AddString("128*128");
	m_comboLightmapResolution.AddString("64*64");
	m_comboLightmapResolution.AddString("32*32");
	m_comboLightmapResolution.AddString("16*16");
	m_comboLightmapResolution.AddString("8*8");
	m_comboLightmapResolution.AddString("4*4");
	return TRUE;
}

void CToolModel::SetActive( bool isModify )
{
	CToolObject* toolObject = GetToolObject();
	Assert( NULL != toolObject );
	toolObject->Bind( this );
}

void CToolModel::RefreshInfo()
{
	CString strValue;

	CToolObject* toolObject = GetToolObject();

	m_spinPosX.SetPos( ZnFloat2Int( toolObject->m_transformingVisitor.m_position[0] ) );
	strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_position[0] );
	m_editPosX.SetWindowText( strValue );
	m_spinPosY.SetPos( ZnFloat2Int( toolObject->m_transformingVisitor.m_position[1] ) );
	strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_position[1] );
	m_editPosY.SetWindowText( strValue );
	m_spinPosZ.SetPos( ZnFloat2Int( toolObject->m_transformingVisitor.m_position[2] ) );
	strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_position[2] );
	m_editPosZ.SetWindowText( strValue );

	m_spinOffX.SetPos( ZnFloat2Int( toolObject->m_transformingVisitor.m_offset[0]*10 ) );
	strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_offset[0] );
	m_editOffX.SetWindowText( strValue );

	m_spinOffY.SetPos( ZnFloat2Int( toolObject->m_transformingVisitor.m_offset[1]*10 ) );
	strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_offset[1] );
	m_editOffY.SetWindowText( strValue );

	m_spinOffZ.SetPos( ZnFloat2Int( toolObject->m_transformingVisitor.m_offset[2]*10 ) );
	strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_offset[2] );
	m_editOffZ.SetWindowText( strValue );


	m_spinRotX.SetPos( ZnFloat2Int( toolObject->m_transformingVisitor.m_rotate[0] ) );
	strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_rotate[0] );
	m_editRotX.SetWindowText( strValue );

	m_spinRotY.SetPos( ZnFloat2Int( toolObject->m_transformingVisitor.m_rotate[1] ) );
	strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_rotate[1] );
	m_editRotY.SetWindowText( strValue );

	m_spinRotZ.SetPos( ZnFloat2Int( toolObject->m_transformingVisitor.m_rotate[2] ) );
	strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_rotate[2] );
	m_editRotZ.SetWindowText( strValue );

	m_spinSclXYZ.SetPos( ZnFloat2Int( toolObject->m_transformingVisitor.m_scale[0]*100.0f ) );
	strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_scale[0]*100.0f );
	m_editSclXYZ.SetWindowText( strValue );

	if (!toolObject->m_selectingVisitor.m_selectModels.empty())
	{
		m_chkLockParam.SetCheck(toolObject->IsLockHeight());

		m_checkCastShadow.SetCheck((*(toolObject->m_selectingVisitor.m_selectModels.begin())).pModel->CastShadow());
		m_comboLightmapResolution.SetCurSel((*(toolObject->m_selectingVisitor.m_selectModels.begin())).pModel->GetLightMapScale());
	}
	UpdateData( FALSE );
}

void CToolModel::UpdateModelTree(LPCTSTR ppathName, bool isRecursion)
{
	m_treeModel.DeleteAllItems();
	CString strPath(ppathName);
	CString worldName = strPath.Mid(strPath.ReverseFind('\\') + 1 );
	HTREEITEM rootItem = m_treeModel.InsertItem( worldName );
	m_treeModel.SetItemData( rootItem, s_DIRECTORY );
	m_treeModel.SetItemImage(rootItem,0,0);
	CreateModelTree(strPath,rootItem,isRecursion);
}

void CToolModel::UpdateWorldPos()
{
	UpdateData();

	CToolObject* toolObject = GetToolObject();

	CString strValue;
	m_editPosX.GetWindowText( strValue );
	toolObject->m_transformingVisitor.m_position[0]	= _tstof( strValue );
	m_editPosY.GetWindowText( strValue );
	toolObject->m_transformingVisitor.m_position[1]	= _tstof( strValue );
	m_editPosZ.GetWindowText( strValue );
	toolObject->m_transformingVisitor.m_position[2]	= _tstof( strValue );

	toolObject->m_transformingVisitor.UpdateModel();
}

void CToolModel::UpdateOff(UINT nPos, CScrollBar* pScrollBar)
{

	UpdateData();
	CToolObject* toolObject = GetToolObject();
	CString strValue;
	switch (pScrollBar->GetDlgCtrlID() )
	{
	case IDC_EDT_OFFSET_POS_X_SPIN:
		{
			short nCurrPos = m_spinOffX.GetPos();
			toolObject->m_transformingVisitor.m_offset[0] = ((flt32)nCurrPos)/10;
			toolObject->m_transformingVisitor.m_offset[0] = ZnClamp<flt32>( toolObject->m_transformingVisitor.m_offset[0], -100.0f, 100.0f );
			strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_offset[0] );
			m_editOffX.SetWindowText( strValue );
		}
		break;
	case IDC_EDT_OFFSET_POS_Y_SPIN:
		{
			short nCurrPos = m_spinOffY.GetPos();
			toolObject->m_transformingVisitor.m_offset[1] = ((flt32)nCurrPos)/10;
			toolObject->m_transformingVisitor.m_offset[1] = ZnClamp<flt32>( toolObject->m_transformingVisitor.m_offset[1], -100.0f, 100.0f );
			strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_offset[1] );
			m_editOffY.SetWindowText( strValue );
		}
		break;
	case IDC_EDT_OFFSET_POS_Z_SPIN:
		{
			short nCurrPos = m_spinOffZ.GetPos();
			toolObject->m_transformingVisitor.m_offset[2] = ((flt32)nCurrPos)/10;
			toolObject->m_transformingVisitor.m_offset[2] = ZnClamp<flt32>( toolObject->m_transformingVisitor.m_offset[2], -100.0f, 100.0f );
			strValue.Format( _T("%.3f"), toolObject->m_transformingVisitor.m_offset[2] );
			m_editOffZ.SetWindowText( strValue );
		}
		break;
	}

	toolObject->m_transformingVisitor.UpdateModel();
}

void CToolModel::UpdateOff()
{
	UpdateData();

	CToolObject* toolObject = GetToolObject();

	CString strValue;
	m_editOffX.GetWindowText( strValue );
	toolObject->m_transformingVisitor.m_offset[0]	= _tstof( strValue );
	toolObject->m_transformingVisitor.m_offset[0] = ZnClamp<flt32>( toolObject->m_transformingVisitor.m_offset[0], -100.0f, 100.0f );

	m_editOffY.GetWindowText( strValue );
	toolObject->m_transformingVisitor.m_offset[1]	= _tstof( strValue );
	toolObject->m_transformingVisitor.m_offset[1] = ZnClamp<flt32>( toolObject->m_transformingVisitor.m_offset[1], -100.0f, 100.0f );
	m_editOffZ.GetWindowText( strValue );
	toolObject->m_transformingVisitor.m_offset[2]	= _tstof( strValue );
	toolObject->m_transformingVisitor.m_offset[2] = ZnClamp<flt32>( toolObject->m_transformingVisitor.m_offset[2], -100.0f, 100.0f );
	toolObject->m_transformingVisitor.UpdateModel();
}

void CToolModel::UpdateRot()
{
	UpdateData();

	CToolObject* toolObject = GetToolObject();

	CString strValue;
	m_editRotX.GetWindowText( strValue );
	toolObject->m_transformingVisitor.m_rotate[0]	= _tstof( strValue );
	toolObject->m_transformingVisitor.m_rotate[0] = ZnClamp<flt32>( toolObject->m_transformingVisitor.m_rotate[0], -360.0f, 360.0f );
	m_editRotY.GetWindowText( strValue );
	toolObject->m_transformingVisitor.m_rotate[1]	= _tstof( strValue );
	toolObject->m_transformingVisitor.m_rotate[1] = ZnClamp<flt32>( toolObject->m_transformingVisitor.m_rotate[1], -360.0f, 360.0f );
	m_editRotZ.GetWindowText( strValue );
	toolObject->m_transformingVisitor.m_rotate[2]	= _tstof( strValue );
	toolObject->m_transformingVisitor.m_rotate[2] = ZnClamp<flt32>( toolObject->m_transformingVisitor.m_rotate[2], -360.0f, 360.0f );
	toolObject->m_transformingVisitor.UpdateModel();
}

void CToolModel::UpdateScl()
{
	UpdateData();

	short nCurrPos = m_spinSclXYZ.GetPos();
	//m_editSclXYZ.SetWindowText()
	TRACE(_T("CToolModel: [UpdateScl] m_spinSclXYZ.GetPos() = %d.\n"), nCurrPos);

	CToolObject* toolObject = GetToolObject();

	CString strValue;
	m_editSclXYZ.GetWindowText( strValue );
	toolObject->m_transformingVisitor.m_scale[0]	= _tstof( strValue ) / 100.0f;
	toolObject->m_transformingVisitor.m_scale[0]	= ZnClamp<flt32>( toolObject->m_transformingVisitor.m_scale[0], 0.01f, 10.0f );
	toolObject->m_transformingVisitor.m_scale[1]	= toolObject->m_transformingVisitor.m_scale[0];
	toolObject->m_transformingVisitor.m_scale[2]	= toolObject->m_transformingVisitor.m_scale[0];
	toolObject->m_transformingVisitor.UpdateModel();
}

void CToolModel::OnChkRecursion() 
{

}

void CToolModel::OnBtnAddModel()
{
	CString strPath;
	strPath.Format( _T("%s\\Data\\SceneObject"), CWorld::GetAppDataCharDir() );
	strPath.MakeLower();

	CPathDialog dirDlg("选择目录对话框", "请选择模型目录", strPath);
	if( dirDlg.DoModal() == IDOK ) {
		CToolObject* toolObject = GetToolObject();
		Assert( NULL != toolObject );

		UpdateData();

		m_currRoot = dirDlg.GetPathName();

		bool isRecursion = false;
		if( BST_CHECKED == m_chkRecursion.GetCheck() ) {
			isRecursion = true;
		}

		toolObject->EnumFile( m_currRoot, isRecursion );

		UpdateModelTree(m_currRoot,isRecursion);
	}
}

void CToolModel::OnModelChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolObject* toolObject		= (CToolObject*)toolMgr->GetTool( TOOL_OBJECT );
	// 	if( toolObject->m_isPickObj )
	// 		return;

	HTREEITEM selItem	= m_treeModel.GetSelectedItem();
	uInt32 tileId	= m_treeModel.GetItemData( selItem );
	if (s_DIRECTORY == tileId)//目录
		return;


	//	if( BST_CHECKED != m_chkLockParamOff.GetCheck() ) 
	{
		m_editOffX.SetWindowText( _T("0.0") );
		m_editOffY.SetWindowText( _T("0.0") );
		m_editOffZ.SetWindowText( _T("0.0") );
		m_spinOffX.SetPos( 0 );
		m_spinOffY.SetPos( 0 );
		m_spinOffZ.SetPos( 0 );

		for( sInt32 i=0; i<3; i++ ) {
			toolObject->m_transformingVisitor.m_offset[i]		= 0.0f;
		}
	}
	//	if( BST_CHECKED != m_chkLockParamRot.GetCheck() ) 
	{
		m_editRotX.SetWindowText( _T("0.0") );
		m_editRotY.SetWindowText( _T("0.0") );
		m_editRotZ.SetWindowText( _T("0.0") );
		m_spinRotX.SetPos( 0 );
		m_spinRotY.SetPos( 0 );
		m_spinRotZ.SetPos( 0 );
		for( sInt32 i=0; i<3; i++ ) {
			toolObject->m_transformingVisitor.m_rotate[i]		= 0.0f;
		}
	}
	//	if( BST_CHECKED != m_chkLockParamScl.GetCheck() ) 
	{
		m_editSclXYZ.SetWindowText( _T("100") );
		m_spinSclXYZ.SetPos( 100 );
		for( sInt32 i=0; i<3; i++ ) {
			toolObject->m_transformingVisitor.m_scale[i]		= 1.0f;
		}
	}
	UpdateData( FALSE );

	toolObject->m_selectingVisitor.Reset();	//防止此刻被选择地物体位置被改变
	toolObject->m_transformingVisitor.UpdateModel();

	UpdateData();

	CString fullModelName;
	if (GetCurrentName(fullModelName))
	{
		toolObject->SetModelId( fullModelName );
	}
}

void CToolModel::OnChkPickobj()
{
	/*
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolObject* object		= (CToolObject*)toolMgr->GetTool( TOOL_OBJECT );

	//object->m_isPickObj		= ( BST_CHECKED == m_chkPickObj.GetCheck() );
	object->m_selModelId	= RES_INVALID_ID;
	//object->m_selObject     = NULL;
	if( !object->m_isPickObj && !m_currRoot.IsEmpty()) {
	CString fullModelName;
	if (GetCurrentName(fullModelName))
	{
	object->SetModelId( fullModelName );
	}

	}
	*/
}

void CToolModel::OnChkLockParam()
{
	UpdateData();
	CToolObject* toolObject = GetToolObject();

	toolObject->LockHeight(BST_CHECKED == m_chkLockParam.GetCheck());
	// 	if( BST_CHECKED == m_chkLockParam.GetCheck() ) {
	// 		m_chkLockParamOff.SetCheck( 1 );
	// 		m_chkLockParamRot.SetCheck( 1 );
	// 		m_chkLockParamScl.SetCheck( 1 );
	// 	}
	// 	else {
	// 		m_chkLockParamOff.SetCheck( 0 );
	// 		m_chkLockParamRot.SetCheck( 0 );
	// 		m_chkLockParamScl.SetCheck( 0 );
	// 	}
	UpdateData( FALSE );
}

void CToolModel::OnKillfocusEdtWorld()
{
	UpdateWorldPos();
}

void CToolModel::OnKillfocusEdtOff()
{
	UpdateOff();
}

void CToolModel::OnKillfocusEdtRot()
{
	UpdateRot();
}

void CToolModel::OnKillfocusEdtScl()
{
	UpdateScl();
}

void CToolModel::OnBnClickedBtnSync()
{
	CToolObject* toolObject = GetToolObject();
	toolObject->SyncOffset2WorldPos();
	//UpdatePos();
	// 	UpdateOff();
	// 	UpdateRot();
	// 	UpdateScl();
}

void CToolModel::OnBnClickedBtnReset()
{

	m_editOffX.SetWindowText( _T("0.0") );
	m_editOffY.SetWindowText( _T("0.0") );
	m_editOffZ.SetWindowText( _T("0.0") );
	m_spinOffX.SetPos( 0 );
	m_spinOffY.SetPos( 0 );
	m_spinOffZ.SetPos( 0 );

	m_editRotX.SetWindowText( _T("0.0") );
	m_editRotY.SetWindowText( _T("0.0") );
	m_editRotZ.SetWindowText( _T("0.0") );
	m_spinRotX.SetPos( 0 );
	m_spinRotY.SetPos( 0 );
	m_spinRotZ.SetPos( 0 );

	m_editSclXYZ.SetWindowText( _T("100") );
	m_spinSclXYZ.SetPos( 100 );

	UpdateData( FALSE );

	CToolObject* toolObject = GetToolObject();
	for( sInt32 i=0; i<3; i++ ) {
		toolObject->m_transformingVisitor.m_offset[i]		= 0.0f;
		toolObject->m_transformingVisitor.m_rotate[i]		= 0.0f;
		toolObject->m_transformingVisitor.m_scale[i]		= 1.0f;
	}
	toolObject->m_transformingVisitor.UpdateModel();
}

void CToolModel::CreateModelTree( LPCTSTR strDir,HTREEITEM rootItem , bool isRecursion)
{
	CFileFind ff;
	CString strPath( strDir );
	strPath += _T("\\*.*");
	BOOL bFound = ff.FindFile(strPath);
	if (!bFound) 
		return;

	while (bFound)
	{
		bFound = ff.FindNextFile();

		if (ff.IsDots())
			continue;

		strPath = ff.GetFilePath();
		if (ff.IsDirectory()) {
			CString worldName = strPath.Mid(strPath.ReverseFind('\\') + 1);

			HTREEITEM newItem	= m_treeModel.InsertItem ( worldName, 1, 1,rootItem );
			m_treeModel.SetItemData( newItem, s_DIRECTORY );
			m_treeModel.SetItemImage(newItem,0,0);
			if (isRecursion)
			{
				CreateModelTree(strPath,newItem,isRecursion);
			}
		}
		else
			strPath.MakeLower();
		int nMexPos = strPath.Find(_T(".mex"));
		if((-1 == nMexPos || (nMexPos != strPath.GetLength() - 4 ))) 
		{
			continue;
		}
		AddChildLeafNode(strPath, rootItem);
	}
}

HTREEITEM CToolModel::AddChildLeafNode( CString strPath, HTREEITEM rootItem )
{
	CString worldName = strPath.Mid(strPath.ReverseFind('\\') + 1 );
	// 	sInt32 pos				= worldName.Find(_T("."));
	// 	if( -1 != pos )
	// 		worldName		= worldName.Left( pos );
	HTREEITEM newItem	= m_treeModel.InsertItem ( worldName, 1, 1,rootItem );

	m_treeModel.SetItemData( newItem, 0 );
	return newItem;

}

bool CToolModel::GetCurrentPath( CString& pPath ,bool isAbsolute)
{
	HTREEITEM selItem = GetCurrSelFoler();
	if (NULL == selItem)
	{
		return false;
	}
	if (isAbsolute)
	{
		pPath =  m_currRoot;
		pPath += _T('\\');
	}
	CString relativePath;
	HTREEITEM rootItem	= m_treeModel.GetRootItem();
	while (selItem != rootItem)
	{
		relativePath.Insert(0,'\\');
		relativePath.Insert(0,m_treeModel.GetItemText(selItem));
		selItem = m_treeModel.GetNextItem( selItem, TVGN_PARENT );
	}
	pPath += relativePath;
	return true;
}

bool CToolModel::GetCurrentName( CString& name, bool isAbsolute)
{
	if(!GetCurrentPath(name,isAbsolute))
		return false;
	HTREEITEM selItem	= m_treeModel.GetSelectedItem();
	name += m_treeModel.GetItemText(selItem);
	return true;
}

HTREEITEM CToolModel::GetCurrSelFoler()
{
	HTREEITEM selItem	= m_treeModel.GetSelectedItem();
	if (NULL == selItem)
	{
		return NULL;
	}
	uInt32 tileId	= m_treeModel.GetItemData( selItem );
	if (s_DIRECTORY != tileId)
	{
		selItem = m_treeModel.GetNextItem( selItem, TVGN_PARENT );
	}
	return selItem;
}




void CToolModel::OnLbnSelchangeListPickedModel()
{
	CToolObject* pToolObject = GetToolObject();
	if(NULL == pToolObject)
		return;

	assert(m_listPickedModel.GetCount() == pToolObject->m_selectingVisitor.m_pickResult.pickResultCount);
	for(int index = 0; index < m_listPickedModel.GetCount(); ++index)
	{
		bool bSeletcted = (m_listPickedModel.GetSel(index) > 0); 
		if(!pToolObject->m_selectingVisitor.SetSelectingModel(
			pToolObject->m_selectingVisitor.m_pickResult.pickResultInfo[index].resultId, bSeletcted))
		{
			AfxMessageBox(_T("设置选择目标失败！"));
			return;
		}
	}

	// 跟新位置信息
	if (!pToolObject->m_selectingVisitor.m_selectModels.empty())
		pToolObject->m_selectingVisitor.UpdateInfo((TObjectEditInfo *)pToolObject->m_selectingVisitor.m_selectModels.begin()->pModel);
	else
		pToolObject->m_selectingVisitor.UpdateInfo(NULL);
}

void CToolModel::UpdatePickedModelList( TPickResult& pickResult )
{
	m_listPickedModel.ResetContent();
	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	if (NULL == resMgr)
	{
		return;
	}
	for( sInt32 i=0; i<pickResult.pickResultCount; i++ ) 
	{
		TObjectInfo* objInfo	= pickResult.pickResultInfo[i].resultObjInfo;
		CString strName;
		CWorldRes* Res	= resMgr->GetStaticModelRefList()[objInfo->id];
		strName			= Res->GetName();
		m_listPickedModel.InsertString(-1, strName );
	}

	//m_listPickedModel.SetCurSel(0);
	//高亮显示当前被选择的models
	CToolObject* pToolObject = GetToolObject();
	if(NULL == pToolObject)
		return;
	for(CToolObject::TModels::const_iterator it = pToolObject->m_selectingVisitor.m_selectModels.begin();
		it != pToolObject->m_selectingVisitor.m_selectModels.end(); ++it)
	{
		for(int index = 0; index < m_listPickedModel.GetCount(); ++index)
		{
			if(it->id == pToolObject->m_selectingVisitor.m_pickResult.pickResultInfo[index].resultId)
			{
				m_listPickedModel.SetSel(index, TRUE);
				break;
			}
		}
	}

	// 设置水平滚动条
	{
		CString str;
		CSize   sz;
		int     dx=0;
		CDC*    pDC = m_listPickedModel.GetDC();
		for (int i=0;i < m_listPickedModel.GetCount();i++)
		{
			m_listPickedModel.GetText( i, str );
			sz = pDC->GetTextExtent(str);

			if (sz.cx > dx)
				dx = sz.cx;
		}
		m_listPickedModel.ReleaseDC(pDC);

		// Set the horizontal extent only if the current extent is not large enough.
		if (m_listPickedModel.GetHorizontalExtent() < dx)
		{
			m_listPickedModel.SetHorizontalExtent(dx);
			ASSERT(m_listPickedModel.GetHorizontalExtent() == dx);
		}
	}
}

CToolObject* CToolModel::GetToolObject()
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_OBJECT );
	return (CToolObject*)( toolManager->GetActiveTool() );
}
void CToolModel::OnBnClickedBtnModelChange()
{
	int nIndex = m_listPickedModel.GetCurSel();
	if(LB_ERR == nIndex)
		return;

	CString strValue;

	m_editChangeModelPath.GetWindowText( strValue );

	if (strValue.IsEmpty())
	{
		return;
	}
	//int npos = strValue.Find(_T(".nif"));
	//if (-1 == npos)
	//{
	//	npos = strValue.Find(_T(".kfm"));
	//}
	int npos = strValue.Find(_T(".mex"));
	if (-1 == npos || npos != strValue.GetLength() - 4)
	{
		return;
	}

	GetToolObject()->m_selectingVisitor.ReplaceModel(nIndex,strValue);

}

void CToolModel::RefreshPickedModelName( int nIndex,LPCTSTR strName )
{
	m_listPickedModel.DeleteString(nIndex);
	m_listPickedModel.InsertString(nIndex, strName );
	m_listPickedModel.SetCurSel(nIndex);
}


bool CToolModel::SelectNextModelInModelTree()
{
	HTREEITEM selItem	= m_treeModel.GetSelectedItem();
	HTREEITEM nextItem = m_treeModel.GetNextItem(selItem);
	uInt32 tileId	= m_treeModel.GetItemData( nextItem );
	if (s_DIRECTORY == tileId)//目录
		return false;
	return m_treeModel.SelectItem(nextItem);

}

bool CToolModel::SelectPreModelInModelTree()
{
	HTREEITEM selItem	= m_treeModel.GetSelectedItem();
	HTREEITEM preItem = m_treeModel.GetPrevItem(selItem);
	uInt32 tileId	= m_treeModel.GetItemData( preItem );
	if (s_DIRECTORY == tileId)//目录
		return false;
	return m_treeModel.SelectItem(preItem);
}


void CToolModel::OnPopmodelmove()
{
	GetToolObject()->m_transformingVisitor.SetTransformType(CToolObject::CTransformingVisitor::e_trans_move);
}

void CToolModel::OnPopmodelrotate()
{
	GetToolObject()->m_transformingVisitor.SetTransformType(CToolObject::CTransformingVisitor::e_trans_rotate);
}

void CToolModel::OnPopmodelscale()
{
	GetToolObject()->m_transformingVisitor.SetTransformType(CToolObject::CTransformingVisitor::e_trans_scale);
}
void CToolModel::OnChkLightmapCastShadow()
{
	CToolObject* pToolObject = GetToolObject();
	if( !pToolObject || pToolObject->m_selectingVisitor.m_selectModels.empty() )
		return;

	CToolObject::TModels::iterator it = pToolObject->m_selectingVisitor.m_selectModels.begin();
	for( ; it != pToolObject->m_selectingVisitor.m_selectModels.end(); ++it )
	{
		if( it->pModel )
			it->pModel->SetCastShadow((bool)m_checkCastShadow.GetCheck());
	}
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE );
}

void CToolModel::OnCbnSelchangeLightmapResolution()
{
	CToolObject* pToolObject = GetToolObject();
	if( !pToolObject || pToolObject->m_selectingVisitor.m_selectModels.empty() )
		return;

	CToolObject::TModels::iterator it = pToolObject->m_selectingVisitor.m_selectModels.begin();
	for( ; it != pToolObject->m_selectingVisitor.m_selectModels.end(); ++it )
	{
		if( it->pModel )
			it->pModel->SetLightMapScale((TObjectInfo::ELightMapScale)m_comboLightmapResolution.GetCurSel());
	}
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE );
}

void CToolModel::OnBnClickedBuildLightmapOneModel()
{
	CToolObject* pToolObject = GetToolObject();
	if( !pToolObject || pToolObject->m_selectingVisitor.m_selectModels.empty() )
		return;

	CWorldTile* pTile = CURRENTTILE;
	if( !pTile )
		return;
	CResEditMgr* resMgr = (CResEditMgr*)pTile->GetCResMgr();
	if( !resMgr )
		return;

	StaticMeshRayTracer xTracer(pTile, FALSE);
	xTracer.ReleaseData();
	int nObjCount = 0;
	int nTotalFaceCount = 0;

	CToolObject::TModels::iterator it = pToolObject->m_selectingVisitor.m_selectModels.begin();
	for( ; it != pToolObject->m_selectingVisitor.m_selectModels.end(); ++it )
	{
		TObjectInfo* pObj =	it->pModel;
		if( !pObj )
			continue;

		// 查找模型在哪几个chunk
		for( INT ChunkIndex = 0; ChunkIndex < pTile->GetChunkTotal(); ++ChunkIndex )
		{
			CWorldChunk* pWorldChunk = pTile->GetChunk(ChunkIndex);
			if( pWorldChunk->GetStaticModelList().size() == 0 )
				continue;

			int nModelNum = pWorldChunk->GetStaticModelList().size();

			// 查找chunk里模型
			for( INT ModelIndex = 0; ModelIndex < nModelNum; ++ModelIndex )
			{
				int nFaceCount = 0;
				sInt32 nModelId = pWorldChunk->GetStaticModelList()[ModelIndex];
				if( nModelId == pObj->id )
					nObjCount = xTracer.IlluminateOneObject(pObj, ChunkIndex, nFaceCount);	// 单独生成一个模型光照，第2个参数设true
				nTotalFaceCount += nFaceCount;
			}
		}
	}

	if( nObjCount == 0 )
		return;

	xTracer.PrepareData(nTotalFaceCount);

	// 旧lightmap贴图注销
	for( int i=0; i<pTile->GetLightMaps().size(); ++i )
	{
		GetEngine()->GetTextureManager()->UnRegisterTexture( pTile->GetLightMaps()[i]->GetTextureId() );
	}
	pTile->ClearLightMaps();

	//显示进度
	/*LightMapMeshProcessDlg processDlg;	
	processDlg.Create(IDD_LIGHTMAP_MESH_PROCESS, 0);
	CRect rect;
	processDlg.GetWindowRect(&rect);
	processDlg.SetWindowPos(0, 500, 500, rect.right - rect.left, rect.bottom - rect.top, 0);
	processDlg.UpdateWindow();
	processDlg.ShowWindow(SW_SHOW);*/

	// 射线处理每个受光模型
	//processDlg.m_process.SetRange(0, nObjCount);
	for( int i=0; i<nObjCount; ++i )
	{
		/*char text[256] = {0};
		processDlg.m_process.SetPos(i+1);
		sprintf_s(text, sizeof(text)-1, "创建%d/%d个模型光照信息", i+1, nObjCount);
		processDlg.m_static.SetWindowText(text);*/

		xTracer.RayTraceObject(i, SwGlobal::GetWorldPicker());
	}
	// 生成光照图
	for( int i=0; i<nObjCount; ++i )
	{
		//char text[256] = {0};
		//processDlg.m_process.SetPos(i+1);
		//sprintf_s(text, sizeof(text)-1, "保存%d/%d个模型光照图", i+1, nObjCount);
		//processDlg.m_static.SetWindowText(text);

		// 此处是生成模型的光照图, 即每个模型的ColorData
		xTracer.BuildObjectResource(i);
	}

	std::map<TObjectInfo*, TObjectInfo*> mapObjects;
	mapObjects.clear();

	for( INT ChunkIndex = 0; ChunkIndex < pTile->GetChunkTotal(); ++ChunkIndex )
	{
		CWorldChunk* pWorldChunk = pTile->GetChunk(ChunkIndex);
		if( pWorldChunk->GetStaticModelList().size() == 0 )
			continue;

		int nModelNum = pWorldChunk->GetStaticModelList().size();

		// 查找chunk里模型
		for( INT ModelIndex = 0; ModelIndex < nModelNum; ++ModelIndex )
		{
			sInt32 nModelId = pWorldChunk->GetStaticModelList()[ModelIndex];

			if( nModelId >= resMgr->GetStaticModelList().size() )
				continue;

			TObjectInfo* pObjInfo = resMgr->GetStaticModelList()[nModelId];
			if( !pObjInfo )
				continue;

			if( pObjInfo->GetStaticMeshIntanceCount() == 0 )
				continue;

			std::map<TObjectInfo*, TObjectInfo*>::iterator iter = mapObjects.find(pObjInfo);
			if( iter == mapObjects.end() )
			{
				mapObjects.insert(std::map<TObjectInfo*, TObjectInfo*>::value_type(pObjInfo, pObjInfo));
				xTracer.AllocateObjectLightMap(pObjInfo);
			}
		}
	}

	// 释放临时数据
	xTracer.ReleaseData();

	// 保存全局光照贴图
	theApp.GetWorldEditor()->SaveLightmapTexture(pTile, NULL/*&processDlg*/);

	//processDlg.ShowWindow(SW_HIDE);

	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( pTile );

	if( pTile->GetLightMapNum() )
		pTile->RefreshLightmapTexId();
}

void CToolModel::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if ((nSBCode == SB_THUMBPOSITION))
	{
		if (pScrollBar != NULL)
		{
		switch (pScrollBar->GetDlgCtrlID())
		{
		case IDC_EDT_WORLD_X_SPIN:
		case IDC_EDT_WORLD_Y_SPIN:
		case IDC_EDT_WORLD_Z_SPIN:
			UpdateWorldPos();
			break;
		case IDC_EDT_OFFSET_POS_X_SPIN:
		case IDC_EDT_OFFSET_POS_Y_SPIN:
		case IDC_EDT_OFFSET_POS_Z_SPIN:
			UpdateOff(nPos,pScrollBar);
			break;
		case IDC_EDT_OFFSET_ROT_X_SPIN:
		case IDC_EDT_OFFSET_ROT_Y_SPIN:
		case IDC_EDT_OFFSET_ROT_Z_SPIN:
			UpdateRot();
			break;
		case IDC_EDT_OFFSET_SCL_XYZ_SPIN:
			UpdateScl();
			break;
		default:
			break;
			}
		}
	}

	VerticalScrollHandler(nSBCode, nPos);
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CToolModel::OnSize(UINT nType, int cx, int cy)
{
	ScrollableDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CRect rcClient;
	GetClientRect(&rcClient);
	Scroll_Setup(820, rcClient.Height());
}