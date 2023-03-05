
#include "MeTerrain/stdafx.h"
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Login.h"
#include "../dxutil.h"
#include "GameMain.h"
#include "../cfg.h"
#include "MessageBox.h"
#include "Me3d/Engine/Engine.h"
#include "Select.h"
#include "Progress.h"
#include "FuncPerformanceLog.h"
#include "SelectBox.h"
#include "NpcChatDialogBox.h"
#include "MeAudio/MeAudio.h"
#include "XmlStringLanguage.h"
#include "Main.h"
#include "Compound.h"
#include "SoftKeyboard.h"
#include "Cfg.h"
#include "../color_config.h"
#include "tstring.h"
#include "GameMain.h"
#include "..\PlayerMgr.h"
#include "ChatInfoBox.h"
#include "../compoundInfo_configure.h"
#include "application_config.h"
#include <list>
#include <algorithm>
#include "ErrorLog.h"
#include "core/Name.h"
#include "MeTerrain/STSkyBox.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "wsRender.h"
#include "SystemSetting.h"
#include "Me3d/ShaderMgr.h"
#include "Me3d/ShaderManager.h"
#include "UserData.h"
#include "PlayerRole.h"
#include "SystemConfig.h"
#include "Dxsdk/dinput.h"
#include "XmlRpc/XmlRpc.h"
#include "sha1.h"
#include "md5.h"
#include "UserData.h"
#include "ui/ExitGame.h"
#include "Me3d/Model/Mex2.h"
#include "register.h"
#include "ui/PasswordProtect.h"
#include "Browser.h"
#include "Common.h"							//added by zhuomeng.hu		[8/25/2010]
#include "RapidXml/MeRapidXml.h"
#include "SoundConfig.h"
#include "MovieManager.h"

#include "../HttpEncapsulation/HttpEncapsulation.h"
#include "SimpleCryptograph.h"
#include "Me3d\PostProcess\PostProcess.h"
#include "Me3d\PostProcess\PostProcessManager.h"
#include "GameBeforeSetting.h"
#include "SelectChannel.h"
#include "ICMPPing.h"
#include "GuildGeneralBattleList.h"
extern char* GetFullFileName(const char* filename);
extern bool GetMacByGetAdaptersAddresses(std::string& macOUT,bool IsRand);

extern DWORD HQ_TimeGetTime();

//added by zhuomeng.hu		[8/23/2010]
#ifndef STR_MAXLEN
#define STR_MAXLEN				255												
#endif
#define ACTIVITY_PATH			"..\\Data\\Config\\Event.config"

#define PLAYER_NAME_KEY        TEXT("Software\\Tolez\\Sanguo")
#define SERVERINFO_PATH			"ServerInfo.dat"
#define SERVERLIST_SHOW_MAX		15

#define LOGIN_SCENE				"denglu\\denglu.mew"
#ifdef _OLD_LOGIN_SCENE_
#define LOGIN_CAMERA_MEX		"select.mex"
#define LOGIN_CAMERA_MODEL		"selectcamera"
#define LOGIN_CAMERA_TARGET		"selecttarget"
#else
#define LOGIN_CAMERA_MEX		"login.mex"
#define LOGIN_CAMERA_MODEL		"logincamera"
#define LOGIN_CAMERA_TARGET		"logintarget"
#endif

#define UPDATE_PING_TIME 60000

extern bool g_bCloseApp;
extern GAME_STATE g_GameState;
extern BOOL g_DynamicMapLoadThreadWillExit;
extern BOOL g_DynamicMapLoadThreadExit;
extern BOOL g_bCreateOk;

extern bool g_bConnectSuccFlag;
extern BOOL DynamicMapLoadThreadExit();

#ifndef __NEW_LOGIN__
#define USE_OLD_LOGIN
#endif

const char* chNetStatus[CUI_ID_FRAME_LOGIN::ES_Max] = 
{
	"{#66660}",
	"{#66661}",
	"{#66662}",
	"{#66663}",
	"{#66664}",
};

const char* chNetPing[CUI_ID_FRAME_LOGIN::EP_Max] = 
{
	"{#PING0}",
	"{#PING1}",
	"{#PING2}",
};

const char* chNetServer[CUI_ID_FRAME_LOGIN::ESV_Max] = 
{
	"{#353}",
	"{#352}",
	"{#350}",
	"",
};

const ColorConfigure nNetStatusColor[CUI_ID_FRAME_LOGIN::ES_Max] = 
{
	CC_PetColor_Green, //绿色
	CC_ItemTip_ItemBind,//黄色
	CC_OrangeName,//橙色
	CC_PetColor_Red,//红色
	CC_PetColor_Taupe,//灰色
};

CUI_ID_FRAME_LOGIN s_CUI_ID_FRAME_LOGIN;
MAP_FRAME_RUN( s_CUI_ID_FRAME_LOGIN, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_LOGIN, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_EDIT_IDOnEditEnter )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_EDIT_PASOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_CGOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_GameBeforeSetOnButtonClick )


MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_EXITOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_ProducerOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_RegisterOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_CHECKBOX_SAVEOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_CANCELOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_FastRegisterOnButtonClick )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_CHECKBOX_3DOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_CHECKBOX_25DOnCheckBoxCheck )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LIST_ServerlistOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LIST_Serverlist2OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LIST_ServerName2OnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LIST_ServerState2OnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_ConfirmSelectServerOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_QuitOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_AreaNameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_ServerNameOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LIST_AreaNameOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LIST_ServerNameOnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_CHECKBOX_ShortCutKeyOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_BroadcastOnButtonClick )
MAP_SCROLL_BAR_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_SCROLLBAR_BroadcastOnScrollBarUpdatePos )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LIST_ServerStateOtherOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LIST_ServerStateOnListSelectChange )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LIST_ServerStateOther2OnListSelectChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_CHECKBOX_PasswordProtectOnCheckBoxCheck )

//added by zhuomeng.hu		[8/18/2010]
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_CHECKBOX_SelectBoardOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_CHECKBOX_SelectServiceOnCheckBoxCheck )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LISTIMG_ActivityIconOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LISTIMG_ActivityIconOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LISTIMG_ActivityIconOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LISTIMG_ActivityIconOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_BUTTON_PayOnButtonClick )

MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_LOGIN, ID_LIST_ServerPing2OnListSelectChange )

extern BOOL DebugCommand( const char* pszCommand );
extern short GetKeyboardInput( int iKey );

bool ProcessCallback( const char bPressYesButton, void *pData );

bool GetGlsid( const char* szAccount, std::string& glsid );
bool GetPwdSha1( const char* szPwd, const std::string& glsid, std::string& md5Result, std::stringstream& sstrSha1 );
bool GetPwdMd5( const char* szPwd, const std::string& glsid, std::string& md5Result, std::stringstream& sstrMd5 );
bool QueryUserStatus(const std::string& glsid, int guid, const std::stringstream& sstrSha1);

std::string	CUI_ID_FRAME_LOGIN::g_gateIp;
int			CUI_ID_FRAME_LOGIN::g_gatePort = 0;
DWORD		CUI_ID_FRAME_LOGIN::g_dwSwitchGateTime = 0;
DWORD		CUI_ID_FRAME_LOGIN::g_dwSwitchGatePeriod = 3000;
BOOL		CUI_ID_FRAME_LOGIN::g_bSwitchGate = FALSE;
BOOL		CUI_ID_FRAME_LOGIN::g_bEndGetCharacter = FALSE;
int			CUI_ID_FRAME_LOGIN::g_nError = 0;
int			CUI_ID_FRAME_LOGIN::g_nLoginLastStatus = 0;
int			CUI_ID_FRAME_LOGIN::g_nQueueNumber = 0;
// DWORD		CUI_ID_FRAME_LOGIN::m_dwLoginStartTime = 0;
bool		CUI_ID_FRAME_LOGIN::m_bShowQueue = true;
bool        CUI_ID_FRAME_LOGIN::m_bNeedAckAgain = true;

extern BOOL g_FindPathThreadWillExit;
extern BOOL g_FindPathThreadExit;
extern HANDLE g_hNewPathRequest;
extern HANDLE g_hDynamicLoadMap;

DWORD WINAPI CurrentServerPingThreadProc( LPVOID lpParam )
{
	char* chIpAddr = (char*)lpParam;
	if ( !chIpAddr )
		return 0;

	CICMPPing cicmp;
	int nPing = cicmp.GetPingTime(chIpAddr);

	std::string strState;
	/*if( nPing > gCfg.m_PingBadMin )
		strState = chNetPing[CUI_ID_FRAME_LOGIN::EP_Red];
	else if( nPing > gCfg.m_PingNormalMin )
		strState = chNetPing[CUI_ID_FRAME_LOGIN::EP_Yellow];
	else
		strState = chNetPing[CUI_ID_FRAME_LOGIN::EP_Green];*/

	char buff[24] = {0};
	if ( nPing < 0 )
		strState = theXmlString.GetString(eText_Server_Unknow);
	else if ( nPing == 0 )
		strState = theXmlString.GetString(eText_Server_UnderOne);
	else
	{
		sprintf_s(buff, sizeof(buff) - 1, theXmlString.GetString(eText_Server_Ping), nPing);
		strState = buff;
	}

	std::string strCurrentServer("");
	
	if( !s_CUI_ID_FRAME_LOGIN.GetArea().empty() && !s_CUI_ID_FRAME_LOGIN.GetServer().empty() )	
		strCurrentServer = s_CUI_ID_FRAME_LOGIN.GetArea() + "     " + s_CUI_ID_FRAME_LOGIN.GetServer() + "  " + strState;
	s_CUI_ID_FRAME_LOGIN.m_pID_TEXT_CurrentServer->SetText( strCurrentServer.c_str() );

	s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ZuiJin->Clear();
	s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ZuiJin->SetCurSelIndex(-1);

	ControlList::S_List stList;
	std::string strAreaServer;
	if( !s_CUI_ID_FRAME_LOGIN.GetArea().empty() && !s_CUI_ID_FRAME_LOGIN.GetServer().empty() )
	{
		strCurrentServer = s_CUI_ID_FRAME_LOGIN.GetArea() + "     " + s_CUI_ID_FRAME_LOGIN.GetServer() + "  " + strState;
		strAreaServer = s_CUI_ID_FRAME_LOGIN.GetArea() + "     " + s_CUI_ID_FRAME_LOGIN.GetServer();
		strncpy(stList.m_szNote, strAreaServer.c_str(), 31 );
		stList.SetData( strCurrentServer.c_str() );
		s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ZuiJin->AddItem( &stList ); 			
	}

	return 0;
}

DWORD WINAPI ServerListPingThreadProc( LPVOID lpParam )
{
	CUI_ID_FRAME_LOGIN::ServerInfo_* pServer = ( CUI_ID_FRAME_LOGIN::ServerInfo_* )lpParam;
	if ( !pServer )
		return 0;

	CICMPPing cicmp;
	int nPing = cicmp.GetPingTime(const_cast< char* >(pServer->strIpAddr.c_str()));

	pServer->nPing = nPing;

	if( strcmp(gCfg.m_szDstIP, pServer->strIpAddr.c_str()) == 0 ) 
	{
		std::string strState;
		char buff[24] = {0};
		if ( nPing < 0 )
			strState = theXmlString.GetString(eText_Server_Unknow);
		else if ( nPing == 0 )
			strState = theXmlString.GetString(eText_Server_UnderOne);
		else
		{
			sprintf_s(buff, sizeof(buff) - 1, theXmlString.GetString(eText_Server_Ping), nPing);
			strState = buff;
		}

		std::string strCurrentServer("");

		if( !s_CUI_ID_FRAME_LOGIN.GetArea().empty() && !s_CUI_ID_FRAME_LOGIN.GetServer().empty() )	
			strCurrentServer = s_CUI_ID_FRAME_LOGIN.GetArea() + "     " + s_CUI_ID_FRAME_LOGIN.GetServer() + "  " + strState;
		s_CUI_ID_FRAME_LOGIN.m_pID_TEXT_CurrentServer->SetText( strCurrentServer.c_str() );

		s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ZuiJin->Clear();
		s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ZuiJin->SetCurSelIndex(-1);

		ControlList::S_List stList;
		std::string strAreaServer;
		if( !s_CUI_ID_FRAME_LOGIN.GetArea().empty() && !s_CUI_ID_FRAME_LOGIN.GetServer().empty() )
		{
			strCurrentServer = s_CUI_ID_FRAME_LOGIN.GetArea() + "     " + s_CUI_ID_FRAME_LOGIN.GetServer() + "  " + strState;
			strAreaServer = s_CUI_ID_FRAME_LOGIN.GetArea() + "     " + s_CUI_ID_FRAME_LOGIN.GetServer();
			strncpy(stList.m_szNote, strAreaServer.c_str(), 31 );
			stList.SetData( strCurrentServer.c_str() );
			s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ZuiJin->AddItem( &stList ); 			
		}
	}

	return 0;
}

bool DisconnectExit ( const bool bPressYesButton, void *pData )
{
	guardfunc;

	// 更新快捷键给服务器
	thePlayerRole.SendHotKeyToServer();

	MsgExit msg;
	GettheNetworkInput().SendMsg(&msg);
	//GettheNetworkInput().CheckSendReq();

	//if( G_MAIN == g_GameState 
	//	&& GetSystemConfig()->m_bLinkPage )
	//{
	//	if( !( GetKeyboardInput(DIK_LCONTROL) || GetKeyboardInput(DIK_RCONTROL) ) )
	//		ShellExecute(NULL, ("open"), GetSystemConfig()->m_LinkWeb.c_str(), NULL,NULL, 0 );
	//}

	g_FindPathThreadWillExit = TRUE;
	SetEvent(g_hNewPathRequest);
	while( !g_FindPathThreadExit )
	{
		Sleep( 1 );
	}

	SetEvent(g_hDynamicLoadMap);
	g_DynamicMapLoadThreadWillExit = TRUE;
	while( !g_DynamicMapLoadThreadExit )
	{
		Sleep( 1 );
	}

	return true;
	unguard;
}

CUI_ID_FRAME_LOGIN::CUI_ID_FRAME_LOGIN()
// :CUIBase( eUI_OBJECT_Login )
{
	guardfunc;
	m_pID_FRAME_LOGIN = NULL;
	m_pID_EDIT_ID = NULL;
	m_pID_EDIT_PAS = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_LIST_ZuiJin = NULL;
//	m_pID_TEXT_SEREV = NULL;
	m_pID_BUTTON_CG = NULL;
	m_pID_BUTTON_EXIT = NULL;
//	m_pID_BUTTON_KuaiSuZhuCe =NULL;
	m_pID_BUTTON_Change = NULL;
	m_pCamera = NULL;
	m_pID_CHECKBOX_SAVE = NULL;
//	m_pID_PICTURE_selectserverback = NULL;
//	m_pID_BUTTON_cancel = NULL;
	m_pID_PICTURE_ServerListBack = NULL;
// 	m_pID_PICTURE_Serverback = NULL;
// 	m_pID_PICTURE_serverback = NULL;
// 	m_pID_PICTURE_listback = NULL;
// 	m_pID_LIST_ServerList = NULL;
// 	m_pID_PICTURE_listback2 = NULL;
	m_pID_LIST_ServerList2 = NULL;
	m_pID_LIST_ServerName2 = NULL;
	m_pID_LIST_ServerState2 = NULL;
	//m_pID_TEXT_LatterlyServer = NULL;
	m_pID_BUTTON_ConfirmSelectServer = NULL;
	m_pID_BUTTON_GameBeforeSet = NULL;
//	m_pID_PICTURE_ServerWall1 = NULL;
// 	m_pID_PICTURE_TitleLeft = NULL;
// 	m_pID_PICTURE_TitleRight = NULL;
// 	m_pID_PICTURE_TitleLeftMiddle = NULL;
// 	m_pID_PICTURE_TitleRightMiddle = NULL;
// 	m_pID_PICTURE_Serverback1 = NULL;
// 	m_pID_PICTURE_ServerWall2 = NULL;
// 	m_pID_PICTURE_ServerWall3 = NULL;
	m_pID_BUTTON_Quit = NULL;
// 	m_pID_BUTTON_AreaName = NULL;
// 	m_pID_BUTTON_ServerName = NULL;
// 	m_pID_LIST_AreaName = NULL;
// 	m_pID_LIST_ServerName = NULL;

	m_nBigAreaIndex = 0;
    m_strArea       = "";
	m_strServer		= "";

	m_bLoginWait	= false;
	m_tmStartWait	= 0;

	//m_pID_TEXT_LoginWait = NULL;
	m_bUseReConnect = false;
	m_nControlMode  = 0;
	m_fSmallMapScale = .0f;

	m_pID_TEXT_Ver = NULL;

// 	m_pID_TEXT_3D = NULL;
// 	m_pID_CHECKBOX_25D = NULL;
// 	m_pID_CHECKBOX_3D = NULL;
// 	m_pID_CHECKBOX_25D = NULL;
	m_pID_CHECKBOX_ShortCutKey = NULL;
	//m_pID_PICTURE_ShortCutKeyTip = NULL;


	_focusInAccount = false;
	_focusInPassword = false;

	IsKeyboardChar = 0;

	m_pID_LIST_ServerList = NULL;

	bShowSelectServerList = true;

	m_tmStartLogin = 0;

	m_bIsTileLoaded = 0;
	//m_pID_PICTURE_LOGO = 0;
	bRotFreezed = false;
	jumpToNextTime = true;

	m_bLogining = false;

    m_pSelectItem = NULL;
	m_Handle = NULL;

    m_pID_BUTTON_Broadcast = NULL;
    //m_pID_PICTURE_BroadcastTitle = NULL;
    m_pID_PICTURE_BroadcastWall = NULL;
    m_pID_TEXT_Broadcast = NULL;
    //m_pID_SCROLLBAR_Broadcast = NULL;
    m_bShowBroadcast = false;
    m_pID_LIST_ServerStateOther = NULL;
//     m_pID_LIST_ServerState = NULL;
//     m_pID_LIST_ServerStateOther2 = NULL;
// 	m_pID_CHECKBOX_PasswordProtect = NULL;
// 	m_pID_TEXT_PasswordProtect = NULL;
	m_bGotRegionServerIpPort = false;

	m_strPasswordProtect = "";
	m_strGlsid = "";
	m_strPwdResult = "";
	m_bShowPwdProtect = false;

	//added by zhuomeng.hu		[8/18/2010]
	//m_pID_TEXT_Ba = NULL;
	m_pID_CHECKBOX_SelectBoard = NULL;
	m_pID_CHECKBOX_SelectService = NULL;
	m_pID_PICTURE_BgAcrivity = NULL;
	m_pID_TEXT_ActivityDesc = NULL;
	m_pID_TEXT_ActivityText = NULL;
	m_pID_LISTIMG_ActivityIcon = NULL;
	m_pID_TEXT_CurrentServerText = NULL;
	m_pID_TEXT_CurrentServer = NULL;
	m_pID_PICTURE_Logo = NULL;
	//m_pID_TEXT_RememberText = NULL;
	m_pID_TEXT_SoftKeyBoardText = NULL;
	m_pID_BUTTON_Pay = NULL;
	m_pID_TEXT_ServiceInfo = NULL;
	m_pID_TEXT_SaveText = NULL;
	m_pID_PICTURE_BgBlackbar = NULL;
	m_pID_PICTURE_BgBroadcast = NULL;
	m_pID_PICTURE_BroadcastWall3 = NULL;
	m_pID_PICTURE_BroadcastWall2 = NULL;

	m_pID_PICTURE_SAVE = NULL;
	m_pID_LIST_ServerPing2 = NULL;

	dwStartTime = timeGetTime();
	unguard;
}

void CUI_ID_FRAME_LOGIN::ReadSettings()
{
	guardfunc;
	HKEY hkey;
	if( ERROR_SUCCESS == RegCreateKeyEx( HKEY_CURRENT_USER, PLAYER_NAME_KEY, 
		0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, NULL ) )
	{
		DXUtil_ReadStringRegKey( hkey, TEXT("PlayerName"), m_stAccount.szID, 128, "" );
		RegCloseKey( hkey );
	}
	unguard;
}

void CUI_ID_FRAME_LOGIN::SavePath()
{
	guardfunc;
	HKEY hkey;
	if( ERROR_SUCCESS == RegCreateKeyEx( HKEY_CURRENT_USER, PLAYER_NAME_KEY, 
		0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, NULL ) )
	{
		CHAR szPath[MAX_PATH] = {0};		
		::GetCurrentDirectory( MAX_PATH, szPath );		
		DXUtil_WriteStringRegKey( hkey, TEXT("HeroPath"), szPath );
		RegCloseKey( hkey );
	}
	unguard;
}


void CUI_ID_FRAME_LOGIN::WriteSettings()
{
	guardfunc;
	HKEY hkey;
	if( ERROR_SUCCESS == RegCreateKeyEx( HKEY_CURRENT_USER, PLAYER_NAME_KEY, 
		0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkey, NULL ) )
	{
		if ( m_pID_CHECKBOX_SAVE->IsChecked() )
		{
			DXUtil_WriteStringRegKey( hkey, TEXT("PlayerName"), m_stAccount.szID );
		}
		else
		{
			DXUtil_WriteStringRegKey( hkey, TEXT("PlayerName"), "" );
		}

		CHAR szPath[MAX_PATH] = {0};		
		::GetCurrentDirectory( MAX_PATH, szPath );		
		DXUtil_WriteStringRegKey( hkey, TEXT("HeroPath"), szPath );

		RegCloseKey( hkey );
	}
	unguard;
}

// Frame
bool CUI_ID_FRAME_LOGIN::OnFrameRun()
{
	guardfunc;
    // 保护
    if( !SwGlobal::GetWorld() )
        return true;

//    CWorldBuffer* pbuffer = SwGlobal::GetWorld()->GetWorldBuffer();
//     if (pbuffer && !m_bIsTileLoaded )
//     {
//         LoadScene();
//     }

	if( IsVisable() && bShowSelectServerList )
	{
		int nStartIndex = m_pID_LIST_ServerList2->GetShowStartHeight();
		m_pID_LIST_ServerName2->SetShowStartHeight(nStartIndex);
		m_pID_LIST_ServerState2->SetShowStartHeight(nStartIndex);
		m_pID_LIST_ServerStateOther->SetShowStartHeight(nStartIndex);
		m_pID_LIST_ServerPing2->SetShowStartHeight(nStartIndex);
	}

	/*if ( timeGetTime() - dwStartTime > UPDATE_PING_TIME )
	{
		dwStartTime = timeGetTime();

		m_serverList.RefreshPing();
	}*/

	return true;
	unguard;
}

