/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\SeeSelfInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_SeeSelfInfo
#define ID_FRAME_SeeSelfInfo		"ID_FRAME_SeeSelfInfo"
#endif  ID_FRAME_SeeSelfInfo
#ifndef ID_TEXT_Age
#define ID_TEXT_Age		"ID_TEXT_Age"
#endif  ID_TEXT_Age
#ifndef ID_TEXT_City
#define ID_TEXT_City		"ID_TEXT_City"
#endif  ID_TEXT_City
#ifndef ID_TEXT_Job
#define ID_TEXT_Job		"ID_TEXT_Job"
#endif  ID_TEXT_Job
#ifndef ID_TEXT_QQ
#define ID_TEXT_QQ		"ID_TEXT_QQ"
#endif  ID_TEXT_QQ
#ifndef ID_TEXT_Desc
#define ID_TEXT_Desc		"ID_TEXT_Desc"
#endif  ID_TEXT_Desc
#ifndef ID_TEXT_Like
#define ID_TEXT_Like		"ID_TEXT_Like"
#endif  ID_TEXT_Like
#ifndef ID_TEXT_Mail
#define ID_TEXT_Mail		"ID_TEXT_Mail"
#endif  ID_TEXT_Mail
#ifndef ID_TEXT_MSN
#define ID_TEXT_MSN		"ID_TEXT_MSN"
#endif  ID_TEXT_MSN
#ifndef ID_TEXT_NickName
#define ID_TEXT_NickName		"ID_TEXT_NickName"
#endif  ID_TEXT_NickName
#ifndef ID_TEXT_Http
#define ID_TEXT_Http		"ID_TEXT_Http"
#endif  ID_TEXT_Http
#ifndef ID_TEXT_Animal
#define ID_TEXT_Animal		"ID_TEXT_Animal"
#endif  ID_TEXT_Animal
#ifndef ID_TEXT_Constellation
#define ID_TEXT_Constellation		"ID_TEXT_Constellation"
#endif  ID_TEXT_Constellation
#ifndef ID_TEXT_BirthMonth
#define ID_TEXT_BirthMonth		"ID_TEXT_BirthMonth"
#endif  ID_TEXT_BirthMonth
#ifndef ID_TEXT_BirthDay
#define ID_TEXT_BirthDay		"ID_TEXT_BirthDay"
#endif  ID_TEXT_BirthDay
#ifndef ID_TEXT_Province
#define ID_TEXT_Province		"ID_TEXT_Province"
#endif  ID_TEXT_Province
#ifndef ID_TEXT_Sex
#define ID_TEXT_Sex		"ID_TEXT_Sex"
#endif  ID_TEXT_Sex

class CUI_ID_FRAME_SeeSelfInfo:public CUIBase
{
	// Member
private:	

	 ControlFrame*	m_pID_FRAME_SeeSelfInfo;
	 ControlText*	m_pID_TEXT_Age;
	 ControlText*	m_pID_TEXT_City;
	 ControlText*	m_pID_TEXT_Job;
	 ControlText*	m_pID_TEXT_QQ;
	 ControlText*	m_pID_TEXT_Desc;
	 ControlText*	m_pID_TEXT_Like;
	 ControlText*	m_pID_TEXT_Mail;
	 ControlText*	m_pID_TEXT_MSN;
	 ControlText*	m_pID_TEXT_NickName;
	 ControlText*	m_pID_TEXT_Http;
	 ControlText*	m_pID_TEXT_Animal;
	 ControlText*	m_pID_TEXT_Constellation;
	 ControlText*	m_pID_TEXT_BirthMonth;
	 ControlText*	m_pID_TEXT_BirthDay;
	 ControlText*	m_pID_TEXT_Province;
	 ControlText*	m_pID_TEXT_Sex;

public:	
	// Frame
	CUI_ID_FRAME_SeeSelfInfo();
	bool OnFrameRun();
	bool OnFrameRender();

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视
private:	
};
extern CUI_ID_FRAME_SeeSelfInfo s_CUI_ID_FRAME_SeeSelfInfo;
