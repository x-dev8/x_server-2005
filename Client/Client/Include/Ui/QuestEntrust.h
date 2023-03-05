/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\QuestEntrust.h
*********************************************************************/
//任务委托UI
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "QuestEntrustDefine.h"
#include "QuestEntrustConfig.h"
#ifndef ID_FRAME_QuestEntrust
#define ID_FRAME_QuestEntrust		"ID_FRAME_QuestEntrust"
#endif  ID_FRAME_QuestEntrust
#ifndef ID_LIST_QuestEntrustReward
#define ID_LIST_QuestEntrustReward		"ID_LIST_QuestEntrustReward"
#endif  ID_LIST_QuestEntrustReward
#ifndef ID_LIST_QuestEntrustName
#define ID_LIST_QuestEntrustName		"ID_LIST_QuestEntrustName"
#endif  ID_LIST_QuestEntrustName
#ifndef ID_CHECKBOX_AllQuestEntrust
#define ID_CHECKBOX_AllQuestEntrust		"ID_CHECKBOX_AllQuestEntrust"
#endif  ID_CHECKBOX_AllQuestEntrust
#ifndef ID_CHECKBOX_MyQuestEntrust
#define ID_CHECKBOX_MyQuestEntrust		"ID_CHECKBOX_MyQuestEntrust"
#endif  ID_CHECKBOX_MyQuestEntrust
#ifndef ID_CHECKBOX_JoinQuestEntrust
#define ID_CHECKBOX_JoinQuestEntrust		"ID_CHECKBOX_JoinQuestEntrust"
#endif  ID_CHECKBOX_JoinQuestEntrust
#ifndef ID_BUTTON_CanelMyQuestEntrust
#define ID_BUTTON_CanelMyQuestEntrust		"ID_BUTTON_CanelMyQuestEntrust"
#endif  ID_BUTTON_CanelMyQuestEntrust
#ifndef ID_BUTTON_DropQuestEntrust
#define ID_BUTTON_DropQuestEntrust		"ID_BUTTON_DropQuestEntrust"
#endif  ID_BUTTON_DropQuestEntrust
#ifndef ID_TEXT_QuestEntrustName
#define ID_TEXT_QuestEntrustName		"ID_TEXT_QuestEntrustName"
#endif  ID_TEXT_QuestEntrustName
#ifndef ID_TEXT_QuestEntrustDepict
#define ID_TEXT_QuestEntrustDepict		"ID_TEXT_QuestEntrustDepict"
#endif  ID_TEXT_QuestEntrustDepict
#ifndef ID_TEXT_QuestEntrustInfo
#define ID_TEXT_QuestEntrustInfo		"ID_TEXT_QuestEntrustInfo"
#endif  ID_TEXT_QuestEntrustInfo
#ifndef ID_TEXT_QuestEntrustReward
#define ID_TEXT_QuestEntrustReward		"ID_TEXT_QuestEntrustReward"
#endif  ID_TEXT_QuestEntrustReward

#ifndef ID_BUTTON_JoinQuestEntrust
#define ID_BUTTON_JoinQuestEntrust		"ID_BUTTON_JoinQuestEntrust"
#endif  ID_BUTTON_JoinQuestEntrust

#ifndef ID_BUTTON_GetReward
#define ID_BUTTON_GetReward		"ID_BUTTON_GetReward"
#endif  ID_BUTTON_GetReward

#ifndef ID_LISTIMG_Item
#define ID_LISTIMG_Item		"ID_LISTIMG_Item"
#endif  ID_LISTIMG_Item

#ifndef ID_BUTTON_Update
#define ID_BUTTON_Update		"ID_BUTTON_Update"
#endif  ID_BUTTON_Update

#ifndef ID_CHECKBOX_ShowCanJoin
#define ID_CHECKBOX_ShowCanJoin		"ID_CHECKBOX_ShowCanJoin"
#endif  ID_CHECKBOX_ShowCanJoin

