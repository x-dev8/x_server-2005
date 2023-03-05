/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\PopIntro.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_POPINTRO
#define ID_FRAME_POPINTRO		"ID_FRAME_PopIntro"
#endif  ID_FRAME_POPINTRO
#ifndef ID_BUTTON_COMFIRM
#define ID_BUTTON_COMFIRM		"ID_BUTTON_COMFIRM"
#endif  ID_BUTTON_COMFIRM
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_CHECKBOX_Close
#define ID_CHECKBOX_Close		"ID_CHECKBOX_Close"
#endif  ID_CHECKBOX_Close
// #ifndef ID_TEXT_Close
// #define ID_TEXT_Close		"ID_TEXT_Close"
// #endif  ID_TEXT_Close

#include "UiBase.h"
class CUI_ID_FRAME_POPINTRO :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_POPINTRO();
private:
	 ControlFrame*	m_pID_FRAME_POPINTRO;
// 	 ControlPicture*	m_pID_PICTURE_Info;
	 ControlButton*	m_pID_BUTTON_COMFIRM;
	 ControlText*	m_pID_TEXT_Info;
	 ControlText*	m_pID_TEXT_Title;
	 ControlCheckBox*	m_pID_CHECKBOX_Close;
// 	 ControlText*	m_pID_TEXT_Close;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_COMFIRMOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_CloseOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	void SetVisable( const bool bVisable ,const char* pTitle,const char* pString);

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable ,const char* pTitle,const char* pString);			// 设置是否可视
public:


	static void HyberClickIntro( ControlObject* pSender, const char* szName );

	void CheckBoxClose_SetCheck(bool bCheck);
private:
};
extern CUI_ID_FRAME_POPINTRO s_CUI_ID_FRAME_POPINTRO;
