// QuestSet.cpp : implementation file
//

#include "stdafx.h"
#include "QuestEditor.h"
#include "QuestSet.h"

#include "slkreader/SlkReader.h"

// QuestSet dialog

IMPLEMENT_DYNAMIC(QuestSet, CDialog)

QuestSet::QuestSet(CWnd* pParent /*=NULL*/)
	: CDialog(QuestSet::IDD, pParent)
	, m_nRadioType(0)
{

}

QuestSet::QuestSet(CQuestEditDlg *pParent)		
{
	m_xpQuestEdit = pParent;

	m_nRadioType = 0;
}

QuestSet::~QuestSet()
{
}

void QuestSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nRadioType);
	DDX_Control(pDX, IDC_EDIT1, m_editName);
	DDX_Control(pDX, IDC_LISTVALUE, m_listSetInfo);
	DDX_Control(pDX, IDC_EDIT3, m_editValue);
	DDX_Control(pDX, IDC_EDIT2, m_editItemFile);
	DDX_Control(pDX, IDC_EDIT4, m_editMonsterFile);
	DDX_Control(pDX, IDC_EDIT5, m_editNpcFile);
	DDX_Control(pDX, IDC_EDIT6, m_editStringFile);
	DDX_Control(pDX, IDC_EDIT7, m_editSlkFile);
	DDX_Control(pDX, IDC_EDIT8, m_editStringXmlFile);
}


BEGIN_MESSAGE_MAP(QuestSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &QuestSet::OnBnClickedButtonAddString)
	ON_BN_CLICKED(IDC_RADIO1, &QuestSet::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &QuestSet::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &QuestSet::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &QuestSet::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &QuestSet::OnBnClickedRadio5)	
	ON_BN_CLICKED(IDC_RADIO6, &QuestSet::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &QuestSet::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &QuestSet::OnBnClickedRadio8)	
	ON_BN_CLICKED(IDC_RADIO9, &QuestSet::OnBnClickedRadio9)
	ON_BN_CLICKED(IDOK, &QuestSet::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON9, &QuestSet::OnBnClickedButtonEdit)
	ON_COMMAND(ID_DELETE, &QuestSet::OnDelete)
	ON_WM_SYSCOMMAND()	
	ON_NOTIFY(NM_RCLICK, IDC_LISTVALUE, &QuestSet::OnNMRclickListValue)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTVALUE, &QuestSet::OnNMDblclkListValue)

	ON_BN_CLICKED(IDC_BUTTON13, &QuestSet::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON15, &QuestSet::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &QuestSet::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &QuestSet::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON19, &QuestSet::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON18, &QuestSet::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON20, &QuestSet::OnBnClickedButtonStringChange)
END_MESSAGE_MAP()


// QuestSet message handlers

BOOL QuestSet::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
		case VK_ESCAPE:
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void QuestSet::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default
	if (nID == SC_CLOSE)
	{
		OnBnClickedOk();	//关闭的时候要保存
	}

	CDialog::OnSysCommand(nID, lParam);
}


void QuestSet::InitInformation()
{
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	int nWidth = m_xpQuestEdit->SetListCtrlStyle(m_listSetInfo, dwStyle);

	m_listSetInfo.InsertColumn(0, "名称", 0, (50 * nWidth) / 100);
	m_listSetInfo.InsertColumn(1, "数值", 0, (50 * nWidth) / 100);
	/////////////////////////////////////////////////////////////////////////////

	ShowSetInfoList(m_nRadioType);

	m_editItemFile.SetWindowText(m_xpQuestEdit->m_szItemFile);
	m_editMonsterFile.SetWindowText(m_xpQuestEdit->m_szMonsterFile);
	m_editNpcFile.SetWindowText(m_xpQuestEdit->m_szNpcFile);
	m_editStringFile.SetWindowText(m_xpQuestEdit->m_szStringFile);
}

void QuestSet::ShowSetInfoList(const int nType)
{
	if (nType >= Enum_End)
	{
		return;
	}

	ShowSetInfoList(m_xpQuestEdit->m_xSetInfo[nType]);	

	m_editName.SetWindowText("");
	m_editValue.SetWindowText("");
}

void QuestSet::ShowSetInfoList(vector<SetInfo> &vecSetInfo)
{
	m_listSetInfo.DeleteAllItems();

	setiter iter = vecSetInfo.begin();
	setiter end = vecSetInfo.end();

	for (int i = 0; iter != end; ++iter, ++i)
	{
		m_listSetInfo.InsertItem(i, (*iter).strName.c_str());
		m_xpQuestEdit->SetListItemText(m_listSetInfo, i, 1, "%d", (*iter).nValue);
	}
}

