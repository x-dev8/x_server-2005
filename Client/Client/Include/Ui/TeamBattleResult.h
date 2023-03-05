/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\chixin.ni\桌面\TeamBattleResult.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MessageDefine.h"

#ifndef ID_FRAME_TeamBattleResult
#define ID_FRAME_TeamBattleResult		"ID_FRAME_TeamBattleResult"
#endif  ID_FRAME_TeamBattleResult
#ifndef ID_PICTURE_Di
#define ID_PICTURE_Di		"ID_PICTURE_Di"
#endif  ID_PICTURE_Di
#ifndef ID_CHECKBOX_All
#define ID_CHECKBOX_All		"ID_CHECKBOX_All"
#endif  ID_CHECKBOX_All
#ifndef ID_CHECKBOX_Sui
#define ID_CHECKBOX_Sui		"ID_CHECKBOX_Sui"
#endif  ID_CHECKBOX_Sui
#ifndef ID_PICTURE_WallPaper
#define ID_PICTURE_WallPaper		"ID_PICTURE_WallPaper"
#endif  ID_PICTURE_WallPaper
#ifndef ID_PICTURE_TitleDi
#define ID_PICTURE_TitleDi		"ID_PICTURE_TitleDi"
#endif  ID_PICTURE_TitleDi
#ifndef ID_PICTURE_10248
#define ID_PICTURE_10248		"ID_PICTURE_10248"
#endif  ID_PICTURE_10248
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_PICTURE_WallLeft2
#define ID_PICTURE_WallLeft2		"ID_PICTURE_WallLeft2"
#endif  ID_PICTURE_WallLeft2
#ifndef ID_PICTURE_WallRight2
#define ID_PICTURE_WallRight2		"ID_PICTURE_WallRight2"
#endif  ID_PICTURE_WallRight2
#ifndef ID_PICTURE_WallLeft
#define ID_PICTURE_WallLeft		"ID_PICTURE_WallLeft"
#endif  ID_PICTURE_WallLeft
#ifndef ID_PICTURE_WallRight
#define ID_PICTURE_WallRight		"ID_PICTURE_WallRight"
#endif  ID_PICTURE_WallRight
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_BUTTON_PlayerName
#define ID_BUTTON_PlayerName		"ID_BUTTON_PlayerName"
#endif  ID_BUTTON_PlayerName
#ifndef ID_BUTTON_KillNumber
#define ID_BUTTON_KillNumber		"ID_BUTTON_KillNumber"
#endif  ID_BUTTON_KillNumber
#ifndef ID_BUTTON_Damage
#define ID_BUTTON_Damage		"ID_BUTTON_Damage"
#endif  ID_BUTTON_Damage
#ifndef ID_LIST_PlayerName
#define ID_LIST_PlayerName		"ID_LIST_PlayerName"
#endif  ID_LIST_PlayerName
#ifndef ID_LIST_KillNumber
#define ID_LIST_KillNumber		"ID_LIST_KillNumber"
#endif  ID_LIST_KillNumber
#ifndef ID_LIST_DeathNumber
#define ID_LIST_DeathNumber		"ID_LIST_DeathNumber"
#endif  ID_LIST_DeathNumber
#ifndef ID_TEXT_ArrowPlayerName
#define ID_TEXT_ArrowPlayerName		"ID_TEXT_ArrowPlayerName"
#endif  ID_TEXT_ArrowPlayerName
#ifndef ID_TEXT_ArrowKillNumber
#define ID_TEXT_ArrowKillNumber		"ID_TEXT_ArrowKillNumber"
#endif  ID_TEXT_ArrowKillNumber
#ifndef ID_TEXT_ArrowDamage
#define ID_TEXT_ArrowDamage		"ID_TEXT_ArrowDamage"
#endif  ID_TEXT_ArrowDamage
#ifndef ID_LIST_Damage
#define ID_LIST_Damage		"ID_LIST_Damage"
#endif  ID_LIST_Damage
#ifndef ID_BUTTON_DeathNumber
#define ID_BUTTON_DeathNumber		"ID_BUTTON_DeathNumber"
#endif  ID_BUTTON_DeathNumber
#ifndef ID_TEXT_ArrowDeathNumber
#define ID_TEXT_ArrowDeathNumber		"ID_TEXT_ArrowDeathNumber"
#endif  ID_TEXT_ArrowDeathNumber
#ifndef ID_BUTTON_Heal
#define ID_BUTTON_Heal		"ID_BUTTON_Heal"
#endif  ID_BUTTON_Heal
#ifndef ID_TEXT_ArrowHeal
#define ID_TEXT_ArrowHeal		"ID_TEXT_ArrowHeal"
#endif  ID_TEXT_ArrowHeal
#ifndef ID_LIST_Heal
#define ID_LIST_Heal		"ID_LIST_Heal"
#endif  ID_LIST_Heal
#ifndef ID_LIST_Resource
#define ID_LIST_Resource		"ID_LIST_Resource"
#endif  ID_LIST_Resource
#ifndef ID_BUTTON_Resource
#define ID_BUTTON_Resource		"ID_BUTTON_Resource"
#endif  ID_BUTTON_Resource
#ifndef ID_TEXT_ArrowResource
#define ID_TEXT_ArrowResource		"ID_TEXT_ArrowResource"
#endif  ID_TEXT_ArrowResource
#ifndef ID_BUTTON_Exit
#define ID_BUTTON_Exit		"ID_BUTTON_Exit"
#endif  ID_BUTTON_Exit
#ifndef ID_LIST_Honor
#define ID_LIST_Honor		"ID_LIST_Honor"
#endif  ID_LIST_Honor
#ifndef ID_BUTTON_Honor
#define ID_BUTTON_Honor		"ID_BUTTON_Honor"
#endif  ID_BUTTON_Honor
#ifndef ID_TEXT_ArrowHonor
#define ID_TEXT_ArrowHonor		"ID_TEXT_ArrowHonor"
#endif  ID_TEXT_ArrowHonor
#ifndef ID_TEXT_CostTime
#define ID_TEXT_CostTime		"ID_TEXT_CostTime"
#endif  ID_TEXT_CostTime
#ifndef ID_LIST_PlayerList
#define ID_LIST_PlayerList		"ID_LIST_PlayerList"
#endif  ID_LIST_PlayerList
#ifndef ID_LIST_PlayerIcon
#define ID_LIST_PlayerIcon		"ID_LIST_PlayerIcon"
#endif  ID_LIST_PlayerIcon

