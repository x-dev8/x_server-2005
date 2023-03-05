/*
 * File:	ximadds.cpp
 * Purpose:	Platform Independent DDS Image Class Loader and Writer
 */

#include "ximadds.h"

#if CXIMAGE_SUPPORT_DDS

#include "ximaiter.h"

enum DDS_Format
{
	FORMAT_UNKNOWN,
	FORMAT_DXT1,	/// opaque or 1-bit alpha
	FORMAT_DXT3,	/// explicit alpha
	FORMAT_DXT5,	/// interpolated alpha
};

enum DDS_Flags {
	DDSD_CAPS			= 0x00000001, 
	DDSD_HEIGHT			= 0x00000002, 
	DDSD_WIDTH			= 0x00000004, 
	DDSD_PITCH			= 0x00000008, 
	DDSD_PIXELFORMAT	= 0x00001000, 
	DDSD_MIPMAPCOUNT	= 0x00020000, 
	DDSD_LINEARSIZE		= 0x00080000, 
	DDSD_DEPTH			= 0x00800000, 
};

enum DDS_PixelFormat_Flags {
	DDPF_ALPHAPIXELS	= 0x00000001, 
	DDPF_FOURCC			= 0x00000004, 
	DDPF_RGB			= 0x00000040, 
};

#if CXIMAGE_SUPPORT_DECODE


/* endian tomfoolery */
typedef union
{
	float	f;
	char	c[ 4 ];
}
floatSwapUnion;

#ifndef __BIG_ENDIAN__
#ifdef _SGI_SOURCE
#define	__BIG_ENDIAN__
#endif
#endif


#ifdef __BIG_ENDIAN__

int   DDSBigLong( int src ) { return src; }
short DDSBigShort( short src ) { return src; }
float DDSBigFloat( float src ) { return src; }

int DDSLittleLong( int src )
{
	return ((src & 0xFF000000) >> 24) |
		((src & 0x00FF0000) >> 8) |
		((src & 0x0000FF00) << 8) |
		((src & 0x000000FF) << 24);
}

short DDSLittleShort( short src )
{
	return ((src & 0xFF00) >> 8) |
		((src & 0x00FF) << 8);
}

float DDSLittleFloat( float src )
{
	floatSwapUnion in,out;
	in.f = src;
	out.c[ 0 ] = in.c[ 3 ];
	out.c[ 1 ] = in.c[ 2 ];
	out.c[ 2 ] = in.c[ 1 ];
	out.c[ 3 ] = in.c[ 0 ];
	return out.f;
}

#else /*__BIG_ENDIAN__*/

int   DDSLittleLong( int src ) { return src; }
short DDSLittleShort( short src ) { return src; }
float DDSLittleFloat( float src ) { return src; }

int DDSBigLong( int src )
{
	return ((src & 0xFF000000) >> 24) |
		((src & 0x00FF0000) >> 8) |
		((src & 0x0000FF00) << 8) |
		((src & 0x000000FF) << 24);
}

short DDSBigShort( short src )
{
	return ((src & 0xFF00) >> 8) |
		((src & 0x00FF) << 8);
}

float DDSBigFloat( float src )
{
	floatSwapUnion in,out;
	in.f = src;
	out.c[ 0 ] = in.c[ 3 ];
	out.c[ 1 ] = in.c[ 2 ];
	out.c[ 2 ] = in.c[ 1 ];
	out.c[ 3 ] = in.c[ 0 ];
	return out.f;
}

#endif /*__BIG_ENDIAN__*/


