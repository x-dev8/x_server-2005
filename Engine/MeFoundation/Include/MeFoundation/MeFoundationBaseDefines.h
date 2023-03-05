#pragma once

#ifdef _DEBUG
#	define MeNew new( __FILE__, __LINE__, __FUNCTION__ )
#	define MeDelete delete
#else
#	define MeNew new
#	define MeDelete delete
#endif // _DEBUG

#define MeDefaultNew new
#define MeDefaultDelete delete

/// Log
#ifdef _DEBUG
#define MeLogMessage MeLog::Instance().Print
#else
#define MeLogMessage
#endif //_DEBUG


#ifdef _DEBUG
#define MeOutputDebugStringA OutputDebugStringA
#define MeOutputDebugStringW OutputDebugStringW
#define MeOutputDebugString OutputDebugString
#else
#define MeOutputDebugStringA( msg )
#define MeOutputDebugStringW( msg )
#define MeOutputDebugString( msg )
#endif // _DEBUG

/// for timer
typedef __int64 MeTimeValue;