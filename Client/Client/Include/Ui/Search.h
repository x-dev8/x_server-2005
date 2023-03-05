/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\刘小兵\社交\Search.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MsgBase.h"
#include "RelationDefine.h"

#ifndef ID_FRAME_Search
#define ID_FRAME_Search		"ID_FRAME_Search"
#endif  ID_FRAME_Search
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_AddFriend
#define ID_BUTTON_AddFriend		"ID_BUTTON_AddFriend"
#endif  ID_BUTTON_AddFriend
#ifndef ID_BUTTON_Advance
#define ID_BUTTON_Advance		"ID_BUTTON_Advance"
#endif  ID_BUTTON_Advance
#ifndef ID_BUTTON_NameSearch
#define ID_BUTTON_NameSearch		"ID_BUTTON_NameSearch"
#endif  ID_BUTTON_NameSearch
#ifndef ID_LIST_Name
#define ID_LIST_Name		"ID_LIST_Name"
#endif  ID_LIST_Name
#ifndef ID_LIST_Guild
#define ID_LIST_Guild		"ID_LIST_Guild"
#endif  ID_LIST_Guild
#ifndef ID_LIST_Country
#define ID_LIST_Country		"ID_LIST_Country"
#endif  ID_LIST_Country
#ifndef ID_LIST_Job
#define ID_LIST_Job		"ID_LIST_Job"
#endif  ID_LIST_Job
#ifndef ID_LIST_Select
#define ID_LIST_Select		"ID_LIST_Select"
#endif  ID_LIST_Select
#ifndef ID_PICTURE_AdvanceBg
#define ID_PICTURE_AdvanceBg		"ID_PICTURE_AdvanceBg"
#endif  ID_PICTURE_AdvanceBg
#ifndef ID_BUTTON_AdvanceSearch
#define ID_BUTTON_AdvanceSearch		"ID_BUTTON_AdvanceSearch"
#endif  ID_BUTTON_AdvanceSearch
#ifndef ID_COMBOBOX_Province
#define ID_COMBOBOX_Province		"ID_COMBOBOX_Province"
#endif  ID_COMBOBOX_Province
#ifndef ID_COMBOBOX_City
#define ID_COMBOBOX_City		"ID_COMBOBOX_City"
#endif  ID_COMBOBOX_City
#ifndef ID_COMBOBOX_Age
#define ID_COMBOBOX_Age		"ID_COMBOBOX_Age"
#endif  ID_COMBOBOX_Age
#ifndef ID_COMBOBOX_Sex
#define ID_COMBOBOX_Sex		"ID_COMBOBOX_Sex"
#endif  ID_COMBOBOX_Sex
#ifndef ID_EDIT_SelectTarget
#define ID_EDIT_SelectTarget		"ID_EDIT_SelectTarget"
#endif  ID_EDIT_SelectTarget
#ifndef ID_BUTTON_PageUp
#define ID_BUTTON_PageUp "ID_BUTTON_PageUp"
#endif  ID_BUTTON_PageUp
#ifndef ID_BUTTON_PageDown
#define ID_BUTTON_PageDown "ID_BUTTON_PageDown"
#endif  ID_BUTTON_PageDown
#ifndef ID_TEXT_Page
#define ID_TEXT_Page "ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_TEXT_Tell
#define ID_TEXT_Tell "ID_TEXT_Tell"
#endif  ID_TEXT_Tell
#ifndef ID_LIST_Lv
#define ID_LIST_Lv		"ID_LIST_Lv"
#endif  ID_LIST_Lv
#ifndef ID_LIST_Faminly
#define ID_LIST_Faminly		"ID_LIST_Faminly"
#endif  ID_LIST_Faminly

#include "UiBase.h"
struct MsgQueryAttributeResult;
class CUI_ID_FRAME_Search: public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_Search();

	 bool OnFrameRun();
	 bool OnFrameRender();
	 bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	 bool ID_BUTTON_AddFriendOnButtonClick( ControlObject* pSender );
	 bool ID_BUTTON_AdvanceOnButtonClick( ControlObject* pSender );
	 bool ID_BUTTON_NameSearchOnButtonClick( ControlObject* pSender );
	 void ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	 void ID_LIST_GuildOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	 void ID_LIST_CountryOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	 void ID_LIST_JobOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	 void ID_LIST_SelectOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	 void ID_LIST_LvOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	 bool ID_BUTTON_AdvanceSearchOnButtonClick( ControlObject* pSender );
	 void ID_COMBOBOX_ProvinceOnComboBoxChange( ControlObject* pSender, const char* szData );
	 void ID_COMBOBOX_CityOnComboBoxChange( ControlObject* pSender, const char* szData );
	 void ID_COMBOBOX_AgeOnComboBoxChange( ControlObject* pSender, const char* szData );
	 void ID_COMBOBOX_SexOnComboBoxChange( ControlObject* pSender, const char* szData );
	 void ID_EDIT_SelectTargetOnEditEnter( ControlObject* pSender, const char* szData );

	  bool ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender );
	  bool ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender );

	 void ID_LIST_FaminlyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

public:
	//member functions
	void OnSearchResult(Msg * pMsg_);
	bool EditInputIsVisable();

private:
	void ShowUnFoundMessage();
	void ShowFoundPlayerAttribute(int nStart_, int nEnd_);
	void ResetRelationAttribute();
	void ResetListData();
	void RefreshButtonState();
	void SetAdvanceVisable(bool);

private:
	std::vector<RelationAttribute> m_vctRelationAttribute;
	int m_nPlayerNumber;
	int m_nCurrentPageIndex;
private:
	 ControlFrame*	m_pID_FRAME_Search;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_AddFriend;
	 ControlButton*	m_pID_BUTTON_Advance;
	 ControlButton*	m_pID_BUTTON_NameSearch;
	 ControlList*	m_pID_LIST_Name;
	 ControlList*	m_pID_LIST_Guild;
	 ControlList*	m_pID_LIST_Country;
	 ControlList*	m_pID_LIST_Job;
	 ControlList*	m_pID_LIST_Select;
	 ControlList*	m_pID_LIST_Lv;
	 ControlPicture*	m_pID_PICTURE_AdvanceBg;
	 ControlButton*	m_pID_BUTTON_AdvanceSearch;
	 ControlComboBox*	m_pID_COMBOBOX_Province;
	 ControlComboBox*	m_pID_COMBOBOX_City;
	 ControlComboBox*	m_pID_COMBOBOX_Age;
	 ControlComboBox*	m_pID_COMBOBOX_Sex;
	 ControlEdit*	m_pID_EDIT_SelectTarget;
	 ControlText* m_pID_TEXT_Page;
	 ControlText* m_pID_TEXT_Tell;
	 ControlButton*	m_pID_BUTTON_PageUp;
	 ControlButton*	m_pID_BUTTON_PageDown;
	 ControlList*	m_pID_LIST_Faminly;
	 ControlGroup AdvanceCtrlGroup;

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
};
extern CUI_ID_FRAME_Search s_CUI_ID_FRAME_Search;
