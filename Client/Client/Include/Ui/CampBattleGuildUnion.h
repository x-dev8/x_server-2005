/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CampBattleGuildUnion.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "CampBattleBaseInfo.h"
#ifndef ID_FRAME_CampBattleGuildUnion
#define ID_FRAME_CampBattleGuildUnion		"ID_FRAME_CampBattleGuildUnion"
#endif  ID_FRAME_CampBattleGuildUnion
#ifndef ID_TEXT_UnionSum
#define ID_TEXT_UnionSum		"ID_TEXT_UnionSum"
#endif  ID_TEXT_UnionSum
#ifndef ID_TEXT_BeginTimeStep
#define ID_TEXT_BeginTimeStep		"ID_TEXT_BeginTimeStep"
#endif  ID_TEXT_BeginTimeStep
#ifndef ID_TEXT_EndTimeStep
#define ID_TEXT_EndTimeStep		"ID_TEXT_EndTimeStep"
#endif  ID_TEXT_EndTimeStep
#ifndef ID_LIST_GuildName
#define ID_LIST_GuildName		"ID_LIST_GuildName"
#endif  ID_LIST_GuildName
#ifndef ID_LIST_GuildStrong
#define ID_LIST_GuildStrong		"ID_LIST_GuildStrong"
#endif  ID_LIST_GuildStrong

class CUI_ID_FRAME_CampBattleGuildUnion:public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_CampBattleGuildUnion();
	 ControlFrame*	m_pID_FRAME_CampBattleGuildUnion;
	 ControlText*	m_pID_TEXT_UnionSum;
	 ControlText*	m_pID_TEXT_BeginTimeStep;
	 ControlText*	m_pID_TEXT_EndTimeStep;
	 ControlList*	m_pID_LIST_GuildName;
	 ControlList*	m_pID_LIST_GuildStrong;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_GuildNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildStrongOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void SetGuildUnionSum(int BattleSum);

	void OnInit();
	CampBattleInfoManger& GetCampBattleInfo(){return m_CampInfo;}
private:
	void LoadFileConfig(const char * FilePath);
	void LoadCampClientInfo(const char * FilePath);
private:
	//国王战的基本数据
	CampBattleTimeInfo		m_TimeInfo;//时间记录
	int						m_WorldBattleSum;
	CampBattleInfoManger	m_CampInfo;
};
extern CUI_ID_FRAME_CampBattleGuildUnion s_CUI_ID_FRAME_CampBattleGuildUnion;
