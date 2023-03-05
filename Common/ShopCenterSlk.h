/********************************************************************
	Filename: 	ShopCenterSlk.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_SHOPCENTERSLK_H__
#define __COMMON_SHOPCENTERSLK_H__

#pragma once

#include "MeRTLibs.h"
#include "GlobalDef.h"



class CShopCenterNode
{
public:
    CShopCenterNode()
    {
        ItemID = InvalidLogicNumber;
        Price = 0;
        VIPPrice = 0;
        Price2 = 0;
        VIPPrice2 = 0;
        Agio = 1.0f;

        ImagePath = "";
        ItemName = "";
        Number = 0;
        Refurbish = -1;

        ShelfType = 0;
        CurNumber = 0;
        bHot = 0;
    }	
public:
    unsigned short	ItemID;
    std::string		Description;
    std::string		ItemName;

    BYTE		ShelfType;	//货价类型
    INT			Price;		//价格
    INT			VIPPrice;	//VIP价格

    INT			Price2;		//以元宝为准的价格
    INT			VIPPrice2;	//VIP价格，以元宝为准
    FLOAT		Agio;		//以%为准
    std::string	ImagePath;	//路径

    INT			CurNumber;	//当前数量
    INT			Number;		//出售数量	-1无限
    DWORD		Refurbish;	//刷新时间 以分钟为单位	
    INT			bHot;
};

class CShopCenterData
{
public:
    enum
    {
        eMax_Shelf = 16,
    };
public:
    DWORD				dwRefurbishTime;
    DWORD				dwSrcTime;
    BOOL				Refurbish( DWORD dwTime );
    bool				LoadFromSlk( char* szFileName );
public:
    INT					GetItemSize()			{ return ItemData.size(); }
    CShopCenterNode*	GetItemNode( INT nIdx );//	{ return &ItemData[nIdx]; }

    INT					GetShelfItemSize(INT nShelf);// { return }
    CShopCenterNode*	GetShelfItemNode( INT nShelf, INT nIdx );

    CShopCenterNode*	GetItemNodeFromID( unsigned short Id );
private:
    std::vector<CShopCenterNode>	ItemData;
    std::vector<CShopCenterNode>	ItemShelfData[eMax_Shelf];
public:
    CShopCenterData();
    ~CShopCenterData();
};

extern CShopCenterData theShopCenterData;

#endif