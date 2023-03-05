/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SlkReader.cpp
* Create: 	10/06/06
* Desc:		SLK文件读取
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include "IFileReader.h"
#include "SlkReader.h"

namespace
{
	const char* sNullString = "";
	static TSLKValue s_defaultValue;

};

#define MAX_NUMBERSTRING_LENGTH		64


TSLKValue::TSLKValue()
{
	intValue	= 0;
	floatValue	= 0.0f;
	stringValue	= NULL;
}

TSLKValue::~TSLKValue()
{
	if( NULL != stringValue )
	{
		delete stringValue;
		stringValue = NULL;
	}
}

int	TSLKValue::ToInt32() const
{
	return intValue;
}

double TSLKValue::Todouble() const
{
	return floatValue;
}

const char* TSLKValue::ToString() const
{
	if( NULL != stringValue )
	{
		return stringValue;
	}else
	{
		return sNullString;
	}
}

//////////////////////////////////////////////////////////////////////////

TSLKRow::TSLKRow()
{
	value = NULL;
}

TSLKRow::~TSLKRow()
{
	SAFE_DELETE_ARRAY( value );
}

const TSLKValue* TSLKRow::GetValue( unsigned int pColumn ) const
{
	return &( value[pColumn] );
}

const bool TSLKRow::SetValue( unsigned int pColumn, TSLKValue* pValue )
{
	value[pColumn].intValue		= pValue->intValue;
	value[pColumn].floatValue	= pValue->floatValue;
	if( NULL != pValue->stringValue )
	{
		size_t len = strlen( pValue->stringValue );
		value[pColumn].stringValue = new char[len+2];
		memcpy( value[pColumn].stringValue, pValue->stringValue, (len+1)*sizeof(char) );
	}else
	{
		SAFE_DELETE_ARRAY( value[pColumn].stringValue );
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//成员函数定义
////////////////////////////////////////////////////////////////////////////////

SlkReader::SlkReader()
{
	m_column	= NULL;
	m_data		= NULL;

	m_row		= 0;
	m_col		= 0;

	m_curRow	= 0;
	m_curCol	= 0;

	m_curPos	= 0;
}

SlkReader::~SlkReader()
{
	Close();
}

bool SlkReader::LoadFromFile( const char* pFileName )
{
	assert( NULL == m_data );
	assert( NULL == m_column );

	IFileReader* fileReader = NULL;
	if( !CreateFileReader( &fileReader ) )
		return false;

	bool isLoadOk = true;
	_TSLKValueArray.clear();
	char*	buffer = NULL;
	unsigned int	bufferSize = 0;
	try
	{
		if( !(fileReader->OpenFile( pFileName )) )
			throw "Failed to call OpenFile\n";
		bufferSize = fileReader->GetSize();
		assert( bufferSize > 0 );
		buffer = new char[bufferSize+1];
		memset( buffer, 0, (bufferSize + 1) * sizeof(char) );
		//不知道为什么要1K 1K的读，测试了与文件一次性读取的结果相同，所以改成一次性读取，速度更快。[QL]
		//char tmpBuffer[1024];
		//memset( tmpBuffer, 0, 1024 * sizeof(char) );
		//char* ptrBuffer = buffer;
		//size_t size = fileReader->Read( (void*)tmpBuffer, 1024 );
		//assert( "出现异常错误！" && size <= 1024 );
		//size_t count = 0;
		//while( size > 0 )		
		//{
		//	memcpy( ptrBuffer, tmpBuffer, size );
		//	ptrBuffer	+= size;
		//	count		+= size;
		//	memset( tmpBuffer, 0, 1024 * sizeof(char) );
		//	size = fileReader->Read( tmpBuffer, 1024 );
		//	assert( "出现异常错误！" && size <= 1024 );
		//}
		size_t count = fileReader->Read( buffer, bufferSize+1 );

		assert( "文件大小错误！" && bufferSize == count );
		if( bufferSize != count )
			throw "bufferSize != count \n";

		if( !GetInfoFromMemory( buffer, bufferSize ) )
			throw "Failed to call LoadFromMemory\n";

		SAFE_DELETE_ARRAY( buffer );

	}
	catch( const char* s )
	{
		SAFE_DELETE_ARRAY( buffer );
		isLoadOk = false;
	} 

	fileReader->Close();
	SAFE_DELETE( fileReader );

	for( unsigned int i = 0; i < _TSLKValueArray.size(); i++ )
	{
		_TSLKValue* p = _TSLKValueArray[i];
		SAFE_DELETE( p );
	}
	_TSLKValueArray.clear();

	return isLoadOk;
}


static bool IsNumberChar( char pChar )
{
	if( (pChar >= '0' && pChar <= '9') || ('.' == pChar) || ('-' == pChar) || ('+' == pChar) )
	{
		return true;
	}
	else
		return false;
}


static bool IsReturnChar( char pChar )
{
	if( '\n' == pChar || '\r' == pChar )
		return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////

enum emSlkKeyType
{
	ESKY_Unkown = 0,
	ESKY_F,
	ESKY_C,
	ESKY_End,
	ESKY_DataEnd
};

static emSlkKeyType GetLineKeyType( char* pString )
{
	if( '\0' == *pString )
		return ESKY_DataEnd;

	if( 'F' == *pString )
	{
		if( ';' == *(pString + 1) )
			return ESKY_F;
	}
	if( 'C' == *pString )
	{
		if( ';' == *(pString + 1) )
			return ESKY_C;
	}
	if( 'E' == *pString )
	{
		return ESKY_End;
	}
	return ESKY_Unkown;
}

//////////////////////////////////////////////////////////////////////////

enum emSlkValueType
{
	ESVT_Unkown = 0,
	ESVT_X,
	ESVT_Y,
	ESVT_K
};

static emSlkValueType GetValueType( char pChar )
{
	if('X' == pChar) 
		return ESVT_X;

	if('Y' == pChar)
		return ESVT_Y;

	if( 'K' == pChar )
		return ESVT_K;

	return ESVT_Unkown;
}

static char* FetchToNextLine( char* pData, bool& pIsEnd )
{
	char* ptrData = pData;
	int i = 0;
	for( ;; )
	{
		if( '\n' == *ptrData )
		{
			ptrData++;
			return ptrData;
		}
		if( '\0' == *ptrData )
		{
			pIsEnd = true;
			return ptrData;
		}
		ptrData++;
	}
}

static char* GetSLKNumValue( char* pData, char* pOutValue, bool& pIsEnd )
{
	char* ptrValue = pOutValue;
	char* ptrData  = pData;
	int len = 0;
	for(;;)
	{
		if( '\n' == *ptrData++ ) 
			return ptrData;

		if('\0' == *ptrData) 
		{
			pIsEnd = true;
			return ptrData;
		}

		if( !IsNumberChar( *ptrData ) )
			return ptrData;

		if( len < MAX_SLK_NUM_STRING_LEN )
			*(ptrValue++) = *(ptrData);
		else
		{
			assert( "数字长度错误！" && false );
		}
		len++;
	}

	return NULL;
}


static char* GetSLKStringValue( char* pData, char* pOutValue, bool& pIsEnd )
{
	char* ptrValue = pOutValue;
	char* ptrData  = pData;
	ptrData++;
	int len = 0;
	for(;;)
	{
		if('\n' == *ptrData++) 
		{
			if( '"' == *(ptrValue-1) )
				*(ptrValue-1) = '\0';
			return ptrData;
		}
		if('\0' == *ptrData)
		{
			pIsEnd = true;
			return ptrData;
		}

		if( len < MAX_SLK_VALUE_STRING )
		{
			if( !IsReturnChar(*ptrData) )
			{
				*(ptrValue++) = *(ptrData);
			}
		}else
		{
			assert( "SLK文件出错！" && false );
			// ("<<<ERRROR>>>[GetSLKStringValue] \n" );
		}
		len++;
	}

	return NULL;
}


char* SlkReader::FetchKnownKeyValue( char* pData, bool& pIsEnd )
{
	char* ptrData = pData;

	for(;;) 
	{
		if('\n' == *(ptrData++) )	
		{
			return ptrData;
		}

		if('\0' == *ptrData)
		{
			pIsEnd = true;
			return ptrData;
		}

		emSlkValueType valueType = GetValueType( *ptrData );
		switch( valueType ) 
		{
		case ESVT_X:
			{
				char strValue[MAX_SLK_NUM_STRING_LEN];
				memset( strValue, 0, sizeof(char)*MAX_SLK_NUM_STRING_LEN );
				ptrData = GetSLKNumValue( ptrData, strValue, pIsEnd );
				m_curCol = atoi( strValue ) -1;
				if( (int)m_curCol < 0 )
				{
					m_curCol = 0;
					//ZM::Log::global().log( "<<<ERROR>>> Error SLK File." );
				}
			}
			break;
		case ESVT_Y:
			{
				char strValue[MAX_SLK_NUM_STRING_LEN];
				memset( strValue, 0, sizeof(char)*MAX_SLK_NUM_STRING_LEN );
				ptrData = GetSLKNumValue( ptrData, strValue, pIsEnd );
				m_curRow = atoi( strValue ) - 1;
				if( (int)m_curRow < 0 )
				{
					m_curRow = 0;
					//ZM::Log::global().log( "<<<ERROR>>> Error SLK File." );
				}
			}
			break;
		case ESVT_K:
			{
				if( '"' != *(ptrData+1) )
				{
					if( IsNumberChar( *(ptrData+1) ) )
					{
						char strValue[MAX_SLK_NUM_STRING_LEN];
						memset( strValue, 0, sizeof(char)*MAX_SLK_NUM_STRING_LEN );
						ptrData = GetSLKNumValue( ptrData, strValue, pIsEnd );

						m_row = max( m_curRow+1, m_row );
						m_col = max( m_curCol+1, m_col );	

						Assert( m_curRow >= 0 && m_curRow < m_row );
						Assert( m_curCol >= 0 && m_curCol < m_col );

						_TSLKValue* value = new _TSLKValue;
						value->col	= m_curCol;
						value->row	= m_curRow;
						value->value.intValue	= atoi( strValue );
						value->value.floatValue = atof( strValue );
						size_t len = strlen( strValue );
						assert( "SLK文件错误,数字太长！" && MAX_SLK_NUM_STRING_LEN > len );
						value->value.stringValue= new char[len+2];
						memset( value->value.stringValue, 0, (len+2)*sizeof(char) );
						strcpy( value->value.stringValue, strValue );

						_TSLKValueArray.push_back( value );

						//ZM::Log::global().log( "[%d,%d](%f)\n", m_curRow, m_curCol, atof( strValue ) );
					}
				}else
				{
					char strValue[MAX_SLK_VALUE_STRING];
					memset( strValue, 0, sizeof(char)*MAX_SLK_VALUE_STRING );
					ptrData = GetSLKStringValue( ptrData, strValue, pIsEnd );

					m_row = max( m_curRow+1, m_row );
					m_col = max( m_curCol+1, m_col );	

					Assert( m_curRow >= 0 && m_curRow < m_row );
					Assert( m_curCol >= 0 && m_curCol < m_col );

					_TSLKValue* value = new _TSLKValue;
					value->col	= m_curCol;
					value->row	= m_curRow;
					value->value.intValue	= atoi( strValue );
					value->value.floatValue = atof( strValue );
					size_t len = strlen( strValue );
					assert( "SLK文件错误！内容太长" && MAX_SLK_VALUE_STRING > len );
					value->value.stringValue= new char[len+2];
					memset( value->value.stringValue, 0, (len+2)*sizeof(char) );
					strcpy( value->value.stringValue, strValue );

					_TSLKValueArray.push_back( value );

					//ZM::Log::global().log( "[%d,%d](%s)\n", m_curRow, m_curCol, strValue );
				}
			}
			break;
		case ESVT_Unkown:
			break;
		}
	}
}

char* SlkReader::EvalFKeyValue( char* pData, bool& pIsEnd )
{
	return FetchKnownKeyValue( pData, pIsEnd );
}

char* SlkReader::EvalCKeyValue( char* pData, bool& pIsEnd )
{
	return FetchKnownKeyValue( pData, pIsEnd );
}


char* SlkReader::EvalUnknowKey( char* pData, bool& pIsEnd )
{
	return FetchToNextLine( pData, pIsEnd );
}


//
//char* CSlkReader::EvalKeyLine( char* pData, bool& pIsEnd )
//
//// OLD.
//{
//	//assert( strlen( pData ) > 0 );
//	emSlkKeyType type = GetLineKeyType( pData );
//	switch( type ) 
//	{
//	case ESKY_Unkown:
//		pData = EvalUnknowKey( pData, pIsEnd );
//		break;
//	case ESKY_F:
//		pData = EvalFKeyValue( pData, pIsEnd );
//		break;
//	case ESKY_C:
//		pData = EvalCKeyValue( pData, pIsEnd );
//		break;
//	case ESKY_End:
//		pIsEnd	= true;
//		//ZM::Log::global().log( "---- Read SLK File End ---- \n");
//		break;
//	case ESKY_DataEnd:
//		pIsEnd	= true;
//		break;
//	}
//
//	//ZM::Log::global().log( "[EvalKeyLine]%d \n", (int)type );
//
//	if( !pIsEnd )
//		return EvalKeyLine( pData, pIsEnd );
//	else
//		return pData;
//}


void SlkReader::EvalKeyLine( char* pData )
{
	//NiOutputDebugString( "CSlkReader::EvalKeyLine===================\n" );
	bool isEnd = false;
	for(;;)
	{
		emSlkKeyType type = GetLineKeyType( pData );
		switch( type ) 
		{
		case ESKY_Unkown:
			pData = EvalUnknowKey( pData, isEnd );
			break;
		case ESKY_F:
			pData = EvalFKeyValue( pData, isEnd );
			break;
		case ESKY_C:
			pData = EvalCKeyValue( pData, isEnd );
			break;
		case ESKY_End:
		case ESKY_DataEnd:
			isEnd	= true;
			break;
		}
		if( isEnd )
			break;	
	}
	//NiOutputDebugString( "CSlkReader::EvalKeyLine--------------------\n" );
}


bool SlkReader::GetInfoFromMemory( void* pMemory, unsigned int pSize )
{
	if( NULL == pMemory )
		return false;

	char* buffer	= (char*)pMemory;
	m_curRow		= 0;
	m_curCol		= 0;

	EvalKeyLine( buffer );

	if( m_col > 0 /* && m_row > 1 */ )
	{
		m_row = m_row - 1;
		unsigned int i;
		m_column = new TSLKColumn[m_col];
		for( i = 0; i < m_col; i++ )
		{
			memset( m_column[i].name, 0, MAX_SLK_COL_NAME_LEN*sizeof(char) );
			sprintf( m_column[i].name, "Column%03d", i );
		}

		m_data	= new TSLKRow[m_row];
		for( i = 0; i < (m_row); i++ )
		{
			m_data[i].value = new TSLKValue[m_col];
		}
		for( i = 0; i < _TSLKValueArray.size(); i++ )
		{
			_TSLKValue* p = _TSLKValueArray[i];
			if( p->row < 1 )
			{
				if( NULL != (p->value.stringValue) )
				{
					size_t len = strlen(p->value.stringValue);
					assert( "列名称太长！（128字符以内）" && MAX_SLK_COL_NAME_LEN > len );
					memset( m_column[p->col].name, 0, MAX_SLK_COL_NAME_LEN*sizeof(char) );
					memcpy( m_column[p->col].name, p->value.stringValue, (len)*sizeof(char) );
				}
			}else
				m_data[(p->row-1)].SetValue( p->col, &(p->value) );
		}
	}

	return true;
}

void SlkReader::Close()
{
	SAFE_DELETE_ARRAY( m_column );
	if( NULL != m_data )
	{
		for( unsigned int i = 0; i < (m_row); i++ )
		{
			SAFE_DELETE_ARRAY( m_data[i].value );
		}
	}
	SAFE_DELETE_ARRAY( m_data );

	m_row		= 0;
	m_col		= 0;
	m_curRow	= 0;
	m_curCol	= 0;
	m_curPos	= 0;
}


const TSLKValue* SlkReader::GetValue( unsigned int pRow, unsigned int pCol ) const
{
	if( ( pRow < m_row ) && ( pCol < m_col ) )
		return m_data[pRow].GetValue( pCol );
	else {
		Trace( "没有发现该字段\n" );
		return &s_defaultValue;
	}
}


TSLKValue* SlkReader::GetValue( unsigned int pRow, unsigned int pCol ) 
{
	if( ( pRow < m_row ) && ( pCol < m_col ) )
		return (TSLKValue*)(m_data[pRow].GetValue( pCol ));
	else {
		Trace( "没有发现该字段\n" );
		return &s_defaultValue;
	}
}

unsigned int	SlkReader::GetFirstRow()
{
	if( 0 == m_row )
		return SLK_EOF;
	else
	{
		m_curPos = 0;
		return m_curPos;
	}
}


unsigned int SlkReader::GetNextRow()
{
	if( m_curPos < m_row - 1 )
	{
		m_curPos++;
		return m_curPos;
	}else
		return SLK_EOF;
}

unsigned int	SlkReader::GetLastRow()
{
	if( m_row > 0 )
	{
		m_curPos = m_row - 1;
		return m_curPos;
	}else
	{
		m_curPos = 0;
		return SLK_EOF;
	}
}

TSLKValue* SlkReader::GetData( const char* pColName ) 
{
	unsigned int id = this->GetColByName( pColName );
	if( SLK_ERR != id )
		return GetValue( m_curPos, id );
	else
		return &s_defaultValue;
}

const TSLKValue* SlkReader::GetData( unsigned int pColumn ) const
{
	return GetValue( m_curPos, pColumn );
}


TSLKValue* SlkReader::GetData( unsigned int pColumn ) 
{
	return GetValue( m_curPos, pColumn );
}


unsigned int SlkReader::GetColByName( const char* pName )
{
	if( NULL == m_column )
		return SLK_ERR;

	for( unsigned int i = 0; i < m_col; i++ )
	{
		if( strcmp( m_column[i].name, pName ) == 0 )
		{
			return i;
		}
	}
	return SLK_ERR;
}
////////////////////////////////////////////////////////////////////////////////
// end of file
////////////////////////////////////////////////////////////////////////////////