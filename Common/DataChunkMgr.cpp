#include "DataChunkMgr.h"
#include "DataChunkWriter.h"
#include "NewWithDebug.h"
#include "ResourcePath.h"
#include "Configure.h"

CDataChunkMgr* GetDataChunkMgr()
{
	static CDataChunkMgr gs_DataChunkMgr;
	return &gs_DataChunkMgr;
}

CAppDataChunkClassID::CAppDataChunkClassID()
{
	m_dwPartA = 0xffffffff;
	m_dwPartB = 0xffffffff;
}
CAppDataChunkClassID::CAppDataChunkClassID( DWORD dwPartA, DWORD dwPartB )
{ 
	m_dwPartA = dwPartA; 
	m_dwPartB = dwPartB; 
}
CAppDataChunkClassID::CAppDataChunkClassID( const CAppDataChunkClassID& cid )
{
	m_dwPartA = cid.m_dwPartA;
	m_dwPartB = cid.m_dwPartB;
}
CAppDataChunkClassID& CAppDataChunkClassID::operator=( const CAppDataChunkClassID& cid )
{
	m_dwPartA = cid.m_dwPartA;
	m_dwPartB = cid.m_dwPartB;
	return *this;
}
int CAppDataChunkClassID::operator==( const CAppDataChunkClassID& cid ) const
{
	if( m_dwPartA == cid.m_dwPartA &&
		m_dwPartB == cid.m_dwPartB )
		return 1;
	return 0;
}
int CAppDataChunkClassID::operator!=( const CAppDataChunkClassID& cid ) const
{
	return !( *this == cid );
}
CAppDataChunk::CAppDataChunk(	
			CAppDataChunkClassID ClassID, 
			CAppDataChunkClassID SuperClassID,
			DWORD dwSubID,
			DWORD dwLength,
			void* pvData ):
m_dwLength(0),
m_pbyData(NULL)
{
	m_ClassID = ClassID;
	m_SuperClassID = SuperClassID;
	m_dwSubID = dwSubID;
	m_dwLength = dwLength;
	if( m_dwLength )
	{	
        m_pbyData = CNewWithDebug<BYTE>::Alloc(m_dwLength, "CAppDataChunk::CAppDataChunk中创建m_pbyData");
		memcpy( m_pbyData, pvData, m_dwLength );
	}
}
CAppDataChunk::~CAppDataChunk()
{
	if( m_pbyData )
	{
        CNewWithDebug<BYTE>::Free(m_pbyData);
		m_pbyData = NULL;
	}
}

CDataChunkMgr::CDataChunkMgr()
{
    char szFile[257] = {0};
    sprintf_s( szFile, sizeof( szFile ) - 1, "%s%s%s.dat", SYSTEM_DIRECTORY, DATACHUNK_FILEPATH, g_Cfg.szGameServerName );
    LoadFromFile( szFile );
}

