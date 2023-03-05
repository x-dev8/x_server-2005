/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\chixin.ni\桌面\TeamBattleState.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MessageDefine.h"

#ifndef ID_FRAME_TeamBattleState
#define ID_FRAME_TeamBattleState		"ID_FRAME_TeamBattleState"
#endif  ID_FRAME_TeamBattleState
#ifndef ID_PICTURE_Tang
#define ID_PICTURE_Tang		"ID_PICTURE_Tang"
#endif  ID_PICTURE_Tang
#ifndef ID_TEXT_Tang
#define ID_TEXT_Tang		"ID_TEXT_Tang"
#endif  ID_TEXT_Tang
#ifndef ID_BUTTON_ShowState
#define ID_BUTTON_ShowState		"ID_BUTTON_ShowState"
#endif  ID_BUTTON_ShowState

#include "UiBase.h"
class CUI_ID_FRAME_TeamBattleState :public CUIBase
{
	// Member
private:
	 ControlFrame*	m_pID_FRAME_TeamBattleState;
	 ControlPicture*	m_pID_PICTURE_Tang;
	 ControlText*	m_pID_TEXT_Tang;
	 ControlButton*	m_pID_BUTTON_ShowState;
public:	
	 CUI_ID_FRAME_TeamBattleState();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_ShowStateOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void OnRecord( MsgTellBattleRecord* pRecord );
	void Refresh();
	void SetRank( int rank ){ m_Rank = rank; }

private:
	MsgTellBattleRecord::RecordInfo m_Info;
	int m_Rank;
};
extern CUI_ID_FRAME_TeamBattleState s_CUI_ID_FRAME_TeamBattleState;
