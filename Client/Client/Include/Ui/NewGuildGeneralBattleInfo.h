/********************************************************************
	Created by UIEditor.exe
	FileName: D:\FullBag(13.10.181)\Data\Ui\NewGuildGeneralBattleInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#include "GameBattleDefine.h"
#include "GuildDefine.h"
#ifndef ID_FRAME_NewGuildGeneralBattleInfo
#define ID_FRAME_NewGuildGeneralBattleInfo		"ID_FRAME_NewGuildGeneralBattleInfo"
#endif  ID_FRAME_NewGuildGeneralBattleInfo
#ifndef ID_TEXT_GuildName
#define ID_TEXT_GuildName		"ID_TEXT_GuildName"
#endif  ID_TEXT_GuildName
#ifndef ID_TEXT_Info
#define ID_TEXT_Info		"ID_TEXT_Info"
#endif  ID_TEXT_Info
#ifndef ID_TEXT_GuildMoney
#define ID_TEXT_GuildMoney		"ID_TEXT_GuildMoney"
#endif  ID_TEXT_GuildMoney
#ifndef ID_TEXT_GuildMission
#define ID_TEXT_GuildMission		"ID_TEXT_GuildMission"
#endif  ID_TEXT_GuildMission
#ifndef ID_TEXT_Money
#define ID_TEXT_Money		"ID_TEXT_Money"
#endif  ID_TEXT_Money
#ifndef ID_TEXT_BeginTime
#define ID_TEXT_BeginTime		"ID_TEXT_BeginTime"
#endif  ID_TEXT_BeginTime
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_BUTTON_Canel
#define ID_BUTTON_Canel		"ID_BUTTON_Canel"
#endif  ID_BUTTON_Canel
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE

class CUI_ID_FRAME_NewGuildGeneralBattleInfo:public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_NewGuildGeneralBattleInfo();
	 ControlFrame*	m_pID_FRAME_NewGuildGeneralBattleInfo;
	 ControlText*	m_pID_TEXT_GuildName;
	 ControlText*	m_pID_TEXT_Info;
	 ControlText*	m_pID_TEXT_GuildMoney;
	 ControlText*	m_pID_TEXT_GuildMission;
	 ControlText*	m_pID_TEXT_Money;
	 ControlText*	m_pID_TEXT_BeginTime;
	 ControlButton*	m_pID_BUTTON_OK;
	 ControlButton*	m_pID_BUTTON_Canel;
	 ControlButton*	m_pID_BUTTON_CLOSE;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CanelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void SetDataToUI(GameBattleDefine::GuildCampBattle* pData,const char * pInfo,const char* nsrcGuildName);
private:
	void ClearAllUIInfo();
private:
	GameBattleDefine::GuildCampBattle Info;
	char infoStr[GameBattleDefine::MaxGameGuildGeneralBattleInfoLength];
	char srcGuildName[GuildDefine::MaxNameLength];
	__int64 m_LogShowTime;
	__int64 m_LogShowTimeStep;
};
extern CUI_ID_FRAME_NewGuildGeneralBattleInfo s_CUI_ID_FRAME_NewGuildGeneralBattleInfo;
