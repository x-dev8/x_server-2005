// QuestEditDlg.cpp : ʵ���ļ�
//

#include "QuestEditor.h"
#include "QuestEditorDlg.h"

#include "StringFileChange.h"
#include "NpcFileChange.h"
#include "QuestFind.h"
#include "DropItemDialog.h"


#define SaveShow_Timer_Id 0x1

#define Default_Grund_Color	RGB(255, 255, 255)
#define Green_Ground_Color	RGB(0, 255, 0)
#define Red_Ground_Color	RGB(255, 0, 0)
#define Text_Color			RGB(0, 0, 0)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CQuestEditDlg �Ի���



CQuestEditDlg::CQuestEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuestEditDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pxDropItemDialog = NULL;
	m_pxListCtrl = NULL;

	m_nItem = -1;
	m_nSubItem = -1;

	m_pxQuestFind = NULL;

	m_nShowFindId = -1;
	m_strQuestFile.clear();

	m_strDropItemFile.Empty();

	m_bWindowsTop = false;
}

void CQuestEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listProperty);
	DDX_Control(pDX, IDC_LIST4, m_listReward);
	DDX_Control(pDX, IDC_LIST6, m_listPreRequiement);
	DDX_Control(pDX, IDC_LIST7, m_listPostRequiement);
	DDX_Control(pDX, IDC_TREE1, m_xTreeQuest);
	DDX_Control(pDX, IDC_STATIC_PREREQUIEMENT, m_staticPre);
	DDX_Control(pDX, IDC_STATIC_POST, m_staticPost);
	DDX_Control(pDX, IDC_STATIC_REWARD, m_staticReward);
	DDX_Control(pDX, IDC_STATIC_SAVE, m_staticSave);
	DDX_Control(pDX, IDC_CHECK1, m_checkBatch);
}

BEGIN_MESSAGE_MAP(CQuestEditDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	
	ON_NOTIFY(NM_CLICK, IDC_LIST4, &CQuestEditDlg::OnNMClickListReward)
	ON_NOTIFY(NM_CLICK, IDC_LIST6, &CQuestEditDlg::OnNMClickListPreRequiement)
	ON_NOTIFY(NM_CLICK, IDC_LIST7, &CQuestEditDlg::OnNMClickListPostRequiement)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CQuestEditDlg::OnNMClickListProprety)
	

	ON_REGISTERED_MESSAGE(WM_XLISTCTRL_COMBO_SELECTION, OnComboSelection)
	ON_REGISTERED_MESSAGE(WM_XLISTCTRL_CHECKBOX_CLICKED, OnCheckbox)
	ON_REGISTERED_MESSAGE(WM_XLISTCTRL_EDIT_END, OnEditEnd)
	ON_COMMAND(ID_FILE_LOAD, &CQuestEditDlg::OnFileLoadQuestFile)
	ON_COMMAND(ID_FILE_SAVEQUEST, &CQuestEditDlg::OnFileSaveQuestFile)
	ON_COMMAND(ID_FILE_EXIT, &CQuestEditDlg::OnFileExit)
	ON_COMMAND(ID_FILE_FIND, &CQuestEditDlg::OnFileFind)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CQuestEditDlg::OnNMClickTreeItem)
	ON_WM_DESTROY()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CQuestEditDlg::OnTvnSelchangedTreeQuest)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST7, &CQuestEditDlg::OnNMDClickListPostRequiement)
	ON_NOTIFY(NM_RCLICK, IDC_LIST7, &CQuestEditDlg::OnNMRclickListPostRequeiment)
	ON_COMMAND(ID_DELETE, &CQuestEditDlg::OnDelete)
	ON_WM_TIMER()
	ON_COMMAND(ID_STRING_CHANGE, &CQuestEditDlg::OnStringChange)
	ON_COMMAND(ID_NPC_CHANGE, &CQuestEditDlg::OnNpcChange)
END_MESSAGE_MAP()


// CQuestEditDlg ��Ϣ�������

BOOL CQuestEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	InitInformation();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CQuestEditDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQuestEditDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{		

		CDialog::OnPaint();	
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CQuestEditDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CQuestEditDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	SafeDelete(m_pxQuestFind);
	SafeDelete(m_pxDropItemDialog);
}


