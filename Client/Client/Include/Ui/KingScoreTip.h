/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\????\RTX\????ս\KingScoreTip.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"

#ifndef ID_FRAME_KingScoreTip
#define ID_FRAME_KingScoreTip		"ID_FRAME_KingScoreTip"
#endif  ID_FRAME_KingScoreTip
#ifndef ID_PICTURE_King
#define ID_PICTURE_King		"ID_PICTURE_King"
#endif  ID_PICTURE_King
#ifndef ID_TEXT_Name1
#define ID_TEXT_Name1		"ID_TEXT_Name1"
#endif  ID_TEXT_Name1
#ifndef ID_TEXT_Name2
#define ID_TEXT_Name2		"ID_TEXT_Name2"
#endif  ID_TEXT_Name2
#ifndef ID_PROGRESS_FriendScore
#define ID_PROGRESS_FriendScore		"ID_PROGRESS_FriendScore"
#endif  ID_PROGRESS_FriendScore
#ifndef ID_PROGRESS_EnemyScore
#define ID_PROGRESS_EnemyScore		"ID_PROGRESS_EnemyScore"
#endif  ID_PROGRESS_EnemyScore
#ifndef ID_TEXT_FriendScore
#define ID_TEXT_FriendScore		"ID_TEXT_FriendScore"
#endif  ID_TEXT_FriendScore
#ifndef ID_TEXT_EnemyScore
#define ID_TEXT_EnemyScore		"ID_TEXT_EnemyScore"
#endif  ID_TEXT_EnemyScore
#ifndef ID_TEXT_Time
#define ID_TEXT_Time		"ID_TEXT_Time"
#endif  ID_TEXT_Time
#ifndef ID_Text_FriendStar
#define ID_Text_FriendStar		"ID_Text_FriendStar"
#endif  ID_Text_FriendStar
#ifndef ID_Text_EnemyStar
#define ID_Text_EnemyStar		"ID_Text_EnemyStar"
#endif  ID_Text_EnemyStar

#ifndef ID_BUTTON_Min
#define ID_BUTTON_Min		"ID_BUTTON_Min"
#endif  ID_BUTTON_Min

struct MsgTellCountryBattlePlayerCount;
class CUI_ID_FRAME_KingScoreTip:public CUIBase
{
	// Member
public:
	CUI_ID_FRAME_KingScoreTip();

private:	
	 ControlFrame*	m_pID_FRAME_KingScoreTip;
	 ControlPicture*	m_pID_PICTURE_King;
	 ControlText*	m_pID_TEXT_Name1;
	 ControlText*	m_pID_TEXT_Name2;
	 ControlProgress*	m_pID_PROGRESS_FriendScore;
	 ControlProgress*	m_pID_PROGRESS_EnemyScore;
	 ControlText*	m_pID_TEXT_FriendScore;
	 ControlText*	m_pID_TEXT_EnemyScore;
	 ControlText*	m_pID_TEXT_Time;
	 ControlText* m_pID_Text_FriendStar;
	 ControlText* m_pID_Text_EnemyStar;
	 ControlButton* m_pID_BUTTON_Min;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_MinonClick( ControlObject* pSender );
private:
	virtual bool _LoadUI();				// ????UI
	bool DoControlConnect();	// ?????ؼ?
	virtual bool _UnLoadUI();			// ж??UI
	virtual bool _IsVisable();			// ?Ƿ??ɼ?
	virtual void _SetVisable( const bool bVisable );			// ?????Ƿ?????

	

	//-------------------------------------------------------
public:
	static const int m_nMaxLive = 6;
	void SetShow();
	void InitCampData();
	void SetTime(DWORD);
	void SetStringId(int);
	void UpdateData(MsgTellCountryBattlePlayerCount* pMsg_);

private:
	void InitMember();
	DWORD m_nTotalTime;
	DWORD m_nStartTime;
	DWORD m_nLastTime;
	int m_nStringId;
	char m_szTime[128];

private:
	void RefreshTime();
	void TranslateTimeToHMS();
	void CalaTime();
	void ShowTime();

private:
	int m_nRedCount;   
	int m_nBlueCount;
	int m_nMaxCount;

	int m_nRedMasterDeathCount;    // ?췽????????????
	int m_nBlueMasterDeathCount;   // ????????????????
	int m_nMaxDeathCount;
};
extern CUI_ID_FRAME_KingScoreTip s_CUI_ID_FRAME_KingScoreTip;
