#ifndef _ckf_tga_h
#define _ckf_tga_h
#include <windows.h>
class Tga
{
public:
	typedef struct 
    {
        BYTE IDLength;
        BYTE ColormapType;
        BYTE ImageType;
        BYTE ColormapSpecification[5];
        WORD XOrigin;
        WORD YOrigin;
        WORD ImageWidth;
        WORD ImageHeight;
        BYTE PixelDepth;
        BYTE ImageDescriptor;
    } TargaHeader;
protected:
	DWORD m_dwWidth;
	DWORD m_dwHeight;
	DWORD m_dwBPP;
	bool m_bHasAlpha;
	DWORD* m_pARGBBuffer;
public:
	Tga();
	virtual ~Tga();
	bool Create();
	void Destroy();

	bool LoadFromFile( const char* pszFilename );
	bool SaveToFile( const char* pszFilename );
	bool SaveToFile( DWORD* pARGBBuffer, int nWidth, int nHeight, const char* pszFilename );
	BOOL ReadInfo( BYTE* pbyBuffer, int nBufferSize );

	DWORD GetWidth(){ return m_dwWidth; }
	DWORD GetHeight(){ return m_dwHeight; }
	DWORD GetBPP(){ return m_dwBPP; }
	bool CreateImage( DWORD dwWidth, DWORD dwHeight, DWORD dwBpp );
	DWORD* GetARGBBuffer(){ return m_pARGBBuffer; }
	DWORD ReadPixel( int x, int y ){ return m_pARGBBuffer[y*m_dwWidth+x]; }
	void SetPixel( int x, int y, DWORD color ){ m_pARGBBuffer[y*m_dwWidth+x] = color; }
};



#endif