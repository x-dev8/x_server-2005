/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolDoodadDlg.cpp
* Date: 	05/31/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "Resource/Resource.h"
#include "Ndl/NdlWorldEditor.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "Edit/ToolDoodad.h"
#include "Edit/ToolManager.h"
#include "ToolDoodadDlg.h"
#include "../Dlg/DoodadNewLevelDlg.h"
////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CToolDoodadDlg, CDialog)

CToolDoodadDlg::CToolDoodadDlg(CToolDoodadDlg* pParent)
: CDialog(CToolDoodadDlg::IDD, pParent)
{
	m_isFillData = false;
}

CToolDoodadDlg::~CToolDoodadDlg()
{

	for(size_t i = 0; i < m_doodadResList.size(); i++ )	{
		CWorldRes* p = m_doodadResList[i];
		SAFE_DELETE( p );
	}
	m_doodadResList.clear();

	for(size_t i = 0; i < m_doodadTypeList.size(); i++ )	{
		CString* p = m_doodadTypeList[i];
		SAFE_DELETE( p );
	}
	m_doodadResList.clear();
}

void CToolDoodadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolDoodadDlg)
	DDX_Control(pDX, IDC_CMB_DOODADS, m_doodadClassList);
	DDX_Control(pDX, IDC_CURRDOODADLEVEL, m_currChunkDoodadList);
	DDX_Control(pDX, IDC_COMBO_DOODAD_BRUSH, m_DoodadBrushList);
	DDX_Control(pDX, IDC_LIST_DOODADS, m_doodadListBox);
	DDX_Control(pDX, IDC_COMBO_OPTMODE, m_modeList);
	DDX_Control(pDX, IDC_CHK_LOCK_PARAM, m_chkLockLayer);
	DDX_Control(pDX, IDC_TILENUM, m_TilePos);
	DDX_Control(pDX, IDC_STATIC_UNITSIZE, m_LevelUnitSize);
	DDX_Control(pDX, IDC_STATIC_TYPE, m_LevelType);
	DDX_Control(pDX, IDC_EDT_SIZE_DENSITY, m_editDensity);
	DDX_Control(pDX, IDC_EDT_SIZE_FRM, m_editSizeFrom );
	DDX_Control(pDX, IDC_EDT_SIZE_TOO, m_editSizeTo );
	//}}AFX_DATA_MAP
}
BEGIN_MESSAGE_MAP(CToolDoodadDlg, CDialog)
	//{{AFX_MSG_MAP(CToolDoodadDlg)
	ON_LBN_SELCHANGE(IDC_CMB_DOODADS, OnDoodadClassChange)
	ON_LBN_SELCHANGE(IDC_CURRDOODADLEVEL, OnCurrDoodadChange)
	ON_LBN_SELCHANGE(IDC_LIST_DOODADS, OnDoodadSelChange)
	ON_LBN_SELCHANGE(IDC_COMBO_OPTMODE, OnModeChange)
	ON_LBN_SELCHANGE(IDC_COMBO_DOODAD_BRUSH, OnBrushSelChange)
	ON_BN_CLICKED(IDC_NEWDOODADLEVEL, OnBtnNewLevel)
	ON_BN_CLICKED(IDC_DELETEDOODADLEVEL, OnBtnDeleteLevel)
	ON_LBN_DBLCLK(IDC_LIST_DOODADS,OnDoodadChange)
	
  	ON_EN_KILLFOCUS(IDC_EDT_SIZE_FRM, OnKillfocusEdtSizeFrom)
  	ON_CBN_KILLFOCUS(IDC_EDT_SIZE_TOO, OnKillfocusEdtSizeTo)
	ON_EN_KILLFOCUS(IDC_EDT_SIZE_DENSITY, OnKillfocusEdtDensity)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CToolDoodadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	m_modeList.SetCurSel( 0 );
	
	m_editSizeFrom.SetWindowText( _T("100") );
	m_editSizeTo.SetWindowText( _T("100") );
	m_editDensity.SetWindowText(_T("100"));
	LoadDoodadRes();
	return TRUE;
}

