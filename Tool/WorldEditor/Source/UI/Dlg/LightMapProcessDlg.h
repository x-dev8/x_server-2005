#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// LightMapProcessDlg dialog

class LightMapProcessDlg : public CDialog
{
	DECLARE_DYNAMIC(LightMapProcessDlg)

public:
	LightMapProcessDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~LightMapProcessDlg();

// Dialog Data
	enum { IDD = IDD_LIGHTMAP_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_processOfTile;
	CProgressCtrl m_processOfGenerate;
	CStatic m_staticTile;
	CStatic m_staticChunk;
};
