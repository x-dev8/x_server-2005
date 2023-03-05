/********************************************************************
Created by UIEditor.exe
FileName: F:\workspace\ShenWang\Hero\Program\trunk\Client\Bin\Data\Ui\HideGroupMe.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_HideGroupMe
#define ID_FRAME_HideGroupMe		"ID_FRAME_HideGroupMe"
#endif  ID_FRAME_HideGroupMe
#ifndef ID_BUTTON_Hide
#define ID_BUTTON_Hide		"ID_BUTTON_Hide"
#endif  ID_BUTTON_Hide
#ifndef ID_BUTTON_Appear
#define ID_BUTTON_Appear		"ID_BUTTON_Appear"
#endif  ID_BUTTON_Appear

#include "UiBase.h"
class CUI_ID_FRAME_HideGroupMe :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_HideGroupMe();
	ControlFrame*	m_pID_FRAME_HideGroupMe;
	ControlButton*	m_pID_BUTTON_Hide;
	ControlButton*	m_pID_BUTTON_Appear;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HideOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AppearOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
public:
};
extern CUI_ID_FRAME_HideGroupMe s_CUI_ID_FRAME_HideGroupMe;
