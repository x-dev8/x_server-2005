
/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	IFileReader.h
* Create: 	10/06/06
* Desc:		文件读取接口
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __IFILEREADER_H__
#define __IFILEREADER_H__

class IFileReader
{
public:
	virtual					~IFileReader(){};

	virtual bool			OpenFile( const char* pFileName ) = 0;
	virtual void			Close() = 0;

	virtual size_t			Read( void* pBuffer, unsigned int pSizeToRead ) = 0;	
	virtual bool			Seek( unsigned int pFinalPosition, int pRelativeMovement = SEEK_SET ) = 0;

	virtual unsigned int	GetSize() const = 0;

};

extern	bool CreateFileReader( IFileReader** pReader );	

#endif	// __IFILEREADER_H__
