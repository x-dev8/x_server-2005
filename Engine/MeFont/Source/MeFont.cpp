#include "MeFont/MeFont.h"
#include <assert.h>

FontManager::FontManager(void)
{
	m_pd3dDevice = NULL;
	m_bUseShadow = false;
	m_fGlobalZ = 0.f;
	m_vtFont.clear();
	m_fFontScale=1.0f;
}

FontManager::~FontManager(void)
{
	
}

float FontManager::GetFontHeight( int nFontIndex )
{
	ID3DXFont *pFont = m_vtFont[nFontIndex];
	assert(pFont);
	D3DXFONT_DESCA desc;
	pFont->GetDesc( &desc );
	return static_cast< float >( desc.Height );
}

float FontManager::GetRealHeight( int nFontIndex )
{
	ID3DXFont *pFont = m_vtFont[nFontIndex];
	assert(pFont);
	D3DXFONT_DESCA desc;
	pFont->GetDesc( &desc );
	return static_cast< float >( desc.Height );
}

int FontManager::GetFontWidth( int nFontIndex )
{
	ID3DXFont *pFont = m_vtFont[nFontIndex];
	assert(pFont);
	D3DXFONT_DESCA desc;
	pFont->GetDesc( &desc );
	return desc.Width;
}

void FontManager::CreateDevice( IDirect3DDevice9* pd3dDevice )
{
	m_pd3dDevice = pd3dDevice;
	HRESULT hr = D3DXCreateSprite( pd3dDevice, &m_pSprite );
	assert( ( hr == S_OK ) && "create font sprite failed" );
}

void FontManager::ResetDevice( float fFontScale /* = 1.f */ )
{	
	for ( unsigned int n=0; n<m_vtFont.size(); n++ )
	{
		ID3DXFont *pFont = m_vtFont[n];
		pFont->OnResetDevice();
	}
	m_pSprite->OnResetDevice();
	fFontScale = min( 1.f , fFontScale );
	/*fFontScale = max( 0.8f, fFontScale );*/
	m_fFontScale = fFontScale;
// 	fFontScale *= 0.9f;
// 	D3DXMATRIX mat( fFontScale, 0, 0, 0,
// 					0, fFontScale, 0, 0,
// 					0, 0, fFontScale, 0,
// 					0, 0, 0, 1 );
// 	m_pSprite->SetTransform( &mat );
}

void FontManager::LostDevice()
{
	for ( unsigned int n=0; n<m_vtFont.size(); n++ )
	{
		ID3DXFont *pFont = m_vtFont[n];
		pFont->OnLostDevice();
	}
	m_pSprite->OnLostDevice();
}

void FontManager::DestroyDevice()
{
	for ( unsigned int n=0; n<m_vtFont.size(); n++ )
	{
		ID3DXFont *pFont = m_vtFont[n];
		pFont->Release();
	}
	m_vtFont.clear();
	if( m_pSprite )
		m_pSprite->Release();
	m_pSprite = 0;
}

