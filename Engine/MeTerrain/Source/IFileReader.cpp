/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	IFileReader.cpp
* Create: 	10/06/06
* Desc:		
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "IFileReader.h"

////////////////////////////////////////////////////////////////////////////////
//CFileReader类定义
////////////////////////////////////////////////////////////////////////////////
class CFileReader	: public IFileReader, public MeCommonAllocObj
{
public:
	CFileReader();
	~CFileReader();

	bool	OpenFile( const char* pFileName );
	void	Close();

	size_t	Read( void* pBuffer, unsigned int pSizeToRead );	
	bool	Seek( unsigned int pFinalPosition, int pRelativeMovement = SEEK_SET );

	virtual unsigned int	GetSize() const { return m_size; };

protected:
	FILE*	m_file;
	unsigned int	m_size;
};

////////////////////////////////////////////////////////////////////////////////
//成员函数定义
////////////////////////////////////////////////////////////////////////////////
CFileReader::CFileReader()
{
	m_size		= 0;
	m_file		= NULL;
}

CFileReader::~CFileReader()
{
	Close();	
}

bool CFileReader::OpenFile( const char* pFileName )
{
	assert( NULL == m_file );
	if ( NULL == pFileName ) 
	{
		return false; 
	}

	//char fileName[MAX_PATH];
	//sprintf_s( fileName, "%s", pFileName );

#if _MSC_VER >= 1400
	fopen_s(&m_file, pFileName, "rb");
#else
	m_file = fopen( pFileName, "rb");
#endif

	if ( NULL != m_file )
	{
		// get FileSize
		fseek( m_file, 0, SEEK_END );
		m_size = ftell( m_file );
		fseek( m_file, 0, SEEK_SET );
		return true;
	}

	return false;
}

void CFileReader::Close()
{
	if ( NULL != m_file)
	{
		fclose( m_file);
		m_file		= NULL;
	}

	m_size		= 0;
}

size_t CFileReader::Read( void* pBuffer, unsigned int pSizeToRead )	
{
	if( m_file )
		return fread( pBuffer, 1, pSizeToRead, m_file );
	else 
		return 0;
}


bool CFileReader::Seek( unsigned int pFinalPosition, int pRelativeMovement )
{
	if( m_file )
		return (fseek( m_file, pFinalPosition, pRelativeMovement ) == 0);
	else
		return false;
}

bool CreateFileReader( IFileReader** pReader )	
{
	IFileReader* fileReader = NULL;
	fileReader = MeNew CFileReader();
	if( fileReader == NULL )
		return false;
	*pReader = fileReader;
	return true;
}
////////////////////////////////////////////////////////////////////////////////
// end of file
////////////////////////////////////////////////////////////////////////////////