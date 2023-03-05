#pragma once

#include "MeFoundation/MeRuntimeLibs.h"

enum EFreeProfileStatus
{
	FPS_Start,
	FPS_End
};

/**
* @brief Manage time for free profile.
*/
template< class Log, MeTimeValue LogLimit, class Timer = MeClockTimer >
class MeFreeProfileMan : public Singleton< MeFreeProfileMan< Log, LogLimit, Timer > >
{
// typedefs.
public:
	typedef MeFreeProfileMan<Log, LogLimit, Timer> ClassType;

// Construction.
public:
	/// Constructor.
	MeFreeProfileMan(){
		m_uiValidIndex = 0;
		m_kProfiles.reserve( ms_cnMaxLayerCnt );
		m_kProfiles.resize( ms_cnMaxLayerCnt );
	}
	
	/// Destructor.
	~MeFreeProfileMan(){ m_kProfiles.clear(); }

// Overload operator.
private:
	/// Disable copy constructor.
	MeFreeProfileMan( const MeFreeProfileMan& kClass ){}

	/// Disable assignment operator.
	const MeFreeProfileMan& operator=( const MeFreeProfileMan& kClass ){}

// Methods.
public:
	/// Start a profile, push to container.
	inline void StartAProfile( const char* pcName ){
		if( m_uiValidIndex < 0 || m_uiValidIndex >= ms_cnMaxLayerCnt )
			return;

		m_kProfiles[m_uiValidIndex++].StartWithName( pcName );
	}

	/// End the top profile of container, and pop it.
	inline void EndAProfile( const char* pcName ){
		if( m_uiValidIndex < 0 || m_uiValidIndex >= ms_cnMaxLayerCnt )
			return;
		
		if( pcName )
		{
			while( --m_uiValidIndex < ms_cnMaxLayerCnt &&
				_tcscmp( m_kProfiles[m_uiValidIndex].GetName(), pcName ) != 0 );
		}
		else
			-- m_uiValidIndex;	


		if( m_uiValidIndex >= ms_cnMaxLayerCnt )
			return;

		m_kProfiles[m_uiValidIndex].EndWithLog();
	}

// Members.
private:
	typedef std::vector< MeProfileEx< Log, LogLimit, Timer > > Profiles;
	typedef typename Profiles::iterator ProfilesIterator;

	/// Store each profiles.
	Profiles m_kProfiles;

	/// Current index.
	unsigned int m_uiValidIndex;

	/// Max layer count.
	static const int ms_cnMaxLayerCnt = 100;
};

/**
* @brief Profile any where.
*/
template< EFreeProfileStatus Status, class Log, MeTimeValue LogLimit, class Timer = MeClockTimer >
class MeFreeProfile
{
// Construction.
private:
	/// Disable constructor.
	MeFreeProfile(){}
	
	/// Disable destructor.
	~MeFreeProfile(){}

// Overload operator.
private:
	/// Disable copy constructor.
	MeFreeProfile( const MeFreeProfile& kClass ){}

	/// Disable assignment operator.
	const MeFreeProfile& operator=( const MeFreeProfile& kClass ){}
};

/**
* @brief Partial specialization for Start.
*/
template< class Log, MeTimeValue LogLimit, class Timer > 
class MeFreeProfile< FPS_Start, Log, LogLimit, Timer >
{
// Construction.
public:
	/// Constructor.
	MeFreeProfile( const char* pcName ){
		MeFreeProfileMan< Log, LogLimit, Timer >::Instance()->StartAProfile( pcName );
	}
	
	/// Destructor.
	~MeFreeProfile(){}
};

/**
* @brief Partial specialization for End.
*/
template< class Log, MeTimeValue LogLimit, class Timer > 
class MeFreeProfile< FPS_End, Log, LogLimit, Timer >
{
	// Construction.
public:
	/// Constructor.
	MeFreeProfile( const char* pcName ){
		MeFreeProfileMan< Log, LogLimit, Timer >::Instance()->EndAProfile( pcName );
	}

	/// Destructor.
	~MeFreeProfile(){}
};