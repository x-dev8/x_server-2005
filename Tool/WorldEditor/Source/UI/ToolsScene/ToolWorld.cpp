/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolWorld.cpp
* Date: 	06/07/2007
* Desc:
*
*******************************************************************************/
#include "stdAfx.h"
#include "Resource/Resource.h"
#include "RapidXml/MeRapidXml.h"
#include "MeTerrain/World.h"
#include "Ndl/NdlWorldEditor.h"
#include <atlimage.h>
#include "UI/Dlg/NewWtdFileDlg.h"
#include "UI/Custom/TextureNavigationWnd.h"
#include "UI/Dlg/ReplaceTileTextureDlg.h"
#include "ui/Dlg/SnapMiniMapDlg.h"
#include "ui/Dlg/ReachableMapDlg.h"
#include "UI/Dlg/MapModelsDlg.h"
#include "ToolWorld.h"
#include <algorithm>
#include <functional>      // For greater<int>( )
#include "atlpath.h"
#include "UI/Custom/PathDialog.h"
#include "ui/Custom/ReachableMapGenerate.h"
#include "MeTerrain/MapConfigXml.h"
#include "Map/WorldWriteStream.h"
#include "SwMap.h"
// #include "MeTerrain/FlyRouteXml.h"
#include "MeTerrain/NPCRouteXml.h"
#include "MeTerrain/SoundPointXml.h"
#include "Me3d/PostProcess/PostProcessManager.h"
#include "ui/ToolsScene/MapBloomDlg.h"
#include "WorldAttribute.h"

IMPLEMENT_DYNAMIC(CToolWorld, CDialog)

const sInt32 s_DIRECTORY = -1;

static MapContrastDlg* s_dlgMapContrast = 0;
static MapBloomDlg* s_dlgMapBloom = 0;
////////////////////////////////////////////////////////////////////////////////
CToolWorld::CToolWorld(CToolWorld* pParent)
					: ScrollableDialog(CToolWorld::IDD, pParent, SB_VERT)
{
	m_sliderHeightPos = 100;
	m_sliderSizePos		= 100;
	m_tile				= -1;
	//s_dlgMapContrast	= NULL;
}

CToolWorld::~CToolWorld()
{
	CReachableMapGenerate::Release();
	if( s_dlgMapContrast )
		delete s_dlgMapContrast;
}

void CToolWorld::SetActive( bool isModify )
{
}

void CToolWorld::Reset()
{	
	m_treeWorld.DeleteAllItems();
}

void CToolWorld::AddTile(CString& name )
{
	HTREEITEM selItem	= m_treeWorld.GetSelectedItem();
	uInt32 tileId	= m_treeWorld.GetItemData( selItem );
	if (s_DIRECTORY != tileId)
	{
		selItem = m_treeWorld.GetNextItem( selItem, TVGN_PARENT );
	}
	HTREEITEM newItem = AddChildLeafNode(name,selItem);
	m_treeWorld.Expand( selItem, TVE_EXPAND );
	m_treeWorld.SetCheck(newItem);
}

void CToolWorld::UpdateTree( const char* strDir )
{
	m_treeWorld.DeleteAllItems();
	CString worldPath;
	worldPath.Format(_T("%hs"),strDir);
	CString worldName = worldPath.Mid(worldPath.ReverseFind('\\') + 1 );

	HTREEITEM rootItem = m_treeWorld.InsertItem( worldName );
	m_treeWorld.SetItemData( rootItem, s_DIRECTORY );
	m_treeWorld.SetItemImage(rootItem,0,0);


	EnumWTDFile(worldPath,rootItem);
	
	m_treeWorld.Expand( rootItem, TVE_EXPAND );

	UpdateData( FALSE );
	
}


