/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\GameSettingTab.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Player.h"

#ifndef ID_FRAME_GameSettingTab
#define ID_FRAME_GameSettingTab		"ID_FRAME_GameSettingTab"
#endif  ID_FRAME_GameSettingTab
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
#ifndef ID_TEXT_SelfInfo
#define ID_TEXT_SelfInfo		"ID_TEXT_SelfInfo"
#endif  ID_TEXT_SelfInfo
#ifndef ID_TEXT_Self
#define ID_TEXT_Self		"ID_TEXT_Self"
#endif  ID_TEXT_Self
#ifndef ID_TEXT_SelfBB
#define ID_TEXT_SelfBB		"ID_TEXT_SelfBB"
#endif  ID_TEXT_SelfBB
#ifndef ID_TEXT_TeamInfo
#define ID_TEXT_TeamInfo		"ID_TEXT_TeamInfo"
#endif  ID_TEXT_TeamInfo
#ifndef ID_TEXT_Team
#define ID_TEXT_Team		"ID_TEXT_Team"
#endif  ID_TEXT_Team
#ifndef ID_TEXT_TeamBB
#define ID_TEXT_TeamBB		"ID_TEXT_TeamBB"
#endif  ID_TEXT_TeamBB
#ifndef ID_TEXT_OtherPlayer
#define ID_TEXT_OtherPlayer		"ID_TEXT_OtherPlayer"
#endif  ID_TEXT_OtherPlayer
#ifndef ID_TEXT_FriendGuildBB
#define ID_TEXT_FriendGuildBB		"ID_TEXT_FriendGuildBB"
#endif  ID_TEXT_FriendGuildBB
#ifndef ID_TEXT_FriendGuild
#define ID_TEXT_FriendGuild		"ID_TEXT_FriendGuild"
#endif  ID_TEXT_FriendGuild
#ifndef ID_TEXT_RedName
#define ID_TEXT_RedName		"ID_TEXT_RedName"
#endif  ID_TEXT_RedName
#ifndef ID_TEXT_EnemyGuildBB
#define ID_TEXT_EnemyGuildBB		"ID_TEXT_EnemyGuildBB"
#endif  ID_TEXT_EnemyGuildBB
#ifndef ID_TEXT_OtherInfo
#define ID_TEXT_OtherInfo		"ID_TEXT_OtherInfo"
#endif  ID_TEXT_OtherInfo
#ifndef ID_TEXT_RedNameBB
#define ID_TEXT_RedNameBB		"ID_TEXT_RedNameBB"
#endif  ID_TEXT_RedNameBB
#ifndef ID_CHECKBOX_Self
#define ID_CHECKBOX_Self		"ID_CHECKBOX_Self"
#endif  ID_CHECKBOX_Self
#ifndef ID_CHECKBOX_SelfBB
#define ID_CHECKBOX_SelfBB		"ID_CHECKBOX_SelfBB"
#endif  ID_CHECKBOX_SelfBB
#ifndef ID_CHECKBOX_Team
#define ID_CHECKBOX_Team		"ID_CHECKBOX_Team"
#endif  ID_CHECKBOX_Team
#ifndef ID_CHECKBOX_TeamBB
#define ID_CHECKBOX_TeamBB		"ID_CHECKBOX_TeamBB"
#endif  ID_CHECKBOX_TeamBB
#ifndef ID_CHECKBOX_EnemyGuildBB
#define ID_CHECKBOX_EnemyGuildBB		"ID_CHECKBOX_EnemyGuildBB"
#endif  ID_CHECKBOX_EnemyGuildBB
#ifndef ID_CHECKBOX_EnemyGuild
#define ID_CHECKBOX_EnemyGuild		"ID_CHECKBOX_EnemyGuild"
#endif  ID_CHECKBOX_EnemyGuild
#ifndef ID_CHECKBOX_RedName
#define ID_CHECKBOX_RedName		"ID_CHECKBOX_RedName"
#endif  ID_CHECKBOX_RedName
#ifndef ID_CHECKBOX_FriendGuildBB
#define ID_CHECKBOX_FriendGuildBB		"ID_CHECKBOX_FriendGuildBB"
#endif  ID_CHECKBOX_FriendGuildBB
#ifndef ID_CHECKBOX_RedNameBB
#define ID_CHECKBOX_RedNameBB		"ID_CHECKBOX_RedNameBB"
#endif  ID_CHECKBOX_RedNameBB
#ifndef ID_TEXT_EnemyGuild
#define ID_TEXT_EnemyGuild		"ID_TEXT_EnemyGuild"
#endif  ID_TEXT_EnemyGuild
#ifndef ID_CHECKBOX_FriendGuild
#define ID_CHECKBOX_FriendGuild		"ID_CHECKBOX_FriendGuild"
#endif  ID_CHECKBOX_FriendGuild
#ifndef ID_TEXT_PK
#define ID_TEXT_PK		"ID_TEXT_PK"
#endif  ID_TEXT_PK
#ifndef ID_CHECKBOX_PK
#define ID_CHECKBOX_PK		"ID_CHECKBOX_PK"
#endif  ID_CHECKBOX_PK
#ifndef ID_TEXT_PKBB
#define ID_TEXT_PKBB		"ID_TEXT_PKBB"
#endif  ID_TEXT_PKBB
#ifndef ID_CHECKBOX_PKBB
#define ID_CHECKBOX_PKBB		"ID_CHECKBOX_PKBB"
#endif  ID_CHECKBOX_PKBB
#ifndef ID_CHECKBOX_SelfInfoControl
#define ID_CHECKBOX_SelfInfoControl		"ID_CHECKBOX_SelfInfoControl"
#endif  ID_CHECKBOX_SelfInfoControl
#ifndef ID_CHECKBOX_TeamInfoControl
#define ID_CHECKBOX_TeamInfoControl		"ID_CHECKBOX_TeamInfoControl"
#endif  ID_CHECKBOX_TeamInfoControl
#ifndef ID_CHECKBOX_OtherPlayerInfoControl
#define ID_CHECKBOX_OtherPlayerInfoControl		"ID_CHECKBOX_OtherPlayerInfoControl"
#endif  ID_CHECKBOX_OtherPlayerInfoControl
#ifndef ID_CHECKBOX_OtherInfoControl
#define ID_CHECKBOX_OtherInfoControl		"ID_CHECKBOX_OtherInfoControl"
#endif  ID_CHECKBOX_OtherInfoControl
#ifndef ID_TEXT_Normal
#define ID_TEXT_Normal		"ID_TEXT_Normal"
#endif  ID_TEXT_Normal
#ifndef ID_CHECKBOX_Normal
#define ID_CHECKBOX_Normal		"ID_CHECKBOX_Normal"
#endif  ID_CHECKBOX_Normal
#ifndef ID_TEXT_NormalBB
#define ID_TEXT_NormalBB		"ID_TEXT_NormalBB"
#endif  ID_TEXT_NormalBB
#ifndef ID_CHECKBOX_NormalBB
#define ID_CHECKBOX_NormalBB		"ID_CHECKBOX_NormalBB"
#endif  ID_CHECKBOX_NormalBB
#ifndef ID_TEXT_Monster
#define ID_TEXT_Monster		"ID_TEXT_Monster"
#endif  ID_TEXT_Monster
#ifndef ID_CHECKBOX_Monster
#define ID_CHECKBOX_Monster		"ID_CHECKBOX_Monster"
#endif  ID_CHECKBOX_Monster

