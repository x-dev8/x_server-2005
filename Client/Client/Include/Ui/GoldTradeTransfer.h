/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\chixin.ni\桌面\金锭UI\GoldTradeTransfer.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GoldTradeDeposit
#define ID_FRAME_GoldTradeDeposit		"ID_FRAME_GoldTradeDeposit"
#endif  ID_FRAME_GoldTradeDeposit
#ifndef ID_TEXT_DepositMoney
#define ID_TEXT_DepositMoney		"ID_TEXT_DepositMoney"
#endif  ID_TEXT_DepositMoney
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_MaxGold
#define ID_BUTTON_MaxGold		"ID_BUTTON_MaxGold"
#endif  ID_BUTTON_MaxGold
#ifndef ID_TEXT_DepositGold
#define ID_TEXT_DepositGold		"ID_TEXT_DepositGold"
#endif  ID_TEXT_DepositGold
#ifndef ID_PICTURE_Jin
#define ID_PICTURE_Jin		"ID_PICTURE_Jin"
#endif  ID_PICTURE_Jin
#ifndef ID_PICTURE_Ying
#define ID_PICTURE_Ying		"ID_PICTURE_Ying"
#endif  ID_PICTURE_Ying
#ifndef ID_PICTURE_Tong
#define ID_PICTURE_Tong		"ID_PICTURE_Tong"
#endif  ID_PICTURE_Tong
#ifndef ID_EDIT_Jin
#define ID_EDIT_Jin		"ID_EDIT_Jin"
#endif  ID_EDIT_Jin
#ifndef ID_EDIT_Yin
#define ID_EDIT_Yin		"ID_EDIT_Yin"
#endif  ID_EDIT_Yin
#ifndef ID_EDIT_Tong
#define ID_EDIT_Tong		"ID_EDIT_Tong"
#endif  ID_EDIT_Tong
#ifndef ID_BUTTON_MaxMoney
#define ID_BUTTON_MaxMoney		"ID_BUTTON_MaxMoney"
#endif  ID_BUTTON_MaxMoney
#ifndef ID_EDIT_Gold
#define ID_EDIT_Gold		"ID_EDIT_Gold"
#endif  ID_EDIT_Gold
#ifndef ID_PICTURE_Gold
#define ID_PICTURE_Gold		"ID_PICTURE_Gold"
#endif  ID_PICTURE_Gold
#ifndef ID_BUTTON_Cancle
#define ID_BUTTON_Cancle		"ID_BUTTON_Cancle"
#endif  ID_BUTTON_Cancle
#ifndef ID_TEXT_ReceiveGold
#define ID_TEXT_ReceiveGold		"ID_TEXT_ReceiveGold"
#endif  ID_TEXT_ReceiveGold
#ifndef ID_TEXT_ReceiveMoney
#define ID_TEXT_ReceiveMoney		"ID_TEXT_ReceiveMoney"
#endif  ID_TEXT_ReceiveMoney
#ifndef ID_PICTURE_DepositGold
#define ID_PICTURE_DepositGold		"ID_PICTURE_DepositGold"
#endif	ID_PICTURE_DepositGold
#ifndef ID_PICTURE_ReceiveGold
#define ID_PICTURE_ReceiveGold		"ID_PICTURE_ReceiveGold"
#endif	ID_PICTURE_ReceiveGold
#ifndef ID_PICTURE_DepositMoney
#define ID_PICTURE_DepositMoney		"ID_PICTURE_DepositMoney"
#endif	ID_PICTURE_DepositMoney
#ifndef ID_PICTURE_ReceiveMoney
#define ID_PICTURE_ReceiveMoney		"ID_PICTURE_ReceiveMoney"
#endif	ID_PICTURE_ReceiveMoney

#include "UIBase.h"

class CUI_ID_FRAME_GoldTradeDeposit : public CUIBase
{
	// Member
private:
	 ControlFrame*	m_pID_FRAME_GoldTradeDeposit;
	 ControlText*	m_pID_TEXT_DepositMoney;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_MaxGold;
	 ControlText*	m_pID_TEXT_DepositGold;
	 ControlPicture*	m_pID_PICTURE_Jin;
	 ControlPicture*	m_pID_PICTURE_Ying;
	 ControlPicture*	m_pID_PICTURE_Tong;
	 ControlEdit*	m_pID_EDIT_Jin;
	 ControlEdit*	m_pID_EDIT_Yin;
	 ControlEdit*	m_pID_EDIT_Tong;
	 ControlButton*	m_pID_BUTTON_MaxMoney;
	 ControlEdit*	m_pID_EDIT_Gold;
	 ControlPicture*	m_pID_PICTURE_Gold;
	 ControlButton*	m_pID_BUTTON_Cancle;
	 ControlText*	m_pID_TEXT_ReceiveGold;
	 ControlText*	m_pID_TEXT_ReceiveMoney;
	 ControlPicture*	m_pID_PICTURE_DepositGold;
	 ControlPicture*	m_pID_PICTURE_ReceiveGold;
	 ControlPicture*	m_pID_PICTURE_DepositMoney;
	 ControlPicture*	m_pID_PICTURE_ReceiveMoney;

public:	
	CUI_ID_FRAME_GoldTradeDeposit();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MaxGoldOnButtonClick( ControlObject* pSender );
	void ID_EDIT_JinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_YinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_TongOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_MaxMoneyOnButtonClick( ControlObject* pSender );
	void ID_EDIT_GoldOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_CancleOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void SetPop();
	void SetPush();
	static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
	void SetCloseUi(bool bValue);
private:

	void Refresh();

	bool m_IsPop;

	bool m_bCloseUi;
};
extern CUI_ID_FRAME_GoldTradeDeposit s_CUI_ID_FRAME_GoldTradeDeposit;
