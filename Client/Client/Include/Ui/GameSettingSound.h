/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\GAME\GameSettingSound.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_GameSettingSound
#define ID_FRAME_GameSettingSound		"ID_FRAME_GameSettingSound"
#endif  ID_FRAME_GameSettingSound
#ifndef ID_TEXT_yinyue
#define ID_TEXT_yinyue		"ID_TEXT_yinyue"
#endif  ID_TEXT_yinyue
#ifndef ID_TEXT_huanjing
#define ID_TEXT_huanjing		"ID_TEXT_huanjing"
#endif  ID_TEXT_huanjing
#ifndef ID_SCROLLBAREX_yinyue
#define ID_SCROLLBAREX_yinyue		"ID_SCROLLBAREX_yinyue"
#endif  ID_SCROLLBAREX_yinyue
#ifndef ID_SCROLLBAREX_huanjing
#define ID_SCROLLBAREX_huanjing		"ID_SCROLLBAREX_huanjing"
#endif  ID_SCROLLBAREX_huanjing

#include "UiBase.h"
class CUI_ID_FRAME_GameSettingSound :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GameSettingSound();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_SCROLLBAREX_yinyueOnScrollBarExUpdatePos( ControlObject* pSender, int n );
	void ID_SCROLLBAREX_huanjingOnScrollBarExUpdatePos( ControlObject* pSender, int n );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void RefreshUI();

    ControlFrame* GetFrame(){return m_pID_FRAME_GameSettingSound;}
private:
    ControlFrame*	m_pID_FRAME_GameSettingSound;
    ControlText*	m_pID_TEXT_yinyue;
    ControlText*	m_pID_TEXT_huanjing;
    ControlScrollBarEx*	m_pID_SCROLLBAREX_yinyue;
    ControlScrollBarEx*	m_pID_SCROLLBAREX_huanjing;
};
extern CUI_ID_FRAME_GameSettingSound s_CUI_ID_FRAME_GameSettingSound;
