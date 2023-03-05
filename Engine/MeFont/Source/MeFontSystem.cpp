#include "MeFont/MeFontSystem.h"
#include "MeFont/MeFont.h"
#include "MeFont/NewFont/MeFTFontManager.h"
#include "MeFont/NewFont/MeFontRender.h"

using namespace More;
// bool g_bFontDrawTextWChar = false;

namespace FontSystem
{
	static bool				s_bIsUseNewFont		=		true;        // 在新旧字体之间切换, 调用InitFontManager修改此值
	static FontManagerBase*	s_pFontManager		=		NULL;

	// 此函数的调用在CHeroGame::InitDeviceObjects()中
	void InitFontManager( bool bIsUseNewFont )
	{
		s_bIsUseNewFont=bIsUseNewFont;

		if( bIsUseNewFont )		
		{
			s_pFontManager = MeFTFontManager::Instance();		
			FontRender::getFontRender()->Initialize();
		}
		else
        {
			s_pFontManager= FontManager::Instance();			
        }
	}

	//***********************************************************************************

	int	CreateFont( LPCSTR	pFaceName,
		INT 	Height,
		UINT	Width,
		UINT	Weight,
		UINT	MipLevels,
		BOOL	Italic,
		DWORD	CharSet,
		DWORD	OutputPrecision,
		DWORD	Quality,
		DWORD	PitchAndFamily,
		HDC		*phDC )
	{
		MeScopeProfileFontFun
		return s_pFontManager->CreateFont( pFaceName,
			Height,
			Width,
			Weight,
			MipLevels,
			Italic,
			CharSet,
			OutputPrecision,
			Quality,
			PitchAndFamily,
			phDC );
	}

	void DrawText( const char* pString, RECT* pRect,
		DWORD Format, D3DCOLOR Color,
		unsigned int nFontIndex, bool bZ /*= false*/ )
	{
		MeScopeProfileFontFun
		D3DCOLOR dwVtColor[4];
// 		if( g_bFontDrawTextWChar )
// 		{
// // 			std::wstring wString;
// 			const int nWLen = 10240;
// 			static WCHAR wChar[nWLen];
// 			wChar[0] = L'\0';
// // 			int nBufSize = MultiByteToWideChar(CP_ACP,0,pString,-1,NULL,0); 
// // 			wchar_t* wsBuf = MeDefaultNew wchar_t[nBufSize];
// // 			if( wsBuf )
// 			{
// 				MultiByteToWideChar(CP_ACP,0,pString,-1,wChar,nWLen - 1); 
// // 				wString = wsBuf;
// // 				delete []wsBuf;
// // 				wsBuf = NULL;
// 
// 				s_pFontManager->DrawTextW( wChar, pRect, Format, Color,dwVtColor, nFontIndex, bZ );
// 			}
// 		}
// 		else
        {
			s_pFontManager->DrawText( pString, pRect, Format, Color, dwVtColor, nFontIndex, bZ );
        }
	}

	void DrawTextW( const WCHAR* pString, RECT* pRect,
		DWORD Format, D3DCOLOR Color,
		unsigned int nFontIndex, bool bZ /*= false*/  )
	{
		MeScopeProfileFontFun

        // 为兼容彩色字接口
        D3DCOLOR dwVtColor[4];
		s_pFontManager->DrawTextW( pString, pRect, Format, Color, dwVtColor, nFontIndex, bZ );
	}

	void DrawText( const char* pString,
		int nX, int nY,
		DWORD Format, D3DCOLOR Color,
		unsigned int nFontIndex , bool bZ /*= false*/ )
	{
		MeScopeProfileFontFun
		D3DCOLOR dwVtColor[4];
// 		if( g_bFontDrawTextWChar )
// 		{
// 			const int nWLen = 10240;
// 			static WCHAR wChar[nWLen];
// 			wChar[0] = L'\0';
// 			MultiByteToWideChar(CP_ACP,0,pString,-1,wChar,nWLen -1); 
// 
// 				RECT rc = {nX,nY,0,0};
// 				s_pFontManager->DrawTextW( wChar, &rc, Format, Color,dwVtColor, nFontIndex, bZ );
// 		}
// 		else
        {
			s_pFontManager->DrawText( pString, nX, nY, Format, Color, dwVtColor, nFontIndex, bZ );
        }
	}

