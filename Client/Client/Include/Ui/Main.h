/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Main.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "MsgBase.h"
#ifndef ID_FRAME_MAIN
#define ID_FRAME_MAIN		"ID_FRAME_MAIN"
#endif  ID_FRAME_MAIN
#ifndef ID_BUTTON_Function
#define ID_BUTTON_Function		"ID_BUTTON_Function"
#endif  ID_BUTTON_Function
#ifndef ID_BUTTON_FightState
#define ID_BUTTON_FightState		"ID_BUTTON_FightState"
#endif  ID_BUTTON_FightState
#ifndef ID_LISTIMG_Hotkey
#define ID_LISTIMG_Hotkey		"ID_LISTIMG_Hotkey"
#endif  ID_LISTIMG_Hotkey
#ifndef ID_LISTIMG_Hotkey2
#define ID_LISTIMG_Hotkey2		"ID_LISTIMG_Hotkey2"
#endif  ID_LISTIMG_Hotkey2
#ifndef ID_LISTIMG_Hotkey3
#define ID_LISTIMG_Hotkey3		"ID_LISTIMG_Hotkey3"
#endif  ID_LISTIMG_Hotkey3
#ifndef ID_BUTTON_OUT
#define ID_BUTTON_OUT		"ID_BUTTON_OUT"
#endif  ID_BUTTON_OUT
#ifndef ID_BUTTON_IN
#define ID_BUTTON_IN		"ID_BUTTON_IN"
#endif  ID_BUTTON_IN
#ifndef ID_PICTURE_BG
#define ID_PICTURE_BG		"ID_PICTURE_BG"
#endif  ID_PICTURE_BG
#ifndef ID_BUTTON_Map
#define ID_BUTTON_Map		"ID_BUTTON_Map"
#endif  ID_BUTTON_Map
#ifndef ID_TEXT_Level
#define ID_TEXT_Level			"ID_TEXT_Level"
#endif ID_TEXT_Level
#ifndef ID_CHECKBOX_IsKeybord
#define ID_CHECKBOX_IsKeybord		"ID_CHECKBOX_IsKeybord"
#endif  ID_CHECKBOX_IsKeybord
#ifndef ID_CHECKBOX_Angle
#define ID_CHECKBOX_Angle		"ID_CHECKBOX_Angle"
#endif  ID_CHECKBOX_Angle
#ifndef ID_CHECKBOX_showhotkey
#define ID_CHECKBOX_showhotkey	"ID_CHECKBOX_showhotkey"
#endif ID_CHECKBOX_showhotkey
#ifndef ID_BUTTON_turnHotkeyUp
#define ID_BUTTON_turnHotkeyUp	"ID_BUTTON_turnHotkeyUp"
#endif ID_BUTTON_turnHotkeyUp
#ifndef ID_BUTTON_turnHotkeyDown
#define ID_BUTTON_turnHotkeyDown	"ID_BUTTON_turnHotkeyDown"
#endif ID_BUTTON_turnHotkeyDown
#ifndef ID_TEXT_Num
#define ID_TEXT_Num	"ID_TEXT_Num"
#endif ID_TEXT_Num
#ifndef ID_BUTTON_ShowExmain
#define ID_BUTTON_ShowExmain		"ID_BUTTON_ShowExmain"
#endif  ID_BUTTON_ShowExmain
#ifndef ID_PROGRESS_EXP
#define ID_PROGRESS_EXP		"ID_PROGRESS_EXP"
#endif  ID_PROGRESS_EXP
#ifndef ID_TEXT_EXP
#define ID_TEXT_EXP		"ID_TEXT_EXP"
#endif  ID_TEXT_EXP

//进入太平幻境的按钮
#ifndef ID_BUTTON_Enter
#define ID_BUTTON_Enter	"ID_BUTTON_Enter"
#endif	ID_BUTTON_Enter
#ifndef ID_BUTTON_LevelUp
#define	ID_BUTTON_LevelUp	"ID_BUTTON_LevelUp"
#endif	ID_BUTTON_LevelUp
#ifndef ID_TEXT_LevelUp
#define ID_TEXT_LevelUp		"ID_TEXT_LevelUp"
#endif  ID_TEXT_LevelUp

#ifndef ID_CHECKBOX_HideChatList
#define ID_CHECKBOX_HideChatList		"ID_CHECKBOX_HideChatList"
#endif  ID_CHECKBOX_HideChatList

