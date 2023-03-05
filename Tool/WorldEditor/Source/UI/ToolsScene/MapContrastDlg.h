#pragma once
#include "afxcmn.h"


// MapContrastDlg dialog

class MapContrastDlg : public CDialog
{
	DECLARE_DYNAMIC(MapContrastDlg)

public:
	MapContrastDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~MapContrastDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONTRAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_sldContrastR;
	CSliderCtrl m_sldContrastG;
	CSliderCtrl m_sldContrastB;
	CSliderCtrl m_sldContrastC;
	sInt32 m_tileId;

public:
	void UpdateContrast();
	void SetSLDValue( float r, float g, float b, float c );
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonReset();
};
