// MessageInfo.cpp : implementation file
//

#include "stdafx.h"
#include "MessageInfo.h"
#include "GameBot.h"

#include "Bot.h"
#include "BotApplication.h"
#include "LogFileObjectName.h"
#include "PasswordDefine.h"
#include "PasswordMessage.h"

// MessageInfo dialog

IMPLEMENT_DYNAMIC(MessageInfo, CDialog)

MessageInfo::MessageInfo(CWnd* pParent /*=NULL*/)
	: CDialog(MessageInfo::IDD, pParent)
	, m_nShowType(0)
{
	m_bInit = false;

	m_nBotID = -1;
}

MessageInfo::~MessageInfo()
{
}

void MessageInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editRunTime);
	DDX_Control(pDX, IDC_EDIT2, m_editUpdataCount);
	DDX_Control(pDX, IDC_EDIT4, m_editLoopCountPerSecond);
	DDX_Control(pDX, IDC_EDIT55, m_editSendCount);
	DDX_Control(pDX, IDC_EDIT7, m_editSendCountPerSecond);
	DDX_Control(pDX, IDC_EDIT9, m_editSendSizePerSecond);
	DDX_Control(pDX, IDC_EDIT8, m_editSendSize);
	DDX_Control(pDX, IDC_EDIT56, m_editRecvCount);
	DDX_Control(pDX, IDC_EDIT12, m_editRecvSize);
	DDX_Control(pDX, IDC_EDIT57, m_editRecvCountPerSecond);
	DDX_Control(pDX, IDC_EDIT58, m_editRecvSizePerSecond);
	DDX_Control(pDX, IDC_EDIT5, m_editMinSendCount);
	DDX_Control(pDX, IDC_EDIT14, m_editMaxSendCount);
	DDX_Control(pDX, IDC_EDIT47, m_editMinRecvCount);
	DDX_Control(pDX, IDC_EDIT48, m_editMaxRecvCount);
	DDX_Control(pDX, IDC_EDIT10, m_editMinSendSize);
	DDX_Control(pDX, IDC_EDIT15, m_editMaxSendSize);
	DDX_Control(pDX, IDC_EDIT16, m_editMinRecvSize);
	DDX_Control(pDX, IDC_EDIT49, m_editMaxRecvSize);
	DDX_Control(pDX, IDC_LIST1, m_listMinSend);
	DDX_Control(pDX, IDC_LIST2, m_listMaxSend);
	DDX_Control(pDX, IDC_LIST4, m_listMinRecv);
	DDX_Control(pDX, IDC_LIST5, m_listMaxRecv);
	DDX_Control(pDX, IDC_LIST6, m_listAllSendMsg);
	DDX_Control(pDX, IDC_LIST7, m_listAllRecvMsg);
	DDX_Radio(pDX, IDC_RADIO2, m_nShowType);
	DDX_Control(pDX, IDC_EDIT3, m_editFile);
	DDX_Control(pDX, IDC_BUTTON2, m_buttonLog);
	DDX_Control(pDX, IDC_EDIT_STATE, m_editState);
	DDX_Control(pDX, IDC_EDIT_IP, m_editIp);
	DDX_Control(pDX, IDC_EDIT17, m_editMonsterNum);
	DDX_Control(pDX, IDC_BUTTON_CREATEMONSTER, m_buttonCreateMonster);
	DDX_Control(pDX, IDC_BUTTON_CHANGEEQUIP, m_buttonChangeEquip);
	DDX_Control(pDX, IDC_BUTTON_RANDRIDE, m_buttonRandRide);
	DDX_Control(pDX, IDC_BUTTON_FIGHT, m_buttonCountryFight);
	DDX_Control(pDX, IDC_EDIT_TOTALMONSTER_NUM, m_editTotalMonsterNum);
}


BEGIN_MESSAGE_MAP(MessageInfo, CDialog)
	ON_BN_CLICKED(IDC_RADIO2, &MessageInfo::OnBnClickedRadioSingle)
	ON_BN_CLICKED(IDC_RADIO3, &MessageInfo::OnBnClickedRadioTotal)
	ON_BN_CLICKED(IDC_BUTTON11, &MessageInfo::OnBnClickedButtonOpenFile)
	ON_BN_CLICKED(IDC_BUTTON2, &MessageInfo::OnBnClickedButtonSaveLog)
	ON_BN_CLICKED(IDC_BUTTON_CREATEMONSTER, &MessageInfo::OnBnCreateMonster)
	ON_BN_CLICKED(IDC_BUTTON_CHANGEEQUIP, &MessageInfo::OnBnClickedChangeEquip)
	ON_BN_CLICKED(IDC_BUTTON_RANDRIDE, &MessageInfo::OnBnClickedButtonRandride)
	ON_BN_CLICKED(IDC_PREPARESUIT, &MessageInfo::OnPreparesuit)
	ON_BN_CLICKED(IDC_BUTTON_FIGHT, &MessageInfo::OnBnClickedButtonFight)
