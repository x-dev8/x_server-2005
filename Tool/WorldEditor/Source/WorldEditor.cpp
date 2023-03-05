// WorldEdit.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <direct.h>
#include "WorldEditor.h"

#include "MeTerrain/World.h"
#include "Edit/OptStack.h"
#include "Ndl/NdlWorldEditor.h"

#include "MainFrm.h"
#include "WorldEditorDoc.h"
#include "WorldEditorView.h"

// deleted, [8/18/2010 zhangjiayi]
//#include "ItemDetail.h"
#include "NpcInfo.h"
#include "ModelConfig.h"
#include "PositionInfo.h"
#include "Singleton.h"

#include "Me3d/Engine/MeRenderManager.h"
#include "Me3d/Engine/MeBitSorter.h"
#include "Me3d/Engine/MeShimmerCollector.h"
#include "Me3d/Engine/MeAlphaCollector.h"
#include "ItemDetail.h"
#include "ItemDetailConfig.h"
#include "Utility.h"

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif
namespace
{
	void CullBaseDir( TCHAR* pszBuffer ) {
		size_t j	= _tcslen( pszBuffer );
		TCHAR* pBuffer = NULL;
		pBuffer = _tcsrchr( pszBuffer, _T('\\') );
		if ( pBuffer ) {
			*(pBuffer+1) = _T('\0');
		}
		j		= _tcslen( pszBuffer );
		if( j > 0 ) {
			if ( ( pszBuffer[j-1] == _T('\\') ) || ( pszBuffer[j-1] == _T('/') ) ) {
				pszBuffer[j-1] = 0;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// CWorldEditApp

BEGIN_MESSAGE_MAP(CWorldEditApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
END_MESSAGE_MAP()


// CWorldEditApp construction

CWorldEditApp::CWorldEditApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	m_isActiveApp				= false;
	m_isForceRenderNextFrame	= false;

	memset( m_appDir, 0, sizeof(m_appDir) );

	m_world						= NULL;
	m_worldEditor				= NULL;
	m_mainFrame					= NULL;
	m_editStack					= NULL;
}

void CWorldEditApp::OnActivateApp( bool isActive )
{
	m_isActiveApp	= isActive;
}

bool CWorldEditApp::IsActiveApp()
{
	return m_isActiveApp;
}

void CWorldEditApp::SetForceRenderNextFrame()
{
	m_isForceRenderNextFrame = true;
}

bool CWorldEditApp::GetForceRenderNextFrame()
{
	return m_isForceRenderNextFrame;
}

// The one and only CWorldEditApp object

CWorldEditApp theApp;
bool g_IsArtUsing = false;
bool g_IsShuiHu = false;
// CWorldEditApp initialization


static MeCollectorPtr ms_spShimmerCollector = 0;
static MeCollectorPtr ms_spAlphaCollector = 0;
static MeSorterPtr ms_spBitSorter = 0;
extern int g_ChunkTextureDefaultOverlap;

BOOL CWorldEditApp::InitInstance()
{
	// 禁用ActivationContext, 防止异常: 正被停用的激活上下文不是最近激活的 导致看不到异常堆栈
	afxAmbientActCtx = FALSE;
	::SetUnhandledExceptionFilter(Utility::WorldEditor_UnhandledExceptionFilter);

#ifdef _DEBUG
	::MessageBox(NULL, "debug", NULL, MB_OK);
#endif

	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	if (strstr(m_lpCmdLine,"-art"))
	{
		g_IsArtUsing = true;
	}

	if (strstr(m_lpCmdLine,"-shuihu"))
	{
		g_IsShuiHu = true;
	}

	//add by yanli 2010-6-22
	char *p = NULL;
	if (p = strstr(m_lpCmdLine,"-DefaultOverlap"))
	{
		while (*p++ != ' ')
			;
		g_ChunkTextureDefaultOverlap = atoi(p);
	}
	
	char cszWorkingDir[MAX_PATH];

	// Get the current working directory: 
	_getcwd( cszWorkingDir, MAX_PATH );
	CStringA gameDataDir = cszWorkingDir;
	gameDataDir += "\\..\\data";
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA(gameDataDir,&data);
	bool bFind = (hFind != INVALID_HANDLE_VALUE);
	if (bFind)
	{
		strlwr(cszWorkingDir);
		_tcscpy_s(m_appDir,MAX_PATH, cszWorkingDir);
// 		gameDataDir = cszWorkingDir;
		CStringA dataStr(cszWorkingDir);
		sInt32 pos				= dataStr.ReverseFind('\\');
		if( -1 != pos )
			dataStr		= dataStr.Left( pos );
// 		gameDataDir += "\\..\\";
		CWorld::SetAppCharDir( cszWorkingDir );
		CWorld::SetAppDataCharDir(dataStr);
		CStringW appStr(dataStr);
		CWorld::SetAppDataDir(appStr.GetString());
		SetRootPath( dataStr.GetString() );
	}
	else
	{
		GetModuleFileName( NULL, m_appDir, MAX_PATH );
		if( 0 != _tcslwr_s( m_appDir ) ) {
			return FALSE;
		}
		CullBaseDir( m_appDir );
		sInt32 len = _tcslen( m_appDir )+1;
		Assert( len < MAX_PATH );
		char				appCharDir[MAX_PATH*2+1];
		SwPublicFunc::TChar2MutiChar( appCharDir, (MAX_PATH*2+1)*sizeof(char), m_appDir, len*sizeof(TCHAR) );
		CWorld::SetAppCharDir( appCharDir );
		CStringA dataStr(appCharDir);
		sInt32 pos				= dataStr.ReverseFind('\\');
		if( -1 != pos )
			dataStr		= dataStr.Left( pos );
		pos				= dataStr.ReverseFind('\\');
		if( -1 != pos )
			dataStr		= dataStr.Left( pos );
		pos				= dataStr.ReverseFind('\\');
		if( -1 != pos )
			dataStr		= dataStr.Left( pos );
		dataStr += "\\Bin\\Client";
		CWorld::SetAppDataCharDir(dataStr.GetString());

		CStringW appStr(dataStr);
		CWorld::SetAppDataDir(appStr.GetString());
		SetRootPath( dataStr.GetString() );
	}

	SetEngine( new CEngineInstance );

	Assert( NULL == m_world );
	m_world = new CWorld();
	CEditWorldBuffer* pBuffer = new CEditWorldBuffer(m_world);
	if( !m_world->Create(pBuffer) ) {
		return FALSE;
	}
// 	m_world->GetWorldBuffer()->SetMultiThread(false);
	SwGlobal::SetWorld(m_world);

	Assert( NULL == m_worldEditor );
	//m_worldEditor = NiTCreate<CNdlWorldEditor>();
	m_worldEditor = new CNdlWorldEditor;
	m_worldEditor->Create( m_world );

	Assert( NULL == m_editStack );
	m_editStack	= new COptStack();
	m_editStack->Create();
	
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CWorldEditDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CWorldEditView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	if (!g_IsArtUsing)
	{
// 		char strName[MAX_PATH] = {0};
// 		sprintf_s(strName, sizeof(strName)/sizeof(char)-1, "%s\\Data\\Config\\Item\\", SwGlobal::GetWorld()->GetAppDataCharDir());
// 		if(!GetItemDetailConfig().LoadItemDetailConfig( strName ))
// 		{
// 			::TerminateProcess( ::GetCurrentProcess(), 0 );
// 		}
 		// deleted, [8/18/2010 zhangjiayi]
 		if (!GettheItemDetail().LoadBinFile("..\\Data\\Config\\Data.config"))
		{
			CString strMsg;
			strMsg.Format( _T("加载Data.config失败, 请更新编辑器版本！") );
			MessageBox( NULL, strMsg, "错误", MB_OK );
 			return FALSE;
		}

		if(!theModelConfig.LoadModelConfig("..\\Data\\Config\\Model.config"))
			return FALSE;

		if(theNpcInfo.LoadConfig("..\\Data\\Config\\Npc.config") != 0)
			return FALSE;

#ifdef _DEBUG
		std::vector<NpcInfo::Npc*> vecSet;
		if(theNpcInfo.GetNpcs(101,vecSet) == 0/*ER_Success*/)
		{
			int nSize = vecSet.size();
			for (int ii = 0;ii < nSize;++ii)
			{

			}

		}
#endif
		if(thePositionInfo.LoadConfig("..\\Data\\Config\\Position.config") != 0)
		{
			return FALSE;
		}
	}

	ms_spShimmerCollector = MeNew MeShimmerCollector;
	ms_spAlphaCollector = MeNew MeAlphaCollector;
	ms_spBitSorter = MeNew MeBitSorter;
	// 默认关
	ms_spShimmerCollector->SetEnable( false );
	MeRenderManager::Instance()->SetSorter( ms_spBitSorter );
	MeRenderManager::Instance()->AddCollector( ms_spAlphaCollector );
	MeRenderManager::Instance()->AddCollector( ms_spShimmerCollector );
	return TRUE;
}

int	CWorldEditApp::ExitInstance()
{
	SAFE_DELETE( m_editStack );
	SAFE_DELETE( m_worldEditor );
	SAFE_DELETE( m_world );
	NDL_SAFE_DELETE( g_render );

	MeRenderManager::Instance()->SetSorter( NULL );
	ms_spShimmerCollector = 0;
	ms_spAlphaCollector = 0;
	ms_spBitSorter = 0;

	return CWinApp::ExitInstance();
}
class detectLeakImpl
{
public:
	~detectLeakImpl(){
#ifdef _DEBUG
		if (0)
		{
			CMeMemoryDetailDump::Instance()->DumpDetailInfo();
		}
#endif
		MeMemoryTracker::Instance()->OutputMemInfo();
		MeMemoryTracker::Shutdown();
		CSingletonBase::ReleaseAll();
	}
};
detectLeakImpl kDetectLeak;


BOOL CWorldEditApp::OnIdle(LONG lCount)
{
	return ( CWinApp::OnIdle( lCount) );
}

void CWorldEditApp::RunFrame(void)
{
	if( CWorldEditDoc::GetActiveMapDoc() && m_isActiveApp )
	{
		// get the time
		CWorldEditDoc::GetActiveMapDoc()->UpdateCurrentTime();
		// run any animation
		CWorldEditDoc::GetActiveMapDoc()->UpdateAnimation();
		// redraw the 3d views
		CWorldEditDoc::GetActiveMapDoc()->Update3DViews();
	}
	m_isForceRenderNextFrame = false;
}

void CWorldEditApp::CalFPS()
{
// 	SwGlobal::s_timer.IsTimeShowNextFrame();
// 
// 	static float time1 = SwGlobal::s_timer.GetTimeTotal();
// 	static int fps = 0;
// 	++fps;
// 
// 	float time2 = SwGlobal::s_timer.GetTimeTotal();
// 	if ( time2-time1>1.0f ) {
// 		char msg[256];
// #ifdef _DEBUG
// 		sprintf(msg, "FPS: %.2f, Models: %d, Faces: %d, Vertices: %d\n", fps/(time2-time1), 
// 			SwGlobal::GetRender()->GetGeometryCount(), SwGlobal::GetRender()->GetFaceCount(), SwGlobal::GetRender()->GetVertexCount());
// #else
// 		sprintf(msg, "FPS: %.2f\n", fps/(time2-time1));
//#endif
// 		OutputDebugStringA(msg);

// 		fps = 0;
// 		time1=time2;
// 	}
}

int CWorldEditApp::Run(void)
{
	// For tracking the idle time state
	bool bIdle = true;
	long lIdleCount = 0;

	//
	// Acquire and dispatch messages until a WM_QUIT message is received.
	//
	for (;;)
	{
		if( !IsActiveApp() )
		{
			Sleep(50);
		}

		RunFrame();

		if( bIdle && !OnIdle(lIdleCount++) )
		{
			bIdle = false;
		}

		//
		// Pump messages until the message queue is empty.
		//
		MSG msg;
		while( ::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE) )
		{
			if( msg.message == WM_QUIT )
			{
				return( ExitInstance() );
			}
			if ( !PreTranslateMessage(&msg) )
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			// Reset idle state after pumping idle message.
			if( IsIdleMessage(&msg) )
			{
				bIdle = true;
				lIdleCount = 0;
			}
		}
	}
	return 0;
}

void CWorldEditApp::SetProcess( int percent )
{
	int per = 0;
	if( percent < 0 )
	{
		per = 0;
	}
	if( percent > 100 )
	{
		per = 100;
	}
	m_mainFrame->UpdateProgress( per );
}

void CWorldEditApp::SetPromptText( LPCTSTR text )
{
	m_mainFrame->SetPromptText( text );
}

void CWorldEditApp::SetMousePosText( sInt32 posX, sInt32 posY, const Vector& rayPt, const Vector& rayDir )
{
	m_mainFrame->SetMousePosText( posX, posY, rayPt, rayDir );
}

void CWorldEditApp::SetWorldPosText( flt32 posX, flt32 posY, flt32 posZ ,flt32 angle)
{
	m_mainFrame->SetWorldPosText( posX, posY, posZ ,angle);
}

void CWorldEditApp::SetLoopCountText( sInt32 countA, sInt32 countB )
{
	m_mainFrame->SetLoopCountText( countA, countB );
}

// App command to run the dialog
void CWorldEditApp::OnAppAbout()
{

}

void CWorldEditApp::SetDefaultLight()
{
	g_render->SetDefaultLight();
}


void CWorldEditApp::SetLightDir( const Vector& dir )
{
	m_world->SetLightDir( dir );
	g_render->SetLightDir( dir );
}

void CWorldEditApp::SetLightAmbientColor( const NiColor& ambient )
{
	m_world->SetLightAmbientColor( ambient );
	g_render->SetLightAmbientColor( ambient );
}

void CWorldEditApp::SetLightDiffuseColor( const NiColor& diffuse )
{
	m_world->SetLightDiffuseColor( diffuse );
	g_render->SetLightDiffuseColor( diffuse );
}

void CWorldEditApp::SetLightSpecularColor( const NiColor& specular )
{
	m_world->SetLightSpecularColor( specular );
	g_render->SetLightSpecularColor( specular );
}

void CWorldEditApp::SetSunLessColor( const NiColor& specular )
{
	m_world->SetSunLessColor( specular );

}


void CWorldEditApp::SetFogColor( const NiColor& fogColor )
{
	g_render->SetFogColor( fogColor );
}

void CWorldEditApp::SetFogDepth( flt32 fogNear, flt32 fogFar )
{
	g_render->SetFogDepth( fogNear, fogFar );
}

FogProperty* CWorldEditApp::GetFogProperty()
{
		return g_render->GetFogProperty();
}

// CWorldEditApp message handlers

