#include "NpcShop.h"

uint8 NpcShop::GetShopItemCostType( ItemDefine::SItemCommon* pItem, SShopItem* pShopItem )
{
    uint8 nCostType  = pItem->costType;

    if (nCostType == ItemDefine::CT_Money || nCostType == ItemDefine::CT_JiaoZi)
    {
        if (pShopItem->bIsBound)
        { nCostType = ItemDefine::CT_JiaoZi; }
        else
        { nCostType = ItemDefine::CT_Money;  }
    }

    return nCostType;
}

int32 NpcShop::GetPlayerSellNpcItemCost( uint16 itemId, uint16 count )
{
    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( itemId );
    if( pItem == NULL )
    { return 0; }

    if ( count == 0 )
    { return 0; }

    int nCost = 0;
    switch( pItem->ucItemType )
    {
    case ItemDefine::ITEMTYPE_WEAPON:
    case ItemDefine::ITEMTYPE_ARMOUR:
    case ItemDefine::ITEMTYPE_OTHER:
       /* { nCost = pItem->dwCost * fSellDiscountRate * count + 1; }
        break;*/
    case ItemDefine::ITEMTYPE_RESTORE:
    case ItemDefine::ITEMTYPE_MATERIAL:
    case ItemDefine::ITEMTYPE_REEL:
    case ItemDefine::ITEMTYPE_TREASUREBOX:
    case ItemDefine::ITEMTYPE_CHECKUP:
    case ItemDefine::ITEMTYPE_REALAWARD:
    case ItemDefine::ITEMTYPE_GEM:
    case ItemDefine::ITEMTYPE_SPECIAL:
        //{ nCost = 1 * count ; }
		nCost = pItem->dwCost * fSellDiscountRate * count + 1;
        break;
    default:
        { return 0; }
        break;
    }

    return nCost;
}

int32 NpcShop::GetPlayerItemReclaimCost( SCharItem* pCharItem, uint16 count )
{
    if (pCharItem == NULL || count == 0)
    { return -1; }

    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    if( pItem == NULL )
    { return -1; }

    if (pItem->ucItemType != ItemDefine::ITEMTYPE_WEAPON && pItem->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return -1; }

    int nCostReturn = 0;
    switch ( pItem->costType )
    {
    case ItemDefine::CT_Reputation:
    case ItemDefine::CT_Exploit:
    case ItemDefine::CT_Honour:
    case ItemDefine::CT_GuildOffer:
        {
            if (pCharItem->equipdata.quality == ItemDefine::EQL_Purple)
            { nCostReturn = pItem->dwCost * count ; }
            else
            { nCostReturn = pItem->dwCost * count * fReclaimDiscountRate + 1; }

        }
        break;
    case ItemDefine::CT_Item:
        {
            ItemDefine::SItemCommon* pBuyItem = GettheItemDetail().GetItemByID( pItem->costItemID );
            if( pBuyItem == NULL )
            { return -1; }

            if (pCharItem->equipdata.quality == ItemDefine::EQL_Purple)
            { nCostReturn = pBuyItem->dwCost * pItem->dwCost * count; }
            else
            { nCostReturn = pBuyItem->dwCost * pItem->dwCost * count  * fReclaimDiscountRate + 1; }
        }
        break;
    default:
        { return -1; }
        break;
    }

    return nCostReturn;
}