BOOL CQuestEditDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		//SetKeywParamSelectText(pMsg->wParam);	
		
		switch (pMsg->wParam)
		{
		case VK_RETURN:
		case VK_ESCAPE:
			return TRUE;

		case VK_F3:			//������һ��
			ShowNextFindQuest();
			break;
		//case 'A':		//Ctrl + A
		//	if ((GetKeyState(VK_CONTROL) & 0x8000) != 0)
		//	{
		//		OnFileSaveAt();
		//	}			
		//	break;

		case 'B':		//Ctrl + B
			if (IsKeyDown(VK_CONTROL))
			{
				m_checkBatch.SetCheck(!m_checkBatch.GetCheck());
			}			
			break;

		case 'E':		//Ctrl + E
			if (IsKeyDown(VK_CONTROL))
			{
				SetListItemCanEdit();
			}			
			break;

		case 'S':		//Ctrl + S
			if (IsKeyDown(VK_CONTROL))
			{
				OnFileSaveQuestFile();
			}
			break;

		case 'L':		//Ctrl + L
			if (IsKeyDown(VK_CONTROL))
			{
				OnFileLoadQuestFile();
			}
			break;

		case 'F':		//Ctrl + F
			if (IsKeyDown(VK_CONTROL))
			{			
				ShowFindDialog();
			}
			break;

		case 'Q':		//Ctrl + Q
			if (IsKeyDown(VK_CONTROL))
			{
				OnFileExit();
			}			
			break;

		case 'T':		//Ctrl + T
			if (IsKeyDown(VK_CONTROL))
			{
				SetWindowTop();				
			}			
			break;

		case 'X':		//Ctrl + X
			if (IsKeyDown())
			{			
				DeleteListItem();
			}
			break;
		case 'Z':		//Ctrl + Z
			if (IsKeyDown(VK_CONTROL))
			{			
				AddListItem();
			}
			break;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

bool CQuestEditDlg::IsKeyDown(UINT nKey)
{
	return (GetKeyState(nKey) & 0x8000);
}

void CQuestEditDlg::SetWindowTop()
{
	if (!m_bWindowsTop)
	{
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		m_bWindowsTop = true;
	}
	else
	{
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		m_bWindowsTop = false;
	}
}


void CQuestEditDlg::SetCurrentWorkDir()
{
	//���õ�ǰ����Ŀ¼
	char szProcPath[_MAX_PATH] = "";
	char szDirve[_MAX_DRIVE] = "";
	char szDir[_MAX_PATH] = "";

	::GetModuleFileName(NULL, szProcPath, sizeof(szProcPath));


	_tsplitpath(szProcPath, szDirve, szDir, NULL, NULL);

	char szWorkDir[_MAX_PATH] = "";
	sprintf_s(szWorkDir, sizeof(szWorkDir), "%s%s", szDirve, szDir);	

	SetCurrentDirectory(szWorkDir);
}

void CQuestEditDlg::ShowFindDialog()
{
	if (m_pxQuestFind == NULL)
	{
		m_pxQuestFind = new QuestFind(this);
		m_pxQuestFind->Create(IDD_DIALOG_FIND, this);
		m_pxQuestFind->InitInformation();
	}

	if (m_pxQuestFind != NULL)
	{
		m_pxQuestFind->ShowWindow(SW_SHOW);
	}
}


void CQuestEditDlg::AddListItem()
{
	HWND hWnd = GetFocus()->m_hWnd;
	if (hWnd == m_listPreRequiement.m_hWnd)
	{
		AddQuestRequiremenetList(m_listPreRequiement, m_xStringArray[Enum_Requirement]);
	}
	else if (hWnd == m_listPostRequiement.m_hWnd)
	{
		AddQuestRequiremenetList(m_listPostRequiement, m_xStringArray[Enum_Requirement]);
	}
	else if (hWnd == m_listReward.m_hWnd)
	{
		AddQuestRewardList(m_listReward, m_xStringArray[Enum_Reward]);
	}
}

void CQuestEditDlg::DeleteListItem()
{
	HWND hWnd = GetFocus()->m_hWnd;
	if (hWnd == m_listPreRequiement.m_hWnd)
	{
		int nIndex = m_listPreRequiement.GetCurSel();
		if (nIndex != -1)
		{
			m_listPreRequiement.DeleteItem(nIndex);
		}
	}
	else if (hWnd == m_listPostRequiement.m_hWnd)
	{
		int nIndex = m_listPostRequiement.GetCurSel();
		if (nIndex != -1)
		{
			//ɾ�� ��Ʒ�������
			OnDelete();
			//m_listPostRequiement.DeleteItem(nIndex);

			if (m_pxDropItemDialog != NULL)
			{
				m_pxDropItemDialog->ShowWindow(SW_HIDE);
			}
		}
	}
	else if(hWnd == m_listReward.m_hWnd)
	{
		int nIndex = m_listReward.GetCurSel();
		if (nIndex != -1)
		{
			m_listReward.DeleteItem(nIndex);
		}
	}
	else if (hWnd == m_xTreeQuest.m_hWnd)
	{
		HTREEITEM hItem = m_xTreeQuest.GetSelectedItem();
		if (hItem != NULL && hItem != m_xTreeQuest.GetRootItem())
		{			
			CString strId = m_xTreeQuest.GetItemText(hItem);
			int nId = atoi(strId.GetBuffer());

			if (DeleteQuestFile(nId))
			{
				theQuestInfo.RemoveQuest(nId);
				m_xTreeQuest.DeleteItem(hItem);
				m_staticSave.SetWindowText("ɾ���ɹ���");

				SetTimer(SaveShow_Timer_Id, 2500, NULL); //2.5��������ʾ
			}			
		}
	}
}

bool CQuestEditDlg::DeleteQuestFile(int nId)
{
	char szInfo[128] = "";
	sprintf_s(szInfo, sizeof(szInfo) - 1, "����Ҫɾ��IDΪ��%d��������ص������ļ���", nId);

	if (MessageBox(szInfo, "��ܰ��ʾ��", MB_YESNO) == IDYES)
	{
		string strQuestFile = GetFileFullPath(nId, Client_Path, Quest_File_Ext);
		::remove(strQuestFile.c_str());

		string strStringFile = GetFileFullPath(nId, Client_Path, String_Ext);
		::remove(strStringFile.c_str());

		//ɾ��Script�ļ�


		return true;
	}

	return false;			
}



void CQuestEditDlg::ShowQuestVersion()
{
	CString strVersion;

	strVersion.Format("����༭�� %s",  ApplicationConfig::Instance().GetFullVersion());

	SetWindowText(strVersion);
}


void CQuestEditDlg::ShowMainMenu()
{
	CMenu xMenu;
	xMenu.LoadMenu(IDR_MAINMENU);
	this->SetMenu(&xMenu);
	xMenu.Detach();
}

void CQuestEditDlg::InitInformation()
{	
	ShowQuestVersion();		//��ʾ�汾��
	/////////////////////////////////////////////////////////////////////////////////
	ShowMainMenu();
	//////////////////////////////////////////////////////////////////////////////////

	char szProcPath[_MAX_PATH] = "";
	char szDir[_MAX_DIR] = "";
	char szDirve[_MAX_DRIVE] = "";

	::GetModuleFileName(NULL, szProcPath, sizeof(szProcPath));

	_tsplitpath(szProcPath, szDirve, szDir, NULL, NULL);
	sprintf_s(m_szFilePath, sizeof(m_szFilePath), "%s%s\\%s", szDirve, szDir, SET_CONFIG_FILE);		

	InitListCtrl(true);	

	ReadSetInfoFile();	//�ַ������ʼ��
	ShowQuestTreeList();	//��ʾ�����б�
	//////////////////////////////////////////////////////////////////////////
	LoadResourceFiles();
	//////////////////////////////////////////////////////////////////////////////

	InitSetInfo();
	InitPropertyList();		//�б��ʼ��
}


void CQuestEditDlg::LoadResourceFiles()
{
	//��ԭ��ǰ����Ŀ¼
	//SetCurrentWorkDir();

	//��ȡ
	if (!GettheItemDetail().LoadBinFile(m_szItemFile))
	{
		AfxMessageBox("���� Item.pak ʧ��!");
	}

	if (!GettheItemDetail().LoadMonster(m_szMonsterFile))
	{
		AfxMessageBox("���� Monster.slk ʧ��!");
	}

	//����NPC��Ϣ
	if (theNpcInfo.LoadConfig(m_szNpcFile) != File_Success)
	{
		AfxMessageBox("���� Npc.xml ʧ��!");
	}

	if (!theXmlString.LoadStringPath(m_szStringFile))
	{
		AfxMessageBox("���� String.xml ʧ��!");
	}

	//Ѱ·�����ļ�
	if (thePositionInfo.LoadConfig(Position_File_Path) != File_Success)
	{
		AfxMessageBox("���� Position.config ʧ��!");
	}
}

void CQuestEditDlg::InitListCtrl(bool bInsert)
{
	int nWidth = 0;
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	
	//����	
	if (bInsert)
	{		
		nWidth = SetListCtrlStyle(m_listProperty, dwStyle);
		m_listProperty.InsertColumn(0, "���������ԡ�", 0, (17 * nWidth) / 100);
		m_listProperty.InsertColumn(1, "����ֵ / ID��", 0, (14 * nWidth) / 100);
		m_listProperty.InsertColumn(2, "�����ơ�", 0, (69 * nWidth) / 100);

		//������Ҫ��
		nWidth = SetListCtrlStyle(m_listPreRequiement, dwStyle);
		m_listPreRequiement.InsertColumn(0, "������ǰ��Ҫ��", 0, (25 * nWidth) / 100);
		m_listPreRequiement.InsertColumn(1, "����ֵ / ID��", 0, (25 * nWidth) / 100);
		m_listPreRequiement.InsertColumn(2, "�����ơ�", 0, (25 * nWidth) / 100);
		m_listPreRequiement.InsertColumn(3, "��������", 0, (25 * nWidth) / 100);

		//������Ҫ��
		nWidth = SetListCtrlStyle(m_listPostRequiement, dwStyle);	
		m_listPostRequiement.InsertColumn(0, "���������Ҫ��", 0, (25 * nWidth) / 100);
		m_listPostRequiement.InsertColumn(1, "����ֵ / ID��", 0, (25 * nWidth) / 100);
		m_listPostRequiement.InsertColumn(2, "�����ơ�", 0, (25 * nWidth) / 100);
		m_listPostRequiement.InsertColumn(3, "��������", 0, (25 * nWidth) / 100);

		//����
		nWidth = SetListCtrlStyle(m_listReward, dwStyle);
		m_listReward.InsertColumn(0, "��������ɽ�����", 0, (25 * nWidth) / 100);
		m_listReward.InsertColumn(1, "����ֵ / ID��", 0, (15 * nWidth) / 100);
		m_listReward.InsertColumn(2, "�����ơ�", 0, (15 * nWidth) / 100);
		m_listReward.InsertColumn(3, "��������", 0, (15 * nWidth) / 100);	
		m_listReward.InsertColumn(4, "��ְҵ��", 0, (15 * nWidth) / 100);	
		m_listReward.InsertColumn(5, "���Ա�", 0, (15 * nWidth) / 100);	
	}
	else
	{
		nWidth = SetListCtrlStyle(m_listProperty, dwStyle);
		m_listProperty.SetColumnWidth(0, (17 * nWidth) / 100);
		m_listProperty.SetColumnWidth(1, (14 * nWidth) / 100);
		m_listProperty.SetColumnWidth(2, (69 * nWidth) / 100);


		//������Ҫ��
		nWidth = SetListCtrlStyle(m_listPreRequiement, dwStyle);	

		m_listPreRequiement.SetColumnWidth(0, (25 * nWidth) / 100);
		m_listPreRequiement.SetColumnWidth(1, (25 * nWidth) / 100);
		m_listPreRequiement.SetColumnWidth(2, (25 * nWidth) / 100);
		m_listPreRequiement.SetColumnWidth(3, (25 * nWidth) / 100);
		//������Ҫ��
		nWidth = SetListCtrlStyle(m_listPostRequiement, dwStyle);	
		m_listPostRequiement.SetColumnWidth(0, (25 * nWidth) / 100);
		m_listPostRequiement.SetColumnWidth(1, (25 * nWidth) / 100);
		m_listPostRequiement.SetColumnWidth(2, (25 * nWidth) / 100);
		m_listPostRequiement.SetColumnWidth(3, (25 * nWidth) / 100);

		//����
		nWidth = SetListCtrlStyle(m_listReward, dwStyle);
		m_listReward.SetColumnWidth(0, (25 * nWidth) / 100);
		m_listReward.SetColumnWidth(1, (15 * nWidth) / 100);
		m_listReward.SetColumnWidth(2, (15 * nWidth) / 100);
		m_listReward.SetColumnWidth(3, (15 * nWidth) / 100);	
		m_listReward.SetColumnWidth(4, (15 * nWidth) / 100);	
		m_listReward.SetColumnWidth(5, (15 * nWidth) / 100);	
	}
}

void CQuestEditDlg::ReadSetInfoFile()
{
	//��ȡ�ļ�
	string strSub = "";
	char szValue[300] = "";

	for (int i = 0; i < Enum_End; ++i)
	{
		::GetPrivateProfileString(s_pzSecion[i], Key_Name, "", szValue, sizeof(szValue) - 1, m_szFilePath);

		m_xStringArray[i].RemoveAll();
		m_xSetInfo[i].clear();

		m_xStringArray[i].Add(Default_Select);

		//string strValue = szValue;

		//while (SubString(strValue, strSub, SUB_STRING1))
		//{
		//	SetInfo xSetInfo;

		//	string strTemp = "";
		//	SubString(strSub, strTemp, SUB_STRING2);
		//	xSetInfo.strName = strTemp;
		//	
		//	SubString(strSub, strTemp, SUB_STRING2);
		//	if (!strTemp.empty())
		//	{
		//		xSetInfo.nValue = atoi(strTemp.c_str());
		//	}
		//	
		//	if (!xSetInfo.strName.empty() && xSetInfo.nValue != -1)
		//	{
		//		m_xSetInfo[i].push_back(xSetInfo);
		//		m_xStringArray[i].Add(xSetInfo.strName.c_str());   //�ַ�����
		//	}			
		//}
	}	

	
	::GetPrivateProfileString(ItemFile_Section, Key_Name, Item_File_Path, m_szItemFile, sizeof(m_szItemFile) - 1, m_szFilePath);
	::GetPrivateProfileString(MapFile_Section, Key_Name, Map_File_Path, m_szMapFile, sizeof(m_szMapFile) - 1, m_szFilePath);
	::GetPrivateProfileString(MonsterFile_Section, Key_Name, Monster_File_Path, m_szMonsterFile, sizeof(m_szMonsterFile) - 1, m_szFilePath);
	::GetPrivateProfileString(NpcFile_Section, Key_Name, Npc_File_Path, m_szNpcFile, sizeof(m_szNpcFile) - 1, m_szFilePath);
	::GetPrivateProfileString(ReputeFile_Section, Key_Name, Repute_File_Path, m_szReputeFile, sizeof(m_szReputeFile) - 1, m_szFilePath);
	::GetPrivateProfileString(StringFile_Section, Key_Name, String_File_Path, m_szStringFile, sizeof(m_szStringFile) - 1, m_szFilePath);
}       

void CQuestEditDlg::InitSetInfo()
{
	//��ͼ
	CWorldMapConfig xWorldMapConfig;
	if (xWorldMapConfig.LoadMapCfg(m_szMapFile) == TRUE)
	{
		int nCount = xWorldMapConfig.GetMapCount();

		for (int i = 0; i < nCount; ++i)
		{
			CWorldMapConfig::SMapSetting *pMapSet = xWorldMapConfig.GetMapCfgByIndex(i);

			SetInfo xSetInfo;
			xSetInfo.nValue = i;		
			if (pMapSet != NULL)
			{
				xSetInfo.strName = pMapSet->strName;
			}
			else
			{
				xSetInfo.strName = "δ֪��ͼ��Ϣ";
			}

			m_xStringArray[Enum_Map].Add(xSetInfo.strName.c_str());
			m_xSetInfo[Enum_Map].push_back(xSetInfo);		
		}
	}

	//�ƺ�
	if (GettheItemDetail().LoadReputeList(m_szReputeFile) == TRUE)
	{
		int nCount = GettheItemDetail().GetReputeListSize();
		for (int i = 0; i < nCount; ++i)
		{

			CItemDetail::ReputeStruct* pRepute = GettheItemDetail().GetReputeById(i);
			if (pRepute != NULL)
			{	
				SetInfo xSetInfo;
				xSetInfo.nValue = i;
				xSetInfo.strName = pRepute->szReputeName;

				m_xStringArray[Enum_Quality].Add(pRepute->szReputeName.c_str());
				m_xSetInfo[Enum_Quality].push_back(xSetInfo);
			}		
		}
	}


	//����Ʒ��
	for (int i = 0; i < SQuest::eQuestRank_Max; ++i)
	{

		SetInfo xSetInfo;
		xSetInfo.nValue = i;
		xSetInfo.strName = s_pszQuality[i];

		m_xStringArray[Enum_Quality].Add(s_pszQuality[i]);
		m_xSetInfo[Enum_Quality].push_back(xSetInfo);
	}


	//Ҫ��
	for (int i = 0; i < SQuest::eRequirement_Max; ++i)
	{
		SetInfo xSetInfo;
		xSetInfo.nValue = i;
		xSetInfo.strName = s_pszRequement[i];

		m_xStringArray[Enum_Requirement].Add(s_pszRequement[i]);
		m_xSetInfo[Enum_Requirement].push_back(xSetInfo);
	}

	//����
	for (int i = 0; i < SQuest::eReward_Max; ++i)
	{
		SetInfo xSetInfo;
		xSetInfo.nValue = i;
		xSetInfo.strName = s_pszReward[i];

		m_xStringArray[Enum_Reward].Add(s_pszReward[i]);
		m_xSetInfo[Enum_Reward].push_back(xSetInfo);
	}

	//�Ա�
	for (int i = 0; i < Sex_Max; ++i)
	{
		SetInfo xSetInfo;
		xSetInfo.nValue = i;
		xSetInfo.strName = s_pszSex[i];

		m_xStringArray[Enum_Sex].Add(s_pszSex[i]);
		m_xSetInfo[Enum_Sex].push_back(xSetInfo);
	}

	//ְҵ
	for (int i = 0; i < EA_ArmsMaxSize; ++i)
	{
		SetInfo xSetInfo;
		xSetInfo.nValue = i;
		xSetInfo.strName = s_pszProfession[i];

		m_xStringArray[Enum_Profession].Add(s_pszProfession[i]);
		m_xSetInfo[Enum_Profession].push_back(xSetInfo);
	}


	//������Ŀ��
	PositionInfo::PositionsIter iter = thePositionInfo.positions_.begin();
	PositionInfo::PositionsIter end = thePositionInfo.positions_.end();
	for( ; iter != end; ++iter)
	{
		SetInfo xSetInfo;
		xSetInfo.nValue = iter->second.id;

		string strName = "";
		
		//����npc
		NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(iter->second.id);
		if (pNpc != NULL)
		{
			strName = pNpc->name;
		}

		if (strName.empty())
		{
			//���ҹ����
			CItemDetail::SMonster *pMonster = GettheItemDetail().GetMonsterById(iter->second.id);
			if (pMonster != NULL)
			{
				strName = pMonster->GetName();
			}
		}

		//��û�� ��ֱ��ʹ��
		if (strName.empty())
		{
			strName = iter->second.name;
		}

		xSetInfo.strName = strName;		
		m_xStringArray[Enum_Position].Add(xSetInfo.strName.c_str());
		m_xSetInfo[Enum_Position].push_back(xSetInfo);
	}

	//��Ʒ
	int nItemCount = GettheItemDetail().GetItemCount();
	for(int i = 0; i < nItemCount; ++i)
	{
		CItemDetail::SItemCommon *pItem = GettheItemDetail().GetItemByID(i);
		if (pItem != NULL)
		{			
			SetInfo xSetInfo;
			xSetInfo.nValue = pItem->ustItemID;
			xSetInfo.strName = pItem->GetItemName();

			m_xStringArray[Enum_Item].Add(pItem->GetItemName());
			m_xSetInfo[Enum_Item].push_back(xSetInfo);
		}
	}

	//����
	int nMonsterCount  = GettheItemDetail().GetMonsterNumber();
	for(int i = 0; i < nMonsterCount; ++i)
	{
		CItemDetail::SMonster *pMonster = GettheItemDetail().GetMonster(i);
		if (pMonster != NULL)
		{			
			SetInfo xSetInfo;
			xSetInfo.nValue = pMonster->stMonsterId;
			xSetInfo.strName = pMonster->GetName();

			m_xStringArray[Enum_Monster].Add(pMonster->GetName());
			m_xSetInfo[Enum_Monster].push_back(xSetInfo);
		}
	}

	//��������
	static const int s_nQuestInfoTypeCount = sizeof(s_pszQuestInfoType) / sizeof(char*);
	for (int i = 0; i < s_nQuestInfoTypeCount; ++i)
	{
		SetInfo xSetInfo;
		xSetInfo.nValue = i;
		xSetInfo.strName = s_pszQuestInfoType[i];

		m_xStringArray[Enum_QuestInfoType].Add(s_pszQuestInfoType[i]);
		m_xSetInfo[Enum_QuestInfoType].push_back(xSetInfo);
	}

	
}


void CQuestEditDlg::SaveSetInfoFile()
{
	for (int i = 0; i < Enum_End; ++i)
	{
		SaveSetInfoFile(s_pzSecion[i], Key_Name, m_xSetInfo[i]);
	}	

	WritePrivateProfileString(ItemFile_Section, Key_Name, m_szItemFile, m_szFilePath);
	WritePrivateProfileString(MonsterFile_Section, Key_Name, m_szMonsterFile, m_szFilePath);
	WritePrivateProfileString(NpcFile_Section, Key_Name, m_szNpcFile, m_szFilePath);
	WritePrivateProfileString(StringFile_Section, Key_Name, m_szStringFile, m_szFilePath);
}

void CQuestEditDlg::SaveSetInfoFile(const char *pszSecion, char *pszKey, vector<SetInfo> &vecSetInfo)
{
	if (pszSecion == NULL || pszKey == NULL)
	{
		return;
	}

	sort(vecSetInfo.begin(), vecSetInfo.end());

	setiter iter = vecSetInfo.begin();
	setiter end = vecSetInfo.end();

	char szValue[500] = "";
	for ( ; iter != end; ++iter)
	{
		sprintf_s(szValue + strlen(szValue), sizeof(szValue) - 1, "%s%s%d%s", (*iter).strName.c_str(), SUB_STRING2, (*iter).nValue, SUB_STRING1);
	}

	::WritePrivateProfileString(pszSecion, pszKey, szValue, m_szFilePath);
}

void CQuestEditDlg::InitPropertyList()
{	
	m_listProperty.DeleteAllItems();	
	///////////////////////////////////////////////////////////////////////////
	//////��������
	int nItem = 0;
	const int nSubItem = 1;

	m_listProperty.InsertItem(nItem, "����ID");	
	m_listProperty.SetEdit(nItem, nSubItem);	
	m_listProperty.SetComboBox(nItem++, nSubItem + 1, TRUE, &m_xStringArray[Enum_QuestInfoType], m_xStringArray[Enum_QuestInfoType].GetCount(), 1);

	m_listProperty.InsertItem(nItem, "��������");	
	//m_listProperty.SetEdit(nItem, nSubItem);
	m_listProperty.SetEdit(nItem++, nSubItem + 1);

	m_listProperty.InsertItem(nItem, "����Ʒ��");	
	//m_listProperty.SetEdit(nItem, nSubItem);
	m_listProperty.SetItemText(nItem, nSubItem, "0");
	m_listProperty.SetComboBox(nItem++, nSubItem + 1, TRUE, &m_xStringArray[Enum_Quality], m_xStringArray[Enum_Quality].GetSize(), 1);

	m_listProperty.InsertItem(nItem, "������������");
	//m_listProperty.SetEdit(nItem, nSubItem);	
	m_listProperty.SetEdit(nItem++, nSubItem + 1);

	m_listProperty.InsertItem(nItem, "����Ŀ������");
	//m_listProperty.SetEdit(nItem, nSubItem);	
	m_listProperty.SetEdit(nItem++, nSubItem + 1);

	m_listProperty.InsertItem(nItem, "�����ͼ");
	//m_listProperty.SetEdit(nItem, nSubItem);
	m_listProperty.SetComboBox(nItem++, nSubItem + 1, TRUE, &m_xStringArray[Enum_Map], m_xStringArray[Enum_Map].GetSize(), 0);

	//����������
	m_listProperty.InsertItem(nItem, "������Ŀ��");
	//m_listProperty.SetEdit(nItem, nSubItem);
	SetListItemBGroundColor(m_listProperty, nItem, 1, Red_Ground_Color);
	m_listProperty.SetComboBox(nItem++, nSubItem + 1, TRUE, &m_xStringArray[Enum_Position], m_xStringArray[Enum_Position].GetSize(), 0);

	m_listProperty.InsertItem(nItem, "��ʾ�ȼ�(xx-yy)");
	m_listProperty.SetEdit(nItem++, nSubItem);

	m_listProperty.InsertItem(nItem, "�ܷ�Э��ִ��");	
	m_listProperty.SetCheckbox(nItem, nSubItem, 0);
	m_listProperty.SetItemText(nItem++, nSubItem, "Э��ִ��");

	m_listProperty.InsertItem(nItem, "�ܷ�������");	
	m_listProperty.SetCheckbox(nItem, nSubItem, 0);
	m_listProperty.SetItemText(nItem++, nSubItem, "������");

	m_listProperty.InsertItem(nItem, "�ܷ��ظ�ִ��");	
	m_listProperty.SetCheckbox(nItem, nSubItem, 0);
	m_listProperty.SetItemText(nItem++, nSubItem, "�ظ�����");

	m_listProperty.InsertItem(nItem, "�ܷ�ɾ������");	
	m_listProperty.SetCheckbox(nItem, nSubItem, 0);
	m_listProperty.SetItemText(nItem++, nSubItem, "����ɾ��");

	m_listPreRequiement.DeleteAllItems();
	m_listPostRequiement.DeleteAllItems();
	m_listReward.DeleteAllItems();
}

void CQuestEditDlg::ShowQuestTreeList()
{
	m_xTreeQuest.DeleteAllItems();

	HTREEITEM hRoot = m_xTreeQuest.InsertItem(Quest_Root);

	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	for( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			AddQuestInTree(hRoot, *(*iter).second);
		}		
	}

	m_xTreeQuest.ExpandAllTreeNodes(NULL, TRUE);
}

