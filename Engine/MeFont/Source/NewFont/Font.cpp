
#include "MeFont/NewFont/MeString.h"
#include "MeFont/NewFont/Font.h"
#include "MeFont/NewFont/MeFont_implData.h"
#include "Me3d/Engine/Engine.h"
#include "tstring.h"
#include "Meui/MeUi.h"
#include "Me3d/Vector.h"
#include "MeFont/NewFont/MeFontRender.h"
#include "Meui/UiRender.h"
#include "MeFont/NewFont/MeFTFontManager.h"

#undef max
#undef min
INT		d_HeightOffset = 2;
namespace More
{

	const UINT		Font::InterGlyphPadSpace	= 0;
	const UINT		Font::FontGlyphTextureSize	= 512;
		  UINT		Font::SpecialCharCode		= 9633;   //9633 -- kuang

	Font::Font(
				std::string fontName, 
				const char* fileName, 
				FontImplData* dat, 
				int nFontSize,
				float fScale 
				)
        :mTtfMaxBearingY(0),
		mFontName(fontName),
		mTtfResolution(96*1.1f), 
		mAntialiasColour(false),
        d_curGlyphTexture(0), 
		d_ptNext_Y(0),
		d_ptNext_X(0),
		d_lineHeight(0),
		d_lineSpacing(0),
		d_max_bearingY(0),
		d_maxGlyphHeight(0),
		d_maxGlyphWidth(0),
		mPixelBytes(4),
		d_horzScaling(1.0f),
		d_vertScaling(1.0f),
		d_srcScale(fScale),
		d_impldat(dat),
		d_fGlobalZ(0.0f),
		mTtfSize(nFontSize)
    {
		
		load(fileName);
    }

    Font::~Font()
    {
        unLoad();
    }


    void Font::load(const std::string& fileName)
    {
		
        if(FT_New_Face(d_impldat->library, fileName.c_str(), 0, &d_impldat->fontFace)) 
		{
			assert(false&&"FreeType无法打开ttf文件");
		}
		// check that default Unicode character map is available
		if( !d_impldat->fontFace )
			return;

		if ( d_impldat->fontFace->charmap != NULL)	
		{
			//##重新计算face等
			resetFontFaces(d_srcScale);
		}
		else
		{
			prepareString((utf8*)"a\xE5\x95\x8A");  //a啊
			FT_Done_Face(d_impldat->fontFace);

			assert("Font_FreeType::constructor_impl - The source font does not have a Unicode charmap, and cannot be used.");
		}
    }  

    void Font::unLoad()
    {
		mCodePointMap.clear();

		// cleanup FreeType face if this is a FreeType based font.
		if(d_impldat)
		{
			FT_Done_Face(d_impldat->fontFace);
		}
		delete d_impldat;
		d_impldat=NULL;

		clearAllFontFaces();

    }

    const Font::GlyphInfo* Font::getGlyphInfo(CodePoint id) const
    {
        CodePointMap::const_iterator i = mCodePointMap.find(id);
        if (i == mCodePointMap.end())
        {
            return nullptr;
        }
        return &i->second;
    }
	

	/*********************************************************
	应该要扩展一个string,如cegui的,可以很方便的将unicode和string之间进行转换

	*********************************************************/
	void Font::prepareString(const More::String& text)
	{
		if(text.empty()) return;
		size_t char_count = text.length();

		CodePointMap::const_iterator end = mCodePointMap.end();
		for (size_t c = 0; c < char_count; ++c)
		{
			utf32 code = text[c];

			// check control code.
			if(code==(utf32)'\r' || code==(utf32)'\n') continue;

			// check is in font map
			if(mCodePointMap.find(code) == end)
			{
				createFontGlyph(code);
			}
		}
	}

	void Font::prepareStringW(const WCHAR* text)
	{
		
		size_t char_count = wcslen(text);

		CodePointMap::const_iterator end = mCodePointMap.end();
		for (size_t c = 0; c < char_count; ++c)
		{
			utf32 code = text[c];

			// check control code.
			if(code==(utf32)'\r' || code==(utf32)'\n') continue;
			
			// check is in font map
			if(mCodePointMap.find(code) == end)
			{
				createFontGlyph(code);
			}
		}
	}



	void Font::prepareString( const char* pText )
	{
		if (strlen(pText)==0)
		{
			return;
		}
		Common::_tstring str=pText;
		String text((utf8*)(str.toUTF8().c_str()));
		prepareString(text);

	}


