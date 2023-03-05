#include "RTTFont.h"

#include "Font3D.h"
#include "Font3DManager.h"

HRESULT RTTFont::Create(LPDIRECT3DDEVICE9 device, int rectWidth,
					   const TCHAR* font, int fontSize,
					   BOOL bold, BOOL italic)
{
	device_ = device;
	rectWidth_ = rectWidth;
	fontSize_ = fontSize;
	fontIndex_ = Font3DManager::Instance()->GetFontIndex(font, fontSize /** 1.8f*/, bold, italic);
	lineSpace_ = 0;
	CreateVertex();
	
	return S_OK;
}

void RTTFont::Destroy()
{
}

bool RTTFont::Render( bool bNoRefresh /*= false*/ )
{
	if (!visibled_ || !tex_)
		return false;

	// 需要刷新，调用者却不要刷新，直接返回 [10/29/2010 zhangjiayi]
	if( needRefresh_ && bNoRefresh )
		return false;

	bool bRet = false;

	if (needRefresh_)
	{
		bRet = true;
		RenderToTexture(tex_);
		needRefresh_ = false;
	}
	//RenderToScreen();
	if( billboard_ && billboard_->m_pkBillboard )
		billboard_->m_pkBillboard->Render();

	return bRet;
}

HRESULT RTTFont::OnResetDevice(LPDIRECT3DDEVICE9 device)
{
	device_ = device;

	tex_ = Font3DManager::Instance()->GetD3DTexture(text_.c_str(), colors_, rectWidth_, needRefresh_);
	needRefresh_ = true;

	//OnResetDeviceVertex();
	if( billboard_ && billboard_->m_pkBillboard )
		billboard_->m_pkBillboard->SetTexture(tex_);

	return S_OK;
}

HRESULT RTTFont::OnLostDevice()
{
	tex_ = 0;
	return S_OK;
}

#ifdef UNICODE
void RTTFont::SetText(const std::wstring& text)
#else
void RTTFont::SetText(const std::string& text)
#endif
{
	if (text_ != text || colors_ != oldColors_)
	{
		Font3DManager::Instance()->ReleaseD3DTexture(tex_);

		text_ = text;
		oldColors_ = colors_;
		tex_ = Font3DManager::Instance()->GetD3DTexture(text_.c_str(), colors_, rectWidth_, needRefresh_);
		needRefresh_ = true;
		//SetTextureToVertex();
		if( billboard_ && billboard_->m_pkBillboard )
			billboard_->m_pkBillboard->SetTexture(tex_);
	}
}

void RTTFont::SetColor(const D3DXCOLOR& col, int index)
{
	if (index >= colors_.size())
		colors_.insert(colors_.end(), index - colors_.size() + 1, D3DXCOLOR());

	if (colors_[index] != col)
		colors_[index] = col;
}

void RTTFont::ClearColor()
{
	oldColors_ = colors_;
	colors_.clear();
}

