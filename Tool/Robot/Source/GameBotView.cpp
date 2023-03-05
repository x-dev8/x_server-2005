// GameBotView.cpp : CGameBotView 类的实现
//

#pragma warning( push )
#pragma warning( disable : 4100 )
#pragma warning( disable : 4005 )


#include "stdafx.h"
#include "GameBot.h"
#include "GameBotDoc.h"
#include "GameBotView.h"
#include "LoginInfo.h"
#include "ManInfo.h"
#include "PackInfo.h"
#include "SkillInfo.h"
#include "CommondDialog.h"
#include "MatrixBot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameBotView
CGameBotView* GettheMainView()
{
    CMDIFrameWnd *pFrame = 
        (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
    if (NULL == pFrame)
    {
        return NULL;
    }
    CMDIChildWnd *pChild = 
        (CMDIChildWnd *) pFrame->GetActiveFrame();
    if (NULL == pChild)
    {
        return NULL;
    }
    CGameBotView *pView = ( CGameBotView *) pChild->GetActiveView();
    return pView;
}

IMPLEMENT_DYNCREATE(CGameBotView, CFormView)

BEGIN_MESSAGE_MAP(CGameBotView, CFormView)
    ON_WM_SIZE()
    ON_NOTIFY(NM_CLICK, IDC_LIST_BOT, &CGameBotView::OnNMClickListBot)
    ON_NOTIFY(NM_RCLICK, IDC_LIST_BOT, &CGameBotView::OnNMRclickListBot)
	ON_COMMAND(IDC_RELOGIN, &CGameBotView::OnReLogin)
	ON_WM_PAINT()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CGameBotView::OnTcnSelchangeTabInfo)
	ON_BN_CLICKED(IDC_BUTTON1, &CGameBotView::OnBnClickedButtonSendChat)
	ON_BN_CLICKED(IDC_RADIO1, &CGameBotView::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CGameBotView::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CGameBotView::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CGameBotView::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CGameBotView::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CGameBotView::OnBnClickedRadio6)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_BOT, &CGameBotView::OnLvnItemchangedListBot)// 左键点击消息 [10/8/2010 pengbo.yang]
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_BOT, &CGameBotView::OnDBCheckListBotCommond)
	ON_COMMAND(IDC_ALLLOGIN, &CGameBotView::OnAlllogin)
    ON_COMMAND(ID_32788, &CGameBotView::OnFlyBackInHell)
    ON_COMMAND(ID_ALLBOT_OUTLINE, &CGameBotView::OnAllBotOutline)
    ON_COMMAND(ID_SELECTED_OUTLINE, &CGameBotView::OnSelectedOutline)
END_MESSAGE_MAP()

// CGameBotView 构造/析构

CGameBotView::CGameBotView()
	: CFormView(CGameBotView::IDD)
	, m_RadioType(0),m_pManInfo(NULL),m_pPackInfo(NULL)
    ,m_pSkillInfo(NULL),m_pMapInfo(NULL),m_nInfoIndex(-1)
    ,m_nBotID(-1),_TempSendPackNum(0),_TempRecvPackNum(0)
    ,_TempSendPackSize(0),_TempRecvPackSize(0)
{
	// TODO: 在此处添加构造代码

	m_vecBaseInfo.clear();
	m_vecDialog.clear();
}

CGameBotView::~CGameBotView()
{
	vector<BaseInfo*>::iterator iter;
	vector<BaseInfo*>::iterator begin = m_vecBaseInfo.begin();
	vector<BaseInfo*>::iterator end = m_vecBaseInfo.end();
	for (iter = begin; iter != end; ++iter)
	{
		delete (*iter);
	}

	if (m_pMapInfo != NULL)
	{
		delete m_pMapInfo;
		m_pMapInfo = NULL;
	}

	m_vecBaseInfo.clear();
	m_vecDialog.clear();
}

