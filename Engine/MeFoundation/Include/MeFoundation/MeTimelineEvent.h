#pragma once

#include "MeFoundation/MeRefObject.h"
#include "Me3d/Vector.h"

/**
* @brief ʱ�����¼����ࡣ
*/
class MEFOUNDATION_ENTRY MeTimelineEventBase : public MeRefObject
{
// Defines.
public:
	/// �¼���״̬��
	enum EEventStates
	{
		EES_Ready,		// δ��ʼ
		EES_Running,	// ������
		EES_Pause,		// ��ͣ��
		EES_End,		// ����
		EES_Count
	};

	/// ���Ϸ����¼�ʱ��
	enum { InvalidEventTime = 0xffffffff };

	/// ����Ϊ�Լ��Ļص��������塣
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

	/// �����¼�����һ���¼��������󣬸���ʱ�䣬��ʼ�����������ݡ�
	/// @return ���Կ�ʼ�������ڸ��¡�
	virtual bool UpdateEvent( const MeTimeValue& kTime ){

		if( kTime <= GetStartTime() )
		{
			SetEventState( EES_Ready );

			// ִ�лص���
			if( m_pfUpdateEventInReady )
			{ m_pfUpdateEventInReady( this ); }

			UpdateEventInReady( kTime );
			IsFirstInRunning( true );
			return false;
		}
		else if( kTime > GetEndTime() )
		{ 
			SetEventState( EES_End ); 

			// ִ�лص���
			if( m_pfUpdateEventInEnd )
			{ m_pfUpdateEventInEnd( this ); }

			UpdateEventInEnd( kTime );
		}
		else 
		{ 
			SetEventState( EES_Running ); 
			if( IsFirstInRunning() )
			{
				// ִ�лص���
				if( m_pfDoFirstInRunning )
				{ m_pfDoFirstInRunning( this ); }

				DoFirstInRunning( kTime );
				IsFirstInRunning( false );
			}

			// ִ�лص���
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
	/// �����׶εĸ��º�����
	virtual void UpdateEventInReady( const MeTimeValue& kTime ){}
	virtual void UpdateEventInRunning( const MeTimeValue& kTime ){}
	virtual void UpdateEventInEnd( const MeTimeValue& kTime ){}

	/// ��һ�ν���runningʱִ�еĺ�����
	virtual void DoFirstInRunning( const MeTimeValue& kTime ){}

// Methods.
public:
	/// �����¼�״̬��
	void SetEventState( MeTimelineEventBase::EEventStates eState ){ m_eEventState = eState; }

	/// ȡ�õ�ǰ�¼�״̬��
	EEventStates GetEventState() const { return m_eEventState; }

	/// ����/ȡ�ÿ�ʼʱ�䡣
	void SetStartTime( const MeTimeValue& kTime ) { m_kStartTime = kTime; }
	const MeTimeValue& GetStartTime() const { return m_kStartTime; }

	/// ȡ�ý���ʱ�䡣
	const MeTimeValue& GetEndTime() const { return m_kEndTime; }
	void SetEndTime( const MeTimeValue& val ){ m_kEndTime = val; }

	/// ���ûص�������	
	void SetResetEventWithDataCallbackFunc( DataCallback pfCallback ){ m_pfResetEventWithDataCallback = pfCallback; }
	void SetDoFirstInRunningCallbackFunc( DataCallback pfCallback ){ m_pfDoFirstInRunning = pfCallback; }
	void SetUpdateEventInReadyCallbackFunc( DataCallback pfCallback ){ m_pfUpdateEventInReady = pfCallback; }
	void SetUpdateEventInRunningCallbackFunc( DataCallback pfCallback ){ m_pfUpdateEventInRunning = pfCallback; }
	void SetUpdateEventInEndCallbackFunc( DataCallback pfCallback ){ m_pfUpdateEventInEnd = pfCallback; }

// Methods.
protected:
	/// ����/ȡ���Ƿ��ǵ�һ�ν���running״̬��
	void IsFirstInRunning( bool bFirst ) { m_bFirstInRunning = bFirst; }
	bool IsFirstInRunning() const { return m_bFirstInRunning; }

// Members.
protected:
	/// �����¼�ʱ�Ļص����������ڳ�ʼ�����������¼��ڵ�ʱ�����ı�����
	DataCallback m_pfResetEventWithDataCallback;

	/// �����׶εĻص��������塣
	DataCallback m_pfDoFirstInRunning;
	DataCallback m_pfUpdateEventInReady;
	DataCallback m_pfUpdateEventInRunning;
	DataCallback m_pfUpdateEventInEnd;

	/// ��ǰ�¼�״̬��
	EEventStates m_eEventState;	

	/** �¼��Ŀ�ʼʱ�䡣���ʱ�����÷�Χ��һ�죬�˱���
		��¼���Ǵӿ�ʼ֮ʱ��������ʱ�䡣��λ���롣
	*/	
	MeTimeValue m_kStartTime;

	/// ���ʱ�䡣
	MeTimeValue m_kEndTime;

	/// �Ƿ��һ�ν���running״̬��
	bool m_bFirstInRunning;

};