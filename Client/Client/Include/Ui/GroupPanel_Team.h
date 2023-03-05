/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\GroupPanel_Team.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GroupPanel_Team
#define ID_FRAME_GroupPanel_Team		"ID_FRAME_GroupPanel_Team"
#endif  ID_FRAME_GroupPanel_Team
#ifndef ID_LIST_Player
#define ID_LIST_Player		"ID_LIST_Player"
#endif  ID_LIST_Player
#ifndef ID_BUTTON_Jiaru
#define ID_BUTTON_Jiaru		"ID_BUTTON_Jiaru"
#endif  ID_BUTTON_Jiaru
#ifndef ID_BUTTON_Tuichu
#define ID_BUTTON_Tuichu		"ID_BUTTON_Tuichu"
#endif  ID_BUTTON_Tuichu
#ifndef ID_LIST_TeamPlayer
#define ID_LIST_TeamPlayer		"ID_LIST_TeamPlayer"
#endif  ID_LIST_TeamPlayer
#ifndef ID_TEXT_TeamName
#define ID_TEXT_TeamName		"ID_TEXT_TeamName"
#endif  ID_TEXT_TeamName
#ifndef ID_TEXT_Leader
#define ID_TEXT_Leader		"ID_TEXT_Leader"
#endif  ID_TEXT_Leader
#ifndef ID_TEXT_LeaderLvl
#define ID_TEXT_LeaderLvl		"ID_TEXT_LeaderLvl"
#endif  ID_TEXT_LeaderLvl
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
#ifndef ID_TEXT_TeamNum
#define ID_TEXT_TeamNum		"ID_TEXT_TeamNum"
#endif  ID_TEXT_TeamNum

#include "UiBase.h"
class CUI_ID_FRAME_GroupPanel_Team :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_GroupPanel_Team();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_PlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_JiaruOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TuichuOnButtonClick( ControlObject* pSender );
	void ID_LIST_TeamPlayerOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

private:
    ControlFrame*	m_pID_FRAME_GroupPanel_Team;
    ControlList*	m_pID_LIST_Player;
    ControlButton*	m_pID_BUTTON_Jiaru;
    ControlButton*	m_pID_BUTTON_Tuichu;
    ControlList*	m_pID_LIST_TeamPlayer;
    ControlText*	m_pID_TEXT_TeamName;
    ControlText*	m_pID_TEXT_Leader;
    ControlText*	m_pID_TEXT_LeaderLvl;
    ControlPicture*	m_pID_PICTURE_Henxian;
    ControlPicture*	m_pID_PICTURE_Henxian2;
    ControlText*	m_pID_TEXT_TeamMate;
    ControlText*	m_pID_TEXT_TeamMateLvl;
    ControlText*	m_pID_TEXT_TeamMateJob;
    ControlText*	m_pID_TEXT_TeamNum;
};
extern CUI_ID_FRAME_GroupPanel_Team s_CUI_ID_FRAME_GroupPanel_Team;
