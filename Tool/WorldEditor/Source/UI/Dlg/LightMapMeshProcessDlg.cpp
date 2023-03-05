// LightMapMeshProcessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WorldEditor.h"
#include "LightMapMeshProcessDlg.h"


// LightMapMeshProcessDlg dialog

IMPLEMENT_DYNAMIC(LightMapMeshProcessDlg, CDialog)

LightMapMeshProcessDlg::LightMapMeshProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LightMapMeshProcessDlg::IDD, pParent)
{

}

LightMapMeshProcessDlg::~LightMapMeshProcessDlg()
{
}

void LightMapMeshProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_LIGHTMAP_MESH, m_process);
	DDX_Control(pDX, IDC_STATIC_LM_MESH, m_static);
}


BEGIN_MESSAGE_MAP(LightMapMeshProcessDlg, CDialog)
END_MESSAGE_MAP()


// LightMapMeshProcessDlg message handlers
