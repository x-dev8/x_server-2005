/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildUnionBattleEnter.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#ifndef ID_FRAME_GuildUnionBattleEnter
#define ID_FRAME_GuildUnionBattleEnter		"ID_FRAME_GuildUnionBattleEnter"
#endif  ID_FRAME_GuildUnionBattleEnter
#ifndef ID_TEXT_Name1
#define ID_TEXT_Name1		"ID_TEXT_Name1"
#endif  ID_TEXT_Name1
#ifndef ID_TEXT_Name2
#define ID_TEXT_Name2		"ID_TEXT_Name2"
#endif  ID_TEXT_Name2
#ifndef ID_TEXT_Introduce
#define ID_TEXT_Introduce		"ID_TEXT_Introduce"
#endif  ID_TEXT_Introduce
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_BUTTON_EnterGuildUnion
#define ID_BUTTON_EnterGuildUnion		"ID_BUTTON_EnterGuildUnion"
#endif  ID_BUTTON_EnterGuildUnion
#ifndef ID_BUTTON_Enter
#define ID_BUTTON_Enter		"ID_BUTTON_Enter"
#endif  ID_BUTTON_Enter
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE

class CUI_ID_FRAME_GuildUnionBattleEnter: public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GuildUnionBattleEnter();
	 ControlFrame*	m_pID_FRAME_GuildUnionBattleEnter;
	 ControlText*	m_pID_TEXT_Name1;
	 ControlText*	m_pID_TEXT_Name2;
	 ControlText*	m_pID_TEXT_Introduce;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlButton*	m_pID_BUTTON_EnterGuildUnion;
	 ControlButton*	m_pID_BUTTON_Enter;
	 ControlButton*	m_pID_BUTTON_CLOSE;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_EnterGuildUnionOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_EnterOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	void SetKingdomMapInfo(unsigned long mapid,float x,float y);
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视.
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
extern CUI_ID_FRAME_GuildUnionBattleEnter s_CUI_ID_FRAME_GuildUnionBattleEnter;
