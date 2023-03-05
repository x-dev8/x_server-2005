#include "Datachunkwriter.h"
//#include "FuncPerformanceLog.h"
#include "Helper.h"
#include "NewWithDebug.h"

CDataChunkWriter::CDataChunkWriter( BYTE* pbyBuffer, DWORD dwBufferSize, BOOL bSkip0SizeChunk )
{
    m_dwBufferSize = dwBufferSize;
    m_pbyBuffer = pbyBuffer;
    m_dwOffset = 0;
    m_bExternalMemory = TRUE;
    m_bSkip0SizeChunk = bSkip0SizeChunk;
}
CDataChunkWriter::CDataChunkWriter( DWORD dwBufferSize, BOOL bSkip0SizeChunk )
{
    m_dwBufferSize = dwBufferSize;
    m_pbyBuffer    = CNewWithDebug<BYTE>::Alloc(m_dwBufferSize, "CDataChunkWriter::CDataChunkWriter创建m_pbyBuffer");

    m_dwOffset        = 0;
    m_bExternalMemory = FALSE;
    m_bSkip0SizeChunk = bSkip0SizeChunk;
}

void CDataChunkWriter::Destroy()
{
    if( m_bExternalMemory )
    { m_pbyBuffer = NULL; }
    else
    {
        if( m_pbyBuffer )
        {
            CNewWithDebug<BYTE>::Free(m_pbyBuffer);
            m_pbyBuffer = NULL;
        }
    }
    m_dwBufferSize = 0;
    m_dwOffset = 0;
}

DWORD CDataChunkWriter::WriteCharChunk( DWORD dwName, char s )
{
    OpenChunk( dwName );
    WriteChar( s );
    CloseChunk( dwName );
    return 0;
}
DWORD CDataChunkWriter::WriteDwordChunk( DWORD dwName, DWORD dw )
{
    OpenChunk( dwName );
    WriteDword( dw );
    CloseChunk( dwName );
    return 0;
}

DWORD CDataChunkWriter::WriteIntChunk( DWORD dwName, int i )
{
    OpenChunk( dwName );
    WriteInt( i );
    CloseChunk( dwName );
    return 0;

}

DWORD CDataChunkWriter::WriteFloatChunk( DWORD dwName, float f )
{
    OpenChunk( dwName );
    WriteFloat( f );
    CloseChunk( dwName );
    return 0;
}

DWORD CDataChunkWriter::WriteShortChunk( DWORD dwName, short s )
{
    OpenChunk( dwName );
    WriteShort( s );
    CloseChunk( dwName );
    return 0;
}

DWORD CDataChunkWriter::WriteWordChunk( DWORD dwName, WORD w )
{
    OpenChunk( dwName );
    WriteWord( w );
    CloseChunk( dwName );
    return 0;
}

DWORD CDataChunkWriter::WriteByteChunk( DWORD dwName, BYTE b )
{
    OpenChunk( dwName );
    WriteByte( b );
    CloseChunk( dwName );
    return 0;
}

DWORD CDataChunkWriter::WriteBufferChunk( DWORD dwName, void* pBuffer, int nBufferSize )
{
    OpenChunk( dwName );
    Write( pBuffer, nBufferSize, 1  );
    CloseChunk( dwName );
    return 0;
}

DWORD CDataChunkWriter::WriteInt64Chunk( DWORD dwName, __int64 i64 )
{
    OpenChunk( dwName );
    WriteInt64( i64 );
    CloseChunk( dwName );
    return 0;
}

DWORD CDataChunkWriter::StartChunk( DWORD dwName )
{
    ChunkDesc desc;
    desc.header.dwName = dwName;
    desc.header.dwSize = 0;
    desc.dwOffset = m_dwOffset;
    m_stackChunkDesc.push( desc );

    Write( &desc.header, sizeof( ChunkHdr ), 1 );
    return 0;
}

DWORD CDataChunkWriter::OpenChunk( DWORD dwName )
{
    return StartChunkWithTag( dwName );
}

