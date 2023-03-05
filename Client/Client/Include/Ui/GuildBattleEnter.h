/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\guildcamp\GuildBattleEnter.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"

#ifndef ID_FRAME_GuildBattleEnter
#define ID_FRAME_GuildBattleEnter		"ID_FRAME_GuildBattleEnter"
#endif  ID_FRAME_GuildBattleEnter
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_TEXT_Name1
#define ID_TEXT_Name1		"ID_TEXT_Name1"
#endif  ID_TEXT_Name1
#ifndef ID_TEXT_Name2
#define ID_TEXT_Name2		"ID_TEXT_Name2"
#endif  ID_TEXT_Name2
#ifndef ID_TEXT_Text
#define ID_TEXT_Text		"ID_TEXT_Text"
#endif  ID_TEXT_Text
#ifndef ID_BUTTON_Enter
#define ID_BUTTON_Enter		"ID_BUTTON_Enter"
#endif  ID_BUTTON_Enter
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel

#ifndef ID_BUTTON_FlyToMap
#define ID_BUTTON_FlyToMap		"ID_BUTTON_FlyToMap"
#endif  ID_BUTTON_FlyToMap



class CUI_ID_FRAME_GuildBattleEnter: public CUIBase
{
	// Member
public:
	CUI_ID_FRAME_GuildBattleEnter();

private:	 
	 ControlFrame*	m_pID_FRAME_GuildBattleEnter;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlText*	m_pID_TEXT_Name1;
	 ControlText*	m_pID_TEXT_Name2;
	 ControlText*	m_pID_TEXT_Text;
	 ControlButton*	m_pID_BUTTON_Enter;
	 ControlButton*	m_pID_BUTTON_Cancel;
	ControlButton*	m_pID_BUTTON_FlyToMap;

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_EnterOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FlyToMapOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );

	void SetKingdomMapInfo(unsigned long mapid,float x,float y);

	void SetIsGameBattle(){IsGameBattle = true;}
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

	bool IsGameBattle;
public:
	void SetOurGuildId(unsigned int nValue) { m_nOurGuildID = nValue; }
	void SetOtherGuildId(unsigned int nValue) { m_nOtherGuildID = nValue; }
	void Refresh();
};
extern CUI_ID_FRAME_GuildBattleEnter s_CUI_ID_FRAME_GuildBattleEnter;