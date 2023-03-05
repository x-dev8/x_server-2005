#pragma once
#include <windows.h>
class CElementSet
{
public:
	CElementSet();
	~CElementSet();
	BOOL	Create( int nWidth, int nHeight );
	BOOL	LoadFromFile( const char* pszFilename );
	BOOL	SaveToFile( const char* pszFilename );
public:
	int		m_nWidth;
	int		m_nHeight;
	float*	m_pfData;
};