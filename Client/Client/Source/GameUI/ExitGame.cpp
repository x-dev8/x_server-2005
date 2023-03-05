/********************************************************************
Created by UIEditor.exe
FileName: E:\Code\RunTime\CLIENT\Data\UI\ExitGame.cpp
*********************************************************************/
#include "MeUi/UiManager.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "PlayerRole.h"
#include "../Player.h"
// #include "Scene/Me3d_CScene.h"
// #include "Me3d/Me3d_world.h"
#include "GameSettingUI.h"
#include "escdlg.h"
//  
#include "ExitGame.h"
// #include "help.h"
#include "customShortcutKey.h"
#include "../ShowScreenText.h"
#include "messageBox.h"
#include "XmlStringLanguage.h"
#include "GameSettingUI.h"
#include "SystemSettingUI.h"
#include "core/Name.h"
#include "Browser/Browser.h"
#include "Resource/Resource.h"
#include "Cfg.h"
#include "ui/DemandItem.h"
#include "ui/GameSettingUIBase.h"
#include "MainMenu.h"
#include "AutoAttackSet.h"
#include "ui/LoginCheck.h"
#include "ui/Team.h"
#include "UserData.h"
#include "GameSetting.h"
#include "SystemSetting.h"
#include "Common.h"
#include "SettingGame.h"
#include "GameSettingBgFrame.h"
#include "CommonChatFrame.h"
#include "ExitTip.h"
#include "escdlg.h"

extern bool g_bCloseApp;
extern GAME_STATE	g_GameState;
// extern Me3d_World g_World;
extern BOOL g_bMainToSelectUI;
extern CHeroGame* theApp;
extern BOOL	g_bRenderUI;
extern BOOL g_bBackToLogin;
extern BOOL g_bIsShowDisconnect;
extern BOOL g_bConnectDis;
BOOL DynamicMapLoadThreadExit();
extern BOOL	g_DynamicMapLoadThreadWillExit;
BOOL DebugCommand( const char* pszCommand );
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
HWND g_HelpHwnd = NULL;
extern HWND g_hWnd;

 bool CUI_ID_FRAME_ExitGame::ExitGameToServerIsReturned = false;

CUI_ID_FRAME_ExitGame s_CUI_ID_FRAME_ExitGame;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ExitGame, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ExitGame, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExitGame, ID_BUTTON_GameSetOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExitGame, ID_BUTTON_SystemSetOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExitGame, ID_BUTTON_RestartOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExitGame, ID_BUTTON_ExitGameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExitGame, ID_BUTTON_ContinueGameOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExitGame, ID_BUTTON_keyboardGameOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExitGame, ID_BUTTON_helpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExitGame, ID_BUTTON_BackToLoginOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExitGame, ID_BUTTON_SelectPlayerOnButtonClick )
CUI_ID_FRAME_ExitGame::CUI_ID_FRAME_ExitGame()
{
	// SGuildMember
	m_pID_FRAME_ExitGame = NULL;
	m_pID_BUTTON_GameSet = NULL;
	m_pID_BUTTON_SystemSet = NULL;
	m_pID_BUTTON_Restart = NULL;
	m_pID_BUTTON_ExitGame = NULL;
	m_pID_BUTTON_ContinueGame = NULL;
	//m_pID_BUTTON_keyboard	=	NULL;
	m_pID_BUTTON_help = NULL;

	IsShowDKLJ = true;
}

// Frame
bool CUI_ID_FRAME_ExitGame::OnFrameRun()
{
	guardfunc;
	return true;
	unguard;
}
bool CUI_ID_FRAME_ExitGame::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_ExitGame::ID_BUTTON_GameSetOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	//s_CUI_ID_FRAME_GameSet.SetVisable( TRUE );
	//s_CUI_ID_FRAME_GameSettingUIBase.SetVisable( TRUE );
	//关掉界面
	SetVisable( false );
	return true;
	unguard;
}
bool CUI_ID_FRAME_ExitGame::ID_BUTTON_SystemSetOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	//s_CUI_ID_FRAME_Systemset.SetVisable( TRUE );
	s_CUI_ID_FRAME_GameSettingBgFrame.SetVisable(true);
	//关掉界面
	SetVisable( false );
	return true;
	unguard;
}

