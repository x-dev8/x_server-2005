#include <assert.h>
#include <stdio.h>
#include <vector>
#include "tga.h"
#include "FuncPerformanceLog.h"
#include "packet_interface.h"
//#include "MemoryManager.h"	// ÄÚ´æ¹ÜÀí
//#include "Launcher/DataLauncher.h"



Tga::Tga()
{
	guardfunc;
	m_dwWidth = 0;
	m_dwHeight = 0;
	m_dwBPP = 0;
	m_bHasAlpha = false;
	m_pARGBBuffer = 0;
	unguard;
}

Tga::~Tga()
{
	guardfunc;
	assert( m_pARGBBuffer == 0 );
	unguard;
}

bool Tga::Create()
{
	guardfunc;
	return true;
	unguard;
}

void Tga::Destroy()
{
	guardfunc;
	if( m_pARGBBuffer )
	{
		delete []m_pARGBBuffer;
		m_pARGBBuffer = 0;
		m_dwWidth = 0;
		m_dwHeight = 0;
		m_dwBPP = 0;
		m_bHasAlpha = false;
	}
	unguard;
}

bool Tga::CreateImage( DWORD dwWidth, DWORD dwHeight, DWORD dwBpp )
{
	guardfunc;
	Destroy();
	if( dwBpp%8 != 0 )
		return false;
	
	m_dwWidth = dwWidth;
	m_dwHeight = dwHeight;
	//m_dwBPP = dwBpp;
	m_dwBPP = 32;
	m_pARGBBuffer = new DWORD[m_dwHeight*m_dwWidth];
	return true;
	unguard;
}
BOOL Tga::ReadInfo( BYTE* pbyBuffer, int nBufferSize )
{
	TargaHeader	header;
	memcpy( &header , pbyBuffer, sizeof(TargaHeader) ) ;
	m_dwWidth	= header.ImageWidth;
	m_dwHeight	= header.ImageHeight;
	m_dwBPP		= header.PixelDepth;
	return TRUE;

}
bool Tga::LoadFromFile(	const char*	pszFilename	)
{
	guardfunc;
	Destroy();

	f_Handle* file = packet_namespace::w_fopen(	pszFilename, "rb" );
	if(	NULL ==	file )
		return false;

	TargaHeader	header;
	packet_namespace::w_fread( &header, sizeof(TargaHeader), 1, file );

	// Only	true color,	non-mapped images are supported
	if(	( 0	!= header.ColormapType	) || 
		( header.ImageType	!= 10 && header.ImageType != 2	) )
	{
		packet_namespace::w_fclose(	file );
		return false;
	}

	// Skip	the	ID field. The first	byte of	the	header is the length of	this field
	if(	header.IDLength )
		packet_namespace::w_fseek( file, header.IDLength, SEEK_CUR	);

	m_dwWidth	= header.ImageWidth;
	m_dwHeight	= header.ImageHeight;
	m_dwBPP		= header.PixelDepth;
	m_pARGBBuffer =	new	DWORD[m_dwWidth*m_dwHeight];

	if(	m_pARGBBuffer	== NULL	)
	{
		packet_namespace::w_fclose(file);
		return false;
	}

	for( DWORD y=0;	y<m_dwHeight; y++ )
	{
		DWORD dwOffset = y*m_dwWidth;

		if(	0 == ( header.ImageDescriptor & 0x0020	) )
			dwOffset = (m_dwHeight-y-1)*m_dwWidth;

		for( DWORD x=0;	x<m_dwWidth; x )
		{
			if(	header.ImageType == 10	)
			{
				BYTE PacketInfo	= packet_namespace::w_getc(	file );
				WORD PacketType	= 0x80 & PacketInfo;
				WORD PixelCount	= (	0x007f & PacketInfo	) +	1;

				if(	PacketType )
				{
					DWORD b	= packet_namespace::w_getc(	file );
					DWORD g	= packet_namespace::w_getc(	file );
					DWORD r	= packet_namespace::w_getc(	file );
					DWORD a	= 0xff;
					if(	m_dwBPP	== 32 )
						a =	packet_namespace::w_getc( file );

					while( PixelCount--	)
					{
						m_pARGBBuffer[dwOffset+x]	= (a<<24)+(r<<16L)+(g<<8L)+(b<<0L);
						x++;
					}
				}
				else
				{
					while( PixelCount--	)
					{
						BYTE b = packet_namespace::w_getc( file	);
						BYTE g = packet_namespace::w_getc( file	);
						BYTE r = packet_namespace::w_getc( file	);
						BYTE a = 0xff;
						if(	m_dwBPP	== 32 )
							a =	packet_namespace::w_getc( file );

						m_pARGBBuffer[dwOffset+x]	= (a<<24)+(r<<16L)+(g<<8L)+(b<<0L);
						x++;
					}
				}
			}
			else
			{
				BYTE b = packet_namespace::w_getc( file	);
				BYTE g = packet_namespace::w_getc( file	);
				BYTE r = packet_namespace::w_getc( file	);
				BYTE a = 0xff;
				if(	m_dwBPP	== 32 )
					a =	packet_namespace::w_getc( file );

				m_pARGBBuffer[dwOffset+x]	= (a<<24)+(r<<16L)+(g<<8L)+(b<<0L);
				x++;
			}
		}
	}

	packet_namespace::w_fclose(	file );

	// Check for alpha content
	for( DWORD i=0;	i<(m_dwWidth*m_dwHeight); i++ )
	{
		if(	( m_pARGBBuffer[i] & 0xff000000 ) != 0xff000000 )
		{
			m_bHasAlpha =	TRUE;
			break;
		}
	}
	return true;
	unguard;
}

bool Tga::SaveToFile( const char* pszFilename )
{
	guardfunc;
	TargaHeader	header;
	header.IDLength = 0;
	header.ColormapType = 0;
	header.ImageType = 0x02;
	memset( header.ColormapSpecification, 0x00, sizeof( header.ColormapSpecification ) );
	header.XOrigin = 0;
	header.YOrigin = 0;
	header.ImageWidth = (WORD)m_dwWidth;
	header.ImageHeight = (WORD)m_dwHeight;
	header.PixelDepth = 32;
	header.ImageDescriptor = 0x08;

	FILE* fp = fopen( pszFilename, "wb" );
	if( fp == 0 )
		return false;
	fwrite( &header, sizeof( header ), 1, fp );
	for( int y = m_dwHeight-1; y >= 0; y-- )
		//for( int y = 0; y < m_dwHeight; y++ )
		fwrite( &m_pARGBBuffer[y*m_dwWidth], sizeof( DWORD )*m_dwWidth, 1, fp );
	fclose( fp );
	return true;
	unguard;
}