END_MESSAGE_MAP()


// MessageInfo message handlers
BOOL MessageInfo::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
		case VK_ESCAPE:
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void MessageInfo::InitInformation()
{
	if (m_bInit)
	{ return; }

	m_bInit = true;

	RECT rect;
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	int nWidth = 0;
	int iIndex = 0;

	static CListCtrl *s_pListInfo[] = { &m_listMinSend, &m_listMaxSend, &m_listMinRecv, &m_listMaxRecv,};	
	const int nCount = sizeof(s_pListInfo) / sizeof(CListCtrl*);

	s_pListInfo[0]->GetClientRect(&rect);
	nWidth = rect.right - rect.left;

	for (int i = 0; i < nCount; ++i)
	{
		s_pListInfo[i]->SetExtendedStyle(dwStyle);

		s_pListInfo[i]->InsertColumn(0, "消息", 0, (50 * nWidth) / 100);
		s_pListInfo[i]->InsertColumn(1, "数量", 0, (20 * nWidth) / 100);
		s_pListInfo[i]->InsertColumn(2, "大小", 0, (30 * nWidth) / 100);
	}

	m_listAllSendMsg.GetClientRect(&rect);
	nWidth = rect.right - rect.left;

	static CListCtrl *s_pAllMsgListInfo[] = { &m_listAllSendMsg, &m_listAllRecvMsg, };	
	const int nAllMsgListCount = sizeof(s_pAllMsgListInfo) / sizeof(CListCtrl*);

	for (int i = 0; i < nAllMsgListCount; ++i)
	{
		s_pAllMsgListInfo[i]->SetExtendedStyle(dwStyle);

		s_pAllMsgListInfo[i]->InsertColumn(0, "消息", 0, (37 * nWidth) / 100);
		s_pAllMsgListInfo[i]->InsertColumn(1, "数量", 0, (18 * nWidth) / 100);
		s_pAllMsgListInfo[i]->InsertColumn(2, "大小", 0, (25 * nWidth) / 100);
		s_pAllMsgListInfo[i]->InsertColumn(3, "百分比", 0, (20 * nWidth) / 100);
	}	

	m_editFile.SetWindowText("MsgLog");
    // 单个机器人的Ping图表
    m_Histogram.Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP, this,IDC_STATIC_CHART);
    m_Histogram.SetRange(1, 100);
    m_Histogram.SetSpeed(CHistogramCtrl::HIGH_SPEED);
}


void MessageInfo::UpdateConnectInfo(const char* ip, WORD port, int nState, DWORD dwError, bool bConnect)
{
	static char* szState[] = { "未连接", "已连接", };

	if (m_editIp.m_hWnd == NULL) { return; }

	CString strText = "";
	strText.Format("%s : %d", szState[bConnect], nState);
	if (ip == NULL || *ip == 0)
	{
		m_editIp.SetWindowText("");
	}
	else
	{
		CString strText = "";
		strText.Format("%s : %u  ", ip, port);
		
		m_editIp.SetWindowText(strText);
	}

	m_editState.SetWindowText(strText);
}

