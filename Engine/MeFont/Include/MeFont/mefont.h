#pragma once
#include <Singleton.h>
#include "MeFont/NewFont/MeFontManagerBase.h"

class FontManager:public FontManagerBase, public Singleton<FontManager>
{
	// 同D3D9接口,在里面进行相应调用
public:
	virtual void	CreateDevice( IDirect3DDevice9* pd3dDevice );
	virtual void	ResetDevice( float fFontScale = 1.f );
	virtual void	LostDevice();
	virtual void	DestroyDevice();

	virtual float GetFontHeight( int nFontIndex );

	virtual int GetFontWidth( int nFontIndex );

public:
	virtual int	CreateFont( LPCSTR	pFaceName,
					INT	Height,
					UINT	Width = 0,
					UINT	Weight = FW_NORMAL,
					UINT	MipLevels = 1,
					BOOL	Italic = FALSE,
					DWORD	CharSet = DEFAULT_CHARSET,
					DWORD	OutputPrecision = OUT_DEFAULT_PRECIS,
					DWORD	Quality = DEFAULT_QUALITY,
					DWORD	PitchAndFamily = DEFAULT_PITCH|FF_DONTCARE,
					HDC		*phDC = NULL );

	virtual void	DrawText( const char* pString,
						RECT* pRect,
						DWORD Format,
						D3DCOLOR Color,
                        const D3DCOLOR ( &dwVtColorArray )[4],
						unsigned int nFontIndex = 0,
                        bool bZ = false,
                        bool bUseColorizedFont = false );

	virtual void	DrawTextW( const WCHAR* pString,
						RECT* pRect,
						DWORD Format,
						D3DCOLOR Color,
                        const D3DCOLOR ( &dwVtColorArray )[4],
						unsigned int nFontIndex = 0, bool bZ = false,
                        bool bUseColorizedFont = false );

	virtual void	DrawText( const char* pString,
						INT X, INT Y,
						DWORD Format,
						D3DCOLOR Color,
                        const D3DCOLOR ( &dwVtColorArray )[4],
						unsigned int nFontIndex = 0,
                        bool bZ = false,
                        bool bUseColorizedFont = false );

	virtual void	DrawTextHighBorder( const char* pString,
								INT X, INT Y,
								DWORD Format,
								D3DCOLOR Color,
                                const D3DCOLOR ( &dwVtColorArray )[4],
								unsigned int nFontIndex = 0,
                                bool bUseColorizedFont = false );

	virtual void DrawTextHighBorder(
		const char* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
        const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex ,
		D3DCOLOR BorderColor,   // 边框颜色
		int BorderWidth,        // 边框宽度
        bool bUseColorizedFont = false 
		){}
	virtual void DrawTextHighBorderW( const WCHAR* pString,
		INT X, INT Y,
		DWORD Format,
		D3DCOLOR Color,
		const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex = 0,
		bool bUseColorizedFont = false ) ;	
	virtual void DrawTextHighBorderW(
		const WCHAR* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
		const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex ,
		D3DCOLOR BorderColor,   // 边框颜色
		int BorderWidth=1,         // 边框宽度
		bool bUseColorizedFont = false
		) {}

	virtual void DrawTextDirect( const char* pString,
						RECT* pRect,
						DWORD Format,
						D3DCOLOR Color,
                        const D3DCOLOR ( &dwVtColorArray )[4],
						unsigned int nFontIndex = 0,
                        bool bBorder = false,
                        bool bUseColorizedFont = false );
	virtual void DrawTextDirectW( const WCHAR* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
		const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex = 0,
		bool bBorder = false,
		bool bUseColorizedFont = false );

	virtual void BeginRender(){}
	virtual void EndRender(){}

	virtual void UseFontShadow(bool v) { m_bUseShadow = v; }
	virtual void SetWorldMatrix( const D3DXMATRIX& matWorld ){ m_matWorld = matWorld; }
	virtual void SetViewMatrix( const D3DXMATRIX& matView ) { m_matView = matView; }
	virtual void SetGlobalZ( float fZ,int nFontIndex=0 ){ m_fGlobalZ = fZ; }
	virtual float GetGlobalZ( int nFontIndex){ return m_fGlobalZ; }
	virtual void SetFontScale( float fFontScale ){ m_fFontScale = fFontScale; }
	virtual float GetFontScale(){ return m_fFontScale; }

public:
	//*******************************************************************************
	virtual int GetTextWidth(const int& nFontIndex, const std::wstring &text, int startCharIndex, int endCharIndex, bool bTrail)
	{ return 0; }

	virtual void GetEndIndexByWidth(
		const int& nFontIndex,
		const std::wstring &text, 
		int startCharIndex,
		int showWidth, 
		int& endCharIndex, 
		bool& bIsEnd){  }

	virtual void InitAllFontScale( float fScale ){  };

	virtual float GetRealHeight( int nFontIndex );

	virtual float GetFontRealScale(int nFontIndex){ return 0; };

	virtual void SaveAllFontTexture(){  };

	virtual	void SetSupportSpecialChar(bool bFlag) {;}
	//*******************************************************************************

private:
	IDirect3DDevice9*		m_pd3dDevice;
	std::vector<ID3DXFont*>	m_vtFont;
	bool m_bUseShadow;
	LPD3DXSPRITE			m_pSprite;
	float					m_fFontScale;
	D3DXMATRIX				m_matWorld;
	D3DXMATRIX				m_matView;
	float					m_fGlobalZ;

public:
	FontManager(void);
	virtual ~FontManager(void);
};