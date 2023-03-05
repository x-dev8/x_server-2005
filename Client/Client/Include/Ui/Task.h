/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\Task.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "PlayerRole.h"
#include "uibase.h"
#include "..\NpcCoord.h"

#ifndef ID_FRAME_Task
#define ID_FRAME_Task		"ID_FRAME_Task"
#endif  ID_FRAME_Task
#ifndef ID_LIST_Task
#define ID_LIST_Task		"ID_LIST_Task"
#endif  ID_LIST_Task
#ifndef ID_PICTURE_2574
#define ID_PICTURE_2574		"ID_PICTURE_2574"
#endif  ID_PICTURE_2574
#ifndef ID_BUTTON_AbandonTask
#define ID_BUTTON_AbandonTask		"ID_BUTTON_AbandonTask"
#endif  ID_BUTTON_AbandonTask
#ifndef ID_PICTURE_12238
#define ID_PICTURE_12238		"ID_PICTURE_12238"
#endif  ID_PICTURE_12238
#ifndef ID_LISTIMG_Reward
#define ID_LISTIMG_Reward		"ID_LISTIMG_Reward"
#endif  ID_LISTIMG_Reward
#ifndef ID_LISTIMG_ThirdItem
#define ID_LISTIMG_ThirdItem		"ID_LISTIMG_ThirdItem"
#endif  ID_LISTIMG_ThirdItem
#ifndef ID_LISTIMG_FourItem
#define ID_LISTIMG_FourItem		"ID_LISTIMG_FourItem"
#endif  ID_LISTIMG_FourItem
#ifndef ID_TEXT_JIN
#define ID_TEXT_JIN		"ID_TEXT_JIN"
#endif  ID_TEXT_JIN
#ifndef ID_TEXT_wp
#define ID_TEXT_wp		"ID_TEXT_wp"
#endif  ID_TEXT_wp
#ifndef ID_TEXT_jb
#define ID_TEXT_jb		"ID_TEXT_jb"
#endif  ID_TEXT_jb
#ifndef ID_PICTURE_174
#define ID_PICTURE_174		"ID_PICTURE_174"
#endif  ID_PICTURE_174
// #ifndef ID_PICTURE_24561
// #define ID_PICTURE_24561		"ID_PICTURE_24561"
// #endif  ID_PICTURE_24561
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_27806
#define ID_TEXT_27806		"ID_TEXT_27806"
#endif  ID_TEXT_27806
#ifndef ID_TEXT_Exp2
#define ID_TEXT_Exp2		"ID_TEXT_Exp2"
#endif  ID_TEXT_Exp2
#ifndef ID_TEXT_Exp
#define ID_TEXT_Exp		"ID_TEXT_Exp"
#endif  ID_TEXT_Exp
#ifndef ID_TEXT_246
#define ID_TEXT_246		"ID_TEXT_246"
#endif  ID_TEXT_246
#ifndef ID_PICTURE_122366
#define ID_PICTURE_122366		"ID_PICTURE_122366"
#endif  ID_PICTURE_122366
#ifndef ID_CHECKBOX_Task1
#define ID_CHECKBOX_Task1		"ID_CHECKBOX_Task1"
#endif  ID_CHECKBOX_Task1
#ifndef ID_CHECKBOX_Task2
#define ID_CHECKBOX_Task2		"ID_CHECKBOX_Task2"
#endif  ID_CHECKBOX_Task2
// #ifndef ID_PICTURE_12234
// #define ID_PICTURE_12234		"ID_PICTURE_12234"
// #endif  ID_PICTURE_12234
#ifndef ID_BUTTON_Zhuizong
#define ID_BUTTON_Zhuizong		"ID_BUTTON_Zhuizong"
#endif  ID_BUTTON_Zhuizong
#ifndef ID_BUTTON_Quxiao
#define ID_BUTTON_Quxiao		"ID_BUTTON_Quxiao"
#endif  ID_BUTTON_Quxiao
#ifndef ID_LIST_Taskstate
#define ID_LIST_Taskstate		"ID_LIST_Taskstate"
#endif  ID_LIST_Taskstate
#ifndef ID_LIST_TaskInfo
#define ID_LIST_TaskInfo		"ID_LIST_TaskInfo"
#endif  ID_LIST_TaskInfo
#ifndef ID_TEXT_TaskDiff
#define ID_TEXT_TaskDiff		"ID_TEXT_TaskDiff"
#endif  ID_TEXT_TaskDiff
#ifndef ID_TEXT_TaskLvl
#define ID_TEXT_TaskLvl		"ID_TEXT_TaskLvl"
#endif  ID_TEXT_TaskLvl
#ifndef ID_CHECKBOX_jieneng
#define ID_CHECKBOX_jieneng		"ID_CHECKBOX_jieneng"
#endif  ID_CHECKBOX_jieneng
#ifndef ID_TEXT_TaskTrack
#define ID_TEXT_TaskTrack		"ID_TEXT_TaskTrack"
#endif  ID_TEXT_TaskTrack
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_PICTURE_RankId3
#define ID_PICTURE_RankId3		"ID_PICTURE_RankId3"
#endif  ID_PICTURE_RankId3
#ifndef ID_PICTURE_RankId2
#define ID_PICTURE_RankId2		"ID_PICTURE_RankId2"
#endif  ID_PICTURE_RankId2
#ifndef ID_PICTURE_RankId1
#define ID_PICTURE_RankId1		"ID_PICTURE_RankId1"
#endif  ID_PICTURE_RankId1
#ifndef ID_PICTURE_RankId0
#define ID_PICTURE_RankId0		"ID_PICTURE_RankId0"
#endif  ID_PICTURE_RankId0
#ifndef ID_PICTURE_RankId4
#define ID_PICTURE_RankId4		"ID_PICTURE_RankId4"
#endif  ID_PICTURE_RankId4

