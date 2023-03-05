#include "SlkReader.h"
#include "Vfs.h"
#include "FlyMemAllocer.h"
#include "FuncPerformanceLog.h"
#include "StringLanguageTranslator.h"
#include "../filepacket/packet_interface.h"
// #ifdef DATA_LAUNCHER
// #include "Launcher/DataLauncher.h"
// #endif

FileIO::CVFS g_SlkVFS;

void (*g_pfnSlkLoadingCallBack)( const char* pszString ) = NULL;
void OutputSlkLoadingMessage( char* pszString, ... )
{
	if( g_pfnSlkLoadingCallBack )
	{
		char TmpBuf[1024];
		va_list vl;

		//转换参数
		va_start(vl, pszString);
		vsnprintf(TmpBuf, sizeof(TmpBuf)-1, pszString, vl);
		va_end(vl);

		g_pfnSlkLoadingCallBack(TmpBuf);
	}
}

#define Safe_Delete(x) {if(x){delete x;x=0;}}

using namespace std;

char g_szValueTemp[ 64000 ];
char g_szStringValueTemp[257];

CSlkReader::CSlkReader()
{
	guardfunc
	m_iMaxLineNo = 0;
	m_pLastFindLine = 0;
	unguard;
}

CSlkReader::~CSlkReader()
{
	FreeAll();
}

void CSlkReader::FreeLine(SLine*pLine)
{
	//CSALocker locker(this);
	SField *pField;
	for( unsigned int i = 0 ; i < pLine->vector.size(); i ++ )
	{	
		pField = (pLine->vector[i]);
		if( !pField )
			continue;
		if( field_string == pField->iFieldType )
		{
			delete[] pField->data.szValue;
		}
		delete pField;
	}
	pLine->vector.clear();
}

void CSlkReader::FreeAll()
{
	//CSALocker locker(this);
	listLine::iterator it;
	for ( it = m_list.begin(); it != m_list.end(); it++ )
	{
		FreeLine( (*it) );
		delete( *it );
	}
	m_list.clear();
	//while( it != m_list.end() )
	//{
	//	FreeLine( (*it) );
	//	delete( *it );
	//	m_list.pop_front();
	//	
	//	it = m_list.begin();
	//}	
	m_iMaxLineNo = 0;
	m_mapIndex.clear();
	m_mapFiledNameToId.clear();
	m_pLastFindLine = NULL;
}

#include "StringLanguageTranslator.h"

char *CSlkReader::GetFieldValue( char *szString,CSlkReader::SField &field )
{
	//CSALocker locker(this);
	char *pcFind;
	int iSize;
	char *pcRead,*pcWrite;;
	bool bIsString = false;
	if( '"' == szString[0] )
		bIsString = true;
	pcFind = strchr( szString,'\r');
	if( pcFind )
	{
		iSize = (int)(pcFind - szString);
		g_szValueTemp[ iSize ] = 0;
		if( bIsString )
		{
			field.iFieldType = field_string;
			bool bFinish = false;
			memcpy(g_szValueTemp,szString, min(iSize, sizeof(g_szValueTemp)));
			pcRead = g_szValueTemp;

			//skip "
			pcRead ++;

			pcWrite = g_szStringValueTemp;
			while( !bFinish )
			{
				switch( *pcRead ) 
				{
				case 0:
					bFinish = true;
					break;
				case '\x1b':
					if( pcRead[1] == '\x20' 
						&& pcRead[2] == '\x3a' )
					{
						pcRead += 3;
						pcWrite[0] = '\r';
						pcWrite[1] = '\n';
						pcWrite += 2;
					}
					else
					{
						pcWrite[0] = pcRead[0];
						pcWrite++;
						pcRead ++;
					}
					break;
				case ';':
					if( pcRead[1] == ';' )
					{
						pcRead += 2;
						pcWrite[0] = ';';
						pcWrite ++;
					}
					else
					{
						pcWrite[0] = pcRead[0];
						pcWrite++;
						pcRead ++;
					}
					break;				
				default:
					pcWrite[0] = pcRead[0];
					pcWrite++;
					pcRead ++;
					break;
				}
			}
			//skip "
			if( pcWrite[-1] == '"' )
				pcWrite[-1] = 0;
			//*(pcWrite - 1) = 0;
			Safe_Delete(field.data.szValue);
			//if( field.data.szValue )
			//	delete[] field.data.szValue;

            std::string strContent = ST(g_szStringValueTemp);
            int nLength = strContent.size();
			field.data.szValue = new char[ nLength + 1];
            memset( field.data.szValue, 0, nLength + 1 );
			sprintf_s( field.data.szValue, nLength + 1, "%s", strContent.c_str() );
			//strcpy( field.data.szValue,strContent.c_str() );

		}
		else
		{
			memcpy(g_szValueTemp, szString, min((pcFind-szString), sizeof(g_szValueTemp)));
			if( strchr( g_szValueTemp,'.') )
			{
				field.iFieldType = field_float;
				field.data.fValue = (float)atof( g_szValueTemp );
			}
			else
			{
				field.iFieldType = field_int;
				field.data.iValue = atoi( g_szValueTemp );
			}
		}

	}
	return pcFind + 1;
}

