#include "Me3d/FilePath.h"
#include "FuncPerformanceLog.h"
#include <vector>
#include <stdio.h>
#include <windows.h>

bool Path::IsExist( const char* pszPathName )
{
	guardfunc;
	FILE* fp = fopen( pszPathName, "rb" );
	if( fp == 0 )
		return false;
	fclose( fp );
	return true;
	unguard;
}

bool Path::IsDirectory( const char* pszPathName )
{
	guardfunc;
	HANDLE fhd;
	WIN32_FIND_DATA	fd;
	if((fhd = FindFirstFile(pszPathName,&fd))==INVALID_HANDLE_VALUE)
		return false;
	if((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{

		FindClose(fhd);
		return true;
	}
	else
	{
		FindClose(fhd);
		return false;
	}
	unguard;
}

bool Path::MakeDirectory( const char* pszPathName )
{
	guardfunc;
	char szPath[1024];
	strcpy( szPath, pszPathName );
	
	
	std::vector<std::string> vectorDir;
	
	unsigned int nLength = strlen( szPath );
	char* pDirNameStart = szPath;
	for( unsigned int i = 0; i < nLength; i++ )
	{
		if( szPath[i] == '\\' )
		{
			szPath[i] = 0;
			vectorDir.push_back( pDirNameStart );
			pDirNameStart = &szPath[i+1];
		}
	}

	szPath[0] = 0;
	for(int  i = 0; i < vectorDir.size(); i++ )
	{
		
		strcat( szPath, vectorDir[i].c_str() );
		if( !IsDirectory( szPath ) )
			CreateDirectory( szPath, NULL );
		strcat( szPath, "\\" );
	}
	
	
	return true;
	unguard;
}

bool Path::Split( const char* pszPathName )
{
	guardfunc;
	_splitpath( pszPathName, drive, dir, fname, ext );
	return true;
	unguard;
}


//void Path::Recurse( const char* pszRoot, const char* pszDir )
//{
//	CFileFind finder;
//
//	// build a string with wildcards
//	CString strWildcard(pszDir);
//	strWildcard += _T("\\*.*");
//
//	// start working for files
//	BOOL bWorking = finder.FindFile(strWildcard);
//
//	std::vector<CString> vectorDir;
//	while (bWorking)
//	{
//		bWorking = finder.FindNextFile();
//
//		// skip . and .. files; otherwise, we'd
//		// recur infinitely!
//
//		if (finder.IsDots())
//			continue;
//
//		// if it's a directory, recursively search it
//
//		if (finder.IsDirectory())
//		{
//			CString str = finder.GetFilePath();
//
//			vectorDir.push_back( str );
//		}
//		CString str = finder.GetFilePath();
//
//
//		char* pszFilename = str.GetBuffer();
//		int nLength = strlen( pszFilename );
//
//		m_vectorFilename.push_back( pszFilename );
//
//	}
//	for( int i = 0; i < vectorDir.size(); i++ )
//	{
//		Recurse( pszRoot, vectorDir[i] );
//	}
//
//	finder.Close();
//}
