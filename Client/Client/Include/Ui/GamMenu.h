/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Turbo\MEUI\3.14-3.19\功能菜单\GamMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_GamMenu
#define ID_FRAME_GamMenu		"ID_FRAME_GamMenu"
#endif  ID_FRAME_GamMenu
#ifndef ID_BUTTON_ChangeEquip
#define ID_BUTTON_ChangeEquip		"ID_BUTTON_ChangeEquip"
#endif  ID_BUTTON_ChangeEquip
#ifndef ID_BUTTON_Family
#define ID_BUTTON_Family		"ID_BUTTON_Family"
#endif  ID_BUTTON_Family
#ifndef ID_BUTTON_Guild
#define ID_BUTTON_Guild		"ID_BUTTON_Guild"
#endif  ID_BUTTON_Guild
#ifndef ID_BUTTON_Fiend
#define ID_BUTTON_Fiend		"ID_BUTTON_Fiend"
#endif  ID_BUTTON_Fiend
#ifndef ID_BUTTON_ZuDui
#define ID_BUTTON_ZuDui		"ID_BUTTON_ZuDui"
#endif  ID_BUTTON_ZuDui
#ifndef ID_TEXT_Family
#define ID_TEXT_Family		"ID_TEXT_Family"
#endif  ID_TEXT_Family
#ifndef ID_TEXT_Guild
#define ID_TEXT_Guild		"ID_TEXT_Guild"
#endif  ID_TEXT_Guild
#ifndef ID_TEXT_Fiend
#define ID_TEXT_Fiend		"ID_TEXT_Fiend"
#endif  ID_TEXT_Fiend
#ifndef ID_TEXT_ZuDui
#define ID_TEXT_ZuDui		"ID_TEXT_ZuDui"
#endif  ID_TEXT_ZuDui
#ifndef ID_TEXT_Country 
#define ID_TEXT_Country     "ID_TEXT_Country"
#endif  ID_TEXT_Country
#ifndef ID_BUTTON_Country
#define ID_BUTTON_Country   "ID_BUTTON_Country"
#endif  ID_BUTTON_Country	

class CUI_ID_FRAME_GamMenu:public CUIBase
{
	// Member
private:	

	 ControlFrame*	m_pID_FRAME_GamMenu;
	 ControlButton*	m_pID_BUTTON_ChangeEquip;
	 ControlButton*	m_pID_BUTTON_Family;
	 ControlButton*	m_pID_BUTTON_Guild;
	 ControlButton*	m_pID_BUTTON_Fiend;
	 ControlButton*	m_pID_BUTTON_ZuDui;
	 ControlButton* m_pID_BUTTON_Country;
	 ControlText*	m_pID_TEXT_Family;
	 ControlText*	m_pID_TEXT_Guild;
	 ControlText*	m_pID_TEXT_Fiend;
	 ControlText*	m_pID_TEXT_ZuDui;
	 ControlText*   m_pID_TEXT_Country;

public:	
	// Frame
	CUI_ID_FRAME_GamMenu();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_ChangeEquipOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FamilyOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GuildOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FiendOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ZuDuiOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CountryOnButtonClick( ControlObject* pSender);

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	void RefreshHotKey();
	void SetFamilyHighLight();
	void SetGuildHighLight();
	void SetFriendHighLight();
	void SetZuDuiHighLight();
	void SetCountryHighLight();
public:
	void SetFamilyBtnState(bool bValue);
	void SetGuildBtnState(bool bValue);
	void SetFriendBtnState(bool bValue);
	void SetTeamBtnState(bool bValue);
	void SetCountryBtnState(bool bValue);
};
extern CUI_ID_FRAME_GamMenu s_CUI_ID_FRAME_GamMenu;
