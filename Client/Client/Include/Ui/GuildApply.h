/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildApply.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MsgBase.h"
#include "UIBase.h"
#include "GuildDefine.h"
#include "PlayerRole.h"
#ifndef ID_FRAME_GuildApply
#define ID_FRAME_GuildApply		"ID_FRAME_GuildApply"
#endif  ID_FRAME_GuildApply
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_PageUp
#define ID_BUTTON_PageUp		"ID_BUTTON_PageUp"
#endif  ID_BUTTON_PageUp
#ifndef ID_TEXT_GuildName
#define ID_TEXT_GuildName		"ID_TEXT_GuildName"
#endif  ID_TEXT_GuildName
#ifndef ID_TEXT_Level
#define ID_TEXT_Level		"ID_TEXT_Level"
#endif  ID_TEXT_Level
#ifndef ID_TEXT_Member
#define ID_TEXT_Member		"ID_TEXT_Member"
#endif  ID_TEXT_Member
#ifndef ID_TEXT_GuildMaster
#define ID_TEXT_GuildMaster		"ID_TEXT_GuildMaster"
#endif  ID_TEXT_GuildMaster
#ifndef ID_TEXT_Announcement
#define ID_TEXT_Announcement		"ID_TEXT_Announcement"
#endif  ID_TEXT_Announcement
#ifndef ID_TEXT_CreateDate
#define ID_TEXT_CreateDate		"ID_TEXT_CreateDate"
#endif  ID_TEXT_CreateDate
#ifndef ID_BUTTON_HELP
#define ID_BUTTON_HELP		"ID_BUTTON_HELP"
#endif  ID_BUTTON_HELP
#ifndef ID_BUTTON_PageDown
#define ID_BUTTON_PageDown		"ID_BUTTON_PageDown"
#endif  ID_BUTTON_PageDown
#ifndef ID_BUTTON_Apply
#define ID_BUTTON_Apply		"ID_BUTTON_Apply"
#endif  ID_BUTTON_Apply
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_LIST_Level
#define ID_LIST_Level		"ID_LIST_Level"
#endif  ID_LIST_Level
#ifndef ID_LIST_CDR
#define ID_LIST_CDR		"ID_LIST_CDR"
#endif  ID_LIST_CDR
#ifndef ID_LIST_Amount
#define ID_LIST_Amount		"ID_LIST_Amount"
#endif  ID_LIST_Amount
#ifndef ID_TEXT_111
#define ID_TEXT_111		"ID_TEXT_111"
#endif  ID_TEXT_111
#ifndef ID_TEXT_222
#define ID_TEXT_222		"ID_TEXT_222"
#endif  ID_TEXT_222
#ifndef ID_TEXT_333
#define ID_TEXT_333		"ID_TEXT_333"
#endif  ID_TEXT_333
#ifndef ID_TEXT_444
#define ID_TEXT_444		"ID_TEXT_444"
#endif  ID_TEXT_444
#ifndef ID_EDIT_4918
#define ID_EDIT_4918		"ID_EDIT_4918"
#endif  ID_EDIT_4918
#ifndef ID_BUTTON_Search
#define ID_BUTTON_Search		"ID_BUTTON_Search"
#endif  ID_BUTTON_Search
#ifndef ID_LIST_GuildList
#define ID_LIST_GuildList		"ID_LIST_GuildList"
#endif  ID_LIST_GuildList

class CUI_ID_FRAME_GuildApply: public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_GuildApply();
	 ControlFrame*	m_pID_FRAME_GuildApply;
	 ControlButton*	m_pID_BUTTON_CLOSE;
	 ControlButton*	m_pID_BUTTON_PageUp;
	 ControlText*	m_pID_TEXT_GuildName;
	 ControlText*	m_pID_TEXT_Level;
	 ControlText*	m_pID_TEXT_Member;
	 ControlText*	m_pID_TEXT_GuildMaster;
	 ControlText*	m_pID_TEXT_Announcement;
	 ControlText*	m_pID_TEXT_CreateDate;
	 ControlButton*	m_pID_BUTTON_HELP;
	 ControlButton*	m_pID_BUTTON_PageDown;
	 ControlButton*	m_pID_BUTTON_Apply;
	 ControlButton*	m_pID_BUTTON_Cancel;
	 ControlText*	m_pID_TEXT_Page;
	 ControlList*	m_pID_LIST_Level;
	 ControlList*	m_pID_LIST_CDR;
	 ControlList*	m_pID_LIST_Amount;
	 ControlText*	m_pID_TEXT_111;
	 ControlText*	m_pID_TEXT_222;
	 ControlText*	m_pID_TEXT_333;
	 ControlText*	m_pID_TEXT_444;
	 ControlEdit*	m_pID_EDIT_4918;
	 ControlButton*	m_pID_BUTTON_Search;
	 ControlList*	m_pID_LIST_GuildList;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PageUpOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HELPOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PageDownOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ApplyOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	void ID_LIST_LevelOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_CDROnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_AmountOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_EDIT_4918OnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_SearchOnButtonClick( ControlObject* pSender );
	void ID_LIST_GuildListOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	void OnMsgQueryGuildData(Msg*);

	void SetNeedRefresh(bool);

	bool EditInputIsVisable();
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual void InitializeAtEnterWorld();
	virtual bool IsHoldInMemory() const { return true; }

	void ShowApplyingMessage();

	void OnInit();
	void ShowGuildInfoByPage(int Page = 1);
	void AddToList(const char* m_GuildName,const char *level,const char* num,const char*Mastername);
	void QueryGuildData(int nGuildId);
private:
	std::vector<CGuildInfo*> m_vctGuild;//当前的结果的公会
	int						 m_NowPage;
	static long int m_sCurrentTime;//发送申请的记录时间
};
extern CUI_ID_FRAME_GuildApply s_CUI_ID_FRAME_GuildApply;