bool CxImageDDS::Decode(CxFile * hFile)
{
	if (hFile == NULL) return false;

	DWORD off = hFile->Tell(); //<CSC>
	try
	{
		const char		ddsMagic[] = "DDS ";		
		char			magic[4];

		if (hFile->Read(&magic,sizeof(char)*4,1)==0) throw "Not a DDS";
		if ( memcmp( &magic, &ddsMagic, 4 ) != 0 ) throw "Not a DDS";

		char header[124];
		if (hFile->Read(&header,sizeof(char)*124,1)==0) throw "Not a DDS";

		// shortcut to parameters

		DWORD* dwSize			= (DWORD*)&header[0];
		DWORD* dwFlags			= (DWORD*)&header[4];
		DWORD* dwHeight			= (DWORD*)&header[8];
		DWORD* dwWidth			= (DWORD*)&header[12];
		DWORD* dwPitchOrSize	= (DWORD*)&header[16];
		//	DWORD* dwDepth		= (DWORD*)&header[20];  // Volume depth
		DWORD* dwMipMapCount	= (DWORD*)&header[24];

		char*  ddPixelFormat		= &header[28 + 4*11];		
		DWORD* pfSize			= (DWORD*)ddPixelFormat;
		DWORD* pfFlags			= (DWORD*)&ddPixelFormat[4];
		char*  pfFourCC			= &ddPixelFormat[8];
		DWORD* pfRGBBitCount	= (DWORD*)&ddPixelFormat[12];
		DWORD* pfRBitMask		= (DWORD*)&ddPixelFormat[16];
		DWORD* pfGBitMask		= (DWORD*)&ddPixelFormat[20];
		DWORD* pfBBitMask		= (DWORD*)&ddPixelFormat[24];
		DWORD* pfAlphaBitMask	= (DWORD*)&ddPixelFormat[28];

		char*  ddsCaps			= &header[28 + 4*11 + 32];
		DWORD* dwCaps1			= (DWORD*)ddsCaps;
		DWORD* dwCaps2			= (DWORD*)&ddsCaps[4];

		// translate image dimensions

		if ( *dwSize != 124 )	throw "Not a DDS";

		// translate pixelformat

		if ( *pfSize != 32 )	throw "Not a DDS";

		int width		= 0;
		int height		= 0;
		int pitch		= 0;
		int mipmaplevels = 0;
		int datasize	= 0;
		int mindatasize = 1;
		DDS_Format format = FORMAT_UNKNOWN;

		if ( *dwFlags & DDSD_WIDTH )
			width = (int)*dwWidth;		
		if ( *dwFlags & DDSD_HEIGHT )
			height = (int)*dwHeight;

		if ( *dwFlags & DDSD_PITCH )
		{
			pitch = (int)*dwPitchOrSize;
			datasize = pitch * height;
		}
		else if ( *dwFlags & DDSD_LINEARSIZE )
		{
			datasize = (int)*dwPitchOrSize;
		}
		else
		{
			if ( *pfFlags & DDPF_FOURCC )
			{
				datasize = __max(1, width / 4) * __max(1, height / 4) * 8;
				if ( memcmp(pfFourCC, "DXT1", 4) != 0 ) 
					datasize *= 2; 
			}
			else 
				if ( ( *dwFlags & DDSD_WIDTH ) && ( *dwFlags & DDSD_HEIGHT ) && ( *dwFlags & DDSD_PIXELFORMAT ) )
					datasize = (int)*dwHeight * (int)*dwWidth * ( ((int)*pfRGBBitCount) >> 3 );
		}

		if ( *dwFlags & DDSD_MIPMAPCOUNT )
			mipmaplevels = (int)*dwMipMapCount;

		if ( datasize == 0 )
		{
			throw "Not a DDS";
		}

		// 读取图片内容
		unsigned char* srcBuf = new unsigned char[datasize];
		if (hFile->Read(srcBuf, datasize, 1)==0) throw "Not a DDS";

		unsigned char* dscBuf = new unsigned char[width*height*4];

		if ( *pfFlags & DDPF_FOURCC )
		{
			if (memcmp(pfFourCC, "DXT1", 4) == 0 )
			{
				format = FORMAT_DXT1;
				pitch = width * 2;
				mindatasize = 8;
				DDSDecompressDXT1( srcBuf, width, height, dscBuf );
			}
			else if (memcmp(pfFourCC, "DXT3", 4) == 0 )
			{
				format = FORMAT_DXT3;
				pitch = width * 4;
				mindatasize = 16;
				DDSDecompressDXT3( srcBuf, width, height, dscBuf );
			}
			else if (memcmp(pfFourCC, "DXT5", 4) == 0 )
			{
				format = FORMAT_DXT5;
				pitch = width * 4;
				mindatasize = 16;
				DDSDecompressDXT5( srcBuf, width, height, dscBuf );
			}
			else
			{
				throw "Not a DDS";
			}
		}	

		delete []srcBuf;


		// 创建数据结构
		if (!Create(width,height,24,CXIMAGE_FORMAT_DDS))
			throw "Can't allocate memory";
		
		unsigned char* p = NULL;
		unsigned char* q = NULL;
		for ( int i=0; i<height; i++ )
		{
			p = info.pImage + info.dwEffWidth*i;
			q = dscBuf + width*4*i;
			for ( int j=0; j<width; j++ )
			{
				*p = *(q+2);
				*(p+1) = *(q+1);
				*(p+2) = *q;
				//memcpy(p, q, 3);
				p+=3;
				q+=4;
			}
		}

		delete []dscBuf;
		return true;
	} 
	catch (char *message)
	{
		strncpy(info.szLastError,message,255);
		if (info.nEscape==-1) return true;
		return false;
	}

	return false;
}


