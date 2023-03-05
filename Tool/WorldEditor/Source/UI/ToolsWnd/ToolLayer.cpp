/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolLayer.cpp
* Date: 	05/31/2007
* Desc:
*
*******************************************************************************/
#include "stdAfx.h"
#include "Resource/Resource.h"
#include "Edit/ToolLayer.h"
#include "Edit/ToolManager.h"
#include "ui/Custom/TexturePreviewWnd.h"
#include "Ndl/NdlWorldEditor.h"
#include "EditRes/NdlEditRes.h"
#include "ToolLayer.h"

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CToolLayerDlg, CDialog)

CToolLayerDlg::CToolLayerDlg(CToolLayerDlg* pParent)
: CDialog(CToolLayerDlg::IDD, pParent)
{
	m_iLayerMode	= 1;	
	m_isFillUI		= false;
	m_nspecialOptLevel		= 0;
}

CToolLayerDlg::~CToolLayerDlg()
{

}

void CToolLayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolLayerDlg)
	DDX_CBIndex(pDX, IDC_COMBO_LAYER_MODE, m_iLayerMode);
	DDX_Control(pDX, IDC_SPIN_ALPHA, m_spinAlpha);
	DDX_Control(pDX, IDC_EDIT_ALPHA, m_editAlpha);
	DDX_Control(pDX, IDC_SPIN_FLOW, m_spinFlow);
	DDX_Control(pDX, IDC_EDIT_FLOW, m_editFlow);

	DDX_Control(pDX, IDC_COMBO_LAYER_BRUSH, m_brushList);
	DDX_Control(pDX, IDC_COMBO_LAYER_TEXTURE, m_textureList);
	DDX_Control(pDX, IDC_COMBO_LAYER_MODE, m_modeList);
	DDX_Control(pDX, IDC_CHK_LOCKLAYER, m_chkLockLayer);
	DDX_Control(pDX, IDC_BTN_VERTEX_COLOR, m_cpVertexColor);
	DDX_XTColorPicker(pDX, IDC_BTN_VERTEX_COLOR, m_vertexColor);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CHECK_TILE_CULLING, m_chk_Culled);
	DDX_Control(pDX, IDC_EDIT_TEXTURE_X0, m_edit_textureX0);
	DDX_Control(pDX, IDC_EDIT_TEXTURE_Y0, m_edit_textureY0);
	DDX_Control(pDX, IDC_EDIT_TEXTURE_SCALEX0, m_edit_textureScaleX0);
	DDX_Control(pDX, IDC_EDIT_TEXTURE_SCALEY0, m_edit_textureScaleY0);
	DDX_Control(pDX, IDC_SPIN_TEXTURE_X0, m_spin_TextureX0);
	DDX_Control(pDX, IDC_SPIN_TEXTURE_Y0, m_spin_TextureY0);
	DDX_Control(pDX, IDC_SPIN_TEXTURE_SCALEX0, m_spin_TextureScaleX0);
	DDX_Control(pDX, IDC_SPIN_TEXTURE_SCALEY0, m_spin_TextureScaleY0);
	DDX_Control(pDX, IDC_CHECK_ALIGN, m_chk_Alignment);
	DDX_Control(pDX, IDC_EDIT_TEXTURE_ROTATION, m_edit_TextureRotation);
	DDX_Control(pDX, IDC_SPIN_TEXTURE_ROTATION, m_spin_TextureRotation);

	DDX_Control(pDX, IDC_CK_USE_WINTAB_4_ALPHA, m_UseWinTabsPressCheckBox);
	// 	DDX_Control(pDX, IDC_CHECK_TILE_CULLING2, m_chkButtonPaintShadow);
}

