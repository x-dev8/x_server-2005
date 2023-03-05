#pragma once


// CNpcPosUpdate dialog

class CNpcPosUpdate : public CDialog
{
	DECLARE_DYNAMIC(CNpcPosUpdate)

public:
	CNpcPosUpdate(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNpcPosUpdate();

// Dialog Data
	enum { IDD = IDD_UPDATEPOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// «Î ‰»Î’˚ ˝
	int m_mapID;
	float m_fXPos;
	float m_fYPos;
	afx_msg void OnBnClickedButton1();
};