void MessageInfo::UpdataInformation(MsgStatistician &xMsgStatistican)
{
	if (m_editRunTime.m_hWnd == NULL) 
   { return; }

	DWORD dwNowTime = HQ_TimeGetTime();

	m_editRunTime.SetWindowText(xMsgStatistican.GetStatisticianTimeString(dwNowTime));
	theApp.SetText(m_editUpdataCount, "%I64u", xMsgStatistican.GetLoopCount());
	theApp.SetText(m_editLoopCountPerSecond, "%I64u", xMsgStatistican.GetLoopCountPerSecond(dwNowTime));

	theApp.SetText(m_editSendCount, "%I64u", xMsgStatistican.GetMsgSendCount());
	theApp.SetText(m_editSendSize, "%I64u", xMsgStatistican.GetMsgSendSize());
	theApp.SetText(m_editSendCountPerSecond, "%I64u", xMsgStatistican.GetMsgSendCountPerSecond(dwNowTime));
	theApp.SetText(m_editSendSizePerSecond, "%I64u", xMsgStatistican.GetMsgSendSizePerSecond(dwNowTime));


	theApp.SetText(m_editRecvCount, "%I64u", xMsgStatistican.GetMsgRecvCount());
	theApp.SetText(m_editRecvSize, "%I64u", xMsgStatistican.GetMsgRecvSize());
	theApp.SetText(m_editRecvCountPerSecond, "%I64u", xMsgStatistican.GetMsgRecvCountPerSecond(dwNowTime));
	theApp.SetText(m_editRecvSizePerSecond, "%I64u", xMsgStatistican.GetMsgRecvSizePerSecond(dwNowTime));
   theApp.SetText(m_editMonsterNum, "%I64u", xMsgStatistican.GetMonsterNum());//luo.qin 3.18

	static CEdit *s_pEditCount[] = {&m_editMinSendCount, &m_editMaxSendCount, &m_editMinRecvCount, &m_editMaxRecvCount, };
	static CEdit *s_pEditSize[] = {&m_editMinSendSize, &m_editMaxSendSize, &m_editMinRecvSize, &m_editMaxRecvSize, };
	static CListCtrl *s_pListInfo[] = { &m_listMinSend, &m_listMaxSend, &m_listMinRecv, &m_listMaxRecv,};	
	const int nCount = sizeof(s_pListInfo) / sizeof(CListCtrl*);

	vector<MsgStatistician::Total_Info_> vecTotalInfo;
	vecTotalInfo.clear();

	vecTotalInfo.push_back(xMsgStatistican.m_xMinSendInfo);
	vecTotalInfo.push_back(xMsgStatistican.m_xMaxSendInfo);
	vecTotalInfo.push_back(xMsgStatistican.m_xMinRecvInfo);
	vecTotalInfo.push_back(xMsgStatistican.m_xMaxRecvInfo);

	for (int i = 0; i < nCount; ++i)
	{
		int nValue = theApp.GetInt(*s_pEditCount[i], 0);  //获得上一次的

		if (nValue != vecTotalInfo[i].dwCount)
		{
			theApp.SetText(*s_pEditCount[i], "%I64u", vecTotalInfo[i].dwCount);
			theApp.SetText(*s_pEditSize[i], "%I64u", vecTotalInfo[i].dwSize);

			s_pListInfo[i]->DeleteAllItems();

			vector<MsgStatistician::Msg_Info_>::iterator iter = vecTotalInfo[i].vecMsgInfo.begin(); // ???
			vector<MsgStatistician::Msg_Info_>::iterator end  = vecTotalInfo[i].vecMsgInfo.end();

			for (int j = 0 ; iter != end; ++iter, ++j)
			{
               if ( (*iter).dwType <= 0 )
               { break;}

				s_pListInfo[i]->InsertItem(j, GetMessageType((*iter).dwType));
				theApp.SetListItemText(*s_pListInfo[i], j, 1, "%I64u", (*iter).dwCount);
				theApp.SetListItemText(*s_pListInfo[i], j, 2, "%I64u", (*iter).dwSize);			
			}
		}		
	}

	///////////////////////////////////////////////////////////////////////////////

	ShowAllMessageInformantion(xMsgStatistican.m_mapMsgSendCount, m_listAllSendMsg, xMsgStatistican.GetMsgSendSize()); // 所有发送的消息列表显示
	ShowAllMessageInformantion(xMsgStatistican.m_mapMsgRecvCount, m_listAllRecvMsg, xMsgStatistican.GetMsgRecvSize()); // 所有接收的消息列表显示
}


void MessageInfo::ShowAllMessageInformantion(map<DWORD, MsgStatistician::Msg_Info_> &mapMsgInfo, CListCtrl &xListCtrl, int64 dwMaxMsgSize)
{
	int nAllCount = xListCtrl.GetItemCount();

	map<DWORD, MsgStatistician::Msg_Info_>::iterator iter = mapMsgInfo.begin();
	map<DWORD, MsgStatistician::Msg_Info_>::iterator end = mapMsgInfo.end();

	int i = 0;
	for ( ; iter != end; ++iter, ++i)
	{
       if ( iter->second.dwType <= 0 ) // 当类型为0时，不显示
       { break;}

		if (i >= nAllCount)
		{
			xListCtrl.InsertItem(i, GetMessageType(iter->second.dwType));
			++nAllCount;
		}
		else
		{
			xListCtrl.SetItemText(i, 0, GetMessageType(iter->second.dwType));
		}

		theApp.SetListItemText(xListCtrl, i, 1, "%I64d", (*iter).second.dwCount);
		theApp.SetListItemText(xListCtrl, i, 2, "%I64d", (*iter).second.dwSize);

		if (dwMaxMsgSize != 0)
		{
			theApp.SetListItemText(xListCtrl, i, 3, "%f", ((double)(*iter).second.dwSize / (double)dwMaxMsgSize) * 100);
		}	
	}

	for (int j = nAllCount - 1; j >= i ;  --j)
	{
		xListCtrl.DeleteItem(j);
	}
}

