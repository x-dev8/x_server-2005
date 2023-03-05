/************************************************************************
filename: 	Font.h
created:	8/20/2010
author:		Yejun.pi

purpose:	font class, use freetype
************************************************************************/
#ifndef __FONT_H__
#define __FONT_H__

#pragma warning( disable:4786 )

#include "MeFontCommon.h"
#include "MeUi/UiRender.h"

// freetype headers
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

using namespace std;
#define nullptr 0
class CD3dGraphic;
class Vector;


namespace More
{
	typedef UINT		argb_t;    //!< 32 bit ARGB representation of a colour.	
	typedef	Vector2		Point;

	struct Rect
	{
		Rect() { }
		Rect(float fleft, float ftop, float fright, float fbottom)
			: left(fleft), right(fright), top(ftop), bottom(fbottom) { }

		float Width() const { return right - left; }
		float Height() const { return bottom - top; }

		Rect& Rect::offset(const Point& pt)
		{
			left	+= pt.x;
			right	+= pt.x;
			top		+= pt.y;
			bottom	+= pt.y;
			return *this;
		}


		float left, right, top, bottom;
	};

	typedef Rect UVRect;

	

	//将文字的缓冲区和纹理关联上
	struct GlyphTexture
	{
		void*		d_memory;		//!< Memory that holds font glyph
		void*		d_texture;		//!< Texture that holds the glyphs for this font.
		bool		d_dirty;		//!< Flag need to recreate this font texture, 当d_memory未拷贝到pTexture的时候为true, 当已拷贝的时候为false.
		void	loadBufferToTexture(UINT nTexWidth,UINT nTexHeight,UINT pixelBytes);
	};

	class String;
    class Font
    {  
    public:
		struct FontImplData;

		/// Information about the position and size of a glyph in a texture
		struct GlyphInfo
		{
		public:
			//CodePoint	codePoint;				// 字符的unicode码, 由map管理，所以不需要重复保存
			UVRect		uvRect;					// 纹理区域
			USHORT		useCount;				// 字符的使用次数
			int			d_horz_advance;			// 这个比较难以准确描述，按道理它应该是在结合了前后的字之后得出的这个字的宽度。
			void*		pTexture;				// 纹理指针
			Point		offset;                 // 渲染区域偏移值，对应image的offset

		public:
			GlyphInfo(){}

			GlyphInfo( const UVRect& _rect, int nAdvance, LPDIRECT3DTEXTURE9 _pTex,Point& p ) 
				: uvRect(_rect), useCount(0), pTexture(_pTex),d_horz_advance(nAdvance),offset(p)
			{
			}
		};

        /// A range of code points, inclusive on both ends
        typedef std::pair<CodePoint, CodePoint> CodePointRange;
        typedef vector<CodePointRange> CodePointRangeList;
    
    public:

		Font(std::string fontName,const char* fileName, FontImplData* dat, int nFontSize, float fScale);

        ~Font();

		static	Font*	getSingletonPtr(void);

        void        load(const std::string& name);

        void        unLoad();

        
	public:


		const UVRect& getGlyphTexCoords(CodePoint id) const;

		
		/** Gets the information available for a glyph corresponding to a
		given code point, or throws an exception if it doesn't exist;
		*/
		const GlyphInfo* getGlyphInfo(CodePoint id) const;

		void    insertGlyphInfo(CodePoint id);

		//&&  重写一些函数，之前的有些函数将不再使用
		// 创建一个字的glyph信息
		virtual GlyphInfo*	createFontGlyph(CodePoint code);

		virtual GlyphTexture*    createGlayphTexture();

		/*!
		\brief
		Copy the current glyph data into \a buffer, which has a width of \a buf_width pixels (not bytes).

		\param buffer
		Memory buffer large enough to receive the imagery for the currently loaded glyph.

		\param buf_width
		Width of \a buffer in pixels (where each pixel is a argb_t).

		\return
		Nothing.
		*/
		virtual void	drawGlyphToBuffer(FT_Face ftFace, argb_t* buffer, UINT buf_width);

