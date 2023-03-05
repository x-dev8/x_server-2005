/********************************************************************
	Created by UIEditor.exe
	FileName: E:\武将三国\Data\Ui\TaiPingHuanJing.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include <string>
#include <map>

#ifndef ID_FRAME_TaiPingHuanJing
#define ID_FRAME_TaiPingHuanJing		"ID_FRAME_TaiPingHuanJing"
#endif  ID_FRAME_TaiPingHuanJing
#ifndef ID_BUTTON_Enter
#define ID_BUTTON_Enter		"ID_BUTTON_Enter"
#endif  ID_BUTTON_Enter
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif	ID_BUTTON_CLOSE
#ifndef ID_PICTURE_rank1
#define ID_PICTURE_rank1		"ID_PICTURE_rank1"
#endif  ID_PICTURE_rank1
#ifndef ID_PICTURE_rank2
#define ID_PICTURE_rank2		"ID_PICTURE_rank2"
#endif  ID_PICTURE_rank2
#ifndef ID_PICTURE_rank3
#define ID_PICTURE_rank3		"ID_PICTURE_rank3"
#endif  ID_PICTURE_rank3
#ifndef ID_PICTURE_rank4
#define ID_PICTURE_rank4		"ID_PICTURE_rank4"
#endif  ID_PICTURE_rank4
#ifndef ID_PICTURE_rank5
#define ID_PICTURE_rank5		"ID_PICTURE_rank5"
#endif  ID_PICTURE_rank5
#ifndef ID_PICTURE_rank6
#define ID_PICTURE_rank6		"ID_PICTURE_rank6"
#endif  ID_PICTURE_rank6
#ifndef ID_BUTTON_Leave
#define ID_BUTTON_Leave		"ID_BUTTON_Leave"
#endif	ID_BUTTON_Leave

using namespace std;

class CUI_ID_FRAME_TaiPingHuanJing:public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_TaiPingHuanJing();
	 ControlFrame*	m_pID_FRAME_TaiPingHuanJing;
	 ControlButton*	m_pID_BUTTON_Enter;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlPicture*	m_pID_PICTURE_rank1;
	 ControlPicture*	m_pID_PICTURE_rank2;
	 ControlPicture*	m_pID_PICTURE_rank3;
	 ControlPicture*	m_pID_PICTURE_rank4;
	 ControlPicture*	m_pID_PICTURE_rank5;
	 ControlPicture*	m_pID_PICTURE_rank6;
	 ControlButton*	m_pID_BUTTON_Leave;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_EnterOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LeaveOnButtonClick( ControlObject* pSender );

	//bool LoadUI();				// 载入UI
	//bool DoControlConnect();	// 关连控件
	//bool UnLoadUI();			// 卸载UI
	//bool IsVisable();			// 是否可见
	//void SetVisable( const bool bVisable );			// 设置是否可视

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();

	void Refresh();
	void Clear();
};
extern CUI_ID_FRAME_TaiPingHuanJing s_CUI_ID_FRAME_TaiPingHuanJing;
