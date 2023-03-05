
#pragma once
#include "MeUi//MeUi.h"
#include "UIBase.h"
#include "../ServerList.h"
#include <time.h>
#include "EventTimeTable.h"				//added by zhuomeng.hu		[8/23/2010]

#ifndef ID_FRAME_LOGIN
#define ID_FRAME_LOGIN		"ID_FRAME_LOGIN"
#endif  ID_FRAME_LOGIN
#ifndef ID_TEXT_LoginWait
#define ID_TEXT_LoginWait		"ID_TEXT_LoginWait"
#endif  ID_TEXT_LoginWait
#ifndef ID_TEXT_LoginInfo
#define ID_TEXT_LoginInfo		"ID_TEXT_LoginInfo"
#endif  ID_TEXT_LoginInfo
#ifndef ID_TEXT_Ver
#define ID_TEXT_Ver		"ID_TEXT_Ver"
#endif  ID_TEXT_Ver
#ifndef ID_BUTTON_Register
#define ID_BUTTON_Register		"ID_BUTTON_Register"
#endif  ID_BUTTON_Register
#ifndef ID_BUTTON_OK
#define ID_BUTTON_OK		"ID_BUTTON_OK"
#endif  ID_BUTTON_OK
#ifndef ID_TEXT_SEREV
#define ID_TEXT_SEREV		"ID_TEXT_SEREV"
#endif  ID_TEXT_SEREV
#ifndef ID_PICTURE_LOGO
#define ID_PICTURE_LOGO		"ID_PICTURE_LOGO"
#endif  ID_PICTURE_LOGO
#ifndef ID_BUTTON_Change
#define ID_BUTTON_Change		"ID_BUTTON_Change"
#endif  ID_BUTTON_Change
#ifndef ID_BUTTON_CG
#define ID_BUTTON_CG		"ID_BUTTON_CG"
#endif  ID_BUTTON_CG

//lyh添加游戏前游戏设置
#ifndef ID_BUTTON_GameBeforeSet
#define ID_BUTTON_GameBeforeSet		"ID_BUTTON_GameBeforeSet"
#endif  ID_BUTTON_GameBeforeSet



