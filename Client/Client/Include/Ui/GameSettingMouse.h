/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\gamesetting\GameSettingMouse.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GameSettingMouse
#define ID_FRAME_GameSettingMouse		"ID_FRAME_GameSettingMouse"
#endif  ID_FRAME_GameSettingMouse
#ifndef ID_TEXT_MouseAgility
#define ID_TEXT_MouseAgility		"ID_TEXT_MouseAgility"
#endif  ID_TEXT_MouseAgility
#ifndef ID_TEXT_MouseOnCamera
#define ID_TEXT_MouseOnCamera		"ID_TEXT_MouseOnCamera"
#endif  ID_TEXT_MouseOnCamera
#ifndef ID_SCROLLBAREX_MouseAgility
#define ID_SCROLLBAREX_MouseAgility		"ID_SCROLLBAREX_MouseAgility"
#endif  ID_SCROLLBAREX_MouseAgility
#ifndef ID_SCROLLBAREX_MouseOnCamera
#define ID_SCROLLBAREX_MouseOnCamera		"ID_SCROLLBAREX_MouseOnCamera"
#endif  ID_SCROLLBAREX_MouseOnCamera
#ifndef ID_TEXT_AutoMouse
#define ID_TEXT_AutoMouse		"ID_TEXT_AutoMouse"
#endif  ID_TEXT_AutoMouse
#ifndef ID_CHECKBOX_AutoMouse
#define ID_CHECKBOX_AutoMouse		"ID_CHECKBOX_AutoMouse"
#endif  ID_CHECKBOX_AutoMouse
#ifndef ID_TEXT_AutoMouseEx
#define ID_TEXT_AutoMouseEx		"ID_TEXT_AutoMouseEx"
#endif  ID_TEXT_AutoMouseEx

#include "UiBase.h"
class CUI_ID_FRAME_GameSettingMouse :public CUIBase
{
	// Member
public:	
    CUI_ID_FRAME_GameSettingMouse();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_SCROLLBAREX_MouseAgilityOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	void ID_SCROLLBAREX_MouseOnCameraOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	void ID_CHECKBOX_AutoMouseOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

    
    void RefreshUI();
    int  GetCameraRotateSpeed(){return CameraRotateSpeed;}
    int  GetMouseSpeed(){return MouseSpeed;}

    ControlFrame* GetFrame(){return m_pID_FRAME_GameSettingMouse;}
private:

    ControlFrame*	m_pID_FRAME_GameSettingMouse;
    ControlText*	m_pID_TEXT_MouseAgility;
    ControlText*	m_pID_TEXT_MouseOnCamera;
    ControlScrollBarEx*	m_pID_SCROLLBAREX_MouseAgility;
    ControlScrollBarEx*	m_pID_SCROLLBAREX_MouseOnCamera;
    ControlText*	m_pID_TEXT_AutoMouse;
    ControlCheckBox*	m_pID_CHECKBOX_AutoMouse;
    ControlText*	m_pID_TEXT_AutoMouseEx;


	int	CameraRotateSpeed;
	int	MouseSpeed;
};
extern CUI_ID_FRAME_GameSettingMouse s_CUI_ID_FRAME_GameSettingMouse;