char* CSlkReader::GetRowOrLineNO(char *szString,int &iValue )
{
	//CSALocker locker(this);
	char *pcFind;
	int iRet  = (int)strcspn( szString,";\r\n");
	if( iRet == 0 )
		return 0;
	pcFind = szString;
	pcFind += iRet;

	if( pcFind && pcFind - szString >= 0 && pcFind - szString < 64000)
	{
		g_szValueTemp[ (pcFind - szString) ] = 0;
		memcpy(g_szValueTemp, szString, min((pcFind-szString), sizeof(g_szValueTemp)) );
		iValue = atoi( g_szValueTemp );
		return pcFind;
	}
	
	return 0;
}

CSlkReader::SLine *CSlkReader::FindLine( int iLine,bool bAddIfNotFound )
{
	//CSALocker locker(this);
	/*listLine::iterator it;
	for( it = m_list.begin() ; it != m_list.end() ; it ++ )
	{
		if( (*it)->iLineNo == iLine )
		{
			return &( *it );
		}
		if( (*it)->iLineNo > iLine )
			break;
	}*/

	if( m_pLastFindLine )
	{
		if( m_pLastFindLine->iLineNo == iLine )
			return m_pLastFindLine;
	}

	mapLine::iterator itFind;
	itFind = m_mapIndex.find( iLine );
	if( itFind != m_mapIndex.end() )
	{
		m_pLastFindLine = (*itFind).second;
		return m_pLastFindLine;
	}
	if( !bAddIfNotFound )
		return 0;
	SLine* pLine = new SLine;
	if( !pLine )
		return 0;
	pLine->iLineNo = iLine;
	//m_list.insert( it,pLine );
	m_list.push_back( pLine );
	if( iLine > m_iMaxLineNo )
		m_iMaxLineNo = iLine;
	m_mapIndex.insert( mapLine::value_type( iLine,pLine ) );
	m_pLastFindLine = pLine;
	return m_pLastFindLine;
}

int	 CSlkReader::FindFirstLineByIntField( int iFieldNo,int iValue )
{
	//CSALocker locker(this);
	for (int i=0; i<m_iMaxLineNo; i++)
	{
		if (ret_succ == GotoNextLine(i))
		{
			int val = 0;
			if (GetIntField(iFieldNo, val))
			{
				if (iValue == val)
				{
					return i;
				}
			}
		}
	}
	return -1;
}

int	 CSlkReader::FindLineByIntField( int iFieldNo,int iValue )
{
	//CSALocker locker(this);
	listLine::iterator it;
	
	SField *pFieldLocal;
	for( it = m_list.begin() ; it != m_list.end() ; it ++ )
	{
		m_pCurGetLine = (*it);
		pFieldLocal = GetFieldOfLine( iFieldNo );
		if( !pFieldLocal )
			continue;
		if( field_int != pFieldLocal->iFieldType )
			continue;
		if( pFieldLocal->data.iValue != iValue )
			continue;
		return m_pCurGetLine->iLineNo;
	}
	return -1;
}

void CSlkReader::SetValue( CSlkReader::SLine *pLine,int iX,SField &field  )
{
	//CSALocker locker(this);
	if( !pLine )
		return;
	SField *pField = 0;

	int iSize =  (int)pLine->vector.size();	

	if( iSize < iX + 1 )
	{
		for( int i = iSize ; i <= iX ; i ++ )
		{
			pLine->vector.push_back( NULL );
		}
	}
	pField = new SField;
	*pField = field;

	// added, jiayi, [2009/6/3]
	if( pLine->vector[ iX ] )
	{
		if( field_string == pLine->vector[ iX ]->iFieldType )
		{
			delete[] pLine->vector[ iX ]->data.szValue;
		}
		Safe_Delete(pLine->vector[ iX ]);
	}
	pLine->vector[ iX ] = pField;
}


