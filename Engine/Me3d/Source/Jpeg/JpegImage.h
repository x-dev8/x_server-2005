// CJpgImage.h: interface for the CJpgImage class.
//
//	缓存格式 X8R8B8G8, X1R5G5B5, X4R4G4B4 R5G6B5
//	图象格式 R8G8B8, A8R8G8B8, A1R5G5B5, A4R4G4B4, R5G6B5, L8, A8L8, P8, A8P8
//
//////////////////////////////////////////////////////////////////////

#ifndef _CJpgImage_H
#define _CJpgImage_H
#include <windows.h>


enum eImgFmt
{
	eImgFmt_UNKNOWN              = 0,

	eImgFmt_R8G8B8               = 1,
	eImgFmt_A8R8G8B8             = 2,
	eImgFmt_R5G6B5               = 3,
	eImgFmt_X1R5G5B5				= 4,
	eImgFmt_A1R5G5B5             = 5,
	eImgFmt_X4R4G4B4             = 6,
	eImgFmt_A4R4G4B4             = 7,
	eImgFmt_R3G3B2               = 8,
	eImgFmt_A8R3G3B2             = 9,

	eImgFmt_A8P8                 = 10,
	eImgFmt_P8                   = 11,
	eImgFmt_L8                   = 12,
	eImgFmt_A8L8                 = 13,

	eImgFmt_D32                  = 14,
	eImgFmt_D16                  = 15,

};

/****************************************************************************
 *			class CJpgImage  												*
 * Todo: All type can be read & write										*
 ****************************************************************************/
class CJpgImage
{
	
public:
	CJpgImage():	m_pData(NULL){}
	BOOL LoadFromFile( const char* pszFilename );
	DWORD* CreateARGBBuffer();
	BOOL ConvertTo( int nType );
	DWORD GetWidth(){ return m_Width; }
	DWORD GetHeight(){ return m_Height; }
	BOOL JPGDecode(LPBYTE pMemIn, DWORD dwLength);
	BYTE* GetData(){ return m_pData; }
	// Note: NOT ALL SPECIFID FORMAT CAN BE GOT!!!!
	// if this bitmap can be converted to specified format,
	// a default format be setted.
	// Normally, any bitmap type can be converted to true
	// or hi-color, but a true or hi-color image can't be
	// convert to index or gray format.
	// Image destroyer
	void Destroy();			// Destroy Image
protected:
	UINT			m_nChannels;
	UINT			m_nAnimates;
	UINT			m_nCubeFaces;
	UINT			m_nVolumes;
	UINT			m_nMipLevels;

	UINT			m_Width;
	UINT			m_Height;
	UINT			m_Pitch;
	UINT			m_BytesPerPixel;
	eImgFmt			m_Format;

	DWORD			m_Bytes;
	LPBYTE			m_pData;
	UINT			m_nPalettes;
	LPPALETTEENTRY	m_pPalette;

};

#endif // !_CJpgImage_H
