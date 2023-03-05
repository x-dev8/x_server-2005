#include "ProgressBar3DManager.h"

#define BACKGROUND_COLOR D3DCOLOR_ARGB(255, 42, 40, 40)
#define BAR_COLOR D3DCOLOR_ARGB(255, 175, 19, 19)

ProgressBar3D::ProgressBar3D()
	: m_fWidthRateBack(1.0f), m_fHeightRateBack(1.0f), m_fWidthRateBar(1.0f), m_fHeightRateBar(1.0f), m_fOffsetY(0.33f),
	m_nMaxValue(0), m_nValue(0), m_fValueRate(1.0f),
	m_nTexId(-1), m_bVisible(true)
{
	memset(m_pElements, 0, sizeof(BillboardBase*)*2);
}

ProgressBar3D::~ProgressBar3D()
{
	Destroy();
}

HRESULT ProgressBar3D::Create(LPDIRECT3DDEVICE9 device, const std::string& texFilename,
			   const D3DXVECTOR2 backgroundUV[], const D3DXVECTOR2 progressUV[],
			   float widthRateBack, float heightRateBack, float widthRateBar, float heightRateBar,
			   DWORD color, DWORD backColor)
{
	HRESULT hr;

	m_fWidthRateBack = widthRateBack;
	m_fHeightRateBack = heightRateBack;
	m_fWidthRateBar = widthRateBar;
	m_fHeightRateBar = heightRateBar;
	m_color = color;
	m_backColor = backColor;
	memcpy(m_backgroundUV, backgroundUV, 4 * sizeof(D3DXVECTOR2));
	memcpy(m_progressUV, progressUV, 4 * sizeof(D3DXVECTOR2));

	BillboardBase::Vertex vs[4];
	GetBackgroundVertexData(vs);
	m_pElements[0] = MeNew Billboard3D();
	if (FAILED(hr = m_pElements[0]->Create(device, vs)))
	{
		delete m_pElements[0];
		m_pElements[0] = NULL;
		return hr;
	}

	GetBarVertexData(vs);
	m_pElements[1] = MeNew Billboard3D();
	if (FAILED(hr = m_pElements[1]->Create(device, vs)))
	{
		delete m_pElements[1];
		m_pElements[1] = NULL;
		return hr;
	}

	char szFileName[MAX_PATH] = {0};
	sprintf_s(szFileName, MAX_PATH - 1, "%s\\%s", GetRootPath(), texFilename.c_str());
	short texid = GetEngine()->GetTextureManager()->RegisterTexture(szFileName, FALSE, TRUE);
	ITexture *tex_ptr = GetEngine()->GetTextureManager()->GetTexture(texid);
	if (tex_ptr != NULL)
	{
		m_pElements[1]->SetTexture((LPDIRECT3DTEXTURE9) tex_ptr->GetData());
	}

	ProgressBar3DManager::Get().AddProgressBar3D(this);
	return S_OK;
}

void ProgressBar3D::Render()
{
	if (!m_bVisible)
		return;

	for (size_t i = 0; i < 2; ++i)
	{
		if (m_pElements[i])
			m_pElements[i]->Render();
	}
}

void ProgressBar3D::Destroy()
{
	for (size_t i = 0; i < 2; ++i)
	{
		if (m_pElements[i])
		{
			m_pElements[i]->Destroy();
			delete m_pElements[i];
			m_pElements[i] = 0;
		}
	}
	ProgressBar3DManager::Get().RemoveProgressBar3D(this);

    if( m_nTexId != -1 )
	    GetEngine()->GetTextureManager()->UnRegisterTexture(m_nTexId);
	m_nTexId = -1;
}

void ProgressBar3D::SetPosition(const D3DXVECTOR3& pos)
{
	if(m_pElements[0])
	   m_pElements[0]->SetPosition(pos);

	if(m_pElements[1])
	   m_pElements[1]->SetPosition(pos);
}

void ProgressBar3D::SetScale(const D3DXVECTOR3& scale)
{
	if(m_pElements[0])
	    m_pElements[0]->SetScale(scale);
	
	if(m_pElements[1])
	   m_pElements[1]->SetScale(scale);
}

void ProgressBar3D::SetVisible(bool v)
{
	m_bVisible = v;
}

void ProgressBar3D::SetCamera(MeCamera* camera)
{
	if(m_pElements[0])
	   m_pElements[0]->SetCamera(camera);

	if(m_pElements[1])
	   m_pElements[1]->SetCamera(camera);
}

void ProgressBar3D::SetMaxValue(int v)
{
	m_nMaxValue = v;
}

void ProgressBar3D::SetValue(int v)
{
	m_nValue = v;
	if (m_nValue > m_nMaxValue)
		m_nValue = m_nMaxValue;
	float f = (float)m_nValue / m_nMaxValue;
	if (f == m_fValueRate)
		return;

	m_fValueRate = f;

	BillboardBase::Vertex vs[4];
	GetBackgroundVertexData(vs);
	if(m_pElements[0])
	   m_pElements[0]->UpdateVB(vs);

	GetBarVertexData(vs);
	if(m_pElements[1])
	   m_pElements[1]->UpdateVB(vs);
}

