#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_Only
#define ID_FRAME_Only		"ID_FRAME_Only"
#endif  ID_FRAME_Only
#ifndef ID_BUTTON_Only
#define ID_BUTTON_Only		"ID_BUTTON_Only"
#endif  ID_BUTTON_Only

class CUI_ID_FRAME_Only : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_Only();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OnlyOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
private:
	ControlFrame*	m_pID_FRAME_Only;
	ControlButton*	m_pID_BUTTON_Only;
};
extern CUI_ID_FRAME_Only s_CUI_ID_FRAME_Only;
