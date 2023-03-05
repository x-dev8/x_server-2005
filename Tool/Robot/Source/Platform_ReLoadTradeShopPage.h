#pragma once

#ifndef __PLATFORM_RELOADTRADESHOP__
#define __PLATFORM_RELOADTRADESHOP__
#include "PageInterface.h"
// Platform_ReLoadTradeShop dialog

class Platform_ReLoadTradeShop : public PageInterface
{
	DECLARE_DYNAMIC(Platform_ReLoadTradeShop)

public:
	Platform_ReLoadTradeShop();
	virtual ~Platform_ReLoadTradeShop();

// Dialog Data
	enum { IDD = IDD_DIALOG_RELOADTRADESHOP };

    afx_msg void OnBnClickedBtnReloadTradShop();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

#endif
