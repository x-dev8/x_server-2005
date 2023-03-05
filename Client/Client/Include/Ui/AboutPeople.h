/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\mingyuan.zhang\桌面\新建文件夹 (7)\AboutPeople.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_AboutPeople
#define ID_FRAME_AboutPeople		"ID_FRAME_AboutPeople"
#endif  ID_FRAME_AboutPeople
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_LIST_TeamName
#define ID_LIST_TeamName		"ID_LIST_TeamName"
#endif  ID_LIST_TeamName
#ifndef ID_LIST_PeopleName
#define ID_LIST_PeopleName		"ID_LIST_PeopleName"
#endif  ID_LIST_PeopleName
#ifndef ID_LIST_LV
#define ID_LIST_LV		"ID_LIST_LV"
#endif  ID_LIST_LV
#ifndef ID_LIST_Job
#define ID_LIST_Job		"ID_LIST_Job"
#endif  ID_LIST_Job
#ifndef ID_LIST_TeamEffect
#define ID_LIST_TeamEffect		"ID_LIST_TeamEffect"
#endif  ID_LIST_TeamEffect
#ifndef ID_BUTTON_Team
#define ID_BUTTON_Team		"ID_BUTTON_Team"
#endif  ID_BUTTON_Team
#ifndef ID_BUTTON_Name
#define ID_BUTTON_Name		"ID_BUTTON_Name"
#endif  ID_BUTTON_Name
#ifndef ID_BUTTON_LV
#define ID_BUTTON_LV		"ID_BUTTON_LV"
#endif  ID_BUTTON_LV
#ifndef ID_BUTTON_Job
#define ID_BUTTON_Job		"ID_BUTTON_Job"
#endif  ID_BUTTON_Job
#ifndef ID_TEXT_Team
#define ID_TEXT_Team		"ID_TEXT_Team"
#endif  ID_TEXT_Team
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_LV
#define ID_TEXT_LV		"ID_TEXT_LV"
#endif  ID_TEXT_LV
#ifndef ID_TEXT_Job
#define ID_TEXT_Job		"ID_TEXT_Job"
#endif  ID_TEXT_Job
#ifndef ID_CHECKBOX_Friend
#define ID_CHECKBOX_Friend		"ID_CHECKBOX_Friend"
#endif  ID_CHECKBOX_Friend
#ifndef ID_CHECKBOX_Foe
#define ID_CHECKBOX_Foe		"ID_CHECKBOX_Foe"
#endif  ID_CHECKBOX_Foe

#include "UIBase.h"

class CUI_ID_FRAME_AboutPeople : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_AboutPeople();

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	void ID_LIST_TeamNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_PeopleNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_LVOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_JobOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_TeamEffectOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_FriendOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FoeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TeamOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_NameOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LVOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_JobOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_FriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_FoeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	const char* GetMPTypeString( int nProfession );

public:
	static void ID_List_OnRBClick(ControlObject* pSender, ControlList::S_List* pItem);
protected:
	void ClearList();
	void AddToList( const char* teamName, const char* playerName, const char* level, const char* professional, const DWORD clr ); //添加玩家的队伍，玩家姓名，等级职业
	
protected:
	void InitialActivePlayerList();
	void RefreshPlayerInfo();
private:
	ControlFrame*	m_pID_FRAME_AboutPeople;
	ControlButton*	m_pID_BUTTON_HELP;
	ControlButton*	m_pID_BUTTON_CLOSE;
	ControlList*	m_pID_LIST_TeamName;
	ControlList*	m_pID_LIST_PeopleName;
	ControlList*	m_pID_LIST_LV;
	ControlList*	m_pID_LIST_Job;
	ControlList*	m_pID_LIST_TeamEffect;

	ControlButton*	m_pID_BUTTON_Team;
	ControlButton*	m_pID_BUTTON_Name;
	ControlButton*	m_pID_BUTTON_LV;
	ControlButton*	m_pID_BUTTON_Job;
	ControlText*	m_pID_TEXT_Team;
	ControlText*	m_pID_TEXT_Name;
	ControlText*	m_pID_TEXT_LV;
	ControlText*	m_pID_TEXT_Job;
	ControlCheckBox*	m_pID_CHECKBOX_Friend;
	ControlCheckBox*	m_pID_CHECKBOX_Foe;
private:
	enum ListType
	{
		List_None,
		List_Friend,
		List_Enemy
	};

	ListType m_eType;

private:
	std::vector<CPlayer*> m_vecSet;
public:
	enum SortType
	{
		Sort_None, //无
		Sort_Name, //名字
		Sort_Team, //队伍
		Sort_LV,   //等级
		Sort_Job   //职业
	};

	void SortListByType(SortType eType);

	static bool SortByName(CPlayer* pPlayer1,CPlayer* pPlayer2);
	static bool SortByTeam(CPlayer* pPlayer1,CPlayer* pPlayer2);
	static bool SortByLV(CPlayer* pPlayer1,CPlayer* pPlayer2);
	static bool SortByJob(CPlayer* pPlayer1,CPlayer* pPlayer2);
	static bool s_Up;
private:
	SortType m_eSortType;
public:
	void SetListType(ListType eType);
	bool IsCanShow(ListType eType,CPlayer* pPlayer);
	bool IsEnemy(CPlayer *pPlayer);
	void SetSortTypeInUi(SortType eType);
};
extern CUI_ID_FRAME_AboutPeople s_CUI_ID_FRAME_AboutPeople;
