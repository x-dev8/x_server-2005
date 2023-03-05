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

	

	//�����ֵĻ����������������
	struct GlyphTexture
	{
		void*		d_memory;		//!< Memory that holds font glyph
		void*		d_texture;		//!< Texture that holds the glyphs for this font.
		bool		d_dirty;		//!< Flag need to recreate this font texture, ��d_memoryδ������pTexture��ʱ��Ϊtrue, ���ѿ�����ʱ��Ϊfalse.
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
			//CodePoint	codePoint;				// �ַ���unicode��, ��map�������Բ���Ҫ�ظ�����
			UVRect		uvRect;					// ��������
			USHORT		useCount;				// �ַ���ʹ�ô���
			int			d_horz_advance;			// ����Ƚ�����׼ȷ��������������Ӧ�����ڽ����ǰ�����֮��ó�������ֵĿ�ȡ�
			void*		pTexture;				// ����ָ��
			Point		offset;                 // ��Ⱦ����ƫ��ֵ����Ӧimage��offset

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

		//&&  ��дһЩ������֮ǰ����Щ����������ʹ��
		// ����һ���ֵ�glyph��Ϣ
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
							bool bIsDirect=false,    //�Ƿ�ֱ�ӻ�, ���Ƿ� prepareString()��prepareFontTexture() ������DrawText����
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

		//�������
		void DrawBorderText(
							UiRender* pRender,
							const char* pString,
							RECT* pRect,
							DWORD Format,
							D3DCOLOR Color,
                            const D3DCOLOR ( &dwVtColorArray )[4],
							unsigned int nFontIndex ,
							bool bIsDirect,
							D3DCOLOR BorderColor,   // �߿���ɫ
							int BorderWidth,        // �߿���
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
			D3DCOLOR BorderColor,   // �߿���ɫ
			int BorderWidth,        // �߿���
			bool bUseColorizedFont = false
			);

		//����Ӱ��, ֻ���ұ���
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
							int BorderWidth,				   // �߿���
                            bool bUseColorizedFont = false
							);

	public:
		/************************************************************************
		���ݸ������ַ�����, �õ��ַ������
		in--text
		in--startCharIndex : ������ʼ
		in--endCharIndex   : ��������λ��
		in--bTrail         : ���Ϊtrue, ���ؽ����ַ��ĺ��ص�λ��; ���Ϊfalse, ���ؽ����ַ���ǰ��λ��.
		out--return value, �ַ������
		************************************************************************/
		int GetTextWidth(const std::wstring &text, const int& startCharIndex, int& endCharIndex, bool bTrail);

		/************************************************************************
		//���ݸ�������ʾ���, �õ�������ʾ���ڼ����ַ�. showWidth--����ԭʼ�������ȱȽ�, ����Ӧ�������������.
		in--text
		in--startCharIndex
		in--showWidth
		out--endCharIndex
		out--bIsEnd : �Ƿ������ʾ���һ���ַ�
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
		out: cur_pos -- �õ�һ�����ֵ����Ͻǵ���ʼ��
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
		�������������Ŀ������, ���ÿ����.
		Ϊ��ʹ���е�DrawText��ʹ����һ�����������е���.
		out: texRect--��������
		out: retDestRect--�������Ŀ������
		in:  cur_pos--��ȾĿ������һ��ƫ��λ��
		************************************************************************/
		void _AjustTexRectAndDestRect(RECT& texRect, RECT& retDestRect,Vector2& cur_pos, RECT& srcDestRect, GlyphInfo& curText,DWORD& Format);

		int _loadChar( CodePoint char_code, FT_Face* localFace);

	protected:
		/// Map from unicode code point to texture coordinates
		typedef		std::map<CodePoint, GlyphInfo>  CodePointMap;
		CodePointMap			mCodePointMap;

		typedef		std::list< GlyphTexture* >		GlyphTextureList;
		GlyphTextureList							d_listGlyphTexture;

		std::string				mFontName;				//���������

		/// Range of code points to generate glyphs for (truetype only)
		CodePointRangeList		mCodePointRangeList;

    protected:
        /// Size of the truetype font, in points
        float					mTtfSize;				// ���ִ�С
        /// Resolution (dpi) of truetype font
        unsigned int			mTtfResolution;
        /// Max distance to baseline of this (truetype) font
        int						mTtfMaxBearingY;
        /// for TRUE_TYPE font only
        bool					mAntialiasColour;

		GlyphTexture*			d_curGlyphTexture;

        UINT					mPixelBytes;			// һ�����ؼ����ֽ�
      
		float					d_lineHeight;			//!< Exact pixel height of font.
		float					d_lineSpacing;			//!< Spacing between multiple lines.
		float					d_max_bearingY;			//!< Maximum bearingY value (gives required spacing down to baseline).
		UINT                    d_maxGlyphHeight;		// �ֵ����߶�
		UINT					d_maxGlyphWidth;		// �ֵ������

		UINT					d_ptNext_X;				//u ���꣬�������ֵĲ����ƫ�ƣ�ʹ�����ر�ʾ����
		UINT					d_ptNext_Y;				//!< Next pos to add new font at current glyph.
		float					d_horzScaling;			//!< current horizontal scaling factor.
		float					d_vertScaling;			//!< current vertical scaling factor.
		float					d_srcScale;             // ������Ϸ��������ű���, ���ֵ����ű����Ǿ����仯��.
		float					d_fGlobalZ;		
		FontImplData*			d_impldat;				//!< Implementation data

		static const UINT	InterGlyphPadSpace;			//!< Pad space between glyphs.��֮��ļ������
		static const UINT	FontGlyphTextureSize;		//!< Font texture size.
		static       UINT	SpecialCharCode;			// �����ַ����������������ֲ�����ʱ��ʹ��������档
    };
}

#endif
