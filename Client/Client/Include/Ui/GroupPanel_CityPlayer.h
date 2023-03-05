/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\huwen\桌面\GroupPanel_CityPlayer.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GroupPanel_CityPlayer
#define ID_FRAME_GroupPanel_CityPlayer		"ID_FRAME_GroupPanel_CityPlayer"
#endif  ID_FRAME_GroupPanel_CityPlayer
#ifndef ID_PICTURE_List
#define ID_PICTURE_List		"ID_PICTURE_List"
#endif  ID_PICTURE_List
#ifndef ID_BUTTON_AddFriend
#define ID_BUTTON_AddFriend		"ID_BUTTON_AddFriend"
#endif  ID_BUTTON_AddFriend
#ifndef ID_BUTTON_Miyu
#define ID_BUTTON_Miyu		"ID_BUTTON_Miyu"
#endif  ID_BUTTON_Miyu
#ifndef ID_BUTTON_Yaoqing
#define ID_BUTTON_Yaoqing		"ID_BUTTON_Yaoqing"
#endif  ID_BUTTON_Yaoqing
#ifndef ID_LIST_Player
#define ID_LIST_Player		"ID_LIST_Player"
#endif  ID_LIST_Player
#ifndef ID_TEXT_PlayerName
#define ID_TEXT_PlayerName		"ID_TEXT_PlayerName"
#endif  ID_TEXT_PlayerName
#ifndef ID_TEXT_PlayerJob
#define ID_TEXT_PlayerJob		"ID_TEXT_PlayerJob"
#endif  ID_TEXT_PlayerJob
#ifndef ID_TEXT_PlayerLvl
#define ID_TEXT_PlayerLvl		"ID_TEXT_PlayerLvl"
#endif  ID_TEXT_PlayerLvl
#ifndef ID_PICTURE_Henxian
#define ID_PICTURE_Henxian		"ID_PICTURE_Henxian"
#endif  ID_PICTURE_Henxian
#ifndef ID_PICTURE_Henxian2
#define ID_PICTURE_Henxian2		"ID_PICTURE_Henxian2"
#endif  ID_PICTURE_Henxian2
#ifndef ID_TEXT_Jieyi
#define ID_TEXT_Jieyi		"ID_TEXT_Jieyi"
#endif  ID_TEXT_Jieyi
#ifndef ID_TEXT_Gonghui
#define ID_TEXT_Gonghui		"ID_TEXT_Gonghui"
#endif  ID_TEXT_Gonghui
#ifndef ID_TEXT_Shenshi
#define ID_TEXT_Shenshi		"ID_TEXT_Shenshi"
#endif  ID_TEXT_Shenshi
#ifndef ID_TEXT_Diqu
#define ID_TEXT_Diqu		"ID_TEXT_Diqu"
#endif  ID_TEXT_Diqu
#ifndef ID_PICTURE_Henxian3
#define ID_PICTURE_Henxian3		"ID_PICTURE_Henxian3"
#endif  ID_PICTURE_Henxian3
#ifndef ID_PICTURE_Henxian4
#define ID_PICTURE_Henxian4		"ID_PICTURE_Henxian4"
#endif  ID_PICTURE_Henxian4
#ifndef ID_PICTURE_Henxian5
#define ID_PICTURE_Henxian5		"ID_PICTURE_Henxian5"
#endif  ID_PICTURE_Henxian5
#ifndef ID_PICTURE_Henxian6
#define ID_PICTURE_Henxian6		"ID_PICTURE_Henxian6"
#endif  ID_PICTURE_Henxian6
#ifndef ID_TEXT_Shenshi1
#define ID_TEXT_Shenshi1		"ID_TEXT_Shenshi1"
#endif  ID_TEXT_Shenshi1
#ifndef ID_COMBOBOX_Shenshi
#define ID_COMBOBOX_Shenshi		"ID_COMBOBOX_Shenshi"
#endif  ID_COMBOBOX_Shenshi
#ifndef ID_TEXT_Diqu2
#define ID_TEXT_Diqu2		"ID_TEXT_Diqu2"
#endif  ID_TEXT_Diqu2
#ifndef ID_COMBOBOX_Diqu
#define ID_COMBOBOX_Diqu		"ID_COMBOBOX_Diqu"
#endif  ID_COMBOBOX_Diqu

#include "UiBase.h"
class CUI_ID_FRAME_GroupPanel_CityPlayer :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GroupPanel_CityPlayer();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_AddFriendOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MiyuOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_YaoqingOnButtonClick( ControlObject* pSender );
	void ID_LIST_PlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_COMBOBOX_ShenshiOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_DiquOnComboBoxChange( ControlObject* pSender, const char* szData );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

private:
    ControlFrame*	m_pID_FRAME_GroupPanel_CityPlayer;
    ControlPicture*	m_pID_PICTURE_List;
    ControlButton*	m_pID_BUTTON_AddFriend;
    ControlButton*	m_pID_BUTTON_Miyu;
    ControlButton*	m_pID_BUTTON_Yaoqing;
    ControlList*	m_pID_LIST_Player;
    ControlText*	m_pID_TEXT_PlayerName;
    ControlText*	m_pID_TEXT_PlayerJob;
    ControlText*	m_pID_TEXT_PlayerLvl;
    ControlPicture*	m_pID_PICTURE_Henxian;
    ControlPicture*	m_pID_PICTURE_Henxian2;
    ControlText*	m_pID_TEXT_Jieyi;
    ControlText*	m_pID_TEXT_Gonghui;
    ControlText*	m_pID_TEXT_Shenshi;
    ControlText*	m_pID_TEXT_Diqu;
    ControlPicture*	m_pID_PICTURE_Henxian3;
    ControlPicture*	m_pID_PICTURE_Henxian4;
    ControlPicture*	m_pID_PICTURE_Henxian5;
    ControlPicture*	m_pID_PICTURE_Henxian6;
    ControlText*	m_pID_TEXT_Shenshi1;
    ControlComboBox*	m_pID_COMBOBOX_Shenshi;
    ControlText*	m_pID_TEXT_Diqu2;
    ControlComboBox*	m_pID_COMBOBOX_Diqu;
};
extern CUI_ID_FRAME_GroupPanel_CityPlayer s_CUI_ID_FRAME_GroupPanel_CityPlayer;
