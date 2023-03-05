#pragma once

/** 
* Use QueryPerformanceFrequency to get time, with 
* best precision. We do not use virtual function 
* for performance reason.
*/
class MEFOUNDATION_ENTRY MePerformanceTimer : public MePerformanceTimerAlloc
{
// Construction.
public:
	/// Constructor.
	MePerformanceTimer() : m_kStart( 0 ), m_kElapsed( 0 ){
		LARGE_INTEGER qwTicksPerSec;
		QueryPerformanceFrequency( &qwTicksPerSec );
		m_kFrequency = qwTicksPerSec.QuadPart;
	}

	/// Copy constructor.
	MePerformanceTimer( const MePerformanceTimer& kTime ){		
		m_kStart = kTime.m_kStart;
		m_kElapsed = kTime.m_kElapsed;
	}

	/// Destructor.
	~MePerformanceTimer(){}

// Overload operator.
public:
	/// Assignment operator.
	const MePerformanceTimer& operator= ( const MePerformanceTimer& kTime ){
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
		LARGE_INTEGER qwTicksPerSec;
		QueryPerformanceCounter( &qwTicksPerSec );
		m_kStart = qwTicksPerSec.LowPart / m_kFrequency -  kTimePassed;
	}
	
	/// End time.
	inline void End(){
		LARGE_INTEGER qwTicksPerSec;
		QueryPerformanceCounter( &qwTicksPerSec );
		m_kElapsed = qwTicksPerSec.LowPart;
		m_kElapsed -= m_kStart;
		m_kElapsed /= m_kFrequency;
		m_kStart = 0;
	}

// Virtual Methods.
public:
	/// Update elapsed time per frame.
	virtual void UpdateElapsedTime(){
		LARGE_INTEGER qwTicksPerSec;
		QueryPerformanceCounter( &qwTicksPerSec );
		m_kElapsed = qwTicksPerSec.LowPart;
		m_kElapsed -= m_kStart;
		m_kElapsed /= m_kFrequency;
	}

	/// Get elapsed time.
	virtual MeTimeValue GetElapsed() const{
		return m_kElapsed;
	}

// Members.
protected:
	/// Counter frequency.
	MeTimeValue m_kFrequency;

	/// To store start time.
	MeTimeValue m_kStart;

	/// To store elapsed time.
	MeTimeValue m_kElapsed;
};