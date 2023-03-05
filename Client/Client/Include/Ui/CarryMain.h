/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\载具\载具\CarryMain.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "ItemDetail.h"

#ifndef ID_FRAME_CarryMain
#define ID_FRAME_CarryMain		"ID_FRAME_CarryMain"
#endif  ID_FRAME_CarryMain
#ifndef ID_LISTIMG_Hotkey
#define ID_LISTIMG_Hotkey		"ID_LISTIMG_Hotkey"
#endif  ID_LISTIMG_Hotkey
#ifndef ID_PROGRESS_EXP
#define ID_PROGRESS_EXP		"ID_PROGRESS_EXP"
#endif  ID_PROGRESS_EXP
#ifndef ID_BUTTON_Live
#define ID_BUTTON_Live		"ID_BUTTON_Live"
#endif  ID_BUTTON_Live

class CUI_ID_FRAME_CarryMain : public CUIBase
{
	// Member
public:
	 CUI_ID_FRAME_CarryMain();
private:	
	 ControlFrame*	m_pID_FRAME_CarryMain;
	 ControlListImage*	m_pID_LISTIMG_Hotkey;
	 ControlProgress*	m_pID_PROGRESS_EXP;
	 ControlButton*	m_pID_BUTTON_Live;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_LISTIMG_HotkeyOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_HotkeyOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_HotkeyOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_HotkeyOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_LiveOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	void SetModelId(int nID){m_nMountID = nID;}
	bool UseSkill(ControlIconDrag::S_ListImg* pItem);

	void UpdateCD();
	bool ClickHotkey( int nKeyIndex);
private:
	int  m_nMountID;
};
extern CUI_ID_FRAME_CarryMain s_CUI_ID_FRAME_CarryMain;
