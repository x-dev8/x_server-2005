#pragma once
#include "afxwin.h"
// DropItemDialog dialog

class DropItemDialog : public CDialog
{
	DECLARE_DYNAMIC(DropItemDialog)

public:
	DropItemDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~DropItemDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_DROPITEM };

public:
	void InitInformation();
	void UpdateInformation();

private:
	void FindMonsterIdByName();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

public:
	CEdit m_editMonsterId;
	CComboBox m_comboMonsterName;
	CEdit m_editItemRate;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEditRate();
	afx_msg void OnBnClickedOk();
};