void CUI_ID_FRAME_LOGIN::LoadScene()
{
	//return;
    // 保护
    if( !SwGlobal::GetWorld() )
        return;

    CWorldBuffer* pbuffer = SwGlobal::GetWorld()->GetWorldBuffer();
    if (pbuffer && !m_bIsTileLoaded )
    {
//         pbuffer->SetMaxTileCacheNum(2);

        pbuffer->SetActiveTile(pbuffer->GetTile(gCfg.m_nLoginMapId));
		SwGlobal::GetRender()->SetFarChunk(7);

        m_bIsTileLoaded = true;

        // 获取相机和人物位置
        CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
        if( pTile )
        {
            CResMgr* pResMgr = pTile->GetCResMgr();
            assert( pResMgr );
            if( pResMgr )
            {
                char pszName[MAX_PATH] = {0};
                BOOL bFindCamera = FALSE;
                BOOL bFindDoor = FALSE;
                for (size_t i = 0; i < pResMgr->GetStaticModelList().size(); ++i )
                {
                    TObjectInfo* pInfo = pResMgr->GetStaticModel(i);
                    if( pInfo->model && pInfo->model->GetMex() )
                    {
                        strcpy(pszName, pInfo->model->GetMex()->GetFilename());
                        strlwr(pszName);
                        if( strstr(pszName, LOGIN_CAMERA_MEX))
                        {
                            m_pCameraModel = pInfo->model;
                            if( m_pCameraModel->GetMexCfg()->GetSequence("idle") )
                            {
                                m_pCameraModel->PlayAnimByName("idle", 0, TRUE);
                            }
                            bFindCamera = TRUE;
                        }
						if( strstr(pszName, "denglu.mex"))
						{
							m_pLoginModel = pInfo->model;
							if( m_pLoginModel->GetMexCfg()->GetSequence("idle") )
							{
								m_pLoginModel->PlayAnimByName("idle", 0, TRUE);
							}
							bFindDoor = TRUE;
						}
						if( bFindCamera && bFindDoor )
							break;
#ifdef _OLD_LOGIN_
                        else if( strstr(pszName, "dljm002.mex") )
                        {
                            m_pDoorModel = pInfo->model;
                            if( m_pDoorModel->GetMexCfg()->GetSequence("idle1") )
                            {
                                m_pDoorModel->PlayAnimByName("idle1", 0, TRUE);
                            }
                            bFindDoor = TRUE;
                        }
                        if( bFindCamera && bFindDoor )
                            break;
#else
						if( bFindCamera )
							break;
#endif
                    }
                }
            }
        }
    }
}

bool CUI_ID_FRAME_LOGIN::OnFrameRender()
{
	if( !m_pCamera )
		return false;
	guardfunc;

	if( SystemSetting::Instance()->IsLowLevelCard() )
	{
		SwGlobal::GetRender()->SetRenderDoodad( false );
		graphics::ShaderManager::instance()->useShader(false);			
	}

	//return false;

    // 保护
    if( !SwGlobal::GetWorld() )
        return false;

    // 加载场景挪到LoadScene函数里，在LoadUI时执行

 	static D3DXVECTOR3 eye(73.7611f, 47.7300f, 19.5708f);
 	static D3DXVECTOR3 lookat(73.7612f, 55.2895f, 19.5708f);
    // 更新相机位置
     if( m_pCameraModel && m_pCameraModel->GetMex() )
     {
         BOOL bUpdateCamera = FALSE;
         BOOL bUpdateTarget = FALSE;
         D3DXVECTOR3 vNewCameraPos = D3DXVECTOR3(0,0,0);
         D3DXVECTOR3 vNewTargetPos = D3DXVECTOR3(0,0,0);
 		char lwrName[MAX_PATH] = {0};
        m_pCameraModel->UpdateByParam( HQ_TimeGetTime() );
        for( int nChunk = 0; nChunk < m_pCameraModel->GetMex()->GetGeometry()->GetChunkCount(); nChunk++ )
        {
            Mex2GeoChunk* pChunk = (Mex2GeoChunk*)m_pCameraModel->GetMex()->GetGeometry()->GetChunk(nChunk);
            std::vector<Vector> vertices;
            vertices.resize(pChunk->GetVertexCount());
            float* vers = (float*)&vertices[0];

            const char* pszName = pChunk->GetName();
            strncpy( lwrName, pszName, sizeof(lwrName)-1 );
            strlwr(lwrName);
            if (strstr(lwrName, LOGIN_CAMERA_MODEL) )
            {
                pChunk->BlendVertex(vers, NULL, pChunk->GetVertexCount(), m_pCameraModel->GetMex(), (float*)m_pCameraModel->GetMatrices(),NULL);
                if( vertices.size() > 0 )
                {
                    for(int j=0; j<vertices.size(); ++j)
                    {
                        vNewCameraPos.x += vertices[j].x;
                        vNewCameraPos.y += vertices[j].y;
                        vNewCameraPos.z += vertices[j].z;
                    }
                    vNewCameraPos.x /= vertices.size();
                    vNewCameraPos.y /= vertices.size();
                    vNewCameraPos.z /= vertices.size();
                }
                bUpdateCamera = TRUE;
            }
            else if (strstr(lwrName,LOGIN_CAMERA_TARGET) )
            {
                pChunk->BlendVertex(vers, NULL, pChunk->GetVertexCount(), m_pCameraModel->GetMex(), (float*)m_pCameraModel->GetMatrices(),NULL);
                if( vertices.size() > 0 )
                {
                    for(int j=0; j<vertices.size(); ++j)
                    {
                        vNewTargetPos.x += vertices[j].x;
                        vNewTargetPos.y += vertices[j].y;
                        vNewTargetPos.z += vertices[j].z;
                    }
                    vNewTargetPos.x /= vertices.size();
                    vNewTargetPos.y /= vertices.size();
                    vNewTargetPos.z /= vertices.size();
                }
                bUpdateTarget = TRUE;
            }
            if( bUpdateCamera && bUpdateTarget )
                break;
        }
        eye = vNewCameraPos;
        lookat = vNewTargetPos;
    }

// 	if( !m_pLoginModel ||  !m_pLoginModel->GetMex() )
// 	{
// 		return false;
// 	}
	IRenderer* RI = GetEngine()->GetRenderer();
	RI->SetRenderState( D3DRS_FOGENABLE, TRUE );

	float fOldBias = GetMe3dConfig()->GetMipLodBais();
	GetMe3dConfig()->SetMipLodBais(0);

 	float fAspect = 1.6f;
// 	RI->SetRenderState( D3DRS_FOGENABLE, FALSE );
// 	RI->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
// 	m_pCamera->SetProjParams( D3DX_PI/4, fAspect, 1.0f, 100000.0f );
// 	RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&m_pCamera->GetProjMatrix() );
// 	GetSTSkyBox()->m_bCanRender = true;

// 	SwGlobal::GetRender()->RenderSkyBox( SwGlobal::GetWorld(), eye );
// 	MeRenderManager::Instance()->DoRender();

// 	GetSTSkyBox()->m_bCanRender = false;

// 	RI->SetRenderState( D3DRS_LIGHTING, FALSE );
// 	RI->SetRenderState( D3DRS_FOGENABLE, TRUE );
// 	RI->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	//flt32 worldWidth = abs(m_pLoginModel->GetWorldMax().x - m_pLoginModel->GetWorldMin().x);
	//flt32 worldHeight = abs(m_pLoginModel->GetWorldMax().z - m_pLoginModel->GetWorldMin().z);

	//flt32 fRadio = ((float)SCREEN_WIDTH)/SCREEN_HEIGHT;
	//if(abs(fRadio - 4.f/3.f) < 0.1)
	//{//
	//	worldHeight = 3.f * worldWidth/4.f;
	//}
// 	float fDelta = 15*SCREEN_HEIGHT/worldHeight;
// 	D3DVIEWPORT9 oldViewport;
// 	D3DVIEWPORT9 newViewport;
// 	newViewport.X = 0;
// 	newViewport.Y = fDelta;
// 	newViewport.Width = SCREEN_WIDTH;
// 	newViewport.Height = SCREEN_HEIGHT - 2*fDelta;
// 	newViewport.MinZ = 0.0f;
// 	newViewport.MaxZ = 1.0f;
// 
// 	LPDIRECT3DDEVICE9 pd3dDevice = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
// 
// 	pd3dDevice->GetViewport(&oldViewport);
// 	pd3dDevice->SetViewport(&newViewport);

	//int l = 10000.0f;

// 	float fCenterX = (m_pLoginModel->GetWorldMax().x + m_pLoginModel->GetWorldMin().x)/2;
// 	float fCenterZ = (m_pLoginModel->GetWorldMax().z + m_pLoginModel->GetWorldMin().z)/2;
// 	D3DXVECTOR3 vEyePt( fCenterX, -132, fCenterZ-0.1 );
// 	D3DXVECTOR3 vLookAt( fCenterX, -7 , fCenterZ);
// 	D3DXVECTOR3 vUp( 0.0f, 0.0f, 1.0f );


// 	D3DXMATRIX matView, matProj;
// 
// 	D3DXMatrixLookAtRH( &matView, &vEyePt, &vLookAt, &vUp );
// 	D3DXMatrixOrthoRH(&matProj,worldWidth, worldHeight, -l, l );

// 	FrustumEx frustum;
// 	frustum.BuildFrustum(matProj, matView);

// 	GetEngine()->GetRenderer()->SetEyePt( (float*)&vEyePt );
// 	GetEngine()->GetRenderer()->SetLookatPt( (float*)&vLookAt );

// 	RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&matProj );
// 	RI->SetTransform( D3DTS_VIEW, (FLOAT*)&matView );



	GetMe3dConfig()->GetCamera()->SetViewParams(
		*(D3DXVECTOR3*)&eye,
		*(D3DXVECTOR3*)&lookat,
		D3DXVECTOR3( 0, 0, 1 ) );

	m_pCamera->SetViewParams(
		*(D3DXVECTOR3*)&eye,
		*(D3DXVECTOR3*)&lookat,
		D3DXVECTOR3( 0, 0, 1 ) );

// 	float fAspect = 1.6f;
	fAspect = (float)SCREEN_WIDTH/SCREEN_HEIGHT;
	m_pCamera->SetProjParams( D3DX_PI/4.f, fAspect,  1.0f, 18000.0f );

	RI->SetEyePt( (float*)&eye );
	RI->SetLookatPt( (float*)&lookat );
	RI->SetTransform( D3DTS_VIEW, (FLOAT*)&m_pCamera->GetViewMatrix() );
	RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&m_pCamera->GetProjMatrix() );

	GetSTSkyBox()->m_bCanRender = TRUE;
	SwGlobal::GetRender()->RenderSkyBox( SwGlobal::GetWorld(), D3DXVECTOR3(0, 0, 0) );		
	GetSTSkyBox()->m_bCanRender = FALSE;

	FrustumEx frustum;	
	frustum.BuildFrustum( m_pCamera->GetProjMatrix(),m_pCamera->GetViewMatrix() );
	SwGlobal::GetRender()->RenderWorld( SwGlobal::GetWorld(), frustum, eye, 0, 0 );

	MeRenderManager::Instance()->DoRender(false);
 	RI->SetRenderState( D3DRS_FOGENABLE, FALSE );

	SwGlobal::GetRender()->RenderLiquid();

#ifdef _OLD_LOGIN_SCENE_
    if( bShowSelectServerList )
	    SwGlobal::GetRender()->RenderEffect( false );
    else
        SwGlobal::GetRender()->RenderEffect( true );
#else
	SwGlobal::GetRender()->RenderEffect( false );
#endif

	GetEngine()->GetRenderer()->Flush( eSortByFarZ );

	MeRenderManager::Instance()->DoRender(true);

	GetMe3dConfig()->SetMipLodBais(fOldBias);
// 	pd3dDevice->SetViewport(&oldViewport);

	return true;
	unguard;
}
// Edit
void CUI_ID_FRAME_LOGIN::ID_EDIT_IDOnEditEnter( ControlObject* pSender, const char* szData )
{
	guardfunc;
	if( !m_pID_FRAME_LOGIN )
		return;
	unguard;
}
// Edit
void CUI_ID_FRAME_LOGIN::ID_EDIT_PASOnEditEnter( ControlObject* pSender, const char* szData )
{
	guardfunc;
	if( !m_pID_FRAME_LOGIN )
		return;
	unguard;
}
// CheckBox
void CUI_ID_FRAME_LOGIN::ID_CHECKBOX_SAVEOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	guardfunc;
	if( !m_pID_FRAME_LOGIN )
		return;
// 	s_CUI_ID_FRAME_LOGIN.hideSoftKeyboard();
	unguard;
}

// void CUI_ID_FRAME_LOGIN::ID_CHECKBOX_3DOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	guardfunc;		
// 	if( !m_pID_FRAME_LOGIN )
// 		return;
// 	if( *pbChecked )
// 	{
// 		m_RadioGroupViewSelect.ToggleRadio( ( ControlCheckBox* )pSender );
// 		CUserData::Instance()->SetViewSet( 1 );
// 	}
// 	else
// 	{
// 		//m_RadioGroupViewSelect.ToggleRadio( ( ControlCheckBox* )m_pID_CHECKBOX_25D );
// 		CUserData::Instance()->SetViewSet( 0 );
// 	}
// 	unguard;
// }
// void CUI_ID_FRAME_LOGIN::ID_CHECKBOX_25DOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	guardfunc;
// 	if( !m_pID_FRAME_LOGIN )
// 		return;
// 	if( *pbChecked )
// 	{
// 		m_RadioGroupViewSelect.ToggleRadio( ( ControlCheckBox* )pSender );
// 		CUserData::Instance()->SetViewSet( 0 );
// 	}
// 	else
// 	{
// 		m_RadioGroupViewSelect.ToggleRadio( ( ControlCheckBox* )m_pID_CHECKBOX_3D );
// 		CUserData::Instance()->SetViewSet( 1 );
// 	}
// 	unguard;
// }

// Button
bool CUI_ID_FRAME_LOGIN::ID_BUTTON_CANCELOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_LOGIN )
		return false;
	s_CUI_ID_FRAME_LOGIN.hideSoftKeyboard();
	TerminateThread( m_Handle, 0 );
	CloseHandle( m_Handle );
	m_Handle = NULL;
	theHeroGame.DisConnect();
	SetLoginInfo("");
	SetLoginWaitText("");

	SetEnable( true );

	theUiManager.SetFocus(m_pID_EDIT_PAS);
	setFocusInAccount(false);
	setFocusInPassword(true);
	return true;
}

//static XmlRpc::XmlRpcValue s_glsUserData;

extern bool    g_bSwitchGate;
extern bool		g_bConnectDis;
BOOL MapLaodThreadExit ();
DWORD WINAPI ConnectThreadProc( LPVOID lpParam )
{
//#ifdef USE_OLD_LOGIN
	guardfunc;
    static unsigned int nLastLoginTime = HQ_TimeGetTime();
	CUI_ID_FRAME_LOGIN::SAccountInfo* pAccount = NULL;
	pAccount = (CUI_ID_FRAME_LOGIN::SAccountInfo*)lpParam;
	BOOL bResult = FALSE;
	bResult = theHeroGame.StartConnectToGate( gCfg.m_szDstIP, gCfg.m_iServerPort );
	if (bResult)
	{
		//thApplication.GetFullVersion();
		/*MsgLoginInfo msg;
		strncpy_s( msg.szAccount,  sizeof(msg.szAccount),  pAccount->szID,				   sizeof(msg.szAccount)-1   );
		strncpy_s( msg.Password,   sizeof(msg.Password),   pAccount->szPwd,				   sizeof(msg.Password)-1    );				
		msg.isWallow               = false;
		GettheNetworkInput().SendMsg(&msg);*/
		MsgLoginAccountInfo msg;		
		strncpy_s( msg.szFullVersion,sizeof(msg.szFullVersion),thApplication.GetFullVersion(),sizeof(msg.szFullVersion)-1   );
		memcpy(msg.szAccount,pAccount->szCryptID,min(CUI_ID_FRAME_LOGIN::SAccountInfo::eMaxString,MsgLoginAccountInfo::eAccountMax));
		memcpy(msg.szPwds,pAccount->szCryptPWD,min(CUI_ID_FRAME_LOGIN::SAccountInfo::eMaxString,MsgLoginAccountInfo::ePwdsMax));
		memcpy(msg.szMac,pAccount->szCryptMac,min(CUI_ID_FRAME_LOGIN::SAccountInfo::eMaxString,MsgLoginAccountInfo::eMacMax));
		/*strncpy_s( msg.szAccount,sizeof(msg.szAccount),pAccount->szCryptID,sizeof(msg.szAccount)-1   );
		strncpy_s( msg.szPwds,sizeof(msg.szPwds),pAccount->szCryptPWD,sizeof(msg.szPwds)-1   );*/
		msg.isEncryp = true;
		msg.nSecondVersion = VERSION_SECOND;
		GettheNetworkInput().SendMsg(&msg);
		return 0;
	}
	DWORD dwStartTime = HQ_TimeGetTime();
	GetErrorLog()->logString( "%s 成功:%d", gCfg.m_szDstIP, bResult );
	while(1)
	{
		if( g_DynamicMapLoadThreadWillExit )
			return 1;

		if ( G_LOGIN == g_GameState)
		{ // 账号在登陆界面
			if (GettheNetworkInput().IsClosed() && HQ_TimeGetTime() - dwStartTime > 10000)
				return 0;
			else if (GettheNetworkInput().ConnectToServer(true))
			{
				/*std::string sessionStr = theHeroGame.GetPlayerMgr()->m_strSessionKey;*/
				/*MsgLoginInfo msg;
				strncpy_s( msg.szAccount,  sizeof(msg.szAccount),  pAccount->szID,				   sizeof(msg.szAccount)-1   );
				strncpy_s( msg.Password,   sizeof(msg.Password),   pAccount->szPwd,				   sizeof(msg.Password)-1    );				
				msg.isWallow               = false;
				GettheNetworkInput().SendMsg(&msg);*/

				MsgLoginAccountInfo msg;
				strncpy_s( msg.szFullVersion,sizeof(msg.szFullVersion),thApplication.GetFullVersion(),sizeof(msg.szFullVersion)-1   );
				strncpy_s( msg.szAccount,sizeof(msg.szAccount),pAccount->szCryptID,sizeof(msg.szAccount)-1   );
				strncpy_s( msg.szPwds,sizeof(msg.szPwds),pAccount->szCryptPWD,sizeof(msg.szPwds)-1   );
				msg.isEncryp = true;
				msg.nSecondVersion = VERSION_SECOND;
				GettheNetworkInput().SendMsg(&msg);

				InterlockedExchange((LONG*)(&g_bConnectSuccFlag), 1);
				return 0;
			}
		}
		else
			return 0;
		Sleep(500);
	}	
	return 0;
	unguard;

	//by vvx 2012.4.7
//#else
//
//	using namespace XmlRpc;
//
//	try
//	{
//		Sleep(100);
//
//		CUI_ID_FRAME_LOGIN::SAccountInfo* pAccount = (CUI_ID_FRAME_LOGIN::SAccountInfo*)lpParam;
//
//		CUI_ID_FRAME_LOGIN::g_nQueueNumber = INT_MAX;
//
//		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_bSwitchGate), 0);
//		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), 0);
//		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nLoginLastStatus), 0);
//		InterlockedExchange((LONG*)(&CUI_ID_FRAME_Select::m_time), 0);
//		s_CUI_ID_FRAME_Select.SetLastIp("");
//		s_CUI_ID_FRAME_Select.SetLastTime("");
//		s_CUI_ID_FRAME_Select.SetLastAddress("");
//
//
//		//
//		//XmlRpcValue args;
//		//XmlRpcClient c(gCfg.m_szDstIP, gCfg.m_iServerPort, "/gls");
//		//XmlRpcValue result;
//
//		//std::string glsid = "";
//		//if( !GetGlsid(pAccount->szID, glsid) )
//		//	return 0;
//
//		//// 是否勾选密保卡
//		//if( s_CUI_ID_FRAME_LOGIN.IsOpenPassWordProc() )
//		//{
//		//	int length = glsid.length();
//  //          s_CUI_ID_FRAME_LOGIN.SetPasswordProc(glsid.substr(length-6,6));
//  //          s_CUI_ID_FRAME_LOGIN.SetGlsid(glsid);
//		//	InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), -4); // 通过login，显示密保卡输入界面...
//		//	return 0;
//		//}
//
//		std::string md5Result = "";
//		std::stringstream sstrSha1;
//		if( !GetPwdSha1("123", "8001", md5Result, sstrSha1) )
//			return 0;
//
//		//// execute login
//		//args.clear();
//		//result.clear();
//
//
//		//// 不用密保卡登录
//		//LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Execute (login) ..." );
//
//		//args[0] = pAccount->szID;
//		//args[1] = glsid;
//		//args[2] = md5Result;
//		//args[3] = s_CUI_ID_FRAME_LOGIN.GetClientLoginType();
//		//if (!c.execute("login_vtype", args, result))
//		//{
//		//	c.close();
//		//	InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), 1);
//		//	return 0;
//		//}
//		//c.close();
//
//		//if (result.hasMember("faultCode"))
//		//{
//		//	int err = result["faultCode"];
//
//		//	if (err == 1207)
//		//	{
//		//		std::string msg = result["faultString"];
//		//		CUI_ID_FRAME_LOGIN::g_nQueueNumber = atoi(msg.c_str());
//		//		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), err);
//		//	}
//		//	else if (err == 1006)
//		//	{
//		//		std::string msg = result["faultString"];
//		//		int code = atoi(msg.c_str());
//		//		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), code);
//		//	}
//		//	else
//		//		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), err);
//
//		//	return 0;
//		//}
//
//		//int guid = result["guid"];
//
//		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), -1); // 通过login，显示正在进入游戏...
//		QueryUserStatus("8001", 0, sstrSha1);
//	}
//	catch (const XmlRpcException& e)
//	{
//		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, "GLS Login Exception (%s)", e.getMessage().c_str());
//	}
//
//	return 0;
//#endif
}

