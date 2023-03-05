#pragma once

#ifndef __PlatForm_ReqAddItem__
#define __PlatForm_ReqAddItem__
#include "PageInterface.h"
// PlatForm_ReqAddItem dialog

class PlatForm_ReqAddItem : public PageInterface
{
	DECLARE_DYNAMIC(PlatForm_ReqAddItem)

public:
	PlatForm_ReqAddItem();
	virtual ~PlatForm_ReqAddItem();

// Dialog Data
	enum { IDD = IDD_DIALOG_PLATFORM_REQADDITEM };

    afx_msg BOOL OnInitDialog();
    afx_msg void OnBnClickedBtnSendReqAddItem();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CString OrderFormID;
    unsigned int AccountId;

    CComboBox  Combox_SelectItem;
    short ItemCount;
};

#endif