void CQuestEditDlg::AddQuestInTree(HTREEITEM hParent, SQuest &xQuest, HTREEITEM hInsertAfter)
{
	CString strId = "";
	strId.Format("%d", xQuest.Id);
	HTREEITEM hItem = m_xTreeQuest.InsertItem(strId, hParent, hInsertAfter);
	//if (hItem != NULL)
	//{
	//	m_xTreeQuest.InsertItem(theXmlString.GetString((*iter).second->QuestName), hItem);
	//}
}


//��ʾ������Ϣ
void CQuestEditDlg::ShowQuestInformation(SQuest &xQuest)
{
	int nIndex = 0;
	const int nSubItem = 1;

	//ID
	SetListItemText(m_listProperty, nIndex++, nSubItem, "%d", xQuest.Id);	//ID

	//����
	SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.QuestName);
	m_listProperty.SetItemText(nIndex++, nSubItem + 1, theXmlString.GetString(xQuest.QuestName));

	//����Ʒ��
	SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.RankId);
	m_listProperty.SetItemText(nIndex++, nSubItem + 1, GetSetInfoName(m_xSetInfo[Enum_Quality], xQuest.RankId));

	//����
	SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.IntroStringId);
	m_listProperty.SetItemText(nIndex++, nSubItem + 1, theXmlString.GetString(xQuest.IntroStringId));			

	//Ŀ��
	SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.TargetStringId);
	m_listProperty.SetItemText(nIndex++, nSubItem + 1, theXmlString.GetString(xQuest.TargetStringId));	

	//��ͼ
	SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.MapId);	
	m_listProperty.SetItemText(nIndex++, nSubItem + 1, GetSetInfoName(m_xSetInfo[Enum_Map], xQuest.MapId));	

	//���ҵ�Ѱ·��������,Ȼ����ʾ֮
	if (xQuest.ReplyTargetId == -1)
	{
		SetListItemBGroundColor(m_listProperty, nIndex, 1, Red_Ground_Color);
	}
	else
	{
		SetListItemBGroundColor(m_listProperty, nIndex, 1, Default_Grund_Color);
	}
	
	SetListItemText(m_listProperty, nIndex, nSubItem, "%d", xQuest.ReplyTargetId);
	CString strNpc = GetSetInfoName(m_xSetInfo[Enum_Position], xQuest.ReplyTargetId, Default_Select);
	m_listProperty.SetItemText(nIndex++, nSubItem + 1, strNpc);
	
	//��ʾ�ȼ�
	CString strLevel = "";
	strLevel.Format("%d%s%d", xQuest.HintLevelMin, SUB_STRING3, xQuest.HintLevelMax);
	m_listProperty.SetItemText(nIndex++, nSubItem, strLevel);
	
	m_listProperty.SetCheckbox(nIndex++, nSubItem, xQuest.CanAssist);		//Э��
	m_listProperty.SetCheckbox(nIndex++, nSubItem, xQuest.CanShare);			//����
	m_listProperty.SetCheckbox(nIndex++, nSubItem, xQuest.IsRepeat);			//�ظ�
	m_listProperty.SetCheckbox(nIndex++, nSubItem, xQuest.IsCancel);				//ɾ��

	//������Ҫ��
	ShowRequirementList(m_listPreRequiement, xQuest.stReceiveRequirement);
	//������Ҫ��
	ShowRequirementList(m_listPostRequiement, xQuest.stCommitRequirement);

	//������
	ShowRewardList(xQuest.stReward);
}

void CQuestEditDlg::ClearQuestInformation()
{
	int nItem = 1;

	//����
	m_listProperty.SetItemText(nItem, 1, "");
	m_listProperty.SetItemText(nItem++, 2, "");

	//Ʒ��
	m_listProperty.SetItemText(nItem, 1, "");
	m_listProperty.SetItemText(nItem++, 2, Default_Select);

	//����
	m_listProperty.SetItemText(nItem, 1, "");
	m_listProperty.SetItemText(nItem++, 2, "");

	//Ŀ��
	m_listProperty.SetItemText(nItem, 1, "");
	m_listProperty.SetItemText(nItem++, 2, "");

	//��ͼ
	m_listProperty.SetItemText(nItem, 1, "");
	m_listProperty.SetItemText(nItem++, 2, Default_Select);

	//Npc
	SetListItemBGroundColor(m_listProperty, nItem, 1, Red_Ground_Color);
	m_listProperty.SetItemText(nItem, 1, "");
	m_listProperty.SetItemText(nItem++, 2, Default_Select);

	//�ȼ�
	m_listProperty.SetItemText(nItem++, 1, "");
	
	m_listProperty.SetCheckbox(nItem++, 1, 0);
	m_listProperty.SetCheckbox(nItem++, 1, 0);
	m_listProperty.SetCheckbox(nItem++, 1, 0);
	m_listProperty.SetCheckbox(nItem++, 1, 0);

	m_listPreRequiement.DeleteAllItems();
	m_listPostRequiement.DeleteAllItems();
	m_listReward.DeleteAllItems();
}

