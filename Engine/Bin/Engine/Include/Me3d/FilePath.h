#ifndef _filepath_h
#define _filepath_h

#include "MeRTLibs.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
class Path
{
public:
	struct SFileName
	{
		char szFilename[MAX_PATH];
	};
public:
	bool IsExist( const char* pszPathName );
	bool IsDirectory( const char* pszPathName );
	bool MakeDirectory( const char* pszPathName );
	bool Split( const char* pszPathName );

	char* GetDrive(){ return drive; }
	char* GetDirectory(){ return dir; }
	char* GetFileName(){ return fname; }
	char* GetExt(){ return ext; }

	void Recurse( const char* pszRoot, const char* pszDir );
	const char*	GetFileName( int i ){ return m_vectorFilename[i].szFilename; }
	int GetFileCount(){ return m_vectorFilename.size(); }

protected:
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	std::vector<SFileName> m_vectorFilename;

};


#endif