BEGIN_MESSAGE_MAP(CToolLayerDlg, CDialog)
	//{{AFX_MSG_MAP(CToolLayerDlg)
	ON_EN_KILLFOCUS(IDC_EDIT_ALPHA, OnKillfocusEdtAlpha)
	ON_EN_KILLFOCUS(IDC_EDIT_FLOW, OnKillfocusCBFlow)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_DEL_LAYER_0, IDC_BTN_DEL_LAYER_3, OnBtnDeleteLayer)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SET_LAYER_0, IDC_BTN_SET_LAYER_3, OnBtnSetLayer )
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GET_LAYER_0, IDC_BTN_GET_LAYER_3, OnBtnGetLayer )
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UP_LAYER_0, IDC_BTN_UP_LAYER_2, OnBtnUpLayer )
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_DOWN_LAYER_1, IDC_BTN_DOWN_LAYER_3, OnBtnDownLayer )
	ON_LBN_SELCHANGE(IDC_COMBO_LAYER_BRUSH, OnBrushChange)
	ON_LBN_SELCHANGE(IDC_COMBO_LAYER_TEXTURE, OnTextureChange)
	ON_LBN_SELCHANGE(IDC_COMBO_LAYER_MODE, OnModeChange)
	ON_CPN_XT_SELENDOK(IDC_BTN_VERTEX_COLOR, OnSelVertexColor)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_TILE_CULLING, &CToolLayerDlg::OnBnClickedCheckTileCulling)
	ON_BN_CLICKED(IDC_CHECK_ALIGN, &CToolLayerDlg::OnBnClickedAlign)
	ON_EN_KILLFOCUS(IDC_EDIT_TEXTURE_X0, &CToolLayerDlg::OnEnKillfocusEditTextureX0)
	ON_EN_KILLFOCUS(IDC_EDIT_TEXTURE_Y0, &CToolLayerDlg::OnEnKillfocusEditTextureY0)
	ON_EN_KILLFOCUS(IDC_EDIT_TEXTURE_SCALEX0, &CToolLayerDlg::OnEnKillfocusEditTextureScalex0)
	ON_EN_KILLFOCUS(IDC_EDIT_TEXTURE_SCALEY0, &CToolLayerDlg::OnEnKillfocusEditTextureScaley0)
	ON_EN_KILLFOCUS(IDC_EDIT_TEXTURE_ROTATION, &CToolLayerDlg::OnEnKillfocusEditTextureRotation)
	ON_BN_CLICKED(IDC_RADIO_Level3, &CToolLayerDlg::OnBnClickedRadioLevel3)
	ON_BN_CLICKED(IDC_RADIO_Level2, &CToolLayerDlg::OnBnClickedRadioLevel2)
	ON_BN_CLICKED(IDC_RADIO_Level1, &CToolLayerDlg::OnBnClickedRadioLevel1)
	ON_BN_CLICKED(IDC_RADIO_Level0, &CToolLayerDlg::OnBnClickedRadioLevel0)
	ON_BN_CLICKED(IDC_BTN_REFRESH_TEXTURE, &CToolLayerDlg::OnBnClickedBtnRefreshTexture)
	// 	ON_BN_CLICKED(IDC_CHECK_PAINT_SHADOW, &CToolLayerDlg::OnBnClickedCheckPaintShadow)
	ON_BN_CLICKED(IDC_BUTTON_SELTEXTURE, &CToolLayerDlg::OnBnClickedButtonSeltexture)
	ON_BN_CLICKED(IDC_CK_USE_WINTAB_4_ALPHA, &CToolLayerDlg::OnBnClickedCkUseWintab4Alpha)

	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()

BOOL CToolLayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_spinAlpha.SetBuddy( &m_editAlpha );
	m_spinAlpha.SetRange( 0x0, 0xFF );  
	m_spinAlpha.SetBase( 16 );  
	m_spinAlpha.SetPos( 0xFF );

	m_spinFlow.SetBuddy( &m_editFlow);
	m_spinFlow.SetRange( 0x0, 100 );  
	m_spinFlow.SetPos( 100 );

	m_spin_TextureX0.SetBuddy( &m_edit_textureX0 );
	m_spin_TextureX0.SetRange( 0x0, TTextureInfo::MAXOFFSET - 1 );  
	m_spin_TextureX0.SetPos( 0x0 );

	m_spin_TextureY0.SetBuddy( &m_edit_textureY0 );
	m_spin_TextureY0.SetRange( 0x0, TTextureInfo::MAXOFFSET - 1 );  
	m_spin_TextureY0.SetPos( 0x0 );

	m_spin_TextureScaleX0.SetBuddy( &m_edit_textureScaleX0 );
	m_spin_TextureScaleX0.SetRange( 0x1, 0xFF );  
	m_spin_TextureScaleX0.SetPos( 10 );

	m_spin_TextureScaleY0.SetBuddy( &m_edit_textureScaleY0 );
	m_spin_TextureScaleY0.SetRange( 0x1, 0xFF );  
	m_spin_TextureScaleY0.SetPos( 10 );

	m_spin_TextureRotation.SetBuddy( &m_edit_TextureRotation );
	m_spin_TextureRotation.SetRange( 0, 359 );  
	m_spin_TextureRotation.SetPos( 0 );

	m_texturePreview.Init( IDC_PREVIEW_LAYER, this );
	m_textureLayer[0].Init( IDC_PREVIEW_LAYER_0, this );
	m_textureLayer[1].Init( IDC_PREVIEW_LAYER_1, this );
	m_textureLayer[2].Init( IDC_PREVIEW_LAYER_2, this );
	m_textureLayer[3].Init( IDC_PREVIEW_LAYER_3, this );

	m_cpVertexColor.SetDefaultColor( RGB(0xaa,0xaa,0xaa) );
	m_cpVertexColor.ShowText(true);
	m_vertexColor		= RGB(0xaa,0xaa,0xaa);
	CheckDlgButton(IDC_RADIO_Level0,1);

	m_UseWinTabsPressCheckBox.SetCheck(BST_UNCHECKED);
	m_nLastAlpha = -1;

	//	PaintModeChange(znLBM_Add);	


	UpdateData(FALSE);

	return TRUE;
}

