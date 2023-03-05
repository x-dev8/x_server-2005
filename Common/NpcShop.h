/********************************************************************
	Filename: 	NpcShop.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __NPC_SHOP_H__
#define __NPC_SHOP_H__

#pragma once

#include "GlobalDef.h"
#include "ItemDetail.h"

class NpcShop
{
public:
    inline static NpcShop& Instance()
    {
        static NpcShop s_xNpcShop;
        return s_xNpcShop;
    }

    uint8 GetShopItemCostType( ItemDefine::SItemCommon* pItem, SShopItem* pShopItem ); // 获得玩家购买道具的花费类型
    int32 GetPlayerSellNpcItemCost( uint16 itemId, uint16 count );                  // 获得玩家卖给NPC道具价格
    int32 GetPlayerItemReclaimCost( SCharItem* pCharItem, uint16 count );           // 获得玩家装备回收价格

protected:
    NpcShop() { }

};

#define theNpcShop NpcShop::Instance()   //实例接口

#endif // __NPC_SHOP_H__