DWORD CDataChunkWriter::CloseChunk( DWORD dwName )
{
    return EndChunkWithTag( dwName );
}

DWORD CDataChunkWriter::StartChunkWithTag( DWORD dwName )
{
    return StartChunk(DC_TAG(dwName));
}

DWORD CDataChunkWriter::EndChunkWithTag( DWORD dwName )
{
    return EndChunk(DC_TAG(dwName));
}

DWORD CDataChunkWriter::EndChunk( DWORD dwName )
{
    assert( !m_stackChunkDesc.empty() );
    ChunkDesc desc = m_stackChunkDesc.top();
    m_stackChunkDesc.pop();

    assert( desc.header.dwName == dwName );
    if (desc.dwOffset > m_dwBufferSize)
    {
        assert(false);
        return 0;
    }
    ChunkHdr* pHdr = (ChunkHdr*)&m_pbyBuffer[desc.dwOffset];
    // 去掉header的size
    pHdr->dwSize = m_dwOffset-( desc.dwOffset+sizeof( ChunkHdr ) );
    // 如果没有实际的数据，那么还原偏移量，这样可以去掉没有用的数据，
    // 同时减小文件尺寸，
    if( m_bSkip0SizeChunk && pHdr->dwSize == 0 )
        m_dwOffset = desc.dwOffset;
    return 0;
}

DWORD CDataChunkWriter::Write( void* pBuffer, DWORD dwBlockSize, DWORD dwBlockCount )
{
    if( m_bExternalMemory )
    {
        if( m_dwOffset+dwBlockSize*dwBlockCount >  m_dwBufferSize ) 
        {
            DebugLogout("m_dwOffset+dwBlockSize*dwBlockCount >  m_dwBufferSize   m_dwOffset = %d, dwBlockSize = %d, dwBlockCount = %d, m_dwBufferSize = %d", 
                m_dwOffset, dwBlockSize, dwBlockCount, m_dwBufferSize);
            assert( false );
            return 0;
        }
    }
    else
    {
        //assert( m_dwOffset+dwBlockSize*dwBlockCount <= m_dwBufferSize );
        //   added 2004.05.20
        while( m_dwOffset+dwBlockSize*dwBlockCount >  m_dwBufferSize )
        {
            DWORD dwNewBufferSize = m_dwBufferSize*2;
            BYTE* pbyNewBuffer = CNewWithDebug<BYTE>::Alloc(dwNewBufferSize, "CDataChunkWriter::Write中创建pbyNewBuffer");
            memcpy(pbyNewBuffer, m_pbyBuffer, min(m_dwBufferSize, dwNewBufferSize));
            CNewWithDebug<BYTE>::Free(m_pbyBuffer);
            m_pbyBuffer = pbyNewBuffer;
            m_dwBufferSize = dwNewBufferSize;
        }
    }
    
    BYTE* pSrc = (BYTE*)pBuffer;
    for( DWORD i = 0; i < dwBlockCount; i++ )
    {
        memcpy( &m_pbyBuffer[m_dwOffset], pSrc, dwBlockSize );
        pSrc += dwBlockSize;
        m_dwOffset += dwBlockSize;
    }
    return m_dwOffset;
}

BOOL CDataChunkWriter::SaveToFile( const char* pszFilename )
{
    assert( m_stackChunkDesc.empty() );
    FILE* fp = fopen( pszFilename, "wb" );
    if( !fp )return FALSE;
    if( m_dwOffset == 0 )
	{
		fclose( fp );
        return FALSE;
	}
    fwrite( m_pbyBuffer, m_dwOffset, 1, fp );
    fclose( fp );
    return TRUE;
}


DWORD CDataChunkWriter::WriteString( char* str )
{
    DWORD dwOffset = WriteInt( strlen( str ) );
    if( strlen( str ) > 0 )
        return Write( str, strlen( str ), 1 );
    return dwOffset;
}

