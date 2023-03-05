/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\刘小兵\GuildAttribute.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"

#ifndef ID_FRAME_GuildAttribute
#define ID_FRAME_GuildAttribute		"ID_FRAME_GuildAttribute"
#endif  ID_FRAME_GuildAttribute
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_LeaderName
#define ID_TEXT_LeaderName		"ID_TEXT_LeaderName"
#endif  ID_TEXT_LeaderName
#ifndef ID_TEXT_Level
#define ID_TEXT_Level		"ID_TEXT_Level"
#endif  ID_TEXT_Level
#ifndef ID_TEXT_Exp
#define ID_TEXT_Exp		"ID_TEXT_Exp"
#endif  ID_TEXT_Exp
#ifndef ID_TEXT_Person
#define ID_TEXT_Person		"ID_TEXT_Person"
#endif  ID_TEXT_Person
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_TEXT_Duty
#define ID_TEXT_Duty		"ID_TEXT_Duty"
#endif  ID_TEXT_Duty
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE

class CUI_ID_FRAME_GuildAttribute: public CUIBase
{
	// Member
private:	
	 ControlFrame*	m_pID_FRAME_GuildAttribute;
	 ControlText*	m_pID_TEXT_Name;
	 ControlText*	m_pID_TEXT_LeaderName;
	 ControlText*	m_pID_TEXT_Level;
	 ControlText*	m_pID_TEXT_Exp;
	 ControlText*	m_pID_TEXT_Person;
	 ControlText*	m_pID_TEXT_Money;
	 ControlText*	m_pID_TEXT_Duty;
	 //ControlButton*	m_pID_BUTTON_CLOSE;

public:	
	CUI_ID_FRAME_GuildAttribute();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

private:	
	void SetAttribute();
};
extern CUI_ID_FRAME_GuildAttribute s_CUI_ID_FRAME_GuildAttribute;