bool QuitGameToSelect( char bIsTell, void *pData )   // 从游戏退到选人界面
{
	s_CUI_ID_FRAME_ExitGame.SetExit( false );
	if( !bIsTell )
		return true;
	//if (thePlayerRole.IsFighting())
	//{
	//	GetShowScreenText() ->AddInfo( theXmlString.GetString(eClient_AddInfo_2slk_13), 0xffff0000, 1000 );
	//	SetVisable(false);
	//	return FALSE;
	//}
	//{
	//	MsgAckBackCharaterList msg;
	//	GettheNetworkInput().SendMsg( &msg );
	//	GettheNetworkInput().CheckSendReq();

	//	g_bMainToSelectUI = TRUE;

	//	return true;
	//}
	//Sleep( 1 );
	//DebugCommand("return");

	// 更新快捷键给服务器
	thePlayerRole.SendHotKeyToServer();
#if 0
	MsgExit msg;
	GettheNetworkInput().SendMsg( &msg );
	//GettheNetworkInput().CheckSendReq();

	g_bMainToSelectUI = TRUE;
#else
	MsgReturnToCharacterServer msg;
	GettheNetworkInput().SendMsg( &msg );
	//GettheNetworkInput().CheckSendReq();
#endif
	UiDrawer::StartFillFullScreen( 500, false );

	s_CUI_ID_FRAME_ExitGame.SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_ExitGame::ID_BUTTON_SelectPlayerOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	SetVisable(false);
	s_CUI_ID_FRAME_MessageBox.closeAll(false);
	s_CUI_ID_FRAME_MessageBox.Show(
		theXmlString.GetString(eText_QuitGameToSelect),
		theXmlString.GetString(eText_QuitGameToSelect),
		CUI_ID_FRAME_MessageBox::eTypeCancel,
		true,
		QuitGameToSelect );
	s_CUI_ID_FRAME_MessageBox.SetAutoClose(6);
	s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(true);//.m_pID_BUTTON_Cancel->SetEnable(true);
	UiDrawer::StartFillFullScreen( 500, true ); // 屏幕变黑

	m_bExit = true;
	//s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().WriteData();
	//添加停止挂机功能
	if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
		s_CUI_ID_FRAME_AutoAttackSet.ID_BUTTON_StopOnButtonClick(NULL);

	return true;
	unguard;
}

bool QuitGameToLogin( char bIsTell, void *pData )   // 从游戏退到登录界面
{
	s_CUI_ID_FRAME_ExitGame.SetExit( false );
	if( bIsTell )
	{
		UiDrawer::StartFillFullScreen( 1, false );
		//DebugCommand("return");
		if (thePlayerRole.GetTeamMemberNum() > 0)
		{
			s_CUI_ID_FRAME_Team.CheckChangeFollowState();
			MsgExitTeam ExitTeammsg;
			GettheNetworkInput().SendMsg( &ExitTeammsg );
		}

		MsgExit msg;
		GettheNetworkInput().SendMsg( &msg );
		//GettheNetworkInput().CheckSendReq();

		g_bMainToSelectUI = TRUE;
	}
	return true;
}
// Button
bool CUI_ID_FRAME_ExitGame::ID_BUTTON_BackToLoginOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);
	s_CUI_ID_FRAME_MessageBox.closeAll(false);
	s_CUI_ID_FRAME_MessageBox.Show(
		theXmlString.GetString(eText_QuitGameToLogin),
		theXmlString.GetString(eText_QuitGameToLogin),
		CUI_ID_FRAME_MessageBox::eTypeCancel,
		true,
		QuitGameToLogin );
	s_CUI_ID_FRAME_MessageBox.SetAutoClose(6);
	s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(true);//.m_pID_BUTTON_Cancel->SetEnable(true);
	UiDrawer::StartFillFullScreen( 500, true ); // 屏幕变黑

	m_bExit = true;

	//s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().WriteData();
	//添加停止挂机功能
	if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
		s_CUI_ID_FRAME_AutoAttackSet.ID_BUTTON_StopOnButtonClick(NULL);

	return true;
}
// Button 
//bool CUI_ID_FRAME_ExitGame::ID_BUTTON_keyboardGameOnButtonClick( ControlObject* pSender )
//{
//	guardfunc;
//	s_CUI_ID_FRAME_custom.SetVisable( TRUE );
//	SetVisable( FALSE ) ;
//	return true;
//	unguard;
//}

