/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\ChangeEquip.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_ChangeEquip
#define ID_FRAME_ChangeEquip		"ID_FRAME_ChangeEquip"
#endif  ID_FRAME_ChangeEquip
#ifndef ID_BUTTON_Save
#define ID_BUTTON_Save		"ID_BUTTON_Save"
#endif  ID_BUTTON_Save
#ifndef ID_BUTTON_Delete
#define ID_BUTTON_Delete		"ID_BUTTON_Delete"
#endif  ID_BUTTON_Delete
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close
#ifndef ID_CHECKBOX_1
#define ID_CHECKBOX_1		"ID_CHECKBOX_1"
#endif  ID_CHECKBOX_1
#ifndef ID_CHECKBOX_2
#define ID_CHECKBOX_2		"ID_CHECKBOX_2"
#endif  ID_CHECKBOX_2
#ifndef ID_CHECKBOX_3
#define ID_CHECKBOX_3		"ID_CHECKBOX_3"
#endif  ID_CHECKBOX_3
#ifndef ID_CHECKBOX_4
#define ID_CHECKBOX_4		"ID_CHECKBOX_4"
#endif  ID_CHECKBOX_4
#ifndef ID_CHECKBOX_5
#define ID_CHECKBOX_5		"ID_CHECKBOX_5"
#endif  ID_CHECKBOX_5
#ifndef ID_PICTURE_1
#define ID_PICTURE_1		"ID_PICTURE_1"
#endif  ID_PICTURE_1
#ifndef ID_PICTURE_2
#define ID_PICTURE_2		"ID_PICTURE_2"
#endif  ID_PICTURE_2
#ifndef ID_PICTURE_3
#define ID_PICTURE_3		"ID_PICTURE_3"
#endif  ID_PICTURE_3
#ifndef ID_PICTURE_4
#define ID_PICTURE_4		"ID_PICTURE_4"
#endif  ID_PICTURE_4
#ifndef ID_PICTURE_5
#define ID_PICTURE_5		"ID_PICTURE_5"
#endif  ID_PICTURE_5

#include "UiBase.h"
class CUI_ID_FRAME_ChangeEquip :public CUIBase
{
	// Member
private:
	 ControlFrame*	m_pID_FRAME_ChangeEquip;
	 ControlButton*	m_pID_BUTTON_Save;
// 	 ControlButton*	m_pID_BUTTON_Delete;
// 	 ControlButton*	m_pID_BUTTON_Close;
	 ControlCheckBox*	m_pID_CHECKBOX_1;
	 ControlCheckBox*	m_pID_CHECKBOX_2;
	 ControlCheckBox*	m_pID_CHECKBOX_3;
	 ControlCheckBox*	m_pID_CHECKBOX_4;
	 ControlCheckBox*	m_pID_CHECKBOX_5;
     ControlPicture*	m_pID_PICTURE_1;
     ControlPicture*	m_pID_PICTURE_2;
     ControlPicture*	m_pID_PICTURE_3;
     ControlPicture*	m_pID_PICTURE_4;
     ControlPicture*	m_pID_PICTURE_5;

public:	
	CUI_ID_FRAME_ChangeEquip();

     static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_SaveOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

    //void SetTip(const char* pszWord);
    //void SetRename();

    void Init();
    void SaveSuit(bool bShowInfo = true);
	void SetElapseTime(DWORD time) { s_dwElapseTime = time; }

protected:
	bool IsCoolDowning();
	bool IsCanReplace(int nIndex);
	void ChangeSuit(int nIndex);
	void SetSuit(int nIndex);

	static DWORD s_dwElapseTime;
    int m_CurrSuit;  //当前选中的是第几套装备
    DWORD m_dwCoolDown;  //CD时间
};
extern CUI_ID_FRAME_ChangeEquip s_CUI_ID_FRAME_ChangeEquip;
