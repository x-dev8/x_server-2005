#pragma once

// freetype headers
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace More
{
	struct MeFTFontManager::FontManagerImplData
	{
		FT_Library		d_ftlib;		//!< FreeType library;
	};

}