void CToolDoodadDlg::UpdateLock( bool isLock )
{
	m_chkLockLayer.SetCheck( isLock?1:0 );
	m_chkLockLayer.SetWindowText( isLock?_T("已锁定"):_T("未锁定") );
}

void CToolDoodadDlg::EnumDoodadFile( LPCTSTR strDir,sInt32 nType )
{
	CFileFind ff;
	CString strPath( strDir );
	strPath += _T("\\*.*");
	BOOL bFound = ff.FindFile(strPath);
	if (!bFound) 
		return;

	char objPath[MAX_PATH*2];
	char objName[MAX_PATH*2];
	while (bFound)	{
		bFound = ff.FindNextFile();
		if (ff.IsDots())
			continue;
		strPath = ff.GetFilePath();
		if ( ff.IsDirectory() ) {
			EnumDoodadFile( strPath, nType );
		}
		else{
			int nNifPos = strPath.Find(_T(".mex")) ;
			//int nKfmPos = strPath.Find(_T(".kfm"));
			if((-1 == nNifPos || (nNifPos != strPath.GetLength() - 4 )))
				//&& (-1 == nKfmPos || (nKfmPos != strPath.GetLength() - 4 ))) 
			{
				continue;
			}
			if( !SpliteFullPathToDataPath( strPath, objPath, objName ) ) {
				continue;
			}
			_strlwr_s( objName );
			{
				CDoodadRes* doodadRes = MeNew CDoodadRes();
				char path[MAX_PATH*2];
				sprintf_s( path, "%s\\%s", objPath, objName );
				doodadRes->SetName(path);
				doodadRes->LoadModel(  );
				doodadRes->SetId(nType);
				m_doodadResList.push_back(doodadRes);
			}
		}
	}	
}

bool CToolDoodadDlg::LoadDoodadRes()
{
	MeXmlDocument Doc;
	char fileName[MAX_PATH*2];
	sprintf_s( fileName, "%s\\Required\\Config\\doodad.xml", CWorld::GetAppCharDir() );
	if( !Doc.LoadFile( fileName ) )
		return false;
	MeXmlElement* root = Doc.FirstChildElement( "Config" );
	if( NULL != root ) {
		MeXmlElement* xmlElmt = root->FirstChildElement();
		while( NULL != xmlElmt ) {
			MeXmlElement* subElmt = xmlElmt->FirstChildElement();
			while( NULL != subElmt ) {
				const char* doodadName	= subElmt->Attribute( "name" );
				ASSERT( NULL != doodadName );
				ASSERT( (strlen(doodadName)+1) < RES_NAME_LEN );
				const char* pathName		= subElmt->Attribute( "data" );
				ASSERT( NULL != pathName );
				ASSERT( (strlen(pathName)+1) < MAX_PATH );
				CString dir;
				dir.Format( _T("%s%hs"), CWorld::GetAppDataCharDir(), pathName );
				CString* pcTmp = new CString(doodadName);
				m_doodadTypeList.push_back(pcTmp);
				EnumDoodadFile( dir, m_doodadTypeList.size() - 1);
				subElmt = subElmt->NextSiblingElement();
			}
			xmlElmt	= xmlElmt->NextSiblingElement();
		}
	}
	return true;
}

void CToolDoodadDlg::SetActive( bool isModify )
{
	CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
	toolManager->SetActiveTool( TOOL_DOODAD );
 	CToolDoodad* toolDoodad = (CToolDoodad*)( toolManager->GetActiveTool() );
 	Assert( NULL != toolDoodad );
	toolDoodad->Reset();

	FillDoodadClass();
	UpdateSetting();
}

