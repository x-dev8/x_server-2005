#include "MeFoundation/MeFoundationPCH.h"
#include "MeFoundation/MeLoopThreadMan.h"
//////////////////////////////////////////////////////////////////////////
MeLoopThreadMan::MeLoopThreadMan()
{

}
//////////////////////////////////////////////////////////////////////////
MeLoopThreadMan::~MeLoopThreadMan()
{
}
////////////////////////////////////////////////////////////////////////
BOOL MeLoopThreadMan::FindPointer( void* p )
{
	for( int i = 0; i < m_Pointers.size(); i++ )
	{
		if( m_Pointers[i] == p )
			return TRUE;
	}
	return FALSE;
}
BOOL MeLoopThreadMan::RegisterPointer( void* p )
{
	for( int i = 0; i < m_Pointers.size(); i++ )
	{
		if( m_Pointers[i] == p )
			return TRUE;
	}
	m_Pointers.push_back( p );
	return TRUE;
}
BOOL MeLoopThreadMan::UnRegisterPointer( void* p )
{
	for( int i = 0; i < m_Pointers.size(); i++ )
	{
		if( m_Pointers[i] == p )
		{
			m_Pointers.erase( m_Pointers.begin()+i );
			return TRUE;
		}
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThreadMan::PostMexLoadingReq( MeLoopThreadReq* req )
{
	if( !req )
		return;

	LoopThreadsIter it = m_LoopThreads.begin();
	for( ; it != m_LoopThreads.end(); ++ it )
	{
		if( (*it)->GetThreadInfo() != req->m_nObjectType )
			continue;
		(*it)->PostMexLoadingReq( req );
		break;
	}
	return;
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThreadMan::StartThreads( MeLoopThread* pThread )
{
	if( !pThread )
		return;

	m_LoopThreads.push_back( pThread );
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThreadMan::CloseThreads()
{
	LoopThreadsIter it = m_LoopThreads.begin();
	for( ; it != m_LoopThreads.end(); ++ it )	
		MeDelete (*it);	

	m_LoopThreads.clear();	
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThreadMan::PauseThreads()
{
	LoopThreadsIter it = m_LoopThreads.begin();
	for( ; it != m_LoopThreads.end(); ++ it )	
	{
		if (!(*it) ->IsPause())
		{
			(*it) ->Pause();
		}		 
	}	
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThreadMan::ResumeThreads()
{
	LoopThreadsIter it = m_LoopThreads.begin();
	for( ; it != m_LoopThreads.end(); ++ it )	
	{
		if ((*it) ->IsPause())
		{
			(*it) ->Resume();
		}		 
	}	
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThreadMan::MainThreadProcess()
{
	LoopThreadsIter it = m_LoopThreads.begin();
	for( ; it != m_LoopThreads.end(); ++ it )
	{
		(*it)->MainThreadProcess();
	}
}
//////////////////////////////////////////////////////////////////////////
void MeLoopThreadMan::ClearLoadingList()
{
	LoopThreadsIter it = m_LoopThreads.begin();
	for( ; it != m_LoopThreads.end(); ++ it )
	{
		(*it)->ClearLoadingList();
	}
}
//////////////////////////////////////////////////////////////////////////