void QuestSet::AddSetInfo(const int nType)
{
	CString strName = "";
	CString strValue = "";

	m_editName.GetWindowText(strName);
	m_editValue.GetWindowText(strValue);

	if (nType >= Enum_End || strName.IsEmpty() || strValue.IsEmpty())
	{
		return;
	}

	SetInfo xSetInfo;
	xSetInfo.strName = strName.GetBuffer();
	xSetInfo.nValue = atoi(strValue.GetBuffer());

	AddSetInfo(m_xpQuestEdit->m_xSetInfo[nType], xSetInfo, m_xpQuestEdit->m_xStringArray[nType]);
}

void QuestSet::AddSetInfo(vector<SetInfo> &vecSetInfo, SetInfo &xSetInfo, CStringArray &xStringArray)
{
	setiter iter = vecSetInfo.begin();
	setiter end = vecSetInfo.end();
	for ( ; iter != end; ++iter)
	{
		if ((*iter).strName == xSetInfo.strName && (*iter).nValue == xSetInfo.nValue)
		{
			return;
		}
	}

	vecSetInfo.push_back(xSetInfo);
	xStringArray.Add(xSetInfo.strName.c_str());
	
	int nCount = m_listSetInfo.GetItemCount();
	m_listSetInfo.InsertItem(nCount, xSetInfo.strName.c_str());
	m_xpQuestEdit->SetListItemText(m_listSetInfo, nCount, 1, "%d", xSetInfo.nValue);
}

int QuestSet::EditSetInfo(const int nType)
{
	int nIndex = m_xpQuestEdit->GetListCtrlCurSel(m_listSetInfo);
	if (nIndex == -1 || nType >= Enum_End)
	{
		return -1;
	}	

	CString strName = m_listSetInfo.GetItemText(nIndex, 0);
	CString strValue = m_listSetInfo.GetItemText(nIndex, 1);

	SetInfo xSetInfo;
	xSetInfo.strName = strName.GetBuffer();
	xSetInfo.nValue = atoi(strValue.GetBuffer());	

	return EditSetInfo(m_xpQuestEdit->m_xSetInfo[nType], xSetInfo, m_xpQuestEdit->m_xStringArray[nType]);	
}

int QuestSet::EditSetInfo(vector<SetInfo> &vecSetInfo, SetInfo &xSetInfo, CStringArray &xStringArray)
{
	CString strNewName = "";
	CString strNewValue = "";

	m_editName.GetWindowText(strNewName);
	m_editValue.GetWindowText(strNewValue);

	if (strNewName.IsEmpty() || strNewValue.IsEmpty())
	{
		return -1;
	}

	setiter iter = vecSetInfo.begin();
	setiter end = vecSetInfo.end();

	for (int i = 0; iter != end; ++iter, ++i)
	{
		if ((*iter).strName == xSetInfo.strName && (*iter).nValue == xSetInfo.nValue)
		{
			(*iter).strName = strNewName.GetBuffer();
			(*iter).nValue = atoi(strNewValue.GetBuffer());
		
			xStringArray.SetAt(i + 1, strNewName);	

			return i;
		}
	}

	return -1;
}

int  QuestSet::DelStringArray(const int nType)
{	
	int nIndex =m_xpQuestEdit->GetListCtrlCurSel(m_listSetInfo);
	if (nIndex == -1 || nType >= Enum_End)
	{
		return -1;
	}	

	CString strName = m_listSetInfo.GetItemText(nIndex, 0);
	CString strValue = m_listSetInfo.GetItemText(nIndex, 1);

	SetInfo xSetInfo;
	xSetInfo.strName = strName.GetBuffer();
	xSetInfo.nValue = atoi(strValue.GetBuffer());	
	
	return DelStringArray(m_xpQuestEdit->m_xSetInfo[nType], xSetInfo, m_xpQuestEdit->m_xStringArray[nType]);		
}

int QuestSet::DelStringArray(vector<SetInfo> &vecSetInfo, SetInfo &xSetInfo, CStringArray &xStringArray)
{	
	setiter iter = vecSetInfo.begin();
	setiter end = vecSetInfo.end();

	for (int i = 0; iter != end; ++iter, ++i)
	{
		if ((*iter).strName == xSetInfo.strName && (*iter).nValue == xSetInfo.nValue)
		{
			vecSetInfo.erase(iter);
			xStringArray.RemoveAt(i + 1);
			return i;
		}
	}

	return -1;
}

