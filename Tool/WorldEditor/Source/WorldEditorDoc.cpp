// WorldEditDoc.cpp : implementation of the CWorldEditDoc class
//
#include "stdafx.h"
#include "RapidXml/MeRapidXml.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "Map/WorldWriteStream.h"
#include "Ndl/NdlWorldEditor.h"

#include "Resource/Resource.h"
#include "ui/Custom/TexturePreviewWnd.h"
#include "ui/Custom/TextureNavigationWnd.h"
#include "Edit/BaseTool.h"

#include "ui/ToolsWnd/ToolDoodadDlg.h"
#include "ui/ToolsWnd/ToolLiquidDlg.h"
#include "ui/ToolsWnd/ToolTransportDlg.h"
#include "ui/ToolsWnd/ToolFlyRouteDlg.h"
#include "ui/ToolsWnd/MonsterQuadDlg.h"
#include "ui/ToolsWnd/ToolModel.h"
#include "ui/ToolsWnd/ToolLayer.h"
#include "ui/ToolsWnd/ToolTerrain.h"
#include "ui/ToolsScene/ToolClickToAddDlg.h"
#include "ui/View/ToolsCreate.h"
#include "ui/ToolsScene/ToolWorld.h"
#include "ui/ToolsScene/ToolEnvironment.h"
#include "ui/ToolsScene/ToolWorldLight.h"
#include "ui/ToolsScene/ToolWorldFog.h"
#include "ui/ToolsScene/ToolZoneDlg.h"

#include "ui/View/ToolsScene.h"
#include "ui/View/ToolsModify.h"
#include "ui/View/ToolsTabView.h"

#include "ui/Dlg/ServerMapDlg.h"
//#include "Map/ServerMapStream.h"

#include "WorldEditor.h"
#include "WorldEditorDoc.h"
#include "WorldEditorView.h"

#include <algorithm>
#include <Mmsystem.h>
#include "ui/Custom/PathDialog.h"
#include "MeTerrain/MapConfigXml.h"
// #include "MeTerrain/FlyRouteXml.h"
#include "MeTerrain/SoundPointXml.h"
#include "ui/dlg/WTDMergeDlg.h"
#include "ui/dlg/WTDSplitDlg.h"
#include "Utility.h"

// CWorldEditDoc
CWorldEditDoc* CWorldEditDoc::m_activeMapDoc	= NULL;

IMPLEMENT_DYNCREATE(CWorldEditDoc, CDocument)

BEGIN_MESSAGE_MAP(CWorldEditDoc, CDocument)
	ON_COMMAND(ID_FILE_NEW, &CWorldEditDoc::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWorldEditDoc::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CWorldEditDoc::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CWorldEditDoc::OnFileSaveAs)
	ON_COMMAND(ID_FILE_MERGETILE, &CWorldEditDoc::OnMergeTiles)
	ON_COMMAND(ID_FILE_SPLITTILE, &CWorldEditDoc::OnSplitTiles)
END_MESSAGE_MAP()


// CWorldEditDoc construction/destruction

CWorldEditDoc::CWorldEditDoc()
{
	// 单文档
	m_activeMapDoc	= this;
	m_mainView		= NULL;
	m_toolsView		= NULL;

	m_currentTime	= 0.0f;
	m_totalTime		= 0.0f;
}

CWorldEditDoc::~CWorldEditDoc()
{
	m_activeMapDoc	= NULL;
	m_mainView		= NULL;
	m_toolsView		= NULL;
}

void CWorldEditDoc::SetWorldModify()
{
	SetModifiedFlag();
}

void CWorldEditDoc::AddTileModify( CWorldTile* worldTile )
{
	bool bFound = false;
	std::vector<uInt32>::iterator it = m_dirtyTileList.begin();
	while(it != m_dirtyTileList.end())
	{
		CWorldTile* pTile = theApp.GetWorld()->m_worldBuffer->GetTile( *it );
		if(pTile == worldTile)
		{
			bFound = true;
		}
		++it;
	}
	if( !bFound ) {

		worldTile->SetModify(true);
		uInt32 tileId = worldTile->GetMapId();
		m_dirtyTileList.push_back( tileId );
	}
	SetModifiedFlag();
}

