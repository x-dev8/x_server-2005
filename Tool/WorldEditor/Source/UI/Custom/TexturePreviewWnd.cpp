/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	TexturePreviewWnd.cpp
* Date: 	03/21/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "TexturePreviewWnd.h"

////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CTexturePreviewWnd, CStatic)
	//{{AFX_MSG_MAP(CTexturePreviewWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////
CTexturePreviewWnd::CTexturePreviewWnd()
{
	m_pParentWnd = NULL;
}

CTexturePreviewWnd::~CTexturePreviewWnd()
{
	m_pParentWnd = NULL;
}

void CTexturePreviewWnd::Init(UINT nID, CDialog* pParentWnd)
{
	m_pParentWnd	= pParentWnd;
	m_hasTexture	= false;
	if( FALSE == SubclassDlgItem(nID, pParentWnd) ) {
		AfxMessageBox( _T("不能创建子控件!") );
	}
}

bool CTexturePreviewWnd::SetTextureName( const char* textureName, ENUM_CXIMAGE_FORMATS texFormat )
{
	if( NULL != textureName ) {
		TCHAR strName[MAX_PATH];
		_stprintf_s( strName, _T("%s\\%hs"), CWorld::GetAppDataCharDir(), textureName );
// 		if( _tcscmp( m_textureName, strName ) != 0 ) 贴图本身可能被修改
		{
			_tcscpy_s( m_textureName, strName );
			if( !m_image.Load( m_textureName, texFormat ) ) {
				m_hasTexture = false;
				return false;
			}
			m_hasTexture = true;
		}
	}
	else {
		_tcscpy_s( m_textureName, _T("No texture") );
		m_hasTexture = false;
	}
	Invalidate();
	return true;
}

bool CTexturePreviewWnd::SetTexture( const char* path, const char* textureName, ENUM_CXIMAGE_FORMATS texFormat )
{
	if( NULL != textureName && NULL != path ) {
		_stprintf_s( m_textureName, _T("%s\\%hs\\%hs"), CWorld::GetAppDataCharDir(), path, textureName );
		if( !m_image.Load( m_textureName, texFormat  ) ) {
			m_hasTexture = false;
			return false;
		}
		m_hasTexture = true;
	}
	else {
		m_hasTexture = false;
	}
	Invalidate();
	return true;
}

void CTexturePreviewWnd::OnPaint()
{
	CPaintDC dcPaint(this); // device context for painting
	
	CRect rc;
	GetWindowRect(rc);
	
	Draw( &dcPaint, CRect(0, 0, rc.right-rc.left, rc.bottom-rc.top) );
}

void CTexturePreviewWnd::Draw( CPaintDC *pDC, CRect& rect )
{
	if( !m_hasTexture ) {
		pDC->FillSolidRect( rect, RGB(0xEC, 0xE9, 0xD8));
		return;
	}
	if( !m_image.IsValid() ) 
		return;
	
	m_image.Stretch( *pDC, rect.left, rect.top, (rect.right-rect.left), (rect.bottom-rect.top) );
	
	//rect.InflateRect(3, 3);
	//pDC->Draw3dRect(rect, RGB(0xFF, 0xFF, 0xFF), 0xFFFF0000);
}