//��ʾ����Ҫ��
void CQuestEditDlg::ShowRequirementList(CXListCtrl &xRequirementList, vector<SQuestRequirement> &vecRequirement)
{
	reqiter iter = vecRequirement.begin();
	reqiter end = vecRequirement.end();

	int nCount = xRequirementList.GetItemCount();
	int nIndex = 0;

	int nProfessionIndex = 0;

	for ( ; iter != end; )
	{
		if (nIndex >= nCount)
		{
			AddQuestRequiremenetList(xRequirementList,  m_xStringArray[Enum_Requirement]);
			++nCount;
		}		

		for (int i = 0; i < xRequirementList.GetColumns(); ++i)
		{
			SetListItemBGroundColor(xRequirementList, nIndex, i, Default_Grund_Color);
		}

		//id ת�����ַ���,Ȼ����ʾ֮
		xRequirementList.SetItemText(nIndex, 0, GetSetInfoName(m_xSetInfo[Enum_Requirement], (*iter).byType));

		if ((*iter).byType != -1)
		{
			//�ж���������ʾ
			CString strName = "";
			if ((*iter).byType == SQuest::eRequirement_Item)
			{
				CItemDetail::SItemCommon *pItem = GettheItemDetail().GetItemByID((*iter).Value);
				if (pItem != NULL)
				{
					strName = pItem->GetItemName();
				}
			}			
			else if ((*iter).byType == SQuest::eRequirement_Sex)
			{
				xRequirementList.SetComboBox(nIndex, 2, TRUE, &m_xStringArray[Enum_Sex], m_xStringArray[Enum_Sex].GetCount(), 0);

				strName = GetSetInfoName(m_xSetInfo[Enum_Sex], (*iter).Value);
				if (strName.IsEmpty())
				{
					strName = Default_Select;
				}
			}
			else if ((*iter).byType == SQuest::eRequirement_Quest)
			{
				SQuest *pQuest = theQuestManager.GetQuest((*iter).Value);
				if (pQuest != NULL)
				{
					strName = theXmlString.GetString(pQuest->QuestName);
				}
			}
			
			xRequirementList.SetItemText(nIndex, 2, strName);
			SetListItemText(xRequirementList, nIndex, 3, "%d", (*iter).MaxNum);

			if ((*iter).byType == SQuest::eRequirement_Profession)	//Ҫ����ְҵ����
			{			
				for ( ; nProfessionIndex < EA_ArmsMaxSize; ++nProfessionIndex)
				{
					int nValue = 1 << nProfessionIndex;

					if (((*iter).Value & nValue ) != 0)
					{
						SetListItemText(xRequirementList, nIndex, 1, "%d", nProfessionIndex);	
						xRequirementList.SetComboBox(nIndex, 2, TRUE, &m_xStringArray[Enum_Profession], m_xStringArray[Enum_Profession].GetCount(), 0);

						strName = GetSetInfoName(m_xSetInfo[Enum_Profession], nProfessionIndex);
						if (strName.IsEmpty())
						{
							strName = Default_Select;
						}
						xRequirementList.SetItemText(nIndex, 2, strName);
						++nProfessionIndex;
						++nIndex;

						break;
					}
				}						

				if (nProfessionIndex == EA_ArmsMaxSize)
				{							
					++iter;
				}
				continue;
			}
			else
			{
				if ((*iter).byType == SQuest::eRequirement_Monster)
				{
					for (int i = 0; i < xRequirementList.GetColumns(); ++i)
					{
						SetListItemBGroundColor(xRequirementList, nIndex, i, Green_Ground_Color);
					}

					xRequirementList.SetItemText(nIndex, 0, GetSetInfoName(m_xSetInfo[Enum_Requirement], (*iter).byType));
					xRequirementList.Resume(nIndex, 1);
					xRequirementList.SetEdit(nIndex, 2);
					//���Ҳ���ʾ
					DropTaskItem::STask xTask;
					int nMonsterId = m_xDropTaskItem.FindDropItemByVarId((*iter).wVar, xTask);
					if (nMonsterId != -1)
					{						
						SetListItemBGroundColor(xRequirementList, nIndex, 1, Green_Ground_Color);
						SetListItemText(xRequirementList, nIndex, 1, "%d", nMonsterId);
												
						CItemDetail::SMonster *pMonster = GettheItemDetail().GetMonsterById(nMonsterId);
						if (pMonster != NULL)
						{
							SetListItemBGroundColor(xRequirementList, nIndex, 2, Green_Ground_Color);
							xRequirementList.SetItemText(nIndex, 2, pMonster->GetName());
						}

						SetListItemText(xRequirementList, nIndex, 3, "%d", xTask.nMaxVar);
					}
					else
					{
						xRequirementList.SetItemText(nIndex, 1, "");
						xRequirementList.SetItemText(nIndex, 2, "");
						xRequirementList.SetItemText(nIndex, 3, "");
					}					
				}
				else
				{
					SetListItemText(xRequirementList, nIndex, 1, "%d", (*iter).Value);
				}						
			}
		}
		++nIndex;
		++iter;
	}

	//����ľ�ɾ����
	for (int i = nCount - 1; i >= nIndex; --i)
	{
		xRequirementList.DeleteItem(i);
	}
}

//��ʾ������
void CQuestEditDlg::ShowRewardList(vector<SQuestReward> &vecReward)
{
	rewarditer iter = vecReward.begin();
	rewarditer end = vecReward.end();

	int nCount = m_listReward.GetItemCount();
	int nIndex = 0;
	for ( ; iter != end; ++iter)
	{
		if (nIndex >= nCount)
		{
			AddQuestRewardList(m_listReward, m_xStringArray[Enum_Reward]);
			++nCount;
		}
		
		if ((*iter).byType != -1)
		{
			m_listReward.SetItemText(nIndex, 0, GetSetInfoName(m_xSetInfo[Enum_Reward], (*iter).byType));

			if ((*iter).Value  != -1)
			{
				SetListItemText(m_listReward, nIndex, 1, "%d", (*iter).Value);
			}


			//�ж���������ʾ
			CString strName = "";
			if ((*iter).byType == SQuest::eReward_Item)
			{
				CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID((*iter).Value);
				if (pItem != NULL)
				{
					strName = pItem->GetItemName();
				}

				m_listReward.SetComboBox(nIndex, 4, TRUE, &m_xStringArray[Enum_Profession], m_xStringArray[Enum_Profession].GetCount(), 0);
				m_listReward.SetComboBox(nIndex, 5, TRUE, &m_xStringArray[Enum_Sex], m_xStringArray[Enum_Sex].GetCount(), 0);
				
				string strProfession = GetSetInfoName(m_xSetInfo[Enum_Profession], (*iter).shProfession);
				if (strProfession.empty())
				{
					strProfession = Default_Select;
				}

				m_listReward.SetItemText(nIndex, 4, strProfession.c_str());

				string strSex = GetSetInfoName(m_xSetInfo[Enum_Sex], (*iter).shSex);
				if (strSex.empty())
				{
					strSex = Default_Select;
				}
				m_listReward.SetItemText(nIndex, 5, strSex.c_str());
				
			}
			else if ((*iter).byType == SQuest::eReward_ReputeName)
			{
				m_listReward.SetComboBox(nIndex, 2, TRUE, &m_xStringArray[Enum_ReputeName], m_xStringArray[Enum_ReputeName].GetCount(), 0);

				strName = GetSetInfoName(m_xSetInfo[Enum_ReputeName], (*iter).Value);
				if (strName.IsEmpty())
				{
					strName = Default_Select;
				}
			}
			else if ((*iter).byType == SQuest::eReward_Buff)
			{
				m_listReward.SetComboBox(nIndex, 2, TRUE, &m_xStringArray[Enum_Buff], m_xStringArray[Enum_Buff].GetCount(), 0);

				strName = GetSetInfoName(m_xSetInfo[Enum_Buff], (*iter).Value);
				if (strName.IsEmpty())
				{
					strName = Default_Select;
				}
			}
		
			m_listReward.SetItemText(nIndex, 2, strName);
			SetListItemText(m_listReward, nIndex, 3, "%d", (*iter).Number);		

			++nIndex;
		}
	}

	//����ľ�ɾ����
	for (int i = nCount - 1; i >= nIndex; --i)
	{
		m_listReward.DeleteItem(i);
	}
}

///////////////////////////////////////////////////////////////////////////////////

int CQuestEditDlg::AddInQuestList()
{
	int nIndex = 0;
	const int nSubItem = 1;

	//����ID
	int nId = GetListItemInt(m_listProperty, nIndex++, nSubItem, -1);
	if (nId == -1)
	{
		//����ID ����Ϊ��
		return nId;
	}

	//����
	int nNameId = GetListItemInt(m_listProperty, nIndex++, nSubItem, Empty_String_Id);
	if (nNameId < Empty_String_Id)
	{
		nNameId = Empty_String_Id;
	}

	//Ʒ��
	int nQuestQuality = GetListItemInt(m_listProperty, nIndex++, nSubItem, -1);

	//����
	int nIntroId = GetListItemInt(m_listProperty, nIndex++, nSubItem, Empty_String_Id);
	if (nIntroId < Empty_String_Id)
	{
		nIntroId = Empty_String_Id;
	}

	//Ѱ��Ŀ��
	int nTargetId = GetListItemInt(m_listProperty, nIndex++, nSubItem, Empty_String_Id);
	if (nTargetId < Empty_String_Id)
	{
		nTargetId = Empty_String_Id;
	}

	//��ͼ
	int nMapId = GetListItemInt(m_listProperty, nIndex++, nSubItem, -1);

	//NPC
	int nNpcId = GetListItemInt(m_listProperty, nIndex++, nSubItem, -1);

	//������ʾ�ȼ�
	string strLevel = m_listProperty.GetItemText(nIndex++, nSubItem).GetBuffer();	
	string strValue = "";
	SubString(strLevel, strValue, SUB_STRING3);
	int nPlayerLevelMin = atoi(strValue.c_str());
	SubString(strLevel, strValue, SUB_STRING3);
	int nPlayerLevelMax = atoi(strValue.c_str());
	//�������
	nPlayerLevelMax = (nPlayerLevelMax == 0 ? Max_Level : nPlayerLevelMax);

	bool CanAssist = m_listProperty.GetCheckbox(nIndex++, nSubItem);	//�ܷ���
	bool CanShare = m_listProperty.GetCheckbox(nIndex++, nSubItem);	//�ܷ���
	bool IsRepeat = m_listProperty.GetCheckbox(nIndex++, nSubItem);		//�ܷ��ظ�
	bool IsCancel = m_listProperty.GetCheckbox(nIndex++, nSubItem);		//�ܷ�ɾ��


	//����ֱ�ӱ��浽�ļ�����ȥ
	string strQuestFile = GetFileFullPath(nId, Client_Path, Quest_File_Ext);

	//�ж���ӵ������Ƿ��Ѿ�����, �������޸�,�������֮
	SQuest *pQuest = theQuestManager.GetQuest(nId);
	if (pQuest != NULL)
	{
		pQuest->Id = nId;
		pQuest->QuestName = nNameId;
		pQuest->RankId = nQuestQuality;
		pQuest->IntroStringId = nIntroId;
		pQuest->TargetStringId = nTargetId;
		pQuest->MapId = nMapId;
		pQuest->ReplyTargetId = nNpcId;
		pQuest->HintLevelMin = nPlayerLevelMin;
		pQuest->HintLevelMax = nPlayerLevelMax;
		pQuest->CanAssist = CanAssist;
		pQuest->CanShare = CanShare;
		pQuest->IsRepeat = IsRepeat;
		pQuest->IsCancel = IsCancel;

		//������Ҫ��
		GetQuestRequirement(m_listPreRequiement, *pQuest, false);

		//������Ҫ��
		GetQuestRequirement(m_listPostRequiement, *pQuest, true);	

		//������
		GetQuestReward(m_listReward, *pQuest);

		SaveQuestAndStringInFile(strQuestFile.c_str(), *pQuest); //�����ļ�
	}
	else
	{
		SQuest xQuest;

		xQuest.Id = nId;
		xQuest.QuestName = nNameId;
		xQuest.RankId = nQuestQuality;
		xQuest.IntroStringId = nIntroId;
		xQuest.TargetStringId = nTargetId;
		xQuest.MapId = nMapId;
		xQuest.ReplyTargetId = nNpcId;

		xQuest.HintLevelMin = nPlayerLevelMin;
		xQuest.HintLevelMax = nPlayerLevelMax;
		xQuest.CanAssist = CanAssist;
		xQuest.CanShare = CanShare;
		xQuest.IsRepeat = IsRepeat;
		xQuest.IsCancel = IsCancel;

		//������Ҫ��
		GetQuestRequirement(m_listPreRequiement, xQuest, false);

		//������Ҫ��
		GetQuestRequirement(m_listPostRequiement, xQuest, true);	

		//������
		GetQuestReward(m_listReward, xQuest);

		SaveQuestAndStringInFile(strQuestFile.c_str(), xQuest); //���浽�ļ���

		//��ӵ��б��� 
		if (theQuestInfo.AddQuest(&xQuest))
		{			
			HTREEITEM hRoot = m_xTreeQuest.GetRootItem();
			if (hRoot != NULL)
			{
				AddQuestInTree(hRoot, xQuest, TVI_SORT);	

				m_xTreeQuest.ExpandAllTreeNodes(hRoot, TRUE);
			}
		}		
	}	

	return nId;
}

