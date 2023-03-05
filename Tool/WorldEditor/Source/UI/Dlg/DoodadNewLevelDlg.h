#pragma once


// CDoodadNewLevelDlg dialog

class CDoodadNewLevelDlg : public CDialog
{
	DECLARE_DYNAMIC(CDoodadNewLevelDlg)

public:
	CDoodadNewLevelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDoodadNewLevelDlg();

// Dialog Data
	enum { IDD = IDD_DLG_DOODADS_NEWLEVEL };
	virtual BOOL	OnInitDialog();
	virtual void		OnOK();
	int GetUnitSize() const;
//	void SetUnitSize(CComboBox val) { m_UnitSize = val; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CComboBox			m_UnitSize;
	sInt32				m_nunitSize;
	DECLARE_MESSAGE_MAP()
};