#ifndef ID_BUTTON_EXIT
#define ID_BUTTON_EXIT		"ID_BUTTON_EXIT"
#endif  ID_BUTTON_EXIT
#ifndef ID_BUTTON_KuaiSuZhuCe
#define ID_BUTTON_KuaiSuZhuCe		"ID_BUTTON_KuaiSuZhuCe"
#endif  ID_BUTTON_KuaiSuZhuCe
#ifndef ID_PICTURE_selectserverback
#define ID_PICTURE_selectserverback		"ID_PICTURE_selectserverback"
#endif  ID_PICTURE_selectserverback
#ifndef ID_CHECKBOX_SAVE
#define ID_CHECKBOX_SAVE		"ID_CHECKBOX_SAVE"
#endif  ID_CHECKBOX_SAVE
#ifndef ID_EDIT_ID
#define ID_EDIT_ID		"ID_EDIT_ID"
#endif  ID_EDIT_ID
#ifndef ID_EDIT_PAS
#define ID_EDIT_PAS		"ID_EDIT_PAS"
#endif  ID_EDIT_PAS
#ifndef ID_PICTURE_ServerListBack
#define ID_PICTURE_ServerListBack		"ID_PICTURE_ServerListBack"
#endif  ID_PICTURE_ServerListBack
#ifndef ID_PICTURE_listback
#define ID_PICTURE_listback		"ID_PICTURE_listback"
#endif  ID_PICTURE_listback
#ifndef ID_PICTURE_serverback
#define ID_PICTURE_serverback		"ID_PICTURE_serverback"
#endif  ID_PICTURE_serverback
#ifndef ID_PICTURE_listback2
#define ID_PICTURE_listback2		"ID_PICTURE_listback2"
#endif  ID_PICTURE_listback2
#ifndef ID_LIST_Serverlist2
#define ID_LIST_Serverlist2		"ID_LIST_Serverlist2"
#endif  ID_LIST_Serverlist2
#ifndef ID_LIST_ServerName2
#define ID_LIST_ServerName2		"ID_LIST_ServerName2"
#endif  ID_LIST_ServerName2
#ifndef ID_LIST_ServerState2
#define ID_LIST_ServerState2		"ID_LIST_ServerState2"
#endif  ID_LIST_ServerState2
#ifndef ID_TEXT_LatterlyServer
#define ID_TEXT_LatterlyServer		"ID_TEXT_LatterlyServer"
#endif  ID_TEXT_LatterlyServer
#ifndef ID_BUTTON_ConfirmSelectServer
#define ID_BUTTON_ConfirmSelectServer		"ID_BUTTON_ConfirmSelectServer"
#endif  ID_BUTTON_ConfirmSelectServer
#ifndef ID_LIST_Serverlist
#define ID_LIST_Serverlist		"ID_LIST_Serverlist"
#endif  ID_LIST_Serverlist
#ifndef ID_PICTURE_Serverback
#define ID_PICTURE_Serverback		"ID_PICTURE_Serverback"
#endif  ID_PICTURE_Serverback
#ifndef ID_PICTURE_ServerWall1
#define ID_PICTURE_ServerWall1		"ID_PICTURE_ServerWall1"
#endif  ID_PICTURE_ServerWall1
#ifndef ID_PICTURE_TitleLeft
#define ID_PICTURE_TitleLeft		"ID_PICTURE_TitleLeft"
#endif  ID_PICTURE_TitleLeft
#ifndef ID_PICTURE_TitleRight
#define ID_PICTURE_TitleRight		"ID_PICTURE_TitleRight"
#endif  ID_PICTURE_TitleRight
#ifndef ID_PICTURE_TitleLeftMiddle
#define ID_PICTURE_TitleLeftMiddle		"ID_PICTURE_TitleLeftMiddle"
#endif  ID_PICTURE_TitleLeftMiddle
#ifndef ID_PICTURE_TitleRightMiddle
#define ID_PICTURE_TitleRightMiddle		"ID_PICTURE_TitleRightMiddle"
#endif  ID_PICTURE_TitleRightMiddle
#ifndef ID_PICTURE_Serverback1
#define ID_PICTURE_Serverback1		"ID_PICTURE_Serverback1"
#endif  ID_PICTURE_Serverback1
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_PICTURE_ServerWall2
#define ID_PICTURE_ServerWall2		"ID_PICTURE_ServerWall2"
#endif  ID_PICTURE_ServerWall2
#ifndef ID_PICTURE_ServerWall3
#define ID_PICTURE_ServerWall3		"ID_PICTURE_ServerWall3"
#endif  ID_PICTURE_ServerWall3
#ifndef ID_BUTTON_Quit
#define ID_BUTTON_Quit		"ID_BUTTON_Quit"
#endif  ID_BUTTON_Quit
#ifndef ID_CHECKBOX_25D
#define ID_CHECKBOX_25D "ID_CHECKBOX_25D"
#endif
#ifndef ID_CHECKBOX_3D
#define ID_CHECKBOX_3D "ID_CHECKBOX_3D"
#endif
#ifndef ID_TEXT_25D
#define ID_TEXT_25D "ID_TEXT_25D"
#endif
#ifndef ID_TEXT_3D
#define ID_TEXT_3D "ID_TEXT_3D"
#endif
#ifndef ID_BUTTON_AreaName
#define ID_BUTTON_AreaName		"ID_BUTTON_AreaName"
#endif  ID_BUTTON_AreaName
#ifndef ID_BUTTON_ServerName
#define ID_BUTTON_ServerName		"ID_BUTTON_ServerName"
#endif  ID_BUTTON_ServerName
#ifndef ID_LIST_AreaName
#define ID_LIST_AreaName		"ID_LIST_AreaName"
#endif  ID_LIST_AreaName
#ifndef ID_LIST_ServerName
#define ID_LIST_ServerName		"ID_LIST_ServerName"
#endif  ID_LIST_ServerName
#ifndef ID_CHECKBOX_ShortCutKey
#define ID_CHECKBOX_ShortCutKey		"ID_CHECKBOX_ShortCutKey"
#endif  ID_CHECKBOX_ShortCutKey
#ifndef ID_PICTURE_ShortCutKeyTip
#define ID_PICTURE_ShortCutKeyTip		"ID_PICTURE_ShortCutKeyTip"
#endif  ID_PICTURE_ShortCutKeyTip
#ifndef ID_BUTTON_Broadcast
#define ID_BUTTON_Broadcast		"ID_BUTTON_Broadcast"
#endif  ID_BUTTON_Broadcast
#ifndef ID_PICTURE_BroadcastTitle
#define ID_PICTURE_BroadcastTitle		"ID_PICTURE_BroadcastTitle"
#endif  ID_PICTURE_BroadcastTitle
#ifndef ID_PICTURE_BroadcastWall
#define ID_PICTURE_BroadcastWall		"ID_PICTURE_BroadcastWall"
#endif  ID_PICTURE_BroadcastWall
#ifndef ID_TEXT_Broadcast
#define ID_TEXT_Broadcast		"ID_TEXT_Broadcast"
#endif  ID_TEXT_Broadcast
#ifndef ID_SCROLLBAR_Broadcast
#define ID_SCROLLBAR_Broadcast		"ID_SCROLLBAR_Broadcast"
#endif  ID_SCROLLBAR_Broadcast
#ifndef ID_LIST_ServerStateOther
#define ID_LIST_ServerStateOther		"ID_LIST_ServerStateOther"
#endif  ID_LIST_ServerStateOther
#ifndef ID_LIST_ServerState
#define ID_LIST_ServerState		"ID_LIST_ServerState"
#endif  ID_LIST_ServerState
#ifndef ID_LIST_ServerStateOther2
#define ID_LIST_ServerStateOther2		"ID_LIST_ServerStateOther2"
#endif  ID_LIST_ServerStateOther2
#ifndef ID_CHECKBOX_PasswordProtect
#define ID_CHECKBOX_PasswordProtect		"ID_CHECKBOX_PasswordProtect"
#endif  ID_CHECKBOX_PasswordProtect
#ifndef ID_TEXT_PasswordProtect
#define ID_TEXT_PasswordProtect		"ID_TEXT_PasswordProtect"
#endif  ID_TEXT_PasswordProtect

