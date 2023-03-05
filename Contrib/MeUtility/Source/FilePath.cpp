#include "FilePath.h"
#include "FuncPerformanceLog.h"
#include "../filepacket/packet_interface.h"
// #ifdef DATA_LAUNCHER
// #include "DataLauncher.h"
// #endif

static CFilePath gs_path;

int LoadFileToMemory( const char* pszFilename, BYTE** ppBuffer )
{
	FILE* fp = fopen( pszFilename, "rb" );
	if( fp == 0 )
		return false;
	fseek ( fp, 0, SEEK_END );
	DWORD dwFileSize = ftell( fp );
	if( dwFileSize == 0 )
	{
		fclose( fp );
		return 0;
	}
	BYTE* pBuffer = new BYTE[dwFileSize];
	rewind( fp );
	fread( pBuffer, dwFileSize, 1, fp );
	fclose( fp );
	*ppBuffer = pBuffer;
	return dwFileSize;
}

void ReleaseFileMemory( BYTE** ppBuffer )
{
	if( *ppBuffer )
	{
		delete []*ppBuffer;
		*ppBuffer = 0;
	}
}

CFilePath::CFilePath()
{
	drive[0] = 0;
	dir[0] = 0;
	fname[0] = 0;
	ext[0] = 0;
}

BOOL CFilePath::IsExist( const char* pszPathName )
{
// #ifdef DATA_LAUNCHER
// 	if (g_DirectReadInPackage)
// 	{
// 		return swIsFileExist(pszPathName);
// 	}
// 	else
// #endif
	{
// 		FILE* fp = fopen( pszPathName, "rb" );
// 		if( fp == 0 )
// 			return FALSE;
// 		fclose( fp );
//		if( _access_s( pszPathName, 0 ) == 0 )
//			return TRUE;
		return packet_namespace::IsOpen(pszPathName);
//		return FALSE;
	}
}

const char* CFilePath::GetDrive()
{ 
	if( drive[0] )
		return drive; 
	return "";
}

const char* CFilePath::GetDirectory()
{ 
	if( dir[0] )
		return dir; 
	return "";
}

const char* CFilePath::GetFileName()
{ 
	if( fname[0] )
		return fname; 
	return "";
}

const char* CFilePath::GetExt()
{ 
	if( ext[0] )
		return ext; 
	return "";
}


