/********************************************************************
	Created by UIEditor.exe
	FileName: E:\trunk2\Bin\Client\Data\Ui\TeamBattleRequest.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MessageDefine.h"
#include "me3d/Vector.h"

#ifndef ID_FRAME_TeamBattleRequest
#define ID_FRAME_TeamBattleRequest		"ID_FRAME_TeamBattleRequest"
#endif  ID_FRAME_TeamBattleRequest
#ifndef ID_PICTURE_BackWall
#define ID_PICTURE_BackWall		"ID_PICTURE_BackWall"
#endif  ID_PICTURE_BackWall
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_Team
#define ID_BUTTON_Team		"ID_BUTTON_Team"
#endif  ID_BUTTON_Team
#ifndef ID_TEXT_NameA
#define ID_TEXT_NameA		"ID_TEXT_NameA"
#endif  ID_TEXT_NameA
#ifndef ID_TEXT_NameB
#define ID_TEXT_NameB		"ID_TEXT_NameB"
#endif  ID_TEXT_NameB
#ifndef ID_LIST_NameA
#define ID_LIST_NameA		"ID_LIST_NameA"
#endif  ID_LIST_NameA
#ifndef ID_LIST_NameB
#define ID_LIST_NameB		"ID_LIST_NameB"
#endif  ID_LIST_NameB
#ifndef ID_LIST_All
#define ID_LIST_All		"ID_LIST_All"
#endif  ID_LIST_All
#ifndef ID_TEXT_LastTime
#define ID_TEXT_LastTime		"ID_TEXT_LastTime"
#endif  ID_TEXT_LastTime
#ifndef ID_BUTTON_ShowTeam
#define ID_BUTTON_ShowTeam		"ID_BUTTON_ShowTeam"
#endif  ID_BUTTON_ShowTeam

#include "UiBase.h"
class CUI_ID_FRAME_TeamBattleRequest :public CUIBase
{
	// Member
private:
	 ControlFrame*	m_pID_FRAME_TeamBattleRequest;
	 ControlPicture*	m_pID_PICTURE_BackWall;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_Team;
	 ControlText*	m_pID_TEXT_NameA;
	 ControlText*	m_pID_TEXT_NameB;
	 ControlList*	m_pID_LIST_NameA;
	 ControlList*	m_pID_LIST_NameB;
	 ControlList*	m_pID_LIST_All;
	 ControlText*	m_pID_TEXT_LastTime;
	 ControlButton*	m_pID_BUTTON_ShowTeam;
public:	
	 CUI_ID_FRAME_TeamBattleRequest();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TeamOnButtonClick( ControlObject* pSender );
	void ID_LIST_NameAOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_NameBOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_AllOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_ShowTeamOnButtonClick( ControlObject* pSender );
	
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void Show( MsgShowBattleSignUpDlg* ack );
	void ShowTime(MsgQueryBattleSignUpTimeAck* ack);
	void OnAck( MsgBattleSignUpAck* pMsg );
	void OnTeamInfo( MsgTellBattleSignUpInfo* pMsg );
	void NotifyEnter();
	void Refresh();
	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }
	const Vector& GetVisiblePosition() const { return m_vVisiblePos; }

	MsgShowBattleSignUpDlg::SignUpInfo m_SignInfo;
private:
	Vector m_vVisiblePos;	

	vector<string> m_vecName;
	vector<int>	   m_vecTeamID;
	

	DWORD m_leftTime;
	int   m_Timestate;
	DWORD m_MsgSendTimeCount;
};
extern CUI_ID_FRAME_TeamBattleRequest s_CUI_ID_FRAME_TeamBattleRequest;