void MessageInfo::ResetChartMap()
{
    m_Histogram.Reset();
}

void MessageInfo::OnBnClickedRadioSingle()
{
	// TODO: Add your control notification handler code here

	m_nShowType = 0;
}

void MessageInfo::OnBnClickedRadioTotal()
{
	// TODO: Add your control notification handler code here
	m_nShowType = 1;
}

void MessageInfo::OnBnClickedButtonOpenFile()
{
	// TODO: Add your control notification handler code here	

	char szProcPath[_MAX_PATH] = {0};
	char szDir[_MAX_DIR] = {0};
	char szDirve[_MAX_DRIVE] = {0};

	::GetModuleFileName(NULL, szProcPath, sizeof(szProcPath));


	_tsplitpath_s(szProcPath, szDirve, sizeof(szDirve), szDir, sizeof(szDir), NULL, 0, NULL, 0);

	CString strFileName = "";
    CString strFilePath = "";
	m_editFile.GetWindowText(strFileName);

	if (strFileName.IsEmpty())
	{
		strFilePath.Format("explorer.exe , %s%s%s", szDirve, szDir, MESSAGE_FILE_PATH);
	}
	else
	{
		strFilePath.Format("explorer.exe /select, %s%s%s\\%s.log", szDirve, szDir, MESSAGE_FILE_PATH, strFileName.GetBuffer());
	}
	
	::WinExec(strFilePath.GetBuffer(), SW_SHOWNORMAL);
}

void MessageInfo::OnBnClickedButtonSaveLog()
{
	// TODO: Add your control notification handler code here
	
	CString strFileName = "";

	m_editFile.GetWindowText(strFileName);
	if (strFileName.IsEmpty())
	{
		return;
	}

	//设置Log文件保存在Error Log 文件夹下
	static char s_szFilePath[_MAX_PATH] = {0};

	if (s_szFilePath[0] == 0)
	{
		char szProcPath[_MAX_PATH];
		char szDir[_MAX_DIR];
		char szDirve[_MAX_DRIVE];

		::GetModuleFileName(NULL, szProcPath, sizeof(szProcPath));

		_tsplitpath(szProcPath, szDirve, szDir, NULL, NULL);
		sprintf_s(s_szFilePath, sizeof(s_szFilePath), "%s%s\\%s", szDirve, szDir, MESSAGE_FILE_PATH);

		if (GetFileAttributes(s_szFilePath) == INVALID_FILE_ATTRIBUTES)
		{
			::_mkdir(s_szFilePath);	
		}		
	}

	char szFile[_MAX_PATH] = {0};
	
	sprintf_s(szFile, sizeof(szFile), ".\\%s\\%s.log", MESSAGE_FILE_PATH, strFileName.GetBuffer());

	theApp.PrintStatLog(m_nShowType, szFile);
}


////////////////////////////////////////////////////////////////////////////////////////////////

char* MessageInfo::GetMessageType(DWORD dwType)
{
	static char szType[30] = "";
	//memset(szType, 0, sizeof(szType));

	switch(dwType)
	{
	case MSG_PING:
		strcpy_s(szType, sizeof(szType), "Ping消息");
		break;

	case MSG_RIGHTCHECK2:
		strcpy_s(szType, sizeof(szType), "版本确认");
		break;

	case MSG_LOGIN2:
		strcpy_s(szType, sizeof(szType), "登录消息");
		break;

	case MSG_ACK_SWITCHGATE:
		strcpy_s(szType, sizeof(szType), "回应Gate服务器");
		break;

	case MSG_ALLOCGWID:
		strcpy_s(szType, sizeof(szType), "请求分配ID");
		break;

	case MSG_GETCHARACTER:
		strcpy_s(szType, sizeof(szType), "获得角色信息");
		break;

	case MSG_CREATECHAR:
		strcpy_s(szType, sizeof(szType), "创建角色");
		break;

	case MSG_ENTERWORLD:
		strcpy_s(szType, sizeof(szType), "进入游戏");
		break;

	case MSG_REQRELIVE:
		strcpy_s(szType, sizeof(szType), "复活消息");
		break;

	case MSG_CHAT:
		strcpy_s(szType, sizeof(szType), "聊天消息");
		break;

	case MSG_EQUIP:
	case MSG_ACKEQUIP:
		strcpy_s(szType, sizeof(szType), "装备道具");
		break;

	case MSG_QUERYCHARINFO:
		strcpy_s(szType, sizeof(szType), "请求玩家信息");
		break;

	case MSG_MAPLOADED:
		strcpy_s(szType, sizeof(szType), "载入地图完成");
		break;

	case MSG_POSCHANGE:
		strcpy_s(szType, sizeof(szType), "坐标变化");
		break;

	case MSG_LOCKTARGET:
		strcpy_s(szType, sizeof(szType), "锁定目标");
		break;

	case MSG_PLAYERMOVINGPOSANDDIRTOSERVER:
		strcpy_s(szType, sizeof(szType), "人物移动");
		break;

	case MSG_ATTACKLOCKTARGET:
		strcpy_s(szType, sizeof(szType), "普通攻击");
		break;

	case MSG_REQSKILLATTACK:
		strcpy_s(szType, sizeof(szType), "魔法攻击");
		break;

	case MSG_ACKLOGIN:
		strcpy_s(szType, sizeof(szType), "回应登录");
		break;

	case MSG_SWITCHGATE:
		strcpy_s(szType, sizeof(szType), "请求Gate服务器");
		break;

	case MSG_ACKCHAR:
		strcpy_s(szType, sizeof(szType), "回应人物角色");
		break;

	case MSG_ENDACKCHAR:
		strcpy_s(szType, sizeof(szType), "角色列表完成");
		break;

	case MSG_ACKENTERWORLD:
		strcpy_s(szType, sizeof(szType), "回应进入游戏");
		break;

	case MSG_ACKENTERWORLDPACK:
		strcpy_s(szType, sizeof(szType), "进入游戏消息");
		break;

	case MSG_VERIFYPOS:
		strcpy_s(szType, sizeof(szType), "校正人物坐标");
		break;

	case MSG_LOGINWAIT:
		strcpy_s(szType, sizeof(szType), "登录等待");
		break;

	case MSG_INQUIREINVITEE:
		strcpy_s(szType, sizeof(szType), "组队邀请");
		break;

	case MSG_CHARATTRCHANGE:
		strcpy_s(szType, sizeof(szType), "角色数值改变");
		break;

	case MSG_PLAYERMOVINGPOS:
		strcpy_s(szType, sizeof(szType), "玩家位置改变");
		break;	

	case MSG_PLAYERMOVINGPOSANDDIR:
		strcpy_s(szType, sizeof(szType), "玩家移动");
		break;

	case MSG_UNPLAYERVERIFYPOS:
		strcpy_s(szType, sizeof(szType), "非玩家坐标校正");
		break;

	case MSG_UNPLAYERMOVINGTOPOS:
		strcpy_s(szType, sizeof(szType), "非玩家移动");
		break;

	case MSG_UNPLAYERCLOSINGTOLOCKTARGET:
		strcpy_s(szType, sizeof(szType), "怪物靠近目标");
		break;

	case MSG_PLAYER_ENTERMYSIGHT:
	case MSG_PLAYER_ENTERMYSIGHTMOVINGASTEP:
	case MSG_ENTERMYSIGHTPACK:
	case MSG_NPC_ENTERMYSIGHT:
	case MSG_NPC_ENTERMYSIGHTMOVINGASTEP:
		strcpy_s(szType, sizeof(szType), "进入视野消息");	
		break;

	case MSG_EXITMYSIGHT:
		strcpy_s(szType, sizeof(szType), "离开人物视野");	
		break;

	case MSG_ACKCHARINFO:
		strcpy_s(szType, sizeof(szType), "回应请求角色");	
		break;

	case MSG_SEEATTACK3:
		strcpy_s(szType, sizeof(szType), "玩家攻击");	
		break;

	case MSG_SAWSOMEONEDEAD:
		strcpy_s(szType, sizeof(szType), "有人死亡");	
		break;

	case MSG_GETITEM:
		strcpy_s(szType, sizeof(szType), "获得物品");	
		break;

	//case MSG_QUERYBARGAINING:
	//	strcpy_s(szType, sizeof(szType), "请求消息");	
	//	break;

	//case MSG_ACKBARGAINING:
	//	strcpy_s(szType, sizeof(szType), "回应交易");	
	//	break;

	case MSG_CHANGEMAP:
		strcpy_s(szType, sizeof(szType), "地图切换");	
		break;

	case MSG_ACKDROPITEM:
		strcpy_s(szType, sizeof(szType), "丢弃物品");	
		break;

	case MSG_CHARLEVELUP:
		strcpy_s(szType, sizeof(szType), "角色升级");	
		break;

	case MSG_SEND_REAL_TIME:
		strcpy_s(szType, sizeof(szType), "发送时间");	
		break;

	//case MSG_GUILD_ACK_GUILDLIST:
	//	strcpy_s(szType, sizeof(szType), "响应公会消息");	
	//	break;

	case MSG_TellShopCenterOffSet:
		strcpy_s(szType, sizeof(szType), "商城折扣");	
		break;

	case MSG_TELLC_LOCKNUM:
		strcpy_s(szType, sizeof(szType), "告诉C锁数量");	
		break;

	case MSG_PKSTATE_CHANGE:
		strcpy_s(szType, sizeof(szType), "PK状态改变");	
		break;

	case MSG_ACK_CHANGE_PKFLAG:
		strcpy_s(szType, sizeof(szType), "回应PK状态改变");	
		break;

	case MSG_TELL_EXPLOIT:
		strcpy_s(szType, sizeof(szType), "功勋改变");	
		break;

	case MSG_TELL_CHAR_VAR:
		strcpy_s(szType, sizeof(szType), "人物状态");	
		break;

	case MSG_SCRIPTEND:
		strcpy_s(szType, sizeof(szType), "脚本结束");	
		break;

	//case MSG_UPDATEBODYSTATUS:
	//	strcpy_s(szType, sizeof(szType), "更新角色状态");	
	//	break;

	case MSG_UPDATEFIGHTDATA:
		strcpy_s(szType, sizeof(szType), "更新2级属性");	
		break;

	//case MSG_ACK_FRIENDLIST:
	//	strcpy_s(szType, sizeof(szType), "好友名单");	
	//	break;

	case MSG_UPDATETIME:
		strcpy_s(szType, sizeof(szType), "更新世界时间");	
		break;

	case MSG_ACK_ECTYPEMAP_INFO:
		strcpy_s(szType, sizeof(szType), "回应副本信息");	
		break;

	case MSG_REQ_FIRSTTIP:
		strcpy_s(szType, sizeof(szType), "事件提示");	
		break;

	case MSG_CHANGE_INTEGRAL:
		strcpy_s(szType, sizeof(szType), "积分改变");	
		break;

	case MSG_USESKILLHINTMESSAGE:
		strcpy_s(szType, sizeof(szType), "技能使用提示");	
		break;

	case MSG_CHANGE_FIGHTSTATE:
		strcpy_s(szType, sizeof(szType), "改变战斗状态");	
		break;

	case MSG_SKILL_BEGINCOLDDOWN:
		strcpy_s(szType, sizeof(szType), "技能冷却");	
		break;

	case MSG_INTONATESTART:
		strcpy_s(szType, sizeof(szType), "开始吟唱");	
		break;

	case MSG_INTONATEEND:
		strcpy_s(szType, sizeof(szType), "结束吟唱");	
		break;

	case MSG_INTONATEINTERRUPT:
		strcpy_s(szType, sizeof(szType), "吟唱中断");	
		break;


	case MSG_RET_CHANGESUBACTION:
		strcpy_s(szType, sizeof(szType), "回应坐下");	
		break;

	case MSG_KILLMONSTER:
		strcpy_s(szType, sizeof(szType), "获得经验");	
		break;

	case MSG_SHOWLEVELINFO:
		strcpy_s(szType, sizeof(szType), "人物升级");	
		break;

	case MSG_SHOWTEXT:
		strcpy_s(szType, sizeof(szType), "显示信息");	
		break;

	case MSG_SKILLCANCELD:
		strcpy_s(szType, sizeof(szType), "技能取消");	
		break;

	case MSG_EXIT:
		strcpy_s(szType, sizeof(szType), "退出游戏");	
		break;

	case MSG_ALLNPCONTHEMAP:
		strcpy_s(szType, sizeof(szType), "加载NPC信息");	
		break;

	case MSG_INTONATINGOVERTIME:
		strcpy_s(szType, sizeof(szType), "吟唱被攻击打断");	
		break;

	case MSG_SKILLSTATUS:
		strcpy_s(szType, sizeof(szType), "持久技能");	
		break;

	case MSG_CHANGEQUIPHP:
		strcpy_s(szType, sizeof(szType), "装备持久");	
		break;

	case MSG_UPDATEVISUALEQUIP:
		strcpy_s(szType, sizeof(szType), "更新装备");	
		break;

	case MSG_EQUIPCHANGED:
		strcpy_s(szType, sizeof(szType), "装备改变");	
		break;

	case MSG_CLEARSECONDEPASSWORDREQ:
		strcpy_s(szType, sizeof(szType), "请求强制清除密码");	
		break;

	case MSG_CLEARSECONDEPASSWORDACK:
		strcpy_s(szType, sizeof(szType), "回应强制清除密码");	
		break;

	case MSG_CASTINEFFICACYSKILL:
		strcpy_s(szType, sizeof(szType), "无效的技能");	
		break;

	//case MSG_GUILD_TELL_ONLINE:
	//	strcpy_s(szType, sizeof(szType), "通知会员上线");	
	//	break;

	case MSG_RELIVENEEDSILVER:
		strcpy_s(szType, sizeof(szType), "复活需要的钱");	
		break;

	case MSG_JUMP:
		strcpy_s(szType, sizeof(szType), "跳跃信息");	
		break;

	case MSG_TELLMAP_NPCQUEST:
		strcpy_s(szType, sizeof(szType), "NPC带有任务");	
		break;

	//case MSG_ACKGUILDINFO:
	//	strcpy_s(szType, sizeof(szType), "返回公会信息");	
	//	break;	

	//case MSG_FRIEND_ONLINE:
	//	strcpy_s(szType, sizeof(szType), "好友上线消息");	
	//	break;	

	case MSG_SCRIPT_SETHOTKEY:
		strcpy_s(szType, sizeof(szType), "设置热键");	
		break;

	//case MSG_GUILD_TELL_LEVEL:
	//	strcpy_s(szType, sizeof(szType), "公会职位变更");	
	//	break;	
		
	case MSG_CHANGE_SKILL:
		strcpy_s(szType, sizeof(szType), "添加技能");	
		break;
				
	case MSG_SEEDAMAGE:
		strcpy_s(szType, sizeof(szType), "单人或多人攻击");
		break;

	case MSG_ACKCREATECHAR:
		strcpy_s(szType, sizeof(szType), "创建角色");
		break;
	
	case MSG_ACKDRAGINFO:
		strcpy_s(szType, sizeof(szType), "药品信息");
		break;

	case MSG_HOLDSKILLEND:
		strcpy_s(szType, sizeof(szType), "维持技能结束");
		break;

	case MSG_ACK_CREATECHECKNAME:
		strcpy_s(szType, sizeof(szType), "检测同名");
		break;
    //case MSG_GUILD_TELL_DISMISS:
    //    strcpy_s(szType, sizeof(szType), "Ack解散公会");
    //    break;
    //case MSG_ACK_GUILD_MANIFESTO_INFO:
    //    strcpy_s(szType, sizeof(szType), "Ack公会宣言");
    //    break;
    //case MSG_GUILD_TELL_LEAVE:
    //    strcpy_s(szType, sizeof(szType), "离开公会");
    //    break;
    //case MSG_GUILD_QUERY_DISMISS:
    //    strcpy_s(szType, sizeof(szType), "Req解散公会宣言");
    //    break;
    //case MSG_REQ_GUILD_MANIFESTO_INFO:
    //    strcpy_s(szType, sizeof(szType), "Req公会宣言");
    //    break;
    //case MSG_GUILD_QUERY_LEAVE:
    //    strcpy_s(szType, sizeof(szType), "Req离开公会");
    //    break;
    //case MSG_GUILD_QUERY_CREATE:
    //    strcpy_s(szType, sizeof(szType), "创建公会");
    //    break;
    case MSG_BUFFSUPDATE:
        strcpy_s(szType, sizeof(szType), "更新Buff");
        break;
    case MSG_MAPINFOREADY:
        strcpy_s(szType, sizeof(szType), "场景地图信息完成");
        break;
    //case MSG_ACK_UPDATE_FRIENDINFO:
    //    strcpy_s(szType, sizeof(szType), "返回更新好友信息");
    //    break;
    case MSG_PLAY_EFFECT: // 播放特效
        strcpy_s(szType, sizeof(szType), "播放特效");
        break;
    case MSG_PLAYERMOVINGPOSTOSERVER:// client to server 发送玩家位置改变消息
        strcpy_s(szType, sizeof(szType), "C2S发送移动中玩家位置改变消息");
        break;

	default:
		//DEBUG_MSG("dwType = %d", dwType);
		sprintf_s(szType, sizeof(szType) - 1, "%u", dwType);
		break;
	}

	return szType;
}

