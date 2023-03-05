/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CampBattleWorld.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "CampBattleBaseInfo.h"
#ifndef ID_FRAME_CampBattleWorld
#define ID_FRAME_CampBattleWorld		"ID_FRAME_CampBattleWorld"
#endif  ID_FRAME_CampBattleWorld
#ifndef ID_TEXT_WorldCountry
#define ID_TEXT_WorldCountry		"ID_TEXT_WorldCountry"
#endif  ID_TEXT_WorldCountry
#ifndef ID_TEXT_EndTimeStep
#define ID_TEXT_EndTimeStep		"ID_TEXT_EndTimeStep"
#endif  ID_TEXT_EndTimeStep
#ifndef ID_TEXT_BeginTimeStep
#define ID_TEXT_BeginTimeStep		"ID_TEXT_BeginTimeStep"
#endif  ID_TEXT_BeginTimeStep

class CUI_ID_FRAME_CampBattleWorld :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_CampBattleWorld();
	 ControlFrame*	m_pID_FRAME_CampBattleWorld;
	 ControlText*	m_pID_TEXT_WorldCountry;
	 ControlText*	m_pID_TEXT_EndTimeStep;
	 ControlText*	m_pID_TEXT_BeginTimeStep;

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
extern CUI_ID_FRAME_CampBattleWorld s_CUI_ID_FRAME_CampBattleWorld;
