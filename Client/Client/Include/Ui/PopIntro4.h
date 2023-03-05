/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\PopIntro4.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_PopIntro4
#define ID_FRAME_PopIntro4		"ID_FRAME_PopIntro4"
#endif  ID_FRAME_PopIntro4
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_CHECKBOX_Close
#define ID_CHECKBOX_Close		"ID_CHECKBOX_Close"
#endif  ID_CHECKBOX_Close
#ifndef ID_TEXT_GuideGif
#define ID_TEXT_GuideGif		"ID_TEXT_GuideGif"
#endif  ID_TEXT_GuideGif

class CUI_ID_FRAME_PopIntro4 :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_PopIntro4();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_CloseOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
private:
	ControlFrame*	m_pID_FRAME_PopIntro4;
	ControlText*	m_pID_TEXT_Info;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlText*	m_pID_TEXT_Title;
	ControlCheckBox*	m_pID_CHECKBOX_Close;
	ControlText*	m_pID_TEXT_GuideGif;
public:
	void ShowInfo(int nTitleId,int nStrindId);
};
extern CUI_ID_FRAME_PopIntro4 s_CUI_ID_FRAME_PopIntro4;