void CGameBotView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BOT, m_ctlBotList);
	// DDX_Control(pDX, IDC_TREE_INFO, m_treeBotInfo);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_EDIT1, m_SystemList);
	DDX_Control(pDX, IDC_EDIT2, m_ChatList);
	DDX_Control(pDX, IDC_STATIC_SYSTEM, m_staticSystem);
	DDX_Control(pDX, IDC_STATIC_CHAT, m_staticChat);
	DDX_Control(pDX, IDC_EDIT3, m_editContent);
	DDX_Control(pDX, IDC_BUTTON1, m_buttonSend);
	DDX_Control(pDX, IDC_STATIC_CHAT2, m_staticChat2);
	DDX_Control(pDX, IDC_RADIO1, m_Radio1);
	DDX_Control(pDX, IDC_RADIO2, m_Radio2);
	DDX_Control(pDX, IDC_RADIO3, m_Radio3);
	DDX_Control(pDX, IDC_RADIO4, m_Radio4);
	DDX_Control(pDX, IDC_RADIO5, m_Radio5);
	DDX_Control(pDX, IDC_RADIO6, m_Radio6);

	DDX_Control(pDX, IDC_EDIT36, m_editTotalMsgCount);
	DDX_Control(pDX, IDC_EDIT37, m_editTotalPosPackCount);
	DDX_Control(pDX, IDC_EDIT38, m_editTotalPosMsgCount);
	DDX_Control(pDX, IDC_EDIT39, m_editTotalEnemyPackCount);
	DDX_Control(pDX, IDC_EDIT41, m_editBotTotalMsgCount);
	DDX_Control(pDX, IDC_EDIT42, m_editBotPosPackCount);
	DDX_Control(pDX, IDC_EDIT43, m_editBotPosMsgCount);
	DDX_Control(pDX, IDC_EDIT44, m_editBotEnemyPackCount);
	DDX_Control(pDX, IDC_EDIT45, m_editBotEnemyMsgCount);
	DDX_Control(pDX, IDC_EDIT40, m_editTotalEnemyMsgCount);
	DDX_Control(pDX, IDC_EDIT51, m_editPerSendCount);
	DDX_Control(pDX, IDC_EDIT52, m_editPerSendSize);
	DDX_Control(pDX, IDC_EDIT53, m_editPerRecvCount);
	DDX_Control(pDX, IDC_EDIT54, m_editPerRecvSize);
}

BOOL CGameBotView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CGameBotView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

    m_frmAdd.Create(IDD_ADD_FORM, this);

#ifdef HIDE_BOT_INFO
	m_xMsgInfo.Create(IDD_DIALOG_MSGINFO, this);
#endif // HIDE_BOT_INFO

	  //ListCtrl
    DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_ctlBotList.SetExtendedStyle(dwStyle);

	RECT rect;
	m_ctlBotList.GetClientRect(&rect);
	int nWidth = rect.right - rect.left;

	int iIndex = 0;

    m_ctlBotList.InsertColumn(iIndex++, "类型", 0, (9 * nWidth / 100));
	m_ctlBotList.InsertColumn(iIndex++, "ID", 0, (9 * nWidth / 100));
    m_ctlBotList.InsertColumn(iIndex++, "帐号", 0, (15 * nWidth / 100));
    m_ctlBotList.InsertColumn(iIndex++, "动作", 0, (22 * nWidth / 100));
	m_ctlBotList.InsertColumn(iIndex++, "状态", 0, (20 * nWidth / 100));
	m_ctlBotList.InsertColumn(iIndex++, "地图", 0, (25 * nWidth / 100));

	//给模拟客户端预留第一行
	m_ctlBotList.InsertItem(0, "");

	static const char* s_szItem[] = {"基本属性", "背包", "技能", "环境", "好友", "队伍", "公会", "任务", "商城", "其他",};
	static const int nCount = sizeof(s_szItem) / sizeof(char*);

	for (int i = 0; i < nCount; ++i)
	{
		m_Tab.InsertItem(i, s_szItem[i]);
	}

	InitTabChildDialog();

	OnSize(0,0,0);
}