CXmlChunkWriter::CXmlChunkWriter(DWORD dwBufferSize, BOOL bSkip0SizeChunk ) : CDataChunkWriter( dwBufferSize, bSkip0SizeChunk )
{
}

void CXmlChunkWriter::Destroy()
{
    return CDataChunkWriter::Destroy();
}

// szChar必须是大小为4的数组
void CXmlChunkWriter::DWORDTOCHAR(char* szChar, DWORD dwStr )
{
    szChar[0] = GET_DWORD1CHAR(dwStr);
    szChar[1] = GET_DWORD2CHAR(dwStr);
    szChar[2] = GET_DWORD3CHAR(dwStr);
    szChar[3] = GET_DWORD4CHAR(dwStr);
}

DWORD CXmlChunkWriter::StartChunk( DWORD dwName )
{
    char szBuff[256] = {0};
    char szDwToChar[5] = {0};    
    DWORDTOCHAR( szDwToChar, dwName );
    szDwToChar[4] = '\0';
    _snprintf( szBuff, sizeof(szBuff)-1, "<%s>", szDwToChar );
    int nLen = strlen(szBuff);
    Write( &szBuff, sizeof(char)*nLen, 1 );
    return 0;
}

DWORD CXmlChunkWriter::EndChunk( DWORD dwName )
{
    char szBuff[256] = {0};
    char szDwToChar[5] = {0};    
    DWORDTOCHAR( szDwToChar, dwName );
    szDwToChar[4] = '\0';
    _snprintf( szBuff, sizeof(szBuff)-1, "</%s>", szDwToChar );
    Write( &szBuff, sizeof(char)*strlen(szBuff), 1 );
    return 0;
}

DWORD CXmlChunkWriter::StartChunkWithTag( DWORD dwName )
{
    return StartChunk(DC_TAG(dwName));
}

DWORD CXmlChunkWriter::EndChunkWithTag( DWORD dwName )
{
    return EndChunk(DC_TAG(dwName));
}

DWORD CXmlChunkWriter::Write( void* pBuffer, DWORD nBlockSize, DWORD nBlockCount )
{
    return CDataChunkWriter::Write( pBuffer, nBlockSize, nBlockCount );
}

BOOL CXmlChunkWriter::SaveToFile( const char* pszFilename )
{
    assert( m_stackChunkDesc.empty() );
    FILE* fp = fopen( pszFilename, "w" );
    if( !fp )return FALSE;
    fwrite( m_pbyBuffer, m_dwOffset, 1, fp );
    fclose( fp );
    return TRUE;
}

DWORD CXmlChunkWriter::WriteChar( char s )
{
    // { return Write( &s, sizeof( char ), 1 ); }
    return CDataChunkWriter::WriteChar( s );
}

DWORD CXmlChunkWriter::WriteInt( int i )
{
    return CDataChunkWriter::WriteInt( i );
}

DWORD CXmlChunkWriter::WriteFloat( float f )
{
    return CDataChunkWriter::WriteFloat( f );
}

DWORD CXmlChunkWriter::WriteShort( short s )
{
    return CDataChunkWriter::WriteShort( s );
}

DWORD CXmlChunkWriter::WriteByte( BYTE b )
{
    return CDataChunkWriter::WriteByte( b );
}

DWORD CXmlChunkWriter::WriteString( char* str )
{
    return CDataChunkWriter::WriteString( str );
}

CDataChunkLoader::CDataChunkLoader(): m_pbyBuffer(NULL), m_nBufferSize(0), m_nChunkSize(0),m_dwChunkName(0)
{}

CDataChunkLoader::CDataChunkLoader(CDataChunkLoader&l) : m_pbyBuffer(NULL), m_nBufferSize(0), m_nChunkSize(0), m_dwChunkName(0)
{
    Init( (BYTE*)l.GetPointer().c, l.GetChunkSize() );
}

