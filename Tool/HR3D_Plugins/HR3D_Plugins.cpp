#include <windows.h>
#include <d3dx9.h>
#include "hr3d_Plugins.h"
#include "hr3d_maxinterface.h"
#include "mdx2ctrlpanel.h"
#include "hr3d_mdx2candidate.h"
#include "particleemittersettingdlg.h"

#define HR3D_PLUGIN_CLASS_ID	Class_ID(0x39cf76ff, 0x41d5ba6)

static bool s_through_xref = 0;	// 020416  --prs.

char g_szEditorExePath[MAX_PATH] = "";


HR3D_Plugins theHR3D_Plugins;

class HR3D_PluginsClassDesc:public ClassDesc2 {
public:
	int 			IsPublic() { return TRUE; }
	void *			Create(BOOL loading = FALSE) { return &theHR3D_Plugins; }
	const TCHAR *	ClassName() { return GetString(IDS_CLASS_NAME); }
	SClass_ID		SuperClassID() { return UTILITY_CLASS_ID; }
	Class_ID		ClassID() { return HR3D_PLUGIN_CLASS_ID; }
	const TCHAR*	Category() { return GetString(IDS_CATEGORY); }

	const TCHAR*	InternalName() { return _T("Mex_Plugin"); }	// returns fixed parsable name (scripter-visible name)
	HINSTANCE		HInstance() { return hInstance; }				// returns owning module handle
};

static HR3D_PluginsClassDesc HR3D_PluginsDesc;
ClassDesc2* GetHR3D_PluginsDesc() { return &HR3D_PluginsDesc; }

static BOOL CALLBACK HR3D_PluginsDlgProc(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
	case WM_INITDIALOG:
		{
			theHR3D_Plugins.Init(hWnd);
		}
		break;

	case WM_DESTROY:
		theHR3D_Plugins.Destroy(hWnd);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case IDC_BUTTON_NODEPROP:
			theHR3D_Plugins.NodeProperty();
			break;
		case IDC_BUTTON_PREVIEW:
			theHR3D_Plugins.Preview();
			break;
		case IDC_BUTTON_EXPMDX2:
			break;
		case IDC_BUTTON_SETRIBBONEMITTER:
			{
				INode* pNode = GetMaxIP()->GetSelectedNode();
				if( !pNode )
					break;
				int nLength = strlen( pNode->GetName() );
				if( nLength > 5 )
				{
					char* pszExt = &pNode->GetName()[nLength-5];
					if( stricmp( pszExt, ".ribb" ) == 0 )
						break;
				}
				char s[256];
				sprintf( s, "%s.ribb", pNode->GetName() );
				pNode->SetName( s );
			}
			break;
		case IDC_BUTTON_SETBILLBOARD:
			{
				INode* pNode = GetMaxIP()->GetSelectedNode();
				if( !pNode )
					break;
				int nLength = strlen( pNode->GetName() );
				if( nLength > 5 )
				{
					char* pszExt = &pNode->GetName()[nLength-5];
					if( stricmp( pszExt, ".bbrd" ) == 0 )
						break;
				}
				char s[256];
				sprintf( s, "%s.bbrd", pNode->GetName() );
				pNode->SetName( s );
			}
			break;
		// realrender added 2003.12.14
		case IDC_APPDATA_GET:
			theHR3D_Plugins.GetAppData();
			break;

		case IDC_APPDATA_PUT:
			theHR3D_Plugins.PutAppData();
			break;
		case IDC_APPDATA_EDIT:
			{
				//switch (HIWORD(wParam)) 
				//{
				//case EN_SETFOCUS:
				//	DisableAccelerators();
				//	break;
				//case EN_KILLFOCUS:
				//	EnableAccelerators();
				//	break;
				//}
			}
			break;
		case IDC_BUTTON_PARTICLEEMITTERSETTING:
			theHR3D_Plugins.ParticleEmitterSetting();
			break;
		case IDC_BUTTON_RIBBONEMITTERSETTING:
			theHR3D_Plugins.RibbonEmitterSetting();
			break;
		case IDC_BUTTON_CONVBONENAME:
			theHR3D_Plugins.ConvertBoneName();
			break;
		}
		break;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MOUSEMOVE:
		theHR3D_Plugins.ip->RollupMouseMessage(hWnd,msg,wParam,lParam); 
		break;

	default:
		return FALSE;
	}
	return TRUE;
}

