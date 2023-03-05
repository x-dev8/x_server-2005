/********************************************************************
	Created by UIEditor.exe
	FileName: D:\Tj\Client\UI\FriendDlg.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include <time.h>
#include <map>
#include "MsgBase.h"
#include "core/Name.h"
#include "XmlStringLanguage.h"
#include "RelationConfig.h"
#include "GlobalDef.h"
#include "RelationDefine.h"
#include "Common.h"
#include "Me3d/Global.h"
#ifndef ID_FRAME_Friend
#define ID_FRAME_Friend		"ID_FRAME_Friend"
#endif  ID_FRAME_Friend
#ifndef ID_LIST_FriendInfo
#define ID_LIST_FriendInfo		"ID_LIST_FriendInfo"
#endif  ID_LIST_FriendInfo
#ifndef ID_LIST_FriendStar
#define ID_LIST_FriendStar		"ID_LIST_FriendStar"
#endif  ID_LIST_FriendStar

// #ifndef ID_BUTTON_DelFriend
// #define ID_BUTTON_DelFriend		"ID_BUTTON_DelFriend"
// #endif  ID_BUTTON_DelFriend

#ifndef ID_BUTTON_AddFriend
#define ID_BUTTON_AddFriend	"ID_BUTTON_AddFriend"
#endif ID_BUTTON_AddFriend
// #ifndef ID_BUTTON_chat
// #define ID_BUTTON_chat	"ID_BUTTON_chat"
// #endif ID_BUTTON_chat
// #ifndef ID_BUTTON_team
// #define ID_BUTTON_team	"ID_BUTTON_team"
// #endif ID_BUTTON_team
// #ifndef ID_BUTTON_MoveHei
// #define ID_BUTTON_MoveHei	"ID_BUTTON_MoveHei"
// #endif ID_BUTTON_MoveHei
#ifndef ID_CHECKBOX_XiongDi
#define ID_CHECKBOX_XiongDi	"ID_CHECKBOX_XiongDi"
#endif ID_CHECKBOX_XiongDi
#ifndef ID_CHECKBOX_ShiTu
#define ID_CHECKBOX_ShiTu	"ID_CHECKBOX_ShiTu"
#endif ID_CHECKBOX_ShiTu
#ifndef ID_CHECKBOX_HeiMingDan
#define ID_CHECKBOX_HeiMingDan	"ID_CHECKBOX_HeiMingDan"
#endif ID_CHECKBOX_HeiMingDan
#ifndef ID_CHECKBOX_LinShiHaoYou
#define ID_CHECKBOX_LinShiHaoYou		"ID_CHECKBOX_LinShiHaoYou"
#endif  ID_CHECKBOX_LinShiHaoYou

#ifndef ID_BUTTON_Search
#define ID_BUTTON_Search "ID_BUTTON_Search"
#endif  ID_BUTTON_Search
#ifndef ID_CHECKBOX_HaoYou
#define ID_CHECKBOX_HaoYou	"ID_CHECKBOX_HaoYou"
#endif ID_CHECKBOX_HaoYou


#ifndef ID_CHECKBOX_Chouren
#define ID_CHECKBOX_Chouren		"ID_CHECKBOX_Chouren"
#endif  ID_CHECKBOX_Chouren

#ifndef ID_BUTTON_Remove
#define ID_BUTTON_Remove		"ID_BUTTON_Remove"
#endif  ID_BUTTON_Remove

#ifndef ID_BUTTON_Adding
#define ID_BUTTON_Adding		"ID_BUTTON_Adding"
#endif  ID_BUTTON_Adding
#ifndef ID_BUTTON_Rename
#define ID_BUTTON_Rename		"ID_BUTTON_Rename"
#endif  ID_BUTTON_Rename
#ifndef ID_PICTURE_Head
#define ID_PICTURE_Head		"ID_PICTURE_Head"
#endif  ID_PICTURE_Head
#ifndef ID_TEXT_PeopleName
#define ID_TEXT_PeopleName		"ID_TEXT_PeopleName"
#endif  ID_TEXT_PeopleName
#ifndef ID_TEXT_Wait
#define ID_TEXT_Wait		"ID_TEXT_Wait"
#endif  ID_TEXT_Wait

#ifndef ID_BUTTON_Addheimingdan
#define ID_BUTTON_Addheimingdan  "ID_BUTTON_Addheimingdan"
#endif
#ifndef ID_BUTTON_Mood
#define ID_BUTTON_Mood		"ID_BUTTON_Mood"
#endif  ID_BUTTON_Mood
#ifndef ID_TEXT_PeopleMood
#define ID_TEXT_PeopleMood		"ID_TEXT_PeopleMood"
#endif  ID_TEXT_PeopleMood
#ifndef ID_BUTTON_AddingFriend
#define ID_BUTTON_AddingFriend		"ID_BUTTON_AddingFriend"
#endif  ID_BUTTON_AddingFriend

#ifndef ID_LIST_FriendHead
#define ID_LIST_FriendHead		"ID_LIST_FriendHead"
#endif  ID_LIST_FriendHead

#ifndef ID_TEXT_CloseIconID
#define ID_TEXT_CloseIconID		"ID_TEXT_CloseIconID"
#endif  ID_TEXT_CloseIconID
#ifndef ID_TEXT_OpenIconID
#define ID_TEXT_OpenIconID		"ID_TEXT_OpenIconID"
#endif  ID_TEXT_OpenIconID

#ifndef ID_BUTTON_AddingClass
#define ID_BUTTON_AddingClass		"ID_BUTTON_AddingClass"
#endif  ID_BUTTON_AddingClass



#include "UiBase.h"
class CUI_ID_FRAME_Friend :public CUIBase
{
	// SGuildMember
private:	
	ControlFrame*	m_pID_FRAME_Friend;
	ControlList*	m_pID_LIST_FriendInfo;
	ControlButton*	m_pID_BUTTON_AddFriend;//需要输入名字
	// 	 ControlButton*	m_pID_BUTTON_DelFriend;

	ControlButton*	_pSendInfo;		//发送信息
	// 	ControlButton*	_pRequestTeam;	//邀请组队
	// 	ControlButton*	_pMoveHei;		//移动到黑名单

	ControlCheckBox*	_pCheckFriend;		//好友列表
	ControlCheckBox*	_pCheckBlackList;	//黑名单列表
	ControlCheckBox*	_pCheckTeachers;	//师徒列表
	//ControlCheckBox*	_pCheckBrother;		//兄弟列表
	ControlCheckBox*	m_pID_CHECKBOX_LinShiHaoYou;

	ControlCheckBox*    _pCheckChouren;     //仇人人选

	ControlButton*	m_pID_BUTTON_Adding;

	ControlButton*	m_pID_BUTTON_Rename;
	ControlPicture*	m_pID_PICTURE_Head;
	ControlText*	m_pID_TEXT_PeopleName;
	ControlText*	m_pID_TEXT_Wait;

	// 	 ControlList*	m_pID_LIST_GuanXi;
	ControlList*	m_pID_LIST_FriendStar;

	ControlText*	m_pID_TEXT_PeopleMood;

	ControlButton*	m_pID_BUTTON_Mood;
	ControlButton* m_pID_BUTTON_Addheimingdan; // 添加到黑名单,需要输入名字
	ControlButton* m_pID_BUTTON_Remove;
	ControlButton*	m_pID_BUTTON_AddingFriend;
	ControlButton*	m_pID_BUTTON_Search;

	ControlList*	m_pID_LIST_FriendHead;

	//这两个控件仅仅是为了保存controlList收起、展开时用的图标的ID
	ControlText*	m_pID_TEXT_CloseIconID;
	ControlText*	m_pID_TEXT_OpenIconID;

	ControlButton*	m_pID_BUTTON_AddingClass;
	 	
public:


	 CUI_ID_FRAME_Friend();

	 ~CUI_ID_FRAME_Friend();


	

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	void ID_LIST_FriendInfoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_AddFriendOnButtonClick( ControlObject* pSender );
// 	bool ID_BUTTON_DelFriendOnButtonClick( ControlObject* pSender );
 	bool ID_BUTTON_AddheimingdanOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AddingOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AddingFriendOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RenameOnButtonClick( ControlObject* pSender );

	static bool ID_BUTTON_RemoveOnButtonClick( ControlObject* pSender );


// 	bool ID_BUTTON_chatOnButtonClick( ControlObject* pSender );
 	static bool ID_BUTTON_teamOnButtonClick( ControlObject* pSender );
	static bool ID_BUTTON_moveHeiOnButtonClick( ControlObject* pSender );
	static void Friend_CollapseCallBackFun(  ControlObject* pSender, ControlList::S_List* pItem );
	static void Friend_ShowTipCallBackFun(  ControlObject* pSender, ControlList::S_List* pItem );

	static void ID_List_OnRBClick( ControlObject* pSender, ControlList::S_List* pItem );
	static void ID_List_OnLDBClick( ControlObject* pSender, ControlList::S_List* pItem );

	static void ID_CheckBox_Friend( ControlObject* pSender, bool* pbChecked );
	static void ID_CheckBox_Blacklist( ControlObject* pSender, bool* pbChecked );
	static void ID_CheckBox_Brothers( ControlObject* pSender, bool* pbChecked );
	static void ID_CheckBox_Teachers( ControlObject* pSender, bool* pbChecked );
	void ID_CHECKBOX_LinShiHaoYouOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_BUTTON_SearchOnButtonClick( ControlObject* pSender );
	static void ID_CheckBox_Chouren( ControlObject* pSender, bool* pbChecked );//zjj add [2008.6.23]
	bool ID_BUTTON_MoodOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_AddingClassOnButtonClick( ControlObject* pSender );

	void RefreshButtonStatus(void);
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:
	static const	int m_nMaxMalePortrait = 5;
	static const	int m_nMaxFamalePortrait = 5;
	static const	int m_nFriendStar = 5;

public:


	void RefreshUI();

	ControlFrame* GetFrame() { return m_pID_FRAME_Friend; }
	static bool sendReqDelGroup( const char bPressYesButton, void *pData );
	static bool sendReqDelFriend( const char bPressYesButton, void *pData );
	static bool sendReqMoveBlackList( const char bPressYesButton, void *pData );//zjj add[2008.8.11]

	void NeedRefresh	(){ m_bNeedRefresh = true; } 
	//----------------
	DWORD GetShowType(){ return showTpye; }

 	void SetTextWait();

	void					ChangeSignature(const char* pName);
	void					ChangeFriendGroupName(const char* pName);
	void					AddFriendGroup(const char* pName);
	void					ChangeFriendTag(const char* pName);

	void					ChangeFriendToGroup(const char* pName);

	void					GetSexProfessionString( RelationDataToClient &friendData, std::string &strSex, string &strProfession );

	const char*				GetPortraitGifFromName(const char* pPlayerName);

	bool IsShowTypeFriend(void);
	void Refresh();

protected:
	//调整面板，类似以前的outlook右面板效果
	void AdaptButtons( int idx );

private:
// 	static void UpdateScrollBar( OUT ControlObject* pSender, int n );
	void RefreshFriendStar();

	void setDelName(const char* name)	{ _delName = name; }
	const char* getDelName()			{ return _delName.c_str(); }

	void sendUpdataFrdInfo();
	void showFriendList();
	void showTempFriendList();
	void showBrotherList();
	void showTeacherList();
	void showBlackList();
	void showChourenList();//zjj add
	void showMarriageList();
	void SetTipForFriend(RelationDataToClient *pFriendData,ControlList::S_List&stItem);
	void SetTipForOther(RelationDataToClient *pFriendData,ControlList::S_List&stItem);
	void AddToList(RelationDataToClient *pFriendData,ControlList::S_List&stItem,DWORD col);
	const char*				GetPortraitGif(RelationDataToClient *friendData);
	bool		m_bNeedRefresh;

	std::string		_delName;

	DWORD		showTpye;

	clock_t			_beginForSendMsgUpdateInfo;
	ControlGroup	m_FriendCtrlGroup;		// 好友控件组
	ControlGroup	m_TempFriendCtrlGroup;		// 临时好友控件组
	ControlGroup	m_MasterCtrlGroup;		// 师徒控件组
	ControlGroup	m_EnemyCtrlGroup;		// 仇人控件组
	ControlGroup	m_BlackListCtrlGroup;	// 黑名单控件组

	ControlTabGroup m_CtrlTabGroup;


};
extern CUI_ID_FRAME_Friend s_CUI_ID_FRAME_Friend;