void CWorldEditDoc::AddTileModify( uInt32 tileId)
{

	std::vector<uInt32>::iterator it = std::find( m_dirtyTileList.begin(), m_dirtyTileList.end(), tileId );
	if( it == m_dirtyTileList.end() ) {

		CWorldTile* worldTile = theApp.GetWorld()->m_worldBuffer->GetTile( tileId );
		Assert( NULL != worldTile );
		worldTile->m_isModify = true;

		m_dirtyTileList.push_back( tileId );
	}
	SetModifiedFlag();
}

void CWorldEditDoc::ClearTileModify( uInt32 tileId)
{

	std::vector<uInt32>::iterator it = std::find( m_dirtyTileList.begin(), m_dirtyTileList.end(), tileId );
	if( it != m_dirtyTileList.end() ) {
		CWorldTile* worldTile = theApp.GetWorld()->m_worldBuffer->GetTile( tileId );
		Assert( NULL != worldTile );
		worldTile->SetModify(false);
		m_dirtyTileList.erase( it );
		if( m_dirtyTileList.size() == 0 )
			SetModifiedFlag( FALSE );
	}
}

void CWorldEditDoc::ClearTileModify()
{
	for( size_t i=0; i<m_dirtyTileList.size(); i++ ) {
		uInt32 tileId	= m_dirtyTileList[i];

		CWorldTile* worldTile = theApp.GetWorld()->m_worldBuffer->GetTile( tileId);
		Assert( NULL != worldTile );
		worldTile->SetModify(false);
	}

	m_dirtyTileList.clear();
	SetModifiedFlag( FALSE );
}

BOOL CWorldEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

BOOL CWorldEditDoc::OnOpenDocument(LPCTSTR lpszPathName)
{



	return TRUE;
}


void CWorldEditDoc::OnFileNew()
{
	//CNdlWorldEditor* editor = theApp.GetWorldEditor();
	//Assert( NULL != editor );
	//
	//if( this->IsModified() ) {
	//	int sel = ::AfxMessageBox( _T("原来文件已经更改，是否保存原来文件？"), MB_YESNOCANCEL );
	//	if( sel == IDYES ) {
	//		// m_activeView;
	//	}
	//	else if( sel == IDNO ) {
	//		
	//	}
	//	// Cancel
	//	else {
	//		return;
	//	}
	//}
	//CNewWorldDlg	dlg;
	//if( IDOK == dlg.DoModal() )	{
	//	char name[WORLD_NAME_LEN], path[MAX_PATH];
	//	dlg.GetWorldPath( path );
	//	dlg.GetWorldName( name );
	//	
	//	theApp.GetWorldEditor()->NewWorld( path, name );
	//	
	//	CString title;
	//	title.Format( _T("%hs\\%hs"), path, name );
	//	SetTitle( title );
	//	
	//	SetModifiedFlag();
	//}
}

LPITEMIDLIST ParsePidlFromPath(LPCSTR path)
{    
	OLECHAR szOleChar[MAX_PATH];    
	LPSHELLFOLDER IpsfDeskTop;    
	LPITEMIDLIST lpifq;    
	ULONG ulEaten, ulAttribs;    
	HRESULT hres;    
	SHGetDesktopFolder(&IpsfDeskTop);    
	MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED, path, -1, szOleChar,sizeof(szOleChar));
	hres = IpsfDeskTop ->ParseDisplayName(NULL, NULL, szOleChar, &ulEaten, &lpifq, &ulAttribs);    
	hres = IpsfDeskTop->Release( );        
	if (FAILED(hres))
		return NULL;
	return lpifq;
}

