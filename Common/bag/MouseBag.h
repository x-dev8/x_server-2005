#ifndef __COMMON_MOUSEBAG_H__
#define __COMMON_MOUSEBAG_H__

#pragma once

#include "GlobalDef.h"
#include "ItemDetail.h"

class CMouseBag
{
private:
    SMouseItem* m_pdata;

public:
    CMouseBag();
    ~CMouseBag();

    void	Clear();	//清空数据
    void	SetMouseItem(SCharItem *pItem);	//设置鼠标上的道具
    void	SetMouseItem(SMouseItem *pItem);
    void	SetMouseShortCut(int bag_type, int bag_index);
    void	SetMouseShortCut(SShortCut *pShortCut);////设置鼠标上的快捷
    bool	GetMouseItem(SCharItem *pItem);	//取得鼠标上的道具
    bool	GetMouseItem(SMouseItem *pItem);

    bool	GetMouseItemAndClear(SCharItem *pItem);//取得鼠标上的道具,并且清掉鼠标上的道具
    bool	GetMouseBag(SMouseItem *pItem);	//取得鼠标背包
    bool	GetMouseShortCut(SShortCut *pShortCut);//取得鼠标上的快捷
    bool	GetMouseShortCutAndClear(SShortCut *pShortCut);//取得鼠标上的快捷，并且清空鼠标
    bool	IsMouseHaveFactItem();	//判断鼠标是是否有实际上的道具
    bool	IsMouseHaveShortCut();//判断鼠标上是否有道具的索引
    bool	CreateFromData( SMouseItem *pMouseData);
};

#endif // __COMMON_MOUSEBAG_H__
