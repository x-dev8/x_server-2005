/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\刘小兵\SearchTeacher.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MsgBase.h"
#include "RelationDefine.h"

#ifndef ID_FRAME_SearchTeacher
#define ID_FRAME_SearchTeacher		"ID_FRAME_SearchTeacher"
#endif  ID_FRAME_SearchTeacher
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Seek
#define ID_BUTTON_Seek		"ID_BUTTON_Seek"
#endif  ID_BUTTON_Seek
#ifndef ID_BUTTON_Apply
#define ID_BUTTON_Apply		"ID_BUTTON_Apply"
#endif  ID_BUTTON_Apply
#ifndef ID_LIST_Name
#define ID_LIST_Name		"ID_LIST_Name"
#endif  ID_LIST_Name
#ifndef ID_LIST_Guild
#define ID_LIST_Guild		"ID_LIST_Guild"
#endif  ID_LIST_Guild
#ifndef ID_LIST_Level
#define ID_LIST_Level		"ID_LIST_Level"
#endif  ID_LIST_Level
#ifndef ID_LIST_Select
#define ID_LIST_Select		"ID_LIST_Select"
#endif  ID_LIST_Select
#ifndef ID_BUTTON_PageUp
#define ID_BUTTON_PageUp		"ID_BUTTON_PageUp"
#endif  ID_BUTTON_PageUp
#ifndef ID_BUTTON_PageDown
#define ID_BUTTON_PageDown		"ID_BUTTON_PageDown"
#endif  ID_BUTTON_PageDown
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Recruit
#define ID_BUTTON_Recruit		"ID_BUTTON_Recruit"
#endif  ID_BUTTON_Recruit
#ifndef ID_BUTTON_Delete
#define ID_BUTTON_Delete		"ID_BUTTON_Delete"
#endif  ID_BUTTON_Delete

#include "UiBase.h"
class CUI_ID_FRAME_SearchTeacher: public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_SearchTeacher();

private:
	 ControlFrame*	m_pID_FRAME_SearchTeacher;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_Seek;
	 ControlButton*	m_pID_BUTTON_Apply;
	 ControlList*	m_pID_LIST_Name;
	 ControlList*	m_pID_LIST_Guild;
	 ControlList*	m_pID_LIST_Level;
	 ControlList*	m_pID_LIST_Select;
	 ControlButton*	m_pID_BUTTON_PageUp;
	 ControlButton*	m_pID_BUTTON_PageDown;
	 ControlText*	m_pID_TEXT_Page;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_Recruit;
	 ControlButton*	m_pID_BUTTON_Delete;

	// Frame
public:
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SeekOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ApplyOnButtonClick( ControlObject* pSender );
	void ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_LevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_SelectOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RecruitOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI 
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
//------------------------------------------------------------------------------------------------------
private:
	std::vector<RelationAttribute> m_vctRelationAttribute;
	int m_nPlayerNumber;
	int m_nCurrentPageIndex;

private:
	void ClearList();  
	void ShowList();
	void ShowAttributeList();
	void RefreshButtonState();
	void ResetState();
	void ShowMessageSending();
	void ShowOperateOnMyself();

public:
	void ShowMyStudentList();
	void OnShowSearchResult(Msg * pMsg_);
};
extern CUI_ID_FRAME_SearchTeacher s_CUI_ID_FRAME_SearchTeacher;