bool CQuestEditDlg::SaveQuestAndStringInFile(const char* pszFile, SQuest &xQuest)
{
	if (theQuestInfo.SaveQuestFile(pszFile, &xQuest))  //���浽�ļ���
	{
		//���������ļ�
		vector<int> vecStringId;
		vecStringId.push_back(xQuest.QuestName);
		vecStringId.push_back(xQuest.IntroStringId);
		vecStringId.push_back(xQuest.TargetStringId);

		string strStringFile = GetFileFullPath(xQuest.Id, Client_Path, String_Ext);
		theXmlString.SaveStringFile(strStringFile.c_str(), vecStringId);

		//����Scrpit �ļ�

		
		m_staticSave.SetWindowText("����ɹ���");
		SetTimer(SaveShow_Timer_Id, 2500, NULL);

		return true;
	}	

	return false;
}

void CQuestEditDlg::AddQuestRequiremenetList(CXListCtrl &xRequirementList, CStringArray &xStringArray)
{
	int nSubItem = 0;
	int nCount = xRequirementList.GetItemCount();

	xRequirementList.InsertItem(nCount, "");	
	xRequirementList.SetComboBox(nCount, 0, TRUE, &xStringArray, xStringArray.GetSize(), 0);
	xRequirementList.SetEdit(nCount, 1);
	xRequirementList.SetEdit(nCount, 3);

	if (m_pxDropItemDialog != NULL)
	{
		m_pxDropItemDialog->ShowWindow(SW_HIDE);
	}
}

void CQuestEditDlg::AddQuestRewardList(CXListCtrl &xRewardList, CStringArray &xStringArray)
{
	int nSubItem = 0;
	int nCount = xRewardList.GetItemCount();

	xRewardList.InsertItem(nCount, "");	
	xRewardList.SetComboBox(nCount, 0, TRUE, &xStringArray, xStringArray.GetSize(), 0);
	xRewardList.SetEdit(nCount, 1);
	xRewardList.SetEdit(nCount, 3);
}

void CQuestEditDlg::GetQuestRequirement(CXListCtrl &xRequirementList, SQuest &xQuest, bool bCommit)
{	
	if (bCommit)  //���Ҫ��
	{
		xQuest.ClearCommitRequirement();
	}
	else  //ǰ��Ҫ��
	{
		xQuest.ClearReceiveRequirement();
	}

	int nRequirement = xRequirementList.GetItemCount();
	for (int i = 0; i < nRequirement; ++i)
	{
		CString strType = xRequirementList.GetItemText(i, 0);
		if (strType == Default_Select)
		{
			continue;
		}

		SQuestRequirement xRequirement;

		xRequirement.byType = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strType.GetBuffer());
		xRequirement.Value = GetListItemInt(xRequirementList, i, 1, -1);
		if (xRequirement.byType == SQuest::eRequirement_Profession)	//�����ְҵ�޶�
		{
			bool bFind = false;

			xRequirement.Value =  1 << xRequirement.Value;
			SQuest::RequirementType::iterator viter = xQuest.stReceiveRequirement.begin();
			SQuest::RequirementType::iterator vend = xQuest.stReceiveRequirement.end();

			for ( ; viter != vend; ++viter)
			{
				if ((*viter).byType == SQuest::eRequirement_Profession)
				{
					(*viter).Value |= xRequirement.Value;					
					bFind = true;
					break;	
				}
			}

			if (bFind)
			{
				continue;
			}
		}
		else if (xRequirement.byType == SQuest::eRequirement_Monster)  //����
		{
			int nMonsterId = GetListItemInt(xRequirementList, i, 1, -1);
			
			DropTaskItem::STask xTask;
			if (m_xDropTaskItem.FindDropItemByMonsterId(nMonsterId, xQuest.Id, xTask) != -1)
			{
				xRequirement.wVar = xTask.nVarId;
			}
			else
			{
				xRequirement.Value = -1;
				AfxMessageBox("�����ù��������Ʒ�趨��");
			}			
		}
		
		xRequirement.MaxNum = GetListItemInt(xRequirementList, i, 3, 0);		
		if (bCommit)  //���Ҫ��
		{
			xQuest.AddCommitRequirement(&xRequirement);
		}
		else  //ǰ��Ҫ��
		{
			xQuest.AddReceiveRequirement(&xRequirement);
		}
	}
}

void CQuestEditDlg::GetQuestReward(CXListCtrl &xRewardList, SQuest &xQuest)
{
	xQuest.ClearReward();

	int nRewardCount = xRewardList.GetItemCount();
	for (int i = 0; i < nRewardCount; ++i)
	{
		CString strType = xRewardList.GetItemText(i, 0);
		if (strType == Default_Select)
		{
			continue;
		}

		SQuestReward xReward;
		xReward.byType = GetSetInfoValue(m_xSetInfo[Enum_Reward], strType.GetBuffer());
		xReward.Value = GetListItemInt(xRewardList, i, 1, -1);	
		xReward.Number = GetListItemInt(xRewardList, i, 3, 0);	

		CString strProfession = xRewardList.GetItemText(i, 4);
		if (!strProfession.IsEmpty())
		{

			xReward.shProfession = GetSetInfoValue(m_xSetInfo[Enum_Profession], strProfession.GetBuffer());
		}

		CString strSex = xRewardList.GetItemText(i, 5);
		if (!strSex.IsEmpty())
		{
			xReward.shSex = GetSetInfoValue(m_xSetInfo[Enum_Sex], strSex.GetBuffer());

			if (xReward.shSex == -1)
			{
				xReward.shSex = Sex_Max;
			}
			else
			{
				if (xReward.shProfession == EA_Fan)
				{
					xReward.shSex = Sex_Female;
				}
			}			
		}
		
		xQuest.AddReward(&xReward);
	}
}

////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//������������
int CQuestEditDlg::GetStringArrayIndex(CStringArray &xArray, CString &strValue)
{
	int nCount = xArray.GetSize();

	for (int i = 0; i < nCount; ++i)
	{
		if (xArray.GetAt(i) == strValue)
		{
			return i;
		}
	}

	return -1;
}

void CQuestEditDlg::SetEditText(CEdit& xEdit, char *pszFormat, ...)
{
	if (xEdit.m_hWnd != NULL)
	{
		va_list valist;

		va_start(valist,pszFormat);

		char szValue[100] = "";

		vsprintf(szValue, pszFormat, valist);

		va_end(valist);

		xEdit.SetWindowText(szValue);
	}
}

int CQuestEditDlg::GetEditInt(CEdit& xEdit, int nDef)
{
	CString strValue = "";

	xEdit.GetWindowText(strValue);

	if (strValue.IsEmpty())
	{
		return nDef;
	}

	return atoi(strValue.GetBuffer());
}

void CQuestEditDlg::InsertItemText(CListCtrl &xList, int nItem, char *pszFormat, ...)
{
	if (xList.m_hWnd != NULL)
	{
		va_list valist;

		va_start(valist,pszFormat);

		char szValue[100] = "";

		vsprintf(szValue, pszFormat, valist);

		va_end(valist);

		xList.InsertItem(nItem, szValue);
	}	
}

void CQuestEditDlg::SetListItemText(CListCtrl& xList, int nItem, int nSubItem, char *pszFormat, ...)
{
	if (xList.m_hWnd != NULL)
	{
		va_list valist;

		va_start(valist,pszFormat);

		char szValue[100] = "";

		vsprintf(szValue, pszFormat, valist);

		va_end(valist);

		xList.SetItemText(nItem, nSubItem, szValue);
	}	
}

int CQuestEditDlg::GetListItemInt(CListCtrl &xList, int nItem, int nSubItem, int nDef)
{
	CString strValue = xList.GetItemText(nItem, nSubItem);

	if (strValue.IsEmpty())
	{
		return nDef;
	}

	return (atoi(strValue.GetBuffer()));
}


bool CQuestEditDlg::SubString(string &strDest,string &strSub,string strSign)
{
	if(strDest == "")
	{
		strSub = "";
		return false;
	}

	string::size_type nPos = strDest.find(strSign);
	if(nPos == string::npos)
	{
		strSub = strDest;
		strDest = "";
		return true;
	}

	strSub = strDest.substr(0, nPos);

	strDest = strDest.substr(nPos + 1);

	return true;
}

int CQuestEditDlg::SetListCtrlStyle(CListCtrl &xList, DWORD dwStyle)
{
	xList.SetExtendedStyle(dwStyle);

	RECT rect;
	xList.GetClientRect(&rect);

	return (rect.right - rect.left);
}

int CQuestEditDlg::GetListCtrlCurSel(CListCtrl &xList)
{
	POSITION pos = xList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		return xList.GetNextSelectedItem(pos); 
	}

	return -1;
}

bool CQuestEditDlg::IsIDNumber(const char *pszID,int nLength)
{
	if (pszID == NULL || nLength <= 0)
	{
		return false;
	}
	
	for (int i = 0; i < nLength; ++i)
	{
		if (pszID[i] < '0' || pszID[i] > '9')
		{
			return false;
		}
	}

	return true;
}


int CQuestEditDlg::GetSetInfoValue(vector<SetInfo> &vecSetInfo, string strName)
{
	if (strName.empty())
	{
		return -1;
	}

	setiter iter = vecSetInfo.begin();
	setiter end = vecSetInfo.end();

	for ( ; iter != end; ++iter)
	{

		if ((*iter).strName == strName)
		{
			return (*iter).nValue;
		}
	}

	return -1;
}

const char* CQuestEditDlg::GetSetInfoName(vector<SetInfo> &vecSetInfo, int nValue, char *pszDef /* = ""*/)
{
	if (nValue == -1)
	{
		return pszDef;
	}

	setiter iter = vecSetInfo.begin();
	setiter end = vecSetInfo.end();

	for ( ; iter != end; ++iter)
	{

		if ((*iter).nValue == nValue)
		{
			return (*iter).strName.c_str();
		}
	}

	return pszDef;
}

