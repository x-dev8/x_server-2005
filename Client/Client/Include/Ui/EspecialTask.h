/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\EspecialTask.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Me3d\Vector.h"

#ifndef ID_FRAME_EspecialTask
#define ID_FRAME_EspecialTask		"ID_FRAME_EspecialTask"
#endif  ID_FRAME_EspecialTask
#ifndef ID_PICTURE_TaskListWall
#define ID_PICTURE_TaskListWall		"ID_PICTURE_TaskListWall"
#endif  ID_PICTURE_TaskListWall
#ifndef ID_LIST_Task
#define ID_LIST_Task		"ID_LIST_Task"
#endif  ID_LIST_Task
#ifndef ID_PICTURE_TitleWall
#define ID_PICTURE_TitleWall		"ID_PICTURE_TitleWall"
#endif  ID_PICTURE_TitleWall
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_PICTURE_TaskAwardWall
#define ID_PICTURE_TaskAwardWall		"ID_PICTURE_TaskAwardWall"
#endif  ID_PICTURE_TaskAwardWall
#ifndef ID_LISTIMG_Award
#define ID_LISTIMG_Award		"ID_LISTIMG_Award"
#endif  ID_LISTIMG_Award
#ifndef ID_TEXT_ItemZ
#define ID_TEXT_ItemZ		"ID_TEXT_ItemZ"
#endif  ID_TEXT_ItemZ
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_PICTURE_TaskInfoWall
#define ID_PICTURE_TaskInfoWall		"ID_PICTURE_TaskInfoWall"
#endif  ID_PICTURE_TaskInfoWall
#ifndef ID_TEXT_TaskListZ
#define ID_TEXT_TaskListZ		"ID_TEXT_TaskListZ"
#endif  ID_TEXT_TaskListZ
#ifndef ID_TEXT_ExpZ
#define ID_TEXT_ExpZ		"ID_TEXT_ExpZ"
#endif  ID_TEXT_ExpZ
#ifndef ID_TEXT_Exp
#define ID_TEXT_Exp		"ID_TEXT_Exp"
#endif  ID_TEXT_Exp
#ifndef ID_TEXT_AwardZ
#define ID_TEXT_AwardZ		"ID_TEXT_AwardZ"
#endif  ID_TEXT_AwardZ
#ifndef ID_PICTURE_TaskStateWall
#define ID_PICTURE_TaskStateWall		"ID_PICTURE_TaskStateWall"
#endif  ID_PICTURE_TaskStateWall
#ifndef ID_LIST_TaskState
#define ID_LIST_TaskState		"ID_LIST_TaskState"
#endif  ID_LIST_TaskState
#ifndef ID_LIST_TaskInfo
#define ID_LIST_TaskInfo		"ID_LIST_TaskInfo"
#endif  ID_LIST_TaskInfo
#ifndef ID_TEXT_TaskAwardZ
#define ID_TEXT_TaskAwardZ		"ID_TEXT_TaskAwardZ"
#endif  ID_TEXT_TaskAwardZ
#ifndef ID_TEXT_TaskLvlZ
#define ID_TEXT_TaskLvlZ		"ID_TEXT_TaskLvlZ"
#endif  ID_TEXT_TaskLvlZ
#ifndef ID_TEXT_TaskLvl
#define ID_TEXT_TaskLvl		"ID_TEXT_TaskLvl"
#endif  ID_TEXT_TaskLvl
#ifndef ID_PICTURE_LeftMiddleWall
#define ID_PICTURE_LeftMiddleWall		"ID_PICTURE_LeftMiddleWall"
#endif  ID_PICTURE_LeftMiddleWall
#ifndef ID_PICTURE_RightMiddleWall
#define ID_PICTURE_RightMiddleWall		"ID_PICTURE_RightMiddleWall"
#endif  ID_PICTURE_RightMiddleWall
#ifndef ID_PICTURE_LeftWall
#define ID_PICTURE_LeftWall		"ID_PICTURE_LeftWall"
#endif  ID_PICTURE_LeftWall
#ifndef ID_PICTURE_RightWall
#define ID_PICTURE_RightWall		"ID_PICTURE_RightWall"
#endif  ID_PICTURE_RightWall
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Accept
#define ID_BUTTON_Accept		"ID_BUTTON_Accept"
#endif  ID_BUTTON_Accept
#ifndef ID_TEXT_MingWangZ
#define ID_TEXT_MingWangZ		"ID_TEXT_MingWangZ"
#endif  ID_TEXT_MingWangZ
#ifndef ID_TEXT_MingWang
#define ID_TEXT_MingWang		"ID_TEXT_MingWang"
#endif  ID_TEXT_MingWang
#ifndef ID_LISTIMG_RewardList
#define ID_LISTIMG_RewardList		"ID_LISTIMG_RewardList"
#endif  ID_LISTIMG_RewardList
#ifndef ID_PICTURE_ReitemWall
#define ID_PICTURE_ReitemWall		"ID_PICTURE_ReitemWall"
#endif  ID_PICTURE_ReitemWall
#ifndef ID_LISTIMG_ItemIcon
#define ID_LISTIMG_ItemIcon		"ID_LISTIMG_ItemIcon"
#endif  ID_LISTIMG_ItemIcon
#ifndef ID_BUTTON_Brush
#define ID_BUTTON_Brush		"ID_BUTTON_Brush"
#endif  ID_BUTTON_Brush
#ifndef ID_TEXT_ItemInfo
#define ID_TEXT_ItemInfo		"ID_TEXT_ItemInfo"
#endif  ID_TEXT_ItemInfo
#ifndef ID_TEXT_TakeNum
#define ID_TEXT_TakeNum		"ID_TEXT_TakeNum"
#endif  ID_TEXT_TakeNum
#ifndef ID_TEXT_TaskExplain
#define ID_TEXT_TaskExplain		"ID_TEXT_TaskExplain"
#endif  ID_TEXT_TaskExplain
#ifndef ID_PICTURE_Title1
#define ID_PICTURE_Title1		"ID_PICTURE_Title1"
#endif  ID_PICTURE_Title1
#ifndef ID_PICTURE_Title2
#define ID_PICTURE_Title2		"ID_PICTURE_Title2"
#endif  ID_PICTURE_Title2
#ifndef ID_TEXT_TaskInfo
#define ID_TEXT_TaskInfo		"ID_TEXT_TaskInfo"
#endif  ID_TEXT_TaskInfo
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_TEXT_MoneyZ
#define ID_TEXT_MoneyZ		"ID_TEXT_MoneyZ"
#endif  ID_TEXT_MoneyZ

