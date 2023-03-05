#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CCompileDlg 对话框

class CCompileDlg : public CDialog
{
	DECLARE_DYNAMIC(CCompileDlg)

public:
	CCompileDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCompileDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_BINDATA_BUILDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lbOutput;
	afx_msg void OnBnClickedButtonCompile();
	afx_msg void OnBnClickedButtonBuildObj();
	afx_msg void OnBnClickedButtonClearObj();
	CProgressCtrl m_progress;
	CStatic m_text;
public:
	CListBox m_lbError;
    afx_msg void OnClose();
};