void ProgressBar3D::SetOffsetY(float offsetY)
{
	if (m_fOffsetY != offsetY)
	{
		m_fOffsetY = offsetY;

		BillboardBase::Vertex vs[4];
		GetBackgroundVertexData(vs);
		if(m_pElements[0])
		   m_pElements[0]->UpdateVB(vs);

		GetBarVertexData(vs);
		if(m_pElements[1])
		   m_pElements[1]->UpdateVB(vs);
	}
}

void ProgressBar3D::GetBackgroundVertexData(BillboardBase::Vertex vs[])
{
	vs[0].p = D3DXVECTOR3(-0.5f * m_fWidthRateBack, m_fOffsetY + 0.5f * m_fHeightRateBack, 0.0f);
	vs[0].c = m_backColor;
	vs[0].uv = m_backgroundUV[0];

	vs[1].p = D3DXVECTOR3(0.5f * m_fWidthRateBack, m_fOffsetY + 0.5f * m_fHeightRateBack, 0.0f);
	vs[1].c = m_backColor;
	vs[1].uv = m_backgroundUV[1];

	vs[2].p = D3DXVECTOR3(0.5f * m_fWidthRateBack, m_fOffsetY - 0.5f * m_fHeightRateBack, 0.0f);
	vs[2].c = m_backColor;
	vs[2].uv = m_backgroundUV[2];

	vs[3].p = D3DXVECTOR3(-0.5f * m_fWidthRateBack, m_fOffsetY - 0.5f * m_fHeightRateBack, 0.0f);
	vs[3].c = m_backColor;
	vs[3].uv = m_backgroundUV[3];
}

void ProgressBar3D::GetBarVertexData(BillboardBase::Vertex vs[])
{
	vs[0].p = D3DXVECTOR3(-0.5f * m_fWidthRateBar, m_fOffsetY + 0.5f * m_fHeightRateBar, 0.0f);
	vs[0].c = m_color;
	vs[0].uv = m_progressUV[0];

	vs[1].p = D3DXVECTOR3((1.0f * m_fValueRate - 0.5f) * m_fWidthRateBar, m_fOffsetY + 0.5f * m_fHeightRateBar, 0.0f);
	vs[1].c = m_color;
	vs[1].uv = D3DXVECTOR2((m_progressUV[1].x - m_progressUV[0].x) * m_fValueRate, m_progressUV[1].y);

	vs[2].p = D3DXVECTOR3((1.0f * m_fValueRate - 0.5f) * m_fWidthRateBar, m_fOffsetY - 0.5f * m_fHeightRateBar, 0.0f);
	vs[2].c = m_color;
	vs[2].uv = D3DXVECTOR2((m_progressUV[2].x - m_progressUV[0].x) * m_fValueRate, m_progressUV[2].y);

	vs[3].p = D3DXVECTOR3(-0.5f * m_fWidthRateBar, m_fOffsetY - 0.5f * m_fHeightRateBar, 0.0f);
	vs[3].c = m_color;
	vs[3].uv = m_progressUV[3];
}

//---------------------------------------------------------------------------
ProgressBar3DManager* ProgressBar3DManager::s_pInst = 0;

ProgressBar3DManager::ProgressBar3DManager()
{

}

ProgressBar3DManager::~ProgressBar3DManager()
{

}

void ProgressBar3DManager::Render()
{
	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice();

	RI->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	RI->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	RI->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	RI->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);
	RI->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	RI->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	RI->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	RI->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	RI->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	RI->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	RI->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	RI->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	RI->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	RI->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	RI->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000022);
	RI->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	RI->SetRenderState(D3DRS_LIGHTING, FALSE);
	RI->SetRenderState(D3DRS_FOGENABLE, FALSE);
	RI->SetRenderState(D3DRS_ZENABLE, TRUE);
	RI->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	RI->Commit();

	pDev->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	pDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	pDev->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);
	pDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	pDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	pDev->SetFVF(Billboard3D::FVF);

	std::list<ProgressBar3D*>::iterator it;   //&& modify by pyj at 20100731
	for (it = m_progressBar3Ds.begin(); it != m_progressBar3Ds.end(); ++it)
	{
        if( *it )
		    (*it)->Render();
	}

	// Çå³ýFVF
	RI->SetTexture( 0, 0 );
	RI->SetFVF(0);
	RI->Commit();
}

void ProgressBar3DManager::Destroy()
{

}

void ProgressBar3DManager::AddProgressBar3D(ProgressBar3D* v)
{
	m_progressBar3Ds.push_back(v);
}

void ProgressBar3DManager::RemoveProgressBar3D(ProgressBar3D* v)
{
	std::list<ProgressBar3D*>::iterator it = std::find(m_progressBar3Ds.begin(), m_progressBar3Ds.end(), v);

	if(it != m_progressBar3Ds.end())
		m_progressBar3Ds.erase(it);
}