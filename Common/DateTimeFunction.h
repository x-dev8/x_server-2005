/********************************************************************
    Filename:     DateTimeFunction.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_DATETIMEFUNCTION_H__
#define __COMMON_DATETIMEFUNCTION_H__

#pragma once

#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/timeb.h>

namespace DateTimeFunction
{
    // 获得本周是今年的第几周 0 - 53
    inline int GetWeekOfYear( void )
    {
        char timebuf[3] ;
        time_t ltime    ;
        struct tm today ;

        _tzset();

        time( &ltime );
        
        errno_t err = _localtime64_s( &today, &ltime );
        if ( err )
        { return -1; }

        strftime( timebuf, sizeof(timebuf), "%U", &today );

        int nWeekOfYear = 0;
        if ( 1 != sscanf(timebuf, "%d", &nWeekOfYear) )
        { return -1; }

        return nWeekOfYear;
    }

    inline int GetWeekOfYear( time_t ltime )
    {
        char timebuf[3] ;
        struct tm today ;

        _tzset();

        errno_t err = _localtime64_s( &today, &ltime );
        if ( err )
        { return -1; }

        strftime( timebuf, sizeof(timebuf), "%U", &today );

        int nWeekOfYear = 0;
        if ( 1 != sscanf(timebuf, "%d", &nWeekOfYear) )
        { return -1; }

        return nWeekOfYear;
    }
}

using namespace DateTimeFunction;

#endif // __COMMON_DATETIMEFUNCTION_H__
