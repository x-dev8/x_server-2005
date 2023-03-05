#pragma once
#include "afxwin.h"


// DorpItem dialog

class DropMonsterDialog : public CDialog
{
	DECLARE_DYNAMIC(DropMonsterDialog)

public:
	DropMonsterDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~DropMonsterDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_DROPMONSTER };


public:
	void InitInformation();
	void UpdateInformation();


private:
	void FindItemIdByName();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:	
	CEdit m_editVarId;
	CEdit m_editItemId;
	CComboBox m_comboItemName;
	CEdit m_editItemCount;
	CEdit m_editItemRate;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnKillfocusEditVarId();
	afx_msg void OnEnKillfocusEditItemId();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEditRate();
};
