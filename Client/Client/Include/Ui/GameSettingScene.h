/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\gamesetting\GameSettingScene.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GameSettingScene
#define ID_FRAME_GameSettingScene		"ID_FRAME_GameSettingScene"
#endif  ID_FRAME_GameSettingScene
#ifndef ID_PICTURE_Wall1
#define ID_PICTURE_Wall1		"ID_PICTURE_Wall1"
#endif  ID_PICTURE_Wall1
#ifndef ID_PICTURE_Wall3
#define ID_PICTURE_Wall3		"ID_PICTURE_Wall3"
#endif  ID_PICTURE_Wall3
#ifndef ID_PICTURE_Wall2
#define ID_PICTURE_Wall2		"ID_PICTURE_Wall2"
#endif  ID_PICTURE_Wall2
#ifndef ID_PICTURE_Wall4
#define ID_PICTURE_Wall4		"ID_PICTURE_Wall4"
#endif  ID_PICTURE_Wall4
#ifndef ID_TEXT_NpcInfo
#define ID_TEXT_NpcInfo		"ID_TEXT_NpcInfo"
#endif  ID_TEXT_NpcInfo
#ifndef ID_TEXT_NpcName
#define ID_TEXT_NpcName		"ID_TEXT_NpcName"
#endif  ID_TEXT_NpcName
#ifndef ID_TEXT_NpcHp
#define ID_TEXT_NpcHp		"ID_TEXT_NpcHp"
#endif  ID_TEXT_NpcHp
#ifndef ID_TEXT_NpcTitle
#define ID_TEXT_NpcTitle		"ID_TEXT_NpcTitle"
#endif  ID_TEXT_NpcTitle
#ifndef ID_TEXT_MonsterInfo
#define ID_TEXT_MonsterInfo		"ID_TEXT_MonsterInfo"
#endif  ID_TEXT_MonsterInfo
#ifndef ID_TEXT_MonsterName
#define ID_TEXT_MonsterName		"ID_TEXT_MonsterName"
#endif  ID_TEXT_MonsterName
#ifndef ID_TEXT_MonsterHp
#define ID_TEXT_MonsterHp		"ID_TEXT_MonsterHp"
#endif  ID_TEXT_MonsterHp
#ifndef ID_TEXT_MapInfo
#define ID_TEXT_MapInfo		"ID_TEXT_MapInfo"
#endif  ID_TEXT_MapInfo
#ifndef ID_TEXT_Team
#define ID_TEXT_Team		"ID_TEXT_Team"
#endif  ID_TEXT_Team
#ifndef ID_TEXT_Npc
#define ID_TEXT_Npc		"ID_TEXT_Npc"
#endif  ID_TEXT_Npc
#ifndef ID_TEXT_Monster
#define ID_TEXT_Monster		"ID_TEXT_Monster"
#endif  ID_TEXT_Monster
#ifndef ID_TEXT_OtherPlayerChat
#define ID_TEXT_OtherPlayerChat		"ID_TEXT_OtherPlayerChat"
#endif  ID_TEXT_OtherPlayerChat
#ifndef ID_TEXT_Friend
#define ID_TEXT_Friend		"ID_TEXT_Friend"
#endif  ID_TEXT_Friend
#ifndef ID_TEXT_ChatInfo
#define ID_TEXT_ChatInfo		"ID_TEXT_ChatInfo"
#endif  ID_TEXT_ChatInfo
#ifndef ID_TEXT_SelfChat
#define ID_TEXT_SelfChat		"ID_TEXT_SelfChat"
#endif  ID_TEXT_SelfChat
#ifndef ID_TEXT_TeamChat
#define ID_TEXT_TeamChat		"ID_TEXT_TeamChat"
#endif  ID_TEXT_TeamChat
#ifndef ID_CHECKBOX_NpcName
#define ID_CHECKBOX_NpcName		"ID_CHECKBOX_NpcName"
#endif  ID_CHECKBOX_NpcName
#ifndef ID_CHECKBOX_NpcHp
#define ID_CHECKBOX_NpcHp		"ID_CHECKBOX_NpcHp"
#endif  ID_CHECKBOX_NpcHp
#ifndef ID_CHECKBOX_NpcTitle
#define ID_CHECKBOX_NpcTitle		"ID_CHECKBOX_NpcTitle"
#endif  ID_CHECKBOX_NpcTitle
#ifndef ID_CHECKBOX_MonsterName
#define ID_CHECKBOX_MonsterName		"ID_CHECKBOX_MonsterName"
#endif  ID_CHECKBOX_MonsterName
#ifndef ID_CHECKBOX_MonsterHp
#define ID_CHECKBOX_MonsterHp		"ID_CHECKBOX_MonsterHp"
#endif  ID_CHECKBOX_MonsterHp
#ifndef ID_CHECKBOX_Team
#define ID_CHECKBOX_Team		"ID_CHECKBOX_Team"
#endif  ID_CHECKBOX_Team
#ifndef ID_CHECKBOX_Npc
#define ID_CHECKBOX_Npc		"ID_CHECKBOX_Npc"
#endif  ID_CHECKBOX_Npc
#ifndef ID_CHECKBOX_Monster
#define ID_CHECKBOX_Monster		"ID_CHECKBOX_Monster"
#endif  ID_CHECKBOX_Monster
#ifndef ID_CHECKBOX_OtherPlayerChat
#define ID_CHECKBOX_OtherPlayerChat		"ID_CHECKBOX_OtherPlayerChat"
#endif  ID_CHECKBOX_OtherPlayerChat
#ifndef ID_CHECKBOX_Friend
#define ID_CHECKBOX_Friend		"ID_CHECKBOX_Friend"
#endif  ID_CHECKBOX_Friend
#ifndef ID_CHECKBOX_SelfChat
#define ID_CHECKBOX_SelfChat		"ID_CHECKBOX_SelfChat"
#endif  ID_CHECKBOX_SelfChat
#ifndef ID_CHECKBOX_TeamChat
#define ID_CHECKBOX_TeamChat		"ID_CHECKBOX_TeamChat"
#endif  ID_CHECKBOX_TeamChat
#ifndef ID_TEXT_DropItem
#define ID_TEXT_DropItem		"ID_TEXT_DropItem"
#endif  ID_TEXT_DropItem
#ifndef ID_PICTURE_Wall5
#define ID_PICTURE_Wall5		"ID_PICTURE_Wall5"
#endif  ID_PICTURE_Wall5
#ifndef ID_TEXT_ItemName
#define ID_TEXT_ItemName		"ID_TEXT_ItemName"
#endif  ID_TEXT_ItemName
#ifndef ID_CHECKBOX_ItemName
#define ID_CHECKBOX_ItemName		"ID_CHECKBOX_ItemName"
#endif  ID_CHECKBOX_ItemName
#ifndef ID_CHECKBOX_Guild
#define ID_CHECKBOX_Guild		"ID_CHECKBOX_Guild"
#endif  ID_CHECKBOX_Guild
#ifndef ID_CHECKBOX_Enemy
#define ID_CHECKBOX_Enemy		"ID_CHECKBOX_Enemy"
#endif  ID_CHECKBOX_Enemy

