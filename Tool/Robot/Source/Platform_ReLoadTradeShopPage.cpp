// Source\Platform_ReLoadTradeShopPage.cpp : implementation file
//

#include "stdafx.h"
#include "Platform_ReLoadTradeShopPage.h"


// Platform_ReLoadTradeShop dialog

IMPLEMENT_DYNAMIC(Platform_ReLoadTradeShop, PageInterface)

Platform_ReLoadTradeShop::Platform_ReLoadTradeShop()
	: PageInterface(Platform_ReLoadTradeShop::IDD)
{
    SetType(ReLoadTradShopPage);
}

Platform_ReLoadTradeShop::~Platform_ReLoadTradeShop()
{
}

void Platform_ReLoadTradeShop::DoDataExchange(CDataExchange* pDX)
{
	PageInterface::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Platform_ReLoadTradeShop, PageInterface)
    ON_BN_CLICKED(IDC_BTN_SEND_RELOADTRADSHOP, &Platform_ReLoadTradeShop::OnBnClickedBtnReloadTradShop)
END_MESSAGE_MAP()

void Platform_ReLoadTradeShop::OnBnClickedBtnReloadTradShop()
{
    if (NULL != Bot)
    {
        Bot->ReqReloadTradeShop();
        MessageBox("·¢ËÍÍê±Ï!");
    }
}

// Platform_ReLoadTradeShop message handlers
