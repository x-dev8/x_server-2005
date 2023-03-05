// DropItemDialog.cpp : implementation file
//

#include "stdafx.h"
#include "QuestEditor.h"
#include "DropItemDialog.h"
#include "QuestEditorView.h"

// DropItemDialog dialog

#define Timer_Id 0x226

IMPLEMENT_DYNAMIC(DropItemDialog, CDialog)

DropItemDialog::DropItemDialog(CWnd* pParent /*=NULL*/)
	: CDialog(DropItemDialog::IDD, pParent)
{

}

DropItemDialog::~DropItemDialog()
{
}

void DropItemDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT9, m_editMonsterId);
	DDX_Control(pDX, IDC_COMBO1, m_comboMonsterName);
	DDX_Control(pDX, IDC_EDIT4, m_editItemRate);
}


BEGIN_MESSAGE_MAP(DropItemDialog, CDialog)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT4, &DropItemDialog::OnEnChangeEditRate)
	ON_BN_CLICKED(IDOK, &DropItemDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// DropItemDialog message handlers
BOOL DropItemDialog::PreTranslateMessage(MSG *pMsg)
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

void DropItemDialog::InitInformation()
{

	//CString strName = "";
	//m_comboMonsterName.GetWindowText(strName);

	m_comboMonsterName.ResetContent();

	int nCount = GettheItemDetail().GetItemCount();

	for(int i = 0; i < nCount; ++i)
	{
		CItemDetail::SMonster *pMonster = GettheItemDetail().GetMonster(i);
		if (pMonster != NULL)
		{
			m_comboMonsterName.AddString(pMonster->GetName());
		}
	}

	//m_comboItemName.SetWindowText(strName);
}

void DropItemDialog::UpdateInformation()
{
	CString strName = "";
	if (theEditor->m_xMonsterDrop.nMonsterId != -1)
	{
		theEditor->SetEditText(m_editMonsterId, "%d", theEditor->m_xMonsterDrop.nMonsterId);

		CItemDetail::SMonster *pMonster = GettheItemDetail().GetMonsterById(theEditor->m_xMonsterDrop.nMonsterId);
		if (pMonster != NULL)
		{
			strName = pMonster->GetName();
		}		
	}	
	else
	{
		m_editMonsterId.SetWindowText("");
	}
	m_comboMonsterName.SetWindowText(strName);	

	theEditor->SetEditText(m_editItemRate, "%d", theEditor->m_xMonsterDrop.nItemRate);


	SetTimer(Timer_Id, 100, NULL);
}


void DropItemDialog::FindMonsterIdByName()
{
	CString strName = "";
	m_comboMonsterName.GetWindowText(strName);

	CItemDetail::SMonster *pMonster = GettheItemDetail().GetMonsterByName(strName);
	if (pMonster != NULL)
	{
		theEditor->SetEditText(m_editMonsterId, "%d", pMonster->stMonsterId);
	}
	else
	{
		m_editMonsterId.SetWindowText("");
	}
}

void DropItemDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	if (nIDEvent == Timer_Id)
	{
		FindMonsterIdByName();
	}


	CDialog::OnTimer(nIDEvent);
}

void DropItemDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	int nMonsterId = theEditor->GetEditInt(m_editMonsterId, -1);
	if (nMonsterId <= 0)
	{
		return;
	}

	DropTaskItem::STask xTask;
	xTask.stItem.nItemId = theEditor->m_xMonsterDrop.nItemId;
	xTask.nMaxItemCount = theEditor->m_xMonsterDrop.nItemCount;
	xTask.stItem.nProbability = theEditor->GetEditInt(m_editItemRate, 0);

	xTask.nTaskId = theEditor->m_xMonsterDrop.nQuestId;

  	//Ìí¼Ó
	theEditor->m_xDropTaskItem.AddQuest(nMonsterId, xTask, false);

	KillTimer(Timer_Id);

	OnOK();
}


void DropItemDialog::OnEnChangeEditRate()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	int nRate = theEditor->GetEditInt(m_editItemRate, -1);
	if (nRate < 0)
	{
		m_editItemRate.SetWindowText("0");
	}
	else if (nRate > 10000)
	{
		m_editItemRate.SetWindowText("10000");
	}
}