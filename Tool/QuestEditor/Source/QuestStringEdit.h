#pragma once
#include "afxwin.h"


// QuestStringEdit dialog

class QuestStringEdit : public CDialog
{
	DECLARE_DYNAMIC(QuestStringEdit)

public:
	QuestStringEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~QuestStringEdit();

	void InitInformation();

	void UpdateInitInformation(const char *path, int nQuestId);

	void SaveStringEdit();

	const char* RemoveChangeLineChar(const char *szValue);

// Dialog Data
	enum { IDD = IDD_DIALOG_QUESTSTRINGEDIT };


private:
	int m_nQuestId;

	CString m_strFilePath;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboId;
	CListBox m_listString;
	afx_msg void OnBnClickedButtonAddString();
	CEdit m_editString;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnLbnDblclkListQuest();
	afx_msg void OnBnClickedButtonRemove();
	afx_msg void OnCbnSelchangeComboId();
};
