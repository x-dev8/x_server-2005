// PackInfo.cpp : implementation file
//

#include "stdafx.h"
#include "PackInfo.h"
#include "ItemDetail.h"


// PackInfo dialog

IMPLEMENT_DYNAMIC(PackInfo, CDialog)

PackInfo::PackInfo(CWnd* pParent /*=NULL*/)
	: CDialog(PackInfo::IDD, pParent)
{
	m_pBot = NULL;
}

PackInfo::~PackInfo()
{
}

void PackInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listEquip);
	DDX_Control(pDX, IDC_LIST2, m_listPack);
	DDX_Control(pDX, IDC_EDIT1, m_editGold);
	DDX_Control(pDX, IDC_EDIT2, m_editSilver);
	DDX_Control(pDX, IDC_EDIT3, m_editCopper);
	DDX_Control(pDX, IDC_EDIT4, m_editMoney);
	DDX_Control(pDX, IDC_EDIT47, m_editWeightMax);
	DDX_Control(pDX, IDC_EDIT5, m_editWeightNow);
}


BEGIN_MESSAGE_MAP(PackInfo, CDialog)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &PackInfo::OnNMRclickListEquip)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &PackInfo::OnNMRclickListPack)
	ON_COMMAND(ID_DEBUS, &PackInfo::OnDebusEquip)
	ON_COMMAND(ID__32788, &PackInfo::OnUseItem)
	ON_COMMAND(ID__32789, &PackInfo::OnMoveItem)
	ON_COMMAND(ID__32790, &PackInfo::OnDeleteItem)
	ON_COMMAND(ID__32791, &PackInfo::OnDebusDress)
END_MESSAGE_MAP()


// PackInfo message handlers
BOOL PackInfo::PreTranslateMessage(MSG *pMsg)
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

void PackInfo::InitInformation()
{
	RECT rect;
	DWORD dwStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	int nWidth = 0;
	int iIndex = 0;
	/////////////////////////////////////////////////////////////////////
	m_listEquip.SetExtendedStyle(dwStyle);
	
	m_listEquip.GetClientRect(&rect);
	nWidth = rect.right - rect.left;

	m_listEquip.InsertColumn(iIndex++, _T("   部位"), 0, (20 * nWidth / 100));
	m_listEquip.InsertColumn(iIndex++, _T("   装备"), 0, (40 * nWidth / 100));
	m_listEquip.InsertColumn(iIndex++, _T("   时装"), 0, (40 * nWidth / 100));
	
	ShowEquipInformation(NULL);

	//////////////////////////////////////////////////////////////////////

	m_listPack.SetExtendedStyle(dwStyle);
	m_listPack.GetClientRect(&rect);
	nWidth = rect.right - rect.left;
	iIndex = 0;

	m_listPack.InsertColumn(iIndex++, _T("   物品名称"), 0, (60 * nWidth / 100));
	m_listPack.InsertColumn(iIndex++, _T("   物品数量"), 0, (40 * nWidth / 100));
	ShowPackInformation(NULL);
}


void PackInfo::UpdateInformation(BaseRobot *pBot)
{
	m_pBot = pBot;

	if (pBot == NULL)
	{
		return;
	}

	if (pBot->GetBotState() == State_Play)
	{
		//显示装备
		ShowEquipInformation(pBot);

		//显示背包
		ShowPackInformation(pBot);

		//金钱
		
		//theApp.SetText(m_editMoney, "%d", pBot->m_CharInfo.baseinfo.liveinfo.dwRMBGold);

		//负重
		//theApp.SetText(m_editWeightNow, "%d", pBot->m_CharInfo.baseinfo.liveinfo.ustWeight);
		//theApp.SetText(m_editWeightMax, "%d", pBot->m_CharInfo.baseinfo.liveinfo.ustWeightCanTake);
	}
	else
	{
		ShowEquipInformation(NULL);
		ShowPackInformation(NULL);

		m_editGold.SetWindowText("0");
		m_editSilver.SetWindowText("0");
		m_editCopper.SetWindowText("0");
		m_editMoney.SetWindowText("0");

		m_editWeightNow.SetWindowText("0");
		m_editWeightMax.SetWindowText("0");
	}
}