CDataChunkLoader::CDataChunkLoader( BYTE* pbyBuffer, int nBufferSize ) : m_pbyBuffer(NULL), m_nBufferSize(0), m_nChunkSize(0), m_dwChunkName(0)
{
    Init( pbyBuffer, nBufferSize );
}

void CDataChunkLoader::Init( BYTE* pbyBuffer, int nBufferSize )
{
    m_pbyBuffer = pbyBuffer;
    m_nBufferSize = nBufferSize;
    m_pointer.byte = m_pbyBuffer;
}

DWORD CDataChunkLoader::GetChunkName()
{
    return DC_TAG( *m_pointer.dw );
}

BOOL CDataChunkLoader::IsChunk( DWORD dwName )
{
    return GetChunkName() == dwName;
}

BOOL CDataChunkLoader::IsEndOfMemory()
{
    return m_pointer.c >= (char*)m_pbyBuffer+m_nBufferSize;
}

BOOL CDataChunkLoader::IsEndOfChunk()
{
    if( m_stackChunkDesc.size() == 0 )
    {
        assert( false );
        return FALSE;
    }
    ChunkDesc desc = m_stackChunkDesc.top();
    return m_pointer.byte >= m_pbyBuffer+desc.dwOffset+sizeof(desc.header)+desc.header.dwSize;
}

//BOOL CDataChunkLoader::TryGetNextChunk()
//{
//    return TRUE;
//}

BOOL CDataChunkLoader::SkipChunk()
{
    //// p.dw++;
    //// int size = *p.i++;
    //// p.c += size; 
    //// break;
    m_pointer.dw++;
    m_nChunkSize = *m_pointer.i++;
    m_pointer.c += m_nChunkSize;
    return TRUE;
}

BOOL CDataChunkLoader::StartChunk( DWORD dwName )
{
    if( m_dwChunkName !=  0 )
    {
        assert( false );
    }
    m_dwChunkName = dwName;
    m_pointer.dw++;
    m_nChunkSize = *m_pointer.i++;
    return TRUE;
}

