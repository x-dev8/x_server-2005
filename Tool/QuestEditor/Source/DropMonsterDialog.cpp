// DorpItem.cpp : implementation file
//

#include "stdafx.h"
#include "QuestEditor.h"
#include "DropMonsterDialog.h"
#include "QuestEditorView.h"

// DorpItem dialog

#define Timer_Id 0x227

IMPLEMENT_DYNAMIC(DropMonsterDialog, CDialog)

DropMonsterDialog::DropMonsterDialog(CWnd* pParent /*=NULL*/)
	: CDialog(DropMonsterDialog::IDD, pParent)
{
	
}

DropMonsterDialog::~DropMonsterDialog()
{
}

void DropMonsterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT11, m_editVarId);
	DDX_Control(pDX, IDC_EDIT9, m_editItemId);
	DDX_Control(pDX, IDC_COMBO1, m_comboItemName);
	DDX_Control(pDX, IDC_EDIT7, m_editItemCount);
	DDX_Control(pDX, IDC_EDIT4, m_editItemRate);
}


BEGIN_MESSAGE_MAP(DropMonsterDialog, CDialog)
	ON_BN_CLICKED(IDOK, &DropMonsterDialog::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_EDIT11, &DropMonsterDialog::OnEnKillfocusEditVarId)
	ON_EN_KILLFOCUS(IDC_EDIT9, &DropMonsterDialog::OnEnKillfocusEditItemId)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT4, &DropMonsterDialog::OnEnChangeEditRate)
END_MESSAGE_MAP()


// DorpItem message handlers
BOOL DropMonsterDialog::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:	
			if (GetFocus()->m_hWnd == m_editItemId.m_hWnd)
			{
				OnEnKillfocusEditItemId();
			}	
			
			return TRUE;

		case VK_ESCAPE:
			return TRUE;

		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void DropMonsterDialog::InitInformation()
{
	m_comboItemName.ResetContent();

	int nCount = GettheItemDetail().GetItemCount();

	for(int i = 0; i < nCount; ++i)
	{
		CItemDetail::SItemCommon *pItem = GettheItemDetail().GetItemByID(i);
		if (pItem != NULL)
		{
			m_comboItemName.AddString(pItem->GetItemName());
		}
	}
}

void DropMonsterDialog::UpdateInformation()
{
	if (theEditor->m_xMonsterDrop.nVarId >= 0)
	{
		theEditor->SetEditText(m_editVarId, "%d", theEditor->m_xMonsterDrop.nVarId);
	}
	else
	{
		m_editVarId.SetWindowText("");
	}

	CString strName = "";
	if (theEditor->m_xMonsterDrop.nItemId != -1)
	{
		theEditor->SetEditText(m_editItemId, "%d", theEditor->m_xMonsterDrop.nItemId);

		CItemDetail::SItemCommon *pItem = GettheItemDetail().GetItemByID(theEditor->m_xMonsterDrop.nItemId);
		if (pItem != NULL)
		{
			strName = pItem->GetItemName();
		}		
	}	
	else
	{
		m_editItemId.SetWindowText("");
	}
	m_comboItemName.SetWindowText(strName);	

	theEditor->SetEditText(m_editItemCount, "%d", theEditor->m_xMonsterDrop.nItemCount);
	theEditor->SetEditText(m_editItemRate, "%d", theEditor->m_xMonsterDrop.nItemRate);


	SetTimer(Timer_Id, 100, NULL);
}

void DropMonsterDialog::FindItemIdByName()
{
	CString strName = "";
	m_comboItemName.GetWindowText(strName);

	CItemDetail::SItemCommon *pItem = GettheItemDetail().GetItemByName(strName);
	if (pItem != NULL)
	{
		theEditor->SetEditText(m_editItemId, "%d", pItem->ustItemID);
	}
	else
	{
		m_editItemId.SetWindowText("");
	}
}

void DropMonsterDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	DropTaskItem::STask xTask;
	int nVarId = theEditor->GetEditInt(m_editVarId, -1);
	if (nVarId < 0)
	{
		AfxMessageBox("请输入正确的变量ID!");
		return;
	}

	
	xTask.nVarId = nVarId;
	xTask.stItem.nItemId = theEditor->GetEditInt(m_editItemId, -1);
	xTask.nMaxItemCount = theEditor->GetEditInt(m_editItemCount, 0);
	xTask.stItem.nProbability = theEditor->GetEditInt(m_editItemRate, 0);

	xTask.nTaskId = theEditor->m_xMonsterDrop.nQuestId;
	xTask.nMaxVar = theEditor->m_xMonsterDrop.nMonsterCount;

	if (xTask.nMaxVar == 0 && xTask.nMaxItemCount == 0)
	{
		AfxMessageBox("请设置怪物或者物品数量！");
		return;
	}

	//添加
	if (!theEditor->m_xDropTaskItem.AddQuest(theEditor->m_xMonsterDrop.nMonsterId, xTask, false))
    {
        CString strError = "";
        strError.Format(_T("添加怪物[%u]掉落关联失败！"), theEditor->m_xMonsterDrop.nMonsterId);
        AfxMessageBox(strError);
    }
	KillTimer(Timer_Id);

	OnOK();
}

void DropMonsterDialog::OnEnKillfocusEditVarId()
{
	// TODO: Add your control notification handler code here

	int nVarId = theEditor->GetEditInt(m_editVarId, -1);
	if (nVarId < 0 || ( nVarId >= 3000 && nVarId < 13000 ))
	{
		AfxMessageBox("变量ID不能在[3000,13000)范围内！");
		m_editVarId.SetWindowText("");
		return;
	}

	DropTaskItem::STask xTask;
	int nMonster = theEditor->m_xDropTaskItem.CheckVarId(nVarId, xTask);
	if ( nMonster != -1)
	{
		if (xTask.nTaskId != -1 && nMonster != theEditor->m_xMonsterDrop.nMonsterId)
		{
			AfxMessageBox("该变量ID已经存在, 请重新输入！");
			m_editVarId.SetWindowText("");
		}
	}
}

void DropMonsterDialog::OnEnKillfocusEditItemId()
{
	// TODO: Add your control notification handler code here
	m_editItemId.EnableWindow(FALSE);
	
	int nItemId = theEditor->GetEditInt(m_editItemId, -1);

	CItemDetail::SItemCommon *pItem = GettheItemDetail().GetItemByID(nItemId);
	if (pItem != NULL)
	{
		m_comboItemName.SetWindowText(pItem->GetItemName());
	}
	else
	{
		m_comboItemName.SetWindowText("");
	}
}

void DropMonsterDialog::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == Timer_Id)
	{
		FindItemIdByName();
	}

	CDialog::OnTimer(nIDEvent);
}

void DropMonsterDialog::OnEnChangeEditRate()
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
