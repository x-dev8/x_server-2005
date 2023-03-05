#include "MeRTLibs.h"
#include "MeUIFontManager.h"
#include "UiRender.h"


namespace More
{
	//////////////////////////////////////////////////////////////////////////
	UIFontManager* UIFontManager::ms_pkThis = 0;
	//////////////////////////////////////////////////////////////////////////
	UIFontManager* UIFontManager::GetInstance()
	{ return ms_pkThis; }
	//////////////////////////////////////////////////////////////////////////
	void UIFontManager::Init()
	{
		if( !ms_pkThis )
		{
			ms_pkThis = new UIFontManager;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	void UIFontManager::Shutdown()
	{
		if( !ms_pkThis )
			return;

		ms_pkThis->m_Fonts.clear();
		ms_pkThis->ClearGeometry();

		delete ms_pkThis;
		ms_pkThis = 0;
	}	
	//////////////////////////////////////////////////////////////////////////
	void UIFontManager::UpdateGeometryPosition()
	{
		if( m_Groups.empty() )
			return;

		FontManagerBase::UpdateGeometryPosition();
	}
	//////////////////////////////////////////////////////////////////////////
	void UIFontManager::AssignVertexInfo( const FloatRect& rRcTarget, 
		const Font::FontUVRect& rRcFontUV, DWORD dwDiffuse, const Font& rkFont )
	{
		// add quad
		RECT rcDest = { rRcTarget.left, rRcTarget.top, rRcTarget.right, rRcTarget.bottom };
		RECT rcTex;
		rcTex.left = rRcFontUV.left * rkFont.GetFinalTextureWidth() - 0.5f;
		rcTex.right = rRcFontUV.right * rkFont.GetFinalTextureWidth() + 0.5f;
		rcTex.top = rRcFontUV.top * rkFont.GetFinalTextureWidth() - 0.5f;
		rcTex.bottom = rRcFontUV.bottom * rkFont.GetFinalTextureWidth() + 0.5f;

		g_uiRenderCurrFrame->addQuad( rcDest, rkFont.GetFontTexture(), rcTex, dwDiffuse, UiRender::TopLeftToBottomRight );
	}
	//////////////////////////////////////////////////////////////////////////
}


