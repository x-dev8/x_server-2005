/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liheng.duan\桌面\ExitTip.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "EventTimeTable.h"

#ifndef ID_FRAME_ExitTip
#define ID_FRAME_ExitTip		"ID_FRAME_ExitTip"
#endif  ID_FRAME_ExitTip
#ifndef ID_BUTTON_Back
#define ID_BUTTON_Back		"ID_BUTTON_Back"
#endif  ID_BUTTON_Back
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Exit
#define ID_BUTTON_Exit		"ID_BUTTON_Exit"
#endif  ID_BUTTON_Exit
#ifndef ID_LIST_Star
#define ID_LIST_Star		"ID_LIST_Star"
#endif  ID_LIST_Star
#ifndef ID_LIST_FunctionLevel
#define ID_LIST_FunctionLevel		"ID_LIST_FunctionLevel"
#endif  ID_LIST_FunctionLevel
#ifndef ID_LIST_Quest
#define ID_LIST_Quest		"ID_LIST_Quest"
#endif  ID_LIST_Quest
#ifndef ID_LIST_NewFunction
#define ID_LIST_NewFunction		"ID_LIST_NewFunction"
#endif  ID_LIST_NewFunction

#ifndef ID_LIST_More
#define ID_LIST_More			"ID_LIST_More"
#endif  ID_LIST_More

#include "UiBase.h"
#include <map>
#include <string>

class CUI_ID_FRAME_ExitTip : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_ExitTip();
	ControlFrame*		m_pID_FRAME_ExitTip;
	ControlButton*		m_pID_BUTTON_Back;
	ControlButton*		m_pID_BUTTON_CLOSE;
	ControlButton*		m_pID_BUTTON_Exit;
	ControlList*		m_pID_LIST_Star;
	ControlList*		m_pID_LIST_Quest;
	ControlList*		m_pID_LIST_More;

	//ControlList*		m_pID_LIST_FunctionLevel;
	//ControlList*		m_pID_LIST_NewFunction;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_BackOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ExitOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_StarOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_StarOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_LIST_FunctionLevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_QuestOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_NewFunctionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	void ID_LIST_StarOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	bool _LoadUI();										// 载入UI
	bool DoControlConnect();							// 关连控件
	bool _UnLoadUI();									// 卸载UI
	bool _IsVisable();									// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视

	// 每次打开时要刷次list
	void RefreshInfo();

	static void ChangeCol( void* data, DWORD* col );

	static void ClickMore( void* data );

private:
	// 设置子list
	void SetChildList( ControlList* pLIST );
	// 判断是否可以播入面板上方的list
	bool IsPushTopList( Event content );
	// 判断是否可以播入面板下方的list
	bool IsPushBottomList( Event content );

	void InsertMoreList( int eventIdx );

	static bool Exit_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

	static void ID_LIST_LDBClick( ControlObject* pSender, ControlList::S_List* pItem );

	static void ID_LISTMore_LBClick( ControlObject* pSender, ControlList::S_List* pItem );


	static bool SortByStar(Event* lhs, Event* rhs);
public:
	void SetOpenUi(bool bValue){m_bByOpenUi = bValue;}
	bool IsOpenUi(){return m_bByOpenUi;}
private:
	bool m_bByOpenUi;
private:

	typedef std::map<std::string, int> NoteNameSet_t;
	typedef NoteNameSet_t::const_iterator NoteNameIt_t;

	NoteNameSet_t mAllNoteName;			// 为防止插入的有名字相同的任务

};
extern CUI_ID_FRAME_ExitTip s_CUI_ID_FRAME_ExitTip;