bool CToolLayerDlg::UpdateSetting( bool isModify )
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_LAYER );
	CToolLayer* toolLayer = (CToolLayer*)( toolManager->GetActiveTool() );
	Assert( NULL != toolLayer );

	if( !m_isFillUI ) {
		toolLayer->Bind( this );
		CString strName;
		m_brushList.ResetContent();
		for( size_t i=0; i<toolLayer->m_brushList.size(); i++ ) {
			const TLayerBrush* brush = toolLayer->m_brushList[i];
			strName.Format( _T("%hs(%d)"), brush->brushName, brush->brushSize );
			m_brushList.AddString( strName );
		}
		// 		if( toolLayer->m_brushList.size() > 1 )
		// 			toolLayer->m_brushId	= 0;

		m_textureList.ResetContent();
		for( size_t i=0; i<toolLayer->m_texInfoList.size(); i++ ) {
			TNameInfo* p = toolLayer->m_texInfoList[i];
			strName.Format( _T("%hs"), p->name );
			m_textureList.AddString( strName );
		}
		if( toolLayer->m_texInfoList.size() > 1 )
			toolLayer->m_textureId	= 0;

		m_isFillUI = true;
	}
	BrushChanged(toolLayer->m_brushId);

	m_textureList.SetCurSel( toolLayer->m_textureId );
	if( -1 != toolLayer->m_textureId ) {
		TNameInfo* nameInfo = toolLayer->m_texInfoList[toolLayer->m_textureId];
		Assert( NULL != nameInfo );
		UpdatePreview( nameInfo->path, nameInfo->name, nameInfo->format );
	}

	PaintModeChange(toolLayer->m_paintMode);
	OnModeChange();

	UpdateData(FALSE);

	return true;
}

void CToolLayerDlg::SetActive( bool isModify )
{
	UpdateSetting( isModify );
}

void CToolLayerDlg::RefreshLayer()
{
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolLayer* layer		= (CToolLayer*)toolMgr->GetTool( TOOL_LAYER );

	CWorldChunk* worldChunk	= layer->m_selWorldChunk;
	CResEditMgr* resMgr		= layer->m_selResMgr;

	if( NULL != worldChunk && NULL!=resMgr ) {
		CNdlTextureRes* layer[4];
		if( theApp.GetWorldEditor()->GetChunkLayerTextureInfo( worldChunk, resMgr, &layer[0], &layer[1], &layer[2], &layer[3] ) ) 
		{
			RefreshSpecialInfo(worldChunk);

			for( sInt32 i=0; i<4; i++ ) {
				if( NULL != layer[i] ) {
					const char* path = layer[i]->GetName();
					const char* strTga = strstr( path, ".tga" );
					const char* strPng = strstr( path, ".png" );
					const char* strDDS = strstr( path, ".dds" );

					ENUM_CXIMAGE_FORMATS texFormat;
					if( NULL !=strTga ) {
						texFormat = CXIMAGE_FORMAT_TGA;
					}
					else if( NULL!=strPng )	{
						texFormat = CXIMAGE_FORMAT_PNG;
					}
					else if( NULL!=strDDS ) {
						texFormat = CXIMAGE_FORMAT_DDS;
					}
					else {
						continue;
					}

					m_textureLayer[i].SetTextureName( path, texFormat );
				} 
				else {
					m_textureLayer[i].SetTextureName( NULL );
				}
			}
		}
	}
	m_chk_Culled.SetCheck(worldChunk->IsCulled());
	// 	m_chkButtonPaintShadow.SetCheck(layer->m_isPaintShadow);
}

void CToolLayerDlg::UpdateLock( bool isLock )
{
	m_chkLockLayer.SetCheck( isLock?1:0 );
	m_chkLockLayer.SetWindowText( isLock?_T("已锁定"):_T("未锁定") );
}

void CToolLayerDlg::OnKillfocusEdtAlpha()
{
	// 	UpdateData();
	// 	
	// 	CString strAlpha;
	// 	m_editAlpha.GetWindowText( strAlpha );
	// 	uInt8 alpha	= _tstoi( strAlpha );
	// 	alpha			= alpha & 0xF0;
	// 	alpha			= alpha|(alpha>>4);
	// 	ShowAlphaText(alpha);
	// 
	// 	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	// 	CToolManager* toolMgr	= view->GetToolManager();
	// 	CToolLayer* layer		= (CToolLayer*)toolMgr->GetTool( TOOL_LAYER );
	// 	layer->m_alpha			= alpha;
	// 	
	// 	UpdateData( FALSE );	
}

void CToolLayerDlg::DeleteLayer( sInt32 layerId )
{
	CString strPmt;
	strPmt.Format( _T("是否删除第[%d]层？"), layerId );
	int sel = ::AfxMessageBox( strPmt, MB_YESNO );
	if( sel == IDYES )		// 保存
	{
		CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CToolManager* toolMgr	= view->GetToolManager();
		CToolLayer* layer		= (CToolLayer*)toolMgr->GetTool( TOOL_LAYER );

		CWorldChunk* worldChunk	= layer->m_selWorldChunk;
		CResEditMgr* resMgr		= layer->m_selResMgr;

		if( theApp.GetWorldEditor()->DelChunkLayer( worldChunk, resMgr, layerId ) )
			RefreshLayer();
	}
}

void CToolLayerDlg::OnBtnDeleteLayer( UINT nID )
{
	sInt32 id = nID - IDC_BTN_DEL_LAYER_0;
	DeleteLayer( id );
}

