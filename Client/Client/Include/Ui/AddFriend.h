/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\AddFriend.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "RelationDefine.h"

#ifndef ID_FRAME_AddFriend
#define ID_FRAME_AddFriend		"ID_FRAME_AddFriend"
#endif  ID_FRAME_AddFriend
#ifndef ID_TEXT_String
#define ID_TEXT_String		"ID_TEXT_String"
#endif  ID_TEXT_String
#ifndef ID_EDIT_FriendName
#define ID_EDIT_FriendName		"ID_EDIT_FriendName"
#endif  ID_EDIT_FriendName
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_COMBOBOX_FriendClass
#define ID_COMBOBOX_FriendClass		"ID_COMBOBOX_FriendClass"
#endif  ID_COMBOBOX_FriendClass
#ifndef ID_BUTTON_True
#define ID_BUTTON_True		"ID_BUTTON_True"
#endif  ID_BUTTON_True
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_PICTURE_1
#define ID_PICTURE_1		"ID_PICTURE_1"
#endif  ID_PICTURE_1
#ifndef ID_TEXT_Friend
#define ID_TEXT_Friend		"ID_TEXT_Friend"
#endif  ID_TEXT_Friend
#ifndef ID_PICTURE_2
#define ID_PICTURE_2		"ID_PICTURE_2"
#endif  ID_PICTURE_2
#include "UIBase.h"
class CUI_ID_FRAME_AddFriend : public CUIBase
{
public:

	enum eFrameType {
		eFrameType_AddFriend
		,eFrameType_AddFriendFromRMenu
		,eFrameType_ChangeFriendToGroup
		,eFrameType_AddBlackFriend
	};

	// Member
private:	
	 ControlFrame*	m_pID_FRAME_AddFriend;
	 ControlText*	m_pID_TEXT_String;
	 ControlEdit*	m_pID_EDIT_FriendName;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlComboBox*	m_pID_COMBOBOX_FriendClass;
	 ControlButton*	m_pID_BUTTON_True;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlPicture*	m_pID_PICTURE_1;
	 ControlText*	m_pID_TEXT_Friend;
	 ControlPicture*	m_pID_PICTURE_2;
public:	
	CUI_ID_FRAME_AddFriend();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_FriendNameOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_COMBOBOX_FriendClassOnComboBoxChange( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_TrueOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );

	bool EditInputIsVisable();
	void sendMsgChangeFriendGroup( const char* name,int nGroup );
	void sendMsgAddFriend( const char* name, RelationDefine::EConstDefine type ,int nGroup );
	void SetFrameType(eFrameType type) { meFrameType = type; }
	void SetPrivateName( const char* szName );

private:
	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
private:	
	eFrameType						meFrameType;
	DWORD							m_dwLastAddFriendReqTime;   // 加好友请求增加3秒CD
	std::string						m_szName;
	int								m_nGroup;
};
extern CUI_ID_FRAME_AddFriend s_CUI_ID_FRAME_AddFriend;