bool CUI_ID_FRAME_ExitGame::TellExitGameForce( char bIsTell, void* pData )
{
	//::ExitProcess(0);
	if (gCfg.m_bOpenExitPage)
	{
		ShellExecute( NULL, "open", gCfg.m_strExitPage.c_str(), NULL, NULL, 0 );
	}
	::TerminateProcess( ::GetCurrentProcess(), 0 );
	return TRUE;
}
extern HANDLE g_hDynamicLoadMap;
 bool CUI_ID_FRAME_ExitGame::TellExitGameToServer(char bIsTell,void *pData )
{
      if (!bIsTell)
      {
		  return false;
      }

	if (thePlayerRole.GetTeamMemberNum() > 0)
	{
		s_CUI_ID_FRAME_Team.CheckChangeFollowState();
		MsgExitTeam msg;
		GettheNetworkInput().SendMsg( &msg );
	}

	if( g_GameState == G_MAIN )
	{
		char szSetting[MAX_PATH] = {0};
		MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
		GameSetting::Instance()->SaveSetting( szSetting );

		MeSprintf_s(szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
		SystemSetting::Instance()->SaveSetting( szSetting );
	}

	bool bDynMapLoadExit = false;
	while( 1 )
	{
		g_DynamicMapLoadThreadWillExit = TRUE;
		SetEvent(g_hDynamicLoadMap);

		if( DynamicMapLoadThreadExit() )
		{
			bDynMapLoadExit = true;
			break;
		}

		Sleep( 1 );
	}

	MsgExit msg;
	GettheNetworkInput().SendMsg(&msg);


	if (theHeroGame.GetPlayerMgr()->GetMe()->m_isOfflineStall)
	{
		g_bCloseApp = true; //直接退出游戏
	}




	ExitGameToServerIsReturned = true;

	return true;
}

bool CUI_ID_FRAME_ExitGame::TellExitGame(char bIsTell,void *pData )    // 关闭客户端
{
	guardfunc;
	if (bIsTell && thePlayerRole.GetTeamMemberNum() > 0)
	{
		s_CUI_ID_FRAME_Team.CheckChangeFollowState();
		MsgExitTeam msg;
		GettheNetworkInput().SendMsg( &msg );
	}
	if (bIsTell && !g_bCloseApp && !g_DynamicMapLoadThreadWillExit)
	{
		//s_CUI_ID_FRAME_GameSetup.GameSet.exportXMLSettings("GameSetting.xml");
		// 从游戏内退出游戏，保存游戏设置
		if( g_GameState == G_MAIN )
		{
			char szSetting[MAX_PATH] = {0};
			MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
			GameSetting::Instance()->SaveSetting( szSetting );

			MeSprintf_s(szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
			SystemSetting::Instance()->SaveSetting( szSetting );
		}

		bool bDynMapLoadExit = false;
		while( 1 )
		{
			g_DynamicMapLoadThreadWillExit = TRUE;
			SetEvent(g_hDynamicLoadMap);

			if( DynamicMapLoadThreadExit() )
			{
				bDynMapLoadExit = true;
				break;
			}

			Sleep( 1 );
		}
		//// 发送退出游戏消息，并等消息队列发送完
		//MsgExit msg;
		//GettheNetworkInput().SendMsg(&msg); //lyh屏蔽结束游戏读秒结束发送退出消息，改为往前提一秒发送
		
		if (theHeroGame.GetPlayerMgr()->GetMe()->m_isOfflineStall)
		{
			g_bCloseApp = true; //直接退出游戏
		}
		
		//GettheNetworkInput().CheckSendReq();
		while( 1 )
		{
			//if( GettheNetworkInput().IsAllMsgSendOver() )
			//{
			//	g_bCloseApp = true;
			//	return true;
			//}

			Sleep( 1 );
			return true;
		}

		return true;
	}
	else
		s_CUI_ID_FRAME_ExitGame.SetExit( false );

	return FALSE;
	unguard;
}

// Button
bool CUI_ID_FRAME_ExitGame::ID_BUTTON_ExitGameOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	//if (thePlayerRole.IsFighting())
	//{
	//	GetShowScreenText() ->AddInfo( theXmlString.GetString(eClient_AddInfo_2slk_13), 0xffff0000, 1000 );
	//	SetVisable(false);
	//	return FALSE;
	//}


	SetVisable(false);
	/*s_CUI_ID_FRAME_MessageBox.closeAll(false);
	s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString(eIsExitGame), theXmlString.GetString(eClient_AddInfo_2slk_16),
		CUI_ID_FRAME_MessageBox::eTypeYesNo, true, CUI_ID_FRAME_ExitGame::ExitGameCountDown);*/

	s_CUI_ID_FRAME_ExitTip.SetVisable( true );
	s_CUI_ID_FRAME_ExitTip.RefreshInfo();

	//UiDrawer::StartFillFullScreen( 500, true );

	m_bExit = true;
	//s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().WriteData();
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_ExitGame::ID_BUTTON_ContinueGameOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	SetVisable( false );
	return true;
	unguard;
}


bool CUI_ID_FRAME_ExitGame::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_ExitGame )
		return false;

	// 		s_CUI_ID_FRAME_Help.SetVisable( true );

