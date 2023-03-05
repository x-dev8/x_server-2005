/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildMember.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GuildDefine.h"
#include "UiBase.h"
#ifndef ID_FRAME_GuildMember
#define ID_FRAME_GuildMember		"ID_FRAME_GuildMember"
#endif  ID_FRAME_GuildMember
#ifndef ID_BUTTON_Appoint
#define ID_BUTTON_Appoint		"ID_BUTTON_Appoint"
#endif  ID_BUTTON_Appoint
#ifndef ID_BUTTON_Quit
#define ID_BUTTON_Quit		"ID_BUTTON_Quit"
#endif  ID_BUTTON_Quit
#ifndef ID_BUTTON_Del
#define ID_BUTTON_Del		"ID_BUTTON_Del"
#endif  ID_BUTTON_Del
#ifndef ID_BUTTON_ZhuanRang
#define ID_BUTTON_ZhuanRang		"ID_BUTTON_ZhuanRang"
#endif  ID_BUTTON_ZhuanRang
#ifndef ID_BUTTON_ADD
#define ID_BUTTON_ADD		"ID_BUTTON_ADD"
#endif  ID_BUTTON_ADD
#ifndef ID_BUTTON_LeavePosition
#define ID_BUTTON_LeavePosition		"ID_BUTTON_LeavePosition"
#endif  ID_BUTTON_LeavePosition
#ifndef ID_CHECKBOX_ShowLeave
#define ID_CHECKBOX_ShowLeave		"ID_CHECKBOX_ShowLeave"
#endif  ID_CHECKBOX_ShowLeave
#ifndef ID_BUTTON_TeamName
#define ID_BUTTON_TeamName		"ID_BUTTON_TeamName"
#endif  ID_BUTTON_TeamName
#ifndef ID_BUTTON_Work
#define ID_BUTTON_Work		"ID_BUTTON_Work"
#endif  ID_BUTTON_Work
#ifndef ID_BUTTON_Lvl
#define ID_BUTTON_Lvl		"ID_BUTTON_Lvl"
#endif  ID_BUTTON_Lvl
#ifndef ID_BUTTON_GongXian
#define ID_BUTTON_GongXian		"ID_BUTTON_GongXian"
#endif  ID_BUTTON_GongXian
#ifndef ID_BUTTON_Activity
#define ID_BUTTON_Activity		"ID_BUTTON_Activity"
#endif  ID_BUTTON_Activity
#ifndef ID_BUTTON_Tong
#define ID_BUTTON_Tong		"ID_BUTTON_Tong"
#endif  ID_BUTTON_Tong
#ifndef ID_BUTTON_Job
#define ID_BUTTON_Job		"ID_BUTTON_Job"
#endif  ID_BUTTON_Job
#ifndef ID_TEXT_ArrowJob
#define ID_TEXT_ArrowJob		"ID_TEXT_ArrowJob"
#endif  ID_TEXT_ArrowJob
#ifndef ID_TEXT_ArrowActivity
#define ID_TEXT_ArrowActivity		"ID_TEXT_ArrowActivity"
#endif  ID_TEXT_ArrowActivity
#ifndef ID_TEXT_ArrowTong
#define ID_TEXT_ArrowTong		"ID_TEXT_ArrowTong"
#endif  ID_TEXT_ArrowTong
#ifndef ID_TEXT_ArrowWork
#define ID_TEXT_ArrowWork		"ID_TEXT_ArrowWork"
#endif  ID_TEXT_ArrowWork
#ifndef ID_TEXT_ArrowLvl
#define ID_TEXT_ArrowLvl		"ID_TEXT_ArrowLvl"
#endif  ID_TEXT_ArrowLvl
#ifndef ID_TEXT_ArrowTeamName
#define ID_TEXT_ArrowTeamName		"ID_TEXT_ArrowTeamName"
#endif  ID_TEXT_ArrowTeamName
#ifndef ID_TEXT_ArrowGongXian
#define ID_TEXT_ArrowGongXian		"ID_TEXT_ArrowGongXian"
#endif  ID_TEXT_ArrowGongXian
#ifndef ID_LIST_TeamName
#define ID_LIST_TeamName		"ID_LIST_TeamName"
#endif  ID_LIST_TeamName
#ifndef ID_LIST_GongXian
#define ID_LIST_GongXian		"ID_LIST_GongXian"
#endif  ID_LIST_GongXian
#ifndef ID_LIST_Activity
#define ID_LIST_Activity		"ID_LIST_Activity"
#endif  ID_LIST_Activity
#ifndef ID_LIST_Tong
#define ID_LIST_Tong		"ID_LIST_Tong"
#endif  ID_LIST_Tong
#ifndef ID_LIST_Work
#define ID_LIST_Work		"ID_LIST_Work"
#endif  ID_LIST_Work
#ifndef ID_LIST_Job
#define ID_LIST_Job		"ID_LIST_Job"
#endif  ID_LIST_Job
#ifndef ID_LIST_Lvl
#define ID_LIST_Lvl		"ID_LIST_Lvl"
#endif  ID_LIST_Lvl
#ifndef ID_LIST_MEMBER
#define ID_LIST_MEMBER		"ID_LIST_MEMBER"
#endif  ID_LIST_MEMBER