DWORD WINAPI ConnectPwdProtectThreadProc( LPVOID lpParam )
{
	using namespace XmlRpc;

	try
	{
		Sleep(100);

		CUI_ID_FRAME_LOGIN::SAccountPwdProtectInfo* pAccountPwdProtect = (CUI_ID_FRAME_LOGIN::SAccountPwdProtectInfo*)lpParam;

		CUI_ID_FRAME_LOGIN::g_nQueueNumber = INT_MAX;

		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_bSwitchGate), 0);
		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), 0);
		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nLoginLastStatus), 0);
		InterlockedExchange((LONG*)(&CUI_ID_FRAME_Select::m_time), 0);
        s_CUI_ID_FRAME_Select.SetLastIp("");
        s_CUI_ID_FRAME_Select.SetLastTime("");
        s_CUI_ID_FRAME_Select.SetLastAddress("");


		//
		/*XmlRpcValue args;
		XmlRpcClient c(gCfg.m_szDstIP, gCfg.m_iServerPort, "/gls");
		XmlRpcValue result;*/

		//
		// login
		//
		std::string md5Result = "";
		std::stringstream sstrSha1;
		if( !GetPwdSha1(pAccountPwdProtect->stAccountInfo.szPwd, pAccountPwdProtect->strGlsid, md5Result, sstrSha1) )
			return 0;

		// execute login
		/*args.clear();
		result.clear();*/

		LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Execute (login) Pwd Protect..." );

		/*args[0] = pAccountPwdProtect->stAccountInfo.szID;
		args[1] = pAccountPwdProtect->strGlsid.c_str();
		args[2] = md5Result;
		args[3] = s_CUI_ID_FRAME_LOGIN.GetClientLoginType();
		args[4]	= pAccountPwdProtect->strPwrProtectResult.c_str();
		if (!c.execute("login_mb", args, result))
		{
			c.close();
			InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), 1);
			return 0;
		}

		c.close();
		if (result.hasMember("faultCode"))
		{
			int err = result["faultCode"];

			if (err == 1207)
			{
				std::string msg = result["faultString"];
				CUI_ID_FRAME_LOGIN::g_nQueueNumber = atoi(msg.c_str());
				InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), err);
			}
			else if (err == 1006)
			{
				std::string msg = result["faultString"];
				int code = atoi(msg.c_str());
				InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), code);
			}
			else
				InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), err);

			return 0;
		}

		int guid = result["guid"];*/

		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), -1); // 通过login，显示正在进入游戏...

		////
		//// execute query_user_status
		//// 
		QueryUserStatus(pAccountPwdProtect->strGlsid, 123, sstrSha1);
	}
	catch (const XmlRpcException& e)
	{
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, "GLS Login Exception (%s)", e.getMessage().c_str());
	}

	return 0;
}
void CUI_ID_FRAME_LOGIN::setBtnAndInfoInLoging( bool result )
{
	guardfunc;
	if( result == FALSE )
	{
		if( !s_CUI_ID_FRAME_LOGIN.GetUserReConnect() )
			s_CUI_ID_FRAME_LOGIN.SetEnable(true);
	}
	else
	{

	}
	unguard;
}
void CUI_ID_FRAME_LOGIN::SetLoginInfo( const char *szText)
{
	guardfunc;
	std::string str = szText;
// 	if( m_pID_TEXT_LoginInfo )
// 	{
// 		m_pID_TEXT_LoginInfo->SetText( str.c_str(), Color_Config.getColor(CC_LoginUI_TextInfo) );
// 	}
	unguard;
}
void CUI_ID_FRAME_LOGIN::ShowConnectedDlg()
{
	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_ConFail),
						theXmlString.GetString(eText_ConFail) );
	//*m_pID_TEXT_LoginInfo = "";
}

// Button
bool CUI_ID_FRAME_LOGIN::ProcessLog( )
{
#ifdef _DEBUG //lyh屏蔽日志
	FILE *fp = fopen( "MsgLog.log", "rb" );
	if( !fp )
		return false;

	fseek ( fp, 0, SEEK_END );
	DWORD dwFileSize = ftell( fp );
	rewind( fp );

	char szBuffer[1024] = {0};
	if( dwFileSize > 1024 )
	{
		dwFileSize = 1024;
	}

	fread( szBuffer, dwFileSize, 1, fp );

	MsgClientLog msg;

	memcpy( msg.szLog, szBuffer, sizeof(char)*1024 );
	memcpy( msg.szName, m_stAccount.szID, sizeof(char)*32 );
	GettheNetworkInput().SendMsg( &msg, msg.GetLength() );

	fclose (fp);

	DeleteFile( "MsgLog.log" );
#endif
	return true;
}	

bool CUI_ID_FRAME_LOGIN::CancelLogin(const char bPressYesButton, void *pData)
{
	if (!bPressYesButton) 
	{
		s_CUI_ID_FRAME_LOGIN.m_bLogining = false;

		/*CUI_ID_FRAME_LOGIN::m_bNeedAckAgain = true;*/
		CUI_ID_FRAME_LOGIN::g_bSwitchGate = false;

		if (s_CUI_ID_FRAME_MessageBox.IsTimeOut())
		{
			if (CUI_ID_FRAME_LOGIN::g_nError == 1000)
			{
				CUI_ID_FRAME_LOGIN::m_bShowQueue = true;
			}
			else
			{
				MsgExit msg;
				GettheNetworkInput().SendMsg( &msg );
				//GettheNetworkInput().CheckSendReq();

				if (s_CUI_ID_FRAME_LOGIN.m_Handle)
				{
					TerminateThread( s_CUI_ID_FRAME_LOGIN.m_Handle, 0 );
					CloseHandle( s_CUI_ID_FRAME_LOGIN.m_Handle );
					s_CUI_ID_FRAME_LOGIN.m_Handle = NULL;
				}

				s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_ServerBusy), "", 
					CUI_ID_FRAME_MessageBox::eTypeConfirm, true, CUI_ID_FRAME_LOGIN::connectFailed );
			}
		}
		else
		{
			if (CUI_ID_FRAME_LOGIN::g_nLoginLastStatus == -2 || CUI_ID_FRAME_LOGIN::g_nLoginLastStatus == -3)
			{
				MsgExit msg;
				GettheNetworkInput().SendMsg( &msg );
				//GettheNetworkInput().CheckSendReq();
			}

			if (s_CUI_ID_FRAME_LOGIN.m_Handle)
			{
				TerminateThread( s_CUI_ID_FRAME_LOGIN.m_Handle, 0 );
				CloseHandle( s_CUI_ID_FRAME_LOGIN.m_Handle );
				s_CUI_ID_FRAME_LOGIN.m_Handle = NULL;
			}

			{
				/*XmlRpc::XmlRpcClient c(gCfg.m_szDstIP, gCfg.m_iServerPort, "/");
				XmlRpc::XmlRpcValue result;
				c.execute("cancel", s_glsUserData, result);
			    c.close();*/
			}

			if( s_CUI_ID_FRAME_Select.GetFrame() )
				s_CUI_ID_FRAME_Select.ID_BUTTON_LEAVEOnButtonClick(0);
			if( s_CUI_ID_FRAME_LOGIN.GetFrame() )
				s_CUI_ID_FRAME_LOGIN.showSelectServerListHideOther();
		}
	}
	return true;
}

bool CUI_ID_FRAME_LOGIN::CancelLoginFromPwdProtect()
{
	s_CUI_ID_FRAME_LOGIN.m_bLogining = false;
	//XmlRpc::XmlRpcClient c(gCfg.m_szDstIP, gCfg.m_iServerPort, "/");
	//XmlRpc::XmlRpcValue result;
	//c.execute("cancel", s_glsUserData, result);
	//c.close();

	return true;
}

// Button
bool CUI_ID_FRAME_LOGIN::ID_BUTTON_OKOnButtonClick( ControlObject* pSender ,bool isForced)
{
/////////test http post////////////////////////////////////
	//SHttpTask* pTask = new SHttpTask;
	//pTask->task_type = etasktype::etasktype_login;
	//pTask->task_detail.accountinfo.user_name;
	//pTask->task_detail.accountinfo.passwords;
	//theHttpEncapsulation.AddHttTask(pTask);
	//return false;
///////////////////////////////////////////////////////////

	if( !m_pID_FRAME_LOGIN )
		return false;
//重写登录，更简单，但是不是优化，只是开发阶段而已 by vvx 2012.4.9
	if( !IsVisable() )
		return false;

	if ( !CheckCurServer() )
	{
		s_CUI_ID_FRAME_LOGIN.changeServerListOnClick( NULL );
		return false;
	}

	char szID[128] = {0};
	strncpy(szID, m_pID_EDIT_ID->GetText(), sizeof(szID)/sizeof(char)-1 );
	strlwr(szID);
	std::string szPwd = m_pID_EDIT_PAS->GetText();
	// 默认选择当前服务器	added by zhuomeng.hu		[8/19/2010]
	int nselectIndex = s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->GetCurSelIndex();
	if( nselectIndex != -1 )
		ProcessResult();
	s_CUI_ID_FRAME_LOGIN.hideSoftKeyboard();

	if( strcmp(gCfg.m_szDstIP, "") == 0 ) 
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SelectServer),
			"" );
		return false;
	}

	if ( strlen(szID) <= 0 || (szPwd.length()) <= 0 )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_EnterUsePass),
			"" );
		return false;
	}

	if ( CheckIsBad() )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_Login_ErrorServer),
			"" );
		return false;
	}

	strncpy( m_stAccount.szID, szID, sizeof(m_stAccount.szID)-1 );
	strncpy( m_stAccount.szPwd, szPwd.c_str(), sizeof(m_stAccount.szPwd)-1 );
	theHeroGame.SetUserName(szID);

	if (!EncodeAccountInfo(&m_stAccount))
	{
		return false;
	}
//	DecodeAccountInfo(&m_stAccount);

	if (m_Handle)
	{
		TerminateThread( m_Handle, 0 );
		CloseHandle( m_Handle );
		m_Handle = NULL;
	}
	 //lyh 取消掉倒计时的取消button
	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_ValidateUser), "", CUI_ID_FRAME_MessageBox::eTypeNothing, true/*, CancelLogin*/); //lyh去掉关联函数 防止ese 去调用
	// 验证200秒改成60秒
	s_CUI_ID_FRAME_MessageBox.SetAutoClose(60, false);
	s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(false); //lyh 改为false ，防止 ese 关闭掉 消息框

	CUI_ID_FRAME_LOGIN::m_bShowQueue = true;
	m_bLogining = true;
	CUI_ID_FRAME_LOGIN::g_bEndGetCharacter = FALSE;
	s_CUI_ID_FRAME_LOGIN.m_Handle = CreateThread( NULL, 0, ConnectThreadProc, &m_stAccount, 0, NULL );
	//ConnectThreadProc(&m_stAccount);
	WriteSettings();
	CUserData::Instance()->SetAccountString(m_stAccount.szID);
	CUserData::Instance()->SetArea(m_strArea.c_str());
	std::string serverName = m_strServer;
	size_t pos = m_strServer.find(" ");
	if (pos != std::string::npos)
		serverName = serverName.substr(0, pos);
	CUserData::Instance()->SetServerString(serverName.c_str());

	s_CUI_ID_FRAME_Select.ClearPlayerData();

	//SHttpTask* pTask = new SHttpTask;
	//pTask->task_type = etasktype::etasktype_login;
	//strncpy( pTask->task_detail.accountinfo.user_name, m_stAccount.szID, MAX_USERNAME-1 );
	//strncpy( pTask->task_detail.accountinfo.passwords, m_stAccount.szPwd, MAX_PASSWORDS-1 );
	//theHttpEncapsulation.AddHttTask(pTask);
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef USE_OLD_LOGIN
	guardfunc;

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "");
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Start connect login \t[%s:%d] ...", gCfg.m_szDstIP, gCfg.m_iServerPort);

	//BOOL bResult = FALSE;
	jumpToNextTime = true;
	if (!g_bConnectSuccFlag)
	{
		if (!theHeroGame.StartConnectToGate( gCfg.m_szDstIP, gCfg.m_iServerPort ))
			Sleep(500); // 等待连接线程连接服务器
	}

	if( s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->GetCurSelIndex() == -1 )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SelectServer),
			""/*theXmlString.GetString(eText_Prompt)*/ );
		return false;
	}

	s_CUI_ID_FRAME_LOGIN.hideSoftKeyboard();

	if( !g_bConnectSuccFlag )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_TimeLongConnectFailed) );
		return false;
	}

	const char *szID = m_pID_EDIT_ID->GetText();
	const char *szPwd = m_pID_EDIT_PAS->GetText();	

	if( strcmp(gCfg.m_szDstIP, "") == 0 ) 
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SelectServer),
							""/*theXmlString.GetString(eText_Prompt)*/ );
		return false;
	}

	if ( strlen(szID) <= 0 || strlen(szPwd) <= 0 )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_EnterUsePass),
							""/*theXmlString.GetString(eText_Prompt)*/ );
		return false;
	}

	/*CONST INT MAX_PASSWORD_LEN = 12;*/
	CONST INT MAX_PASSWORD_LEN = 20;

	if( strlen(szPwd) > MAX_PASSWORD_LEN )
	{
		s_CUI_ID_FRAME_MessageBox.Show( "The length of Password must less than 20 characters" );
		return false;
	}

	{
		strcpy( m_stAccount.szID, szID );
		strcpy( m_stAccount.szPwd, szPwd );
	}

	//UI_MessageBox::Show( "当前队列位置为: 1 \n当前服务器总人数为: 100" , "", MB_OK);
	//*m_pID_TEXT_LoginWait = "正在登入...";
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Start connect Server ...");
	//theHeroGame.SetLoginWait();

	//m_Handle = CreateThread( NULL, 0,
	//	ConnectThreadProc, &m_stAccount,
	//	0, NULL );

	m_tmStartLogin = HQ_TimeGetTime();

	s_CUI_ID_FRAME_LOGIN.SetEnable( false );
	s_CUI_ID_FRAME_LOGIN.setBtnDisable();
	if( theHeroGame.login2LoginServer( m_stAccount.szID, m_stAccount.szPwd, IsKeyboardChar ,isForced) )
	{
		setBtnAndInfoInLoging( true );
		s_CUI_ID_FRAME_LOGIN.clearKeyboardChar();
	}
	else
	{
		setBtnAndInfoInLoging( false );
		//m_pID_EDIT_PAS->SetText(theHeroGame.m_LoginPWD);
		//m_pID_EDIT_ID->SetText(theHeroGame.m_LoginName);
	}

	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_NowTryConnecting), "", CUI_ID_FRAME_MessageBox::eTypeCancel, true, CancelLogin);
	s_CUI_ID_FRAME_MessageBox.SetAutoClose(30, false);

// 	for( int i=0; i<MAX_PLAYER_COUNT;i++)
// 	{
// 		s_CUI_ID_FRAME_Select.m_bSlotIsUsed[i] = FALSE;
// 	}

	//WriteConfigXml(m_strConfigPath.c_str());
	WriteSettings();

    CUserData::Instance()->SetAccountString(m_stAccount.szID);
    CUserData::Instance()->SetArea(strAreas[0].c_str());
    CUserData::Instance()->SetServerString(m_strServer.c_str());

	g_bCreateOk = FALSE;
	bRotFreezed = true;
	m_bLogining = true;

	return true;
	unguard;
#else
//    if( !IsVisable() )
//        return false;
//
//	char szID[128] = {0};
//	strncpy(szID, m_pID_EDIT_ID->GetText(), sizeof(szID)/sizeof(char)-1 );
//	strlwr(szID);
//	std::string szPwd = m_pID_EDIT_PAS->GetText();	
//
//	// 默认选择当前服务器	added by zhuomeng.hu		[8/19/2010]
//	int nselectIndex = s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->GetCurSelIndex();
//	if( nselectIndex != -1 )
//		ProcessResult();
//	s_CUI_ID_FRAME_LOGIN.hideSoftKeyboard();
//
//	if( strcmp(gCfg.m_szDstIP, "") == 0 ) 
//	{
//		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SelectServer),
//			"" );
//		return false;
//	}
//
//	if ( strlen(szID) <= 0 || (szPwd.length()) <= 0 )
//	{
//		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_EnterUsePass),
//			"" );
//		return false;
//	}
//
//	strncpy( m_stAccount.szID, szID, sizeof(m_stAccount.szID)-1 );
//	strncpy( m_stAccount.szPwd, szPwd.c_str(), sizeof(m_stAccount.szPwd)-1 );
//	theHeroGame.SetUserName(szID);
//
//	if (m_Handle)
//	{
//		TerminateThread( m_Handle, 0 );
//		CloseHandle( m_Handle );
//		m_Handle = NULL;
//	}
//
//	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_ValidateUser), "", CUI_ID_FRAME_MessageBox::eTypeCancel, true, CancelLogin);
//	s_CUI_ID_FRAME_MessageBox.SetAutoClose(20, false);
//	s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(false);
//
//	//LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "");
//	//LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Start connect GLS ...");
//
//// 	s_CUI_ID_FRAME_LOGIN.m_dwLoginStartTime = HQ_TimeGetTime();
//	CUI_ID_FRAME_LOGIN::m_bShowQueue = true;
//
//	m_bLogining = true;
//	CUI_ID_FRAME_LOGIN::g_bEndGetCharacter = FALSE;
//
//	s_CUI_ID_FRAME_LOGIN.m_Handle = CreateThread( NULL, 0, ConnectThreadProc, &m_stAccount, 0, NULL );
//
//	WriteSettings();
//
//    CUserData::Instance()->SetAccountString(m_stAccount.szID);
//    CUserData::Instance()->SetArea(m_strArea.c_str());
//
//	std::string serverName = m_strServer;
//	size_t pos = m_strServer.find(" ");
//	if (pos != std::string::npos)
//		serverName = serverName.substr(0, pos);
//    CUserData::Instance()->SetServerString(serverName.c_str());
//
//	s_CUI_ID_FRAME_Select.ClearPlayerData();
//
//	//
//	std::string sessionStr = theHeroGame.GetPlayerMgr()->m_strSessionKey;
//	MsgLoginInfo msg;
//	msg.nAccountID             = 123;
//	strncpy_s( msg.szIP,       sizeof(msg.szIP ),      "127.0.0.1",        sizeof(msg.szIP)-1)       ;
//	strncpy_s( msg.SessionKey, sizeof(msg.SessionKey), sessionStr.c_str(),	   sizeof(msg.SessionKey )-1 );
//	strncpy_s( msg.szAccount,  sizeof(msg.szAccount),  "123",				   sizeof(msg.szAccount)-1   );
//	strncpy_s( msg.Password,   sizeof(msg.Password),   "123",				   sizeof(msg.Password)-1    );
//	strncpy_s( msg.Seed ,      sizeof(msg.Seed),       "" ,					   sizeof(msg.Seed)-1        );
//	msg.isWallow               = false;
//	GettheNetworkInput().SendMsg(&msg);
//	//
	return true;
#endif
}

bool CUI_ID_FRAME_LOGIN::ID_BUTTON_CGOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_LOGIN )
		return false;
	
	// 暂时只播放第一个视频, 以后以列表形式选择播放
	CMovieManager::Instance()->OpenByType(CMovieManager::Type_Login);

	return true;
	unguard;
}

bool CUI_ID_FRAME_LOGIN::ID_BUTTON_EXITOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_LOGIN )
		return false;
	if (m_Handle)
	{
		TerminateThread( m_Handle, 0 );
		CloseHandle( m_Handle );
		m_Handle = NULL;
	}

	s_CUI_ID_FRAME_LOGIN.hideSoftKeyboard();
	g_DynamicMapLoadThreadWillExit = TRUE;
	SetEvent(g_hDynamicLoadMap);
	g_bCloseApp = TRUE;

	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_LOGIN::ID_BUTTON_ProducerOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_LOGIN )
		return false;
	ChangeGameState( G_LOGIN,G_PRODUCER );
	return true;
	unguard;
}

void CUI_ID_FRAME_LOGIN::ID_List_Serverlist2OnLDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !s_CUI_ID_FRAME_LOGIN.GetFrame() )
		return;
	s_CUI_ID_FRAME_LOGIN.confirmServerListOnClick( NULL );
}
void CUI_ID_FRAME_LOGIN::connectLoginServer( ControlObject* pSender, ControlList::S_List* pItem )
{
	guardfunc;

	GetErrorLog()->logString( "ID_List_ServerlistOnSelect ..................." );

    // 记录m_strArea
    //ControlList::S_List* pList = NULL;//s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList->GetCurSelItem();
	ControlList::S_List* pList = s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList->GetCurSelItem();
    if( pList == NULL )
        return;
    s_CUI_ID_FRAME_LOGIN.m_strArea = pList->m_szNote;

    pList = pItem;
    if( pList == NULL )
    {
	    pList = s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->GetCurSelItem();
	    if( pList == NULL )
		    return ;
    }
	GetErrorLog()->logString( "ID_List_ServerlistOnSelect" );
	std::string szName = pList->m_szNote;

    s_CUI_ID_FRAME_LOGIN.GetServerInfo( szName );

#ifdef USE_OLD_LOGIN
	SAccountInfo& account = s_CUI_ID_FRAME_LOGIN.getAccountInfo();
	s_CUI_ID_FRAME_LOGIN.m_Handle = CreateThread( NULL, 0, ConnectThreadProc, &account, 0, NULL );
#endif
	s_CUI_ID_FRAME_LOGIN.SetEnable(true);
	s_CUI_ID_FRAME_LOGIN.hideSoftKeyboard();

	unguard;
}
// 快速注册
bool CUI_ID_FRAME_LOGIN::ID_BUTTON_FastRegisterOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_LOGIN )
		return false;
	// 开始组合字符串
	int nSelectIndex = s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->GetCurSelIndex();
	if( nSelectIndex == -1 )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SelectServer),"" );
		return false;
	}
	
    CServerList::ServerData* pServerData = m_serverList.GetServerData(strBigAreas[m_nBigAreaIndex].c_str(), m_strArea.c_str(), vctServerInfo[nSelectIndex].strName.c_str());
    if( !pServerData )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SelectServer),"" );
		return false;
	}
	
	int iArea = -1;
	if ( iArea == -1 )
	{
		s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SelectServer),"" );
		return false;
	}

	//char szUrl[MaxStringSize] = { 0 };

	//_snprintf(szUrl,sizeof(szUrl)-1,"%sgid=%s&areaid=%s",gCfg.m_szHomePagePrefix,
	//													 CCfg::Areas[iArea].gid.c_str(),
	//													 CCfg::Areas[iArea].areaid.c_str());

	ShellExecute( NULL, "open", gCfg.m_szHomePagePrefix, NULL, NULL, 0 );
	return true;
}

