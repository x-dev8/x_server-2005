/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\功能菜单\ExMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_ExMenu
#define ID_FRAME_ExMenu		"ID_FRAME_ExMenu"
#endif  ID_FRAME_ExMenu
#ifndef ID_BUTTON_ActivityDay
#define ID_BUTTON_ActivityDay		"ID_BUTTON_ActivityDay"
#endif  ID_BUTTON_ActivityDay
#ifndef ID_BUTTON_Taxis
#define ID_BUTTON_Taxis		"ID_BUTTON_Taxis"
#endif  ID_BUTTON_Taxis
#ifndef ID_BUTTON_ChangeEquip
#define ID_BUTTON_ChangeEquip		"ID_BUTTON_ChangeEquip"
#endif  ID_BUTTON_ChangeEquip
#ifndef ID_BUTTON_Action
#define ID_BUTTON_Action		"ID_BUTTON_Action"
#endif  ID_BUTTON_Action
#ifndef ID_BUTTON_Protect
#define ID_BUTTON_Protect		"ID_BUTTON_Protect"
#endif  ID_BUTTON_Protect
#ifndef ID_BUTTON_Shop
#define ID_BUTTON_Shop		"ID_BUTTON_Shop"
#endif  ID_BUTTON_Shop
#ifndef ID_BUTTON_Card
#define ID_BUTTON_Card		"ID_BUTTON_Card"
#endif  ID_BUTTON_Card

#ifndef ID_TEXT_Shop
#define ID_TEXT_Shop		"ID_TEXT_Shop"
#endif  ID_TEXT_Shop
#ifndef ID_TEXT_Action
#define ID_TEXT_Action		"ID_TEXT_Action"
#endif  ID_TEXT_Action
#ifndef ID_TEXT_ActivityDay1
#define ID_TEXT_ActivityDay1		"ID_TEXT_ActivityDay1"
#endif  ID_TEXT_ActivityDay1
#ifndef ID_TEXT_Taxis
#define ID_TEXT_Taxis		"ID_TEXT_Taxis"
#endif  ID_TEXT_Taxis
#ifndef ID_TEXT_Protect
#define ID_TEXT_Protect		"ID_TEXT_Protect"
#endif  ID_TEXT_Protect
#ifndef ID_TEXT_Card
#define ID_TEXT_Card		"ID_TEXT_Card"
#endif  ID_TEXT_Card
#ifndef ID_BUTTON_Achievement 
#define ID_BUTTON_Achievement  "ID_BUTTON_Achievement"
#endif  ID_BUTTON_Achievement
#ifndef ID_TEXT_Achievement
#define ID_TEXT_Achievement   "ID_TEXT_Achievement"
#endif	ID_TEXT_Achievement




class CUI_ID_FRAME_ExMenu:public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_ExMenu();
private:
	 ControlFrame*	m_pID_FRAME_ExMenu;
	 ControlButton*	m_pID_BUTTON_ActivityDay;
	 ControlButton*	m_pID_BUTTON_Taxis;
	 ControlButton*	m_pID_BUTTON_ChangeEquip;
	 ControlButton*	m_pID_BUTTON_Action;
	 ControlButton*	m_pID_BUTTON_Protect;
	 ControlButton*	m_pID_BUTTON_Shop;
	 ControlButton*	m_pID_BUTTON_Card;
	 ControlButton* m_pID_BUTTON_Achievement;
	
	 ControlText*	m_pID_TEXT_Achievement;
	 ControlText*	m_pID_TEXT_Shop;
	 ControlText*	m_pID_TEXT_Action;
	 ControlText*	m_pID_TEXT_ActivityDay1;
	 ControlText*	m_pID_TEXT_Taxis;
	 ControlText*	m_pID_TEXT_Protect;
	 ControlText*	m_pID_TEXT_Card;


public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_ActivityDayOnButtonClick( ControlObject* pSender );
	
	bool ID_BUTTON_TaxisOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ChangeEquipOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ActionOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ProtectOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ShopOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CardOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AchievementOnButtonClick( ControlObject* pSender);

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	void RefreshHotKey();

	 ControlButton*	GetpIDButtonTaxis();
	 ControlButton*	GetpIDButtonProtect();
	 ControlButton*	GetpIDButtonShop();
     ControlButton*	GetpIDButtonChangeEquip();
	 ControlButton*	GetpIDButtonAction();
	 ControlButton* GetpIDButtonAchievement();
	

	 void SetTaxisPressPic();
	 void SetProtectPressPic();
	 void SetShopPressPic();
	 void SetChangeEquipPressPic();
	 void SetActionPressPic();
	 void SetActivityPressPic();
	 void SetActivityNormalPic();
	 void SetAchievementPressPic();

	

	 void SetTaxisNormalPic();
	 void SetachievementNormalPic();
	 void SetProtectNormalPic();
	 void SetShopNormalPic();
	 void SetChangeEquipNormalPic();
	 void SetActionNormalPic();
	 void SetAchievementNormalPic();
	 

	 void SetCartState(bool bValue);
public:
	void SetShopHighLight();
	void SetActionHighLight();
	void SetActivityDay1HighLight();
	void SetAchievementHighLight();
	
	void SetTaxisHighLight();
	void SetProtectHighLight();
	void SetCardHighLight();
};
extern CUI_ID_FRAME_ExMenu s_CUI_ID_FRAME_ExMenu;