bool CSlkReader::ReadFromFile( const char *szFile )
{
	//CSALocker locker(this);

	if( g_SlkVFS.IsOpen() )
	{	
		size_t size = 0;
		if (!g_SlkVFS.GetUnitLength(szFile, size))
		{
			return FALSE;
		}
		unsigned char *pbyMemory = new unsigned char[size];
		if (!g_SlkVFS.GetUnit(szFile, pbyMemory, size))
		{
			delete[] pbyMemory;
			pbyMemory = NULL;
			return FALSE;
		}

        ReadFromString( (char*)pbyMemory, size );
		InitFiledName();

		delete []pbyMemory;
		pbyMemory =NULL;

		return TRUE;
	}

	f_Handle *fp;
	fp = packet_namespace::w_fopen( szFile,"rb" );
	if( !fp )
		return false;
	DWORD dwSize;
	char *szBuf;
	packet_namespace::w_fseek( fp,0,SEEK_END );
	dwSize = packet_namespace::w_ftell(fp);
	packet_namespace::w_fseek( fp,0,SEEK_SET );
	szBuf = new char[ dwSize + 1 ];

	if( !szBuf )
	{
		packet_namespace::w_fclose( fp );
		return false;
	}
	szBuf[ dwSize ] = 0;
	bool bRet = false;
	if( 1 ==packet_namespace::w_fread( szBuf,dwSize,1,fp ) )
	{   
		bRet = ReadFromString( szBuf, dwSize + 1 );
	}	

	delete[] szBuf;
	packet_namespace::w_fclose(fp);

	//if( stricmp( szFile, "slk\\weapon.slk" ) == 0 )
	//{
	//	int k = 0;
	//}
	InitFiledName();

	return bRet;
}

bool CSlkReader::ReadFromString( char *szString,int iSize )
{
	//CSALocker locker(this);

	FreeAll();
	int iYValue = 0;
	int iXValue = 0;

	char *pcChar = szString;
	char *pcNext = 0;
	SLine *pCurLine = 0;	
	bool bNewLine = true;
	bool bValueLine = false;
	
	//int nTimes = 0;
	DWORD dwTime = HQ_TimeGetTime();

	char s[256];
	_snprintf(s, sizeof(s)-1, "/record %ld", iSize/1024);
	OutputSlkLoadingMessage( s );

	while( 0 != pcChar && 0 != *pcChar)
	{
		if( HQ_TimeGetTime()-dwTime > 200 )
		{
			dwTime = HQ_TimeGetTime();
			//switch( d++%4 )
			//{
			//case 0:
			//	OutputSlkLoadingMessage("/L分析中");
			//	break;
			//case 1:
			//	OutputSlkLoadingMessage("/L 分析中");
			//	break;
			//case 2:
			//	OutputSlkLoadingMessage("/L  分析中");
			//	break;
			//case 3:
			//	OutputSlkLoadingMessage("/L   分析中");
			//	break;
			//}
			int nNumPassedK = (pcChar-szString)/1024;
			_snprintf(s, sizeof(s)-1, "/L(%ldK字节)/(%ldK字节)", nNumPassedK, iSize/1024);
			OutputSlkLoadingMessage( s );

			_snprintf(s, sizeof(s)-1, "/process %ld", (pcChar-szString)/1024);
			OutputSlkLoadingMessage( s );

		}
		if( pcChar - szString >= iSize )
			break;		
		if( bNewLine )
		{
			if( ( 'c' == pcChar[0] || 'C' == pcChar[0] )
				&& ( ';' == pcChar[1]  ) )
			{
				bValueLine = true;
			}
			else
				bValueLine = false;
		}
		bNewLine = false;

		switch( *pcChar ) 
		{
		case ';':	
			pcChar ++;
			switch( *pcChar )
			{
			case 'X':
				{
					pcNext = GetRowOrLineNO( pcChar + 1,iXValue );

					pcChar = pcNext;
				}
				break;
			case 'Y':
				{
					pcNext = GetRowOrLineNO( pcChar + 1,iYValue );
					if( pcNext )
					{
						pCurLine = FindLine( iYValue );
					}
					pcChar = pcNext;
				}
				break;
			case 'K':
				{
					//查看
					if( !bValueLine )
					{
						pcChar ++;
						break;
					}
					//数值
					SField field;
					pcNext = GetFieldValue( pcChar + 1,field );
					if( pcNext )
					{
						SetValue( pCurLine,iXValue,field );
					}
					pcChar = pcNext;
				}
				break;
			case ';':
				pcChar ++;
				break;
			default:
				break;
			}
			break;		
		case '\n':
			bNewLine = true;
			pcChar ++;
			break;
		default:
			pcChar ++;
			break;
		}
	}
	
	ClearBlankRow();

	m_pCurGetLine = FindLine( 0,false );
	
	return true;
}