BEGIN_MESSAGE_MAP(CToolWorld, CDialog)
	//{{AFX_MSG_MAP(CToolWorld)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_NEWFOLDER, OnBtnNewFolder)
	ON_BN_CLICKED(IDC_BTN_NEWTILE, OnBtnNewtile)
	ON_BN_CLICKED(IDC_BTN_DELTILE, OnBtnDelTile)
	ON_BN_CLICKED(IDC_CHK_SHOWGRID, OnChkShowGrid)
	ON_BN_CLICKED(IDC_CHK_REACHABLE, OnChkReachable)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_WORLD, OnDbClkTreeCtrl)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_WORLD, OnRClkTreeCtrl)
	ON_COMMAND(ID_POP_TILE_SNAP, OnListMenuSnapMinimap)
	ON_COMMAND(ID_POP_REACHABLEMAP, OnListMenuReachableMap)
	ON_COMMAND(ID_POP_TILE_REPLACETEXTURE, OnListMenuReplaceTileTexture)
	ON_COMMAND(ID_POP_TILE_CLEAN_MODEL, OnListMenuCleanModel)
	ON_COMMAND(ID_POP_CONVERT2GAMEMAP, OnListMenuConvert2GameMap)
	ON_COMMAND(ID_POP_MonsterData, OnListMenuMonsterData)
	ON_COMMAND(ID_POP_CAL_PF_WEIGHT, OnListMenuCalPFWeight)
	ON_COMMAND(ID_POP_WATER_MAP, OnListMenuWaterMap)
	ON_COMMAND(ID_POP_HEIGHT_MAP, OnListMenuHeightMap)
	ON_COMMAND(IDM_MAP_MODELS, OnListMenuMapModels)

	ON_EN_KILLFOCUS(IDC_EDIT_REACHABLEANGLE, OnKillfocusReachableAngle)
	ON_EN_KILLFOCUS(IDC_EDIT_REACHABLEANGLE, OnKillfocusReachableAngle)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_HEIGHTSCALE, &CToolWorld::OnNMCustomdrawSliderHeightscale)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SIZESCALE, &CToolWorld::OnNMCustomdrawSliderSizescale)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MESHHEIGHT, &CToolWorld::OnMeshHeightSizescale)
	ON_EN_KILLFOCUS(IDC_EDIT_CHINESENAME, &CToolWorld::OnEnKillfocusEditChinesename)
	//ON_BN_CLICKED(IDC_CHK_SHOWFOOTPRINT, &CToolWorld::OnBnClickedChkShowfootprint)
    ON_COMMAND(ID_POP_BBOX_SNAP, OnListMenuSnapBBoxMinimap)
	ON_BN_CLICKED(IDC_BUTTON_WORLDATTR, &CToolWorld::OnBnClickedButtonWorldattr)
	ON_BN_CLICKED(IDC_BUTTON_SETMESH, &CToolWorld::OnBnClickedButtonSetMesh)
	ON_BN_CLICKED(IDC_BUTTON_CONTRAST, &CToolWorld::OnBnClickedButtonContrast)
	ON_BN_CLICKED(IDC_BUTTON_BLOOM, &CToolWorld::OnBnClickedButtonBloom)
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CToolWorld::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolWorld)
	DDX_Control(pDX, IDC_TREE_WORLD, m_treeWorld);
	DDX_Control(pDX, IDC_SLIDER_HEIGHTSCALE, m_sliderHeightScale);
	DDX_Control(pDX, IDC_STATIC_HEIGHTSCALE, m_textHeightScale);
	DDX_Control(pDX, IDC_SLIDER_SIZESCALE, m_sliderSizeScale);
	DDX_Control(pDX, IDC_STATIC_SIZESCALE, m_textSizeScale);
	DDX_Control(pDX, IDC_EDIT_REACHABLEANGLE, m_editReachableAngle);
	DDX_Control(pDX, IDC_CHK_REACHABLE, m_ckShowReachable);
	DDX_Control(pDX, IDC_EDIT_CHINESENAME, m_edit_ChineseName);
	//DDX_Control(pDX, IDC_CHK_SHOWFOOTPRINT, m_check_ShowFootPrint);
	DDX_Control(pDX, IDC_EDIT_MINLEVEL, m_editMesh);
	DDX_Control(pDX, IDC_SLIDER_MESHHEIGHT, m_sliderMeshHeight);
	//}}AFX_DATA_MAP
}

BOOL CToolWorld::OnInitDialog()
{
	CDialog::OnInitDialog();

	//if (!m_treeWorld.Create( WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
	//	CRect(0,0,0,0), this, 0xFF ))
	//{
	//	TRACE0( "Unable to create tree control.\n" );
	//	return FALSE;
	//}
	m_treeWorld.EnableMultiSelect( FALSE );

	HTREEITEM rootItem;
	CWorld* world = theApp.GetWorld();

	rootItem = m_treeWorld.InsertItem( _T("World") );
	m_treeWorld.SetItemState (rootItem, TVIS_BOLD, TVIS_BOLD);
	m_treeWorld.Expand( rootItem, TVE_EXPAND );
	

	m_sizeBitmap.LoadBitmap(IDB_BITMAP_WORLDTREEICON);
	m_sizeImageList.Create(16, 15, ILC_COLOR16, 2, 1);
	m_sizeImageList.Add(&m_sizeBitmap, RGB(0,255,0));
	m_treeWorld.SetImageList(&m_sizeImageList,LVSIL_NORMAL);
	m_tileNavigation.Init( IDC_TILE_NAVIGATION, this );
//	m_tileNavigation.SetTexture( "Data\\Texture\\Terrain\\xuedi", "plan_xuedi005.dds" );
	m_tileNavigation.ShowGrid( false );
	
	m_sliderHeightScale.SetRangeMax(200);
	m_sliderHeightScale.SetRangeMin(1);
	m_sliderHeightScale.SetTicFreq(20);
	m_sliderHeightScale.SetPos(m_sliderHeightPos);

	m_sliderSizeScale.SetRangeMax(200);
	m_sliderSizeScale.SetRangeMin(1);
	m_sliderSizeScale.SetTicFreq(20);
	m_sliderSizeScale.SetPos(m_sliderSizePos);

	m_sliderMeshHeight.SetRange(0, 100);
	m_sliderSizeScale.SetRangeMin(1);
	m_sliderSizeScale.SetTicFreq(20);
	m_sliderSizeScale.SetPos(m_nMeshHeight);

	UpdateData(FALSE);
	return TRUE;
}

