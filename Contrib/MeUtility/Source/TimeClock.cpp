#include "TimeClock.h"
#include "FuncPerformanceLog.h"

TimeClock::TimeClock(void)
{
	guardfunc
	m_dwTime = 0;
	m_iTimeFactor = 4; //define 30��
	m_iUpdateInterval = 1000;
	m_dwLastUpdate = 0;
	m_dwCaluRest = 0;
	unguard;
}

TimeClock::~TimeClock(void)
{
	guardfunc
	unguard;

}

void TimeClock::SetCurrentTime( DWORD dwTime )
{
	guardfunc
	m_dwTime = dwTime;
	m_dwLastUpdate = HQ_TimeGetTime();
	m_dwCaluRest = 0;
	unguard;
}

void TimeClock:: Update( void )
{
	guardfunc
	DWORD dwTick = ::HQ_TimeGetTime();

	//if( dwTick < m_dwLastUpdate + m_iUpdateInterval )
	//	return;	
	DWORD dwTime = dwTick - m_dwLastUpdate;	
	dwTime *= m_iTimeFactor;

	//�����ϴε�����
	dwTime += m_dwCaluRest;
	dwTime /= 1000;	

	//��������
	m_dwCaluRest = dwTime % 1000;
	//���ʱ���ۼƲ���
	if( dwTime <= 0 )
		return;
	m_dwLastUpdate = dwTick;

	m_dwTime += dwTime;
	while( m_dwTime >= const_iFullTimeCircle )
		m_dwTime -= const_iFullTimeCircle;
	unguard;
}
