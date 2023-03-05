/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\RTX\国王战\KingBattleEnter.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"

#ifndef ID_FRAME_KingBattleEnter
#define ID_FRAME_KingBattleEnter		"ID_FRAME_KingBattleEnter"
#endif  ID_FRAME_KingBattleEnter
#ifndef ID_TEXT_Name1
#define ID_TEXT_Name1		"ID_TEXT_Name1"
#endif  ID_TEXT_Name1
#ifndef ID_TEXT_Name2
#define ID_TEXT_Name2		"ID_TEXT_Name2"
#endif  ID_TEXT_Name2
#ifndef ID_TEXT_Introduce
#define ID_TEXT_Introduce		"ID_TEXT_Introduce"
#endif  ID_TEXT_Introduce
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Enter
#define ID_BUTTON_Enter		"ID_BUTTON_Enter"
#endif  ID_BUTTON_Enter
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_EnterKindom
#define ID_BUTTON_EnterKindom		"ID_BUTTON_EnterKindom"
#endif  ID_BUTTON_EnterKindom

class CUI_ID_FRAME_KingBattleEnter: public CUIBase
{
	// Member
public:
	CUI_ID_FRAME_KingBattleEnter();

private:	
	 ControlFrame*	m_pID_FRAME_KingBattleEnter;
	 ControlText*	m_pID_TEXT_Name1;
	 ControlText*	m_pID_TEXT_Name2;
	 ControlText*	m_pID_TEXT_Introduce;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_Enter;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_EnterKindom;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_EnterOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_EnterKindomOnButtonClick( ControlObject* pSender );

	void SetKingdomMapInfo(unsigned long mapid,float x,float y);
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	//-------------------------------------------------------------------------
private:
	unsigned int m_nOurGuildID;
	unsigned int m_nOtherGuildID;

	unsigned int m_nKingdomMapID;
	float		 m_fKingdomX;
	float		 m_fKingdomY;
public:
	void SetOurGuildId(unsigned int nValue) { m_nOurGuildID = nValue; }
	void SetOtherGuildId(unsigned int nValue) { m_nOtherGuildID = nValue; }
	void Refresh();
};
extern CUI_ID_FRAME_KingBattleEnter s_CUI_ID_FRAME_KingBattleEnter;
