/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\TradeRecord.h
*********************************************************************/
#pragma once

#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_TradeRecord
#define ID_FRAME_TradeRecord		"ID_FRAME_TradeRecord"
#endif  ID_FRAME_TradeRecord
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_Clear
#define ID_BUTTON_Clear		"ID_BUTTON_Clear"
#endif  ID_BUTTON_Clear
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_Record
#define ID_TEXT_Record		"ID_TEXT_Record"
#endif  ID_TEXT_Record

class CUI_ID_FRAME_TradeRecord : public CUIBase
{
private:	
	 ControlFrame*	m_pID_FRAME_TradeRecord;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_Clear;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlText*	m_pID_TEXT_Record;

public:	
	CUI_ID_FRAME_TradeRecord();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ClearOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视

    void Refresh();

protected:
    void ResetMembers();
};

extern CUI_ID_FRAME_TradeRecord s_CUI_ID_FRAME_TradeRecord;