int FontManager::CreateFont( LPCSTR	pFaceName,
						   INT		Height,
						   UINT		Width,
						   UINT		Weight,
						   UINT		MipLevels,
						   BOOL		Italic,
						   DWORD	CharSet,
						   DWORD	OutputPrecision,
						   DWORD	Quality,
						   DWORD	PitchAndFamily,
						   HDC		*phDC )
{
	assert(m_pd3dDevice);
	if ( !m_pd3dDevice )
	{
		return 0;
	}
	const char* szFontName = "宋体";
	if ( strcmp( pFaceName, "宋体" ) != 0 )
	{
		szFontName = pFaceName;
	}
	int nFontSize = 12;
	if ( Height != 12 )
	{
		nFontSize = Height;
	}
	else
	{
		Height = nFontSize;
	}

	// 先查找有没有此字体存在
	for ( unsigned int n=0; n<m_vtFont.size(); n++ )
	{
		ID3DXFont *pFont = m_vtFont[n];
		D3DXFONT_DESCA desc;
		pFont->GetDesc( &desc );
		if ( strcmp(desc.FaceName, szFontName) == 0 &&
			desc.Height == nFontSize &&
			desc.Width == Width &&
			desc.Weight == Weight )
		{
			if ( phDC )
			{
				*phDC = pFont->GetDC();
			}
			return n;
		}
	}
	//
	BYTE lfCharSet = GB2312_CHARSET; //gCfg.m_nLanguage;
	// 之所以有这个2是为兼容以前遗留下来的问题
	//if( gCfg.m_nLanguage == 2 )
	//{
	//	lfCharSet = GB2312_CHARSET;
	//}
	HRESULT hr;
	ID3DXFont *pFont = NULL;
	hr = D3DXCreateFont( m_pd3dDevice, nFontSize, Width, Weight, MipLevels, Italic, lfCharSet, 
						OutputPrecision, Quality, PitchAndFamily, szFontName, &pFont );
	if ( FAILED(hr) )
    {
        hr = D3DXCreateFont( m_pd3dDevice, nFontSize, Width, Weight, MipLevels, Italic, lfCharSet, 
            OutputPrecision, Quality, PitchAndFamily, "楷体_GB2312", &pFont );
        if ( FAILED(hr) )
		    return 0;
	}
	if ( phDC )
	{
		*phDC = pFont->GetDC();
	}	
	m_vtFont.push_back( pFont );
	return (int)m_vtFont.size()-1;
}


void FontManager::DrawTextHighBorderW( const WCHAR* pString, INT X, INT Y, DWORD Format, D3DCOLOR Color,
									  const D3DCOLOR ( &dwVtColorArray )[4],
									  unsigned int nFontIndex /* = 0 */,
									  bool bUseColorizedFont )
{
	RECT rc = {X,Y,0,0};
	RECT* pRect = &rc;
	if ( nFontIndex >= m_vtFont.size() )
	{
		assert(false);
		return;
	}
	ID3DXFont *pFont = m_vtFont[nFontIndex];	

	float fX = 0.f;
	float fY = 0.f;
	DWORD tempFormat = Format & ~DT_NOCLIP;
	//所有left,left-top,left-bottom都改为left-center
	if( ( tempFormat == DT_LEFT ) )
	{
		fX = (float)pRect->left;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}
	else if( ( tempFormat & DT_VCENTER ) && ( tempFormat == DT_TOP ) )
	{
		fX = ( pRect->left + pRect->right )*1.f / 2;
		fY = (float)pRect->top;
	}
	else if( ( tempFormat & DT_RIGHT ) && ( tempFormat == DT_TOP ) )
	{
		fX = (float)pRect->right;
		fY = (float)pRect->top;
	}
	else if( ( tempFormat & DT_RIGHT) && ( tempFormat & DT_VCENTER ) ) 
	{
		fX = (float)pRect->right;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}
	else if( ( tempFormat & DT_VCENTER ) && ( tempFormat & DT_BOTTOM ) )
	{
		fX = ( pRect->left + pRect->right )*1.f / 2;
		fY = (float)pRect->bottom;
	}
	else if( ( tempFormat & DT_RIGHT ) && ( tempFormat & DT_BOTTOM ) )
	{
		fX = (float)pRect->right;
		fY = (float)pRect->bottom;
	}
	else if( tempFormat & DT_RIGHT )
	{
		fX = (float)pRect->right;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}
	else
	{
		fX = ( pRect->left + pRect->right )*1.f / 2;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}

	m_pSprite->Begin( D3DXSPRITE_SORT_TEXTURE );
	D3DXMATRIX mat;
	D3DXVECTOR2 vScale( m_fFontScale, m_fFontScale );
	D3DXVECTOR2 vScaleCenter( fX, fY );	
	D3DXMatrixTransformation2D( &mat, &vScaleCenter, 1, &vScale, 0, 0, 0 );
	m_pSprite->SetTransform( &mat );
	//Format |= DT_NOCLIP;

	const DWORD dwShadowColor = (BYTE((Color>>24)*0.5f))<<24;
	RECT rcShadow = *pRect;		
	//right-bottom
	rcShadow.left += 4;
	rcShadow.right += 4;		
	rcShadow.top += 4;
	rcShadow.bottom += 4;
	pFont->DrawTextW( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );		
	//right
	rcShadow.top -= 4;
	rcShadow.bottom -= 4;
	pFont->DrawTextW( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );
	//bottom
	rcShadow.top += 4;
	rcShadow.bottom += 4;
	rcShadow.left -= 4;
	rcShadow.right -= 4;
	pFont->DrawTextW( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );	
	//left-bottom	
	rcShadow.left -= 4;
	rcShadow.right -= 4;
	pFont->DrawTextW( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );	
	//left
	rcShadow.top -= 4;
	rcShadow.bottom -= 4;	
	pFont->DrawTextW( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );	
	//left-top
	rcShadow.top -= 4;
	rcShadow.bottom -= 4;	
	pFont->DrawTextW( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );	
	//top
	rcShadow.left += 4;
	rcShadow.right += 4;	
	pFont->DrawTextW( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );	

	//pFont->DrawTextW( m_pSprite, pString, -1, pRect, Format, Color );	
	int nR = (( Color & 0x00ff0000 ) >> 16) ;
	if( nR + 0x09 <= 255 )
		nR += 0x09;
	int nG = (( Color & 0x0000ff00 ) >> 8);
	if( nG + 0x09 <= 255 )
		nG += 0x09;
	int nB = (( Color & 0x000000ff ));	
	if( nB + 0x09 <= 255 )
		nB += 0x09;
	DWORD dwCoverColor = ( ( 0xff )<<24) | ((nR)<<16) | ((nG)<<8) | (nB) ;
	pFont->DrawTextW( m_pSprite, pString, -1, pRect, Format, dwCoverColor );	
	m_pSprite->End();

}

