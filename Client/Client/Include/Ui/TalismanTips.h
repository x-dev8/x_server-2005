/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\����\������Դ\����\����\TalismanTips.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_TalismanTips
#define ID_FRAME_TalismanTips		"ID_FRAME_TalismanTips"
#endif  ID_FRAME_TalismanTips
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_TEXT_Remark
#define ID_TEXT_Remark		"ID_TEXT_Remark"
#endif  ID_TEXT_Remark
#ifndef ID_TEXT_Attribute
#define ID_TEXT_Attribute		"ID_TEXT_Attribute"
#endif  ID_TEXT_Attribute
#ifndef ID_BUTTON_Confirm
#define ID_BUTTON_Confirm		"ID_BUTTON_Confirm"
#endif  ID_BUTTON_Confirm

class CUI_ID_FRAME_TalismanTips : public CUIBase
{
public:
	CUI_ID_FRAME_TalismanTips();
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_TalismanTips;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlText*	m_pID_TEXT_Remark;
	 ControlText*	m_pID_TEXT_Attribute;
	 ControlButton*	m_pID_BUTTON_Confirm;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ConfirmOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
private:	
};
extern CUI_ID_FRAME_TalismanTips s_CUI_ID_FRAME_TalismanTips;
