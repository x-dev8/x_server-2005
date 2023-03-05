/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Fcm.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Fcm
#define ID_FRAME_Fcm		"ID_FRAME_Fcm"
#endif  ID_FRAME_Fcm
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Msg
#define ID_TEXT_Msg		"ID_TEXT_Msg"
#endif  ID_TEXT_Msg

#include "UiBase.h"
class CUI_ID_FRAME_Fcm :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_Fcm();
private:
	 ControlFrame*	m_pID_FRAME_Fcm;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_Msg;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
public:

};
extern CUI_ID_FRAME_Fcm s_CUI_ID_FRAME_Fcm;