Interface* g_ip = NULL;
HR3D_Plugins::HR3D_Plugins()
{
	iu = NULL;
	ip = NULL;	
	g_ip = ip;
	hPanel = NULL;
}

HR3D_Plugins::~HR3D_Plugins()
{

}

static HR3D_MaxInterface gs_maxInterface;
HR3D_MaxInterface* GetMaxIP()
{
	return &gs_maxInterface;
}

void HR3D_Plugins::BeginEditParams(Interface *ip,IUtil *iu) 
{
	this->iu = iu;
	this->ip = ip;
	g_ip = ip;
	hPanel = ip->AddRollupPage(
		hInstance,
		MAKEINTRESOURCE(IDD_PANEL),
		HR3D_PluginsDlgProc,
		GetString(IDS_PARAMS),
		0);

	gs_maxInterface.Create(0, theHR3D_Plugins.ip);

	// realrender added 2003.10.07
	static BOOL bInit = FALSE;
	if( !bInit )
	{
		bInit = TRUE;
		//HR3D_Config::m_bAlwaysRenderEffect = TRUE;

		sprintf( m_szPluginAppPath, "%shr3d", ip->GetDir( APP_PLUGINS_DIR ) );
		//char szStdSkeletonDefFilename[MAX_PATH];
		//sprintf( 
		//	szStdSkeletonDefFilename,
		//	"%s\\ArabianNightsSkeleton.cfg",
		//	//"%s\\XSanguoSkeleton2.cfg",
		//	//"%s\\ZGSkeleton.cfg",
		//	theHR3D_Plugins.GetPluginAppPath() );
		//g_stdCharSkeleton.LoadCfg( szStdSkeletonDefFilename );
		
		/*
		CCfgFileLoader l;
		char szEditorIni[MAX_PATH];
		sprintf( 
			szEditorIni,
			"%s\\editor.ini", 
			theHR3D_Plugins.GetPluginAppPath() );
		if( l.LoadFromFile( szEditorIni ) )
		{
			strcpy( g_szEditorExePath, l.GetStringValue( "EditorExe" ) );
		}
		*/
	}

}

void HR3D_Plugins::EndEditParams(Interface *ip,IUtil *iu) 
{
	this->iu = NULL;
	this->ip = NULL;
	ip->DeleteRollupPage(hPanel);
	hPanel = NULL;
}

void HR3D_Plugins::Init(HWND hWnd)
{

}

void HR3D_Plugins::Destroy(HWND hWnd)
{

}

void HR3D_Plugins::NodeProperty()
{
	INode* pNode = GetMaxIP()->GetSelectedNode();
	if( pNode )
	{
		if( !GetMaxIP()->IsBone( pNode ) &&
			!GetMaxIP()->IsBipedBone( pNode ) )
		{
			MessageBox( hPanel, "Cannot select none bone node", "failed", MB_OK );
			return;
		}
	}
	if( g_mdx2CtrlPanel.m_bRunning )
		return;
	g_mdx2CtrlPanel.Create( hInstance );
	g_mdx2CtrlPanel.Run();
}


void HR3D_Plugins::Preview()
{

}