// CGameBotView 诊断

#ifdef _DEBUG
void CGameBotView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGameBotView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CGameBotDoc* CGameBotView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameBotDoc)));
	return (CGameBotDoc*)m_pDocument;
}
#endif //_DEBUG


// CGameBotView 消息处理程序

void CGameBotView::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);

	static const int nPos = 450;

    // TODO: 在此处添加消息处理程序代码
    RECT rect, rectAdd;
    GetWindowRect(&rect);
	
    //AddFrm
    if(m_frmAdd.m_hWnd != NULL)
    {  
		m_frmAdd.GetWindowRect(&rectAdd);     
   //     m_frmAdd.SetWindowPos(NULL, nPos + 5, (rect.bottom-rect.top) - (rectAdd.bottom-rectAdd.top), 0, 0, SWP_NOSIZE);
        m_frmAdd.GetWindowRect(&rectAdd);   
		m_frmAdd.ShowWindow(SW_SHOW);       
    }

#ifdef HIDE_BOT_INFO
	if(m_xMsgInfo.m_hWnd != NULL)
	{  
		m_xMsgInfo.GetWindowRect(&rectAdd);     
		m_xMsgInfo.SetWindowPos(NULL, nPos + 5, 5, 0, 0, SWP_NOSIZE);
		m_xMsgInfo.ShowWindow(SW_SHOW);     

		m_xMsgInfo.InitInformation();
	}
#endif // HIDE_BOT_INFO

	//TabCtrl
	if (m_Tab.m_hWnd != NULL && m_frmAdd.m_hWnd != NULL)
	{
		m_Tab.SetWindowPos(NULL, nPos + 5, 5, 600, (rect.bottom-rect.top)-(rectAdd.bottom-rectAdd.top) - 5, SWP_SHOWWINDOW);
			
	}

    //ListCtrl
    if(m_ctlBotList.m_hWnd != NULL)
    {
        m_ctlBotList.SetWindowPos(NULL, 0, 0, nPos, rect.bottom - rect.top, SWP_NOMOVE);
    }

	int nPos2 = nPos + 5 + 600 + 5;
	int nWidth = rect.right - rect.left - nPos2 - 10;


	int off=145;
	if (m_staticSystem.m_hWnd != NULL)
	{
		m_staticSystem.SetWindowPos(NULL, nPos2, 150-off, nWidth, 15, SWP_SHOWWINDOW);
	}

	if (m_SystemList.m_hWnd != NULL)
	{
		m_SystemList.SetWindowPos(NULL, nPos2, 170-off, nWidth, 90, SWP_SHOWWINDOW);
	}

	if (m_staticChat.m_hWnd != NULL)
	{
		m_staticChat.SetWindowPos(NULL, nPos2, 265-off, nWidth, 15, SWP_SHOWWINDOW);
	}

	if (m_ChatList.m_hWnd != NULL)
	{
		m_ChatList.SetWindowPos(NULL, nPos2, 280-off, nWidth, 90, SWP_SHOWWINDOW);
	}

	if (m_staticChat2.m_hWnd != NULL)
	{
		m_staticChat2.SetWindowPos(NULL, nPos2, 380-off, nWidth, 100, SWP_SHOWWINDOW);
	}

	//////////////////////////////////////
	static CButton* s_pButton[] = {&m_Radio1, &m_Radio2, &m_Radio3, &m_Radio4, &m_Radio5, &m_Radio6, };
	static const int nCount = sizeof(s_pButton) / sizeof(CButton*);
	int nPosY = 480 + 15-off;
	if (m_Radio1.m_hWnd != NULL)
	{
		for (int i = 0; i < nCount; ++i)
		{
			s_pButton[i]->SetWindowPos(NULL, nPos2 + 10, nPosY, 60, 25, SWP_SHOWWINDOW);

			nPosY += 25;
		}

		if (m_RadioType == 0)
		{
			m_Radio1.SetCheck(TRUE);
		}
	}
	

	if (m_editContent.m_hWnd != NULL)
	{
		m_editContent.SetWindowPos(NULL, nPos2 + 70, 510-off, nWidth - 80, 20, SWP_SHOWWINDOW);
	}

	if (m_buttonSend.m_hWnd != NULL)
	{
		m_buttonSend.SetWindowPos(NULL, nPos2 + 70, 530-off, 70, 22, SWP_SHOWWINDOW);
	}
	
