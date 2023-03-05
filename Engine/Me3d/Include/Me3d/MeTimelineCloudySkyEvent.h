#pragma once
#include <MeFoundation/MeTimelineShadeEvent.h>

/**
* @brief ����ת����
*/
class MEFOUNDATION_ENTRY MeTimelineCloudySkyEvent : public MeTimelineShadeEvent
{
// Construction.
public:
	/// Constructor.
	MeTimelineCloudySkyEvent(){
		m_kOriginalAmbient = D3DXCOLOR( 0, 0, 0, 0 );
		m_kOriginalDiffuse = D3DXCOLOR( 0, 0, 0, 0 );
		m_kDestinationAmbient = D3DXCOLOR( 0, 0, 0, 0 );
		m_kDestinationDiffuse = D3DXCOLOR( 0, 0, 0, 0 );
		m_kCurrentAmbient = D3DXCOLOR( 0, 0, 0, 0 );
		m_kCurrentDiffuse = D3DXCOLOR( 0, 0, 0, 0 );

	}

	/// Copy constructor.
	MeTimelineCloudySkyEvent( const MeTimelineCloudySkyEvent& kClass ){
		m_kOriginalAmbient = kClass.m_kOriginalAmbient;
		m_kOriginalDiffuse = kClass.m_kOriginalDiffuse;
		m_kDestinationAmbient = kClass.m_kDestinationAmbient;
		m_kDestinationDiffuse = kClass.m_kDestinationDiffuse;
		m_kCurrentAmbient = kClass.m_kCurrentAmbient;
		m_kCurrentDiffuse = kClass.m_kCurrentDiffuse;
	}

// Overload operator.
public:
	/// Assignment operator.
	const MeTimelineCloudySkyEvent& operator=( const MeTimelineCloudySkyEvent& kClass ){
		m_kOriginalAmbient = kClass.m_kOriginalAmbient;
		m_kOriginalDiffuse = kClass.m_kOriginalDiffuse;
		m_kDestinationAmbient = kClass.m_kDestinationAmbient;
		m_kDestinationDiffuse = kClass.m_kDestinationDiffuse;
		m_kCurrentAmbient = kClass.m_kCurrentAmbient;
		m_kCurrentDiffuse = kClass.m_kCurrentDiffuse;
		return *this;
	}

// Override.
public:
	/// Destructor.
	virtual ~MeTimelineCloudySkyEvent(){}

	/// Destroy.
	virtual void DestroyEvent() {}

	/// Render.
	virtual void RenderEvent() {}

	/// ��һ�ν���running״̬�����¹���ֵ��
	virtual void DoFirstInRunning( const MeTimeValue& kTime );

	/// ���޵��еĸ��¡�
	virtual void UpdateBeginToFull( const MeTimeValue& kTime );

	/// ��ȫ�仯ʱ�ĸ��¡�
	virtual void UpdateInFull( const MeTimeValue& kTime );

	/// ���е��޵ĸ��¡�
	virtual void UpdateFullToEnd( const MeTimeValue& kTime );

// Methods.
public:
	/// ԭʼ�����������
	const D3DXCOLOR& GetOriginalAmbient() const { return m_kOriginalAmbient; }
	void SetOriginalAmbient(const D3DXCOLOR& val) { m_kOriginalAmbient = val; }

	/// ԭʼ����������
	const D3DXCOLOR& GetOriginalDiffuse() const { return m_kOriginalDiffuse; }
	void SetOriginalDiffuse(const D3DXCOLOR& val) { m_kOriginalDiffuse = val; }

	/// ��ȫ�仯��Ļ����������
	const D3DXCOLOR& GetDestinationAmbient() const { return m_kDestinationAmbient; }
	void SetDestinationAmbient(const D3DXCOLOR& val) { m_kDestinationAmbient = val; }

	/// ��ȫ�仯�������������
	const D3DXCOLOR& GetDestinationDiffuse() const { return m_kDestinationDiffuse; }
	void SetDestinationDiffuse(const D3DXCOLOR& val) { m_kDestinationDiffuse = val; }

	/// ��ǰ�����������
	const D3DXCOLOR& GetCurrentAmbient() const { return m_kCurrentAmbient; }
	void SetCurrentAmbient(const D3DXCOLOR& val) { m_kCurrentAmbient = val; }

	/// ��ǰ����������
	const D3DXCOLOR& GetCurrentDiffuse() const { return m_kCurrentDiffuse; }
	void SetCurrentDiffuse(const D3DXCOLOR& val) { m_kCurrentDiffuse = val; }

// Methods.
protected:

// Members.
protected:
	/// ԭʼ�����⡣
	D3DXCOLOR m_kOriginalAmbient;

	/// ԭʼ����⡣
	D3DXCOLOR m_kOriginalDiffuse;

	/// ��ȫ�仯��Ļ����⡣
	D3DXCOLOR m_kDestinationAmbient;

	/// ��ȫ�仯�������⡣
	D3DXCOLOR m_kDestinationDiffuse;

	/// ��ǰ�����⡣
	D3DXCOLOR m_kCurrentAmbient;

	/// ��ǰ����⡣
	D3DXCOLOR m_kCurrentDiffuse;
};