#ifdef UNICODE
void RTTFont::RenderToTexture(LPDIRECT3DTEXTURE9 tex)
#else
void RTTFont::RenderToTexture(LPDIRECT3DTEXTURE9 tex)
#endif
{
	Font3DManager::RenderTargetInfo* rti = Font3DManager::Instance()->GetRenderTargetInfo(rectWidth_);
	if (!rti)
		return;

	int nColorSize = colors_.size();

	if( nColorSize <= 0 )
		return;

	RECT rc;
	SetRect(&rc, 0, 0, rectWidth_, rectWidth_);

	LPDIRECT3DSURFACE9 RT = 0;
	HRESULT hr = rti->rt->GetSurfaceLevel(0, &RT);
	assert(hr == S_OK && "GetSurfaceLevel");

	// 得到Main RenderTarget
	IDirect3DSurface9* oldRT = 0;
	IDirect3DSurface9* oldDS = 0;
	hr = device_->GetRenderTarget(0, &oldRT);
	if( hr != D3D_OK )
		return;
	hr = device_->GetDepthStencilSurface(&oldDS);
	if( hr != D3D_OK )
		return;
	// 设置字体贴图RenderTarget，为了把字渲染到贴图上
	hr = device_->SetRenderTarget(0, RT);
	assert(hr == S_OK && "SetRenderTarget");

	LPDIRECT3DSURFACE9 ds = Font3DManager::Instance()->GetD3DDepthSurface();
	hr = device_->SetDepthStencilSurface(ds);
	assert(hr == S_OK && "SetDepthStencilSurface");

	D3DXCOLOR c;
	c.r = c.g = c.b = 0.3f;
	c.a = 0.0f;

	device_->Clear(0L, NULL, D3DCLEAR_TARGET, c, 1.0f, 0L);

#ifdef UNICODE
	std::vector<std::wstring> texts;
#else
	std::vector<std::string> texts;
#endif
	std::string::size_type s = 0;
	std::string::size_type p = 0;

	while ((p = text_.find('\n', s)) != std::string::npos)
	{
		texts.push_back(text_.substr(s, p - s));
		s = p + 1;
	}
	texts.push_back(text_.substr(s));

	//
	// 渲染字导RenderTarget上
	//
	RECT rect = rc;
	rect.top += 2;		

	int nOldIdx = FontRender::getFontRender()->GetDefaultRendererIdx();
	FontRender::getFontRender()->ClearRender( FontRender::EFR_THIRD );
	FontRender::getFontRender()->SetDefaultRendererIdx( FontRender::EFR_THIRD );

	for (std::string::size_type i = 0; i < texts.size(); ++i)
	{
		int j = min( i, nColorSize - 1 );
		RenderTextNew(texts[i].c_str(), colors_[j], rect);
		rect.top += /*fontSize_*/FontSystem::GetFontHeight( fontIndex_ ) + lineSpace_;
	}
	IRenderer* r = GetEngine()->GetRenderer();
	r->SetRenderState(D3DRS_LIGHTING, FALSE);
	r->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE );
	r->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE );
	r->SetRenderState(D3DRS_FOGENABLE, FALSE);
	r->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	r->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE );
	r->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE );
	r->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 0);
	r->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	r->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT); 
	r->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); 
	//r->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1 );
	r->SetTextureStageState(0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1); //之前是D3DTOP_MODULATE   alpha混合在ControlImageList上面显示数字会有问题, 所以选为Font纹理的alpha值
	r->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	
	r->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);  //之前是D3DTA_CURRENT
	r->SetTextureStageState(0, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	r->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	r->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);

	FontSystem::DoRender( FontRender::EFR_THIRD, true );
	FontRender::getFontRender()->SetDefaultRendererIdx( (FontRender::EFontRenders)nOldIdx );	
	//
	// 拷贝字到贴图上
	//
	device_->GetRenderTargetData(RT, rti->offscreenSurf);

	D3DSURFACE_DESC sd;
	tex->GetLevelDesc(0, &sd);

	D3DLOCKED_RECT offRC, srcRC;
	hr = rti->offscreenSurf->LockRect(&offRC, 0, D3DLOCK_READONLY);
	if (SUCCEEDED(hr))
	{
		hr = tex->LockRect(0, &srcRC, 0, 0);
		if (SUCCEEDED(hr))
		{
			memcpy(srcRC.pBits, offRC.pBits, sd.Height * srcRC.Pitch);
			tex->UnlockRect(0);
		}
		rti->offscreenSurf->UnlockRect();
	}

	//
	// Release
	//
	device_->SetDepthStencilSurface(oldDS);
	device_->SetRenderTarget(0, oldRT);

	RT->Release();
	oldDS->Release();
	oldRT->Release();
}

void RTTFont::RenderTextNew(const TCHAR* text, const D3DXCOLOR& color, const RECT& rc)
{
	if( fontIndex_ == -1 )
		return;

	if( customShadow_ )
		FontSystem::DrawTextShadow( text, const_cast<LPRECT>(&rc), DT_NOCLIP|DT_TOP|DT_CENTER|DT_WORDBREAK, color, fontShadow_, 1, fontIndex_ );
	else
		FontSystem::DrawTextRGB( text, const_cast<LPRECT>(&rc),  DT_NOCLIP|DT_TOP|DT_CENTER|DT_WORDBREAK, color, fontIndex_ );
}
