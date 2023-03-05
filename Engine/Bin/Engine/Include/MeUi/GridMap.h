#pragma once
#include <Windows.h>
class CGridMap
{
public:
	struct Tile
	{
		bool bSet;
		Tile()
		{
			bSet = false;
		}
	};
public:
	CGridMap(void);
	~CGridMap(void);

	BOOL	Create( int nWidth, int nHeight );
	void	Clear();
	Tile*	GetTileAt( int x, int y );
	// 分配一个矩形
	BOOL	FindRect( int nRectWidth, int nRectHeight, int* px, int* py );
	BOOL	SetRect( RECT* pRect );
	BOOL	SetRect( int x, int y, int w, int h, bool bSet = true );
	//BOOL	ClearRect( int x, int y, int w, int h );
	BOOL	MoveRect( int x0, int y0, int w, int h, int x1, int y1 );
	BOOL	CanPlaceRect( int x, int y, int w, int h );
	BOOL	DebugLog( const char* pszFilename );
protected:
	int		m_nWidth;
	int		m_nHeight;
	Tile*	m_pTiles;
};
