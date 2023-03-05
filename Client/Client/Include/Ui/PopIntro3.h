/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\����\PopIntro3.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_PopIntro3
#define ID_FRAME_PopIntro3		"ID_FRAME_PopIntro3"
#endif  ID_FRAME_PopIntro3
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok

class CUI_ID_FRAME_PopIntro3 :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_PopIntro3();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
private:
	ControlFrame*	m_pID_FRAME_PopIntro3;
	ControlText*	m_pID_TEXT_Info;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlButton*	m_pID_BUTTON_Ok;
public:
	void ShowInfo(int nNpcName,int nStrindInfo);
private:
	std::string m_strNpcName;
};
extern CUI_ID_FRAME_PopIntro3 s_CUI_ID_FRAME_PopIntro3;