// List
void CUI_ID_FRAME_LOGIN::ID_LIST_ServerlistOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_LOGIN )
		return;
    // 选择区，刷新服务器列表
    //ControlList::S_List* pList = 0;//s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList->GetCurSelItem();
	ControlList::S_List* pList = s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList->GetCurSelItem();
    if( pList == NULL )
		return;
    //std::string szAreaName;// = pList->m_szNote;
	std::string szAreaName = pList->m_szNote;
    if( m_strLastSelectArea != szAreaName )
    {
        m_strLastSelectArea = szAreaName;
        RefreshAreaServerArray(m_nBigAreaIndex, szAreaName);
        if( m_strArea == szAreaName )
            ListShowServerInfo(m_strServer);
        else
            ListShowServerInfo();
    }
}
// List
void CUI_ID_FRAME_LOGIN::ID_LIST_Serverlist2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_LOGIN )
		return;
}
// List
void CUI_ID_FRAME_LOGIN::ID_LIST_ServerName2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_LOGIN )
		return;
}
// List
void CUI_ID_FRAME_LOGIN::ID_LIST_ServerState2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_LOGIN )
		return;
}
// Button
bool CUI_ID_FRAME_LOGIN::ID_BUTTON_ConfirmSelectServerOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_LOGIN )
		return false;
    s_CUI_ID_FRAME_LOGIN.confirmServerListOnClick(pSender);
	return true;
}
// Button
bool CUI_ID_FRAME_LOGIN::ID_BUTTON_AreaNameOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_LOGIN )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_LOGIN::ID_BUTTON_ServerNameOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_LOGIN )
		return false;
	return true;
}

// Button
bool CUI_ID_FRAME_LOGIN::ID_BUTTON_QuitOnButtonClick( ControlObject* pSender )
{
	//modified by zhuomeng.hu		[8/19/2010]
    //s_CUI_ID_FRAME_LOGIN.ID_BUTTON_EXITOnButtonClick(pSender);
	s_CUI_ID_FRAME_LOGIN.showSelectServerListHideOther( false );
	return true;
}
// List
void CUI_ID_FRAME_LOGIN::ID_LIST_AreaNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_LOGIN )
		return;
//    s_CUI_ID_FRAME_LOGIN.m_pID_LIST_AreaName->SetCurSelIndex(-1);
}
// List
void CUI_ID_FRAME_LOGIN::ID_LIST_ServerNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_LOGIN )
		return;
//    s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerName->SetCurSelIndex(-1);
}
// CheckBox
void CUI_ID_FRAME_LOGIN::ID_CHECKBOX_ShortCutKeyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_LOGIN )
		return;
    s_CUI_ID_FRAME_SoftKeyboard.SetVisable(*pbChecked);
    // 光标移到输入密码框
    theUiManager.SetFocus( s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_PAS );
	setFocusInAccount(false);
	setFocusInPassword(true);

    CUserData::Instance()->SetSoftKeyboard( *pbChecked );
    if( m_pID_CHECKBOX_ShortCutKey->IsChecked() )
    {
        char tip[MAX_PATH] = {0};
        strcpy(tip,theXmlString.GetString(eText_DisableSoftKeyboard));
//        m_pID_PICTURE_ShortCutKeyTip->setTip(tip);
    }
    else
    {
        char tip[MAX_PATH] = {0};
        strcpy(tip,theXmlString.GetString(eText_EnableSoftKeyboard));
//        m_pID_PICTURE_ShortCutKeyTip->setTip(tip);
    }
}

// Button
bool CUI_ID_FRAME_LOGIN::ID_BUTTON_BroadcastOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_LOGIN )
		return false;
    m_bShowBroadcast = false;
    m_GroupBroadcast.SetVisible(false);

	//modified by zhuomeng.hu		[8/19/2010]
    //if( !m_bGotRegionServerIpPort )
    //{
    //    showSelectServerListHideOther();	// 选区
    //}
    //else 
    //{
     	showSelectServerListHideOther(false);	// 登录
    //}
    return true;
}
// ScrollBar
void CUI_ID_FRAME_LOGIN::ID_SCROLLBAR_BroadcastOnScrollBarUpdatePos( ControlObject* pSender, int n )
{
	if( !m_pID_FRAME_LOGIN )
		return;
   //控制文件的显示
	char szWord[64] = {0};
    sprintf_s(szWord,sizeof(szWord)-1, "%d",n);
    Trace(szWord);
}

// List
void CUI_ID_FRAME_LOGIN::ID_LIST_ServerStateOtherOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_LOGIN )
		return;
}

// List
void CUI_ID_FRAME_LOGIN::ID_LIST_ServerStateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_LOGIN )
		return;
}
// List
void CUI_ID_FRAME_LOGIN::ID_LIST_ServerStateOther2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_LOGIN )
		return;
}

// List
void CUI_ID_FRAME_LOGIN::ID_LIST_ServerPing2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}


void CUI_ID_FRAME_LOGIN::ID_CHECKBOX_PasswordProtectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_LOGIN )
		return;
	if( getFocusInAccount() )
		theUiManager.SetFocus( s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_ID );
	else if( getFocusInPassword() )
		theUiManager.SetFocus( s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_PAS );
}


//added by zhuomeng.hu		[8/18/2010]
// CheckBox
void CUI_ID_FRAME_LOGIN::ID_CHECKBOX_SelectBoardOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_LOGIN )
	{
		assert( false && "ui error" );
		return;
	}
	if( pbChecked )
	{
		m_pID_CHECKBOX_SelectBoard->SetCheck( true );
		m_pID_CHECKBOX_SelectService->SetCheck( false );
		m_GroupGongGao.SetVisible( true );
		m_GroupKeFu.SetVisible( false );		
	}
}
// CheckBox
void CUI_ID_FRAME_LOGIN::ID_CHECKBOX_SelectServiceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_LOGIN )
	{
		assert( false && "ui error" );
		return;
	}
	if( pbChecked )
	{
		m_pID_CHECKBOX_SelectBoard->SetCheck( false );
		m_pID_CHECKBOX_SelectService->SetCheck( true );
		m_GroupGongGao.SetVisible( false );
		m_GroupKeFu.SetVisible( true );		
	}
}
// ListImg / ListEx
bool CUI_ID_FRAME_LOGIN::ID_LISTIMG_ActivityIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															 ControlIconDrag::S_ListImg* pItemDrag,
															 ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_LOGIN )
		return false;
	return false;
}
bool CUI_ID_FRAME_LOGIN::ID_LISTIMG_ActivityIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_LOGIN )
		return false;
	return false;
}
bool CUI_ID_FRAME_LOGIN::ID_LISTIMG_ActivityIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_LOGIN )
		return false;
	
	int i = m_pID_LISTIMG_ActivityIcon->GetItemIndex( m_pID_LISTIMG_ActivityIcon->GetCurSelItem() );
	m_pID_TEXT_ActivityDesc->SetText( m_activityContentVec[i].description.c_str() );
    if( pItem && m_pSelectItem && m_pSelectItem->m_pkIconInfo && pItem->m_pkIconInfo )
    {
        m_pSelectItem->m_pkIconInfo->SetColorFrameType( eColorFrame_None );
        pItem->m_pkIconInfo->SetColorFrameType( eColorFrame_Select );
        m_pSelectItem = pItem;
    }
	return true;
}
bool CUI_ID_FRAME_LOGIN::ID_LISTIMG_ActivityIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_LOGIN )
		return false;
	return false;
}
// Button
bool CUI_ID_FRAME_LOGIN::ID_BUTTON_PayOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_LOGIN )
		return false;

	ShellExecute( NULL, "open", "http://sg.chcgame.com", NULL, NULL, 0 );
	return true;
}


// 装载UI
bool CUI_ID_FRAME_LOGIN::_LoadUI()
{
	guardfunc;
 
	InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_bSwitchGate), 0);
	
	SavePath();
 	s_CUI_ID_FRAME_SoftKeyboard.LoadUI();
// 	{
// 		char	szScratch [_MAX_PATH];
// 		sprintf(szScratch, theXmlString.GetString( eDumper_MessageBox_ClientError ) );
// 		::MessageBoxA(NULL, szScratch, ApplicationConfig::Instance().GetFullVersion(), MB_OK);
// 		return false;
// 	}

//	g_compoundInfo_configure.load();
// 	s_CUI_ID_FRAME_Register.LoadUI();
	
	s_CUI_ID_FRAME_PasswordProtect.LoadUI();
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Login.meui" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Login.UI]失败")
			return false;
	}

	bRotFreezed = false;
	jumpToNextTime = true;
	bool ret = DoControlConnect();

   if( ret )
    {
        //LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d         Login加载场景开始", GetCurrentThreadId() );
        LoadScene();
        //LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "ThreadId: %d         Login加载场景结束", GetCurrentThreadId() );
    }
	_SetVisable(true);
    return ret;
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_LOGIN::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_LOGIN, s_CUI_ID_FRAME_LOGINOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_LOGIN, s_CUI_ID_FRAME_LOGINOnFrameRender, true);
	theUiManager.OnButtonClick( ID_FRAME_LOGIN, ID_BUTTON_Register, s_CUI_ID_FRAME_LOGINID_BUTTON_RegisterOnButtonClick );
	theUiManager.OnEditEnter( ID_FRAME_LOGIN, ID_EDIT_ID, s_CUI_ID_FRAME_LOGINID_EDIT_IDOnEditEnter );
	theUiManager.OnEditEnter( ID_FRAME_LOGIN, ID_EDIT_PAS, s_CUI_ID_FRAME_LOGINID_EDIT_PASOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_LOGIN, ID_BUTTON_OK, s_CUI_ID_FRAME_LOGINID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_LOGIN, ID_BUTTON_CG, s_CUI_ID_FRAME_LOGINID_BUTTON_CGOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_LOGIN, ID_BUTTON_GameBeforeSet, s_CUI_ID_FRAME_LOGINID_BUTTON_GameBeforeSetOnButtonClick );

	

	theUiManager.OnButtonClick( ID_FRAME_LOGIN, ID_BUTTON_EXIT, s_CUI_ID_FRAME_LOGINID_BUTTON_EXITOnButtonClick );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_LOGIN, ID_CHECKBOX_3D, s_CUI_ID_FRAME_LOGINID_CHECKBOX_3DOnCheckBoxCheck );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_LOGIN, ID_CHECKBOX_25D, s_CUI_ID_FRAME_LOGINID_CHECKBOX_25DOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_LOGIN, ID_CHECKBOX_SAVE, s_CUI_ID_FRAME_LOGINID_CHECKBOX_SAVEOnCheckBoxCheck );
    theUiManager.OnButtonClick( ID_FRAME_LOGIN, ID_BUTTON_KuaiSuZhuCe, s_CUI_ID_FRAME_LOGINID_BUTTON_FastRegisterOnButtonClick );//zjj add[6.30]
    theUiManager.OnListSelectChange( ID_FRAME_LOGIN, ID_LIST_Serverlist, s_CUI_ID_FRAME_LOGINID_LIST_ServerlistOnListSelectChange );
    theUiManager.OnListSelectChange( ID_FRAME_LOGIN, ID_LIST_Serverlist2, s_CUI_ID_FRAME_LOGINID_LIST_Serverlist2OnListSelectChange );
    theUiManager.OnListSelectChange( ID_FRAME_LOGIN, ID_LIST_ServerName2, s_CUI_ID_FRAME_LOGINID_LIST_ServerName2OnListSelectChange );
    theUiManager.OnListSelectChange( ID_FRAME_LOGIN, ID_LIST_ServerState2, s_CUI_ID_FRAME_LOGINID_LIST_ServerState2OnListSelectChange );
    theUiManager.OnButtonClick( ID_FRAME_LOGIN, ID_BUTTON_ConfirmSelectServer, s_CUI_ID_FRAME_LOGINID_BUTTON_ConfirmSelectServerOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_LOGIN, ID_BUTTON_Quit, s_CUI_ID_FRAME_LOGINID_BUTTON_QuitOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_LOGIN, ID_BUTTON_AreaName, s_CUI_ID_FRAME_LOGINID_BUTTON_AreaNameOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_LOGIN, ID_BUTTON_ServerName, s_CUI_ID_FRAME_LOGINID_BUTTON_ServerNameOnButtonClick );
    theUiManager.OnListSelectChange( ID_FRAME_LOGIN, ID_LIST_AreaName, s_CUI_ID_FRAME_LOGINID_LIST_AreaNameOnListSelectChange );
    theUiManager.OnListSelectChange( ID_FRAME_LOGIN, ID_LIST_ServerName, s_CUI_ID_FRAME_LOGINID_LIST_ServerNameOnListSelectChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_LOGIN, ID_CHECKBOX_ShortCutKey, s_CUI_ID_FRAME_LOGINID_CHECKBOX_ShortCutKeyOnCheckBoxCheck );
    theUiManager.OnButtonClick( ID_FRAME_LOGIN, ID_BUTTON_Broadcast, s_CUI_ID_FRAME_LOGINID_BUTTON_BroadcastOnButtonClick );
    theUiManager.OnScrollBarUpdatePos( ID_FRAME_LOGIN, ID_SCROLLBAR_Broadcast, s_CUI_ID_FRAME_LOGINID_SCROLLBAR_BroadcastOnScrollBarUpdatePos );
    theUiManager.OnListSelectChange( ID_FRAME_LOGIN, ID_LIST_ServerStateOther, s_CUI_ID_FRAME_LOGINID_LIST_ServerStateOtherOnListSelectChange );
    theUiManager.OnListSelectChange( ID_FRAME_LOGIN, ID_LIST_ServerState, s_CUI_ID_FRAME_LOGINID_LIST_ServerStateOnListSelectChange );
    theUiManager.OnListSelectChange( ID_FRAME_LOGIN, ID_LIST_ServerStateOther2, s_CUI_ID_FRAME_LOGINID_LIST_ServerStateOther2OnListSelectChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_LOGIN, ID_CHECKBOX_PasswordProtect, s_CUI_ID_FRAME_LOGINID_CHECKBOX_PasswordProtectOnCheckBoxCheck );

	//added by zhuomeng.hu		[8/18/2010]
	theUiManager.OnCheckBoxCheck( ID_FRAME_LOGIN, ID_CHECKBOX_SelectBoard, s_CUI_ID_FRAME_LOGINID_CHECKBOX_SelectBoardOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_LOGIN, ID_CHECKBOX_SelectService, s_CUI_ID_FRAME_LOGINID_CHECKBOX_SelectServiceOnCheckBoxCheck );
	theUiManager.OnIconDragOn( ID_FRAME_LOGIN, ID_LISTIMG_ActivityIcon, s_CUI_ID_FRAME_LOGINID_LISTIMG_ActivityIconOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_LOGIN, ID_LISTIMG_ActivityIcon, s_CUI_ID_FRAME_LOGINID_LISTIMG_ActivityIconOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_LOGIN, ID_LISTIMG_ActivityIcon, s_CUI_ID_FRAME_LOGINID_LISTIMG_ActivityIconOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_LOGIN, ID_LISTIMG_ActivityIcon, s_CUI_ID_FRAME_LOGINID_LISTIMG_ActivityIconOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_LOGIN, ID_BUTTON_Pay, s_CUI_ID_FRAME_LOGINID_BUTTON_PayOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_LOGIN, ID_LIST_ServerPing2, s_CUI_ID_FRAME_LOGINID_LIST_ServerPing2OnListSelectChange );

	m_pID_FRAME_LOGIN = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_LOGIN );
	m_pID_EDIT_ID = (ControlEdit*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_EDIT_ID );
	m_pID_EDIT_PAS = (ControlEdit*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_EDIT_PAS );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_OK );
//	m_pID_TEXT_SEREV = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_SEREV );
	m_pID_BUTTON_CG = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_CG );

	m_pID_BUTTON_GameBeforeSet = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_GameBeforeSet );
	assert(m_pID_BUTTON_GameBeforeSet);

	m_pID_BUTTON_EXIT = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_EXIT );
	m_pID_CHECKBOX_SAVE = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_CHECKBOX_SAVE );
//	m_pID_TEXT_LoginWait = (ControlText*)theUiManager.FindControl(ID_FRAME_LOGIN, ID_TEXT_LoginWait);
//	m_pID_BUTTON_cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_Cancel );
//	m_pID_TEXT_LoginInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_LoginInfo );
	m_pID_BUTTON_Register = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_Register );
	m_pID_TEXT_Ver = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_Ver );
//	m_pID_BUTTON_KuaiSuZhuCe = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_KuaiSuZhuCe );
//	m_pID_PICTURE_Serverback = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_Serverback );
//	m_pID_PICTURE_Serverback1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_Serverback1 );
//	m_pID_TEXT_3D = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_3D );
//	m_pID_TEXT_25D = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_25D );
//	m_pID_CHECKBOX_3D = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_CHECKBOX_3D );
//	m_pID_CHECKBOX_25D = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_CHECKBOX_25D );
//	assert(m_pID_BUTTON_KuaiSuZhuCe);
 	m_pID_LIST_ServerList = (ControlList*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_LIST_Serverlist );
 	assert( m_pID_LIST_ServerList );
	m_pID_LIST_ZuiJin = (ControlList*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_LIST_ZuiJin );
	m_pID_BUTTON_Change = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_Change );
	assert( m_pID_BUTTON_Change );
	m_pID_BUTTON_Change->SetButtonClickFun( changeServerListOnClick );
	m_pID_PICTURE_ServerListBack = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_ServerListBack );
	assert( m_pID_PICTURE_ServerListBack );
	m_pID_BUTTON_ConfirmSelectServer = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_ConfirmSelectServer );
	assert( m_pID_BUTTON_ConfirmSelectServer );
	m_pID_BUTTON_ConfirmSelectServer->SetButtonClickFun( confirmServerListOnClick );
//	m_pID_PICTURE_listback = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_listback );
	//assert( m_pID_PICTURE_listback );
//	m_pID_PICTURE_serverback = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_serverback );
	//assert( m_pID_PICTURE_serverback );
//	m_pID_PICTURE_selectserverback = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_selectserverback );
	//assert( m_pID_PICTURE_selectserverback);
//	m_pID_PICTURE_LOGO = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_LOGO );
	//assert( m_pID_PICTURE_LOGO);
//	m_pID_PICTURE_listback2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_listback2 );
	m_pID_LIST_ServerList2 = (ControlList*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_LIST_Serverlist2 );
    assert( m_pID_LIST_ServerList2 );
    m_pID_LIST_ServerList2->SetLDBClickFun( ID_List_Serverlist2OnLDBClick );
	m_pID_LIST_ServerName2 = (ControlList*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_LIST_ServerName2 );
	m_pID_LIST_ServerState2 = (ControlList*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_LIST_ServerState2 );
//	m_pID_TEXT_LatterlyServer = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_LatterlyServer );
	m_pID_BUTTON_ConfirmSelectServer = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_ConfirmSelectServer );
//	m_pID_PICTURE_ServerWall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_ServerWall1 );
// 	m_pID_PICTURE_TitleLeft = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_TitleLeft );
// 	m_pID_PICTURE_TitleRight = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_TitleRight );
// 	m_pID_PICTURE_TitleLeftMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_TitleLeftMiddle );
// 	m_pID_PICTURE_TitleRightMiddle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_TitleRightMiddle );
	//m_pID_PICTURE_Serverback1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_Serverback1 );
//	m_pID_PICTURE_ServerWall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_ServerWall2 );
//	m_pID_PICTURE_ServerWall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_ServerWall3 );
	m_pID_BUTTON_Quit = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_Quit );
//	m_pID_BUTTON_AreaName = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_AreaName );
//	m_pID_BUTTON_ServerName = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_ServerName );
// 	m_pID_LIST_AreaName = (ControlList*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_LIST_AreaName );
// 	m_pID_LIST_ServerName = (ControlList*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_LIST_ServerName );
	m_pID_CHECKBOX_ShortCutKey = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_CHECKBOX_ShortCutKey );
	//m_pID_PICTURE_ShortCutKeyTip = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_ShortCutKeyTip );
    m_pID_BUTTON_Broadcast = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_Broadcast );
//    m_pID_PICTURE_BroadcastTitle = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_BroadcastTitle );
    m_pID_PICTURE_BroadcastWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_BroadcastWall );
    m_pID_TEXT_Broadcast = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_Broadcast );
//    m_pID_SCROLLBAR_Broadcast = (ControlScrollBar*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_SCROLLBAR_Broadcast );
	m_pID_LIST_ServerStateOther = (ControlList*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_LIST_ServerStateOther );

//    m_pID_LIST_ServerState = (ControlList*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_LIST_ServerState );
//    m_pID_LIST_ServerStateOther2 = (ControlList*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_LIST_ServerStateOther2 );
// 	m_pID_CHECKBOX_PasswordProtect = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_CHECKBOX_PasswordProtect );
// 	m_pID_TEXT_PasswordProtect = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_PasswordProtect );

	//added by zhuomeng.hu		[8/18/2010]
//	m_pID_TEXT_Ba = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_Ba );
	m_pID_CHECKBOX_SelectBoard = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_CHECKBOX_SelectBoard );
	m_pID_CHECKBOX_SelectService = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_CHECKBOX_SelectService );
	m_pID_PICTURE_BgAcrivity = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_BgAcrivity );
	m_pID_TEXT_ActivityDesc = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_ActivityDesc );
	m_pID_TEXT_ActivityText = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_ActivityText );
	m_pID_LISTIMG_ActivityIcon = (ControlListImage*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_LISTIMG_ActivityIcon );
	m_pID_TEXT_CurrentServerText = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_CurrentServerText );
	m_pID_TEXT_CurrentServer = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_CurrentServer );
	m_pID_PICTURE_Logo = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_Logo );