int		CSlkReader::GetFieldNumOfLine()
{
	//CSALocker locker(this);
	if( !m_pCurGetLine )	
		return 0;
	return (int)m_pCurGetLine->vector.size();
}

CSlkReader::SField *CSlkReader::GetFieldOfLine( int iFieldNo )
{
	//CSALocker locker(this);
	if( !m_pCurGetLine )	
		return 0;
	if( iFieldNo >= (int)m_pCurGetLine->vector.size() )
		return 0;
	SField *pField = m_pCurGetLine->vector[ iFieldNo ];
	if( !pField )
		return 0;
	return pField;
}

int CSlkReader::GotoNextLine( int iLine )
{
	//CSALocker locker(this);
	if( iLine > m_iMaxLineNo )
		return ret_readover;
	m_pCurGetLine = FindLine( iLine,false );
	if(m_pCurGetLine != 0)
		return ret_succ;	
	return ret_nothisline;
}

void CSlkReader::OutDebugLine(SLine*pLine,FILE *fp)
{
	//CSALocker locker(this);
	SField *pField = NULL;
	for( int i = 0 ; i < (int)pLine->vector.size(); i ++ )
	{	
		pField = (pLine->vector[i]);
		if( !pField )
			continue;
		fprintf( fp,"(%d,%d)  :",i,pLine->iLineNo);
		switch( pField->iFieldType ) 
		{
		case field_string:
			fprintf( fp,"%s",pField->data.szValue );
			break;
		case field_int:
			fprintf( fp,"%d",pField->data.iValue );
			break;
		case field_float:
			fprintf( fp,"%f",pField->data.fValue );
			break;		
		}
		fprintf( fp,"\r\n");
	}
}

void CSlkReader::OutDebugInfo()
{
	listLine::iterator it = m_list.begin();
	FILE *fp;
	fp = fopen( "slkinfo.txt","ab" );
	fprintf( fp,"\r\n\r\nbegin info log:\r\n" );
	while( it != m_list.end() )
	{
		OutDebugLine( (*it),fp );	

		it ++;
	}	
	fclose( fp );
}

bool CSlkReader::GetIntField( int iCol,int &iValue )
{
	//CSALocker locker(this);
	//
	SField *pField;
	//
	//
	pField = GetFieldOfLine( iCol );
	if( !pField )
		return false;
	switch( pField->iFieldType )
	{
	case CSlkReader::field_int: 
		iValue = pField->data.iValue;
		break;
	case CSlkReader::field_float: 
		return false;
		break;
	case CSlkReader::field_string:
		return false;		
	}	
	return true;
}

bool CSlkReader::GetFloatField( int iCol, float &fValue )
{
	//CSALocker locker(this);
	SField *pField;
	pField = GetFieldOfLine( iCol );
	if(!pField)
		return false;
	switch( pField->iFieldType )
	{
	case CSlkReader::field_int:
		fValue = (float)(pField->data.iValue);
		break;
	case CSlkReader::field_float:
		fValue = pField->data.fValue;
		break;
	case CSlkReader::field_string:
		return false;
	}
	return true;
}

bool CSlkReader::GetStringField( int iCol,string& strRetValue )
{
	//CSALocker locker(this);
	CSlkReader::SField *pField;
	pField = GetFieldOfLine( iCol );
	if( !pField )
		return false;
	if( CSlkReader::field_string != pField->iFieldType )
		return false;
	if( !pField->data.szValue )
		return false;
	strRetValue = pField->data.szValue;
	return true;
}

bool CSlkReader::GetStringField( int iCol,char **pstrRetValue,CFlyMemAllocer*pAllocer )
{
	//CSALocker locker(this);
	int iStringSize;
	CSlkReader::SField *pField;
	pField = GetFieldOfLine( iCol );
	if( !pField )
		return false;
	if( CSlkReader::field_string != pField->iFieldType )
		return false;
	if( !pField->data.szValue )
		return false;
	iStringSize = strlen( pField->data.szValue );	
	if(!(*pstrRetValue))
		(*pstrRetValue) = (char*)pAllocer->Malloc( iStringSize + 1 );
	if( !(*pstrRetValue) )
		return false;
	strcpy( (*pstrRetValue),pField->data.szValue );
	return true;
}

//////////////////////////////////////////////////////////////////////////
int CSlkReader::ConvHeaderToId( const char* pszCol )
{
	//CSALocker locker(this);
	if( !pszCol )
	{
		return -1;
	}
	char c = pszCol[0];
	if( c >= 'a' && c <= 'z' ) 
		return c-'a'+1;
	if( c >= 'A' && c <= 'Z')
		return c-'A'+1;
	return -1;
}

