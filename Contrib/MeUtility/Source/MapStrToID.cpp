#include "MapStrToID.h"
#include "FuncPerformanceLog.h"

int CMapStrToIDMgr::RecordSet::FindName( const char* pszName )
{
	guardfunc
	if( !pszName )
	{
		assert( false );
		return -1;
	}
	assert( pszName && "record set find name error, name is null" );
	int nRecCount = (int)vectorRecord.size();
	if( nRecCount <= 0 )
		return -1;
	assert( nRecCount > 0 && "record set find error, rec count is 0" );
	Record* r = &vectorRecord[0];
	for( int i = 0; i < nRecCount; i++ )
	{
		if( !r[i].pszName )
			continue;
		if( stricmp( pszName, r[i].pszName ) == 0 )
			return i;
	}
	return -1;
	unguard;
}

CMapStrToIDMgr::RecordSet::~RecordSet()
{
	guardfunc
	for( int i = 0; i < (int)vectorRecord.size(); i++ )
	{
		if( vectorRecord[i].pszName )
		{
			delete []vectorRecord[i].pszName;
		}
	}
	vectorRecord.clear();
	unguard;
}
CMapStrToIDMgr::CMapStrToIDMgr():
m_bSupportSameNameElement(FALSE)
{
	guardfunc
	unguard;
}

CMapStrToIDMgr::~CMapStrToIDMgr()
{
	Destroy();
}

int CMapStrToIDMgr::GetSize()
{
	guardfunc
	return m_mapRecordSet.size();
	unguard;
}

void CMapStrToIDMgr::Destroy()
{
	guardfunc
	std::map< DWORD, RecordSet* >::iterator it;
	for( it = m_mapRecordSet.begin(); it != m_mapRecordSet.end(); it++ )
	{
		RecordSet* pSet = it->second;
		delete pSet;
	}
	m_mapRecordSet.clear();
	unguard;
}

DWORD CMapStrToIDMgr::GenID( const char* pszName )
{
	guardfunc
	assert( pszName && "gen id error, name is null" );
	int nLen = (int)strlen( pszName );
	assert( nLen <= 255 && "gen id error, name len too large" );
	DWORD dwSum = 0;
	DWORD dwCode = 0;
	for( int i = 0; i < nLen; i++ )
	{
		DWORD code = tolower( pszName[i] );
		dwSum += code;
		dwCode ^= code;
	}
	DWORD dwID = nLen<<24|dwCode<<16|dwSum;
	return dwID;
	unguard;
}
void* CMapStrToIDMgr::GetDstByName( const char* pszName )
{
	guardfunc
	DWORD dwID = GenID( pszName );
	std::map< DWORD, RecordSet* >::const_iterator it = m_mapRecordSet.find( dwID );
	if( it == m_mapRecordSet.end() )
		return NULL;
	RecordSet* pSet = it->second;
	int nId = pSet->FindName( pszName );
	if( nId != -1 )
		return pSet->vectorRecord[nId].pDst;
	return NULL;
	unguard;
}
CMapStrToIDMgr::RecordSet* CMapStrToIDMgr::GetRecordSetByID( DWORD dwID )
{
	guardfunc
	std::map< DWORD, RecordSet* >::const_iterator it = m_mapRecordSet.find( dwID );
	if( it == m_mapRecordSet.end() )
		return NULL;
	return it->second;
	unguard;
}
CMapStrToIDMgr::RecordSet* CMapStrToIDMgr::GetRecordSetByName( const char* pszName )
{
	guardfunc
	DWORD dwID = GenID( pszName );
	RecordSet* pSet = GetRecordSetByID( dwID );
	return pSet;
	unguard;
}
DWORD CMapStrToIDMgr::Register( const char* pszName, void* pElement )
{
	guardfunc
	if( !pszName )
		return 0;
	void* pDst = GetDstByName( pszName );
	if( pDst )
	{
		if( !IsSupportSameNameElement() )
			return 0;
	}
	// 如果找到了，
	//if( pDst )
		
	DWORD dwID = GenID( pszName );
	RecordSet* pSet = GetRecordSetByID( dwID );

	Record record;
	int nLen = (int)strlen( pszName );
	record.pszName = new char[nLen+1];
    memset(record.pszName, 0, nLen+1);
	strncpy_s(record.pszName, nLen + 1, pszName, nLen);
	record.pDst = pElement;

	if( !pSet )
	{
		pSet = new RecordSet;
		m_mapRecordSet[dwID] = pSet;
	}
	pSet->vectorRecord.push_back( record );
	return dwID;
	unguard;
}

BOOL CMapStrToIDMgr::UnRegister( const char* pszName )
{
	guardfunc
	if( !pszName )
		return FALSE;
	void* pDst = GetDstByName( pszName );
	if( !pDst )
	{
		assert( false && "map str to id warning, not found name" );
		return FALSE;
	}
	DWORD dwID = GenID( pszName );
	RecordSet* pSet = GetRecordSetByID( dwID );
    if( !pSet )
    {
        assert( false );
        return FALSE;
    }

	int nId = pSet->FindName( pszName );
	if( nId == -1 )
	{
		assert( false );
		return FALSE;
	}
	delete[] pSet->vectorRecord[nId].pszName;
	pSet->vectorRecord.erase( pSet->vectorRecord.begin()+nId );

	if( pSet->vectorRecord.size() == 0 )
	{
		m_mapRecordSet.erase( dwID );
		delete pSet;
	}
	return TRUE;
	unguard;
}