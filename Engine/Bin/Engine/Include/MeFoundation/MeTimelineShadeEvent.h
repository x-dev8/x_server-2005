#pragma once
#include <MeFoundation/MeTimelineEvent.h>

/**
* @brief 晴天转阴天
*/
class MEFOUNDATION_ENTRY MeTimelineShadeEvent : public MeTimelineEventBase
{
// Defines.
public:
	/// 渐变的事件属性
	enum EShadeEventState
	{
		ESES_Ready,			// 未开始
		ESES_BeginToFull,	// 开始到完全变化
		ESES_Full,			// 完全变化
		ESES_FullToEnd,		// 完全变化到结束变化
		ESES_End,			// 结束
		ESES_Count
	};

// Construction.
public:
	/// Constructor.
	MeTimelineShadeEvent(){
		m_kToFull = InvalidEventTime;
		m_kToEnd = InvalidEventTime;
	}

	/// Copy constructor.
	MeTimelineShadeEvent( const MeTimelineShadeEvent& kClass ){
		m_kToFull = kClass.m_kToFull;
		m_kToEnd = kClass.m_kToEnd;
	}

// Overload operator.
public:
	/// Destructor.
	virtual ~MeTimelineShadeEvent(){}

	/// Assignment operator.
	const MeTimelineShadeEvent& operator=( const MeTimelineShadeEvent& kClass ){
		m_kToFull = kClass.m_kToFull;
		m_kToEnd = kClass.m_kToEnd;
		return *this;
	}

// Override.
public:
	virtual void InitializeEvent(){ UpdateValueForPerformance(); }

	
// Override.
protected:
	/// 更新事件。所有时间区间为左开右闭。
	virtual void UpdateEventInRunning( const MeTimeValue& kTime ){
		// 开始了，并且还未变化完全。
		if( kTime <= ( m_kToFull + FLOAT_TOLERANCE ) )
		{ UpdateBeginToFull( kTime ); }
		// 变化完全阶段的表现。
		else if( kTime > ( m_kToFull + FLOAT_TOLERANCE ) && kTime <= ( m_kToEnd + FLOAT_TOLERANCE ) )
		{ UpdateInFull( kTime ); }
		// 变化完全阶段到结束阶段的过渡。
		else if( kTime > ( m_kToEnd + FLOAT_TOLERANCE ) && kTime <= ( GetEndTime() + FLOAT_TOLERANCE ) )
		{ UpdateFullToEnd( kTime ); }		
	}

	/// 从无到有的更新。
	virtual void UpdateBeginToFull( const MeTimeValue& kTime ) = 0;

	/// 完全变化时的更新。
	virtual void UpdateInFull( const MeTimeValue& kTime ) = 0;

	/// 从有到无的更新。
	virtual void UpdateFullToEnd( const MeTimeValue& kTime ) = 0;

// Methods.
public:
	/// 无到有渐变时间操作。
	const MeTimeValue& GetToFull() const { return m_kToFull;}
	void SetToFull( const MeTimeValue& val ) { m_kToFull = val; }

	/// 有到无渐变时间操作。
	const MeTimeValue& GetToEnd() const { return m_kToEnd; }
	void SetToEnd( const MeTimeValue& val ) { m_kToEnd = val; }

// Methods.
protected:
	/// 记录两个经常用到的除法运算，节省效率。
	void UpdateValueForPerformance(){
		m_f1_Divide_ToFull_Minus_Start = 1.f / ( float )( GetToFull() - GetStartTime() );
		m_f1_Divide_End_Minus_ToEnd = 1.f / ( float )( GetEndTime() - GetToEnd() );
	}

	/// 获得经常用到的两个除法运算结果。
	float Get1_Divide_ToFull_Minus_Start() const { return m_f1_Divide_ToFull_Minus_Start; }
	float Get1_Divide_End_Minus_ToEnd() const { return m_f1_Divide_End_Minus_ToEnd; }

// Members.
protected:
	/// 从无到有的渐变时间。
	MeTimeValue m_kToFull;

	/// 从有到无的渐变时间。
	MeTimeValue m_kToEnd;

	/// 1 / ( ToFull - Start )。
	float m_f1_Divide_ToFull_Minus_Start;

	/// 1 / ( End - ToEnd )。
	float m_f1_Divide_End_Minus_ToEnd;
};
