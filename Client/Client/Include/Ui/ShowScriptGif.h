/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\ShowScriptGif.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_ShowScriptGif
#define ID_FRAME_ShowScriptGif		"ID_FRAME_ShowScriptGif"
#endif  ID_FRAME_ShowScriptGif
#ifndef ID_PICTURE_ScriptGif
#define ID_PICTURE_ScriptGif		"ID_PICTURE_ScriptGif"
#endif  ID_PICTURE_ScriptGif

#include "UiBase.h"
class CUI_ID_FRAME_ShowScriptGif :public CUIBase
{
	// Member
private:
	 ControlFrame*	m_pID_FRAME_ShowScriptGif;
	 ControlPicture*	m_pID_PICTURE_ScriptGif;

public:	
	CUI_ID_FRAME_ShowScriptGif();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����
public:


private:
	DWORD	m_dwCloseTime;			// ����ʱ��UI�ر�
};
extern CUI_ID_FRAME_ShowScriptGif s_CUI_ID_FRAME_ShowScriptGif;