void FontManager::DrawTextHighBorder( const char* pString, 
									 INT X, INT Y, 
									 DWORD Format, 
									 D3DCOLOR Color, 
                                     const D3DCOLOR ( &dwVtColorArray )[4],
									 unsigned int nFontIndex /* = 0 */,
                                     bool bUseColorizedFont )
{
	RECT rc = {X,Y,0,0};
	RECT* pRect = &rc;
	if ( nFontIndex >= m_vtFont.size() )
	{
		assert(false);
		return;
	}
	ID3DXFont *pFont = m_vtFont[nFontIndex];	

	float fX = 0.f;
	float fY = 0.f;
	DWORD tempFormat = Format & ~DT_NOCLIP;
	//所有left,left-top,left-bottom都改为left-center
	if( ( tempFormat == DT_LEFT ) )
	{
		fX = (float)pRect->left;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}
	else if( ( tempFormat & DT_VCENTER ) && ( tempFormat == DT_TOP ) )
	{
		fX = ( pRect->left + pRect->right )*1.f / 2;
		fY = (float)pRect->top;
	}
	else if( ( tempFormat & DT_RIGHT ) && ( tempFormat == DT_TOP ) )
	{
		fX = (float)pRect->right;
		fY = (float)pRect->top;
	}
	else if( ( tempFormat & DT_RIGHT) && ( tempFormat & DT_VCENTER ) ) 
	{
		fX = (float)pRect->right;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}
	else if( ( tempFormat & DT_VCENTER ) && ( tempFormat & DT_BOTTOM ) )
	{
		fX = ( pRect->left + pRect->right )*1.f / 2;
		fY = (float)pRect->bottom;
	}
	else if( ( tempFormat & DT_RIGHT ) && ( tempFormat & DT_BOTTOM ) )
	{
		fX = (float)pRect->right;
		fY = (float)pRect->bottom;
	}
	else if( tempFormat & DT_RIGHT )
	{
		fX = (float)pRect->right;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}
	else
	{
		fX = ( pRect->left + pRect->right )*1.f / 2;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}

	m_pSprite->Begin( D3DXSPRITE_SORT_TEXTURE );
	D3DXMATRIX mat;
	D3DXVECTOR2 vScale( m_fFontScale, m_fFontScale );
	D3DXVECTOR2 vScaleCenter( fX, fY );	
	D3DXMatrixTransformation2D( &mat, &vScaleCenter, 1, &vScale, 0, 0, 0 );
	m_pSprite->SetTransform( &mat );
	//Format |= DT_NOCLIP;

	const DWORD dwShadowColor = (BYTE((Color>>24)*0.5f))<<24;
	RECT rcShadow = *pRect;		
	//right-bottom
	rcShadow.left += 4;
	rcShadow.right += 4;		
	rcShadow.top += 4;
	rcShadow.bottom += 4;
	pFont->DrawTextA( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );		
	//right
	rcShadow.top -= 4;
	rcShadow.bottom -= 4;
	pFont->DrawTextA( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );
	//bottom
	rcShadow.top += 4;
	rcShadow.bottom += 4;
	rcShadow.left -= 4;
	rcShadow.right -= 4;
	pFont->DrawTextA( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );	
	//left-bottom	
	rcShadow.left -= 4;
	rcShadow.right -= 4;
	pFont->DrawTextA( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );	
	//left
	rcShadow.top -= 4;
	rcShadow.bottom -= 4;	
	pFont->DrawTextA( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );	
	//left-top
	rcShadow.top -= 4;
	rcShadow.bottom -= 4;	
	pFont->DrawTextA( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );	
	//top
	rcShadow.left += 4;
	rcShadow.right += 4;	
	pFont->DrawTextA( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );	

	//pFont->DrawTextW( m_pSprite, pString, -1, pRect, Format, Color );	
	int nR = (( Color & 0x00ff0000 ) >> 16) ;
	if( nR + 0x09 <= 255 )
		nR += 0x09;
	int nG = (( Color & 0x0000ff00 ) >> 8);
	if( nG + 0x09 <= 255 )
		nG += 0x09;
	int nB = (( Color & 0x000000ff ));	
	if( nB + 0x09 <= 255 )
		nB += 0x09;
	DWORD dwCoverColor = ( ( 0xff )<<24) | ((nR)<<16) | ((nG)<<8) | (nB) ;
	pFont->DrawTextA( m_pSprite, pString, -1, pRect, Format, dwCoverColor );	
	m_pSprite->End();

}

