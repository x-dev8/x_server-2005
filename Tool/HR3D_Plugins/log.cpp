#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
#include "log.h"
CLog g_log;
void CLog::Print( const char* string, ... )
{
	va_list	va;
	static char data[1024];

	va_start( va, string );
	wvsprintf( (char*)data, string, va );
	va_end( va );
	m_strings.push_back( data );
}
