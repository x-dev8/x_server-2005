#include "animtimeline.h"
#include "Me3d/Model/mexconfig.h"
#include "ErrorLog.h"
#include "FuncPerformanceLog.h"
#include <assert.h>

//
AnimTimeLine::AnimTimeLine()
{
	guardfunc;
	Reset();
	unguard;
}
void AnimTimeLine::Reset()
{
	guardfunc;
	m_dwStartTime = 0;
	m_nStartFrameID = 0;
	m_nEndFrameID = 0;
	m_nHitPoint = -1;
	m_bHitPointUsed = FALSE;
	m_nOneLoopTime = 0;

	m_bLoopPlaying = FALSE;
	m_bFastPlaying = FALSE;

	//m_fBlendFactor = 0.0f;
	unguard;
}

BOOL AnimTimeLine::HasHitPoint()
{
	guardfunc;
	return m_nHitPoint != -1;
	unguard;
}

void AnimTimeLine::HitPointUnused()
{
	guardfunc;
	m_bHitPointUsed = FALSE;
	unguard;
}
BOOL AnimTimeLine::TryHitPoint( DWORD dwTime )
{
	guardfunc;
	if( m_nHitPoint == -1 )
		return FALSE;
	if( m_bHitPointUsed )
		return FALSE;
	int nFrame = GetFrameID( dwTime );
	int nLooptime = GetNumLooped( dwTime );
	if( nFrame >= m_nHitPoint || nLooptime > 0 )
	{
		m_bHitPointUsed = TRUE;
		return TRUE;
	}
	return FALSE;
	unguard;
}

DWORD AnimTimeLine::FastPlay( DWORD dwTime, float fSpeedX )
{
	guardfunc;
	if( !m_bFastPlaying )
	{
		m_bFastPlaying = TRUE;
		if( dwTime > m_dwStartTime )
		{
			DWORD dwPassed = dwTime - m_dwStartTime;
			float fPercent = (float)dwPassed/m_nOneLoopTime;

			if( fSpeedX > 0 )
				m_nOneLoopTime = m_nOneLoopTime/fSpeedX;

			if( m_nOneLoopTime < 1 )
				m_nOneLoopTime = 1;

			m_dwStartTime = dwTime - m_nOneLoopTime*fPercent;

			if( m_dwStartTime > dwTime )
				m_dwStartTime = dwTime;

			fPercent = (dwPassed%m_nOneLoopTime)/m_nOneLoopTime;
			return ( 1 - fPercent )*m_nOneLoopTime;
		}
		else
		{
			if( fSpeedX > 0 )
				m_nOneLoopTime = m_nOneLoopTime/fSpeedX;

			if( m_nOneLoopTime < 1 )
				m_nOneLoopTime = 1;

			return 0;
		}
	}
	return 0;
	unguard;
}

float AnimTimeLine::GetCurPlayPercent( DWORD dwTime )
{
	guardfunc;
	if( m_nOneLoopTime == 0 )
		return 255.0f;

	if( dwTime < m_dwStartTime )

		return 0;
	DWORD dwPassed = dwTime-m_dwStartTime;
	float fPercent = (float)dwPassed/m_nOneLoopTime;
	return fPercent;
	unguard;
}

float AnimTimeLine::GetLoopPlayPercent( DWORD dwTime )
{
	guardfunc;
	if( m_nOneLoopTime == 0 )
		return 255.0f;

	if( dwTime < m_dwStartTime )
		return 0;

	DWORD dwPassed = dwTime-m_dwStartTime;
	DWORD dwOffset = (dwPassed%m_nOneLoopTime);
	float fPercent = (float)dwOffset/m_nOneLoopTime;
	if( fPercent > 1 )
	{
		fPercent = 1.0f;
	}
	return fPercent;
	unguard;
}

void AnimTimeLine::Play( DWORD dwStartTime,
							 int nStartFrameID, 
							 int nEndFrameID, 
							 int nHitPoint,
							 DWORD dwOneLoopTime )
{
	guardfunc;
	m_dwStartTime = dwStartTime;
	m_nStartFrameID = nStartFrameID;
	m_nEndFrameID = nEndFrameID;
	m_nHitPoint = nHitPoint;
	m_nOneLoopTime = dwOneLoopTime;
	if( m_nOneLoopTime == 0 )
	{
		assert( false );
	}

	// Çå³ý¹¥»÷µã
	HitPointUnused();
	unguard;
}
int	AnimTimeLine::GetNumLooped( DWORD dwTime )
{
	guardfunc;
	DWORD dwPassed = dwTime-m_dwStartTime;
	return dwPassed/(m_nOneLoopTime?m_nOneLoopTime:1);
	unguard;
}
int	AnimTimeLine::GetFrameID( DWORD dwTime )
{
	guardfunc;
	if( m_nOneLoopTime == 0 )
		return 0;
	DWORD dwPassed = dwTime-m_dwStartTime;
	DWORD dwOffset = (dwPassed%m_nOneLoopTime);
	float t = ((float)dwOffset)/m_nOneLoopTime;
	return m_nStartFrameID+t*(m_nEndFrameID-m_nStartFrameID);
	unguard;
}

int AnimTimeLine::GetOneLoopTime()
{
	guardfunc;
	return m_nOneLoopTime;
	unguard;
}

int AnimTimeLine::GetStartTime()
{
	guardfunc;
	return m_dwStartTime;
	unguard;
}

void AnimTimeLine::SetOneLoopTime( DWORD dwTime )
{
	guardfunc;
	if( dwTime > 0 )
	{
		m_nOneLoopTime = dwTime;
	}
	unguard;
}

void AnimTimeLine::SetLoopPlay()
{
	guardfunc;
	m_bLoopPlaying = TRUE;
	unguard;
}

BOOL AnimTimeLine::IsLoopPlaying()
{
	guardfunc;
	return m_bLoopPlaying;
	unguard;
}

int AnimTimeLine::GetStartFrameID()
{
	guardfunc;
	return m_nStartFrameID;
	unguard;
}

int AnimTimeLine::GetEndFrameID()
{
	guardfunc;
	return m_nEndFrameID;
	unguard;
}