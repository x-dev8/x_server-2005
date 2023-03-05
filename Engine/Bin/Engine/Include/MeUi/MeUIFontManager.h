//////////////////////////////////////////////////////////////////////////
// This source file is a part of More Engine
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "MeFontNew/MeFontManagerBase.h"

namespace More
{
	class UIFontManager : public FontManagerBase
	{
	public:// public virtual function
	
		/** update font vertex position		
		*/
		virtual void UpdateGeometryPosition();

		/** 
		*/
		virtual void AssignVertexInfo( const FloatRect& rRcTarget, 
			const Font::FontUVRect& rRcFontUV, DWORD dwDiffuse, const Font& rkFont );

	public:// singleton staff
		~UIFontManager(){}

		/// get font manager instance
		static UIFontManager* GetInstance();

		/// initialize font manager
		static void Init();

		/// shutdown font manager
		static void Shutdown();

	protected:// singleton staff
		static UIFontManager* ms_pkThis;
		UIFontManager(){}		
	};

}
//////////////////////////////////////////////////////////////////////////