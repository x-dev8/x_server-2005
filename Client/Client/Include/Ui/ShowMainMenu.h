/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\ShowMainMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_ShowMainMenu
#define ID_FRAME_ShowMainMenu		"ID_FRAME_ShowMainMenu"
#endif  ID_FRAME_ShowMainMenu
#ifndef ID_BUTTON_Show
#define ID_BUTTON_Show		"ID_BUTTON_Show"
#endif  ID_BUTTON_Show
#ifndef ID_BUTTON_Hide
#define ID_BUTTON_Hide		"ID_BUTTON_Hide"
#endif  ID_BUTTON_Hide

class CUI_ID_FRAME_ShowMainMenu : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_ShowMainMenu();
	virtual ~CUI_ID_FRAME_ShowMainMenu();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_ShowOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HideOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();

	void ShowButton();
	void Refresh();

private:	
	 ControlFrame*	m_pID_FRAME_ShowMainMenu;
	 ControlButton*	m_pID_BUTTON_Show;
	 ControlButton*	m_pID_BUTTON_Hide;

	 bool m_bShow;
};
extern CUI_ID_FRAME_ShowMainMenu s_CUI_ID_FRAME_ShowMainMenu;
