#include "MeFont/NewFont/MeFTFontManager.h"
#include "MeFont/NewFont/MeFontManager_implData.h"
#include "MeFont/NewFont/MeString.h"
#include "MeFont/NewFont/Font.h"
#include "MeFont/NewFont/MeFont_implData.h"
#include "Me3d/Global.h"
#include "MeFont/NewFont/MeFontRender.h"
#include "tstring.h"

namespace More
{

	MeFTFontManager::MeFTFontManager():
	d_fontId_counter(0),m_bSupportSpecialChar(false),d_fScale(1.0)
	{

		d_implData = new FontManagerImplData;

		if (FT_Init_FreeType(&d_implData->d_ftlib))
		{
			assert("FontManager::FontManager - Failed to initialise the FreeType library.");
		}
	}



	int	MeFTFontManager::CreateFont(   LPCSTR	pFontName,
		INT	Height,
		UINT	Width ,
		UINT	Weight ,
		UINT	MipLevels,
		BOOL	Italic ,
		DWORD	CharSet,
		DWORD	OutputPrecision ,
		DWORD	Quality ,
		DWORD	PitchAndFamily ,
		HDC		*phDC
		)
	{
		// 1. 对字体大小做一个处理，目前oldfont的大小 10~55, 而新字体对应约 8~17.
		// 	float oldScale=((float)Height-8.0f)/(56.0f-8.0f);
		// 	UINT newSize= (oldScale*(17.0f-3.0f)+3.0f);
		int newSize = Height /*/ 4 */* d_fScale;

		// 2. 对字体名字做一个处理
		char* pTemp=const_cast<char*>(pFontName);
		strlwr(pTemp);

		//3. 判断字体文件是否存在
		char fullPathName[MAX_PATH];
		sprintf_s(fullPathName,MAX_PATH-1,"%s\\client\\Font\\%s.ttf",GetRootPath(),pTemp);
		//字体文件不存在, 则指定默认的字体
		if( (_access( fullPathName, 0 )) == -1 )   
		{
			// 尝试ttc
			sprintf_s(fullPathName,MAX_PATH-1,"%s\\client\\Font\\%s.ttc",GetRootPath(),pTemp);
			if( ( _access( fullPathName, 0 ) ) == -1 )
			{
				pTemp="fzlb";
				sprintf_s(fullPathName,MAX_PATH-1,"%s\\client\\Font\\%s.ttf",GetRootPath(),pTemp);
			}			
		}

		//4. 判断字体是否已经创建
		FontRegistry::iterator iter;
		for (iter=d_fonts.begin(); iter!=d_fonts.end(); ++iter)
		{
			if( strcmp(pTemp,iter->second->fileName)==0 && newSize==(iter->second)->fontSize )
			{
				return (iter->second)->fontId;
			}
		}

		//5. 创建字体
		Font* temp = new Font(std::string(pTemp), fullPathName, new Font::FontImplData(d_implData->d_ftlib), newSize, d_fScale);

		if (temp->getFontHeight() > 100)
		{
			assert(false&&"字体大小error");
		}

		SFontData* ps=new SFontData;
		ps->fontId=d_fontId_counter;
		ps->fontSize=newSize;
		ps->pFont=temp;
		strcpy_s( ps->fileName,sizeof(ps->fileName)/sizeof(char),pTemp );

		//6. 将font* 插入到d_fonts
		d_fonts[d_fontId_counter++]=ps;

		return ps->fontId;
	}


	Font* MeFTFontManager::GetDefaultFont( int nFontIndex)
	{
		if (!m_bSupportSpecialChar)
		{
			return NULL;
		}
		FontRegistry::iterator iter = d_defaultFonts.find(nFontIndex);
		if (iter != d_defaultFonts.end())
		{
			return iter->second->pFont;
		}
		//1. 判断字体文件是否存在
		char* pTemp="fzlb";
		char fullPathName[MAX_PATH];
		sprintf_s(fullPathName,MAX_PATH-1,"%s\\client\\Font\\%s.ttf",GetRootPath(),pTemp);

		//3. 创建字体
		Font* temp = new Font(std::string(pTemp), fullPathName, new Font::FontImplData(d_implData->d_ftlib), nFontIndex, d_fScale);

		//4. 将名字插入到d_fontNameList
		SFontData* ps=new SFontData;
// 		ps->fontId=d_fontId_counter;
		ps->fontSize=nFontIndex;
		ps->pFont=temp;
// 		strcpy_s( ps->fileName,sizeof(ps->fileName)/sizeof(char),pTemp );

		//5. 将font* 插入到d_defaultFonts
		d_defaultFonts[nFontIndex]=ps;


		return d_defaultFonts[nFontIndex]->pFont;
	}

