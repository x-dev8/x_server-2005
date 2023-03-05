#ifndef __FORMATSTRING_H__
#define __FORMATSTRING_H__

#include "MeRTLibs.h"
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

static const int FS_BUFFER_DEFAULT = 1024;

template<const int iBufLen>
class CFormatString
{
public:
    CFormatString( LPCTSTR szStr, ... )
    {
        va_list vl;
        va_start(vl, szStr);
        vsnprintf(szBuffer, sizeof(szBuffer)-1, (char*)szStr, vl);
        va_end(vl);
    }
    operator char *()       { return szBuffer; }
    operator const char *() { return szBuffer; }
protected:
    char szBuffer[iBufLen];
};

template<const int iBufLen> const char * FormatString( const char * szString, ... )
{
    if( NULL == szString )
        return NULL;

    int nLength = (int)strlen( szString );
    if ( nLength <=0 )
        return NULL;

    static char data[iBufLen];

    va_list	va;
    va_start( va, szString );
    wvnsprintf(data, sizeof(data)-1, szString, va );
    va_end( va );

    return data;
}

typedef CFormatString<FS_BUFFER_DEFAULT> CFMSTR;
#define FMSTR FormatString<FS_BUFFER_DEFAULT>

#endif // __FORMATSTRING_H__
