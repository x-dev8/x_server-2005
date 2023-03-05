/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (13)\FamilyMessageBox.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GUILD_FamilyMessageBox
#define ID_FRAME_GUILD_FamilyMessageBox		"ID_FRAME_GUILD_FamilyMessageBox"
#endif  ID_FRAME_GUILD_FamilyMessageBox
#ifndef ID_BUTTON_CREATE
#define ID_BUTTON_CREATE		"ID_BUTTON_CREATE"
#endif  ID_BUTTON_CREATE
#ifndef ID_BUTTON_close
#define ID_BUTTON_close		"ID_BUTTON_close"
#endif  ID_BUTTON_close
#ifndef ID_TEXT_Info1
#define ID_TEXT_Info1		"ID_TEXT_Info1"
#endif  ID_TEXT_Info1
#ifndef ID_TEXT_FamilyName
#define ID_TEXT_FamilyName		"ID_TEXT_FamilyName"
#endif  ID_TEXT_FamilyName
#ifndef ID_TEXT_Info2
#define ID_TEXT_Info2		"ID_TEXT_Info2"
#endif  ID_TEXT_Info2
#ifndef ID_TEXT_PlayerName
#define ID_TEXT_PlayerName		"ID_TEXT_PlayerName"
#endif  ID_TEXT_PlayerName
#ifndef ID_TEXT_Info3
#define ID_TEXT_Info3		"ID_TEXT_Info3"
#endif  ID_TEXT_Info3
#ifndef ID_TEXT_Info4
#define ID_TEXT_Info4		"ID_TEXT_Info4"
#endif  ID_TEXT_Info4
#ifndef ID_TEXT_Message
#define ID_TEXT_Message		"ID_TEXT_Message"
#endif  ID_TEXT_Message

#ifndef ID_BUTTON_Agree
#define ID_BUTTON_Agree		"ID_BUTTON_Agree"
#endif  ID_BUTTON_Agree
#ifndef ID_BUTTON_Refuse
#define ID_BUTTON_Refuse		"ID_BUTTON_Refuse"
#endif  ID_BUTTON_Refuse

#include "UIBase.h"

class CUI_ID_FRAME_GUILD_FamilyMessageBox : public CUIBase
{
	enum MsgVierwType
	{
		eVT_ModifyNote = 0,		//修改公告
		eVT_RequestMsgSend,		//申请加入家族留言
		eVT_RequestMsgRev,		//接到申请留言
		eVT_MAX
	};
	// Member
public:	
	 CUI_ID_FRAME_GUILD_FamilyMessageBox();
	 ControlFrame*	m_pID_FRAME_GUILD_FamilyMessageBox;
	 ControlButton*	m_pID_BUTTON_CREATE;
	 ControlButton*	m_pID_BUTTON_close;
	 ControlText*	m_pID_TEXT_Info1;
	 ControlText*	m_pID_TEXT_FamilyName;
	 ControlText*	m_pID_TEXT_Info2;
	 ControlText*	m_pID_TEXT_PlayerName;
	 ControlText*	m_pID_TEXT_Info3;
	 ControlText*	m_pID_TEXT_Info4;
	 ControlEdit*	m_pID_TEXT_Message;

	 ControlButton*	m_pID_BUTTON_Agree;
	 ControlButton*	m_pID_BUTTON_Refuse;


public:
	bool    EditInputIsVisable();
	

	 //ui相关
public:
	void HideAllCaption();
	void ShowAsModifyNote();	//修改公告视图
	void ShowAsRequestMsgSend();
	void ShowAsRequestMsgRev();

	void ShowOkCancelButton();
	void ShowAcceptRefuseButton();

public:
	void SetRequestFamilyInfo( unsigned int familyId, const char* familyName );
	void SetRequestPlayerInfo( unsigned int playerDbid, const char* playerName, const char* note );

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CREATEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_closeOnButtonClick( ControlObject* pSender );
	void ID_TEXT_MessageOnEditEnter( ControlObject* pSender, const char* szData );

	bool ID_BUTTON_AgreeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RefuseOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
private:	
	MsgVierwType m_eVierwType;

	// for request...
	unsigned int m_nFamilyID;		// 玩家请求需要的信息
	std::string  m_szFamilyName;

	unsigned int m_nPlayerDBID;		// 族长回应所需要的信息
	std::string  m_szPlayerName;
	std::string  m_szNote;
};
extern CUI_ID_FRAME_GUILD_FamilyMessageBox s_CUI_ID_FRAME_GUILD_FamilyMessageBox;