/*
DDSDecompressDXT1()
decompresses a dxt1 format texture
*/

int CxImageDDS::DDSDecompressDXT1( unsigned char *src, int width, int height, unsigned char *dest )
{
	int				x, y, xBlocks, yBlocks;
	unsigned int	*pixel;
	ddsColorBlock_t	*block;
	ddsColor_t		colors[ 4 ];


	/* setup */
	xBlocks = width / 4;
	yBlocks = height / 4;

	/* walk y */
	for( y = 0; y < yBlocks; y++ )
	{
		/* 8 bytes per block */
		block = (ddsColorBlock_t*) ((unsigned int) src + y * xBlocks * 8);

		/* walk x */
		for( x = 0; x < xBlocks; x++, block++ )
		{
			DDSGetColorBlockColors( block, colors );
			pixel = (unsigned int*) (dest + x * 16 + (y * 4) * width * 4);
			DDSDecodeColorBlock( pixel, block, width, (unsigned int*) colors );
		}
	}

	/* return ok */
	return 0;
}



/*
DDSGetColorBlockColors()
extracts colors from a dds color block
*/

void CxImageDDS::DDSGetColorBlockColors( ddsColorBlock_t *block, ddsColor_t colors[ 4 ] )
{
	unsigned short		word;


	/* color 0 */
	word = DDSLittleShort( block->colors[ 0 ] );
	colors[ 0 ].a = 0xff;

	/* extract rgb bits */
	colors[ 0 ].b = (unsigned char)(word & 0xFF);
	colors[ 0 ].b <<= 3;
	colors[ 0 ].b |= (colors[ 0 ].b >> 5);
	word >>= 5;
	colors[ 0 ].g = (unsigned char)(word & 0xFF);
	colors[ 0 ].g <<= 2;
	colors[ 0 ].g |= (colors[ 0 ].g >> 5);
	word >>= 6;
	colors[ 0 ].r = (unsigned char)(word & 0xFF);
	colors[ 0 ].r <<= 3;
	colors[ 0 ].r |= (colors[ 0 ].r >> 5);

	/* same for color 1 */
	word = DDSLittleShort( block->colors[ 1 ] );
	colors[ 1 ].a = 0xff;

	/* extract rgb bits */
	colors[ 1 ].b = (unsigned char)(word & 0xFF);
	colors[ 1 ].b <<= 3;
	colors[ 1 ].b |= (colors[ 1 ].b >> 5);
	word >>= 5;
	colors[ 1 ].g = (unsigned char)(word & 0xFF);
	colors[ 1 ].g <<= 2;
	colors[ 1 ].g |= (colors[ 1 ].g >> 5);
	word >>= 6;
	colors[ 1 ].r = (unsigned char)(word & 0xFF);
	colors[ 1 ].r <<= 3;
	colors[ 1 ].r |= (colors[ 1 ].r >> 5);

	/* use this for all but the super-freak math method */
	if( block->colors[ 0 ] > block->colors[ 1 ] )
	{
		/* four-color block: derive the other two colors.    
		00 = color 0, 01 = color 1, 10 = color 2, 11 = color 3
		these two bit codes correspond to the 2-bit fields 
		stored in the 64-bit block. */

		word = ((unsigned short) colors[ 0 ].r * 2 + (unsigned short) colors[ 1 ].r ) / 3;
		/* no +1 for rounding */
		/* as bits have been shifted to 888 */
		colors[ 2 ].r = (unsigned char) word;
		word = ((unsigned short) colors[ 0 ].g * 2 + (unsigned short) colors[ 1 ].g) / 3;
		colors[ 2 ].g = (unsigned char) word;
		word = ((unsigned short) colors[ 0 ].b * 2 + (unsigned short) colors[ 1 ].b) / 3;
		colors[ 2 ].b = (unsigned char) word;
		colors[ 2 ].a = 0xff;

		word = ((unsigned short) colors[ 0 ].r + (unsigned short) colors[ 1 ].r * 2) / 3;
		colors[ 3 ].r = (unsigned char) word;
		word = ((unsigned short) colors[ 0 ].g + (unsigned short) colors[ 1 ].g * 2) / 3;
		colors[ 3 ].g = (unsigned char) word;
		word = ((unsigned short) colors[ 0 ].b + (unsigned short) colors[ 1 ].b * 2) / 3;
		colors[ 3 ].b = (unsigned char) word;
		colors[ 3 ].a = 0xff;
	} else {
		/* three-color block: derive the other color.
		00 = color 0, 01 = color 1, 10 = color 2,  
		11 = transparent.
		These two bit codes correspond to the 2-bit fields 
		stored in the 64-bit block */

		word = ((unsigned short) colors[ 0 ].r + (unsigned short) colors[ 1 ].r) / 2;
		colors[ 2 ].r = (unsigned char)(word & 0xFF);
		word = ((unsigned short) colors[ 0 ].g + (unsigned short) colors[ 1 ].g) / 2;
		colors[ 2 ].g = (unsigned char)(word & 0xFF);
		word = ((unsigned short) colors[ 0 ].b + (unsigned short) colors[ 1 ].b) / 2;
		colors[ 2 ].b = (unsigned char)(word & 0xFF);
		colors[ 2 ].a = 0xff;

		/* random color to indicate alpha */
		colors[ 3 ].r = 0x00;
		colors[ 3 ].g = 0xff;
		colors[ 3 ].b = 0xff;
		colors[ 3 ].a = 0x00;
	}
}


