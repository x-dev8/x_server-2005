/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\chixin.ni\桌面\金锭UI\GoldTradeSelect.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GoldTradeSelect
#define ID_FRAME_GoldTradeSelect		"ID_FRAME_GoldTradeSelect"
#endif  ID_FRAME_GoldTradeSelect
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

#include "UIBase.h"

class CUI_ID_FRAME_GoldTradeSelect : public CUIBase
{
	// Member
private:
	 ControlFrame*	m_pID_FRAME_GoldTradeSelect;
	 ControlText*	m_pID_TEXT_Msg;
	 ControlPicture*	m_pID_PICTURE_Wall;
	 ControlEdit*	m_pID_EDIT_AddName;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Cancle;

public:	
	CUI_ID_FRAME_GoldTradeSelect();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_AddNameOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void SetBuy();
	void SetSell();
private:
	bool m_IsBuy;

};
extern CUI_ID_FRAME_GoldTradeSelect s_CUI_ID_FRAME_GoldTradeSelect;
