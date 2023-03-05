#include "Me3d/MeMemoryTracker.h"

//---------------------------------------------------------------------
MeMemoryTracker* MeMemoryTracker::ms_This = 0;
DWORD MeMemoryTracker::ms_dwInitTime = 0;
//---------------------------------------------------------------------
MeMemoryTracker* MeMemoryTracker::Instance()
{	
	if( !ms_This )
		Init();
	return ms_This;
}
//---------------------------------------------------------------------
void MeMemoryTracker::Init()
{
	if( !ms_This )
		ms_This = MeDefaultNew MeMemoryTracker;	
	ms_dwInitTime = timeGetTime();
}
//---------------------------------------------------------------------
void MeMemoryTracker::Shutdown()
{
	if( !ms_This )
		return;
	MeDefaultDelete ms_This;
	ms_This = 0;
}
//---------------------------------------------------------------------
void MeMemoryTracker::Allocate( void* pMem, 
							   const char* pcFile, 
							   int nLine, 
							   const char* pcFunction )
{
	::EnterCriticalSection( &m_csAccess );
	++m_uiTotalObjectCount;
	m_MemInfos[*(DWORD*)&pMem] = MeMemInfo( pcFile, 
		nLine, pcFunction, timeGetTime() - ms_dwInitTime );
	if( 0 )
	{
		OutputMemInfo();
		m_MemInfos.clear();
	}
	::LeaveCriticalSection( &m_csAccess );
}
//---------------------------------------------------------------------
void MeMemoryTracker::Deallocate( void* pMem )
{
	::EnterCriticalSection( &m_csAccess );
	MeMemInfoContainer::iterator it =	
		m_MemInfos.find( *(DWORD*)&pMem );
	if( it != m_MemInfos.end() )
	{
		--m_uiTotalObjectCount;
		m_MemInfos.erase( it );
	}
	else
	{
		//assert( 0 && "memory not found?" );
	}
	::LeaveCriticalSection( &m_csAccess );
}
//---------------------------------------------------------------------
// void MeMemoryTracker::OutputMemInfo()
// {
// // 	OutputDebugStringA("\n==================Memory Tracker Begin=================\n" );
// // 	::EnterCriticalSection( &m_csAccess );
// // 	MeMemInfoContainer::iterator it = m_MemInfos.begin();
// // 	char acOutput[255] = {0};
// // 	if( m_MemInfos.size() != 0 )
// // 		OutputDebugStringA( "\nmemory leak!!" );
// // 	for( ; it != m_MemInfos.end() ; ++ it )
// // 	{		
// // 		sprintf_s( acOutput, 255, "\nborn: %d, file:%s, line:%d, func:%s", 
// // 			(*it).second.m_dwBornTime, (*it).second.m_acFile, (*it).second.m_nLine,
// // 			(*it).second.m_acFunction );
// // 		OutputDebugStringA( acOutput );
// // 	}
// // 	::LeaveCriticalSection( &m_csAccess );
// // 	OutputDebugStringA("\n==================Memory Tracker End===================\n" );	
// 	::EnterCriticalSection( &m_csAccess );
// 	std::multimap<std::string, MeMemInfo> tempInfos;
// 	MeMemInfoContainer::iterator it = m_MemInfos.begin();
// 	char acOutput[255] = {0};
// 	if( m_MemInfos.size() != 0 )
// 		OutputDebugStringA( "\nmemory leak!!" );
// 	for( ; it != m_MemInfos.end() ; ++ it )
// 	{		
// 		//tempInfos[(*it).second.m_dwBornTime] = (*it).second;
// 		tempInfos.insert( std::multimap<std::string, MeMemInfo>::value_type( 
// 			(*it).second.m_acFunction, (*it).second ) );
// 	}	
// 	std::multimap<std::string, MeMemInfo>::iterator itTemp = tempInfos.begin();
// 
// 	OutputDebugStringA("\n==================Memory Tracker Begin=================\n" );
// 	for( ; itTemp != tempInfos.end(); ++itTemp )
// 	{
// 		sprintf_s( acOutput, 255, "\nborn: %d, file:%s, line:%d, func:%s", 
// 			(*itTemp).second.m_dwBornTime, (*itTemp).second.m_acFile, (*itTemp).second.m_nLine,
// 			(*itTemp).second.m_acFunction );
// 		OutputDebugStringA( acOutput );
// 	}
// 	::LeaveCriticalSection( &m_csAccess );
// 	OutputDebugStringA("\n==================Memory Tracker End===================\n" );
// }
//---------------------------------------------------------------------
void MeMemoryTracker::OutputMemInfo()
{
	::EnterCriticalSection( &m_csAccess );
	std::map<std::string, int> tempInfos;
	MeMemInfoContainer::iterator it = m_MemInfos.begin();
	char acOutput[255] = {0};
	if( m_MemInfos.size() != 0 )
		OutputDebugStringA( "\nmemory leak!!" );
	for( ; it != m_MemInfos.end() ; ++ it )
	{		
		//tempInfos[(*it).second.m_dwBornTime] = (*it).second;
		if( tempInfos.find( (*it).second.m_acFunction ) != tempInfos.end() )
			++tempInfos[(*it).second.m_acFunction];
		else
			tempInfos[(*it).second.m_acFunction] = 1;
	}	
	std::map<std::string, int>::iterator itTemp = tempInfos.begin();

	OutputDebugStringA("\n==================Memory Tracker Begin=================\n" );
	for( ; itTemp != tempInfos.end(); ++itTemp )
	{
		sprintf_s( acOutput, 255, "file:%s, count:%d\n", 
			(*itTemp).first.c_str(), (*itTemp).second );
		OutputDebugStringA( acOutput );
	}
	::LeaveCriticalSection( &m_csAccess );
	OutputDebugStringA("\n==================Memory Tracker End===================\n" );
}
//---------------------------------------------------------------------