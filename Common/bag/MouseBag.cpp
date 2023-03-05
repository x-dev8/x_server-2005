#include "MouseBag.h"

CMouseBag::CMouseBag()
{
	m_pdata = NULL;
}
CMouseBag::~CMouseBag()
{
}
//
//清空数据
void	CMouseBag::Clear()
{
//	m_pdata->type = SMouseItem::TypeNull;
	m_pdata->ItemData.itembaseinfo.ustItemID = ErrorUnsignedShortID;
}
void	CMouseBag::SetMouseItem(SMouseItem *pItem)
{
	if (NULL == pItem)
		return;
	//
	memcpy(m_pdata, pItem, sizeof(*m_pdata));
}
//设置鼠标上的道具
void	CMouseBag::SetMouseItem(SCharItem *pItem)
{
	if (NULL == pItem)
		return;
	//
	memcpy(&(m_pdata->ItemData), pItem, sizeof(m_pdata->ItemData));
	//if (ErrorUnsignedShortID == m_pdata->ItemData.ustItemID)
	//	m_pdata->type = SMouseItem::TypeNull;
	//else
	//	m_pdata->type = SMouseItem::TypeFactItem;
}
//取得鼠标上的道具
bool	CMouseBag::GetMouseItem(SMouseItem *pItem)
{
	if (NULL == pItem)
		return false;
	//
	//
	memcpy(pItem, m_pdata, sizeof(*m_pdata));
	//
	return true;
}
bool	CMouseBag::GetMouseItem(SCharItem *pItem)
{
	if (NULL == pItem)
		return false;
	//
	//if (SMouseItem::TypeFactItem != m_pdata->type)
	//{
	//	pItem->ustItemID = ErrorUnsignedShortID;
	//	return false;
	//}
	//
	memcpy(pItem, &(m_pdata->ItemData), sizeof(SCharItem));
	//
	return true;
}
//取得鼠标上的道具,并且清掉鼠标上的道具
bool	CMouseBag::GetMouseItemAndClear(SCharItem *pItem)
{
	if (NULL == pItem)
		return false;
	//
	//if (SMouseItem::TypeFactItem != m_pdata->type)
	//{
	//	pItem->ustItemID = ErrorUnsignedShortID;
	//	return false;
	//}
	//
	memcpy(pItem, &(m_pdata->ItemData), sizeof(SCharItem));
	//
	Clear();
	//
	return true;
}
//取得鼠标上的道具索引
bool CMouseBag::GetMouseShortCut(SShortCut *pShortCut)
{
	//if (SMouseItem::TypeNotItem != m_pdata->type)
	//	return false;
	//
	memcpy(pShortCut, &(m_pdata->ShortCut), sizeof(*pShortCut));
	return true;
}
bool CMouseBag::GetMouseShortCutAndClear(SShortCut *pShortCut)
{
	//if (SMouseItem::TypeNotItem != m_pdata->type)
	//	return false;
	//
	memcpy(pShortCut, &(m_pdata->ShortCut), sizeof(*pShortCut));
//	m_pdata->type = SMouseItem::TypeNull;
	return true;
}
//
void	CMouseBag::SetMouseShortCut(int bag_type, int bag_index)
{
	SShortCut ShortCut;
	//
	ShortCut.BagIndex = bag_index;
	ShortCut.BagType = bag_type;
	//
	SetMouseShortCut(&ShortCut);
}
void	CMouseBag::SetMouseShortCut(SShortCut *pShortCut)
{
//	m_pdata->type = SMouseItem::TypeNotItem;
	memcpy(&(m_pdata->ShortCut), pShortCut, sizeof(*pShortCut));
}
//判断鼠标是是否有实际上的道具
bool	CMouseBag::IsMouseHaveFactItem()
{
	//if (SMouseItem::TypeFactItem == m_pdata->type)
	//	return true;
	return false;
}
//判断鼠标上是否有道具的索引
bool	CMouseBag::IsMouseHaveShortCut()
{
	//if (SMouseItem::TypeNotItem == m_pdata->type)
	//	return true;
	return false;
}
bool	CMouseBag::CreateFromData( SMouseItem *pMouseData)
{
	m_pdata = pMouseData;
	return true;
}
bool	CMouseBag::GetMouseBag(SMouseItem *pItem)	//取得鼠标背包
{
	memcpy(pItem, m_pdata, sizeof(*m_pdata));
	return true;
}
//-------------------------------------------------------------------------
//	End.
//-------------------------------------------------------------------------
