#pragma once
#include <MeFoundation/MeTimelineShadeEvent.h>

/**
* @brief 晴天转阴天
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

	/// 第一次进入running状态，更新光照值。
	virtual void DoFirstInRunning( const MeTimeValue& kTime );

	/// 从无到有的更新。
	virtual void UpdateBeginToFull( const MeTimeValue& kTime );

	/// 完全变化时的更新。
	virtual void UpdateInFull( const MeTimeValue& kTime );

	/// 从有到无的更新。
	virtual void UpdateFullToEnd( const MeTimeValue& kTime );

// Methods.
public:
	/// 原始环境光操作。
	const D3DXCOLOR& GetOriginalAmbient() const { return m_kOriginalAmbient; }
	void SetOriginalAmbient(const D3DXCOLOR& val) { m_kOriginalAmbient = val; }

	/// 原始漫射光操作。
	const D3DXCOLOR& GetOriginalDiffuse() const { return m_kOriginalDiffuse; }
	void SetOriginalDiffuse(const D3DXCOLOR& val) { m_kOriginalDiffuse = val; }

	/// 完全变化后的环境光操作。
	const D3DXCOLOR& GetDestinationAmbient() const { return m_kDestinationAmbient; }
	void SetDestinationAmbient(const D3DXCOLOR& val) { m_kDestinationAmbient = val; }

	/// 完全变化后的漫射光操作。
	const D3DXCOLOR& GetDestinationDiffuse() const { return m_kDestinationDiffuse; }
	void SetDestinationDiffuse(const D3DXCOLOR& val) { m_kDestinationDiffuse = val; }

	/// 当前环境光操作。
	const D3DXCOLOR& GetCurrentAmbient() const { return m_kCurrentAmbient; }
	void SetCurrentAmbient(const D3DXCOLOR& val) { m_kCurrentAmbient = val; }

	/// 当前漫射光操作。
	const D3DXCOLOR& GetCurrentDiffuse() const { return m_kCurrentDiffuse; }
	void SetCurrentDiffuse(const D3DXCOLOR& val) { m_kCurrentDiffuse = val; }

// Methods.
protected:

// Members.
protected:
	/// 原始环境光。
	D3DXCOLOR m_kOriginalAmbient;

	/// 原始漫射光。
	D3DXCOLOR m_kOriginalDiffuse;

	/// 完全变化后的环境光。
	D3DXCOLOR m_kDestinationAmbient;

	/// 完全变化后的漫射光。
	D3DXCOLOR m_kDestinationDiffuse;

	/// 当前环境光。
	D3DXCOLOR m_kCurrentAmbient;

	/// 当前漫射光。
	D3DXCOLOR m_kCurrentDiffuse;
};
