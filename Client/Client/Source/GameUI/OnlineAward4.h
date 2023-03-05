/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\上线领奖\Ui\OnlineAward4.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_OnlineAward4
#define ID_FRAME_OnlineAward4		"ID_FRAME_OnlineAward4"
#endif  ID_FRAME_OnlineAward4
#ifndef ID_PICTURE_7206
#define ID_PICTURE_7206		"ID_PICTURE_7206"
#endif  ID_PICTURE_7206
#ifndef ID_BUTTON_OnlineAward_add
#define ID_BUTTON_OnlineAward_add		"ID_BUTTON_OnlineAward_add"
#endif  ID_BUTTON_OnlineAward_add
#ifndef ID_TEXT_OnlineAward_addtime
#define ID_TEXT_OnlineAward_addtime		"ID_TEXT_OnlineAward_addtime"
#endif  ID_TEXT_OnlineAward_addtime

#include "UiBase.h"
class CUI_ID_FRAME_OnlineAward4 :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_OnlineAward4();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OnlineAward_addOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	void SetLeftTime(unsigned long nTime);
	void UpdateTime();
	void ShowTime(unsigned long nTime);
private:
	unsigned long  m_LeftTime;
private:
	ControlFrame*	m_pID_FRAME_OnlineAward4;
	ControlPicture*	m_pID_PICTURE_7206;
	ControlButton*	m_pID_BUTTON_OnlineAward_add;
	ControlText*	m_pID_TEXT_OnlineAward_addtime;
};
extern CUI_ID_FRAME_OnlineAward4 s_CUI_ID_FRAME_OnlineAward4;
