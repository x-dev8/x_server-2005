#pragma once
#include "MeFoundation/MeTimelineEvent.h"

/**
* @brief 时间轴类，用给定的速率进行以时间驱动的事件触发机制。
* @template Timer: 定制的计时器。
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
	/// 添加事件。
	void PushEvent( MeTimelineEventBase* pEvent );

	/// 按时间排序所有事件。
	void SortEventsByTime();

	/// 清除所有事件。
	void ClearAllEvents();

	/// 更新时间。
	void UpdateTimeline();

	/// 渲染时间轴事件。
	void RenderTimeline(const Vector &playerPos);

	/// 获得计时器。
	const Timer& GetTimer() const{ return m_kTimer; }
	Timer* GetTimer(){ return &m_kTimer; }

	/// 获得事件容器。
	const TimelineEvents& GetEvents() const { return m_akEvents; }
	TimelineEvents& GetEvents() { return m_akEvents; }

	/// 开始计时，并允许传入一个起始偏移时间。
	void StartTime( const MeTimeValue& kTimePassed );

// Static Methods.
protected:
	static bool EventsSortAlgorism( MeTimelineEventBase* pEvent1, MeTimelineEventBase* pEvent2 )
	{
		return pEvent1->GetStartTime() < pEvent2->GetStartTime();
	}

// Members.
protected:
	/// 计时器。
	Timer m_kTimer;

	/// 事件容器。排列顺序是启动时间。	
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

	// 更新计时器。必须第一时间完成。
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