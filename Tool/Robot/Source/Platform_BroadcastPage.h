#pragma once
#include "PageInterface.h"
// Platform_Broadcast dialog

class Platform_Broadcast : public PageInterface
{
	DECLARE_DYNAMIC(Platform_Broadcast)

public:
	Platform_Broadcast();   // standard constructor
	virtual ~Platform_Broadcast();

// Dialog Data
	enum { IDD = IDD_DIALOG_PLATFORM_BROADCAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnPlatfromSendbroadcast();
    CString BroadcastString;
};
