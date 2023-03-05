/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yangxiaoyong\桌面\师徒\Master.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "RelationConfig.h"
#include "PlayerRole.h"

#ifndef ID_FRAME_Master
#define ID_FRAME_Master		"ID_FRAME_Master"
#endif  ID_FRAME_Master
#ifndef ID_TEXT_Point
#define ID_TEXT_Point		"ID_TEXT_Point"
#endif  ID_TEXT_Point
#ifndef ID_TEXT_Level
#define ID_TEXT_Level		"ID_TEXT_Level"
#endif  ID_TEXT_Level
#ifndef ID_PICTURE_MemberWall
#define ID_PICTURE_MemberWall		"ID_PICTURE_MemberWall"
#endif  ID_PICTURE_MemberWall
#ifndef ID_LIST_Member
#define ID_LIST_Member		"ID_LIST_Member"
#endif  ID_LIST_Member
#ifndef ID_BUTTON_Kick
#define ID_BUTTON_Kick		"ID_BUTTON_Kick"
#endif  ID_BUTTON_Kick
#ifndef ID_BUTTON_Leave
#define ID_BUTTON_Leave		"ID_BUTTON_Leave"
#endif  ID_BUTTON_Leave
#ifndef ID_BUTTON_Teach
#define ID_BUTTON_Teach		"ID_BUTTON_Teach"
#endif  ID_BUTTON_Teach
#ifndef ID_BUTTON_Report
#define ID_BUTTON_Report		"ID_BUTTON_Report"
#endif  ID_BUTTON_Report
#ifndef ID_LIST_GuanXi
#define ID_LIST_GuanXi		"ID_LIST_GuanXi"
#endif  ID_LIST_GuanXi
#ifndef ID_TEXT_Explain
#define ID_TEXT_Explain		"ID_TEXT_Explain"
#endif  ID_TEXT_Explain
#ifndef ID_BUTTON_ChooseStudent
#define ID_BUTTON_ChooseStudent		"ID_BUTTON_ChooseStudent"
#endif  ID_BUTTON_ChooseStudent
#ifndef ID_BUTTON_ChooseTeacher
#define ID_BUTTON_ChooseTeacher		"ID_BUTTON_ChooseTeacher"
#endif  ID_BUTTON_ChooseTeacher
#ifndef ID_BUTTON_AddFriend
#define ID_BUTTON_AddFriend		"ID_BUTTON_AddFriend"
#endif  ID_BUTTON_AddFriend
#ifndef ID_BUTTON_Team
#define ID_BUTTON_Team		"ID_BUTTON_Team"
#endif  ID_BUTTON_Team
#ifndef ID_TEXT_Explain2
#define ID_TEXT_Explain2		"ID_TEXT_Explain2"
#endif  ID_TEXT_Explain2

#include "UiBase.h"
class CUI_ID_FRAME_Master :public CUIBase
{
	// Member
private:
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_Master;
	ControlText*	m_pID_TEXT_Point;
	ControlText*	m_pID_TEXT_Level;
	ControlPicture*	m_pID_PICTURE_MemberWall;
	ControlList*	m_pID_LIST_Member;
	ControlButton*	m_pID_BUTTON_Kick;
	ControlButton*	m_pID_BUTTON_Leave;
// 	ControlButton*	m_pID_BUTTON_Teach;
// 	ControlButton*	m_pID_BUTTON_Report;
	ControlList*	m_pID_LIST_GuanXi;
	ControlText*	m_pID_TEXT_Explain;
// 	ControlButton*	m_pID_BUTTON_ChooseStudent;
// 	ControlButton*	m_pID_BUTTON_ChooseTeacher;
// 	ControlButton*	m_pID_BUTTON_AddFriend;
	ControlButton*	m_pID_BUTTON_Team;
	 ControlText*	m_pID_TEXT_Explain2;

public:	
	CUI_ID_FRAME_Master();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_MemberOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_KickOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LeaveOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_TeachOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_ReportOnButtonClick( ControlObject* pSender );
	void ID_LIST_GuanXiOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
// 	bool ID_BUTTON_ChooseStudentOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_ChooseTeacherOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_AddFriendOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TeamOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	enum EMasterType
	{
		eMT_None,				// 无师傅无徒弟
		eMT_Teacher,			// 师傅
		eMT_Student,			// 徒弟
	};

	ControlFrame* GetFrame() { return m_pID_FRAME_Master; }
	void NeedRefresh() { m_bNeedRefresh = true; }


	bool IsKickRelation() { return m_bKickRelation; }
	void SetKickRelation(bool bSet) { m_bKickRelation = bSet; }

private:
	static bool sendReqKickAndLeaver( const char bPressYesButton, void *pData );	// 逐出/叛离师门MessageBox回调
	static void ID_List_OnRBClick( ControlObject* pSender, ControlList::S_List* pItem );	// 列表右击回调
	static void ID_List_OnLDBClick( ControlObject* pSender, ControlList::S_List* pItem );	// 列表双击回调
	static void HyberClickInfo( ControlObject* pSender, const char* szName );

	void RefreshALL();			// 刷新所有控件
	void Reset();				// 重置成员变量
	void ClearAll();			// 重置界面
	void Refresh();				// 刷新界面
	bool RetreiveMemberList(bool bFindTeacher);	// 获取师傅或徒弟列表, bFindTeacher: true: 搜师傅，false:搜徒弟
	void GetSexProfessionString( RelationDataToClient &friendData, std::string &strSex, string &strProfession );

	EMasterType			m_eType;
	unsigned char		m_uchMasterLevel;		// 师门等级
	DWORD				m_dwMasterValue;        // 威望值
	DWORD				m_dwMaxMasterValue;		// 师门等级对应最大威望值
	DWORD				m_dwExperience;         // 自己为徒弟时候, 保存的历练值

	bool				m_bNeedRefresh;
	bool				m_bKickRelation;		// 主动解除关系
};
extern CUI_ID_FRAME_Master s_CUI_ID_FRAME_Master;
