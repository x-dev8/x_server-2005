/********************************************************************
	Created by UIEditor.exe
	FileName: E:\武将三国\Data\Ui\TimeLimitTask.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_TimeLimitTask
#define ID_FRAME_TimeLimitTask		"ID_FRAME_TimeLimitTask"
#endif  ID_FRAME_TimeLimitTask
#ifndef ID_BUTTON_Sub
#define ID_BUTTON_Sub		"ID_BUTTON_Sub"
#endif  ID_BUTTON_Sub
#ifndef ID_BUTTON_Plus
#define ID_BUTTON_Plus		"ID_BUTTON_Plus"
#endif  ID_BUTTON_Plus
#ifndef ID_PICTURE_TaskWall
#define ID_PICTURE_TaskWall		"ID_PICTURE_TaskWall"
#endif  ID_PICTURE_TaskWall
#ifndef ID_LIST_Task
#define ID_LIST_Task		"ID_LIST_Task"
#endif  ID_LIST_Task

class CUI_ID_FRAME_TimeLimitTask:public CUIBase 
{
	// Member
public:	
	 CUI_ID_FRAME_TimeLimitTask();
	 ControlFrame*	m_pID_FRAME_TimeLimitTask;
	 ControlButton*	m_pID_BUTTON_Sub;
	 ControlButton*	m_pID_BUTTON_Plus;
	 ControlPicture*	m_pID_PICTURE_TaskWall;
	 ControlList*	m_pID_LIST_Task;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_SubOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PlusOnButtonClick( ControlObject* pSender );
	void ID_LIST_TaskOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	static void Task_CollapseCallBackFun(  ControlObject* pSender, ControlList::S_List* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();
	void RefreshTask();
	void RefreshListData();

	bool m_bMinisize;
	bool m_bHasTask;
};
extern CUI_ID_FRAME_TimeLimitTask s_CUI_ID_FRAME_TimeLimitTask;