// 名字的问题找策划  added by zhuomeng.hu		[8/18/2010]
#ifndef ID_TEXT_Ba
#define ID_TEXT_Ba		"ID_TEXT_Ba"
#endif  ID_TEXT_Ba
#ifndef ID_CHECKBOX_SelectBoard
#define ID_CHECKBOX_SelectBoard		"ID_CHECKBOX_SelectBoard"
#endif  ID_CHECKBOX_SelectBoard
#ifndef ID_CHECKBOX_SelectService
#define ID_CHECKBOX_SelectService		"ID_CHECKBOX_SelectService"
#endif  ID_CHECKBOX_SelectService
#ifndef ID_PICTURE_BgAcrivity
#define ID_PICTURE_BgAcrivity		"ID_PICTURE_BgAcrivity"
#endif  ID_PICTURE_BgAcrivity
#ifndef ID_TEXT_ActivityDesc
#define ID_TEXT_ActivityDesc		"ID_TEXT_ActivityDesc"
#endif  ID_TEXT_ActivityDesc
#ifndef ID_TEXT_ActivityText
#define ID_TEXT_ActivityText		"ID_TEXT_ActivityText"
#endif  ID_TEXT_ActivityText
#ifndef ID_LISTIMG_ActivityIcon
#define ID_LISTIMG_ActivityIcon		"ID_LISTIMG_ActivityIcon"
#endif  ID_LISTIMG_ActivityIcon
#ifndef ID_TEXT_CurrentServerText
#define ID_TEXT_CurrentServerText		"ID_TEXT_CurrentServerText"
#endif  ID_TEXT_CurrentServerText
#ifndef ID_TEXT_CurrentServer
#define ID_TEXT_CurrentServer		"ID_TEXT_CurrentServer"
#endif  ID_TEXT_CurrentServer
#ifndef ID_PICTURE_Logo
#define ID_PICTURE_Logo		"ID_PICTURE_Logo"
#endif  ID_PICTURE_Logo
#ifndef ID_TEXT_RememberText
#define ID_TEXT_RememberText		"ID_TEXT_RememberText"
#endif  ID_TEXT_RememberText
#ifndef ID_TEXT_SoftKeyBoardText
#define ID_TEXT_SoftKeyBoardText		"ID_TEXT_SoftKeyBoardText"
#endif  ID_TEXT_SoftKeyBoardText
#ifndef ID_BUTTON_Pay
#define ID_BUTTON_Pay		"ID_BUTTON_Pay"
#endif  ID_BUTTON_Pay
#ifndef ID_TEXT_ServiceInfo
#define ID_TEXT_ServiceInfo		"ID_TEXT_ServiceInfo"
#endif  ID_TEXT_ServiceInfo
#ifndef ID_TEXT_SaveText
#define ID_TEXT_SaveText		"ID_TEXT_SaveText"
#endif  ID_TEXT_SaveText
#ifndef ID_PICTURE_BgBlackbar
#define ID_PICTURE_BgBlackbar		"ID_PICTURE_BgBlackbar"
#endif  ID_PICTURE_BgBlackbar
#ifndef ID_PICTURE_BgBroadcast
#define ID_PICTURE_BgBroadcast		"ID_PICTURE_BgBroadcast"
#endif	ID_PICTURE_BgBroadcast
#ifndef ID_PICTURE_BroadcastWall3
#define ID_PICTURE_BroadcastWall3		"ID_PICTURE_BroadcastWall3"
#endif  ID_PICTURE_BroadcastWall3
#ifndef ID_PICTURE_BroadcastWall2
#define ID_PICTURE_BroadcastWall2		"ID_PICTURE_BroadcastWall2"
#endif  ID_PICTURE_BroadcastWall2

