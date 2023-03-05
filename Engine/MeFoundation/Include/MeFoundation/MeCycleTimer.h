#pragma once
#include "MeFoundation/MeClockTimer.h"

/**
* @brief �����Լ�ʱ������������Ϊ�������ڣ�
		 ����ʱ���գ��ܵȡ�ģ�������λΪ���롣
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
	/// ����������ʱ����λ��
	virtual void UpdateElapsedTime(){
		Timer::UpdateElapsedTime();
		m_kElapsed = GetElapsed() % kCycle;
	}

	/// ������š�
	virtual MeTimeValue GetElapsed() const{
		return Timer::GetElapsed() * GetTimeRatio();
	}

// Methods.
public:
	/// ����/���ʱ�����ű�����
	float GetTimeRatio() const { return m_fRatio; }
	void SetTimeRatio( float fRatio ){ m_fRatio = fRatio; }

// Members.
protected:
	/// ���űȡ�
	float m_fRatio;
};

// ʱ
typedef MeCycleTimer<3600000, MeClockTimer> MeHourTimer;

// ��
typedef MeCycleTimer<3600000 * 24, MeClockTimer> MeDayTimer;