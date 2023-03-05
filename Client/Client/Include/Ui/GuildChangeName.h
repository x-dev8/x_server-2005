/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildChangeName.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#ifndef ID_FRAME_GuildChangeName
#define ID_FRAME_GuildChangeName		"ID_FRAME_GuildChangeName"
#endif  ID_FRAME_GuildChangeName
#ifndef ID_EDIT_GuilldName
#define ID_EDIT_GuilldName		"ID_EDIT_GuilldName"
#endif  ID_EDIT_GuilldName
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Canel
#define ID_BUTTON_Canel		"ID_BUTTON_Canel"
#endif  ID_BUTTON_Canel
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
class CUI_ID_FRAME_GuildChangeName : public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_GuildChangeName();
	virtual ~CUI_ID_FRAME_GuildChangeName();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_GuilldNameOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CanelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	virtual bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

private:	
	 ControlFrame*	m_pID_FRAME_GuildChangeName;
	 ControlEdit*	m_pID_EDIT_GuilldName;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Canel;
	 ControlButton*	m_pID_BUTTON_Close;
	 ControlText*	m_pID_TEXT_Info;
};
extern CUI_ID_FRAME_GuildChangeName s_CUI_ID_FRAME_GuildChangeName;
