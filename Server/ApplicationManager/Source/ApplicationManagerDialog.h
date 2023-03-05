#pragma once

#include <string>
#include <vector>
#include <map>
#include <afxcview.h>
#include "TabSheet.h"
#include "ProcessManager.h"
#include "HelpDialog.h"

enum LeafNodeType
{
    LNT_NONE,
    LNT_APPLICATION_NORMAL,
    LNT_APPLICATION_CAN_RECEIVE_MESSAGE,
};

class CApplicationManagerDialog : public CDialog
{
public:
	CApplicationManagerDialog(CWnd* pParent = NULL);

	enum { IDD = IDD_PROTECTOR_DIALOG };

public:
    bool LoadConfig(const std::string& strSolutionPath, bool bAppend=false );

    void ClearConfig();

    afx_msg void OnTimer(UINT_PTR nIDEvent);

    afx_msg void OnFileExit();

    afx_msg void OnOpenSolution();

    afx_msg void OnAppendOpenconfig();

    afx_msg void OnNMDblclkTreeProcess(NMHDR *pNMHDR, LRESULT *pResult);

    afx_msg void OnTcnSelchangeTabProcess(NMHDR *pNMHDR, LRESULT *pResult);

    afx_msg void OnDebugTestcase();

    afx_msg void OnSize(UINT nType, int cx, int cy);

    afx_msg void OnHelpAbout();

	void SetTreeItemText( std::string strName, bool IsBad );
	HTREEITEM FindTreeItem( HTREEITEM item, CString strText );

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

    HTREEITEM AddTreeNode(HTREEITEM hParentItem, const std::string& strNodeText, unsigned int uiNodeType, unsigned  long ulDataId );

    virtual BOOL OnInitDialog();

    afx_msg void OnPaint();

    afx_msg HCURSOR OnQueryDragIcon();

    virtual void OnCancel();

    DECLARE_MESSAGE_MAP()

    void _StartAllApplication();

protected:
    HICON m_hIcon;

    CStatic*   _pTextInfo;

    CTreeCtrl* _pProcessTree;

    CTabSheet  _ProcessTab;

    bool _bAutoStart;

	bool _bCrashAutoStart;
public:
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