void CToolWorld::OnBtnRefresh()
{
	if( CWorldEditDoc::GetActiveMapDoc()->IsModified() ) 
	{
		::AfxMessageBox( _T("必须保存修改后才可刷新!") );
		return;
	}
	if (!theApp.GetWorld()->HasName())
	{
		::AfxMessageBox( _T("请先打开地图数据目录!") );
		return;
	}
	CWorld* world = theApp.GetWorld();
	CStringA	worldPath(world->GetWorldPath());
	Assert( NULL != world );
	world->Reset();
	CWorldEditDoc::GetActiveMapDoc()->Reset();
	if( !world->Load( worldPath ) ) {
		::AfxMessageBox( _T("载入文件出错!") );
		return;
	}
	Reset();
	UpdateTree(worldPath);
}

void CToolWorld::OnBtnNewFolder()
{
	CString strPath;
	if (!theApp.GetWorld()->HasName())
	{
		strPath.Format( _T("%s\\Data\\EditWorld"), CWorld::GetAppDataCharDir() );
	}
	else
	{
		if (NULL == m_treeWorld.GetSelectedItem())
		{
			::AfxMessageBox( _T("必须选择某个节点后才可新建目录!") );
			return;
		}
		else
		{
			GetCurrentPath(strPath);
		}

	}
	strPath.MakeLower();
	CString strYourCaption(_T("新建目录"));
	CString strYourTitle(_T("请在文字编辑框结尾处，当前目录后加‘\\’后，输入新建目录名"));


	CPathDialog dlg(strYourCaption, strYourTitle, strPath);

	if(dlg.DoModal()==IDOK)
	{
		 CString newFoler = dlg.GetPathName();
		 newFoler.MakeLower();
 		 sInt32 pos = newFoler.Find(strPath);
		 if(0 != pos)
		 {
			 ::AfxMessageBox( _T("必须在当前目录下新建目录!") );
			 return;
		 }
		 CString folderName = newFoler.Mid(strPath.GetLength());

		 HTREEITEM newItem = NULL;
		 if (!theApp.GetWorld()->HasName())
		 {
			 m_treeWorld.DeleteAllItems();
			 newItem = m_treeWorld.InsertItem( folderName );
			 CStringA charFolder;
			 charFolder.Format("%S",newFoler);
			 theApp.GetWorld()->Load(charFolder);
		 }
		 else
		 {
			 HTREEITEM selItem = GetCurrSelFoler();
			 HTREEITEM childItem = m_treeWorld.GetNextItem(selItem,TVGN_CHILD);
			 while(NULL != childItem)
			 {
				 if (s_DIRECTORY == m_treeWorld.GetItemData(childItem))
				 {
					 if (folderName == m_treeWorld.GetItemText(childItem))
					 {
						 m_treeWorld.SetCheck(childItem);
						 ::AfxMessageBox( _T("此目录已经存在了!") );
						 return;
					 }
				 }
				 childItem = m_treeWorld.GetNextItem(selItem,TVGN_NEXT);
			 }
			 HTREEITEM newItem	= m_treeWorld.InsertItem ( folderName, 1, 1,selItem );
		 }

		 m_treeWorld.SetItemData( newItem, s_DIRECTORY );
		 m_treeWorld.SetItemImage(newItem,0,0);
		 EnumWTDFile(newFoler,newItem);
	}

	// 刷新
	OnBtnRefresh();
}


void CToolWorld::OnBtnNewtile()
{
	if (!theApp.GetWorld()->IsActive())
	{
		theApp.GetWorldEditor()->NewWorld();
	}

	if (!theApp.GetWorld()->HasName())
	{
		::AfxMessageBox( _T("请先选择地图数据目录!") );
		return;
	}
	else
	{
		if (NULL == m_treeWorld.GetSelectedItem())
		{
			::AfxMessageBox( _T("必须选择某个节点后才可新建tile!") );
			return;
		}
	}

	CNewWtdFileDlg dlg;
	CString currPath;
	GetCurrentPath(currPath);
	dlg.SetCurrPath(currPath);
	if( IDOK == dlg.DoModal() )	
	{
		CString tileName = currPath;
		tileName +=  dlg.GetTileName();
		
		char workPathName[MAX_PATH*2];

		GetRelativePathToWorldPath(tileName,workPathName);
		
		const CImage* image = NULL;
		if( dlg.HasHeightmap() ) 
		{
			image = dlg.GetHeightmap();
		}
		CWorldTile* pTile = NULL;
		if(pTile = theApp.GetWorldEditor()->NewTile( workPathName, dlg.GetBaseTexture(), dlg.GetHeight(),dlg.GetTileRow(),dlg.GetTileHeight(), dlg.GetHeightMapUnit(), image, this ) ) 
		{
			//::AfxMessageBox( _T("创建成功!") );
			CWorldEditDoc::GetActiveMapDoc()->Reset();
			m_tile = pTile->GetMapId();
			AddTile(tileName );
		}
		else 
		{
			::AfxMessageBox( _T("创建失败，请检察是否已经存在!") );
		}
	}
}

bool DeleteDirectory(CString sDirName) 
{ 
	CFileFind tempFind; 
	char sTempFileFind[200] ;

	sprintf(sTempFileFind,"%s\*.*",sDirName); 
	BOOL IsFinded = tempFind.FindFile(sTempFileFind); 
	while (IsFinded) 
	{ 
		IsFinded = tempFind.FindNextFile(); 

		if (!tempFind.IsDots()) 
		{ 
			char sFoundFileName[200]; 
			strcpy(sFoundFileName,tempFind.GetFileName().GetBuffer(200)); 

			if (tempFind.IsDirectory()) 
			{ 
				char sTempDir[200]; 
				sprintf(sTempDir,"%s\%s",sDirName,sFoundFileName); 
				DeleteDirectory(sTempDir); 
			} 
			else 
			{ 
				char sTempFileName[200]; 
				sprintf(sTempFileName,"%s\%s",sDirName,sFoundFileName); 
				DeleteFile(sTempFileName); 
			} 
		} 
	} 
	tempFind.Close(); 
	if(!RemoveDirectory(sDirName)) 
	{ 
		return FALSE; 
	} 
	return TRUE; 
} 