#include "UiBase.h"
class CUI_ID_FRAME_TeamBattleResult :public CUIBase
{
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_TeamBattleResult;
	 ControlPicture*	m_pID_PICTURE_Di;
	 ControlCheckBox*	m_pID_CHECKBOX_All;
	 ControlCheckBox*	m_pID_CHECKBOX_Sui;
	 ControlPicture*	m_pID_PICTURE_WallPaper;
	 ControlPicture*	m_pID_PICTURE_TitleDi;
	 ControlPicture*	m_pID_PICTURE_10248;
	 ControlText*	m_pID_TEXT_Title;
	 ControlPicture*	m_pID_PICTURE_WallLeft2;
	 ControlPicture*	m_pID_PICTURE_WallRight2;
	 ControlPicture*	m_pID_PICTURE_WallLeft;
	 ControlPicture*	m_pID_PICTURE_WallRight;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_help;
	 ControlButton*	m_pID_BUTTON_PlayerName;
	 ControlButton*	m_pID_BUTTON_KillNumber;
	 ControlButton*	m_pID_BUTTON_Damage;
	 ControlList*	m_pID_LIST_PlayerName;
	 ControlList*	m_pID_LIST_KillNumber;
	 ControlList*	m_pID_LIST_DeathNumber;
	 ControlText*	m_pID_TEXT_ArrowPlayerName;
	 ControlText*	m_pID_TEXT_ArrowKillNumber;
// 	 ControlText*	m_pID_TEXT_ArrowDamage;
// 	 ControlList*	m_pID_LIST_Damage;
	 ControlButton*	m_pID_BUTTON_DeathNumber;
	 ControlText*	m_pID_TEXT_ArrowDeathNumber;
// 	 ControlButton*	m_pID_BUTTON_Heal;
// 	 ControlText*	m_pID_TEXT_ArrowHeal;
// 	 ControlList*	m_pID_LIST_Heal;
	 ControlList*	m_pID_LIST_Resource;
	 ControlButton*	m_pID_BUTTON_Resource;
	 ControlText*	m_pID_TEXT_ArrowResource;
	 ControlButton*	m_pID_BUTTON_Exit;
	 ControlList*	m_pID_LIST_Honor;
	 ControlButton*	m_pID_BUTTON_Honor;
	 ControlText*	m_pID_TEXT_ArrowHonor;
//	 ControlText*	m_pID_TEXT_CostTime;
	 ControlList*	m_pID_LIST_PlayerList;
	 ControlList*	m_pID_LIST_PlayerIcon;
public:
	// Frame
	 CUI_ID_FRAME_TeamBattleResult();
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_CHECKBOX_AllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PlayerNameOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_KillNumberOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DamageOnButtonClick( ControlObject* pSender );
	void ID_LIST_PlayerNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_KillNumberOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_DeathNumberOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	//void ID_LIST_DamageOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_DeathNumberOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_HealOnButtonClick( ControlObject* pSender );
	//void ID_LIST_HealOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ResourceOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_ResourceOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ExitOnButtonClick( ControlObject* pSender );
	void ID_LIST_HonorOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_HonorOnButtonClick( ControlObject* pSender );
	void ID_LIST_PlayerListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_PlayerIconOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void OnRecord( MsgTellBattleRecord* pRecord );
	void OnTeamRecord( MsgQueryTeamRecordAck* pRecord );
	void Refresh();
	void SetBeginTime();
	void RefreshTime();
	void SetEnd( bool b ){ m_end = b; }

	vector<MsgTellBattleRecord::RecordInfo> m_vecRecordInfoNoSort;
private:

	vector<MsgTellBattleRecord::RecordInfo> m_vecRecordInfo;
	vector<MsgQueryTeamRecordAck::RecordInfo> m_vecTeamRecordInfo;

	DWORD m_BeginTime;
	DWORD m_EndTime;
	bool  m_end;

	int m_worningTime;
	int m_worningTime2;

	int m_sel;
};
extern CUI_ID_FRAME_TeamBattleResult s_CUI_ID_FRAME_TeamBattleResult;
