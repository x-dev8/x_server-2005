/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\HelpRemend.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_HelpRemend
#define ID_FRAME_HelpRemend		"ID_FRAME_HelpRemend"
#endif  ID_FRAME_HelpRemend
#ifndef ID_BUTTON_1
#define ID_BUTTON_1		"ID_BUTTON_1"
#endif  ID_BUTTON_1
#ifndef ID_BUTTON_2
#define ID_BUTTON_2		"ID_BUTTON_2"
#endif  ID_BUTTON_2
#ifndef ID_BUTTON_3
#define ID_BUTTON_3		"ID_BUTTON_3"
#endif  ID_BUTTON_3
#ifndef ID_BUTTON_4
#define ID_BUTTON_4		"ID_BUTTON_4"
#endif  ID_BUTTON_4
#ifndef ID_BUTTON_5
#define ID_BUTTON_5		"ID_BUTTON_5"
#endif  ID_BUTTON_5

class CUI_ID_FRAME_HelpRemend
{
	// Member
public:	
	 CUI_ID_FRAME_HelpRemend();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_3OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_4OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_5OnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


    void RefreshButtonTips();

private:


	ControlButton*	m_arrButton[5];	
	RECT			rcButton[5];

    ControlFrame*	m_pID_FRAME_HelpRemend;
    ControlButton*	m_pID_BUTTON_1;
    ControlButton*	m_pID_BUTTON_2;
    ControlButton*	m_pID_BUTTON_3;
    ControlButton*	m_pID_BUTTON_4;
    ControlButton*	m_pID_BUTTON_5;

};
extern CUI_ID_FRAME_HelpRemend s_CUI_ID_FRAME_HelpRemend;
