/************************************************************************
filename: 	FontManager.h
created:	8/20/2010
author:		Yejun.pi

purpose:	manage font, create font, destory font, ready font texture and so on
************************************************************************/


#ifndef _FontManager_h_
#define _FontManager_h_

#include "MeFontCommon.h"
#include "MeFont/NewFont/Font.h"
#include "MeFont/NewFont/MeFontManagerBase.h"
#include <MeUtility/Singleton.h>

namespace More
{

	struct SFontData
	{
		UINT   fontId;   
		UINT   fontSize;
		char   fileName[32];    // 只取文件名，如"../data/font/simhei.ttf", 只取simhei
		Font*  pFont;
	};

	//class Font;
	class MeFTFontManager : public Singleton<MeFTFontManager>, public FontManagerBase
	{
	public:
		virtual ~MeFTFontManager();

		virtual int	MeFTFontManager::CreateFont( LPCSTR	pFaceName,
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

		virtual Font* getFont( const UINT& fontId );


		virtual void destroyAllFonts(void);

		virtual void destroyFont( const UINT& fontId );

		virtual void MeFTFontManager::prepareFontTexture(void);

		Font* GetDefaultFont(int nFontIndex);

		//打印所有的文字纹理
		virtual void SaveAllFontTexture();

		virtual void DrawText( const char* pString, 
			RECT* pRect, 
			DWORD Format, 
			D3DCOLOR Color, 
            const D3DCOLOR ( &dwVtColorArray )[4],
			unsigned int nFontIndex,
			bool bZ,
            bool bUseColorizedFont = false );

		virtual void DrawTextW( const WCHAR* pString, 
			RECT* pRect, 
			DWORD Format, 
			D3DCOLOR Color, 
            const D3DCOLOR ( &dwVtColorArray )[4],
			unsigned int nFontIndex, 
			bool bZ,
            bool bUseColorizedFont = false );

		virtual void DrawText( const char* pString, 
			INT X, INT Y, 
			DWORD Format, 
			D3DCOLOR Color, 
            const D3DCOLOR ( &dwVtColorArray )[4],
			unsigned int nFontIndex ,
			bool bZ,
            bool bUseColorizedFont = false );

		virtual void DrawTextHighBorder(
			const char* pString,
			RECT* pRect,
			DWORD Format,
			D3DCOLOR Color,
            const D3DCOLOR ( &dwVtColorArray )[4],
			unsigned int nFontIndex ,
			D3DCOLOR BorderColor,   // 边框颜色
			int BorderWidth=1,      // 边框宽度
            bool bUseColorizedFont = false
			);
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
			);

		virtual void BeginRender();
		virtual void EndRender(){}


		virtual UiRender* MeFTFontManager::getRender();

	public:
		virtual int GetTextWidth(const int& nFontIndex, const std::wstring &text, int startCharIndex, int endCharIndex, bool bTrail);

		virtual float GetFontHeight( int nFontIndex );

		virtual void GetEndIndexByWidth(const int& nFontIndex,const std::wstring &text, int startCharIndex,int showWidth, int& endCharIndex, bool& bIsEnd);

		virtual void ResetDevice(float fScale);

		virtual void InitAllFontScale(float fScale);

		virtual float MeFTFontManager::GetRealHeight( int nFontIndex );

		virtual int MeFTFontManager::GetFontWidth( int nFontIndex );

		virtual float MeFTFontManager::GetFontRealScale(int nFontIndex);

		virtual void SetGlobalZ(float z, int nFontIndex);

		virtual	void SetSupportSpecialChar(bool bFlag) {m_bSupportSpecialChar = bFlag;}

	public:
		//*****************************************************************************
		virtual void DrawTextHighBorder( const char* pString,
			INT X, INT Y,
			DWORD Format,
			D3DCOLOR Color,
            const D3DCOLOR ( &dwVtColorArray )[4],
			unsigned int nFontIndex = 0,
            bool bUseColorizedFont = false );

		virtual void DrawTextHighBorderW( const WCHAR* pString,
			INT X, INT Y,
			DWORD Format,
			D3DCOLOR Color,
			const D3DCOLOR ( &dwVtColorArray )[4],
			unsigned int nFontIndex = 0,
			bool bUseColorizedFont = false );

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

		virtual void CreateDevice( IDirect3DDevice9* pd3dDevice ){ };

		virtual void LostDevice(){  };

		virtual void DestroyFontManager();

		virtual void UseFontShadow(bool v){   };

		virtual void SetWorldMatrix( const D3DXMATRIX& matWorld ){    };

		virtual void SetViewMatrix( const D3DXMATRIX& matView ){   } ;

		virtual float GetGlobalZ(int nFontIndex);

		virtual void SetFontScale( float fFontScale ){    };

		virtual float GetFontScale(){  return 0; };

		virtual void DestroyDevice();


		bool IsSupportSpecialChar() const { return m_bSupportSpecialChar; }

		//***************************************************************************************

	private:

		typedef	std::map<UINT, SFontData*> FontRegistry;
		typedef FontRegistry::iterator FontRegistryIter;
		typedef FontRegistry::const_iterator FontRegistryConstIter;

		FontRegistry			d_fonts;

		char				    d_fontDir[MAX_PATH];	//保存字体文件的目录		

		ulong					d_fontId_counter;


		FontRegistry			d_defaultFonts;			//这里的key用默认字体的Index
		bool					m_bSupportSpecialChar;

		float					d_fScale;			   // 保存ui的缩放比例, 这个并不等于文字的缩放比例.

		struct FontManagerImplData;
		struct FontImplData;
		FontManagerImplData*	d_implData;

	protected:
		friend class Singleton<MeFTFontManager>;
		MeFTFontManager();
	};

}

#endif