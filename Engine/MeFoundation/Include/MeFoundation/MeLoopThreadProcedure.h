#pragma once

#include "MeFoundation/MeFoundationPCH.h"
#include "MeFoundation/MeThread.h"
//////////////////////////////////////////////////////////////////////////
class MEFOUNDATION_ENTRY MeLoopThreadReq : public MeAllocatedObject<MeLoopThreadReq>
{
protected:
	MeLoopThreadReq() : m_nSerialNo(0),
		m_pMex(0), m_pMexCfg(0), m_nModelId(-1), m_bValid( true ), m_nLowestIntensity(0)
	{
		memset( m_szFileName, 0, sizeof( m_szFileName ) );
	}

public:
	virtual ~MeLoopThreadReq(){}

	virtual void Destroy() = 0;

	virtual void Process() = 0;
	virtual bool ProcessInThread( bool bFailed = false ) = 0;
	virtual bool IsValid() const { return m_bValid; }
	virtual void SetValid( bool bValid ){ m_bValid = bValid; }

public:
	int		m_nObjectType;
	int		m_nSerialNo;
	char	m_szFileName[MAX_PATH];
	class IMex* m_pMex;
	class MexCfg* m_pMexCfg;
	int		m_nModelId;
	// 当前req是否有效。
	bool	m_bValid;
	int m_nLowestIntensity;

};
//////////////////////////////////////////////////////////////////////////
class MEFOUNDATION_ENTRY MeLoopThreadProcedure :
	public MeThreadProcedure
{
public:
	MeLoopThreadProcedure();
	virtual ~MeLoopThreadProcedure();

	virtual void Destroy();

	// thread procedure function
	virtual void ThreadProcedure();

	// tell the procedure to complete
	virtual void WaitForComplete();

	// awake the procedure
	virtual void Signal();

	virtual void Pause();

	virtual void Resume();

	virtual bool IsPause();

	// add request
	virtual void PostMexLoadingReq( MeLoopThreadReq* pReq );

	// set the main process speed
	void SetMainProcessSpeed( int nSpeed ){
		m_nSpeed = nSpeed;
	}

	// clear all requests
	virtual void ClearLoopList();

protected:
	virtual void PostMexLoadingAck( MeLoopThreadReq* pReq );

	virtual bool LoadMexFromReq2( MeLoopThreadReq* pReq ) = 0;

	virtual void ClearAckList() = 0;

	virtual void ClearReqCacheList();

	virtual void ClearReqList();

protected:
	// main process speed
	int m_nSpeed;

	CRITICAL_SECTION m_MexLoadingCS;

	typedef std::list<MeLoopThreadReq*> Mex2LoadReqs;
	typedef Mex2LoadReqs::iterator Mex2LoadReqsIter;
	Mex2LoadReqs m_MexLoadingReqsCache;
	Mex2LoadReqs m_MexLoadingReqs;
	Mex2LoadReqs m_MexLoadingAcks;

	// store string list
	typedef std::map< std::string, bool > MexBackListStrings;
	MexBackListStrings m_MexBackListString;

	// store integer list
	typedef std::map< int, bool > MexBackListInts;
	MexBackListInts m_MexBackListInt;

	// event handle
	HANDLE m_hMexLoadingEvent;

	bool m_bMexLoadingThreadPaused;
	bool m_bMexLaodingThreadWillPause;
	bool m_bMexLoadingThreadWillDestroy;
	bool m_bMexLoadingThreadTerminated;
};