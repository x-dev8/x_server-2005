/********************************************************************
Created by UIEditor.exe
FileName: E:\Work\Run\Client\UI\Task_Track.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_TRACK
#define ID_FRAME_TRACK		"ID_FRAME_TRACK"
#endif  ID_FRAME_TRACK
#ifndef ID_PICTURE_Drag
#define ID_PICTURE_Drag		"ID_PICTURE_Drag"
#endif  ID_PICTURE_Drag
#ifndef ID_LIST_TRACK
#define ID_LIST_TRACK		"ID_LIST_TRACK"
#endif  ID_LIST_TRACK
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_LIST_Finish
#define ID_LIST_Finish		"ID_LIST_Finish"
#endif  ID_LIST_Finish
#ifndef ID_LIST_Activity
#define ID_LIST_Activity		"ID_LIST_Activity"
#endif  ID_LIST_Activity
#ifndef ID_LIST_ActivityState
#define ID_LIST_ActivityState		"ID_LIST_ActivityState"
#endif  ID_LIST_ActivityState
#ifndef ID_LIST_Player
#define ID_LIST_Player		"ID_LIST_Player"
#endif  ID_LIST_Player
#ifndef ID_LIST_PlayerState
#define ID_LIST_PlayerState		"ID_LIST_PlayerState"
#endif  ID_LIST_PlayerState
#ifndef ID_LIST_PlayerName
#define ID_LIST_PlayerName		"ID_LIST_PlayerName"
#endif  ID_LIST_PlayerName
#ifndef ID_CHECKBOX_Player
#define ID_CHECKBOX_Player		"ID_CHECKBOX_Player"
#endif  ID_CHECKBOX_Player
#ifndef ID_CHECKBOX_Activity
#define ID_CHECKBOX_Activity		"ID_CHECKBOX_Activity"
#endif  ID_CHECKBOX_Activity
#ifndef ID_CHECKBOX_Task
#define ID_CHECKBOX_Task		"ID_CHECKBOX_Task"
#endif  ID_CHECKBOX_Task
#ifndef ID_TEXT_Activity
#define ID_TEXT_Activity		"ID_TEXT_Activity"
#endif  ID_TEXT_Activity
#ifndef ID_CHECKBOX_NPC
#define ID_CHECKBOX_NPC		"ID_CHECKBOX_NPC"
#endif  ID_CHECKBOX_NPC
#ifndef ID_LIST_NPC
#define ID_LIST_NPC		"ID_LIST_NPC"
#endif  ID_LIST_NPC
#ifndef ID_LIST_NPCFunction
#define ID_LIST_NPCFunction		"ID_LIST_NPCFunction"
#endif  ID_LIST_NPCFunction
#ifndef ID_LIST_NPCName
#define ID_LIST_NPCName		"ID_LIST_NPCName"
#endif  ID_LIST_NPCName
#ifndef ID_BUTTON_Plus
#define ID_BUTTON_Plus		"ID_BUTTON_Plus"
#endif  ID_BUTTON_Plus
#ifndef ID_BUTTON_Sub
#define ID_BUTTON_Sub		"ID_BUTTON_Sub"
#endif  ID_BUTTON_Sub
#ifndef ID_BUTTON_AvailableTask
#define ID_BUTTON_AvailableTask		"ID_BUTTON_AvailableTask"
#endif  ID_BUTTON_AvailableTask

#include "UiBase.h"
class CUI_ID_FRAME_TRACK :public CUIBase
{
private:
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_TRACK;
	ControlPicture*	m_pID_PICTURE_Drag;
	ControlList*	m_pID_LIST_TRACK;
	ControlList*	m_pID_LIST_Finish;
	ControlCheckBox*	m_pID_CHECKBOX_Task;
	ControlGroup m_finishPicGroup;
	ControlGroup m_taskTrackGroup;
	ControlGroup m_eventTrackGroup;
	ControlGroup m_playerGroup;
	ControlGroup m_NpcGroup;
	ControlTabGroup m_tabGroup;
    ControlButton*	m_pID_BUTTON_Plus;
    ControlButton*	m_pID_BUTTON_Sub;
	ControlButton*	m_pID_BUTTON_AvailableTask;

public:	
	CUI_ID_FRAME_TRACK();
	bool OnFrameRun();
	bool OnFrameRender();
    bool ID_BUTTON_PlusOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_SubOnButtonClick( ControlObject* pSender );
	void ID_LIST_TRACKOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	virtual bool IsHoldInMemory() const { return true; }
	bool ID_BUTTON_AvailableTaskOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	        // 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	ControlList* GetLIST_TRACK();
	ControlList* GetLIST_Finish();
	ControlGroup& GetfinishPicGroup() { return m_finishPicGroup; }
	void RefreshTask();
    bool IsMinisized();

private:
	void RefreshNpcFunction();
	void ShowUIs(bool bVisible);
 	static void Npc_HyberClick( ControlObject* pSender, const std::string& content ,int nId );
	static void Task_CollapseCallBackFun(  ControlObject* pSender, ControlList::S_List* pItem );
	static bool MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed);

	int		m_nLastNpcMap;
    bool    m_bMinisize;            // 杨凯需求
};
extern CUI_ID_FRAME_TRACK s_CUI_ID_FRAME_TRACK;