void CToolWorld::OnBtnDelTile()
{
	HTREEITEM selItem	= m_treeWorld.GetSelectedItem();
	if( NULL == selItem )
		return;
	
	HTREEITEM rootItem	= m_treeWorld.GetRootItem();

	if( rootItem != selItem ) {
		uInt32 tileId	= m_treeWorld.GetItemData( selItem );

		if (s_DIRECTORY == tileId)
		{
			CString prompt;
			prompt.Format( _T("是否删除该文件夹[%s]以及下面所有保存的Tiles？"), m_treeWorld.GetItemText(selItem));
			int sel = ::AfxMessageBox( prompt, MB_YESNOCANCEL );
			if( sel == IDYES ) {
				CString folderPath;
				GetCurrentPath(folderPath);

				DeleteDirectory(folderPath);

				m_treeWorld.DeleteItem( selItem );
				UpdateData( FALSE );
			}
		}
		else
		{
			CString prompt;
			prompt.Format( _T("是否删除Tile[%s]？"), m_treeWorld.GetItemText(selItem));
			int sel = ::AfxMessageBox( prompt, MB_YESNOCANCEL );
			if( sel == IDYES ) {
				theApp.GetWorldEditor()->DeleteTile(tileId);

				m_treeWorld.DeleteItem( selItem );
				UpdateData( FALSE );
			}
		}
				
	}
}

void CToolWorld::OnDbClkTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR; 

	HTREEITEM selItem	= m_treeWorld.GetSelectedItem();
	if( NULL == selItem )
		return;

	m_tile	= m_treeWorld.GetItemData( selItem );
	if (s_DIRECTORY != m_tile)
	{
// 		CString name;
// 		GetCurrentName(name,false);
// 		char strName[MAX_PATH*2];
// 
// 		SwPublicFunc::TChar2MutiChar( strName, MAX_PATH*2*sizeof(char), name, (name.GetLength()+1)*sizeof(TCHAR) );
		CWorldTile* pTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tile);
		if( pTile )
		{
			theApp.GetWorld()->GetWorldBuffer()->SetActiveTile(pTile);
			RefreshByTile(CURRENTTILE);
			CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->ResetCamera();
		}
	}
}

void CToolWorld::OnRClkTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR; 
	

	CPoint pt;
	GetCursorPos( &pt );
	m_treeWorld.ScreenToClient( &pt );
	
	HTREEITEM selItem = m_treeWorld.HitTest( pt );
	//HTREEITEM selItem	= m_treeWorld.GetSelectedItem();
	if( NULL == selItem )
		return;
	
	m_tile = m_treeWorld.GetItemData( selItem );
	if( s_DIRECTORY != m_tile ) {

		CPoint point;
		GetCursorPos(&point);

		CMenu menu;
		VERIFY(menu.LoadMenu( IDR_LIST_TILE_MENU ) );
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		NMITEMACTIVATE * pNMItemActivate = (NMITEMACTIVATE  *)pNMHDR;

		pPopup->TrackPopupMenu( TPM_NONOTIFY | TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
	}
	*pResult = 0;
}

void CToolWorld::OnChkShowGrid()
{
	m_tileNavigation.ShowGrid( !m_tileNavigation.IsShowGrid() );
	UpdateMinimap();
	UpdateData( FALSE );
}

void CToolWorld::UpdateMinimap()
{
	if (IsWindowVisible())
	{
		if( NULL == theApp.GetWorld() )
			return;

		if( !theApp.GetWorld()->HasName() )
			return;

		if(-1 == m_tile)
			return;

		CWorldTile* selTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tile);

		if(NULL == selTile || !selTile->IsLoad())
		{
			return;
		}
		m_tileNavigation.UpdateMinimap();
	}
}

void CToolWorld::UpdateWorldTree( sInt32 tileId)
{
	HTREEITEM selItem = FindTile(tileId);
	
	if( NULL != selItem ) {
		m_treeWorld.SelectItem( selItem );
		UpdateData( FALSE );
	}
}

void CToolWorld::SetTilePrompt( const TCHAR* strPmpt )
{
	GetDlgItem( IDC_TILE_PROMPT )->SetWindowText( strPmpt );

	UpdateData( FALSE );
}

void CToolWorld::OnListMenuConvert2GameMap()
{
	if( NULL == theApp.GetWorld() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	CWorldTile* selTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tile);

	if(NULL == selTile || !selTile->IsLoad())
	{
		return;
	}
// 	CString name;
// 	HTREEITEM selItem	= m_treeWorld.GetSelectedItem();
// 	name = m_treeWorld.GetItemText(selItem);
// 	CString filePath;
// 	GetCurrentPath(filePath,false);
// 	CStringA filename;
// 	filename.Format( "%s\\world\\%S\\%S.map", CWorld::GetAppDataCharDir(),filePath,name);
	CWorldWriteStream* stream = new CWorldWriteStream( theApp.GetWorld() );
	stream->WriteGameWtd(selTile);
	SAFE_DELETE( stream );


}