void CToolDoodadDlg::UpdateSetting()
{
	CToolDoodad* toolDoodad = GetDoodadTool();
	Assert( NULL != toolDoodad );
	
	toolDoodad->Bind( this );

	m_modeList.SetCurSel( toolDoodad->m_optMode );

	if( RES_INVALID_ID != toolDoodad->m_curDoodadClassId ) {
		m_doodadClassList.SetCurSel( toolDoodad->m_curDoodadClassId );
	}
	if( RES_INVALID_ID != toolDoodad->m_curDoodadId ) {
		m_doodadListBox.SetCurSel( toolDoodad->m_curDoodadId );
	}
	m_LevelType.SetWindowText("");
	if (toolDoodad->GetCurrLevel())
	{
		CString sTemp;
		const char* pName = toolDoodad->GetDoodadName(toolDoodad->GetCurrLevel());
		sTemp.Format(_T("%hs"),pName);
		m_LevelType.SetWindowText(sTemp);
		flt32	fUnitSize = WORLD_CHUNKSIZE/toolDoodad->GetCurrLevel()->mulevelUnit;
		sTemp.Format(_T("%6.4f"),fUnitSize);
		m_LevelUnitSize.SetWindowText(sTemp);
	}

	BrushChanged(toolDoodad->m_brushIndex);
	if (toolDoodad->m_selWorldChunk && toolDoodad->m_selWorldChunk->GetDoodadLevelCount() > 0)
	{
		m_currChunkDoodadList.SetCurSel(toolDoodad->m_nCurrLevel);
	}
	UpdateData( FALSE );
}

void CToolDoodadDlg::FillDoodadClass()
{
	if( m_isFillData )
		return;

	m_doodadClassList.ResetContent();
	for( size_t i=0; i<m_doodadTypeList.size(); i++ ) {
		m_doodadClassList.InsertString( i, m_doodadTypeList[i]->GetString() );
	}
	CToolDoodad* toolDoodad = GetDoodadTool();
	m_doodadClassList.SetCurSel(toolDoodad->m_curDoodadClassId);
	FillDoodad(0);
	m_isFillData = true;
}

void CToolDoodadDlg::FillDoodad( sInt32 doodadClassId )
{
	if( doodadClassId <0 || doodadClassId >= m_doodadTypeList.size() )
		return;
	m_doodadListBox.ResetContent();
	std::vector< CWorldRes* >& list = m_doodadResList;
	sInt32 nCount = 0;
	for( size_t i=0; i<list.size(); i++ ) 
	{
		if (((CDoodadRes*)list[i])->GetId() == doodadClassId)
		{
			CString strName;
			strName = list[i]->GetName();
			m_doodadListBox.AddString(strName );
			m_doodadListBox.SetItemDataPtr(nCount,list[i]);
			++nCount;
		}

	}
	m_doodadListBox.SetCurSel(0);
}

void CToolDoodadDlg::OnDoodadClassChange()
{
	sInt32 sel = m_doodadClassList.GetCurSel();
	if( -1 != sel ) {
		CToolManager* toolManager = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetToolManager();
		CToolDoodad* toolDoodad = (CToolDoodad*)( toolManager->GetActiveTool() );
		Assert( NULL != toolDoodad );
		
		toolDoodad->m_curDoodadClassId	= sel;
		toolDoodad->m_curDoodadId		= 0;
		FillDoodad( toolDoodad->m_curDoodadClassId );

		UpdateSetting();
	}
}

void CToolDoodadDlg::OnDoodadSelChange()
{
	sInt32 sel = m_doodadListBox.GetCurSel();
	if( -1 != sel ) {
		CToolDoodad* toolDoodad		=  GetDoodadTool();
		Assert( NULL != toolDoodad );
		
		toolDoodad->m_curDoodadId	= sel;
		
		UpdateSetting();
	}
}

