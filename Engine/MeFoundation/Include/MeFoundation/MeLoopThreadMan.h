#pragma once
#include "MeFoundation/MeLoopThread.h"

/**
* @brief Manager of threads.
*/
class MEFOUNDATION_ENTRY MeLoopThreadMan : public Singleton< MeLoopThreadMan >
{
//Construction.
private:
	friend class Singleton< MeLoopThreadMan >;

	/// Constructor.
	MeLoopThreadMan();
	
	/// Destructor.
	~MeLoopThreadMan();

// Overload operator.
private:
	/// Disable assignment operator.
	const MeLoopThreadMan& operator=( const MeLoopThreadMan& kClass ){ return *this; }

	/// Disable copy constructor.
	MeLoopThreadMan( const MeLoopThreadMan& kClass ){}

// Methods.
public:
	/// Find a registered pointer.
	BOOL FindPointer( void* p );

	/// Register a pointer.
	BOOL RegisterPointer( void* p );

	/// Unregister a pointer.
	BOOL UnRegisterPointer( void* p );   	

	/// Push a request to cache.
	void PostMexLoadingReq( MeLoopThreadReq* req );

	/// Push a thread to container. In fact, its already started.
	void StartThreads( MeLoopThread* pThread );

	/// Close all threads.
	void CloseThreads();

	void PauseThreads();

	void ResumeThreads();

	/// Function in main loop.
	void MainThreadProcess();
	
	/// Clear request list.
	void ClearLoadingList();

// Members.
protected:
	/// Store pointers.
	typedef std::vector<void*> Pointers;
	typedef Pointers::iterator PointersIterator;
	Pointers m_Pointers;

	/// Thread Container.
	typedef std::vector<MeLoopThread*> LoopThreads;
	typedef LoopThreads::iterator LoopThreadsIter;
	LoopThreads m_LoopThreads;
};