/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\ExitGame.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_ExitGame
#define ID_FRAME_ExitGame		"ID_FRAME_ExitGame"
#endif  ID_FRAME_ExitGame
#ifndef ID_BUTTON_GameSet
#define ID_BUTTON_GameSet		"ID_BUTTON_GameSet"
#endif  ID_BUTTON_GameSet
#ifndef ID_BUTTON_SystemSet
#define ID_BUTTON_SystemSet		"ID_BUTTON_SystemSet"
#endif  ID_BUTTON_SystemSet
#ifndef ID_BUTTON_Restart
#define ID_BUTTON_Restart		"ID_BUTTON_Restart"
#endif  ID_BUTTON_Restart
#ifndef ID_BUTTON_ExitGame
#define ID_BUTTON_ExitGame		"ID_BUTTON_ExitGame"
#endif  ID_BUTTON_ExitGame
#ifndef ID_BUTTON_ContinueGame
#define ID_BUTTON_ContinueGame		"ID_BUTTON_ContinueGame"
#endif  ID_BUTTON_ContinueGame
#ifndef ID_BUTTON_keyboard
#define ID_BUTTON_keyboard		"ID_BUTTON_keyboard"
#endif  ID_BUTTON_keyboard
#ifndef ID_BUTTON_helpsys
#define ID_BUTTON_helpsys	"ID_BUTTON_helpsys"
#endif ID_BUTTON_helpsys
#ifndef ID_BUTTON_BackToLogin
#define ID_BUTTON_BackToLogin		"ID_BUTTON_BackToLogin"
#endif  ID_BUTTON_BackToLogin

#include "UiBase.h"
class CUI_ID_FRAME_ExitGame :public CUIBase
{
private:
	// SGuildMember
	ControlFrame*	m_pID_FRAME_ExitGame;
	ControlButton*	m_pID_BUTTON_GameSet;
	ControlButton*	m_pID_BUTTON_SystemSet;
	ControlButton*	m_pID_BUTTON_Restart;
	ControlButton*	m_pID_BUTTON_ExitGame;
	ControlButton*	m_pID_BUTTON_ContinueGame;
	//ControlButton*	m_pID_BUTTON_keyboard;
	ControlButton*	m_pID_BUTTON_help;
	bool m_bExit;
public:
	CUI_ID_FRAME_ExitGame();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	// Button
	bool ID_BUTTON_GameSetOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SystemSetOnButtonClick( ControlObject* pSender );
	// Button
	//bool ID_BUTTON_RestartOnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_ExitGameOnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_ContinueGameOnButtonClick( ControlObject* pSender );
	// Button
	//bool ID_BUTTON_keyboardGameOnButtonClick( ControlObject* pSender );
	//button
	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BackToLoginOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SelectPlayerOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
    virtual bool IsHoldInMemory() const { return true; }
    virtual void InitializeAtEnterWorld();

    static bool ExitGameCountDown(char bIsTell, void *pData);
    static bool ExitByHookOff( char bIsTell, void *pData );
	static bool TellExitGame(char bIsTell,void *pData );

	static bool TellExitGameToServer(char bIsTell,void *pData );
	static bool ExitGameToServerIsReturned ;
	// added, jiayi, [2009/9/6]
	static bool TellExitGameForce( char bIsTell, void* pData );//强制退出
    static bool BackToLogin(char bIsTell,void *pData);
	//bool QuitGameToSelect( char bIsTell, void *pData );
	//bool QuitGameToLogin( char bIsTell, void *pData );

	static void OnVisibleChanged( ControlObject* pSender );

	static bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

	void SetExit( bool b ){ m_bExit = b; }
	bool GetExit(){ return m_bExit; }

	bool IsShowDKLJ;
};

extern CUI_ID_FRAME_ExitGame s_CUI_ID_FRAME_ExitGame;