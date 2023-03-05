#pragma once

class CMapModelsDlg : public CDialog
{
public:
	enum { IDD = IDD_MAP_MODELS };

	DECLARE_DYNAMIC(CMapModelsDlg)

	CMapModelsDlg(CWnd *lpParent = NULL);
	virtual ~CMapModelsDlg();

public:
	enum MapModelState
	{
		MMS_OK = 0,
		MMS_LOAD_FAILED,
		MMS_VERSION_UNDER_105
	};

public:
	virtual void DoDataExchange(CDataExchange *pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();

	afx_msg void OnBtnClickedDel();
	afx_msg void OnBtnClickedCleanUnused();
	afx_msg void OnBtnClickedExport();

	afx_msg void OnNotifyCustomDraw(NMHDR *pNmHdr, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

private:
	bool IsModelLoadFailed(TObjectInfo *obj);
	bool IsModelVersionUnder105(TObjectInfo *obj);

	void Refresh();

private:
	CListCtrl mList;
	std::string mClientFolder;

	std::vector<MapModelState> mMapModelStates;
};