#ifndef ID_LIST_ZuiJin
#define ID_LIST_ZuiJin		"ID_LIST_ZuiJin"
#endif  ID_LIST_ZuiJin

#ifndef	ID_PICTURE_SAVE
#define ID_PICTURE_SAVE		"ID_PICTURE_SAVE"
#endif	ID_PICTURE_SAVE

#ifndef ID_LIST_ServerPing2
#define ID_LIST_ServerPing2		"ID_LIST_ServerPing2"
#endif  ID_LIST_ServerPing2

#include "UiBase.h"
class CUI_ID_FRAME_LOGIN :public CUIBase
{
public:	
	 CUI_ID_FRAME_LOGIN();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_RegisterOnButtonClick( ControlObject* pSender );
	void ID_EDIT_IDOnEditEnter( ControlObject* pSender, const char* szData );
	void ID_EDIT_PASOnEditEnter( ControlObject* pSender, const char* szData );
	bool ID_BUTTON_OKOnButtonClick( ControlObject* pSender ,bool isForced = false);
	bool ID_BUTTON_CGOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_GameBeforeSetOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_EXITOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ProducerOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FastRegisterOnButtonClick( ControlObject* pSender );
	void ID_CHECKBOX_SAVEOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked );
	void ID_CHECKBOX_25DOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked );
	void ID_CHECKBOX_3DOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked );
	
	bool ID_BUTTON_CANCELOnButtonClick( ControlObject* pSender );
	void ID_LIST_ServerlistOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_Serverlist2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ServerName2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ServerState2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	bool ID_BUTTON_ConfirmSelectServerOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_QuitOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AreaNameOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ServerNameOnButtonClick( ControlObject* pSender );
	void ID_LIST_AreaNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_LIST_ServerNameOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_ShortCutKeyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

    bool ID_BUTTON_BroadcastOnButtonClick( ControlObject* pSender );
    void ID_SCROLLBAR_BroadcastOnScrollBarUpdatePos( ControlObject* pSender, int n );
	void ID_LIST_ServerStateOtherOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
    void ID_LIST_ServerStateOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );
    void ID_LIST_ServerStateOther2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	static bool softKeyboardOnClick( ControlObject* pSender );
	static bool changeServerListOnClick( ControlObject* pSender );
	static bool confirmServerListOnClick( ControlObject* pSender );
	static void frameOnTab();
	static bool frameOnLClick( ControlObject* pSender );
	static void ID_List_Serverlist2OnLDBClick( ControlObject* pSender, ControlList::S_List* pItem );
	static void connectLoginServer( ControlObject* pSender, ControlList::S_List* pItem );
    static void ID_LIST_AreaNameOnLBClick( ControlObject* pSender, ControlList::S_List* pItem );
    static void ID_LIST_ServerNameOnLBClick( ControlObject* pSender, ControlList::S_List* pItem );
    static void ID_LIST_ServerNameOnLDBClick( ControlObject* pSender, ControlList::S_List* pItem );
	void ID_CHECKBOX_PasswordProtectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );

	//added by zhuomeng.hu		[8/18/2010]
	void ID_CHECKBOX_SelectBoardOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	void ID_CHECKBOX_SelectServiceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  );
	bool ID_LISTIMG_ActivityIconOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag,ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ActivityIconOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ActivityIconOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_ActivityIconOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_BUTTON_PayOnButtonClick( ControlObject* pSender );
	void ID_LIST_ServerPing2OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem );

	static void ID_LIST_ZuiJinOnLBClick( ControlObject* pSender, ControlList::S_List* pItem );

	static void ID_LIST_ZuiJinOnLDBClick( ControlObject* pSender, ControlList::S_List* pItem );
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	void SetEnable( bool bEnable );
	void setBtnDisable( bool disable = true );

	ControlFrame* GetFrame() { return m_pID_FRAME_LOGIN; }

	void LoadServerList();
    bool RefreshAreaServerArray( int nBigArea, std::string strArea = "" );  // 根据给出大区和区，刷新大区，区和服务器表格字串，如果strArea为空，则服务器表格为空
	void GetServerInfo(std::string szSeverName );       // 获取所选服务器数据
    void ListShowServerInfo(std::string szServerName = "");  // 刷新服务器列表，并选中szServerName所在行
    void ListShowAreaInfo(std::string szAreaName = "");    // 刷新区列表，并选中szAreaName所在行
	int  GetBigAreaCount();

	void PingServer(const char* szIP, int nPort);

	bool CheckCurServer(); //检查默认选择是否在serverlist里面
	bool CheckIsBad(); //检查当前选择的服务器是否在维护状态

	void SetDefaultServer(std::string defaultserver)	{ m_strServer = defaultserver; }

	inline std::string GetServer()	const		{ return m_strServer;	}
	inline std::string GetArea()	const		{ return m_strArea;	}		// 增加获取大区名的接口		added by zhuomeng.hu		[8/20/2010]

	void SetLoginWaitText(const char* szText);
	void SetLoginWaitShow(bool bShow = true);

	bool		ProcessLog( );

	bool IsLoginWait()							{ return m_bLoginWait; }
	void SetLoginWaitSign(bool bWait = true)	{ m_bLoginWait = bWait; }

	void	SetStartWait();
	clock_t	GetStartWait()						{ return m_tmStartWait; }
	void	SetUserReConnect(bool bReConnect = true)
	{
		m_bUseReConnect = bReConnect;
	}
	bool	GetUserReConnect()					{ return m_bUseReConnect; }

	void	SetControlMode(int nMode)		{ m_nControlMode = nMode;	}
	int		GetControlMode() const			{ return m_nControlMode; 	}
	void	SetSmallMapScale(double fScale)	{ m_fSmallMapScale = fScale;}
	double	GetSmallMapScale() const		{ return m_fSmallMapScale;  }

	void	SetLoginInfo( const char *szText);

	static bool ReturnLogin( const bool bPressYesButton, void *pData );
	static void Edit_ID_ONLBtnDown( ControlObject* pSender, const char* szData );
	static void Edit_Pass_OnLBtnUp( ControlObject* pSender, const char* szData );
	static void Eidt_OnDelByte( ControlObject* pSender, int begin, int end );
	static void CombBox_ShowList();
	static bool connectFailed(const char bPressYesButton, void *pData);
	static bool connectFailed_UserOnline(const char bPressYesButton, void *pData);
	static void OnTab( );
	static bool CancelLogin(const char bPressYesButton, void *pData);
	static bool CancelLoginFromPwdProtect();
	static bool CancelLoginQueue(const char bPressYesButton, void *pData);


	void	ShowConnectedDlg();
	void	SavePath();

	void	setFocusInAccount(bool value)	{ _focusInAccount = value; }
	void	setFocusInPassword(bool value)	{ _focusInPassword = value; }
	bool	getFocusInAccount() const		{ return _focusInAccount; }
	bool	getFocusInPassword() const		{ return _focusInPassword; }
	void	hideSoftKeyboard();

	static void setBtnAndInfoInLoging( bool result );		//登陆的时候设置相应的ｂｔｎ　和　提示信息


	void	showSelectServerListHideOther( bool show = true );
	bool	bShowSelectServerList;
    bool    m_bShowBroadcast;      //当按下Enter时，用于公告界面

	static bool frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed );

	DWORD	m_tmStartLogin;

	void	setStartLogin_Time( DWORD t );

	bool   m_bLogining;
	bool   IsLogining() { return m_bLogining; }

