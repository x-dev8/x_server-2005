#ifndef _stdio_h
#define _stdio_h

#include "MeRTLibs.h"
class File
{
public:
	File();
	virtual ~File();
	bool fopen( const char* pszFilename, const char* pszMode );
	//   added 2003.05.18
	void fclose( bool bReleaseMemory = true );
	//void fclose();
	int fread( void* buffer, int size, int count );
	bool fseek( int offset, int type );

	DWORD GetOffset(){ return m_dwFileOffset; }
	
	//   added 2003.01.04
	int ReadInt();
	float ReadFloat();
	char* ReadString();

	//   added 2003.05.18
	BYTE* GetBuffer(){ return m_pBuffer; }
	DWORD GetBufferSize(){ return m_dwFileSize; }

	FILE* m_fp;
	BYTE* m_pBuffer;
	DWORD m_dwFileSize;
	DWORD m_dwFileOffset;

};


#endif