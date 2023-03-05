/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (13)\FamilyUI\FamilyTenet.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GUILD_FamilyTenet
#define ID_FRAME_GUILD_FamilyTenet		"ID_FRAME_GUILD_FamilyTenet"
#endif  ID_FRAME_GUILD_FamilyTenet
#ifndef ID_BUTTON_CREATE
#define ID_BUTTON_CREATE		"ID_BUTTON_CREATE"
#endif  ID_BUTTON_CREATE
#ifndef ID_BUTTON_close
#define ID_BUTTON_close		"ID_BUTTON_close"
#endif  ID_BUTTON_close
#ifndef ID_TEXT_JiaZuZongZhi
#define ID_TEXT_JiaZuZongZhi		"ID_TEXT_JiaZuZongZhi"
#endif  ID_TEXT_JiaZuZongZhi
#ifndef ID_EDIT_ZongZhi
#define ID_EDIT_ZongZhi		"ID_EDIT_ZongZhi"
#endif  ID_EDIT_ZongZhi

#include "UiBase.h"

class CUI_ID_FRAME_GUILD_FamilyTenet : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GUILD_FamilyTenet();
	 ControlFrame*	m_pID_FRAME_GUILD_FamilyTenet;
	 ControlButton*	m_pID_BUTTON_CREATE;
	 ControlButton*	m_pID_BUTTON_close;
	 ControlText*	m_pID_TEXT_JiaZuZongZhi;
	 ControlEdit*	m_pID_EDIT_ZongZhi;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_closeOnButtonClick( ControlObject* pSender );
	void ID_EDIT_ZongZhiOnEditEnter( ControlObject* pSender, const char* szData );

public:
	void UpdateAim();	//更新到基本数据

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	bool    EditInputIsVisable();

private:
	std::string		szNewAim;
};
extern CUI_ID_FRAME_GUILD_FamilyTenet s_CUI_ID_FRAME_GUILD_FamilyTenet;
