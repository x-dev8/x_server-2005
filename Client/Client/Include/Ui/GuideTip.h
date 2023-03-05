/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\����\GuideTip.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_GuideTip
#define ID_FRAME_GuideTip		"ID_FRAME_GuideTip"
#endif  ID_FRAME_GuideTip
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_CHECKBOX_ShowAgain
#define ID_CHECKBOX_ShowAgain		"ID_CHECKBOX_ShowAgain"
#endif  ID_CHECKBOX_ShowAgain

class CUI_ID_FRAME_GuideTip : public CUIBase
{
private:	
	 ControlFrame*	    m_pID_FRAME_GuideTip;
	 ControlText*	    m_pID_TEXT_Info;
	 ControlButton*	    m_pID_BUTTON_CLOSE;
	 ControlCheckBox*	m_pID_CHECKBOX_ShowAgain;

public:
    CUI_ID_FRAME_GuideTip();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_ShowAgainOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

    void ShowPopInfo( int iStringId );

private:
	bool _LoadUI();				    // ����UI
	bool DoControlConnect();	    // �����ؼ�
	bool _UnLoadUI();			    // ж��UI
	bool _IsVisable();			    // �Ƿ�ɼ�
	void _SetVisable( const bool bVisable );			// �����Ƿ����

    void ResetMembers();

};

extern CUI_ID_FRAME_GuideTip s_CUI_ID_FRAME_GuideTip;
