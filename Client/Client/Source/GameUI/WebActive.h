/********************************************************************
	Created by UIEditor.exe
	FileName: E:\sg_pro\3Guo_Branch\FullClient\Data\Ui\WebActive.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_WebActive
#define ID_FRAME_WebActive		"ID_FRAME_WebActive"
#endif  ID_FRAME_WebActive
#ifndef ID_BUTTON_BTOPEN
#define ID_BUTTON_BTOPEN		"ID_BUTTON_BTOPEN"
#endif  ID_BUTTON_BTOPEN
#include "UiBase.h"
class CUI_ID_FRAME_WebActive:public CUIBase 
{
	// Member
public:	
	CUI_ID_FRAME_WebActive();
	virtual ~CUI_ID_FRAME_WebActive();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_BTOPENOnButtonClick( ControlObject* pSender );

	//bool LoadUI();				// ����UI
	//bool DoControlConnect();	// �����ؼ�
	//bool UnLoadUI();			// ж��UI
	//bool IsVisable();			// �Ƿ�ɼ�
	//void SetVisable( const bool bVisable );			// �����Ƿ����

	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����


	

public:
	virtual bool IsHoldInMemory() const { return true; }

private:	
	 ControlFrame*	m_pID_FRAME_WebActive;
	 ControlButton*	m_pID_BUTTON_BTOPEN;
};
extern CUI_ID_FRAME_WebActive s_CUI_ID_FRAME_WebActive;