void CToolWorld::OnListMenuReachableMap()
{
	if( NULL == theApp.GetWorld() )
		return;

	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	_beginthreadex(0, 0, CToolWorld::GenerateReachableMapThreadProc, this, 0, 0);
}

void CToolWorld::OnListMenuSnapMinimap()
{
	if( NULL == g_render )
		return;

	if( NULL == theApp.GetWorld() )
		return;

	if( !theApp.GetWorld()->IsActive() )
		return;
	
	if( !theApp.GetWorld()->HasName() )
		return;

	CSnapMinimapDlg dlg;

	CString name;
	HTREEITEM selItem	= m_treeWorld.GetSelectedItem();
	name = m_treeWorld.GetItemText(selItem);
	name.Mid(name.ReverseFind(_T('.')));
	dlg.m_tileName = name;

	CWorldTile* pTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tile);
	dlg.m_tile = pTile;
	if( IDOK == dlg.DoModal() ) 
	{
		CWorldWriteStream stream( theApp.GetWorld() );
		if (stream.RemoveReadOnly(dlg.m_fileName))
		{
			// 生成Minimap
			g_render->GenerateMinimap( pTile, 1024, dlg.m_fileName );
			CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera()->SetPos(CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera()->GetPos());
		}
	}
}

void CToolWorld::OnListMenuReplaceTileTexture()
{
	if( NULL == g_render )
		return;

	if( NULL == theApp.GetWorld() )
		return;

	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	CReplaceTileTextureDlg dlg;
	if( IDOK == dlg.DoModal() ) {
		theApp.GetWorldEditor()->ResetTileTexture( dlg.m_textureName, m_tile );
	}
}

void CToolWorld::OnListMenuCleanModel()
{
	if( NULL == g_render )
		return;

	if( NULL == theApp.GetWorld() )
		return;

	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	int sel = ::AfxMessageBox( _T("是否进行模型优化?请备份好数据.\n\n是否继续?"), MB_YESNO );
	if( sel == IDYES ) {
		
		theApp.GetWorldEditor()->CleanUnusedModel( m_tile );
//		theApp.GetWorldEditor()->CleanStaticModel( m_tile );//合并入CleanUnusedModel
		
		::AfxMessageBox( _T("清理完毕!") );
	}
}

void CToolWorld::EnumWTDFile( CString& strDir,HTREEITEM rootItem )
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

			HTREEITEM newItem	= m_treeWorld.InsertItem ( worldName, 1, 1,rootItem );
			m_treeWorld.SetItemData( newItem, s_DIRECTORY );
			m_treeWorld.SetItemImage(newItem,0,0);
			EnumWTDFile(strPath,newItem);
		}
		else //if (ff.IsArchived()) 
		{
			int nfindPos = strPath.Find(_T(".mew"));
			if(-1 == nfindPos || (nfindPos != strPath.GetLength() - 4 )) 
			{
				continue;
			}
			AddChildLeafNode(strPath, rootItem);
		}
	}	

}

HTREEITEM CToolWorld::FindTile( sInt32 tileHash )
{
	HTREEITEM rootItem	= m_treeWorld.GetRootItem();
	return FindTile(tileHash,rootItem);

}

HTREEITEM CToolWorld::FindTile( sInt32 tileHash ,HTREEITEM rootItem )
{
	HTREEITEM curItem	= m_treeWorld.GetNextItem( rootItem, TVGN_CHILD );
	while( NULL != curItem ) {
		uInt32 tileId	= m_treeWorld.GetItemData( curItem );
		if (tileHash == tileId)
		{
			return curItem;
		}
		else if (s_DIRECTORY == tileId)
		{
			HTREEITEM result = FindTile(tileHash,curItem);

			if (NULL != result)
			{
				return result;
			}
		}
		curItem	= m_treeWorld.GetNextItem( curItem, TVGN_NEXT );
	}
	return NULL;

}

void CToolWorld::GetCurrentPath( CString& pPath ,bool isAbsolute)
{
	if (isAbsolute)
	{
		pPath.Format(_T("%hs"),theApp.GetWorld()->GetWorldPath()); 
		pPath += _T('\\');
	}
	CString relativePath;
	HTREEITEM selItem = GetCurrSelFoler();
	HTREEITEM rootItem	= m_treeWorld.GetRootItem();
	while (selItem != rootItem)
	{
		relativePath.Insert(0,'\\');
		relativePath.Insert(0,m_treeWorld.GetItemText(selItem));
		selItem = m_treeWorld.GetNextItem( selItem, TVGN_PARENT );
	}
	pPath += relativePath;

}

HTREEITEM CToolWorld::AddChildLeafNode( CString strPath, HTREEITEM rootItem )
{
	
	CString worldName = strPath.Mid(strPath.ReverseFind('\\') + 1 );
	sInt32 pos				= worldName.Find(_T(".mew"));
	if( -1 != pos )
		worldName		= worldName.Left( pos );
	HTREEITEM newItem	= m_treeWorld.InsertItem ( worldName, 1, 1,rootItem );

	char workPathName[MAX_PATH*2];
	GetRelativePathToWorldPath(strPath,workPathName);
	CWorldTile* pTile = theApp.GetWorld()->m_worldBuffer->GetTileFromPath(workPathName);
	m_treeWorld.SetItemData( newItem, pTile->GetMapId() );
	return newItem;
}

