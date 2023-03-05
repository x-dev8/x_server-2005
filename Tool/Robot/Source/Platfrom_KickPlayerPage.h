#pragma once
#ifndef __PLATFROM_KICKPLAYER__
#define __PLATFROM_KICKPLAYER__

#include "PageInterface.h"

// Platfrom_KickPlayer dialog

class Platfrom_KickPlayer : public PageInterface
{
	DECLARE_DYNAMIC(Platfrom_KickPlayer)

public:
	Platfrom_KickPlayer();
	virtual ~Platfrom_KickPlayer();

// Dialog Data
	enum { IDD = IDD_DIALOG_PLATFORM_KICKPLAYER };
    BOOL OnInitDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnKick();
    CString KickPlayerName;
};
#endif