/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\RTX\GuildResource.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_GuildResource
#define ID_FRAME_GuildResource		"ID_FRAME_GuildResource"
#endif  ID_FRAME_GuildResource
#ifndef ID_PICTURE_Money
#define ID_PICTURE_Money		"ID_PICTURE_Money"
#endif  ID_PICTURE_Money
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_TipsText
#define ID_TEXT_TipsText		"ID_TEXT_TipsText"
#endif  ID_TEXT_TipsText
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_BUTTON_MoneyInput
#define ID_BUTTON_MoneyInput		"ID_BUTTON_MoneyInput"
#endif  ID_BUTTON_MoneyInput
#ifndef ID_TEXT_MoneyText
#define ID_TEXT_MoneyText		"ID_TEXT_MoneyText"
#endif  ID_TEXT_MoneyText

class CUI_ID_FRAME_GuildResource : public CUIBase
{
	// Member
public:
	CUI_ID_FRAME_GuildResource();

private:	
	 ControlFrame*	m_pID_FRAME_GuildResource;
	 ControlPicture*	m_pID_PICTURE_Money;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_TipsText;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlText*	m_pID_TEXT_Money;
	 ControlButton*	m_pID_BUTTON_MoneyInput;
	 ControlText*	m_pID_TEXT_MoneyText;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MoneyInputOnButtonClick( ControlObject* pSender );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视

	void ShowGuildDonate();
	static bool GetGuildDonateResult( DWORD dwMoney, void* pData );   // 募捐金钱输入回调

protected:
	void ResetMembers();
	void SetMoney( DWORD dwMoney );

private:
	DWORD       m_dwMoney;
};
extern CUI_ID_FRAME_GuildResource s_CUI_ID_FRAME_GuildResource;
