/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\SevenDaysTask.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_SevenDays_Task
#define ID_FRAME_SevenDays_Task		"ID_FRAME_SevenDays_Task"
#endif  ID_FRAME_SevenDays_Task
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_LIST_Name
#define ID_LIST_Name		"ID_LIST_Name"
#endif  ID_LIST_Name
#ifndef ID_LIST_State
#define ID_LIST_State		"ID_LIST_State"
#endif  ID_LIST_State
#ifndef ID_LIST_Select
#define ID_LIST_Select		"ID_LIST_Select"
#endif  ID_LIST_Select
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_TEXT_Condition
#define ID_TEXT_Condition		"ID_TEXT_Condition"
#endif  ID_TEXT_Condition
#ifndef ID_TEXT_Tips
#define ID_TEXT_Tips		"ID_TEXT_Tips"
#endif  ID_TEXT_Tips
#ifndef ID_LISTIMG_Item1
#define ID_LISTIMG_Item1		"ID_LISTIMG_Item1"
#endif  ID_LISTIMG_Item1
#ifndef ID_TEXT_ItemName1
#define ID_TEXT_ItemName1		"ID_TEXT_ItemName1"
#endif  ID_TEXT_ItemName1
#ifndef ID_LISTIMG_Item2
#define ID_LISTIMG_Item2		"ID_LISTIMG_Item2"
#endif  ID_LISTIMG_Item2
#ifndef ID_TEXT_ItemName2
#define ID_TEXT_ItemName2		"ID_TEXT_ItemName2"
#endif  ID_TEXT_ItemName2
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_BUTTON_GainTask
#define ID_BUTTON_GainTask		"ID_BUTTON_GainTask"
#endif  ID_BUTTON_GainTask
#ifndef ID_BUTTON_Reward
#define ID_BUTTON_Reward		"ID_BUTTON_Reward"
#endif  ID_BUTTON_Reward
#ifndef ID_LISTIMG_Item3
#define ID_LISTIMG_Item3		"ID_LISTIMG_Item3"
#endif  ID_LISTIMG_Item3
#ifndef ID_TEXT_ItemName3
#define ID_TEXT_ItemName3		"ID_TEXT_ItemName3"
#endif  ID_TEXT_ItemName3
#ifndef ID_LISTIMG_Item4
#define ID_LISTIMG_Item4		"ID_LISTIMG_Item4"
#endif  ID_LISTIMG_Item4
#ifndef ID_TEXT_ItemName4
#define ID_TEXT_ItemName4		"ID_TEXT_ItemName4"
#endif  ID_TEXT_ItemName4
#ifndef ID_TEXT_GiftTip
#define ID_TEXT_GiftTip		"ID_TEXT_GiftTip"
#endif  ID_TEXT_GiftTip


class CUI_ID_FRAME_SevenDays_Task : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_SevenDays_Task();
	virtual ~CUI_ID_FRAME_SevenDays_Task();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_StateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_SelectOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_LISTIMG_Item1OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Item1OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item1OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item1OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item2OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Item2OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item2OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item2OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_BUTTON_GainTaskOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RewardOnButtonClick( ControlObject* pSender );

	bool ID_LISTIMG_Item3OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Item3OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item3OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item3OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item4OnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_Item4OnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item4OnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_Item4OnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void Init();
	void InitIntroduce();

	void SetListNameState();
	void SetIntroduceData();
	void ShowItemName(ControlText* pText, int itemID);

	const char* GetStatesText(int state);

	void Refresh();

private:	
	 ControlFrame*	m_pID_FRAME_SevenDays_Task;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlList*	m_pID_LIST_Name;
	 ControlList*	m_pID_LIST_State;
	 ControlList*	m_pID_LIST_Select;
	 ControlText*	m_pID_TEXT_Title;
	 ControlText*	m_pID_TEXT_Condition;
	 ControlText*	m_pID_TEXT_Tips;
	 ControlListImage*	m_pID_LISTIMG_Item1;
	 ControlText*	m_pID_TEXT_ItemName1;
	 ControlListImage*	m_pID_LISTIMG_Item2;
	 ControlText*	m_pID_TEXT_ItemName2;
	 ControlText*	m_pID_TEXT_Money;
	 ControlButton*	m_pID_BUTTON_GainTask;
	 ControlButton*	m_pID_BUTTON_Reward;
	 ControlListImage*	m_pID_LISTIMG_Item3;
	 ControlText*	m_pID_TEXT_ItemName3;
	 ControlListImage*	m_pID_LISTIMG_Item4;
	 ControlText*	m_pID_TEXT_ItemName4;
	 ControlText*	m_pID_TEXT_GiftTip;

	 ControlGroup  m_ItemGroup;
	 ControlGroup  m_NameGroup;

	 int m_lastSelectIndex;
};
extern CUI_ID_FRAME_SevenDays_Task s_CUI_ID_FRAME_SevenDays_Task;
