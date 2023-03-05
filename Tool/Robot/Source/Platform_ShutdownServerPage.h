#pragma once
#include "PageInterface.h"

// Platform_ShutdownServer dialog

class Platform_ShutdownServer : public PageInterface
{
	DECLARE_DYNAMIC(Platform_ShutdownServer)

public:
	Platform_ShutdownServer();
	virtual ~Platform_ShutdownServer();

// Dialog Data
	enum { IDD = IDD_DIALOG_PLATFORM_SHUTDOWNSERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangeEdShutdownTime();
    afx_msg BOOL OnInitDialog();

    UINT GetShutDownTime(){return _ShutdownTime;}
private:
    UINT _ShutdownTime;
public:
    afx_msg void OnBnClickedBtnSendSd();
};