/*
DDSDecompressDXT3()
decompresses a dxt3 format texture
*/

int CxImageDDS::DDSDecompressDXT3(unsigned char *src, int width, int height, unsigned char *dest )
{
	int						x, y, xBlocks, yBlocks;
	unsigned int			*pixel, alphaZero;
	ddsColorBlock_t			*block;
	ddsAlphaBlockExplicit_t	*alphaBlock;
	ddsColor_t				colors[ 4 ];


	/* setup */
	xBlocks = width / 4;
	yBlocks = height / 4;

	/* create zero alpha */
	colors[ 0 ].a = 0;
	colors[ 0 ].r = 0xFF;
	colors[ 0 ].g = 0xFF;
	colors[ 0 ].b = 0xFF;
	alphaZero = *((unsigned int*) &colors[ 0 ]);

	/* walk y */
	for( y = 0; y < yBlocks; y++ )
	{
		/* 8 bytes per block, 1 block for alpha, 1 block for color */
		block = (ddsColorBlock_t*) ((unsigned int) src + y * xBlocks * 16);

		/* walk x */
		for( x = 0; x < xBlocks; x++, block++ )
		{
			/* get alpha block */
			alphaBlock = (ddsAlphaBlockExplicit_t*) block;

			/* get color block */
			block++;
			DDSGetColorBlockColors( block, colors );

			/* decode color block */
			pixel = (unsigned int*) (dest + x * 16 + (y * 4) * width * 4);
			DDSDecodeColorBlock( pixel, block, width, (unsigned int*) colors );

			/* overwrite alpha bits with alpha block */
			DDSDecodeAlphaExplicit( pixel, alphaBlock, width, alphaZero );
		}
	}

	/* return ok */
	return 0;
}



/*
DDSDecompressDXT5()
decompresses a dxt5 format texture
*/

