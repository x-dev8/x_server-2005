/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\Guild_Info.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Guild_Info
#define ID_FRAME_Guild_Info		"ID_FRAME_Guild_Info"
#endif  ID_FRAME_Guild_Info
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_Level
#define ID_TEXT_Level		"ID_TEXT_Level"
#endif  ID_TEXT_Level
#ifndef ID_TEXT_PlayerNum
#define ID_TEXT_PlayerNum		"ID_TEXT_PlayerNum"
#endif  ID_TEXT_PlayerNum
#ifndef ID_EDIT_Info
#define ID_EDIT_Info		"ID_EDIT_Info"
#endif  ID_EDIT_Info
#ifndef ID_PROGRESS_Exp
#define ID_PROGRESS_Exp		"ID_PROGRESS_Exp"
#endif  ID_PROGRESS_Exp
#ifndef ID_BUTTON_Member
#define ID_BUTTON_Member		"ID_BUTTON_Member"
#endif  ID_BUTTON_Member
#ifndef ID_BUTTON_Announce
#define ID_BUTTON_Announce		"ID_BUTTON_Announce"
#endif  ID_BUTTON_Announce
#ifndef ID_BUTTON_Mgr
#define ID_BUTTON_Mgr		"ID_BUTTON_Mgr"
#endif  ID_BUTTON_Mgr
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE

namespace UI_ID_FRAME_Guild_Info
{
	// SGuildMember
	extern ControlFrame*	m_pID_FRAME_Guild_Info;
	extern ControlText*	m_pID_TEXT_Name;
	extern ControlText*	m_pID_TEXT_Level;
	extern ControlText*	m_pID_TEXT_PlayerNum;
	extern ControlEdit*	m_pID_EDIT_Info;
	extern ControlProgress*	m_pID_PROGRESS_Exp;
	extern ControlButton*	m_pID_BUTTON_Member;
	extern ControlButton*	m_pID_BUTTON_Announce;
	extern ControlButton*	m_pID_BUTTON_Mgr;
	extern ControlButton*	m_pID_BUTTON_CLOSE;

	// Frame
	bool ID_FRAME_Guild_InfoOnFrameRun();
	bool ID_FRAME_Guild_InfoOnFrameRender();
	// Edit
	void ID_EDIT_InfoOnEditEnter( ControlObject* pSender, const char* szData );
	// Button
	bool ID_BUTTON_MemberOnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_AnnounceOnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_MgrOnButtonClick( ControlObject* pSender );
	// Button
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

}