	Font::GlyphInfo* Font::createFontGlyph( CodePoint code )
	{
		FT_Face localFace = NULL;
		//Load character glyph data from freetype 
		if ( _loadChar(code,&localFace) )
		{
			CodePointMap::const_iterator end = mCodePointMap.end();
			CodePointMap::const_iterator ret=mCodePointMap.find(SpecialCharCode);
			if(ret == end)
			{
				if( _loadChar( SpecialCharCode,&localFace) )
				{
					assert(false&&"SpecialCharCode is not in ttf file");
					return NULL;
				}
			}
			else
			{
				mCodePointMap[code]=ret->second;
				return &(mCodePointMap[code]);
			}
		}

		// update font maxheight
		if ((UINT)(localFace->glyph->bitmap.rows) > d_maxGlyphHeight)
		{
			d_maxGlyphHeight = localFace->glyph->bitmap.rows;
		}

		// font glyph width
		UINT nWidth = localFace->glyph->bitmap.width + InterGlyphPadSpace;

		if(!d_curGlyphTexture)// create new font imageset
		{
			d_curGlyphTexture = createGlayphTexture();
		}
		else
		{
			// Check is enough space to paint new character glyph in this line
			if( d_ptNext_X + nWidth > FontGlyphTextureSize ) // new line
			{
				d_ptNext_Y += d_maxGlyphHeight;
				d_ptNext_X = 0;

				// check is enough space in this imageset.
				if(d_ptNext_Y + d_maxGlyphHeight > FontGlyphTextureSize)
				{
					d_curGlyphTexture = createGlayphTexture();
				}
			}
		}
		if( !d_curGlyphTexture )
			return 0;

		// calculate offset into buffer for this glyph
		argb_t* dest_buff = 
			(argb_t*)(d_curGlyphTexture->d_memory) + d_ptNext_Y*FontGlyphTextureSize + d_ptNext_X;

		// draw glyph into buffer
		drawGlyphToBuffer(localFace, dest_buff, FontGlyphTextureSize);

		// define Image on Imageset for this glyph to save re-rendering glyph later
		Rect rect;
		rect.left		= (float)d_ptNext_X;   
		rect.top		= (float)d_ptNext_Y;   
		rect.right		= (float)(d_ptNext_X + nWidth - InterGlyphPadSpace);
		rect.bottom		= (float)(d_ptNext_Y + d_maxGlyphHeight);

		Point offset;
		offset.x		=  (float)(localFace->glyph->metrics.horiBearingX >> 6);
		offset.y		= -(float)(localFace->glyph->metrics.horiBearingY >> 6);


		//Next Point
		d_ptNext_X += nWidth;

		// create entry in code-point to Image map
		GlyphInfo	dat;
		dat.pTexture = d_curGlyphTexture->d_texture;
		dat.d_horz_advance = localFace->glyph->advance.x >> 6;
		dat.offset=offset;
		dat.uvRect=rect;
		dat.useCount=0;

		if ( dat.d_horz_advance > d_maxGlyphWidth )
		{
			d_maxGlyphWidth=dat.d_horz_advance;
		}

		mCodePointMap[code] = dat;

		//set dirty flag
		d_curGlyphTexture->d_dirty = true;

		return &(mCodePointMap[code]);
	}

	GlyphTexture* Font::createGlayphTexture()
	{
		// set dirty flag of old glyph
		if(d_curGlyphTexture)
		{
			d_curGlyphTexture->d_dirty = true;
		}

		// create new font glyph.		
		d_curGlyphTexture = new GlyphTexture;

		d_curGlyphTexture->d_dirty = true;

		// alloca font glyph memory.
		d_curGlyphTexture->d_memory = new argb_t[FontGlyphTextureSize * FontGlyphTextureSize];
		memset(d_curGlyphTexture->d_memory, 0, ((FontGlyphTextureSize * FontGlyphTextureSize) * sizeof(argb_t)));

		HRESULT hr = 0;
		//&&
		hr = D3DXCreateTexture(
			(LPDIRECT3DDEVICE9)GetEngine()->GetRenderer()->GetRealDevice(),
			FontGlyphTextureSize,
			FontGlyphTextureSize,
			1,
			0,
			D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED,  //D3DPOOL_MANAGED
			(LPDIRECT3DTEXTURE9*)&(d_curGlyphTexture->d_texture)
			); 

		if(FAILED(hr))
		{
			assert(false&&"Create font Texture failed");
			delete [] d_curGlyphTexture->d_memory;
			delete d_curGlyphTexture;
			return 0;
		}
		
		//insert imageset list
		d_listGlyphTexture.push_back(d_curGlyphTexture);

		// reset next pos
		d_ptNext_X = d_ptNext_Y = 0;

		return d_curGlyphTexture;
	}

	/*************************************************************************
	Copy the FreeType glyph bitmap into the given memory buffer
	*************************************************************************/
	void Font::drawGlyphToBuffer(FT_Face ftFace, argb_t* buffer, UINT buf_width)
	{
		FT_Bitmap* glyph_bitmap = &ftFace->glyph->bitmap;

		for (int i = 0; i < glyph_bitmap->rows; ++i)
		{
			for (int j = 0; j < glyph_bitmap->width; ++j)
			{			
// 				if (temp>80 && temp<170)
// 					temp*=1.4f;
// 				else if(temp>169)
// 					temp=255;

				switch (glyph_bitmap->pixel_mode)
				{
				case FT_PIXEL_MODE_GRAY:
					{
						uchar* bytebuff = reinterpret_cast<uchar*>(&buffer[j]);
						*bytebuff++ = 0xFF;
						*bytebuff++ = 0xFF;
						*bytebuff++ = 0xFF;
						*bytebuff=glyph_bitmap->buffer[(i * glyph_bitmap->pitch) + j];
					}
					break;

				case FT_PIXEL_MODE_MONO:
					buffer[j] = ((glyph_bitmap->buffer[(i * glyph_bitmap->pitch) + j / 8] << (j % 8)) & 0x80) ? 0xFFFFFFFF : 0x00000000;
					break;

				default:
					assert("Font::drawGlyphToBuffer - The glyph could not be drawn because the pixel mode is unsupported.");
					break;
				}

			}
			buffer += buf_width;
		}
	}

	/*************************************************************************
	Prepare the font texture.
	*************************************************************************/
	void Font::prepareFontTexture(void)
	{
		GlyphTextureList::iterator it, end = d_listGlyphTexture.end();

		for(it=d_listGlyphTexture.begin(); it!=end; ++it)
		{
			GlyphTexture* thisGlyph = *it;

			// font glyph need update to texture.
			if(thisGlyph->d_dirty)
			{
				thisGlyph->loadBufferToTexture(FontGlyphTextureSize,FontGlyphTextureSize,mPixelBytes);
#ifdef _MeDebug_
				CManageTexture::getSingletonPtr()->PushFontTexture("FontTexture",(LPDIRECT3DTEXTURE9)thisGlyph->d_texture);
#endif
				thisGlyph->d_dirty = false;
			}
		}
	}

