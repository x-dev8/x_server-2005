/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\chixin.ni\桌面\密码\密码\SuperPassword.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"

#ifndef ID_FRAME_SuperPassword
#define ID_FRAME_SuperPassword		"ID_FRAME_SuperPassword"
#endif  ID_FRAME_SuperPassword
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
#ifndef ID_BUTTON_ForgetPassword
#define ID_BUTTON_ForgetPassword		"ID_BUTTON_ForgetPassword"
#endif  ID_BUTTON_ForgetPassword
#ifndef ID_TEXT_UnLock
#define ID_TEXT_UnLock		"ID_TEXT_UnLock"
#endif  ID_TEXT_UnLock

#include "UiBase.h"
class CUI_ID_FRAME_SuperPassword :public CUIBase
{
	// Member
private:
	void ResetMembers();
	 ControlFrame*	m_pID_FRAME_SuperPassword;
	 ControlText*	m_pID_TEXT_Msg;
	 ControlPicture*	m_pID_PICTURE_Wall;
	 ControlEdit*	m_pID_EDIT_AddName;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Cancle;
	 ControlButton*	m_pID_BUTTON_ForgetPassword;
	 ControlText*	m_pID_TEXT_UnLock;

public:	
	CUI_ID_FRAME_SuperPassword();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ForgetPasswordOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	bool Reset();
	void SetChOperator(uint8 ucho){ uchOperator = ucho; };
	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }
	ControlEdit* GetEditAddName();
	bool EditInputIsVisable();
	bool GetChecked(){return m_bHasChecked;}
	void SetChecked(bool value){m_bHasChecked = value;}
private:
	static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );


	uint8 uchOperator;

	const Vector& GetVisiblePosition() const { return m_vVisiblePos; }
	Vector m_vVisiblePos;	
	bool m_bHasChecked;			//是否已经通过二级密码验证;
};
extern CUI_ID_FRAME_SuperPassword s_CUI_ID_FRAME_SuperPassword;
