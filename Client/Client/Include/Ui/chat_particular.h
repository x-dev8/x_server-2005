/********************************************************************
	Created by UIEditor.exe
	FileName: D:\Tj\Client\UI\chat_particular.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GlobalDef.h"
#include <stdio.h>


#ifndef ID_FRAME_ChatParticular
#define ID_FRAME_ChatParticular		"ID_FRAME_ChatParticular"
#endif  ID_FRAME_ChatParticular
#ifndef ID_TEXT_PromptInfo
#define ID_TEXT_PromptInfo		"ID_TEXT_PromptInfo"
#endif  ID_TEXT_PromptInfo
#ifndef ID_EDIT_ChatInfo
#define ID_EDIT_ChatInfo		"ID_EDIT_ChatInfo"
#endif  ID_EDIT_ChatInfo
#ifndef ID_BUTTON_Send
#define ID_BUTTON_Send		"ID_BUTTON_Send"
#endif  ID_BUTTON_Send

#include "UiBase.h"
class CUI_ID_FRAME_ChatParticular :public CUIBase
{
	// SGuildMember
public:	
	CUI_ID_FRAME_ChatParticular();
private:
	 ControlFrame*	m_pID_FRAME_ChatParticular;
	 ControlText*	m_pID_TEXT_PromptInfo;
	 ControlEdit*	m_pID_EDIT_ChatInfo;
	 ControlButton*	m_pID_BUTTON_Send;
public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_ChatInfoOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_SendOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void show( AN_S2A_OpenClientUI_Flag flag );
	void sendChatmsgParticular( const char* chat, AN_S2A_OpenClientUI_Flag flag );
	//void addHyberText( const char* text, SCharItem* iteminfo );
	void addHyberText( const char* text, __int64 onlyId = 0, int itemid = 0 );
	void SendMsgChat( const char* szData );

	bool EditInputIsVisable();

	AN_S2A_OpenClientUI_Flag&	getChatFlag()	{  return chatFlag; }

private:
	AN_S2A_OpenClientUI_Flag	chatFlag;

	//SCharItem		_HyberItemInfo[ITEM_HYBER_MAX_CNT];	//保存聊天 物品链接的信息
	__int64						_HyberItemInfo[ITEM_HYBER_MAX_CNT];
	int							_HyberItemId[ITEM_HYBER_MAX_CNT];
	int		ItemHyberCnt;
	std::string					_saveItemHyber[ITEM_HYBER_MAX_CNT];
};

extern CUI_ID_FRAME_ChatParticular s_CUI_ID_FRAME_ChatParticular;