bool CSlkReader::GetIntField( const char* pszCol,int &iValue )
{
	//CSALocker locker(this);
	int nCol = ConvHeaderToId( pszCol );
	if( nCol == -1 )
		return false;
	return GetIntField( nCol, iValue );
}

//读取string
bool CSlkReader::GetStringField( const char* pszCol,std::string& pstrRetValue)
{
	//CSALocker locker(this);
	int nCol = ConvHeaderToId( pszCol );
	if( nCol == -1 )
		return false;
	return GetStringField( nCol, pstrRetValue );
}

//读取string
bool CSlkReader::GetStringField( const char* pszCol,char **pstrRetValue,CFlyMemAllocer*pAllocer )
{
	//CSALocker locker(this);
	int nCol = ConvHeaderToId( pszCol );
	if( nCol == -1 )
		return false;
	return GetStringField( nCol, pstrRetValue, pAllocer );
}
//读取浮点
bool CSlkReader::GetFloatField( const char* pszCol, float &fValue )
{
	//CSALocker locker(this);
	int nCol = ConvHeaderToId( pszCol );
	if( nCol == -1 )
		return false;
	return GetFloatField( nCol, fValue );
}

//////////////////////////////////////////////////////////////////////////


void CSlkReader::ClearBlankRow()
{
	//CSALocker locker(this);
	listLine::iterator it,itNext;

	SLine *pLine;
	//SField *pFieldLocal;
	for( it = m_list.begin() ; it != m_list.end() ; )
	{	

		itNext = it;
		itNext ++;
		pLine = (*it);
		if( 0 == pLine->vector.size() )
		{
			if( m_pLastFindLine == pLine )
				m_pLastFindLine = 0;
			m_list.erase( it );
			//清除索引
			mapLine::iterator itFind = m_mapIndex.find( pLine->iLineNo );
			m_mapIndex.erase( itFind );
			delete pLine;
		}

		it = itNext;
	}
}

void CSlkReader::InitFiledName()
{
	//CSALocker locker(this);
    GotoNextLine( 2 );

    for( int i=0; i<=256; i++ )
    {
        std::string tempName;
        if( !GetStringField( i, tempName ) )
            continue;
        m_mapFiledNameToId.insert( std::map<std::string,int>::value_type( tempName, i ) );
		OutputSlkLoadingMessage( "    字段[%s]", tempName.c_str() );
	}
}

int CSlkReader::GetFiledNameID( const char * strName )
{
	//CSALocker locker(this);
    std::string strFiledName = strName;
    std::map<std::string,int>::iterator itr = m_mapFiledNameToId.find( strFiledName );
    if( itr != m_mapFiledNameToId.end() )
        return itr->second;
	return -1;
}

bool CSlkReader::GetIntFieldByName( const char* pszColName,int &iValue )
{
	//CSALocker locker(this);
	iValue = 0;
    int iCol = GetFiledNameID( pszColName );
    if( iCol == -1 )
	{
        return false;
	}
    
	return GetIntField( iCol, iValue );
}
//bool CSlkReader::GetIntFieldByName( const char* pszColName,short &shValue )
//{
//	int nValue = 0;
//	if( GetIntFieldByName( pszColName, nValue ) )
//	{
//		shValue = nValue;
//		return true;
//	}
//	return false;
//}
//读取string
bool CSlkReader::GetStringFieldByName( const char* pszColName,std::string& pstrRetValue)
{
	//CSALocker locker(this);
    int iCol = GetFiledNameID( pszColName );
    if( iCol == -1 )
        return false;
	return GetStringField( iCol, pstrRetValue );
}
//读取string
bool CSlkReader::GetStringFieldByName( const char* pszColName,char **pstrRetValue,CFlyMemAllocer*pAllocer )
{
	//CSALocker locker(this);
    int iCol = GetFiledNameID( pszColName );
    if( iCol == -1 )
        return false;
	return GetStringField( iCol, pstrRetValue, pAllocer );
}
//读取浮点
bool CSlkReader::GetFloatFieldByName( const char* pszColName, float &fValue )
{
	//CSALocker locker(this);
    int iCol = GetFiledNameID( pszColName );
    if( iCol == -1 )
        return false;
	return GetFloatField( iCol, fValue );
}
//
//bool CSlkReader::InsertLine( int nLineIndex )
//{ 
//    return 0;
//}
//
//bool CSlkReader::DeteleLine( int nLineIndxe ) 
//{ 
//    return true;
//}
