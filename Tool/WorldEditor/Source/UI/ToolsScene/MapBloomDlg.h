#pragma once


// MapBloomDlg dialog

class MapBloomDlg : public CDialog
{
	DECLARE_DYNAMIC(MapBloomDlg)

public:
	MapBloomDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~MapBloomDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_BLOOM };

protected:
	CSliderCtrl m_sldBloomScale;
	CSliderCtrl m_sldBloomLuminance;
	sInt32 m_tileId;

public:
	void UpdateBloom();
	void SetBloomValue( float fScale, float Lumi );
	void SetTitleId( sInt32 id ){ m_tileId = id; }

protected:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonBloomreset();
};
