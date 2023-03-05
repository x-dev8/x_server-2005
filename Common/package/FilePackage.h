#pragma once
#include "XUnzip.h"
class CFilePackage
{
public:
	CFilePackage(void);
	~CFilePackage(void);

public:
	BOOL	Open( const char* pszFilename );
	int		LoadFileToMemory( const char* pszFilename, BYTE** ppBuffer );
	BOOL	UnPack( const char* pszFilename, BYTE** ppbyBuffer, DWORD* pdwSize );
protected:
	HZIP	m_hZip;
};
