#pragma once

#include "PageInterface.h"
#include "afxwin.h"
// Platform_ChangeMapRate dialog

class Platform_ChangeMapRate : public PageInterface
{
	DECLARE_DYNAMIC(Platform_ChangeMapRate)

public:
	Platform_ChangeMapRate();
	virtual ~Platform_ChangeMapRate();
    BOOL OnInitDialog();
// Dialog Data
	enum { IDD = IDD_DIALOG_PLATFORM_CHANGE_MAPRATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CString Ed_FLoat_Rate;
    int Slider_Float_Rate;
    afx_msg void OnEnChangeEdFloatRate();
    afx_msg void OnNMReleasedcaptureSliderFloatRate(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedBtnChangRate();
    CComboBox Combo_ChangeMapId;
};
