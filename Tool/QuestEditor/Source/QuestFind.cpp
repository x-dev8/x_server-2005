// QuestFind.cpp : implementation file
//
#include "stdafx.h"
#include "QuestEditor.h"
#include "QuestFind.h"

#include "QuestEditorView.h"

// QuestFind dialog

IMPLEMENT_DYNAMIC(QuestFind, CDialog)

QuestFind::QuestFind(CWnd* pParent /*=NULL*/)
	: CDialog(QuestFind::IDD, pParent)
{

}

QuestFind::~QuestFind()
{
}

void QuestFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboType);
	DDX_Control(pDX, IDC_EDIT1, m_editFind);
	DDX_Control(pDX, IDC_EDIT3, m_editReplace);
	DDX_Control(pDX, IDC_CHECK1, m_checkMatch);
}


BEGIN_MESSAGE_MAP(QuestFind, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &QuestFind::OnBnClickedButtonFind)
END_MESSAGE_MAP()


// QuestFind message handlers
BOOL QuestFind::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			OnBnClickedButtonFind();
			return TRUE;

		case VK_ESCAPE:
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void QuestFind::InitInformation()
{
	m_comboType.ResetContent();

	for(int i = 0; i < Enum_QuestMax; ++i)
	{
		m_comboType.AddString(s_pFindType[i]);
	}

	m_comboType.SetCurSel(0);
}


void QuestFind::OnBnClickedButtonFind()
{
	// TODO: Add your control notification handler code here

	CString strValue = "";
	m_editFind.GetWindowText(strValue);

	if (strValue.IsEmpty())
	{
		return;
	}

	FindInfo xFindInfo;

	xFindInfo.nFindMatch = m_checkMatch.GetCheck();

	int nFirstId = theEditor->FindQuest(strValue, m_comboType.GetCurSel(), &xFindInfo);
	
	if (nFirstId != -1)
	{
		theEditor->ShowFindQuest(nFirstId);
		this->ShowWindow(SW_HIDE);
	}	
}
