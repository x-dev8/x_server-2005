/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\guildcamp\ScoreTip.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"

#ifndef ID_FRAME_ScoreTip
#define ID_FRAME_ScoreTip		"ID_FRAME_ScoreTip"
#endif  ID_FRAME_ScoreTip
#ifndef ID_TEXT_FriendScore
#define ID_TEXT_FriendScore		"ID_TEXT_FriendScore"
#endif  ID_TEXT_FriendScore
#ifndef ID_TEXT_EnemyScore
#define ID_TEXT_EnemyScore		"ID_TEXT_EnemyScore"
#endif  ID_TEXT_EnemyScore
#ifndef ID_TEXT_Name1
#define ID_TEXT_Name1		"ID_TEXT_Name1"
#endif  ID_TEXT_Name1
#ifndef ID_TEXT_Name2
#define ID_TEXT_Name2		"ID_TEXT_Name2"
#endif  ID_TEXT_Name2
#ifndef ID_TEXT_Time
#define ID_TEXT_Time		"ID_TEXT_Time"
#endif  ID_TEXT_Time
#ifndef ID_BUTTON_ShowBattleInfo
#define ID_BUTTON_ShowBattleInfo		"ID_BUTTON_ShowBattleInfo"
#endif  ID_BUTTON_ShowBattleInfo
#ifndef ID_BUTTON_Min
#define ID_BUTTON_Min		"ID_BUTTON_Min"
#endif  ID_BUTTON_Min

class CUI_ID_FRAME_ScoreTip:public CUIBase
{
	// Member
public:
	CUI_ID_FRAME_ScoreTip();

private:	 
	 ControlFrame*	m_pID_FRAME_ScoreTip;
	 ControlText*	m_pID_TEXT_FriendScore;
	 ControlText*	m_pID_TEXT_EnemyScore;
	 ControlText*	m_pID_TEXT_Name1;
	 ControlText*	m_pID_TEXT_Name2;
	 ControlText*	m_pID_TEXT_Time;
	 ControlButton*	m_pID_BUTTON_ShowBattleInfo;
	 ControlButton*	m_pID_BUTTON_Min;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_ShowBattleInfoOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MinOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	//-------------------------------------------------------
public:
	void SetShow();
	void SetTime(DWORD);
	void SetStringId(int);
	int GetStringId(){return m_nStringId;}
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
};
extern CUI_ID_FRAME_ScoreTip s_CUI_ID_FRAME_ScoreTip;
