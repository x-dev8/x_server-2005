/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (13)\FamilyMoney.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GUILD_FamilyMoney
#define ID_FRAME_GUILD_FamilyMoney		"ID_FRAME_GUILD_FamilyMoney"
#endif  ID_FRAME_GUILD_FamilyMoney
#ifndef ID_BUTTON_CREATE
#define ID_BUTTON_CREATE		"ID_BUTTON_CREATE"
#endif  ID_BUTTON_CREATE
#ifndef ID_BUTTON_close
#define ID_BUTTON_close		"ID_BUTTON_close"
#endif  ID_BUTTON_close
#ifndef ID_EDIT_Jin
#define ID_EDIT_Jin		"ID_EDIT_Jin"
#endif  ID_EDIT_Jin
#ifndef ID_EDIT_Yin
#define ID_EDIT_Yin		"ID_EDIT_Yin"
#endif  ID_EDIT_Yin
#ifndef ID_EDIT_Tong
#define ID_EDIT_Tong		"ID_EDIT_Tong"
#endif  ID_EDIT_Tong

#include "UIBase.h"

class CUI_ID_FRAME_GUILD_FamilyMoney : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GUILD_FamilyMoney();
	 ControlFrame*	m_pID_FRAME_GUILD_FamilyMoney;
	 ControlButton*	m_pID_BUTTON_CREATE;
	 ControlButton*	m_pID_BUTTON_close;
	 ControlEdit*	m_pID_EDIT_Jin;
	 ControlEdit*	m_pID_EDIT_Yin;
	 ControlEdit*	m_pID_EDIT_Tong;

public:
	bool    EditInputIsVisable();

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_closeOnButtonClick( ControlObject* pSender );
	void ID_EDIT_JinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_YinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_TongOnEditEnter( ControlObject* pSender, const char* szData );

public:
	void CheckInput();

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();			// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
private:	
};
extern CUI_ID_FRAME_GUILD_FamilyMoney s_CUI_ID_FRAME_GUILD_FamilyMoney;
