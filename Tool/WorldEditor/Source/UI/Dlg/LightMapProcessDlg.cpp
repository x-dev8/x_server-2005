// F:\Hero\Program\Tool\WorldEditor\Source\UI\Dlg\LightMapProcessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resource/Resource.h"
#include "WorldEditor.h"
#include "LightMapProcessDlg.h"


// LightMapProcessDlg dialog

IMPLEMENT_DYNAMIC(LightMapProcessDlg, CDialog)

LightMapProcessDlg::LightMapProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LightMapProcessDlg::IDD, pParent)
{

}

LightMapProcessDlg::~LightMapProcessDlg()
{
}

void LightMapProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIGHTMAP_TILE, m_processOfTile);
	DDX_Control(pDX, IDC_LIGHTMAP_CHUNK, m_processOfGenerate);
	DDX_Control(pDX, IDC_STATIC_TILE, m_staticTile);
	DDX_Control(pDX, IDC_STATIC_CHUNK, m_staticChunk);
}


BEGIN_MESSAGE_MAP(LightMapProcessDlg, CDialog)
END_MESSAGE_MAP()


// LightMapProcessDlg message handlers