public:
    void FinishEnterPwdProtect( const std::string strPwdProResult );
    HANDLE GetHandle(){return m_Handle;}
    void   SetHandle(HANDLE handle){m_Handle = handle;}
    int    GetPasswordProcLength(){return m_strPasswordProtect.length();}
    char   GetPasswordChar(int nIndex){if(nIndex >m_strPasswordProtect.length()) return 0;return m_strPasswordProtect[nIndex];}

    bool   IsOpenPassWordProc()//{if(!m_pID_FRAME_LOGIN) return false;return m_pID_CHECKBOX_PasswordProtect->IsChecked();}
	{
		return false;
	}

    void  SetPasswordProc(std::string pszPassWord){m_strPasswordProtect = pszPassWord;}
    void  SetGlsid(std::string strGlsid){m_strGlsid = strGlsid; }

    void  AddCharEditPas(int nByte){if(!m_pID_FRAME_LOGIN) return;m_pID_EDIT_PAS->addChar(nByte); }
    void  DelCharEditPas(){if(!m_pID_FRAME_LOGIN) return; m_pID_EDIT_PAS->DelByte(true);}

    std::string GetClientLoginType(){return m_clientLoginType;}
    void  SetClientLoginType(std::string strValue){m_clientLoginType = strValue;}
    int   GetClientLoginLen(){return m_clientLoginType.length();}

    void SetPwdProtect( bool bShow ) { m_bShowPwdProtect = bShow; }
    void SetRegionServerIPPort(const char* szRegion, const char* szServer, const char* szIP, const char* szPort);

    void SetLoginGroupVisable(bool bValue)
	{
		m_GroupBroadcast.SetVisible( bValue );
		//added by zhuomeng.hu		[8/19/2010]
		if( bValue )
		{
			m_GroupKeFu.SetVisible( false );
			m_pID_CHECKBOX_SelectBoard->SetCheck( true );
			m_pID_CHECKBOX_SelectService->SetCheck( false );
		}
	}

    ControlEdit* GetEditPas(){if(!m_pID_FRAME_LOGIN) return NULL; return m_pID_EDIT_PAS;}

    static bool CheckState();
    static bool ProcessResult();

    static std::string	g_gateIp;
    static int			g_gatePort;
    static DWORD		g_dwSwitchGateTime;
    static DWORD		g_dwSwitchGatePeriod;
    static BOOL			g_bSwitchGate;
	static BOOL			g_bEndGetCharacter;		// SwitchGate结束，但收到MsgEndAckChar消息前，置为true
    static int			g_nError;
    static int			g_nLoginLastStatus;
    static int			g_nQueueNumber;