void FontManager::DrawText( const char* pString, 
						   RECT* pRect, 
						   DWORD Format, 
						   D3DCOLOR Color, 
                           const D3DCOLOR ( &dwVtColorArray )[4],
						   unsigned int nFontIndex /* = 0 */,
						   bool bZ /* = false */,
                           bool bUseColorizedFont )
{
	//return;

	if ( nFontIndex >= m_vtFont.size() )
	{
		assert(false);
		return;
	}
	ID3DXFont *pFont = m_vtFont[nFontIndex];	

	float fX = 0.f;
	float fY = 0.f;
	DWORD tempFormat = Format & ~DT_NOCLIP;
	//所有left,left-top,left-bottom都改为left-center
	if( ( tempFormat == DT_LEFT ) )
	{
		fX = (float)pRect->left;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}
	else if( ( tempFormat & DT_VCENTER ) && ( tempFormat == DT_TOP ) )
	{
		fX = ( pRect->left + pRect->right )*1.f / 2;
		fY = (float)pRect->top;
	}
	else if( ( tempFormat & DT_RIGHT ) && ( tempFormat == DT_TOP ) )
	{
		fX = (float)pRect->right;
		fY = (float)pRect->top;
	}
	else if( ( tempFormat & DT_RIGHT) && ( tempFormat & DT_VCENTER ) ) 
	{
		fX = (float)pRect->right;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}
	else if( ( tempFormat & DT_VCENTER ) && ( tempFormat & DT_BOTTOM ) )
	{
		fX = ( pRect->left + pRect->right )*1.f / 2;
		fY = (float)pRect->bottom;
	}
	else if( ( tempFormat & DT_RIGHT ) && ( tempFormat & DT_BOTTOM ) )
	{
		fX = (float)pRect->right;
		fY = (float)pRect->bottom;
	}
	else if( tempFormat & DT_RIGHT )
	{
		fX = (float)pRect->right;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}
	else
	{
		fX = ( pRect->left + pRect->right )*1.f / 2;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}

	DWORD dwSpriteFlag = D3DXSPRITE_SORT_TEXTURE;
	if( bZ )
	{
		dwSpriteFlag = D3DXSPRITE_SORT_DEPTH_BACKTOFRONT;
		m_pSprite->SetWorldViewRH( &m_matWorld, &m_matView );
	}

	m_pSprite->Begin( dwSpriteFlag );
	D3DXMATRIX mat;
	D3DXVECTOR2 vScale( m_fFontScale, m_fFontScale );
	D3DXVECTOR2 vScaleCenter( fX, fY );	
	D3DXMatrixTransformation2D( &mat, &vScaleCenter, 1, &vScale, 0, 0, 0 );
	if( bZ )
	{
		mat._43 = m_fGlobalZ;
	}
	m_pSprite->SetTransform( &mat );
	//Format |= DT_NOCLIP;
	
	if (m_bUseShadow)
	{
		const DWORD dwShadowColor = (BYTE((Color>>24)*0.5f))<<24;
		RECT rcShadow = *pRect;		
		//right-bottom
		rcShadow.left += 1;
		rcShadow.right += 1;		
		rcShadow.top += 1;
		rcShadow.bottom += 1;
		pFont->DrawTextA( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );		
		//right
		rcShadow.top -= 1;
		rcShadow.bottom -= 1;
		pFont->DrawTextA( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );
		//bottom
		rcShadow.top += 1;
		rcShadow.bottom += 1;
		rcShadow.left -= 1;
		rcShadow.right -= 1;
		pFont->DrawTextA( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );
		
	}
	else//只画一层
	{
		// Shadow
		RECT rcShadow = *pRect;		
		rcShadow.left += 3;
		rcShadow.right += 3;
		rcShadow.top += 3;
		rcShadow.bottom += 3;

		pFont->DrawTextA( m_pSprite, pString, -1, &rcShadow, Format, D3DCOLOR_XRGB(0,0,0) );
	}

	//pFont->DrawTextW( m_pSprite, pString, -1, pRect, Format, Color );	
	int nR = (( Color & 0x00ff0000 ) >> 16) ;
	if( nR + 0x09 <= 255 )
		nR += 0x09;
	int nG = (( Color & 0x0000ff00 ) >> 8);
	if( nG + 0x09 <= 255 )
		nG += 0x09;
	int nB = (( Color & 0x000000ff ));	
	if( nB + 0x09 <= 255 )
		nB += 0x09;
	DWORD dwCoverColor = ( ( 0xff )<<24) | ((nR)<<16) | ((nG)<<8) | (nB) ;
	pFont->DrawTextA( m_pSprite, pString, -1, pRect, Format, dwCoverColor );	
	m_pSprite->End();
}

