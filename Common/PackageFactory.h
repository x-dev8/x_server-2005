#pragma once
#include <windows.h>
#include "MapStrToID.h"
#include <string>
#include "vfs.h"
class CPackageFactory
{
public:
	struct Package
	{
		int				nId;
		char			szPath[MAX_PATH];
		FileIO::CVFS	vfs;
		BOOL			bExist;
		Package():bExist(FALSE)/*,bLoaded(FALSE)*/{}
	};
public:
	CPackageFactory();
	~CPackageFactory();
	void	Destroy();
	BOOL	IsFileExist( const char* pszPackage, const char* pszFilename );
	int		OpenPackage( const char* pszPackage );
	BOOL	LoadFileToMemoryFromDisk( const char* pszFilename, BYTE** ppBuffer, int* pnFileSize );
	BOOL	LoadFileToMemory( const char* pszPackage, const char* pszFilename, BYTE** ppBuffer, int* pnFileSize );
	BOOL	LoadFileToMemory( int nPackage, const char* pszFilename, BYTE** ppBuffer, int* pnFileSize );
protected:
	std::vector<Package*>	m_Packages;
	CMapStrToIDMgr			m_Finder;
};
extern CPackageFactory* GetPackageFactory();
extern BOOL LoadFileToMemory( const char* pszPackage, const char* pszFilename, BYTE** ppBuffer, int* pnFileSize );