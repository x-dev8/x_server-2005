#pragma once
#include "BaseInfo.h"
#include "afxwin.h"
#include "afxcmn.h"


/*

	负责客户端机器人 帐号名密码 采集

*/




// LoginInfo dialog
class Client;
class LoginInfo : public CDialog, public BaseInfo
{
	DECLARE_DYNAMIC(LoginInfo)

public:
	LoginInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~LoginInfo();

// Dialog Data
	enum { IDD = IDD_DIALOG_LOGIN };

public:
	virtual void InitInformation();
	virtual void UpdateInformation(BaseRobot *pBot){};

	void SaveClientConfig();
	void ReadClientConfig();

	void CreateCharSuccess();

private:
	Client *m_pClient;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	CButton m_buttonSend;
	CButton m_buttonEnter;
	CButton m_buttonCreate;
	CButton m_buttonDelete;
	CButton m_buttonLoginOut;
	CButton m_buttonCheck;
	CButton m_buttonCreateOk;
	CButton m_buttonReset;
	CButton m_buttonCancle;
	CEdit m_editAccount;
	CEdit m_editPassword;
	CButton m_CheckSave;
	CEdit m_editName;
	BOOL m_RadioSale;
	BOOL m_RadioPrefession;
	afx_msg void OnBnClickedButtonLoginIn();
	CListCtrl m_listChar;
	afx_msg void OnNMClickListChar(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonEnter();
	afx_msg void OnBnClickedButtonCreateChar();
	afx_msg void OnBnClickedButtonCancle();
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonLoginOut();
	afx_msg void OnBnClickedButtonCreateOk();
	afx_msg void OnNMDblclkListChar(NMHDR *pNMHDR, LRESULT *pResult);
};