void FontManager::DrawTextW( const WCHAR* pString, 
							RECT* pRect, 
							DWORD Format, 
							D3DCOLOR Color, 
                            const D3DCOLOR ( &dwVtColorArray )[4],
							unsigned int nFontIndex /* = 0 */, 
							bool bZ /* = false */,
                            bool bUseColorizedFont )
{
	//return;

	if ( nFontIndex >= m_vtFont.size() )
	{
		assert(false);
		return;
	}
	

	float fX = 0.f;
	float fY = 0.f;
	DWORD tempFormat = Format & ~DT_NOCLIP;
	//所有left,left-top,left-bottom都改为left-center
	if( ( tempFormat == DT_LEFT || tempFormat == DT_VCENTER ) )   //## 原DT_LEFT
	{
		fX = (float)pRect->left;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}
	else if( ( tempFormat & DT_VCENTER ) && ( tempFormat == DT_TOP ) )
	{
		fX = ( pRect->left + pRect->right )*1.f / 2;
		fY = (float)pRect->top;
	}
	else if( ( tempFormat & DT_RIGHT ) && ( tempFormat == DT_TOP ) )
	{
		fX = (float)pRect->right;
		fY = (float)pRect->top;
	}
	else if( ( tempFormat & DT_RIGHT) && ( tempFormat & DT_VCENTER ) ) 
	{
		fX = (float)pRect->right;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}
	else if( ( tempFormat & DT_VCENTER ) && ( tempFormat & DT_BOTTOM ) )
	{
		fX = ( pRect->left + pRect->right )*1.f / 2;
		fY = (float)pRect->bottom;
	}
	else if( ( tempFormat & DT_RIGHT ) && ( tempFormat & DT_BOTTOM ) )
	{
		fX = (float)pRect->right;
		fY = (float)pRect->bottom;
	}
	else if( tempFormat & DT_RIGHT )
	{
		fX = (float)pRect->right;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}
	else
	{
		fX = ( pRect->left + pRect->right )*1.f / 2;
		fY = ( pRect->top + pRect->bottom )*1.f / 2;
	}

	DWORD dwSpriteFlag = D3DXSPRITE_SORT_TEXTURE;
	if( bZ )
	{
		dwSpriteFlag = D3DXSPRITE_SORT_DEPTH_BACKTOFRONT;
		m_pSprite->SetWorldViewRH( &m_matWorld, &m_matView );
	}

	ID3DXFont *pFont = m_vtFont[nFontIndex];
	m_pSprite->Begin( dwSpriteFlag );

	D3DXMATRIX mat;
	D3DXVECTOR2 vScale( m_fFontScale, m_fFontScale );
	D3DXVECTOR2 vScaleCenter( fX, fY );
	D3DXMatrixTransformation2D( &mat, &vScaleCenter, 1, &vScale, 0, 0, 0 );
	if( bZ )
	{
		mat._43 = m_fGlobalZ;
	}
	m_pSprite->SetTransform( &mat );

	//Format |= DT_NOCLIP;
	const DWORD dwShadowColor = (BYTE((Color>>24)*0.5f))<<24;
	if (m_bUseShadow)
	{		
		RECT rcShadow = *pRect;		
		//right-bottom
		rcShadow.left += 1;
		rcShadow.right += 1;		
		rcShadow.top += 1;
		rcShadow.bottom += 1;
		pFont->DrawTextW( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );		
		//right
		rcShadow.top -= 1;
		rcShadow.bottom -= 1;
		pFont->DrawTextW( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );
		//bottom
		rcShadow.top += 1;
		rcShadow.bottom += 1;
		rcShadow.left -= 1;
		rcShadow.right -= 1;
		pFont->DrawTextW( m_pSprite, pString, -1, &rcShadow, Format, dwShadowColor );	
		
	}
	else//只画一层
	{
		// Shadow
		RECT rcShadow = *pRect;		
		rcShadow.left += 3;
		rcShadow.right += 3;
		rcShadow.top += 3;
		rcShadow.bottom += 3;	

		pFont->DrawTextW( m_pSprite, pString, -1, &rcShadow, Format, D3DCOLOR_XRGB(0,0,0) );
	}
	
	//pFont->DrawTextW( m_pSprite, pString, -1, pRect, Format, Color );	
	int nR = (( Color & 0x00ff0000 ) >> 16) ;
	if( nR + 0x09 <= 255 )
		nR += 0x09;
	int nG = (( Color & 0x0000ff00 ) >> 8);
	if( nG + 0x09 <= 255 )
		nG += 0x09;
	int nB = (( Color & 0x000000ff ));	
	if( nB + 0x09 <= 255 )
		nB += 0x09;
	DWORD dwCoverColor = ( ( 0xff )<<24) | ((nR)<<16) | ((nG)<<8) | (nB) ;
	pFont->DrawTextW( m_pSprite, pString, -1, pRect, Format, dwCoverColor );	
	m_pSprite->End();
}

