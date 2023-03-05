/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\GroupPanel_NearPlayer.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GroupPanel_NearPlayer
#define ID_FRAME_GroupPanel_NearPlayer		"ID_FRAME_GroupPanel_NearPlayer"
#endif  ID_FRAME_GroupPanel_NearPlayer
#ifndef ID_LIST_Player
#define ID_LIST_Player		"ID_LIST_Player"
#endif  ID_LIST_Player
#ifndef ID_LIST_PlayerTitle
#define ID_LIST_PlayerTitle		"ID_LIST_PlayerTitle"
#endif  ID_LIST_PlayerTitle
#ifndef ID_LIST_TeamTitle
#define ID_LIST_TeamTitle		"ID_LIST_TeamTitle"
#endif  ID_LIST_TeamTitle
#ifndef ID_BUTTON_Yaoqing
#define ID_BUTTON_Yaoqing		"ID_BUTTON_Yaoqing"
#endif  ID_BUTTON_Yaoqing
#ifndef ID_BUTTON_Duizhang
#define ID_BUTTON_Duizhang		"ID_BUTTON_Duizhang"
#endif  ID_BUTTON_Duizhang
#ifndef ID_BUTTON_TiChu
#define ID_BUTTON_TiChu		"ID_BUTTON_TiChu"
#endif  ID_BUTTON_TiChu
#ifndef ID_BUTTON_Tuichu
#define ID_BUTTON_Tuichu		"ID_BUTTON_Tuichu"
#endif  ID_BUTTON_Tuichu
#ifndef ID_LIST_TeamPlayer
#define ID_LIST_TeamPlayer		"ID_LIST_TeamPlayer"
#endif  ID_LIST_TeamPlayer
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
#ifndef ID_TEXT_TeamMate
#define ID_TEXT_TeamMate		"ID_TEXT_TeamMate"
#endif  ID_TEXT_TeamMate
#ifndef ID_TEXT_TeamMateLvl
#define ID_TEXT_TeamMateLvl		"ID_TEXT_TeamMateLvl"
#endif  ID_TEXT_TeamMateLvl
#ifndef ID_TEXT_TeamMateJob
#define ID_TEXT_TeamMateJob		"ID_TEXT_TeamMateJob"
#endif  ID_TEXT_TeamMateJob

#include "UiBase.h"
class CUI_ID_FRAME_GroupPanel_NearPlayer :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_GroupPanel_NearPlayer();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_PlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_YaoqingOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DuizhangOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TiChuOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TuichuOnButtonClick( ControlObject* pSender );
	void ID_LIST_TeamPlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void Refresh();
private:
    ControlFrame*	m_pID_FRAME_GroupPanel_NearPlayer;
    ControlList*	m_pID_LIST_Player;
    ControlList*    m_pID_LIST_PlayerTitle;
    ControlList*	m_pID_LIST_TeamTitle;
    ControlButton*	m_pID_BUTTON_Yaoqing;
    ControlButton*	m_pID_BUTTON_Duizhang;
    ControlButton*	m_pID_BUTTON_TiChu;
    ControlButton*	m_pID_BUTTON_Tuichu;
    ControlList*	m_pID_LIST_TeamPlayer;
    ControlText*	m_pID_TEXT_PlayerName;
    ControlText*	m_pID_TEXT_PlayerJob;
    ControlText*	m_pID_TEXT_PlayerLvl;
    ControlPicture*	m_pID_PICTURE_Henxian;
    ControlPicture*	m_pID_PICTURE_Henxian2;
    ControlText*	m_pID_TEXT_TeamMate;
    ControlText*	m_pID_TEXT_TeamMateLvl;
    ControlText*	m_pID_TEXT_TeamMateJob;
};
extern CUI_ID_FRAME_GroupPanel_NearPlayer s_CUI_ID_FRAME_GroupPanel_NearPlayer;