#ifndef ID_TEXT_LastTime
#define ID_TEXT_LastTime		"ID_TEXT_LastTime"
#endif  ID_TEXT_LastTime

#ifndef ID_TEXT_MoneySum
#define ID_TEXT_MoneySum		"ID_TEXT_MoneySum"
#endif  ID_TEXT_MoneySum


class CUI_ID_FRAME_QuestEntrust : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_QuestEntrust();
	 ControlFrame*	m_pID_FRAME_QuestEntrust;
	 ControlList*	m_pID_LIST_QuestEntrustReward;
	 ControlList*	m_pID_LIST_QuestEntrustName;
	 ControlCheckBox*	m_pID_CHECKBOX_AllQuestEntrust;
	 ControlCheckBox*	m_pID_CHECKBOX_MyQuestEntrust;
	 ControlCheckBox*	m_pID_CHECKBOX_JoinQuestEntrust;
	 ControlButton*	m_pID_BUTTON_CanelMyQuestEntrust;
	 ControlButton*	m_pID_BUTTON_DropQuestEntrust;
	 ControlButton*	m_pID_BUTTON_JoinQuestEntrust;
     ControlButton*	m_pID_BUTTON_GetReward;
	 
	 ControlText*	m_pID_TEXT_QuestEntrustName;
	 ControlText*	m_pID_TEXT_QuestEntrustDepict;
	 ControlText*	m_pID_TEXT_QuestEntrustInfo;
	 ControlText*	m_pID_TEXT_QuestEntrustReward;
	 ControlListImage*	m_pID_LISTIMG_Item;
	 ControlButton*	m_pID_BUTTON_Update;

	 ControlCheckBox* m_pID_CHECKBOX_ShowCanJoin;
	 ControlText*	m_pID_TEXT_LastTime;
	 
	 ControlText*	m_pID_TEXT_MoneySum;
	 
	 

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_QuestEntrustRewardOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_QuestEntrustNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_AllQuestEntrustOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MyQuestEntrustOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_JoinQuestEntrustOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_CanelMyQuestEntrustOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DropQuestEntrustOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_JoinQuestEntrustOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GetRewardOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UpdateOnButtonClick( ControlObject* pSender );

	void ID_CHECKBOX_ShowCanJoinOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	bool ID_LISTIMG_ItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );// 设置是否可视
public:
	void LoadAllQuestEntrust(QuestEntrustStates* pList,int Sum);//将所有的数据加入集合
	void UpdateQuestEntrust(QuestEntrustStates& pInfo);//更新集合里的数据
	void UpdateUI();//更新UI上的显示

	void NeedGetAllData();

	bool IfCanJoinQuest(unsigned int QuestID);

	QuestEntrustConfig& GetConfig() {return m_Config;}

	void SetIsNeedClear(){m_IsNeedClear = true;}
private:
	void SetEmpty();//设置UI上的数据为空
	void SetAllQuestEntrustToUI(unsigned int SelectID = -1,bool IsShowNeed = false);//将所有可以接取的委托发布到UI上面去
	void SetMyQuestEntrusrToUI(unsigned int SelectID = -1);//将我发布的委托发布到Ui上面去
	void SetMyJoinQuestEntrustToUI(unsigned int SelectID = -1);//将我接的委托发布到UI上面去
	void SetQuestEntrustInfoToUI(unsigned int ID);
	int SetNameAndRewardToList(unsigned int ID);
	void SetSelectList(unsigned int Row);

	void OnShow();

	void ShowLastTime();
private:
	std::map<unsigned int,QuestEntrustStates> QuestEntrustList;
	std::map<int,unsigned int> IndexToIDMap;

	QuestEntrustConfig m_Config;

	unsigned int m_LastTime;//当前接取的委托的倒计时

	bool	     m_IsNeedClear;
};
extern CUI_ID_FRAME_QuestEntrust s_CUI_ID_FRAME_QuestEntrust;
