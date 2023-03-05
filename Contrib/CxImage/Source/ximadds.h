/*
 * File:	ximadds.h
 * Purpose:	DDS Image Class Loader and Writer
 * 说明，只能处理DTX1,DTX3,DTX5
 */

#if !defined(__ximaDDS_h)
#define __ximaDDS_h

#include "ximage.h"

#if CXIMAGE_SUPPORT_DDS

typedef struct ddsColorBlock_s
{
	unsigned short		colors[ 2 ];
	unsigned char		row[ 4 ];
}
ddsColorBlock_t;


typedef struct ddsColor_s
{
	unsigned char		r, g, b, a;
}
ddsColor_t;

typedef struct ddsAlphaBlockExplicit_s
{
	unsigned short		row[ 4 ];
}
ddsAlphaBlockExplicit_t;


typedef struct ddsAlphaBlock3BitLinear_s
{
	unsigned char		alpha0;
	unsigned char		alpha1;
	unsigned char		stuff[ 6 ];
}
ddsAlphaBlock3BitLinear_t;


class CxImageDDS: public CxImage
{
public:
	CxImageDDS(): CxImage(CXIMAGE_FORMAT_DDS) {}

#if CXIMAGE_SUPPORT_DECODE
	bool Decode(CxFile * hFile);
	bool Decode(FILE *hFile) { CxIOFile file(hFile); return Decode(&file); }
#endif // CXIMAGE_SUPPORT_DECODE

#if CXIMAGE_SUPPORT_ENCODE
	bool Encode(CxFile * hFile);
	bool Encode(FILE *hFile) { CxIOFile file(hFile); return Encode(&file); }
#endif // CXIMAGE_SUPPORT_ENCODE

protected:

#if CXIMAGE_SUPPORT_DECODE
	int DDSDecompressDXT1( unsigned char *src, int width, int height, unsigned char *dest );
	int DDSDecompressDXT3( unsigned char *src, int width, int height, unsigned char *dest );
	int DDSDecompressDXT5( unsigned char *src, int width, int height, unsigned char *dest );
	
	void DDSGetColorBlockColors( ddsColorBlock_t *block, ddsColor_t colors[ 4 ] );
	void DDSDecodeColorBlock( unsigned int *pixel, ddsColorBlock_t *block, int width, unsigned int colors[ 4 ] );
	void DDSDecodeAlphaExplicit( unsigned int *pixel, ddsAlphaBlockExplicit_t *alphaBlock, int width, unsigned int alphaZero );
	void DDSDecodeAlpha3BitLinear( unsigned int *pixel, ddsAlphaBlock3BitLinear_t *alphaBlock, int width, unsigned int alphaZero );

#endif // CXIMAGE_SUPPORT_DECODE

};

#endif

#endif