void CToolLayerDlg::OnBtnGetLayer( UINT nID )
{
	sInt32 id = nID - IDC_BTN_GET_LAYER_0;

	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolLayer* toolLayer	= (CToolLayer*)toolMgr->GetTool( TOOL_LAYER );

	CWorldChunk* worldChunk	= toolLayer->m_selWorldChunk;
	CResEditMgr* resMgr		= toolLayer->m_selResMgr;
	if( NULL != worldChunk && NULL!=resMgr ) {
		CNdlTextureRes* layer[4];
		if( theApp.GetWorldEditor()->GetChunkLayerTextureInfo( worldChunk, resMgr, &layer[0], &layer[1], &layer[2], &layer[3] ) ) {
			if( NULL != layer[id] ) {
				layer[id]->GetName();
				sInt32 sel = -1;
				char path[MAX_PATH];
				for( size_t i=0; i<toolLayer->m_texInfoList.size(); i++ ) 
				{
					TNameInfo* p = toolLayer->m_texInfoList[i];
					memset( path, 0, sizeof(char) );
					sprintf_s( path, "%s\\%s", p->path, p->name );
					CStringA charName = layer[id]->GetName();
					if (0 == charName.Find(".\\"))
					{
						charName = charName.Mid(2);//romove ".\"
					}
					if( charName == path ) 
					{
						m_textureList.SetCurSel( i );
						toolLayer->m_textureId = i;
						UpdatePreview( p->path, p->name, p->format );
						break;
					}
				}
			}
		}
	}

}

void CToolLayerDlg::OnBtnSetLayer( UINT nID )
{
	sInt32 id = nID - IDC_BTN_SET_LAYER_0;

	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolLayer* toolLayer	= (CToolLayer*)toolMgr->GetTool( TOOL_LAYER );

	CWorldChunk* worldChunk	= toolLayer->m_selWorldChunk;
	CResEditMgr* resMgr		= toolLayer->m_selResMgr;
	if(toolLayer->m_multiSel)
	{
		CString strPmt;
		strPmt.Format( _T("是否替换第[%d]层纹理为当前选中纹理？"), id );
		int sel = ::AfxMessageBox( strPmt, MB_YESNO );
		if( sel == IDYES ) {
			TNameInfo* nameInfo = toolLayer->GetTexNameInfoFromId( toolLayer->m_textureId );
			char path[MAX_PATH];
			sprintf_s( path, "%s\\%s", nameInfo->path, nameInfo->name );

			for(int i=0;i<toolLayer->m_vecWorldChunk.size();++i)
			{
				CWorldChunk* chunk = toolLayer->m_vecWorldChunk[i];
				theApp.GetWorldEditor()->ReplaceChunkTexture( chunk, resMgr, id, path ); 
			}
		}

	}
	else
	{
		if( NULL != worldChunk && NULL!=resMgr ) {

			// 		if (GetKeyState(VK_SHIFT) && GetKeyState(VK_CONTROL))
			// 		{
			// 			CString strPmt;
			// 			strPmt.Format( _T("是否替换本地图所有此纹理为当前选中纹理？"), id );
			// 			int sel = ::AfxMessageBox( strPmt, MB_YESNO );
			// 			if( sel == IDYES ) {
			// 				TNameInfo* nameInfo = toolLayer->GetTexNameInfoFromId( toolLayer->m_textureId );
			// 				char path[MAX_PATH];
			// 				sprintf_s( path, "%s\\%s", nameInfo->path, nameInfo->name );
			// 				theApp.GetWorldEditor()->ReplaceTexture( resMgr, worldChunk->GetTexture(id) , path ); 
			// 			}
			// 		}
			// 		else
			{
				CString strPmt;
				strPmt.Format( _T("是否替换第[%d]层纹理为当前选中纹理？"), id );
				int sel = ::AfxMessageBox( strPmt, MB_YESNO );
				if( sel == IDYES ) {
					TNameInfo* nameInfo = toolLayer->GetTexNameInfoFromId( toolLayer->m_textureId );
					char path[MAX_PATH];
					sprintf_s( path, "%s\\%s", nameInfo->path, nameInfo->name );
					theApp.GetWorldEditor()->ReplaceChunkTexture( worldChunk, resMgr, id, path ); 
				}

			}
		}
	}

}

void CToolLayerDlg::OnBtnUpLayer( UINT nID )
{
	sInt32 layerId = nID - IDC_BTN_UP_LAYER_0;

	CString strPmt;
	strPmt.Format( _T("是否提升第[%d]层？"), layerId );
	int sel = ::AfxMessageBox( strPmt, MB_YESNO );
	if( sel == IDYES )		// 保存
	{
		CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CToolManager* toolMgr	= view->GetToolManager();
		CToolLayer* layer		= (CToolLayer*)toolMgr->GetTool( TOOL_LAYER );

		CWorldChunk* worldChunk	= layer->m_selWorldChunk;
		CResEditMgr* resMgr		= layer->m_selResMgr;

		if( theApp.GetWorldEditor()->UpChunkLayer( worldChunk, resMgr, layerId ) )
			RefreshLayer();
	}
}

