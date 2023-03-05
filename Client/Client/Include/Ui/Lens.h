/********************************************************************
	Created by UIEditor.exe
	FileName: E:\ShenWang\Turbo\Program\trunk\Bin\Client\Data\Ui\Lens.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_Lens
#define ID_FRAME_Lens		"ID_FRAME_Lens"
#endif  ID_FRAME_Lens
#ifndef ID_PROGRESS_Up1
#define ID_PROGRESS_Up1		"ID_PROGRESS_Up1"
#endif  ID_PROGRESS_Up1
#ifndef ID_PROGRESS_Down1
#define ID_PROGRESS_Down1		"ID_PROGRESS_Down1"
#endif  ID_PROGRESS_Down1
#ifndef ID_PROGRESS_Up2
#define ID_PROGRESS_Up2		"ID_PROGRESS_Up2"
#endif  ID_PROGRESS_Up2
#ifndef ID_PROGRESS_Down2
#define ID_PROGRESS_Down2		"ID_PROGRESS_Down2"
#endif  ID_PROGRESS_Down2
#ifndef ID_PICTURE_Up
#define ID_PICTURE_Up		"ID_PICTURE_Up"
#endif  ID_PICTURE_Up
#ifndef ID_PICTURE_Down
#define ID_PICTURE_Down		"ID_PICTURE_Down"
#endif  ID_PICTURE_Down

class CUI_ID_FRAME_Lens : public CUIBase
{
	// Member
public:
	CUI_ID_FRAME_Lens();
private:	
	 ControlFrame*	m_pID_FRAME_Lens;
	 ControlProgress*	m_pID_PROGRESS_Up1;
	 ControlProgress*	m_pID_PROGRESS_Down1;
	 ControlProgress*	m_pID_PROGRESS_Up2;
	 ControlProgress*	m_pID_PROGRESS_Down2;
	 ControlPicture*	m_pID_PICTURE_Up;
	 ControlPicture*	m_pID_PICTURE_Down;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	void BeginAnim();
	void EndAnim();
	void ModifyWAndH();
public:
	virtual void ResetDevice();
	bool IsTimeOver();
	void BeginTime();
	void ProcessUIShowOrHide();
	void ShowMoviceUpAndDown();
	void SetScreenPlay(DWORD dwTime);
	void ProcessScreenPlay();
private:
	DWORD  m_dwBeginTime;
	bool   m_bTiming;
	bool   m_bAning; //是否动画中
private:
	DWORD m_dwScreenTime;
	DWORD m_dwScreenTimeBegin;
};
extern CUI_ID_FRAME_Lens s_CUI_ID_FRAME_Lens;
