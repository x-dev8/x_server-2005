#include <windows.h>
#include <stdio.h>
#include "filepackage.h"
CFilePackage::CFilePackage(void)
{
	m_hZip = 0;
}

CFilePackage::~CFilePackage(void)
{
	if( m_hZip )
	{
		CloseZip( m_hZip );
		m_hZip = 0;
	}
}

BOOL CFilePackage::Open( const char* pszFilename )
{
	m_hZip = OpenZip( (void*)pszFilename, 0, ZIP_FILENAME );
	if( m_hZip != 0 )
		return TRUE;
	return FALSE;
}

int CFilePackage::LoadFileToMemory( const char* pszFilename, BYTE** ppBuffer )
{
	FILE* fp = fopen( pszFilename, "rb" );
	if( fp == 0 )
		return false;
	fseek ( fp, 0, SEEK_END );
	DWORD dwFileSize = ftell( fp );
	if( dwFileSize == 0 )
	{
		fclose( fp );
		return 0;
	}
	BYTE* pBuffer = new BYTE[dwFileSize];
	rewind( fp );
	fread( pBuffer, dwFileSize, 1, fp );
	fclose( fp );
	*ppBuffer = pBuffer;
	return dwFileSize;
}

BOOL CFilePackage::UnPack( const char* pszFilename, BYTE** ppbyBuffer, DWORD* pdwSize )
{
#ifdef _UNICODE
	ZIPENTRYW ze;
#else
	ZIPENTRY ze; 
#endif

	memset(&ze, 0, sizeof(ze));
	int index = -1;
	ZRESULT zr = 0;

	//zr = FindZipItem( hZip, pszFilename, TRUE, &index, &ze);
	char szFile[MAX_PATH];
	strcpy( szFile, pszFilename );

	int nLen = strlen( szFile );
	for( int i = 0; i < nLen; i++ )
	{
		if( szFile[i] == '\\' )
			szFile[i] = '/';
	}

	zr = FindZipItem( m_hZip, szFile, TRUE, &index, &ze);

	if( zr != ZR_OK )
		return FALSE;

	//DWORD dwSize = ze.unc_size;
	//BYTE* pbyBuffer = new BYTE[dwSize];

	zr = UnzipItem( m_hZip, index, "tmp.mex", 0, ZIP_FILENAME );
	//zr = UnzipItem( hZip, index, pbyBuffer, dwSize, ZIP_MEMORY );
	if( zr != ZR_OK )
	{
		//delete []pbyBuffer;
		return FALSE;
	}
	*pdwSize = LoadFileToMemory( "tmp.mex", ppbyBuffer );
	remove( "tmp.mex" );
	return TRUE;


}
