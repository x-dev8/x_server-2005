// OptionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OptionDlg.h"
#include "GameDefineBot.h"

// COptionDlg 对话框

IMPLEMENT_DYNAMIC(COptionDlg, CDialog)

COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionDlg::IDD, pParent)
{
	m_vecAddInfo.clear();
}

COptionDlg::~COptionDlg()
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_IP, m_editIp);
    DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
    DDX_Control(pDX, IDC_EDIT_VERSION, m_editVersion);
    DDX_Control(pDX, IDC_EDIT_VERSION2, m_editAccount);
    DDX_Control(pDX, IDC_EDIT_VERSION4, m_editWidth);
    DDX_Control(pDX, IDC_EDIT_VERSION3, m_editPassword);
    DDX_Control(pDX, IDC_EDIT1, m_editSecond);
    DDX_Control(pDX, IDC_EDIT2, m_editCount);
    DDX_Control(pDX, IDC_CHECK2, m_checkRequest);
    DDX_Control(pDX, IDC_CHECK1, m_checkSleep);
    DDX_Control(pDX, IDC_LIST3, m_listAreaInfo);
    DDX_Control(pDX, IDC_COMBO1, m_comboId);
    DDX_Control(pDX, IDC_COMBO2, m_comboType);
    DDX_Control(pDX, IDC_COMBO3, m_comboCount);
    DDX_Control(pDX, IDC_COMBO4, m_comboMap);
    DDX_Control(pDX, IDC_COMBO5, m_comboScript);
    DDX_Control(pDX, IDC_EDIT3, m_editAddTime);
    DDX_Control(pDX, IDC_EDIT7, m_editRunTime);
    DDX_Control(pDX, IDC_EDIT55, m_editPosX);
    DDX_Control(pDX, IDC_EDIT12, m_editPosY);
    DDX_Control(pDX, IDC_EDIT_TIME4, m_editRadius);
    DDX_Control(pDX, IDC_CHECK3, m_checkLoginOnly);
    DDX_Control(pDX, IDC_CHECK4, m_checkReLogin);
    DDX_Control(pDX, IDC_CHECK5, m_checkDisableCheckTime);
    DDX_Control(pDX, IDC_CHOOSE_NET, m_cmbChooseNet);
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK2, &COptionDlg::OnBnClickedCheckRequest)
	ON_BN_CLICKED(IDC_BUTTON9, &COptionDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON4, &COptionDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON10, &COptionDlg::OnBnClickedButtonSave)
	ON_COMMAND(ID_DeleteAddInfo, &COptionDlg::OnDeleteaddinfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST3, &COptionDlg::OnNMRclickListAddInfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, &COptionDlg::OnNMDblclkListAddInfo)
	ON_BN_CLICKED(IDOK, &COptionDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// COptionDlg 消息处理程序

BOOL COptionDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_editIp.SetWindowText(theBotDataCenter.GetServerIP());
	theApp.SetText(m_editPort, "%d", theBotDataCenter.GetServerPort());
	m_editVersion.SetWindowText(theBotDataCenter.GetVersion());
	
	m_editAccount.SetWindowText(theBotDataCenter.GetBotAccount());
	theApp.SetText(m_editWidth, "%d", theBotDataCenter.GetAccountWidth());
	m_editPassword.SetWindowText(theBotDataCenter.GetBotPassword());
	
	SSetInfo *pSetInfo = theApp.gBotApplication.GetBotSetInfo();

	if(pSetInfo != NULL)
	{
		m_checkSleep.SetCheck(theBotDataCenter.SleepTime);		
		m_checkRequest.SetCheck(pSetInfo->nRequestStart);
		theApp.SetText(m_editSecond, "%d", pSetInfo->nRequestSecond);
		theApp.SetText(m_editCount, "%d", pSetInfo->nRequestCount);
	}

	m_checkLoginOnly.SetCheck(g_nLoginOnly);
	m_checkReLogin.SetCheck(!g_nReLogin);
	m_checkDisableCheckTime.SetCheck(g_nDisableCheckTime);

    // 网络选择
    m_cmbChooseNet.AddString(_T("内网"));
    m_cmbChooseNet.AddString(_T("外网"));
    m_cmbChooseNet.SetCurSel( theBotDataCenter.GetBotNet() );

	OnBnClickedCheckRequest();

	InitInformation();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

BOOL COptionDlg::PreTranslateMessage(MSG* pMsg)
{
    if ( pMsg->message == WM_KEYDOWN )
    {
        switch (pMsg->wParam)
        {
        case VK_RETURN:
            OnOK();
        	return TRUE;
        case VK_ESCAPE:
            OnOK();
            return TRUE;
        }
    }
    return CDialog::PreTranslateMessage(pMsg);
}
void COptionDlg::OnOK()
{
    // TODO: 在此添加专用代码和/或调用基类
    UpdateData();

    CString strIP;
    CString strPort;
    CString strVersion;
	CString strAccount;
	CString strWidth;
	CString strPassword;

	SSetInfo xSetInfo;

    m_editIp.GetWindowText(strIP);  
	m_editPort.GetWindowText(strPort);
	m_editVersion.GetWindowText(strVersion);
	m_editAccount.GetWindowText(strAccount);
	m_editWidth.GetWindowText(strWidth);
	m_editPassword.GetWindowText(strPassword);
    int nNet = m_cmbChooseNet.GetCurSel();// 网络选择
	
	theBotDataCenter.SleepTime = m_checkSleep.GetCheck();
	g_nLoginOnly = m_checkLoginOnly.GetCheck();
	g_nReLogin = !m_checkReLogin.GetCheck();
	g_nDisableCheckTime = m_checkDisableCheckTime.GetCheck();
	xSetInfo.nRequestStart = m_checkRequest.GetCheck();
	xSetInfo.nRequestSecond = theApp.GetInt(m_editSecond, 0);
	xSetInfo.nRequestCount = theApp.GetInt(m_editCount, 0);

    theBotDataCenter.SetServerIp(strIP.GetBuffer(strIP.GetLength()));
	theBotDataCenter.SetServerPort(atoi(strPort.GetBuffer()));
	//theApp.m_BotServer.SetServerVersion(strVersion.GetBuffer());
	theBotDataCenter.SetBotAccount(strAccount.GetBuffer(strPort.GetLength()));
	theBotDataCenter.SetAccountWidth(atoi(strWidth.GetBuffer()));
	theBotDataCenter.SetBotPassword(strPassword.GetBuffer());
    theBotDataCenter.SetBotNet( nNet ); //得到网络登录类型

	theApp.gBotApplication.SetBotSetInfo(&xSetInfo);

    static char s_szFile[] = "..\\Data\\RobotScript\\Robot.ini";
	theBotDataCenter.WritePrivateProfileInt("GameBot", "RequestStart", xSetInfo.nRequestStart, s_szFile);
	theBotDataCenter.WritePrivateProfileInt("GameBot", "RequestSecond", xSetInfo.nRequestSecond, s_szFile);
	theBotDataCenter.WritePrivateProfileInt("GameBot", "RequestCount", xSetInfo.nRequestCount, s_szFile);
    theBotDataCenter.SaveConfigFile(s_szFile);
	theApp.UpdataAddFrmScriptCombox();

    CDialog::OnOK();
}

void COptionDlg::OnCancel()
{
    // TODO: 在此添加专用代码和/或调用基类

    CDialog::OnCancel();
}

void COptionDlg::OnBnClickedCheckRequest()
{
	// TODO: Add your control notification handler code here
	int nCheck = m_checkRequest.GetCheck();

	m_editSecond.EnableWindow(nCheck);
	m_editCount.EnableWindow(nCheck);
}




void COptionDlg::InitInformation()
{
	RECT rect;
	int nWidth = 0;
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;

	m_listAreaInfo.SetExtendedStyle(dwStyle);
	m_listAreaInfo.GetClientRect(&rect);

	nWidth = rect.right - rect.left;
	int iIndex = 0;

	m_listAreaInfo.InsertColumn(iIndex++, _T("起始ID"), 0, (12 * nWidth / 100));
	m_listAreaInfo.InsertColumn(iIndex++, _T("类型"), 0, (10 * nWidth / 100));
	m_listAreaInfo.InsertColumn(iIndex++, _T("数量"), 0, (10 * nWidth / 100));
	m_listAreaInfo.InsertColumn(iIndex++, _T("地图"), 0, (25 * nWidth / 100));
	m_listAreaInfo.InsertColumn(iIndex++, _T("坐标"), 0, (20 * nWidth / 100));
	m_listAreaInfo.InsertColumn(iIndex++, _T("半径"), 0, (10 * nWidth / 100));
	m_listAreaInfo.InsertColumn(iIndex++, _T("添加间隔"), 0, (14 * nWidth / 100));
	m_listAreaInfo.InsertColumn(iIndex++, _T("执行间隔"), 0, (14 * nWidth / 100));


	////////////////////////////////////////////////////////////////////////////////////
	m_comboId.AddString("1000");
	m_comboId.AddString("2000");
	m_comboId.AddString("3000");
	m_comboId.AddString("4000");
	m_comboId.AddString("5000");
	m_comboId.AddString("6000");
	m_comboId.AddString("7000");
	m_comboId.AddString("8000");
	m_comboId.AddString("9000");

	m_comboId.SetCurSel(0);

	///////////////////////////////////////////////////////////////////////////////////////////////
	static const int s_nTypeCount = sizeof(s_pBotType) / sizeof(char*);
	for (int i = 0; i < s_nTypeCount; ++i)
	{
		m_comboType.AddString(s_pBotType[i]);
		m_vecType.push_back(s_pBotType[i]);
	}	
	m_comboType.SetCurSel(0);

	/////////////////////////////////////////////////////////////////////////////////////////////////

	m_comboCount.AddString("1");
	m_comboCount.AddString("500");
	m_comboCount.AddString("1000");
	m_comboCount.AddString("2000");
	m_comboCount.AddString("3000");
	m_comboCount.AddString("4000");

	m_comboCount.SetCurSel(0);

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//添加地图信息
	m_vecMap.clear();
	m_comboMap.AddString("不指定区域");
	m_vecMap.push_back("不指定区域");
	int nCount = theMapConfig.MapDataCount();
	for (int i = 0; i < nCount; ++i)
	{
		MapConfig::MapData* pMapData = theMapConfig.GetMapDataByIndex(i);
		if (pMapData != NULL)
		{
			m_comboMap.AddString(pMapData->MapName.c_str());
			m_vecMap.push_back(pMapData->MapName);
		}
		else
		{
			m_comboMap.AddString("未知地图信息");
			m_vecMap.push_back("未知地图信息");
		}
	}
	m_comboMap.SetCurSel(0);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	m_editAddTime.SetWindowText("1000");
	m_editRunTime.SetWindowText("500");
	m_editPosX.SetWindowText("300");
	m_editPosY.SetWindowText("300");
	m_editRadius.SetWindowText("300");
	//读取所有的脚本文件
	theApp.ReadAllScript(Script_Path, m_comboScript, m_vecScript);
}


void COptionDlg::OnBnClickedButtonLoad()
{
	// TODO: Add your control notification handler code here
	CString strScript = "";

	m_comboScript.GetWindowText(strScript);

	if (strScript.IsEmpty())
	{
		return;
	}

	CString strFile = "";
	strFile.Format("%s\\%s", Script_Path, strScript);

	theApp.LoadScript(strFile.GetBuffer(), m_vecAddInfo);

	ShowAddInfoList();

}

void COptionDlg::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here

	CString strScript = "";

	m_comboScript.GetWindowText(strScript);

	if (strScript.IsEmpty())
	{
		return;
	}

	CString strFile = "";
	strFile.Format("%s\\%s", Script_Path, strScript);

	theApp.SaveScript(strFile.GetBuffer(), m_vecAddInfo);
}


void COptionDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here

	SAddInfo xAddInfo;

	CString strStartId = "";
	m_comboId.GetWindowText(strStartId);
	xAddInfo.nStartId = atoi(strStartId.GetBuffer());

	CString strType = "";
	xAddInfo.nType = m_comboType.GetCurSel();

	CString strCount = "";
	m_comboCount.GetWindowText(strCount);
	xAddInfo.nCount = atoi(strCount.GetBuffer());

	xAddInfo.nSpaceTime = theApp.GetInt(m_editAddTime, 1000);
	xAddInfo.nPerCount = 1;
	xAddInfo.nMoveStep = theApp.GetInt(m_editRunTime, 500);

	xAddInfo.xAreaInfo.nMap = m_comboMap.GetCurSel() - 1;
	xAddInfo.xAreaInfo.xPoint.x = theApp.GetInt(m_editPosX, 300);
	xAddInfo.xAreaInfo.xPoint.y = theApp.GetInt(m_editPosY, 300);
	xAddInfo.xAreaInfo.nRadius = theApp.GetInt(m_editRadius, 300);

	xAddInfo.nFlySpace = 120;
	xAddInfo.nOnlineTime = 120;
	
	AddInVector(xAddInfo);

	ShowAddInfoList();
}

void  COptionDlg::AddInVector(SAddInfo &xAddInfo)
{
	//先找相同的
	ItrAddInfoContainer iter = find(m_vecAddInfo.begin(), m_vecAddInfo.end(), xAddInfo.nStartId);
	if (iter != m_vecAddInfo.end())
	{
		(*iter) = xAddInfo;
	}
	else
	{
		//找空的
		iter = find(m_vecAddInfo.begin(), m_vecAddInfo.end(), -1);
		if (iter != m_vecAddInfo.end())
		{
			(*iter) = xAddInfo;
		}
		else
		{
			//没有找到 直接添加
			m_vecAddInfo.push_back(xAddInfo);
		}
	}
	
	sort(m_vecAddInfo.begin(), m_vecAddInfo.end());
}