		/*!
		\brief
		Prepare the font texture.
		Check all glyph Imageset and recreate the dirtyed texture.

		\return
		Nothing
		*/
		void	prepareFontTexture(void);

		/*!
		\brief
		Recreate font glyph data map and imageset.
		*/
		virtual void	resetFontFaces(float fScale=1.0f);

		void clearAllFontFaces(void);

		void prepareString(const More::String& text);

		void prepareString(const char* pText);

		void prepareStringW(const WCHAR* text);

		void SaveAllTexture(const char* rootPath);

		
		void drawTextLine(const String& text, const Vector& position, const Rect& clip_rect, /*const ColourRect& colours,*/ float x_scale, float y_scale);
	
		/************************************************************************

		************************************************************************/
		void Font::DrawText(UiRender* pRender,
							const char* pString, 
							RECT* pRect, 
							DWORD Format, 
							D3DCOLOR Color, 
                            const D3DCOLOR ( &dwVtColorArray )[4],
							unsigned int nFontIndex , 
							bool bIsDirect=false,    //是否直接画, 即是否将 prepareString()和prepareFontTexture() 都放在DrawText里面
							bool bZ= false, 
							bool bUseColorizedFont = false
							);

		void DrawTextEx(  UiRender* pRender,
						const WCHAR* pString, 
						INT X, INT Y, 
						DWORD Format, 
						D3DCOLOR Color, 
                        const D3DCOLOR ( &dwVtColorArray )[4],
						unsigned int nFontIndex ,
						bool bIsDirect=false,
						bool bZbZ = false,
                        bool bUseColorizedFont = false
						);

		void Font::DrawText(UiRender* pRender,
							const WCHAR* pString, 
							RECT* pRect, 
							DWORD Format, 
							D3DCOLOR Color, 
                            const D3DCOLOR ( &dwVtColorArray )[4],
							unsigned int nFontIndex ,
							bool bIsDirect=false,
							bool bZ= false, 
							bool bUseColorizedFont = false
							);

		//画描边字
		void DrawBorderText(
							UiRender* pRender,
							const char* pString,
							RECT* pRect,
							DWORD Format,
							D3DCOLOR Color,
                            const D3DCOLOR ( &dwVtColorArray )[4],
							unsigned int nFontIndex ,
							bool bIsDirect,
							D3DCOLOR BorderColor,   // 边框颜色
							int BorderWidth,        // 边框宽度
                            bool bUseColorizedFont = false
							);
		void DrawBorderTextW(
			UiRender* pRender,
			const WCHAR* pString,
			RECT* pRect,
			DWORD Format,
			D3DCOLOR Color,
			const D3DCOLOR ( &dwVtColorArray )[4],
			unsigned int nFontIndex ,
			bool bIsDirect,
			D3DCOLOR BorderColor,   // 边框颜色
			int BorderWidth,        // 边框宽度
			bool bUseColorizedFont = false
			);

		//画阴影字, 只有右边有
		void DrawShadowText(
							UiRender* pRender,
							const WCHAR* pString,
							RECT* pRect,
							DWORD Format,
							D3DCOLOR Color,
                            const D3DCOLOR ( &dwVtColorArray )[4],
							unsigned int nFontIndex ,
							bool bIsDirect,
							bool bZ,
							int BorderWidth,				   // 边框宽度
                            bool bUseColorizedFont = false
							);

	public:
		/************************************************************************
		根据给定的字符索引, 得到字符串宽度
		in--text
		in--startCharIndex : 索引开始
		in--endCharIndex   : 索引结束位置
		in--bTrail         : 如果为true, 返回结束字符的后沿的位置; 如果为false, 返回结束字符的前沿位置.
		out--return value, 字符串宽度
		************************************************************************/
		int GetTextWidth(const std::wstring &text, const int& startCharIndex, int& endCharIndex, bool bTrail);

