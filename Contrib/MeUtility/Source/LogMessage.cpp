#include <stdarg.h>
#include <tchar.h>
#include <iostream>
#include "LogMessage.h"

using namespace std;

#define FORMAT_MESSAGE( format, buffer, size )	va_list args;\
	va_start( args, format );\
	_vstprintf_s( buffer, size, format, args );\
	va_end( args )

#define BUFFER_SIZE_LOG 1024 * 100

LogMessage::LogMessage( void )
{
}

LogMessage::~LogMessage( void )
{
}

//Common
void LogMessage::LogSystemError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
	FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogSystemWarning( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, buffer );
}

void LogMessage::LogSystemInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, buffer );
}

void LogMessage::LogLogicError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogLogicInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, buffer );
}

void LogMessage::LogLogicDebug( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_DEBUG, buffer );
}

void LogMessage::LogCapabilityError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( CAPABILITYOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogCapabilityWarning( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
    LOG_MESSAGE( CAPABILITYOBJECT, LOG_PRIORITY_WARNING, buffer );
}

void LogMessage::LogCapabilityInfo( const char* format, ... )
{
	static char buffer[BUFFER_SIZE_LOG];
	FORMAT_MESSAGE(format,buffer,sizeof(buffer));
	LOG_MESSAGE( CAPABILITYOBJECT, LOG_PRIORITY_INFO, buffer );
}

void LogMessage::LogSqlError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogSqlCritical( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
    LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_CRITICAL, buffer );
}

void LogMessage::LogSqlInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_INFO, buffer );
}

void LogMessage::LogSqlDebug( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
    LOG_MESSAGE( SQLOBJECT, LOG_PRIORITY_DEBUG, buffer );
}

void LogMessage::LogStatisticsError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( STATISTICSOBJECT, LOG_PRIORITY_ERROR, buffer );
}
void LogMessage::LogStatisticsInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( STATISTICSOBJECT, LOG_PRIORITY_INFO, buffer );
}

void LogMessage::LogBillingError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( BILLINGOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogBillingInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( BILLINGOBJECT, LOG_PRIORITY_INFO, buffer );
}

void LogMessage::LogShoppingError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( SHOPPINGOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogShoppingInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( SHOPPINGOBJECT, LOG_PRIORITY_INFO, buffer );
}

void LogMessage::LogCheckCheatError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( CHECKCHEATOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogCheckCheatInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( CHECKCHEATOBJECT, LOG_PRIORITY_INFO, buffer );
}

void LogMessage::LogMailError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( MAILOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogMailInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( MAILOBJECT, LOG_PRIORITY_INFO, buffer );
}

void LogMessage::LogAuctionError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogAuctionInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( AUCTIONOBJECT, LOG_PRIORITY_INFO, buffer );
}

void LogMessage::LogChatError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( CHATOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogChatInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( CHATOBJECT, LOG_PRIORITY_INFO, buffer );
}

void LogMessage::LogPKError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( PKOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogPKInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( PKOBJECT, LOG_PRIORITY_INFO, buffer );
}

//GameServer
void LogMessage::LogPlayerError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogPlayerInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_INFO, buffer );
}

void LogMessage::LogPlayerDebug( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
    LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_DEBUG, buffer );
}

void LogMessage::LogScriptError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
    LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogScriptInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_INFO, buffer );
}

// CenterServer
void LogMessage::LogPlatformError( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( PLATFORMOBJECT, LOG_PRIORITY_ERROR, buffer );
}

void LogMessage::LogPlatformInfo( const char* format, ... )
{
    static char buffer[ BUFFER_SIZE_LOG ] = { 0 };
    FORMAT_MESSAGE( format, buffer, sizeof( buffer ) );
	LOG_MESSAGE( PLATFORMOBJECT, LOG_PRIORITY_INFO, buffer );
}