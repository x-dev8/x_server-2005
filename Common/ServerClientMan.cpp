#include "Serverclientman.h"
#include <assert.h>
#include <windows.h>

//extern gDebugLog theLog;

CServerClientMan::CServerClientMan( int iFreeQueueSize,int iBlockSize )
:m_free( iFreeQueueSize )
{
	m_iBlockSize = iBlockSize;
}

void CServerClientMan::Clear(void)
{
	int iUsed,iSize;
	int iLoopUsed,iLoopSize;
	void **ppClient;
	iUsed = m_free.GetUsed();
	iSize = m_free.GetSize();

	for( iLoopUsed = 0 , iLoopSize = 0 ;
		iLoopUsed < iUsed && iLoopSize < iSize ; iLoopSize ++ )
	{
		ppClient = m_free[ iLoopSize ];
		if( !ppClient )
			continue;
		iLoopUsed ++;
		//theLog.OutputWithTime( "Free :%x\r\n",*ppClient );
		delete *ppClient ;
		//找到了
		m_free.Free( iLoopSize );		
	}
}

CServerClientMan::~CServerClientMan(void)
{
	Clear();
}

void *CServerClientMan::AllocClient( void )
{
	int iUsed,iSize;
	int iLoopUsed,iLoopSize;
	void **ppClient;
	iUsed = m_free.GetUsed();
	iSize = m_free.GetSize();
	if( iUsed <= 0 )
	{
		return new char[ m_iBlockSize ];
	}
	else
	{
		for( iLoopUsed = 0 , iLoopSize = 0 ;
			iLoopUsed < iUsed && iLoopSize < iSize ; iLoopSize ++ )
		{
			ppClient = m_free[ iLoopSize ];
			if( !ppClient )
				continue;
			iLoopUsed ++;
			//找到了
			m_free.Free( iLoopSize );
			return *ppClient;
		}
	}
	return 0;
}

void CServerClientMan::FreeClient( void *pClient,bool bRealFree )
{
	if( bRealFree )
	{
		delete pClient ;
		return;
	}
	int iID = m_free.Malloc();
	if( -1 == iID )
	{
		assert( false );
		Sleep( 100 );
		delete pClient ;
		return;
	}
	*m_free[ iID ] = pClient;
}
