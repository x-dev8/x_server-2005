///#include "stdafx.h"
#include "MapPicStruct.h"

#include "..\FuncPerformanceLog.h"

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=NULL ) { delete[](x); (x)=NULL; }
#endif

//----------------------------- 图片数据 -----------------------------    at [8/30/2003]
stMapPicStructHead::stMapPicStructHead()
{
	guardfunc;
	nWidthCount = nHeightCount = 0;
	nWidth = nHeight = 0;
	unguard;
}

stMapPicStruct::stMapPicStruct()
{
	guardfunc;
	memset( &stHead, 0x00, sizeof(stMapPicStructHead) );
	pbCanMove = NULL;
	pdwARGB = NULL;
	unguard;
}

stMapPicStruct::~stMapPicStruct()
{
	guardfunc;
	Release();
	unguard;
}

void stMapPicStruct::Release()
{
	guardfunc;
	SAFE_DELETE_ARRAY( pbCanMove );
	SAFE_DELETE_ARRAY( pdwARGB );
	unguard;
}

bool stMapPicStruct::IsInit()
{
	guardfunc;
	if ( pbCanMove && pdwARGB )
		return true;
	else
		return false;
	unguard;
}

//----------------------------- 地图数据 -----------------------------    at [8/30/2003]
stMapHead::stMapHead()
{
	guardfunc;
	nWidth = nHeight = 0;
	nWidthCount = nHeightCount = 0;
	unguard;
}

stMapData::stMapData()
{
	guardfunc;
	bCanBeMove = true;
	bHaveUnit = false;
	memset( szFileName, 0x00, sizeof(szFileName) );
	memset( &rc, 0x00, sizeof(RECT) );
	unguard;
}

stMap::stMap()
{
	guardfunc;
	memset( &stHead, 0x00, sizeof(stHead) );
	pstData = NULL;
	unguard;
}

stMap::~stMap()
{
	guardfunc;
	Release();
	unguard;
}

void stMap::Release()
{
	guardfunc;
	SAFE_DELETE_ARRAY( pstData );
	unguard;
}

bool stMap::IsEmpty()
{
	guardfunc;
	if ( pstData )
		return false;
	else
		return true;
	unguard;
}

//-------  区块   (   at 10/13/2003)
stAreaHead::stAreaHead()
{
	guardfunc;
	nNumber = 0;
	pData = NULL;
	unguard;
}

stAreaHead::~stAreaHead()
{
	guardfunc;
	Release();
	unguard;
}

void stAreaHead::Release()
{
	guardfunc;
	nNumber = 0;
	if ( pData ) delete[] pData;
	pData = NULL;
	unguard;
}

bool stAreaHead::ChangeAreaName( const char* pszCurName, const char* pszChangeName )
{
	guardfunc;
	for( int n=0; n<nNumber; n++ )
	{
		if ( strcmp( pData[n].szName, pszCurName) == 0 )
		{
			for( int m=0; m<nNumber; m++ )
			{
				if ( strcmp( pData[m].szName, pszChangeName) == 0 )
					return false;
			}
			strcpy( pData[n].szName, pszChangeName );
			return true;
		}
	}
	return false;
	unguard;
}

char* stAreaHead::FindArea( const int nX, const int nY )
{
	guardfunc;
	for( int n=0; n<nNumber; n++ )
	{
		if ( nX >= pData[n].rc.left && nX <= pData[n].rc.right &&
			nY >= pData[n].rc.top && nY <= pData[n].rc.bottom )
		{
			return pData[n].szName;
		}
	}
	return NULL;
	unguard;
}

bool stAreaHead::AddArea( const char* pszName, const RECT* prc )
{
	guardfunc;
	for( int n=0; n<nNumber; n++ )
	{
		if ( strcmp( pData[n].szName, pszName) == 0 )
			return false;
	}
	nNumber++;
	stArea*	p = new stArea[nNumber];
	if(pData)
	{
		memcpy( p, pData, sizeof(stArea)*(nNumber-1) );
		delete[] pData;
	}
	strcpy( p[nNumber-1].szName, pszName );
	p[nNumber-1].rc = *prc;
	pData = new stArea[nNumber];
	memcpy( pData, p, sizeof(stArea)*nNumber );
	delete[] p;
	return true;
	unguard;
}