void CWorldEditDoc::OnFileOpen()
{
	CString strPath;
	strPath.Format(_T("%s\\Data\\World"), CWorld::GetAppDataCharDir());
	strPath.MakeLower();
	CString strYourCaption(_T("打开地图目录"));
	CString strYourTitle(_T("请选择需要打开的目录"));

	CPathDialog dlg(strYourCaption, strYourTitle, strPath);
	if (dlg.DoModal() == IDOK)
	{
		// 修改过
		if (this->IsModified())
		{
			int sel = ::AfxMessageBox( _T("原来文件已经更改，是否保存原来文件？"), MB_YESNOCANCEL );
			if (sel == IDYES )
			{
				WriteDirtyTile();
			}
			else if (sel == IDNO)
			{
				ClearTileModify();
			}	
			else
			{
				return;
			}
		}

		CString fileFolder = dlg.GetPathName();

		int pos = fileFolder.ReverseFind('\\');
		CString folderName = fileFolder.Right(fileFolder.GetLength() - pos - 1);

		/*
		// 不能选择World目录
		if (folderName.Find("World") != -1)
		{
			::AfxMessageBox("不能选择World目录");
			return;
		}

		// 地图目录必须存在mew文件
		CString fileFormat;
		fileFormat.Format("%s\\*.mew", fileFolder);
		if (!Utility::IsFileExistsInFolder(fileFormat))
		{
			::AfxMessageBox("请检查您所选择的目录下是否存在mew文件");
			return;
		}
		*/

		CWorld* world = theApp.GetWorld();
		Assert( NULL != world );
		world->Reset();
		Reset();
		CStringA worldPath(fileFolder);

		if( !world->Load( worldPath ) ) {
			::AfxMessageBox( _T("载入文件出错!") );
			return;
		}
		CToolWorld& toolWorld = m_toolsView->GetToolSceneWnd().GetToolWorldWnd();
		toolWorld.Reset();
		toolWorld.UpdateTree( worldPath );
		world->SetActivePos( 0.0f, 0.0f );

		this->SetPathName( fileFolder );

		CString szRootPath(fileFolder);
		szRootPath.MakeLower();
		pos = szRootPath.Find("data");
		szRootPath = szRootPath.Left(pos);
		SetRootPath(szRootPath.GetString());
	}
}

void CWorldEditDoc::OnFileSave()
{
	WriteDirtyTile();
}

void CWorldEditDoc::OnFileSaveAs()
{
	CWorld* world = theApp.GetWorld();
	if (!world->HasName())
	{
		return;
	}
	CString strPath;
	strPath.Format( _T("%s\\Data\\EditWorld"), CWorld::GetAppDataCharDir() );
	strPath.MakeLower();
	CString strYourCaption(_T("另存为..."));
	CString strYourTitle(_T("请选择地图保存目录！\n注意：该目录的同名文件将被自动覆盖！"));


	CPathDialog dlg(strYourCaption, strYourTitle, strPath);

	if(dlg.DoModal()==IDOK)
	{
		CStringA worldPath;
		worldPath.Format("%S",dlg.GetPathName());

		//		GetRelativePathToDataPath(dlg.GetPathName(),worldPath);

		WriteWorld( worldPath);

		world->SetWorldPath( worldPath );
		SetPathName( dlg.GetPathName() );


		CToolWorld& toolWorld = m_toolsView->GetToolSceneWnd().GetToolWorldWnd();
		toolWorld.Reset();
		toolWorld.UpdateTree( worldPath );
	}

}


bool CWorldEditDoc::WriteDirtyTile( bool isPrompt )
{
	if (!this->IsModified())
	{
		if (isPrompt)
			::AfxMessageBox(_T("文件没有改变不需要保存!"));
		return true;
	}

	for (size_t i = 0; i < m_dirtyTileList.size(); ++i) 
	{
		uInt32 tileId = m_dirtyTileList[i];
		CWorldTile *pTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(tileId);
		if (WriteTile(pTile,isPrompt))
		{
			ClearTileModify(tileId);
		}
	}
	return true;
}