#ifndef ID_BUTTON_Depose
#define ID_BUTTON_Depose		"ID_BUTTON_Depose"
#endif  ID_BUTTON_Depose
#ifndef ID_BUTTON_AppointAssistant
#define ID_BUTTON_AppointAssistant		"ID_BUTTON_AppointAssistant"
#endif  ID_BUTTON_AppointAssistant

#ifndef ID_LIST_OnlineTime
#define ID_LIST_OnlineTime		"ID_LIST_OnlineTime"
#endif  ID_LIST_OnlineTime
#ifndef ID_BUTTON_OnlineTime
#define ID_BUTTON_OnlineTime		"ID_BUTTON_OnlineTime"
#endif  ID_BUTTON_OnlineTime
#ifndef ID_TEXT_OnlineTime
#define ID_TEXT_OnlineTime		"ID_TEXT_OnlineTime"
#endif  ID_TEXT_OnlineTime

class CUI_ID_FRAME_GuildMember :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GuildMember();
	 ControlFrame*	m_pID_FRAME_GuildMember;
	 ControlButton*	m_pID_BUTTON_Appoint;
	 ControlButton*	m_pID_BUTTON_Quit;
	 ControlButton*	m_pID_BUTTON_Del;
	 ControlButton*	m_pID_BUTTON_ZhuanRang;
	 ControlButton*	m_pID_BUTTON_ADD;
	 ControlButton*	m_pID_BUTTON_LeavePosition;
	 ControlCheckBox*	m_pID_CHECKBOX_ShowLeave;
	 ControlButton*	m_pID_BUTTON_TeamName;
	 ControlButton*	m_pID_BUTTON_Work;
	 ControlButton*	m_pID_BUTTON_Lvl;
	 ControlButton*	m_pID_BUTTON_GongXian;
	 ControlButton*	m_pID_BUTTON_Activity;
	 ControlButton*	m_pID_BUTTON_Tong;
	 ControlButton*	m_pID_BUTTON_Job;
	 ControlText*	m_pID_TEXT_ArrowJob;
	 ControlText*	m_pID_TEXT_ArrowActivity;
	 ControlText*	m_pID_TEXT_ArrowTong;
	 ControlText*	m_pID_TEXT_ArrowWork;
	 ControlText*	m_pID_TEXT_ArrowLvl;
	 ControlText*	m_pID_TEXT_ArrowTeamName;
	 ControlText*	m_pID_TEXT_ArrowGongXian;
	 ControlList*	m_pID_LIST_TeamName;
	 ControlList*	m_pID_LIST_GongXian;
	 ControlList*	m_pID_LIST_Activity;
	 ControlList*	m_pID_LIST_Tong;
	 ControlList*	m_pID_LIST_Work;
	 ControlList*	m_pID_LIST_Job;
	 ControlList*	m_pID_LIST_Lvl;
	 ControlList*	m_pID_LIST_MEMBER;

	 ControlButton* m_pID_BUTTON_Depose;
	 ControlButton* m_pID_BUTTON_AppointAssistant;


	 ControlList*	m_pID_LIST_OnlineTime;
	 ControlButton* m_pID_BUTTON_OnlineTime;
	 ControlText*	m_pID_TEXT_OnlineTime;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_AppointOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_QuitOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ZhuanRangOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ADDOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LeavePositionOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_ShowLeaveOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_TeamNameOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_WorkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LvlOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GongXianOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ActivityOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TongOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_JobOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_OnlineTimeOnButtonClick( ControlObject* pSender );
	void ID_LIST_TeamNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GongXianOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ActivityOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_TongOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_WorkOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_JobOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_LvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_MEMBEROnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_OnlineTimeOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_DeposeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AppointAssistantOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }
	
	void OnUpdateUiInfo();
	void OnShow();

	static bool IsOperateOnMyself(int);
	static bool LeaveGuild(char m_ok,void *data);
	static bool GuildDelMemberCallBack(char, void*);
	static bool ZhuanRang(char m_ok,void *data);

	static void ID_List_OnRBClick(ControlObject* pSender, ControlList::S_List* pItem);

