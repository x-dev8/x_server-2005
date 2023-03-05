#include <d3dx9.h>
#include <windows.h>
#include "mdx2ctrlpanel.h"
#include "resource.h"
#include "hr3d_Plugins.h"
#include "hr3d_maxinterface.h"
#include "hr3d_mdx2candidate.h"
#include "log.h"

extern HR3D_Mdx2Candidate*	g_pMdx2Candidate;
extern char g_szEditorExePath[MAX_PATH];
CMdx2CtrlPanel g_mdx2CtrlPanel;
PROCESS_INFORMATION g_pi;
BOOL g_bUseSelfRender = TRUE;

#define EXP_MDX_FILE "c:\\exptmp.mdx2"

LRESULT CALLBACK D3DViewWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   return g_mdx2CtrlPanel.MsgProc( hWnd, uMsg, wParam, lParam );
}

INT_PTR CALLBACK CtrlPanelMsgProc( HWND hDlg,UINT uMsg,	WPARAM wParam, LPARAM lParam )
{
	return g_mdx2CtrlPanel.CtrlPanelMsgProc( hDlg, uMsg, wParam, lParam );
}

INT_PTR CALLBACK AutoNamePanelMsgProc( HWND hDlg,UINT uMsg,	WPARAM wParam, LPARAM lParam )
{
	return g_mdx2CtrlPanel.AutoNamePanelMsgProc( hDlg, uMsg, wParam, lParam );
}

INT_PTR CALLBACK LogDlgMsgProc( HWND hDlg,UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return g_mdx2CtrlPanel.LogDlgMsgProc( hDlg, uMsg, wParam, lParam );
}

CMdx2CtrlPanel::~CMdx2CtrlPanel()
{
	if( m_pd3dDevice != NULL ) 
	{
		m_pd3dDevice->Release(); 
		m_pd3dDevice = NULL; 
	}

	if( m_pD3D != NULL ) 
	{
		m_pD3D->Release(); 
		m_pD3D = NULL; 
	}
	if( m_hD3DWnd )
	{
		DestroyWindow( m_hD3DWnd );
		m_hD3DWnd = NULL;
	}
	if( m_hCtrlPanel )
	{
		DestroyWindow( m_hCtrlPanel );
		m_hCtrlPanel = NULL;
	}
}

BOOL CMdx2CtrlPanel::CreateD3DViewWnd()
{
	/*
	MSG 	   uMsg;

	memset(&uMsg,0,sizeof(uMsg));

	m_winClass.lpszClassName = "MY_WINDOWS_CLASS";
	m_winClass.cbSize 	   = sizeof(WNDCLASSEX);
	m_winClass.style		   = CS_HREDRAW | CS_VREDRAW;
	m_winClass.lpfnWndProc   = D3DViewWndProc;
	m_winClass.hInstance	   = hInstance;
	m_winClass.hIcon		   = LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
	m_winClass.hIconSm	   = LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
	m_winClass.hCursor	   = LoadCursor(NULL, IDC_ARROW);
	m_winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_winClass.lpszMenuName  = NULL;
	m_winClass.cbClsExtra    = 0;
	m_winClass.cbWndExtra    = 0;

	if(!RegisterClassEx( &m_winClass) )
		return FALSE;

	m_hD3DWnd = CreateWindowEx( NULL, "MY_WINDOWS_CLASS", "Dragoon",
							 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
							 0, 0, 800, 600, NULL, NULL, hInstance, NULL );

	if( m_hD3DWnd == NULL )
		return FALSE;

	ShowWindow( m_hD3DWnd, SW_SHOW );
	UpdateWindow( m_hD3DWnd );

	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	D3DDISPLAYMODE d3ddm;

	m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	d3dpp.Windowed				 = TRUE;
	d3dpp.SwapEffect			 = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat		 = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hD3DWnd,
						  D3DCREATE_SOFTWARE_VERTEXPROCESSING,
						  &d3dpp, &m_pd3dDevice );

	//g_pd3dDevice = m_pd3dDevice;
	//SetHR3DDevice( m_pd3dDevice );
	SetHREngine( new CHREngineInstance );
	GetHREngine()->GetRenderer()->SetDevice( m_pd3dDevice );
	GetHREngine()->UseAbstractPath(TRUE);
	HR3D_Config::m_fMdlSpaceScale = 1.0f;
	*/
	return TRUE;
}