// 	if (NULL == g_HelpHwnd)
// 	{
// 		g_HelpHwnd = theHeroGame.CreateHelpWindow();
// 	}
// 	// 		if( !g_HelpHwnd )
// 	// 		{
// 	// 			g_HelpHwnd = CreateDialog( 
// 	// 				0, 
// 	// 				_T("Help Window"), g_hWnd, 
// 	// 				HelpWndProc );
// 	// 		}
// 	if (g_HelpHwnd)
// 	{
// 		char fullname[MAX_PATH] = {0};
// 		sprintf( fullname, "%s/%s", GetRootPath(),gCfg.m_szHelpPagePath );
// 
// 		DisplayHTMLPage(g_HelpHwnd,fullname);
// 		// 			ShowWindow( g_HelpHwnd, SW_HIDE );
// 		ShowWindow( g_HelpHwnd, SW_SHOW );
// 		//UiDrawer::StartFillFullScreen( 500 );
// 	}
	SetVisable(false);
	return true;
	unguard;
}

void CUI_ID_FRAME_ExitGame::InitializeAtEnterWorld()
{
    if( !m_pID_FRAME_ExitGame )
        return;

//     CUILayout::GetInstance()->AddFrame( m_pID_FRAME_ExitGame );
    m_pID_FRAME_ExitGame->SetMsgProcFun( CUI_ID_FRAME_ExitGame::MsgProc );
    m_pID_FRAME_ExitGame->SetOnVisibleChangedFun( CUI_ID_FRAME_ExitGame::OnVisibleChanged );
    //m_pID_BUTTON_Restart->SetEnable( FALSE );
    m_bExit = false;
    _SetVisable( false );

	// 如果显示退出窗口的时候清理掉所有的FreeTip
	CommonChatFrame::HideAllFreeTip();
}