#ifndef ID_TEXT_TitleZ
#define ID_TEXT_TitleZ		"ID_TEXT_TitleZ"
#endif  ID_TEXT_TitleZ
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_BUTTON_ActivityList
#define ID_BUTTON_ActivityList		"ID_BUTTON_ActivityList"
#endif  ID_BUTTON_ActivityList

#ifndef ID_TEXT_FinallyItem
#define ID_TEXT_FinallyItem		"ID_TEXT_FinallyItem"
#endif  ID_TEXT_FinallyItem
#ifndef ID_LISTIMG_FinallyReward
#define ID_LISTIMG_FinallyReward		"ID_LISTIMG_FinallyReward"
#endif  ID_LISTIMG_FinallyReward
#ifndef ID_LIST_Finish
#define ID_LIST_Finish		"ID_LIST_Finish"
#endif  ID_LIST_Finish
#ifndef ID_TEXT_MingWangZ
#define ID_TEXT_MingWangZ		"ID_TEXT_MingWangZ"
#endif  ID_TEXT_MingWangZ
#ifndef ID_TEXT_MingWang
#define ID_TEXT_MingWang		"ID_TEXT_MingWang"
#endif  ID_TEXT_MingWang
#ifndef ID_TEXT_RongYuZ
#define ID_TEXT_RongYuZ		"ID_TEXT_RongYuZ"
#endif  ID_TEXT_RongYuZ
#ifndef ID_TEXT_RongYu
#define ID_TEXT_RongYu		"ID_TEXT_RongYu"
#endif  ID_TEXT_RongYu
#ifndef ID_TEXT_GongXunZ
#define ID_TEXT_GongXunZ		"ID_TEXT_GongXunZ"
#endif  ID_TEXT_GongXunZ
#ifndef ID_TEXT_GongXun
#define ID_TEXT_GongXun		"ID_TEXT_GongXun"
#endif  ID_TEXT_GongXun
#ifndef ID_LISTIMG_FinallyReward2
#define ID_LISTIMG_FinallyReward2		"ID_LISTIMG_FinallyReward2"
#endif  ID_LISTIMG_FinallyReward2
#ifndef ID_LISTIMG_RewardList
#define ID_LISTIMG_RewardList		"ID_LISTIMG_RewardList"
#endif  ID_LISTIMG_RewardList
#ifndef ID_TEXT_TaskInfo
#define ID_TEXT_TaskInfo		"ID_TEXT_TaskInfo"
#endif  ID_TEXT_TaskInfo
#ifndef ID_TEXT_TaskDepict
#define ID_TEXT_TaskDepict		"ID_TEXT_TaskDepict"
#endif  ID_TEXT_TaskDepict
#ifndef ID_TEXT_SkillExpZ
#define ID_TEXT_SkillExpZ		"ID_TEXT_SkillExpZ"
#endif  ID_TEXT_SkillExpZ
#ifndef ID_TEXT_SkillExp
#define ID_TEXT_SkillExp		"ID_TEXT_SkillExp"
#endif  ID_TEXT_SkillExp
#ifndef ID_TEXT_EspecialMoneyZ
#define ID_TEXT_EspecialMoneyZ		"ID_TEXT_EspecialMoneyZ"
#endif  ID_TEXT_EspecialMoneyZ
#ifndef ID_TEXT_EspecialMoney
#define ID_TEXT_EspecialMoney		"ID_TEXT_EspecialMoney"
#endif  ID_TEXT_EspecialMoney
#ifndef ID_LISTIMG_SecondItem
#define ID_LISTIMG_SecondItem		"ID_LISTIMG_SecondItem"
#endif  ID_LISTIMG_SecondItem
#ifndef ID_TEXT_FITEM
#define ID_TEXT_FITEM		"ID_TEXT_FITEM"
#endif  ID_TEXT_FITEM
#ifndef ID_TEXT_SECITEM
#define ID_TEXT_SECITEM		"ID_TEXT_SECITEM"
#endif  ID_TEXT_SECITEM
#ifndef ID_BUTTON_Epic
#define ID_BUTTON_Epic		"ID_BUTTON_Epic"
#endif  ID_BUTTON_Epic
#ifndef ID_CHECKBOX_ActivityTrack
#define ID_CHECKBOX_ActivityTrack		"ID_CHECKBOX_ActivityTrack"
#endif  ID_CHECKBOX_ActivityTrack