#include "UiBase.h"
class CUI_ID_FRAME_GameSettingTab :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_GameSettingTab();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_SelfOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SelfBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_EnemyGuildBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_EnemyGuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RedNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_FriendGuildBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RedNameBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_FriendGuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PKOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PKBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SelfInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_TeamInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherPlayerInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherInfoControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_NormalOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_NormalBBOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MonsterOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


private:
	void SetCheckValue(int id, bool value);
	void RefreshUI();
	void RefreshSelectAllState();
	DWORD GetTabPlayerType();

private:
    ControlFrame*	m_pID_FRAME_GameSettingTab;
    ControlPicture*	m_pID_PICTURE_Wall1;
    ControlPicture*	m_pID_PICTURE_Wall3;
    ControlPicture*	m_pID_PICTURE_Wall2;
    ControlPicture*	m_pID_PICTURE_Wall4;
    ControlText*	m_pID_TEXT_SelfInfo;
    ControlText*	m_pID_TEXT_Self;
    ControlText*	m_pID_TEXT_SelfBB;
    ControlText*	m_pID_TEXT_TeamInfo;
    ControlText*	m_pID_TEXT_Team;
    ControlText*	m_pID_TEXT_TeamBB;
    ControlText*	m_pID_TEXT_OtherPlayer;
    ControlText*	m_pID_TEXT_FriendGuildBB;
    ControlText*	m_pID_TEXT_FriendGuild;
    ControlText*	m_pID_TEXT_RedName;
    ControlText*	m_pID_TEXT_EnemyGuildBB;
    ControlText*	m_pID_TEXT_OtherInfo;
    ControlText*	m_pID_TEXT_RedNameBB;
    ControlCheckBox*	m_pID_CHECKBOX_Self;
    ControlCheckBox*	m_pID_CHECKBOX_SelfBB;
    ControlCheckBox*	m_pID_CHECKBOX_Team;
    ControlCheckBox*	m_pID_CHECKBOX_TeamBB;
    ControlCheckBox*	m_pID_CHECKBOX_EnemyGuildBB;
    ControlCheckBox*	m_pID_CHECKBOX_EnemyGuild;
    ControlCheckBox*	m_pID_CHECKBOX_RedName;
    ControlCheckBox*	m_pID_CHECKBOX_FriendGuildBB;
    ControlCheckBox*	m_pID_CHECKBOX_RedNameBB;
    ControlText*	m_pID_TEXT_EnemyGuild;
    ControlCheckBox*	m_pID_CHECKBOX_FriendGuild;
    ControlText*	m_pID_TEXT_PK;
    ControlCheckBox*	m_pID_CHECKBOX_PK;
    ControlText*	m_pID_TEXT_PKBB;
    ControlCheckBox*	m_pID_CHECKBOX_PKBB;
    ControlCheckBox*	m_pID_CHECKBOX_SelfInfoControl;
    ControlCheckBox*	m_pID_CHECKBOX_TeamInfoControl;
    ControlCheckBox*	m_pID_CHECKBOX_OtherPlayerInfoControl;
    ControlCheckBox*	m_pID_CHECKBOX_OtherInfoControl;
    ControlText*	m_pID_TEXT_Normal;
    ControlCheckBox*	m_pID_CHECKBOX_Normal;
    ControlText*	m_pID_TEXT_NormalBB;
    ControlCheckBox*	m_pID_CHECKBOX_NormalBB;
    ControlText*	m_pID_TEXT_Monster;
    ControlCheckBox*	m_pID_CHECKBOX_Monster;
};
extern CUI_ID_FRAME_GameSettingTab s_CUI_ID_FRAME_GameSettingTab;
