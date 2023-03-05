#pragma once

class CCameraFollowDialog : public CDialog
{
public:
	enum { IDD = IDD_CAMERA_FOLLOW };

	DECLARE_DYNAMIC(CCameraFollowDialog)

	CCameraFollowDialog(CWnd *lpParent = NULL);
	virtual ~CCameraFollowDialog();

public:
	virtual void DoDataExchange(CDataExchange *pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

private:
	CString mInputMex;
};
