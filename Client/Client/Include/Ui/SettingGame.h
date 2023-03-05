/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\SettingGame.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Ui/UIBase.h"
#ifndef ID_FRAME_GameSet
#define ID_FRAME_GameSet		"ID_FRAME_GameSet"
#endif  ID_FRAME_GameSet
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Default
#define ID_BUTTON_Default		"ID_BUTTON_Default"
#endif  ID_BUTTON_Default
#ifndef ID_CHECKBOX_PlayerName
#define ID_CHECKBOX_PlayerName		"ID_CHECKBOX_PlayerName"
#endif  ID_CHECKBOX_PlayerName
#ifndef ID_CHECKBOX_SelfHP
#define ID_CHECKBOX_SelfHP		"ID_CHECKBOX_SelfHP"
#endif  ID_CHECKBOX_SelfHP
#ifndef ID_CHECKBOX_PlayerGuild
#define ID_CHECKBOX_PlayerGuild		"ID_CHECKBOX_PlayerGuild"
#endif  ID_CHECKBOX_PlayerGuild
#ifndef ID_CHECKBOX_OthersHP
#define ID_CHECKBOX_OthersHP		"ID_CHECKBOX_OthersHP"
#endif  ID_CHECKBOX_OthersHP
#ifndef ID_CHECKBOX_MonsterName
#define ID_CHECKBOX_MonsterName		"ID_CHECKBOX_MonsterName"
#endif  ID_CHECKBOX_MonsterName
#ifndef ID_CHECKBOX_MonsterHP
#define ID_CHECKBOX_MonsterHP		"ID_CHECKBOX_MonsterHP"
#endif  ID_CHECKBOX_MonsterHP
#ifndef ID_CHECKBOX_RefuseFriend
#define ID_CHECKBOX_RefuseFriend		"ID_CHECKBOX_RefuseFriend"
#endif  ID_CHECKBOX_RefuseFriend
#ifndef ID_CHECKBOX_RefuseTrade
#define ID_CHECKBOX_RefuseTrade		"ID_CHECKBOX_RefuseTrade"
#endif  ID_CHECKBOX_RefuseTrade
#ifndef ID_CHECKBOX_RefuseBattle
#define ID_CHECKBOX_RefuseBattle		"ID_CHECKBOX_RefuseBattle"
#endif  ID_CHECKBOX_RefuseBattle
#ifndef ID_CHECKBOX_RefuseTeam
#define ID_CHECKBOX_RefuseTeam		"ID_CHECKBOX_RefuseTeam"
#endif  ID_CHECKBOX_RefuseTeam
#ifndef ID_CHECKBOX_RefuseGuild
#define ID_CHECKBOX_RefuseGuild		"ID_CHECKBOX_RefuseGuild"
#endif  ID_CHECKBOX_RefuseGuild
#ifndef ID_CHECKBOX_CloseGuide
#define ID_CHECKBOX_CloseGuide		"ID_CHECKBOX_CloseGuide"
#endif  ID_CHECKBOX_CloseGuide
#ifndef ID_CHECKBOX_LockShortcut
#define ID_CHECKBOX_LockShortcut		"ID_CHECKBOX_LockShortcut"
#endif  ID_CHECKBOX_LockShortcut
#ifndef ID_CHECKBOX_CloseChatBubble
#define ID_CHECKBOX_CloseChatBubble		"ID_CHECKBOX_CloseChatBubble"
#endif  ID_CHECKBOX_CloseChatBubble
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_CHECKBOX_RefuseStrangerMessaage
#define ID_CHECKBOX_RefuseStrangerMessaage		"ID_CHECKBOX_RefuseStrangerMessaage"
#endif  ID_CHECKBOX_RefuseStrangerMessaage
#ifndef ID_CHECKBOX_RefuseAllMessaage
#define ID_CHECKBOX_RefuseAllMessaage		"ID_CHECKBOX_RefuseAllMessaage"
#endif  ID_CHECKBOX_RefuseAllMessaage
#ifndef ID_CHECKBOX_Automatism
#define ID_CHECKBOX_Automatism		"ID_CHECKBOX_Automatism"
#endif  ID_CHECKBOX_Automatism

class CUI_ID_FRAME_GameSet : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GameSet();
	 ControlFrame*	m_pID_FRAME_GameSet;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_Default;
	 ControlCheckBox*	m_pID_CHECKBOX_PlayerName;
	 ControlCheckBox*	m_pID_CHECKBOX_SelfHP;
	 ControlCheckBox*	m_pID_CHECKBOX_PlayerGuild;
	 ControlCheckBox*	m_pID_CHECKBOX_OthersHP;
	 ControlCheckBox*	m_pID_CHECKBOX_MonsterName;
	 ControlCheckBox*	m_pID_CHECKBOX_MonsterHP;
	 ControlCheckBox*	m_pID_CHECKBOX_RefuseFriend;
	 ControlCheckBox*	m_pID_CHECKBOX_RefuseTrade;
	 ControlCheckBox*	m_pID_CHECKBOX_RefuseBattle;
	 ControlCheckBox*	m_pID_CHECKBOX_RefuseTeam;
	 ControlCheckBox*	m_pID_CHECKBOX_RefuseGuild;
	 ControlCheckBox*	m_pID_CHECKBOX_CloseGuide;
	 ControlCheckBox*	m_pID_CHECKBOX_LockShortcut;
	 ControlCheckBox*	m_pID_CHECKBOX_CloseChatBubble;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlCheckBox*	m_pID_CHECKBOX_RefuseStrangerMessaage;
	 ControlCheckBox*	m_pID_CHECKBOX_RefuseAllMessaage;
     ControlCheckBox*    m_pID_CHECKBOX_Automatism;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_PlayerNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SelfHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PlayerGuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OthersHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MonsterNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_MonsterHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RefuseFriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RefuseTradeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RefuseBattleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RefuseTeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RefuseGuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_CloseGuideOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_LockShortcutOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_CloseChatBubbleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_RefuseStrangerMessaageOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RefuseAllMessaageOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
    void ID_CHECKBOX_AutomatismOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	void RefreshUI();
	void SetRefuseStrangerMessage(bool val);
	void SetRefuseAllMessage(bool val);

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视


private:
	bool				m_bShowPlayerName;
	bool				m_bShowPlayerHP;
	bool				m_bShowPlayerGuild;
	bool				m_bShowOthersHP;
	bool				m_bShowMonsterName;
	bool				m_bShowMonsterHP;

	bool				m_bRefuseFriend;
	bool				m_bRefuseTrade;
	bool				m_bRefuseBattle;
	bool				m_bRefuseTeam;
	bool				m_bRefuseGuild;

	bool				m_bCloseGuide;
	bool				m_bLockShortcut;
	bool				m_bChatPaoPao;

	bool				m_bRefuseStrangerMessage_New;
	bool				m_bRefuseAllMessage_New;

	bool				m_bRefuseStrangerMessage;
	bool				m_bRefuseAllMessage;
};
extern CUI_ID_FRAME_GameSet s_CUI_ID_FRAME_GameSet;
