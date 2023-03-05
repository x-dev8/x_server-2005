// QuestStringEdit.cpp : implementation file
//

#include "stdafx.h"
#include "QuestEditor.h"
#include "QuestStringEdit.h"
#include "XmlStringLanguage.h"
#include "Define.h"
#include "QuestEditorView.h"

// QuestStringEdit dialog

IMPLEMENT_DYNAMIC(QuestStringEdit, CDialog)

QuestStringEdit::QuestStringEdit(CWnd* pParent /*=NULL*/)
	: CDialog(QuestStringEdit::IDD, pParent)
	,m_nQuestId(-1)
{

}

QuestStringEdit::~QuestStringEdit()
{
}

void QuestStringEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboId);
	DDX_Control(pDX, IDC_LIST1, m_listString);
	DDX_Control(pDX, IDC_EDIT1, m_editString);
}


BEGIN_MESSAGE_MAP(QuestStringEdit, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &QuestStringEdit::OnBnClickedButtonAddString)
	ON_WM_SYSCOMMAND()
	ON_LBN_DBLCLK(IDC_LIST1, &QuestStringEdit::OnLbnDblclkListQuest)
	ON_BN_CLICKED(IDC_BUTTON3, &QuestStringEdit::OnBnClickedButtonRemove)
	ON_CBN_SELCHANGE(IDC_COMBO1, &QuestStringEdit::OnCbnSelchangeComboId)
END_MESSAGE_MAP()


BOOL QuestStringEdit::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		//case VK_RETURN:
		case VK_ESCAPE:
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

// QuestStringEdit message handlers
void QuestStringEdit::InitInformation()
{

}


void QuestStringEdit::UpdateInitInformation(const char* path, int nQuestId)
{
	if (path == NULL || *path == 0 || nQuestId < 0)
	{
		m_nQuestId = -1;
		return;
	}

	m_nQuestId = nQuestId;
	m_strFilePath.Format("%s%s\\%d%s", path, Client_Path, nQuestId, String_Ext);

	m_comboId.ResetContent();
	m_listString.ResetContent();
	m_editString.SetWindowText("");

	for (int i = 11; i < StringId_Count; ++i)//zhuxincong 7.6.2012 把StringId_Count的值从30改成了50 策划需求，这里的for循环是任务编织器下拉菜单中的数值。
	{
		CString strId = "";

		strId.Format("%d%d", nQuestId, i);
		m_comboId.AddString(strId);

		int nId = atoi(strId.GetBuffer());

		CString strValue = theXmlString.GetString(nId);		
		if (strValue != Empty_String_Value)
		{
			m_listString.AddString(strId);
		}
	}

	m_comboId.SetCurSel(0);
}

void QuestStringEdit::OnBnClickedButtonAddString()
{
	// TODO: Add your control notification handler code here
	CString strId = "";
	m_comboId.GetWindowText(strId);
	int nId = atoi(strId.GetBuffer());
	//XmlString::SetString(nId);//zhuxincong
	CString strValue = "";
	m_editString.GetWindowText(strValue);
	if (strValue.IsEmpty())
	{
		return;
	}

	bool bExist = false;
	{
		bExist = true;
		if(MessageBox("此Id内容已经存在，需要修改吗？", "提示", MB_YESNO | MB_ICONWARNING) == IDNO)
		{			
			return;
		}
	}
	theXmlString.SetString(nId, string(strValue));

	strValue = RemoveChangeLineChar(strValue.GetBuffer());

	theXmlString.AddString(nId, strValue.GetString());
	if (!bExist)
	{
		m_listString.AddString(strId);
	}
	SQuest*pQuest = theQuestManager.GetQuest(theEditor->curr_show_quest_id);
	if (pQuest)
	{
		theEditor->ShowQuestInformation(*pQuest);
	}
}


void QuestStringEdit::SaveStringEdit()
{
	if (m_nQuestId < 0)
	{
		return;
	}

	vector<int> vecStringId;
	vecStringId.clear();

	CString strId = "";

	strId.Format("%d%02d", m_nQuestId, 1);
	int nId = atoi(strId.GetBuffer());
	for (int i = 0; i < StringId_Count; ++i)
	{
		vecStringId.push_back(nId + i);
	}

	theXmlString.SaveStringFile(m_strFilePath.GetBuffer(), vecStringId, false);
}


void QuestStringEdit::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default
	if (nID == SC_CLOSE)
	{
		SaveStringEdit();
		this->ShowWindow(SW_HIDE);

		return;
	}
	
	CDialog::OnSysCommand(nID, lParam);
}

void QuestStringEdit::OnLbnDblclkListQuest()
{
	// TODO: Add your control notification handler code here

	int nIndex = m_listString.GetCurSel();
	if (nIndex < 0)
	{
		return;
	}

	CString strId = "";
	m_listString.GetText(nIndex, strId);

	m_comboId.SetCurSel(m_comboId.FindString(0, strId));

	CString strText = theXmlString.GetString(atoi(strId.GetBuffer()));
	strText = RemoveChangeLineChar(strText.GetBuffer());

	m_editString.SetWindowText(strText);
}


void QuestStringEdit::OnBnClickedButtonRemove()
{
	// TODO: Add your control notification handler code here
	int nIndex = m_listString.GetCurSel();
	if (nIndex < 0)
	{
		return;
	}

	CString strId = "";
	m_listString.GetText(nIndex, strId);
	if (strId.IsEmpty())
	{
		return;
	}

	int nId = atoi(strId.GetBuffer());

	theXmlString.DeleteString(nId);
	m_listString.DeleteString(nIndex);
}

void QuestStringEdit::OnCbnSelchangeComboId()
{
	// TODO: Add your control notification handler code here

	CString strId = "";
	m_comboId.GetWindowText(strId);

	CString strText = theXmlString.GetString(atoi(strId.GetBuffer()));
	strText = RemoveChangeLineChar(strText.GetBuffer());

	m_editString.SetWindowText(strText);
}

const char* QuestStringEdit::RemoveChangeLineChar(const char *szText)
{
	if (szText == NULL)
	{
		return "";
	}

	static string strValue = "";
	strValue.clear();
	
	int i = 0;
	int j = 0;
	while (szText[i] != 0)
	{
		if (szText[i] != '\r' && szText[i] != '\n')
		{
			strValue.push_back(szText[i]);
		}
		++i;
	}

	return strValue.c_str();
}