// 装载UI
bool CUI_ID_FRAME_ExitGame::_LoadUI()
{		
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\ExitGame.meui", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\ExitGame.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_ExitGame::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_ExitGame, s_CUI_ID_FRAME_ExitGameOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ExitGame, s_CUI_ID_FRAME_ExitGameOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ExitGame, ID_BUTTON_GameSet, s_CUI_ID_FRAME_ExitGameID_BUTTON_GameSetOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExitGame, ID_BUTTON_SystemSet, s_CUI_ID_FRAME_ExitGameID_BUTTON_SystemSetOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExitGame, ID_BUTTON_Restart, s_CUI_ID_FRAME_ExitGameID_BUTTON_SelectPlayerOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExitGame, ID_BUTTON_ExitGame, s_CUI_ID_FRAME_ExitGameID_BUTTON_ExitGameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExitGame, ID_BUTTON_ContinueGame, s_CUI_ID_FRAME_ExitGameID_BUTTON_ContinueGameOnButtonClick );
	//theUiManager.OnButtonClick( ID_FRAME_ExitGame, ID_BUTTON_keyboard, s_CUI_ID_FRAME_ExitGameID_BUTTON_keyboardGameOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExitGame, ID_BUTTON_helpsys, s_CUI_ID_FRAME_ExitGameID_BUTTON_helpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExitGame, ID_BUTTON_BackToLogin, s_CUI_ID_FRAME_ExitGameID_BUTTON_BackToLoginOnButtonClick );	

	m_pID_FRAME_ExitGame = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ExitGame );
	m_pID_BUTTON_GameSet = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExitGame, ID_BUTTON_GameSet );
	m_pID_BUTTON_SystemSet = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExitGame, ID_BUTTON_SystemSet );
	m_pID_BUTTON_Restart = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExitGame, ID_BUTTON_Restart );
	m_pID_BUTTON_ExitGame = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExitGame, ID_BUTTON_ExitGame );
	m_pID_BUTTON_ContinueGame = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExitGame, ID_BUTTON_ContinueGame );
	//m_pID_BUTTON_keyboard = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExitGame, ID_BUTTON_keyboard );
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExitGame, ID_BUTTON_helpsys );
	
    assert( m_pID_BUTTON_help );
	assert( m_pID_FRAME_ExitGame );
	assert( m_pID_BUTTON_GameSet );
	assert( m_pID_BUTTON_SystemSet );
	assert( m_pID_BUTTON_Restart );
	assert( m_pID_BUTTON_ExitGame );
	assert( m_pID_BUTTON_ContinueGame );
	//assert( m_pID_BUTTON_keyboard );

    _SetVisable( false );
	return true;
	unguard;
}
// 卸载UI
bool CUI_ID_FRAME_ExitGame::_UnLoadUI()
{
	guardfunc;
	//CLOSE_SCRIPT( eUI_OBJECT_ExitGame );
	m_pID_FRAME_ExitGame = NULL;
	m_pID_BUTTON_GameSet = NULL;
	m_pID_BUTTON_SystemSet = NULL;
	m_pID_BUTTON_Restart = NULL;
	m_pID_BUTTON_ExitGame = NULL;
	m_pID_BUTTON_ContinueGame = NULL;
	//m_pID_BUTTON_keyboard	=	NULL;
	m_pID_BUTTON_help = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\ExitGame.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_ExitGame::_IsVisable()
{
	guardfunc;
	if( m_pID_FRAME_ExitGame )
		return m_pID_FRAME_ExitGame->IsVisable();
	return false;
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_ExitGame::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( m_pID_FRAME_ExitGame )
	{
		//if( bVisable != IsVisable() )
		//	CUILayout::GetInstance()->SetVisable(m_pID_FRAME_ExitGame);
		//else
		if (bVisable) //lyh++ 如果显示退出界面，立马隐藏所有的界面 为了解决 窗口变换的时候，界面的位置可能跑到屏幕外边而点不到
		{
			theUiManager.HideAllDlgNoAllVisable();
		}

		m_pID_FRAME_ExitGame->SetVisable( bVisable );			
	}
	//	m_pID_FRAME_ExitGame->SetVisable( bVisable );
	//	m_pID_FRAME_ExitGame->SetAllVisable( bVisable, true );
	unguard;
}

void CUI_ID_FRAME_ExitGame::OnVisibleChanged( ControlObject* pSender )
{
	//UiDrawer::StartFillFullScreen( 500, s_CUI_ID_FRAME_ExitGame.IsVisable() );
	//s_CUI_ID_FRAME_MainMenu.SetButSysNormalPic();//.m_pID_BUTTON_System->SetNormalPic();
	s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiHideOrSystem,true);
}

