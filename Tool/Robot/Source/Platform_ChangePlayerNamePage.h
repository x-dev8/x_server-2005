#pragma once

#ifndef __Platform_ChangePlayerName__
#define __Platform_ChangePlayerName__
#include "PageInterface.h"
// Platform_ChangePlayerName dialog

class Platform_ChangePlayerName : public PageInterface
{
	DECLARE_DYNAMIC(Platform_ChangePlayerName)

public:
	Platform_ChangePlayerName();
	virtual ~Platform_ChangePlayerName();

// Dialog Data
	enum { IDD = IDD_DIALOG_PLATFORM_CHANGEROLENAME };
    afx_msg BOOL OnInitDialog();
    afx_msg void OnBnClickedBtnSendChangeRoleName();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CString TargetPlayerName;
    CString NewPlayerName;
};
#endif