//	m_pID_TEXT_RememberText = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_RememberText );
	m_pID_TEXT_SoftKeyBoardText = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_SoftKeyBoardText );
	m_pID_BUTTON_Pay = (ControlButton*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_BUTTON_Pay );
	m_pID_TEXT_ServiceInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_ServiceInfo );
	m_pID_TEXT_SaveText = (ControlText*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_TEXT_SaveText );
	m_pID_PICTURE_BgBlackbar = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_BgBlackbar );
	m_pID_PICTURE_BgBroadcast = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_BgBroadcast );
	m_pID_PICTURE_BroadcastWall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_BroadcastWall3 );
	m_pID_PICTURE_BroadcastWall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_BroadcastWall2 );

	m_pID_PICTURE_SAVE = (ControlPicture*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_PICTURE_SAVE );
	m_pID_LIST_ServerPing2 = (ControlList*)theUiManager.FindControl( ID_FRAME_LOGIN, ID_LIST_ServerPing2 );
	assert( m_pID_PICTURE_SAVE );
	//added by ZhuoMeng.Hu		[8/30/2010]
	m_pID_LISTIMG_ActivityIcon->ShowPressEffect( true );
	m_pID_LISTIMG_ActivityIcon->SetCanbePick( true );
	m_pID_LISTIMG_ActivityIcon->SetEnableDrag( false );

    assert( m_pID_FRAME_LOGIN );
    m_pID_FRAME_LOGIN->setRenderFlag( eLinearFilter );
	m_pID_FRAME_LOGIN->SetMsgProcFun( frame_msg );
		assert( m_pID_BUTTON_Register );
	m_pID_FRAME_LOGIN->SetOnTab( frameOnTab );
	m_pID_FRAME_LOGIN->SetOnClickFun( frameOnLClick );
	m_pID_FRAME_LOGIN->SetOnTab( OnTab );
	assert( m_pID_EDIT_ID );
	m_pID_EDIT_ID->SetLBtnDownFun( Edit_ID_ONLBtnDown );
	m_pID_EDIT_ID->SetSelectAllAfterTab(true);
	assert( m_pID_EDIT_PAS );
	m_pID_EDIT_PAS->SetLBtnDownFun( Edit_Pass_OnLBtnUp );
	m_pID_EDIT_PAS->SetDelByteFun( Eidt_OnDelByte );
	m_pID_EDIT_PAS->SetSelectAllAfterTab(true);
	assert( m_pID_BUTTON_OK );
	// ui commented out, [9/26/2010 zhangjiayi]
	//assert( m_pID_TEXT_SEREV );
	assert( m_pID_BUTTON_CG );
	assert( m_pID_BUTTON_EXIT );
	assert( m_pID_CHECKBOX_SAVE );
	// ui commented out, [9/26/2010 zhangjiayi]
// 	assert( m_pID_TEXT_LoginWait );
// 	assert( m_pID_BUTTON_cancel );
// 	assert( m_pID_TEXT_LoginInfo );
	assert( m_pID_PICTURE_ServerListBack );
	// ui commented out, [9/26/2010 zhangjiayi]
	//assert( m_pID_PICTURE_listback2 );
	assert( m_pID_LIST_ServerName2 );
	assert( m_pID_LIST_ServerState2 );
	assert( m_pID_LIST_ZuiJin );
	m_pID_LIST_ZuiJin->SetLDBClickFun(s_CUI_ID_FRAME_LOGIN.ID_LIST_ZuiJinOnLDBClick);
	m_pID_LIST_ZuiJin->SetLBtnDownFun(s_CUI_ID_FRAME_LOGIN.ID_LIST_ZuiJinOnLBClick);
	// ui commented out, [9/26/2010 zhangjiayi]
	//assert( m_pID_TEXT_LatterlyServer );
	assert( m_pID_BUTTON_ConfirmSelectServer );
	// ui commented out, [9/26/2010 zhangjiayi]
// 	assert( m_pID_PICTURE_ServerWall1 );
// 	assert( m_pID_PICTURE_TitleLeft );
// 	assert( m_pID_PICTURE_TitleRight );
// 	assert( m_pID_PICTURE_TitleLeftMiddle );
// 	assert( m_pID_PICTURE_TitleRightMiddle );
// 	assert( m_pID_PICTURE_Serverback1 );
// 	assert( m_pID_PICTURE_ServerWall2 );
// 	assert( m_pID_PICTURE_ServerWall3 );
	assert( m_pID_BUTTON_Quit );
	// ui commented out, [9/26/2010 zhangjiayi]
// 	assert( m_pID_BUTTON_AreaName );
// 	assert( m_pID_BUTTON_ServerName );
// 	assert( m_pID_LIST_AreaName );
// 	assert( m_pID_LIST_ServerName );
	assert( m_pID_CHECKBOX_ShortCutKey );
	// ui commented out, [9/26/2010 zhangjiayi]
	//assert( m_pID_PICTURE_ShortCutKeyTip );
    assert( m_pID_BUTTON_Broadcast );
	// ui commented out, [9/26/2010 zhangjiayi]
    //assert( m_pID_PICTURE_BroadcastTitle );
    assert( m_pID_PICTURE_BroadcastWall );
    assert( m_pID_TEXT_Broadcast );
    
	// ui commented out, [9/26/2010 zhangjiayi]
	//assert( m_pID_SCROLLBAR_Broadcast );
	assert( m_pID_LIST_ServerStateOther );

	// ui commented out, [9/26/2010 zhangjiayi]
//     assert( m_pID_LIST_ServerState );
//     assert( m_pID_LIST_ServerStateOther2 );
// 	assert( m_pID_CHECKBOX_PasswordProtect );
// 	assert( m_pID_TEXT_PasswordProtect );

	//added by zhuomeng.hu		[8/18/2010]
	// ui commented out, [9/26/2010 zhangjiayi]
	//assert( m_pID_TEXT_Ba );
	assert( m_pID_CHECKBOX_SelectBoard );
	assert( m_pID_CHECKBOX_SelectService );
	assert( m_pID_PICTURE_BgAcrivity );
	assert( m_pID_TEXT_ActivityDesc );
	assert( m_pID_TEXT_ActivityText );
	assert( m_pID_LISTIMG_ActivityIcon );
	assert( m_pID_TEXT_CurrentServerText );
	assert( m_pID_TEXT_CurrentServer );
	assert( m_pID_PICTURE_Logo );
	// ui commented out, [9/26/2010 zhangjiayi]
	//assert( m_pID_TEXT_RememberText );
	assert( m_pID_TEXT_SoftKeyBoardText );
	assert( m_pID_BUTTON_Pay );
	assert( m_pID_TEXT_ServiceInfo );
	assert( m_pID_TEXT_SaveText );
	assert( m_pID_PICTURE_BgBlackbar );
	assert( m_pID_PICTURE_BgBroadcast );
	assert( m_pID_PICTURE_BroadcastWall3 );
	assert( m_pID_PICTURE_BroadcastWall2 );
	assert( m_pID_LIST_ServerPing2 );

	// ui commented out, [9/26/2010 zhangjiayi]
//     m_pID_LIST_ServerName->SetLBClickFun(s_CUI_ID_FRAME_LOGIN.ID_LIST_ServerNameOnLBClick);
//     m_pID_LIST_ServerName->SetLDBClickFun(s_CUI_ID_FRAME_LOGIN.ID_LIST_ServerNameOnLDBClick);
//     m_pID_LIST_AreaName->SetLBClickFun(s_CUI_ID_FRAME_LOGIN.ID_LIST_AreaNameOnLBClick);
    // 登录界面群组
    m_GroupLogin.Clear();
	m_GroupLogin.AddControl(m_pID_BUTTON_CG);
	m_GroupLogin.AddControl(m_pID_BUTTON_GameBeforeSet);
    m_GroupLogin.AddControl(m_pID_BUTTON_EXIT);
//     m_GroupLogin.AddControl(m_pID_BUTTON_madeNameList);
//     m_GroupLogin.AddControl(m_pID_BUTTON_KuaiSuZhuCe);
//     m_GroupLogin.AddControl(m_pID_BUTTON_cancel);
//     m_GroupLogin.AddControl(m_pID_TEXT_LoginWait);
//     m_GroupLogin.AddControl(m_pID_TEXT_LoginInfo);
    m_GroupLogin.AddControl(m_pID_BUTTON_Change);
	// ui commented out, [9/26/2010 zhangjiayi]
//     m_GroupLogin.AddControl(m_pID_TEXT_SEREV);
//     m_GroupLogin.AddControl(m_pID_TEXT_3D);
//     m_GroupLogin.AddControl(m_pID_TEXT_25D);
    m_GroupLogin.AddControl(m_pID_EDIT_ID);
    m_GroupLogin.AddControl(m_pID_EDIT_PAS);
    //m_GroupLogin.AddControl(m_pID_CHECKBOX_SAVE);
	// ui commented out, [9/26/2010 zhangjiayi]
//     m_GroupLogin.AddControl(m_pID_CHECKBOX_3D);
//     m_GroupLogin.AddControl(m_pID_CHECKBOX_25D);
    m_GroupLogin.AddControl(m_pID_BUTTON_OK);
//     m_GroupLogin.AddControl(m_pID_PICTURE_selectserverback);
//     m_GroupLogin.AddControl(m_pID_PICTURE_LOGO);
    m_GroupLogin.AddControl(m_pID_CHECKBOX_ShortCutKey);
    //m_GroupLogin.AddControl(m_pID_PICTURE_ShortCutKeyTip);
	m_GroupLogin.AddControl(m_pID_BUTTON_Register);

	//added by zhuomeng.hu		[8/18/2010]
	//m_GroupLogin.AddControl( m_pID_TEXT_Ba );
	m_GroupLogin.AddControl( m_pID_BUTTON_Pay );
	m_GroupLogin.AddControl( m_pID_TEXT_CurrentServerText );
	m_GroupLogin.AddControl( m_pID_TEXT_CurrentServer );
	//m_GroupLogin.AddControl( m_pID_TEXT_RememberText );
	m_GroupLogin.AddControl( m_pID_TEXT_SoftKeyBoardText );
	m_GroupLogin.AddControl( m_pID_PICTURE_Logo );
	m_GroupLogin.AddControl( m_pID_TEXT_SaveText );
	m_GroupLogin.AddControl( m_pID_TEXT_SoftKeyBoardText );
	m_GroupLogin.AddControl( m_pID_CHECKBOX_ShortCutKey );
	
	
// 	if( m_bShowPwdProtect )
// 	{
// 		m_GroupLogin.AddControl(m_pID_CHECKBOX_PasswordProtect);
// 		m_GroupLogin.AddControl(m_pID_TEXT_PasswordProtect);
// 	}
// 	else
// 	{
// 		m_pID_CHECKBOX_PasswordProtect->SetVisable(false);
// 		m_pID_TEXT_PasswordProtect->SetVisable(false);
// 	}
    m_GroupLogin.SetVisible(false);

    // 选区选服界面群组
    m_GroupAreaServer.Clear();
    m_GroupAreaServer.AddControl(m_pID_PICTURE_ServerListBack);
    m_GroupAreaServer.AddControl(m_pID_LIST_ServerList);
//     m_GroupAreaServer.AddControl(m_pID_PICTURE_listback2);
    m_GroupAreaServer.AddControl(m_pID_LIST_ServerList2);
    m_GroupAreaServer.AddControl(m_pID_LIST_ServerName2);
    m_GroupAreaServer.AddControl(m_pID_LIST_ServerState2);
	 m_GroupAreaServer.AddControl(m_pID_LIST_ServerPing2);
   // m_GroupAreaServer.AddControl(m_pID_TEXT_LatterlyServer);
    m_GroupAreaServer.AddControl(m_pID_BUTTON_ConfirmSelectServer);
//     m_GroupAreaServer.AddControl(m_pID_PICTURE_listback);
//     m_GroupAreaServer.AddControl(m_pID_PICTURE_serverback);
//     m_GroupAreaServer.AddControl(m_pID_PICTURE_Serverback);
//     m_GroupAreaServer.AddControl(m_pID_PICTURE_Serverback1);
//     m_GroupAreaServer.AddControl(m_pID_PICTURE_ServerWall1);
//     m_GroupAreaServer.AddControl(m_pID_BUTTON_AreaName);
//     m_GroupAreaServer.AddControl(m_pID_BUTTON_ServerName);
//     m_GroupAreaServer.AddControl(m_pID_LIST_AreaName);
//     m_GroupAreaServer.AddControl(m_pID_LIST_ServerName);
//     m_GroupAreaServer.AddControl(m_pID_PICTURE_TitleLeft);
//     m_GroupAreaServer.AddControl(m_pID_PICTURE_TitleRight);
//     m_GroupAreaServer.AddControl(m_pID_PICTURE_TitleLeftMiddle);
//     m_GroupAreaServer.AddControl(m_pID_PICTURE_TitleRightMiddle);
//     m_GroupAreaServer.AddControl(m_pID_PICTURE_ServerWall2);
//     m_GroupAreaServer.AddControl(m_pID_PICTURE_ServerWall3);
    m_GroupAreaServer.AddControl(m_pID_BUTTON_Quit);
    m_GroupAreaServer.AddControl(m_pID_LIST_ServerStateOther);
//     m_GroupAreaServer.AddControl(m_pID_LIST_ServerState);
//     m_GroupAreaServer.AddControl(m_pID_LIST_ServerStateOther2);
	m_GroupAreaServer.AddControl( m_pID_LIST_ZuiJin );

    m_GroupAreaServer.SetVisible(false);
	m_RadioGroupViewSelect.Clear();
// 	m_RadioGroupViewSelect.AddRadio( m_pID_CHECKBOX_25D );
// 	m_RadioGroupViewSelect.AddRadio( m_pID_CHECKBOX_3D );

    m_GroupBroadcast.Clear();
//     m_GroupBroadcast.AddControl(m_pID_PICTURE_TitleLeft);
//     m_GroupBroadcast.AddControl(m_pID_PICTURE_TitleLeftMiddle);
//     m_GroupBroadcast.AddControl(m_pID_PICTURE_serverback);
//     m_GroupBroadcast.AddControl(m_pID_PICTURE_TitleRightMiddle);
//     m_GroupBroadcast.AddControl(m_pID_PICTURE_TitleRight);
    m_GroupBroadcast.AddControl(m_pID_PICTURE_BgBroadcast);

    m_GroupBroadcast.AddControl(m_pID_TEXT_Broadcast);
    m_GroupBroadcast.AddControl(m_pID_BUTTON_Broadcast);
   // m_GroupBroadcast.AddControl(m_pID_PICTURE_BroadcastTitle);
    m_GroupBroadcast.AddControl(m_pID_PICTURE_BroadcastWall);
   // m_GroupBroadcast.AddControl(m_pID_SCROLLBAR_Broadcast);

	//added by zhuomeng.hu		[8/18/2010]
	m_GroupBroadcast.AddControl( m_pID_CHECKBOX_SelectBoard );
	m_GroupBroadcast.AddControl( m_pID_CHECKBOX_SelectService );
	m_GroupBroadcast.AddControl( m_pID_PICTURE_BgAcrivity );
	m_GroupBroadcast.AddControl( m_pID_TEXT_ActivityDesc );
	m_GroupBroadcast.AddControl( m_pID_TEXT_ActivityText );
	m_GroupBroadcast.AddControl( m_pID_LISTIMG_ActivityIcon );
	m_GroupBroadcast.AddControl( m_pID_TEXT_ServiceInfo );
	m_GroupBroadcast.AddControl( m_pID_PICTURE_BroadcastWall );
	m_GroupBroadcast.AddControl( m_pID_PICTURE_BgBlackbar );
	m_GroupBroadcast.AddControl( m_pID_PICTURE_BroadcastWall3 );
	m_GroupBroadcast.AddControl( m_pID_PICTURE_BroadcastWall2 );


	// 公告子组		added by zhuomeng.hu		[8/19/2010]
	m_GroupGongGao.Clear();
	m_GroupGongGao.AddControl( m_pID_TEXT_Broadcast );
	m_GroupGongGao.AddControl( m_pID_TEXT_ActivityText );
	m_GroupGongGao.AddControl( m_pID_TEXT_ActivityDesc );
	m_GroupGongGao.AddControl( m_pID_LISTIMG_ActivityIcon );
	m_GroupGongGao.AddControl( m_pID_PICTURE_BgAcrivity );
	m_GroupGongGao.AddControl( m_pID_PICTURE_BroadcastWall );
	m_GroupGongGao.AddControl( m_pID_PICTURE_BgBlackbar );
	m_GroupGongGao.AddControl( m_pID_PICTURE_BroadcastWall2 );

	// 客服子组		added by zhuomeng.hu		[8/19/2010]
	m_GroupKeFu.Clear();
	m_GroupKeFu.AddControl( m_pID_TEXT_ServiceInfo );
	m_GroupKeFu.AddControl( m_pID_PICTURE_BroadcastWall3 );

	if( m_serverList.GetBigAreaBroadcast(0) )
		*m_pID_TEXT_Broadcast = m_serverList.GetBigAreaBroadcast(0);
    //m_pID_SCROLLBAR_Broadcast->SetStepValue(1);  //设置ScrollBar的步长
    int nMax = 0;
    int nLine = 0;
	if( m_pID_TEXT_Broadcast )
	{
		nMax = m_pID_TEXT_Broadcast->GetMaxLines();
		nLine = m_pID_TEXT_Broadcast->GetShowLine();
	}
    if(nMax > nLine)
        nLine = nMax - nLine;
    else
        nLine = 1;
   // m_pID_SCROLLBAR_Broadcast->SetMaxValue(nLine);

	char szBuffer[MAX_PATH] = {0};
	*m_pID_TEXT_Ver = ApplicationConfig::Instance().GetFullVersion();
	m_pID_TEXT_Ver->SetVisable(true);

	m_pID_FRAME_LOGIN->SetWidth( SCREEN_WIDTH );
	m_pID_FRAME_LOGIN->SetHeight( SCREEN_HEIGHT );

	m_pID_EDIT_ID->SetMaxLength( 16 );
	m_pID_EDIT_PAS->SetMaxLength( 14 );

	// Init
	ReadSettings();

	USE_SCRIPT( eUI_OBJECT_Login, this );

	//
	m_pCamera = MeNew MeCamera;
	D3DXVECTOR3 vFromPt	  = D3DXVECTOR3( 0.0f, 300.0f, 200.0f );
	D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec	  = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	m_pCamera->SetViewParams( vFromPt, vLookatPt, vUpVec );

    m_pID_LIST_ServerName2->SetMsgHoldup(false);	//不接受消息
    m_pID_LIST_ServerName2->HaveSelBar( false );	//没有绿色cur选中地图
    m_pID_LIST_ServerName2->SetCurSelIndex(-1);
    m_pID_LIST_ServerState2->SetMsgHoldup(false);	//不接受消息
    m_pID_LIST_ServerState2->HaveSelBar( false );	//没有绿色cur选中地图
    m_pID_LIST_ServerState2->SetCurSelIndex(-1);

    m_pID_LIST_ServerStateOther->SetMsgHoldup(false);
    m_pID_LIST_ServerStateOther->HaveSelBar(false);
    m_pID_LIST_ServerStateOther->SetCurSelIndex(-1);

	m_pID_LIST_ServerPing2->SetMsgHoldup(false);	//不接受消息
	m_pID_LIST_ServerPing2->HaveSelBar( false );	//没有绿色cur选中地图
	m_pID_LIST_ServerPing2->SetCurSelIndex(-1);

//     m_pID_LIST_AreaName->SetCurSelIndex(-1);
//     m_pID_LIST_ServerName->SetCurSelIndex(-1);
// 
//     m_pID_LIST_ServerState->SetMsgHoldup(false);
//     m_pID_LIST_ServerState->HaveSelBar(false);
//     m_pID_LIST_ServerState->SetCurSelIndex(-1);
// 
//     m_pID_LIST_ServerStateOther2->SetMsgHoldup(false);
//     m_pID_LIST_ServerStateOther2->HaveSelBar(false);
//     m_pID_LIST_ServerStateOther2->SetCurSelIndex(-1);

	// 设置滚动条刷新函数
	m_pID_LIST_ServerList2->GetScrollBar()->SetStepValue(1);

    // 初始化默认的区和服
    ListShowAreaInfo(m_strArea);
    ListShowServerInfo(m_strServer);

	//GMusic.PlayMusic( gCfg.m_szLoginPageMusic, TRUE, TRUE );
//     GMusic.StopMusic();
	GSound.StopSound();
	string strFullPath(CWorld::GetAppDataCharDir());
	strFullPath += '\\';
	strFullPath += theSoundConfig.GetSoundFile( SoundConfig::EST_LoginScene );
	GMusic.PlayMusic( strFullPath.c_str(), TRUE, TRUE );

	SetEnable(true);

    if ( strlen( m_stAccount.szID ) > 0 )
    {
        m_pID_EDIT_ID->SetText( m_stAccount.szID );
        m_pID_CHECKBOX_SAVE->SetCheck( true );
    }
    else
    {
        m_pID_CHECKBOX_SAVE->SetCheck( false );
	}

#ifdef _DEBUG
	// 默认12345为密码
	m_pID_EDIT_PAS->SetText( "12345" );
#endif

	// 公告->活动		added by zhuomeng.hu		[8/23/2010]
	if( LoadActivityConfig( ACTIVITY_PATH ) )
	    SetActivity();
	
	if(m_bShowBroadcast)
	{
		m_GroupBroadcast.SetVisible(true);
		// 客服子组不可见	added by zhuomeng.hu		[8/19/2010]
		m_GroupKeFu.SetVisible( false );
		m_pID_CHECKBOX_SelectBoard->SetCheck( true );
		m_pID_CHECKBOX_SelectService->SetCheck( false );
		//记住账号
		m_pID_CHECKBOX_SAVE->SetVisable(false);
		m_pID_PICTURE_SAVE->SetVisable(false);
	}
	else
	{
		// 返回时跳过服务器选择界面		modified by zhuomeng.hu		[8/20/2010]
		m_GroupBroadcast.SetVisible(false);
		showSelectServerListHideOther(false);
		//if( !m_bGotRegionServerIpPort )
		//{
		//	showSelectServerListHideOther();
		//}
		//else 
		//{
		//	showSelectServerListHideOther(false);
		//}
	}
    m_pCameraModel = NULL;
	m_pLoginModel = NULL;
#ifdef _OLD_LOGIN_
    m_pDoorModel = NULL;
