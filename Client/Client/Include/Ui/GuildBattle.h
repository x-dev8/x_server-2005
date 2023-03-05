/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\RTX\帮会战界面\GuildBattle.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#include "CampBattleDefine.h"

#ifndef ID_FRAME_GuildBattle
#define ID_FRAME_GuildBattle		"ID_FRAME_GuildBattle"
#endif  ID_FRAME_GuildBattle
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_Rank1
#define ID_BUTTON_Rank1		"ID_BUTTON_Rank1"
#endif  ID_BUTTON_Rank1
#ifndef ID_BUTTON_Name1
#define ID_BUTTON_Name1		"ID_BUTTON_Name1"
#endif  ID_BUTTON_Name1
#ifndef ID_BUTTON_Level1
#define ID_BUTTON_Level1		"ID_BUTTON_Level1"
#endif  ID_BUTTON_Level1
#ifndef ID_BUTTON_Job1
#define ID_BUTTON_Job1		"ID_BUTTON_Job1"
#endif  ID_BUTTON_Job1
#ifndef ID_BUTTON_Kill1
#define ID_BUTTON_Kill1		"ID_BUTTON_Kill1"
#endif  ID_BUTTON_Kill1
#ifndef ID_BUTTON_Death1
#define ID_BUTTON_Death1		"ID_BUTTON_Death1"
#endif  ID_BUTTON_Death1
#ifndef ID_LIST_Rank1
#define ID_LIST_Rank1		"ID_LIST_Rank1"
#endif  ID_LIST_Rank1
#ifndef ID_LIST_Name1
#define ID_LIST_Name1		"ID_LIST_Name1"
#endif  ID_LIST_Name1
#ifndef ID_LIST_Level1
#define ID_LIST_Level1		"ID_LIST_Level1"
#endif  ID_LIST_Level1
#ifndef ID_LIST_Job1
#define ID_LIST_Job1		"ID_LIST_Job1"
#endif  ID_LIST_Job1
#ifndef ID_LIST_Kill1
#define ID_LIST_Kill1		"ID_LIST_Kill1"
#endif  ID_LIST_Kill1
#ifndef ID_LIST_Death1
#define ID_LIST_Death1		"ID_LIST_Death1"
#endif  ID_LIST_Death1
#ifndef ID_LIST_GuildBattle1
#define ID_LIST_GuildBattle1		"ID_LIST_GuildBattle1"
#endif  ID_LIST_GuildBattle1
#ifndef ID_TEXT_ArrowLevel1
#define ID_TEXT_ArrowLevel1		"ID_TEXT_ArrowLevel1"
#endif  ID_TEXT_ArrowLevel1
#ifndef ID_TEXT_ArrowKill1
#define ID_TEXT_ArrowKill1		"ID_TEXT_ArrowKill1"
#endif  ID_TEXT_ArrowKill1
#ifndef ID_TEXT_ArrowDeath1
#define ID_TEXT_ArrowDeath1		"ID_TEXT_ArrowDeath1"
#endif  ID_TEXT_ArrowDeath1
#ifndef ID_TEXT_GuildName1
#define ID_TEXT_GuildName1		"ID_TEXT_GuildName1"
#endif  ID_TEXT_GuildName1
#ifndef ID_TEXT_Player1
#define ID_TEXT_Player1		"ID_TEXT_Player1"
#endif  ID_TEXT_Player1
#ifndef ID_TEXT_Score1
#define ID_TEXT_Score1		"ID_TEXT_Score1"
#endif  ID_TEXT_Score1
#ifndef ID_BUTTON_Rank2
#define ID_BUTTON_Rank2		"ID_BUTTON_Rank2"
#endif  ID_BUTTON_Rank2
#ifndef ID_BUTTON_Name2
#define ID_BUTTON_Name2		"ID_BUTTON_Name2"
#endif  ID_BUTTON_Name2
#ifndef ID_BUTTON_Level2
#define ID_BUTTON_Level2		"ID_BUTTON_Level2"
#endif  ID_BUTTON_Level2
#ifndef ID_BUTTON_Job2
#define ID_BUTTON_Job2		"ID_BUTTON_Job2"
#endif  ID_BUTTON_Job2
#ifndef ID_BUTTON_Kill2
#define ID_BUTTON_Kill2		"ID_BUTTON_Kill2"
#endif  ID_BUTTON_Kill2
#ifndef ID_BUTTON_Death2
#define ID_BUTTON_Death2		"ID_BUTTON_Death2"
#endif  ID_BUTTON_Death2
#ifndef ID_TEXT_ArrowLevel2
#define ID_TEXT_ArrowLevel2		"ID_TEXT_ArrowLevel2"
#endif  ID_TEXT_ArrowLevel2
#ifndef ID_TEXT_ArrowKill2
#define ID_TEXT_ArrowKill2		"ID_TEXT_ArrowKill2"
#endif  ID_TEXT_ArrowKill2
#ifndef ID_TEXT_ArrowDeath2
#define ID_TEXT_ArrowDeath2		"ID_TEXT_ArrowDeath2"
#endif  ID_TEXT_ArrowDeath2
#ifndef ID_LIST_Rank2
#define ID_LIST_Rank2		"ID_LIST_Rank2"
#endif  ID_LIST_Rank2
#ifndef ID_LIST_Name2
#define ID_LIST_Name2		"ID_LIST_Name2"
#endif  ID_LIST_Name2
#ifndef ID_LIST_Level2
#define ID_LIST_Level2		"ID_LIST_Level2"
#endif  ID_LIST_Level2
#ifndef ID_LIST_Job2
#define ID_LIST_Job2		"ID_LIST_Job2"
#endif  ID_LIST_Job2
#ifndef ID_LIST_Kill2
#define ID_LIST_Kill2		"ID_LIST_Kill2"
#endif  ID_LIST_Kill2
#ifndef ID_LIST_Death2
#define ID_LIST_Death2		"ID_LIST_Death2"
#endif  ID_LIST_Death2
#ifndef ID_LIST_GuildBattle2
#define ID_LIST_GuildBattle2		"ID_LIST_GuildBattle2"
#endif  ID_LIST_GuildBattle2
#ifndef ID_TEXT_GuildName2
#define ID_TEXT_GuildName2		"ID_TEXT_GuildName2"
#endif  ID_TEXT_GuildName2
#ifndef ID_TEXT_Player2
#define ID_TEXT_Player2		"ID_TEXT_Player2"
#endif  ID_TEXT_Player2
#ifndef ID_TEXT_Score2
#define ID_TEXT_Score2		"ID_TEXT_Score2"
#endif  ID_TEXT_Score2
#ifndef ID_BUTTON_Leave
#define ID_BUTTON_Leave		"ID_BUTTON_Leave"
#endif  ID_BUTTON_Leave
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel

