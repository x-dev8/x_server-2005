
#pragma once
#include "Dxsdk/d3d9.h"
#include "Dxsdk/d3dx9core.h"
#include <string>

namespace UI_FONT
{
	int	CreateFont( LPCSTR	pFaceName,
					INT&	Height,
					UINT	Width = 0,
					UINT	Weight = FW_NORMAL,
					UINT	MipLevels = 1,
					BOOL	Italic = FALSE,
					DWORD	CharSet = DEFAULT_CHARSET,
					DWORD	OutputPrecision = OUT_DEFAULT_PRECIS,
					DWORD	Quality = DEFAULT_QUALITY,
					DWORD	PitchAndFamily = DEFAULT_PITCH|FF_DONTCARE,
					HDC		*phDC = NULL );

	void DrawText( const char* pString,
					RECT* pRect,
					DWORD Format,
					D3DCOLOR Color,
					unsigned int nFontIndex = 0,
					bool bZ = false );
	void DrawTextW( const WCHAR* pString,
					RECT* pRect,
					DWORD Format,
					D3DCOLOR Color,
					unsigned int nFontIndex = 0,
					bool bZ = false );
	void DrawTextRGB( const char* pString,
					RECT* pRect,
					DWORD Format,
					D3DCOLOR Color,
					unsigned int nFontIndex = 0,
					bool bZ = false );
	void DrawText( const char* pString,
					int nX,
					int nY,
					DWORD Format,
					D3DCOLOR Color,
					unsigned int nFontIndex = 0,
					bool bZ = false );
}
