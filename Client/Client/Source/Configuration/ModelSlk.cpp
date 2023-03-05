#include "ModelSlk.h" 
#include "slkreader.h"
#include "FuncPerformanceLog.h"

CModelSlk theModelSlk;
CNpcVisualSlk theNpcVisual;
CNpcVisualSlk::CNpcVisualSlk()
{}
CNpcVisualSlk::~CNpcVisualSlk()
{
}
BOOL CNpcVisualSlk::Init( const char* pszFilename )
{
	CSlkReader reader;
	int iRet;
	int iRow = 3;
	if( !reader.ReadFromFile(pszFilename))
	{
		return FALSE;
	}
	int			nID;
	std::string strAvatar;


	while(CSlkReader::ret_readover != ( iRet = reader.GotoNextLine(iRow++)))
	{
		if(CSlkReader::ret_nothisline == iRet)
			continue;
		if( !reader.GetIntFieldByName("ModelID", nID))
		{
			continue;
		}
		if( !reader.GetStringFieldByName("AvatarFile", strAvatar))
		{
			continue;
		}
		if( Find( nID ) )
			continue;
		Record* pRecord = new Record;
		pRecord->nModelId = nID;
		strcpy( pRecord->szPath, strAvatar.c_str() );
		m_records.Add( nID, pRecord );
	}

	return TRUE;
}
CNpcVisualSlk::Record* CNpcVisualSlk::Find( int nModelID )
{
	return m_records.Find( nModelID );
}

void CModelSlk::AddToMap( SModelInfo *pInfo )
{
	guardfunc;
	mapModel::iterator it;	

	it = m_mapModel.find( pInfo->ustModelID );

	if( it == m_mapModel.end() )
	{		
		m_mapModel.insert( mapModel::value_type( pInfo->ustModelID,pInfo ) );
	}
	unguard;
}

CModelSlk::SModelInfo *CModelSlk::FindByModelID( int iModelID )
{
	guardfunc;
	mapModel::iterator it;	

	it = m_mapModel.find( iModelID );
	if( it == m_mapModel.end() )
	{
		return (*it).second;
	}
	return 0;
	unguard;
}

char *CModelSlk::GetModelFildByModelID( int iModelID )
{
	guardfunc;
	SModelInfo *pInfo = FindByModelID( iModelID );
	if( pInfo )
		return (char *)pInfo->szModelFile.c_str();
	return NULL;
	unguard;
}

bool CModelSlk::LoadFromSlk( char *pszFile )
{
	guardfunc;
	CSlkReader reader;

	if( !reader.ReadFromFile( pszFile ) )
		return false;
	int iRet;
	int iLine = 2;
	int iValue;
	int iCol;
	SModelInfo *pInfo = 0;
	while( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iLine ++ ) ) )
	{
		if( CSlkReader::ret_nothisline == iRet )
			continue;

		if( pInfo )
			delete pInfo;
		pInfo = new SModelInfo;
		if( !pInfo )
			return false;

		iCol = 1;
		if( !reader.GetIntField( iCol++,iValue ) )
			continue;
		if( iValue < 0 )
			continue;
		
		pInfo->ustModelID = iValue;
		//
		if( !reader.GetStringField( iCol++, pInfo->szModelFile))
			continue;
		
		AddToMap( pInfo );

		pInfo = 0;
	}
	if( pInfo )
		delete pInfo;
	return true;
	unguard;
}
