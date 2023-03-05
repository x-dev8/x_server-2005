#pragma once


// freetype headers
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace More
{
	struct Font::FontImplData
	{
		FontImplData(FT_Library lib) : library(lib), fontFace(0) {}

		FT_Library	library;
		FT_Face		fontFace;
	};
}