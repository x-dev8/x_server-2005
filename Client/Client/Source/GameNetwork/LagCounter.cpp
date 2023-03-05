#include "lagcounter.h"

#include "FuncPerformanceLog.h"

CLagCounter::CLagCounter(void)
{
	guardfunc;
	m_dwLag = 0;
	m_iStatus = STATUS_IDLE;
	m_dwLastCounterTime = 0;
	unguard;
}

CLagCounter::~CLagCounter(void)
{
	guardfunc;
	unguard;
}

BOOL CLagCounter::CanSendReq()
{
	guardfunc;
	DWORD dwTick = HQ_TimeGetTime();
	if( STATUS_IDLE == m_iStatus )
	{
		if( dwTick - m_dwLastCounterTime < const_iCounterInterval )
			return FALSE;
		m_iStatus = STATUS_READY;
		return TRUE;
	}
	else
	if( STATUS_READY == m_iStatus )
		return TRUE;
	return FALSE;
	unguard;
}

void CLagCounter::SendReq()
{
	guardfunc;
	m_iStatus = STATUS_WAITACK;
	m_dwSendReqTime = HQ_TimeGetTime();
	unguard;
}

//
void CLagCounter::RecvAck()
{
	guardfunc;
	if( STATUS_WAITACK != m_iStatus )
		return;
	DWORD dwLag;
	m_dwLastCounterTime = HQ_TimeGetTime();
	dwLag = HQ_TimeGetTime() - m_dwSendReqTime;
	dwLag /= 2;
	//¹ýÂËµôÒ»Ð©
	if( dwLag < 2000 )
	{
		m_dwLag = ( m_dwLag + dwLag )/2;
	}
	m_iStatus = STATUS_IDLE;
	unguard;
}

DWORD CLagCounter::GetLag()
{
	guardfunc;
	return m_dwLag;
	unguard;
}