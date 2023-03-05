/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\SevenDaysButton.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_SevenDaysButton
#define ID_FRAME_SevenDaysButton		"ID_FRAME_SevenDaysButton"
#endif  ID_FRAME_SevenDaysButton
#ifndef ID_BUTTON_Show
#define ID_BUTTON_Show		"ID_BUTTON_Show"
#endif  ID_BUTTON_Show
#ifndef ID_TEXT_Show
#define ID_TEXT_Show		"ID_TEXT_Show"
#endif  ID_TEXT_Show

class CUI_ID_FRAME_SevenDaysButton : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_SevenDaysButton();
	virtual ~CUI_ID_FRAME_SevenDaysButton();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_ShowOnButtonClick( ControlObject* pSender );
	bool ID_TEXT_ShowOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();

	void SetShowText();
	int GetDayTime( __time64_t startTime, __time64_t nowTime );

private:	
	 ControlFrame*	m_pID_FRAME_SevenDaysButton;
	 ControlButton*	m_pID_BUTTON_Show;
	 ControlText*	m_pID_TEXT_Show;
};
extern CUI_ID_FRAME_SevenDaysButton s_CUI_ID_FRAME_SevenDaysButton;