#include "UiBase.h"
struct SQuest;
class CUI_ID_FRAME_EspecialTask :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_EspecialTask();
private:
	ControlFrame*	m_pID_FRAME_EspecialTask;
	ControlPicture*	m_pID_PICTURE_TaskListWall;
	ControlList*	m_pID_LIST_Task;
	ControlPicture*	m_pID_PICTURE_TitleWall;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlPicture*	m_pID_PICTURE_TaskAwardWall;
	ControlListImage*	m_pID_LISTIMG_Award;
	ControlText*	m_pID_TEXT_ItemZ;
	//ControlPicture*	m_pID_PICTURE_Title;
	ControlPicture*	m_pID_PICTURE_TaskInfoWall;
	ControlText*	m_pID_TEXT_TaskListZ;
	ControlText*	m_pID_TEXT_ExpZ;
	ControlText*	m_pID_TEXT_Exp;
	ControlText*	m_pID_TEXT_AwardZ;
	ControlPicture*	m_pID_PICTURE_TaskStateWall;
	ControlList*	m_pID_LIST_TaskState;
	ControlList*	m_pID_LIST_TaskInfo;
	ControlText*	m_pID_TEXT_TaskAwardZ;
	ControlText*	m_pID_TEXT_TaskLvlZ;
	ControlText*	m_pID_TEXT_TaskLvl;
	ControlPicture*	m_pID_PICTURE_LeftMiddleWall;
	ControlPicture*	m_pID_PICTURE_RightMiddleWall;
	ControlPicture*	m_pID_PICTURE_LeftWall;
	ControlPicture*	m_pID_PICTURE_RightWall;
	ControlButton*	m_pID_BUTTON_help;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlButton*	m_pID_BUTTON_Accept;
	ControlText*	m_pID_TEXT_MingWangZ;
	ControlText*	m_pID_TEXT_MingWang;
	ControlListImage*	m_pID_LISTIMG_RewardList;
	ControlPicture*	m_pID_PICTURE_ReitemWall;
	ControlListImage*	m_pID_LISTIMG_ItemIcon;
	ControlButton*	m_pID_BUTTON_Brush;
	ControlText*	m_pID_TEXT_ItemInfo;
	ControlText*	m_pID_TEXT_TakeNum;
	ControlText*	m_pID_TEXT_TaskExplain;
	ControlPicture*	m_pID_PICTURE_Title1;
	ControlPicture*	m_pID_PICTURE_Title2;
	ControlText*    m_pID_TEXT_MoneyZ;
	ControlText*	m_pID_TEXT_Money;
	ControlText*	m_pID_TEXT_TaskInfo;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_TaskOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_AwardOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_AwardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AwardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_AwardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	void ID_LIST_TaskStateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_TaskInfoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AcceptOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_RewardListOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_RewardListOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_RewardListOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_RewardListOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_BrushOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void Show(const ControlList::S_List* pTaskListItem, int count, int npcId, char taskType);
	void SetCanRefresh(bool bRefresh) { m_canRefresh = bRefresh; }
	bool GetCanRefresh() { return m_canRefresh; }
	int GetNpcId() { return m_npcId; }
	char GetTaskType() { return m_taskType; }

	void ShowTaskReward(SQuest* pQuest);
	void RefeshBrushButton();

private:
	bool m_canRefresh;
	int m_npcId;
	char m_taskType;

	void TaskListSelectChanged();
	void RefreshListPictrue();

// 	static void Task_HyberOtherClick( ControlObject* pSender, const std::string& content ,int nId );
	static void Task_HyberRBtnDown( ControlObject* pSender, const char* szName ,int eHyberType);
	static void OnVisibleChanged(ControlObject *pObject);
public:
	void ProcessVisualUI();
	void SetVisualPos(Vector &pos){m_VisualPos = pos;}
private:
	Vector m_VisualPos;
};
extern CUI_ID_FRAME_EspecialTask s_CUI_ID_FRAME_EspecialTask;
