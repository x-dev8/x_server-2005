/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#ifndef ID_FRAME_GuildInfo
#define ID_FRAME_GuildInfo		"ID_FRAME_GuildInfo"
#endif  ID_FRAME_GuildInfo
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_RenShu
#define ID_TEXT_RenShu		"ID_TEXT_RenShu"
#endif  ID_TEXT_RenShu
#ifndef ID_TEXT_GuildExp
#define ID_TEXT_GuildExp		"ID_TEXT_GuildExp"
#endif  ID_TEXT_GuildExp
#ifndef ID_TEXT_GuildMoney
#define ID_TEXT_GuildMoney		"ID_TEXT_GuildMoney"
#endif  ID_TEXT_GuildMoney
#ifndef ID_TEXT_GuildLevel
#define ID_TEXT_GuildLevel		"ID_TEXT_GuildLevel"
#endif  ID_TEXT_GuildLevel
#ifndef ID_TEXT_Warxishu
#define ID_TEXT_Warxishu		"ID_TEXT_Warxishu"
#endif  ID_TEXT_Warxishu
#ifndef ID_TEXT_GuildMaster
#define ID_TEXT_GuildMaster		"ID_TEXT_GuildMaster"
#endif  ID_TEXT_GuildMaster
#ifndef ID_TEXT_Announcement
#define ID_TEXT_Announcement		"ID_TEXT_Announcement"
#endif  ID_TEXT_Announcement
#ifndef ID_BUTTON_Announcement
#define ID_BUTTON_Announcement		"ID_BUTTON_Announcement"
#endif  ID_BUTTON_Announcement

#ifndef ID_TEXT_Mision
#define ID_TEXT_Mision		"ID_TEXT_Mision"
#endif  ID_TEXT_Mision

#ifndef ID_BUTTON_GuildCampBattle
#define ID_BUTTON_GuildCampBattle		"ID_BUTTON_GuildCampBattle"
#endif  ID_BUTTON_GuildCampBattle

#ifndef ID_TEXT_MaxPlayerSum
#define ID_TEXT_MaxPlayerSum		"ID_TEXT_MaxPlayerSum"
#endif  ID_TEXT_MaxPlayerSum


class CUI_ID_FRAME_GuildInfo  :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GuildInfo();
	 ControlFrame*	m_pID_FRAME_GuildInfo;
	 ControlText*	m_pID_TEXT_Name;
	 ControlText*	m_pID_TEXT_RenShu;
	 ControlText*	m_pID_TEXT_GuildExp;
	 ControlText*	m_pID_TEXT_GuildMoney;
	 ControlText*	m_pID_TEXT_GuildLevel;
	 ControlText*	m_pID_TEXT_Warxishu;
	 ControlText*	m_pID_TEXT_GuildMaster;
	 ControlText*	m_pID_TEXT_Announcement;
	 ControlButton*	m_pID_BUTTON_Announcement;
	 ControlButton*	m_pID_BUTTON_GuildCampBattle;
	 ControlText*	m_pID_TEXT_Mision;
	 ControlText*	m_pID_TEXT_MaxPlayerSum;
	 
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_AnnouncementOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GuildCampBattleOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }

	void OnUpdateUiInfo();//UI上的值需要进行更新 只有在客户端的公会相关数据发送变化的时候才更新
private:
	void OnShow();
};
extern CUI_ID_FRAME_GuildInfo s_CUI_ID_FRAME_GuildInfo;
