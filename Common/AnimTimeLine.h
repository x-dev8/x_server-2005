#ifndef _animtimeline_h
#define _animtimeline_h

#include "MeRTLibs.h"
class AnimTimeLine
{
public:
	struct SKey
	{
		int		nType;
		DWORD	dwTime;
	};

public:
	AnimTimeLine();
	void	Reset();

	BOOL	HasHitPoint();
	BOOL	TryHitPoint( DWORD dwTime );
	void	HitPointUnused();
	void	Play(	DWORD dwStartTime,
					int nStartFrameID, 
					int nEndFrameID, 
					int nHitPoint,
					DWORD dwOneLoopTime );

	// 加速，返回播完还要多少时间
	DWORD	FastPlay( DWORD dwTime, float fSpeedX );

	int		GetNumLooped( DWORD dwTime );
	int		GetFrameID( DWORD dwTime );
	//void	SetBlendFactor( float f ){ m_fBlendFactor = f; }
	//float	GetBlendFactor(){ return m_fBlendFactor; }
	int		GetOneLoopTime();
	int		GetStartTime();

	void	SetOneLoopTime( DWORD dwTime );

	int		GetStartFrameID();
	int		GetEndFrameID();

	float	GetCurPlayPercent( DWORD dwTime );
	float	GetLoopPlayPercent( DWORD dwTime );

	void	SetLoopPlay();
	BOOL	IsLoopPlaying();

protected:
	//float	m_fBlendFactor;
	//int		m_nBlendFrame0;
	//int		m_nBlendFrame1;

	int		m_dwStartTime;
	int		m_nStartFrameID;
	int		m_nEndFrameID;
	int		m_nHitPoint;
	BOOL	m_bHitPointUsed;
	int		m_nOneLoopTime;

	BOOL	m_bLoopPlaying;
	BOOL	m_bFastPlaying;
};
#endif