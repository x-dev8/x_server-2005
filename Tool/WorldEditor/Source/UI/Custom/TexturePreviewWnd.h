/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	CTexturePreviewWnd.h
* Date: 	03/21/2007
* Desc:
*
*******************************************************************************/
#ifndef _UI_DLG_TEXTUREPREVIEWWND_H__
#define _UI_DLG_TEXTUREPREVIEWWND_H__

class CxImage;
////////////////////////////////////////////////////////////////////////////////
class CTexturePreviewWnd : public CStatic
{
public:
				CTexturePreviewWnd();
				~CTexturePreviewWnd();
				
	void		Init(UINT nID, CDialog* pParentWnd);
	bool		SetTextureName( const char* textureName, ENUM_CXIMAGE_FORMATS texFormat = CXIMAGE_FORMAT_PNG );
	bool		SetTexture( const char* path, const char* textureName, ENUM_CXIMAGE_FORMATS texFormat = CXIMAGE_FORMAT_PNG );
	void		Draw( CPaintDC *pDC, CRect& rect );


protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
public:
	bool		m_hasTexture;
	TCHAR		m_textureName[MAX_PATH];
	CDialog*	m_pParentWnd;
	CxImage		m_image;
	
};

#endif	// _UI_DLG_TEXTUREPREVIEWWND_H__
