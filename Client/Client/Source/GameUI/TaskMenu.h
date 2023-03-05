/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\TaskMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_TaskMenu
#define ID_FRAME_TaskMenu		"ID_FRAME_TaskMenu"
#endif  ID_FRAME_TaskMenu
#ifndef ID_BUTTON_Task
#define ID_BUTTON_Task		"ID_BUTTON_Task"
#endif  ID_BUTTON_Task
#ifndef ID_BUTTON_Activity
#define ID_BUTTON_Activity		"ID_BUTTON_Activity"
#endif  ID_BUTTON_Activity
#ifndef ID_BUTTON_Entrust
#define ID_BUTTON_Entrust		"ID_BUTTON_Entrust"
#endif  ID_BUTTON_Entrust
#ifndef ID_BUTTON_Hunting
#define ID_BUTTON_Hunting		"ID_BUTTON_Hunting"
#endif  ID_BUTTON_Hunting

class CUI_ID_FRAME_TaskMenu : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_TaskMenu();
	virtual ~CUI_ID_FRAME_TaskMenu();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_TaskOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ActivityOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_EntrustOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HuntingOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����

	void RefreshHotKey();

private:	
	 ControlFrame*	m_pID_FRAME_TaskMenu;
	 ControlButton*	m_pID_BUTTON_Task;
	 ControlButton*	m_pID_BUTTON_Activity;
	 ControlButton*	m_pID_BUTTON_Entrust;
	 ControlButton*	m_pID_BUTTON_Hunting;
};
extern CUI_ID_FRAME_TaskMenu s_CUI_ID_FRAME_TaskMenu;