		/************************************************************************
		//根据给定的显示宽度, 得到可以显示到第几个字符. showWidth--是与原始的文理宽度比较, 所以应该外面除掉缩放.
		in--text
		in--startCharIndex
		in--showWidth
		out--endCharIndex
		out--bIsEnd : 是否可以显示最后一个字符
		************************************************************************/
		void GetEndIndexByWidth(const std::wstring &text, const int& startCharIndex,int& showWidth, int& endCharIndex, bool& bIsEnd);

		float Font::getFontHeight(void);

		float GetRealHeight(void);

		int GetFontWidth();

		float getRealScale();

		void setGlobalZ( float fZ ){ d_fGlobalZ = fZ; }
		float GetGlobalZ() const { return d_fGlobalZ; }
		
	private:
		/************************************************************************
		out: cur_pos -- 得到一行文字的左上角的起始点
		************************************************************************/
		void _getOffsetByFromat(Vector2& cur_pos, DWORD& Format,int& char_count,RECT& pRect, const WCHAR* text);

		void _DrawText(
						UiRender* pRender,
						int char_count,
						const WCHAR* text, 
						RECT* pRect, 
						DWORD Format, 
						D3DCOLOR Color, 
                        const D3DCOLOR ( &dwVtColorArray )[4],
						unsigned int nFontIndex, 
						bool bZ,
                        bool bUseColorizedFont = false
						);

		/************************************************************************
		调整纹理区域和目标区域, 针对每个字.
		为了使所有的DrawText都使用这一个函数来进行调整.
		out: texRect--纹理区域
		out: retDestRect--调整后的目标区域
		in:  cur_pos--渲染目标区域一个偏移位置
		************************************************************************/
		void _AjustTexRectAndDestRect(RECT& texRect, RECT& retDestRect,Vector2& cur_pos, RECT& srcDestRect, GlyphInfo& curText,DWORD& Format);

		int _loadChar( CodePoint char_code, FT_Face* localFace);

	protected:
		/// Map from unicode code point to texture coordinates
		typedef		std::map<CodePoint, GlyphInfo>  CodePointMap;
		CodePointMap			mCodePointMap;

		typedef		std::list< GlyphTexture* >		GlyphTextureList;
		GlyphTextureList							d_listGlyphTexture;

		std::string				mFontName;				//字体的名字

		/// Range of code points to generate glyphs for (truetype only)
		CodePointRangeList		mCodePointRangeList;

    protected:
        /// Size of the truetype font, in points
        float					mTtfSize;				// 文字大小
        /// Resolution (dpi) of truetype font
        unsigned int			mTtfResolution;
        /// Max distance to baseline of this (truetype) font
        int						mTtfMaxBearingY;
        /// for TRUE_TYPE font only
        bool					mAntialiasColour;

		GlyphTexture*			d_curGlyphTexture;

        UINT					mPixelBytes;			// 一个象素几个字节
      
		float					d_lineHeight;			//!< Exact pixel height of font.
		float					d_lineSpacing;			//!< Spacing between multiple lines.
		float					d_max_bearingY;			//!< Maximum bearingY value (gives required spacing down to baseline).
		UINT                    d_maxGlyphHeight;		// 字的最大高度
		UINT					d_maxGlyphWidth;		// 字的最大宽度

		UINT					d_ptNext_X;				//u 坐标，随着文字的插入而偏移（使用象素表示）。
		UINT					d_ptNext_Y;				//!< Next pos to add new font at current glyph.
		float					d_horzScaling;			//!< current horizontal scaling factor.
		float					d_vertScaling;			//!< current vertical scaling factor.
		float					d_srcScale;             // 保存游戏界面的缩放比例, 文字的缩放比例是经过变化的.
		float					d_fGlobalZ;		
		FontImplData*			d_impldat;				//!< Implementation data

		static const UINT	InterGlyphPadSpace;			//!< Pad space between glyphs.字之间的间隔距离
		static const UINT	FontGlyphTextureSize;		//!< Font texture size.
		static       UINT	SpecialCharCode;			// 特殊字符，当玩家输入的文字不存在时，使用这个代替。
    };
}

#endif
