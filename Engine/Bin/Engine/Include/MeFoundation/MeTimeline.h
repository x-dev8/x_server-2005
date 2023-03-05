#pragma once
#include "MeFoundation/MeTimelineEvent.h"

/**
* @brief ʱ�����࣬�ø��������ʽ�����ʱ���������¼��������ơ�
* @template Timer: ���Ƶļ�ʱ����
*/
template< class Timer >
class MEFOUNDATION_ENTRY MeTimeline : public MeRefObject
{
// Defines.
public:
	typedef MeTimeline< Timer > ThisClass;
	typedef std::vector<MeTimelineEventBase*> TimelineEvents;
	typedef TimelineEvents::iterator TimelineEventsIterator;
	typedef TimelineEvents::const_iterator TimelineEventsConstIterator;

// Construction.
public:
	/// Constructor.
	MeTimeline(){}
	
	/// Destructor.
	~MeTimeline(){}

	/// Copy constructor.
	MeTimeline( const ThisClass& kClass ){
		m_akEvents = kClass.m_akEvents;
		m_kTimer = kClass.m_kTimer;
	}

// Overload operator.
public:
	/// Assignment operator.
	const MeTimeline& operator=( const ThisClass& kClass ){	
		m_akEvents = kClass.m_akEvents;
		m_kTimer = kClass.m_kTimer;
		return *this; 
	}

// Methods.
public:
	/// ����¼���
	void PushEvent( MeTimelineEventBase* pEvent );

	/// ��ʱ�����������¼���
	void SortEventsByTime();

	/// ��������¼���
	void ClearAllEvents();

	/// ����ʱ�䡣
	void UpdateTimeline();

	/// ��Ⱦʱ�����¼���
	void RenderTimeline(const Vector &playerPos);

	/// ��ü�ʱ����
	const Timer& GetTimer() const{ return m_kTimer; }
	Timer* GetTimer(){ return &m_kTimer; }

	/// ����¼�������
	const TimelineEvents& GetEvents() const { return m_akEvents; }
	TimelineEvents& GetEvents() { return m_akEvents; }

	/// ��ʼ��ʱ����������һ����ʼƫ��ʱ�䡣
	void StartTime( const MeTimeValue& kTimePassed );

// Static Methods.
protected:
	static bool EventsSortAlgorism( MeTimelineEventBase* pEvent1, MeTimelineEventBase* pEvent2 )
	{
		return pEvent1->GetStartTime() < pEvent2->GetStartTime();
	}

// Members.
protected:
	/// ��ʱ����
	Timer m_kTimer;

	/// �¼�����������˳��������ʱ�䡣	
	TimelineEvents m_akEvents;
};
//////////////////////////////////////////////////////////////////////////
template< class Timer >
void MeTimeline< Timer >::PushEvent( MeTimelineEventBase* pEvent )
{
	m_akEvents.push_back( pEvent );
}
//////////////////////////////////////////////////////////////////////////
template< class Timer >
void MeTimeline< Timer >::SortEventsByTime()
{
	std::sort( m_akEvents.begin(), m_akEvents.end(), EventsSortAlgorism );
}
//////////////////////////////////////////////////////////////////////////
template< class Timer >
void MeTimeline< Timer >::ClearAllEvents()
{
	TimelineEventsConstIterator kIter = m_akEvents.begin();	
	for( ; kIter != m_akEvents.end(); ++ kIter )
	{
		( *kIter )->DestroyEvent();
		MeDelete ( *kIter );
	}
	m_akEvents.clear();
}
//////////////////////////////////////////////////////////////////////////
template< class Timer >
void MeTimeline< Timer >::UpdateTimeline()
{
	if( !m_kTimer.IsStarted() )
	{ return; }

	// ���¼�ʱ���������һʱ����ɡ�
	m_kTimer.UpdateElapsedTime();

	if( m_akEvents.empty() )
		return;

	TimelineEventsConstIterator kIter = m_akEvents.begin();	
	for( ; kIter != m_akEvents.end(); ++ kIter )
	{
		( *kIter )->UpdateEvent( m_kTimer.GetElapsed() );			
	}
}
//////////////////////////////////////////////////////////////////////////
template< class Timer >
void MeTimeline< Timer >::RenderTimeline(const Vector &playerPos)
{
	if( !m_kTimer.IsStarted() )
	{ return; }

	if( m_akEvents.empty() )
		return;

	TimelineEventsConstIterator kIter = m_akEvents.begin();	
	for( ; kIter != m_akEvents.end(); ++ kIter )
	{
		( *kIter )->RenderEvent(playerPos);
	}
}
//////////////////////////////////////////////////////////////////////////
template< class Timer >
void MeTimeline< Timer >::StartTime( const MeTimeValue& kTimePassed )
{
	m_kTimer.Start( kTimePassed );
}
//////////////////////////////////////////////////////////////////////////