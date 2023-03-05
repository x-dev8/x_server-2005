/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\SettingGame.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

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
#ifndef ID_CHECKBOX_SelfHP
#define ID_CHECKBOX_SelfHP		"ID_CHECKBOX_SelfHP"
#endif  ID_CHECKBOX_SelfHP
#ifndef ID_CHECKBOX_PlayerName
#define ID_CHECKBOX_PlayerName		"ID_CHECKBOX_PlayerName"
#endif  ID_CHECKBOX_PlayerName
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
#ifndef ID_CHECKBOX_RefuseStrangerMessaage
#define ID_CHECKBOX_RefuseStrangerMessaage		"ID_CHECKBOX_RefuseStrangerMessaage"
#endif  ID_CHECKBOX_RefuseStrangerMessaage
#ifndef ID_CHECKBOX_RefuseAllMessaage
#define ID_CHECKBOX_RefuseAllMessaage		"ID_CHECKBOX_RefuseAllMessaage"
#endif  ID_CHECKBOX_RefuseAllMessaage
#ifndef ID_CHECKBOX_Automatism
#define ID_CHECKBOX_Automatism		"ID_CHECKBOX_Automatism"
#endif  ID_CHECKBOX_Automatism
#ifndef ID_CHECKBOX_PlayerCH
#define ID_CHECKBOX_PlayerCH		"ID_CHECKBOX_PlayerCH"
#endif  ID_CHECKBOX_PlayerCH
#ifndef ID_CHECKBOX_PetName
#define ID_CHECKBOX_PetName		"ID_CHECKBOX_PetName"
#endif  ID_CHECKBOX_PetName
#ifndef ID_CHECKBOX_PetMaster
#define ID_CHECKBOX_PetMaster		"ID_CHECKBOX_PetMaster"
#endif  ID_CHECKBOX_PetMaster
#ifndef ID_CHECKBOX_PetHP
#define ID_CHECKBOX_PetHP		"ID_CHECKBOX_PetHP"
#endif  ID_CHECKBOX_PetHP
#ifndef ID_CHECKBOX_OtherPetHP
#define ID_CHECKBOX_OtherPetHP		"ID_CHECKBOX_OtherPetHP"
#endif  ID_CHECKBOX_OtherPetHP
#ifndef ID_CHECKBOX_HPLetter
#define ID_CHECKBOX_HPLetter		"ID_CHECKBOX_HPLetter"
#endif  ID_CHECKBOX_HPLetter
#ifndef ID_SCROLLBAREX_Agility
#define ID_SCROLLBAREX_Agility		"ID_SCROLLBAREX_Agility"
#endif  ID_SCROLLBAREX_Agility
#ifndef ID_SCROLLBAREX_Speed
#define ID_SCROLLBAREX_Speed		"ID_SCROLLBAREX_Speed"
#endif  ID_SCROLLBAREX_Speed

class CUI_ID_FRAME_GameSetup :public CUIBase
{
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_GameSet;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_Default;
	 ControlCheckBox*	m_pID_CHECKBOX_SelfHP;
	 ControlCheckBox*	m_pID_CHECKBOX_PlayerName;
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
	 ControlCheckBox*	m_pID_CHECKBOX_RefuseStrangerMessaage;
	 ControlCheckBox*	m_pID_CHECKBOX_RefuseAllMessaage;
	 ControlCheckBox*	m_pID_CHECKBOX_Automatism;
	 ControlCheckBox*	m_pID_CHECKBOX_PlayerCH;
	 ControlCheckBox*	m_pID_CHECKBOX_PetName;
	 ControlCheckBox*	m_pID_CHECKBOX_PetMaster;
	 ControlCheckBox*	m_pID_CHECKBOX_PetHP;
	 ControlCheckBox*	m_pID_CHECKBOX_OtherPetHP;
	 ControlCheckBox*	m_pID_CHECKBOX_HPLetter;
	 ControlScrollBarEx*	m_pID_SCROLLBAREX_Agility;
	 ControlScrollBarEx*	m_pID_SCROLLBAREX_Speed;


public:	
	// Frame
	CUI_ID_FRAME_GameSetup();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_SelfHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PlayerNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
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
	void ID_CHECKBOX_RefuseStrangerMessaageOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_RefuseAllMessaageOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_AutomatismOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PlayerCHOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PetNameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PetMasterOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_PetHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_OtherPetHPOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_HPLetterOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_SCROLLBAREX_AgilityOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	void ID_SCROLLBAREX_SpeedOnScrollBarExUpdatePos( ControlObject* pSender, int n );

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual void InitializeAtEnterWorld();
private:	
	bool bShowHotkey;//
	bool ShowItemName;
	bool ShowNpcName;
	bool ShowPlayerName;
	bool ShowHP;
	bool ShowMP;
	bool ShowFP;
	int	CameraRotateSpeed;
	int	MouseSpeed;
public:
	void RefreshUI();

	void SetShowHp(bool bValue){ShowHP = bValue;}
	bool GetShowHp(){return ShowHP;}

	void SetShowMp(bool bValue){ShowMP = bValue;}
	bool GetShowMp(){return ShowMP;}

	void SetShowFp(bool bValue){ShowFP = bValue;}
	bool GetShowFp(){return ShowFP;}

	void SetShowHotKey(bool bValue){bShowHotkey = bValue;}
	bool GetShowHotKey(){return bShowHotkey;}

	void SetShowItemName(bool bValue){ShowItemName = bValue;}
	bool GetShowItemName(){return ShowItemName;}

	void SetShowPlayerName(bool bValue){ShowPlayerName = bValue;}
	bool GetShowPlayerName(){return ShowPlayerName;}

	void SetShowNpcName(bool bValue){ShowNpcName = bValue;}
	bool GetShowNpcName(){return ShowNpcName;}

	void SetRotateSpeed(int nValue){CameraRotateSpeed = nValue;}
	int GetRotateSpeed(){return CameraRotateSpeed;}

	void SetMouseSpeed(int nValue){MouseSpeed = nValue;}
	int GetMouseSpeed(){return MouseSpeed;}
};
extern CUI_ID_FRAME_GameSetup s_CUI_ID_FRAME_GameSetup;