//     static DWORD		m_dwLoginStartTime;
    static bool			m_bShowQueue;
	static bool			m_bNeedAckAgain;//重连标记

    struct SAccountInfo
    {
        enum
        {
            eMaxString = 128
        };
        SAccountInfo()
        {
            memset( this, 0, sizeof(*this) );
        }
        char szID[eMaxString];
        char szPwd[eMaxString];

		char szCryptID[eMaxString];   //加密后帐号密码,作为网络发送用
		char szCryptPWD[eMaxString];
		char szCryptMac[eMaxString];
    };

    struct SAccountPwdProtectInfo
    {
        SAccountPwdProtectInfo()
        {
            strGlsid = "";
            strPwrProtectResult = "";
        }
        SAccountInfo stAccountInfo;
        std::string strGlsid;
        std::string strPwrProtectResult;
    };
private:


	bool	LoadActivityConfig( const char *path );			// 读取活动信息		added by zhuomeng.hu		[8/23/2010]
	void	SetActivity();									// 设置活动信息		added by zhuomeng.hu		[8/23/2010]
	void	setKeyboardCharIndex(int index, bool ch);
	void	updataIndexMap( int begin, int end, bool ch );
	void	clearKeyboardChar();

	SAccountInfo&	getAccountInfo()
	{
		return m_stAccount;
	}



	std::string		m_strPasswordProtect;				// 密保卡信息，取glsid末6位
	std::string		m_strGlsid;							// 用密保卡登录时，暂存glsid
	PeriodTypeContainer     m_activityTypeVec;			//	活动安排	added by zhuomeng.hu		[8/23/2010]
	EventContents			m_activityContentVec;		//	当天活动	added by zhuomeng.hu		[8/23/2010]
   
private:
	SAccountInfo	m_stAccount;
	void ReadSettings();
	void WriteSettings();

    void LoadScene();
	int m_nBigAreaIndex;
    std::string m_strArea;
	std::string m_strServer;
    std::string m_strLastSelectArea;

	bool			m_bLoginWait;
	clock_t			m_tmStartWait;
	clock_t			m_StartSendTime;	//用于计算pin一个server  记录开始发消息的时间

	bool			m_bUseReConnect;
	int				m_nControlMode;	//操作方式 用于 选择界面  在这里读取 保存而已。

	double			m_fSmallMapScale;	//小地图的缩放比例

	bool			_focusInAccount;	//光标在账号输入框
	bool			_focusInPassword;	//光标在密码输入框

	int				IsKeyboardChar;
	bool			m_bIsTileLoaded ;
	bool			bRotFreezed;
	DWORD			oldTime ;
	bool			jumpToNextTime;

    MexAnimCtrl*    m_pCameraModel;
	MexAnimCtrl*    m_pLoginModel;