LRESULT CQuestEditDlg::OnComboSelection(WPARAM nItem, LPARAM nSubItem)
{
	if (nItem >= 0 && nSubItem >= 0)
	{
		CString strName = m_pxListCtrl->GetItemText(nItem, nSubItem);
		if (m_strValue == strName)
		{
			return 0;
		}

		//�����б�
		if (m_pxListCtrl == &m_listProperty)
		{
			if (nItem == 0 && nSubItem == 2)  //����ǰ׺
			{
				CString strText = m_listProperty.GetItemText(nItem, nSubItem);
				if (strText != Default_Select)
				{
					m_listProperty.SetItemText(1, 2, strText);
				}				
			}
			if (nItem == 2 && nSubItem == 2)  //Ʒ��
			{								
				int nQualityId = GetSetInfoValue(m_xSetInfo[Enum_Quality], strName.GetBuffer());
				if (nQualityId != -1)
				{
					SetListItemText(*m_pxListCtrl, nItem, 1, "%d", nQualityId);
				}
				else
				{
					m_pxListCtrl->SetItemText(nItem, 1, "");
				}
								
			}			
			else if (nItem == 5 && nSubItem == 2) //��ͼ
			{
				int nMapId = GetSetInfoValue(m_xSetInfo[Enum_Map], strName.GetBuffer());
				if (nMapId != -1)
				{
					SetListItemText(*m_pxListCtrl, nItem, 1, "%d", nMapId);
				}
				else
				{
					m_pxListCtrl->SetItemText(nItem, 1, "");
				}

			}
			else if (nItem == 6 && nSubItem == 2) //������Ŀ��
			{
				int nNpcId = GetSetInfoValue(m_xSetInfo[Enum_Position], strName.GetBuffer());
				if (nNpcId != -1)
				{
					SetListItemBGroundColor(m_listProperty, nItem, 1, Default_Grund_Color);
					SetListItemText(m_listProperty, nItem, 1, "%d", nNpcId);
				}	
				else
				{
					SetListItemBGroundColor(m_listProperty, nItem, 1, Red_Ground_Color);
					m_listProperty.SetItemText(nItem, 1, "");
				}
								
			}
		}
		else if (m_pxListCtrl == &m_listPreRequiement || m_pxListCtrl == &m_listPostRequiement) //����Ҫ��
		{
			if (nSubItem == 0)  //��1��
			{
				m_pxListCtrl->Resume(nItem, 1);
				for(int i = 0; i < m_pxListCtrl->GetColumns(); ++i)
				{
					SetListItemBGroundColor(*m_pxListCtrl, nItem, i, Default_Grund_Color);
				}

				int nValue = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strName.GetBuffer());

				if (nValue == SQuest::eRequirement_Profession)
				{					
					m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Profession], m_xStringArray[Enum_Profession].GetCount(), 0);

					m_pxListCtrl->SetItemText(nItem, 1, "");
					m_pxListCtrl->SetItemText(nItem, 3, "");	
				}
				else if (nValue == SQuest::eRequirement_Sex)
				{					
					m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Sex], m_xStringArray[Enum_Sex].GetCount(), 0);

					m_pxListCtrl->SetItemText(nItem, 1, "");
					m_pxListCtrl->SetItemText(nItem, 3, "");	
				}		
				else if (nValue == SQuest::eRequirement_Monster)
				{
					m_pxListCtrl->Resume(nItem, 1);
					m_pxListCtrl->SetItemText(nItem, 1, "");
					m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Monster], m_xStringArray[Enum_Monster].GetCount(), 0);	

					for(int i = 0; i < m_pxListCtrl->GetColumns(); ++i)
					{
						SetListItemBGroundColor(*m_pxListCtrl, nItem, i, Green_Ground_Color);
					}					
				}
				else if (nValue == SQuest::eRequirement_Item)
				{
					m_pxListCtrl->Resume(nItem, 1);
					m_pxListCtrl->SetItemText(nItem, 1, "");
					m_pxListCtrl->SetItemText(nItem, 3, "");	
					m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Item], m_xStringArray[Enum_Item].GetCount(), 0);
				}
				else 
				{
					//�ָ�
					m_pxListCtrl->SetEdit(nItem, 1);	

					m_pxListCtrl->Resume(nItem, 2);								
					m_pxListCtrl->SetItemText(nItem, 2, "");					
				}

			}
			else if (nSubItem == 2)  //��3��
			{
				CString strTypeName = m_pxListCtrl->GetItemText(nItem, 0);
				int nValue = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strTypeName.GetBuffer());

				if (nValue == SQuest::eRequirement_Profession)
				{
					CString strProfession = m_pxListCtrl->GetItemText(nItem, nSubItem);
					SetListItemText(*m_pxListCtrl, nItem, 1, "%d", GetSetInfoValue(m_xSetInfo[Enum_Profession], strProfession.GetBuffer()));
				}
				else if (nValue == SQuest::eRequirement_Sex)
				{
					CString strSex = m_pxListCtrl->GetItemText(nItem, nSubItem);

					SetListItemText(*m_pxListCtrl, nItem, 1, "%d", GetSetInfoValue(m_xSetInfo[Enum_Sex], strSex.GetBuffer()));
				}
				else if (nValue == SQuest::eRequirement_Item)
				{
					CString strItem = m_pxListCtrl->GetItemText(nItem, nSubItem);

					SetListItemText(*m_pxListCtrl, nItem, 1, "%d", GetSetInfoValue(m_xSetInfo[Enum_Item], strItem.GetBuffer()));
				}
				else if (nValue == SQuest::eRequirement_Monster)
				{
					CString strMonster = m_pxListCtrl->GetItemText(nItem, nSubItem);

					SetListItemText(*m_pxListCtrl, nItem, 1, "%d", GetSetInfoValue(m_xSetInfo[Enum_Monster], strMonster.GetBuffer()));
				}
			}			
		}
		else if (m_pxListCtrl == &m_listReward)
		{			
			if (nSubItem == 0)
			{
				CString strTypeName = m_pxListCtrl->GetItemText(nItem, nSubItem);
				int nValue = GetSetInfoValue(m_xSetInfo[Enum_Reward], strTypeName.GetBuffer());
				if (nValue == SQuest::eReward_ReputeName)
				{					
					m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_ReputeName], m_xStringArray[Enum_ReputeName].GetCount(), 0);

					m_pxListCtrl->SetItemText(nItem, 1, "");
					m_pxListCtrl->SetItemText(nItem, 3, "");					
				}
				else if (nValue == SQuest::eReward_Buff)
				{					
					m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Buff], m_xStringArray[Enum_Buff].GetCount(), 0);

					m_pxListCtrl->SetItemText(nItem, 1, "");
					m_pxListCtrl->SetItemText(nItem, 3, "");				
				}
				else
				{
					//�ָ�
					m_pxListCtrl->Resume(nItem, 2);					
					if (nValue == SQuest::eReward_Item)
					{
						m_pxListCtrl->Resume(nItem, 1);		
						m_pxListCtrl->SetComboBox(nItem, 2, TRUE, &m_xStringArray[Enum_Item], m_xStringArray[Enum_Item].GetCount(), 0);
						m_pxListCtrl->SetComboBox(nItem, 4, TRUE, &m_xStringArray[Enum_Profession], m_xStringArray[Enum_Profession].GetCount(), 0);
						m_pxListCtrl->SetComboBox(nItem, 5, TRUE, &m_xStringArray[Enum_Sex], m_xStringArray[Enum_Sex].GetCount(), 0);
					}	
					else
					{
						m_pxListCtrl->Resume(nItem, 4);
						m_pxListCtrl->Resume(nItem, 5);

						m_pxListCtrl->SetItemText(nItem, 4, "");
						m_pxListCtrl->SetItemText(nItem, 5, "");
					}
				}
			}
			else if (nSubItem == 2)
			{
				CString strTypeName = m_pxListCtrl->GetItemText(nItem, 0);
				int nValue = GetSetInfoValue(m_xSetInfo[Enum_Reward], strTypeName.GetBuffer());

				if (nValue == SQuest::eReward_ReputeName)
				{
					CString ReputeName = m_pxListCtrl->GetItemText(nItem, nSubItem);
					SetListItemText(*m_pxListCtrl, nItem, 1, "%d", GetSetInfoValue(m_xSetInfo[Enum_ReputeName], ReputeName.GetBuffer()));
				}
				else if (nValue == SQuest::eReward_Buff)
				{
					CString strBuff = m_pxListCtrl->GetItemText(nItem, nSubItem);
					SetListItemText(*m_pxListCtrl, nItem, 1, "%d", GetSetInfoValue(m_xSetInfo[Enum_Buff], strBuff.GetBuffer()));
				}
				else if (nValue == SQuest::eReward_Item)
				{
					CString strName = m_pxListCtrl->GetItemText(nItem, nSubItem);
					CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(strName.GetBuffer());
					if (pItem != NULL)
					{
						SetListItemText(*m_pxListCtrl, nItem, 1, "%d", pItem->ustItemID);
					}
				}
			}
		}
	}

	return 0;
}

LRESULT CQuestEditDlg::OnEditEnd(WPARAM nItem, LPARAM nSubItem)
{
	if (nItem >= 0 && nSubItem >= 0)
	{
		//�����б�
		if (m_pxListCtrl == &m_listProperty)
		{
			/////����ID
			if (nItem == 0 && nSubItem == 1)
			{
				int nQuestId = GetListItemInt(*m_pxListCtrl, nItem, nSubItem, -1);

				SQuest *pQuest = theQuestManager.GetQuest(nQuestId);
				if (pQuest != NULL)
				{
					ShowQuestInformation(*pQuest);
				}
				else
				{
					ClearQuestInformation();

					SetStringId(nQuestId);
				}
			}
			else if ((nItem == 1 || nItem == 3 || nItem == 4) && nSubItem == 2)  //����,  ���� ����  �б༭��Ҫ����
			{				
				int nNameId = GetListItemInt(*m_pxListCtrl, nItem, 1, Empty_String_Id);
				CString strValue = m_pxListCtrl->GetItemText(nItem, nSubItem);
				if (!strValue.IsEmpty() && strValue != Empty_String_Value)
				{						
					nNameId = theXmlString.AddString(nNameId, strValue.GetBuffer());												
										
					SetListItemText(*m_pxListCtrl, nItem, nSubItem - 1, "%d", nNameId);		
				}
			}
		}
		else if (m_pxListCtrl == &m_listPreRequiement || m_pxListCtrl == &m_listPostRequiement)
		{
			CString strName = m_pxListCtrl->GetItemText(nItem, 0);
			int nValue = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strName.GetBuffer());

			if (nSubItem == 1)
			{
				int nId = GetListItemInt(*m_pxListCtrl, nItem, nSubItem, -1);

				if (nValue == SQuest::eRequirement_Profession)
				{
					CString strName = GetSetInfoName(m_xSetInfo[Enum_Profession], nId);
					if (strName.IsEmpty())
					{
						m_pxListCtrl->SetItemText(nItem, nSubItem, "-1");
						strName = Default_Select;
					}
					
					m_pxListCtrl->SetItemText(nItem, 2, strName);
				}
				else if (nValue == SQuest::eRequirement_Sex)
				{
					CString strName = GetSetInfoName(m_xSetInfo[Enum_Sex], nId);
					if (strName.IsEmpty())
					{
						m_pxListCtrl->SetItemText(nItem, nSubItem, "-1");
						strName = Default_Select;
					}

					m_pxListCtrl->SetItemText(nItem, 2, strName);
				}
				else if (nValue == SQuest::eRequirement_Quest)
				{
					CString strName = "";
					SQuest *pQuest = theQuestManager.GetQuest(nId);
					if (pQuest != NULL)
					{
						strName = theXmlString.GetString(pQuest->QuestName);
					}

					m_pxListCtrl->SetItemText(nItem, 2, strName);
				}
				else if (nValue == SQuest::eRequirement_Monster)
				{
					CString strName = "";					
					CItemDetail::SMonster *pMonster = GettheItemDetail().GetMonsterById(nId);
					if (pMonster != NULL)
					{
						strName = pMonster->GetName();
					}
					
					m_pxListCtrl->Resume(nItem, nSubItem);
					m_pxListCtrl->SetItemText(nItem, 2, strName);
				}
				else if (nValue == SQuest::eRequirement_Item)
				{
					CString strName = "";					
					CItemDetail::SItemCommon *pItem = GettheItemDetail().GetItemByID(nId);
					if (pItem != NULL)
					{
						strName = pItem->GetItemName();
					}

					m_pxListCtrl->Resume(nItem, nSubItem);
					m_pxListCtrl->SetItemText(nItem, 2, strName);
				}
			}				
		}
		else if (m_pxListCtrl == &m_listReward)
		{			
			if (nSubItem == 1)
			{
				CString strName = m_pxListCtrl->GetItemText(nItem, 0);
				int nValue = GetSetInfoValue(m_xSetInfo[Enum_Reward], strName.GetBuffer());					
				int nId = GetListItemInt(*m_pxListCtrl, nItem, nSubItem, -1);

				if (nValue == SQuest::eReward_Item)
				{
					CString strName = "";
					CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(nId);
					if (pItem != NULL)
					{
						strName = pItem->GetItemName();
					}

					m_pxListCtrl->SetItemText(nItem, 2, strName);					
				}
				else if (nValue == SQuest::eReward_ReputeName)
				{
					CString strName = GetSetInfoName(m_xSetInfo[Enum_ReputeName], nId);
					if (strName.IsEmpty())
					{
						strName = Default_Select;
					}

					m_pxListCtrl->SetItemText(nItem, 2, strName);
				}
				else if (nValue == SQuest::eReward_Buff)
				{
					CString strName = GetSetInfoName(m_xSetInfo[Enum_Buff], nId);
					if (strName.IsEmpty())
					{
						strName = Default_Select;
					}

					m_pxListCtrl->SetItemText(nItem, 2, strName);
				}
			}			
		}
	}

	return 0;
}