BOOL CDataChunkLoader::EndChunk( DWORD dwName )
{
    if( m_dwChunkName == 0 )
    {
        assert( false );
    }
    if( m_dwChunkName != dwName )
    {
        assert( false );
    }
    m_dwChunkName = 0;
    m_pointer.c += m_nChunkSize;
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL CDataChunkLoader::OpenChunk()
{
    ChunkDesc desc;
    // 当前偏移量
    desc.dwOffset = m_pointer.byte-m_pbyBuffer;
    // 略过name
    desc.header.dwName = *m_pointer.dw++;
    // 得到chunk的大小
    desc.header.dwSize = *m_pointer.i++;

    m_stackChunkDesc.push( desc );
    return TRUE;
}

BOOL CDataChunkLoader::CloseChunk()
{
    if( m_stackChunkDesc.empty() )
    {
        assert( false );
        return FALSE;
    }
    ChunkDesc desc = m_stackChunkDesc.top();
    m_stackChunkDesc.pop();
    m_pointer.byte = m_pbyBuffer+desc.dwOffset+sizeof(desc.header)+desc.header.dwSize;
    return TRUE;
}

DWORD CDataChunkLoader::ReadToBuffer( BYTE* pbyBuffer, int nBufferSize )
{
    //pbyBuffer = m_pointer.byte;
    memcpy( pbyBuffer, m_pointer.byte, nBufferSize );
    m_pointer.c += nBufferSize;
    return nBufferSize;
}

DWORD CDataChunkLoader::Read( BYTE* pbyBuffer, int nBufferSize )
{
    pbyBuffer = m_pointer.byte;
    //memcpy( pbyBuffer, m_pointer.byte, nBufferSize );
    m_pointer.c += nBufferSize;
    return nBufferSize;
}

BOOL CDataChunkLoader::TryReadDwordChunk( DWORD dwName, DWORD& dw    )
{
    if( IsChunk( dwName ) )
    {
        OpenChunk();
        dw = ReadDword();
        CloseChunk();
        return TRUE;
    }
    return FALSE;
}

BOOL CDataChunkLoader::TryReadIntChunk( DWORD dwName, int& n        )
{
    if( IsChunk( dwName ) )
    {
        OpenChunk();
        n = ReadInt();
        CloseChunk();
        return TRUE;
    }
    return FALSE;
}

BOOL CDataChunkLoader::TryReadCharChunk( DWORD dwName, char& c        )
{
    if( IsChunk( dwName ) )
    {
        OpenChunk();
        c = ReadChar();
        CloseChunk();
        return TRUE;
    }
    return FALSE;
}

BOOL CDataChunkLoader::TryReadByteChunk( DWORD dwName, BYTE& byte    )
{
    if( IsChunk( dwName ) )
    {
        OpenChunk();
        byte = ReadByte();
        CloseChunk();
        return TRUE;
    }
    return FALSE;
}

BOOL CDataChunkLoader::TryReadShortChunk( DWORD dwName, short& s    )
{
    if( IsChunk( dwName ) )
    {
        OpenChunk();
        s = ReadShort();
        CloseChunk();
        return TRUE;
    }
    return FALSE;
}

BOOL CDataChunkLoader::TryReadWordChunk( DWORD dwName, WORD& w )
{
    if( IsChunk( dwName ) )
    {
        OpenChunk();
        w = ReadWord();
        CloseChunk();
        return TRUE;
    }
    return FALSE;
}

BOOL CDataChunkLoader::TryReadFloatChunk( DWORD dwName, float& f )
{
    if( IsChunk( dwName ) )
    {
        OpenChunk();
        f = ReadFloat();
        CloseChunk();
        return TRUE;
    }
    return FALSE;
}

BOOL CDataChunkLoader::TryReadInt64Chunk( DWORD dwName, __int64& n64 )
{
    if( IsChunk( dwName ) )
    {
        OpenChunk();
        n64 = ReadInt64();
        CloseChunk();
        return TRUE;
    }
    return FALSE;
}

//BOOL CDataChunkLoader::OpenPath( DWORD dwNames[], int nMaxDepth, int nDepth )
//{
//    while( !IsEndOfChunk() )
//    {
//        if( IsChunk( dwNames[nDepth] ) )
//        {
//            // 已经是最后的一个name，那么就找到了，
//            if( nDepth == nMaxDepth-1 )
//                return TRUE;
//            OpenChunk();
//            if( OpenPath( dwNames, nMaxDepth, nDepth+1 ) )
//            {
//                return TRUE;
//            }
//            CloseChunk();
//        }
//        else 
//            SkipChunk();
//    }
//    return FALSE;
//}
//BOOL CDataChunkLoader::OpenPath( const char* pszPath )
//{
//    char szPath[MAX_PATH] = "";
//    strcpy( szPath, pszPath );
//    std::vector<DWORD> vectorName;
//    int nLength = strlen( szPath );
//    for( int i = 0; i < nLength; i += 5 )
//    {
//        DWORD dwChar[4] = 
//        { 
//            szPath[i],
//            szPath[i+1],
//            szPath[i+2],
//            szPath[i+3],
//        };
//        DWORD dwName = (dwChar[0]<<24)|(dwChar[1]<<16)|(dwChar[2])<<8|(dwChar[3]);
//        vectorName.push_back( dwName );
//    }
//    while( !IsEndOfMemory() )
//    {
//        if( IsChunk( 'bbds'/*vectorName[0]*/ ) )
//        {
//            if( vectorName.size() == 1 )
//            {
//                OpenChunk();
//                return TRUE;
//            }
//            //OpenChunk();
//            StartChunk( 'bbds' );
//            if( OpenPath( &vectorName[0], vectorName.size(), 1 ) )
//                return TRUE;
//            //CloseChunk();
//            EndChunk( 'bbds' );
//        }
//        //else
//        else
//            SkipChunk();
//    }
//    return TRUE;
//}