void CToolLayerDlg::OnBtnDownLayer( UINT nID ) 
{
	sInt32 layerId = nID - IDC_BTN_DOWN_LAYER_1 + 1;

	CString strPmt;
	strPmt.Format( _T("是否下降第[%d]层？"), layerId );
	int sel = ::AfxMessageBox( strPmt, MB_YESNO );
	if( sel == IDYES )		// 保存
	{
		CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CToolManager* toolMgr	= view->GetToolManager();
		CToolLayer* layer		= (CToolLayer*)toolMgr->GetTool( TOOL_LAYER );

		CWorldChunk* worldChunk	= layer->m_selWorldChunk;
		CResEditMgr* resMgr		= layer->m_selResMgr;

		if( theApp.GetWorldEditor()->DownChunkLayer( worldChunk, resMgr, layerId ) )
			RefreshLayer();
	}
}

void CToolLayerDlg::OnBrushChange()
{
	sInt32 sel = m_brushList.GetCurSel();
	if( CB_ERR != sel ) {
		CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CToolManager* toolMgr	= view->GetToolManager();
		CToolLayer* layer		= (CToolLayer*)toolMgr->GetTool( TOOL_LAYER );
		if( sel < layer->m_brushList.size() ) {
			layer->m_brushId = sel;
		}
	}
}

void CToolLayerDlg::OnTextureChange()
{
	sInt32 sel = m_textureList.GetCurSel();
	if( CB_ERR != sel ) {
		CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		CToolManager* toolMgr	= view->GetToolManager();
		CToolLayer* layer		= (CToolLayer*)toolMgr->GetTool( TOOL_LAYER );
		if( sel < layer->m_texInfoList.size() ) {
			TNameInfo* nameInfo		= layer->m_texInfoList[sel];
			Assert( NULL != nameInfo ); 
			layer->m_textureId = sel;
			UpdatePreview( nameInfo->path, nameInfo->name, nameInfo->format );
		}
	}
}
void CToolLayerDlg::OnBnClickedButtonSeltexture()
{
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolLayer* layer		= (CToolLayer*)toolMgr->GetTool( TOOL_LAYER );

	CFileDialog fileDlg(true,"打开贴图","",NULL,"DDS (*.dds)|*.dds");

	if( IDOK == fileDlg.DoModal() )
	{
		string path = fileDlg.GetPathName();
		string name = fileDlg.GetFileName();

		TNameInfo* nameInfo;
		for(int i=0;i<layer->m_texInfoList.size();++i)
		{
			nameInfo = layer->m_texInfoList[i];
			if(nameInfo->name == name )
			{
				m_textureList.SetCurSel(i);
				layer->m_textureId = i;
				UpdatePreview( nameInfo->path, nameInfo->name, nameInfo->format );
			}
		}
	}
}

void CToolLayerDlg::OnModeChange()
{
	sInt32 sel = m_modeList.GetCurSel();
	if( CB_ERR != sel ) 
	{
		CToolLayer*  layer = GetToolLayer();
		if( sel == znLBM_Shadow || sel == znLBM_InvVertexCorlor) 
		{	
			// 阴影
			EnableAlphaCtrl( FALSE );
			EnableColorSelect(FALSE);
		}
		else if (sel == znLBM_VertexCorlor)
		{
			EnableAlphaCtrl( FALSE );
			EnableColorSelect(TRUE);
		}
		else 
		{
			EnableAlphaCtrl( TRUE );
			EnableColorSelect(FALSE);
		}
		layer->m_paintMode		= sel;
	}	
}

void CToolLayerDlg::EnableAlphaCtrl( BOOL isEnable )
{
	m_textureList.EnableWindow( isEnable );
	m_editAlpha.EnableWindow( true );
	m_spinAlpha.EnableWindow( true );
}

void CToolLayerDlg::UpdateLayer()
{

}

void CToolLayerDlg::UpdatePreview( const char* path, const char* name, sInt32 format )
{
	m_texturePreview.SetTexture( path, name, (ENUM_CXIMAGE_FORMATS)format );
	CString strPmt;
	strPmt	= path;
	strPmt	+= _T("\\");
	strPmt	+= name;
	GetDlgItem( IDC_STATIC_NAME_PROMPT )->SetWindowText( strPmt );

	UpdateData( FALSE );
}
void CToolLayerDlg::OnSelVertexColor()
{
	UpdateData();

	ConvertRGB2NiColor( m_vertexColor, GetToolLayer()->m_NiColor );

}

void CToolLayerDlg::EnableColorSelect( BOOL isEnable /*= TRUE */ )
{
	m_cpVertexColor.EnableWindow(isEnable);
	m_spinFlow.EnableWindow(isEnable);
	m_editFlow.EnableWindow(isEnable);

}

CToolLayer* CToolLayerDlg::GetToolLayer()
{
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	return (CToolLayer*)toolMgr->GetTool( TOOL_LAYER );
}

void CToolLayerDlg::OnKillfocusCBFlow()
{

	UpdateData();

	CString strFlow;
	m_editFlow.GetWindowText( strFlow );
	sInt32 flow	= ZnMin<sInt32>(_tstoi( strFlow ),100);

	m_spinFlow.SetPos( flow );

	GetToolLayer()->m_flow			= flow;

	UpdateData( FALSE );	
}

void CToolLayerDlg::OnBnClickedCheckTileCulling()
{
	CToolLayer*toolLayer = GetToolLayer();

	CWorldChunk* worldChunk	= toolLayer->m_selWorldChunk;
	CResEditMgr* resMgr		= toolLayer->m_selResMgr;
	worldChunk->SetCulled(BST_CHECKED == m_chk_Culled.GetCheck());

	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);

}