	void DrawTextShadow( const char* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
		D3DCOLOR SColor,
		int nShadowBorder,
		unsigned int nFontIndex /*= 0*/,
		bool bZ /*= false*/ )
	{
		MeScopeProfileFontFun

        // 为兼容彩色字接口
        D3DCOLOR dwVtColor[4];
		s_pFontManager->DrawTextHighBorder( pString, pRect, Format, Color, dwVtColor, nFontIndex, SColor, nShadowBorder );
	}

	//**************************************************************
	void DrawTextRGB( const char* pString, RECT* pRect,
		DWORD Format, D3DCOLOR Color,
		unsigned int nFontIndex, bool bZ /*= false*/  )
	{
		MeScopeProfileFontFun
		D3DCOLOR dwVtColor[4];
// 		if( g_bFontDrawTextWChar )
// 		{
// 			const int nWLen = 10240;
// 			static WCHAR wChar[nWLen];
// 			wChar[0] = L'\0';
// 			MultiByteToWideChar(CP_ACP,0,pString,-1,wChar,nWLen - 1); 
// 
// 			s_pFontManager->DrawTextW( wChar, pRect, Format, Color,dwVtColor, nFontIndex, bZ );
// 		}
// 		else
        {
			s_pFontManager->DrawText( pString, pRect, Format, Color, dwVtColor, nFontIndex, bZ );
        }
	}

	void DrawTextHighBorder( const char* pString,
		INT X, INT Y,
		DWORD Format,
		D3DCOLOR Color,
		unsigned int nFontIndex )
	{
		MeScopeProfileFontFun
        // 为兼容彩色字接口
        D3DCOLOR dwVtColor[4];
		s_pFontManager->DrawTextHighBorder( pString, X, Y, Format, Color, dwVtColor, nFontIndex );
	}

	void DrawTextHighBorderW( const WCHAR* pString, INT X, INT Y, DWORD Format, D3DCOLOR Color, unsigned int nFontIndex /*= 0 */ )
	{
		MeScopeProfileFontFun

			// 为兼容彩色字接口
		D3DCOLOR dwVtColor[4];
		s_pFontManager->DrawTextHighBorderW(  pString,
			X,Y, Format,
			Color, dwVtColor,nFontIndex );

	}

	void CreateDevice( IDirect3DDevice9* pd3dDevice )
	{
		s_pFontManager->CreateDevice( pd3dDevice );
	}

	void ResetDevice( float fFontScale )
	{
		s_pFontManager->ResetDevice(fFontScale);
	}

	void LostDevice()
	{
		s_pFontManager->LostDevice();
	}

	void DestroyFontManager()
	{
		s_pFontManager->DestroyDevice();
		FontManager::Release();
		MeFTFontManager::Release();
		s_pFontManager = 0;
	}

	void DrawTextDirect( 
		const char* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
		unsigned int nFontIndex , 
		bool bBorder )
	{
        // 为兼容彩色字接口
        D3DCOLOR dwVtColor[4];
		s_pFontManager->DrawTextDirect(pString, pRect, Format, Color, dwVtColor, nFontIndex, bBorder );
	}

	void DrawTextDirectW( 
		const WCHAR* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
		unsigned int nFontIndex , 
		bool bBorder )
	{
		D3DCOLOR dwVtColor[4];
		s_pFontManager->DrawTextDirectW(pString, pRect, Format, Color,dwVtColor, nFontIndex, bBorder);
	}

	void UseFontShadow( bool v )
	{
		s_pFontManager->UseFontShadow( v );
	}

	void SetWorldMatrix( const D3DXMATRIX& matWorld )
	{
		s_pFontManager->SetWorldMatrix( matWorld );
	}

	void SetViewMatrix( const D3DXMATRIX& matView ) 
	{
		s_pFontManager->SetViewMatrix( matView );
	}

	void SetGlobalZ( float fZ, int nFontIndex )
	{
		s_pFontManager->SetGlobalZ(fZ,nFontIndex);
	}

	float GetGlobalZ( int nFontIndex )
	{
		return s_pFontManager->GetGlobalZ( nFontIndex );
	}

	void SetFontScale( float fFontScale )
	{
		return s_pFontManager->SetFontScale( fFontScale );
	}

	float GetFontScale()
	{
		return s_pFontManager->GetFontScale();
	}

