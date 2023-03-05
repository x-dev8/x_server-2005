#include "stdafx.h"
#include "WorldEditor.h"
#include "MapBloomDlg.h"
#include "Me3d/PostProcess/PostProcessManager.h"
#include "MeTerrain/MapConfigXml.h"


// MapBloomDlg dialog

IMPLEMENT_DYNAMIC(MapBloomDlg, CDialog)

MapBloomDlg::MapBloomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MapBloomDlg::IDD, pParent)
{
	m_tileId = -1;

}

MapBloomDlg::~MapBloomDlg()
{
}

void MapBloomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_BLOOMSCALE, m_sldBloomScale);
	DDX_Control(pDX, IDC_SLIDER_BLOOMLUMNIANCE, m_sldBloomLuminance);
}


BEGIN_MESSAGE_MAP(MapBloomDlg, CDialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &MapBloomDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_BLOOMRESET, &MapBloomDlg::OnBnClickedButtonBloomreset)
END_MESSAGE_MAP()


// MapBloomDlg message handlers

// MapContrastDlg message handlers

void MapBloomDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	UpdateBloom();
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void MapBloomDlg::UpdateBloom()
{
	float fScale = (float)( m_sldBloomScale.GetPos() ) / 125.f;
	float fLumi = (float)( m_sldBloomLuminance.GetPos() ) / 5000.f;
	PostProcessManager::instance().setParameter( "BloomScale", D3DXVECTOR4( fScale, 0, 0, 0 ) );
	PostProcessManager::instance().setParameter( "Luminance", D3DXVECTOR4( fLumi, 0, 0, 0 ) );
}

void MapBloomDlg::SetBloomValue( float fScale, float Lumi )
{
	m_sldBloomScale.SetRange( 0, 500 );
	m_sldBloomLuminance.SetRange( 0, 500 );

	m_sldBloomScale.SetPos( int(fScale * 125.f) );
	m_sldBloomLuminance.SetPos( int(Lumi * 5000.f) );
}
void MapBloomDlg::OnBnClickedOk()
{
	CWorldTile* pTile = theApp.GetWorld()->GetWorldBuffer()->GetTile(m_tileId);
	if (!pTile)
	{
		OnOK();
		return;
	}
	D3DXVECTOR4 kScale = *PostProcessManager::instance().getParameterVector4( "BloomScale" );
	D3DXVECTOR4 kLumi = *PostProcessManager::instance().getParameterVector4( "Luminance" );
	pTile->SetBloomScale( kScale.x );
	pTile->SetLuminance( kLumi.x );
	CMapConfigXml::Instance()->RefreshTileMapInfo(pTile);
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify( pTile );
	OnOK();
}
void MapBloomDlg::OnBnClickedButtonBloomreset()
{
	SetBloomValue( 0, 0 );
	UpdateBloom();
}