LRESULT CQuestEditDlg::OnCheckbox(WPARAM nItem, LPARAM nSubItem)
{
	if (nItem >= 0 && nSubItem >= 0)
	{
		
	}

	return 0;
}

void CQuestEditDlg::ClickList(CListCtrl &xList, NMHDR *pNMHDR)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nItem = -1;
	int nSubItem = -1;
	if (pNMIA)
	{
		nItem = pNMIA->iItem;
		nSubItem = pNMIA->iSubItem;
	}

	if (nItem >= 0 && nSubItem >= 0)
	{
		m_pxListCtrl = (CXListCtrl*) &xList;  //���浱ǰ��list�ؼ�

		m_strValue = xList.GetItemText(nItem, nSubItem);

		m_nItem = nItem;
		m_nSubItem = nSubItem;
	}
	else
	{
		m_nItem = -1;
		m_nSubItem = -1;
	}
}


void CQuestEditDlg::OnNMClickListReward(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	ClickList(m_listReward, pNMHDR);
	*pResult = 0;
}

void CQuestEditDlg::OnNMClickListPreRequiement(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	ClickList(m_listPreRequiement, pNMHDR);
	*pResult = 0;
}

void CQuestEditDlg::OnNMClickListPostRequiement(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	ClickList(m_listPostRequiement, pNMHDR);

	*pResult = 0;
}

void CQuestEditDlg::OnNMClickListProprety(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	ClickList(m_listProperty, pNMHDR);

	*pResult = 0;
}

void CQuestEditDlg::CheckFilePathExist()
{
	CString strClient = "";
	strClient.Format("%s%s", m_strQuestFile.c_str(), Client_Path);
	if (GetFileAttributes(strClient) == -1)
	{
		_mkdir(strClient.GetBuffer());
	}

	CString strServer = "";
	strServer.Format("%s%s", m_strQuestFile.c_str(), Server_Path);
	if (GetFileAttributes(strServer) == -1)
	{
		_mkdir(strServer.GetBuffer());
	}
}

void CQuestEditDlg::OnFileLoadQuestFile()
{
	// TODO: Add your command handler code here
	SetCurrentWorkDir();
	CString strFolder = InitPath;

	CFolderDialog xFolderDialog(&strFolder);
	if (xFolderDialog.DoModal() == IDOK)
	{
		//���浱ǰ��String�ļ���·��
		m_strQuestFile = strFolder.GetBuffer();

		//�ж�����Client �� Server�ļ���
		CheckFilePathExist();
		
		//���������ļ�
		if (!theQuestInfo.LoadQuest(m_strQuestFile.c_str()))
		{
			AfxMessageBox("���������ļ�ʧ�ܣ�");

			return;
		}

		//������Ʒ�����趨
		m_strDropItemFile.Format("%s%s\\%s", m_strQuestFile.c_str(), Server_Path, Drop_Item_File);
		m_xDropTaskItem.LoadXmlData(m_strDropItemFile.GetBuffer());
		//////////////////////////////////////////////////////////////////////////////////////////////

		//��ʾ�����ռ���
		ShowQuestTreeList();		
	}
}

void CQuestEditDlg::OnFileSaveQuestFile()
{
	// TODO: Add your command handler code here
	if(m_strQuestFile.empty())
	{
		OnFileLoadQuestFile();
	}

	//û���趨�ͷ���
	if (m_strQuestFile.empty())
	{
		return;
	}

	int nId = AddInQuestList();


	//�����������ļ�
	m_xDropTaskItem.SaveXmlData(m_strDropItemFile.GetBuffer());

	//�������
	if (m_checkBatch.GetCheck() == 1 && nId != -1)
	{
		SetListItemText(m_listProperty, 0, 1, "%d", ++nId);
		SetStringId(nId);

		m_listPostRequiement.DeleteAllItems();
	}	
}

//�˳�
void CQuestEditDlg::OnFileExit()
{
	// TODO: Add your command handler code here
	OnOK();
}

//���Ϊ
void CQuestEditDlg::OnFileSaveAt()
{
	// TODO: Add your command handler code here
	CFileDialog FileDlg(false, NULL, NULL, OFN_HIDEREADONLY, "Quest Xml(*.xml)|*.xml|");

	if (FileDlg.DoModal() == IDOK)
	{		
		//���������ļ�
		if (!theQuestInfo.SaveQuest(FileDlg.GetPathName()))
		{
			AfxMessageBox("���������ļ�ʧ�ܣ�");

			return;
		}

		m_strQuestFile = FileDlg.GetPathName();
	}
}

void CQuestEditDlg::OnFileFind()
{
	// TODO: Add your command handler code here
	ShowFindDialog();
}

void CQuestEditDlg::OnNMClickTreeItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_xTreeQuest.GetCursorItem();
	if (hItem != NULL)
	{
		CString strId = m_xTreeQuest.GetItemText(hItem);
		int nId = atoi(strId.GetBuffer());
		SQuest *pQuest = theQuestManager.GetQuest(nId);

		if (pQuest != NULL)
		{
			ShowQuestInformation(*pQuest);
		}
	}

	*pResult = 0;
}

void CQuestEditDlg::OnTvnSelchangedTreeQuest(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_xTreeQuest.GetSelectedItem();
	if (hItem != NULL)
	{
		CString strId = m_xTreeQuest.GetItemText(hItem);
		int nId = atoi(strId.GetBuffer());
		SQuest *pQuest = theQuestManager.GetQuest(nId);

		if (pQuest != NULL)
		{
			ShowQuestInformation(*pQuest);
		}
	}

	*pResult = 0;
}


void CQuestEditDlg::ShowFindQuest(int nId)
{
	if (nId == -1)
	{
		return;
	}

	CString strId = "";
	strId.Format("%d", nId);

	HTREEITEM hItem = m_xTreeQuest.FindNodeItem(Quest_Root, strId);

	if (hItem != NULL)
	{
		m_xTreeQuest.SetFocus();

		m_xTreeQuest.Select(hItem, TVGN_CARET);
		m_xTreeQuest.SelectItem(hItem);

		SQuest *pQuest = theQuestManager.GetQuest(nId);
		if (pQuest != NULL)
		{
			ShowQuestInformation(*pQuest);
		}
	}
}

void CQuestEditDlg::ShowNextFindQuest()
{
	if (m_vecFindQuestId.empty())
	{
		return;
	}

	vector<int>::iterator iter = find(m_vecFindQuestId.begin(), m_vecFindQuestId.end(), m_nShowFindId);
	if (iter != m_vecFindQuestId.end())
	{
		++iter;		
	}

	if (iter == m_vecFindQuestId.end())
	{
		iter = m_vecFindQuestId.begin();
	}

	m_nShowFindId = (*iter);

	ShowFindQuest(m_nShowFindId);
}

CQuestEditDlg::_FindFun CQuestEditDlg::FindFun[Enum_QuestMax] = 
{
	&CQuestEditDlg::FindByQuestId,
	&CQuestEditDlg::FindByQuestNameId,
	&CQuestEditDlg::FindByQuestName,
	&CQuestEditDlg::FindByQuality,
	&CQuestEditDlg::FindByContentId,
	&CQuestEditDlg::FindByContent,
	&CQuestEditDlg::FindByTargetId,
	&CQuestEditDlg::FindByTarget,
	&CQuestEditDlg::FindByMapId,
	&CQuestEditDlg::FindByMapName,
	&CQuestEditDlg::FindByNpcId,
	&CQuestEditDlg::FindByNpcName,
	&CQuestEditDlg::FindByCanAssist,
	&CQuestEditDlg::FindByCanShare,
	&CQuestEditDlg::FindByRepeate,
	&CQuestEditDlg::FindByPreRequementItemId,
	&CQuestEditDlg::FindByPreRequementItemName,
	&CQuestEditDlg::FindByPostRequementItemId,
	&CQuestEditDlg::FindByPostRequementItemName,
	&CQuestEditDlg::FindByRewardItemId,
	&CQuestEditDlg::FindByRewardItemName,
};

int CQuestEditDlg::FindQuest(CString strValue, int nType, FindInfo *pFindInfo /* = NULL */)
{
	m_nShowFindId = -1;
	m_vecFindQuestId.clear();

	if (nType < Enum_QuestMax)
	{
		(this->*FindFun[nType])(strValue, pFindInfo);
	}

	if (!m_vecFindQuestId.empty())
	{
		m_nShowFindId = m_vecFindQuestId[0];
	}

	return m_nShowFindId;
}

void CQuestEditDlg::FindByQuestId(CString strValue, FindInfo *pFindInfo /* = NULL */)
{
	questiter iter = theQuestInfo.m_pQuests.find(atoi(strValue.GetBuffer()));
	if (iter != theQuestInfo.m_pQuests.end())
	{
		if ((*iter).second->Id != -1)
		{
			m_vecFindQuestId.push_back((*iter).second->Id);
		}
	}
}

void CQuestEditDlg::FindByQuestNameId(CString strValue, FindInfo *pFindInfo /* = NULL */)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nNameId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if (nNameId == nNameId)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditDlg::FindByQuestName(CString strValue, FindInfo *pFindInfo /* = NULL */)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nFindMatch = 0;
	if (pFindInfo != NULL)
	{
		nFindMatch = pFindInfo->nFindMatch;
	}

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			string strName = theXmlString.GetString((*iter).second->QuestName);

			if (nFindMatch == 0)
			{
				if (strName == strValue.GetBuffer())
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
			else if (nFindMatch == 1)
			{
				if (strName.find(strValue) != string::npos)
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
		}
	}	
}


void CQuestEditDlg::FindByQuality(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nQuality = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->RankId ==  nQuality)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}

}

void CQuestEditDlg::FindByContentId(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nContentId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->IntroStringId == nContentId)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditDlg::FindByContent(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nFindMatch = 0;
	if (pFindInfo != NULL)
	{
		nFindMatch = pFindInfo->nFindMatch;
	}

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			string strName = theXmlString.GetString((*iter).second->IntroStringId);

			if (nFindMatch == 0)
			{
				if (strName == strValue.GetBuffer())
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
			else if (nFindMatch == 1)
			{
				if (strName.find(strValue) != string::npos)
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
		}
	}	
}

void CQuestEditDlg::FindByTargetId(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nTargetId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->TargetStringId == nTargetId)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditDlg::FindByTarget(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nFindMatch = 0;
	if (pFindInfo != NULL)
	{
		nFindMatch = pFindInfo->nFindMatch;
	}

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			string strName = theXmlString.GetString((*iter).second->TargetStringId);

			if (nFindMatch == 0)
			{
				if (strName == strValue.GetBuffer())
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
			else if (nFindMatch == 1)
			{
				if (strName.find(strValue) != string::npos)
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
		}
	}	
}

void CQuestEditDlg::FindByMapId(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nMapId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->MapId == nMapId)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}


void CQuestEditDlg::FindByMapName(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	int nMapId = GetSetInfoValue(m_xSetInfo[Enum_Map], strValue.GetBuffer());
	if (nMapId == -1)
	{
		return;
	}

	strValue.Format("%d", nMapId);

	FindByMapId(strValue, pFindInfo);
}

void CQuestEditDlg::FindByNpcId(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();


	int nNpcId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->ReplyTargetId == nNpcId)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditDlg::FindByNpcName(CString strValue, FindInfo *pFindInfo)
{
	NpcManager::SNpc *pNpc = GetNpcManager().FindNpcByNpcName(strValue.GetBuffer());
	if (pNpc == NULL)
	{
		return;
	}

	strValue.Format("%d", pNpc->nID);

	FindByNpcId(strValue, pFindInfo);
}



