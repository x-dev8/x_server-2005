/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\上线领奖\Ui\OnlineAward3.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_OnlineAward3
#define ID_FRAME_OnlineAward3		"ID_FRAME_OnlineAward3"
#endif  ID_FRAME_OnlineAward3
#ifndef ID_BUTTON_OnlineAward
#define ID_BUTTON_OnlineAward		"ID_BUTTON_OnlineAward"
#endif  ID_BUTTON_OnlineAward
#ifndef ID_BUTTON_OnlineAward1
#define ID_BUTTON_OnlineAward1		"ID_BUTTON_OnlineAward1"
#endif  ID_BUTTON_OnlineAward1
#ifndef ID_TEXT_OnlineAward
#define ID_TEXT_OnlineAward		"ID_TEXT_OnlineAward"
#endif  ID_TEXT_OnlineAward
#ifndef ID_TEXT_OnlineAward_time
#define ID_TEXT_OnlineAward_time		"ID_TEXT_OnlineAward_time"
#endif  ID_TEXT_OnlineAward_time

#include "UiBase.h"
class CUI_ID_FRAME_OnlineAward3 :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_OnlineAward3();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OnlineAwardOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OnlineAward1OnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	void UpdateTime();
	void StartTime();
	void SendMsg(int nIndex);
	int  GetGiftIndex(unsigned long ulTime);   //获得在线时间的礼物
	void Clear();
	bool IsMaxValue(int nIndex);   //是否为最大值
	void ProcessResult();
	void ShowTime(unsigned long ulTime);

	void SetEnableOnlineAward(bool bValue);

    static int            s_nIndex;       //礼物索引
private:
	unsigned long  m_dwBeginTime;  //开始计时
private:
	ControlFrame*	m_pID_FRAME_OnlineAward3;
	ControlButton*	m_pID_BUTTON_OnlineAward;
	ControlButton*	m_pID_BUTTON_OnlineAward1;
	ControlText*	m_pID_TEXT_OnlineAward;
	ControlText*	m_pID_TEXT_OnlineAward_time;
};
extern CUI_ID_FRAME_OnlineAward3 s_CUI_ID_FRAME_OnlineAward3;
