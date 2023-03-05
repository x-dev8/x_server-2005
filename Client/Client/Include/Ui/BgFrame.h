/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\����\BgFrame.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_BgFrame
#define ID_FRAME_BgFrame		"ID_FRAME_BgFrame"
#endif  ID_FRAME_BgFrame
#ifndef ID_PICTURE_NpcHead
#define ID_PICTURE_NpcHead		"ID_PICTURE_NpcHead"
#endif  ID_PICTURE_NpcHead
#ifndef ID_PICTURE_BgHead
#define ID_PICTURE_BgHead		"ID_PICTURE_BgHead"
#endif  ID_PICTURE_BgHead
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_BUTTON_EXIT
#define ID_BUTTON_EXIT		"ID_BUTTON_EXIT"
#endif  ID_BUTTON_EXIT

class CUI_ID_FRAME_BgFrame : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_BgFrame();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_EXITOnButtonClick( ControlObject* pSender );
	ControlFrame*	m_pID_FRAME_BgFrame;
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����

    virtual bool IsHoldInMemory() const { return true; }
    virtual void InitializeAtEnterWorld();
private:

	ControlPicture*	m_pID_PICTURE_NpcHead;
	ControlPicture*	m_pID_PICTURE_BgHead;
	ControlText*	m_pID_TEXT_Name;
	ControlButton*	m_pID_BUTTON_EXIT;
public:
	void SetNpcName(const char *pszName);
	void SetPicPath(const char *pszPic,bool bVisable);
};
extern CUI_ID_FRAME_BgFrame s_CUI_ID_FRAME_BgFrame;