int CxImageDDS::DDSDecompressDXT5( unsigned char *src, int width, int height, unsigned char *dest )
{
	int							 x, y, xBlocks, yBlocks;
	unsigned int				*pixel, alphaZero;
	ddsColorBlock_t				*block;
	ddsAlphaBlock3BitLinear_t	*alphaBlock;
	ddsColor_t					 colors[ 4 ];


	/* setup */
	xBlocks = width / 4;
	yBlocks = height / 4;

	/* create zero alpha */
	colors[ 0 ].a = 0;
	colors[ 0 ].r = 0xFF;
	colors[ 0 ].g = 0xFF;
	colors[ 0 ].b = 0xFF;
	alphaZero = *((unsigned int*) &colors[ 0 ]);

	/* walk y */
	for( y = 0; y < yBlocks; y++ )
	{
		/* 8 bytes per block, 1 block for alpha, 1 block for color */
		block = (ddsColorBlock_t*) ((unsigned int) src + y * xBlocks * 16);

		/* walk x */
		for( x = 0; x < xBlocks; x++, block++ )
		{
			/* get alpha block */
			alphaBlock = (ddsAlphaBlock3BitLinear_t*) block;

			/* get color block */
			block++;
			DDSGetColorBlockColors( block, colors );

			/* decode color block */
			pixel = (unsigned int*) (dest + x * 16 + (y * 4) * width * 4);
			DDSDecodeColorBlock( pixel, block, width, (unsigned int*) colors );

			/* overwrite alpha bits with alpha block */
			DDSDecodeAlpha3BitLinear( pixel, alphaBlock, width, alphaZero );
		}
	}

	/* return ok */
	return 0;
}



/*
DDSDecodeAlpha3BitLinear()
decodes interpolated alpha block
*/

void CxImageDDS::DDSDecodeAlpha3BitLinear( unsigned int *pixel, ddsAlphaBlock3BitLinear_t *alphaBlock, int width, unsigned int alphaZero )
{

	int					row, pix;
	unsigned int		stuff;
	unsigned char		bits[ 4 ][ 4 ];
	unsigned short		alphas[ 8 ];
	ddsColor_t			aColors[ 4 ][ 4 ];


	/* get initial alphas */
	alphas[ 0 ] = alphaBlock->alpha0;
	alphas[ 1 ] = alphaBlock->alpha1;

	/* 8-alpha block */
	if( alphas[ 0 ] > alphas[ 1 ] )
	{
		/* 000 = alpha_0, 001 = alpha_1, others are interpolated */
		alphas[ 2 ] = ( 6 * alphas[ 0 ] +     alphas[ 1 ]) / 7;	/* bit code 010 */
		alphas[ 3 ] = ( 5 * alphas[ 0 ] + 2 * alphas[ 1 ]) / 7;	/* bit code 011 */
		alphas[ 4 ] = ( 4 * alphas[ 0 ] + 3 * alphas[ 1 ]) / 7;	/* bit code 100 */
		alphas[ 5 ] = ( 3 * alphas[ 0 ] + 4 * alphas[ 1 ]) / 7;	/* bit code 101 */
		alphas[ 6 ] = ( 2 * alphas[ 0 ] + 5 * alphas[ 1 ]) / 7;	/* bit code 110 */
		alphas[ 7 ] = (     alphas[ 0 ] + 6 * alphas[ 1 ]) / 7;	/* bit code 111 */
	}

	/* 6-alpha block */
	else
	{ 
		/* 000 = alpha_0, 001 = alpha_1, others are interpolated */
		alphas[ 2 ] = (4 * alphas[ 0 ] +     alphas[ 1 ]) / 5;	/* bit code 010 */
		alphas[ 3 ] = (3 * alphas[ 0 ] + 2 * alphas[ 1 ]) / 5;	/* bit code 011 */
		alphas[ 4 ] = (2 * alphas[ 0 ] + 3 * alphas[ 1 ]) / 5;	/* bit code 100 */
		alphas[ 5 ] = (    alphas[ 0 ] + 4 * alphas[ 1 ]) / 5;	/* bit code 101 */
		alphas[ 6 ] = 0;										/* bit code 110 */
		alphas[ 7 ] = 255;										/* bit code 111 */
	}

	/* decode 3-bit fields into array of 16 bytes with same value */

	/* first two rows of 4 pixels each */
	stuff = *((unsigned int*) &(alphaBlock->stuff[ 0 ]));

	bits[ 0 ][ 0 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 0 ][ 1 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 0 ][ 2 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 0 ][ 3 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 1 ][ 0 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 1 ][ 1 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 1 ][ 2 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 1 ][ 3 ] = (unsigned char) (stuff & 0x00000007);

	/* last two rows */
	stuff = *((unsigned int*) &(alphaBlock->stuff[ 3 ])); /* last 3 bytes */

	bits[ 2 ][ 0 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 2 ][ 1 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 2 ][ 2 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 2 ][ 3 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 3 ][ 0 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 3 ][ 1 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 3 ][ 2 ] = (unsigned char) (stuff & 0x00000007);
	stuff >>= 3;
	bits[ 3 ][ 3 ] = (unsigned char) (stuff & 0x00000007);

	/* decode the codes into alpha values */
	for( row = 0; row < 4; row++ )
	{
		for( pix=0; pix < 4; pix++ )
		{
			aColors[ row ][ pix ].r = 0;
			aColors[ row ][ pix ].g = 0;
			aColors[ row ][ pix ].b = 0;
			aColors[ row ][ pix ].a = (unsigned char) alphas[ bits[ row ][ pix ] ];
		}
	}

	/* write out alpha values to the image bits */
	for( row = 0; row < 4; row++, pixel += width-4 )
	{
		for( pix = 0; pix < 4; pix++ )
		{
			/* zero the alpha bits of image pixel */
			*pixel &= alphaZero;

			/* or the bits into the prev. nulled alpha */
			*pixel |= *((unsigned int*) &(aColors[ row ][ pix ]));	
			pixel++;
		}
	}
}