CDataChunkMgr::~CDataChunkMgr()
{
	for( int nChunk = 0; nChunk < m_chunks.size(); nChunk++ )
	{
		CAppDataChunk* pChunk = m_chunks[nChunk];
		delete pChunk;
	}
}
void CDataChunkMgr::Clear()
{
	for( int nChunk = 0; nChunk < m_chunks.size(); nChunk++ )
	{
		CAppDataChunk* pChunk = m_chunks[nChunk];
		delete pChunk;
	}
	m_chunks.clear();
}
BOOL CDataChunkMgr::AddAppDataChunk( 
									CAppDataChunkClassID ClassID, 
									CAppDataChunkClassID SuperClassID, 
									DWORD dwSubID, 
									DWORD dwLength, 
									void* pvData )
{
	CAppDataChunk* pChunk = GetAppDataChunk( ClassID, SuperClassID, dwSubID );
	if( pChunk )
		return FALSE;
	pChunk = new CAppDataChunk( ClassID, SuperClassID, dwSubID, dwLength, pvData );
	m_chunks.push_back( pChunk );
	return TRUE;
}
CAppDataChunk* CDataChunkMgr::GetAppDataChunk( 
							   CAppDataChunkClassID ClassID, 
							   CAppDataChunkClassID SuperClassID, 
							   DWORD dwSubID )
{
	for( int nChunk = 0; nChunk < m_chunks.size(); nChunk++ )
	{
		CAppDataChunk* pChunk = m_chunks[nChunk];
		if( pChunk->m_ClassID == ClassID &&
			pChunk->m_SuperClassID == SuperClassID &&
			pChunk->m_dwSubID == dwSubID )
			return pChunk;
	}
	return NULL;
}
BOOL CDataChunkMgr::RemoveAppDataChunk( 
						CAppDataChunkClassID ClassID, 
						CAppDataChunkClassID SuperClassID, 
						DWORD dwSubID )
{
	for( int nChunk = 0; nChunk < m_chunks.size(); nChunk++ )
	{
		CAppDataChunk* pChunk = m_chunks[nChunk];
		if( pChunk->m_ClassID == ClassID &&
			pChunk->m_SuperClassID == SuperClassID &&
			pChunk->m_dwSubID == dwSubID )
		{
            delete pChunk;
			m_chunks.erase( m_chunks.begin()+nChunk );
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CDataChunkMgr::SaveToFile( const char* pszFilename )
{
	CDataChunkWriter w;
	w.StartChunkWithTag( 'dchk' );
	{
		w.WriteInt( 100 );
	}
	w.EndChunkWithTag( 'dchk' );
	w.StartChunkWithTag( 'chks' );
	{
		w.WriteInt( m_chunks.size() );
		for( int nChunk  = 0; nChunk < m_chunks.size(); nChunk++ )
		{
			CAppDataChunk* pChunk = m_chunks[nChunk];
			w.StartChunkWithTag( 'chk0' );
			{
				w.Write( &pChunk->m_ClassID, sizeof( pChunk->m_ClassID ), 1 );
				w.Write( &pChunk->m_SuperClassID, sizeof( pChunk->m_SuperClassID ), 1 );
				//w.WriteInt( pChunk->m_ClassID.GetPartA() );
				//w.WriteInt( pChunk->m_ClassID.GetPartB() );
				//w.WriteInt( pChunk->m_SuperClassID.GetPartA() );
				//w.WriteInt( pChunk->m_SuperClassID.GetPartB() );
				
				w.WriteInt( pChunk->m_dwSubID );
				w.WriteInt( pChunk->m_dwLength );
				w.Write( pChunk->m_pbyData, pChunk->m_dwLength, 1 );
			}
			w.EndChunkWithTag( 'chk0' );
		}
	}
	w.EndChunkWithTag( 'chks' );
	BOOL bOK = w.SaveToFile( pszFilename );
	w.Destroy();
	return bOK;
}
extern int LoadFileToMemory( const char* pszFilename, BYTE** ppBuffer );
#define DC_TAG(x) (DWORD)(  (((DWORD)x&0x0000ff00)<<8)+(((DWORD)x&0x000000ff)<<24)+(((DWORD)x&0x00ff0000)>>8)+(((DWORD)x&0xff000000)>>24) )
BOOL CDataChunkMgr::LoadFromFile( const char* pszFilename )
{
	BYTE* pbyBuffer = NULL;
	int nFileSize = LoadFileToMemory( pszFilename, &pbyBuffer );
	if( nFileSize == 0 )
		return FALSE;

    //清空当前所存储的chunks
   // m_chunks.clear();
	Clear();
	UDataChunkPointer p(pbyBuffer);
	while( p.c < (char*)pbyBuffer+nFileSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'dchk':
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
			}
			break;
		case 'chks':
			{
				p.dw++;
				int size = *p.i++;
				UDataChunkPointer s(p.c);
				{
					int nChunkCount = *s.i++;
					while( s.c < p.c+size )
					{
						switch( DC_TAG( *s.dw ) )
						{
						case 'chk0':
							{
								s.dw++;
								int size = *s.i++;
								UDataChunkPointer cp(s.c);
								{
									CAppDataChunkClassID ClassID;// = CAppDataChunkClassID( *cp.i++, *cp.i++ );
									memcpy( &ClassID, cp.c, sizeof( ClassID ) );
									cp.c += sizeof( ClassID );
									CAppDataChunkClassID SuperClassID;// = CAppDataChunkClassID( *cp.i++, *cp.i++ ); 
									memcpy( &SuperClassID, cp.c, sizeof( SuperClassID ) );
									cp.c += sizeof( SuperClassID );
									DWORD dwSubID = *cp.i++;
									DWORD dwLength = *cp.i++;
									BYTE* pbyData = cp.byte;
									CAppDataChunk* pChunk = 
										new CAppDataChunk( ClassID, SuperClassID, dwSubID, dwLength, pbyData );
									m_chunks.push_back( pChunk );
								}
								s.c += size; 
							}
							break;
						default:
							{
								s.dw++;
								int size = *s.i++;
								s.c += size; 
							}
							break;
						}
					}
				}
				p.c += size; 
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size;
			}
		}
	}
	delete [] pbyBuffer;
	return FALSE;
}

BOOL CDataChunkMgr::LoadFromMemory(unsigned char* pData, size_t nSize)
{
    if (pData == NULL || nSize == 0)
    {
        return FALSE;
    }
	unsigned char* pbyBuffer = pData;
    size_t nFileSize = nSize;

    //清空当前所存储的chunks
  //  m_chunks.clear();
	Clear();
	UDataChunkPointer p(pbyBuffer);
	while( p.c < (char*)pbyBuffer+nFileSize )
	{
		switch( DC_TAG( *p.dw ) )
		{
		case 'dchk':
			{
				p.dw++;
				int size = *p.i++;
				p.c += size; 
			}
			break;
		case 'chks':
			{
				p.dw++;
				int size = *p.i++;
				UDataChunkPointer s(p.c);
				{
					int nChunkCount = *s.i++;
					while( s.c < p.c+size )
					{
						switch( DC_TAG( *s.dw ) )
						{
						case 'chk0':
							{
								s.dw++;
								int size = *s.i++;
								UDataChunkPointer cp(s.c);
								{
									CAppDataChunkClassID ClassID;// = CAppDataChunkClassID( *cp.i++, *cp.i++ );
									memcpy( &ClassID, cp.c, sizeof( ClassID ) );
									cp.c += sizeof( ClassID );
									CAppDataChunkClassID SuperClassID;// = CAppDataChunkClassID( *cp.i++, *cp.i++ ); 
									memcpy( &SuperClassID, cp.c, sizeof( SuperClassID ) );
									cp.c += sizeof( SuperClassID );
									DWORD dwSubID = *cp.i++;
									DWORD dwLength = *cp.i++;
									BYTE* pbyData = cp.byte;
									CAppDataChunk* pChunk = 
										new CAppDataChunk( ClassID, SuperClassID, dwSubID, dwLength, pbyData );
									m_chunks.push_back( pChunk );
								}
								s.c += size; 
							}
							break;
						default:
							{
								s.dw++;
								int size = *s.i++;
								s.c += size; 
							}
							break;
						}
					}
				}
				p.c += size; 
			}
			break;
		default:
			{
				p.dw++;
				int size = *p.i++;
				p.c += size;
			}
		}
	}
	return FALSE;
}
BOOL CDataChunkMgr::SaveToMemory(unsigned char* pData, size_t& nSize)
{
    if (SaveToFile("tmp.tmp"))
    {
	    BYTE* pbyBuffer = NULL;
	    int nFileSize = LoadFileToMemory( "tmp.tmp", &pbyBuffer );
        if (nFileSize == 0)
        {
            return FALSE;
        }

        if (nSize < nFileSize)
        {
            nSize = nFileSize;
            delete [] pbyBuffer;
            return FALSE;
        }

        memcpy(pData, pbyBuffer, min(nFileSize, nSize));
        nSize = nFileSize;
        delete [] pbyBuffer;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

