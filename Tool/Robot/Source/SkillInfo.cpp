// SkillInfo.cpp : implementation file
//

#include "stdafx.h"
#include "SkillInfo.h"
#include "ItemDetail.h"

// SkillInfo dialog

IMPLEMENT_DYNAMIC(SkillInfo, CDialog)

SkillInfo::SkillInfo(CWnd* pParent /*=NULL*/)
	: CDialog(SkillInfo::IDD, pParent)
{

}

SkillInfo::~SkillInfo()
{
}

void SkillInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listProfession);
	DDX_Control(pDX, IDC_LIST2, m_listNormal);
	DDX_Control(pDX, IDC_LIST4, m_listProduce);
	DDX_Control(pDX, IDC_EDIT1, m_editSkillExp);
}


BEGIN_MESSAGE_MAP(SkillInfo, CDialog)
END_MESSAGE_MAP()


// SkillInfo message handlers
BOOL SkillInfo::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void SkillInfo::InitInformation()
{
	
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	int nWidth = 0;
	int iIndex = 0;	
	/////////////////////////////////////////////////////////////////////

	static CListCtrl* s_pList[] = {&m_listProfession, &m_listNormal, &m_listProduce,};
	static const int nCount = sizeof(s_pList) / sizeof(CListCtrl*);

	for (int i = 0; i < nCount; ++i)
	{
		RECT rect;
		s_pList[i]->GetClientRect(&rect);
		nWidth = rect.right - rect.left;

		s_pList[i]->SetExtendedStyle(dwStyle);
		s_pList[i]->InsertColumn(iIndex++, _T("   技能"), 0, (40 * nWidth / 100));
		s_pList[i]->InsertColumn(iIndex++, _T("   等级"), 0, (20 * nWidth / 100));
		s_pList[i]->InsertColumn(iIndex++, _T("   经验"), 0, (40 * nWidth / 100));
	}	
	//////////////////////////////////////////////////////////////////////////////
}

void SkillInfo::UpdateInformation(BaseRobot *pBot)
{
	if (pBot == NULL || pBot->GetBotState() != State_Play)
	{
		m_listProfession.DeleteAllItems();
		m_listNormal.DeleteAllItems();
		m_listProduce.DeleteAllItems();

		m_editSkillExp.SetWindowText("0");
	}
	else	
	{	
		//可用技能点数
		//theApp.SetText(m_editSkillExp, "%d", pBot->m_CharInfo.baseinfo.liveinfo.stSkillPoint);
	
		static int nCount = 0;
		
		//先简单处理
		for (int i = 0; i < More_iMaxSkillKnown; ++i)
		{
			if (!pBot->m_pSkillBag[i].bAvailable)
			{
				break;
			}

			if (i >= nCount)
			{
				CItemDetail::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(pBot->m_pSkillBag[i].ustSkillID, pBot->m_pSkillBag[i].stSkillLevel);
				if (pSkill != NULL)
				{							
					m_listProfession.InsertItem(i, pSkill->GetSkillName());							
				}
				else
				{
					m_listProfession.InsertItem(i, "未知技能");
				}
				++nCount;
			}				
			theApp.SetListItemText(m_listProfession, i, 1, "%d", pBot->m_pSkillBag[i].stSkillLevel);
			theApp.SetListItemText(m_listProfession, i, 2, "%d", pBot->m_pSkillBag[i].dwCurSkillExp);				
		}		
	}
}