void MessageInfo::UpdatePingChart(DWORD time)
{
    if (0 != time)
    {
        m_Histogram.Draw(time);
        if (time > 1000*2)
        {
            LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"PingTimeOutOf [%d] ms",2000);
        }
    }
}

//点击开始创建怪物 luo.qin 3.18
void MessageInfo::OnBnCreateMonster()
{
	// TODO: Add your control notification handler code here

	CString strBeginCreate = "开始创建怪物";
	CString strStopCreate = "暂停创建怪物";
	CButton* pCreateMonster = (CButton*)GetDlgItem(IDC_BUTTON_CREATEMONSTER);

	if ( m_bCreateMonster )						//m_bCreateMonster = true时，可以创建
	{
		int n_TotalNum = theApp.gBotApplication.GetTotalBotCount();
		int n_OnLineNum = theApp.gBotApplication.GetOnLineBotCount();
		if (  1/*CheckBotNum( n_TotalNum, n_OnLineNum ) */ )
		{

			pCreateMonster->SetWindowText( strStopCreate.GetBuffer() );
			m_bCreateMonster = false;
			theApp.gBotApplication.SetBCreateMonster( true );
		}
	}
	else
	{
		pCreateMonster->SetWindowText( strBeginCreate.GetBuffer() );
		m_bCreateMonster = true;
		theApp.gBotApplication.SetBCreateMonster( false );
	}

}

