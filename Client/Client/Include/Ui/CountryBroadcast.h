/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\����\���ҽ���\CountryBroadcast.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Country.h"

#ifndef ID_FRAME_CountryBroadcast
#define ID_FRAME_CountryBroadcast		"ID_FRAME_CountryBroadcast"
#endif  ID_FRAME_CountryBroadcast
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_Tips
#define ID_TEXT_Tips		"ID_TEXT_Tips"
#endif  ID_TEXT_Tips
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_EDIT_BroadcastText
#define ID_EDIT_BroadcastText		"ID_EDIT_BroadcastText"
#endif  ID_EDIT_BroadcastText

#include "UiBase.h"
class CUI_ID_FRAME_CountryBroadcast :public CUIBase
{
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_CountryBroadcast;
	 ControlText*	m_pID_TEXT_Title;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlText*	m_pID_TEXT_Tips;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlEdit*	m_pID_EDIT_BroadcastText;

public:	
	CUI_ID_FRAME_CountryBroadcast();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	void ID_EDIT_BroadcastTextOnEditEnter( ControlObject* pSender, const char* szData );
	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
public:


	bool EditInputIsVisable();						//���뷨
	void GetBroadcastResult( uint8 result );		//���չ��淢�����

private:	
	std::string		m_strBroadcast;

};
extern CUI_ID_FRAME_CountryBroadcast s_CUI_ID_FRAME_CountryBroadcast;
