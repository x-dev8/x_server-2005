#pragma once
#ifndef __PlatformTest__
#define __PlatformTest__
// PlatFormDialog dialog
#include "stdafx.h"
#include "resource.h"

class PlatFormDialog : public CDialog
{
	DECLARE_DYNAMIC(PlatFormDialog)

public:
	PlatFormDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~PlatFormDialog();
    static void RunThreadFunc(void *pVoid);
// Dialog Data
	enum { IDD = IDD_DIALOG_PLATFORM };

    static volatile bool _exit;
    static volatile bool _alaryExitThread;
private:
    // tab control
    
protected:
    virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
};

#endif