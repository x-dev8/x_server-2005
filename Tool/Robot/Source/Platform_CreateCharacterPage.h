#pragma once

#ifndef __PLATFORM_CREATECHARACTER__
#define __PLATFORM_CREATECHARACTER__

#include "PageInterface.h"
// Platform_CreateCharacter dialog

class Platform_CreateCharacter : public PageInterface
{
	DECLARE_DYNAMIC(Platform_CreateCharacter)

public:
	Platform_CreateCharacter();
	virtual ~Platform_CreateCharacter();

// Dialog Data
	enum { IDD = IDD_DIALOG_PLATFORM_CREATEROLE };
    
    afx_msg BOOL OnInitDialog();
    afx_msg void OnBnClickedBtnSendCreateRole();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
    CString RoleName;
    unsigned long AccoundId;

    CComboBox Combo_Level;
    CComboBox Combo_Sex;
    CComboBox Combo_GiftItemId;
    CComboBox Combo_Country;
    CComboBox Combo_Profession;
};
#endif