#ifdef HIDE_BOT_INFO
	if(m_Tab.m_hWnd != NULL)
	{
		m_Tab.ShowWindow(SW_HIDE);
		m_staticSystem.ShowWindow(SW_HIDE);
		m_SystemList.ShowWindow(SW_HIDE);
		m_staticChat.ShowWindow(SW_HIDE);
		m_ChatList.ShowWindow(SW_HIDE);
		m_editContent.ShowWindow(SW_HIDE);
		m_buttonSend.ShowWindow(SW_HIDE);

		m_staticChat2.ShowWindow(SW_HIDE);		
		for (int i = 0; i < nCount; ++i)
		{
			s_pButton[i]->ShowWindow(SW_HIDE);
		}		
	}
#endif // HIDE_BOT_INFO
}

void CGameBotView::OnNMClickListBot(NMHDR *pNMHDR, LRESULT *pResult)
{
    // delete [10/8/2010 pengbo.yang]
    // TODO: 在此添加控件通知处理程序代码
   // CString strSelect;
   // //取得选中的个数   
   // UINT uSelectedCount = m_ctlBotList.GetSelectedCount();   
   // int nItem = -1;   
   // if(uSelectedCount > 0)   
   // {   
   //     //取得第一个被选中的项   
   //     nItem = m_ctlBotList.GetNextItem(nItem, LVNI_SELECTED);    
   //     if(nItem != -1)
   //     {
			//CString strID = m_ctlBotList.GetItemText(nItem, 1);

			//if (!strID.IsEmpty())
			//{
			//	int nID = atoi(strID.GetBuffer());

			//	theApp.gBotApplication.SetCurSel(nID);
			//	//theApp.ShowBotInfo(nID);

			//	m_nBotID = nID;
   //             m_xMsgInfo.ResetChartMap();
			//}			
   //     }
   // }   

    // add [10/8/2010 pengbo.yang]
    int nIndex = -1;
    LPNMITEMACTIVATE lpNMITEMACTIVATE = (LPNMITEMACTIVATE)pNMHDR;
    if (lpNMITEMACTIVATE != NULL)
    {
        nIndex = lpNMITEMACTIVATE->iItem;
    }

    if (nIndex < 0)
    { return;}

    CString strID = m_ctlBotList.GetItemText(nIndex, 1);//得到ID
    if (strID.IsEmpty())
    { return;}

    int id = atoi(strID);
    GMsgShowRobot msg;
    msg.robotId = id; // 设置消息的成员robotId
    theApp.gBotApplication.PushMessage( &msg );

    *pResult = 0;
}

BOOL CGameBotView::DestroyWindow()
{
    // TODO: 在此添加专用代码和/或调用基类
    return CFormView::DestroyWindow();
}

void CGameBotView::OnNMRclickListBot(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: 在此添加控件通知处理程序代码
    //取得选中的个数   
    UINT uSelectedCount = m_ctlBotList.GetSelectedCount();   
    int nItem = -1;   
    if(uSelectedCount > 0)   
    {//取得第一个被选中的项   
        nItem = m_ctlBotList.GetNextItem(nItem, LVNI_SELECTED);    
        if(nItem != -1)
        {
            CMenu menu;
            CPoint pt;
            GetCursorPos(&pt);
            menu.LoadMenu(IDR_MENU_POP);
            menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);		
        }
    }  

    *pResult = 0;
}