//添加
void QuestSet::OnBnClickedButtonAddString()
{
	// TODO: Add your control notification handler code here

	AddSetInfo(m_nRadioType);
}


//修改
void QuestSet::OnBnClickedButtonEdit()
{
	// TODO: Add your control notification handler code here

	int nIndex = EditSetInfo(m_nRadioType);

	if (nIndex == -1)
	{
		return;
	}

	CString strName = "";
	CString strValue = "";
	m_editName.GetWindowText(strName);
	m_editValue.GetWindowText(strValue);

	m_listSetInfo.SetItemText(nIndex, 0, strName);
	m_listSetInfo.SetItemText(nIndex, 1, strValue);
}

//显示删除菜单
void QuestSet::ShowDeleteMenu()
{
	int nIndex = m_xpQuestEdit->GetListCtrlCurSel(m_listSetInfo);

	if (nIndex == -1)
	{
		return;
	}

	CMenu menu;
	CPoint xPoint;
	GetCursorPos(&xPoint);
	menu.LoadMenu(IDR_MENU_POP);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, xPoint.x, xPoint.y, this);
}

//删除一个
void QuestSet::OnDelete()
{
	// TODO: Add your command handler code here
	int nIndex = DelStringArray(m_nRadioType);

	if (nIndex != -1)
	{
		m_listSetInfo.DeleteItem(nIndex);
	}	
}

void QuestSet::OnLbnDblclkList()
{
	// TODO: Add your control notification handler code here
	int nIndex = m_xpQuestEdit->GetListCtrlCurSel(m_listSetInfo);

	if (nIndex == -1)
	{
		return;
	}

	CString strName = m_listSetInfo.GetItemText(nIndex, 0);
	CString strValue = m_listSetInfo.GetItemText(nIndex, 1);

	m_editName.SetWindowText(strName);
	m_editValue.SetWindowText(strValue);
}


void QuestSet::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_xpQuestEdit->SaveSetInfoFile();

	m_xpQuestEdit->InitCtrlList();

	this->ShowWindow(SW_HIDE);
}


void QuestSet::OnNMRclickListValue(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int iIndex = m_xpQuestEdit->GetListCtrlCurSel(m_listSetInfo);
	if (iIndex != -1)
	{
		ShowDeleteMenu();
	}
}



void QuestSet::OnNMDblclkListValue(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int iIndex = m_xpQuestEdit->GetListCtrlCurSel(m_listSetInfo);
	if (iIndex != -1)
	{
		m_editName.SetWindowText(m_listSetInfo.GetItemText(iIndex, 0));
		m_editValue.SetWindowText(m_listSetInfo.GetItemText(iIndex, 1));
	}
}


void QuestSet::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here

	if (m_nRadioType == Enum_Map)
	{
		return;
	}

	m_nRadioType = Enum_Map;
	ShowSetInfoList(m_nRadioType);
}

void QuestSet::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	if (m_nRadioType == Enum_Profession)
	{
		return;
	}

	m_nRadioType = Enum_Profession;
	ShowSetInfoList(m_nRadioType);
}

void QuestSet::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
	if (m_nRadioType == Enum_Level)
	{
		return;
	}

	m_nRadioType = Enum_Level;
	ShowSetInfoList(m_nRadioType);
}

void QuestSet::OnBnClickedRadio4()
{
	// TODO: Add your control notification handler code here
	if (m_nRadioType == Enum_Requirement)
	{
		return;
	}

	m_nRadioType = Enum_Requirement;
	ShowSetInfoList(m_nRadioType);
}

void QuestSet::OnBnClickedRadio5()
{
	// TODO: Add your control notification handler code here
	if (m_nRadioType == Enum_Reward)
	{
		return;
	}

	m_nRadioType = Enum_Reward;
	ShowSetInfoList(m_nRadioType);
}

void QuestSet::OnBnClickedRadio7()
{
	// TODO: Add your control notification handler code here

	if (m_nRadioType == Enum_ReputeName)
	{
		return;
	}

	m_nRadioType = Enum_ReputeName;
	ShowSetInfoList(m_nRadioType);
}

void QuestSet::OnBnClickedRadio8()
{
	// TODO: Add your control notification handler code here

	if (m_nRadioType == Enum_Buff)
	{
		return;
	}

	m_nRadioType = Enum_Buff;
	ShowSetInfoList(m_nRadioType);
}

void QuestSet::OnBnClickedRadio6()
{
	// TODO: Add your control notification handler code here

	if (m_nRadioType == Enum_Refer)
	{
		return;
	}

	m_nRadioType = Enum_Refer;
	ShowSetInfoList(m_nRadioType);
}

