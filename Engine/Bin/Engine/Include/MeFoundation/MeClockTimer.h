#pragma once

/** 
* use _time64 to get time, with low precise.
* We do not use virtual function for performance 
* reason
*/
#include <Windows.h>
#include <MMSystem.h>
class MEFOUNDATION_ENTRY MeClockTimer : public MeClockTimerAlloc
{
// Construction.
public:
	/// Constructor.
	MeClockTimer() : m_kStart( 0 ), m_kElapsed( 0 ){}

	/// Copy constructor.
	MeClockTimer( const MeClockTimer& kTime ){
		m_kStart = kTime.m_kStart;
		m_kElapsed = kTime.m_kElapsed;
	}

	/// Destructor.
	virtual ~MeClockTimer(){}

// Overload operator.
public:
	/// Assignment operator.
	const MeClockTimer& operator= ( const MeClockTimer& kTime ){
		m_kStart = kTime.m_kStart;
		m_kElapsed = kTime.m_kElapsed;
		return *this;
	}

// Methods.
public:
	/// Is started.
	inline bool IsStarted() const { return m_kStart != 0; }

	/// Start time.
	inline void Start( const MeTimeValue& kTimePassed = 0 ){
		m_kStart = timeGetTime() - kTimePassed;
	}

	/// End time.
	inline void End(){
		m_kElapsed = timeGetTime();
		m_kElapsed -= m_kStart;
		m_kStart = 0;
	}

// Virtual Methods.
public:
	/// Update elapsed time per frame.
	virtual void UpdateElapsedTime(){
		m_kElapsed = timeGetTime();
		m_kElapsed -= m_kStart;
	}

	/// Get elapsed time.
	virtual MeTimeValue GetElapsed() const{
		return m_kElapsed;
	}

// Members.
protected:
	/// To store start time.
	MeTimeValue m_kStart;

	/// To store elapsed time.
	MeTimeValue m_kElapsed;

};