#pragma once

#include "MeFoundation/MeRuntimeLibs.h"
#include "MeFoundation/MeFoundationLibType.h"
#include "MeFoundation/MeFoundationBaseDefines.h"

/**
* A basic profiling class with a timer.
* @template T: specify a particular timer.
*/
template< class T >
class MEFOUNDATION_ENTRY MeProfile
{
// Typedefs.
public:
	typedef MeProfile<T> ClassType;

// Construction.
public:
	/// Constructor.
	MeProfile(){}

	/// Destructor.
	virtual ~MeProfile(){}

// Overload operator.
public:
	/// Copy constructor.
	MeProfile( const MeProfile& kProfile ){}

	/// Assignment operator.
	const MeProfile& operator=( const MeProfile& kProfile ){}

// Methods.
public:
	/// Start time.
	inline void Start();

	/// End time.
	inline void End();

	/// Get elapsed time.
	inline MeTimeValue GetElapsed() const;

// Members.
protected:
	/// Timer.
	T m_kTimer;
};
#include "MeFoundation/MeProfile.inl"

/**
* @brief Contains a string for profile.
*/
class MeProfileString
{
//Construction.
public:
	/// Constructor.
	MeProfileString(){}
	
	/// Destructor.
	virtual ~MeProfileString(){}

	/// Copy constructor.
	MeProfileString( const MeProfileString& kClass ){
		m_strName = kClass.m_strName;
	}

// Overload operator.
public:
	/// Assignment operator.
	const MeProfileString& operator=( const MeProfileString& kClass ){
		m_strName = kClass.m_strName;
		return *this;
	}

// Methods.
public:
	/// Get name.
	inline const char* GetName(){ return m_strName.c_str(); }

	/// Set name.
	inline void SetName( const char* pcName ){ m_strName = pcName; }

// Members.
protected:
	/// String.
	std::string m_strName;
};

/**
* @brief Profile with string.
*/
template< class Log, MeTimeValue LogLimit, class Timer >
class MeProfileEx : public MeProfile< Timer >, public MeProfileString
{

// Construction.
public:
	/// Constructor.
	MeProfileEx(){}
	
	/// Destructor.
	virtual ~MeProfileEx(){}


// Overload operator.
public:
	/// Copy constructor.
	MeProfileEx( const MeProfileEx& kClass ){}

	/// Assignment operator.
	const MeProfileEx& operator=( const MeProfileEx& kClass ){ return *this; }

// Methods.
public:
	/// Start time and set a string.
	inline void StartWithName( const char* pcName ){
		SetName( pcName );
		Start();
	}

	/// End time and log.
	inline void EndWithLog(){
		End();
		if( GetElapsed() >= LogLimit &&
			GetName() )
			Log::Instance()->Print( "Profile Warning: %s, %d\n", 
			GetName(), GetElapsed() );
	}
};