#ifndef ID_CHECKBOX_Other
#define ID_CHECKBOX_Other		"ID_CHECKBOX_Other"
#endif  ID_CHECKBOX_Other
#ifndef ID_CHECKBOX_MonsterChat
#define ID_CHECKBOX_MonsterChat		"ID_CHECKBOX_MonsterChat"
#endif  ID_CHECKBOX_MonsterChat
#ifndef ID_CHECKBOX_NPCChat
#define ID_CHECKBOX_NPCChat		"ID_CHECKBOX_NPCChat"
#endif  ID_CHECKBOX_NPCChat
#ifndef ID_CHECKBOX_NpcInfoControl
#define ID_CHECKBOX_NpcInfoControl		"ID_CHECKBOX_NpcInfoControl"
#endif  ID_CHECKBOX_NpcInfoControl
#ifndef ID_CHECKBOX_MonsterInfoControl
#define ID_CHECKBOX_MonsterInfoControl		"ID_CHECKBOX_MonsterInfoControl"
#endif  ID_CHECKBOX_MonsterInfoControl
#ifndef ID_CHECKBOX_MapInfoControl
#define ID_CHECKBOX_MapInfoControl		"ID_CHECKBOX_MapInfoControl"
#endif  ID_CHECKBOX_MapInfoControl
#ifndef ID_CHECKBOX_ChatInfoControl
#define ID_CHECKBOX_ChatInfoControl		"ID_CHECKBOX_ChatInfoControl"
#endif  ID_CHECKBOX_ChatInfoControl

