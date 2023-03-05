// LoginInfo.cpp : implementation file
//

#include "stdafx.h"
#include "LoginInfo.h"
#include "Bot.h"
#include "Client.h"


#define CONFIG_FILE_PATH "Client.ini"
// LoginInfo dialog

IMPLEMENT_DYNAMIC(LoginInfo, CDialog)

LoginInfo::LoginInfo(CWnd* pParent /*=NULL*/)
	: CDialog(LoginInfo::IDD, pParent)
	, m_RadioSale(FALSE)
	, m_RadioPrefession(FALSE)
{
	m_pClient = NULL;
}

LoginInfo::~LoginInfo()
{
}

void LoginInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, m_buttonSend);
	DDX_Control(pDX, IDC_BUTTON3, m_buttonEnter);
	DDX_Control(pDX, IDC_BUTTON5, m_buttonCreate);
	DDX_Control(pDX, IDC_BUTTON4, m_buttonDelete);
	DDX_Control(pDX, IDC_BUTTON6, m_buttonLoginOut);
	DDX_Control(pDX, IDC_BUTTON7, m_buttonCheck);
	DDX_Control(pDX, IDC_BUTTON8, m_buttonCreateOk);
	DDX_Control(pDX, IDC_BUTTON10, m_buttonReset);
	DDX_Control(pDX, IDC_BUTTON9, m_buttonCancle);
	DDX_Control(pDX, IDC_EDIT1, m_editAccount);
	DDX_Control(pDX, IDC_EDIT2, m_editPassword);
	DDX_Control(pDX, IDC_CHECK1, m_CheckSave);
	DDX_Control(pDX, IDC_EDIT15, m_editName);
	DDX_Radio(pDX, IDC_RADIO1, m_RadioSale);
	DDX_Radio(pDX, IDC_RADIO4, m_RadioPrefession);
	DDX_Control(pDX, IDC_LIST1, m_listChar);
}


BEGIN_MESSAGE_MAP(LoginInfo, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &LoginInfo::OnBnClickedButtonLoginIn)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &LoginInfo::OnNMClickListChar)
	ON_BN_CLICKED(IDC_BUTTON3, &LoginInfo::OnBnClickedButtonEnter)
	ON_BN_CLICKED(IDC_BUTTON5, &LoginInfo::OnBnClickedButtonCreateChar)
	ON_BN_CLICKED(IDC_BUTTON9, &LoginInfo::OnBnClickedButtonCancle)
	ON_BN_CLICKED(IDC_BUTTON7, &LoginInfo::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON10, &LoginInfo::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON6, &LoginInfo::OnBnClickedButtonLoginOut)
	ON_BN_CLICKED(IDC_BUTTON8, &LoginInfo::OnBnClickedButtonCreateOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &LoginInfo::OnNMDblclkListChar)
END_MESSAGE_MAP()


// LoginInfo message handlers

BOOL LoginInfo::PreTranslateMessage(MSG* pMsg)
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

void LoginInfo::InitInformation()
{	
	ReadClientConfig();

	m_buttonEnter.EnableWindow(FALSE);
	m_buttonCreate.EnableWindow(FALSE);
	m_buttonDelete.EnableWindow(FALSE);
	m_buttonLoginOut.EnableWindow(FALSE);

	m_buttonCheck.EnableWindow(FALSE);
	m_buttonCreateOk.EnableWindow(FALSE);
	m_buttonReset.EnableWindow(FALSE);
	m_buttonCancle.EnableWindow(FALSE);

	/////////////////////////////////////////////////////////////////////
	RECT rect;
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	int nWidth = 0;
	int iIndex = 0;
		
	m_listChar.SetExtendedStyle(dwStyle);

	m_listChar.GetClientRect(&rect);
	nWidth = rect.right - rect.left;

	m_listChar.InsertColumn(iIndex++, _T("名称"), 0, (30 * nWidth / 100));
	m_listChar.InsertColumn(iIndex++, _T("等级"), 0, (20 * nWidth / 100));
	m_listChar.InsertColumn(iIndex++, _T("职业"), 0, (20 * nWidth / 100));
	m_listChar.InsertColumn(iIndex++, _T("生日"), 0, (30 * nWidth / 100));
}

