#pragma once

#include "logmgr.h"
#include "Singleton.h"
#define INFO_LOG "Info.log"

/**
* @brief Log abstract interface class.
*/
class MEFOUNDATION_ENTRY IMeLog
{
// Construction
public:
	/// Constructor.
	IMeLog(){}

	/// Destructor.
	virtual ~IMeLog(){}

// Method.
public:
	/// Print information with the specified format.
	virtual void Print( const char* format, ... ) = 0;

	/// Print information with the specified format.
	virtual void Print( const std::string& message ) = 0;
};

/**
* @brief Log to file
*/
class MEFOUNDATION_ENTRY MeLog : public IMeLog, public Singleton< MeLog >
{
// Override.
public:
	/// Print information with the specified format.
	virtual void Print( const char* format, ... )
	{
		return;
		va_list args;
		va_start( args, format );
		//log4cpp::Category::getInstance( INFO_LOG ).logva( LOG_PRIORITY_INFO, format, args );
		va_end( args );
	}

	/// Print information with the specified format.
	virtual void Print( const std::string& message )
	{
		return;
		//Log4cppLogger::Instance().Print( INFO_LOG, LOG_PRIORITY_INFO, message );
	}
// Construction.
private:
	friend class Singleton< MeLog >;

	/// Constructor
	MeLog(){}

	/// Destructor	
	~MeLog(){}

	/// disable copy ctor
	MeLog( const MeLog& ){}

// Overload operator.
private:
	/// disable assignment operator
	const MeLog& operator= ( const MeLog& ){ return *this; }
};

/** 
* @brief Log to output window
*/
class MEFOUNDATION_ENTRY MeOutputLog : public IMeLog, public Singleton< MeOutputLog >
{
// Override.
public:
	/// Print information with the specified format.
	virtual void Print( const char* format, ... )
	{
		va_list args;
		va_start( args, format );
		char szOutput[1024] = {0};
		_vsnprintf( szOutput, 1024, format, args );
		MeOutputDebugStringA( szOutput );
		va_end( args );
	}

	/// Print information with the specified format.
	virtual void Print( const std::string& message )
	{
		MeOutputDebugStringA( message.c_str() );
	}

// Construction.
private:
	friend class Singleton< MeOutputLog >;

	/// Constructor.
	MeOutputLog(){}
	
	/// Destructor.
	~MeOutputLog(){}

// Overload operator.
private:
	/// disable copy ctor.
	MeOutputLog( const MeOutputLog& ){}

	/// disable assignment operator.
	const MeOutputLog& operator= ( const MeOutputLog& ){ return *this; }
};