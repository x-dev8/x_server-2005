/********************************************************************
	Created by UIEditor.exe
	FileName: F:\project\Turbo\Bin\Client\Data\Ui\Editor.h
*********************************************************************/

/*----------------------------------------------------------
desc	: 角色的心情和称号对应的编辑和显示界面。
author	: zilong
version	: 1.0
date	: 2011-03-17
revision:
----------------------------------------------------------*/

#pragma once
#include "MeUi/MeUi.h"
#include "TitleConfig.h"

#ifndef ID_FRAME_Editor
#define ID_FRAME_Editor		"ID_FRAME_Editor"
#endif  ID_FRAME_Editor
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_TitleTop
#define ID_TEXT_TitleTop		"ID_TEXT_TitleTop"
#endif  ID_TEXT_TitleTop
#ifndef ID_TEXT_NonceName
#define ID_TEXT_NonceName		"ID_TEXT_NonceName"
#endif  ID_TEXT_NonceName
#ifndef ID_TEXT_HeartName
#define ID_TEXT_HeartName		"ID_TEXT_HeartName"
#endif  ID_TEXT_HeartName
#ifndef ID_BUTTON_Show
#define ID_BUTTON_Show		"ID_BUTTON_Show"
#endif  ID_BUTTON_Show
#ifndef ID_BUTTON_Conceal
#define ID_BUTTON_Conceal		"ID_BUTTON_Conceal"
#endif  ID_BUTTON_Conceal
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_CHECKBOX_Choice
#define ID_CHECKBOX_Choice		"ID_CHECKBOX_Choice"
#endif  ID_CHECKBOX_Choice
#ifndef ID_LIST_TitleList
#define ID_LIST_TitleList		"ID_LIST_TitleList"
#endif  ID_LIST_TitleList
#ifndef ID_TEXT_TitleContent
#define ID_TEXT_TitleContent		"ID_TEXT_TitleContent"
#endif  ID_TEXT_TitleContent
#ifndef ID_BUTTON_Sure
#define ID_BUTTON_Sure		"ID_BUTTON_Sure"
#endif  ID_BUTTON_Sure
#ifndef ID_BUTTON_ShowTitle
#define ID_BUTTON_ShowTitle		"ID_BUTTON_ShowTitle"
#endif  ID_BUTTON_ShowTitle
#ifndef ID_BUTTON_ConcealTitle
#define ID_BUTTON_ConcealTitle		"ID_BUTTON_ConcealTitle"
#endif  ID_BUTTON_ConcealTitle

#include "UiBase.h"

class TitleData;

class CUI_ID_FRAME_Editor: public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_Editor();
	 ControlFrame*	m_pID_FRAME_Editor;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_TitleTop;
	 ControlText*	m_pID_TEXT_NonceName;
	 ControlText*	m_pID_TEXT_HeartName;
	 ControlButton*	m_pID_BUTTON_Show;
	 ControlButton*	m_pID_BUTTON_Conceal;
	 ControlText*	m_pID_TEXT_Title;
	 ControlCheckBox*	m_pID_CHECKBOX_Choice;
	 ControlList*	m_pID_LIST_TitleList;
	 ControlText*	m_pID_TEXT_TitleContent;
	 ControlButton*	m_pID_BUTTON_Sure;
	 ControlButton*	m_pID_BUTTON_ShowTitle;
	 ControlButton*	m_pID_BUTTON_ConcealTitle;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ShowOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ConcealOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_ChoiceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_LIST_TitleListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_SureOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ShowTitleOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ConcealTitleOnButtonClick( ControlObject* pSender );

	void Refresh(void);
	void RefreshHeadInfo(void);
	void RefreshMoodText(void);

	void RefreshButtonState(void);

	void SendTitleMsg(bool bShow);
	void SendMoodMsg(bool bShow);

	void OnClickTitleButton(bool bShow);
	void OnClickMoodButton(bool bShow);

	bool EditInputIsVisable();

private:
	void RefreshTitleList(void);
	void RefreshTitleContent(void);
	void RefreshTitleContent(const TitleConfig::Title *pTitle_);

	//是否显示所有可以拥有的title
	bool IsShowAllTitle(void);
	bool IsActiveTitle(const TitleConfig::Title *pTitle_);
	void ShowAllTitle(bool bShowAll);
	//void ShowActiveTitle(void);
	const TitleData *GetTitleData(const TitleConfig::Title *pTitle_);

	void AddToTitleList( void* pTitleInfo, unsigned char ucLastType );

	TitleConfig::Title *GetCurrentSelectedTitle();
	const char *GetTitleTypeName(unsigned char ucType);

	void SetMoodButton(bool bShow);
	void SetTitleButton(bool bShow);

	void ChangeSignature(const char *pContent_);



private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
};
extern CUI_ID_FRAME_Editor s_CUI_ID_FRAME_Editor;