enum eSortType
{
	ekey_Level,
	ekey_kill,
	ekey_death,
	ekey_max
};

enum eListType
{
	eList_big,
	eList_rank,
	eList_name,
	eList_level,
	eList_job,
	eList_kill,
	eList_death,
	eList_max
};

typedef BattlePlayer xPlayer;

struct Data
{
	Data(int i = 0, xPlayer* p = NULL)
	{
		m_nRank = i;
		m_pValue = p;
	}
	int m_nRank;
	xPlayer* m_pValue;
};

class BattleData
{
public:
	BattleData() { Init(); }

public:
	typedef bool(*SortFunc)(const Data& lhs, const Data& rhs);

	static bool SortByLevel_Greater(const Data& lhs, const Data& rhs);
	static bool SortByKill_Greater(const Data& lhs, const Data& rhs);
	static bool SortByDeath_Greater(const Data& lhs, const Data& rhs);

	static bool SortByLevel_Less(const Data& lhs, const Data& rhs);
	static bool SortByKill_Less(const Data& lhs, const Data& rhs);
	static bool SortByDeath_Less(const Data& lhs, const Data& rhs);

private:
	void Init();

	eSortType m_key;
	SortFunc m_currentSortFunc;
	bool m_bArrow[ekey_max];
	SortFunc m_funcSort[ekey_max];
	SortFunc m_funcSortReverse[ekey_max];
	ControlText* m_pID_TEXT_Arrow[ekey_max];
	ControlList* m_pListCtl[eList_max];

private:
	void AddDataToList();
	void AddToListHelp(const Data* pData, DWORD color) const;
	void Sort();
	void InitSortFunc();
	void ShowSortArrow();
	bool m_bNeedRefresh;

public:
	void Clear();
	void ClearList();
	void InitListCtl(ControlList**);
	void InitArrowArray(ControlText**);
	void SetSortFunc(eSortType);
	void SetNeedRefresh(bool bNeed) { m_bNeedRefresh = bNeed; }
	bool GetNeedRefresh() { return m_bNeedRefresh; }
	void ResetSortTypeAndArrowShow();
	void push_back(const Data& rf) { m_xData.push_back(rf); }
	void Refresh();
	int GetMemberCount() { return m_xData.size(); }

private:
	std::vector<Data> m_xData;
};