#endif
	m_strPasswordProtect = "";
	m_strGlsid = "";
	m_strPwdResult = "";

	int nViewSet = CUserData::Instance()->GetViewSet();
	m_pID_CHECKBOX_ShortCutKey->SetCheck(CUserData::Instance()->IsSoftKeyboardEnable());
	if( m_pID_CHECKBOX_ShortCutKey->IsChecked() )
	{
		char tip[MAX_PATH] = {0};
		strcpy(tip,theXmlString.GetString(eText_DisableSoftKeyboard));
		//            m_pID_PICTURE_ShortCutKeyTip->setTip(tip);
	}
	else
	{
		char tip[MAX_PATH] = {0};
		strcpy(tip,theXmlString.GetString(eText_EnableSoftKeyboard));
		//            m_pID_PICTURE_ShortCutKeyTip->setTip(tip);
	}

	// 开场动画只在第一次进入游戏时播放(UserData不存在的时候才播放)
	if (!SystemSetting::Instance()->IsUserDataExisted())
	{
		CMovieManager::Instance()->OpenByType(CMovieManager::Type_Login);
		SystemSetting::Instance()->SetUserDataExisted(true);
	}

	s_CUI_ID_FRAME_GameBeforeSetting._LoadUI(); //lyh做游戏前系统设置

	
	return true;
	unguard;
}

 bool CUI_ID_FRAME_LOGIN::ID_BUTTON_GameBeforeSetOnButtonClick( ControlObject* pSender )
 {
	 if (s_CUI_ID_FRAME_GameBeforeSetting._IsVisable())
	 {
		 s_CUI_ID_FRAME_GameBeforeSetting.SetVisable(false);
	 }else
		 s_CUI_ID_FRAME_GameBeforeSetting.SetVisable(true);

	 
	 return true;
 }

void CUI_ID_FRAME_LOGIN::showSelectServerListHideOther( bool show )
{
	bShowSelectServerList = show;	

	if( show )
	{
		//隐藏记住账号的，liaojie
		m_pID_CHECKBOX_SAVE->SetVisable(false);
		m_pID_PICTURE_SAVE->SetVisable(false);
		//m_pID_PICTURE_SAVE->SetVisable(false);
        
		m_pID_EDIT_PAS->SetText("");
		m_GroupLogin.SetVisible(false);
		m_GroupAreaServer.SetVisible(true);
		s_CUI_ID_FRAME_SoftKeyboard.SetVisable(false);
		theUiManager.SetFocus( NULL );

		m_pID_LIST_ZuiJin->Clear();
		m_pID_LIST_ZuiJin->SetCurSelIndex(-1);

		ControlList::S_List stList;
		std::string strCurrentServer("");
		if( !m_strArea.empty() && !m_strServer.empty() )
		{
			strCurrentServer = m_strArea + "     " + m_strServer;
			strncpy(stList.m_szNote, strCurrentServer.c_str(), 31 );
			stList.SetData( strCurrentServer.c_str() );
			m_pID_LIST_ZuiJin->AddItem( &stList ); 			
		}

		ControlList::S_List* pList = m_pID_LIST_ServerList->GetCurSelItem();
		if( pList  )
		{
			std::string szAreaName = pList->m_szNote;
			
			RefreshAreaServerArray(m_nBigAreaIndex, szAreaName);
			if( m_strArea == szAreaName )
				ListShowServerInfo(m_strServer);
			else
				ListShowServerInfo();
		}
		
       // 显示最近选择区和服
       /* m_pID_LIST_AreaName->Clear();
        m_pID_LIST_AreaName->SetCurSelIndex(-1);
        m_pID_LIST_ServerName->Clear();
        m_pID_LIST_ServerName->SetCurSelIndex(-1);

         m_pID_LIST_ServerState->Clear();
        m_pID_LIST_ServerState->SetCurSelIndex(-1);

        m_pID_LIST_ServerStateOther2->Clear();
        m_pID_LIST_ServerStateOther2->SetCurSelIndex(-1);

        ControlList::S_List stList;
        if( !m_strArea.empty() )
        {
            strncpy(stList.m_szNote, m_strArea.c_str(), 31 );
            stList.SetData( m_strArea.c_str() );
            m_pID_LIST_AreaName->AddItem( &stList ); 
			m_pID_TEXT_CurrentServer->SetText( m_strArea.c_str() );			//added by zhuomeng.hu		[8/19/2010]
        }
        if( !m_strServer.empty() )
        {
            strncpy(stList.m_szNote, m_strServer.c_str(), 31 );
            stList.SetData( m_strServer.c_str() );
            m_pID_LIST_ServerName->AddItem( &stList ); 
			m_pID_TEXT_CurrentServer->SetText( m_strServer.c_str() );			//added by zhuomeng.hu		[8/19/2010]
		}

        CServerList::ServerData* pServerData = m_serverList.GetServerData(strBigAreas[m_nBigAreaIndex].c_str(), m_strArea.c_str(),m_strServer.c_str());
        if( pServerData != NULL)
        {
            //设置ServerState状态和ServerStateOther2状态
            strncpy(stList.m_szNote, pServerData->strStatus.c_str(), 31 );
            stList.SetData(pServerData->strStatus.c_str());
            m_pID_LIST_ServerState->AddItem(&stList);

            strncpy(stList.m_szNote, pServerData->strCommon.c_str(), 31 );
            stList.SetData(pServerData->strCommon.c_str());
            m_pID_LIST_ServerStateOther2->AddItem(&stList);

        }*/		
	}
	else
	{
// 		m_RadioGroupViewSelect.ToggleRadio( m_pID_CHECKBOX_3D );
// 		if( nViewSet == 1 )// 3d
// 			m_RadioGroupViewSelect.ToggleRadio( m_pID_CHECKBOX_3D );
// 		else if( nViewSet ==  0 )// 2.5d
// 			m_RadioGroupViewSelect.ToggleRadio( m_pID_CHECKBOX_25D );

		if( strlen(m_pID_EDIT_ID->GetText()) > 0 )
		{
			theUiManager.SetFocus( m_pID_EDIT_PAS );
    	    s_CUI_ID_FRAME_SoftKeyboard.SetVisable(m_pID_CHECKBOX_ShortCutKey->IsChecked());
			setFocusInAccount(false);
			setFocusInPassword(true);
		}
		else
		{
			theUiManager.SetFocus( m_pID_EDIT_ID );
			setFocusInAccount(true);
			setFocusInPassword(false);
		}

		m_pID_BUTTON_OK->SetEnable( true );
		m_pID_BUTTON_Change->SetEnable( true );
        m_GroupAreaServer.SetVisible(false);
        m_GroupLogin.SetVisible(true);
		m_pID_CHECKBOX_SAVE->SetVisable(true);
		m_pID_PICTURE_SAVE->SetVisable(true);

//        m_pID_PICTURE_ShortCutKeyTip->setShowTip(true);

		// 区和服名称添加到窗口名称
		char szWindowName[256] = {0};
		sprintf_s(szWindowName, sizeof(szWindowName)-1, "%s %s", m_strArea.c_str(), m_strServer.c_str());
		theHeroGame.SetWindowText(szWindowName);


	}
	setStartLogin_Time(0);

	// 显示最近选择区和服     added by zhuomeng.hu		[8/19/2010]
	std::string strCurrentServer("");
	if( !m_strArea.empty() && !m_strServer.empty() )
		strCurrentServer = m_strArea + "     " + m_strServer;
	m_pID_TEXT_CurrentServer->SetText( strCurrentServer.c_str() );

	//m_Handle = CreateThread( NULL, 0, CurrentServerPingThreadProc, gCfg.m_szDstIP, 0, NULL );
	
}
// 卸载UI
bool CUI_ID_FRAME_LOGIN::_UnLoadUI()
{
	guardfunc;
	if (NULL == m_pID_FRAME_LOGIN)
	{
		return true;
	}
	m_tmStartLogin = 0;
// 	s_CUI_ID_FRAME_Register.UnLoadUI();

 	s_CUI_ID_FRAME_SoftKeyboard.UnLoadUI();
	s_CUI_ID_FRAME_PasswordProtect.UnLoadUI();
    m_GroupLogin.Clear();
    m_GroupAreaServer.Clear();
    m_GroupBroadcast.Clear();
    m_GroupGongGao.Clear();
    m_GroupKeFu.Clear();

//	m_pID_TEXT_LoginInfo = NULL;
	if( m_pCamera )
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}
	CLOSE_SCRIPT( eUI_OBJECT_Login );
	m_bIsTileLoaded = false;

    // 保存账号，大区，区，服务器
    CUserData::Instance()->SetAccountString(m_stAccount.szID);
	CUserData::Instance()->SetArea(m_strArea.c_str());
	strncpy(m_stAccount.szPwd, "", sizeof(m_stAccount.szPwd)-1);

	std::string serverName = m_strServer;
	size_t pos = m_strServer.find(" ");
	if (pos != std::string::npos)
		serverName = serverName.substr(0, pos);
	CUserData::Instance()->SetServerString(serverName.c_str());

    CUserData::Instance()->WriteLoginData();
    m_pCameraModel = NULL;
	m_pLoginModel = NULL;
#ifdef _OLD_LOGIN_
    m_pDoorModel = NULL;
#endif
	m_pID_FRAME_LOGIN = NULL;
	m_pID_EDIT_PAS = NULL;

	CMovieManager::Instance()->Close();

    return theUiManager.RemoveFrame( "data\\ui\\Login.meui" );

	unguard;
}
// 是否可视
bool CUI_ID_FRAME_LOGIN::_IsVisable()
{
	guardfunc;
	if( !m_pID_FRAME_LOGIN )
		return false;
	return m_pID_FRAME_LOGIN->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_LOGIN::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( !m_pID_FRAME_LOGIN )
		return;
	m_pID_FRAME_LOGIN->SetVisable( bVisable );
    if( bVisable )
	{
        s_CUI_ID_FRAME_SoftKeyboard.SetVisable(m_pID_CHECKBOX_ShortCutKey->IsVisable() && m_pID_CHECKBOX_ShortCutKey->IsChecked());
		s_CUI_ID_FRAME_SelectChannel.SetSelectFlag( false );
		s_CUI_ID_FRAME_SelectChannel.SetLastChannelIndex( -1 );
		s_CUI_ID_FRAME_SelectChannel.ClearData();

		s_CUI_ID_FRAME_GuildGeneralBattleList.ClearData();
	}
    else
        s_CUI_ID_FRAME_SoftKeyboard.SetVisable(false);
	unguard;
}

void CUI_ID_FRAME_LOGIN::SetEnable( bool bEnable )
{
	guardfunc;
	if ( bEnable )
	{
		m_pID_EDIT_PAS->SetReadOnly( false );


		//*m_pID_TEXT_LoginInfo = "";
	}
	else
	{
		m_pID_EDIT_PAS->SetReadOnly( true );
	}
	unguard;
}

void CUI_ID_FRAME_LOGIN::LoadServerList()
{
	guardfunc;
	m_serverList.LoadFromGlobalConfig();
    if( CUserData::Instance()->LoadLoginData() && !m_bGotRegionServerIpPort)
    {
        m_strArea = CUserData::Instance()->GetArea();
        m_strServer = CUserData::Instance()->GetServer();
    }
    if( m_serverList.GetBigAreaList() && m_serverList.GetBigAreaList()->size() )
    {
        m_nBigAreaIndex = m_nBigAreaIndex < m_serverList.GetBigAreaList()->size() ?  m_nBigAreaIndex : 0;	
        RefreshAreaServerArray(m_nBigAreaIndex, m_strArea);
    }
	unguard;
}

bool CUI_ID_FRAME_LOGIN::RefreshAreaServerArray( int nBigArea, std::string strArea )
{
	guardfunc;

	if (nBigArea < 0)
	{
		return false;
	}

	strBigAreas.clear();
	strAreas.clear();
	vctServerInfo.clear();

    // 大区
    if( !m_serverList.GetBigAreaList() || m_serverList.GetBigAreaList()->size() <= 0 )
    {
        OutputDebugString("ServerList 无大区数据");
        assert(false);
        return false;
    }

    std::vector<CServerList::BigAreaData>* pBigAreaList = m_serverList.GetBigAreaList();
    for(int iBigArea=0; iBigArea<pBigAreaList->size(); ++iBigArea)
    {
        strBigAreas.push_back((*pBigAreaList)[iBigArea].strBigArea);
    }

    // 区
    if( strBigAreas.size() == 0 || nBigArea >= strBigAreas.size() )
    {
        OutputDebugString("ServerList 大区个数不正确");
        return false;
    }

    std::vector<CServerList::AreaData>* pAreaList = m_serverList.GetAreaList(strBigAreas[nBigArea].c_str());
    if( pAreaList )
    {
        for( int iArea=0; iArea<pAreaList->size(); ++iArea )
        {
            strAreas.push_back((*pAreaList)[iArea].strArea);
        }
    }
    else
    {
        char msg[MAX_PATH] = {0};
        sprintf(msg, "找不到大区:%s\n", strBigAreas[nBigArea].c_str());
        OutputDebugString(msg);
        return false;
    }

    // 如果strArea不为空，则显示strArea对应服务器列表
    if( strArea.empty() )
    {
        strArea = strAreas[0];
    }
    std::vector<CServerList::ServerData>* pServerList = m_serverList.GetServerList(strBigAreas[nBigArea].c_str(), strArea.c_str());
    // 如果找不到，则去第1个区的服务器
    if( !pServerList )
    {
        strArea = strAreas[0];
        pServerList = m_serverList.GetServerList(strBigAreas[nBigArea].c_str(), strArea.c_str());
    }
    if( pServerList )
    {
        for( int iServer=0; iServer<pServerList->size(); ++iServer )
        {
            ServerInfo_ kServer;
            kServer.strName = (*pServerList)[iServer].strServer;
            kServer.strStatus = (*pServerList)[iServer].strStatus;
            kServer.dwStatusColor = (*pServerList)[iServer].dwStatusColor;
            kServer.strCommon = (*pServerList)[iServer].strCommon;
			kServer.unStatus = (*pServerList)[iServer].unStatus;
			kServer.unIsNew = (*pServerList)[iServer].unIsNew;
			kServer.unIsRecommend = (*pServerList)[iServer].unIsRecommend;
			kServer.unIsVehemence = (*pServerList)[iServer].unIsVehemence;
			kServer.strIpAddr = (*pServerList)[iServer].strIpAddr;
			kServer.nPing = (*pServerList)[iServer].nPing;
            vctServerInfo.push_back(kServer);
        }
    }

	return true;
	unguard;
}

void CUI_ID_FRAME_LOGIN::GetServerInfo( std::string szServerName )
{
	guardfunc;

	m_strServer = szServerName;

	if ( strAreas.size() > 0 && strBigAreas.size() > 0 )
	{
        CServerList::ServerData* pServerData = m_serverList.GetServerData(strBigAreas[m_nBigAreaIndex].c_str(), m_strArea.c_str(), m_strServer.c_str());
        if( pServerData )
        {
		    m_strIp = pServerData->strIpAddr;
		    m_dwPort = pServerData->wPort;
			m_strHttp = pServerData->strHttpAddr;
        }

		if ( m_strIp.size() > 0 )
		{
			strcpy( gCfg.m_szDstIP, m_strIp.c_str() );
			gCfg.m_iServerPort = m_dwPort;
			gCfg.m_strHttp = m_strHttp;
		}
	}

	unguard;
}

bool CUI_ID_FRAME_LOGIN::CheckCurServer()
{
	bool IsFind = false;

	for (int i = 0; i < strBigAreas.size(); i++)
	{
		CServerList::ServerData* pServerData = m_serverList.GetServerData(strBigAreas[i].c_str(), m_strArea.c_str(), m_strServer.c_str());
		if( pServerData )
		{
			IsFind = true;
			break;
		}
	}
	return IsFind;
}

bool CUI_ID_FRAME_LOGIN::CheckIsBad()
{
	bool IsBad = false;

	CServerList::ServerData* pServerData = m_serverList.GetServerData(strBigAreas[m_nBigAreaIndex].c_str(), m_strArea.c_str(), m_strServer.c_str());
	if( pServerData )
	{
		if ( pServerData->unStatus == ES_Bad )
			IsBad = true;
	}

	return IsBad;
}

struct SeverListsort
{
	INT nLvl;
	ControlList :: S_List stList;
};

static bool SeverlistSort(SeverListsort s1, SeverListsort s2)
{
	return (s1.nLvl) < (s2.nLvl);
}

void CUI_ID_FRAME_LOGIN::ListShowServerInfo(std::string szServerName/* = ""*/)
{
	guardfunc;
	if (!s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2)
		return;

    s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->Clear();
    s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerName2->Clear();
    s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerState2->Clear();
    s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerStateOther->Clear();
	s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerPing2->Clear();
	s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->GetScrollBar()->SetValue(0);

	ControlList::S_List stList;
    int nSelectIndex = -1;
    for( int i=0; i< vctServerInfo.size(); i++ )
    {
		strncpy(stList.m_szNote, vctServerInfo[i].strName.c_str(), 31 );
		stList.SetData( "" );
		s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->AddItem( &stList,NULL, false );

		strncpy(stList.m_szNote, vctServerInfo[i].strName.c_str(), 31 );
		stList.SetData( vctServerInfo[i].strName.c_str() );
		stList.setColor( Color_Config.getColor( nNetStatusColor[ vctServerInfo[i].unStatus % ES_Max ] ) );
		s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerName2->AddItem( &stList );


		//strncpy(stList.m_szNote, vctServerInfo[i].strStatus.c_str(), 31 );
		//stList.SetData( vctServerInfo[i].strStatus.c_str() );
		//stList.setColor( vctServerInfo[i].dwStatusColor );
		stList.SetData( chNetStatus[ vctServerInfo[i].unStatus % ES_Max ] );
		s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerState2->AddItem( &stList );

		//strncpy(stList.m_szNote,vctServerInfo[i].strCommon.c_str(),31);
		//stList.SetData(vctServerInfo[i].strCommon.c_str());
		EServer eServer = ESV_Null;
		if ( vctServerInfo[i].unIsNew > 0 )
			eServer = ESV_New;
		else if ( vctServerInfo[i].unIsRecommend > 0 )
			eServer = ESV_Recommend;
		else if ( vctServerInfo[i].unIsVehemence > 0 )
			eServer = ESV_Vehemence;
		stList.SetData( chNetServer[ eServer ] );
		s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerStateOther->AddItem(&stList);

		std::string strState;
		int ncolor = 0;
		if( vctServerInfo[i].nPing > gCfg.m_PingBadMin )
			ncolor = ES_Full;
		else if( vctServerInfo[i].nPing > gCfg.m_PingNormalMin )
			ncolor = ES_Crowded;
		else
			ncolor = ES_Good;
		char buff[24] = {0};
		if ( vctServerInfo[i].nPing < 0 )
			strState = theXmlString.GetString(eText_Server_Unknow);
		else if ( vctServerInfo[i].nPing == 0 )
			strState = theXmlString.GetString(eText_Server_UnderOne);
		else
		{
			sprintf_s(buff, sizeof(buff) - 1, theXmlString.GetString(eText_Server_Ping), vctServerInfo[i].nPing);
			strState = buff;
		}
		stList.SetData( strState.c_str() );
		stList.setColor( Color_Config.getColor( nNetStatusColor[ ncolor % ES_Max ] ) );
		s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerPing2->AddItem(&stList);

        if( !szServerName.empty() && vctServerInfo[i].strName == szServerName )
            nSelectIndex = i;
    }
	if( nSelectIndex < 0 || nSelectIndex >= s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->GetListItemCnt() )
		nSelectIndex = 0;

    s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->SetCurSelIndex(nSelectIndex);
	unguard;
}

void CUI_ID_FRAME_LOGIN::ListShowAreaInfo(std::string szAreaName)
{
     if (!s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList)
         return;
 
     if( strAreas.size() == 0 )
         return;
 
     // 刷新列表
     s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList->Clear();
     ControlList::S_List stList;
     int nSelectIndex = 0;
     for( int i=0; i< strAreas.size(); i++ )
     {
         strncpy(stList.m_szNote, strAreas[i].c_str(), 31 );
         stList.SetData( strAreas[i].c_str() );
		 stList.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
         s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList->AddItem( &stList ); 
         if( !szAreaName.empty() && strAreas[i] == szAreaName )
             nSelectIndex = i;
     }
     m_strLastSelectArea = szAreaName;
     s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList->SetCurSelIndex(nSelectIndex);

	if( strAreas.empty() )
		return;

	if( m_strArea.empty() )
	{
		m_strArea = strAreas[0];
	}
}

