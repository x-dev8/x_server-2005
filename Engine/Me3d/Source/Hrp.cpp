#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <gdiplus.h>
#include "hrp.h"
#include "..\common\tga.h"
#include "..\hr3d\jpeg\jpegimage.h"
#include "..\hr3d\hr3d_global.h" 
#include "..\common\datachunkwriter.h"
#include "..\hr3d\hr3d_stdio.h"
#include "..\common\FuncPerformanceLog.h"
#include "vfs.h"

extern FileIO :: CVFS g_TextureVFS;

DWORD HR3D_Picture::m_dwDetailShift = 0;
BOOL HR3D_PictureVersion::Read( HR3D_PicturePointer inP, int nSize )
{
	guardfunc;
	HR3D_PicturePointer p(inP.p);
	m_dwVersion = *p.i++;
	return TRUE;
	unguard;
}
BOOL HR3D_PictureInfo::Read( HR3D_PicturePointer inP, int nSize )
{
	guardfunc;
	HR3D_PicturePointer p(inP.p);
	m_dwWidth = *p.i++;
	m_dwHeight = *p.i++;
	m_dwMipmapLevel = *p.i++;
	m_dwSrcFileFormat = *p.i++;
	return TRUE;
	unguard;
}
HR3D_PictureImage::~HR3D_PictureImage()
{
	guardfunc;
	unguard;
}
BOOL HR3D_PictureImage::Read( HR3D_PicturePointer inP, int nSize )
{
	guardfunc;
	HR3D_PicturePointer p(inP.p);
	m_dwWidth = *p.i++;
	m_dwHeight = *p.i++;
	m_nQuality = *p.i++;
	m_dwFormat = *p.dw++;
	m_dwCompressMethod = *p.dw++;
	m_dwImageBufferSize = *p.dw++;
	m_pbyImageBuffer = p.byte;
	//memcpy( m_pbyImageBuffer, p.byte, m_dwImageBufferSize );
	p.c += m_dwImageBufferSize;
	return TRUE;
	unguard;
}

BOOL HR3D_PictureMipmap::Read( HR3D_PicturePointer inP, int nSize )
{
	guardfunc;
	HR3D_PicturePointer p(inP.p);
	m_dwWidth = *p.dw++;
	m_dwHeight = *p.dw++;
	
	while( p.c < inP.c+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'rgb0':
			{
				p.dw++;
				int size = *p.i++;
				m_bHasRGB = TRUE;
				m_imageRGB.Read( p, size );
				p.c += size; 
			}
			break;
		case 'alph':
			{
				p.dw++;
				int size = *p.i++;
				m_bHasAlpha = TRUE;
				m_imageAlpha.Read( p, size );
				p.c += size; 
				break;
			}
			break;
		case 'argb':
			{
				p.dw++;
				int size = *p.i++;
				m_bHasARGB = TRUE;
				m_imageARGB.Read( p, size );
				p.c += size; 
				break;
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
				break;
			}
			break;
		}

	}
	return TRUE;
	unguard;
}

BYTE* HR3D_PictureMipmap::Decode( DWORD dwFormat )
{
	guardfunc;
	// 先还原成32bit argb
	DWORD* pdwARGB = new DWORD[m_dwHeight*m_dwWidth];
	if( m_bHasARGB )
	{
		memcpy( pdwARGB, m_imageARGB.m_pbyImageBuffer, m_dwWidth*m_dwHeight*sizeof(DWORD) );
		return (BYTE*)pdwARGB;
	}
	if( m_bHasRGB )
	{
		CJpgImage jpg;
		if( !jpg.JPGDecode( m_imageRGB.m_pbyImageBuffer, m_imageRGB.m_dwImageBufferSize ) )
		{
			if( pdwARGB )
				delete []pdwARGB;
			return NULL;
		}
		BYTE* rgb = jpg.GetData();
		for( int i = 0; i < m_dwHeight; i++ )
		{
			for( int j = 0; j < m_dwWidth; j++ )
			{
				BYTE r = rgb[(i*m_dwWidth+j)*3];
				BYTE g = rgb[(i*m_dwWidth+j)*3+1];
				BYTE b = rgb[(i*m_dwWidth+j)*3+2];

				pdwARGB[i*m_dwWidth+j] = r<<16|g<<8|b;
			}
		}
		jpg.Destroy();
	}
	if( m_bHasAlpha )
	{
		CJpgImage jpg;
		if( !jpg.JPGDecode( m_imageAlpha.m_pbyImageBuffer, m_imageAlpha.m_dwImageBufferSize ) )
		{
			assert( false );
			if( pdwARGB )
				delete []pdwARGB;
			return NULL;
		}
		BYTE* alpha = jpg.GetData();
		for( int i = 0; i < m_dwHeight; i++ )
		{
			for( int j = 0; j < m_dwWidth; j++ )
			{
				BYTE a = alpha[(i*m_dwWidth+j)*3];

				pdwARGB[i*m_dwWidth+j] |= a<<24;
			}
		}
		jpg.Destroy();
	}

	return (BYTE*)pdwARGB;
	unguard;
}
BOOL HR3D_PictureMipmaps::Read( HR3D_PicturePointer inP, int nSize )
{
	guardfunc;
	HR3D_PicturePointer p(inP.p);
	while( p.c < inP.c+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'mip0':
			{
				p.dw++;
				int size = *p.i++;
				HR3D_PictureMipmap mipmap;
				mipmap.Read( p, size );
				m_mipmaps.push_back( mipmap );
				p.c += size; 
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
				break;
			}
			break;
		}

	}
	return TRUE;
	unguard;	
}
BOOL HR3D_Picture::LoadFromFile( const char* pszFilename )
{
	guardfunc;
	HR3D_File fp;
	int nSize = 0;
	BOOL bOpen = FALSE;
	if( !fp.fopen( pszFilename, "rb" ) )
	{
		size_t size = 0;
		if (!g_TextureVFS.GetUnitLength(pszFilename, size))
		{
			return FALSE;
		}
		m_pbyMemory = new unsigned char[size];
		if (!g_TextureVFS.GetUnit(pszFilename, m_pbyMemory, size))
		{
			delete[] m_pbyMemory;
			m_pbyMemory = NULL;
			return FALSE;
		}
		nSize = size;
	//	dwSize = size;
		
	}
	else
	{
		m_pbyMemory = fp.GetBuffer();
		nSize = fp.GetBufferSize();
		bOpen = TRUE;
	}
	

	

	HR3D_PicturePointer p(m_pbyMemory);

	while( p.c < (char*)m_pbyMemory+nSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'hrp0':
			{
				p.dw++;
				int size = *p.i++;
				m_version.Read( p, size );
				p.c += size; 
			}
			break;
		case 'info':
			{
				p.dw++;
				int size = *p.i++;
				m_info.Read( p, size );
				p.c += size; 

			}
			break;
		case 'mips':
			{
				p.dw++;
				int size = *p.i++;
				m_mipmaps.Read( p, size );
				p.c += size; 

			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
				break;
			}
			break;

		}
	}
	if( bOpen )
		fp.fclose( false );
	return TRUE;
	unguard;
}

