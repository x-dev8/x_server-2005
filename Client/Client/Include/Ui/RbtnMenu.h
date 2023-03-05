/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\RbtnMenu.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "md5.h"

#ifndef ID_BUTTON_AddHei
#define ID_BUTTON_AddHei		"ID_BUTTON_AddHei"
#endif  ID_BUTTON_AddHei
#ifndef ID_BUTTON_UnLock
#define ID_BUTTON_UnLock		"ID_BUTTON_UnLock"
#endif  ID_BUTTON_UnLock
#ifndef ID_BUTTON_Lock
#define ID_BUTTON_Lock		"ID_BUTTON_Lock"
#endif  ID_BUTTON_Lock
#ifndef ID_FRAME_RBTNMENU
#define ID_FRAME_RBTNMENU		"ID_FRAME_RBTNMENU"
#endif  ID_FRAME_RBTNMENU
#ifndef ID_BUTTON_TERM
#define ID_BUTTON_TERM		"ID_BUTTON_TERM"
#endif  ID_BUTTON_TERM
#ifndef ID_BUTTON_TERM2
#define ID_BUTTON_TERM2		"ID_BUTTON_TERM2"
#endif  ID_BUTTON_TERM2
#ifndef ID_BUTTON_EXCHANGE
#define ID_BUTTON_EXCHANGE		"ID_BUTTON_EXCHANGE"
#endif  ID_BUTTON_EXCHANGE
#ifndef ID_BUTTON_FRD
#define ID_BUTTON_FRD		"ID_BUTTON_FRD"
#endif  ID_BUTTON_FRD
#ifndef ID_BUTTON_KICKOUT
#define ID_BUTTON_KICKOUT		"ID_BUTTON_KICKOUT"
#endif  ID_BUTTON_KICKOUT
#ifndef ID_BUTTON_Private
#define ID_BUTTON_Private		"ID_BUTTON_Private"
#endif  ID_BUTTON_Private
#ifndef ID_BUTTON_SEEK
#define ID_BUTTON_SEEK		"ID_BUTTON_SEEK"
#endif  ID_BUTTON_SEEK
#ifndef ID_BUTTON_DUEL
#define ID_BUTTON_DUEL		"ID_BUTTON_DUEL"
#endif  ID_BUTTON_DUEL
#ifndef ID_BUTTON_UpgradeTeam
#define ID_BUTTON_UpgradeTeam		"ID_BUTTON_UpgradeTeam"
#endif  ID_BUTTON_UpgradeTeam
#ifndef ID_BUTTON_GUILD
#define ID_BUTTON_GUILD		"ID_BUTTON_GUILD"
#endif  ID_BUTTON_GUILD
#ifndef ID_BUTTON_Tuan
#define ID_BUTTON_Tuan		"ID_BUTTON_Tuan"
#endif  ID_BUTTON_Tuan
#ifndef ID_BUTTON_Heimingdan
#define ID_BUTTON_Heimingdan		"ID_BUTTON_Heimingdan"
#endif  ID_BUTTON_Heimingdan
#ifndef ID_BUTTON_FOLLOWME
#define ID_BUTTON_FOLLOWME		"ID_BUTTON_FOLLOWME"
#endif  ID_BUTTON_FOLLOWME
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_BUTTON_Waigua
#define ID_BUTTON_Waigua		"ID_BUTTON_Waigua"
#endif  ID_BUTTON_Waigua
#ifndef ID_BUTTON_Fuzhi
#define ID_BUTTON_Fuzhi		"ID_BUTTON_Fuzhi"
#endif  ID_BUTTON_Fuzhi
#ifndef ID_BUTTON_MessageChat
#define ID_BUTTON_MessageChat "ID_BUTTON_MessageChat"
#endif  ID_BUTTON_MessageChat
#ifndef ID_BUTTON_Gang
#define ID_BUTTON_Gang		"ID_BUTTON_Gang"
#endif  ID_BUTTON_Gang
#ifndef ID_BUTTON_Hug
#define ID_BUTTON_Hug		"ID_BUTTON_Hug"
#endif  ID_BUTTON_Hug
#ifndef ID_BUTTON_Pet
#define ID_BUTTON_Pet		"ID_BUTTON_Pet"
#endif  ID_BUTTON_Pet
#ifndef ID_BUTTON_ChooseStudent
#define ID_BUTTON_ChooseStudent		"ID_BUTTON_ChooseStudent"
#endif  ID_BUTTON_ChooseStudent
#ifndef ID_BUTTON_ChooseTeacher
#define ID_BUTTON_ChooseTeacher		"ID_BUTTON_ChooseTeacher"
#endif  ID_BUTTON_ChooseTeacher
#ifndef ID_BUTTON_GivePresent
#define ID_BUTTON_GivePresent		"ID_BUTTON_GivePresent"
#endif  ID_BUTTON_GivePresent
#ifndef ID_BUTTON_ST
#define ID_BUTTON_ST		"ID_BUTTON_ST"
#endif  ID_BUTTON_ST
#ifndef ID_PICTURE_Link
#define ID_PICTURE_Link		"ID_PICTURE_Link"
#endif  ID_PICTURE_Link
#ifndef ID_BUTTON_Report
#define ID_BUTTON_Report		"ID_BUTTON_Report"
#endif  ID_BUTTON_Report
#ifndef ID_BUTTON_Teach
#define ID_BUTTON_Teach		"ID_BUTTON_Teach"
#endif  ID_BUTTON_Teach
#ifndef ID_PICTURE_Expand
#define ID_PICTURE_Expand		"ID_PICTURE_Expand"
#endif  ID_PICTURE_Expand
#ifndef ID_BUTTON_FRDClass
#define ID_BUTTON_FRDClass		"ID_BUTTON_FRDClass"
#endif  ID_BUTTON_FRDClass
#ifndef ID_PICTURE_1
#define ID_PICTURE_1		"ID_PICTURE_1"
#endif  ID_PICTURE_1
#ifndef ID_BUTTON_Remark
#define ID_BUTTON_Remark		"ID_BUTTON_Remark"
#endif  ID_BUTTON_Remark
#ifndef ID_BUTTON_DelFriend
#define ID_BUTTON_DelFriend		"ID_BUTTON_DelFriend"
#endif  ID_BUTTON_DelFriend