int CUI_ID_FRAME_LOGIN::GetBigAreaCount()
{
	guardfunc;
    if( m_serverList.GetBigAreaList() && m_serverList.GetBigAreaList()->size() )
        return m_serverList.GetBigAreaList()->size();
	return 0;
	unguard;
}
void CUI_ID_FRAME_LOGIN::PingServer(const char* szIP, int nPort)
{
	guardfunc;
	m_StartSendTime = clock();

	unguard;

}
void CUI_ID_FRAME_LOGIN::SetLoginWaitText(const char* szText)
{
	guardfunc;
	//if(szText)
//		*m_pID_TEXT_LoginWait = szText;
	unguard;
}
void CUI_ID_FRAME_LOGIN::SetLoginWaitShow(bool bShow)
{
	guardfunc;
// 	if(bShow)
// //		m_pID_TEXT_LoginWait->SetVisable(true);
// 	else
// 		m_pID_TEXT_LoginWait->SetVisable(false);
	unguard;
}
void CUI_ID_FRAME_LOGIN::SetStartWait()
{
	guardfunc;
	m_tmStartWait = clock();
	unguard;
}
bool CUI_ID_FRAME_LOGIN::ReturnLogin( const bool bPressYesButton, void *pData )
{
	guardfunc;
	s_CUI_ID_FRAME_Select.ID_BUTTON_LEAVEOnButtonClick(NULL);
	return true;
	unguard;
}
void CUI_ID_FRAME_LOGIN::Edit_ID_ONLBtnDown( ControlObject* pSender, const char* szData )
{
	guardfunc;
	s_CUI_ID_FRAME_LOGIN.hideSoftKeyboard();
	s_CUI_ID_FRAME_LOGIN.setFocusInPassword(false);
	s_CUI_ID_FRAME_LOGIN.setFocusInAccount(true);
	s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_PAS->setNoPitchOn();
	unguard;
}
void CUI_ID_FRAME_LOGIN::Edit_Pass_OnLBtnUp( ControlObject* pSender, const char* szData )
{
	guardfunc;
	s_CUI_ID_FRAME_LOGIN.setFocusInAccount(false);
	s_CUI_ID_FRAME_LOGIN.setFocusInPassword(true);
	s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_ID->setNoPitchOn();
	s_CUI_ID_FRAME_SoftKeyboard.SetVisable(s_CUI_ID_FRAME_LOGIN.m_pID_CHECKBOX_ShortCutKey->IsChecked());
	unguard;
}
void CUI_ID_FRAME_LOGIN::Eidt_OnDelByte( ControlObject* pSender, int begin, int end )
{
	guardfunc;
	s_CUI_ID_FRAME_LOGIN.updataIndexMap( begin, end, false );
	unguard;
}
void CUI_ID_FRAME_LOGIN::CombBox_ShowList()
{
	guardfunc;
	s_CUI_ID_FRAME_LOGIN.hideSoftKeyboard();
	unguard;
}
bool CUI_ID_FRAME_LOGIN::softKeyboardOnClick( ControlObject* pSender )
{
	guardfunc;
 	s_CUI_ID_FRAME_SoftKeyboard.SetVisable( !s_CUI_ID_FRAME_SoftKeyboard.IsVisable() );
	s_CUI_ID_FRAME_LOGIN.setFocusInAccount(false);
	s_CUI_ID_FRAME_LOGIN.setFocusInPassword(true);
	theUiManager.SetFocus( s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_PAS );
	return true;
	unguard;
}
bool CUI_ID_FRAME_LOGIN::changeServerListOnClick( ControlObject* pSender )
{
	guardfunc;
	s_CUI_ID_FRAME_LOGIN.m_tmStartLogin = 0;

	s_CUI_ID_FRAME_LOGIN.showSelectServerListHideOther();
	return true;
	unguard;
}
bool CUI_ID_FRAME_LOGIN::confirmServerListOnClick( ControlObject* pSender )
{
	guardfunc;

    if(CheckState())
    {
        s_CUI_ID_FRAME_MessageBox.SetButYesCaption(theXmlString.GetString(eText_OperateContinue));
        s_CUI_ID_FRAME_MessageBox.SetButNoCaption(theXmlString.GetString(eText_OperatorReturn));

        s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_ServerStatus)," ",CUI_ID_FRAME_MessageBox::eTypeYesNo,true,ProcessCallback);
        return false;
    }
    ProcessResult();
	s_CUI_ID_FRAME_SoftKeyboard.SetVisable(s_CUI_ID_FRAME_LOGIN.m_pID_CHECKBOX_ShortCutKey->IsChecked());

	return true;
	unguard;
}
void CUI_ID_FRAME_LOGIN::frameOnTab()
{
	guardfunc;
	if( theUiManager.GetFocus() == s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_ID )
	{
		theUiManager.SetFocus( s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_PAS );
        if( s_CUI_ID_FRAME_LOGIN.m_pID_CHECKBOX_ShortCutKey->IsChecked() )
		    s_CUI_ID_FRAME_SoftKeyboard.SetVisable(true);
		s_CUI_ID_FRAME_LOGIN.setFocusInAccount(false);
		s_CUI_ID_FRAME_LOGIN.setFocusInPassword(true);
	}
	else if( theUiManager.GetFocus() == s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_PAS )
	{
		theUiManager.SetFocus( s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_ID );
		s_CUI_ID_FRAME_SoftKeyboard.SetVisable(false);
		s_CUI_ID_FRAME_LOGIN.setFocusInAccount(true);
		s_CUI_ID_FRAME_LOGIN.setFocusInPassword(false);
	}
	unguard;
}
bool CUI_ID_FRAME_LOGIN::frameOnLClick( ControlObject* pSender )
{
	guardfunc;
	return true;
	unguard;
}
void CUI_ID_FRAME_LOGIN::hideSoftKeyboard()
{
	guardfunc;
 	s_CUI_ID_FRAME_SoftKeyboard.SetVisable( false );
	unguard;
}
void CUI_ID_FRAME_LOGIN::setKeyboardCharIndex(int index, bool ch)
{
	guardfunc;
	if( ch )
	{
		IsKeyboardChar |= 1 << index;
	}
	else
	{
		IsKeyboardChar &= 1 << index;
	}
	unguard;
}
void CUI_ID_FRAME_LOGIN::clearKeyboardChar()
{
	guardfunc;
	IsKeyboardChar = 0;
	unguard;
}
void CUI_ID_FRAME_LOGIN::updataIndexMap( int begin, int end, bool ch )
{
	guardfunc;
	if( ch )
	{
		for( int i=begin; i<end; ++i )
		{
			IsKeyboardChar |= 1 << i;
		}
	}
	else
	{
		for( int i=begin; i<end; ++i )
		{
			IsKeyboardChar &= ~( 1 << i );
		}
	}
	unguard;
}

bool CUI_ID_FRAME_LOGIN::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;

	if ( g_GameState != G_LOGIN )
		return false;

// 	if (s_CUI_ID_FRAME_Register.IsVisable())
// 	{
// 		return false;
// 	}
	switch( msg ) 
	{
	case WM_KEYUP:
		{
			if ( !s_CUI_ID_FRAME_MessageBox.IsEnableOnButCancel() )
				break;
            if(s_CUI_ID_FRAME_LOGIN.m_bShowBroadcast)
            {
                if(wParam == VK_RETURN)
                {
                    s_CUI_ID_FRAME_LOGIN.ID_BUTTON_BroadcastOnButtonClick( NULL );
                    return true;
                }
            }
            else if( s_CUI_ID_FRAME_LOGIN.bShowSelectServerList )
			{
				if( wParam == VK_RETURN )
				{
					s_CUI_ID_FRAME_LOGIN.confirmServerListOnClick( NULL );
					return true;
				}

				if( wParam == VK_ESCAPE )
				{
					return true;
				}
			}
			else
			{
				if( wParam == VK_ESCAPE )
				{
					s_CUI_ID_FRAME_LOGIN.changeServerListOnClick( NULL );
					return true;
				}
				if( wParam == VK_RETURN )
				{
					s_CUI_ID_FRAME_LOGIN.ID_BUTTON_OKOnButtonClick( NULL );
				}
			}
		}
		break;
	}

	return false;

	unguard;
}
bool CUI_ID_FRAME_LOGIN::connectFailed(const char bPressYesButton, void *pData)
{
	guardfunc;
 	s_CUI_ID_FRAME_LOGIN.m_bLogining = false;
	s_CUI_ID_FRAME_ExitGame.BackToLogin(0,0);
	return true;
	unguard;
}
bool CUI_ID_FRAME_LOGIN::connectFailed_UserOnline(const char bPressYesButton, void *pData)
{
	guardfunc;
	if (bPressYesButton)
	{
		if( s_CUI_ID_FRAME_LOGIN.GetFrame() )
			s_CUI_ID_FRAME_LOGIN.ID_BUTTON_OKOnButtonClick(NULL,true);
	}
	else
	{
		if( s_CUI_ID_FRAME_LOGIN.GetFrame() )
			s_CUI_ID_FRAME_LOGIN.showSelectServerListHideOther();
		s_CUI_ID_FRAME_LOGIN.m_bLogining = false;
	}
	return true;
	unguard;
}
void CUI_ID_FRAME_LOGIN::setBtnDisable( bool disable )
{
	guardfunc;
	if( disable )
	{
		m_pID_BUTTON_OK->SetEnable( false );
		m_pID_BUTTON_Change->SetEnable( false );
	}
	else
	{
		m_pID_BUTTON_OK->SetEnable( true );
		m_pID_BUTTON_Change->SetEnable( true );
	}
	unguard;
}
void CUI_ID_FRAME_LOGIN::OnTab()
{
	guardfunc;
	if( theUiManager.GetFocus() == s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_ID )
	{
		theUiManager.SetFocus( s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_PAS );
		s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_PAS->SelectAllContext();
		s_CUI_ID_FRAME_SoftKeyboard.SetVisable(s_CUI_ID_FRAME_LOGIN.m_pID_CHECKBOX_ShortCutKey->IsChecked());
		s_CUI_ID_FRAME_LOGIN.setFocusInAccount(false);
		s_CUI_ID_FRAME_LOGIN.setFocusInPassword(true);

	}
	else if( theUiManager.GetFocus() == s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_PAS )
	{
		theUiManager.SetFocus( s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_ID );
		s_CUI_ID_FRAME_LOGIN.m_pID_EDIT_ID->SelectAllContext();
		s_CUI_ID_FRAME_SoftKeyboard.SetVisable(false);
		s_CUI_ID_FRAME_LOGIN.setFocusInAccount(true);
		s_CUI_ID_FRAME_LOGIN.setFocusInPassword(false);
	}
	unguard;
}

void CUI_ID_FRAME_LOGIN::setStartLogin_Time( DWORD t )
{
	m_tmStartLogin = t;
	bRotFreezed = false;
	jumpToNextTime = true;
}
void CUI_ID_FRAME_LOGIN::ID_LIST_ZuiJinOnLDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	s_CUI_ID_FRAME_LOGIN.confirmServerListOnClick(NULL);
}
void CUI_ID_FRAME_LOGIN::ID_LIST_ZuiJinOnLBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ZuiJin->SetCurSelIndex(-1);

	if( s_CUI_ID_FRAME_LOGIN.m_strArea.empty() || s_CUI_ID_FRAME_LOGIN.m_strServer.empty())
		return;

	int nSelectIndex = -1;
	for( int i=0; i< s_CUI_ID_FRAME_LOGIN.strAreas.size(); i++ )
	{
		if( s_CUI_ID_FRAME_LOGIN.strAreas[i] == s_CUI_ID_FRAME_LOGIN.m_strArea )
		{
			nSelectIndex = i;
			break;
		}
	}
	if( nSelectIndex >= 0 )
	{
		s_CUI_ID_FRAME_LOGIN.m_strLastSelectArea = s_CUI_ID_FRAME_LOGIN.m_strArea;
		s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ZuiJin->SetCurSelIndex(nSelectIndex);
		// 刷新服务器列表
		s_CUI_ID_FRAME_LOGIN.RefreshAreaServerArray(s_CUI_ID_FRAME_LOGIN.m_nBigAreaIndex, s_CUI_ID_FRAME_LOGIN.m_strArea);
		s_CUI_ID_FRAME_LOGIN.ListShowServerInfo(s_CUI_ID_FRAME_LOGIN.m_strServer);
	}
}
void CUI_ID_FRAME_LOGIN::ID_LIST_ServerNameOnLBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
//    s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerName->SetCurSelIndex(-1);

    if( s_CUI_ID_FRAME_LOGIN.m_strArea.empty() )
        return;

    int nSelectIndex = -1;
    for( int i=0; i< s_CUI_ID_FRAME_LOGIN.strAreas.size(); i++ )
    {
        if( s_CUI_ID_FRAME_LOGIN.strAreas[i] == s_CUI_ID_FRAME_LOGIN.m_strArea )
        {
            nSelectIndex = i;
            break;
        }
    }
    if( nSelectIndex >= 0 )
    {
        s_CUI_ID_FRAME_LOGIN.m_strLastSelectArea = s_CUI_ID_FRAME_LOGIN.m_strArea;
       // s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList->SetCurSelIndex(nSelectIndex);
        // 刷新服务器列表
        s_CUI_ID_FRAME_LOGIN.RefreshAreaServerArray(s_CUI_ID_FRAME_LOGIN.m_nBigAreaIndex, s_CUI_ID_FRAME_LOGIN.m_strArea);
        s_CUI_ID_FRAME_LOGIN.ListShowServerInfo(s_CUI_ID_FRAME_LOGIN.m_strServer);
    }
}

void CUI_ID_FRAME_LOGIN::ID_LIST_ServerNameOnLDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
    s_CUI_ID_FRAME_LOGIN.confirmServerListOnClick(NULL);
}

void CUI_ID_FRAME_LOGIN::ID_LIST_AreaNameOnLBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
//    s_CUI_ID_FRAME_LOGIN.m_pID_LIST_AreaName->SetCurSelIndex(-1);

    if( s_CUI_ID_FRAME_LOGIN.m_strArea.empty() )
        return;

    int nSelectIndex = -1;
    for( int i=0; i< s_CUI_ID_FRAME_LOGIN.strAreas.size(); i++ )
    {
        if( s_CUI_ID_FRAME_LOGIN.strAreas[i] == s_CUI_ID_FRAME_LOGIN.m_strArea )
        {
            nSelectIndex = i;
            break;
        }
    }
    if( nSelectIndex >= 0 /*&& s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList->GetCurSelIndex() != nSelectIndex*/ )
    {
        s_CUI_ID_FRAME_LOGIN.m_strLastSelectArea = s_CUI_ID_FRAME_LOGIN.m_strArea;
       // s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList->SetCurSelIndex(nSelectIndex);
        // 刷新服务器列表
        s_CUI_ID_FRAME_LOGIN.RefreshAreaServerArray(s_CUI_ID_FRAME_LOGIN.m_nBigAreaIndex, s_CUI_ID_FRAME_LOGIN.m_strArea);
        s_CUI_ID_FRAME_LOGIN.ListShowServerInfo(s_CUI_ID_FRAME_LOGIN.m_strServer);
    }
}

HWND g_RegisterHwnd = NULL;
LRESULT CALLBACK RegisterWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
	case WM_CREATE:
		{
			long lstyle = GetWindowLong(hWnd,GWL_STYLE);
			lstyle = WS_OVERLAPPED;
			SetWindowLong(hWnd,GWL_STYLE,lstyle);
			// Embed the browser object into our host window. We need do this only
			// once. Note that the browser object will start calling some of our
			// IOleInPlaceFrame and IOleClientSite functions as soon as we start
			// calling browser object functions in EmbedBrowserObject().
			if ( EmbedBrowserObject( hWnd ) ) return -1;

			return 0; // Success
		}
	case WM_MOUSEACTIVATE:
		{
			POINT ptCursor;
			GetCursorPos( &ptCursor );
			RECT rect ;
			GetWindowRect(hWnd,&rect);
			if (ptCursor.x < rect.right - 12
				&& ptCursor.x > rect.right - 32
				&& ptCursor.y > rect.top + 9
				&& ptCursor.y < rect.top + 29)
			{
				DestroyWindow(hWnd);
				BringWindowToTop(g_hWnd);
				g_RegisterHwnd = NULL;
			}
			return 0;
		}
		break;
	case WM_DESTROY:
		{
			// Detach the browser object from this window, and free resources.
			UnEmbedBrowserObject( hWnd );
			g_RegisterHwnd = NULL;
			return 0;
		}
	case WM_KEYUP:
		{
			switch( wParam )
			{
			case VK_ESCAPE:
				DestroyWindow(g_RegisterHwnd);
				BringWindowToTop(g_hWnd);
				g_RegisterHwnd = NULL;
				break;
			}
			return 0;
		}
	}

	return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
}

bool CUI_ID_FRAME_LOGIN::ID_BUTTON_RegisterOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_LOGIN )
		return false;
	ShellExecute( NULL, "open", "http://user.chcgame.com/usercenter/Normal", NULL, NULL, 0 );
// 	if( !g_RegisterHwnd )
// 	{
// 		int nWidth = 367;
// 		int nHeight = 332;
// 		RECT wrect;
// 		GetWindowRect( g_hWnd, &wrect );
// 
// 		RECT rect;
// 		SetRect( &rect, (wrect.left + wrect.right - nWidth)/2 , (wrect.top + wrect.bottom - nHeight)/2, nWidth, nHeight );
// 
// 		DWORD dwExWindowStyle = 0;
// 		DWORD dwWindowStyle = WS_OVERLAPPED| WS_POPUP;
// 		WNDCLASS wndClass = { CS_PARENTDC, RegisterWndProc, 0, 0, NULL,
// 			NULL,
// 			LoadCursor( NULL, IDC_ARROW ),
// 			(HBRUSH)GetStockObject(WHITE_BRUSH),
// 			NULL, _T("Register Window") };
// 		RegisterClass( &wndClass );
// 		g_RegisterHwnd = CreateWindowEx(dwExWindowStyle, _T("Register Window"), _T("Register"), dwWindowStyle,
// 			rect.left, rect.top,
// 			nWidth, nHeight, 
// 			g_hWnd,
// 			NULL,
// 			NULL, 0L );
// 	}
// 
// 	if (g_RegisterHwnd)
// 	{
// 		DisplayHTMLPage(g_RegisterHwnd, "http://ws.tolez.com/client/wsreg.html");
// 		ShowWindow( g_RegisterHwnd, SW_SHOW );
// 	}
	return true;
}

void CUI_ID_FRAME_LOGIN::SetRegionServerIPPort(const char* szRegion, const char* szServer, const char* szIP, const char* szPort)
{
	if( !szRegion || szRegion[0] == '\0' )
		return;
	if( !szServer || szServer[0] == '\0' )
		return;
	if( !szIP || szIP[0] == '\0' )
		return;
	if( !szPort || szPort[0] == '\0' )
		return;

	m_strArea = szRegion;
	m_strServer = szServer;
	m_strIp = szIP;
	m_dwPort = atoi(szPort);
	if ( m_strIp.size() > 0 && m_dwPort > 0 )
	{
		strcpy( gCfg.m_szDstIP, m_strIp.c_str() );
		gCfg.m_iServerPort = m_dwPort;
		m_bGotRegionServerIpPort = true;
	}
}

bool CUI_ID_FRAME_LOGIN::CheckState()
{
    if(!s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2)
        return false;

    int nSelectIndex = s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->GetCurSelIndex();
    if( nSelectIndex == -1 )
    {
        s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SelectServer),"");
        return false;
    }

#ifdef _DEBUG
    const char* pszWOrd = s_CUI_ID_FRAME_LOGIN.vctServerInfo[nSelectIndex].strStatus.c_str();
#endif

    if(strcmp(s_CUI_ID_FRAME_LOGIN.vctServerInfo[nSelectIndex].strStatus.c_str(),theXmlString.GetString(eText_SuperAll)) != 0)
        return false;

    return true;
}

bool CUI_ID_FRAME_LOGIN::ProcessResult()
{
    s_CUI_ID_FRAME_LOGIN.jumpToNextTime = true;
    if( s_CUI_ID_FRAME_LOGIN.bShowSelectServerList )
    {
        int nselectIndex = s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->GetCurSelIndex();
        if( nselectIndex == -1 )
        {
            s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eText_SelectServer),
                "" );
            return false;
        }
    }
    GettheNetworkInput().Close();
    s_CUI_ID_FRAME_LOGIN.connectLoginServer( NULL, s_CUI_ID_FRAME_LOGIN.m_pID_LIST_ServerList2->GetCurSelItem() );
    s_CUI_ID_FRAME_LOGIN.showSelectServerListHideOther(false);

    return true;
}

void CUI_ID_FRAME_LOGIN::FinishEnterPwdProtect( const std::string strPwdProResult )
{
	if( strPwdProResult.length() <= 0 )
		return;

	if( !IsVisable() )
		return;

	memcpy(&m_stAccountPwdProtect.stAccountInfo, &m_stAccount, sizeof(SAccountInfo));
	m_stAccountPwdProtect.strGlsid = m_strGlsid;
	m_stAccountPwdProtect.strPwrProtectResult = strPwdProResult;

	if (m_Handle)
	{
		TerminateThread( m_Handle, 0 );
		CloseHandle( m_Handle );
		m_Handle = NULL;
	}
    //lyh 取消掉倒计时的取消button
	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eLogin_ValidateUser), "", CUI_ID_FRAME_MessageBox::eTypeNothing, true/*, CancelLogin*/);
	s_CUI_ID_FRAME_MessageBox.SetAutoClose(20, false);
	s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(false);

	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "");
	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Start connect GLS Pwd Protect...");

// 	s_CUI_ID_FRAME_LOGIN.m_dwLoginStartTime = HQ_TimeGetTime();
	CUI_ID_FRAME_LOGIN::m_bShowQueue = true;//false;

	m_bLogining = true;

	s_CUI_ID_FRAME_LOGIN.m_Handle = CreateThread( NULL, 0, ConnectPwdProtectThreadProc, &m_stAccountPwdProtect, 0, NULL );
}

// 在线程里调用
bool GetGlsid( const char* szAccount, std::string& glsid )
{
	if( !szAccount || szAccount[0] == '\0' )
		return false;

	using namespace XmlRpc;

	try
	{
		//XmlRpcValue args;
		//XmlRpcClient c(gCfg.m_szDstIP, gCfg.m_iServerPort, "/gls");

		////
		//// execute get_glsid_version
		////
		//args[0] = szAccount;									// user name
		//args[1] = "";												// mac
		//args[2] = ApplicationConfig::Instance().GetFullVersion();	// version
		//XmlRpcValue result;

		//LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Execute (get_glsid_version) \t[%s:%d] ...", gCfg.m_szDstIP, gCfg.m_iServerPort);

		//if (!c.execute("get_glsid_version", args, result))
		//{
		//	c.close();
		//	InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), 1);
		//	return false;
		//}
		//c.close();

		//if (result.hasMember("faultCode"))
		//{
		//	int err = result["faultCode"];
		//	InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), err);

		//	return false;
		//}

		//glsid = result["glsid"];
	}
	catch (const XmlRpcException& e)
	{
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, "GLS Login Exception (%s)", e.getMessage().c_str());
	}
	return true;
}
// 在登录线程里调用
bool GetPwdMd5( const char* szPwd, const std::string& glsid, std::string& md5Result, std::stringstream& sstrMd5 )
{
	if( !szPwd || szPwd[0] == '\0' )
		return false;

	using namespace XmlRpc;

	try
	{
		// password
		std::string password(szPwd);

		// sha1( password )
		MD5 md5pass( password.c_str() );

// 		std::ios::fmtflags flags = sstrMd5.setf(std::ios::hex, std::ios::basefield);
// 
// 		for (int i = 0; i < 5; ++i)
// 		{
// 			sstrMd5.width(8);
// 			sstrMd5.fill('0');
// 			sstrMd5. md5pass.digest[i];
// 		}
// 
// 		sstrMd5.setf(flags);

		sstrMd5<<md5pass.toString();

		// md5( glsid + md5( password ) )
		std::stringstream sstr;
		sstr << glsid;
		sstr << md5pass.toString();

		MD5 md5(sstr.str());
		md5Result = md5.toString();
	}
	catch (const XmlRpcException& e)
	{
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, "GLS Login Exception (%s)", e.getMessage().c_str());
	}

	return true;
}
// 在登录线程里调用
bool GetPwdSha1( const char* szPwd, const std::string& glsid, std::string& md5Result, std::stringstream& sstrSha1 )
{
	if( !szPwd || szPwd[0] == '\0' )
		return false;

	using namespace XmlRpc;

	try
	{
		// password
		std::string password(szPwd);

		// sha1( password )
		SHA1 sha1;
		sha1.Reset();
		sha1 << password.c_str();

		unsigned digest[5];
		if (!sha1.Result(digest))
		{
			InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), 1);
			return false;
		}

		std::ios::fmtflags flags = sstrSha1.setf(std::ios::hex, std::ios::basefield);

		for (int i = 0; i < 5; ++i)
		{
			sstrSha1.width(8);
			sstrSha1.fill('0');
			sstrSha1 << digest[i];
		}

		sstrSha1.setf(flags);

		// md5( glsid + sha1( password ) )
		std::stringstream sstr;
		sstr << glsid;
		sstr << sstrSha1.str();

		MD5 md5(sstr.str());
		md5Result = md5.toString();
	}
	catch (const XmlRpcException& e)
	{
		LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, "GLS Login Exception (%s)", e.getMessage().c_str());
	}

	return true;
}