private:
	void		SetGuildMemberInfo();
	void		ShowSelectNothingMessage();
	enum SortType
	{
		ekey_name,
		ekey_level,
		ekey_profession,
		ekey_position,
		ekey_active,
		ekey_offer,
		eKey_OnLineTime,
		ekey_max = 7,
	};
private:
	bool		m_IsNeedUpdate;

	bool		m_IsShowNonOnLinePlayer;
	
	GuildMember* m_pMovedMember;
	GuildMember* m_pAcceptPositionMember;
private:
	void SetSortFunc(SortType ekey);

	typedef bool (*funcSort) (GuildMember* lhs, GuildMember* rhs);

	static bool SortByName(GuildMember* lhs, GuildMember* rhs);
	static bool SortByLevel(GuildMember* lhs, GuildMember* rhs);
	static bool SortByProfession(GuildMember* lhs, GuildMember* rhs);
	static bool SortByPosition(GuildMember* lhs, GuildMember* rhs);
	static bool SortByFamily(GuildMember* lhs, GuildMember* rhs);
	static bool SortByActive(GuildMember* lhs, GuildMember* rhs);
	static bool SortByOffer(GuildMember* lhs, GuildMember* rhs);
	static bool SortByOnlineTime(GuildMember* lhs, GuildMember* rhs);
	
	static bool SortByName_Reverse(GuildMember* lhs, GuildMember* rhs);
	static bool SortByLevel_Reverse(GuildMember* lhs, GuildMember* rhs);
	static bool SortByProfession_Reverse( GuildMember* lhs, GuildMember* rhs );
	static bool SortByPosition_Reverse( GuildMember* lhs, GuildMember* rhs );
	static bool SortByFamily_Reverse( GuildMember* lhs, GuildMember* rhs );
	static bool SortByActive_Reverse( GuildMember* lhs, GuildMember* rhs );
	static bool SortByOffer_Reverse( GuildMember* lhs, GuildMember* rhs );
	static bool SortByOnlineTime_Reverse( GuildMember* lhs, GuildMember* rhs );

	void SortAndRefresh();
	void ShowSortArrow();
	void ShowOnlineMember();
	void ShowNonOnlineMember();
	void InitArrowArray();
	void SetSkipAllMsg();
	void ResetSortMember();

	bool CheckCanTransferPosition() const;
	void ShowUnableTransferPositionWhenIsKingGuild();
	void ShowUnableTransferPosition();
	void ShowTransferPositionInfo();
	void InitAllSortFunc();
	void SetAllList();
	void ClearAllList();
	void AddToList(GuildMember* pMember, DWORD color);
	const char* GetPositionByID(int nPosition) const ;
	const char* GetProfessionByID(int nPosition) const ;

	void OnUpdateListShowHeight();
	void ClearButtonAppoint();
private:
	//排序用数据
	funcSort m_funcSort[ekey_max];
	funcSort m_funcSortReverse[ekey_max];
	funcSort m_currentSortFunc;
	SortType m_key;
	ControlText* m_pID_TEXT_Arrow[ekey_max];
	bool m_bArrow[ekey_max];
	vector<GuildMember*> m_vctAllMember;
};
extern CUI_ID_FRAME_GuildMember s_CUI_ID_FRAME_GuildMember;