BOOL HR3D_Plugins::ExpPrim( const char* pszFilename )
{
	INode* node = GetMaxIP()->GetSelectedNode( 0 );
	Mesh* mesh = GetMaxIP()->GetMesh( node );
	if( !mesh )return FALSE;

	int nVertexCount = mesh->numVerts;
	int nFaceCount = mesh->numFaces;

	if( nVertexCount == 0 || nFaceCount == 0 )
		return FALSE;

	FILE* fp = fopen( pszFilename, "wb" );
	fwrite( &nVertexCount, sizeof( int ), 1, fp );
	fwrite( &nFaceCount, sizeof( int ), 1, fp );

	int i = 0;
	for( i = 0; i < nVertexCount; i++ )
	{
		Point3 pos = mesh->getVert( i );
		fwrite( pos, sizeof( Point3 ), 1, fp );
	}

	for( i = 0; i < nFaceCount; i++ )
	{
		short face[3];
		face[0] = mesh->faces[i].v[0];
		face[1] = mesh->faces[i].v[1];
		face[2] = mesh->faces[i].v[2];
		fwrite( face, sizeof( short )*3, 1, fp );
	}


	fclose( fp );
	return TRUE;
}
extern HR3D_Mdx2Candidate*	g_pMdx2Candidate;

Animatable *HR3D_Plugins::PickAnim()
{
	TrackViewPick pick;
	if (ip->TrackViewPickDlg(hPanel,&pick)) 
	{
		return pick.anim;
	} 
	else 
	{
		return NULL;
	}
}

#define DATAID 1234 
void HR3D_Plugins::PutAppData()
{/*
	INode* pNode = GetMaxIP()->GetSelectedNode();
	if( !pNode )
		return;

	char* szText = (char*)malloc( 256 );
	strcpy( szText, "hello" );
	pNode->RemoveAppDataChunk(
		Class_ID(APPDATA_TEST_CLASS_ID,0), 
		UTILITY_CLASS_ID, 
		DATAID );

	pNode->AddAppDataChunk( 
		Class_ID(APPDATA_TEST_CLASS_ID,0), 
		UTILITY_CLASS_ID, 
		DATAID, 
		256, 
		szText );
	*/
}

void HR3D_Plugins::GetAppData()
{
	//INode* pNode = GetMaxIP()->GetSelectedNode();
	//if( !pNode )
	//	return;
	////char szText[256];
	//
	//AppDataChunk *ad = 
	//	pNode->GetAppDataChunk(
	//	Class_ID(APPDATA_TEST_CLASS_ID,0), 
	//	UTILITY_CLASS_ID, 
	//	DATAID );
	//if( ad )
	//{
	//	char* p = (char*)ad->data;
	//	int k = 0;
	//}
	//
}

extern INT_PTR CALLBACK ParticleEmitterSettingWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
extern INT_PTR CALLBACK RibbonEmitterSettingWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

BOOL HR3D_Plugins::RibbonEmitterSetting()
{
	INode *curNode = GetMaxIP()->GetSelectedNode(0);
	if (curNode == NULL || strnicmp(curNode->GetName(), "ribb.", 5) != 0)
	{
		MessageBox(NULL, "请先选择一个 条带 节点", "提示", MB_OK);
		return FALSE;
	}
	DialogBox(hInstance, MAKEINTRESOURCE( IDD_DIALOG_RIBBONEMITTERSETTING ), this->hPanel, RibbonEmitterSettingWndProc );
	return TRUE;
}

BOOL HR3D_Plugins::ParticleEmitterSetting()
{
	INode *curNode = GetMaxIP()->GetSelectedNode(0);
	if (curNode == NULL || strnicmp(curNode->GetName(), "part.", 5) != 0)
	{
		MessageBox(NULL, "请先选择一个 粒子 节点", "提示", MB_OK);
		return FALSE;
	}	

	DialogBox(hInstance, MAKEINTRESOURCE( IDD_DIALOG_PARTICLEEMITTERSETTING ), this->hPanel, ParticleEmitterSettingWndProc );
	return TRUE;
};

void HR3D_Plugins::ConvertBoneName()
{
	if( MessageBox( 0, "Will u convert the bones' names?", "warning", MB_YESNO ) == IDYES )
		GetMaxIP()->ConvertBoneName();
}