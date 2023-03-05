#pragma once

#include "MeFoundation/MeProfile.h"
#include "MeFoundation/MeClockTimer.h"
#include "MeFoundation/MePerformanceTimer.h"
#include "MeFoundation/MeLog.h"

/**
* Profile type, the value is the limit 
* time( millisecond ) for profile.
*/
enum MeProfileType
{
	MPT_Common = 30
};

/**
* The class Log must implement these functions:
* 1> Instance().
* 2> Print( const char* , ... )
* 3> Print( const std::string& )
* when elapsed time touch the LogLimit, print a warning log.
* @template Log: Logger.
* @template LogLimit: Base line for profiling.
* @template Timer: Timer.
*/
template< class Log, MeTimeValue LogLimit, class Timer = MeClockTimer >
class MEFOUNDATION_ENTRY MeScopeProfile : public MeProfileEx< Log, LogLimit, Timer >
{
// Typedefs.
public:
	typedef MeScopeProfile<Log, LogLimit, Timer> ClassType;

// Construction.
public:
	/// Constructor.
	MeScopeProfile(){
		Start();
	}

	/// Constructor with name.
	MeScopeProfile( const char* pcName ){
		StartWithName( pcName );
	}

	/// Destructor.
	~MeScopeProfile(){
		EndWithLog();
	}

// Overload operator
public:
	/// Copy constructor
	MeScopeProfile( const MeScopeProfile& kProfile );

	/// Assignment operator.
	const MeScopeProfile& operator=( const MeScopeProfile& kProfile );
	
};

// Log to file.
typedef MeScopeProfile<MeLog, MPT_Common> MeProfileCommon;
/*
You could define your own type like this:
typedef MeScopeProfile<YourLog, MPT_Yourtype> MeProfileYour;
*/

// Log to output window.
typedef MeScopeProfile<MeOutputLog, MPT_Common> MeScopeProfileOutput;