void LoginInfo::ReadClientConfig()
{
	int nCheck = ::GetPrivateProfileInt("Client", "Save", 0, CONFIG_FILE_PATH);
	m_CheckSave.SetCheck(nCheck);

	char szAccount[50] = "";
	::GetPrivateProfileString("Client", "Account", "", szAccount, sizeof(szAccount) - 1, CONFIG_FILE_PATH);
	m_editAccount.SetWindowText(szAccount);

	char szPassword[50] = "";
	::GetPrivateProfileString("Client", "Password", "", szPassword, sizeof(szPassword) - 1, CONFIG_FILE_PATH);
	m_editPassword.SetWindowText(szPassword);	
}


void LoginInfo::SaveClientConfig()
{
	CString strValue = "";

	int nCheck = m_CheckSave.GetCheck();
	strValue.Format("%d", nCheck);
	WritePrivateProfileString("Client", "Save", strValue.GetBuffer(), CONFIG_FILE_PATH);

	if (nCheck == 0)
	{
		WritePrivateProfileString("Client", "Account", "", CONFIG_FILE_PATH);		
		WritePrivateProfileString("Client", "Password", "", CONFIG_FILE_PATH);
		return;
	}
	
	m_editAccount.GetWindowText(strValue);
	WritePrivateProfileString("Client", "Account", strValue.GetBuffer(), CONFIG_FILE_PATH);

	m_editPassword.GetWindowText(strValue);
	WritePrivateProfileString("Client", "Password", strValue.GetBuffer(), CONFIG_FILE_PATH);

}


void LoginInfo::OnBnClickedButtonLoginIn()
{
	// TODO: Add your control notification handler code here
	CString strAccount = "";
	m_editAccount.GetWindowText(strAccount);

	CString strPassword = "";
	m_editPassword.GetWindowText(strPassword);

	if (strAccount.IsEmpty() || strPassword.IsEmpty())
	{
		return;
	}

	SaveClientConfig();

	if (m_pClient == NULL)
	{
		m_pClient = new Client(this);
		if (m_pClient != NULL)
		{
			theApp.gBotApplication.AddClientInMapList(m_pClient);
		}
	}
	
	if (m_pClient == NULL)
	{
		return;
	}

	m_pClient->SetAccount(strAccount.GetBuffer());
	m_pClient->SetPassword(strPassword.GetBuffer());

	//m_pClient->LoginServer();
}

void LoginInfo::OnNMClickListChar(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listChar.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_listChar.GetNextSelectedItem(pos);
		if (nIndex != -1)
		{
			if (m_pClient->GetBotState() != State_Play)
			{	
				if (m_pClient->m_vecDelete[nIndex] == 0)
				{
					m_buttonEnter.EnableWindow(TRUE);
					m_buttonDelete.SetWindowText(_T("删除角色"));
					m_buttonDelete.EnableWindow(TRUE);
				}
				else
				{
					m_buttonEnter.EnableWindow(FALSE);
					m_buttonDelete.SetWindowText(_T("恢复角色"));
					m_buttonDelete.EnableWindow(TRUE);
				}
			}
			else
			{
				m_buttonEnter.EnableWindow(FALSE);
				m_buttonDelete.EnableWindow(FALSE);
				m_buttonCreate.EnableWindow(FALSE);
			}
		}		
	}
	else
	{
		m_buttonEnter.EnableWindow(FALSE);
		m_buttonDelete.EnableWindow(FALSE);
	}

	*pResult = 0;
}

void LoginInfo::OnBnClickedButtonEnter()
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listChar.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nIndex = m_listChar.GetNextSelectedItem(pos);
		if (nIndex != -1)
		{
			m_pClient->EnterWorld(nIndex);
		}
	}
}