#ifdef _OLD_LOGIN_
    MexAnimCtrl*    m_pDoorModel;
#endif
	bool			m_bGotRegionServerIpPort;	// 只需要再构造函数里初始化

	std::string		m_strPwdResult;				// 密保卡输入结果
	SAccountPwdProtectInfo m_stAccountPwdProtect;
	bool			m_bShowPwdProtect;

public:
    ControlFrame*	m_pID_FRAME_LOGIN;
    ControlText*	    m_pID_TEXT_Ver;

    // 登入界面
    ControlButton*		m_pID_BUTTON_EXIT;

	// 播放CG按钮
	ControlButton*		m_pID_BUTTON_CG;

	//游戏设置按钮
	ControlButton*		m_pID_BUTTON_GameBeforeSet;


//     ControlButton*		m_pID_BUTTON_madeNameList;
//     ControlButton*     m_pID_BUTTON_KuaiSuZhuCe;
// 
//     ControlButton*	    m_pID_BUTTON_cancel;
//     ControlText*	    m_pID_TEXT_LoginWait;
// 
//     ControlText*		m_pID_TEXT_LoginInfo;
    ControlButton*	m_pID_BUTTON_Register;
    ControlButton*		m_pID_BUTTON_Change;
//     ControlText*		m_pID_TEXT_SEREV;
//     ControlText*		m_pID_TEXT_3D;
//     ControlText*		m_pID_TEXT_25D;
    ControlEdit*		m_pID_EDIT_ID;
    ControlEdit*		m_pID_EDIT_PAS;
    ControlCheckBox*	m_pID_CHECKBOX_SAVE;
	ControlPicture*		m_pID_PICTURE_SAVE;
//     ControlCheckBox*	m_pID_CHECKBOX_3D;
//     ControlCheckBox*	m_pID_CHECKBOX_25D;
    ControlButton*		m_pID_BUTTON_OK;
//     ControlPicture*	m_pID_PICTURE_selectserverback;
//     ControlPicture*	m_pID_PICTURE_LOGO;

    ControlGroup       m_GroupLogin;

    //---------------
    // 选区选服界面
    ControlPicture*	m_pID_PICTURE_ServerListBack;
    ControlList*		m_pID_LIST_ServerList;
//     ControlPicture*	m_pID_PICTURE_listback2;
    ControlList*	    m_pID_LIST_ServerList2;
    ControlList*	    m_pID_LIST_ServerName2;
    ControlList*	    m_pID_LIST_ServerState2;
   // ControlText*	    m_pID_TEXT_LatterlyServer;
    ControlButton*		m_pID_BUTTON_ConfirmSelectServer;
//     ControlPicture*	m_pID_PICTURE_listback;
//     ControlPicture*	m_pID_PICTURE_serverback;

//     ControlPicture*	m_pID_PICTURE_Serverback;
//     ControlPicture*	m_pID_PICTURE_Serverback1;
//     ControlPicture*	m_pID_PICTURE_ServerWall1;
//     ControlPicture*	m_pID_PICTURE_TitleLeft;
//     ControlPicture*	m_pID_PICTURE_TitleRight;
//     ControlPicture*	m_pID_PICTURE_TitleLeftMiddle;
//     ControlPicture*	m_pID_PICTURE_TitleRightMiddle;
//     ControlPicture*	m_pID_PICTURE_ServerWall2;
//     ControlPicture*	m_pID_PICTURE_ServerWall3;
    ControlButton*	    m_pID_BUTTON_Quit;
//     ControlButton*	    m_pID_BUTTON_AreaName;
//     ControlButton*	    m_pID_BUTTON_ServerName;
//     ControlList*	    m_pID_LIST_AreaName;
//     ControlList*	    m_pID_LIST_ServerName;
    ControlCheckBox*	m_pID_CHECKBOX_ShortCutKey;
   // ControlPicture*	m_pID_PICTURE_ShortCutKeyTip;
    ControlList*	    m_pID_LIST_ServerStateOther;