void PackInfo::ShowEquipInformation(BaseRobot *pBot)
{
	static char* s_pszEquip[] = 
	{
		"头发", "头盔", "脸", "盔甲", "手套", "鞋子",
		"右手物品", "左手物品", "头饰", "盾", "护肩", "护腿",
		"饰品", "戒指", "手镯", "项链", "腰带", "勋章",
	};

	static const int nCount = sizeof(s_pszEquip) / sizeof(char*);

	static bool s_bInit = false;

	if (pBot == NULL)
	{
		for (int i = 0; i < nCount; ++i)
		{
			if(!s_bInit)
			{
				m_listEquip.InsertItem(i, s_pszEquip[i]);
			}
			
			m_listEquip.SetItemText(i, 1, "");
			m_listEquip.SetItemText(i, 2, "");
		}

		s_bInit = true;
	}
	else
	{		
		for (int i = 0; i < nCount; ++i)
		{	
			CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID( pBot->m_CharInfo.visual.equipitem[i].itembaseinfo.ustItemID );

			if (pItem != NULL)
			{
				m_listEquip.SetItemText(i, 1, pItem->GetItemName());				
			}
			else
			{
				m_listEquip.SetItemText(i, 1, "");
			}

			pItem = GettheItemDetail().GetItemByID( pBot->m_CharInfo.visual.equipitem[i + nCount].itembaseinfo.ustItemID );
			if (pItem != NULL)
			{
				m_listEquip.SetItemText(i, 2, pItem->GetItemName());	
			}
			else
			{
				m_listEquip.SetItemText(i, 2, "");
			}
		}
	}	
}