void LoginInfo::OnBnClickedButtonCreateChar()
{
	// TODO: Add your control notification handler code here

	m_buttonCreateOk.EnableWindow(TRUE);
	m_buttonCheck.EnableWindow(TRUE);
	m_buttonReset.EnableWindow(TRUE);
	m_buttonCancle.EnableWindow(TRUE);

	m_pClient->SetTipsInfo("开始创建角色");
}

void LoginInfo::OnBnClickedButtonCancle()
{
	// TODO: Add your control notification handler code here
	m_buttonCreateOk.EnableWindow(FALSE);
	m_buttonCheck.EnableWindow(FALSE);
	m_buttonReset.EnableWindow(FALSE);
	m_buttonCancle.EnableWindow(FALSE);
}


void LoginInfo::OnBnClickedButtonCheck()
{
	// TODO: Add your control notification handler code here
	CString strName = "";

	m_editName.GetWindowText(strName);
	if (strName.IsEmpty())
	{
		AfxMessageBox(_T("请输入角色名称"));
		return;
	}

	MsgReqCreateCheckName xMsg;

	strncpy(xMsg.szName, strName.GetBuffer(), sizeof(xMsg.szName) - 1);

	m_pClient->SendMsg(&xMsg);
}

void LoginInfo::OnBnClickedButtonReset()
{
	// TODO: Add your control notification handler code here

	m_editName.SetWindowText("");

	m_RadioSale = FALSE;
	m_RadioPrefession = FALSE;

	UpdateData(FALSE);
}

void LoginInfo::OnBnClickedButtonLoginOut()
{
	// TODO: Add your control notification handler code here

	m_listChar.DeleteAllItems();
	
	m_buttonSend.EnableWindow(TRUE);

	m_buttonEnter.EnableWindow(FALSE);
	m_buttonCreate.EnableWindow(FALSE);
	m_buttonDelete.EnableWindow(FALSE);
	m_buttonLoginOut.EnableWindow(FALSE);

	m_buttonCheck.EnableWindow(FALSE);
	m_buttonCreateOk.EnableWindow(FALSE);
	m_buttonReset.EnableWindow(FALSE);
	m_buttonCancle.EnableWindow(FALSE);

	MsgExit xMsg;	
	m_pClient->SendMsg(&xMsg);

	m_pClient->SetBotState(State_End);
}

void LoginInfo::OnBnClickedButtonCreateOk()
{
	// TODO: Add your control notification handler code here

	CString strName = "";
	m_editName.GetWindowText(strName);
	if (strName.IsEmpty())
	{
		return;
	}

	UpdateData(TRUE);

	static MsgCreateHeroChar xMsg;

	xMsg.stWhichSlot = m_listChar.GetItemCount();
	strncpy(xMsg.create.szCharacterName, strName.GetBuffer(), sizeof(xMsg.create.szCharacterName) - 1);
	
	xMsg.create.usProfession = m_RadioPrefession;		
	xMsg.create.ucSex = m_RadioSale;
	
	xMsg.create.ucFaceIndex = Race_China;					// 种族
	xMsg.create.ucHairColorIndex = (unsigned char)0;	//头发颜色的索引
	xMsg.create.ucHairModelIndex = (unsigned char)0;	//头发模型的索引
	xMsg.create.ucModelIndex = (unsigned char)0;		//身体模型的索引
	xMsg.create.ucHeadPic = (unsigned char)0;

	m_pClient->SendMsg(&xMsg);
}

void LoginInfo::CreateCharSuccess()
{	
	///////////////////////////////////////////////////////
	m_buttonCheck.EnableWindow(FALSE);
	m_buttonCreateOk.EnableWindow(FALSE);
	m_buttonReset.EnableWindow(FALSE);
	m_buttonCancle.EnableWindow(FALSE);
}


void LoginInfo::OnNMDblclkListChar(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	OnBnClickedButtonEnter();

	*pResult = 0;
}