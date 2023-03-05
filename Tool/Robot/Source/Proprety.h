#ifndef __ControlsSheet__
#define __ControlsSheet__
#include "stdafx.h"
#include "GmCommandRobot.h"
#include "Platform_ShutdownServerPage.h"
#include "Platform_BroadcastPage.h"
#include "Platform_ChangeMapRatePage.h"
#include "Platfrom_KickPlayerPage.h"
#include "Platform_AddPointsPage.h"
#include "Platform_ReLoadTradeShopPage.h"
#include "Platform_CreateCharacterPage.h"
#include "Platform_ChangePlayerNamePage.h"
#include "PlatForm_ReqAddItemPage.h"

class ControlsSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(ControlsSheet)

// Construction
public:
	/*ControlsSheet(UINT nIDCaption, GmCommandRobot *Bot,CWnd* pParentWnd = NULL, UINT iSelectPage = 0);*/
	ControlsSheet(LPCTSTR pszCaption,GmCommandRobot *Bot, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

protected:
	void AddControlPages(void); // 添加页面

// Attributes
public:
    // todo:自定义页面
    Platform_ShutdownServer _DownPage;
    Platform_Broadcast      _BroadcastPage;
    Platform_ChangeMapRate  _ChangeMapRatePage;
    Platfrom_KickPlayer     _KickPlayerPage;
    Platform_AddPoints      _AddPointsPage;
    Platform_ReLoadTradeShop _ReloadTradShopPage;
    Platform_CreateCharacter _CreateCharacterPage;
    Platform_ChangePlayerName _ChangePlayerName;
    PlatForm_ReqAddItem     _ReqAddItemPage;
// Operations
public:
    void SetPlatformBot(GmCommandRobot* bot);
private:
    GmCommandRobot* _Bot;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAllControlsSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ControlsSheet();
	virtual BOOL OnInitDialog();

	// Generated message map functions
protected:

	HICON m_hIcon;

	//{{AFX_MSG(CAllControlsSheet)
	afx_msg HCURSOR OnQueryDragIcon();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif