// AddFrm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameBot.h"
#include "AddFrm.h"
#include "direct.h"
#include "LevelExperienceConfig.h"
#include "LogFileObjectName.h"
// CAddFrm �Ի���

IMPLEMENT_DYNAMIC(CAddFrm, CDialog)

CAddFrm::CAddFrm(CWnd* pParent /*=NULL*/)
	: CDialog(CAddFrm::IDD, pParent)
{
	m_vecErrorLog.clear();
}

CAddFrm::~CAddFrm()
{
}

void CAddFrm::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_ID, m_cmbIDStart);
    DDX_Control(pDX, IDC_COMBO_TYPE, m_cmbBotType);
    DDX_Control(pDX, IDC_COMBO_NUM, m_cmbBotNum);
    DDX_Control(pDX, IDC_EDIT_TIME, m_editTime);
    DDX_Control(pDX, IDC_EDIT_STEP, m_editMoveStep);
    DDX_Control(pDX, IDC_ED_ROBNUM, m_TolalRototNumber);
    DDX_Control(pDX, IDC_ED_ROBNUM2, m_totalOnlineNum);
    DDX_Control(pDX, IDC_STATIC_POINT, m_MapPoint);
    DDX_Control(pDX, IDC_STATIC_MAP, m_Map);
    DDX_Control(pDX, IDC_COMBO1, m_ComboError);
    DDX_Control(pDX, IDC_EDIT1, m_BotID);
    DDX_Control(pDX, IDC_EDIT2, m_MsgType);
    DDX_Control(pDX, IDC_EDIT3, m_MsgFlag);
    DDX_Control(pDX, IDC_EDIT4, m_MsgLength);
    DDX_Control(pDX, IDC_EDIT6, m_ErrorInfo);
    DDX_Control(pDX, IDC_EDIT5, m_ErrorFile);
    DDX_Control(pDX, IDC_EDIT7, m_Account);
    DDX_Control(pDX, IDC_EDIT8, m_Count);
    DDX_Control(pDX, IDC_ED_ROBNUM5, m_NotInGame);
    DDX_Control(pDX, IDC_ED_ROBNUM3, m_AttackCount);
    DDX_Control(pDX, IDC_ED_ROBNUM4, m_MoveCount);
    DDX_Control(pDX, IDC_LIST3, m_listMapDistributing);
    DDX_Control(pDX, IDC_COMBO_NUM2, m_comboMapList);
    DDX_Control(pDX, IDC_EDIT55, m_editPosX);
    DDX_Control(pDX, IDC_EDIT12, m_editPosY);
    DDX_Control(pDX, IDC_EDIT_TIME2, m_editRadius);
    DDX_Control(pDX, IDC_COMBO_TYPE2, m_comboAddSpace);
    DDX_Control(pDX, IDC_COMBO_TYPE3, m_comboPerCount);
    DDX_Control(pDX, IDC_EDIT_TIME3, m_editFlySpace);
    DDX_Control(pDX, IDC_COMBO_NUM3, m_comboCount);
    DDX_Control(pDX, IDC_COMBO_TYPE4, m_comboScript);
    //DDX_Control(pDX, IDC_EDIT11, m_BotSpace);
    DDX_Control(pDX, IDC_EDIT_MOVE_RANGE, m_BotMoveRange);
    DDX_Control(pDX, IDC_COMBO_SKILL_ID, m_cmbSkillID);
    DDX_Control(pDX, IDC_LUASCRIPT_FILE, m_cmbLuaFile);
}


BEGIN_MESSAGE_MAP(CAddFrm, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_ADD, &CAddFrm::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddFrm::OnBnClickedButtonOpenErrorFile)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddFrm::OnCbnSelchangeComboSelectErrorLog)
	ON_STN_DBLCLK(IDC_STATIC_POINT, &CAddFrm::OnStnDblclickStaticPoint)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, &CAddFrm::OnCbnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_ADD2, &CAddFrm::OnBnClickedButtonEditArea)
	ON_NOTIFY(NM_RCLICK, IDC_LIST3, &CAddFrm::OnNMRclickListMapInfo)
	ON_COMMAND(ID_DISPERSE, &CAddFrm::OnDisperse)
    ON_BN_CLICKED(IDC_BTN_ATTACK, &CAddFrm::OnBnClickedBtnAttack)
    ON_BN_CLICKED(IDC_PAUSE_ADDBOT, &CAddFrm::OnPauseAddbot)
    ON_BN_CLICKED(IDC_PLAYSKILL, &CAddFrm::OnPlaySkill)
    //ON_BN_CLICKED(IDC_CHANGE_BOTSPACE, &CAddFrm::OnChangeBotSpace)
    ON_BN_CLICKED(IDC_BOT_MOVE, &CAddFrm::OnBotMoveRange)
    ON_BN_CLICKED(IDC_BOT_ATTACK, &CAddFrm::OnBotAttack)
    ON_BN_CLICKED(IDC_BOT_RIDE, &CAddFrm::OnBotRide)
    ON_BN_CLICKED(IDC_RELOAD_LUASCRIPT, &CAddFrm::OnBnClickedReloadLuascript)
END_MESSAGE_MAP()


//bool CAddFrm::bIsChangeStartID = false;
//int  CAddFrm::nOldStartID = 1000; // Ĭ�ϳ�ʼIDΪ1000
// CAddFrm ��Ϣ�������

BOOL CAddFrm::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    m_cmbBotNum.AddString(_T("1"));
    m_cmbBotNum.AddString(_T("10"));
    m_cmbBotNum.AddString(_T("100"));
    m_cmbBotNum.AddString(_T("500"));
    m_cmbBotNum.AddString(_T("1000"));
    m_cmbBotNum.AddString(_T("1200"));
    m_cmbBotNum.AddString(_T("1500"));
    m_cmbBotNum.AddString(_T("2000"));
    m_cmbBotNum.AddString(_T("2500"));
    m_cmbBotNum.AddString(_T("3000"));
    m_cmbBotNum.SetCurSel(4);

	m_cmbIDStart.AddString(_T("1000"));
    m_cmbIDStart.AddString(_T("1500"));
	m_cmbIDStart.AddString(_T("2000"));
	m_cmbIDStart.AddString(_T("2500"));
	m_cmbIDStart.AddString(_T("3000"));
	m_cmbIDStart.AddString(_T("3500"));
	m_cmbIDStart.AddString(_T("4000"));
	m_cmbIDStart.AddString(_T("4500"));
	m_cmbIDStart.AddString(_T("5000"));
	m_cmbIDStart.AddString(_T("5500"));
    m_cmbIDStart.AddString(_T("6000"));
    m_cmbIDStart.AddString(_T("6500"));
    m_cmbIDStart.AddString(_T("7000"));
    m_cmbIDStart.AddString(_T("7500"));
    m_cmbIDStart.AddString(_T("8000"));
    m_cmbIDStart.AddString(_T("8500"));
    m_cmbIDStart.AddString(_T("9000"));
    m_cmbIDStart.AddString(_T("9500"));
    m_cmbIDStart.AddString(_T("10000"));

	m_cmbIDStart.SetCurSel(0);

    // ��ʼ�������˼�� Edit
    //m_BotSpace.SetWindowText(_T("6"));
    // ��ʼ���ƶ����� Edit
    m_BotMoveRange.SetWindowText(_T("6"));
    // ��ʼ������ID ��Ͽ�
    m_cmbSkillID.AddString(_T("1030")); // ����������
    //m_cmbSkillID.AddString(_T("1034"));
    m_cmbSkillID.SetCurSel(0);
    // ��ʼ�����������Lua�ű��ļ�
    m_cmbLuaFile.AddString(_T("MatrixBot.lua")); // path = ..\\Data\\RobotScript\\MatrixBot.lua
    m_cmbLuaFile.SetCurSel(0);

	static const int s_nTypeCount = sizeof(s_pBotType) / sizeof(char*);
	for (int i = 0; i < s_nTypeCount; ++i)
	{
        if (strcmp(s_pBotType[i], "") != 0)
        {
            m_cmbBotType.AddString(s_pBotType[i]);    
        }		
	}
	m_cmbBotType.SetCurSel(16);

	m_editTime.SetWindowText("120");//����ʱ��
	m_editFlySpace.SetWindowText("120");//���м��ʱ��

	m_editMoveStep.SetWindowText("500");//�ƶ�ʱ����

	//���������ʱ����
    m_comboAddSpace.AddString("10");
    m_comboAddSpace.AddString("100");
	m_comboAddSpace.AddString("1000");
	m_comboAddSpace.AddString("10000");
	m_comboAddSpace.SetCurSel(0);

	m_comboPerCount.AddString("1");
    m_comboPerCount.AddString("10");
    m_comboPerCount.AddString("20");
    m_comboPerCount.AddString("50");
	m_comboPerCount.AddString("100");
	m_comboPerCount.SetCurSel(1);

	//��ӵ�ͼ��Ϣ
	m_comboMapList.AddString("��ָ������");
	int nCount = theMapConfig.MapDataCount();
	for (int i = 0; i < nCount; ++i)
	{
		MapConfig::MapData* pMapData = theMapConfig.GetMapDataByIndex(i);
		if (pMapData != NULL)
		{
			if (!pMapData->MapName.empty() && !pMapData->IsEctypeMap())
			{
				m_comboMapList.AddString(pMapData->MapName.c_str());
			}
		}
		else
		{
			m_comboMapList.AddString("δ֪��ͼ��Ϣ");
		}
	}
	m_comboMapList.SetCurSel(0);

	m_editPosX.SetWindowText("300");
	m_editPosY.SetWindowText("300");
	m_editRadius.SetWindowText("300");


	m_comboCount.AddString("1");
	m_comboCount.AddString("100");
	m_comboCount.AddString("200");
	m_comboCount.SetCurSel(0);

	ShowEdit(m_Count, 0);

	////////////////////////////////////////////////////////////////
	RECT rect;
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	int nWidth = 0;
	int iIndex = 0;
	/////////////////////////////////////////////////////////////////////
	m_listMapDistributing.SetExtendedStyle(dwStyle);

	m_listMapDistributing.GetClientRect(&rect);
	nWidth = rect.right - rect.left;

	m_listMapDistributing.InsertColumn(iIndex++, _T("   ��ͼ"), 0, (65 * nWidth / 100));
	m_listMapDistributing.InsertColumn(iIndex++, _T("   ����"), 0, (35 * nWidth / 100));


	theApp.UpdataAddFrmScriptCombox();

    // ��ʼ���ǻ�δ���ʱ���Ƚ������Ϊ������
    CButton* addButton = (CButton*)GetDlgItem(IDC_BUTTON_ADD);
    addButton->EnableWindow(FALSE);

    bPause = true;    //��ӻ�������ͣ�ͼ������Ʊ�������
    bPlaySkill = true;    // �ͷż��ܿ��ƿ���
    bBotMove = true;    // �������ƶ����Ƴ�ʼ��
    nMoveRange = 6; // Ĭ�ϵ��ƶ�����
    bPlayAttack = true;    // �����˹������ƿ��س�ʼ��
    bRide = true;    // ������������

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}


void CAddFrm::OnBnClickedButtonAdd()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSelect = m_comboScript.GetCurSel();
	if (nSelect == 0)  // ��ʹ�ýű�
	{
		CString strNum;
		CString strStartID;
		int     nType;
		CString strSpaceTime;
		CString strPerCount;
		CString strOnlineTime;
		CString strFlySpace;
		CString strMoveStep;
        CString strBotSpace; // �����˼��

		m_cmbBotNum.GetWindowText(strNum);
		m_cmbIDStart.GetWindowText(strStartID);
		nType = m_cmbBotType.GetCurSel();
        if (nType == Bot_Script)
        {
            MessageBox("��ʱ������ӽű�������");
            return;
        }
		m_comboAddSpace.GetWindowText(strSpaceTime);
		m_comboPerCount.GetWindowText(strPerCount);
		m_editTime.GetWindowText(strOnlineTime);
		m_editFlySpace.GetWindowText(strFlySpace);
		m_editMoveStep.GetWindowText(strMoveStep);
        //m_BotSpace.GetWindowText(strBotSpace); // �õ������˼��

        GMsgAddRobot addRobot;

        CString CurMapName;
        m_comboMapList.GetWindowText(CurMapName);
        MapConfig::MapData* pMapDate = theMapConfig.GetMapDataByName(CurMapName);
        if (NULL != pMapDate)
        { addRobot.m_xAddInfo.xAreaInfo.nMap = pMapDate->Id;  }
        else
        { addRobot.m_xAddInfo.xAreaInfo.nMap = -1; }

		//xAreaInfo.nMap = m_comboMapList.GetCurSel() - 1;
		addRobot.m_xAddInfo.xAreaInfo.xPoint.x = theApp.GetInt( m_editPosX,   0 );
		addRobot.m_xAddInfo.xAreaInfo.xPoint.y = theApp.GetInt( m_editPosY,   0 );
		addRobot.m_xAddInfo.xAreaInfo.nRadius  = theApp.GetInt( m_editRadius, 0 );
		addRobot.m_xAddInfo.nCount = atoi(strNum.GetBuffer());
		addRobot.m_xAddInfo.nStartId = atoi(strStartID.GetBuffer());
		addRobot.m_xAddInfo.nType = nType;
		addRobot.m_xAddInfo.nSpaceTime = atoi(strSpaceTime.GetBuffer());
		addRobot.m_xAddInfo.nPerCount = atoi(strPerCount.GetBuffer());
		addRobot.m_xAddInfo.nOnlineTime = atoi(strOnlineTime.GetBuffer());
		addRobot.m_xAddInfo.nFlySpace = atoi(strFlySpace.GetBuffer());
		addRobot.m_xAddInfo.nMoveStep = atoi(strMoveStep.GetBuffer());
        //addRobot.nBotSpace = atoi(strBotSpace.GetBuffer()); // ���

		theApp.gBotApplication.PushMessage( &addRobot );        
        // ����10����¼�߳�
        /*
        if (!theApp.AlreadyCreateThread )
        {
            for (int i = 0;i<xAddInfo.nPerCount;++i)
            {
                _beginthread(BotApplication::UpdateToLoginQueue,0,&(theApp.m_BotServer));
            }
            theApp.AlreadyCreateThread  = false;
        }
        */
	}
	else
	{
		CString strScript = "";
		m_comboScript.GetWindowText(strScript);

		CString strFile = "";
		strFile.Format("%s\\%s", Script_Path, strScript);
		theApp.LoadScript(strFile.GetBuffer(), theApp.gBotApplication.m_vecAddInfo);
	}

 //   theApp.m_BotServer.AddBot( atoi(strNum.GetBuffer()), atoi(strStartID.GetBuffer()), nType, atoi(strOnlineTime.GetBuffer()), atoi(strMoveStep.GetBuffer()), &xAreaInfo);

	if (theApp.m_xTatolMsgStatistician.GetStartTime() == 0)
	{
		theApp.m_xTatolMsgStatistician.SetStartTime(HQ_TimeGetTime());
	}
}

BOOL CAddFrm::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			OnBnClickedButtonAdd();
			return TRUE;
		case VK_ESCAPE:
			return TRUE;		
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CAddFrm::AddErrorLog(Error_Log_ &stErrorLog)
{
	m_vecErrorLog.push_back(stErrorLog);

	ShowEdit(m_Count, m_vecErrorLog.size());

	CString strError;

	strError.Format("%s %s %d %d %d", stErrorLog.strInfo.c_str(), stErrorLog.strAccount.c_str(), stErrorLog.nMsgType, stErrorLog.nMsgFlag, stErrorLog.nMsgLength);
	m_ComboError.AddString(strError.GetBuffer());

	m_ComboError.SetCurSel(m_vecErrorLog.size() - 1);

	ShowerrorLog(stErrorLog);
}

void CAddFrm::ShowerrorLog(Error_Log_ &stErrorLog)
{

	ShowEdit(m_BotID, stErrorLog.nBotID);
	m_Account.SetWindowText(stErrorLog.strAccount.c_str());
	ShowEdit(m_MsgType, stErrorLog.nMsgType);
	ShowEdit(m_MsgFlag, stErrorLog.nMsgFlag);
	ShowEdit(m_MsgLength, stErrorLog.nMsgLength);
	m_ErrorInfo.SetWindowText(stErrorLog.strInfo.c_str());
	m_ErrorFile.SetWindowText(stErrorLog.strFile.c_str());
}

void CAddFrm::ShowEdit(CEdit &xEdit, int nValue)
{
	CString strValue = "";
	strValue.Format("%d", nValue);

	xEdit.SetWindowText(strValue.GetBuffer());
}

void CAddFrm::OnBnClickedButtonOpenErrorFile()
{
	// TODO: Add your control notification handler code here

	CString strFileName;

	m_ErrorFile.GetWindowText(strFileName);

	if (strFileName.IsEmpty())
	{
		return;
	}

	char szProcPath[_MAX_PATH] = {0};
	char szDir[_MAX_DIR] = {0};
	char szDirve[_MAX_DRIVE] = {0};

	::GetModuleFileName(NULL, szProcPath, sizeof(szProcPath));

	_tsplitpath_s(szProcPath, szDirve, sizeof(szDirve), szDir, sizeof(szDir), NULL, 0, NULL, 0);
	strFileName.Format("explorer.exe /select, %s%s%s\\%s", szDirve, szDir, ERROR_LOG_PATH, strFileName.GetBuffer());

	::WinExec(strFileName.GetBuffer(), SW_SHOWNORMAL);
}

void CAddFrm::OnCbnSelchangeComboSelectErrorLog()
{
	// TODO: Add your control notification handler code here
	
	int nIndex = m_ComboError.GetCurSel();

	if (nIndex == -1 || nIndex >= m_vecErrorLog.size())
	{
		return;
	}

	ShowerrorLog(m_vecErrorLog[nIndex]);
}

void CAddFrm::OnStnDblclickStaticPoint()
{
	// TODO: Add your control notification handler code here

	theApp.ShowBigMap();

}

void CAddFrm::OnCbnSelchangeComboType()
{
	// TODO: Add your control notification handler code here
	int nIndex = m_cmbBotType.GetCurSel();
	if(nIndex==Bot_PlatformTest)
	{
		AfxMessageBox("��֧��Bot_PlatformTest������");
		return ;
	}

	if (nIndex == Bot_Normal)
	{
		m_comboMapList.SetCurSel(0);
	}
}

void CAddFrm::OnBnClickedButtonEditArea()
{
	// TODO: Add your control notification handler code here
    UpdateData(FALSE);
	static SAreaInfo xAreaInfo;

    CString CurMapName;
    m_comboMapList.GetWindowText(CurMapName);
    if (CurMapName == "��ָ������")
        return;
    MapConfig::MapData* pMapDate = theMapConfig.GetMapDataByName(CurMapName);
    if (NULL == pMapDate)
    {
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"ѡ���˴���ĵ�ͼ %s ",CurMapName.GetBuffer(CurMapName.GetLength()));
        return;
    }
    else
        xAreaInfo.nMap = pMapDate->Id;
    
	xAreaInfo.xPoint.x  = theApp.GetInt(m_editPosX, 0);
	xAreaInfo.xPoint.y  = theApp.GetInt(m_editPosY, 0);
	xAreaInfo.nRadius   = theApp.GetInt(m_editRadius, 0);

	CString strCount = "";
	m_comboCount.GetWindowText(strCount);

	theApp.EditAttackAreaInfo(&xAreaInfo, atoi(strCount.GetBuffer()));
}

void CAddFrm::OnNMRclickListMapInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	POSITION pos = m_listMapDistributing.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_listMapDistributing.GetNextSelectedItem(pos);
		if (nIndex != -1)
		{
			CMenu menu;
			CPoint pt;
			GetCursorPos(&pt);
			menu.LoadMenu(IDR_MENU_DISPERSE);
			menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);	
		}
	}

	*pResult = 0;
}

void CAddFrm::OnDisperse()
{
	// TODO: Add your command handler code here	
	POSITION pos = m_listMapDistributing.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_listMapDistributing.GetNextSelectedItem(pos);
		if (nIndex != -1)
		{
			CString strMap  = m_listMapDistributing.GetItemText(nIndex, 0);		//��ͼ 
			int nCount      = theApp.GetListItemInt(m_listMapDistributing, nIndex, 1, 0);					//����

			theApp.DisPerseBot(strMap.GetBuffer(), nCount);
		}
	}

}

void CAddFrm::OnBnClickedBtnAttack()
{
    // TODO: Add your control notification handler code here
    theApp.bAttack = true;
}

void CAddFrm::OnPauseAddbot()
{
    // TODO: Add your control notification handler code here
    CButton* pauseButton = (CButton*)GetDlgItem(IDC_PAUSE_ADDBOT);
    GMsgPauseBot msg;
    CString strPause = "��ͣ���";
    CString strContinue = "�������";
    if (bPause)
    {
        msg.bIsPause = true;
        pauseButton->SetWindowText(strContinue.GetBuffer());
        theApp.gBotApplication.PushMessage(&msg);
        bPause = false;
    }
    else
    {
        msg.bIsPause = false;
        pauseButton->SetWindowText(strPause.GetBuffer());
        theApp.gBotApplication.PushMessage(&msg);
        bPause = true;
    }
}