void CGameBotView::OnReLogin()
{
	// TODO: Add your command handler code here
	POSITION pos = m_ctlBotList.GetFirstSelectedItemPosition();

	if (pos != NULL)
	{
		int nIndex = m_ctlBotList.GetNextSelectedItem(pos);
		if (nIndex != -1)
		{
			CString strID = m_ctlBotList.GetItemText(nIndex, 1);
			if (!strID.IsEmpty())
			{
				int nID = atoi(strID.GetBuffer());
				BaseRobot *pBot = theApp.gBotApplication.GetBot(nID);
				if(pBot != NULL && pBot->GetBotState() != State_Play)
				{
					pBot->SetBotState(e_state_no_confirm);
				}
			}	
		}
	}	
}


void CGameBotView::InitTabChildDialog()
{
	RECT rect;

	rect.top = 26;
	rect.left = 457;
	rect.right = rect.left + 594;
	rect.bottom = 710;

	//////////////////////////////////////////////////////////////////
	//人物属性
	if (m_pManInfo == NULL)
	{
		m_pManInfo = new ManInfo();
		if (m_pManInfo != NULL)
		{
			m_pManInfo->Create(IDD_DIALOG_MANINFO, this);	
			m_pManInfo->MoveWindow(&rect);	
			m_pManInfo->ShowWindow(SW_SHOW);

#ifdef HIDE_BOT_INFO
			m_pManInfo->ShowWindow(SW_HIDE);
#endif
			m_vecDialog.push_back(m_pManInfo);
			m_vecBaseInfo.push_back(m_pManInfo);

			const int iIndex = 0;
			m_nInfoIndex = iIndex;
			m_Tab.SetCurSel(iIndex);
		}

	}
	
	///////////////////////////////////////////////////////////////////
	//背包信息
	if (m_pPackInfo == NULL)
	{
		m_pPackInfo = new PackInfo();
		if (m_pPackInfo != NULL)
		{
			m_pPackInfo->Create(IDD_DIALOG_PACKINFO, this);
			m_pPackInfo->MoveWindow(&rect);
			
			m_vecDialog.push_back(m_pPackInfo);
			m_vecBaseInfo.push_back(m_pPackInfo);			
		}
	}

	///////////////////////////////////////////////////////////////////////
	//技能信息
	if (m_pSkillInfo == NULL)
	{
		m_pSkillInfo = new SkillInfo();
		if (m_pSkillInfo != NULL)
		{
			m_pSkillInfo->Create(IDD_DIALOG_SKILL, this);
			m_pSkillInfo->MoveWindow(&rect);

			m_vecDialog.push_back(m_pSkillInfo);
			m_vecBaseInfo.push_back(m_pSkillInfo);
		}
	}
	///////////////////////////////////////////////////////////////////

	vector<BaseInfo*>::iterator iter;
	vector<BaseInfo*>::iterator begin = m_vecBaseInfo.begin();
	vector<BaseInfo*>::iterator end = m_vecBaseInfo.end();
	for (iter = begin; iter != end; ++iter)
	{
		(*iter)->InitInformation();
	}
}


void CGameBotView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CFormView::OnPaint() for painting messages.
}

void CGameBotView::OnTcnSelchangeTabInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nIndex = m_Tab.GetCurSel();

	if (nIndex != m_nInfoIndex && nIndex < m_vecDialog.size())
	{
		m_vecDialog[nIndex]->ShowWindow(SW_SHOW);
		m_vecDialog[m_nInfoIndex]->ShowWindow(SW_HIDE);

		m_nInfoIndex = nIndex;
	}
}

