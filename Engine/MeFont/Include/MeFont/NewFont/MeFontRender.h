/************************************************************************
filename: 	MeFontRender.h
created:	8/20/2010
author:		Yejun.pi

purpose:	render font which is not belong to window
************************************************************************/
#ifndef FontRender_h_
#define FontRender_h_

#include "MeFontCommon.h"
#include "MeUi/UiRender.h"

class FontRender
{
public:
	enum EFontRenders
	{
		EFR_FIRST,
		EFR_SECOND,
		EFR_THIRD,
		EFR_COUNT
	};

public:
	FontRender();

	~FontRender();

	static FontRender* getFontRender();
	static void deleteFontRender();

	void Initialize();

	void DoRender( EFontRenders eIdx, bool bOuterStates = false );

	void ClearRender( EFontRenders eIdx );

	UiRender* GetDefaultRenderer();

	void SetDefaultRendererIdx( EFontRenders eIdx ){ m_eDefaultRenderer = eIdx; }
	const EFontRenders& GetDefaultRendererIdx() const{ return m_eDefaultRenderer; }

protected:

	static FontRender*			g_pFontRender;	
	UiRender*					m_pRender[EFR_COUNT];
	EFontRenders				m_eDefaultRenderer;

};

#endif