void CToolLayerDlg::OnEnKillfocusEditTextureX0()
{
	CString strValue;
	m_edit_textureX0.GetWindowText( strValue );
	uInt8 temp	= _tstoi( strValue );
	m_spin_TextureX0.SetPos( temp );
	strValue.Format( _T("%d"), temp );
	m_edit_textureX0.SetWindowText( strValue );

	CToolLayer* layer		= GetToolLayer();
	if (!layer->m_selWorldChunk)
	{
		return;
	}
	TTextureInfo& pInfo = layer->m_selWorldChunk->GetTexInfo(m_nspecialOptLevel);
	if (pInfo.IsAlign())
	{
		return;
	}
	pInfo.m_nX = temp;
	layer->m_selResMgr->RefreshSpecialChunkLayer(layer->m_selWorldChunk,m_nspecialOptLevel);
	UpdateData( FALSE );	
}

void CToolLayerDlg::OnEnKillfocusEditTextureY0()
{
	CString strValue;
	m_edit_textureY0.GetWindowText( strValue );
	uInt8 temp	= _tstoi( strValue );
	m_spin_TextureY0.SetPos( temp );
	strValue.Format( _T("%d"), temp );
	m_edit_textureY0.SetWindowText( strValue );

	CToolLayer* layer		= GetToolLayer();
	if (!layer->m_selWorldChunk)
	{
		return;
	}
	TTextureInfo& pInfo = layer->m_selWorldChunk->GetTexInfo(m_nspecialOptLevel);
	if (pInfo.IsAlign())
	{
		return;
	}
	pInfo.m_nY = temp;
	layer->m_selResMgr->RefreshSpecialChunkLayer(layer->m_selWorldChunk,m_nspecialOptLevel);
	UpdateData( FALSE );	
}

void CToolLayerDlg::OnEnKillfocusEditTextureScalex0()
{
	CString strValue;
	m_edit_textureScaleX0.GetWindowText( strValue );
	uInt8 temp	= _tstoi( strValue );
	m_spin_TextureScaleX0.SetPos( temp );
	strValue.Format( _T("%d"), temp );
	m_edit_textureScaleX0.SetWindowText( strValue );

	CToolLayer* layer		= GetToolLayer();
	if (!layer->m_selWorldChunk)
	{
		return;
	}
	TTextureInfo& pInfo = layer->m_selWorldChunk->GetTexInfo(m_nspecialOptLevel);
	if (pInfo.IsAlign())
	{
		return;
	}
	pInfo.m_ScaleX = temp;
	layer->m_selResMgr->RefreshSpecialChunkLayer(layer->m_selWorldChunk,m_nspecialOptLevel);
	UpdateData( FALSE );	
}

void CToolLayerDlg::OnEnKillfocusEditTextureScaley0()
{
	CString strValue;
	m_edit_textureScaleY0.GetWindowText( strValue );
	uInt8 temp	= _tstoi( strValue );
	m_spin_TextureScaleY0.SetPos( temp );
	strValue.Format( _T("%d"), temp );
	m_edit_textureScaleY0.SetWindowText( strValue );

	CToolLayer* layer		= GetToolLayer();
	if (!layer->m_selWorldChunk)
	{
		return;
	}
	TTextureInfo& pInfo = layer->m_selWorldChunk->GetTexInfo(m_nspecialOptLevel);
	if (pInfo.IsAlign())
	{
		return;
	}
	pInfo.m_ScaleY = temp;
	layer->m_selResMgr->RefreshSpecialChunkLayer(layer->m_selWorldChunk,m_nspecialOptLevel);
	UpdateData( FALSE );	
}

void CToolLayerDlg::OnBnClickedAlign()
{
	CToolLayer*toolLayer = GetToolLayer();

	CWorldChunk* worldChunk	= toolLayer->m_selWorldChunk;
	CResEditMgr* resMgr		= toolLayer->m_selResMgr;
	bool bchecked = (BST_CHECKED == m_chk_Alignment.GetCheck());
	if (worldChunk && resMgr->SetSpecialLayerAlign(worldChunk,bchecked,m_nspecialOptLevel))
	{
		if (!bchecked)
		{
			RefreshSpecialInfo(worldChunk);
		}
	}
	else
	{
		if (bchecked)
		{
			::AfxMessageBox( _T("不能合法的向左或下看齐大贴图!") );
			m_chk_Alignment.SetCheck(false);
			UpdateData( FALSE );	
		}
	}

	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( CURRENTTILE);

}