	void Font::SaveAllTexture(const char* rootPath)
	{
		GlyphTextureList::iterator it, end = d_listGlyphTexture.end();

		int i=0; 
		char fullPathName[MAX_PATH];
		for(it=d_listGlyphTexture.begin(); it!=end; ++it,++i)
		{
			GlyphTexture* thisGlyph = *it;
			//输出文件为,如: F:\work_hero\Hero\Program\trunk\Bin\Client\Data\Font\simhei_14_0.dds 
			sprintf_s(fullPathName,MAX_PATH-1,"%s\\client\\Font\\texture\\%s_%d_%d.dds",rootPath,mFontName.c_str(),(UINT)mTtfSize,i);
			
			D3DXSaveTextureToFileA(fullPathName,D3DXIFF_DDS, (LPDIRECT3DTEXTURE9)thisGlyph->d_texture, 0);
			
		}
	}

	void GlyphTexture::loadBufferToTexture(UINT nTexWidth,UINT nTexHeight,UINT pixelBytes)
	{
		D3DLOCKED_RECT lockedRect;
		((IDirect3DTexture9*)d_texture)->LockRect(0, &lockedRect,0, 0);         

		//使用类型注意
		int*   TexData = (int*)lockedRect.pBits;
		int*   bufData = (int*)d_memory;

		for(UINT i = 0; i < nTexHeight; ++i)
		{
			for(UINT j = 0; j < nTexWidth; ++j)
			{
				//Pitch数据的总长度
				int index = i * lockedRect.Pitch / pixelBytes + j;
				TexData[index] = bufData[index];
			}
		}
		((IDirect3DTexture9*)d_texture)->UnlockRect(0);
	}

	/*************************************************************************
	Recreate font glyph data map and imageset.
	*************************************************************************/
	void Font::resetFontFaces(float fScale)
	{
		if(d_impldat->fontFace == 0) return;

		UINT horzDpi = mTtfResolution;
		UINT vertDpi = mTtfResolution;

// 		d_srcScale=fScale;

		// 将缩放放大
// 		if( (fScale-0.48f>0.01f) || (fScale-0.48f<-0.01f) )
// 			d_horzScaling = d_vertScaling = (fScale/0.48f)*1.05f; 
// 		else
		d_horzScaling = d_vertScaling = 1.0f;

		//if (d_autoScale)
		{
			horzDpi = (UINT)(((float)horzDpi) * d_horzScaling);
			vertDpi = (UINT)(((float)vertDpi) * d_vertScaling);
		}

		if (FT_Set_Char_Size(d_impldat->fontFace, 0, (FT_F26Dot6)(mTtfSize * 64), horzDpi, vertDpi) != 0)
		{
			// failed to set size for font
			assert("Font_FreeType::createFontFromFT_Face - An error occurred while creating a source font with the requested size.");
		}

		// clear font faces and memory
		clearAllFontFaces();

		d_maxGlyphWidth = d_maxGlyphHeight = 0;
		//insert default data to set font size data
		prepareString((utf8*)"a\xE5\x95\x8A");  //a啊
		//prepareString((utf8*)"谁"); //测试找不到字的情况


		d_lineHeight = (float)d_maxGlyphHeight;

		// calculate spacing and base-line
		d_max_bearingY = ((float)d_impldat->fontFace->ascender / (float)d_impldat->fontFace->units_per_EM) * (float)d_impldat->fontFace->size->metrics.y_ppem;
		d_lineSpacing = ((float)d_impldat->fontFace->height / (float)d_impldat->fontFace->units_per_EM) * (float)d_impldat->fontFace->size->metrics.y_ppem;
	}


	/*************************************************************************
	Clean all font glyph pTexture and memory.
	*************************************************************************/
	void Font::clearAllFontFaces(void)
	{
		// Clear font map
		mCodePointMap.clear();

		// Clear font glyph imagesets.
		GlyphTextureList::iterator it, end = d_listGlyphTexture.end();
		for(it=d_listGlyphTexture.begin(); it!=end; ++it)
		{
			GlyphTexture* thisGlyph = *it;

			delete[] thisGlyph->d_memory;
			thisGlyph->d_memory = NULL;

			((LPDIRECT3DTEXTURE9)(thisGlyph->d_texture))->Release();

			delete thisGlyph;
		}

		d_listGlyphTexture.clear();
		d_curGlyphTexture = 0;
		d_ptNext_X = d_ptNext_Y = 0;
		d_maxGlyphHeight = 0;
		d_max_bearingY = 0;
		d_lineSpacing = 0;
		d_lineHeight = 0;
		
	}

	const UVRect& Font::getGlyphTexCoords( CodePoint id ) const
	{
		CodePointMap::const_iterator i = mCodePointMap.find(id);
		if (i != mCodePointMap.end())
		{
			return i->second.uvRect;
		}
		else
		{
			static UVRect nullRect(0.0, 0.0, 0.0, 0.0);
			return nullRect;
		}
	}

	/*************************************************************************
	Draw a line of text.  No formatting is applied. returns draw result struct.
	*************************************************************************/
	void Font::drawTextLine(const String& text, const Vector& position, const Rect& clip_rect, /*const ColourRect& colours,*/ float x_scale, float y_scale)
	{
		Vector	cur_pos(position);

		float top_y = position.y;
		
		size_t char_count = text.length();
		CodePointMap::iterator	pos, end = mCodePointMap.end();

		float			blinkAlpha = 1.0f;
		unsigned long	lquid = 0;

		//Caculate max height and line base.
		float total_height = getFontHeight();
		for (size_t c = 0; c < char_count; ++c)
		{
			pos = mCodePointMap.find(text[c]);

			if (pos != end)
			{
				GlyphInfo* pInfo = &pos->second;
				float height = pInfo->uvRect.Height() * y_scale;
				if(height > total_height) total_height = height;
				if(height/y_scale > d_lineHeight) *((float*)&d_lineHeight) = height/y_scale;
			}
			
		}

		float base_y = top_y+total_height-InterGlyphPadSpace-1;

		for (size_t c = 0; c < char_count; ++c)
		{
			pos = mCodePointMap.find(text[c]);

			if (pos != end)
			{
				GlyphInfo* pInfo = &pos->second;
				cur_pos.y = base_y - (pInfo->offset.y - pInfo->offset.y * y_scale);
				//Size sz(pInfo->uvRect->getWidth() * x_scale, pInfo->uvRect->getHeight() * y_scale);

				cur_pos.x += (float)pos->second.d_horz_advance * x_scale;
			}
			

		}


// 		DrawTextResult dret;
// 		dret.d_lineCount = 1;
// 		dret.d_totalHeight = total_height + LineSpace;
//		return dret;
	}