void CToolWorld::GetCurrentName( CString& name, bool isAbsolute)
{
	GetCurrentPath(name,isAbsolute);
	HTREEITEM selItem	= m_treeWorld.GetSelectedItem();
	name += m_treeWorld.GetItemText(selItem);
	name += _T(".mew");
}


HTREEITEM CToolWorld::GetCurrSelFoler()
{
	HTREEITEM selItem	= m_treeWorld.GetSelectedItem();
	uInt32 tileId	= m_treeWorld.GetItemData( selItem );
	if (s_DIRECTORY != tileId)
	{
		selItem = m_treeWorld.GetNextItem( selItem, TVGN_PARENT );
	}
	return selItem;
}

void CToolWorld::DeleteWTDFiles( CString& strDir )
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
			DeleteWTDFiles(strPath);
			RemoveDirectory(strDir);
		}
		else //if (ff.IsArchived()) 
		{
			if( -1 != strPath.Find(_T(".mew")) ) 
			{
				char workPathName[MAX_PATH*2];
				GetRelativePathToWorldPath(strPath,workPathName);
				CWorldTile* pTile = theApp.GetWorld()->GetWorldBuffer()->GetTileFromPath(workPathName);
				if (pTile == NULL)
					return;

				theApp.GetWorldEditor()->DeleteTile(pTile->GetMapId());
			}
			else
			{
				SetFileAttributes(strPath,FILE_ATTRIBUTE_NORMAL);
				int nRet = DeleteFile(strPath);
// 				if (0 == nRet)
// 				{
// 					uInt32 lastError = GetLastError();
// 				}
			}
		}
	}	
}

unsigned int __stdcall CToolWorld::GenerateReachableMapThreadProc(void *args)
{
	CToolWorld *pToolWorld = reinterpret_cast<CToolWorld *>(args);
	if (pToolWorld == NULL)
		return 1;

	CWorldTile *selTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(pToolWorld->m_tile);
	if (NULL == selTile || !selTile->IsLoad())
		return 1;

	char mapPath[MAX_PATH] = {0};
	
	CString mapFolder = SwGlobal::GetWorld()->GetWorldPath();
	int pos = mapFolder.Find(".mew");
	if (pos != -1)
	{
		mapFolder = mapFolder.Left(pos);
	}

	pos = mapFolder.ReverseFind('\\');
	CString mapName = mapFolder.Right(mapFolder.GetLength() - pos - 1);

	sprintf_s(mapPath, MAX_PATH, "%s\\%s.map", mapFolder, mapName);

	CReachableMapGenerate::Instance()->GenerateFile(pToolWorld->m_tile, g_reachableMapScale, mapPath);
	return 0;
}

void CToolWorld::OnNMCustomdrawSliderHeightscale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nPos = m_sliderHeightScale.GetPos();
	if (m_sliderHeightPos != nPos)
	{
		m_sliderHeightPos = nPos;
		UpdateHeightScale(nPos);
		m_tileNavigation.UpdateMinimap();
	}
}

void CToolWorld::OnNMCustomdrawSliderSizescale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	int nPos = m_sliderSizeScale.GetPos();
	if (m_sliderSizePos != nPos)
	{
		m_tileNavigation.m_sizeScale = (nPos)*0.01f;
		CString strValue;
		strValue.Format(_T("%4.2f"),m_tileNavigation.m_sizeScale);
		m_textSizeScale.SetWindowText(strValue);
		m_tileNavigation.UpdateMinimap();
	}
}

void CToolWorld::OnKillfocusReachableAngle()
{
	UpdateData();

	CString strAngle;
	m_editReachableAngle.GetWindowText( strAngle );
	if (strAngle.IsEmpty())
	{
		return;
	}
	flt32 angle	= _tstof( strAngle );
	angle = ZnMin<flt32>(angle,60.f);
	angle = ZnMax<flt32>(angle,0.f);
	strAngle.Format( _T("%8.2f"), angle );
	m_editReachableAngle.SetWindowText( strAngle );
	CWorldTile* pTile = CURRENTTILE;
	if (pTile)
	{
		pTile->SetReachableAngle(angle);
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( pTile );
		m_tileNavigation.UpdateMinimap();
	}

}

void CToolWorld::OnChkReachable()
{
	m_tileNavigation.ShowReachable( !m_tileNavigation.IsShowReachable() );
	UpdateMinimap();
	UpdateData( FALSE );

}

bool CToolWorld::RefreshByTile( CWorldTile* pTile )
{
	CString strAngle ;
	strAngle.Format( _T("%8.2f"), pTile->GetReachableAngle() );
	m_editReachableAngle.SetWindowText( strAngle );
	flt32 deltaHeight = (pTile->GetHeight()[1] - pTile->GetHeight()[0])/255;
	if (deltaHeight > 2.0f)
	{
		deltaHeight = 2.0f;
	}
	m_sliderHeightPos = ZnFloor2Int(deltaHeight*100);
	m_sliderHeightScale.SetPos(m_sliderHeightPos);
	UpdateHeightScale(m_sliderHeightPos);
// 	CString strName(pTile->GetTileName());
	//m_edit_ChineseName.SetWindowText(pTile->GetTileName());
	//m_check_ShowFootPrint.SetCheck(pTile->GetShowFootPrint());
	return true;
}

