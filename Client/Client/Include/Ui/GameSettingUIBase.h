/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\gamesetting\GameSetting.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GameSettingUIBase
#define ID_FRAME_GameSettingUIBase		"ID_FRAME_GameSettingUIBase"
#endif  ID_FRAME_GameSettingUIBase
#ifndef ID_PICTURE_TitleMiddle
#define ID_PICTURE_TitleMiddle		"ID_PICTURE_TitleMiddle"
#endif  ID_PICTURE_TitleMiddle
#ifndef ID_PICTURE_Title
#define ID_PICTURE_Title		"ID_PICTURE_Title"
#endif  ID_PICTURE_Title
#ifndef ID_PICTURE_ListWall
#define ID_PICTURE_ListWall		"ID_PICTURE_ListWall"
#endif  ID_PICTURE_ListWall
#ifndef ID_BUTTON_Default
#define ID_BUTTON_Default		"ID_BUTTON_Default"
#endif  ID_BUTTON_Default
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_PICTURE_TitleLeft
#define ID_PICTURE_TitleLeft		"ID_PICTURE_TitleLeft"
#endif  ID_PICTURE_TitleLeft
#ifndef ID_PICTURE_TitleRight
#define ID_PICTURE_TitleRight		"ID_PICTURE_TitleRight"
#endif  ID_PICTURE_TitleRight
#ifndef ID_PICTURE_TitleLeftMiddle
#define ID_PICTURE_TitleLeftMiddle		"ID_PICTURE_TitleLeftMiddle"
#endif  ID_PICTURE_TitleLeftMiddle
#ifndef ID_PICTURE_TitleRightMiddle
#define ID_PICTURE_TitleRightMiddle		"ID_PICTURE_TitleRightMiddle"
#endif  ID_PICTURE_TitleRightMiddle
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close
#ifndef ID_BUTTON_Help
#define ID_BUTTON_Help		"ID_BUTTON_Help"
#endif  ID_BUTTON_Help
#ifndef ID_LIST_SettingList
#define ID_LIST_SettingList		"ID_LIST_SettingList"
#endif  ID_LIST_SettingList
#ifndef ID_CHECKBOX_Game
#define ID_CHECKBOX_Game		"ID_CHECKBOX_Game"
#endif  ID_CHECKBOX_Game
#ifndef ID_CHECKBOX_System
#define ID_CHECKBOX_System		"ID_CHECKBOX_System"
#endif  ID_CHECKBOX_System

enum eGameSettingUICategory
{
	eGameSetting_Self = 0,	// 自身信息
	eGameSetting_Player,	// 其他玩家信息
	eGameSetting_Scene,		// npc及场景
	eGameSetting_Function,
	eGameSetting_Mouse,
	eGameSetting_Sound,
    eGameSetting_Refuse,
	eGameSetting_Sell,
	//eGameSetting_Tab,
	eGameSetting_Count
};

enum eSettingTab    // 标签
{
    eSettingTab_Game = 0,
    eSettingTab_Setting
};

#include "UiBase.h"
class CUI_ID_FRAME_GameSettingUIBase :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GameSettingUIBase();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_HelpOnButtonClick( ControlObject* pSender );
	void ID_LIST_SettingListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_GameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SystemOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	ControlFrame* GetFrame() { return m_pID_FRAME_GameSettingUIBase; }
	void			AddGroupSystemSetting(ControlObject* pObject){m_GroupSystemSetting.AddControl(pObject);}
	void SetVisibleFrame( eGameSettingUICategory eCat );
	void RefreshUI();
	static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

protected:
	void  FillFrameList();
    unsigned char m_shLastSelectTab;        // 见enum eSettingTab定义
    unsigned char m_shLastSelectCategory;   // 见enum eGameSettingUICategory定义

private:
    ControlFrame*	m_pID_FRAME_GameSettingUIBase;
    //ControlPicture*	m_pID_PICTURE_TitleMiddle;
    ControlPicture*	m_pID_PICTURE_Title;
    ControlPicture*	m_pID_PICTURE_ListWall;
    ControlButton*	m_pID_BUTTON_Default;
    ControlButton*	m_pID_BUTTON_Ok;
    ControlButton*	m_pID_BUTTON_Cancel;
//     ControlPicture*	m_pID_PICTURE_TitleLeft;
//     ControlPicture*	m_pID_PICTURE_TitleRight;
//     ControlPicture*	m_pID_PICTURE_TitleLeftMiddle;
//     ControlPicture*	m_pID_PICTURE_TitleRightMiddle;
    ControlButton*	m_pID_BUTTON_Close;
   // ControlButton*	m_pID_BUTTON_Help;
    ControlList*	m_pID_LIST_SettingList;
    ControlCheckBox*	m_pID_CHECKBOX_Game;
    ControlCheckBox*	m_pID_CHECKBOX_System;

    ControlRadioGroup  m_SettingRadioGroup;
    ControlGroup	m_GroupGameSetting;
    ControlGroup	m_GroupSystemSetting;
    CUIBase*		m_FrameGroup[eGameSetting_Count];
    std::string	m_FrameName[eGameSetting_Count];
};
extern CUI_ID_FRAME_GameSettingUIBase s_CUI_ID_FRAME_GameSettingUIBase;