void CGameBotView::UpdateSystemMessageCount(BaseRobot* pBot)
{
	if (pBot == NULL || m_ChatList.m_hWnd == NULL)
	{
		return;
	}

	if (HQ_TimeGetTime() - pBot->ShowPackTime >= 1000)
	{
		pBot->ShowPackTime = HQ_TimeGetTime();
		_TempSendPackNum = pBot->m_SendPackNum;
		_TempRecvPackNum = pBot->m_RecvPackNum;
		pBot->m_SendPackNum = 0;
		pBot->m_RecvPackNum = 0;
		_TempSendPackSize = pBot->m_SendPackSize;
		_TempRecvPackSize = pBot->m_RecvPackSize;
		pBot->m_SendPackSize = 0;
		pBot->m_RecvPackSize = 0;

		theApp.SetText(m_editPerSendCount, "%d", _TempSendPackNum);
		theApp.SetText(m_editPerSendSize, "%d", _TempSendPackSize);
		theApp.SetText(m_editPerRecvCount, "%d", _TempRecvPackNum);
		theApp.SetText(m_editPerRecvSize, "%d", _TempRecvPackSize);
	}

	theApp.SetText(m_editBotTotalMsgCount, "%d", pBot->m_nTotalMsgNum);
	theApp.SetText(m_editBotPosPackCount, "%d", pBot->m_nTotalPosPack);
	theApp.SetText(m_editBotPosMsgCount, "%d", pBot->m_nTotalPosMsg);
	theApp.SetText(m_editBotEnemyPackCount, "%d", pBot->m_nTotalSightPack);
	theApp.SetText(m_editBotEnemyMsgCount, "%d", pBot->m_nTotalSightMsg);

	theApp.SetText(m_editTotalMsgCount, "%d", g_nTotalMsgNum);
	theApp.SetText(m_editTotalPosPackCount, "%d", g_nTotalPosPack);
	theApp.SetText(m_editTotalPosMsgCount, "%d", g_nTotalPosMsg);
	theApp.SetText(m_editTotalEnemyPackCount, "%d", g_nTotalSightPack);
	theApp.SetText(m_editTotalEnemyMsgCount, "%d", g_nTotalSightMsg);	
}

void CGameBotView::UpdataStatMsgInfo(BaseRobot* pBot)
{
	if (m_xMsgInfo.GetShowType() == 0)
	{
		m_xMsgInfo.UpdataInformation(pBot->m_xMsgStatistician);
        m_xMsgInfo.UpdatePingChart(pBot->GetPingTime());
	}
	else
	{
		m_xMsgInfo.UpdataInformation(theApp.m_xTatolMsgStatistician);
	}

	m_xMsgInfo.UpdateConnectInfo(pBot->_targetGateIp.c_str(), pBot->_targetGatePort, pBot->GetBotState(), 0, pBot->IsConnectted());
}


void CGameBotView::UpdateChatMessage(BaseRobot *pBot)
{
	if (pBot == NULL || m_ChatList.m_hWnd == NULL)
	{
		return;
	}

	static int nBotID = -1;
	if (nBotID != pBot->GetBotID())
	{
		m_ChatList.SetWindowText("");
		nBotID = pBot->GetBotID();
	}
	
	static int nLineCount = 0;

	CString strEdit = "";
	m_ChatList.GetWindowText(strEdit);
	m_ChatList.SetSel(strEdit.GetLength(), strEdit.GetLength());

	string strMessage = pBot->PopChatMsgFormList();
	while (!strMessage.empty())
	{		
		strMessage += "\r\n";
		
		//if (nLineCount > 100)
		//{
		//	m_ChatList.SetSel(0, -1);
		//	m_ChatList.Cut();
		//	nLineCount = 0;			
		//}
		//else
		//{		
		//	
		//	++nLineCount;
		//}

		m_ChatList.ReplaceSel(strMessage.c_str());

		strMessage = pBot->PopChatMsgFormList();
	}	
}

