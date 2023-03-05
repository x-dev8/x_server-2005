/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\chixin.ni\桌面\DeleteCase.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_DeleteCase
#define ID_FRAME_DeleteCase		"ID_FRAME_DeleteCase"
#endif  ID_FRAME_DeleteCase
#ifndef ID_PICTURE_BackGround
#define ID_PICTURE_BackGround		"ID_PICTURE_BackGround"
#endif  ID_PICTURE_BackGround
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Reset
#define ID_BUTTON_Reset		"ID_BUTTON_Reset"
#endif  ID_BUTTON_Reset
#ifndef ID_BUTTON_Delete
#define ID_BUTTON_Delete		"ID_BUTTON_Delete"
#endif  ID_BUTTON_Delete
#ifndef ID_CHECKBOX_Reason0
#define ID_CHECKBOX_Reason0		"ID_CHECKBOX_Reason0"
#endif  ID_CHECKBOX_Reason0
#ifndef ID_CHECKBOX_Reason1
#define ID_CHECKBOX_Reason1		"ID_CHECKBOX_Reason1"
#endif  ID_CHECKBOX_Reason1
#ifndef ID_CHECKBOX_Reason2
#define ID_CHECKBOX_Reason2		"ID_CHECKBOX_Reason2"
#endif  ID_CHECKBOX_Reason2
#ifndef ID_CHECKBOX_Reason3
#define ID_CHECKBOX_Reason3		"ID_CHECKBOX_Reason3"
#endif  ID_CHECKBOX_Reason3
#ifndef ID_CHECKBOX_Reason4
#define ID_CHECKBOX_Reason4		"ID_CHECKBOX_Reason4"
#endif  ID_CHECKBOX_Reason4
#ifndef ID_EDIT_Reason0
#define ID_EDIT_Reason0		"ID_EDIT_Reason0"
#endif  ID_EDIT_Reason0
#ifndef ID_TEXT_Reason1
#define ID_TEXT_Reason1		"ID_TEXT_Reason1"
#endif  ID_TEXT_Reason1
#ifndef ID_TEXT_Reason2
#define ID_TEXT_Reason2		"ID_TEXT_Reason2"
#endif  ID_TEXT_Reason2
#ifndef ID_TEXT_Reason3
#define ID_TEXT_Reason3		"ID_TEXT_Reason3"
#endif  ID_TEXT_Reason3
#ifndef ID_TEXT_Reason4
#define ID_TEXT_Reason4		"ID_TEXT_Reason4"
#endif  ID_TEXT_Reason4
#ifndef ID_TEXT_Reason5
#define ID_TEXT_Reason5		"ID_TEXT_Reason5"
#endif  ID_TEXT_Reason5

#include "UiBase.h"
class CUI_ID_FRAME_DeleteCase :public CUIBase
{
	// Member
private:	
	ControlFrame*	m_pID_FRAME_DeleteCase;
	//ControlPicture*	m_pID_PICTURE_BackGround;
	ControlText*	m_pID_TEXT_Title;
	//ControlButton*	m_pID_BUTTON_CLOSE;
	ControlButton*	m_pID_BUTTON_Reset;
	ControlButton*	m_pID_BUTTON_Delete;
// 	ControlCheckBox*	m_pID_CHECKBOX_Reason0;
// 	ControlCheckBox*	m_pID_CHECKBOX_Reason1;
// 	ControlCheckBox*	m_pID_CHECKBOX_Reason2;
// 	ControlCheckBox*	m_pID_CHECKBOX_Reason3;
// 	ControlCheckBox*	m_pID_CHECKBOX_Reason4;
// 	ControlEdit*	m_pID_EDIT_Reason0;
// 	ControlText*	m_pID_TEXT_Reason1;
// 	ControlText*	m_pID_TEXT_Reason2;
// 	ControlText*	m_pID_TEXT_Reason3;
// 	ControlText*	m_pID_TEXT_Reason4;
// 	ControlText*	m_pID_TEXT_Reason5;

public:
	CUI_ID_FRAME_DeleteCase();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	//bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ResetOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender );
// 	void ID_CHECKBOX_Reason0OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_Reason1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_Reason2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_Reason3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_Reason4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_EDIT_Reason0OnEditEnter( ControlObject* pSender, const char* szData );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void WriteBack();
	void SendMail(const char* pszFileName,string content);
};
extern CUI_ID_FRAME_DeleteCase s_CUI_ID_FRAME_DeleteCase;
