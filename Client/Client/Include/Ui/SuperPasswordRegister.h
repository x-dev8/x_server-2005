/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\chixin.ni\����\����\����\SuperPasswordRegister.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "me3d/Vector.h"

#ifndef ID_FRAME_SuperPasswordRegister
#define ID_FRAME_SuperPasswordRegister		"ID_FRAME_SuperPasswordRegister"
#endif  ID_FRAME_SuperPasswordRegister
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
#ifndef ID_PICTURE_Tip
#define ID_PICTURE_Tip		"ID_PICTURE_Tip"
#endif  ID_PICTURE_Tip

#include "UiBase.h"
class CUI_ID_FRAME_SuperPasswordRegister :public CUIBase
{
	// Member
private:
	void ResetMembers();
	 ControlFrame*	m_pID_FRAME_SuperPasswordRegister;
	 ControlText*	m_pID_TEXT_Msg;
	 ControlPicture*	m_pID_PICTURE_Wall;
	 ControlEdit*	m_pID_EDIT_AddName;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Cancle;
	 ControlText*	m_pID_TEXT_Msg2;
	 ControlPicture*	m_pID_PICTURE_Wall2;
	 ControlEdit*	m_pID_EDIT_AddName2;
	 ControlPicture*	m_pID_PICTURE_Tip;

public:	
	CUI_ID_FRAME_SuperPasswordRegister();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );
	void ID_EDIT_AddName2OnEditEnter( ControlObject* pSender, const char* szData );

	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
public:


	bool Reset();
	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }
	ControlEdit* GetEDIT_AddName();
	ControlEdit* GetEDIT_AddName2();
	bool EditInputIsVisable();
private:
	static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );


	const Vector& GetVisiblePosition() const { return m_vVisiblePos; }
	Vector m_vVisiblePos;	
};
extern CUI_ID_FRAME_SuperPasswordRegister s_CUI_ID_FRAME_SuperPasswordRegister;
