#pragma once
#include "Dxsdk/d3d9.h"
#pragma warning(disable : 4995)
#include <string>
#pragma warning(default : 4995)
#include "Billboard3D.h"
#include "Cfg.h"

class RTTFont : public MeCommonAllocObj<RTTFont>
{
public:
	enum
	{
		RTT_TEX_WIDTH = 256
	};
	enum ERTTFontType
	{
		ERTT_2D,
		ERTT_3D,
		ERTT_Count
	};
public:
	RTTFont() : device_(0), tex_(0), needRefresh_(false), fontIndex_(-1),
		customShadow_( false )
	{
	}

	virtual ~RTTFont()
	{
		//Destroy();
	}

	virtual HRESULT OnResetDevice(LPDIRECT3DDEVICE9 device);

	virtual HRESULT OnLostDevice();

	virtual void Destroy();

	virtual HRESULT Create(LPDIRECT3DDEVICE9 device, int rectWidth,
		const TCHAR* font, int fontSize,
		BOOL bold = false, BOOL italic = false);

	/// bNoRefresh用来强制不刷新贴图
	virtual bool Render( bool bNoRefresh = false );

#ifdef UNICODE
	void SetText(const std::wstring& text);
	const std::wstring& GetText() { return text_; }
#else
	void SetText(const std::string& text);
	const std::string& GetText() { return text_; }
#endif

	void SetColor(const D3DXCOLOR& col, int index);
	int GetColorsCount() const{ return (int)colors_.size(); }
	void ClearColor();



	virtual void SetCamera(MeCamera* camera)
	{
		if( billboard_ &&
			billboard_->m_pkBillboard )
			billboard_->m_pkBillboard->SetCamera(camera);
	}

	virtual  void SetPosition(const D3DXVECTOR3& pos)
	{
		if( billboard_ &&
			billboard_->m_pkBillboard )
			billboard_->m_pkBillboard->SetPosition(pos);
	}

	virtual const D3DXVECTOR3& GetPosition()
	{
		if( billboard_ &&
			billboard_->m_pkBillboard )
			return billboard_->m_pkBillboard->GetPosition();

		static D3DXVECTOR3 s_vec = D3DXVECTOR3(0,0,0);
		return s_vec;
	}

	virtual const D3DXMATRIXA16& GetWorld()
	{
		if( billboard_ &&
			billboard_->m_pkBillboard )
			return billboard_->m_pkBillboard->GetWorld();

		static D3DXMATRIXA16 matWorld ;
		D3DXMatrixIdentity( &matWorld );
		return matWorld;
	}

	virtual void SetScale(const D3DXVECTOR3& scale)
	{
		if( billboard_ &&
			billboard_->m_pkBillboard )
			billboard_->m_pkBillboard->SetScale(scale);
	}

	void SetVisible(bool v)
	{
		visibled_ = v;
	}

	bool IsVisible() { return visibled_; }

	int GetWidth() { return rectWidth_; }

	LPDIRECT3DTEXTURE9 GetD3DTexture() { return tex_; }

	int GetFontIndex() const{ return fontIndex_; }

	void SetCustomShadow( bool bEnable ){ customShadow_ = bEnable; }
	void EnableCustomShadow( const D3DXCOLOR& shadow ){ customShadow_ = true; fontShadow_ = shadow; }
	const D3DXCOLOR& GetCustomShadow() const{ return fontShadow_; }

	ERTTFontType GetType() const{ return eFontType_; }


	void SetLineSpace( int space ){ lineSpace_ = space; }
	int GetLineSpace(){ return lineSpace_; }

protected:
	virtual void CreateVertex() = 0;

	virtual void RenderToTexture(LPDIRECT3DTEXTURE9 tex);
	virtual void RenderTextNew(const TCHAR* text, const D3DXCOLOR& color, const RECT& rc);

	//
	// Fields
	//
	LPDIRECT3DDEVICE9 device_;
	LPDIRECT3DTEXTURE9 tex_;
	typedef std::vector<D3DXCOLOR> Colors;
	Colors colors_;
	Colors oldColors_;
	int rectWidth_;
	int fontSize_;
	int lineSpace_;
	int fontIndex_;
	bool visibled_;
	bool needRefresh_;

	// custom shadow color
	bool customShadow_;
	D3DXCOLOR fontShadow_;

	ERTTFontType eFontType_;

	BillboardItemPtr billboard_;

#ifdef UNICODE
	std::wstring text_;
#else
	std::string text_;
#endif
};