void CToolDoodadDlg::OnDoodadChange()
{
	sInt32 sel = m_doodadListBox.GetCurSel();
	if( -1 != sel ) {
		CToolDoodad* toolDoodad = GetDoodadTool();
		Assert( NULL != toolDoodad );

		toolDoodad->m_curDoodadId	= sel;
		TDoodadLevelInfo* pInfo = toolDoodad->GetCurrLevel();
		if (NULL != pInfo)
		{
			CWorldRes*	pRes = (CWorldRes*)m_doodadListBox.GetItemDataPtr(sel);
			toolDoodad->ChangeDoodad(pInfo,pRes->GetName());
		}
		UpdateSetting();
	}

}


void CToolDoodadDlg::OnModeChange()
{
	sInt32 sel = m_modeList.GetCurSel();
	if( CB_ERR != sel ) {
		CToolDoodad* toolDoodad	= GetDoodadTool();
		toolDoodad->m_optMode	= sel;
	}	
}


void CToolDoodadDlg::OnKillfocusEdtSizeFrom()
{
	UpdateData();

	CToolDoodad* toolDoodad	= GetDoodadTool();
	if (!toolDoodad)
	{
		return;
	}
	CString strValue;
	m_editSizeFrom.GetWindowText( strValue );
	toolDoodad->m_size[0]	= _tstoi( strValue );
	toolDoodad->m_size[0]	= ZnClamp<uInt32>( toolDoodad->m_size[0], 1, 255 );
	m_editSizeTo.GetWindowText( strValue );
	toolDoodad->m_size[1]	= _tstoi( strValue );
	toolDoodad->m_size[1]	= ZnClamp<uInt32>( toolDoodad->m_size[1], 1, 255 );
	if( toolDoodad->m_size[1] < toolDoodad->m_size[0] ) {
		toolDoodad->m_size[1] = toolDoodad->m_size[0];
	}
	strValue.Format( _T("%d"), toolDoodad->m_size[0] );
	m_editSizeFrom.SetWindowText( strValue );
	strValue.Format( _T("%d"), toolDoodad->m_size[1] );
	m_editSizeTo.SetWindowText( strValue );
	UpdateData( FALSE );
}

void CToolDoodadDlg::OnKillfocusEdtSizeTo()
{
	UpdateData();

	CToolDoodad* toolDoodad	= GetDoodadTool();
	if (!toolDoodad)
	{
		return;
	}


	CString strValue;
	m_editSizeFrom.GetWindowText( strValue );
	toolDoodad->m_size[0]	= _tstoi( strValue );
	toolDoodad->m_size[0]	= ZnClamp<uInt32>( toolDoodad->m_size[0], 1, 255 );
	m_editSizeTo.GetWindowText( strValue );
	toolDoodad->m_size[1]	= _tstoi( strValue );
	toolDoodad->m_size[1]	= ZnClamp<uInt32>( toolDoodad->m_size[1], 1, 255 );
	if( toolDoodad->m_size[0] > toolDoodad->m_size[1] ) {
		toolDoodad->m_size[0] = toolDoodad->m_size[1];
	}
	strValue.Format( _T("%d"), toolDoodad->m_size[0] );
	m_editSizeFrom.SetWindowText( strValue );
	strValue.Format( _T("%d"), toolDoodad->m_size[1] );
	m_editSizeTo.SetWindowText( strValue );
	UpdateData( FALSE );
}


void CToolDoodadDlg::OnKillfocusEdtDensity()
{
	UpdateData();

	CToolDoodad* toolDoodad	= GetDoodadTool();
	if (!toolDoodad)
	{
		return;
	}

	CString strValue;

	m_editDensity.GetWindowText( strValue );
	toolDoodad->m_density	= _tstoi( strValue );
	toolDoodad->m_density	= ZnClamp<uInt32>( toolDoodad->m_density, 1, 100);
	strValue.Format( _T("%d"), toolDoodad->m_density );
	m_editDensity.SetWindowText( strValue );
	UpdateData( FALSE );
}


