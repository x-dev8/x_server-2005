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

    BYTE		ShelfType;	//��������
    INT			Price;		//�۸�
    INT			VIPPrice;	//VIP�۸�

    INT			Price2;		//��Ԫ��Ϊ׼�ļ۸�
    INT			VIPPrice2;	//VIP�۸���Ԫ��Ϊ׼
    FLOAT		Agio;		//��%Ϊ׼
    std::string	ImagePath;	//·��

    INT			CurNumber;	//��ǰ����
    INT			Number;		//��������	-1����
    DWORD		Refurbish;	//ˢ��ʱ�� �Է���Ϊ��λ	
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