void PackInfo::ShowPackInformation(BaseRobot *pBot)
{
	if (pBot != NULL)
	{
		for (int i = 0; i < ITEM_BAGMAX; ++i)
		{
			if (pBot->m_pItemBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
			{
				CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID( pBot->m_pItemBag[i].itembaseinfo.ustItemID );

				if (pItem != NULL)
				{
					m_listPack.SetItemText(i, 0, pItem->GetItemName());
					theApp.SetListItemText(m_listPack, i, 1, "%d", pBot->m_pItemBag[i].itembaseinfo.ustItemCount);
				}				
			}
			else
			{
				m_listPack.SetItemText(i, 0, "");
				m_listPack.SetItemText(i, 1, "0");
			}
		}
	}
	else
	{
		static bool s_bInit = false;
		for (int i = 0; i < ITEM_BAGMAX; ++i)
		{
			if (!s_bInit)
			{
				m_listPack.InsertItem(i, "");
			}
			else
			{
				m_listPack.SetItemText(i, 0, "");
			}

			m_listPack.SetItemText(i, 1, "");
		}

		s_bInit = true;
	}
}

void PackInfo::OnNMRclickListEquip(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if (GetListSelectItemIndex(m_listEquip) != -1)
	{
		CPoint pt;
		GetCursorPos(&pt);

		CMenu menu;
		menu.LoadMenu(IDR_MENU_EQUIP);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
	}
}

void PackInfo::OnNMRclickListPack(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if (GetListSelectItemIndex(m_listPack) != -1)
	{
		CPoint pt;
		GetCursorPos(&pt);

		CMenu menu;
		menu.LoadMenu(IDR_MENU_PACK);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
	}
}

//卸下装备
void PackInfo::OnDebusEquip()
{
	// TODO: Add your command handler code here
	
	if (m_pBot == NULL || m_pBot->GetBotState() != State_Play)
	{
		return;
	}

	int nIndex = GetListSelectItemIndex(m_listEquip);
	if (nIndex != -1)
	{
		CString strName = m_listEquip.GetItemText(nIndex, 1);
		if (strName.IsEmpty())
		{
			//如果没有装备
			return;
		}

		MsgUnEquip xMsg;
		xMsg.ustWhere = nIndex;

		//背包不要满了
		int nPackIndex = FindEmptyPackItemIndex(m_pBot->m_pItemBag);
		if (nPackIndex != -1)
		{
			xMsg.stPackIndex = nPackIndex;
			m_pBot->SendMsg(&xMsg);	
			
			//m_pBot->m_pItemBag[nPackIndex].itembaseinfo.ustItemID = m_pBot->m_CharInfo.visual.equipitem[nIndex].itembaseinfo.ustItemID;
			//m_pBot->m_pItemBag[nPackIndex].itembaseinfo.ustItemCount = 1;
			//m_pBot->m_pItemBag[nPackIndex].itembaseinfo.stPacketIdx = nPackIndex;

			memcpy(&m_pBot->m_pItemBag[nPackIndex], &m_pBot->m_CharInfo.visual.equipitem[nIndex], sizeof(SCharItem));
			m_pBot->m_pItemBag[nPackIndex].itembaseinfo.stPacketIdx = nPackIndex;

			m_pBot->m_CharInfo.visual.equipitem[nIndex].itembaseinfo.ustItemID = ErrorUnsignedShortID;			
		}
	}
}

//使用道具
void PackInfo::OnUseItem()
{
	// TODO: Add your command handler code here
	if (m_pBot == NULL || m_pBot->GetBotState() != State_Play)
	{
		return;
	}
	
	int nIndex = GetListSelectItemIndex(m_listPack);
	if (nIndex == -1 || nIndex >= ITEM_BAGMAX)
	{
		return;
	}

	CString strItem = m_listPack.GetItemText(nIndex, 0);
	if (strItem.IsEmpty())
	{
		return;
	}

	CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID( m_pBot->m_pItemBag[nIndex].itembaseinfo.ustItemID );
	if (pItem == NULL)
	{
		return;
	}

	//装备道具
	if (pItem->ucItemType == CItemDetail::ITEMTYPE_WEAPON || pItem->ucItemType == CItemDetail::ITEMTYPE_ARMOUR)
	{
		MsgEquip xMsg;
		xMsg.ustPackIndex = nIndex;

		m_pBot->SendMsg(&xMsg);
	}
	else if (pItem->ucItemType == CItemDetail::ITEMTYPE_RESTORE)
	{
		//使用道具
		MsgUseGoods xMsg;
		xMsg.ustItemIndex = nIndex;
		xMsg.stItemCount = 1;
		xMsg.stDstChar = m_pBot->m_shPlayerId;
		xMsg.stSrcChar = m_pBot->m_shPlayerId;
		xMsg.nRemainValue = 0;

		m_pBot->SendMsg(&xMsg);
	}

}

//移动道具
void PackInfo::OnMoveItem()
{
	// TODO: Add your command handler code here

	if (m_pBot == NULL || m_pBot->GetBotState() != State_Play)
	{
		return;
	}

	int nIndex = GetListSelectItemIndex(m_listPack);
	if (nIndex == -1 || nIndex >= ITEM_BAGMAX)
	{
		return;
	}

	int nPackIndex = FindEmptyPackItemIndex(m_pBot->m_pItemBag);
	if (nPackIndex == -1)
	{
		nPackIndex = 1;
	}

	MsgMoveGoods xMsg;

	xMsg.ustSrcIndex = nIndex;
	xMsg.ustDstIndex = nPackIndex;
	xMsg.ustCount = m_pBot->m_pItemBag[nIndex].itembaseinfo.ustItemCount;

	m_pBot->SendMsg(&xMsg);

	//显示更新
	SCharItem xCharItem;

	memcpy(&xCharItem, &m_pBot->m_pItemBag[nPackIndex], sizeof(SCharItem));
	memcpy(&m_pBot->m_pItemBag[nPackIndex], &m_pBot->m_pItemBag[nIndex], sizeof(SCharItem));
	m_pBot->m_pItemBag[nPackIndex].itembaseinfo.stPacketIdx = nPackIndex;

	memcpy(&m_pBot->m_pItemBag[nIndex], &xCharItem, sizeof(SCharItem));
	m_pBot->m_pItemBag[nIndex].itembaseinfo.stPacketIdx = nIndex;
}

//删除道具
void PackInfo::OnDeleteItem()
{
	// TODO: Add your command handler code here
	if (m_pBot == NULL || m_pBot->GetBotState() != State_Play)
	{
		return;
	}

	int nIndex = GetListSelectItemIndex(m_listPack);
	if (nIndex == -1 || nIndex >= ITEM_BAGMAX)
	{
		return;
	}

	CString strItem = m_listPack.GetItemText(nIndex, 0);
	if (strItem.IsEmpty())
	{
		return;
	}

	MsgMoveGoods xMsg;
	xMsg.ustSrcIndex = nIndex;
	xMsg.ustDstIndex = ITEM_DISTORY;
	xMsg.ustCount = m_pBot->m_pItemBag[nIndex].itembaseinfo.ustItemCount;

	m_pBot->SendMsg(&xMsg);

	m_pBot->m_pItemBag[nIndex].itembaseinfo.ustItemID = ErrorUnsignedShortID;
	m_pBot->m_pItemBag[nIndex].itembaseinfo.ustItemCount = 0;
}

//卸下时装
void PackInfo::OnDebusDress()
{
	// TODO: Add your command handler code here
}

int PackInfo::GetListSelectItemIndex(CListCtrl &xList)
{
	POSITION pos = xList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		return xList.GetNextSelectedItem(pos);
	}

	return -1;
}


int PackInfo::FindEmptyPackItemIndex(SCharItem *pItemBag)
{
	if (pItemBag == NULL)
	{
		return -1;
	}

	for (int i = 0; i < ITEM_BAGMAX; ++i)
	{
		if (pItemBag[i].itembaseinfo.ustItemID == ErrorUnsignedShortID)
		{
			return i;
		}
	}

	return -1;
}