void MessageInfo::OnBnClickedChangeEquip()
{// 开始换装
	CString strBeginCreate = "开始换装";
	CString strStopCreate = "停止换装";
	CButton* pCreateMonster = (CButton*)GetDlgItem(IDC_BUTTON_CHANGEEQUIP);

	if ( m_bChangeEquip )
	{
		pCreateMonster->SetWindowText( strStopCreate.GetBuffer() );
		m_bChangeEquip = false;
		theApp.gBotApplication.SetBChangeEquip( true );
	}
	else
	{
		pCreateMonster->SetWindowText( strBeginCreate.GetBuffer() );
		m_bChangeEquip = true;
		theApp.gBotApplication.SetBChangeEquip( false );
	}
}

void MessageInfo::OnBnClickedButtonRandride()
{
	// TODO: Add your control notification handler code here
	CString strBeginCreate = "开始随机骑马";
	CString strStopCreate = "停止随机骑马";
	CButton* pCreateMonster = (CButton*)GetDlgItem(IDC_BUTTON_RANDRIDE);

	if ( m_bRandRide )						   //m_bRandRide = true时，可以创建
	{

		pCreateMonster->SetWindowText( strStopCreate.GetBuffer() );
		m_bRandRide = false;
		theApp.gBotApplication.SetBRandRide( true );

	}
	else
	{
		pCreateMonster->SetWindowText( strBeginCreate.GetBuffer() );
		m_bRandRide = true;
		theApp.gBotApplication.SetBRandRide( false );
	}
}

void MessageInfo::OnPreparesuit()
{
	// TODO: Add your control notification handler code here
	GMsgPrepareSuit msg;
	theApp.gBotApplication.PushMessage(&msg);
}

void MessageInfo::OnBnClickedButtonFight()
{
	// TODO: Add your control notification handler code here

	CString strBeginCreate = "开始国战";
	CString strStopCreate = "停止国战";
	CButton* pCreateMonster = (CButton*)GetDlgItem( IDC_BUTTON_FIGHT );

	if ( m_bCountryFight )						   //m_bRandRide = true时，可以创建
	{

		pCreateMonster->SetWindowText( strStopCreate.GetBuffer() );
		m_bCountryFight = false;
		theApp.gBotApplication.SetBCountryFight( true );

	}
	else
	{
		pCreateMonster->SetWindowText( strBeginCreate.GetBuffer() );
		m_bCountryFight = true;
		theApp.gBotApplication.SetBCountryFight( false );
	}

}