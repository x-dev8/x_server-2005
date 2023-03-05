/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (13)\FamilyUI\FamilyLogo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_FamilyLogo
#define ID_FRAME_FamilyLogo		"ID_FRAME_FamilyLogo"
#endif  ID_FRAME_FamilyLogo
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Sure
#define ID_BUTTON_Sure		"ID_BUTTON_Sure"
#endif  ID_BUTTON_Sure
#ifndef ID_CHECKBOX_Logo01
#define ID_CHECKBOX_Logo01		"ID_CHECKBOX_Logo01"
#endif  ID_CHECKBOX_Logo01
#ifndef ID_CHECKBOX_Logo02
#define ID_CHECKBOX_Logo02		"ID_CHECKBOX_Logo02"
#endif  ID_CHECKBOX_Logo02
#ifndef ID_CHECKBOX_Logo03
#define ID_CHECKBOX_Logo03		"ID_CHECKBOX_Logo03"
#endif  ID_CHECKBOX_Logo03
#ifndef ID_CHECKBOX_Logo04
#define ID_CHECKBOX_Logo04		"ID_CHECKBOX_Logo04"
#endif  ID_CHECKBOX_Logo04
#ifndef ID_CHECKBOX_Logo05
#define ID_CHECKBOX_Logo05		"ID_CHECKBOX_Logo05"
#endif  ID_CHECKBOX_Logo05
#ifndef ID_CHECKBOX_Logo06
#define ID_CHECKBOX_Logo06		"ID_CHECKBOX_Logo06"
#endif  ID_CHECKBOX_Logo06
#ifndef ID_CHECKBOX_Logo07
#define ID_CHECKBOX_Logo07		"ID_CHECKBOX_Logo07"
#endif  ID_CHECKBOX_Logo07
#ifndef ID_CHECKBOX_Logo08
#define ID_CHECKBOX_Logo08		"ID_CHECKBOX_Logo08"
#endif  ID_CHECKBOX_Logo08

#include "UiBase.h"

class CUI_ID_FRAME_FamilyLogo : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_FamilyLogo();
	 ControlFrame*	m_pID_FRAME_FamilyLogo;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_Sure;
	 ControlCheckBox*	m_pID_CHECKBOX_Logo01;
	 ControlCheckBox*	m_pID_CHECKBOX_Logo02;
	 ControlCheckBox*	m_pID_CHECKBOX_Logo03;
	 ControlCheckBox*	m_pID_CHECKBOX_Logo04;
	 ControlCheckBox*	m_pID_CHECKBOX_Logo05;
	 ControlCheckBox*	m_pID_CHECKBOX_Logo06;
	 ControlCheckBox*	m_pID_CHECKBOX_Logo07;
	 ControlCheckBox*	m_pID_CHECKBOX_Logo08;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SureOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_Logo01OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Logo02OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Logo03OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Logo04OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Logo05OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Logo06OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Logo07OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Logo08OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

public:
	void UncheckedAll();

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
private:	
};
extern CUI_ID_FRAME_FamilyLogo s_CUI_ID_FRAME_FamilyLogo;
