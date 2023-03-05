#pragma once
#include <windows.h>
#include <stdio.h>
//----------------------------- ͼƬ���� -----------------------------    at [8/30/2003]
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

//----------------------------- ��ͼ���� -----------------------------    at [8/30/2003]
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



//-------  ����   (   at 10/13/2003)
struct stArea
{
	stArea();
	~stArea(){;}

	char	szName[128];	// ��������
	RECT	rc;				// ���鷶Χ
};

struct stAreaHead
{
	stAreaHead();
	~stAreaHead();

	void	Release();
	
	bool	ChangeAreaName( const char* pszCurName, const char* pszChangeName );
	char*	FindArea( const int nX, const int nY );			// ���������,��:����Null,��:��������
	bool	AddArea( const char* pszName, const RECT* prc );
	bool	DelArea( const char* pszName );

	void	SaveToFile( const char* szpFileName );
	bool	LoadFromFile( const char* pszFileName );
	void	SaveToFile( FILE* fp );
	bool	LoadFromFile( FILE* fp );

	int		nNumber;		// ��������
	stArea*	pData;			// ��������
};

//-------  �ռ���   (   at 10/13/2003)
struct stDoor
{
	stDoor();
	~stDoor(){;}

	char	szName[128];	// �ռ�������
	RECT	rc;				// �ռ��ŷ�Χ
};

struct stDoorHead
{
	stDoorHead();
	~stDoorHead();

	void	Release();

	bool	ChangeDoorName( const char* pszCurName, const char* pszChangeName );
	char*	FindDoor( const int nX, const int nY );			// ������,��:����Null,��:��������
	bool	AddDoor( const char* pszName, const RECT* prc );
	bool	DelDoor( const char* pszName );

	void	SaveToFile( const char* szpFileName );
	bool	LoadFromFile( const char* pszFileName );
	void	SaveToFile( FILE* fp );
	bool	LoadFromFile( FILE* fp );

	int		nNumber;		// �ռ�������
	stDoor*	pData;			// �ռ�������
};


void SaveToMapdesc( const char* szpFileName, stAreaHead* pArea, stDoorHead* pDoor );
bool LoadFromMapdesc( const char* pszFileName, stAreaHead* pArea, stDoorHead* pDoor );