void CToolLayerDlg::RefreshSpecialInfo( CWorldChunk* worldChunk )
{
	TTextureInfo& pInfo = worldChunk->GetTexInfo(m_nspecialOptLevel);
	CString strValue;
	m_spin_TextureX0.SetPos( pInfo.m_nX );
	strValue.Format( _T("%d"), pInfo.m_nX );
	m_edit_textureX0.SetWindowText( strValue );

	m_spin_TextureY0.SetPos( pInfo.m_nY );
	strValue.Format( _T("%d"), pInfo.m_nY );
	m_edit_textureY0.SetWindowText( strValue );

	m_spin_TextureScaleX0.SetPos( pInfo.m_ScaleX );
	strValue.Format( _T("%d"), pInfo.m_ScaleX );
	m_edit_textureScaleX0.SetWindowText( strValue );

	m_spin_TextureScaleY0.SetPos( pInfo.m_ScaleY );
	strValue.Format( _T("%d"), pInfo.m_ScaleY );
	m_edit_textureScaleY0.SetWindowText( strValue );

	m_spin_TextureRotation.SetPos( ZnFloat2Int(pInfo.m_angle) );
	strValue.Format( _T("%6.2f"), pInfo.m_angle );
	m_edit_TextureRotation.SetWindowText( strValue );

	m_chk_Alignment.SetCheck(pInfo.IsAlign());

}
void CToolLayerDlg::OnEnKillfocusEditTextureRotation()
{
	CString strValue;
	m_edit_TextureRotation.GetWindowText( strValue );
	flt32 temp	= _tstof( strValue );
	temp = ZnClamp<flt32>(temp,0.f,360.f);
	m_spin_TextureRotation.SetPos( ZnFloat2Int(temp) );
	strValue.Format( _T("%6.2f"), temp );
	m_edit_TextureRotation.SetWindowText( strValue );

	CToolLayer* layer		= GetToolLayer();
	if (!layer->m_selWorldChunk)
	{
		return;
	}
	TTextureInfo& pInfo = layer->m_selWorldChunk->GetTexInfo(m_nspecialOptLevel);
	if (pInfo.IsAlign())
	{
		return;
	}
	pInfo.m_angle = temp;
	layer->m_selResMgr->RefreshSpecialChunkLayer(layer->m_selWorldChunk,m_nspecialOptLevel);
	UpdateData( FALSE );	
}

void CToolLayerDlg::ShowAlphaText( uInt8 alpha )
{
	CString strAlpha;
	// 	m_spinAlpha.SetPos( alpha&0x0F );
	strAlpha.Format( _T("%x"), alpha );
	m_editAlpha.SetWindowText( strAlpha );

	// 更新数据到控件上
	UpdateData(FALSE);
}

void CToolLayerDlg::PaintModeChange( sInt32 paintMode )
{
	m_modeList.SetCurSel( paintMode );
}

void CToolLayerDlg::BrushChanged( int nSelect )
{
	m_brushList.SetCurSel( nSelect );
}

void CToolLayerDlg::FlowChanged( uInt32 flow )
{
	CString strFlow;
	strFlow.Format( _T("%d"), flow );
	m_editFlow.SetWindowText( strFlow );
}

BOOL CToolLayerDlg::IsUseWinTabPressAsAlpha()
{
	return m_UseWinTabsPressCheckBox.GetCheck() == BST_CHECKED;
}

void CToolLayerDlg::OnBnClickedRadioLevel3()
{
	CToolLayer* layer		= GetToolLayer();
	CWorldChunk* worldChunk = layer->m_selWorldChunk;
	if (!worldChunk)
	{
		return;
	}
	if (worldChunk->GetLayerCount() == 4)
	{
		m_nspecialOptLevel = 3;
		RefreshSpecialInfo(worldChunk);
	}
	RefreshSpecialRadioBtn();

}

void CToolLayerDlg::OnBnClickedRadioLevel2()
{
	CToolLayer* layer		= GetToolLayer();
	CWorldChunk* worldChunk = layer->m_selWorldChunk;
	if (!worldChunk)
	{
		return;
	}
	if (worldChunk->GetLayerCount() >= 3)
	{
		m_nspecialOptLevel = 2;
		RefreshSpecialInfo(worldChunk);
	}
	RefreshSpecialRadioBtn();
}

void CToolLayerDlg::OnBnClickedRadioLevel1()
{
	CToolLayer* layer		= GetToolLayer();
	CWorldChunk* worldChunk = layer->m_selWorldChunk;
	if (!worldChunk)
	{
		return;
	}
	if (worldChunk->GetLayerCount() >= 2)
	{
		m_nspecialOptLevel = 1;
		RefreshSpecialInfo(worldChunk);
	}
	RefreshSpecialRadioBtn();
}

void CToolLayerDlg::OnBnClickedRadioLevel0()
{
	CToolLayer* layer		= GetToolLayer();
	CWorldChunk* worldChunk = layer->m_selWorldChunk;
	if (!worldChunk)
	{
		return;
	}
	m_nspecialOptLevel = 0;
	RefreshSpecialInfo(worldChunk);
	RefreshSpecialRadioBtn();
}

void CToolLayerDlg::RefreshSpecialRadioBtn()
{
	CheckDlgButton( IDC_RADIO_Level0, 0 );
	CheckDlgButton( IDC_RADIO_Level1, 0 );
	CheckDlgButton( IDC_RADIO_Level2, 0 );
	CheckDlgButton( IDC_RADIO_Level3, 0 );
	switch (m_nspecialOptLevel)
	{
	case 0:
		{
			CheckDlgButton(IDC_RADIO_Level0,1);
			break;
		}
	case 1:
		{
			CheckDlgButton(IDC_RADIO_Level1,1);
			break;
		}
	case 2:
		{
			CheckDlgButton(IDC_RADIO_Level2,1);
			break;
		}
	case 3:
		{
			CheckDlgButton(IDC_RADIO_Level3,1);
			break;
		}
	}

}
void CToolLayerDlg::OnBnClickedBtnRefreshTexture()
{
	CToolLayer* layer		= GetToolLayer();
	CWorldChunk* worldChunk = layer->m_selWorldChunk;
	if (!worldChunk)
	{
		return;
	}
	if (m_nspecialOptLevel >= worldChunk->GetLayerCount())
	{
		return;
	}
	CResEditMgr* resMgr		= layer->m_selResMgr;
	resMgr->ReloadTexture(worldChunk->GetTexture(m_nspecialOptLevel));
}

