/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (22)\TeamFlag.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_TeamFlag
#define ID_FRAME_TeamFlag		"ID_FRAME_TeamFlag"
#endif  ID_FRAME_TeamFlag
#ifndef ID_PICTURE_flag
#define ID_PICTURE_flag		"ID_PICTURE_flag"
#endif  ID_PICTURE_flag

#include "UIBase.h"

class CUI_ID_FRAME_TeamFlag : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_TeamFlag();
	 ControlFrame*	m_pID_FRAME_TeamFlag;
	 ControlPicture*	m_pID_PICTURE_flag;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	bool _UnLoadUI();			// 卸载UI
	bool _IsVisable();			// 是否可见
	void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	ControlFrame* GetFrame(){return m_pID_FRAME_TeamFlag;}
private:

};
extern CUI_ID_FRAME_TeamFlag s_CUI_ID_FRAME_TeamFlag;
