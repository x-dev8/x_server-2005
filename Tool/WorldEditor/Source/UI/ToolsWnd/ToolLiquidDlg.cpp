/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolLiquid.cpp
* Date: 	05/31/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include "Edit/ToolLiquid.h"
#include "Edit/ToolManager.h"
#include "ToolLiquidDlg.h"
#include "Ndl/NdlWorldEditor.h"
#include "MeTerrain/NdlResMgr.h"
#include "EditRes/NdlEditRes.h"
////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CToolLiquidDlg, CDialog)

CToolLiquidDlg::CToolLiquidDlg(CToolLiquidDlg* pParent)
: CDialog(CToolLiquidDlg::IDD, pParent)
{
	m_isFillUI		= false;
}

CToolLiquidDlg::~CToolLiquidDlg()
{
	
}

void CToolLiquidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolLiquidDlg)
	DDX_Control(pDX, IDC_EDT_TEXTURE, m_editTextureFile);
	DDX_Control(pDX, IDC_CHK_LOCK_PARAM, m_chkLockLayer);
	DDX_Control(pDX, IDC_TILENUM, m_TilePos);
	
	DDX_Text(pDX, IDC_EDIT_WATER_HEIGHT, mWaterHeight);

	DDX_Control(pDX, IDC_SLIDER_ALPHA, mWaterAlphaCtrl);
	DDX_Slider(pDX, IDC_SLIDER_ALPHA, mWaterAlpha);
	DDX_Control(pDX, IDC_STATIC_WATER_ALPHA, mWaterAlphaStatic);

	DDX_Control(pDX, IDC_BTN_WATER_COLOR, m_cpLiquidColor);
	DDX_XTColorPicker(pDX, IDC_BTN_WATER_COLOR, m_liquidColor);

	DDX_Control(pDX, IDC_BTN_DEL_CHUNK_LIQUID, mDelLiquidBtn);
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CToolLiquidDlg, CDialog)
	//{{AFX_MSG_MAP(CToolLiquidDlg)
	//}}AFX_MSG_MAP
	ON_CPN_XT_SELENDOK(IDC_BTN_WATER_COLOR, OnSelLiquidColor)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_DEL_CHUNK_LIQUID, &CToolLiquidDlg::OnBnClickedBtnDelChunkLiquid)
END_MESSAGE_MAP()


BOOL CToolLiquidDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editTextureFile.Initialize(this, BES_XT_CHOOSEFILE);
	m_editTextureFile.SetDlgStyle( OFN_NOCHANGEDIR|OFN_OVERWRITEPROMPT );

// 	ConvertNiColor2RGB(g_defaultLiquidColor,m_liquidColor);
	m_liquidColor = g_defaultLiquidColor;
	m_cpLiquidColor.SetDefaultColor( m_liquidColor );
	m_cpLiquidColor.ShowText(true);

	mWaterAlphaCtrl.SetRange(1, 100);
	mWaterAlphaCtrl.SetPos(1);
	mWaterAlphaStatic.SetWindowText("1");

	mDelLiquidBtn.EnableWindow(FALSE);

	UpdateData( FALSE );

	return TRUE;
}

void CToolLiquidDlg::UpdateLock( bool isLock )
{
	m_chkLockLayer.SetCheck( isLock?1:0 );
	m_chkLockLayer.SetWindowText( isLock?_T("已锁定"):_T("未锁定") );

	// 当前Chunk有Liquid才允许删除
	CToolLiquid *liquidTool = GetToolLiquid();
	mDelLiquidBtn.EnableWindow(isLock && liquidTool->IsCurSelectedChunkHaveLiquid());
}

void CToolLiquidDlg::SetActive( bool isModify )
{
	UpdateSetting( isModify );
}

void CToolLiquidDlg::RefreshLiquid(flt32* pt2)
{
	sInt32 chunk[2];
	theApp.GetWorldEditor()->GetChunkIndexFromPos( chunk, pt2 );

	CString strTile;
	strTile.Format( _T("(%d,%d)"), chunk[0], chunk[1]);
	m_TilePos.SetWindowText(strTile.GetString());

	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	CToolLiquid* layer		= (CToolLiquid*)toolMgr->GetTool( TOOL_LIQUID );

	CWorldChunk* worldChunk	= layer->m_selWorldChunk;
	CResEditMgr* resMgr		= layer->m_selResMgr;

	if (NULL != worldChunk && NULL!=resMgr ) 
	{
		CString strValue;

		strValue.Format("%8.2f", worldChunk->m_liquidHeight);
		mWaterHeight = strValue;
		
		m_liquidColor = worldChunk->m_liquidColor;
		m_cpLiquidColor.SetColor(m_liquidColor);

		mWaterAlpha = worldChunk->m_liquidAlphaCoaf;

		strValue.Format("%d", mWaterAlpha);
		mWaterAlphaStatic.SetWindowText(strValue);

		// send data to control
		UpdateData(FALSE);
	}
}

bool CToolLiquidDlg::UpdateSetting( bool isModify )
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_LIQUID );

	CToolLiquid* toolLiquid = (CToolLiquid*)( toolManager->GetActiveTool() );

	Assert( NULL != toolLiquid );

	if (!m_isFillUI)
	{
		toolLiquid->Bind(this);
		m_isFillUI = true;
	}

	UpdateData(FALSE);
	return true;
}

void CToolLiquidDlg::OnSelLiquidColor()
{
	UpdateData();
	GetToolLiquid()->m_NiColor = m_liquidColor;

	GetToolLiquid()->RefreshLiquid();
}

CToolLiquid* CToolLiquidDlg::GetToolLiquid()
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_LIQUID );

	return (CToolLiquid*)( toolManager->GetActiveTool() );
}

BOOL CToolLiquidDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	WORD wNotify = HIWORD(wParam);
	WORD wCtrlID = LOWORD(wParam);

	if (wNotify == EN_KILLFOCUS)
	{
		if (wCtrlID == IDC_EDIT_WATER_HEIGHT)
		{
			// retrieved data
			UpdateData(TRUE);

			if (!mWaterHeight.IsEmpty())
			{
				flt32 height = atof(mWaterHeight);

				CToolLiquid *liquidTool = GetToolLiquid();
				liquidTool->m_height = height;
				liquidTool->RefreshLiquid();
			}
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}

void CToolLiquidDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (nSBCode == TB_THUMBPOSITION)
	{
		mWaterAlpha = nPos;

		CString strValue;
		strValue.Format("%d", mWaterAlpha);
		mWaterAlphaStatic.SetWindowText(strValue);

		CToolLiquid *liquidTool = GetToolLiquid();
		liquidTool->m_alphaCoaf = mWaterAlpha;
		liquidTool->RefreshLiquid();
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CToolLiquidDlg::OnBnClickedBtnDelChunkLiquid()
{
	if (!mDelLiquidBtn.IsWindowEnabled())
		return;

	if (::AfxMessageBox("水体删除不可回复, 确定要删除?", MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
	{
		mDelLiquidBtn.EnableWindow(FALSE);

		CToolLiquid *liquidTool = GetToolLiquid();
		liquidTool->RemoveCurSelectedLiquid();
	}
}
