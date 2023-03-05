#pragma once

/**
@desc: thread procedure class
*/
class MEFOUNDATION_ENTRY MeThreadProcedure : 
	public MeCommonAllocObj<MeThreadProcedure>
{
public:
	MeThreadProcedure(){}
	virtual ~MeThreadProcedure(){}

	virtual void Destroy() = 0;

	// thread procedure function
	virtual void ThreadProcedure() = 0;

	// tell the procedure to complete
	virtual void WaitForComplete() = 0;

	// awake the procedure
	virtual void Signal() = 0;

	// post process the processed request
	virtual void MainThreadProcess() = 0;
};

/**
@desc: thread class
*/
class MEFOUNDATION_ENTRY MeThread : 
	public MeCommonAllocObj<MeThread>
{
public:	
	MeThread();
	virtual ~MeThread();

	void SetProcedure( MeThreadProcedure* pkProc ){
		m_pkThreadProc = pkProc;
	}
	inline MeThreadProcedure* GetProcedure(){ return m_pkThreadProc; }	

	static MeThread* CreateThread( MeThreadProcedure* pkProc );


protected:// protected members
	MeThreadProcedure* m_pkThreadProc;

protected:// thread process function
	static void ThreadProc( void* p );
};