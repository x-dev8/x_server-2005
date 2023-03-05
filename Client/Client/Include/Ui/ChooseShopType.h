/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\tian.peng\����\��̯UI\��̯UI\ChooseShopType.h
*********************************************************************/

/*----------------------------------------------------------
desc	: ��̯����ѡ�����, ѡ������/���߰�̯	
author	: zilong
version	: 1.0
date	: 2011-03-22
revision:
----------------------------------------------------------*/

#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_ChooseShopType
#define ID_FRAME_ChooseShopType		"ID_FRAME_ChooseShopType"
#endif  ID_FRAME_ChooseShopType
#ifndef ID_BUTTON_Online
#define ID_BUTTON_Online		"ID_BUTTON_Online"
#endif  ID_BUTTON_Online
#ifndef ID_BUTTON_Leave
#define ID_BUTTON_Leave		"ID_BUTTON_Leave"
#endif  ID_BUTTON_Leave
#ifndef ID_TEXT_Tip
#define ID_TEXT_Tip		"ID_TEXT_Tip"
#endif  ID_TEXT_Tip

#include "UIBase.h"
class CUI_ID_FRAME_ChooseShopType: public CUIBase
{
public:
	typedef void (*callfun)(bool flag);
	// Member
public:	
	 CUI_ID_FRAME_ChooseShopType();
	 ControlFrame*	m_pID_FRAME_ChooseShopType;
	 ControlButton*	m_pID_BUTTON_Online;
	 ControlButton*	m_pID_BUTTON_Leave;
	 ControlText*	m_pID_TEXT_Tip;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OnlineOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LeaveOnButtonClick( ControlObject* pSender );

	void Show(callfun pf);

private:
	bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	bool _UnLoadUI();			// ж��UI
	bool _IsVisable();			// �Ƿ�ɼ�
	void _SetVisable( const bool bVisable );			// �����Ƿ����

private:
	callfun m_pCallFun;
};
extern CUI_ID_FRAME_ChooseShopType s_CUI_ID_FRAME_ChooseShopType;
