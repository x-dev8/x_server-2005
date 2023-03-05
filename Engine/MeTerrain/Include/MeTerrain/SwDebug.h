/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwDebug.h
* Create: 	10/06/06
* Desc:		µ÷ÊÔ´úÂë
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __SWDEBUG_H__
#define __SWDEBUG_H__

///////////////////////////////////////////////////////////////////////////////
#ifdef SW_DEBUG

//#	define SW_TRACE_FULL
#	ifndef SW_TRACE_FULL 
#		define Trace		Ze::_Trace 
#       define TraceW       Ze::_TraceW
#	else
#		define Trace		Ze::_KeepFileLine( __FILE__, __LINE__); Ze::_TraceEx
#	endif
#	define BreakPoint()		_asm{ int 3 }
#ifndef Assert
#	define Assert( exp )	if( !(exp) ){ Ze::_TraceAssert( exp, #exp, __FILE__, __LINE__ ); BreakPoint(); }
#endif
#	define Verify( exp )	if( !(exp) ){ Ze::_TraceAssert( exp, #exp, __FILE__, __LINE__ ); BreakPoint(); }

#else

#	define Trace			__noop	
#ifndef Assert
#	define Assert( exp )	void(0)		
#endif
#	define Verify( exp )	( exp )

#endif

///////////////////////////////////////////////////////////////////////////////

namespace Ze
{
	void _Trace( const char* msg, ... );
	void _TraceW( const wchar_t* msg, ... );
	void _KeepFileLine( const char* filename, int line );
	void _TraceEx( const char* msg, ... );
	void _TraceAssert(bool expression, const char* message, const char* file, unsigned int line);
};

#endif	// __SWDEBUG_H__