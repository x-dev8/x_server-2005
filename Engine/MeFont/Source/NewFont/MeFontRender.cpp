#include "MeFont/NewFont/MeFontRender.h"

FontRender*	FontRender::g_pFontRender = 0;

FontRender::FontRender()
{
	memset( m_pRender, 0, sizeof( UiRender* ) * EFR_COUNT );
	m_eDefaultRenderer= EFR_FIRST;
}

FontRender::~FontRender()
{
	for( int i = 0 ; i < EFR_COUNT ; ++ i )
	{
		delete m_pRender[i];
		m_pRender[i] = 0;
	}

}

void FontRender::Initialize()
{
	for( int i = 0 ; i < EFR_COUNT; ++ i )
	{
		m_pRender[i] = new UiRender;
		m_pRender[i]->Initialize();
	}
}

FontRender* FontRender::getFontRender()
{
	if( !g_pFontRender )
		g_pFontRender = new FontRender;

	return g_pFontRender;
}

void FontRender::deleteFontRender()
{
	delete g_pFontRender;
	g_pFontRender = 0;
}

void FontRender::DoRender( EFontRenders eIdx, bool bOuterStates /*= false*/ )
{
	if( eIdx < EFR_COUNT 
		&& eIdx >= 0 
		&& m_pRender[eIdx] )
		m_pRender[eIdx]->doRender( bOuterStates );
	else
	{
		for( int i = 0 ; i < EFR_COUNT ; ++ i )
		{
			if( m_pRender[i] )
				m_pRender[i]->doRender( bOuterStates );
		}
	}
}
void FontRender::ClearRender( EFontRenders eIdx )
{
	if( eIdx < EFR_COUNT 
		&& eIdx >= 0 
		&& m_pRender[eIdx] )
		m_pRender[eIdx]->clearRenderList();
	else
	{
		for( int i = 0 ; i < EFR_COUNT ; ++ i )
		{
			if( m_pRender[i] )
				m_pRender[i]->clearRenderList();
		}
	}
}

UiRender* FontRender::GetDefaultRenderer()
{	
	return m_pRender[GetDefaultRendererIdx()];//return first
}