class CUI_ID_FRAME_GuildBattle: public CUIBase
{
	// Member
public:
	CUI_ID_FRAME_GuildBattle();

private:	
	 ControlFrame*	m_pID_FRAME_GuildBattle;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_Rank1;
	 ControlButton*	m_pID_BUTTON_Name1;
	 ControlButton*	m_pID_BUTTON_Level1;
	 ControlButton*	m_pID_BUTTON_Job1;
	 ControlButton*	m_pID_BUTTON_Kill1;
	 ControlButton*	m_pID_BUTTON_Death1;
	 ControlList*	m_pID_LIST_Rank1;
	 ControlList*	m_pID_LIST_Name1;
	 ControlList*	m_pID_LIST_Level1;
	 ControlList*	m_pID_LIST_Job1;
	 ControlList*	m_pID_LIST_Kill1;
	 ControlList*	m_pID_LIST_Death1;
	 ControlList*	m_pID_LIST_GuildBattle1;
	 ControlText*	m_pID_TEXT_ArrowLevel1;
	 ControlText*	m_pID_TEXT_ArrowKill1;
	 ControlText*	m_pID_TEXT_ArrowDeath1;
	 ControlText*	m_pID_TEXT_GuildName1;
	 ControlText*	m_pID_TEXT_Player1;
	 ControlText*	m_pID_TEXT_Score1;

	 ControlButton*	m_pID_BUTTON_Rank2;
	 ControlButton*	m_pID_BUTTON_Name2;
	 ControlButton*	m_pID_BUTTON_Level2;
	 ControlButton*	m_pID_BUTTON_Job2;
	 ControlButton*	m_pID_BUTTON_Kill2;
	 ControlButton*	m_pID_BUTTON_Death2;
	 ControlText*	m_pID_TEXT_ArrowLevel2;
	 ControlText*	m_pID_TEXT_ArrowKill2;
	 ControlText*	m_pID_TEXT_ArrowDeath2;
	 ControlList*	m_pID_LIST_Rank2;
	 ControlList*	m_pID_LIST_Name2;
	 ControlList*	m_pID_LIST_Level2;
	 ControlList*	m_pID_LIST_Job2;
	 ControlList*	m_pID_LIST_Kill2;
	 ControlList*	m_pID_LIST_Death2;
	 ControlList*	m_pID_LIST_GuildBattle2;
	 ControlText*	m_pID_TEXT_GuildName2;
	 ControlText*	m_pID_TEXT_Player2;
	 ControlText*	m_pID_TEXT_Score2;
	 ControlButton*	m_pID_BUTTON_Leave;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlList* m_arraySelfListCtl[eList_max];
	 ControlList* m_arrayEnemyListCtl[eList_max];
	 ControlText* m_arraySelfTextCtl[ekey_max];
	 ControlText* m_arrayEnemyTextCtl[ekey_max];

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Rank1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Name1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Level1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Job1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Kill1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Death1OnButtonClick( ControlObject* pSender );
	void ID_LIST_Rank1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_Name1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_Level1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_Job1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_Kill1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_Death1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildBattle1OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_Rank2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Name2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Level2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Job2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Kill2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Death2OnButtonClick( ControlObject* pSender );
	void ID_LIST_Rank2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_Name2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_Level2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_Job2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_Kill2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_Death2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildBattle2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_LeaveOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	//----------------------------------------------------------------

private:
	void SetSkipAllMsg();
private:
	void AckInfo();
	void Refresh();
	void Clear();
	void SetText();
	void SetGuildName();
	void GetSelfListAndScrollBarShowHeight(int&, int&);
	void GetOtherListAndScrollBarShowHeight(int&, int&);
	void SetSelfListAndScrollBarShowHeight(int&, int&);
	void SetOtherListAndScrollBarShowHeight(int&, int&);

public:
	void InitBattleInfo(int nCount, const xPlayer* pXplayer);
	void SetNeedRefresh();
	void RefreshScore();
	
private:
	std::vector<xPlayer> m_vctTotalBattlePlayer;

	std::vector<xPlayer*> m_vctOurBattlePlayer;
	std::vector<xPlayer*> m_vctOtherBattlePlayer;
	
	void InitBothData();
	void SortAndStoreInfo(std::vector<xPlayer*>& rfVct, BattleData&);
	
private:
	BattleData m_ourData;
	BattleData m_otherData;
};
extern CUI_ID_FRAME_GuildBattle s_CUI_ID_FRAME_GuildBattle;