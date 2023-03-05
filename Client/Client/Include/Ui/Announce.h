/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\Announce.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Announce
#define ID_FRAME_Announce		"ID_FRAME_Announce"
#endif  ID_FRAME_Announce
#ifndef ID_EDIT_Info
#define ID_EDIT_Info		"ID_EDIT_Info"
#endif  ID_EDIT_Info
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_BUTTON_Save
#define ID_BUTTON_Save		"ID_BUTTON_Save"
#endif  ID_BUTTON_Save
#ifndef ID_BUTTON_Restart
#define ID_BUTTON_Restart		"ID_BUTTON_Restart"
#endif  ID_BUTTON_Restart
#ifndef ID_TEXT_Msg
#define ID_TEXT_Msg "ID_TEXT_Msg"
#endif  ID_TEXT_Msg


#include "UiBase.h"
class CUI_ID_FRAME_Announce :public CUIBase
{
public:
	enum EDlgType
	{
		E_Type_Announcement = 0,	//公告
		E_Type_Creed,	//宗旨
	};

	// Member
public:	
	 CUI_ID_FRAME_Announce();
private:
	 ControlFrame*	m_pID_FRAME_Announce;
	 ControlEdit*	m_pID_EDIT_Info;
	 ControlButton*	m_pID_BUTTON_Cancel;
// 	 ControlButton*	m_pID_BUTTON_CLOSE;
// 	 ControlButton*	m_pID_BUTTON_help;
	 ControlButton*	m_pID_BUTTON_Save;
	 ControlButton*	m_pID_BUTTON_Restart;
	 ControlText*	m_pID_TEXT_Msg;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_InfoOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SaveOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RestartOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	void SetDlgType(EDlgType type_){m_dlgType = type_;}
	void Refresh(void);
	void SendMsg_ChangeGuild(const char *content_);

	bool EditInputIsVisable();
	void SetGang(bool gang) { m_bGang = gang; }
private:
	bool m_bGang;

	EDlgType m_dlgType;
	int	m_MaxLength;
};
extern CUI_ID_FRAME_Announce s_CUI_ID_FRAME_Announce;

//发送更改公告的消息
bool SendMsg_ChangeGuildAnnouncement(const char *content_);
//发送更改宗旨的消息
bool SendMsg_ChangeGuildCreed(const char *content_);
