/********************************************************************
	Created by UIEditor.exe
	FileName: D:\FullBag(13.10.181)\Data\Ui\GuildGeneralBattleList.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#include "GameBattleDefine.h"
#ifndef ID_FRAME_GuildGeneralBattleList
#define ID_FRAME_GuildGeneralBattleList		"ID_FRAME_GuildGeneralBattleList"
#endif  ID_FRAME_GuildGeneralBattleList
#ifndef ID_LIST_GuildName
#define ID_LIST_GuildName		"ID_LIST_GuildName"
#endif  ID_LIST_GuildName
#ifndef ID_LIST_GuildMasterName
#define ID_LIST_GuildMasterName		"ID_LIST_GuildMasterName"
#endif  ID_LIST_GuildMasterName
#ifndef ID_LIST_GuildLevel
#define ID_LIST_GuildLevel		"ID_LIST_GuildLevel"
#endif  ID_LIST_GuildLevel
#ifndef ID_LIST_GuildRoleSum
#define ID_LIST_GuildRoleSum		"ID_LIST_GuildRoleSum"
#endif  ID_LIST_GuildRoleSum
#ifndef ID_LIST_GuildMoney
#define ID_LIST_GuildMoney		"ID_LIST_GuildMoney"
#endif  ID_LIST_GuildMoney
#ifndef ID_LIST_GuildMIssion
#define ID_LIST_GuildMIssion		"ID_LIST_GuildMIssion"
#endif  ID_LIST_GuildMIssion
#ifndef ID_LIST_Money
#define ID_LIST_Money		"ID_LIST_Money"
#endif  ID_LIST_Money
#ifndef ID_LIST_BeginTime
#define ID_LIST_BeginTime		"ID_LIST_BeginTime"
#endif  ID_LIST_BeginTime
#ifndef ID_BUTTON_Up
#define ID_BUTTON_Up		"ID_BUTTON_Up"
#endif  ID_BUTTON_Up
#ifndef ID_BUTTON_Down
#define ID_BUTTON_Down		"ID_BUTTON_Down"
#endif  ID_BUTTON_Down
#ifndef ID_TEXT_PageInfo
#define ID_TEXT_PageInfo		"ID_TEXT_PageInfo"
#endif  ID_TEXT_PageInfo


#ifndef ID_LIST_All
#define ID_LIST_All		"ID_LIST_All"
#endif  ID_LIST_All
class CUI_ID_FRAME_GuildGeneralBattleList:public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GuildGeneralBattleList();
	 ControlFrame*	m_pID_FRAME_GuildGeneralBattleList;
	 ControlList*	m_pID_LIST_GuildName;
	 ControlList*	m_pID_LIST_GuildMasterName;
	 ControlList*	m_pID_LIST_GuildLevel;
	 ControlList*	m_pID_LIST_GuildRoleSum;
	 ControlList*	m_pID_LIST_GuildMoney;
	 ControlList*	m_pID_LIST_GuildMIssion;
	 ControlList*	m_pID_LIST_Money;
	 ControlList*	m_pID_LIST_BeginTime;
	 ControlButton*	m_pID_BUTTON_Up;
	 ControlButton*	m_pID_BUTTON_Down;
	 ControlText*	m_pID_TEXT_PageInfo;

	 ControlList*	m_pID_LIST_All;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_GuildNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildMasterNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildLevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildRoleSumOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildMoneyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildMIssionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_MoneyOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_BeginTimeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_UpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DownOnButtonClick( ControlObject* pSender );

	void ID_LIST_AllOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );


	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视


	void OnUpdateUiInfo();
	void OnShow();

	void OnInit();
	void ShowGuildInfoByPage(int Page = 1);
	void AddToList(const char* m_GuildName,const char *level,const char* num,const char*Mastername,const char * GuildMoney,const char* Money,const char* GuildMission,const char* BeginTime);

	void LoadGuildGeneral(GameBattleDefine::GuildCampBattle& pData);
	void AddNewGuildGenetal(GameBattleDefine::GuildCampBattle& pData);
	void DelGuildGeneral(unsigned int ID);
	void ClearData();
private:
	map<unsigned int,GameBattleDefine::GuildCampBattle>  pList;
	int						 m_NowPage;
	bool					 m_IsLoad;
};
extern CUI_ID_FRAME_GuildGeneralBattleList s_CUI_ID_FRAME_GuildGeneralBattleList;