	void SaveAllFontTexture()
	{
		return s_pFontManager->SaveAllFontTexture();
	}

	bool IsUseNewFont()
	{
		return s_bIsUseNewFont;
	}

	//*********************************************************************************************

	int GetTextWidth( const int& nFontIndex, const std::wstring &text, const int startCharIndex, int endCharIndex, bool bTrail )
	{
		return s_pFontManager->GetTextWidth( nFontIndex, text, startCharIndex, endCharIndex, bTrail );
	}

	float GetFontHeight( const int& nFontIndex )
	{
		return s_pFontManager->GetFontHeight( nFontIndex );
	}

	void GetEndIndexByWidth(
		const int& nFontIndex,
		const std::wstring &text, 
		int startCharIndex,
		int showWidth, 
		int& endCharIndex, 
		bool& bIsEnd )
	{
		s_pFontManager->GetEndIndexByWidth( nFontIndex, text, startCharIndex, showWidth, endCharIndex, bIsEnd );
	}

	void InitAllFontScale( float fScale )
	{
		s_pFontManager->InitAllFontScale( fScale );
	}

	float GetRealHeight( int nFontIndex )
	{		
		return s_pFontManager->GetRealHeight( nFontIndex );
	}

	int GetFontWidth( int nFontIndex )
	{
		return s_pFontManager->GetFontWidth( nFontIndex );
	}

	float GetFontRealScale( int nFontIndex )
	{
		return s_pFontManager->GetFontRealScale( nFontIndex );
	}

	void BeginRender()
	{
		s_pFontManager->BeginRender();
	}

	void EndRender()
	{
		s_pFontManager->EndRender();
	}

	void DoRender( FontRender::EFontRenders eIdx, bool bOuterStates /*= false*/ )
	{
		MeScopeProfileFontFun
		BeginRender();
		FontRender::getFontRender()->DoRender( eIdx, bOuterStates );
		EndRender();
	}

	void ClearRender( FontRender::EFontRenders eIdx )
	{
		FontRender::getFontRender()->ClearRender( eIdx );
	}

    //------------ 彩色字接口 (只支持新字体)      added by zhuomeng.hu  [4/11/2011] ---------
    void DrawColorizedText( const char* pString, RECT* pRect, DWORD Format, const D3DCOLOR ( &dwVtColor )[4], unsigned int nFontIndex, bool bZ )
    {
        MeScopeProfileFontFun
        s_pFontManager->DrawText( pString, pRect, Format, 0, dwVtColor, nFontIndex, bZ, true );
    }

    void DrawColorizedText( const char* pString, int nX, int nY, DWORD Format, const D3DCOLOR ( &dwVtColor )[4], unsigned int nFontIndex, bool bZ )
    {
        MeScopeProfileFontFun
        s_pFontManager->DrawText( pString, nX, nY, Format, 0, dwVtColor, nFontIndex, bZ, true );
    }

    void DrawColorizedTextW( const WCHAR* pString, RECT* pRect, DWORD Format, const D3DCOLOR ( &dwVtColor )[4], unsigned int nFontIndex, bool bZ )
    {
        MeScopeProfileFontFun
        s_pFontManager->DrawTextW( pString, pRect, Format, 0, dwVtColor, nFontIndex, bZ, true );
    }

    void DrawColorizedShadowText( const char* pString, RECT* pRect, DWORD Format, const D3DCOLOR ( &dwVtColor )[4], D3DCOLOR SColor,
                                  int nShadowBorder, unsigned int nFontIndex, bool bZ )
    {
        MeScopeProfileFontFun
        s_pFontManager->DrawTextHighBorder( pString, pRect, Format, 0, dwVtColor, nFontIndex, SColor, nShadowBorder, true );
    }

    void DrawColorizedBorderText( const char* pString, INT X, INT Y, DWORD Format, const D3DCOLOR ( &dwVtColor )[4], unsigned int nFontIndex )
    {
        MeScopeProfileFontFun
        s_pFontManager->DrawTextHighBorder( pString, X, Y, Format, 0, dwVtColor, nFontIndex, true );
    }
    //---------------------------------------------------------------------------------------

	void SetSupportSpecialChar(bool bFlag) 
	{
		s_pFontManager->SetSupportSpecialChar( bFlag);
	}

}