#include "UIBase.h"
struct SCharSkill;
class CUI_ID_FRAME_MAIN :public CUIBase 
{
	// SGuildMember
public:	
	// Frame
	CUI_ID_FRAME_MAIN();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_FunctionOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FightStateOnButtonClick( ControlObject* pSender );

	bool ID_LISTIMG_HotkeyOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_HotkeyOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_HotkeyOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_BUTTON_OUTOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_INOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MapOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_turnHotkeyUpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_turnHotkeyDownOnButtonClick( ControlObject* pSender );
	
	void ID_CHECKBOX_AngleOnClick(ControlObject* pSender, bool* pbChecked);
	void ID_CHECKBOX_IsKeybordOnClick(ControlObject* pSender, bool* pbChecked);
	void ID_CHECKBOX_showbotkeyOnClick(ControlObject* pSender, bool* pbChecked);
	bool ID_BUTTON_ShowExmainOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_HideChatListOnClick(ControlObject* pSender, bool* pbChecked);

	bool ID_LISTIMG_HotkyeOnIconDisableDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_HotkyeOnIconDisableDragOut( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	bool ID_BUTTON_EnterOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LevelUpOnButtonClick( ControlObject* pSender );
	bool ID_TEXT_LevelUpOnButtonClick( ControlObject* pSender );

	virtual bool IsHoldInMemory() const { return true; }
    virtual void InitializeAtEnterWorld();
	
private:
	virtual bool _LoadUI();				// 载入UI6
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	void RefeashHotKey();
    static void useSkill( int index, bool bMouse = false, bool bIconEnable = true );

public: //---针对m_pID_LISTIMG_Hotkey
    ControlFrame*     GetFrame(){return m_pID_FRAME_MAIN;}
    ControlListImage* GetHotKeyListImage();
    int               GetHotKeyListImageIndex(ControlIconDrag::S_ListImg* pImg);
    int               GetHotKeyItemSize();
    ControlIconDrag::S_ListImg* GetHotKeyItemByIndex(int nIndex);
    int               GetHotKey(){return nIndexHotKey;}
    void              SetHotKeyPressIndex(int nIndex);
    bool              IsHotKeyVisable();
    void              SetHotKeyListImageDrag(bool bEnable);

    void RefreshExp();
    void RefeashHotNumber();
    void setHelpWithHtmlExit()	{ return;}
    void SetHotkey(Msg* pMsg);
    void SetFullSceenValue(bool bVaule);
    void setKeyboardChecked();
    void setAngleChecked();
    void Refeash();
	bool ClickHotkey( int nKeyIndex, bool bIconEnable = true );

	static void IconOnShiftLBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

public:
	bool SetSkillAutoToListImage(SCharSkill* pSkill_);
//---------
private:
	void RefreshHotKeyEnableSetting();

	void setIconIndex( int index );

	void iconDargOn(  int nIndexDrag, int nIndexSrc, ControlObject* pSender, ControlObject* pMe,
		ControlIconDrag::S_ListImg* pItemDrag,
		ControlIconDrag::S_ListImg* pItemSrc );

	void UpdateIconInfo();
	BOOL FunctionBtnOutIn( bool bVis );
	BOOL FunctionBtnIn();

    ControlFrame*	m_pID_FRAME_MAIN;
    ControlButton*	m_pID_BUTTON_Function;
    ControlProgress*	m_pID_PROGRESS_Exp;
    ControlListImage*	m_pID_LISTIMG_Hotkey;
    ControlButton*	m_pID_BUTTON_OUT;
    ControlButton*	m_pID_BUTTON_IN;
    ControlPicture* m_pID_PICTURE_BG;
    ControlButton*	m_pID_BUTTON_Map;
    ControlText*	m_pID_TEXT_Num;
    ControlCheckBox* m_pID_CHECKBOX_Angle;
    ControlCheckBox* m_pID_CHECKBOX_IsKeyboard;
    ControlCheckBox* m_pID_CHECKBOX_showhotkey;
    ControlButton*	m_pID_BUTTON_turnHotkeyUp;
    ControlButton*	m_pID_BUTTON_turnHotkeyDown;
	ControlText*	m_pID_TEXT_EXP;
	ControlButton*  m_pID_BUTTON_Enter;
	ControlButton*	m_pID_BUTTON_LevelUp;
	ControlText*	m_pID_TEXT_LevelUp;

	ControlCheckBox* m_pID_CHECKBOX_HideChatList;

    int				nIndexHotKey;

    bool				bFullScreen;	//保存全屏值 假全屏
};
bool UIMain_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );
extern CUI_ID_FRAME_MAIN s_CUI_ID_FRAME_MAIN;