	void MeFTFontManager::DestroyDevice()
	{
		DestroyFontManager();
	}

	void MeFTFontManager::DestroyFontManager()
	{
		destroyAllFonts();

		FT_Done_FreeType(d_implData->d_ftlib);
		delete d_implData;

		FontRender::deleteFontRender();
	}

	MeFTFontManager::~MeFTFontManager()
	{
	}

	void MeFTFontManager::destroyAllFonts(void)
	{
		while (!d_fonts.empty())
		{
			destroyFont(d_fonts.begin()->first);
		}
		for(FontRegistry::iterator pos = d_defaultFonts.begin(); pos != d_defaultFonts.end();++pos)
		{
			delete pos->second->pFont;
			delete pos->second;
		}
		d_defaultFonts.clear();
	}

	float MeFTFontManager::GetFontRealScale(int nFontIndex)
	{
		return getFont(nFontIndex)->getRealScale();
	}


	void MeFTFontManager::destroyFont( const UINT& fontId )
	{
		FontRegistry::iterator	pos = d_fonts.find(fontId);

		if (pos != d_fonts.end())
		{
			delete pos->second->pFont;
			delete pos->second;
			d_fonts.erase(pos);

		}
	}


	void MeFTFontManager::prepareFontTexture(void)
	{
		// notify all attached Font objects to prepare font texture.
		FontRegistry::iterator pos = d_fonts.begin(), end = d_fonts.end();

		for (; pos != end; ++pos)
		{
			pos->second->pFont->prepareFontTexture();
		}
	}

	Font* MeFTFontManager::getFont( const UINT& fontId )
	{
		return d_fonts[fontId]->pFont;
	}

	void MeFTFontManager::SaveAllFontTexture()
	{
		FontRegistry::iterator pos = d_fonts.begin(), end = d_fonts.end();

		for (; pos != end; ++pos)
		{
			pos->second->pFont->SaveAllTexture(GetRootPath());
		}
	}

	void MeFTFontManager::DrawText( const char* pString, 
		RECT* pRect, 
		DWORD Format, 
		D3DCOLOR Color, 
        const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex,
		bool bZ,
        bool bUseColorizedFont )
	{
		std::wstring text = Common::_tstring::toWideString( pString );

		getFont(nFontIndex)->DrawShadowText( getRender(),text.c_str(), pRect, Format, Color, dwVtColorArray, nFontIndex, true, bZ, 1, bUseColorizedFont );
	}

	void MeFTFontManager::DrawTextW( const WCHAR* pString, 
		RECT* pRect, 
		DWORD Format, 
		D3DCOLOR Color, 
        const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex, 
		bool bZ,
        bool bUseColorizedFont )
	{
		getFont(nFontIndex)->DrawShadowText(getRender(),pString, pRect, Format, Color, dwVtColorArray, nFontIndex, true, bZ, 1, bUseColorizedFont );
	}

	void MeFTFontManager::DrawText( const char* pString, 
		INT X, INT Y, 
		DWORD Format, 
		D3DCOLOR Color, 
        const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex ,
		bool bZ,
        bool bUseColorizedFont )
	{
		std::wstring text = Common::_tstring::toWideString( pString );

		getFont(nFontIndex)->DrawTextEx(getRender(), text.c_str(), X, Y, Format, Color, dwVtColorArray, nFontIndex, true, bZ, bUseColorizedFont );
	}

	UiRender* MeFTFontManager::getRender()
	{
		if (g_uiRenderCurrFrame!=NULL)
		{
			return g_uiRenderCurrFrame;
		}
		return FontRender::getFontRender()->GetDefaultRenderer();

	}

	void MeFTFontManager::DrawTextHighBorder(
		const char* pString,
		RECT* pRect,
		DWORD Format,
		D3DCOLOR Color,
        const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex ,
		D3DCOLOR BorderColor,   // 边框颜色
		int BorderWidth,        // 边框宽度
        bool bUseColorizedFont
		)
	{
		getFont( nFontIndex )->DrawBorderText( getRender(), pString, pRect, Format, Color, dwVtColorArray,
                                            nFontIndex, true, BorderColor, BorderWidth, bUseColorizedFont );
	}

