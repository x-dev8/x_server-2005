/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildSQ.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "GuildDefine.h"
#include "UiBase.h"
#ifndef ID_FRAME_GuildSQ
#define ID_FRAME_GuildSQ		"ID_FRAME_GuildSQ"
#endif  ID_FRAME_GuildSQ
#ifndef ID_BUTTON_Index
#define ID_BUTTON_Index		"ID_BUTTON_Index"
#endif  ID_BUTTON_Index
#ifndef ID_BUTTON_Profession
#define ID_BUTTON_Profession		"ID_BUTTON_Profession"
#endif  ID_BUTTON_Profession
#ifndef ID_BUTTON_Level
#define ID_BUTTON_Level		"ID_BUTTON_Level"
#endif  ID_BUTTON_Level
#ifndef ID_BUTTON_Name
#define ID_BUTTON_Name		"ID_BUTTON_Name"
#endif  ID_BUTTON_Name
#ifndef ID_TEXT_Index
#define ID_TEXT_Index		"ID_TEXT_Index"
#endif  ID_TEXT_Index
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_TEXT_Level
#define ID_TEXT_Level		"ID_TEXT_Level"
#endif  ID_TEXT_Level
#ifndef ID_TEXT_Profession
#define ID_TEXT_Profession		"ID_TEXT_Profession"
#endif  ID_TEXT_Profession
#ifndef ID_LIST_Index
#define ID_LIST_Index		"ID_LIST_Index"
#endif  ID_LIST_Index
#ifndef ID_LIST_Profession
#define ID_LIST_Profession		"ID_LIST_Profession"
#endif  ID_LIST_Profession
#ifndef ID_LIST_Level
#define ID_LIST_Level		"ID_LIST_Level"
#endif  ID_LIST_Level
#ifndef ID_LIST_Name
#define ID_LIST_Name		"ID_LIST_Name"
#endif  ID_LIST_Name
#ifndef ID_BUTTON_Accept
#define ID_BUTTON_Accept		"ID_BUTTON_Accept"
#endif  ID_BUTTON_Accept
#ifndef ID_BUTTON_Refuse
#define ID_BUTTON_Refuse		"ID_BUTTON_Refuse"
#endif  ID_BUTTON_Refuse
#ifndef ID_LIST_MEMBER
#define ID_LIST_MEMBER		"ID_LIST_MEMBER"
#endif  ID_LIST_MEMBER

struct GuildSQInfo
{
	uint32	ID;
	uint32	Level;
	uint16  Profession;
	char	Name[33];
};

class CUI_ID_FRAME_GuildSQ :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GuildSQ();
	 ControlFrame*	m_pID_FRAME_GuildSQ;

	 ControlButton*	m_pID_BUTTON_Index;
	 ControlButton*	m_pID_BUTTON_Profession;
	 ControlButton*	m_pID_BUTTON_Level;
	 ControlButton*	m_pID_BUTTON_Name;

	 ControlText*	m_pID_TEXT_Index;
	 ControlText*	m_pID_TEXT_Name;
	 ControlText*	m_pID_TEXT_Level;
	 ControlText*	m_pID_TEXT_Profession;

	 ControlList*	m_pID_LIST_Index;
	 ControlList*	m_pID_LIST_Profession;
	 ControlList*	m_pID_LIST_Level;
	 ControlList*	m_pID_LIST_Name;

	 ControlButton*	m_pID_BUTTON_Accept;
	 ControlButton*	m_pID_BUTTON_Refuse;
	 ControlList*	m_pID_LIST_MEMBER;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_IndexOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ProfessionOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LevelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_NameOnButtonClick( ControlObject* pSender );
	void ID_LIST_IndexOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ProfessionOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_LevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_AcceptOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RefuseOnButtonClick( ControlObject* pSender );
	void ID_LIST_MEMBEROnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual bool IsHoldInMemory() const { return true; }

	void OnUpdateUiInfo();
	void OnShow();

	void AddGuildMember(GuildSQInfo& pGuildMember);
	void DelGuildMember(uint32 ID);
	void AddGuildMenberList(GuildSQInfo* pGuildMember,uint32 Num);
	void ClearGuildMemberInfo();

	static bool IsOperateOnMyself(int);
	void		ShowSelectNothingMessage();
private:
	vector<GuildSQInfo>			m_MemberList;//玩家申请加入公会的列表
	bool						m_IsNeedUpdate;
//排序
private:
	enum SortType
	{
		ekey_id,
		ekey_name,
		ekey_level,
		ekey_profession,
		ekey_max = 4,
	};

	void SetSortFunc(SortType ekey);
	typedef bool (*funcSort) (GuildSQInfo lhs, GuildSQInfo rhs);
	static bool SortByID(GuildSQInfo lhs, GuildSQInfo rhs);
	static bool SortByName(GuildSQInfo lhs, GuildSQInfo rhs);
	static bool SortByLevel(GuildSQInfo lhs, GuildSQInfo rhs);
	static bool SortByProfession(GuildSQInfo lhs, GuildSQInfo rhs);
	static bool SortByID_Reverse(GuildSQInfo lhs, GuildSQInfo rhs);
	static bool SortByName_Reverse(GuildSQInfo lhs, GuildSQInfo rhs);
	static bool SortByLevel_Reverse(GuildSQInfo lhs, GuildSQInfo rhs);
	static bool SortByProfession_Reverse( GuildSQInfo lhs, GuildSQInfo rhs );

	void SetGuildMemberInfo();
	void SortAndRefresh();
	void ShowSortArrow();
	void InitArrowArray();
	void SetSkipAllMsg();
	void ResetSortMember();
	void SetAllList();
	void ClearAllList();
	void AddToList(GuildSQInfo& pMember, DWORD color);

	const char* GetProfessionByID(int nPosition) const ;

	void InitAllSortFunc();
private:
	funcSort m_funcSort[ekey_max];
	funcSort m_funcSortReverse[ekey_max];
	funcSort m_currentSortFunc;
	SortType m_key;
	ControlText* m_pID_TEXT_Arrow[ekey_max];
	bool m_bArrow[ekey_max];
};
extern CUI_ID_FRAME_GuildSQ s_CUI_ID_FRAME_GuildSQ;
