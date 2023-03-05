/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\Alignment.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_Alignment
#define ID_FRAME_Alignment		"ID_FRAME_Alignment"
#endif  ID_FRAME_Alignment
#ifndef ID_PICTURE_Di
#define ID_PICTURE_Di		"ID_PICTURE_Di"
#endif  ID_PICTURE_Di
#ifndef ID_PICTURE_TitleDi
#define ID_PICTURE_TitleDi		"ID_PICTURE_TitleDi"
#endif  ID_PICTURE_TitleDi
#ifndef ID_PICTURE_WallPaper
#define ID_PICTURE_WallPaper		"ID_PICTURE_WallPaper"
#endif  ID_PICTURE_WallPaper
#ifndef ID_TEXT_Title
#define ID_TEXT_Title		"ID_TEXT_Title"
#endif  ID_TEXT_Title
#ifndef ID_LIST_GuildList
#define ID_LIST_GuildList		"ID_LIST_GuildList"
#endif  ID_LIST_GuildList
#ifndef ID_CHECKBOX_Friend
#define ID_CHECKBOX_Friend		"ID_CHECKBOX_Friend"
#endif  ID_CHECKBOX_Friend
#ifndef ID_CHECKBOX_Enemy
#define ID_CHECKBOX_Enemy		"ID_CHECKBOX_Enemy"
#endif  ID_CHECKBOX_Enemy
#ifndef ID_BUTTON_Invite
#define ID_BUTTON_Invite		"ID_BUTTON_Invite"
#endif  ID_BUTTON_Invite
#ifndef ID_EDIT_Search
#define ID_EDIT_Search		"ID_EDIT_Search"
#endif  ID_EDIT_Search
#ifndef ID_BUTTON_Next
#define ID_BUTTON_Next		"ID_BUTTON_Next"
#endif  ID_BUTTON_Next
#ifndef ID_PICTURE_WallLeft2
#define ID_PICTURE_WallLeft2		"ID_PICTURE_WallLeft2"
#endif  ID_PICTURE_WallLeft2
#ifndef ID_PICTURE_WallRight2
#define ID_PICTURE_WallRight2		"ID_PICTURE_WallRight2"
#endif  ID_PICTURE_WallRight2
#ifndef ID_PICTURE_WallLeft
#define ID_PICTURE_WallLeft		"ID_PICTURE_WallLeft"
#endif  ID_PICTURE_WallLeft
#ifndef ID_PICTURE_WallRight
#define ID_PICTURE_WallRight		"ID_PICTURE_WallRight"
#endif  ID_PICTURE_WallRight
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_help
#define ID_BUTTON_help		"ID_BUTTON_help"
#endif  ID_BUTTON_help
#ifndef ID_CHECKBOX_Stranger
#define ID_CHECKBOX_Stranger		"ID_CHECKBOX_Stranger"
#endif  ID_CHECKBOX_Stranger
#ifndef ID_TEXT_G
#define ID_TEXT_G		"ID_TEXT_G"
#endif  ID_TEXT_G
#ifndef ID_BUTTON_GuildName
#define ID_BUTTON_GuildName		"ID_BUTTON_GuildName"
#endif  ID_BUTTON_GuildName
#ifndef ID_BUTTON_GuildLeader
#define ID_BUTTON_GuildLeader		"ID_BUTTON_GuildLeader"
#endif  ID_BUTTON_GuildLeader
#ifndef ID_BUTTON_Number
#define ID_BUTTON_Number		"ID_BUTTON_Number"
#endif  ID_BUTTON_Number
#ifndef ID_LIST_GuildName
#define ID_LIST_GuildName		"ID_LIST_GuildName"
#endif  ID_LIST_GuildName
#ifndef ID_LIST_GuildLeader
#define ID_LIST_GuildLeader		"ID_LIST_GuildLeader"
#endif  ID_LIST_GuildLeader
#ifndef ID_LIST_Lvl
#define ID_LIST_Lvl		"ID_LIST_Lvl"
#endif  ID_LIST_Lvl
#ifndef ID_BUTTON_Enemy
#define ID_BUTTON_Enemy		"ID_BUTTON_Enemy"
#endif  ID_BUTTON_Enemy
#ifndef ID_BUTTON_JieChu
#define ID_BUTTON_JieChu		"ID_BUTTON_JieChu"
#endif  ID_BUTTON_JieChu
#ifndef ID_BUTTON_YanHe
#define ID_BUTTON_YanHe		"ID_BUTTON_YanHe"
#endif  ID_BUTTON_YanHe
#ifndef ID_BUTTON_QiangZhi
#define ID_BUTTON_QiangZhi		"ID_BUTTON_QiangZhi"
#endif  ID_BUTTON_QiangZhi
#ifndef ID_TEXT_ArrowGuildName
#define ID_TEXT_ArrowGuildName		"ID_TEXT_ArrowGuildName"
#endif  ID_TEXT_ArrowGuildName
#ifndef ID_TEXT_ArrowGuildLeader
#define ID_TEXT_ArrowGuildLeader		"ID_TEXT_ArrowGuildLeader"
#endif  ID_TEXT_ArrowGuildLeader
#ifndef ID_TEXT_ArrowNumber
#define ID_TEXT_ArrowNumber		"ID_TEXT_ArrowNumber"
#endif  ID_TEXT_ArrowNumber
#ifndef ID_TEXT_Wait
#define ID_TEXT_Wait		"ID_TEXT_Wait"
#endif  ID_TEXT_Wait
#ifndef ID_LIST_Number
#define ID_LIST_Number		"ID_LIST_Number"
#endif  ID_LIST_Number
#ifndef ID_BUTTON_GuildLvl
#define ID_BUTTON_GuildLvl		"ID_BUTTON_GuildLvl"
#endif  ID_BUTTON_GuildLvl
#ifndef ID_TEXT_ArrowGuildLvl
#define ID_TEXT_ArrowGuildLvl		"ID_TEXT_ArrowGuildLvl"
#endif  ID_TEXT_ArrowGuildLvl