void CToolWorld::UpdateHeightScale( int nPos )
{
	m_tileNavigation.m_heightScale = (nPos)*0.01f;
	CString strValue;
	strValue.Format(_T("%4.2f"),m_tileNavigation.m_heightScale);
	m_textHeightScale.SetWindowText(strValue);
}


void CToolWorld::OnEnKillfocusEditChinesename()
{
	CString strName;
	m_edit_ChineseName.GetWindowText( strName );
	if (strName.IsEmpty())
	{
		return;
	}
	CWorldTile* pTile = CURRENTTILE;
	if (pTile)
	{
		pTile->SetTileName(strName);
		CWorldEditDoc::GetActiveMapDoc()->AddTileModify( pTile );
	}

}

#include "MeTerrain/MonsterFile.h"
void CToolWorld::OnListMenuMonsterData()
{
	if( NULL == theApp.GetWorld() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	CWorldTile* selTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tile);

	if(NULL == selTile || !selTile->IsLoad())
	{
		return;
	}
	const unsigned char* reachableData = NULL;
	if (!selTile->IsLoadReachableMap())
	{
		CReachableMapGenerate::Instance()->ReadInReachableData(selTile);
	}
	{
		reachableData = selTile->ReachableMap().GetMapData();
	}
// 	unsigned char* reachableData = CReachableMapGenerate::Instance()->ReadInReachableData(selTile);
	if (NULL == reachableData)
	{
		return;
	}
	CResEditMgr* resMgr = (CResEditMgr*)selTile->GetCResMgr();
	for (int i = 0; i < resMgr->GetMonsterQuadCount(); ++i)
	{
		CMonsterQuadRes* pRes = resMgr->MonsterQuad(i);
		//pRes->RefreshMonsterPoint(selTile,reachableData);
	}

	char gameMapPath[MAX_PATH];
	memset(gameMapPath,0,MAX_PATH);
	GetGameWtdFileName(selTile->GetPathName(),gameMapPath);
// 	pFind[1] = 'm';
// 	pFind[2] = 'o';
// 	pFind[3] = 'n';


	CWorldWriteStream* stream = new CWorldWriteStream( theApp.GetWorld() );
	stream->WriteMonsterData(selTile,gameMapPath);
	SAFE_DELETE( stream );
}

void CToolWorld::OnListMenuCalPFWeight()
{
	if( NULL == g_render )
		return;

	if( NULL == theApp.GetWorld() )
		return;

	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;
	CWorldTile* selTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tile);
	if (selTile->CalPFWeight())
	{
		CMapConfigXml::Instance()->RefreshTileMapInfo(selTile);
	}
	else
	{
		::AfxMessageBox( _T("不能打开寻路地图，权重计算失败!") );
	}
}

void CToolWorld::OnListMenuWaterMap()
{
	if( NULL == g_render )
		return;

	if( NULL == theApp.GetWorld() )
		return;

	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;
	CWorldTile* selTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tile);

	if(NULL == selTile || !selTile->IsLoad())
	{
		return;
	}

	char gameMapPath[MAX_PATH];
	GetGameWtdFileName(selTile->GetPathName(),gameMapPath);
	_strlwr(gameMapPath);
// 	char* pFind = strstr(gameMapPath,"\\mew\\");
// 	if (pFind)
// 	{
// 		pFind[1] = 'm';
// 		pFind[2] = 'o';
// 		pFind[3] = 'n';
// 	}
// 	pFind = strstr(gameMapPath,".mew");
// 	pFind[0] = '\0';
// 	WIN32_FIND_DATAA data;
// 	HANDLE hFind = FindFirstFileA(gameMapPath,&data);
// 	bool bFind = (hFind != INVALID_HANDLE_VALUE);
// 	if (!bFind)
// 	{
// 		CreateDirectoryA(gameMapPath,NULL);
// 	}

	char* pFind = strstr(gameMapPath,".mew");;
	char waterfile[] = ".water";
	memcpy(pFind,waterfile,strlen(waterfile) + 1);
	CWorldWriteStream stream(theApp.GetWorld());
	if (!stream.RemoveReadOnly(gameMapPath))
	{
		return ;
	}
	CReachableMapGenerate::Instance()->GenerateWaterMap(m_tile,g_reachableMapScale,gameMapPath);
}

void CToolWorld::OnListMenuHeightMap()
{
	if( NULL == g_render )
		return;

	if( NULL == theApp.GetWorld() )
		return;

	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;
	CWorldTile* selTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tile);

	if(NULL == selTile || !selTile->IsLoad())
	{
		return;
	}

	char gameMapPath[MAX_PATH];	
	GetGameWtdFileName(selTile->GetPathName(),gameMapPath);
	_strlwr(gameMapPath);

	std::string strPath = gameMapPath;
	int nPos = strPath.find_last_of("\\");
	if(nPos == -1)
		return;

	std::string sub = strPath.substr(0,nPos);
	sub += "\\MapHeight.height";