bool COptionDlg::DeleteFromVector(int nStartId)
{
	if (nStartId == -1)
	{
		return false;
	}

	ItrAddInfoContainer iter = find(m_vecAddInfo.begin(), m_vecAddInfo.end(), nStartId);
	if (iter != m_vecAddInfo.end())
	{
		(*iter).nStartId = -1;

		sort(m_vecAddInfo.begin(), m_vecAddInfo.end());

		return true;
	}

	return false;
}

bool  COptionDlg::AddInListCtrl(int nIndex, SAddInfo &xAddInfo)
{
	if (xAddInfo.nStartId == -1 || xAddInfo.nType < 0 || xAddInfo.nType > m_vecType.size())
	{
		return false;
	}

	int nSubItem = 0;
	m_listAreaInfo.InsertItem(nIndex, "");
	theApp.SetListItemText(m_listAreaInfo, nIndex, nSubItem++, "%d", xAddInfo.nStartId);
	m_listAreaInfo.SetItemText(nIndex, nSubItem++, m_vecType[xAddInfo.nType].c_str());
	theApp.SetListItemText(m_listAreaInfo, nIndex, nSubItem++, "%d", xAddInfo.nCount);

	m_listAreaInfo.SetItemText(nIndex, nSubItem++, m_vecMap[xAddInfo.xAreaInfo.nMap + 1].c_str());

	theApp.SetListItemText(m_listAreaInfo, nIndex, nSubItem++, "%d,%d", xAddInfo.xAreaInfo.xPoint.x, xAddInfo.xAreaInfo.xPoint.y);
	theApp.SetListItemText(m_listAreaInfo, nIndex, nSubItem++, "%d", xAddInfo.xAreaInfo.nRadius);
	theApp.SetListItemText(m_listAreaInfo, nIndex, nSubItem++, "%d", xAddInfo.nSpaceTime);
	theApp.SetListItemText(m_listAreaInfo, nIndex, nSubItem++, "%d", xAddInfo.nMoveStep);

	return true;
}