void CGameBotView::OnBnClickedButtonSendChat()
{
	// TODO: Add your control notification handler code here

	CString strContent;
	m_editContent.GetWindowText(strContent);

	if (strContent.IsEmpty())
	{
		return;
	}

	BaseRobot *pBot = theApp.gBotApplication.GetBot(m_nBotID);
	if (pBot == NULL || pBot->GetBotState() != State_Play)
	{
		m_editContent.SetWindowText("");
		return;
	}

	MsgChat::CHAT_TYPE eType = MsgChat::CHAT_TYPE_NORMAL;

	switch(m_RadioType)
	{
	case 0:
		eType = MsgChat::CHAT_TYPE_NORMAL;
		break;
	case 1:
		eType = MsgChat::CHAT_TYPE_GUILD;
		break;
	case 2:
		eType = MsgChat::CHAT_TYPE_LEAGUE;
		break;
	case 3:
		eType = MsgChat::CHAT_TYPE_TERM;
		break;
	case 4:
		eType = MsgChat::CHAT_TYPE_HIGHSHOUT;
		break;
	case 5:
		eType = MsgChat::CHAT_TYPE_PRIVATE;
		//strcpy 私聊对象名字
		break;		
	}

	MsgChat xMsgChat(eType);
	
	xMsgChat.SetString(strContent.GetBuffer());
	pBot->SendMsg( &xMsgChat );

	m_editContent.SetWindowText("");
}

void CGameBotView::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	m_RadioType = 0;
}

void CGameBotView::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	m_RadioType = 1;
}

void CGameBotView::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
	m_RadioType = 2;
}

void CGameBotView::OnBnClickedRadio4()
{
	// TODO: Add your control notification handler code here
	m_RadioType = 3;
}

void CGameBotView::OnBnClickedRadio5()
{
	// TODO: Add your control notification handler code here
	m_RadioType = 4;
}

void CGameBotView::OnBnClickedRadio6()
{
	// TODO: Add your control notification handler code here
	m_RadioType = 5;
}


BOOL CGameBotView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			OnBnClickedButtonSendChat();

			return TRUE;
		}
	}
	
	return CFormView::PreTranslateMessage(pMsg);
}

void CGameBotView::ShowBigMap()
{
#ifdef HIDE_BOT_INFO
	return;
#endif

	if (m_pMapInfo == NULL)
	{
		m_pMapInfo = new MapInfo();

		if (m_pMapInfo != NULL)
		{
			m_pMapInfo->Create(IDD_DIALOG_MAP, this);
			m_pMapInfo->InitInformation();
		}
	}

	if (m_pMapInfo != NULL && m_nBotID == 0 )
	{
		m_pMapInfo->SetBotID(m_nBotID);
		m_pMapInfo->ShowWindow(SW_NORMAL);
		m_pMapInfo->SetForegroundWindow();
		m_pMapInfo->SetShow(true);

		m_pMapInfo->ShowMapBmp();
	}
}

int CGameBotView::GetBotTypeByTxt(CString BotTypeTxt)
{
    if (BotTypeTxt.IsEmpty())
        return Bot_End;

    for (int i = Bot_Normal; i < Bot_End;++i)
    {
        if (stricmp(s_pBotType[i],BotTypeTxt) == 0)
        {
            return i;
        }
    }
    return Bot_End;
}

void CGameBotView::OnDBCheckListBotCommond(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    
//     CString ItemTxt;
//     CString strID;
//     UINT uSelectedCount = m_ctlBotList.GetSelectedCount();   
//     int nItem = -1;   
//     if(uSelectedCount > 0)   
//     {   
//         //取得第一个被选中的项   
//         nItem = m_ctlBotList.GetNextItem(nItem, LVNI_SELECTED);    
//         if(nItem != -1)
//         {
//             ItemTxt = m_ctlBotList.GetItemText(nItem,0);
//             strID = m_ctlBotList.GetItemText(nIndex, 1);
//             m_nBotID = atoi(strID); 
//         }
//     }
//     if (ItemTxt.IsEmpty())
//         return ;
// 
//     if (stricmp(ItemTxt,"指令") != 0)
//         return;

    //过滤掉非指令机器的响应
    //////////////////////////////////////////////////////////////////////////

//     CCommondDialog Dialog(this);
//     Dialog.DoModal();
    *pResult = 0;
}

