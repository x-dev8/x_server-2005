/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\TimeString.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_TimeShow
#define ID_FRAME_TimeShow		"ID_FRAME_TimeShow"
#endif  ID_FRAME_TimeShow
#ifndef ID_LIST_Member
#define ID_LIST_Member		"ID_LIST_Member"
#endif  ID_LIST_Member
#ifndef ID_LIST_String
#define ID_LIST_String		"ID_LIST_String"
#endif  ID_LIST_String
#ifndef ID_LIST_Time
#define ID_LIST_Time		"ID_LIST_Time"
#endif  ID_LIST_Time

class CUI_ID_FRAME_TimeShow : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_TimeShow();
	 ControlFrame*	m_pID_FRAME_TimeShow;
	 ControlList*	m_pID_LIST_Member;
	 ControlList*	m_pID_LIST_String;
	 ControlList*	m_pID_LIST_Time;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_MemberOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_StringOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_TimeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();

	void RefreshTime();

private:
	DWORD m_lastTime;
};
extern CUI_ID_FRAME_TimeShow s_CUI_ID_FRAME_TimeShow;