bool stAreaHead::DelArea( const char* pszName )
{
	guardfunc;
	for( int n=0; n<nNumber; n++ )
	{
		if ( strcmp( pData[n].szName, pszName) == 0 )
		{
			// 如果不是最后一个
			if ( n != nNumber-1 )
			{
				memcpy( &pData[n], &pData[nNumber-1], sizeof(stArea) );
			}
			nNumber--;
			return true;
		}
	}
	return false;
	unguard;
}

void stAreaHead::SaveToFile( const char* pszFileName )
{
	guardfunc;
	FILE*	fp = fopen( pszFileName, "wt" );
	if (fp)
	{
		fprintf( fp, "%d\n", nNumber );
		for( int n=0; n<nNumber; n++ )
		{
			fprintf( fp, "Area %s %d %d %d %d\n", 
					pData[n].szName,
					pData[n].rc.left,
					pData[n].rc.top,
					pData[n].rc.right,
					pData[n].rc.bottom );
		}
		fclose( fp );
	}
	unguard;
}

bool stAreaHead::LoadFromFile( const char* pszFileName )
{
	guardfunc;
	Release();

	FILE*	fp = fopen( pszFileName, "rt" );
	if (fp)
	{
		fscanf( fp, "%d", &nNumber );
		pData = new stArea[nNumber];
		char	szTemp[16];
		for( int n=0; n< nNumber; n++ )
		{
			fscanf( fp, "%s %s %d %d %d %d", szTemp, pData[n].szName,
					&pData[n].rc.left, &pData[n].rc.top, &pData[n].rc.right, &pData[n].rc.bottom );
		}
		fclose(fp);
		return true;
	}
	return false;
	unguard;
}

void stAreaHead::SaveToFile( FILE* fp )
{
	guardfunc;
	if (fp)
	{
		fprintf( fp, "%d\n", nNumber );
		for( int n=0; n<nNumber; n++ )
		{
			fprintf( fp, "Area %s %d %d %d %d\n", 
				pData[n].szName,
				pData[n].rc.left,
				pData[n].rc.top,
				pData[n].rc.right,
				pData[n].rc.bottom );
		}
	}
	unguard;
}

bool stAreaHead::LoadFromFile( FILE* fp )
{
	guardfunc;
	Release();

	if (fp)
	{
		fscanf( fp, "%d", &nNumber );
		pData = new stArea[nNumber];
		char	szTemp[16];
		for( int n=0; n< nNumber; n++ )
		{
			fscanf( fp, "%s %s %d %d %d %d", szTemp, pData[n].szName,
				&pData[n].rc.left, &pData[n].rc.top, &pData[n].rc.right, &pData[n].rc.bottom );
		}
		return true;
	}
	return false;
	unguard;
}

stArea::stArea()
{
	guardfunc;
	memset( szName, 0x00, sizeof(szName) );
	memset( &rc, 0x00, sizeof(RECT) );
	unguard;
}

//-------  空间门   (   at 10/13/2003)
stDoorHead::stDoorHead()
{
	guardfunc;
	nNumber = 0;
	pData = NULL;
	unguard;
}

stDoorHead::~stDoorHead()
{
	guardfunc;
	Release();
	unguard;
}

void stDoorHead::Release()
{
	guardfunc;
	nNumber = 0;
	if ( pData ) delete[] pData;
	pData = NULL;
	unguard;
}

bool stDoorHead::ChangeDoorName( const char* pszCurName, const char* pszChangeName )
{
	guardfunc;
	for( int n=0; n<nNumber; n++ )
	{
		if ( strcmp( pData[n].szName, pszCurName) == 0 )
		{
			for( int m=0; m<nNumber; m++ )
			{
				if ( strcmp( pData[m].szName, pszChangeName) == 0 )
					return false;
			}
			strcpy( pData[n].szName, pszChangeName );
			return true;
		}
	}
	return false;
	unguard;
}

char* stDoorHead::FindDoor( const int nX, const int nY )
{
	guardfunc;
	for( int n=0; n<nNumber; n++ )
	{
		if ( nX >= pData[n].rc.left && nX <= pData[n].rc.right &&
			nY >= pData[n].rc.top && nY <= pData[n].rc.bottom )
		{
			return pData[n].szName;
		}
	}
	return NULL;
	unguard;
}

