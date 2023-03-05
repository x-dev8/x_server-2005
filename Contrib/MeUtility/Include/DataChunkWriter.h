/********************************************************************
    Filename:    DataChunkWriter.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __UTILITY_DATACHUNKWRITER_H__
#define __UTILITY_DATACHUNKWRITER_H__

#include "MeRTLibs.h"

#define DC_TAG(x) (DWORD)(  (((DWORD)x&0x0000ff00)<<8)+(((DWORD)x&0x000000ff)<<24)+(((DWORD)x&0x00ff0000)>>8)+(((DWORD)x&0xff000000)>>24) )

#define GET_DWORD1CHAR(dw)    (dw&0xffffff00)>>24
#define GET_DWORD2CHAR(dw)    (dw&0xffffff00)>>16
#define GET_DWORD3CHAR(dw)    (dw&0x0000ff00)>>8
#define GET_DWORD4CHAR(dw)    (dw&0x000000ff)

union MapPointer
{
    BYTE*    byte;
    bool*    boolean;
    short*   s;
    WORD*    w;
    int*     i;
    DWORD*   dw;
    char*    c;
    void*    p;
    float*   f;
    __int64* i64;    

    MapPointer(void *in):p(in)
    {

    }
    MapPointer():p(NULL)
    {}
};

class CDataChunkWriter
{
public:
    struct ChunkHdr
    {
        DWORD dwName;
        DWORD dwSize;
    };
    struct ChunkDesc
    {
        ChunkHdr header;
        DWORD dwOffset;
    };
    
public:
    CDataChunkWriter( DWORD dwBufferSize = 65536, BOOL bSkip0SizeChunk = TRUE );
    CDataChunkWriter( BYTE* pbyBuffer, DWORD dwBufferSize, BOOL bSkip0SizeChunk = TRUE );
    virtual ~CDataChunkWriter(){ Destroy(); }
    virtual void  Destroy();
    virtual DWORD StartChunk( DWORD dwName );
    virtual DWORD EndChunk( DWORD dwName );
    virtual DWORD StartChunkWithTag( DWORD dwName );
    virtual DWORD EndChunkWithTag( DWORD dwName );
    virtual DWORD Write( void* pBuffer, DWORD nBlockSize, DWORD nBlockCount );
    virtual BOOL  SaveToFile( const char* pszFilename );
    virtual DWORD OpenChunk( DWORD dwName );
    virtual DWORD CloseChunk( DWORD dwName );

    template <class T>
    DWORD WriteT( T value ) { return Write( &value,  sizeof( T ),  1 );}

    virtual DWORD WriteChar  ( char s )    { return Write( &s,  sizeof( char ),  1 ); }
    virtual DWORD WriteDword ( DWORD dw )  { return Write( &dw, sizeof( DWORD ), 1 ); }
    virtual DWORD WriteInt   ( int i )     { return Write( &i,  sizeof( int ),   1 ); }
    virtual DWORD WriteFloat ( float f )   { return Write( &f,  sizeof( float ), 1 ); }
    virtual DWORD WriteShort ( short s )   { return Write( &s,  sizeof( short ), 1 ); }
    virtual DWORD WriteWord  ( WORD w )    { return Write( &w,  sizeof( WORD ),  1 ); }
    virtual DWORD WriteByte  ( BYTE b )    { return Write( &b,  sizeof( BYTE ),  1 ); }
    virtual DWORD WriteInt64 (__int64 nInt){ return Write(&nInt,sizeof(__int64), 1 ); }
    virtual DWORD WriteString( char* str );

    template <class T>
    void WriteChunkT( DWORD dwName, T value )
    {
        OpenChunk( dwName );
        WriteT( value );
        CloseChunk( dwName );
    }

    DWORD WriteCharChunk  ( DWORD dwName, char s );
    DWORD WriteDwordChunk ( DWORD dwName, DWORD dw );;
    DWORD WriteIntChunk   ( DWORD dwName, int i );
    DWORD WriteFloatChunk ( DWORD dwName, float f );
    DWORD WriteShortChunk ( DWORD dwName, short s );
    DWORD WriteWordChunk  ( DWORD dwName, WORD w );
    DWORD WriteByteChunk  ( DWORD dwName, BYTE b );
    DWORD WriteBufferChunk( DWORD dwName, void* pBuffer, int nBufferSize );
    DWORD WriteInt64Chunk ( DWORD dwName, __int64 i64 );

    DWORD GetUsedSize(){ return m_dwOffset; }
    BYTE* GetBuffer(){ return m_pbyBuffer; }
protected:
    std::stack<ChunkDesc> m_stackChunkDesc;
    DWORD    m_dwBufferSize;
    BYTE*    m_pbyBuffer;
    DWORD    m_dwOffset;
    BOOL    m_bSkip0SizeChunk;
    BOOL    m_bExternalMemory;    //是否是自己分配的内存,如果使用外部内存,就不需要释放,也不能再分配或者增长
};

class CDataChunkLoader
{
public:
    struct ChunkHdr
    {
        DWORD dwName;
        DWORD dwSize;
    };
    struct ChunkDesc
    {
        ChunkHdr header;
        DWORD dwOffset;
    };
public:
    CDataChunkLoader();
    CDataChunkLoader(CDataChunkLoader&l);
    CDataChunkLoader( BYTE* pbyBuffer, int nBufferSize );
    void    Init( BYTE* pbyBuffer, int nBufferSize );
    BOOL    IsChunk( DWORD dwName );
    DWORD   GetChunkName();

    BOOL    StartChunk( DWORD dwName );
    BOOL    EndChunk( DWORD dwName );
    BOOL    OpenChunk();
    BOOL    CloseChunk();
    BOOL    OpenPath( DWORD dwNames[], int nMaxDepth, int nDepth );
    BOOL    OpenPath( const char* pszPath );
    
    BOOL    IsEndOfMemory();
    BOOL    IsEndOfChunk();
    BOOL    TryGetNextChunk();
    BOOL    SkipChunk();

    char    ReadChar()  { return *m_pointer.c++;   }
    DWORD   ReadDword() { return *m_pointer.dw++;  }
    int     ReadInt()   { return *m_pointer.i++;   }
    __int64 ReadInt64() { return *m_pointer.i64++; }
    float   ReadFloat() { return *m_pointer.f++;   }
    short   ReadShort() { return *m_pointer.s++;   }
    WORD    ReadWord()  { return *m_pointer.w++;   }
    BYTE    ReadByte()  { return *m_pointer.byte++;}

    DWORD   Read( BYTE* pbyBuffer, int nBufferSize );
    DWORD   ReadToBuffer( BYTE* pbyBuffer, int nBufferSize );

    BOOL    TryReadDwordChunk( DWORD dwName, DWORD& dw    );
    BOOL    TryReadIntChunk  ( DWORD dwName, int& n       );
    BOOL    TryReadCharChunk ( DWORD dwName, char& c      );
    BOOL    TryReadByteChunk ( DWORD dwName, BYTE& byte   );
    BOOL    TryReadShortChunk( DWORD dwName, short& s     );
    BOOL    TryReadWordChunk ( DWORD dwName, WORD& w      );
    BOOL    TryReadFloatChunk( DWORD dwName, float& f     );
    BOOL    TryReadInt64Chunk( DWORD dwName, __int64& n64 );    

    MapPointer& GetPointer(){ return m_pointer; }
    int         GetChunkSize(){ return m_nChunkSize; }
    int         GetBufferSize(){return m_nBufferSize;}

    template<class T>
    BOOL TryReadChunkT( DWORD dwName, T& value)
    {   
        if( IsChunk( dwName ) )
        {
            OpenChunk();
            value = *((T*)m_pointer.p);
            m_pointer.c += sizeof(T);
            CloseChunk();
            return TRUE;
        }
        return FALSE;
    }

    template<class T>
    void ReadT( T& value )
    {   
        value = *((T*)m_pointer.p);
        m_pointer.c += sizeof(T);
    }

protected:
    BYTE*                 m_pbyBuffer;
    int                   m_nBufferSize;
    MapPointer            m_pointer;
    std::stack<ChunkDesc> m_stackChunkDesc;
    DWORD                 m_dwChunkName;
    int                   m_nChunkSize;
};

class CXmlChunkWriter :public CDataChunkWriter
{
public:
    CXmlChunkWriter(DWORD dwBufferSize = 65536, BOOL bSkip0SizeChunk = TRUE);
    virtual void  Destroy();
    virtual DWORD StartChunk( DWORD dwName );
    virtual DWORD EndChunk( DWORD dwName );
    virtual DWORD StartChunkWithTag( DWORD dwName );
    virtual DWORD EndChunkWithTag( DWORD dwName );
    virtual DWORD Write( void* pBuffer, DWORD nBlockSize, DWORD nBlockCount );
    virtual BOOL  SaveToFile( const char* pszFilename );

    virtual DWORD WriteChar( char s );// { return Write( &s, sizeof( char ), 1 ); }
    virtual DWORD WriteInt( int i );//{ return Write( &i, sizeof( int ), 1 ); }
    virtual DWORD WriteFloat( float f );//{ return Write( &f, sizeof( float ), 1 ); }
    virtual DWORD WriteShort( short s );//{ return Write( &s, sizeof( short ), 1 ); }
    virtual DWORD WriteByte( BYTE b );//{ return Write( &b, sizeof( BYTE ), 1 ); }
    virtual DWORD WriteString( char* str );

private:
    void    DWORDTOCHAR(char* szChar, DWORD dwStr );
};

#endif // __UTILITY_DATACHUNKWRITER_H__
