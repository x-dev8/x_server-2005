#include "Font3DManager.h"
#include "Billboard2D.h"

Font3DManager* Font3DManager::m_pInst = 0;

void Font3DManager::Render()
{
	IRenderer* RI = GetEngine()->GetRenderer();        



	RI->SetRenderState( D3DRS_ZENABLE, TRUE );
	RI->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	RI->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
	RI->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	RI->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);
	RI->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	RI->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	RI->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);
	RI->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	RI->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	RI->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	RI->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	RI->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//RI->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1 );	
	RI->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	RI->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	RI->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	RI->SetRenderState(D3DRS_LIGHTING, FALSE);
	RI->SetRenderState(D3DRS_FOGENABLE, FALSE);

	RI->SetFVF(Billboard3D::FVF);

	RI->Commit();

	bool bNoRefresh = false;
	static int snFrameCount = 0;
	static int snMaxFrameCount = 10;
	if( ++snFrameCount && snFrameCount < 10 )
		bNoRefresh = true;
	else
		snFrameCount = 0;

	Font3DList::iterator it, end = m_font3DList.end();
	for (it = m_font3DList.begin(); it != end; ++it)
	{
		if( (*it)->Render( bNoRefresh ) )
			bNoRefresh = true;
	}

	// Çå³ýFVF
	RI->SetFVF(0);
	RI->Commit();
}