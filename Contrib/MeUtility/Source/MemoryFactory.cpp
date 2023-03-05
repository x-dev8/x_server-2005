#include <assert.h>
#include "memoryfactory.h"
#include "FuncPerformanceLog.h"
#define MAX_MEMORYFACTORY_USER_BLOCKSIZE (1024*256)
BYTE* CMemoryFactory::Block::Alloc( int nWillSize )
{
	guardfunc;
	if( nBufferUsed+nWillSize > nBufferSize )
		return NULL;
	BYTE* pAlloc = &pbyBuffer[nBufferUsed];
	nBufferUsed += nWillSize;
	return pAlloc;
	unguard;
}
CMemoryFactory::CMemoryFactory( int nBlockSize ):
m_nBlockSize(0)
{
	guardfunc;
	m_nBlockSize = nBlockSize;
	unguard;
}

CMemoryFactory::~CMemoryFactory()
{
	guardfunc;
	Destroy();
	unguard;
}
void CMemoryFactory::SetAllocSize( int nBlockSize )
{
	guardfunc;
	m_nBlockSize = nBlockSize;
	unguard;
}
CMemoryFactory::Block* CMemoryFactory::FindSpace( int nWillSize )
{
	guardfunc;
	for( int nBlock = 0; nBlock < m_blocks.size(); nBlock++ )
	{
		Block* pBlock = &m_blocks[nBlock];
		// 看看有没有足够大的地方
		if( pBlock->nBufferUsed+nWillSize <= pBlock->nBufferSize )
			return pBlock;
	}
	return NULL;
	unguard;
}
BYTE* CMemoryFactory::Alloc( int nWillSize )
{
	guardfunc;
	User user;
	if( ( nWillSize > m_nBlockSize/*MAX_MEMORYFACTORY_USER_BLOCKSIZE*/ ) ||
		( m_nBlockSize == 0 ) )
	{
		user.bUseSystemAlloc = TRUE;
		user.pbyBuffer = new BYTE[nWillSize];
		user.nUsedSize = nWillSize;
#ifdef _DEBUG
		if( nWillSize > 4 )
		{
			user.pbyBuffer[0] = 'u';
			user.pbyBuffer[1] = 's';
			user.pbyBuffer[2] = 'e';
			user.pbyBuffer[3] = 'r';
		}
#endif
		m_users.push_back( user );
		return user.pbyBuffer;
	}
	Block* pBlock = FindSpace( nWillSize );
	if( !pBlock )
	{
		Block block;
		block.nBufferSize = m_nBlockSize;
		block.pbyBuffer = new BYTE[block.nBufferSize];
#ifdef _DEBUG
		if( m_nBlockSize > 4 )
		{
			block.pbyBuffer[0] = 'b';
			block.pbyBuffer[1] = 'l';
			block.pbyBuffer[2] = 'o';
			block.pbyBuffer[3] = 'c';
			block.pbyBuffer[3] = 'k';
		}
#endif
		m_blocks.push_back( block );
		pBlock = FindSpace( nWillSize );
	}
	if( !pBlock )
	{
		assert( false );
		return NULL;
	}
	pBlock->nRef++;
	user.pbyBuffer = pBlock->Alloc( nWillSize );
	user.nUsedSize = nWillSize;
	m_users.push_back( user );
	return user.pbyBuffer;
	unguard;
}
BOOL CMemoryFactory::Free( BYTE* pbyBuffer )
{
	if( pbyBuffer == NULL )
	{
		assert( false );
		return FALSE;
	}
	for( int nUser = 0; nUser < m_users.size(); nUser++ )
	{
		User* pUser = &m_users[nUser];
		if( pUser->pbyBuffer == pbyBuffer )
		{
			if( pUser->bUseSystemAlloc )
			{
				delete[] pUser->pbyBuffer;
			}
			//pUser->pbyBuffer = NULL;
			m_users.erase( m_users.begin()+nUser );
			return TRUE;
		}
	}
	assert( false );
	return FALSE;
}
void CMemoryFactory::Destroy()
{
	guardfunc;
	for( int nBlock = 0; nBlock < m_blocks.size(); nBlock++ )
	{
		Block* pBlock = &m_blocks[nBlock];
		// 看看有没有足够大的地方
		if( pBlock->pbyBuffer )
		{
			delete[] pBlock->pbyBuffer;
		}
	}
	m_blocks.clear();
	for( int nUser = 0; nUser < m_users.size(); nUser++ )
	{
		User* pUser = &m_users[nUser];
		if( pUser->bUseSystemAlloc )
		{
			if( pUser->pbyBuffer )
				delete[] pUser->pbyBuffer;
		}
	}
	m_users.clear();
	unguard;
}