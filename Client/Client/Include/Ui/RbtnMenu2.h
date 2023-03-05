/********************************************************************
Created by UIEditor.exe
FileName: E:\Work\HeroRuntime\Client\UI\RbtnMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#ifndef ID_FRAME_RBTNMENU
#define ID_FRAME_RBTNMENU		"ID_FRAME_RBTNMENU"
#endif  ID_FRAME_RBTNMENU
#ifndef ID_BUTTON_TERM
#define ID_BUTTON_TERM		"ID_BUTTON_TERM"
#endif  ID_BUTTON_TERM
#ifndef ID_BUTTON_EXCHANGE
#define ID_BUTTON_EXCHANGE		"ID_BUTTON_EXCHANGE"
#endif  ID_BUTTON_EXCHANGE
#ifndef ID_BUTTON_FRD
#define ID_BUTTON_FRD		"ID_BUTTON_FRD"
#endif  ID_BUTTON_FRD
#ifndef ID_BUTTON_FOLLOWME
#define ID_BUTTON_FOLLOWME		"ID_BUTTON_FOLLOWME"
#endif  ID_BUTTON_FOLLOWME
#ifndef ID_BUTTON_KICKOUT
#define ID_BUTTON_KICKOUT		"ID_BUTTON_KICKOUT"
#endif  ID_BUTTON_KICKOUT
#ifndef ID_BUTTON_Private
#define ID_BUTTON_Private	"ID_BUTTON_Private"
#endif ID_BUTTON_Private
#ifndef ID_BUTTON_SEEK
#define ID_BUTTON_SEEK	"ID_BUTTON_SEEK"
#endif ID_BUTTON_SEEK
#ifndef ID_BUTTON_DUEL
#define ID_BUTTON_DUEL	"ID_BUTTON_DUEL"
#endif ID_BUTTON_DUEL
#ifndef ID_BUTTON_UpgradeTeam
#define ID_BUTTON_UpgradeTeam	"ID_BUTTON_UpgradeTeam"
#endif ID_BUTTON_UpgradeTeam
#ifndef ID_BUTTON_GUILD
#define ID_BUTTON_GUILD	 "ID_BUTTON_GUILD"
#endif ID_BUTTON_GUILD
#ifndef ID_BUTTON_Tuan
#define ID_BUTTON_Tuan	 "ID_BUTTON_Tuan"
#endif ID_BUTTON_Tuan

#ifndef ID_BUTTON_BLACKFRIEND
#define ID_BUTTON_BLACKFRIEND "ID_BUTTON_Heimingdan"
#endif  ID_BUTTON_BLACKFRIEND


class CUI_ID_FRAME_RBTNMENU
{
	// SGuildMember
public:
	CUI_ID_FRAME_RBTNMENU();
public:	
	ControlFrame*	m_pID_FRAME_RBTNMENU;
	ControlButton*	m_pID_BUTTON_TERM;		  // 邀请组队
	ControlButton*	m_pID_BUTTON_Tuan;
	ControlButton*	m_pID_BUTTON_EXCHANGE;	  // 交易
	ControlButton*	m_pID_BUTTON_FRD;		  // 加为好友
	ControlButton*	m_pID_BUTTON_FOLLOWME;	  // 跟随 -- 现在没有
	ControlButton*	m_pID_BUTTON_KICKOUT;	  // 踢除
	ControlButton*	m_pID_BUTTON_Private;	  // 私聊
	ControlButton*	m_pID_BUTTON_SEEK;		  // 察看
    ControlButton*	m_pID_BUTTON_DUEL;		  // 切磋
	ControlButton*	m_pID_BUTTON_UpgradeTeam; // 提升队长
    ControlButton*	m_pID_BUTTON_GUILD;       // 邀请入会
    ControlButton*	m_pID_BUTTON_BLACKFRIEND; // 加为黑名单

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_TERMOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_EXCHANGEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FRDOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FOLLOWMEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_KICKOUTOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PrivateOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SeekOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_DuelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UpgradeTeamOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_GUILDOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_BLACKFRIENDOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable, 
public:

		bool bGroupClick = false,
		int index = -1,
		bool showNormal = true,
		BOOL bChat = FALSE );			// 设置是否可视
	void SetPrivateName( const char* szName)		{ m_szName = szName; }
	const char* GetPrivateName() const				{ return m_szName.c_str(); 	}
	void SetPlayerID( int nID);
	int	 GetPlayerID() const						{ return m_szID; }

	VOID SetPos(INT x, INT y);
	static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

	std::string m_szName;	//这个用于暂时保存 私聊 玩家的名字 (暂时以为着只有电击“悄悄话”在有用)
	int			m_szID;		//保存玩家id用于添加好友 等操作

	std::vector<ControlButton*>		_vecBtn;

	int			_nGroupID;	//存储队友id

	void SetGroupID(int nID)		{ _nGroupID = nID;}
};
extern CUI_ID_FRAME_RBTNMENU s_CUI_ID_FRAME_RBTNMENU;