#ifndef ID_BUTTON_SQQC
#define ID_BUTTON_SQQC		"ID_BUTTON_SQQC"
#endif  ID_BUTTON_SQQC
#ifndef ID_BUTTON_YQQC
#define ID_BUTTON_YQQC		"ID_BUTTON_YQQC"
#endif  ID_BUTTON_YQQC
#ifndef ID_BUTTON_AddFamily
#define ID_BUTTON_AddFamily		"ID_BUTTON_AddFamily"
#endif  ID_BUTTON_AddFamily
#ifndef ID_BUTTON_AddVendetta
#define ID_BUTTON_AddVendetta		"ID_BUTTON_AddVendetta"
#endif  ID_BUTTON_AddVendetta

class CPlayer;

#include "UiBase.h"
class CUI_ID_FRAME_RBTNMENU :public CUIBase
{
	// Member
public:
	enum ShowType
	{
		eShow_normal,
		eShow_FriendFriend,
		eShow_FriendOther,
		eShow_Gang,
	};
public:	
	CUI_ID_FRAME_RBTNMENU();

private:
	void ResetMembers();
	ControlFrame*	m_pID_FRAME_RBTNMENU;
	ControlButton*	m_pID_BUTTON_TERM;
	ControlButton*	m_pID_BUTTON_TERM2;
	ControlButton*	m_pID_BUTTON_EXCHANGE;
	ControlButton*	m_pID_BUTTON_FRD;
	ControlButton*	m_pID_BUTTON_KICKOUT;
	ControlButton*	m_pID_BUTTON_Private;
	ControlButton*	m_pID_BUTTON_SEEK;
	ControlButton*	m_pID_BUTTON_DUEL;
	ControlButton*	m_pID_BUTTON_UpgradeTeam;
	ControlButton*	m_pID_BUTTON_GUILD;
	ControlButton*	m_pID_BUTTON_Tuan;
	ControlButton*	m_pID_BUTTON_FOLLOWME;
	/*ControlButton*	m_pID_BUTTON_Waigua;*/
	ControlButton*	m_pID_BUTTON_Fuzhi;
 	ControlButton*	m_pID_BUTTON_MessageChat;
	ControlButton*	m_pID_BUTTON_Lock;
	ControlButton*	m_pID_BUTTON_UnLock;
	ControlButton*	m_pID_BUTTON_AddHei;
	ControlButton*	m_pID_BUTTON_FRDClass;
	ControlPicture*	m_pID_PICTURE_1;
	ControlButton*	m_pID_BUTTON_Remark;
	ControlButton*	m_pID_BUTTON_DelFriend;

	ControlButton*	m_pID_BUTTON_SQQC;
	ControlButton*	m_pID_BUTTON_YQQC;
	ControlButton*	m_pID_BUTTON_AddFamily;

	ControlButton*	m_pID_BUTTON_AddVendetta;

public:
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_TERMOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TERM2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_EXCHANGEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FRDOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_KICKOUTOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PrivateOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SEEKOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DUELOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UpgradeTeamOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GUILDOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TuanOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LockOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_UnLockOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AddHeiOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FOLLOWMEOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_WaiguaOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FuzhiOnButtonClick( ControlObject* pSender );
 	bool ID_BUTTON_MessageChatOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FRDClassOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RemarkOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DelFriendOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_SQQCOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_YQQCOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AddFamilyOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AddVendettaOnButtonClick( ControlObject* pSender );

	void SetVisable( const bool bVisable, bool isOnline = true );			
	static void UpdateTeamButtonStatus( ControlButton* pTeamButton,CPlayer* pTagetPlayer,bool isOnline, bool bTargetInBlackList ,bool bTeamMember = false);
	static bool InviteTeam(std::string& strPlayerName);
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable, bool isOnline = true );			

public:
	ControlFrame* GetFrame() { return m_pID_FRAME_RBTNMENU; }
	void SetPos(INT x, INT y);
	void SetDBID(int nID)						{ m_dwDBID = nID;}
	void SetPrivateName( const char* szName);
	void SetShowType(ShowType ekey) { m_eShowType = ekey;}

private:
	void SetLockAndUnLockState();

private:
	const char* GetPrivateName() const				{ return m_szName.c_str(); 	}

	std::string m_szName;	//这个用于保存 玩家的名字 
	int			m_dwDBID;	//存储队友id
	ShowType m_eShowType;
};
extern CUI_ID_FRAME_RBTNMENU s_CUI_ID_FRAME_RBTNMENU;