void FontManager::DrawText( const char* pString, 
						   INT X, INT Y, 
						   DWORD Format, 
						   D3DCOLOR Color, 
                           const D3DCOLOR ( &dwVtColorArray )[4],
						   unsigned int nFontIndex /* = 0 */,
						   bool bZ /* = false */,
                           bool bUseColorizedFont )
{
	RECT rc = {X,Y,0,0};
	DrawText( pString, &rc, Format, Color, dwVtColorArray, nFontIndex, bZ, bUseColorizedFont );
}

void FontManager::DrawTextDirect( const char* pString, 
								 RECT* pRect, 
								 DWORD Format, 
								 D3DCOLOR Color, 
                                 const D3DCOLOR ( &dwVtColorArray )[4],
								 unsigned int nFontIndex /* = 0 */,
								 bool bBorder /*= false*/,
                                 bool bUseColorizedFont )
{	
	if ( nFontIndex >= m_vtFont.size() )
	{
		assert(false);
		return;
	}
	ID3DXFont *pFont = m_vtFont[nFontIndex];
	if( !pFont )
		return;

	if( bBorder )
	{
		RECT rc = *pRect;
		DWORD dwShadowColor = 0xee000000;
		//right-bottom
		rc.left += 1;
		rc.right += 1;		
		rc.top += 1;
		rc.bottom += 1;
		pFont->DrawTextA( 0, pString, -1, &rc, Format, dwShadowColor );		
		//right
		rc.top -= 1;
		rc.bottom -= 1;
		pFont->DrawTextA( 0, pString, -1, &rc, Format, dwShadowColor );
		//bottom
		rc.top += 1;
		rc.bottom += 1;
		rc.left -= 1;
		rc.right -= 1;
		pFont->DrawTextA( 0, pString, -1, &rc, Format, dwShadowColor );	
		//left-bottom	
		rc.left -= 1;
		rc.right -= 1;
		pFont->DrawTextA( 0, pString, -1, &rc, Format, dwShadowColor );	
		//left
		rc.top -= 1;
		rc.bottom -= 1;	
		pFont->DrawTextA( 0, pString, -1, &rc, Format, dwShadowColor );	
		//left-top
		rc.top -= 1;
		rc.bottom -= 1;	
		pFont->DrawTextA( 0, pString, -1, &rc, Format, dwShadowColor );	
		//top
		rc.left += 1;
		rc.right += 1;	
		pFont->DrawTextA( 0, pString, -1, &rc, Format, dwShadowColor );	
	}
	pFont->DrawTextA( 0, pString, -1, pRect, Format, Color );	
	
}
void FontManager::DrawTextDirectW( const WCHAR* pString, 
								 RECT* pRect, 
								 DWORD Format, 
								 D3DCOLOR Color, 
								 const D3DCOLOR ( &dwVtColorArray )[4],
								 unsigned int nFontIndex /*= 0*/,
								 bool bBorder /*= false */,
								 bool bUseColorizedFont )

