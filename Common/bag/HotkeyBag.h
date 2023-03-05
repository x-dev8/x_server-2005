#ifndef __COMMON_HOTKEYBAG_H__
#define __COMMON_HOTKEYBAG_H__

#pragma once

#include "GlobalDef.h"

class CHotkeyBag
{
public:
	CHotkeyBag();
	~CHotkeyBag();

	// 初始化
	void CreateFromData( SMouseItem* pHotkeyData, int iBagSize );

	//放置快捷
	bool PushItem( SMouseItem &item, short stIndex=-1 );
	//取出快捷
	bool ClearItem( short stIndex );

	//获取指定快捷的信息
	bool GetHotkey( short stIndex, SMouseItem *pHotkey );

	//设置指定Hotkey的快捷信息
	void SetShortCut( int iHotKeyIndex, int iBagType, int iBagIndex );

	//获取指定索引的状况...判断该位置是有
	bool IsHaveHotkey( short stIndex );
	bool IsHaveFactItem( short stIndex );
	bool CHotkeyBag::IsHaveShortCut( short stIndex );

	//清空指定索引的快捷
	bool ClearHotkey( short stIndex );
	//清空指向指定背包,索引的快捷
	void ClearSpecialHotkey( int bag_type, int index );
	
	bool	GetHotKeyCanClear( short stIndex, SMouseItem *pHotkey );
	//{ add by ^^
	int		PopItem( SCharItem &item,unsigned short &ustCount );
	int		GetItemCount( int iItemID );
	//} add by ^^

private:

	//找一个空的位置
	int  FindNullHotkeyOffSet( );

	//背包的最大数目
	int	 m_iBagSize;
	//快捷的数据指针
	SMouseItem *m_pHotkeyData;
};

#endif // __COMMON_HOTKEYBAG_H__
