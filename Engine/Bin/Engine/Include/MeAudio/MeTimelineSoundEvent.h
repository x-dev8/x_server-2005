#pragma once
#include <MeFoundation/MeFoundationPCH.h>
#include <MeFoundation/MeTimelineShadeEvent.h>

/**
* @brief 播放声音事件。一个时间点触发后，播放一个声音。
		 起始声音大小为0，目标声音大小为当前最大声音值。
*/
class MEFOUNDATION_ENTRY MeTimelineSoundEvent : public MeTimelineShadeEvent
{
// Construction.
public:
	/// Constructor.
	MeTimelineSoundEvent(){
		m_nSoundIndex = -1;
		m_bLoop = false;
	}
	
	/// Destructor.
	virtual ~MeTimelineSoundEvent(){}

	/// Copy constructor.
	MeTimelineSoundEvent( const MeTimelineSoundEvent& kClass ){}

// Overload operator.
public:
	/// Assignment operator.
	const MeTimelineSoundEvent& operator=( const MeTimelineSoundEvent& kClass ){ return *this; }

	/// Reset event.
	virtual void ResetEvent();

// Override.
public:
	/// Destroy.
	virtual void DestroyEvent(){}

// Override.
protected:
	/// 从无到有的更新。
	virtual void UpdateBeginToFull( const MeTimeValue& kTime );

	/// 完全变化时的更新。
	virtual void UpdateInFull( const MeTimeValue& kTime );

	/// 从有到无的更新。
	virtual void UpdateFullToEnd( const MeTimeValue& kTime );

	/// Update event.
	virtual void DoFirstInRunning( const MeTimeValue& kTime );
	virtual void UpdateEventInEnd( const MeTimeValue& kTime );

// Methods.
public:
	/// Set sound filename.
	void SetSoundFilename( const std::string& strFilename ){ m_strSoundFilename = strFilename; }

	/// Set loop config.
	void SetLoop( bool bLoop ){ m_bLoop = bLoop; }

// Members.
protected:
	/// Sound full path filename.
	std::string m_strSoundFilename;

	/// Is loop.
	bool m_bLoop;

	/// Sound index.
	int m_nSoundIndex;
};