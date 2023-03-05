/********************************************************************
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "ChatChannelConfig.h"

#ifndef ID_FRAME_ChatSet
#define ID_FRAME_ChatSet		"ID_FRAME_ChatSet"
#endif  ID_FRAME_ChatSet
#ifndef ID_PICTURE_title_wall
#define ID_PICTURE_title_wall		"ID_PICTURE_title_wall"
#endif  ID_PICTURE_title_wall
#ifndef ID_PICTURE_ChannelList
#define ID_PICTURE_ChannelList		"ID_PICTURE_ChannelList"
#endif  ID_PICTURE_ChannelList
#ifndef ID_PICTURE_imagewall
#define ID_PICTURE_imagewall		"ID_PICTURE_imagewall"
#endif  ID_PICTURE_imagewall
#ifndef ID_BUTTON_Ok
#define ID_BUTTON_Ok		"ID_BUTTON_Ok"
#endif  ID_BUTTON_Ok
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_Near
#define ID_TEXT_Near		"ID_TEXT_Near"
#endif  ID_TEXT_Near
#ifndef ID_TEXT_Team
#define ID_TEXT_Team		"ID_TEXT_Team"
#endif  ID_TEXT_Team
#ifndef ID_TEXT_Camp
#define ID_TEXT_Camp		"ID_TEXT_Camp"
#endif  ID_TEXT_Camp
#ifndef ID_TEXT_MiniGroup
#define ID_TEXT_MiniGroup		"ID_TEXT_MiniGroup"
#endif  ID_TEXT_MiniGroup
#ifndef ID_TEXT_ChatInto
#define ID_TEXT_ChatInto		"ID_TEXT_ChatInto"
#endif  ID_TEXT_ChatInto
#ifndef ID_TEXT_AotoChat
#define ID_TEXT_AotoChat		"ID_TEXT_AotoChat"
#endif  ID_TEXT_AotoChat
#ifndef ID_CHECKBOX_Team
#define ID_CHECKBOX_Team		"ID_CHECKBOX_Team"
#endif  ID_CHECKBOX_Team
#ifndef ID_CHECKBOX_MiniGroup
#define ID_CHECKBOX_MiniGroup		"ID_CHECKBOX_MiniGroup"
#endif  ID_CHECKBOX_MiniGroup
#ifndef ID_CHECKBOX_Near
#define ID_CHECKBOX_Near		"ID_CHECKBOX_Near"
#endif  ID_CHECKBOX_Near
#ifndef ID_CHECKBOX_AotoChat
#define ID_CHECKBOX_AotoChat		"ID_CHECKBOX_AotoChat"
#endif  ID_CHECKBOX_AotoChat
#ifndef ID_TEXT_World
#define ID_TEXT_World		"ID_TEXT_World"
#endif  ID_TEXT_World
#ifndef ID_CHECKBOX_World
#define ID_CHECKBOX_World		"ID_CHECKBOX_World"
#endif  ID_CHECKBOX_World
#ifndef ID_PICTURE_imagewall3
#define ID_PICTURE_imagewall3		"ID_PICTURE_imagewall3"
#endif  ID_PICTURE_imagewall3
#ifndef ID_EDIT_AotoChat
#define ID_EDIT_AotoChat		"ID_EDIT_AotoChat"
#endif  ID_EDIT_AotoChat
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_PICTURE_25399
#define ID_PICTURE_25399		"ID_PICTURE_25399"
#endif  ID_PICTURE_25399
#ifndef ID_CHECKBOX_Camp
#define ID_CHECKBOX_Camp		"ID_CHECKBOX_Camp"
#endif  ID_CHECKBOX_Camp
#ifndef ID_LIST_ChannelList
#define ID_LIST_ChannelList		"ID_LIST_ChannelList"
#endif  ID_LIST_ChannelList
#ifndef ID_BUTTON_Delete
#define ID_BUTTON_Delete		"ID_BUTTON_Delete"
#endif  ID_BUTTON_Delete
#ifndef ID_BUTTON_Create
#define ID_BUTTON_Create		"ID_BUTTON_Create"
#endif  ID_BUTTON_Create
#ifndef ID_TEXT_ChannelName
#define ID_TEXT_ChannelName		"ID_TEXT_ChannelName"
#endif  ID_TEXT_ChannelName
#ifndef ID_TEXT_Private
#define ID_TEXT_Private		"ID_TEXT_Private"
#endif  ID_TEXT_Private
#ifndef ID_CHECKBOX_Private
#define ID_CHECKBOX_Private		"ID_CHECKBOX_Private"
#endif  ID_CHECKBOX_Private

#ifndef ID_TEXT_System
#define ID_TEXT_System		"ID_TEXT_System"
#endif  ID_TEXT_System
#ifndef ID_CHECKBOX_System
#define ID_CHECKBOX_System		"ID_CHECKBOX_System"
#endif  ID_CHECKBOX_System
#ifndef ID_CHECKBOX_AttackInfo
#define ID_CHECKBOX_AttackInfo		"ID_CHECKBOX_AttackInfo"
#endif  ID_CHECKBOX_AttackInfo
#ifndef ID_TEXT_AttackInfo
#define ID_TEXT_AttackInfo		"ID_TEXT_AttackInfo"
#endif  ID_TEXT_AttackInfo
#ifndef ID_TEXT_ZhenYing
#define ID_TEXT_ZhenYing		"ID_TEXT_ZhenYing"
#endif  ID_TEXT_ZhenYing
#ifndef ID_CHECKBOX_ZhenYing
#define ID_CHECKBOX_ZhenYing		"ID_CHECKBOX_ZhenYing"
#endif  ID_CHECKBOX_ZhenYing
#ifndef ID_CHECKBOX_Country
#define ID_CHECKBOX_Country		"ID_CHECKBOX_Country"
#endif  ID_CHECKBOX_Country
#ifndef ID_CHECKBOX_Horn
#define ID_CHECKBOX_Horn		"ID_CHECKBOX_Horn"
#endif  ID_CHECKBOX_Horn
#ifndef ID_BUTTON_Default
#define ID_BUTTON_Default		"ID_BUTTON_Default"
#endif  ID_BUTTON_Default
#ifndef ID_SCROLLBAREX_Diaphaneity
#define ID_SCROLLBAREX_Diaphaneity		"ID_SCROLLBAREX_Diaphaneity"
#endif  ID_SCROLLBAREX_Diaphaneity
#ifndef ID_CHECKBOX_Family
#define ID_CHECKBOX_Family		"ID_CHECKBOX_Family"
#endif  ID_CHECKBOX_Family

//lyh添加官员聊天频
#ifndef ID_CHECKBOX_GuanYuan
#define ID_CHECKBOX_GuanYuan		"ID_CHECKBOX_GuanYuan"
#endif  ID_CHECKBOX_GuanYuan



#include "UiBase.h"
class CUI_ID_FRAME_ChatSet :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_ChatSet();
private:
	ControlFrame*	m_pID_FRAME_ChatSet;
	//ControlPicture*	m_pID_PICTURE_title_wall;
	ControlPicture*	m_pID_PICTURE_ChannelList;
	ControlPicture*	m_pID_PICTURE_imagewall;
	ControlButton*	m_pID_BUTTON_Ok;
	ControlButton*	m_pID_BUTTON_Cancel;
	ControlText*	m_pID_TEXT_Near;
	ControlText*	m_pID_TEXT_Team;
	ControlText*	m_pID_TEXT_Camp;
	ControlText*	m_pID_TEXT_MiniGroup;
	ControlText*	m_pID_TEXT_ChatInto;
	ControlText*	m_pID_TEXT_AotoChat;
	ControlCheckBox*	m_pID_CHECKBOX_Team;
	ControlCheckBox*	m_pID_CHECKBOX_MiniGroup;
	ControlCheckBox*	m_pID_CHECKBOX_Near;
	ControlCheckBox*	m_pID_CHECKBOX_AotoChat;
	ControlText*	m_pID_TEXT_World;
	ControlCheckBox*	m_pID_CHECKBOX_World;
	ControlPicture*	m_pID_PICTURE_imagewall3;
	ControlEdit*	m_pID_EDIT_AotoChat;
	ControlButton*	m_pID_BUTTON_CLOSE;
// 	ControlButton*	m_pID_BUTTON_help;
// 	ControlPicture*	m_pID_PICTURE_25399;
// 	ControlCheckBox*	m_pID_CHECKBOX_Camp;
	ControlList*	m_pID_LIST_ChannelList;
	ControlButton*	m_pID_BUTTON_Delete;
	ControlButton*	m_pID_BUTTON_Create;
	ControlText*	m_pID_TEXT_ChannelName;
	ControlText*	m_pID_TEXT_Private;
	ControlCheckBox*	m_pID_CHECKBOX_Private;
	ControlText*	m_pID_TEXT_System;
	ControlCheckBox*	m_pID_CHECKBOX_System;
    ControlCheckBox*	m_pID_CHECKBOX_AttackInfo;
    ControlText*	m_pID_TEXT_AttackInfo;
// 	ControlText*	m_pID_TEXT_ZhenYing;
// 	ControlCheckBox*	m_pID_CHECKBOX_ZhenYing;
	ControlCheckBox*	m_pID_CHECKBOX_Country;
    ControlCheckBox*    m_pID_CHECKBOX_Horn;
    ControlButton*      m_pID_BUTTON_Default;
    ControlScrollBarEx*	m_pID_SCROLLBAREX_Diaphaneity;
	ControlCheckBox*	m_pID_CHECKBOX_Family;
    //lyh guanyuan
	ControlCheckBox*    m_pID_CHECKBOX_GuanYuan;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_TeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MiniGroupOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_NearOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_AotoChatOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_WorldOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	//lyh++ guanyuan
	void ID_CHECKBOX_GuanYuanOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );


	void ID_EDIT_AotoChatOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	//void ID_CHECKBOX_CampOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_LIST_ChannelListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_DeleteOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CreateOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_PrivateOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SystemOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_AttackInfoOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	//void ID_CHECKBOX_ZhenYingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_CountryOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_HornOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked );
    bool ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender );
    void ID_SCROLLBAREX_DiaphaneityOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	void ID_CHECKBOX_FamilyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	void AddChannel( const char* pszName );
	bool IsAutoAck() { if(!m_pID_FRAME_ChatSet) return false;return m_pID_CHECKBOX_AotoChat->IsChecked() && strlen(m_pID_EDIT_AotoChat->GetText()) > 0; }

	BOOL EditInputIsVisable();

	const char* GetAutoAckInfo() { return m_pID_EDIT_AotoChat->GetText(); }
	void LoadChannelConfig();
private:
	void LoadAutoReplyConfig();
	void SaveAutoReplyConfig();

	void SaveChannelConfig();

	void RefreshChannelList();
	void RefreshChannelInfo();

	/// 水浒需求，不可配置的频道全部灰色（NC)
	void RefreshCheckBoxsEnable( bool bEnable );

	std::string m_backupAutoText;
    ChatChannelConfig::ChatChannelInfoList m_DefChatChannelList;
};
extern CUI_ID_FRAME_ChatSet s_CUI_ID_FRAME_ChatSet;

