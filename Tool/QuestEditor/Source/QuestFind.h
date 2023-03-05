#pragma once
#include "afxwin.h"

// QuestFind dialog

class QuestFind : public CDialog
{
	DECLARE_DYNAMIC(QuestFind)

public:
	QuestFind(CWnd* pParent = NULL);   // standard constructor
	virtual ~QuestFind();
// Dialog Data
	enum { IDD = IDD_DIALOG_FIND };



public:
	void InitInformation();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboType;
	afx_msg void OnBnClickedButtonFind();
	CEdit m_editFind;
	CEdit m_editReplace;
	CButton m_checkMatch;
};
