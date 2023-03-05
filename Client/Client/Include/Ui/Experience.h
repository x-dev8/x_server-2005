/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\experience\Experience.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Experience
#define ID_FRAME_Experience		"ID_FRAME_Experience"
#endif  ID_FRAME_Experience
#ifndef ID_PICTURE_WallPaper
#define ID_PICTURE_WallPaper		"ID_PICTURE_WallPaper"
#endif  ID_PICTURE_WallPaper
#ifndef ID_TEXT_Explain
#define ID_TEXT_Explain		"ID_TEXT_Explain"
#endif  ID_TEXT_Explain
#ifndef ID_LIST_ExperienceList
#define ID_LIST_ExperienceList		"ID_LIST_ExperienceList"
#endif  ID_LIST_ExperienceList

#include "UiBase.h"
class CUI_ID_FRAME_Experience :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_Experience();
private:
	ControlFrame*	m_pID_FRAME_Experience;
	ControlPicture*	m_pID_PICTURE_WallPaper;
	ControlText*	m_pID_TEXT_Explain;
	ControlList*	m_pID_LIST_ExperienceList;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_ExperienceListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void Refresh();
};
extern CUI_ID_FRAME_Experience s_CUI_ID_FRAME_Experience;