bool CWorldEditDoc::WriteTile( CWorldTile* cacheTile, bool isPrompt )
{
	bool canWrite = false;
	if (theApp.GetWorld()->HasName())
	{
		canWrite = true;
	}
	else
	{
		CString strPath;
		strPath.Format( _T("%s\\Data\\EditWorld"), CWorld::GetAppDataCharDir() );
		strPath.MakeLower();
		CString strYourCaption(_T("保存为..."));
		CString strYourTitle(_T("请选择地图保存目录！\n注意：该目录的同名文件将被自动覆盖！"));

		CPathDialog dlg(strYourCaption, strYourTitle, strPath);
		if (dlg.DoModal() == IDOK)
		{
			CStringA worldPath;
			worldPath.Format("%S",dlg.GetPathName());

			theApp.GetWorld()->SetWorldPath(worldPath);
			this->SetPathName(dlg.GetPathName());
			canWrite = true;
		}
	}
	if (canWrite)
	{
		CWorldWriteStream *stream = new CWorldWriteStream(theApp.GetWorld());
		// 保存到Tile的mex文件
		if (!stream->WriteTile(cacheTile))
		{
			if (isPrompt)
				::AfxMessageBox(_T("保存mew文件失败!"));

		}
		else
		{
			CString prompt;
			prompt.Format(_T("保存文件[%hs]成功!"), cacheTile->GetPathName());
			if (isPrompt)
				::AfxMessageBox(prompt);

			prompt.Format(_T("%hs"), cacheTile->GetPathName());
			this->SetPathName(prompt);
		}
		SAFE_DELETE(stream);	
	}
	else
	{
		if (isPrompt)
			::AfxMessageBox(_T("文件没有保存!"));
		return false;
	}
	return true;
}

bool CWorldEditDoc::WriteWorld( const char* worldPath )
{
	CWorldWriteStream* stream = new CWorldWriteStream( theApp.GetWorld() );

	CString prompt;
	if( stream->WriteAllTile( worldPath ) ) {
		ClearTileModify();
		prompt.Format( _T("保存文件[%hs]成功!"), worldPath );
		::AfxMessageBox( prompt );

	}
	else {
		prompt.Format( _T("保存文件[%hs]Tile失败!"), worldPath );
		::AfxMessageBox( prompt );
	}
	SAFE_DELETE( stream );

	return true;
}

bool CWorldEditDoc::WriteServerMap( const char* mapPath, const char* mapName )
{

	return true;
}

// CWorldEditDoc serialization
void CWorldEditDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// 
	}
	else
	{
		// 
	}
}


// CWorldEditDoc diagnostics

#ifdef _DEBUG
void CWorldEditDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWorldEditDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

CWorldEditDoc*	CWorldEditDoc::GetActiveMapDoc()
{
	//	Assert( NULL != m_activeMapDoc );
	return m_activeMapDoc;
}

void CWorldEditDoc::SetMainView( CWorldEditView* pView )
{
	m_mainView	= pView;
}

void CWorldEditDoc::SetToolView( CToolsTabView* pView )
{
	m_toolsView = pView;
}

void CWorldEditDoc::UpdateCurrentTime()
{

}

void CWorldEditDoc::UpdateAnimation()
// run any animation
{
	flt32 curTime	= ((flt32)timeGetTime())/1000.0f;
	flt32 deltaTime	= curTime-m_currentTime;
	m_currentTime	= curTime;
	m_totalTime		+= deltaTime;

	m_mainView->Update( m_totalTime, deltaTime );
}

void CWorldEditDoc::UpdateAllViews( CView* pSender, LPARAM lHint, CObject* pHint )
{
	CDocument::UpdateAllViews( pSender, lHint, pHint );
}

void CWorldEditDoc::Update3DViews()
// redraw the 3d views
{
	if( (NULL != m_mainView) && (!theApp.GetForceRenderNextFrame()) )	{
		//Sleep( 1 );
	}
	else {
		m_mainView->Invalidate( false );
		m_mainView->UpdateWindow();
	}
}

void CWorldEditDoc::UpdateMinimap()
{
	CToolWorld& toolWorld = m_toolsView->GetToolSceneWnd().GetToolWorldWnd();
	toolWorld.UpdateMinimap();
}

void CWorldEditDoc::OnMergeTiles()
{
	CWTDMergeDlg dlg;
	if( IDOK == dlg.DoModal() ) 
	{
		::AfxMessageBox( _T("合并成功！") );
	}
}

void CWorldEditDoc::Reset()
{
	GetWorldView()->Reset();
	m_toolsView->Reset();
}

void CWorldEditDoc::OnSplitTiles()
{
	CWTDSplitDlg dlg;
	if( IDOK == dlg.DoModal() ) 
	{
		::AfxMessageBox( _T("拆分成功！") );
	}
}