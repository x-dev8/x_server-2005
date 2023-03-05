/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\RankTitle.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_RankTitle
#define ID_FRAME_RankTitle		"ID_FRAME_RankTitle"
#endif  ID_FRAME_RankTitle
#ifndef ID_LIST_RankName
#define ID_LIST_RankName		"ID_LIST_RankName"
#endif  ID_LIST_RankName
#ifndef ID_TEXT_CurRank
#define ID_TEXT_CurRank		"ID_TEXT_CurRank"
#endif  ID_TEXT_CurRank
#ifndef ID_BUTTON_ShowTitle
#define ID_BUTTON_ShowTitle		"ID_BUTTON_ShowTitle"
#endif  ID_BUTTON_ShowTitle
#ifndef ID_BUTTON_HideTitle
#define ID_BUTTON_HideTitle		"ID_BUTTON_HideTitle"
#endif  ID_BUTTON_HideTitle
#ifndef ID_TEXT_Introduction
#define ID_TEXT_Introduction		"ID_TEXT_Introduction"
#endif  ID_TEXT_Introduction
#ifndef ID_TEXT_CurSalary
#define ID_TEXT_CurSalary		"ID_TEXT_CurSalary"
#endif  ID_TEXT_CurSalary
#ifndef ID_LISTIMG_Buff
#define ID_LISTIMG_Buff		"ID_LISTIMG_Buff"
#endif  ID_LISTIMG_Buff
#ifndef ID_TEXT_CurHonour
#define ID_TEXT_CurHonour		"ID_TEXT_CurHonour"
#endif  ID_TEXT_CurHonour
#ifndef ID_TEXT_NeedHonour
#define ID_TEXT_NeedHonour		"ID_TEXT_NeedHonour"
#endif  ID_TEXT_NeedHonour
#ifndef ID_TEXT_NeedMoney
#define ID_TEXT_NeedMoney		"ID_TEXT_NeedMoney"
#endif  ID_TEXT_NeedMoney
#ifndef ID_BUTTON_GetSalary
#define ID_BUTTON_GetSalary		"ID_BUTTON_GetSalary"
#endif  ID_BUTTON_GetSalary
#ifndef ID_BUTTON_Advancement
#define ID_BUTTON_Advancement		"ID_BUTTON_Advancement"
#endif  ID_BUTTON_Advancement

class CUI_ID_FRAME_RankTitle : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_RankTitle();
	virtual ~CUI_ID_FRAME_RankTitle();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_RankNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_ShowTitleOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HideTitleOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_BuffOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_BuffOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_BuffOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_BuffOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_GetSalaryOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AdvancementOnButtonClick( ControlObject* pSender );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视

	void Refresh();
	void RefreshSelectChange();

private:	
	 ControlFrame*	m_pID_FRAME_RankTitle;
	 ControlList*	m_pID_LIST_RankName;
	 ControlText*	m_pID_TEXT_CurRank;
	 ControlButton*	m_pID_BUTTON_ShowTitle;
	 ControlButton*	m_pID_BUTTON_HideTitle;
	 ControlText*	m_pID_TEXT_Introduction;
	 ControlText*	m_pID_TEXT_CurSalary;
	 ControlListImage*	m_pID_LISTIMG_Buff;
	 ControlText*	m_pID_TEXT_CurHonour;
	 ControlText*	m_pID_TEXT_NeedHonour;
	 ControlText*	m_pID_TEXT_NeedMoney;
	 ControlButton*	m_pID_BUTTON_GetSalary;
	 ControlButton*	m_pID_BUTTON_Advancement;
};
extern CUI_ID_FRAME_RankTitle s_CUI_ID_FRAME_RankTitle;