BOOL LaunchApp( const char* pszExeFileName )
{
	STARTUPINFO si = {sizeof(si)};

	// 得到Windows目录
	char szCommand[1024];
	sprintf( szCommand, "%s %s 1", pszExeFileName, EXP_MDX_FILE );
	BOOL ret = CreateProcess(pszExeFileName,szCommand,NULL, NULL, FALSE, 0, NULL, NULL, &si,&g_pi );
	if(!ret) 
	{
		//assert( false && "cannot lunch app" );
		return FALSE;
	}
	else
	{
		CloseHandle(g_pi.hThread);
		g_pi.hThread = NULL;
		//CloseHandle(pi.hProcess);
	}
	return TRUE;
}

BOOL CMdx2CtrlPanel::Create( HINSTANCE hInstance )
{
	m_bQuit = FALSE;
	m_bRunning = TRUE;

	g_log.Reset();

	InitCommonControls();

	//assert( g_pMdx2Candidate == NULL && "mdx2 candidate has not destroied" );
	if( g_pMdx2Candidate )
		delete g_pMdx2Candidate;
	
	g_pMdx2Candidate = new HR3D_Mdx2Candidate;
	// realrender added 2003.09.25
	CCreateMdxParam param;
	INode* pSelNode = NULL;
	if( GetMaxIP()->GetSelectedNode() )
	{
		pSelNode = GetMaxIP()->GetSelectedNode();
	}
	else
		pSelNode = GetMaxIP()->GetRootNode();
	param.SetRootNode( pSelNode );
	

	if( !g_pMdx2Candidate->CreateMdx( &param ) )
	{
		MessageBox( m_hCtrlPanel, "Create mdx failed", "??", MB_OK );
		ShutDown( FALSE );
		
		return FALSE;
	}
	
	static char filter[] =	("Mex files (*.mex)\0*.mex\0");

	std::string pszFilename = GetOpenOrSaveFileNameEx(false, filter);

	if( !pszFilename.empty() )
	{
		BOOL bOk = g_pMdx2Candidate->SaveMdx( pszFilename.c_str() );

		if( !bOk )
		{
			MessageBox( m_hCtrlPanel, "Save mdx failed", "??", MB_OK );
			ShutDown( FALSE );
			return FALSE;
		}
	}
	m_bRunning = FALSE;
	return TRUE;
}