void CQuestEditDlg::FindByCanAssist(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nCanAssist = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->CanAssist == nCanAssist)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditDlg::FindByCanShare(CString strValue, FindInfo *pFindInfo/* = NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nCanShare = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->CanShare == nCanShare)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditDlg::FindByRepeate(CString strValue, FindInfo *pFindInfo /*= NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nRepeate = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			if ((*iter).second->IsRepeat == nRepeate)
			{
				m_vecFindQuestId.push_back((*iter).second->Id);
			}
		}
	}
}

void CQuestEditDlg::FindByPreRequementItemId(CString strValue, FindInfo *pFindInfo /*= NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nItemId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			SQuest::RequirementType::iterator viter = (*iter).second->stReceiveRequirement.begin();
			SQuest::RequirementType::iterator vend = (*iter).second->stReceiveRequirement.end();

			for ( ; viter != vend; ++viter)
			{
				if ((*viter).byType == SQuest::eRequirement_Item && (*viter).Value == nItemId)
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
		}
	}
}

void CQuestEditDlg::FindByPreRequementItemName(CString strValue, FindInfo *pFindInfo /*= NULL*/)
{
	CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(strValue.GetBuffer());
	if (pItem == NULL)
	{
		return;
	}		

	strValue.Format("%d", pItem->ustItemID);

	FindByPreRequementItemId(strValue, pFindInfo);
}

void CQuestEditDlg::FindByPostRequementItemId(CString strValue, FindInfo *pFindInfo /*= NULL*/)
{

	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nItemId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			SQuest::RequirementType::iterator viter = (*iter).second->stCommitRequirement.begin();
			SQuest::RequirementType::iterator vend = (*iter).second->stCommitRequirement.end();

			for ( ; viter != vend; ++viter)
			{
				if ((*viter).byType == SQuest::eRequirement_Item && (*viter).Value == nItemId)
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
		}
	}
}

void CQuestEditDlg::FindByPostRequementItemName(CString strValue, FindInfo *pFindInfo /* = NULL */)
{
	CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(strValue.GetBuffer());
	if (pItem == NULL)
	{
		return;
	}		

	strValue.Format("%d", pItem->ustItemID);
	FindByPostRequementItemId(strValue, pFindInfo);
}

void CQuestEditDlg::FindByRewardItemId(CString strValue, FindInfo *pFindInfo /*= NULL*/)
{
	questiter iter = theQuestInfo.m_pQuests.begin();
	questiter end = theQuestInfo.m_pQuests.end();

	int nItemId = atoi(strValue.GetBuffer());

	for ( ; iter != end; ++iter)
	{
		if ((*iter).second->Id != -1)
		{
			SQuest::RewardType::iterator viter = (*iter).second->stReward.begin();
			SQuest::RewardType::iterator vend = (*iter).second->stReward.end();

			for ( ; viter != vend; ++viter)
			{
				if ((*viter).byType == SQuest::eReward_Item && (*viter).Value == nItemId)
				{
					m_vecFindQuestId.push_back((*iter).second->Id);
				}
			}
		}
	}
}

void CQuestEditDlg::FindByRewardItemName(CString strValue, FindInfo *pFindInfo /* = NULL */)
{
	CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByName(strValue.GetBuffer());
	if (pItem == NULL)
	{
		return;
	}		

	strValue.Format("%d", pItem->ustItemID);
	FindByRewardItemId(strValue, pFindInfo);
}


void CQuestEditDlg::SetListItemCanEdit()
{	
/*	if (m_pxListCtrl == &m_listProperty)
	{
		int nIndex = m_pxListCtrl->GetCurSel();

		if (nIndex == 1 || nIndex == 3 || nIndex == 4 || nIndex == 5)
		{
			m_pxListCtrl->SetEdit(nIndex, 1);
		}			
	}
	else*/ 
	if (m_pxListCtrl == &m_listPostRequiement || m_pxListCtrl == &m_listPreRequiement)
	{
		int nIndex = m_pxListCtrl->GetCurSel();
		
		if (nIndex != -1)
		{
			CString strText = m_pxListCtrl->GetItemText(nIndex, 0);

			int nValue = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strText.GetBuffer());
			if (nValue == SQuest::eRequirement_Monster || nValue == SQuest::eRequirement_Item)
			{
				m_pxListCtrl->SetEdit(nIndex, 1);
			}
		}		
	}
}


string CQuestEditDlg::GetFileFullPath(int nId, const char* pszPath, const char* pExt)
{
	if (nId == -1 || pExt == NULL)
	{
		return "";
	}

	char szFlie[_MAX_PATH] = "";
	if (*pszPath != 0)
	{
		sprintf_s(szFlie, sizeof(szFlie) - 1, "%s%s\\%d%s", m_strQuestFile.c_str(), pszPath, nId, pExt);
	}
	else
	{
		sprintf_s(szFlie, sizeof(szFlie) - 1, "%s\\%d%s", m_strQuestFile.c_str(), nId, pExt);
	}
	
	return szFlie;
}


void CQuestEditDlg::ShowDropItemDialog()
{
	if (m_pxDropItemDialog == NULL)
	{
		m_pxDropItemDialog = new DropItemDialog(this);

		m_pxDropItemDialog->Create(IDD_DIALOG_DROPITEM, this);

		m_pxDropItemDialog->InitInformation();
	}

	if (m_pxDropItemDialog != NULL)
	{
		m_pxDropItemDialog->UpdateInformation();
		m_pxDropItemDialog->ShowWindow(SW_SHOW);
	}
}


void CQuestEditDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	if (m_xTreeQuest.m_hWnd == NULL)
	{
		return;
	}

	RECT rect;
	GetWindowRect(&rect);

	int nHeight = rect.bottom - rect.top - 65;
	int nWidth = rect.right - rect.left - 165;

	int nPosY = 5;
	
	m_xTreeQuest.SetWindowPos(NULL,  5, nPosY, 135, nHeight, SWP_SHOWWINDOW);


	int nPropertyHeight = (29 * nHeight / 100);
	m_listProperty.SetWindowPos(NULL, 150, nPosY, nWidth , nPropertyHeight, SWP_SHOWWINDOW);

	//ǰ��
	nPosY += nPropertyHeight + 5;
	int nPreStaticHeight = (22 * nHeight / 100);
	m_staticPre.SetWindowPos(NULL, 150, nPosY , nWidth, nPreStaticHeight, SWP_SHOWWINDOW);

	int nPreRequiementHeight = (195 * nHeight / 1000);
	m_listPreRequiement.SetWindowPos(NULL, 155, nPosY + 15, nWidth - 10, nPreRequiementHeight, SWP_SHOWWINDOW);

	//�ύ
	nPosY += nPreStaticHeight + 5;
	int nPostStaticHeight = (22 * nHeight / 100);
	m_staticPost.SetWindowPos(NULL, 150, nPosY, nWidth, nPostStaticHeight, SWP_SHOWWINDOW);

	int nPostRequiementHeight = (195 * nHeight / 1000);
	m_listPostRequiement.SetWindowPos(NULL, 155, nPosY + 15, nWidth - 10, nPostRequiementHeight, SWP_SHOWWINDOW);

	//����
	nPosY += nPostStaticHeight + 5;
	int nRewardStaticHeight = (22 * nHeight / 100);
	m_staticReward.SetWindowPos(NULL, 150, nPosY, nWidth, nRewardStaticHeight, SWP_SHOWWINDOW);

	int nRewardHeight = (195 * nHeight / 1000);
	m_listReward.SetWindowPos(NULL, 155, nPosY + 15, nWidth - 10, nRewardHeight, SWP_SHOWWINDOW);

	nPosY += nRewardStaticHeight + 5;

	m_staticSave.SetWindowPos(NULL, 18 *(rect.right - rect.left) / 100, nPosY, 0, 0, SWP_NOSIZE);
	m_checkBatch.SetWindowPos(NULL, 50 *(rect.right - rect.left) / 100, nPosY, 0, 0, SWP_NOSIZE);

	InitListCtrl(false);
}

void CQuestEditDlg::OnNMDClickListPostRequiement(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	int nIndex = m_listPostRequiement.GetCurSel();
	if (nIndex != -1)
	{

		int nQuestId = GetListItemInt(m_listProperty, 0, 1, -1);
		if (nQuestId < 0)
		{
			return;
		}

		CString strType = m_listPostRequiement.GetItemText(nIndex, 0);
		int nType = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strType.GetBuffer());
		if (nType != SQuest::eRequirement_Monster)
		{
			return;
		}

		int nId = GetListItemInt(m_listPostRequiement, nIndex, 1, -1);
		if (nId < 0)
		{
			return;
		}
		int nCount = GetListItemInt(m_listPostRequiement, nIndex, 3, 0);

		m_xMonsterDrop.Clear();
		
		m_xMonsterDrop.nMonsterId = nId;
		m_xMonsterDrop.nMonsterCount = nCount;
		m_xMonsterDrop.nQuestId = nQuestId;

		//���ҹ�������
		DropTaskItem::STask xTask;
		if (m_xDropTaskItem.FindDropItemByMonsterId(nId, nQuestId, xTask) != -1)
		{
			m_xMonsterDrop.nVarId = xTask.nVarId;
			m_xMonsterDrop.nItemId = xTask.stItem.nItemId;
			m_xMonsterDrop.nItemRate = xTask.stItem.nProbability;
			m_xMonsterDrop.nItemCount = xTask.nMaxItemCount;
		}
					
		//����ʾ	
		ShowDropItemDialog();
	}
	*pResult = 0;
}


void CQuestEditDlg::SetListItemColor(CXListCtrl &xList, int nItem, int nSubItem, COLORREF dwColor)
{
	if (nItem < 0 || nSubItem < 0)
	{
		return;
	}

	COLORREF crText, crBGround;

	xList.GetItemColors(nItem, nSubItem, crText, crBGround);

	xList.SetItemColors(nItem, nSubItem, dwColor, crBGround);
}


void CQuestEditDlg::SetListItemBGroundColor(CXListCtrl &xList, int nItem, int nSubItem, COLORREF dwColor)
{
	if (nItem < 0 || nSubItem < 0)
	{
		return;
	}

	COLORREF crText, crBGround;

	xList.GetItemColors(nItem, nSubItem, crText, crBGround);

	xList.SetItemColors(nItem, nSubItem, crText, dwColor);
}

void CQuestEditDlg::OnNMRclickListPostRequeiment(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	int nIndex = m_listPostRequiement.GetCurSel();
	if (nIndex != -1)
	{
		CString strType = m_listPostRequiement.GetItemText(nIndex, 0);
		int nType = GetSetInfoValue(m_xSetInfo[Enum_Requirement], strType.GetBuffer());
		if (nType == SQuest::eRequirement_Monster)
		{
			CMenu menu;
			CPoint xPoint;
			GetCursorPos(&xPoint);
			menu.LoadMenu(IDR_MENU_DELETE);
			menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, xPoint.x, xPoint.y, this);
		}
	}

	*pResult = 0;
}

void CQuestEditDlg::OnDelete()
{
	// TODO: Add your command handler code here
	int nIndex = m_listPostRequiement.GetCurSel();
	if (nIndex != -1)
	{
		int nQuestId = GetListItemInt(m_listProperty, 0, 1, -1);
		int nMonsterId = GetListItemInt(m_listPostRequiement, nIndex, 1, -1);

		m_xDropTaskItem.SubQuest(nMonsterId, nQuestId);

		m_listPostRequiement.DeleteItem(nIndex);
	}
}

void CQuestEditDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	if (nIDEvent == SaveShow_Timer_Id)
	{
		m_staticSave.SetWindowText("");

		KillTimer(SaveShow_Timer_Id);
	}	

	CDialog::OnTimer(nIDEvent);
}


void CQuestEditDlg::SetStringId(int nQuestId)
{
	if (nQuestId < 0)
	{
		return;
	}

	static char* p_szFormat = "%d%02d";

	int i = 0; 
	CString strString  = "";

	strString.Format(p_szFormat, nQuestId, ++i);
	m_listProperty.SetItemText(1, 1, strString);
	m_listProperty.SetItemText(1, 2, "");

	strString.Format(p_szFormat, nQuestId, ++i);
	m_listProperty.SetItemText(3, 1, strString);
	m_listProperty.SetItemText(3, 2, "");

	strString.Format(p_szFormat, nQuestId, ++i);
	m_listProperty.SetItemText(4, 1, strString);
	m_listProperty.SetItemText(4, 2, "");

}


void CQuestEditDlg::OnStringChange()
{
	// TODO: Add your command handler code here

	StringFileChange xStringFileChange;
	xStringFileChange.DoModal();
}

void CQuestEditDlg::OnNpcChange()
{
	// TODO: Add your command handler code here

	NpcFileChange xNpcFileChange;
	xNpcFileChange.DoModal();
}
