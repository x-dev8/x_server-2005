/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\����\�½��ļ��� (22)\TeamFlag.h
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

	bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	bool _UnLoadUI();			// ж��UI
	bool _IsVisable();			// �Ƿ�ɼ�
	void _SetVisable( const bool bVisable );			// �����Ƿ����

public:
	ControlFrame* GetFrame(){return m_pID_FRAME_TeamFlag;}
private:

};
extern CUI_ID_FRAME_TeamFlag s_CUI_ID_FRAME_TeamFlag;