LRESULT	CMdx2CtrlPanel::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{	
	case WM_CLOSE:
		break;
	case WM_DESTROY:
        break;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

void CMdx2CtrlPanel::Run()
{
	//m_bRunning = TRUE;
	//MSG 	   uMsg;
	//while( !m_bQuit )
	//{
	//	if( PeekMessage( &uMsg, NULL, 0, 0, PM_REMOVE ) )
	//	{
	//		TranslateMessage( &uMsg );
	//		DispatchMessage( &uMsg );
	//	}
	//	else
	//	{
	//		if( !g_bUseSelfRender )
	//		{
	//			DWORD dwExitCode = 0;
	//			if( GetExitCodeProcess( g_pi.hProcess, &dwExitCode ) )
	//			{
	//				if( dwExitCode != STILL_ACTIVE )
	//				{
	//					CloseHandle( g_pi.hProcess );
	//					g_pi.hProcess = NULL;
	//					ShutDown();
	//					break;
	//				}

	//			}
	//		}
	//		else
	//			Render();
	//		Sleep( 1 );
	//	}
	//}

	//UnregisterClass( "MY_WINDOWS_CLASS", m_winClass.hInstance );
	//
	//m_bRunning = FALSE;
}

void CMdx2CtrlPanel::ShutDown( BOOL bCreateSucc )
{
	if( g_pMdx2Candidate )
	{
		delete g_pMdx2Candidate;
		g_pMdx2Candidate = NULL;
	}

	if( g_bUseSelfRender &&
		bCreateSucc )
	{
		/*
		GetMdxResMgr()->DestroyModel( 0 );
		GetMdxResMgr()->Destroy();

		g_pCurScene->DeleteAll();

		GetHREngine()->Release();

		if( m_pd3dDevice != NULL ) 
		{
			m_pd3dDevice->Release(); 
			m_pd3dDevice = NULL; 
		}

		if( m_pD3D != NULL ) 
		{
			m_pD3D->Release(); 
			m_pD3D = NULL; 
		}

		if( m_hD3DWnd )
		{
			DestroyWindow( m_hD3DWnd );
			m_hD3DWnd = NULL;
		}
		*/
	}
	if( m_hCtrlPanel )
	{
		DestroyWindow( m_hCtrlPanel );
		m_hCtrlPanel = NULL;
	}
	
	m_bQuit = TRUE;
	m_bRunning = FALSE;
}

void CMdx2CtrlPanel::AddObjectsToTree( HWND hWnd )
{
	HWND hTree = ::GetDlgItem( hWnd, IDC_TREE_NODE );
	TreeView_DeleteAllItems( hTree );
	
	TVINSERTSTRUCT	is;
	ZeroMemory(&is,sizeof(TVINSERTSTRUCT));
	is.item.mask = TVIF_TEXT | TVIF_PARAM;
	is.item.lParam = 0;
	is.item.pszText = "Objects";
	is.hParent = NULL;
	
	HTREEITEM  hRoot = TreeView_InsertItem(hTree,&is);
	
	for( int i = 0; i < g_pMdx2Candidate->m_skeleton.vectorBone.size(); i++ )
	{
		char szName[256];
		sprintf( szName, "%s", g_pMdx2Candidate->m_skeleton.vectorBone[i].szName );

		is.item.lParam = (LPARAM)g_pMdx2Candidate->m_skeleton.vectorBone[i].pNode;
		is.item.pszText = szName;
		is.hParent = hRoot;

		TreeView_InsertItem( hTree, &is );
	}
}

void CMdx2CtrlPanel::AddAnimsToList(  HWND hWnd )
{
	HWND hListWnd = ::GetDlgItem( hWnd, IDC_LIST_SEQUENCE );
	ListBox_ResetContent( hListWnd );
}

void CMdx2CtrlPanel::AddTexturesToList( HWND hWnd )
{
	HWND hListWnd = ::GetDlgItem( hWnd, IDC_LIST_TEXTURES );
	ListBox_ResetContent( hListWnd );
}

void CMdx2CtrlPanel::AddMaterialsToTree( HWND hWnd )
{
	HWND hTree = ::GetDlgItem( hWnd, IDC_TREE_MATERIALS );
	TreeView_DeleteAllItems( hTree );

	TVINSERTSTRUCT	is;
	ZeroMemory(&is,sizeof(TVINSERTSTRUCT));
	
	is.item.mask = TVIF_TEXT | TVIF_PARAM;
	is.item.lParam = 0;
	is.item.pszText = "Materials";
	is.hParent = NULL;
	
	HTREEITEM  hRoot = TreeView_InsertItem(hTree,&is);
	int nMtlCount = g_pMdx2Candidate->m_mtls.vectorMtl.size();
	for( int i = 0; i < nMtlCount; i++ )
	{
		HR3D_Mdx2Candidate::Material* pMtl = &g_pMdx2Candidate->m_mtls.vectorMtl[i];
		char szName[256];
		sprintf( szName, "Material%ld", i );

		is.item.lParam = (LPARAM)pMtl;
		is.item.pszText = szName;
		is.hParent = hRoot;

		HTREEITEM hMtlItem = TreeView_InsertItem( hTree, &is );
		for( int l = 0; l < pMtl->vectorLayer.size(); l++ )
		{
			HR3D_Mdx2Layer* pLayer = &pMtl->vectorLayer[l];
			
			sprintf( szName, "Layer%ld", l );
			is.item.lParam = (LPARAM)pLayer;
			is.item.pszText = szName;
			is.hParent = hMtlItem;

			HTREEITEM hLayerItem = TreeView_InsertItem( hTree, &is );
			
			is.hParent = hLayerItem;
			is.item.lParam = 0;
			
			sprintf( szName, "BlendMode:%ld", pLayer->GetBlendMode() );
			is.item.pszText = szName;
			TreeView_InsertItem( hTree, &is );

			sprintf( szName, "Flag:%ld", pLayer->GetFlag() );
			TreeView_InsertItem( hTree, &is );

			sprintf( szName, "TextureId:%ld", pLayer->GetTextureID() );
			TreeView_InsertItem( hTree, &is );

			sprintf( szName, "Alpha:%f", pLayer->GetAlpha() );
			TreeView_InsertItem( hTree, &is );
		}
	}

}
void CMdx2CtrlPanel::AddChunksToTree( HWND hWnd )
{
	HWND hTree = ::GetDlgItem( hWnd, IDC_TREE_CHUNKS );
	TreeView_DeleteAllItems( hTree );

	TVINSERTSTRUCT	is;
	ZeroMemory(&is,sizeof(TVINSERTSTRUCT));
	
	is.item.mask = TVIF_TEXT | TVIF_PARAM;
	is.item.lParam = 0;
	is.item.pszText = "Mesh";
	is.hParent = NULL;
	
	HTREEITEM  hRoot = TreeView_InsertItem(hTree,&is);

	int nVertexCount = 0;
	int nFaceCount = 0;
	for( int i = 0; i < g_pMdx2Candidate->m_geometry.vectorChunk.size(); i++ )
	{
		HR3D_Mdx2Candidate::GeomChunk* pChunk = &g_pMdx2Candidate->m_geometry.vectorChunk[i];
		nVertexCount += pChunk->vectorSplitVertex.size();
		nFaceCount += pChunk->vectorFace.size();
	}

	char s[256];
	sprintf( s, "Total Vertex Count:%ld", nVertexCount );
	is.item.lParam = NULL;
	is.item.pszText = s;
	is.hParent = hRoot;
	TreeView_InsertItem( hTree, &is );
	sprintf( s, "Total Face Count:%ld", nFaceCount );
	is.item.lParam = NULL;
	is.item.pszText = s;
	is.hParent = hRoot;
	TreeView_InsertItem( hTree, &is );

	for( int i = 0; i < g_pMdx2Candidate->m_geometry.vectorChunk.size(); i++ )
	{
		
		HR3D_Mdx2Candidate::GeomChunk* pChunk = &g_pMdx2Candidate->m_geometry.vectorChunk[i];
		char szName[256];
		sprintf( szName, "Chunk%ld", i );

		is.item.lParam = (LPARAM)pChunk;
		is.item.pszText = szName;
		is.hParent = hRoot;

		HTREEITEM hChunkItem = TreeView_InsertItem( hTree, &is );
		
		is.item.lParam = 0;
		is.hParent = hChunkItem;
		is.item.pszText = szName;

		sprintf( szName, "Face:%ld", pChunk->vectorFace.size() );
		TreeView_InsertItem( hTree, &is );
		sprintf( szName, "Vertex:%ld", pChunk->vectorVertex.size() );
		TreeView_InsertItem( hTree, &is );
		sprintf( szName, "Material:%ld", pChunk->nMtlId );
		TreeView_InsertItem( hTree, &is );
	}
}


void CMdx2CtrlPanel::Render()
{
	/*
	GetMaxIP()->ClearNodeTree();
	GetMaxIP()->GetNodeTree( NULL );

	m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
						 D3DCOLOR_COLORVALUE(0.5f,0.5f,0.5f,1.0f), 1.0f, 0 );

	m_pd3dDevice->BeginScene();
	
	m_pd3dDevice->SetTransform( D3DTS_VIEW, (D3DXMATRIX*)&m_pCamera->GetViewMatrix() );
	HR3D_Config::SetBillboard( *(HR3D_Matrix*)&m_pCamera->GetBillboardMatrix() );
	GetHREngine()->GetRenderer()->SetEyePt( (float*)&m_pCamera->GetEyePt() );

	long static time = timeGetTime();
	if( timeGetTime()-time > 33 )
	{
		time = timeGetTime();

		g_pMdx2Candidate->m_nFrameId++;
	
	}

	D3DMATERIAL9 mtrl;
	D3DUtil_InitMaterial( mtrl, 0.2f, 0.2f, 0.2f );
	mtrl.Ambient.r = 0.2f;
	mtrl.Ambient.g = 0.2f;
	mtrl.Ambient.b = 0.2f;
	m_pd3dDevice->SetMaterial( &mtrl );

	// realrender added 2003.09.06
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity( &matWorld );
	g_pMdx2Candidate->m_pAnimCtrl->GetMdx()->SetTransform( (float*)&matWorld );
	
	HR3D_CFrustum frustum;
	frustum.BuildFrustum( m_pCamera->GetProjMatrix(), m_pCamera->GetViewMatrix() );
	g_pCurScene->Update( m_pCamera->GetEyePt(), m_pCamera->GetEyePt(), D3DXVECTOR3( 0, 0, 1 ),&frustum );
	
	
	g_pCurScene->SetLights( m_pCamera->GetEyePt() );
	
	g_pMdx2Candidate->Render();

	GetHREngine()->GetRenderer()->Flush( eSortByFarZ );

	Sleep( 5 );



	m_pd3dDevice->EndScene();
	m_pd3dDevice->Present( NULL, NULL, NULL, NULL );
	*/
}

LRESULT	CMdx2CtrlPanel::CtrlPanelMsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			AddObjectsToTree( hWnd );
			AddAnimsToList( hWnd );
			AddTexturesToList( hWnd );
			AddMaterialsToTree( hWnd );
			AddChunksToTree( hWnd );
			HWND hListWnd = ::GetDlgItem( hWnd, IDC_LIST_LOG1 );
			for( int i = 0; i < g_log.m_strings.size(); i++ )
				ListBox_AddString( hListWnd, g_log.m_strings[i].c_str() );

		}
		break;
	case WM_NOTIFY:
		if( wParam == IDC_TREE_NODE )
		{
			if( ((LPNMHDR) lParam)->code == TVN_SELCHANGED )
			{
				if( 0 != ((LPNMTREEVIEW) lParam)->itemNew.lParam )
				{
				}
			}
			break;
		}
		return FALSE;
		break;
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDC_BUTTON_PAUSE:
			{

				HWND hButton = GetDlgItem( hWnd, IDC_BUTTON_PAUSE );
				m_bPause = !m_bPause;
				if( m_bPause )
					SetWindowText( hButton, "Pause" );
				else
					SetWindowText( hButton, "Start" );
			}
			break;
		case IDC_BUTTON_SAVEPANELDATA:
			{
			}
			break;

		//case IDC_BUTTON_SAVEMDX:
		//	{
		//		char* pszFilename = NULL;
		//		// 如果创建主角，那么需要自动命名，
		//		if( g_pMdx2Candidate->m_bIsDressingDoll )
		//		{
		//			char szMdxName[MAX_PATH] = "";
		//			DialogBoxParam( hInstance, 
		//				MAKEINTRESOURCE( IDD_DIALOG_CHAR_AUTO_NAME ), 
		//				NULL, 
		//				::AutoNamePanelMsgProc,
		//				(LPARAM)szMdxName );
		//			if( szMdxName[0] == 0 )
		//			{
		//				//assert( false && "not assign mdx name, failed" );
		//				MessageBox( m_hCtrlPanel, "Null Filename, Not Saved.", "warning", MB_OK );
		//				//break;
		//				return FALSE;
		//			}
		//			char szDir[MAX_PATH];
		//			// 如果有选中
		//			if( BrowseBox( NULL, szDir, MAX_PATH ) )
		//			{
		//				HR3D_Path path;
		//				static char szFullPath[MAX_PATH];
		//				sprintf( szFullPath, "%s%s\\", szDir, szMdxName );
		//				path.MakeDirectory( szFullPath );
		//				sprintf( 
		//					szFullPath, 
		//					"%s%s\\%s.mdx2", 
		//					szDir, 
		//					szMdxName, 
		//					szMdxName );
		//				pszFilename = szFullPath;

		//			}

		//		}
		//		else
		//		{
		//			static TCHAR filter[] =
		//				TEXT("CKF Mdx files (*.mdx2)\0*.mdx2\0")
		//				TEXT("All Files (*.*)\0*.*\0");
		//			pszFilename = OpenFileDialog( filter, "mdx2" );
		//		}

		//		
		//		if( pszFilename )
		//		{
		//			//if( !m_mdxCandidate.SaveToFile( pszFilename ) )
		//			// realrender added 2003.12.22
		//			// 拷贝并预处理贴图文件
		//		//	g_pMdx2Candidate->ConvertTextures( pszFilename );
		//			if( !g_pMdx2Candidate->SaveMdx( pszFilename ) )
		//				MessageBox(m_hCtrlPanel, "Mdx2(.mdx2)保存失败！", "", MB_OK );
		//			else
		//				MessageBox(m_hCtrlPanel, "Mdx2(.mdx2)保存成功！", "", MB_OK );

		//		}

		//	}
		//	break;
		case IDC_BUTTON_CLOSEPROP:
			ShutDown();
			break;
		}
		return FALSE;
		break;
	}
	return FALSE;
}