BOOL CFilePath::IsDirectory( const char* pszPathName )
{
	HANDLE fhd;
	WIN32_FIND_DATA	fd;
	if((fhd = FindFirstFile(pszPathName,&fd))==INVALID_HANDLE_VALUE)
		return FALSE;
	if((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{

		FindClose(fhd);
		return TRUE;
	}
	else
	{
		FindClose(fhd);
		return FALSE;
	}
}

BOOL CFilePath::MakeDirectory( const char* pszPathName )
{
	if( !pszPathName )
		return FALSE;
	char szPath[1024] = {0};
	strncpy_s(szPath, sizeof( szPath ), pszPathName, sizeof(szPath)-1);
	
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
	for( int i = 0; i < vectorDir.size(); i++ )
	{
		size_t freesize = sizeof(szPath) - strlen(szPath);
        strncat( szPath, vectorDir[i].c_str(), freesize-1 );
		if( !IsDirectory( szPath ) )
			CreateDirectory( szPath, NULL );

        freesize = sizeof(szPath) - strlen(szPath);
		strncat( szPath, "\\", freesize-1 );
	}
	
	
	return TRUE;
}

BOOL CFilePath::Split( const char* pszPathName )
{
	_splitpath( pszPathName, drive, dir, fname, ext );
	return TRUE;
}

BOOL CFilePath::MakeDirectoryForFile( const char* pszPathName )
{
	Split( pszPathName );
	return TRUE;
}
DWORD CFilePath::GetFileSize( const char* pszPathName )
{
	FILE* fp = fopen( pszPathName, "rb" );
	if( !fp )
		return 0;
	fseek ( fp, 0, SEEK_END );
	DWORD dwSize = ftell( fp );
	fclose( fp );
	return dwSize;
}
const char* CFilePath::GetFileDir( const char* pszPathName )
{
	gs_path.Split( pszPathName );
	static char szPath[MAX_PATH];
	_snprintf( szPath, sizeof(szPath)-1, "%s\\%s", gs_path.GetDrive(), gs_path.GetDirectory() );
	return szPath;
}
const char* CFilePath::GetFileNameExt( const char* pszPathName )
{
	gs_path.Split( pszPathName );
	return gs_path.GetExt();
}
//void CFilePath::Recurse( const char* pszRoot, const char* pszDir )
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

CFileDesc::CFileDesc()
{
	memset( m_szFilename, 0x00, sizeof( m_szFilename ) );
	m_dwSize = 0;
	m_dwCheckSum = 0;
	m_dwBitSum = 0;
}

CFileDesc::~CFileDesc()
{
}
//int CFileDesc::GetByteBitSum( BYTE byte )
//{
//	int nCount = 0;
//	for( int i = 0; i < 8; i++ )
//	{
//		if( byte & 0x01 )
//			nCount++;
//		byte >>= 1;
//	}
//	return nCount;
//}

BOOL CFileDesc::Create( const char* pszFilename, BOOL* pbProcess )
{
	FILE* fp = fopen( pszFilename, "rb" );
	if( !fp )
		return FALSE;
	fseek ( fp, 0, SEEK_END );
	m_dwSize = ftell( fp );
	// 回到头部,准备计算数据块
	rewind( fp );


	//int const CHUNK_SIZE = 4096;
	//BYTE byBuffer[CHUNK_SIZE];
	//int nChunkCount = m_dwSize/CHUNK_SIZE;
	//int nLeftBytesCount = m_dwSize%CHUNK_SIZE;

	//m_dwCheckSum = 0;
	//for( int nChunk = 0; nChunk < nChunkCount; nChunk++ )
	//{
	//	if( !(*pbProcess) )
	//	{
	//		fclose( fp );
	//		return FALSE;
	//	}

	//	fread( byBuffer, CHUNK_SIZE, 1, fp );
	//	// 增加校验和
	//	for( int i = 0; i < CHUNK_SIZE; i++ )
	//	{
	//		m_dwCheckSum += byBuffer[i];
	//		m_dwBitSum += GetByteBitSum( byBuffer[i] );
	//	}
	//}
	//if( nLeftBytesCount > 0 )
	//{
	//	fread( byBuffer, nLeftBytesCount, 1, fp );
	//}
	//for( int i = 0; i < nLeftBytesCount; i++ )
	//{
	//	m_dwCheckSum += byBuffer[i];
	//	m_dwBitSum += GetByteBitSum( byBuffer[i] );
	//}

	fclose( fp );
	return TRUE;
}

CFileDescMgr::~CFileDescMgr()
{
	Destroy();
}

void CFileDescMgr::Destroy()
{
	for( int i = 0; m_files.size(); i++ )
	{
		delete m_files[i];
	}
	m_files.clear();
}

BOOL CFileDescMgr::CreateFileList( const char* pszFilename, std::vector<CFileDesc>& files )
{
    if ( pszFilename == NULL || *pszFilename == 0 )
    { return FALSE; }

	char s[MAX_PATH]= {0};
	FILE* fp = fopen( pszFilename, "wb" );
	if( !fp )
	{
		return FALSE;
	}
	int nFileCount = files.size();
	fwrite( &nFileCount, sizeof(int),1, fp );
	for( int i = 0; i < files.size(); i++ )
	{
		CFileDesc* pDesc = &files[i];
		fwrite( pDesc, sizeof( CFileDesc ), 1, fp );
	}
	fclose( fp );
	return TRUE;
}
