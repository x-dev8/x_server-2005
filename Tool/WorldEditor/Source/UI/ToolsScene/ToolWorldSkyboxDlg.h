#pragma once
#include "afxwin.h"


// CToolWorldSkyboxDlg dialog

class CToolWorldSkyboxDlg : public CDialog
{
	DECLARE_DYNAMIC(CToolWorldSkyboxDlg)

public:
	CToolWorldSkyboxDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CToolWorldSkyboxDlg();

// Dialog Data
	enum { IDD = IDD_DLG_SKYBOXBLOOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL		OnInitDialog();
	virtual void		OnOK();

	DECLARE_MESSAGE_MAP()
protected:
	CXTBrowseEdit m_editSkyboxPath;	
	CXTBrowseEdit m_editSkyboxTexturePath;	
public:
	CStringA m_strFilename;
	CStringA m_strTextureFilename;
};