bool QueryUserStatus(const std::string& glsid, int guid, const std::stringstream& sstrSha1)
{
	MD5 md5Key(sstrSha1.str());
	CUI_ID_FRAME_LOGIN::g_gateIp = "127.0.0.1";//ip;
	CUI_ID_FRAME_LOGIN::g_gatePort = 21080;//port;
	CUI_ID_FRAME_LOGIN::g_dwSwitchGateTime = HQ_TimeGetTime() + CUI_ID_FRAME_LOGIN::g_dwSwitchGatePeriod;

	//MD5 md5Key(key + sstrSha1.str());

	theHeroGame.GetPlayerMgr()->m_dwAccountID = 123;
	theHeroGame.GetPlayerMgr()->m_strSessionKey = md5Key.toString();

	// 连接游戏服务器...
	InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), -3);
	InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_bSwitchGate), 1);

	//using namespace XmlRpc;

	//try
	//{
	//	XmlRpcValue args;
	//	XmlRpcClient c(gCfg.m_szDstIP, gCfg.m_iServerPort, "/gls");
	//	XmlRpcValue result;
	//	//
	//	// execute query_user_status
	//	// 
	//	args.clear();
	//	result.clear();

	//	args[0] = guid;
	//	args[1] = glsid;

	//	s_glsUserData[0] = guid;
	//	s_glsUserData[1] = glsid;

	//	DWORD dwTime = 3000;
	//	Sleep(3000); // Sleep 3s, 否则每个玩家都会提示有1个人排队后再进入游戏, 其实这1个人是玩家自己

	//	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Execute (query_user_status) ..." );
	//	
	//	/*
	//	status返回值解释:
	//		0  帐号通过身份验证，排队中
	//		1  等待游戏服务器认领帐号
	//		2  游戏服务器正在为帐号分配资源
	//		3  资源分配完毕
	//		4  玩家进入游戏
	//	*/

	//	while (1)
	//	{
	//		result.clear();

	//		if (!c.execute("query_user_status", args, result))
	//		{
	//		    c.close();
	//			InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), 1);
	//			return false;
	//		}

	//		if (result.hasMember("faultCode"))
	//		{
	//			int err = result["faultCode"];
	//			InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), err);

	//			return false;
	//		}

	//		int status = result["status"];
	//		if (status == 3)						//资源分配完毕
	//		{
	//			std::string msg = result["msg"];
	//			std::string key;
	//			std::string ip;
	//			int port;

	//			size_t p = msg.find(',') + 1;
	//			size_t p2 = msg.find(',', p);

	//			key = msg.substr(0, p - 1);
	//			ip = msg.substr(p, p2 - p);
	//			port = atoi(msg.substr(p2 + 1).c_str());

	//			CUI_ID_FRAME_LOGIN::g_gateIp = "192.168.1.122";//ip;
	//			CUI_ID_FRAME_LOGIN::g_gatePort = 21080;//port;
	//			CUI_ID_FRAME_LOGIN::g_dwSwitchGateTime = HQ_TimeGetTime() + CUI_ID_FRAME_LOGIN::g_dwSwitchGatePeriod;

	//			MD5 md5Key(key + sstrSha1.str());

	//			theHeroGame.GetPlayerMgr()->m_dwAccountID = guid;
	//			theHeroGame.GetPlayerMgr()->m_strSessionKey = md5Key.toString();

	//			// 连接游戏服务器...
	//			InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), -3);
	//			InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_bSwitchGate), 1);

	//			break;
	//		}
	//		else if (status == 2 || status == 1)	//2 游戏服务器正在为帐号分配资源; 1 等待游戏服务器认领帐号
	//		{
	//			InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), -2); // 正在处理中...
	//		}
	//		else if (status == 0)					//帐号通过身份验证，排队中
	//		{
	//			std::string msg = result["msg"];
	//			int number = atoi(msg.c_str());
	//			CUI_ID_FRAME_LOGIN::g_nQueueNumber = number;
	//			if (CUI_ID_FRAME_LOGIN::g_nQueueNumber == 0)
	//				CUI_ID_FRAME_LOGIN::g_nQueueNumber = 1;
	//			InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), 1000); // 排队中...
	//			Sleep(1000);
	//			continue;
	//		}

	//		Sleep(dwTime);
	//	}

	//	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Execute (query_lastlogin_ip_time) ..." );
	//	if (!c.execute("query_lastlogin_ip_time", args, result))
	//	{
	//		c.close();
	//		InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), 1);
	//		return false;
	//	}

	//	c.close();

	//	if (result.hasMember("ip_time"))
	//	{
	//		std::string ip_time = result["ip_time"];

	//		size_t p = ip_time.find(',') + 1;

	//		char ip[128];
	//		MeSprintf_s(ip, sizeof(ip)/sizeof(char) - 1, theXmlString.GetString(eText_LastIp), ip_time.substr(0, p - 1).c_str());
	//		s_CUI_ID_FRAME_Select.SetLastIp(ip);

	//		time_t ltime = atol(ip_time.substr(p).c_str());
	//		struct tm tmtime;
	//		localtime_s(&tmtime, &ltime);

	//		//	增加了周几		added by zhuomeng.hu		[8/23/2010]
	//		char weekday[STR_MAXLEN];
	//		switch( tmtime.tm_wday )
	//		{
	//		case 0:
	//			MeSprintf_s( weekday, STR_MAXLEN - 1, "%s", "星期日" );
	//			break;
	//		case 1:
	//			MeSprintf_s( weekday, STR_MAXLEN - 1, "%s", "星期一" );
	//			break;
	//		case 2:
	//			MeSprintf_s( weekday, STR_MAXLEN - 1, "%s", "星期二" );
	//			break;
	//		case 3:
	//			MeSprintf_s( weekday, STR_MAXLEN - 1, "%s", "星期三" );
	//			break;
	//		case 4:
	//			MeSprintf_s( weekday, STR_MAXLEN - 1, "%s", "星期四" );
	//			break;
	//		case 5:
	//			MeSprintf_s( weekday, STR_MAXLEN - 1, "%s", "星期五" );
	//			break;
	//		case 6:
	//			MeSprintf_s( weekday, STR_MAXLEN - 1, "%s", "星期六" );
	//			break;
	//		default:
	//			MeSprintf_s( weekday, STR_MAXLEN - 1, "%s", "" );
	//			break;
	//		}
	//		char buf[128];
	//		MeSprintf_s(buf, sizeof(buf)/sizeof(char) - 1, "%d-%d-%d    %s    %d:%02d:%02d",
	//			tmtime.tm_year + 1900, tmtime.tm_mon + 1, tmtime.tm_mday, weekday,
	//			tmtime.tm_hour, tmtime.tm_min, tmtime.tm_sec);
	//		char lastTime[128];
	//		MeSprintf_s(lastTime, sizeof(lastTime)/sizeof(char) - 1, theXmlString.GetString(eText_LastTime), buf);
	//		s_CUI_ID_FRAME_Select.SetLastTime(lastTime);

	//		s_CUI_ID_FRAME_Select.SetLastAddress("");

	//		InterlockedExchange((LONG*)(&CUI_ID_FRAME_Select::m_time), ltime);
	//	}
	//}
	//catch (const XmlRpcException& e)
	//{
	//	LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, "GLS Login Exception (%s)", e.getMessage().c_str());
	//}

	return true;
}

bool ProcessCallback( const char bPressYesButton, void *pData )
{
    guardfunc;
    if( bPressYesButton )
    {
        s_CUI_ID_FRAME_LOGIN.ProcessResult();
    }
    s_CUI_ID_FRAME_MessageBox.SetButYesCaption(theXmlString.GetString(eText_Yes));
    s_CUI_ID_FRAME_MessageBox.SetButNoCaption(theXmlString.GetString(eText_No));
    return true;
    unguard;
}



bool CUI_ID_FRAME_LOGIN::CancelLoginQueue( const char bPressYesButton, void *pData )
{
	if (!bPressYesButton)
	{
		// 取消排队
		//using namespace XmlRpc;

		//try
		//{
		//	/*XmlRpcValue args;
		//	XmlRpcClient c(gCfg.m_szDstIP, gCfg.m_iServerPort, "/gls");
		//	XmlRpcValue result;*/
		//	//
		//	// execute cancel_queue
		//	// 
		//	DWORD dwTime = 1000;
		//	//Sleep(1000); // Sleep 1s 保证cancel_queue第一次能拿到返回值

		//	LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Execute (query_user_status) ..." );

		//	while (1)
		//	{
		//		result.clear();

		//		if (!c.execute("cancel_queue", s_glsUserData, result))
		//		{
		//	        c.close();
		//			InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), 1);
		//			return false;
		//		}

		//		if (result.hasMember("faultCode"))
		//		{
		//			int err = result["faultCode"];
		//			InterlockedExchange((LONG*)(&CUI_ID_FRAME_LOGIN::g_nError), err);

		//			return false;
		//		}

		//		int status = result["status"];
		//		if (status == 1)
		//		{
		//			// 成功
		//			break;
		//		}
		//		else if(status == 0)
		//		{
		//			// 失败，继续通过线程从gls获取状态
		//			return false;
		//		}
		//		Sleep(dwTime);
		//	}

		//	c.close();
		//}
		//catch (const XmlRpcException& e)
		//{
		//	LOG_MESSAGE( ERROR_INFO_LOG, LOG_PRIORITY_ERROR, "GLS Login Exception (%s)", e.getMessage().c_str());
		//}

		s_CUI_ID_FRAME_LOGIN.m_bLogining = false;

		// 结束登录线程
		if (s_CUI_ID_FRAME_LOGIN.m_Handle)
		{
			TerminateThread( s_CUI_ID_FRAME_LOGIN.m_Handle, 0 );
			CloseHandle( s_CUI_ID_FRAME_LOGIN.m_Handle );
			s_CUI_ID_FRAME_LOGIN.m_Handle = NULL;
		}

		{
			/*XmlRpc::XmlRpcClient c(gCfg.m_szDstIP, gCfg.m_iServerPort, "/");
			XmlRpc::XmlRpcValue result;
			c.execute("cancel", s_glsUserData, result);
			c.close();*/
		}

		if( s_CUI_ID_FRAME_Select.GetFrame() )
			s_CUI_ID_FRAME_Select.ID_BUTTON_LEAVEOnButtonClick(0);
		if( s_CUI_ID_FRAME_LOGIN.GetFrame() )
			s_CUI_ID_FRAME_LOGIN.showSelectServerListHideOther();
	}
	return true;
}

//	added by zhuomeng.hu		[8/23/2010]
bool CUI_ID_FRAME_LOGIN::LoadActivityConfig( const char *path )
{
	guardfunc;
	if ( !m_pID_FRAME_LOGIN )
	{
		assert( false && "ui error" );
		return false;
	}

    if( !m_activityContentVec.empty() )
        return false;

	m_activityTypeVec.clear();
	m_activityContentVec.clear();

	if ( path == NULL || *path == 0 )
	{
		assert( false && "Load EventConfig Error" );
		return false;
	}

	MeXmlDocument xMeXml;
	if ( !xMeXml.LoadFile( path, 1 ) )
	{	
		assert( false && "Load EventConfig Error" );
		return false;
	}

	MeXmlElement* pRoot = xMeXml.FirstChildElement( "Project" );
	if ( NULL == pRoot )
	{
		assert( false && "Attribute Error" );
		return false;
	}

	//`	读取活动日程安排
	MeXmlElement* pPeriodTypes = pRoot->FirstChildElement( "PeriodTypes" );
	if ( NULL == pPeriodTypes )
	{
		assert( false && "Attribute Error" );
		return false;
	}
	else
	{
		MeXmlElement* pType = pPeriodTypes->FirstChildElement("Type");
		while( NULL != pType )
		{
			EventPeriodType type;
			if ( pType->Attribute( "Id", &type.id ) == NULL )
				return false;
			const char* pDescription = pType->Attribute( "Description" );
			if (NULL != pDescription)
				type.description = _tstring::toNarrowString( _tstring::UTF8towcs( pDescription ).c_str() );

			m_activityTypeVec.push_back( type );
			pType = pType->NextSiblingElement();
		}
	}

	MeXmlElement* pEvents = pRoot->FirstChildElement( "Events" );
	if ( NULL == pEvents )
	{
		assert( false && "Attribute Error" );
		return false;
	}

	//	获取时间
	time_t t = time( NULL );
	tm* pTime = localtime( &t );
	//tm_year 年  tm_mon 月  tm_mday 日   tm_wday 周几
	//int weekday = HelperFunc::Ymd2Wday( year, month, day );	//根据时间算出是周几
 

	//	读取当天活动
	MeXmlElement* pEvent = pEvents->FirstChildElement( "Event" );
	while ( pEvent != NULL )
	{
		Event evt;

		//	活动名
		const char* name = pEvent->Attribute( "Name" );
		if ( NULL == name )
			return false;
		evt.name = _tstring::toNarrowString( _tstring::UTF8towcs( name ).c_str() );

		//	周几
		int tmpPeriodTypeId;
		if ( NULL == pEvent->Attribute( "PeriodTypeId", &tmpPeriodTypeId ) )
			return false;
		evt.periodTypeId = tmpPeriodTypeId;
		
		ItrPeriodTypeContainer _iter = find( m_activityTypeVec.begin(), m_activityTypeVec.end(), evt.periodTypeId );
		if ( _iter == m_activityTypeVec.end() )
		{
			return false;
		}
		evt.period = _iter->description; // 每日/周几
		
		if ( NULL == pEvent->Attribute( "Quality", &evt.quality ) )
			return false;

		//	起始NPC
		if ( NULL == pEvent->Attribute( "NpcId", &evt.npcId ) )
			return false;
		
		const char* NpcName = pEvent->Attribute( "NpcName" );
		if ( NULL == NpcName )
			evt.npc = "";
		else
			evt.npc = _tstring::toNarrowString( _tstring::UTF8towcs( NpcName ).c_str() );

		//	描述
		const char* var = pEvent->Attribute( "Description" );
		if ( NULL != var )
			evt.description = _tstring::toNarrowString( _tstring::UTF8towcs( var ).c_str() );

		// EventItemID 对应 Item 表
		int tmpEventItemId;
		if ( NULL == pEvent->Attribute( "EventItemId", &tmpEventItemId ) )
			return false;
		evt.eventItemId = unsigned short( tmpEventItemId );

		//	起始时间
		if ( pEvent->Attribute( "Year", &evt.year ) == NULL )
			return false;

		if ( pEvent->Attribute( "Month", &evt.month ) == NULL )
			return false;

		if ( evt.month > 11 || evt.month < -1 )
			evt.month = -1;

		if ( pEvent->Attribute( "Day", &evt.day ) == NULL)
			return false;

		if ( pEvent->Attribute( "Hour", &evt.hour ) == NULL )
			return false;

		if ( pEvent->Attribute( "Minute", &evt.minute ) == NULL)
			return false;

		//	持续时间
		if ( pEvent->Attribute( "Duration", &evt.duration ) == NULL)
			return false;

		//	时间描述  "全天"
		const char* durationDesVar = pEvent->Attribute( "DurationDescription" );
		if ( NULL != durationDesVar )
			evt.durationDescription = _tstring::toNarrowString( _tstring::UTF8towcs( durationDesVar ).c_str() );

		//	结束时间
		evt.endMinute = evt.minute + evt.duration;
		evt.endHour = evt.hour;
		if( evt.endMinute >= 60 )
		{
			evt.endHour += evt.endMinute / 60;
			evt.endMinute %= 60;
			if( evt.endHour > 24 )
				evt.endHour %= 24;
		}
		
		//	将活动信息整合到 describe 中
		std::string strActivityDes;

		strActivityDes = "活动名:" + evt.name + "\n";

		if( evt.durationDescription == "全天" )
		{
			strActivityDes += "活动时间: 全天\n";
		}
		else
		{
			char strTmp[STR_MAXLEN] = "";
			MeSprintf_s( strTmp, STR_MAXLEN - 1, "%d", evt.hour );
			strActivityDes += "活动时间:" + std::string( strTmp ) + ":";
			MeSprintf_s( strTmp, STR_MAXLEN - 1, "%d", evt.minute );
			if( strcmp( strTmp, "0" ) == 0 )
				strActivityDes += "00 - ";
			else
				strActivityDes += std::string( strTmp ) + " - ";
			MeSprintf_s( strTmp, STR_MAXLEN - 1, "%d", evt.endHour );
			strActivityDes += std::string( strTmp ) + " : ";
			MeSprintf_s( strTmp, STR_MAXLEN - 1, "%d", evt.endMinute );
			if( strcmp( strTmp, "0" ) == 0 )
				strActivityDes += "00\n";
			else
				strActivityDes += std::string( strTmp ) + "\n";
		}

        if( !evt.npc.empty() )
		    strActivityDes += "起始 npc:" + evt.npc + "\n";

		strActivityDes += "描述:\n" + evt.description;
		evt.description = strActivityDes;


		//	以下属性对于公告界面的活动显示无用， 故不再读取
		evt.periodParameter = -1;
		evt.isEveryday = -1;
		evt.week = -1;
		evt.needLevel = -1;
		evt.count = -1;
		evt.isHot = -1;
		evt.isPivot = -1;
		evt.scriptId = -1;
		evt.mapId = -1;
		evt.mapName = "";
		evt.mapPosX = 0.0f;
		evt.mapPosY = 0.0f;
		evt.completeTimeVarIndex = -1;
		evt.endWeek = -1;

		//	符合当日显示条件，则加入到表中
		if( evt.periodTypeId == 0 )
		{
			if( pTime->tm_year == evt.year && pTime->tm_mon == evt.month && pTime->tm_mday == evt.day )
				m_activityContentVec.push_back( evt );		//节日	年 tm_year + 1900		月 tm_mon + 1
		}
		else if( evt.periodTypeId > 0 && evt.periodTypeId < 4 )
		{
			m_activityContentVec.push_back( evt );			//日常
		}
		else if( evt.periodTypeId > 9 && evt.periodTypeId < 17 )
		{
			if( pTime->tm_wday == evt.periodTypeId - 10 )
				m_activityContentVec.push_back( evt );		//周常
		}

		pEvent = pEvent->NextSiblingElement( "Event" );
	}

	//	按 Quality 大->小 排序
	EventContents::size_type i,j;
	Event tmpEvt;
	for( i = 0; i < m_activityContentVec.size() - 1; i++ )
	{
		for( j = i + 1; j < m_activityContentVec.size(); j++ )
		{
			if( m_activityContentVec[i].quality <  m_activityContentVec[j].quality )
			{
				tmpEvt = m_activityContentVec[i];
				m_activityContentVec[i] = m_activityContentVec[j];
				m_activityContentVec[j] = tmpEvt;
			}
		}
	}

	return true;
	unguard;
}

// 设置活动信息		added by zhuomeng.hu		[8/23/2010]
void CUI_ID_FRAME_LOGIN::SetActivity()
{
	guardfunc;
	m_pID_LISTIMG_ActivityIcon->Clear();

	EventContents::size_type i;
	for( i = 0; i < m_activityContentVec.size(); i++ )
	{
		ControlIconDrag::S_ListImg stListItem;
		stListItem.SetData( m_activityContentVec[i].eventItemId, 1, eIcon_Enable, false, eTipFlag_Event );
		m_pID_LISTIMG_ActivityIcon->SetItem( &stListItem, i );
	}
	m_pID_LISTIMG_ActivityIcon->SetHeightMaxCnt(m_activityContentVec.size()/m_pID_LISTIMG_ActivityIcon->GetRowItemCnt() + 1);
	if( !m_activityContentVec.empty() )
    {
        // 默认选中第一个
        ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_ActivityIcon->GetItem( 0, 0 );
        if( pItem && pItem->m_pkIconInfo )
        {
            pItem->m_pkIconInfo->SetColorFrameType( eColorFrame_Select );
            m_pSelectItem = pItem;
        }
		m_pID_TEXT_ActivityDesc->SetText( m_activityContentVec[0].description.c_str() );
    }
	unguard;
}
bool CUI_ID_FRAME_LOGIN::EncodeAccountInfo(SAccountInfo* pAccountInfo)
{
	if (!pAccountInfo)
	{
		return false;
	}

	std::string szMac = "None";
	BOOL bResult = GetMacByGetAdaptersAddresses(szMac,true);
	if(!bResult)
		return false;

	memset(pAccountInfo->szCryptID,0,sizeof(pAccountInfo->szCryptID));
	memset(pAccountInfo->szCryptPWD,0,sizeof(pAccountInfo->szCryptPWD));
	memset(pAccountInfo->szCryptMac,0,sizeof(pAccountInfo->szCryptMac));
	

	/*return true;*/
	if (!theSimpleCtyp.Encode(pAccountInfo->szID,16/*strlen(pAccountInfo->szID)*/,pAccountInfo->szCryptID)
		||!theSimpleCtyp.Encode(pAccountInfo->szPwd,16/*strlen(pAccountInfo->szPwd)*/,pAccountInfo->szCryptPWD)
		||!theSimpleCtyp.Encode(szMac.c_str(),szMac.size()/*strlen(pAccountInfo->szPwd)*/,pAccountInfo->szCryptMac) )
	{
		return false;
	}
	return true;
}

//bool CUI_ID_FRAME_LOGIN::DecodeAccountInfo(SAccountInfo* pAccountInfo)
//{
//	if (!pAccountInfo)
//	{
//		return false;
//	}
//
//	char szID1[128];
//	char szPwd1[128];
//	if (!theSimpleCtyp.Decode(pAccountInfo->szCryptID,strlen(pAccountInfo->szCryptID),szID1)
//		||!theSimpleCtyp.Decode(pAccountInfo->szCryptPWD,strlen(pAccountInfo->szCryptPWD),szPwd1))
//	{
//		return false;
//	}
//	return true;
//}