class GuildInfoEx;
#include "UiBase.h"
class CUI_ID_FRAME_Alignment :public CUIBase
{
	// Member
public:	
	enum eSortType
	{
		ESName = 0,
		ESLeader,
		ESNumber,
		ESLevel,
		eSortTypeTotal
	};

	 CUI_ID_FRAME_Alignment();
private:
	 ControlFrame*	m_pID_FRAME_Alignment;
	 ControlPicture*	m_pID_PICTURE_Di;
	 ControlPicture*	m_pID_PICTURE_TitleDi;
	 ControlPicture*	m_pID_PICTURE_WallPaper;
	 ControlText*	m_pID_TEXT_Title;
	 ControlList*	m_pID_LIST_GuildList;
	 ControlCheckBox*	m_pID_CHECKBOX_Friend;
	 ControlCheckBox*	m_pID_CHECKBOX_Enemy;
	 ControlButton*	m_pID_BUTTON_Invite;
	 ControlEdit*	m_pID_EDIT_Search;
	 ControlButton*	m_pID_BUTTON_Next;
	 ControlPicture*	m_pID_PICTURE_WallLeft2;
	 ControlPicture*	m_pID_PICTURE_WallRight2;
	 ControlPicture*	m_pID_PICTURE_WallLeft;
	 ControlPicture*	m_pID_PICTURE_WallRight;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_help;
	 ControlCheckBox*	m_pID_CHECKBOX_Stranger;
	 ControlText*	m_pID_TEXT_G;
	 ControlButton*	m_pID_BUTTON_GuildName;
	 ControlButton*	m_pID_BUTTON_GuildLeader;
	 ControlButton*	m_pID_BUTTON_Number;
	 ControlList*	m_pID_LIST_GuildName;
	 ControlList*	m_pID_LIST_GuildLeader;
	 ControlList*	m_pID_LIST_Lvl;
	 ControlButton*	m_pID_BUTTON_Enemy;
	 ControlButton*	m_pID_BUTTON_JieChu;
	 ControlButton*	m_pID_BUTTON_YanHe;
	 ControlButton*	m_pID_BUTTON_QiangZhi;
	 ControlText*	m_pID_TEXT_ArrowGuildName;
	 ControlText*	m_pID_TEXT_ArrowGuildLeader;
	 ControlText*	m_pID_TEXT_ArrowNumber;
	 ControlText*	m_pID_TEXT_Wait;
	 ControlList*	m_pID_LIST_Number;
	 ControlButton*	m_pID_BUTTON_GuildLvl;
	 ControlText*	m_pID_TEXT_ArrowGuildLvl;

	ControlText*						m_pID_TEXT_Arrow[eSortTypeTotal];
	bool								m_bArrow[eSortTypeTotal];

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_GuildListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_FriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_EnemyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_InviteOnButtonClick( ControlObject* pSender );
	void ID_EDIT_SearchOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_NextOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_helpOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_StrangerOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_GuildNameOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GuildLeaderOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_NumberOnButtonClick( ControlObject* pSender );
	void ID_LIST_GuildNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_GuildLeaderOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_LvlOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_EnemyOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_JieChuOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_YanHeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_QiangZhiOnButtonClick( ControlObject* pSender );
	void ID_LIST_NumberOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_GuildLvlOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void SetTextWait(const char* chr);

private:
	void RefreshUI();
	void InitialChildList(ControlList* m_p_LIST);
	void RefreshChildList();
	void FillMemberList( void* pVoid, DWORD dwColor);
	void RefreshOptButton();
	void UpdateGuildList();
	void UpdateGuildListUI();
	std::string m_strName;
	void GetMemberListCurSelName();
	int  GetSelectDBId();

	bool IsExistRelation(int id);
	int nRelationType;
	int nSortType;
	std::list<GuildInfoEx*> resultList;
	void setGuildRelation( char relation );

	bool IsClearRuptureItemExist(int* pIndex = NULL,__int64* pnItemGuid = NULL);
	void SendRelationChangeMsg( unsigned int nGuildId, char relation );
	std::map<int,DWORD>		m_PeaceTimeMap;
	std::map<int,DWORD>		m_InviteTimeMap;

	int		m_nGangRight;

	void								ShowSortArrow(int eType);
	bool		m_bWaitText;

};
extern CUI_ID_FRAME_Alignment s_CUI_ID_FRAME_Alignment;