// 	char* pFind = strstr(gameMapPath,".mew");
// 	strcpy(&pFind[0],"\\MapHeight.height");

	CReachableMapGenerate::Instance()->GenerateHeightMap(m_tile, g_reachableMapScale, sub.c_str()/*gameMapPath*/);
}

void CToolWorld::OnListMenuMapModels()
{
	CMapModelsDlg dlg;
	dlg.DoModal();
}

void CToolWorld::OnBnClickedChkShowfootprint()
{
	if( NULL == theApp.GetWorld() )
		return;

	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;
	CWorldTile* selTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tile);

	if(NULL == selTile || !selTile->IsLoad())
	{
		return;
	}
	bool bShow = ( BST_CHECKED == m_check_ShowFootPrint.GetCheck() ) ;
	selTile->SetShowFootPrint(bShow);
}

void CToolWorld::OnListMenuSnapBBoxMinimap()
{
    GetMe3dConfig()->SetRenderBBox(TRUE);
    if( NULL == g_render )
        return;

    if( NULL == theApp.GetWorld() )
        return;

    if( !theApp.GetWorld()->IsActive() )
        return;

    if( !theApp.GetWorld()->HasName() )
        return;

    CSnapMinimapDlg dlg;

    CString name;
    HTREEITEM selItem	= m_treeWorld.GetSelectedItem();
    name = m_treeWorld.GetItemText(selItem);
    name.Mid(name.ReverseFind(_T('.')));
    dlg.m_tileName = name + "_bbox";
	CWorldTile* pTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tile);
	dlg.m_tile = pTile;
    if( IDOK == dlg.DoModal() ) 
    {
        CWorldWriteStream stream( theApp.GetWorld() );
        if (stream.RemoveReadOnly(dlg.m_fileName))
        {
            g_render->GenerateMinimap( pTile, 1024, dlg.m_fileName );
			CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera()->SetPos(CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera()->GetPos());
        }
    }
    GetMe3dConfig()->SetRenderBBox(FALSE);
}


void CToolWorld::OnBnClickedButtonWorldattr()
{
	// TODO: Add your control notification handler code here

	WorldAttribute xWorldAttribute;

	xWorldAttribute.DoModal();
}

void CToolWorld::OnBnClickedButtonSetMesh()
{
	CWorldTile* pTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tile);
	if (!pTile)
	{
		return;
	}
	g_render->SetMesh(false);
	CString str;
	m_editMesh.GetWindowText(str);
	if (str.IsEmpty())
	{
		return;
	}
	float percent = float(m_nMeshHeight) / 100.f;
	sInt32 nLength = _tstof(str);
	((CResEditMgr*)pTile->GetCResMgr())->SetMeshRes(m_tile, nLength, percent);
	g_render->SetMesh(true);
}

void CToolWorld::OnMeshHeightSizescale(NMHDR *pNMHDR, LRESULT *pResult)
{
	CWorldTile* pTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tile);
	if (!pTile)
	{
		return;
	}
	g_render->SetMesh(false);
	CString str;
	m_editMesh.GetWindowText(str);
	if (str.IsEmpty())
	{
		return;
	}
	m_nMeshHeight = m_sliderMeshHeight.GetPos();
	float percent = float(m_nMeshHeight) / 100.f;
	sInt32 nLength = _tstof(str);
	((CResEditMgr*)pTile->GetCResMgr())->SetMeshRes(m_tile, nLength, percent);
	g_render->SetMesh(true);
}

void CToolWorld::OnBnClickedButtonContrast()
{
	float fC = PostProcessManager::instance().GetBrightness();
	D3DXVECTOR3 kB = PostProcessManager::instance().GetContrast();

	if ( s_dlgMapContrast == NULL )
	{
		s_dlgMapContrast = new MapContrastDlg;
		s_dlgMapContrast->Create( IDD_DIALOG_CONTRAST, this );
	}
	s_dlgMapContrast->m_tileId = m_tile;
	s_dlgMapContrast->SetSLDValue( kB.x, kB.y, kB.z, fC );
	s_dlgMapContrast->ShowWindow( SW_SHOW );
	// TODO: Add your control notification handler code here
}

void CToolWorld::OnBnClickedButtonBloom()
{
	D3DXVECTOR4 kScale = *PostProcessManager::instance().getParameterVector4( "BloomScale" );
	D3DXVECTOR4 kLumi = *PostProcessManager::instance().getParameterVector4( "Luminance" );
	if( s_dlgMapBloom == NULL )
	{
		s_dlgMapBloom = new MapBloomDlg;
		s_dlgMapBloom->Create( IDD_DIALOG_BLOOM, this );
	}
	s_dlgMapBloom->SetTitleId( m_tile );
	s_dlgMapBloom->SetBloomValue( kScale.x, kLumi.x );
	s_dlgMapBloom->ShowWindow( SW_SHOW );
}

void CToolWorld::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	switch (nSBCode)
	{
	case SB_LINEUP:
		Scroll_LineUpDown(-10);
		break;

	case SB_LINEDOWN:
		Scroll_LineUpDown(10);
		break;

	case SB_THUMBTRACK:
		Scroll_To(nPos);
		break;
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CToolWorld::OnSize(UINT nType, int cx, int cy)
{
	ScrollableDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CRect rcClient;
	GetClientRect(&rcClient);
	Scroll_Setup(820, rcClient.Height());
}
