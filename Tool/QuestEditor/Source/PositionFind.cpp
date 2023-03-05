// PositionFind.cpp : implementation file
//

#include "stdafx.h"
#include "QuestEditor.h"
#include "PositionFind.h"

#include "QuestEditorView.h"

// PositionFind dialog

IMPLEMENT_DYNAMIC(PositionFind, CDialog)

PositionFind::PositionFind(CWnd* pParent /*=NULL*/)
	: CDialog(PositionFind::IDD, pParent)
	, m_RadioType(0)
{
	m_nType = Enum_Position;
}

PositionFind::~PositionFind()
{
}

void PositionFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listPosition);
	DDX_Control(pDX, IDC_EDIT1, m_editName);
	DDX_Radio(pDX, IDC_RADIO1, m_RadioType);
	DDX_Control(pDX, IDC_EDIT2, m_editId);
}


BEGIN_MESSAGE_MAP(PositionFind, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &PositionFind::OnEnChangeEditName)
	ON_LBN_DBLCLK(IDC_LIST1, &PositionFind::OnLbnDblclkListPosition)
	ON_BN_CLICKED(IDC_RADIO1, &PositionFind::OnBnClickedRadioPosition)
	ON_BN_CLICKED(IDC_RADIO2, &PositionFind::OnBnClickedRadioMonster)
	ON_BN_CLICKED(IDC_RADIO3, &PositionFind::OnBnClickedRadioItem)
	ON_LBN_SELCHANGE(IDC_LIST1, &PositionFind::OnLbnSelchangeListPosition)
END_MESSAGE_MAP()


// PositionFind message handlers


BOOL PositionFind::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitInformation();

	return TRUE;
}


BOOL PositionFind::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			{
				HWND hWnd = GetFocus()->m_hWnd;
				if (hWnd == m_editName.m_hWnd)
				{
					m_listPosition.SetFocus(); //设置list焦点
				}
				else if (hWnd = m_listPosition.m_hWnd)
				{
					OnLbnDblclkListPosition(); //直接选中
				}
			}
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void PositionFind::InitInformation()
{
	m_listPosition.ResetContent();

    m_vecFind.clear();

	vector<SetInfo>::iterator iter = theEditor->m_xSetInfo[m_nType].begin();
	vector<SetInfo>::iterator end = theEditor->m_xSetInfo[m_nType].end();

	for ( ; iter != end; ++iter)
	{
		m_listPosition.AddString(iter->strName.c_str());

        FindInfo xFindInfo;
        xFindInfo.id = iter->nValue;
        xFindInfo.name = iter->strName;

        m_vecFind.push_back(xFindInfo);
	}

	m_editId.SetWindowText("");
}

void PositionFind::OnEnChangeEditName()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString strName = "";
	m_editName.GetWindowText(strName);

	m_listPosition.ResetContent();
	m_vecFind.clear();

	vector<SetInfo>::iterator iter = theEditor->m_xSetInfo[m_nType].begin();
	vector<SetInfo>::iterator end = theEditor->m_xSetInfo[m_nType].end();

	if (strName.IsEmpty())
	{
		for ( ; iter != end; ++iter)
		{
			m_listPosition.AddString(iter->strName.c_str());

            FindInfo xFindInfo;
            xFindInfo.id = iter->nValue;
            xFindInfo.name = iter->strName;

            m_vecFind.push_back(xFindInfo);
		}
	}
	else
	{
		for ( ; iter != end; ++iter)
		{
			if (iter->strName.find(strName) != string::npos)
			{
				m_listPosition.AddString(iter->strName.c_str());

				FindInfo xFindInfo;
				xFindInfo.id = iter->nValue;
				xFindInfo.name = iter->strName;

				m_vecFind.push_back(xFindInfo);
			}
		}
	}
}



void PositionFind::OnLbnDblclkListPosition()
{
	// TODO: Add your control notification handler code here

	int nIndex = m_listPosition.GetCurSel();
	if (nIndex >= 0 && nIndex < m_vecFind.size())
	{
		int nId = m_vecFind[nIndex].id;
		CString strText = m_vecFind[nIndex].name.c_str();

		if (m_nType == Enum_Position)
		{            
			if (nId >= 0)
			{
				theEditor->SetListItemBGroundColor(theEditor->m_listProperty, theEditor->m_nItem, 1, Default_Grund_Color);
				theEditor->SetListItemText(theEditor->m_listProperty, theEditor->m_nItem, 1, "%d", nId);
				theEditor->m_listProperty.SetItemText(theEditor->m_nItem, 2, strText);
			}
			else
			{
				theEditor->SetListItemBGroundColor(theEditor->m_listProperty, theEditor->m_nItem, 1, Red_Ground_Color);
				theEditor->m_listProperty.SetItemText(theEditor->m_nItem, 1, "");
				theEditor->m_listProperty.SetItemText(theEditor->m_nItem, 2, Default_Select);
			}
		}
		else if (m_nType == Enum_Monster || m_nType == Enum_Item)
		{
			if (theEditor->m_pxListCtrl != NULL && theEditor->m_nItem != -1)
			{
				if (nId >= 0)
				{
					theEditor->SetListItemText(*(theEditor->m_pxListCtrl), theEditor->m_nItem, 1, "%d", nId);
					theEditor->m_pxListCtrl->SetItemText(theEditor->m_nItem, 2, strText);
				}
				else
				{
					theEditor->m_pxListCtrl->SetItemText(theEditor->m_nItem, 1, "");
					theEditor->m_pxListCtrl->SetItemText(theEditor->m_nItem, 2, "");
				}
			}
		}		

		OnOK();
	}
}

void PositionFind::OnBnClickedRadioPosition()
{
	// TODO: Add your control notification handler code here
	m_nType = Enum_Position;
	InitInformation();
}

void PositionFind::OnBnClickedRadioMonster()
{
	// TODO: Add your control notification handler code here
	m_nType = Enum_Monster; 
	InitInformation();
}

void PositionFind::OnBnClickedRadioItem()
{
	// TODO: Add your control notification handler code here
	m_nType = Enum_Item;
	InitInformation();
}

void PositionFind::OnLbnSelchangeListPosition()
{
	// TODO: Add your control notification handler code here

	int nIndex = m_listPosition.GetCurSel();
	if (nIndex >= 0 && nIndex < m_vecFind.size())
	{
		

		int nId = m_vecFind[nIndex].id;

		if (nId >= 0)
		{
			theEditor->SetEditText(m_editId, "%d", nId);
		}
		else
		{
			m_editId.SetWindowText("");
		}		
	}

}
