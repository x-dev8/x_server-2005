/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\chixin.ni\桌面\TeamBattleShowTeamInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MessageDefine.h"
#include "me3d/Vector.h"

#ifndef ID_FRAME_TeamBattleShowTeamInfo
#define ID_FRAME_TeamBattleShowTeamInfo		"ID_FRAME_TeamBattleShowTeamInfo"
#endif  ID_FRAME_TeamBattleShowTeamInfo
#ifndef ID_PICTURE_BackWall
#define ID_PICTURE_BackWall		"ID_PICTURE_BackWall"
#endif  ID_PICTURE_BackWall
#ifndef ID_BUTTON_Back
#define ID_BUTTON_Back		"ID_BUTTON_Back"
#endif  ID_BUTTON_Back
#ifndef ID_BUTTON_Team
#define ID_BUTTON_Team		"ID_BUTTON_Team"
#endif  ID_BUTTON_Team
#ifndef ID_LIST_Name
#define ID_LIST_Name		"ID_LIST_Name"
#endif  ID_LIST_Name
#ifndef ID_LIST_Lvl
#define ID_LIST_Lvl		"ID_LIST_Lvl"
#endif  ID_LIST_Lvl
#ifndef ID_LIST_All
#define ID_LIST_All		"ID_LIST_All"
#endif  ID_LIST_All
#ifndef ID_TEXT_LastTime
#define ID_TEXT_LastTime		"ID_TEXT_LastTime"
#endif  ID_TEXT_LastTime
#ifndef ID_TEXT_NameZ
#define ID_TEXT_NameZ		"ID_TEXT_NameZ"
#endif  ID_TEXT_NameZ
#ifndef ID_TEXT_LvlZ
#define ID_TEXT_LvlZ		"ID_TEXT_LvlZ"
#endif  ID_TEXT_LvlZ
#ifndef ID_TEXT_JobZ
#define ID_TEXT_JobZ		"ID_TEXT_JobZ"
#endif  ID_TEXT_JobZ
#ifndef ID_TEXT_GangZ
#define ID_TEXT_GangZ		"ID_TEXT_GangZ"
#endif  ID_TEXT_GangZ
#ifndef ID_LIST_Job
#define ID_LIST_Job		"ID_LIST_Job"
#endif  ID_LIST_Job
#ifndef ID_LIST_Gang
#define ID_LIST_Gang		"ID_LIST_Gang"
#endif  ID_LIST_Gang

#include "UiBase.h"
class CUI_ID_FRAME_TeamBattleShowTeamInfo :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_TeamBattleShowTeamInfo();
	 ControlFrame*	m_pID_FRAME_TeamBattleShowTeamInfo;
	 ControlPicture*	m_pID_PICTURE_BackWall;
	 ControlButton*	m_pID_BUTTON_Back;
	 ControlButton*	m_pID_BUTTON_Team;
	 ControlList*	m_pID_LIST_Name;
	 ControlList*	m_pID_LIST_Lvl;
	 ControlList*	m_pID_LIST_All;
	 ControlText*	m_pID_TEXT_LastTime;
	 ControlText*	m_pID_TEXT_NameZ;
	 ControlText*	m_pID_TEXT_LvlZ;
	 ControlText*	m_pID_TEXT_JobZ;
	 //ControlText*	m_pID_TEXT_GangZ;
	 ControlList*	m_pID_LIST_Job;
	// ControlList*	m_pID_LIST_Gang;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_BackOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TeamOnButtonClick( ControlObject* pSender );
	void ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_LvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_AllOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_JobOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	//void ID_LIST_GangOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	void Show(MsgShowBattleSignUpDlg* ack);
	void ShowTime(MsgQueryBattleSignUpTimeAck* ack);
	const Vector& GetVisiblePosition() const { return m_vVisiblePos; }
	void SetVisiblePosition( const Vector& vPos ){ m_vVisiblePos = vPos; }
	void ShowInfo(MsgQueryBattleTeamInfoAck* pMsg);

private:
	Vector m_vVisiblePos;	
	MsgShowBattleSignUpDlg::SignUpInfo m_SignInfo;

	DWORD m_leftTime;
	int   m_Timestate;
	DWORD m_MsgSendTimeCount;
};
extern CUI_ID_FRAME_TeamBattleShowTeamInfo s_CUI_ID_FRAME_TeamBattleShowTeamInfo;
