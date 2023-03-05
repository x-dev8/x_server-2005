#include <stdio.h>
#include <assert.h>
#include "elementset.h"
CElementSet::CElementSet():
m_nWidth(0),
m_nHeight(0),
m_pfData(NULL)
{
}
CElementSet::~CElementSet()
{
	//assert( m_pfData == NULL );
	if( m_pfData )
	{
		delete[] m_pfData;
		m_pfData = NULL;
	}
}
BOOL CElementSet::LoadFromFile( const char* pszFilename )
{
	FILE* fp = fopen( pszFilename, "rb" );
	if( !fp )
		return FALSE;
	int nWidth = 0, nHeight = 0;
	fread( &nWidth, sizeof(int), 1, fp );
	fread( &nHeight, sizeof(int), 1, fp );
	if( nWidth > 0 && nHeight > 0 )
	{
		//m_pfData = new float[m_nHeight*m_nWidth];
		Create( nWidth, nHeight );
		fread( m_pfData, m_nHeight*m_nWidth*sizeof(float), 1, fp );
	}
	if( fp )
	{
		fclose( fp );
	}
	return TRUE;
}
BOOL CElementSet::SaveToFile( const char* pszFilename )
{
	FILE* fp = fopen( pszFilename, "wb" );
	if( !fp )
		return FALSE;
	fwrite( &m_nWidth, sizeof(int), 1, fp );
	fwrite( &m_nHeight, sizeof(int), 1, fp );
	if( m_nHeight > 0 && m_nWidth > 0 )
	{
		//m_pfData = new float[m_nHeight*m_nWidth];
		fwrite( m_pfData, m_nHeight*m_nWidth*sizeof(float), 1, fp );
	}
	if( fp )
	{
		fclose( fp );
	}
	return TRUE;
}
BOOL CElementSet::Create( int nWidth, int nHeight )
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_pfData = new float[m_nHeight*m_nWidth];
	
	return TRUE;
}