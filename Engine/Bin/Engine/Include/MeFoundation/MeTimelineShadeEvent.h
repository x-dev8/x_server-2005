#pragma once
#include <MeFoundation/MeTimelineEvent.h>

/**
* @brief ����ת����
*/
class MEFOUNDATION_ENTRY MeTimelineShadeEvent : public MeTimelineEventBase
{
// Defines.
public:
	/// ������¼�����
	enum EShadeEventState
	{
		ESES_Ready,			// δ��ʼ
		ESES_BeginToFull,	// ��ʼ����ȫ�仯
		ESES_Full,			// ��ȫ�仯
		ESES_FullToEnd,		// ��ȫ�仯�������仯
		ESES_End,			// ����
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
	/// �����¼�������ʱ������Ϊ���ұա�
	virtual void UpdateEventInRunning( const MeTimeValue& kTime ){
		// ��ʼ�ˣ����һ�δ�仯��ȫ��
		if( kTime <= ( m_kToFull + FLOAT_TOLERANCE ) )
		{ UpdateBeginToFull( kTime ); }
		// �仯��ȫ�׶εı��֡�
		else if( kTime > ( m_kToFull + FLOAT_TOLERANCE ) && kTime <= ( m_kToEnd + FLOAT_TOLERANCE ) )
		{ UpdateInFull( kTime ); }
		// �仯��ȫ�׶ε������׶εĹ��ɡ�
		else if( kTime > ( m_kToEnd + FLOAT_TOLERANCE ) && kTime <= ( GetEndTime() + FLOAT_TOLERANCE ) )
		{ UpdateFullToEnd( kTime ); }		
	}

	/// ���޵��еĸ��¡�
	virtual void UpdateBeginToFull( const MeTimeValue& kTime ) = 0;

	/// ��ȫ�仯ʱ�ĸ��¡�
	virtual void UpdateInFull( const MeTimeValue& kTime ) = 0;

	/// ���е��޵ĸ��¡�
	virtual void UpdateFullToEnd( const MeTimeValue& kTime ) = 0;

// Methods.
public:
	/// �޵��н���ʱ�������
	const MeTimeValue& GetToFull() const { return m_kToFull;}
	void SetToFull( const MeTimeValue& val ) { m_kToFull = val; }

	/// �е��޽���ʱ�������
	const MeTimeValue& GetToEnd() const { return m_kToEnd; }
	void SetToEnd( const MeTimeValue& val ) { m_kToEnd = val; }

// Methods.
protected:
	/// ��¼���������õ��ĳ������㣬��ʡЧ�ʡ�
	void UpdateValueForPerformance(){
		m_f1_Divide_ToFull_Minus_Start = 1.f / ( float )( GetToFull() - GetStartTime() );
		m_f1_Divide_End_Minus_ToEnd = 1.f / ( float )( GetEndTime() - GetToEnd() );
	}

	/// ��þ����õ�������������������
	float Get1_Divide_ToFull_Minus_Start() const { return m_f1_Divide_ToFull_Minus_Start; }
	float Get1_Divide_End_Minus_ToEnd() const { return m_f1_Divide_End_Minus_ToEnd; }

// Members.
protected:
	/// ���޵��еĽ���ʱ�䡣
	MeTimeValue m_kToFull;

	/// ���е��޵Ľ���ʱ�䡣
	MeTimeValue m_kToEnd;

	/// 1 / ( ToFull - Start )��
	float m_f1_Divide_ToFull_Minus_Start;

	/// 1 / ( End - ToEnd )��
	float m_f1_Divide_End_Minus_ToEnd;
};
