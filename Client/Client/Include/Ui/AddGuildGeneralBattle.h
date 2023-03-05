/********************************************************************
	Created by UIEditor.exe
	FileName: D:\FullBag(13.10.181)\Data\Ui\AddGuildGeneralBattle.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#include "GuildDefine.h"
#include "PlayerRole.h"
#ifndef ID_FRAME_AddGuildGeneralBattle
#define ID_FRAME_AddGuildGeneralBattle		"ID_FRAME_AddGuildGeneralBattle"
#endif  ID_FRAME_AddGuildGeneralBattle
#ifndef ID_EDIT_SelectName
#define ID_EDIT_SelectName		"ID_EDIT_SelectName"
#endif  ID_EDIT_SelectName
#ifndef ID_BUTTON_Select
#define ID_BUTTON_Select		"ID_BUTTON_Select"
#endif  ID_BUTTON_Select
#ifndef ID_TEXT_PageInfo
#define ID_TEXT_PageInfo		"ID_TEXT_PageInfo"
#endif  ID_TEXT_PageInfo
#ifndef ID_BUTTON_Back
#define ID_BUTTON_Back		"ID_BUTTON_Back"
#endif  ID_BUTTON_Back
#ifndef ID_BUTTON_Next
#define ID_BUTTON_Next		"ID_BUTTON_Next"
#endif  ID_BUTTON_Next
#ifndef ID_EDIT_Info
#define ID_EDIT_Info		"ID_EDIT_Info"
#endif  ID_EDIT_Info
#ifndef ID_EDIT_GuildMoneyJin
#define ID_EDIT_GuildMoneyJin		"ID_EDIT_GuildMoneyJin"
#endif  ID_EDIT_GuildMoneyJin
#ifndef ID_EDIT_GuildMoneyYin
#define ID_EDIT_GuildMoneyYin		"ID_EDIT_GuildMoneyYin"
#endif  ID_EDIT_GuildMoneyYin
#ifndef ID_EDIT_GuildMoneyTon
#define ID_EDIT_GuildMoneyTon		"ID_EDIT_GuildMoneyTon"
#endif  ID_EDIT_GuildMoneyTon
#ifndef ID_BUTTON_Add
#define ID_BUTTON_Add		"ID_BUTTON_Add"
#endif  ID_BUTTON_Add
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_EDIT_GuildMission
#define ID_EDIT_GuildMission		"ID_EDIT_GuildMission"
#endif  ID_EDIT_GuildMission
#ifndef ID_EDIT_MoneyJin
#define ID_EDIT_MoneyJin		"ID_EDIT_MoneyJin"
#endif  ID_EDIT_MoneyJin
#ifndef ID_EDIT_MoneyYin
#define ID_EDIT_MoneyYin		"ID_EDIT_MoneyYin"
#endif  ID_EDIT_MoneyYin
#ifndef ID_EDIT_MoneyTon
#define ID_EDIT_MoneyTon		"ID_EDIT_MoneyTon"
#endif  ID_EDIT_MoneyTon
#ifndef ID_COMBOBOX_BeginTimeYear
#define ID_COMBOBOX_BeginTimeYear		"ID_COMBOBOX_BeginTimeYear"
#endif  ID_COMBOBOX_BeginTimeYear
#ifndef ID_COMBOBOX_BeginTimeMonth
#define ID_COMBOBOX_BeginTimeMonth		"ID_COMBOBOX_BeginTimeMonth"
#endif  ID_COMBOBOX_BeginTimeMonth
#ifndef ID_COMBOBOX_BeginTimeDay
#define ID_COMBOBOX_BeginTimeDay		"ID_COMBOBOX_BeginTimeDay"
#endif  ID_COMBOBOX_BeginTimeDay
#ifndef ID_COMBOBOX_BeginTimeHour
#define ID_COMBOBOX_BeginTimeHour		"ID_COMBOBOX_BeginTimeHour"
#endif  ID_COMBOBOX_BeginTimeHour
#ifndef ID_COMBOBOX_BeginTimeMin
#define ID_COMBOBOX_BeginTimeMin		"ID_COMBOBOX_BeginTimeMin"
#endif  ID_COMBOBOX_BeginTimeMin
#ifndef ID_COMBOBOX_BeginTimeSec
#define ID_COMBOBOX_BeginTimeSec		"ID_COMBOBOX_BeginTimeSec"
#endif  ID_COMBOBOX_BeginTimeSec
#ifndef ID_LIST_GuildName
#define ID_LIST_GuildName		"ID_LIST_GuildName"
#endif  ID_LIST_GuildName
#ifndef ID_LIST_GuildPlayerSum
#define ID_LIST_GuildPlayerSum		"ID_LIST_GuildPlayerSum"
#endif  ID_LIST_GuildPlayerSum
#ifndef ID_LIST_GuildLevel
#define ID_LIST_GuildLevel		"ID_LIST_GuildLevel"
#endif  ID_LIST_GuildLevel
#ifndef ID_LIST_GuildMasterName
#define ID_LIST_GuildMasterName		"ID_LIST_GuildMasterName"
#endif  ID_LIST_GuildMasterName

#ifndef ID_LIST_All
#define ID_LIST_All		"ID_LIST_All"
#endif  ID_LIST_All

#ifndef ID_TEXT_EndTimeStep
#define ID_TEXT_EndTimeStep		"ID_TEXT_EndTimeStep"
#endif  ID_TEXT_EndTimeStep


class CUI_ID_FRAME_AddGuildGeneralBattle :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_AddGuildGeneralBattle();
	 ControlFrame*	m_pID_FRAME_AddGuildGeneralBattle;
	 ControlEdit*	m_pID_EDIT_SelectName;
	 ControlButton*	m_pID_BUTTON_Select;
	 ControlText*	m_pID_TEXT_PageInfo;
	 ControlButton*	m_pID_BUTTON_Back;
	 ControlButton*	m_pID_BUTTON_Next;
	 ControlEdit*	m_pID_EDIT_Info;
	 ControlEdit*	m_pID_EDIT_GuildMoneyJin;
	 ControlEdit*	m_pID_EDIT_GuildMoneyYin;
	 ControlEdit*	m_pID_EDIT_GuildMoneyTon;
	 ControlButton*	m_pID_BUTTON_Add;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlEdit*	m_pID_EDIT_GuildMission;
	 ControlEdit*	m_pID_EDIT_MoneyJin;
	 ControlEdit*	m_pID_EDIT_MoneyYin;
	 ControlEdit*	m_pID_EDIT_MoneyTon;
	 ControlComboBox*	m_pID_COMBOBOX_BeginTimeYear;
	 ControlComboBox*	m_pID_COMBOBOX_BeginTimeMonth;
	 ControlComboBox*	m_pID_COMBOBOX_BeginTimeDay;
	 ControlComboBox*	m_pID_COMBOBOX_BeginTimeHour;
	 ControlComboBox*	m_pID_COMBOBOX_BeginTimeMin;
	 ControlComboBox*	m_pID_COMBOBOX_BeginTimeSec;

	 ControlList*	m_pID_LIST_GuildName;
	 ControlList*	m_pID_LIST_GuildPlayerSum;
	 ControlList*	m_pID_LIST_GuildLevel;
	 ControlList*	m_pID_LIST_GuildMasterName;
	 ControlList*	m_pID_LIST_All;

	 ControlText*   m_pID_TEXT_EndTimeStep;
	 

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_EDIT_SelectNameOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_SelectOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_BackOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_NextOnButtonClick( ControlObject* pSender );
	void ID_EDIT_InfoOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_GuildMoneyJinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_GuildMoneyYinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_GuildMoneyTonOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_AddOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_EDIT_GuildMissionOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_MoneyJinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_MoneyYinOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_MoneyTonOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_BeginTimeYearOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_BeginTimeMonthOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_BeginTimeDayOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_BeginTimeHourOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_BeginTimeMinOnComboBoxChange( ControlObject* pSender, const char* szData );
	void ID_COMBOBOX_BeginTimeSecOnComboBoxChange( ControlObject* pSender, const char* szData );

	void ID_LIST_GuildNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildPlayerSumOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildLevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildMasterNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	void ID_LIST_AllOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }

	void OnUpdateUiInfo();
	void OnShow();

	void OnInit();
	void ShowGuildInfoByPage(int Page = 1);
	void AddToList(const char* m_GuildName,const char *level,const char* num,const char*Mastername);
	void UpdateAllGuild();

	void SetBeginTimeComBox();

	bool EditInputIsVisable();
private:
	void UpdateGameGeneralBattleStepTime();
	bool IfCanAddGameGeneralBattleByTime();
private:
	std::vector<CGuildInfo*> m_vctGuild;//当前的结果的公会
	int						 m_NowPage;
};
extern CUI_ID_FRAME_AddGuildGeneralBattle s_CUI_ID_FRAME_AddGuildGeneralBattle;
