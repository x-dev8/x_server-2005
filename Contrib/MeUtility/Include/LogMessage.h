#ifndef __LOGMESSAGE_H__
#define __LOGMESSAGE_H__

#include "LogFileObjectNameEx.h"

class LogMessage
{
public:
	LogMessage( void );
	~LogMessage( void );
public:
	//Common
	static void LogSystemError( const char* format, ... );
    static void LogSystemWarning( const char* format, ... );
	static void LogSystemInfo( const char* format, ... );

	static void LogLogicError( const char* format, ... );
	static void LogLogicInfo( const char* format, ... );
    static void LogLogicDebug( const char* format,... );

	static void LogCapabilityError( const char* format, ... );
    static void LogCapabilityWarning( const char* format, ... );
	static void LogCapabilityInfo( const char* format, ... );

	static void LogSqlError( const char* format, ... );
	static void LogSqlInfo( const char* format, ... );
    static void LogSqlCritical( const char* format, ... );
    static void LogSqlDebug( const char* format, ... );

	static void LogStatisticsError( const char* format, ... );
	static void LogStatisticsInfo( const char* format, ... );

	static void LogBillingError( const char* format, ... );
	static void LogBillingInfo( const char* format, ... );

	static void LogShoppingError( const char* format, ... );
	static void LogShoppingInfo( const char* format, ... );

	static void LogCheckCheatError( const char* format, ... );
	static void LogCheckCheatInfo( const char* format, ... );

	static void LogMailError( const char* format, ... );
	static void LogMailInfo( const char* format, ... );

	static void LogAuctionError( const char* format, ... );
	static void LogAuctionInfo( const char* format, ... );

	static void LogChatError( const char* format, ... );
	static void LogChatInfo( const char* format, ... );

	static void LogPKError(const char* format,...);
	static void LogPKInfo(const char* format,...);

	//GameServer
	static void LogPlayerError( const char* format, ... );
	static void LogPlayerInfo( const char* format, ... );
    static void LogPlayerDebug( const char* format, ... );

	static void LogScriptError( const char* format, ... );
	static void LogScriptInfo( const char* format, ... );
	
	// CenterServer
	static void LogPlatformError( const char* format, ... );
	static void LogPlatformInfo( const char* format, ... );
};
#endif   //__LOGMESSAGE_H__