void COptionDlg::ShowAddInfoList()
{

	m_listAreaInfo.DeleteAllItems();

	ItrAddInfoContainer iter = m_vecAddInfo.begin();
	ItrAddInfoContainer end = m_vecAddInfo.end();

	for (int i = 0; iter != end; ++iter)
	{
		if (AddInListCtrl(i, (*iter)))
		{
			++i;
		}
	}
}

void COptionDlg::OnDeleteaddinfo()
{
	// TODO: Add your command handler code here

	int nIndex = theApp.GetListCtrlCurSel(m_listAreaInfo);
	if (nIndex != -1)
	{
		int nStartId = theApp.GetListItemInt(m_listAreaInfo, nIndex, 0, -1);

		if (DeleteFromVector(nStartId))
		{
			ShowAddInfoList();
		}
	}

}

void COptionDlg::OnNMRclickListAddInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int nIndex = theApp.GetListCtrlCurSel(m_listAreaInfo);
	if (nIndex != -1)
	{
		CMenu menu;
		CPoint pt;
		GetCursorPos(&pt);
		menu.LoadMenu(IDR_MENU_DELETEADDINFO);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);	
	}
	*pResult = 0;
}

void COptionDlg::OnNMDblclkListAddInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	int nIndex = theApp.GetListCtrlCurSel(m_listAreaInfo);

	if (nIndex != -1)
	{
		int nStartId = theApp.GetListItemInt(m_listAreaInfo, nIndex, 0, -1);
		SAddInfo *pAddInfo = FindAddInfo(nStartId);
		if (pAddInfo != NULL)
		{
			ShowAddInfo(*pAddInfo);
		}
	}

	*pResult = 0;
}


SAddInfo* COptionDlg::FindAddInfo(int nStartId)
{
	if (nStartId == -1)
	{
		return NULL;
	}

	ItrAddInfoContainer iter = find(m_vecAddInfo.begin(), m_vecAddInfo.end(), nStartId);
	if (iter != m_vecAddInfo.end())
	{
		return &(*iter);
	}

	return NULL;
}

void COptionDlg::ShowAddInfo(SAddInfo &xAddInfo)
{	
	theApp.SetText(m_comboId, "%d", xAddInfo.nStartId);
	m_comboType.SetCurSel(xAddInfo.nType);
	theApp.SetText(m_comboCount, "%d", xAddInfo.nCount);
	theApp.SetText(m_editAddTime, "%d", xAddInfo.nSpaceTime);
	theApp.SetText(m_editRunTime, "%d", xAddInfo.nMoveStep);

	m_comboMap.SetCurSel(xAddInfo.xAreaInfo.nMap + 1);
	theApp.SetText(m_editPosX, "%d", xAddInfo.xAreaInfo.xPoint.x);
	theApp.SetText(m_editPosY, "%d", xAddInfo.xAreaInfo.xPoint.y);
	theApp.SetText(m_editRadius, "%d", xAddInfo.xAreaInfo.nRadius);
}
void COptionDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
