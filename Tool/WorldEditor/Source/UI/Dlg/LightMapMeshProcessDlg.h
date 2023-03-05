#pragma once


// LightMapMeshProcessDlg dialog

class LightMapMeshProcessDlg : public CDialog
{
	DECLARE_DYNAMIC(LightMapMeshProcessDlg)

public:
	LightMapMeshProcessDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~LightMapMeshProcessDlg();

// Dialog Data
	enum { IDD = IDD_LIGHTMAP_MESH_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CProgressCtrl m_process;
	CStatic m_static;
};
