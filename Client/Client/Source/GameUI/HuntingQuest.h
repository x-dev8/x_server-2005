/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\HuntingQuest.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "QuestDefine.h"

#ifndef ID_FRAME_Hunting
#define ID_FRAME_Hunting		"ID_FRAME_Hunting"
#endif  ID_FRAME_Hunting
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_LIST_Name
#define ID_LIST_Name		"ID_LIST_Name"
#endif  ID_LIST_Name
#ifndef ID_LIST_Level
#define ID_LIST_Level		"ID_LIST_Level"
#endif  ID_LIST_Level
#ifndef ID_LIST_State
#define ID_LIST_State		"ID_LIST_State"
#endif  ID_LIST_State
#ifndef ID_LIST_Quest
#define ID_LIST_Quest		"ID_LIST_Quest"
#endif  ID_LIST_Quest
#ifndef ID_BUTTON_FreshGold
#define ID_BUTTON_FreshGold		"ID_BUTTON_FreshGold"
#endif  ID_BUTTON_FreshGold
#ifndef ID_TEXT_Gold
#define ID_TEXT_Gold		"ID_TEXT_Gold"
#endif  ID_TEXT_Gold
#ifndef ID_BUTTON_FreshFree
#define ID_BUTTON_FreshFree		"ID_BUTTON_FreshFree"
#endif  ID_BUTTON_FreshFree
#ifndef ID_BUTTON_FreshMoney
#define ID_BUTTON_FreshMoney		"ID_BUTTON_FreshMoney"
#endif  ID_BUTTON_FreshMoney
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_TEXT_TaskDepict
#define ID_TEXT_TaskDepict		"ID_TEXT_TaskDepict"
#endif  ID_TEXT_TaskDepict
#ifndef ID_TEXT_AdviseLevel
#define ID_TEXT_AdviseLevel		"ID_TEXT_AdviseLevel"
#endif  ID_TEXT_AdviseLevel
#ifndef ID_TEXT_TaskInfo
#define ID_TEXT_TaskInfo		"ID_TEXT_TaskInfo"
#endif  ID_TEXT_TaskInfo
#ifndef ID_TEXT_Award
#define ID_TEXT_Award		"ID_TEXT_Award"
#endif  ID_TEXT_Award
#ifndef ID_LISTIMG_Reward
#define ID_LISTIMG_Reward		"ID_LISTIMG_Reward"
#endif  ID_LISTIMG_Reward
#ifndef ID_LISTIMG_SecondItem
#define ID_LISTIMG_SecondItem		"ID_LISTIMG_SecondItem"
#endif  ID_LISTIMG_SecondItem
#ifndef ID_LISTIMG_ThirdItem
#define ID_LISTIMG_ThirdItem		"ID_LISTIMG_ThirdItem"
#endif  ID_LISTIMG_ThirdItem
#ifndef ID_LISTIMG_FourItem
#define ID_LISTIMG_FourItem		"ID_LISTIMG_FourItem"
#endif  ID_LISTIMG_FourItem
#ifndef ID_BUTTON_AccpetQuest
#define ID_BUTTON_AccpetQuest		"ID_BUTTON_AccpetQuest"
#endif  ID_BUTTON_AccpetQuest
#ifndef ID_TEXT_Aim
#define ID_TEXT_Aim		"ID_TEXT_Aim"
#endif  ID_TEXT_Aim

class CUI_ID_FRAME_Hunting : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_Hunting();
	virtual ~CUI_ID_FRAME_Hunting();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_LevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_StateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_QuestOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_FreshGoldOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FreshFreeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FreshMoneyOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_RewardOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_RewardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_RewardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_RewardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SecondItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_SecondItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SecondItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_SecondItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ThirdItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ThirdItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ThirdItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ThirdItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_FourItemOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_FourItemOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_FourItemOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_FourItemOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_AccpetQuestOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void SetLeftTime( int time );
	void SetStartTime( DWORD time ) { dwStartTime = time; }

	void SetReFreshGoldMoney();
	void Refresh();

	void Init();
	void InitIntroduce();
	void SetListInfo();
	void SetIntroduce();

	void GetRewardItemInfo(SQuest *pQuest,std::string &strRewardItem);
	void GetNeedItemInfo(SQuest *pQuest,std::string &strNeedItem);

	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }

	bool HasVarId(int nId);
	bool HasUnAcceptQuest();

private:	
	 ControlFrame*	m_pID_FRAME_Hunting;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlList*	m_pID_LIST_Name;
	 ControlList*	m_pID_LIST_Level;
	 ControlList*	m_pID_LIST_State;
	 ControlList*	m_pID_LIST_Quest;
	 ControlButton*	m_pID_BUTTON_FreshGold;
	 ControlText*	m_pID_TEXT_Gold;
	 ControlButton*	m_pID_BUTTON_FreshFree;
	 ControlButton*	m_pID_BUTTON_FreshMoney;
	 ControlText*	m_pID_TEXT_Money;
	 ControlText*	m_pID_TEXT_TaskDepict;
	 ControlText*	m_pID_TEXT_AdviseLevel;
	 ControlText*	m_pID_TEXT_TaskInfo;
	 ControlText*	m_pID_TEXT_Award;
	 ControlListImage*	m_pID_LISTIMG_Reward;
	 ControlListImage*	m_pID_LISTIMG_SecondItem;
	 ControlListImage*	m_pID_LISTIMG_ThirdItem;
	 ControlListImage*	m_pID_LISTIMG_FourItem;
	 ControlButton*	m_pID_BUTTON_AccpetQuest;
	 ControlText*	m_pID_TEXT_Aim;

	 int nLeftTime;
	 DWORD dwStartTime;

	 Vector m_vVisiblePos;
};
extern CUI_ID_FRAME_Hunting s_CUI_ID_FRAME_Hunting;
