#pragma once
#include "afxwin.h"


#ifndef __PLATFORM_ADDPOINTS__
#define __PLATFORM_ADDPOINTS__
#include "PageInterface.h"
// Platform_AddPoints dialog

class Platform_AddPoints : public PageInterface
{
	DECLARE_DYNAMIC(Platform_AddPoints)

public:
	Platform_AddPoints();
	virtual ~Platform_AddPoints();

// Dialog Data
	enum { IDD = IDD_DIALOG_PLATFORM_ADDPOINTS };
    
    BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    
	DECLARE_MESSAGE_MAP()
public:
    CString typesn;
    UINT guid;
    CString signstr;
    CString remark;
    UINT paytime;
    UINT gssid;
    int discount;
    int netincome;
    BYTE channel;
    CComboBox comboTypeId;
    afx_msg void OnBnClickedBtnSendaddpoint();

private:
    unsigned int WM_UserMsg;
public:
    UINT addamount;
    UINT points;
};
#endif