void CGameBotView::OnLvnItemchangedListBot(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here

	//CString strSelect;   
	////取得选中的个数
	//UINT uSelectedCount = m_ctlBotList.GetSelectedCount();   
	//int nItem = -1;   
	//if(uSelectedCount > 0)   
	//{   
	//	//取得第一个被选中的项   
	//	nItem = m_ctlBotList.GetNextItem(nItem, LVNI_SELECTED);    
	//	if(nItem != -1)
	//	{
	//		CString strID = m_ctlBotList.GetItemText(nItem, 1);

	//		if (!strID.IsEmpty())
	//		{
	//			int nID = atoi(strID.GetBuffer());

	//			theApp.m_BotServer.SetCurSel(nID);
	//			//theApp.ShowBotInfo(nID);

	//			m_nBotID = nID;
	//		}			
	//	}
	//}   
	*pResult = 0;
}

void CGameBotView::OnAlllogin()
{
	// TODO: Add your command handler code here
	int nCount = m_ctlBotList.GetItemCount();

	for (int i = 0; i < nCount; ++i)
	{
		CString strID = m_ctlBotList.GetItemText(i, 1);

		if (!strID.IsEmpty())
		{
			int nID = atoi(strID.GetBuffer());

			BaseRobot *pBot = theApp.gBotApplication.GetBot(nID);

			if(pBot != NULL && pBot->GetBotState() != State_Play)
			{
				pBot->SetBotState(e_state_no_confirm);
			}
		}	
	}
}


void CGameBotView::OnSelectedOutline()
{// 当前选中行的机器人下线
    POSITION pos = m_ctlBotList.GetFirstSelectedItemPosition();

    if (pos != NULL)
    {
        int nIndex = m_ctlBotList.GetNextSelectedItem(pos);
        if (nIndex != -1)
        {
            CString strID = m_ctlBotList.GetItemText(nIndex, 1);
            if (!strID.IsEmpty())
            {
                int nID = atoi(strID.GetBuffer());
                BaseRobot *pBot = theApp.gBotApplication.GetBot(nID);
                if(pBot != NULL && pBot->GetBotState() == State_Play)
                {
                    pBot->SetBotState(State_End);
                }
            }	
        }
    }
}

void CGameBotView::OnAllBotOutline()
{// 所有机器人下线
    int nCount = m_ctlBotList.GetItemCount();
    for (int i=0; i<nCount; ++i)
    {
        CString strID = m_ctlBotList.GetItemText(i, 1);
        if ( strID.IsEmpty() )
        { continue;}

        int nID = atoi(strID.GetBuffer());
        BaseRobot* pBot = theApp.gBotApplication.GetBot(nID);
        if (pBot != NULL && pBot->GetBotState() == State_Play)
        {
            pBot->SetBotState(State_End);   // 设置状态为离线
        }
    }
}

void CGameBotView::OnFlyBackInHell()
{
    // 暂时只给出矩阵机器人飞回地图
    CString strBotID;
    int nBotID = 0;
    int nCount = m_ctlBotList.GetItemCount();
    for (int i=0; i<nCount; ++i)
    {
        strBotID = m_ctlBotList.GetItemText(i, 1);
        if ( !strBotID.IsEmpty() )
        {
            nBotID = atoi(strBotID.GetBuffer());
            CMatrixBot* pMatrixBot = (CMatrixBot*)( theApp.gBotApplication.GetBot(nBotID) );
            if ( pMatrixBot != NULL && (pMatrixBot->GetMapID() == 99 || pMatrixBot->GetMapID() == 399 || pMatrixBot->GetMapID() == 699 || pMatrixBot->GetMapID() == 999) ) // 如果是在回魂殿
            {
                pMatrixBot->AddHp(); // 回满血
                CMatrixBot::fPoint pos = pMatrixBot->GetBotPos();
                pMatrixBot->FlyToMap(pMatrixBot->GetCurrentMap(), pos.x, pos.y); // 飞回原地
            }
        }
    }
}

#pragma warning( pop )