void QuestSet::OnBnClickedRadio9()
{
	// TODO: Add your control notification handler code here
	if (m_nRadioType == Enum_Sex)
	{
		return;
	}

	m_nRadioType = Enum_Sex;
	ShowSetInfoList(m_nRadioType);
}

void QuestSet::OnBnClickedButton13()
{
	// TODO: Add your control notification handler code here

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "Item File(Item.pak)|Item.pak|");

	if (FileDlg.DoModal() == IDOK)
	{
		strcpy_s(m_xpQuestEdit->m_szItemFile, sizeof(m_xpQuestEdit->m_szItemFile), FileDlg.GetPathName());
		m_editItemFile.SetWindowText(FileDlg.GetPathName());		
	}	
}

void QuestSet::OnBnClickedButton15()
{
	// TODO: Add your control notification handler code here

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "Monster File(Monster.slk)|Monster.slk|");

	if (FileDlg.DoModal() == IDOK)
	{
		strcpy_s(m_xpQuestEdit->m_szMonsterFile, sizeof(m_xpQuestEdit->m_szMonsterFile), FileDlg.GetPathName());
		m_editMonsterFile.SetWindowText(FileDlg.GetPathName());		
	}
}

void QuestSet::OnBnClickedButton16()
{
	// TODO: Add your control notification handler code here

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "Npc File(Npc.slk)|Npc.slk|");

	if (FileDlg.DoModal() == IDOK)
	{
		strcpy_s(m_xpQuestEdit->m_szNpcFile, sizeof(m_xpQuestEdit->m_szNpcFile), FileDlg.GetPathName());
		m_editNpcFile.SetWindowText(FileDlg.GetPathName());		
	}
}

void QuestSet::OnBnClickedButton17()
{
	// TODO: Add your control notification handler code here

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "String File(String.xml)|String.xml|");

	if (FileDlg.DoModal() == IDOK)
	{
		strcpy_s(m_xpQuestEdit->m_szStringFile, sizeof(m_xpQuestEdit->m_szStringFile), FileDlg.GetPathName());
		m_editStringFile.SetWindowText(FileDlg.GetPathName());		
	}
}

void QuestSet::OnBnClickedButton19()
{
	// TODO: Add your control notification handler code here

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "String Slk(String.slk)|String.slk|");

	if (FileDlg.DoModal() == IDOK)
	{
		m_editStringSlkFile.SetWindowText(FileDlg.GetPathName());		
	}
}

void QuestSet::OnBnClickedButton18()
{
	// TODO: Add your control notification handler code here
	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "String Xml(String.xml)|String.xml|");

	if (FileDlg.DoModal() == IDOK)
	{
		m_editStringXmlFile.SetWindowText(FileDlg.GetPathName());		
	}
}

void QuestSet::OnBnClickedButtonStringChange()
{
	// TODO: Add your control notification handler code here

	CString strSlk = "";
	m_editStringSlkFile.GetWindowText(strSlk);

	CString strXml = "";
	m_editStringXmlFile.GetWindowText(strXml);

	if (strSlk.IsEmpty() || strXml.IsEmpty())
	{
		return;
	}

	if (LoadFromSlk(strSlk.GetBuffer()))
	{
		if (theString.SaveLanguageFile(strXml.GetBuffer()))
		{
			AfxMessageBox("转换成功！");
		}
		

	}
	

}


bool QuestSet::LoadFromSlk( char* szFileName )
{
	CSlkReader reader;
	if( !reader.ReadFromFile( szFileName ) )
	{
		assert(false&&"找不到Slk文件");
		return false;
	}

	int nLine = 2;
	int	nIndex = 0;
	CSlkReader::SField* pField = NULL;
	std::string	strData;
	while( CSlkReader::ret_readover != reader.GotoNextLine( nLine+1 ) )
	{
		// 第一列
		pField = reader.GetFieldOfLine( 1 );
		if( !pField || pField->iFieldType != CSlkReader::field_int )
		{
			assert( false );
			return false;
		}
		if ( nIndex != pField->data.iValue )
		{
			assert( false&&"索引没有按顺序!" );
			return false;
		}
		// 读相应的语言
		//pField = reader.GetFieldOfLine( m_enCurLanguage );
		pField = reader.GetFieldOfLine( 2 );
		if( !pField || pField->iFieldType != CSlkReader::field_string )
		{
			strData = "";
		}
		else
		{
			strData = pField->data.szValue;
		}

		theString.AddString(strData);

		++nIndex;
		++nLine;
	}
	return true;
}


