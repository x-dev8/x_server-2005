#ifndef __GAMESERVER_SHOPMGR_H__
#define __GAMESERVER_SHOPMGR_H__

#pragma once

#include "GlobalDef.h"

class CShopMgr
{
public:
    struct SShop
    {
        enum EConstDefine
        {
            eShopItemMax = SHOP_ITEM_MAXCOUNT,
        };

        SShop()
        {
            nShopId       = -1;
            dwRefreshRate = 0;
            byType        = 0xff;
            bIsBound      = true;
            nItemCount    = 0;
            nShopNpcId    = -1;
        }

        int       nShopNpcId;
        int       nShopId;       // �̵�ID
        DWORD     dwRefreshRate; // ��Ʒˢ������
        BYTE      byType;        // �չ���Ʒ������
        bool      bIsBound;      // �Ƿ�Ϊ���̵�
        SShopItem stItem[eShopItemMax];
        int       nItemCount;

        SShopItem* GetItemById( int nId );
        void       RefreshCount();
        void       RefreshPrice();
        bool       AddItem( const SShopItem* pItem );
    };

    struct SShopMgr 
    {
        enum EConstDefine
        {
            eMaxShopCount = 256
        };

        SShopMgr(): nShopCount(0)
        {}
        SShop stShop[eMaxShopCount];
        int   nShopCount;
    };

public:
    CShopMgr();
    ~CShopMgr();

    void    Run();
    bool    AddShop( const SShop* shop );
    SShop*  GetShopByIndex( unsigned int nIndex );
    SShop*  GetShopById( int nId );
    bool    LoadData();
    bool    SaveData();

private:
    DWORD    m_dwTime;
    SShopMgr m_stShopData;
};

extern CShopMgr* GetShopMgr();

#endif // __GAMESERVER_SHOPMGR_H__