#include "UiBase.h"
class CUI_ID_FRAME_GameSettingScene :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GameSettingScene();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_NpcNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_NpcHpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_NpcTitleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MonsterNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MonsterHpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_NpcOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MonsterOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherPlayerChatOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_FriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SelfChatOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamChatOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_ItemNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_GuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_EnemyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MonsterChatOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_NPCChatOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_NpcInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_MonsterInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_MapInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
// 	void ID_CHECKBOX_ChatInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	void RefreshUI();
    void CheckNpcInfoControl();
    void CheckMonsterInfoControl();
    void CheckMapInfoControl();
    void CheckChatInfoControl();

    ControlFrame* GetFrame(){return m_pID_FRAME_GameSettingScene;}
private:
    ControlFrame*	m_pID_FRAME_GameSettingScene;
    ControlPicture*	m_pID_PICTURE_Wall1;
    ControlPicture*	m_pID_PICTURE_Wall3;
    ControlPicture*	m_pID_PICTURE_Wall2;
    ControlPicture*	m_pID_PICTURE_Wall4;
    ControlText*	m_pID_TEXT_NpcInfo;
    ControlText*	m_pID_TEXT_NpcName;
    ControlText*	m_pID_TEXT_NpcHp;
    ControlText*	m_pID_TEXT_NpcTitle;
    ControlText*	m_pID_TEXT_MonsterInfo;
    ControlText*	m_pID_TEXT_MonsterName;
    ControlText*	m_pID_TEXT_MonsterHp;
    ControlText*	m_pID_TEXT_MapInfo;
    ControlText*	m_pID_TEXT_Team;
    ControlText*	m_pID_TEXT_Npc;
    ControlText*	m_pID_TEXT_Monster;
    ControlText*	m_pID_TEXT_OtherPlayerChat;
    ControlText*	m_pID_TEXT_Friend;
    ControlText*	m_pID_TEXT_ChatInfo;
    ControlText*	m_pID_TEXT_SelfChat;
    ControlText*	m_pID_TEXT_TeamChat;
    ControlCheckBox*	m_pID_CHECKBOX_NpcName;
    ControlCheckBox*	m_pID_CHECKBOX_NpcHp;
    ControlCheckBox*	m_pID_CHECKBOX_NpcTitle;
    ControlCheckBox*	m_pID_CHECKBOX_MonsterName;
    ControlCheckBox*	m_pID_CHECKBOX_MonsterHp;
    ControlCheckBox*	m_pID_CHECKBOX_Team;
    ControlCheckBox*	m_pID_CHECKBOX_Npc;
    ControlCheckBox*	m_pID_CHECKBOX_Monster;
    ControlCheckBox*	m_pID_CHECKBOX_OtherPlayerChat;
    ControlCheckBox*	m_pID_CHECKBOX_Friend;
    ControlCheckBox*	m_pID_CHECKBOX_SelfChat;
    ControlCheckBox*	m_pID_CHECKBOX_TeamChat;
    ControlCheckBox*	m_pID_CHECKBOX_Guild;
    ControlCheckBox*	m_pID_CHECKBOX_Enemy;
    ControlText*	m_pID_TEXT_DropItem;
    ControlPicture*	m_pID_PICTURE_Wall5;
    ControlText*	m_pID_TEXT_ItemName;
    ControlCheckBox*	m_pID_CHECKBOX_ItemName;
    ControlCheckBox*	m_pID_CHECKBOX_Other;
    ControlCheckBox*	m_pID_CHECKBOX_MonsterChat;
    ControlCheckBox*	m_pID_CHECKBOX_NPCChat;
//     ControlCheckBox*	m_pID_CHECKBOX_NpcInfoControl;
//     ControlCheckBox*	m_pID_CHECKBOX_MonsterInfoControl;
//     ControlCheckBox*	m_pID_CHECKBOX_MapInfoControl;
//     ControlCheckBox*	m_pID_CHECKBOX_ChatInfoControl;
};
extern CUI_ID_FRAME_GameSettingScene s_CUI_ID_FRAME_GameSettingScene;