// void CToolLayerDlg::OnBnClickedCheckPaintShadow()
// {
// 	CToolLayer*toolLayer = GetToolLayer();
// 
// 	bool isPaintShadow = (BST_CHECKED == m_chkButtonPaintShadow.GetCheck());
// 	toolLayer->SetPaintShadow(isPaintShadow);
// 
// }

void CToolLayerDlg::OnBnClickedCkUseWintab4Alpha()
{
	// TODO: Add your control notification handler code here
	if (m_UseWinTabsPressCheckBox.GetCheck() == BST_UNCHECKED)
	{
		// 把原来的Alpha值设置回去
		CString strAlpha;
		strAlpha.Format( _T("%x"), m_nLastAlpha);
		m_editAlpha.SetWindowText( strAlpha );
	}
	else
	{
		m_nLastAlpha = GetToolLayer()->m_alpha;
	}
}

void CToolLayerDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	CToolLayer* layer		= GetToolLayer();
	if (nSBCode==SB_THUMBPOSITION) 
	{
		if (pScrollBar != NULL)
		{
			if(pScrollBar->GetDlgCtrlID()==IDC_SPIN_ALPHA) 
			{
				if (IsUseWinTabPressAsAlpha())
				{
					CString strAlpha;
					strAlpha.Format( _T("%x"), m_nLastAlpha == -1 ? layer->m_alpha : m_nLastAlpha);
					m_editAlpha.SetWindowText( strAlpha );
				}
				else
				{
					UpdateData(TRUE);

					uInt8 alpha	= nPos & 0x0F;
					alpha = alpha | (alpha << 4);
					ShowAlphaText(alpha);

					layer->m_alpha = alpha;
				}
			}
			else if (pScrollBar->GetDlgCtrlID()==IDC_SPIN_FLOW)
			{
				UpdateData();
				uInt32 flow	= nPos ;
				FlowChanged(flow);

				layer->m_flow			= flow;

				UpdateData( FALSE );
			}
			else
			{
				if (!layer->m_selWorldChunk)
				{
					return;
				}
				TTextureInfo& pInfo = layer->m_selWorldChunk->GetTexInfo(m_nspecialOptLevel);
				if (pInfo.IsAlign())
				{
					return;
				}
				if (pScrollBar->GetDlgCtrlID()==IDC_SPIN_TEXTURE_X0)
				{
					CString strValue;
					strValue.Format( _T("%d"), nPos );
					m_edit_textureX0.SetWindowText( strValue );

					pInfo.m_nX = nPos;
					layer->m_selResMgr->RefreshSpecialChunkLayer(layer->m_selWorldChunk,m_nspecialOptLevel);
					UpdateData( FALSE );	
				}
				else if (pScrollBar->GetDlgCtrlID()==IDC_SPIN_TEXTURE_Y0)
				{
					CString strValue;
					strValue.Format( _T("%d"), nPos );
					m_edit_textureY0.SetWindowText( strValue );

					pInfo.m_nY = nPos;
					layer->m_selResMgr->RefreshSpecialChunkLayer(layer->m_selWorldChunk,m_nspecialOptLevel);
					UpdateData( FALSE );	
				}
				else if (pScrollBar->GetDlgCtrlID()==IDC_SPIN_TEXTURE_SCALEX0)
				{
					CString strValue;
					strValue.Format( _T("%d"), nPos );
					m_edit_textureScaleX0.SetWindowText( strValue );

					pInfo.m_ScaleX = nPos;
					layer->m_selResMgr->RefreshSpecialChunkLayer(layer->m_selWorldChunk,m_nspecialOptLevel);
					UpdateData( FALSE );	
				}
				else if (pScrollBar->GetDlgCtrlID()==IDC_SPIN_TEXTURE_SCALEY0)
				{
					CString strValue;
					strValue.Format( _T("%d"), nPos );
					m_edit_textureScaleY0.SetWindowText( strValue );

					pInfo.m_ScaleY = nPos;
					layer->m_selResMgr->RefreshSpecialChunkLayer(layer->m_selWorldChunk,m_nspecialOptLevel);
					UpdateData( FALSE );	
				}
				else if (pScrollBar->GetDlgCtrlID()==IDC_SPIN_TEXTURE_ROTATION)
				{
					CString strValue;
					strValue.Format( _T("%6.2f"), nPos );
					m_edit_textureScaleY0.SetWindowText( strValue );

					pInfo.m_angle = nPos;
					layer->m_selResMgr->RefreshSpecialChunkLayer(layer->m_selWorldChunk,m_nspecialOptLevel);
					UpdateData( FALSE );	
				}
			}
		}
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}