
#include "Me3d/StdioEx.h"
//#include "global.h"
#include "FilePath.h"
#include "FuncPerformanceLog.h"
#include "assert.h"

File::File()
{
	guardfunc;
	m_fp = 0;
	m_pBuffer = 0;
	m_dwFileSize = 0;
	m_dwFileOffset = 0;
	unguard;
}

File::~File()
{
	guardfunc;
	assert( m_fp == 0 );
	assert( m_pBuffer == 0 );
	unguard;
}

bool File::fopen( const char* pszFilename, const char* pszMode )
{
	guardfunc;
	/*fclose();
	
	m_fp = ::fopen( pszFilename, pszMode );
	if( m_fp == 0 )
		return false;
	::fseek ( m_fp, 0, SEEK_END );
	m_dwFileSize = ::ftell( m_fp );
	if( m_dwFileSize == 0 )
	{
		fclose();
		return false;
	}
	m_pBuffer = MeDefaultNew BYTE[m_dwFileSize];
	m_dwFileOffset = 0;
	::rewind( m_fp );
	::fread( m_pBuffer, m_dwFileSize, 1, m_fp );
	return true;*/

	fclose();
	m_dwFileSize = LoadFileToMemory( pszFilename, &m_pBuffer );
	m_dwFileOffset = 0;
	if( m_dwFileSize > 0 )
		return true;

#ifdef _DEBUG
    {
        // modify by SongLiang { [10/14/2003]
        
        // 当没有读取成功时，Debug版中做出提示。
        char szTempOutString[MAX_PATH+100];
        sprintf(szTempOutString,"3d file system can't find file ?[%s]",pszFilename);
        //MessageBox(NULL,szTempOutString,"3d System File Read Error?",MB_OK);
		//assert( false && "3d System File Read Error?" );

        // modify by SongLiang } [10/14/2003]
    }
#endif // _DEBUG

	return false;
	unguard;
}

void File::fclose( bool bReleaseMemory )
{
	guardfunc;
	if( m_fp )
	{
		::fclose( m_fp );
		m_fp = 0;
	}
	if( bReleaseMemory && m_pBuffer )
	{
		ReleaseFileMemory( &m_pBuffer );
		m_pBuffer = 0;
	}

	//   added 2003.09.06
	// make m_pBuffer NULL 
	m_pBuffer = 0;
	unguard;
}

int File::fread( void* buffer, int size, int count )
{
	guardfunc;
	DWORD dwLength = size*count;
	if( m_dwFileOffset+dwLength > m_dwFileSize )
		return 0;
	memcpy( buffer, &m_pBuffer[m_dwFileOffset], dwLength );
	m_dwFileOffset += dwLength;
	return count;
	unguard;
}

bool File::fseek( int offset, int type )
{
	guardfunc;
	switch( type )
	{
	case SEEK_SET:
		m_dwFileOffset = offset;
		break;
	case SEEK_CUR:
		m_dwFileOffset += offset;
		break;
	case SEEK_END:
		m_dwFileOffset = m_dwFileSize-offset;
		break;
	}
	if( m_dwFileOffset > m_dwFileSize )
		return false;
	
	return true;
	unguard;
}

int File::ReadInt()
{
	guardfunc;
	int nNumber;
	fread( &nNumber, sizeof( int ), 1 );
	return nNumber;
	unguard;
}
float File::ReadFloat()
{
	guardfunc;
	float fNumber;
	fread( &fNumber, sizeof( float ), 1 );
	return fNumber;
	unguard;
}
char* File::ReadString()
{
	guardfunc;
	int nLength = ReadInt();
	if( nLength > 0 )
	{
		static char szBuffer[1024];
		fread( szBuffer, nLength, 1 );
		return szBuffer;
		/*char* pBuffer = MeDefaultNew char[nLength];
		fread( pBuffer, nLength, 1 );
		return pBuffer;*/
	}
	return 0;
	unguard;
}
