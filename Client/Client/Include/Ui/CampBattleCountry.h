/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CampBattleCountry.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "CampBattleBaseInfo.h"
#ifndef ID_FRAME_CampBattleCountry
#define ID_FRAME_CampBattleCountry		"ID_FRAME_CampBattleCountry"
#endif  ID_FRAME_CampBattleCountry
#ifndef ID_TEXT_GuildAName
#define ID_TEXT_GuildAName		"ID_TEXT_GuildAName"
#endif  ID_TEXT_GuildAName
#ifndef ID_TEXT_GuildBName
#define ID_TEXT_GuildBName		"ID_TEXT_GuildBName"
#endif  ID_TEXT_GuildBName
#ifndef ID_TEXT_GuildBStrong
#define ID_TEXT_GuildBStrong		"ID_TEXT_GuildBStrong"
#endif  ID_TEXT_GuildBStrong
#ifndef ID_TEXT_GuildAStrong
#define ID_TEXT_GuildAStrong		"ID_TEXT_GuildAStrong"
#endif  ID_TEXT_GuildAStrong
#ifndef ID_TEXT_BeginTimeStep
#define ID_TEXT_BeginTimeStep		"ID_TEXT_BeginTimeStep"
#endif  ID_TEXT_BeginTimeStep
#ifndef ID_TEXT_EndTimeStep
#define ID_TEXT_EndTimeStep		"ID_TEXT_EndTimeStep"
#endif  ID_TEXT_EndTimeStep

class CUI_ID_FRAME_CampBattleCountry :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_CampBattleCountry();
	 ControlFrame*	m_pID_FRAME_CampBattleCountry;
	 ControlText*	m_pID_TEXT_GuildAName;
	 ControlText*	m_pID_TEXT_GuildBName;
	 ControlText*	m_pID_TEXT_GuildBStrong;
	 ControlText*	m_pID_TEXT_GuildAStrong;
	 ControlText*	m_pID_TEXT_BeginTimeStep;
	 ControlText*	m_pID_TEXT_EndTimeStep;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void OnInit();
	CampBattleInfoManger& GetCampBattleInfo(){return m_CampInfo;}
private:
	void LoadFileConfig(const char * FilePath);
	void LoadCampClientInfo(const char * FilePath);
private:
	//国王战的基本数据
	CampBattleTimeInfo		m_TimeInfo;//时间记录
	CampBattleInfoManger	m_CampInfo;
};
extern CUI_ID_FRAME_CampBattleCountry s_CUI_ID_FRAME_CampBattleCountry;
