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

    uint8 GetShopItemCostType( ItemDefine::SItemCommon* pItem, SShopItem* pShopItem ); // �����ҹ�����ߵĻ�������
    int32 GetPlayerSellNpcItemCost( uint16 itemId, uint16 count );                  // ����������NPC���߼۸�
    int32 GetPlayerItemReclaimCost( SCharItem* pCharItem, uint16 count );           // ������װ�����ռ۸�

protected:
    NpcShop() { }

};

#define theNpcShop NpcShop::Instance()   //ʵ���ӿ�

#endif // __NPC_SHOP_H__
