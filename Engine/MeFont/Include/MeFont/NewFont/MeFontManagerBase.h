/************************************************************************
filename: 	FontManagerBas.h
created:	9/1/2010
author:		Yejun.pi

purpose:	将Mefont 和 FontManager统一起来
************************************************************************/

#pragma once

#include "Dxsdk/d3d9.h"
#include "Dxsdk/d3dx9core.h"
#include <string>

class FontManagerBase
{
public: /// device related functions

	/// create device
	virtual void CreateDevice( IDirect3DDevice9* pd3dDevice ) = 0;

	/// reset device
	virtual void ResetDevice( float fFontScale = 1.f ) = 0;

	/// lost devices
	virtual void LostDevice() = 0;

	/// destroy resources
	virtual void DestroyDevice() = 0;

public: /// create & draw functions

	virtual int	CreateFont( LPCSTR	pFaceName,
		INT		Height,
		UINT	Width = 0,
		UINT	Weight = FW_NORMAL,
		UINT	MipLevels = 1,
		BOOL	Italic = FALSE,
		DWORD	CharSet = DEFAULT_CHARSET,
		DWORD	OutputPrecision = OUT_DEFAULT_PRECIS,
		DWORD	Quality = DEFAULT_QUALITY,
		DWORD	PitchAndFamily = DEFAULT_PITCH|FF_DONTCARE,
		HDC		*phDC = NULL )=0;
	
	/// 
	virtual void DrawText( const char* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
        const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex = 0,
		bool bZ = false,
        bool bUseColorizedFont = false ) = 0;

	virtual void DrawTextW( const WCHAR* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
        const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex = 0,
		bool bZ = false,
        bool bUseColorizedFont = false ) = 0;

	virtual void DrawText( const char* pString,
		int nX,
		int nY,
		DWORD Format,
		D3DCOLOR Color,
        const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex = 0,
		bool bZ = false,
        bool bUseColorizedFont = false ) = 0;

	virtual void DrawTextHighBorder( const char* pString,
		INT X, INT Y,
		DWORD Format,
		D3DCOLOR Color,
        const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex = 0,
        bool bUseColorizedFont = false ) = 0;	

	virtual void DrawTextHighBorderW( const WCHAR* pString,
		INT X, INT Y,
		DWORD Format,
		D3DCOLOR Color,
		const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex = 0,
		bool bUseColorizedFont = false ) = 0;	

	virtual void DrawTextHighBorder(
		const char* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
        const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex ,
		D3DCOLOR BorderColor,   // 边框颜色
		int BorderWidth,        // 边框宽度
		bool bUseColorizedFont = false ) = 0;
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
		) = 0;

	virtual void DrawTextDirect( const char* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
        const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex = 0, 
		bool bBorder = false,
        bool bUseColorizedFont = false ) = 0;
	virtual void DrawTextDirectW( const WCHAR* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
		const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex = 0, 
		bool bBorder = false,
		bool bUseColorizedFont = false ) = 0;

public: /// other functions

	virtual void UseFontShadow(bool v) = 0;

	virtual void SetWorldMatrix( const D3DXMATRIX& matWorld ) = 0;

	virtual void SetViewMatrix( const D3DXMATRIX& matView ) = 0 ;

	virtual void SetGlobalZ( float fZ, int nFontIndex ) = 0;

	virtual float GetGlobalZ( int nFontIndex) = 0;

	virtual void SetFontScale( float fFontScale ) = 0;

	virtual float GetFontScale() = 0;

	virtual int GetTextWidth(const int& nFontIndex, const std::wstring &text, int startCharIndex, int endCharIndex, bool bTrail) = 0;

	virtual float GetFontHeight( int nFontIndex ) = 0;

	virtual void GetEndIndexByWidth(
		const int& nFontIndex,
		const std::wstring &text, 
		int startCharIndex,
		int showWidth, 
		int& endCharIndex, 
		bool& bIsEnd) = 0;

	virtual void InitAllFontScale( float fScale ) = 0;

	virtual float GetRealHeight( int nFontIndex ) = 0;

	virtual int GetFontWidth( int nFontIndex ) = 0;

	virtual float GetFontRealScale(int nFontIndex) = 0;

	virtual void SaveAllFontTexture() = 0;

	virtual void BeginRender() = 0;
	virtual void EndRender() = 0;

	virtual	void SetSupportSpecialChar(bool bFlag) = 0;
};