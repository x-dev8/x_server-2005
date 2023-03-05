/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\MiniChat.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_MiniChat
#define ID_FRAME_MiniChat		"ID_FRAME_MiniChat"
#endif  ID_FRAME_MiniChat
#ifndef ID_LIST_List
#define ID_LIST_List		"ID_LIST_List"
#endif  ID_LIST_List

#include "UiBase.h"
class CUI_ID_FRAME_MiniChat :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_MiniChat();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_ListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	static void ID_List_MinilistOnLBClick( ControlObject* pSender, ControlList::S_List* pItem );

	void RefrestListHeight();
	void			AddMiniPlayerListName(const char* pPlayer);
	void			AddRemindPlayer(const char* pPlayer);
	std::list<std::string>					m_MiniPlayerList;//用于正在聊天状态的最小化的列表
	std::list<std::string>					m_MiniRemindPlayerList;
	bool			IsRemindPlayer(const char* pPlayer);
	bool			IsMiniChatPlayer(const char* pPlayer);
	bool			RemoveRemindPlayer(const char* pPlayer);
	void			Clear();
private:
    ControlFrame*	m_pID_FRAME_MiniChat;
    ControlList*	m_pID_LIST_List;
};
extern CUI_ID_FRAME_MiniChat s_CUI_ID_FRAME_MiniChat;
