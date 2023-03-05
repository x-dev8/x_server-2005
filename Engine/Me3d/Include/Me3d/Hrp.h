#ifndef _hrp_h
#define _hrp_h
#include <windows.h>
#include <vector>
#include "Dxsdk/d3dx9.h"
union PicturePointer
{
	BYTE*			byte;
	bool*			boolean;
	int*			i;
	DWORD*			dw;
	char*			c;
	void*			p;
	float*			f;
	PicturePointer(void* in) :p(in)
	{
	}
};

class PictureVersion
{
public:
	PictureVersion():
		m_dwVersion(0){}
	DWORD	m_dwVersion;
	BOOL	Read( PicturePointer inP, int nSize );
};

class PictureInfo
{
public:
	PictureInfo():
		m_dwWidth(0),
		m_dwHeight(0),
		m_dwMipmapLevel(0){}
	DWORD	m_dwWidth;
	DWORD	m_dwHeight;
	DWORD	m_dwMipmapLevel;
	DWORD	m_dwSrcFileFormat;
	BOOL	Read( PicturePointer inP, int nSize );
};
class PictureImage
{
public:
	PictureImage():
		m_dwWidth(0),
		m_dwHeight(0),
		m_nQuality(0),
		m_dwFormat(0),
		m_dwCompressMethod(0),
		m_dwImageBufferSize(0),
		m_pbyImageBuffer(NULL){}
	~PictureImage();
	DWORD	m_dwWidth;
	DWORD	m_dwHeight;
	int		m_nQuality;
	DWORD	m_dwFormat;
	DWORD	m_dwCompressMethod;
	DWORD	m_dwImageBufferSize;
	BYTE*	m_pbyImageBuffer;
	BOOL	Read( PicturePointer inP, int nSize );


};
class PictureMipmap
{
public:
	PictureMipmap():
		m_dwWidth(0),
		m_dwHeight(0),
		m_bHasAlpha(FALSE),
		m_bHasRGB(FALSE),
		m_bHasARGB(FALSE)
		//m_bAllAlphaIs255(FALSE)
		{}
	DWORD	m_dwWidth;
	DWORD	m_dwHeight;
	BOOL	m_bHasRGB;
	BOOL	m_bHasAlpha;
	BOOL	m_bHasARGB;
	//BOOL	m_bAllAlphaIs255;
	PictureImage m_imageRGB;
	PictureImage m_imageAlpha;
	PictureImage m_imageARGB;
	BOOL	Read( PicturePointer inP, int nSize );
	// 把图形解码成目标格式
	BYTE*	Decode( DWORD dwFormat );
};
class PictureMipmaps
{
public:
	std::vector<PictureMipmap> m_mipmaps;
	BOOL	Read( PicturePointer inP, int nSize );
};
class Picture
{
public:
	enum
	{
		eMaxMipmapLevel = 16
	};
	enum
	{
		eCompressed_None,
		eCompressed_Jpeg,
		eCompressed_ZLib,
	};
	enum
	{
		eFormat_A8R8G8B8,
		eFormat_A1R5G5B5,
		eFormat_A4R4G4B4,
		eFormat_R8G8B8,
		eFormat_R5G6B5,
		eFromat_R5G5B5,
		eFormat_Index,
	};
public:
	Picture():
		m_pbyMemory(NULL)
		//m_dwWidth(0),
		//m_dwHeight(0),
		//m_dwMipmapLevel(0)
		{}
	~Picture();
	BOOL	LoadFromFile( const char* pszFilename );
	BOOL	CreateTexture( LPDIRECT3DDEVICE9 pd3dDevice, LPDIRECT3DTEXTURE9* ppTexture );
	static void	DetailShift( DWORD dwShift );
protected:
	BYTE*	m_pbyMemory;
	//DWORD	m_dwWidth;
	//DWORD	m_dwHeight;
	//DWORD	m_dwMipmapLevel;
	PictureVersion m_version;
	PictureInfo	m_info;
	PictureMipmaps m_mipmaps;
	static DWORD	m_dwDetailShift;
};

#endif