#ifndef ID_TEXT_AwardExp
#define ID_TEXT_AwardExp		"ID_TEXT_AwardExp"
#endif  ID_TEXT_AwardExp
#ifndef ID_TEXT_AwardMoney
#define ID_TEXT_AwardMoney		"ID_TEXT_AwardMoney"
#endif  ID_TEXT_AwardMoney

#ifndef ID_PICTURE_JQ1
#define ID_PICTURE_JQ1		"ID_PICTURE_JQ1"
#endif  ID_PICTURE_JQ1

#ifndef ID_TEXT_Amount
#define ID_TEXT_Amount		"ID_TEXT_Amount"
#endif  ID_TEXT_Amount
#ifndef ID_TEXT_Award
#define ID_TEXT_Award		"ID_TEXT_Award"
#endif  ID_TEXT_Award
#ifndef ID_TEXT_Aim
#define ID_TEXT_Aim		"ID_TEXT_Aim"
#endif  ID_TEXT_Aim

#ifndef ID_CHECKBOX_Jin
#define ID_CHECKBOX_Jin		"ID_CHECKBOX_Jin"
#endif	ID_CHECKBOX_Jin


#ifndef ID_BUTTON_AddQuestEntrust
#define ID_BUTTON_AddQuestEntrust		"ID_BUTTON_AddQuestEntrust"
#endif	ID_BUTTON_AddQuestEntrust

#ifndef ID_BUTTON_OpenQuestEntrust
#define ID_BUTTON_OpenQuestEntrust		"ID_BUTTON_OpenQuestEntrust"
#endif	ID_BUTTON_OpenQuestEntrust




#include "UiBase.h"
class CUI_ID_FRAME_Task :public CUIBase 
{
	// Member
private:
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_Task;
	ControlList*	m_pID_LIST_Task;
	ControlButton*	m_pID_BUTTON_AbandonTask;
	ControlListImage*	m_pID_LISTIMG_Reward;
	ControlListImage*	m_pID_LISTIMG_ThirdItem;
	ControlListImage*	m_pID_LISTIMG_FourItem;
	ControlPicture*	m_pID_PICTURE_174;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlCheckBox*	m_pID_CHECKBOX_Task1;
	ControlCheckBox*	m_pID_CHECKBOX_Task2;
	ControlButton*	m_pID_BUTTON_Zhuizong;
	ControlButton*	m_pID_BUTTON_Quxiao;
	ControlText*	m_pID_TEXT_TaskDiff;
	ControlCheckBox*	m_pID_CHECKBOX_jieneng;
	ControlText*	m_pID_TEXT_TaskTrack;
    ControlButton*	m_pID_BUTTON_ActivityList;
    ControlList*	m_pID_LIST_Finish;
    ControlText*	m_pID_TEXT_TaskInfo;
	ControlText*	m_pID_TEXT_TaskDepict;
	ControlListImage*	m_pID_LISTIMG_SecondItem;
	ControlText*	m_pID_TEXT_FITEM;
	ControlText*	m_pID_TEXT_SECITEM;
	ControlButton*	m_pID_BUTTON_Epic;
	ControlCheckBox*	m_pID_CHECKBOX_ActivityTrack;

	ControlText*	m_pID_TEXT_AwardExp;
	ControlText*	m_pID_TEXT_AwardMoney;
	ControlText*	m_pID_TEXT_Amount;

	ControlText*	m_pID_TEXT_Award;
	ControlPicture*	m_pID_PICTURE_JQ1;
	ControlText*	m_pID_TEXT_Aim;
	ControlCheckBox*  m_pID_CHECKBOX_Jin;

	ControlButton*	m_pID_BUTTON_AddQuestEntrust;

	ControlButton*	m_pID_BUTTON_OpenQuestEntrust;

    ControlGroup m_finishPics;

	BOOL m_bUILoad;
	COLORREF col;
	int			_nCurIndex;
	WORD		m_dwLastRefreshTime;	

	std::list<int> m_vTrackList;
	std::vector<int> m_vNotTrackList;

