/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yangxiaoyong\����\ʦͽ\Master.h
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
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
public:


	enum EMasterType
	{
		eMT_None,				// ��ʦ����ͽ��
		eMT_Teacher,			// ʦ��
		eMT_Student,			// ͽ��
	};

	ControlFrame* GetFrame() { return m_pID_FRAME_Master; }
	void NeedRefresh() { m_bNeedRefresh = true; }


	bool IsKickRelation() { return m_bKickRelation; }
	void SetKickRelation(bool bSet) { m_bKickRelation = bSet; }

private:
	static bool sendReqKickAndLeaver( const char bPressYesButton, void *pData );	// ���/����ʦ��MessageBox�ص�
	static void ID_List_OnRBClick( ControlObject* pSender, ControlList::S_List* pItem );	// �б��һ��ص�
	static void ID_List_OnLDBClick( ControlObject* pSender, ControlList::S_List* pItem );	// �б�˫���ص�
	static void HyberClickInfo( ControlObject* pSender, const char* szName );

	void RefreshALL();			// ˢ�����пؼ�
	void Reset();				// ���ó�Ա����
	void ClearAll();			// ���ý���
	void Refresh();				// ˢ�½���
	bool RetreiveMemberList(bool bFindTeacher);	// ��ȡʦ����ͽ���б�, bFindTeacher: true: ��ʦ����false:��ͽ��
	void GetSexProfessionString( RelationDataToClient &friendData, std::string &strSex, string &strProfession );

	EMasterType			m_eType;
	unsigned char		m_uchMasterLevel;		// ʦ�ŵȼ�
	DWORD				m_dwMasterValue;        // ����ֵ
	DWORD				m_dwMaxMasterValue;		// ʦ�ŵȼ���Ӧ�������ֵ
	DWORD				m_dwExperience;         // �Լ�Ϊͽ��ʱ��, ���������ֵ

	bool				m_bNeedRefresh;
	bool				m_bKickRelation;		// ���������ϵ
};
extern CUI_ID_FRAME_Master s_CUI_ID_FRAME_Master;
