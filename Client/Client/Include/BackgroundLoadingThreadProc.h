#pragma once

#include <MeFoundation/MeFoundationPCH.h>
#include <MeFoundation/MeThread.h>

class BackgoundLoadingThreadProc :
	public MeThreadProcedure
{
public:
	typedef void (*funcThreadProc)();
public:
	BackgoundLoadingThreadProc();
	BackgoundLoadingThreadProc( funcThreadProc pf );
	virtual ~BackgoundLoadingThreadProc();

	virtual void Destroy();

	virtual void ThreadProcedure();

	// tell the procedure to complete
	virtual void WaitForComplete();

	// awake the procedure
	virtual void Signal(){}

	// post process the processed request
	virtual void MainThreadProcess(){}

	void SetThreadProcCallBack( funcThreadProc pf ){
		m_pfThreadProc = pf;
	}

protected:
	funcThreadProc m_pfThreadProc;
};