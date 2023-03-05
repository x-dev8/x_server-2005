/********************************************************************
	Created by UIEditor.exe
	FileName: E:\temp\ChatHistory.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_ChatHistory
#define ID_FRAME_ChatHistory		"ID_FRAME_ChatHistory"
#endif  ID_FRAME_ChatHistory
#ifndef ID_PICTURE_Di
#define ID_PICTURE_Di		"ID_PICTURE_Di"
#endif  ID_PICTURE_Di
#ifndef ID_PICTURE_TitleDi
#define ID_PICTURE_TitleDi		"ID_PICTURE_TitleDi"
#endif  ID_PICTURE_TitleDi
#ifndef ID_PICTURE_title
#define ID_PICTURE_title		"ID_PICTURE_title"
#endif  ID_PICTURE_title
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_BUTTON_Exit
#define ID_BUTTON_Exit		"ID_BUTTON_Exit"
#endif  ID_BUTTON_Exit
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_LIST_FriendName
#define ID_LIST_FriendName		"ID_LIST_FriendName"
#endif  ID_LIST_FriendName
#ifndef ID_LIST_ChatList
#define ID_LIST_ChatList		"ID_LIST_ChatList"
#endif  ID_LIST_ChatList
// #ifndef ID_TEXT_ChatPlayer
// #define ID_TEXT_ChatPlayer		"ID_TEXT_ChatPlayer"
// #endif  ID_TEXT_ChatPlayer
// #ifndef ID_TEXT_ChatTime
// #define ID_TEXT_ChatTime		"ID_TEXT_ChatTime"
// #endif  ID_TEXT_ChatTime
// #ifndef ID_TEXT_Chat
// #define ID_TEXT_Chat		"ID_TEXT_Chat"
// #endif  ID_TEXT_Chat
#ifndef ID_CHECKBOX_Friend
#define ID_CHECKBOX_Friend		"ID_CHECKBOX_Friend"
#endif  ID_CHECKBOX_Friend
#ifndef ID_CHECKBOX_Stranger
#define ID_CHECKBOX_Stranger		"ID_CHECKBOX_Stranger"
#endif  ID_CHECKBOX_Stranger
// #ifndef ID_TEXT_Chat2
// #define ID_TEXT_Chat2		"ID_TEXT_Chat2"
// #endif  ID_TEXT_Chat2
#ifndef ID_BUTTON_Delete
#define ID_BUTTON_Delete		"ID_BUTTON_Delete"
#endif  ID_BUTTON_Delete
// #ifndef ID_TEXT_Detail
// #define ID_TEXT_Detail		"ID_TEXT_Detail"
// #endif  ID_TEXT_Detail
#ifndef ID_BUTTON_LastPage
#define ID_BUTTON_LastPage		"ID_BUTTON_LastPage"
#endif  ID_BUTTON_LastPage
#ifndef ID_BUTTON_FirstPage
#define ID_BUTTON_FirstPage		"ID_BUTTON_FirstPage"
#endif  ID_BUTTON_FirstPage
#ifndef ID_BUTTON_PageDown
#define ID_BUTTON_PageDown		"ID_BUTTON_PageDown"
#endif  ID_BUTTON_PageDown
#ifndef ID_BUTTON_PageUp
#define ID_BUTTON_PageUp		"ID_BUTTON_PageUp"
#endif  ID_BUTTON_PageUp
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_EDIT_Search
#define ID_EDIT_Search		"ID_EDIT_Search"
#endif  ID_EDIT_Search
#ifndef ID_BUTTON_Next
#define ID_BUTTON_Next		"ID_BUTTON_Next"
#endif  ID_BUTTON_Next
#ifndef ID_COMBOBOX_Search
#define ID_COMBOBOX_Search		"ID_COMBOBOX_Search"
#endif  ID_COMBOBOX_Search

#include "UiBase.h"
class CUI_ID_FRAME_ChatHistory :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_ChatHistory();
private:
	 ControlFrame*	m_pID_FRAME_ChatHistory;
	 //ControlPicture*	m_pID_PICTURE_Di;
// 	 ControlPicture*	m_pID_PICTURE_TitleDi;
// 	 ControlPicture*	m_pID_PICTURE_title;
	 ControlButton*	m_pID_BUTTON_CLOSE;
//	 ControlButton*	m_pID_BUTTON_help;
// 	 ControlButton*	m_pID_BUTTON_Exit;
//	 ControlText*	m_pID_TEXT_Title;
	 ControlList*	m_pID_LIST_FriendName;
	 ControlList*	m_pID_LIST_ChatList;
// 	 ControlText*	m_pID_TEXT_ChatPlayer;
// 	 ControlText*	m_pID_TEXT_ChatTime;
// 	 ControlText*	m_pID_TEXT_Chat2;
	 ControlCheckBox*	m_pID_CHECKBOX_Friend;
	 ControlCheckBox*	m_pID_CHECKBOX_Stranger;
// 	 ControlText*	m_pID_TEXT_Detail;
	 ControlButton*	m_pID_BUTTON_Delete;
// 	 ControlText*	m_pID_TEXT_Chat;
	 ControlButton*	m_pID_BUTTON_LastPage;
	 ControlButton*	m_pID_BUTTON_FirstPage;
	 ControlButton*	m_pID_BUTTON_PageDown;
	 ControlButton*	m_pID_BUTTON_PageUp;
	 ControlText*	m_pID_TEXT_Page;
	 ControlEdit*	m_pID_EDIT_Search;
	 ControlButton*	m_pID_BUTTON_Next;
	 ControlComboBox*	m_pID_COMBOBOX_Search;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
//	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ExitOnButtonClick( ControlObject* pSender );
	void ID_LIST_FriendNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ChatListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_FriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_StrangerOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LastPageOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FirstPageOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender );
	void ID_EDIT_SearchOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_NextOnButtonClick( ControlObject* pSender );
	void ID_COMBOBOX_SearchOnComboBoxChange( ControlObject* pSender, const char* szData );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void RefreshFriendListUI(bool isFriend);
	void RefreshChatList();
	void ShowTextInHistoryChatList( std::string& str, const D3DCOLOR col = 0xffffffff);

	void RefreshPageButtonStatus();
	void ShowHistoryChat(const char* pPlayer);

	BOOL EditInputIsVisable();

	enum eSearchType
	{
		ChatName = 0,
		ChatContent,
		SearchTypeTotal
	};

	std::vector<std::string>						m_goodFriendList;
	std::vector<std::string>						m_otherFriendList;
private:
	std::string										m_currFriendName;
	int												m_currChatIndex;
	void SetCurrChatIndex(int val);
	void RefreshFriendName();

	const static int  cDateTimeLength						=  22;
	struct historyChatMessage {
// 		char		playerName[20];
		char		dateTime[cDateTimeLength];
		char		chatContent[256];
		bool		isToMe;
	};
	void _FillChatContent( historyChatMessage &msg, const char * contentStr );

	void _FillPlayerName( historyChatMessage &msg, const char * nameBegin , int nCount);

	void _fillDateTime( historyChatMessage &msg, SYSTEMTIME &time );
	int AddChatMessage( historyChatMessage &msg );

	typedef std::vector<historyChatMessage> oldChatVec;
	oldChatVec					m_oldChatVec;
	oldChatVec& GetHistoryChatVec() {return m_oldChatVec;}

	eSearchType							m_SearchType;
	void								DoSearch();
// 	void								ResetSearchResult();
// 	struct SNameSearchResult 
// 	{
// 		bool							m_bGoodFriend;
// 		int								m_index;
// 		void							Reset();
// 
// 	} nameSearchResult;
	std::string							m_lastSearchString;
	void								DoNameSearch(const char* pName);
 	int									m_lastSearchIndex;
	void SetLastSearchIndex(int val);

	void								DoContentSearch(const char* pContent);

};
extern CUI_ID_FRAME_ChatHistory s_CUI_ID_FRAME_ChatHistory;
