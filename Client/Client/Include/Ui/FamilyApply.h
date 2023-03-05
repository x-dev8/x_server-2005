/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Turbo\MEUI\3.14-3.19\家族\FamilyApply.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_FamilyApply
#define ID_FRAME_FamilyApply		"ID_FRAME_FamilyApply"
#endif  ID_FRAME_FamilyApply
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_TEXT_Announcement
#define ID_TEXT_Announcement		"ID_TEXT_Announcement"
#endif  ID_TEXT_Announcement
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_Apply
#define ID_BUTTON_Apply		"ID_BUTTON_Apply"
#endif  ID_BUTTON_Apply
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_LIST_GuildList
#define ID_LIST_GuildList		"ID_LIST_GuildList"
#endif  ID_LIST_GuildList
#ifndef ID_LIST_Level
#define ID_LIST_Level		"ID_LIST_Level"
#endif  ID_LIST_Level
#ifndef ID_LIST_CDR
#define ID_LIST_CDR		"ID_LIST_CDR"
#endif  ID_LIST_CDR
#ifndef ID_LIST_Amount
#define ID_LIST_Amount		"ID_LIST_Amount"
#endif  ID_LIST_Amount
#ifndef ID_TEXT_ZuZhang
#define ID_TEXT_ZuZhang		"ID_TEXT_ZuZhang"
#endif  ID_TEXT_ZuZhang
#ifndef ID_TEXT_ZhiYe
#define ID_TEXT_ZhiYe		"ID_TEXT_ZhiYe"
#endif  ID_TEXT_ZhiYe
#ifndef ID_TEXT_DengJi
#define ID_TEXT_DengJi		"ID_TEXT_DengJi"
#endif  ID_TEXT_DengJi

#ifndef ID_EDIT_GJZ
#define ID_EDIT_GJZ		"ID_EDIT_GJZ"
#endif  ID_EDIT_GJZ
#ifndef ID_BUTTON_Search
#define ID_BUTTON_Search		"ID_BUTTON_Search"
#endif  ID_BUTTON_Search

#ifndef ID_LIST_Name
#define ID_LIST_Name		"ID_LIST_Name"
#endif  ID_LIST_Name

#include "UIBase.h"

#include "FamilyDefine.h"
#include "FamilyMessage.h"

class CUI_ID_FRAME_FamilyApply : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_FamilyApply();
	 ControlFrame*	m_pID_FRAME_FamilyApply;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlText*	m_pID_TEXT_Announcement;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_Apply;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlList*	m_pID_LIST_GuildList;
	 ControlList*	m_pID_LIST_Level;
	 ControlList*	m_pID_LIST_CDR;
	 ControlList*	m_pID_LIST_Amount;
	 ControlText*	m_pID_TEXT_ZuZhang;
	 ControlText*	m_pID_TEXT_ZhiYe;
	 ControlText*	m_pID_TEXT_DengJi;
	 ControlEdit*	m_pID_EDIT_GJZ;
	 ControlButton*	m_pID_BUTTON_Search;
	 ControlList*	m_pID_LIST_Name;


public:
	bool    EditInputIsVisable();

 //游戏逻辑相关
public:
	void InitialListValues();	//初始化列表的值
	void InitialSearchResult();
	void ClearValues();
	void AddToList( const char* familyName, const char* level, const char* prosperity, const char* memberCount, DWORD clr );

	void CheckList();

	void OnMsgQueryFamilyInfoAck( Msg *pMsg );

public:	
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ApplyOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	void ID_LIST_GuildListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_LevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_CDROnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_AmountOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_EDIT_GJZOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_SearchOnButtonClick( ControlObject* pSender );
	void ID_LIST_NameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

public:
	static void ListScrollPosChanged( OUT ControlObject* pSender, int n );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();			// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
private:	
	typedef	std::vector<FamilyDefine::FamilySimpleInfo> FamilySimpleInfoSet_t;
	typedef FamilySimpleInfoSet_t::iterator	FamilySimpleInfoSetIt_t;

	typedef std::map<unsigned int, MsgQueryFamilyInfoAck> QueryFamilyInfoAck_t;
	typedef QueryFamilyInfoAck_t::iterator				QueryFamilyInfoAckIt_t;

	FamilySimpleInfoSet_t		m_vecSimpleInfoSet;		//这个数据时跟界面列表对应的
	FamilySimpleInfoSet_t		m_vecSearchResultSet;

	QueryFamilyInfoAck_t		m_mapFamilyInfoAck;

	bool						m_bIsSreachResult;
};
extern CUI_ID_FRAME_FamilyApply s_CUI_ID_FRAME_FamilyApply;
