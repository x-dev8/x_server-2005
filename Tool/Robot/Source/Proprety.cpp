/////////////////////////////////////////////////////////////////////////////
// CAllControlsSheet

#include "Proprety.h"

IMPLEMENT_DYNAMIC(ControlsSheet, CPropertySheet)

// ControlsSheet::ControlsSheet(UINT nIDCaption,GmCommandRobot* Bot, CWnd* pParentWnd, UINT iSelectPage)
// 	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage),_Bot(Bot)
// {
// 	AddControlPages();
// 
// 	// TODO :: Add the pages for the rest of the controls here.
// }

ControlsSheet::ControlsSheet(LPCTSTR pszCaption,GmCommandRobot* Bot, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage),_Bot(Bot)
{
	AddControlPages();
}

ControlsSheet::~ControlsSheet()
{
    if (NULL != _Bot)
    {
        _Bot = NULL;
    }
}

void ControlsSheet::AddControlPages()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_psh.dwFlags |= PSP_USEHICON;
	m_psh.hIcon = m_hIcon;
	m_psh.dwFlags |= PSH_NOAPPLYNOW;    // Lose the Apply Now button
	m_psh.dwFlags &= ~PSH_HASHELP;  // Lose the Help button

    // ÃÌº”“≥√Ê    
    _DownPage.SetBot(_Bot);
    AddPage(&_DownPage);
    _BroadcastPage.SetBot(_Bot);
    AddPage(&_BroadcastPage);
    _ChangeMapRatePage.SetBot(_Bot);
    AddPage(&_ChangeMapRatePage);
    _KickPlayerPage.SetBot(_Bot);
    AddPage(&_KickPlayerPage);
    _AddPointsPage.SetBot(_Bot);
    AddPage(&_AddPointsPage);
    _ReloadTradShopPage.SetBot(_Bot);
    AddPage(&_ReloadTradShopPage);
    _CreateCharacterPage.SetBot(_Bot);
    AddPage(&_CreateCharacterPage);
    _ChangePlayerName.SetBot(_Bot);
    //AddPage(&_ChangePlayerName);
    _ReqAddItemPage.SetBot(_Bot);
    AddPage(&_ReqAddItemPage);
}

BEGIN_MESSAGE_MAP(ControlsSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CAllControlsSheet)
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAllControlsSheet message handlers

BOOL ControlsSheet::OnInitDialog()
{
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
// 	ASSERT((IDD_ABOUTBOX & 0xFFF0) == IDD_ABOUTBOX);
// 	ASSERT(IDD_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDD_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			//pSysMenu->AppendMenu(MF_STRING, IDD_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
    
	return CPropertySheet::OnInitDialog();
}
HCURSOR ControlsSheet::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void ControlsSheet::SetPlatformBot(GmCommandRobot* bot)
{
    if (NULL != bot)
    {
        return;
    }
    _Bot = bot;
}