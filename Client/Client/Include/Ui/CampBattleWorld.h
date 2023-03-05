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

	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����

	void OnInit();
	CampBattleInfoManger& GetCampBattleInfo(){return m_CampInfo;}
private:
	void LoadFileConfig(const char * FilePath);
	void LoadCampClientInfo(const char * FilePath);
private:
	//����ս�Ļ�������
	CampBattleTimeInfo		m_TimeInfo;//ʱ���¼
	CampBattleInfoManger	m_CampInfo;
};
extern CUI_ID_FRAME_CampBattleWorld s_CUI_ID_FRAME_CampBattleWorld;
