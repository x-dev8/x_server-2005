#pragma once
#include "BaseInfo.h"
#include "afxwin.h"


// CCommondDialog dialog

class CCommondDialog : public CDialog
{
	DECLARE_DYNAMIC(CCommondDialog)

public:
	CCommondDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCommondDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_ROBOT_INSTRUCTION };

    void OnClickedAddCommondBTN();
    void OnClickedSubCommondBTN();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
    CListCtrl   m_BotCommondList;
    CString     m_CommondShow;
    CString     m_CommondInput;
    int         m_CommondParam1;
    CString     m_CommondParam2;
    CComboBox   m_CommondCombo;
    CComboBox   m_CommondTimeCombo;
    CComboBox   m_CommondPriorityCombo;
    CButton     m_AddCommondBtn;
    CButton     m_SubCommondBtn;

    static const char *CommondChar[];
};
