/************************************************************************
	filename: FontSystem.h
	author:		Yejun.pi
	
	purpose:
	modify by pyj at 20100827
	为了最小的改动原有的系统, 所以只对这个文件做修改, 由于文件名已与它的功能不是很
	相符, 所以修改原来的文件名FontManager为FontSystem, 因为FontManager已经存在, 
	而且这个文件的功能应该是在FontManager之上.
	修改bIsUseNewFont=false; 使用 DxFont来绘制文字.
	为true则使用FreeType来绘制文字.

************************************************************************/

#ifndef _FontSystem_h_
#define _FontSystem_h_

#include "NewFont/MeFontCommon.h"
#include "NewFont/MeFontRender.h"

namespace FontSystem
{
	void InitFontManager(bool bIsUseNewFont=true);
	
	//*******************************************************************************
	int	CreateFont( LPCSTR	pFaceName,
					INT		Height,
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

	void DrawTextShadow( const char* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
		D3DCOLOR SColor,
		int nShadowBorder,
		unsigned int nFontIndex = 0,
		bool bZ = false );

	void DrawText( const char* pString,
					int nX,
					int nY,
					DWORD Format,
					D3DCOLOR Color,
					unsigned int nFontIndex = 0,
					bool bZ = false );

	void SaveAllFontTexture();
	
	//*****************************************************************************
	void DrawTextHighBorder( const char* pString,
							INT X, INT Y,
							DWORD Format,
							D3DCOLOR Color,
							unsigned int nFontIndex = 0 );

	void DrawTextHighBorderW( const WCHAR* pString,
		INT X, INT Y,
		DWORD Format,
		D3DCOLOR Color,
		unsigned int nFontIndex = 0 );

	void CreateDevice( IDirect3DDevice9* pd3dDevice );

	void ResetDevice( float fFontScale = 1.f );

	void LostDevice();

	void DestroyFontManager();

	void DrawTextDirect( const char* pString,
							RECT* pRect,
							DWORD Format,
							D3DCOLOR Color,
							unsigned int nFontIndex = 0, 
							bool bBorder = false );

	void DrawTextDirectW( const WCHAR* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
		unsigned int nFontIndex = 0, 
		bool bBorder = false );

	void UseFontShadow(bool v);

	void SetWorldMatrix( const D3DXMATRIX& matWorld );

	void SetViewMatrix( const D3DXMATRIX& matView ) ;

	void SetGlobalZ( float fZ, int nFontIndex );

	float GetGlobalZ( int nFontIndex);

	void SetFontScale( float fFontScale );

	float GetFontScale();

	bool IsUseNewFont();

	//***************************************************************************************
	int GetTextWidth(const int& nFontIndex, const std::wstring &text, int startCharIndex, int endCharIndex, bool bTrail);
	
	float GetFontHeight( const int& nFontIndex );

	void GetEndIndexByWidth(
							const int& nFontIndex,
							const std::wstring &text, 
							int startCharIndex,
							int showWidth, 
							int& endCharIndex, 
							bool& bIsEnd);

	void InitAllFontScale( float fScale );

	float GetRealHeight( int nFontIndex );

	int GetFontWidth( int nFontIndex );

	float GetFontRealScale(int nFontIndex);

	void BeginRender();
	void DoRender( FontRender::EFontRenders eIdx, bool bOuterStates = false );
	void ClearRender( FontRender::EFontRenders eIdx );
	void EndRender();
	
    //------------ 彩色字接口 (只支持新字体)      added by zhuomeng.hu  [4/11/2011] ---------
    void DrawColorizedText(
        const char* pString,
        RECT* pRect,
        DWORD Format,
        const D3DCOLOR ( &dwVtColor )[4],
        unsigned int nFontIndex = 0,
        bool bZ = false
        );

    void DrawColorizedText(
        const char* pString,
        int nX,
        int nY,
        DWORD Format,
        const D3DCOLOR ( &dwVtColor )[4],
        unsigned int nFontIndex = 0,
        bool bZ = false
        );

    void DrawColorizedTextW(
        const WCHAR* pString,
        RECT* pRect,
        DWORD Format,
        const D3DCOLOR ( &dwVtColor )[4],
        unsigned int nFontIndex = 0,
        bool bZ = false
        );

    void DrawColorizedShadowText(
        const char* pString,
        RECT* pRect,
        DWORD Format,
        const D3DCOLOR ( &dwVtColor )[4],
        D3DCOLOR SColor,
        int nShadowBorder,
        unsigned int nFontIndex = 0,
        bool bZ = false
        );

    void DrawColorizedBorderText(
        const char* pString,
        INT X, INT Y,
        DWORD Format,
        const D3DCOLOR ( &dwVtColor )[4],
        unsigned int nFontIndex = 0
        );
    //---------------------------------------------------------------------------------------
	void SetSupportSpecialChar(bool bFlag) ;

}


#endif