void CToolDoodadDlg::OnBtnNewLevel()
{
	CToolDoodad* toolDoodad = GetDoodadTool();
	if (NULL == toolDoodad->m_selWorldChunk)
	{
		return;
	}
	CDoodadNewLevelDlg dlg;

	if( dlg.DoModal() == IDOK ) {
		int nLevelUnit = dlg.GetUnitSize();
		CWorldEditDoc::GetActiveMapDoc()->SetWorldModify();

		int nIndex = m_doodadListBox.GetCurSel();
		//added by zilong. 2010-01-10
		//增加选择序号的判断，防止没有选择时出错（即nIndex == -1）。
		if (nIndex != LB_ERR)
		{

			CWorldRes*	pRes = (CWorldRes*)m_doodadListBox.GetItemDataPtr(nIndex);

			toolDoodad->CreateNewLevel(nLevelUnit,pRes->GetName());

			RefreshChunckDoodadLevel();

			UpdateSetting();
		}

	}

}

void CToolDoodadDlg::OnBtnDeleteLevel()
{
	CToolDoodad* toolDoodad = GetDoodadTool();
	if(toolDoodad->DeleteCurrLevel())
	{
		RefreshChunckDoodadLevel();
		UpdateSetting();
	}
}

void CToolDoodadDlg::Refresh( flt32* pt )
{
	sInt32 chunk[2];
	theApp.GetWorldEditor()->GetChunkIndexFromPos( chunk, pt );

	CString strTile;
	strTile.Format( _T("(%d,%d)"), chunk[0], chunk[1]);
	m_TilePos.SetWindowText(strTile.GetString());

	UpdateSetting();

}

CToolDoodad* CToolDoodadDlg::GetDoodadTool()
{
	CWorldEditDoc* worldEditDoc = CWorldEditDoc::GetActiveMapDoc();
	if (!worldEditDoc)
	{
		return NULL;
	}
	CWorldEditView* view	= worldEditDoc->GetWorldView();
	CToolManager* toolMgr	= view->GetToolManager();
	return	 (CToolDoodad*)toolMgr->GetTool( TOOL_DOODAD );
}

void CToolDoodadDlg::RefreshChunckDoodadLevel()
{
	CToolDoodad* toolDoodad = GetDoodadTool();
	
	CWorldChunk* pchunk = toolDoodad->m_selWorldChunk;
	if (NULL == pchunk)
	{
		return;
	}

	// 重新初始化 装饰物LB
	m_currChunkDoodadList.ResetContent();
	for (sInt32 i = 0; i < pchunk->GetDoodadLevelCount(); ++i)
	{
		CString pListItem;
		if (pchunk->GetDoodadLevel(i))
		{
			const char* pName = toolDoodad->GetDoodadName(pchunk->GetDoodadLevel(i));
			pListItem.Format(_T("%d:%hs"),i,pName);
		}
		m_currChunkDoodadList.AddString(  pListItem.GetString());
	}
}

void CToolDoodadDlg::OnCurrDoodadChange()
{
	CToolDoodad* toolDoodad = GetDoodadTool();
	CWorldChunk* pchunk = toolDoodad->m_selWorldChunk;
	if (NULL == pchunk)
	{
		return;
	}
	sInt32 nSel = m_currChunkDoodadList.GetCurSel();
	if (nSel >=0 && nSel < pchunk->GetDoodadLevelCount())
	{
		toolDoodad->m_nCurrLevel = nSel;
	}
	UpdateSetting();
}

void CToolDoodadDlg::OnBrushSelChange()
{
	CToolDoodad* toolDoodad = GetDoodadTool();
	CWorldChunk* pchunk = toolDoodad->m_selWorldChunk;
	if (NULL == pchunk)
	{
		return;
	}
	sInt32 nSel = m_DoodadBrushList.GetCurSel();
	toolDoodad->SetBrushIndex( nSel );

}

void CToolDoodadDlg::BrushChanged( int nSelect )
{
	m_DoodadBrushList.SetCurSel(nSelect);
}