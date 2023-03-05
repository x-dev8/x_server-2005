/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\游戏设置UI\keyset.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "../shortcutkey_configure.h"

#ifndef ID_FRAME_custom
#define ID_FRAME_custom		"ID_FRAME_custom"
#endif  ID_FRAME_custom
#ifndef ID_PICTURE_grounding
#define ID_PICTURE_grounding		"ID_PICTURE_grounding"
#endif  ID_PICTURE_grounding
#ifndef ID_PICTURE_title_pattern
#define ID_PICTURE_title_pattern		"ID_PICTURE_title_pattern"
#endif  ID_PICTURE_title_pattern
#ifndef ID_PICTURE_title
#define ID_PICTURE_title		"ID_PICTURE_title"
#endif  ID_PICTURE_title
#ifndef ID_PICTURE_pattern
#define ID_PICTURE_pattern		"ID_PICTURE_pattern"
#endif  ID_PICTURE_pattern
#ifndef ID_PICTURE_pattern2
#define ID_PICTURE_pattern2		"ID_PICTURE_pattern2"
#endif  ID_PICTURE_pattern2
#ifndef ID_BUTTON_default
#define ID_BUTTON_default		"ID_BUTTON_default"
#endif  ID_BUTTON_default
#ifndef ID_BUTTON_sure
#define ID_BUTTON_sure		"ID_BUTTON_sure"
#endif  ID_BUTTON_sure
#ifndef ID_BUTTON_cancel
#define ID_BUTTON_cancel		"ID_BUTTON_cancel"
#endif  ID_BUTTON_cancel
#ifndef ID_TEXT_function
#define ID_TEXT_function		"ID_TEXT_function"
#endif  ID_TEXT_function
#ifndef ID_BUTTON_close
#define ID_BUTTON_close		"ID_BUTTON_close"
#endif  ID_BUTTON_close
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
// #ifndef ID_LIST_KeyList
// #define ID_LIST_KeyList		"ID_LIST_KeyList"
// #endif  ID_LIST_KeyList
#ifndef ID_SCROLLBAR_KeyList
#define ID_SCROLLBAR_KeyList		"ID_SCROLLBAR_KeyList"
#endif  ID_SCROLLBAR_KeyList
#ifndef ID_CHECKBOX_CaoZuo
#define ID_CHECKBOX_CaoZuo "ID_CHECKBOX_CaoZuo"
#endif ID_CHECKBOX_CaoZuo
#ifndef ID_CHECKBOX_GongNeng
#define  ID_CHECKBOX_GongNeng "ID_CHECKBOX_GongNeng"
#endif  ID_CHECKBOX_GongNeng
#ifndef ID_CHECKBOX_KuaiJieJian
#define  ID_CHECKBOX_KuaiJieJian "ID_CHECKBOX_KuaiJieJian"
#endif ID_CHECKBOX_KuaiJieJian

#include "UiBase.h"
class CUI_ID_FRAME_custom :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_custom();
private:
	ControlFrame*	m_pID_FRAME_custom;
	ControlPicture*	m_pID_PICTURE_grounding;
	ControlPicture*	m_pID_PICTURE_title_pattern;
	ControlPicture*	m_pID_PICTURE_title;
	ControlPicture*	m_pID_PICTURE_pattern;
	ControlPicture*	m_pID_PICTURE_pattern2;
	ControlButton*	m_pID_BUTTON_default;
	ControlButton*	m_pID_BUTTON_sure;
	ControlButton*	m_pID_BUTTON_cancel;
	ControlText*	m_pID_TEXT_function;
	ControlButton*	m_pID_BUTTON_close;
	ControlButton*	m_pID_BUTTON_help;
	//ControlList*	m_pID_LIST_KeyList;
	ControlScrollBar*	m_pID_SCROLLBAR_KeyList;
	ControlCheckBox* m_pID_CHECKBOX_KuaiJieJian;
	ControlCheckBox* m_pID_CHECKBOX_GongNeng;
	ControlCheckBox* m_pID_CHECKBOX_CaoZuo;
public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_defaultOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_sureOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_cancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_closeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	//void ID_LIST_KeyListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_KeyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GongNengCheck(ControlObject* pSender, bool* pbChecked );
	void ID_CHECKBOX_CaoZuoCheck(ControlObject* pSender, bool* pbChecked );
	void ID_CHECKBOX_KuaiJieJianCheck(ControlObject* pSender, bool* pbChecked );
	void ID_SCROLLBAR_KeyListOnScrollBarUpdatePos( ControlObject* pSender, int n );

public:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void load();

	std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue>&	getTempSaveKeyInfo()
	{
		return _tempSaveKeyInfo;
	}
	int GetSelectedKey() { return m_nSelectedKey; }
private:
	void listCustomUpdata();
	void initTempKeyInfo();
	void setTempSaveKeyInfoItem( int id, const char* value  );
	void updateSelectedKeyInfo();
	const char* GetCheckString();

	std::vector<ControlCheckBox*> m_pID_CHECKBOX_KeyList;
	std::vector<ControlText*> m_pID_TEXT_KeyList;

	int m_nSelectedKey;

	static bool msgCustom( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );



	std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue>	_tempSaveKeyInfo;
};
extern CUI_ID_FRAME_custom s_CUI_ID_FRAME_custom;
