#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "ui/ToolsWnd/NpcEditDlg.h"
#include "../Custom/ScrollableDialog.h"

// CDlgNpcEditor dialog
class CToolNpc;
class CDlgNpcEditor : public ScrollableDialog
{
	DECLARE_DYNAMIC(CDlgNpcEditor)

public:
	CDlgNpcEditor(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgNpcEditor();

	void			SetActive( bool isModify = false );
// Dialog Data
	enum { IDD = IDD_DIALOG_NPC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CToolNpc*		GetToolNpc();
	void            InitData(); 
	void            LoadNpcInTheMap();
	void            LoadComBoxData();
	const char*     ParseString(CString& strData);

	void            RefreshNpc(CNpcRes* res);
	void RefreshNpcPos(CNpcRes *res_);
	void            InsertNewItem(CNpcRes* pRes);
	void            DelItem(CNpcRes* pRes);

    bool            CloneNpc(int oldMapID,int newMapID);
    void            CloneNpcPosition(int nOldMapID,int nNewMapID);

    bool            DeleteNpc(int mapID);
    void            DeleteNpcPosition(int mapID);

	int GetNpcID(const HTREEITEM item_);
	void SetSelectedNpc(int NpcID_);

public:
	afx_msg void OnBnClickedRadioAddNpc();
	afx_msg void OnBnClickedRadioNpcEdit();
	afx_msg void OnNMDblclkNpclist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButupdaepos();
	afx_msg void OnBnClickedButupdatestr();
	afx_msg void OnBnClickedSavedata();
	afx_msg void OnCbnSelchangeComboModid();

	afx_msg LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	bool InitComboxData(CString strData/*const char *pszString*/,const char *pszKeyWord,const char *pszAttribute,CComboBox* comBox);
private:
	CTreeCtrl m_TreeNpc;
	
	CComboBox m_ComModelID;
	CComboBox m_ComType;

	CEdit m_findx;
	CEdit m_findY;
	CEdit m_cNpcX;
	CEdit m_cNpcY;
	CEdit m_cNpcZ;
	CEdit m_NpcDir;
	CEdit m_cNpcScale;

	CButton m_chkLine;
	CNpcEditDlg m_DlgNpcEdit;
public:
	afx_msg void OnBnClickedRadioAddPos();
	afx_msg void OnBnClickedRadioNone();
	afx_msg void OnBnClickedButdelpoi();
	afx_msg void OnBnClickedButuppoi();
	afx_msg void OnBnClickedSavepos();
	CComboBox m_ComShow;
	afx_msg void OnBnClickedUpdatenpc();
	afx_msg void OnBnClickedShowline();
    afx_msg void OnBnClickedCopynpc();
    afx_msg void OnBnClickedDelnpc();
    CEdit m_textMap;
    afx_msg void OnSaveNpcString();
	afx_msg void OnTvnSelchangedNpclist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
