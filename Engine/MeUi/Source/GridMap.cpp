#include "MeUi/GridMap.h"
#include <assert.h>
#include <stdio.h>
CGridMap::CGridMap(void):
m_nWidth(0),
m_nHeight(0),
m_pTiles(NULL)
{
}

CGridMap::~CGridMap(void)
{
	if( m_pTiles )
	{
		delete []m_pTiles;
		m_pTiles = NULL;
	}
}

BOOL CGridMap::Create( int nWidth, int nHeight )
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_pTiles = MeDefaultNew Tile[m_nWidth*m_nHeight];
	return TRUE;
}
void CGridMap::Clear()
{
	if( !m_pTiles )
		return;
	memset( m_pTiles, 0x00, m_nWidth*m_nHeight*sizeof(Tile) );
}
CGridMap::Tile* CGridMap::GetTileAt( int x, int y )
{
	if( x < 0 || x >= m_nWidth ||
		y < 0 || y >= m_nHeight )
		return NULL;
	if( !m_pTiles )
		return NULL;
	return &m_pTiles[y*m_nWidth+x];
}
BOOL CGridMap::CanPlaceRect( int x, int y, int w, int h )
{
	if( !m_pTiles )
		return FALSE;

	if( x < 0 || x >= m_nWidth ||
		y < 0 || y >= m_nHeight )
		return FALSE;
	if( x+w > m_nWidth ||
		y+h > m_nHeight )
		return FALSE;

	BOOL bSomeSet = FALSE;
	for( int i = 0; i < h; i++ )
	{
		for( int j = 0; j < w; j++ )
		{
			int dx = x+j;
			int dy = y+i;
			
			if( GetTileAt( dx, dy )->bSet )
			//if( m_pTiles[dy*m_nWidth+dx].bSet )
			{
				bSomeSet = TRUE;
				break;
			}
		}
		if( bSomeSet )
			break;
	}
	if( bSomeSet )
		return FALSE;
	return TRUE;
}
BOOL CGridMap::SetRect( int x, int y, int w, int h, bool bSet )
{
	//if( !CanPlaceRect( x, y, w, h ) )
	//	return FALSE;
	for( int i = 0; i < h; i++ )
	{
		for( int j = 0; j < w; j++ )
		{
			int dx = x+j;
			int dy = y+i;
			Tile* pTile = GetTileAt( dx, dy );
			if( pTile )
				pTile->bSet = bSet;
		}
	}
	return TRUE;
}
BOOL CGridMap::FindRect( int nRectWidth, int nRectHeight, int* px, int* py )
{
	for( int y = 0; y < m_nHeight; y++ )
	{
		for( int x = 0; x < m_nWidth; x++ )
		{
			if( CanPlaceRect( x, y, nRectWidth, nRectHeight ) )
			{
				*px = x;
				*py = y;
				return TRUE;
			}
		}
	}
	return FALSE;
}
//BOOL CGridMap::SetRect( RECT* pRect )
//{}
//BOOL CGridMap::ClearRect( RECT* pRect )
//{}
BOOL CGridMap::MoveRect( int x0, int y0, int w, int h, int x1, int y1 )
{
	SetRect( x0, y0, w, h, false );
	if( !CanPlaceRect( x1, y1, w, h ) )
	{
		SetRect( x0, y0, w, h );
		return FALSE;
	}
	//SetRect( x0, y0, w, h, false );
	SetRect( x1, y1, w, h );
	return TRUE;
}
BOOL CGridMap::DebugLog( const char* pszFilename )
{
	FILE* fp = fopen( pszFilename, "w" );
	if( !fp )
		return FALSE;
	for( int i = 0; i < m_nHeight; i++ )
	{
		for( int j = 0; j < m_nWidth; j++ )
		{
			if( GetTileAt( j, i)->bSet )
				fprintf( fp, "*" );
			else
				fprintf( fp, "." );
		}
		fprintf( fp, "\n" );
	}
	fclose( fp );
	return TRUE;
}