bool stDoorHead::AddDoor( const char* pszName, const RECT* prc )
{
	guardfunc;
	for( int n=0; n<nNumber; n++ )
	{
		if ( strcmp( pData[n].szName, pszName) == 0 )
			return false;
	}
	nNumber++;
	stDoor*	p = new stDoor[nNumber];
	if(pData)
	{
		memcpy( p, pData, sizeof(stDoor)*(nNumber-1) );
		delete[] pData;
	}
	strcpy( p[nNumber-1].szName, pszName );
	p[nNumber-1].rc = *prc;
	pData = new stDoor[nNumber];
	memcpy( pData, p, sizeof(stDoor)*nNumber );
	delete[] p;
	return true;
	unguard;
}

bool stDoorHead::DelDoor( const char* pszName )
{
	guardfunc;
	for( int n=0; n<nNumber; n++ )
	{
		if ( strcmp( pData[n].szName, pszName) == 0 )
		{
			// 如果不是最后一个
			if ( n != nNumber-1 )
			{
				memcpy( &pData[n], &pData[nNumber-1], sizeof(stDoor) );
			}
			nNumber--;
			return true;
		}
	}
	return false;
	unguard;
}

void stDoorHead::SaveToFile( const char* pszFileName )
{
	guardfunc;
	FILE*	fp = fopen( pszFileName, "wt" );
	if (fp)
	{
		fprintf( fp, "%d\n", nNumber );
		for( int n=0; n<nNumber; n++ )
		{
			fprintf( fp, "Door %s %d %d %d %d\n", 
				pData[n].szName,
				pData[n].rc.left,
				pData[n].rc.top,
				pData[n].rc.right,
				pData[n].rc.bottom );
		}
		fclose( fp );
	}
	unguard;
}

bool stDoorHead::LoadFromFile( const char* pszFileName )
{
	guardfunc;
	Release();

	FILE*	fp = fopen( pszFileName, "rt" );
	if (fp)
	{
		fscanf( fp, "%d", &nNumber );
		pData = new stDoor[nNumber];
		char	szTemp[16];
		for( int n=0; n< nNumber; n++ )
		{
			fscanf( fp, "%s %s %d %d %d %d",szTemp, pData[n].szName,
				&pData[n].rc.left, &pData[n].rc.top, &pData[n].rc.right, &pData[n].rc.bottom );
		}
		fclose(fp);
		return true;
	}
	return false;
	unguard;
}

void stDoorHead::SaveToFile( FILE* fp )
{
	guardfunc;
	if (fp)
	{
		fprintf( fp, "%d\n", nNumber );
		for( int n=0; n<nNumber; n++ )
		{
			fprintf( fp, "Door %s %d %d %d %d\n", 
				pData[n].szName,
				pData[n].rc.left,
				pData[n].rc.top,
				pData[n].rc.right,
				pData[n].rc.bottom );
		}
	}
	unguard;
}

bool stDoorHead::LoadFromFile( FILE* fp )
{
	guardfunc;
	Release();

	if (fp)
	{
		fscanf( fp, "%d", &nNumber );
		pData = new stDoor[nNumber];
		char	szTemp[16];
		for( int n=0; n< nNumber; n++ )
		{
			fscanf( fp, "%s %s %d %d %d %d",szTemp, pData[n].szName,
				&pData[n].rc.left, &pData[n].rc.top, &pData[n].rc.right, &pData[n].rc.bottom );
		}
		return true;
	}
	return false;
	unguard;
}

stDoor::stDoor()
{
	guardfunc;
	memset( szName, 0x00, sizeof(szName) );
	memset( &rc, 0x00, sizeof(RECT) );
	unguard;
}

void SaveToMapdesc( const char* szpFileName, stAreaHead* pArea, stDoorHead* pDoor )
{
	guardfunc;
	FILE* fp = fopen( szpFileName, "wt" );
	if ( fp )
	{
		pArea->SaveToFile( fp );
		pDoor->SaveToFile( fp );
		fclose( fp );
	}
	unguard;
}

bool LoadFromMapdesc( const char* pszFileName, stAreaHead* pArea, stDoorHead* pDoor )
{
	guardfunc;
	FILE* fp = fopen( pszFileName, "rt" );
	if (fp)
	{
		pArea->LoadFromFile( fp );
		pDoor->LoadFromFile( fp );
		fclose(fp);
		return true;
	}
	return false;
	unguard;
}


