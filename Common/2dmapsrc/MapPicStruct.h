#pragma once
#include <windows.h>
#include <stdio.h>
//----------------------------- 图片数据 -----------------------------    at [8/30/2003]
struct stMapPicStructHead
{
	stMapPicStructHead();
	~stMapPicStructHead(){;}

	int	nWidthCount;
	int	nHeightCount;
	int	nWidth;
	int	nHeight;
};

struct stMapPicStruct
{
	stMapPicStruct();
	~stMapPicStruct();
	void	Release();
	bool	IsInit();

	stMapPicStructHead	stHead;
	bool*				pbCanMove;
	DWORD*				pdwARGB;
};

//----------------------------- 地图数据 -----------------------------    at [8/30/2003]
struct stMapHead
{
	stMapHead();
	~stMapHead(){;}

	int	nWidth;
	int	nHeight;
	int	nWidthCount;
	int	nHeightCount;
};

struct stMapData
{
	stMapData();
	~stMapData(){;}

	bool	bCanBeMove;
	bool	bHaveUnit;
	char	szFileName[32];
	RECT	rc;
};

struct stMap
{
	stMap();
	~stMap();
	void	Release();
	bool	IsEmpty();
	int		GetWidth(){ return stHead.nWidth; }
	int		GetHeight(){ return stHead.nHeight; }
	int		GetWidthCount(){ return stHead.nWidthCount; }
	int		GetHeightCount(){ return stHead.nHeightCount; }
	int		GetDataSize(){ return stHead.nWidthCount*stHead.nHeightCount; }
	int		GetColorSize(){ return stHead.nWidth*stHead.nHeight; }

	stMapHead	stHead;
	stMapData*	pstData;
};



//-------  区块   (   at 10/13/2003)
struct stArea
{
	stArea();
	~stArea(){;}

	char	szName[128];	// 区块名字
	RECT	rc;				// 区块范围
};

struct stAreaHead
{
	stAreaHead();
	~stAreaHead();

	void	Release();
	
	bool	ChangeAreaName( const char* pszCurName, const char* pszChangeName );
	char*	FindArea( const int nX, const int nY );			// 查找区域块,无:反回Null,有:反回名字
	bool	AddArea( const char* pszName, const RECT* prc );
	bool	DelArea( const char* pszName );

	void	SaveToFile( const char* szpFileName );
	bool	LoadFromFile( const char* pszFileName );
	void	SaveToFile( FILE* fp );
	bool	LoadFromFile( FILE* fp );

	int		nNumber;		// 区块数量
	stArea*	pData;			// 区块数据
};

//-------  空间门   (   at 10/13/2003)
struct stDoor
{
	stDoor();
	~stDoor(){;}

	char	szName[128];	// 空间门名字
	RECT	rc;				// 空间门范围
};

struct stDoorHead
{
	stDoorHead();
	~stDoorHead();

	void	Release();

	bool	ChangeDoorName( const char* pszCurName, const char* pszChangeName );
	char*	FindDoor( const int nX, const int nY );			// 查找门,无:反回Null,有:反回名字
	bool	AddDoor( const char* pszName, const RECT* prc );
	bool	DelDoor( const char* pszName );

	void	SaveToFile( const char* szpFileName );
	bool	LoadFromFile( const char* pszFileName );
	void	SaveToFile( FILE* fp );
	bool	LoadFromFile( FILE* fp );

	int		nNumber;		// 空间门数量
	stDoor*	pData;			// 空间门数据
};


void SaveToMapdesc( const char* szpFileName, stAreaHead* pArea, stDoorHead* pDoor );
bool LoadFromMapdesc( const char* pszFileName, stAreaHead* pArea, stDoorHead* pDoor );


