#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "GameBot.h"

#include <string>
#include <vector>
using namespace std;

// COptionDlg 对话框

class COptionDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionDlg)

public:
	COptionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COptionDlg();

// 对话框数据
	enum { IDD = IDD_OPTION_DIALOG };

public:
	void WritePrivateProfileInt(LPCTSTR lpAppName,LPCTSTR lpKeyName,int nValue,	LPCTSTR lpFileName);

	void InitInformation();

	void ReadAllScirpt(const char* pszPath);


	void AddInVector(SAddInfo &xAddInfo);
	bool AddInListCtrl(int nIndex, SAddInfo &xAddInfo);
	bool DeleteFromVector(int nStartId);

	SAddInfo *FindAddInfo(int nStartId);

	void ShowAddInfo(SAddInfo &xAddInfo);
	void ShowAddInfoList();

private:
	vector<string> m_vecType;
	vector<string> m_vecMap;

	vector<string> m_vecScript;

	vector<SAddInfo> m_vecAddInfo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    virtual BOOL PreTranslateMessage(MSG* pMsg); //消息处理
public:
    CEdit m_editIp;
public:
    CEdit m_editPort;
public:
    CEdit m_editVersion;
protected:
    virtual void OnOK();
    virtual void OnCancel();
public:
	CEdit m_editAccount;
	CEdit m_editWidth;
	CEdit m_editPassword;
	afx_msg void OnBnClickedCheckRequest();
	CEdit m_editSecond;
	CEdit m_editCount;
	CButton m_checkRequest;
	CButton m_checkSleep;
	CListCtrl m_listAreaInfo;
	CComboBox m_comboId;
	CComboBox m_comboType;
	CComboBox m_comboCount;
	CComboBox m_comboMap;
	CComboBox m_comboScript;
	CEdit m_editAddTime;
	CEdit m_editRunTime;
	CEdit m_editPosX;
	CEdit m_editPosY;
	CEdit m_editRadius;
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnDeleteaddinfo();
	afx_msg void OnNMRclickListAddInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListAddInfo(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_checkLoginOnly;
	CButton m_checkReLogin;
	CButton m_checkDisableCheckTime;
    CComboBox m_cmbChooseNet;    // 网络选择
	afx_msg void OnBnClickedOk();
};
