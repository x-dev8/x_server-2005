/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Work\Turbo\Program\trunk\Bin\Client\Data\Ui\TargetProgrss.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "GameDefineChar.h"
#include "MsgBase.h"

#ifndef ID_FRAME_TargetProgrss
#define ID_FRAME_TargetProgrss		"ID_FRAME_TargetProgrss"
#endif  ID_FRAME_TargetProgrss
#ifndef ID_CASTINGBAR_Intermit
#define ID_CASTINGBAR_Intermit		"ID_CASTINGBAR_Intermit"
#endif  ID_CASTINGBAR_Intermit
#ifndef ID_PROGRESS
#define ID_PROGRESS		"ID_PROGRESS"
#endif  ID_PROGRESS
#ifndef ID_CASTINGBAR_Full
#define ID_CASTINGBAR_Full		"ID_CASTINGBAR_Full"
#endif  ID_CASTINGBAR_Full
#ifndef ID_CASTINGBAR_BORDER
#define ID_CASTINGBAR_BORDER		"ID_CASTINGBAR_BORDER"
#endif  ID_CASTINGBAR_BORDER
#ifndef ID_TEXT_PROGRESSNAME
#define ID_TEXT_PROGRESSNAME		"ID_TEXT_PROGRESSNAME"
#endif  ID_TEXT_PROGRESSNAME

class CUI_ID_FRAME_TargetProgrss :public CUIBase 
{
	// Member
private:	
	 
	 ControlFrame*	m_pID_FRAME_TargetProgrss;
	 ControlPicture*	m_pID_CASTINGBAR_Intermit;
	 ControlPicture*	m_pID_CASTINGBAR_BORDER;
	 ControlPicture*	m_pID_CASTINGBAR_Full;
	 ControlProgress*	m_pID_PROGRESS;
	 ControlText*	m_pID_TEXT_PROGRESSNAME;

public:	
	CUI_ID_FRAME_TargetProgrss();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void SetProgressText(const char* strText);
	void SetProgressValue(int nValue);
	void Finish();
	void BreakProgress();
	void Reset();
	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();
private:	
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

};
extern CUI_ID_FRAME_TargetProgrss s_CUI_ID_FRAME_TargetProgrss;