	enum
	{
		MaxTrackNum = 5
	};

public:	
	CUI_ID_FRAME_Task();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_TaskOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_AbandonTaskOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AddQuestEntrustOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OpenQuestEntrustOnButtonClick( ControlObject* pSender );
	

	bool ID_LISTIMG_RewardOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_RewardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_RewardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_RewardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ThirdItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ThirdItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ThirdItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ThirdItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_FourItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_FourItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_FourItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_FourItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_Task1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_Task2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_ZhuizongOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_QuxiaoOnButtonClick( ControlObject* pSender );
	void ID_LIST_TaskstateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_jienengOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_ActivityListOnButtonClick( ControlObject* pSender );
	void ID_LIST_FinishOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_SecondItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SecondItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SecondItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SecondItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_EpicOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_ActivityTrackOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_JinOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	static bool UITaskFrame_MsgProc(UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed);

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	        // 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
    virtual void InitializeAtEnterWorld();
	ControlFrame* GetFrame() { return m_pID_FRAME_Task; }
	void Refresh(bool bClear = false );
	void AddTaskItem(SQuest *pQuest);
	bool RefreshCurrSelect();
	void ShowUnderLine( bool bShow = true );
	void CHECKBOX_jieneng_SetCheck( bool bCheck );
	void FillMapPosTip(const NpcCoordInfo* pNpcInfo,ControlList::S_List* pList);
	void SetDirty( bool bDirty ){ m_bUpdateTrackTask = bDirty; }
	bool IsDirty(){ return m_bUpdateTrackTask; }
	void RefreshTaskTrack();

// 	static void Task_HyberOtherClick( ControlObject* pSender, const std::string& content ,int nId );

	static void Task_HyberRBtnDown( ControlObject* pSender, const char* szName ,int eHyberType);
	static bool Task_AbandonCallBackFun( const char bPressYesButton, void *pData );
	static void Task_CollapseCallBackFun(  ControlObject* pSender, ControlList::S_List* pItem );
	static void Task_OnVisiableChanged( ControlObject* pSender );
	static void FrameOnVisiableChanged( ControlObject* pSender );
	static void Text_TaskInfo_HyberClick( ControlObject* pSender, const char* szData );
	static void UpdateTaskInfo( OUT ControlObject* pSender, int n );
	bool LoadTrackInfo();
    void UpdateTrackInfo();
	void UpdateTrackInfoItem(SQuest *pQuest,bool bDone,std::map<int, int> &collapseStatus);
	ControlObject* GetTextControl(){if(!m_pID_FRAME_Task) return NULL;return m_pID_TEXT_TaskInfo;}

	std::string GetQuestTargetInfo( SQuest *pQuest, CPlayerRole::QuestInfo* pInfo,bool IsAddStrMapName = true);
private:
	bool UITask_ShowInfo( int questId );
	void ClearShowInfo();
	//新的信息显示面板添加的函数
	bool UpdateTaskPanel( int questId );
	void ClearTaskPanel();
	

	void AddInfoToTaskInfo(std::string& str,short questId,short npcId);
	void AddInfoToTaskState(const std::string& str);
	void AddInfoToList(const std::string& str, ControlList* pList,DWORD col,short questId,short npcId,bool bShowMapName,int nHiberarchy = 0,std::vector<UiCallbackDataBase*> *pData = NULL);
	void AddInfoToListName(const std::string& str, ControlList* pList,DWORD col,short questId,bool bShowMapName,int nHiberarchy = 0,std::vector<UiCallbackDataBase*> *pData = NULL);
    void RecordCollapseInfo();
    bool LoadCollapseInfo();
    bool SaveCollapseInfo();
	void RefreshFinishPic();
    void SaveTrackInfo();
	void GetNeedItemInfo(SQuest *pQuest,std::string &strNeedItem);
	void GetRewardItemInfo(SQuest *pQuest,std::string &strRewardItem);
	void ModifyRewardItem(int nTop,int nLeft);
	void UpdateRewardItem(int n);
	void AddMapName(const NpcCoordInfo* pNpcInfo,std::string &format);
	void SetTaskNum(int nTaskNum);
	
	static uint8 GetQusetSortValue(uint8 Type);
	static bool SortByQuestID(int lhs, int rhs);
private:
	bool		        m_bUpdateTrackTask;
	const char*	        m_QuestTypeString[SQuest::Type_End];
	int			        m_nCurrSelectedQuest;
	bool                m_bTaskInfoLoaded;
	std::vector<int>    m_arrHideTaskTypeInAccecptableTask;
	char	            m_CurrTabType;
private:
	bool                m_bFirst;
	RECT                m_rc;
};
extern CUI_ID_FRAME_Task s_CUI_ID_FRAME_Task;
