#pragma once

#include "MeFoundation/MeFoundationPCH.h"
#include "MeFoundation/MeThread.h"
#include "MeFoundation/MeLoopThreadProcedure.h"

/**
* @brief A type of thread. Will always exist in process.
*/
class MEFOUNDATION_ENTRY MeLoopThread : public MeThread
{
//Construction.
public:
	/// Constructor.
	MeLoopThread( int nThreadInfo ){
		m_nThreadInfo = nThreadInfo;
	}
	
	/// Destructor.
	virtual ~MeLoopThread(){}

	/// Copy constructor.
	MeLoopThread( const MeLoopThread& kClass ){
		m_nThreadInfo = kClass.m_nThreadInfo;
	}

// Overload operator.
public:
	/// Assignment operator.
	const MeLoopThread& operator=( const MeLoopThread& kClass ){
		m_nThreadInfo = kClass.m_nThreadInfo;
		return *this;
	}

// Overload Methods.
public:
	/// Overload CreateThread.
	static MeLoopThread* CreateThread( MeLoopThreadProcedure* pkProc, int nThreadInfo );

// Methods.
public:
	/// Using in main loop.
	inline void MainThreadProcess(){
		GetProcedure()->MainThreadProcess();
	}

	/// Push a request to cache.
	bool IsPause();

	void Pause();

	void Resume();

	/// Push a request to cache.
	void PostMexLoadingReq( MeLoopThreadReq* req );

	/// Clear all loading request.
	void ClearLoadingList();

	/// Set a process speed.
	void SetMainProcessSpeed( int nSpeed );

	/// Set thread info using a integer.
	void SetThreadInfo( int nInfo ){ m_nThreadInfo = nInfo; }

	/// Get thread info.
	int GetThreadInfo() const { return m_nThreadInfo; }

// Members.
protected:
	int m_nThreadInfo;
};