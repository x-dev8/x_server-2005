#pragma once

#include "MeFoundation/MeRefObject.h"
#include "Me3d/Vector.h"

/**
* @brief 时间轴事件基类。
*/
class MEFOUNDATION_ENTRY MeTimelineEventBase : public MeRefObject
{
// Defines.
public:
	/// 事件的状态。
	enum EEventStates
	{
		EES_Ready,		// 未开始
		EES_Running,	// 运行中
		EES_Pause,		// 暂停中
		EES_End,		// 结束
		EES_Count
	};

	/// 不合法的事件时间
	enum { InvalidEventTime = 0xffffffff };

	/// 参数为自己的回调函数定义。
	typedef void (*DataCallback)( MeTimelineEventBase* );

// Construction.
public:
	/// Constructor.
	MeTimelineEventBase(){
		m_eEventState = EES_Count;
		m_kStartTime = InvalidEventTime;
		m_kEndTime = InvalidEventTime;
		m_pfResetEventWithDataCallback = NULL;
		m_pfDoFirstInRunning = NULL;
		m_pfUpdateEventInReady = NULL;
		m_pfUpdateEventInRunning = NULL;
		m_pfUpdateEventInEnd = NULL;
		m_bFirstInRunning = true;
	}
	
	/// Copy constructor.
	MeTimelineEventBase( const MeTimelineEventBase& kClass ){}

// Overload operator.
public:
	/// Assignment operator.
	const MeTimelineEventBase& operator=( const MeTimelineEventBase& kClass ){ return *this; }

// Virtual Methods.
public:
	/// Destructor.
	virtual ~MeTimelineEventBase(){}	

	/// Initialize.
	virtual void InitializeEvent() = 0;

	/// Reset states.
	virtual void ResetEvent(){ 
		if( m_pfResetEventWithDataCallback )
		{ m_pfResetEventWithDataCallback( this ); }
	}

	/// Destroy.
	virtual void DestroyEvent() = 0;

	/// 更新事件。当一个事件被触发后，根据时间，开始更新里面内容。
	/// @return 可以开始并且正在更新。
	virtual bool UpdateEvent( const MeTimeValue& kTime ){

		if( kTime <= GetStartTime() )
		{
			SetEventState( EES_Ready );

			// 执行回调。
			if( m_pfUpdateEventInReady )
			{ m_pfUpdateEventInReady( this ); }

			UpdateEventInReady( kTime );
			IsFirstInRunning( true );
			return false;
		}
		else if( kTime > GetEndTime() )
		{ 
			SetEventState( EES_End ); 

			// 执行回调。
			if( m_pfUpdateEventInEnd )
			{ m_pfUpdateEventInEnd( this ); }

			UpdateEventInEnd( kTime );
		}
		else 
		{ 
			SetEventState( EES_Running ); 
			if( IsFirstInRunning() )
			{
				// 执行回调。
				if( m_pfDoFirstInRunning )
				{ m_pfDoFirstInRunning( this ); }

				DoFirstInRunning( kTime );
				IsFirstInRunning( false );
			}

			// 执行回调。
			if( m_pfUpdateEventInRunning )
			{ m_pfUpdateEventInRunning( this ); }

			UpdateEventInRunning( kTime );
		}
		return true;
	}

	/// Render.
	virtual void RenderEvent(const Vector &playerPos) {}

	/// Device Lost
	virtual void OnDeviceLost() {}

	/// Device Reset
	virtual void OnDeviceReset() {}

// Override.
protected:
	/// 三个阶段的更新函数。
	virtual void UpdateEventInReady( const MeTimeValue& kTime ){}
	virtual void UpdateEventInRunning( const MeTimeValue& kTime ){}
	virtual void UpdateEventInEnd( const MeTimeValue& kTime ){}

	/// 第一次进入running时执行的函数。
	virtual void DoFirstInRunning( const MeTimeValue& kTime ){}

// Methods.
public:
	/// 设置事件状态。
	void SetEventState( MeTimelineEventBase::EEventStates eState ){ m_eEventState = eState; }

	/// 取得当前事件状态。
	EEventStates GetEventState() const { return m_eEventState; }

	/// 设置/取得开始时间。
	void SetStartTime( const MeTimeValue& kTime ) { m_kStartTime = kTime; }
	const MeTimeValue& GetStartTime() const { return m_kStartTime; }

	/// 取得结束时间。
	const MeTimeValue& GetEndTime() const { return m_kEndTime; }
	void SetEndTime( const MeTimeValue& val ){ m_kEndTime = val; }

	/// 设置回调函数。	
	void SetResetEventWithDataCallbackFunc( DataCallback pfCallback ){ m_pfResetEventWithDataCallback = pfCallback; }
	void SetDoFirstInRunningCallbackFunc( DataCallback pfCallback ){ m_pfDoFirstInRunning = pfCallback; }
	void SetUpdateEventInReadyCallbackFunc( DataCallback pfCallback ){ m_pfUpdateEventInReady = pfCallback; }
	void SetUpdateEventInRunningCallbackFunc( DataCallback pfCallback ){ m_pfUpdateEventInRunning = pfCallback; }
	void SetUpdateEventInEndCallbackFunc( DataCallback pfCallback ){ m_pfUpdateEventInEnd = pfCallback; }

// Methods.
protected:
	/// 设置/取得是否是第一次进入running状态。
	void IsFirstInRunning( bool bFirst ) { m_bFirstInRunning = bFirst; }
	bool IsFirstInRunning() const { return m_bFirstInRunning; }

// Members.
protected:
	/// 重置事件时的回调函数。用于初始化各种类型事件在当时环境的变量。
	DataCallback m_pfResetEventWithDataCallback;

	/// 各个阶段的回调函数定义。
	DataCallback m_pfDoFirstInRunning;
	DataCallback m_pfUpdateEventInReady;
	DataCallback m_pfUpdateEventInRunning;
	DataCallback m_pfUpdateEventInEnd;

	/// 当前事件状态。
	EEventStates m_eEventState;	

	/** 事件的开始时间。这个时间作用范围是一天，此变量
		记录的是从开始之时到启动的时间。单位毫秒。
	*/	
	MeTimeValue m_kStartTime;

	/// 完成时间。
	MeTimeValue m_kEndTime;

	/// 是否第一次进入running状态。
	bool m_bFirstInRunning;

};