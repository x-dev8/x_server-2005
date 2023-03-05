/********************************************************************
	Filename: 	MemoryFactory.h
	MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#pragma once

#include "MeRTLibs.h"

class CMemoryFactory
{
public:
	struct Block
	{
		BYTE*	pbyBuffer;
		int		nBufferSize;
		int		nBufferUsed;
		int		nRef;
		Block():pbyBuffer(NULL),nBufferSize(0),nBufferUsed(0),nRef(0){}
		BYTE*	Alloc( int nWillSize );
	};
	struct User
	{
		BYTE*	pbyBuffer;
		BOOL	bUseSystemAlloc;
		int		nBlock;
		int		nOffset;
		int		nUsedSize;
		User():pbyBuffer(NULL),nBlock(0),nOffset(0),nUsedSize(0),bUseSystemAlloc(FALSE){}
	};
public:
	CMemoryFactory( int nBlockSize = 0 );
	~CMemoryFactory();
	void	SetAllocSize( int nBlockSize );
	BYTE*	Alloc( int nWillSize );
	BOOL	Free( BYTE* pbyBuffer );
	BOOL	FreeBlock( int nBlock );
	Block*	FindSpace( int nWillSize );
	void	Destroy();
protected:
	int		m_nBlockSize;
	std::vector<Block> m_blocks;
	std::vector<User> m_users;
	//int		m_nBlock;
	//int		m_nUser;
};