	void MeFTFontManager::DrawTextHighBorderW( const WCHAR* pString, RECT* pRect, DWORD Format, D3DCOLOR Color, 
		const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex ,
		D3DCOLOR BorderColor,   // 边框颜色
		int BorderWidth,        // 边框宽度
		bool bUseColorizedFont
		)
	{
		const DWORD dwShadowColor = (BYTE((Color>>24)*0.5f))<<24;

		getFont(nFontIndex)->DrawBorderTextW(getRender(), pString, pRect, Format, Color,dwVtColorArray, nFontIndex, true, dwShadowColor, BorderWidth,bUseColorizedFont);

	}

	void MeFTFontManager::DrawTextHighBorder(
		const char* pString,
		INT X, INT Y,
		DWORD Format,
		D3DCOLOR Color,
        const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex,
        bool bUseColorizedFont )
	{
		RECT r ={ X, Y, 0, 0 };
		DrawTextHighBorder( pString,
			&r, Format,
			Color, dwVtColorArray, nFontIndex,
			0, 1,
            bUseColorizedFont );
	}
	void MeFTFontManager::DrawTextHighBorderW( const WCHAR* pString, INT X, INT Y, DWORD Format, D3DCOLOR Color,
		const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex,
		bool bUseColorizedFont
		)
	{
		RECT r = { X, Y, 0, 0 };
		DrawTextHighBorderW( pString,
			&r, Format,
			Color, dwVtColorArray, nFontIndex,
			0, 1,
			bUseColorizedFont
			);

	}

	int MeFTFontManager::GetTextWidth( const int& nFontIndex, const std::wstring& text, int startCharIndex, int endCharIndex, bool bTrail )
	{
		return getFont( nFontIndex )->GetTextWidth( text, startCharIndex, endCharIndex, bTrail );
	}

	float MeFTFontManager::GetFontHeight( int nFontIndex )
	{
		return getFont(nFontIndex)->getFontHeight();
	}

	float MeFTFontManager::GetRealHeight( int nFontIndex )
	{
		return getFont( nFontIndex )->GetRealHeight();
	}

	int MeFTFontManager::GetFontWidth( int nFontIndex )
	{
		return getFont( nFontIndex )->GetFontWidth();
	}

	void MeFTFontManager::GetEndIndexByWidth(
		const int& nFontIndex,
		const std::wstring &text, 
		int startCharIndex,
		int showWidth, 
		int& endCharIndex, 
		bool& bIsEnd )
	{
		getFont( nFontIndex )->GetEndIndexByWidth( text, startCharIndex, showWidth, endCharIndex, bIsEnd );
	}

	void MeFTFontManager::ResetDevice( float fScale )
	{
		FontRegistry::iterator iter;
		for( iter = d_fonts.begin(); iter != d_fonts.end(); ++iter )
		{
			iter->second->pFont->resetFontFaces( fScale );
		}
		for (iter=d_defaultFonts.begin(); iter!=d_defaultFonts.end(); ++iter)
		{
			iter->second->pFont->resetFontFaces(fScale);
		}
	}

	void MeFTFontManager::InitAllFontScale( float fScale )
	{
		d_fScale=fScale;
	}

	void MeFTFontManager::SetGlobalZ( float z, int nFontIndex )
	{
		getFont( nFontIndex )->setGlobalZ( z );
	}

	void MeFTFontManager::DrawTextDirect( const char* pString,
        RECT* pRect,
        DWORD Format,
        D3DCOLOR Color,
        const D3DCOLOR ( &dwVtColorArray )[4],
        unsigned int nFontIndex /*= 0*/,
        bool bBorder /*= false */,
        bool bUseColorizedFont )
	{
		std::wstring text = Common::_tstring::toWideString( pString );
		getFont( nFontIndex )->DrawShadowText( getRender(), text.c_str(), pRect, Format, Color, dwVtColorArray,
                                                nFontIndex, true, false, 1, bUseColorizedFont );
	}

	void MeFTFontManager::DrawTextDirectW( const WCHAR* pString, RECT* pRect, DWORD Format, D3DCOLOR Color, 
		const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex /*= 0*/,
		bool bBorder /*= false */,
		bool bUseColorizedFont )
	{
		getFont(nFontIndex)->DrawShadowText( getRender(),pString, pRect, Format, Color, dwVtColorArray, nFontIndex, true, false, 1, bUseColorizedFont );
	}

	void MeFTFontManager::BeginRender()
	{
		prepareFontTexture();
	}

	float MeFTFontManager::GetGlobalZ( int nFontIndex )
	{
		return getFont(nFontIndex)->GetGlobalZ();
	}
} //end of namespace me