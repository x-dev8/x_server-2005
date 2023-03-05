/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\策划文档\密保卡界面\PasswordProtect.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_PasswordProtect
#define ID_FRAME_PasswordProtect		"ID_FRAME_PasswordProtect"
#endif  ID_FRAME_PasswordProtect
#ifndef ID_TEXT_Msg
#define ID_TEXT_Msg		"ID_TEXT_Msg"
#endif  ID_TEXT_Msg
#ifndef ID_PICTURE_Wall
#define ID_PICTURE_Wall		"ID_PICTURE_Wall"
#endif  ID_PICTURE_Wall
#ifndef ID_EDIT_AddName
#define ID_EDIT_AddName		"ID_EDIT_AddName"
#endif  ID_EDIT_AddName
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancle
#define ID_BUTTON_Cancle		"ID_BUTTON_Cancle"
#endif  ID_BUTTON_Cancle
#ifndef ID_TEXT_Msg2
#define ID_TEXT_Msg2		"ID_TEXT_Msg2"
#endif  ID_TEXT_Msg2
#ifndef ID_PICTURE_Wall2
#define ID_PICTURE_Wall2		"ID_PICTURE_Wall2"
#endif  ID_PICTURE_Wall2
#ifndef ID_EDIT_AddName2
#define ID_EDIT_AddName2		"ID_EDIT_AddName2"
#endif  ID_EDIT_AddName2
#ifndef ID_TEXT_Msg3
#define ID_TEXT_Msg3		"ID_TEXT_Msg3"
#endif  ID_TEXT_Msg3
#ifndef ID_PICTURE_Wall3
#define ID_PICTURE_Wall3		"ID_PICTURE_Wall3"
#endif  ID_PICTURE_Wall3
#ifndef ID_EDIT_AddName3
#define ID_EDIT_AddName3		"ID_EDIT_AddName3"
#endif  ID_EDIT_AddName3
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_PICTURE_TitleWall
#define ID_PICTURE_TitleWall		"ID_PICTURE_TitleWall"
#endif  ID_PICTURE_TitleWall
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title

#include "UiBase.h"
class CUI_ID_FRAME_PasswordProtect :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_PasswordProtect();
private:
	 ControlFrame*	m_pID_FRAME_PasswordProtect;
	 ControlText*	m_pID_TEXT_Msg;
	 ControlPicture*	m_pID_PICTURE_Wall;
	 ControlEdit*	m_pID_EDIT_AddName;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Cancle;
	 ControlText*	m_pID_TEXT_Msg2;
	 ControlPicture*	m_pID_PICTURE_Wall2;
	 ControlEdit*	m_pID_EDIT_AddName2;
	 ControlText*	m_pID_TEXT_Msg3;
	 ControlPicture*	m_pID_PICTURE_Wall3;
	 ControlEdit*	m_pID_EDIT_AddName3;
	 ControlText*	m_pID_TEXT_Title;
	 ControlPicture*	m_pID_PICTURE_TitleWall;
	 //ControlPicture*	m_pID_PICTURE_Title;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );
	void ID_EDIT_AddName2OnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_AddName3OnEditEnter( ControlObject* pSender, const char* szData );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

protected:
	float m_fCountDown;	// 倒计时60秒后自动关闭
};
extern CUI_ID_FRAME_PasswordProtect s_CUI_ID_FRAME_PasswordProtect;