{	
	if ( nFontIndex >= m_vtFont.size() )
	{
		assert(false);
		return;
	}
	ID3DXFont *pFont = m_vtFont[nFontIndex];
	if( !pFont )
		return;

	if( bBorder )
	{
		RECT rc = *pRect;
		DWORD dwShadowColor = 0xee000000;
		//right-bottom
		rc.left += 1;
		rc.right += 1;		
		rc.top += 1;
		rc.bottom += 1;
		pFont->DrawTextW( 0, pString, -1, &rc, Format, dwShadowColor );		
		//right
		rc.top -= 1;
		rc.bottom -= 1;
		pFont->DrawTextW( 0, pString, -1, &rc, Format, dwShadowColor );
		//bottom
		rc.top += 1;
		rc.bottom += 1;
		rc.left -= 1;
		rc.right -= 1;
		pFont->DrawTextW( 0, pString, -1, &rc, Format, dwShadowColor );	
		//left-bottom	
		rc.left -= 1;
		rc.right -= 1;
		pFont->DrawTextW( 0, pString, -1, &rc, Format, dwShadowColor );	
		//left
		rc.top -= 1;
		rc.bottom -= 1;	
		pFont->DrawTextW( 0, pString, -1, &rc, Format, dwShadowColor );	
		//left-top
		rc.top -= 1;
		rc.bottom -= 1;	
		pFont->DrawTextW( 0, pString, -1, &rc, Format, dwShadowColor );	
		//top
		rc.left += 1;
		rc.right += 1;	
		pFont->DrawTextW( 0, pString, -1, &rc, Format, dwShadowColor );	
	}
	pFont->DrawTextW( 0, pString, -1, pRect, Format, Color );	

}


