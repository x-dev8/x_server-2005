/********************************************************************
	Created by UIEditor.exe
	FileName: D:\SVNClient\sg_pro\3Guo_Main\FullClient\Data\Ui\LeaveExp.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#ifndef ID_FRAME_LeaveExp
#define ID_FRAME_LeaveExp		"ID_FRAME_LeaveExp"
#endif  ID_FRAME_LeaveExp
#ifndef ID_TEXT_AllKillSum
#define ID_TEXT_AllKillSum		"ID_TEXT_AllKillSum"
#endif  ID_TEXT_AllKillSum
#ifndef ID_TEXT_MaxKillSum
#define ID_TEXT_MaxKillSum		"ID_TEXT_MaxKillSum"
#endif  ID_TEXT_MaxKillSum
#ifndef ID_TEXT_ExpRad
#define ID_TEXT_ExpRad		"ID_TEXT_ExpRad"
#endif  ID_TEXT_ExpRad
#ifndef ID_TEXT_LeaveHour
#define ID_TEXT_LeaveHour		"ID_TEXT_LeaveHour"
#endif  ID_TEXT_LeaveHour
#ifndef ID_TEXT_ExpSum
#define ID_TEXT_ExpSum		"ID_TEXT_ExpSum"
#endif  ID_TEXT_ExpSum
#ifndef ID_BUTTON_GetExp
#define ID_BUTTON_GetExp		"ID_BUTTON_GetExp"
#endif  ID_BUTTON_GetExp

class CUI_ID_FRAME_LeaveExp : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_LeaveExp();
	 ControlFrame*	m_pID_FRAME_LeaveExp;
	 ControlText*	m_pID_TEXT_AllKillSum;
	 ControlText*	m_pID_TEXT_MaxKillSum;
	 ControlText*	m_pID_TEXT_ExpRad;
	 ControlText*	m_pID_TEXT_LeaveHour;
	 ControlText*	m_pID_TEXT_ExpSum;
	 ControlButton*	m_pID_BUTTON_GetExp;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_GetExpOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void OnShow();
	void Clear();
	void SetInfo(unsigned int KillSum,unsigned int MaxKillSum,float Rad,unsigned int Hour,unsigned int Exp);
};
extern CUI_ID_FRAME_LeaveExp s_CUI_ID_FRAME_LeaveExp;
