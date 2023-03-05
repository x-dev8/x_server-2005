/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Bin\Client\Data\Ui\Message_Chat.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "CommonChatFrame.h"
#ifndef ID_FRAME_Message_Chat
#define ID_FRAME_Message_Chat		"ID_FRAME_Message_Chat"
#endif  ID_FRAME_Message_Chat
#ifndef ID_TEXT_Target
#define ID_TEXT_Target		"ID_TEXT_Target"
#endif  ID_TEXT_Target
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Minimize
#define ID_BUTTON_Minimize		"ID_BUTTON_Minimize"
#endif  ID_BUTTON_Minimize
#ifndef ID_TEXT_Char
#define ID_TEXT_Char		"ID_TEXT_Char"
#endif  ID_TEXT_Char
#ifndef ID_CHECKBOX_Save
#define ID_CHECKBOX_Save		"ID_CHECKBOX_Save"
#endif  ID_CHECKBOX_Save
#ifndef ID_BUTTON_Clear
#define ID_BUTTON_Clear		"ID_BUTTON_Clear"
#endif  ID_BUTTON_Clear
#ifndef ID_BUTTON_face
#define ID_BUTTON_face		"ID_BUTTON_face"
#endif  ID_BUTTON_face
#ifndef ID_EDIT_Input
#define ID_EDIT_Input		"ID_EDIT_Input"
#endif  ID_EDIT_Input
#ifndef ID_BUTTON_History
#define ID_BUTTON_History		"ID_BUTTON_History"
#endif  ID_BUTTON_History
#ifndef ID_BUTTON_Enter
#define ID_BUTTON_Enter		"ID_BUTTON_Enter"
#endif  ID_BUTTON_Enter

#ifndef ID_BUTTON_AddFriend
#define ID_BUTTON_AddFriend		"ID_BUTTON_AddFriend"
#endif  ID_BUTTON_AddFriend

class CUI_ID_FRAME_Message_Chat :  public CommonChatFrame ,public CUINotManagedByUIMgr
{
	// Member
public:	
	 CUI_ID_FRAME_Message_Chat(int frameIndex);

	// Frame
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MinimizeOnButtonClick( ControlObject* pSender );
// 	void ID_LIST_CharOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_SaveOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_ClearOnButtonClick( ControlObject* pSender );
	virtual void ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData );

	void SendMessage( const char* szData );
	bool ID_BUTTON_HistoryOnButtonClick( ControlObject* pSender );
	virtual bool ID_BUTTON_EnterOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AddFriendOnButtonClick( ControlObject* pSender );
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	virtual	bool			IsShow() {return IsVisable();}
	virtual	void			SetShow(bool bFlag) {SetVisable(bFlag);}

public:


	void SetSaveMessageStatus(bool isSaved);

	void RefreshChatMessage();
	
	virtual void AddMyChatHistories( const char* szData );
	void Clear();

    ControlText*	m_pID_TEXT_Target;
private:
    ControlButton*	m_pID_BUTTON_CLOSE;
    ControlButton*	m_pID_BUTTON_Minimize;
    ControlCheckBox*	m_pID_CHECKBOX_Save;
    ControlButton*	m_pID_BUTTON_Clear;
    ControlButton*	m_pID_BUTTON_History;
	ControlButton*	m_pID_BUTTON_AddFriend;

    ControlFrame*			m_pObject;
	int m_FrameIndex;
	int m_PlayerID;
	char	szFrameID[64];
};
