/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\保护设置\Protect.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Protect
#define ID_FRAME_Protect		"ID_FRAME_Protect"
#endif  ID_FRAME_Protect
#ifndef ID_PICTURE_TitleWall
#define ID_PICTURE_TitleWall		"ID_PICTURE_TitleWall"
#endif  ID_PICTURE_TitleWall
#ifndef ID_CHECKBOX_ProtectSet
#define ID_CHECKBOX_ProtectSet		"ID_CHECKBOX_ProtectSet"
#endif  ID_CHECKBOX_ProtectSet
#ifndef ID_CHECKBOX_PkSet
#define ID_CHECKBOX_PkSet		"ID_CHECKBOX_PkSet"
#endif  ID_CHECKBOX_PkSet
#ifndef ID_PICTURE_Wall
#define ID_PICTURE_Wall		"ID_PICTURE_Wall"
#endif  ID_PICTURE_Wall
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_All
#define ID_TEXT_All		"ID_TEXT_All"
#endif  ID_TEXT_All
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_PICTURE_22476
#define ID_PICTURE_22476		"ID_PICTURE_22476"
#endif  ID_PICTURE_22476
#ifndef ID_PICTURE_28008
#define ID_PICTURE_28008		"ID_PICTURE_28008"
#endif  ID_PICTURE_28008
#ifndef ID_PICTURE_27628
#define ID_PICTURE_27628		"ID_PICTURE_27628"
#endif  ID_PICTURE_27628
#ifndef ID_PICTURE_20101
#define ID_PICTURE_20101		"ID_PICTURE_20101"
#endif  ID_PICTURE_20101
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close
#ifndef ID_BUTTON_Help
#define ID_BUTTON_Help		"ID_BUTTON_Help"
#endif  ID_BUTTON_Help
#ifndef ID_PICTURE_18290
#define ID_PICTURE_18290		"ID_PICTURE_18290"
#endif  ID_PICTURE_18290
#ifndef ID_LIST_ProtectInfo
#define ID_LIST_ProtectInfo		"ID_LIST_ProtectInfo"
#endif  ID_LIST_ProtectInfo
#ifndef ID_PICTURE_Wall3
#define ID_PICTURE_Wall3		"ID_PICTURE_Wall3"
#endif  ID_PICTURE_Wall3
#ifndef ID_EDIT_Time
#define ID_EDIT_Time		"ID_EDIT_Time"
#endif  ID_EDIT_Time
#ifndef ID_TEXT_Min
#define ID_TEXT_Min		"ID_TEXT_Min"
#endif  ID_TEXT_Min
#ifndef ID_TEXT_TimeWord
#define ID_TEXT_TimeWord		"ID_TEXT_TimeWord"
#endif  ID_TEXT_TimeWord
#ifndef ID_TEXT_Time
#define ID_TEXT_Time		"ID_TEXT_Time"
#endif  ID_TEXT_Time

#include "UiBase.h"
class CUI_ID_FRAME_Protect :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_Protect();
private:
	void ResetMembers();
	ControlFrame*	    m_pID_FRAME_Protect;
	//ControlPicture*	m_pID_PICTURE_TitleWall;
	ControlCheckBox*	m_pID_CHECKBOX_ProtectSet;
	ControlCheckBox*	m_pID_CHECKBOX_PkSet;
	ControlPicture*		m_pID_PICTURE_Wall;
	ControlButton*		m_pID_BUTTON_Ok;
	ControlButton*		m_pID_BUTTON_Cancel;
	ControlText*		m_pID_TEXT_All;
	
//	ControlButton*		m_pID_BUTTON_Close;
	ControlPicture*		m_pID_PICTURE_18290;
	ControlList*		m_pID_LIST_ProtectInfo;
	ControlPicture*		m_pID_PICTURE_Wall3;
	ControlEdit*		m_pID_EDIT_Time;
	ControlText*		m_pID_TEXT_Min;
	ControlText*		m_pID_TEXT_TimeWord;
	ControlText*		m_pID_TEXT_Time;
	ControlRadioGroup	m_SettingTypeRadioGroup;
	ControlGroup		m_ProtectSetGroup;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_ProtectSetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PkSetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_HelpOnButtonClick( ControlObject* pSender );
	void ID_LIST_ProtectInfoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_EDIT_TimeOnEditEnter( ControlObject* pSender, const char* szData );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void SetChangeTimeSuccess() {if( m_shChangeTime >= 0 ) m_shProtectTime = m_shChangeTime;}
	short GetProtectTime() {return m_shProtectTime;}

private:
    void ToggleProtectSet();
    void TogglePkSet();

    void SetProtectTime( short time ) {m_shProtectTime = time;}

	void InitProtectInfoList();

    void UpdateProtectTimeCountDown();
    bool m_bInited;
    short m_shProtectTime;  // 保护时间（分钟）
    short m_shChangeTime;   // 提交的新的保护时间
};
extern CUI_ID_FRAME_Protect s_CUI_ID_FRAME_Protect;
