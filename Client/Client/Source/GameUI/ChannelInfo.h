/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_02.05\Data\Ui\ChannelInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_ChannelInfo
#define ID_FRAME_ChannelInfo		"ID_FRAME_ChannelInfo"
#endif  ID_FRAME_ChannelInfo
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_BUTTON_Change
#define ID_BUTTON_Change		"ID_BUTTON_Change"
#endif  ID_BUTTON_Change

class CUI_ID_FRAME_ChannelInfo : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_ChannelInfo();
	virtual ~CUI_ID_FRAME_ChannelInfo();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_ChangeOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����

	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();

	void ShowChannelName();

private:	
	 ControlFrame*	m_pID_FRAME_ChannelInfo;
	 ControlText*	m_pID_TEXT_Name;
	 ControlButton*	m_pID_BUTTON_Change;
};
extern CUI_ID_FRAME_ChannelInfo s_CUI_ID_FRAME_ChannelInfo;