LRESULT CMdx2CtrlPanel::AutoNamePanelMsgProc( HWND hDlg,UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	static char* pszMdxName = NULL;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			pszMdxName = (char*)lParam;	
			char szIniFilename[MAX_PATH];
			sprintf( szIniFilename, "%s\\CharAutoName.ini",  theHR3D_Plugins.GetPluginAppPath() );


			FILE *fp;
			BOOL bHasIni = TRUE;
			fp = fopen( szIniFilename, "rb" );
			if( fp == NULL )
			{
				MessageBox( m_hCtrlPanel, "cannot find autoname ini file", "warning", MB_OK );
				bHasIni = FALSE;
			}
			fclose(fp);
			if( !bHasIni )
				break;

			const char* szRace  = "Race";
			const char* szLevel = "Level";
			const char* szSex   = "Sex";
			int nRaceCount  = GetPrivateProfileInt( szRace, "count", 0 , szIniFilename );
			int nLevelCount = GetPrivateProfileInt( szLevel, "count", 0 , szIniFilename );
			int nSexCount   = GetPrivateProfileInt( szSex, "count", 0 , szIniFilename );
			int i = 0;
			HWND hItem;
			
			
			hItem = GetDlgItem( hDlg, IDC_COMBO_RACE );
			for( i = 0; i < nRaceCount; i++ )
			{
				char key[256];
				sprintf( key, "Race%02ld", i );
				char value[256];
				GetPrivateProfileString( szRace, key , "" , value, 256 , szIniFilename );
				ComboBox_AddString( hItem, value );
			}

			hItem = GetDlgItem( hDlg, IDC_COMBO_LEVEL );
			for( i = 0; i < nLevelCount; i++ )
			{
				char key[256];
				sprintf( key, "Level%02ld", i );
				char value[256];
				GetPrivateProfileString( szLevel, key , "" , value, 256 , szIniFilename );
				ComboBox_AddString( hItem, value );
			}

			hItem = GetDlgItem( hDlg, IDC_COMBO_SEX );
			for( i = 0; i < nSexCount; i++ )
			{
				char key[256];
				sprintf( key, "Sex%02ld", i );
				char value[256];
				GetPrivateProfileString( szSex, key , "" , value, 256 , szIniFilename );
				ComboBox_AddString( hItem, value );
			}		
		}
		break;
	case WM_CLOSE:
		break;
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDOK:
			{
				char szRace[MAX_PATH] = "";
				char szLevel[MAX_PATH] = "";
				char szSex[MAX_PATH] = "";
				char szExt[MAX_PATH] = "";
				int nSelId;
				HWND hItem;
			
				hItem = GetDlgItem( hDlg, IDC_COMBO_RACE );
				nSelId = ComboBox_GetCurSel( hItem );
				if( nSelId != -1 )
				{
					ComboBox_GetLBText( hItem, nSelId, szRace );
				}
	
				hItem = GetDlgItem( hDlg, IDC_COMBO_LEVEL );
				nSelId = ComboBox_GetCurSel( hItem );
				if( nSelId != -1 )
				{
					ComboBox_GetLBText( hItem, nSelId, szLevel );
				}

				hItem = GetDlgItem( hDlg, IDC_COMBO_SEX );
				nSelId = ComboBox_GetCurSel( hItem );
				if( nSelId != -1 )
				{
					ComboBox_GetLBText( hItem, nSelId, szSex );
				}

				hItem = GetDlgItem( hDlg, IDC_EDIT_CHARNAME_EXT );
				GetWindowText( hItem, szExt, MAX_PATH );
				
				if( szExt[0] == 0 )
				{
					sprintf( pszMdxName, "%s_%s_%s", 
						szRace,
						szLevel,
						szSex );
				}
				else
				{
					sprintf( pszMdxName, "%s_%s_%s_%s", 
						szRace,
						szLevel,
						szSex,
						szExt );
				}
				EndDialog( hDlg, 0 );

			}
			break;
		case IDCANCEL:
			EndDialog( hDlg, 0 );
			break;
		}

	}
	return FALSE;
}
//LRESULT CMdx2CtrlPanel::AnimSequenceSettingDlgMsgProc( HWND hDlg,UINT uMsg, WPARAM wParam, LPARAM lParam )
//{
//	static HR3D_Mdx2Candidate::AnimSequence* as = NULL;
//	switch (uMsg)
//	{
//	case WM_INITDIALOG:
//		as = (HR3D_Mdx2Candidate::AnimSequence*)lParam;
//		break;
//	case WM_CLOSE:
//		break;
//	case WM_COMMAND:
//		switch( LOWORD(wParam) )
//		{
//		case IDOK:
//			{
//				char s[256];
//				
//				HWND hEdit = ::GetDlgItem( hDlg, IDC_EDIT_ANIMSEQUENCE_STARTFRAME );
//				GetWindowText( hEdit, s, 256 );
//				as->nStartFrame = atoi( s );
//				hEdit = ::GetDlgItem( hDlg, IDC_EDIT_ANIMSEQUENCE_ENDFRAME );
//				GetWindowText( hEdit, s, 256 );
//				as->nEndFrame = atoi( s );
//				hEdit = ::GetDlgItem( hDlg, IDC_EDIT_ANIMSEQUENCE_NAME );
//				strcpy( as->szName, s );
//				HWND hCheckBox = ::GetDlgItem( hDlg, IDC_CHECK_ANIMSEQUENCE_LOOPPING );
//				as->nLoopping = Button_GetCheck( hCheckBox );
//				EndDialog( hDlg, 0 );
//			}
//			break;
//		case IDCANCEL:
//			EndDialog( hDlg, 0 );
//			break;
//		}
//	/*default:
//		{
//			return DefWindowProc( hDlg, uMsg, wParam, lParam );
//		}*/
//
//	}
//	return FALSE;
//}
LRESULT CMdx2CtrlPanel::LogDlgMsgProc( HWND hDlg,UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			HWND hListWnd = ::GetDlgItem( hDlg, IDC_LIST_LOG );
			for( int i = 0; i < g_log.m_strings.size(); i++ )
				ListBox_AddString( hListWnd, g_log.m_strings[i].c_str() );
		}
		break;
	case WM_CLOSE:
		EndDialog( hDlg, 0 );
		break;
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDOK:
			{
				EndDialog( hDlg, 0 );
			}
			break;
		}
	}
	return FALSE;
}