HR3D_Picture::~HR3D_Picture()
{
	guardfunc;
	if( m_pbyMemory )
	{
		delete []m_pbyMemory;
		m_pbyMemory = NULL;
	}
	unguard;
}

void HR3D_Picture::DetailShift( DWORD dwShift )
{
	guardfunc;
	m_dwDetailShift = dwShift;
	unguard;
}
BOOL HR3D_Picture::CreateTexture( LPDIRECT3DDEVICE8 pDevice, LPDIRECT3DTEXTURE8* ppTexture )
{
	guardfunc;
	LPDIRECT3DTEXTURE8 pTexture = NULL;
	DWORD dwSurfaceFormat = D3DFMT_A1R5G5B5;
	//if( m_info.m_dwSrcFileFormat == D3DXIFF_TGA )
		dwSurfaceFormat = D3DFMT_A8R8G8B8;

	if( pDevice->CreateTexture( 
				m_info.m_dwWidth>>m_dwDetailShift, 
				m_info.m_dwHeight>>m_dwDetailShift, 
				m_info.m_dwMipmapLevel-m_dwDetailShift, 
				0, (D3DFORMAT)dwSurfaceFormat, D3DPOOL_MANAGED, &pTexture ) != D3D_OK )
	{
		assert( false && "create hrp texture failed" );
		return FALSE;
	}
	for( int i = 0+m_dwDetailShift; i < m_info.m_dwMipmapLevel; i++ )
	{
		D3DLOCKED_RECT lr;

		HRESULT hr = pTexture->LockRect(i-m_dwDetailShift, &lr, NULL, 0);
		char *pp = (char*)lr.pBits;
		DWORD dwHeight = m_mipmaps.m_mipmaps[i].m_dwHeight;
		DWORD dwWidth = m_mipmaps.m_mipmaps[i].m_dwWidth;
		
		BYTE* timage = m_mipmaps.m_mipmaps[i].Decode( 0 );
		assert( timage );
		unsigned long index = 0, x = 0, y = 0;
		for (y=0; y < dwHeight; y++)
		{
			for (x=0; x < dwWidth; x++)
			{
				DWORD a = timage[(y*4*dwWidth)+4*x];
				DWORD r = timage[(y*4*dwWidth)+4*x+1];
				DWORD g = timage[(y*4*dwWidth)+4*x+2];
				DWORD b = timage[(y*4*dwWidth)+4*x+3];
				if( dwSurfaceFormat == D3DFMT_A8R8G8B8 )
				{
					pp[index++] = a;
					pp[index++] = r;
					pp[index++] = g;
					pp[index++] = b;
				}
				else
				{
					WORD c = 1<<15|(r>>3)<<10|(g>>3)<<5|(b>>3);
					pp[index++] = c&0x00ff;
					pp[index++] = (c&0xff00)>>8;
					
				}
				//pp[index++] = timage[(y*4*dwWidth)+4*x];
				//pp[index++] = timage[(y*4*dwWidth)+4*x+1];
				//pp[index++] = timage[(y*4*dwWidth)+4*x+2];
				//pp[index++] = timage[(y*4*dwWidth)+4*x+3];
			}
			if( dwSurfaceFormat == D3DFMT_A8R8G8B8 )
				index += lr.Pitch - (dwWidth*4);
			else
				index += lr.Pitch - (dwWidth*2);
		}
		pTexture->UnlockRect(i-m_dwDetailShift);
		delete []timage;

	}
	*ppTexture = pTexture;

	return TRUE;
	unguard;
}