/*
DDSDecodeColorBlock()
decodes a dds color block
fixme: make endian-safe
*/

void CxImageDDS::DDSDecodeColorBlock( unsigned int *pixel, ddsColorBlock_t *block, int width, unsigned int colors[ 4 ] )
{
	int				r, n;
	unsigned int	bits;
	unsigned int	masks[] = { 3, 12, 3 << 4, 3 << 6 };	/* bit masks = 00000011, 00001100, 00110000, 11000000 */
	int				shift[] = { 0, 2, 4, 6 };


	/* r steps through lines in y */
	for( r = 0; r < 4; r++, pixel += (width - 4) )	/* no width * 4 as unsigned int ptr inc will * 4 */
	{
		/* width * 4 bytes per pixel per line, each j dxtc row is 4 lines of pixels */

		/* n steps through pixels */
		for( n = 0; n < 4; n++ )
		{
			bits = block->row[ r ] & masks[ n ];
			bits >>= shift[ n ];

			switch( bits )
			{
			case 0:
				*pixel = colors[ 0 ];
				pixel++;
				break;

			case 1:
				*pixel = colors[ 1 ];
				pixel++;
				break;

			case 2:
				*pixel = colors[ 2 ];
				pixel++;
				break;

			case 3:
				*pixel = colors[ 3 ];
				pixel++;
				break;

			default:
				/* invalid */
				pixel++;
				break;
			}
		}
	}
}



/*
DDSDecodeAlphaExplicit()
decodes a dds explicit alpha block
*/

void CxImageDDS::DDSDecodeAlphaExplicit( unsigned int *pixel, ddsAlphaBlockExplicit_t *alphaBlock, int width, unsigned int alphaZero )
{	
	int				row, pix;
	unsigned short	word;
	ddsColor_t		color;


	/* clear color */
	color.r = 0;
	color.g = 0;
	color.b = 0;

	/* walk rows */
	for( row = 0; row < 4; row++, pixel += (width - 4) )
	{
		word = DDSLittleShort( alphaBlock->row[ row ] );

		/* walk pixels */
		for( pix = 0; pix < 4; pix++ )
		{
			/* zero the alpha bits of image pixel */
			*pixel &= alphaZero;
			color.a = unsigned char(word & 0x000F);
			color.a = color.a | (color.a << 4);
			*pixel |= *((unsigned int*) &color);
			word >>= 4;		/* move next bits to lowest 4 */
			pixel++;		/* move to next pixel in the row */

		}
	}
}


#endif // CXIMAGE_SUPPORT_DECODE

#if CXIMAGE_SUPPORT_ENCODE
bool CxImageDDS::Encode(CxFile * hFile)
{
	return false;
}
#endif // CXIMAGE_SUPPORT_ENCODE

#endif