void CAddFrm::OnPlaySkill()
{
    // TODO: Add your control notification handler code here
    CButton* PlaySkillButton = (CButton*)GetDlgItem(IDC_PLAYSKILL);
    GMsgPlaySkill msg;
    CString strPlaySkill = "�ͷ�";
    CString strStopPlaySkill = "��ͣ";
    CString strSkillID; // ����ID
    int nIndex = m_cmbSkillID.GetCurSel();
    m_cmbSkillID.GetLBText(nIndex, strSkillID);
    //m_cmbSkillID.GetWindowText(strSkillID); //�õ���ǰ�ļ���ID
    if ( bPlaySkill )
    {
        msg.nSkillID = atoi(strSkillID);
        msg.bIsPlaySkill = true;
        PlaySkillButton->SetWindowText(strStopPlaySkill.GetBuffer());
        theApp.gBotApplication.PushMessage(&msg);
        bPlaySkill = false;
    }
    else
    {
        msg.nSkillID = atoi(strSkillID);
        msg.bIsPlaySkill = false;
        PlaySkillButton->SetWindowText(strPlaySkill.GetBuffer());
        theApp.gBotApplication.PushMessage(&msg);
        bPlaySkill = true;
    }
}

//void CAddFrm::OnChangeBotSpace()
//{
//    // TODO
//}

void CAddFrm::OnBotMoveRange() //�������ƶ�����
{
    // TODO: Add your control notification handler code here
    CButton* pMoveButton = (CButton*)GetDlgItem(IDC_BOT_MOVE);
    CString strMoveRange;
    m_BotMoveRange.GetWindowText(strMoveRange);
    GMsgBotMoving msg;
    nMoveRange = atoi(strMoveRange);
    if (nMoveRange > 50) // ���ܳ���50����ֹbot�ƶ�����ͼ
    {
        AfxMessageBox(_T("Ϊ��ֹ�����˳���ͼ���˴����벻�ܴ���50��"));
        return;
    }

    CString strMoving = "�ƶ�";
    CString strStopMoving = "��ͣ";
    if ( bBotMove )
    {
        msg.bIsMove = true;
        msg.nMoveRange = nMoveRange;
        theApp.gBotApplication.PushMessage(&msg);
        pMoveButton->SetWindowText(strStopMoving.GetBuffer());
        bBotMove = false;
    }
    else
    {
        msg.bIsMove = false;
        msg.nMoveRange = nMoveRange;
        theApp.gBotApplication.PushMessage(&msg);
        pMoveButton->SetWindowText(strMoving.GetBuffer());
        bBotMove = true;
    }
}

void CAddFrm::OnBotAttack()
{
    // TODO: Add your control notification handler code here
    CButton* pPlayAttackButton = (CButton*)GetDlgItem(IDC_BOT_ATTACK);
    GMsgBotPlayAttack msg;
    CString strPlayAttack = "��ʼ����";
    CString strStopPlayAttack = "��ͣ����";
    if ( bPlayAttack )
    {
        msg.bIsPlayAttack = true;
        theApp.gBotApplication.PushMessage(&msg);
        pPlayAttackButton->SetWindowText(strStopPlayAttack.GetBuffer());
        bPlayAttack = false;
    }
    else
    {
        msg.bIsPlayAttack = false;
        theApp.gBotApplication.PushMessage(&msg);
        pPlayAttackButton->SetWindowText(strPlayAttack.GetBuffer());
        bPlayAttack = true;
    }
}

void CAddFrm::OnBotRide()
{
    // TODO: Add your control notification handler code here
    //CButton* pRideButton = (CButton*)GetDlgItem(IDC_BOT_RIDE);
    GMsgBotRide msg;
    //CString strRide = "����";
    //CString strStopRide = "����";
    //if (bRide)
    //{
        // ����ֹͣ�ƶ�
    if ( !bBotMove )
    {
        bBotMove = false;
        OnBotMoveRange(); // ����ֹͣ�ƶ�����
    }

    msg.bIsRide = true;
    theApp.gBotApplication.PushMessage(&msg);
        //pRideButton->SetWindowText(strStopRide.GetBuffer());
        //bRide = false;
    //}
    //else
    //{
    //    msg.bIsRide = true;
    //    theApp.gBotApplication.PushMessage(&msg);
    //    pRideButton->SetWindowText(strRide.GetBuffer());
    //    bRide = true;
    //}
}

void CAddFrm::OnBnClickedReloadLuascript()
{
    // ���¼���Lua�ű��ļ�
    GMsgReLoadLuaScript msg;
    msg.bIsReloadLuaScript = true;
    theApp.gBotApplication.PushMessage(&msg);
}