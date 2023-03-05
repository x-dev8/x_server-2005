// NewDlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NewDlg.h"
#include "NewDlgDlg.h"
#include "SkinImgMgr.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern SkinImgMgr  ImgMgr  ;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CNewDlgDlg dialog




CNewDlgDlg::CNewDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewDlgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	image=NULL;
}
void CNewDlgDlg::LoadXML(CString filename)
{
	if( !m_TiXmlDoc.LoadFile(filename) )
	{
		return;
	}
	const char* szValue = NULL;

	m_TiElemRoot	= m_TiXmlDoc.FirstChildElement("root");
	if(m_TiElemRoot)
	{
		TiXmlElement* imgbg = m_TiElemRoot->FirstChildElement("dlgsize");
		if( imgbg )
		{

			TiXmlElement* imagerect = imgbg->FirstChildElement("rect");
			if( imagerect )
			{
				szValue = imagerect->Attribute("value");
				CRect rc;
				if( szValue )
				{
					sscanf( szValue, "%d, %d, %d, %d", &rc.left, &rc.top, &rc.right, &rc.bottom );
					this->MoveWindow(rc);
				}
			}

		}

	}
}
void CNewDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNewDlgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CNewDlgDlg message handlers

BOOL CNewDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	image=ImgMgr.AddImg(".\\UpData\\launcher.png");
	CWindowDC   m_dc(NULL); 
	SetWindowPos(&CWnd::wndTopMost,(m_dc.GetDeviceCaps(HORZRES)-1024)/2,(m_dc.GetDeviceCaps(VERTRES)-768)/2,1024,768, SWP_NOZORDER | SWP_NOMOVE);
	LoadXML(_T(".\\UpData\\bk.xml"));
	m_dwFlags = 0;
	GetWindowRect(rcWindowRaw);

	CRect rcWindow;                  
	GetWindowRect(rcWindow);
	rcWindow.DeflateRect(10,20,-10,-10);

	pChildWnd->MoveWindow(&rcWindow);

	SetWindowText("Launcher");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNewDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNewDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNewDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CNewDlgDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	//创建子窗体
	pChildWnd=new CNewBackDlg(this);
	pChildWnd->Create(IDD_NEW_BACK_DLG);
	pChildWnd->ShowWindow(SW_SHOW);
	// TODO:  Add your specialized creation code here

	return 0;
}

void CNewDlgDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if ( m_dwFlags & DRAGGING )
	{
		RECT rect;
		GetWindowRect( &rect );

		rect.left += point.x - m_pntMouse.x;
		rect.top += point.y - m_pntMouse.y;

		SetWindowPos( NULL, rect.left, rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
		GetWindowRect(rcWindowRaw);

	}
	CDialog::OnMouseMove(nFlags, point);
}

void CNewDlgDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnLButtonDown(nFlags, point);
	ReleaseCapture ();
	SendMessage (WM_NCLBUTTONDOWN, HTCAPTION, 0);

	CDialog::OnLButtonDown(nFlags, point);
}

BOOL CNewDlgDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rtClient;
	GetClientRect(rtClient);

	CDC * dc =new CDC;
	CBitmap * bmp=new CBitmap;
	dc->CreateCompatibleDC(pDC);
	bmp->CreateCompatibleBitmap(pDC,rtClient.Width(),rtClient.Height());
	dc->SelectObject(bmp);

	Graphics graph(dc->m_hDC);
	if(image)
		graph.DrawImage (image,0, 0,rtClient.Width(),rtClient.Height());

	DWORD dwExStyle=GetWindowLong(m_hWnd,GWL_EXSTYLE);
	if((dwExStyle&0x80000)!=0x80000)
		SetWindowLong(m_hWnd,GWL_EXSTYLE,dwExStyle^0x80000);

	BLENDFUNCTION m_Blend; 
	m_Blend.BlendOp=0; 
	m_Blend.BlendFlags=0; 
	m_Blend.AlphaFormat=1;
	m_Blend.SourceConstantAlpha=255;//AC_SRC_ALPHA

	RECT rct;
	GetWindowRect(&rct);
	POINT ptWinPos={rct.left,rct.top};
	SIZE sizeWindow={rtClient.Width(),rtClient.Height()};
	POINT ptSrc={0,0};
	BOOL bRet=FALSE;
	bRet= UpdateLayeredWindow( pDC,&ptWinPos,
		&sizeWindow,dc,&ptSrc,0,&m_Blend,2);
	dc->DeleteDC();
	bmp->DeleteObject();
	delete dc;
	delete bmp;
	return true;
}

void CNewDlgDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if ( m_dwFlags & DRAGGING )
	{
		m_dwFlags &= ~DRAGGING;
		ReleaseCapture();
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CNewDlgDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);
	CRect rcWindow;                  
	GetWindowRect(rcWindow);
	rcWindow.DeflateRect(10,20,-10,-10);
	pChildWnd->MoveWindow(&rcWindow);
	// TODO: Add your message handler code here
}