bool CUI_ID_FRAME_ExitGame::BackToLogin( char bIsTell,void *pData )    // 断开链接时返回登录界面
{
	// 如果验证码界面开着，关闭
	if( s_CUI_ID_FRAME_LoginCheck.IsVisable() )
		s_CUI_ID_FRAME_LoginCheck.SetVisable(false);

	//添加停止挂机功能
	if(s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
		s_CUI_ID_FRAME_AutoAttackSet.ID_BUTTON_StopOnButtonClick(NULL);

	//DemandItemFrameManage.Reset();  // 重置掷骰子界面
	g_bBackToLogin = TRUE;
	g_bIsShowDisconnect = FALSE;
	g_bConnectDis = TRUE;
	s_CUI_ID_FRAME_ExitGame.IsShowDKLJ = true;
	return true;
}

bool CUI_ID_FRAME_ExitGame::ExitGameCountDown( char bIsTell, void *pData ) // 退出客户端倒计时
{
	if( bIsTell )
	{
		s_CUI_ID_FRAME_MessageBox.Show(
			theXmlString.GetString(eText_ExitGameCountDown),
			theXmlString.GetString(eText_ExitGameCountDown),
			CUI_ID_FRAME_MessageBox::eTypeCancel,
			true,
			TellExitGame );
		s_CUI_ID_FRAME_MessageBox.SetAutoClose(6);
		s_CUI_ID_FRAME_MessageBox.SetButEnableCancel(true);//.m_pID_BUTTON_Cancel->SetEnable(true);
		UiDrawer::StartFillFullScreen( 500, true ); // 屏幕变黑
	}
	return true;
}

bool CUI_ID_FRAME_ExitGame::ExitByHookOff( char bIsTell, void *pData ) // 以离线挂机方式退出客户端
{
    if( bIsTell )
    {
        MsgSetOfflineHook msg;
        msg.bSetOfflineHook = true;
        GettheNetworkInput().SendMsg( &msg );
    }
    return true;
}

bool CUI_ID_FRAME_ExitGame::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if (/* bMsgUsed == true || */g_GameState != G_MAIN )
		return false;

	switch( msg ) 
	{
	case WM_KEYUP:
		{
			if( wParam == g_shortcutKey_configure.getValueCharWin32(AN_Configure_ShortcutKey::AN_SCKC_uiHideOrSystem) )
			{
				if( !g_bRenderUI )
					break;

				if( s_CUI_ID_FRAME_custom.IsVisable() )
					break;

				// 特殊处理，Esc键先关闭所有FreeTip
				if ( CommonChatFrame::EscCloseFreeTip() )
				{
					return true;
				}

				if( theApp->GetPlayerMgr()->GetLockPlayerID() < 0 )
				{
					if( !theUiManager.HideDlg() )
					{
						//SetVisable( !IsVisable() );
						if (thePlayerRole.IsDie() && !s_CUI_ID_FRAME_ESCDLG.IsVisable())
						{
							s_CUI_ID_FRAME_ESCDLG.SetVisable(true);
						}
						else
						{
							if( !s_CUI_ID_FRAME_ExitGame.IsVisable() )
								s_CUI_ID_FRAME_ExitGame.SetVisable( true );
							else
								s_CUI_ID_FRAME_ExitGame.SetVisable( false );
						}
						return true;
					}
				}
				else
				{
					theUiManager.HideDlg();
				}
			}
		}
		break;
	case WM_KEYDOWN:
		if( (wParam == VK_F4 && GetAsyncKeyState(VK_MENU) & 0x800000) )
		{
			if( !g_bRenderUI )
				break;

			if(s_CUI_ID_FRAME_ExitGame.IsVisable())
				s_CUI_ID_FRAME_ExitGame.SetVisable(false);
			else
				theUiManager.HideDlg();
		}
		break;
	}
	return false;
	unguard;
}