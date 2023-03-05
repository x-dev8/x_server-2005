/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwDebug.cpp
* Create: 	10/06/06
* Desc:		µ÷ÊÔ´úÂë
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
// #include <windows.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <assert.h>
#include "MeTerrain/SwDebug.h"

#define _MAX_DEBUG_DEPTH			32
#define _MAX_DEBUG_STRING_LENGTH	(_MAX_DEBUG_DEPTH * 20 + 2048)

namespace Ze
{
	//////////////////////////////////////////////////////////////////////////

	static int		s_lineNumber = 0;
	static char		s_strTempFileName[_MAX_PATH];
	static char		s_strTempBuffer[_MAX_DEBUG_STRING_LENGTH];
	static wchar_t  s_strTempBufferW[_MAX_DEBUG_STRING_LENGTH];
	static char		s_strTempString[_MAX_DEBUG_STRING_LENGTH];

	////////////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	void _Trace( const char* pMsg, ... )
		//------------------------------------------------------------------------
	{
		va_list args;
		va_start( args, pMsg );
		memset( s_strTempBuffer, 0, _MAX_DEBUG_STRING_LENGTH * sizeof(char) );
#if _MSC_VER >= 1400
		vsprintf_s( s_strTempBuffer, pMsg, args );
#else
		vsprintf( s_strTempBuffer, pMsg, args );
#endif
		va_end(args);

		OutputDebugStringA( s_strTempBuffer );
	}

	////////////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	void _TraceW( const wchar_t* pMsg, ... )
		//------------------------------------------------------------------------
	{
		va_list args;
		va_start( args, pMsg );
		memset( s_strTempBufferW, 0, _MAX_DEBUG_STRING_LENGTH * sizeof(wchar_t) );
#if _MSC_VER >= 1400
		vswprintf_s( s_strTempBufferW, pMsg, args );
#else
		vswprintf( s_strTempBufferW, pMsg, args );
#endif
		va_end(args);

		OutputDebugStringW( s_strTempBufferW );
	}

	//------------------------------------------------------------------------
	void _KeepFileLine( const char* pFileName, int pLine )
		//------------------------------------------------------------------------
	{
		s_lineNumber	= 0;
		memset( s_strTempFileName, 0, _MAX_PATH * sizeof(char) );
		size_t len		= strlen( pFileName );
		if( len > 0 && len < (_MAX_PATH - 1) )
		{
			memcpy( s_strTempFileName, pFileName, len * sizeof( char ) + 1);
			s_lineNumber = pLine;
		}
	}

	//------------------------------------------------------------------------
	void _TraceEx( const char* pMsg, ... )
		//------------------------------------------------------------------------
	{
		va_list args;
		va_start( args, pMsg );
		memset( s_strTempString, 0, _MAX_DEBUG_STRING_LENGTH * sizeof(char) );
#if _MSC_VER >= 1400
		vsprintf_s( s_strTempString, pMsg, args );
#else
		vsprintf( s_strTempString, pMsg, args );
#endif
		va_end(args);

		_Trace( "%s(%u): %s", s_strTempFileName, s_lineNumber, s_strTempString );
	}

	//------------------------------------------------------------------------
	void _TraceAssert(bool expression, const char* message, const char* file, unsigned int line)
		//------------------------------------------------------------------------
	{
		if ( !expression )
		{
			_TraceEx( "%s(%d):ERROR [%s] \n", file, line, message );
			//assert( message && false );
		}
	}

};	// namespace Ze.

////////////////////////////////////////////////////////////////////////////////
// end of file
////////////////////////////////////////////////////////////////////////////////