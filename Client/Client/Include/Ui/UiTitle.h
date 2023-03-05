/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\Title.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "TitleConfig.h"
#include "GlobalDef.h"

#ifndef ID_FRAME_Title
#define ID_FRAME_Title		"ID_FRAME_Title"
#endif  ID_FRAME_Title
#ifndef ID_PICTURE_PropertyWall
#define ID_PICTURE_PropertyWall		"ID_PICTURE_PropertyWall"
#endif  ID_PICTURE_PropertyWall
#ifndef ID_PICTURE_ExplainWall
#define ID_PICTURE_ExplainWall		"ID_PICTURE_ExplainWall"
#endif  ID_PICTURE_ExplainWall
#ifndef ID_PICTURE_TitleWall
#define ID_PICTURE_TitleWall		"ID_PICTURE_TitleWall"
#endif  ID_PICTURE_TitleWall
#ifndef ID_TEXT_Explain
#define ID_TEXT_Explain		"ID_TEXT_Explain"
#endif  ID_TEXT_Explain
#ifndef ID_BUTTON_HideTitle
#define ID_BUTTON_HideTitle		"ID_BUTTON_HideTitle"
#endif  ID_BUTTON_HideTitle
#ifndef ID_LIST_TitleList
#define ID_LIST_TitleList		"ID_LIST_TitleList"
#endif  ID_LIST_TitleList
#ifndef ID_BUTTON_ShowTitle
#define ID_BUTTON_ShowTitle		"ID_BUTTON_ShowTitle"
#endif  ID_BUTTON_ShowTitle
#ifndef ID_LIST_Property
#define ID_LIST_Property		"ID_LIST_Property"
#endif  ID_LIST_Property

#ifndef ID_LIST_NextProperty
#define ID_LIST_NextProperty		"ID_LIST_NextProperty"
#endif  ID_LIST_NextProperty

#ifndef ID_TEXT_NextExplain
#define ID_TEXT_NextExplain		"ID_TEXT_NextExplain"
#endif  ID_TEXT_NextExplain

#ifndef ID_TEXT_NextTitle
#define ID_TEXT_NextTitle		"ID_TEXT_NextTitle"
#endif  ID_TEXT_NextTitle

#ifndef ID_EDIT_MOOD
#define ID_EDIT_MOOD		"ID_EDIT_MOOD"
#endif  ID_EDIT_MOOD

#ifndef ID_COMBOBOX_MOOD_TITLE
#define ID_COMBOBOX_MOOD_TITLE		"ID_COMBOBOX_MOOD_TITLE"
#endif  ID_COMBOBOX_MOOD_TITLE

#ifndef ID_BUTTON_MODIFY_MOOD
#define ID_BUTTON_MODIFY_MOOD		"ID_BUTTON_MODIFY_MOOD"
#endif  ID_BUTTON_MODIFY_MOOD

#ifndef ID_LISTIMG_Buff
#define ID_LISTIMG_Buff		"ID_LISTIMG_Buff"
#endif  ID_LISTIMG_Buff

#include "UiBase.h"
#include "RelationDefine.h"

class CUI_ID_FRAME_Title :public CUIBase
{
	// Member
private:
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_Title;
	ControlText*	m_pID_TEXT_Explain;
	ControlButton*	m_pID_BUTTON_HideTitle;
	ControlList*	m_pID_LIST_TitleList;
	ControlButton*	m_pID_BUTTON_ShowTitle;
	ControlList*	m_pID_LIST_Property;
// 	ControlText*	m_pID_TEXT_NextExplain;
// 	ControlList*	m_pID_LIST_NextProperty;
// 	ControlText*	m_pID_TEXT_NextTitle;
	ControlEdit*	m_pID_EDIT_MOOD;
	ControlComboBox*	m_pID_COMBOBOX_MOOD_TITLE;
	ControlButton*	m_pID_BUTTON_MODIFY_MOOD;
	ControlListImage*	m_pID_LISTIMG_Buff;

public:	
	CUI_ID_FRAME_Title();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HideTitleOnButtonClick( ControlObject* pSender );
	void ID_LIST_TitleListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_ShowTitleOnButtonClick( ControlObject* pSender );
	void ID_LIST_PropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	//void ID_LIST_NextPropertyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_EDIT_MOODOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_MOOD_TITLEOnComboBoxChange( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_MODIFY_MOODOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_BuffOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_BuffOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_BuffOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_BuffOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	ControlFrame* GetFrame() { return m_pID_FRAME_Title; }
	ControlList* GetLIST_TitleList();
	void NeedRefresh();
	bool EditInputIsVisable();

	TitleConfig::Title* GetCurrentSelectTitle(); //baseproperty中要用到
private:
	void RefreshMood();
	void RefreshTitleList();
	void Refresh();
	void RefreshTitleDesc( ControlObject* pDescUi, TitleConfig::Title* pTitle, bool bShowName = false );
	void RefreshTitleProp( ControlObject* pPropertyUi, TitleConfig::Title* pTitle );
	void RefreshTitleBuff( ControlObject* pBuffUi, TitleConfig::Title* pTitle );

    TitleData* IsHaveExistTitle(TitleConfig::Title* pTitle);

	void AddToTitleList( void* pTitleInfo, unsigned char ucLastType );
	const char* GetTitleTypeName( unsigned char ucType );
	
    bool  m_bNeedRefresh;
};
extern CUI_ID_FRAME_Title s_CUI_ID_FRAME_Title;