//     ControlList*	m_pID_LIST_ServerState;
//     ControlList*	m_pID_LIST_ServerStateOther2;


    //登入界面Boradcast
    ControlButton*	    m_pID_BUTTON_Broadcast;
  //  ControlPicture*	m_pID_PICTURE_BroadcastTitle;
    ControlPicture*	m_pID_PICTURE_BroadcastWall;
    ControlText*	    m_pID_TEXT_Broadcast;
	ControlList*	    m_pID_LIST_ZuiJin;
   // ControlScrollBar*	m_pID_SCROLLBAR_Broadcast;
 	ControlPicture* m_pID_PICTURE_BgBroadcast;
	ControlPicture*	m_pID_PICTURE_BroadcastWall3;
	ControlPicture*	m_pID_PICTURE_BroadcastWall2;

    ControlGroup        m_GroupAreaServer;
    ControlGroup        m_GroupBroadcast;
	ControlGroup		m_GroupGongGao;		// 公告子组		added by zhuomeng.hu		[8/19/2010]
	ControlGroup		m_GroupKeFu;		// 客服子组		added by zhuomeng.hu		[8/19/2010]
    //-------------------

    ControlRadioGroup  m_RadioGroupViewSelect;

    // 密保卡
//     ControlCheckBox*	m_pID_CHECKBOX_PasswordProtect;
//     ControlText*	m_pID_TEXT_PasswordProtect;


	//added by zhuomeng.hu		[8/18/2010]
	//ControlText*	m_pID_TEXT_Ba;
	ControlCheckBox*	m_pID_CHECKBOX_SelectBoard;
	ControlCheckBox*	m_pID_CHECKBOX_SelectService;
	ControlPicture*	m_pID_PICTURE_BgAcrivity;
	ControlText*	m_pID_TEXT_ActivityDesc;
	ControlText*	m_pID_TEXT_ActivityText;
	ControlListImage*	m_pID_LISTIMG_ActivityIcon;
	ControlText*	m_pID_TEXT_CurrentServerText;
	ControlText*	m_pID_TEXT_CurrentServer;
	ControlPicture*	m_pID_PICTURE_Logo;
	//ControlText*	m_pID_TEXT_RememberText;
	ControlText*	m_pID_TEXT_SoftKeyBoardText;
	ControlButton*	m_pID_BUTTON_Pay;
	ControlText*	m_pID_TEXT_ServiceInfo;
	ControlText*	m_pID_TEXT_SaveText;
	ControlPicture*	m_pID_PICTURE_BgBlackbar;
	ControlList*	m_pID_LIST_ServerPing2;

	class MeCamera  *m_pCamera;

    CServerList m_serverList;
    ControlIconDrag::S_ListImg* m_pSelectItem;
    struct ServerInfo_
    {
		ServerInfo_()
		{
			nPing = -1;
		}

        std::string    strName;
        std::string    strStatus;
        DWORD          dwStatusColor;
        std::string    strCommon;
		std::string	   strIpAddr;

		int unStatus;
		int unIsNew;
		int unIsRecommend;
		int unIsVehemence;
		int nPing;
    };

    std::vector<std::string> strBigAreas;
    std::vector<std::string> strAreas;
    std::vector<ServerInfo_> vctServerInfo;

    std :: map< std::string, INT > m_mapServerInfo;
    std :: map< std::string, DWORD > m_mapServerColor; //Name Color
    std :: map< std::string, std::string > m_mapServerNote; //Name Color

    std::string	m_strIp;
    DWORD		m_dwPort;

    std::string m_clientLoginType;

    HANDLE		m_Handle;

	std::string	m_strHttp;

	DWORD	dwStartTime;

public:
	bool EncodeAccountInfo(SAccountInfo* pAccountInfo);
	//bool DecodeAccountInfo(SAccountInfo* pAccountInfo);

	enum EStatus //服务器拥堵状态
	{
		ES_Good,
		ES_Crowded,
		ES_Busy,
		ES_Full,
		ES_Bad,
		ES_Max,
	};

	enum EPing //Ping网络状态
	{
		EP_Green,
		EP_Yellow,
		EP_Red,
		EP_Max,
	};

	enum EServer //新服，推荐服，热门服
	{
		ESV_New,
		ESV_Recommend,
		ESV_Vehemence,
		ESV_Null,
		ESV_Max,
	};
};

extern CUI_ID_FRAME_LOGIN s_CUI_ID_FRAME_LOGIN;