	// 准备字符和准备纹理都在一个函数里面, 主要给ui使用.
	void Font::DrawText(
							UiRender* pRender,
							const WCHAR* text, 
							RECT* pRect, 
							DWORD Format, 
							D3DCOLOR Color, 
                            const D3DCOLOR ( &dwVtColorArray )[4],
							unsigned int nFontIndex, 
							bool bIsDirect,
							bool bZ,
                            bool bUseColorizedFont
							)
	{
		if (bIsDirect)
		{
			prepareStringW(text);
			//prepareFontTexture();
		}
		
		CodePointMap::iterator	pos, end = mCodePointMap.end();
		Vector2 cur_pos(0.0f,0.0f);   //定位每个字符渲染目标区域的左上角的点的位置.

		int char_count=wcslen(text);
		if(0==char_count)
			return;

		_DrawText(
			pRender,
			char_count,
			text, 
			pRect, 
			Format, 
			Color, 
            dwVtColorArray,
			nFontIndex, 
			bZ,
            bUseColorizedFont
			);
	}

	/************************************************************************
	pRender--由传入的render决定,将quad添加到哪个里面.
																			
	************************************************************************/
	void Font::DrawText(
							UiRender* pRender,
							const char* pString, 
							RECT* pRect, 
							DWORD Format, 
							D3DCOLOR Color, 
                            const D3DCOLOR ( &dwVtColorArray )[4],
							unsigned int nFontIndex, 
							bool bIsDirect,
							bool bZ,
                            bool bUseColorizedFont
							)
	{
		if (bIsDirect)
		{
			prepareString(pString);
			//prepareFontTexture();
		}
	

		if(strlen(pString)==0)
			return;

		//
		std::wstring text = Common::_tstring::toWideString( pString );
		int char_count=text.length();

		_DrawText(
			pRender,
			char_count,
			(WCHAR*)text.c_str(), 
			pRect, 
			Format, 
			Color, 
            dwVtColorArray,
			nFontIndex, 
			bZ,
            bUseColorizedFont
			);
	}

	// 在这个函数中直接画九遍, 而不是象cegui中只画border.
	void Font::DrawBorderText(
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
                        bool bUseColorizedFont
						)
	{
		std::wstring text = Common::_tstring::toWideString( pString );
		DrawBorderTextW(pRender,text.c_str(),pRect,Format,Color,dwVtColorArray,nFontIndex,bIsDirect,BorderColor,BorderWidth,bUseColorizedFont);

	}
	void Font::DrawBorderTextW( UiRender* pRender, const WCHAR* pString, RECT* pRect, DWORD Format, D3DCOLOR Color,
		const D3DCOLOR ( &dwVtColorArray )[4],
		unsigned int nFontIndex ,
		bool bIsDirect,
		D3DCOLOR BorderColor,   // 边框颜色
		int BorderWidth,        // 边框宽度
		bool bUseColorizedFont
		)
	{
		if (bIsDirect)
		{
			prepareStringW( pString);
			//prepareFontTexture();
		}

		if(wcslen(pString)==0)
			return;

		int char_count=wcslen(pString);

		CodePointMap::iterator	pos, end = mCodePointMap.end();

		Vector2 cur_pos;   

		_getOffsetByFromat(cur_pos, Format, char_count, *pRect, pString);

		for (size_t c = 0; c < char_count; ++c)
		{
			pos = mCodePointMap.find(pString[c]);

			if (pos != end)
			{
				GlyphInfo& curText=pos->second;

				RECT DestRect;
				RECT texRect;
				_AjustTexRectAndDestRect(texRect, DestRect, cur_pos, *pRect, curText, Format);

				// 对于裁减之后的文字描边需要注意, 如果上边被裁减掉, 那么只描左下右; 如果下边被裁减掉, 那么只描左上右.
				RECT borderRect=DestRect;

				//(1)往右移边框宽度
				borderRect.left = DestRect.left +BorderWidth;
				borderRect.right= DestRect.right+BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ );
				//(2)往右下移边框宽度
				borderRect.left = DestRect.left  +BorderWidth;
				borderRect.right= DestRect.right +BorderWidth;
				borderRect.top  = DestRect.top   +BorderWidth;
				borderRect.bottom=DestRect.bottom+BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);

				//(3)往下移边框宽度
				borderRect=DestRect;
				borderRect.top  = DestRect.top   +BorderWidth;
				borderRect.bottom=DestRect.bottom+BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);

