/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\RightMainMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_RightMainMenu
#define ID_FRAME_RightMainMenu		"ID_FRAME_RightMainMenu"
#endif  ID_FRAME_RightMainMenu
#ifndef ID_BUTTON_Hide
#define ID_BUTTON_Hide		"ID_BUTTON_Hide"
#endif  ID_BUTTON_Hide
#ifndef ID_BUTTON_Appear
#define ID_BUTTON_Appear		"ID_BUTTON_Appear"
#endif  ID_BUTTON_Appear
#ifndef ID_BUTTON_Shop
#define ID_BUTTON_Shop		"ID_BUTTON_Shop"
#endif  ID_BUTTON_Shop
#ifndef ID_BUTTON_ActivityList
#define ID_BUTTON_ActivityList		"ID_BUTTON_ActivityList"
#endif  ID_BUTTON_ActivityList
#ifndef ID_BUTTON_Taxis
#define ID_BUTTON_Taxis		"ID_BUTTON_Taxis"
#endif  ID_BUTTON_Taxis
#ifndef ID_BUTTON_Title
#define ID_BUTTON_Title		"ID_BUTTON_Title"
#endif  ID_BUTTON_Title
#ifndef ID_BUTTON_Riches
#define ID_BUTTON_Riches		"ID_BUTTON_Riches"
#endif  ID_BUTTON_Riches

#include "UiBase.h"
class CUI_ID_FRAME_RightMainMenu :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_RightMainMenu();
private:
	ControlFrame*	m_pID_FRAME_RightMainMenu;
	ControlButton*	m_pID_BUTTON_Hide;
	ControlButton*	m_pID_BUTTON_Appear;
	ControlButton*	m_pID_BUTTON_Shop;
	ControlButton*	m_pID_BUTTON_ActivityList;
	ControlButton*	m_pID_BUTTON_Taxis;
	ControlButton*	m_pID_BUTTON_Title;
	ControlButton*	m_pID_BUTTON_Riches;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HideOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AppearOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ShopOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ActivityListOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TaxisOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TitleOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RichesOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

};
extern CUI_ID_FRAME_RightMainMenu s_CUI_ID_FRAME_RightMainMenu;
