#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "QuestEditorDlg.h"

// QuestSet dialog

class CQuestEditDlg;
class QuestSet : public CDialog
{
	DECLARE_DYNAMIC(QuestSet)

public:
	QuestSet(CWnd* pParent = NULL);   // standard constructor
	QuestSet(CQuestEditDlg *pParent);   
	virtual ~QuestSet();

public:
	void InitInformation();

	void ShowSetInfoList(const int nType);
	void ShowSetInfoList(vector<SetInfo> &vecSetInfo);

	void AddSetInfo(const int nType);
	void AddSetInfo(vector<SetInfo> &vecSetInfo, SetInfo &xSetInfo, CStringArray &xStringArray);

	int EditSetInfo(const int nType);
	int EditSetInfo(vector<SetInfo> &vecSetInfo, SetInfo &xSetInfo, CStringArray &xStringArray);

	int DelStringArray(const int nType);
	int DelStringArray(vector<SetInfo> &vecSetInfo, SetInfo &xSetInfo, CStringArray &xStringArray);


public:
	CQuestEditDlg *m_xpQuestEdit;

private:
	void ShowDeleteMenu();
	bool LoadFromSlk( char* szFileName );

private:
	//vector<SetInfo> m_xSetInfo[Enum_End];
// Dialog Data
	enum { IDD = IDD_DIALOG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	int m_nRadioType;
	afx_msg void OnBnClickedButtonAddString();
	CEdit m_editName;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnDelete();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnLbnDblclkList();
	CListCtrl m_listSetInfo;
	afx_msg void OnNMRclickListValue(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_editValue;
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnNMDblclkListValue(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio9();
	afx_msg void OnBnClickedButton13();
	CEdit m_editItemFile;
	CEdit m_editMonsterFile;
	CEdit m_editNpcFile;
	CEdit m_editStringFile;
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	CEdit m_editStringSlkFile;
	CEdit m_editStringXmlFile;
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButtonStringChange();
};


