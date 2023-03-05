/********************************************************************
	Created by UIEditor.exe
	FileName: D:\Tj\Client\UI\SelectAssignMode.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "Group_Me.h"

#ifndef ID_FRAME_SelectAssignMode
#define ID_FRAME_SelectAssignMode		"ID_FRAME_SelectAssignMode"
#endif  ID_FRAME_SelectAssignMode
#ifndef ID_BUTTON_Freedom
#define ID_BUTTON_Freedom		"ID_BUTTON_Freedom"
#endif  ID_BUTTON_Freedom
#ifndef ID_BUTTON_Team
#define ID_BUTTON_Team		"ID_BUTTON_Team"
#endif  ID_BUTTON_Team
#ifndef ID_BUTTON_Random
#define ID_BUTTON_Random		"ID_BUTTON_Random"
#endif  ID_BUTTON_Random
#ifndef ID_BUTTON_Assign
#define ID_BUTTON_Assign		"ID_BUTTON_Assign"
#endif  ID_BUTTON_Assign
#ifndef ID_PICTURE_Freedom
#define ID_PICTURE_Freedom	"ID_PICTURE_Freedom"
#endif	ID_PICTURE_Freedom
#ifndef ID_PICTURE_Team
#define ID_PICTURE_Team		"ID_PICTURE_Team"
#endif	ID_PICTURE_Team
#ifndef ID_PICTURE_Random
#define ID_PICTURE_Random	"ID_PICTURE_Random"
#endif	ID_PICTURE_Random
#ifndef ID_PICTURE_Assign
#define ID_PICTURE_Assign	"ID_PICTURE_Assign"
#endif	ID_PICTURE_Assign
#ifndef ID_PICTURE_Dui
#define ID_PICTURE_Dui	"ID_PICTURE_Dui"
#endif	ID_PICTURE_Dui
#ifndef ID_PICTURE_Tuan
#define ID_PICTURE_Tuan	"ID_PICTURE_Tuan"
#endif	ID_PICTURE_Tuan

#include "UiBase.h"
class CUI_ID_FRAME_SelectAssignMode :public CUIBase
{
	// SGuildMember
public:	
	CUI_ID_FRAME_SelectAssignMode();
private:
	 ControlFrame*	m_pID_FRAME_SelectAssignMode;
	 ControlButton*	m_pID_BUTTON_Freedom;
	 ControlButton*	m_pID_BUTTON_Team;
	 ControlButton*	m_pID_BUTTON_Random;
	 ControlButton*	m_pID_BUTTON_Assign;

	 ControlPicture*	m_pID_PIC_Freedom;
	 ControlPicture*	m_pID_PIC_Team;
	 ControlPicture*	m_pID_PIC_Random;
	 ControlPicture*	m_pID_PIC_Assign;

	 ControlPicture*	m_pID_PIC_Tuan;
	 ControlPicture*	m_pID_PIC_Dui;

	 clock_t		tmChangeAssignModeStart;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_FreedomOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TeamOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RandomOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AssignOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


private:
	void send_Change_AssignMode( unsigned char mode);
};

extern CUI_ID_FRAME_SelectAssignMode s_CUI_ID_FRAME_SelectAssignMode;