				//(4)往左下移边框宽度
				borderRect.left = DestRect.left  -BorderWidth;
				borderRect.right= DestRect.right -BorderWidth;
				borderRect.top  = DestRect.top   +BorderWidth;
				borderRect.bottom=DestRect.bottom+BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);

				//(5)往左移边框宽度
				borderRect=DestRect;
				borderRect.left = DestRect.left  -BorderWidth;
				borderRect.right= DestRect.right -BorderWidth;				
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);

				//(6)往左上移边框宽度
				borderRect.left = DestRect.left  -BorderWidth;
				borderRect.right= DestRect.right -BorderWidth;
				borderRect.top  = DestRect.top   -BorderWidth;
				borderRect.bottom=DestRect.bottom-BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);

				//(7)往上移边框宽度
				borderRect=DestRect;
				borderRect.top  = DestRect.top   -BorderWidth;
				borderRect.bottom=DestRect.bottom-BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);

				//(8)往右上移边框宽度
				borderRect.left = DestRect.left  +BorderWidth;
				borderRect.right= DestRect.right +BorderWidth;
				borderRect.top  = DestRect.top   -BorderWidth;
				borderRect.bottom=DestRect.bottom-BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);


				//(9)最后添加本身的quad
				if( bUseColorizedFont )
				{
					pRender->AddColorizedQuad( DestRect, ( LPDIRECT3DTEXTURE9 )curText.pTexture, texRect, dwVtColorArray, font_quad, d_fGlobalZ );
				}
				else
				{
					pRender->addQuad(DestRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,Color,font_quad,d_fGlobalZ);
				}

				cur_pos.x = cur_pos.x + curText.d_horz_advance  + InterGlyphPadSpace;

			}
		}
	}


	//画阴影字, 只描右下.
	void Font::DrawShadowText(
								UiRender* pRender,
								const WCHAR* pString,
								RECT* pRect,
								DWORD Format,
								D3DCOLOR Color,
                                const D3DCOLOR ( &dwVtColorArray )[4],
								unsigned int nFontIndex ,
								bool bIsDirect,
								bool bZ,
								int BorderWidth,    // 边框宽度	
                                bool bUseColorizedFont
								)
	{
		static char cS = 0x0f;
		char cAlpha = ( ( Color & 0xff000000 ) >> 24 );
		D3DCOLOR BorderColor = D3DCOLOR_ARGB( cAlpha, cS,cS,cS );
		if (bIsDirect)
		{
			prepareStringW(pString);
			//prepareFontTexture();
		}

		int char_count=wcslen(pString);
		if(0==char_count)
			return;

		CodePointMap::iterator	pos, end = mCodePointMap.end();

		Vector2 cur_pos;   

		_getOffsetByFromat(cur_pos, Format, char_count, *pRect, pString);

		for (size_t c = 0; c < char_count; ++c)
		{
			pos = mCodePointMap.find(pString[c]);

			if (pos != end)
			{
				GlyphInfo& curText=pos->second;

				RECT DestRect;
				RECT texRect;
				_AjustTexRectAndDestRect(texRect, DestRect, cur_pos, *pRect, curText, Format);

				// 对于裁减之后的文字描边需要注意, 如果上边被裁减掉, 那么只描左下右; 如果下边被裁减掉, 那么只描左上右.
				RECT borderRect=DestRect;

				//(1)往右移边框宽度
 				borderRect.left = DestRect.left +BorderWidth;
 				borderRect.right= DestRect.right+BorderWidth;
 				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ );
 				//(2)往右下移边框宽度
 				borderRect.left = DestRect.left  +BorderWidth;
 				borderRect.right= DestRect.right +BorderWidth;
 				borderRect.top  = DestRect.top   +BorderWidth;
 				borderRect.bottom=DestRect.bottom+BorderWidth;
 				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);
 
 				//(3)往下移边框宽度
 				borderRect=DestRect;
 				borderRect.top  = DestRect.top   +BorderWidth;
 				borderRect.bottom=DestRect.bottom+BorderWidth;
 				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);
 
 				//(4)往左下移边框宽度
 				borderRect.left = DestRect.left  -BorderWidth;
 				borderRect.right= DestRect.right -BorderWidth;
 				borderRect.top  = DestRect.top   +BorderWidth;
 				borderRect.bottom=DestRect.bottom+BorderWidth;
 				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);
 
 				//(5)往左移边框宽度
 				borderRect=DestRect;
 				borderRect.left = DestRect.left  -BorderWidth;
 				borderRect.right= DestRect.right -BorderWidth;				
 				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);
 
 				//(6)往左上移边框宽度
 				borderRect.left = DestRect.left  -BorderWidth;
 				borderRect.right= DestRect.right -BorderWidth;
 				borderRect.top  = DestRect.top   -BorderWidth;
 				borderRect.bottom=DestRect.bottom-BorderWidth;
 				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);
 
 				//(7)往上移边框宽度
 				borderRect=DestRect;
 				borderRect.top  = DestRect.top   -BorderWidth;
 				borderRect.bottom=DestRect.bottom-BorderWidth;
 				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);
 
 				//(8)往右上移边框宽度
 				borderRect.left = DestRect.left  +BorderWidth;
 				borderRect.right= DestRect.right +BorderWidth;
 				borderRect.top  = DestRect.top   -BorderWidth;
 				borderRect.bottom=DestRect.bottom-BorderWidth;
 				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);


				//(9)最后添加本身的quad
                if( bUseColorizedFont )
                {
                    pRender->AddColorizedQuad( DestRect, ( LPDIRECT3DTEXTURE9 )curText.pTexture, texRect, dwVtColorArray, font_quad, d_fGlobalZ );
                }
				else
                {
                    pRender->addQuad(DestRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,Color,font_quad,d_fGlobalZ);
                }

				cur_pos.x = cur_pos.x + curText.d_horz_advance  + InterGlyphPadSpace;

			}
		}
	}

	void Font::DrawTextEx( UiRender* pRender,
								const WCHAR* pString, 
								INT X, 
								INT Y, 
								DWORD Format, 
								D3DCOLOR Color, 
                                const D3DCOLOR ( &dwVtColorArray )[4],
								unsigned int nFontIndex , 
								bool bIsDirect,
								bool bZ,
                                bool bUseColorizedFont
								)
	{
		RECT rc = {X,Y,0,0};
		DrawShadowText( pRender,pString, &rc, Format, Color, dwVtColorArray, nFontIndex, bIsDirect,bZ, 1, bUseColorizedFont );
	}

	void Font::_getOffsetByFromat(Vector2& v, DWORD& Format,int& char_count,RECT& pRect, const WCHAR* text)
	{
		CodePointMap::iterator	pos, end = mCodePointMap.end();

		DWORD tempFormat = Format & ~DT_NOCLIP & ~DT_WORDBREAK;        
		float offsetX=0.0f;
		float offsetY=0.0f;
		// 暂时注释
		Vector2 LineRect(0.0f,0.0f);  // 记录这行文字的宽度和高度
		if ( pRect.bottom!=0 )
		{
			for (size_t c = 0; c < char_count; ++c)
			{
				pos = mCodePointMap.find(text[c]);
				if (pos != end)
				{
					//UVRect& r=pos->second.uvRect;
					LineRect.x = LineRect.x + pos->second.d_horz_advance + InterGlyphPadSpace;
				}
			}
			LineRect.y = d_maxGlyphHeight;
		}
		else
		{
			v.x=offsetX;
			v.y=offsetY;
			return;
		}
		//所有left,left-top,left-bottom都改为left-center
// 		if( ( tempFormat == DT_LEFT ) )
// 		{
// 			//offsetY = ( ( pRect.bottom - pRect.top ) - LineRect.y ) / 2;
// 		}
// 		else if( ( tempFormat & DT_VCENTER ) && !( tempFormat & DT_CENTER ) )
// 		{
// 			offsetY = ( ( pRect.bottom - pRect.top ) - LineRect.y ) / 2;			
// 		}
// 		else if( ( tempFormat & DT_RIGHT ) && !( tempFormat & DT_CENTER ) )
// 		{
// 			offsetX = pRect.right - pRect.left - LineRect.x;
// 		}
// 		else if( ( tempFormat & DT_RIGHT) && ( tempFormat & DT_VCENTER ) ) 
// 		{
// 			offsetX = pRect.right - pRect.left - LineRect.x;
// 			offsetY = ( ( pRect.bottom - pRect.top ) - LineRect.y ) / 2;
// 		}
// 		else if( ( tempFormat & DT_VCENTER ) && ( tempFormat & DT_BOTTOM ) )
// 		{
// 			offsetX = ( ( pRect.right - pRect.left ) - LineRect.x ) / 2;
// 			offsetY = pRect.bottom - pRect.top - LineRect.y;
// 		}
// 		else if( ( tempFormat & DT_RIGHT ) && ( tempFormat & DT_BOTTOM ) )
// 		{
// 			offsetX = pRect.right - pRect.left - LineRect.x;
// 			offsetY = pRect.bottom - pRect.top - LineRect.y;
// 		}
// 		else if( tempFormat & DT_RIGHT )
// 		{
// 			offsetX = pRect.right - pRect.left - LineRect.x;
// 		}
// 		else
// 		{
// 			offsetX = ( ( pRect.right - pRect.left ) - LineRect.x ) / 2;
// 			offsetY = ( ( pRect.bottom - pRect.top ) - LineRect.y ) / 2;
// 		}
        // left top
        if( tempFormat == DT_LEFT )
        {}
        // top middle
        else if( tempFormat == DT_CENTER )
        {
            offsetX = ( ( pRect.right - pRect.left ) - LineRect.x ) / 2;
        }
        // top right
        else if( tempFormat == DT_RIGHT )
        {
            offsetX = pRect.right - pRect.left - LineRect.x;
        }
        // left middle
        else if( tempFormat == DT_VCENTER )
        {
            offsetY = ( ( pRect.bottom - pRect.top ) - LineRect.y ) / 2;
        }
        // middle middle
        else if( tempFormat == ( DT_VCENTER | DT_CENTER ) )
        {
            offsetX = ( ( pRect.right - pRect.left ) - LineRect.x ) / 2;
            offsetY = ( ( pRect.bottom - pRect.top ) - LineRect.y ) / 2;
        }
        // right middle
        else if( tempFormat == ( DT_VCENTER | DT_RIGHT ) )
        {
            offsetX = pRect.right - pRect.left - LineRect.x;
            offsetY = ( ( pRect.bottom - pRect.top ) - LineRect.y ) / 2;
        }
        // left bottom
        else if( tempFormat == ( DT_LEFT | DT_BOTTOM ) )
        {
            offsetY = pRect.bottom - pRect.top - LineRect.y;
        }
        // bottom middle
        else if( tempFormat == ( DT_CENTER | DT_BOTTOM ) )
        {
            offsetX = ( ( pRect.right - pRect.left ) - LineRect.x ) / 2;
            offsetY = pRect.bottom - pRect.top - LineRect.y;
        }
        // right bottom
        else if( tempFormat == ( DT_RIGHT | DT_BOTTOM ) )
        {
            offsetX = pRect.right - pRect.left - LineRect.x;
            offsetY = pRect.bottom - pRect.top - LineRect.y;
        }

		v.x=offsetX;
		v.y=offsetY;
	}

	void Font::_DrawText(
					UiRender* pRender,
					int char_count,
					const WCHAR* text, 
					RECT* pRect, 
					DWORD Format, 
					D3DCOLOR Color, 
                    const D3DCOLOR ( &dwVtColorArray )[4],
					unsigned int nFontIndex, 
					bool bZ,
                    bool bUseColorizedFont
					)
	{
// 		int nR = (( Color & 0x00ff0000 ) >> 16) ;
// 		if( nR + 0x09 <= 255 )
// 			nR += 0x09;
// 		int nG = (( Color & 0x0000ff00 ) >> 8);
// 		if( nG + 0x09 <= 255 )
// 			nG += 0x09;
// 		int nB = (( Color & 0x000000ff ));	
// 		if( nB + 0x09 <= 255 )
// 			nB += 0x09;
// 		DWORD dwCoverColor = ( ( 0xff )<<24) | ((nR)<<16) | ((nG)<<8) | (nB) ;

		CodePointMap::iterator	pos, end = mCodePointMap.end();
		
		Vector2 cur_pos;   //渲染目标区域一个偏移位置

		_getOffsetByFromat(cur_pos, Format, char_count, *pRect, text);
		
		//float base_y = pRect->top+d_lineHeight-InterGlyphPadSpace-1;
		int BorderWidth = 1;
		char cAlpha = ( ( Color & 0xff000000 ) >> 24 );
		static char cS = 0x0f;
		DWORD BorderColor = D3DCOLOR_ARGB( cAlpha, cS, cS, cS );
		for (size_t c = 0; c < char_count; ++c)
		{
			pos = mCodePointMap.find(text[c]);

			if (pos != end)
			{
				GlyphInfo& curText=pos->second;

				RECT DestRect;
				RECT texRect;
				_AjustTexRectAndDestRect(texRect, DestRect, cur_pos, *pRect, curText, Format);

				// 对于裁减之后的文字描边需要注意, 如果上边被裁减掉, 那么只描左下右; 如果下边被裁减掉, 那么只描左上右.
				RECT borderRect=DestRect;

				//(1)往右移边框宽度
				borderRect.left = DestRect.left +BorderWidth;
				borderRect.right= DestRect.right+BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ );
				//(2)往右下移边框宽度
				borderRect.left = DestRect.left  +BorderWidth;
				borderRect.right= DestRect.right +BorderWidth;
				borderRect.top  = DestRect.top   +BorderWidth;
				borderRect.bottom=DestRect.bottom+BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);

				//(3)往下移边框宽度
				borderRect=DestRect;
				borderRect.top  = DestRect.top   +BorderWidth;
				borderRect.bottom=DestRect.bottom+BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);

				//(4)往左下移边框宽度
				borderRect.left = DestRect.left  -BorderWidth;
				borderRect.right= DestRect.right -BorderWidth;
				borderRect.top  = DestRect.top   +BorderWidth;
				borderRect.bottom=DestRect.bottom+BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);

				//(5)往左移边框宽度
				borderRect=DestRect;
				borderRect.left = DestRect.left  -BorderWidth;
				borderRect.right= DestRect.right -BorderWidth;				
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);

				//(6)往左上移边框宽度
				borderRect.left = DestRect.left  -BorderWidth;
				borderRect.right= DestRect.right -BorderWidth;
				borderRect.top  = DestRect.top   -BorderWidth;
				borderRect.bottom=DestRect.bottom-BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);

				//(7)往上移边框宽度
				borderRect=DestRect;
				borderRect.top  = DestRect.top   -BorderWidth;
				borderRect.bottom=DestRect.bottom-BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);

				//(8)往右上移边框宽度
				borderRect.left = DestRect.left  +BorderWidth;
				borderRect.right= DestRect.right +BorderWidth;
				borderRect.top  = DestRect.top   -BorderWidth;
				borderRect.bottom=DestRect.bottom-BorderWidth;
				pRender->addQuad(borderRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,BorderColor,font_quad,d_fGlobalZ);


				//(9)最后添加本身的quad
                if( bUseColorizedFont )
                {
                    pRender->AddColorizedQuad( DestRect, ( LPDIRECT3DTEXTURE9 )curText.pTexture, texRect, dwVtColorArray, font_quad, d_fGlobalZ );
                }
                else
                {
                    pRender->addQuad(DestRect,(LPDIRECT3DTEXTURE9)curText.pTexture,texRect,Color,font_quad,d_fGlobalZ);
                }

				cur_pos.x = cur_pos.x + curText.d_horz_advance  + InterGlyphPadSpace;

			}
		}
	}

	/************************************************************************
	之后出现滚动条情况, 需要对文字的uv坐标做一个裁减, 就在这里调整.
	************************************************************************/
	void Font::_AjustTexRectAndDestRect(RECT& texRect, RECT& retDestRect,Vector2& cur_pos, RECT& srcDestRect, GlyphInfo& curText,DWORD& Format)
	{
	

		//curText.offset -- 对渲染区域的调整, 调整后的位置是文字的基线位置, 所以加上d_maxGlyphHeight, 但加上d_maxGlyphHeight
		//之后又有点偏低, 所以减去2个象素; 之所以给宽度和高度都减2个象素, 是因为, 在uirender里面, 目标区域相对于纹理区域多了
		//两个象素, 所以在这里减去两个象素.
		retDestRect.left  = srcDestRect.left + cur_pos.x + curText.offset.x ; 
		retDestRect.right =	retDestRect.left + curText.uvRect.Width();// -1.0f;  // 这里只-1.0f, 因为texRect加宽了一个象素
 		retDestRect.top   =	srcDestRect.top  + cur_pos.y + curText.offset.y + d_maxGlyphHeight-d_HeightOffset;
 		retDestRect.bottom=	retDestRect.top  + curText.uvRect.Height()	/*-1.0f*/; // 这里只-1.0f, 因为texRect加高了一个象素
		

		UVRect& r=curText.uvRect;
		texRect.left  = r.left;
		texRect.top   =	r.top;    
		texRect.right =	r.right;//+1;		//往右多加一个象素.
		texRect.bottom=	r.bottom;//+1;		//将纹理区域往多加一个象素 

	}

	int Font::_loadChar( CodePoint char_code , FT_Face* localFace)
	{
		//return FT_Load_Char(d_impldat->fontFace, char_code, FT_LOAD_RENDER /*|FT_LOAD_FORCE_AUTOHINT|FT_LOAD_TARGET_NORMAL*//*FT_LOAD_DEFAULT|FT_LOAD_RENDER|FT_LOAD_TARGET_NORMAL*/);
// 		if( mTtfSize < 10 )
// 			return FT_Load_Char(d_impldat->fontFace, char_code, FT_LOAD_RENDER | FT_LOAD_NO_AUTOHINT | FT_LOAD_MONOCHROME );//点阵
// 		else
		static DWORD dwTest = FT_LOAD_RENDER | FT_LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH;
		int nRet = FT_Load_Char(d_impldat->fontFace, char_code, dwTest );
		if (0 == nRet)
		{
			FT_Bitmap* glyph_bitmap = &d_impldat->fontFace->glyph->bitmap;
			if (!MeFTFontManager::Instance()->IsSupportSpecialChar() || char_code == ' ')
			{
				*localFace = d_impldat->fontFace;
				return 0;
			}
			bool bValid = false;
			for (int i = 0; i < glyph_bitmap->rows; ++i)
			{
				switch (glyph_bitmap->pixel_mode)
				{
				case FT_PIXEL_MODE_GRAY:
					{
						for (int j = 0; j < glyph_bitmap->width; ++j)
						{
							if (glyph_bitmap->buffer[(i * glyph_bitmap->pitch) + j] != 0)
							{
								bValid = true;
								break;
							}
						}
					}
					break;

				case FT_PIXEL_MODE_MONO:
					for (int j = 0; j < glyph_bitmap->width/8; ++j)
					{
						if (glyph_bitmap->buffer[(i * glyph_bitmap->pitch) + j] != 0)
						{
							bValid = true;
							break;
						}
					}
					break;

				default:
					assert("Font::drawGlyphToBuffer - The glyph could not be drawn because the pixel mode is unsupported.");
					break;
				}			
				if (bValid)
				{
					break;
				}
			}
			if (bValid)
			{
				*localFace = d_impldat->fontFace;
				return 0;
			}
			else
			{
				Font* pDefault = MeFTFontManager::Instance()->GetDefaultFont(mTtfSize* 0.85f);
				if (pDefault && pDefault->d_impldat 
					&& 0 == FT_Load_Char(pDefault->d_impldat->fontFace, char_code, dwTest ))
				{
					*localFace = pDefault->d_impldat->fontFace;
					return 0;
				}
			}
		}
		return nRet;
	}

	//得到一段字符串的宽度, 缩放交给外面处理.
	//bTrail : 如果为true, 返回结束字符的后沿的位置; 如果为false, 返回结束字符的前沿位置, 不过左为前还是右为前,这个还有待考察
	// 暂时理解右为前
	int Font::GetTextWidth(const std::wstring &text, const int& startCharIndex, int& endCharIndex, bool bTrail)
	{
		if(text.empty()) return 0;

		int width=0;

		if(bTrail)
			endCharIndex -= 1;
		
		CodePointMap::const_iterator end = mCodePointMap.end();
		CodePointMap::const_iterator ret;
		for (int c = startCharIndex; c < endCharIndex; ++c)
		{
			utf32 code = text[c];

			// check control code.
			if(code==(utf32)'\r' || code==(utf32)'\n') continue;

			// check is in font map
			Font::GlyphInfo* pInfo;
			if( (ret=mCodePointMap.find(code)) == end)
			{
				pInfo=createFontGlyph(code);
			}
			else
			{
				pInfo=(GlyphInfo*)(&(ret->second));
			}
			if( !pInfo )
				return 0;
			// -1.0f 的解释见_AjustTexRectAndDestRect里面. 
			//width = width+ (pInfo->uvRect.Width()+pInfo->offset.d_x+pInfo->d_horz_advance+InterGlyphPadSpace-1.0f);
			width = width+ pInfo->d_horz_advance+InterGlyphPadSpace;
		}
		return width;
	}

	/************************************************************************
	//根据给定的显示宽度, 得到可以显示到第几个字符.
	in--text
	in--startCharIndex
	in--showWidth
	out--endCharIndex
	out--bIsEnd : 是否可以显示最后一个字符
	************************************************************************/
	void Font::GetEndIndexByWidth(const std::wstring &text, const int& startCharIndex,int& showWidth, int& endCharIndex, bool& bIsEnd)
	{
		if(text.empty()) return ;

		int width=0;
		CodePointMap::const_iterator end = mCodePointMap.end();
		CodePointMap::const_iterator ret;
		int char_count=text.length();
		size_t c = startCharIndex;
		for (; c < char_count; ++c)
		{
			utf32 code = text[c];

			// check control code.
			if(code==(utf32)'\r' || code==(utf32)'\n') continue;

			// check is in font map
			Font::GlyphInfo* pInfo;
			if( (ret=mCodePointMap.find(code)) == end)
			{
				pInfo=createFontGlyph(code);
			}
			else
			{
				pInfo=(GlyphInfo*)(&(ret->second));
			}
			if( !pInfo )
				return;
			// -1.0f 的解释见_AjustTexRectAndDestRect里面.
			//width = width+ (pInfo->uvRect.Width()+pInfo->offset.d_x+pInfo->d_horz_advance+InterGlyphPadSpace-1.0f);
			width = width+ pInfo->d_horz_advance+InterGlyphPadSpace;

			if (width>=showWidth)
			{
				bIsEnd=false;
				endCharIndex=c;    // 本来这里应该为c-1，但是在getTextWidth中，会在这个基础上再少一个字符，所以就刚好。
				return;
			}
			
		}
		bIsEnd=true;
		endCharIndex=c;
	}

	float Font::getFontHeight(void)
	{
		return d_maxGlyphHeight/*/d_srcScale*/;   //因为外边在得到这个高度后都乘一个fscale;
	}

	float Font::GetRealHeight( void )
	{
		return d_maxGlyphHeight;
	}

	int Font::GetFontWidth()
	{
		return d_maxGlyphWidth+InterGlyphPadSpace;
	}

	float Font::getRealScale()
	{
		return d_horzScaling;
	}


}
