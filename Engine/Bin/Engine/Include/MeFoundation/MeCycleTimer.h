#pragma once
#include "MeFoundation/MeClockTimer.h"

/**
* @brief 周期性计时器。可以设置为任意周期，
		 比如时，日，周等。模板参数单位为毫秒。
*/
template< MeTimeValue kCycle, class Timer = MeClockTimer >
class MEFOUNDATION_ENTRY MeCycleTimer : public Timer
{
// typedefs.
public:
	typedef MeCycleTimer<kCycle,Timer> ClassType;

// Construction.
public:
	/// Constructor.
	MeCycleTimer(){
		m_fRatio = 1.f;
	}
	
	/// Destructor.
	virtual ~MeCycleTimer(){}

	/// Copy constructor.
	MeCycleTimer( const ClassType& kClass ){}

// Overload operator.
public:
	/// Assignment operator.
	const MeCycleTimer& operator=( const ClassType& kClass ){ return *this; }

// Override.
public:
	/// 当超过周期时，复位。
	virtual void UpdateElapsedTime(){
		Timer::UpdateElapsedTime();
		m_kElapsed = GetElapsed() % kCycle;
	}

	/// 添加缩放。
	virtual MeTimeValue GetElapsed() const{
		return Timer::GetElapsed() * GetTimeRatio();
	}

// Methods.
public:
	/// 设置/获得时间缩放比例。
	float GetTimeRatio() const { return m_fRatio; }
	void SetTimeRatio( float fRatio ){ m_fRatio = fRatio; }

// Members.
protected:
	/// 缩放比。
	float m_fRatio;
};

// 时
typedef MeCycleTimer<3600000, MeClockTimer> MeHourTimer;

// 日
typedef MeCycleTimer<3600000 * 24, MeClockTimer> MeDayTimer;