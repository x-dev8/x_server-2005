// F:\More\Games\Next\Program\trunk\Tool\WorldEditor\Source\UI\ToolsScene\MapContrastDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WorldEditor.h"
#include "MapContrastDlg.h"
#include "Me3d/PostProcess/PostProcessManager.h"
#include "MeTerrain/MapConfigXml.h"


// MapContrastDlg dialog

IMPLEMENT_DYNAMIC(MapContrastDlg, CDialog)

MapContrastDlg::MapContrastDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MapContrastDlg::IDD, pParent)
{
	m_tileId = -1;

}

MapContrastDlg::~MapContrastDlg()
{
}

void MapContrastDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST_R, m_sldContrastR);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST_G, m_sldContrastG);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST_B, m_sldContrastB);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST_C, m_sldContrastC);
}


BEGIN_MESSAGE_MAP(MapContrastDlg, CDialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &MapContrastDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &MapContrastDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// MapContrastDlg message handlers

void MapContrastDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	UpdateContrast();
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void MapContrastDlg::UpdateContrast()
{
	float c = (float)( m_sldContrastC.GetPos() ) / 255.f;
	float r = (float)( m_sldContrastR.GetPos() ) / 255.f;
	float g = (float)( m_sldContrastG.GetPos() ) / 255.f;
	float b = (float)( m_sldContrastB.GetPos() ) / 255.f;
	PostProcessManager::instance().SetBrightNContrast( c, D3DXVECTOR3( r, g, b ) );
}

void MapContrastDlg::SetSLDValue( float r, float g, float b, float c )
{
	m_sldContrastR.SetRange( 0, 500 );
	m_sldContrastG.SetRange( 0, 500 );
	m_sldContrastB.SetRange( 0, 500 );
	m_sldContrastC.SetRange( -125, 125, TRUE );

	m_sldContrastR.SetPos( int(r * 255.f) );
	m_sldContrastG.SetPos( int(g * 255.f) );
	m_sldContrastB.SetPos( int(b * 255.f) );
	m_sldContrastC.SetPos( int(c * 255.f) );
}
void MapContrastDlg::OnBnClickedOk()
{
	CWorldTile* pTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tileId);
	if (!pTile)
	{
		OnOK();
		return;
	}
	float fC = PostProcessManager::instance().GetBrightness();
	D3DXVECTOR3 kB = PostProcessManager::instance().GetContrast();
	pTile->SetBrightnessOffset( fC );
	pTile->SetContrastOffset( kB.x, kB.y, kB.z );
	CMapConfigXml::Instance()->RefreshTileMapInfo(pTile);
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( pTile );
	OnOK();
}

void MapContrastDlg::OnBnClickedButtonReset()
{
	SetSLDValue( 1, 1, 1, 0 );
	UpdateContrast();
}
